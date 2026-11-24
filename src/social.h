#pragma once
#include <string>
#include <vector>
#include "ue/ue.h"

namespace p3a::social {
struct Link { int arcana; int rank; int points; };   // arcana 1 Fool .. 22 Aeon; rank 0 = not established
std::vector<Link> read();                // every link record (game thread)
std::string arcana_name(int id);
int rank(int id);                        // the link's rank, 0 before it is formed
std::string formed_arcana(int id);       // the arcana once the link is formed, else "Unknown Arcana" (no spoilers)
std::string person(int id);              // the partner's name as the camp shows it ("Kenji Tomochika")
std::string partner_rank(const std::string& name);   // "Magician, rank 3" (", ready to rank up") when `name` is an established link's partner
int partner_arcana(const std::string& name);         // the arcana of the established link whose partner `name` names, else 0
int community_arcana(const std::string& label);      // the established link the game labels `label` ("Track Team": its CommunityName), else 0
std::string arcana_rank(int arcana);                 // "Chariot, rank 2" (", reversed" or ", ready to rank up") for an established link, else ""
bool reversed(int id);                   // the link is reversed (story flag; game thread)
bool ready(const Link& l);               // the game's own test (the town map's blue card): the next hangout ranks it up
bool ready(int arcana);
std::string describe(const Link& l);     // "Magician (Classmate), rank 3", then ", reversed" or ", ready to rank up"
std::string summary();                   // every established link
std::vector<std::string> summary_parts();   // the same, the count then a link per part (spoken one utterance each)
void tick();                             // announces new links, rank ups, points and reversals
// The rank card is up showing this link at this rank (screens/rank_up.cpp, every tick while it is up): the card
// speaks the change, so tick() leaves that rank to it. Returns what happened ("New Social Link") and what the card
// shows ("Magician Social Link, Kenji Tomochika, rank 1").
struct Card { std::string what, line; };
Card card(int arcana, int rank);
void install();                          // hooks CMM_RANKUP (the rank card's flowscript command); /social dev route
}  // namespace p3a::social
