#include "doctest.h"
#include <string>
#include "core/calendar_text.h"

using namespace p3a::core;

TEST_CASE("calendar_text: the moon's phase by its age") {
  CHECK(moon_phase(29) == "New moon");
  CHECK(moon_phase(0) == "Waxing crescent moon");
  CHECK(moon_phase(5) == "Waxing crescent moon");
  CHECK(moon_phase(6) == "First quarter moon");
  CHECK(moon_phase(7) == "Waxing gibbous moon");
  CHECK(moon_phase(13) == "Waxing gibbous moon");
  CHECK(moon_phase(14) == "Full moon");
  CHECK(moon_phase(15) == "Waning gibbous moon");
  CHECK(moon_phase(21) == "Waning gibbous moon");
  CHECK(moon_phase(22) == "Last quarter moon");
  CHECK(moon_phase(23) == "Waning crescent moon");
  CHECK(moon_phase(28) == "Waning crescent moon");
}

TEST_CASE("calendar_text: an age the game does not count has no phase") {
  CHECK(moon_phase(-1).empty());
  CHECK(moon_phase(30).empty());
}

TEST_CASE("calendar_text: only the quarters, the full and the new moon are marked") {
  CHECK(moon_mark(6) == "First quarter moon");
  CHECK(moon_mark(14) == "Full moon");
  CHECK(moon_mark(22) == "Last quarter moon");
  CHECK(moon_mark(29) == "New moon");
  for (int age : {-1, 0, 5, 7, 13, 15, 21, 23, 28, 30}) CHECK(moon_mark(age).empty());
}

TEST_CASE("calendar_text: weekdays from Sunday") {
  CHECK(std::string(weekday_name(0)) == "Sunday");
  CHECK(std::string(weekday_name(1)) == "Monday");
  CHECK(std::string(weekday_name(6)) == "Saturday");
  CHECK(std::string(weekday_name(7)).empty());
  CHECK(std::string(weekday_name(-1)).empty());
}

TEST_CASE("calendar_text: a date, weekday and time of day first, then the holiday") {
  CHECK(date_text(5, 8, 3, false, "Evening") == "Wednesday Evening, May 8th");
  CHECK(date_text(4, 6, 1, false, "") == "Monday, April 6th");
  CHECK(date_text(4, 6, 1, false, "Late Night") == "Monday Late Night, April 6th");
  CHECK(date_text(4, 29, 3, true, "Daytime") == "Wednesday Daytime, April 29th, holiday");
  CHECK(date_text(12, 31, 4, true, "") == "Thursday, December 31st, holiday");
  CHECK(date_text(1, 1, 5, false, "") == "Friday, January 1st");
  CHECK(date_text(1, 2, 5, false, "") == "Friday, January 2nd");
  CHECK(date_text(1, 3, 5, false, "") == "Friday, January 3rd");
  CHECK(date_text(1, 11, 5, false, "") == "Friday, January 11th");
  CHECK(date_text(1, 12, 5, false, "") == "Friday, January 12th");
  CHECK(date_text(1, 13, 5, false, "") == "Friday, January 13th");
  CHECK(date_text(1, 22, 5, false, "") == "Friday, January 22nd");
}

TEST_CASE("calendar_text: a weekday out of range leaves it out; a month out of range gives nothing") {
  CHECK(date_text(4, 6, 9, false, "") == "April 6th");
  CHECK(date_text(4, 6, 9, false, "Evening") == "Evening, April 6th");
  CHECK(date_text(0, 6, 1, false, "").empty());
  CHECK(date_text(13, 6, 1, false, "").empty());
}
