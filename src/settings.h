#pragma once

namespace p3a::settings {
// The mod's options, saved to %LOCALAPPDATA%\Arcana\settings.ini (settings-dev.ini for dev launches), and the
// mod settings menu that changes them: F2, or both triggers and View on a controller (the game's Config keys say so).
// A new option: an Id here (in the menu's order: the table follows it), a row in settings.cpp's table, its name in strings.h, and its README line.
enum Id { TurnedRooms, AlwaysDash, PoiRange, FloorOnly, WallTones, WallRange, ShadowAlerts, ShadowSight, SightRange, StrikeAssist, RelaxedReaper, AlwaysAdvantage,
          Sonar, SonarScope, SonarRange, SonarExits, SonarDoors, SonarPeople, SonarShops, SonarThings, SonarEvents, SonarFragments,
          MasterVolume, SonarVolume, WallVolume, SoundVolume, DescriptionVolume,
          BehindPitch,
          VoicedLines, VoiceEndSound, Subtitles, AudioDescription, SceneDescription, SceneVoice, SceneSpeed,
          TriggerDelay, EntryHints, MenuSpeed, Language, Count };
int get(Id id);   // the value: 0/1, meters, percent, milliseconds or a choice's index
inline bool on(Id id) { return get(id) != 0; }
// VoicedLines: what the screen reader does with a line the game voices.
enum Voiced { VoicedRead, VoicedName, VoicedSilent };
// VoiceEndSound: what says a voiced line has finished: "Next" spoken, or a game sound (voice.cpp maps them to cues).
enum EndSound { EndNext, EndPage, EndMessage, EndCursor, EndOff };
// SonarScope: which points of interest the sonar sounds for.
enum Scope { ScopeAll, ScopeCategory, ScopeSelected };
// AudioDescription (the animated movies) and SceneVoice (story scenes in the 3D engine): how a description is given,
// by the narrator's recorded voice or as text to the screen reader (ad.cpp). SceneVoice offers no DescOff: that is
// SceneDescription's.
enum Description { DescOff, DescAudio, DescReader };
// SceneDescription: whether the 3D scenes are described, and SceneOnce: a description already heard is not read
// again (core/heard_cues, ad.cpp).
enum SceneMode { SceneOff, SceneOn, SceneOnce };
// SceneSpeed: how much faster the narrator reads a 3D scene's descriptions (0 off, then 25, 50, 75 percent; ad.cpp).
inline double scene_speed_factor(int v) { return 1.0 + 0.25 * v; }
// WallTones: when the tones play (walltones::set_mode). A saved 1 from the old on/off toggle is WallMoving.
enum WallMode { WallOff, WallMoving, WallContinuous };
void set(Id id, int value);   // applies it (wall tones, volume) and saves

// The menu: modal while open (the game gets no keys or buttons; the field keeps running).
void open();
void close();
void install();   // loads and applies the file, binds nothing (commands.cpp binds F2), dev route /settings
}  // namespace p3a::settings
