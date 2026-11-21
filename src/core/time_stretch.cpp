#include "core/time_stretch.h"
#include <algorithm>
#include <cmath>

namespace p3a::core {
namespace {
constexpr double kFrame = 0.040;       // seconds a frame: two or more voice periods, short enough for speech
constexpr double kTolerance = 0.012;   // how far a frame may move from its nominal place: one period down to ~85 Hz
constexpr int kCoarse = 2;             // the search's first pass tries every second offset...
constexpr int kStride = 3;             // ...comparing every third sample; the best is then refined one sample around
}  // namespace

std::vector<float> time_stretch(const std::vector<float>& in, int sample_rate, double speed) {
  const int win = std::max(64, (int)(sample_rate * kFrame)) & ~1;
  const int hop = win / 2;
  const long long tol = std::max(1, (int)(sample_rate * kTolerance));
  const long long n = (long long)in.size();
  if (speed <= 1.0 || n < 2LL * win) return in;
  const size_t out_len = (size_t)((double)n / speed);
  std::vector<float> out(out_len + win, 0.0f), norm(out_len + win, 0.0f), w(win);
  const double pi = 3.14159265358979323846;
  for (int i = 0; i < win; ++i) w[i] = (float)(0.5 - 0.5 * std::cos(2.0 * pi * i / win));   // periodic Hann: halves sum to 1
  auto at = [&](long long i) { return i >= 0 && i < n ? in[(size_t)i] : 0.0f; };
  // How well the frame at `pos` continues the last one: its correlation with the input that followed the last frame,
  // over the half that will overlap, normalized by its own energy (a loud spot is not a better fit).
  auto fit = [&](long long pos, long long natural, int stride) {
    double xy = 0, yy = 1e-9;
    for (int i = 0; i < hop; i += stride) {
      const double y = at(pos + i);
      xy += y * at(natural + i);
      yy += y * y;
    }
    return xy / std::sqrt(yy);
  };
  long long prev = 0;
  for (size_t m = 0; m * hop < out_len; ++m) {
    const long long nominal = std::llround((double)(m * hop) * speed);
    long long pos = nominal;
    if (m > 0) {
      const long long natural = prev + hop;
      const long long lo = std::max(0LL, nominal - tol), hi = nominal + tol;
      double best = -1e300;
      for (long long k = lo; k <= hi; k += kCoarse) {
        const double f = fit(k, natural, kStride);
        if (f > best) { best = f; pos = k; }
      }
      const long long c = pos;
      best = fit(c, natural, 1);
      for (long long k = std::max(lo, c - kCoarse + 1); k <= std::min(hi, c + kCoarse - 1); ++k) {
        if (k == c) continue;
        const double f = fit(k, natural, 1);
        if (f > best) { best = f; pos = k; }
      }
    }
    const size_t base = m * hop;
    for (int i = 0; i < win; ++i) {
      out[base + i] += w[i] * at(pos + i);
      norm[base + i] += w[i];
    }
    prev = pos;
  }
  out.resize(out_len);
  for (size_t i = 0; i < out_len; ++i)
    if (norm[i] > 1e-3f) out[i] /= norm[i];
  return out;
}
}  // namespace p3a::core
