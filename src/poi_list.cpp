// The points-of-interest list the review keys walk: its categories, the selection, and what each key says.
// Categories (left and right) each hold their points of interest nearest first (up and down). Changing category
// selects the nearest; opening the controller's mod layer says the selection, or selects the nearest when there is
// none; an empty category is skipped.
// Read here: the selected actor's own place (K2_GetActorLocation) and bHidden; everything else comes from poi::scan.
#include "poi_internal.h"
#include "core/poi_text.h"
#include "core/strings.h"
#include "core/units.h"
#include "doors.h"
#include "seh.h"
#include "sonar.h"
#include "speech.h"
#include "world.h"
#include <cmath>
#include <format>

namespace p3a::poi {
using namespace ue;

// Top-down, the bearing is from north and said by the compass; else by the clock face, from the camera.
std::string clock(float b) {
  if (world::north_up()) return strings::kCompass[core::compass_point(b)].c_str();
  return std::format("{} {}", core::clock_hour(b), strings::kOClock);
}

std::string describe(const Poi& p) {
  // The name stands alone, a way into another area's too: it is where it leads, and its category says what it is
  // ("Gekkoukan High School exit" was taken for the way out of the school; the user's call, 2026-11-09).
  std::string who = p.state.empty() ? p.name : p.name + ", " + p.state;
  return std::format("{}, {}, {}", who, core::meters(p.dist / 100.0f), clock(p.bearing));
}

enum class Cat { Exits, Doors, People, Shops, Things, Events, Shadows, Count };
static_assert((int)Cat::Count == 7, "strings::kPoiCategory has a name per category, in order");
static const char* cat_name(Cat c) { return strings::kPoiCategory[(int)c]; }
static Cat g_cat = Cat::Exits;
static WeakObj g_sel;
static Poi g_sel_poi;   // what the list said about it: selected() refreshes the place

static bool in_cat(const Poi& p, Cat c) {
  switch (c) {
    case Cat::Exits: return p.kind == Kind::Exit;
    case Cat::Doors: return p.kind == Kind::Door;
    case Cat::People: return p.kind == Kind::Person;
    case Cat::Shops: return p.kind == Kind::Shop;
    case Cat::Things: return p.kind == Kind::Thing || p.kind == Kind::Fragment;   // a fragment is an object with its own sound
    case Cat::Events: return p.kind == Kind::Event;
    default: return p.kind == Kind::Enemy;
  }
}

bool in_selected_category(const Poi& p) { return in_cat(p, g_cat); }

static std::vector<Poi> in_category(const std::vector<Poi>& all, Cat c) {
  std::vector<Poi> v;
  for (auto& p : all) if (in_cat(p, c)) v.push_back(p);
  return v;   // scan() sorts nearest first
}

// The current category, or the next one in `delta`'s direction that has something (staying put when it does).
static std::vector<Poi> settle(const std::vector<Poi>& all, int delta, bool move) {
  int c = core::settle_category((int)g_cat, (int)Cat::Count, delta, move, [&](int cat) {
    for (auto& p : all) if (in_cat(p, (Cat)cat)) return true;
    return false;
  });
  if (c < 0) return {};
  g_cat = (Cat)c;
  return in_category(all, g_cat);
}

// "Exits, Iwatodai Station, 6 meters, 2 o'clock, 1 of 3": list[i] selected. The category is said once, first, as the
// list enters it (a bracket key, the controller's layer opening); moving within it says the thing alone (the user,
// 2026-11-14: the type on every point was in the way). Comma and the number keys never say it: said first it held up
// the thing itself (a player, 2026-11-18: "exits, door to wherever"; the user: the thing tells what it is).
static void announce_at(const std::vector<Poi>& list, size_t i, bool with_cat) {
  g_sel = list[i].obj;
  g_sel_poi = list[i];
  // A story beat is named "Event: Jin"; in the Events category it said "Event" twice (Adamah, 2026-11-13).
  Poi said = list[i];
  if (std::string head = std::string(strings::kPoiEvent) + ": "; g_cat == Cat::Events && said.name.starts_with(head)) said.name.erase(0, head.size());
  std::string text = std::format("{}, {}", describe(said), strings::of(i + 1, list.size()));
  speech::speak(with_cat ? std::format("{}, {}", cat_name(g_cat), text) : text, true);
  sonar::selected(list[i]);   // its sound, from where it is
}

static void announce_nearest(const std::vector<Poi>& list) {
  if (list.empty()) { speech::speak(strings::kNothingNearbyFull.c_str(), true); g_sel = {}; return; }
  announce_at(list, 0, true);
}

// The list is of the field the player is walking: in a menu, a conversation, a battle or a scene its keys say so.
static bool in_field() {
  if (world::exploring()) return true;
  speech::speak(strings::kNotInField.c_str(), true);
  return false;
}

void next(int delta) {
  if (!in_field()) return;
  auto all = scan();
  Cat was = g_cat;
  auto list = settle(all, 1, false);
  int cur = -1;
  for (size_t i = 0; i < list.size(); ++i) if (list[i].obj == g_sel) cur = (int)i;
  if (list.empty() || g_cat != was || cur < 0) { announce_nearest(list); return; }
  int n = (int)list.size();
  int i = ((cur + delta) % n + n) % n;
  g_sel = list[i].obj;
  g_sel_poi = list[i];
  speech::speak(std::format("{}, {}", describe(list[i]), strings::of(i + 1, n)), true);
  sonar::selected(list[i]);
}

void next_category(int delta) {
  if (!in_field()) return;
  announce_nearest(settle(scan(), delta, true));
}

// The controller's layer opening: the selection, where it still is in the list. It selected the nearest every time, so
// a point chosen, the triggers let go, then A (walk) walked to the nearest instead (Adamah, 2026-11-13).
void announce_list() {
  auto list = settle(scan(), 1, false);
  for (size_t i = 0; i < list.size(); ++i)
    if (list[i].obj == g_sel) { announce_at(list, i, true); return; }
  announce_nearest(list);
}

// Comma / Shift+Comma: every point of interest of any kind, nearest first. The first press lands on the nearest (Shift:
// the farthest, as Grim Dark's review keys enter a list); while the selection is still Comma's, each press moves on
// from it, wrapping. Said as the list says it, its position counted in the whole list ("Vending Machine, 3 meters,
// north, 2 of 9", no category), and its category becomes the list's. Nothing walks: Apostrophe or Period goes there once
// the player has heard what it is (the user, 2026-11-14: walking at once went somewhere unknown).
static WeakObj g_comma;   // what Comma last chose
void cycle_nearest(int dir) {
  if (!in_field()) return;
  auto all = scan();   // nearest first
  if (all.empty()) { speech::speak(strings::kNothingNearbyFull.c_str(), true); g_sel = {}; return; }
  const int n = (int)all.size();
  int cur = -1;
  if (g_comma == g_sel) for (int i = 0; i < n; ++i) if (all[(size_t)i].obj == g_sel) cur = i;
  const int i = cur < 0 ? (dir >= 0 ? 0 : n - 1) : ((cur + dir) % n + n) % n;
  for (int c = 0; c < (int)Cat::Count; ++c) if (in_cat(all[(size_t)i], (Cat)c)) { g_cat = (Cat)c; break; }
  g_comma = all[(size_t)i].obj;
  announce_at(all, (size_t)i, false);
}

// The number keys, one a category (Grim Dark's review keys: one key a kind of thing). The first press selects the
// category's nearest (Shift: its farthest); while the selection is in that category, each press moves on from it,
// wrapping. The key named the category, so it is not said; an empty one says so and keeps the selection.
void cycle_category(int cat, int dir) {
  if (!in_field() || cat < 0 || cat >= (int)Cat::Count) return;
  auto list = in_category(scan(), (Cat)cat);
  if (list.empty()) { speech::speak(strings::fmt(strings::kNoneOfFmt, cat_name((Cat)cat)), true); return; }
  const int n = (int)list.size();
  int cur = -1;
  if (g_cat == (Cat)cat) for (int i = 0; i < n; ++i) if (list[(size_t)i].obj == g_sel) cur = i;
  g_cat = (Cat)cat;
  announce_at(list, (size_t)(cur < 0 ? (dir >= 0 ? 0 : n - 1) : ((cur + dir) % n + n) % n), false);
}

// The selection as it is now, from its own actor: a rescan could miss it (an Event trigger is only listed when nothing
// else is near) and paid a navmesh query per far-off hit actor on every read.
bool selected(Poi& out) {
  UObject* a = g_sel.resolve();
  if (!a || get_bool(a, "bHidden")) return false;   // a defeated or parked Shadow
  world::FVector me, v{};
  if (!world::player_location(me) || !guarded([&] { v = world::actor_location(a); })) return false;
  if (doors::behind(a, me, v)) return false;   // the hero has gone through a door since: it is not in the list now
  out = g_sel_poi;
  out.loc = v;
  out.dist = std::sqrt((v.x - me.x) * (v.x - me.x) + (v.y - me.y) * (v.y - me.y) + (v.z - me.z) * (v.z - me.z));
  out.bearing = world::bearing(me, v);
  return true;
}
}  // namespace p3a::poi
