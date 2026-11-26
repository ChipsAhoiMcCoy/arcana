#include "doors.h"
#include "core/boxes.h"
#include "core/doorway.h"
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "seh.h"
#include "watch.h"
#include "world.h"
#include <algorithm>
#include <cmath>
#include <format>
#include <map>
#include <memory>
#include <string>
#include <vector>

// AFldDoorObjCore (BP_F101_103_DoorA_C, BP_F101_PassDoor_C, every room and shop door): a skeletal door with its own
// blocking boxes. Most hang in a wall beside the navmesh and no path meets them; a few stand across it (the gym
// hallway's is a 5 m x 20 cm box, WorldStatic, at (0, -2652)), shut until the game's own exit script plays them open
// (PlayDoorOpen; IsPlayingOpen while it does) and walks the hero through. The navmesh runs on underneath.
namespace p3a::doors {
using ue::UObject;
using ue::WeakObj;
using world::FVector;

struct Door { WeakObj obj; FVector lo{}, hi{}; };   // the bounds of its colliding parts
static std::vector<Door> g_doors;                   // the visible levels' doors
static std::vector<WeakObj::Key> g_keys;
// Counts every time the hero may be in another part of the map than before: answers are kept per count.
static uint64_t g_side = 1;
uint64_t side_stamp() { return g_side; }

// A door's colliding bounds (GetActorBounds, a call into the game): Ok, None while nothing of it collides (yet), or
// Skip when the call cannot be made.
enum class Bounds { Ok, None, Skip };
static Bounds bounds_of(UObject* d, FVector& lo, FVector& hi) {
  ue::Params p(ue::find_function(ue::class_of(d), "GetActorBounds"));
  if (!p.fn || !p.set<uint8_t>("bOnlyCollidingComponents", 1)) return Bounds::Skip;
  FVector* o = p.at<FVector>("Origin");
  FVector* e = p.at<FVector>("BoxExtent");
  if (!o || !e || !guarded([&] { ue::call(d, p); })) return Bounds::Skip;
  if (e->x <= 0 && e->y <= 0) return Bounds::None;
  lo = FVector{o->x - e->x, o->y - e->y, o->z - e->z};
  hi = FVector{o->x + e->x, o->y + e->y, o->z + e->z};
  return Bounds::Ok;
}

// Waiting on a door's bounds with the levels unchanged: the doors read before are there in the same order and none of
// the others has bounds now. Only those others are asked: two of the dorm's toilet doors (Toilet1F01, Toilet4F01)
// never collide, and asking all nineteen doors every frame cost ~18 us (2026-11-26).
static bool still_waiting(int id) {
  size_t known = 0;
  for (UObject* d : watch::all(id)) {
    if (!world::actor_visible_level(d)) continue;
    if (known < g_keys.size() && WeakObj::of(d).key() == g_keys[known]) { ++known; continue; }
    FVector lo, hi;
    if (bounds_of(d, lo, hi) == Bounds::Ok) return false;   // one more to read (or the order changed): read them all
  }
  return known == g_keys.size();   // else one read before has gone
}

// The doors come and go with their levels: read again when the set of visible levels changes (every door of every
// loaded level each frame cost 10 us, 2026-11-11), and when a visible door that had no bounds (a level just shown)
// has them.
static void refresh() {
  static const int id = watch::want("FldDoorObjCore", true);
  static uint64_t levels = ~0ull;
  static bool unready = false;
  uint64_t stamp = world::levels_stamp();
  if (stamp == levels && (!unready || still_waiting(id))) return;
  levels = stamp;
  unready = false;
  std::vector<Door> doors;
  std::vector<WeakObj::Key> keys;
  for (UObject* d : watch::all(id)) {
    if (!world::actor_visible_level(d)) continue;
    FVector lo, hi;
    Bounds b = bounds_of(d, lo, hi);
    if (b == Bounds::Skip) continue;
    if (b == Bounds::None) { unready = true; continue; }   // nothing of it collides (yet)
    doors.push_back(Door{WeakObj::of(d), lo, hi});
    keys.push_back(doors.back().obj.key());
  }
  if (keys == g_keys) return;
  g_keys = std::move(keys);
  g_doors = std::move(doors);
  ++g_side;
  log::writef("doors: {} on the visible levels", g_doors.size());
}

static core::Rect rect(const Door& d) { return core::Rect{d.lo.x, d.lo.y, d.hi.x, d.hi.y}; }

void tick() {
  static WeakObj hero_seen;
  static FVector at{};
  static uint64_t levels = 0;
  UObject* hero = world::player();
  FVector me;
  if (!hero || !world::player_location(me)) return;   // hidden behind a menu: he comes back where he was, or jumps
  world::actor_visible_level(hero);   // keeps the list of visible levels current
  refresh();
  if (uint64_t l = world::levels_stamp(); l != levels) { levels = l; ++g_side; }   // a level came or went, its navmesh with it
  WeakObj h = WeakObj::of(hero);
  float step = std::fabs(me.x - at.x) + std::fabs(me.y - at.y) + std::fabs(me.z - at.z);
  if (!(h == hero_seen) || step > 400.0f) ++g_side;   // a new field's hero; stairs and exits move him in one frame
  else if (step > 1.0f)
    // The game walks him through an open door: the step that passes its bounds is the change of sides.
    for (const Door& d : g_doors) {
      core::Vec2 in, out;
      if (me.z < d.lo.z - 150.0f || me.z > d.hi.z + 150.0f) continue;
      if (core::clip(core::Vec2{at.x, at.y}, core::Vec2{me.x, me.y}, rect(d), in, out)) { ++g_side; break; }
    }
  hero_seen = h;
  at = me;
}

// The path's leg a -> b (navmesh points, at the floor) is shut by this door.
static bool shuts(const Door& d, const FVector& a, const FVector& b, std::vector<UObject*>& people) {
  if (std::max(a.z, b.z) + 250.0f < d.lo.z || std::min(a.z, b.z) - 100.0f > d.hi.z) return false;   // another storey's
  core::Vec2 in, out;
  if (!core::clip(core::Vec2{a.x, a.y}, core::Vec2{b.x, b.y}, rect(d), in, out)) return false;
  // Where the leg crosses the door's bounds, its floor must be within the door's height: a leg up a stairway passes
  // over a door below it. The Iwatodai Strip Mall's stairs to the Net Cafe run 1.3 m over the diner's closed door
  // (its top at 651, the steps at 750 to 810, 2026-11-23): the storey test above let it by by a centimetre, the door
  // shut the way, and the walk said there was none.
  {
    float len2 = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    auto z_at = [&](core::Vec2 p) {
      float t = len2 < 1.0f ? 0.0f : std::clamp(((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / len2, 0.0f, 1.0f);
      return a.z + (b.z - a.z) * t;
    };
    float lo = std::min(z_at(in), z_at(out)), hi = std::max(z_at(in), z_at(out));
    if (lo > d.hi.z - 50.0f || hi + 250.0f < d.lo.z) return false;   // over the door's top, or under it
  }
  UObject* door = d.obj.resolve();
  if (!door) return false;
  // Playing open (the hero is being walked through it): it is a shut door again when that is over.
  if (ue::call_ret<bool>(door, "IsPlayingOpen")) return true;
  // The bounds are a box round the whole door, wider than a door that stands at an angle: the door itself is asked,
  // with a line at chest height along the leg's piece inside them. Whatever stops it there shuts the way.
  float dx = b.x - a.x, dy = b.y - a.y, len = std::hypot(dx, dy);
  if (len < 1.0f) return false;
  dx /= len; dy /= len;
  float z = std::clamp((a.z + b.z) * 0.5f + 90.0f, d.lo.z + 30.0f, std::max(d.lo.z + 30.0f, d.hi.z - 30.0f));
  world::Hit hit = world::line(FVector{in.x - dx * 5.0f, in.y - dy * 5.0f, z}, FVector{out.x + dx * 5.0f, out.y + dy * 5.0f, z}, "Pawn", &people);
  return hit.hit;
}

// The hero sees the thing over the furniture: a line above head height meets no wall on the way (people are looked
// past, the thing itself and what stands at it end the line). A room whose desks split its navmesh (classroom 2-F:
// the path from the back door to a front desk goes out through one door and in through the other) is still one room.
static bool same_room(UObject* thing, const FVector& me, const FVector& at, std::string* report) {
  float z = std::max(me.z, at.z) + 90.0f;
  FVector a{me.x, me.y, z}, b{at.x, at.y, z};
  float len = std::hypot(b.x - a.x, b.y - a.y);
  std::vector<UObject*> people;
  world::Hit hit = world::line(a, b, "Pawn", &people);
  bool clear = !hit.hit || hit.actor == thing || hit.distance > len - 100.0f;
  if (report) *report += std::format("sightline at z {:.0f}: {}\n", z, clear ? "clear" : std::format("stopped by {} at {:.0f} of {:.0f} cm", hit.actor ? ue::name_of(hit.actor) : "?", hit.distance, len));
  return clear;
}

// What the walking path to a thing meets: a closed door on the way, and whether the thing is in the hero's room all
// the same (in another part of the map only when both). `via`: no door on the way to the floor beside the thing on
// another side, where the hero reaches it (see other_side).
struct Verdict { bool shut = false, same_room = false, has_via = false; FVector via{}; };

// The first closed door on a path to a thing at `to`. A thing at the door itself (the exit that opens it, a hit on the
// door) is not behind it: its path ends in the door's bounds, a body's width allowed.
static bool door_on(const std::vector<FVector>& path, const FVector& to, std::string* report) {
  std::vector<UObject*> people;   // somebody standing in a doorway does not shut it
  auto at_door = [&](const Door& d) {
    return to.x > d.lo.x - 30.0f && to.x < d.hi.x + 30.0f && to.y > d.lo.y - 30.0f && to.y < d.hi.y + 30.0f && to.z > d.lo.z - 150.0f && to.z < d.hi.z + 150.0f;
  };
  for (size_t i = 1; i < path.size(); ++i)
    for (const Door& d : g_doors)
      if (!at_door(d) && shuts(d, path[i - 1], path[i], people)) {
        if (report) *report += std::format("shut by {} on the leg ({:.0f}, {:.0f}) -> ({:.0f}, {:.0f})\n", ue::name_of(d.obj.resolve()), path[i - 1].x, path[i - 1].y, path[i].x, path[i].y);
        return true;
      }
  return false;
}

// The hero standing at `p` (a navmesh point, at the floor) reaches the thing: its trigger box (else its spot) is a step
// away, with nothing solid between at waist height (people are looked past; the thing itself ends the line).
static bool reaches_from(UObject* thing, const FVector& p, const FVector& at) {
  core::Box box;
  bool has_box = world::trigger_box(thing, box);
  FVector q = at;
  if (has_box) {
    core::Vec3 n = core::box_nearest(box, core::Vec3{p.x, p.y, at.z});
    q = FVector{n.x, n.y, at.z};
  }
  float d = std::hypot(q.x - p.x, q.y - p.y);
  if (d > (has_box ? 100.0f : 150.0f)) return false;
  float z = p.z + 80.0f;
  std::vector<UObject*> people;
  world::Hit hit = world::line(FVector{p.x, p.y, z}, FVector{q.x, q.y, z}, "Pawn", &people);
  return !hit.hit || hit.actor == thing || hit.distance > d - (has_box ? 15.0f : 40.0f);
}

// A thing set in a wall has floor on both sides of it, and the navmesh path to its spot can end on the far side: the
// Printing Room's sign on the school's 2F stands in the corridor's south wall, and the path to it went through the
// next classroom's closed door to the floor behind the sign (2026-11-23), so it was left out of the list. The hero
// presses it from the corridor. Tried when the path to the spot is shut: the floor round it, eight ways, at two
// distances; the nearest walk to a point that reaches the thing with no closed door on the way.
static bool other_side(UObject* thing, const FVector& me, const FVector& at, FVector& via, std::string* report) {
  float best = 1e30f;
  for (float r : {100.0f, 180.0f})
    for (int k = 0; k < 8; ++k) {
      float a = k * 3.14159265f / 4.0f;
      FVector p{};
      if (!world::project_to_nav(FVector{at.x + std::cos(a) * r, at.y + std::sin(a) * r, at.z}, 60.0f, p, 150.0f)) continue;
      auto no = [&](const char* why) { if (report) *report += std::format("  ({:.0f}, {:.0f}, {:.0f}): {}\n", p.x, p.y, p.z, why); };
      if (!reaches_from(thing, p, at)) { no("does not reach it"); continue; }
      bool partial = false;
      auto path = world::find_path(world::path_start(me), p, &partial);
      if (path.empty() || (partial && std::hypot(path.back().x - p.x, path.back().y - p.y) > 50.0f)) { no("no path"); continue; }
      if (door_on(path, at, nullptr)) { no("a closed door on the way"); continue; }
      float len = 0;
      for (size_t i = 1; i < path.size(); ++i) len += std::hypot(path[i].x - path[i - 1].x, path[i].y - path[i - 1].y);
      if (len < best) { best = len; via = p; }
    }
  if (report) *report += best < 1e30f ? std::format("reached from another side: stand at ({:.0f}, {:.0f}), {:.0f} cm to walk\n", via.x, via.y, best)
                                      : std::string("no other side reaches it\n");
  return best < 1e30f;
}

static Verdict work_out(UObject* thing, const FVector& me, const FVector& at, std::string* report = nullptr) {
  bool partial = false;
  auto path = world::find_path(world::path_start(me), at, &partial);
  // A thing standing off the navmesh: the path to the navmesh beside it, as the auto-walk takes it.
  FVector beside{};
  if (path.empty() && world::project_to_nav(at, 300.0f, beside)) path = world::find_path(world::path_start(me), beside, &partial);
  if (report) *report += std::format("path: {} point(s){}\n", path.size(), partial ? " (partial)" : "");
  Verdict v;
  if (!door_on(path, at, report)) return v;
  if (other_side(thing, me, at, v.via, report)) { v.has_via = true; return v; }
  v.shut = true;
  v.same_room = same_room(thing, me, at, report);
  return v;
}

static Verdict verdict(UObject* a, const FVector& me, const FVector& at) {
  if (g_doors.empty() || !a) return {};
  struct Answer { FVector at; Verdict v; };
  static std::map<WeakObj::Key, Answer> answers;
  static uint64_t side = 0;
  if (side != g_side) { side = g_side; answers.clear(); }
  auto key = WeakObj::of(a).key();
  auto it = answers.find(key);
  // Somebody who has walked on is asked about again.
  if (it != answers.end() && std::fabs(it->second.at.x - at.x) + std::fabs(it->second.at.y - at.y) + std::fabs(it->second.at.z - at.z) < 100.0f)
    return it->second.v;
  Verdict v;
  guarded([&] { v = work_out(a, me, at); });
  answers[key] = Answer{at, v};
  return v;
}

bool behind(UObject* a, const FVector& me, const FVector& at) { Verdict v = verdict(a, me, at); return v.shut && !v.same_room; }
// Asked afresh: the walk starts from where the hero stands now, and in a room the navmesh splits the answer changes
// with that (from the back of classroom 2-F the path to the front bookshelf goes through the doors, from the front it
// does not; the kept answer sent the walk into the back door, 2026-11-12).
Way walk_way(UObject* a, const FVector& me, const FVector& at, FVector* via) {
  if (g_doors.empty() || !a) return Way::open;
  Verdict v;
  guarded([&] { v = work_out(a, me, at); });
  if (v.has_via && via) *via = v.via;
  return v.has_via ? Way::other_side : !v.shut ? Way::open : v.same_room ? Way::in_room : Way::behind;
}

void install() {
  dev::route("/doors", [](const dev::Request& r, int&) {
    int obj = (int)dev::arg_int(r, "obj", -1);
    bool all = dev::arg(r, "all") == "1";
    auto out = std::make_shared<std::string>("timeout\n");
    hooks::run_on_game_thread([out, obj, all] {
      std::string s = std::format("{} door(s) on the visible levels, side count {}\n", g_doors.size(), g_side);
      FVector here;
      if (all && world::player_location(here)) {
        // Every hit on the visible levels with a closed door on its path from here: behind it, in this room, or
        // reached from another side.
        static const int hits = watch::want("FldHitCore", true);
        for (UObject* t : watch::all(hits)) {
          if (!world::actor_visible_level(t)) continue;
          FVector at = world::actor_location(t);
          Verdict v;
          guarded([&] { v = work_out(t, here, at); });
          if (v.has_via) s += std::format("via #{} {} at ({:.0f}, {:.0f}, {:.0f}) from ({:.0f}, {:.0f})\n", ue::index_of(t), ue::name_of(t), at.x, at.y, at.z, v.via.x, v.via.y);
          else if (v.shut) s += std::format("{} #{} {} at ({:.0f}, {:.0f}, {:.0f})\n", v.same_room ? "room" : "behind", ue::index_of(t), ue::name_of(t), at.x, at.y, at.z);
        }
        *out = s;
        return;
      }
      for (const Door& d : g_doors) {
        UObject* o = d.obj.resolve();
        s += std::format("  #{} {} ({:.0f}, {:.0f}, {:.0f}) .. ({:.0f}, {:.0f}, {:.0f}){}\n", d.obj.index, o ? ue::name_of(o) : "gone", d.lo.x, d.lo.y, d.lo.z,
                         d.hi.x, d.hi.y, d.hi.z, o && ue::call_ret<bool>(o, "IsPlayingOpen") ? " playing open" : "");
      }
      FVector me;
      if (UObject* t = obj >= 0 ? ue::object_at(obj) : nullptr; t && world::player_location(me)) {
        std::string why;
        Verdict v = work_out(t, me, world::actor_location(t), &why);
        s += std::format("{}: {}\n{}", ue::name_of(t), v.has_via ? "reached from another side" : !v.shut ? "not behind a door" : v.same_room ? "in this room; the walking path goes through a closed door" : "behind a closed door", why);
      }
      *out = s;
    });
    return *out;
  }, "?obj=N the visible levels' doors; whether the path to an actor goes through a closed one");
}
}  // namespace p3a::doors
