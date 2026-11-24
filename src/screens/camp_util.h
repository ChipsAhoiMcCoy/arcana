#pragma once
// What the camp's submenus share: a party member's line, the party panel and key-help bar their moves drive, and the
// objects two screens of one submenu both read (Stats, Social Link).
#include "screens/camp.h"
#include "screens/util.h"
#include "party.h"
#include "social.h"
#include "core/strings.h"
#include <algorithm>
#include <string>
#include <vector>

namespace p3a::screens {
// `level` false: a member being picked for an item, a skill or gear, where the level tells nothing (the user's call,
// 2026-11-11).
// `mark` follows the name (party_marks).
inline std::string member_line(int id, bool level = true, const std::string& mark = {}) {
  party::Member m;
  if (party::member(id, m)) { m.name += mark; return party::line(m, level); }
  return party::name(id) + mark;
}
// A member list that holds both the active party and members outside it (the Stats roster, an item or gear picked for
// anyone): which each row is, ", in party", ", navigator" or ", reserve", in list order. A list of one kind marks
// nothing (the tester's report, 2026-11-20: the Stats list never said who was in the party). The navigator never
// fights (party::navigator).
template <class Id>
std::vector<std::string> party_marks(const ue::TArray<Id>* ids) {
  std::vector<std::string> out(ids && ids->data ? ids->num : 0);
  if (out.empty()) return out;
  std::vector<int> party = party::ids();
  auto in = [&](int id) { return std::find(party.begin(), party.end(), id) != party.end(); };
  int navi = party::navigator();
  bool any_in = false, any_out = false;
  for (int i = 0; i < ids->num; ++i) (in(ids->data[i]) ? any_in : any_out) = true;
  if (any_in && any_out)
    for (int i = 0; i < ids->num; ++i) {
      int id = ids->data[i];
      out[i] = std::string(", ") + (in(id) ? strings::kInParty : id == navi ? strings::kNavigator : strings::kReserve);
    }
  return out;
}
// The party panel's highlight on `row` and its slide (FUN_14130fed0 + FUN_141307760: Item, Skill, Equip members).
inline void panel_to(uint8_t* panel, int row, uint8_t* menu) {
  *(int32_t*)(panel + 8) = row;
  fn<void (*)(void*, int, void*, char)>(0x1307760)(panel, 0, *(void**)(menu + 0x30), 0);
}
// The key-help bar's layout: a message to UI type 6 (UIKeyHelpDraw) through the contact manager, as the game's moves send it.
inline void key_help(int layout) {
  void* ui = fn<void* (*)()>(0x134dce0)();
  if (!ui) return;
  alignas(16) uint8_t req[0x80] = {};
  fn<void (*)(void*)>(0xfe6f30)(req);
  *(int32_t*)(req + 0x24) = 10;
  fn<void (*)(void*, int, int, void*)>(0x1352d20)(ui, 6, layout, req);
  for (int off : {0x60, 0x50}) if (void* p = *(void**)(req + off)) fn<void (*)(void*)>(0x174d4b0)(p);
}

// The Stats submenu's UI, for the screens over it (the party list, a member's page): UCmpStatus +0x44 != 0 while it
// is open, its Actor_ +0x58 (UUICmpStatus), whose SceneFSM_ (+0x2B0) stacks the scenes.
struct CampStatsUi {
  Finder status_menu_{"CmpStatus"};
  uint8_t* ui() {
    ue::UObject* o = camp_open() ? status_menu_.get() : nullptr;
    return o && i32(o, 0x44) != 0 ? *(uint8_t**)((uint8_t*)o + 0x58) : nullptr;
  }
  // The scene on top of the UI's scene stack (UUISceneFSM.SceneStack_).
  ue::UObject* scene() {
    uint8_t* u = ui();
    ue::UObject* fsm = u ? *(ue::UObject**)(u + 0x2B0) : nullptr;
    auto* st = fsm ? ue::field<ue::TArray<ue::UObject*>>(fsm, "SceneStack_") : nullptr;
    return st && st->num > 0 ? st->data[st->num - 1] : nullptr;
  }
};

// The Social Link submenu's actor, for the screens over it (the list, a link's page): UCmpCommu +0x58 while it is
// open, its Actor_ +0xC50, whose details scene (+0x418) is up while its +0x54 is 1.
struct CampSocialUi {
  Finder commu_menu_{"CmpCommu"};
  uint8_t* actor() {
    ue::UObject* o = camp_open() ? commu_menu_.get() : nullptr;
    return o && ((uint8_t*)o)[0x58] ? *(uint8_t**)((uint8_t*)o + 0xC50) : nullptr;
  }
  // The details scene while it is up (a link's page), else null.
  uint8_t* details() {
    uint8_t* a = actor();
    uint8_t* d = a ? *(uint8_t**)(a + 0x418) : nullptr;
    return d && i32(d, 0x54) == 1 ? d : nullptr;
  }
};
// The record of the link of `arcana` among `all` (social::read), or one of rank 0 when it has none.
inline social::Link link_of(const std::vector<social::Link>& all, int arcana) {
  social::Link l{arcana, 0, 0};
  for (auto& x : all) if (x.arcana == arcana) l = x;
  return l;
}

// A character's Theurgy personality, what fills their gauge (theurgy.cpp); empty when the text is not there.
std::string theurgy_personality(int who);
}  // namespace p3a::screens
