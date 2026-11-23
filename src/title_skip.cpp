// Dev: the boot's title screens skipped, for tests that load a save or start a game (/title/skip, p3.py flow load,
// up --slot, flow newgame). ATitleActor runs a state machine: TitleStates (+0x288, a TMap<ETitleState, UTitleState*>:
// elements of 0x18 bytes, the key at +0 and the state at +8, the count at +0x290), and each state's update (its vtable
// at +0x280) takes (state, delta) and returns the state to go to next. Detours on those updates return the target
// once armed: the notices (Caution, PhotosensitiveCaution, NetworkCheck) go on to the Logo, which runs once (it starts
// the title's loading) and then goes to the target: LoadGame (the save list), PressWait (the title menu after its
// press-wait) or NewGame. The method is p3rpc.essentials' intro skip (IntroSkip.cs). One-shot: the skip disarms
// after it is used, the detours then pass through until unload. Only a route arms it, so the player's game never skips.
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "ue/scan.h"
#include "ue/ue.h"
#include <windows.h>
#include <utility>
#include <atomic>
#include <format>
#include <string>

namespace p3a::title_skip {
using namespace ue;
namespace {
enum : uint8_t { TS_Logo = 3, TS_OP = 4, TS_PressWait = 5, TS_NewGame = 7, TS_LoadGame = 8 };
using Update = uint8_t (*)(UObject* state, float delta);

std::atomic<int> g_target{-1};   // the state to skip to, -1 disarmed

std::string state_name(UObject* s) {
  std::string n = name_of(class_of(s));
  return n.rfind("TitleState", 0) == 0 ? n.substr(10) : n;
}

uint8_t decide(UObject* self, uint8_t next) {
  int target = g_target;
  if (target < 0) return next;
  std::string n = state_name(self);
  if (n == "Caution" || n == "PhotosensitiveCaution" || n == "NetworkCheck") return TS_Logo;
  if (n == "Logo" || n == "OP" || n == "OP_Astrea" || n == "PressWait" || n == "PressWait_Astrea") {
    g_target = -1;
    log::writef("title_skip: {} -> state {}", n, target);
    return (uint8_t)target;
  }
  return next;
}

// One detour per distinct update function (each state class has its own).
constexpr int kSlots = 12;
Update g_orig[kSlots] = {};
template <int I>
uint8_t detour(UObject* self, float delta) { return decide(self, g_orig[I](self, delta)); }
template <int... I>
constexpr Update make(int i, std::integer_sequence<int, I...>) { constexpr Update all[] = {&detour<I>...}; return all[i]; }
Update detour_at(int i) { return make(i, std::make_integer_sequence<int, kSlots>{}); }
uintptr_t g_target_fn[kSlots] = {};
int g_used = 0;

// Every title state's update hooked (once per function): what was hooked, for the route's answer.
std::string hook_states(UObject* actor) {
  uint8_t* a = (uint8_t*)actor;
  uint8_t* elems = *(uint8_t**)(a + 0x288);
  int count = *(int*)(a + 0x290);
  if (!elems || count <= 0 || count > 32) return std::format("no title states (count {})\n", count);
  uintptr_t lo = scan::exe_base();
  auto* nt = (IMAGE_NT_HEADERS*)(lo + ((IMAGE_DOS_HEADER*)lo)->e_lfanew);
  uintptr_t hi = lo + nt->OptionalHeader.SizeOfImage;
  std::string out;
  for (int i = 0; i < count; ++i) {
    UObject* s = *(UObject**)(elems + i * 0x18 + 8);
    if (!s || name_of(class_of(s)).rfind("TitleState", 0) != 0) continue;
    uintptr_t fn = (*(uintptr_t**)s)[0x280 / 8];
    if (fn < lo || fn >= hi) continue;
    bool have = false;
    for (int k = 0; k < g_used; ++k) have |= g_target_fn[k] == fn;
    if (have || g_used == kSlots) continue;
    int k = g_used;
    g_orig[k] = (Update)fn;
    if (!hooks::attach((void**)&g_orig[k], (void*)detour_at(k), "title state update (dev skip)")) { g_orig[k] = nullptr; continue; }
    g_target_fn[k] = fn;
    ++g_used;
    out += std::format("hooked {} {:#x}\n", state_name(s), fn - lo);
  }
  return out;
}
}  // namespace

void install() {
  dev::route("/title/skip", [](const dev::Request& r, int& status) {
    std::string to = dev::arg(r, "to");
    int target = to == "load" ? TS_LoadGame : to == "menu" ? TS_PressWait : to == "newgame" ? TS_NewGame : to == "off" ? -1 : -2;
    if (target == -2) { status = 400; return std::string("?to=load|menu|newgame|off\n"); }
    return dev::on_game([target]() -> std::string {
      if (target < 0) { g_target = -1; return "off\n"; }
      UObject* actor = find_first("TitleActor");
      if (!actor) return "no title actor (not on the title)\n";
      UObject* cur = get<UObject*>(actor, "CurrentTitleState");
      std::string now = cur ? state_name(cur) : "none";
      if (now == "Select" || now == "Select_Astrea" || now == "LoadGame" || now == "NewGame" || now == "Config")
        return std::format("already past the boot screens ({})\n", now);
      std::string hooked = hook_states(actor);
      g_target = target;
      log::writef("title_skip: armed for state {} from {}", target, now);
      return std::format("armed: state {} from {}\n{}", target, now, hooked);
    });
  }, "?to=load|menu|newgame|off dev: skip the boot's title screens to the save list, the title menu or a new game");
}
}  // namespace p3a::title_skip
