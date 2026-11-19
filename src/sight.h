#pragma once
#include <string>

namespace p3a::sight {
// Where Tartarus Shadows can see the hero, in sound (the Shadow sight setting):
//  - the edge: each nearby Shadow's sight sizzles from its point nearest the hero, louder and higher as that edge
//    nears, within the Shadow sight range;
//  - hidden: a muffled hum while the hero stands inside a Shadow's sight but a wall blocks its view.
// The sight is the game's own test, read live from each Shadow (its search distances and angles for its mood, the
// cone for the hero's pace, the trace walls block). Shadows already hunting the hero are left out.
void tick();      // game thread, with no screen or message up; plays only while the player walks the field
void install();   // dev route /sight
// The sound test: 1.2 s of one sound. 0: a zone halfway through the range; 1: at its edge; 2: hidden.
void demo(int which);
}  // namespace p3a::sight
