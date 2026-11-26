// The points of interest around the hero: the scan every list, sound and prompt reads, and the module's tick.
// Read here:
//  - AFldHitCore (every hit actor on a visible level): mCheckIcon_, mType_ (Normal / AreaChange), mNameIndex_,
//    mKeyPushBluePrint_ / mOverlapBluePrint_ (an unnamed box with only an overlap blueprint is a trigger), and the
//    flags that retire it: mExecutedFlagName_, mOffFlagName_, mIgnoreFlagName_.
//  - AFldNpcActor: bHidden, Children, mNpcBaseClass_ / mCharaBaseClass_ (a placeholder has none of them),
//    mCharaModelList_ (empty: no character stands there), mIconActor_ (the game's talk icon: someone is, a body or not).
//  - AFldDungeonObjectActor: ObjType and m_pHitActorList (a chest's kind for its hit), Box (a breakable's body).
//  - UFldDungeonMissingController.m_pMissingPerson, +0x108 / +0x168 (its case: missing_name); AEnemySymbolBaseCore
//    (the roaming Shadows) with the enemy manager's holders (shadow::enemy_holders).
#include "poi_internal.h"
#include "bmdfile.h"
#include "dat.h"
#include "core/path_rules.h"
#include "core/poi_text.h"
#include "core/strings.h"
#include "core/text_clean.h"
#include "party.h"
#include "devserver.h"
#include "doors.h"
#include "hooks.h"
#include "floors.h"
#include "msg.h"
#include "screens/screen.h"
#include "seh.h"
#include "settings.h"
#include "shadow.h"
#include "sight.h"
#include "social.h"
#include "world.h"
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <format>
#include <map>
#include <memory>

namespace p3a::poi {
using namespace ue;

// A thing's sound, its distance and its direction come from its body's point nearest the hero, so a long counter or a
// wide exit is where its near part is, not where its marker stands (Dark Vision's way, 2026-11-13; the list and the
// right stick too since 2026-11-25: the user asked that every doorway be where it starts). A box wider than kBodyMaxM
// to a side is not trusted (a trigger can cover a whole room): its place it is. An exit's or a door's box always is:
// it is the way through itself, however wide (the line across the school's Entranceway is 18 m long, Port Island
// Station's street side 21 m, the school's front doors 6 m by 13 m: each was heard from its marker, up to 10 m
// along it from where the hero walks in).
constexpr float kBodyMaxM = 6.0f;
Body body_of(UObject* a, Kind k) {
  Body b;
  if (k == Kind::Person || k == Kind::Enemy || k == Kind::Way) return b;
  if (!a || !guarded([&] { b.has = world::trigger_box(a, b.box); })) return Body{};
  b.has = b.has && (k == Kind::Exit || k == Kind::Door || std::max(b.box.extent.x, b.box.extent.y) <= kBodyMaxM * 100.0f);
  return b;
}
// Standing inside the body (Paulownia Mall's exits are strips 9 m long the hero walks through, 2026-11-13) the
// nearest point is the hero himself, with no direction: the sound is heard in the middle then, from no side, at the
// rhythm of being at it. (It came from the thing's own place at first, which is not the box's middle: stepping into
// Port Island Station's way to the outskirts from the west, its sound went from 0.1 m to the right to 2.2 m to the
// left, 2026-11-25.)
Place place_of(const FVector& loc, const Body& b, const FVector& me) {
  auto metres = [&](const FVector& p) {
    return std::sqrt((p.x - me.x) * (p.x - me.x) + (p.y - me.y) * (p.y - me.y) + (p.z - me.z) * (p.z - me.z)) / 100.0f;
  };
  if (!b.has) return {loc, metres(loc)};
  if (core::box_holds(b.box, world::vec3(me), 0.0f, 200.0f)) return {me, 0.0f, true};   // the hero is 90 cm up: a step's leeway
  const FVector p = world::fvec(core::box_nearest(b.box, world::vec3(me)));
  return {p, metres(p)};
}
void place(Poi& p, const FVector& me) {
  const Place pl = place_of(p.loc, p.body, me);
  p.dist = pl.dist_m * 100.0f;
  p.bearing = world::bearing(me, pl.inside ? world::fvec(p.body.box.center) : pl.at);
}

// The navmesh path ends near the thing. Kept per actor while the hero stays on his side of the map (floors
// are joined by stairs that jump him: doors::side_stamp counts those, doors passed and levels changing).
// A path the navmesh calls partial counts when it ends there too: a hit's box floats above the floor, off the mesh,
// so the path to it never reaches its centre (Mandragora up Paulownia Mall's stairs, 2026-11-15: the path climbed
// the stairs and stopped 0.6 m short, partial; the shop and the whole upper floor were left out). Its end being on
// the thing's own floor (within 2.5 m up or down, floors are 3.4 m apart) is what keeps a spot below or above out.
static bool walkable(UObject* a, const world::FVector& me, const world::FVector& v) {
  static std::map<WeakObj::Key, bool> cache;
  static uint64_t side = 0;
  if (uint64_t s = doors::side_stamp(); s != side) { side = s; cache.clear(); }
  auto key = WeakObj::of(a).key();
  auto it = cache.find(key);
  if (it != cache.end()) return it->second;
  bool partial = true;
  auto path = world::find_path(world::path_start(me), v, &partial);
  // Its end on the thing's floor and near it, and no leg straight up (core::walks_to). Loading slot 9 puts the hero at
  // the dorm lounge's counter, right under 2F's "Your Room" exit: the exit was listed 4 meters away on the lounge
  // until the hero moved (the walk said "Stuck", 2026-11-24).
  std::vector<core::Vec3> pts;
  pts.reserve(path.size());
  for (const FVector& p : path) pts.push_back(world::vec3(p));
  bool ok = core::walks_to(pts, world::vec3(v));
  cache[key] = ok;
  return ok;
}

// The story flag an actor's FName property names is on (false when the property is unset or "None").
static bool flag_prop_on(UObject* a, const char* prop) {
  auto* f = field<FName>(a, prop);
  if (!f || f->index <= 0) return false;
  std::string flag = fname(*f);
  return !flag.empty() && flag != "None" && flag_on(flag);
}

// The name of the missing person on this floor, as the police board's notice gives it, or "" while the board does
// not show it yet. UFldDungeonMissingController: +0x168 a case is placed, +0x108 its data, whose +0x68 is the case
// number (what DUNGEON_GET_MISSING_ID returns, FUN_14117e120). The name is the speaker of that dialog of
// BMD_DisappearHelp, shown once the case's InfoOn flag is set (DisappearDataAsset +0x30: a TMap, elements of 0x30,
// key at +0, the case's flags Active, Success, Failed, Npc, InfoOn, Award at +8), as the Missing Persons list does.
static std::string missing_name(UObject* controller) {
  if (!controller || !ue::known_build()) return {};
  int no = 0;
  if (!guarded([&] {
        uint8_t* c = (uint8_t*)controller;
        uint8_t* data = c[0x168] ? *(uint8_t**)(c + 0x108) : nullptr;
        no = data ? *(int32_t*)(data + 0x68) : 0;
      }) || no <= 0)
    return {};
  static const int asset_id = watch::want("DisappearDataAsset", true);
  UObject* d = dat::find(asset_id, "DisappearDataAsset");
  if (!d) return {};
  auto* map = (TArray<uint8_t>*)((uint8_t*)d + 0x30);
  const int32_t* fl = nullptr;
  for (int i = 0; map->data && i < map->num && i < 200; ++i)
    if (*(uint16_t*)(map->data + i * 0x30) == no) fl = (const int32_t*)(map->data + i * 0x30 + 8);
  if (!fl || !party::flag(fl[4])) return {};
  auto f = bmdfile::load("BMD_DisappearHelp");
  if (!f || !f->ok || no >= (int)f->dialogs.size()) return {};
  int sp = f->dialogs[no].speaker;
  return sp >= 0 && sp < (int)f->speakers.size() ? core::clean_text(f->speakers[sp]) : std::string();
}

// Where the minimap draws the objective's mark (the "!" over the faculty office's door on 4/7, the field's objective
// "Head to the faculty office"): UFldMiniMapManager +0x40, a TArray of FTransform (0x30 each, its translation at
// +0x10). Empty while the minimap shows no mark (the classroom on 4/7 after school, "Return to the dorm"). Seen
// 2026-11-24: one mark 22 cm from the Faculty Office's hit, gone once the scene there had run.
static std::vector<FVector> objective_marks() {
  std::vector<FVector> out;
  static const int id = watch::want("FldMiniMapManager");
  UObject* m = watch::get(id);
  if (!m || !ue::known_build()) return out;   // this build's offset
  guarded([&] {
    auto* arr = (TArray<uint8_t>*)((uint8_t*)m + 0x40);
    if (!arr->data || arr->num <= 0 || arr->num > 8) return;
    for (int i = 0; i < arr->num; ++i) {
      const float* t = (const float*)(arr->data + i * 0x30 + 0x10);
      out.push_back(FVector{t[0], t[1], t[2]});
    }
  });
  return out;
}

bool breakable(UObject* a) {
  if (!a) return false;
  std::string cn = name_of(class_of(a));
  if (cn.find("Broken") == std::string::npos || get_bool(a, "bHidden")) return false;
  if (UObject* box = get<UObject*>(a, "Box")) {
    UFunction* f = find_function(class_of(box), "GetCollisionEnabled");
    if (f) { Params p(f); call(box, p); if (p.ret<uint8_t>() == 0) return false; }
  }
  return true;
}

std::vector<Poi> scan(float radius) {
  if (radius < 0) radius = settings::get(settings::PoiRange) * 100.0f;
  std::vector<Poi> out;
  world::FVector me;
  if (!world::player_location(me)) return out;
  UObject* hero = world::player();
  bool dungeon = hero && name_of(class_of(hero)).find("DUNGEON") != std::string::npos;
  // The Dark Hour's hero is the dungeon one everywhere, the 4/9 dorm included: only Tartarus (fields 2xx, its floors
  // name none) goes without the floor filter. The dorm's Dark Hour lounge listed every floor's doors ("Your Room,
  // 5 meters" from the lounge, 2026-11-24).
  if (int ma = 0, mi = 0; dungeon && area_ids(ma, mi) && (ma < 200 || ma >= 300)) dungeon = false;
  // Whether the unnamed triggers are listed (below) is one answer for every caller: it goes by what the list's own
  // range holds, not by `radius`. The sonar reads 10 m around the player, found nothing else that near, and sounded
  // a trigger the list (60 m, a chest and the stairs in it) did not have (a Tartarus floor, 2026-11-11).
  const float list_radius = std::max(radius, settings::get(settings::PoiRange) * 100.0f);
  bool beyond = false;   // something past `radius` that the list has
  // The icon the game floats over a person: an actor of its own, BP_UI_AccessIcon_<Kind>_C, whose Owner is the person
  // (the dorm lounge, 2026-11-11: five Talk icons owned by the five people there; Akihiko's became Talk_Read once he
  // was talked to). Hidden while a conversation runs. The plain Talk (a speech bubble) and Listen (an ear over two
  // students chatting) icons are the unread ones: the school hallway, 6/8 after school: six Talk, one Listen.
  static const char* const kIconKinds[] = {"Talk", "Listen", "Talk_Read", "Listen_Read", "Commu", "Commu_Field", "Commu_Reverse", "DormitoryLife",
                                           "MaleQuest", "MaleQuest_Field", "Quest", "StudyGroup", "Walking"};
  // The handwritten word icons are the same kind of actor (EFldHitCharaIconType WORD_13..16, the kind table's
  // 13..18): a "buzz" over a crowd and a "whisper" over people gossiping, both listened in on, each with a read
  // version (FldNpcActor_318_000 in the school; WORD_13 poked onto a student and FLD_RECREATE_MODEL_HEAD_ICON made
  // BP_UI_Handwriting_Buzz_00_C owned by them, 2026-11-21). Groan and mumble hang over people with no check icon
  // (the Lost at the station), who are not listed.
  static const char* const kWordKinds[] = {"Buzz_00", "Buzz_Read_00", "Whisper_00", "Whisper_Read_00"};
  static const std::vector<int> icon_ids = [] {
    std::vector<int> ids;
    for (const char* k : kIconKinds) ids.push_back(watch::want(std::format("BP_UI_AccessIcon_{}_C", k), true));
    for (const char* k : kWordKinds) ids.push_back(watch::want(std::format("BP_UI_Handwriting_{}_C", k), true));
    return ids;
  }();
  constexpr size_t kAccessKinds = std::size(kIconKinds);
  std::map<UObject*, const char*> icons;   // a person -> what their icon says
  for (size_t i = 0; i < icon_ids.size(); ++i)
    for (UObject* icon : watch::all(icon_ids[i])) {
      if (!is_live(icon) || get_bool(icon, "bHidden")) continue;
      if (UObject* owner = get<UObject*>(icon, "Owner"))
        icons[owner] = i < kAccessKinds ? core::icon_state(kIconKinds[i]) : core::icon_state(kWordKinds[i - kAccessKinds]);
    }
  // The list's own scan (not the sonar's or a prompt's nearer one): what the floor's objective is about is listed at
  // any distance on it.
  const bool list_scan = radius >= settings::get(settings::PoiRange) * 100.0f;
  auto add = [&](UObject* a, Kind k, std::string name, bool any_floor = false, bool any_distance = false) {
    world::FVector v{};
    if (!guarded([&] { v = world::actor_location(a); })) return;
    float d = std::sqrt((v.x - me.x) * (v.x - me.x) + (v.y - me.y) * (v.y - me.y) + (v.z - me.z) * (v.z - me.z));
    // Floors of one building share a level, stacked about 3.4 m apart and joined by teleporting stairs (the dorm,
    // 2026-10-27): another floor's things count only when the navmesh walks there (Tartarus' raised entrance does).
    // Tartarus floors are levels of their own with raised and sunken parts: no floor filter there.
    // A thing's box stands on its floor or above it: more than 1.2 m below the feet is the floor below (each floor's
    // stair box up sits 2.3 m over its floor, 1.9 m under the next: "Hallway 3F" was listed on 3F, 2026-11-24).
    float dz = v.z - (me.z - 90.0f);
    bool other_floor = !dungeon && !any_floor && (dz > 280.0f || dz < -120.0f);
    if (d > radius && !(any_distance && list_scan)) { beyond |= d <= list_radius && !other_floor; return; }
    // A Tartarus floor's Monad section stands in the same level about 74 m above it (z ~7600, area.cpp): no path
    // joins them. From inside it the floor's Head Up and Enter Door were listed and the walk there got stuck
    // (Adamah 231, 2026-11-24); things more than 30 m above or below belong to the other part.
    if (dungeon && std::abs(v.z - me.z) > 3000.0f) return;
    // "Same floor only": nothing of another floor, walkable or not, whether it stands a storey away or the walk to it
    // takes a stairway (the stairways themselves are listed on any).
    // Where the floors are joined by stairways the walk tells them apart, not the height: Paulownia Mall's upper
    // floor starts a metre above the square, and Mandragora at the top of its stairs stands 3.3 m over their foot.
    if (other_floor && !walkable(a, me, v)) return;
    if (settings::on(settings::FloorOnly) && k != Kind::Way && (floors::stairways() ? floors::elsewhere(a, me, v) : other_floor)) return;
    // Another part of the map, past a closed door (the corridor's things from the gym hallway, 2026-11-11): listed
    // once the hero is through it.
    if (doors::behind(a, me, v)) return;
    // The daily and the Dark Hour version of a hit often stand on the same spot: one entry per name and place.
    for (auto& o : out)
      if (core::same_thing(o.name, world::vec3(o.loc), name, world::vec3(v))) return;
    out.push_back(Poi{WeakObj::of(a), k, std::move(name), v, d, world::bearing(me, v)});
    out.back().body = body_of(a, k);
    place(out.back(), me);
    if (auto it = icons.find(a); it != icons.end()) out.back().state = it->second;
    // A Social Link partner whose next hangout ranks the link up (the game's own test, the town map's blue card): the
    // field's card icon looks the same either way, so the list says it (the user's call, 2026-11-24). Asked only of a
    // partner (FldCmmActor) or someone under the card icon: the name lookup reads the link table.
    if (k == Kind::Person) {
      Poi& p = out.back();
      int id = 0;
      if (is_a(a, "FldCmmActor")) id = get<int32_t>(a, "mUniqueId_", -1) + 1;
      else if (p.state == strings::kIconLink.c_str()) id = social::partner_arcana(p.name);
      if (id >= 1 && id <= 22 && social::ready(id))
        p.state = p.state.empty() ? std::string(strings::kReadyToRankUp) : p.state + ", " + strings::kReadyToRankUp.c_str();
    }
  };
  std::vector<UObject*> triggers;
  // A story trigger named for its scene, FldHitActor_<major>_<Scene>_H<n> (FldHitActor_299_Takaya_H0 and _Nyx_H0 at
  // the top of Tartarus, 2026-10-28), is where the story goes next: listed beside everything else, on any floor
  // (Takaya's box floats 7 m up a ramp, with no navmesh path to its centre), until its off flag is set.
  // Seen at Adamah floor 263 (2026-11-11): "Event: Takaya" and "Event: Nyx" listed from the landing, and the walk
  // to each started its fight.
  auto story_beat = [](UObject* a) -> std::string {
    std::string w = core::story_scene(name_of(a));
    if (w.empty() || flag_prop_on(a, "mOffFlagName_")) return {};
    // Only the box that starts the scene: after the 1/31 Jin scene his "stoper" stayed listed as "Event: Jin" and
    // said "There's no time to look back." (2026-11-24).
    if (!core::story_start(name_of(get<UObject*>(a, "mOverlapBluePrint_")))) return {};
    return w;
  };
  // A thing farther off than the list's own range cannot be in the result, nor change it: it is passed over before
  // its name and flags are read (most of a town's hit actors, every scan).
  auto out_of_range = [&](UObject* a) {
    world::FVector v{};
    if (!guarded([&] { v = world::actor_location(a); })) return true;
    return std::sqrt((v.x - me.x) * (v.x - me.x) + (v.y - me.y) * (v.y - me.y) + (v.z - me.z) * (v.z - me.z)) > list_radius;
  };
  std::map<UObject*, std::string> chests;   // a chest's hit -> its dungeon object's type
  for (UObject* o : live("FldDungeonObjectActor")) {
    auto* hits = field<TArray<UObject*>>(o, "m_pHitActorList");
    if (!hits) continue;
    guarded([&] {
      std::string type = enum_prop_name(o, "ObjType");
      if (!type.starts_with("TBox") || !hits->data || hits->num <= 0 || hits->num > 16) return;
      for (int i = 0; i < hits->num; ++i) if (hits->data[i]) chests[hits->data[i]] = type;
    });
  }
  // A missing person on this Tartarus floor (UFldDungeonMissingController.m_pMissingPerson, a BP_FldMisNPC_<n>_C;
  // the rescue scene's script destroys the actor and clears the pointer, DUNGEON_DESTROY_MISSING_NPC).
  static const int missing_id = watch::want("FldDungeonMissingController");
  UObject* missing = nullptr;
  if (UObject* mc = watch::get(missing_id)) missing = get<UObject*>(mc, "m_pMissingPerson");
  if (missing && (!is_live(missing) || get_bool(missing, "bHidden"))) missing = nullptr;
  for (UObject* a : live("FldHitCore")) {
    // The missing person is the floor's objective ("Find missing persons."): listed wherever on the floor they are
    // (a floor's far side was 107 m off, past the list's 60 m, and the list said "No People", 2026-11-24).
    // So is 5/9's way into the monorail, 200 m up the overhead bridge from where the party starts.
    std::string overlap = name_of(get<UObject*>(a, "mOverlapBluePrint_"));
    bool lost_one = missing && overlap == "BP_FldHit_MISNPC_01_HERO_C";
    bool way_on = overlap == "BP_FldHitActor_302_101_H1_Play_C";
    // A Tartarus floor's ways on (stairs, teleporter, doors) and its Gatekeeper are listed wherever on the floor they
    // are: after the 5F Gatekeeper the list said "No Exits" with Head Up 68 m off and the teleporter 62 m
    // (2026-11-25). Only for the list's own scan: the sonar's 4 Hz one keeps the range test.
    bool floor_wide = dungeon && list_scan;
    if (!world::actor_visible_level(a) || is_a(a, "FldNpcActor") || (!lost_one && !way_on && !floor_wide && out_of_range(a))) continue;
    // A slab across a stairway that sets the field's part: the stairways on from here are listed below (floors::ways).
    if (floors::slab(a)) continue;
    std::string icon = icon_of(a);
    // The missing person's only hit has no icon: a sphere that starts the rescue when walked into
    // (BP_DHIT_MISNPC_C, overlap BP_FldHit_MISNPC_01_HERO_C). Named by the game's hit-name table: "Stray Cat",
    // "Old Man in Pain", else "Missing Person" (row 10009013).
    // Seen on floor 50 (2026-11-12): listed under People, the walk into it started the rescue.
    if (icon == "None" && missing && name_of(get<UObject*>(a, "mOverlapBluePrint_")) == "BP_FldHit_MISNPC_01_HERO_C") {
      std::string nm = hit_name(a);
      if (nm.empty()) {
        nm = kin_name({"DT_FldDungeonHitName"}, 10009013);
        if (nm.empty()) nm = strings::kPoiMissingPerson;
        // The person's name from the police board's notice, as the Missing Persons list says it (seen on floor 50,
        // 2026-11-12: "Missing Person, Ayako Yoshimoto"); the hit's own name stays first.
        if (std::string who = missing_name(watch::get(missing_id)); !who.empty()) nm += ", " + who;
      }
      add(a, Kind::Person, nm, false, true);
      continue;
    }
    if (icon == "None") continue;
    // A box whose script does nothing (the 4/9 dorm escape's "Head Upstairs", at the stairs down: walked to and
    // checked, nothing happened, 2026-11-24).
    if (!get<UObject*>(a, "mKeyPushBluePrint_") && core::dead_hit(overlap)) continue;
    // Story triggers: unnamed boxes that only run a blueprint when walked through (the first Tartarus floor's
    // tutorial gates, 2026-10-27). Nothing there to use, but where the story leads: kept for an area with nothing
    // else (the monorail tracks, whose way on is a row of them, 2026-10-27).
    bool trigger = get<int32_t>(a, "mNameIndex_", -1) < 0 && !get<UObject*>(a, "mKeyPushBluePrint_") && get<UObject*>(a, "mOverlapBluePrint_");
    if (trigger)
      if (std::string beat = story_beat(a); !beat.empty()) { add(a, Kind::Event, std::format("{}: {}", strings::kPoiEvent, beat), true); continue; }
    // Done already: an opened treasure chest keeps its hit, with its story flag on (FLD_TAR_TBOX_OPENED_04).
    if (flag_prop_on(a, "mExecutedFlagName_")) continue;
    // Turned off: a picked-up resource spot ("Something Shining", a Twilight Fragment) keeps its hit with its off flag
    // on (FLD_RESOURCE_SPOT10, Paulownia Mall 2026-10-31).
    if (flag_prop_on(a, "mOffFlagName_")) continue;
    // The game's own "is this hit on" test fails on a second flag too, mIgnoreFlagName_ (a few unnamed triggers).
    // UNTESTED: from the game's code; none of those triggers was met with its flag on.
    if (flag_prop_on(a, "mIgnoreFlagName_")) continue;
    if (trigger) {
      // A Gatekeeper's floor: the box that starts its fight (BP_FldHit_Tartarus_GateKeeper, the Abyss of Time's too),
      // off once it is beaten (FLD_BATTLE_DEFEAT_GK_*, checked above). Always listed: it is what the floor is for.
      // The other unnamed boxes were never checked against their flags: a finished one is left out now.
      std::string bp = name_of(get<UObject*>(a, "mOverlapBluePrint_"));
      if (bp == "BP_FldHit_Tartarus_GateKeeper_C") add(a, Kind::Event, strings::kPoiGatekeeper.c_str(), false, true);
      // A full moon's boss: the box on the way to it (the Moonlight Bridge's, 13 m up the bridge, was not listed
      // while the party stood nearby, 2026-11-24). It goes once the fight is won (the field changes).
      else if (core::boss_trigger(bp)) add(a, Kind::Event, strings::kPoiLargeShadow.c_str());
      // 5/9's overhead bridge: of its unnamed boxes only this one leads on, into the monorail (CALL_FIELD(302, 102));
      // the others turn the party back. Listed as an exit (it was one of five "Event" boxes, 2026-11-24).
      else if (way_on) add(a, Kind::Exit, strings::kPoiIntoMonorail.c_str(), false, true);
      // A staircase with no name (the 7/7 hotel's: the way to the boss on 3F was listed only in an empty area,
      // 2026-11-24): an exit, by the floor it leads to.
      // Only the ones on the hero's floor (the banner's): another floor's flight, above or below, cannot be walked to
      // from here ("Stairs to floor 1" was listed on 3F, and the walk to it stuck, 2026-11-24).
      else if (int from = 0, to = 0; core::stairs(name_of(a), from, to)) { if (!banner_floor() || from == banner_floor()) add(a, Kind::Exit, strings::fmt(strings::kPoiStairsTo, to)); }
      else triggers.push_back(a);
      continue;
    }
    std::string type = enum_prop_name(a, "mType_");
    // A Social Link partner stands in the world as a hit actor of its own (FldCmmActor), hidden while away.
    bool cmm = is_a(a, "FldCmmActor");
    if (cmm && get_bool(a, "bHidden")) continue;
    std::string nm = cmm ? npc_name(a) : hit_name(a);
    // A character the story stands in the field as a hit of its own (FldHitCharacter: Yukari on the dorm's escape,
    // 2026-11-16) has no hit name; it carries its own, which the list said as "Person".
    if (nm.empty()) nm = disp_name(a);
    // The July hotel types the things you check on its ground floor (the information panel, the curtained waiting
    // booths, the reception window, the entrance; scripts that only show a message) as AreaChange hits under the
    // plain Check icon: listed as exits, they read as ways out (2026-11-24). Every other AreaChange hit in the game is
    // a FldAreaChange or carries the Go To icon (a survey of the field levels): a FldHitActor under Check is a thing.
    bool way_out = icon == "Goto" || (type == "AreaChange" && !(icon == "Check" && !is_a(a, "FldAreaChange")));
    if (way_out) add(a, Kind::Exit, nm.empty() ? strings::kPoiExit.c_str() : nm, false, dungeon);
    else if (icon == "Shop") add(a, Kind::Shop, nm.empty() ? strings::kPoiShop.c_str() : nm);
    // A vendor under the Speak icon (a hit named as a shop) is a shop like an NPC vendor (below).
    else if (icon == "Speak" || icon == "Listen") add(a, !cmm && check_kind(a) == Kind::Shop ? Kind::Shop : Kind::Person, nm.empty() ? strings::kPoiPerson.c_str() : nm);
    // Tartarus' doors are ways onward under the plain Check icon: the Monad door on a floor ("Enter Door", row
    // 10009006; seen on Adamah floors 231 and 243, 2026-11-11), and in the passage "Exit Door", "Proceed Onward" and
    // the way back (10009007-10009009, 10009012; all three seen listed on Adamah floor 255, 2026-11-11).
    else if (int idx = get<int32_t>(a, "mNameIndex_", -1); ((idx >= 10009006 && idx <= 10009009) || idx == 10009012) && !nm.empty()) add(a, Kind::Exit, nm, false, dungeon);
    else if (fragment_spot(a)) add(a, Kind::Fragment, strings::kPoiFragment.c_str());
    else if (nm.empty()) add(a, Kind::Thing, strings::kPoiThing.c_str());
    else if (auto c = chests.find(a); c != chests.end()) add(a, Kind::Thing, chest_name(c->second, nm));
    else add(a, check_kind(a), nm);
    // The desk in your room (row KIN_02121001, "Desk") is where its computer is: Innocent Sin Online (the Hermit link)
    // is played there, and a sighted player sees the computer on it. Said after its name with the game's own name for
    // a computer (KIN_02102109's Name, "Computer"; its Name2 is the lounge's "Shared Computer").
    if (!out.empty() && out.back().obj == WeakObj::of(a) && get<int32_t>(a, "mNameIndex_", -1) == 2121001)
      if (std::string pc = kin_name({"DT_FldDailyHitName"}, 2102109, nullptr, true); !pc.empty()) out.back().state = pc;
    // The July hotel's 3F rooms (7/7, "Break the defective mirror on 3F"): the defective mirror is the one that shows
    // no reflection, which a sighted player sees as they walk in. Each room's mirror runs its own procedure of
    // BF_FldHit_HotelDungeon through its key-press blueprint: 53, 56 and 59 (rooms 301-303, SUB_MISTAKE_MIRROR: a
    // fade back to the hallway) and 62 (room 304, the right one). Said after the mirror's name.
    if (!out.empty() && out.back().obj == WeakObj::of(a)) {
      std::string bp = name_of(get<UObject*>(a, "mKeyPushBluePrint_"));
      if (bp == "BP_FldHitActor_304_114_H62_Play_C") out.back().state = strings::kMirrorNoReflection.c_str();
      else if (bp == "BP_FldHitActor_304_111_H53_Play_C" || bp == "BP_FldHitActor_304_112_H56_Play_C" || bp == "BP_FldHitActor_304_113_H59_Play_C")
        out.back().state = strings::kMirrorReflection.c_str();
    }
    // A named spot that starts a full moon's boss fight (9/5's Club Escapade door, 10/4's way to the station plaza:
    // Fuuka's "Are you ready?"): it says so after its name and Events lists it too, as the objective's mark is.
    if (!out.empty() && out.back().obj == WeakObj::of(a) &&
        (core::boss_trigger(name_of(get<UObject*>(a, "mKeyPushBluePrint_"))) || core::boss_trigger(name_of(get<UObject*>(a, "mOverlapBluePrint_"))))) {
      Poi& p = out.back();
      p.objective = true;
      p.state = p.state.empty() ? std::string(strings::kPoiLargeShadow) : p.state + ", " + strings::kPoiLargeShadow.c_str();
    }
  }
  // The stairways to the field's other floors (the Strip Mall's, Club Escapade's, Port Island Station's): each by the
  // slab at its far end, on a landing above or below the hero's floor.
  // Each is listed and heard from where it is walked into from here (floors::lead), not from the slab itself.
  for (const floors::Way& w : floors::ways()) {
    const size_t had = out.size();
    add(w.box, Kind::Way, floors::name(w), true);
    world::FVector at{};
    if (out.size() == had || !floors::lead(w.box, me, at)) continue;
    Poi& p = out.back();
    p.loc = at;
    p.dist = std::sqrt((at.x - me.x) * (at.x - me.x) + (at.y - me.y) * (at.y - me.y) + (at.z - me.z) * (at.z - me.z));
    p.bearing = world::bearing(me, at);
  }
  for (UObject* a : live("FldNpcActor")) {
    if (!world::actor_visible_level(a) || get_bool(a, "bHidden")) continue;
    // A placeholder with nobody spawned in it (no child actor, no class): not a person (the dorm lounge, 2026-10-27).
    auto* kids = field<TArray<UObject*>>(a, "Children");
    if (kids && kids->num == 0 && !get<UObject*>(a, "mNpcBaseClass_") && !get<UObject*>(a, "mCharaBaseClass_")) continue;
    // Nobody standing in it: no character model loaded (mCharaModelList_, a TMap: its element array's count is 0).
    // Three such spots on the dorm's third floor (FldNpcActor_298_*, a base class but no model and no icon, 5/4
    // evening, 2026-11-12) were listed as "Person" 2 m away, and the auto-walk stalled against their collision.
    // A spot the game gave an interaction icon (mIconActor_) is someone to talk to even without a model of its own:
    // the Weak Cat at the Station Outskirts (FldNpcActor_424_000; its body is placed in the level, the spot's only
    // child is its talk icon, 2026-11-18) was left out.
    auto* models = field<TArray<uint8_t>>(a, "mCharaModelList_");
    if (models && models->num == 0 && !get<UObject*>(a, "mIconActor_")) continue;
    // Scenery: someone the game gives no way to talk to. Officer Kurosawa (FldNpcActor_150_000, Paulownia Mall)
    // stands inside the police station, behind its wall, where no walk reaches him; his menu opens at the station's
    // door (the Police Station shop). The game gave him no talk icon (mIconType_ None, no mIconActor_), no key-press
    // blueprint (mKeyPushBluePrint_) and no script (mBfAssetPath_), where the people you talk to have them
    // (2026-11-23). Listed, the walk to him circled the plaza for 15 s and said "Stuck".
    auto* icon_type = field<uint8_t>(a, "mIconType_");
    auto* bf = field<FString>(a, "mBfAssetPath_");
    if (icon_type && *icon_type == 0 && !get<UObject*>(a, "mIconActor_") && !get<UObject*>(a, "mKeyPushBluePrint_") &&
        (!bf || bf->num <= 1))
      continue;
    // A vendor is a shop: talking opens its menu. The game marks most with the Shop icon (Octopia, 2026-11-16: listed
    // as a Person before); the rest by their script (core::npc_sells).
    bool sells = icon_of(a) == "Shop";
    if (!sells) {
      UObject* lvl = outer_of(a);
      UObject* w = lvl ? outer_of(lvl) : nullptr;   // a ULevel's outer is its UWorld, named for the level
      sells = core::npc_sells(get<int32_t>(a, "mMajorID_", -1), get<int32_t>(a, "mMinorID_", -1), w ? name_of(w) : std::string());
    }
    std::string who = npc_name(a);
    // A bar customer in Mutatsu's order quiz: where they stand, as the bartender will ask about them.
    if (const char* at = core::bar_customer_place(get<int32_t>(a, "mMajorID_", -1), get<int32_t>(a, "mMinorID_", -1)))
      who = std::format("{} ({})", who, at);
    add(a, sells ? Kind::Shop : Kind::Person, who);
  }
  // Tartarus' breakable Shadow remains (BP_DOBJ_Broken*_C; strike them, Ctrl, for items). A broken one stays visible
  // but its Box stops colliding (NoCollision, 2026-10-27).
  // One of them is a crystal that always gives a Twilight Fragment (BP_DOBJ_BrokenFragment_C,
  // EDungeonObjType::BrokenFragment; its script is BF_BP_DOBJ_BrokenObject's "Hit_BrokenHakumei_Object"). It is built
  // like the others (the same Box), and was left out of the breakables until 2026-11-11.
  // Seen listed on Adamah floor 240 (2026-11-11).
  for (UObject* a : live("FldDungeonObjectActor")) {
    if (!breakable(a)) continue;
    if (name_of(class_of(a)).find("BrokenFragment") != std::string::npos) add(a, Kind::Fragment, strings::kPoiFragmentCrystal.c_str());
    else add(a, Kind::Thing, strings::kPoiBreakable.c_str());
  }
  // Shadows roaming a Tartarus floor (EnemySymbolBaseCore; parked or defeated ones are hidden).
  const std::vector<shadow::Holder> holders = shadow::enemy_holders();
  for (UObject* a : live("EnemySymbolBaseCore")) {
    if (get_bool(a, "bHidden")) continue;
    UObject* comp = nullptr;
    for (const shadow::Holder& h : holders) if (h.actor == a) { comp = h.comp; break; }
    add(a, Kind::Enemy, shadow_name(a, comp));
  }
  if (out.empty() && !beyond) for (UObject* a : triggers) add(a, Kind::Event, strings::kPoiEvent.c_str());
  std::sort(out.begin(), out.end(), [](const Poi& a, const Poi& b) { return a.dist < b.dist; });
  // A door between two rooms is two exits a step apart, one on each side, each named for where it leads (the
  // monorail's cars, 1.4 m apart, 2026-10-27): only the one on the player's side, the nearer, counts.
  std::vector<core::Place> places;
  for (auto& p : out) places.push_back(core::Place{p.kind == Kind::Exit, p.name, world::vec3(p.loc)});   // not a Way: it has no other side
  std::vector<Poi> kept;
  for (size_t i : core::near_sides(places)) kept.push_back(std::move(out[i]));
  // The objective's mark: the thing it stands on (within 3 m, on its floor) is where the story sends the player.
  // A sighted player sees the "!" on the minimap; the list says "objective" after its name and Events lists it.
  for (const FVector& m : objective_marks()) {
    Poi* best = nullptr;
    float bd = 300.0f;
    for (Poi& p : kept) {
      float d = std::hypot(p.loc.x - m.x, p.loc.y - m.y);
      if (d < bd && std::fabs(p.loc.z - m.z) < 250.0f) { bd = d; best = &p; }
    }
    if (!best || best->objective) continue;
    best->objective = true;
    best->state = best->state.empty() ? std::string(strings::kObjectiveMark) : best->state + ", " + strings::kObjectiveMark.c_str();
  }
  return kept;
}

void tick() {
  if (screens::loading()) objectives_reset();   // asked before the early return: the load list is a screen
  if (screens::current() || msg::current().blocking) return;   // a menu, notice or message has the floor
  pickup_tick();
  // The field's sounds only while the player walks it: a battle between turns has no screen up, and a story scene
  // no blocking window, yet neither is the place for them.
  shadow::tick();   // it checks that the player walks the field itself, after logging how a battle begins
  sight::tick();    // the edge of the Shadows' sight (it checks the same)
  prompt_tick();
  arrival_tick();
}

void install() {
  dev::route("/hits", [](const dev::Request& r, int&) {
    // /hits?idx=10002012 every hit actor with that name index (any level), with its level and visibility
    int want = (int)dev::arg_int(r, "idx", -1);
    auto out = std::make_shared<std::string>("timeout\n");
    hooks::run_on_game_thread([out, want] {
      std::string s;
      for (UObject* a : live("FldHitCore")) {
        int idx = get<int32_t>(a, "mNameIndex_", -1);
        if (want >= 0 && idx != want) continue;
        world::FVector v = world::actor_location(a);
        s += std::format("#{} {} idx {} '{}' level {} visible={} at ({:.0f}, {:.0f}, {:.0f})\n", index_of(a), name_of(a), idx, hit_name(a), name_of(outer_of(outer_of(a))),
                         world::actor_visible_level(a), v.x, v.y, v.z);
      }
      *out = s.empty() ? "none\n" : s;
    });
    return *out;
  }, "?idx=N hit actors by name index");
  dev::route("/poi", [](const dev::Request& r, int&) {
    auto out = std::make_shared<std::string>("timeout\n");
    float radius = (float)dev::arg_num(r, "r", 6000);
    bool body = dev::has(r, "body");
    hooks::run_on_game_thread([out, radius, body] {
      std::string s;
      world::FVector me{};
      world::player_location(me);
      for (auto& p : scan(radius)) {
        s += std::format("#{} [{}] {}", p.obj.index, kind_name(p.kind), describe(p));
        // ?body=1: its box (two sides in metres), whether its near edge is used, and how far its own place is.
        if (body)
          s += std::format("  | box {:.1f} x {:.1f} m {} marker {:.1f} m", p.body.box.extent.x / 50.0f, p.body.box.extent.y / 50.0f,
                           p.body.has ? "edge" : "marker", place_of(p.loc, Body{}, me).dist_m);
        s += "\n";
      }
      *out = s.empty() ? "none\n" : s;
    });
    return *out;
  }, "?r=cm ?body=1 points of interest near the player");
}
}  // namespace p3a::poi
