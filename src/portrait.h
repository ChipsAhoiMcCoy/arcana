#pragma once
#include <string>

namespace p3a::portrait {
// The area key during a conversation: what the character speaking looks like, in the outfit and pose of the portrait
// beside the line (src/core/portrait_text: the words). Empty when no portrait is up.
std::string description();   // game thread
void install();    // dev route /portrait
}  // namespace p3a::portrait
