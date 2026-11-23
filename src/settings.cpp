#include "settings.h"
#include "audio.h"
#include "core/graph_builder.h"
#include "core/navigator.h"
#include "core/settings_text.h"
#include "core/sonar_cues.h"
#include "core/speech_text.h"
#include "core/strings.h"
#include "core/units.h"
#include "devserver.h"
#include "input.h"
#include "keys.h"
#include "log.h"
#include "mod.h"
#include "shadow.h"
#include "sight.h"
#include "sonar.h"
#include "speech.h"
#include "voice.h"
#include "language.h"
#include "core/lang.h"
#include "walltones.h"
#include "world.h"
#include "screens/camp.h"
#include <windows.h>
#include <xinput.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace p3a::settings {
enum class Unit { Toggle, Meters, Percent, Ms, Choice };
// The menu's categories (the user's call, 2026-11-11: one list of 27 rows had grown too long). Each is a stop of its
// own: a short list with its own positions, its name said on landing; Tab / Shift+Tab (Page Down / Page Up, RB / LB)
// go to the next / previous one, wrapping. A row names its category, so the table's order stays the file's.
// Regrouped 2026-11-17 (the user's call): every volume in one category, and a row does not repeat its category's name
// ("Range" under Sonar, "Master" under Volume). The table's order is the menu's order within each category.
// 2026-11-20 (the user asked to keep it organized as the narrator speed came in): the descriptions left Dialogue and
// movies for a category of their own, Audio description; Dialogue keeps the game's lines.
enum Category { CatExploring, CatSonar, CatVolume, CatSound, CatDialogue, CatDescription, CatControls, CatLanguage, CatCount };
static const strings::Tr kCategoryNames[CatCount] = {strings::kCatExploring, strings::kCatSonar, strings::kCatVolume,
                                                     strings::kCatSound, strings::kCatDialogue, strings::kCatDescription,
                                                     strings::kCatControls, strings::kCatLanguage};
struct Def {
  const char* key; strings::Tr name;
  Category cat;        // where the menu lists it
  strings::Tr help;    // what it does: read with its row, after the position
  Unit unit; std::vector<int> values; int def; std::vector<strings::Tr> labels = {};
};
static const std::vector<int> kPercents = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
// One row per Id, in its order: what the file calls it, what the menu says and where, the values it cycles through.
// The values run left to right by the common norm (the user's call, 2026-11-20, replacing 2026-11-17's match with the
// game's Config, which draws ON left of OFF): Off at the left, On to its right; a mode's Off first, then from less to
// more; a scale (a number, a speed, a delay) from Off or its least at the left, growing to the right. Left is off or
// less, Right on or more. The game's own Config is left as the game has it.
// The Language row's choices: the game's language, then every language named in itself (core::lang).
static std::vector<strings::Tr> language_labels() {
  std::vector<strings::Tr> v{strings::kLangGame};
  for (int i = 0; i < core::lang::Count; ++i) v.push_back({core::lang::native_name(i)});
  return v;
}
static const Def kDefs[Count] = {
  // the camera fixed north and every sound heard from above while walking freely (topdown.cpp)
  {"top_down", strings::kSetTopDown, CatExploring, strings::kHelpTopDown, Unit::Toggle, {0, 1}, 1},
  // in the top-down mode, a room reached by a jump is turned so the way walked in stays up (topdown.cpp kRoomTurns)
  {"turned_rooms", strings::kSetTurnedRooms, CatExploring, strings::kHelpTurnedRooms, Unit::Toggle, {0, 1}, 1},
  // the daily hero dashes whenever he moves, outside Tartarus; Shift (RT) then runs (walkmode.cpp). On by default (the user's call, 2026-11-23)
  {"always_dash", strings::kSetAlwaysDash, CatExploring, strings::kHelpAlwaysDash, Unit::Toggle, {0, 1}, 1},
  {"poi_range", strings::kSetPoiRange, CatExploring, strings::kHelpPoiRange, Unit::Meters, {20, 40, 60, 100, 150}, 60},
  // when the wall tones play: all the time, only while the player moves (the default), or never (walltones.cpp)
  {"wall_tones", strings::kSetWallTones, CatExploring, strings::kHelpWallTones, Unit::Choice, {WallOff, WallMoving, WallContinuous}, WallMoving,
   {strings::kOff, strings::kWallMoving, strings::kWallContinuous}},
  // how far each wall tone reaches, in meters, in either mode (walltones.cpp; Dark Vision's is 15 ft, 1 to 40)
  {"wall_range", strings::kSetWallRange, CatExploring, strings::kHelpWallRange, Unit::Meters, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5},
  {"shadow_alerts", strings::kSetShadowAlerts, CatExploring, strings::kHelpShadowAlerts, Unit::Toggle, {0, 1}, 1},
  // the edge of each Shadow's sight, and the hum while a wall hides the hero from one (sight.cpp)
  {"shadow_sight", strings::kSetShadowSight, CatExploring, strings::kHelpShadowSight, Unit::Toggle, {0, 1}, 1},
  // how far from the edge of a Shadow's sight its zone is heard, in meters (a new key: the old warning distance meant
  // something else)
  {"sight_range", strings::kSetSightRange, CatExploring, strings::kHelpSightRange, Unit::Meters, {2, 4, 6, 8, 10, 12, 14, 16}, 10},
  // the hero turns to the Shadow his strike can reach as the swing starts (shadow.cpp)
  {"strike_assist", strings::kSetStrikeAssist, CatExploring, strings::kHelpStrikeAssist, Unit::Toggle, {0, 1}, 1},
  // the Reaper's timers on a Tartarus floor run twice as long (shadow.cpp); off is the game's own pace
  {"relaxed_reaper", strings::kSetRelaxedReaper, CatExploring, strings::kHelpRelaxedReaper, Unit::Toggle, {0, 1}, 0},
  // every nearby point of interest sounds (sonar.cpp)
  {"sonar", strings::kSetSonar, CatSonar, strings::kHelpSonar, Unit::Toggle, {0, 1}, 1},
  {"sonar_scope", strings::kSetSonarScope, CatSonar, strings::kHelpSonarScope, Unit::Choice, {ScopeSelected, ScopeCategory, ScopeAll}, ScopeAll,
   {strings::kScopeAll, strings::kScopeCategory, strings::kScopeSelected}},
  // 10 m (20 was tried for a day under the key sonar_distance: what made things seem late was the wait before a
  // thing's first sound, not the range; the user's call, 2026-11-10).
  {"sonar_range", strings::kSetSonarRange, CatSonar, strings::kHelpSonarRange, Unit::Meters, {5, 10, 15, 20, 30, 40}, 10},
  {"sonar_exits", strings::kSetSonarExits, CatSonar, strings::kHelpSonarKind, Unit::Toggle, {0, 1}, 1},
  {"sonar_doors", strings::kSetSonarDoors, CatSonar, strings::kHelpSonarKind, Unit::Toggle, {0, 1}, 1},
  {"sonar_people", strings::kSetSonarPeople, CatSonar, strings::kHelpSonarKind, Unit::Toggle, {0, 1}, 1},
  {"sonar_shops", strings::kSetSonarShops, CatSonar, strings::kHelpSonarKind, Unit::Toggle, {0, 1}, 1},
  {"sonar_objects", strings::kSetSonarThings, CatSonar, strings::kHelpSonarKind, Unit::Toggle, {0, 1}, 1},
  {"sonar_events", strings::kSetSonarEvents, CatSonar, strings::kHelpSonarKind, Unit::Toggle, {0, 1}, 1},
  {"sonar_fragments", strings::kSetSonarFragments, CatSonar, strings::kHelpSonarKind, Unit::Toggle, {0, 1}, 1},
  {"master_volume", strings::kSetMasterVolume, CatVolume, strings::kHelpMasterVolume, Unit::Percent, kPercents, 100},
  {"sonar_volume", strings::kSetSonarVolume, CatVolume, strings::kHelpSonarVolume, Unit::Percent, kPercents, 50},     // the Sonar bus
  {"wall_volume", strings::kSetWallVolume, CatVolume, strings::kHelpWallVolume, Unit::Percent, kPercents, 50},
  {"sound_volume", strings::kSetSoundVolume, CatVolume, strings::kHelpSoundVolume, Unit::Percent, kPercents, 50},     // the Cues bus
  {"description_volume", strings::kSetDescriptionVolume, CatVolume, strings::kHelpDescriptionVolume, Unit::Percent, kPercents, 100},
  // how positional cues are placed: Dark Vision's stereo model, Steam Audio's HRTF, or a plain pan (a new key: the
  // old "hrtf" toggle's saved 1 would have kept the HRTF)
  {"spatial", strings::kSetSpatial, CatSound, strings::kHelpSpatial, Unit::Choice, {SpatialStereo, SpatialHrtf, SpatialPan}, SpatialStereo,
   {strings::kSpatialStereo, strings::kSpatialHrtf, strings::kSpatialPan}},
  {"behind_pitch", strings::kSetBehindPitch, CatSound, strings::kHelpBehindPitch, Unit::Toggle, {0, 1}, 1},
  {"voiced_lines", strings::kSetVoicedLines, CatDialogue, strings::kHelpVoicedLines, Unit::Choice, {VoicedSilent, VoicedName, VoicedRead}, VoicedSilent,
   {strings::kVoicedRead, strings::kVoicedName, strings::kVoicedSilent}},
  {"voice_end_sound", strings::kSetVoiceEndSound, CatDialogue, strings::kHelpVoiceEndSound, Unit::Choice, {EndOff, EndNext, EndPage, EndMessage, EndCursor}, EndNext,
   {strings::kEndNext, strings::kEndPage, strings::kEndMessage, strings::kEndCursor, strings::kOff}},
  // the screen reader reads a cutscene's subtitles (msg.cpp)
  {"subtitles", strings::kSetSubtitles, CatDialogue, strings::kHelpSubtitles, Unit::Toggle, {0, 1}, 0},
  // the marks drawn over a character's head for a moment: "Question mark over Junpei" (emotes.cpp)
  {"emote_marks", strings::kSetEmotes, CatDialogue, strings::kHelpEmotes, Unit::Toggle, {0, 1}, 1},
  // the descriptions of the animated story movies and of the story scenes in the 3D engine (ad.cpp): the narrator's
  // voice or the screen reader. A saved 1 from the old on/off toggle is DescAudio.
  {"audio_description", strings::kSetAudioDescription, CatDescription, strings::kHelpAudioDescription, Unit::Choice, {DescOff, DescAudio, DescReader}, DescAudio,
   {strings::kOff, strings::kDescAudio, strings::kDescReader}},
  // the 3D scenes: described, described once (a description heard is not read again), or not; and by whom. The saved
  // scene_description=2 of the old row (Off / narrator / screen reader) meant the screen reader: load() moves it.
  {"scene_description", strings::kSetSceneDescription, CatDescription, strings::kHelpSceneDescription, Unit::Choice, {SceneOff, SceneOnce, SceneOn}, SceneOn,
   {strings::kOff, strings::kOn, strings::kSceneOnce}},
  {"scene_voice", strings::kSetSceneVoice, CatDescription, strings::kHelpSceneVoice, Unit::Choice, {DescAudio, DescReader}, DescAudio,
   {strings::kOff, strings::kDescAudio, strings::kDescReader}},
  // the narrator of 3D scenes reads faster, its pitch kept (core/time_stretch, ad.cpp); movies keep their timing
  {"scene_speed", strings::kSetSceneSpeed, CatDescription, strings::kHelpSceneSpeed, Unit::Choice, {0, 1, 2, 3}, 0,
   {strings::kOff, strings::kFaster25, strings::kFaster50, strings::kFaster75}},
  // a 3D scene's description pauses it, like a message window, until Enter (A) (ad.cpp); off: said over it. Movies never wait
  {"description_wait", strings::kSetDescriptionWait, CatDescription, strings::kHelpDescriptionWait, Unit::Toggle, {0, 1}, 1},
  {"trigger_delay", strings::kSetTriggerDelay, CatControls, strings::kHelpTriggerDelay, Unit::Ms, {0, 100, 150, 250}, 150},
  {"entry_hints", strings::kSetEntryHints, CatControls, strings::kHelpEntryHints, Unit::Toggle, {0, 1}, 0},
  // the world's time runs faster while a menu is up (menuspeed.cpp): its index into menuspeed's scales
  {"menu_speed", strings::kSetMenuSpeed, CatControls, strings::kHelpMenuSpeed, Unit::Choice, {0, 1, 2, 3}, 0,
   {strings::kOff, strings::kSpeed4, strings::kSpeed8, strings::kSpeed16}},
  // the mod's own lines: the game's language, or one chosen (core::lang::Code + 1; language.cpp). Each language named
  // in itself.
  {"language", strings::kSetLanguage, CatLanguage, strings::kHelpLanguage, Unit::Choice, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}, 0,
   language_labels()},
};
static int g_value[Count] = {};   // load() fills it from kDefs, then the file

int get(Id id) { return id >= 0 && id < Count ? g_value[id] : 0; }

static std::wstring file() {
  std::wstring p = log::path();
  p = p.substr(0, p.find_last_of(L'\\') + 1);
  // Dev launches (unfocused) keep their own file: tests never change the player's settings.
  return p + (env_flag(L"P3A_NOFOCUS") ? L"settings-dev.ini" : L"settings.ini");
}

static void save() {
  FILE* f = _wfopen(file().c_str(), L"w");
  if (!f) { log::write("settings: cannot write the file"); return; }
  for (int i = 0; i < Count; ++i) fprintf(f, "%s=%d\n", kDefs[i].key, g_value[i]);
  fclose(f);
}

static void apply(Id id) {
  if (id == WallTones && !env_flag(L"P3A_NOWALLTONES")) walltones::set_mode(g_value[id]);
  if (id == WallRange) walltones::set_range(g_value[id] * 100.0f);
  if (id == MasterVolume) audio::set_master_volume(g_value[id] / 100.0f);
  if (id == SoundVolume) audio::set_bus_volume(audio::Bus::Cues, g_value[id] / 100.0f);
  if (id == SonarVolume) audio::set_bus_volume(audio::Bus::Sonar, g_value[id] / 100.0f);
  if (id == WallVolume) audio::set_bus_volume(audio::Bus::Walls, g_value[id] / 100.0f);
  if (id == DescriptionVolume) audio::set_bus_volume(audio::Bus::Narration, g_value[id] / 100.0f);
  if (id == Spatial) audio::set_spatial(g_value[id]);
  if (id == Language) language::apply(g_value[id]);
}

void set(Id id, int value) {
  if (id < 0 || id >= Count) return;
  if (id == RelaxedReaper && (value != 0) != (g_value[id] != 0)) shadow::set_relaxed_reaper(value != 0);
  g_value[id] = value;
  apply(id);
  save();
}

static void load() {
  for (int i = 0; i < Count; ++i) g_value[i] = kDefs[i].def;
  if (FILE* f = _wfopen(file().c_str(), L"r")) {
    char line[256];
    std::vector<std::pair<std::string, int>> saved;
    while (fgets(line, sizeof line, f)) {
      std::string key; int v;
      if (core::parse_setting(line, key, v)) saved.emplace_back(key, v);
    }
    fclose(f);
    // a file from before scene_voice: its scene_description=2 was the screen reader, not "suppress repeated"
    const bool voice_saved = std::ranges::any_of(saved, [](const auto& kv) { return kv.first == "scene_voice"; });
    for (auto [key, v] : saved) {
      if (key == "scene_description" && v == DescReader && !voice_saved) {
        g_value[SceneDescription] = SceneOn;
        g_value[SceneVoice] = DescReader;
        continue;
      }
      for (int i = 0; i < Count; ++i)   // a value the option does not offer (a hand edit) keeps the default
        if (key == kDefs[i].key && std::ranges::find(kDefs[i].values, v) != kDefs[i].values.end()) g_value[i] = v;
    }
  }
  for (int i = 0; i < Count; ++i) apply((Id)i);
}

static std::string label(Id id) {
  int v = g_value[id];
  switch (kDefs[id].unit) {
    case Unit::Toggle: return v ? strings::kOn.c_str() : strings::kOff.c_str();
    case Unit::Meters: return core::meters((float)v);
    case Unit::Percent: return strings::count(v, strings::kPercent);
    case Unit::Choice:
      // another language than English has no narrator: its descriptions go to the screen reader (ad.cpp)
      if (!core::lang::english() && ((id == AudioDescription && v == DescAudio) || id == SceneVoice)) return strings::kDescReader.c_str();
      return v >= 0 && v < (int)kDefs[id].labels.size() ? std::string(kDefs[id].labels[v].c_str()) : std::to_string(v);
    default: return v ? std::format("{} {}", v, strings::kMilliseconds) : std::string(strings::kOff);
  }
}

// ---- the menu, on core/navigator like every bespoke menu: one item per option in its category, "Mod keys" (reads
// the mod's keys) last. The navigator owns focus, positions and edges; Left/Right
// adjust the focused option (on_adjust), Space/Enter steps it on. It plays the game's own menu sounds (the camp menu's
// open, close, cursor and confirm cues; Config's option cue on a change). Keys reach it through keys::set_modal. ----
static bool g_open = false;

static void change(Id id, int delta) {
  const auto& vals = kDefs[id].values;
  int at = core::value_index(vals, g_value[id]);
  // Space (0) steps forward and wraps; left and right stop at the ends.
  int next = core::step_index(at, (int)vals.size(), delta);
  if (next == at) return;   // state_text says the value again
  set(id, vals[next]);
  if (id == VoiceEndSound && g_value[id] != EndNext) voice::play_end_sound();   // a preview, in place of the menu's sound
  else if (sonar::preview(id)) {}   // a kind's own sound, or one at the new volume
  else voice::play_system_sound(voice::CueOption);   // the game's Config plays it on every value change (FUN_141391c40)
}

// The sound test (the last category): row i of strings::kSoundTests plays its sound, from the menu, wherever the
// player is and whatever is switched off. In the order of that table.
static void play_test(int i) {
  using core::SignalCue;
  const audio::Spot ahead{};
  switch (i) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: sonar::demo(i); break;
    case 7: sonar::demo(2, true); break;
    case 8: case 9: case 10: shadow::demo(i - 8); break;
    case 11: audio::signal((int)SignalCue::Lost, 1.1f, ahead); break;
    case 12: case 13: case 14: sight::demo(i - 12); break;   // right under the Shadow's own sounds
    case 15: audio::signal_here((int)SignalCue::Reach, 1.2f); break;
    case 16: audio::signal_here((int)SignalCue::Ambush, 1.2f); break;
    case 17: case 18: case 19: case 20: walltones::demo(i - 17); break;
    case 21: audio::signal((int)SignalCue::Layer, 0.9f, ahead); break;
  }
}

static void open_keys();
struct Menu : ui::Screen {
  std::string_view key() const override { return "mod_settings"; }
  std::string screen_name() const override { return strings::kModSettings.c_str(); }
  bool wrap() const override { return true; }
  void build(ui::GraphBuilder& b) override {
    namespace k = ui::announcement_kinds;
    for (int c = 0; c < CatCount; ++c) {
      b.begin_stop(std::format("cat{}", c));
      b.push_context(kCategoryNames[c].c_str());
      for (int i = 0; i < Count; ++i) {
        Id id = (Id)i;
        if (kDefs[i].cat != c) continue;
        auto v = std::make_shared<ui::NodeVtable>();
        // What the setting does is read with the row, after its position (the user's call, 2026-11-11: no details
        // keys in this menu).
        v->announcements = {ui::NodeAnnouncement([id] { return std::string(kDefs[id].name); }, false, k::kLabel),
                            ui::NodeAnnouncement([id] { return label(id); }, true, k::kValue),
                            ui::NodeAnnouncement([id] { return keys::fill(kDefs[id].help.c_str()); }, false, k::kTooltip)};
        v->on_adjust = [id](int sign, bool) { change(id, sign); };
        v->on_activate = [id] { change(id, 0); };
        v->state_text = [id] { return label(id); };
        b.add_item(ui::ControlId::structural(kDefs[i].key), v);
      }
      if (c == CatControls) {
        auto v = std::make_shared<ui::NodeVtable>();
        v->announcements = {ui::NodeAnnouncement([] { return std::string(strings::kModKeys); }, false, k::kLabel),
                            ui::NodeAnnouncement([] { return std::string(strings::kHelpModKeys); }, false, k::kTooltip)};
        v->on_activate = [] { open_keys(); };
        b.add_item(ui::ControlId::structural("mod_keys"), v);
      }
      b.pop_context();
    }
    // The sound test: Space or A plays the row's sound; the row says what the sound means. No cursor sound on
    // these rows' activation: only the sound asked for is heard.
    b.begin_stop("sound_test");
    b.push_context(strings::kCatSoundTest.c_str());
    for (int i = 0; i < (int)std::size(strings::kSoundTests); ++i) {
      const strings::SoundTest& t = strings::kSoundTests[i];
      auto v = std::make_shared<ui::NodeVtable>();
      v->announcements = {ui::NodeAnnouncement([&t] { return std::string(t.name); }, false, k::kLabel),
                          ui::NodeAnnouncement([&t] { return std::string(t.help); }, false, k::kTooltip)};
      v->on_activate = [i] { play_test(i); };
      b.add_item(ui::ControlId::structural(std::format("test{}", i)), v);
    }
    b.pop_context();
  }
};
static Menu g_menu;

// ---- the Mod keys page (Mod keys in Controls, Enter): one row per keyboard binding (what it does, then its key),
// "Read all keys" first and "Reset all keys to default" last. Enter (A) on a binding waits for the next key: it takes
// it (a binding already there trades keys with it), Escape (B) cancels, a key the game needs buzzes and waits on.
// Delete (X) puts the focused one back on its own key. Escape (B) goes back to the settings, on Mod keys. ----
enum class Page { Main, Keys };
static Page g_page = Page::Main;
static int g_capture = -1;   // the binding waiting for its new key, else -1
constexpr int kCueBuzzer = 8;   // the game's refusal (a list entry that cannot be chosen; FUN_141286af0(8))

static void start_capture(int i) {
  g_capture = i;
  voice::play_system_sound(voice::CueDecide);
  speech::speak(std::format("{} {}. {}", strings::kKeysPress, keys::binding_help(i), strings::kKeysPressCancel()), true);
}

// ". Next point of interest moves to Period": each listed binding a change moved.
static std::string moved_text(const std::vector<int>& moved) {
  std::string s;
  for (int j : moved) s += std::format(". {} {} {}", keys::binding_help(j), strings::kKeysMovesTo, keys::binding_key(j));
  return s;
}

static void reset_one(int i) {
  if (keys::binding_default(i)) { voice::play_system_sound(kCueBuzzer); speech::speak(std::format("{}, {}", keys::binding_key(i), strings::kKeysAlreadyDefault), true); return; }
  std::vector<int> moved;
  if (keys::reset_binding(i, moved) != keys::Rebind::Done) { voice::play_system_sound(kCueBuzzer); return; }
  voice::play_system_sound(voice::CueOption);
  speech::speak(std::format("{}, {}{}", keys::binding_key(i), strings::kKeysBackToDefault, moved_text(moved)), true);
}

struct KeysMenu : ui::Screen {
  std::string_view key() const override { return "mod_keys"; }
  std::string screen_name() const override { return strings::kModKeys.c_str(); }
  bool wrap() const override { return true; }
  void build(ui::GraphBuilder& b) override {
    namespace k = ui::announcement_kinds;
    b.begin_stop("keys");
    {
      auto v = std::make_shared<ui::NodeVtable>();
      v->announcements = {ui::NodeAnnouncement([] { return std::string(strings::kKeysReadAll); }, false, k::kLabel),
                          ui::NodeAnnouncement([] { return std::string(strings::kHelpKeysReadAll); }, false, k::kTooltip)};
      v->on_activate = [] { voice::play_system_sound(voice::CueDecide); speech::speak(keys::help(), true); };
      b.add_item(ui::ControlId::structural("read_all"), v);
    }
    for (int i : keys::keyboard_bindings()) {
      auto v = std::make_shared<ui::NodeVtable>();
      v->announcements = {ui::NodeAnnouncement([i] { return keys::binding_help(i); }, false, k::kLabel),
                          ui::NodeAnnouncement([i] { return keys::binding_key(i); }, false, k::kValue)};
      v->on_activate = [i] { start_capture(i); };   // its Shift back, if any, moves with it
      b.add_item(ui::ControlId::structural(std::format("bind{}", i)), v);
    }
    {
      auto v = std::make_shared<ui::NodeVtable>();
      v->announcements = {ui::NodeAnnouncement([] { return std::string(strings::kKeysResetAll); }, false, k::kLabel)};
      v->on_activate = [] {
        keys::reset_all();
        voice::play_system_sound(voice::CueOption);
        speech::speak(strings::kKeysResetDone.c_str(), true);
      };
      b.add_item(ui::ControlId::structural("reset_all"), v);
    }
  }
};
static KeysMenu g_keys_menu;
static std::optional<ui::ControlId> g_move_from;   // the focus before the key being handled
static ui::GraphNavigator& nav();
// The cursor sound, unless the press moved nothing: at a list's first or last row the row is said again without it,
// as in the game's menus (the user's call, 2026-11-11).
static void move_sound() {
  auto at = nav().focused_id();
  if (g_move_from && at && *g_move_from == *at) return;
  voice::play_system_sound(voice::CueCursor);
}
static ui::GraphNavigator& nav() {
  static ui::GraphNavigator n(ui::NavigatorHost{[](std::string_view t, bool interrupt) { speech::speak(t, interrupt); },
                                                [] { move_sound(); },
                                                [] { return g_open; }, {}, {}, core::place_of});
  return n;
}

// One key through the navigator, then its pull (the navigator rebuilds and announces in ensure_focus).
static void action(std::string_view a) {
  g_move_from = nav().focused_id();
  nav().on_action(a);
  nav().ensure_focus();
  g_move_from.reset();
}

static int held_mods() {
  int m = keys::None;
  if (GetKeyState(VK_SHIFT) & 0x8000) m |= keys::Shift;
  if (GetKeyState(VK_CONTROL) & 0x8000) m |= keys::Ctrl;
  if (GetKeyState(VK_MENU) & 0x8000) m |= keys::Alt;
  return m;
}

static void open_keys() {
  g_page = Page::Keys;
  g_capture = -1;
  voice::play_system_sound(voice::CueDecide);
  nav().screen_closed(&g_keys_menu);   // every visit starts on its first row
  nav().attach(&g_keys_menu);
  nav().settle_silently();
  speech::speak(strings::kModKeys.c_str(), true);
  nav().announce_current();
}

// Back to the settings, on the Mod keys row (the navigator kept the settings' own focus).
static void close_keys() {
  g_page = Page::Main;
  g_capture = -1;
  voice::play_system_sound(voice::CueCancel);
  nav().screen_closed(&g_keys_menu);
  nav().attach(&g_menu);
  nav().settle_silently();
  nav().announce_current();
}

static int focused_binding() {
  auto f = nav().focused_id();
  if (!f || !f->structural_key().is_string()) return -1;
  const std::string s = f->structural_key().text();
  return s.starts_with("bind") ? std::atoi(s.c_str() + 4) : -1;
}

// The key a binding waits for. Modifiers alone wait on (Shift+1 is Shift, then 1).
static void capture_key(uint32_t vk, bool repeat) {
  if (repeat) return;
  switch (vk) {
    case VK_SHIFT: case VK_CONTROL: case VK_MENU: case VK_LSHIFT: case VK_RSHIFT: case VK_LCONTROL: case VK_RCONTROL:
    case VK_LMENU: case VK_RMENU: case VK_LWIN: case VK_RWIN: case VK_CAPITAL: case VK_NUMLOCK: case VK_SCROLL: return;
    default: break;
  }
  const int mods = held_mods();
  const int i = g_capture;
  if (vk == VK_ESCAPE && mods == keys::None) {
    g_capture = -1;
    voice::play_system_sound(voice::CueCancel);
    speech::speak(std::format("{}, {}", strings::kKeysCancelled, keys::binding_key(i)), true);
    return;
  }
  if (keys::reserved(vk, mods)) {
    voice::play_system_sound(kCueBuzzer);
    speech::speak(std::format("{} {}", keys::key_label(vk, mods), strings::kKeysReserved), true);
    return;   // still waiting
  }
  std::vector<int> moved;
  switch (keys::rebind(i, vk, mods, moved)) {
    case keys::Rebind::NeedsNoShift:   // still waiting
      voice::play_system_sound(kCueBuzzer);
      speech::speak(std::format("{} {}", keys::key_label(vk, mods), strings::kKeysNeedsNoShift), true);
      return;
    case keys::Rebind::BackKey:
      voice::play_system_sound(kCueBuzzer);
      speech::speak(std::format("{}. {}", strings::fmt(strings::kGoesBackForFmt, keys::key_label(vk, mods), keys::binding_help(keys::plain_of(vk, mods))), strings::kKeysPressAnother), true);
      return;
    case keys::Rebind::Refused: g_capture = -1; voice::play_system_sound(kCueBuzzer); return;
    case keys::Rebind::Done: break;
  }
  g_capture = -1;
  voice::play_system_sound(voice::CueOption);   // the game's Config: a value changed
  speech::speak(keys::binding_key(i) + moved_text(moved), true);
}

static void on_key(uint32_t vk, bool repeat) {
  using namespace ui::ui_actions;
  if (g_capture >= 0) { capture_key(vk, repeat); return; }
  // The settings key (F2, or where the player put it) closes the whole menu, from either page.
  if (!repeat && keys::is_key("settings", vk, held_mods())) { close(); return; }
  if (g_page == Page::Keys) {
    switch (vk) {
      case VK_ESCAPE: case VK_BACK: if (!repeat) close_keys(); return;
      case VK_DELETE: if (!repeat && focused_binding() >= 0) reset_one(focused_binding()); return;
      case VK_F1: if (!repeat) speech::speak(strings::kModKeysPageKeys(), true); return;
      case VK_LEFT: case VK_RIGHT: return;
      default: break;
    }
  }
  switch (vk) {
    case VK_UP: action(Up); break;
    case VK_DOWN: action(Down); break;
    case VK_LEFT: action(Left); break;
    case VK_RIGHT: action(Right); break;
    case VK_HOME: action(Home); break;
    case VK_END: action(End); break;
    case VK_TAB: action(GetKeyState(VK_SHIFT) & 0x8000 ? Prev : Next); break;
    case VK_NEXT: action(Next); break;
    case VK_PRIOR: action(Prev); break;
    case VK_SPACE: case VK_RETURN: if (!repeat) action(Activate); break;
    case VK_ESCAPE: case VK_BACK: if (!repeat) close(); break;
    case VK_F1: if (!repeat) speech::speak(strings::kModSettingsKeys(), true); break;
    default: break;
  }
}

static void on_pad(uint16_t button, bool repeat) {
  using namespace ui::ui_actions;
  if (g_capture >= 0) {   // the new key comes from the keyboard; B cancels
    if (button == XINPUT_GAMEPAD_B && !repeat) {
      const int i = g_capture;
      g_capture = -1;
      voice::play_system_sound(voice::CueCancel);
      speech::speak(std::format("{}, {}", strings::kKeysCancelled, keys::binding_key(i)), true);
    }
    return;
  }
  if (g_page == Page::Keys) {
    switch (button) {
      case XINPUT_GAMEPAD_B: if (!repeat) close_keys(); return;
      case XINPUT_GAMEPAD_BACK: if (!repeat) close(); return;
      case XINPUT_GAMEPAD_X: if (!repeat && focused_binding() >= 0) reset_one(focused_binding()); return;
      case XINPUT_GAMEPAD_START: if (!repeat) speech::speak(strings::kModKeysPageKeys(), true); return;
      case XINPUT_GAMEPAD_DPAD_LEFT: case XINPUT_GAMEPAD_DPAD_RIGHT: return;
      default: break;
    }
  }
  switch (button) {
    case XINPUT_GAMEPAD_DPAD_UP: action(Up); break;
    case XINPUT_GAMEPAD_DPAD_DOWN: action(Down); break;
    case XINPUT_GAMEPAD_DPAD_LEFT: action(Left); break;
    case XINPUT_GAMEPAD_DPAD_RIGHT: action(Right); break;
    case XINPUT_GAMEPAD_RIGHT_SHOULDER: action(Next); break;
    case XINPUT_GAMEPAD_LEFT_SHOULDER: action(Prev); break;
    case XINPUT_GAMEPAD_A: if (!repeat) action(Activate); break;
    case XINPUT_GAMEPAD_B: case XINPUT_GAMEPAD_BACK: if (!repeat) close(); break;
    case XINPUT_GAMEPAD_START: if (!repeat) speech::speak(strings::kModSettingsKeys(), true); break;
    default: break;
  }
}

void open() {
  if (g_open) return;
  // In free roam the field stands still while the menu is up, as under the camp menu (asked by a player,
  // 2026-11-19): the camp's own pause on the game's stack. Asked before the menu takes the keys (exploring() is false
  // under a mod modal).
  bool still = world::exploring();
  g_open = true;
  g_page = Page::Main;
  g_capture = -1;
  if (still) screens::hold_pause(true);
  keys::set_modal(on_key, on_pad);
  input::set_modal(true);
  voice::play_system_sound(voice::CueMenuOpen);
  // Every opening starts on the first option: a fresh state, the title, then the focused item (queued after it).
  nav().screen_closed(&g_menu);
  nav().attach(&g_menu);
  nav().settle_silently();   // the focus is read after the title
  speech::speak(strings::kModSettings.c_str(), true);
  nav().announce_current();
}

void close() {
  if (!g_open) return;
  g_open = false;
  g_capture = -1;
  if (g_page == Page::Keys) { g_page = Page::Main; nav().screen_closed(&g_keys_menu); }
  screens::hold_pause(false);
  keys::set_modal(nullptr, nullptr);
  input::set_modal(false);
  voice::play_system_sound(voice::CueMenuClose);
  speech::speak(strings::kModSettingsClosed.c_str(), true);
}

static std::string focused_key() {
  auto f = nav().focused_id();
  return f && f->structural_key().is_string() ? f->structural_key().text() : std::string();
}

void install() {
  load();
  std::wstring f = file();
  log::writef("settings: loaded {}", log::utf8(std::u16string(f.begin(), f.end())));
  dev::route("/settings", [](const dev::Request& r, int&) {
    // /settings?set=poi_range&v=40 | ?open=1 | ?close=1 | ?keys=1 (the Mod keys page) | ?vk=N[&shift=1] (a key to the
    // open menu, as the keyboard sends it: posted keys reach the game's own handlers instead)
    std::string key = dev::arg(r, "set");
    int v = (int)dev::arg_int(r, "v", 0);
    bool op = dev::has(r, "open"), cl = dev::has(r, "close"), kp = dev::has(r, "keys");
    uint32_t vk = (uint32_t)dev::arg_int(r, "vk", 0);
    return dev::on_game([=] {
      for (int i = 0; i < Count; ++i) if (!key.empty() && key == kDefs[i].key) set((Id)i, v);
      if (op) open();
      if (kp && g_open) open_keys();
      if (vk && g_open) on_key(vk, false);
      if (cl) close();
      std::string s = std::format("open={} page={} capture={} focus={}\n", g_open, g_page == Page::Keys ? "keys" : "main", g_capture, focused_key());
      for (int i = 0; i < Count; ++i) s += std::format("{}={} ({})\n", kDefs[i].key, g_value[i], label((Id)i));
      return s;
    });
  }, "?set=key&v=N ?open=1 ?close=1 the mod's settings");
}
}  // namespace p3a::settings
