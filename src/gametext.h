#pragma once
#include <string>
#include "ue/ue.h"

namespace p3a::gametext {
// The game's own words, from its data tables (game thread).
std::string system_text(int row);                 // DT_SystemTextName row "<row>" (Name)
std::string ui_text(int row);                     // DT_UIUseTextName row "<row>" (Name): menu labels ("Armor")
std::string time_zone(int tz, bool holiday = false);   // ECldTimeZone -> "Late Night" (rows 120..129); "Daytime" on a holiday
ue::UObject* table(const char* name);             // a DataTable by object name, cached
void install();                                   // /gametext dev route
}  // namespace p3a::gametext
