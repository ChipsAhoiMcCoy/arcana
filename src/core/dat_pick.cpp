#include "core/dat_pick.h"

namespace p3a::core {
bool astrea_package(std::string_view path) { return path.find("/Astrea/") != std::string_view::npos; }

DatPick pick_asset(const std::vector<std::string>& paths, bool astrea) {
  DatPick p;
  for (int i = (int)paths.size(); i-- > 0;)
    if (astrea_package(paths[i]) == astrea) { p.index = i; return p; }
  if (!paths.empty()) { p.index = (int)paths.size() - 1; p.fallback = true; }
  return p;
}
}  // namespace p3a::core
