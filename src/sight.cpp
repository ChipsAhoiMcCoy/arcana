// After Grim Dark's harmful ground (GD Access, by Austin Hicks): its sounds (assets/audio/sight, zlib, see LICENSES/)
// and its idea, a sound for ground that hurts and a bed while you stand in it, put to a Shadow's sight.
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
//
// The sound: each nearby wandering Shadow's sight is a zone on the ground, its cones cut by the walls that block its
// view, and the zone sizzles from its point nearest the hero (held, placed in the world, heard through the HRTF like
// the growl) for as long as that point is within the Shadow sight range: louder and higher by an even step for every
// metre nearer, loudest at the edge (it was a quiet floor rising only over the last two metres, and the player barely
// heard it under the growl, 2026-11-19). The nearest few zones sound at once; the growl of a Shadow whose zone sounds
// is lowered (shadow.cpp). The point is the cones' own nearest
// point when the Shadow sees it; when a wall hides that point, a fan of rays around the hero's bearing is traced to
// find where the view really ends.
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
using core::SightRay;
using core::Vec3;
using world::FVector;

constexpr int kZoneHold = 20;    // audio::hold ids 20..22: the nearest zones
constexpr int kZones = 3;
constexpr int kBedHold = 24;     // 24 left, 25 right: hidden
constexpr int kDemoHold = 26;    // 26 a zone, 27 and 28 the hum
constexpr uint32_t kReaperBit = 0x20000582;   // BIT 1410: set as the Reaper appears on the floor
constexpr float kFanStep = 5.0f;              // degrees between the fan's rays
constexpr int kFanHalf = 6;                   // rays to each side of the hero's bearing (60 degrees in all)
constexpr int kTickTraces = 40;               // traces in all, a tick (past it, rays count as unblocked)
constexpr float kBehindRate = 0.84f;          // "Lower pitch behind you", as the sonar

// knobs (dev route /sight)
float g_gain = 1.0f;        // a zone's loudness at its edge
float g_bed_gain = 0.45f;   // the hidden hum's (Grim Dark's 0.45)
float g_bed_tone = 0.25f;   // its brightness: muffled (audio::hold's tone)
float g_bed_spread = 0.5f;  // its two halves, left and right
float g_range_dev = 0;      // cm; 0: the setting

bool g_hidden = false;
int g_hidden_by = -1;
bool g_dashing = false;
std::string g_blind;          // why no Shadow can see the hero now, or empty
int g_traces = 0;
// The tick's cost while a Shadow is near enough to trace for (dev: /sight; ?reset=1 starts over).
double g_busy_us = 0, g_max_us = 0;
int g_busy_ticks = 0, g_max_traces = 0;
std::string g_shadows;        // one line per Shadow considered

// The mod's prediction against the game's noticing, per Shadow.
struct Watch { int seen_ago = 1000; int seen_run = 0; bool alarm_counted = false; int step = -1; };
std::map<WeakObj::Key, Watch> g_watch;
int g_match = 0, g_missed = 0, g_false = 0;
constexpr int kMatchFrames = 3;    // the game notices within this many ticks of the mod saying "seen"
constexpr int kFalseFrames = 10;   // "seen" this many ticks running and no noticing: the mod was wrong

// What the player hears of each Shadow's zone, for the log: when it starts and stops, how close the edge came.
struct Heard { bool on = false; float closest = 1e9f; float level_at = 0; int meters = 1000; bool kept = false; };
std::map<WeakObj::Key, Heard> g_heard;
std::map<WeakObj::Key, int> g_slot;   // the zone's hold slot (0..kZones-1), kept while it sounds
std::vector<int> g_sounding;          // the object indexes of the Shadows whose zones sound now

std::string sound_dir() { return audio::module_dir() + "assets\\audio\\sight\\"; }
audio::Pcm load(const std::string& file) {
  auto v = std::make_shared<std::vector<float>>();
  if (!audio::decode_mono(sound_dir() + file, *v)) log::writef("sight: cannot load {}", file);
  return v;
}
const audio::Pcm& zone_pcm() {
  static audio::Pcm p = load("zone.wav");
  return p;
}
const audio::Pcm& bed_pcm(int side) {
  static audio::Pcm p[2] = {load("hidden_left.wav"), load("hidden_right.wav")};
  return p[side];
}
// A direction from the player (no place in the world: it turns with him).
audio::Spot toward(float right, float ahead, float dist_m = 1.0f) {
  audio::Spot s;
  s.right = right; s.ahead = ahead; s.dist_m = dist_m; s.pan = right;
  return s;
}
void play_bed(float vol, int id = kBedHold, int hold_ms = 250) {
  float side = g_bed_spread, front = std::sqrt(1.0f - side * side);
  audio::hold(id, bed_pcm(0), vol, toward(-side, front), 1.0f, g_bed_tone, 0.0f, hold_ms);
  audio::hold(id + 1, bed_pcm(1), vol, toward(side, front), 1.0f, g_bed_tone, 0.0f, hold_ms);
}
void silence() {
  for (int i = 0; i < kZones; ++i) audio::release_hold(kZoneHold + i);
  audio::release_hold(kBedHold);
  audio::release_hold(kBedHold + 1);
  g_slot.clear();
  g_sounding.clear();
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

// The line from the Shadow's centre to a point is clear (the game's sight trace).
bool sees(const Eye& e, const Vec3& p) {
  ++g_traces;
  world::Hit h = world::sight_line(FVector{e.at.x, e.at.y, e.at.z}, FVector{p.x, p.y, p.z}, e.actor);
  return !h.hit;
}
bool in_sight(const Eye& e, const Vec3& p) {
  for (const SightCone& c : e.cones) if (core::cone_holds(c, p)) return true;
  return false;
}

// Where a Shadow's zone is nearest the hero, walls counted. `how`: "clear" (the cones' own nearest point, seen),
// "walls" (a fan of traced rays), "" (none).
struct Zone { Vec3 at; float dist = 0; const char* how = ""; };
bool zone_of(const Eye& e, const Vec3& me, bool hero_inside, Zone& z) {
  // The cones' own nearest point; seen from the Shadow, that is the edge.
  Vec3 best{};
  float bd = 1e30f;
  for (const SightCone& c : e.cones) {
    Vec3 q; float d;
    if (core::sector_nearest(c, me, q, d) && d < bd) { bd = d; best = q; }
  }
  if (bd >= 1e29f) return false;
  if (!hero_inside && sees(e, best)) { z = Zone{best, bd, "clear"}; return true; }
  // A wall hides it (or the hero stands inside the cones, hidden): the view's real end, ray by ray, on a fan around
  // the hero's bearing, or around the nearest edge of the cones when he is outside their angle.
  float phi = std::atan2(me.y - e.at.y, me.x - e.at.x) * 180.0f / core::kPi;
  float centre = phi;
  if (core::reach_at(e.cones, me.z, phi) <= 0) {
    float bestoff = 1e9f;
    for (const SightCone& c : e.cones)
      for (float side : {-0.5f, 0.5f}) {
        float edge = c.yaw + side * c.angle - side * 2.0f;   // just inside the edge
        float off = std::fabs(std::remainder(edge - phi, 360.0f));
        if (off < bestoff) { bestoff = off; centre = edge; }
      }
  }
  std::vector<float> offs;
  for (int k = -kFanHalf; k <= kFanHalf; ++k) offs.push_back(k * kFanStep);
  for (const SightCone& c : e.cones)   // the cones' sides inside the fan, so a side is where the view ends
    for (float side : {-0.5f, 0.5f}) {
      float off = std::remainder(c.yaw + side * c.angle - centre, 360.0f);
      if (std::fabs(off) < kFanHalf * kFanStep) { offs.push_back(off - 0.3f); offs.push_back(off + 0.3f); }
    }
  std::sort(offs.begin(), offs.end());
  std::vector<SightRay> rays;
  for (float off : offs) {
    float theta = centre + off;
    float reach = core::reach_at(e.cones, me.z, theta);
    float len = reach;
    if (reach > 0 && g_traces < kTickTraces) {
      float a = theta * core::kPi / 180.0f;
      FVector to{e.at.x + std::cos(a) * reach, e.at.y + std::sin(a) * reach, me.z};
      ++g_traces;
      world::Hit h = world::sight_line(FVector{e.at.x, e.at.y, e.at.z}, to, e.actor);
      if (h.hit) {
        float full = std::sqrt(reach * reach + (me.z - e.at.z) * (me.z - e.at.z));
        len = full > 0 ? reach * std::clamp(h.distance / full, 0.0f, 1.0f) : 0.0f;
      }
    }
    rays.push_back(SightRay{theta, len});
  }
  Vec3 q; float d;
  if (!core::fan_nearest(e.at, rays, me, q, d)) return false;
  z = Zone{q, d, "walls"};
  return true;
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

// What the player hears of each zone, logged: it starts, its edge comes within each whole metre, it stops (with the
// closest it came and how loud it was then).
void log_heard(int index, const WeakObj::Key& key, bool on, float dist, float level) {
  Heard& h = g_heard[key];
  h.kept = true;
  if (on && !h.on) {
    h = Heard{true, dist, level, (int)std::floor(dist / 100.0f), true};
    log::writef("sight: #{} zone sounds, its edge {:.1f} m away (volume {:.2f}, dashing {})", index, dist / 100.0f, level, g_dashing);
    return;
  }
  if (!on) {
    if (h.on) log::writef("sight: #{} zone quiet; its edge came within {:.1f} m (volume {:.2f})", index, h.closest / 100.0f, h.level_at);
    h.on = false;
    return;
  }
  if (dist < h.closest) { h.closest = dist; h.level_at = level; }
  int m = (int)std::floor(dist / 100.0f);
  if (m < h.meters) {
    h.meters = m;
    log::writef("sight: #{} edge within {} m (volume {:.2f}{})", index, m + 1, level, g_dashing ? ", dashing" : "");
  }
}

}  // namespace

bool sounding(int index) { return std::find(g_sounding.begin(), g_sounding.end(), index) != g_sounding.end(); }

void demo(int which) {
  // 1.2 s: the sound test's own length, not a wait on anything.
  if (which == 0) audio::hold(kDemoHold, zone_pcm(), core::zone_level(500, 1000) * g_gain, toward(0, 1, 5), core::zone_rate(500, 1000), 1.0f, 0.0f, 1200);
  else if (which == 1) audio::hold(kDemoHold, zone_pcm(), g_gain, toward(0, 1, 1), core::zone_rate(0, 1000), 1.0f, 0.0f, 1200);
  else if (which == 2) play_bed(g_bed_gain, kDemoHold + 1, 1200);
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
  auto quiet_all = [] {
    silence();
    for (auto& [key, h] : g_heard) if (h.on) log::writef("sight: #{} zone quiet; its edge came within {:.1f} m (volume {:.2f})", std::get<0>(key), h.closest / 100.0f, h.level_at);
    g_heard.clear();
  };
  if (!settings::on(settings::ShadowSight) || !world::exploring()) { quiet_all(); g_watch.clear(); return; }
  FVector mef;
  if (!world::player_location(mef)) { quiet_all(); return; }
  const Vec3 me{mef.x, mef.y, mef.z};
  const float range = g_range_dev > 0 ? g_range_dev : settings::get(settings::SightRange) * 100.0f;
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
  if (all.empty()) { quiet_all(); g_shadows.clear(); g_blind.clear(); return; }   // not on a Tartarus floor
  g_blind = unseen ? "not searched by enemies" : party::flag(kReaperBit) ? "the Reaper is on the floor" : "";
  std::vector<bool> seen_now(all.size(), false);
  g_shadows.clear();
  struct Heard1 { WeakObj::Key key; int index; Zone z; float level, rate; };
  std::vector<Heard1> zones;
  // Nearest Shadows first: the trace budget goes to them.
  std::vector<size_t> order(all.size());
  for (size_t i = 0; i < order.size(); ++i) order[i] = i;
  std::sort(order.begin(), order.end(), [&](size_t a, size_t b) { return core::dist3(all[a].at, me) < core::dist3(all[b].at, me); });
  for (size_t i : order) {
    Eye& e = all[i];
    bool counts = !e.skip && !e.hunting && g_blind.empty();
    float dist = core::dist3(e.at, me);
    bool inside = false, clear = false;
    Zone z;
    bool has_zone = false;
    if (counts && dist <= reach_of(e) + range) {
      inside = in_sight(e, me);
      if (inside) {
        clear = sees(e, me);
        if (clear) seen_now[i] = true;
        else if (!g_hidden) { g_hidden = true; g_hidden_by = e.index; }
      }
      if (inside && clear) { z = Zone{me, 0, "seen"}; has_zone = true; }
      else has_zone = zone_of(e, me, inside, z);
      if (has_zone && z.dist < range) zones.push_back(Heard1{WeakObj::of(e.actor).key(), e.index, z, core::zone_level(z.dist, range), core::zone_rate(z.dist, range)});
    }
    std::string cones;
    for (const SightCone& c : e.cones) cones += std::format(" {:.0f}/{:.0f}", c.range, c.angle);
    g_shadows += std::format("  step {} #{} {:.1f} m at ({:.0f}, {:.0f}, {:.0f}) yaw {:.0f}, {} block, cones{}{}{}{}{}{}{}\n", e.step, e.index, dist / 100.0f, e.at.x,
                             e.at.y, e.at.z, e.cones.empty() ? 0.0f : e.cones[0].yaw, e.block, cones, e.hunting ? ", not searching" : "",
                             e.skip ? std::string(", skipped: ") + e.why : std::string(), inside ? ", hero inside its sight" : "",
                             inside ? (clear ? ", line clear (SEEN)" : ", line blocked (hidden)") : "", counts ? "" : ", left out",
                             has_zone ? std::format(", edge {:.0f} cm ({}) at ({:.0f}, {:.0f})", z.dist, z.how, z.at.x, z.at.y) : std::string());
  }
  log_prediction(all, seen_now, me);
  // The nearest few zones sound, each in a slot it keeps while it sounds.
  std::sort(zones.begin(), zones.end(), [](const Heard1& a, const Heard1& b) { return a.z.dist < b.z.dist; });
  if ((int)zones.size() > kZones) zones.resize(kZones);
  std::map<WeakObj::Key, int> slots;
  bool used[kZones] = {};
  for (const Heard1& h : zones)
    if (auto it = g_slot.find(h.key); it != g_slot.end()) { slots[h.key] = it->second; used[it->second] = true; }
  for (const Heard1& h : zones)
    if (!slots.count(h.key))
      for (int s = 0; s < kZones; ++s) if (!used[s]) { slots[h.key] = s; used[s] = true; break; }
  for (int s = 0; s < kZones; ++s) if (!used[s]) audio::release_hold(kZoneHold + s);
  for (const Heard1& h : zones) {
    audio::Spot at = world::spot(mef, FVector{h.z.at.x, h.z.at.y, me.z});
    float rate = h.rate * (at.ahead < -0.2f && settings::on(settings::BehindPitch) ? kBehindRate : 1.0f);
    audio::hold(kZoneHold + slots[h.key], zone_pcm(), h.level * g_gain, at, rate, 1.0f, 0.0f);
  }
  g_slot.swap(slots);
  g_sounding.clear();
  for (const Heard1& h : zones) g_sounding.push_back(h.index);
  // The log: each zone as it starts, nears and stops.
  for (auto& [key, h] : g_heard) h.kept = false;
  for (const Heard1& h : zones) log_heard(h.index, h.key, true, h.z.dist, h.level);
  for (auto it = g_heard.begin(); it != g_heard.end();) {
    if (!it->second.kept) {
      if (it->second.on) log_heard(std::get<0>(it->first), it->first, false, 0, 0);
      it = g_heard.erase(it);
    } else ++it;
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
  // Decoded now, not on the first sound: the files took ~10 ms in the field's tick.
  zone_pcm();
  bed_pcm(0);
  dev::route("/sight", [](const dev::Request& r, int&) {
    if (dev::has(r, "gain")) g_gain = std::clamp((float)dev::arg_num(r, "gain", g_gain), 0.0f, 1.0f);
    if (dev::has(r, "bed")) g_bed_gain = std::clamp((float)dev::arg_num(r, "bed", g_bed_gain), 0.0f, 1.0f);
    if (dev::has(r, "tone")) g_bed_tone = std::clamp((float)dev::arg_num(r, "tone", g_bed_tone), 0.0f, 1.0f);
    if (dev::has(r, "spread")) g_bed_spread = std::clamp((float)dev::arg_num(r, "spread", g_bed_spread), 0.0f, 1.0f);
    if (dev::has(r, "range")) g_range_dev = std::max(0.0f, (float)dev::arg_num(r, "range", g_range_dev));
    if (dev::has(r, "reset")) { g_match = g_missed = g_false = 0; g_busy_us = g_max_us = 0; g_busy_ticks = g_max_traces = 0; }
    if (dev::has(r, "demo")) { int w = (int)dev::arg_num(r, "demo", 0); return dev::on_game([w] { demo(w); return std::string("ok\n"); }); }
    return dev::on_game([] {
      std::string s = std::format("on={} range={:.0f} cm dashing={} blind={} hidden={}{} traces={} gain={:.2f} bed={:.2f} tone={:.2f} spread={:.2f}\n",
                                  settings::on(settings::ShadowSight), g_range_dev > 0 ? g_range_dev : settings::get(settings::SightRange) * 100.0f, g_dashing,
                                  g_blind.empty() ? "-" : g_blind, g_hidden, g_hidden ? std::format(" (#{})", g_hidden_by) : "", g_traces, g_gain, g_bed_gain,
                                  g_bed_tone, g_bed_spread);
      for (auto& [key, slot] : g_slot) {
        auto h = g_heard.find(key);
        s += std::format("  sounding: #{} in slot {}, closest {:.0f} cm\n", std::get<0>(key), slot, h != g_heard.end() ? h->second.closest : -1.0f);
      }
      s += std::format("prediction vs the game's noticing: {} matched, {} missed, {} false alarms\n", g_match, g_missed, g_false);
      s += std::format("cost with a Shadow near: {:.1f} us a tick on average over {} ticks, worst {:.0f} us, most traces {}\n",
                       g_busy_ticks ? g_busy_us / g_busy_ticks : 0.0, g_busy_ticks, g_max_us, g_max_traces);
      return s + g_shadows;
    });
  }, "?gain=&bed=&tone=&spread=&range=cm&reset=1&demo=0..2 Shadow sight: each Shadow's zone edge, hidden, the prediction's score");
}
}  // namespace p3a::sight
