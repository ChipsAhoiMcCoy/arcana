// Emote marks. Story scenes and field scripts draw a hand-drawn mark over a character's head for a moment, with a
// short sound: "!" (surprise), "?", a sweat drop, an anger mark, "Zzz", a knock, Koromaru's woof (EAtlEvtHandwritingType;
// ~740 scenes use them, mostly "!", sweat drops, "?" and the irritated scribble). The flowscript's
// FLD_FAM_ICON_START_EX(fam, icon, ...) asks for one in the field (1 Exclamation, 10 Sweat_00, read 2026-11-21);
// events spawn them from their sequences.
// Each mark is an AHandwritingEffectBase (BP_Handwriting_Effect_<kind>_C) whose Owner is its AHandwritingSpawner; the
// spawner's root component is attached to the character's mesh (AttachParent CharacterMesh0, socket
// Soc_FX_BadStatus00), whose outer is the character. Its UAppCharBaseComp names it: GetCategoryID (1 main character)
// and GetIndexID (the player id: 1 the hero, 2 Yukari...). Both effect and spawner live a second or two and are
// destroyed: a new effect is read once, as it appears. Read through msg::say_description, so the next dialogue line
// queues after it.
#include "emotes.h"
#include "core/emote_text.h"
#include "core/strings.h"
#include "log.h"
#include "msg.h"
#include "party.h"
#include "poi.h"
#include "seh.h"
#include "settings.h"
#include "ue/ue.h"
#include "watch.h"
#include "world.h"
#include <set>
#include <string>
#include <utility>

namespace p3a::emotes {
using namespace ue;

namespace {
std::set<WeakObj::Key> g_seen;   // effects already read (an effect lives a second or two)
bool g_primed = false;           // the first tick after loading: marks already up are not new

// The character a mark is over: its spawner's root component's attach parent is the character's mesh.
UObject* character_of(UObject* effect) {
  UObject* spawner = get<UObject*>(effect, "Owner");
  if (!spawner) return nullptr;
  UObject* root = get<UObject*>(spawner, "RootComponent");
  UObject* mesh = root ? get<UObject*>(root, "AttachParent") : nullptr;
  return mesh ? outer_of(mesh) : nullptr;
}

// The character's UAppCharBaseComp: a property of the actor holding one (AppCharacterComp on the field's characters).
UObject* char_comp(UObject* actor) {
  if (UObject* c = get<UObject*>(actor, "AppCharacterComp"); c && is_a(c, "AppCharBaseComp")) return c;
  for (UStruct* s = (UStruct*)class_of(actor); s; s = super_of(s))
    for (FField* p = first_prop(s); p; p = prop_next(p)) {
      if (prop_type(p) != "ObjectProperty") continue;
      UObject* v = *(UObject**)((uint8_t*)actor + prop_offset(p));
      if (v && is_live(v) && is_a(v, "AppCharBaseComp")) return v;
    }
  return nullptr;
}

// "you", a field person's name, a party member's first name, or "" for anyone else (an extra in a story scene).
std::string who(UObject* chara) {
  if (!chara) return {};
  if (chara == world::player()) return strings::kEmoteYou.c_str();
  // A field person's model (BP_FldNpcMob_C) is owned by its FldNpcActor (FldNpcActor_316_010, 2026-11-21): the
  // name the people list gives them ("Earnest Student").
  if (UObject* owner = get<UObject*>(chara, "Owner"); owner && (is_a(owner, "FldNpcActor") || is_a(owner, "FldCmmActor")))
    if (std::string n = poi::npc_name(owner); !n.empty()) return n;
  UObject* comp = char_comp(chara);
  if (!comp) return {};
  int cat = call_ret<uint8_t>(comp, "GetCategoryID");
  int id = call_ret<int32_t>(comp, "GetIndexID");
  if (cat != 1 || id <= 0) return {};
  if (id == 1) return strings::kEmoteYou.c_str();
  return party::name(id);
}
}  // namespace

void tick() {
  static const int effects = watch::want("HandwritingEffectBase", true);
  bool primed = std::exchange(g_primed, true);
  std::set<WeakObj::Key> live;
  for (UObject* e : watch::all(effects)) {
    if (!is_live(e)) continue;
    WeakObj::Key k = WeakObj::of(e).key();
    live.insert(k);
    if (g_seen.count(k) || !primed) continue;
    std::string cls = name_of(class_of(e));
    const char* mark = core::emote_mark(cls);
    std::string name;
    guarded([&] { name = who(character_of(e)); });
    std::string line = core::emote_line(mark, name);
    log::writef("emote: {} over {}{}", cls, name.empty() ? "?" : name, settings::on(settings::Emotes) ? "" : " (off)");
    if (!line.empty() && settings::on(settings::Emotes)) msg::say_description(line.c_str());
  }
  g_seen = std::move(live);
}
}  // namespace p3a::emotes
