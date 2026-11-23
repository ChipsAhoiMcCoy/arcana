// The game's online features (config "Network Functions", flag 0x40000068). Neither opens by itself: the game's View
// action (input action 0x33; N on the keyboard) shows it, and N or C closes it. Both are menus of the mod's: a row per
// answer, or per kind of activity with the activities under it.
//  - Voice Answer: during a class question's answers (Event_Extr_330_020/030: NET_START_ANSWER sets
//    AAtlEvtEventManager +0x320, the answer list reaching its input state sets +0x321), how other players answered.
//    AUIVoiceAnswer.pVoiceAnswerDrawActor (+0x340) -> AUIVoiceAnswerDraw: IsGetData (+0x2C8) once the download came,
//    +0x9B8 once the figures were copied in (frames later), +0x30C int32[4] each answer's percentage (count * 100 /
//    total, FUN_1414b5360). The answers are the choice list's own (the draw keeps the same USelItem at +0x2E8), read
//    here as msg reads them. The game draws them as "Everyone's Response" with the date.
//  - Voice Action: in town (not on a Tartarus floor, where the same button is the navigator's), what other players did
//    today. UFldManagerSubsystem.mVoiceActionDisp_ (the AUIVoiceAction) while it is up; its pVoiceActionDrawActor
//    (AUIVoiceActionDraw): IsGetData (+0x307), u16 percentages at +0x2BA / +0x2BC / +0x2BE (daily life, Social Links,
//    Tartarus; they sum to 100), and each kind's sticky notes, TArray<FBmdPage*> at +0x2C0 / +0x2D0 / +0x2E0
//    (BMD_ActionRecord pages, up to five drawn). FUN_1414b4f30 builds them, FUN_1414b8e20 copies them into the draw,
//    but only once the action's opening has gone past its state 4: IsGetData is set when the download answers
//    (FUN_1414ba* state code), frames before the copy, and not at all when the game had today's data already (then
//    IsStartGetData, +0x306): the figures are there when the percentages sum to more than 0 (a new draw each open).
//  - A download that failed sets the action's +0x41A (its +0x288 part's +0x192), or the answer's +0x36D (+0x288 part's
//    +0xE5), with IsGetData, and nothing is ever copied.
#include "screens/menu.h"
#include "screens/util.h"
#include "core/calendar_text.h"
#include "core/strings.h"
#include "calendar.h"
#include "msg.h"
#include "seh.h"
#include <format>

namespace p3a::screens {
using namespace ue;

namespace {
std::string percent_line(const std::string& what, int pct) {
  return std::vformat(strings::kNetPercent.c_str(), std::make_format_args(what, pct));
}

// One of the two screens. The figures are read once, when the game has copied them into its draw (they do not change
// while it is up; each opening is a new draw). Until then the menu has no rows: the title is said as it opens, and the
// first row once the figures are in (at once when the game had them already).
class NetMenu : public MenuScreen {
 protected:
  struct Row { std::string id, text, region; };
  std::vector<Row> rows_;
  int start_ = 0;   // the row the menu opens on
  enum State { Waiting, Ready, Failed };

  virtual UObject* draw() = 0;
  virtual bool has_data(UObject* d) = 0;
  virtual bool failed(UObject* d) = 0;
  virtual void read(UObject* d) = 0;   // fills rows_ (and start_)
  virtual const char* base_title() const = 0;
  virtual strings::Hint keys() const = 0;

 private:
  const void* read_from_ = nullptr;   // compared, never dereferenced: the draw the rows were read from
  State state_ = Waiting;
  bool shown_ = false;                // the menu has rows (or the failure) the opening or a focus has said
  State refresh() {
    UObject* d = draw();
    if (!d) return Waiting;
    if (d != read_from_) { rows_.clear(); start_ = 0; read_from_ = nullptr; }
    if (!read_from_ && has_data(d)) { read(d); read_from_ = d; }
    if (read_from_ && !rows_.empty()) return Ready;
    return failed(d) ? Failed : Waiting;
  }

 public:
  bool active() override { return draw() != nullptr; }
  // Each press of N is a new showing (over the same choice list, which stays up between them).
  bool title_every_entry() override { return true; }
  std::string title() override {
    calendar::Now n = calendar::now();
    std::string date = n.valid ? core::date_text(n.month, n.day, n.weekday, false, {}) : std::string();
    return date.empty() ? std::string(base_title()) : std::string(base_title()) + ", " + date;
  }
  void on_enter() override {
    screens::set_keys(keys());
    read_from_ = nullptr;
    rows_.clear();
    state_ = refresh();
    shown_ = state_ != Waiting;
  }
  void on_tick() override {
    state_ = refresh();
    if (state_ == Waiting || shown_) return;
    shown_ = true;
    // Queued after the title, which may still be speaking.
    if (state_ == Ready) focus(ui::ControlId::structural(rows_[std::min<size_t>(start_, rows_.size() - 1)].id), false);
    else focus(ui::ControlId::structural("net.failed"), false);
  }
  void build(ui::GraphBuilder& b) override {
    b.begin_stop("net");
    if (state_ == Failed) {
      b.add_item(ui::ControlId::structural("net.failed"), item([] { return std::string(strings::kNetFailed); }));
      return;
    }
    std::string region;
    for (auto& r : rows_) {
      if (!r.region.empty() && r.region != region) { region = r.region; b.set_region(region); }
      std::string text = r.text;
      b.add_item(ui::ControlId::structural(r.id), item([text] { return text; }));
    }
    if (!rows_.empty()) b.set_start(ui::ControlId::structural(rows_[std::min<size_t>(start_, rows_.size() - 1)].id));
  }
  std::string describe() override {
    if (state_ == Waiting) return title() + ". " + strings::kNetWaiting;
    return MenuScreen::describe();
  }
};

class NetAnswerScreen : public NetMenu {
  Finder answer_{"UIVoiceAnswer"};
 protected:
  UObject* draw() override {
    UObject* a = answer_.get();
    if (!a || !is_live(a)) return nullptr;
    UObject* d = get<UObject*>(a, "pVoiceAnswerDrawActor");
    return d && is_live(d) ? d : nullptr;
  }
  // The copy (FUN_1414b8fd0, past the answer's state 4) sets +0x9B8 in the same call that writes the percentages.
  // IsGetData is no sign: it comes frames earlier with a download, and never when the game had the data already
  // (it sets IsStartGetData, +0x2C7, then).
  bool has_data(UObject* d) override {
    bool copied = false;
    guarded([&] { copied = *((uint8_t*)d + 0x9B8) != 0; });
    return copied;
  }
  bool failed(UObject* d) override {
    UObject* a = answer_.get();
    bool err = false;
    if (a && is_live(a)) guarded([&] { err = *((uint8_t*)a + 0x36D) != 0; });
    return err && get_bool(d, "IsGetData");
  }
  // A row per answer, opening on the one the player's cursor is on.
  void read(UObject* d) override {
    int pct[4] = {};
    if (!guarded([&] { for (int i = 0; i < 4; ++i) pct[i] = *(int32_t*)((uint8_t*)d + 0x30C + 4 * i); })) return;
    msg::Current c = msg::current();
    size_t n = c.choices.empty() ? 4 : std::min<size_t>(c.choices.size(), 4);
    for (size_t i = 0; i < n; ++i) {
      std::string what = i < c.choices.size() ? c.choices[i] : std::to_string(i + 1);
      while (!what.empty() && (what.back() == '.' || what.back() == ' ')) what.pop_back();   // "Boneyards." as a row
      rows_.push_back({std::format("net.a{}", i), percent_line(what, pct[i]), {}});
    }
    start_ = c.choice >= 0 && c.choice < (int)n ? c.choice : 0;
  }
  const char* base_title() const override { return strings::kNetAnswerTitle; }
  strings::Hint keys() const override { return strings::kNetAnswerKeys; }
 public:
  const char* id() const override { return "net_answer"; }
  int priority() const override { return 38; }   // over the class question's choice list (35), under the log (40)
  bool over_messages() const override { return true; }
};

class NetActionScreen : public NetMenu {
  Finder fields_{"FldManagerSubsystem"};
  UObject* action() {
    UObject* f = fields_.get();
    UObject* a = f ? get<UObject*>(f, "mVoiceActionDisp_") : nullptr;
    return a && is_live(a) ? a : nullptr;
  }
 protected:
  UObject* draw() override {
    UObject* a = action();
    UObject* d = a ? get<UObject*>(a, "pVoiceActionDrawActor") : nullptr;
    return d && is_live(d) ? d : nullptr;
  }
  bool has_data(UObject* d) override {
    int sum = 0;
    guarded([&] { for (int k = 0; k < 3; ++k) sum += *(uint16_t*)((uint8_t*)d + 0x2BA + 2 * k); });
    return sum > 0;
  }
  bool failed(UObject* d) override {
    UObject* a = action();
    bool err = false;
    if (a) guarded([&] { err = *((uint8_t*)a + 0x41A) != 0; });
    return err && get_bool(d, "IsGetData");
  }
  // Each kind of activity is a section: its share, then the activities the game notes for it (Tab jumps the kinds).
  void read(UObject* d) override {
    for (int k = 0; k < 3; ++k) {
      int pct = 0;
      std::vector<void*> pages;
      guarded([&] {
        pct = *(uint16_t*)((uint8_t*)d + 0x2BA + 2 * k);
        auto* notes = (TArray<void*>*)((uint8_t*)d + 0x2C0 + 0x10 * k);
        for (int i = 0; notes->data && i < notes->num && i < 5; ++i) pages.push_back(notes->data[i]);
      });
      std::string region = std::format("net.k{}", k);
      rows_.push_back({region, percent_line(strings::kNetActionKinds[k].c_str(), pct), region});
      for (size_t i = 0; i < pages.size(); ++i)
        if (std::string t = msg::page_string(pages[i]); !t.empty()) rows_.push_back({std::format("{}.{}", region, i), t, region});
    }
  }
  const char* base_title() const override { return strings::kNetActionTitle; }
  strings::Hint keys() const override { return strings::kNetActionKeys; }
 public:
  const char* id() const override { return "net_action"; }
  int priority() const override { return 30; }
};
}  // namespace

std::unique_ptr<Screen> make_net_answer() { return std::make_unique<NetAnswerScreen>(); }
std::unique_ptr<Screen> make_net_action() { return std::make_unique<NetActionScreen>(); }

// The class question's answers offer the other players' answers (AAtlEvtEventManager +0x320 the event asked for it,
// +0x321 the answer list was handed over), with Network Functions on.
bool net_answer_offered() {
  static Finder manager{"AtlEvtEventManager"};
  UObject* m = manager.get();
  if (!m) return false;
  bool on = false;
  guarded([&] { on = *((uint8_t*)m + 0x320) && *((uint8_t*)m + 0x321); });
  return on;
}
}  // namespace p3a::screens
