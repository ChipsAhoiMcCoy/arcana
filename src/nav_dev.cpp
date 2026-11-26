// The auto-walk's dev half: the direct movement experiments (/nav?sample, ?push), the /nav route (walk, stop, drive,
// map, floor, body, plan) and /strike. Moved out of nav.cpp (2026-11-26); what they share is nav_internal.h.
#include "nav.h"
#include "nav_internal.h"
#include "devserver.h"
#include "hooks.h"
#include "log.h"
#include "poi.h"
#include "seh.h"
#include "world.h"
#include <algorithm>
#include <cmath>
#include <format>
#include <memory>

namespace p3a::nav {
using ue::WeakObj;
using world::trigger_box;

// ---- dev: how the game moves the hero (direct movement experiments) ----
// /nav?sample=ms logs his movement state every 100 ms for that long; /nav?push=yaw&ms=[&force=1][&speed=cm/s]
// asks his pawn to move along world yaw every frame for that long, then logs how far he went.
static ULONGLONG g_sample_until = 0, g_sample_next = 0;
static ULONGLONG g_push_until = 0;
static float g_push_yaw = 0, g_push_speed = 0;
static bool g_push_force = false;
static FVector g_push_from{};
void dev_tick(ULONGLONG now) {
  ue::UObject* hero = world::player();
  if (!hero) return;
  ue::UObject* cmc = ue::get<ue::UObject*>(hero, "CharacterMovement");
  if (g_push_until) {
    FVector me{};
    world::player_location(me);
    if (now >= g_push_until) {
      g_push_until = 0;
      log::writef("nav dev: push done, moved {:.0f} cm (from ({:.0f}, {:.0f}) to ({:.0f}, {:.0f}))", flat(g_push_from, me), g_push_from.x, g_push_from.y, me.x, me.y);
    } else {
      float r = g_push_yaw * 3.14159265f / 180.0f;
      if (g_push_speed > 0 && cmc) if (float* m = ue::field<float>(cmc, "MaxWalkSpeed")) *m = g_push_speed;
      ue::Params a(ue::find_function(ue::class_of(hero), "AddMovementInput"));
      a.set<FVector>("WorldDirection", FVector{std::cos(r), std::sin(r), 0.0f});
      a.set<float>("ScaleValue", 1.0f);
      a.set<bool>("bForce", g_push_force);
      ue::call(hero, a);
    }
  }
  if (g_sample_until && now >= g_sample_next) {
    if (now >= g_sample_until) { g_sample_until = 0; return; }
    g_sample_next = now + 100;
    FVector me{};
    world::player_location(me);
    auto v3 = [](ue::UObject* o, const char* n) { ue::FVector v = o ? ue::get<ue::FVector>(o, n) : ue::FVector{}; return std::format("({:.0f},{:.0f})", v.x, v.y); };
    ue::Params ig(ue::find_function(ue::class_of(hero), "IsMoveInputIgnored"));
    ue::call(hero, ig);
    log::writef("nav dev: at ({:.0f}, {:.0f}) vel {} accel {} maxwalk {:.0f} ctlin {} lastin {} ignored {} held {:c}{:c}", me.x, me.y, v3(cmc, "Velocity"), v3(cmc, "Acceleration"),
                cmc ? ue::get<float>(cmc, "MaxWalkSpeed") : -1.0f, v3(hero, "ControlInputVector"), v3(hero, "LastControlInputVector"), ig.ret<bool>(),
                g_held[0] ? (char)g_held[0] : '-', g_held[1] ? (char)g_held[1] : '-');
  }
}

void install_dev() {
  // Dev: the field strike without a key. A posted Ctrl reaches the game's input layer but never starts the attack
  // (2026-10-27); the dungeon component's state machine does: NextBehavior = Attack (7) while Behavior is Free (1)
  // swings once and returns to Free. The player strikes with Ctrl as usual.
  dev::route("/strike", [](const dev::Request&, int&) {
    auto out = std::make_shared<std::string>("no dungeon player\n");
    hooks::run_on_game_thread([out] {
      if (!ue::known_build()) { *out = "another build of the game\n"; return; }   // the offsets below are this build's
      ue::UObject* c = ue::find_first("FldPlayerDungeonComp");
      if (!c) return;
      int32_t* b = ue::field<int32_t>(c, "Behavior");
      int32_t* nb = ue::field<int32_t>(c, "NextBehavior");
      if (!b || !nb) return;
      if (*b != 1) { *out = std::format("busy (behavior {})\n", *b); return; }
      // The attack looks its data up by AttackId (+0x514) in a native set at +0x188 (elements of 0x3c: key +0,
      // next +0x34; buckets inline at +0x1c0 or behind +0x1c8, size +0x1d0) and reads through null when the id is
      // missing: that crashed right after a battle (P3R.exe+0x1125183, 2026-10-27). Same lookup here first.
      uint8_t* p = (uint8_t*)c;
      // A fresh session's AttackId is 0, which has no data; a real first swing uses 1 (the combo's first blow).
      auto has = [&](int32_t id) {
      bool found = false;
      guarded([&] {
        if (*(int32_t*)(p + 0x190) == *(int32_t*)(p + 0x1bc)) return;   // empty
        int32_t* buckets = *(int32_t**)(p + 0x1c8) ? *(int32_t**)(p + 0x1c8) : (int32_t*)(p + 0x1c0);
        int32_t idx = buckets[(*(int32_t*)(p + 0x1d0) - 1) & id];
        uint8_t* elems = *(uint8_t**)(p + 0x188);
        for (int n = 0; idx != -1 && n < 64; ++n) {
          uint8_t* e = elems + (size_t)idx * 0x3c;
          if (*(int32_t*)e == id) { found = true; return; }
          idx = *(int32_t*)(e + 0x34);
        }
      });
      return found;
      };
      int32_t* id = (int32_t*)(p + 0x514);
      if (!has(*id)) {
        if (!has(1)) { *out = std::format("no attack data for id {}\n", *id); return; }
        *id = 1;
      }
      *nb = 7;
      *out = "ok\n";
    });
    return *out;
  }, "field strike in Tartarus (dev)");
  dev::route("/nav", [](const dev::Request& r, int&) {
    if (dev::has(r, "walk")) {
      int obj = (int)dev::arg_int(r, "walk", -1);
      bool use = dev::has(r, "use");
      hooks::run_on_game_thread([obj, use] { ue::UObject* o = ue::object_at(obj); if (!o) return;
        // The name the points of interest list gives it, as the walk key passes it (arriving compares it with the
        // game's prompt): a person has no hit name, and the object's own name never matched the prompt.
        std::string n;
        for (const poi::Poi& p : poi::scan(30000.0f)) if (p.obj.index == obj) { n = p.name; break; }
        if (n.empty()) n = poi::hit_name(o);
        walk_to(WeakObj::of(o), n.empty() ? ue::name_of(o) : n, use); });
    }
    if (dev::has(r, "stop")) hooks::run_on_game_thread([] { stop(true); });
    if (dev::has(r, "sample")) {
      ULONGLONG ms = (ULONGLONG)dev::arg_int(r, "sample", 2000);
      hooks::run_on_game_thread([ms] { g_sample_until = GetTickCount64() + ms; g_sample_next = 0; });
    }
    if (dev::has(r, "push")) {
      float yaw = (float)dev::arg_num(r, "push", 0), speed = (float)dev::arg_num(r, "speed", 0);
      ULONGLONG ms = (ULONGLONG)dev::arg_int(r, "ms", 1000);
      bool force = dev::arg(r, "force") == "1";
      hooks::run_on_game_thread([yaw, speed, ms, force] {
        g_push_yaw = yaw; g_push_speed = speed; g_push_force = force;
        world::player_location(g_push_from);
        g_push_until = GetTickCount64() + ms;
      });
    }
    if (dev::has(r, "drive")) {
      // How the walk steers: auto (directly once the game is seen to take it, else keys), native, keys.
      std::string d = dev::arg(r, "drive");
      hooks::run_on_game_thread([d] {
        g_drive = d == "native" ? Drive::Native : d == "keys" ? Drive::Keys : Drive::Auto;
        if (g_drive == Drive::Auto) g_native = 0;
      });
    }
    if (dev::has(r, "map")) {
      // Where the hero's body fits, as a character map round him (`map` = half width in cm, `cell` cm): . fits,
      // # blocked, p a person, @ the hero. North (+x) is up, +y to the right.
      float span = (float)dev::arg_num(r, "map", 700), cell = (float)dev::arg_num(r, "cell", 20), spare = (float)dev::arg_num(r, "spare", 3);
      auto out = std::make_shared<std::string>("timeout\n");
      hooks::run_on_game_thread([out, span, cell, spare] {
        FVector me;
        if (!world::player_location(me)) { *out = "no player\n"; return; }
        float radius, half;
        hero_body(radius, half);
        float z = me.z + 10.0f, h = std::max(radius + 1.0f, half - 30.0f);
        std::string s = std::format("hero ({:.0f}, {:.0f}, {:.0f}) body {:.1f} + {:.0f} cm, cell {:.0f}\n", me.x, me.y, me.z, radius, spare, cell);
        int n = (int)(span / cell);
        for (int i = n; i >= -n; --i) {
          for (int j = -n; j <= n; ++j) {
            if (i == 0 && j == 0) { s += '@'; continue; }
            FVector p{me.x + i * cell, me.y + j * cell, z};
            world::Hit hh = world::sweep(p, FVector{p.x + 0.5f, p.y, z}, radius + spare, h);
            if (!hh.hit) { s += '.'; continue; }
            std::vector<ue::UObject*> people;
            world::Hit hp = world::sweep(p, FVector{p.x + 0.5f, p.y, z}, radius + spare, h, &people);
            s += hp.hit ? '#' : 'p';
          }
          s += '\n';
        }
        *out = s;
      });
      return *out;
    }
    if (dev::has(r, "floor")) {
      // Whether the hero stands on his floor's navmesh, and the way onto it from here (reads only).
      return dev::on_game([] {
        FVector me, at{}, out{}, any{};
        if (!world::player_location(me)) return std::string("no player\n");
        FVector f = feet_of(me);
        bool on = on_floor_nav(me, &at);
        bool near_any = world::project_to_nav(f, 300.0f, any);
        bool way = !on && way_onto_floor_nav(me, out);
        return std::format("hero ({:.0f}, {:.0f}, {:.0f}) feet z {:.0f}\non floor navmesh: {}{}\nnearest navmesh (3 m cube): {}\nway onto it: {}\n", me.x, me.y,
                           me.z, f.z, on, on ? std::format(" at ({:.0f}, {:.0f}, {:.0f})", at.x, at.y, at.z) : std::string(),
                           near_any ? std::format("({:.0f}, {:.0f}, {:.0f})", any.x, any.y, any.z) : std::string("none"),
                           way ? std::format("({:.0f}, {:.0f})", out.x, out.y) : std::string(on ? "not needed" : "none"));
      });
    }
    if (dev::has(r, "body")) {
      // The way between the furniture to a target as a walk in a split room would plan it (reads only).
      int obj = (int)dev::arg_int(r, "body", -1);
      bool past = dev::arg(r, "people") == "0";
      auto out = std::make_shared<std::string>("timeout\n");
      hooks::run_on_game_thread([out, obj, past] {
        ue::UObject* o = ue::object_at(obj);
        FVector me;
        if (!o || !world::player_location(me)) { *out = "no player or target\n"; return; }
        std::string s;
        std::vector<FVector> pts;
        body_plan(goal_of(o), me, pts, &s, past);
        *out = s;
      });
      return *out;
    }
    if (dev::has(r, "plan")) {
      // The ways in to a target as the walk would find them from here (reads only: sweeps and paths).
      int obj = (int)dev::arg_int(r, "plan", -1);
      auto out = std::make_shared<std::string>("timeout\n");
      hooks::run_on_game_thread([out, obj] {
        ue::UObject* o = ue::object_at(obj);
        FVector me;
        if (!o || !world::player_location(me)) { *out = "no player or target\n"; return; }
        Goal g;
        g.has_box = trigger_box(o, g.box);
        g.at = world::actor_location(o);
        float radius, half;
        hero_body(radius, half);
        std::vector<ue::UObject*> people;
        FVector c = centre(g);
        std::string s = g.has_box ? std::format("box extent ({:.0f}, {:.0f}, {:.0f}) yaw {:.0f}\n", g.box.extent.x, g.box.extent.y, g.box.extent.z, g.box.yaw) : std::string();
        s += std::format("target ({:.0f}, {:.0f}, {:.0f}) box={} hero ({:.0f}, {:.0f}) body {:.1f} x {:.1f}\nstraight in from here: {}\n", c.x, c.y, c.z,
                                    g.has_box, me.x, me.y, radius, half, sweep_reaches(g, me, me, radius, half, people) ? "clear" : "blocked");
        LARGE_INTEGER a, z, f;
        QueryPerformanceCounter(&a);
        auto entries = find_entries(g, me, &s);
        QueryPerformanceCounter(&z); QueryPerformanceFrequency(&f);
        s += std::format("{} way(s) in, found in {} us\n", entries.size(), (z.QuadPart - a.QuadPart) * 1000000 / f.QuadPart);
        *out = s;
      });
      return *out;
    }
    return status();
  }, "?walk=objindex [&use=1: press Space there] | ?stop=1 the auto-walk | ?drive=auto|native|keys how it steers | ?plan=objindex the ways in to a target | ?body=objindex the way between the furniture");
}
}  // namespace p3a::nav
