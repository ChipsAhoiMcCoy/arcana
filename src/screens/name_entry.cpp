// The contract (name entry), a bespoke menu over the game's own state (measured 2026-11-02, keyboard and pad):
// ANameEntry (the actor the event makes; its draw AUINameEntryDraw at +0x328)
//   +0x2A0 int    the field cursor: 0 first name, 1 last name (A / D / Left / Right toggle it, wrapping)
//   +0x2A8 FText  the first name, +0x2C0 FText the last name (set when Enter commits a field)
//   +0x294 int    the state (4 the list, 5 typing, 6 and on signing)
//   +0x334 byte   open the first name by itself once the opening animation ends (draw +0x2D1, ~4.5 s after it starts)
//   +0x340 byte   open the field by itself in 1/3 s: a first name committed while the last is blank (the cursor moves on)
//   +0x341 byte   typing: the text field (WBP_NameEntryInput_C.CurrentEditableText) has the keys
// AUINameEntryDraw +0x2D1 (bIsFinishInAnim) the opening animation is over; +0x2D4 (bIsKeyOutAnim) is set by H (exe+0x14b9210
// state 6, which also opens UI type 6 for "Did I spell that correctly?"); the draw and the actor outlive the contract, so
// that is where it ends.
// AUINameEntryDraw +0x34A / +0x34B: set by a move of the field cursor, +0x34A (and +0x34B cleared) when it goes to the
// last name, +0x34B (and +0x34A cleared) when it goes to the first.
// The screen is a vertical list from the start (the user's call, 2026-11-04): the two names, mirrored to +0x2A0, and
// Done, which presses the game's H (pad Menu; the game ignores it while a name is blank). The field cursor is written
// as the list state's own Left / Right does it (the state's tick, exe+0x14b9770 case 4): the cursor sound, the draw's
// two flags, then the cursor. The game would open the fields by itself in a row: the mod clears its two flags
// (+0x334, +0x340), so a field opens only on Enter (pad A, which opens the same text field) and the first name's
// commit leaves the cursor where it was. While typing the game has the keys and core::TextField reads the box like a
// screen reader's own edit field.
// On a controller (input::pad_in_use when the field opens, or a pad press while it is open) the mod's own keyboard
// (core::VirtualKeyboard) takes the pad while the field is open: the D-pad walks a QWERTY grid, A types the key into the
// box (EditableText.SetText with KismetTextLibrary.Conv_StringToText's FText), B erases the last character, Y capitals,
// X reads the name, Start commits with an injected Enter (the box's own commit, as the keyboard's: every
// OnTextCommitted runs Decide). B with the box empty commits it empty: the keyboard closes, the name stays blank.
// Steam's keyboard: opening a field (exe+0x149e4b0) first asks Steam for its gamepad keyboard (exe+0x1272c90:
// ISteamUtils vtable +0xA0, ShowGamepadTextInput(normal, single line, description, max, existing text); state byte
// 1 pending, 2 submitted, 3 cancelled, 4 no Steam), which Steam shows only in Big Picture or on a Steam Deck and a
// screen reader does not read. Only when that fails does it open WBP_NameEntryInput (+0x341). The mod answers the
// request as the no-Steam path does (state 4, false), so the game's own box always opens and the keyboard here takes it.
#include "screens/menu.h"
#include "screens/util.h"
#include "core/strings.h"
#include "core/text_field.h"
#include "core/virtual_keyboard.h"
#include "input.h"
#include "hooks.h"
#include "ue/scan.h"
#include "keys.h"
#include "log.h"
#include "seh.h"
#include "speech.h"
#include <windows.h>
#include <xinput.h>
#include <cstring>
#include <format>

namespace p3a::screens {
using namespace ue;

class NameEntryScreen : public MenuScreen {
  Finder entry_{"NameEntry"};
  uint8_t* ne() { return (uint8_t*)entry_.get(); }
  uint8_t* draw() {
    uint8_t* n = ne();
    UObject* d = n ? *(UObject**)(n + 0x328) : nullptr;
    return d && is_live(d) ? (uint8_t*)d : nullptr;
  }
  int cursor() { uint8_t* n = ne(); int c = n ? *(int32_t*)(n + 0x2A0) : -1; return c == 0 || c == 1 ? c : -1; }
  bool typing() { uint8_t* n = ne(); return n && n[0x341]; }
  bool both_named() { return !name(0).empty() && !name(1).empty(); }   // what the game's H checks
  // The list takes input: the opening animation is over and no field is open.
  bool list_up() { uint8_t* n = ne(); uint8_t* d = draw(); return n && d && d[0x2D1] && *(int32_t*)(n + 0x294) == 4 && !n[0x341]; }
  std::string name(int f) {
    uint8_t* n = ne();
    std::string s;
    if (n) guarded([&] { s = text(*(FText*)(n + (f == 0 ? 0x2A8 : 0x2C0))); });
    return s;
  }
  UObject* edit_box() {
    static const int input_id = watch::want("WBP_NameEntryInput_C");
    UObject* in = watch::get(input_id);
    return in ? get<UObject*>(in, "CurrentEditableText") : nullptr;
  }
  // Whether the edit box has the keys. Enter takes them away as it commits; the box's text changes in that frame (it
  // empties, or goes back to the old name) while +0x341 is still set: that is not an edit to echo.
  bool box_focused() { UObject* et = edit_box(); return et && call_ret<bool>(et, "HasKeyboardFocus"); }
  // The text field's live text (the name being typed).
  std::string field_text() {
    UObject* et = edit_box();
    UFunction* f = et ? find_function(class_of(et), "GetText") : nullptr;
    if (!f) return {};
    Params p(f);
    call(et, p);
    FText* t = p.at<FText>("ReturnValue");
    if (!t) return {};
    std::string s = text(*t);
    release_text(*t);
    return s;
  }
  static const char* field_name(int f) { return f == 1 ? strings::kLastName : strings::kFirstName; }
  std::string name_or_blank(int f) { std::string n = name(f); return n.empty() ? std::string(strings::kBlank) : n; }
  // The game opens its fields by itself on these two flags; here a field opens on the player's Enter only.
  void stop_opening_fields() { if (uint8_t* n = ne()) { n[0x334] = 0; n[0x340] = 0; } }
  // The field cursor put on field f the way the game's own move writes it (without its sound). Also for the first
  // name's commit, which moved the game's cursor on to a blank last name: back to the field it was on.
  void back_to_field(int f) {
    uint8_t* n = ne();
    uint8_t* d = draw();
    if (!n || !d) return;
    d[0x34A] = f == 1;
    d[0x34B] = f == 0;
    n[0x2A0] = (uint8_t)f;
  }
  std::string summary() { return std::format("{} {}, {} {}", strings::kFirstName, name_or_blank(0), strings::kLastName, name_or_blank(1)); }

  Mirror& fields_ = mirror("fields", [this] { return cursor(); });
  // Not a game list (no cursor): a mirror only so Left / Right on Done stay with the menu, not move the game's fields.
  Mirror& done_ = mirror("done", [] { return -1; });
  bool typed_ = false;      // typing when last ticked
  int typed_field_ = -1;
  core::TextField field_;   // the open field's text and caret
  core::VirtualKeyboard kb_;
  bool kb_open_ = false;    // the on-screen keyboard has the pad
  bool kb_sent_ = false;    // its Enter went: nothing more is typed until the field closes

  // The box's text set to s, as the player's typing would leave it (the echo in on_tick reads the change).
  bool set_box_text(const std::string& s) {
    UObject* et = edit_box();
    UFunction* f = et ? find_function(class_of(et), "SetText") : nullptr;
    if (!f) return false;
    std::u16string w = to_u16(s);
    Params c = call_static("KismetTextLibrary", "Conv_StringToText", [&](Params& p) { p.set<FString>("inString", make_fstring(w)); });
    FText* t = c.fn ? c.at<FText>("ReturnValue") : nullptr;
    if (!t) return false;
    Params p(f);
    p.set<FText>("InText", *t);
    call(et, p);
    release_text(*t);
    return true;
  }
  void open_keyboard() {
    kb_open_ = true;
    kb_sent_ = false;
    kb_.reset();
    input::set_pad_capture(true);
    keys::set_pad_capture([this](uint16_t b, bool repeat) { keyboard_pad(b, repeat); });
    log::write("name_entry: on-screen keyboard open");
  }
  void close_keyboard() {
    if (!kb_open_) return;
    kb_open_ = false;
    keys::set_pad_capture(nullptr);
    input::set_pad_capture(false);
    log::write("name_entry: on-screen keyboard closed");
  }
  void commit() {
    if (kb_sent_) return;
    kb_sent_ = true;
    input::inject_key(VK_RETURN);
  }
  void erase_or_close() {
    std::string t = field_text();
    if (t.empty()) { commit(); return; }
    size_t cut = t.size() - 1;
    while (cut > 0 && ((unsigned char)t[cut] & 0xC0) == 0x80) --cut;   // a whole UTF-8 character
    field_.pressed(core::TextField::Key::Backspace);
    set_box_text(t.substr(0, cut));
  }
  void keyboard_pad(uint16_t b, bool repeat) {
    if (!typing() || kb_sent_) return;
    using M = core::VirtualKeyboard::Move;
    using A = core::VirtualKeyboard::Action;
    std::string line;
    switch (b) {
      case XINPUT_GAMEPAD_DPAD_UP: line = kb_.move(M::Up, repeat); break;
      case XINPUT_GAMEPAD_DPAD_DOWN: line = kb_.move(M::Down, repeat); break;
      case XINPUT_GAMEPAD_DPAD_LEFT: line = kb_.move(M::Left, repeat); break;
      case XINPUT_GAMEPAD_DPAD_RIGHT: line = kb_.move(M::Right, repeat); break;
      case XINPUT_GAMEPAD_A: {
        auto p = kb_.activate(field_text());
        if (p.action == A::Type) set_box_text(field_text() + p.text);
        else if (p.action == A::Erase) erase_or_close();
        else if (p.action == A::Capitals && !repeat) line = kb_.toggle_capitals();
        else if (p.action == A::Done && !repeat) commit();
        break;
      }
      case XINPUT_GAMEPAD_B: erase_or_close(); break;
      case XINPUT_GAMEPAD_Y: if (!repeat) line = kb_.toggle_capitals(); break;
      case XINPUT_GAMEPAD_X: if (!repeat) { std::string t = field_text(); line = std::format("{}, {}", t.empty() ? strings::kBlank : t, kb_.where()); } break;
      case XINPUT_GAMEPAD_START: if (!repeat) commit(); break;
      case XINPUT_GAMEPAD_BACK: if (!repeat) speech::speak(strings::kTypeThenEnter(), true); break;
      default: break;
    }
    if (!line.empty()) speech::speak(line, true);
  }

 public:
  NameEntryScreen() {
    fields_.keep_edges = true;
    fields_.ready = [this] { return list_up(); };
    fields_.set = [this](int f) {
      if (!list_up() || (f != 0 && f != 1)) return false;
      if (cursor() == f) return true;
      cursor_sound();
      back_to_field(f);
      return true;
    };
    done_.keep_edges = true;
  }
  const char* id() const override { return "name_entry"; }
  int priority() const override { return 20; }
  bool active() override {
    uint8_t* d = draw();
    if (!d || d[0x2D4]) return false;
    return call_ret<bool>((UObject*)d, "IsCursorName1Use") || call_ret<bool>((UObject*)d, "IsCursorName2Use");
  }
  bool escape_is_back() override { return false; }   // Escape is the game's here
  // The game has the keys only while a field is being typed.
  bool holds_keys() override { return !typing(); }
  std::string title() override { return strings::kContract; }
  void on_leave() override { close_keyboard(); }
  void on_enter() override {
    typed_ = false; typed_field_ = -1;
    stop_opening_fields();
    screens::set_keys([this] { return typing() ? std::string(strings::kTypeThenEnter()) : std::string(strings::kNameEntryOptions()); });
  }
  void on_tick() override {
    stop_opening_fields();
    bool ty = typing();                 // the game's flag: the field is open
    bool keys = ty && box_focused();    // ...and its box still has the keys (not committing)
    int f = cursor();
    if (!ty) close_keyboard();
    if (ty && (!typed_ || f != typed_field_)) {
      // A field opened for typing: its name and what is in it; on a controller, the keyboard and its key.
      std::string t = field_text();
      field_.open(t);
      bool pad = input::pad_in_use();
      if (pad) open_keyboard();
      std::string line = std::format("{}. {}", field_name(f), t.empty() ? strings::kTypeThenEnter() : t);
      if (pad) line = std::format("{}. {}. {}", line, strings::kKeyboardOpen, kb_.key_name());
      say(line, true);
    } else if (keys && !kb_open_ && input::pad_in_use()) {
      // A controller picked up while the field was open from the keyboard.
      open_keyboard();
      say(std::format("{}. {}", strings::kKeyboardOpen, kb_.key_name()), true);
    } else if (keys) {
      // The echo of typing is spoken directly, here and in on_game_key: the game has the keys, so a menu's guard
      // against saying a line twice would take the second of two equal echoes (a doubled letter, the same character
      // stepped over again) for a repeat.
      std::string t = field_text();
      if (t != field_.text()) speech::speak(field_.edited(t), true);
    } else if (!ty && typed_) {
      // Committed (the game cleared its flag once it stored the name): the list has the keys again, on the same name.
      log::writef("name_entry: first '{}' last '{}'", name(0), name(1));
      if (typed_field_ >= 0 && f != typed_field_) back_to_field(typed_field_);
      if (typed_field_ >= 0) focus_quietly(slot("fields", typed_field_));
      say_focus();
    }
    typed_ = ty; typed_field_ = ty ? f : typed_field_;
  }
  // A key on its way to the open text box: the arrows read it, as in any edit field.
  void on_game_key(uint32_t vk, int mods) override {
    if (mods != keys::None || !typing() || !box_focused()) return;
    using Key = core::TextField::Key;
    std::string say;
    switch (vk) {
      case VK_LEFT: say = field_.pressed(Key::Left); break;
      case VK_RIGHT: say = field_.pressed(Key::Right); break;
      case VK_HOME: say = field_.pressed(Key::Home); break;
      case VK_END: say = field_.pressed(Key::End); break;
      case VK_UP: case VK_DOWN: say = field_.pressed(Key::Line); break;
      case VK_BACK: field_.pressed(Key::Backspace); break;
    }
    if (!say.empty()) speech::speak(say, true);
  }
  void build(ui::GraphBuilder& b) override {
    if (cursor() < 0) return;
    b.begin_stop("fields");
    for (int i = 0; i < 2; ++i)
      b.add_item(slot("fields", i), game_item(fields_, i, [this, i] { return std::format("{}, {}", field_name(i), name_or_blank(i)); }));
    b.add_item(slot("done", 0), item([] { return std::string(strings::kNameDone); }, [this] {
      if (both_named()) press_game('H', XINPUT_GAMEPAD_START);
      else say(strings::kNamesMissing, true);
    }));
    b.set_start(slot("fields", cursor()));
  }
  std::string describe() override {
    if (typing()) { std::string t = field_text(); return std::format("{}: {}", field_name(cursor()), t.empty() ? strings::kBlank : t); }
    return summary();
  }
};

// Steam's gamepad keyboard refused: the request answered as when Steam is not running (its own failure path).
using ShowSteamKeyboard_t = bool (*)(uint8_t* state, void* description, uint32_t max_chars, void* existing);
static ShowSteamKeyboard_t g_show_steam_keyboard = nullptr;
static bool show_steam_keyboard_hook(uint8_t* state, void*, uint32_t, void*) {
  if (state) *state = 4;
  log::write("name_entry: Steam's keyboard refused, the game's box opens");
  return false;
}
void install_name_entry() {
  uintptr_t m = scan::find_unique("48 8B F1 C6 01 01 48 8D 0D ?? ?? ?? ?? 49 8B D9 41 8B E8 48 8B FA FF 15 ?? ?? ?? ?? 4C 8B 30 4D 85 F6");
  uintptr_t f = m ? m - 0x20 : 0;
  if (f && memcmp((void*)f, "\x40\x53\x55\x56\x57\x41\x56", 7) != 0) f = 0;   // push rbx, rbp, rsi, rdi, r14
  log::writef("name_entry: ShowGamepadTextInput call={:#x}", f ? f - scan::exe_base() : 0);
  if (!f) return;
  g_show_steam_keyboard = (ShowSteamKeyboard_t)f;
  hooks::attach((void**)&g_show_steam_keyboard, (void*)&show_steam_keyboard_hook, "ShowGamepadTextInput (contract)");
}

std::unique_ptr<Screen> make_name_entry() { return std::make_unique<NameEntryScreen>(); }
}  // namespace p3a::screens
