// The story's data assets (dat.h). The game's loaders (UDatSkill, UDatPersona and the unreflected player-table
// loader) build their table paths from /Game/Xrd777/ and switch to /Game/Astrea/ when FUN_140fcb300 is true, the
// native behind AstreaFuncLib.IsPlayingAstrea; /dat compares this module's choice with their pointers.
#include "dat.h"
#include "core/dat_pick.h"
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "seh.h"
#include "watch.h"
#include <format>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace p3a::dat {
using namespace ue;

bool astrea() {
  static uint64_t frame = ~0ull;
  static bool playing = false;
  if (hooks::frame() == frame) return playing;
  frame = hooks::frame();
  Params p = call_static("AstreaFuncLib", "IsPlayingAstrea");
  static bool told = false;
  if (!p.fn && !told) { told = true; log::write("dat: AstreaFuncLib.IsPlayingAstrea not found; reading the main story's tables"); }
  bool now = p.fn && p.ret<bool>();
  static bool logged = false, last = false;
  if (!logged || now != last) { logged = true; last = now; log::writef("dat: story {}", now ? "Episode Aigis" : "main"); }
  return playing = now;
}

namespace {
struct Choice { uint64_t frame = ~0ull; WeakObj obj; };
std::map<std::pair<int, std::string>, Choice>& choices() { static std::map<std::pair<int, std::string>, Choice> m; return m; }
std::set<std::string>& warned() { static std::set<std::string> s; return s; }

// The candidates of one name, oldest first.
std::vector<UObject*> candidates(int watch_id, std::string_view name) {
  std::vector<UObject*> out;
  for (UObject* o : watch::all(watch_id)) if (name_of(o) == name) out.push_back(o);
  return out;
}
}  // namespace

UObject* find(int watch_id, std::string_view name) {
  Choice& c = choices()[{watch_id, std::string(name)}];
  const uint64_t now = hooks::frame();
  if (c.frame == now) return c.obj.resolve();
  c.frame = now;
  auto cands = candidates(watch_id, name);
  std::vector<std::string> paths;
  for (UObject* o : cands) paths.push_back(path_name(o));
  const bool aigis = astrea();
  core::DatPick pick = core::pick_asset(paths, aigis);
  if (paths.size() > 1 && warned().insert(std::string(name)).second) {
    std::string list;
    for (size_t i = 0; i < paths.size(); ++i) list += std::format("{}{}{}", i ? ", " : "", paths[i], (int)i == pick.index ? " (read)" : "");
    log::writef("dat: warning: {} copies of {} loaded ({} story): {}", paths.size(), name, aigis ? "Episode Aigis" : "main", list);
  }
  if (pick.fallback && warned().insert(std::string(name) + "#fallback").second)
    log::writef("dat: warning: no {} copy of {} loaded; reading {}", aigis ? "Episode Aigis" : "main story", name, paths[pick.index]);
  c.obj = pick.index >= 0 ? WeakObj::of(cands[pick.index]) : WeakObj{};
  return pick.index >= 0 ? cands[pick.index] : nullptr;
}

void install() {
  dev::route("/dat", [](const dev::Request&, int&) {
    return dev::on_game([] {
      std::string s = std::format("story: {}\n", astrea() ? "Episode Aigis" : "main");
      for (auto& [key, c] : choices()) {
        s += std::format("{} (watch {}):\n", key.second, key.first);
        UObject* chosen = find(key.first, key.second);
        for (UObject* o : candidates(key.first, key.second))
          s += std::format("  {}{}\n", path_name(o), o == chosen ? "  <- read" : "");
      }
      // The game's own loaders' pointers, for comparison.
      auto loader = [&](const char* cls, const char* prop) {
        UObject* l = find_first(cls);
        UObject* t = l ? get<UObject*>(l, prop) : nullptr;
        s += std::format("game {}.{}: {}\n", cls, prop, t ? path_name(t) : std::string("none"));
      };
      loader("DatPersona", "TableAttr");
      loader("DatPersona", "TableName");
      loader("DatSkill", "TableName");
      loader("DatSkill", "TableNormal");
      return s;
    });
  }, "the data assets read by name: every loaded copy and the one read (dev)");
}
}  // namespace p3a::dat
