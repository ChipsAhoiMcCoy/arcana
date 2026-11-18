#include "doctest.h"
#include "core/heard_cues.h"

using p3a::core::HeardCues;

TEST_CASE("heard_cues: a description heard is known by its scene and text") {
  HeardCues h;
  CHECK_FALSE(h.heard("LS_Event_Extr_450_020_C", "You drink your coffee."));
  CHECK(h.add(HeardCues::id("LS_Event_Extr_450_020_C", "You drink your coffee.")));
  CHECK(h.heard("LS_Event_Extr_450_020_C", "You drink your coffee."));
  CHECK_FALSE(h.add(HeardCues::id("LS_Event_Extr_450_020_C", "You drink your coffee.")));   // not new
}

TEST_CASE("heard_cues: another scene or a rewritten text is new") {
  HeardCues h;
  h.add(HeardCues::id("LS_Event_Extr_460_010_C", "You work behind the counter."));
  CHECK_FALSE(h.heard("LS_Event_Extr_460_015_C", "You work behind the counter."));
  CHECK_FALSE(h.heard("LS_Event_Extr_460_010_C", "You work behind the café counter."));
}

TEST_CASE("heard_cues: the file's lines read back; malformed ones are left out") {
  HeardCues h;
  std::string id = HeardCues::id("LS_Event_Main_110_210_C", "Mitsuru sits on the sofa.");
  CHECK(h.add_line(id + "\r\n"));
  CHECK(h.heard("LS_Event_Main_110_210_C", "Mitsuru sits on the sofa."));
  CHECK_FALSE(h.add_line("garbage"));
  CHECK_FALSE(h.add_line("LS_X 12345"));
  CHECK_FALSE(h.add_line("LS_X 0123456789abcdeZ"));
  CHECK_FALSE(h.add_line(" 0123456789abcdef"));
  CHECK(h.size() == 1);
}
