#pragma once
#include <cstdint>
#include <utility>
#include <vector>

namespace p3a::screens {
// "Next" (or the game sound the setting VoiceEndSound picks) once a screen takes OK: the stats panel, an item got,
// a Social Link card, the victory pages. Not when the screen opens: their animations play first and OK does nothing
// until they are done (the stats panel said "Next" 2 s before it took OK, 2026-11-14).
// The screen says when it can (`ready`: its own state or key help). Unless told the game's sign alone is enough, the
// cue also waits for the game itself to start asking for the decide button (confirm.h) from code that was not
// already asking before the screen opened (the field, a message window under it). There is no time limit to fall
// back on (no timers in menus, the user's call 2026-11-14): if the game gives no sign the mod can see, no cue.
// Code asking is not always a sign: a screen whose handler asks from its first frame and drops the press until its
// own animation is done (the stats panel) passes that state as `ready` with `game_sign_enough`.
class NextCue {
 public:
  explicit NextCue(const char* who) : who_(who) {}
  void arm();                                 // the screen opened: the cue is due once it takes OK
  void disarm();                           // gone, or the cue no longer wanted (said already)
  bool armed() const { return armed_; }
  // Every tick while the screen is current. `ready`: the screen's own sign it takes OK. `game_sign_enough`: that sign
  // is the game's own (the victory screen's OK key help), so the pad queries are not waited for.
  void tick(bool ready, bool game_sign_enough = false);
 private:
  const char* who_;
  bool armed_ = false, given_ = false, sound_due_ = false;
  uint64_t armed_ms_ = 0, armed_frame_ = 0;
  std::vector<uintptr_t> before_;   // code asking for the decide button before the screen opened
  std::vector<std::pair<uintptr_t, uint64_t>> first_;   // code asking since it opened, and the frame it began
  void give(const char* why, uintptr_t caller);
};
}  // namespace p3a::screens
