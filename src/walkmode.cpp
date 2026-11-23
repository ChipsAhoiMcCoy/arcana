// Walking on the keyboard (walkmode.h).
//  - FldPlayerComp (Daily and Dungeon heroes): PlayerData (FFldPlayerData) +0xE8, its InputWalkZone at +0x4 (comp
//    +0xEC); SpeedData {Walk, Run, Dash, Assault} +0x2D0; bEnableDash +0x2E8, bEnableAssault +0x2E9; the input
//    vector +0x3B0. FUN_1411302c0 (each frame of movement): length < 0.01 stands; bEnableAssault, then bEnableDash
//    take their speeds; else length < InputWalkZone walks (SpeedData.Walk, RotSpeed_Walk), otherwise runs.
//    FUN_141131a30 (the speed state the Shadows' sight reads) compares the same zone.
#include "walkmode.h"
#include "core/strings.h"
#include "devserver.h"
#include "keys.h"
#include "log.h"
#include "nav.h"
#include "world.h"
#include "ue/ue.h"
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
  dev::route("/walkmode", [](const dev::Request& r, int&) {
    bool flip = dev::has(r, "toggle");
    return dev::on_game([flip] {
      if (flip) g_dev = !g_dev;
      std::string s = std::format("walking {} (Alt {}, dev {}), auto-walk {}, kept {}\n", g_on, keys::alt_held(), g_dev, nav::walking(), g_kept.size());
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
