// Audio description: a narrator describes the animated story movies between their lines.
// A story movie is a CRI UManaComponent ("Mana") on BP_MoviePlayer_C (anime movies) or
// BP_MoviePlayerEventSequenceTrack_C (movies inside an event's sequence): GetTime returns an FTimespan (int64,
// 100 ns ticks), GetSource the UManaMovie, IsPlaying stays true while paused (Enter). AudioTrack (+0x1A0) picks
// the voice language: two 5.1 tracks, 0 Japanese and 1 English (the gap maps hold for both).
//
// Data: assets/ad/<key>.txt (one cue a line: at, length, clip, text) and assets/ad/<key>/NN.mp3.
// <key> is the source's name less "_VP9" and a trailing "_Movi" (MS_Event_Main_100_030_M). A movie with no file
// gets nothing. Its clips are decoded on a worker thread when the movie starts (well before the first cue).
// core::ad::Schedule decides what plays when (pauses, seeks, a skip); here its actions reach the mixer's
// narrator, and the movie's own volume (Mana SetVolume) dips under a description. Every cue's end is logged
// ("ad: <key> cue N done|cut ... played P of T s") and kept for /ad/status: the in-game tests read those.
// A 3D scene's descriptions are played over it as it moves (see "Played over" in tick). With DescriptionWait on, each is
// a box like a message window instead: it pauses the scene and waits for Enter (see "the description box" below). The
// animated movies' descriptions, and a Theurgy's, are timed to fit between their lines and never stop them.
// A 3D scene's description once heard (its box closed by Enter or Auto, or its narration played to its end) is
// recorded in seen-descriptions.txt beside the settings (core/heard_cues); with SceneDescription on "suppress repeated
// descriptions" a scene is loaded without the ones heard. Movies are not recorded.
// SceneSpeed: a 3D scene's narrator reads faster. Its clips are sped up as they are decoded (core/time_stretch keeps
// the pitch) and its cues' lengths shortened to match; a movie's clips keep their speed (they are timed to its gaps).
#include "ad.h"
#include "ad_internal.h"
#include "event_skip.h"
#include "audio.h"
#include "core/ad_schedule.h"
#include "core/heard_cues.h"
#include "core/time_stretch.h"
#include "mod.h"
#include "core/strings.h"
#include "core/lang.h"
#include "devserver.h"
#include "hooks.h"
#include "input.h"
#include "screens/util.h"
#include "keys.h"
#include "log.h"
#include "msg.h"
#include "settings.h"
#include "speech.h"
#include "voice.h"
#include "watch.h"
#include "world.h"
#include "ue/ue.h"
#include <windows.h>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <format>
#include <memory>
#include <mutex>
#include <thread>

namespace p3a::ad {
using namespace ue;
namespace sched = core::ad;

// Shared with the in-game test (ad_internal.h).
std::shared_ptr<Scene> g_scene;
sched::Schedule g_sched;
std::vector<Run> g_runs;
double seconds(int64_t ticks) { return ticks / 1e7; }
std::string data_dir() { return audio::module_dir() + "assets\\ad\\"; }

namespace {
constexpr float kDuck = 0.45f;       // the movie's volume under a description (about -7 dB)
constexpr float kDuckStep = 0.08f;   // per frame toward the target: ~7 frames, ~120 ms at 60 fps

std::vector<sched::State> g_seen;   // the states already logged
int g_voice_id = -1;                // the narrator clip that is ours
int g_cur = -1;
bool g_was_playing = false;
std::string g_key;                  // the movie we last set up for (with or without descriptions)
int g_mode = settings::DescOff;     // how its descriptions are given (settings::Description)
bool g_once = false;                // it was loaded without the descriptions already heard (settings::SceneOnce)
int g_speed = 0;                    // its narrator's speed-up (settings::SceneSpeed; 0 for a movie)
float g_base_volume = -1, g_volume = -1;
double g_opening = 0;               // a 3D scene's opening ends (scene seconds): no description starts before it
// All of the above is the game thread's: the dev routes read it through dev::on_game.

// The clip decoders: one worker thread per described movie, each owned here until it is joined (once its scene is
// ready, at the next movie's load; or at unload, which first tells them to stop). Their code is in this DLL, so none
// may outlive it. The list is never destroyed: a thread still joinable must not meet its destructor at process exit.
struct Decoder { std::thread thread; std::shared_ptr<Scene> scene; };
std::mutex g_decoders_mu;                // the list (the game thread loads, unload runs on another thread)
std::atomic<bool> g_unloading{false};    // set by unload: no new decoder, and the running ones stop after their clip
std::vector<Decoder>& decoders() { static auto* list = new std::vector<Decoder>; return *list; }

int player_id() { static int id = watch::want("BP_MoviePlayer_C"); return id; }
int track_player_id() { static int id = watch::want("BP_MoviePlayerEventSequenceTrack_C"); return id; }

// A movie is under way from its header decode to its end (EManaComponentStatus DecHdr 1 .. Playing 5): a seek
// takes it back through DecHdr/Prep for a few frames, when IsPlaying is false but the movie has not ended.
UObject* mana_of(int watch_id) {
  UObject* p = watch::get(watch_id);
  UObject* m = p ? get<UObject*>(p, "Mana") : nullptr;
  if (!m) return nullptr;
  int st = call_ret<uint8_t>(m, "GetStatus");
  return st >= 1 && st <= 5 ? m : nullptr;
}
UObject* playing_mana() {
  if (UObject* m = mana_of(player_id())) return m;
  return mana_of(track_player_id());
}

// A story scene played in the engine (an event): an AtlEvtLevelSequenceActor named after its LevelSequence
// (LS_Event_Main_110_240_C) and its ULevelSequencePlayer (SequencePlayer). The sequence's own clock is the scene's:
// GetCurrentTime is an FQualifiedFrameTime {frame int32, subframe float, rate numerator, denominator}, in the
// sequence's display rate (30 fps). The sequence pauses itself at a message that holds it (a dialogue key with
// bPauseSequencer, a WaitingMessage controller) until the player moves on: IsPaused then (seen live, 2026-11-15).
int event_actor_id() { static int id = watch::want("AtlEvtLevelSequenceActor", true); return id; }

// A battle's own scenes: a boss's entrance and the turns of its fight (LS_BtlEvent<id>_<row>, DT_BtlEvt<id> rows the
// battle's script loads and plays: BTL_CUTSCENE_LOAD / PLAY / SYNC / END), a party member's first summon
// (LS_BtlPc<nn>FirstSummon, BP_BtlHumanBase's FirstSummonSceneActor). Each is a plain LevelSequenceActor the battle
// spawns with its own SequencePlayer; only those with descriptions are followed (assets/ad/LS_Btl*.txt, listed once):
// a battle plays many more (summons, skills, criticals) that have none.
// Their pause: the battle's script waits for a scene's end (BTL_CUTSCENE_SYNC, the first summon's OnFinished) by its
// player still playing, so a Pause let the battle run on under a frozen picture (seen live, 2026-11-24: 704_999 paused,
// the result screen came 3.5 s later). The box holds one by its play rate instead (SetPlayRate, kHeldRate): it stays
// playing, barely moving, and the battle waits for it (704_000 held 12 s, the fight started 5 s after the release).
constexpr float kHeldRate = 0.001f;
int seq_actor_id() { static int id = watch::want("LevelSequenceActor", true); return id; }
const std::vector<std::string>& battle_keys();
bool is_battle_key(const std::string& k) {
  for (const std::string& b : battle_keys()) if (b == k) return true;
  return false;
}
// A Theurgy's scene: LS_Btl_Theurgia_<member><A|B> (a member's, Takaya's) or LS_Btl_MixRaid<letter> (the hero's), one
// per row of DT_BtlTheurgiaSeqList (the skill's id), played by BP_BtlTheurgiaController with a _Sound sub-sequence of
// its own beside it (no description). It runs on its own, like a movie: no line holds it.
bool is_theurgy_key(std::string_view k) {
  if (k.ends_with("_Astrea")) k.remove_suffix(7);
  return (k.starts_with("LS_Btl_Theurgia_") || k.starts_with("LS_Btl_MixRaid")) && !k.ends_with("_Sound");
}
// A battle sequence's key: its name. Episode Aigis has scenes of its own under the base game's names (its
// LS_Btl_MixRaidA is /Game/Astrea/Battle/Theurgia/PC12/, the base game's /Game/Xrd777/.../Pc01/): those get "_Astrea".
std::string battle_seq_key(UObject* seq) {
  std::string k = name_of(seq);
  if (path_name(seq).starts_with("/Game/Astrea/")) k += "_Astrea";
  return k;
}
UObject* playing_event(UObject** actor, bool* battle = nullptr) {
  if (battle) *battle = false;
  for (UObject* a : watch::all(event_actor_id())) {
    UObject* p = get<UObject*>(a, "SequencePlayer");
    if (p && is_live(p) && (call_ret<bool>(p, "IsPlaying") || call_ret<bool>(p, "IsPaused"))) { if (actor) *actor = a; return p; }
  }
  if (battle_keys().empty()) return nullptr;
  for (UObject* a : watch::all(seq_actor_id())) {
    if (is_a(a, "AtlEvtLevelSequenceActor")) continue;
    UObject* p = get<UObject*>(a, "SequencePlayer");
    if (!p || !is_live(p)) continue;
    UObject* seq = get<UObject*>(p, "Sequence");
    if (!seq || !is_live(seq)) continue;
    // a Theurgy's is followed whether described or not (/ad/clock times it for capture)
    if (const std::string k = battle_seq_key(seq); !is_battle_key(k) && !is_theurgy_key(k)) continue;
    if (call_ret<bool>(p, "IsPlaying") || call_ret<bool>(p, "IsPaused")) {
      if (actor) *actor = a;
      if (battle) *battle = true;
      return p;
    }
  }
  return nullptr;
}
double event_seconds(UObject* player) {
  UFunction* fn = find_function(class_of(player), "GetCurrentTime");
  if (!fn) return 0;
  Params p(fn);
  if (!call(player, p)) return 0;
  const uint8_t* r = p.at<uint8_t>("ReturnValue");
  if (!r) return 0;
  int32_t frame = *(const int32_t*)r, num = *(const int32_t*)(r + 8), den = *(const int32_t*)(r + 12);
  float sub = *(const float*)(r + 4);
  return num > 0 ? (frame + (double)sub) * den / num : 0;
}

// ---- a scene's opening ----
// A scene opens with keys of its own: its music (an MovieSceneEvtAdxSoundSection key, GlobalBGM, Play; mostly in a
// LS_..._Sound sub-sequence) and a fade in from black (MovieSceneEvtFadeScreenSection, FADE_IN, FadeFrame frames
// long). A description due before they have played was said over the last scene's music and a black screen, and its box
// paused the scene before its music could start (2026-11-24: in 630 of 846 described scenes the first description came
// before the music key, mostly at frame 1). The opening is the first music key and the first fade in's end, of those that
// come before the scene's first line (MovieSceneEvtDialogueSection): a later one is the scene's own choice to stay
// quiet or dark. Until the scene's clock passes it no description starts (the schedule's `talk` wait: it starts then).
// A music track carried over from the last scene does not matter: this is the new scene's own clock against its own keys.
// Every section's EventData is {Times TArray<FFrameNumber>, KeyValues TArray<payload>}, read by reflection; times are
// in its MovieScene's TickResolution (24000 in every scene), a sub-sequence's shifted by its SubSection's start.
int sound_section_id() { static int id = watch::want("MovieSceneEvtAdxSoundSection", true); return id; }
int fade_section_id() { static int id = watch::want("MovieSceneEvtFadeScreenSection", true); return id; }
int dialogue_section_id() { static int id = watch::want("MovieSceneEvtDialogueSection", true); return id; }

struct Opening { double music = -1, fade = -1, first_line = -1, end = 0; };

// A frame rate property's {numerator, denominator} in `o`: frames to seconds (-1 without one).
double frames_to_seconds(UObject* o, const char* prop, double frames) {
  const int32_t* r = field<int32_t>(o, prop);
  return r && r[0] > 0 ? frames * r[1] / r[0] : -1;
}

// Calls f(seconds, payload, payload struct) for each key of a section's EventData; `shift` seconds are added.
template <typename F>
void each_key(UObject* section, UObject* scene, double shift, F&& f) {
  FField* ed = find_prop((UStruct*)class_of(section), "EventData");
  UStruct* eds = ed ? (UStruct*)prop_inner_object(ed) : nullptr;
  FField* times = eds ? find_prop(eds, "Times") : nullptr;
  FField* keys = eds ? find_prop(eds, "KeyValues") : nullptr;
  FField* inner = keys ? prop_inner_prop(keys) : nullptr;
  UStruct* payload = inner ? (UStruct*)prop_inner_object(inner) : nullptr;
  if (!times || !payload) return;
  const uint8_t* base = (const uint8_t*)section + prop_offset(ed);
  auto* t = (const TArray<int32_t>*)(base + prop_offset(times));
  auto* k = (const TArray<uint8_t>*)(base + prop_offset(keys));
  const int32_t stride = prop_size(inner);
  if (!t->data || !k->data || stride <= 0) return;
  for (int32_t i = 0; i < t->num && i < k->num; ++i) {
    double s = frames_to_seconds(scene, "TickResolution", t->data[i]);
    if (s >= 0) f(s + shift, k->data + (size_t)i * stride, payload);
  }
}

// The enum value's name a payload holds ("EEvtSoundCategoryType::GlobalBGM" or "GlobalBGM").
bool payload_is(const uint8_t* p, UStruct* payload, const char* prop, std::string_view value) {
  FField* f = find_prop(payload, prop);
  UObject* e = f ? prop_inner_object(f) : nullptr;
  if (!e) return false;
  return enum_name(e, *(const int8_t*)(p + prop_offset(f))).ends_with(value);
}

Opening scene_opening(UObject* seq) {
  Opening o;
  UObject* ms = seq ? get<UObject*>(seq, "MovieScene") : nullptr;
  if (!ms || !is_live(ms)) return o;
  // the scene's MovieScene and its sub-sequences' (the sound), each with where it starts in the scene
  std::vector<std::pair<UObject*, double>> scenes{{ms, 0.0}};
  if (auto* tracks = field<TArray<UObject*>>(ms, "MasterTracks"))
    for (int32_t i = 0; i < tracks->num; ++i) {
      UObject* tr = tracks->data[i];
      auto* sections = tr && is_a(tr, "MovieSceneSubTrack") ? field<TArray<UObject*>>(tr, "Sections") : nullptr;
      for (int32_t j = 0; sections && j < sections->num; ++j) {
        UObject* sub = sections->data[j];
        UObject* sseq = sub ? get<UObject*>(sub, "SubSequence") : nullptr;
        UObject* sms = sseq ? get<UObject*>(sseq, "MovieScene") : nullptr;
        if (!sms) continue;
        // SectionRange: TRange<FFrameNumber>, its lower bound {uint8 type (0 open), int32 frame}
        double start = 0;
        if (const uint8_t* r = field<uint8_t>(sub, "SectionRange"); r && r[0] != 0)
          start = std::max(0.0, frames_to_seconds(ms, "TickResolution", *(const int32_t*)(r + 4)));
        scenes.push_back({sms, start});
      }
    }
  // a section's track's MovieScene: one of ours, and where it starts
  auto shift_of = [&](UObject* section) -> double {
    UObject* track = outer_of(section);
    UObject* owner = track ? outer_of(track) : nullptr;
    for (auto& [s, at] : scenes) if (s == owner) return at;
    return -1;
  };
  auto first = [](double& slot, double v) { if (slot < 0 || v < slot) slot = v; };
  auto scene_of = [&](UObject* section) {
    UObject* track = outer_of(section);
    return track ? outer_of(track) : nullptr;
  };
  for (UObject* sec : watch::all(dialogue_section_id())) {
    double shift = shift_of(sec);
    if (shift >= 0) each_key(sec, scene_of(sec), shift, [&](double s, const uint8_t*, UStruct*) { first(o.first_line, s); });
  }
  for (UObject* sec : watch::all(sound_section_id())) {
    double shift = shift_of(sec);
    if (shift < 0) continue;
    each_key(sec, scene_of(sec), shift, [&](double s, const uint8_t* p, UStruct* pl) {
      if (payload_is(p, pl, "EvtSoundCategoryType", "GlobalBGM") && payload_is(p, pl, "EvtAdxSoundOperationType", "Play"))
        first(o.music, s);
    });
  }
  for (UObject* sec : watch::all(fade_section_id())) {
    double shift = shift_of(sec);
    if (shift < 0) continue;
    each_key(sec, scene_of(sec), shift, [&](double s, const uint8_t* p, UStruct* pl) {
      if (!payload_is(p, pl, "FadeScreenType", "FADE_IN")) return;
      FField* ff = find_prop(pl, "FadeFrame");
      double len = ff ? frames_to_seconds(scene_of(sec), "DisplayRate", *(const int32_t*)(p + prop_offset(ff))) : 0;
      first(o.fade, s + std::max(0.0, len));   // the fade's frames at the scene's display rate (30 fps)
    });
  }
  for (double v : {o.music, o.fade})
    if (v >= 0 && (o.first_line < 0 || v < o.first_line)) o.end = std::max(o.end, v);
  return o;
}

std::string key_of(std::string name) {
  // the player's source is a PlatformManaMovie wrapping the platform's FileManaMovie (seen live, 2026-11-02)
  if (name.starts_with("PlatformManaMovie_")) name.erase(0, 18);
  if (auto p = name.find("_VP9"); p != std::string::npos) name.erase(p, 4);
  if (name.size() > 5 && name.ends_with("_Movi")) name.resize(name.size() - 5);
  return name;
}


const std::vector<std::string>& battle_keys() {
  static const std::vector<std::string>* keys = [] {
    auto* v = new std::vector<std::string>;
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA((data_dir() + "LS_Btl*.txt").c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE) {
      do { std::string k = fd.cFileName; k.resize(k.size() - 4); v->push_back(std::move(k)); } while (FindNextFileA(h, &fd));
      FindClose(h);
    }
    log::writef("ad: {} battle scenes described", v->size());
    return v;
  }();
  return *keys;
}

// ---- the descriptions heard (3D scenes) ----
// The file sits beside the settings; dev launches (P3A_NOFOCUS) keep their own, as they do settings-dev.ini.
std::wstring heard_file() {
  std::wstring p = log::path();
  p = p.substr(0, p.find_last_of(L'\\') + 1);
  return p + (env_flag(L"P3A_NOFOCUS") ? L"seen-descriptions-dev.txt" : L"seen-descriptions.txt");
}
core::HeardCues& heard() {
  static core::HeardCues* h = [] {
    auto* cues = new core::HeardCues;
    if (FILE* f = _wfopen(heard_file().c_str(), L"rb")) {
      char line[256];
      while (fgets(line, sizeof line, f)) cues->add_line(line);
      fclose(f);
    }
    log::writef("ad: {} scene descriptions heard before", cues->size());
    return cues;
  }();
  return *h;
}
// A 3D scene's cue was heard: recorded (once).
void mark_heard(const Scene& s, int cue) {
  if (cue < 0 || cue >= (int)s.heard_ids.size()) return;
  const std::string& id = s.heard_ids[cue];
  if (!heard().add(id)) return;
  if (FILE* f = _wfopen(heard_file().c_str(), L"ab")) { fprintf(f, "%s\n", id.c_str()); fclose(f); }
}

// decode false: the descriptions go to the screen reader, as text; no clip is decoded.
// scene: a 3D scene (its cues get heard ids); once: the cues already heard are left out; speed > 1: the clips are
// sped up by it, their pitch kept, and the cues' lengths with them.
std::shared_ptr<Scene> load_scene(const std::string& key, bool decode, bool scene, bool once, double speed) {
  FILE* f = fopen((data_dir() + key + ".txt").c_str(), "rb");
  if (!f) return nullptr;
  auto s = std::make_shared<Scene>();
  s->key = key;
  char line[2048];
  while (fgets(line, sizeof line, f)) {
    if (strncmp(line, "#file ", 6) == 0) {
      s->file = line + 6;
      while (!s->file.empty() && (s->file.back() == '\n' || s->file.back() == '\r')) s->file.pop_back();
      continue;
    }
    double at = 0, dur = 0;
    char file[64] = {};
    int used = 0;
    if (sscanf(line, "%lf\t%lf\t%63[^\t]\t%n", &at, &dur, file, &used) < 3) continue;
    std::string text = line + used;
    while (!text.empty() && (text.back() == '\n' || text.back() == '\r')) text.pop_back();
    if (scene) {
      std::string id = core::HeardCues::id(key, text);
      if (once && heard().heard(key, text)) { ++s->left_out; continue; }   // heard before: left out
      s->heard_ids.push_back(std::move(id));
    }
    s->cues.push_back({at, speed > 1 ? dur / speed : dur});
    s->files.push_back(file);
    s->texts.push_back(decode ? text : core::lang::tr(std::string_view(text)));   // read by the screen reader: in the mod's language
  }
  fclose(f);
  s->pcm.resize(s->cues.size());
  if (!decode) { s->ready = true; return s; }
  std::lock_guard lk(g_decoders_mu);
  if (g_unloading) return nullptr;
  std::vector<Decoder>& list = decoders();
  // The decoders that have finished are joined here (their last statement sets `ready`: no wait to speak of).
  for (auto it = list.begin(); it != list.end();) {
    if (it->scene->ready) { it->thread.join(); it = list.erase(it); }
    else ++it;
  }
  list.push_back(Decoder{std::thread([s, speed] {
    for (size_t i = 0; i < s->files.size() && !g_unloading; ++i) {
      auto v = std::make_shared<std::vector<float>>();
      if (audio::decode_mono(data_dir() + s->key + "\\" + s->files[i], *v)) {
        if (speed > 1) *v = core::time_stretch(*v, audio::sample_rate(), speed);
        s->pcm[i] = std::move(v);
      }
      else ++s->failed;
    }
    s->ready = true;
  }), s});
  return s;
}

void set_movie_volume(UObject* m, float v) {
  UFunction* fn = find_function(class_of(m), "SetVolume");
  if (!fn) return;
  Params p(fn);
  p.set<float>("Volume", v);
  call(m, p);
}

void log_endings(const Scene& s) {
  for (size_t i = 0; i < s.cues.size(); ++i) {
    sched::State st = g_sched.state((int)i);
    if (st == g_seen[i]) continue;
    g_seen[i] = st;
    if (st == sched::State::Playing || st == sched::State::Pending) continue;
    if (st == sched::State::Done) mark_heard(s, (int)i);   // said to its end (a box's narrator, or one said over the scene)
    const Run& r = g_runs[i];
    log::writef("ad: {} cue {} {} at {:.2f} {}{}played {:.2f} of {:.2f} s", s.key, i, sched::state_name(st),
                s.cues[i].at, g_sched.reason((int)i), g_sched.reason((int)i).empty() ? "" : ", ",
                r.played / 48000.0, r.total / 48000.0);
  }
}

void stop_all() {
  if (g_cur >= 0) audio::narrate_stop();
  g_cur = -1;
  g_voice_id = -1;
}

// ---- the description box (setting DescriptionWait; 3D scenes only) ----
// A description pauses its scene (the SequencePlayer's Pause: what the game's own holds at a message do) and waits like a message window: the description (the narrator or the
// screen reader), then the cue a page that waits gets ("Next" or the VoiceEndSound sound), and Enter, Space or A goes on with the sound a message
// window's page turn makes (cue 9 of exe+0x1286af0, heard as the player pressed through a conversation) and
// plays the source again. A press while the narrator still speaks cuts it, as a press skips a voiced line. The press
// never reaches the game (keys::set_prompt, input::set_swallow_prompt). With the game's Auto on it goes on by itself
// once the description is said, as Auto turns a page once its voice ends: the narrator's clip at its end, the screen
// reader once it reports quiet (one that cannot tell, NVDA, at once: the game's own unvoiced pages under Auto do not
// wait for it either); no end cue then. Fast-forward, a skip, the source ending or
// the setting turned off closes it. The schedule sees the held source as playing (Clock::held): the cue's narrator
// plays out and nothing further starts until the box closes.
int g_box = -1;              // the cue whose box is up, else -1
bool g_box_go = false;       // Enter, Space or A taken while it is up (game thread: the window procedure runs there)
bool g_box_pad = true;       // A was down at the last frame (only a fresh press counts)
bool g_box_ended = false;    // its narrator finished (the end cue was given)
bool g_box_spoke = false;    // the screen reader reported it speaking (Auto waits for it to go quiet)
bool g_releasing = false;    // the box closed and asked the source to play: until it reports so, the pause is ours
// The scene's clock when the box's first frame saw it held (-1 until then). The box holds the scene still, so a clock
// that has run on past it is the game's own skip (Tab or Menu in a fusion's animation: the sequence jumps to the new
// Persona's appearance, 18.8 s in, paused or not): the box closes and the scene plays from there. Left up, the scene
// had jumped but stood still until Enter, which the player who had just skipped it had no reason to press
// (2026-11-25).
double g_box_time = -1;
constexpr double kBoxSkipS = 1.0;   // a held scene the game lets go for a frame creeps a few hundredths at most

uint16_t a_mask() { static uint16_t a = input::button_mask("a"); return a; }
uint16_t pad_a() { return input::layer_open() ? 0 : (input::real_buttons() & a_mask()); }

bool g_battle = false;        // the scene loaded is a battle's (playing_event): held by its rate, not paused
float g_rate = 1.0f;          // a held battle scene's play rate before the box held it
bool g_box_over_msg = false;  // the box came up over a battle line's window that waits for the player (see tick)

void set_rate(UObject* player, float r) {
  if (UFunction* fn = find_function(class_of(player), "SetPlayRate")) { Params p(fn); p.set<float>("PlayRate", r); call(player, p); }
}

void hold_source(bool on) {
  if (UObject* m = playing_mana()) {
    if (UFunction* fn = find_function(class_of(m), "Pause")) { Params p(fn); p.set<uint8_t>("bPause", on ? 1 : 0); call(m, p); }
    return;
  }
  bool battle = false;
  UObject* ev = playing_event(nullptr, &battle);
  if (!ev) return;
  if (!battle) { call(ev, on ? "Pause" : "Play"); return; }
  const float r = call_ret<float>(ev, "GetPlayRate", 1.0f);
  if (on) {
    if (r > kHeldRate * 2) { g_rate = r; set_rate(ev, kHeldRate); }
  } else if (r <= kHeldRate * 2) {
    set_rate(ev, g_rate > kHeldRate * 2 ? g_rate : 1.0f);
  }
}

void open_box(int cue) {
  g_box = cue;
  g_box_go = false;
  g_box_ended = false;
  g_box_spoke = false;
  g_box_time = -1;
  g_box_pad = pad_a() != 0;   // an A still down from the last message is not this box's press
  // Over a battle line's window that waits for the player, the press that goes on is the window's too: it reaches
  // the game, so one press closes both, as one press turns a page.
  const msg::Current w = msg::current();
  g_box_over_msg = g_battle && w.open && w.blocking;
  input::set_swallow_prompt(g_box_over_msg ? 0 : a_mask());
  hold_source(true);   // no opening sound: a dialogue window opens without one (the user's call, 2026-11-20)
}

// resume: the source is still the one the box held (playing, not replaced): it plays again.
// cut: the narrator stops (the player went on); a battle scene that ended under its box lets it finish.
void close_box(bool resume, bool cut = true) {
  if (g_box < 0) return;
  if (cut && g_cur >= 0) audio::narrate_stop();   // gone on before the narrator finished: the cue is logged cut
  if (resume) { hold_source(false); g_releasing = true; }
  input::set_swallow_prompt(0);
  g_box = -1;
  g_box_go = false;
  g_box_over_msg = false;
}
}  // namespace

bool holding() { return g_box >= 0 || g_releasing; }

void unload() {
  // a box still up lets its scene go (the game thread: it calls the game), and the keys stop coming here
  hooks::run_on_game_thread([] { close_box(true); keys::set_prompt(nullptr); }, 3000);
  g_unloading = true;
  std::vector<Decoder> list;
  { std::lock_guard lk(g_decoders_mu); list.swap(decoders()); }
  for (Decoder& d : list) if (d.thread.joinable()) d.thread.join();
}

Clock clock() {
  Clock c;
  UObject* m = playing_mana();
  if (!m) {
    UObject* actor = nullptr;
    bool battle = false;
    UObject* ev = playing_event(&actor, &battle);
    // Fast-forward runs a scene at four times its pace: no description is played over it (one playing stops; the
    // schedule skips what it passes). It is the same scene: reporting it as stopped reloaded the scene at each
    // toggle (2026-11-16, 110_210 in a player's log).
    if (!ev) return c;
    c.fast = !battle && world::scene_fast();
    c.playing = true;
    c.event = true;
    c.battle = battle;
    // a battle scene held by its rate (the box's hold) counts as paused
    c.paused = call_ret<bool>(ev, "IsPaused") || (battle && call_ret<float>(ev, "GetPlayRate", 1.0f) <= kHeldRate * 2);
    // Keyed by the LevelSequence the player runs (UMovieSceneSequencePlayer::Sequence), not by the actor: 30 Social
    // Link levels name their actor after another scene (009_055's is LS_Event_Cmmu_009_053_C, the _600s' a _610) or
    // with a _2 (the _717/_737 hangouts), and their descriptions never played.
    UObject* seq = get<UObject*>(ev, "Sequence");
    c.movie = seq && is_live(seq) ? (battle ? battle_seq_key(seq) : name_of(seq)) : name_of(actor);
    c.theurgy = battle && is_theurgy_key(c.movie);
    c.time = event_seconds(ev);
    return c;
  }
  c.playing = true;
  c.paused = call_ret<bool>(m, "IsPaused");
  if (UObject* src = call_ret<UObject*>(m, "GetSource")) {
    // The player's source is a PlatformManaMovie wrapping the language's FileManaMovie (ManaMovie), which carries
    // its file ("Movie_VP9/Anim/MS_..._VP9.usm"). The file names the movie: one wrapper can stand for two files
    // (the Episode Aigis opening plays MS_Astrea_OP_Movie_B in English, _A otherwise).
    if (UObject* inner = get<UObject*>(src, "ManaMovie")) src = inner;
    FString* fp = field<FString>(src, "FilePath");
    std::string path = fp ? to_utf8(*fp) : std::string();
    if (auto slash = path.find_last_of("/\\"); slash != std::string::npos) path.erase(0, slash + 1);
    if (path.ends_with(".usm")) path.resize(path.size() - 4);
    c.movie = path.empty() ? name_of(src) : path;
  }
  c.time = seconds(call_ret<int64_t>(m, "GetTime"));
  c.frame = call_ret<int32_t>(m, "GetFrameNumber");
  c.audio_track = get<int32_t>(m, "AudioTrack");
  return c;
}

void tick() {
  test_tick();
  UObject* m = playing_mana();   // null for a scene in the engine: its sound is not dipped
  Clock c = clock();
  bool playing = c.playing;
  if (!playing && !g_was_playing && g_sched.playing() < 0) return;   // nothing on, nothing finishing
  // Movies and scenes each have their setting: off, the narrator's voice, or the screen reader. A description
  // finishing after its movie keeps the mode it started in.
  // A 3D scene: SceneDescription says whether (and whether once), SceneVoice by whom.
  int mode = g_mode;
  bool once = g_once;
  int speed = g_speed;
  if (playing && !c.event) { mode = settings::get(settings::AudioDescription); once = false; speed = 0; }
  if (playing && c.event && !c.theurgy) {
    const int scene = settings::get(settings::SceneDescription);
    mode = scene == settings::SceneOff ? settings::DescOff : settings::get(settings::SceneVoice);
    once = scene == settings::SceneOnce;
    speed = mode == settings::DescAudio ? settings::get(settings::SceneSpeed) : 0;
  }
  // A Theurgy is described like a movie (the user's call, 2026-11-26): the movies' setting, its timing kept, not
  // recorded as heard.
  if (playing && c.theurgy) { mode = settings::get(settings::AudioDescription); once = false; speed = 0; }
  // The narrator speaks English only: in another language the descriptions are read by the screen reader, translated
  // (the user's call, 2026-11-23: no generated voices).
  if (mode == settings::DescAudio && !core::lang::english()) { mode = settings::DescReader; speed = 0; }
  if (!playing || !c.paused) g_releasing = false;
  if (mode == settings::DescOff) {
    close_box(playing);
    if (g_was_playing) { stop_all(); g_was_playing = false; g_scene.reset(); g_key.clear(); }
    return;
  }
  if (playing && (!g_was_playing || g_key != key_of(c.movie) || mode != g_mode || once != g_once || speed != g_speed)) {
    // a movie starts (or the source changed under a running player, or the setting changed): load its
    // descriptions, if it has any
    close_box(g_key == key_of(c.movie));
    stop_all();
    g_key = key_of(c.movie);
    g_battle = c.battle;
    g_mode = mode;
    g_once = once;
    g_speed = speed;
    auto s = load_scene(g_key, mode == settings::DescAudio, c.event && !c.theurgy, once, settings::scene_speed_factor(speed));
    g_scene = s;
    // a 3D scene's description is said to its end when the scene ends under it (a battle goes on, the next scene loads)
    g_sched.load(s ? s->cues : std::vector<sched::Cue>{}, c.event);
    g_runs.assign(g_sched.size(), Run{});
    g_seen.assign(g_sched.size(), sched::State::Pending);
    g_base_volume = m ? call_ret<float>(m, "GetVolume", 1.0f) : 1.0f;
    g_volume = g_base_volume;
    g_opening = 0;
    if (c.event && s) {
      UObject* ev = playing_event(nullptr);
      UObject* seq = ev ? get<UObject*>(ev, "Sequence") : nullptr;
      Opening o = scene_opening(seq && is_live(seq) ? seq : nullptr);
      g_opening = o.end;
      log::writef("ad: {} opens at {:.2f} (music {:.2f}, fade in done {:.2f}, first line {:.2f})", g_key, o.end, o.music,
                  o.fade, o.first_line);
    }
    log::writef("ad: {} {} ({}), {} descriptions{}{}", c.battle ? "battle scene" : c.event ? "scene" : "movie", c.movie, key_of(c.movie), s ? s->cues.size() : 0,
                s && s->left_out ? std::format(", {} heard before left out", s->left_out) : std::string(),
                speed ? std::format(", narrator x{:.2f}", settings::scene_speed_factor(speed)) : std::string());
  }
  g_was_playing = playing;
  std::shared_ptr<Scene> s = g_scene;
  if (!s || !s->ready) return;

  bool reader = g_mode == settings::DescReader;
  audio::Narration n = audio::narration();
  bool ours = !reader && n.id == g_voice_id && g_voice_id >= 0;
  if (ours && g_cur >= 0) { g_runs[g_cur].played = n.played; g_runs[g_cur].total = n.total; }
  // The screen reader takes a description whole and queues it: it is done as soon as it is handed over.
  sched::Voice v = reader ? sched::Voice{false, g_sched.playing() >= 0} : sched::Voice{ours && n.active, ours && n.ended};
  // Only 3D scenes can wait (a box, setting DescriptionWait, off by default since 2026-11-26): an animated movie's
  // descriptions are timed to fit its gaps (the user's call, 2026-11-18), and so are a Theurgy's.
  const bool scene3d = c.event && !c.theurgy;
  const bool wait = scene3d && settings::on(settings::DescriptionWait);
  // Played over (the default, the user's call 2026-11-26: "like the animated cutscenes"): the scene never stops for a
  // description. It plays as the scene moves; one that comes due while another is said waits its turn (Clock::queue);
  // the narrator pauses while a character's voice line plays and goes on after it (the line itself never waits), and
  // while the game's skip prompt holds the scene. The scene's own hold at a line waiting for Enter is not a pause: the
  // description goes on over it, as the player listens.
  const bool over = scene3d && !wait;
  sched::Clock sc{playing, c.paused, c.time, c.fast};
  // A 3D scene's description waits while someone talks: under the game's Auto the scene runs on through its lines
  // (without it, it pauses at each line until the player goes on), and its descriptions began over the voice
  // (2026-11-20, 100_040 in a player's log). A movie's lines are in its own sound: its cues are timed between them.
  if (scene3d) {
    const msg::Current w = msg::current();
    sc.talk = (w.open && w.blocking) || voice::playing();
    // A battle's script shows a line as it plays a scene, and ends the scene soon after the line's window closes
    // (BTL_CUTSCENE_PLAY, MSG, WAIT, END): a description waiting for the window to close would never come. Once the
    // line's voice has ended the window only waits for the player, as a held page does: the description comes then,
    // over it (open_box: one press goes on from both). Played over, any scene's voiced line that has ended leaves
    // such a gap. An unvoiced line is read by the screen reader: its window stays a line spoken.
    if ((g_battle || over) && w.open && w.blocking && w.voice_done && !voice::playing()) sc.talk = false;
    // Played over, a battle's scene lasts a few seconds and the fight goes on: a line its script shows beside it
    // (unvoiced: "Priestess defeated" with her fall) held its description until the scene had ended, and it was
    // never said (seen live, 2026-11-26, 701_999). Only a voice holds it; the narrator pauses for one.
    if (g_battle && over) sc.talk = voice::playing();
    if (c.time <= g_opening) sc.talk = true;   // its opening (music, fade in) has not played yet: see scene_opening
    if (over) {
      sc.queue = true;
      sc.paused = voice::playing() || event_skip::prompt();
    }
  }
  if (g_box >= 0) {
    // A battle scene ended under its box (its script ended it: the line's window closed under Auto): the description
    // is said to its end, over the battle.
    if (!playing && g_battle) close_box(false, false);
    else if (!playing || c.fast || !wait) close_box(playing);
    else if (g_box_time >= 0 && c.time > g_box_time + kBoxSkipS) {
      log::writef("ad: {} cue {} box closed by a skip, {:.2f} to {:.2f}", s->key, g_box, g_box_time, c.time);
      close_box(true);
      sc.paused = false;
    } else {
      if (g_box_time < 0 && c.paused) g_box_time = c.time;
      const bool a = pad_a() != 0;
      if (a && !g_box_pad) g_box_go = true;
      g_box_pad = a;
      bool by_auto = false;
      if (!g_box_go && msg::auto_on()) {   // Auto: on once it is said
        if (reader) {
          const int sp = speech::speaking();
          if (sp == 1) g_box_spoke = true;
          by_auto = sp == -1 || (sp == 0 && g_box_spoke);
        } else {
          by_auto = !ours || n.ended;
        }
        g_box_go = by_auto;
      }
      // The game's skip prompt is up (the skip button's first press: the game holds the scene too): the box stays
      // until the player has skipped or cancelled. Letting the scene go under the prompt would play it while the
      // game has it paused.
      if (event_skip::prompt()) g_box_go = false;
      if (g_box_go) {
        log::writef("ad: {} cue {} box closed at {:.2f}{}", s->key, g_box, c.time, by_auto ? " (Auto)" : "");
        mark_heard(*s, g_box);   // the player went on from it (or Auto did): heard, even if cut short
        close_box(true);
        screens::cursor_sound(9);   // what a message window plays as Enter turns its page (measured 2026-11-17)
        sc.paused = false;   // it plays from this frame
      } else {
        if (!c.paused) hold_source(true);   // the game let it go meanwhile: hold it again
        sc.paused = false;
        sc.held = true;
        // The description is said and the box waits: the cue a message window's page gets then (msg's end_cue_tick),
        // "Next" or the chosen sound; none under Auto, which goes on by itself. The narrator: once its clip ended.
        // The screen reader: "Next" is speech, queued behind the description at once; a sound waits until the reader
        // has reported it under way and then quiet (one that cannot tell, NVDA: at once).
        if (!g_box_ended && !msg::auto_on() && !voice::playing()) {
          const bool next = settings::get(settings::VoiceEndSound) == settings::EndNext;
          bool said = false;
          if (reader) {
            const int sp = speech::speaking();
            if (sp == 1) g_box_spoke = true;
            said = next || sp == -1 || (sp == 0 && g_box_spoke);
          } else {
            said = ours && n.ended;
          }
          if (said) {
            g_box_ended = true;
            if (next) speech::speak(strings::kNext.c_str(), false);
            else voice::play_end_sound();
          }
        }
      }
    }
  }
  for (const sched::Action& a : g_sched.step(sc, v)) {
    if (a.act == sched::Act::Play && scene3d) msg::remember_line(s->texts[a.cue]);   // in the log (B)
    if (reader) {   // nothing of ours sounds: nothing to pause or stop
      if (a.act == sched::Act::Play) {
        if (wait) open_box(a.cue);
        speech::speak(s->texts[a.cue], false);
        g_runs[a.cue] = Run{c.time, 0, 0};
        log::writef("ad: {} cue {} read at {:.2f} (due {:.2f}){}: {}", s->key, a.cue, c.time, s->cues[a.cue].at, wait ? ", box" : "", s->texts[a.cue]);
      }
      continue;
    }
    switch (a.act) {
      case sched::Act::Play:
        if (!s->pcm[a.cue]) break;   // a clip that would not decode: the cue is logged as cut by the narrator
        if (wait) open_box(a.cue);
        g_voice_id = audio::narrate(s->pcm[a.cue]);
        g_cur = a.cue;
        g_runs[a.cue] = Run{c.time, 0, s->pcm[a.cue]->size()};
        log::writef("ad: {} cue {} plays at {:.2f} (due {:.2f}){}: {}", s->key, a.cue, c.time, s->cues[a.cue].at, wait ? ", box" : "", s->texts[a.cue]);
        break;
      case sched::Act::Pause: audio::narrate_pause(true); break;
      case sched::Act::Resume: audio::narrate_pause(false); break;
      case sched::Act::Stop: audio::narrate_stop(); g_cur = -1; break;
    }
  }
  if (g_sched.playing() < 0) g_cur = -1;
  log_endings(*s);
  if (!playing) {   // the movie is over: keep the scene until a last description has played out
    if (g_sched.playing() < 0) { g_scene.reset(); g_key.clear(); }
    return;
  }
  if (!m) return;   // a scene in the engine: no movie sound to dip
  // the movie's own sound dips while a description speaks
  float target = g_base_volume * (g_cur >= 0 && !c.paused ? kDuck : 1.0f);
  if (g_volume != target) {
    g_volume = g_volume < target ? std::min(target, g_volume + kDuckStep) : std::max(target, g_volume - kDuckStep);
    set_movie_volume(m, g_volume);
  }
}

void register_routes() {
  keys::set_prompt([](uint32_t vk, bool repeat) {
    if (g_box < 0 || (vk != VK_RETURN && vk != VK_SPACE)) return false;
    if (!repeat) g_box_go = true;
    // over a battle line's waiting window the press goes on to it too (open_box), while that window is still up (a
    // battle line in its forced mode closes itself once said)
    if (g_box_over_msg) { const msg::Current w = msg::current(); return !(w.open && w.blocking); }
    return true;
  });
  player_id();
  track_player_id();
  sound_section_id();
  fade_section_id();
  dialogue_section_id();
  // the playing scene's opening (scene_opening), read now
  dev::route("/ad/opening", [](const dev::Request&, int&) {
    return dev::on_game([] {
      UObject* ev = playing_event(nullptr);
      UObject* seq = ev ? get<UObject*>(ev, "Sequence") : nullptr;
      if (!seq || !is_live(seq)) return std::string("no scene\n");
      Opening o = scene_opening(seq);
      return std::format("{} opens at {:.3f} (music {:.3f}, fade in done {:.3f}, first line {:.3f}); now {:.3f}, gate {:.3f}\n",
                         name_of(seq), o.end, o.music, o.fade, o.first_line, event_seconds(ev), g_opening);
    });
  }, "the playing 3D scene's opening (its music and fade in): no description starts before it");
  dev::route("/ad/clock", [](const dev::Request&, int&) {
    return dev::on_game([] {
      Clock c = clock();
      if (!c.playing) return std::string("playing=0\n");
      return std::format("playing=1 paused={} {}={} time={:.3f} frame={} track={}{}{}\n", c.paused ? 1 : 0,
                         c.event ? "scene" : "movie", c.movie, c.time, c.frame, c.audio_track,
                         c.fast ? " fast=1" : "", c.theurgy ? " theurgy=1" : "");
    });
  }, "the story movie or scene clock (audio description): movie or scene, time s, frame, pause, voice track");
  // /ad/box: the description box up (its cue) or -1: the dev flows press Enter on it as on a message page.
  dev::route("/ad/box", [](const dev::Request&, int&) {
    return dev::on_game([] { return std::format("box={}\n", g_box); });
  }, "the scene description box's cue, or -1 (dev flows press Enter on it)");
  dev::route("/ad/status", [](const dev::Request&, int&) {
    return dev::on_game([] {
      std::shared_ptr<Scene> s = g_scene;
      if (!s) return std::string("no described movie\n");
      std::string out = std::format("movie {} ready={} failed_clips={} cues={} playing={}\n", s->key, s->ready.load(),
                                    s->failed.load(), s->cues.size(), g_sched.playing());
      for (size_t i = 0; i < s->cues.size(); ++i)
        out += std::format("{:3} {:8.2f} {:8} played {:.2f}/{:.2f} {}\n", i, s->cues[i].at,
                           sched::state_name(g_sched.state((int)i)), g_runs[i].played / 48000.0, g_runs[i].total / 48000.0,
                           g_sched.reason((int)i));
      return out;
    });
  }, "the described movie: every cue's state and how much of it played");
  register_test_route();   // /ad/test, ad_test.cpp
  dev::route("/ad/heard", [](const dev::Request& r, int&) {
    const bool clear = dev::has(r, "clear");
    return dev::on_game([clear] {
      if (clear) { heard().clear(); _wremove(heard_file().c_str()); }
      return std::format("{} scene descriptions heard{}\n", heard().size(), clear ? " (forgotten)" : "");
    });
  }, "the 3D scene descriptions heard (suppress repeated descriptions); ?clear=1 forgets them");
  dev::route("/ad/selftest",[](const dev::Request& r, int&) {
    // Every packed clip of every movie decoded and its length compared with the cue's (a fast check of the shipped
    // files, not of the timing or the mixer). Runs on the server's thread: it touches no game state.
    std::string filter = dev::arg(r, "movie");
    return selftest(filter);
  }, "?movie=filter decode every packed description clip and report frames (shipping check)");
}

}  // namespace p3a::ad
