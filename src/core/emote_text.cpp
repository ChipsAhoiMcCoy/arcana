#include "emote_text.h"
#include "strings.h"

namespace p3a::core {

const char* emote_mark(std::string_view cls) {
  constexpr std::string_view head = "BP_Handwriting_Effect_", tail = "_C";
  if (!cls.starts_with(head) || !cls.ends_with(tail) || cls.size() <= head.size() + tail.size()) return "";
  std::string_view kind = cls.substr(head.size(), cls.size() - head.size() - tail.size());
  for (const auto& e : strings::kEmoteMarks)
    if (kind.starts_with(e.kind)) return e.text;
  return "";
}

std::string emote_line(std::string_view mark, std::string_view who) {
  std::string out(mark);
  if (out.empty()) return out;
  if (!who.empty()) out = strings::fmt(strings::kEmoteOverFmt, out, who);
  return out;
}

}  // namespace p3a::core
