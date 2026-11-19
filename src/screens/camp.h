#pragma once
// The camp menu's place among the game's pauses (camp.cpp).
namespace p3a::screens {
int pause_top();            // the innermost pause, an EAppPauseType: 1 Camp, 2 TownMap, 3 DialogueLog; 0 none
bool camp_open();           // the camp menu is the innermost pause
bool camp_submenu_open();   // one of the camp root's submenus is open
// The mod's own pause (the mod menu): on, the camp's pause is pushed on the game's stack, so the field stands still as
// under the camp menu (only in free roam: over no pause of the game's); off, it is taken off again. pause_top() and
// camp_open() look past it.
void hold_pause(bool on);
void pause_tick();          // game thread: a release that waited for a pause of the game's over the mod's
}  // namespace p3a::screens
