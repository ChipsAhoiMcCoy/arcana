#pragma once
#include <string>

namespace p3a::sight {
// Where Tartarus Shadows can see the hero, in sound (the Shadow sight setting):
//  - the edge: one sizzle for each way the player can push (ahead, right, behind, left, as the wall tones), louder as
//    a Shadow's sight comes within the warning band that way: walking that far would get the hero noticed;
//  - hidden: a muffled hum while the hero stands inside a Shadow's sight but a wall blocks its view.
// The sight is the game's own test, read live from each Shadow (its search distances and angles for its mood, the
// cone for the hero's pace, the trace walls block). Shadows already hunting the hero are left out.
void tick();      // game thread, with no screen or message up; plays only while the player walks the field
void install();   // dev route /sight
// The sound test: 1.2 s of one sound. 0..3: the edge ahead, right, behind, left; 4: hidden.
void demo(int which);
}  // namespace p3a::sight
