// Walking on the keyboard (walkmode.h).
//  - FldPlayerComp (Daily and Dungeon heroes): PlayerData (FFldPlayerData) +0xE8, its InputWalkZone at +0x4 (comp
//    +0xEC); SpeedData {Walk, Run, Dash, Assault} +0x2D0; bEnableDash +0x2E8, bEnableAssault +0x2E9; the input
//    vector +0x3B0. FUN_1411302c0 (each frame of movement): length < 0.01 stands; bEnableAssault, then bEnableDash
//    take their speeds; else length < InputWalkZone walks (SpeedData.Walk, RotSpeed_Walk), otherwise runs.
//    FUN_141131a30 (the speed state the Shadows' sight reads) compares the same zone.
//  - The Dash key: FUN_1411d7db0 (the player controller's movement each frame) sets bEnableDash through its setter
//    FUN_14113cdf0 (`mov [rcx+0x2E8], dl; ret`) to: input action 0x31 held (FUN_140c9f310: Shift, RT) and not
//    BIT 0x40000075 (FUN_14122a080 on the flag manager FUN_14122ac90; the game's "no dashing" flag). That call site is
//    found by its bytes below. The only reader that matters is FUN_141133ba0 ("is dashing": moving and bEnableDash or
//    bEnableAssault), and all its callers are the Shadows' sight: outside Tartarus a dash costs nothing.
#include "walkmode.h"
#include "core/strings.h"
#include "devserver.h"
#include "hooks.h"
#include "keys.h"
#include "log.h"
#include "nav.h"
#include "settings.h"
#include "seh.h"
#include "world.h"
#include "ue/scan.h"
#include "ue/ue.h"
#include <cstring>
#include <cmath>
#include <format>
#include <vector>

namespace p3a::walkmode {
using namespace ue;

constexpr float kZone = 2.0f;   // past a full push (1.0): every push walks

struct Kept { WeakObj comp; float game; };
static std::vector<Kept> g_kept;   // components whose zone is ours, with the game's value
static bool g_dev = false;   // /walkmode?toggle=1: walking without Alt (tests)
static bool g_on = false;

bool on() { return g_on; }

// ---- always dash (settings::AlwaysDash) ----
// The setter is hooked: the game hands it "Dash held and allowed" each frame; with the option on, the daily hero
// (FldPlayerDailyComp: never the Tartarus or Episode Aigis dungeon hero, FldPlayerDungeonComp) gets "allowed and Dash
// not held" instead, while the player has him (world::exploring) and Alt is not held (Alt walks: the Dash flag is
// checked before the walk zone). So the three paces stay: dash by default, Shift (RT) runs, Alt walks.
using SetDash_t = void (*)(UObject* comp, uint8_t on);
using FlagMgr_t = void* (*)();
using FlagChk_t = char (*)(void* mgr, uint32_t bit);
static SetDash_t g_set_dash = nullptr;
static FlagMgr_t g_flag_mgr = nullptr;
static FlagChk_t g_flag_chk = nullptr;
constexpr uint32_t kNoDashFlag = 0x40000075;
static bool g_dash_turned = false;   // this frame's dash was the option's (/walkmode)

static bool always_dash_for(UObject* comp) {
  if (!settings::on(settings::AlwaysDash) || g_on || !comp || !world::exploring()) return false;
  static UClass* daily = nullptr;
  if (!daily) daily = find_class("FldPlayerDailyComp");
  return daily && is_a(comp, daily);
}
static void set_dash_hook(UObject* comp, uint8_t held) {
  uint8_t v = held;
  bool turned = false;
  guarded([&] {
    if (!always_dash_for(comp)) return;
    bool allowed = !g_flag_chk(g_flag_mgr(), kNoDashFlag);
    v = allowed && !held;
    turned = true;
  });
  g_dash_turned = turned;
  g_set_dash(comp, v);
}
static void install_dash() {
  // mov rcx, rax; mov edx, 0x40000075; call flag check; test al, al; jne; mov dl, 1; jmp; xor dl, dl; mov rcx, rdi;
  // call the setter. The call before it gets the flag manager.
  uintptr_t at = scan::find_unique("E8 ?? ?? ?? ?? 48 8B C8 BA 75 00 00 40 E8 ?? ?? ?? ?? 84 C0 75 04 B2 01 EB 02 32 D2 48 8B CF E8 ?? ?? ?? ??");
  if (!at) { log::write("walkmode: the Dash key's call site not found: always dash is off"); return; }
  g_flag_mgr = (FlagMgr_t)scan::rip(at + 1);
  g_flag_chk = (FlagChk_t)scan::rip(at + 14);
  uintptr_t setter = scan::rip(at + 32);
  static const uint8_t body[] = {0x88, 0x91, 0xE8, 0x02, 0x00, 0x00, 0xC3};   // mov [rcx+0x2E8], dl; ret
  if (memcmp((const void*)setter, body, sizeof body) != 0) { log::write("walkmode: the Dash setter is not as expected: always dash is off"); return; }
  g_set_dash = (SetDash_t)setter;
  if (!hooks::attach((void**)&g_set_dash, (void*)&set_dash_hook, "SetEnableDash")) g_set_dash = nullptr;
}

static float* zone_of(UObject* comp) {
  float* data = comp ? field<float>(comp, "PlayerData") : nullptr;
  return data ? data + 1 : nullptr;   // FFldPlayerData.InputWalkZone
}

static void give_back() {
  for (const Kept& k : g_kept)
    if (float* z = zone_of(k.comp.resolve()); z && *z == kZone) *z = k.game;
  if (!g_kept.empty()) log::writef("walkmode: gave {} hero components their walk zone back", g_kept.size());
  g_kept.clear();
}

void tick() {
  const bool want = keys::alt_held() || g_dev;
  if (want != g_on) log::writef("walkmode: {}", want ? "walking" : "running");
  g_on = want;
  // The auto-walk keeps its pace (its stuck check and arrival expect a run): the game's zone while it walks.
  if (!g_on || nav::walking()) { if (!g_kept.empty()) give_back(); return; }
  UObject* p = world::player();
  if (!p) return;
  for (const char* name : {"FldPlayerDailyComp", "FldPlayerDungeonComp"}) {
    UObject* comp = get<UObject*>(p, name);
    float* z = zone_of(comp);
    if (!z || *z == kZone) continue;
    // A zone that is not ours: the game's (a new hero, or the game set its data again).
    WeakObj w = WeakObj::of(comp);
    bool known = false;
    for (Kept& k : g_kept) if (k.comp == w) { k.game = *z; known = true; }
    if (!known) g_kept.push_back({w, *z});
    log::writef("walkmode: {} walk zone {:.2f} -> {:.2f}", name, *z, kZone);
    *z = kZone;
  }
}

void shutdown() { give_back(); }

void install() {
  install_dash();
  dev::route("/walkmode", [](const dev::Request& r, int&) {
    bool flip = dev::has(r, "toggle");
    return dev::on_game([flip] {
      if (flip) g_dev = !g_dev;
      std::string s = std::format("walking {} (Alt {}, dev {}), auto-walk {}, kept {}, always dash {} (hooked {}, this frame {})\n", g_on, keys::alt_held(),
                                  g_dev, nav::walking(), g_kept.size(), settings::on(settings::AlwaysDash), g_set_dash != nullptr, g_dash_turned);
      if (UObject* p = world::player())
        for (const char* name : {"FldPlayerDailyComp", "FldPlayerDungeonComp"}) {
          UObject* comp = get<UObject*>(p, name);
          float* z = zone_of(comp);
          float* speed = comp ? field<float>(comp, "SpeedData") : nullptr;
          bool* dash = comp ? field<bool>(comp, "bEnableDash") : nullptr;
          if (z) s += std::format("{}: zone {:.2f}, speeds walk {:.0f} run {:.0f} dash {:.0f}, dash on {}\n", name, *z,
                                  speed ? speed[0] : -1.f, speed ? speed[1] : -1.f, speed ? speed[2] : -1.f, dash && *dash);
        }
      FVector v{};
      if (world::player_velocity(v)) s += std::format("speed {:.0f} cm/s\n", std::sqrt(v.x * v.x + v.y * v.y));
      return s;
    });
  }, "?toggle=1 walking as if Alt were held, on or off; the hero's walk zone, speeds and pace");
}
}  // namespace p3a::walkmode
