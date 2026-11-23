#pragma once
#include <functional>
#include <string>
#include <string_view>
#include <vector>
#include "core/boxes.h"

// The points of interest's own reasoning about names and lists: what a name says a thing is, how an actor's or a
// flag's name comes apart, which entries of a list are one thing seen twice. Engine-free.
namespace p3a::core {

// A camera-relative bearing in degrees (0 ahead, 90 right) as a clock hour, 1 to 12 (12 = ahead).
int clock_hour(float bearing_deg);
// A bearing clockwise from north in degrees as one of the compass' eight points, 0 north to 7 north-west
// (strings::kCompass).
int compass_point(float bearing_deg);

// An object's name split at its underscores ("FldNpcActor_105_102_Yukari_6" -> 5 parts; empty parts are kept).
std::vector<std::string> name_parts(const std::string& name);
// The person an NPC actor's name stands for: one of the cast by the romanised spelling the actor names carry
// ("Mituru" -> "Mitsuru", "Sanada" -> "Akihiko"), else the first part after the class that is not a number
// ("FldNpcActor_Jin" -> "Jin"). "" when the name has neither.
std::string person_from_actor_name(const std::string& actor_name);
// The scene a story trigger is named for: FldHitActor_<major>_<Scene>_H<n> -> "Scene" ("FldHitActor_299_Takaya_H0"
// -> "Takaya"). "" for an ordinary hit actor (FldHitActor_105_101_H3).
std::string story_scene(const std::string& actor_name);

// A name that ends in "_<digits>" without a leading zero is, to Unreal, the name before it with a number one
// higher: "FOO_12" is FOO with number 13. True, with both parts, when `name` is such a name.
bool numbered_name(const std::string& name, std::string& base, int& number);

// What the icon floating over a person says about them, by the icon's kind (the middle of its class name,
// BP_UI_AccessIcon_<Kind>_C): "" for the plain Talk and Listen icons and for a kind not known.
const char* icon_state(std::string_view kind);
// The kind in an icon actor's class name: "BP_UI_AccessIcon_Talk_Read_C" -> "Talk_Read"; "" for another class.
std::string icon_kind(std::string_view class_name);

// What a hit under the plain Check icon is, by the name the game gives it: somewhere to buy, eat, work or spend
// time (a business's entrance, a vendor, a vending machine); a room's door to check; or a thing.
enum class CheckKind { Shop, Door, Thing };
CheckKind check_kind(int name_index);   // a hit's mNameIndex_

// A person whose talk opens a shop: an NPC by its script's character and variant (FldNpcActor mMajorID_ /
// mMinorID_) and the level it stands in (the event-day variant 700 sells only on New Year's, "..._Event_550").
// Those marked with the Shop icon are shops by the icon; this covers the ones under the Speak icon too.
bool npc_sells(int major, int minor, std::string_view level);

// The rows of the NPC name table (DT_FldNpcName, KIN_<8 digits>) to try for an NPC, best first: its own mNameIndex_
// (-1 when it has none), then, on a field level (LV_F<n>...), the rows its script ids name: major * 1000 + minor, then
// major * 1000 (the character's own row: 150 -> 150000 "Officer Kurosawa"). Shop and Velvet Room backdrop levels reuse
// other characters' ids, so they get only the index.
std::vector<int> npc_name_rows(int name_index, int major, int minor, std::string_view level);

// Club Escapade's order quiz (Mutatsu's Tower link, Event_fild_390_001): the customers are named by their looks
// ("Temperamental Woman", NPCs 683-686 variant 700) but the bartender asks by where they stand. The customer a
// question asks about (its NPC major id), 0 for any other line; and where a customer stands in his words, nullptr
// for anyone else (and for the man, whose question names no place).
int bar_customer_asked(std::string_view line);
const char* bar_customer_place(int major, int minor);

// A Tartarus chest's name by its dungeon object type: the rare and the gold ones by the mod's words, a locked one
// with what it costs ("..., 3 Twilight Fragments"), any other by the game's own name.
std::string chest_name(const std::string& type, const std::string& game_name);

// A point of interest is the one a prompt's label names: the same name, or the name with something in brackets
// after it ("Nozomi Suemitsu (Moon)" for the label "Nozomi Suemitsu").
bool is_named(const std::string& poi_name, const std::string& label);
// A way onward named as what you do there ("Go Elsewhere", "Head Up", "Return to Dorm"), not as a place.
bool named_as_action(int name_index, bool name2_shown);   // a hit's mNameIndex_, and whether its Name2 shows

// The category a list settles on: `current` when it has something (and `move` is false), else the next one in
// `delta`'s direction that has, wrapping round `count` categories. -1 when every category is empty.
int settle_category(int current, int count, int delta, bool move, const std::function<bool(int)>& has_any);

// Two entries are one thing listed twice: the same name within 150 cm (summed over the three axes).
bool same_thing(const std::string& name_a, const Vec3& at_a, const std::string& name_b, const Vec3& at_b);
// A door between two rooms is two exits a step apart, one on each side, each named for where it leads. Of a list
// sorted nearest first, the indices to keep: an exit within 2 m of a kept exit of another name is the far side.
struct Place { bool exit = false; std::string name; Vec3 at; };
std::vector<size_t> near_sides(const std::vector<Place>& sorted);

}  // namespace p3a::core
