#pragma once
#include <string>
#include <vector>
#include "ue/ue.h"

// Floors of one field that the hero walks between (the Iwatodai Strip Mall's three, Club Escapade's two, Paulownia
// Mall's two): the game keeps which "part" of the field he is in and changes it when he walks through a slab across
// the stairway. The stairways are points of interest (poi.cpp lists what ways() gives), each heard as a run of tones
// across its width. The new floor itself is said by the arrival (the place banner shows it). Game thread.
namespace p3a::floors {
// The field part the game has the hero in (GET_FIELD_PARTS_ID: its floor in a building of floors), -1 when unknown.
int part();
// A stairway that leads on from the hero's part: the slab at its far end (walking into it changes the part).
// to: the part it leads to, the floor's number. rise: +1 it leads up, -1 down.
struct Way { ue::UObject* box = nullptr; int to = 0; int rise = 0; };
std::vector<Way> ways();
std::string name(const Way& w);   // "Stairs to floor 2"
// A walk-through slab that sets a field part (any of them, the hero's own side's too): never a point of interest by
// itself.
bool slab(ue::UObject* hit);
// The walk from the hero (at `me`) to the thing at `at` goes up or down a stairway to another floor: its path passes
// through a slab that sets another part than his. What "Same floor only" leaves out; height alone does not tell
// (Paulownia Mall's upper floor is a metre above the square). Worked out once per actor and kept while the hero stays
// in his part and on his side of the map's doors. False where the field has no such stairways.
bool elsewhere(ue::UObject* a, const ue::FVector& me, const ue::FVector& at);
bool stairways();   // the field has such stairways to another floor than the hero's: elsewhere() tells its floors apart
// The stairway's sound once: tones from one side of the slab to the other, from the listener's left to his right,
// rising for a way up and falling for a way down. focus: it plays through the sonar's solo. start_s: when it starts
// (audio::now_s's clock; 0 at once).
void trail(ue::UObject* box, int rise, bool focus, double start_s = 0);
inline constexpr double kTrailPeriodS = 1.5;   // from one run's start to the next, while a stairway keeps sounding
void demo();   // the sound test: a run of tones ahead, left to right, rising
void tick();   // the stairways near the hero sound while the sonar is on
void install();   // dev route /floors
}  // namespace p3a::floors
