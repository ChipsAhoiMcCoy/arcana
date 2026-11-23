#pragma once
#include <string>
#include <string_view>

namespace p3a::core::lang {
// The language the mod speaks its own lines in (game text passes through in the game's language). Every line the mod
// writes is looked up by its English text in that language's tables (assets/lang/<code>/*.tsv, made with
// tools/lang.py: "English<TAB>translation" a line, \t \n \\ escaped); a line with no translation is said in English.
// Engine-free.
enum Code { En, Ja, Fr, It, De, Es, Pt, Pl, Tr, Ru, Ko, ZhHans, ZhHant, Count };
const char* code(int lang);          // "en", "zh-Hans": its tables' folder
const char* native_name(int lang);   // "English", "Español": how a menu names it, in that language
// A culture or language name as Unreal gives it ("es", "es-ES", "pt-BR", "zh-Hans", "zh-CN", "zh-TW") -> its Code,
// or -1 for one the mod has no tables for.
int from_culture(std::string_view culture);

// The folder holding <code>/*.tsv (ends in a separator). Set once, before the first `set`.
void set_root(const std::wstring& dir);
// Switches the mod's language; a language's tables are read on first use and kept (a pointer `tr` returned stays good).
void set(int lang);
int current();
inline bool english() { return current() == En; }
// Reads one table's text into a language (tests, and `set`'s loader). Returns the lines read.
int load_text(int lang, std::string_view tsv);

// The line in the current language: its translation, or `en` itself.
const char* tr(const char* en);
std::string tr(std::string_view en);
// Which of a word's plural forms goes with n in the current language, of `forms` written ("one|few|many" in Russian
// and Polish; "one|other" elsewhere).
int plural_index(long long n, int forms);

// The game's own language (its culture: the text the game shows), which a player may set apart from the mod's.
void set_game(int lang);
int game();
// Whether the game's text `shown` names a place written `en` in English: in English, or as the game's tables write it
// in the game's language (assets/lang/<code>/places.tsv: "@place:Thebel<TAB>Тевель", alternatives "|"-separated).
bool names_place(std::string_view shown, const char* en);
// Whether game text (ASCII lowercased) says the word written `en` in English ("battle"), in English or in the game's
// language (words.tsv: "@word:battle<TAB>kampf|gefecht").
bool says_word(std::string_view lowered, const char* en);
}  // namespace p3a::core::lang
