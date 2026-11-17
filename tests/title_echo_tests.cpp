#include "doctest.h"
#include "core/title_echo.h"

using p3a::core::drop_echoed_title;

TEST_CASE("title_echo: the title naming the confirmed row is dropped") {
  CHECK(drop_echoed_title("Item", "Item") == "");
  CHECK(drop_echoed_title("Social Link", "Social Link") == "");
  CHECK(drop_echoed_title("Items", "Item") == "");
  CHECK(drop_echoed_title("Skill", "skills") == "");
}

TEST_CASE("title_echo: a tail on the row's label does not stop the match") {
  CHECK(drop_echoed_title("Persona", "Persona, Unavailable") == "");
  CHECK(drop_echoed_title("Mail", "Mail. 3 new") == "");
}

TEST_CASE("title_echo: the rest of the title stays") {
  CHECK(drop_echoed_title("Tactics. Give an order?", "Tactics") == "Give an order?");
}

TEST_CASE("title_echo: the landing loses a leading name that is the confirmed row's") {
  using p3a::core::drop_echoed_prefix;
  CHECK(drop_echoed_prefix("Colton, Weapon: Long Wakizashi, 1 of 5", "Colton, HP 165 of 165, 1 of 3") ==
        "Weapon: Long Wakizashi, 1 of 5");
  CHECK(drop_echoed_prefix("Colton", "Colton, HP 165 of 165") == "Colton");
  CHECK(drop_echoed_prefix("Coltons, Weapon", "Colton") == "Coltons, Weapon");
  CHECK(drop_echoed_prefix("Yukari, Weapon: Bow", "Colton, HP 1") == "Yukari, Weapon: Bow");
  CHECK(drop_echoed_prefix("Yukari, Weapon: Bow", "") == "Yukari, Weapon: Bow");
}

TEST_CASE("title_echo: another title, or no row, keeps the title") {
  CHECK(drop_echoed_title("Config", "System") == "Config");
  CHECK(drop_echoed_title("Item", "") == "Item");
  CHECK(drop_echoed_title("Items", "Itemize") == "Items");
  CHECK(drop_echoed_title("", "Item") == "");
}
