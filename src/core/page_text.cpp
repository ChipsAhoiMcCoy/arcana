#include "core/page_text.h"
#include "core/strings.h"
#include "core/text_clean.h"
#include <cctype>

namespace p3a::core {
const char* icon_key(int id, bool pad, bool battle, std::string_view around) {
  const strings::IconKey* key = nullptr;
  for (auto& k : strings::kIconKeys) if (k.id == id) key = &k;
  if (!key) return nullptr;
  if (pad) return key->pad;
  std::string a(around);
  for (auto& ch : a) ch = (char)tolower((unsigned char)ch);
  auto says = [&](std::string_view w) { return a.find(w) != std::string::npos; };
  auto nearby = [&](std::string_view w) { return !battle && says(w); };   // a field key: not while the battle is up
  // A battle's keys where the battle screen is up or the sentence is about battle: the game names them so on its
  // battle tutorials wherever they are read (the Tutorial list too, 2026-11-15: "Pressing H during battle will let you
  // Rush" where the game draws Tab).
  bool fight = battle || says("battle") || says("tactics") || says("survey");
  switch (id) {
    case 104: return fight ? strings::kIconUpBattle : key->keyboard;     // battle Tactics; field zoom in
    case 105: return fight ? strings::kIconDownBattle : key->keyboard;   // battle Survey; field camera reset
    case 108: return fight || says("rush") ? strings::kIconRushBattle : key->keyboard;   // battle Rush; the field's save
    case 111: return battle && !says("sword") ? strings::kIconItemsBattle : key->keyboard;   // battle Items; the field's strike
    case 112: return nearby("menu") ? strings::kIconMenuField : key->keyboard;   // battle skills (Persona); the field menu
    case 114: return nearby("map") ? strings::kIconMapField : key->keyboard;     // previous page; the field map
    case 117:   // next page (and the next Persona); Assist in battle; Auto-Recover in Tartarus
      if (says("assist")) return strings::kIconAssistBattle;
      return nearby("exploration") || nearby("recover") ? strings::kIconRecoverField : key->keyboard;
    case 118: return battle || says("theurgy") ? strings::kIconTheurgyBattle : key->keyboard;   // battle Theurgy; the field's dash
    default: return key->keyboard;
  }
}

std::string finish_icons(std::string out, bool pad, bool battle) {
  // The sentence around a button decides its key: from the last full stop before it to the next one after.
  for (size_t p; (p = out.find(kIconByPlace)) != std::string::npos && p + 1 < out.size();) {
    int id = (unsigned char)out[p + 1];
    size_t from = out.rfind('.', p), to = out.find('.', p);
    if (from == std::string::npos) from = 0;
    std::string around = out.substr(from, (to == std::string::npos ? out.size() : to) - from);
    const char* name = icon_key(id, pad, battle, around);
    out.replace(p, 2, name ? name : "");
  }
  for (size_t p; (p = out.find(kIconGlyph)) != std::string::npos;) {
    bool dropped = p + 1 >= out.size() || isalnum((unsigned char)out[p + 1]);
    out.replace(p, 1, dropped ? "" : strings::kAKey);
  }
  return out;
}

std::string rows_as_list(const std::vector<std::string>& rows, std::string_view joined) {
  std::vector<std::string> kept;
  for (auto& r : rows) if (std::string c = clean_text(r); !c.empty()) kept.push_back(c);
  if (kept.size() < 2) return {};
  std::string spaced, listed;
  for (size_t i = 0; i < kept.size(); ++i) {
    const std::string& r = kept[i];
    if (r.find_first_of(".,!?:;") != std::string::npos) return {};
    if (i && !isupper((unsigned char)r[0]) && !isdigit((unsigned char)r[0])) return {};
    spaced += (i ? " " : "") + r;
    listed += (i ? ", " : "") + r;
  }
  return spaced == joined ? listed : std::string{};
}

int declared_cue(const uint8_t* d, size_t size, bool any) {
  if (!d) return 0;
  for (size_t i = 0; i < 96 && i + 2 < size && d[i] == 0xFE;) {
    uint8_t f = d[i + 1];
    int argc = (f & 0x0F) - 1;
    if ((f & 0xF0) != 0xF0 || argc < 0) return 0;
    if (d[i + 2] == 0x61 && argc >= 4) {
      if (i + 10 >= size) return 0;
      if (any || (d[i + 3] == 0x02 && d[i + 4] == 0x01)) return (d[i + 9] - 1) + (d[i + 10] - 1) * 256;   // low byte, then high byte, each stored plus one
    }
    i += 3 + (size_t)argc * 2;
  }
  return 0;
}
bool declares_voice(const uint8_t* d, size_t size, bool any) { return declared_cue(d, size, any) != 0; }
int declared_voice_type(const uint8_t* d, size_t size) {
  if (declared_cue(d, size, true) == 0) return -1;
  for (size_t i = 0; i + 4 < size && d[i] == 0xFE;) {   // the same walk: find the function declared_cue found
    int argc = (d[i + 1] & 0x0F) - 1;
    if (d[i + 2] == 0x61 && argc >= 4) return (d[i + 3] - 1) + (d[i + 4] - 1) * 256;
    i += 3 + (size_t)argc * 2;
  }
  return -1;
}
}  // namespace p3a::core
