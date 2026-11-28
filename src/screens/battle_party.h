#pragma once
// Quick status checks in a battle (battle_party.cpp): the number keys 1 to 4 (the controller's layer: D-pad up,
// right, down, left) step through the party slot's status, 5 (layer A) reads the navigator's SP.
namespace p3a::screens::battle_party {
bool active();          // a battle is running and its party is there: the number keys are these, not the field's
// Party slot i (0 = the leader): entering it says the name and HP, each press after it the next part (dir 1) or the
// one before (dir -1, Shift with the key).
void slot(int i, int dir = 1);
void navigator();       // the navigator's name and SP (she is never in the battle's party)
void install();         // the /battle/party dev route
}  // namespace p3a::screens::battle_party
