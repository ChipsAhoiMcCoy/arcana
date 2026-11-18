#include "core/speech_text.h"
#include "core/strings.h"
#include "core/text_clean.h"
#include <format>

namespace p3a::core {
std::string position(std::string_view text, size_t place, size_t count) {
  return std::format("{}, {} {} {}", text, place, strings::kOf, count);
}

std::string place_of(int place, int count) { return std::format("{} {} {}", place, strings::kOf, count); }

std::string spoken_line(std::string_view speaker, std::string_view text) {
  // A page of "......" names its marks: after a name it was "Junpei:" and nothing (the player's report, 2026-11-17).
  if (speaker.empty()) return speakable(text);
  // A speaker the game hides is "???": a screen reader says nothing for it.
  std::string out = speaker.find_first_not_of('?') == std::string_view::npos ? std::string(strings::kUnknownCap) : std::string(speaker);
  out += ": ";
  out += speakable(text);
  return out;
}

std::string without_own_stop(std::string s) {
  if (s.size() >= 2 && s.back() == '.' && s[s.size() - 2] != '.') s.pop_back();
  return s;
}

bool all_filled(const std::vector<std::string>& entries) {
  if (entries.empty()) return false;
  for (auto& e : entries) if (e.empty()) return false;
  return true;
}

std::string no_digits(std::string_view s) {
  std::string out;
  for (char ch : s) {
    bool d = ch >= '0' && ch <= '9';
    if (!d) out += ch;
    else if (out.empty() || out.back() != '#') out += '#';
  }
  return out;
}

std::string sentence(std::string s) {
  if (!s.empty() && s.back() != '.' && s.back() != '?' && s.back() != '!') s += '.';
  return s;
}
}  // namespace p3a::core
