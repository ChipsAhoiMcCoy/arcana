#pragma once
#include <string>

namespace p3a::ad {
// Audio description of the animated story movies (src/ad.cpp): the movie clock, and the narrator that
// follows it. Game thread.
struct Clock {
  bool playing = false;
  bool paused = false;
  std::string movie;   // the movie file's name less ".usm", e.g. MS_Event_Main_100_030_M_Movi_VP9 (else the source's name)
  double time = 0;     // GetTime: seconds into the movie
  int frame = -1;      // GetFrameNumber
  int audio_track = -1;   // 0 Japanese voices, 1 English
  bool event = false;  // a scene played in the engine (its LevelSequence's clock; movie = the sequence's name)
  bool fast = false;   // the scene is fast-forwarded: still playing, but no description is said over it
};
// A description's box holds the movie or scene paused (or has just let it go): the pause is the mod's, not the
// player's (the movie screen says nothing of it).
bool holding();
// The playing movie's or scene's clock.
Clock clock();
void tick();                                   // every frame: follow the movie, play its descriptions
std::string selftest(const std::string& filter);   // decode every packed clip and check its length (any thread)
void register_routes();
// The mod is being unloaded (any thread, before the DLL is freed): waits for the clip decoders' worker threads to
// end, so none is left running code that is about to go away.
void unload();
}  // namespace p3a::ad
