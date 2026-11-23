#pragma once

namespace p3a::walkmode {
// Walking on the keyboard: hold Alt (keys::alt_held), as Shift is held to dash. The game picks the hero's pace from how far the stick is pushed
// (FldPlayerComp, FUN_1411302c0): under PlayerData.InputWalkZone he walks, at or past it he runs, and with bEnableDash
// (the game's own Dash key, Shift / RT, checked first) he dashes. The keyboard always pushes all the way, so it
// could only run. While Alt is held, the hero's InputWalkZone is raised past a full push, so the same keys walk;
// Shift still dashes. The game's value is given back when Alt is let go, during the mod's auto-walk (it keeps its run
// pace) and at the unload.
bool on();         // walking now
void tick();       // game thread
void install();    // dev route /walkmode
void shutdown();   // the unload: the game's values given back
}  // namespace p3a::walkmode
