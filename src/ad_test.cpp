// Audio description's in-game test (/ad/test: plays described movies through a player it spawns and checks every
// description plays in full) and the packed clips' selftest. Moved out of ad.cpp (2026-11-26); what they share is
// ad_internal.h.
#include "ad.h"
#include "ad_internal.h"
#include "audio.h"
#include "devserver.h"
#include "log.h"
#include "ue/ue.h"
#include <windows.h>
#include <cstdio>
#include <format>

namespace p3a::ad {
using namespace ue;

// ---- the in-game test (/ad/test) ----
// Plays movies through a movie player it spawns (BP_MoviePlayer_C via GameplayStatics), each chosen by its playlist
// id (the data file's "#id" line; see arm), and for each description starts a fresh player half a second before it,
// then waits for the narrator to finish it: the real clock, scheduler, decoder, mixer and ducking, with the
// dialogue between descriptions skipped. A description passes when it ends Done with every sample played. Results: /ad/test (progress) and the
// log ("ad test: ..."). mode=full plays a movie start to finish instead (no seeks).
namespace {
struct Test {
  bool on = false, full = false;
  std::vector<std::string> keys;
  size_t movie = 0;
  int cue = -1;
  enum Step { Open, WaitPlay, Seek, WaitCue, Next } step = Open;
  double fps = 0;   // measured from the movie's own clock before the first seek
  double seek_to = 0;
  int status = -1;   // the player's last Mana status (logged as it changes)
  int arm_frame = 0;
  bool armed = true;
  bool cue_started = false;   // the current description has begun (its time limit runs from then)
  double last_clock = -1;
  ULONGLONG clock_moved = 0;   // when the movie clock last changed (the watchdog)
  int id = -1;   // the movie's playlist index (#id line)
  std::vector<double> ats;   // its descriptions' times (the scene is reloaded with each fresh player)
  int cues = 0;   // the movie's description count (the scene object is replaced each time the movie restarts)
  ULONGLONG since = 0;
  WeakObj player;
  int pass = 0, fail = 0, movies_done = 0;
  ULONGLONG paused_at = 0;   // the pause check: the movie paused mid-description (first cue of each movie)
  int paused_checks = 0;
  std::vector<std::string> failures;
  std::string now;
} g_test;

// A Blueprint class by its object path, loaded if it is not (KismetSystemLibrary::LoadClassAsset_Blocking). The
// TSoftClassPtr parameter (0x28): a weak pointer and tag (0x10, zeroed), then the FSoftObjectPath: the path as an
// FName (+0x10, made by KismetStringLibrary::Conv_StringToName) and an empty sub-path FString (+0x18).
// load_soft("LoadAsset_Blocking", "Asset", path) loads any asset the same way (TSoftObjectPtr has the layout).
UObject* load_soft(const char* fn, const char* param, const std::string& path) {
  UObject* ksl = find_object("/Script/Engine.Default__KismetSystemLibrary");
  UObject* kstr = find_object("/Script/Engine.Default__KismetStringLibrary");
  UFunction* conv = kstr ? find_function(class_of(kstr), "Conv_StringToName") : nullptr;
  UFunction* load = ksl ? find_function(class_of(ksl), fn) : nullptr;
  if (!conv || !load) return nullptr;
  std::u16string w = to_u16(path);
  Params n(conv);
  n.set<FString>("inString", make_fstring(w));
  call(kstr, n);
  FName name = n.ret<FName>();
  Params p(load);
  if (uint8_t* soft = p.at<uint8_t>(param)) memcpy(soft + 0x10, &name, sizeof name);
  call(ksl, p);
  return p.ret<UObject*>();
}
UClass* load_class(const char* path) { return (UClass*)load_soft("LoadClassAsset_Blocking", "AssetClass", path); }

UObject* spawn_player() {
  UClass* cls = find_class("BP_MoviePlayer_C");
  if (!cls) cls = load_class("/Game/Xrd777/Blueprints/Movies/BP_MoviePlayer.BP_MoviePlayer_C");
  UObject* gs = find_object("/Script/Engine.Default__GameplayStatics");
  if (!cls || !gs) return nullptr;
  float xf[12] = {0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0};   // FTransform: identity rotation, origin, unit scale
  UFunction* begin = find_function(class_of(gs), "BeginDeferredActorSpawnFromClass");
  UFunction* finish = find_function(class_of(gs), "FinishSpawningActor");
  if (!begin || !finish) return nullptr;
  Params p(begin);
  p.set<UObject*>("WorldContextObject", gworld());
  p.set<UObject*>("ActorClass", (UObject*)cls);
  if (auto* t = p.at<float>("SpawnTransform")) memcpy(t, xf, sizeof xf);
  p.set<uint8_t>("CollisionHandlingOverride", 1);   // AlwaysSpawn
  call(gs, p);
  UObject* a = p.ret<UObject*>();
  if (!a) return nullptr;
  Params q(finish);
  q.set<UObject*>("Actor", a);
  if (auto* t = q.at<float>("SpawnTransform")) memcpy(t, xf, sizeof xf);
  call(gs, q);
  return a;
}

// Close the test's movie player the way the game does at a movie's end (BP Close(ForceClose): Remove, then
// K2_DestroyActor). Stopping a spawned player and playing it again crashed the game inside CRI (twice,
// 2026-11-02): every start gets a fresh player instead.
void close_player(Test& t) {
  if (UObject* pl = t.player.resolve())
    if (UFunction* fn = find_function(class_of(pl), "Close")) { Params p(fn); p.set<uint8_t>("ForceClose", 1); call(pl, p); }
  t.player = WeakObj{};
}

// A fresh player on `path`, starting at `frame` (Mana SeekToPosition before Play sets the start).
UObject* open_movie(Test& t, int frame) {
  close_player(t);
  UObject* pl = spawn_player();
  UObject* m = pl ? get<UObject*>(pl, "Mana") : nullptr;
  if (!m) return nullptr;
  t.player = WeakObj::of(pl);
  // The Blueprint binds the movie's cue commands from Mana.OnStatusChanged (MovieBindCuePointFunction at WaitPrep)
  // and the first, CueCmd_LoadBmdAsset (FUN_14a63f500), reads a message-system object that is gone the second time
  // a test player starts: null + 0x48, a crash. The test needs no subtitles: unbind the handler (the delegate's
  // binding array count, +8) so neither the cue commands nor the end-of-movie teardown run.
  if (uint8_t* d = field<uint8_t>(m, "OnStatusChanged")) *(int32_t*)(d + 8) = 0;
  // with its status handler unbound the Blueprint plays nothing itself: test_tick picks the movie, the start frame,
  // and plays it (arm)
  t.arm_frame = frame;
  t.armed = false;
  return m;
}

// The second half of open_movie, once the fresh player has stopped.
// The movie is chosen the game's way: its ID (its index in the player's playlist, MPL_MoviePlayer[En], what
// MOVIE_PLAY(id) plays) requested on the actor, which opens it (RequestMovie, CallOpenSourceForBP). SetFile,
// SetMovie and PreparePlaylistIndex on the Mana were all ignored.
void arm(Test& t, UObject* m) {
  t.armed = true;
  UObject* pl = t.player.resolve();
  if (!pl) return;
  if (UFunction* fn = find_function(class_of(pl), "RequestMovie")) { Params p(fn); p.set<int32_t>("ID", t.id); call(pl, p); }
  call(pl, "CallOpenSourceForBP");
  if (t.arm_frame > 0)
    if (UFunction* fn = find_function(class_of(m), "SeekToPosition")) { Params p(fn); p.set<int32_t>("FrameNumber", t.arm_frame); call(m, p); }
  call(m, "Play");
}

void test_fail(const std::string& what) {
  ++g_test.fail;
  g_test.failures.push_back(what);
  log::writef("ad test: FAIL {}", what);
}

}  // namespace

void test_tick() {
  Test& t = g_test;
  if (!t.on) return;
  ULONGLONG now = GetTickCount64();
  if (t.movie >= t.keys.size()) {
    t.on = false;
    close_player(t);
    log::writef("ad test: finished: {} movies, {} descriptions passed, {} failed, {} pause checks", t.movies_done,
                t.pass, t.fail, t.paused_checks);
    return;
  }
  const std::string& key = t.keys[t.movie];
  UObject* pl = t.player.resolve();
  UObject* m = pl ? get<UObject*>(pl, "Mana") : nullptr;
  if (m) {   // with the Blueprint's status handler unbound, nothing plays the movie once it is prepared: we do
    int st = call_ret<uint8_t>(m, "GetStatus");
    if (st != t.status) { log::writef("ad test: player status {} -> {}", t.status, st); t.status = st; }
    // watchdog: a movie whose clock stands still for 10 s (outside the deliberate pause) is frozen; fail and move
    // on rather than wait (a frozen player once held a run for half an hour)
    double tm = seconds(call_ret<int64_t>(m, "GetTime"));
    if (tm != t.last_clock || t.paused_at > 1 && now - t.paused_at < 1600 || st != 5) { t.last_clock = tm; t.clock_moved = now; }
    else if (t.clock_moved && now - t.clock_moved > 10000 && (t.step == Test::WaitPlay || t.step == Test::WaitCue)) {
      test_fail(std::format("{} cue {}: the movie froze at {:.2f} s", t.keys[t.movie], t.cue, tm));
      t.clock_moved = now;
      t.step = t.full || t.step == Test::WaitPlay ? Test::Next : Test::Seek;
    }
    if (!t.armed && st == 0) arm(t, m);
    else if (t.armed && st == 4) call(m, "Play");   // Ready
  }
  if (!m && t.step != Test::Open && t.step != Test::Seek && t.step != Test::Next) {
    test_fail(key + ": the movie player went away"); t.step = Test::Next; return;
  }
  std::shared_ptr<Scene> s = g_scene;
  switch (t.step) {
    case Test::Open: {
      FILE* f = fopen((data_dir() + key + ".txt").c_str(), "rb");
      std::string path;
      if (f) {
        char line[512] = {};
        if (fgets(line, sizeof line, f) && strncmp(line, "#file ", 6) == 0) path = line + 6;
        // the second line ("#asset", the movie's asset path) is read past: the movie is chosen by its id
        if (fgets(line, sizeof line, f) && fgets(line, sizeof line, f) && strncmp(line, "#id ", 4) == 0) t.id = atoi(line + 4);
        fclose(f);
      }
      while (!path.empty() && (path.back() == '\n' || path.back() == '\r')) path.pop_back();
      if (path.empty()) { test_fail(key + ": no #file line"); t.step = Test::Next; break; }
      if (!open_movie(t, 0)) { test_fail(key + ": no movie player"); t.on = false; break; }
      t.now = key;
      t.cue = -1;
      t.step = Test::WaitPlay;
      t.since = now;
      log::writef("ad test: {} opens {}", key, path);
      break;
    }
    case Test::WaitPlay:
      if (!(s && s->key == key && s->ready)) {
        if (now - t.since > 15000) { test_fail(key + ": the movie did not start (or has no data)"); t.step = Test::Next; }
        break;
      }
      if (!t.full) {   // the frame rate (29.97 or 30), from the movie's own clock once it has run a second
        double tm = seconds(call_ret<int64_t>(m, "GetTime"));
        if (tm < 1.0) break;
        t.fps = call_ret<int32_t>(m, "GetFrameNumber") / tm;
      }
      t.cues = (int)s->cues.size();
      t.ats.clear();
      for (const auto& c : s->cues) t.ats.push_back(c.at);
      t.step = t.full ? Test::WaitCue : Test::Seek;
      t.cue = t.full ? 0 : -1;
      t.since = now;
      break;
    case Test::Seek:
      // Mana's Seek stops a playing movie (Playing -> StopProcessing -> Stop, seen live) and a stopped spawned
      // player cannot be played again safely: a fresh player starts at the frame; the narrator sees the movie start
      // there and skips what is behind it. A description still sounding (one that began while the frame rate was
      // measured) finishes first, so the next check is not confused by it.
      if (g_sched.playing() >= 0 && now - t.since < 8000) break;
      if (++t.cue >= t.cues) { t.step = Test::Next; break; }
      t.seek_to = std::max(0.0, t.ats[t.cue] - 0.5);
      t.cue_started = false;
      if (!open_movie(t, (int)(t.seek_to * t.fps))) { test_fail(key + ": no movie player"); t.step = Test::Next; break; }
      t.step = Test::WaitCue;
      t.since = now;
      break;
    case Test::WaitCue: {
      if (!s || s->key != key || !s->ready || g_sched.size() != (size_t)t.cues) {   // restarting after the seek
        if (now - t.since > 10000) { test_fail(std::format("{} cue {}: the movie did not come back after the seek", key, t.cue)); t.step = Test::Seek; }
        break;
      }
      if (t.full) {   // wait for the whole movie; judge every cue at the end
        if (now - t.since > 1000 * (ULONGLONG)(s->cues.empty() ? 5 : s->cues.back().at + s->cues.back().dur + 5)) t.step = Test::Next;
        break;
      }
      sched::State st = g_sched.state(t.cue);
      const Run& run = g_runs[t.cue];
      // the first description of each movie: pause the movie halfway through it for 1.5 s (the narrator must hold
      // and then finish, not stop or run on)
      if (t.cue == 0 && st == sched::State::Playing && !t.paused_at && run.total && run.played > run.total / 2) {
        if (UFunction* fn = find_function(class_of(m), "Pause")) { Params p(fn); p.set<uint8_t>("bPause", 1); call(m, p); }
        t.paused_at = now;
        log::writef("ad test: {} paused the movie at {} of {} samples", key, run.played, run.total);
      }
      if (t.paused_at > 1 && now - t.paused_at > 1500) {
        if (audio::narration().played > run.played + 4800) test_fail(key + ": the narrator ran on while the movie was paused");
        if (UFunction* fn = find_function(class_of(m), "Pause")) { Params p(fn); p.set<uint8_t>("bPause", 0); call(m, p); }
        t.paused_at = 1;   // done for this movie
        ++t.paused_checks;
        t.since = now;
      }
      bool final = st != sched::State::Pending && st != sched::State::Playing;
      // the time limit runs from the description's start, not the request: event movies take seconds to open
      if (st == sched::State::Playing && !t.cue_started) { t.cue_started = true; t.since = now; }
      ULONGLONG limit = t.cue_started ? (ULONGLONG)(1000 * (s->cues[t.cue].dur + 4)) : 15000;
      if (!final && now - t.since < limit) break;
      const Run& r = g_runs[t.cue];
      if (st == sched::State::Done && r.total > 0 && r.played == r.total) ++t.pass;
      else test_fail(std::format("{} cue {} at {:.2f}: {} {} (played {} of {} samples)", key, t.cue, s->cues[t.cue].at,
                                 sched::state_name(st), g_sched.reason(t.cue), r.played, r.total));
      t.step = Test::Seek;
      break;
    }
    case Test::Next:
      if (t.full && s && s->key == key)
        for (size_t i = 0; i < s->cues.size(); ++i) {
          const Run& r = g_runs[i];
          if (g_sched.state((int)i) == sched::State::Done && r.total > 0 && r.played == r.total) ++t.pass;
          else test_fail(std::format("{} cue {} at {:.2f}: {} {}", key, i, s->cues[i].at, sched::state_name(g_sched.state((int)i)), g_sched.reason((int)i)));
        }
      close_player(t);
      t.paused_at = 0;
      ++t.movies_done;
      ++t.movie;
      t.step = Test::Open;
      break;
  }
}

void register_test_route() {
  dev::route("/ad/test", [](const dev::Request& r, int&) {
    std::string movie = dev::arg(r, "movie");
    bool start = dev::has(r, "start"), full = dev::arg(r, "mode") == "full", stop = dev::has(r, "stop");
    return dev::on_game([movie, start, full, stop] {
      Test& t = g_test;
      if (stop) { t.on = false; close_player(t); return std::string("stopped\n"); }
      if (start) {
        // a player left from an earlier run (a stop before a hot reload) is the one the clock would read: close
        // every movie player first (a scan, once per run)
        for (UObject* old : find_all("BP_MoviePlayer_C"))
          if (UFunction* fn = find_function(class_of(old), "Close")) { Params p(fn); p.set<uint8_t>("ForceClose", 1); call(old, p); }
        t = Test{};
        WIN32_FIND_DATAA fd;
        HANDLE h = FindFirstFileA((data_dir() + "*.txt").c_str(), &fd);
        if (h != INVALID_HANDLE_VALUE) {
          do {
            std::string k = fd.cFileName;
            k.resize(k.size() - 4);
            if (movie.empty() || k.find(movie) != std::string::npos) t.keys.push_back(k);
          } while (FindNextFileA(h, &fd));
          FindClose(h);
        }
        t.full = full;
        t.on = !t.keys.empty();
        log::writef("ad test: starts ({} movies, {})", t.keys.size(), full ? "full playback" : "seek to each description");
      }
      std::string out = std::format("running={} movie {}/{} {} cue {} passed={} failed={} pause_checks={}\n", t.on,
                                    t.movie, t.keys.size(), t.now, t.cue, t.pass, t.fail, t.paused_checks);
      for (const auto& f : t.failures) out += "FAIL " + f + "\n";
      return out;
    });
  }, "?start=1[&movie=filter][&mode=full] play described movies in game and check every description plays in full; no args: progress");
}

std::string selftest(const std::string& filter) {
  WIN32_FIND_DATAA fd;
  HANDLE h = FindFirstFileA((data_dir() + "*.txt").c_str(), &fd);
  if (h == INVALID_HANDLE_VALUE) return "no assets\\ad\n";
  int movies = 0, clips = 0, bad = 0;
  double total = 0;
  std::string out;
  do {
    std::string key = fd.cFileName;
    key.resize(key.size() - 4);
    if (!filter.empty() && key.find(filter) == std::string::npos) continue;
    FILE* f = fopen((data_dir() + fd.cFileName).c_str(), "rb");
    if (!f) continue;
    ++movies;
    char line[2048];
    while (fgets(line, sizeof line, f)) {
      double at = 0, dur = 0;
      char file[64] = {};
      if (sscanf(line, "%lf\t%lf\t%63[^\t]", &at, &dur, file) < 3) continue;
      std::vector<float> v;
      ++clips;
      bool ok = audio::decode_mono(data_dir() + key + "\\" + file, v);
      double got = v.size() / 48000.0;
      total += got;
      // MP3 adds up to ~50 ms of encoder padding; a clip shorter than its voiced length lost its end
      if (!ok || got < dur - 0.03 || got > dur + 0.12) {
        ++bad;
        out += std::format("BAD {} {} at {:.2f}: decoded {:.3f} s, voiced {:.3f} s\n", key, file, at, got, dur);
      }
    }
    fclose(f);
  } while (FindNextFileA(h, &fd));
  FindClose(h);
  return out + std::format("selftest: {} movies, {} clips, {:.1f} min decoded, {} bad\n", movies, clips, total / 60, bad);
}
}  // namespace p3a::ad
