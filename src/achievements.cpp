// Achievements (Steam's trophies). Every one the game asks for goes through one function, FUN_1412aa8a0(self, name,
// progress, flag): the scripts' TROPHY_REQUEST(name, 100) (FUN_1412ad140) and the game's own calls ("ACH_DAMAGE_999",
// "ACH_SKILL_CHANGE"...); a progress of 100 (200 for some) unlocks. The names are Steam's achievement ids
// (WindowsEngine.ini, Achievement_N_Id). Steam shows an unlock only in its overlay, which no screen reader reads: the
// mod says it. A request for one Steam has not unlocked yet is kept, and said once Steam has it unlocked (the game
// hands it on through the engine's online layer); one unlocked before (a count asked again at 100, the Monad doors')
// is never said. The name and description are Steam's own, in the player's Steam language.
#include "achievements.h"
#include "core/strings.h"
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "speech.h"
#include "ue/scan.h"
#include "ue/ue.h"
#include <windows.h>
#include <algorithm>
#include <format>
#include <mutex>
#include <string>
#include <vector>

namespace p3a::achievements {

using Request_t = void (*)(void*, const char*, float, char);
static Request_t g_request = nullptr;

using UserStats_t = void* (*)();
using GetAchievement_t = bool (*)(void*, const char*, bool*);
using Attribute_t = const char* (*)(void*, const char*, const char*);
struct Steam { UserStats_t stats = nullptr; GetAchievement_t get = nullptr; Attribute_t attr = nullptr; };
static Steam steam() {
  static Steam s;
  if (s.stats) return s;
  HMODULE m = GetModuleHandleW(L"steam_api64.dll");
  if (!m) return s;
  s.get = (GetAchievement_t)GetProcAddress(m, "SteamAPI_ISteamUserStats_GetAchievement");
  s.attr = (Attribute_t)GetProcAddress(m, "SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute");
  if (s.get && s.attr) s.stats = (UserStats_t)GetProcAddress(m, "SteamAPI_SteamUserStats_v012");
  return s;
}
// Whether Steam has it unlocked: 1 yes, 0 no, -1 Steam cannot say (not running, an unknown name).
static int unlocked(const Steam& s, const std::string& name) {
  void* us = s.stats ? s.stats() : nullptr;
  bool done = false;
  return us && s.get(us, name.c_str(), &done) ? (done ? 1 : 0) : -1;
}

static std::mutex g_mu;
static std::vector<std::string> g_pending;   // asked for while locked: said once Steam has them

static void request_hook(void* self, const char* name, float progress, char flag) {
  if (name && progress >= 100.f) {
    std::string n = name;
    int was = unlocked(steam(), n);
    log::writef("achievements: {} asked for ({}), {}", n, progress, was == 1 ? "unlocked before" : was == 0 ? "locked" : "Steam cannot say");
    if (was == 0) {
      std::lock_guard lk(g_mu);
      if (std::find(g_pending.begin(), g_pending.end(), n) == g_pending.end()) g_pending.push_back(n);
    }
  }
  g_request(self, name, progress, flag);
}

void tick() {
  std::vector<std::string> due;
  {
    std::lock_guard lk(g_mu);
    if (g_pending.empty()) return;
    Steam s = steam();
    for (auto i = g_pending.begin(); i != g_pending.end();) {
      if (unlocked(s, *i) == 1) { due.push_back(*i); i = g_pending.erase(i); }
      else ++i;
    }
  }
  Steam s = steam();
  void* us = s.stats ? s.stats() : nullptr;
  for (auto& n : due) {
    const char* t = us ? s.attr(us, n.c_str(), "name") : nullptr;
    const char* d = us ? s.attr(us, n.c_str(), "desc") : nullptr;
    std::string title = t && *t ? t : n, desc = d ? d : "";
    log::writef("achievements: {} unlocked ({})", n, title);
    speech::speak(std::format("{}: {}", strings::kAchievementUnlocked, title) + (desc.empty() ? "" : ". " + desc), false);
  }
}

void install() {
  if (!ue::known_build()) return;   // this build's address
  g_request = (Request_t)(scan::exe_base() + 0x12aa8a0);
  hooks::attach((void**)&g_request, (void*)&request_hook, "achievement request");
  // Dev: what Steam says of one (?name=ACH_SEES_JOIN): unlocked or not, its name and description. Reads only.
  dev::route("/achievements", [](const dev::Request& r, int&) {
    std::string n = dev::arg(r, "name");
    Steam s = steam();
    void* us = s.stats ? s.stats() : nullptr;
    if (!us) return std::string("no Steam user stats\n");
    std::string out;
    {
      std::lock_guard lk(g_mu);
      for (auto& p : g_pending) out += "pending " + p + "\n";
    }
    if (n.empty()) return out + "?name=ACH_...\n";
    // &ask=1: ask the game for it at 100, as its own calls do (through the hook): only for one unlocked already, so
    // a test never unlocks the player's achievement. &say=1: queue it as if asked for while locked (says it now).
    if (dev::arg_int(r, "ask") && unlocked(s, n) == 1)
      hooks::run_on_game_thread([n] {
        uint8_t* g = ((uint8_t * (*)())(scan::exe_base() + 0x122ac90))();
        if (g) ((Request_t)(scan::exe_base() + 0x12aa8a0))(g + 0x109f8, n.c_str(), 100.f, 0);
      });
    if (dev::arg_int(r, "say")) { std::lock_guard lk(g_mu); g_pending.push_back(n); }
    const char* t = s.attr(us, n.c_str(), "name");
    const char* d = s.attr(us, n.c_str(), "desc");
    return out + std::format("{}: unlocked {} name '{}' desc '{}'\n", n, unlocked(s, n), t ? t : "", d ? d : "");
  }, "?name=ACH_...[&ask=1 (an unlocked one)|&say=1] what Steam says of an achievement (dev)");
}
}  // namespace p3a::achievements
