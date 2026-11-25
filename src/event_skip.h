#pragma once

// The game's own skip of an event scene (a fusion's animation): the skip button first pauses the scene and shows
// "Skip" beside a pause mark at the bottom right; pressed again it skips, cancel resumes. The prompt is said when it
// comes up, and "Resumed" when it is cancelled. Game thread.
namespace p3a::event_skip {
bool prompt();   // the skip prompt is up: the scene stands paused by the game, waiting for skip or cancel
void tick();
}  // namespace p3a::event_skip
