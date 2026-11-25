#pragma once
// The sonar's sounds, made here: one short sound per kind of thing, each with a character of its own (so they are told
// apart by more than pitch) and energy across the spectrum (a pure tone gives the ears little to place ahead or
// behind). Mono, engine-free, all at one loudness. Where a kind has a sound file (file_cue below: Grim Dark's sonar
// sounds since 2026-11-13), the file is played and the one made here is its stand-in when the file is missing.
#include <vector>

namespace p3a::core {

enum class SonarCue {
  Exit,     // a way into another area: a breath of air rising through an opening, over a soft low thump
  Door,     // a room's door: one hollow knock on wood
  Person,   // someone to talk to: a whistled "yoo-hoo" in one breath, scooping up and falling a third
  Shop,     // a shop or vendor: two small bells a fifth apart struck together (a till's "ching")
  Thing,    // something to check or open: one warm plucked note
  Event,    // a spot that starts a fight or a scene when walked into: one hollow note leaping up a fourth ("bwip")
  Fragment, // a Twilight Fragment to pick up or strike loose: one shimmering chime of crystal, a sparkle
  Count
};

// The sound at `rate` Hz: one event (a knock, a strike, a note), starts and ends on silence, over 0.11 s and under
// 0.2 s, at the common loudness kCueLoudness (peak at most kCuePeak).
// brief: its form for a thing too near for the whole sound to fit its rhythm, under 0.092 s: the same sound, dying
// sooner.
std::vector<float> sonar_cue(SonarCue cue, int rate, bool brief = false);

// One tone of the trail that marks a stairway between floors (floors.cpp): kWaySteps of them are played one after
// another from places across the stairway's width, so the ear follows a line of sound from one side of the opening to
// the other and hears how wide it is. A small struck bar with a breath of noise at its start (something to place, as
// a pure tone gives little). The run climbs a pentatonic scale when the way leads up (`rise` > 0), comes down it when
// it leads down (< 0), and stays on one note for a way on the level. Under 0.12 s, at the cues' common loudness.
inline constexpr int kWaySteps = 5;
inline constexpr double kWayStepS = 0.085;   // from one tone's start to the next
std::vector<float> way_tone(int rate, int step, int rise);

// How loud a cue sounds (ITU-R BS.1770's K-weighting, over its loudest 100 ms, silence after it counted), as an RMS.
// Every cue and signal is made to this one level, so none stands out by being bright or quiet by being short.
double cue_loudness(const std::vector<float>& v, int rate);
// The old set's middle (they ran 0.087 to 0.186, 6.6 dB apart: the sparkle and the bell loudest, the layer's tick
// quietest), so the mix around them is as it was.
inline constexpr double kCueLoudness = 0.13;
inline constexpr double kCuePeak = 0.9;

// The mod's other signals, made the same way and at the same loudness (they were plain sine and triangle beeps). The
// Shadow's growl is 0.28 s, the rest under 0.2 s:
enum class SignalCue {
  Shadow,   // a Shadow near: a low, rattling snarl that dies away
  Ambush,   // the strike will land from behind: one glassy tick that flicks up a fifth
  Layer,    // the controller's mod layer opened: one soft, low glass tick
  Reach,    // a Shadow or a breakable thing is within the strike's reach: a quick ting of steel, repeated fast
  Spotted,  // a Shadow has noticed the hero: an alarm, one buzzing note jumping up a tritone
  Lost,     // it has lost him again: one soft note sinking a fourth
  Count
};
std::vector<float> signal_cue(SignalCue cue, int rate);

// The nearest Shadow's held sound (the user, 2026-11-15: one constant sound, its facing told by something other than
// pitch): a low, rough, breathing snarl that loops seamlessly, kDroneSeconds long, with energy up to a few kHz so a
// low-pass darkening it is plain to hear. At the cues' common loudness.
inline constexpr double kDroneSeconds = 1.0;
std::vector<float> drone_loop(int rate);

// A cue from a sound file instead (the user, 2026-11-13: Grim Dark's sonar sounds, assets/audio/sonar and
// assets/audio/signals): `v` decoded to mono at `rate`. The silence at its ends is cut, then it is finished like the
// made ones: soft ends, no DC, the common loudness (peak at most kCuePeak). brief: cut to kFileBriefS first, so it
// fits the fastest rhythm. Empty for a silent file.
inline constexpr double kFileBriefS = 0.088;
std::vector<float> file_cue(std::vector<float> v, int rate, bool brief = false);

}  // namespace p3a::core
