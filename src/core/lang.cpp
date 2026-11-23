#include "lang.h"

#include <atomic>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace p3a::core::lang {
namespace {
struct Lang {
  const char* code;
  const char* name;
};
constexpr Lang kLangs[Count] = {
    {"en", "English"},
    {"ja", "\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E"},                          // 日本語
    {"fr", "Fran\xC3\xA7" "ais"},
    {"it", "Italiano"},
    {"de", "Deutsch"},
    {"es", "Espa\xC3\xB1ol"},
    {"pt", "Portugu\xC3\xAAs"},
    {"pl", "Polski"},
    {"tr", "T\xC3\xBCrk\xC3\xA7" "e"},
    {"ru", "\xD0\xA0\xD1\x83\xD1\x81\xD1\x81\xD0\xBA\xD0\xB8\xD0\xB9"},       // Русский
    {"ko", "\xED\x95\x9C\xEA\xB5\xAD\xEC\x96\xB4"},                          // 한국어
    {"zh-Hans", "\xE7\xAE\x80\xE4\xBD\x93\xE4\xB8\xAD\xE6\x96\x87"},          // 简体中文
    {"zh-Hant", "\xE7\xB9\x81\xE9\xAB\x94\xE4\xB8\xAD\xE6\x96\x87"},          // 繁體中文
};

// A language's lines, English -> translation. Never freed and never changed once published: `tr` hands out pointers
// into it and may run on any thread.
using Table = std::unordered_map<std::string, std::string>;
std::mutex g_mu;                       // loading
Table* g_tables[Count] = {};           // built under g_mu
std::atomic<const Table*> g_live{nullptr};
std::atomic<int> g_current{En};
std::wstring g_root;

std::string unescape(std::string_view s) {
  std::string out;
  out.reserve(s.size());
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == '\\' && i + 1 < s.size()) {
      char n = s[++i];
      if (n == 't') out += '\t';
      else if (n == 'n') out += '\n';
      else if (n == '\\') out += '\\';
      else { out += '\\'; out += n; }   // not an escape: kept as written
    } else {
      out += s[i];
    }
  }
  return out;
}

Table& table(int lang) {
  if (!g_tables[lang]) g_tables[lang] = new Table();
  return *g_tables[lang];
}

int load_locked(int lang, std::string_view text) {
  Table& t = table(lang);
  int n = 0;
  size_t pos = 0;
  if (text.starts_with("\xEF\xBB\xBF")) pos = 3;
  while (pos < text.size()) {
    size_t end = text.find('\n', pos);
    if (end == std::string_view::npos) end = text.size();
    std::string_view line = text.substr(pos, end - pos);
    pos = end + 1;
    if (!line.empty() && line.back() == '\r') line.remove_suffix(1);
    size_t tab = line.find('\t');
    if (tab == std::string_view::npos || tab == 0 || tab + 1 >= line.size()) continue;
    t[unescape(line.substr(0, tab))] = unescape(line.substr(tab + 1));
    ++n;
  }
  return n;
}

void load_files_locked(int lang) {
  if (g_tables[lang] || g_root.empty()) { table(lang); return; }
  table(lang);
  std::error_code ec;
  std::filesystem::path dir = std::filesystem::path(g_root) / kLangs[lang].code;
  for (const auto& e : std::filesystem::directory_iterator(dir, ec)) {
    if (e.path().extension() != ".tsv") continue;
    FILE* f = _wfopen(e.path().c_str(), L"rb");
    if (!f) continue;
    std::string text;
    char buf[65536];
    size_t got;
    while ((got = fread(buf, 1, sizeof buf, f)) > 0) text.append(buf, got);
    fclose(f);
    load_locked(lang, text);
  }
}
}  // namespace

const char* code(int lang) { return lang >= 0 && lang < Count ? kLangs[lang].code : "en"; }
const char* native_name(int lang) { return lang >= 0 && lang < Count ? kLangs[lang].name : kLangs[En].name; }

int from_culture(std::string_view c) {
  auto lower = [](std::string_view s) {
    std::string o(s);
    for (char& ch : o) ch = (char)((ch >= 'A' && ch <= 'Z') ? ch + 32 : ch);
    return o;
  };
  const std::string s = lower(c);
  if (s.starts_with("zh")) {
    // Traditional: zh-Hant, zh-TW, zh-HK, zh-MO; everything else Chinese is Simplified
    if (s.find("hant") != std::string::npos || s.ends_with("-tw") || s.ends_with("-hk") || s.ends_with("-mo"))
      return ZhHant;
    return ZhHans;
  }
  const std::string base = s.substr(0, s.find_first_of("-_"));
  for (int i = 0; i < Count; ++i)
    if (base == kLangs[i].code) return i;
  return -1;
}

void set_root(const std::wstring& dir) {
  std::lock_guard lk(g_mu);
  g_root = dir;
}

void set(int lang) {
  if (lang < 0 || lang >= Count) lang = En;
  const Table* t = nullptr;
  if (lang != En) {
    std::lock_guard lk(g_mu);
    load_files_locked(lang);
    t = g_tables[lang];
  }
  g_live.store(t);
  g_current.store(lang);
}

int current() { return g_current.load(); }

int load_text(int lang, std::string_view tsv) {
  if (lang < 0 || lang >= Count) return 0;
  std::lock_guard lk(g_mu);
  int n = load_locked(lang, tsv);
  if (g_current.load() == lang && lang != En) g_live.store(g_tables[lang]);
  return n;
}

// "@context:text": a word the English uses in two roles ("on" a setting's value, "on" a target) carries a context
// that keeps its translations apart; said in English, the context is left out.
static const char* plain(const char* en) {
  if (en && en[0] == '@')
    if (const char* c = std::strchr(en, ':')) return c + 1;
  return en;
}

std::atomic<int> g_game{En};
std::atomic<const Table*> g_game_live{nullptr};

void set_game(int lang) {
  if (lang < 0 || lang >= Count) lang = En;
  const Table* t = nullptr;
  if (lang != En) {
    std::lock_guard lk(g_mu);
    load_files_locked(lang);
    t = g_tables[lang];
  }
  g_game_live.store(t);
  g_game.store(lang);
}
int game() { return g_game.load(); }

// `shown` holds `en` or one of the game language's alternatives for it (the table's "<prefix><en>" line).
static bool holds(std::string_view shown, const char* prefix, const char* en) {
  if (!en || !*en || shown.empty()) return false;
  if (shown.find(en) != std::string_view::npos) return true;
  const Table* t = g_game_live.load(std::memory_order_acquire);
  if (!t) return false;
  auto it = t->find(std::string(prefix) + en);
  if (it == t->end()) return false;
  std::string_view alts = it->second;
  for (size_t at = 0;;) {
    size_t bar = alts.find('|', at);
    std::string_view a = alts.substr(at, bar == std::string_view::npos ? std::string_view::npos : bar - at);
    if (!a.empty() && shown.find(a) != std::string_view::npos) return true;
    if (bar == std::string_view::npos) return false;
    at = bar + 1;
  }
}
bool names_place(std::string_view shown, const char* en) { return holds(shown, "@place:", en); }
bool says_word(std::string_view lowered, const char* en) { return holds(lowered, "@word:", en); }

int plural_index(long long n, int forms) {
  if (forms <= 1) return 0;
  if (n < 0) n = -n;
  const int l = g_current.load();
  if (forms >= 3 && (l == Ru || l == Pl)) {
    const long long d = n % 10, h = n % 100;
    if (l == Ru ? (d == 1 && h != 11) : n == 1) return 0;
    if (d >= 2 && d <= 4 && (h < 12 || h > 14)) return 1;
    return 2;
  }
  if (l == Fr || l == Pt) return n <= 1 ? 0 : 1;   // 0 and 1 are singular
  return n == 1 ? 0 : 1;
}

const char* tr(const char* en) {
  const Table* t = g_live.load(std::memory_order_acquire);
  if (!t || !en || !*en) return plain(en);
  auto it = t->find(en);
  return it == t->end() ? plain(en) : it->second.c_str();
}

std::string tr(std::string_view en) {
  const Table* t = g_live.load(std::memory_order_acquire);
  if (t && !en.empty())
    if (auto it = t->find(std::string(en)); it != t->end()) return it->second;
  if (en.starts_with('@'))
    if (size_t c = en.find(':'); c != std::string_view::npos) en.remove_prefix(c + 1);
  return std::string(en);
}
}  // namespace p3a::core::lang
