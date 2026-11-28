// Emote marks: the handwritten "!", "?", sweat drop, "Zzz" ... the game pops over a character's head for a second or
// two, in the field (the scripts' FLD_FAM_ICON_START(_EX), a chest's trap, a person noticing you) and in story scenes
// (a sequence's MovieSceneEvtCharaHandwritingTrack: 669 of the base game's scenes). They are pictures with no text,
// so each is said as it appears: "Junpei, surprised".
// The chain (this build, 2026-11-28, read live from FLD_FAM_ICON_START_EX(0, 1, -1) on the hero): the mark is an
// AHandwritingEffectBase (BP_Handwriting_Effect_<EAtlEvtHandwritingType>_C, its class names the kind); its Owner is an
// AHandwritingSpawner (BP_Handwriting_Field_Spawner_C / _Event_Spawner_C), whose RootComponent is attached to the
// character's CharacterMesh0; the mesh's outer is the character actor. Who it is: the actor's UAppCharBaseComp
// (GetCategoryID: 1 MainCharacter, GetIndexID the character id, 1 the hero), else a field person's model, whose
// Owner is its FldNpcActor (the points-of-interest name). A mark whose owner is not set yet is read the next tick.
#include "emote.h"
#include "core/strings.h"
#include "log.h"
#include "party.h"
#include "poi.h"
#include "seh.h"
#include "settings.h"
#include "speech.h"
#include "ue/ue.h"
#include "watch.h"
#include <algorithm>
#include <format>
#include <string_view>
#include <vector>

namespace p3a::emote {
using namespace ue;
namespace {
// The mark's kind from its class name, as EAtlEvtHandwritingType orders them; -1 for none of them.
int kind_of(UObject* fx) {
  static constexpr std::string_view kKinds[] = {"AngerMark_00", "AngerMark_01", "Calling", "DoorKnock_00",
                                                "Exclamation_00", "Sweat_00", "DoubleExclamation_00", "Question_00",
                                                "ExclamationQuestion_00", "Sweat_01", "Woof_00", "Whine_00", "Zzz_00",
                                                "Ittitate_00", "AccessIcon_Listen"};
  std::string c = name_of((UObject*)class_of(fx));
  constexpr std::string_view head = "BP_Handwriting_Effect_", tail = "_C";
  if (c.size() <= head.size() + tail.size() || c.rfind(head, 0) != 0) return -1;
  std::string_view k = std::string_view(c).substr(head.size(), c.size() - head.size() - tail.size());
  for (int i = 0; i < (int)std::size(kKinds); ++i)
    if (k == kKinds[i] || (i == 0 && k == "AngerMark")) return i;
  return -1;
}

// The character a mark hangs over: its actor, or null while the spawner is not attached yet.
UObject* character_of(UObject* fx) {
  UObject* spawner = get<UObject*>(fx, "Owner");
  UObject* root = spawner ? get<UObject*>(spawner, "RootComponent") : nullptr;
  UObject* mesh = root ? get<UObject*>(root, "AttachParent") : nullptr;
  return mesh ? outer_of(mesh) : nullptr;
}

// "You", a party member's first name, a field person's name, or "" when the game gives the character none.
std::string who(UObject* actor) {
  static const int comps = watch::want("AppCharBaseComp", true);
  for (UObject* c : watch::all(comps)) {
    if (outer_of(c) != actor) continue;
    int category = call_ret<uint8_t>(c, "GetCategoryID");
    int id = call_ret<int32_t>(c, "GetIndexID");
    if (category == 1 && id == 1) return strings::kEmoteYou.c_str();
    if (category == 1 && id > 1 && id <= 12) {
      std::string n = party::name(id);
      if (!n.empty()) return n;
    }
    break;
  }
  if (UObject* npc = get<UObject*>(actor, "Owner")) return poi::npc_name(npc);
  return {};
}
}  // namespace

void tick() {
  static const int fx_id = watch::want("HandwritingEffectBase", true);
  static std::vector<WeakObj> said;   // the marks said, while they live
  std::erase_if(said, [](const WeakObj& w) { return !w.valid(); });
  for (UObject* fx : watch::all(fx_id)) {
    WeakObj w = WeakObj::of(fx);
    if (std::find(said.begin(), said.end(), w) != said.end()) continue;
    int kind = kind_of(fx);
    if (kind < 0) { said.push_back(w); continue; }
    UObject* actor = nullptr;
    if (!guarded([&] { actor = character_of(fx); }) || !actor) continue;   // not attached yet
    said.push_back(w);
    if (!settings::on(settings::EmoteMarks)) continue;   // turned off: marked as said, never read later
    std::string name;
    guarded([&] { name = who(actor); });
    std::string word = strings::kEmotes[kind].c_str();
    log::writef("emote: {} over {} ({})", name_of((UObject*)class_of(fx)), name_of(actor), name);
    speech::speak(name.empty() ? word : strings::fmt(strings::kEmoteFmt, name, word), false);
  }
}
}  // namespace p3a::emote
