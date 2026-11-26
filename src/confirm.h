#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace p3a::confirm {
// When does the game take OK? Every screen of the game asks its pad layer "was the decide button pressed?" through a
// few small functions (exe+0x10a8890..0x10a8a00: (button, key) on, trigger, repeat...), and only while that press would
// do something. The decide button is a pad id the button layout sets (exe+0x5393e60: 2 or 4, cancel the other at
// +0x5393e64). Hooking them gives, for each code address that asks, the mod frame it last asked in.
bool install();
uint64_t frame();   // the mod's frame now (hooks::frame)
// Code that asked for the decide button in frames [from, to] (exe offsets of the callers).
std::vector<uintptr_t> callers(uint64_t from, uint64_t to);
// The first caller asking in the last `recent` frames that is not in `except`; 0 if none.
uintptr_t new_caller(const std::vector<uintptr_t>& except, uint64_t recent = 3);
// The last mod frame a pad query called from code in exe [from, to) answered true, for any button (0: none yet):
// a screen's own key check firing ("the game saw its party key").
uint64_t answered(uintptr_t from, uintptr_t to);
std::string status();
}  // namespace p3a::confirm
