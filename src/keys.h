#pragma once
#include <cstdint>
#include <functional>
#include <string>
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
bool is_key(const char* name, uint32_t vk, int mods);   // that binding is on this key now
bool reserved(uint32_t vk, int mods);     // the game's own (walking, act, back, menu) or a Ctrl / Alt chord
// Moves binding i to the key and saves; a binding already on that key takes i's old one (returned, else -1).
int rebind(int i, uint32_t vk, int mods);
int reset_binding(int i);                 // back to the mod's key, as rebind
void reset_all();
std::string help();   // every binding: keyboard keys, or the controller's mod layer while the player is on a pad
// The controller's mod layer (both triggers held, input.cpp): a binding's button there (XINPUT_GAMEPAD_* mask).
void bind_pad(const char* name, uint16_t button);
void on_pad_layer(Handler h);           // the layer opened
void pad(uint16_t button, bool repeat); // a button pressed in the layer, or 0 = the layer opened (game thread)
// A mod menu that takes every key and button while open (the settings menu): no bindings run, the game gets nothing
// (keys swallowed here, buttons hidden by input::set_modal). nullptr clears.
using ModalKey = std::function<void(uint32_t vk, bool repeat)>;
using ModalPad = std::function<void(uint16_t button, bool repeat)>;
void set_modal(ModalKey key, ModalPad pad);
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
bool movement_key_down();   // W/A/S/D or the arrow keys, from the real keyboard: cancels auto-walk
uint64_t game_key_ms();     // when the player last pressed a key the game gets (not a mod key), or 0
uint32_t movement_presses(uint32_t vk);   // how many times that movement key has been pressed (no auto-repeats)
}  // namespace p3a::keys
