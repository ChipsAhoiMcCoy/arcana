#include "core/text_clean.h"
#include "core/strings.h"
#include <cstring>
#include <vector>

namespace p3a::core {
// Punctuation that closes what came before: a space left in front of it by a dropped icon ("Thanks @.") or a row
// break would leave it alone, and a lone "." is read as "dot" (NVDA at punctuation level some, and eSpeak itself).
static bool closes(std::string_view s, size_t i) {
  auto punct = [](char c) { return c == '.' || c == ',' || c == '!' || c == '?' || c == ';' || c == ':'; };
  if (!punct(s[i])) return false;
  size_t j = i;
  while (j < s.size() && punct(s[j])) ++j;
  // An ellipsis that opens a word ("...Hm?") keeps its space.
  bool opens = s[i] == '.' && j < s.size() && s[j] != ' ' && s[j] != '\n' && s[j] != '\r' && s[j] != '"' && s[j] != ')';
  return !opens;
}

std::string clean_text(std::string_view s) {
  std::string out;
  out.reserve(s.size());
  bool space = false, line_start = true;
  for (size_t i = 0; i < s.size(); ++i) {
    unsigned char c = (unsigned char)s[i];
    if (c == '\n' || c == '\r' || c == '\t' || c == ' ') { space = true; if (c == '\n') line_start = true; continue; }
    if (c < 0x20) continue;
    // '@' is what BmdPageToFString leaves for an inline emote icon (a page of just "@" is a speaker's sweat drop or
    // similar, seen 2026-10-27): drop it, so such a page is silent.
    if (c == '@') continue;
    // U+2022 BULLET (E2 80 A2) and U+30FB KATAKANA MIDDLE DOT (E3 83 BB) as list markers at a line start.
    if (line_start && i + 2 < s.size() && c == 0xE2 && (unsigned char)s[i + 1] == 0x80 && (unsigned char)s[i + 2] == 0xA2) { i += 2; space = true; continue; }
    if (line_start && i + 2 < s.size() && c == 0xE3 && (unsigned char)s[i + 1] == 0x83 && (unsigned char)s[i + 2] == 0xBB) { i += 2; space = true; continue; }
    // U+3000 IDEOGRAPHIC SPACE
    if (i + 2 < s.size() && c == 0xE3 && (unsigned char)s[i + 1] == 0x80 && (unsigned char)s[i + 2] == 0x80) { i += 2; space = true; continue; }
    if (space && !out.empty() && !closes(s, i)) out += ' ';
    space = false;
    line_start = false;
    out += (char)c;
  }
  return out;
}
bool has_words(std::string_view s) {
  for (unsigned char c : s) if (c >= 0x80 || (c >= '0' && c <= '9') || ((c | 0x20) >= 'a' && (c | 0x20) <= 'z')) return true;
  return false;
}

std::string first_sentence(std::string_view s) {
  for (size_t i = 0; i + 1 < s.size(); ++i) {
    if (s[i] == '.' && i > 0 && s[i - 1] == '.') continue;   // an ellipsis does not end a sentence
    if ((s[i] == '.' || s[i] == '!' || s[i] == '?') && s[i + 1] == ' ') return std::string(s.substr(0, i + 1));
  }
  return std::string(s);
}

// Lines the mod joins ("<name>, 3 of 4", "<line>. <description>", a choice list) get a comma or a period after text
// that already ends a sentence: "member., 3 of 4", "HP.. Slightly", "yo!. y'know". A screen reader says "dot" for
// ".," (the player's report, 2026-10-30). The comma or the extra period goes; ellipses ("...", "......") stay.
static bool ends_sentence(const std::string& out) {
  size_t j = out.size();
  while (j && out[j - 1] == ' ') --j;
  if (!j) return false;
  char p = out[j - 1];
  if (p == '.' || p == '!' || p == '?') return true;
  return j >= 3 && (unsigned char)out[j - 3] == 0xE2 && (unsigned char)out[j - 2] == 0x80 && (unsigned char)out[j - 1] == 0xA6;   // U+2026
}
std::string tidy_joins(std::string_view s) {
  std::string out;
  out.reserve(s.size());
  for (size_t i = 0; i < s.size(); ++i) {
    char c = s[i];
    if ((c == ',' || c == ';') && ends_sentence(out)) {
      if (!out.empty() && out.back() == ' ' && i + 1 < s.size() && s[i + 1] == ' ') ++i;
      continue;
    }
    if (c == '.') {
      size_t n = 1;
      while (i + n < s.size() && s[i + n] == '.') ++n;
      bool mark = !out.empty() && (out.back() == '!' || out.back() == '?');
      if (n <= 2 && mark) { i += n - 1; continue; }   // "yo!." -> "yo!"
      if (n == 1 && !out.empty() && out.back() != '.' && ends_sentence(out)) {   // "Hm<U+2026>." and "member. . 3 of 4"
        if (out.back() == ' ' && i + 1 < s.size() && s[i + 1] == ' ') ++i;
        continue;
      }
      if (n == 2) { out += '.'; ++i; continue; }       // "HP.." -> "HP."
      out.append(n, '.');                              // one period, or an ellipsis
      i += n - 1;
      continue;
    }
    out += c;
  }
  return out;
}

std::string speakable(std::string_view s) {
  std::vector<const char*> names;
  size_t i = 0;
  auto at = [&](const char* u) { size_t n = std::strlen(u); return s.substr(i, n) == u ? n : 0; };
  while (i < s.size()) {
    char c = s[i];
    const char* name = nullptr;
    size_t n = 0;
    if (c == ' ') { ++i; continue; }
    if (c == '.' || at("\xE2\x80\xA6")) {   // a run of periods and U+2026 HORIZONTAL ELLIPSIS
      size_t dots = 0, j = i;
      while (j < s.size()) {
        if (s[j] == '.') { ++j; ++dots; continue; }
        if (s.substr(j, 3) == "\xE2\x80\xA6") { j += 3; dots += 3; continue; }
        break;
      }
      name = dots >= 2 ? strings::kPunctEllipsis : strings::kPunctPeriod;
      n = j - i;
    } else if (c == '?') name = strings::kPunctQuestion, n = 1;
    else if (c == '!') name = strings::kPunctExclamation, n = 1;
    else if (c == ',') name = strings::kPunctComma, n = 1;
    else if (c == '-') name = strings::kPunctDash, n = 1;
    else if (c == '~') name = strings::kPunctTilde, n = 1;
    else if ((n = at("\xE2\x80\x94")) || (n = at("\xE2\x80\x93"))) name = strings::kPunctDash;   // em / en dash
    else if ((n = at("\xE3\x80\x9C")) || (n = at("\xEF\xBD\x9E"))) name = strings::kPunctTilde;  // wave dash, fullwidth tilde
    else return std::string(s);   // a word, a digit or another glyph: the line speaks for itself
    if (names.empty() || names.back() != name) names.push_back(name);   // "!!!" is one exclamation mark
    i += n;
  }
  if (names.empty()) return std::string(s);
  std::string out;
  for (auto* n : names) { if (!out.empty()) out += ", "; out += n; }
  return out;
}
}  // namespace p3a::core
