#pragma once
#include "core/boxes.h"
#include <vector>

namespace p3a::core {
// Whether a navmesh path (the hero's start to `target`, partial ones included) walks to a thing:
//  - its end is on the thing's own floor: from 2.5 m below to 1 m above it (floors are 3.4 m apart; a thing stands on
//    its floor or above it), and within 3 m of it on the ground. A path that ends a metre above it is on the floor
//    above: the dorm's 2F stair flight runs over 1F's "Hallway 2F" box, 1.9 m below the 2F floor (2026-11-24).
//  - no leg rises more than it runs, plus a step (1 m): a path straight up is no walk (from the dorm lounge's counter,
//    right under 2F's "Your Room" exit, the path was 2 points, 4 m straight up, 2026-11-24).
// An empty path walks nowhere.
bool walks_to(const std::vector<Vec3>& path, const Vec3& target);
}  // namespace p3a::core
