#pragma once
// Speeding up a recorded voice without raising its pitch (setting SceneSpeed: the narrator of 3D scene descriptions,
// ad.cpp). WSOLA: the output is built from Hann-windowed frames overlapping by half; each frame is taken from the input
// at its nominal place (output time * speed), moved by up to `kTolerance` to where it best continues the frame before
// it (cross-correlation), so the voice's periods line up and nothing clicks or warbles. Mono float PCM, any rate.
#include <vector>

namespace p3a::core {
// `speed` > 1 shortens: the result lasts about in.size() / speed samples. speed <= 1 (or a clip shorter than one frame)
// returns the input as it is.
std::vector<float> time_stretch(const std::vector<float>& in, int sample_rate, double speed);
}  // namespace p3a::core
