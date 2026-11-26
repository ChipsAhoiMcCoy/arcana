#pragma once
#include <vector>
#include "ue/ue.h"

namespace p3a::shadow {
// The Shadows roaming a Tartarus floor, in sound (the Shadow alerts setting):
//  - the nearest within 30 m snarls steadily from where it is, louder as it closes in and higher while it hunts the
//    hero: bright facing him, duller as it turns away, wobbling too once he is behind it (a strike's advantage);
//  - a Shadow that loses him again sounds a falling note (the game's own sound says it noticed him);
//  - while a Shadow stands inside the reach of the hero's strike (the game's own hit area) a blade's ring repeats:
//    the strike will connect. From behind it, the ring is two rising ticks instead: the strike brings the advantage.
void tick();      // game thread, with no screen or message up; the cues only while the player walks the field
void install();   // dev route /shadows
// The Relaxed Reaper rate option changed: doubles (on) or halves (off) what is left of the Reaper's timers on this
// floor. Game thread.
void set_relaxed_reaper(bool on);
// The Always advantage option: a battle a roaming Shadow starts begins with the party's advantage, however the two
// met. Game thread, every frame (field and battle).
void advantage_tick();
// The sound test: 1.5 s of the nearest Shadow's snarl, ahead. 0 facing the hero, 1 hunting him, 2 its back turned.
void demo(int which);
// The enemy manager's list (AFldEnemyManager.Enemies, FFldEnemyHolder): each Shadow's actor beside the component
// that holds its state. Every entry as the game has it (either pointer may be null); empty off a Tartarus floor.
// A breakable thing (Tartarus' Shadow remains) the hero's strike would break, turned to face it from where he stands
// (`me`): the strike's box turned round him toward it meets its Box. `yaw` is that facing. Game thread.
bool strike_reaches(ue::UObject* breakable, const ue::FVector& me, float& yaw);
struct Holder { ue::UObject* actor; ue::UObject* comp; };
std::vector<Holder> enemy_holders();
}  // namespace p3a::shadow
