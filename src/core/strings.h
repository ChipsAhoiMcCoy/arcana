#pragma once
// Every string the mod itself speaks lives here (game text passes through verbatim). Written in English; each is said
// in the mod's language (core/lang: looked up by its English text, tools/lang.py makes the tables).
#include <format>
#include <string>
#include <string_view>

#include "core/lang.h"

namespace p3a::strings {
// A line of the mod's own: the English it is written in, said in the current language. It turns into the translated
// text where it is used. Never keep the text it turned into across a change of language (a table built at startup
// keeps the Tr, not its const char*).
struct Tr {
  const char* en;
  operator const char*() const { return core::lang::tr(en); }
  const char* c_str() const { return core::lang::tr(en); }
};
inline std::string operator+(const std::string& a, Tr b) { return a + b.c_str(); }
inline std::string operator+(std::string&& a, Tr b) { return std::move(a) + b.c_str(); }
inline std::string operator+(Tr a, const std::string& b) { return a.c_str() + b; }
inline std::string operator+(Tr a, std::string&& b) { return a.c_str() + std::move(b); }
inline std::string operator+(const char* a, Tr b) { return std::string(a) + b.c_str(); }
inline std::string operator+(Tr a, const char* b) { return std::string(a.c_str()) + b; }
inline bool operator==(const std::string& a, Tr b) { return a == b.c_str(); }
inline bool operator==(std::string_view a, Tr b) { return a == std::string_view(b.c_str()); }
// A format string of the mod's own: its "{}" kept in every language.
template <class... A>
std::string fmt(Tr f, const A&... a) { return std::vformat(f.c_str(), std::make_format_args(a...)); }

std::string of(long long part, long long whole);   // kOfFormat: "2 of 5" (core/speech_text.cpp)
// A number and its word: "1 minute", "3 minutes". The plural's translation may hold every form the language needs,
// "|"-separated ("минута|минуты|минут"); core/speech_text.cpp.
std::string count(long long n, Tr one, Tr other);
std::string count(long long n, Tr word);   // a word that keeps one form in English ("3 yen")

// Key hints come in two wordings: kX() names the keyboard keys, or the controller's buttons (Xbox names) while the
// player is on a controller (input.cpp decides: whichever the game was last driven with).
bool pad_hints();
struct Hint {
  Tr keyboard;
  Tr pad;
  const char* operator()() const { return pad_hints() ? pad.c_str() : keyboard.c_str(); }
};
// Title flow
inline constexpr Tr kTitlePressAny{"Persona 3 Reload. Press any button."};
inline constexpr Tr kTitlePressAnyAstrea{"Persona 3 Reload, Episode Aigis. Press any button."};
inline constexpr Tr kTitleOpening{"Opening movie. Press any button to skip."};
// The title menu's credits (Z or L1 on the title menu).
inline constexpr Hint kCreditsRolling{"Credits. Tab twice skips them.", "Credits. The Menu button twice skips them."};
inline constexpr Hint kCreditsPaused{"Credits paused. Tab skips them, Enter resumes.", "Credits paused. The Menu button skips them, A resumes."};
inline constexpr Tr kCreditsResumed{"Credits resumed."};
inline constexpr Hint kCreditsKeys{"Enter pauses and resumes the credits. Tab, while they are paused, skips them.", "A pauses and resumes the credits. The Menu button, while they are paused, skips them."};
// The two boot notices are images: what they say, in the mod's own words.
inline constexpr Tr kTitleCaution{
    "Caution. The game shows violence, bullying and suicide, so please take care and take breaks when you need "
    "them. It is fiction: any likeness to real people, groups, events or terms is coincidence."};
inline constexpr Tr kTitlePhotosensitive{
    "Photosensitivity warning. The game has flashing screens and bright effects. Rarely, strong or flashing light "
    "or a TV screen can cause brief muscle cramps, loss of consciousness or other symptoms in some people. If that "
    "has ever happened to you, ask your doctor before playing. If it happens while you play, stop right away and "
    "get medical help."};
// The boot logos, one name each (the user's call, 2026-10-29: the longer descriptions were too much).
inline constexpr Tr kTitleLogos[] = {"Atlus", "P-Studio", "Unreal Engine"};
inline constexpr Tr kTitleMenu{"Title menu"};
inline constexpr Tr kTitleItems[] = {"New Game", "Load Game", "Config", "Change Episode"};
inline constexpr Tr kSelectDifficulty{"Select game difficulty"};
inline constexpr Tr kDifficulties[] = {"Peaceful", "Easy", "Normal", "Hard", "Merciless"};
inline constexpr Tr kContract{"Contract."};
inline constexpr Tr kFirstName{"First name"};
inline constexpr Tr kLastName{"Last name"};
inline constexpr Hint kTypeThenEnter{"Type it, then press Enter.", "D-pad chooses a key, A types it, B erases, Y capitals, X reads the name, Start confirms. B with nothing typed closes."};
// The contract's on-screen keyboard (a controller): its keys' spoken names and what it says.
inline constexpr Tr kVkSpace{"space"};
inline constexpr Tr kCapital{"capital"};   // before a capital letter: "capital Q"
inline constexpr Tr kVkDash{"dash"};
inline constexpr Tr kVkApostrophe{"apostrophe"};
inline constexpr Tr kVkPeriod{"period"};
inline constexpr Tr kVkCapitals{"Capitals"};
inline constexpr Tr kVkErase{"Erase"};
inline constexpr Tr kVkDone{"Done"};
inline constexpr Tr kRow{"row"};
inline constexpr Tr kCapitalsOn{"Capitals on"};
inline constexpr Tr kCapitalsOff{"Capitals off"};
inline constexpr Tr kKeyboardOpen{"Keyboard"};
inline constexpr Tr kBlank{"blank"};
inline constexpr Tr kNameDone{"Done"};
inline constexpr Tr kNamesMissing{"Both names are needed first."};
inline constexpr Hint kPressAnyKey{"Any key continues.", "Any button continues."};
inline constexpr Hint kNameEntryOptions{"Up and down choose a name or Done. Enter retypes a name, or signs on Done.", "Up and down choose a name or Done. A retypes a name, or signs on Done."};
inline constexpr Tr kSaveGame{"Save game"};
inline constexpr Tr kLoadGame{"Load game"};
inline constexpr Tr kCarryOverSave{"Choose the save data to carry over"};
inline constexpr Tr kSlot{"Slot"};
inline constexpr Tr kSaved{"Saved"};
inline constexpr Tr kEmpty{"empty"};
inline constexpr Tr kLevel{"level"};
inline constexpr Tr kPlayTime{"play time"};
inline constexpr Tr kClearData{"Clear data, start a new game"};   // a slot holding a finished game, as its row says
inline constexpr Tr kHoursAnd{"hours"};
inline constexpr Tr kMinutes{"minutes"};
inline constexpr Tr kHour{"hour"};
inline constexpr Tr kMinute{"minute"};
inline constexpr Tr kCamp{"Menu"};
inline constexpr Tr kCampItems[] = {"Skill", "Item", "Equip", "Persona", "Stats", "Quest", "Social Link", "Calendar", "System"};
inline constexpr Tr kCampHelp[] = {"Use a Skill", "View or use items", "View or change equipment", "View or change Personas",
                                            "View stats or organize the party", "View requests", "View Social Links", "View the calendar",
                                            "View settings"};
// Calendar: the part-time jobs by ArbeitInfo HelpMSGLabel (their names are images; the places' names as the game's
// dialogue writes them), and when each takes work (EArbeitOrderableTime: 1 afternoon, 2 evening, 3 both).
inline constexpr Tr kJobs[] = {"Chagall Caf\xC3\xA9", "Be Blue V", "Screen Shot"};
inline constexpr Tr kJobTimes[] = {"", "daytime", "evening", "daytime or evening"};
inline constexpr Tr kJob{"Part-time job"};
inline constexpr Tr kToday{"today"};  // the calendar's current day
// The day change's moon (ECldMoonAge 0..29: 0 new, 14 full, as the game's full-moon nights).
inline constexpr Tr kMoonPhases[] = {"New moon", "Waxing crescent moon", "First quarter moon", "Waxing gibbous moon", "Full moon",
                                              "Waning gibbous moon", "Last quarter moon", "Waning crescent moon"};
inline constexpr Tr kGot{"Got"};
// Whole sentences with the game's words in them, so each language puts the pieces in its own order:
inline constexpr Tr kGotFmt{"Got {}"};                 // "Got Bead x3, Medicine"
inline constexpr Tr kCountFmt{"{} x{}"};               // an item and how many: "Bead x3"
inline constexpr Tr kHitOnFmt{"{} on {}"};             // a hit's word and whom: "Weak on Junpei"
inline constexpr Tr kUseOnFmt{"Use {} on {}?"};        // "Use Agi on all enemies?"
inline constexpr Tr kUseOnSideFmt{"Use on {}?"};       // "Use on all allies?"
inline constexpr Tr kNoneOfFmt{"No {}"};               // "No Shadows": a category key with nothing in its category
inline constexpr Tr kChooseMoreFmt{"Choose {} more"};  // Shuffle Time: "Choose 1 more"
inline constexpr Tr kWouldBecomeFmt{"{} would become {}"};   // "Agi would become Agilao"
inline constexpr Tr kRankUpFmt{"{} up to rank {}"};    // a social stat: "Charm up to rank 3"
inline constexpr Tr kStatUpFmt{"{} up"};               // "Charm up"
inline constexpr Tr kUpByFmt{"up {}"};                 // a Persona stat's rise: "St 12, up 2"
inline constexpr Tr kGoesBackForFmt{"{} goes back for {}"};   // "Shift+1 goes back for Exits: ..."
inline constexpr Tr kTimes{"times"};   // a pickup's count: "Got Bead times 3"
inline constexpr Tr kItemNumber{"item"};   // an item with no known name: "item 16387"
inline constexpr Tr kSpent{"Spent"};
inline constexpr Hint kGetItemClose{"Space closes it.", "A closes it."};
inline constexpr Hint kMoviePaused{"Movie paused. Tab skips it, Enter resumes.", "Movie paused. The Menu button skips it, A resumes."};
inline constexpr Tr kMovieResumed{"Resumed"};
inline constexpr Tr kCredits{"Credits"};
inline constexpr Hint kMovieKeys{"Enter pauses and resumes the movie. Tab, while it is paused, skips it.", "A pauses and resumes the movie. The Menu button, while it is paused, skips it."};
inline constexpr Hint kOpeningKeys{"Any key skips the movie.", "Any button skips the movie."};
inline constexpr Hint kMoviePlaying{"Movie playing. Enter pauses, Tab twice skips it.", "Movie playing. A pauses, the Menu button twice skips it."};
inline constexpr Tr kTownMap{"Town map"};
inline constexpr Tr kTownMapPlaces[] = {"Gekkoukan High School", "Student Dormitory", "Paulownia Mall", "Port Island Station",
                                                 "Iwatodai Station Strip Mall", "Naganaki Shrine"};
inline constexpr Hint kFastTravelKeys{"Up and down arrows choose, Space goes, Tab zooms the map, Escape closes.", "Up and down choose, A goes, Y zooms the map, B closes."};
// The town map's entrance list: cancel goes back to the map (FUN_141454640 case 5).
inline constexpr Hint kEntranceKeys{"Up and down arrows choose, Space goes, F town info, Escape back to the map.", "Up and down choose, A goes, X town info, B back to the map."};
inline constexpr Tr kMail{"Mail"};
inline constexpr Tr kMailNew{"new"};
inline constexpr Tr kMailEmpty{"No messages"};
inline constexpr Hint kMailKeys{"Up and down arrows choose, Space reads, Escape closes.", "Up and down choose, A reads, B closes."};
// An open text (FUN_141475cb0 case 5): Space replies to one that takes a reply, else goes back like cancel.
inline constexpr Hint kMailOpenKeys{"Space replies when the text takes a reply, otherwise goes back; Escape goes back.", "A replies when the text takes a reply, otherwise goes back; B goes back."};
inline constexpr Tr kTownMapWhere{"Where should I go?"};   // the game's own entrance-list title, matched
inline constexpr Tr kAreaMap{"Area map"};
// Tartarus' map before the floor's stairs, teleporter, return device or Monad door is found: no shortcut to take yet.
inline constexpr Tr kNoShortcuts{"No shortcuts found yet. Find the stairs, a teleporter or a return device to travel to it from here."};
inline constexpr Hint kAreaMapKeys{"Tab zooms, Escape closes.", "Y zooms, B closes."};
inline constexpr Hint kTownMapHelp{"Up and down arrows choose, Space opens its entrances, F town info, Escape closes.",
                                   "The D-pad goes through the list, the stick moves on the map, A opens its entrances, X town info, B closes."};
inline constexpr Tr kSocialStats[] = {"Academics", "Charm", "Courage"};
inline constexpr Tr kRank{"rank"};
inline constexpr Tr kRankUp{"up to rank"};
inline constexpr Tr kStatUp{"up"};
inline constexpr Tr kStatsUp{"Stats up."};
inline constexpr Hint kSpaceContinues{"Space continues.", "A continues."};
inline constexpr Hint kGameOverKeys{"Space skips to the choices.", "A skips to the choices."};
inline constexpr Tr kGameOver{"Game Over"};   // the game's own words, when its message file is not loaded
inline constexpr Hint kResultKeys{"The up and down arrows go through the results, Space continues.", "Up and down go through the results, A continues."};
// Battle
inline constexpr Tr kBattle{"Battle"};
inline constexpr Tr kHP{"HP"};
inline constexpr Tr kSP{"SP"};
inline constexpr Tr kOf{"of"};
// A count against its whole: "2 of 5" (a position), "HP 30 of 45". strings::of(2, 5) says it in the language's order.
inline constexpr Tr kOfFormat{"{} of {}"};
// Punctuation named where a line is nothing else (core::speakable): a screen reader says nothing for "...".
inline constexpr Tr kPunctEllipsis{"ellipsis"};
inline constexpr Tr kPunctQuestion{"question mark"};
inline constexpr Tr kPunctExclamation{"exclamation mark"};
inline constexpr Tr kPunctPeriod{"period"};
inline constexpr Tr kPunctComma{"comma"};
inline constexpr Tr kPunctDash{"dash"};
inline constexpr Tr kPunctTilde{"tilde"};
inline constexpr Tr kTarget{"Target"};
inline constexpr Tr kSkills{"Skills"};
inline constexpr Tr kItems{"Items"};
inline constexpr Tr kChooseTarget{"Choose target"};
// A skill or item that takes a whole side at once: a question, "Use Mazio Gem on all enemies?" with its buttons.
inline constexpr Tr kUse{"Use"};
inline constexpr Tr kAllEnemies{"all enemies"};
inline constexpr Tr kAllAllies{"all allies"};
inline constexpr Tr kAllUnits{"everyone"};
inline constexpr Hint kAllTargetsKeys{"Space to confirm, Escape to cancel.", "A to confirm, B to cancel."};
// EBtlDataAnalyze 0..6: normal, null, repel, drain, weak, resist, unknown
inline constexpr Tr kAttrNames[] = {"Slash", "Strike", "Pierce", "Fire", "Ice", "Elec", "Wind", "Light", "Dark"};
inline constexpr Tr kAffinity[] = {"", "nulls", "repels", "drains", "weak to", "resists", ""};
// Analyze's panel (core::analyze_affinities): each affinity a sentence of its own.
inline constexpr Tr kAffinityCap[] = {"", "Nulls", "Repels", "Drains", "Weak to", "Resists", ""};
inline constexpr Tr kAffinitiesUnknown{"Affinities unknown"};
// An affinity on its own line, as the icon row shows it: "Fire: weak", "Slash: normal", "Dark: unknown".
inline constexpr Tr kAffinityShort[] = {"normal", "null", "repel", "drain", "weak", "resist", "unknown"};
inline constexpr Tr kNoAffinitiesCap{"No weaknesses or resistances"};
inline constexpr Tr kUnknownCap{"Unknown"};
inline constexpr Tr kNormalCap{"Normal"};
inline constexpr Tr kRestNormal{"The rest normal"};
inline constexpr Tr kRestUnknown{"The rest unknown"};
inline constexpr Tr kDamage{"damage"};
inline constexpr Tr kHealed{"healed"};
inline constexpr Tr kDefeated{"defeated"};
inline constexpr Tr kKnockedOut{"knocked out"};
inline constexpr Tr kVictory{"Victory"};
inline constexpr Tr kExp{"EXP"};
inline constexpr Tr kYen{"yen"};
// Before a script's price question ("Buy / Don't buy"): "Price 2980 yen, you have 4800 yen".
inline constexpr Tr kPrice{"Price"};
inline constexpr Tr kLevelUp{"Level up!"};
// EBtlDataBadStatus 0..13
inline constexpr Tr kBadStatus[] = {"is dizzy", "is charmed", "is distressed", "panics", "is afraid", "is enraged", "is frozen", "is shocked",
                                            "is poisoned", "", "", "", "", "is down"};
// A unit's ailments as they stand (EBtlDataBadStatus; empty = not said): on focus and in the details.
inline constexpr Tr kAilments[] = {"Dizzy", "Charmed", "Distressed", "Panicked", "Afraid", "Enraged", "Frozen", "Shocked",
                                            "Poisoned", "Orgia Mode", "Overheated", "Time bomb", "", "Down"};
inline constexpr Tr kNoAilments{"No ailments"};
inline constexpr Tr kNoEffects{"No buffs or debuffs"};
inline constexpr Tr kGuarding{"Guarding"};
inline constexpr Tr kUpTo{"up to"};
inline constexpr Tr kTurn{"turn"};
inline constexpr Tr kTurns{"turns"};
// A battle's countdown (the monorail's, BTL_COUNTDOWN_START): "Time left: 30 minutes", "29 minutes 12 seconds left".
inline constexpr Tr kTimeLeftStart{"Time left:"};
inline constexpr Tr kTimeLeft{"left"};
inline constexpr Tr kSecond{"second"};
inline constexpr Tr kSeconds{"seconds"};
inline constexpr Tr kPersonaWord{"Persona"};
inline constexpr Tr kTheurgyCharge{"Theurgy gauge"};
inline constexpr Hint kDetailKeys{"Control and the up and down arrows read the details of what is in focus.", "The right stick, up and down, reads the details of what is in focus."};
inline constexpr Tr kOneMore{"1 More!"};
inline constexpr Tr kRushOn{"Rush"};
inline constexpr Tr kRushOff{"Rush off"};
// The word beside a hit's number (BP_BtlGuiDamage2 types 5 to 9), then "on" and the unit unless the player chose it.
inline constexpr Tr kHitWords[] = {"Weak", "Critical", "Resist", "Miss", "Block"};
inline constexpr Tr kPersonaStatus{"Persona status"};
inline constexpr Tr kLearnSkill{"Learn"};
inline constexpr Tr kNewSkill{"New skill"};
inline constexpr Tr kNextSkill{"Next skill"};
inline constexpr Tr kLearned{"Learned"};
inline constexpr Tr kWouldBecome{"would become"};   // a skill change offered after a level up: "Agi would become Agilao"
inline constexpr Hint kCBack{"Escape goes back.", "B goes back."};
inline constexpr Tr kEmptySlot{"Empty slot"};
// A level up (after a battle, or a fusion's bonus): the Persona is fixed; only a skill card's page switches Persona.
inline constexpr Hint kLearnLevelUpKeys{"Space learns. When asked to forget one, the arrows move over the slots, two columns of four; Escape goes back.", "A learns. When asked to forget one, the D-pad moves over the slots, two columns of four; B goes back."};
inline constexpr Hint kLearnSkillKeys{"Q and E switch Persona, Space learns. When asked to forget one, the arrows move over the slots, two columns of four; Escape goes back.", "LB and RB switch Persona, A learns. When asked to forget one, the D-pad moves over the slots, two columns of four; B goes back."};
inline constexpr Tr kShuffleTime{"Shuffle Time"};
inline constexpr Hint kShuffleKeys{"Left and right arrows choose a card, Space takes it.", "Left and right choose a card, A takes it."};
inline constexpr Tr kChoose{"choose"};
inline constexpr Tr kMore{"more"};                   // "choose 1 more"
inline constexpr Tr kArcanaBurst{"Arcana Burst"};
inline constexpr Tr kPersonaOverstock{"Persona overstock. Choose a Persona to release"};
inline constexpr Tr kGain{"Gain"};                   // the overstock list's new Persona: "Gain: Apsaras, ..."
// The overstock's status page (F): Space releases the Persona shown, Q / E go through the list (FUN_141011540).
inline constexpr Hint kOverstockPageKeys{"Up and down arrows go through the lines, Tab and Shift Tab jump between sections, Q and E switch Persona, Space releases it, Escape back to the list.", "Up and down go through the lines, RT and LT jump between sections, LB and RB switch Persona, A releases it, B back to the list."};
inline constexpr Hint kOverstockKeys{"Up and down arrows choose a Persona, Space releases it, F shows its stats.",
                                     "Up and down choose a Persona, A releases it, X shows its stats."};
inline constexpr Hint kSkillKeys{"Space confirms, Q and E change Persona, F Persona stats, Escape back.", "A confirms, LB and RB change Persona, X Persona stats, B back."};
inline constexpr Hint kKeyAttack{"Space attack", "A attack"};
inline constexpr Hint kKeySkills{"E skills", "Y skills"};
inline constexpr Hint kKeyItems{"R items", "X items"};
inline constexpr Hint kKeyGuard{"C guard", "B guard"};
inline constexpr Hint kKeyAnalyze{"Q analyze", "LB analyze"};
// The battle wheel's keys (battle.cpp, F1)
inline constexpr Hint kKeyTactics{"W tactics", "D-pad up tactics"};
inline constexpr Hint kKeySurvey{"S survey", "D-pad down survey"};
inline constexpr Hint kKeyRush{"Tab rush", "Menu button rush"};
inline constexpr Hint kKeyTheurgy{"T Theurgy", "RT Theurgy"};
inline constexpr Hint kKeyShift{"B shift", "LT shift"};
inline constexpr Hint kKeyAssist{"F assist", "RB assist"};
inline constexpr Hint kChangeTargetKeys{"A and D or the left and right arrows change target.", "Left and right change target."};
inline constexpr Hint kAnalyzeKeys{"Up and down arrows go through the lines, Tab and Shift Tab jump between sections, Q and E or A and D change target, Escape closes.",
                                   "Up and down go through the lines, RT and LT jump between sections, LB and RB change target, B closes."};
inline constexpr Hint kTargetKeys{"Left and right arrows choose a target, Space confirms, Q analyzes it, Escape back.", "Left and right choose a target, A confirms, LB analyzes it, B back."};
inline constexpr Hint kTheurgyKeys{"Left and right arrows choose, Space uses it, Escape back.", "Left and right choose, A uses it, B back."};
inline constexpr Hint kShiftKeys{"Left and right arrows choose who takes the turn, Space passes it, F Persona stats, Escape back.", "Left and right choose who takes the turn, A passes it, X Persona stats, B back."};
inline constexpr Hint kSurveyKeys{"Up and down arrows go through everyone, Space analyzes a foe or opens a member's status, Escape back.", "Up and down go through everyone, A analyzes a foe or opens a member's status, B back."};
inline constexpr Hint kAllOutKeys{"Space to attack, Escape to hold back.", "A to attack, B to hold back."};
inline constexpr Hint kGuardKeys{"Space to guard, Escape to cancel.", "A to guard, B to cancel."};
inline constexpr Tr kAnalyze{"Analyze"};
// Analyze's other panels, in the detail buffer: "Arcana Magician", "Skills: Agi, Rakunda", "Drops: Mask of Cruelty".
inline constexpr Tr kArcanaWord{"Arcana"};
inline constexpr Tr kDrops{"Drops"};
inline constexpr Tr kMaxWord{"Max"};              // "Max HP 83, max SP 20"
inline constexpr Tr kMaxWordLower{"max"};
inline constexpr Tr kAttackType{"Attack type"};   // then the game's name for it: "Attack type Strike Attack"
// What Analyze still hides, said where its panel would be (the game draws "??" and "UNKNOWN").
inline constexpr Tr kStatusUnknown{"Level, HP and SP unknown"};
inline constexpr Tr kSkillsAttackUnknown{"Skills and attack type unknown"};
inline constexpr Tr kSkillsUnknown{"Skills unknown"};
inline constexpr Tr kAttackTypeUnknown{"Attack type unknown"};
inline constexpr Tr kLevelCap{"Level"};
inline constexpr Tr kSkillAttackTitle{"Skill and attack type"};   // the panel's own heading, "SKILL & ATTACK TYPE"
inline constexpr Tr kUnknownCapLine{"Unknown"};
inline constexpr Tr kSurveyTitle{"Survey"};
inline constexpr Tr kAllOutTitle{"All-Out Attack?"};
inline constexpr Tr kGuardTitle{"Guard?"};
// Said with a turn's line and after "1 More!", without their keys: F1 names those (kKeyTheurgy, kKeyShift).
// Who moves first, as the splash at a battle's start shows it (its pictures: S.E.E.S. / Shadow, Advantage).
inline constexpr Tr kAdvantageParty{"S.E.E.S. advantage"};
inline constexpr Tr kAdvantageEnemy{"Shadow advantage"};
// The wheel's four main commands by name, for the turn line when the game has greyed some out ("Attack, Items, Guard
// unavailable"): the wheel's slots 0 attack, 2 Persona, 3 item, 1 guard.
inline constexpr Tr kWheelCommands[] = {"Attack", "Skills", "Items", "Guard"};
inline constexpr Tr kTheurgyReadyWords{"Theurgy ready"};
inline constexpr Tr kShiftAvailableWords{"Shift available"};
// A shop's quantity as it opens, before the number; its keys are kHowMany's (F1).
inline constexpr Tr kHowManyWords{"How many?"};
// An item found more than once after a battle, a std::format string: the word, the item, how many ("Got Bead x3").
inline constexpr Tr kTacticsTitle{"Tactics. Give an order?"};
inline constexpr Tr kTacticsOrder{"Order"};
inline constexpr Tr kTacticsEscape{"Escape"};
inline constexpr Tr kTacticsWho{"Whose orders?"};
inline constexpr Tr kTacticsAll{"Everyone"};
inline constexpr Tr kTacticsWhich{"Which order?"};
inline constexpr Tr kArcana[] = {"", "Fool", "Magician", "Priestess", "Empress", "Emperor", "Hierophant", "Lovers", "Chariot",
                                          "Justice", "Hermit", "Fortune", "Strength", "Hanged Man", "Death", "Temperance", "Devil",
                                          "Tower", "Star", "Moon", "Sun", "Judgement", "Aeon"};
inline constexpr Tr kSocialLinks{"Social Links"};
inline constexpr Tr kNoSocialLinks{"No Social Links yet"};
inline constexpr Tr kNewSocialLink{"New Social Link"};
inline constexpr Tr kSocialLinkUp{"Social Link rank up"};
inline constexpr Tr kSocialLinkMaxed{"Social Link at max rank"};
inline constexpr Tr kSocialLink{"Social Link"};
inline constexpr Tr kUnknownArcana{"Unknown Arcana"};   // a Social Link partner before the link is formed
inline constexpr Tr kSocialLinkReversed{"Social Link reversed"};
inline constexpr Tr kSocialLinkRestored{"Social Link restored"};
inline constexpr Tr kRankMax{"MAX"};
inline constexpr Tr kReversed{"reversed"};
inline constexpr Tr kReadyToRankUp{"ready to rank up"};
inline constexpr Tr kBondUp{"Bond deepened"};
inline constexpr Tr kPoints{"points"};
inline constexpr Tr kShop{"Shop"};
inline constexpr Tr kBuy{"Buy"};
inline constexpr Tr kQuit{"Quit"};
inline constexpr Tr kEquip{"Equip"};
inline constexpr Tr kDontEquip{"Don't Equip"};
inline constexpr Tr kWeaponShopMenu[] = {"Buy Weapon", "Buy Armor", "Buy Footwear", "Buy Accessory", "Sell Item"};
inline constexpr Tr kOwned{"owned"};
inline constexpr Tr kAntiqueShop{"Mayoido Antiques"};
inline constexpr Tr kAntiqueMenu[] = {"Fuse Equipment", "Trade Card", "Trade Item"};
inline constexpr Tr kNeeds{"needs"};
inline constexpr Tr kYouHave{"you have"};
inline constexpr Hint kHowMany{"How many? Up and down change it by one, left and right by ten, Space confirms, Escape back.",
                               "How many? Up and down change it by one, left and right by ten, A confirms, B back."};
inline constexpr Hint kShopListBackKeys{"Up and down arrows choose, Space buys, Escape back.", "Up and down choose, A buys, B back."};
inline constexpr Hint kShopListKeys{"Up and down arrows choose, Space buys, Escape leaves.", "Up and down choose, A buys, B leaves."};
inline constexpr Hint kShopTopKeys{"Up and down arrows choose, Space opens, Escape leaves.", "Up and down choose, A opens, B leaves."};
inline constexpr Hint kShopWeaponKeys{"Up and down arrows choose, Space buys, Q and E switch member, Escape back.", "Up and down choose, A buys, LB and RB switch member, B back."};
inline constexpr Hint kShopSellKeys{"Up and down arrows choose, Space sells, Q and E switch category, Escape back.", "Up and down choose, A sells, LB and RB switch category, B back."};
inline constexpr Hint kShopTradeKeys{"Up and down arrows choose, Space trades, Escape back.", "Up and down choose, A trades, B back."};
// The antique shop's fusion list (state 0x11, FUN_141400750) and its who-can-equip view (F: 0x12, FUN_141400430).
inline constexpr Hint kShopFuseKeys{"Up and down arrows choose, Space fuses, F shows who can equip it, Escape back.", "Up and down choose, A fuses, X shows who can equip it, B back."};
inline constexpr Hint kShopFuseDetailKeys{"Up and down arrows choose, Q and E switch between members who can equip it, Space fuses, F or Escape back to the list.", "Up and down choose, LB and RB switch between members who can equip it, A fuses, X or B back to the list."};
// A buy list's second view (F: state 8, FUN_1413f1250): the same list, Space buys.
inline constexpr Hint kShopDetailKeys{"Up and down arrows choose, Space buys, F or Escape back to the list.", "Up and down choose, A buys, X or B back to the list."};
inline constexpr Hint kShopDetailWeaponKeys{"Up and down arrows choose, Q and E switch member, Space buys, F or Escape back to the list.", "Up and down choose, LB and RB switch member, A buys, X or B back to the list."};
inline constexpr Hint kShopYesNoKeys{"Left and right arrows choose, Space confirms.", "Left and right choose, A confirms."};
inline constexpr Tr kAttack{"attack"};
inline constexpr Tr kAccuracy{"accuracy"};
inline constexpr Tr kDefence{"defense"};
inline constexpr Tr kEvasion{"evasion"};
inline constexpr Tr kSystemItems[] = {"Tutorial", "Config", "Dictionary", "Load Data", "Save Data", "Rewind", "Return to Title"};
inline constexpr Tr kTutorials{"Tutorials"};
inline constexpr Tr kTutorialTabs[5] = {"Battle", "Dungeon", "Daily Life", "Fusion", "System"};   // drawn as pictures
inline constexpr Tr kNoMessage{"No message"};
inline constexpr Tr kAKey{"a key"};
inline constexpr Hint kYesNoHint{"Space for yes, C for no.", "A for yes, B for no."};
inline constexpr Tr kThinking{"Thinking"};
// The buttons a message page draws as icons (tutorials), by the game's icon id: the key on the keyboard (the game's
// default) and the controller's button. The keyboard has other keys for some of them by place: in battle, and in the
// field where the sentence around the icon speaks of the menu, the map or recovering.
struct IconKey { int id; Tr keyboard; Tr pad; };
inline constexpr IconKey kIconKeys[] = {
  {104, "U", "D-pad up"}, {105, "O", "D-pad down"}, {108, "H", "Menu"}, {109, "N", "View"}, {110, "C", "B"}, {111, "Ctrl", "X"},
  {112, "E", "Y"}, {113, "Space", "A"},
  {114, "Q", "LB"}, {115, "B", "LT"}, {117, "E", "RB"}, {118, "Shift", "RT"}, {119, "R", "the right stick button"},
  {121, "I, J, K and L", "the right stick"}};
inline constexpr Tr kIconUpBattle{"W"};       // 104 in battle
inline constexpr Tr kIconDownBattle{"S"};     // 105 in battle
inline constexpr Tr kIconMenuField{"Tab"};    // 112 in the field: the menu
inline constexpr Tr kIconMapField{"M"};       // 114 in the field: the map
inline constexpr Tr kIconRecoverField{"Y"};   // 117 in the field: Auto-Recover
// A battle's own keys for the controller's buttons, where the sentence around the icon speaks of battle (the game draws
// these on its tutorials even when they are read from the Tutorial list, outside battle; checked against its glyphs,
// 2026-11-15): Rush, Assist, Theurgy, Items.
inline constexpr Tr kIconRushBattle{"Tab"};   // 108 (Menu)
inline constexpr Tr kIconAssistBattle{"F"};   // 117 (RB) for an Assist; Q / E for Personas stay E
inline constexpr Tr kIconTheurgyBattle{"T"};  // 118 (RT)
inline constexpr Tr kIconItemsBattle{"R"};    // 111 (X) in battle; the field's strike is Ctrl
inline constexpr Tr kKeySpace{"Space"};       // the key configuration's Space
// The punctuation keys by name (core::punct_key_name), as the README names them.
inline constexpr Tr kKeySemicolon{"Semicolon"};
inline constexpr Tr kKeyEquals{"Equals"};
inline constexpr Tr kKeyComma{"Comma"};
inline constexpr Tr kKeyMinus{"Minus"};
inline constexpr Tr kKeyPeriod{"Period"};
inline constexpr Tr kKeySlash{"Slash"};
inline constexpr Tr kKeyGrave{"Grave accent"};
inline constexpr Tr kKeyLeftBracket{"Left bracket"};
inline constexpr Tr kKeyBackslash{"Backslash"};
inline constexpr Tr kKeyRightBracket{"Right bracket"};
inline constexpr Tr kKeyApostrophe{"Apostrophe"};
inline constexpr Tr kTitleScreen{"Title screen"};
inline constexpr Hint kTutorialKeys{"Q and E turn the pages, Space goes on.", "LB and RB turn the pages, A goes on."};
inline constexpr Hint kDialogueKeys{"Conversation keys: Space next, B log, Shift auto, Tab fast-forwards.",
                                    "Conversation keys: A next, L3 log, X auto, Menu button fast-forwards."};
inline constexpr Hint kFieldKeys{"Field keys: Space checks and talks, Tab menu, M map, B log, Ctrl messages or attack, Shift dash, hold Alt to walk, H saves.",
                                 "Field keys: A checks and talks, Y menu, LB map, L3 log, X messages or attack, RT dash, Menu button saves."};
// Added to the field's keys on a Tartarus floor. Auto-Recover's button is the one its tutorial draws (icon 117).
// N (View) is the game's Navi: the navigator's support skills (Jamming, Escape Route, Tartarus Search; tutorials
// Dungeon 24 to 29). "N Navi" alone left players asking what it does (2026-11-15).
inline constexpr Hint kTartarusKeys{"In Tartarus: Y Auto-Recover, N the navigator's support skills, such as Escape Route.",
                                    "In Tartarus: RB Auto-Recover, View the navigator's support skills, such as Escape Route."};
// The help keys (F1 = this screen's keys, Shift+F1 = the mod's own keys, F2 its settings; on a controller, the mod
// layer's Menu, and View for the settings, whose last row reads the keys).
// Every {name} is a binding's key now (keys::fill): the player may have moved it.
inline constexpr Hint kModKeysHint{"{help.mod} lists the mod's keys, {settings} opens its settings, where Mod keys changes them.", "Both triggers and View open the mod's settings; Mod keys there lists the mod's keys."};
inline constexpr Tr kNoKeys{"No keys to tell here."};
inline constexpr Tr kModKeys{"Mod keys"};
inline constexpr Tr kPadLayer{"Hold both triggers, then"};
// The top-down mode's right stick, after the layer's buttons in the controller's list of mod keys and in F1's field keys.
inline constexpr Tr kPadScanKeys{"Without the triggers, in top-down mode: the right stick finds the nearest point of interest that way; RT while it is on one walks there and uses it."};
// F1 in the field: the walk that uses its point (Shift+Period; RT on the right stick's point in top-down mode).
inline constexpr Tr kFieldWalkUseKeys{"{nav.walk.period} walks to the selected point of interest, {nav.use} walks there and uses it; {poi.nearest} selects the nearest one, then the next nearest, {poi.nearest.prev} goes back; {poi.again} says the selected one again."};
// The mod settings menu (settings.cpp)
inline constexpr Tr kModSettings{"Mod settings"};
inline constexpr Tr kModSettingsClosed{"Mod settings closed"};
inline constexpr Hint kModSettingsKeys{"Up and down arrows choose, Tab and Shift+Tab change category, left and right arrows change, Space changes, reads or plays, Escape closes.",
                                       "Up and down choose, LB and RB change category, left and right change, A changes, reads or plays, B closes."};
// Its categories, in order.
inline constexpr Tr kCatExploring{"Exploring"};
inline constexpr Tr kCatSonar{"Sonar"};
inline constexpr Tr kCatSound{"Sound"};
inline constexpr Tr kCatVolume{"Volume"};
inline constexpr Tr kCatDialogue{"Dialogue"};
inline constexpr Tr kCatDescription{"Audio description"};
inline constexpr Tr kCatControls{"Controls and help"};
// The Language setting (language.cpp): the mod's own lines in another language. The languages are named in their own
// language (core/lang).
inline constexpr Tr kCatLanguage{"Language"};
inline constexpr Tr kSetLanguage{"Language of the mod"};
inline constexpr Tr kHelpLanguage{"The language of everything the mod says itself: menus, hints and descriptions. The game's language follows the game. In any language but English, descriptions of movies and scenes are read by your screen reader: the narrator's voice speaks English only."};
inline constexpr Tr kLangGame{"The game's language"};
inline constexpr Tr kCatSoundTest{"Sound test"};
// What each setting does: read with its row, after the position.
inline constexpr Tr kHelpWallTones{"A tone for each wall near you: ahead, behind, left and right. Each grows louder as the wall gets closer. They play all the time, only while you move, or not at all."};
inline constexpr Tr kHelpSonar{"Every point of interest near you repeats its own sound from where it is, faster and louder the closer it is. {sonar} also switches it."};
inline constexpr Tr kHelpSonarScope{"Which points the sonar plays: everything nearby, only the category the points of interest list is on, or only the point you selected there, at any distance."};
inline constexpr Tr kHelpSonarRange{"How far away a thing can be and still sound."};
inline constexpr Tr kHelpSonarKind{"Whether this kind of thing sounds. Changing it plays its sound."};
inline constexpr Tr kHelpSonarVolume{"How loud the sonar's sounds are. Changing it plays one."};
inline constexpr Tr kHelpShadowSight{"In Tartarus: each nearby Shadow's sight sizzles from its edge nearest you, louder as that edge comes closer. Step into it and the Shadow notices you. A muffled hum means a Shadow would see you if a wall were not in its way."};
inline constexpr Tr kHelpSightRange{"How far from the edge of a Shadow's sight you start to hear it."};
inline constexpr Tr kHelpShadowAlerts{"In Tartarus: the nearest Shadow's steady snarl, muffled and wobbling when its back is to you, the note when one loses you, the ring when your strike will reach, and whether a close Shadow faces you."};
inline constexpr Tr kHelpTopDown{"While you walk freely, the camera stays facing north and every sound, the game's and the mod's, is heard from you as if from above: north ahead, east to your right. Up walks north. The right stick scans a direction. Off, the camera turns as before."};
inline constexpr Tr kHelpTurnedRooms{"In top-down exploration, where the game moves you into a room by a jump that turns you, such as the back alley to the Velvet Room, that room's north is turned so the way you walked in stays up, and down leads back out. Off, north is the map's north everywhere."};
inline constexpr Tr kHelpSpatial{"How the mod's sounds are placed. Stereo: left and right by level and timing, things behind you darker. 3D: through a head model for headphones, also above and below. Plain: left and right only."};
inline constexpr Tr kHelpStrikeAssist{"In Tartarus: when you attack, you turn to face the Shadow your strike can reach, on any side. Your reach stays the same."};
inline constexpr Tr kHelpRelaxedReaper{"In Tartarus: you can stay on a floor twice as long before the Reaper comes. On a floor, the time left doubles, or halves when you turn it off."};
inline constexpr Tr kHelpAlwaysDash{"Outside Tartarus: you dash whenever you move, without holding Shift or RT. Holding Shift or RT then runs, and Alt still walks. The walk to a point of interest dashes too."};
inline constexpr Tr kHelpBehindPitch{"Sounds whose source is behind you play lower."};
inline constexpr Tr kHelpPoiRange{"How far the points of interest list reaches."};
inline constexpr Tr kHelpMasterVolume{"Every sound the mod plays. The game's own sounds follow the game's settings."};
inline constexpr Tr kHelpSoundVolume{"The Shadow sounds and the controller layer's tick."};
inline constexpr Tr kHelpWallVolume{"How loud the wall tones are."};
inline constexpr Tr kHelpWallRange{"How far away a wall starts to sound. Shorter keeps the tones for walls close by."};
inline constexpr Tr kHelpTriggerDelay{"How long one trigger waits for the other before it counts as the game's own press. Longer makes the mod's controller layer easier to open."};
inline constexpr Tr kHelpMenuSpeed{"Menus open, close and change faster, so they take your keys sooner. The game's menu sounds still play. Not in battle, story scenes or conversations."};
inline constexpr Tr kHelpEntryHints{"Menus say their keys after their first line. Off, F1 still reads them."};
inline constexpr Tr kHelpVoicedLines{"What the screen reader does with a line the game voices: stay silent, say only who speaks, or read it aloud. Unvoiced lines are always read."};
inline constexpr Tr kHelpVoiceEndSound{"What tells you a line has finished and waits for you: the word Next, one of the game's sounds, or nothing."};
inline constexpr Tr kHelpSubtitles{"The screen reader reads the subtitles of movies and cutscenes as they appear. They are in the log either way."};
inline constexpr Tr kHelpAudioDescription{"What is on screen in the animated story movies is described between the lines of dialogue: by a narrator's voice, or read by the screen reader."};
inline constexpr Tr kHelpSceneDescription{"What is on screen in the story scenes played in the game's 3D engine is described between the lines. Suppress repeated descriptions: a description you have already heard is not read again, so a scene that comes back, a job shift or a meal, is described the first time only."};
inline constexpr Tr kHelpSceneVoice{"Who reads the descriptions of 3D scenes: a narrator's voice, or your screen reader."};
inline constexpr Tr kHelpSceneSpeed{"The narrator of 3D story scenes reads 25, 50 or 75 percent faster, at the same pitch. Off, at its normal speed. The animated movies keep the normal speed: their descriptions are timed between the lines."};
inline constexpr Tr kHelpDescriptionWait{"In 3D story scenes, each description pauses the scene like a message window and waits for Enter. Off, descriptions are fitted between the lines while it plays. Animated movies never wait: their descriptions are timed between the lines."};
inline constexpr Tr kHelpDescriptionVolume{"How loud the narrator of movies and scenes is."};
inline constexpr Tr kHelpModKeys{"Lists the mod's keys, to change them."};
// The Mod keys page (settings.cpp): a row per key, what it does then its key.
inline constexpr Tr kKeysReadAll{"Read all keys"};
inline constexpr Tr kHelpKeysReadAll{"Reads every mod key at once."};
inline constexpr Tr kKeysResetAll{"Reset all keys to default"};
inline constexpr Tr kKeysResetDone{"Every mod key is back on its default."};
inline constexpr Tr kKeysPress{"Press the new key for"};   // + what it does
inline constexpr Hint kKeysPressCancel{"Escape cancels.", "Press it on the keyboard; B cancels."};
inline constexpr Tr kKeysCancelled{"Cancelled"};   // + the key it keeps
inline constexpr Tr kKeysReserved{"is the game's. Press another key, or Escape."};   // after the key
inline constexpr Tr kKeysNeedsNoShift{"has Shift: Shift with this key goes back. Press a key without Shift, or Escape."};   // after the key
inline constexpr Tr kKeysBackOf{"goes back for"};   // "Shift+1 goes back for Exits: ..."
inline constexpr Tr kKeysPressAnother{"Press another key, or Escape."};
inline constexpr Tr kKeysMovesTo{"moves to"};   // "<what the other key does> moves to Apostrophe"
inline constexpr Tr kKeysBackToDefault{"back on its default"};
inline constexpr Tr kKeysAlreadyDefault{"already its default"};
inline constexpr Hint kModKeysPageKeys{"Up and down arrows choose, Enter changes the key: then press the new one. Delete puts a key back on its default, Escape goes back to the settings.",
                                       "Up and down choose, A changes the key: then press the new one on the keyboard. X puts a key back on its default, B goes back to the settings."};
// The sound test: each row plays one of the mod's sounds (name, then what it means). The sonar's rows are named by
// their kind alone (the user's call, 2026-11-17: no "Sonar:" before every row); the description says what it is.
struct SoundTest { Tr name; Tr help; };
inline constexpr SoundTest kSoundTests[] = {
    {"Exit", "A way into another area."},
    {"Door", "A room's door. One hollow knock."},
    {"Person", "Someone to talk to. A whistled note that rises and falls."},
    {"Shop", "A shop or vendor. Two small bells struck together."},
    {"Object", "Something to check or open."},
    {"Event", "A spot that starts a fight or a scene when you walk into it, such as a Gatekeeper."},
    {"Twilight Fragment", "A Twilight Fragment to pick up, or in Tartarus a crystal to strike for one."},
    {"A sound behind you", "The person whistle, from behind you. Lower in pitch when that setting is on."},
    {"Shadow, facing you", "The nearest Shadow within 30 meters snarls steadily from where it is, louder as it nears. Bright: it faces you."},
    {"Shadow, hunting you", "The snarl of a Shadow that has noticed you: higher and louder."},
    {"Shadow, back turned", "Muffled and wobbling: its back is to you, and a strike now brings the advantage. It grows duller as it turns away."},
    {"Shadow lost you", "A Shadow that was hunting you has lost you."},
    {"Shadow sight", "A sizzle from the edge of a Shadow's sight, from its point nearest you: you can walk up to it but not into it, or the Shadow notices you. Quiet while the edge is far."},
    {"Shadow sight, at the edge", "The same sizzle with the edge right beside you: one more step and the Shadow notices you."},
    {"Hidden from a Shadow", "A muffled hum: you stand where a Shadow would see you, but a wall blocks its view."},
    {"Strike reach", "A Shadow or a breakable object is within reach of your strike. In the game it repeats quickly while you stay in reach."},
    {"Strike reach, behind the Shadow", "Within reach and behind the Shadow: the strike brings the advantage."},
    {"Wall ahead", "The wall tone for a wall in front of you."},
    {"Wall to the right", "The wall tone for a wall on your right."},
    {"Wall behind", "The wall tone for a wall behind you."},
    {"Wall to the left", "The wall tone for a wall on your left."},
    {"Controller layer", "Both triggers are held: the mod's controller layer is open."},
};
inline constexpr Tr kSetWallTones{"Wall tones"};
inline constexpr Tr kSetSonar{"Sonar"};
inline constexpr Tr kSetSonarScope{"Plays"};
inline constexpr Tr kScopeAll{"everything nearby"};
inline constexpr Tr kScopeCategory{"the list's category only"};
inline constexpr Tr kScopeSelected{"the selected point only, at any distance"};
inline constexpr Tr kSetSonarRange{"Range"};
inline constexpr Tr kSetSonarExits{"Exits"};
inline constexpr Tr kSetSonarDoors{"Doors"};
inline constexpr Tr kSetSonarPeople{"People"};
inline constexpr Tr kSetSonarShops{"Shops"};
inline constexpr Tr kSetSonarThings{"Objects"};
inline constexpr Tr kSetSonarEvents{"Events"};
inline constexpr Tr kSetSonarFragments{"Twilight Fragments"};
inline constexpr Tr kSetSonarVolume{"Sonar"};
inline constexpr Tr kSonarOn{"Sonar on"};
inline constexpr Tr kSonarOff{"Sonar off"};
inline constexpr Tr kSetShadowAlerts{"Shadow alerts"};
inline constexpr Tr kSetShadowSight{"Shadow sight"};
inline constexpr Tr kSetSightRange{"Shadow sight range"};
inline constexpr Tr kSetTopDown{"Top-down exploration"};
inline constexpr Tr kSetTurnedRooms{"Keep your heading through passages"};
inline constexpr Tr kSetStrikeAssist{"Strike assist"};
inline constexpr Tr kSetAlwaysDash{"Always dash"};
inline constexpr Tr kSetRelaxedReaper{"Relaxed Reaper rate"};
inline constexpr Tr kSetSpatial{"Placement"};
inline constexpr Tr kSpatialStereo{"stereo"};
inline constexpr Tr kSpatialHrtf{"3D for headphones"};
inline constexpr Tr kSpatialPan{"plain left and right"};
inline constexpr Tr kSetBehindPitch{"Lower pitch behind you"};
inline constexpr Tr kSetPoiRange{"Points of interest range"};
inline constexpr Tr kSetMasterVolume{"Master"};
inline constexpr Tr kSetSoundVolume{"Shadow sounds"};
inline constexpr Tr kSetWallVolume{"Wall tones"};
inline constexpr Tr kSetWallRange{"Wall tone range"};
inline constexpr Tr kWallContinuous{"continuous"};
inline constexpr Tr kWallMoving{"only while moving"};
inline constexpr Tr kSetTriggerDelay{"Trigger delay"};
inline constexpr Tr kSetEntryHints{"Menu key hints on entry"};
inline constexpr Tr kSetMenuSpeed{"Menu animation speed"};
inline constexpr Tr kSpeed4{"4 times"};
inline constexpr Tr kSpeed8{"8 times"};
inline constexpr Tr kSpeed16{"16 times"};
inline constexpr Tr kSetVoicedLines{"Voiced dialogue"};
inline constexpr Tr kVoicedRead{"read aloud"};
inline constexpr Tr kVoicedName{"speaker's name only"};
inline constexpr Tr kVoicedSilent{"not read, the voice plays alone"};
inline constexpr Tr kSetVoiceEndSound{"When a line ends"};
inline constexpr Tr kSetSubtitles{"Read subtitles"};
inline constexpr Tr kSetAudioDescription{"Movies"};
inline constexpr Tr kSetSceneDescription{"3D scenes"};
inline constexpr Tr kSetSceneVoice{"3D scenes read by"};
inline constexpr Tr kSetSceneSpeed{"Faster narrator in 3D scenes"};
inline constexpr Tr kFaster25{"25 percent"};
inline constexpr Tr kFaster50{"50 percent"};
inline constexpr Tr kFaster75{"75 percent"};
inline constexpr Tr kSceneOnce{"suppress repeated descriptions"};
inline constexpr Tr kSetDescriptionWait{"Descriptions wait for Enter"};
inline constexpr Tr kDescAudio{"narrator's voice"};
inline constexpr Tr kDescReader{"screen reader"};
inline constexpr Tr kSetDescriptionVolume{"Audio description"};
inline constexpr Tr kEndNext{"say Next"};
inline constexpr Tr kNext{"Next"};
inline constexpr Tr kAutoOn{"Auto on"};
inline constexpr Tr kAutoOff{"Auto off"};
inline constexpr Tr kFastForwardOn{"Fast-forward on"};
inline constexpr Tr kFastForwardOff{"Fast-forward off"};
inline constexpr Tr kEndPage{"page turn sound"};
inline constexpr Tr kEndMessage{"message chime sound"};
inline constexpr Tr kEndCursor{"cursor tick sound"};
inline constexpr Tr kMetersUnit{"meters"};
// A spoken distance (core/units.cpp): "1 meter", "6 meters", "less than 1 meter".
inline constexpr Tr kMeterUnit{"meter"};
inline constexpr Tr kLessThanOneMeter{"less than 1 meter"};
inline constexpr Tr kPercent{"percent"};
inline constexpr Tr kMilliseconds{"milliseconds"};
inline constexpr Hint kListKeys{"Up and down arrows choose, Space confirms, Escape back.", "Up and down choose, A confirms, B back."};
inline constexpr Hint kTutorialListKeys{"Up and down arrows choose, Q and E switch tabs, Space opens, Escape back.", "Up and down choose, LB and RB switch tabs, A opens, B back."};
inline constexpr Hint kChooseKeys{"Up and down arrows choose, Space confirms.", "Up and down choose, A confirms."};
// The game's online features (Network Functions on; N is the game's View button). Over a class question's answers:
// how other players answered (Voice Answer). In town: what other players did today (Voice Action).
inline constexpr Hint kNetAnswerKey{"N shows how other players answered.", "View shows how other players answered."};
inline constexpr Hint kNetActionKey{"N what other players did today.", "View what other players did today."};
// The two screens are menus: a row per answer, or per kind of activity with the activities the game notes under it.
inline constexpr Hint kNetAnswerKeys{"Up and down arrows read the answers, N or Escape closes.", "Up and down read the answers, View or B closes."};
inline constexpr Hint kNetActionKeys{"Up and down arrows read, Tab jumps to the next kind of activity, N or Escape closes.", "Up and down read, RT jumps to the next kind of activity, View or B closes."};
inline constexpr Tr kNetAnswerTitle{"Other players' answers"};
inline constexpr Tr kNetActionTitle{"What other players did today"};
inline constexpr Tr kNetWaiting{"Getting other players' data."};   // the review key before the figures come
inline constexpr Tr kNetFailed{"Other players' data could not be fetched."};
inline constexpr Tr kNetPercent{"{}, {} percent"};   // an answer or kind of activity, then its share
// The three kinds of activity the game sorts other players' days into, in its own order.
inline constexpr Tr kNetActionKinds[3] = {"Daily life", "Social Links", "Tartarus"};
inline constexpr Hint kCampKeys{"Up and down arrows choose, Space opens, Escape closes.", "Up and down choose, A opens, B closes."};
// Points of interest
// A way into another area: said by its name alone, which is where it leads ("Gekkoukan High School exit" was taken
// for the way out of the school; the players' call, 2026-11-09). This is the one with no name.
inline constexpr Tr kPoiExit{"Exit"};
inline constexpr Tr kVerbGoTo{"Go to"};
inline constexpr Tr kVerbTalk{"Talk"};
inline constexpr Tr kVerbListen{"Listen"};
inline constexpr Tr kVerbShop{"@verb:Shop"};
inline constexpr Tr kVerbAction{"Action"};
inline constexpr Tr kVerbCheck{"Check"};
inline constexpr Tr kPoiPerson{"Person"};
inline constexpr Tr kPoiShop{"Shop"};
inline constexpr Tr kPoiDoor{"Door"};
inline constexpr Tr kPoiThing{"Object"};
inline constexpr Tr kPoiEvent{"Event"};
inline constexpr Tr kPoiGatekeeper{"Gatekeeper"};   // the game's word for the boss of a border floor
inline constexpr Tr kPoiShadow{"Shadow"};
inline constexpr Tr kPoiBreakable{"Breakable object"};
inline constexpr Tr kPoiShadowStrong{"Strong Shadow"};
inline constexpr Tr kPoiShadowRare{"Rare Shadow"};   // the game's word (Mitsuru: "rare Shadows")
inline constexpr Tr kPoiReaper{"The Reaper"};
inline constexpr Tr kPoiMissingPerson{"Missing Person"};   // the game's own name, when its table has no row
// Club Escapade's order quiz (Mutatsu's Tower link): where each customer stands, in the bartender's own words, said
// in brackets after the name ("Unemotional Woman (by the entrance)"); the man has no place in his question.
inline constexpr Tr kBarPlaceBack{"by the table in the back"};
inline constexpr Tr kBarPlaceEntrance{"by the entrance"};
inline constexpr Tr kBarPlaceMiddle{"in the middle of the floor"};
// After the bartender's question: who it means ("That's the Unemotional Woman.").
inline constexpr Tr kBarCustomerIs{"That's the {}."};
inline constexpr Tr kPoiChestRare{"Rare Treasure Chest"};
inline constexpr Tr kPoiChestGold{"Gold Treasure Chest"};
inline constexpr Tr kPoiChestLocked{"Locked Treasure Chest"};   // then what it costs: ", 2 Twilight Fragments"
inline constexpr Tr kPoiFragments{"Twilight Fragments"};
inline constexpr Tr kPoiFragment{"Twilight Fragment"};                  // the game shows "Something Shining"
inline constexpr Tr kPoiFragmentCrystal{"Twilight Fragment crystal"};   // Tartarus: strike it for one
// One point's type, said after its name when the list lands on it ("Vending Machine, Object, 3 meters"), in the
// categories' order.
inline constexpr Tr kPoiCategory[7] = {"Exits", "Doors", "People", "Shops", "Objects", "Events", "Shadows"};
inline constexpr Tr kShadowBackTurned{"Shadow close, back turned"};
inline constexpr Tr kShadowFacingYou{"Shadow close, facing you"};
inline constexpr Tr kNothingNearbyFull{"Nothing nearby"};
inline constexpr Tr kPoiNoneOf{"No"};   // "No Shadows": a category key with nothing in its category
inline constexpr Tr kNothingSelected{"Nothing selected"};
inline constexpr Tr kOClock{"o'clock"};                 // after the hour, a direction by the clock face: "2 o'clock"
// The compass in the top-down mode (north fixed): a bearing's eight points, from north clockwise.
inline constexpr Tr kCompass[8] = {"north", "north-east", "east", "south-east", "south", "south-west", "west", "north-west"};
inline constexpr Tr kScanNothing{"nothing"};            // the right-stick scan: no point anywhere in range
inline constexpr Tr kMonad{"Monad"};                    // the area key's name for the section behind a Monad door
inline constexpr Tr kMonadChambers{"Monad Chambers"};   // the same in Episode Aigis' Abyss of Time
// What the icon over a person says, after their name in the list ("Akihiko Sanada, already spoken to"). The speech bubble
// (something new to say, what guides call the students to talk to) and the ear (two people chatting, to listen in on)
// are said too: a talkable person with no icon at all says nothing.
inline constexpr Tr kIconTalk{"something to say"};
inline constexpr Tr kIconListen{"overhear"};
inline constexpr Tr kIconBuzz{"overhear, a buzz of chatter"};   // the handwritten "buzz" over a crowd
inline constexpr Tr kIconWhisper{"overhear, whispering"};      // the handwritten "whisper"
inline constexpr Tr kIconTalked{"already spoken to"};
inline constexpr Tr kIconHeard{"already heard"};
inline constexpr Tr kIconLink{"Social Link"};
inline constexpr Tr kIconLinkReversed{"Social Link, reversed"};
inline constexpr Tr kIconHangout{"hangout"};
inline constexpr Tr kIconEpisode{"Linked Episode"};
inline constexpr Tr kIconRequest{"request"};
inline constexpr Tr kIconStudy{"study group"};
inline constexpr Tr kIconWalk{"walk"};
// Navigation
inline constexpr Tr kNoPath{"No path"};
inline constexpr Tr kNoPathInRoom{"No path, though it is in this room"};
inline constexpr Tr kStuck{"Stuck, stopping"};
inline constexpr Tr kStopped{"Stopped"};
inline constexpr Tr kNotInField{"Not in the field"};
inline constexpr Tr kObjective{"Objective"};
inline constexpr Tr kNoObjective{"No objective shown yet"};
inline constexpr Tr kNothingToReview{"No menu or message to read"};
inline constexpr Tr kNoAreaDescription{"No description for this place:"};
inline constexpr Tr kNoPortraitDescription{"No description for this portrait:"};
inline constexpr Tr kFloor{"floor"};
inline constexpr Tr kTartarus{"Tartarus"};
inline constexpr Tr kUnknownArea{"Unknown area"};
// Velvet Room (the menus are pictures: the mod's own words)
inline constexpr Tr kVelvetMenu[] = {"Fusion", "Summon from the Compendium", "Register to the Compendium"};
inline constexpr Tr kVelvetTop{"What do you wish for?"};
inline constexpr Tr kFusionMethods[] = {"Dyad Fusion, two Personas", "Special Fusion", "Fusion Search"};
inline constexpr Tr kFusionMethod{"Choose a fusion method."};
inline constexpr Tr kFusionFirst{"Choose the base Persona."};
inline constexpr Tr kFusionSecond{"Choose the second Persona."};
inline constexpr Tr kFusionSearch{"Fusion Search. Choose a Persona to fuse."};
inline constexpr Tr kFusionFrom{"from"};
inline constexpr Tr kFusionAnd{"and"};
inline constexpr Hint kFusionSearchKeys{"Space confirms, Q and E sort, Escape back.", "A confirms, LB and RB sort, B back."};
inline constexpr Tr kFusionNone{"No Persona can be fused."};
inline constexpr Tr kSpecialFusion{"Special Fusion. Choose a Persona to fuse."};
inline constexpr Tr kSpecialHave{"you have"};
inline constexpr Tr kSpecialReady{"ready to fuse"};
inline constexpr Tr kCompendium{"Compendium. Select a Persona."};
inline constexpr Tr kRegister{"Who shall you register?"};
inline constexpr Tr kRegisterThis{"Register this Persona?"};
inline constexpr Tr kSummonThis{"Summon this Persona?"};
inline constexpr Hint kStatusConfirmKeys{"Space registers it, Page Down and Page Up jump between sections, Q and E switch Persona, F skills and affinities, Tab registered stats, Escape back.", "A registers it, RT and LT jump between sections, LB and RB switch Persona, X skills and affinities, Y registered stats, B back."};
inline constexpr Hint kRegisterKeys{"Up and down arrows choose, Space opens its status, Tab marks it, F registers the marked ones or all, Escape back.", "Up and down choose, A opens its status, Y marks it, X registers the marked ones or all, B back."};
inline constexpr Hint kCompendiumPageKeys{"Space summons, Tab and Shift Tab jump between sections, Q and E switch Persona, F skills and affinities, Escape back.", "A summons, RT and LT jump between sections, LB and RB switch Persona, X skills and affinities, B back."};
inline constexpr Hint kLevelUpKeys{"Tab and Shift Tab jump between sections, Space continues.", "RT and LT jump between sections, A continues."};
inline constexpr Hint kCompendiumKeys{"Up and down arrows choose, Space opens its page, Q and E sort, Tab registered only, F lock, Escape back.", "Up and down choose, A opens its page, LB and RB sort, Y registered only, X lock, B back."};
inline constexpr Tr kFusionGives{"makes"};
inline constexpr Tr kFusionImpossible{"cannot fuse"};
inline constexpr Tr kAboveYourLevel{"above your level"};
inline constexpr Tr kAlreadyOwned{"already in your stock"};
inline constexpr Hint kFusionKeys{"Space confirms, F Persona stats, Escape back.", "A confirms, X Persona stats, B back."};
inline constexpr Tr kEquipped{"equipped"};
inline constexpr Tr kFusionResult{"Result"};
inline constexpr Tr kFusionMaterial{"Material"};
// Persona status pages (camp, Velvet Room, battle)
inline constexpr Tr kStatNames[] = {"Strength", "Magic", "Endurance", "Agility", "Luck"};
inline constexpr Tr kStatsTitle{"Stats"};
inline constexpr Tr kAffinitiesTitle{"Affinities"};
inline constexpr Tr kNoAffinities{"no weaknesses or resistances"};
inline constexpr Tr kLearnsTitle{"Learns later"};
inline constexpr Tr kLearnsAt{"at level"};
inline constexpr Tr kSlBonus{"Social Link bonus"};
inline constexpr Tr kSlRank{"rank"};
inline constexpr Tr kExpToNext{"EXP to next level"};
inline constexpr Tr kRaisesTo{"up to level"};
inline constexpr Tr kUp{"up"};
inline constexpr Tr kNew{"new"};
inline constexpr Tr kInheritTitle{"Choose skills to inherit."};
inline constexpr Tr kInheritUpTo{"Choose skills to inherit, up to"};   // then how many: "..., up to 3."
inline constexpr Tr kPicks{"picks"};   // "chosen, 1 of 2 picks": apart from the row's place in the list
inline constexpr Tr kInherits{"Inherits"};
inline constexpr Tr kNotChosen{"not chosen"};
inline constexpr Tr kFusing{"Fusing."};
inline constexpr Hint kFusingKeys{"Tab skips the animation.", "The Menu button skips the animation."};
inline constexpr Hint kInheritSkill{"Up and down arrows move, Space takes a skill or puts it back, Escape back.", "Up and down move, A takes a skill or puts it back, B back."};
inline constexpr Hint kFusionConfirmKeys{"Space fuses, Tab and Shift Tab jump between sections, Q and E page through the result and its materials, F skills and affinities, Escape back.", "A fuses, RT and LT jump between sections, LB and RB page through the result and its materials, X skills and affinities, B back."};
// Config (System > Config, and the title screen's)
inline constexpr Tr kConfig{"Config"};
inline constexpr Tr kOn{"on"};   // a setting's value
inline constexpr Tr kOnTarget{"@target:on"};   // "Weak on Junpei", "Use Agi on all enemies?"
inline constexpr Tr kOff{"off"};
inline constexpr Tr kUnavailable{"unavailable"};
inline constexpr Tr kUnsupportedBuild{"This copy of Persona 3 Reload is not the version Arcana was made for, such as the demo or an older update. To keep the game from freezing, menus are not read. Messages and the field still are."};
inline constexpr Hint kConfigTabKeys{"Up and down arrows choose, Space opens, Escape back. {settings} opens the mod's settings.", "Up and down choose, A opens, B back. Both triggers and View open the mod's settings."};
inline constexpr Hint kBgmKeys{"Up and down arrows choose, Tab and Shift Tab jump between modes and tracks, Space sets it, F plays or stops a track, E marks or unmarks a favorite, Escape back.", "Up and down choose, RT and LT jump between modes and tracks, A sets it, X plays or stops a track, RB marks or unmarks a favorite, B back."};
// A music row: Space (or left and right) opens its playlist; the game's confirm would save and leave.
inline constexpr Hint kConfigBgmRowKeys{"Up and down arrows choose, Space or the left and right arrows open the playlist, H restores defaults, Escape back. {settings} opens the mod's settings.", "Up and down choose, A or left and right open the playlist, Menu button restores defaults, B back. Both triggers and View open the mod's settings."};
inline constexpr Hint kConfigKeys{"Up and down arrows choose, left and right arrows change, Space saves changes, H restores defaults, Escape back. {settings} opens the mod's settings.", "Up and down choose, left and right change, A saves changes, Menu button restores defaults, B back. Both triggers and View open the mod's settings."};
inline constexpr Tr kKeyCode{"key code"};
inline constexpr Tr kPlaylist{"Playlist"};   // when the BGM row's own title is not known
inline constexpr Tr kBgmModes{"Modes"};
inline constexpr Tr kBgmTracks{"Tracks"};
// The playlist's first three rows (Default, Random, Favorited by their BgmId -1, -2, -3): what each does.
inline constexpr Tr kBgmModeDesc[] = {"The game's own music", "A random track each time", "A random favorite each time"};
inline constexpr Tr kBgmNoFavorites{"no favorites yet"};
inline constexpr Tr kBgmPlaying{"playing"};
inline constexpr Tr kBgmStopped{"stopped"};
inline constexpr Tr kBgmUnfavorited{"not a favorite"};
inline constexpr Tr kFavorite{"favorite"};
inline constexpr Tr kBgmCurrent{"current"};   // the playlist's track now set (the game's SET mark)
inline constexpr Tr kDictionary{"Dictionary"};
inline constexpr Tr kNoParty{"No party"};
inline constexpr Tr kInParty{"in party"};   // a member list that mixes the active party with the rest
inline constexpr Tr kReserve{"reserve"};
inline constexpr Tr kNavigator{"navigator"};
inline constexpr Tr kTownInfo{"Places here"};
inline constexpr Tr kTownLinks{"Social Links here"};
inline constexpr Tr kTownOthers{"Also here"};
inline constexpr Tr kTheurgy{"Theurgy"};
inline constexpr Tr kBuffs[] = {"attack up", "attack down", "defense up", "defense down", "agility up", "agility down"};
inline constexpr Tr kCharged{"Charged"};
inline constexpr Tr kConcentrating{"Concentrating"};
inline constexpr Tr kPhysicalShield{"Physical attacks reflected"};
inline constexpr Tr kMagicShield{"Magic attacks reflected"};
inline constexpr Tr kAilmentsDoubled{"Ailments land more easily"};
inline constexpr Tr kWalls[] = {"Fire resisted", "Ice resisted", "Electricity resisted", "Wind resisted"};
inline constexpr Tr kBreaks[] = {"Fire resistance broken", "Ice resistance broken", "Wind resistance broken", "Electricity resistance broken"};
inline constexpr Tr kLog{"Log"};
inline constexpr Tr kRequests{"Elizabeth's requests"};
inline constexpr Tr kMissingPersons{"Missing Persons"};
inline constexpr Tr kNumber{"Number"};
inline constexpr Tr kUnknown{"unknown"};
inline constexpr Tr kMissingFound{"found"};
inline constexpr Tr kMissingDiscontinued{"discontinued"};
inline constexpr Tr kMissingSearching{"searching"};
inline constexpr Hint kRequestKeys{"Up and down arrows choose, Space accepts or reports, F info, X sorts, Escape closes.", "Up and down choose, A accepts or reports, X info, RT sorts, B closes."};
// The battle's Persona page from a skill list: OK equips the Persona shown (BP_BtlGuiPersonaStatus: CheckPersonaChange,
// SetEquipPersona); opened from Shift, Survey or a target (IsStrategy) OK does nothing and L1 / R1 switch the member.
inline constexpr Hint kPersonaStatusKeys{"Tab and Shift Tab jump between sections, Q and E switch Persona, Space equips the one shown, Escape back.", "RT and LT jump between sections, LB and RB switch Persona, A equips the one shown, B back."};
inline constexpr Hint kBattleMemberStatusKeys{"Tab and Shift Tab jump between sections, Q and E switch member, Escape back.", "RT and LT jump between sections, LB and RB switch member, B back."};
// A member's Persona status opened from their Stats page (X): Q / E switch the member (FUN_14135d270).
inline constexpr Hint kStatsPersonaKeys{"Up and down arrows go through the lines, Tab and Shift Tab jump between sections, Q and E switch member, Escape closes Persona status.", "Up and down go through the lines, LB and RB switch member, B closes Persona status."};
// Rush running with no battle menu up: the GUI's OPTION toggles it, CANCEL turns it off (BP_BtlGuiComponent).
inline constexpr Hint kRushRunningKeys{"Tab or C stops Rush.", "The Menu button or B stops Rush."};
// The Velvet Room's Persona page (F on a fusion list): the result page's skills and affinities switch works there too.
inline constexpr Hint kVelvetPersonaKeys{"Tab and Shift Tab jump between sections, Q and E switch Persona, F skills and affinities, Escape back.", "RT and LT jump between sections, LB and RB switch Persona, X skills and affinities, B back."};
inline constexpr Tr kTacticsHeading{"Tactics"};
inline constexpr Tr kTerminal{"Terminal. Where do you want to go?"};
inline constexpr Hint kTerminalKeys{"Up and down arrows choose, Space travels, Escape closes.", "Up and down choose, A travels, B closes."};
inline constexpr Tr kEntrance{"Entrance"};
inline constexpr Tr kFloorTitle{"Floor"};
inline constexpr Tr kYouAreHere{"furthest floor reached"};
// The title menu: Z opens the credits (UTitleStateSelect: action 0x1a, LT).
inline constexpr Hint kTitleMenuKeys{"Up and down arrows choose, Space confirms, Z plays the credits.", "Up and down choose, A confirms, LT plays the credits."};
// Request info (F on a request, UIRequest state 9; FUN_1415a9370): up and down switch request; Space accepts at the Velvet Room.
inline constexpr Hint kRequestInfoKeys{"Up and down arrows switch request, F or Escape back to the list.", "Up and down switch request, X or B back to the list."};
inline constexpr Hint kRequestInfoVelvetKeys{"Up and down arrows switch request, Space accepts, F or Escape back to the list.", "Up and down switch request, A accepts, X or B back to the list."};
inline constexpr Hint kSelectKeys{"Up and down arrows choose, Space confirms, Escape closes.", "Up and down choose, A confirms, B closes."};
inline constexpr Hint kLogKeys{"Up and down arrows scroll, Space replays the voice, Escape closes.", "Up and down scroll, A replays the voice, B closes."};
inline constexpr Tr kLogEarlier{"An earlier line, from before this session"};
inline constexpr Tr kLogNone{"None"};   // the log has no lines (the game's own word for it)
inline constexpr Tr kShift{"Shift. Pass the turn to"};
inline constexpr Tr kRewind{"Rewind. Choose a day to go back to"};
inline constexpr Tr kCard{"Card"};
// Shuffle Time's Minor Arcana suits, said with the card's number: "Wands 1".
inline constexpr Tr kSuitSwords{"Swords"};
inline constexpr Tr kSuitCoins{"Coins"};
inline constexpr Tr kSuitCups{"Cups"};
inline constexpr Tr kSuitWands{"Wands"};
// Camp submenus (screens/camp_*.cpp, quest.cpp, theurgy.cpp)
// Their keys (F1), from each menu's native input function: Q / E LB / RB,
// F the X button, X RT, Z LT, H the Menu button.
inline constexpr Hint kItemListKeys{"Up and down arrows choose, Q and E switch category, Space uses, Escape back.", "Up and down choose, LB and RB switch category, A uses, B back."};
inline constexpr Hint kEquipSlotKeys{"Up and down arrows choose a slot, Space changes it, Q and E switch member, Escape back.", "Up and down choose a slot, A changes it, LB and RB switch member, B back."};
inline constexpr Hint kEquipGearKeys{"Up and down arrows choose, Space equips, Q and E switch member, F reads it again, Escape back.", "Up and down choose, A equips, LB and RB switch member, X reads it again, B back."};
inline constexpr Hint kCampPersonaKeys{"Up and down arrows go through the lines, Tab and Shift Tab jump between sections, Q and E switch Persona, Space on its name equips it, F reads it again, H releases, Escape back.", "Up and down go through the lines, RT and LT jump between sections, LB and RB switch Persona, A on its name equips it, X reads it again, Menu button releases, B back."};
inline constexpr Hint kCampPersonaStatusKeys{"Tab and Shift Tab jump between sections, Q and E switch Persona, Space equips it, Escape back.", "RT and LT jump between sections, LB and RB switch Persona, A equips it, B back."};
inline constexpr Hint kStatsKeys{"Up and down arrows choose, Space opens their page, Q and E tactics, F joins or leaves the party, Escape back.", "Up and down choose, A opens their page, LB and RB tactics, X joins or leaves the party, B back."};
inline constexpr Hint kTacticsListKeys{"Up and down arrows choose, Space changes their tactic, Q and E back to stats, F joins or leaves the party, Escape back.", "Up and down choose, A changes their tactic, LB and RB back to stats, X joins or leaves the party, B back."};
// The triggers are the game's on this page (Theurgy, Persona status): on a pad the D-pad walks its lines.
inline constexpr Hint kStatsPageKeys{"Up and down arrows go through the lines, Tab and Shift Tab jump between sections, Q and E switch member, X Persona status, Z Theurgy, F joins or leaves the party, Escape back.", "Up and down go through the lines, LB and RB switch member, RT Persona status, LT Theurgy, X joins or leaves the party, B back."};
inline constexpr Hint kCampRequestKeys{"Up and down arrows choose, F info, X sorts, Q and E switch tabs, Escape closes.", "Up and down choose, X info, RT sorts, LB and RB switch tabs, B closes."};
inline constexpr Hint kMissingPersonsKeys{"Up and down arrows choose, F reads it again, X sorts, Q and E switch tabs, Escape closes.", "Up and down choose, X reads it again, RT sorts, LB and RB switch tabs, B closes."};
inline constexpr Hint kMissingBoardKeys{"Up and down arrows choose, F reads it again, X sorts, Escape closes.", "Up and down choose, X reads it again, RT sorts, B closes."};
inline constexpr Hint kCalendarKeys{"Left and right arrows move a day, up and down arrows a week, Q and E change month, F opens the part-time jobs, Escape closes.", "Left and right move a day, up and down a week, LB and RB change month, X opens the part-time jobs, B closes."};
inline constexpr Hint kCalendarPlansKeys{"Up and down arrows go through the jobs, F or Escape closes them.", "Up and down go through the jobs, X or B closes them."};
inline constexpr Hint kSocialPageKeys{"Up and down arrows choose, Q and E switch link, Escape back.", "Up and down choose, LB and RB switch link, B back."};
inline constexpr Hint kTheurgyListKeys{"Left and right arrows choose, Q and E switch character, F personality, Escape back.", "Left and right choose, LB and RB switch character, X personality, B back."};
inline constexpr Tr kItemCategories[] = {"Order Obtained", "Consumable Items", "Skill Cards", "Materials & Valuables", "Event & Misc."};
inline constexpr Tr kItem{"Item"};
inline constexpr Tr kNoItems{"No items"};
inline constexpr Tr kUseOnWhom{"On whom?"};
inline constexpr Tr kWhichPersona{"Which Persona?"};
inline constexpr Tr kEquipSlots[] = {"Weapon", "Armor", "Footwear", "Accessory", "Outfit"};
inline constexpr Tr kTactic{"Tactic"};
inline constexpr Tr kChosen{"chosen"};
inline constexpr Tr kTheurgyObtained{"New Theurgy"};
inline constexpr Tr kTheurgyGauge{"Gauge condition"};
inline constexpr Tr kNotEnough{"not enough"};
// Shops (shop.cpp)
inline constexpr Tr kOption{"Option"};
inline constexpr Tr kCannotBuy{"not now"};
inline constexpr Tr kOutOfStock{"out of stock"};
inline constexpr Tr kCarryingMax{"carrying the maximum"};
inline constexpr Tr kNotEnoughYen{"not enough yen"};
inline constexpr Tr kLeft{"left"};
inline constexpr Tr kForWhom{"For whom?"};
inline constexpr Tr kFor{"for"};
inline constexpr Tr kSell{"Sell"};
inline constexpr Tr kSellAll{"Sell all items"};
inline constexpr Tr kWhichMaterial{"Which material do you want to use?"};
inline constexpr Tr kBuyQuestion{"Is this what you want?"};
inline constexpr Tr kEquipQuestion{"Equip it now?"};
inline constexpr Tr kSellConfirm{"Sell it?"};
inline constexpr Tr kSellOldQuestion{"Sell what they wore before?"};
inline constexpr Tr kKeep{"Keep"};
inline constexpr Tr kMarked{"marked"};
inline constexpr Tr kNoTutorials{"There are no tutorials to display."};
// The camp's tactics as the game draws them (Stats, E), by the unit's tactic index (unit +0x296; read 2026-10-30)
inline constexpr Tr kTacticNames[] = {"Direct Commands", "Act Freely", "Full Assault", "Conserve SP", "Heal/Support"};
inline constexpr Tr kRequestStatus[] = {"not accepted", "accepted", "completed", "expired", "ready to report"};
inline constexpr Tr kRequestLocked{"???"};   // a request not yet open (status 5), as the game lists it
// Story cut-ins (cutin.cpp): the close-up a scene flashes before a line it stresses, by the game's character id and
// picture (T_UI_CI_<PC|SC><char>_<pic>, each picture looked at; 2026-11-02).
struct Cutin { int chara, pic; Tr text; };
inline constexpr Cutin kCutins[] = {
  {2, 1, "Close-up: Yukari, smiling."},
  {2, 2, "Close-up: Yukari, glaring."},
  {2, 4, "Close-up: Yukari, wide-eyed in surprise."},
  {2, 10, "Close-up: Yukari, blushing, eyes squeezed shut."},
  {3, 1, "Close-up: Junpei, grinning."},
  {3, 2, "Close-up: Junpei, scowling."},
  {3, 4, "Close-up: Junpei, eyebrows raised in surprise."},
  {3, 10, "Close-up: Junpei in the dark, terrified, teeth clenched."},
  {3, 11, "Close-up: Junpei, cap on backwards, grinning."},
  {3, 12, "Close-up: Junpei, cap on backwards, fired up, teeth clenched."},
  {4, 1, "Close-up: Akihiko, smirking."},
  {4, 2, "Close-up: Akihiko, frowning hard."},
  {4, 4, "Close-up: Akihiko, wide-eyed."},
  {4, 10, "Close-up: Akihiko, sweating nervously."},
  {5, 1, "Close-up: Mitsuru, eyes closed, a faint smile."},
  {5, 2, "Close-up: Mitsuru, a cold, stern stare."},
  {5, 4, "Close-up: Mitsuru, startled."},
  {5, 10, "Close-up: Mitsuru, hair tied up, blushing."},
  {6, 1, "Close-up: Fuuka, smiling gently."},
  {6, 2, "Close-up: Fuuka, determined."},
  {6, 4, "Close-up: Fuuka, wide-eyed in alarm."},
  {7, 2, "Close-up: Aigis, wide-eyed and intent."},
  {8, 1, "Close-up: Ken, a small smile."},
  {8, 2, "Close-up: Ken, frowning."},
  {8, 4, "Close-up: Ken, startled."},
  {9, 1, "Close-up: Koromaru, happy, tongue out."},
  {9, 2, "Close-up: Koromaru, snarling, eyes red."},
  {10, 2, "Close-up: Shinjiro, glaring from under his beanie."},
  {11, 1, "Close-up: Metis, a soft smile."},
  {11, 2, "Close-up: Metis, glaring."},
  {11, 4, "Close-up: Metis, startled."},
  {12, 1, "Close-up: Aigis, smiling."},
  {12, 2, "Close-up: Aigis, determined."},
  {12, 10, "Close-up: Aigis, wide-eyed, lips parted."},
  {211, 10, "Close-up: Takaya, a menacing grin."},
  {212, 10, "Close-up: Jin, glaring through his glasses."},
  {213, 10, "Close-up: Chidori, a faint smile."},
  {221, 10, "Close-up: Ryoji, smiling gently."},
  {222, 10, "Close-up: Ikutsuki, a wide, manic grin."},
  {222, 11, "Close-up: Ikutsuki, smiling pleasantly."},
  {223, 10, "Close-up: a student with a ponytail, panicked, teeth clenched."},
};
// Pictures a scene shows full screen (picture.cpp, AUIMiscPictureDraw; T_UI_Picture_<id>, each looked at 2026-11-03):
// the chalkboard picture of a class question (UI/Picture/Lesson; never the answer, the teacher names it after) and
// the story's sketch (UI/Picture/Event). Tutorial/T_UI_Picture_200 is an empty placeholder.
struct ScenePicture { const char* texture; Tr text; };
inline constexpr ScenePicture kScenePictures[] = {
  {"T_UI_Picture_000", "Picture: a pencil sketch in a spiral-bound sketchbook: Junpei in his baseball cap and a high-collared jacket, a little goatee on his chin, smiling as he looks off to the side."},
  {"T_UI_Picture_100", "Picture: four spirals, each drawn around the origin of x and y axes. A: a spiral that widens fast, each turn far wider than the one inside it, ending in a broad open sweep. B: evenly spaced rings, every turn the same distance from the last. C: rings that crowd together toward the outside, around a small open curl at the centre. D: a few tight turns around the origin that unwind into a long tail, flattening out to the right along the top."},
  {"T_UI_Picture_101", "Picture: the same four spirals, with A, the one that widens fast, boxed in red."},
  {"T_UI_Picture_102", "Picture: a device on a flat base: two long arms hinged at their middles form a tall rhombus, with a small folding arm inside it, and a contact strip across the top."},
  {"T_UI_Picture_103", "Picture: on x and y axes, a circle resting on the origin, touching a horizontal line across its top. A line from the origin through the circle runs out to that top line; a red bell-shaped curve peaks at the top of the circle and falls away on both sides toward the x axis."},
};

// The mod's key list (Shift+F1, the settings menu's "Mod keys" row): what each key does, in the order they are bound.
inline constexpr Tr kKeyHelpScreenKeys{"The keys of this screen"};
inline constexpr Tr kKeyHelpModKeys{"The mod's keys"};
inline constexpr Tr kKeyHelpSettings{"Mod settings"};
inline constexpr Tr kKeyHelpSonar{"Sonar on or off: the sounds of the things around you"};
inline constexpr Tr kKeyHelpWhere{"Where am I: the date, the area, your yen and the objective"};
inline constexpr Tr kKeyHelpStats{"Social stats"};
inline constexpr Tr kKeyHelpSocial{"Social Links and their ranks"};
inline constexpr Tr kKeyHelpReview{"Repeat the current message or describe the current screen"};
inline constexpr Tr kKeyHelpPoiNext{"Next point of interest, farther away"};
inline constexpr Tr kKeyHelpPoiPrev{"Previous point of interest, nearer"};
inline constexpr Tr kKeyHelpPoiCatNext{"Next category of points of interest, from its nearest"};
inline constexpr Tr kKeyHelpPoiCatPrev{"Previous category"};
inline constexpr Tr kKeyHelpParty{"Party: each member's level, HP and SP"};
inline constexpr Tr kKeyHelpWalk{"Walk to the selected point of interest, or stop walking"};
inline constexpr Tr kKeyHelpPoiNearest{"Select the nearest point of interest of any kind; again, the next nearest"};
inline constexpr Tr kKeyHelpPoiNearestPrev{"Back through the points of interest of any kind, toward the nearest"};
inline constexpr Tr kKeyHelpWalkUse{"Walk to the selected point of interest and use it: check, talk or open"};
// A number key's category ("Shadows: the nearest, again the next; Shift goes back").
inline constexpr Tr kKeyHelpPoiCatKey{"the nearest, again the next; Shift goes back"};
inline constexpr Tr kKeyHelpPoiCatBack{"back toward the nearest; first, the farthest"};
inline constexpr Tr kKeyHelpPoiAgain{"The selected point of interest again: where it is now, and its sound"};
inline constexpr Tr kKeyHelpArea{"Describe: how the place around you looks; while someone talks, how they look (press again for the place); on a Persona or a Shadow in focus, how it looks; on a Social Link, its picture"};
// A key's name in that list: its modifiers, then the key as Windows names it (kKeyUnnamed and its code when it has
// no name).
inline constexpr Tr kModCtrl{"Ctrl+"};
inline constexpr Tr kModAlt{"Alt+"};
inline constexpr Tr kModShift{"Shift+"};
inline constexpr Tr kKeyUnnamed{"key"};
// A controller button's name in that list.
inline constexpr Tr kPadDpadUp{"D-pad up"};
inline constexpr Tr kPadDpadDown{"D-pad down"};
inline constexpr Tr kPadDpadLeft{"D-pad left"};
inline constexpr Tr kPadDpadRight{"D-pad right"};
inline constexpr Tr kPadMenu{"Menu button"};
inline constexpr Tr kPadView{"View button"};
inline constexpr Tr kPadL3{"L3"};
inline constexpr Tr kPadR3{"R3"};
inline constexpr Tr kPadLB{"LB"};
inline constexpr Tr kPadRB{"RB"};
inline constexpr Tr kPadA{"A"};
inline constexpr Tr kPadB{"B"};
inline constexpr Tr kPadX{"X"};
inline constexpr Tr kPadY{"Y"};
inline constexpr Tr kPadUnknown{"?"};
// Said once the mod is up, or when it could not start.
inline constexpr Tr kModLoaded{"Arcana loaded"};
inline constexpr Tr kModLoadedNoSpeech{"Arcana loaded, no speech backend"};
inline constexpr Tr kNoEngine{"Arcana could not find the game engine. This game version may be unsupported."};
// A date: "April 6, Monday", then ", holiday" on one (the game's own table abbreviates the weekday: "(Su)").
// A date (calendar_text): {month} the month's name, {day} its number, {th} the English ordinal's ending (st, nd, rd,
// th); a language without one leaves {th} out: "{day} de {month}".
inline constexpr Tr kDateFormat{"{month} {day}{th}"};
inline constexpr Tr kWeekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
inline constexpr Tr kMonths[13] = {"", "January", "February", "March", "April", "May", "June", "July",
                                            "August", "September", "October", "November", "December"};
inline constexpr Tr kHoliday{"holiday"};
// A Persona's stats on its one-line status, in kStatNames' order.
inline constexpr Tr kStatAbbrev[5] = {"St", "Ma", "En", "Ag", "Lu"};
}  // namespace p3a::strings

// std::format("{}", strings::kX): the text in the current language.
template <>
struct std::formatter<p3a::strings::Tr, char> : std::formatter<std::string_view, char> {
  auto format(p3a::strings::Tr t, std::format_context& ctx) const {
    return std::formatter<std::string_view, char>::format(std::string_view(t.c_str()), ctx);
  }
};
