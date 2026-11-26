#include "doctest.h"
#include "core/ad_sim.h"

using namespace p3a::core::ad;

static std::vector<Cue> three() { return {{1.0, 2.0}, {4.0, 1.5}, {8.0, 3.0}}; }

TEST_CASE("ad: a clean run plays every cue in full, on time") {
  Scenario sc; sc.length = 12;
  SimResult r = simulate(three(), sc);
  CHECK(r.count(State::Done) == 3);
  for (size_t i = 0; i < 3; ++i) {
    CHECK(r.played[i] == doctest::Approx(three()[i].dur));
    CHECK(r.started[i] - three()[i].at < 0.05);
  }
}

TEST_CASE("ad: a pause holds the narrator and it still finishes") {
  Scenario sc; sc.length = 12; sc.pauses = {{1.8, 3.0}, {8.5, 0.5}};
  SimResult r = simulate(three(), sc);
  CHECK(r.count(State::Done) == 3);
  CHECK(r.played[0] == doctest::Approx(2.0));
}

TEST_CASE("ad: a short hitch does not lose a cue") {
  Scenario sc; sc.length = 12; sc.hitches = {{3.9, 0.3}};
  SimResult r = simulate(three(), sc);
  CHECK(r.count(State::Done) == 3);
}

TEST_CASE("ad: skipping the movie cuts the cue that is playing and skips nothing else silently") {
  Scenario sc; sc.length = 12; sc.stop_at = 4.2;   // cue 1 (4.0, 1.5 s long) has 1.3 s left
  SimResult r = simulate(three(), sc);
  CHECK(r.states[0] == State::Done);
  CHECK(r.states[1] == State::Cut);
  CHECK(r.reasons[1] == "the movie stopped");
  CHECK(r.states[2] == State::Pending);
}

TEST_CASE("ad: a jump forward skips the cues behind it, a rewind plays them again") {
  Scenario fwd; fwd.length = 12; fwd.seek_at = 1.5; fwd.seek_to = 7.0;
  SimResult r = simulate(three(), fwd);
  CHECK(r.states[0] == State::Cut);
  CHECK(r.states[1] == State::Skipped);
  CHECK(r.states[2] == State::Done);
  Scenario back; back.length = 12; back.seek_at = 9.0; back.seek_to = 3.0;
  r = simulate(three(), back);
  CHECK(r.states[1] == State::Done);
  CHECK(r.states[2] == State::Done);   // played again after the rewind
}

TEST_CASE("ad: joining a movie late skips what is already past") {
  Schedule s; s.load(three());
  auto a = s.step({true, false, 5.0}, {});
  CHECK(s.state(0) == State::Skipped);
  CHECK(s.state(1) == State::Skipped);   // 4.0 + kLate < 5.0
  CHECK(a.empty());
}

TEST_CASE("ad: overlapping cues are reported, not hidden") {
  SimResult r = simulate({{1.0, 3.0}, {2.0, 1.0}}, Scenario{.length = 6});
  CHECK(r.states[0] == State::Done);
  CHECK(r.states[1] == State::Missed);
}

TEST_CASE("ad: a seek while a cue plays stops the narrator") {
  Schedule s; s.load(three());
  auto a = s.step({true, false, 1.0}, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Play);
  CHECK(a[0].cue == 0);
  CHECK(s.playing() == 0);
  a = s.step({true, false, 7.0}, {true, false});   // the clock jumped over cue 1
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Stop);
  CHECK(a[0].cue == 0);
  CHECK(s.playing() == -1);
  CHECK(s.state(0) == State::Cut);
  CHECK(s.reason(0) == "the movie jumped");
  CHECK(s.state(1) == State::Skipped);
  CHECK(s.state(2) == State::Pending);
}

TEST_CASE("ad: a narrator that stops by itself leaves the cue cut, and the next one still plays") {
  Schedule s; s.load(three());
  s.step({true, false, 1.0}, {});
  auto a = s.step({true, false, 1.1}, {false, false});   // no clip sounding, and none reached its end
  CHECK(a.empty());
  CHECK(s.state(0) == State::Cut);
  CHECK(s.reason(0) == "the narrator stopped");
  a = s.step({true, false, 4.0}, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Play);
  CHECK(a[0].cue == 1);
}

TEST_CASE("ad: a movie that ends during a pause lets a nearly finished description play out") {
  Schedule s; s.load({{1.0, 2.0}});
  s.step({true, false, 1.0}, {});
  s.step({true, false, 2.0}, {true, false});
  auto a = s.step({true, true, 2.6}, {true, false});      // the player pauses: 0.4 s of it left
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Pause);
  a = s.step({false, false, 2.6}, {true, false});         // the movie is gone while paused
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Resume);
  CHECK(s.state(0) == State::Playing);
  a = s.step({false, false, 2.6}, {false, true});         // it reached its end
  CHECK(a.empty());
  CHECK(s.state(0) == State::Done);
  CHECK(s.playing() == -1);
}

TEST_CASE("ad: reset arms every cue again") {
  Schedule s; s.load(three());
  s.step({true, false, 9.0}, {});                          // joined late: the first two are behind the clock
  CHECK(s.state(0) == State::Skipped);
  s.reset();
  CHECK(s.size() == 3);
  CHECK(s.playing() == -1);
  for (int i = 0; i < 3; ++i) { CHECK(s.state(i) == State::Pending); CHECK(s.reason(i).empty()); }
  auto a = s.step({true, false, 1.0}, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].cue == 0);
}

TEST_CASE("ad: fast-forward cuts the cue, skips what it passes and keeps the rest") {
  Schedule s; s.load(three());
  auto a = s.step({true, false, 1.0}, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Play);
  double t = 1.0;
  a = s.step({true, false, t += 1.0 / 15, true}, {true, false});   // fast-forward: four times the pace at 60 fps
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Stop);
  CHECK(s.state(0) == State::Cut);
  CHECK(s.reason(0) == "fast-forward");
  while (t < 5.0) {
    a = s.step({true, false, t += 1.0 / 15, true}, {});
    CHECK(a.empty());                                       // nothing is said over it, and it is no jump
  }
  CHECK(s.state(1) == State::Skipped);
  CHECK(s.reason(1) == "fast-forward");
  CHECK(s.state(2) == State::Pending);
  a.clear();
  while (a.empty() && t < 9.0) a = s.step({true, false, t += 1.0 / 60}, {});   // back to normal: the schedule goes on
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Play);
  CHECK(a[0].cue == 2);
}

TEST_CASE("ad: a cue still ahead of a fast-forward plays on time after it") {
  Schedule s; s.load(three());
  double t = 0;
  while (t < 2.5) s.step({true, false, t += 1.0 / 15, true}, {});
  CHECK(s.state(0) == State::Skipped);
  std::vector<Action> a;
  while (a.empty() && t < 5.0) a = s.step({true, false, t += 1.0 / 60}, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Play);
  CHECK(a[0].cue == 1);
  CHECK(t - 4.0 < 0.05);
}

TEST_CASE("ad: a description's box holds the scene: its narrator plays out, the next cue waits for it to close") {
  Schedule s; s.load({{1.0, 2.0}, {1.2, 1.0}});
  auto a = s.step({true, false, 1.0}, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Play);
  Clock held{true, false, 1.0, false, true};   // the mod paused the scene: its clock stands, IsPaused is ours
  a = s.step(held, {true, false});
  CHECK(a.empty());                            // not paused: the narrator goes on
  a = s.step(held, {false, true});
  CHECK(a.empty());                            // done, and the next cue does not start under the box
  CHECK(s.state(0) == State::Done);
  CHECK(s.state(1) == State::Pending);
  a = s.step({true, false, 1.0}, {});          // the box closes: the scene plays on
  CHECK(a.empty());
  a = s.step({true, false, 1.2}, {});          // the next cue on time
  REQUIRE(a.size() == 1);
  CHECK(a[0].act == Act::Play);
  CHECK(a[0].cue == 1);
}

TEST_CASE("ad: a cue due while someone talks waits for the line, however long, and the next after it") {
  Schedule s; s.load({{1.0, 1.0}, {1.5, 1.0}, {9.0, 1.0}});
  CHECK(s.step({true, false, 0.9}, {}).empty());
  Clock talk{true, false, 1.0, false, false, true};   // Auto: the scene runs on through a voiced line
  for (double t = 1.0; t < 4.0; t += 0.1) { talk.time = t; CHECK(s.step(talk, {}).empty()); }
  CHECK(s.state(0) == State::Pending);
  CHECK(s.state(1) == State::Pending);
  auto a = s.step({true, false, 4.0}, {});            // the line ended, 3 s after the cue's moment
  REQUIRE(a.size() == 1);
  CHECK(a[0].cue == 0);
  a = s.step({true, false, 4.5}, {true, false});      // the second waits behind the first, not missed
  CHECK(a.empty());
  CHECK(s.state(1) == State::Pending);
  a = s.step({true, false, 5.0}, {false, true});
  REQUIRE(a.size() == 1);
  CHECK(a[0].cue == 1);
  CHECK(s.state(0) == State::Done);
  // a cue that was simply late (no line over it) is still missed
  a = s.step({true, false, 5.5}, {false, true});
  for (double t = 6.0; t < 8.0; t += 1.0) s.step({true, false, t}, {});
  s.step({true, false, 8.9}, {});
  a = s.step({true, false, 9.8}, {});   // a hitch past the cue's moment
  CHECK(a.empty());
  CHECK(s.state(2) == State::Missed);
}

TEST_CASE("ad: every state has a name for the log") {
  CHECK(std::string(state_name(State::Pending)) == "pending");
  CHECK(std::string(state_name(State::Playing)) == "playing");
  CHECK(std::string(state_name(State::Done)) == "done");
  CHECK(std::string(state_name(State::Cut)) == "cut");
  CHECK(std::string(state_name(State::Missed)) == "missed");
  CHECK(std::string(state_name(State::Skipped)) == "skipped");
}

TEST_CASE("ad: a description in its last second outlives the movie's end") {
  Scenario sc; sc.length = 2.6;   // cue 0 runs 1.0-3.0: 0.4 s left when the movie ends
  SimResult r = simulate({{1.0, 2.0}}, sc);
  CHECK(r.states[0] == State::Done);
  CHECK(r.played[0] == doctest::Approx(2.0));
}

TEST_CASE("ad: a scene played over queues its cues: one due while the narrator speaks waits and plays after") {
  Schedule s;
  s.load({{1.0, 3.0}, {2.0, 1.0}, {2.5, 1.0}});
  Clock c{true, false, 1.0}; c.queue = true;
  auto a = s.step(c, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].cue == 0);
  for (double t = 1.5; t <= 3.5; t += 0.5) { c.time = t; CHECK(s.step(c, {true, false}).empty()); }
  c.time = 4.0;   // cue 0 ends 1.5 s after cue 1 came due: cue 1 plays, not missed
  a = s.step(c, {false, true});
  REQUIRE(a.size() == 1);
  CHECK(a[0].cue == 1);
  CHECK(s.state(2) == State::Pending);
  c.time = 5.0;
  a = s.step(c, {false, true});
  REQUIRE(a.size() == 1);
  CHECK(a[0].cue == 2);
}

TEST_CASE("ad: a scene played over: a cue due while the narrator is paused for a line waits for it") {
  Schedule s;
  s.load({{1.0, 1.0}});
  Clock c{true, true, 1.0}; c.queue = true;   // paused: a voice line plays
  CHECK(s.step(c, {}).empty());
  for (double t = 1.5; t <= 4.0; t += 0.5) { c.time = t; CHECK(s.step(c, {}).empty()); }
  c.paused = false;
  c.time = 4.1;
  auto a = s.step(c, {});
  REQUIRE(a.size() == 1);
  CHECK(a[0].cue == 0);
}

TEST_CASE("ad: play_out: the scene ends and its description is said to its end; the rest are dropped") {
  Schedule s;
  s.load({{1.0, 5.0}, {2.0, 1.0}}, true);
  s.step({true, false, 1.0}, {});
  s.step({true, false, 1.5}, {true, false});
  auto a = s.step({false, false, 0}, {true, false});   // the scene is gone, 4.5 s of the description left
  CHECK(a.empty());
  CHECK(s.playing() == 0);
  a = s.step({false, false, 0}, {false, true});
  CHECK(s.state(0) == State::Done);
  CHECK(s.playing() == -1);
}
