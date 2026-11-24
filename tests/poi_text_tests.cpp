#include "doctest.h"
#include "core/poi_text.h"
#include "core/strings.h"
#include <string>
#include <vector>

using namespace p3a;
using namespace p3a::core;

TEST_CASE("clock_hour: a bearing as a clock face") {
  CHECK(clock_hour(0.0f) == 12);
  CHECK(clock_hour(14.0f) == 12);     // still nearer 12 than 1
  CHECK(clock_hour(16.0f) == 1);
  CHECK(clock_hour(60.0f) == 2);
  CHECK(clock_hour(90.0f) == 3);
  CHECK(clock_hour(180.0f) == 6);
  CHECK(clock_hour(-180.0f) == 6);
  CHECK(clock_hour(-90.0f) == 9);
  CHECK(clock_hour(-30.0f) == 11);
  CHECK(clock_hour(-10.0f) == 12);
}

TEST_CASE("name_parts: split at underscores, empty parts kept") {
  auto p = name_parts("FldNpcActor_105_102_Yukari_6");
  REQUIRE(p.size() == 5);
  CHECK(p[0] == "FldNpcActor");
  CHECK(p[3] == "Yukari");
  CHECK(p[4] == "6");
  CHECK(name_parts("Plain").size() == 1);
  auto q = name_parts("A__B_");
  REQUIRE(q.size() == 4);
  CHECK(q[1].empty());
  CHECK(q[3].empty());
  CHECK(name_parts("").size() == 1);
}

TEST_CASE("person_from_actor_name: the cast by their romanised names, others by their own word") {
  CHECK(person_from_actor_name("FldNpcActor_105_102_Yukari_6") == "Yukari");
  CHECK(person_from_actor_name("FldNpcActor_102_101_Mituru_2") == "Mitsuru");
  CHECK(person_from_actor_name("FldNpcActor_102_101_Sanada") == "Akihiko");
  CHECK(person_from_actor_name("FldNpcActor_102_101_Aegis_1") == "Aigis");
  CHECK(person_from_actor_name("FldNpcActor_102_101_Amada_1") == "Ken");
  CHECK(person_from_actor_name("FldNpcActor_Jin") == "Jin");                 // no field ids at all
  CHECK(person_from_actor_name("FldNpcActor_101_103_Student_12") == "Student");
  CHECK(person_from_actor_name("FldNpcActor_101_103_12").empty());           // numbers only
  CHECK(person_from_actor_name("FldNpcActor").empty());
}

TEST_CASE("stairs: the hotel's unnamed staircases") {
  int from = 0, to = 0;
  CHECK(stairs("FldHitActor_304_101_H0", from, to)); CHECK(from == 1); CHECK(to == 2);
  CHECK(stairs("FldHitActor_304_101_H1", from, to)); CHECK(from == 2); CHECK(to == 1);
  CHECK(stairs("FldHitActor_304_101_H2", from, to)); CHECK(from == 2); CHECK(to == 3);
  CHECK(stairs("FldHitActor_304_101_H3_1", from, to)); CHECK(from == 3); CHECK(to == 2);
  CHECK_FALSE(stairs("FldHitActor_304_101_H24", from, to));
  CHECK_FALSE(stairs("FldHitActor_105_101_H0", from, to));
}

TEST_CASE("story_scene: a trigger named for its scene") {
  CHECK(story_scene("FldHitActor_299_Takaya_H0") == "Takaya");
  CHECK(story_scene("FldHitActor_299_Nyx_H0") == "Nyx");
  CHECK(story_scene("FldHitActor_105_101_H3").empty());      // field ids, then the hit's number
  CHECK(story_scene("FldHitActor_305_H30_X").empty());       // H<n> is a hit number, not a scene
  CHECK(story_scene("FldHitActor_299_Takaya").empty());      // too short to be one
  CHECK(story_scene("FldNpcActor_299_Takaya_H0").empty());   // not a hit actor
  CHECK(story_scene("FldHitActor_Takaya_Nyx_H0").empty());   // no field id
  CHECK(story_scene("FldHitActor_299_T_H0").empty());        // one letter is no scene
  CHECK(story_scene("FldHitActor_299_Hall_H0") == "Hall");   // H followed by a letter is a word
}

TEST_CASE("numbered_name: a numeric suffix is the name's number plus one") {
  std::string base;
  int n = 0;
  REQUIRE(numbered_name("FLD_TAR_TBOX_OPENED_12", base, n));
  CHECK(base == "FLD_TAR_TBOX_OPENED");
  CHECK(n == 13);
  REQUIRE(numbered_name("FOO_0", base, n));   // a lone zero is a number
  CHECK(base == "FOO");
  CHECK(n == 1);
  REQUIRE(numbered_name("FLD_RESOURCE_SPOT_7", base, n));
  CHECK(n == 8);
}

TEST_CASE("numbered_name: what stays one whole name") {
  std::string base = "untouched";
  int n = -1;
  CHECK_FALSE(numbered_name("FLD_RESOURCE_SPOT10", base, n));           // no underscore before the digits
  CHECK_FALSE(numbered_name("FLD_TAR_TBOX_OPENED_04", base, n));        // a leading zero
  CHECK_FALSE(numbered_name("FLD_MOON_MILITARY_R_MEDAL_01_GOT", base, n));
  CHECK_FALSE(numbered_name("FOO_", base, n));
  CHECK_FALSE(numbered_name("FOO", base, n));
  CHECK_FALSE(numbered_name("FOO_12a", base, n));
  CHECK_FALSE(numbered_name("FOO_1234567890", base, n));                // too long for a number
  CHECK(base == "untouched");
  CHECK(n == -1);
}

TEST_CASE("check_kind: shops, doors and things by their name's row") {
  CHECK(check_kind(2) == CheckKind::Shop);          // Ramen Shop
  CHECK(check_kind(3101002) == CheckKind::Shop);
  CHECK(check_kind(1) == CheckKind::Door);          // Classroom Door
  CHECK(check_kind(0) == CheckKind::Thing);
  CHECK(check_kind(-1) == CheckKind::Thing);
}

TEST_CASE("npc_name_rows: the index first, then the script ids on a field level") {
  CHECK(npc_name_rows(1000, 1, 0, "LV_F101_102_Npc") == std::vector<int>{1000, 1000});
  CHECK(npc_name_rows(-1, 150, 0, "LV_F103_101_Npc") == std::vector<int>{150000});            // Officer Kurosawa
  CHECK(npc_name_rows(-1, 31, 700, "LV_F103_101_Npc_KeyFree_Event_300") == std::vector<int>{31700, 31000});
  CHECK(npc_name_rows(-1, 103, 119, "LV_WeaponShop").empty());                                // a shop's backdrop
  CHECK(npc_name_rows(-1, 201, 103, "LV_VelvetRoom").empty());
  CHECK(npc_name_rows(-1, 150, 0, "").empty());
  CHECK(npc_name_rows(-1, -1, -1, "LV_F103_101_Npc").empty());
}

TEST_CASE("npc_sells: the vendors' scripts, not their event-day chatter") {
  CHECK(npc_sells(103, 0, "LV_F105_102_Npc"));                        // Octopia
  CHECK(npc_sells(104, 0, "LV_F103_111_Npc"));                        // Luxury Shopkeeper (Speak icon)
  CHECK(npc_sells(404, 0, "LV_F103_111_Npc"));                        // Fortune-Teller
  CHECK(npc_sells(103, 700, "LV_F106_101_Npc_KeyFree_Event_550"));    // New Year's takoyaki
  CHECK_FALSE(npc_sells(103, 700, "LV_F105_102_Npc_KeyFree_Event_600"));
  CHECK_FALSE(npc_sells(105, 700, "LV_F103_111_Npc_KeyFree_Event_900"));
  CHECK_FALSE(npc_sells(413, 0, "LV_F105_102_Npc"));                  // a passer-by
  CHECK_FALSE(npc_sells(106, 0, ""));
}

TEST_CASE("chest_name: by the dungeon object's type") {
  CHECK(chest_name("TBoxPrimField", "Treasure Chest") == "Treasure Chest");
  CHECK(chest_name("TBoxRare", "Treasure Chest") == strings::kPoiChestRare);
  CHECK(chest_name("TBoxJewelry", "Treasure Chest") == strings::kPoiChestGold);
  CHECK(chest_name("TBoxMedal1", "Treasure Chest") == std::string(strings::kPoiChestLocked) + ", 1 " + strings::kPoiFragment);
  CHECK(chest_name("TBoxMedal3", "Treasure Chest") == std::string(strings::kPoiChestLocked) + ", 3 " + strings::kPoiFragments);
  CHECK(chest_name("TBoxMedal3", "Treasure Chest") == "Locked Treasure Chest, 3 Twilight Fragments");
  CHECK(chest_name("", "Bed") == "Bed");
}

TEST_CASE("bar_customer_asked: the bartender's questions name a customer by place") {
  CHECK(bar_customer_asked("Hey, what does the girl standing by the table in the back want?") == 683);
  CHECK(bar_customer_asked("What did that girl by the entrance order?") == 684);
  CHECK(bar_customer_asked("Bartender: And the girl in the middle of the floor?") == 685);
  CHECK(bar_customer_asked("I see, who else...? Oh, what about that guy over there? What does he want?") == 686);
  CHECK(bar_customer_asked("Alright, I'll start on the drinks.") == 0);
  CHECK(bar_customer_asked("Who's that guy over there?") == 0);
}

TEST_CASE("bar_customer_place: where a customer stands, in the bartender's words") {
  CHECK(std::string(bar_customer_place(683, 700)) == "by the table in the back");
  CHECK(std::string(bar_customer_place(684, 700)) == "by the entrance");
  CHECK(std::string(bar_customer_place(685, 700)) == "in the middle of the floor");
  CHECK(bar_customer_place(686, 700) == nullptr);
  CHECK(bar_customer_place(684, 0) == nullptr);
}

TEST_CASE("is_named: a prompt's label names a point of interest") {
  CHECK(is_named("Bed", "Bed"));
  CHECK(is_named("Nozomi Suemitsu (Moon)", "Nozomi Suemitsu"));
  CHECK_FALSE(is_named("Nozomi Suemitsu", "Nozomi Suemitsu (Moon)"));
  CHECK_FALSE(is_named("Bedroom", "Bed"));
  CHECK_FALSE(is_named("Bed 2", "Bed"));
  CHECK_FALSE(is_named("Bed", "Desk"));
}

TEST_CASE("named_as_action: a way onward that says what you do, by its name's row") {
  CHECK(named_as_action(10000001, false));        // Go Elsewhere
  CHECK(named_as_action(10009017, false));        // Enter the Velvet Room
  CHECK_FALSE(named_as_action(10009003, false));  // Giant Device ...
  CHECK(named_as_action(10009003, true));         // ... Go to Another Floor once its flag is on
  CHECK_FALSE(named_as_action(2102108, false));   // Bulletin Board
  CHECK_FALSE(named_as_action(-1, false));
}

TEST_CASE("settle_category: stay, move on past empty ones, wrap, or find none") {
  auto has = [](std::vector<int> full) {
    return [full](int c) { for (int f : full) if (f == c) return true; return false; };
  };
  CHECK(settle_category(2, 7, 1, false, has({2, 5})) == 2);    // the current one has something: stay
  CHECK(settle_category(2, 7, 1, false, has({5})) == 5);       // else the next that has
  CHECK(settle_category(2, 7, 1, true, has({2, 5})) == 5);     // a move leaves the current one
  CHECK(settle_category(5, 7, 1, true, has({2, 5})) == 2);     // and wraps
  CHECK(settle_category(2, 7, -1, true, has({2, 5})) == 5);    // backwards, wrapping below zero
  CHECK(settle_category(2, 7, 1, true, has({2})) == 2);        // nothing else: back where it was
  CHECK(settle_category(0, 7, -1, true, has({6})) == 6);
  CHECK(settle_category(3, 7, 1, false, has({})) == -1);
  CHECK(settle_category(3, 7, -1, true, has({})) == -1);
}

TEST_CASE("same_thing: one name on one spot") {
  CHECK(same_thing("Door", Vec3{0, 0, 0}, "Door", Vec3{50, 50, 40}));
  CHECK_FALSE(same_thing("Door", Vec3{0, 0, 0}, "Door", Vec3{50, 50, 50}));   // 150 over the three axes
  CHECK_FALSE(same_thing("Door", Vec3{0, 0, 0}, "Gate", Vec3{0, 0, 0}));
  CHECK(same_thing("Door", Vec3{-10, 20, 5}, "Door", Vec3{-10, 20, 5}));
}

TEST_CASE("near_sides: of a door's two exits only the nearer is kept") {
  std::vector<Place> list = {
    {true, "Car 2", Vec3{0, 0, 0}},        // this side of the door
    {false, "Seat", Vec3{50, 0, 0}},
    {true, "Car 1", Vec3{140, 0, 0}},      // its other side, 1.4 m on
    {true, "Car 3", Vec3{-900, 0, 0}},     // another door altogether
    {true, "Car 3", Vec3{-950, 0, 0}},     // the same name twice is not a pair of sides
    {false, "Bin", Vec3{-910, 0, 0}},      // a thing beside an exit is kept
  };
  CHECK(near_sides(list) == std::vector<size_t>{0, 1, 3, 4, 5});
}

TEST_CASE("near_sides: a far side does not hide a third exit") {
  // The middle exit goes (it is 1.5 m from the first); the last is 3 m from the first and is kept, although it is
  // 1.5 m from the one that went.
  std::vector<Place> list = {{true, "A", Vec3{0, 0, 0}}, {true, "B", Vec3{150, 0, 0}}, {true, "C", Vec3{300, 0, 0}}};
  CHECK(near_sides(list) == std::vector<size_t>{0, 2});
  CHECK(near_sides({}).empty());
  // Height counts: an exit 2.5 m above another is no far side of it.
  std::vector<Place> stacked = {{true, "Up", Vec3{0, 0, 0}}, {true, "Down", Vec3{0, 0, 250}}};
  CHECK(near_sides(stacked) == std::vector<size_t>{0, 1});
}

TEST_CASE("icon_state: what the icon over a person says") {
  using p3a::core::icon_kind;
  using p3a::core::icon_state;
  CHECK(icon_kind("BP_UI_AccessIcon_Talk_Read_C") == "Talk_Read");
  CHECK(icon_kind("BP_UI_AccessIcon_Commu_C") == "Commu");
  CHECK(icon_kind("FldNpcActor").empty());
  CHECK(icon_kind("BP_UI_AccessIcon__C").empty());
  CHECK(std::string(icon_state("Talk")) == "something to say");   // the speech bubble
  CHECK(std::string(icon_state("Listen")) == "overhear");
  CHECK(std::string(icon_state("Buzz_00")) == "overhear, a buzz of chatter");
  CHECK(std::string(icon_state("Whisper_00")) == "overhear, whispering");
  CHECK(std::string(icon_state("Whisper_Read_00")) == "already heard");
  CHECK(std::string(icon_state("Talk_Read")) == "already spoken to");
  CHECK(std::string(icon_state("Listen_Read")) == "already heard");
  CHECK(std::string(icon_state("Commu")) == std::string(icon_state("Commu_Field")));
  CHECK(std::string(icon_state("Commu_Reverse")) == "Social Link, reversed");
  CHECK(std::string(icon_state("MaleQuest_Field")) == "Linked Episode");
  CHECK(std::string(icon_state("Something_New")).empty());
}

TEST_CASE("compass_point: eight points from north, clockwise, wrapping") {
  CHECK(p3a::core::compass_point(0) == 0);
  CHECK(p3a::core::compass_point(44) == 1);
  CHECK(p3a::core::compass_point(90) == 2);
  CHECK(p3a::core::compass_point(-90) == 6);
  CHECK(p3a::core::compass_point(-170) == 4);
  CHECK(p3a::core::compass_point(338) == 0);
  CHECK(p3a::core::compass_point(-23) == 7);
}

TEST_CASE("boss_trigger: the boxes on the way to a full moon's boss") {
  CHECK(boss_trigger("BP_FldHitActor_308_101_H0_Play_C"));
  CHECK(boss_trigger("BP_FldHitActor_305_101_H17_Play_C"));
  CHECK_FALSE(boss_trigger("BP_FldHitActor_308_101_H1_Play_C"));   // the bridge's other box: "no escaping now"
  CHECK_FALSE(boss_trigger("BP_FldHit_Tartarus_GateKeeper_C"));
  CHECK_FALSE(boss_trigger(""));
}
