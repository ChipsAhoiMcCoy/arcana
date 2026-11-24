#pragma once
// Achievements (achievements.cpp): an unlock is said, as Steam's overlay shows it.
namespace p3a::achievements {
void install();   // hooks the game's achievement request; /achievements dev route
void tick();      // says an achievement asked for while locked once Steam has it unlocked
}  // namespace p3a::achievements
