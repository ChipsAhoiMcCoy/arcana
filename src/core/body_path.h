#pragma once
#include "core/approach.h"
#include <cstdint>
#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>

// A walk the navmesh does not have: classroom 2-F's desks cut its navmesh into islands (the navmesh keeps a wider
// berth than the hero needs), so the path from the back door to a front desk led out through one door and in at the
// other. The hero's own body fits between the desks. This searches a grid of floor points for a way, asking the
// caller whether the body moves from one point to the next (the engine's capsule sweep). Engine-free.
namespace p3a::core {

struct BodyPlan {
  bool found = false;
  std::vector<Vec2> points;   // the start, every turn, and the end (each leg a straight run the body makes)
  int expanded = 0;           // grid points taken off the open list
  int tested = 0;             // moves asked of `clear`
};

// How far from the start `max_expand` grid points of `cell` cm can carry a plan: three times the radius of the disc
// that many cells fill. A search toward the goal floods far less than the disc in the open (classroom 2-F's far
// bookshelf, 15 m off, took 3200 of 12000 points, 2026-11-23: the disc's radius is 6.2 m), all of it round an
// obstacle.
// Hemmed in at the Naganaki Shrine's see-saw (2026-11-17), the walk asked for a plan 25 m across with 12000 points of
// 10 cm (a disc of 6 m): it flooded the whole budget, every frame it was asked, and found nothing.
float body_reach(int max_expand, float cell);

using BodyClear = std::function<bool(Vec2, Vec2)>;
using BodyArrived = std::function<bool(Vec2)>;

// A* over a square grid of `cell` cm with its axes turned `yaw` radians (the camera's, so every leg is one of the
// eight walking directions), from `from` toward `goal`. Eight neighbours; a diagonal costs its length.
// `clear(a, b)`: the body moves a -> b. `arrived(p)`: standing at p ends the walk. Gives up after `max_expand` points,
// or past `reach` cm from the start; `reach` is held to what the budget covers (body_reach), and a goal past it is
// refused at once.
// Resumable: step() runs the search on until it has asked `clear` about `budget` more moves, so a search of 9000
// points (20 ms of sweeps, classroom 2-F) is spread over frames instead of stalling one.
class BodySearch {
 public:
  BodySearch(Vec2 from, Vec2 goal, float cell, float yaw, int max_expand, float reach);
  // True once finished (found or given up); plan() is then final.
  bool step(int budget, const BodyClear& clear, const BodyArrived& arrived);
  bool done() const { return done_; }
  const BodyPlan& plan() const { return plan_; }

 private:
  struct Node { float g = 0; uint64_t parent = 0; bool closed = false; bool root = false; };
  struct Open { float f; float g; int i, j; };
  struct Later { bool operator()(const Open& a, const Open& b) const { return a.f > b.f; } };
  Vec2 at(int i, int j) const;
  float h(Vec2 p) const;
  void finish_found(int i, int j, const BodyClear& clear);
  Vec2 from_, goal_;
  float cell_, c_, s_;
  int max_expand_;
  float reach_;
  bool done_ = false;
  BodyPlan plan_;
  std::unordered_map<uint64_t, Node> nodes_;
  std::priority_queue<Open, std::vector<Open>, Later> open_;
  bool have_cur_ = false;   // a point taken off the open list whose neighbours are part done (a slice ended there)
  Open cur_{};
  int cur_d_ = 0;
};

// The whole search at once.
BodyPlan body_path(Vec2 from, Vec2 goal, float cell, float yaw, int max_expand, float reach, const BodyClear& clear, const BodyArrived& arrived);

}  // namespace p3a::core
