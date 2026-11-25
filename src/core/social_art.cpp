#include "social_art.h"
#include "lang.h"
#include <algorithm>

namespace p3a::core::social_art {
namespace {
// In the game's order (T_UI_Camp_Commu_Bustup_0100 .. 0105, 0200 .. 0500, 0600, 0601, 0700 .. 2200). The team
// collages are drawn as panels of cut-out faces on bright cyan, tilted and overlapping like snapshots pinned to a
// board; the others are a single figure from the chest up.
const char* const kPictures[] = {
  // 0100: the Fool, the team as it starts
  "Four tilted snapshot panels on cyan, the team as it first came together. A light-haired girl with a "
  "heart-buckled choker and a big bow gives a cool smile; an elegant girl glances sideways through dark hair "
  "falling over one eye; a goateed boy in a backwards cap peers up; and largest, a silver-haired boy with a plaster "
  "on his brow stares straight out. Four strangers, framed side by side.",
  // 0101: one more
  "Five tilted snapshot panels on cyan. The elegant girl with dark hair over one eye, the light-haired girl with "
  "her heart choker, the boy in the backwards cap and the silver-haired boy with the plaster on his brow crowd the "
  "top, and largest at the front is a newcomer: a short-haired girl with wide, gentle eyes and a high flowered "
  "collar. The circle has opened to let one more in.",
  // 0102
  "Six snapshot panels on bright cyan, packed closer now. Small frames hold the silver-haired boy with his plaster, "
  "the boy in the cap, the light-haired girl's eyes and the short-haired girl's soft face; the elegant girl leans "
  "in large, a big bow at her throat. Largest of all, a blonde girl with round mechanical ear pieces and a big bow "
  "at a white collar looks straight out, calm and glassy-eyed.",
  // 0103
  "Seven snapshot panels on cyan, in a staggered column. The short-haired girl, the goateed boy in a cap with a "
  "peace badge, the light-haired girl, a strip of the blonde girl's wide eyes, the elegant girl and the "
  "silver-haired boy fill the small frames. The tallest panel belongs to a white dog, a collar at his neck and his "
  "tongue lolling happily. Even he has a place in the picture.",
  // 0104
  "Eight snapshot panels on bright cyan, a full board of faces. Across the top, the elegant girl's eye under her "
  "dark hair and a big close-up of the silver-haired boy's plastered brow; below, the blonde girl, the light-haired "
  "girl, the boy in the cap and the white dog's watchful eyes. Large at the bottom, a young boy in blazer and tie "
  "gazes out, serious, beside the short-haired girl.",
  // 0105 (also Judgement's, 2100)
  "Nine snapshot panels on cyan, the whole team like a wall of photographs. The boy in the cap, the short-haired "
  "girl, the silver-haired boy, the light-haired girl, the white dog, the blonde girl's wide eyes and the young boy "
  "in his tie look out. A brooding young man in a beanie turns up his studded collar with a faint smile, and the "
  "elegant girl stands tallest in her big bow.",
  // 0200: the Magician
  "A boy drawn in cool blue ink in the lower corner, his head cocked to one side under a mop of messy dark hair. "
  "One brow is hitched up, his eyes slide sideways and his mouth twists into a lopsided, doubtful line. His school "
  "blazer hangs loose over a white shirt and dark tie. He looks easygoing and a little sceptical, as if weighing "
  "whether you are kidding.",
  // 0300: the Priestess
  "A shy girl drawn in cool blue ink, small in the lower corner, her head tipped gently to one side. A short, "
  "rounded bob with a jagged fringe frames wide dark eyes and a small closed mouth. A high collar printed with "
  "flowers, its white ribbon loose at one side, rises from a dark coat with large round buttons. She holds herself "
  "small and still, hopeful and unsure.",
  // 0400: the Empress
  "A tall girl drawn in cool blue ink, turned half away and looking back over her shoulder, long heavy hair falling "
  "in waves down her back and a lock sweeping across one eye. Her gaze slides sideways from under lowered lids, her "
  "lips closed and unsmiling. A huge soft bow spills from the collar of her white jacket, its loops and tails "
  "hanging to her chest. She regards you coolly, from a distance she means to keep.",
  // 0500: the Emperor
  "A young man drawn in cool blue ink, his dark hair slicked back with one strand curling loose over his forehead "
  "and the ends flicking out at his neck. His eyes cut sideways under a sharply arched brow, and his lips press "
  "into a thin, satisfied smirk. Blazer neat, tie straight, an official armband on his sleeve. He looks pleased "
  "with himself and quick to judge.",
  // 0600: the Hierophant, the old man
  "An old man drawn in cool blue ink, leaning forward out of the corner with a pipe cupped in one hand. A wild "
  "cloud of white hair surrounds a deeply lined face with an age spot at one temple. Heavy-lidded eyes peer over "
  "rectangular glasses slipped down his nose, above a bushy moustache and pursed lips. His chunky sweater is "
  "knitted in zigzags. He looks weary and gruff, but patient.",
  // 0601: the Hierophant, the old woman
  "A small, stooped old woman drawn in cool blue ink, her shoulders rounded and her head bowed forward. Neat white "
  "hair is combed back from a lined forehead, and her droopy eyes look out above a small mouth turned down. She "
  "wears a blouse printed with climbing leaves under a dark apron with round buttons on its straps. Soft and "
  "patient, she seems to carry a quiet sorrow without complaint.",
  // 0700: the Lovers
  "A girl drawn in cool blue ink, her head tipped to one side so her short hair swings out at the ends. Her eyes "
  "look up at you, and her lips hold the faintest closed smile. A choker with a heart-shaped buckle circles her "
  "throat above a wide pointed collar, a big ribbon bow and a ribbed cardigan. She seems poised and a little "
  "guarded, testing you before she warms.",
  // 0800: the Chariot
  "A sporty boy drawn in cool blue ink, turned half away and looking back over his shoulder. His short dark hair "
  "spikes up and back, and his narrow eyes slide sideways above a crooked, confident smirk. A high-collared track "
  "jacket with white stripes down the sleeves is zipped nearly to his chin. He carries himself loose and sure, "
  "proud and quick to rise to a challenge.",
  // 0900: Justice
  "A girl drawn in cool blue ink, long straight dark hair parted over a high forehead and falling past her "
  "shoulders. Thin rectangular glasses sit on her nose, and her eyes glance up and aside above a small, uncertain "
  "smile. One hand is raised to her chest, fingers curled at the soft bow of her school uniform. She seems careful "
  "and shy, as if hoping she said the right thing.",
  // 1000: the Hermit
  "Not a person but an avatar, built from flat, angular polygons and striped with scan lines like an old screen. A "
  "smooth capped head sits over spiky hair that flares out sideways in jagged points; a single pale eye shows, and "
  "a high, blocky collar hides the face below it. The coat is marked with stripes and arrowheads. Faceless and "
  "guarded, it keeps whoever is behind it out of sight.",
  // 1100: Fortune
  "A boy drawn in cool blue ink, his head tilted, a soft mop of curly hair spilling over his brow and ears. "
  "Rectangular glasses sit crooked on his nose, his eyes glance sideways and his closed lips curl into a small, "
  "bashful smile. He wears a neat school blazer and dark tie, the crest on its pocket. Gentle and a touch awkward, "
  "he seems pleased and embarrassed at once.",
  // 1200: Strength
  "A girl drawn in cool blue ink, her head turned toward you, short dark hair gathered into a little tail that "
  "sticks out behind and a hairpin clipped above one eye. Her big round eyes are wide and her lips parted, as if "
  "about to speak up. A soft bow sits at the collar of her school blazer. She looks earnest and eager, ready to "
  "help before she is asked.",
  // 1300: the Hanged Man
  "A little girl drawn in cool blue ink, both hands gripping the straps of a stiff school satchel on her back. Her "
  "dark hair is pulled smoothly back into a braided bun wrapped in a frilly scrunchie, a few freckles dot her "
  "cheeks, and she smiles up at you with round, bright eyes. An open shirt hangs over a plain T-shirt. She looks "
  "cheerful and determined, holding on tight.",
  // 1400: Death
  "A small boy drawn in cool blue ink, his head tipped slightly, a tousled mop of dark hair falling over his brow. "
  "Large, pale eyes gaze straight out, a beauty mark beneath one, and his small mouth rests in a flat, unreadable "
  "line. He wears a plain buttoned shirt in bold horizontal stripes. Innocent and very still, he watches with a "
  "calm that seems older than he is.",
  // 1500: Temperance
  "A boy drawn in cool blue ink, holding a dark folding fan open beside his face, painted with butterflies and "
  "grasses. His hair is a pale bowl cut with a blunt fringe, a small earring at one ear, and his eyes and gentle "
  "closed smile look dreamily past you. Beneath the fan, his school blazer. Serene and a little theatrical, he "
  "poses as if on a stage of his own.",
  // 1600: the Devil
  "A man drawn in cool blue ink, his head cocked and shoulders slouched, shaggy dark hair falling untidily around a "
  "long face. Heavy-lidded eyes slide sideways at you under one raised brow, and his mouth tugs up at one corner in "
  "a sly, knowing smirk. He wears a pale suit with a loosened dark tie. Shifty and amused, he looks like a man "
  "sizing up what you are worth.",
  // 1700: the Tower
  "A bald old monk drawn in cool blue ink, chin lifted and glaring down his nose, his brow knotted and his mouth "
  "pulled into a deep, sour frown. He holds a thick cigar up near his chin in a hand crowded with heavy rings. Dark "
  "robes cross over a white collar, a strap running over one shoulder. Gruff and defiant, he scowls like a man "
  "daring anyone to lecture him.",
  // 1800: the Star
  "A lean young man drawn in cool blue ink, facing you with his head held level, short dark hair spiking at the "
  "edges. Strong straight brows sit over clear, steady eyes, and one corner of his mouth lifts in an easy, "
  "confident half smile. He wears a white zip-up hoodie, a dark band of triangles running down the sleeve. Relaxed "
  "and self-assured, he looks ready for whatever comes next.",
  // 1900: the Moon
  "A heavyset boy drawn in cool blue ink, his round head drooping to one side, one curl sprouting up from the crown "
  "and another looping onto his forehead. His heavy-lidded eyes sag under sloping brows, and his full cheeks puff "
  "around a pouting, wobbling lip. A school blazer strains over his shirt and loose tie. He looks thoroughly sorry "
  "for himself, and quite sure the world owes him better.",
  // 2000: the Sun
  "A thin, pale young man drawn in cool blue ink, his head tilted back and turned aside, gazing up and away. "
  "Straight hair falls to his jaw. His brows lift in a worried slant and his lips press into a strained, wavering "
  "smile. A shirt in bold vertical stripes hangs open at the neck over sharp collarbones. Fragile and wistful, he "
  "seems lost in a thought he cannot finish.",
  // 2100: Judgement, the whole team (0105's collage)
  "Nine snapshot panels on cyan, the whole team like a wall of photographs. The boy in the cap, the short-haired "
  "girl, the silver-haired boy, the light-haired girl, the white dog, the blonde girl's wide eyes and the young boy "
  "in his tie look out. A brooding young man in a beanie turns up his studded collar with a faint smile, and the "
  "elegant girl stands tallest in her big bow.",
  // 2200: the Aeon
  "A girl drawn in cool blue ink, facing you with her head tilted slightly, short pale hair framing her face "
  "beneath a lattice-like metal headpiece. Round mechanical units cover her ears, and her large eyes look out "
  "calmly over softly closed lips. A big ribbon bow sits at a high white collar, and jointed armour plates cap her "
  "shoulders. Machine-made and gentle, she seems quietly attentive, almost tender.",
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

std::string describe(int pic) { return pic >= 0 && pic < kCount ? lang::tr(kPictures[pic]) : ""; }   // in the mod's language
int pictures() { return kCount; }
}  // namespace p3a::core::social_art
