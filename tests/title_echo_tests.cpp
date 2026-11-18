#include "doctest.h"
#include "core/title_echo.h"

using p3a::core::drop_echoed_title;
using p3a::core::names_row;
using p3a::core::names_rows;

TEST_CASE("title_echo: a heading names the row it starts") {
  CHECK(names_row("Colton", "Colton, HP 165 of 165, SP 112 of 112"));
  CHECK(names_row("Armor", "Armor: Bulletproof Shirt, defense 65"));
  CHECK(names_row("Mail", "Mail. 3 new"));
  CHECK(names_row("Social Link", "Social Link"));
  CHECK(names_row("Items", "Item"));
  CHECK(names_row("skill", "Skill, Unavailable"));
}

TEST_CASE("title_echo: a heading that is not the row's name does not") {
  CHECK_FALSE(names_row("Yukari", "Colton, HP 165"));
  CHECK_FALSE(names_row("Colton", "Coltonia, HP 1"));
  CHECK_FALSE(names_row("Item", "Itemize"));
  CHECK_FALSE(names_row("Consumable Items", "Item"));
  CHECK_FALSE(names_row("Armor", ""));
  CHECK_FALSE(names_row("", "Armor"));
}

TEST_CASE("title_echo: the title naming the confirmed row is dropped") {
  CHECK(drop_echoed_title("Item", "Item") == "");
  CHECK(drop_echoed_title("Items", "Item") == "");
  CHECK(drop_echoed_title("Persona", "Persona, Unavailable") == "");
  CHECK(drop_echoed_title("Equip", "Equip: View or change equipment") == "");
}

TEST_CASE("title_echo: the rest of the title stays") {
  CHECK(drop_echoed_title("Tactics. Give an order?", "Tactics") == "Give an order?");
}

TEST_CASE("title_echo: another title, or no row, keeps the title") {
  CHECK(drop_echoed_title("Config", "System") == "Config");
  CHECK(drop_echoed_title("Item", "") == "Item");
  CHECK(drop_echoed_title("Items", "Itemize") == "Items");
  CHECK(drop_echoed_title("", "Item") == "");
}

TEST_CASE("title_echo: a heading made of the rows confirmed on the way") {
  std::vector<std::string> path{"Buy Weapon", "Colton"};
  CHECK(names_rows("Buy Weapon, for Colton", path));
  CHECK(names_rows("Colton", path));
  CHECK_FALSE(names_rows("Buy Weapon", path));                 // the last confirm is not in it
  CHECK_FALSE(names_rows("Buy Armor, for Colton", path));      // a part nobody confirmed
  CHECK_FALSE(names_rows("Buy Weapon, for Colton", std::vector<std::string>{}));
}
