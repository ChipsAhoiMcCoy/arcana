// Shadows on a Tartarus floor. What the game holds:
//  - AEnemySymbolBaseCore: the roaming Shadow's actor (hidden while parked or defeated).
//  - AFldEnemyManager.Enemies: one FFldEnemyHolder { Actor, EnemyComp } per Shadow (Actor is that same actor). A
//    UFldEnemyNormalComp has CurrentMarkEffectParam, the mark over its head (its Asset is ExclamationEffect's or
//    QuestionEffect's), and TrackingTarget (an FFldPlayerHolder whose Pawn is whom it is after). Watched on floor 2
//    (2026-11-10): at rest no mark and no target; the exclamation mark came up as each Shadow noticed the hero (at
//    3.4 m and 7.3 m, running at them), and the target was the hero while it chased. Losing him (the question mark,
//    the target let go) is UNTESTED.
//  - UFldPlayerDungeonComp.AttackArea: an AFldCharArea whose box (AreaComp) rides in front of the hero. The strike's
//    hit test is that box's overlapping actors (FUN_1411257b0), and the box's profile, FldPlayerAtk, overlaps the Enemy
//    channel alone (DefaultEngine.ini): a Shadow's body (FieldEnemy, its capsule, 1 m round and 2 m tall) and a
//    breakable's Box. So the strike connects the moment any of the Shadow's body touches the box. Measured on floor 5
//    (2026-11-10): centre 84 cm ahead of the hero, extent 90 x 60 x 50, so with the body it reaches 2.7 m ahead and
//    1.6 m to each side. The box is read live, so whatever sizes it is followed. With a long-range strike the target
//    is LockOnActor instead (UNTESTED; see long_range).
//  - UFldEnemyComp.AttackArea: the Shadow's own AFldCharArea, its box 2 x 3.8 m from 1.3 to 3.3 m in front of it
//    (BP_FldEmNormalBase), overlapping the Player channel alone: where it can go for the hero. Only logged.
//  - AFldOperator.EncountType: how the next battle starts (EFldOperatorEncountType: 1 the strike with the Shadow facing
//    the hero, 2 from behind it, 3 and 4 the same with Ambush, 5 the Shadow reached him first), set once per encounter
//    with the Shadow in EncountEnemy (FUN_1411db770). Logged, beside whether the ring had sounded for that Shadow.
#include "shadow.h"
#include "audio.h"
#include "core/boxes.h"
#include "core/sonar_cues.h"
#include "core/strings.h"
#include "devserver.h"
#include "flow.h"
#include "hooks.h"
#include "log.h"
#include "poi.h"
#include "seh.h"
#include "settings.h"
#include "speech.h"
#include "watch.h"
#include "world.h"
#include <windows.h>
#include <cmath>
#include <format>
#include <map>
#include <vector>

namespace p3a::shadow {
namespace {
using namespace ue;
using core::angle_diff;
using core::Box;
using core::boxes_meet;
using core::kPi;
using core::SignalCue;
using world::FVector;
using world::read_box;
using world::yaw_of;

// cm: the growl. 15 m at first, and only for a Shadow within 3 m of the hero's height: it was not heard until it was
// about to strike (the user, 2026-11-10). A Tartarus floor has raised and sunken parts, so height filters nothing now.
constexpr float kPulseRange = 3000.0f;
constexpr int kDroneId = 1;               // audio::hold's id for the nearest Shadow's held snarl
constexpr int kDemoId = 2;                // and the sound test's
// Past this far off a Shadow's front the hero is behind it: the game's own test for a strike's advantage
// (FUN_14115f090, 90 degrees). It was 110 here, a guess, until the game's was read (2026-11-14).
constexpr float kBackTurnedDeg = 90.0f;
constexpr float kMindRange = 4000.0f;    // cm: how far off a Shadow's noticing is told
constexpr double kReachS = 0.150;        // the ring's rhythm while in reach (the ring itself lasts 0.09 s)

// What a Shadow's component shows this frame: the mark over its head, and whether it holds the hero as its target.
enum class Mark { None, Exclamation, Question };
struct Raw { Mark mark = Mark::None; bool tracking = false; };
struct Seen { UObject* actor; FVector at; float dist; Raw raw; UObject* comp = nullptr; };

std::vector<UObject*> live(std::string_view cls) { return watch::all(watch::want(cls, true)); }
float flat(const FVector& a, const FVector& b) { return std::hypot(a.x - b.x, a.y - b.y); }

// A struct property's first member, an object pointer (TrackingTarget.Pawn, an effect param's Asset).
UObject* first_object(UObject* o, const char* prop) {
  UObject** p = field<UObject*>(o, prop);
  return p ? *p : nullptr;
}
Raw raw_of(UObject* comp) {
  Raw r;
  if (!comp || !is_a(comp, "FldEnemyNormalComp")) return r;   // a floor's guardian has no such state
  UObject* mark = first_object(comp, "CurrentMarkEffectParam");
  if (mark && mark == first_object(comp, "ExclamationEffect")) r.mark = Mark::Exclamation;
  else if (mark && mark == first_object(comp, "QuestionEffect")) r.mark = Mark::Question;
  r.tracking = first_object(comp, "TrackingTarget") != nullptr;
  return r;
}

// The enemy manager's entries that have both an actor and a component.
std::vector<Holder> holders() {
  std::vector<Holder> out;
  for (const Holder& h : enemy_holders()) if (h.actor && h.comp) out.push_back(h);
  return out;
}

// The visible Shadows near the hero's floor, each with what it knows of him.
std::vector<Seen> look(const FVector& me) {
  std::vector<Seen> out;
  for (UObject* a : live("EnemySymbolBaseCore")) {
    if (get_bool(a, "bHidden")) continue;
    FVector v{};
    if (!guarded([&] { v = world::actor_location(a); })) continue;
    out.push_back({a, v, std::hypot(flat(v, me), v.z - me.z), Raw{}});
  }
  if (out.empty()) return out;
  // A holder's Actor is the Shadow's own actor (floor 5's guardian, 2026-11-10).
  for (const Holder& h : holders())
    for (Seen& s : out)
      if (s.actor == h.actor) { s.comp = h.comp; guarded([&] { s.raw = raw_of(h.comp); }); break; }
  return out;
}

// ---- the strike's reach ----
UObject* dungeon_comp() {
  static const int id = watch::want("FldPlayerDungeonComp");
  return watch::get(id);
}
bool strike_box(UObject* dc, Box& b) {
  UObject* area = dc ? get<UObject*>(dc, "AttackArea") : nullptr;
  return read_box(area ? get<UObject*>(area, "AreaComp") : nullptr, b);
}
// The strike goes to a locked-on target, not the box. IsUsingLongRangeAttack alone does not say so: the swing's start
// (FUN_141124420) sets it for the standing, walking and running swings too, and takes the long-range way only with a
// LockOnActor (and, it seems, only in Episode Aigis). Read alone, it stood the ring and the strike assist down on every
// ordinary swing (the user's log, 2026-11-15: "no strike box to aim with", the ring gone as the swing began).
bool long_range(UObject* dc) {
  return dc && get_bool(dc, "IsUsingLongRangeAttack") && get<UObject*>(dc, "LockOnActor") != nullptr;
}
// A Shadow's body as the box meets it: its capsule (radius, half height), else a slim guess.
void body_of(UObject* shadow, float& radius, float& half_height) {
  radius = 30.0f; half_height = 60.0f;
  world::capsule_of(shadow, radius, half_height);
}
// The body touches the box: the game's own test, the whole body counted. A roaming Shadow's capsule is 1 m in radius
// (floor 2, 2026-11-10). Six tenths of it were counted once, for a ring well inside the reach; it then began 40 cm
// short of where the strike connects, and the user wants it the moment the strike would land (2026-11-14).
bool box_holds(const Box& b, const FVector& p, float radius, float half_height) {
  return core::box_meets_body(b, world::vec3(p), radius, half_height);
}
// The strike would connect with this Shadow now. `known` false: the game's hit area could not be read. With strike
// assist on, a swing turns the hero to a Shadow it would reach on any side, so the reach is the box turned round him
// to face the Shadow, the assist's own test: the ring sounds for a Shadow closing in from behind too (the user's
// call, 2026-11-19: one reached him from behind with no ring until his second swing had turned him).
bool in_reach(UObject* shadow, const FVector& at, const FVector& me, bool& known) {
  UObject* dc = dungeon_comp();
  known = false;
  if (!dc) return false;
  if (long_range(dc)) { known = true; return get<UObject*>(dc, "LockOnActor") == shadow; }
  Box b;
  if (!strike_box(dc, b)) return false;
  known = true;
  float r, hh;
  body_of(shadow, r, hh);
  if (box_holds(b, at, r, hh)) return true;
  if (!settings::on(settings::StrikeAssist)) return false;
  float yaw = std::atan2(at.y - me.y, at.x - me.x) * 180.0f / kPi;
  return core::box_meets_body(core::turned_about(b, world::vec3(me), yaw), world::vec3(at), r, hh);
}

// A breakable thing (Tartarus' Shadow remains) the strike would break now: the game's hit test takes them from the
// same box as the Shadows (the actors overlapping AttackArea's AreaComp). That box collides with nothing between
// swings (CollisionEnabled NoCollision at rest, seen in the player's game 2026-11-10: the engine's overlap answered
// false beside a breakable), so the two boxes are compared here: the strike's and the breakable's own Box.
// The strike's box meets this breakable's Box: as the hero faces now, or (`turned`) with the box turned round him to
// face it, as strike assist turns him on a swing. `yaw` is that facing (toward its Box's middle).
bool breakable_meets(const Box& strike, UObject* a, const FVector& me, bool turned, float& yaw) {
  Box body;
  if (!read_box(get<UObject*>(a, "Box"), body)) return false;
  yaw = std::atan2(body.center.y - me.y, body.center.x - me.x) * 180.0f / kPi;
  if (boxes_meet(strike, body)) return true;
  return turned && boxes_meet(core::turned_about(strike, world::vec3(me), yaw), body);
}
// The nearest breakable the strike reaches (turned to it with strike assist on, like a Shadow: in_reach).
UObject* breakable_reached(const FVector& me, FVector& at, float& yaw) {
  UObject* dc = dungeon_comp();
  Box strike;
  if (!dc || long_range(dc) || !strike_box(dc, strike)) return nullptr;
  const bool turned = settings::on(settings::StrikeAssist);
  UObject* found = nullptr;
  float best = 600.0f;   // cm: nothing farther is in the box
  guarded([&] {
    for (UObject* a : live("FldDungeonObjectActor")) {
      FVector v = world::actor_location(a);
      float d = std::hypot(flat(v, me), v.z - me.z);
      float y = 0.0f;
      if (d >= best || !poi::breakable(a)) continue;
      if (breakable_meets(strike, a, me, turned, y)) { best = d; found = a; at = v; yaw = y; }
    }
  });
  return found;
}
bool breakable_in_reach(const FVector& me, FVector& at) {
  float yaw = 0.0f, best = 0.0f;
  UObject* found = breakable_reached(me, at, yaw);
  if (found) best = std::hypot(flat(at, me), at.z - me.z);
  static WeakObj logged;
  if (WeakObj w = WeakObj::of(found); found && !(w == logged)) {
    logged = w;
    log::writef("shadow: breakable #{} in the strike's reach at {:.1f} m", w.index, best / 100.0f);
  }
  return found != nullptr;
}

// Within 4 m the nearest Shadow's heading is spoken ("back turned" / "facing you"): each of the two lines at most
// once per approach, however often the Shadow turns meanwhile. An approach ends when that Shadow is more than 6 m
// off, or when another Shadow becomes the close one. In reach of the strike (any side with strike assist) a blade's ring repeats; from behind it
// (the battle then starts with the advantage) two rising ticks instead: the ring follows its facing as it is now.
// Returns the ring's cue while the Shadow is in reach, else -1.
int close_cues(const Seen& s, const FVector& me) {
  static WeakObj told;                 // the Shadow this approach is to
  static bool said[2] = {false, false};   // "facing you", "back turned": said on this approach
  float to_me = std::atan2(me.y - s.at.y, me.x - s.at.x) * 180.0f / kPi;
  bool back_turned = angle_diff(yaw_of(s.actor), to_me) > kBackTurnedDeg;   // the hero is outside its front
  WeakObj w = WeakObj::of(s.actor);
  if (s.dist < 400.0f) {
    if (!(w == told)) { told = w; said[0] = said[1] = false; }
    int st = back_turned ? 1 : 0;
    if (!said[st]) {
      said[st] = true;
      // A Rare Shadow, a Strong one or the Reaper is named as the list names it: "Shadow close" for the Reaper hid
      // what was on the hero (2026-11-24, Adamah 232, right after Fuuka's warning).
      std::string kind = poi::shadow_name(s.actor, s.comp);
      if (kind == strings::kPoiShadow.c_str())
        speech::speak(back_turned ? strings::kShadowBackTurned.c_str() : strings::kShadowFacingYou.c_str(), false);
      else
        speech::speak(strings::fmt(back_turned ? strings::kKindBackTurnedFmt : strings::kKindFacingYouFmt, kind), false);
    }
  } else if (s.dist > 600.0f && w.index == told.index) {
    said[0] = said[1] = false;
  }
  if (s.dist > 800.0f) return -1;
  bool known = false;
  bool reach = in_reach(s.actor, s.at, me, known);
  if (!known) {
    // No hit area to read: the old estimate, close behind it and facing it.
    UObject* hero = world::player();
    float to_shadow = std::atan2(s.at.y - me.y, s.at.x - me.x) * 180.0f / kPi;
    reach = hero && back_turned && s.dist < 220.0f && angle_diff(yaw_of(hero), to_shadow) < 45.0f;
  }
  return !reach ? -1 : (int)(back_turned ? SignalCue::Ambush : SignalCue::Reach);
}

// What each Shadow knows of the hero, followed from the marks the game shows over it: the exclamation mark is the
// moment it notices him (the alarm), and it hunts him from then until its question mark (it lost him) or until it
// lets go of him as its target (the falling notes). The target alone starts nothing: only the mark says "noticed".
// Every Shadow on the floor is followed for as long as its actor is there and shown, however far off it is, so one
// that hunts the hero out of earshot and back still reads as hunting; the two cues sound only within kMindRange.
struct Mind { bool hunting = false, tracked = false; Mark last = Mark::None; };
std::map<WeakObj::Key, Mind> g_minds;

// ---- a Rare Shadow's flight ----
// A Rare Shadow (EFldEnemyType 2) never hunts the hero: its exclamation mark starts its flight. Its behaviour
// (FUN_14111c670; the state object at FldEnemyNormalComp +0x388, its step at +0x08, as sight.cpp reads it): 4 and 5 it
// wanders, 6 it has noticed him (DiscoverWaitTime), 7 it flees (FUN_141109a20: EscapeSpeed, for EscapeTime, 15 s, or
// until it loses him), 9 it vanishes (its actor hidden), 10 it waits to come back far off (RespawnDistance, 96 m), 11
// and 2 it is back. Watched on Yabbashah floor 86 (2026-11-24): 4, 6 at 4.7 m, 7, then 9 and 10 fifteen seconds on.
bool is_rare(UObject* comp) {
  bool r = false;
  guarded([&] { r = comp && is_a(comp, "FldEnemyNormalComp") && get<int8_t>(comp, "EnemyType") == 2; });
  return r;
}
int behaviour_step(UObject* comp) {
  int step = -1;
  guarded([&] {
    uint8_t* so = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(comp) + 0x388);
    if (so) step = *reinterpret_cast<int32_t*>(so + 0x08);
  });
  return step;
}
// "Rare Shadow fleeing" as one within kMindRange starts to run (a sighted player sees it turn and bolt), and "Rare
// Shadow got away" when one told as fleeing vanishes. Caught (a battle) or anything else ends the flight quietly.
void rare_cues(const FVector& me) {
  if (!ue::known_build()) return;   // the state object's layout is this build's
  static std::map<WeakObj::Key, bool> fleeing;   // the Rare Shadows told as fleeing
  std::map<WeakObj::Key, bool> now;
  for (const Holder& h : holders()) {
    if (!is_rare(h.comp)) continue;
    const int step = behaviour_step(h.comp);
    auto key = WeakObj::of(h.actor).key();
    bool told = fleeing.count(key) > 0;
    if (step == 7 && !told) {
      FVector at{};
      if (guarded([&] { at = world::actor_location(h.actor); }) && std::hypot(flat(at, me), at.z - me.z) <= kMindRange) {
        speech::speak(strings::kRareFleeing.c_str(), false);
        log::writef("shadow: rare #{} flees", std::get<0>(key));
        told = true;
      }
    } else if (told && step != 7) {
      if (step == 9 || step == 10) {
        speech::speak(strings::kRareGotAway.c_str(), false);
        log::writef("shadow: rare #{} got away", std::get<0>(key));
      }
      told = false;
    }
    if (told) now[key] = true;
  }
  fleeing.swap(now);
}
bool hunting(UObject* shadow) {
  auto it = g_minds.find(WeakObj::of(shadow).key());
  return it != g_minds.end() && it->second.hunting;
}
void mind_cues(const std::vector<Seen>& seen, const FVector& me) {
  std::map<WeakObj::Key, Mind> now_known;
  for (const Seen& s : seen) {
    if (is_rare(s.comp)) continue;   // it flees instead: rare_cues
    const bool heard = s.dist <= kMindRange;
    auto key = WeakObj::of(s.actor).key();
    auto it = g_minds.find(key);
    Mind m = it == g_minds.end() ? Mind{} : it->second;
    bool was = m.hunting;
    if (s.raw.mark == Mark::Exclamation && m.last != Mark::Exclamation) { m.hunting = true; m.tracked = false; }
    else if (m.hunting) {
      if (s.raw.mark == Mark::Question && m.last != Mark::Question) m.hunting = false;
      else if (s.raw.tracking) m.tracked = true;
      else if (m.tracked) m.hunting = false;   // it held him as its target and has let go
    }
    m.last = s.raw.mark;
    if (m.hunting && !was) {
      // No alarm of the mod's own: the game sounds one as the mark goes up (the user's call, 2026-11-15). Logged only.
      log::writef("shadow: #{} noticed the hero at {:.1f} m{}", std::get<0>(key), s.dist / 100.0f, heard ? "" : " (too far off for the cue)");
    } else if (was && !m.hunting) {
      if (heard) audio::signal((int)SignalCue::Lost, 1.1f, audio::fading(world::spot(me, s.at)));
      log::writef("shadow: #{} lost the hero{}", std::get<0>(key), heard ? "" : " (too far off for the cue)");
    }
    now_known[key] = m;
  }
  g_minds.swap(now_known);
}

// ---- the log: the ring, the Shadows' attack zones and how each battle began, to tell afterwards why a fight went
// as it did (the user heard no ring before five battles, 2026-11-14) ----
// How far the hero stands off a Shadow's front, in degrees: under 90 the game counts it as facing him.
float off_front(const Seen& s, const FVector& me) {
  float to_me = std::atan2(me.y - s.at.y, me.x - s.at.x) * 180.0f / kPi;
  return angle_diff(yaw_of(s.actor), to_me);
}
// The ring for the nearest Shadow as it starts, changes and stops. `ring` is close_cues' answer (-1: none).
WeakObj g_ring_of;          // the Shadow the ring is sounding for now (none: index -1)
WeakObj g_rang_for;         // the Shadow it last sounded for, and when it last did
ULONGLONG g_rang_for_at = 0;
void log_ring(const Seen* s, int ring, const FVector& me) {
  static int cue = -1;
  WeakObj w = s && ring >= 0 ? WeakObj::of(s->actor) : WeakObj{};
  if (w == g_ring_of && ring == cue) {
    if (ring >= 0) g_rang_for_at = GetTickCount64();
    return;
  }
  if (cue >= 0) {
    if (s && WeakObj::of(s->actor) == g_ring_of)
      log::writef("shadow: #{} out of the strike's reach at {:.1f} m", g_ring_of.index, s->dist / 100.0f);
    else log::writef("shadow: #{} out of the strike's reach", g_ring_of.index);
  }
  if (ring >= 0) {
    log::writef("shadow: #{} in the strike's reach at {:.1f} m, {:.0f} deg off its front: {}", w.index, s->dist / 100.0f, off_front(*s, me),
                ring == (int)SignalCue::Ambush ? "the behind ring" : "the ring");
    g_rang_for = w;
    g_rang_for_at = GetTickCount64();
  }
  g_ring_of = w;
  cue = ring;
}

// The hero's body inside a Shadow's attack zone (its AttackArea's box), for the Shadows within 8 m. No sound: the log
// only (the user's call, 2026-11-14).
std::map<WeakObj::Key, ULONGLONG> g_in_zone;   // the Shadows whose zone holds the hero, and since when
bool attack_zone(UObject* comp, Box& b) {
  UObject* area = comp ? get<UObject*>(comp, "AttackArea") : nullptr;
  return read_box(area ? get<UObject*>(area, "AreaComp") : nullptr, b);
}
void log_zones(const std::vector<Seen>& seen, const FVector& me) {
  float r = 35.0f, hh = 90.0f;
  world::capsule_of(world::player(), r, hh);
  std::map<WeakObj::Key, ULONGLONG> now_in;
  for (const Seen& s : seen) {
    if (s.dist > 800.0f || !s.comp) continue;
    Box zone;
    bool in = false;
    if (!guarded([&] { in = attack_zone(s.comp, zone) && core::box_meets_body(zone, world::vec3(me), r, hh); }) || !in) continue;
    auto key = WeakObj::of(s.actor).key();
    auto it = g_in_zone.find(key);
    if (it != g_in_zone.end()) { now_in[key] = it->second; continue; }
    now_in[key] = GetTickCount64();
    log::writef("shadow: #{} the hero is in its attack zone at {:.1f} m, {:.0f} deg off its front{}", std::get<0>(key), s.dist / 100.0f,
                off_front(s, me), hunting(s.actor) ? ", hunting" : "");
  }
  for (auto& [key, since] : g_in_zone)
    if (!now_in.count(key)) log::writef("shadow: #{} the hero is out of its attack zone", std::get<0>(key));
  g_in_zone.swap(now_in);
}

// How a battle is about to begin, as the game decided it (AFldOperator.EncountType), once per encounter.
void log_encounter() {
  static const int id = watch::want("FldOperator");
  static int last_type = 0;
  static WeakObj last_enemy;
  UObject* op = watch::get(id);
  int type = 0;
  Holder h{nullptr, nullptr};
  if (op)
    guarded([&] {
      if (int32_t* t = field<int32_t>(op, "EncountType")) type = *t;
      if (Holder* e = field<Holder>(op, "EncountEnemy")) h = *e;
    });
  WeakObj enemy = WeakObj::of(h.actor);
  if (type == last_type && enemy == last_enemy) return;
  last_type = type;
  last_enemy = enemy;
  if (type < 1 || type > 5 || !h.actor) return;
  static const char* kinds[] = {"", "your strike, the Shadow facing you: a normal battle", "your strike from behind: your advantage",
                                "Ambush, the Shadow facing you: your advantage", "Ambush from behind: your advantage",
                                "the Shadow reached you first: its attack"};
  std::string where = "?";
  FVector me, at{};
  if (world::player_location(me) && guarded([&] { at = world::actor_location(h.actor); }))
    where = std::format("{:.1f} m", std::hypot(flat(at, me), at.z - me.z) / 100.0f);
  std::string ring = enemy == g_ring_of        ? "the ring was sounding"
                     : enemy == g_rang_for     ? std::format("the ring last sounded {:.1f} s before", (GetTickCount64() - g_rang_for_at) / 1000.0)
                                               : "the ring never sounded for it";
  auto zone = g_in_zone.find(enemy.key());
  std::string in_zone = zone != g_in_zone.end() ? std::format("the hero was in its attack zone for {:.1f} s", (GetTickCount64() - zone->second) / 1000.0)
                                                : "the hero was not in its attack zone";
  log::writef("shadow: battle begins with #{} at {}: {} (type {}); {}; {}", enemy.index, where, kinds[type], type, ring, in_zone);
}

// The held snarl's samples, made on first use (game thread).
const audio::Pcm& drone_pcm() {
  static const audio::Pcm drone = std::make_shared<const std::vector<float>>(core::drone_loop(audio::sample_rate()));
  return drone;
}

// ---- strike assist ----
// As a swing starts the hero turns to the Shadow his strike would reach if he faced it, on any side: the strike's
// box swung round him to face each Shadow and put to the game's own test against its body, so the reach itself is
// unchanged; it only aims. A Shadow hunting him first, then the nearest (the user's call, 2026-11-15). The swing takes
// its direction from his facing as it starts (AttackForward, written on its first frame, FUN_141124420): turned while
// the swing is asked for (NextBehavior Attack) the game aims it itself; caught on its first frame instead,
// AttackForward is set too. Each blow of a combo is aimed again. Every swing is logged, with or without a Shadow.
constexpr int32_t kBehaviorAttack = 7;   // FldPlayerDungeonComp.Behavior: 1 Free, 7 Attack (nav.cpp's /strike)
void strike_assist(const std::vector<Seen>& seen, const FVector& me) {
  UObject* dc = dungeon_comp();
  int32_t* b = dc ? field<int32_t>(dc, "Behavior") : nullptr;
  int32_t* nb = dc ? field<int32_t>(dc, "NextBehavior") : nullptr;
  if (!b || !nb) return;
  int32_t* id = field<int32_t>(dc, "AttackId");
  const int aid = id ? *id : 0;
  const bool swinging = *b == kBehaviorAttack, asked = *nb == kBehaviorAttack;
  static bool armed = true;
  static int prev_b = 0, prev_aid = -1;
  bool fire = false;
  if (!swinging && !asked) armed = true;
  else if (armed) { fire = true; armed = false; }
  else if (swinging && prev_b == kBehaviorAttack && aid != prev_aid) fire = true;   // the combo's next blow
  prev_b = *b;
  prev_aid = aid;
  if (!fire) return;
  const char* when = swinging ? "first frame" : "asked";
  if (!settings::on(settings::StrikeAssist)) { log::writef("shadow: swing (attack {}, {}), strike assist off", aid, when); return; }
  Box box;
  if (long_range(dc) || !strike_box(dc, box)) {
    log::writef("shadow: swing (attack {}, {}), no strike box to aim with (long range {}, lock-on {})", aid, when,
                get_bool(dc, "IsUsingLongRangeAttack"), get<UObject*>(dc, "LockOnActor") != nullptr);
    return;
  }
  const Seen* pick = nullptr;
  float pick_yaw = 0.0f;
  for (const Seen& s : seen) {
    float yaw = std::atan2(s.at.y - me.y, s.at.x - me.x) * 180.0f / kPi;
    float r, hh;
    body_of(s.actor, r, hh);
    if (!core::box_meets_body(core::turned_about(box, world::vec3(me), yaw), world::vec3(s.at), r, hh)) continue;
    bool better = !pick || (hunting(s.actor) != hunting(pick->actor) ? hunting(s.actor) : s.dist < pick->dist);
    if (better) { pick = &s; pick_yaw = yaw; }
  }
  UObject* hero = world::player();
  // No Shadow: a breakable thing in reach on any side, the nearest (aimed the same way; 2026-11-24, aiming at one by
  // ear was hard).
  if (!pick && hero) {
    FVector at{};
    float yaw = 0.0f;
    if (UObject* br = breakable_reached(me, at, yaw)) {
      float turned = angle_diff(yaw_of(hero), yaw);
      Params sp(find_function(class_of(hero), "K2_SetActorRotation"));
      sp.set<FRotator>("NewRotation", FRotator{0.0f, yaw, 0.0f});
      call(hero, sp);
      if (swinging)
        if (FVector* fwd = field<FVector>(dc, "AttackForward")) *fwd = FVector{std::cos(yaw * kPi / 180.0f), std::sin(yaw * kPi / 180.0f), 0.0f};
      log::writef("shadow: swing (attack {}, {}): strike assist turned the hero {:.0f} deg to breakable #{}", aid, when, turned, index_of(br));
      return;
    }
  }
  if (!pick || !hero) { log::writef("shadow: swing (attack {}, {}), no Shadow in reach on any side", aid, when); return; }
  float turned = angle_diff(yaw_of(hero), pick_yaw);
  Params sp(find_function(class_of(hero), "K2_SetActorRotation"));
  sp.set<FRotator>("NewRotation", FRotator{0.0f, pick_yaw, 0.0f});
  call(hero, sp);
  if (swinging)
    if (FVector* fwd = field<FVector>(dc, "AttackForward"))
      *fwd = FVector{std::cos(pick_yaw * kPi / 180.0f), std::sin(pick_yaw * kPi / 180.0f), 0.0f};
  log::writef("shadow: swing (attack {}, {}): strike assist turned the hero {:.0f} deg to #{} at {:.1f} m, {:.0f} deg off its front{}", aid, when, turned,
              index_of(pick->actor), pick->dist / 100.0f, off_front(*pick, me), hunting(pick->actor) ? ", hunting" : "");
}
}  // namespace

bool strike_reaches(UObject* breakable, const FVector& me, float& yaw) {
  UObject* dc = dungeon_comp();
  Box strike;
  if (!breakable || !dc || long_range(dc) || !strike_box(dc, strike)) return false;
  bool r = false;
  guarded([&] { r = poi::breakable(breakable) && breakable_meets(strike, breakable, me, true, yaw); });
  return r;
}

std::vector<Holder> enemy_holders() {
  static const int id = watch::want("FldEnemyManager");
  std::vector<Holder> out;
  UObject* mgr = watch::get(id);
  auto* arr = mgr ? field<TArray<Holder>>(mgr, "Enemies") : nullptr;
  if (arr && arr->data && arr->num > 0 && arr->num < 256)
    guarded([&] { for (int i = 0; i < arr->num; ++i) out.push_back(arr->data[i]); });
  return out;
}

void tick() {
  log_encounter();   // the battle starts as the field is left, so before the check below
  if (!world::in_control()) return;
  FVector me;
  if (!world::player_location(me)) return;
  std::vector<Seen> seen = look(me);
  strike_assist(seen, me);   // its own setting, and every swing logged
  if (!settings::on(settings::ShadowAlerts)) return;
  mind_cues(seen, me);
  rare_cues(me);
  log_zones(seen, me);
  const Seen* nearest = nullptr;
  for (const Seen& s : seen) if (!nearest || s.dist < nearest->dist) nearest = &s;
  const bool shadow_near = nearest && nearest->dist <= kPulseRange;
  // The strike's ring: a Shadow is in reach, else a breakable thing is. It says "you can strike now", so it comes
  // from the player (no place, both ears alike), not from the thing (the user's call, 2026-11-10).
  int ring = shadow_near ? close_cues(*nearest, me) : -1;
  log_ring(nearest, ring, me);
  FVector ring_at{};
  if (ring < 0 && breakable_in_reach(me, ring_at)) ring = (int)SignalCue::Reach;
  // Each ring is queued a tick ahead at its own time, a steady 150 ms apart (on the frames and the coarse tick count it
  // was 150 or 166 ms). After a pause in it, the first rings at once.
  const double now = audio::now_s();
  static double ring_next = 0;
  if (ring >= 0 && now + audio::tick_interval_s() >= ring_next) {
    const double start = now - ring_next > kReachS ? now : std::max(ring_next, now);
    audio::signal_here(ring, 1.2f, start);
    ring_next = start + kReachS;
  }
  // The nearest Shadow within 30 m: one held snarl from where it is (it was a growl repeated faster as it neared; the
  // user asked for one constant sound, its facing told by something other than pitch, 2026-11-15). Louder as it
  // nears, by Dark Vision's distance curve (half as loud at 3 m as on him, followed while it sounds): its level rose
  // evenly over the whole 30 m before, so a few steps toward it or away changed almost nothing and its distance could
  // not be judged (a player's report, 2026-11-25). Higher while it hunts the hero, lower from behind him (the Behind pitch setting), as before. Its facing:
  // bright facing him, more muffled the further it turns away, and once his place is behind its front half (the
  // game's own 90 degrees, where a strike brings the advantage) its loudness wobbles too.
  const audio::Pcm& drone = drone_pcm();
  if (!shadow_near) { audio::release_hold(kDroneId); return; }
  bool hunted = hunting(nearest->actor);
  bool behind = std::cos(world::bearing(me, nearest->at) * kPi / 180.0f) < -0.2f && settings::on(settings::BehindPitch);
  float off = off_front(*nearest, me);
  audio::hold(kDroneId, drone, hunted ? 1.5f : 1.3f, audio::fading(world::spot(me, nearest->at)),
              (behind ? 0.7f : 1.0f) * (hunted ? 1.3f : 1.0f), 1.0f - off / 180.0f, off > kBackTurnedDeg ? 0.75f : 0.0f);
  // Its facing, logged as it crosses the game's line (to compare with what was heard).
  static WeakObj facing_of;
  static bool was_back = false;
  WeakObj fw = WeakObj::of(nearest->actor);
  bool back = off > kBackTurnedDeg;
  if (!(fw == facing_of) || back != was_back) {
    if (fw == facing_of || back)
      log::writef("shadow: #{} {} at {:.1f} m ({:.0f} deg off its front)", fw.index, back ? "turned its back on the hero" : "turned to face the hero",
                  nearest->dist / 100.0f, off);
    facing_of = fw;
    was_back = back;
  }
  // A Shadow's first growl is logged with its distance (how early the player could have heard it).
  static WeakObj growled;
  if (WeakObj w = WeakObj::of(nearest->actor); !(w == growled)) {
    growled = w;
    log::writef("shadow: #{} first growls at {:.1f} m{}", w.index, nearest->dist / 100.0f, hunted ? ", hunting" : "");
  }
}

void demo(int which) {
  audio::Spot ahead{};
  ahead.dist_m = 3.0f;
  if (which == 0) audio::hold(kDemoId, drone_pcm(), 1.0f, ahead, 1.0f, 1.0f, 0.0f, 1500);
  else if (which == 1) audio::hold(kDemoId, drone_pcm(), 1.2f, ahead, 1.3f, 1.0f, 0.0f, 1500);
  else audio::hold(kDemoId, drone_pcm(), 1.0f, ahead, 1.0f, 0.15f, 0.75f, 1500);
}

// The Reaper's timer (Relaxed Reaper Rate). A floor's init script (BF_FldInitScript_299_all, SUB_REAPER) calls
// DUNGEON_REAPER_APPEAR_TIME(n) on arrival: 180 + 5 per part of the floor, 10 + 5 per part where the Reaper already
// came, 25 for its quick return (BIT 1377, COUNT 231 1-2), 0 at the entrance. The command (FUN_1411a1100) stores n as
// a float at UFldDungeonReaperController +0x150, which counts down in seconds (FUN_14118b520; Fuuka's warning at
// COUNT 230 = 20 left, the Reaper spawns at 0). DUNGEON_REAPER_CONTINUE_APPEAR_TIME (+0x154, 2100 or 180) is the
// second timer, which sets BIT 1377 (the quick return) when it runs out. With the option on, both arguments are
// doubled before the command reads them, so every timer the scripts set runs twice as long; the warning still comes
// 20 seconds before. Turning the option on or off on a floor doubles or halves what is left of the timers set
// before (set_relaxed_reaper); each timer remembers whether it was set doubled, so it is never doubled twice or
// halved below the game's own time.
static flow::Command g_appear_cmd, g_continue_cmd;
static bool g_doubled[2];   // the appear timer (+0x150) and the continue timer (+0x154) were set doubled

static int64_t relaxed(flow::Command orig, int which, const char* what, uint8_t* ctx) {
  g_doubled[which] = false;
  if (settings::on(settings::RelaxedReaper)) {
    int before = flow::int_arg(ctx);
    if (flow::scale_arg(ctx, 2)) {
      g_doubled[which] = true;
      log::writef("shadow: {}({}) doubled to {}", what, before, flow::int_arg(ctx));
    }
  }
  return orig(ctx);
}
static int64_t appear_hook(uint8_t* ctx) { return relaxed(g_appear_cmd, 0, "reaper appear time", ctx); }
static int64_t continue_hook(uint8_t* ctx) { return relaxed(g_continue_cmd, 1, "reaper continue time", ctx); }

void set_relaxed_reaper(bool on) {
  if (!ue::known_build()) return;   // the controller's layout is this build's
  static const int id = watch::want("FldDungeonReaperController");
  UObject* ctrl = watch::get(id);
  for (int which = 0; which < 2; ++which) {
    if (g_doubled[which] == on) continue;
    g_doubled[which] = on;
    if (!ctrl) continue;
    guarded([&] {
      float& left = *(float*)((uint8_t*)ctrl + 0x150 + which * 4);
      if (left <= 0.0f) return;   // not counting: nothing to change
      float before = left;
      left = on ? left * 2.0f : left / 2.0f;
      log::writef("shadow: reaper {} timer {:.0f} s left, now {:.0f}", which ? "continue" : "appear", before, left);
    });
  }
}

void install() {
  if ((g_appear_cmd = (flow::Command)flow::command("DUNGEON_REAPER_APPEAR_TIME")))
    hooks::attach((void**)&g_appear_cmd, (void*)&appear_hook, "DUNGEON_REAPER_APPEAR_TIME");
  if ((g_continue_cmd = (flow::Command)flow::command("DUNGEON_REAPER_CONTINUE_APPEAR_TIME")))
    hooks::attach((void**)&g_continue_cmd, (void*)&continue_hook, "DUNGEON_REAPER_CONTINUE_APPEAR_TIME");
  dev::route("/shadows", [](const dev::Request&, int&) {
    return dev::on_game([] {
      FVector me;
      if (!world::player_location(me)) return std::string("no hero\n");
      std::string s;
      UObject* dc = dungeon_comp();
      Box b{};
      bool has_box = strike_box(dc, b);
      UObject* area = dc ? get<UObject*>(dc, "AttackArea") : nullptr;
      UObject* comp = area ? get<UObject*>(area, "AreaComp") : nullptr;
      s += std::format("hero ({:.0f}, {:.0f}, {:.0f}) dungeon_comp={} long_range={} lock_on={}\n", me.x, me.y, me.z, dc ? name_of(dc) : "-",
                       dc ? get_bool(dc, "IsUsingLongRangeAttack") : false, dc && get<UObject*>(dc, "LockOnActor") ? name_of(get<UObject*>(dc, "LockOnActor")) : "-");
      if (has_box)
        s += std::format("strike box centre ({:.0f}, {:.0f}, {:.0f}) extent ({:.0f}, {:.0f}, {:.0f}) yaw {:.0f}, {:.0f} cm from the hero\n", b.center.x, b.center.y,
                         b.center.z, b.extent.x, b.extent.y, b.extent.z, b.yaw, flat(world::fvec(b.center), me));
      else s += "no strike box\n";
      for (UObject* a : live("FldDungeonObjectActor")) {
        if (!poi::breakable(a)) continue;
        FVector v = world::actor_location(a);
        bool engine = false;
        if (comp) { Params p(find_function(class_of(comp), "IsOverlappingActor")); p.set<UObject*>("Other", a); if (call(comp, p)) engine = p.ret<bool>(); }
        Box body{};
        bool has_body = read_box(get<UObject*>(a, "Box"), body);
        s += std::format("  breakable {} #{} {:.0f} cm bearing {:.0f} engine overlap={} box centre ({:.0f}, {:.0f}, {:.0f}) extent ({:.0f}, {:.0f}, {:.0f}) yaw {:.0f} meets={}\n",
                         name_of(a), index_of(a), std::hypot(flat(v, me), v.z - me.z), world::bearing(me, v), engine, body.center.x, body.center.y, body.center.z,
                         body.extent.x, body.extent.y, body.extent.z, body.yaw, has_body && has_box && boxes_meet(b, body));
      }
      if (FVector at; breakable_in_reach(me, at)) s += "  a breakable is in the strike's reach\n";
      for (const Seen& e : look(me)) {
        bool known = false;
        bool reach = in_reach(e.actor, e.at, me, known);
        float r, hh;
        body_of(e.actor, r, hh);
        bool engine = false;
        if (comp) { Params p(find_function(class_of(comp), "IsOverlappingActor")); p.set<UObject*>("Other", e.actor); if (call(comp, p)) engine = p.ret<bool>(); }
        s += std::format("  {} #{} {:.0f} cm mark={} tracking={} hunting={} reach={} (known={}, engine overlap={}) body r {:.0f} hh {:.0f}\n", name_of(e.actor),
                         index_of(e.actor), e.dist, (int)e.raw.mark, e.raw.tracking, hunting(e.actor), reach, known, engine, r, hh);
      }
      for (const Holder& h : holders()) {
        UObject* mark = first_object(h.comp, "CurrentMarkEffectParam");
        UObject* track = first_object(h.comp, "TrackingTarget");
        s += std::format("  holder {} ({}) comp {} state {} mark {} tracking {} dead {} vanish {}\n", name_of(h.actor), name_of(class_of(h.actor)),
                         name_of(class_of(h.comp)), get<int32_t>(h.comp, "State", -1), mark ? name_of(mark) : "-", track ? name_of(track) : "-",
                         get_bool(h.comp, "bIsDead"), get_bool(h.comp, "bVanish"));
      }
      return s;
    });
  }, "the Shadows on the floor: what each knows of the hero, and the strike's reach");
}
}  // namespace p3a::shadow
