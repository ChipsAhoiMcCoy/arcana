#include "core/sight_cone.h"
#include <algorithm>
#include <cmath>

namespace p3a::core {
namespace {
float rad(float deg) { return deg * kPi / 180.0f; }
// The nearest point of segment a-b to p on the ground plane (p's height kept), and the distance.
float seg_nearest(float ax, float ay, float bx, float by, const Vec3& p, Vec3& out) {
  float dx = bx - ax, dy = by - ay, l2 = dx * dx + dy * dy;
  float t = l2 > 0 ? std::clamp(((p.x - ax) * dx + (p.y - ay) * dy) / l2, 0.0f, 1.0f) : 0.0f;
  out = Vec3{ax + dx * t, ay + dy * t, p.z};
  return std::hypot(p.x - out.x, p.y - out.y);
}
float slice_radius(const SightCone& c, float z) {
  float dz = z - c.eye.z;
  return std::fabs(dz) > c.range ? -1.0f : std::sqrt(c.range * c.range - dz * dz);
}
bool holds_bearing(const SightCone& c, float theta) { return c.angle >= 360.0f || angle_diff(theta, c.yaw) <= c.angle * 0.5f; }
}  // namespace

bool cone_holds(const SightCone& c, const Vec3& p) {
  if (dist3(c.eye, p) > c.range) return false;
  if (c.angle >= 360.0f) return true;
  float dx = p.x - c.eye.x, dy = p.y - c.eye.y;
  if (dx == 0 && dy == 0) return true;   // straight above or below: the game's yaw of a zero vector is 0
  return holds_bearing(c, std::atan2(dy, dx) * 180.0f / kPi);
}

bool sector_nearest(const SightCone& c, const Vec3& p, Vec3& out, float& dist) {
  float r = slice_radius(c, p.z);
  if (r < 0) return false;
  float vx = p.x - c.eye.x, vy = p.y - c.eye.y, d = std::hypot(vx, vy);
  bool in_wedge = d < 1e-3f || holds_bearing(c, std::atan2(vy, vx) * 180.0f / kPi);
  if (in_wedge) {
    if (d <= r) { out = p; dist = 0; return true; }
    out = Vec3{c.eye.x + vx / d * r, c.eye.y + vy / d * r, p.z};
    dist = d - r;
    return true;
  }
  dist = 1e30f;
  for (float side : {-0.5f, 0.5f}) {
    float a = rad(c.yaw + side * c.angle);
    Vec3 q;
    float e = seg_nearest(c.eye.x, c.eye.y, c.eye.x + std::cos(a) * r, c.eye.y + std::sin(a) * r, p, q);
    if (e < dist) { dist = e; out = q; }
  }
  return true;
}

float reach_at(const std::vector<SightCone>& cones, float z, float theta) {
  float best = 0;
  for (const SightCone& c : cones)
    if (holds_bearing(c, theta)) best = std::max(best, slice_radius(c, z));
  return best;
}

bool fan_nearest(const Vec3& eye, const std::vector<SightRay>& rays, const Vec3& p, Vec3& out, float& dist) {
  dist = 1e30f;
  bool any = false;
  auto tip = [&](const SightRay& r, float& x, float& y) { x = eye.x + std::cos(rad(r.theta)) * r.len; y = eye.y + std::sin(rad(r.theta)) * r.len; };
  auto consider = [&](float ax, float ay, float bx, float by) {
    Vec3 q;
    float e = seg_nearest(ax, ay, bx, by, p, q);
    if (e < dist) { dist = e; out = q; }
    any = true;
  };
  for (size_t i = 0; i < rays.size(); ++i) {
    if (rays[i].len <= 0) continue;
    float x, y;
    tip(rays[i], x, y);
    bool open_before = i == 0 || rays[i - 1].len <= 0, open_after = i + 1 == rays.size() || rays[i + 1].len <= 0;
    if (open_before || open_after) consider(eye.x, eye.y, x, y);   // a side of the region: from the eye out
    if (i + 1 < rays.size() && rays[i + 1].len > 0) {
      float x2, y2;
      tip(rays[i + 1], x2, y2);
      consider(x, y, x2, y2);
    }
  }
  return any;
}

float zone_level(float dist, float range) {
  if (range <= 0 || dist >= range) return 0.0f;
  constexpr float kFloor = 0.12f;   // heard across the whole range
  float closeness = 1.0f - std::max(dist, 0.0f) / range;
  float fade = std::min(1.0f, (range - dist) / 100.0f);   // the floor comes in over the range's outer metre
  return std::max(kFloor * fade, closeness * closeness * closeness);
}

}  // namespace p3a::core
