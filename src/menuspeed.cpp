#include "menuspeed.h"
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "msg.h"
#include "seh.h"
#include "settings.h"
#include "watch.h"
#include "world.h"
#include "screens/battle_state.h"
#include "screens/camp.h"
#include "screens/menu.h"
#include "screens/screen.h"
#include "ue/ue.h"
#include <cmath>
#include <cstdlib>
#include <format>
#include <vector>

namespace p3a::menuspeed {
using namespace ue;

// The setting's choices, as time scales. The world clamps to its MaxGlobalTimeDilation (20 in this game).
static const float kScale[] = {1.f, 4.f, 8.f, 16.f};
static float g_dev_scale = 0;      // /menuspeed?scale=N: overrides the setting (0: the setting decides)
static bool g_applied = false;     // our scale is on
static float g_given = 1.f;        // the scale we set
static float g_before = 1.f;       // the game's value when we set ours
static const char* g_why = "off";  // why the scale is (not) on, for /menuspeed
static const char* g_busy = "";    // what the menu is at (MenuScreen::busy), for the log
static std::vector<WeakObj> g_kept;  // the characters held at the game's own time (keep_characters)

static float scale_wanted() {
  if (g_dev_scale > 0) return g_dev_scale;
  int i = settings::get(settings::MenuSpeed);
  return i > 0 && i < (int)std::size(kScale) ? kScale[i] : 1.f;
}

// In a battle, only a menu opening before it has ever taken a key: nothing acts then (a turn's actions start from a
// confirm, and the player has not had the keys yet), so the menu's fly-in, and the camera and idle world meanwhile,
// are all the scale speeds; the characters keep the game's time (keep_characters). It is off from the frame the menu
// takes input, before any press. The end of an action before the next turn's wheel (~1 s) is the action's own.
//   The wheel: a turn opens it with its keys unbound for TopUIDelayFrame / 30 s of game time (10 frames;
//   BP_BtlGuiComponent SetBindTimer, then SetState(1)); BP_BtlGuiBaseActor holds BindFlag until its timer binds them.
//   A list (skills, items, Theurgy, targets, ...): its MenuScreen opening and not yet said (the list's slide-in; the
//   Theurgy list's InAnimEnd is the end of its 0.9 s opening timeline).
static bool battle_menu_opening() {
  using namespace screens;
  g_why = "battle";
  g_busy = "";
  if (gui_state() == 0) return false;
  if (auto* m = dynamic_cast<MenuScreen*>(current())) {
    if (std::string_view(m->id()).starts_with("battle_") && m->opening()) { g_why = m->id(); g_busy = "opening"; return true; }
    return false;
  }
  static Finder top{"BP_BtlTopUI_C"};
  UObject* t = gui_state() == 1 ? top.get() : nullptr;
  if (t && get_bool(t, "isStateInit") && get_bool(t, "BindFlag")) { g_why = "battle wheel"; g_busy = "keys not bound yet"; return true; }
  return false;
}

// Whether a menu is up that the scale may speed (header).
static bool menu_up() {
  static const int battle = watch::want("BtlCoreComponent");
  if (watch::get(battle)) return battle_menu_opening();
  if (world::scene_playing()) { g_why = "story scene"; return false; }
  if (msg::current().open) { g_why = "message window"; return false; }
  // The game pauses itself while its window is minimized (the world's time stands still, the camp root's timer with it):
  // a list then reads as not taking input, and the camp counted as busy for 8 minutes while the player was away
  // (2026-11-17). Nothing runs to be sped.
  if (UObject* w = gworld()) {
    auto p = call_static("GameplayStatics", "IsGamePaused", [w](Params& p) { p.set<UObject*>("WorldContextObject", w); });
    if (p.fn && p.ret<bool>()) { g_why = "game paused"; return false; }
  }
  // A menu sitting idle runs at the game's time: the game times its idle lines (Igor's "Take all the time you need",
  // 15 s in the request list) on the same clock, and they came sixteen times as often (the user's report, 2026-11-17).
  if (auto* m = dynamic_cast<screens::MenuScreen*>(screens::current())) {
    const char* busy = nullptr;
    guarded([&] { busy = m->busy(); });
    g_why = busy ? m->id() : "waiting for the player";
    g_busy = busy ? busy : "";
    return busy != nullptr;
  }
  g_busy = "";
  if (screens::camp_open()) { g_why = "camp, between screens"; return true; }   // between the root and a submenu
  if (auto* s = screens::animating()) { g_why = s->id(); return true; }
  g_why = "no menu";
  return false;
}

static float read_scale(UObject* w) {
  auto p = call_static("GameplayStatics", "GetGlobalTimeDilation", [w](Params& p) { p.set<UObject*>("WorldContextObject", w); });
  return p.fn ? p.ret<float>() : -1.f;
}
static void write_scale(UObject* w, float v) {
  call_static("GameplayStatics", "SetGlobalTimeDilation", [w, v](Params& p) {
    p.set<UObject*>("WorldContextObject", w);
    p.set<float>("TimeDilation", v);
  });
}

// The characters on screen (Igor at the fusion table, the camp's party model) keep the game's own time: their looping
// idles carry sounds (Igor's cards), which a sped world played many times a second (the user's report, 2026-11-17).
// Each Character's CustomTimeDilation is 1 / scale while the scale is on, one spawned meanwhile included; given back
// unless the game set its own.
static void keep_characters(float scale) {
  static const int chars = watch::want("Character", true);
  for (UObject* a : watch::all(chars)) {
    float* t = field<float>(a, "CustomTimeDilation");
    if (!t || std::fabs(*t - 1.f) >= 0.001f) continue;   // ours already, or the game's own
    *t = 1.f / scale;
    g_kept.push_back(WeakObj::of(a));
  }
}
static void free_characters(float scale) {
  for (auto& k : g_kept)
    if (UObject* a = k.resolve())
      if (float* t = field<float>(a, "CustomTimeDilation"); t && std::fabs(*t - 1.f / scale) < 0.001f) *t = 1.f;
  g_kept.clear();
}

static void release(UObject* w, const char* why) {
  if (!g_applied) return;
  g_applied = false;
  free_characters(g_given);
  float now = w ? read_scale(w) : -1.f;
  // Only our own value is taken back: one the game set meanwhile is the game's.
  if (w && std::fabs(now - g_given) < 0.01f) write_scale(w, g_before);
  log::writef("menuspeed: off ({}), the game's {:.2f} back", why, g_before);
}

void tick() {
  UObject* w = gworld();
  float want = scale_wanted();
  bool menu = menu_up();
  if (!w) { g_applied = false; g_kept.clear(); return; }
  if (g_applied) {
    float now = read_scale(w);
    if (std::fabs(now - g_given) >= 0.01f) {   // the game changed it: its value stands
      g_applied = false;
      free_characters(g_given);
      log::writef("menuspeed: the game set {:.2f}, left to it", now);
      return;
    }
    if (!menu || want <= 1.f) { release(w, g_why); return; }
    if (std::fabs(want - g_given) >= 0.01f) { free_characters(g_given); write_scale(w, want); g_given = read_scale(w); }
    keep_characters(g_given);
    return;
  }
  if (!menu || want <= 1.f) return;
  float before = read_scale(w);
  // Only over the game's normal time: a slowed or sped world (a battle's own dilation) is the game's.
  if (before < 0 || std::fabs(before - 1.f) >= 0.01f) return;
  g_before = before;
  write_scale(w, want);
  g_given = read_scale(w);
  g_applied = true;
  keep_characters(g_given);
  log::writef("menuspeed: on ({}{}{}), {:.0f} times", g_why, *g_busy ? ", " : "", g_busy, g_given);
}

void shutdown() { release(gworld(), "unload"); }

void install() {
  dev::route("/menuspeed", [](const dev::Request& r, int&) {
    std::string s = dev::arg(r, "scale");
    return dev::on_game([s] {
      if (!s.empty()) g_dev_scale = (float)atof(s.c_str());
      UObject* w = gworld();
      auto clock = [w](const char* fn) {
        auto p = call_static("GameplayStatics", fn, [w](Params& p) { p.set<UObject*>("WorldContextObject", w); });
        return p.fn ? p.ret<float>() : -1.f;
      };
      return std::format("scale wanted {:.2f} (dev {:.2f}), applied {}, world {:.2f}, menu: {}, characters kept {}\n"
                         "clocks: game {:.3f} real {:.3f} unpaused {:.3f}, frame {}\n",
                         scale_wanted(), g_dev_scale, g_applied, w ? read_scale(w) : -1.f, g_why, g_kept.size(),
                         w ? clock("GetTimeSeconds") : -1.f, w ? clock("GetRealTimeSeconds") : -1.f,
                         w ? clock("GetUnpausedTimeSeconds") : -1.f, hooks::frame());
    });
  }, "?scale=N overrides the menu speed setting (0: the setting); the world's time scale and why");
}
}  // namespace p3a::menuspeed
