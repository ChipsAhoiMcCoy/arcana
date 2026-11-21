// The game's online features (config "Network Functions", flag 0x40000068). Neither opens by itself: the game's View
// action (input action 0x33; N on the keyboard) shows it, and N or C closes it.
//  - Voice Answer: during a class question's answers (Event_Extr_330_020/030: NET_START_ANSWER sets
//    AAtlEvtEventManager +0x320, the answer list reaching its input state sets +0x321), how other players answered.
//    AUIVoiceAnswer.pVoiceAnswerDrawActor (+0x340) -> AUIVoiceAnswerDraw: IsGetData (+0x2C8) once the download came,
//    +0x30C int32[4] each answer's percentage (count * 100 / total, FUN_1414b5360). The answers are the choice list's
//    own (the draw keeps the same USelItem at +0x2E8), read here as msg reads them.
//  - Voice Action: in town (not on a Tartarus floor, where the same button is the navigator's), what other players did
//    today. UFldManagerSubsystem.mVoiceActionDisp_ (the AUIVoiceAction) while it is up; its AUIVoiceActionDraw:
//    IsGetData (+0x307), u16 percentages at +0x2BA / +0x2BC / +0x2BE (daily life, Social Links, Tartarus; they sum to
//    100), and each kind's sticky notes, TArray<FBmdPage*> at +0x2C0 / +0x2D0 / +0x2E0 (BMD_ActionRecord pages, up to
//    five drawn). FUN_1414b4f30 builds them, FUN_1414b8e20 copies them into the draw.
#include "screens/screen.h"
#include "screens/util.h"
#include "core/strings.h"
#include "msg.h"
#include "seh.h"
#include "speech.h"
#include <format>

namespace p3a::screens {
using namespace ue;

namespace {
std::string percent_line(const std::string& what, int pct) {
  return std::vformat(strings::kNetPercent, std::make_format_args(what, pct));
}

// One of the two screens: says its title as it opens, then its figures once they have come (at once when the game
// had them already). The review key reads it all again.
class NetScreen : public Screen {
  bool said_ = false;
 protected:
  virtual UObject* draw() = 0;
  virtual bool has_data(UObject* d) = 0;
  virtual std::string figures(UObject* d) = 0;
  virtual const char* title() const = 0;
 public:
  bool active() override { return draw() != nullptr; }
  void enter() override {
    said_ = false;
    screens::set_keys(strings::kNetCloseKeys);
    UObject* d = draw();
    std::string line = title();
    if (d && has_data(d)) { line += ". " + figures(d); said_ = true; }
    else line += ". " + std::string(strings::kNetWaiting);
    speech::speak(line, true);
  }
  void tick() override {
    if (said_) return;
    UObject* d = draw();
    if (d && has_data(d)) { speech::speak(figures(d), false); said_ = true; }
  }
  std::string describe() override {
    UObject* d = draw();
    if (!d) return {};
    return std::string(title()) + ". " + (has_data(d) ? figures(d) : std::string(strings::kNetWaiting));
  }
};

class NetAnswerScreen : public NetScreen {
  Finder answer_{"UIVoiceAnswer"};
 protected:
  UObject* draw() override {
    UObject* a = answer_.get();
    if (!a || !is_live(a)) return nullptr;
    UObject* d = get<UObject*>(a, "pVoiceAnswerDrawActor");
    return d && is_live(d) ? d : nullptr;
  }
  bool has_data(UObject* d) override { return get_bool(d, "IsGetData"); }
  std::string figures(UObject* d) override {
    int pct[4] = {};
    if (!guarded([&] { for (int i = 0; i < 4; ++i) pct[i] = *(int32_t*)((uint8_t*)d + 0x30C + 4 * i); })) return {};
    std::vector<std::string> answers = msg::current().choices;
    size_t n = answers.empty() ? 4 : std::min<size_t>(answers.size(), 4);
    std::string out;
    for (size_t i = 0; i < n; ++i) {
      std::string what = i < answers.size() ? answers[i] : std::to_string(i + 1);
      out += (out.empty() ? "" : ". ") + percent_line(what, pct[i]);
    }
    return out + ".";
  }
  const char* title() const override { return strings::kNetAnswerTitle; }
 public:
  const char* id() const override { return "net_answer"; }
  int priority() const override { return 38; }   // over the class question's choice list (35), under the log (40)
  bool over_messages() const override { return true; }
};

class NetActionScreen : public NetScreen {
  Finder fields_{"FldManagerSubsystem"};
  Finder draw_{"UIVoiceActionDraw"};
 protected:
  UObject* draw() override {
    UObject* f = fields_.get();
    if (!f || !get<UObject*>(f, "mVoiceActionDisp_")) return nullptr;
    UObject* d = draw_.get();
    return d && is_live(d) ? d : nullptr;
  }
  bool has_data(UObject* d) override { return get_bool(d, "IsGetData"); }
  std::string figures(UObject* d) override {
    std::string out;
    for (int k = 0; k < 3; ++k) {
      int pct = 0;
      std::vector<void*> pages;
      guarded([&] {
        pct = *(uint16_t*)((uint8_t*)d + 0x2BA + 2 * k);
        auto* notes = (TArray<void*>*)((uint8_t*)d + 0x2C0 + 0x10 * k);
        for (int i = 0; notes->data && i < notes->num && i < 5; ++i) pages.push_back(notes->data[i]);
      });
      std::string line = percent_line(strings::kNetActionKinds[k], pct);
      std::string said;
      for (void* p : pages)
        if (std::string t = msg::page_string(p); !t.empty()) said += (said.empty() ? "" : ", ") + t;
      if (!said.empty()) line += ": " + said;
      out += (out.empty() ? "" : ". ") + line;
    }
    return out + ".";
  }
  const char* title() const override { return strings::kNetActionTitle; }
 public:
  const char* id() const override { return "net_action"; }
  int priority() const override { return 30; }
};
}  // namespace

std::unique_ptr<Screen> make_net_answer() { return std::make_unique<NetAnswerScreen>(); }
std::unique_ptr<Screen> make_net_action() { return std::make_unique<NetActionScreen>(); }

// The class question's answers offer the other players' answers (AAtlEvtEventManager +0x320 the event asked for it,
// +0x321 the answer list was handed over), with Network Functions on.
bool net_answer_offered() {
  static Finder manager{"AtlEvtEventManager"};
  UObject* m = manager.get();
  if (!m) return false;
  bool on = false;
  guarded([&] { on = *((uint8_t*)m + 0x320) && *((uint8_t*)m + 0x321); });
  return on;
}
}  // namespace p3a::screens
