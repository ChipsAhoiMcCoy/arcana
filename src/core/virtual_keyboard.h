#pragma once
// An on-screen keyboard of the mod's own, for typing a name on a controller (the contract): a QWERTY grid the D-pad
// walks, read key by key. It owns no text: the caller types what activate() hands back into the game's box.
// Engine-free (tests/virtual_keyboard_tests.cpp).
#include <cstddef>
#include <string>

namespace p3a::core {

class VirtualKeyboard {
 public:
  enum class Move { Up, Down, Left, Right };
  enum class Action { None, Type, Erase, Capitals, Done };
  struct Press { Action action = Action::None; std::string text; };   // text: what to type (Type only)

  static constexpr size_t kRows = 5;
  // Back on the first letter (q), capitals off.
  void reset();
  size_t row() const { return row_; }
  size_t col() const { return col_; }
  size_t row_length(size_t r) const;
  bool capitals() const { return caps_; }
  // The key under the cursor as spoken ("q", "Q" with capitals on, "space", "dash").
  std::string key_name() const;
  // The key under the cursor with its place: "w, 2 of 10" across, "a, row 3" up and down. Empty for a move that hits an
  // edge (the edges do not wrap; a held D-pad's repeats stop there quietly) unless it is the first press there, when
  // the key is said again.
  std::string move(Move m, bool repeat);
  // The cursor's key pressed. `before` is the text in the box now: a letter typed at its start, or after a space or a
  // dash, is a capital (names), as is every letter with capitals on.
  Press activate(const std::string& before);
  // Capitals on or off (the Capitals key, or Y): what to say.
  std::string toggle_capitals();
  // The whole keyboard's state for a reread: the key and its place.
  std::string where() const;

 private:
  size_t row_ = 1, col_ = 0;
  bool caps_ = false;
};

}  // namespace p3a::core
