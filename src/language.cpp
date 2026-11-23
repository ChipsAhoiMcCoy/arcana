#include "language.h"

#include <windows.h>

#include <format>

#include "core/lang.h"
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "msg.h"
#include "paths.h"
#include "ue/ue.h"

namespace p3a::language {
std::string route(const dev::Request& r);
static std::string set_game_culture(const std::string& g);
std::string game_culture() {
  ue::Params p = ue::call_static("KismetInternationalizationLibrary", "GetCurrentLanguage");
  if (!p.fn) return {};
  ue::FString s = p.ret<ue::FString>();
  return msg::take_fstring(s);
}

void apply(int setting) {
  static bool rooted = false;
  if (!rooted) { rooted = true; core::lang::set_root(paths::dir_w() + L"assets\\lang\\"); }
  int lang = core::lang::En;
  std::string culture = game_culture();
  core::lang::set_game(core::lang::from_culture(culture));   // the game's own text: its place names (lang::names_place)
  if (setting > 0 && setting <= core::lang::Count) {
    lang = setting - 1;
  } else {
    int c = core::lang::from_culture(culture);
    if (c >= 0) lang = c;
  }
  if (lang == core::lang::current() && core::lang::current() != core::lang::En) return;
  core::lang::set(lang);
  log::writef("lang: {} ({})", core::lang::code(lang), setting ? "chosen" : std::format("the game's: {}", culture.empty() ? "unknown" : culture));
}

// ---- dev: the game booted in another language (P3A_CULTURE) ----
// The game takes its language from Steam as it starts (its Steam language plugin: ISteamApps::GetCurrentGameLanguage
// -> " -culture=xx" on the command line), and loads its text tables in it: a culture set later leaves them in the old
// one, and a -culture argument of our own is overridden. So the first time the game asks for the ISteamApps interface
// (SteamInternal_ContextInit with the apps context, RVA 0x538d680 on this build; steam_api64.dll's export), its GetCurrentGameLanguage (vtable +0x20) is pointed at one that answers the wanted language;
// the slot goes back once the engine is up. Dev launches only: the player's game is never touched.
namespace {
using ContextInit = void* (*)(void*);
ContextInit g_ctx_orig = nullptr;
bool g_ctx_hooked = false;
void** g_lang_slot = nullptr;      // the vtable entry patched
void* g_lang_orig = nullptr;
char g_steam_lang[32] = {};
constexpr uintptr_t kAppsContextRva = 0x538d680;

const char* steam_name(int lang) {
  static const char* const k[core::lang::Count] = {"english", "japanese", "french", "italian", "german", "spanish",
                                                   "brazilian", "polish", "turkish", "russian", "koreana", "schinese", "tchinese"};
  return lang >= 0 && lang < core::lang::Count ? k[lang] : "english";
}
const char* __fastcall fake_language(void*) { return g_steam_lang; }

bool write_ptr(void** at, void* v) {
  DWORD old;
  if (!VirtualProtect(at, sizeof(void*), PAGE_READWRITE, &old)) return false;
  InterlockedExchangePointer(at, v);
  VirtualProtect(at, sizeof(void*), old, &old);
  return true;
}

void* ctx_hook(void* data) {
  void* r = g_ctx_orig(data);
  auto base = (uintptr_t)GetModuleHandleW(nullptr);
  if (!g_lang_slot && (uintptr_t)data == base + kAppsContextRva && r && *(void**)r) {
    void** vtbl = *(void***)*(void**)r;
    g_lang_slot = &vtbl[4];
    g_lang_orig = vtbl[4];
    write_ptr(g_lang_slot, (void*)&fake_language);
  }
  return r;
}

}  // namespace

void boot_culture() {
  wchar_t c[32] = {};
  if (!GetEnvironmentVariableW(L"P3A_CULTURE", c, 32) || !*c) return;
  std::string g;
  for (wchar_t* q = c; *q; ++q) g += (char)*q;
  int lang = core::lang::from_culture(g);
  if (lang < 0) { log::writef("lang: P3A_CULTURE={} is none of the game's languages", g); return; }
  auto base = (uint8_t*)GetModuleHandleW(nullptr);
  auto nt = (IMAGE_NT_HEADERS64*)(base + ((IMAGE_DOS_HEADER*)base)->e_lfanew);
  if (nt->FileHeader.TimeDateStamp != 0x69ce3439) { log::write("lang: P3A_CULTURE needs the known build of the game"); return; }
  strcpy_s(g_steam_lang, steam_name(lang));
  // P3R.exe's Steam imports are bound at run time (no import table entry to point elsewhere): steam_api64.dll's
  // export is detoured instead, until the engine is up.
  // Not loaded yet this early, and not on the search path: the engine loads it from its ThirdParty folder later
  // (the same module then).
  HMODULE steam = GetModuleHandleW(L"steam_api64.dll");
  if (!steam) {
    wchar_t exe[MAX_PATH];
    GetModuleFileNameW(nullptr, exe, MAX_PATH);
    std::wstring p(exe);
    p = p.substr(0, p.find_last_of(L'\\') + 1) + L"..\\..\\..\\Engine\\Binaries\\ThirdParty\\Steamworks\\Steamv151\\Win64\\steam_api64.dll";
    steam = LoadLibraryW(p.c_str());
  }
  g_ctx_orig = steam ? (ContextInit)GetProcAddress(steam, "SteamInternal_ContextInit") : nullptr;
  if (!g_ctx_orig || !hooks::attach((void**)&g_ctx_orig, (void*)&ctx_hook, "SteamInternal_ContextInit (P3A_CULTURE)")) {
    log::write("lang: SteamInternal_ContextInit not hooked");
    g_ctx_orig = nullptr;
    return;
  }
  g_ctx_hooked = true;
  log::writef("lang: the game boots as Steam language {}", g_steam_lang);
}

void boot_culture_done() {
  if (g_ctx_hooked) { hooks::detach((void**)&g_ctx_orig, (void*)&ctx_hook); g_ctx_hooked = false; }
  if (g_lang_slot && g_lang_orig) {
    write_ptr(g_lang_slot, g_lang_orig);
    g_lang_slot = nullptr;
    log::writef("lang: Steam's language answer restored (the game asked while it booted)");
  }
}

void install() {
  boot_culture_done();   // the engine is up: Steam answers for itself again
  dev::route("/lang", [](const dev::Request& r, int&) { return dev::on_game([r] { return route(r); }); },
             "?code=es (sets the mod's language until the setting is changed) &game=es (the game's culture, live; dev) "
             "&tr=English text: the mod's and the game's language");
}

// The game's own culture (dev: to test the mod against the game's other languages). Tables already loaded keep the
// language they were loaded in (to boot in a language: P3A_CULTURE, above).
static std::string set_game_culture(const std::string& g) {
  std::u16string w(g.begin(), g.end());
  ue::FString f = ue::make_fstring(w);
  ue::Params p = ue::call_static("KismetInternationalizationLibrary", "SetCurrentCulture", [&](ue::Params& q) {
    q.set<ue::FString>("Culture", f);
    q.set<bool>("SaveToConfig", false);
  });
  if (!p.fn) return "SetCurrentCulture not found\n";
  if (!p.ret<bool>()) return "the game refused that culture\n";
  return {};
}

std::string route(const dev::Request& r) {
  {
    if (dev::has(r, "game"))
      if (std::string e = set_game_culture(dev::arg(r, "game")); !e.empty()) return e;
    if (dev::has(r, "code")) {
      int c = core::lang::from_culture(dev::arg(r, "code"));
      if (c >= 0) core::lang::set(c);
    }
    std::string out = std::format("mod: {}\ngame culture: {}\n", core::lang::code(core::lang::current()), game_culture());
    if (dev::has(r, "tr")) out += std::format("tr: {}\n", core::lang::tr(std::string_view(dev::arg(r, "tr"))));
    return out;
  }
}
}  // namespace p3a::language
