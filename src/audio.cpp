// Altered from Grim Dark (GD Access) by Austin Hicks, itself ported from Dark Vision (WrathAccess) by Bradley Renshaw; both zlib, see LICENSES/. This is not the original software.
#include "audio.h"
#include "paths.h"
#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_ENCODING
#define MA_NO_FLAC
#define MA_NO_GENERATION
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_ENGINE
#define MA_NO_DEVICE_IO_CUSTOM_BACKEND
#include <miniaudio.h>
#include <windows.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <format>
#include <memory>
#include <mutex>
#include <vector>
#include "core/sonar_cues.h"
#include "core/spatializer.h"
#include "devserver.h"
#include "hrtf.h"
#include "log.h"

namespace p3a::audio {
namespace {
constexpr int kRate = 48000;
constexpr int kPeriod = 480;   // 10 ms; miniaudio's fixed-size callback always delivers this many frames
constexpr float kPi = 3.14159265358979f;

// Every gain change glides instead of stepping: a volume that jumps between two samples is a click, and the
// drivers (wall tones every frame, 10 ms mixer blocks) change volumes in steps. One pole, ~5 ms time constant: per
// sample, so still no click; 15 ms (until 2026-11-17) put a wall tone's change 10 to 45 ms behind the walk.
constexpr float kGlide = 1.0f - 0.995842f;  // 1 - exp(-1 / (0.005 s * 48000))
constexpr float kSilent = 1e-5f;            // below this a gliding voice counts as stopped

// A looping mono sample at a fixed pan (the wotr WallTones channel), on the Walls bus.
struct Loop {
  int id;
  std::vector<float> samples;
  size_t pos = 0;
  float volume = 0;         // requested by the driver
  float cur = 0;            // what plays, gliding toward volume * gain
  float gain = 1.0f;        // static trim (set_loop_gain, not clamped): the wall tones' per-file loudness match
  float gl = 0.70710677f, gr = 0.70710677f;
  ULONGLONG refreshed = 0;  // GetTickCount64 at the last set_loop_volume: a loop nobody drives goes silent
  double onset_at = 0;      // dev: when the driver turned it on from silence (now_s), until the mixer has it at half
};
constexpr ULONGLONG kLoopStaleMs = 250;  // the game stops ticking us while paused; the loops must not sing on

// The narrator (audio description, src/ad.cpp): one mono sample at a time, centred, on the Narration bus. A new
// one replaces the old; stop fades out (kNarrFade: silent within 70 ms); pause holds the position. `played` counts the frames that reached
// the output, so the caller can tell a clip that played in full from one cut short.
struct Narr {
  int id = -1;
  std::shared_ptr<const std::vector<float>> pcm;
  size_t pos = 0;
  float cur = 0;            // gliding gain (fade in/out)
  bool paused = false;
  bool stopping = false;
  bool ended = false;       // reached the end of the sample
  bool active = false;
};
constexpr float kNarrFade = 1.0f - 0.99653f;   // 1 - exp(-1 / (0.006 s * 48000)): ~20 ms to 5 %, ~70 ms to kSilent

// A one-shot sample from a place (the sonar's sounds): read at `rate` with linear interpolation.
struct Shot {
  Pcm pcm;
  double pos = 0;
  float rate = 1.0f, vol = 1.0f;
  Bus bus = Bus::Cues;
  Spot spot;
  bool spatial = true;    // false once no HRTF slot was free: panned to its end
  int slot = -1;          // the HRTF slot, held one block past the end for the filter's tail
  bool dead = false;
  bool focus = false;     // plays through the solo
  double start_s = 0;     // when it starts (now_s; 0: at the next block), placed to the sample in its block
  float duck = 1.0f;      // glides to 0 when the solo silences it (it is then cut)
  float fall = -1.0f;     // the distance curve's gain where the last block ended (spot.falloff; -1: not started)
  core::SpatialVoice stereo;   // Dark Vision's stereo model: its filters' and delay's state (held by value: the audio
                               // thread neither allocates nor frees)
  // A held voice (audio::hold): loops, its volume, tone and wobble glide to what the caller last asked, and it fades
  // out and ends once the caller stops asking for hold_ms.
  int hold = 0;                // its id; 0: a one-shot
  ULONGLONG held_at = 0;       // GetTickCount64 at the last hold() for it
  ULONGLONG hold_ms = 250;     // how long it plays on unasked
  float vol_to = 0.0f;         // the volume it glides to (vol is where it is)
  float tone = 1.0f, tone_to = 1.0f;       // brightness 0..1 (1: as recorded)
  float wobble = 0.0f, wobble_to = 0.0f;   // the tremolo's depth 0..1
  float lp = 0.0f;             // the low-pass's state
  double trem = 0.0;           // the tremolo's phase
};
// A held voice unasked for its hold_ms (250 by default, as the wall tones: the game stops ticking us while paused).
constexpr double kWobbleHz = 6.0;
// The low-pass's corner for a tone: 1 is open (no filter), 0 is 350 Hz, between them evenly in octaves.
float tone_coef(float tone, int rate) {
  if (tone >= 0.999f) return 1.0f;
  double hz = 350.0 * std::pow(9000.0 / 350.0, std::clamp((double)tone, 0.0, 1.0));
  return (float)(1.0 - std::exp(-2.0 * kPi * hz / rate));
}
constexpr size_t kMaxShots = 32;   // more at once is a runaway caller: further ones are dropped
std::atomic<bool> g_solo{false};   // audio::solo
// What the solo silences: every sound from a place except the focus. A Cues sound with no place is about the player.
bool soloed_out(const Shot& s) { return !s.focus && (s.bus != Bus::Cues || s.spot.placed); }

std::mutex g_mu;
std::vector<Shot> g_shots;
Narr g_narr;
Narr g_narr_out;   // the clip a new one replaced, fading out under it (a cut mid-word clicked)
std::vector<Loop> g_loops;
ma_device g_device;
std::atomic<bool> g_ready{false};   // the device is open and playing
// The output device can go (a headset unplugged with nothing to fall back to) or be missing at launch: tick() opens it
// again, every kRetryMs, without touching what is loaded or playing.
bool g_inited = false;                // init ran (game thread)
std::atomic<bool> g_lost{false};      // the device stopped on its own
std::atomic<bool> g_rerouted{false};  // miniaudio moved the stream to the new default device
std::atomic<bool> g_closing{false};   // our own uninit: its stop is not a loss
ULONGLONG g_retry_at = 0;
bool g_retry_logged = false;
constexpr ULONGLONG kRetryMs = 3000;
float g_master = 1.0f;   // the player's Master volume: scales every bus
// Buses: one volume per kind of sound, so each can be set apart (and later exposed as a setting). target is
// requested; cur is where the last block ended, and each block ramps linearly from cur to target.
struct BusState { float target = 1.0f, cur = 1.0f; };
BusState g_bus[(int)Bus::Count] = {{0.6f, 0.6f}, {1.0f, 1.0f}, {1.0f, 1.0f}, {0.8f, 0.8f}};   // settings set them at load
// The output limiter: sums above the ceiling are turned down at once and recover over ~100 ms, instead of being
// clipped (a hard clip of several sounds at once crackles).
constexpr float kCeiling = 0.95f;
constexpr float kRelease = 1.0f - 0.99979f;   // 1 - exp(-1 / (0.1 s * 48000))
float g_limit = 1.0f;
uint32_t g_limited_blocks = 0;   // dev: blocks in which the limiter worked
// 3D sound: positional sounds go through an HRTF slot. Fallbacks (no free slot, or a block of an unexpected size)
// pan instead and are counted for /audio.
// Dark Vision's stereo model is the one placement now (the user's call, 2026-11-25): the HRTF is never switched on
// and never initialised; its code stays until that model has been played with.
constexpr bool g_hrtf_on = false;
// Inside it the pan follows the sideways offset; beyond it, the bearing. Dark Vision's own 10 ft (1 m was used here
// from 2026-11-13; back to Dark Vision's to match it exactly, 2026-11-25).
using core::kPanWidthM;
uint32_t g_hrtf_fallbacks = 0;
bool g_odd_block_logged = false;
constexpr int kMaxBlock = 4096;
float g_mono[kMaxBlock], g_ear_l[kMaxBlock], g_ear_r[kMaxBlock];   // audio thread only
uint64_t g_cb_max_us = 0;   // dev: the slowest callback
// The mixer's clock: which now_s moment a block stands for. Frames rendered since the device opened, plus a base that
// follows the callbacks' own times smoothly (they come in bursts while the buffer fills, and wake a little late).
// Every block plays the device's buffer later, the same for all of them: a sound placed at its time keeps its beat.
uint64_t g_frames = 0;
double g_clock = 0;
bool g_clock_ok = false;
// dev (/audio): a wall tone's onset (the driver's first volume over silence to the mixer playing it at half), and the
// scheduled starts (how many, how many came after their time and by how much at most).
struct Lat { uint32_t n = 0; double sum_ms = 0, max_ms = 0; void add(double ms) { ++n; sum_ms += ms; max_ms = std::max(max_ms, ms); } };
Lat g_onset, g_late;
uint32_t g_scheduled = 0;
double g_buffer_ms = 0;   // the device's buffer (WASAPI), logged when it opens

void pan_gains(float pan, float& l, float& r) {
  float a = (pan + 1.0f) * (kPi / 4.0f);  // equal power
  l = std::cos(a); r = std::sin(a);
}

hrtf::Dir dir_of(const Spot& s) { return {s.right, s.up, s.ahead, s.dist_m}; }
// A slot's output added to the block.
void add_ears(float* o, ma_uint32 frames) {
  for (ma_uint32 i = 0; i < frames; ++i) { o[i * 2] += g_ear_l[i]; o[i * 2 + 1] += g_ear_r[i]; }
}

void data_callback(ma_device*, void* out, const void*, ma_uint32 frames) {
  LARGE_INTEGER t0; QueryPerformanceCounter(&t0);
  float* o = (float*)out;
  for (ma_uint32 i = 0; i < frames * 2; ++i) o[i] = 0;
  std::lock_guard lk(g_mu);
  // The moment this block stands for (see g_clock). A jump (the device stalled, or reopened) starts the clock again.
  {
    const double obs = now_s() - (double)g_frames / kRate;
    if (!g_clock_ok || std::abs(obs - g_clock) > 0.1) { g_clock = obs; g_clock_ok = true; }
    else g_clock += (obs - g_clock) * 0.02;
  }
  const double block_t = g_clock + (double)g_frames / kRate;
  g_frames += frames;
  // HRTF slots need the fixed block size they were made for (miniaudio's fixed-size callback gives it).
  const bool hrtf_block = g_hrtf_on && hrtf::available() && (int)frames == hrtf::frame() && frames <= (ma_uint32)kMaxBlock;
  if constexpr (g_hrtf_on) {
    if (hrtf::available() && !hrtf_block && !g_odd_block_logged) {
      g_odd_block_logged = true;
      log::writef("audio: a {}-frame block (HRTF needs {}); positional sounds pan for such blocks", frames, hrtf::frame());
    }
  }
  // Per-bus gain ramps for this block: from where the last block ended to the target (the master folded in).
  float b_from[(int)Bus::Count], b_step[(int)Bus::Count];
  for (int b = 0; b < (int)Bus::Count; ++b) {
    float target = g_bus[b].target * g_master;
    b_from[b] = g_bus[b].cur;
    b_step[b] = frames ? (target - g_bus[b].cur) / (float)frames : 0.0f;
    g_bus[b].cur = target;
  }
  auto bus_gain = [&](Bus b, ma_uint32 i) { return b_from[(int)b] + b_step[(int)b] * (float)(i + 1); };
  const bool soloing = g_solo;
  for (Shot& sh : g_shots) {
    if (sh.dead) {
      // The block after a shot ends: its slot plays the filters' tail, then is free again.
      if (sh.slot >= 0) {
        if (hrtf_block) {
          std::fill(g_mono, g_mono + frames, 0.0f);
          hrtf::process(sh.slot, g_mono, dir_of(sh.spot), g_ear_l, g_ear_r);
          add_ears(o, frames);
        }
        hrtf::release(sh.slot);
        sh.slot = -1;
      }
      continue;
    }
    // A start in a later block waits (holding nothing); one in this block begins at its sample.
    ma_uint32 first = 0;
    if (sh.start_s > 0) {
      const double off = (sh.start_s - block_t) * kRate;
      if (off >= (double)frames) continue;
      ++g_scheduled;
      if (off > 0) first = (ma_uint32)off;
      else if (-off > kRate / 1000.0) g_late.add(-off * 1000.0 / kRate);   // more than a millisecond after its time
      sh.start_s = 0;
    }
    if (sh.spatial && hrtf_block && sh.slot < 0) {
      sh.slot = hrtf::claim();
      if (sh.slot < 0) { ++g_hrtf_fallbacks; sh.spatial = false; }   // all slots busy: this one pans
    }
    if (sh.slot >= 0 && !hrtf_block) { hrtf::release(sh.slot); sh.slot = -1; }   // 3D sound switched off mid-shot
    // Dark Vision's stereo: the model when chosen, and the HRTF's own fallback (no slot, odd block, no phonon).
    const bool stereo = sh.spatial && sh.slot < 0 && frames <= (ma_uint32)kMaxBlock;
    const bool ears = sh.slot >= 0 || stereo;
    if (ears) std::fill(g_mono, g_mono + frames, 0.0f);
    // The distance curve, from where the listener is this block (audio::follow moved the spot): the gain glides
    // across the block to it, as Dark Vision's voices do, so a sound walked toward grows without a step.
    float fall_to = 1.0f;
    if (sh.spot.falloff) {
      const float level = std::sqrt(std::max(0.0f, 1.0f - sh.spot.up * sh.spot.up));
      const float across = sh.spot.flat_m >= 0.0f ? sh.spot.flat_m : sh.spot.dist_m * level;
      fall_to = core::distance_gain(across / std::max(level, 0.05f));
    }
    if (sh.fall < 0.0f) sh.fall = fall_to;
    const float fall_step = (fall_to - sh.fall) / (float)(frames - first);
    float l, r; pan_gains(sh.spot.pan, l, r);
    const std::vector<float>& v = *sh.pcm;
    const float duck_to = soloing && soloed_out(sh) ? 0.0f : 1.0f;
    if (sh.hold && GetTickCount64() - sh.held_at > sh.hold_ms) sh.vol_to = 0.0f;   // nobody holds it: fade out
    if (sh.hold) sh.tone += (sh.tone_to - sh.tone) * 0.3f;   // per block: ~30 ms to settle
    const float coef = sh.hold ? tone_coef(sh.tone, kRate) : 1.0f;
    for (ma_uint32 i = first; i < frames; ++i) {
      if (sh.hold && sh.pos >= (double)v.size()) sh.pos -= (double)v.size();   // a held voice loops
      size_t k = (size_t)sh.pos;
      if (!sh.hold && k + 1 >= v.size()) { sh.dead = true; break; }
      const size_t k1 = k + 1 < v.size() ? k + 1 : 0;   // a loop's last sample runs on into its first
      sh.duck += (duck_to - sh.duck) * kGlide;
      if (duck_to == 0.0f && sh.duck < 1e-3f) { sh.dead = true; break; }   // faded out under the solo: cut
      float frac = (float)(sh.pos - (double)k);
      float x = v[k] + (v[k1] - v[k]) * frac;
      if (sh.hold) {
        sh.vol += (sh.vol_to - sh.vol) * kGlide;
        if (sh.vol_to == 0.0f && sh.vol < 1e-4f) { sh.dead = true; break; }   // faded out: ended
        sh.lp += coef * (x - sh.lp);
        sh.wobble += (sh.wobble_to - sh.wobble) * kGlide;
        x = sh.lp * (1.0f - sh.wobble * 0.5f * (1.0f - (float)std::cos(sh.trem)));
        sh.trem += 2.0 * kPi * kWobbleHz / kRate;
        if (sh.trem > 2.0 * kPi) sh.trem -= 2.0 * kPi;
      }
      sh.fall += fall_step;
      float s = x * sh.vol * sh.fall * sh.duck * bus_gain(sh.bus, i);
      sh.pos += sh.rate;
      if (ears) g_mono[i] = s;
      else { o[i * 2] += s * l; o[i * 2 + 1] += s * r; }
    }
    if (sh.slot >= 0) {
      hrtf::process(sh.slot, g_mono, dir_of(sh.spot), g_ear_l, g_ear_r);
      add_ears(o, frames);
    } else if (stereo) {
      // The listener's own frame: right is east and ahead north in the top-down mode, the camera's otherwise.
      // The sideways offset is the ground's alone. The hero's place is his body's middle, ~90 cm over the floor a
      // thing's nearest point sits on, and that height is left out of the direction (core::listener_spot): counted in
      // the offset, a door's edge 5 cm to the side and 90 cm down panned 90% to that side, and walking past its corner
      // swept it from ear to ear within a step (the user, 2026-11-13).
      float flat = sh.spot.flat_m >= 0.0f ? sh.spot.flat_m : sh.spot.dist_m * std::sqrt(std::max(0.0f, 1.0f - sh.spot.up * sh.spot.up));
      float horiz = std::hypot(sh.spot.right, sh.spot.ahead);
      float east = horiz > 1e-4f ? sh.spot.right / horiz * flat : 0.0f, north = horiz > 1e-4f ? sh.spot.ahead / horiz * flat : 1.0f;
      if (sh.spot.dist_m <= 0.0f) { east = sh.spot.pan * kPanWidthM; north = sh.spot.ahead; }   // a Spot with no distance: by direction alone
      core::SpatialCue cue = core::spatial_cue(east, north, kPanWidthM, kRate);
      std::fill(g_ear_l, g_ear_l + frames, 0.0f);
      std::fill(g_ear_r, g_ear_r + frames, 0.0f);
      sh.stereo.process(g_mono, (int)frames, cue, kRate, g_ear_l, g_ear_r);
      add_ears(o, frames);
    }
  }
  const ULONGLONG now = GetTickCount64();
  for (Loop& lp : g_loops) {
    if (lp.samples.empty()) continue;
    // Watchdog: silent unless driven. The solo leaves the wall tones playing (the user, 2026-11-17: on is always on).
    float target = now - lp.refreshed > kLoopStaleMs ? 0.0f : lp.volume * lp.gain;
    if (target <= 0.0f && lp.cur < kSilent) { lp.cur = 0; lp.pos = (lp.pos + frames) % lp.samples.size(); continue; }
    for (ma_uint32 i = 0; i < frames; ++i) {
      lp.cur += (target - lp.cur) * kGlide;
      if (lp.onset_at > 0 && target > 0 && lp.cur >= target * 0.5f) {
        g_onset.add((block_t + (double)i / kRate - lp.onset_at) * 1000.0);
        lp.onset_at = 0;
      }
      float s = lp.samples[lp.pos] * lp.cur * bus_gain(Bus::Walls, i);  // the loop's own gain, then the Walls bus (the master in it)
      if (++lp.pos >= lp.samples.size()) lp.pos = 0;  // seamless wrap
      o[i * 2] += s * lp.gl; o[i * 2 + 1] += s * lp.gr;
    }
  }
  for (Narr* n : {&g_narr_out, &g_narr}) {
    if (!n->active || !n->pcm) continue;
    const auto& v = *n->pcm;
    for (ma_uint32 i = 0; i < frames; ++i) {
      float target = n->stopping || n->paused ? 0.0f : 1.0f;
      n->cur += (target - n->cur) * kNarrFade;
      if (n->paused && n->cur < kSilent) { n->cur = 0; break; }   // hold the position
      if (n->stopping && n->cur < kSilent) { n->active = false; break; }
      if (n->pos >= v.size()) { n->ended = true; n->active = false; break; }
      float s = v[n->pos++] * n->cur * bus_gain(Bus::Narration, i) * 0.70710677f;
      o[i * 2] += s; o[i * 2 + 1] += s;
    }
  }  bool limited = false;
  for (ma_uint32 i = 0; i < frames; ++i) {
    float peak = std::max(std::abs(o[i * 2]), std::abs(o[i * 2 + 1]));
    if (peak * g_limit > kCeiling) { g_limit = kCeiling / peak; limited = true; }
    o[i * 2] *= g_limit; o[i * 2 + 1] *= g_limit;
    g_limit += (1.0f - g_limit) * kRelease;
  }
  if (limited) ++g_limited_blocks;
  std::erase_if(g_shots, [](const Shot& s) { return s.dead && s.slot < 0; });
  LARGE_INTEGER t1, fq; QueryPerformanceCounter(&t1); QueryPerformanceFrequency(&fq);
  uint64_t us = (uint64_t)((t1.QuadPart - t0.QuadPart) * 1000000 / fq.QuadPart);
  if (us > g_cb_max_us) g_cb_max_us = us;
}
}  // namespace

// Never under g_mu: uninit waits for the callback, which takes it.
static void close_device() {
  g_closing = true;
  ma_device_uninit(&g_device);
  g_closing = false;
}
// miniaudio's own thread. A stop we did not ask for is a lost device; tick() reopens it on the game thread.
static void on_notification(const ma_device_notification* n) {
  if (n->type == ma_device_notification_type_stopped && !g_closing) g_lost = true;
  if (n->type == ma_device_notification_type_rerouted) g_rerouted = true;
}

// The default output, opened and started. False (and closed again) when there is none to open.
static bool open_device() {
  ma_device_config cfg = ma_device_config_init(ma_device_type_playback);
  cfg.playback.format = ma_format_f32;
  cfg.playback.channels = 2;
  cfg.sampleRate = kRate;
  cfg.dataCallback = data_callback;
  cfg.notificationCallback = on_notification;
  cfg.periodSizeInFrames = kPeriod;   // noFixedSizedCallback stays false: every callback is exactly this long
  if (ma_device_init(nullptr, &cfg, &g_device) != MA_SUCCESS) return false;
  if (ma_device_start(&g_device) != MA_SUCCESS) { close_device(); return false; }
  // How far ahead of the ear the mixer works: WASAPI's buffer (22 ms on a 48 kHz device in low-latency shared mode).
  ma_uint32 buf = 0;
  if (g_device.pContext->backend == ma_backend_wasapi && g_device.wasapi.pAudioClientPlayback &&
      SUCCEEDED(((ma_IAudioClient*)g_device.wasapi.pAudioClientPlayback)->lpVtbl->GetBufferSize((ma_IAudioClient*)g_device.wasapi.pAudioClientPlayback, &buf)) && g_device.playback.internalSampleRate)
    g_buffer_ms = 1000.0 * buf / g_device.playback.internalSampleRate;
  log::writef("audio: device '{}' at {} Hz (mixer {} Hz), {}-frame periods, buffer {:.1f} ms", g_device.playback.name,
              g_device.playback.internalSampleRate, kRate, g_device.playback.internalPeriodSizeInFrames, g_buffer_ms);
  return true;
}

bool init() {
  if (g_inited) return g_ready;
  g_inited = true;
  { std::lock_guard lk(g_mu); g_shots.reserve(kMaxShots); }   // push_shot never reallocates under the callback's lock
  if (!open_device()) {
    log::writef("audio: no output device to open; trying again every {} s", kRetryMs / 1000);
    g_retry_logged = true;
    g_retry_at = GetTickCount64() + kRetryMs;
    return false;
  }
  g_ready = true;
  log::writef("audio: output ready ({} Hz, {}-frame periods)", kRate, kPeriod);
  return true;
}
double now_s() { return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
static double g_tick_at = 0, g_tick_gap = 1.0 / 60;
double tick_interval_s() { return std::clamp(g_tick_gap, 0.005, 0.05); }
void tick() {
  {
    const double t = now_s();
    if (g_tick_at > 0 && t - g_tick_at < 0.25) g_tick_gap += (t - g_tick_at - g_tick_gap) * 0.2;   // a pause is not a frame
    g_tick_at = t;
  }
  if (!g_inited) return;
  if (g_rerouted.exchange(false)) log::write("audio: the output moved to the new default device");
  const ULONGLONG now = GetTickCount64();
  if (g_ready && g_lost.exchange(false)) {
    log::write("audio: the output device stopped; reopening");
    g_ready = false;
    close_device();
    std::lock_guard lk(g_mu);   // what was playing then is not played late: the shots go, their HRTF slots with them
    for (Shot& sh : g_shots) if (sh.slot >= 0) hrtf::release(sh.slot);
    g_shots.clear();
    g_narr.active = false;   // the narrator stopped: the description is cut, not left waiting on a silent device
    g_narr_out = Narr{};
    g_retry_at = now;
  }
  if (g_ready || now < g_retry_at) return;
  g_retry_at = now + kRetryMs;
  if (!open_device()) {
    if (!std::exchange(g_retry_logged, true)) log::writef("audio: no output device; trying again every {} s", kRetryMs / 1000);
    return;
  }
  g_ready = true;
  g_retry_logged = false;
  log::write("audio: output open again");
}
void shutdown() {
  if (!g_inited) return;
  g_inited = false;
  if (g_ready) { g_ready = false; close_device(); }   // no callback after this: the HRTF slots can go
  hrtf::shutdown();
  std::lock_guard lk(g_mu);
  g_shots.clear();
  g_loops.clear();
  g_narr = Narr{};
  g_narr_out = Narr{};
}

// One shot into the mixer, whole, under the lock. `spatial`: heard from `at` (through the HRTF, panned without it);
// false: from no place, both ears alike.
static void push_shot(Pcm pcm, float volume, const Spot& at, Bus bus, float rate, bool spatial, bool focus = false, double start_s = 0) {
  if (!g_ready || !pcm || pcm->size() < 2 || (int)bus < 0 || bus >= Bus::Count) return;   // only the device callback drains g_shots
  std::lock_guard lk(g_mu);
  if (g_shots.size() >= kMaxShots) return;
  Shot s;
  s.focus = focus;
  s.pcm = std::move(pcm);
  s.vol = volume < 0 ? 0 : volume;
  s.rate = std::clamp(rate, 0.25f, 4.0f);
  s.bus = bus;
  s.spot = at;
  s.spatial = spatial;
  if (start_s > 0) s.start_s = std::min(start_s, now_s() + 0.5);   // a rhythm queues a frame ahead, never far
  if (g_solo && soloed_out(s)) return;   // the solo holds: only the focus starts
  g_shots.push_back(std::move(s));
}
void play(Pcm pcm, float volume, const Spot& at, Bus bus, float rate, bool focus, double start_s) { push_shot(std::move(pcm), volume, at, bus, rate, true, focus, start_s); }
void hold(int id, Pcm pcm, float volume, const Spot& at, float rate, float tone, float wobble, int hold_ms) {
  if (!g_ready || !pcm || pcm->size() < 2 || id == 0) return;
  const ULONGLONG now = GetTickCount64();
  volume = volume < 0 ? 0 : volume;
  tone = std::clamp(tone, 0.0f, 1.0f);
  wobble = std::clamp(wobble, 0.0f, 1.0f);
  std::lock_guard lk(g_mu);
  for (Shot& s : g_shots)
    if (s.hold == id && !s.dead && s.pcm == pcm && s.vol_to > 0.0f) {
      s.held_at = now;
      s.hold_ms = (ULONGLONG)std::max(hold_ms, 0);
      s.vol_to = volume;
      s.spot = at;
      s.rate = std::clamp(rate, 0.25f, 4.0f);
      s.tone_to = tone;
      s.wobble_to = wobble;
      return;
    }
  for (Shot& s : g_shots) if (s.hold == id) s.vol_to = 0.0f;   // an older one fading out, not taken back
  if (g_shots.size() >= kMaxShots) return;
  Shot s;
  s.pcm = std::move(pcm);
  s.hold = id;
  s.held_at = now;
  s.hold_ms = (ULONGLONG)std::max(hold_ms, 0);
  s.vol = 0.0f;   // it fades in
  s.vol_to = volume > 0.0f ? volume : 1e-6f;
  s.rate = std::clamp(rate, 0.25f, 4.0f);
  s.bus = Bus::Cues;
  s.spot = at;
  s.spatial = true;
  s.tone = s.tone_to = tone;
  s.wobble = s.wobble_to = wobble;
  if (g_solo && soloed_out(s)) return;
  g_shots.push_back(std::move(s));
}
void release_hold(int id) {
  std::lock_guard lk(g_mu);
  for (Shot& s : g_shots) if (s.hold == id) s.vol_to = 0.0f;
}
void solo(bool on) {
  if (g_solo.exchange(on) != on) log::writef("audio: solo {}", on ? "on" : "off");
}
int sample_rate() { return kRate; }
// A sound's pitch stays as it started (the lower pitch from behind); where it is heard from moves, and with it the
// level of a sound whose spot has `falloff`. The HRTF takes a new direction per 10 ms block and blends from the last one.
std::atomic<int> g_followed{0};
void follow(const std::function<Spot(float, float, float)>& where) {
  if (!g_ready) return;
  std::lock_guard lk(g_mu);
  int n = 0;
  for (Shot& s : g_shots) if (!s.dead && s.spot.placed) { const bool falloff = s.spot.falloff; s.spot = where(s.spot.wx, s.spot.wy, s.spot.wz); s.spot.placed = true; s.spot.falloff = falloff; ++n; }
  g_followed += n;
}
// A signal's samples, made on first use (game thread only). Null for a number that is no signal. A signal with a file
// in assets/audio/signals plays the file (the Shadow: Grim Dark's enemy ping, the user 2026-11-13); the rest, or a
// missing file, the sound made in core/sonar_cues.
static Pcm signal_pcm(int signal) {
  static Pcm made[(int)core::SignalCue::Count];
  static constexpr const char* kFile[] = {"shadow", "ambush", "layer", "reach", "spotted", "lost"};
  static_assert(std::size(kFile) == (size_t)core::SignalCue::Count, "one file name per SignalCue, in its order");
  if (signal < 0 || signal >= (int)core::SignalCue::Count) return nullptr;
  if (made[signal]) return made[signal];
  std::vector<float> file;
  const std::string path = module_dir() + "assets\\audio\\signals\\" + kFile[signal] + ".wav";
  if (GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES && decode_mono(path, file)) file = core::file_cue(std::move(file), kRate);
  if (!file.empty()) log::writef("audio: signal {} plays {} ({:.0f} ms)", kFile[signal], path, 1000.0 * file.size() / kRate);
  else file = core::signal_cue((core::SignalCue)signal, kRate);
  made[signal] = std::make_shared<const std::vector<float>>(std::move(file));
  return made[signal];
}
void signal(int signal, float volume, const Spot& at, float rate, bool focus, double start_s) { push_shot(signal_pcm(signal), volume, at, Bus::Cues, rate, true, focus, start_s); }
void signal_here(int signal, float volume, double start_s) { push_shot(signal_pcm(signal), volume, Spot{}, Bus::Cues, 1.0f, false, false, start_s); }

bool render_beep_wav(float freq, int ms, const Spot& at, const std::string& path) {
  // A test beep: sine, ~10 ms smoothing in, 5 ms fade out.
  int n = ms * kRate / 1000;
  std::vector<float> mono(n + 2400);
  float vol = 0, phase = 0, step = 2.0f * kPi * freq / kRate;
  for (size_t i = 0; i < mono.size(); ++i) {
    float target = (int)i < n - 240 ? 1.0f : 0.0f;
    vol += (target - vol) * 0.002f;
    mono[i] = std::sin(phase) * vol;
    phase += step; if (phase > 2.0f * kPi) phase -= 2.0f * kPi;
  }
  std::vector<float> l, r;
  if (!hrtf::render(mono, dir_of(at), l, r)) return false;
  FILE* f = fopen(path.c_str(), "wb");
  if (!f) return false;
  uint32_t frames = (uint32_t)l.size(), data = frames * 4, riff = 36 + data, fmt = 16, rate = kRate, byte_rate = kRate * 4;
  uint16_t pcm = 1, ch = 2, align = 4, bits = 16;
  fwrite("RIFF", 1, 4, f); fwrite(&riff, 4, 1, f); fwrite("WAVEfmt ", 1, 8, f); fwrite(&fmt, 4, 1, f);
  fwrite(&pcm, 2, 1, f); fwrite(&ch, 2, 1, f); fwrite(&rate, 4, 1, f); fwrite(&byte_rate, 4, 1, f); fwrite(&align, 2, 1, f); fwrite(&bits, 2, 1, f);
  fwrite("data", 1, 4, f); fwrite(&data, 4, 1, f);
  for (uint32_t i = 0; i < frames; ++i) {
    int16_t s[2] = {(int16_t)std::lround(std::clamp(l[i], -1.0f, 1.0f) * 32767.0f), (int16_t)std::lround(std::clamp(r[i], -1.0f, 1.0f) * 32767.0f)};
    fwrite(s, 2, 2, f);
  }
  fclose(f);
  return true;
}

bool decode_mono(const std::string& path, std::vector<float>& out) {
  ma_decoder_config dc = ma_decoder_config_init(ma_format_f32, 1, kRate);
  ma_decoder dec;
  if (ma_decoder_init_file(path.c_str(), &dc, &dec) != MA_SUCCESS) return false;
  float buf[4096];
  out.clear();
  for (;;) {
    ma_uint64 got = 0;
    ma_result r = ma_decoder_read_pcm_frames(&dec, buf, 4096, &got);
    out.insert(out.end(), buf, buf + got);
    if (r != MA_SUCCESS || got == 0) break;
  }
  ma_decoder_uninit(&dec);
  return !out.empty();
}

int narrate(std::shared_ptr<const std::vector<float>> pcm) {
  static int next_id = 0;
  std::lock_guard lk(g_mu);
  // The clip still sounding (a seek cuts one and starts the next in the same tick) fades out under the new one.
  if (g_narr.active && !g_narr.paused) { g_narr_out = g_narr; g_narr_out.stopping = true; }
  g_narr = Narr{};
  g_narr.id = ++next_id;
  g_narr.pcm = std::move(pcm);
  g_narr.cur = 1.0f;   // the clips start on silence (trimmed 10 ms before the voice): no fade-in needed
  g_narr.active = g_ready && g_narr.pcm && !g_narr.pcm->empty();
  return g_narr.id;
}
void narrate_pause(bool paused) { std::lock_guard lk(g_mu); g_narr.paused = paused; }
void narrate_stop() { std::lock_guard lk(g_mu); if (g_narr.active) g_narr.stopping = true; }
Narration narration() {
  std::lock_guard lk(g_mu);
  return {g_narr.id, g_narr.active, g_narr.paused, g_narr.ended, g_narr.pos, g_narr.pcm ? g_narr.pcm->size() : 0};
}

bool load_loop(int id, const std::string& wav_path, float pan) {
  // Decoded to mono float at the mixer rate (miniaudio resamples; the wotr files are 44.1 kHz).
  std::vector<float> samples;
  if (!decode_mono(wav_path, samples)) { log::writef("audio: cannot open loop '{}', or it decoded to nothing", wav_path); return false; }
  Loop lp{id};
  lp.samples = std::move(samples);
  pan_gains(pan, lp.gl, lp.gr);
  std::lock_guard lk(g_mu);
  std::erase_if(g_loops, [id](const Loop& l) { return l.id == id; });
  g_loops.push_back(std::move(lp));
  log::writef("audio: loop {} = '{}' ({} frames, pan {:.1f})", id, wav_path, g_loops.back().samples.size(), pan);
  return true;
}
void set_loop_volume(int id, float volume) {
  std::lock_guard lk(g_mu);
  for (Loop& l : g_loops)
    if (l.id == id) {
      const float v = volume < 0 ? 0 : volume > 1 ? 1 : volume;
      if (v > 0 && l.volume <= 0 && l.cur < kSilent) l.onset_at = now_s();   // dev: an onset from silence, timed to the mixer
      if (v <= 0) l.onset_at = 0;
      l.volume = v;
      l.refreshed = GetTickCount64();
    }
}
void set_loop_gain(int id, float gain) {
  std::lock_guard lk(g_mu);
  for (Loop& l : g_loops) if (l.id == id) l.gain = gain < 0 ? 0 : gain;
}
std::string module_dir() { return paths::dir(); }
void set_master_volume(float v) { std::lock_guard lk(g_mu); g_master = v < 0 ? 0 : v > 1 ? 1 : v; }
void set_bus_volume(Bus b, float v) {
  if ((int)b < 0 || b >= Bus::Count) return;
  std::lock_guard lk(g_mu);
  g_bus[(int)b].target = v < 0 ? 0 : v > 1 ? 1 : v;
}
void reset_stats() { std::lock_guard lk(g_mu); g_cb_max_us = 0; g_hrtf_fallbacks = 0; g_onset = {}; g_late = {}; g_scheduled = 0; }
std::string status() {
  std::lock_guard lk(g_mu);
  int loud = 0;
  for (const Loop& l : g_loops) if (l.cur >= kSilent) ++loud;
  // The held voices (a Shadow's snarl, the sight zones): each one's volume, its distance curve's gain and its place.
  std::string held;
  for (const Shot& s : g_shots)
    if (s.hold && !s.dead) {
      float l, r;
      core::SpatialCue c = core::spatial_cue(s.spot.right * std::max(s.spot.flat_m, 0.0f), s.spot.ahead * std::max(s.spot.flat_m, 0.0f), kPanWidthM, kRate);
      core::spatial_pan_gains(c.pan, l, r);
      held += std::format("hold {} vol {:.2f} falloff {} gain {:.3f} at {:.2f} m (flat {:.2f}) pan {:+.2f} left {:.3f} right {:.3f} rear {:.1f} dB\n", s.hold, s.vol,
                          s.spot.falloff, s.fall, s.spot.dist_m, s.spot.flat_m, c.pan, l, r, c.rear_shelf_db);
    }
  return held + std::format("audio ready={} master={:.2f} buses cues={:.2f} walls={:.2f} narration={:.2f} sonar={:.2f} shots={} loops={} ({} audible) limiter={:.2f} limited_blocks={}\n"
                     "hrtf {} slots {}/{} fallbacks={} air={:.1f} callback_max_us={} followed={}\n",
                     g_ready.load(), g_master, g_bus[(int)Bus::Cues].target, g_bus[(int)Bus::Walls].target, g_bus[(int)Bus::Narration].target,
                     g_bus[(int)Bus::Sonar].target, g_shots.size(), g_loops.size(), loud, g_limit, g_limited_blocks,
                     "off (stereo model)", hrtf::slots_used(), hrtf::slot_count(), g_hrtf_fallbacks,
                     hrtf::air(), g_cb_max_us, g_followed.load()) +
         std::format("latency: device buffer {:.1f} ms; tick every {:.1f} ms; wall-tone onset to half volume in the mixer avg {:.1f} max {:.1f} ms ({}); "
                     "scheduled starts {}, late {} (max {:.1f} ms)\n",
                     g_buffer_ms, tick_interval_s() * 1000.0, g_onset.n ? g_onset.sum_ms / g_onset.n : 0.0, g_onset.max_ms, g_onset.n,
                     g_scheduled, g_late.n, g_late.max_ms);
}
// Dev routes: the mixer, the process mute, an offline HRTF render.
void install_routes() {
  dev::route("/audiomute", [](const dev::Request& r, int&) {
    bool on = dev::arg(r, "on", "1") == "1";
    return std::format("audio_muted={} ok={}\n", on, audio::mute_process(on));
  }, "?on=1|0 the process's audio session");
  dev::route("/audio", [](const dev::Request& r, int&) {
    const char* names[(int)audio::Bus::Count] = {"cues", "walls", "narration", "sonar"};   // one per bus
    for (int b = 0; b < (int)audio::Bus::Count; ++b)
      if (dev::has(r, names[b])) audio::set_bus_volume((audio::Bus)b, (float)dev::arg_num(r, names[b], 1.0));
    if (dev::has(r, "air")) hrtf::set_air((float)dev::arg_num(r, "air", 10.0));
    if (dev::has(r, "reset")) audio::reset_stats();
    return audio::status();
  }, "?cues=&walls=0..1 &air=N (HRTF air absorption multiplier) &reset=1 the mod's mixer: bus volumes, voices, limiter, HRTF");
  dev::route("/audio/render", [](const dev::Request& r, int&) {
    // A beep through the HRTF, offline, from azimuth az (degrees, 90 = right), elevation elev, dist metres.
    float az = (float)dev::arg_num(r, "az", 0) * 3.14159265f / 180.0f, el = (float)dev::arg_num(r, "elev", 0) * 3.14159265f / 180.0f;
    audio::Spot s{std::sin(az) * std::cos(el), std::sin(el), std::cos(az) * std::cos(el), (float)dev::arg_num(r, "dist", 1), std::sin(az)};
    std::string out = dev::has(r, "out") ? dev::arg(r, "out") : audio::module_dir() + "hrtf_test.wav";
    bool ok = audio::render_beep_wav((float)dev::arg_num(r, "freq", 880), (int)dev::arg_int(r, "ms", 200), s, out);
    return ok ? std::format("wrote {}\n", out) : std::string("HRTF unavailable or the file could not be written\n");
  }, "?az=&elev=&dist=m&freq=&ms=&out=path a beep rendered offline through the HRTF into a stereo WAV (dev check)");
}

}  // namespace p3a::audio
