#include "core/key_name.h"
#include "core/strings.h"
#include <format>

namespace p3a::core {
std::string config_key_name(int v) {
  static const char* kRows = "QWERTYUIOPASDFGHJKLZXCVBNM";
  if (v >= 431 && v <= 440) return std::string(1, kRows[v - 431]);
  if (v >= 441 && v <= 449) return std::string(1, kRows[10 + v - 441]);
  if (v >= 450 && v <= 456) return std::string(1, kRows[19 + v - 450]);
  if (v == 469) return strings::kKeySpace.c_str();
  return std::format("{} {}", strings::kKeyCode, v);
}

const char* punct_key_name(unsigned vk) {
  switch (vk) {
    case 0xBA: return strings::kKeySemicolon;     // VK_OEM_1
    case 0xBB: return strings::kKeyEquals;        // VK_OEM_PLUS
    case 0xBC: return strings::kKeyComma;         // VK_OEM_COMMA
    case 0xBD: return strings::kKeyMinus;         // VK_OEM_MINUS
    case 0xBE: return strings::kKeyPeriod;        // VK_OEM_PERIOD
    case 0xBF: return strings::kKeySlash;         // VK_OEM_2
    case 0xC0: return strings::kKeyGrave;         // VK_OEM_3
    case 0xDB: return strings::kKeyLeftBracket;   // VK_OEM_4
    case 0xDC: return strings::kKeyBackslash;     // VK_OEM_5
    case 0xDD: return strings::kKeyRightBracket;  // VK_OEM_6
    case 0xDE: return strings::kKeyApostrophe;    // VK_OEM_7
    default: return nullptr;
  }
}
}  // namespace p3a::core
