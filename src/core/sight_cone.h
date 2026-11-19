#pragma once
#include <utility>
#include <vector>
#include "core/boxes.h"

// A Shadow's sight as the game tests it (a Tartarus Shadow noticing the hero): the hero's centre is seen when it is
// within `range` of the Shadow's centre, measured in space, and within half of `angle` to either side of the Shadow's
// facing, measured on the ground plane, and nothing blocks the line between the two centres (that last part is a trace
// in the game, left to the caller). Unreal's units: centimetres, yaw in degrees. Engine-free.

namespace p3a::core {

struct SightCone {
  Vec3 eye;          // the Shadow's centre
  float yaw = 0;     // its facing
  float range = 0;   // cm
  float angle = 0;   // the whole cone, degrees (360: all round)
};

// The point is inside the cone (range and angle; no line of sight).
bool cone_holds(const SightCone& c, const Vec3& p);
// The stretches of the walk from `from` along the ground direction (dx, dy) (a unit vector), out to `len`, that lie
// inside the cone: sorted, each [start, end] in cm along the walk. The walk keeps `from`'s height.
std::vector<std::pair<float, float>> cone_spans(const SightCone& c, const Vec3& from, float dx, float dy, float len);
// The union of several sets of spans, sorted and merged.
std::vector<std::pair<float, float>> merge_spans(std::vector<std::pair<float, float>> spans);
// How loud the edge is at `dist` cm from it, in a warning band `band` cm wide: 0 at the band's far end (and past it),
// 1 at the edge, rising steeply over the last part ((1 - d/band) squared).
float edge_level(float dist, float band);

}  // namespace p3a::core
