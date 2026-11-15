// Altered from Grim Dark (GD Access) by Austin Hicks; zlib, see LICENSES/. This is not the original software.
#pragma once
#include <string>
#include <cstdint>
#include <string_view>
#include <vector>
#include "ring.h"
namespace p3a::speech {
bool init();            // loads prism, picks the best available backend
void shutdown();
void speak(std::string_view utf8, bool interrupt = true);
// Distinct facts read as a list (a status line: the date, the area, the money): each its own utterance, so the
// screen reader pauses between them as it does between lines; one long string runs them together (the player's ear,
// 2026-11-14). The first interrupts when asked; empty parts are skipped.
void speak_parts(const std::vector<std::string>& parts, bool interrupt = true);
void stop();
// The player pressed a button or key: what is being said stops, as a screen reader stops its speech on a key, so a
// confirm does not leave a description reading into what comes next (the player on a controller, 2026-11-15). A key
// stops speech only on a speech engine (SAPI, OneCore): a screen reader does that itself.
void player_pressed(bool keyboard);
uint64_t count();      // lines spoken so far (a reader can tell whether anything else spoke since its last line)
int speaking();         // 1 speaking, 0 quiet, -1 the backend cannot tell (or muted)
const char* backend_name();
void set_muted(bool m);  // muted: nothing reaches the backend, but history still records
bool muted();
std::string timing();   // the backend's slowest speak call (/health)
std::vector<uint64_t> bench(int n);   // dev: n interrupting calls with a single space, each call's microseconds
LineRing& history();     // the last 500 lines passed to speak(), for the dev server
}  // namespace p3a::speech
