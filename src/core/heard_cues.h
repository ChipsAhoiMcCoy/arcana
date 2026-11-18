#pragma once
// The 3D scene descriptions the player has heard (setting SceneDescription, "suppress repeated descriptions"): a
// description once heard is not read again. A description is named by its scene and its text (FNV-1a of the text):
// a description rewritten later counts as new and is heard once more. The record is one line per description,
// "<scene key> <16 hex digits>", appended as each is heard (ad.cpp keeps the file beside the settings).
#include <cstdint>
#include <format>
#include <set>
#include <string>
#include <string_view>

namespace p3a::core {
class HeardCues {
 public:
  static std::string id(std::string_view scene, std::string_view text) {
    uint64_t h = 0xcbf29ce484222325ull;
    for (unsigned char c : text) { h ^= c; h *= 0x100000001b3ull; }
    return std::format("{} {:016x}", scene, h);
  }
  bool heard(std::string_view scene, std::string_view text) const { return ids_.contains(id(scene, text)); }
  // True when it is new (the caller appends the line to the file).
  bool add(const std::string& id) { return !id.empty() && ids_.insert(id).second; }
  // One line of the file: a scene key and 16 hex digits; anything else is left out.
  bool add_line(std::string_view line) {
    while (!line.empty() && (line.back() == '\n' || line.back() == '\r' || line.back() == ' ')) line.remove_suffix(1);
    auto sp = line.rfind(' ');
    if (sp == std::string_view::npos || sp == 0 || line.size() - sp - 1 != 16) return false;
    for (char c : line.substr(sp + 1))
      if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return false;
    return add(std::string(line));
  }
  void clear() { ids_.clear(); }
  size_t size() const { return ids_.size(); }

 private:
  std::set<std::string, std::less<>> ids_;
};
}  // namespace p3a::core
