#include "core/pad_layer.h"

namespace p3a::core {
// Each newly pressed button is an event and becomes the held one; the held one repeats while it stays down.
void PadLayer::buttons(uint32_t s, uint32_t pressed, uint64_t now, PadLayerOutput& out) {
  for (uint32_t bit = 1; bit <= 0x8000; bit <<= 1)
    if (pressed & bit) { out.add((uint16_t)bit, false, on); held = bit; repeat_at = now + 450; }
  if (held && (s & held) && now >= repeat_at) { out.add((uint16_t)held, true, on); repeat_at = now + 130; }
}

void PadLayer::filter(PadState& g, uint64_t now, const PadLayerOptions& o, PadLayerOutput& out) {
  // A trigger counts as held where the game counts it pressed (Unreal's XInput reader: past
  // XINPUT_GAMEPAD_TRIGGER_THRESHOLD, 30 of 255) and until it falls under 15 (no flicker at the threshold).
  uint32_t trig = 0;
  if (g.lt > kTriggerPress || (g.lt >= kTriggerRelease && (prev & kPadLT))) trig |= kPadLT;
  if (g.rt > kTriggerPress || (g.rt >= kTriggerRelease && (prev & kPadRT))) trig |= kPadRT;
  uint32_t s = g.buttons | trig, pressed = s & ~prev;
  hidden &= s;   // released: no longer hidden
  bool both = (s & kPadTriggers) == kPadTriggers;
  if (o.modal) {
    // A mod menu: the game sees nothing (sticks included); each new button goes to the menu. Triggers still held
    // when it closes count as the layer already open, so closing it from the layer does not announce the layer again.
    // With modal_layer (the contract's on-screen keyboard) both triggers still open the layer, so its keys (F1's
    // hints) work there; its buttons are marked as the layer's.
    if (o.modal_layer && both && !on) out.add(0, false);
    on = both;
    hidden |= s;
    buttons(s, pressed, now, out);
    prev = s;
    g = PadState{};
    return;
  }
  if (both && !on) { on = true; out.add(0, false); }
  else if (!both && on) on = false;
  if (on) {
    hidden |= s;
    buttons(s, pressed, now, out);
  } else {
    held = 0;
    // A claimed lone trigger is the caller's tap on its press (an analog trigger takes a while to travel back), hidden
    // from the game until let go. A lone trigger is never held back otherwise: the game has it at once (the user's
    // call, 2026-11-28: the trigger delay cost every trigger press more than a stray one ever did).
    if (uint32_t t = pressed & kPadTriggers & ~hidden; o.claim_taps && t && !(s & kPadTriggers & ~t)) {
      out.tap = t == kPadLT ? -1 : 1;
      hidden |= t;
    }
  }
  prev = s;
  g.buttons &= ~(uint16_t)(hidden & 0xFFFF);
  if (hidden & kPadLT) g.lt = 0;
  if (hidden & kPadRT) g.rt = 0;
}
}  // namespace p3a::core
