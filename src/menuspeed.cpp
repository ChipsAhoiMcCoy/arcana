#include "menuspeed.h"
#include "devserver.h"
#include "log.h"
#include "msg.h"
#include "settings.h"
#include "watch.h"
#include "world.h"
#include "screens/camp.h"
#include "screens/menu.h"
#include "screens/screen.h"
#include "ue/ue.h"
#include <cmath>
#include <cstdlib>
#include <format>

namespace p3a::menuspeed {
using namespace ue;

// The setting's choices, as time scales. The world clamps to its MaxGlobalTimeDilation (20 in this game).
static const float kScale[] = {1.f, 4.f, 8.f, 16.f};
static float g_dev_scale = 0;      // /menuspeed?scale=N: overrides the setting (0: the setting decides)
static bool g_applied = false;     // our scale is on
static float g_given = 1.f;        // the scale we set
static float g_before = 1.f;       // the game's value when we set ours
static const char* g_why = "off";  // why the scale is (not) on, for /menuspeed

static float scale_wanted() {
  if (g_dev_scale > 0) return g_dev_scale;
  int i = settings::get(settings::MenuSpeed);
  return i > 0 && i < (int)std::size(kScale) ? kScale[i] : 1.f;
}

// Whether a menu is up that the scale may speed (header).
static bool menu_up() {
  static const int battle = watch::want("BtlCoreComponent");
  if (watch::get(battle)) { g_why = "battle"; return false; }
  if (world::scene_playing()) { g_why = "story scene"; return false; }
  if (msg::current().open) { g_why = "message window"; return false; }
  if (screens::camp_open()) { g_why = "camp"; return true; }
  if (dynamic_cast<screens::MenuScreen*>(screens::current())) { g_why = screens::current()->id(); return true; }
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

static void release(UObject* w, const char* why) {
  if (!g_applied) return;
  g_applied = false;
  float now = w ? read_scale(w) : -1.f;
  // Only our own value is taken back: one the game set meanwhile is the game's.
  if (w && std::fabs(now - g_given) < 0.01f) write_scale(w, g_before);
  log::writef("menuspeed: off ({}), the game's {:.2f} back", why, g_before);
}

void tick() {
  UObject* w = gworld();
  float want = scale_wanted();
  bool menu = menu_up();
  if (!w) { g_applied = false; return; }
  if (g_applied) {
    float now = read_scale(w);
    if (std::fabs(now - g_given) >= 0.01f) {   // the game changed it: its value stands
      g_applied = false;
      log::writef("menuspeed: the game set {:.2f}, left to it", now);
      return;
    }
    if (!menu || want <= 1.f) { release(w, g_why); return; }
    if (std::fabs(want - g_given) >= 0.01f) { write_scale(w, want); g_given = read_scale(w); }
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
  log::writef("menuspeed: on ({}), {:.0f} times", g_why, g_given);
}

void shutdown() { release(gworld(), "unload"); }

void install() {
  dev::route("/menuspeed", [](const dev::Request& r, int&) {
    std::string s = dev::arg(r, "scale");
    return dev::on_game([s] {
      if (!s.empty()) g_dev_scale = (float)atof(s.c_str());
      UObject* w = gworld();
      return std::format("scale wanted {:.2f} (dev {:.2f}), applied {}, world {:.2f}, menu: {}\n", scale_wanted(),
                         g_dev_scale, g_applied, w ? read_scale(w) : -1.f, g_why);
    });
  }, "?scale=N overrides the menu speed setting (0: the setting); the world's time scale and why");
}
}  // namespace p3a::menuspeed
