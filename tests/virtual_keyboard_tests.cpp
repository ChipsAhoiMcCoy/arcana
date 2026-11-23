#include "core/virtual_keyboard.h"
#include "doctest.h"

using p3a::core::VirtualKeyboard;
using Move = VirtualKeyboard::Move;
using Action = VirtualKeyboard::Action;

TEST_CASE("the keyboard opens on q and reads each key with its place") {
  VirtualKeyboard k;
  k.reset();
  CHECK(k.key_name() == "q");
  CHECK(k.move(Move::Right, false) == "w, 2 of 10");
  CHECK(k.move(Move::Down, false) == "s, row 3");
  CHECK(k.move(Move::Up, false) == "w, row 2");
  CHECK(k.move(Move::Up, false) == "2, row 1");
  CHECK(k.where() == "2, 2 of 10, row 1");
}

TEST_CASE("edges do not wrap: the key again on a press, nothing on a held repeat") {
  VirtualKeyboard k;
  k.reset();
  CHECK(k.move(Move::Left, false) == "q");
  CHECK(k.move(Move::Left, true) == "");
  CHECK(k.col() == 0);
}

TEST_CASE("the action row is four wide and keeps the place across rows") {
  VirtualKeyboard k;
  k.reset();
  for (int i = 0; i < 9; ++i) k.move(Move::Right, false);   // p
  k.move(Move::Down, false);                                  // l, the last of nine
  CHECK(k.key_name() == "l");
  CHECK(k.move(Move::Down, false) == "apostrophe, row 4");
  CHECK(k.move(Move::Down, false) == "Done, row 5");
  CHECK(k.activate("Abc").action == Action::Done);
  CHECK(k.move(Move::Left, false) == "Erase, 3 of 4");
  CHECK(k.activate("Abc").action == Action::Erase);
  CHECK(k.move(Move::Left, false) == "Capitals, 2 of 4");
  CHECK(k.move(Move::Left, false) == "space, 1 of 4");
  auto p = k.activate("Abc");
  CHECK(p.action == Action::Type);
  CHECK(p.text == " ");
}

TEST_CASE("a name's letters: a capital at the start and after a space or dash") {
  VirtualKeyboard k;
  k.reset();
  CHECK(k.activate("").text == "Q");
  CHECK(k.activate("Ab").text == "q");
  CHECK(k.activate("Ab ").text == "Q");
  CHECK(k.activate("Ab-").text == "Q");
  CHECK(k.toggle_capitals() == "Capitals on");
  CHECK(k.key_name() == "capital Q");
  CHECK(k.move(Move::Right, false) == "capital W, 2 of 10");
  k.move(Move::Left, false);
  CHECK(k.activate("Ab").text == "Q");
  CHECK(k.toggle_capitals() == "Capitals off");
  k.move(Move::Up, false);
  CHECK(k.activate("").text == "1");
}
