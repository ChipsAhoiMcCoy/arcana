// Battle (the skill, item and target lists are bespoke menus: battle_menus.cpp). The command wheel is a sprite; its
// state is reflected (battle_state.h reads it):
//   ABtlGuiStateManager.nowState     EBtlGuiState (TOP 1, SKILL 2, ITEM 3, TARGET 4, ...)
//   BP_BtlTargetManager_C             MainCharacter (whose turn), CursorTargets (the target the wheel points at)
// and the words come from the game's own battle database (UBtlDataBaseComponent: GetUnitName, GetUnitHP,
// GetSkillName, GetSkillCost, GatAnalizeAttr, GetAttackName). Keyboard: Space attack, E skills (Persona),
// R items, C guard, A and D change target (measured 2026-10-27 on the 4/9 rooftop battle).
// What happens is watched on UBtlCoreComponent (PlayerList, EnemyList, CurrentPhase, CurrentAction, the Rush request)
// and the hit popups (BP_BtlGuiDamage2_C); Analyze's own target list is BP_BtlGuiAnalyze_C's (EnemyList, TargetIndex).
// The wheel is played with the game's own keys (the player's call, 2026-11-01: no command list); F1 names the open
// ones. Left and right step BP_BtlGuiComponent_C.EnemyList (sorted live targets; "Target Index" + 1 mod its length,
// On Select Next Target): a target's position there is its "1 of 2". The game clears IsCreateEnemyList as the wheel
// opens a turn and builds the turn's list on its next tick, setting it again: until then EnemyList is the last turn's,
// empty on a battle's first.
#include "screens/screen.h"
#include "screens/util.h"
#include "screens/battle.h"
#include "screens/battle_state.h"
#include "screens/battle_words.h"
#include "core/strings.h"
#include "input.h"
#include "keys.h"
#include "items.h"
#include "msg.h"
#include "party.h"
#include "persona.h"
#include "speech.h"
#include "core/battle_text.h"
#include "core/text_clean.h"
#include "core/bmd.h"
#include "bmdfile.h"
#include "hooks.h"
#include "log.h"
#include "seh.h"
#include <windows.h>
#include <xinput.h>
#include <format>
#include <cstring>
#include <map>
#include <set>
#include <vector>

namespace p3a::screens {
using namespace ue;

int g_start_level[32];
std::string g_party_name[32];
std::map<int, StartPersona> g_start_personas;
void forget_battle_start() { memset(g_start_level, 0, sizeof g_start_level); g_start_personas.clear(); }
// A member's Personas as the battle begins: the hero's whole stock, a member's equipped one.
static void remember_personas(int unit_id) {
  auto keep = [](int pid, int level, const uint8_t* st, const uint16_t* sk) {
    StartPersona p;
    p.level = level;
    memcpy(p.stats.data(), st, sizeof p.stats);
    memcpy(p.skills.data(), sk, sizeof p.skills);
    g_start_personas[pid] = p;
  };
  if (unit_id == 1) { for (auto& o : persona::stock()) keep(o.id, o.level, o.stats, o.skills); return; }
  if (const uint8_t* e = party::persona_entry(unit_id))
    if (int pid = *(uint16_t*)(e + 2)) keep(pid, *(uint16_t*)(e + 4), e + 0x1C, (const uint16_t*)(e + 0xC));
}

class BattleScreen : public Screen {
  Finder top_{"BP_BtlTopUI_C"};
  int state_ = -1;
  WeakObj actor_, target_, last_actor_;
  bool turn_due_ = false;   // the wheel opened a turn whose line is not said yet: it waits for the turn's list
  BtlWords& w_ = btl_words();   // the battle database's words and numbers
  // An enemy on the wheel with its place among the targets left and right go through.
  std::string target_line(UObject* t) {
    std::string s = w_.enemy(t);
    auto* l = wheel_enemies();
    for (int i = 0; l && l->num > 1 && i < l->num; ++i)
      if (l->data[i] == t) { s += std::format(", {}", strings::of(i + 1, l->num)); break; }
    return s;
  }
  // The wheel's commands, each with the game's key (or button). key_index: BP_BtlTopUI_C.KeyControl's slot, the one
  // its key checks (0 attack, 1 guard, 2 Persona, 3 item, 4 Shift, 5 analyze, 6 tactics, 7 assist, 8 rush, 9 survey;
  // BP_BtlTopUI 47757-50523), -1 none.
  struct Cmd { int key_index; const strings::Hint* key; };
  static constexpr Cmd kCmds[] = {
      {0, &strings::kKeyAttack}, {2, &strings::kKeySkills},  {3, &strings::kKeyItems},   {1, &strings::kKeyGuard},
      {6, &strings::kKeyTactics}, {5, &strings::kKeyAnalyze}, {9, &strings::kKeySurvey}, {8, &strings::kKeyRush},
      {-1, &strings::kKeyTheurgy}, {4, &strings::kKeyShift},  {7, &strings::kKeyAssist},
  };
  bool open(const Cmd& c) {
    UObject* top = top_.get();
    if (c.key == &strings::kKeyTheurgy) {
      UObject* a = acting_member();
      int tp = w_.unit_int("GetUnitTP", a), max_tp = w_.unit_int("GetUnitMaxTP", a);
      return max_tp > 0 && tp >= max_tp;
    }
    // Shift: after a 1 More with someone to pass to (BP_BtlTopUI_C.IsOneMore, which shows the game's Shift button).
    if (c.key == &strings::kKeyShift && (!top || !get_bool(top, "IsOneMore"))) return false;
    auto* kc = top ? field<TArray<bool>>(top, "KeyControl") : nullptr;
    return c.key_index < 0 || !kc || c.key_index >= kc->num || kc->data[c.key_index];
  }
  // F1 on the wheel: each open command's key (the game's tutorials lock some), then changing the target.
  std::string top_keys() {
    std::string s;
    for (auto& c : kCmds)
      if (open(c)) s += (s.empty() ? "" : ", ") + std::string((*c.key)());
    return s + ". " + strings::kChangeTargetKeys();
  }

  // ---- what happened: every unit's HP is watched, and the action banner (the skill name the game shows at the
  // top while someone acts, BP_BtlSkillNamePanel_C) is spoken with the actor's name. Damage numbers are sprites.
  struct Unit { std::string name; int hp; bool enemy; uint32_t status = 0; };
  bool downed_since_turn_ = false;
  // The game's own "1 MORE" (BP_BtlGuiOneMore_C, made by BP_BtlGuiIcon.CreateOneMorePanel(IsEnemy, LifeTime) and gone
  // after its lifetime). A weakness hit that defeats its target gives a 1 More with no Down to see: an Agi that killed
  // a Cowardly Maya (Thebel floor 4, 2026-11-24) drew the panel and the hero acted again, and nothing was said.
  int one_more_panels_ = watch::want("BP_BtlGuiOneMore_C");
  WeakObj one_more_panel_;   // the panel last seen
  bool one_more_ = false;    // a party member's 1 More panel came up since the last turn
  bool shift_pending_ = false;   // a 1 More said before the wheel's Shift came up: said once it does
  void watch_one_more() {
    UObject* p = watch::get(one_more_panels_);
    if (!p || WeakObj::of(p) == one_more_panel_) return;
    one_more_panel_ = WeakObj::of(p);
    if (!get_bool(p, "IsEnemy")) one_more_ = true;
  }
  // EBtlDataBadStatus bits the game tracks per unit: 0 dizzy, 1 charm .. 8 poison, 13 down (GetBadStatus).
  uint32_t status_of(UObject* u) {
    uint32_t bits = 0;
    for (int t : {0, 1, 2, 3, 4, 5, 6, 7, 8, 13})
      if (w_.has_ailment(u, t)) bits |= 1u << t;
    return bits;
  }
  std::map<WeakObj::Key, Unit> units_;
  std::set<WeakObj::Key> won_enemies_;   // the enemies left when the battle was won (watch())
  WeakObj advantage_of_;                 // the battle whose advantage line was said
  // The action banner is the game's skill-name panel (BP_BtlSkillNamePanel_C): BP_BtlGuiIconComponent's
  // CreateSkillNamePanelForBP(cmd, id, isEnemy, time) makes a new one for every banner (any panel still up is removed
  // first) and fills it through SetSkillID / SetItemName / SetCommonText: `Text` the words drawn, `Skill ID` the skill
  // (set by SetSkillID only). Each panel is said once.
  int panels_ = watch::want("BP_BtlSkillNamePanel_C");
  WeakObj banner_panel_;   // the panel last said
  // Who the player just picked a skill, item or Guard for: that member's next banner is what the player chose, and is
  // not said (the user's call, 2026-11-05: any member the player commands). Whatever a member does of their own accord
  // is said: nothing is picked on the wheel (Rush), for a member on orders or an ailment (no wheel), or once anyone else acts.
  WeakObj picked_;
  // Whose action the player gave on the wheel or in its lists (a plain attack too): the one unit it hits is the one
  // the player chose, so its damage or healing is said without the name (the user's call, 2026-11-10). Dropped once
  // anyone else acts, so a later turn of the same member that no wheel opened (an ailment, orders) names its target.
  WeakObj commanded_;
  // Rush (Tab): BP_BtlGuiComponent ChangeRush flips the core's request (RequestRushMode) and shows or hides the RUSH
  // sign, a sprite; the fighting phase follows it at the next turn. The request is what the press changed.
  bool rush_ = false;
  // What a hit was: the word the game throws up beside the number (BP_BtlGuiDamage2_C, one actor per popup, made by
  // BP_BtlGuiIcon CreateDamage and started with the unit and a type: 5 WEAK, 6 CRITICAL, 7 RESIST, 8 MISS, 9 BLOCK;
  // 0 to 4 are the plain numbers, which the HP watch says). A miss or a block changes no HP: nothing was said at all.
  int popups_ = watch::want("BP_BtlGuiDamage2_C", true);
  std::set<WeakObj::Key> popups_seen_;
  std::set<WeakObj::Key> popped_;   // units a new popup came up on since their damage was last said (this action)
  WeakObj popped_by_;               // the action they came up in
  void hit_words(UObject* action_now, int st) {
    std::set<WeakObj::Key> live;
    for (UObject* o : watch::all(popups_)) {
      UObject* u = get<UObject*>(o, "Chara");
      if (!u) continue;   // not started yet
      auto key = WeakObj::of(o).key();
      live.insert(key);
      if (popups_seen_.count(key)) continue;
      popped_.insert(WeakObj::of(u).key());
      int type = get<int32_t>(o, "Type");
      if (type < 5 || type > 9) continue;
      const char* word = strings::kHitWords[type - 5];
      bool chosen = st == 0 && action_now && commanded_.resolve() == action_now && attacked(action_now) == u;
      speech::speak(chosen ? std::string(word) : strings::fmt(strings::kHitOnFmt, word, w_.unit_name(u)), false);
    }
    popups_seen_.swap(live);
  }
  // The one unit an action hits (ABtlActor.GetActionTargets), null for none or several.
  UObject* attacked(UObject* action) {
    UFunction* f = action ? find_function(class_of(action), "GetActionTargets") : nullptr;
    if (!f) return nullptr;
    Params p(f);
    if (!call(action, p)) return nullptr;
    auto* a = p.at<TArray<UObject*>>("ReturnValue");
    if (!a || !a->data) return nullptr;
    UObject* one = a->num == 1 ? a->data[0] : nullptr;
    msg::game_free(a->data);
    a->data = nullptr;
    return one;
  }
  // The situation banner (BP_BtlGuiJyokyoHelp_C, "jyokyohelp" in BMD_BtlJyokyoHelp): the box the game slides in for
  // what a turn did beyond its damage, a boss's warnings above all: "... is charging up...", "... has set its
  // sights!", "... is targeting Mitsuru!", "...'s glare sharpens!", "... is almost done charging up...!"; an enemy's
  // AI_ACT_WAIT2(msg) turn ("Supreme Hand is waiting..."), "... ran away...", stat changes, "Insufficient SP!".
  // BP_BtlGuiIcon makes one actor per banner and removes it once shown: SetParam (live names, which differ in case
  // from the decompile: genus, ID, msgNo, var1, var2, renderTime, DelayTime, flags), then Start() (IsStart) builds
  // MsgObj or MsgObj2, a UBtlGuiDrawObjectMsg whose Data (FBtlGuiDrawMsg) holds the file (bmd), msgNo and pageNo, and
  // SetVariableJyokyoHelp (exe+0x1004f80) puts the banner's own values in the message's variables: slot 0 a name (genus
  // 1 a party member by ID; else flags & 2 a Persona, flags & 4 something of var1, otherwise an enemy by ID: 207 for a
  // Supreme Hand, 2026-11-18), slot 1 var1 (an item's name with flags & 1, else the number), slot 2 var2. The draw
  // object builds its own page once, at its first draw (exe+0xff3c70), and keeps it: Data +0x48 the FBmdPage, +0x54
  // and +0x60 the msgNo and pageNo it was built for (the draw rebuilds while they differ from +0x50 / +0x58). That
  // page, rendered, is the banner's words: its own, whatever other banner of the same message is up. Each message
  // object is said once, when its page is built.
  int helps_ = watch::want("BP_BtlGuiJyokyoHelp_C", true);
  std::set<WeakObj::Key> helps_said_;
  // A banner's message as its draw object holds it; page null until the game built it.
  struct HelpMsg { UObject* bmd = nullptr; int dialog = -1, page_no = 0; void* page = nullptr; };
  static bool help_msg(UObject* m, HelpMsg& out) {
    static UStruct* data_struct = nullptr;
    static int32_t o_bmd = -1, o_no = -1, o_page = -1;
    static bool logged = false;
    if (!data_struct)
      if (FField* p = find_prop(class_of(m), "Data")) {
        data_struct = (UStruct*)prop_inner_object(p);
        if (data_struct) { o_bmd = offset_of(data_struct, "bmd"); o_no = offset_of(data_struct, "msgNo"); o_page = offset_of(data_struct, "pageNo"); }
      }
    uint8_t* data = field<uint8_t>(m, "Data");
    if (!data || o_bmd < 0 || o_no < 0 || o_page < 0) {
      if (!logged) log::writef("battle: banner message layout not found (Data {}, bmd {}, msgNo {}, pageNo {})", (void*)data, o_bmd, o_no, o_page);
      logged = true;
      return false;
    }
    out.bmd = *(UObject**)(data + o_bmd);
    out.dialog = *(int32_t*)(data + o_no);
    out.page_no = *(int32_t*)(data + o_page);
    void* page = *(void**)(data + o_no - 8);
    bool built = page && *(int32_t*)(data + o_no + 4) == out.dialog && *(int32_t*)(data + o_page + 8) == out.page_no;
    out.page = built ? page : nullptr;
    return true;
  }
  // A variable function's slot (BMD function table 2, its one argument stored as two bytes each plus 1: 01 01 slot 0,
  // 02 01 slot 1).
  static int var_slot(const core::bmd::Function& f) {
    if (f.table != 2 || f.args.empty()) return -1;
    int a = f.args[0] & 0xFF, b = f.args[0] >> 8;
    return (a == 1 ? b : a) - 1;
  }
  // The name a banner's slot 0 holds, from the banner's own genus, ID and flags as SetVariableJyokyoHelp reads them:
  // the unit of that side with that unit id, a Persona; "" when the mod cannot tell.
  std::string help_name(UObject* btl, UObject* help) {
    int genus = get<int32_t>(help, "genus"), id = get<int32_t>(help, "ID"), flags = get<int32_t>(help, "flags");
    if (genus != 1 && (flags & 2)) return persona::name(id);
    if (genus != 1 && (flags & 4)) return {};
    auto* a = field<TArray<UObject*>>(btl, genus == 1 ? "PlayerList" : "EnemyList");
    for (int i = 0; a && i < a->num; ++i)
      if (a->data[i] && w_.unit_int("GetUnitID", a->data[i]) == id) return w_.unit_name(a->data[i]);
    return genus == 1 ? party::name(id) : std::string();
  }
  // The hero's last name as the player entered it (UGlobalWork +0xC768, UTF-8; the first name is at +0xC728, the two
  // joined at +0xC7A8): message function 4 1 ("Tank-Form Shadow is targeting yuki!", jyokyohelp_BOSS015, 2026-11-18;
  // 4 2 is the first name).
  static std::string hero_last_name() {
    uint8_t* g = party::global_work();
    std::string s;
    if (g) guarded([&] { const char* p = (const char*)g + 0xC768; size_t n = strnlen(p, 32); if (n < 32) s.assign(p, n); });
    return s;
  }
  // The banner's words from the file, its variables filled from the banner's own values (message functions 4 1 and
  // 4 2 the hero's names); "" when one of them is something the mod cannot name.
  std::string help_from_file(const core::bmd::File& f, int dialog, int page, UObject* help, UObject* btl) {
    if (dialog < 0 || dialog >= (int)f.dialogs.size()) return {};
    auto& d = f.dialogs[dialog];
    if (page < 0 || page >= (int)d.pages.size()) return {};
    core::bmd::Page pg = d.pages[page];
    for (auto it = pg.functions.rbegin(); it != pg.functions.rend(); ++it) {
      if (it->pos > pg.text.size()) continue;
      std::string v;
      if (int slot = var_slot(*it); slot == 0) v = help_name(btl, help);
      else if (slot == 1 || slot == 2) {
        int n = get<int32_t>(help, slot == 1 ? "var1" : "var2");
        if (n == -1) return {};
        v = slot == 1 && (get<int32_t>(help, "flags") & 1) ? items::name_of(n) : std::to_string(n);
      } else if (it->table == 4 && it->index == 2) v = party::name(1);
      else if (it->table == 4 && it->index == 1) v = hero_last_name();
      else continue;
      if (v.empty()) return {};
      pg.text.insert(it->pos, v);
    }
    return core::clean_text(core::bmd::plain(pg));
  }
  // The banners that repeat what is said already: an ailment taken ("Inflicted with Freeze!": the unit's own line says
  // who), and the blank and test entries.
  static bool help_said_elsewhere(const std::string& name) {
    return name.starts_with("jyokyohelp_SET_BAD_") || name.starts_with("jyokyohelp_BLANK") ||
           name.starts_with("jyokyohelp_LOCALIZATION");
  }
  void watch_help(UObject* btl) {
    std::set<WeakObj::Key> live;
    for (UObject* h : watch::all(helps_)) {
      UObject* m = get<UObject*>(h, "MsgObj");
      if (!m) m = get<UObject*>(h, "MsgObj2");
      if (!m || !get_bool(h, "IsStart")) continue;   // not started: nothing drawn yet
      auto key = WeakObj::of(m).key();
      live.insert(key);
      if (helps_said_.count(key)) continue;
      HelpMsg d;
      if (!help_msg(m, d) || !d.page || !d.bmd) continue;   // not drawn yet: its page comes with its first draw
      auto file = bmdfile::load(d.bmd);
      if (!file) continue;   // the file not read yet: a later tick
      helps_said_.insert(key);
      std::string name = d.dialog >= 0 && d.dialog < (int)file->dialogs.size() ? file->dialogs[d.dialog].name : "";
      if (help_said_elsewhere(name)) continue;
      std::string text = msg::page_string(d.page);   // rendered and cleaned
      // The page the game built renders to nothing (no page renderer in this build): the file's page, filled in.
      bool from_file = !core::has_words(text);
      if (from_file) text = help_from_file(*file, d.dialog, d.page_no, h, btl);
      if (!core::has_words(text)) continue;
      log::writef("battle: banner {}{}", name, from_file ? " (from the file)" : "");
      speech::speak(text, false);
    }
    std::erase_if(helps_said_, [&](const WeakObj::Key& k) { return !live.count(k); });
  }
  void say_banner(UObject* actor, const std::string& b) {
    if (actor && WeakObj::of(actor) == picked_) { picked_ = {}; return; }
    std::string who = actor ? w_.unit_name(actor) : "";
    speech::speak(who.empty() ? b : std::format("{}: {}", who, b), false);
  }
  // Everything that happened since the last tick, in the order it is said: Rush, the action's banner, what each hit
  // was, then every unit's HP and ailments and who fell.
  void watch() {
    UObject* core = battle_core();
    if (!core) return;
    int st = gui_state();
    watch_rush(core);
    UObject* action_now = get<UObject*>(core, "CurrentAction");
    if (!hits_.empty() && (st != 0 || !(WeakObj::of(action_now) == hits_by_))) flush_hits();   // that action is over
    watch_commands(st, action_now);
    watch_banner(action_now);
    watch_help(core);
    if (!(WeakObj::of(action_now) == popped_by_)) { popped_.clear(); popped_by_ = WeakObj::of(action_now); }
    hit_words(action_now, st);
    watch_units(core, st, action_now);
    say_landed();
    watch_one_more();
  }
  // On is said at once, over anything else: it answers the player's own press. Off queues: the game also ends a rush
  // itself (a boss's mid-battle lines: DisableRush), with the last blow's news still being read.
  void watch_rush(UObject* core) {
    if (bool rush = call_ret<bool>(core, "CheckRequestRushMode"); rush != rush_) {
      rush_ = rush;
      speech::speak(rush ? strings::kRushOn.c_str() : strings::kRushOff.c_str(), rush);
    }
  }
  // Whose action is the player's own (picked_, commanded_): set while the wheel or one of its lists is up, dropped
  // once anyone else acts.
  void watch_commands(int st, UObject* action_now) {
    if (st == 1) picked_ = {};
    else if (st == 2 || st == 3 || st == 4 || st == 7 || st == 11) picked_ = WeakObj::of(acting_member());
    if (st == 0 && action_now && !(WeakObj::of(action_now) == picked_)) picked_ = {};
    if (st != 0) commanded_ = WeakObj::of(acting_member());
    else if (action_now && !(WeakObj::of(action_now) == commanded_)) commanded_ = {};
  }
  // The action banner: a panel not said yet (above), with its words.
  void watch_banner(UObject* action_now) {
    UObject* p = watch::get(panels_);
    if (!p || WeakObj::of(p) == banner_panel_) return;
    auto* text = field<FString>(p, "Text");
    std::string b = text ? core::clean_text(to_utf8(*text)) : std::string();
    if (!core::has_words(b)) return;   // made, not filled yet
    banner_panel_ = WeakObj::of(p);
    paid_ = {};   // a new action (the same member again after a 1 More pays again)
    flush_hits();   // the last action's repeated hits, before this one's name
    // GetActionType (EBtlCommandType): 1 a plain attack has no banner, and a skill's banner is its own skill: any
    // other skill is a passive of the one attacked (a counter: "High Counter" came under the attacker's name,
    // 2026-11-06).
    int type = action_now ? call_ret<uint8_t>(action_now, "GetActionType") : 0;
    auto* skill = field<int32_t>(p, "Skill ID");
    // Only a passive skill (the table's type 1: Counter, High Counter) is another unit's: an active one is the actor's
    // own, even when its action still holds the last one (Elizabeth's second action of a turn: her Slash Attack read
    // as "Makoto: Slash Attack", 2026-11-24).
    bool theirs = type != 1 && (type != 2 || !skill || *skill == call_ret<int32_t>(action_now, "GetSkillID"));
    if (!theirs && skill && *skill > 0 && !persona::skill_passive(*skill)) theirs = true;
    say_banner(theirs ? action_now : attacked(action_now), b);
  }
  // HP changes, ailments and defeats. The enemies an All-Out Attack finishes keep their HP until the results take them
  // away, after Shuffle Time ("2 Muttering Tiara defeated" came after the cards, 2026-11-09): a deal with a card still
  // to take (the next battle's comes on the same actor, its last deal's picks all made) means the battle is won, and
  // whoever is left is defeated now. A battle with no Shuffle Time (a scripted one) has no deal: its defeats waited
  // for the results, through the whole attack in silence (2026-11-25). The attack's finishing cut says the same
  // sooner, with or without cards (allout_finishing).
  // Who has the advantage, once per battle before anything of it is read: the battle's FBtlEncountParam.Preemptive
  // (EBtlEncountPreemptive: 1 Enemy, 2 Ally; it read Ally after a strike that started the fight, 2026-11-11), which
  // the game shows as a splash (BP_BtlGuiEncountAlert) on a battle's first wave only (EncountIndex 0).
  void say_advantage(UObject* core) {
    WeakObj w = WeakObj::of(core);
    if (w == advantage_of_) return;
    advantage_of_ = w;
    auto* param = field<uint8_t>(core, "EncountParameter");
    int pre = param && get<int32_t>(core, "EncountIndex") == 0 ? param[4] : 0;
    if (pre == 2) speech::speak(strings::kAdvantageParty.c_str(), false);
    else if (pre == 1) speech::speak(strings::kAdvantageEnemy.c_str(), false);
  }
  // A physical skill takes its HP cost from the one using it as it lands: that drop is the price the player read on
  // the skill's row, not damage (the user's call, 2026-11-16). Only the acting unit's own drop by exactly its skill's
  // HP cost, once per action (paid_: dropped once anyone else acts); a counter or anything else on them is still said.
  WeakObj paid_;
  // An action that strikes the same unit again (Strength's Mobius Rondo hits each member six times; a weapon that
  // hits more than once): its damage is added up per unit and said at its last hit, one line per unit ("Makoto 147
  // damage in all"; a single hit, "Makoto 26 damage"), not a line per hit (Mobius Rondo was 24 lines, 2026-11-24).
  // Saying the first hit as it landed made one attack sound like two ("14 damage", then "59 damage in all"), and
  // waiting for the action's end said every number a second or more after its hit (2026-11-25).
  // Which hit is the last is the game's own call: a multi-hit animation's notifies deal the damage in portions
  // (PreAffectSkillDamagePortion, the rest with AffectSkillDamageRestPortion), and BP_BtlGuiIcon CreateDamage keeps
  // each unit with a portion shown in PotionPatamMap (added at the first portion, removed by the hit that is not one).
  // A unit's damage is said once a popup came up on it (the hit has been shown, so the map has had its say) and it is
  // not in the map. Anything left (no popup: the display off) goes when the action is over: another unit acts, the
  // next banner comes up (the same unit's next action) or a wheel or list opens. A unit that falls says so instead.
  int icons_ = watch::want("BP_BtlGuiIcon_C", true);
  // TMap<BP_BtlCharacterBase_C*, int32>: a TSparseArray of 0x18-byte elements (key at +0), allocation bits as in
  // ue::datatable_rows (inline at +0x10, secondary at +0x20, NumBits at +0x28).
  bool portion_open(const WeakObj::Key& unit) {
    for (UObject* icon : watch::all(icons_)) {
      auto* map = field<uint8_t>(icon, "PotionPatamMap");
      if (!map) continue;
      auto& elems = *(TArray<uint8_t>*)map;
      const uint32_t* secondary = *(const uint32_t**)(map + 0x20);
      const uint32_t* bits = secondary ? secondary : (const uint32_t*)(map + 0x10);
      int32_t num_bits = *(int32_t*)(map + 0x28);
      for (int i = 0; elems.data && i < elems.num && i < 64; ++i) {
        if (i < num_bits && !((bits[i / 32] >> (i % 32)) & 1)) continue;   // a removed element
        UObject* u = *(UObject**)(elems.data + i * 0x18);
        if (u && WeakObj::of(u).key() == unit) return true;
      }
    }
    return false;
  }
  struct Hits { WeakObj::Key key; std::string name; int total; int count; bool chosen; };
  std::vector<Hits> hits_;
  WeakObj hits_by_;   // the acting unit whose action landed them
  Hits* hit_on(const WeakObj::Key& k) {
    for (auto& h : hits_) if (h.key == k) return &h;
    return nullptr;
  }
  void drop_hits(const WeakObj::Key& k) { std::erase_if(hits_, [&](const Hits& h) { return h.key == k; }); }
  void say_hit(const Hits& h) {
    std::string one = std::format("{} {}", h.total, strings::kDamage);
    if (h.count < 2) speech::speak(h.chosen ? one : std::format("{} {}", h.name, one), false);
    else speech::speak(h.chosen ? strings::fmt(strings::kDamageInAllFmt, h.total)
                                : strings::fmt(strings::kNamedDamageInAllFmt, h.name, h.total), false);
  }
  // The units whose last hit has landed: said now, the rest wait for theirs.
  void say_landed() {
    std::erase_if(hits_, [&](const Hits& h) {
      if (!popped_.count(h.key) || portion_open(h.key)) return false;
      popped_.erase(h.key);
      say_hit(h);
      return true;
    });
  }
  void flush_hits() {
    for (auto& h : hits_) {
      auto u = units_.find(h.key);
      if (u == units_.end() || u->second.hp <= 0) continue;   // it fell: that is said instead
      say_hit(h);
    }
    hits_.clear();
    hits_by_ = {};
  }
  // The enemies that ran away: their own action an escape (GetActionType 4, BTL_ACT_ESCAPE: AI_ACT_ESCAPE sets it, and
  // so does a Fear turn's flee roll, exe+0xfd4200). One leaves with its HP at 0 and was said as defeated after the
  // game's "Supreme Hand ran away..." (2026-11-18). The enemy's escape has no failing branch (exe+0xfe4740 raises the
  // banner and nothing else; ESCAPE_FAILUR and ESCAPE_IMPOSS are the party's), but one that acts again with another
  // action is still here and fights on: it is no longer counted as fled.
  std::set<WeakObj::Key> fled_;
  bool paid_cost(UObject* u, UObject* action_now, int d) {
    if (!action_now || u != action_now || d >= 0 || WeakObj::of(u) == paid_) return false;
    if (call_ret<uint8_t>(action_now, "GetActionType") != 2) return false;
    int cost = w_.skill_hp_cost(call_ret<int32_t>(action_now, "GetSkillID"), action_now);
    if (cost <= 0 || -d != cost) return false;
    paid_ = WeakObj::of(u);
    return true;
  }
  void watch_units(UObject* core, int st, UObject* action_now) {
    if (st != 0 || !action_now || !(WeakObj::of(action_now) == paid_)) paid_ = {};
    if (action_now) {
      auto k = WeakObj::of(action_now).key();
      uint8_t type = call_ret<uint8_t>(action_now, "GetActionType");
      if (type == 4) fled_.insert(k);
      else if (type != 0) fled_.erase(k);   // 0: no action set (the turn's start clears it), not a new one
    }
    say_advantage(core);
    UObject* deal = shuffle_ui();
    int picks = deal ? get<int32_t>(deal, "EnableSelectNum") : 0;
    bool won = (picks > 0 && get<int32_t>(deal, "SelectedCardNum") < picks) || allout_finishing();
    std::map<WeakObj::Key, Unit> next;
    std::vector<std::string> defeated;
    for (const char* list : {"PlayerList", "EnemyList"}) {
      auto* a = field<TArray<UObject*>>(core, list);
      for (int i = 0; a && i < a->num; ++i) {
        UObject* u = a->data[i];
        if (!u) continue;
        WeakObj w = WeakObj::of(u);
        auto key = w.key();
        Unit cur{w_.unit_name(u), w_.unit_int("GetUnitHP", u), list[0] == 'E', 0};
        // Once counted as defeated an enemy stays so: with the card taken the deal no longer says the battle is won,
        // and the HP they still hold read as "healed 54", "is down" and a second "defeated" (2026-11-10).
        if (cur.enemy && (won || won_enemies_.count(key))) { cur.hp = 0; won_enemies_.insert(key); }
        cur.status = cur.hp > 0 ? status_of(u) : 0;
        if (!cur.enemy) {   // party levels as the battle began, for the victory screen's level ups
          int id = w_.unit_int("GetUnitID", u);
          if (id > 0 && id < 32 && !g_start_level[id]) {
            g_start_level[id] = persona::unit_level(id) ? persona::unit_level(id) : w_.unit_int("GetUnitLevel", u);
            g_party_name[id] = cur.name;
            remember_personas(id);
          }
        }
        auto it = units_.find(key);
        if (it != units_.end() && cur.hp != it->second.hp && cur.hp >= 0 && it->second.hp >= 0) {
          int d = cur.hp - it->second.hp;
          Hits* again = d < 0 && st == 0 && action_now && WeakObj::of(action_now) == hits_by_ ? hit_on(key) : nullptr;
          if (paid_cost(u, action_now, d)) {}   // the skill's own HP cost: the skill list already said it
          else if (cur.hp == 0 && cur.enemy) { drop_hits(key); if (!fled_.count(key)) defeated.push_back(cur.name); }
          else if (cur.hp == 0) { drop_hits(key); speech::speak(std::format("{} {}", cur.name, strings::kKnockedOut), false); }
          else if (again) { again->total -= d; ++again->count; }   // said with the rest once the action is over
          else {
            // The player's own choice of this one unit: the number alone. Anything else names who it landed on (an
            // enemy's or an ally's own action, a whole side, an attack sent back at the attacker).
            bool chosen = st == 0 && action_now && commanded_.resolve() == action_now && attacked(action_now) == u;
            if (d < 0 && st == 0 && action_now) {   // said once the action is over, with any hits after it
              if (!(WeakObj::of(action_now) == hits_by_)) { flush_hits(); hits_by_ = WeakObj::of(action_now); }
              hits_.push_back({key, cur.name, -d, 1, chosen});
            } else {
              std::string s = d < 0 ? std::format("{} {}", -d, strings::kDamage) : std::format("{} {}", strings::kHealed, d);
              speech::speak(chosen ? s : std::format("{} {}", cur.name, s), false);
            }
          }
        }
        if (it != units_.end()) {
          uint32_t gained = cur.status & ~it->second.status;
          for (int t = 0; t <= 13; ++t)
            if (gained & (1u << t)) {
              speech::speak(std::format("{} {}", cur.name, strings::kBadStatus[t]), false);
              if (t == 13 && cur.enemy) downed_since_turn_ = true;
            }
        }
        next[key] = cur;
      }
    }
    for (auto& [k, u] : units_)
      if (u.enemy && u.hp > 0 && !next.count(k) && !fled_.count(k)) { drop_hits(k); defeated.push_back(u.name); }
    units_.swap(next);
    std::erase_if(won_enemies_, [&](const WeakObj::Key& k) { return !units_.count(k); });   // gone with the battle
    std::erase_if(fled_, [&](const WeakObj::Key& k) { return !units_.count(k); });
    // Enemies falling together (an All-Out Attack) in one line: "2 Cowardly Maya defeated", not the same line twice.
    if (!defeated.empty()) speech::speak(core::defeated_line(defeated), false);
  }

  void announce_top() {
    UObject* a = acting_member();
    UObject* t = wheel_target();
    actor_ = WeakObj::of(a);
    target_ = WeakObj::of(t);
    // Kept short, it is heard every turn (the user's call, 2026-11-11): HP and SP without their maxima, and the
    // target without its place in the row. A move reads the place; the details and the review key the rest.
    std::string s = std::format("{}, {}", w_.unit_name(a), w_.hp_sp_short(a));
    // The Theurgy gauge (GetUnitTP / GetUnitMaxTP): full means the Theurgy command is open.
    int tp = w_.unit_int("GetUnitTP", a), max_tp = w_.unit_int("GetUnitMaxTP", a);
    if (max_tp > 0 && tp >= max_tp) s += std::string(", ") + strings::kTheurgyReadyWords;
    if (t) s += ". " + w_.enemy(t);
    // Main commands the game has greyed out on the wheel (KeyControl: a tutorial's battle, and the last turn of the
    // final battle, where only the Persona's skills are left, 2026-11-11): named, or a press on one goes unanswered.
    std::string locked;
    for (int i = 0; i < 4; ++i)
      if (!open(kCmds[i])) locked += (locked.empty() ? "" : ", ") + std::string(strings::kWheelCommands[i]);
    if (!locked.empty()) s += std::format(". {} {}", locked, strings::kUnavailable);
    if (countdown_on_) s += std::format(". {} {}", core::countdown_text(countdown_was_, false), strings::kTimeLeft);
    speech::speak(s, false);   // queued after what just happened
  }

  // A battle's countdown (BP_BtlCountdown_C, the core's Countdown once a script ran BTL_COUNTDOWN_START; the
  // Priestess's monorail, encounter 701, is the only one): Timer falls in real time while IsPlay is set, through
  // every turn and menu; BTL_COUNTDOWN_REDUCE slides it down with IsAnimation set, to AnimationEndTime. IsVisible
  // also drops for cut-ins, so it is not read. Said when it starts, when it is cut, at its marks, and with each turn.
  bool countdown_on_ = false, countdown_cut_ = false;
  float countdown_was_ = 0;
  void countdown_tick(UObject* battle) {
    UObject* c = battle ? get<UObject*>(battle, "Countdown") : nullptr;
    float t = c ? get<float>(c, "Timer") : 0.0f;
    bool cut = c && get_bool(c, "IsAnimation");
    if (!c || (!cut && !(get_bool(c, "IsPlay") && t > 0))) {
      // Run out (not stopped by a won battle, which leaves time on it): the screen shows 0:00 and the battle is lost
      // at the turn's end; the last mark said was "10 seconds left" (2026-11-24).
      if (countdown_on_ && c && !cut && t <= 0) speech::speak(strings::kTimeUp.c_str(), false);
      countdown_on_ = countdown_cut_ = false;
      return;
    }
    if (!countdown_on_) {
      countdown_on_ = true;
      countdown_was_ = t;
      speech::speak(std::format("{} {}", strings::kTimeLeftStart, core::countdown_text(t, true)), false);
      return;
    }
    if (cut) {
      if (countdown_cut_) return;
      countdown_cut_ = true;
      countdown_was_ = get<float>(c, "AnimationEndTime");
      speech::speak(std::format("{} {}", core::countdown_text(countdown_was_, true), strings::kTimeLeft), false);
      return;
    }
    countdown_cut_ = false;
    if (int mark = core::countdown_mark(countdown_was_, t); mark >= 0)
      speech::speak(std::format("{} {}", core::countdown_text((float)mark, true), strings::kTimeLeft), false);
    countdown_was_ = t;
  }

  // TOP: whose turn it is and the target, said from background() (top_tick).
  // target_press: left or right pressed since the last tick (the keys and the D-pad), read every tick so that a press
  // from another list or from the field is never taken for one on the wheel.
  uint32_t target_keys_seen_ = 0;
  uint16_t target_pad_was_ = 0;
  bool target_press() {
    uint32_t n = 0;
    for (uint32_t vk : {(uint32_t)VK_LEFT, (uint32_t)VK_RIGHT, (uint32_t)'A', (uint32_t)'D'}) n += keys::movement_presses(vk);
    uint16_t pad = input::real_buttons() & (XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT);
    // A press made in the mod layer stays held as its button when the triggers let go: it was never one on the wheel.
    bool pressed = n != target_keys_seen_ || (!input::layer_open() && (pad & ~target_pad_was_));
    target_keys_seen_ = n;
    target_pad_was_ = pad;
    return pressed;
  }
  void top_tick(bool entering, bool target_pressed) {
    UObject* a = acting_member();
    if (entering || (a && a != actor_.resolve())) turn_due_ = true;
    // The wheel's Shift slides in after the turn opens (its timeline drives "Shift" 0 -> 1 once ShiftVisible(true)
    // ran): a 1 More said on the turn's first frame read it as 0, and "Shift available" went unsaid though B worked
    // (Koromaru's Maragion on a Fire-weak Devoted Cupid, 9/5, 2026-11-24). Said once it shows, while the same member
    // still holds the turn.
    if (shift_pending_) {
      UObject* top = top_.get();
      if (!a || a != last_actor_.resolve()) shift_pending_ = false;
      else if (top && get<float>(top, "Shift") > 0.5f) { shift_pending_ = false; speech::speak(strings::kShiftAvailableWords.c_str(), false); }
    }
    // The turn's target and its place are read from the turn's list. The line said before it was built had no "1 of 2"
    // on a battle's first turn, and the list appearing under it swallowed the player's first move (2026-11-05).
    UObject* g = battle_objects().gui_comp.get();
    if (!g || !get_bool(g, "IsCreateEnemyList")) return;
    UObject* t = wheel_target();
    if (a && turn_due_) {   // no acting member (between turns): nothing to say yet
      turn_due_ = false;
      // The same member acting again right after knocking an enemy down, or after the game showed its 1 More panel
      // (a weakness hit that defeated its target): the game's "1 More".
      bool again = a == last_actor_.resolve() && (downed_since_turn_ || one_more_);
      // After a 1 More the wheel shows Shift (B) once it is unlocked (BP_BtlTopUI_C "Shift" is 1 then, but it
      // stays 1 between turns too, 2026-10-28: only said with the 1 More).
      UObject* top = top_.get();
      bool shift = top && get<float>(top, "Shift") > 0.5f;
      if (again) speech::speak(shift ? std::format("{} {}", strings::kOneMore, strings::kShiftAvailableWords) : std::string(strings::kOneMore), false);
      shift_pending_ = again && !shift;
      downed_since_turn_ = false;
      one_more_ = false;
      last_actor_ = WeakObj::of(a);
      announce_top();
    }
    else if (t && t != target_.resolve()) {
      // The player moved the target: said at once, with its place (two of the same Shadow at the same health read
      // alike otherwise).
      target_ = WeakObj::of(t);
      speech::speak(target_line(t), true);
    }
    else if (t && target_pressed && screens::current() == this && !msg::current().blocking && !input::modal()) {
      // The last enemy left: the game's cursor has nowhere to go, so the press is answered with who it is still on.
      auto* l = wheel_enemies();
      if (l && l->num == 1) speech::speak(target_line(t), true);   // interrupting, like a menu's end (say_end)
    }
  }
  // ---- no wrapping (the players' call, 2026-11-09): the game's own target cursors go round (the wheel's "Target
  // Index" + 1 mod the list, BP_BtlGuiComponent 17497; Analyze's ListControll), so with two enemies nobody could tell
  // the leftmost from the rightmost. A press that would go round never reaches the game: the key is taken
  // (keys::set_capture), the button hidden (input::block_ends), and the press is answered with who the cursor is
  // still on. Which press lowers the index: the wheel's left (On Select Behind Target) and Analyze's R1 (NextTarget
  // is ListControll(false)); its L1 raises it.
  Finder analyze_{"BP_BtlGuiAnalyze_C"};
  struct Ends { bool low = false, high = false; UObject* on = nullptr; };   // the cursor is on the first / the last
  Ends ends(int st) {
    UObject* o = st == 1 ? battle_objects().gui_comp.get() : st == 8 ? analyze_.get() : nullptr;
    if (!o || (st == 1 && !get_bool(o, "IsCreateEnemyList"))) return {};   // the wheel's list is this turn's
    auto* l = field<TArray<UObject*>>(o, "EnemyList");
    int32_t* i = field<int32_t>(o, st == 1 ? "Target Index" : "TargetIndex");
    if (!l || !i || l->num < 2 || *i < 0 || *i >= l->num) return {};
    return {*i == 0, *i == l->num - 1, l->data[*i]};
  }
  // The screen that has the keys: this one, or Analyze's page over it (the same target keys).
  bool mine() {
    Screen* c = screens::current();
    bool ours = c == this || (c && std::string_view(c->id()) == "battle_analyze");
    return ours && !msg::current().blocking && !input::modal();
  }
  // Analyze's page is its own menu (battle_menus.cpp, BattleAnalyze); a press at its end says the target's line.
  std::string analyze_line(UObject* t) { return w_.analyze_name(t); }
  void say_end(int st, UObject* t) {
    // Interrupting, like a menu's end: each press says it afresh instead of queueing the name (the user's call, 2026-11-09).
    if (t) speech::speak(st == 1 ? target_line(t) : analyze_line(t), true);
  }
  bool end_key(uint32_t vk, bool repeat) {
    if (!mine()) return false;
    int st = gui_state(), step = core::target_key_step(st, vk);   // -1 lowers the game's index, +1 raises it
    if (!step) return false;
    Ends e = ends(st);
    if (!(step < 0 ? e.low : e.high)) return false;
    if (!repeat) say_end(st, e.on);
    return true;
  }
  uint16_t end_pad_was_ = 0, end_hidden_was_ = 0;
  void end_pad(int st) {
    Ends e = mine() ? ends(st) : Ends{};
    uint16_t hide = 0;
    int sticks = 0;
    if (st == 1) {
      if (e.low) { hide |= XINPUT_GAMEPAD_DPAD_LEFT; sticks |= 1; }
      if (e.high) { hide |= XINPUT_GAMEPAD_DPAD_RIGHT; sticks |= 2; }
    } else if (st == 8) {
      if (e.low) hide |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
      if (e.high) hide |= XINPUT_GAMEPAD_LEFT_SHOULDER;
    }
    input::block_ends(hide, sticks);
    uint16_t pad = input::layer_open() ? 0 : input::real_buttons() & (XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT |
                                                                        XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER);
    // Only a press the game never got: its button was already hidden when it came. The press that brought the cursor
    // to this end was the game's, and the move says itself (both spoke: every target was sent twice, 2026-11-10).
    if (pad & ~end_pad_was_ & hide & end_hidden_was_) say_end(st, e.on);
    end_pad_was_ = pad;
    end_hidden_was_ = hide;
  }
  int bg_state_ = -1;
  // Said the current prompt (state 5 / 11): set when it is said, cleared when the game's state changes. The All-Out
  // state lasts through Shuffle Time and the results, so coming back to this screen is no new prompt.
  bool prompt_said_ = false;

 public:
  BattleScreen() {
    battle_objects();   // the battle's objects are watched for from the start, not from the first battle
    keys::set_capture([this](uint32_t vk, bool repeat) { return end_key(vk, repeat); });
  }
  const char* id() const override { return "battle"; }
  // The All-Out and guard prompts and Analyze answer C (Cancel); on the command wheel C is Guard (and so is the
  // game's own Escape there, left to it).
  bool escape_is_back() override { int st = gui_state(); return st == 5 || st == 8 || st == 11; }
  int priority() const override { return 25; }
  bool active() override { return gui_state() != 0; }
  void enter() override { state_ = -1; }
  // Results are watched for as long as a battle exists, not only while a menu is up: the last blow ends the menus.
  void background() override {
    bool target_pressed = target_press();
    UObject* core = battle_core();
    end_pad(core ? gui_state() : 0);
    if (!core) { units_.clear(); won_enemies_.clear(); forget_battle_start(); downed_since_turn_ = false; one_more_ = false; shift_pending_ = false; last_actor_ = {}; rush_ = false; popups_seen_.clear(); helps_said_.clear(); fled_.clear(); hits_.clear(); hits_by_ = {}; popped_.clear(); popped_by_ = {}; popped_by_ = {}; countdown_on_ = false; return; }
    watch();
    countdown_tick(core);
    int st = gui_state();
    // Assist (13, BTL_STATE_NAVIGATION) only plays the navigator's advice over the wheel: back from it is the same
    // turn, not the wheel opening again (each press re-read the turn line, 2026-11-01).
    bool entering = st != bg_state_ && bg_state_ != 13;
    // The mod loaded into a battle already in the All-Out state (a hot reload): that state lasts through Shuffle Time
    // and the results, so it is taken as answered (the prompt was said again after Shuffle Time, 2026-11-09).
    bool loaded_into = bg_state_ == -1 && st == 5;
    bg_state_ = st;
    if (entering) prompt_said_ = loaded_into;
    if (st == 1) top_tick(entering, target_pressed);
    else turn_due_ = false;
  }
  void tick() override {
    int st = gui_state();
    bool entering = st != state_;
    state_ = st;
    switch (st) {
      case 1:   // TOP: the game's keys run the commands; the turn is read in background()
        if (entering) screens::set_keys([this] { return top_keys(); });
        break;
      // 2 skills, 3 items, 4 targets, 6 Survey, 7 Theurgy, 9 Shift, 10 Tactics: bespoke menus (battle_menus.cpp);
      // 12 the Persona status page (persona_status.cpp)
      // 5 All-Out Attack, 11 guard confirmation: button prompts with no cursor (BP_BtlPromiseCommon, BP_BtlGuard bind
      // only TrigOK / TrigCANCEL), so the game's own keys answer them; the question is said once with its two buttons
      // (the player's call, 2026-11-01: a prompt's buttons are its content, not a hint).
      case 5: {
        if (prompt_said_) break;
        // The All-Out state lingers into Shuffle Time and the results: not a prompt then.
        if (shuffle_ui() || result_phase()) break;
        prompt_said_ = true;
        screens::set_keys(strings::kAllOutKeys);
        speech::speak(std::format("{} {}", strings::kAllOutTitle, strings::kAllOutKeys()), true);
        break;
      }
      case 11:
        if (prompt_said_) break;
        prompt_said_ = true;
        screens::set_keys(strings::kGuardKeys);
        speech::speak(std::format("{} {}", strings::kGuardTitle, strings::kGuardKeys()), true);
        break;
      // 8 Analyze: its own page (BattleAnalyze) once the screen's component is made; nothing is said before.
      default: break;
    }
  }
  std::string describe() override {
    UObject* a = acting_member();
    UObject* t = wheel_target();
    std::string s = a ? std::format("{}. {}", w_.unit_name(a), w_.hp_sp(a)) : std::string(strings::kBattle);
    if (t) s += std::format(". {} {}", strings::kTarget, target_line(t));
    return s;
  }
};

std::unique_ptr<Screen> make_battle() { return std::make_unique<BattleScreen>(); }
}  // namespace p3a::screens
