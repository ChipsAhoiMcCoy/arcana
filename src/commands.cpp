// The player's keys (README.md lists them). Chosen from keys P3R's keyboard layout leaves free:
// punctuation on the right of the keyboard and F1.
#include "commands.h"
#include "area.h"
#include "audio.h"
#include "core/sonar_cues.h"
#include "core/strings.h"
#include "core/text_clean.h"
#include "keys.h"
#include "msg.h"
#include "nav.h"
#include "party.h"
#include "settings.h"
#include "poi.h"
#include "calendar.h"
#include "screens/screen.h"
#include "screens/battle.h"
#include "screens/battle_state.h"
#include "screens/battle_party.h"
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
  if (!world::player() && area == strings::kUnknownArea.c_str()) { speech::speak(strings::kNotInField.c_str(), true); return; }
  // The date first, then the area (the player's order, 2026-11-14); each its own utterance, so the screen reader
  // pauses between them.
  // The moon as the date in the corner shows it: "FULL" on a full moon (an operation night), else the days left to
  // the next ("LIMIT 29" beside the moon from June 11 on); the quarters and the new moon as the calendar marks them
  // (2026-11-24: on 7/7 and 7/8 the date said nothing of either).
  calendar::Now now = calendar::now();
  std::string date = calendar::describe(now);
  if (!date.empty()) {
    if (std::string m = calendar::moon_mark(now.moon); !m.empty()) date += ", " + m;
    if (int d = calendar::days_to_full_moon(now.total); d > 0) date += ", " + strings::fmt(strings::kFullMoonIn, strings::count(d, strings::kDayOne, strings::kDays));
  }
  std::vector<std::string> parts{date, area};
  if (int m = stats::money(); m >= 0) parts.push_back(strings::count(m, strings::kYen));
  // The story objective with the line stacked under it (the field's top-right panel, the last one shown).
  std::string goal = poi::objectives();
  parts.push_back(goal.empty() ? std::string(strings::kNoObjective) : std::string(strings::kObjective) + ": " + goal);
  speech::speak_parts(parts, true);
}

static void review() {
  // A screen open over a conversation (the rank card and its poem, the log) is what is in front: it answers first.
  auto* s = screens::current();
  bool over = s && s->over_messages();
  if (msg::current().open && !over) { msg::repeat(); return; }
  if (s) { std::string d = s->describe(); if (!d.empty()) { speech::speak(d, true); return; } }
  if (msg::current().open) { msg::repeat(); return; }
  speech::speak(strings::kNothingToReview.c_str(), true);
}

// F1: the keys of what is in front of the player (a message window, the current screen, or the field). Screens no
// longer say their keys on entry (the player's choice, 2026-10-28).
static void screen_keys() {
  msg::Current m = msg::current();
  std::string k;
  // A screen opened over a message window (the log over a conversation) has the keys.
  bool over = screens::current() && screens::current()->over_messages();
  // A System notice, or a page a screen opened itself (a dictionary term), has no log, Auto or fast-forward; a System
  // question is answered yes or no.
  bool own = screens::current() && screens::current()->own_messages();
  if (m.blocking && !over) k = m.kind == "Tutorial" ? strings::kTutorialKeys() : !m.choices.empty() ? strings::kChooseKeys()
                    : m.kind == "System" && core::is_question(m.text) ? strings::kYesNoHint()
                    : m.kind == "System" || own ? strings::kSpaceContinues() : strings::kDialogueKeys();
  else if (screens::current()) {
    k = screens::keys();
    // Wherever the detail buffer has something to read (a battle's units, a row with a description kept off it).
    if (screens::battle_details::in_focus()) k += (k.empty() ? "" : " ") + std::string(strings::kDetailKeys());
  }
  else if (ue::UObject* btl = screens::battle_core(); btl && ue::call_ret<bool>(btl, "CheckRequestRushMode")) k = strings::kRushRunningKeys();
  else if (world::player()) {
    k = std::string(strings::kFieldKeys()) + " " + (poi::tartarus_floor() > 0 ? std::string(strings::kTartarusKeys()) + " " : std::string());
    // In town with Network Functions on (flag 0x40000068) and past its tutorial's lock (0x4000002D), N (View) shows
    // what other players did today (screens/net_voice.cpp).
    if (poi::tartarus_floor() == 0 && party::flag(0x40000068) && !party::flag(0x4000002D)) k += std::string(strings::kNetActionKey()) + " ";
    // The mod's walk that uses its point: Shift+Period, or on a controller RT on the top-down scan's point.
    if (!strings::pad_hints()) k += keys::fill(strings::kFieldWalkUseKeys.c_str()) + " ";
    else if (topdown::active()) k += std::string(strings::kPadScanKeys) + " ";
    k += keys::fill(strings::kModKeysHint());
  }
  if (k.empty()) k = std::string(strings::kNoKeys) + " " + keys::fill(strings::kModKeysHint());
  speech::speak(k, true);
}

// The controller's mod layer opened (both triggers): a tick, and in the field the points of interest at once.
static void pad_layer() {
  audio::signal((int)core::SignalCue::Layer, 0.9f, audio::Spot{});
  if (!screens::current() && !msg::current().blocking && world::player()) poi::announce_list();
}

// Shift+Period: the walk, then Space at the point once its prompt is up (Grim Dark's "walk there and use it").
static void walk_and_use() {
  if (!world::exploring()) { speech::speak(strings::kNotInField.c_str(), true); return; }
  poi::Poi p;
  if (!poi::selected(p)) { speech::speak(strings::kNothingSelected.c_str(), true); return; }
  nav::walk_to(p.obj, p.name, true);
}

// Shift+semicolon: the selection again, from where the player is now (Grim Dark's ; re-ping of the reviewed thing).
static void selected_again() {
  poi::Poi p;
  if (!poi::selected(p)) { speech::speak(strings::kNothingSelected.c_str(), true); return; }
  speech::speak(poi::describe(p), true);
  sonar::selected(p);
}

static void walk_selected() {
  if (nav::walking()) { nav::stop(true); return; }
  poi::Poi p;
  if (!poi::selected(p)) { speech::speak(strings::kNothingSelected.c_str(), true); return; }
  nav::walk_to(p.obj, p.name);
}


void install() {
  using namespace keys;
  bind(VK_F1, None, "help", strings::kKeyHelpScreenKeys.en, screen_keys);
  bind(VK_F1, Shift, "help.mod", strings::kKeyHelpModKeys.en, [] { speech::speak(keys::help(), true); });
  bind(VK_F2, None, "settings", strings::kKeyHelpSettings.en, settings::open);
  bind(VK_F3, None, "sonar", strings::kKeyHelpSonar.en, sonar::toggle);
  bind(VK_OEM_2, None, "where", strings::kKeyHelpWhere.en, where_am_i);                                             // /
  bind(VK_OEM_2, Shift, "stats", strings::kKeyHelpStats.en, [] {                                                    // Shift+/
    std::string s = stats::describe();
    speech::speak(s.empty() ? strings::kNotInField.c_str() : s, true);
  });
  bind(VK_OEM_5, Shift, "social", strings::kKeyHelpSocial.en, [] { speech::speak_parts(social::summary_parts(), true); });      // Shift+backslash
  bind(VK_OEM_5, None, "review", strings::kKeyHelpReview.en, review);                                               // backslash
  bind(VK_OEM_6, None, "poi.next", strings::kKeyHelpPoiNext.en, [] { poi::next(1); }, true);                        // ]
  bind(VK_OEM_4, None, "poi.prev", strings::kKeyHelpPoiPrev.en, [] { poi::next(-1); }, true);                       // [
  bind(VK_OEM_6, Shift, "poi.cat.next", strings::kKeyHelpPoiCatNext.en, [] { poi::next_category(1); });             // Shift+]
  bind(VK_OEM_4, Shift, "poi.cat.prev", strings::kKeyHelpPoiCatPrev.en, [] { poi::next_category(-1); });            // Shift+[
  bind(VK_OEM_7, Shift, "party", strings::kKeyHelpParty.en, [] { speech::speak_parts(party::summary_parts(), true); });         // Shift+'
  bind(VK_OEM_7, None, "nav.walk", strings::kKeyHelpWalk.en, walk_selected);                                        // '
  bind(VK_OEM_1, None, "area", strings::kKeyHelpArea.en, area::describe);                                           // ;
  // After Grim Dark's review keys: its ; (the reviewed thing again) and Enter (walk there and use it). Shift, as the
  // mod's other second keys: Ctrl is the game's (messages, attack).
  bind(VK_OEM_1, Shift, "poi.again", strings::kKeyHelpPoiAgain.en, selected_again);                                // Shift+;
  bind(VK_OEM_COMMA, None, "poi.nearest", strings::kKeyHelpPoiNearest.en, [] { poi::cycle_nearest(1); }, true);      // ,
  bind(VK_OEM_COMMA, Shift, "poi.nearest.prev", strings::kKeyHelpPoiNearestPrev.en, [] { poi::cycle_nearest(-1); }, true);   // Shift+,
  // 1 to 7: one category each, in the bracket keys' order (Grim Dark's per-kind review keys; a player asked,
  // 2026-11-18). Letters are mostly the game's (Q E R T F Z X C B M N H), the number row is not. Shift goes back;
  // F1 leaves the Shift binding out while both are on their own keys: the plain one's help says so.
  // In a battle 1 to 4 are the party slots' status and 5 the navigator's (screens/battle_party.cpp; the user's
  // design, 2026-11-28): a battle has no points of interest.
  for (int c = 0; c < 7; ++c) {
    const std::string name = std::format("poi.cat.{}", c + 1);
    std::string help = std::format("{}{}{}", strings::kPoiCategory[c].en, keys::kHelpJoin, strings::kKeyHelpPoiCatKey.en);
    if (c < 4) help += std::format("{}{}", keys::kHelpJoin, strings::kKeyHelpBattleSlot.en);
    if (c == 4) help += std::format("{}{}", keys::kHelpJoin, strings::kKeyHelpBattleNavigator.en);
    bind('1' + c, None, name.c_str(), help.c_str(), [c] {
      if (c < 5 && screens::battle_party::active()) { if (c < 4) screens::battle_party::slot(c); else screens::battle_party::navigator(); return; }
      poi::cycle_category(c, 1);
    }, true);
    std::string back = std::format("{}{}{}", strings::kPoiCategory[c].en, keys::kHelpJoin, strings::kKeyHelpPoiCatBack.en);
    if (c < 4) back += std::format("{}{}", keys::kHelpJoin, strings::kKeyHelpBattleSlotBack.en);
    bind('1' + c, Shift, (name + ".prev").c_str(), back.c_str(), [c] {
      if (c < 5 && screens::battle_party::active()) { if (c < 4) screens::battle_party::slot(c, -1); else screens::battle_party::navigator(); return; }
      poi::cycle_category(c, -1);
    }, true, false);
  }
  // Period walks to the selection, beside Comma that chooses it; Shift+Period walks and uses it (Grim Dark's
  // walk-there-and-use, Shift+Enter until 2026-11-14; the user's call). The game binds neither Comma nor Period
  // (Config/DefaultInput.ini has them only in its unused pad emulation, PM_R2 / PM_R3).
  bind(VK_OEM_PERIOD, None, "nav.walk.period", strings::kKeyHelpWalk.en, walk_selected);                             // .
  bind(VK_OEM_PERIOD, Shift, "nav.use", strings::kKeyHelpWalkUse.en, walk_and_use);                                  // Shift+.
  // Shift goes back: those move with their plain key and are not listed on the Mod keys page.
  keys::shift_back("poi.nearest.prev", "poi.nearest");
  for (int c = 1; c <= 7; ++c) keys::shift_back(std::format("poi.cat.{}.prev", c).c_str(), std::format("poi.cat.{}", c).c_str());
  // A battle's party keys on the controller (controller-only, vk 0): the D-pad clockwise from up is the four slots, A
  // the navigator; while a battle runs they take those buttons from the field's (keys::bind_when).
  const uint16_t slot_pad[4] = {XINPUT_GAMEPAD_DPAD_UP, XINPUT_GAMEPAD_DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_LEFT};
  for (int c = 0; c < 4; ++c) {
    const std::string name = std::format("battle.slot.{}", c + 1);
    bind(0, None, name.c_str(), strings::kKeyHelpPadBattleSlot[c].en, [c] { screens::battle_party::slot(c); }, false, false);
    bind_pad(name.c_str(), slot_pad[c]);
    bind_when(name.c_str(), screens::battle_party::active);
  }
  bind(0, None, "battle.navigator", strings::kKeyHelpPadBattleNavigator.en, screens::battle_party::navigator, false, false);
  bind_pad("battle.navigator", XINPUT_GAMEPAD_A);
  bind_when("battle.navigator", screens::battle_party::active);
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
