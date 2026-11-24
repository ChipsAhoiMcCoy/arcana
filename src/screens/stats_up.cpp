// The "Stats up! Social stats" screen (Space for OK): AUIGetHeroParameterDraw, made for it and destroyed once it has
// closed, its panel a UCmpHeroHumanStatusDraw (+0xD00 pHumanParamDraw_). Its state +0x294 (previous +0x298, the UI
// actors' common task state) is 6 while it is up and takes OK, then 7, 8 and 9 as it closes (measured 2026-11-03,
// studying at the desk). The stats and their rank names are the save data's (stats::read).
// Its OK (state 6's handler, exe+0x13a025b): the decide or cancel button closes it only once the panel's own state
// (UCmpHeroHumanStatusDraw +0x38) is 9; it is 5 while the panel rises (about a second; OK did nothing then,
// 2026-11-16). With its flag +0x40B8 clear only cancel closes it (never seen: 1 each time).
#include "screens/screen.h"
#include "screens/util.h"
#include "screens/next_cue.h"
#include "core/strings.h"
#include "speech.h"
#include "stats.h"
#include <format>

namespace p3a::screens {
using namespace ue;

class StatsUpScreen : public Screen {
  Finder draw_{"UIGetHeroParameterDraw"};
  // The panel as a line: each social stat with its level and rank name. `rise` names the stat that went up first (the
  // last rise no panel has shown).
  std::string line(bool rise) {
    stats::Stats s;
    if (!stats::read(s)) return {};
    std::string out = strings::kStatsUp.c_str();
    if (int up = rise ? stats::last_up() : -1; up >= 0) out += " " + strings::fmt(strings::kStatUpFmt, strings::kSocialStats[up].c_str()) + ".";
    // The panel's gauges: how far each stat is from its next rank, in the game's points.
    for (int i = 0; i < 3; ++i) {
      out += std::format(" {} {} {}", strings::kSocialStats[i], s.level[i], stats::rank_name(s, i));
      if (s.next[i] > 0) out += ", " + strings::fmt(strings::kToNextRankFmt, strings::count(s.next[i], strings::kPoint, strings::kPoints));
      out += ".";
    }
    return out;
  }
 public:
  const char* id() const override { return "stats_up"; }
  int priority() const override { return 29; }   // a notice over whatever menu gave it, as get_item
  bool active() override {
    uint8_t* d = (uint8_t*)draw_.get();
    if (!d || *(int32_t*)(d + 0x294) != 6 || !*(UObject**)(d + 0xD00)) return false;
    stats::Stats s;
    return stats::read(s);
  }
  // The stat that went up was said as its points changed, 2.4 s before this screen (2026-10-29): the review line
  // names it, the entry does not again. The key that closes the panel is the screen's key help (F1), not part of
  // either line.
  // The panel is made for one showing: the same one entered again (back from a window over it) was said already.
  // Two rises in a row (Charm, then Courage) show the panel twice, the same actor each time: once it has closed
  // (left while no longer up), the next showing is a new one (the second went unsaid, 2026-11-14).
  // Its OK: the cue once the panel takes it, the panel's own state 9 (above). State 6 comes as it opens, before its
  // rise animation lets OK through, and code asking for the button from the first frame (the UI input bridge, the
  // panel's own handler) is no sign ("Next" said before OK did anything, 2026-11-14 and 2026-11-16).
  WeakObj spoken_;
  NextCue next_{"stats_up"};
  void enter() override {
    screens::set_keys(strings::kSpaceContinues);
    WeakObj d = WeakObj::of(draw_.get());
    if (d == spoken_) return;
    spoken_ = d;
    speech::speak(line(false), true);
    next_.arm();
  }
  bool takes_ok() {
    uint8_t* d = (uint8_t*)draw_.get();
    uint8_t* panel = d ? *(uint8_t**)(d + 0xD00) : nullptr;
    return panel && *(int32_t*)(panel + 0x38) == 9 && *(uint8_t*)(panel + 0x40B8);
  }
  void tick() override { next_.tick(takes_ok(), true); }
  void leave() override {
    if (active()) return;   // covered, not closed
    next_.disarm();
    spoken_ = {};
    stats::up_shown();   // its rise has been shown
  }
  std::string describe() override { return line(true); }
};

std::unique_ptr<Screen> make_stats_up() { return std::make_unique<StatsUpScreen>(); }
}  // namespace p3a::screens
