#include "look_text.h"
#include <cstring>

namespace p3a::core::look {
namespace {
struct Model { const char* key; const char* text; };
struct Use { int id; const char* model; };
#include "look_entries.inc"

const char* text_of(const char* key) {
  for (auto& m : kModels)
    if (std::strcmp(m.key, key) == 0) return m.text;
  return nullptr;
}
template <size_t N>
std::string find(const Use (&uses)[N], int id) {
  for (auto& u : uses)
    if (u.id == id) { const char* t = text_of(u.model); return t ? t : ""; }
  return {};
}
}  // namespace

std::string persona(int id) { return find(kPersonas, id); }
std::string enemy(int id) { return find(kEnemies, id); }
bool model_written(const char* key) { const char* t = text_of(key); return t && *t; }
int persona_ids() { return (int)(sizeof(kPersonas) / sizeof(kPersonas[0])); }
int enemy_ids() { return (int)(sizeof(kEnemies) / sizeof(kEnemies[0])); }
const char* persona_model(int i, int& id) { id = kPersonas[i].id; return kPersonas[i].model; }
const char* enemy_model(int i, int& id) { id = kEnemies[i].id; return kEnemies[i].model; }
}  // namespace p3a::core::look
