#include "core/path_rules.h"
#include <cmath>

namespace p3a::core {
bool walks_to(const std::vector<Vec3>& path, const Vec3& v) {
  bool ok = !path.empty() && path.back().z - v.z > -250.0f && path.back().z - v.z < 100.0f &&
            std::hypot(path.back().x - v.x, path.back().y - v.y) < 300.0f;
  for (size_t i = 1; ok && i < path.size(); ++i)
    if (std::fabs(path[i].z - path[i - 1].z) > std::hypot(path[i].x - path[i - 1].x, path[i].y - path[i - 1].y) + 100.0f) ok = false;
  return ok;
}
}  // namespace p3a::core
