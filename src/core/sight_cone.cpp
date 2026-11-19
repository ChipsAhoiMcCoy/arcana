#include "core/sight_cone.h"
#include <algorithm>
#include <cmath>

namespace p3a::core {

bool cone_holds(const SightCone& c, const Vec3& p) {
  if (dist3(c.eye, p) > c.range) return false;
  if (c.angle >= 360.0f) return true;
  float dx = p.x - c.eye.x, dy = p.y - c.eye.y;
  if (dx == 0 && dy == 0) return true;   // straight above or below: the game's yaw of a zero vector is 0
  float to = std::atan2(dy, dx) * 180.0f / kPi;
  return angle_diff(to, c.yaw) <= c.angle * 0.5f;
}

std::vector<std::pair<float, float>> cone_spans(const SightCone& c, const Vec3& from, float dx, float dy, float len) {
  std::vector<std::pair<float, float>> out;
  if (len <= 0 || c.range <= 0) return out;
  // Where the walk's line can cross the cone's boundary: the range's circle at this height, and the two side rays.
  float dz = from.z - c.eye.z;
  if (std::fabs(dz) > c.range) return out;
  float r = std::sqrt(c.range * c.range - dz * dz);
  float ox = from.x - c.eye.x, oy = from.y - c.eye.y;
  std::vector<float> cut{0.0f, len};
  float b = ox * dx + oy * dy, cc = ox * ox + oy * oy - r * r;
  float disc = b * b - cc;
  if (disc < 0) return out;   // the line misses the circle: never inside
  float sq = std::sqrt(disc);
  cut.push_back(-b - sq);
  cut.push_back(-b + sq);
  if (c.angle < 360.0f) {
    for (float side : {-0.5f, 0.5f}) {
      float a = (c.yaw + side * c.angle) * kPi / 180.0f;
      float ex = std::cos(a), ey = std::sin(a);
      // from + s*d = eye + t*e  ->  s*d - t*e = -o
      float det = dx * (-ey) - dy * (-ex);
      if (std::fabs(det) < 1e-6f) continue;
      float s = ((-ox) * (-ey) - (-oy) * (-ex)) / det;
      cut.push_back(s);
    }
  }
  std::vector<float> pts;
  for (float s : cut) if (s >= 0 && s <= len) pts.push_back(s);
  std::sort(pts.begin(), pts.end());
  pts.erase(std::unique(pts.begin(), pts.end()), pts.end());
  auto at = [&](float s) { return Vec3{from.x + dx * s, from.y + dy * s, from.z}; };
  for (size_t i = 0; i + 1 < pts.size(); ++i) {
    float a = pts[i], e = pts[i + 1];
    if (e - a < 1e-3f) continue;
    if (!cone_holds(c, at((a + e) * 0.5f))) continue;
    if (!out.empty() && std::fabs(out.back().second - a) < 1e-3f) out.back().second = e;
    else out.push_back({a, e});
  }
  // A walk that starts on the boundary and runs out of the cone: the start alone is inside.
  if (out.empty() && cone_holds(c, from)) out.push_back({0.0f, 0.0f});
  return out;
}

std::vector<std::pair<float, float>> merge_spans(std::vector<std::pair<float, float>> spans) {
  std::sort(spans.begin(), spans.end());
  std::vector<std::pair<float, float>> out;
  for (auto& s : spans) {
    if (!out.empty() && s.first <= out.back().second + 1e-3f) out.back().second = std::max(out.back().second, s.second);
    else out.push_back(s);
  }
  return out;
}

float edge_level(float dist, float band) {
  if (band <= 0 || dist >= band) return 0.0f;
  float v = 1.0f - std::max(dist, 0.0f) / band;
  return v * v;
}

}  // namespace p3a::core
