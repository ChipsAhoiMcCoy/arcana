#pragma once
// A menu's title said on entry repeats the row the player just confirmed to open it ("Item" in the camp, then the Item
// menu's "Item"): the player knows where they went. The title loses its first sentence when that sentence names the
// confirmed row (its label before any ", Unavailable"-style tail), plural or singular alike; the rest of the title, a
// question or a prompt ("Tactics. Give an order?"), stays.
#include <string>
#include <string_view>

namespace p3a::core {
namespace title_echo_detail {
inline bool space(char c) { return c == ' ' || c == '\t'; }
inline std::string_view trim(std::string_view s) {
  while (!s.empty() && (space(s.front()) || s.front() == '.')) s.remove_prefix(1);
  while (!s.empty() && (space(s.back()) || s.back() == '.' || s.back() == ',' || s.back() == ':'))
    s.remove_suffix(1);
  return s;
}
inline std::string fold(std::string_view s) {
  std::string out;
  for (char c : trim(s)) out += c >= 'A' && c <= 'Z' ? (char)(c - 'A' + 'a') : c;
  if (out.size() > 1 && out.back() == 's') out.pop_back();
  return out;
}
}  // namespace title_echo_detail

// The title to say when the screen was opened by confirming a row labelled `label` (empty: none).
inline std::string drop_echoed_title(std::string_view title, std::string_view label) {
  using namespace title_echo_detail;
  if (title.empty() || label.empty()) return std::string(title);
  std::string_view head = label.substr(0, label.find(", "));
  head = head.substr(0, head.find(". "));
  size_t cut = title.find(". ");
  std::string_view first = title.substr(0, cut);
  if (fold(first).empty() || fold(first) != fold(head)) return std::string(title);
  return cut == std::string_view::npos ? std::string() : std::string(trim(title.substr(cut + 2)));
}

// The first line of the list a confirm opened, without a leading name that is the confirmed row's: the member chosen
// in Equip is the slot list's context ("Colton, Weapon: ..." after "Colton" was confirmed). A line that is only that
// name is kept.
inline std::string drop_echoed_prefix(std::string_view line, std::string_view label) {
  if (label.empty()) return std::string(line);
  std::string_view head = label.substr(0, label.find(", "));
  head = head.substr(0, head.find(". "));
  if (head.empty() || line.size() <= head.size() + 2 || line.substr(0, head.size()) != head) return std::string(line);
  std::string_view sep = line.substr(head.size(), 2);
  if (sep != ", " && sep != ". ") return std::string(line);
  return std::string(line.substr(head.size() + 2));
}
}  // namespace p3a::core
