#pragma once
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

// The cone cut at `p`'s height is a sector on the ground plane (its range shrunk by the height between). The point
// of that sector nearest `p`, at `p`'s height, and the distance to it on the ground (0: `p` is inside). False when
// the cone does not reach that height.
bool sector_nearest(const SightCone& c, const Vec3& p, Vec3& out, float& dist);

// How far a set of cones (one Shadow's) reaches along ground bearing `theta` (degrees from the eye) at height `z`:
// the longest range, at that height, of the cones holding that bearing; 0 when none does.
float reach_at(const std::vector<SightCone>& cones, float z, float theta);

// One ray of a fan from the eye: its ground bearing and how far it sees along it (0: not at all).
struct SightRay { float theta = 0, len = 0; };
// The region a fan of rays (bearings ascending, a few degrees apart) sweeps out from `eye`: the point of its edge
// nearest `p` (at `p`'s height) and the ground distance to it. The edge runs from tip to tip of neighbouring rays, and
// from the eye out to the first and last ray that sees, and to either side of a ray that sees none. False: no ray
// sees.
bool fan_nearest(const Vec3& eye, const std::vector<SightRay>& rays, const Vec3& p, Vec3& out, float& dist);

// How loud a Shadow's sight is with its edge `dist` cm away, heard from `range` cm out: a quiet floor across the
// range (faded in over its outer metre), rising steeply over the last metres to 1 at the edge; 0 past the range.
float zone_level(float dist, float range);

}  // namespace p3a::core
