#pragma once
#include <string>
#include <string_view>

namespace p3a::core {
// The marks the game draws over a character's head for a moment (a "!" of surprise, a sweat drop, "Zzz"): the
// handwriting effects, BP_Handwriting_Effect_<kind>_C (EAtlEvtHandwritingType). Engine-free.
// The mark's words for an effect class's name, or "" for one not known.
const char* emote_mark(std::string_view class_name);
// What is said: "Question mark over Junpei", "Sweat drop over you", or the mark alone when nobody is named.
std::string emote_line(std::string_view mark, std::string_view who);
}  // namespace p3a::core
