// Quick status checks in a battle, a party slot at a time (the user's design, 2026-11-28). A slot's key enters its
// group and says the member's name with HP; each press of the same key after that says the next part: SP, ailments,
// buffs and debuffs (guarding, charges, shields and walls with them), the Theurgy gauge where the member has one, and
// round again to HP (the name only on entering); Shift with the key goes back a part. Another slot's key enters that group. The navigator (Fuuka, Mitsuru
// before her) is never in the battle's party; her SP pays for her support, so 5 says it.
// The slots are the save data's party order (GlobalWorkBpLib GWorkGetPartyID 0..3, party::ids), matched to the battle's
// units (UBtlCoreComponent.PlayerList) by GetUnitID; the words and numbers are the battle database's (battle_words.h).
#include "screens/battle_party.h"
#include "screens/battle_state.h"
#include "screens/battle_words.h"
#include "core/strings.h"
#include "devserver.h"
#include "log.h"
#include "party.h"
#include "seh.h"
#include "speech.h"
#include "world.h"
#include <format>

namespace p3a::screens::battle_party {
using namespace ue;

namespace {
TArray<UObject*>* battle_party() {
  UObject* core = battle_core();
  auto* a = core ? field<TArray<UObject*>>(core, "PlayerList") : nullptr;
  return a && a->num > 0 ? a : nullptr;
}
// Party slot i's battle unit, or null.
UObject* unit_in_slot(int i) {
  auto* a = battle_party();
  if (!a || i < 0) return nullptr;
  auto ids = party::ids();
  if (i < (int)ids.size())
    for (int k = 0; k < a->num; ++k)
      if (a->data[k] && btl_words().unit_int("GetUnitID", a->data[k]) == ids[(size_t)i]) return a->data[k];
  // A party the save data does not list (Episode Aigis's, a story battle's guests): the battle's own order.
  if (i >= (int)ids.size() && !ids.empty()) return nullptr;
  return i < a->num ? a->data[i] : nullptr;
}
// The parts of a member's status, each said on its own press.
std::vector<std::vector<std::string>> parts_of(UObject* u) {
  BtlWords& w = btl_words();
  std::vector<std::vector<std::string>> out;
  out.push_back({std::format("{} {}", strings::kHP, strings::of(w.unit_int("GetUnitHP", u), w.unit_int("GetUnitMaxHP", u)))});
  out.push_back({std::format("{} {}", strings::kSP, strings::of(w.unit_int("GetUnitSP", u), w.unit_int("GetUnitMaxSP", u)))});
  auto ail = w.ailment_lines(u);
  out.push_back(ail.empty() ? std::vector<std::string>{strings::kNoAilments.c_str()} : ail);
  auto eff = w.effect_lines(u);
  if (call_ret<bool>(u, "IsGuard")) eff.insert(eff.begin(), strings::kGuarding.c_str());
  out.push_back(eff.empty() ? std::vector<std::string>{strings::kNoEffects.c_str()} : eff);
  int tp = w.unit_int("GetUnitTP", u), max_tp = w.unit_int("GetUnitMaxTP", u);
  if (max_tp > 0) out.push_back({std::format("{} {}", strings::kTheurgyCharge, strings::of(tp, max_tp))});
  return out;
}
WeakObj g_unit;    // the group entered: whose status the next press goes on with
int g_part = -1;   // the part said last
std::vector<std::string> step(int i, int dir) {
  UObject* u = unit_in_slot(i);
  if (!u) { g_unit = {}; g_part = -1; return {strings::kNoPartyMemberInSlot.c_str()}; }
  auto parts = parts_of(u);
  WeakObj w = WeakObj::of(u);
  bool entering = !(w == g_unit) || g_part < 0;
  g_unit = w;
  const int n = (int)parts.size();
  g_part = entering ? 0 : ((g_part + dir) % n + n) % n;
  auto said = parts[(size_t)g_part];
  if (entering) said[0] = btl_words().unit_name(u) + ", " + said[0];
  return said;
}
std::vector<std::string> navigator_line() {
  int nav = party::navigator();
  party::Member m;
  if (!party::joined(nav) || !party::member(nav, m)) return {strings::kNoNavigator.c_str()};
  g_unit = {}; g_part = -1;   // a slot's key after this enters its group again
  return {std::format("{}, {}, {} {}", m.name, strings::kNavigator, strings::kSP, m.max_sp > 0 ? strings::of(m.sp, m.max_sp) : std::to_string(m.sp))};
}
}  // namespace

bool active() {
  bool on = false;
  guarded([&] {
    bool party_there = battle_party() != nullptr, exploring = world::exploring();
    on = party_there && !exploring;
    if (!on && battle_core()) log::writef("battle_party: off (party {}, exploring {}, core {})", party_there, exploring, (void*)battle_core());
  });
  if (!on) { g_unit = {}; g_part = -1; }   // a new battle enters its groups afresh
  return on;
}
void slot(int i, int dir) {
  std::vector<std::string> l;
  guarded([&] { l = step(i, dir); });
  if (!l.empty()) speech::speak_parts(l, true);
}
void navigator() {
  std::vector<std::string> l;
  guarded([&] { l = navigator_line(); });
  if (!l.empty()) speech::speak_parts(l, true);
}
void install() {
  dev::route("/battle/party", [](const dev::Request& r, int&) {
    int s = (int)dev::arg_int(r, "slot", 0);
    bool back = dev::arg_int(r, "back", 0) != 0;
    return dev::on_game([s, back] {
      std::string out;
      guarded([&] {
        if (!active()) { out = "not in battle\n"; return; }
        auto l = s >= 1 && s <= 4 ? step(s - 1, back ? -1 : 1) : s == 5 ? navigator_line() : std::vector<std::string>{};
        for (auto& x : l) out += x + "\n";
        out += std::format("part {}\n", g_part);
      });
      return out;
    });
  }, "?slot=1..4 [&back=1] what that party key (Shift: back a part) says now, stepping it as the key does; slot=5 the navigator");
}
}  // namespace p3a::screens::battle_party
