// When the game takes OK: who asks the pad layer for the decide button, and when (confirm.h).
// The six pad queries (rva, P3R.exe of 2026-11; the decompile's FUN_1410a8890..FUN_1410a8a00) each start by fetching
// the pad object and hand on to its own reader. Each is checked against its first bytes before it is hooked, so a
// game update that moves them leaves this off (and the screens give no cue).
#include "confirm.h"
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "ue/scan.h"
#include <windows.h>
#include <intrin.h>
#include <cstring>
#include <format>

namespace p3a::confirm {
namespace {
constexpr uintptr_t kDecideRva = 0x5393e60;   // the decide button's pad id (2 or 4)

// One slot per code address that asked for the decide button: written on the game thread, read there too.
struct Slot { uintptr_t rva; uint64_t frame; uint64_t count; };
constexpr int kSlots = 128;
Slot g_slots[kSlots];
int g_used = 0;
uint64_t g_asks = 0;
uintptr_t g_base = 0;

inline void note(uint32_t button, void* ret) {
  if (button != *(uint32_t*)(g_base + kDecideRva)) return;
  ++g_asks;
  uintptr_t rva = (uintptr_t)ret - g_base;
  uint64_t f = hooks::frame();
  for (int i = 0; i < g_used; ++i)
    if (g_slots[i].rva == rva) { g_slots[i].frame = f; ++g_slots[i].count; return; }
  if (g_used < kSlots) g_slots[g_used++] = {rva, f, 1};
}

using Q2 = bool (*)(uint32_t, uint8_t);
using Q1 = bool (*)(uint32_t);
using Q3 = bool (*)(uint32_t, uint8_t, int32_t);
Q2 g_on = nullptr, g_trg = nullptr, g_rep = nullptr;
Q1 g_on1 = nullptr, g_trg1 = nullptr;
Q3 g_list = nullptr;
bool on_hook(uint32_t b, uint8_t k) { note(b, _ReturnAddress()); return g_on(b, k); }
bool trg_hook(uint32_t b, uint8_t k) { note(b, _ReturnAddress()); return g_trg(b, k); }
bool rep_hook(uint32_t b, uint8_t k) { note(b, _ReturnAddress()); return g_rep(b, k); }
bool on1_hook(uint32_t b) { note(b, _ReturnAddress()); return g_on1(b); }
bool trg1_hook(uint32_t b) { note(b, _ReturnAddress()); return g_trg1(b); }
bool list_hook(uint32_t b, uint8_t k, int32_t id) { note(b, _ReturnAddress()); return g_list(b, k, id); }

bool matches(uintptr_t rva, const char* hex) {
  auto* p = (const uint8_t*)(g_base + rva);
  for (const char* h = hex; *h;) {
    if (*h == ' ') { ++h; continue; }
    unsigned v = 0;
    if (sscanf_s(h, "%2x", &v) != 1 || *p++ != (uint8_t)v) return false;
    h += 2;
  }
  return true;
}
bool g_installed = false;
}  // namespace

uint64_t frame() { return hooks::frame(); }

std::vector<uintptr_t> callers(uint64_t from, uint64_t to) {
  std::vector<uintptr_t> out;
  for (int i = 0; i < g_used; ++i)
    if (g_slots[i].frame >= from && g_slots[i].frame <= to) out.push_back(g_slots[i].rva);
  return out;
}

uintptr_t new_caller(const std::vector<uintptr_t>& except, uint64_t recent) {
  uint64_t f = hooks::frame();
  for (int i = 0; i < g_used; ++i) {
    if (g_slots[i].frame + recent < f) continue;
    bool old = false;
    for (uintptr_t e : except) if (e == g_slots[i].rva) { old = true; break; }
    if (!old) return g_slots[i].rva;
  }
  return 0;
}

std::string status() {
  if (!g_installed) return "confirm: off\n";
  std::string s = std::format("confirm: decide={} asks={} callers={} frame={}\n", *(uint32_t*)(g_base + kDecideRva), g_asks, g_used, hooks::frame());
  for (int i = 0; i < g_used; ++i)
    s += std::format("  exe+{:#x} last frame {} ({} asks)\n", g_slots[i].rva, g_slots[i].frame, g_slots[i].count);
  return s;
}

bool install() {
  g_base = scan::exe_base();
  if (!g_base) return false;
  struct H { uintptr_t rva; const char* bytes; void** orig; void* hook; const char* name; };
  const char* two = "48 89 5c 24 08 57 48 83 ec 20 0f b6 da 8b f9 e8";
  const char* one = "40 53 48 83 ec 20 8b d9 e8";
  H hs[] = {
      {0x10a8890, two, (void**)&g_on, (void*)&on_hook, "pad query a8890"},
      {0x10a8920, two, (void**)&g_trg, (void*)&trg_hook, "pad query a8920"},
      {0x10a89b0, two, (void**)&g_rep, (void*)&rep_hook, "pad query a89b0"},
      {0x10a88e0, one, (void**)&g_on1, (void*)&on1_hook, "pad query a88e0"},
      {0x10a8970, one, (void**)&g_trg1, (void*)&trg1_hook, "pad query a8970"},
      {0x10a8a00, "48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 41 8b d8", (void**)&g_list, (void*)&list_hook, "pad query a8a00"},
  };
  int n = 0;
  for (auto& h : hs) {
    if (!matches(h.rva, h.bytes)) { log::writef("confirm: exe+{:#x} not as expected, left alone", h.rva); continue; }
    *h.orig = (void*)(g_base + h.rva);
    if (hooks::attach(h.orig, h.hook, h.name)) ++n;
    else *h.orig = nullptr;
  }
  g_installed = n > 0;
  log::writef("confirm: {} of 6 pad queries hooked", n);
  dev::route("/confirm", [](const dev::Request&, int&) { return dev::on_game([] { return status(); }); },
             "who asks for the decide button, and when");
  return g_installed;
}
}  // namespace p3a::confirm
