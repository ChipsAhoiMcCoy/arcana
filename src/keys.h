#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace p3a::keys {
// The mod's own keys. Handlers run on the game thread from the window procedure; a bound key is swallowed (down,
// repeat, char and up) so the game never sees it. Modifiers: exact match.
enum Mods : int { None = 0, Shift = 1, Ctrl = 2, Alt = 4 };
using Handler = std::function<void()>;
// in_help false: F1 leaves it out while it and its plain key are where the mod put them (a Shift variant the plain
// key's help speaks for: "Shift goes back").
void bind(uint32_t vk, int mods, const char* name, const char* help, Handler h, bool repeat = false, bool in_help = true);
void install();   // after every bind: loads the player's own keys (keys.ini)
// The player's own keys (the mod menu's Mod keys page). A binding is an index; only keyboard ones are listed.
std::vector<int> keyboard_bindings();     // every rebindable binding, in the order bound
std::string binding_help(int i);          // what it does
std::string binding_key(int i);           // its key now ("Shift+1")
bool binding_default(int i);              // still on the mod's own key
std::string key_label(uint32_t vk, int mods);
std::string key_of(const char* name);     // that binding's key now ("Period"), or "" for no such binding
// A hint naming the mod's keys: each {binding.name} becomes that binding's key now, so a moved key is said where it
// is (strings.h writes the hints with them: "{nav.walk.period} walks to..."). An unknown name stays as written.
std::string fill(std::string_view text);
bool is_key(const char* name, uint32_t vk, int mods);   // that binding is on this key now
bool reserved(uint32_t vk, int mods);     // the game's own (walking, act, back, menu) or a Ctrl / Alt chord
// A Shift "go back" binding that follows a plain one (Shift+Comma after Comma): left off the Mod keys page, always
// Shift with its plain key's key. After both are bound.
void shift_back(const char* back_name, const char* plain_name);
int back_of(int i);                       // binding i's Shift back, or -1
int plain_of(uint32_t vk, int mods);      // the plain binding whose back is on this key, or -1
// Moves binding i (and its back) to the key and saves; bindings already there take the keys it left (`moved`:
// the listed ones that moved). NeedsNoShift: i has a back, so its key takes no Shift. BackKey: another pair's back.
enum class Rebind { Done, NeedsNoShift, BackKey, Refused };
Rebind rebind(int i, uint32_t vk, int mods, std::vector<int>& moved);
Rebind reset_binding(int i, std::vector<int>& moved);   // back to the mod's key, as rebind
void reset_all();
std::string help();   // every binding: keyboard keys, or the controller's mod layer while the player is on a pad
// The controller's mod layer (both triggers held, input.cpp): a binding's button there (XINPUT_GAMEPAD_* mask).
void bind_pad(const char* name, uint16_t button);
void on_pad_layer(Handler h);           // the layer opened
void pad(uint16_t button, bool repeat, bool layer = true); // a button pressed in the layer, or 0 = the layer opened (game thread)
// A mod menu that takes every key and button while open (the settings menu): no bindings run, the game gets nothing
// (keys swallowed here, buttons hidden by input::set_modal). nullptr clears.
using ModalKey = std::function<void(uint32_t vk, bool repeat)>;
using ModalPad = std::function<void(uint16_t button, bool repeat)>;
void set_modal(ModalKey key, ModalPad pad);
// A screen that takes every controller button for a while (the contract's on-screen keyboard; input::set_pad_capture
// hides them from the game) but those pressed in the layer (both triggers), which stay the mod's keys. The keyboard is
// left alone; the settings menu's modal goes first. nullptr clears.
void set_pad_capture(ModalPad pad);
// A screen that takes some of the game's own keys (unmodified presses only): return true to swallow the key from the
// game (down, repeat, char and up). Runs before the mod's bindings. nullptr clears.
using CaptureKey = std::function<bool(uint32_t vk, bool repeat)>;
void set_capture(CaptureKey key);
// A box of the mod's that waits for the player over a paused scene (a description, ad.cpp): unmodified presses, before
// the menu, the capture and the bindings; true swallows the key from the game. nullptr clears.
void set_prompt(CaptureKey key);
// The bespoke menu's keys (screens/menu.cpp): every key down with its modifiers, before the capture and the
// bindings; true swallows it. Keys the mod injects for the game (input::inject_key) never reach it.
using MenuKey = std::function<bool(uint32_t vk, int mods, bool repeat)>;
void set_menu(MenuKey key);
// The player's own presses of keys the game gets, as the window procedure sees them (keys the mod posts are not counted).
// Alt held (the walk key, walkmode.cpp): its own down and up are swallowed, so Windows never opens the window's
// system menu on its release, and it is no modifier for the mod's keys (they work while walking). Let go when the
// window loses the keyboard.
bool alt_held();
bool movement_key_down();   // W/A/S/D or the arrow keys, from the real keyboard: cancels auto-walk
uint64_t game_key_ms();     // when the player last pressed a key the game gets (not a mod key), or 0
uint32_t movement_presses(uint32_t vk);   // how many times that movement key has been pressed (no auto-repeats)
}  // namespace p3a::keys
