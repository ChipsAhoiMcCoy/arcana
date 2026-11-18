#pragma once
#include <string>

namespace p3a::core::look {
// Written descriptions of how the Personas and the Shadows look (the area key on a focused Persona or enemy: a battle
// target, a fusion result, the compendium). Engine-free. Each was written from the game's own 3D model and its
// textures. A Persona is the game's Persona id (DatPersonaDataAsset row, BP_BtlPs<id>); an enemy the game's enemy
// id (DatEnemyNameDataAsset row, BP_BtlEm<id>). Several ids share a model (a Shadow's recoloured siblings have one
// each; a boss reusing a Shadow's model has that one).
std::string persona(int id);   // "" when the Persona has no description
std::string enemy(int id);     // "" when the enemy has none
// For the tests: every model an id points at is written, and the counts.
bool model_written(const char* key);
int persona_ids();
int enemy_ids();
const char* persona_model(int i, int& id);   // the i-th Persona row: its id and model key
const char* enemy_model(int i, int& id);
}  // namespace p3a::core::look
