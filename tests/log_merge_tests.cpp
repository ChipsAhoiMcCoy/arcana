#include "doctest.h"
#include "core/log_index.h"

using p3a::core::LogRow;
using p3a::core::merge_log;

namespace {
// Rows as "g<row>" (with "=r<record>" when matched) or "r<record>" for a line only the mod recorded.
std::string show(const std::vector<LogRow>& rows) {
  std::string s;
  for (auto& r : rows) {
    if (!s.empty()) s += " ";
    if (r.game >= 0) s += "g" + std::to_string(r.game) + (r.record >= 0 ? "=r" + std::to_string(r.record) : "");
    else s += "r" + std::to_string(r.record);
  }
  return s;
}
}  // namespace

TEST_CASE("log_record_is: the same line, or after a speaker") {
  using p3a::core::log_record_is;
  CHECK(log_record_is("Yes.", "Yes."));
  CHECK(log_record_is("Junpei Iori: Yo!", "Yo!"));
  CHECK(log_record_is("Thinking: Hm.", "Hm."));
  CHECK_FALSE(log_record_is("Junpei Iori: Yo!", "o!"));
  CHECK_FALSE(log_record_is("Yo!", ""));
}

TEST_CASE("merge_log: the navigator's remarks the game leaves out of its log go between its entries") {
  std::vector<std::string> game = {"Hi.", "Bye."};
  std::vector<std::string> rec = {"Yukari Takeba: Hi.", "Mitsuru Kirijo: I'm sensing a locked treasure chest.",
                                  "Junpei Iori: Bye.", "Mitsuru Kirijo: Be careful."};
  CHECK(show(merge_log(game, rec, 0)) == "g0=r0 r1 g1=r2 r3");
}

TEST_CASE("merge_log: an empty game log (Tartarus) lists the mod's records") {
  std::vector<std::string> rec = {"Mitsuru Kirijo: I'm sensing a locked treasure chest on this floor!"};
  CHECK(show(merge_log({}, rec, 0)) == "r0");
  CHECK(show(merge_log({}, {}, 0)).empty());
  // Only the newest `unanchored` records.
  std::vector<std::string> many = {"a", "b", "c", "d"};
  CHECK(show(merge_log({}, many, 0, 30, 60, 2)) == "r2 r3");
}

TEST_CASE("merge_log: records older than a full log's oldest entry are left out") {
  std::vector<std::string> game = {"B.", "C."};
  std::vector<std::string> rec = {"A.", "Navi: old remark.", "B.", "C."};
  CHECK(show(merge_log(game, rec, 0, 2)) == "g0=r2 g1=r3");
  // A log with room kept everything since a load: the navigator's remark before the first talk is listed.
  CHECK(show(merge_log(game, rec, 0)) == "r0 r1 g0=r2 g1=r3");
}

TEST_CASE("merge_log: the page on screen the game has not logged is skipped") {
  std::vector<std::string> game = {"A."};
  std::vector<std::string> rec = {"A.", "Description: rain.", "B."};
  CHECK(show(merge_log(game, rec, 1)) == "g0=r0 r1");
  CHECK(show(merge_log(game, rec, 0)) == "g0=r0 r1 r2");
}

TEST_CASE("merge_log: entries with no record (before this session, unreadable) keep their place") {
  // The oldest entries are from before this session.
  std::vector<std::string> game = {"Old.", "Older line.", "A."};
  std::vector<std::string> rec = {"A.", "Navi: hm."};
  CHECK(show(merge_log(game, rec, 0)) == "g0 g1 g2=r0 r1");
  // An unreadable entry between two matched ones.
  std::vector<std::string> game2 = {"A.", "", "C."};
  std::vector<std::string> rec2 = {"A.", "B.", "C."};
  CHECK(show(merge_log(game2, rec2, 0)) == "g0=r0 g1=r1 g2=r2");
  // An answer the game's store gave no line for, after a remark only the mod recorded (Tartarus, 2026-11-23).
  CHECK(show(merge_log({"Hi.", ""}, {"Mitsuru Kirijo: A chest.", "Junpei Iori: Hi.", "Later."}, 0)) == "r0 g0=r1 g1=r2");
  // No entry matched at all: the game's first, then the newest records.
  CHECK(show(merge_log({"X."}, {"Y."}, 0)) == "g0 r0");
}

TEST_CASE("merge_log: a repeated line matches the newest record that fits the order") {
  std::vector<std::string> game = {"...", "Go.", "..."};
  std::vector<std::string> rec = {"...", "Go.", "Navi: careful.", "..."};
  CHECK(show(merge_log(game, rec, 0)) == "g0=r0 g1=r1 r2 g2=r3");
}
