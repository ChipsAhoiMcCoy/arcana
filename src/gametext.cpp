#include "gametext.h"
#include "dat.h"
#include "devserver.h"
#include "watch.h"
#include "seh.h"
#include <format>
#include <map>

namespace p3a::gametext {
using namespace ue;

UObject* table(const char* name) {
  // From the object watcher's list: a table not loaded here (the dungeon's, in town) was a full object scan per call.
  // By name and story (DT_SystemTextName has an Episode Aigis copy).
  static const int tables = watch::want("DataTable", true);
  return dat::find(tables, name);
}

std::string system_text(int row) {
  UObject* t = table("DT_SystemTextName");
  uint8_t* r = t ? datatable_find(t, std::to_string(row)) : nullptr;
  if (!r) return {};
  return text(*(FText*)(r + offset_of(datatable_struct(t), "Name")));   // DatNameTable.Name is an FText
}

std::string ui_text(int row) {
  UObject* t = table("DT_UIUseTextName");
  uint8_t* r = t ? datatable_find(t, std::to_string(row)) : nullptr;
  if (!r) return {};
  return text(*(FText*)(r + offset_of(datatable_struct(t), "Name")));
}

std::string time_zone(int tz, bool holiday) {
  // ECldTimeZone 1..9 -> DT_SystemTextName 120..129. 126 is "Daytime": the afternoon (PM, 5) of a holiday, as the
  // date in the corner and the time change show it (their sprite switch, exe+0x1449480 / exe+0x14542b0: PM is the
  // "Daytime" sprite when the day's IsHoliday byte is set, the byte GetNowYasumi reads; Sunday June 7 read
  // "Afternoon" under "Daytime", 2026-11-24).
  static const int rows[10] = {0, 120, 121, 122, 123, 124, 125, 127, 128, 129};
  if (tz < 1 || tz > 9) return {};
  return system_text(tz == 5 && holiday ? 126 : rows[tz]);
}

void install() {
  dev::route("/gametext", [](const dev::Request& r, int&) {
    int row = (int)dev::arg_int(r, "row", 120);
    return dev::on_game([row] {
      UObject* t = table("DT_SystemTextName");
      uint8_t* p = t ? datatable_find(t, std::to_string(row)) : nullptr;
      std::string s = std::format("table #{} {} row {} at {} name off {}\n", t ? index_of(t) : -1, t ? full_name(t) : "", row, (void*)p,
                                  t ? offset_of(datatable_struct(t), "Name") : -1);
      if (p) guarded([&] { s += "text: " + system_text(row) + "\n"; });
      return s;
    });
  }, "?row=N a DT_SystemTextName row, with where it was found");
}
}  // namespace p3a::gametext

