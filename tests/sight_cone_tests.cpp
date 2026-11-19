#include "doctest.h"
#include "core/sight_cone.h"
#include <cmath>

using namespace p3a::core;

namespace {
// A Shadow at the origin facing +x (yaw 0), 855 cm and 270 degrees: the walking cone of a normal Shadow.
SightCone walk_cone() { return SightCone{Vec3{0, 0, 0}, 0.0f, 855.0f, 270.0f}; }
}  // namespace

TEST_CASE("cone_holds: range in space, angle on the ground") {
  SightCone c = walk_cone();
  CHECK(cone_holds(c, Vec3{800, 0, 0}));
  CHECK_FALSE(cone_holds(c, Vec3{900, 0, 0}));
  CHECK_FALSE(cone_holds(c, Vec3{800, 0, 400}));            // 885 cm away in space
  CHECK(cone_holds(c, Vec3{0, 500, 0}));                    // 90 degrees off: inside a 270-degree cone
  CHECK(cone_holds(c, Vec3{-300, 310, 0}));                 // ~134 degrees off, just inside 135
  CHECK_FALSE(cone_holds(c, Vec3{-500, 0, 0}));             // straight behind: the blind wedge
  CHECK_FALSE(cone_holds(c, Vec3{-300, 290, 0}));           // ~136 degrees off
  SightCone all{Vec3{0, 0, 0}, 0.0f, 370.0f, 360.0f};
  CHECK(cone_holds(all, Vec3{-300, 0, 0}));
}

TEST_CASE("sector_nearest: in front, beside and behind the Shadow") {
  SightCone c = walk_cone();
  Vec3 q; float d;
  REQUIRE(sector_nearest(c, Vec3{1200, 0, 0}, q, d));       // straight ahead, out of range: the arc
  CHECK(d == doctest::Approx(345.0f));
  CHECK(q.x == doctest::Approx(855.0f));
  REQUIRE(sector_nearest(c, Vec3{0, 1000, 0}, q, d));       // 90 degrees off: still the arc
  CHECK(d == doctest::Approx(145.0f));
  REQUIRE(sector_nearest(c, Vec3{-500, 0, 0}, q, d));       // in the blind wedge: the nearer side ray
  CHECK(d == doctest::Approx(500.0f * 0.70710678f).epsilon(0.001));
  REQUIRE(sector_nearest(c, Vec3{400, 0, 0}, q, d));        // inside
  CHECK(d == 0.0f);
  CHECK_FALSE(sector_nearest(c, Vec3{0, 0, 900}, q, d));    // a floor above, out of reach
  REQUIRE(sector_nearest(c, Vec3{1200, 0, 300}, q, d));     // 3 m higher: the slice is smaller
  CHECK(d == doctest::Approx(1200.0f - std::sqrt(855.0f * 855.0f - 300.0f * 300.0f)));
}

TEST_CASE("reach_at: the longest cone holding the bearing") {
  std::vector<SightCone> cones{walk_cone(), SightCone{Vec3{0, 0, 0}, 0.0f, 370.0f, 352.0f}};
  CHECK(reach_at(cones, 0, 0) == doctest::Approx(855.0f));
  CHECK(reach_at(cones, 0, 170) == doctest::Approx(370.0f));   // behind: the close cone only
  CHECK(reach_at(cones, 0, 179) == doctest::Approx(0.0f));     // its 8-degree blind wedge
}

TEST_CASE("fan_nearest: a wall cuts the rays on one side") {
  // Rays from the origin every 10 degrees, -20..20; the two on the left see only 200 cm (a wall), the rest 855.
  std::vector<SightRay> rays{{-20, 855}, {-10, 855}, {0, 855}, {10, 200}, {20, 200}};
  Vec3 q; float d;
  REQUIRE(fan_nearest(Vec3{0, 0, 0}, rays, Vec3{1200, 0, 0}, q, d));
  CHECK(d == doctest::Approx(345.0f).epsilon(0.02));          // ahead: the far tips
  REQUIRE(fan_nearest(Vec3{0, 0, 0}, rays, Vec3{300, 100, 0}, q, d));   // inside the cone, but behind the wall
  CHECK(d < 100.0f);                                           // the edge where the wall cuts in, just below
  CHECK(q.y < 60.0f);
  std::vector<SightRay> none{{0, 0}, {10, 0}};
  CHECK_FALSE(fan_nearest(Vec3{0, 0, 0}, none, Vec3{100, 0, 0}, q, d));
}

TEST_CASE("zone_level: a floor across the range, steep near the edge") {
  CHECK(zone_level(0, 600) == doctest::Approx(1.0f));
  CHECK(zone_level(600, 600) == doctest::Approx(0.0f));
  CHECK(zone_level(900, 600) == doctest::Approx(0.0f));
  CHECK(zone_level(400, 600) == doctest::Approx(0.12f));        // far: the floor
  CHECK(zone_level(550, 600) == doctest::Approx(0.06f));        // the floor fading in at the range's end
  CHECK(zone_level(100, 600) == doctest::Approx(0.5787f).epsilon(0.01));
  CHECK(zone_level(100, 600) > 2.0f * zone_level(250, 600));    // the last metres rise steeply
}
