// After Grim Dark's harmful ground (GD Access, by Austin Hicks): its sounds (assets/audio/sight, zlib, see LICENSES/)
// and its design, a lane for each way the player can walk and a bed while he stands in it, put to a Shadow's sight.
//
// How a Shadow notices the hero (the game's own test, P3R.exe 0x113bb40 and its callers, one per mood):
//  - from the Shadow's centre (its root component) to the hero's: the distance in space, and the hero's yaw off the
//    Shadow's facing on the ground plane, -180..180;
//  - a line trace between the two centres on the FldAttackSight trace type (TraceTypeQuery3): walls and breakable
//    objects block it, other Shadows do not;
//  - never while the hero's FldPlayerComp.bNotSearchedByEnemies is set, while Fuuka's Jamming is up
//    (FldPlayerComp.bJammingSkill) against a Shadow whose SkillReaction.bJamming is set (all but the Reaper), or while
//    BIT 1410 (the Reaper on the floor) is set, against any Shadow but the Reaper;
//  - seen when the line is clear and the hero is inside ANY of the Shadow's cones (UFldEnemyDataAsset, the block for
//    its kind and mood: Normal, anger, Confusion, fear, upset, Rare; each an FFldEnemy*Param whose search params sit
//    at +0x04 NormalSearch, +0x0C PlayerNearSearch, +0x14 PlayerDashSearch, each {Range cm, Angle deg, the whole
//    cone}): NormalSearch, PlayerNearSearch, and PlayerDashSearch while the hero dashes (moving, with bEnableDash or
//    bEnableAssault set on his FldPlayerComp). PlayerShootSerach (Episode Aigis' shots) is not modelled.
//  - Instant: the roaming states run the test every frame, and a pass goes straight to the noticing state (the
//    exclamation mark) without testing again; there is no meter that fills.
// Only a wandering Shadow tests its sight: its behaviour object (FldEnemyNormalComp +0x388) at step 4 (on the move) or
// 5 (waiting between moves). Noticing is step 6 (the mark, ~0.75 s), the chase 7, contact 8 (watched on floor 2,
// 2026-11-19); a floor's Shadows stand at another step until the player first moves. Every other step is left out.
// The mark and TrackingTarget stay set after a Shadow gives up and wanders again: they say nothing of now.
#include "sight.h"
#include "audio.h"
#include "core/sight_cone.h"
#include "core/strings.h"
#include "devserver.h"
#include "log.h"
#include "party.h"
#include "seh.h"
#include "settings.h"
#include "shadow.h"
#include "watch.h"
#include "world.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <format>
#include <map>
#include <memory>
#include <vector>

namespace p3a::sight {
namespace {
using namespace ue;
using core::SightCone;
using core::Vec3;
using world::FVector;

constexpr int kLaneHold = 20;   // audio::hold ids 20..23: the edge ahead, right, behind, left
constexpr int kBedHold = 24;    // 24 left, 25 right: hidden
constexpr int kDemoHold = 26;  // 26 an edge, 27 and 28 the hum
constexpr const char* kLaneFile[4] = {"north.wav", "east.wav", "south.wav", "west.wav"};   // ahead, right, behind, left
constexpr uint32_t kReaperBit = 0x20000582;   // BIT 1410: set as the Reaper appears on the floor
constexpr int kMaxTraces = 6;                 // per Shadow and direction, inside its sight
constexpr float kTraceStep = 25.0f;           // cm between them at least
constexpr int kTickTraces = 32;               // and in all, a tick (two Shadows behind walls)

// knobs (dev route /sight)
float g_gain = 0.8f;        // the edge's loudness at the edge
float g_bed_gain = 0.45f;   // the hidden hum's (Grim Dark's 0.45)
float g_bed_tone = 0.25f;   // its brightness: muffled (audio::hold's tone)
float g_bed_spread = 0.5f;  // its two halves, left and right
float g_band_dev = 0;       // cm; 0: the setting

// What the last tick found, for /sight.
struct Lane { float dist = 0; int shadow = -1; };
Lane g_lane[4];
float g_room[4] = {-1, -1, -1, -1};   // how far each way went before a wall (-1: not traced)
bool g_hidden = false;
int g_hidden_by = -1;
bool g_dashing = false;
std::string g_blind;          // why no Shadow can see the hero now, or empty
int g_traces = 0;
// The tick's cost while a Shadow is near enough to trace for (dev: /sight; ?reset=1 starts over).
double g_busy_us = 0, g_max_us = 0;
int g_busy_ticks = 0, g_max_traces = 0;
std::string g_shadows;        // one line per Shadow considered

// The mod's prediction against the game's mark, per Shadow.
struct Watch { int seen_ago = 1000; int seen_run = 0; bool alarm_counted = false; int step = -1; };
std::map<WeakObj::Key, Watch> g_watch;
int g_match = 0, g_missed = 0, g_false = 0;
constexpr int kMatchFrames = 3;    // the mark goes up within this many ticks of the mod saying "seen"
constexpr int kFalseFrames = 10;   // "seen" this many ticks running and no mark: the mod was wrong

std::string sound_dir() { return audio::module_dir() + "assets\\audio\\sight\\"; }
audio::Pcm load(const std::string& file) {
  auto v = std::make_shared<std::vector<float>>();
  if (!audio::decode_mono(sound_dir() + file, *v)) log::writef("sight: cannot load {}", file);
  return v;
}
const audio::Pcm& lane_pcm(int d) {
  static audio::Pcm p[4] = {load(kLaneFile[0]), load(kLaneFile[1]), load(kLaneFile[2]), load(kLaneFile[3])};
  return p[d];
}
const audio::Pcm& bed_pcm(int side) {
  static audio::Pcm p[2] = {load("hidden_left.wav"), load("hidden_right.wav")};
  return p[side];
}
// A direction from the player (no place in the world: it turns with him).
audio::Spot toward(float right, float ahead) {
  audio::Spot s;
  s.right = right; s.ahead = ahead; s.dist_m = 1.0f; s.pan = right;
  return s;
}
audio::Spot lane_spot(int d) {
  static const float r[4] = {0, 1, 0, -1}, a[4] = {1, 0, -1, 0};
  return toward(r[d], a[d]);
}
void play_bed(float vol, int id = kBedHold, int hold_ms = 250) {
  float side = g_bed_spread, front = std::sqrt(1.0f - side * side);
  audio::hold(id, bed_pcm(0), vol, toward(-side, front), 1.0f, g_bed_tone, 0.0f, hold_ms);
  audio::hold(id + 1, bed_pcm(1), vol, toward(side, front), 1.0f, g_bed_tone, 0.0f, hold_ms);
}
void silence() {
  for (int i = 0; i < 4; ++i) audio::release_hold(kLaneHold + i);
  audio::release_hold(kBedHold);
  audio::release_hold(kBedHold + 1);
}

UObject* first_object(UObject* o, const char* prop) {
  UObject** p = field<UObject*>(o, prop);
  return p ? *p : nullptr;
}
UObject* hero_comp() {
  static const int id = watch::want("FldPlayerDungeonComp");   // an FldPlayerComp: the flags below are its
  return watch::get(id);
}

// One Shadow as its sight stands this tick.
struct Eye {
  UObject* actor = nullptr;
  int index = -1;
  Vec3 at;
  std::vector<SightCone> cones;
  const char* block = "";
  bool hunting = false, marked = false;
  int step = -1;   // its behaviour's step (see behaviour_step)
  bool skip = false; const char* why = "";
};

// The step a Shadow's behaviour is at: FldEnemyNormalComp +0x388 holds its native state object (built per mood,
// FUN_141140a40), whose +0x08 is the step and +0x6C the seconds in it (floor 2, 2026-11-19). -1: none.
int behaviour_step(UObject* comp) {
  int step = -1;
  guarded([&] {
    uint8_t* so = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(comp) + 0x388);
    if (so) step = *reinterpret_cast<int32_t*>(so + 0x08);
  });
  return step;
}

// The data asset's block for this Shadow's kind and mood, as the game's state object picks it.
const char* block_of(UObject* comp) {
  int type = get<int8_t>(comp, "EnemyType");
  if (type == 2) return "Rare";
  if (get_bool(comp, "bForceUpset")) return "upset";
  switch (get<int32_t>(comp, "AbnormalStateId", -1)) {
    case 2: return "anger";
    case 3: return "Confusion";
    case 4: return "fear";
    case 5: return "upset";
    default: return "Normal";
  }
}

std::vector<Eye> eyes(bool dashing, bool jamming) {
  std::vector<Eye> out;
  for (const shadow::Holder& h : shadow::enemy_holders()) {
    if (!h.actor || !h.comp) continue;
    Eye e;
    e.actor = h.actor;
    e.index = index_of(h.actor);
    bool ok = guarded([&] {
      if (get_bool(h.actor, "bHidden")) { e.skip = true; e.why = "hidden"; return; }
      int type = get<int8_t>(h.comp, "EnemyType");
      if (type >= 3) { e.skip = true; e.why = "not a roaming Shadow"; return; }   // the Reaper, a Gatekeeper, a door
      // EFldEnemyState: a roaming Shadow is Execution (4, its behaviour running; floor 2, 2026-11-19), Alive (2) before
      int state = get<int32_t>(h.comp, "State");
      if ((state != 2 && state != 4) || get_bool(h.comp, "bIsDead") || get_bool(h.comp, "bVanish")) { e.skip = true; e.why = "not roaming"; return; }
      UObject* mark = first_object(h.comp, "CurrentMarkEffectParam");
      e.marked = mark && mark == first_object(h.comp, "ExclamationEffect");
      if (is_a(h.comp, "FldEnemyNormalComp")) e.step = behaviour_step(h.comp);
      // Not searching: any step but wandering. Without a behaviour to read, the mark stands in.
      e.hunting = e.step >= 0 ? e.step != 4 && e.step != 5 : e.marked;
      if (jamming) {
        auto* reaction = field<uint8_t>(h.comp, "SkillReaction");   // FFldEnemySkillReactionParam: bJamming, bPressure
        if (reaction && reaction[0]) { e.skip = true; e.why = "Jamming"; return; }
      }
      UObject* da = get<UObject*>(h.comp, "EnemyData");
      if (!da) { e.skip = true; e.why = "no data"; return; }
      e.block = block_of(h.comp);
      auto* blk = field<uint8_t>(da, e.block);
      if (!blk) { e.skip = true; e.why = "no block"; return; }
      FVector v = world::actor_location(h.actor);
      e.at = Vec3{v.x, v.y, v.z};
      float yaw = world::yaw_of(h.actor);
      auto cone = [&](int off) {
        const float* f = reinterpret_cast<const float*>(blk + off);
        if (f[0] > 0 && f[1] > 0) e.cones.push_back(SightCone{e.at, yaw, f[0], f[1]});
      };
      cone(0x04);                 // NormalSearch
      cone(0x0C);                 // PlayerNearSearch
      if (dashing) cone(0x14);    // PlayerDashSearch
    });
    if (!ok) { e.skip = true; e.why = "unreadable"; }
    out.push_back(std::move(e));
  }
  return out;
}

float reach_of(const Eye& e) {
  float r = 0;
  for (const SightCone& c : e.cones) r = std::max(r, c.range);
  return r;
}

// The Shadow sees this point (the hero's centre there): inside a cone and the line clear.
bool sees(const Eye& e, const Vec3& p) {
  ++g_traces;
  world::Hit h = world::sight_line(FVector{e.at.x, e.at.y, e.at.z}, FVector{p.x, p.y, p.z}, e.actor);
  return !h.hit;
}
bool in_sight(const Eye& e, const Vec3& p) {
  for (const SightCone& c : e.cones) if (core::cone_holds(c, p)) return true;
  return false;
}

void log_prediction(const std::vector<Eye>& all, const std::vector<bool>& seen_now, const Vec3& me) {
  std::map<WeakObj::Key, Watch> next;
  for (size_t i = 0; i < all.size(); ++i) {
    const Eye& e = all[i];
    auto key = WeakObj::of(e.actor).key();
    auto it = g_watch.find(key);
    Watch w = it == g_watch.end() ? Watch{.step = e.step} : it->second;
    if (seen_now[i]) { w.seen_ago = 0; ++w.seen_run; }
    else { w.seen_ago = std::min(w.seen_ago + 1, 1000); w.seen_run = 0; w.alarm_counted = false; }
    float dist = core::dist3(e.at, me);
    // The game noticed him: its behaviour went from wandering to noticing.
    if ((w.step == 4 || w.step == 5) && e.step == 6) {
      // A Shadow that steps (or turns) into sight and notices him in the same frame was never seen unmarked by the
      // mod, which reads the world before the game's frame: the hero inside its sight now, the line clear, agrees.
      const bool same_frame = w.seen_ago > kMatchFrames && in_sight(e, me) && sees(e, me);
      if (w.seen_ago <= kMatchFrames || same_frame) {
        ++g_match;
        log::writef("sight: #{} noticed the hero at {:.1f} m, as the mod said {} ({} block)", e.index, dist / 100.0f,
                    same_frame ? std::string("in the frame it came into sight") : std::format("{} tick(s) before", w.seen_ago), e.block);
      } else {
        ++g_missed;
        log::writef("sight: MISSED #{} noticed the hero at {:.1f} m, the mod saw no sight (last {} ticks ago; {} block, dashing {}, in a cone now {})", e.index,
                    dist / 100.0f, w.seen_ago, e.block, g_dashing, in_sight(e, me));
      }
    }
    if (w.seen_run >= kFalseFrames && !w.alarm_counted && !e.hunting) {
      w.alarm_counted = true;
      ++g_false;
      log::writef("sight: FALSE ALARM #{}: the mod has said seen for {} ticks at {:.1f} m and the game has not noticed ({} block, dashing {})", e.index,
                  w.seen_run, dist / 100.0f, e.block, g_dashing);
    }
    w.step = e.step;
    next[key] = w;
  }
  g_watch.swap(next);
}

}  // namespace

void demo(int which) {
  // 1.2 s: the sound test's own length, not a wait on anything.
  if (which >= 0 && which < 4) audio::hold(kDemoHold, lane_pcm(which), 0.6f * g_gain, lane_spot(which), 1.0f, 1.0f, 0.0f, 1200);
  else if (which == 4) play_bed(g_bed_gain, kDemoHold + 1, 1200);
}

static void tick_body();
void tick() {
  auto t0 = std::chrono::steady_clock::now();
  tick_body();
  if (g_traces > 0) {
    double us = std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - t0).count();
    g_busy_us += us; ++g_busy_ticks;
    g_max_us = std::max(g_max_us, us);
    g_max_traces = std::max(g_max_traces, g_traces);
  }
}

static void tick_body() {
  g_traces = 0;
  g_hidden = false; g_hidden_by = -1;
  for (Lane& l : g_lane) l = Lane{};
  for (float& r : g_room) r = -1;
  if (!settings::on(settings::ShadowSight) || !world::exploring()) { silence(); g_watch.clear(); return; }
  FVector mef;
  if (!world::player_location(mef)) { silence(); return; }
  const Vec3 me{mef.x, mef.y, mef.z};
  const float band = g_band_dev > 0 ? g_band_dev : settings::get(settings::SightBand) * 100.0f;
  UObject* hc = hero_comp();
  FVector vel{};
  g_dashing = false;
  bool jamming = false, unseen = false;
  guarded([&] {
    if (!hc) return;
    unseen = get_bool(hc, "bNotSearchedByEnemies");
    jamming = get_bool(hc, "bJammingSkill");
    bool moving = world::player_velocity(vel) && std::sqrt(vel.x * vel.x + vel.y * vel.y + vel.z * vel.z) >= 0.01f;
    g_dashing = moving && (get_bool(hc, "bEnableDash") || get_bool(hc, "bEnableAssault"));
    // Also by his speed, past halfway from the game's Run to its Dash (SpeedData: Walk, Run, Dash, Assault; 890 and
    // 1180 cm/s): the flags could not be set from the dev game (Shift cannot be injected), so they are unconfirmed.
    const float* speed = field<float>(hc, "SpeedData");
    if (moving && speed && speed[2] > speed[1] && std::hypot(vel.x, vel.y) > (speed[1] + speed[2]) * 0.5f) g_dashing = true;
  });
  std::vector<Eye> all = eyes(g_dashing, jamming);
  if (all.empty()) { silence(); g_shadows.clear(); g_blind.clear(); return; }   // not on a Tartarus floor
  g_blind = unseen ? "not searched by enemies" : party::flag(kReaperBit) ? "the Reaper is on the floor" : "";
  std::vector<bool> seen_now(all.size(), false);
  g_shadows.clear();
  // How far each way the hero could go before a wall: sight past it is out of his reach (Grim Dark's lanes stop at the
  // wall too). One line at his centre's height per way, traced once a tick when a Shadow is near enough to matter.
  float room[4] = {-1, -1, -1, -1};
  std::vector<UObject*> people;
  auto room_of = [&](int d) {
    if (room[d] < 0) {
      FVector v = world::dir_vector(d);
      world::Hit h = world::line(mef, FVector{mef.x + v.x * band, mef.y + v.y * band, mef.z}, "Pawn", &people);
      ++g_traces;
      room[d] = h.hit && !h.start_inside ? h.distance : band;
      g_room[d] = room[d];
    }
    return room[d];
  };
  for (size_t i = 0; i < all.size(); ++i) {
    Eye& e = all[i];
    bool counts = !e.skip && !e.hunting && g_blind.empty();
    float dist = core::dist3(e.at, me);
    bool inside = false, clear = false;
    if (counts && dist <= reach_of(e) + band) {
      inside = in_sight(e, me);
      if (inside) {
        clear = sees(e, me);
        if (clear) seen_now[i] = true;
        else if (!g_hidden) { g_hidden = true; g_hidden_by = e.index; }
      }
      // Each way the player can push: the first point within the band that this Shadow would see.
      for (int d = 0; d < 4; ++d) {
        if (g_lane[d].shadow >= 0 && g_lane[d].dist == 0) continue;
        FVector v = world::dir_vector(d);
        std::vector<std::pair<float, float>> spans;
        const float reach = room_of(d);
        for (const SightCone& c : e.cones) for (auto& s : core::cone_spans(c, me, v.x, v.y, reach)) spans.push_back(s);
        spans = core::merge_spans(std::move(spans));
        int traces = 0;
        float found = -1;
        for (auto [a, b] : spans) {
          float step = std::max(kTraceStep, (b - a) / kMaxTraces);
          for (float s = a; s <= b + 0.01f && traces < kMaxTraces && g_traces < kTickTraces; s += step) {
            if (s == 0 && inside) { if (clear) { found = 0; break; } continue; }   // the hero's own place, traced above
            ++traces;
            if (sees(e, Vec3{me.x + v.x * s, me.y + v.y * s, me.z})) { found = s; break; }
          }
          if (found >= 0 || traces >= kMaxTraces) break;
        }
        if (found >= 0 && (g_lane[d].shadow < 0 || found < g_lane[d].dist)) g_lane[d] = Lane{found, e.index};
      }
    }
    std::string cones;
    for (const SightCone& c : e.cones) cones += std::format(" {:.0f}/{:.0f}", c.range, c.angle);
    g_shadows += std::format("  step {} #{} {:.1f} m at ({:.0f}, {:.0f}, {:.0f}) yaw {:.0f}, {} block, cones{}{}{}{}{}{}\n", e.step, e.index, dist / 100.0f, e.at.x, e.at.y, e.at.z,
                             e.cones.empty() ? 0.0f : e.cones[0].yaw, e.block, cones, e.hunting ? ", not searching" : "",
                             e.skip ? std::string(", skipped: ") + e.why : std::string(), inside ? ", hero inside its sight" : "",
                             inside ? (clear ? ", line clear (SEEN)" : ", line blocked (hidden)") : "", counts ? "" : ", left out");
  }
  log_prediction(all, seen_now, me);
  for (int d = 0; d < 4; ++d) {
    float v = g_lane[d].shadow >= 0 ? core::edge_level(g_lane[d].dist, band) : 0.0f;
    if (v <= 0) { audio::release_hold(kLaneHold + d); continue; }
    audio::hold(kLaneHold + d, lane_pcm(d), v * g_gain, lane_spot(d), 1.0f, 1.0f, 0.0f);
  }
  if (g_hidden) play_bed(g_bed_gain);
  else { audio::release_hold(kBedHold); audio::release_hold(kBedHold + 1); }
  // A change of the hidden state, logged (to compare with what was heard).
  static bool was_hidden = false;
  if (g_hidden != was_hidden) {
    was_hidden = g_hidden;
    log::writef("sight: {}", g_hidden ? std::format("hidden from #{} by a wall", g_hidden_by) : std::string("no longer hidden"));
  }
}

void install() {
  // Decoded now, not on the first sound: six files took ~10 ms in the field's tick.
  for (int d = 0; d < 4; ++d) lane_pcm(d);
  bed_pcm(0);
  dev::route("/sight", [](const dev::Request& r, int&) {
    if (dev::has(r, "gain")) g_gain = std::clamp((float)dev::arg_num(r, "gain", g_gain), 0.0f, 1.0f);
    if (dev::has(r, "bed")) g_bed_gain = std::clamp((float)dev::arg_num(r, "bed", g_bed_gain), 0.0f, 1.0f);
    if (dev::has(r, "tone")) g_bed_tone = std::clamp((float)dev::arg_num(r, "tone", g_bed_tone), 0.0f, 1.0f);
    if (dev::has(r, "spread")) g_bed_spread = std::clamp((float)dev::arg_num(r, "spread", g_bed_spread), 0.0f, 1.0f);
    if (dev::has(r, "band")) g_band_dev = std::max(0.0f, (float)dev::arg_num(r, "band", g_band_dev));
    if (dev::has(r, "reset")) { g_match = g_missed = g_false = 0; g_busy_us = g_max_us = 0; g_busy_ticks = g_max_traces = 0; }
    if (dev::has(r, "demo")) { int w = (int)dev::arg_num(r, "demo", 0); return dev::on_game([w] { demo(w); return std::string("ok\n"); }); }
    return dev::on_game([] {
      static const char* dir[4] = {"ahead", "right", "behind", "left"};
      std::string s = std::format("on={} band={:.0f} cm dashing={} blind={} hidden={}{} traces={} gain={:.2f} bed={:.2f} tone={:.2f} spread={:.2f}\n",
                                  settings::on(settings::ShadowSight), g_band_dev > 0 ? g_band_dev : settings::get(settings::SightBand) * 100.0f, g_dashing,
                                  g_blind.empty() ? "-" : g_blind, g_hidden, g_hidden ? std::format(" (#{})", g_hidden_by) : "", g_traces, g_gain, g_bed_gain,
                                  g_bed_tone, g_bed_spread);
      for (int d = 0; d < 4; ++d)
        s += (g_lane[d].shadow >= 0 ? std::format("  {}: edge at {:.0f} cm (#{})", dir[d], g_lane[d].dist, g_lane[d].shadow) : std::format("  {}: none", dir[d])) +
             (g_room[d] >= 0 ? std::format(", room {:.0f} cm\n", g_room[d]) : std::string("\n"));
      s += std::format("prediction vs the game's mark: {} matched, {} missed, {} false alarms\n", g_match, g_missed, g_false);
      s += std::format("cost with a Shadow near: {:.1f} us a tick on average over {} ticks, worst {:.0f} us, most traces {}\n",
                       g_busy_ticks ? g_busy_us / g_busy_ticks : 0.0, g_busy_ticks, g_max_us, g_max_traces);
      return s + g_shadows;
    });
  }, "?gain=&bed=&tone=&spread=&band=cm&reset=1&demo=0..4 Shadow sight: each way's edge, hidden, the prediction's score");
}
}  // namespace p3a::sight
