#include "core/text_clean.h"
#include "core/strings.h"
#include <cctype>
#include <cstring>
#include <vector>

namespace p3a::core {
// Punctuation that closes what came before: a space left in front of it by a dropped icon ("Thanks @.") or a row
// break would leave it alone, and a lone "." is read as "dot" (NVDA at punctuation level some, and eSpeak itself).
// Japanese and Chinese full stops: 。 ！ ？ (E3 80 82, EF BC 81, EF BC 9F): the bytes of the one at i, or 0.
static size_t wide_stop(std::string_view s, size_t i) {
  if (i + 3 > s.size()) return 0;
  auto b = [&](size_t k) { return (unsigned char)s[i + k]; };
  if (b(0) == 0xE3 && b(1) == 0x80 && b(2) == 0x82) return 3;
  if (b(0) == 0xEF && b(1) == 0xBC && (b(2) == 0x81 || b(2) == 0x9F)) return 3;
  return 0;
}
// A Japanese or Chinese character (kana, ideographs, their punctuation: lead bytes E3 to E9, and the full-width forms
// EF BC / EF BD): text with no spaces between words, where a line break is no word break. Korean (EA to ED) has spaces.
static bool unspaced(unsigned char lead) { return (lead >= 0xE3 && lead <= 0xE9) || lead == 0xEF; }

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
  bool space = false, line_start = true, real_space = false;
  size_t last_lead = std::string::npos;   // where the last character written began
  for (size_t i = 0; i < s.size(); ++i) {
    unsigned char c = (unsigned char)s[i];
    if (c == '\n' || c == '\r' || c == '\t' || c == ' ') {
      space = true;
      if (c == ' ' || c == '\t') real_space = true;
      if (c == '\n') line_start = true;
      continue;
    }
    if (c < 0x20) continue;
    // '@' is what BmdPageToFString leaves for an inline emote icon (a page of just "@" is a speaker's sweat drop or
    // similar, seen 2026-10-27): drop it, so such a page is silent.
    if (c == '@') continue;
    // U+2022 BULLET (E2 80 A2) and U+30FB KATAKANA MIDDLE DOT (E3 83 BB) as list markers at a line start.
    if (line_start && i + 2 < s.size() && c == 0xE2 && (unsigned char)s[i + 1] == 0x80 && (unsigned char)s[i + 2] == 0xA2) { i += 2; space = true; continue; }
    if (line_start && i + 2 < s.size() && c == 0xE3 && (unsigned char)s[i + 1] == 0x83 && (unsigned char)s[i + 2] == 0xBB) { i += 2; space = true; continue; }
    // U+3000 IDEOGRAPHIC SPACE
    if (i + 2 < s.size() && c == 0xE3 && (unsigned char)s[i + 1] == 0x80 && (unsigned char)s[i + 2] == 0x80) { i += 2; space = true; continue; }
    // a line break inside Japanese or Chinese text joins the two lines with nothing between them
    bool joined = !real_space && last_lead != std::string::npos && unspaced((unsigned char)out[last_lead]) && unspaced(c);
    // a line broken after a hyphen or slash inside a word ("old-\nschool", "Confuse/\nCharm") joins with no space
    bool split = !real_space && out.size() >= 2 && (out.back() == '-' || out.back() == '/') &&
                 ((unsigned char)out[out.size() - 2] >= 0x80 || std::isalnum((unsigned char)out[out.size() - 2]));
    if (space && !out.empty() && !closes(s, i) && !joined && !split) out += ' ';
    space = false;
    real_space = false;
    line_start = false;
    if ((c & 0xC0) != 0x80) last_lead = out.size();
    out += (char)c;
  }
  return out;
}
bool has_words(std::string_view s) {
  for (unsigned char c : s) if (c >= 0x80 || (c >= '0' && c <= '9') || ((c | 0x20) >= 'a' && (c | 0x20) <= 'z')) return true;
  return false;
}

std::string without_last_sentence_naming(std::string_view s, std::string_view who) {
  std::string_view t = s;
  while (!t.empty() && t.back() == ' ') t.remove_suffix(1);
  if (who.empty() || t.empty()) return std::string(s);
  // the end of the sentence before the last: a stop followed by a space, or a wide stop
  size_t cut = std::string_view::npos;
  for (size_t i = 0; i + 1 < t.size(); ++i) {
    if ((t[i] == '.' || t[i] == '!' || t[i] == '?') && t[i + 1] == ' ') cut = i + 1;
    else if (size_t n = wide_stop(t, i); n && i + n < t.size()) cut = i + n;
  }
  if (cut == std::string_view::npos) return std::string(s);
  std::string_view last = t.substr(cut);
  if (last.find(who) == std::string_view::npos) return std::string(s);
  std::string out(t.substr(0, cut));
  while (!out.empty() && out.back() == ' ') out.pop_back();
  return out;
}

std::string first_sentence(std::string_view s) {
  for (size_t i = 0; i + 1 < s.size(); ++i) {
    if (s[i] == '.' && i > 0 && s[i - 1] == '.') continue;   // an ellipsis does not end a sentence
    if ((s[i] == '.' || s[i] == '!' || s[i] == '?') && s[i + 1] == ' ') return std::string(s.substr(0, i + 1));
    if (size_t n = wide_stop(s, i); n && i + n < s.size()) return std::string(s.substr(0, i + n));   // 。！？ need no space
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
  if (j >= 3 && wide_stop(out, j - 3)) return true;
  return j >= 3 && (unsigned char)out[j - 3] == 0xE2 && (unsigned char)out[j - 2] == 0x80 && (unsigned char)out[j - 1] == 0xA6;   // U+2026
}
std::string clean_lines(std::string_view s) {
  std::string out;
  size_t lead = std::string::npos;   // where the last character written began
  while (!s.empty()) {
    size_t nl = s.find('\n');
    std::string line = clean_text(s.substr(0, nl));
    s = nl == std::string_view::npos ? std::string_view() : s.substr(nl + 1);
    if (!has_words(line)) continue;
    if (!out.empty()) {
      bool wide = unspaced((unsigned char)out[lead]);
      char last = out.back();
      if (!ends_sentence(out) && last != ':' && last != ',' && last != ';') out += wide ? "\xE3\x80\x82" : ".";
      if (!wide) out += ' ';
    }
    out += line;
    for (size_t i = out.size(); i-- > 0;) if (((unsigned char)out[i] & 0xC0) != 0x80) { lead = i; break; }
  }
  return out;
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
      bool mark = !out.empty() && (out.back() == '!' || out.back() == '?' || (out.size() >= 3 && wide_stop(out, out.size() - 3)));
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

bool is_question(std::string_view s) {
  while (!s.empty() && (s.back() == ' ' || s.back() == '\n')) s.remove_suffix(1);
  // a note in brackets after the question
  if (s.ends_with(')')) { if (size_t q = s.rfind('('); q != std::string_view::npos) s = s.substr(0, q); }
  else if (s.ends_with("\xEF\xBC\x89")) { if (size_t q = s.rfind("\xEF\xBC\x88"); q != std::string_view::npos) s = s.substr(0, q); }
  while (!s.empty() && s.back() == ' ') s.remove_suffix(1);
  return s.ends_with('?') || s.ends_with("\xEF\xBC\x9F");
}
}  // namespace p3a::core
