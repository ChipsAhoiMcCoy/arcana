#pragma once
// Which loaded copy of a data asset to read. Persona 3 Reload ships most of its tables twice: the main story's under
// /Game/Xrd777/ and Episode Aigis's under /Game/Astrea/ (localized copies under /Game/L10N/<lang>/Xrd777|Astrea/),
// same class, same object name. The game's own loaders take the Astrea paths while AstreaFuncLib.IsPlayingAstrea is
// true, the Xrd777 ones otherwise; the mod chooses the same way.
#include <string>
#include <string_view>
#include <vector>

namespace p3a::core {
// Whether an object path is in Episode Aigis's set (a "/Astrea/" folder anywhere in it).
bool astrea_package(std::string_view path);

struct DatPick {
  int index = -1;          // into the candidates, or -1 when there are none
  bool fallback = false;   // no candidate is in the running story's set: the newest of the others
};
// The candidate to read, from the paths of the loaded objects of one name (oldest first): the newest in the running
// story's set, else the newest of all.
DatPick pick_asset(const std::vector<std::string>& paths, bool astrea);
}  // namespace p3a::core
