#include "doctest.h"
#include "core/time_stretch.h"
#include <cmath>

using p3a::core::time_stretch;

namespace {
std::vector<float> tone(double hz, double seconds, int rate) {
  std::vector<float> v((size_t)(seconds * rate));
  for (size_t i = 0; i < v.size(); ++i) v[i] = (float)std::sin(2.0 * 3.14159265358979323846 * hz * (double)i / rate);
  return v;
}
// the frequency from rising zero crossings over [from, to)
double frequency(const std::vector<float>& v, size_t from, size_t to, int rate) {
  int crossings = 0;
  for (size_t i = from + 1; i < to; ++i)
    if (v[i - 1] < 0 && v[i] >= 0) ++crossings;
  return crossings * (double)rate / (double)(to - from);
}
}  // namespace

TEST_CASE("time_stretch: shorter by the speed, the pitch kept") {
  const int rate = 48000;
  const std::vector<float> in = tone(220, 2.0, rate);
  for (double speed : {1.25, 1.5, 1.75}) {
    CAPTURE(speed);
    const std::vector<float> out = time_stretch(in, rate, speed);
    CHECK(out.size() == (size_t)((double)in.size() / speed));
    const size_t a = rate / 10, b = out.size() - rate / 10;   // the middle, away from the edges' fades
    CHECK(frequency(out, a, b, rate) == doctest::Approx(220).epsilon(0.02));
    double rms = 0, jump = 0;
    for (size_t i = a; i < b; ++i) {
      rms += out[i] * out[i];
      jump = std::max(jump, (double)std::fabs(out[i] - out[i - 1]));
    }
    CHECK(std::sqrt(rms / (double)(b - a)) == doctest::Approx(std::sqrt(0.5)).epsilon(0.05));   // no dips where frames join
    CHECK(jump < 0.045);   // no clicks: a 220 Hz sine moves at most 0.029 a sample
  }
}

TEST_CASE("time_stretch: normal speed, or a clip too short to frame, is left as it is") {
  const std::vector<float> in = tone(300, 0.5, 48000);
  CHECK(time_stretch(in, 48000, 1.0) == in);
  const std::vector<float> tiny = tone(300, 0.02, 48000);
  CHECK(time_stretch(tiny, 48000, 1.5) == tiny);
}
