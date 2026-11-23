#pragma once
#include <string>

namespace p3a::language {
// The mod's language (core/lang): the Language setting's choice, or with it on "the game's language" (0), the game's
// own culture (KismetInternationalizationLibrary.GetCurrentLanguage: Steam's language for the game). A culture the mod
// has no tables for is English. Tables: assets/lang/<code>/*.tsv beside the mod.
void apply(int setting);   // the Language setting's value: 0 the game's, else core::lang::Code + 1
std::string game_culture();   // "" before the engine has one
void install();            // the dev route /lang
// Dev: P3A_CULTURE=es boots the game in that language (Steam's answer to the game, while it starts). boot_culture()
// first thing as the mod loads; install() puts Steam's answer back.
void boot_culture();
}  // namespace p3a::language
