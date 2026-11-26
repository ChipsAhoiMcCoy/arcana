#include "doctest.h"
#include "core/path_rules.h"

using namespace p3a::core;

TEST_CASE("walks_to: the path's end on the thing's floor, near it") {
  const Vec3 thing{1000, 0, 100};
  CHECK(walks_to({{0, 0, 90}, {500, 0, 90}, {990, 0, 90}}, thing));
  CHECK(walks_to({{0, 0, 90}, {800, 0, 90}}, thing));                // a partial path 2 m short counts
  CHECK_FALSE(walks_to({{0, 0, 90}, {600, 0, 90}}, thing));          // 4 m short
  CHECK_FALSE(walks_to({}, thing));
  CHECK(walks_to({{0, 0, -100}, {1000, 0, -140}}, thing));           // 2.4 m below: its floor (a hit's box floats)
  CHECK_FALSE(walks_to({{0, 0, -200}, {1000, 0, -160}}, thing));     // 2.6 m below: the floor below
  // the dorm's 2F stair flight over 1F's "Hallway 2F" box, 1.9 m below the 2F floor: the path ends a floor up
  CHECK_FALSE(walks_to({{0, 0, 90}, {700, 0, 200}, {1000, 0, 290}}, thing));
}

TEST_CASE("walks_to: no leg rises more than it runs plus a step") {
  // the dorm lounge's counter right under 2F's "Your Room" exit: 2 points, 4 m straight up
  CHECK_FALSE(walks_to({{0, 0, 90}, {20, 0, 490}}, Vec3{20, 0, 480}));
  // stairs: 3.4 m up over 5 m of run
  CHECK(walks_to({{0, 0, 90}, {500, 0, 430}}, Vec3{520, 0, 440}));
  CHECK(walks_to({{0, 0, 0}, {10, 0, 105}}, Vec3{10, 0, 105}));      // 1.05 m up over 10 cm: within its run plus 1 m
}
