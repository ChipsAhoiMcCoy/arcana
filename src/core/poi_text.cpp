#include "core/poi_text.h"
#include <algorithm>
#include "core/strings.h"
#include <cctype>
#include <cmath>
#include <format>
#include <map>
#include <set>

namespace p3a::core {

int clock_hour(float b) {
  int h = (int)std::lround(b / 30.0f);
  if (h <= 0) h += 12;
  return h;
}

int compass_point(float b) {
  return ((int)std::lround(b / 45.0f) % 8 + 8) % 8;
}

std::vector<std::string> name_parts(const std::string& n) {
  std::vector<std::string> tok;
  for (size_t s = 0; s <= n.size();) { size_t e = n.find('_', s); if (e == std::string::npos) e = n.size(); tok.push_back(n.substr(s, e - s)); s = e + 1; }
  return tok;
}

std::string person_from_actor_name(const std::string& actor_name) {
  static const std::map<std::string, std::string> cast = {
    {"Yukari", "Yukari"}, {"Junpei", "Junpei"}, {"Mituru", "Mitsuru"}, {"Sanada", "Akihiko"}, {"Fuka", "Fuuka"},
    {"Aegis", "Aigis"}, {"Koromaru", "Koromaru"}, {"Ken", "Ken"}, {"Amada", "Ken"}, {"Shinjiro", "Shinjiro"}, {"Aragaki", "Shinjiro"},
    {"Ikutsuki", "Ikutsuki"}, {"Elizabeth", "Elizabeth"}, {"Igor", "Igor"}, {"Pharos", "Pharos"},
  };
  // FldNpcActor_105_102_Yukari_6 -> the first token after the field ids
  std::vector<std::string> tok = name_parts(actor_name);
  for (auto& t : tok) { auto it = cast.find(t); if (it != cast.end()) return it->second; }
  // The first word after the class (FldNpcActor_Jin has no field ids at all: Adamah, 2026-10-28).
  for (size_t i = 1; i < tok.size(); ++i) if (!tok[i].empty() && !isdigit((unsigned char)tok[i][0])) return tok[i];
  return {};
}

std::string story_scene(const std::string& actor_name) {
  std::vector<std::string> tok = name_parts(actor_name);
  if (tok.size() < 4 || tok[0] != "FldHitActor" || tok[1].empty() || !isdigit((unsigned char)tok[1][0])) return {};
  const std::string& w = tok[2];
  if (w.size() < 2 || !isalpha((unsigned char)w[0]) || (w[0] == 'H' && isdigit((unsigned char)w[1]))) return {};
  return w;
}

bool story_start(const std::string& overlap_class) { return overlap_class.ends_with("_H0_Play_C"); }

bool dead_hit(const std::string& overlap_class) {
  return overlap_class == "BP_FldHitActor_102_102_Shadow_H7_Play_C" || overlap_class == "BP_FldHitActor_302_102_H12_Play_C";
}

bool boss_trigger(const std::string& overlap_class) {
  static const std::set<std::string> bosses = {
    "BP_FldAreaChange_302_102_H24_Play_C",   // 5/9, the monorail
    "BP_FldHitActor_103_101_Shadow_H0_Play_C",   // 9/5, Club Escapade's door (named: says it after its name)
    "BP_FldHitActor_105_102_Shadow_H0_Play_C",   // 10/4, the way to Iwatodai Station's plaza (named)
    "BP_FldHitActor_299_267_H0_Play_C",      // 6/8, Fuuka's rescue in Tartarus
    "BP_FldHitActor_304_101_H24_Play_C",     // 7/7, the hotel
    "BP_FldHitActor_305_101_H17_Play_C",     // 8/6, the base
    "BP_FldHitActor_308_101_H0_Play_C",      // 11/3, the Moonlight Bridge
  };
  return bosses.count(overlap_class) > 0;
}

bool stairs(const std::string& actor_name, int& from, int& to) {
  std::vector<std::string> tok = name_parts(actor_name);
  if (tok.size() < 4 || tok[0] != "FldHitActor" || tok[1] != "304" || tok[2] != "101") return false;
  static const std::map<std::string, std::pair<int, int>> hotel = {{"H0", {1, 2}}, {"H1", {2, 1}}, {"H2", {2, 3}}, {"H3", {3, 2}}};
  auto it = hotel.find(tok[3]);
  if (it == hotel.end()) return false;
  from = it->second.first;
  to = it->second.second;
  return true;
}

bool numbered_name(const std::string& flag, std::string& base, int& number) {
  size_t us = flag.find_last_of('_');
  if (us == std::string::npos || us + 1 >= flag.size() || flag.size() - us > 10 ||
      flag.find_first_not_of("0123456789", us + 1) != std::string::npos || (flag[us + 1] == '0' && us + 2 != flag.size()))
    return false;
  base = flag.substr(0, us);
  number = std::stoi(flag.substr(us + 1)) + 1;
  return true;
}

// The game marks nearly every hit with the plain Check icon: a business's door (Be Blue V, the police station, Hagakure
// Ramen) and a classroom's look exactly like a bookshelf; only the Net Cafe and Umiushi carry the Shop icon. Their
// scripts tell them apart (HIT_SKILL_SHOP, HIT_POLICE_ENTER, CALL_PUBLIC_SHOP; FLD_OPEN_ORD_DOOR_FADE for a room), so
// these lists sort the Check hits by their name's row (mNameIndex_, KIN_<n> of DT_FldDailyHitName and
// DT_FldDungeonHitName; surveyed from every field level's hits and their BF_OBJ flowscripts, 2026-10-31). By row, not
// by the name: the names are in the game's language (2026-11-23). Every row bearing one of these names in the English
// tables, the main story's and Episode Aigis's; no row of either means anything else.
CheckKind check_kind(int name_index) {
  // Somewhere to buy, eat, work or spend time: a business's entrance, a vendor, a vending machine. The rows named
  // Ramen Shop, Vending Machine, Chagall Café, Be Blue V, Police Station, Mandragora, Mayoido Antiques, Aohige
  // Pharmacy, Kenneth Arnold, Game Parade, Screen Shot, Ticket Booth, Café, Mahjong Parlor Red Hawk, Que Sera Sera,
  // Wilduck Burger, Azuki Arai Sweets, Hagakure Ramen, Wakatsu Kitchen, Net Café, Umiushi Beef Bowls, Bookworms,
  // Souvenir Sweets, Kyoto Souvenirs, Kyoto Crafts, Hamburger Shop, Used Bookstore, Takoyaki Vendor, Mystery Vending
  // Machine, Mayoido, Octopia
  static constexpr int kShops[] = {
    2, 2102003, 3101002, 3101003, 3101004, 3101005, 3101006, 3101007, 3101008, 3101009, 4101001, 4101003, 4101008,
    4101010, 4102001, 4102002, 5101001, 5102101, 5102201, 5102202, 5102203, 5102204, 5102205, 5102206, 5102505,
    8101105, 8101106, 8101109, 8101202, 10001006, 10002000, 10002007, 10002009, 10002010, 10003018, 10003019,
    10006001, 10006002, 10006004, 10006005, 10006006, 10006007, 10006008, 10006010, 10007001, 10007002, 10007003,
    10007004, 10007006, 10007007, 10007008, 10007010,
  };
  // A room's door you check to go in (or find locked): classrooms, offices, restrooms, the dorm's bedrooms, the
  // school's stairs (a Check hit, HIT_SECOND_FLOOR_STAIRS). The rows named
  // Classroom Door, School Building 3F, Command Room, Men's Room, Women's Room, Faculty Office, Library, Nurse's
  // Office, Laboratory, Janitor's Room, Welfare Training Room, Printing Room, Home Ec Prep Room, Music Prep Room,
  // School Building 2F, Classroom 2-E, Emergency Exit, PA Room, Computer Room, Student Council Room, Art Room,
  // Science Room, Music Room, Home Economics Room, Locked Gate, Practice Field, Gym, Indoor Swimming Pool, Storage
  // Room, Rear Entrance, Kitchen Door, Storeroom, Sanada's Room, Vacant Room, His Room, Junpei's Room, Amada's Room,
  // Mitsuru's Room, Yukari's Room, Fuuka's Room, Large Door, Rooftop Storage, Door to Velvet Room, Restroom, Inn
  // Exit, Hot Spring, Fuji Room, Bathroom, Metal Doors
  static constexpr int kDoors[] = {
    1, 113100, 214100, 1102001, 1102002, 1102102, 1102103, 1102104, 1102107, 1102108, 1102110, 1102111, 1102112,
    1102113, 1102114, 1102201, 1102202, 1102203, 1102204, 1102504, 1102510, 1102511, 1102512, 1102514, 1103005,
    1103507, 1103508, 1103509, 1141003, 2102001, 2102002, 2102101, 2102110, 2102114, 2102202, 2102203, 2102204,
    2102205, 2102220, 2102221, 2102222, 2102301, 2102302, 2102303, 2102304, 2102305, 2102320, 2102402, 2102420,
    2141003, 2151002, 3101012, 3111001, 4101002, 8101002, 8101101, 8101102, 8101201, 10000108, 10001000, 10001002,
    10001003, 10001004, 10003023, 10003027, 10005000, 10008002,
  };
  if (std::ranges::binary_search(kShops, name_index)) return CheckKind::Shop;
  if (std::ranges::binary_search(kDoors, name_index)) return CheckKind::Door;
  return CheckKind::Thing;
}

// The NPC scripts that open a shop (CALL_PUBLIC_SHOP, SEL_GENERIC_SHOP; surveyed from every BF_NPC flowscript,
// 2026-11-16): 100 School Store Vendor, 101 Flower Shop Lady, 102 6HARA Clerk, 103 Octopia (all four carry the Shop
// icon), 104 Luxury Shopkeeper, 105 Suspicious Man, 404 Fortune-Teller (a Speak icon). Their event-day variants
// (700) say the stall is shut, except Octopia's at the shrine on New Year's (kfev550, HIT_TAKOYAKI_SHOP_NEWYEAR).
bool npc_sells(int major, int minor, std::string_view level) {
  if (minor == 0) return (major >= 100 && major <= 105) || major == 404;
  return major == 103 && minor == 700 && level.ends_with("_Event_550");
}

// Surveyed from every map's placed NPCs (2026-11-18): of 780 with a name index, 586 point at their major's row. Of
// those without one, every field-level NPC whose major has a row is that character (Officer Kurosawa outside the
// Paulownia Mall police station, Mitsuru / Junpei / Akihiko on event days, the bartender); the backdrops of the shop
// and Velvet Room menus (LV_WeaponShop, LV_VelvetRoom) borrow ids whose rows are someone else (Octopia, Ms. Toriumi).
std::vector<int> npc_name_rows(int name_index, int major, int minor, std::string_view level) {
  std::vector<int> rows;
  if (name_index >= 0) rows.push_back(name_index);
  bool field = level.size() > 4 && level.starts_with("LV_F") && isdigit((unsigned char)level[4]);
  if (field && major > 0 && major < 100000) {
    if (minor > 0 && minor < 1000) rows.push_back(major * 1000 + minor);
    rows.push_back(major * 1000);
  }
  return rows;
}

// The questions are fixed, always in this order (BF_Scr_Event_fild_390_001_C: four SELs, no randomness). Each one's
// answer is that customer's last word on their order, and the NPCs' places agree (683 farthest from the door, 684
// nearest it, 685 mid-floor; measured 2026-11-21). Matched on the words that place them, so a reworded line after an
// update names nobody rather than the wrong one.
int bar_customer_asked(std::string_view line) {
  if (line.find("girl standing by the table in the back") != std::string_view::npos) return 683;
  if (line.find("girl by the entrance") != std::string_view::npos) return 684;
  if (line.find("girl in the middle of the floor") != std::string_view::npos) return 685;
  if (line.find("that guy over there") != std::string_view::npos && line.find("What does he want") != std::string_view::npos) return 686;
  return 0;
}

const char* bar_customer_place(int major, int minor) {
  if (minor != 700) return nullptr;
  switch (major) {
    case 683: return strings::kBarPlaceBack;
    case 684: return strings::kBarPlaceEntrance;
    case 685: return strings::kBarPlaceMiddle;
    default: return nullptr;
  }
}

std::string chest_name(const std::string& type, const std::string& game_name) {
  if (type == "TBoxRare") return strings::kPoiChestRare.c_str();
  if (type == "TBoxJewelry") return strings::kPoiChestGold.c_str();
  int cost = type == "TBoxMedal1" ? 1 : type == "TBoxMedal2" ? 2 : type == "TBoxMedal3" ? 3 : 0;
  if (cost) return std::format("{}, {}", strings::kPoiChestLocked, strings::count(cost, strings::kPoiFragment, strings::kPoiFragments));
  return game_name;
}

bool is_named(const std::string& poi_name, const std::string& label) {
  return poi_name == label || (poi_name.size() > label.size() + 2 && poi_name.starts_with(label) &&
                               poi_name.compare(label.size(), 2, " (") == 0);
}

// The hit-name rows whose name says what you do ("Proceed Onward", "Enter the Velvet Room", "To furthest floor"): by
// row, as the names are in the game's language (2026-11-23). Every row of the English tables (main story and Episode
// Aigis) whose Name, or whose Name2 (shown while the row's story flag is on), starts with Go, Head, Return, Proceed,
// Enter, Exit or To.
bool named_as_action(int name_index, bool name2_shown) {
  // Enter Door, Enter the Velvet Room, Exit Door, Go Back, Go Elsewhere, Go elsewhere, Head Downstairs, Head Up, Head Upstairs, Proceed Onward, Return to Dorm, Return to Entrance, Return to the Desert of Doors, To furthest floor
  static constexpr int kName[] = {
    900000, 900001, 3101030, 10000001, 10001007, 10001008, 10002012, 10009002, 10009005, 10009006, 10009007,
    10009008, 10009009, 10009012, 10009017, 10009033, 10009037,
  };
  // Go to Another Floor, Go to Tartarus, Head to the Dorm, Return to Dorm, Return to the Desert of Doors
  static constexpr int kName2[] = {
    2102108, 2102150, 10002012, 10009003, 10009031,
  };
  return name2_shown ? std::ranges::binary_search(kName2, name_index) : std::ranges::binary_search(kName, name_index);
}

int settle_category(int current, int n, int delta, bool move, const std::function<bool(int)>& has_any) {
  for (int step = move ? 1 : 0; step <= n; ++step) {
    int c = ((current + step * delta) % n + n) % n;
    if (has_any(c)) return c;
  }
  return -1;
}

bool same_thing(const std::string& name_a, const Vec3& a, const std::string& name_b, const Vec3& b) {
  return name_a == name_b && std::fabs(a.x - b.x) + std::fabs(a.y - b.y) + std::fabs(a.z - b.z) < 150.0f;
}

std::vector<size_t> near_sides(const std::vector<Place>& sorted) {
  std::vector<size_t> kept;
  for (size_t i = 0; i < sorted.size(); ++i) {
    const Place& p = sorted[i];
    bool far_side = false;
    if (p.exit)
      for (size_t k : kept)
        if (sorted[k].exit && sorted[k].name != p.name &&
            std::hypot(sorted[k].at.x - p.at.x, sorted[k].at.y - p.at.y, sorted[k].at.z - p.at.z) < 200.0f) far_side = true;
    if (!far_side) kept.push_back(i);
  }
  return kept;
}

const char* icon_state(std::string_view kind) {
  if (kind == "Talk") return strings::kIconTalk;
  if (kind == "Listen") return strings::kIconListen;
  if (kind == "Talk_Read") return strings::kIconTalked;
  if (kind == "Listen_Read") return strings::kIconHeard;
  if (kind == "Commu" || kind == "Commu_Field") return strings::kIconLink;
  if (kind == "Commu_Reverse") return strings::kIconLinkReversed;
  if (kind == "DormitoryLife") return strings::kIconHangout;
  if (kind == "MaleQuest" || kind == "MaleQuest_Field") return strings::kIconEpisode;
  if (kind == "Quest") return strings::kIconRequest;
  if (kind == "StudyGroup") return strings::kIconStudy;
  if (kind == "Walking") return strings::kIconWalk;
  // The handwritten word icons (BP_UI_Handwriting_<kind>_C): a crowd's buzz and people whispering, overheard.
  if (kind == "Buzz_00") return strings::kIconBuzz;
  if (kind == "Whisper_00") return strings::kIconWhisper;
  if (kind == "Buzz_Read_00" || kind == "Whisper_Read_00") return strings::kIconHeard;
  return "";
}

std::string icon_kind(std::string_view class_name) {
  constexpr std::string_view head = "BP_UI_AccessIcon_", tail = "_C";
  if (class_name.size() <= head.size() + tail.size() || !class_name.starts_with(head) || !class_name.ends_with(tail)) return {};
  return std::string(class_name.substr(head.size(), class_name.size() - head.size() - tail.size()));
}

}  // namespace p3a::core
