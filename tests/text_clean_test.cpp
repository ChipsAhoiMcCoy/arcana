#include "doctest.h"
#include "core/text_clean.h"
using p3a::core::clean_text;

TEST_CASE("clean_text joins lines and drops bullets") {
  CHECK(clean_text("\xE2\x80\xA2 A device was\ndisconnected.\n\nPressing any button") == "A device was disconnected. Pressing any button");
  CHECK(clean_text("  hello   world  ") == "hello world");
  CHECK(clean_text("a\x01" "b") == "ab");
  CHECK(clean_text("") == "");
  CHECK(clean_text("@") == "");
  CHECK(clean_text("Hey @ you") == "Hey you");
}
TEST_CASE("clean_text joins a word broken after a hyphen or slash") {
  CHECK(clean_text("An old-\nschool sword.") == "An old-school sword.");
  CHECK(clean_text("Inflicts Confuse/\nCharm.") == "Inflicts Confuse/Charm.");
  CHECK(clean_text("Wait -\nwhat") == "Wait - what");      // a dash between words keeps its spaces
  CHECK(clean_text("well- guarded") == "well- guarded");   // a written space stays
}
TEST_CASE("clean_lines ends each line as a sentence") {
  using p3a::core::clean_lines;
  CHECK(clean_lines("24 years old\nFemale\nPart-time worker\nDisappeared on 6/25 during a break.\n") ==
        "24 years old. Female. Part-time worker. Disappeared on 6/25 during a break.");
  CHECK(clean_lines("Done!\n\nNext:\nthing") == "Done! Next: thing");
  CHECK(clean_lines("") == "");
  CHECK(clean_lines("Serve coffee that boosts a person's charm!\nTime: Night\nPay: 2,500+ daily\nLocation: Paulownia Mall") ==
        "Serve coffee that boosts a person's charm! Time: Night. Pay: 2,500+ daily. Location: Paulownia Mall");
  CHECK(clean_lines("\xE5\xA5\xB3\xE6\x80\xA7\n\xE4\xBC\x9A\xE7\xA4\xBE\xE5\x93\xA1") ==
        "\xE5\xA5\xB3\xE6\x80\xA7\xE3\x80\x82\xE4\xBC\x9A\xE7\xA4\xBE\xE5\x93\xA1");
}
TEST_CASE("clean_text keeps closing punctuation on its word") {
  CHECK(clean_text("Thanks @.") == "Thanks.");
  CHECK(clean_text("Thanks\n.") == "Thanks.");
  CHECK(clean_text("Wait ... what ?") == "Wait... what?");
  CHECK(clean_text("Yukari: ...Hm? The list.") == "Yukari: ...Hm? The list.");
  CHECK(clean_text("I see @...") == "I see...");
  CHECK(clean_text("He said \"no\" .") == "He said \"no\".");
}
TEST_CASE("has_words") {
  CHECK(p3a::core::has_words("...a"));
  CHECK_FALSE(p3a::core::has_words("... !"));
}
TEST_CASE("first_sentence") {
  CHECK(p3a::core::first_sentence("Low-stress combat. Your choice...") == "Low-stress combat.");
  CHECK(p3a::core::first_sentence("No stop") == "No stop");
  CHECK(p3a::core::first_sentence("Wait... really? Yes.") == "Wait... really?");
}
TEST_CASE("tidy_joins drops a comma or period after a sentence's end") {
  using p3a::core::tidy_joins;
  CHECK(tidy_joins("Then choose a party member., 3 of 4") == "Then choose a party member. 3 of 4");
  CHECK(tidy_joins("2 choices: Kinda., How so?") == "2 choices: Kinda. How so?");
  CHECK(tidy_joins("Running late?, Not feeling well?") == "Running late? Not feeling well?");
  CHECK(tidy_joins("1 ally's HP.. Slightly") == "1 ally's HP. Slightly");
  CHECK(tidy_joins("Junpei Iori. yo!. y'know") == "Junpei Iori. yo! y'know");
  CHECK(tidy_joins("Fine..., Okay.") == "Fine... Okay.");
  CHECK(tidy_joins("member. , 3 of 4") == "member. 3 of 4");
  CHECK(tidy_joins("member. . 3 of 4") == "member. 3 of 4");
  CHECK(tidy_joins("Hm\xE2\x80\xA6. Next") == "Hm\xE2\x80\xA6 Next");
}
TEST_CASE("tidy_joins leaves ellipses, numbers and plain commas") {
  using p3a::core::tidy_joins;
  CHECK(tidy_joins("Thinking: ......") == "Thinking: ......");
  CHECK(tidy_joins("Yukari: ...Hm? The list.") == "Yukari: ...Hm? The list.");
  CHECK(tidy_joins("Wait.... what") == "Wait.... what");
  CHECK(tidy_joins("Dia, 3 SP, 1 of 1. Restores 1,000 HP.") == "Dia, 3 SP, 1 of 1. Restores 1,000 HP.");
  CHECK(tidy_joins("Ver. 1.5, ok") == "Ver. 1.5, ok");
}

TEST_CASE("speakable names a line that is only punctuation") {
  using p3a::core::speakable;
  CHECK(speakable("......") == "ellipsis");
  CHECK(speakable("...") == "ellipsis");
  CHECK(speakable("\xE2\x80\xA6") == "ellipsis");
  CHECK(speakable("?") == "question mark");
  CHECK(speakable("......!?") == "ellipsis, exclamation mark, question mark");
  CHECK(speakable("!!!") == "exclamation mark");
  CHECK(speakable("...Huh?") == "...Huh?");
  CHECK(speakable("Yes.") == "Yes.");
  CHECK(speakable("") == "");
  CHECK(speakable(" ") == " ");
  CHECK(speakable("...?") == "ellipsis, question mark");
}

TEST_CASE("is_question: a closing ?, before a note in brackets too, full-width in Japanese and Chinese") {
  using p3a::core::is_question;
  CHECK(is_question("Do you want to quit?"));
  CHECK(is_question("Quit? \n"));
  CHECK(is_question("Keep these changes? (Settings will revert in 10 seconds.)"));
  CHECK(is_question("\xE8\xA8\xAD\xE5\xAE\x9A\xEF\xBC\x9F"));                                      // full-width ?
  CHECK(is_question("\xE4\xBF\x9D\xE5\xAD\x98\xEF\xBC\x9F\xEF\xBC\x88" "10\xEF\xBC\x89"));   // ? then a full-width bracketed note
  CHECK_FALSE(is_question("Saved."));
  CHECK_FALSE(is_question("(Is this a question?) No."));
  CHECK_FALSE(is_question("A note (really?)"));   // the bracketed part is dropped: "A note"
  CHECK_FALSE(is_question(""));
}
