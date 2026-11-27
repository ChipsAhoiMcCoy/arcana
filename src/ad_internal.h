#pragma once
// What ad.cpp shares with its in-game test, ad_test.cpp (/ad/test, the packed clips' selftest): the described
// movie, its schedule and every cue's last play. Game thread. Not for other files.
#include "core/ad_schedule.h"
#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace p3a::ad {
namespace sched = core::ad;

struct Scene {
  std::string key;
  std::string file;   // the movie's path under CriData/Stream ("#file" line)
  // "#wait" line: a battle scene whose descriptions wait for Enter like a story scene's (a boss's entrance, a big reveal,
  // a first summon: the user's call, 2026-11-26); the rest of a battle's scenes are played over
  bool wait = false;
  std::vector<sched::Cue> cues;
  std::vector<std::string> files, texts;
  std::vector<std::string> heard_ids;   // a 3D scene's: each cue's core::HeardCues id (empty for a movie)
  int left_out = 0;                     // cues left out as heard before (settings::SceneOnce)
  std::vector<std::shared_ptr<const std::vector<float>>> pcm;
  std::atomic<bool> ready{false};
  std::atomic<int> failed{0};
};

struct Run {   // one cue's last play, for /ad/status and the tests
  double started = -1;   // movie time
  size_t played = 0, total = 0;
};

extern std::shared_ptr<Scene> g_scene;   // the described movie or scene playing
extern sched::Schedule g_sched;
extern std::vector<Run> g_runs;
double seconds(int64_t ticks);   // a Mana FTimespan (100 ns ticks) in seconds
std::string data_dir();          // assets\ad\ beside the mod

// ad_test.cpp
void test_tick();             // each frame while a test runs
void register_test_route();   // /ad/test
}  // namespace p3a::ad
