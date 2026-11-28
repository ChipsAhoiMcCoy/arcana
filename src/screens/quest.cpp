// Elizabeth's requests and the missing persons as a bespoke menu (menu.h), modelled from the game's own objects (the
// offsets are this build's, measured 2026-10-30): the camp's Quest submenu, the request counter in the Velvet Room
// and the Missing Persons board show the same two lists. Every list uses the generic ListCursor (util.h): index =
// row + top.
//
//   UCmpQuest +0x3C open, +0x1C4 tab (0 requests, 1 missing persons).
//   UIRequest: +0x34 state (8 list, 9 info), +0xD0 TArray<{u16 quest, u8 status, u8 new, ...}> (0xC each),
//   ListCursor +0xE0, +0x300 the highlighted request, +0x309 0 at the Velvet Room's counter, +0x5F8 the prompt up
//   (-1 none), +0xD60 / +0xD61 the list leaving.
//   UIMissingPerson: +0x34 state (6 list, 7 detail), +0x40 / +0x44 two floats the bar's slide is given, +0x4C /
//   +0x4D (no move while either is set), +0x531 1 from the camp (FUN_14148f9e0) and 0 from a board outside it
//   (FUN_14147fc20, 2026-11-24), +0x538 a pointer to its ListCursor,
//   +0x548 the bar, +0x728 the highlighted case, +0xB48 TArray<{u16, u16 case}> (count also at +0xB50).
//   DisappearDataAsset +0x30: a TMap, elements of 0x30 (key at +0, the case's flags at +8).
//   VelvetRoomQuestDataAsset (the game's common resource 0x12, FUN_1414fcee0): Data +0x30 / count +0x38, rows of
//   0x48 indexed by the list's quest id: +0x12 EndMonth, +0x13 EndDay (the Deadline column, 0 none), +0x20 Rank (the
//   Info view's difficulty butterflies, of 5), +0x24 Request {u8 type (0 event, 1 item, 2 Persona, 3 counter), +0x28
//   u32 ID, +0x2C u32 Value}, +0x34 Reward {u16 item, u16 count, u32 money}, +0x44 QuestIndex (the No. column).
//   The Info view (UIRequest state 9) shows the request at +0x300: its task and counter, reward, BMD_Quest page 0
//   (the details, laid out with the item's name) and the difficulty.
#include "screens/menu.h"
#include "screens/util.h"
#include "screens/camp.h"
#include "bmdfile.h"
#include "core/bmd.h"
#include "core/calendar_text.h"
#include "core/speech_text.h"
#include "core/strings.h"
#include "core/text_clean.h"
#include "items.h"
#include "msg.h"
#include "party.h"
#include <algorithm>
#include <format>
#include <map>
#include <optional>

namespace p3a::screens {
using namespace ue;

class CampQuest : public MenuScreen {
 public:
  CampQuest() {
    // A request's move (FUN_1415a9370 state 8): the sound, the NEW mark of the request left cleared, the highlighted
    // request (+0x300), the bar (FUN_141585740) and Elizabeth's reaction to its status (FUN_141587280). Not while
    // a prompt is up (+0x5F8) or the list is leaving (+0xD60 / +0xD61).
    reqs_.ready = [this] { uint8_t* r = req(); return r && !r[0xD61] && r[0xD60] != 1 && i32(r, 0x5F8) == -1; };
    reqs_.set = [this](int i) {
      uint8_t* r = req();
      auto* list = r ? arr<uint8_t>(r, 0xD0) : nullptr;
      ListCursor lc(r ? r + 0xE0 : nullptr);
      int old = lc.index();
      if (!list || i >= list->num || old < 0 || old >= list->num || !lc.set(i)) return false;
      cursor_sound();
      fn<void (*)(uint16_t, char)>(0x1505690)(*(uint16_t*)(list->data + old * 0xC), 0);
      list->data[old * 0xC + 3] = 0;
      *(int32_t*)(r + 0x300) = i;
      fn<void (*)(void*)>(0x1585740)(r);
      fn<void (*)(void*, char, char, char, char)>(0x1587280)(r, r[0x309], list->data[i * 0xC + 2], 1, 0);
      return true;
    };
    // A case's move (FUN_14149c750 state 6): the bar (FUN_141490460, two floats), the sound, the case left marked
    // seen, the highlighted case (+0x728).
    cases_.ready = [this] { uint8_t* r = missing(); return r && !r[0x4C] && !r[0x4D]; };
    cases_.set = [this](int i) {
      uint8_t* r = missing();
      ListCursor lc = cursor_at(r, 0x538);
      if (!r || !lc.set(i)) return false;
      int old = i32(r, 0x728), n = i32(r, 0xB50);
      fn<void (*)(void*, float, float)>(0x1490460)(r + 0x548, *(float*)(r + 0x40), row_of(lc.p) * 60.f + *(float*)(r + 0x44));
      if (n != 0 && old != i) {
        cursor_sound();
        if (old >= 0 && old < n) {
          uint32_t f = *(uint16_t*)(*(uint8_t**)(r + 0xB48) + old * 4 + 2) + 0x20000E95u;
          void* g = game_work();
          if (!fn<bool (*)(void*, uint32_t)>(0x122a080)(g, f)) fn<void (*)(void*, uint32_t, int)>(0x1230410)(g, f, 1);
        }
      }
      *(int32_t*)(r + 0x728) = i;
      return true;
    };
  }
  void on_enter() override {
    screens::set_keys([this] {
      if (tab() == 0 && info()) return std::string(velvet() ? strings::kRequestInfoVelvetKeys() : strings::kRequestInfoKeys());
      return std::string(velvet() ? strings::kRequestKeys() : board() ? strings::kMissingBoardKeys()
                         : tab() == 1 ? strings::kMissingPersonsKeys() : strings::kCampRequestKeys());
    });
  }
 private:
  Finder menu_{"CmpQuest"}, req_{"UIRequest"}, missing_{"UIMissingPerson"}, velvet_{"UIVelvetRoomRequest"};
  Finder quests_data_{"DisappearDataAsset"};
  bool open() { UObject* q = camp_open() ? menu_.get() : nullptr; return q && ((uint8_t*)q)[0x3C]; }
  // Elizabeth's own counter in the Velvet Room shows the same list (UIRequest +0x309 = 0 there: accept and report).
  bool velvet() { return !open() && velvet_.get() != nullptr; }
  // The Missing Persons list on its own, outside the camp: a bulletin board's check opens it (Fountain Square's,
  // 2026-11-24). Outside the camp nothing else shows its list. Its +0x531 is 0 then, not 1: asking for 1 left the
  // board silent, with the field's checks dead under it until C closed it.
  bool board() { return !open() && missing(); }
  int tab() { if (board()) return 1; if (velvet()) return 0; UObject* q = menu_.get(); return q ? i32(q, 0x1C4) : 0; }
  uint8_t* req() { UObject* r = req_.get(); return r && i32(r, 0x34) == 8 ? (uint8_t*)r : nullptr; }
  // A request's info (F: state 9): the game's keys (up and down switch request, F or cancel back), the screen stays.
  uint8_t* info() { UObject* r = req_.get(); return r && i32(r, 0x34) == 9 ? (uint8_t*)r : nullptr; }
  uint8_t* missing() { UObject* r = missing_.get(); return r && i32(r, 0x34) == 6 ? (uint8_t*)r : nullptr; }
  Mirror& reqs_ = mirror("requests", [this] { uint8_t* r = req(); return r && tab() == 0 ? ListCursor(r + 0xE0).index() : -1; });
  Mirror& cases_ = mirror("cases", [this] { uint8_t* r = missing(); return r && tab() == 1 ? cursor_at(r, 0x538).index() : -1; });
  std::string quest_title(int id) {
    auto f = bmdfile::load("BMD_Quest");
    if (!f || !f->ok || id < 0 || id >= (int)f->dialogs.size()) return std::format("{} {}", strings::kNumber, id);
    auto& d = f->dialogs[id];
    if (d.speaker >= 0 && d.speaker < (int)f->speakers.size()) return core::clean_text(f->speakers[d.speaker]);
    return std::format("{} {}", strings::kNumber, id);
  }
  std::string quest_page(int id, int page, bool* gap = nullptr) {
    auto f = bmdfile::load("BMD_Quest");
    if (!f || !f->ok || id < 0 || id >= (int)f->dialogs.size() || page >= (int)f->dialogs[id].pages.size()) return {};
    auto& pg = f->dialogs[id].pages[page];
    // Table 4 functions are text the game fills in (an item's name): the file's text has a hole there.
    if (gap) { *gap = false; for (auto& fn : pg.functions) if (fn.table == 4) *gap = true; }
    return core::clean_text(core::bmd::plain(pg));
  }
  static uint8_t* quest_row(int id) {
    void* res = fn<void* (*)()>(0xfc85f0)();
    UObject* a = res ? fn<UObject* (*)(void*, uint8_t)>(0x15695e0)(res, 0x12) : nullptr;
    if (!a || !ue::is_a(a, "VelvetRoomQuestDataAsset") || id < 0 || id >= i32((uint8_t*)a, 0x38)) return nullptr;
    uint8_t* d = *(uint8_t**)((uint8_t*)a + 0x30);
    return d ? d + id * 0x48 : nullptr;
  }
  // A list row as the game draws it: the title, NEW, the status, the deadline.
  std::string row_label(const uint8_t* e) {
    int id = *(const uint16_t*)e, status = e[2];
    if (status == 5) return strings::kRequestLocked.c_str();
    std::string label = quest_title(id);
    if (e[3]) label += std::string(", ") + strings::kNew;
    if (status >= 0 && status < 5) label += std::string(", ") + strings::kRequestStatus[status];
    if (uint8_t* q = quest_row(id); q && q[0x12] && q[0x13])
      label += ", " + strings::fmt(strings::kRequestDeadlineFmt, core::date_text(q[0x12], q[0x13], -1, false, ""));
    return label;
  }
  // The Info view's counter ("120/200") as the game's clear check counts it (FUN_1414feb20): an item carried
  // (FUN_1411ef210) plus the ones party members 1..12 wear (FUN_140fca100 present, FUN_14130caf0 slots 0..4); a
  // counter (FUN_1412296e0). An event or a Persona has none (-1).
  static int progress(const uint8_t* q) {
    uint32_t id = *(const uint32_t*)(q + 0x28);
    if (q[0x24] == 3) return fn<int (*)(void*, uint32_t)>(0x12296e0)(game_work(), id);
    if (q[0x24] != 1) return -1;
    int n = fn<uint8_t (*)(uint16_t)>(0x11ef210)((uint16_t)id);
    for (uint32_t m = 1; m < 0xD; ++m) {
      if (!fn<bool (*)(uint32_t)>(0xfca100)(m)) continue;
      for (int s = 0; s < 5; ++s)
        if (fn<uint16_t (*)(uint16_t, int)>(0x130caf0)((uint16_t)m, s) == (uint16_t)id) ++n;
    }
    return n;
  }
  // Request Details: the page the game laid out from BMD_Quest for the Info view (dialog = the id, page 0: the details
  // alone, the item's name filled in; its text starts as the file's, so a page of another file once at that buffer's
  // address does not count). Until then the file's page when it has no hole, its task (page 1) cut from its end.
  // nullopt: the game's page is still to come.
  std::optional<std::string> details(int id) {
    bool gap = false;
    std::string file = quest_page(id, 0, &gap);
    std::string head = file.substr(0, std::min<size_t>(file.size(), 8));
    if (const void* buf = bmdfile::buffer("BMD_Quest"))
      for (auto& pg : msg::pages_of(buf))
        if (pg.dialog == id && pg.page == 0) {
          std::string t = core::clean_text(pg.text);
          if (!head.empty() && t.starts_with(head)) return t;
        }
    if (gap) return std::nullopt;
    std::string task = quest_page(id, 1);
    if (!task.empty() && file.size() > task.size() && file.ends_with(task)) {
      file.resize(file.size() - task.size());
      while (!file.empty() && file.back() == ' ') file.pop_back();
    }
    return file;
  }
  // The Info view's request, read in the order the game lays it out: the row, the task and its counter, the reward,
  // the details, the difficulty. Empty while its details page is still being built.
  std::string info_text(int& shown) {
    uint8_t* r = info();
    auto* list = r ? arr<uint8_t>(r, 0xD0) : nullptr;
    int i = r ? i32(r, 0x300) : -1;
    shown = i;
    if (!list || i < 0 || i >= list->num) return {};
    const uint8_t* e = list->data + i * 0xC;
    int id = *(const uint16_t*)e;
    std::string out = core::position(row_label(e), i + 1, list->num);
    if (e[2] == 5) return out;
    auto d = details(id);
    if (!d) return {};
    bool gap = false;
    std::string task = quest_page(id, 1, &gap);
    if (const void* buf = bmdfile::buffer("BMD_Quest"))
      for (auto& pg : msg::pages_of(buf))
        if (pg.dialog == id && pg.page == 1) {
          std::string t = core::clean_text(pg.text);
          if (t.starts_with(task.substr(0, std::min<size_t>(task.size(), 8)))) { task = t; gap = false; }
        }
    if (!gap && !task.empty()) out += ". " + task;
    if (uint8_t* q = quest_row(id)) {
      // the game's counter stops at the goal (203 chests opened shows 200/200)
      if (int p = progress(q); p >= 0) {
        int goal = (int)*(const uint32_t*)(q + 0x2C);
        out += ". " + strings::fmt(strings::kRequestProgressFmt, strings::of(std::min(p, goal), goal));
      }
      int item = *(const uint16_t*)(q + 0x34), count = *(const uint16_t*)(q + 0x36);
      uint32_t money = *(const uint32_t*)(q + 0x38);
      std::string reward;
      if (std::string n = item ? items::name_of(item) : std::string(); !n.empty()) reward = count > 1 ? strings::fmt(strings::kCountFmt, n, count) : n;
      if (money) reward += (reward.empty() ? "" : ", ") + strings::count(money, strings::kYen);
      if (!reward.empty()) out += ". " + strings::fmt(strings::kRequestRewardFmt, reward);
      if (!d->empty()) out += ". " + *d;
      if (q[0x20]) out += ". " + strings::fmt(strings::kRequestDifficultyFmt, strings::of(q[0x20], 5));
    } else if (!d->empty()) {
      out += ". " + *d;
    }
    return out;
  }
  // Built only when the shown request (+0x300) is not the one said: once said, nothing is read again until it changes;
  // while its details page is still to come (info_text empty) it is tried again on the next frame.
  int info_said_ = -1;
  void on_tick() override {
    uint8_t* r = tab() == 0 ? info() : nullptr;
    if (!r) { info_said_ = -1; return; }
    if (i32(r, 0x300) == info_said_) return;
    int shown = -1;
    std::string t = info_text(shown);
    if (!t.empty()) { info_said_ = shown; say(t, true); }
  }
 public:
  const char* id() const override { return "camp_quest"; }
  int priority() const override { return 21; }
  bool active() override { return (open() || velvet() || board()) && ((tab() == 0 && (req() || info())) || (tab() == 1 && missing())); }
  // A request's prompt (accept? / the report) is a message window over the list: the keys are its.
  bool holds_keys() override { if (tab() == 0 && info()) return false; uint8_t* r = req(); return tab() == 1 || !r || *(int32_t*)(r + 0x5F8) == -1; }
  // A case's profile is read with each row: the game's details key (F / X) does nothing there. A request's info (F)
  // stays the game's: Elizabeth's text names the item only on the page the game builds for that view.
  bool blocks_status() override { return tab() == 1; }
  std::string title() override { return tab() == 1 ? strings::kMissingPersons.c_str() : strings::kRequests.c_str(); }
  void build(ui::GraphBuilder& b) override {
    if (tab() == 0) {
      uint8_t* r = req() ? req() : info();   // the list stays built under the info view
      auto* list = r ? arr<uint8_t>(r, 0xD0) : nullptr;
      b.begin_stop("requests");
      for (int i = 0; list && i < list->num; ++i) {
        uint8_t* e = list->data + i * 0xC;
        int id = *(uint16_t*)e, status = e[2];
        std::string label = row_label(e);
        // Its details are the file's task only when that text is whole: with a hole for an item's name ("Show
        // Elizabeth an.") the review key read it after the filled one below (2026-11-24).
        auto v = game_item(reqs_, i, [label] { return label; }, [this, id, status] {
          bool gap = false;
          std::string t = status == 5 ? std::string() : quest_page(id, 1, &gap);
          return gap ? std::string() : t;
        });
        // The task after the title, as the game shows it beside the list. The message file's text leaves out what the
        // game fills in (an item's name: "Show Elizabeth a ."); the page the game laid out from BMD_Quest for the
        // request (dialog = its id, page 1) has it once the game's cursor has been there. Its text starts as the
        // file's: a page of another file once at that buffer's address does not.
        if (status != 5) {
          bool gap = false;
          std::string task = quest_page(id, 1, &gap);
          describe_with(v, [id, task, gap] {
            std::string head = task.substr(0, std::min<size_t>(task.size(), 8));
            if (const void* buf = bmdfile::buffer("BMD_Quest"))
              for (auto& pg : msg::pages_of(buf))
                if (pg.dialog == id && pg.page == 1) {
                  std::string t = core::clean_text(pg.text);
                  if (!head.empty() && t.starts_with(head)) return t;
                }
            return gap ? std::string() : task;
          });
        }
        b.add_item(slot("requests", i), v);
      }
      if (int c = reqs_.cursor(); c >= 0) b.set_start(slot("requests", c));
      return;
    }
    uint8_t* r = missing();
    auto* list = r ? arr<uint32_t>(r, 0xB48) : nullptr;
    auto f = bmdfile::load("BMD_DisappearHelp");
    // Each case's state from DisappearDataAsset (a TMap: elements of 0x30, key at +0, flags Active, Success,
    // Failed, Npc, InfoOn, Award at +8), and its name only once InfoOn is set.
    std::map<int, const int32_t*> flags;
    if (UObject* d = quests_data_.get()) {
      auto* map = (TArray<uint8_t>*)((uint8_t*)d + 0x30);
      for (int i = 0; map->data && i < map->num && i < 200; ++i) flags[*(uint16_t*)(map->data + i * 0x30)] = (int32_t*)(map->data + i * 0x30 + 8);
    }
    b.begin_stop("cases");
    for (int i = 0; list && i < list->num; ++i) {
      int no = (list->data[i] >> 16) & 0xFFFF;
      std::string name = strings::kUnknown.c_str(), profile, status;
      const int32_t* fl = flags.count(no) ? flags[no] : nullptr;
      if (fl) status = party::flag(fl[1]) ? strings::kMissingFound : party::flag(fl[2]) ? strings::kMissingDiscontinued : strings::kMissingSearching;
      if ((!fl || party::flag(fl[4])) && f && f->ok && no < (int)f->dialogs.size()) {
        auto& dlg = f->dialogs[no];
        if (dlg.speaker >= 0 && dlg.speaker < (int)f->speakers.size()) name = core::clean_text(f->speakers[dlg.speaker]);
        // One fact a line (age, sex, job, then how they went missing): each line its own sentence.
        if (!dlg.pages.empty()) profile = core::clean_lines(dlg.pages[0].text);
      }
      std::string label = std::format("{} {}, {}", strings::kNumber, no, name);
      if (!status.empty()) label += ", " + status;
      auto v = game_item(cases_, i, [label] { return label; }, [profile] { return profile; });
      describe_with(v, [profile] { return profile; });
      b.add_item(slot("cases", i), v);
    }
    if (int c = cases_.cursor(); c >= 0) b.set_start(slot("cases", c));
  }
};

std::unique_ptr<Screen> make_camp_quest() { return std::make_unique<CampQuest>(); }
}  // namespace p3a::screens
