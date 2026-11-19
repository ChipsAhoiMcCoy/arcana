#include "doctest.h"
#include "core/sight_cone.h"

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

TEST_CASE("cone_spans: walking straight at the Shadow from in front") {
  SightCone c = walk_cone();
  auto s = cone_spans(c, Vec3{1200, 0, 0}, -1, 0, 600);
  REQUIRE(s.size() == 1);
  CHECK(s[0].first == doctest::Approx(345.0f));
  CHECK(s[0].second == doctest::Approx(600.0f));
}

TEST_CASE("cone_spans: walking away out of range") {
  auto s = cone_spans(walk_cone(), Vec3{800, 0, 0}, 1, 0, 300);
  REQUIRE(s.size() == 1);
  CHECK(s[0].first == doctest::Approx(0.0f));
  CHECK(s[0].second == doctest::Approx(55.0f));
}

TEST_CASE("cone_spans: walking past behind the Shadow crosses the blind wedge") {
  // Along y at x = -300: inside the cone until the side ray at 135 degrees (y = 300), blind between, inside again.
  auto s = cone_spans(walk_cone(), Vec3{-300, -600, 0}, 0, 1, 1200);
  REQUIRE(s.size() == 2);
  CHECK(s[0].second == doctest::Approx(300.0f).epsilon(0.01));    // y = -300
  CHECK(s[1].first == doctest::Approx(900.0f).epsilon(0.01));      // y = +300
}

TEST_CASE("cone_spans: a walk that never enters") {
  CHECK(cone_spans(walk_cone(), Vec3{-500, -100, 0}, -1, 0, 500).empty());   // behind, walking further back
  CHECK(cone_spans(walk_cone(), Vec3{2000, 0, 0}, 0, 1, 500).empty());       // far off, walking across
  CHECK(cone_spans(walk_cone(), Vec3{100, 0, 900}, 1, 0, 500).empty());      // a floor above, out of range
}

TEST_CASE("merge_spans: overlapping cones of one Shadow are one stretch") {
  auto m = merge_spans({{300, 500}, {0, 100}, {80, 320}});
  REQUIRE(m.size() == 1);
  CHECK(m[0].first == doctest::Approx(0.0f));
  CHECK(m[0].second == doctest::Approx(500.0f));
  auto two = merge_spans({{0, 10}, {50, 60}});
  CHECK(two.size() == 2);
}

TEST_CASE("edge_level: steep near the edge, nothing past the band") {
  CHECK(edge_level(0, 200) == doctest::Approx(1.0f));
  CHECK(edge_level(100, 200) == doctest::Approx(0.25f));
  CHECK(edge_level(200, 200) == doctest::Approx(0.0f));
  CHECK(edge_level(500, 200) == doctest::Approx(0.0f));
}
