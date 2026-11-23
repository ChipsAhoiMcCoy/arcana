#include "core/units.h"
#include "core/strings.h"
#include <cmath>

namespace p3a::core {
std::string meters(float m) {
  long n = std::lround(m);
  if (n < 1) return strings::kLessThanOneMeter.c_str();
  return strings::count(n, strings::kMeterUnit, strings::kMetersUnit);
}
}  // namespace p3a::core
