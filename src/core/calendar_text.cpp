#include "core/calendar_text.h"
#include "core/strings.h"
#include <format>

namespace p3a::core {
std::string moon_phase(int age) {
  // Full at 14: April 6 reads 11, April 7 12, and the full moon is April 9 (measured 2026-10-31).
  if (age < 0 || age > 29) return {};
  int i = age == 29 ? 0 : age < 6 ? 1 : age == 6 ? 2 : age < 14 ? 3 : age == 14 ? 4 : age < 22 ? 5 : age == 22 ? 6 : 7;
  return strings::kMoonPhases[i];
}

std::string moon_mark(int age) {
  return age == 6 || age == 14 || age == 22 || age == 29 ? moon_phase(age) : std::string();
}

const char* weekday_name(int weekday) { return weekday >= 0 && weekday < 7 ? strings::kWeekdays[weekday] : ""; }

static const char* ordinal_suffix(int n) {
  if (n % 100 >= 11 && n % 100 <= 13) return "th";
  switch (n % 10) { case 1: return "st"; case 2: return "nd"; case 3: return "rd"; default: return "th"; }
}

// "Wednesday Evening, May 8th" (the player's order, 2026-11-14), then the holiday.
std::string date_text(int month, int day, int weekday, bool holiday, std::string_view time_of_day) {
  if (month < 1 || month > 12) return {};
  std::string s = weekday_name(weekday);
  if (!time_of_day.empty()) { if (!s.empty()) s += ' '; s += time_of_day; }
  if (!s.empty()) s += ", ";
  s += std::format("{} {}{}", strings::kMonths[month], day, ordinal_suffix(day));
  if (holiday) s += std::string(", ") + strings::kHoliday;
  return s;
}
}  // namespace p3a::core
