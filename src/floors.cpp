// Floors of one field the hero walks between, and the stairways that join them.
// Read here:
//  - The field's owner object (native 0x11af780; what GET_FIELD_PARTS_ID asks): +0x54 the field's major id, +0x58
//    its minor, +0x64 the hero's entry in it, whose thousands are the part (0x11addf0: entry / 1000; SET_FIELD_PARTS_ID
//    writes part * 1000 + 1). This build's addresses: asked only on a known build.
//  - AFldHitCore.mOverlapBluePrint_: a slab's walk-in blueprint, which names the part its script sets
//    (core::part_box); its HitComp_ box (world::trigger_box) is the slab: about 0.6 m thick, as wide as the stairway,
//    the actor's own place its middle.
#include "floors.h"
#include "core/boxes.h"
#include "core/poi_text.h"
#include "core/strings.h"
#include "devserver.h"
#include "doors.h"
#include "ue/scan.h"
#include "seh.h"
#include "watch.h"
#include "world.h"
#include <algorithm>
#include <cmath>
#include <format>
#include <map>

namespace p3a::floors {
using namespace ue;
namespace {
using world::FVector;

uintptr_t owner() {
  if (!known_build()) return 0;
  return ((uintptr_t (*)())(scan::exe_base() + 0x11af780))();
}

// The field the owner is of, and the hero's part of it.
bool where(int& major, int& minor, int& part) {
  uintptr_t o = owner();
  if (!o) return false;
  part = (int)((uint32_t (*)(uintptr_t))(scan::exe_base() + 0x11addf0))(o);
  return guarded([&] { major = *(int32_t*)(o + 0x54); minor = *(int32_t*)(o + 0x58); });
}

struct Slab { UObject* a; int part; FVector at; };
std::vector<Slab> slabs() {
  static const int id = watch::want("FldHitCore", true);
  std::vector<Slab> v;
  for (UObject* a : watch::all(id)) {
    Slab s{a, core::part_box(name_of(get<UObject*>(a, "mOverlapBluePrint_"))), {}};
    if (!s.part || !world::actor_visible_level(a)) continue;
    if (guarded([&] { s.at = world::actor_location(a); })) v.push_back(s);
  }
  return v;
}
std::vector<core::PartBox> boxes(const std::vector<Slab>& s) {
  std::vector<core::PartBox> b;
  for (const Slab& x : s) b.push_back({x.part, world::vec3(x.at)});
  return b;
}
}  // namespace

int part() {
  uintptr_t o = owner();
  return o ? (int)((uint32_t (*)(uintptr_t))(scan::exe_base() + 0x11addf0))(o) : -1;
}

bool slab(UObject* hit) { return hit && core::part_box(name_of(get<UObject*>(hit, "mOverlapBluePrint_"))) != 0; }

// What elsewhere() worked out, kept while the hero stays in his part and on his side of the map's doors (a level
// coming or going counts there too).
static std::map<WeakObj::Key, bool> cache;
static std::vector<core::Box> other;   // the slabs that set another part than the hero's
static uint64_t side = ~0ull;
static int cur = -2;
static void refresh() {
  if (uint64_t s = doors::side_stamp(); s != side || part() != cur) {
    side = s;
    cur = part();
    cache.clear();
    other.clear();
    for (const Slab& x : slabs()) {
      core::Box b;
      if (x.part != cur && world::trigger_box(x.a, b)) other.push_back(b);
    }
  }
}

bool stairways() {
  refresh();
  return !other.empty() && cur > 0;
}

bool elsewhere(UObject* a, const FVector& me, const FVector& at) {
  if (!stairways()) return false;
  const auto key = WeakObj::of(a).key();
  if (auto it = cache.find(key); it != cache.end()) return it->second;
  bool through = false, partial = false;
  const std::vector<FVector> path = world::find_path(world::path_start(me), at, &partial);
  // The path runs on the stairs' floor, a slab hangs over them: sampled every 25 cm, with 1.5 m of leeway in height.
  for (size_t i = 1; !through && i < path.size(); ++i) {
    const core::Vec3 p = world::vec3(path[i - 1]), q = world::vec3(path[i]);
    const int n = std::max(1, (int)(core::dist3(p, q) / 25.0f));
    for (int k = 0; !through && k <= n; ++k) {
      const float u = (float)k / n;
      const core::Vec3 at_k{p.x + (q.x - p.x) * u, p.y + (q.y - p.y) * u, p.z + (q.z - p.z) * u};
      for (const core::Box& b : other) if (core::box_holds(b, at_k, 0.0f, 150.0f)) { through = true; break; }
    }
  }
  cache[key] = through;
  return through;
}

std::vector<Way> ways() {
  std::vector<Way> out;
  const int cur = part();
  if (cur <= 0) return out;
  const std::vector<Slab> s = slabs();
  if (s.empty()) return out;
  const std::vector<core::PartBox> b = boxes(s);
  for (size_t i : core::ways_from(b, cur))
    out.push_back({s[i].a, s[i].part});
  return out;
}

std::string name(const Way& w) { return strings::fmt(strings::kPoiStairsTo, w.to); }

void install() {
  dev::route("/floors", [](const dev::Request& r, int&) {
    // /floors | ?path=<object index> (the walking path to it, point by point)
    int to = (int)dev::arg_int(r, "path", -1);
    return dev::on_game([to] {
      int major = 0, minor = 0, p = -1;
      where(major, minor, p);
      std::string s = std::format("field {} {} part {}\n", major, minor, p);
      FVector me{};
      world::player_location(me);
      for (const Slab& x : slabs()) {
        core::Box b{};
        bool has = world::trigger_box(x.a, b);
        s += std::format("slab #{} {} sets part {} at ({:.0f}, {:.0f}, {:.0f}) box {:.0f} x {:.0f} x {:.0f} yaw {:.0f}{}\n", index_of(x.a), name_of(x.a), x.part,
                         x.at.x, x.at.y, x.at.z, b.extent.x * 2, b.extent.y * 2, b.extent.z * 2, b.yaw,
                         has && core::box_holds(b, world::vec3(me), 0.0f, 200.0f) ? "  hero inside" : "");
      }
      if (UObject* t = to >= 0 ? object_at(to) : nullptr) {
        bool partial = false;
        const FVector at = world::actor_location(t);
        s += std::format("path to #{} at ({:.0f}, {:.0f}, {:.0f}) elsewhere={}:", to, at.x, at.y, at.z, elsewhere(t, me, at));
        for (const FVector& q : world::find_path(world::path_start(me), at, &partial)) s += std::format(" ({:.0f}, {:.0f}, {:.0f})", q.x, q.y, q.z);
        s += partial ? " partial\n" : "\n";
      }
      for (const Way& w : ways()) s += std::format("way: {} -> part {} #{}\n", name(w), w.to, index_of(w.box));
      return s;
    });
  }, "?path=obj the field's part, the slabs that set it and the stairways on from here");
}
}  // namespace p3a::floors
