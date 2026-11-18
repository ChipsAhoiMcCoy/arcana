#include "core/affinity.h"
#include "core/strings.h"
#include <format>

namespace p3a::core {
namespace {
// The kinds in the order they are tested and grouped.
constexpr struct { uint16_t bit; int kind; } kKinds[] = {{0x0800, 4}, {0x1000, 5}, {0x0100, 1}, {0x0200, 2}, {0x0400, 3}};
}  // namespace

int attr_index(int slot) {
  for (int i = 0; i < 9; ++i) if (kAffinitySlots[i] == slot) return i;
  return -1;
}

std::string attr_name(int slot) {
  int i = attr_index(slot);
  return i < 0 ? std::string() : std::string(strings::kAttrNames[i]);
}

int affinity_kind(uint16_t value) {
  for (auto& k : kKinds) if (value & k.bit) return k.kind;
  return 0;
}

std::vector<std::string> affinity_groups(const uint16_t* row) {
  std::vector<std::string> out;
  if (!row) return out;
  for (auto& k : kKinds) {
    std::string list;
    for (int i = 0; i < 9; ++i)
      if (affinity_kind(row[kAffinitySlots[i]]) == k.kind) list += (list.empty() ? "" : " ") + std::string(strings::kAttrNames[i]);
    if (!list.empty()) out.push_back(std::string(strings::kAffinity[k.kind]) + " " + list);
  }
  return out;
}

std::vector<std::string> affinity_lines(const uint16_t* row) {
  std::vector<std::string> out;
  if (!row) return out;
  for (int i = 0; i < 9; ++i)
    out.push_back(std::format("{}: {}", strings::kAttrNames[i], strings::kAffinityShort[affinity_kind(row[kAffinitySlots[i]])]));
  return out;
}
}  // namespace p3a::core
