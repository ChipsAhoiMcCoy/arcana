#pragma once
#include <string>
#include "ue/ue.h"

namespace p3a::items {
// id: the game's item id, category << 12 | index in the category's list (0x4003 = Common 3, Bead; 0x6045 = Material
// 69, Turquoise; matched against DatAntiqueShopLineupDataAsset, 2026-10-28).
struct Info { std::string category; uint32_t price = 0, sell = 0; uint16_t attack = 0, accuracy = 0, defence = 0, evasion = 0; int bag = -1; int id = -1; };
bool find(const std::string& name, Info& out);   // by the item's English name (game thread; cached)
std::string stats(const Info& in);                // ", attack 60, accuracy 95" (only the stats the item has)
std::string name_of(int id);                      // an item's English name by id, empty if unknown
int owned(const Info& in);                         // how many the player carries, -1 if unknown
std::string help(int id);                          // its help line (BMD_Item<category>Help), empty if unknown
std::string labelled(int id, const std::string& name);   // a skill card's name as one ("Maragi skill card")
std::string labelled_pickup(const std::string& name);    // a drawn pickup's name, labelled by the ids queued last (game thread)
void install();                                    // registers the item database with the object watcher; /item dev route
}  // namespace p3a::items
