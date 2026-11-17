// Voiced lines. The game's sound manager (USoundManagerGameInstanceSubSystem.PlayAdxControl, a UPlayAdxControl)
// keeps 0x100 players, mPlayerControlBlock at +0x40. A UPlayerControlBlock: +0x28 Player (UAtomComponent), +0x30 the
// bank (index into mAcbFileControlBlock, -1 unused), +0x34 its EPlayerType (0 BGM, 1 VOICE, 2 SE), +0x3C the cue last
// requested (measured 2026-10-29: an event's Voice_Event_Main_* cue sheet plays through type-1 blocks, the
// voice_configue and voice_singleword sheets too). A voice starts when its component's GetStatus turns Prep or
// Playing, or its cue changes while playing.
#include "voice.h"
#include "devserver.h"
#include "hooks.h"
#include "settings.h"
#include "log.h"
#include "seh.h"
#include "ue/scan.h"
#include "ue/ue.h"
#include "watch.h"
#include <windows.h>
#include <deque>
#include <format>
#include <memory>

namespace p3a::voice {
using namespace ue;

struct Slot { int status = 0; int cue = -1; int bank = -1; };
static Slot g_slot[0x100];
struct Start { uint64_t n; int cue; };
static std::deque<Start> g_starts;   // the voices that began, newest last
static uint64_t g_start_count = 0;
static bool g_playing = false;

static int status_of(UObject* comp) {
  UFunction* fn = find_function(class_of(comp), "GetStatus");   // cached by (class, name)
  if (!fn) return 0;
  Params p(fn);
  if (!call(comp, p)) return 0;
  return p.ret<int8_t>();   // EAtomComponentStatus: Stop, Prep, Playing, PlayEnd, Error
}

// The sound manager's player blocks as they are now (blk null: an empty slot). False when there is no manager.
struct Raw { UObject* blk; int bank, type, cue; };
static bool read_blocks(Raw raw[0x100]) {
  static const int id = watch::want("PlayAdxControl");
  UObject* ctl = watch::get(id);
  if (!ctl) return false;
  guarded([&] {
    UObject** blocks = (UObject**)((uint8_t*)ctl + 0x40);
    for (int k = 0; k < 0x100; ++k) {
      uint8_t* b = (uint8_t*)blocks[k];
      if (!b) continue;
      raw[k] = Raw{(UObject*)b, *(int*)(b + 0x30), *(int*)(b + 0x34), *(int*)(b + 0x3C)};
    }
  });
  return true;
}

void tick() {
  g_playing = false;
  Raw raw[0x100]{};
  if (!read_blocks(raw)) return;
  for (int k = 0; k < 0x100; ++k) {
    Slot& s = g_slot[k];
    const Raw& r = raw[k];
    if (!r.blk || r.type != 1 || r.bank < 0 || !is_live(r.blk)) { s = Slot{}; continue; }
    UObject* comp = get<UObject*>(r.blk, "Player");
    int st = comp && is_live(comp) ? status_of(comp) : 0;
    bool on = st == 1 || st == 2, was = s.status == 1 || s.status == 2;
    if (on && (!was || r.cue != s.cue)) {
      g_starts.push_back(Start{++g_start_count, r.cue});
      if (g_starts.size() > 16) g_starts.pop_front();
      log::writef("voice: start block {} bank {} cue {}", k, r.bank, r.cue);
    }
    if (on) g_playing = true;
    s = Slot{st, r.cue, r.bank};
  }
}

// The cue sheets the sound manager holds: mAcbFileControlBlock[0x40] at +0x840, each a UAcbFileControlBlock whose
// +0x40 is its USoundAtomCueSheet (CueSheetName +0x40, an FString; BP_GetCueInfoFromId answers whether it has a cue).
// An event's voices are its own sheet, Voice_Event_<event> (the Junpei arcade hangout's has cues 1-36, and its stat-up
// page declares 37, a voice that never plays: the line waited silent until the review key, 2026-11-17).
static int sheet_has(UObject* sheet, int cue) {
  UFunction* fn = find_function(class_of(sheet), "BP_GetCueInfoFromId");
  if (!fn) return -1;
  Params p(fn);
  p.set<int32_t>("ID", cue);
  if (!call(sheet, p)) return -1;
  return p.ret<bool>() ? 1 : 0;
}
template <class F> static void each_sheet(F f) {
  static const int id = watch::want("PlayAdxControl");
  UObject* ctl = watch::get(id);
  if (!ctl) return;
  for (int k = 0; k < 0x40; ++k) {
    UObject* sheet = nullptr;
    std::string name;
    guarded([&] {
      auto* blk = ((UObject**)((uint8_t*)ctl + 0x840))[k];
      if (!blk || !is_live(blk)) return;
      auto* s = *(UObject**)((uint8_t*)blk + 0x40);
      if (!s || !is_live(s)) return;
      sheet = s;
      name = to_utf8(*(FString*)((uint8_t*)s + 0x40));
    });
    if (sheet) f(k, sheet, name);
  }
}
int event_has_cue(int cue) {
  int seen = 0, has = 0;
  each_sheet([&](int, UObject* s, const std::string& name) {
    if (name.rfind("Voice_Event", 0) != 0) return;
    int h = sheet_has(s, cue);
    if (h < 0) return;
    ++seen;
    if (h) ++has;
  });
  return has ? 1 : seen ? 0 : -1;
}

uint64_t started(int cue) {
  for (size_t i = g_starts.size(); i-- > 0;) if (g_starts[i].cue == cue) return g_starts[i].n;
  return 0;
}
bool playing() { return g_playing; }

// Cues of the system sheet (CriData/CueSheet/system, read 2026-10-29): 5 "page", 9 "message", 0 "Sys_Cursor".
// 21 opens a message window (the network question, 2026-10-29). The menu cues were heard on the SE player as the camp menu and title menu played them (2026-10-29).
void play_system_sound(int cue) {
  UClass* cls = find_class("SoundApp");   // both lookups are cached
  UFunction* fn = cls ? find_function(cls, "PlayComSE") : nullptr;
  UObject* cdo = cls ? cdo_of(cls) : nullptr;
  if (!fn || !cdo) return;
  Params p(fn);
  p.set<int32_t>("CueId", cue);
  call(cdo, p);
}

void play_end_sound() {
  static const int kCue[] = {CuePage, CueMessage, CueCursor};   // EndPage, EndMessage, EndCursor
  int v = settings::get(settings::VoiceEndSound) - settings::EndPage;
  if (v >= 0 && v < (int)std::size(kCue)) play_system_sound(kCue[v]);
}

// Dev: every cue asked of exe+0x1286af0 (the lists' moves, BtlSEPlay and cursor_sound), a log line each: how a test
// counts ticks in the muted dev game.
static void (*g_cue_orig)(int) = nullptr;
static void cue_detour(int cue) {
  log::writef("sound: cue {}", cue);
  g_cue_orig(cue);
}

void install() {
  dev::route("/voice/cues", [](const dev::Request& r, int&) {
    bool on = dev::arg_int(r, "on", 1) != 0;
    return dev::on_game([on]() -> std::string {
      if (!ue::known_build()) return "another build of the game\n";
      if (on == (g_cue_orig != nullptr)) return "no change\n";
      if (on) {
        g_cue_orig = (void (*)(int))(scan::exe_base() + 0x1286af0);
        if (!hooks::attach((void**)&g_cue_orig, (void*)&cue_detour, "sound cue")) { g_cue_orig = nullptr; return "attach failed\n"; }
      } else {
        hooks::detach((void**)&g_cue_orig, (void*)&cue_detour);
        g_cue_orig = nullptr;
      }
      return on ? "logging cues\n" : "off\n";
    });
  }, "?on=1|0 log every game sound cue (dev)");
  dev::route("/voice", [](const dev::Request& r, int&) {
    auto out = std::make_shared<std::string>("timeout\n");
    bool all = dev::has(r, "all");
    hooks::run_on_game_thread([out, all] {
      std::string s = std::format("playing={}\n", g_playing);
      if (all) {   // every player block in use: type (0 BGM, 1 voice, 2 SE), bank, the cue last requested
        Raw raw[0x100]{};
        read_blocks(raw);
        for (int k = 0; k < 0x100; ++k)
          if (raw[k].blk && raw[k].bank >= 0) s += std::format("all {} type {} bank {} cue {}\n", k, raw[k].type, raw[k].bank, raw[k].cue);
        each_sheet([&](int k, UObject*, const std::string& name) { s += std::format("sheet {} {}\n", k, name); });
      }
      for (int k = 0; k < 0x100; ++k)
        if (g_slot[k].bank >= 0) s += std::format("block {} bank {} cue {} status {}\n", k, g_slot[k].bank, g_slot[k].cue, g_slot[k].status);
      for (const Start& t : g_starts) s += std::format("start {} cue {}\n", t.n, t.cue);
      *out = s;
    });
    return *out;
  }, "voice players and recent voice starts");
}
}  // namespace p3a::voice
