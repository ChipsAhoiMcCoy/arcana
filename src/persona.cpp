// Persona data and the hero's stock. Names: UDatPersonaNameTable.Data[id].Name (FText); arcana and base level:
// UDatPersonaTable.Data[id] (FDatPersonaDataRecord, 0xE bytes: +2 Race, +3 Level). The stock: UGlobalWork +0x1B0 is
// FDatUnitWork[11] (0x2B4 each; the hero is unit 1, ID 1), +0x48 FDatUnitPersona {u16 equip, entries of 0x30 from +4:
// +0 flags (1 = filled), +2 id, +4 level, +0xC skills u16[8], +0x1C St Ma En Ag Lu} (p3rpc.nativetypes; measured
// 2026-10-27: Orpheus 3 and Apsaras 2).
#include "persona.h"
#include "bmdfile.h"
#include "core/affinity.h"
#include "dat.h"
#include "core/strings.h"
#include "devserver.h"
#include "party.h"
#include "seh.h"
#include "social.h"
#include "ue/scan.h"
#include "ue/ue.h"
#include "watch.h"
#include <windows.h>
#include <algorithm>
#include <cstring>
#include <format>
#include <memory>

namespace p3a::persona {
using namespace ue;

// The data assets below come from the object watcher (a class wanted for the first time is filled by one sweep, so
// an asset loaded long before is found; after that no lookup scans the objects).
static UObject* dat() {
  static const int id = watch::want("DatPersona");
  return watch::get(id);
}

std::string name(int id) {
  UObject* d = dat();
  UObject* t = d ? get<UObject*>(d, "TableName") : nullptr;
  auto* rows = t ? field<TArray<FText>>(t, "Data") : nullptr;   // FDatPersonaName is one FText
  if (!rows || id <= 0 || id >= rows->num) return {};
  std::string s;
  guarded([&] { s = text(rows->data[id]); });
  return s;
}

static const uint8_t* record(int id) {
  UObject* d = dat();
  UObject* t = d ? get<UObject*>(d, "TablePersona") : nullptr;
  auto* rows = t ? field<TArray<uint8_t>>(t, "Data") : nullptr;
  if (!rows || id <= 0 || id >= rows->num) return nullptr;
  return rows->data + id * 0xE;
}
// Affinities: UDatAffinityTable (DatPersonaAffinityDataAsset) Data[id] = u16 attr[19], 38 bytes a row: the slots
// and kinds are core/affinity's (tested there: 8 Light, 9 Dark).
std::string affinities(int id) {
  std::string out;
  for (auto& g : affinity_groups(id)) out += (out.empty() ? "" : ", ") + g;
  return out;
}

// The enemies' table (DatEnemyAffinityDataAsset, 601 rows) has the same class, and Episode Aigis has its own copy of
// both: the Persona table is taken by its name and story (dat::find), never the newest of the class (a battle loads
// the enemies' one, and Omoikane, row 62, read the enemy row's null Strike and Fire, drain Elec, repel Dark; a
// player's report, 2026-11-17).
static const uint16_t* affinity_row(int id) {
  static const int table_id = watch::want("DatAffinityTable", true);
  UObject* t = dat::find(table_id, "DatPersonaAffinityDataAsset");
  auto* rows = t ? field<TArray<uint8_t>>(t, "Data") : nullptr;
  if (!rows || id <= 0 || id >= rows->num) return nullptr;
  return (const uint16_t*)(rows->data + id * core::kAffinitySlotsInRow * 2);
}

std::vector<std::string> affinity_groups(int id) {
  std::vector<std::string> out;
  if (const uint16_t* a = affinity_row(id)) guarded([&] { out = core::affinity_groups(a); });
  return out;
}

std::vector<std::string> affinity_lines(int id) {
  std::vector<std::string> out;
  if (const uint16_t* a = affinity_row(id)) guarded([&] { out = core::affinity_lines(a); });
  return out;
}

int arcana(int id) { const uint8_t* r = record(id); return r ? r[2] : 0; }   // Race 1 = Fool
int base_level(int id) { const uint8_t* r = record(id); return r ? r[3] : 0; }

static uint8_t* hero_personas() {
  uint8_t* u = party::unit_work(1);
  return u ? u + 0x48 : nullptr;
}

std::vector<Owned> stock() {
  std::vector<Owned> out;
  uint8_t* p = hero_personas();
  if (!p) return out;
  guarded([&] {
    for (int i = 0; i < 12; ++i) {
      uint8_t* e = p + 4 + i * 0x30;
      if (!(*(uint16_t*)e & 1)) continue;
      Owned o{i, *(uint16_t*)(e + 2), *(uint16_t*)(e + 4), {}, {}};
      memcpy(o.skills, e + 0xC, sizeof o.skills);
      memcpy(o.stats, e + 0x1C, sizeof o.stats);
      if (o.id > 0) out.push_back(o);
    }
  });
  return out;
}

int unit_level(int unit_id) {
  uint8_t* u = unit_id == 1 ? party::unit_work(unit_id) : nullptr;   // the other members keep their level elsewhere (+0x1C reads 1 for them)
  if (!u) return 0;
  int lv = 0;
  guarded([&] { lv = *(int16_t*)(u + 0x1C); });
  return lv;
}

int equipped() {
  uint8_t* p = hero_personas();
  int v = -1;
  if (p) guarded([&] { v = *(uint16_t*)p; });
  return v;
}

// The game's help line for a skill, from its file (BMD_SkillHelp, dialog = the skill id) rather than the drawn page:
// the game builds that page once per highlight, so a drawn-page read came up empty after a second or on a reused page.
std::string skill_help(int id) {
  auto f = bmdfile::load("BMD_SkillHelp");
  if (!f || !f->ok || id < 0 || id >= (int)f->dialogs.size() || f->dialogs[id].pages.empty()) return {};
  return bmdfile::text(f->dialogs[id].pages[0]);
}
std::string skill_name(int id) {
  static const int table_id = watch::want("DatSkillNameTable", true);
  UObject* t = dat::find(table_id, "DatSkillNameDataAsset");
  auto* rows = t ? field<TArray<FText>>(t, "Data") : nullptr;
  if (!rows || id <= 0 || id >= rows->num) return {};
  std::string s;
  guarded([&] { s = text(rows->data[id]); });
  return s;
}

bool skill_passive(int id) {
  static const int table_id = watch::want("DatSkillTable", true);
  UObject* t = dat::find(table_id, "DatSkillDataAsset");
  if (!t) return false;
  TableRows rows = table_rows(t);
  if (!rows || id <= 0 || id >= rows.num) return false;
  int oType = offset_of(rows.row, "Type");
  if (oType < 0) return false;
  bool passive = false;
  guarded([&] { passive = rows.at(id)[oType] == 1; });
  return passive;
}

std::string skill_cost(int id) {
  static const int table_id = watch::want("DatSkillNormalTable", true);
  UObject* t = dat::find(table_id, "DatSkillNormalDataAsset");
  if (!t) return {};
  TableRows rows = table_rows(t);
  if (!rows || id <= 0 || id >= rows.num) return {};
  int oType = offset_of(rows.row, "costtype"), oCost = offset_of(rows.row, "cost");
  if (oType < 0 || oCost < 0) return {};
  std::string s;
  guarded([&] {
    const uint8_t* r = rows.at(id);
    int type = r[oType], cost = *(uint16_t*)(r + oCost);
    if (type == 1 && cost) s = std::format("{}% {}", cost, strings::kHP);
    else if (type == 2 && cost) s = std::format("{} {}", cost, strings::kSP);
  });
  return s;
}

int stat_total(const uint8_t* e, int i) {
  if (!e || i < 0 || i > 4) return 0;
  int v = 0;
  guarded([&] { v = e[0x1C + i] + e[0x21 + i] + e[0x26 + i]; });
  return v > 99 ? 99 : v;
}

// The total EXP an entry needs for a level: exe+0x1204000(entry, level) (0 below level 2; ally Personas, ids 1..0x22,
// from their unit's table, the rest from a curve; the base of FDatUnitPersona::CalculateBonusExp, exe+0x1563220).
int exp_for_level(const uint8_t* e, int level) {
  if (!e || level < 2 || !ue::known_build()) return 0;
  int v = -1;
  guarded([&] { v = ((int (*)(const void*, uint16_t))(scan::exe_base() + 0x1204000))(e, (uint16_t)level); });
  return v;
}

int exp_to_next(const uint8_t* e) {
  int level = e ? *(const uint16_t*)(e + 4) : 99;
  if (level >= 99) return -1;
  int need = exp_for_level(e, level + 1);
  return need < 0 ? -1 : std::max(0, need - (int)*(const uint32_t*)(e + 8));
}

int level_with_exp(const uint8_t* e, int gain) {
  int level = e ? *(const uint16_t*)(e + 4) : 0;
  if (!e || gain <= 0) return level;
  int64_t total = (int64_t)*(const uint32_t*)(e + 8) + gain;
  while (level < 99) {
    int need = exp_for_level(e, level + 1);
    if (need <= 0 || need > total) break;
    ++level;
  }
  return level;
}

std::vector<std::string> detail_lines(const uint8_t* e) {
  std::vector<std::string> out;
  int id = e ? *(const uint16_t*)(e + 2) : 0;
  if (name(id).empty()) return out;
  for (int i = 0; i < 5; ++i) out.push_back(std::format("{} {}", strings::kStatNames[i], stat_total(e, i)));
  for (int i = 0; i < 8; ++i)
    if (int sid = *(const uint16_t*)(e + 0xC + i * 2)) {
      std::string l = skill_name(sid), cost = skill_cost(sid);
      out.push_back(cost.empty() ? l : l + ", " + cost);
    }
  for (auto& l : affinity_lines(id)) out.push_back(l);
  return out;
}

const uint8_t* stock_entry(int slot) {
  uint8_t* p = hero_personas();
  return p && slot >= 0 && slot < 12 ? p + 4 + slot * 0x30 : nullptr;
}

std::vector<Learn> learnset(int id) {
  std::vector<Learn> out;
  UObject* d = dat();
  UObject* t = d ? get<UObject*>(d, "TableGrowth") : nullptr;
  TableRows rows = table_rows(t);
  if (!rows || id <= 0 || id >= rows.num) return out;
  int ev = offset_of(rows.row, "skillEvent"), base = base_level(id);
  if (ev < 0) return out;
  guarded([&] {
    const uint8_t* r = rows.at(id) + ev;
    for (int i = 0; i < 16; ++i, r += 6)
      if (int sk = *(const uint16_t*)(r + 4)) out.push_back({base + r[0], sk});
  });
  return out;
}

std::string status_line(const uint8_t* e) {
  std::string s;
  guarded([&] {
    int id = *(uint16_t*)(e + 2), level = *(uint16_t*)(e + 4);
    if (!id) return;
    s = describe(id, level);
    for (int i = 0; i < 5; ++i) s += std::format(", {} {}", strings::kStatAbbrev[i], stat_total(e, i));
    std::string sk;
    for (int i = 0; i < 8; ++i)
      if (int sid = *(uint16_t*)(e + 0xC + i * 2)) sk += (sk.empty() ? "" : ", ") + skill_name(sid);
    if (!sk.empty()) s += std::string(". ") + strings::kSkills + ": " + sk;
    if (std::string af = affinities(id); !af.empty()) { af[0] = (char)toupper((unsigned char)af[0]); s += ". " + af; }
  });
  return s;
}

const uint8_t* status_entry(UObject* ps) {
  UObject* draw = ps ? get<UObject*>(ps, "pPersonaStatusDraw") : nullptr;
  return draw ? (const uint8_t*)draw + 0x34C : nullptr;
}
bool status_page_up(UObject* ps) { return ps && *(int32_t*)((uint8_t*)ps + 0x528) == 1; }   // 2 once closed
const uint8_t* shown_status() {
  static const int status_id = watch::want("PersonaStatus");   // absent outside its screen: no scan per call
  return status_entry(watch::get(status_id));
}

std::string describe(int id, int level) {
  return std::format("{}, {}, {} {}", name(id), social::arcana_name(arcana(id)), strings::kLevel, level);
}

void install() {
  // Wanted before the first tick, so that tick's one sweep fills them with every other class's.
  watch::want("DatPersona");
  // Every copy (the enemies' affinities, Episode Aigis's tables): dat::find picks.
  for (const char* c : {"DatSkillNameTable", "DatSkillNormalTable", "DatAffinityTable"}) watch::want(c, true);
  dev::route("/persona", [](const dev::Request& r, int&) {
    // /persona the hero's stock | ?id=N one Persona's data
    int id = (int)dev::arg_int(r, "id", -1);
    std::string find = dev::arg(r, "find");
    bool learn = dev::has(r, "learn"), levelup = dev::has(r, "levelup");
    return dev::on_game([id, find, learn, levelup] {
      if (!find.empty()) {
        for (int i = 1; i < 600; ++i) if (name(i) == find) return std::format("{} {}\n", i, find);
        return std::string("not found\n");
      }
      if (id == 0) {   // ?id=0: every Persona (id race level flag name)
        std::string s;
        for (int i = 1; i < 600; ++i) {
          const uint8_t* rec = record(i);
          if (!rec) break;
          s += std::format("{} {} {} {:#x} {}\n", i, rec[2], rec[3], *(uint16_t*)rec, name(i));
        }
        return s;
      }
      if (id >= 0) return std::format("{} {} arcana {} base level {}; skill {}; {}\n", id, name(id), arcana(id), base_level(id), skill_name(id), affinities(id));
      if (levelup) {   // ?levelup=1: the equipped Persona one EXP short of its next level (dev: a skill change roll)
        auto* e = (uint8_t*)stock_entry(equipped());
        int pid = e ? *(uint16_t*)(e + 2) : 0, level = e ? *(uint16_t*)(e + 4) : 0;
        int need = e ? exp_for_level(e, level + 1) : 0;
        if (need <= 0) return std::string("no next level\n");
        *(uint32_t*)(e + 8) = (uint32_t)(need - 1);
        return std::format("{} EXP {}: level {} next\n", name(pid), need - 1, level + 1);
      }
      if (learn) {   // ?learn=1: the equipped Persona one EXP short of the level of its next skill (dev: the victory
                     // screen's skill-learned status page)
        auto* e = (uint8_t*)stock_entry(equipped());
        int pid = e ? *(uint16_t*)(e + 2) : 0, level = e ? *(uint16_t*)(e + 4) : 0;
        for (auto& l : learnset(pid)) {
          if (l.level <= level) continue;
          int need = exp_for_level(e, l.level);
          if (need <= 0) break;
          *(uint32_t*)(e + 8) = (uint32_t)(need - 1);
          return std::format("{} EXP {}: learns {} at level {}\n", name(pid), need - 1, skill_name(l.skill), l.level);
        }
        return std::string("no skill left to learn\n");
      }
      std::string s = std::format("equipped slot {}\n", equipped());
      for (auto& o : stock()) s += std::format("  slot {} id {} {}\n", o.slot, o.id, describe(o.id, o.level));
      return s;
    });
  }, "the hero's Persona stock | ?id=N one Persona | ?learn=1 the equipped one 1 EXP short of its next skill | ?levelup=1 of its next level (dev)");
}
}  // namespace p3a::persona
