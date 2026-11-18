#include "social_art.h"
#include <algorithm>

namespace p3a::core::social_art {
namespace {
// In the game's order (T_UI_Camp_Commu_Bustup_0100 .. 0105, 0200 .. 0500, 0600, 0601, 0700 .. 2200). The team
// collages are drawn as panels of cut-out faces on bright cyan, tilted and overlapping like snapshots pinned to a
// board; the others are a single figure from the chest up.
const char* const kPictures[] = {
  // 0100: the Fool, the team as it starts
  "A collage of four tilted snapshot panels on bright cyan, the team as it first came together: a light-haired girl "
  "with a big bow at her collar, glancing sideways; an elegant girl with long dark hair falling over one eye; the "
  "joker of the group in a backwards baseball cap, grinning; and, largest, a silver-haired boy with a plaster on his "
  "brow and a calm, fighter's stare. Mismatched frames, one family in the making.",
  // 0101: one more
  "A collage of five tilted snapshot panels on bright cyan: the elegant girl with dark hair over one eye, the "
  "light-haired girl with the bow, the grinning boy in his baseball cap and the silver-haired boy with the plaster "
  "on his brow, and, largest at the front, a newcomer: a shy, short-haired girl with wide gentle eyes and a high "
  "lace-patterned collar. The team is growing.",
  // 0102
  "A collage of six snapshot panels on bright cyan: the silver-haired boy with the plaster on his brow, the joker "
  "in his cap, the light-haired girl, the shy girl with the bob, the elegant girl with her big bow, and, largest, a "
  "blonde girl with round mechanical ear pieces, a calm, glassy gaze and a big bow at a white collar: the android "
  "who joined. The frames crowd closer together.",
  // 0103
  "A collage of seven snapshot panels on bright cyan: the shy girl with the bob, the joker, now sporting a little "
  "goatee and a cap with a peace badge, the light-haired girl, a strip of the android girl's wide eyes, the elegant "
  "girl, the silver-haired boy, and, taking the whole corner, a white Shiba dog with alert ears and his tongue "
  "lolling happily over his collar. Even the dog made the team photo.",
  // 0104
  "A collage of eight snapshot panels on bright cyan: the elegant girl, a big close-up of the silver-haired boy's "
  "plastered brow, the android girl, the light-haired girl, the joker in his cap, the white dog's bright eyes, and, "
  "large at the bottom, a young boy with neat short hair and a serious little face in a school uniform, beside the "
  "shy girl with the bob. A full, busy board of friends.",
  // 0105 (also Judgement's, 2100)
  "A collage of nine snapshot panels on bright cyan, the whole team at last: the joker's eyes under his cap, the shy "
  "girl with the bob, the silver-haired boy, the light-haired girl, a brooding young man in a beanie with a metal "
  "plate and a studded coat collar turned up, the white dog, a strip of the android girl's eyes, the elegant girl "
  "tall in her big bow, and the serious young boy in his uniform. Every face that stood together, crowded into one "
  "frame.",
  // 0200: the Magician
  "A boy with messy, short brown hair, his head tilted, one brow up and a lopsided, easy grin. School blazer with "
  "the crest on the pocket, shirt open at the neck and tie loose. Pure class-clown energy, always up for ramen or "
  "trouble.",
  // 0300: the Priestess
  "A shy girl with a short, rounded bob and a straight fringe, wide gentle eyes and a soft, hesitant look. A high, "
  "lace-patterned collar tied with a ribbon peeks over a dark coat with large round buttons. Quiet, kind and a "
  "little fragile, like she'd apologise for taking up space.",
  // 0400: the Empress
  "A poised young woman with long, wavy hair swept over one eye, heavy-lidded eyes and the faintest cool smile. A "
  "soft white blouse with a huge, floppy bow at the throat. Regal and composed, the untouchable queen of the "
  "school.",
  // 0500: the Emperor
  "A stern young man with slicked-back dark hair, a few strands falling loose, narrowed eyes and a smug half "
  "smile. Blazer buttoned, tie straight, and an official armband on his sleeve. The rules in human form, and he "
  "knows it.",
  // 0600: the Hierophant, the old man
  "An old man with a wild cloud of white hair, bushy brows, a drooping moustache and rectangular glasses on his "
  "nose, leaning forward with a pipe in one hand. He wears a chunky sweater with a zig-zag pattern. A gruff, "
  "grandfatherly bookseller with a soft heart.",
  // 0601: the Hierophant, the old woman
  "A small, stooped old woman with neat white hair, droopy, gentle eyes and a soft, faintly sad mouth. A "
  "leaf-patterned blouse under a dark apron. Sweet and warm, the kind of grandmother who always has a snack for "
  "you.",
  // 0700: the Lovers
  "A pretty girl with short hair flipping out at the ends, her head tilted with a shy, sidelong glance. A choker "
  "with a little heart buckle sits at her throat, above a wide-collared shirt with a big ribbon bow and a ribbed "
  "cardigan. Spirited and popular, but softer than she lets on.",
  // 0800: the Chariot
  "A sporty boy with short, spiky dark hair, sharp eyes and a confident smirk over his shoulder. A high-collared "
  "track jacket zipped to the chin. All athlete's swagger and stubborn pride.",
  // 0900: Justice
  "A girl with long, straight dark hair parted over a high forehead and thin rectangular glasses, one hand "
  "fidgeting at her bow, with a small, nervous smile. Neat school uniform. Bookish and timid, the student council's "
  "quiet treasurer.",
  // 1000: the Hermit
  "Not a person but an avatar: a figure built from blocky polygons and flickering scan lines, like a low-resolution "
  "game character. Spiky angular hair, a pale face half hidden behind a high, armoured collar, one bright eye. The "
  "online friend, all pixels and mystery.",
  // 1100: Fortune
  "A boy with fluffy, curly hair and rectangular glasses, his head tilted with a sweet, slightly bashful smile. A "
  "neat school blazer with the crest on the pocket. Gentle and artistic, a quiet dreamer.",
  // 1200: Strength
  "A sporty girl with short dark hair flicking out behind, a hair clip above one eye, big bright eyes and lips "
  "parted as if mid-sentence. School blazer with a big bow. Energetic and caring, the team's devoted manager.",
  // 1300: the Hanged Man
  "A little girl with her hair in a bun tied with a frilly scrunchie, freckles on her cheeks and a big, happy "
  "smile, hands gripping the straps of a school backpack over an open shirt. A cheerful kid trying very hard to be "
  "fine.",
  // 1400: Death
  "A small boy with messy dark curls and a beauty mark beneath one eye, gazing out with a calm, unreadable "
  "expression. He wears a simple shirt with bold horizontal stripes. Innocent-looking, and quietly uncanny.",
  // 1500: Temperance
  "A boy with a smooth, pale bowl cut, sleepy smiling eyes and a tiny earring, holding open a folding fan painted "
  "with butterflies in front of his school uniform. Dreamy and theatrical, in love with everything traditional.",
  // 1600: the Devil
  "A man in a light, slightly rumpled suit and tie, with shaggy dark hair, a sly sidelong look and a smug, "
  "knowing smirk. Slick, shady charm: the kind of salesman who'd sell you your own wallet.",
  // 1700: the Tower
  "A bald old monk with a deeply lined, scowling face, a thick cigarette pinched between his fingers, in dark robes "
  "with a white collar. Gruff, grumpy and drowning his sorrows, though there's more to him than the frown.",
  // 1800: the Star
  "A lean young man with short dark hair, confident brows and an easy, friendly smirk, in a white zip-up hoodie "
  "with a band of triangles down the sleeve. A star athlete, cheerful and a little cocky.",
  // 1900: the Moon
  "A chubby boy with a single curl sticking up from his hair, droopy, mournful eyes, puffed cheeks and a wobbling "
  "lip. School blazer and a ribbon tie. Comically sorry for himself, and surprisingly full of grand ideas.",
  // 2000: the Sun
  "A thin, pale young man with straight, shoulder-length hair, tired eyes and a wan, strained smile, in a shirt "
  "with bold vertical stripes. Fragile and wistful, looking back over his shoulder.",
  // 2100: Judgement, the whole team (0105's collage)
  "A collage of nine snapshot panels on bright cyan, the whole team together: the joker's eyes under his cap, the "
  "shy girl with the bob, the silver-haired boy, the light-haired girl, a brooding young man in a beanie with a "
  "metal plate and a studded coat collar, the white dog, a strip of the android girl's eyes, the elegant girl tall "
  "in her big bow, and the serious young boy in his uniform. Every face that stood together, crowded into one "
  "frame.",
  // 2200: the Aeon
  "A girl with short blonde hair under a lattice-like metal headpiece, round mechanical ear units and a calm, "
  "gentle gaze. A big bow sits at her white collar, and jointed armour shows at her shoulders. An android with a "
  "very human softness in her eyes.",
};
constexpr int kCount = (int)(sizeof(kPictures) / sizeof(kPictures[0]));
}  // namespace

int picture(int arcana, int person, int fool_members) {
  if (arcana == 1) return std::clamp(fool_members, 0, 5);
  if (arcana >= 2 && arcana <= 5) return arcana + 4;
  if (arcana == 6) return person == 1 ? 11 : 10;
  if (arcana >= 7 && arcana <= 22) return arcana + 5;
  return -1;
}

std::string describe(int pic) { return pic >= 0 && pic < kCount ? kPictures[pic] : ""; }
int pictures() { return kCount; }
}  // namespace p3a::core::social_art
