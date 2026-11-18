#pragma once
// The game's data assets by name, for the story running. Most tables are loaded twice once Episode Aigis has been
// touched: the main story's (/Game/Xrd777/) and Episode Aigis's (/Game/Astrea/), same class and object name, so "the
// newest of the class" can be the wrong story's (or, for a shared class, another table: the enemies' affinities read
// as a Persona's, 2026-11-17). Every lookup of a Dat table or data asset goes through find().
#include "ue/ue.h"
#include <string_view>

namespace p3a::dat {
// Whether Episode Aigis is the story running: AstreaFuncLib.IsPlayingAstrea, the test the game's own table loaders
// make before taking the Astrea paths. Read once per frame. False when the function is missing.
bool astrea();
// The loaded object named `name` among the instances of watch handle `watch_id` (wanted with all = true), from the
// running story's set (core::pick_asset); the newest of the other set when only it is loaded. Logs once per name
// when more than one candidate is loaded, naming them. Resolved once per frame. Game thread.
ue::UObject* find(int watch_id, std::string_view name);
void install();   // the /dat route
}  // namespace p3a::dat
