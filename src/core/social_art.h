#pragma once
#include <string>

namespace p3a::core::social_art {
// The picture the camp's Social Link menu draws beside a link (T_UI_Camp_Commu_Bustup_<id>, 28 of them, inked in
// blue and white): written descriptions, each from the picture itself (2026-11-18). Engine-free.
// The game's choice (FUN_141300ba0): the Fool shows one of six team collages, one more face for each member who has
// joined (`fool_members`, 0..5); the Hierophant shows the old man, or the old woman while the cursor is on her
// (`person` 1); every other arcana has its own. Arcana ids as the game's (1 Fool .. 22 Aeon). -1 when none.
int picture(int arcana, int person, int fool_members);
std::string describe(int picture);   // "" when out of range
int pictures();                      // 28
}  // namespace p3a::core::social_art
