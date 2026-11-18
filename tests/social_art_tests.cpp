#include "doctest.h"
#include "core/social_art.h"

using namespace p3a::core;

TEST_CASE("every Social Link picture is described, in the game's order") {
  CHECK(social_art::pictures() == 28);
  for (int i = 0; i < social_art::pictures(); ++i) { INFO("picture ", i); CHECK_FALSE(social_art::describe(i).empty()); }
  CHECK(social_art::describe(-1).empty());
  CHECK(social_art::describe(28).empty());
}

TEST_CASE("the picture follows the game's choice (FUN_141300ba0)") {
  CHECK(social_art::picture(1, 0, 0) == 0);    // the Fool: one collage per member joined
  CHECK(social_art::picture(1, 0, 5) == 5);
  CHECK(social_art::picture(1, 0, 9) == 5);
  CHECK(social_art::picture(2, 0, 0) == 6);    // the Magician
  CHECK(social_art::picture(5, 0, 0) == 9);    // the Emperor
  CHECK(social_art::picture(6, 0, 0) == 10);   // the Hierophant: the old man
  CHECK(social_art::picture(6, 1, 0) == 11);   // the old woman under the cursor
  CHECK(social_art::picture(7, 0, 0) == 12);   // the Lovers
  CHECK(social_art::picture(22, 0, 0) == 27);  // the Aeon
  CHECK(social_art::picture(0, 0, 0) == -1);
  CHECK(social_art::picture(23, 0, 0) == -1);
}
