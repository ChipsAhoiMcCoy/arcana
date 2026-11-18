#pragma once
// The game's element numbering and the affinity words built from it. One numbering covers the Personas' and the
// enemies' affinity tables (UDatAffinityTable: u16 per slot) and Analyze's BtlDataBaseComponent.GatAnalizeAttr `attr`:
// 0 Slash, 1 Strike, 2 Pierce, 3 Fire, 4 Ice, 5 Elec, 6 Wind, 7 Almighty, 8 Light, 9 Dark (2026-10-31: Gabriel nulls
// 8 and is weak to 9; Hell Biker weak to 8, its page marks Light). GetAttackName numbers them otherwise (its 8 is
// "Dark"): never name a slot through it (Analyze said "Dark" for Light, 2026-11-17).
#include <cstdint>
#include <string>
#include <vector>

namespace p3a::core {
// The slots a status page or Analyze shows, in strings::kAttrNames' order (Almighty, 7, is not shown).
inline constexpr int kAffinitySlots[9] = {0, 1, 2, 3, 4, 5, 6, 8, 9};
inline constexpr int kAffinitySlotsInRow = 19;   // u16 per row in the tables (38 bytes)

// kAttrNames' index of a table slot / Analyze attr, or -1 (Almighty, or past Dark).
int attr_index(int slot);
// The slot's element name ("Light" for 8), or "" for one not shown.
std::string attr_name(int slot);
// A table value's kind (strings::kAffinity / kAffinityShort: 0 normal, 1 nulls, 2 repels, 3 drains, 4 weak, 5
// resists). The high byte holds it: 0x01 nulls, 0x02 repels, 0x04 drains, 0x08 weak, 0x10 resists; 0x0014 alone is
// normal (measured 2026-10-28 and 2026-10-31). Weak and resist are tested first, as the status page shows them.
int affinity_kind(uint16_t value);
// A row's special affinities grouped by kind, weak first: "weak to Fire", "nulls Light Dark".
std::vector<std::string> affinity_groups(const uint16_t* row);
// Every shown slot of a row on its own line, in kAttrNames' order: "Slash: normal" .. "Dark: weak".
std::vector<std::string> affinity_lines(const uint16_t* row);
}  // namespace p3a::core
