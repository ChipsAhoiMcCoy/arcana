#include "doctest.h"
#include "core/affinity.h"
#include "core/dat_pick.h"
#include "core/strings.h"
#include <string>
#include <vector>

using namespace p3a::core;
namespace strings = p3a::strings;

TEST_CASE("affinity: the table / Analyze slots name the right elements") {
  CHECK(attr_name(0) == "Slash");
  CHECK(attr_name(6) == "Wind");
  CHECK(attr_name(7).empty());   // Almighty is not shown
  CHECK(attr_name(8) == "Light");
  CHECK(attr_name(9) == "Dark");
  CHECK(attr_name(10).empty());
  CHECK(attr_name(-1).empty());
  for (int i = 0; i < 9; ++i) {   // each shown slot round-trips to its name's index
    CHECK(attr_index(kAffinitySlots[i]) == i);
    CHECK(attr_name(kAffinitySlots[i]) == strings::kAttrNames[i]);
  }
}

TEST_CASE("affinity: kinds from a table value") {
  CHECK(affinity_kind(0x0014) == 0);   // normal
  CHECK(affinity_kind(0x0100) == 1);   // nulls (Jack Frost's Ice)
  CHECK(affinity_kind(0x0200) == 2);   // repels (Hell Biker's Fire)
  CHECK(affinity_kind(0x0400) == 3);   // drains (Mithras's Fire)
  CHECK(affinity_kind(0x0800) == 4);   // weak (Nekomata's Elec)
  CHECK(affinity_kind(0x1000) == 5);   // resists (Nekomata's Wind)
  CHECK(affinity_kind(0x2000) == 0);   // not read
}

TEST_CASE("affinity: Light and Dark are not swapped (Gabriel nulls Light, weak to Dark)") {
  uint16_t row[kAffinitySlotsInRow] = {};
  for (auto& v : row) v = 0x0014;
  row[7] = 0x0100;   // Almighty: never shown
  row[8] = 0x0100;   // Light: nulls
  row[9] = 0x0800;   // Dark: weak
  auto groups = affinity_groups(row);
  REQUIRE(groups.size() == 2);
  CHECK(groups[0] == "weak to Dark");
  CHECK(groups[1] == "nulls Light");
  auto lines = affinity_lines(row);
  REQUIRE(lines.size() == 9);
  CHECK(lines[0] == "Slash: normal");
  CHECK(lines[7] == "Light: null");
  CHECK(lines[8] == "Dark: weak");
}

TEST_CASE("affinity: groups in the order weak, resists, nulls, repels, drains") {
  uint16_t row[kAffinitySlotsInRow] = {};
  row[3] = 0x0400;   // Fire drains
  row[4] = 0x0800;   // Ice weak
  row[5] = 0x0800;   // Elec weak
  row[6] = 0x1000;   // Wind resists
  row[8] = 0x0200;   // Light repels
  auto g = affinity_groups(row);
  REQUIRE(g.size() == 4);
  CHECK(g[0] == "weak to Ice Elec");
  CHECK(g[1] == "resists Wind");
  CHECK(g[2] == "repels Light");
  CHECK(g[3] == "drains Fire");
  CHECK(affinity_groups(nullptr).empty());
}

TEST_CASE("dat_pick: the running story's copy, newest first") {
  const std::vector<std::string> both = {
    "/Game/Xrd777/Battle/Tables/DatSkillNormalDataAsset.DatSkillNormalDataAsset",
    "/Game/Astrea/Battle/Tables/DatSkillNormalDataAsset.DatSkillNormalDataAsset",
  };
  CHECK(pick_asset(both, false).index == 0);   // the main story never reads the newer Astrea copy
  CHECK(!pick_asset(both, false).fallback);
  CHECK(pick_asset(both, true).index == 1);
  CHECK(astrea_package("/Game/L10N/en/Astrea/Blueprints/common/Names/DatSkillNameDataAsset.DatSkillNameDataAsset"));
  CHECK(!astrea_package("/Game/L10N/en/Xrd777/Blueprints/common/Names/DatSkillNameDataAsset.DatSkillNameDataAsset"));
  const std::vector<std::string> two_main = {"/Game/Xrd777/A.A", "/Game/L10N/en/Xrd777/A.A"};
  CHECK(pick_asset(two_main, false).index == 1);
}

TEST_CASE("dat_pick: only the other story's copy loaded falls back to it") {
  const std::vector<std::string> only_astrea = {"/Game/Astrea/A.A"};
  auto p = pick_asset(only_astrea, false);
  CHECK(p.index == 0);
  CHECK(p.fallback);
  CHECK(pick_asset({}, false).index == -1);
}
