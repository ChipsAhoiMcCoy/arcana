// The staff rolls. Both draw the names as sprites with their own draw actor (AStaffRollDraw) and say nothing, so each
// is announced and the silence is not taken for a hang.
// - The ending's (AStaffRoll, over a movie; no input; seen at the ending, 2026-11-11: "Credits" as the roll began).
// - The title menu's (ATitleCredit): Z or L1 on the title menu opens it (UTitleStateSelect's tick,
//   FUN_1410a89b0(10, 0x1a) -> FUN_141551290) and locks the menu under it (the select struct's +0x08) until it ends;
//   a player who pressed Z there was left in a silent game that took no keys (2026-11-17). ATitleCredit +0x2ba (u16)
//   is its step: 0 idle, 1 opening, 2..8 rolling, 9 / 10 ending (FUN_1410bd270). Its input (FUN_1410be240): the first
//   press of OK, Back, Tab (the Menu button) or a few others pauses the roll and shows the skip prompt (+0x2b9 set);
//   then OK or Back resumes it and Tab skips (+0x2b8 set: the roll fades out and ends).
// The review key reads what is rolling past: the roll's rows are UStaffRollDataAsset.Data (pStaffRollDataList on
// either actor; up to four name columns a row), and the draw (pStaffRollDraw) keeps the first row not yet rolled off
// at +0x3A730 (it went 5, then 10 ten seconds on, of 750). The whole roll is never read unasked: hundreds of names.
#include "screens/screen.h"
#include "screens/util.h"
#include "core/strings.h"
#include "seh.h"
#include "speech.h"

namespace p3a::screens {
using namespace ue;

class CreditsScreen : public Screen {
  Finder roll_{"StaffRoll"};
  Finder title_{"TitleCredit"};
  int paused_ = -1;   // the title roll's pause, as last said (-1: not said yet)

  UObject* title_roll() {
    UObject* a = title_.get();
    if (!a || is_cdo(a)) return nullptr;
    int step = *(uint16_t*)((uint8_t*)a + 0x2ba);
    return step >= 1 && step <= 9 ? a : nullptr;
  }
  // The actor whose roll is up: the ending's or the title's.
  UObject* source() {
    UObject* r = roll_.get();
    if (r && get<UObject*>(r, "pStaffRollDraw")) return r;
    return title_roll();
  }
  bool title_paused() {
    UObject* a = title_roll();
    return a && ((uint8_t*)a)[0x2b9] && !((uint8_t*)a)[0x2b8];
  }
  std::string state_line() {
    if (!title_roll()) return strings::kCredits.c_str();
    return title_paused() ? strings::kCreditsPaused() : strings::kCreditsRolling();
  }

 public:
  const char* id() const override { return "credits"; }
  int priority() const override { return 6; }   // over the movie the ending's plays on, and the title menu
  bool holds_loading() const override { return true; }
  bool active() override { return source() != nullptr; }
  void enter() override {
    paused_ = -1;
    if (title_roll()) screens::set_keys(strings::kCreditsKeys);
  }
  void tick() override {
    if (!title_roll()) {
      if (paused_ < 0) speech::speak(strings::kCredits.c_str(), true);
      paused_ = 0;
      return;
    }
    int p = title_paused() ? 1 : 0;
    if (paused_ < 0) speech::speak(state_line(), true);
    else if (p != paused_) speech::speak(p ? strings::kCreditsPaused() : strings::kCreditsResumed, true);
    paused_ = p;
  }
  std::string describe() override {
    std::string out = state_line();
    UObject* r = source();
    UObject* draw = r ? get<UObject*>(r, "pStaffRollDraw") : nullptr;
    UObject* list = r ? get<UObject*>(r, "pStaffRollDataList") : nullptr;
    if (!draw || !list || !ue::known_build()) return out;
    TableRows rows = table_rows(list);
    static const char* const kColumns[] = {"FirstColumnName", "SecondColumnName", "ThirdColumnName", "ForthColumnName"};
    guarded([&] {
      int at = *(int32_t*)((uint8_t*)draw + 0x3A730);
      if (!rows || at < 0) return;
      // A screenful from the first row still rolling.
      bool first = true;
      for (int i = at; i < rows.num && i < at + 8; ++i)
        for (const char* col : kColumns) {
          int off = offset_of(rows.row, col);
          if (off < 0) continue;
          std::string t = to_utf8(*(FString*)(rows.at(i) + off));
          if (!t.empty()) { out += (first ? ". " : ", ") + t; first = false; }
        }
    });
    return out;
  }
};

std::unique_ptr<Screen> make_credits() { return std::make_unique<CreditsScreen>(); }
}  // namespace p3a::screens
