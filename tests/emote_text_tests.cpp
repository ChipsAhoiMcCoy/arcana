#include "doctest.h"
#include "core/emote_text.h"
#include <string>

using namespace p3a::core;

TEST_CASE("emote_mark: the mark over a character's head, from the effect's class") {
  CHECK(std::string(emote_mark("BP_Handwriting_Effect_Exclamation_00_C")) == "Exclamation mark");
  CHECK(std::string(emote_mark("BP_Handwriting_Effect_ExclamationQuestion_00_C")) == "Exclamation and question mark");
  CHECK(std::string(emote_mark("BP_Handwriting_Effect_DoubleExclamation_00_C")) == "Double exclamation mark");
  CHECK(std::string(emote_mark("BP_Handwriting_Effect_Sweat_01_C")) == "Sweat drop");
  CHECK(std::string(emote_mark("BP_Handwriting_Effect_AccessIcon_Listen_C")) == "Listening");
  CHECK(std::string(emote_mark("BP_Handwriting_Effect_Base_C")).empty());
  CHECK(std::string(emote_mark("BP_UI_Handwriting_Buzz_00_C")).empty());
}

TEST_CASE("emote_line: the mark and whom it is over") {
  CHECK(emote_line("Question mark", "Junpei") == "Question mark over Junpei");
  CHECK(emote_line("Sweat drop", "you") == "Sweat drop over you");
  CHECK(emote_line("Zzz", "") == "Zzz");
  CHECK(emote_line("", "Junpei").empty());
}
