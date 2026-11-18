// The log (B in the field): the game's record of recent dialogue, thoughts and answers, newest at the bottom.
// BP_UIBackLogDraw_C lives only while it is open; native layout (measured 2026-10-28): AUIBackLog +0x320 the
// ListCursor (0 = oldest .. count-1 = newest, where it opens; the draw's +0x5DC is a copy that follows it late),
// +0x324 the number of entries. Its text storage is unmapped, so each entry is read from the mod's own record of the
// session (msg::history), counted from the newest; entries older than this session are said to be so.
#include "screens/menu.h"
#include "screens/util.h"
#include "core/log_index.h"
#include "core/speech_text.h"
#include "core/strings.h"
#include "log.h"
#include "msg.h"
#include "seh.h"
#include "ue/scan.h"
#include <map>

namespace p3a::screens {
using namespace ue;

// A bespoke menu: the entries oldest first, as the game lists them. The game's cursor is AUIBackLog's ListCursor
// (+0x320, its count +0x324); a write is followed by exe+0x12a3a80(log), the rest of its move (the draw's index
// +0x55C, which it sets to row + top, the voice replay hint, the sound). The list does not wrap. Opened from the field the log holds a pause
// (+0x2F0 set, its handle +0x2E0) and steps +0x2F4: 0-1 fading in, 2 open, 3-5 closing (FUN_1412ab830, which takes
// moves in every one but 5); it takes the mod's moves while open. +0x2F0 is set for the whole time it is open (moves
// waited on it and never reached the game, 2026-10-31).
class BacklogScreen : public MenuScreen {
  Finder draw_{"BP_UIBackLogDraw_C"};
  Finder log_{"UIBackLog"};
  int count() {
    UObject* l = log_.get();
    int n = l ? *(int32_t*)((uint8_t*)l + 0x324) : 0;
    return n > 0 && n < 10000 ? n : 0;
  }
  // A new log actor each time it opens. Its constructor (FUN_141292ad0) zeroes the count and leaves the step +0x2F4 at
  // 10.0f; the opening task (FUN_1412ab5f0) sets the ListCursor's count and its cursor on the newest entry in one call
  // and the step to 0. Read before that, the opening line was "An earlier line" (2026-10-29).
  bool settled() {
    UObject* l = log_.get();
    if (!draw_.get() || !l || !count()) return false;
    int step = *(int32_t*)((uint8_t*)l + 0x2F4);
    return step >= 0 && step <= 5;
  }
  // The game's cursor: the ListCursor itself (read from the draw's +0x5DC copy, an opening said "1 of 6" before the newest).
  int cursor() {
    UObject* l = log_.get();
    int n = count(), c = l ? ListCursor((uint8_t*)l + 0x320).index() : -1;
    return c >= 0 && c < n ? c : -1;
  }
  Mirror& list_ = mirror("log", [this] { return cursor(); });
  // The game adds a page to its log once it moves on, or (a voiced page) once its voice has ended: opened in a
  // conversation on a page still unheard, the page on screen is the mod's newest record but not yet the log's, and every
  // entry was read one off (2026-10-29). skip_ leaves it out. A voiced page heard to its end is in the game's log
  // already: skipping it read every entry one older than the game's (the player's report, 2026-10-29; the voice-end
  // rule is a guess from that report and the opposite measurement, which opened the log at once).
  int skip_ = 0;
  // The game's own log (read 2026-11-17; the count above went one off when the page on screen was already in it):
  // exe+0x12392f0() is the store, +0x08 its count (at most 30), +0x10 its oldest node; a node is {entry, next, prev}.
  // An entry (0x50, built by exe+0x12360d0) holds its speaker's BMD page at +0x38 and its line's at +0x40, the same
  // FCurrentBmdPage the message windows read (null speaker: a thought or narration; a choice's line is the answer).
  std::map<int, std::string> game_lines_;
  std::string game_line(int c) {
    if (auto it = game_lines_.find(c); it != game_lines_.end()) return it->second;
    void* who = nullptr; void* line = nullptr;
    guarded([&] {
      auto* store = (uint8_t*)((void* (*)())(scan::exe_base() + 0x12392f0))();
      if (!store || c >= *(int32_t*)(store + 8)) return;
      auto* node = *(uint8_t**)(store + 0x10);
      for (int i = 0; node && i < c; ++i) node = *(uint8_t**)(node + 8);
      auto* e = node ? *(uint8_t**)node : nullptr;
      if (!e) return;
      who = *(void**)(e + 0x38);
      line = *(void**)(e + 0x40);
    });
    std::string text = line ? msg::page_string(line) : std::string();
    if (text.empty()) return {};
    // The mod's record of the same line has its wording ("Thinking: ..."): the newest record that ends with it.
    std::string out;
    auto& h = msg::history();
    for (size_t i = h.size(); i-- > 0 && out.empty();) {
      const std::string& r = h[i];
      if (r == text || (r.size() > text.size() + 2 && r.ends_with(text) && r.compare(r.size() - text.size() - 2, 2, ": ") == 0)) out = r;
    }
    if (out.empty()) {
      std::string speaker = who ? msg::page_string(who) : std::string();
      if (speaker.rfind("DEV:", 0) == 0 || speaker.rfind("Internal", 0) == 0) speaker = strings::kThinking;
      out = core::spoken_line(speaker, text);
    }
    game_lines_[c] = out;
    return out;
  }
  std::string entry(int c, int n) {
    if (std::string g = game_line(c); !g.empty()) return g;
    log::writef("backlog: entry {} of {} not readable from the game's log, counted from the mod's record", c, n);
    auto& h = msg::history();
    int i = core::log_record_index(c, n, skip_, (int)h.size());
    return i < 0 ? std::string(strings::kLogEarlier) : h[(size_t)i];
  }
 public:
  BacklogScreen() {
    list_.ready = [this] { auto* l = (uint8_t*)log_.get(); return l && (!l[0x2F0] || *(int32_t*)(l + 0x2F4) == 2); };
    list_.set = [this](int i) {
      auto* l = (uint8_t*)log_.get();
      if (!l || !list_.ready() || !ListCursor(l + 0x320).set(i)) return false;
      ((void (*)(void*))(scan::exe_base() + 0x12a3a80))(l);
      return true;
    };
  }
  const char* id() const override { return "backlog"; }
  int priority() const override { return 40; }
  bool active() override { return draw_.get() != nullptr; }
  bool over_messages() const override { return true; }   // B in a conversation opens it over the window
  // Every opening says "Log" first (the user's call): it opens over a conversation, so title_due() (once per opening
  // of what is underneath) would leave it out the second time.
  std::string title() override { return strings::kLog; }
  bool title_every_entry() override { return true; }
  void on_enter() override {
    skip_ = 0;
    game_lines_.clear();
    screens::set_keys(strings::kLogKeys);
    msg::Current m = msg::current();
    auto& h = msg::history();
    bool on_screen = m.open && !h.empty() && h.back() == core::spoken_line(m.speaker, m.text);
    if (on_screen && !m.voice_done) skip_ = 1;
    log::writef("backlog: opened, {} records, page on screen {}{}, skip {}", h.size(), on_screen ? "is the newest" : "not recorded",
                m.voice_done ? " (voice ended)" : "", skip_);
  }
  // Back in the conversation: the line on screen again.
  void on_leave() override { if (msg::current().open) msg::repeat(); }
  void build(ui::GraphBuilder& b) override {
    if (!settled()) return;
    int n = count();
    b.begin_stop("log");
    for (int i = 0; i < n; ++i) b.add_item(slot("log", i), game_item(list_, i, [this, i, n] { return entry(i, n); }));
    if (int c = list_.cursor(); c >= 0) b.set_start(slot("log", c));
  }
};

std::unique_ptr<Screen> make_backlog() { return std::make_unique<BacklogScreen>(); }
}  // namespace p3a::screens
