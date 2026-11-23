#include "core/virtual_keyboard.h"
#include "core/speech_text.h"
#include "core/strings.h"
#include "core/text_field.h"
#include <algorithm>
#include <cctype>
#include <format>
#include <iterator>

namespace p3a::core {
namespace {
// The grid, QWERTY. The last row's keys are words (the actions).
constexpr const char* kGrid[VirtualKeyboard::kRows] = {"1234567890", "qwertyuiop", "asdfghjkl", "zxcvbnm-'.", ""};
constexpr VirtualKeyboard::Action kLast[] = {VirtualKeyboard::Action::Type, VirtualKeyboard::Action::Capitals,
                                             VirtualKeyboard::Action::Erase, VirtualKeyboard::Action::Done};
constexpr size_t kLastRow = VirtualKeyboard::kRows - 1;

std::string char_name(char c, bool caps) {
  switch (c) {
    case '-': return strings::kVkDash.c_str();
    case '\'': return strings::kVkApostrophe.c_str();
    case '.': return strings::kVkPeriod.c_str();
    default: return spoken_char(std::string(1, caps ? (char)std::toupper((unsigned char)c) : c));
  }
}
}  // namespace

void VirtualKeyboard::reset() { row_ = 1; col_ = 0; caps_ = false; }

size_t VirtualKeyboard::row_length(size_t r) const {
  if (r == kLastRow) return std::size(kLast);
  return r < kRows ? std::string_view(kGrid[r]).size() : 0;
}

std::string VirtualKeyboard::key_name() const {
  if (row_ == kLastRow) {
    switch (kLast[col_]) {
      case Action::Type: return strings::kVkSpace.c_str();
      case Action::Capitals: return strings::kVkCapitals.c_str();
      case Action::Erase: return strings::kVkErase.c_str();
      default: return strings::kVkDone.c_str();
    }
  }
  return char_name(kGrid[row_][col_], caps_);
}

std::string VirtualKeyboard::where() const {
  return std::format("{}, {} {}", position(key_name(), col_ + 1, row_length(row_)), strings::kRow, row_ + 1);
}

std::string VirtualKeyboard::move(Move m, bool repeat) {
  size_t r = row_, c = col_;
  switch (m) {
    case Move::Left: if (c > 0) --c; break;
    case Move::Right: if (c + 1 < row_length(r)) ++c; break;
    case Move::Up: if (r > 0) --r; break;
    case Move::Down: if (r + 1 < kRows) ++r; break;
  }
  if (r == row_ && c == col_) return repeat ? std::string() : key_name();   // an edge
  bool across = r == row_;
  if (!across) {
    // The same column, or the row's last key where it is shorter; to and from the four-wide action row, the same
    // part of the row.
    size_t from = row_length(row_), to = row_length(r);
    c = (r == kLastRow || row_ == kLastRow) ? std::min(to - 1, col_ * to / from) : std::min(to - 1, col_);
  }
  row_ = r;
  col_ = c;
  if (across) return position(key_name(), col_ + 1, row_length(row_));
  return std::format("{}, {} {}", key_name(), strings::kRow, row_ + 1);
}

VirtualKeyboard::Press VirtualKeyboard::activate(const std::string& before) {
  if (row_ == kLastRow) {
    Action a = kLast[col_];
    return a == Action::Type ? Press{Action::Type, " "} : Press{a, {}};
  }
  char c = kGrid[row_][col_];
  if (std::isalpha((unsigned char)c)) {
    bool start = before.empty() || before.back() == ' ' || before.back() == '-';
    if (caps_ || start) c = (char)std::toupper((unsigned char)c);
  }
  return {Action::Type, std::string(1, c)};
}

std::string VirtualKeyboard::toggle_capitals() {
  caps_ = !caps_;
  return caps_ ? strings::kCapitalsOn.c_str() : strings::kCapitalsOff.c_str();
}

}  // namespace p3a::core
