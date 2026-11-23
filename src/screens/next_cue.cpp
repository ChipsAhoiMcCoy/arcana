#include "screens/next_cue.h"
#include "confirm.h"
#include "core/strings.h"
#include "log.h"
#include "settings.h"
#include "speech.h"
#include "voice.h"
#include <windows.h>
#include <format>
#include <string>

namespace p3a::screens {

void NextCue::arm() {
  armed_ = true;
  given_ = sound_due_ = false;
  armed_ms_ = GetTickCount64();
  armed_frame_ = confirm::frame();
  first_.clear();
  // Asking in the 2 s before the screen, up to 4 frames before it: code that was there already. A screen that began
  // asking in the frames just before the mod saw it open is its own, not the field's.
  before_ = confirm::callers(armed_frame_ > 250 ? armed_frame_ - 250 : 0, armed_frame_ > 4 ? armed_frame_ - 4 : 0);
}

// What asked for OK while the screen was up, for the log: how a screen the game gave no sign on can get its own.
void NextCue::disarm() {
  if (armed_) {
    std::string seen;
    for (auto [c, f] : first_) {
      bool old = false;
      for (uintptr_t b : before_) old |= b == c;
      seen += std::format(" exe+{:#x}{}", c, old ? std::string("(before)") : std::format("(from frame {})", f - armed_frame_));
    }
    log::writef("next: {} closed after {} ms, {}; asking for OK:{}", who_, (unsigned)(GetTickCount64() - armed_ms_),
                given_ ? "cue given" : "no cue", seen.empty() ? " nothing" : seen);
  }
  armed_ = false;
  sound_due_ = false;
}

void NextCue::give(const char* why, uintptr_t caller) {
  given_ = true;
  unsigned ms = (unsigned)(GetTickCount64() - armed_ms_);
  if (caller) log::writef("next: {} takes OK after {} ms ({}, exe+{:#x} asks)", who_, ms, why, caller);
  else log::writef("next: {} takes OK after {} ms ({})", who_, ms, why);
  int end = settings::get(settings::VoiceEndSound);
  if (end == settings::EndOff) return;
  if (end == settings::EndNext) { speech::speak(strings::kNext.c_str(), false); return; }   // queued behind any reading
  sound_due_ = true;   // a sound waits for the reading to end
}

void NextCue::tick(bool ready, bool game_sign_enough) {
  if (sound_due_) {
    // The reading said before the cue ends first (NVDA cannot tell: -1, the sound goes at once).
    if (speech::speaking() != 1) { voice::play_end_sound(); sound_due_ = false; }
  }
  if (!armed_) return;
  // Each caller's first frame of asking while up: when the screen's own code began taking OK, for the closing line.
  uint64_t now = confirm::frame();
  for (uintptr_t c : confirm::callers(now > 0 ? now - 1 : 0, now)) {
    bool known = false;
    for (auto& e : first_) known |= e.first == c;
    if (!known) first_.push_back({c, now});
  }
  if (given_) return;
  if (!ready) return;
  if (game_sign_enough) { give("its own sign", 0); return; }
  // No timer stands in for the game's sign (the user's call, 2026-11-14): a screen the game gives none on stays
  // quiet, and its closing log line names what asked for OK, to find its own sign from.
  if (uintptr_t c = confirm::new_caller(before_)) give("the game asks for OK", c);
}
}  // namespace p3a::screens
