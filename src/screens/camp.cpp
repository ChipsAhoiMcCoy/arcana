// The camp menu (Tab in the field). Open while the innermost pause is Camp (pause_top); the root list's cursor is
// UCmpRoot +0x3c (0 Skill .. 8 System, measured 2026-10-27). Labels and help lines are sprites: the mod's wording
// for the labels, the help lines as the game shows them (strings::kCampHelp).
#include "screens/menu.h"
#include "screens/util.h"
#include "screens/camp.h"
#include "core/strings.h"
#include "hooks.h"
#include "log.h"
#include "party.h"

namespace p3a::screens {
using namespace ue;

// The innermost pause: AppPauseManagerSubsystem.PauseFlow is a stack of EAppPauseType ({None, TownMap} while the
// town map is up; IsPause(type) answers true for every type once anything pauses, measured 2026-10-27).
static UObject* pause_manager() {
  static const int id = watch::want("AppPauseManagerSubsystem");
  return watch::get(id);
}
static TArray<uint8_t>* pause_flow(UObject* m) {
  auto* flow = m ? field<TArray<uint8_t>>(m, "PauseFlow") : nullptr;
  return flow && flow->num > 0 && flow->data ? flow : nullptr;
}

// The mod's own pause (the mod menu, hold_pause): the stack's length once the camp entry it pushed was on it, or 0.
// Pause(Camp) runs what the camp's opening runs (FUN_1411b76f0 -> FUN_1410a8ad0(1)): every pauseable whose flags meet
// 0x6e (characters, the field's local actors, the system UI, field sounds, crowds) stops. It pushes only when the top
// is another type, and UnPause (FUN_1410af740) takes every entry of the top's type off: so the mod pushes only over no
// pause at all, and pops only while its entry is the top (a pause the game put over it is waited out).
static int g_held_at = 0;
static bool g_release = false;

int pause_top() {
  auto* flow = pause_flow(pause_manager());
  if (!flow) return 0;
  // The mod's own entry is not a menu of the game's: the one under it is the innermost pause.
  if (g_held_at && flow->num == g_held_at && flow->num >= 2) return flow->data[flow->num - 2];
  return flow->data[flow->num - 1];
}
bool camp_open() { return pause_top() == 1; }   // EAppPauseType::Camp

static void release_pause(const char* why) {
  UObject* m = pause_manager();
  auto* flow = pause_flow(m);
  if (!flow) { g_held_at = 0; g_release = false; return; }   // the subsystem is gone (a load): its stack with it
  int i = g_held_at - 1;
  if (i >= flow->num || flow->data[i] != 1) {   // an UnPause of the game's took it off already
    log::writef("pause: the mod's hold was taken off by the game ({})", why);
    g_held_at = 0; g_release = false; return;
  }
  if (flow->num != g_held_at) { g_release = true; return; }   // a pause of the game's over it: popped once it ends
  call(m, "UnPause");
  log::writef("pause: released ({})", why);
  g_held_at = 0; g_release = false;
}

void hold_pause(bool on) {
  if (!on) { if (g_held_at) release_pause("menu closed"); return; }
  if (g_held_at) { g_release = false; return; }
  UObject* m = pause_manager();
  auto* flow = pause_flow(m);
  if (!flow || flow->data[flow->num - 1] != 0) return;   // only over no pause: a menu of the game's already holds one
  Params p(find_function(class_of(m), "Pause"));
  if (!p.fn || !p.set<uint8_t>("InPauseType", 1)) return;
  call(m, p);
  flow = pause_flow(m);
  if (flow && flow->data[flow->num - 1] == 1) {
    g_held_at = flow->num;
    log::writef("pause: held (stack {})", flow->num);
  }
}

void pause_tick() {
  if (g_release) release_pause("after the game's pause");
}

// Whether one of the root's submenus is open. Each submenu is one object for the whole session (all ten exist from
// boot, measured 2026-11-01) whose state is 0 while it is closed: Skill +0x3C, Item / Equip / Persona +0x38, Stats
// +0x44, System +0x54 (ints), Quest +0x3C, Social Link +0x58, Calendar +0x3C (byte flags).
bool camp_submenu_open() {
  static Finder skill{"CmpSkill"}, item{"CmpItem"}, equip{"CmpEquip"}, persona{"CmpPersona"}, status{"CmpStatus"},
      quest{"CmpQuest"}, commu{"CmpCommu"}, calendar{"CmpCalendar"}, sys{"CmpSystem"};
  auto i32 = [](Finder& f, int off) { UObject* o = f.get(); return o ? *(int32_t*)((uint8_t*)o + off) : 0; };
  auto u8 = [](Finder& f, int off) { UObject* o = f.get(); return o ? ((uint8_t*)o)[off] : 0; };
  return i32(skill, 0x3C) || i32(item, 0x38) || i32(equip, 0x38) || i32(persona, 0x38) || i32(status, 0x44) ||
         i32(sys, 0x54) || u8(quest, 0x3C) || u8(commu, 0x58) || u8(calendar, 0x3C);
}

class CampScreen : public MenuScreen {
  Finder root_{"CmpRoot"};
  static constexpr int kCount = 9;
  // The root's timer (+0x40) as last seen, and whether it moved in the last frame: the root adds the frame's time to it
  // on every frame it runs (FUN_141328720), and it reads input only then. A cancel closes the camp through the camp
  // manager, which stops running the root for the close (about 0.4 s) while it stays in state 3 (2026-11-16).
  float timer_seen_ = -1;
  uint64_t timer_frame_ = 0;
  bool timer_moving_ = false;
  bool root_running(const uint8_t* r) {
    float t = *(const float*)(r + 0x40);
    if (uint64_t f = hooks::frame(); f != timer_frame_) {
      timer_moving_ = t != timer_seen_;
      timer_seen_ = t;
      timer_frame_ = f;
    }
    return timer_moving_;
  }
  Mirror& list_ = mirror("camp", [this] {
    UObject* r = root_.get();
    int c = r ? *(int32_t*)((uint8_t*)r + 0x3c) : -1;
    return c >= 0 && c < kCount ? c : -1;
  });
 public:
  // The root's ListCursor is +0x48 (+0x3c is its row, copied every frame). The draw reads the cursor each frame; the
  // move (FUN_141328720) adds the row copy, the help line's fade (draw +0x88, +0x7BC) and the sound.
  CampScreen() {
    // The game takes input in states 1-3 (this screen is up in 2-4, active()); the list counts as ready, for moves and
    // the confirm alike, once the root's timer (+0x40) has run a third of a second, while the root runs (not closing).
    list_.ready = [this] {
      auto* r = (uint8_t*)root_.get();
      int st = r ? *(int32_t*)(r + 0x38) : 0;
      return st >= 1 && st <= 3 && *(float*)(r + 0x40) >= 1.f / 3 && root_running(r);
    };
    list_.set = [this](int i) {
      auto* r = (uint8_t*)root_.get();
      int st = r ? *(int32_t*)(r + 0x38) : 0;
      if (st < 1 || st > 3 || !ListCursor(r + 0x48).set(i)) return false;
      *(int32_t*)(r + 0x3c) = *(int32_t*)(r + 0x48 + 0x24);
      if (uint8_t* d = *(uint8_t**)(r + 0x88)) *(uint64_t*)(d + 0x7BC) = 0;
      cursor_sound();
      return true;
    };
  }
  const char* id() const override { return "camp"; }
  int priority() const override { return 15; }
  // The save key (H) opens the save list under a camp pause too, without the root menu: UCmpRoot +0x38 is the
  // root's state, 0 unless the menu itself is open (measured 2026-10-27).
  // It is 3 while idle on the list, and stays 3 while a submenu is open: state 4 asks the camp manager for the
  // submenu and goes straight back to 3 (FUN_141328720; 5-8 closing). So the state alone does not say the root is in
  // front: no submenu may be open either (camp_submenu_open), else it read "Equip, 3 of 9" again whenever a submenu
  // passed between its own states (2026-11-01).
  // State 2 is the opening slide, in which the game already takes moves (FUN_141328720 falls through to the list's
  // input; only its confirm waits for the timer): the screen is up from it. The mod's own moves and confirm wait for
  // the timer (list_.ready).
  bool active() override {
    UObject* r = camp_open() ? root_.get() : nullptr;
    int st = r ? *(int32_t*)((uint8_t*)r + 0x38) : 0;
    // 4 for a frame as a confirmed entry opens its submenu (2026-11-03): still the camp, not a gap that read its title
    // again when it came back.
    if (!(st == 2 || st == 3 || st == 4) || camp_submenu_open()) return false;
    // System's Return to Title, once confirmed, fades the screen out, waits for the fade (FUN_14135b890 state 0xF:
    // FUN_141090af0, the fade at its end) and only then closes itself and the camp: the root is on its list for a few
    // more frames behind the black screen, and read "Menu, System, 9 of 9" on the way to the title (2026-11-10).
    return !faded_out();
  }
  std::string title() override { return strings::kCamp.c_str(); }
  void on_enter() override { screens::set_keys(strings::kCampKeys); }
  // Every frame, so the timer is compared with the frame before (ready is asked only now and then).
  void on_tick() override { if (auto* r = (uint8_t*)root_.get()) root_running(r); }
  void build(ui::GraphBuilder& b) override {
    b.begin_stop("camp");
    // An entry the story has not opened yet is still selectable (the game buzzes): its lock flags, in list order
    // (exe+0x53b8428).
    static constexpr int kLock[kCount] = {0x40000080, 0x40000081, 0x40000082, 0x40000083, 0x40000084, 0x40000086, 0x40000085, 0x40000087, 0x40000088};
    for (int i = 0; i < kCount; ++i) {
      std::string label = strings::kCampItems[i].c_str(), help = strings::kCampHelp[i].c_str();
      if (party::flag(kLock[i])) label += std::string(", ") + strings::kUnavailable;
      auto v = game_item(list_, i, [label] { return label; }, [help] { return help; });
      buffer_with(v, [help] { return help; });   // "View or use items": said on every opening and move before
      b.add_item(slot("camp", i), v);
    }
    if (int c = list_.cursor(); c >= 0) b.set_start(slot("camp", c));
  }
};

std::unique_ptr<Screen> make_camp() { return std::make_unique<CampScreen>(); }
}  // namespace p3a::screens
