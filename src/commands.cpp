// The player's keys (README.md lists them). Chosen from keys P3R's keyboard layout leaves free:
// punctuation on the right of the keyboard and F1.
#include "commands.h"
#include "area.h"
#include "audio.h"
#include "core/sonar_cues.h"
#include "core/strings.h"
#include "keys.h"
#include "msg.h"
#include "nav.h"
#include "party.h"
#include "settings.h"
#include "poi.h"
#include "calendar.h"
#include "screens/screen.h"
#include "screens/battle.h"
#include "speech.h"
#include "topdown.h"
#include "stats.h"
#include "social.h"
#include "sonar.h"
#include "world.h"
#include <windows.h>
#include <xinput.h>
#include <format>

namespace p3a::commands {
static void where_am_i() {
  // A shop hides the hero: the place is then the one the hero walked in from (poi::area_name).
  std::string area = poi::area_name();
  if (!world::player() && area == strings::kUnknownArea) { speech::speak(strings::kNotInField, true); return; }
  // The date first, then the area (the player's order, 2026-11-14); each its own utterance, so the screen reader
  // pauses between them.
  std::vector<std::string> parts{calendar::describe(calendar::now()), area};
  if (int m = stats::money(); m >= 0) parts.push_back(std::format("{} {}", m, strings::kYen));
  // The story objective with the line stacked under it (the field's top-right panel, the last one shown).
  std::string goal = poi::objectives();
  parts.push_back(goal.empty() ? std::string(strings::kNoObjective) : std::string(strings::kObjective) + ": " + goal);
  // Pressed again with nothing else said and no game key since, it steps through the parts one at a time (the
  // player's call, 2026-11-17): the first press reads them all, the next ones the date, the area, the yen and the
  // objective, then all of them again. Each press rebuilds the parts, so a step reads them as they stand now.
  static uint64_t spoken = ~0ull, key_ms = 0;
  static size_t step = 0;   // 0 = all of them, n = part n-1
  step = (speech::count() == spoken && keys::game_key_ms() == key_ms) ? (step + 1) % (parts.size() + 1) : 0;
  if (step == 0) speech::speak_parts(parts, true);
  else speech::speak(parts[step - 1], true);
  spoken = speech::count();
  key_ms = keys::game_key_ms();
}

static void review() {
  // A screen open over a conversation (the rank card and its poem, the log) is what is in front: it answers first.
  auto* s = screens::current();
  bool over = s && s->over_messages();
  if (msg::current().open && !over) { msg::repeat(); return; }
  if (s) { std::string d = s->describe(); if (!d.empty()) { speech::speak(d, true); return; } }
  if (msg::current().open) { msg::repeat(); return; }
  speech::speak(strings::kNothingToReview, true);
}

// F1: the keys of what is in front of the player (a message window, the current screen, or the field). Screens no
// longer say their keys on entry (the player's choice, 2026-10-28).
static void screen_keys() {
  msg::Current m = msg::current();
  std::string k;
  // A screen opened over a message window (the log over a conversation) has the keys.
  bool over = screens::current() && screens::current()->over_messages();
  if (m.blocking && !over) k = m.kind == "Tutorial" ? strings::kTutorialKeys() : !m.choices.empty() ? strings::kChooseKeys()
                    : m.kind == "System" ? strings::kSpaceContinues() : strings::kDialogueKeys();
  else if (screens::current()) {
    k = screens::keys();
    // Wherever the detail buffer has something to read (a battle's units, a row with a description kept off it).
    if (screens::battle_details::in_focus()) k += (k.empty() ? "" : " ") + std::string(strings::kDetailKeys());
  }
  else if (world::player()) {
    k = std::string(strings::kFieldKeys()) + " " + (poi::tartarus_floor() > 0 ? std::string(strings::kTartarusKeys()) + " " : std::string());
    // The mod's walk that uses its point: Shift+Period, or on a controller RT on the top-down scan's point.
    if (!strings::pad_hints()) k += std::string(strings::kFieldWalkUseKeys) + " ";
    else if (topdown::active()) k += std::string(strings::kPadScanKeys) + " ";
    k += strings::kModKeysHint();
  }
  if (k.empty()) k = std::string(strings::kNoKeys) + " " + strings::kModKeysHint();
  speech::speak(k, true);
}

// The controller's mod layer opened (both triggers): a tick, and in the field the points of interest at once.
static void pad_layer() {
  audio::signal((int)core::SignalCue::Layer, 0.9f, audio::Spot{});
  if (!screens::current() && !msg::current().blocking && world::player()) poi::announce_list();
}

// Shift+Period: the walk, then Space at the point once its prompt is up (Grim Dark's "walk there and use it").
static void walk_and_use() {
  if (!world::exploring()) { speech::speak(strings::kNotInField, true); return; }
  poi::Poi p;
  if (!poi::selected(p)) { speech::speak(strings::kNothingSelected, true); return; }
  nav::walk_to(p.obj, p.name, true);
}

// Shift+semicolon: the selection again, from where the player is now (Grim Dark's ; re-ping of the reviewed thing).
static void selected_again() {
  poi::Poi p;
  if (!poi::selected(p)) { speech::speak(strings::kNothingSelected, true); return; }
  speech::speak(poi::describe(p), true);
  sonar::selected(p);
}

static void walk_selected() {
  if (nav::walking()) { nav::stop(true); return; }
  poi::Poi p;
  if (!poi::selected(p)) { speech::speak(strings::kNothingSelected, true); return; }
  nav::walk_to(p.obj, p.name);
}


void install() {
  using namespace keys;
  bind(VK_F1, None, "help", strings::kKeyHelpScreenKeys, screen_keys);
  bind(VK_F1, Shift, "help.mod", strings::kKeyHelpModKeys, [] { speech::speak(keys::help(), true); });
  bind(VK_F2, None, "settings", strings::kKeyHelpSettings, settings::open);
  bind(VK_F3, None, "sonar", strings::kKeyHelpSonar, sonar::toggle);
  bind(VK_OEM_2, None, "where", strings::kKeyHelpWhere, where_am_i);                                             // /
  bind(VK_OEM_2, Shift, "stats", strings::kKeyHelpStats, [] {                                                    // Shift+/
    std::string s = stats::describe();
    speech::speak(s.empty() ? strings::kNotInField : s, true);
  });
  bind(VK_OEM_5, Shift, "social", strings::kKeyHelpSocial, [] { speech::speak_parts(social::summary_parts(), true); });      // Shift+backslash
  bind(VK_OEM_5, None, "review", strings::kKeyHelpReview, review);                                               // backslash
  bind(VK_OEM_6, None, "poi.next", strings::kKeyHelpPoiNext, [] { poi::next(1); }, true);                        // ]
  bind(VK_OEM_4, None, "poi.prev", strings::kKeyHelpPoiPrev, [] { poi::next(-1); }, true);                       // [
  bind(VK_OEM_6, Shift, "poi.cat.next", strings::kKeyHelpPoiCatNext, [] { poi::next_category(1); });             // Shift+]
  bind(VK_OEM_4, Shift, "poi.cat.prev", strings::kKeyHelpPoiCatPrev, [] { poi::next_category(-1); });            // Shift+[
  bind(VK_OEM_7, Shift, "party", strings::kKeyHelpParty, [] { speech::speak_parts(party::summary_parts(), true); });         // Shift+'
  bind(VK_OEM_7, None, "nav.walk", strings::kKeyHelpWalk, walk_selected);                                        // '
  bind(VK_OEM_1, None, "area", strings::kKeyHelpArea, area::describe);                                           // ;
  // After Grim Dark's review keys: its ; (the reviewed thing again) and Enter (walk there and use it). Shift, as the
  // mod's other second keys: Ctrl is the game's (messages, attack).
  bind(VK_OEM_1, Shift, "poi.again", strings::kKeyHelpPoiAgain, selected_again);                                // Shift+;
  bind(VK_OEM_COMMA, None, "poi.nearest", strings::kKeyHelpPoiNearest, [] { poi::cycle_nearest(1); }, true);      // ,
  bind(VK_OEM_COMMA, Shift, "poi.nearest.prev", strings::kKeyHelpPoiNearestPrev, [] { poi::cycle_nearest(-1); }, true);   // Shift+,
  // Period walks to the selection, beside Comma that chooses it; Shift+Period walks and uses it (Grim Dark's
  // walk-there-and-use, Shift+Enter until 2026-11-14; the user's call). The game binds neither Comma nor Period
  // (Config/DefaultInput.ini has them only in its unused pad emulation, PM_R2 / PM_R3).
  bind(VK_OEM_PERIOD, None, "nav.walk.period", strings::kKeyHelpWalk, walk_selected);                             // .
  bind(VK_OEM_PERIOD, Shift, "nav.use", strings::kKeyHelpWalkUse, walk_and_use);                                  // Shift+.
  // The same keys on a controller: hold both triggers, then (input.cpp keeps these buttons from the game meanwhile).
  struct PadKey { const char* name; uint16_t button; };
  const PadKey pad[] = {
    {"poi.next", XINPUT_GAMEPAD_DPAD_DOWN}, {"poi.prev", XINPUT_GAMEPAD_DPAD_UP},
    {"poi.cat.next", XINPUT_GAMEPAD_DPAD_RIGHT}, {"poi.cat.prev", XINPUT_GAMEPAD_DPAD_LEFT},
    {"nav.walk", XINPUT_GAMEPAD_A}, {"area", XINPUT_GAMEPAD_B}, {"review", XINPUT_GAMEPAD_X}, {"where", XINPUT_GAMEPAD_Y},
    {"stats", XINPUT_GAMEPAD_LEFT_SHOULDER}, {"social", XINPUT_GAMEPAD_RIGHT_SHOULDER}, {"party", XINPUT_GAMEPAD_LEFT_THUMB},
    {"sonar", XINPUT_GAMEPAD_RIGHT_THUMB}, {"help", XINPUT_GAMEPAD_START}, {"settings", XINPUT_GAMEPAD_BACK},
  };
  for (auto [name, button] : pad) bind_pad(name, button);
  on_pad_layer(pad_layer);
  keys::install();
}
}  // namespace p3a::commands
