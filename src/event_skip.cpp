// The game's skip prompt in an event scene.
// Read here (this build's layout, measured in the fusion's scene LS_Event_Qest_600_110_C, 2026-11-25):
//  - AAtlEvtEventManager (one per event level, BP_AtlEvtEventManager_C): +0x28C the skip prompt's state: 0 none, 7
//    while the prompt shows and the scene stands paused (the skip button's first press; cancel puts it back to 0, the
//    scene's time unchanged; the second press skips and it goes to 0 too); +0x2AC 1 while the scene can still be
//    skipped (0 once it was), +0x2B0 the time in seconds the skip jumps to (18.83 in the fusion: the new Persona
//    appearing). Other values are not the prompt: the game over scene holds 1 while its poem runs (2026-11-25: read
//    as a prompt, "Paused" was said over the poem with nothing pressed, and "Resumed" cut into its reading).
#include "event_skip.h"
#include "core/strings.h"
#include "seh.h"
#include "speech.h"
#include "ue/ue.h"
#include "watch.h"
#include <cstdint>

namespace p3a::event_skip {
using namespace ue;
namespace {
constexpr int kPrompt = 7;   // +0x28C while the skip prompt shows
// state: the prompt's; can: the scene can still be skipped. False without a live event manager.
bool read(int& state, bool& can) {
  static const int id = watch::want("AtlEvtEventManager", true);
  if (!known_build()) return false;
  UObject* m = watch::get(id);
  if (!m || !is_live(m)) return false;
  return guarded([&] {
    state = *(int32_t*)((uint8_t*)m + 0x28C);
    can = *((uint8_t*)m + 0x2AC) != 0;
  });
}
}  // namespace

bool prompt() {
  int state = 0; bool can = false;
  return read(state, can) && state == kPrompt && can;
}

void tick() {
  static bool was = false;
  int state = 0; bool can = false;
  const bool live = read(state, can);
  const bool now = live && state == kPrompt && can;
  if (now && !was) speech::speak(strings::kSkipPrompt(), true);
  // Gone with the scene still skippable: cancelled, the scene plays on. Gone because it was skipped (or the scene
  // ended): what comes next speaks for itself.
  else if (!now && was && live && can) speech::speak(strings::kSkipResumed.c_str(), true);
  was = now;
}
}  // namespace p3a::event_skip
