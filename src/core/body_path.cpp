#include "core/body_path.h"
#include <algorithm>
#include <climits>
#include <cmath>

namespace p3a::core {

float body_reach(int max_expand, float cell) { return 3.0f * cell * std::sqrt((float)std::max(0, max_expand) / 3.14159265f); }

static uint64_t key(int i, int j) { return ((uint64_t)(uint32_t)i << 32) | (uint32_t)j; }

BodySearch::BodySearch(Vec2 from, Vec2 goal, float cell, float yaw, int max_expand, float reach)
    : from_(from), goal_(goal), cell_(cell), c_(std::cos(yaw)), s_(std::sin(yaw)), max_expand_(max_expand) {
  reach_ = std::min(reach, body_reach(max_expand, cell));
  if (std::hypot(goal.x - from.x, goal.y - from.y) > reach_) { done_ = true; return; }   // further than the budget carries
  nodes_[key(0, 0)] = Node{0, 0, false, true};
  open_.push(Open{h(from), 0, 0, 0});
}

// Grid (i, j): i along the turned x axis, j along the turned y axis, (0, 0) at the start.
Vec2 BodySearch::at(int i, int j) const {
  float u = (float)i * cell_, v = (float)j * cell_;
  return Vec2{from_.x + u * c_ - v * s_, from_.y + u * s_ + v * c_};
}
float BodySearch::h(Vec2 p) const { return std::hypot(goal_.x - p.x, goal_.y - p.y); }

void BodySearch::finish_found(int i0, int j0, const BodyClear& clear) {
  // Back along the parents, keeping only the points where the direction turns.
  std::vector<std::pair<int, int>> cells;
  for (uint64_t k = key(i0, j0);;) {
    cells.emplace_back((int)(int32_t)(k >> 32), (int)(int32_t)(k & 0xffffffffu));
    const Node& m = nodes_[k];
    if (m.root) break;
    k = m.parent;
  }
  plan_.found = true;
  for (size_t a = cells.size(); a-- > 0;) {
    bool turn = a == 0 || a + 1 == cells.size();
    if (!turn) {
      auto [pi, pj] = cells[a + 1];
      auto [ci, cj] = cells[a];
      auto [ni, nj] = cells[a - 1];
      turn = (ci - pi) != (ni - ci) || (cj - pj) != (nj - cj);
    }
    if (turn) plan_.points.push_back(at(cells[a].first, cells[a].second));
  }
  plan_.points.front() = from_;
  // A grid's diagonal runs as a staircase of short legs: from each point, on to the furthest later one the body
  // reaches straight. Through a narrow gap only the straight legs are clear, so those stay.
  std::vector<Vec2> pulled{plan_.points.front()};
  for (size_t a = 0; a + 1 < plan_.points.size();) {
    size_t b = plan_.points.size() - 1;
    while (b > a + 1 && !(++plan_.tested, clear(plan_.points[a], plan_.points[b]))) --b;
    pulled.push_back(plan_.points[b]);
    a = b;
  }
  plan_.points = std::move(pulled);
  done_ = true;
}

bool BodySearch::step(int budget, const BodyClear& clear, const BodyArrived& arrived) {
  static const int di[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dj[8] = {0, 1, 0, -1, 1, -1, 1, -1};
  const float diag = cell_ * 1.41421356f;
  const int stop_at = plan_.tested > INT_MAX - budget ? INT_MAX : plan_.tested + budget;
  while (!done_) {
    if (!have_cur_) {
      if (open_.empty()) { done_ = true; break; }
      Open o = open_.top();
      open_.pop();
      Node& n = nodes_[key(o.i, o.j)];
      if (n.closed || o.g > n.g) continue;
      n.closed = true;
      if (arrived(at(o.i, o.j))) { finish_found(o.i, o.j, clear); break; }
      if (++plan_.expanded > max_expand_) { done_ = true; break; }
      cur_ = o;
      cur_d_ = 0;
      have_cur_ = true;
    }
    Vec2 p = at(cur_.i, cur_.j);
    for (; cur_d_ < 8; ++cur_d_) {
      if (plan_.tested >= stop_at) return false;   // the slice is spent: on from this neighbour next time
      int i = cur_.i + di[cur_d_], j = cur_.j + dj[cur_d_];
      Vec2 q = at(i, j);
      if (std::hypot(q.x - from_.x, q.y - from_.y) > reach_) continue;
      float g = cur_.g + (cur_d_ < 4 ? cell_ : diag);
      auto it = nodes_.find(key(i, j));
      if (it != nodes_.end() && (it->second.closed || it->second.g <= g)) continue;
      ++plan_.tested;
      if (!clear(p, q)) continue;
      Node& m = nodes_[key(i, j)];
      m.g = g;
      m.parent = key(cur_.i, cur_.j);
      m.root = false;
      open_.push(Open{g + h(q), g, i, j});
    }
    have_cur_ = false;
  }
  return true;
}

BodyPlan body_path(Vec2 from, Vec2 goal, float cell, float yaw, int max_expand, float reach, const BodyClear& clear, const BodyArrived& arrived) {
  BodySearch s(from, goal, cell, yaw, max_expand, reach);
  s.step(INT_MAX, clear, arrived);
  return s.plan();
}

}  // namespace p3a::core
