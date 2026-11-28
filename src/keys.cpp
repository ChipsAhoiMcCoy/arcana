#include "keys.h"
#include "hooks.h"
#include "input.h"
#include "core/key_name.h"
#include "core/strings.h"
#include "log.h"
#include "mod.h"
#include "msg.h"
#include "speech.h"
#include "seh.h"
#include "ue/ue.h"
#include <windows.h>
#include <xinput.h>
#include <format>
#include <vector>
#include <atomic>
#include <algorithm>
#include <cstdio>

namespace p3a::keys {
// vk/mods: the key now (the player's, from the keys file); def_vk/def_mods: the mod's own.
// plain / back: a Shift "go back" binding and the plain one it follows (shift_back): the back is not listed on the Mod
// keys page and is always Shift with its plain key's key.
struct Binding { uint32_t vk; int mods; std::string name, help; Handler h; bool repeat; bool in_help; uint32_t def_vk; int def_mods; uint16_t pad = 0; int plain = -1, back = -1; std::function<bool()> when; };
static std::vector<Binding> g_bindings;
static bool g_swallowing[256];   // a bound key's down was swallowed: swallow its char and up too

// A binding's help is kept in English and said in the mod's language when read (the language can change after the
// keys are bound). Parts joined by kHelpJoin are each looked up, then joined by ": ".
static std::string said_help(const std::string& en) {
  std::string out;
  size_t at = 0;
  for (;;) {
    size_t j = en.find(kHelpJoin, at);
    out += core::lang::tr(std::string_view(en).substr(at, j == std::string::npos ? std::string::npos : j - at));
    if (j == std::string::npos) return out;
    out += ": ";
    at = j + 1;
  }
}

void bind(uint32_t vk, int mods, const char* name, const char* help, Handler h, bool repeat, bool in_help) {
  g_bindings.push_back(Binding{vk, mods, name, help, std::move(h), repeat, in_help, vk, mods});
}

static Handler g_on_layer;
static ModalKey g_modal_key;
static ModalPad g_modal_pad;
void set_modal(ModalKey key, ModalPad pad) { g_modal_key = std::move(key); g_modal_pad = std::move(pad); }
static ModalPad g_pad_capture;
void set_pad_capture(ModalPad pad) { g_pad_capture = std::move(pad); }
static CaptureKey g_capture;
void set_capture(CaptureKey key) { g_capture = std::move(key); }
static CaptureKey g_prompt;
void set_prompt(CaptureKey key) { g_prompt = std::move(key); }
static MenuKey g_menu;
void set_menu(MenuKey key) { g_menu = std::move(key); }
void bind_pad(const char* name, uint16_t button) { for (auto& b : g_bindings) if (b.name == name) b.pad = button; }
void bind_when(const char* name, std::function<bool()> when) { for (auto& b : g_bindings) if (b.name == name) b.when = std::move(when); }
void on_pad_layer(Handler h) { g_on_layer = std::move(h); }
void pad(uint16_t button, bool repeat, bool layer) {
  if (g_modal_pad) {   // a copy: the handler may close the menu, clearing g_modal_pad under itself
    if (button) { ModalPad h = g_modal_pad; if (!guarded([&] { h(button, repeat); })) log::write("keys: modal pad faulted"); }
    return;
  }
  if (g_pad_capture && !layer) {
    if (button) { ModalPad h = g_pad_capture; if (!guarded([&] { h(button, repeat); })) log::write("keys: pad capture faulted"); }
    return;
  }
  if (!button) { if (g_on_layer && !guarded([&] { g_on_layer(); })) log::write("keys: pad layer faulted"); return; }
  // A binding with a `when` goes first while it says true (a battle's party keys over the field's D-pad).
  for (int pass = 0; pass < 2; ++pass)
    for (auto& b : g_bindings) {
      if (b.pad != button || (pass == 0) != (bool)b.when) continue;
      bool on = true;
      if (b.when && !guarded([&] { on = b.when(); })) on = false;
      if (!on) continue;   // not now (a battle's own buttons outside a battle): the next binding on this button
      if (repeat && !b.repeat) return;
      if (!guarded([&] { b.h(); })) log::writef("keys: {} faulted", b.name);
      return;
    }
}

// Alt is the walk key (alt_held), not a modifier: the mod binds no Alt chord (reserved).
static int current_mods() {
  int m = 0;
  if ((GetKeyState(VK_SHIFT) & 0x8000) || input::dev_modifier_held(VK_SHIFT)) m |= Shift;
  if ((GetKeyState(VK_CONTROL) & 0x8000) || input::dev_modifier_held(VK_CONTROL)) m |= Ctrl;
  return m;
}

static bool g_movement[256];
static std::atomic<uint64_t> g_game_key_ms{0};
uint64_t game_key_ms() { return g_game_key_ms; }
static uint32_t g_movement_presses[256];
uint32_t movement_presses(uint32_t vk) { return g_movement_presses[vk & 0xFF]; }
static bool is_movement(uint32_t vk) { return vk == 'W' || vk == 'A' || vk == 'S' || vk == 'D' || vk == VK_UP || vk == VK_DOWN || vk == VK_LEFT || vk == VK_RIGHT; }
// A movement key is held from its key-down to its key-up. The window losing the keyboard takes the key-up with it
// (it goes to the other window; a stuck flag stopped every walk at once, 2026-10-28), so losing it lets go of every
// movement key (focus_lost, from the window procedure).
bool movement_key_down() {
  for (int i = 0; i < 256; ++i) if (g_movement[i]) return true;
  return false;
}
static bool g_alt = false;
bool alt_held() { return g_alt; }
static void focus_lost() { for (bool& held : g_movement) held = false; g_alt = false; }

// Synthetic keys the navigator posts carry this marker in the lParam's reserved bits, so they are neither bound
// commands nor a "player took over" signal.
constexpr LPARAM kSyntheticMark = 0x01000000;   // bit 24 = extended-key flag; the navigator's keys are never extended

static bool filter(UINT msg, WPARAM w, LPARAM l) {
  if (ue::exit_requested()) return false;   // the game is quitting: no mod key reads what it is taking down
  uint32_t vk = (uint32_t)w & 0xFF;
  // A key the mod pressed for the game (a menu stepping the game's cursor to its focus): the game's, untouched.
  if ((msg == WM_KEYDOWN || msg == WM_KEYUP) && (l & 0xFFFF) == input::kInjectedRepeat) return false;
  bool synthetic = (l & kSyntheticMark) != 0 && is_movement(vk) && vk >= 'A' && vk <= 'Z';
  // Alt alone, the walk key: Windows opens the window's (invisible) system menu when Alt is let go with no key
  // between, and the keys after it went to that menu. Neither its down nor its up reaches the window.
  if (vk == VK_MENU && (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN || msg == WM_KEYUP || msg == WM_SYSKEYUP)) {
    const bool down = msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN;
    if (down != g_alt) log::writef("keys: Alt {}", down ? "down" : "up");
    g_alt = down;
    return true;
  }
  if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN) {
    if (is_movement(vk) && !synthetic) {
      if (!g_movement[vk]) log::writef("keys: movement key {:#x} down (lParam {:#x})", vk, (uint64_t)l);
      if (!(l & (1 << 30))) ++g_movement_presses[vk];
      g_movement[vk] = true;
    }
    bool repeat = (l & (1 << 30)) != 0;
    // Any key but a modifier stops the speech on a speech engine, as a screen reader does by itself.
    if (!repeat && !synthetic && vk != VK_SHIFT && vk != VK_CONTROL && vk != VK_MENU && vk != VK_LWIN && vk != VK_RWIN)
      speech::player_pressed(true);
    // Shift is the game's Auto key in a conversation (and dash in the field): msg says Auto only after it.
    if (!repeat && vk == VK_SHIFT) p3a::msg::auto_key_pressed();
    // Confirm or cancel from the player: a message window's reading stops before anything the press says itself.
    if (msg == WM_KEYDOWN && !repeat && !g_modal_key && (vk == VK_RETURN || vk == VK_SPACE || vk == VK_ESCAPE || vk == VK_BACK))
      p3a::msg::player_pressed();
    if (g_modal_key && !synthetic && msg == WM_KEYDOWN) {
      g_swallowing[vk] = true;
      ModalKey h = g_modal_key;
      if (!guarded([&] { h(vk, repeat); })) log::write("keys: modal key faulted");
      return true;
    }
    int mods = current_mods();
    if (g_prompt && !synthetic && msg == WM_KEYDOWN && mods == None) {
      CaptureKey h = g_prompt;
      bool taken = false;
      if (!guarded([&] { taken = h(vk, repeat); })) log::write("keys: prompt faulted");
      if (taken) { g_swallowing[vk] = true; return true; }
    }
    if (g_menu && !synthetic && msg == WM_KEYDOWN) {
      MenuKey h = g_menu;
      bool taken = false;
      // A menu's key is the player on the keyboard too: the menu steps the game with keys, not pad buttons, and the
      // hints name keys (input::pad_in_use). Counted before the menu acts on it, so anything the menu's handler asks
      // about the device already sees this key.
      const uint64_t key_was = g_game_key_ms;
      if (!repeat) g_game_key_ms = GetTickCount64();
      if (!guarded([&] { taken = h(vk, mods, repeat); })) log::write("keys: menu key faulted");
      if (taken) { g_swallowing[vk] = true; return true; }
      g_game_key_ms = key_was;
    }
    if (g_capture && !synthetic && msg == WM_KEYDOWN && mods == None) {
      CaptureKey h = g_capture;
      bool taken = false;
      if (!guarded([&] { taken = h(vk, repeat); })) log::write("keys: capture faulted");
      if (taken) { g_swallowing[vk] = true; return true; }
    }
    for (auto& b : g_bindings) {
      if (b.vk != vk || b.mods != mods) continue;
      g_swallowing[vk] = true;
      if (repeat && !b.repeat) return true;
      if (!guarded([&] { b.h(); })) log::writef("keys: {} faulted", b.name);
      return true;
    }
    // A key the game gets: the player is on the keyboard (the mod's own keys say nothing about that).
    if (!synthetic && !repeat) g_game_key_ms = GetTickCount64();   // not the raw bit: real arrows are extended keys
    return false;
  }
  if (msg == WM_KEYUP || msg == WM_SYSKEYUP) {
    if (is_movement(vk) && !synthetic) g_movement[vk] = false;
    if (g_swallowing[vk]) { g_swallowing[vk] = false; return true; }
    return false;
  }
  if (msg == WM_CHAR) {
    if (g_modal_key) return true;
    // The char of a swallowed key: VkKeyScan maps it back (good enough for the punctuation keys the mod binds).
    SHORT k = VkKeyScanW((WCHAR)w);
    if (k != -1 && g_swallowing[k & 0xFF]) return true;
  }
  return false;
}

static std::string key_name(uint32_t vk, int mods) {
  std::string s;
  if (mods & Ctrl) s += strings::kModCtrl;
  if (mods & Alt) s += strings::kModAlt;
  if (mods & Shift) s += strings::kModShift;
  if (const char* punct = core::punct_key_name(vk)) return s + punct;
  UINT sc = MapVirtualKeyW(vk, MAPVK_VK_TO_VSC);
  wchar_t buf[64] = {};
  LONG lp = (LONG)(sc << 16);
  if (vk >= VK_PRIOR && vk <= VK_DELETE) lp |= 1 << 24;
  if (GetKeyNameTextW(lp, buf, 64) > 0) { char nb[128]; WideCharToMultiByte(CP_UTF8, 0, buf, -1, nb, 128, nullptr, nullptr); s += nb; }
  else s += std::format("{} {:#x}", strings::kKeyUnnamed, vk);
  return s;
}

static const char* pad_name(uint16_t m) {
  switch (m) {
    case XINPUT_GAMEPAD_DPAD_UP: return strings::kPadDpadUp;
    case XINPUT_GAMEPAD_DPAD_DOWN: return strings::kPadDpadDown;
    case XINPUT_GAMEPAD_DPAD_LEFT: return strings::kPadDpadLeft;
    case XINPUT_GAMEPAD_DPAD_RIGHT: return strings::kPadDpadRight;
    case XINPUT_GAMEPAD_START: return strings::kPadMenu;
    case XINPUT_GAMEPAD_BACK: return strings::kPadView;
    case XINPUT_GAMEPAD_LEFT_THUMB: return strings::kPadL3;
    case XINPUT_GAMEPAD_RIGHT_THUMB: return strings::kPadR3;
    case XINPUT_GAMEPAD_LEFT_SHOULDER: return strings::kPadLB;
    case XINPUT_GAMEPAD_RIGHT_SHOULDER: return strings::kPadRB;
    case XINPUT_GAMEPAD_A: return strings::kPadA;
    case XINPUT_GAMEPAD_B: return strings::kPadB;
    case XINPUT_GAMEPAD_X: return strings::kPadX;
    case XINPUT_GAMEPAD_Y: return strings::kPadY;
    default: return strings::kPadUnknown;
  }
}

std::string help() {
  std::string s = std::string(strings::kModKeys) + ". ";
  if (strings::pad_hints()) {
    s += std::string(strings::kPadLayer) + ": ";
    for (auto& b : g_bindings) if (b.pad) s += std::string(pad_name(b.pad)) + ": " + said_help(b.help) + ". ";
    return s + strings::kPadScanKeys;
  }
  // vk 0: a controller-only binding. A binding out of the help is a Shift variant its plain key's help speaks for
  // ("Shift goes back"): it moves with that key, so the help stays true.
  for (auto& b : g_bindings) {
    if (!b.vk) continue;
    if (!b.in_help) continue;
    s += key_name(b.vk, b.mods) + ": " + said_help(b.help) + ". ";
  }
  return s;
}

// ---- the player's own keys (the mod menu's Mod keys page): saved by binding name, only those moved from the
// default, in keys.ini beside settings.ini (keys-dev.ini for dev launches, as settings-dev.ini). ----
static std::wstring keys_file() {
  std::wstring p = log::path();
  return p.substr(0, p.find_last_of(L'\\') + 1) + (env_flag(L"P3A_NOFOCUS") ? L"keys-dev.ini" : L"keys.ini");
}

static void save_keys() {
  FILE* f = _wfopen(keys_file().c_str(), L"w");
  if (!f) { log::write("keys: cannot write the keys file"); return; }
  for (auto& b : g_bindings)
    if (b.def_vk && (b.vk != b.def_vk || b.mods != b.def_mods)) fprintf(f, "%s=%u,%d\n", b.name.c_str(), b.vk, b.mods);
  fclose(f);
}

static void load_keys() {
  FILE* f = _wfopen(keys_file().c_str(), L"r");
  if (!f) return;
  char line[256];
  int moved = 0;
  while (fgets(line, sizeof line, f)) {
    char name[128];
    unsigned vk = 0;
    int mods = 0;
    if (sscanf_s(line, "%127[^=]=%u,%d", name, (unsigned)sizeof name, &vk, &mods) != 3 || !vk || vk > 0xFE || (mods & ~(Shift | Ctrl | Alt))) continue;
    for (auto& b : g_bindings)
      if (b.def_vk && b.name == name) { b.vk = vk; b.mods = mods; ++moved; }
  }
  fclose(f);
  for (auto& b : g_bindings)   // a back follows its plain key, whatever the file says
    if (b.plain >= 0) { b.vk = g_bindings[(size_t)b.plain].vk; b.mods = g_bindings[(size_t)b.plain].mods | Shift; }
  // A hand edit that gave two bindings one key: the later one goes back to its default.
  for (size_t i = 0; i < g_bindings.size(); ++i)
    for (size_t j = 0; j < i; ++j)
      if (g_bindings[i].vk && g_bindings[i].vk == g_bindings[j].vk && g_bindings[i].mods == g_bindings[j].mods) {
        g_bindings[i].vk = g_bindings[i].def_vk;
        g_bindings[i].mods = g_bindings[i].def_mods;
      }
  if (moved) log::writef("keys: {} of the player's keys loaded", moved);
}

std::vector<int> keyboard_bindings() {
  std::vector<int> v;
  for (int i = 0; i < (int)g_bindings.size(); ++i) if (g_bindings[(size_t)i].def_vk && g_bindings[(size_t)i].plain < 0) v.push_back(i);
  return v;
}

void shift_back(const char* back_name, const char* plain_name) {
  int bi = -1, pi = -1;
  for (int i = 0; i < (int)g_bindings.size(); ++i) {
    if (g_bindings[(size_t)i].name == back_name) bi = i;
    if (g_bindings[(size_t)i].name == plain_name) pi = i;
  }
  if (bi < 0 || pi < 0) { log::writef("keys: shift_back {} / {}: no such binding", back_name, plain_name); return; }
  g_bindings[(size_t)bi].plain = pi;
  g_bindings[(size_t)pi].back = bi;
}
static bool valid(int i) { return i >= 0 && i < (int)g_bindings.size() && g_bindings[(size_t)i].def_vk; }
std::string binding_help(int i) { return valid(i) ? said_help(g_bindings[(size_t)i].help) : std::string(); }
std::string binding_key(int i) { return valid(i) ? key_name(g_bindings[(size_t)i].vk, g_bindings[(size_t)i].mods) : std::string(); }
bool binding_default(int i) {
  return !valid(i) || (g_bindings[(size_t)i].vk == g_bindings[(size_t)i].def_vk && g_bindings[(size_t)i].mods == g_bindings[(size_t)i].def_mods);
}
std::string key_label(uint32_t vk, int mods) { return key_name(vk, mods); }
std::string key_of(const char* name) {
  for (auto& b : g_bindings) if (b.name == name) return key_name(b.vk, b.mods);
  return {};
}
std::string fill(std::string_view text) {
  std::string out;
  size_t at = 0;
  while (at < text.size()) {
    size_t open = text.find('{', at), close = open == std::string_view::npos ? open : text.find('}', open);
    if (close == std::string_view::npos) break;
    out.append(text.substr(at, open - at));
    const std::string name(text.substr(open + 1, close - open - 1));
    std::string key = key_of(name.c_str());
    out += key.empty() ? std::string(text.substr(open, close - open + 1)) : key;
    at = close + 1;
  }
  out.append(text.substr(std::min(at, text.size())));
  return out;
}
bool is_key(const char* name, uint32_t vk, int mods) {
  for (auto& b : g_bindings) if (b.name == name) return b.vk == vk && b.mods == mods;
  return false;
}

// The game's keys a mod binding may not take: walking, Space / Enter (act, confirm), Escape / Backspace (back), Tab
// (the menu). The game's other defaults (Q, E, F, C...) are allowed: the player may have moved them in the game.
bool reserved(uint32_t vk, int mods) {
  if (mods & (Ctrl | Alt)) return true;   // Ctrl is the game's (attack, messages); Alt goes to Windows
  switch (vk) {
    case 'W': case 'A': case 'S': case 'D': case VK_UP: case VK_DOWN: case VK_LEFT: case VK_RIGHT:
    case VK_SPACE: case VK_RETURN: case VK_ESCAPE: case VK_BACK: case VK_TAB: return true;
    default: return false;
  }
}

static int holder(uint32_t vk, int mods, int not_a, int not_b) {
  for (int j = 0; j < (int)g_bindings.size(); ++j)
    if (j != not_a && j != not_b && g_bindings[(size_t)j].vk == vk && g_bindings[(size_t)j].mods == mods) return j;
  return -1;
}
static void put(int j, uint32_t vk, int mods) { g_bindings[(size_t)j].vk = vk; g_bindings[(size_t)j].mods = mods; }

// A binding moves with its Shift back, if it has one; whatever held the keys it takes gets the keys it leaves:
//   the plain key's holder O (with O's own back) takes the old plain key (and old+Shift);
//   a lone binding on the new Shift key (not O's back) takes the old Shift key; one on the old Shift key, when O's
//   back needs it, takes the new Shift key.
// Every case leaves each key with one binding. Refused: a Shift key for a binding with a back (its back would be
// Shift+Shift), and another binding's back key (it belongs to that pair).
Rebind rebind(int i, uint32_t vk, int mods, std::vector<int>& moved) {
  moved.clear();
  if (!valid(i) || g_bindings[(size_t)i].plain >= 0) return Rebind::Refused;
  const int bk = g_bindings[(size_t)i].back;
  if (bk >= 0 && (mods & Shift)) return Rebind::NeedsNoShift;
  const int at = holder(vk, mods, i, bk);
  if (at >= 0 && g_bindings[(size_t)at].plain >= 0) return Rebind::BackKey;
  const uint32_t old_vk = g_bindings[(size_t)i].vk;
  const int old_mods = g_bindings[(size_t)i].mods;
  if (old_vk == vk && old_mods == mods) return Rebind::Done;
  const int o_back = at >= 0 ? g_bindings[(size_t)at].back : -1;
  const int y_new = bk >= 0 ? holder(vk, mods | Shift, at, o_back) : -1;   // a lone binding on the new Shift key
  const int y_old = o_back >= 0 && bk < 0 ? holder(old_vk, old_mods | Shift, i, o_back) : -1;   // one on the old Shift key
  put(i, vk, mods);
  if (bk >= 0) put(bk, vk, mods | Shift);
  if (at >= 0) { put(at, old_vk, old_mods); moved.push_back(at); }
  if (o_back >= 0) put(o_back, old_vk, old_mods | Shift);
  if (y_new >= 0) { put(y_new, old_vk, old_mods | Shift); moved.push_back(y_new); }
  if (y_old >= 0) { put(y_old, vk, mods | Shift); moved.push_back(y_old); }
  save_keys();
  return Rebind::Done;
}

Rebind reset_binding(int i, std::vector<int>& moved) {
  moved.clear();
  if (!valid(i)) return Rebind::Refused;
  const Binding& b = g_bindings[(size_t)i];
  return rebind(i, b.def_vk, b.def_mods, moved);
}

int plain_of(uint32_t vk, int mods) {
  for (auto& b : g_bindings) if (b.vk == vk && b.mods == mods && b.plain >= 0) return b.plain;
  return -1;
}

void reset_all() {
  for (auto& b : g_bindings) { b.vk = b.def_vk; b.mods = b.def_mods; }
  save_keys();
}

void install() {
  load_keys();
  hooks::set_key_filter(&filter);
  hooks::set_focus_lost(&focus_lost);
}
}  // namespace p3a::keys
