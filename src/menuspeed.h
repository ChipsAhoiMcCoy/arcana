#pragma once
#include <string>

namespace p3a::menuspeed {
// Fast menus (the "Menu animation speed" setting): while a menu is up, the game's world time runs faster
// (GameplayStatics.SetGlobalTimeDilation), so the menus' own timers (opening slides, transitions, the waits before a
// menu takes input) and the scenes behind them (the Velvet Room's fusion) finish sooner. The game's menu sounds are
// played by its input and its state changes, not by the clock, so they stay.
//  - A menu: the current screen is a bespoke menu (MenuScreen), or the camp is the innermost pause (its transitions
//    between the root and a submenu included).
//  - Never in a battle (the game sets its own time dilation there), a story scene, or under a message window (a
//    voiced line would fall behind its scene).
//  - The game's own value is given back when the menu closes; a value the game set meanwhile is left alone.
void tick();       // game thread, after the screens
void install();    // dev route /menuspeed
void shutdown();   // the unload: the game's value given back
}  // namespace p3a::menuspeed
