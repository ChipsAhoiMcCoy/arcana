#include "core/release_pick.h"

#include <cstdlib>
#include <vector>

namespace p3a::core {
namespace {
// Just enough JSON for GitHub's answer: objects, arrays, strings (escapes and \u included), numbers, true/false/null.
struct Value {
  enum Kind { Null, Bool, Number, String, Array, Object } kind = Null;
  bool b = false;
  std::string text;               // a string's text, or a number as written
  std::vector<std::string> keys;  // an object's keys, in order
  std::vector<Value> items;       // an object's values (beside its keys) or an array's items

  const Value* get(std::string_view key) const {
    if (kind != Object) return nullptr;
    for (size_t i = 0; i < keys.size(); ++i)
      if (keys[i] == key) return &items[i];
    return nullptr;
  }
  std::string str(std::string_view key) const {
    const Value* v = get(key);
    return v && v->kind == String ? v->text : std::string();
  }
  bool flag(std::string_view key) const {
    const Value* v = get(key);
    return v && v->kind == Bool && v->b;
  }
};

struct Parser {
  std::string_view s;
  size_t at = 0;
  int depth = 0;

  void blanks() {
    while (at < s.size() && (s[at] == ' ' || s[at] == '\t' || s[at] == '\r' || s[at] == '\n')) ++at;
  }
  bool word(std::string_view w) {
    if (s.substr(at, w.size()) != w) return false;
    at += w.size();
    return true;
  }
  static void put_utf8(std::string& out, unsigned cp) {
    if (cp < 0x80) out += (char)cp;
    else if (cp < 0x800) { out += (char)(0xC0 | (cp >> 6)); out += (char)(0x80 | (cp & 0x3F)); }
    else if (cp < 0x10000) { out += (char)(0xE0 | (cp >> 12)); out += (char)(0x80 | ((cp >> 6) & 0x3F)); out += (char)(0x80 | (cp & 0x3F)); }
    else { out += (char)(0xF0 | (cp >> 18)); out += (char)(0x80 | ((cp >> 12) & 0x3F)); out += (char)(0x80 | ((cp >> 6) & 0x3F)); out += (char)(0x80 | (cp & 0x3F)); }
  }
  bool hex4(unsigned& cp) {
    if (at + 4 > s.size()) return false;
    cp = 0;
    for (int i = 0; i < 4; ++i) {
      char c = s[at++];
      cp <<= 4;
      if (c >= '0' && c <= '9') cp |= (unsigned)(c - '0');
      else if (c >= 'a' && c <= 'f') cp |= (unsigned)(c - 'a' + 10);
      else if (c >= 'A' && c <= 'F') cp |= (unsigned)(c - 'A' + 10);
      else return false;
    }
    return true;
  }
  bool string(std::string& out) {
    if (at >= s.size() || s[at] != '"') return false;
    ++at;
    while (at < s.size()) {
      char c = s[at++];
      if (c == '"') return true;
      if (c != '\\') { out += c; continue; }
      if (at >= s.size()) return false;
      char e = s[at++];
      switch (e) {
        case '"': out += '"'; break;
        case '\\': out += '\\'; break;
        case '/': out += '/'; break;
        case 'b': out += '\b'; break;
        case 'f': out += '\f'; break;
        case 'n': out += '\n'; break;
        case 'r': out += '\r'; break;
        case 't': out += '\t'; break;
        case 'u': {
          unsigned cp;
          if (!hex4(cp)) return false;
          if (cp >= 0xD800 && cp < 0xDC00 && s.substr(at, 2) == "\\u") {   // a surrogate pair
            at += 2;
            unsigned lo;
            if (!hex4(lo)) return false;
            if (lo >= 0xDC00 && lo < 0xE000) cp = 0x10000 + ((cp - 0xD800) << 10) + (lo - 0xDC00);
          }
          put_utf8(out, cp);
          break;
        }
        default: return false;
      }
    }
    return false;
  }
  bool value(Value& v) {
    if (++depth > 64) return false;
    blanks();
    if (at >= s.size()) return false;
    bool ok = true;
    char c = s[at];
    if (c == '{') {
      v.kind = Value::Object;
      ++at;
      blanks();
      if (at < s.size() && s[at] == '}') ++at;
      else
        for (;;) {
          blanks();
          std::string key;
          if (!string(key)) { ok = false; break; }
          blanks();
          if (at >= s.size() || s[at] != ':') { ok = false; break; }
          ++at;
          v.keys.push_back(std::move(key));
          v.items.emplace_back();
          if (!value(v.items.back())) { ok = false; break; }
          blanks();
          if (at < s.size() && s[at] == ',') { ++at; continue; }
          if (at < s.size() && s[at] == '}') { ++at; break; }
          ok = false;
          break;
        }
    } else if (c == '[') {
      v.kind = Value::Array;
      ++at;
      blanks();
      if (at < s.size() && s[at] == ']') ++at;
      else
        for (;;) {
          v.items.emplace_back();
          if (!value(v.items.back())) { ok = false; break; }
          blanks();
          if (at < s.size() && s[at] == ',') { ++at; continue; }
          if (at < s.size() && s[at] == ']') { ++at; break; }
          ok = false;
          break;
        }
    } else if (c == '"') {
      v.kind = Value::String;
      ok = string(v.text);
    } else if (word("true")) { v.kind = Value::Bool; v.b = true; }
    else if (word("false")) { v.kind = Value::Bool; }
    else if (word("null")) { v.kind = Value::Null; }
    else {
      size_t start = at;
      while (at < s.size() && (s[at] == '-' || s[at] == '+' || s[at] == '.' || s[at] == 'e' || s[at] == 'E' || (s[at] >= '0' && s[at] <= '9'))) ++at;
      ok = at > start;
      v.kind = Value::Number;
      v.text = std::string(s.substr(start, at - start));
    }
    --depth;
    return ok;
  }
};

bool is_hex64(const std::string& h) {
  if (h.size() != 64) return false;
  for (char c : h)
    if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return false;
  return true;
}

// Markdown made plain for a screen reader: no heading or emphasis marks, links as their text, code as its text.
std::string plain_line(std::string_view line) {
  std::string s(line);
  size_t h = 0;
  while (h < s.size() && s[h] == '#') ++h;
  if (h > 0 && h < s.size() && s[h] == ' ') s = s.substr(h + 1);
  if (s.starts_with("- ") || s.starts_with("* ")) s = s.substr(2);
  std::string out;
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == '[') {   // [text](address) -> text
      size_t close = s.find(']', i);
      if (close != std::string::npos && close + 1 < s.size() && s[close + 1] == '(') {
        size_t end = s.find(')', close);
        if (end != std::string::npos) {
          out += s.substr(i + 1, close - i - 1);
          i = end;
          continue;
        }
      }
    }
    if (s[i] == '`') continue;
    if (s[i] == '*' && i + 1 < s.size() && s[i + 1] == '*') { ++i; continue; }
    out += s[i];
  }
  while (!out.empty() && (out.back() == ' ' || out.back() == '\r')) out.pop_back();
  // a heading ("Battle") is a sentence of its own when read out
  if (!out.empty() && out.back() != '.' && out.back() != '!' && out.back() != '?' && out.back() != ':') out += '.';
  return out;
}
}  // namespace

std::optional<Release> pick_release(std::string_view json, const Version& current) {
  Parser p{json};
  Value root;
  if (!p.value(root) || root.kind != Value::Array) return std::nullopt;
  std::optional<Release> best;
  Version best_v = current;
  for (const Value& r : root.items) {
    if (r.kind != Value::Object || r.flag("draft")) continue;
    Version v = parse_version(r.str("tag_name").c_str());
    if (!v.ok || !newer(v, best_v)) continue;
    const std::string version = std::to_string(v.part[0]) + "." + std::to_string(v.part[1]) + "." + std::to_string(v.part[2]);
    const Value* assets = r.get("assets");
    if (!assets || assets->kind != Value::Array) continue;
    for (const Value& a : assets->items) {
      if (a.kind != Value::Object || a.str("name") != "arcana-" + version + ".zip") continue;
      std::string digest = a.str("digest");
      if (!digest.starts_with("sha256:")) continue;
      digest = digest.substr(7);
      for (char& c : digest)
        if (c >= 'A' && c <= 'F') c = (char)(c - 'A' + 'a');
      std::string url = a.str("browser_download_url");
      if (!is_hex64(digest) || !url.starts_with("https://")) continue;
      Release out;
      out.version = version;
      out.zip_url = url;
      out.sha256 = digest;
      if (const Value* size = a.get("size"); size && size->kind == Value::Number) out.size = std::strtoull(size->text.c_str(), nullptr, 10);
      out.notes = r.str("body");
      best = std::move(out);
      best_v = v;
      break;
    }
  }
  return best;
}

std::string release_notes_text(std::string_view body) {
  std::vector<std::string_view> lines;
  for (size_t at = 0; at <= body.size();) {
    size_t nl = body.find('\n', at);
    if (nl == std::string_view::npos) nl = body.size();
    lines.push_back(body.substr(at, nl - at));
    at = nl + 1;
  }
  auto is_section = [](std::string_view l) { return l.starts_with("## "); };
  size_t from = 0, to = lines.size();
  for (size_t i = 0; i < lines.size(); ++i) {
    std::string lower;
    for (char c : lines[i]) lower += (char)((c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c);
    if (is_section(lines[i]) && lower.find("what's new") != std::string::npos) {
      from = i + 1;
      for (size_t j = from; j < lines.size(); ++j)
        if (is_section(lines[j])) { to = j; break; }
      break;
    }
  }
  std::string out;
  for (size_t i = from; i < to; ++i) {
    std::string l = plain_line(lines[i]);
    if (l.empty()) continue;
    if (!out.empty()) out += '\n';
    out += l;
  }
  return out;
}

std::string hex_digest(const unsigned char (&bytes)[32]) {
  static const char* kHex = "0123456789abcdef";
  std::string out;
  for (unsigned char b : bytes) {
    out += kHex[b >> 4];
    out += kHex[b & 15];
  }
  return out;
}
}  // namespace p3a::core
