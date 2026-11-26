#pragma once
// What nav.cpp shares with its dev half, nav_dev.cpp (the /strike and /nav routes, the direct movement experiments):
// the walk's planning pieces the /nav route runs on its own, and its steering state. Not for other files.
#include "core/boxes.h"
#include "world.h"
#include <cstdint>
#include <string>
#include <vector>
#include <windows.h>

namespace p3a::nav {
using world::FVector;

// How the walk steers (nav.cpp, steering): auto (directly once the game is seen to take it, else keys), native, keys.
enum class Drive { Auto, Native, Keys };
extern Drive g_drive;      // dev: /nav?drive=
extern int g_native;       // direct movement: 0 not seen yet, 1 the hero moves by it, -1 ignored
extern uint32_t g_held[2];   // the movement keys the walk holds down

float flat(const FVector& a, const FVector& b);
void hero_body(float& radius, float& half);
// The floor under the hero (nav.cpp, off the floor's navmesh).
FVector feet_of(const FVector& me);
bool on_floor_nav(const FVector& me, FVector* at = nullptr);
bool way_onto_floor_nav(const FVector& me, FVector& out);

// A walk's target: its trigger box when it has one, else its location (nav.cpp, the ways in).
struct Goal { bool has_box = false; core::Box box{}; FVector at{}; };
FVector centre(const Goal& g);
Goal goal_of(ue::UObject* t);
bool sweep_reaches(const Goal& g, const FVector& from, const FVector& me, float radius, float half,
                   std::vector<ue::UObject*>& people);
std::vector<FVector> find_entries(const Goal& g, const FVector& me, std::string* report = nullptr);
bool body_plan(const Goal& g, const FVector& me, std::vector<FVector>& out, std::string* report = nullptr, bool past_people = false);

// nav_dev.cpp
void dev_tick(ULONGLONG now);   // the direct movement experiments, each tick
void install_dev();             // the /strike and /nav routes
}  // namespace p3a::nav
