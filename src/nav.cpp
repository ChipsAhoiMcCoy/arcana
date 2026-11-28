#include "nav.h"
#include "nav_internal.h"
#include "core/approach.h"
#include "core/body_path.h"
#include "core/boxes.h"
#include "core/strings.h"
#include "devserver.h"
#include "doors.h"
#include "floors.h"
#include "hooks.h"
#include "input.h"
#include "keys.h"
#include "log.h"
#include "msg.h"
#include "poi.h"
#include "screens/screen.h"
#include "speech.h"
#include "seh.h"
#include "shadow.h"
#include "watch.h"
#include "world.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <format>
#include <memory>
#include <vector>

namespace p3a::nav {
using world::FVector;
using ue::WeakObj;

struct BodyPlanner;
// One walk's plan: everything here starts over with each walk (walk_to resets it by value).
struct Walk {
  WeakObj target;
  std::string name;
  std::vector<FVector> path;
  ULONGLONG path_at = 0, progress_at = 0;
  FVector progress_pos{};
  bool last_valid = false;   // the hero position of the previous walking tick is known
  FVector detour{};
  bool detour_on = false;
  int detours = 0;            // detours tried on this walk
  float detour_base = 0;      // the side first blocked on (radians from the target)
  bool direct = false;        // after a detour: straight for the target, not back along the path
  bool off_mesh = false;      // the target's own spot has no navmesh path: it stands inside something
  bool planned = false;       // the ways in were looked for on this walk
  std::vector<FVector> entries;   // a standing point outside each way in to the target, nearest first
  size_t entry_next = 0;
  FVector side{};             // a step to the side, round someone or something the path runs into
  bool side_on = false;
  int side_tries = 0;         // steps tried after getting stuck, with the target no nearer since
  float side_best = 1e9f;     // the nearest to the target the walk was when it got stuck
  // Inside a room the navmesh splits (classroom 2-F's desks): the path is the body's own way between the furniture,
  // planned once (again when blocked), and path[0] is the start of the leg being walked.
  bool body = false;
  int body_replans = 0;
  bool body_tried = false;    // a navmesh walk blocked on the way asked the body for a way once
  bool use = false;           // press Space at the target once its prompt is up (walk_to's use)
  ULONGLONG native_at = 0;    // direct movement began to be tried on this walk (while it is not known to work)
  ULONGLONG touch_at = 0;     // the hero came to a stop with his body in the target's box (see tick)
  // How it went (dev: /nav's last= line, the stress harness reads it).
  int id = 0;                 // counts walks this session
  ULONGLONG started_at = 0, ended_at = 0;
  std::string outcome;        // empty while walking
  float end_left = -1;        // cm from the target when it ended
  int sides = 0, entries_used = 0;
  long long plan_us_max = 0;  // the slowest frame of a body plan on this walk
  // A body plan under way (BodyPlanner, run a slice a frame while the hero stands), and what it was asked for.
  std::shared_ptr<BodyPlanner> planner;
  enum class PlanFor { Start, StartRoom, Blocked, Replan } plan_for = PlanFor::Start;
  bool stuck_now = false;     // a plan asked when blocked found nothing: on with the blocked checks at once
};
static Walk g_w;
static bool g_walking = false;
uint32_t g_held[2] = {0, 0};
// The stuck check starts again from here.
static void restart_progress(const FVector& me, ULONGLONG now) { g_w.progress_at = now; g_w.progress_pos = me; }
constexpr float kArrive = 110.0f;      // cm from the target's location
constexpr float kWaypointReached = 70.0f;

float flat(const FVector& a, const FVector& b) { return core::flat(world::vec3(a), world::vec3(b)); }

// Keys let go of while the game took no field input (a battle opening, a message window, a menu): the key-up reaches
// the window but not the player controller, which kept A held into a battle (the target wheel ran left every 100 ms,
// 2026-11-01; the battle reads PlayerController key state, BP_BtlGuiComponent CheckKeyboardInput). Each is let go
// again once the game takes input: the battle's command wheel, or the field with nothing over it.
static uint32_t g_owed[4] = {};
static bool g_taking_input = true;   // the game took field or battle input at this tick's start
static void owe(uint32_t k) {
  if (g_taking_input) return;
  for (uint32_t& o : g_owed) if (o == k) return;
  for (uint32_t& o : g_owed) if (!o) { o = k; return; }
}

static void hold(uint32_t a, uint32_t b) {
  uint32_t want[2] = {a, b};
  for (uint32_t k : g_held) if (k && k != a && k != b) { input::post_key(k, false, true); owe(k); }
  for (uint32_t k : want) if (k && k != g_held[0] && k != g_held[1]) input::post_key(k, true, true);
  g_held[0] = a; g_held[1] = b;
}
static void release() { hold(0, 0); }

// ---- steering ----
// The walk moves the hero by asking his pawn to go along a world direction each frame (AddMovementInput), the way the
// stick does after the game turns it by the camera: any angle, so the path is followed on its line rather than by
// the nearest of eight key directions, and no camera stands between (the hero's room, whose fixed camera faces 108
// degrees off north, ran every key walk into the walls, 2026-11-14). Whether the game takes it is seen on the first
// walk; if it does not, the walk steers with the movement keys as before, for the rest of the session.
Drive g_drive = Drive::Auto;   // dev: /nav?drive= (Drive: nav_internal.h)
int g_native = 0;              // direct movement: 0 not seen yet, 1 the hero moves by it, -1 ignored
static bool native_on() { return g_drive == Drive::Native || (g_drive == Drive::Auto && g_native >= 0); }
static bool body_clear(const FVector& a, const FVector& b, const FVector& me, float radius, float half);

static void steer_keys(const FVector& me, const FVector& wp) {
  // 8-way chord toward the waypoint, by the way the movement keys walk (world::move_yaw).
  float b = world::camera_bearing(me, wp);
  int sector = ((int)std::lround(b / 45.0f) % 8 + 8) % 8;
  static const uint32_t chords[8][2] = {{'W', 0}, {'W', 'D'}, {'D', 0}, {'S', 'D'}, {'S', 0}, {'S', 'A'}, {'A', 0}, {'W', 'A'}};
  hold(chords[sector][0], chords[sector][1]);
}

// The walk ends here, for `why` (kept for /nav's last= line).
static void finish(const char* why) {
  g_w.outcome = why;
  g_w.ended_at = GetTickCount64();
  FVector me{};
  if (ue::UObject* t = g_w.target.resolve(); t && world::player_location(me)) g_w.end_left = flat(me, world::actor_location(t));
}

void stop(bool announce) {
  bool was = g_walking;
  if (was && g_w.outcome.empty()) finish(announce ? "stopped" : "ended");
  g_walking = false;
  release();
  if (was && announce) speech::speak(strings::kStopped.c_str(), true);
}
bool walking() { return g_walking; }
// A walk that ends by using its target: Space is pressed once the game's prompt is up, until this time.
constexpr ULONGLONG kUseWaitMs = 1500;
static ULONGLONG g_use_until = 0;
static bool g_use_faced = false;   // turned to the target once he stood still (use_tick)
static void face(ue::UObject* t, const FVector& me);
// The walk reached its target: logged only (the player will give arrival its own cue; "Arrived" was spoken until
// 2026-10-31). A walk to use it waits for its prompt (use_tick). `can_use` false: a teleport next to it (stairs) was
// the target, already used.
static void arrived_at(bool can_use = true) {
  log::writef("nav: arrived, {}", g_w.name);
  if (g_w.use && can_use) { g_use_until = GetTickCount64() + kUseWaitMs; g_use_faced = false; }
}
// The prompt came up: Space, as a sighted player presses it. The player moving, or anything over the field, ends the
// wait; so does the time running out (an exit has no prompt: walking in is using it).
static void use_tick(bool in_field, ULONGLONG now) {
  if (!g_use_until) return;
  if (!in_field || keys::movement_key_down() || input::pad_moving()) { g_use_until = 0; return; }
  // Once the prompt has finished appearing (state 1 to 2) and the hero stands still: the press sent as it appeared
  // did nothing (the July hotel's mirror and its exit door, at 24 frames a second, 2026-11-24).
  FVector v{};
  bool still = !world::player_velocity(v) || std::hypot(v.x, v.y) < 1.0f;
  // Turned on arrival while still sliding, the hero turns back to the way he slides (his movement faces him along his
  // velocity), and the check's facing test (exe+0x11bf590) then fails: Elizabeth ended behind him, her prompt gone,
  // and the press did nothing (2026-11-24). Once he stands still he is turned to it again, and pressed after that.
  if (still && !g_use_faced) {
    g_use_faced = true;
    FVector me{};
    if (ue::UObject* t = g_w.target.resolve(); t && world::player_location(me)) { face(t, me); return; }
  }
  if (!poi::prompt().empty() && poi::prompt_settled() && still) {
    log::writef("nav: using {} (prompt {})", g_w.name, poi::prompt());
    input::inject_key(VK_SPACE, 80);
    g_use_until = 0;
    return;
  }
  if (now >= g_use_until) { log::writef("nav: no prompt at {}, nothing pressed", g_w.name); g_use_until = 0; }
}

// ---- off the floor's navmesh ----
// The navmesh leaves a margin round furniture wider than the hero, and he can stand in it: pressed against the
// playground see-saw at Naganaki Shrine, the floor's navmesh was 2.2 m off and the nearest navmesh at all a raised
// scrap on the see-saw (2026-11-17). Every path started from that scrap, came out partial and led back into the
// see-saw: each walk from there said "Stuck". The floor is his feet's height, give or take a step.
constexpr float kFloorBand = 40.0f;
FVector feet_of(const FVector& me) {
  float radius, half;
  hero_body(radius, half);
  return FVector{me.x, me.y, me.z - half};
}
// The floor's navmesh under him (within 30 cm), as a point at his height.
bool on_floor_nav(const FVector& me, FVector* at) {
  FVector on{};
  if (!world::project_to_nav(feet_of(me), 30.0f, on, kFloorBand)) return false;
  if (at) *at = on;
  return true;
}
// Off it: the nearest floor-level navmesh point his body reaches in a straight line from where he stands (the free
// side out of the margin), nearest first, within 3 m. `out` is at his height.
bool way_onto_floor_nav(const FVector& me, FVector& out) {
  float radius, half;
  hero_body(radius, half);
  FVector feet = feet_of(me), on{};
  std::vector<std::pair<float, FVector>> cands;
  if (world::project_to_nav(feet, 300.0f, on, kFloorBand)) cands.emplace_back(flat(on, me), on);
  for (int i = 0; i < 16; ++i)
    for (float r : {80.0f, 150.0f, 250.0f}) {
      float a = 6.28318531f * (float)i / 16.0f;
      if (world::project_to_nav(FVector{me.x + r * std::cos(a), me.y + r * std::sin(a), feet.z}, 50.0f, on, kFloorBand)) cands.emplace_back(flat(on, me), on);
    }
  std::sort(cands.begin(), cands.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
  for (auto& [d, p] : cands) {
    if (d < 20.0f) continue;
    // 20 cm past the edge, so he stands on it rather than at its rim.
    FVector s{p.x + (p.x - me.x) / d * 20.0f, p.y + (p.y - me.y) / d * 20.0f, me.z};
    if (body_clear(me, s, me, radius, half)) { out = s; return true; }
  }
  return false;
}

static bool refresh_path(const FVector& me) {
  ue::UObject* t = g_w.target.resolve();
  if (!t) return false;
  if (g_w.body) { g_w.path_at = GetTickCount64(); return true; }   // planned with the body, not the navmesh
  // On the way round to another side of the target, the path leads to that side's standing point.
  bool round = g_walking && g_w.detour_on;
  FVector to = round ? g_w.detour : world::actor_location(t);
  // From the floor's navmesh at his feet, not from whatever navmesh the engine finds nearest his middle (see above:
  // the see-saw's scrap was 33 cm from it, the floor 77): the floor point itself is the path's start. Off the
  // floor's navmesh, the nearest floor point within 3 m, walked to first.
  FVector start = world::path_start(me);
  g_w.path = world::find_path(start, to);
  if (!g_w.path.empty() && flat(start, me) > 30.0f) g_w.path.insert(g_w.path.begin(), FVector{start.x, start.y, me.z});
  if (!round) g_w.off_mesh = g_w.path.empty();
  // A thing standing off the navmesh (the entrance terminal, 2026-10-28) has no path to its centre: path to the
  // nearest navmesh point beside it, then head straight in. A story trigger can float well above its floor (the box
  // that starts the Takaya fight is 7 m over the ramp at the top of Tartarus, 2026-11-11: with no point within 3 m
  // the walk went straight at it, into the pillar the way leads round): the search widens once before giving up.
  FVector beside{};
  if (g_w.path.empty() && (world::project_to_nav(to, 300.0f, beside) || world::project_to_nav(to, 1200.0f, beside))) { g_w.path = world::find_path(start, beside); if (!g_w.path.empty()) g_w.path.push_back(to); }
  // Farther still from any navmesh: the game left a whole stretch out. Aigis on 7/21 waits up a forest trail past the
  // beach's navmesh, which ends in a straight line partway up the cliff path, 100 m short of her (2026-11-28); headed
  // straight at from the sand, the walk ran into the cliff and said "Stuck". The navmesh nearest her along the way
  // back towards the hero is where the walkable part ends: the path goes there, then on straight in.
  if (g_w.path.empty()) {
    const float dx = start.x - to.x, dy = start.y - to.y, d = std::hypot(dx, dy);
    for (float s = 1500.0f; s < d; s += 1500.0f) {
      FVector probe{to.x + dx / d * s, to.y + dy / d * s, to.z};
      if (!world::project_to_nav(probe, 1500.0f, beside, 3000.0f)) continue;
      bool partial = false;
      auto p = world::find_path(start, beside, &partial);
      if (p.empty() || partial) continue;
      g_w.path = std::move(p);
      g_w.path.push_back(to);
      static FVector logged{};   // the walk plans again every second or so: said once per point
      if (flat(logged, beside) > 500.0f)
        log::writef("nav: {} stands off the navmesh; its nearest walkable point is ({:.0f}, {:.0f}, {:.0f}), {:.0f} m short", g_w.name,
                    beside.x, beside.y, beside.z, flat(beside, to) / 100.0f);
      logged = beside;
      break;
    }
  }
  if (g_w.path.empty()) g_w.path.push_back(to);   // no navmesh here: head straight for it (the stuck check still guards)
  g_w.path_at = GetTickCount64();
  return true;
}

using core::Box;
using world::trigger_box;
// The point is inside the trigger, `margin` cm in from (negative) or out past its sides.
// Height too: a door upstairs is right above a spot downstairs (the dorm's "Your Room", 2026-10-27). The hero's
// location is about 90 cm above the floor; allow a step's worth more.
static bool inside(const Box& b, const FVector& p, float margin) { return core::box_holds(b, world::vec3(p), margin, 150.0f); }

// Where to head for the last of the way into a trigger box: its nearest point, 15 cm in from its side, not its centre.
// A box that stands in the wall (the radiator in the hero's room, 2026-11-14) has its centre behind the wall: heading
// there pressed the hero straight into it, 2 cm short of the box. Heading for its nearest point, he slides along the
// wall into it. Already over it (only the height is off): its centre.
static FVector box_aim(const Box& b, const FVector& me) {
  Box in = b;
  in.extent.x = std::max(0.0f, b.extent.x - 15.0f);
  in.extent.y = std::max(0.0f, b.extent.y - 15.0f);
  core::Vec3 p = core::box_nearest(in, world::vec3(me));
  FVector at{p.x, p.y, me.z};
  return flat(at, me) < 5.0f ? world::fvec(b.center) : at;
}

// ---- the ways in to a target that stands inside something solid ----
// A teleporter's trigger is a 64 cm box in the middle of the device, between two walls and four corner pillars: the
// hero gets in through a 96 cm gap on one side or a 67 cm one opposite, and nowhere else (Thebel 11, 2026-11-10).
// Circling it a sixth of a turn at a time from the side first bumped missed both gaps every time. The ways in are
// asked of the engine instead: the hero's own body swept toward the trigger from every side.
FVector centre(const Goal& g) { return g.has_box ? world::fvec(g.box.center) : g.at; }
// Arrived = inside the trigger box; a target without one = close to its location.
static bool reaches(const Goal& g, const FVector& p) { return g.has_box ? inside(g.box, p, -5.0f) : flat(g.at, p) < kArrive; }

void hero_body(float& radius, float& half) {
  radius = 26.5f; half = 85.0f;
  world::capsule_of(world::player(), radius, half);
}

static float path_length(const std::vector<FVector>& p) {
  float d = 0;
  for (size_t i = 1; i < p.size(); ++i) d += flat(p[i - 1], p[i]);
  return d;
}

// The hero's body swept a -> b at the height he walks at (`me` gives it): lifted off the floor by a step's height,
// as his own movement steps over a low edge. The characters it meets are looked past and listed in `people`.
static world::Hit sweep_body(const FVector& a, const FVector& b, const FVector& me, float radius, float half,
                             std::vector<ue::UObject*>& people) {
  float z = me.z + 10.0f, h = std::max(radius + 1.0f, half - 30.0f);
  return world::sweep(FVector{a.x, a.y, z}, FVector{b.x, b.y, z}, radius, h, &people);
}

// The body swept from `from` to the target's middle gets far enough to count as arrived. `me` gives the height.
bool sweep_reaches(const Goal& g, const FVector& from, const FVector& me, float radius, float half,
                   std::vector<ue::UObject*>& people) {
  world::Hit hit = sweep_body(from, centre(g), me, radius, half, people);
  if (hit.start_inside) return false;
  return !hit.hit || reaches(g, FVector{hit.location.x, hit.location.y, me.z});
}

// A standing point outside each way in, the shortest walk first. Empty: no side is open (or every side is).
std::vector<FVector> find_entries(const Goal& g, const FVector& me, std::string* report) {
  constexpr int kDirs = 72;   // 5 degrees apart: the narrow gap above is 8 degrees wide from its middle
  float radius, half;
  hero_body(radius, half);
  FVector c = centre(g);
  std::vector<ue::UObject*> people;   // party members and other characters do not close a way in
  // Where the hero can stand on that side, on the navmesh and clear of the walls, with a free run in from there.
  auto stand = [&](float a, float spare, FVector& out) {
    for (float r : {330.0f, 240.0f, 170.0f}) {
      FVector on{};
      if (!world::project_to_nav(FVector{c.x + r * std::cos(a), c.y + r * std::sin(a), me.z - half}, 60.0f, on)) continue;
      if (!sweep_reaches(g, on, me, radius + spare, half, people)) continue;
      out = FVector{on.x, on.y, me.z};
      return true;
    }
    return false;
  };
  struct Entry { FVector at; float walk; };
  std::vector<Entry> found;
  // First with 10 cm to spare on each side, so a gap the hero only just fits is left for last: the walk holds its
  // line to about that.
  for (float spare : {10.0f, 2.0f}) {
    std::vector<bool> clear(kDirs);
    std::vector<FVector> at(kDirs);
    for (int i = 0; i < kDirs; ++i) clear[i] = stand(6.28318531f * (float)i / kDirs, spare, at[i]);
    auto open = core::openings(clear);
    if (report) *report += std::format("spare {:.0f} cm: {} opening(s)\n", spare, open.size());
    if (open.size() == 1 && open[0].width > 6.2f) return {};   // open all round: nothing to find
    for (const core::Opening& o : open) {
      FVector s{};
      if (!stand(o.angle, spare, s)) s = at[o.index];
      bool partial = false;
      auto path = world::find_path(world::path_start(me), s, &partial);
      bool ok = !path.empty() && !partial;
      if (report)
        *report += std::format("  at {:.0f} deg, {:.0f} deg wide: stand at ({:.0f}, {:.0f}), {}\n", o.angle * 57.29578f, o.width * 57.29578f, s.x, s.y,
                               ok ? std::format("{:.0f} cm to walk", path_length(path)) : std::string("no path to it"));
      if (ok) found.push_back(Entry{s, path_length(path)});
    }
    if (!found.empty()) break;
  }
  std::sort(found.begin(), found.end(), [](const Entry& a, const Entry& b) { return a.walk < b.walk; });
  std::vector<FVector> out;
  for (const Entry& e : found) out.push_back(e.at);
  return out;
}

// ---- inside a room the navmesh splits ----
// Classroom 2-F's desks cut its navmesh into islands: from the back door the navmesh path to most desks leads out
// through one door and in at the other, though the hero fits between the desks (2026-11-12). Where the walking path
// meets a closed door but the thing is in sight over the furniture (doors.cpp), the way is planned with the hero's own
// body: a grid of floor points turned to the camera, so every leg is one of the eight walking directions, and the
// capsule swept from each point to the next at the height he walks at. People block here (the seated students sit at
// the aisles' ends); the target is reached from inside its trigger, so its own body is no matter.
constexpr float kBodyReach = 2500.0f;   // the furthest a walk plans with the body alone (a room, not a district)
// Floor under every 30 cm of the legs, at most a step (35 cm) below the hero's feet (`me` his middle, `half` his half
// height). `off`: the first point without.
static bool on_floor(const std::vector<FVector>& pts, const FVector& me, float half, FVector& off) {
  float feet = me.z - half;
  for (size_t i = 0; i < pts.size(); ++i) {
    const FVector& a = pts[i];
    const FVector& b = i + 1 < pts.size() ? pts[i + 1] : pts[i];
    int n = std::max(1, (int)std::ceil(flat(a, b) / 30.0f));
    for (int k = 0; k <= n; ++k) {
      float t = (float)k / (float)n;
      FVector p{a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, me.z};
      if (!world::line(p, FVector{p.x, p.y, feet - 35.0f}).hit) { off = p; return false; }
    }
  }
  return true;
}
// The search runs in slices: a plan in 2-F took 9000 grid points and 22 ms of sweeps, all in one frame, and a plan
// that found nothing (Officer Kurosawa, behind Paulownia Mall's police station wall) spent its whole budget, 21 ms
// (2026-11-23). The walk stands while it plans, a slice a frame, each asking at most kSweepsPerFrame moves (a sweep
// is about 1.3 us).
constexpr int kSweepsPerFrame = 2500;
struct BodyPlanner {
  Goal g;
  FVector me;
  bool past_people = false;
  float radius = 26.5f, half = 85.0f, yaw = 0, reach = 0, z = 0, h = 0;
  int spare_i = 0;   // kSpares[spare_i] is being searched
  std::unique_ptr<core::BodySearch> s;
  long long us = 0, slice_max = 0;
  std::string* report = nullptr;
  // First with room to spare, so the walk's eight directions have some slack; then as close as the body fits: the
  // aisles between 2-F's desks leave his middle a band about 10 cm wide (measured with /nav?map, 2026-11-12), which a
  // coarser grid steps over.
  static constexpr float kSpares[2] = {6.0f, 0.0f};
  BodyPlanner(const Goal& goal, const FVector& at, bool past) : g(goal), me(at), past_people(past) {
    hero_body(radius, half);
    yaw = world::move_yaw() * 3.14159265f / 180.0f;   // the legs follow the keys' eight directions
    reach = flat(me, centre(g)) + 800.0f;
    z = me.z + 10.0f;
    h = std::max(radius + 1.0f, half - 30.0f);
  }
  // 1: found (`out` holds it), -1: none, 0: not done yet (call again next frame).
  int step(int budget, std::vector<FVector>& out) {
    FVector c = centre(g);
    // A trigger can sit inside the thing (a bookshelf's is in the shelf): the plan ends where the body touches its
    // side, and the walk presses on into it (its prompt coming up is arriving).
    auto arrived = [&](core::Vec2 p) { FVector at{p.x, p.y, me.z}; return reaches(g, at) || (g.has_box && inside(g.box, at, radius + 10.0f)); };
    while (spare_i < 2) {
      float spare = kSpares[spare_i];
      std::vector<ue::UObject*> people;
      auto clear = [&](core::Vec2 a, core::Vec2 b) { return !world::sweep(FVector{a.x, a.y, z}, FVector{b.x, b.y, z}, radius + spare, h, past_people ? &people : nullptr).hit; };
      if (!s) s = std::make_unique<core::BodySearch>(core::Vec2{me.x, me.y}, core::Vec2{c.x, c.y}, 10.0f, yaw, 12000, reach);
      LARGE_INTEGER t0, t1, f;
      QueryPerformanceCounter(&t0);
      bool done = s->step(budget, clear, arrived);
      QueryPerformanceCounter(&t1);
      QueryPerformanceFrequency(&f);
      long long slice = (t1.QuadPart - t0.QuadPart) * 1000000 / f.QuadPart;
      us += slice;
      slice_max = std::max(slice_max, slice);
      if (!done) return 0;
      const core::BodyPlan& plan = s->plan();
      log::writef("nav: body plan, spare {:.0f} cm: {}, {} points expanded, {} sweeps, {} us (slowest frame {} us)", spare,
                  plan.found ? std::format("{} legs", plan.points.size() - 1) : std::string("none"), plan.expanded, plan.tested, us, slice_max);
      if (report) {
        *report += std::format("spare {:.0f} cm: {}, {} expanded, {} sweeps, {} us\n", spare, plan.found ? "found" : "none", plan.expanded, plan.tested, us);
        for (core::Vec2 p : plan.points) *report += std::format("  ({:.0f}, {:.0f})\n", p.x, p.y);
      }
      if (!plan.found) {
        s.reset();
        us = 0;
        ++spare_i;
        if (budget != INT_MAX) return spare_i < 2 ? 0 : -1;   // the next spare from the next frame
        continue;
      }
      out.clear();
      for (core::Vec2 p : plan.points) out.push_back(FVector{p.x, p.y, me.z});
      // The capsule is swept at the hero's height, so the plan knows walls and not floors: on the dorm's 2F landing it
      // ran straight out over the stairs down (the hero walked down them into their trigger, "It's not safe down
      // below...", 2026-11-16). A plan that leaves his floor is no plan: every 30 cm along it there must be floor no
      // more than a step below his feet.
      if (FVector off{}; !on_floor(out, me, half, off)) {
        log::writef("nav: body plan leaves the floor at ({:.0f}, {:.0f}): not taken", off.x, off.y);
        if (report) *report += std::format("  leaves the floor at ({:.0f}, {:.0f}): not taken\n", off.x, off.y);
        return -1;
      }
      return 1;
    }
    return -1;
  }
};
// All at once (the dev route).
bool body_plan(const Goal& g, const FVector& me, std::vector<FVector>& out, std::string* report, bool past_people) {
  BodyPlanner p(g, me, past_people);
  p.report = report;
  return p.step(INT_MAX, out) == 1;
}
Goal goal_of(ue::UObject* t) {
  Goal g;
  g.has_box = trigger_box(t, g.box);
  g.at = world::actor_location(t);
  return g;
}

void walk_to(const WeakObj& target, const std::string& name, bool use) {
  g_use_until = 0;
  static int walks = 0;
  if (g_walking) stop(false);   // the walk under way gives way to this one (or ends, if this one is refused)
  g_w = Walk{};   // a new walk's plan starts empty; the keys held and g_walking are not part of it
  g_w.id = ++walks;
  g_w.target = target;
  g_w.name = name;
  g_w.started_at = GetTickCount64();
  FVector me;
  static const int battle = watch::want("BtlCoreComponent");
  if (!world::player_location(me) || watch::get(battle)) { finish("refused: not in the field"); speech::speak(strings::kNotInField.c_str(), true); return; }
  ue::UObject* t = target.resolve();
  // Past a closed door: the navmesh runs on under it, so there is a path, and it ends against the door ("Stuck",
  // the gym hallway, 2026-11-11).
  // In this room with no path inside it (classroom 2-F's desks): the hero's own body finds the way between the
  // furniture; with none, said so and the player walks the last of it.
  bool plan_body = false;
  FVector via{};
  doors::Way way = t ? doors::walk_way(t, me, world::actor_location(t), &via) : doors::Way::open;
  if (way == doors::Way::behind) { finish("refused: behind a door"); speech::speak(strings::kNoPath.c_str(), true); return; }
  if (way == doors::Way::in_room) {
    plan_body = true;
  } else if (way == doors::Way::other_side) {
    // Set in a wall, its path ending behind the wall through a closed door (the Printing Room's sign on the school's
    // 2F): round to the side it is pressed from as to a way in (the path leads there while detour_on), then straight in.
    g_w.detour = via;
    g_w.detour_on = true;
    log::writef("nav: {} is reached from ({:.0f}, {:.0f}), not through the door behind it", name, via.x, via.y);
  } else if (t && flat(me, world::actor_location(t)) < kBodyReach) {
    // No navmesh path, or one that stops short, to something close by: the hero stands in an aisle the navmesh left
    // out (between 2-F's desks), or the thing does. The body's own way, if it has one; else the walk as before.
    FVector at = world::actor_location(t), beside{};
    bool partial = false;
    auto path = world::find_path(world::path_start(me), at, &partial);
    if (path.empty() && world::project_to_nav(at, 300.0f, beside)) path = world::find_path(world::path_start(me), beside, &partial);
    // A partial path that ends under the target reaches it: a stairway's trigger floats over the steps, off the
    // navmesh, so the path to it is always partial. Taken for "stops short", it sent the walk to the 3F stairs on the
    // body's way out over the stairs down (2026-11-16); the navmesh's path goes round by the landing.
    Goal g = goal_of(t);
    bool under = !path.empty() && (g.has_box ? core::box_holds(g.box, world::vec3(path.back()), 50.0f, 400.0f) : flat(path.back(), at) < kArrive);
    plan_body = path.empty() || (partial && !under);
  }
  g_w.use = use;
  if (!refresh_path(me)) { finish("refused: no path"); speech::speak(strings::kNoPath.c_str(), true); return; }
  // The body's own way is planned over the next frames, the hero standing meanwhile (see BodyPlanner).
  if (plan_body) {
    g_w.planner = std::make_shared<BodyPlanner>(goal_of(t), me, false);
    g_w.plan_for = way == doors::Way::in_room ? Walk::PlanFor::StartRoom : Walk::PlanFor::Start;
  }
  // Standing off the floor's navmesh (in the margin round a piece of furniture): out onto it first, by the free side.
  if (!plan_body && !on_floor_nav(me) && way_onto_floor_nav(me, g_w.side)) {
    g_w.side_on = true;
    log::writef("nav: off the floor's navmesh at ({:.0f}, {:.0f}), out via ({:.0f}, {:.0f})", me.x, me.y, g_w.side.x, g_w.side.y);
  }
  g_walking = true;
  if (g_w.detour_on) refresh_path(me);   // round to the other side from the first step (refresh_path heads there only once walking)
  restart_progress(me, GetTickCount64());
  // Nothing is said on starting: "Auto-pathing" was (2026-11-14), and was dropped as redundant (the user's call,
  // 2026-11-15). Arriving has no word of its own either: the target's prompt says it.
}

// ---- round what the path runs into ----
// The navmesh knows the walls and nothing of who stands on the floor: a path down a hallway ran straight into a
// student walking the other way, and the walk pushed against them until it said "Stuck" (the Gym Hallway,
// 2026-11-11). The same goes for anything solid the navmesh was not cut round. The hero's body is swept ahead as
// the game would move it, and when it would not get through, a step to one side is looked for.

// Someone the body would walk into going a -> b. A person beside or behind the start does not count: the hero may
// be touching them already, and walks away from them.
static bool walks_into(const FVector& a, const FVector& b, const std::vector<ue::UObject*>& people, const FVector* goal = nullptr) {
  float len = flat(a, b);
  for (ue::UObject* p : people) {
    FVector at = world::actor_location(p);
    float d = flat(a, at);
    // The person the walk is going to (a character's body is another actor than its talk trigger) is not in the way.
    if (goal && flat(at, *goal) < 200.0f) continue;
    if (d < 1.0f || len < 1.0f) return true;
    if (((b.x - a.x) * (at.x - a.x) + (b.y - a.y) * (at.y - a.y)) / (len * d) > 0.3f) return true;
  }
  return false;
}
// The body can go a -> b: nothing solid on the way and nobody to walk into. `me` gives the height.
static bool body_clear(const FVector& a, const FVector& b, const FVector& me, float radius, float half) {
  std::vector<ue::UObject*> people;
  world::Hit hit = sweep_body(a, b, me, radius, half, people);
  return !hit.hit && !walks_into(a, b, people);
}
// Somebody stands in the next stretch toward the waypoint.
static bool person_ahead(const FVector& me, const FVector& wp, const FVector& goal) {
  float d = flat(me, wp);
  if (d < 1.0f) return false;
  float radius, half;
  hero_body(radius, half);
  float k = std::min(d, 150.0f) / d;
  FVector to{me.x + (wp.x - me.x) * k, me.y + (wp.y - me.y) * k, me.z};
  std::vector<ue::UObject*> people;
  sweep_body(me, to, me, radius, half, people);
  return !people.empty() && walks_into(me, to, people, &goal);
}
// A point to one side that the body can step to and walk on from toward the waypoint: the smallest turn off the
// line first, either side, then further out. `skip` passes over that many that would do (the ones tried already).
static bool find_sidestep(const FVector& me, const FVector& wp, int skip, FVector& out, bool back = false) {
  float radius, half;
  hero_body(radius, half);
  float heading = std::atan2(wp.y - me.y, wp.x - me.x);
  for (float r : {120.0f, 180.0f, 260.0f})
    // `back`: last, back the way he came, once stuck: pressed into a corner, every way forward is shut (the see-saw,
    // 2026-11-17). Never to step round someone ahead: in the dorm's narrow 3F hallway that walked him back, then on
    // into the same person, over and over, never stuck (2026-11-23).
    for (float deg : {45.0f, -45.0f, 70.0f, -70.0f, 90.0f, -90.0f, 120.0f, -120.0f, 150.0f, -150.0f, 180.0f}) {
      if (!back && std::fabs(deg) > 120.0f) continue;
      float a = heading + deg * 3.14159265f / 180.0f;
      FVector on{};
      if (!world::project_to_nav(FVector{me.x + r * std::cos(a), me.y + r * std::sin(a), me.z - half}, 40.0f, on)) continue;
      FVector s{on.x, on.y, me.z};
      if (flat(s, me) < 60.0f || !body_clear(me, s, me, radius, half)) continue;
      float d = flat(s, wp);
      if (d < 30.0f) continue;
      float k = std::min(d, 250.0f) / d;
      if (!body_clear(s, FVector{s.x + (wp.x - s.x) * k, s.y + (wp.y - s.y) * k, me.z}, me, radius, half)) continue;
      if (skip-- > 0) continue;
      out = s;
      return true;
    }
  return false;
}

// The game shows a hit actor's prompt only while the hero faces the way its mHeroDirectType_ asks: Back = against
// the actor's own forward (into the door; the faculty office door, yaw -90, wants the hero at yaw 90, measured
// 2026-10-27), Front = along it, Left/Right = a quarter turn, Center = toward its location. BackNG (a seated Social
// Link partner) is Center too, refused only from within 10 degrees of straight behind the actor (the game's check,
// exe+0x11bf590; turned as Back, the hero stood beside Kenji's desk looking away and no prompt came, 2026-11-11).
// Turn the hero that way on arrival, as a sighted player would.
static void face(ue::UObject* t, const FVector& me) {
  // Things without a facing rule (Tartarus' breakables) are faced straight on, so a strike lands.
  std::string type = ue::find_prop(ue::class_of(t), "mHeroDirectType_") ? ue::enum_prop_name(t, "mHeroDirectType_") : "Center";
  float yaw = world::yaw_of(t);
  if (type == "Back") yaw += 180.0f;
  else if (type == "Left") yaw -= 90.0f;
  else if (type == "Right") yaw += 90.0f;
  else if (type == "Center" || type == "BackNG") { FVector a = world::actor_location(t); yaw = std::atan2(a.y - me.y, a.x - me.x) * 180.0f / 3.14159265f; }
  else if (type != "Front") return;
  ue::UObject* hero = world::player();
  if (!hero) return;
  ue::Params sp(ue::find_function(ue::class_of(hero), "K2_SetActorRotation"));
  sp.set<ue::FRotator>("NewRotation", ue::FRotator{0.0f, yaw, 0.0f});
  ue::call(hero, sp);
}

// Toward the waypoint this frame: directly, or by the keys where the game does not take that.
static void steer(const FVector& me, const FVector& wp, ULONGLONG now) {
  if (native_on()) {
    float dx = wp.x - me.x, dy = wp.y - me.y, d = std::hypot(dx, dy);
    release();   // no keys while steering directly (a fallback's chord let go)
    if (d > 1.0f) world::add_move_input(FVector{dx / d, dy / d, 0.0f}, 1.0f);
    if (g_native == 0 && g_drive == Drive::Auto && d > 1.0f) {
      // Taken: the hero moves along the direction asked. Not taken: still, with nothing in his way that direction
      // for 600 ms (a wall in the way decides nothing: the keys would not move him either).
      if (!g_w.native_at) g_w.native_at = now;
      FVector v{};
      float speed = world::player_velocity(v) ? std::hypot(v.x, v.y) : 0.0f;
      if (speed > 30.0f && (v.x * dx + v.y * dy) / (speed * d) > 0.5f) {
        g_native = 1;
        log::write("nav: the game takes direct movement: the walk steers at any angle");
      } else if (now - g_w.native_at > 600) {
        float radius, half;
        hero_body(radius, half);
        float k = std::min(d, 60.0f) / d;
        if (body_clear(me, FVector{me.x + dx * k, me.y + dy * k, me.z}, me, radius, half)) {
          g_native = -1;
          log::write("nav: the game ignores direct movement: the walk steers with the movement keys");
        } else {
          g_w.native_at = now;   // blocked: look again
        }
      }
    }
    if (native_on()) return;
  }
  steer_keys(me, wp);
}

// The next waypoint not yet reached (the path's first point is our own projected position).
static bool next_waypoint(const FVector& me, FVector& out) {
  while (g_w.path.size() > 1 && flat(g_w.path.front(), me) < kWaypointReached) g_w.path.erase(g_w.path.begin());
  if (g_w.path.empty()) return false;
  out = g_w.path.front();
  return true;
}

void tick() {
  FVector me;
  // A menu up over the field (an exit's "Where should I go?" crossed on the way, a scripted area map; 2026-10-28)
  // holds the walk like a message window: held keys would move its cursor.
  bool located = world::player_location(me), blocking = msg::current().blocking || screens::current();
  // A battle (a Shadow met on the way) keeps the field hero but ends the walk: between turns no screen is up, and the
  // held keys went on into the fight (W tactics, A and D the target) until it said "Stuck" (2026-11-01).
  static const int battle = watch::want("BtlCoreComponent");
  bool fighting = watch::get(battle) != nullptr;
  bool in_field = located && !blocking && !fighting;
  ULONGLONG now = GetTickCount64();
  dev_tick(now);
  static const int gui = watch::want("BtlGuiStateManager");
  ue::UObject* g = watch::get(gui);
  bool battle_input = fighting && g && ue::get<uint8_t>(g, "nowState") != 0;
  g_taking_input = in_field || battle_input;
  if (g_taking_input) {
    for (uint32_t& o : g_owed)
      if (o) {
        if (o != g_held[0] && o != g_held[1]) { input::post_key(o, false, true); log::writef("nav: let go of {:#x} again", o); }
        o = 0;
      }
  }
  use_tick(in_field, now);
  if (g_walking) {
    if (!located) { finish("hero gone"); stop(false); return; }
    if (fighting) { log::write("nav: stopped, a battle began"); finish("battle"); stop(false); return; }
    // A message window or a menu over the field ends the walk, without a word over what it says (the user's call,
    // 2026-11-09). It used to wait and walk on: Mitsuru's "Hold on. It's not safe to continue any further" turns the
    // hero back from a blocked way, and the walk took him straight into it again, over and over.
    if (blocking) { log::write("nav: stopped, a message or a menu came up"); finish("message or menu"); stop(false); return; }
    // So does a story scene the walk ran into: the 7/21 chase after Aigis plays a short one at each bend of the path
    // ("the girl runs on, farther up the path"), with no message window; the walk pushed on against the scene and said
    // "Stuck" over its description (2026-11-28).
    if (world::scene_playing()) { log::write("nav: stopped, a story scene began"); finish("scene"); stop(false); return; }
    if (keys::movement_key_down()) { log::write("nav: stopped, a movement key is held"); stop(true); return; }   // the player took over
    if (input::pad_moving()) { log::write("nav: stopped, the controller's stick is pushed"); stop(true); return; }
    // Stairs and doors are area changes that move the hero to another part of the map in one frame; the walk ends
    // there (otherwise it re-paths from the new floor and runs on through the next staircase).
    static FVector last{};
    bool jumped = g_w.last_valid && std::fabs(me.x - last.x) + std::fabs(me.y - last.y) + std::fabs(me.z - last.z) > 400.0f;
    FVector before = last;
    last = me; g_w.last_valid = true;
    ue::UObject* t = g_w.target.resolve();
    if (!t) { log::write("nav: stopped, the target is gone"); finish("target gone"); stop(true); return; }
    FVector goal = world::actor_location(t);
    // A teleport taken next to the target was the target (stairs); one taken on the way (the path crossed another
    // exit, the back alley's, 2026-10-27) only moved the hero: plan again from there. Where the hero stood before the
    // jump decides, not where he landed: the alley's exit drops him 7 m from the Velvet Room's door, which ended the
    // walk short of it (2026-11-12).
    if (jumped) {
      Box tb{};
      // Someone standing about (no trigger of their own) is never reached through a teleport: the exit taken was on
      // the way, and the place's name the game says tells the player where it led. Planning on from the far side of
      // it walked on through the next part of the map.
      if (!trigger_box(t, tb)) { finish("area change on the way"); stop(false); return; }
      if (flat(goal, before) < 800.0f) { finish("arrived (area change)"); stop(false); arrived_at(false); return; }
      g_w.side_on = false;
      g_w.body = false;   // a plan between the furniture was for the room he left: the navmesh's from here
      refresh_path(me);
      restart_progress(me, now);
    }
    // A hit actor is usable from inside its trigger box, which can reach well past its centre point (the bed's box
    // is 1.3 x 1.4 m): arrived = inside the box; anything else = close to the location.
    Box box;
    bool has_box = trigger_box(t, box);
    bool arrived = has_box ? inside(box, me, -5.0f) : flat(goal, me) < kArrive;
    // A stairway's slab is reached once the game has moved the hero to the floor it sets (walking into it does): the
    // box's height leeway reached through floors. The Strip Mall's east slab down to 1F hangs under the 2F walkway,
    // and the walk "arrived" on 2F standing over it (2026-11-28).
    const int stair_part = floors::sets(t);
    if (stair_part) arrived = floors::part() == stair_part;
    // A box mostly inside the wall (the radiator and the mirror in the hero's room, 2026-11-14): the wall stops his
    // middle 2 to 5 cm short of it, though his body is in it. Stopped there for a moment is arriving: turned to it, the
    // game's prompt comes up (pressed still against the wall, he never turned, and the walk said "Stuck").
    if (!arrived && has_box && !stair_part) {
      float radius, half;
      hero_body(radius, half);
      FVector v{};
      bool still = world::player_velocity(v) && std::hypot(v.x, v.y) < 60.0f;
      if (inside(box, me, radius) && still) {
        if (!g_w.touch_at) g_w.touch_at = now;
        arrived = now - g_w.touch_at >= 250;
      } else {
        g_w.touch_at = 0;
      }
    }
    // The target's own prompt is up: arriving, wherever its box was thought to be. A body plan ends beside a trigger
    // inside the thing (the bookshelf's); a shop's vendor talks from behind the counter, which stops the hero 30 cm
    // short of the box read for him, with his prompt already up (the School Store, 2026-11-23: the walk pushed on
    // into the counter for 1.5 s, then circled the store six times). Near the target only: names repeat (2-F's two
    // bookshelves), and the walk to the far one passes the near one's prompt.
    bool near_target = has_box ? inside(box, me, 150.0f) : flat(goal, me) < 300.0f;
    // Stopped on its prompt, the hero still faces the way he walked: the prompt came up for his heading as he passed, and
    // as he slowed it could go again (Elizabeth in the back alley: arrived facing the Velvet Room door, 15 cm from her, no
    // prompt, Space did nothing, 2026-11-24). Turned the way its check asks, as on every other arrival.
    if (!arrived && near_target && poi::prompt() == g_w.name) { finish("arrived (prompt)"); stop(false); face(t, me); arrived_at(); return; }
    // A breakable thing (Tartarus' Shadow remains) is reached once the strike would break it: he stops there turned to
    // it, the strike's ring sounds, and Ctrl breaks it. They stand in rings: walking on into the middle of one, the
    // others blocked him and the walk said "Stuck" (2026-11-24). Nothing to use: no Space.
    if (float yaw = 0.0f; shadow::strike_reaches(t, me, yaw)) {
      finish("arrived (strike reach)");
      stop(false);
      if (ue::UObject* hero = world::player()) {
        ue::Params sp(ue::find_function(ue::class_of(hero), "K2_SetActorRotation"));
        sp.set<ue::FRotator>("NewRotation", ue::FRotator{0.0f, yaw, 0.0f});
        ue::call(hero, sp);
      }
      arrived_at(false);
      return;
    }
    if (arrived) { finish("arrived"); stop(false); face(t, me); arrived_at(); return; }
    Goal target{has_box, box, goal};
    // The next way in: walk round to its standing point (the path leads there while g_w.detour_on), then straight in.
    auto next_entry = [&] {
      if (g_w.entry_next >= g_w.entries.size()) return false;
      g_w.detour = g_w.entries[g_w.entry_next++];
      ++g_w.entries_used;
      g_w.detour_on = true;
      g_w.direct = false;
      refresh_path(me);
      restart_progress(me, now);
      log::writef("nav: way in {} of {} via ({:.0f}, {:.0f})", g_w.entry_next, g_w.entries.size(), g_w.detour.x, g_w.detour.y);
      return true;
    };
    // A navmesh walk blocked on the way goes on by the body's own way, if it has one (asked once a walk).
    auto to_body = [&] {
      if (g_w.body || g_w.body_tried || flat(goal, me) > kBodyReach) return false;
      g_w.body_tried = true;
      g_w.planner = std::make_shared<BodyPlanner>(target, me, false);
      g_w.plan_for = Walk::PlanFor::Blocked;
      release();
      restart_progress(me, now);
      return true;
    };
    auto plan = [&] {
      g_w.planned = true;
      g_w.entries = find_entries(target, me);
      g_w.entry_next = 0;
      log::writef("nav: {} way(s) in to {}", g_w.entries.size(), g_w.name);
    };
    // A body plan under way: the hero stands while it runs, a slice a frame; then the walk goes on as it was asked.
    if (g_w.planner) {
      release();
      restart_progress(me, now);
      std::vector<FVector> pts;
      int r = g_w.planner->step(kSweepsPerFrame, pts);
      g_w.plan_us_max = std::max(g_w.plan_us_max, g_w.planner->slice_max);
      if (r == 0) return;
      g_w.planner.reset();
      bool found = r == 1;
      switch (g_w.plan_for) {
        case Walk::PlanFor::StartRoom:
          if (!found) { finish("refused: no way in the room"); stop(false); speech::speak(strings::kNoPathInRoom.c_str(), true); return; }
          [[fallthrough]];
        case Walk::PlanFor::Start:
          if (found) { g_w.body = true; g_w.path = std::move(pts); g_w.side_on = false; }
          break;
        case Walk::PlanFor::Blocked:
          if (found) {
            g_w.body = true;
            g_w.path = std::move(pts);
            g_w.detour_on = g_w.direct = g_w.side_on = false;
            log::writef("nav: blocked at ({:.0f}, {:.0f}), on by the body's own way", me.x, me.y);
          } else {
            g_w.stuck_now = true;   // still blocked: on with the other ways round, now
          }
          break;
        case Walk::PlanFor::Replan:
          if (found && pts.size() > 1) {
            ++g_w.body_replans;
            g_w.path = std::move(pts);
            log::writef("nav: blocked at ({:.0f}, {:.0f}), planned again", me.x, me.y);
            break;
          }
          // A plan of no legs: the body touches the thing's box here, so the plan calls him there, but the game's
          // prompt is not up (its talk trigger faces another side: the Suspicious Man in Club Escapade, where the walk
          // planned none twice and said "Stuck", 2026-11-17). The body's way is done; on as a walk blocked close to
          // the target goes: round to the sides it can be come in from.
          if (!found) {
            finish("stuck (no body plan)");
            stop(false);
            speech::speak(strings::kStuck.c_str(), true);
            return;
          }
          log::writef("nav: at ({:.0f}, {:.0f}) the plan says arrived, no prompt: round to another side", me.x, me.y);
          g_w.body = false;
          g_w.body_tried = true;
          refresh_path(me);
          g_w.stuck_now = true;
          break;
      }
      return;
    }
    // A target with no navmesh path to its own spot stands inside something. Close to it, before bumping into it:
    // when the hero's body cannot run straight in from here, find the sides it can come in from.
    if (g_w.off_mesh && !g_w.planned && flat(centre(target), me) < 500.0f) {
      float radius, half;
      hero_body(radius, half);
      std::vector<ue::UObject*> people;
      if (sweep_reaches(target, me, me, radius, half, people)) g_w.planned = true;
      else { plan(); next_entry(); }
    }
    // The step to the side is taken: back on the path from there.
    if (g_w.side_on && flat(g_w.side, me) < 45.0f) { g_w.side_on = false; refresh_path(me); }
    if (now - g_w.path_at > 700) refresh_path(me);
    FVector wp;
    if (g_w.body) {
      // Leg by leg, held to its line (core::follow): a leg is done at its end or once past it.
      while (g_w.path.size() > 1) {
        const FVector &a = g_w.path[0], &b = g_w.path[1];
        float len = flat(a, b), along = len < 1.0f ? 0.0f : ((me.x - a.x) * (b.x - a.x) + (me.y - a.y) * (b.y - a.y)) / len;
        if (flat(b, me) < 20.0f || along > len - 5.0f) g_w.path.erase(g_w.path.begin());
        else break;
      }
      if (g_w.path.size() > 1) {
        core::Vec2 w = core::follow(core::Vec2{g_w.path[0].x, g_w.path[0].y}, core::Vec2{g_w.path[1].x, g_w.path[1].y}, core::Vec2{me.x, me.y}, 35.0f);
        wp = FVector{w.x, w.y, me.z};
      } else {
        wp = has_box ? box_aim(box, me) : goal;   // the plan's end is in the trigger: on into it
      }
    } else if (!next_waypoint(me, wp)) { log::write("nav: stopped, no path"); finish("no path"); stop(true); return; }
    if (g_w.body) {
      // Steered above: no detours or ways in on a plan the body made.
    } else if (g_w.detour_on) {
      // Round to another side of the target: at its standing point, turn in.
      if (flat(g_w.detour, me) < 80.0f) { g_w.detour_on = false; g_w.direct = true; refresh_path(me); }
    } else if (g_w.direct) {
      // Straight in from there, held to the line: a way in can be a gap with 20 cm to spare on each side.
      FVector c = centre(target);
      core::Vec2 w = core::follow(core::Vec2{g_w.detour.x, g_w.detour.y}, core::Vec2{c.x, c.y}, core::Vec2{me.x, me.y}, 40.0f);
      wp = FVector{w.x, w.y, me.z};
    } else if (g_w.path.size() == 1 && flat(wp, me) < kWaypointReached + 30.0f && has_box) {
      // The navmesh path ends where the floor ends (beside the bed); from its last point head straight for the box.
      wp = box_aim(box, me);
    }
    // Somebody in the way is stepped round before the hero walks into them.
    FVector on_path = wp;
    if (!g_w.body && !g_w.side_on && !g_w.direct && person_ahead(me, wp, goal) && find_sidestep(me, wp, 0, g_w.side)) {
      g_w.side_on = true;
      log::writef("nav: someone in the way at ({:.0f}, {:.0f}), round via ({:.0f}, {:.0f})", me.x, me.y, g_w.side.x, g_w.side.y);
    }
    if (g_w.side_on) wp = g_w.side;
    steer(me, wp, now);
    if (g_w.stuck_now || now - g_w.progress_at > 1500) {
      bool recheck = g_w.stuck_now;
      g_w.stuck_now = false;
      if (recheck || flat(me, g_w.progress_pos) < 40.0f) {
        // Blocked by the thing itself (a chest's collision) while its prompt is already up: that is arriving.
        bool there = poi::prompt() == g_w.name;
        // A walk between the furniture plans its way again from where it stopped, twice.
        if (!there && g_w.body) {
          if (g_w.body_replans >= 2) {
            finish("stuck (body plan)");
            stop(false);
            speech::speak(strings::kStuck.c_str(), true);
            return;
          }
          g_w.planner = std::make_shared<BodyPlanner>(target, me, false);
          g_w.plan_for = Walk::PlanFor::Replan;
          release();
          restart_progress(me, now);
          return;
        }
        // Blocked close to it (the teleporter pad's pylons, 2026-10-27; the entrance terminal opens only to one
        // side, 2026-10-28): come in through the next way in the engine's sweeps found.
        if (!there && flat(goal, me) < 600.0f) {
          log::writef("nav: blocked at ({:.0f}, {:.0f})", me.x, me.y);
          if (!g_w.planned) plan();
          if (next_entry()) return;
          // No way in the sweeps found from round about: the body's own way from here (Junpei's desk in 2-F, where
          // the navmesh path ends in the aisle beside the next desk, 2026-11-12).
          if (to_body()) return;
          // No side the sweeps call open (the target's box may be reached some other way): circle round and come
          // in from another side, six tries a sixth of a turn apart.
          // Only a side the navmesh reaches in full: Officer Kurosawa stands in the police station behind a wall
          // (Paulownia Mall, 2026-11-23), every side of him is inside it, and the partial paths to them led the hero
          // on round the plaza and into the back alley's exit.
          bool found = false;
          if (g_w.entries.empty() && g_w.detours == 0) g_w.detour_base = std::atan2(me.y - goal.y, me.x - goal.x);
          while (g_w.entries.empty() && g_w.detours < 6 && !found) {
            ++g_w.detours;
            float a = g_w.detour_base + g_w.detours * 3.14159265f / 3.0f;
            FVector side{goal.x + 330.0f * std::cos(a), goal.y + 330.0f * std::sin(a), me.z}, on{};
            if (!world::project_to_nav(side, 100.0f, on)) continue;
            bool partial = false;
            auto p = world::find_path(world::path_start(me), on, &partial);
            if (p.empty() || partial || flat(p.back(), on) > 80.0f) continue;
            g_w.detour = side;
            found = true;
          }
          if (found) {
            g_w.detour_on = true;
            g_w.direct = false;
            refresh_path(me);
            restart_progress(me, now);
            log::writef("nav: detour {} via ({:.0f}, {:.0f})", g_w.detours, g_w.detour.x, g_w.detour.y);
            return;
          }
        }
        // Blocked by something the path does not know of (or the step round it was): step to one side and go on
        // from there. Three steps with the target no nearer, and the walk is stuck.
        if (!there) {
          float left = flat(goal, me);
          if (left < g_w.side_best - 50.0f) { g_w.side_best = left; g_w.side_tries = 0; }
          g_w.side_on = false;
          if (g_w.side_tries < 3 && find_sidestep(me, on_path, g_w.side_tries, g_w.side, true)) {
            ++g_w.side_tries;
            ++g_w.sides;
            g_w.side_on = true;
            restart_progress(me, now);
            log::writef("nav: blocked at ({:.0f}, {:.0f}), round via ({:.0f}, {:.0f})", me.x, me.y, g_w.side.x, g_w.side.y);
            return;
          }
          // Wedged off the floor's navmesh, where no step to the side lands on it: out by the free side.
          if (g_w.side_tries < 4 && !on_floor_nav(me) && way_onto_floor_nav(me, g_w.side)) {
            g_w.side_tries = 4;
            ++g_w.sides;
            g_w.side_on = true;
            restart_progress(me, now);
            log::writef("nav: wedged off the navmesh at ({:.0f}, {:.0f}), out via ({:.0f}, {:.0f})", me.x, me.y, g_w.side.x, g_w.side.y);
            return;
          }
        }
        // Stuck on the navmesh's way (it can lead out of a room the desks split and into its closed door): the body's
        // own way, once, before giving up.
        if (!there && to_body()) return;
        finish(there ? "arrived (prompt)" : "stuck");
        stop(false);
        if (there) { face(t, me); arrived_at(); } else speech::speak(strings::kStuck.c_str(), true);
        return;
      }
      restart_progress(me, now);
    }
  }
}

std::string status() {
  static const char* drives[] = {"auto", "native", "keys"};
  return std::format("nav walking={} target='{}' path={} held={:c}{:c} drive={} native={} steering={}\n", g_walking, g_w.name, g_w.path.size(),
                     g_held[0] ? (char)g_held[0] : '-', g_held[1] ? (char)g_held[1] : '-', drives[(int)g_drive],
                     g_native == 1 ? "taken" : g_native < 0 ? "ignored" : "not seen yet", native_on() ? "direct" : "keys") +
         std::format("last={} outcome='{}' ms={} left={:.0f} detours={} entries={} sides={} body={} body_replans={} plan_us_max={}\n", g_w.id,
                     g_w.outcome.empty() ? std::string(g_walking ? "walking" : "none") : g_w.outcome,
                     (g_w.ended_at ? g_w.ended_at : GetTickCount64()) - g_w.started_at, g_w.end_left, g_w.detours, g_w.entries_used, g_w.sides,
                     g_w.body, g_w.body_replans, g_w.plan_us_max);
}

// The mod is going (a hot reload): the walk's keys are let go. Left held, the game ran the hero on with nobody
// steering and wedged him in a corner, and the next walk was "Stuck" against the key still down (2026-11-09).
void unload() {
  g_walking = false;
  for (uint32_t& k : g_held) { if (k) input::post_key(k, false, true); k = 0; }
}

void install() {
  // A walk key an earlier copy of the mod left down (it was unloaded or died mid-walk) is let go, unless the player
  // has that key down now.
  for (uint32_t k : {(uint32_t)'W', (uint32_t)'A', (uint32_t)'S', (uint32_t)'D'})
    if (!(GetAsyncKeyState((int)k) & 0x8000)) input::post_key(k, false, true);
  install_dev();   // the dev routes, nav_dev.cpp
}
}  // namespace p3a::nav
