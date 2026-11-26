#pragma once

// Boxes on the field, turned about the vertical only (a hit actor's trigger, the strike's reach, a breakable's
// body), and the distances and angles the walk and the Shadow cues measure with. Unreal's units: centimetres, yaw in
// degrees. Engine-free.

namespace p3a::core {

constexpr float kPi = 3.14159265f;

struct Vec3 { float x = 0, y = 0, z = 0; };
// A box as it stands in the world: its centre, its half sizes along its own axes, and its yaw.
struct Box { Vec3 center, extent; float yaw = 0; };

float flat(const Vec3& a, const Vec3& b);    // the distance on the ground plane
float dist3(const Vec3& a, const Vec3& b);   // the distance in space
// How far apart two headings are, in degrees: 0 (the same way) to 180 (opposite).
float angle_diff(float a, float b);
// The heading of a ground offset in degrees, Unreal's yaw: 0 along +x, 90 along +y, -90 along -y.
float heading(float dx, float dy);

// `p` is inside the box grown by `grow_xy` along both of its ground axes (negative: shrunk) and by `grow_z` up and
// down.
bool box_holds(const Box& b, const Vec3& p, float grow_xy, float grow_z);
// A standing body (a capsule as the field's collision has it: `radius` around the vertical line through `p`, `half_height`
// above and below `p`) and the box share space, touching included: the box's nearest ground point to that line lies
// within `radius`, and their heights overlap. The capsule's rounded ends are taken as flat (a cylinder), a few
// centimetres generous at the box's top and bottom corners only.
bool box_meets_body(const Box& b, const Vec3& p, float radius, float half_height);
// The box swung round `pivot` (on the ground plane) until its yaw is `yaw`: where a box that rides in front of a
// character would stand if he turned to face `yaw`.
Box turned_about(const Box& b, const Vec3& pivot, float yaw);
// Two boxes share space (touching counts): the separating-axis test on the ground plane over both boxes' sides, and
// their heights overlapping.
bool boxes_meet(const Box& a, const Box& b);
// The point of the box nearest `p` (p itself when the box holds it): where a sound from a large thing comes from.
Vec3 box_nearest(const Box& b, const Vec3& p);

}  // namespace p3a::core
