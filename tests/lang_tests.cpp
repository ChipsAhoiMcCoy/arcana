#include "doctest.h"

#include <string>

#include "core/lang.h"
#include "core/strings.h"

using namespace p3a;
namespace lang = p3a::core::lang;

TEST_CASE("lang: cultures map to the mod's languages") {
  CHECK(lang::from_culture("en") == lang::En);
  CHECK(lang::from_culture("en-US") == lang::En);
  CHECK(lang::from_culture("es-ES") == lang::Es);
  CHECK(lang::from_culture("es-419") == lang::Es);
  CHECK(lang::from_culture("pt-BR") == lang::Pt);
  CHECK(lang::from_culture("ja") == lang::Ja);
  CHECK(lang::from_culture("zh-Hans") == lang::ZhHans);
  CHECK(lang::from_culture("zh-CN") == lang::ZhHans);
  CHECK(lang::from_culture("zh-Hant") == lang::ZhHant);
  CHECK(lang::from_culture("zh-TW") == lang::ZhHant);
  CHECK(lang::from_culture("ZH-hant-HK") == lang::ZhHant);
  CHECK(lang::from_culture("nl") == -1);
  CHECK(lang::from_culture("") == -1);
  CHECK(std::string(lang::code(lang::ZhHant)) == "zh-Hant");
}

TEST_CASE("lang: a line is said in the current language, English when it has no translation") {
  const int n = lang::load_text(lang::Fr, "Title menu\tMenu titre\r\nCredits.\\tTab\tCr\\u00e9dits\\n\nbroken line\n\n");
  CHECK(n == 2);
  lang::set(lang::Fr);
  CHECK(std::string(lang::tr("Title menu")) == "Menu titre");
  CHECK(std::string(strings::kTitleMenu) == "Menu titre");
  CHECK(std::string(lang::tr("Credits.\tTab")) == "Cr\\u00e9dits\n");   // \t \n unescaped, an unknown escape kept
  CHECK(std::string(lang::tr("Not translated")) == "Not translated");
  CHECK(lang::tr(std::string_view("Title menu")) == "Menu titre");
  CHECK(std::format("{}", strings::kTitleMenu) == "Menu titre");
  // a line held across a change of language is the Tr, said in the new one
  const strings::Tr held = strings::kTitleMenu;
  lang::set(lang::En);
  CHECK(std::string(held) == "Title menu");
  CHECK(std::string(lang::tr("Title menu")) == "Title menu");
}

TEST_CASE("lang: format strings keep their placeholders") {
  lang::load_text(lang::De, "That's the {}.\tDas ist der {}.\n");
  lang::set(lang::De);
  CHECK(strings::fmt(strings::kBarCustomerIs, "Gast") == "Das ist der Gast.");
  lang::set(lang::En);
  CHECK(strings::fmt(strings::kBarCustomerIs, "guest") == "That's the guest.");
}

TEST_CASE("lang: a word with a context is said without it, and translated apart") {
  CHECK(std::string(strings::kOnTarget) == "on");
  CHECK(lang::tr(std::string_view("@target:on")) == "on");
  lang::load_text(lang::It, "@target:on\tsu\non\tattivo\n");
  lang::set(lang::It);
  CHECK(std::string(strings::kOnTarget) == "su");
  CHECK(std::string(strings::kOn) == "attivo");
  lang::set(lang::En);
}

TEST_CASE("lang: a place is named in English or as the game's language writes it") {
  CHECK(lang::names_place("Thebel, floor 3", "Thebel"));
  lang::load_text(lang::Ru, "@place:Thebel\t\xD0\xA2\xD0\xB5\xD0\xB2\xD0\xB5\xD0\xBB\xD1\x8C|Alt\n");
  lang::set_game(lang::Ru);
  CHECK(lang::names_place("\xD0\xA2\xD0\xB5\xD0\xB2\xD0\xB5\xD0\xBB\xD1\x8C, 3", "Thebel"));
  CHECK(lang::names_place("Alt", "Thebel"));
  CHECK_FALSE(lang::names_place("Arqa", "Thebel"));
  lang::set_game(lang::En);
  CHECK_FALSE(lang::names_place("Alt", "Thebel"));
}

#include "core/text_clean.h"
TEST_CASE("text: Japanese and Chinese punctuation and line breaks") {
  using namespace p3a::core;
  // a line break inside Japanese text is no word break; one between English words is
  CHECK(clean_text("\xE3\x81\x82\xE3\x81\x84\n\xE3\x81\x86") == "\xE3\x81\x82\xE3\x81\x84\xE3\x81\x86");
  CHECK(clean_text("one\ntwo") == "one two");
  CHECK(clean_text("\xE3\x81\x82 \xE3\x81\x84") == "\xE3\x81\x82 \xE3\x81\x84");   // a written space stays
  CHECK(first_sentence("\xE6\x96\x87\xE3\x80\x82\xE6\xAC\xA1") == "\xE6\x96\x87\xE3\x80\x82");
  CHECK(tidy_joins("\xE6\x96\x87\xE3\x80\x82, 1 / 5") == "\xE6\x96\x87\xE3\x80\x82 1 / 5");
  CHECK(without_last_sentence_naming("Light armor. For Yukari.", "Yukari") == "Light armor.");
  CHECK(without_last_sentence_naming("Light armor. Sturdy.", "Yukari") == "Light armor. Sturdy.");
  CHECK(without_last_sentence_naming("\xE9\x8E\xA7\xE3\x80\x82\xE3\x82\x86\xE3\x81\x8B\xE3\x82\x8A\xE7\x94\xA8", "\xE3\x82\x86\xE3\x81\x8B\xE3\x82\x8A") == "\xE9\x8E\xA7\xE3\x80\x82");
}
