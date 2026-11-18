#pragma once
// What the player already knows after confirming a row: its name. A menu's title said on entry ("Item" after the camp's
// Item) and the heading a confirm's list leads with (the member over Equip's slots, the slot over its gear) repeat it,
// and are left out (menu.cpp). The test starts from the heading, not from guessing where the row's name ends: the
// row's label is the heading, or starts with it followed by a comma, colon or period ("Armor: Bulletproof Shirt" is
// named by "Armor"); case and a plural 's' aside ("Items" names "Item").
#include <string>
#include <string_view>
#include <vector>

namespace p3a::core {
namespace title_echo_detail {
inline bool space(char c) { return c == ' ' || c == '\t'; }
inline char lower(char c) { return c >= 'A' && c <= 'Z' ? (char)(c - 'A' + 'a') : c; }
inline bool sep(char c) { return c == ',' || c == ':' || c == '.'; }
inline std::string_view trim(std::string_view s) {
  while (!s.empty() && (space(s.front()) || sep(s.front()))) s.remove_prefix(1);
  while (!s.empty() && (space(s.back()) || sep(s.back()))) s.remove_suffix(1);
  return s;
}
inline std::string fold(std::string_view s) {
  std::string out;
  for (char c : trim(s)) out += lower(c);
  if (out.size() > 1 && out.back() == 's') out.pop_back();
  return out;
}
}  // namespace title_echo_detail

// Whether `heading` names the row labelled `label`.
inline bool names_row(std::string_view heading, std::string_view label) {
  using namespace title_echo_detail;
  heading = trim(heading);
  label = trim(label);
  if (heading.empty() || label.empty()) return false;
  if (label.size() >= heading.size()) {
    bool same = true;
    for (size_t i = 0; i < heading.size() && same; ++i) same = lower(label[i]) == lower(heading[i]);
    if (same && (label.size() == heading.size() || sep(label[heading.size()]))) return true;
  }
  size_t end = 0;
  while (end < label.size() && !sep(label[end])) ++end;
  return fold(heading) == fold(label.substr(0, end));
}

// The title to say when the screen was opened by confirming a row labelled `label` (empty: none): without its first
// sentence when that names the row. The rest, a question or a prompt ("Tactics. Give an order?"), stays.
inline std::string drop_echoed_title(std::string_view title, std::string_view label) {
  using namespace title_echo_detail;
  size_t cut = title.find(". ");
  if (!names_row(title.substr(0, cut), label)) return std::string(title);
  return cut == std::string_view::npos ? std::string() : std::string(trim(title.substr(cut + 2)));
}
// Whether a heading made of rows confirmed on the way here names them all ("Buy Weapon, for Colton" after Buy Weapon,
// then Colton): every comma-separated part, a leading "for" aside, names one of `labels`, and one names the last.
inline bool names_rows(std::string_view heading, const std::vector<std::string>& labels) {
  using namespace title_echo_detail;
  if (labels.empty()) return false;
  bool last = false;
  for (size_t at = 0; at <= heading.size();) {
    size_t end = heading.find(", ", at);
    if (end == std::string_view::npos) end = heading.size();
    std::string_view part = trim(heading.substr(at, end - at));
    if (part.size() > 4 && lower(part[0]) == 'f' && lower(part[1]) == 'o' && lower(part[2]) == 'r' && part[3] == ' ')
      part.remove_prefix(4);
    bool any = false;
    for (const auto& l : labels) if (names_row(part, l)) { any = true; if (&l == &labels.back()) last = true; }
    if (!any) return false;
    at = end + 2;
  }
  return last;
}
}  // namespace p3a::core
