#include "doctest.h"
#include "core/look_text.h"
#include <string>

using namespace p3a::core;

TEST_CASE("every Persona and enemy id points at a written model") {
  CHECK(look::persona_ids() > 200);
  CHECK(look::enemy_ids() > 350);
  for (int i = 0; i < look::persona_ids(); ++i) {
    int id = 0;
    const char* m = look::persona_model(i, id);
    INFO("Persona ", id, " model ", m);
    CHECK(look::model_written(m));
    CHECK_FALSE(look::persona(id).empty());
  }
  for (int i = 0; i < look::enemy_ids(); ++i) {
    int id = 0;
    const char* m = look::enemy_model(i, id);
    INFO("enemy ", id, " model ", m);
    CHECK(look::model_written(m));
    CHECK_FALSE(look::enemy(id).empty());
  }
}

TEST_CASE("the game's Personas, Shadows and bosses are described") {
  // Orpheus, Pixie, Jack Frost, Thanatos, Messiah, Satan, Lucifer, the DLC's Arsene and Kaguya
  for (int id : {64, 156, 108, 128, 183, 93, 204, 300, 320}) { INFO("Persona ", id); CHECK_FALSE(look::persona(id).empty()); }
  // Cowardly Maya, Magic Hand, the Reaper, the Priestess, the Hanged Man and its statues, Nyx Avatar, Takaya, Elizabeth
  for (int id : {13, 1, 220, 370, 388, 391, 396, 350, 500}) { INFO("enemy ", id); CHECK_FALSE(look::enemy(id).empty()); }
  CHECK(look::persona(9999).empty());
  CHECK(look::enemy(-1).empty());
}

TEST_CASE("descriptions are clean prose") {
  auto check = [](const std::string& t) {
    CHECK(t.size() > 200);
    CHECK(t.find('\t') == std::string::npos);
    CHECK(t.find(",.") == std::string::npos);
    CHECK(t.find("  ") == std::string::npos);
    for (unsigned char c : t) CHECK(c < 0x80);   // plain ASCII: no curly quotes or dashes for the screen reader
  };
  for (int i = 0; i < look::persona_ids(); ++i) { int id = 0; look::persona_model(i, id); INFO("Persona ", id); check(look::persona(id)); }
  for (int i = 0; i < look::enemy_ids(); ++i) { int id = 0; look::enemy_model(i, id); INFO("enemy ", id); check(look::enemy(id)); }
}
