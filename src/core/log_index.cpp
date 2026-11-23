#include "core/log_index.h"
#include <algorithm>

namespace p3a::core {

bool log_record_is(const std::string& r, const std::string& text) {
  if (text.empty()) return false;
  if (r == text) return true;
  return r.size() > text.size() + 2 && r.ends_with(text) && r.compare(r.size() - text.size() - 2, 2, ": ") == 0;
}

std::vector<LogRow> merge_log(const std::vector<std::string>& game, const std::vector<std::string>& records, int skip,
                              int capacity, int depth, int unanchored) {
  int n = (int)game.size();
  int end = std::max(0, (int)records.size() - std::max(0, skip));
  // Each entry's record, newest first: never past the record the newer entry took. An entry that could not be read
  // takes the record just before the newer entry's, as the log was counted before it was read.
  std::vector<int> match(n, -1);
  std::vector<int> owner(end, -1);
  int j = end;
  for (int g = n - 1; g >= 0; --g) {
    if (game[g].empty()) {
      if (j > 0) { match[g] = j - 1; owner[j - 1] = g; j = j - 1; }
      continue;
    }
    for (int k = j - 1; k >= 0 && k >= j - depth; --k) {
      if (log_record_is(records[k], game[g])) { match[g] = k; owner[k] = g; j = k; break; }
    }
  }
  int oldest = -1;
  for (int g = 0; g < n && oldest < 0; ++g) oldest = match[g];
  // A full log has dropped what came before its oldest entry; one with room has kept everything since it was last
  // emptied (a load), so the mod's older lines go before it.
  int from = std::max(0, end - unanchored);
  if (oldest >= 0) from = n >= capacity ? oldest : std::min(from, oldest);
  std::vector<LogRow> rows;
  int next = 0;   // the next entry of the game's to list
  // No entry matched: the game's are older than this session's records, so they come first.
  if (oldest < 0) for (; next < n; ++next) rows.push_back({next, -1});
  for (int k = from; k < end; ++k) {
    if (int g = owner[k]; g >= 0) {
      for (; next < g; ++next) rows.push_back({next, -1});   // entries with no record come before the next matched one
      rows.push_back({g, k});
      next = g + 1;
    } else {
      rows.push_back({-1, k});
    }
  }
  for (; next < n; ++next) rows.push_back({next, -1});
  return rows;
}
}  // namespace p3a::core
