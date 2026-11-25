// How the Personas and Shadows look (included by look_text.cpp), written from renders of the game's own 3D models
// and textures (research tools, 2026-11-17). Model keys: Ps<group>_<variant> a Persona's, Em<family>_<variant> a
// Shadow's (BP_Em<family>_<variant>; siblings of one family are recolours), Human_<name> a person fought.
const Model kModels[] = {
  {"Em0001_000",  // 検証用のマーヤ
        "A small, squat blob of black tar-like ooze spread across the floor like a spilled puddle, with a rounded "
        "hump in the middle and two long, thin, knobbly arms rising straight up from it, each ending in a spindly "
        "hand with needle-pointed fingertips and a thorny, curling thumb. Pressed onto the front of the hump is a "
        "teal-blue mask of a long, solemn face, marked with the numeral I on its brow: big round black eyeholes, "
        "a long straight nose and a small downturned mouth, pinned on with little silver bolts. It's the humblest "
        "of Shadows, a puddle of gloom groping upward, glum and grasping."},
  {"Em0001_001",  // Merciless Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Instead of a full face it wears a magenta-pink "
        "masquerade half-mask over the top of the hump, its edges flaring out like butterfly wings, with narrow, "
        "heavy-lidded eye slits and the numeral II at its side. Sly and coquettish behind that party mask, it's a "
        "puddle of shadow with a cruel streak."},
  {"Em0001_002",  // Frivolous Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is cream-white and shaped like a crown, "
        "three sharp points standing up along the top edged in thin gold, with the numeral III on the brow and "
        "calm, closed, smiling eyes. It looks pleased with itself, a little puddle of darkness playing at royalty "
        "without a care in the world."},
  {"Em0001_003",  // Haughty Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a showy lavender-purple affair marked "
        "IV: narrow eyeholes under a crest of spiky prongs fanning up like antlers, with two long, curving prongs "
        "sweeping down past the chin. That grand, thorny headpiece makes it look puffed up and lordly, sneering "
        "down from a body that's barely more than a spill."},
  {"Em0001_004",  // ?
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a steel-blue shield shape, wide at "
        "the top and narrowing to a point at the chin, marked V, with two slanted dark eyeholes and a little "
        "triangular hole for a mouth, as if caught mid-yawn. Slack and dull-eyed, it seems far too lazy to bother "
        "being frightening."},
  {"Em0001_005",  // ?
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a rosy crimson-pink face marked VI, "
        "with brows tilted up in a pitiful, worried slant, drooping eyes and a small mouth open in a sorrowful "
        "frown. It looks forlorn and pleading, though those clawed hands reaching up suggest the sad face is only "
        "a lure."},
  {"Em0001_006",  // Ill-Fated Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a bright yellow shield like a "
        "knight's visor, marked VII, smooth and blank but for a thick black T across it: two heavy slashes for "
        "brows meeting a black stripe down the nose. Faceless and grim behind that warning-yellow plate, it has "
        "the air of something doomed and dooming."},
  {"Em0001_007",  // ?
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a deep royal-blue face, smooth and "
        "serene, with almond eyeholes, a fine straight nose and full lips, a small white diamond outlined on the "
        "brow beside the numeral XI. Calm and almost beautiful, it gazes out with an unsettling, gut-level hunger "
        "beneath the composure."},
  {"Em0001_008",  // Desirous Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is burnt orange and round, marked IX, "
        "with a single dark hole at its centre ringed by a raised rim like one staring eye, and a jaw of long "
        "tooth-like grooves hanging below, half skull, half dial. That one wide, empty eye gives it a fixed, "
        "wanting stare."},
  {"Em0001_009",  // Imprudent Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a glossy emerald-green oval marked X, "
        "with two black spirals for eyes stacked one above the other, joined by a looping line, and a huge black "
        "crescent grin across the bottom. Dizzy, giddy and grinning, it looks like it would leap into anything "
        "without a second thought."},
  {"Em0001_010",  // Bigoted Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a pale sage-green shield with a "
        "pointed chin and no face at all, only a bold black cross running down and across it, and the numeral "
        "VIII at the top. Blank and rigid behind that cross, it has the narrow, unbending air of a zealot."},
  {"Em0001_011",  // Devious Maya
        "A small, squat blob of black tar-like ooze spread across the floor like a puddle, with a rounded hump in "
        "the middle and two long, thin, knobbly arms rising straight up, each ending in a spindly hand with "
        "needle-pointed fingertips and a thorny, curling thumb. Its mask is a soft slate-grey face, round and "
        "puffy, with heavy-lidded, sleepily closed eyes, a broad nose and the numeral XII low on the face. Its "
        "drowsy, smug calm is the most unreadable of its kind, as if it is quietly plotting while pretending to "
        "doze."},
  {"Em0011_000",  // White Hand
        "A giant hand turned upside down that walks on its fingers: a crisp white glove whose wrist rises into a "
        "short neck and a round, egg-shaped black head. On the back of the hand is a cream tuxedo shirtfront with "
        "fine pleats and three dark buttons, and a little red bow tie sits at the neck. The face is a teal-blue "
        "mask marked I, long and solemn, with round black eyeholes, a long nose and a downturned mouth, bolted on "
        "with small silver spikes. Dressed up like a stage magician's assistant, it's a dapper, eerie conjuring "
        "trick come to life."},
  {"Em0011_001",  // Pink Hand
        "A giant hand turned upside down that walks on its fingers: a fluffy pink knitted glove patterned with "
        "white leafy flowers, its wrist rising into a short neck and a round, egg-shaped black head. At the neck "
        "sits a frilled collar of pink lace over a gaudy necklace of gold filigree, pearls and little gems, and "
        "one finger wears a chunky gold ring set with a huge faceted aqua gemstone. The face is the teal-blue "
        "mask marked I, long and glum, with round black eyeholes, bolted on with silver spikes. Frilly, sparkly "
        "and a little tacky, it flounces about like a showgirl."},
  {"Em0011_002",  // Black Hand
        "A giant hand turned upside down that walks on its fingers: a glossy black leather glove whose wrist "
        "rises into a short neck and a round, egg-shaped black head. Around the neck is a spiked metal collar, "
        "and down the back of the hand runs a grey leather panel edged with silver studs and fastened by three "
        "buttons shaped like tiny skulls. The face is the teal-blue mask marked I, long and glum, with round "
        "black eyeholes, bolted on with silver spikes. All black leather, spikes and skulls, it's the tough, "
        "menacing punk of its family."},
  {"Em0011_003",  // Foot Soldier
        "A giant hand turned upside down that walks on its fingers: a pale silvery-white glove whose wrist rises "
        "into a short neck and a round, egg-shaped head covered in the same pale silver. Around the neck flares a "
        "tall, crimped ivory ruff, over a white lace jabot and a royal-blue front panel embroidered with gold "
        "scrollwork and crossed by three gold braids, like a courtier's doublet. The face is the teal-blue mask "
        "marked I, long and glum, with round black eyeholes, bolted on with silver spikes. It carries itself like "
        "a stiff, obedient footman of some old royal court."},
  {"Em0011_004",  // Final Checkmate
        "A giant hand turned upside down that walks on its fingers: a gleaming gold glove whose wrist rises into "
        "a short neck and a round, egg-shaped head of the same shining gold. Red piping traces a waistcoat down "
        "the back of the hand with a round red button, a little red bow tie sits at the neck, and every fingertip "
        "ends in a glossy red-painted nail. The face is the teal-blue mask marked I, long and glum, with round "
        "black eyeholes, bolted on with silver spikes. Dripping with wealth and polish, it looks like a living "
        "treasure, the gilded prize of its kind."},
  {"Em0012_000",  // Laughing Table
        "A magician's table come to life, its tarot tools hovering in a stack above it. At the bottom is a small "
        "table on thin, dark curling metal legs, draped in a dusty grey-brown cloth with a faint cobweb pattern "
        "and a frayed, striped hem, the teal-blue mask marked I bolted to its front: a long, glum face with round "
        "black eyeholes. Above float a plain pewter goblet, a single-edged steel blade rising point-up from it, a "
        "flat dark disc, and on top a gnarled wooden wand with a lumpy knob. It feels like a cheap street "
        "conjuror's act, shabby yet sinister."},
  {"Em0012_001",  // Grievous Table
        "A magician's table come to life, its tarot tools hovering in a stack above it. At the bottom is a small "
        "table on thin, dark curling metal legs, draped in a harlequin cloth of red and black diamonds trimmed in "
        "gold, the teal-blue mask marked I bolted to its front: a long, glum face with round black eyeholes. "
        "Above float a black goblet painted with red flame-like teeth, a red-hilted sword with a glowing "
        "orange-amber crystal blade, a flat red disc, and a gnarled wooden crook curled like a question mark with "
        "a red orb in its hook. Fiery and theatrical, it looks ready to burst into tears or flame."},
  {"Em0012_002",  // Angry Table
        "A magician's table come to life, its tarot tools hovering in a stack above it. At the bottom is a small "
        "table on thin, dark curling metal legs, draped in a cloth split down the middle, red and royal blue at "
        "the front and yellow and black at the back, hemmed with a heavy gold fringe, the teal-blue mask marked I "
        "bolted to its front: a long, glum face with round black eyeholes. Above float a tan goblet banded with "
        "dark triangles, a steel double-edged sword with a gold crossguard, a flat gold disc, and a gnarled "
        "wooden crook tipped with silver. It bristles like a jester in a temper."},
  {"Em0012_003",  // Terminal Table
        "A magician's table come to life, its tarot tools hovering in a stack above it. At the bottom is a small "
        "table on thin, pale silver curling legs, draped in a delicate white lace cloth, the teal-blue mask "
        "marked I bolted to its front: a long, glum face with round black eyeholes. Above float a dark, glossy "
        "blue-black goblet, a slender silver rapier with an ornate swept hilt rising from it, a thin silver disc, "
        "and on top a slim navy rod banded in gold, crowned with a small gold cross and ending in a silver spike. "
        "Hushed and funereal, it looks laid out for a wake."},
  {"Em0013_000",  // Magical Magus
        "A tall, robed sorcerer dressed like a court jester, rising from a vast dark cloak shaped like two "
        "gigantic hands spread behind it, their long, smoky-black fingers fanning out wide on either side. Its "
        "own body is a long robe of bold black and white stripes with flared, navy-trimmed sleeves and pale white "
        "gloved hands, a studded navy collar fastened with a round gold cross brooch, and a navy sash hanging to "
        "its hem. A white two-pointed jester's hood curls up into horns, each tip hung with a gold ring, framing "
        "the teal-blue mask marked I. Grand and stagey, it's a ringmaster of dark tricks."},
  {"Em0013_001",  // Venomous Magus
        "A tall, robed sorcerer dressed like a court jester, rising from a vast dark cloak shaped like two "
        "gigantic hands spread behind it, their long, smoky-black fingers fanning out wide on either side. Its "
        "own body is a candy-pink robe scattered with purple stars, with wide sleeves lined in orange-gold, soft "
        "pink gloved hands, and a gold collar studded with green gems around a round teal-jewelled brooch. A "
        "starry pink two-pointed jester's hood curls up into horns, each tip hung with a gold ring, framing the "
        "teal-blue mask marked I. Sweet as a children's party conjuror, and twice as poisonous underneath."},
  {"Em0013_002",  // Prime Magus
        "A tall, robed sorcerer dressed like a court jester, rising from a vast dark cloak shaped like two "
        "gigantic hands spread behind it, their long, smoky-black fingers fanning out wide on either side. Its "
        "own body is a deep crimson robe with darker red stripes, wide sleeves trimmed in gold, cream gloved "
        "hands, and a gold collar set with purple gems and a gold band of purple stones running down its front. A "
        "crimson two-pointed jester's hood curls up into horns, each tip hung with a gold ring, framing the "
        "teal-blue mask marked I. Rich and regal in blood red, it's the high priest of its order."},
  {"Em0013_003",  // Grand Magus
        "A tall, robed sorcerer dressed like a court jester, rising from a cloak shaped like two gigantic hands "
        "spread behind it, but here the hands are a ghostly, see-through pale mint and sky blue, their long "
        "fingers fanning out wide on either side. Its robe shimmers in pastel stripes of yellow, mint and aqua, "
        "fading to lavender and pink at the hem, with silver trim, aqua gloved hands and a silver collar of teal "
        "studs. A mint-and-yellow two-pointed jester's hood curls up into horns, each tip hung with a silver "
        "ring, framing the teal-blue mask marked I. Iridescent and dreamlike, it's the most exalted of its kind."},
  {"Em0021_000",  // Loathsome Tiara
        "A floating, bodiless head with no neck or shoulders, just a long curtain of wavy charcoal-black hair "
        "hanging down beneath it and ending in ragged, tentacle-like points. Its faceless dark grey head wears a "
        "rose-pink domino mask cut like butterfly wings, edged in silver, with a tiny Roman numeral two scratched "
        "over one eye. Above it rises a towering headdress in dusky rose-pink: two huge open loops like the "
        "handles of a pair of scissors, flanking an almond-shaped olive-gold panel, all set on a spiked gold "
        "coronet studded with silver rivets. It's a haunting, empty-headed queen of whispers, all hair and crown."},
  {"Em0021_001",  // Grieving Tiara
        "A floating, bodiless head with no neck or shoulders, just a long curtain of wavy charcoal-black hair "
        "hanging down beneath it and ending in ragged, tentacle-like points. Its faceless dark grey head wears a "
        "rose-pink domino mask cut like butterfly wings, edged in silver, with a tiny Roman numeral two scratched "
        "over one eye. Its towering headdress is pale polished silver: two huge open loops like the handles of a "
        "pair of scissors flanking an almond-shaped panel of deep teal, on a silver coronet whose points are "
        "edged in bright teal. Cold and gleaming, it looks like a mourner crowned in moonlight."},
  {"Em0021_002",  // Mage Soldier
        "A floating, bodiless head with no neck or shoulders, just a long curtain of wavy charcoal-black hair "
        "hanging down beneath it and ending in ragged, tentacle-like points. Its faceless dark grey head wears a "
        "rose-pink domino mask cut like butterfly wings, edged in silver, with a tiny Roman numeral two scratched "
        "over one eye. Its towering headdress is royal violet piped with thin gold lines: two huge open loops "
        "like the handles of a pair of scissors flanking an almond-shaped panel of dull pewter grey, set on a "
        "spiked gold coronet. The rich purple gives it a twisted, regal air, a sorceress's crown with no "
        "sorceress beneath."},
  {"Em0021_003",  // Shouting Tiara
        "A floating, bodiless head with no neck or shoulders, just a long curtain of wavy, pale lilac-grey hair "
        "hanging down beneath it and ending in ragged, tentacle-like points. Its faceless head is pale "
        "lavender-grey, wearing a rose-pink domino mask cut like butterfly wings, edged in silver, with a tiny "
        "Roman numeral two scratched over one eye. Its towering headdress is creamy bone-beige: two huge open "
        "loops like the handles of a pair of scissors flanking an almond-shaped panel of deep wine red, set on a "
        "crimson coronet studded with silver rivets. Ghostly pale and blood-trimmed, it looks like a crowned "
        "spectre ready to scream."},
  {"Em0022_000",  // Tome of Atrophy
        "A floating, bodiless head trailing a long mane of wavy, deep indigo-violet hair that hangs below it in "
        "ragged, tentacle-like locks, with no body at all. Its faceless dark grey head wears a rose-pink "
        "butterfly-wing domino mask edged in silver. On top sits a teal-green crown with gold leaf-shaped points, "
        "and rising from it a tall arching hoop of riveted bronze topped with a pointed finial, framing a thick "
        "holy book standing upright: a brown leather tome with an olive-green panel and a raised cross on its "
        "cover. It's a grim little relic of the church, a scripture with a head instead of hands."},
  {"Em0022_001",  // Tome of Persecution
        "A floating, bodiless head trailing a long mane of wavy candy-pink hair that deepens to magenta at the "
        "tips, hanging below it in ragged, tentacle-like locks, with no body at all. Its faceless dark grey head "
        "wears a rose-pink butterfly-wing domino mask edged in silver. On top sits a pale blue crown with leafy "
        "green points, and rising from it a tall arching hoop of riveted moss-green metal topped with a silver "
        "finial, framing a thick holy book standing upright: a mauve-pink tome with a sky-blue panel and a bright "
        "gold cross on its cover. Sweet-coloured but unsettling, it looks like a storybook gone mad."},
  {"Em0022_002",  // Silent Book
        "A floating, bodiless head trailing a long mane of wavy, dark navy-blue hair that hangs below it in "
        "ragged, tentacle-like locks, with no body at all. Its faceless dark grey head wears a rose-pink "
        "butterfly-wing domino mask edged in silver. On top sits a silvery steel-blue crown set with small red "
        "stones, and rising from it a tall arching hoop of riveted steel-blue metal topped with a pointed finial, "
        "framing a thick holy book standing upright: a charcoal-black tome with a blood-red panel and a darker "
        "red cross on its cover. Sombre and severe, it has the look of a forbidden book that should stay shut."},
  {"Em0022_003",  // Morbid Book
        "A floating, bodiless head trailing a long mane of wavy, pale cream-blonde hair that hangs below it in "
        "ragged, tentacle-like locks, with no body at all. Its faceless head is light grey, wearing a rose-pink "
        "butterfly-wing domino mask edged in silver. On top sits a teal and navy crown with gold points, and "
        "rising from it a tall arching hoop of riveted brass topped with a pointed finial, framing a thick holy "
        "book standing upright: a silvery-white tome with a gold panel and a raised gold cross on its cover. "
        "Bright and gilded, it looks like a sacred scripture with a furious, haunted owner."},
  {"Em0023_000",  // Tranquil Idol
        "A slender, faceless woman of smooth dark slate-grey, sitting cross-legged in meditation atop a floating "
        "stepped pedestal of dark stone that tapers to a point beneath her like an upside-down pyramid. Her bare "
        "body has a womanly bust and long, thin limbs, and her face is hidden by a rose-pink butterfly-wing "
        "domino mask. A crimson veil hangs from her head like a hood and spreads into wide sweeping wings either "
        "side, edged in gold. A green band set with round bronze studs rings the platform. With no throne behind "
        "her, she sits plain and still, a shrine's statue that might open its eyes at any moment."},
  {"Em0023_001",  // Liberating Idol
        "A slender, faceless woman of smooth dusky grey-brown, sitting cross-legged in meditation on a floating "
        "stepped pedestal of magenta stone that tapers to a point beneath her. Her bare body has a womanly bust "
        "and long thin limbs; her face is hidden by a rose-pink butterfly-wing domino mask. A pale sea-green veil "
        "falls from her head and spreads wide either side. Behind her stands a tall magenta throne-back with a "
        "deep indigo panel, crowned by a great spoked wheel with a golden sunburst at its hub. A band of bronze "
        "studs rings the platform. She sits like a mystic idol, calm and unknowable."},
  {"Em0023_002",  // Ruinous Idol
        "A slender, faceless woman of smooth charcoal grey, sitting cross-legged in meditation on a floating "
        "stepped pedestal of tarnished brass that tapers to a point beneath her. Her bare body has a womanly bust "
        "and long thin limbs; her face is hidden by a rose-pink butterfly-wing domino mask. A cream veil with a "
        "thin gold edge falls from her head and spreads wide either side. Behind her rises a brass throne-back "
        "with a royal blue panel, topped by two stacked blue and gold spoked wheels, a crescent moon at one hub, "
        "a sunburst at the other. She's a cold, cosmic idol of sun and moon."},
  {"Em0023_003",  // Vehement Idol
        "A slender, faceless woman of smooth icy pale blue, sitting cross-legged in meditation on a floating "
        "stepped pedestal of sea-green stone that tapers to a point beneath her. Her bare body has a womanly bust "
        "and long thin limbs; her face is hidden by a rose-pink butterfly-wing domino mask. A long veil of peachy "
        "blonde flows from her head like hair and spreads wide either side, blushing pink at the hems. Behind her "
        "stands a pale blue throne-back with an olive-gold panel, crowned by a silvery full moon in navy rings "
        "radiating thin spokes tipped with stars. She's dreamy and moonlit, a goddess of the night sky."},
  {"Em0023_004",  // ?
        "A slender, faceless woman of smooth deep teal-green, sitting cross-legged in meditation on a floating "
        "stepped pedestal of brown stone ending in raw rock. Her bare body has a womanly bust and long thin "
        "limbs; her face is hidden by a rose-pink butterfly-wing domino mask. A pale blue hood falls into a royal "
        "blue veil edged with gold embroidery, spreading wide either side. Behind her stands a bronze throne-back "
        "with a silver tablet carved in rows of script, draped in ivy and topped by two stacked blue and gold "
        "wheels with a crescent moon, a sunburst and two stars. She looks like a forgotten idol from an overgrown "
        "temple."},
  {"Em0031_000",  // Lightning Eagle
        "A great raven-black bird of prey, taller than a person, with huge ragged wings, a long sweeping tail and "
        "red-tipped talons. Its dark beak-like face wears an ivory mask with closed, serene eyes and a tall "
        "pointed top like a crown, a Roman numeral three on its brow and a small gold ring at one cheek. A "
        "frilled white ruff circles its neck, and behind its head stands a tall scarlet heart-shaped collar. Its "
        "breast is wrapped in a smooth red bodice, like a lady's gown on a bird. It has the haughty bearing of a "
        "queen who takes to the skies to hunt."},
  {"Em0031_001",  // Dark Eagle
        "A great raven-black bird of prey, taller than a person, with huge ragged wings, a long sweeping tail and "
        "dark red-tipped talons. Its dark beak-like face wears an ivory mask with closed, serene eyes and a tall "
        "pointed top like a crown, a Roman numeral three on its brow and a small gold ring at one cheek. Behind "
        "its head rise two tall, slender violet blades like the ears of a hare, over a ruffled collar of dark "
        "red. Its breast is laced into a purple corset with criss-cross lacing and red frills. Sleek and "
        "sinister, it looks like a dark empress of the night."},
  {"Em0031_002",  // Jupiter Eagle
        "A great raven-black bird of prey with a faint green sheen, taller than a person, with huge ragged wings, "
        "a long sweeping tail and grey talons. Its dark beak-like face wears an ivory mask with closed, serene "
        "eyes and a tall pointed top like a crown, a Roman numeral three on its brow and a small gold ring at one "
        "cheek. Behind its head opens a huge round fan collar of grey-green metal, ringed with dark rivet holes, "
        "over a grey ruff. Its breast is armoured in a silver plated bodice with panels down the belly. Steely "
        "and stately, it looks like a war queen in battle dress."},
  {"Em0031_003",  // Eternal Eagle
        "A great pale bird of prey, taller than a person, its feathers a soft greenish ivory that burns to rusty "
        "orange at the tips of the wings and the long sweeping tail, with turquoise talons. Its pale beak-like "
        "face wears an ivory mask with closed, serene eyes and a tall pointed top like a crown, a Roman numeral "
        "three on its brow and a small gold ring at one cheek. A white ruff circles its neck, and behind its head "
        "stands a huge bubblegum-pink heart-shaped collar, matched by a pink bodice on its breast. Bright and "
        "romantic, it looks like a sweetheart queen of the skies."},
  {"Em0032_000",  // Creation Relic
        "A seated statue of a robed mother on a tall throne, carved all of warm grain-streaked wood. She cradles "
        "a small child in one arm and holds up a dark iron ball in her other hand. Her long hair falls over her "
        "shoulders under a tall flat-topped hat, and her face is hidden by an ivory mask with closed eyes, a "
        "crown-like pointed top and a Roman numeral three on the brow. Her throne is dark iron-grey stone. Beside "
        "it hover five long, slender dark iron spearheads in a row, pointing ahead. Holy and motherly at first "
        "glance, she is armed to the teeth."},
  {"Em0032_001",  // Constancy Relic
        "A seated statue of a robed mother on a tall throne, her robe and tall flat-topped hat a weathered jade "
        "green, like old bronze, and her skin and long hair a cold blue-grey. She cradles a small child in one "
        "arm and holds up a pale tan ball in her other hand. Her face is hidden by an ivory mask with closed "
        "eyes, a crown-like pointed top and a Roman numeral three on the brow. Her throne is glossy black, its "
        "back set with small clear crystals. Beside it hover five long, slender spearheads of glassy pale green, "
        "pointing ahead. She's a serene graveyard Madonna, quietly lethal."},
  {"Em0032_002",  // Heartless Relic
        "A seated statue of a robed mother on a tall throne, her robe and tall flat-topped hat deep navy blue, "
        "her skin and long hair a chalky pale grey. She cradles a small grey child in one arm and holds up a dark "
        "grey ball in her other hand. Her face is hidden by an ivory mask with closed eyes, a crown-like pointed "
        "top and a Roman numeral three on the brow. Her throne is glossy black, its back set with small clear "
        "crystals. Beside it hover five long, slender white-silver spearheads in a row, pointing ahead. Cold and "
        "solemn, she looks like a mourning saint keeping a deadly vigil."},
  {"Em0032_003",  // Change Relic
        "A seated statue of a robed mother on a tall throne, all carved from pale cream limestone: her robe, her "
        "long hair, her tall flat-topped hat, the child she cradles in one arm and the throne itself. In her "
        "other hand she holds up a small golden ball. Her face is hidden by a pinkish ivory mask with closed "
        "eyes, a crown-like pointed top and a Roman numeral three on the brow. Behind the throne bursts a fan of "
        "flat stone rays, crowned by one tall central spike, and beside it hover five long, slender stone "
        "spearheads, pointing ahead. Radiant and austere, she's a sun goddess carved in marble."},
  {"Em0032_004",  // ?
        "A seated statue of a robed mother on a tall throne, her robe and tall flat-topped hat a dull khaki gold "
        "trimmed with dusky purple at the collar and hatband, her skin and long hair pale grey. She cradles a "
        "small grey child in one arm and holds up a bright red ball in her other hand. Her face is hidden by an "
        "ivory mask with closed eyes, a crown-like pointed top and a Roman numeral three on the brow. Her throne "
        "is dusky purple. Beside it hover five long, slender silver spearheads, pointing ahead. She's a regal "
        "Madonna with a hint of forbidden fruit."},
  {"Em0033_000",  // Elegant Mother
        "A tall, slender woman with a sleek, featureless black body, lounging on an ornate chaise longue of "
        "bottle-green upholstery framed in copper-brown wrought scrolls, with curling legs. One long black leg "
        "stretches up along the seat. She wears a floor-length dark navy-violet coat with thin gold piping and a "
        "huge shaggy tawny fur collar and cuffs, with pearls and gold chains at her throat. Her face hides behind "
        "an ivory mask with closed eyes, a crown-like pointed top and a Roman numeral three, under a tall black "
        "hat, with straight magenta locks at her cheeks. Clawed fingers finish the look: a languid, wealthy "
        "matriarch, bored and dangerous."},
  {"Em0033_001",  // Regal Mother
        "A tall, slender woman with a sleek, featureless black body, lounging on a plum-purple chaise longue "
        "framed in silver-grey wrought iron, with curling legs. One long black leg stretches up along the seat. "
        "She wears a floor-length crimson coat with a fluffy lilac fur collar and cuffs and pearls at her throat. "
        "Her face hides behind an ivory mask with closed eyes, a crown-like pointed top and a Roman numeral "
        "three, under a tall lilac hat, with long honey-brown hair. Behind her fans a spread of black spikes "
        "webbed with sheer fins shading from lime green to blue, flecked orange at the edges. She's a decadent "
        "queen, sultry and imperious."},
  {"Em0033_002",  // Lascivious Lady
        "A tall, slender woman with a sleek, featureless black body, lounging on a tiger-striped chaise longue "
        "framed in gold scrollwork, on curling gold legs. One long black leg stretches up along the seat. She "
        "wears a floor-length leopard-print coat and a matching tall leopard-print hat, with a smoky grey fur "
        "collar and cuffs and pearls at her throat. Her face hides behind an ivory mask with closed eyes, a "
        "crown-like pointed top and a Roman numeral three, framed by long purple hair. Behind her sofa fans a "
        "huge spread of dark purple spikes webbed with white fins spotted in black. All animal prints and "
        "attitude, she's a flamboyant, man-eating diva."},
  {"Em0033_003",  // Divine Mother
        "A tall, slender woman with a sleek, featureless lilac-grey body, lounging on a lavender chaise longue "
        "framed in silver scrollwork, on curling legs. One long leg stretches up along the seat. She wears a "
        "floor-length pale mint coat with a feathery mint fur collar and cuffs, pearls at her throat and a tall "
        "mint hat. Her face hides behind an ivory mask with closed eyes, a crown-like pointed top and a Roman "
        "numeral three, framed by long blonde hair. Behind her fans a peacock's tail, green feathers with bright "
        "eye spots fading to violet and blue. Cool and vain, she's an elegant beauty showing off in pastel "
        "splendour."},
  {"Em0041_000",  // Grave Beetle
        "A huge rhinoceros beetle, longer than a car, its domed shell cracked all over like old glaze in mottled "
        "purple and moss green, splashed with streaks of blood red. From its snout a long horn curves up and back "
        "like a swan's neck, and balanced on its tip is a lavender mask: a half face with hollow eye slots, the "
        "numeral IV on its brow and five barbed spikes fanning up like a crown. Pale bulging eyes sit low on its "
        "head, thin smoky wings jut out sideways, and four pairs of black, jagged legs carry it. It looks "
        "diseased and ancient, a grave-dweller crawling up out of the dirt."},
  {"Em0041_001",  // Adamant Beetle
        "A huge rhinoceros beetle with a smooth shell of deep crimson-maroon. A band of gold key-pattern runs "
        "around the edge of its wing case, and a jagged gold crown set with tiny blue stones sits on its back "
        "like a saddle. From its snout a long horn curves up and back, and balanced on the tip is a lavender "
        "mask: a half face with hollow eye slots, the numeral IV on its brow and five barbed spikes fanning up "
        "like a crown. Its eyes are glossy pink domes, its sideways wings pale tan, its legs dark and thorny. "
        "Polished and pompous, it carries itself like minor royalty."},
  {"Em0041_002",  // Golden Beetle
        "A huge rhinoceros beetle dressed as a king. Its head and thorax are armoured in bright gold, and its "
        "wing case is a royal blanket embroidered in purple, teal and gold swirls on deep navy. On its back sits "
        "a full coronation crown: crimson velvet under gold arches studded with blue, green and red jewels, a "
        "white fur band at the base and a jewelled cross on top. A long gold horn curves up from its snout, "
        "holding high a lavender half mask with hollow eyes, the numeral IV on its brow and five barbed spikes. "
        "Gold wings and black thorny legs finish a creature dripping with gaudy majesty."},
  {"Em0041_003",  // Emperor Beetle
        "A huge rhinoceros beetle in shimmering pastel blue, violet and mint. Unlike its plainer kin it has two "
        "extra horns, long curved tusks rising from its thorax and arching forward to meet in a point, draped "
        "with strings of beads in teal, lilac and yellow. A row of round turquoise stones runs along its wing "
        "case, and its legs are pale, almost white, and spiky. Its snout horn curves up to hold a dark violet "
        "half mask with hollow eyes, the numeral IV on its brow and five barbed spikes. Gorgeous and "
        "jewel-draped, it looks like an emperor's parade float come to life."},
  {"Em0041_004",  // ?
        "A huge rhinoceros beetle in bold scarlet, its wing case covered in curling gold swirls and edged in "
        "gold. On its back sits a jagged crown of bright green rimmed with gold, and its eyes are round green "
        "gems. Its sideways wings fade from red to orange to a green tip, and its legs are dark and thorny. From "
        "its snout a long red horn curves up and back, holding high a lavender half mask with hollow eye slots, "
        "the numeral IV on its brow and five barbed spikes fanning up like a crown. Loud, fiery and showy, it "
        "looks like a festival lantern that learned to bite."},
  {"Em0042_000",  // ?
        "A headless knight on a dragon steed. The rider is gunmetal-grey plate armour with flared, pointed "
        "shoulder guards, a gold-patterned band across the chest and a dark blue scarf streaming behind; where "
        "the head should be floats a lavender half mask with hollow eyes, the numeral IV on its brow and five "
        "barbed spikes. His mount has a long armoured dragon's head with a single horn, a spiky mane, red eyes "
        "and reins, and a segmented tail, its body hidden under a navy caparison trimmed in gold and hung with "
        "purple diamond jewels. He carries a long purple-grey lance and a small round shield. A grim, avenging "
        "cavalier."},
  {"Em0042_001",  // Champion Knight
        "A headless knight on a dragon steed, in dark violet-grey plate armour with flared, pointed shoulder "
        "guards and a gold-patterned chest band, a crimson scarf streaming behind him. Where the head should be "
        "floats a lavender half mask with hollow eyes, the numeral IV on its brow and five barbed spikes. His "
        "mount has a long armoured dragon's head with a single horn, a spiky mane, red eyes and reins, and a "
        "segmented tail; its body is draped in a deep crimson caparison trimmed in gold and hung with steel-grey "
        "diamond charms. A long dark lance and a small round shield complete a proud champion in blood red."},
  {"Em0042_002",  // Demented Knight
        "A headless knight on a dragon steed, almost black: blue-black plate armour with flared, pointed shoulder "
        "guards, a pale-patterned chest band and a dark plum scarf streaming behind. Where the head should be "
        "floats a lavender half mask with hollow eyes, the numeral IV on its brow and five barbed spikes. His "
        "mount is black too, its studded dragon head horned and maned, with red eyes, and it wears a deep purple "
        "caparison edged in thin red and white braid and hung with dark purple diamond charms. He bears a black "
        "lance and a small round shield: a nightmare ridden up out of hell."},
  {"Em0042_003",  // Intrepid Knight
        "A headless knight on a dragon steed, all pale and ghostly: frosty mint-white plate armour with flared "
        "pointed shoulder guards and a red-patterned chest band, and a vivid violet scarf streams behind him. "
        "Where the head should be floats a dark violet half mask with hollow eyes, the numeral IV on its brow and "
        "five barbed spikes. His mount is bone white, its dragon head crested with one long horn, a spiky mane "
        "and pale blue eyes, and its caparison is a pale lilac-grey trimmed in red and hung with purple diamond "
        "charms. He bears a grey lance banded in red and a small round shield. Swift and spectral."},
  {"Em0043_000",  // Haunted Castle
        "A walking crag with a castle on top. A towering column of grey rock, ringed with ledges, tapers into two "
        "thick stony legs with an arch between them. A narrow staircase winds around it, little gatehouses cling "
        "to its sides and black cannon barrels poke out in every direction. Crowning it is a grey stone castle "
        "with battlements, an arched door and turrets with purple pointed roofs and purple pennants. From the "
        "keep rises a black hooded head wearing a lavender mask: hollow eyes, the numeral IV on its brow and a "
        "ring of barbed spikes radiating like a sunburst. A dour fortress on the march."},
  {"Em0043_001",  // Isolated Castle
        "A walking crag with a castle on top. A towering column of rock furred with bright green moss, ringed "
        "with ledges and tapering into two thick legs with an arch between them. A narrow staircase winds up it, "
        "little gatehouses cling to its sides and dark cannons poke out all around. On the summit stands a sandy, "
        "honey-coloured stone castle with battlements, an arched door and turrets capped in brick-red roofs with "
        "red pennants. From the keep rises a black hooded head wearing a lavender mask: hollow eyes, the numeral "
        "IV on its brow and a ring of barbed spikes like a sunburst. A lonely island fortress that grew legs."},
  {"Em0043_002",  // Death Castle
        "A walking crag with a castle on top, its rock a lurid blood crimson, ringed with ledges and tapering "
        "into two thick legs with an arch between them. A red staircase winds up it and black cannons banded in "
        "red poke out from ports framed with red crosses. On the summit stands a cold grey stone castle with "
        "battlements, an arched door and turrets with dark red roofs and red pennants. From the keep rises a "
        "black hooded head wearing a lavender mask: hollow eyes, the numeral IV on its brow and a ring of barbed "
        "spikes like a sunburst. Soaked in red, it looks built for slaughter."},
  {"Em0043_003",  // Comeback Castle
        "A walking crag with a castle on top, all in pale, dreamy tones: its rock is a soft lilac grey, ringed "
        "with ledges and tapering into two thick legs with an arch between them, a faint purple staircase winding "
        "up it. Bronze cannons with gold bands poke out all around. On the summit stands a weathered white stone "
        "castle with battlements, an arched door and turrets capped in blue-violet roofs with tan pennants. From "
        "the keep rises a cream hooded head wearing a mask of orchid pink: hollow eyes, the numeral IV on its "
        "brow and a ring of barbed spikes like a sunburst. An ancient fairy-tale stronghold, stately and serene."},
  {"Em0051_000",  // Trance Twins
        "Two gaunt, identical figures chained together like prisoners: charcoal skin, bald heads with round "
        "disc-like ears, long bony hands. Each wears a drab olive-brown hooded monk's robe tied with a rope belt, "
        "and a heavy iron collar with matching cuffs at wrists and ankles. Three long iron rods run through the "
        "collars, wrists and ankles of both, each with an arrowhead and fletching-like crossbars, skewering them "
        "side by side on giant arrows. Each face is covered by a blue oval mask with the numeral V on the brow, "
        "slanted eye slits and a gaping triangular mouth, bolted to the head. Eerie and joyless."},
  {"Em0051_001",  // ?
        "Two gaunt, identical figures chained together like prisoners, with dark charcoal skin, bald heads and "
        "round disc-like ears. They wear black robes with a short deep purple shoulder cape trimmed in lilac, a "
        "purple sash at the waist and a pale stripe at the hem, and blue-violet collars and cuffs at neck, wrists "
        "and ankles. Three long dark iron rods run through both, each with an arrowhead and fletching-like "
        "crossbars, skewering them side by side on giant arrows. Each face is covered by a blue oval mask with "
        "the numeral V on the brow, slanted eye slits and a gaping triangular mouth, bolted on. Executioners "
        "bound to each other."},
  {"Em0051_002",  // Death Twins
        "Two gaunt, identical figures chained together, dark charcoal skin and round disc-like ears, each wearing "
        "a small red skullcap banded in gold and black. Their robes are rich crimson with gold piping, a wide "
        "front panel of black and gold filigree running down the middle and a black cord belt, like a cardinal's "
        "finery. Brass collars and cuffs clasp neck, wrists and ankles, and three long brass rods with arrowheads "
        "and fletching-like crossbars skewer them side by side. Each face is hidden by a blue oval mask with the "
        "numeral V, slanted eye slits and a gaping triangular mouth, bolted on. Grand, grim and deathly."},
  {"Em0051_003",  // Crazy Twins
        "Two gaunt, identical figures chained together, but these have pale ash-grey skin, bald heads and round "
        "disc-like ears. Their hooded robes are off-white with a faint woven damask pattern, tied with an olive "
        "cord, and their collars and cuffs at neck, wrists and ankles are a pale sea green. Three long "
        "olive-brass rods with arrowheads and fletching-like crossbars skewer them side by side on giant arrows. "
        "Each face is covered by a blue oval mask with the numeral V on the brow, slanted eye slits and a gaping "
        "triangular mouth, bolted to the head. Washed-out and ghostly, they look quietly unhinged."},
  {"Em0052_000",  // Corrupt Tower
        "A towering totem of three stone heads stacked one on another, dark grey, eyes closed and serene, each "
        "smaller than the one below. Each wears a bishop's mitre of crimson with a gold frame, a band of gold "
        "studded with blue stones and a column of gems, purple above green, up its front, and each mitre is "
        "crowned by the next head. The topmost face wears a blue oval mask with slanted eye slits, bolted to the "
        "head, beneath the tallest mitre of all, with a gold sunburst panel bearing a large purple gem over two "
        "green. Silent and pious, it looks like a church spire that worships itself."},
  {"Em0052_001",  // Dogmatic Tower
        "A towering totem of three stone heads stacked one on another, dark grey, eyes closed and serene, each "
        "smaller than the one below. Each wears a bishop's mitre of ivory cream with a gold frame and a band of "
        "gold squares studded with little red stones, a gold medallion set with rubies on its front, and each "
        "mitre is crowned by the next head. The topmost face wears a blue oval mask with slanted eye slits, "
        "bolted to the head, beneath the tallest mitre, whose gold sunburst panel carries a column of three red "
        "gems. Pale and stern, it has the cold sanctity of doctrine."},
  {"Em0052_002",  // Pagoda of Disaster
        "A towering totem of three stone heads stacked one on another, dark grey, eyes closed and serene, each "
        "smaller than the one below. Each wears a bishop's mitre of glossy black framed in silver, with a band of "
        "silver squares set with violet stones and a silver medallion of red gems on its front, and each mitre is "
        "crowned by the next head. The topmost face wears a blue oval mask with slanted eye slits, bolted to the "
        "head, beneath the tallest mitre, whose silver sunburst panel carries a column of three red gems. It "
        "looks like a heretic's idol, a church gone wrong."},
  {"Em0052_003",  // Fanatic Tower
        "A towering totem of three heads stacked one on another, chalky white like marble statues, eyes closed "
        "and serene, each smaller than the one below. Each wears a bishop's mitre of royal blue laced with gold "
        "filigree hearts and curls, and on the front of each sits a large oval mirror in a gold frame with spiky "
        "gold flourishes and a green gem below. Each mitre is crowned by the next head, and the topmost face "
        "wears a blue oval mask with slanted eye slits, bolted to the head, beneath the tallest, a green bead at "
        "its very tip. Gleaming and lofty, it looks like an imposing cathedral spire."},
  {"Em0052_004",  // ?
        "A towering totem of three heads stacked one on another, eyes closed and serene, each smaller than the "
        "one below. The heads are pale sea green with white faces streaked by thin green lines running down from "
        "the eyes like dried tears. Each wears a deep green bishop's mitre with gold flame-like swirls, a band of "
        "gold zigzags and a cream and gold spine studded with red gems, crowned by the next head. The top face "
        "wears a bolted-on blue oval mask with slanted eye slits, under a mitre ending in a gold spearpoint set "
        "with a red gem. Weeping and solemn, a shrine to some sorrowful faith."},
  {"Em0053_000",  // Blue Sigil
        "A priest hidden inside a giant book: four huge tan parchment pages, dense with black script under a "
        "great curled initial, stand around him front and back like the leaves of a tome. Between them he wears a "
        "teal-blue cassock with silver cross-shaped clasps, a white stole edged in gold and dotted with blue "
        "flowers, a dark navy cape, and a round brooch of a gold square stone ringed by blue gems and pearls. On "
        "his head is a tall white mitre with gold crosses, and his face is a blue mask with the numeral V, "
        "slanted eyes and a gaping beak-like mouth. A preacher of forbidden scripture."},
  {"Em0053_001",  // Red Sigil
        "A priest hidden inside a giant book: four huge ashen grey pages, dense with black script under a great "
        "curled initial, stand around him like the leaves of a tome, and small black feathered wings on curling "
        "stems peek out at his sides. Between the pages he wears a black cassock fastened with bone-white "
        "cross-shaped clasps, a crimson cape, and a round brooch of a red square stone ringed by lilac pearls. "
        "His tall black mitre carries silver crosses and a band of silver spikes, and his face is a blue mask "
        "with the numeral V, slanted eyes and a gaping beak-like mouth. A dark, blood-red zealot."},
  {"Em0053_002",  // Cultist of the Storm
        "A priest hidden inside a giant book: four huge pages of dark wine red, dense with black script under a "
        "great curled initial, stand around him front and back like the leaves of a tome. Between them he wears "
        "an emerald green cassock fastened with gold cross-shaped clasps, a stole of deep blue, a green cape, and "
        "a round brooch of a gold square stone ringed by green gems and pearls. His tall green mitre carries gold "
        "crosses, and his face is a blue mask with the numeral V, slanted eyes and a gaping beak-like mouth. "
        "Green and gold, he looks like the cult leader of some storm-worshipping sect."},
  {"Em0053_003",  // Cultist of Death
        "A priest hidden inside a giant book: four huge ghostly white pages, dense with black script under a "
        "great curled initial, stand around him like the leaves of a tome, and small pink feathered wings on gold "
        "curls peek out at his sides. Between the pages he wears a white cassock with lilac cross-shaped clasps, "
        "a hot pink stole, and a round brooch of a teal square stone set on pink and ringed in pearls. His very "
        "tall mitre is bubblegum pink, banded and spiked in silver, and his face is a blue mask with the numeral "
        "V, slanted eyes and a gaping beak-like mouth. Sweet colours for a herald of death."},
  {"Em0061_000",  // Jealous Cupid
        "A small, plump cherub of pure shadow, the size of a toddler, its round belly, stubby legs and "
        "long-fingered hands all a dull charcoal black, with a pair of black feathered wings at its back. Its "
        "whole face is a hot pink mask stamped with a pale VI on the brow, bolted round the edge with steel "
        "clasps; the eyes droop half-shut and the little mouth hangs open in a sleepy O. It carries a pale silver "
        "bow with curled scroll ends and arrows tipped with heart-shaped heads. A love god of legend gone sullen "
        "and dark, it looks bored, spoiled and quietly dangerous."},
  {"Em0061_001",  // Enslaved Cupid
        "A small, plump cherub of shadow, the size of a toddler, in a skin-tight black body striped down the "
        "sides and legs with royal blue. Its wings fade from dark teal at the root to bright sky blue at the "
        "tips. Its whole face is a hot pink mask stamped with a pale VI on the brow and bolted round the edge "
        "with steel clasps, over a black hood; the eyes droop half-shut and the little mouth hangs open in a "
        "sleepy O. It carries a violet bow with curled scroll ends and blue-shafted arrows tipped with violet "
        "hearts. Cool-toned and sulky, a love god gone jealous and cold."},
  {"Em0061_002",  // Devoted Cupid
        "A small, plump cherub of shadow, the size of a toddler, in a skin-tight black body striped down the "
        "sides and legs with deep magenta. Its wings fade from black at the root to hot pink at the tips. Its "
        "whole face is a hot pink mask stamped with a pale VI on the brow and bolted round the edge with steel "
        "clasps, over a black hood; the eyes droop half-shut and the little mouth hangs open in a sleepy O. It "
        "carries a candy-pink bow with curled scroll ends and black-shafted arrows tipped with bright red hearts. "
        "All pink and black, it is a love god of smothering, sulky devotion."},
  {"Em0061_003",  // Luckless Cupid
        "A small, plump cherub of shadow, the size of a toddler, but this one is pale: its round belly, stubby "
        "legs and long-fingered hands are a glassy mint aqua, under a white hood. Its wings shimmer in soft "
        "pastels, lilac at the root through pale green and yellow to warm orange tips. Its whole face is a "
        "crimson-pink mask stamped with a pale VI on the brow and bolted round the edge with gold clasps; the "
        "eyes droop half-shut and the little mouth hangs open in a sleepy O. It carries a gold bow with curled "
        "ends and silver-shafted arrows tipped with gold hearts. Sweet as a sugared almond, and just as bored."},
  {"Em0062_000",  // Lustful Snake
        "A long, rigidly straight serpent, taller than a person, its body pitch black and ringed with fine bands, "
        "tapering to a needle tip below and a small blunt head above. On the back of its head sits a tiny "
        "crimson-pink mask with narrow slit eyes. Threaded onto its body like beads on a cord are two flat "
        "ornamental symbols: in front a magenta ring above a cross whose arms end in arrowheads and whose foot is "
        "a heart, behind a steel-blue ring above a downward-pointing arrow. Sleek and single-minded, it is desire "
        "made into a slithering emblem."},
  {"Em0062_001",  // Immoral Snake
        "A long, rigidly straight serpent, taller than a person, black along its front, while its back is striped "
        "from head to tail in bold alternating bands of magenta and violet, like a gaudy candy cane. A small "
        "blunt head tops it, with a tiny crimson-pink slit-eyed mask set at the back. Threaded onto its body are "
        "two flat ornamental symbols: in front a magenta ring above a cross with arrowhead arms and a heart at "
        "its foot, behind a dusky indigo ring above a downward arrow. Loud, lurid and flirtatious, it flaunts its "
        "stripes shamelessly."},
  {"Em0062_002",  // Carnal Snake
        "A long, rigidly straight serpent, taller than a person, its front a smooth black and its back covered in "
        "a mesh of blood-red scales like fishnet over shadow. A small blunt head tops it, a tiny crimson-pink "
        "slit-eyed mask set at the back. Threaded onto its body are two flat ornamental symbols: in front a "
        "polished silver ring above a cross with arrowhead arms and a heart at its foot, behind a black iron ring "
        "engraved with runes above a downward arrow. Black, red and silver, it has a cold, sinful elegance."},
  {"Em0062_003",  // Invasive Serpent
        "A long, rigidly straight serpent, taller than a person, its body a pale bone or cream colour, finely "
        "ridged like old ivory, tapering to a needle tip, with a small blunt head carrying a tiny crimson-pink "
        "slit-eyed mask at the back. Threaded onto its body are two flat ornamental symbols shimmering like "
        "mother-of-pearl: in front a ring above a cross with arrowhead arms and a heart at its foot, washed in "
        "soft pink and lilac, behind a ring above a downward arrow in mint, blue and cyan. Pale and pearly, it "
        "looks deceptively sweet."},
  {"Em0062_004",  // ?
        "A long, rigidly straight serpent, taller than a person, its front a deep teal and its back covered in "
        "small overlapping scales of bright leaf green, tapering to a needle tip, with a small blunt head "
        "carrying a tiny crimson-pink slit-eyed mask at the back. Threaded onto its body are two flat ornamental "
        "symbols in engraved bronze: in front a ring above a cross with arrowhead arms and a heart at its foot, "
        "behind a ring above a downward arrow. Green and bronze like a jungle idol, it is the most "
        "natural-looking of its kind, and just as sly."},
  {"Em0063_000",  // Dependent Partner
        "A headless dancer of human height whose head is a floating black heart, bigger than a face, with a "
        "crimson-pink mask pinned to its front by a ring of nails, stamped VI, its closed eyes and open mouth "
        "sagging in sorrow. A dark neck stump rises from a white tailcoat with cream lapels and a pink bow, worn "
        "over a long coral-pink ballroom gown fading to peach at the hem, smeared with dripping black at the "
        "waist. It has black boots and dark long-fingered hands, and a steel fencing foil with a bell guard lies "
        "at its feet. Half gentleman, half lady, it is a tango partner made of heartbreak."},
  {"Em0063_001",  // Ardent Dancer
        "A headless dancer of human height whose head is a floating black heart with a crimson-pink mask pinned "
        "to its front by a ring of nails, stamped VI, its closed eyes and open mouth sagging in sorrow. Its body "
        "wears a sky-blue tailcoat with cream lapels and a golden bow over a long marigold-yellow gown printed "
        "with white flowers, its skirt tiered in lace-edged ruffles, with dripping black at the waist. Black "
        "boots, dark long-fingered hands and a gold fencing foil with a bell guard complete it. Bright as a "
        "carnival, it dances its sadness in sunshine colours."},
  {"Em0063_002",  // Royal Dancer
        "A headless dancer of human height whose head is a floating black heart with a crimson-pink mask pinned "
        "to its front by a ring of nails, stamped VI, its closed eyes and open mouth sagging in sorrow. Its body "
        "is all black: a black tailcoat with white lapels and a black bow over a long black gown, both sprinkled "
        "with tiny gold polka dots, with gold piping running down the coat-tails and along the hem. Black boots, "
        "dark long-fingered hands and a silver fencing foil with a bell guard complete it. Dressed for a midnight "
        "ball, it is the most formal and funereal of its kind."},
  {"Em0063_003",  // ?
        "A headless dancer of human height whose head is a floating heart of pale icy mint and white, the only "
        "one of its kind not black, with a crimson-pink mask pinned to its front by a ring of nails, stamped VI, "
        "its closed eyes and open mouth sagging in sorrow. Its body wears a cream tailcoat with a pink bow over a "
        "long pastel pink gown with a mint underlayer, and pale blue-white boots and hands. A grey-blue steel "
        "fencing foil with a bell guard lies at its feet. All pastels and frost, it looks like a sugared "
        "wedding-cake topper with a broken heart."},
  {"Em0063_004",  // ?
        "A headless dancer of human height whose head is a floating heart of dark slate teal, with a crimson-pink "
        "mask pinned to its front by a ring of nails, stamped VI, its closed eyes and open mouth sagging in "
        "sorrow. Unlike its kin it wears no long gown: a short crimson jacket with a frilled white cravat and "
        "white ruffled cuffs, a black belt and a short skirt of white tiered ruffles over long dark legs in tall "
        "black boots. A gold fencing foil with a bell guard lies at its feet. Sharp and showy, it looks like a "
        "flamenco duellist."},
  {"Em0071_000",  // Bestial Wheel
        "A beast of war built on a single wheel: a huge lion's head the height of a person, framed by a great "
        "spiky mane of shaggy brown blades, set over a big black spoked wheel. Its face is a yellow lion mask "
        "stamped VII, with narrow closed eye slits, clamped on with black studs, and beneath it a real mouth "
        "gapes in a fanged red snarl. Black spikes jut out to either side from the wheel's hub like chariot "
        "scythes, and a long tawny tail sweeps back, ending in a tufted brown bulb. All mane, teeth and rolling "
        "iron, it is a war chariot with a lion's temper."},
  {"Em0071_001",  // Mach Wheel
        "A beast of war built on a single wheel: a huge lion's head the height of a person over a big black "
        "spoked wheel, its spiky mane made of bright green leaf-like blades, like a lion grown from a jungle. Its "
        "face is a yellow lion mask stamped VII, with narrow closed eye slits, clamped on with black studs, a "
        "fanged red mouth snarling beneath. Dark slate-grey spikes jut to either side from a steel hub like "
        "chariot scythes, and a long tawny tail sweeps back to a green tuft. Leafy and wild, it charges like an "
        "overgrown jungle king."},
  {"Em0071_002",  // Brave Wheel
        "A beast of war built on a single wheel: a huge lion's head the height of a person, its spiky mane of "
        "blazing orange and red blades flaring like a bonfire, set over a big black wheel whose spokes are "
        "painted red. Its face is a yellow lion mask stamped VII, with narrow closed eye slits, clamped on with "
        "black studs, a fanged red mouth snarling beneath. Black spikes jut to either side from a red-ringed hub "
        "like chariot scythes, and a long rust-orange tail sweeps back to a flame-orange tuft. Fiery from mane to "
        "tail, it looks born to burn rubber."},
  {"Em0071_003",  // Dancing Beast Wheel
        "A beast of war built on a single wheel: a huge lion's head the height of a person, its spiky mane made "
        "of icy blue-white blades like shards of frost, set over a wheel with a pale ice-blue rim and polished "
        "gold spokes and hub. Its face is a yellow lion mask stamped VII, with narrow closed eye slits, clamped "
        "on with silver studs, a fanged mouth snarling beneath. Long gold spikes jut to either side like chariot "
        "scythes, and a tail shading from lilac to pale blue sweeps back to a frosty tuft. Glittering ice and "
        "gold, it is a regal, wintry war machine."},
  {"Em0072_000",  // Wild Drive
        "A hulking knight fused with a horse: a broad armoured torso set on four black, crooked horse legs ending "
        "in hooves. Its face is a yellow knight's mask with a T-shaped eye slit and a small VII, pinned inside a "
        "black mesh hood that wraps the neck like a scarf. It wears grey-silver segmented plate armour fastened "
        "with tan straps, a dull bronze shield at its belly and round shields of bronze and teal at its hips, and "
        "through its shoulders runs a massive grey-green cudgel studded with spikes. Heavy, grim and rearing, it "
        "is a jouster that tramples rather than rides."},
  {"Em0072_001",  // Killer Drive
        "A hulking knight fused with a horse: a broad armoured torso set on four black, crooked horse legs ending "
        "in hooves. Its face is a yellow knight's mask with a T-shaped eye slit and a small VII, pinned inside a "
        "dark green mesh hood that wraps the neck. Its armour is deep navy blue lined with bright blue seams and "
        "brown straps, with a faceted steel disc on each shoulder and round gold shields with teal bosses and "
        "copper rivets at its hips. Through its shoulders runs a long pale steel lance, pointed at both ends. "
        "Blue and gold, it is a dashing, deadly jouster."},
  {"Em0072_002",  // Slaughter Drive
        "A hulking knight fused with a horse: a broad armoured torso set on four black, crooked horse legs ending "
        "in hooves. Its face is a yellow knight's mask with a T-shaped eye slit and a small VII, pinned inside a "
        "hood of cream-white cloth. Its armour is glossy crimson trimmed in cream, its shields purple with red "
        "rims and cream bosses, and its belly plate purple engraved with a gold pattern. Through its shoulders "
        "runs a long golden blade with an ornate purple and gold crossguard. Red, gold and royal purple, it looks "
        "like a crusader charging under a banner."},
  {"Em0072_003",  // Rampage Drive
        "A hulking knight fused with a horse: a broad armoured torso set on four crooked horse legs, here a pale "
        "icy mint-white rather than black, ending in hooves. Its face is a yellow knight's mask with a T-shaped "
        "eye slit and a small VII, pinned inside a pale aqua mesh hood. Its armour shades from blue to teal with "
        "cream trim, its belly plate a vivid blue, and its round shields shimmer blue and teal inside gold rims. "
        "Through its shoulders runs a long lance of pale lavender steel, pointed at both ends. Frosty and "
        "gleaming, it is a ghostly knight of ice."},
  {"Em0073_000",  // Wicked Turret
        "A battle tank bigger than a car, wearing its armour like a pleated skirt: broad scalloped plates of "
        "charcoal grey, riveted and edged in gold zigzag trim, flaring out over six spoked road wheels on each "
        "side, their edges fringed like cloth. On top sits a gold-trimmed turret with a long black gun barrel, "
        "and its rounded roof is a smooth yellow dome with dark eye slits: the Shadow's mask, lying face up to "
        "the sky. Dark, gilded and heavy, it is a war chariot reborn as rolling artillery."},
  {"Em0073_001",  // Scarlet Turret
        "A battle tank bigger than a car, wearing its armour like a pleated skirt: broad scalloped plates of "
        "glossy crimson red, riveted and edged in silver-white zigzag trim, flaring out over six spoked road "
        "wheels on each side, their edges fringed like cloth. On top sits a crimson turret ringed in silver, with "
        "a long black gun barrel, and its rounded roof is a smooth yellow dome with dark eye slits: the Shadow's "
        "mask, lying face up to the sky. Bright red and silver, it looks like a parade tank out for blood."},
  {"Em0073_002",  // Wicked Turret
        "A battle tank bigger than a car, wearing its armour like a pleated skirt: broad scalloped plates of deep "
        "purple, strapped with riveted steel bands and edged in silver zigzag trim, flaring out over six spoked "
        "road wheels on each side, their edges fringed like cloth. On top sits a purple turret ringed in steel, "
        "with a long black gun barrel, and its rounded roof is a smooth yellow dome with dark eye slits: the "
        "Shadow's mask, lying face up to the sky. Bruise-purple and steel, it has a cruel, regal menace."},
  {"Em0073_003",  // Hallowed Turret
        "A battle tank bigger than a car, wearing its armour like a pleated skirt: broad scalloped plates of pale "
        "cream and blush sand, riveted and edged in silver zigzag trim, flaring out over six pale grey spoked "
        "road wheels on each side, their edges fringed like cloth. On top sits a cream turret ringed in silver, "
        "with a long gun barrel of polished brass, and its rounded roof is a smooth yellow dome with dark eye "
        "slits: the Shadow's mask, lying face up to the sky. Pale and burnished, it looks almost holy, a "
        "ceremonial war machine."},
  {"Em0073_004",  // ?
        "A battle tank bigger than a car, wearing its armour like a pleated skirt: broad scalloped plates painted "
        "in woodland camouflage blotches of olive, tan, black and green, with leafy ivy vines trailing across "
        "them, flaring out over six spoked road wheels on each side, their edges fringed like cloth. On top sits "
        "a dark green turret with a green gun barrel banded in bronze, and its rounded roof is a smooth yellow "
        "dome with dark eye slits: the Shadow's mask, lying face up to the sky. Overgrown and camouflaged, it "
        "looks as if it has lurked in a forest for years."},
  {"Em0073_005",  // ?
        "A battle tank bigger than a car, wearing its armour like a pleated skirt: broad scalloped plates of navy "
        "blue painted across the front and sides with hot-rod flames of yellow and red, edged in copper-orange "
        "zigzag trim, flaring out over six spoked road wheels on each side, their edges fringed like cloth. On "
        "top sits a navy turret ringed in copper, with a navy gun barrel banded in orange, and its rounded roof "
        "is a smooth yellow dome with dark eye slits: the Shadow's mask, lying face up to the sky. Loud and "
        "flashy, it is a muscle car of a tank."},
  {"Em0081_000",  // Voltaic Youngest Sibling
        "A tall samurai in gleaming white lacquered armour laced with green cord, its chest marked with a gold "
        "three-comma crest, over a body of black. Its face is a smooth cobalt-blue mask, calm and expressionless, "
        "with a Roman numeral eleven and a little diamond on the brow. A white helmet carries a gold crest of a "
        "central blade flanked by two sweeping horns, a navy capelet sits on its shoulders, and a long cloak "
        "hangs behind it, deep navy outside and blood red within. Arrows jut from its shoulder guards, and it "
        "bears an enormously long, thin curved sword. A pale, proud ghost who fought on full of arrows."},
  {"Em0081_001",  // Blazing Middle Sibling
        "A tall samurai in bright red lacquered armour edged with silver, over a black body, a gold three-comma "
        "crest on its chest. Its face is a smooth cobalt-blue mask, calm and expressionless, with a Roman numeral "
        "eleven on the brow, framed in gold. Instead of a horned helmet it wears a towering red cone of a hat, "
        "ribbed lengthwise with a gold disc on each side, taller than its head and neck together. A black capelet "
        "trimmed in gold and a long black cloak hang from its shoulders, arrows jut from its shoulder guards, and "
        "it bears an enormously long, thin curved sword. Fiery and imperious."},
  {"Em0081_002",  // Deadly Eldest Sibling
        "A tall samurai in dark violet lacquered armour edged with lilac, over a body of black, its chest marked "
        "with a blood-red three-comma crest. Its face is a smooth cobalt-blue mask with a Roman numeral eleven on "
        "the brow, and a black eyepatch strapped over one of its eyes. A dark purple helmet carries a single wide "
        "silver crescent moon as its crest, a plum-purple capelet sits on its shoulders, and a long cloak falls "
        "behind it, purple outside and sea-teal within. Red-fletched arrows jut from its shoulder guards, and it "
        "bears an enormously long, thin curved sword. A grim, one-eyed, battle-scarred veteran."},
  {"Em0081_003",  // Tenjin Musha
        "A tall samurai in cream and pale gold lacquered armour bound with green cord, over a body of pale "
        "blue-grey, its chest marked with a deep blue three-comma crest. Its face is a smooth cobalt-blue mask "
        "with a Roman numeral eleven on the brow. Its cream helmet carries a grand crest of a gold ring framed by "
        "two upswept, feathered wings, and a cream capelet and long cream cloak drape from its shoulders. Arrows "
        "jut from its shoulder guards, and it bears an enormously long, thin curved sword with a pale gold blade "
        "and a blue hilt. A radiant, serene heavenly general."},
  {"Em0082_000",  // Steel Gigas
        "A colossal, absurdly muscled giant built like a professional wrestler, its body pure glossy black and "
        "bulging with slabs of muscle, studded all over with round silver rivets down its chest, shoulders and "
        "legs. Its face is a smooth cobalt-blue mask with a Roman numeral eleven on the brow, clamped over a "
        "metal jaw-piece with bracket-like bars around the mouth. Long straight white hair spills from the back "
        "of its head. It wears nothing but silver wrestling briefs with a swirling pattern, silver wristbands and "
        "tall silver boots with ornate trim. A hulking, silent powerhouse, all brawn and no mercy."},
  {"Em0082_001",  // Profligate Gigas
        "A colossal, absurdly muscled giant built like a professional wrestler, its body glossy black and bulging "
        "with slabs of muscle, studded all over with round bronze rivets down its chest, shoulders and legs. Its "
        "face is a smooth cobalt-blue mask with a Roman numeral eleven on the brow, clamped over a metal "
        "jaw-piece with bracket-like bars around the mouth. Long straight golden-blond hair spills from the back "
        "of its head. It wears only gold wrestling briefs with an orange centre and swirling trim, gold "
        "wristbands and tall gold boots. Flashy and swaggering, a champion who wants the whole arena to see the "
        "gold."},
  {"Em0082_002",  // Daring Gigas
        "A colossal, absurdly muscled giant built like a professional wrestler, its body glossy black and bulging "
        "with slabs of muscle, studded all over with round rose-pink rivets. Its face is a smooth cobalt-blue "
        "mask with a Roman numeral eleven on the brow, clamped over a jaw-piece with pink bracket-like bars "
        "around the mouth. Long straight hair falls from the back of its head in a full rainbow, purple and red "
        "at the crown through orange and yellow to green at the tips. It wears pastel, rainbow-sheened wrestling "
        "briefs with a pink centre, pale teal wristbands and mint-green boots. A gaudy, show-stealing bruiser, "
        "loud in every colour at once."},
  {"Em0082_003",  // Ultimate Gigas
        "A colossal, absurdly muscled giant built like a professional wrestler, but this one's skin is chalk "
        "white, painted with bold red tribal flame markings that curl over its chest, shoulders, back and down "
        "the length of its legs. Grey rivets stud its muscles. Its face is a smooth cobalt-blue mask with a Roman "
        "numeral eleven on the brow, clamped over a jaw-piece with red bracket-like bars around the mouth, and "
        "long straight red hair spills from the back of its head. It wears plain black wrestling briefs, black "
        "wristbands and tall black boots. Pale as marble and striped like war paint, the ultimate heavyweight in "
        "its prime."},
  {"Em0082_004",  // ?
        "A colossal, absurdly muscled giant built like a professional wrestler, its skin a deep purple-black, "
        "painted with vivid green tribal flame markings over its chest, back, arms and calves, and studded with "
        "green rivets. Its face is a smooth cobalt-blue mask with a Roman numeral eleven on the brow, clamped "
        "over a metal jaw-piece with bracket-like bars around the mouth, and long straight bright green hair "
        "spills from the back of its head. Unlike its kin it wears longer green wrestling trunks reaching "
        "mid-thigh, trimmed with white spiky bands, plus green-banded wristbands and tall green boots. A "
        "toxic-looking brute, venom-green and very angry."},
  {"Em0083_000",  // Wild Beast
        "A big tawny lion, sandy gold in body with a thick, shaggy brown mane and pale, glaring eyes, standing on "
        "all fours with a long tail ending in a brown tuft. A heavy black iron collar engraved with patterns "
        "rings its neck under the mane, and dark iron chains hang from it, one dragging down to a huge black iron "
        "ball, wider than the lion's own head. Set into the far side of that ball is its face: a smooth "
        "cobalt-blue mask, calm and expressionless, with a Roman numeral eleven on the brow. A proud king of "
        "beasts shackled like a convict, the mask riding on its prison weight."},
  {"Em0083_001",  // Enslaved Beast
        "A big lion with a body the colour of dark green verdigris, as if cast in tarnished bronze, and a thick, "
        "shaggy mane of ashen grey, its eyes pale and cold. A long tail ends in a grey tuft. A black iron collar "
        "engraved with patterns rings its neck, and dark chains hang from it, one dragging down to a huge black "
        "iron ball wider than the lion's head. Set into the far side of the ball is its face: a smooth "
        "cobalt-blue mask, calm and expressionless, with a Roman numeral eleven on the brow. A sickly, "
        "statue-like beast, a temple guardian turned into a chained slave."},
  {"Em0083_002",  // Feral Beast
        "A big lion with a body of dusky purple and a thick, shaggy mane of pure black, its eyes burning red. A "
        "long tail ends in a black tuft. A bronze-studded collar engraved with patterns rings its neck under the "
        "mane, and dark iron chains hang from it, one dragging down to a huge black iron ball wider than the "
        "lion's head. Set into the far side of the ball is its face: a smooth cobalt-blue mask, calm and "
        "expressionless, with a Roman numeral eleven on the brow. Dark as a moonless night with eyes like embers, "
        "it looks savage and only barely held by its chains."},
  {"Em0083_003",  // Nemean Beast
        "A big white lion, its body pale grey-white as marble, with a thick, shaggy mane of olive-gold and "
        "piercing yellow eyes. A long tail ends in an olive tuft. A silver collar engraved with patterns rings "
        "its neck, and bright steel chains hang from it, one dragging down to a huge cracked grey stone ball "
        "wider than the lion's head. Set into the far side of the ball is its face: a smooth cobalt-blue mask, "
        "calm and expressionless, with a Roman numeral eleven on the brow. Regal and ghostly, a legendary lion "
        "out of myth whose hide no blade should pierce."},
  {"Em0083_004",  // ?
        "A big lion with a body of rich mustard gold and a thick, wild mane striped in black and bright yellow, "
        "like a thundercloud shot with lightning, its eyes glowing yellow. A long tail ends in a black and yellow "
        "tuft. A silver collar engraved with patterns rings its neck, and steel chains hang from it, one dragging "
        "down to a huge cracked grey stone ball wider than the lion's head. Set into the far side of the ball is "
        "its face: a smooth cobalt-blue mask, calm and expressionless, with a Roman numeral eleven on the brow. "
        "Bold and electric, it looks the fiercest and flashiest of its chained kind."},
  {"Em0084_000",  // Shadow of the Abyss
        "A monstrous heap of a creature, a huge black mound of lumpy, glistening flesh squatting like a giant "
        "toad, many times a person's size and streaked with blood red. Almost its whole front is a cavernous "
        "mouth, ringed with rows of blunt red teeth and ribbed red gums, a fat red tongue lolling on its lower "
        "jaw and a dangling red uvula at the back of its throat. A cluster of glossy red bulbous eyes sits on its "
        "brow, and stubby clawed feet with red talons poke out at the sides. Dozens of swords stand thrust into "
        "its back like a pincushion. A ravenous pit that swallows heroes whole."},
  {"Em0091_000",  // Black Raven
        "A large black raven with a heavy hooked beak, glossy dusk-black feathers and ragged, wide-spread wings, "
        "perched on the iron handle of a hanging lantern that holds a single white candle in a brass-coloured "
        "frame. Strapped across its breast by thin metal bands is its mask: a rust-orange plate with a single "
        "round black eye-hole in the middle, ringed by grooves, a Roman numeral nine above it and a grille of "
        "slits below, like a cyclops's face. The lantern sways beneath its talons as it flies. An ominous "
        "messenger of the night, lighting the way to nowhere good."},
  {"Em0091_001",  // Will O' Wisp Raven
        "A large black raven with a heavy hooked beak, its wings and long tail feathers fading from black through "
        "deep crimson and orange to tips of bright flame yellow, as if its feathers burn at the edges. It perches "
        "on the iron handle of a hanging lantern with a bronze-brown frame and a single white candle inside. "
        "Strapped across its breast is its mask: a rust-orange plate with a single round black eye-hole in the "
        "middle, ringed by grooves, a Roman numeral nine above it and a grille of slits below. A cruel firebird "
        "of a crow, smouldering and spiteful."},
  {"Em0091_002",  // Ruthless Ice Raven
        "A large black raven with a heavy hooked beak, its wings and long tail feathers fading from black through "
        "deep violet to tips of icy sky blue, like feathers rimed with frost. It perches on the iron handle of a "
        "hanging lantern with a cold grey steel frame and a single white candle inside. Strapped across its "
        "breast is its mask: a rust-orange plate with a single round black eye-hole in the middle, ringed by "
        "grooves, a Roman numeral nine above it and a grille of slits below. A chilly, merciless omen bird, "
        "carrying a frozen light."},
  {"Em0091_003",  // Amenti Raven
        "A large raven turned entirely white, its heavy hooked beak, feathers, legs and ragged, wide-spread wings "
        "all a pale ghostly grey-white. It perches on the handle of a hanging lantern with a black iron frame and "
        "a single white candle inside. Strapped across its breast, the only colour on it, is its mask: a "
        "rust-orange plate with a single round black eye-hole in the middle, ringed by grooves, a Roman numeral "
        "nine above it and a grille of slits below. A spectral bird out of the land of the dead, an eerie white "
        "guide for departing souls."},
  {"Em0092_000",  // Phantom Mage
        "A gaunt, floating phantom wrapped in a hooded cloak of tattered beige cloth, its hem cut into jagged "
        "points and its back stitched shut with a line of dark cross-stitches like a rag doll. Inside the hood is "
        "a rust-orange mask with a single round black eye-hole, ringed by grooves, a Roman numeral nine above and "
        "a grille of slits at the chin. A gold chain hangs at its throat over a ribbed black body, a brass "
        "lantern with a white candle hangs at its chest, and below dangle two long, spindly black legs tapering "
        "to points. A shabby, creeping wraith, the lowest apprentice of the dark arts."},
  {"Em0092_001",  // Phantom Master
        "A gaunt, floating phantom in a hooded cloak of deep black lined with dark purple and edged in grey, its "
        "hem splitting into long ragged points tipped with arrowhead spikes like a bat's wing. Inside the hood is "
        "a rust-orange mask with a single round black eye-hole, ringed by grooves, a Roman numeral nine above and "
        "a grille of slits at the chin. A silver chain hangs at its throat over a ribbed black body, a dark iron "
        "lantern with a white candle hangs at its chest, and two long, spindly black legs dangle below. Sinister "
        "and sharp-edged, a sorcerer grown into its power."},
  {"Em0092_002",  // Phantom Lord
        "A gaunt, floating phantom in a rich hooded cloak of emerald green lined with dark wine red and trimmed "
        "in gold, its pointed hem hung with little gold-capped green teardrop gems. Inside the hood is a "
        "rust-orange mask with a single round black eye-hole, ringed by grooves, a Roman numeral nine above and a "
        "grille of slits at the chin. A gold chain hangs at its throat over a ribbed black body, an ornate gold "
        "lantern with curling arms and dangling green gems holds a white candle at its chest, and two long, "
        "spindly black legs dangle below. Lavish and lordly, a necromancer dressed in jewels."},
  {"Em0092_003",  // Phantom King
        "A gaunt, floating phantom in a full, bell-shaped hooded cloak of creamy ivory, edged all round in soft "
        "lavender, worn and a little frayed. Inside the hood is a rust-orange mask with a single round black "
        "eye-hole, ringed by grooves, a Roman numeral nine above and a grille of slits at the chin. A gold chain "
        "hangs at its throat over a ribbed body of pale silver-white, a gold lantern with a pair of small "
        "feathered wings holds a white candle at its chest, and two long, spindly silver-white legs dangle below. "
        "Pale and stately, a ghostly king who glides as if on a holy errand."},
  {"Em0092_004",  // ?
        "A gaunt, floating phantom with a dark teal body and two long, spindly teal legs, wearing a plum-purple "
        "hood and short capelet from which long purple stoles hang in strips nearly to its feet, each embroidered "
        "with twisting gold glyphs. Gold-capped red teardrop gems dangle from the capelet's points. Inside the "
        "hood is a rust-orange mask with a single round black eye-hole, ringed by grooves, a Roman numeral nine "
        "above and a grille of slits at the chin. A gold chain hangs at its throat, and an ornate gold lantern "
        "set with a red gem holds a white candle at its chest. An arcane high priest wrapped in spells."},
  {"Em0093_000",  // Resentful Surveillant
        "A colossal disembodied head, a stern stone-grey face with a heavy brow, broad nose and grim, downturned "
        "mouth, two slanting rust-red stripes running from its crown down past its eyes. Its eyes are dark blue "
        "orbs ringed in pale yellow-green, and a long mane of blood-red hair pours from its scalp and spreads "
        "across the ground behind it like a cloak. Three more dark blue eyeballs float above its head, each with "
        "a black crow perched on top, wings flung wide. In the middle of its forehead is pinned a small "
        "copper-orange mask with a single round hole, marked IX, fixed by silver spikes. A brooding, all-seeing "
        "omen of death."},
  {"Em0093_001",  // Fate Seeker
        "A colossal disembodied head, a stern slate-grey face with a heavy brow, broad nose and grim, downturned "
        "mouth, two pale grey stripes slanting from its crown down past its eyes. Its eyes are glossy magenta "
        "orbs with violet rings, and a long mane of ash-grey hair pours from its scalp and spreads behind it like "
        "a ragged shroud. Three more magenta eyeballs float above its head, each with a black crow perched on "
        "top, wings flung wide. Pinned to its forehead by silver spikes is a small copper-orange mask with a "
        "single round hole, marked IX. Dull and dusty but for those vivid eyes, it watches like fate itself."},
  {"Em0093_002",  // Arcanist Decapitator
        "A colossal disembodied head, a stern charcoal-grey face with a heavy brow, broad nose and grim, "
        "downturned mouth, its skin plain and unmarked. Its eyes are cream-coloured eyeballs with bright sky-blue "
        "irises, staring wide, and a long mane of straw-blond hair pours from its scalp and spreads across the "
        "ground behind it. Three more cream eyeballs with blue irises float above its head, each with a black "
        "crow perched on top, wings flung wide. Pinned to its forehead by silver spikes is a small copper-orange "
        "mask with a single round hole, marked IX. With its pale gold mane and staring blue eyes, it looks like a "
        "fallen, haughty aristocrat."},
  {"Em0093_003",  // Appropriating Noble
        "A colossal disembodied head, its stern face a pale, ghostly lilac-white with a heavy brow, broad nose "
        "and grim mouth. Its eyes are black orbs with red-and-white bullseye irises, and thick streaks of dark "
        "blood run from both eyes down its cheeks. A long mane of silvery white hair pours down behind it. Three "
        "more black eyeballs with red centres float above its head, each with a white bird perched on top, wings "
        "flung wide. Pinned to its forehead by silver spikes is a small copper-orange mask with a single round "
        "hole, marked IX. A weeping, bloodless spectre of the river of the dead."},
  {"Em0101_000",  // Bronze Dice
        "A single giant die, a cube about as tall as a person, with thick bevelled charcoal-black edges framing "
        "dark grey faces. On one face is bolted its mask: a glossy green oval held by six silver pins, with two "
        "black spiral eyes stacked one above the other, a small X scratched beside them and a wide black crescent "
        "grin, giving it a dizzy, mocking leer. Another face shows two bright green pips joined by a green line, "
        "and the opposite face carries a gold skull and crossbones. A plain, dark gambler's die with a nasty "
        "sense of humour."},
  {"Em0101_001",  // Iron Dice
        "A single giant die, a cube about as tall as a person, with thick bevelled blood-red edges framing dark "
        "grey faces, the faces sculpted into shallow four-sided pyramids. On one face is bolted its mask: a "
        "glossy green oval held by six silver pins, with two black spiral eyes stacked one above the other, a "
        "small X beside them and a wide black crescent grin. Another face shows two hot-pink pips joined by a "
        "pink line, and the opposite face carries a pale aqua skull and crossbones. Red, pink and aqua make it "
        "louder and meaner than its dark grey sibling."},
  {"Em0102_000",  // Silver Dice
        "A pair of giant dice, side by side, each a cube with thick bevelled brassy olive-gold edges framing dark "
        "grey faces. Each die wears the same mask on one face: a glossy green oval held by six silver pins, with "
        "two black spiral eyes stacked one above the other, a small X beside them and a wide black crescent grin. "
        "Their side faces show two deep blue pips joined by a blue line, and their opposite faces each carry a "
        "silver skull and crossbones. Twin grins and twin skulls, they look like a loaded throw just waiting to "
        "come up deadly."},
  {"Em0102_001",  // Platinum Dice
        "A pair of giant dice, side by side, each a cube of pale icy blue-grey, its thick bevelled edges framing "
        "frosty faces. Each die wears the same mask on one face: a glossy green oval held by six silver pins, "
        "with two black spiral eyes stacked one above the other, a small X beside them and a wide black crescent "
        "grin. Their side faces show two deep blue pips joined by a blue line, and their opposite faces each "
        "carry a glossy black skull and crossbones. Cold and gleaming, the twins look like expensive dice with a "
        "very bad outcome in store."},
  {"Em0103_000",  // Terror Dice
        "A single giant die, a cube with bevelled charcoal-black edges and dark grey faces, set at the centre of "
        "a huge, razor-thin black ring that circles it like a planet's ring, many times wider than the die, "
        "tapering to sharp edges. On one face is bolted its mask: a glossy green oval held by silver pins, with "
        "two black spiral eyes, a small X and a wide black crescent grin. Another face shows two bright green "
        "pips joined by a green line, and the face opposite the mask a gold skull and crossbones. The blade-thin "
        "ring makes it look like a spinning die that could slice anything near it."},
  {"Em0103_001",  // Curse Dice
        "A single giant die, a cube with bevelled blood-red edges and dark grey faces sculpted into shallow "
        "pyramids, set at the centre of a huge, razor-thin crimson ring that circles it like a planet's ring, "
        "many times wider than the die and tapering to sharp edges. On one face is bolted its mask: a glossy "
        "green oval held by silver pins, with two black spiral eyes, a small X and a wide black crescent grin. "
        "Another face shows two hot-pink pips joined by a pink line, and the opposite face a pale aqua skull and "
        "crossbones. All red and pink, it looks like a curse spinning on its axis."},
  {"Em0104_000",  // Death Dice
        "Two giant dice stacked one above the other with a gap between them, each a cube with bevelled brassy "
        "olive-gold edges and dark grey faces. Through the gap runs a huge, razor-thin olive-gold ring, many "
        "times wider than the dice, like a planet's ring slicing between them. Each die wears the same mask on "
        "one face: a glossy green oval held by silver pins, with two black spiral eyes, a small X and a wide "
        "black crescent grin. Their sides show two deep blue pips joined by a line, and their backs silver skulls "
        "and crossbones. A grinning, blade-ringed tower of bad luck."},
  {"Em0104_001",  // Reckoning Dice
        "Two giant dice stacked one above the other with a gap between them, each a cube of pale icy blue-grey "
        "with thick bevelled edges. Through the gap runs a huge, razor-thin ring of the same frosty blue, many "
        "times wider than the dice, like a planet's ring slicing between them. Each die wears the same mask on "
        "one face: a glossy green oval held by silver pins, with two black spiral eyes, a small X and a wide "
        "black crescent grin. Their sides show two deep blue pips joined by a line, and their backs glossy black "
        "skulls and crossbones. Cold, gleaming and scornful, a tower of reckoning."},
  {"Em0105_000",  // Flowing Sand
        "A tall, gangly hourglass walking on legs: its body is a pale lavender glass hourglass, two swollen bulbs "
        "pinched to a narrow waist, bound by cream-white metal straps studded with plum-coloured rivets, with "
        "little clasps at the shoulders. Long, thin, charcoal-black arms hang from the top bulb almost to its "
        "knees, and two spindly black legs carry the lower bulb. Its mask is a small green dome capping the top "
        "of the glass, with a dark slit across it. A wide, flat olive-gold ring circles its narrow waist, "
        "engraved with strange lettering and fringed with feather-like blades. An eerie, stooping timekeeper with "
        "sand to spare."},
  {"Em0105_001",  // Ochlocratic Sand
        "A tall, gangly hourglass walking on legs: its body is a rose-red glass hourglass, two swollen bulbs "
        "pinched to a narrow waist, bound by cream-coloured metal straps studded with plum rivets, with little "
        "clasps at the shoulders. Long, thin, charcoal-black arms hang from the top bulb almost to its knees, and "
        "two spindly black legs carry the lower bulb. Its mask is a small green dome capping the top of the "
        "glass, with a dark slit across it. A wide, flat magenta ring circles its narrow waist, engraved with "
        "lettering and fringed with olive and pink feather-like blades. Warmer and angrier than its pale sibling, "
        "a mob's ticking clock."},
  {"Em0105_002",  // Rampaging Sand
        "A tall, gangly hourglass walking on legs: its body is a deep cobalt-blue glass hourglass, two swollen "
        "bulbs pinched to a narrow waist, bound by dark slate-grey metal straps studded with gold rivets, with "
        "little gold clasps at the shoulders. Long, thin, charcoal-black arms hang from the top bulb almost to "
        "its knees, and two spindly black legs carry the lower bulb. Its mask is a small green dome capping the "
        "top of the glass, with a dark slit across it. A wide, flat navy ring circles its narrow waist, inscribed "
        "with gold lettering and fringed with dark feather-like blades. A dark, rushing hourglass that never runs "
        "out."},
  {"Em0105_003",  // Eternal Sand
        "A tall, gangly hourglass walking on legs: its body is a pearly silver-white glass hourglass, two swollen "
        "bulbs pinched to a narrow waist, bound by pale tan metal straps studded with grey rivets. Unlike its "
        "dark-limbed siblings, its long, thin arms and spindly legs are an ivory cream, the arms hanging from the "
        "top bulb almost to its knees. Its mask is a small green dome capping the top of the glass, with a dark "
        "slit across it. A wide, flat cream-coloured ring circles its narrow waist, engraved with lettering and "
        "fringed with pale feather-like blades. Ghostly pale and patient, it looks like it could wait forever."},
  {"Em0111_000",  // Cruel Greatsword
        "A giant stone arm rising from a dark earthen mound, built of rough brown and tan masonry blocks, its "
        "hand raised with fingers spread and a teal carved bracelet around the wrist. Standing in front of it is "
        "a huge sword, point to the sky: a broad, steel-grey blade, a carved bronze-brown crossguard and grip, "
        "and a pale lavender gem set in the pommel near the ground. On the guard sits its mask, a grey-green "
        "shield-shaped plate bearing a bold black cross and the numeral VIII, pinned by silver spikes. Monumental "
        "and stern, like a crusader's grave marker come to life."},
  {"Em0111_001",  // Conviction Sword
        "A giant stone arm rising from a black earthen mound, built of rough blue-grey masonry blocks, its hand "
        "raised with fingers spread and a gold carved bracelet around the wrist. Standing in front of it is a "
        "huge sword, point to the sky: a broad, icy pale-blue blade, a black crossguard and grip, and a magenta "
        "gem set in the pommel near the ground. On the guard sits its mask, a grey-green shield-shaped plate "
        "bearing a bold black cross and the numeral VIII, pinned by silver spikes. Cold, blue and unbending, a "
        "monument to grim conviction."},
  {"Em0111_002",  // Judgment Sword
        "A giant stone arm rising from a dark green earthen mound, built of rough, mossy green masonry blocks, "
        "its hand raised with fingers spread and a bronze carved bracelet around the wrist. Standing in front of "
        "it is a huge sword, point to the sky: a broad, bright sky-blue blade, a carved olive-gold crossguard and "
        "grip, and a magenta gem set in the pommel near the ground. On the guard sits its mask, a grey-green "
        "shield-shaped plate bearing a bold black cross and the numeral VIII, pinned by silver spikes. Overgrown "
        "and ancient, it looks like a forgotten executioner's monument."},
  {"Em0111_003",  // Doom Sword
        "A giant stone arm rising from a slate-grey mound, built of pale grey, faintly lilac masonry blocks, its "
        "hand raised with fingers spread and a teal carved bracelet around the wrist. Standing in front of it is "
        "a huge sword, point to the sky: a broad, gleaming silver-blue blade, a black crossguard and grip, and a "
        "magenta gem set in the pommel near the ground. On the guard sits its mask, a grey-green shield-shaped "
        "plate bearing a bold black cross and the numeral VIII, pinned by silver spikes. Pale as a tombstone, it "
        "looks like a monument to doom itself."},
  {"Em0112_000",  // Heat Balance
        "A towering black iron cross, sharpened to a spike at its foot, hung with a giant pair of scales: each "
        "arm of the cross carries a chain and a shallow pan, the left one fiery red, the right one sky blue. "
        "Behind the cross turns a spiked wheel split down the middle, its left half bright red and its right half "
        "blue, black thorns jutting from its rim. At the crossing sits its mask, a grey-green shield-shaped plate "
        "bearing a bold black cross and the numeral VIII, pinned by silver spikes. Fire weighed against ice, a "
        "cold machine of judgement."},
  {"Em0112_001",  // Sky Balance
        "A towering black iron cross, sharpened to a spike at its foot, hung with a giant pair of scales: on the "
        "left arm a violet chain carries a deep, cone-shaped purple and blue pan, and on the right a green chain "
        "carries a stepped, ribbed green bowl fading to yellow-green at the bottom. Behind the cross turns a "
        "spiked wheel split down the middle, violet on the left and green on the right, black thorns jutting from "
        "its rim. At the crossing sits its mask, a grey-green shield-shaped plate bearing a bold black cross and "
        "the numeral VIII. A lopsided, unsettling judge of sky and earth."},
  {"Em0112_002",  // World Balance
        "A towering black iron cross inlaid with thin gold lines, sharpened to a spike at its foot, hung with a "
        "giant pair of gold scales, a shallow golden pan on a golden chain from each arm. Behind the cross turns "
        "a grand double wheel of gold, an inner ring and a larger outer ring joined by spokes, studded with "
        "silver spearhead spikes all around its rim. At the crossing sits its mask, a grey-green shield-shaped "
        "plate bearing a bold black cross and the numeral VIII, pinned by silver spikes. Richer and grander than "
        "its siblings, it looks like the final arbiter of all creation."},
  {"Em0112_003",  // Light Balance
        "A towering cross that shimmers in pastel iridescence, pale aqua, soft lilac and buttery yellow, warming "
        "to coral at its sharpened spike of a foot. A pair of scales hangs from its arms, a shallow silvery-blue "
        "pan on a silver chain at each side. Behind the cross turns a golden wheel with copper rivets, long "
        "golden spikes radiating from its rim like sunbeams. At the crossing sits its mask, a grey-green "
        "shield-shaped plate bearing a bold black cross and the numeral VIII, pinned by silver spikes. Bright and "
        "almost holy, a radiant judge of light."},
  {"Em0113_000",  // Order Giant
        "A towering giant built like a crumbling castle keep: its body and huge, blocky arms are stacked courses "
        "of weathered tan and brown stone, the shoulders rising as square turrets either side of a small broken "
        "tower for a head. In that tower sits a tiny pale green shield-shaped mask marked with a black cross, "
        "framed by a half-ring of iron-grey spikes. Down its front hangs an enormous steel broadsword with a "
        "carved copper-brown hilt, and below it a black cross on a chain carries little golden scales of justice. "
        "It looms like a fortress come to pass sentence."},
  {"Em0113_001",  // Merciless Judge
        "A towering giant built like a castle keep of blue-violet bricks with teal mortar, its body and huge, "
        "blocky arms all masonry, the shoulders rising as square turrets either side of a small broken tower for "
        "a head. In that tower sits a tiny pale green shield-shaped mask marked with a black cross, framed by a "
        "gold crescent collar bristling with blue spikes. Down its front hangs an enormous broadsword, blade and "
        "hilt in cold teal-blue with a magenta gem in the pommel, and below it a black cross on a chain carries "
        "little golden scales. It is a stern judge carved from night-coloured stone."},
  {"Em0113_002",  // ?
        "A towering giant built like a moss-covered castle keep: its body and huge, blocky arms are grey stone "
        "thick with bright green moss, the shoulders rising as square turrets either side of a small broken tower "
        "for a head. Its tiny pale green shield-shaped mask, marked with a black cross, is framed by a carved "
        "wheel of pale silver metal set with short spikes. Down its front hangs an enormous steel broadsword with "
        "an olive-gold hilt and a purple gem in the pommel, and below it a black cross on a chain carries little "
        "golden scales. It feels ancient and overgrown, a ruin still keeping order."},
  {"Em0113_003",  // Void Giant
        "A towering giant built like a frost-pale castle keep: its body and huge, blocky arms are bricks of white "
        "and soft lavender, the shoulders rising as square turrets either side of a small broken tower for a "
        "head. Its tiny shield-shaped mask, marked with a black cross, is framed by gold spikes, one tall spike "
        "shooting straight up above its head. Down its front hangs an enormous broadsword with a pale teal hilt "
        "and a magenta gem in the pommel, and below it a silvery cross on a chain carries little pale scales. Icy "
        "and lofty, it is a judge from a merciless heaven."},
  {"Em0113_004",  // ?
        "A towering giant built like a castle keep melting from within: its body and huge arms are black bricks "
        "with glowing orange and yellow molten seams between them, the shoulders rising as square turrets either "
        "side of a small broken tower for a head. Its tiny pale shield-shaped mask, marked with a black cross, is "
        "framed by a gold crescent collar of spikes. Down its front hangs an enormous broadsword with a grey iron "
        "hilt, an amber gem in the pommel and a glowing orange blade, and below it a dark cross on a chain "
        "carries little golden scales. It looks like a furnace that has learned to judge."},
  {"Em0121_000",  // Deviant Convict
        "A hulking bull-man with a body of hard black muscle, huge arms and thick thighs bending down into "
        "hooved, backward-jointed legs. A long, shaggy mane of sandy blond hair pours over its shoulders, and a "
        "bib of brown fur covers its chest and belly. Short cream horns curl up from its head, and its face is a "
        "smooth grey-blue mask of a sleeping face, eyes peacefully shut, the Roman numeral twelve over the mouth. "
        "A silver collar rings its neck, with heavy silver chains running to cuffs on both wrists. It is a brute "
        "in shackles, all bulk and quiet menace."},
  {"Em0121_001",  // Minotaur III
        "A hulking bull-man with a body of hard black muscle, huge arms and thick thighs bending into hooved, "
        "backward-jointed legs. A long mane of vivid violet hair falls over its shoulders above a bib of shaggy "
        "purple fur. Two tall, studded horns of tawny gold sweep high above its head, and its face is a smooth "
        "grey-blue mask of a sleeping face, eyes shut, the Roman numeral twelve over the mouth. A black iron "
        "collar rings its neck, with heavy black chains running to cuffs on both wrists. Dark and garish at once, "
        "it is a chained beast with a showy streak."},
  {"Em0121_002",  // Minotaur II
        "A hulking bull-man with a body of hard black muscle and hooved, backward-jointed legs, dressed for "
        "glory. Its long mane flares in streaks of red, orange and yellow like a blaze, over a bib of crimson "
        "fur. Its horns are deep red ringed and tipped with gold and swagged with strings of golden beads, and "
        "its face is a smooth grey-blue mask of a sleeping face, eyes shut, the Roman numeral twelve over the "
        "mouth. A gold collar and gold chains bind its neck and wrists, and on its chest hangs an ornate red and "
        "gold collar-piece of rings and dangling gold beads. It is a gilded gladiator in chains."},
  {"Em0121_003",  // Minotaur Nulla
        "A hulking bull-man drained of all colour: its huge, muscular body is ashen pale grey, from its heavy "
        "arms to the hooved, backward-jointed legs. A long mane of white hair spills over its shoulders above a "
        "bib of shaggy white fur. Two tall, pale bone horns curve up from its head, and its face is a smooth "
        "grey-blue mask of a sleeping face, eyes shut, the Roman numeral twelve over the mouth. A pale silver "
        "collar and silver chains bind its neck and wrists. It looks like the ghost of a minotaur, cold and "
        "bloodless."},
  {"Em0121_004",  // ?
        "A hulking bull-man with a body of hard navy-black muscle and hooved, backward-jointed legs. A long mane "
        "of sky-blue hair falls over its shoulders above a bib of shaggy blue fur. Its two curved horns are "
        "banded red and black, with a third, smaller horn jutting from its brow, and its face is a smooth "
        "grey-blue mask of a sleeping face, eyes shut, the Roman numeral twelve over the mouth. A red collar and "
        "blood-red chains bind its neck and wrists, and on its chest hangs a red collar-piece set with silver "
        "discs and a fringe of red beads. Cold blue and angry red, it looks ready to charge."},
  {"Em0122_000",  // Jotun of Power
        "A grotesquely fat giant with dark charcoal skin, a vast round belly and four thick arms, riding a "
        "child's rocking horse of weathered pale grey planks, riveted together, with a jagged mane and long "
        "curved rockers. Its small bald head wears a pale grey-blue mask of a sleeping face, brow furrowed, the "
        "Roman numeral twelve over the mouth. Purple-blue leather straps bind it everywhere: a collar with a "
        "ring, a band around the belly, cuffs at wrists, thighs and ankles. Two heavy rings set in its chest are "
        "joined by a sagging silver chain. Bloated, bound and rocking, it is a nightmare nursery toy."},
  {"Em0122_001",  // Jotun of Blood
        "A grotesquely fat giant with dark charcoal skin, a vast round belly and four thick arms, riding a "
        "rocking horse of salmon-pink planks, riveted together, with a jagged mane and long pink rockers. Its "
        "small bald head wears a pale grey-blue mask of a sleeping face, brow furrowed, the Roman numeral twelve "
        "over the mouth. Olive-green straps studded with orange bind its neck, wrists, thighs and ankles, a "
        "maroon band circles its belly, and two heavy rings set in its chest are joined by a sagging blood-red "
        "chain. The sweet pink horse makes the bloated, shackled rider all the more unsettling."},
  {"Em0122_002",  // Jotun of Evil
        "A grotesquely fat giant with dark olive-drab skin, a vast round belly and four thick arms, riding a "
        "rocking horse of dark gunmetal plates painted all over with staring gold and white eyes, with a mane of "
        "steel spikes. Its small bald head wears a pale grey-blue mask of a sleeping face, brow furrowed, the "
        "Roman numeral twelve over the mouth. Gold bands bind its neck, wrists, thighs and ankles, the collar and "
        "cuffs bristling with spikes, a dusky mauve band circles its belly, and two spiked rings in its chest are "
        "joined by a sagging gold chain. It looks rich, cruel and watched from every side."},
  {"Em0122_003",  // Genocidal Mercenary
        "A grotesquely fat giant with ghostly white skin, a vast round belly and four thick arms, riding a "
        "rocking horse of pale mint-green, faintly pearly plates with a jagged mane and long curved rockers. Its "
        "small bald head wears a darker grey mask of a sleeping face, brow furrowed, the Roman numeral twelve "
        "over the mouth. Dull teal straps bind its neck, belly, wrists, thighs and ankles, and two heavy rings "
        "set in its chest are joined by a sagging blood-red chain, sharp against all that pallor. Pale and "
        "swollen, it is a corpse-white nightmare on a toy horse."},
  {"Em0123_000",  // Mighty Cyclops
        "A muscular man with dark grey skin, hung upside down on a great steel wheel taller than a person. His "
        "ankles are clamped together and chained to the top of the rim, his arms bound behind him, a silver "
        "harness of straps and rings across his chest. At the bottom, his small grey mask with a dark numeral "
        "sits inside one huge blue eye. The wheel is a heavy steel ring studded with bolts and dark slots and "
        "edged all round with spikes, with an inner ring and eight barred spokes behind him. It is a single-eyed "
        "watcher on a torture wheel, helpless and terrible at once."},
  {"Em0123_001",  // Mad Cyclops
        "A muscular man with charcoal skin and black boots, hung upside down against a great round disc taller "
        "than a person. His ankles are clamped in a brass cuff and chained to the top, his arms bound behind him, "
        "a brass harness across his chest. At the bottom, his small grey mask with a dark numeral sits inside one "
        "huge yellow eye. The disc is deep violet etched with fine lines and painted with red flame-like petals "
        "around round black eyes, in a black rim of red panels and brass bolts ringed by violet cone-shaped "
        "studs, with brass chains looping down. Gaudy and occult, a sinister carnival target."},
  {"Em0123_002",  // Fierce Cyclops
        "A muscular man with charcoal skin and black boots, hung upside down against a great round disc taller "
        "than a person. His ankles are clamped in a steel cuff and chained to the top, his arms bound behind him, "
        "a steel harness across his chest. At the bottom, his small grey mask with a dark numeral sits inside one "
        "huge red eye. The disc is a bowl of mustard gold etched with fine radiating lines and rings of dark "
        "dots, framed in a thick black rim pierced with slots and bolts, edged all round with silver spikes and "
        "looped with silver chains. The angry red eye glares out of the gold like a furious sun."},
  {"Em0123_003",  // Chaos Cyclops
        "A muscular man with chalk-white skin, hung upside down against a great round disc taller than a person. "
        "His ankles are clamped in a black cuff and chained to the top, his arms bound behind him, and black "
        "leather straps and briefs harness his pale body. At the bottom, his small grey mask with a dark numeral "
        "sits inside one huge red eye. The disc is covered in deep crimson shaggy fur, framed in a silver-grey "
        "rim of slots and bolts edged all round with golden spikes, with pale gold chains looping down. White "
        "flesh on blood-red fur makes it lurid and hedonistic, a sinner pinned up for display."},
  {"Em0123_004",  // ?
        "A muscular man with dark plum-purple skin, hung upside down on a great wheel taller than a person. His "
        "ankles are clamped in cobalt-blue cuffs and chained to the top of the rim, his arms bound behind him, a "
        "cobalt harness across his chest. At the bottom, his small grey mask with a dark numeral sits inside one "
        "huge red eye. The wheel is a broad ring of icy, mottled sky-blue metal edged all round with blue spikes, "
        "with an inner ring and eight barred spokes behind him, and cobalt chains looping down. Frosty and stark, "
        "it looks like a prisoner frozen mid-punishment."},
  {"Em0123_005",  // ?
        "A muscular man with dark purple skin, hung upside down against a great round disc taller than a person. "
        "His ankles are clamped in red cuffs and chained to the top, his arms bound behind him, a red harness "
        "across his chest. At the bottom, his small grey mask with a dark numeral sits inside one huge teal-green "
        "eye. The disc is a bowl of glossy mint green fading to amber at its edge, in a bright green rim set with "
        "red bolts and pale lilac slots and edged with red-and-green spikes, with red chains looping down. It is "
        "garish as a festive ornament, and just as unsettling."},
  {"Em0131_000",  // The Reaper
        "A tall, gaunt figure of death in a long double-breasted coat of black and crimson with brass buttons, "
        "its high flared collar, sleeves and skirts torn into ragged tatters that trail to the ground, all of it "
        "spattered with blood. Its head is a hood soaked red, one bulging, bloodshot eye staring out, with a rope "
        "cinched around its neck like a noose. Long chains are slung crosswise over its body and loop in great "
        "arcs around it. In each black-gloved hand it holds a revolver with an absurdly long, slender silver "
        "barrel reaching nearly to the floor. It is pure dread: slow, silent, and always arriving."},
  {"Em0511_000",  // Priestess
        "A woman split exactly down the middle, one half jet black, the other bone white, sitting on the ground "
        "with her legs flung wide apart, one black and one white, her pale sea-blue skirts, edged with white "
        "lace, spread open between them and caught at the waist by a gold clasp. She is bare to the waist and "
        "thin enough that her ribs show on the white side, a letter on each breast, B on the black side and J on "
        "the white, the two pillars of a temple. A glossy magenta masquerade mask with pointed wings hides her "
        "eyes above dark lips, and a corkscrew ringlet hangs beside each cheek. From behind her head burst two "
        "vast fans of paper strips covered in tiny printed script and tipped in red, white on her black side and "
        "black on her white. Shameless and serene, she sits like a priestess who has thrown the temple doors open "
        "and dares you to read what is written."},
  {"Em0521_000",  // Empress
        "An absurd queen whose body is a huge riveted globe of dark slate-green metal with gold latches and a "
        "round gold medallion like the lock of a jewel box. Puffed teal-blue silk sleeves and bloomers frame it, "
        "and spindly black legs end in red high heels. Her impossibly long black neck is ringed with gold and "
        "hung with amethysts, a vast scalloped cream ruff dotted with gold stars fanning up behind it. Her face "
        "is a cream crown-shaped mask, eyes closed, marked with the Roman numeral three. Thin, gold-banded black "
        "arms trail a sheer pale aqua veil, and she carries a gold-headed sceptre. She is vain, regal and "
        "grotesquely grand."},
  {"Em0522_000",  // Emperor
        "A stiff king shaped like a walking shield: his torso is a long, rounded plate of dark teal-green studded "
        "with brass rosettes and emblazoned with a bold red cross, with a small round red face, eyes shut, at its "
        "foot. His face is a spiky purple crown-mask marked with the Roman numeral four. His shoulders swell into "
        "big ribbed teal puffs capped with brass and fringed with white tassels, a scarlet cape falls behind, and "
        "long sleeves end in white fur cuffs and black clawed hands. Below a short pleated skirt, thin black legs "
        "end in curled, pointed shoes. Pompous and rigid, he is a tyrant in tin-soldier form."},
  {"Em0531_000",  // Hierophant
        "A grotesque mock pontiff, two beings stacked into one. The lower is a squat, enormously round white "
        "body, its face a small round blue mask with glowing cyan eyes and a gaping mouth, set in a thick black "
        "hood. It wears a short scarlet cape, cyan-and-white striped breeches, black fishnets and red high heels, "
        "with a gilded throne frame strapped around its hips and a red banner of crossed pink and blue keys "
        "hanging down its front. From its back rises a slender, long-armed, full-breasted figure of white "
        "porcelain whose head is a branching golden tree studded with red jewels. Two white crosses float beside "
        "it, one marked with a black splash, one with a red rose. A sermon turned freak show."},
  {"Em0532_000",  // Lovers
        "A giant heart, deep glossy crimson, caged in riveted brass bands like a corset of armour, the bands "
        "along its top bristling with spikes. Thick branching limbs spread from its sides like antlers or bare "
        "wings, shading from blood red to violet, and long drips run down from heart and limbs as if it were "
        "melting. On its front is a pink female symbol fused with a blue arrow, and pink hearts outlined in black "
        "climb its side. Perched on top on a short black neck is a tiny pink mask with a sad, drooping face and a "
        "numeral on its brow. Pink and blue symbols of woman and man float beside it. Romance bleeding inside a "
        "cage."},
  {"Em0541_000",  // Chariot
        "A battered war machine of a tank, painted in mottled desert camouflage of sand, brown and moss green, "
        "standing high on four walking legs, each one a full caterpillar track looped around toothed wheels. Its "
        "boxy turret has a wide square hatch on the front, round headlamps flank the hull, and a vent grille sits "
        "behind. Painted on each side of the turret is a staring red-rimmed eye with a red pupil, and across the "
        "front of the hull a wide grinning mouth of red lips and white teeth. Rattling and lopsided, it looks "
        "like a child's drawing of war brought to clanking, hungry life."},
  {"Em0542_000",  // Justice
        "A small knight hovering on wings, stubby and doll-like in plain steel armour, a red sash slung across "
        "its chest and a red belt at its waist. Its round great helm is cut by a black cross-shaped visor with "
        "two yellow eyes glinting behind it and a Roman numeral on the brow. Behind it fan two big grey wings of "
        "riveted metal feathers, and behind its head a broad gold disc of pleated rays, embossed with a pair of "
        "scales and a cross. A short sword hangs point-down beneath its feet. Separate from it floats a long "
        "camouflage-painted cannon barrel with a boxy breech. Earnest, stiff and self-righteous, a tin-toy "
        "crusader of judgement."},
  {"Em0543_000",  // Tank-Form Shadow
        "A clanking union of tank and knight: a camouflaged war machine of sand, brown and moss green, standing "
        "high on four legs that are each a looping caterpillar track, with a long cannon jutting from its boxy "
        "turret. Staring red-rimmed eyes are painted on the turret's sides and a wide grin of red lips and white "
        "teeth across the hull, with round headlamps beside it. Slung underneath, between the tracks, hangs a "
        "little steel knight with a cross-visored great helm, a red sash, a short sword pointing down, two grey "
        "wings of riveted metal feathers and a gold sunburst disc behind its head, as if the tank were carrying "
        "its own crusader into battle. Loud, lumbering and absurdly menacing."},
  {"Em0551_000",  // Hermit
        "A hunched, towering beast of wire, its two legs nothing but thick bundles of cables in red, blue, green, "
        "black and yellow that knot and trail along the ground. Brass collars gather the bundles, and above them "
        "the legs turn to dark, scaly flesh arching into a black back traced all over with red circuit lines. "
        "Three black cylinders like old vacuum tubes, printed with white lettering, jut from its back. Its head "
        "is buried in a huge spiky mane of pale blue-grey flame-like spines, its face a small orange mask with a "
        "round black hole at its centre, like a lens or a speaker. It is a lurking broadcast monster, all static "
        "and eavesdropping."},
  {"Em0561_000",  // Fortune
        "A little brass mechanical beast seated like a sphinx at the hub of an enormous flat bronze wheel, many "
        "times its own size. Its scrolled golden body is riveted with gears and round glass portholes, a grey "
        "dome rides on its back with a ribbed fan of brass behind it, and a long dark chain with a small spiked "
        "ball at its end trails out like a tail. Its face is a green mask speckled with red, framed by a striped "
        "pharaoh-style headdress. Beside it on the great disc lies a long black block tapering to a needle-sharp "
        "silver point, like the wheel's pointer. It is a gambler's idol, a clockwork riddle on a wheel of chance."},
  {"Em0562_000",  // Strength
        "A tall, slender lady in a long cream gown that flares into a wide cone, with puffed white sleeves at her "
        "shoulders and a pink trim at her neckline. Her skin is jet black, long straight ash-blonde hair falls "
        "down her back, and her face is a smooth cobalt-blue mask with closed, sleepy eyes and a row of tiny dots "
        "around its edge. In one dark hand she holds a single red rose. The lower half of her gown is swallowed "
        "in a great bouquet of roses, lilies and sunflowers in every colour, tangled with green vines and "
        "trailing to a point. A pink ribbon swirls above her head, and a long wrought-iron fence of spear-tipped "
        "railings stands before her. Graceful, still and quietly sinister."},
  {"Em0571_000",  // Hanged Man
        "A massive grey-green brute hanging face down from a steel girder, its muscular body lashed up by hooks "
        "and straps, cuffed at the wrists and ankles, with dark hands and heavy black boots. Its head is a "
        "lavender-grey helmet with a Roman numeral above a black, glassy face plate ringed in teal, like a "
        "diver's or a welder's mask. Above it, chains run up to two long brass beams stacked one over the other, "
        "each sprouting ragged sky-blue wings of jagged feathers. The whole thing sways like a strung-up carcass "
        "on a crane, a hanged colossus suspended between heaven and the ground."},
  {"Em0572_000",  // Statue
        "A life-size statue of a woman carved in pale grey stone, standing on a low plinth. A long veil covers "
        "her head and falls over her shoulders in heavy folds to her feet, over a plain, high-waisted gown. Her "
        "eyes are lowered, her face is serene, and her hands are pressed together in prayer at her chest. Smooth "
        "and unadorned, it is the quiet, sorrowful image of a holy mother, peaceful yet eerie for standing where "
        "no statue should."},
  {"Em0581_000",  // Nyx Avatar
        "A dark, regal figure borne on great layered wings of black feathers, wider than a house, their "
        "undersides veined with glowing electric-blue lines like cracks of lightning. The body at their centre is "
        "slender and humanlike: a pale, gaunt face framed by spiky black hair, under a tall flat-crowned black "
        "hat with a thin gold band. It wears a fitted coat of black and gunmetal armour, the same blue veins "
        "glowing at its chest and forearms, with long clawed gauntlets and long coat panels hanging like a "
        "tattered robe. It holds a long, slim silver sword with a fine gold hilt. Cold and terribly calm, it "
        "carries itself like death in a dress uniform."},
  {"Em0582_000",  // Nyx Core
        "A huge egg-shaped orb, its shell a pearly swirl of pale sage green and bronze streaked like feathers or "
        "marbled silk, split down one side by a stepped zigzag seam, nested at the heart of a vast black tangle. "
        "Long ribbons and tattered sheets of jet-black matter spread outward like a burst flower or a ruined web, "
        "and from their ends reach dozens of thin, bony black arms ending in skeletal clawed hands, grasping in "
        "every direction. There is no face and no mask, only that cracked, shimmering core and its many withered "
        "hands. Silent and enormous, it feels less like a creature than the end of everything given shape."},
  {"Em0601_000",  // ?
        "A gaunt, two-headed beast with a skull at each end of its body. Each head is a long tan bone skull with "
        "a grinning mouth of jagged teeth and two glowing red bead eyes, crowned with long curving horns that "
        "sweep back like scythe blades. Between them stretches a hunched, muscular body of sooty black-brown "
        "flesh, ragged with dripping, shredded strands like wet rags, held up on four long, thin limbs ending in "
        "spindly clawed hands. With no mask and no front or back, it can prowl whichever way it likes, a "
        "nightmare of bone and tar."},
  {"Human_Chidori",  // Chidori
        "A pale young woman with the eerie, fragile beauty of a gothic porcelain doll. Very long red hair with "
        "blunt bangs falls to her waist, laced with white ribbons and crowned by a frilly white headdress pierced "
        "with a silver dagger-shaped pin. Her long white gothic-lolita dress is all tiers of ruffles and lace, "
        "with long white sleeves and a high frilled collar, down to chunky white platform boots with dark soles "
        "and silver ankle bands. From one hand trails a long, heavy chain ending in a small red-handled hatchet. "
        "Delicate to look at, unsettling to be near."},
  {"Human_Elizabeth",  // Elizabeth
        "A slender young woman with pale skin, the poised, faintly uncanny air of a doll-like hostess and a hint "
        "of quiet danger. Her short silver bob with straight blunt bangs frames bright yellow eyes under a small "
        "blue cap. She wears a sleeveless, high-collared dark blue dress, a stripe of lighter blue down its front "
        "set with large round brass-centred buttons like ringed targets, matching fingerless blue gauntlets on "
        "her forearms and tall, glossy blue boots over dark stockings. A thick leather-bound tome sits at her "
        "feet, ready to open. Elegant, perfectly composed and terrifyingly strong."},
  {"Human_Jin",  // Jin
        "A lean young man with the guarded, techy look of a back-room hacker who trusts nobody. His jaw-length "
        "dark blue hair falls over one eye behind narrow glasses with orange-tinted lenses. He's zipped into a "
        "bright green jacket with a tall collar hiding his chin, crossed by black buckled harness straps and "
        "bands, over baggy dark navy cargo trousers with thigh pockets. At his feet sits a chunky green and navy "
        "attache case, the kind that holds something far worse than paperwork. He looks wiry, watchful and ready "
        "to start throwing things."},
  {"Human_Takaya",  // Takaya
        "A gaunt, bare-chested man with the languid menace of a wandering prophet gone wrong. Long, wavy "
        "silver-grey hair falls past his shoulders, held off his face by a thin dark circlet, over sunken cheeks, "
        "stubble and unsettling yellow eyes. Purple and red tattoos of serpents and suns wind down both arms from "
        "shoulder to wrist. Below his pale, ribby torso he wears faded light-blue flared jeans on a white studded "
        "belt with a gold buckle, a ragged scrap of blood-red cloth hanging from his hip, and worn sandals, with "
        "a revolver kept close. Calm, barefaced and far too comfortable with violence."},
  {"Ps0001_000",  // Archangel
        "A dark-skinned warrior angel in the full kit of a medieval knight, a great pair of crimson feathered "
        "wings sweeping up around him. His round silver helmet has a perforated faceguard, gold trim and a tall "
        "spike flying a little red pennant marked with a black glyph, and beneath it his stern face glares with "
        "glowing green eyes. He wears fine silver chainmail over gold-edged plate arms and legs, a red leather "
        "strap across his chest, and a white tabard striped down the middle in red with a black star and glyph, "
        "cinched by a studded red belt. He carries a plain long sword: heaven's soldier, grim, disciplined and "
        "unbending."},
  {"Ps0001_010",  // Asura
        "A towering demigod of Indian legend with blazing red skin, a powerful bare chest and six arms fanning "
        "from his shoulders, each ringed with gold bands. His head has faces on three sides, the front one "
        "scowling with pale blue eyes, under a tall spiked gold helmet. Broad gold shoulder plates join a gold "
        "collar, a thin gold chain loops across his chest and a white sash crosses one shoulder. A gold buckle "
        "shaped like a snarling beast's face holds a skirt of layered gold plates over red-patterned white cloth, "
        "and gold rings stack around his ankles. He radiates fury, ready to strike with every hand at once."},
  {"Ps0001_020",  // Atavaka
        "A fearsome guardian deity of Buddhist lore with green skin, a muscular bare torso and a fan of eight "
        "arms. His head is a cluster of scowling faces with blood-red eyes and a red mark on the brow, under "
        "spiky royal-blue hair and a gold diadem, and a smaller head with its own blue topknot sits on top. "
        "Silver hoops hang from his ears. White scarves stream over a blue sash, baggy white trousers and ornate "
        "gold knee guards. His hands carry a tall gold trident hung with a red tassel, a gold sword, a gold "
        "ritual sceptre and a coiled black rope. He is wrathful protection given form."},
  {"Ps0001_030",  // Attis
        "A slender, unsettling figure wrapped from neck to toe in worn tan bandages like a mummy, the wrappings "
        "outlining a lean, muscled body. A shaggy mop of blond hair spills from his head, and two short, dark "
        "curved horns rise through the bandage binding his brow. His face is teal-skinned and crossed by pale "
        "white bands, leaving only narrow golden eyes showing, and his teal hands and feet carry the same pale "
        "stripes. Long ragged ribbons of bandage trail far out from his shoulders and back, and one hand holds a "
        "small curved blade. He seems bound, sacrificed and quietly tragic, a beauty hidden under his own "
        "wrappings."},
  {"Ps0001_040",  // Atropos
        "A tall, slim woman in a skin-tight black bodysuit finely pinstriped in grey, with black gloves and bare "
        "feet. Her head is swallowed by a tall grey cylinder of woven, interlocking lattice, like a basket or a "
        "cage, rising well above her crown and split down the front by a narrow gap. Through it you glimpse a "
        "pale face with glowing golden eyes and teal hair under a braided gold band. One hand holds a slender "
        "golden needle, and a long, thin black thread trails from her. She is one of the Greek Fates, the one who "
        "cuts life's thread: cold, impersonal, a silent keeper of endings."},
  {"Ps0001_050",  // Ananta
        "An enormous serpent of Hindu myth with seven cobra heads rising together from one trunk like the fingers "
        "of an opening hand. Each broad, flared hood is salmon-pink and ribbed in front, mottled sea-blue scales "
        "behind marked with pale green rings, and each head stares with small yellow eyes. Ornate gold bands "
        "clasp the necks together, and below them a gold collar with a hanging gold ornament holds a draped white "
        "cloth. Beneath, the body becomes one thick blue and pink serpent tail stretching far along the ground. "
        "It feels ancient, vast and serene, a cosmic being older than the world itself."},
  {"Ps0001_060",  // Anubis
        "A jackal-headed god of ancient Egypt, jet black from head to foot, sitting cross-legged in mid-air. His "
        "long, narrow muzzle and two very tall, pointed ears give him a sharp, elegant silhouette, and his eyes "
        "are rimmed in red with teal irises. A bright blue and white striped headcloth drapes behind his head in "
        "two flat lappets. A broad silver and gold collar with a red inner band circles his neck, silver bands "
        "ring his arms, and he wears a white pleated kilt tied with a teal sash. One hand holds up golden balance "
        "scales with two hanging pans. He is calm, aloof and utterly impartial, the weigher of hearts."},
  {"Ps0001_070",  // Abaddon
        "A colossal mound of olive-green flesh, wider than it is tall, made almost entirely of a gaping mouth. "
        "Its lumpy hide is covered in small pointed warts, and the whole bulk slumps down at the back like a "
        "melting hill. Near the top two round yellow eyes and a flat nose sit above a vast open maw ringed with "
        "big, square white teeth, its throat a deep red cavern with a huge red tongue rolling at the bottom. "
        "Small clawed hands stick out at either side of its base. It is a bottomless pit of hunger, a demon of "
        "the abyss ready to swallow anything whole."},
  {"Ps0001_080",  // Apsaras
        "A graceful celestial dancer with smooth pale blue skin and a slender, shapely figure. Her deep navy hair "
        "is pinned into two round buns at the sides of her head, held by a silver circlet with a blue teardrop "
        "jewel on her forehead, and she wears blue teardrop earrings and a choker of blue gems. A fitted white "
        "wrap top edged in silver, a belt of glossy blue teardrop gems and a short skirt of sheer mint-green silk "
        "dress her, with silver anklets on bare feet. A long ribbon of sheer green fabric arcs over her head. She "
        "has the airy, serene allure of a heavenly nymph."},
  {"Ps0001_090",  // Arahabaki
        "A squat, chunky figure like an ancient Japanese clay idol, cast all over in dark teal stone with a faint "
        "mottled sheen. Its big round head is dominated by two enormous goggle eyes with thin glowing orange "
        "slits, framed by a spiky rim, above a small round open mouth, with a tall ornamental finial on top. The "
        "body is all bulging curves: wide rounded shoulders flaring into short ridged stumps of arms with small "
        "claws, two round swellings on the chest, a flared skirt-like waist and thick, bulbous legs. It feels "
        "ancient, mysterious and a little alien, an earthbound guardian with a strange, sleepy watchfulness."},
  {"Ps0001_100",  // Ara Mitama
        "A glossy, blood-red spirit shaped like a giant comma: a big round head that tapers down and curls into a "
        "long pointed tail, like the curved jewel of Japanese tradition. There is no body, just that smooth, "
        "plump teardrop of red, larger than a person's torso. Its face is pure rage: heavy, thickly furrowed "
        "brows, fierce white eyes outlined in black, a flared nose and a wide, grimacing mouth baring a solid row "
        "of clenched white teeth. It is the raging, wild side of the soul given shape, all hot temper and "
        "violence with nowhere to hide."},
  {"Ps0001_110",  // Alice
        "A little girl with long, straight blonde hair, a neat fringe cut straight across her brow and a white "
        "headband, with large amber eyes in a pale, doll-like face. She wears a royal purple dress with short "
        "puffed sleeves cuffed in white, a frilled white collar and a thin black ribbon at the throat. A broad "
        "white sash ties in a big bow at the back, a frilled white petticoat peeks below the full skirt, and "
        "black strapped shoes finish the look. Sweet as a storybook child, she is also eerily blank and still, "
        "the kind of little girl who asks you to please die for her."},
  {"Ps0001_120",  // Alilat
        "A tall, double-pointed crystal of dusky rose stone, a long six-sided column tapering to a sharp point at "
        "each end, as tall as a person. Bold red lines are carved into every face. Each side bears the same "
        "stylised goddess figure, like an ancient fertility idol: a domed, striped head, almond eyes, full round "
        "breasts, a narrow waist and broad hips over two short legs. The pointed ends each bear a pair of "
        "concentric circles crossed by a straight line, like watchful eyes. It feels primeval and sacred, a "
        "desert goddess reduced to a carved talisman, silent and powerful."},
  {"Ps0002_000",  // Inugami
        "A dog spirit of Japanese folk curses, a black dog's head on an absurdly long, thin white body that "
        "stretches far down like a ribbon and ends in a long pale tail. The head is jet black with tall, pointed "
        "ears, glaring red eyes, a tangled red sigil on its brow and a wide grin packed with sharp white fangs "
        "and red gums. Below its neck two small white forelegs end in black claws, and far down the body two "
        "little hind legs dangle. It wears nothing at all. It looks spiteful and vengeful, a grudge that never "
        "lets go, coiling after its target."},
  {"Ps0002_010",  // Incubus
        "A wiry little demon with dusty pink skin, a scrawny, rib-showing body and long spindly limbs whose hands "
        "and feet darken to black claws. His bald, elongated head has pointed ears, long curling antennae and a "
        "grinning face with yellow eyes, a sharp chin and a wide, smug smile. A ruff of black fur rings his neck, "
        "and two bat wings rise high from his back, pink bony frames stretching black membranes. He wears only "
        "black briefs and a belt, with a curved red horn mottled with dark spots at his hip, and a long thin tail "
        "ends in an arrowhead. He oozes sleazy, leering mischief."},
  {"Ps0003_000",  // Virtue
        "A heavenly figure that looks carved from dark green stone with a faint verdigris speckle, like an old "
        "weathered statue. She has the graceful, curving figure of a woman, unclothed and smooth as sculpture, "
        "with short, softly waved hair, and her arms are folded up across her chest. A pair of long, narrow "
        "feathered wings sweeps down from her shoulders, nearly as long as she is tall. Every part of her, wings "
        "included, is the same single colour of deep green stone. She feels solemn, pure and still, an angel of "
        "grace frozen in quiet devotion."},
  {"Ps0003_010",  // Vasuki
        "A serpent king of Hindu myth: a humanoid upper body on an immensely long, thin snake tail of banded "
        "purple scales that stretches far below. His pale face has purple paint around the eyes and a jewel on "
        "the brow, framed by long red hair, under a spiky gold crown set before a grey cobra hood painted with "
        "two staring green eyes and topped with a gold spire. Two long gold feelers tipped in green sway above. "
        "Six arms fan around him, tattooed with dark patterns and wrapped in grey bracers with gold bands, teal "
        "tassels hanging down. He is a strange, regal serpent of the deep."},
  {"Ps0003_020",  // Valkyrie
        "A Norse warrior maiden riding a red horse. She has tan skin, red lips and golden blonde hair swept up "
        "into a tall, curling crest, with a silver half-mask whose sides flare into small silver wings. She wears "
        "a fitted brown leather bodysuit with silver scale armour panels, dark gloves with silver cuffs, black "
        "boots and a long dark brown cape lined in cream, and carries a long silver sword with a blue guard. Her "
        "crimson steed has a red mane and tail tipped in gold, gold hooves, and a round red shield with a silver "
        "emblem at its side. She looks fierce and gallant, a chooser of the slain."},
  {"Ps0003_030",  // Vishnu
        "A preserver god of Hindu myth with smooth golden-yellow skin, a lean muscled build and four arms. His "
        "long black hair rises in a topknot under a tall silver crown, framing a calm, handsome face with pointed "
        "ears and teal eyes. Thick silver coils loop around his body, curling into two scrolls behind his "
        "shoulders, and a silver chain with a red jewel hangs at his chest. He wears a light blue wrap skirt with "
        "a red jewel at the belt. His hands hold a heavy silver mace, a pink spiral conch shell, a silver discus "
        "ring and a pink lotus flower. He radiates serene, confident divinity."},
  {"Ps0003_040",  // Uriel
        "An archangel with smooth pale blue skin, short tousled brown hair and piercing golden eyes in a stern, "
        "youthful face. Two great wings rise from his back, cream-feathered in front and pale sky-blue behind. He "
        "wears fitted magenta armour with high shoulder guards and a standing collar, under a long white tabard "
        "edged in gold and marked with gold crosses down its length, tied with a knotted gold sash whose ends "
        "hang to his knees. Magenta boots and greaves finish his legs. He grips a long sword with a gold hilt and "
        "a blade shimmering from blue to violet. He looks righteous and severe, heaven's judge in arms."},
  {"Ps0004_000",  // Eligor
        "A demon knight in gleaming blood-red plate armour from head to toe, every limb sheathed in layered, "
        "ridged plates. His closed helmet is crowned by two big, curved brown ram's horns, with a narrow visor "
        "slit through which two small white eyes glow, and a shaggy grey fur mantle bunches over his shoulders. A "
        "long dark purple cape falls behind him, and he wields a long, thin spear. He rides a dark navy-black "
        "horse with a wild, pale silvery-green mane and tail, a plain brown saddle, a bridle and hanging "
        "stirrups. Together they look like a nightmare cavalry charge, a duke of hell leading his war host."},
  {"Ps0004_010",  // Angel
        "A winged woman with long, wavy dark blonde hair and pale skin, two broad white-grey feathered wings "
        "spread wide from her back. A dark band blindfolds her eyes, printed with a single open eye, and below it "
        "her red lips are just parted. A black collar circles her neck, and a heavy steel chain hangs from it "
        "straight down her front to her knees. Her outfit is little more than black straps: a strapless band "
        "across her chest, a wide belt at her waist and short black shorts, and she is barefoot. Heavenly and "
        "bound at once, she looks strikingly provocative for an angel."},
  {"Ps0005_000",  // Okuninushi
        "A young man of ancient Japanese myth with long, straight black hair, part of it looped into two round "
        "coils on top of his head, held by a thin red headband, and calm brown eyes in a gentle, fine-boned face. "
        "He wears armour of grey metal plates laced in rows with red cords over a white robe with loose sleeves, "
        "and baggy white trousers bound at the knees with red cords. A necklace of dark beads and orange "
        "claw-shaped jewels hangs at his throat, and he carries a long, straight, double-edged sword, its sheath "
        "at his waist. He looks noble, kind and quietly capable, more healer than conqueror."},
  {"Ps0005_010",  // ?
        "A tall, lean all-father of Norse myth with dusky purple skin and a hard, muscled body. His long black "
        "hair falls past his shoulders from under a gold helmet with a pointed nose guard, from which two tall, "
        "curving gold horns sweep straight up like blades. Beneath it his eyes glow a cold pale white. He wears "
        "little more than a white cloth wrapped at his hips and a long white cloak with a gathered collar falling "
        "to the ground behind him, and he grips a very long, slender dark spear. He has the cold, distant "
        "presence of a king of gods, wise, severe and terrible in battle."},
  {"Ps0005_020",  // Ose
        "A tall leopard-man with tawny spotted fur, a strong, lean muscled body and a long spotted tail. His "
        "cat's face is sly, with teal eyes, whiskers and a wide, toothy grin, rising out of a high, stiff green "
        "collar that zips up the front like a hood. A short green cape flows into a long cloak, green outside and "
        "dark wine-red inside, reaching the ground. Polished silver bands guard his forearms and a silver plate "
        "covers his hips. He wields a slender, needle-thin sword with a green-wrapped hilt and gold fittings. He "
        "carries himself like a cocky, cunning duellist, a hell-born predator with a gentleman's swagger."},
  {"Ps0005_030",  // Oni
        "A huge, burly ogre of Japanese folklore with brick-red skin, bulging muscles and broad shoulders. His "
        "head has two short black horns, a tall spike of blond hair standing straight up, and a scowling face "
        "with fierce glowing blue eyes, a heavy brow and a jaw full of jagged grey fangs, silver rings hanging "
        "from his ears. A short navy cape with a white collar is printed with purple square crests, and his baggy "
        "navy shorts carry matching purple diamonds over a dark sash and white leg wraps. He swings a huge "
        "long-handled iron cleaver. He looks brutish and rowdy, a hard-hitting brawler spoiling for a fight."},
  {"Ps0005_040",  // Oberon
        "A fairy king with a pale, porcelain face, ice-blue eyes and long straight black hair under a tall gold "
        "crown striped in black and set with square red jewels. He is dressed like a toy soldier in a regal red "
        "military jacket with puffed sleeves, gold toggles, a red jewelled clasp, a dark diagonal strap and black "
        "belt, short red flared trunks, white tights and tall black boots. From his back spread four huge black "
        "butterfly wings, veined in dark green and dotted with pale olive-yellow spots, the lower ones ending in "
        "long swallowtails. He holds a slender rapier. He is a proud, theatrical, mischievous monarch."},
  {"Ps0005_050",  // Omoikane
        "A floating human brain the size of a boulder, pinkish-orange and deeply folded, with two round glossy "
        "blue eyes peering out low on its front. Beneath it trails a tangle of long, limp fleshy tendrils, like a "
        "jellyfish's, and one straight stalk drops far below, ending in a pointed, leaf-shaped tip. Thin fleshy "
        "rods spear clean through the brain from side to side, some ending in more staring blue eyes on swollen "
        "stalks, others in flat, frilled fin-like tips. A Japanese god of wisdom pictured as pure, naked thought: "
        "unsettling, cerebral and quietly watching everything at once."},
  {"Ps0005_060",  // Orthrus
        "A huge two-headed hound, bigger than a horse, with a lean, long-legged body in dull mustard-gold fur and "
        "clawed paws. A dark teal-black mane of ragged, spiky fur bristles over both shoulders and down its chest "
        "and back. Its two wolfish heads sit side by side, each with tall pointed ears lined in purple, piercing "
        "teal eyes and snarling jaws full of sharp teeth. Behind it stretches a startlingly long, whip-thin tail "
        "of purple segmented scales, studded along its top with small spikes. The guard dog of Greek myth, twice "
        "as watchful and twice as hungry."},
  {"Ps0005_070",  // Orobas
        "A tall, wiry horse-man: a muscular, man-shaped body in deep crimson skin, fading to pale cream on the "
        "chest, throat and lower legs, with a lean, ribbed belly. On his shoulders sits a full horse's head with "
        "a crimson face, a pale blaze down the nose, glinting green eyes and bared, flat teeth set in a toothy "
        "grin. A thick, wild mane of dark green hair tumbles over his head and shoulders, and a matching green "
        "horse's tail sweeps out behind. His legs end in tan hooves. A demonic stallion standing upright, uncanny "
        "and a little too eager to talk."},
  {"Ps0005_080",  // Onmoraki
        "A strange little creature like a scrawny plucked bird crowned with an onion. Its head is a big, pale "
        "cream bulb topped by a twisting green shoot, with two sleepy, half-closed eyes and a wide, black, gaping "
        "grin stretching right across it. The bulb hangs off a thin neck striped in dark brown and cream rings, "
        "joined to a round, pot-bellied body of bare, pinkish-tan skin, with spindly arms ending in splayed "
        "little claws and skinny, bony bird legs. Part vegetable, part naked chick, it looks gormless, eerie and "
        "faintly ghoulish, a lost soul in a ridiculous body."},
  {"Ps0011_000",  // Kali
        "A fearsome six-armed goddess of Hindu legend with blood-red skin, slicked-back black hair falling to her "
        "shoulders, a green jewel set like a third eye in her forehead, glaring green eyes and small fangs. Her "
        "torso is cased in a ribbed breastplate of silver-grey plates, studded with blue gems, and a gold rope "
        "belt holds a carved skull at her waist. A grey apron swirls over a navy fringed skirt, and a girdle of "
        "grinning skulls rings her hips. Four of her hands grip long, sweeping curved blades with bone hilts. She "
        "is wrath given a body, gorgeous and terrifying."},
  {"Ps0011_010",  // Ganesha
        "A big, pot-bellied elephant-headed god of Hindu legend with smooth dusky blue skin, sturdy limbs and "
        "bare feet. Large pink-lined ears fan out from beneath a golden domed helmet ridged like a melon, studded "
        "with rubies and topped by a stacked gold crown. One ivory tusk curves proudly, the other is snapped off "
        "short. A wide collar of green bands and gold plates covers his shoulders, a string of gold beads hangs "
        "over his round belly, and a white loincloth, gold side guards and a green front panel cover his hips. He "
        "carries a long curved sword. Jolly-looking, but every inch a warrior."},
  {"Ps0011_020",  // Hua Po
        "A small, slender fairy with butterfly wings and red skin. Her hair is black on top, falling in two long, "
        "straight curtains of bright orange-gold either side of her face, framing big green eyes and a sweet "
        "smile. She wears a short cream Chinese-style tunic dress with a high collar and black knotted buttons "
        "down the front, its long sleeves printed with orange and pink blossoms, and little orange slippers. "
        "Behind her spread four large, gauzy butterfly wings that shade from yellow-green into purple and deep "
        "blue at the tips. A bright, flitting little flower spirit, playful and full of mischief."},
  {"Ps0011_030",  // ?
        "A tall, graceful angel with sage-green skin, long wavy black hair and amber eyes, small silver cross "
        "earrings hanging from her ears. Her chest and stomach are cased in a sculpted gold cuirass with flared "
        "shoulder guards and a high collar, over a long, flowing white gown banded in crimson, patterned with red "
        "diamonds and edged with a deep red hem. Two great feathered wings rise from her back, pale grey-green in "
        "front and rich green behind. In one hand she holds a slim sword, in the other a long stem of orange "
        "lilies. Serene, noble and quietly stern, a herald of heaven."},
  {"Ps0011_040",  // Garuda
        "A great bird-man of Hindu legend with a lean, tan human body, bird's talons for feet and broad brown "
        "feathered wings spreading far to either side. His head is an eagle's, with a hooked yellow beak and blue "
        "eyes, crowned by a tall, ornate golden headdress. Rounded gold pauldrons set with blue jewels cap his "
        "shoulders, and a red cloth wraps his hips. A long hanging banner of red, white and blue swirls drops "
        "down his front, gold bands circle his ankles, and a long, thin, stiff tail juts out behind him. Proud, "
        "regal and fiercely airborne, the king of birds."},
  {"Ps0011_050",  // Ganga
        "A serpent goddess of an Indian holy river: a pale, blue-white woman from the waist up, sinking into an "
        "immensely long snake's tail of fine silvery scales with a ribbed dark grey underside, tapering to a "
        "needle point far below. Fanned out from her arms are two sail-like fins of coral-red membrane, ribbed "
        "with pale spines. Her head carries a tall, stacked golden crown above a fan of cream, pleated cloth, a "
        "red jewel sits on her brow, and her eyes are pale green. A small gold bra hung with red tassels covers "
        "her chest. Elegant, cool and sinuous, she flows rather than stands."},
  {"Ps0012_000",  // Kaiwan
        "A huge five-pointed star with a face in its heart. The star's spikes are charcoal black, slashed with "
        "wavy grey stripes, and plain black behind. In the middle sits a long, pale grey face with pointed ears, "
        "a ridged, lilac-tinged forehead, deep frown lines, a heavy downturned mouth and small blood-red eyes. "
        "Around it writhe thick, twisting purple tendrils, rising like flames above the head and trailing below "
        "like a long, ragged beard. A star god of ill omen, gloomy, brooding and very far from a wish upon a "
        "star."},
  {"Ps0012_010",  // Kikuri-Hime
        "A tall, regal goddess with dark charcoal skin, pale blue eyes and lips, and very long, straight white "
        "hair falling to her waist. At each side of her head sits a big pink-red ornament shaped like a lotus "
        "seed pod, pocked with round holes. She wears a fitted top banded in red, cream and black, tied at the "
        "front with a thin black cord, and at her hips two round pink lotus buds with green petals. Long white "
        "tassels dangle at her sides, and a vast, pleated red mantle with a black hem drapes from her arms to the "
        "ground. Barefoot, she is calm, solemn and quietly otherworldly."},
  {"Ps0012_020",  // Chimera
        "A three-headed beast out of Greek myth, larger than a horse, with a sleek tawny lion's body and clawed "
        "paws. At the front is a snarling lion's head buried in a thick, shaggy golden mane, with red eyes and "
        "bared fangs. Rising from its back is a long-necked black goat's head, with a flowing grey-black mane, "
        "glaring yellow-green eyes and long, ridged, curving horns. Its tail is an enormous serpent, scaled in "
        "bright blue with purple bands and a row of small spikes, stretching far behind it to a blue snake's "
        "head. Mismatched, ferocious and unpredictable, every head wanting a bite."},
  {"Ps0012_030",  // Cybele
        "A tall, curvy goddess with vivid blue skin, painted all over in swooping white stripes that curl around "
        "her body like ribbons, over the curves of her bust and hips, so that she seems clothed in nothing but "
        "paint. Long, ridged brown ram's horns sweep back from her head, and her glossy black hair falls in a "
        "long ponytail to her knees, with a fringe across one eye. She has pointed ears, sultry amber eyes and "
        "dark lips curled in a knowing smile. In each hand she holds a slim, curved sword with a bronze hilt. "
        "Sensual, untamed and dangerously alluring."},
  {"Ps0012_040",  // Girimekhala
        "A massive, pot-bellied elephant demon with teal-blue skin streaked with dark tiger-like stripes. Its "
        "head has a single huge purple eye in the middle of the brow, a long trunk, broad ears and two great "
        "curving ivory tusks, and a few wiry black hairs sprout from its crown. Heavy gold shoulder guards with "
        "curling engravings cap its shoulders over a dark band, a thick black sash wraps its belly with a round "
        "gold medallion hanging below, and gold bands circle its arms and ankles. It carries a long, curved "
        "sword. Cyclopean, lumbering and brutish, a living siege engine."},
  {"Ps0012_050",  // King Frost
        "A pint-sized snowman king riding an enormous golden war machine. His head is a round white snowball with "
        "a black, fanged grinning mouth and two oval black eyes, ringed by a white fur collar and framed by rolls "
        "of powdered, curly blond wig. A tall, spiked gold crown with a white snowflake emblem rises above. His "
        "body is a huge dome of riveted gold metal, split by black seams, with black hinges, handles, a big "
        "padlock on the front and arched wheel openings at the sides; two gold pipes rise behind him beside a red "
        "bow. A white mitten holds an outsized gold key. Pompous, silly and pleased with himself."},
  {"Ps0013_000",  // Queen Medb
        "A tall, statuesque queen of Irish legend with a cloud of wild lilac-pink hair spilling to her waist, her "
        "face hidden behind a sharp green mask with red slanted eye slits. A cropped bolero of cream scales "
        "covers her shoulders over a shiny silver bra, and below it a skin-tight bodysuit in green, purple and "
        "cream chevrons hugs her long legs. Her forearms are lost in huge, fluffy lilac fur cuffs, her hands in "
        "glossy red claw-tipped gloves, and a long cape of cream scales falls behind her to the ground. "
        "Seductive, imperious and hungry, a queen who takes what she wants."},
  {"Ps0013_010",  // Cu Chulainn
        "A tall, handsome warrior from Irish legend with long, straight black hair, cool blue eyes and a serious "
        "face, crowned by a white circlet set with a violet diamond. He wears sleek white armour outlined in "
        "violet and black, with high collar, layered pauldrons and bracers, over a dark chainmail skirt, plus "
        "dark violet gloves and tall, curling violet boots. A long pale grey cape hangs behind him to the ground. "
        "He carries a very long, slender spear with a narrow blade. Noble, cold and composed, the very picture of "
        "a heroic knight."},
  {"Ps0013_020",  // Kumbhanda
        "A gaunt, skeletal ghoul with dark green-black flesh stretched over a ribbed, bony body, long spindly "
        "limbs and clawed hands and feet. Its head is a long, grey, horse-like skull face with a fixed grin of "
        "big flat teeth and glowing yellow eyes, framed by long, lank dark red hair. On top sits a wide, flat red "
        "hat marked with a black bat emblem, its brim hung all round with chains ending in barbed hooks. A dark "
        "red cloak is tied at its throat, and it carries a curved, rusty blade. Lurking, hungry and grotesque, a "
        "demon of graveyards and bad dreams."},
  {"Ps0013_030",  // Kushi Mitama
        "A big, glossy, olive-green comma-shaped spirit, like a fat raindrop or a curled jewel bead, its rounded "
        "body sweeping into a long, pointed tail curling off to one side. On the round part is a sly face: one "
        "eye shut in a squinting wink, the other wide open and white under a raised black brow, a little rounded "
        "nose and a crooked smirk showing a sliver of white teeth. There is nothing else to it: no limbs, no "
        "clothes. A cheeky, knowing little soul fragment that clearly thinks it's in on the joke."},
  {"Ps0013_040",  // Kurama Tengu
        "A powerful mountain goblin of Japanese legend, dressed as a mountain hermit, with vivid blue skin and a "
        "lean, muscular build. His long blue hair is swept back into a sharp crest, a small black cap is strapped "
        "to his forehead with a dark headband, green lightning-like marks run down his face, and his eyes glint "
        "red. He wears white monk's robes with a gold brocade stole hung with four big round white tassels ringed "
        "in black, black-and-white striped baggy trousers, white leggings and wooden sandals. Large grey-white "
        "wings, edged in deep blue, rise behind him. He carries a speckled conch shell on a green cord. Stern, "
        "aloof and proud."},
  {"Ps0013_050",  // Gurulu
        "A tall, gaunt bird demon with a dark, inky purple-black body, overlaid with a pale grey bony skeleton on "
        "the outside: a ribcage, spine, shoulder and hip bones clamped over its limbs like armour. Its head is a "
        "bird's skull with a long, hooked beak, a sharp horn jutting back, a single red jewel on the brow and "
        "gold rings hanging at its neck. Two huge wings of ragged black-violet feathers span far to either side, "
        "and its feet are bony talons. It carries a long, segmented staff hung with gold rings. A creature of "
        "death and ill omen, stark, cold and ominous."},
  {"Ps0013_060",  // Clotho
        "A slender, poised woman, one of the Greek fates, with porcelain-pale skin, amber eyes and red lips. Her "
        "golden-blond hair is shaped into a full, rounded bob with a thick braid circling her head, and two "
        "bright green coils of thread are wound into the hair either side of her face. She wears a high-necked, "
        "close-fitting white suit with fine pinstripes, black gloves, and from her waist hangs a tall, heavy "
        "cylinder of a skirt woven in a dark grey lattice, open at the front over her bare legs. In one hand she "
        "holds a black-and-gold handle trailing a single fine thread. Cool, precise and quietly ominous."},
  {"Ps0014_000",  // Quetzalcoatl
        "An immense winged serpent of Aztec legend, impossibly long and thin, its whole body covered in pale "
        "sea-green scales. Behind its head bursts a great upright fan of frosty, pale blue feathers, and two "
        "vast, slender wings of white and lavender-grey feathers spread wide on either side. Its head is a "
        "snake's, with glowing red eyes and wide-open jaws showing a pink mouth and sharp fangs, and its body "
        "stretches on and on behind it into a fine, tapering tail. Majestic, airy and divine, a feathered god of "
        "the sky and wind."},
  {"Ps0014_010",  // Genbu
        "A giant tortoise, one of the four Chinese guardian beasts, with a broad, domed shell of deep teal-black "
        "plates outlined in glowing magenta-pink lines. Beneath it are thick, tan, scaly legs with sharp claws, "
        "and a long-necked tan head with green eyes, a curved beak, small fangs and a dark, bristly beard hanging "
        "below its chin. From its rear stretches an enormously long serpent, scaled in red-orange with a row of "
        "dark spikes along its back, ending in a fierce, maned, red-orange snake's head facing backwards. Steady, "
        "ancient and unbreakable, a fortress that keeps a snake on guard behind it."},
  {"Ps0015_000",  // Koumokuten
        "A burly guardian king of Buddhist temples with dark blue skin, a deeply scowling face, sharp white eyes "
        "and heavy brows. His black hair is pulled into a high topknot, held by a flame-shaped red and gold crown "
        "ornament. He wears armour of maroon plates over orange robes: a sculpted breastplate, shoulder guards "
        "shaped like beasts' heads, a long maroon armoured skirt, a white sash knotted at his waist, white "
        "sleeves, orange trousers bound with dark straps and black shoes. In one hand he holds a writing brush, "
        "in the other a green scroll. Grim, watchful and severe, he notes down everyone's misdeeds."},
  {"Ps0015_010",  // Kohryu
        "A magnificent golden dragon of Chinese legend, with a long, sinuous, scaled body stretching far behind "
        "it to a pointed tail, a row of small spines along its back. Its head bristles with a spiky mane of "
        "golden whiskers, wide, glaring red eyes and a snarling mouth of fine teeth, and above it rises a "
        "towering crown of antlers: branching golden horns around a tall, V-shaped crest. Each of its four clawed "
        "feet grips a large glossy orb, one red, one blue, one smoky black and one pale lavender. Radiant, "
        "imperial and overwhelming, the emperor of all dragons."},
  {"Ps0021_000",  // Saki Mitama
        "A floating spirit shaped like a fat golden comma or a magatama bead: a smooth, round egg of glossy "
        "yellow-gold whose top sweeps sideways into a long, curling, tapering tail, like a teardrop caught by the "
        "wind. On the round end sits a calm, gentle face moulded into the gold, with a small straight nose, thin "
        "arched black brows, eyes closed in contented upturned crescents and a soft, closed-lipped smile. No "
        "body, limbs or clothes, just that one bright, polished shape. It radiates serene, sunny happiness, a "
        "little drop of pure good fortune."},
  {"Ps0021_010",  // Succubus
        "A slender, alluring demon woman with shoulder-length wavy dark blonde hair, pointed elfin ears, pale "
        "skin, vivid blue eyes and dark painted lips. A black choker with a little red heart charm circles her "
        "throat. She wears a skin-tight, high-necked black leotard cut very high on the hips and open at the "
        "sides and back, long black opera gloves and black thigh-high boots, with a thin shackle chain at one "
        "ankle. Huge bat wings, dark crimson on the inside and navy black outside, rise far above her head, and a "
        "long, whip-thin black tail ends in an arrowhead spade. A seductive nightmare, playful and dangerous."},
  {"Ps0021_020",  // Satan
        "A colossal fallen-angel serpent: a long, thick, dark navy-blue tail, ridged and scaled, sweeps away "
        "behind, and from it rises a lean, muscular dark blue torso with a horned, fanged demon face, a single "
        "gold point gleaming in its brow. Around it fan rows of huge folded wings, deep blue outside and blood "
        "red within, stacked like the ribs of a palm, with pale, steely blades jutting between them and tall "
        "spikes standing up behind its armoured, segmented crest. Two enormously long, thin, jointed bone-grey "
        "spines stretch down from its sides. Vast, dark and apocalyptic, it looks like the end of the world "
        "arriving."},
  {"Ps0021_030",  // Sati
        "A slender, graceful goddess in black from head to toe. Her chin-length black bob is crowned by a black "
        "cap edged with a scalloped band of gold medallions and dangling drops, and a black veil hides her face "
        "below the eyes, which are a striking deep pink-red; thin gold chains loop from the veil. Her "
        "long-sleeved black gown wraps across the chest with a ribbed gold trim, a scalloped gold belt sits at "
        "her waist, and the skirt splits high at the front over bare pale legs and black harem trousers, ringed "
        "with gold bands down to her bare feet. Mysterious and composed, a veiled goddess wrapped in quiet fire."},
  {"Ps0021_040",  // ?
        "A tall, lean, muscular figure whose whole body is patterned like an anatomy chart: bright red muscle "
        "panels framed by pale bone-grey bands with crisp white outlines, over chest, arms and legs. The bald "
        "head is red at the crown, sweeping back into a tall curved crest, with a pale grey face, sharp blue eyes "
        "and an open red mouth. The hands are smooth red mitts with no fingers, the legs taper into pointed red "
        "feet, and a perfectly round black orb sits in the hollow of its belly like a hole into nothing. It looks "
        "like an ancient Roman god of time and harvest, stern, strange and slightly unsettling."},
  {"Ps0021_050",  // Samael
        "A huge, flat, crimson serpent built like a living spearhead: a long blade-thin body of rough red hide, "
        "striped with diagonal black bands and with a dark purple underside, tapering behind into a needle-sharp "
        "tail. Its broad, blunt head is cracked and craggy, with a short horn on top and a cluster of glossy blue "
        "eyes, one large in the centre and smaller ones around it, above a dark purple lower jaw. Long, thin, "
        "ribbed red struts spread from its shoulders like the bones of folded wings, each ending in a hooked "
        "claw. Sleek, alien and venomous, it looks like death gliding in."},
  {"Ps0021_060",  // Sarasvati
        "A graceful goddess of music and learning with warm brown skin, long black hair, blue eyes and "
        "gold-painted lips. On her head sits a tall golden crown set with blue gems, topped by a pointed golden "
        "urn and framed behind by a gleaming golden halo ring. She wears a high-necked emerald-green top with "
        "gold-and-black striped borders, white short sleeves and a white overskirt trimmed in gold stripes, a "
        "gold belt studded with sapphires, and full, pleated green harem trousers gathered at bare ankles. Beside "
        "her floats a long-necked wooden sitar, and pale ribbons of silk drift at her shoulders. Serene and "
        "refined, she looks like a song made visible."},
  {"Ps0021_070",  // Thunderbird
        "A great stylised bird carved as if from smooth dark slate, sleek and totem-like rather than feathered. "
        "Its narrow head is topped by a rounded, helmet-like crest and holds two round, glowing orange-red eyes, "
        "with jagged lightning-bolt grooves running down its face like war paint. Two massive wings arch up from "
        "its shoulders and sweep down to long, curved points, their undersides ribbed with grooved black bands "
        "and edged in steely blue. Two small taloned hands cradle a red core at its chest, and below, its body "
        "spreads into a wide forked tail. It looks like a storm spirit of Native American legend, poised to crack "
        "the sky."},
  {"Ps0021_080",  // Sandalphon
        "A tall, gleaming angel built like a golden statue: his skin is polished gold, his face calm and "
        "mask-like with bright blue eyes, under a silver helmet cut in a sharp, straight-fringed bob. A long, "
        "sleeveless emerald-green tabard bearing a big red cross hangs from his shoulders to his ankles, cinched "
        "with a knotted red sash whose long tails trail far behind. Silver and gold armour plates with round "
        "sun-wheel medallions sit at his shoulders, elbows and knees. From his back rises a golden horseshoe "
        "arch, and behind it spread vast wings of long, pale silver blades, layered like a feathered fan. Lofty "
        "and immaculate, a guardian of heaven."},
  {"Ps0021_090",  // Sandman
        "A lanky little imp whose head is a polished black and silver crescent moon: the thick curve of the moon "
        "forms his skull and chin, with pointed grey elf ears jutting from the sides, narrow, smug amber eyes, a "
        "black triangle of a nose and a thin, sly grin. His skinny body is clad in a snug dark red bodysuit with "
        "silver rings at the wrists and ankles, ending in curly-toed red slippers. In one hand he hauls a fat, "
        "lumpy burlap sack, stitched shut and banded in black, stuffed with the sand of sleep. Mischievous and a "
        "bit sneaky, the bringer of drowsy dreams."},
  {"Ps0022_000",  // Siegfried
        "A tall, lean young warrior with orange-red skin, long, shaggy greenish-blond hair and calm blue eyes. "
        "His crimson spiked helmet and sleeveless tunic are covered in silver-studded diamond plates, over a high "
        "collar of black chain mail. Two black straps with silver rings cross his chest, and white laced bands "
        "tie at his wrists and below his knees above black laced slippers. A round shield with a pink rim and an "
        "embossed silver face rides on his back, a dagger in an orange sheath hangs at his belt and he carries a "
        "long blue-steel broadsword. Every inch the dragon-slaying hero of German legend."},
  {"Ps0022_010",  // Shiisaa
        "A stocky guardian lion-dog of Okinawa, about the size of a pony, with a bright yellow body and stout "
        "legs ending in big paws with white claws. Its huge round head grins wide, baring rows of square white "
        "teeth, with round staring eyes ringed in red, bushy curled brows and pointed yellow ears. A thick "
        "teal-green mane and beard, carved into tight curls and fading to dark red at the tips, frames its face "
        "and rises to a tall pointed spike on its head, and more teal curls sprout at its elbows, hocks and its "
        "big swirling tail. Fierce-looking but a bit comical, a loyal rooftop protector."},
  {"Ps0022_020",  // Shiva
        "A lean, muscular god with deep blue skin, four arms and long black hair, gathered in a topknot with a "
        "gold finial and a silver crescent moon. His forehead bears three pale stripes with a vertical third eye "
        "between them and gold rings hang from his ears. Dark prayer beads hang on his bare chest and a scaly "
        "teal serpent coils around his shoulders and waist. He wears a leopard-skin loincloth with fur trim and a "
        "long crimson sash, and carries a tall golden trident, a conch shell and a small hand drum. Calm, "
        "beautiful and terrible: the Hindu destroyer god."},
  {"Ps0022_030",  // Shiki-Ouji
        "A spindly paper-doll warrior, all flat, sharp-cornered planes as if folded and cut from card. Its front "
        "is split straight down the middle, one half white, the other black, and its back is blood red and black, "
        "painted with a column of black kanji. A great black and white crescent rises like horns above a small "
        "skull-like face with dark eye holes and a fringe of jagged, tooth-like strips for a jaw. Angular "
        "shoulder plates, banded white forearms, a short pleated skirt of layered paper strips and long claw-like "
        "fingers finish it. Eerie and weightless, a summoned paper spirit of Japanese sorcery."},
  {"Ps0022_040",  // Jikokuten
        "A broad, imposing general in Chinese armour, one of the four Heavenly Kings. His face is a golden mask "
        "of a scowl, with heavy black brows and a thick curled black moustache, under a dark green helmet with "
        "gold bands, a gold flower boss and a red plume on top, and silver winged guards over his ears. His "
        "armour is dark green lamellar scales trimmed in gold, with snarling lion heads on the shoulders, a white "
        "sash knotted at the waist and teal under-robes, over white sleeves, gold gauntlets and green greaves "
        "with red straps. Stern, proud and unbudging, a temple guardian."},
  {"Ps0022_050",  // Black Frost
        "A round little snowman-like imp, but jet black: a big round head on a pudgy little body. His floppy "
        "jester's hood is deep purple, with two pointed cat-ear peaks, a long zigzag tail flopping behind and a "
        "yellow crescent emblem on the front. His face has slanted, angry red eyes and a huge grinning red mouth "
        "with two white fangs. A purple collar of jagged points sits at his neck, his arms are ragged black "
        "stumps, and a little forked tail pokes out. He stands in purple boots with yellow cuffs and curling "
        "pointed toes. Cute, but grumpy and up to no good: a cheerful snow sprite's evil twin."},
  {"Ps0022_060",  // Jatayu
        "A great crimson vulture king with huge, wide-spread wings of dusky rose-red feathers and a thick ruff of "
        "grey-white plumes around his long neck. His hooked beak is tan, his eye a bright blue, and on his head "
        "sits a dark bronze helmet with a pointed domed top and two curved horns. From his head hang heavy golden "
        "pendants with pale gemstones, each ending in a ribbed crimson tassel. His body is lean and red, his legs "
        "end in scaly tan shins and sharp talons, and an extremely long, thin, segmented tan tail trails far "
        "behind. Noble and battle-hardened, the loyal bird hero of Indian epic."},
  {"Ps0022_070",  // Jack Frost
        "A small, round snow sprite, about knee high, with snowy white skin, a big round head and a pudgy belly. "
        "He wears a floppy royal-blue jester's hood with two pointed cat-ear peaks, a long zigzag tail flopping "
        "behind and a yellow oval emblem on the front. His face is all happy cartoon: big black oval eyes and a "
        "huge open grin with two little white fangs. A spiky blue collar rings his neck, his white arms end in "
        "soft mitten hands, a tiny pointed tail pokes out behind, and he stands in chunky blue boots with yellow "
        "cuffs. Irrepressibly cheerful, the cutest little frost imp around."},
  {"Ps0022_080",  // Jack-o'-Lantern
        "A cheeky pumpkin-headed spook: a round orange pumpkin head with a carved face, two sharp glowing "
        "red-white eyes, a little triangle nose and a jagged, toothy grin. A floppy teal witch's hat with a white "
        "band and a long bent tip crowns him. Instead of a body there is just a billowing dark blue cloak, tied "
        "at the neck with a cord ending in two white pom-poms, flapping open over empty space. One white-gloved "
        "hand pokes out to hold an old iron lantern with a glowing yellow glass. Mischievous and impish, a "
        "Halloween trickster out for a night of pranks."},
  {"Ps0022_090",  // Chi You
        "A towering, six-armed war god with bright green skin, a bull's long black horns and a fanged, beastly "
        "snout with small blue eyes. A white helmet with a pink ridged crest and orange trim sits between the "
        "horns. A scalloped white and pink mantle spreads over his shoulders, and a long red quilted tabard bears "
        "a big yellow disc printed with a black Chinese character. His many hands carry a long spear, a "
        "red-tasselled halberd, a golden axe and a great gold gong trailing yellow ribbons, and on his back hangs "
        "a round shield painted with a snarling blue and pink face. Brutish and unstoppable, an ancient Chinese "
        "warlord."},
  {"Ps0022_100",  // Silky
        "A slender woman with pale mint-green skin, amber eyes and long, flowing green hair that drifts out "
        "behind her and ends in wavy, tendril-like strands like waterweed. A neat white kerchief covers her head "
        "and falls to her shoulders. She wears a long, full, off-the-shoulder gown of burnt orange, its fitted "
        "bodice laced down the front with curling black ironwork-like scrolls, its long sleeves trimmed with the "
        "same at the cuffs, and its wide skirt edged in dark grey trim. Quiet and gentle, she looks like the "
        "ghost of a faithful old house servant from Scottish folklore."},
  {"Ps0023_000",  // Scathach
        "A pale, mysterious warrior woman almost lost inside an enormous black cloak that spreads into a vast "
        "cone around her. She wears a tall, flat-crowned black hat with a very wide, sharply pointed brim, banded "
        "with leather and silver crosses. Beneath it her skin is ghostly white, her eyes closed and her lips "
        "pink, with a red rose painted on one cheek. Rings of green and teal stripes circle her neck over a black "
        "banded bustier, a silver Celtic cross hangs at her bare midriff, and she wears black briefs and long "
        "striped black gloves. Cool, enigmatic and deadly, a shadow-queen of Celtic myth."},
  {"Ps0023_010",  // Skadi
        "A tall, slender goddess with jet-black skin, glaring red eyes and red lips. Her silver-white hair sweeps "
        "straight up into two tall pointed plumes like horns. Huge golden, carved collar pieces stand up on her "
        "shoulders like crowns, and from them falls a vast cape, deep forest green on the inside and patterned "
        "outside in a bold gold and black chevron weave, spreading wide to the ground like a cloak of mountain "
        "bark. Under it her body is a sleek, featureless black silhouette. Cold, regal and austere, a winter "
        "huntress-goddess of the Norse north."},
  {"Ps0023_020",  // Suzaku
        "A glorious crimson phoenix with a long, slender neck and a fluffy pink breast. Its head wears a soft "
        "white crest and a spray of pink feathers, with a small golden beak and blue eyes. Its wings flare wide "
        "in deep scarlet, and behind them rises a huge fan of red tail feathers, each tipped with a gold and "
        "orange eye like a peacock's, among curling black thorny spikes. Five long streamers hang far below it, "
        "blue, white, black, red and gold, each ending in a feathered eye. Dazzling and fiery, the vermilion bird "
        "guarding the south."},
  {"Ps0023_030",  // ?
        "A tall, wiry god with dusky purple skin sitting cross-legged in the air, his face hidden behind a long, "
        "straight curtain of silver-white hair. On his head stands a towering silver crown of twisted, branching "
        "spikes, like dead branches or frozen lightning. A heavy necklace of curved golden fangs with a turquoise "
        "pendant hangs on his bare, muscular chest, and a long, stiff cape falls behind him, dark charcoal "
        "speckled with blood red and swirled with faint storm patterns, edged in grey beads. In one hand he holds "
        "a long, black, saw-toothed sword. Brooding and wild, the Shinto storm god in a moment of dangerous calm."},
  {"Ps0023_040",  // Slime
        "A lumpy mound of oozing green sludge, roughly as tall as a person's waist, slumping and dripping in "
        "thick ridges down to the floor. Its slick surface is mottled with blotches of sickly yellow, densest on "
        "its rounded top, and pitted with dark little holes. Two round, glossy red eyes bulge from deep sockets, "
        "and below them gapes a wide, droopy black mouth with a heavy hanging lower lip. No arms, legs or "
        "clothes, just quivering muck. Gross, gloomy and a bit pathetic, the lowliest of creatures."},
  {"Ps0023_050",  // Surt
        "A towering, gaunt giant with charcoal-grey skin wrapped in irregular dark red bands like smouldering "
        "stripes of fire across his whole body. His head is long and tall, rising into a flat-topped cylinder "
        "like a fez, with narrow glowing yellow eyes, a heavy scowl, a hooked nose and a small stub of a beard on "
        "his chin. His body is lean but powerfully muscled, with long arms and bare feet. In one hand he grips a "
        "very long, thin, dark red sword with an orange and black patterned hilt. Grim and smouldering, the fire "
        "giant of Norse myth who will set the world ablaze."},
  {"Ps0024_000",  // Qitian Dasheng
        "The monkey king of Chinese legend as a wiry old immortal sage, with a brown wrinkled ape face, pointed "
        "ears, a toothy grin, sharp blue eyes and a great white mane and beard. He wears a tall red scholar's hat "
        "banded in gold, a tasselled golden rod laid across its crown. He wears a sweeping crimson robe with "
        "enormous bell sleeves and orange-gold trim over a blue under-robe, cinched with a gold-buckled belt, He "
        "stands on a puffy white swirl of cloud, a long red staff capped in gold at both ends close by. Proud, "
        "mischievous and impossibly old, he looks like he still enjoys a good brawl."},
  {"Ps0024_010",  // Seiryu
        "A colossal Eastern dragon, the azure guardian of the east from Chinese lore, its body a tremendously "
        "long, thin serpent of dark navy-blue scales running far behind it, a row of yellow-green spines down its "
        "back and small clawed feet along its length. The head is all drama: a shaggy mane of dark green fur "
        "flaring like a lion's ruff, two branching tan antlers, long green whiskers trailing from the snout, "
        "blazing yellow-orange eyes under a scowling brow and a gaping red mouth of fangs. Its forelegs end in "
        "big hooked tan talons. It looks ancient, wise and furious, a storm of scales ready to coil around the "
        "sky."},
  {"Ps0024_020",  // Setanta
        "A young warrior hero of Irish legend, a boy with a neat black bowl cut and steady grey-blue eyes peeking "
        "over a long sky-blue tartan scarf, crossed with green and pink lines, wound up over his nose and hanging "
        "down his chest. He wears quilted white padded armour with puffed shoulders, a polished silver "
        "breastplate, a belt hung with two round carved wooden medallions and fringed tassels, blue tartan "
        "sleeves and short breeches, white quilted boots and a plain brown cape. He carries a long steel-tipped "
        "spear and a pair of slender wooden staves. Earnest, quiet and fearless, he looks like the hound of a "
        "hero in the making."},
  {"Ps0024_030",  // Seth
        "A huge, sleek black dragon, an Egyptian god of chaos and desert storms in monstrous form, its whole body "
        "dark charcoal with a faint purple sheen. Vast bat-like wings stretch far out to either side, their "
        "leading edges studded with small hooked claws. A long, narrow head bristles with a crown of backswept "
        "spikes, with small green eyes and a mouth lined with red. Its lean, muscular body stands on clawed hind "
        "legs, and a long whip of a tail trails behind it, ridged its whole length with jagged spines. It looks "
        "lithe, cruel and silent, a shadow of sandstorm and night given wings."},
  {"Ps0025_000",  // Zouchouten
        "A stern guardian king of Buddhist temples, a broad-shouldered warrior with green skin, a scowling, "
        "heavy-browed face with a thin drooping moustache and pale glaring eyes, his black hair tied up in a "
        "topknot under a small blue crown. He wears ornate armour in steel blue and charcoal: rounded black chest "
        "plates, blue shoulder guards moulded into snarling beast faces, gold-lined collar, layered black "
        "lamellar skirts, white sleeves and a thick white rope sash knotted at his waist, with blue leggings and "
        "black boots. Beside him stands a tall golden trident. He looks immovable and grim, a gatekeeper nothing "
        "slips past."},
  {"Ps0025_010",  // Throne
        "A silent, hooded figure set within a great wheel. A slender being with dark brown skin, a calm, "
        "mask-like face and faintly glowing red eyes peers out from a deep navy-blue hood, its long robe of "
        "glossy dark blue fabric falling in a layered cape over the shoulders and in wide sleeves to its bare "
        "feet. Around it stands a huge wheel of weathered grey stone, taller than a person, with six spokes "
        "meeting at a hub behind its back, and on the rim six round amber lamps glowing like eyes. It looks "
        "solemn and judging, an angel of the high ranks turned into the very wheel of fate."},
  {"Ps0031_000",  // Dakini
        "A slender, golden-skinned goddess of fierce Hindu lore, with dark hair in a bun, red-lidded eyes painted "
        "with blue stripes beneath and a red mark on her brow. Her crown is a golden fan of finned plates topped "
        "with a ring of small skulls and gilded finials, and great golden disc earrings hang beside her face. She "
        "wears a cropped green top with silvery wave patterns, a dusky pink wrap skirt, and strand upon strand of "
        "red beads at her throat, arms, wrists, ankles and hips. She holds a pair of curved silver swords. Lithe "
        "and lovely in a deadly way, her beauty comes with a blade and a grin."},
  {"Ps0031_010",  // ?
        "A seated skeletal monk, a mummified holy man of Japan who starved himself into a living Buddha, all bone "
        "and robes. A grinning bare skull peers out from under a tall, pointed golden-brown hat bound with a "
        "green band and two silver discs, long green streamers falling down beside the face. He sits cross-legged "
        "in a voluminous ochre-gold robe with great flaring sleeves, over a green under-robe crossed with a dark "
        "lattice pattern and edged in white. In his bony hands he holds a string of red prayer beads and a small "
        "golden ritual bell. Utterly calm and utterly dead, he radiates a creepy, unshakeable serenity."},
  {"Ps0031_020",  // Take-Mikazuchi
        "A proud young thunder god of Japanese myth, with reddish-brown skin and narrowed amber eyes, his black "
        "hair looped into two bunches at his ears in ancient style and tied with a blue headband. Teal "
        "comma-shaped jewels dangle from his ears and hang on a necklace of dark beads at his chest. He wears a "
        "plain white tunic fastened with small ties and full white trousers bound below the knee with blue cords, "
        "with blue shoes. At his waist hangs a gold and blue apron panel marked with two rings, and a long black "
        "scabbard; a gleaming golden sword lies close by. He looks cool, confident and quietly dangerous."},
  {"Ps0031_030",  // Take-Minakata
        "A beaten, bound war god of Japanese myth, a hulking figure with green skin, a craggy ogre's face, small "
        "tusks and one glowing red eye, two pale curved horns sweeping from his temples and black hair tied in "
        "loops at the sides. He has no arms: dark round guards cap his shoulders, and thick hemp rope lashes his "
        "chest in a tight crisscross harness. He wears a white tunic and trousers, a navy sash with a dark "
        "stripe, red cords below the knee, dark shin guards and bare green feet. Defeated but still glowering, he "
        "looks like a captive who has not stopped plotting his revenge."},
  {"Ps0031_040",  // Tam Lin
        "A handsome elfin knight of Scottish ballad, tall and slim, with long straight silver-white hair framing "
        "a pale, fine-boned face and cool blue eyes, a teal circlet set with a diamond-shaped gem on his brow and "
        "a small ring in one pointed ear. He wears sleek teal plate armour edged in silver piping, with a high "
        "stand-up collar, flared shoulder guards and tall teal and black boots, over a black mail skirt, with "
        "black clawed gauntlets. A long white cloak with a grey lining hangs to his heels, and he carries a thin "
        "black spear. Elegant, melancholy and a little enchanted, he looks like a prince stolen away by fairies."},
  {"Ps0032_000",  // Chernobog
        "A tall, gaunt black god of darkness from Slavic myth, its body a single long column of glossy black robe "
        "flaring to the ground, with a red sunburst emblem glowing on the chest. Its face is a pale blue skull "
        "grinning under an enormous flat, round purple hat like a mushroom cap, its underside ribbed with gills. "
        "One hand grips a long, straight silver sword with a jewelled crossguard. Around the hem of its robe "
        "sprout slender teal stalks topped with little purple caps, a sinister garden of fungus. It looks "
        "patient, chilling and funereal, a lord of the night waiting for everything to rot."},
  {"Ps0034_000",  // Dionysus
        "A lithe, flamboyant god of wine and revelry from Greek myth, covered from head to toe in a psychedelic "
        "pattern of swirling waves in green, blue, yellow, orange and teal that runs right over his face like a "
        "painted mask. A shock of spiky silver-white hair crowns his head over long, wavy brown locks. A long "
        "crimson cloth drapes over one shoulder and spills far below his feet, and he wears white gloves and "
        "white boots. Slung on a cord he carries a twisted wooden staff topped with a silver pine cone. Wild, "
        "sensual and gleefully unhinged, he looks like a party that never ends."},
  {"Ps0034_010",  // Titania
        "A graceful fairy queen of English folklore, a slender woman with long, wavy golden hair falling to her "
        "waist, a pink lily tucked behind one pointed ear, teal eyes and soft pink lips. A green choker circles "
        "her throat. Her gown is a flowing forest-green dress with a scoop neckline, a pointed shoulder capelet "
        "and long sleeves, the full skirt patterned with golden zigzag flames and runes, and she goes barefoot "
        "with a thin anklet. From her back rise four tall, translucent wings of pale lilac and blue, veined like "
        "a dragonfly's. Regal, lovely and a little aloof, she looks every bit the queen of a moonlit forest "
        "court."},
  {"Ps0034_020",  // Decarabia
        "A five-pointed star with a single great eye in its middle, a demon of old grimoires that hides in the "
        "shape of a star. Its front is a mottled rusty orange-red, smooth and slightly rounded, and its back is "
        "cold, blue-grey marbled stone with ridges running down each point. At the centre stares a large violet "
        "eye with a white gleam, ringed in black and fringed with short black tendril-like lashes ending in "
        "little dots. It is about the size of a person and almost flat. Odd, unblinking and creepily watchful, it "
        "looks like a starfish that has learned to cast spells."},
  {"Ps0035_000",  // Thoth
        "An Egyptian baboon god of wisdom, perched on a giant closed book. He has a black, long-muzzled face with "
        "yellow eyes and bared teeth, framed by a huge thick ruff of white fur that rises around his head like a "
        "hood, and on his crown sits a golden disc resting in a golden crescent moon. Across his shoulders lies a "
        "broad Egyptian collar of teal and green with black panels dotted in gold diamonds. His body is lean and "
        "white-furred with black hands and a long thin tail. The book's tan cover bears hieroglyphs and a painted "
        "eye. He looks scholarly, smug and patient, a judge who has read everything."},
  {"Ps0035_010",  // Thor
        "A towering, muscular thunder god of Norse myth, with deep brown skin, black knotwork tattoos banding his "
        "upper arms and thighs, and long black hair falling over his chest. His head is hidden in a gold helmet "
        "with a row of spikes along its crest and a closed faceplate, two glowing blue eye slits staring out. A "
        "gold breastplate of overlapping scales covers his torso above white briefs, and thick white banded cuffs "
        "wrap his forearms and shins. A white cloak and cowl drape his shoulders over a black lining. He wields a "
        "heavy, blocky grey hammer. He looks like pure power and swagger, a storm walking on two legs."},
  {"Ps0035_020",  // Dominion
        "A noble angel, pale, slender figure with long, wild dark blue hair and piercing green eyes. A long band "
        "of white parchment, marked with dark dots and dashes, curls behind his head and streams out to one side. "
        "Two broad wings of grey-brown feathers rise from his back. He wears a flowing white robe with a fine "
        "patterned hem, a red-jewelled silver belt, a brown sash and shoulder cape trimmed with gold key "
        "patterns, and a long crimson and brown cloak. In one hand he holds black balance scales, in the other a "
        "blue leather book. He looks serene, exacting and impartial, an angel of order."},
  {"Ps0035_030",  // Trumpeter
        "A skeletal angel of the end of days, floating in long, rippling pale grey robes with no feet below. Its "
        "face is a grinning bone-white skull, framed by stiff golden curls rolled at each side like a judge's "
        "wig, under a tall black and gold checkered cap. A black stole runs down its chest, patterned with white "
        "clover marks and pointed triangles, and a long black bar rests across its shoulders. Great layered grey "
        "wings sweep down behind it. It carries a golden trumpet, topped by a small red bird ornament with one "
        "blue eye. Solemn and dreadful, it looks ready to sound the last call."},
  {"Ps0041_000",  // Naga
        "A serpent spirit of Hindu myth, a man above the waist and a snake below, with smooth pale blue-grey "
        "skin. His long black hair is tied in a topknot and falls in two long tails, beneath a silver scrolled "
        "tiara set with a small green gem. A bright yellow sash crosses his chest. His long scaly tail is pale "
        "blue in front and streaked with magenta along its back, a small bell tied to its tip with yellow ribbon. "
        "He carries a slim silver spear and a round steel shield bearing a coiled serpent emblem. Calm and "
        "watchful, he looks like a guardian of a hidden river temple."},
  {"Ps0041_010",  // Naga Raja
        "A king of the serpent people of Hindu myth, a man's torso rising from an immensely long snake's body, "
        "tan scales banded with dark red, stretching on and on behind him. His head is crowned by a great fan of "
        "golden spines like a cobra's hood, shading a cold, narrow face. A black spiked emblem marks his tan "
        "chest below a necklace of orange teeth, and his arms are clad in gold scales ending in golden claws. A "
        "sheer white stole loops around his shoulders and streams away. He wields a golden spear trailing a red "
        "tassel. He looks regal, cold and coiled to strike."},
  {"Ps0041_020",  // Narcissus
        "A beautiful youth of Greek myth who loved his own face and became a flower, which grows right out of "
        "him: a cluster of white, bell-shaped daffodils on green stems sprouts from the crown of his head. He is "
        "slim and pale-skinned, with long, wavy golden hair spilling to his waist and falling over one blue eye. "
        "He wears nothing but a sash of deep crimson silk wrapped low around his hips, its long end floating out "
        "behind him. He stands in a tuft of bright green grass and more white daffodils. Dreamy, delicate and "
        "completely self-absorbed, he looks lost in his own reflection."},
  {"Ps0042_000",  // Nidhoggr
        "A monstrous serpent-worm of Norse myth, the dragon that gnaws at the roots of the world tree, its body "
        "an immensely long, smooth tube of pale teal hide veined with jagged violet lines, tapering to a "
        "needle-thin tail. It has no eyes at all: the front end is just a huge round gaping mouth crammed with "
        "big, blunt, eerily human-looking teeth around a pink tongue. Two short, stubby limbs with flat, "
        "finger-like flippers stick out near the head, a row of pale knobs runs along each flank and its "
        "underside is a dark ribbed red. Grotesque and hungry, it looks like an endless mouth that will chew "
        "through anything."},
  {"Ps0042_010",  // Nigi Mitama
        "A smiling droplet of a gentle spirit from Shinto belief, the soul's peaceful side, shaped like a big, "
        "plump teardrop or comma-shaped jewel in smooth, glossy teal, its pointed tip curling up and over to one "
        "side like a curl of water. On its rounded front is a soft, simple face: happy closed eyes curved like "
        "crescents, a small rounded nose and a wide, contented smile showing a sliver of white teeth. It is about "
        "the size of a person's torso and has no limbs at all. Placid, cheerful and soothing, it looks like a "
        "little blob of pure good mood."},
  {"Ps0044_000",  // Neko Shogun
        "A pint-sized black cat warlord, a feline samurai general from Japanese legend, with big yellow-green "
        "eyes, a stubby snout and pink-lined pointed ears poking out from a black and gold helmet with a crescent "
        "moon crest and a flaming red plume. From his back rise two tall red war banners on gold-trimmed poles, "
        "one printed with a black paw print and one with a black cat's face. He wears pale teal lacquered armour "
        "edged with frilly white trim and gold, a small cat-face badge on the chest and a red cloth apron at the "
        "front, and carries a long black staff. He looks pompous, bossy and utterly adorable."},
  {"Ps0044_010",  // Nekomata
        "A slim, sly cat woman, a two-tailed demon cat of Japanese folklore given a human shape, with long, sleek "
        "brown hair, pointed black cat ears, slitted golden eyes and pale skin. A black mask covers her nose and "
        "mouth, striped with white whisker marks and showing two small fangs. She wears a skin-tight black "
        "bodysuit ribbed across the chest, hugging her lean, long-legged figure, under a cropped, shaggy jacket "
        "of white fur with dark cuffs, and her fingers end in black claws. A long, thin grey tail hangs behind "
        "her. Graceful, teasing and dangerous, she looks like a cat burglar who would happily scratch."},
  {"Ps0044_020",  // Nebiros
        "A gaunt necromancer, a demon general of the grimoires who commands the dead, wrapped in a voluminous red "
        "hooded cloak that falls in a great diamond around a tall, thin body. His face is painted as a skull, "
        "white with purple shading, sunken red-rimmed eyes, and a gold chain earring hangs from one pointed ear. "
        "Beneath the cloak his purple skin is patterned in green, with red shorts, purple and white striped "
        "stockings. Beside him dangles a puppet skeleton of dark rods ringed in pale green and yellow, its head a "
        "cat-eared mask with green eyes and a red mouth. He looks theatrical, morbid and delighted with his toys."},
  {"Ps0045_000",  // Norn
        "A great golden wreath floating in the air: a thick ring of swirling, rippling gold like molten cloud, "
        "framing a perfectly round hole of pure black at its heart. Three winged women are sculpted into the ring "
        "as if grown from it, all in the same burnished gold. One sits on top, long hair streaming and a single "
        "great wing sweeping out behind her, while her two sisters cling to the sides, half sunk into the gold. "
        "Loose ribbons of gold curl and trail all around the rim. It looks like a holy relic, the three sisters "
        "of Norse fate keeping their watch over an empty void, serene and unknowable."},
  {"Ps0051_000",  // Baal Zebul
        "A hulking, pot-bellied ogre with smooth blue skin veined with purple, red eyes, pointed ears and a "
        "fanged mouth gaping in a roar. A wild mane of black hair spills down his back under a tiger-striped "
        "headband, curved fang earrings hang from his ears, and a necklace of small skulls and fangs rings his "
        "thick neck. A tiger pelt is slung over one shoulder and wrapped around his huge gut, the beast's "
        "snarling, blue-eyed head riding on his shoulder, and tiger-striped cuffs bind his wrists and ankles. He "
        "carries a long black staff and a pale skull pierced with spikes. Brutish and greedy, a wild man who "
        "devours everything."},
  {"Ps0051_010",  // Parvati
        "A graceful Hindu goddess with pale skin, magenta eyes, painted pink lips, rose-pink hair in two round "
        "buns like flower buds, with a long tail down her back. A gold tiara set with a blue jewel crowns a small "
        "white cap, and a lavender veil sprinkled with gold falls from it over her shoulders. She wears gold "
        "earrings, a broad gold collar, a fitted pink top with gold-trimmed sleeves and a pink and gold sash, "
        "loose saffron trousers, and a long pink overskirt open at the front, dotted with tiny gold diamonds and "
        "hemmed in black and gold. She holds a little pink lotus. Serene, gentle and quietly regal."},
  {"Ps0051_020",  // High Pixie
        "A slender grown-up fairy, taller and sharper than her little sisters, with a spiky crest of icy blue "
        "hair standing straight up, pale blue eyes, plum lips, pointed elfin ears and silver ring earrings. Her "
        "outfit is half armour: a polished grey steel breastplate riveted over a purple bodysuit, a steel collar "
        "at her throat, long purple gloves to the upper arm, dark charcoal leggings and chunky purple boots. From "
        "her back rise four tall, pointed insect wings, translucent and shimmering in turquoise, sea green and "
        "streaks of blue. She has the cool, haughty poise of a fairy queen's captain: pretty, but not to be "
        "trifled with."},
  {"Ps0051_030",  // Pazuzu
        "A winged Mesopotamian wind demon with a tall, lean, tan-furred body and the head of a snarling lion: "
        "blue eyes, pink-lined ears, bared teeth, and a shaggy mane and beard of silvery white. A crest of curved "
        "cream-and-gold plates fans over his skull like a helmet's comb, topped by a pale spike. A jagged stripe "
        "of rust-red feathers runs down his chest to his loins. Four great wings of tawny brown feathers spread "
        "from his back, two reaching high and two sweeping low, and his hands and bird-like feet end in dark "
        "hooked claws. Gaunt and ancient, he looks like a plague riding in on the desert wind."},
  {"Ps0051_040",  // Hanuman
        "A wiry monkey king of Hindu legend, with tawny fur, a long white beard and whiskers, fierce green eyes "
        "and an open, fanged mouth mid-roar. He wears a tall golden helmet shaped like a temple spire, a red "
        "jewel on its brow and pointed flaps flaring at the sides, and a broad golden collar of pointed wings "
        "studded with teal gems. Gold bands circle his arms, wrists and ankles. Below a red sash and gold "
        "medallion belt hangs a green apron worked with a golden swirl, flanked by long white streamers. He holds "
        "a gleaming scimitar, and a long tail hangs behind him. Old, proud and spoiling for a fight."},
  {"Ps0051_050",  // Baphomet
        "A sinister goat-headed idol with sooty black fur and skin, glowing red eyes in a long goat's face, and "
        "two pairs of great ridged horns curling back and out from its brow around a small pointed crest. A long, "
        "lank mane of black hair falls over its chest, partly hiding a woman's breasts capped in glossy black. At "
        "its belly sits a golden staff wound with twin serpents around a green orb. A white cloth wraps its hips, "
        "its shaggy legs are a goat's, ending in hooves, and two vast wings of dark brown-black feathers spread "
        "behind it. Half beast, half woman, wholly occult: a black-mass altar come to life."},
  {"Ps0051_060",  // Hariti
        "A tall, ghostly woman wrapped in a long hooded robe of dusky rose-red, the hood rising to two small "
        "pointed peaks above her head. Her face is pale as porcelain, with blood-red eyes and red lips framed by "
        "dark hair. The robe clings to her slim figure before falling into enormous trailing sleeves and a ragged "
        "hem that drifts past her bare feet, slit at the front. With her goes a swaddled bundle of gold brocade, "
        "a baby wrapped tight in a hood and tied with a purple cord whose ends trail far below. A child-snatching "
        "demon turned protector of children, she looks both motherly and deeply unsettling."},
  {"Ps0051_070",  // Barong
        "A shaggy lion-beast of Balinese temple dance, long and low like a huge dog draped in a curtain of coarse "
        "cream-white hair that falls to the ground on every side, sturdy blue legs and paws peeking out beneath. "
        "Its face is a carved blue mask with bulging orange eyes, a black nose, square white teeth and pink ears, "
        "framed in an ornate silver headdress studded with blue gems, with a long beard of dark green strands and "
        "fringes of deep blue. Silver spikes crown its head, and its tail rises straight up as a tall silver pole "
        "topped with a spray of navy ribbons. Gaudy and kindly, a festival guardian."},
  {"Ps0051_080",  // Power
        "An armoured angelic warrior with dusky violet skin, a shadowed face and piercing green eyes under a "
        "blood-red helmet that flares into two curling horns around a central spike. His red armour has a high "
        "ribbed collar, broad shoulder plates with gold rosettes, a moulded chest and plated gauntlets and shin "
        "guards, belted in brown leather over a red-and-black checked skirt and a long, pale grey-green tabard "
        "falling to his ankles. Two huge wings of dark slate-black feathers rise behind him. He carries a long "
        "red spear with a steel point and a kite shield of red edged in gold, emblazoned with a black octopus. A "
        "grim soldier of heaven."},
  {"Ps0052_000",  // Pixie
        "A tiny fairy with a bob of short auburn hair curling at her cheeks, big rose-pink eyes, a sweet little "
        "smile and pointed elfin ears. She wears a sleek high-necked royal blue leotard, long blue gloves and "
        "thigh-high blue boots, each topped with a black crisscross lacing band, with matching lacing on a black "
        "choker. Two pairs of wings sprout from her back, gauzy sky-blue and teal, marbled like water and curling "
        "at the tips into pale green tendrils. She looks bright, cheeky and eager, the plucky little sidekick "
        "fluttering at your shoulder."},
  {"Ps0052_010",  // Pisaca
        "A gaunt, ghoulish figure with a starved, skeletal woman's frame and leathery rust-brown skin crossed "
        "with dark crack-like lines like dried bark. Its head is a nightmare: a smooth bulb from which a long, "
        "thin stalk juts out to each side, each tipped with a single yellow eye. Where the face and chest should "
        "be, a huge mouth splits the body open from throat to belly, lined in dark purple and studded along both "
        "edges with rows of curved ivory fangs. Its long arms end in spidery fingers with dark claws. Hollow and "
        "ravenous, a corpse-eating ghoul of Indian legend that seems to be nothing but hunger."},
  {"Ps0052_020",  // Bishamonten
        "A stern Buddhist guardian god, broad and solid, with deep red skin, a furious scowl, heavy brows, gold "
        "eyes and a thick black moustache curling at the tips. His black hair is pulled into a topknot capped "
        "with a small gold crest. He wears ornate olive-gold armour: a high flared collar, a breastplate with "
        "round studs, shoulder guards shaped like snarling lion heads, a scaled skirt and plated shin guards, "
        "with white sleeves and a white sash knotted at his waist. In one hand he holds a small golden pagoda, in "
        "the other a short golden club. Unbending and thunderous, a divine general who guards the north."},
  {"Ps0052_030",  // Byakko
        "A colossal white tiger, the guardian beast of the west in Chinese myth, its snowy fur striped in crisp "
        "black. Piercing ice-blue eyes glare from a broad face framed by a great ruff of white fur that sweeps "
        "back like flames from its cheeks and chest, and more flame-like tufts flare around its legs above heavy "
        "paws. Its mouth is open in a snarl, showing long fangs. A very long, thin striped tail stretches far "
        "behind it to a pointed tip. Powerful, regal and coldly furious, it prowls like winter itself."},
  {"Ps0053_000",  // Fortuna
        "A Roman goddess of luck with long wavy hair of deep royal blue, amber eyes and a knowing half-smile, a "
        "small white hood perched on the back of her head. A white high-necked halter top hugs her bust and "
        "leaves her shoulders and arms bare, and a silver spoked wheel, like a chariot's, is set right into her "
        "midriff. A short wrapped brown skirt, lined in dark red, sits at her hips over long bare legs. Two long "
        "scarves loop around her in great arcs, one twisted brown and one gauzy white, like a wheel forever "
        "turning. Capricious, she could smile on you or spin you down."},
  {"Ps0053_010",  // Forneus
        "A huge flat fish-demon, part manta ray and part shark, its body spreading into vast wide fins that sweep "
        "out far to either side, with a tall shark's dorsal fin and a long, whip-thin tail behind. Its hide is "
        "charcoal grey dappled with darker blue-black spots, with gill slits along the underside. A squat head "
        "rises from its back: a stony grey face with narrow teal eyes, curved black horns and a silver crown set "
        "with green gems. Below it, at the front edge of the body, two small purple eyes sit above a wide mouth "
        "of jagged teeth. A brooding king of the deep, gliding low and sly."},
  {"Ps0053_020",  // Futsunushi
        "A lean, battle-hardened Japanese sword god with grey-green skin, glaring magenta eyes and a deep frown. "
        "Long straight hair of dark violet falls past his shoulders from under a white headband marked with a "
        "black-and-white yin-yang emblem, and a leather cord at his throat holds a curved purple jewel. Grey "
        "bandages wrap his arms, chest, waist and thighs, like a monk who trains until he bleeds, and the rest of "
        "him is bare and sinewy. Beside him stands a towering rack of swords, dozens of slim verdigris-green "
        "blades side by side like a fence. Austere and unshakeable, a swordsman's spirit who has given everything "
        "to the blade."},
  {"Ps0053_030",  // Flauros
        "A demon leopard in the shape of a tall, lean man, its scarlet leopard's head set low on its chest, with "
        "ice-blue eyes, white jowls and fangs flanked by two gold tusks. Its body is red fur with black rosettes "
        "and a white belly. It wears a high-shouldered black leather jacket studded with small gold spikes, the "
        "collar rising behind it in two tall black columns, with gold-and-black striped bands at the shoulders. "
        "Between the columns rises a black-and-gold pillar topped by a tiny grinning blue demon face in a gold "
        "crest. Black gauntlets end in long golden claws. Flashy, menacing and feral."},
  {"Ps0053_040",  // Principality
        "A noble angel in the look of a crusader prince, with pale skin, a calm, faintly sad face and golden "
        "eyes. A silver helmet sprouts a crown of long, sharp silver spikes like rays of light, ringed in gold, "
        "and a hood of chainmail falls to his shoulders under a short teal capelet. Over chainmail sleeves he "
        "wears a royal blue tunic and a green surcoat hung with gold medallions, over a long pale robe hemmed in "
        "yellow, with a sword at his hip. Two great wings of olive and green feathers rise behind him, and he "
        "holds a long staff crowned with a golden cross. Dignified and devout."},
  {"Ps0054_000",  // Pale Rider
        "A hooded skeleton on a pale horse, the fourth horseman of the apocalypse. The rider's face is a bare, "
        "yellowed skull deep in a black hood, his black robe flowing into enormous ragged sleeves and a tattered "
        "hem that hangs over the horse's flanks, with bony gauntleted hands poking out. He carries a long scythe "
        "on a brown wooden shaft, its thin black blade sweeping in a cruel curve. His steed is ghostly "
        "grey-white, with pale blue eyes, a long, wispy mane falling over its face and a ragged, smoky tail, "
        "harnessed in black straps. Silent and inevitable, death itself come riding."},
  {"Ps0054_010",  // Hecatoncheires
        "A hulking giant of Greek myth with smooth, mottled teal skin and the muscles of a statue, sprouting a "
        "whole crown of arms: ten of them, fanning out from its shoulders and back in every direction. Its head "
        "is a lumpy dome scattered with round, glassy blue eyes, and three gaping mouths full of big human teeth "
        "open on its face and sides. The main mouth is gagged: a gold chain runs straight through it and a heavy "
        "brass padlock is jammed between its teeth. Chained, many-handed and howling, it looks like a prisoner of "
        "the gods that never stopped struggling."},
  {"Ps0054_020",  // Berith
        "An armoured knight on a blood-red warhorse. The rider is encased head to toe in dark, slate-teal plate "
        "armour: a visored helmet topped with a spike and flared crests, golden eyes glinting through the slit, "
        "ridged shoulder plates, round elbow guards, flanged gauntlets and a layered plate skirt. He carries a "
        "long golden lance with a barbed point. His horse is muscular and deep red, with a thick black mane, a "
        "long black tail, gold hooves, a dark leather saddle and silver stirrups. Grim and martial, a demon duke "
        "of war riding out at the head of hell's cavalry."},
  {"Ps0054_030",  // Hell Biker
        "A grinning skull in black leather astride a chopper. Its head is a bare, bone-white skull with fiery "
        "orange eyes, and a long red scarf at its throat streams out behind it like a flag. A black leather biker "
        "jacket with a wide collar and silver piping, black gloves, black trousers and knee-high black boots "
        "complete the look. The motorcycle is a long chrome chopper with towering handlebars, a stretched front "
        "fork, a round headlamp, an exposed engine and a pink fuel tank painted with a red heart and a yellow "
        "lightning bolt. A ghost rider of urban legend, loud, reckless and out for one last race."},
  {"Ps0054_040",  // Beelzebub
        "A monstrous giant fly, its bloated, ribbed abdomen and hunched body covered in blue-black chitin edged "
        "with ragged spines. Huge glossy red compound eyes bulge beneath a gold helm striped in black like a "
        "tiger, its brim sweeping up into horns. A long, segmented rust-red proboscis hangs from its face between "
        "curved white mandibles, and a necklace of small grey skulls rings its throat. Its thorny, crooked legs "
        "end in hooked claws, and one clutches a bone sceptre tipped with a skull. Two tall wings shimmer from "
        "white to green and violet, each marked with a black skull and crossbones. The lord of flies, regal and "
        "filthy."},
  {"Ps0054_050",  // Belphegor
        "A squat, brawny demon with deep purple skin, tall ridged horns curving upward, pointed ears, a hooked "
        "nose and small red eyes under a heavy brow, a nasty grin full of jagged teeth and a scruffy grey beard. "
        "A black spiked collar sits at his throat. His hands and lower legs are tan, like old leather gloves and "
        "boots, ending in purple claws, and a thin purple tail tipped with an arrowhead trails behind him. His "
        "throne is a gleaming white porcelain toilet, lid raised, never far from his backside. Lazy, crude and "
        "gleefully vulgar, a demon of sloth who would rather sit than stand."},
  {"Ps0055_000",  // Houou
        "A magnificent phoenix of Chinese and Japanese legend, built like a long-legged pheasant. Its body is "
        "crimson, its throat and breast covered in a ruff of shaggy jade-green feathers fading to pale mint, and "
        "a spiky red crest frames its face around a small gold beak. From its crown rises a tall golden plume "
        "curled into spirals like flames. Its broad wings are slate blue on the front with bright red edges and "
        "solid red behind, and an extremely long, thin tail of olive-gold feathers streams far behind it. Golden "
        "scaled legs end in sharp talons. Radiant and auspicious, a bird of good fortune on the wing."},
  {"Ps0055_010",  // Horus
        "A great golden falcon, the bird of an Egyptian sky god, every feather of its body, wings and long fanned "
        "tail shining gold, from deep amber to pale straw. Its head is fierce and compact, with a hooked pinkish "
        "beak and small, piercing blue eyes under a ruff of spiky golden feathers. Its wings are broad and "
        "pointed, and long tail plumes trail below. Its legs are clad in rust-red scales and end in big hooked "
        "talons of glossy black. Dazzling and proud, it looks like the midday sun given wings."},
  {"Ps0055_020",  // White Rider
        "A hooded skeletal horseman, a crowned rider of the apocalypse. Under a deep black hood grins a bare "
        "white skull, topped by a spiked gold crown. His long black robe has wide sleeves and hangs in tattered, "
        "ragged strips over his mount's flanks, a leather strap crossing his chest to a quiver of white-fletched "
        "arrows on his back, and he carries a long, slender wooden bow. He rides a pale white horse with a wild, "
        "shaggy straw-white mane and tail, its whole hide dotted with dozens of staring blue eyes. Silent, regal "
        "and deathly, he looks like conquest itself come riding."},
  {"Ps0061_000",  // Mara
        "A grotesque demon of lust, frankly and unmistakably phallic. Its towering green body is a ribbed, veined "
        "shaft capped with a smooth domed head, beneath which gapes a wide, wet pink mouth with a lolling tongue. "
        "Long tapering green spines fan out from its back, and small clawed limbs wave from its sides. It rides a "
        "gleaming brass war chariot carved with a grinning skull, with big spoked wheels, coiled springs and "
        "curved silver blades jutting from the front. Lewd, leering and absurdly proud of itself, it's as obscene "
        "as it is menacing."},
  {"Ps0061_010",  // ?
        "A skeletal temptress riding a seven-headed beast. The woman wears a long blood-red veil framing a bare "
        "white skull, a gold-banded headdress studded in black, a beaded necklace with a round gold pendant, and "
        "a low-cut red top with puffed sleeves showing pale cleavage, over billowing purple striped bloomers and "
        "long purple gloves; one hand raises a golden goblet. Beneath her prowls a huge red beast with seven "
        "snarling horned heads, each wearing a little spiked gold crown, its hide spotted with black diamonds, "
        "with bat-like red wings and a long spiny tail. Decadent, seductive and rotten to the bone."},
  {"Ps0061_020",  // Masakado
        "A vengeful samurai lord of Japanese legend, wild and imperious. A huge, windswept mane of deep blue hair "
        "falls over a stark white face painted kabuki-style with bold red streaks around glaring yellow eyes, set "
        "in a fierce scowl. He wears flowing robes of burnished gold patterned with thin circles, with broad, "
        "stiff shoulders over full white sleeves and wide gold trousers, and a white panel at his waist bears a "
        "black crest of small circles ringed around a central one. A long sword in a brown lacquered scabbard "
        "hangs at his waist. He looks like a furious ghost-general, proud and unforgiving."},
  {"Ps0061_030",  // Mada
        "A towering four-armed demon of intoxication in bold, clownish colours. Its tall, narrow purple head is a "
        "mask-like dome patterned with rows of orange flame strokes, with a grimacing set of square teeth near "
        "the bottom and fat turquoise curls like tusks and whiskers around it. Its stocky body and limbs are "
        "black, dotted with white spots and ringed with white stripes, with clawed purple hands, turquoise cuffs "
        "and discs at the wrists and a flaring turquoise skirt-like frill at the waist. Behind it stands a great "
        "turquoise wheel with eight spokes. Bloated, grinning and drunkenly menacing."},
  {"Ps0061_040",  // Matador
        "A skeleton bullfighter, all flourish and swagger. A grinning white skull peers out from under a teal "
        "tricorn hat trimmed with gold braid. He wears a matador's suit of lights: a short teal jacket heavy with "
        "gold embroidery, rows of gold ornaments set with red jewels across the front and big gold-encrusted "
        "shoulder pads, a white cravat pinned with a red gem, a red sash, tight white trousers striped with gold, "
        "and tall teal boots. One bony hand holds a long, thin curved sword with a gold cup guard, the other a "
        "red cape hung from a rod. Long dead, but still dancing with danger."},
  {"Ps0062_000",  // Michael
        "A warrior archangel, stern and powerful. His skin is a fiery orange-red, his dark slate hair swept back "
        "from a hard, handsome face with sharp yellow-green eyes. A golden breastplate moulded to his muscular "
        "chest and stomach sits under ornate gold shoulder guards, with gold bracers and anklets; below it hangs "
        "a long white skirt bordered in gold diamonds, slit at the side, and he goes barefoot. Huge wings sweep "
        "up from his back, pale tan feathers in front and blazing orange behind. He carries a long iron spear. "
        "Every inch the commander of heaven's armies."},
  {"Ps0062_010",  // Mishaguji
        "An eerie, pale serpent spirit in a slender human shape. Its head is a smooth, ridged white dome like a "
        "snake's or a grub's, with a thin slit of a mouth and no other face, framed by a fall of long black hair. "
        "Its lean body is chalk white, with a scaly mustard-yellow plate down the front, red stripes along its "
        "sides, and pink forearms and lower legs veined with white marks, ending in pink clawed hands and feet. A "
        "long, tapering ridged tail trails behind, and it carries a rough, pinkish-brown spear. Silent, alien and "
        "quietly unsettling."},
  {"Ps0062_020",  // Mitra
        "A fierce lion-headed god wrapped in a serpent. His body is a lean, muscular man's, skinned in deep "
        "crimson, and his head is a red lion's with piercing blue eyes and a thick, curling dark brown mane and "
        "beard. A huge snake banded in orange and black coils round and round him from ankles to shoulders, its "
        "dark head rising high above his own with a flicking red tongue. Two pairs of translucent rose-red "
        "feathered wings spread behind him, and he grips a dark hooked sickle in each hand. Solemn, kingly and "
        "coiled with power."},
  {"Ps0062_030",  // Mithras
        "A serene, ethereal youth rising out of a ball of rock. His slim, muscular upper body is a pale "
        "lavender-grey, his face delicate and cool with red eyes, framed by long golden hair that tumbles down in "
        "heavy corkscrew ringlets. A crested golden helmet like a sunburst fan sits on his head, and a gold "
        "armlet circles one arm. From the waist down he's sunk into a great black boulder, rough and pitted, "
        "carved all over with golden zodiac signs, a smooth pink crystal wedge opening at the front where his "
        "body meets it. Calm, cosmic and remote, he looks like the keeper of the heavens."},
  {"Ps0064_000",  // Metatron
        "A towering archangel who looks carved from silver and marble. His skin is a cold metallic grey, his "
        "swept-back golden hair falls to his neck, and his stern face has piercing green eyes and a small gold "
        "mark on the brow. Silvery plate armour trimmed in gold scrollwork covers his arms and legs, beneath a "
        "white robe draped over one shoulder and a long white tabard emblazoned with a tall gold cross, white "
        "ribbons hanging from a knotted sash. Great pale grey wings rise from his back, their upper tips ending "
        "in dark round knobs. Majestic, impassive and absolute, the very voice of heaven."},
  {"Ps0064_010",  // Melchizedek
        "An armoured angel with no face at all. His head is a smooth gold helmet, rounded and blank, with a "
        "single ridge down the middle ending in a pointed, beak-like edge where a face should be. His sleek body "
        "is clad in vivid purple, with a white panel running down the chest and stomach, white bands at the "
        "shoulders and black at the joints. Ribbed gold gauntlets cover his forearms, huge segmented gold greaves "
        "his legs, and a spiked gold collar holds a round turquoise jewel at his chest. Behind him spread dark "
        "grey wings made of stiff, straight slats like shutters. Cold, mechanical and implacable."},
  {"Ps0065_000",  // Mokoi
        "A gangly spirit of Aboriginal Australian legend that looks carved from green wood. Its head is a "
        "flat-topped block like a tree stump, the cut top showing reddish growth rings, with two big round "
        "staring white eyes and a thin, flat red-lipped mouth. Its body is lumpy and dark green, scored with "
        "grain-like cracks, with long dangling arms and stubby legs, and its only clothing is a white cloth tied "
        "loosely round its waist. In one hand it clutches a red boomerang tipped with yellow. Goofy at first "
        "glance, but those blank eyes and that flat mouth give it a creepy, sinister stillness."},
  {"Ps0065_010",  // Mothman
        "A strange, fuzzy moth-creature, about as tall as a person. Its body is a plump, egg-shaped bundle of "
        "shaggy steel-blue fur perched on two long, spindly dark legs with clawed bird feet. Its round head has "
        "two glinting red eyes and a wide, flat black slot of a mouth, and two thin antennae curve up from it, "
        "tipped with little green and blue feathery fans. Its broad wings are plain blue on the back, but in "
        "front they blaze with big black-outlined eyespots on red and yellow, edged with dark green feathers. "
        "Bizarre and a little comic, but an omen in the night all the same."},
  {"Ps0065_020",  // Mot
        "A tall golden coffin that lives. It's an upright six-sided casket of weathered gold-ochre stone, plain "
        "brown on its sides and back, its lid carved with a staring eye shooting out rays, a crescent moon and a "
        "round sun, and below them a stiff, long-eared figure flanked by spread wings above a coiling serpent, "
        "with lines of strange script at top and bottom. A single dark curved horn juts from the top. Two long, "
        "wiry arms covered in purple scales netted with bright red veins reach out from holes in its sides. Death "
        "itself, boxed up and restless."},
  {"Ps0071_000",  // Yakshini
        "A wild, seductive demoness with violet skin. Long straight black hair spills down her back and over her "
        "bare chest, which it barely covers, and her face is sharp and fanged, with pointed ears and bright blue "
        "eyes. A spiky gold headdress set with red jewels crowns her, two long gold horns sweeping up from it. "
        "Gold bands ring her upper arms, wrists and ankles, and her only clothing is a short red-and-white "
        "wave-patterned skirt hung with gold discs. She wields a pair of curved sabres with ornate gold hilts. "
        "Lithe, alluring and bloodthirsty, a beauty best admired from far away."},
  {"Ps0071_010",  // Yatagarasu
        "A great three-legged crow of Japanese legend, sacred and sharp-eyed. Its feathers are a deep, glossy "
        "blue-black, sleek on its body and broad on its wide wings, with a long, tapering tail. Its heavy curved "
        "beak is a dull greyish horn colour, and its eyes burn red beneath a stern, frowning brow. It stands on "
        "three scaly blue-black legs with hooked claws. Around its neck hangs a black cord threaded with three "
        "fat, glossy red comma-shaped jewels. Proud and watchful, it looks like a divine messenger come to lead "
        "the way."},
  {"Ps0071_020",  // Yamata-no-Orochi
        "A colossal eight-headed serpent from Japanese myth. Eight long, thick necks rise straight up side by "
        "side from one coiled body like a forest of towering columns, each scaled in deep mossy green along the "
        "back with a pale tan, ribbed belly in front. Each ends in a narrow snake's head with small icy blue "
        "eyes, and some rear with their jaws gaping open. A long, heavy green tail trails out behind the cluster "
        "along the ground. Vast, many-mouthed and hungry, it's a monster that could swallow a village whole."},
  {"Ps0072_000",  // Unicorn
        "A noble unicorn, sleek and pure. Its coat is a pale silvery lavender-white, smooth over a slender, "
        "well-muscled horse's body and long elegant legs, and each hoof is capped in gold. A long, spiralling "
        "golden horn rises straight from its forehead, framed by a shaggy, windswept mane of pale silver-green, "
        "with a long tail streaming out to match. Its face is narrow and fine-boned, with sharp red eyes and "
        "pointed ears. Graceful and proud, it looks gentle but untouchable, a creature that would let only the "
        "purest come near."},
  {"Ps0072_010",  // Yurlungur
        "A great rainbow serpent of Aboriginal Australian legend, impossibly long and slender. Its body is a "
        "smooth, thin tube stretching on and on, shading through the whole rainbow along its length, from pink "
        "and violet through sky blue, green and yellow to deep red and back to magenta. All along it run bold "
        "black bands and squared spiral patterns, like painted designs. Its blunt, rounded head is a deep purple, "
        "with small round gold eyes. Calm, ancient and endless, it looks like the arc of a rainbow come alive to "
        "wind across the land."},
  {"Ps0081_000",  // Rakshasa
        "A crimson demon warrior, lean and ferocious. His whole muscular body is a deep reddish pink, wrapped all "
        "over in spiralling pale pink bands like bindings around his arms, legs and torso. His face is a "
        "scowling, helmet-like mask with a ridged brow striped in pale pink and glinting eyes, and two long, thin "
        "red horns sweep up high like antennae. Long straight black hair falls past his shoulders. A broad black "
        "sash with a round gold boss cinches his waist, long black cloth panels hanging down in front, and he "
        "wields a pair of thin, straight swords with gold hilts. Wicked and quick, a man-eating demon of Indian "
        "myth."},
  {"Ps0081_010",  // Lakshmi
        "A graceful, serene goddess of fortune. Her honey-blonde hair is gathered into a sculpted bun of rolled "
        "curls, crowned by a small silver tiara set with a blue jewel, and her fine face has pale turquoise eyes, "
        "teal lips and a small gold mark on her brow. A wide silver collar and a strand of red beads circle her "
        "neck, over a short pale blue top that bares her midriff and an open black sleeveless vest. Loose pale "
        "blue trousers gather at her bare ankles beneath a black and blue panelled overskirt. A ribbon of sheer "
        "golden silk arches over her head and floats around her. Poised, gentle and radiant."},
  {"Ps0081_020",  // Lachesis
        "One of the Fates of Greek myth, stately and strange. She has a pale, mask-like face with golden eyes and "
        "a calm, unreadable expression, framed by a big, rounded bob of golden hair with two puffs of lilac at "
        "the sides, and a thick braided gold band round her head, looped into a handle on top like a basket. She "
        "wears a close-fitting, finely ribbed crimson bodysuit with black gloves and bare feet, and over it a "
        "stiff, flared mantle of grey interlocking links, open down the front. A long, thin measuring rod hangs "
        "level at her waist. Quiet and precise, she looks ready to measure out a life."},
  {"Ps0081_030",  // Raphael
        "A handsome archangel, clean-cut and proud. His skin is pale lavender, his spiky golden hair swept high "
        "and back, his face sharp with narrow green eyes. He wears close-fitting royal blue armour with a ribbed "
        "high collar, broad shoulder plates, bracers and greaves, a white sash draped over one shoulder and "
        "pinned with a gold clasp, and a long white tabard trimmed in gold and marked with gold crosses. Big "
        "wings spread from his back, pale blue-grey feathers in front and deep violet behind. He carries a long "
        "straight sword with a gold hilt. Composed, righteous and just a little vain."},
  {"Ps0081_040",  // Lamia
        "A serpent-woman of Greek legend, beautiful above and monstrous below. From the waist up she's a slender "
        "woman with pale skin, pointed ears and long, wavy blue-black hair falling over her bare chest, with gold "
        "bands on her arms and wrists and a necklace with a blue pendant. Below her hips her body becomes an "
        "enormously long snake's tail, many times her own height, scaled in rich red patterned with dark swirls "
        "along the back, with a ridged dark brown belly, tapering to a fine point. Seductive and coldly smiling, "
        "she's a temptress who would happily coil around her prey."},
  {"Ps0081_050",  // Rangda
        "A terrifying witch-queen of Balinese legend. A vast, spiky black mane bursts around her head and pours "
        "down to the ground. Her face is red, with bulging blue eyes, curved white tusks and a bundle of green "
        "sticks clenched across her mouth. Her chest is painted pink with black swirls, a gold collar sits at her "
        "throat, and her long red arms end in enormous needle-thin claws. At her waist hangs a gold and silver "
        "demon mask with red eyes, from which drops a long tongue-like panel striped red, gold and black, flanked "
        "by strings of black and red lanterns ending in gold anchor hooks. Savage, garish and fearsome."},
  {"Ps0082_000",  // Leanan Sidhe
        "A pale fairy-muse of Irish legend, a gaunt and dangerous beauty. Her long, straight blonde hair, held "
        "back by a dark band, falls in a single sheet down her back and past her feet. Her face is sharp and "
        "bloodless, with pointed ears, red eyes and dark red lips. She wears a long, clinging violet-black gown "
        "with a high, stiff, flared collar and a deep plunging neckline down to her stomach, slit up one leg, and "
        "goes barefoot, her nails painted red. Thin silver trinkets glint in her hands. Seductive and draining, "
        "she's the kind of lover who leaves poets wasting away."},
  {"Ps0082_010",  // Lilith
        "A slender temptress of chalk-white skin, a demon of Hebrew legend, with black hair swept up and back in "
        "a sleek crest, gold snake eyes, dark lips and long black nails. Her only covering is of grey and black "
        "snakeskin that wraps her body in spiralling bands: a strip across her bust, a scaled collar at her "
        "throat, coils down her arms and legs. A huge brown python with a pale belly loops around her neck and "
        "shoulders and hangs past her knees, its head at her chest flicking a red tongue. Bare, cold and coolly "
        "seductive, she is a serpent's lover through and through."},
  {"Ps0082_020",  // Lilim
        "A lithe, long-legged demon girl with smooth tan skin, sleek black hair falling to her shoulders, pointed "
        "elf ears, blue eyes and full pink lips. She wears a tiny cropped white jacket with a high zipped collar, "
        "left wide open over her bare chest, white gloves, and low white hot pants with a broad belt and a round "
        "silver buckle, her slim waist and legs bare down to her bare feet. A small dark tattoo marks one thigh. "
        "Plum-red bat wings spread from her back and a thin tail ends in an arrowhead. Flirty, sultry and "
        "playful, she is a succubus who knows exactly the effect she has."},
  {"Ps0083_000",  // Lucifer
        "A towering fallen angel, a demon lord of muscle and shadow, with dark blue-green skin over a heavily "
        "ribbed, sinewy body, long clawed hands and taloned feet. Wild golden hair falls about a grim, scowling "
        "face with red eyes, and two long, ridged ivory horns curl up from his brow like a ram's. Six enormous "
        "bat wings, three pairs, fan out around him, dark teal on the outside and blood red within, veined like "
        "flesh, their tips hooked into claws. Long ribbons of pale grey cloth wind loosely around his body and "
        "drift above his head. He looks every inch the king of hell: vast, proud and terrible."},
  {"Ps0083_010",  // Helel
        "A beautiful, slender angel of pale ashen skin and a calm, androgynous face with glowing gold eyes, long "
        "golden hair falling past his waist, and two thick, ridged, dark grey horns curving out and up from his "
        "head like a ram's. He is bare but for a long ribbon of pale lavender-silver cloth that spirals loosely "
        "around his body from chest to ankles and streams up above his head. Behind him spread three pairs of "
        "great white feathered wings, softly tinged with lilac, fanning out on every side. Radiant and serene yet "
        "horned, he is the morning star before the fall, lovely and quietly unsettling."},
  {"Ps0084_000",  // Legion
        "A bloated ball of fused crimson flesh about the size of a person, made of many bald, bulging heads "
        "pressed together, each face screaming with its mouth stretched wide over rows of square teeth, brows "
        "knotted and small yellow eyes glaring. Veins and folds ripple over the purplish-red skin. Thick, ringed "
        "tendrils like fat worms wriggle out all around it, ending in pointed, diamond-shaped tips, and more loop "
        "and coil over the surface between the faces. Heavy limbs hang beneath it like dangling feet. A howling "
        "mob of the damned crushed into one body, it is pure, shrieking horror."},
  {"Ps0085_000",  // Loa
        "A giant human skull, pale white bone with a few dark cracks across the crown, its empty eye sockets "
        "black and its grin full of big square teeth. A long, slender snake of dark green scales with a bright "
        "golden-yellow belly coils over the top of the skull, winds out through one eye socket and around the "
        "jaw, and trails a long tail beneath. Its head rears from the skull's eye with small red eyes and an open "
        "mouth showing a pinkish-purple lining. Simple, stark and eerie, it is a voodoo spirit of death, the "
        "grave and the serpent wound together."},
  {"Ps0085_010",  // ?
        "A tall, slim trickster god with sea-green skin, a sly grin of big white teeth, long straight blond hair "
        "falling in a curtain past his shoulders and a green stripe slashed across one eye. He wears a skin-tight "
        "dark purple suit fastened down the chest with chunky square silver clasps, silver studs on his shoulders "
        "and wrists, a stack of silver rings around his neck, and dark boots with long toes curling up into a "
        "jester's hook. Huge purple-black bat wings rise behind him and curl over at the tips. Smirking and "
        "elegant, he is the Norse god of mischief, charming and not to be trusted."},
  {"Ps1001_010",  // Orpheus
        "A slender, puppet-like figure built into a great harp, a Greek musician of legend made machine. His face "
        "is dark grey with one red eye glowing beneath ash-white hair and a pale blue headband, and a red scarf "
        "wraps his neck. His body is teal metal plating with dotted speaker grilles on the chest, puffy pale grey "
        "sleeves and shorts, and a round porthole set in his belly. His legs are two plain pale pillars. Behind "
        "him rises a pale green lyre with scrolled arms, a shell crest and blue strings. Quiet and enigmatic, he "
        "is a melancholy bard of steel."},
  {"Ps1001_011",  // Orpheus Telos
        "A slender, puppet-like figure built into a great golden harp, the same musician-machine recast in red "
        "and gold. His face is pale grey with one bright cyan eye beneath golden blond hair and a red headband, "
        "and a soft grey scarf wraps his neck. His body is glossy red plating with dotted speaker grilles on the "
        "chest, gold piping, and a gold-rimmed round porthole in his belly. His legs are two plain pale grey "
        "pillars. Behind him rises a gleaming gold lyre with scrolled arms, a shell crest and gold strings. "
        "Brighter and nobler than before, he looks like a bard reborn in triumph."},
  {"Ps1001_020",  // Io
        "A slim, faceless maiden riding a huge bull's skull of polished ivory and black, the head of the heifer "
        "of Greek myth turned into a chariot. Her skin is slate grey, her closed eyes streaked with black tears, "
        "and her golden hair is braided up into a tall plume curling like a flame. She wears a loose salmon-pink "
        "blouse with fluttering sleeves and a gold choker, her grey legs folded into a padded orange seat set in "
        "the skull's brow. The skull has two towering ridged horns, staring eyes ringed with black lashes, black "
        "panels and a trailing chain. Sad, serene and strange, she is a gentle passenger of sorrow."},
  {"Ps1001_030",  // Hermes
        "A slim, dark figure of bronze and gold, the swift messenger god of Greece. Its face is hidden by a gold "
        "helmet with a black grilled visor, swept back into a long winged blade of silver and gold. It wears a "
        "fitted, high-collared bronze-brown coat with a long skirt cut into jagged panels, gold trim at the "
        "collar, gauntlets and tall bronze boots over black tights. From its back spread two great golden wings, "
        "not feathered but cut from metal into lacy, sweeping openwork, studded with rivets along their edges. "
        "Sleek and sharp, it looks built for speed."},
  {"Ps1001_040",  // Polydeuces
        "A hulking, muscle-bound giant in a pale teal bodysuit criss-crossed by stitched cream straps, the boxer "
        "twin of Greek myth. His head is tiny and sunk deep into his collar, just a blank pale face with two "
        "round, empty eyes peering out under a heavy blond fringe, while long golden hair pours down his back to "
        "his thighs. A cream vest of square silver plates armours his chest, and a cream belt and plated straps "
        "ring his waist and legs. His hands and feet are bright red, and one forearm is a huge grey syringe-like "
        "cannon. Powerful and mute, he is a brawler built like a tank."},
  {"Ps1001_050",  // Penthesilea
        "A tall, slim warrior queen in fitted armour, the Amazon of Greek legend, her face hidden completely by a "
        "smooth teal-grey knight's helm with a narrow eye slit, topped by a small gold crown. A dark navy jacket "
        "with a high, flared collar is hung with silver chains, and a white lace cravat falls over a teal steel "
        "corset that hugs a shapely figure, with riveted cups over her chest and a short flared skirt plate. Dark "
        "green stockings run to wide white cuffs and black heeled boots, and she carries a long, slender "
        "gold-hilted sword. Cold, regal and deadly, she is a duellist sworn to battle."},
  {"Ps1001_060",  // Lucia
        "A towering lady in an enormous ball gown, a blind mother goddess of a lost kingdom. Her head is wrapped "
        "in white bandages, with only a smooth red face showing, and a wild mane of ash-blonde hair streams out "
        "to the sides. A rose-pink corset sits over a black off-shoulder top with pale pink frilled cuffs and "
        "long pink sleeves. Her vast skirt is a glossy dome of deep blue and teal, mottled like a night sky or "
        "deep water, netted with gold filigree in a sunburst ring and studded with small jewels, and draped in "
        "rose-pink silk that sweeps behind into a long train. Gentle and protective, she is a great sheltering "
        "bell of a woman."},
  {"Ps1001_070",  // Palladion
        "A tall, stately goddess of war whose body seems carved from teal stone, her blank serene face framed by "
        "two long braids. A teal helmet trimmed in gold rises into a sweeping red horsehair crest, with a black "
        "spearhead jutting straight up through its middle. Over her shoulders sits a golden mantle of fish-scale "
        "plates with a round sun face on the chest, and a gold sash cinches her waist. Wide, fluted sleeves hang "
        "from her arms and a long teal gown flares out to the floor in great rippling folds. Calm, statuesque and "
        "unshakable, she is a guardian statue come to life."},
  {"Ps1001_080",  // Nemesis
        "A tall, skeletal construct of dark slate-blue armour, a goddess of retribution turned machine. Its head "
        "is a tall, pointed spire split by a glowing blue line, and its chest is a broad, curved plate set with "
        "two round orange eyes, watchful and staring. Long, thin arms end in clawed fingers, and its legs taper "
        "down to points like stilts. Behind it hangs a huge dark ring like a gear wheel, its outer edge a blazing "
        "band of blue teeth, with a zigzag of blue light and a thinner gold ring inside. Cold, precise and "
        "patient, it looks like judgement itself, wound and ticking."},
  {"Ps1001_090",  // ?
        "A three-headed hound of the underworld, taller than a man, its long-muzzled heads black with white jaws, "
        "sharp yellow eyes and snarling red mouths full of teeth. Each head sits on a thick neck guarded by an "
        "engraved silver collar plate, and heavy chains hang in loops across its deep blue chest and down its "
        "sides. Its body is black above and blue beneath, ribbed and lean. Its legs are encased in long silver "
        "greaves ending in three-pronged trident points instead of paws, small dark wings sprout from its back, "
        "and a long spiked tail juts out behind. Fierce and loyal, it is a guard dog of the dead."},
  {"Ps1001_100",  // Castor
        "A massive dark knight fused with his black warhorse, the horseman twin of Greek myth. His broad, muscled "
        "body wears a black bodysuit striped with silver stitching, a vest of grey steel plates, buckled straps "
        "on his arms, and his hands and feet are deep blue. His head is a tiny pale skull-like face sunk into his "
        "collar beneath a heavy blond fringe, and long golden hair pours down his back. Before his chest rears "
        "the horse's head in grey barding with a single long golden horn, and its black body and hooves swing out "
        "behind beneath ragged dark plates. Grim and imposing, rider and steed are one."},
  {"Ps1001_110",  // ?
        "A bodiless gown floating on the air, an ethereal butterfly spirit. Where a woman should stand there is "
        "only a slender gold lattice like a little tower, rising from a ring of cream roses on a fluted white "
        "bodice. Below, a wide white ball gown falls in gathered swags, with a second band of cream roses at the "
        "waist. At the top, a narrow crimson head with small hollow eyes spreads into two vast butterfly wings of "
        "glowing red stained glass, veined in dark crimson, dripping into long curling trails. Two drifting grey "
        "ribbons stand in for arms. Lovely, ghostly and fragile, she is beauty with no one inside."},
  {"Ps1002_010",  // Messiah
        "A lean, pale saviour figure whose body is bound in ribbed cream wrappings like bandages, with long legs, "
        "gloved white hands and a teal top over a ridged belly. A soft grey hood and scarf wrap his head and "
        "neck, his golden blond hair spills over one side of his face, and the face beneath is a smooth white "
        "mask cracked by a thin line, with one glowing red eye. A tall slate-grey cross towers behind him, "
        "sprouting long, downswept grey feathered wings at its base, and he carries a long black rod banded in "
        "grey. Solemn and otherworldly, he is a saviour risen from the coffin."},
  {"Ps1002_020",  // ?
        "A regal goddess of ancient Egypt built of gold, black and enamel, with a pale, calm face beneath a white "
        "headdress and violet-ringed eyes. Two tall black horns curve up from her brow and cradle a great glossy "
        "red sun disc above her head. Her black body is laced with gold, her shoulders capped in bands of red and "
        "blue feather patterns, and a large golden ring stands at each side. Long wings spread from her arms, "
        "enamelled in red and blue feathers with ivory edges, and her body tapers to a gold spindle point instead "
        "of legs. Serene, majestic and protective, she is a winged mother of magic."},
  {"Ps1002_030",  // ?
        "A slim, striking figure dressed head to toe in glossy red, the thrice-great god of alchemy. Its head is "
        "a white beaked helmet with a black lattice visor and a red ball on its crest, sweeping back into a long "
        "silver and gold blade like a wing. A high-collared red coat striped with fine gold pinstripes flares "
        "into a long skirt cut into jagged panels, with silver shoulder plates, red gauntlets and tall red boots. "
        "Two huge golden wings of riveted, lacy metal openwork spread from its back, and one long gleaming "
        "blade-wing juts from a shoulder. Brilliant and fiery, it looks like a herald of transformation."},
  {"Ps1002_040",  // ?
        "A towering emperor in a white hooded robe, his face a black mask with glowing red eyes, crowned with a "
        "silver laurel wreath. A white scarf knotted at the throat drapes his shoulders, and a red-lined cape "
        "hangs behind. His chest opens like a lit shrine: inside a glowing red niche sits a small dark man on a "
        "throne, legs crossed, chin on hand, thinking. His dark, muscular arms are banded with silver, a skirt of "
        "white scale plates hangs at his waist, and his bare black feet stand on a small globe of the Earth. He "
        "bears a plain sword. Proud and commanding, he holds the world underfoot."},
  {"Ps1002_050",  // ?
        "A tall, haughty warrior queen in navy and gold, her pale face half hidden by a bright red mask over her "
        "eyes and hair, gold ram-like curls at each ear. A high-collared navy coat opens on a white cravat and a "
        "navy corset ribbed in gold that hugs her bust and wasp waist, its chest cups riveted in gold. Golden "
        "spiked plates flare from her shoulders and hips, a stone lion's face is set at her belt, and a wide navy "
        "skirt puffs out from a gold toothed hem. Long green boots and a long, whip-thin rapier complete the "
        "look. Severe, imperious and alluring, she rules by fear."},
  {"Ps1002_060",  // Juno
        "A towering goddess-queen in crimson and blue, her face a white mask set with seven orange, almond-shaped "
        "eyes, framed by flowing pale blue hair and a red-and-white frilled bonnet. A red corset over a black "
        "off-shoulder top meets long red sleeves frilled white at the shoulder. Behind her spread wide "
        "charcoal-grey wings edged in red, each set with a row of peacock eyes in teal, blue and orange rings. "
        "Her huge skirt is a glossy dome of deep blue, netted with gold scrollwork in petal shapes around a "
        "pointed red panel, and draped in crimson silk that sweeps behind into a long train. Graceful and "
        "all-seeing, she is a peacock queen of the heavens."},
  {"Ps1002_070",  // ?
        "A noble war goddess in gold and white, her calm blue-grey face framed by brown braids beneath a gold "
        "Greek helmet with a tiny sphinx and a tall red crest. A golden mantle of fish-scale plates covers her "
        "shoulders, and a long white gown billows down in great flowing folds where legs would be. Before her "
        "stands a huge round shield of royal blue and gold, edged with gold waves and patterned with a stern "
        "red-eyed face. A long blue-and-gold bar runs across her body, a mirror disc at one end and a gold "
        "spearhead at the other. Shining, vigilant and fearless, she is a shield-maiden of wisdom."},
  {"Ps1002_080",  // ?
        "A tall, spindly war machine of red-orange and black armour, a god of retribution reborn. Its chest is an "
        "angular orange block with no face, its slim arms end in clawed black hands, and its legs taper to long "
        "orange spikes. On each shoulder sits a huge black sphere studded with small orange-lit plates, wrapped "
        "in a skeletal steel cage, its outer face marked with bold orange zodiac signs: twins, lion, crab and "
        "more. Two broad silver bands cross in a great X over its body, arching from sphere to sphere like the "
        "paths of orbits. Cold and celestial, it looks like judgement written in the stars."},
  {"Ps1005_010",  // Thanatos
        "A tall, gaunt reaper of a figure in a long, high-collared navy greatcoat studded with silver rivets, its "
        "skirts flaring around stick-thin legs of bone-white plate that end in gold-tipped points. Its face is a "
        "smooth white skull-like mask drawn into a sharp beak, with a jagged grin of dark teeth. Red leather "
        "straps cross its chest, a gold buckle shines at its belt and a long black sword hangs at its hip. Rising "
        "from its back is a crown of eight black coffins, each lid carved with a pale shrouded figure, all hung "
        "together on heavy iron chains. It is death made a soldier: cold, silent, inevitable."},
  {"Ps2001_010",  // Hypnos
        "A slender, bald, man-shaped figure with smooth, pale sea-green skin, every inch of it threaded with thin "
        "branching red veins, as if the body had been peeled back to its circulation. A dark grey sleep mask with "
        "a thin strap covers its eyes. From its spine fans a set of bright red ribs that gather into two long "
        "black arms, which end in huge, ragged wings of torn charcoal feathers spreading far wider than the body. "
        "Quiet, blind and dreaming, it has the eerie calm of a sleepwalker who never means to wake."},
  {"Ps2001_020",  // Moros
        "A tall, stilt-legged machine assembled like a clock tower taken apart. Its head is a wide, inverted "
        "grey-steel cone, its rim engraved with a ring of numerals like a clock face, banded with teal, topped by "
        "a thin white spire and capped with a black strip of scrolling green digital lettering. Below it a "
        "smaller funnel of a body narrows to a downward spike between two legs of ball joints and slim, flaring "
        "white shafts with flat feet. One arm is a horizontal rod strung with white spheres, ending in green "
        "prongs. It feels like a mechanical countdown on legs, ticking towards doom."},
  {"Ps2001_030",  // Medea
        "A tall, impossibly slender woman, all long limbs and narrow waist, with a womanly figure sheathed in "
        "matte black. Her arms and legs are glossy blood red, licked with golden flame shapes at the hips and "
        "shoulders, and a thin gold line runs from her throat down her body to a gold heart-shaped ornament. Her "
        "face is hidden behind a pale bone-coloured mask with curled ram's horns and narrow, glaring red eyes, "
        "and a mane of long, ropy, straw-gold dreadlocks falls to her thighs. At her feet lie a wavy black dagger "
        "and a small golden chalice. She is a sorceress of poison and grudges, elegant and vicious."},
  {"Ps5001_010",  // Arsène
        "A tall, lean gentleman-demon in a fitted blood-red tailcoat and high red boots with spurred black heels, "
        "a frilled white cravat bunched at his throat beneath a fine gold chain. A towering black top hat sits on "
        "a black-and-red mask whose sharp, flared points sweep out like a beak, and his long black-clawed fingers "
        "hang from red sleeves. From his back spread two enormous wings of glossy black feathers with a purple "
        "sheen, wider than he is tall. Dashing, theatrical and wicked, he is a phantom thief of a devil, a "
        "gentleman burglar who steals hearts with a flourish."},
  {"Ps5001_020",  // Captain Kidd
        "A swaggering skeleton pirate captain riding the deck of his own ship. A black tricorn hat edged in gold "
        "and marked with a skull and crossbones shades a grinning white skull face with one glowing red eye and a "
        "skull patch. He wears a tight blue jacket with gold frogging under a black vest, two grey belts crossed "
        "over his chest with a pair of heavy chains ending in anchors, and two broad curved cutlasses crossed "
        "behind his head. His arms end in chunky black cannons with gold-rimmed muzzles. Below him floats a small "
        "black galleon, and a tattered red-and-black coat streams behind. He is pure buccaneer bravado."},
  {"Ps5001_030",  // Zorro
        "A hulking masked swordsman, an enormous dark-grey barrel chest and huge rounded arms balanced on thin, "
        "almost spindly legs. His tight black outfit is embroidered with silver vines and studded with rivets, "
        "cinched by a red sash and an ornate silver belt buckle carved with a bold Z. His small head is hidden "
        "under a black hood and mask with sharp yellow eyes, framed by a tall, spiked white collar, and a "
        "wide-brimmed black hat flares above with a sweeping black cape. In one hand he holds a slim silver "
        "rapier. He is a dashing folk hero of a masked avenger, all flourish and gallantry."},
  {"Ps5001_040",  // Carmen
        "A tall, curvaceous temptress in a flamenco gown of layered ruffles striped in deep red, black and coral, "
        "its bodice heaped with red roses and cut low to show pink skin. Her face is pink, behind a dark speckled "
        "masquerade mask with fiery eyes; a cigarette dangles from her lips, a black choker circles her slim "
        "throat, and her black hair is piled in two drill-curled buns. Her lacy black gloves trail thorny green "
        "vines that lead out to a pair of small men in black suits, each with a big pink heart for a head and "
        "dazed heart eyes. Sultry and dangerous, she keeps her admirers on a leash."},
  {"Ps5001_050",  // Goemon
        "A flamboyant kabuki outlaw in a riot of colour. A huge rope of twisted navy and white curls in two loops "
        "above his shoulders, and a dark purple cap sits over a white kabuki face painted with teal and red "
        "streaks. His black robe has enormous winged sleeves, trimmed in bright teal and lined with pink leopard "
        "print, over a red cross-wrapped front, a black-and-white diamond-patterned undergarment and a chequered "
        "sash of yellow and black knotted with red cord. Under one arm rests a giant white pipe painted with gold "
        "flowers. Balanced on tall wooden clogs, he is a stage-strutting master thief, loud, proud and dramatic."},
  {"Ps5001_060",  // Johanna
        "A sleek, armoured motorcycle with no rider, built big and heavy like a beast of chrome. Its body is "
        "polished pale silver-blue steel, sculpted into sharp, curving plates with fin-like flares, deep chrome "
        "engine blocks and wide side panels that bulge out over its two fat, treaded tyres and turbine-spoked "
        "wheels. A tall crest of deep royal blue rises over the front like a helmet's plume, and a pair of long "
        "silver handlebars stretch out from it above a black seat. Fierce and gleaming, it is a war machine for "
        "an iron-willed queen, built to charge straight through anything in its way."},
  {"Ps5001_070",  // Milady
        "A towering noblewoman made almost entirely of ballgown, a vast bell skirt of hot magenta silk painted "
        "with gold lilies and swirling vines, a pair of shut, lashed eyes and a smiling pair of gold lips across "
        "the front, hemmed with pink ruffles and a fringed gold border. Deep wine-red drapes swag around it, "
        "gathered into black panels with red bows. Above, a slim black corset rises to puffed sleeves of striped "
        "pink and a stiff white fan-shaped collar, with a teal ribbon at her throat and a small dagger hanging at "
        "her breast. Elegant, mature and quietly deadly, she is a court beauty with secrets beneath her skirts."},
  {"Ps5001_080",  // Robin Hood
        "A muscular armoured hero, half archer of legend and half comic-book superhero. His plating is white and "
        "silver, trimmed in gold, with gold epaulettes tipped by red spikes, a red studded belt and a short "
        "fringed skirt. A big blue heart-shaped plate on his chest bears a gold and red emblem of two bold "
        "letters, R and H. His helmet is black with a red crest and two swept gold wings rising from it, and a "
        "long, speckled blue-and-white cape streams behind. He wields a long golden arrow. Bright, square-jawed "
        "and earnest, he looks like a hero of justice posing for his own poster."},
  {"Ps5001_090",  // Cendrillon
        "A tall, delicate fairy-tale princess in glass armour, her long, slender legs sheathed in faceted "
        "royal-blue and sky-blue crystal that tapers to golden points instead of feet. Her bodice is cut ice-blue "
        "crystal around a violet gem, and her arms are black, traced with swirling cyan lines. Her black face, "
        "with glowing cyan eyes and pink lips, peeks from a deep blue hood under a gold visored helmet crowned "
        "with a big pale cyan bow whose tails flare up like feathered wings. A tall gold filigree collar stands "
        "behind her neck, a short skirt of gold scrollwork flares at her hips, and a sheer white cape hangs "
        "behind, scalloped like a petticoat. A Cinderella dressed for battle, glittering and graceful."},
  {"Ps5002_010",  // Satanael
        "A towering dark god of rebellion with six vast, ragged black bat-like wings spread around him, lined "
        "with dark feathers and tipped with gold barbs. His long, lean body is clad in black and ash-grey armour "
        "with fluted gold-trimmed plates over the shoulders and hips, a fitted gold-buttoned jacket and a crimson "
        "sash running across his chest to a gold star medal. His face is a gilded mask framed by two great "
        "sweeping golden horns. A long, needle-thin dark weapon with a gilded grip hangs from one clawed hand. "
        "Majestic and ominous, he is a fallen angel standing tall against heaven itself."},
  {"Ps5002_020",  // Seiten Taisei
        "A stocky, muscular monkey king of Chinese legend, riding a big, round black storm cloud curled with "
        "spiral patterns and marked with a yellow and red eye. His skin is black, and his opera-style armour is "
        "bright red, teal and gold, wrapped in silver chains crossing his chest, over baggy red trousers. A thick "
        "red scarf bunches at his white monkey face, which wears green goggles, and a huge golden crest of spikes "
        "bursts up from his head in a burning sunburst. He carries a long red and black staff capped in gold, and "
        "golden ribbons stream from his shoulders. Cocky and unstoppable, he is a born trickster warrior."},
  {"Ps5002_030",  // Mercurius
        "A slim, swift messenger in a skin-tight royal-blue jumpsuit quilted like scales, zipped down the front "
        "with a gold symbol of a circle and cross at the chest. A blue hood frames a black face mask, crowned "
        "with two flaming red wing-shapes that sweep up like horns, and big ribbed gold shoulder plates and "
        "armoured gold gauntlets and boots gleam with scale patterns. Two great wings of layered blue, silver and "
        "sky-blue feathers sweep down from his back to his heels. Beside him floats a tall gold staff twined in "
        "spirals and topped with a pair of small wings. Sleek and quick, he is a god of speed and cunning."},
  {"Ps5002_040",  // Hecate
        "A gaunt, theatrical demon queen whose body tapers to a single slim black stem flaring into a pedestal at "
        "the floor. A tall cape of bat-like red and black wings drapes around her, its scalloped hem dripping "
        "with silver claws. Her head is lost under a pair of huge black antler-like horns, and in the curve of "
        "them glare two huge cat eyes of blue and orange with slit pupils. Silver spiked armour shields her "
        "chest, and in each hand a hoop leads to a long chain ending in a small, fanged blue demon head with a "
        "red maw. Spooky and stylish, she is a goddess of witchcraft."},
  {"Ps5002_050",  // Kamu Susano-o
        "A brawny, wild-haired storm god of Japanese myth with smooth, bright blue skin covered in dark red "
        "tribal tattoos. A tall, shaggy mane of white spiked hair bursts up around a gold mask with red eyes and "
        "two tall gold horns. A long red-and-gold patterned scarf stretches across his shoulders like a banner. "
        "He wears a dark, studded skirt of layered black armour over loose black trousers and gold-cuffed boots, "
        "with a gilded collar of jagged plates at his waist. On his back hangs a huge, black, blocky broadsword, "
        "and in his hand a slender black blade of linked segments. Fierce and untamed, he is a tempest with "
        "fists."},
  {"Ps5002_060",  // Anat
        "A powerful war goddess built from a motorcycle, her limbs and body all polished pale silver-blue steel "
        "panels, chrome pistons and black machinery. Her face is a stern blood-red woman's head, with a deep blue "
        "crest behind it and two great curving golden horns. A grinning red skull sits on her chest over a gold "
        "collar, and her hands are gold claws, her shoulders bristling with gold blades. One wheel hangs on her "
        "back, the other forms her knees, and a whole matching motorcycle stands beside her, its blue crest "
        "raised. Ferocious and unstoppable, she is a goddess of war who rides into battle as her own steed."},
  {"Ps5002_070",  // Astarte
        "A slender, voluptuous goddess with deep black skin, perched atop a gigantic floating skull. She wears a "
        "gold bra of coiled rings, gold bangles and anklets and a gold choker, her long black hair streaming out "
        "behind her, and a huge golden crescent moon arcs over her head like a halo. The skull below is enormous "
        "and bubble-round, covered all over in a cheerful print of pink, purple and orange flowers, with big "
        "round green eyes and blue-lashed sockets, ringed at its jaw by sweeping golden bands and ending below in "
        "a black arrow-tipped spike. Seductive and playful, she is a love goddess riding a carnival of death."},
  {"Ps5002_080",  // Loki
        "A tall, slender trickster god covered from head to toe in dazzling black and white zebra stripes, "
        "swirling in chevrons over a lean, armoured body. His head is a smooth black mask crowned with two "
        "curling horns striped black and white, and from it spill long, thick black braids streaked with red, "
        "trailing to his knees. Thin gold chains loop across his chest, and his feet end in gold high-heeled "
        "points. Floating beside him is a long, blazing red-orange greatsword like a tongue of fire, with a "
        "black, jagged hilt. Dazzling and unsettling, he is a mischief-maker whose patterns hurt to stare at."},
  {"Ps5002_090",  // Vanadis
        "A tall, slender warrior goddess in deep scarlet. A black hood hangs like a veil from her head to her "
        "shoulders, and from it rise two tall, curved, scarlet horns like a helmet's crest, framing a dark face "
        "with small golden eyes over a white ruff collar. Her red bodice is laced with gold scrollwork and black "
        "heart-like patterns, and from her waist flares a wide skirt of red scales that opens into a great ring "
        "of dark brown and black feathers, spreading out like wings. Long red stockinged legs end in sharp black "
        "points. She is a Norse goddess of love and battle, poised and proud."},
  {"Ps5003_010",  // Izanagi
        "A tall, lean warrior in a long black high-collared greatcoat lined with blood red, its skirts falling to "
        "his ankles and its front fastened with buckles and a silver-grey zip. His face is a smooth silver mask "
        "with narrow yellow eyes and a pale cloth beneath, under a white helmet band with two short horn-like "
        "points. Long grey sleeves end in black gloves, gold crests sit on his shoulders, and his legs are plated "
        "in grey armour tapering to spiked feet. A white scarf trails behind him, and he grips a huge, broad, "
        "black-bladed cleaver of a sword. Stoic and steady, he looks born to seek the truth."},
  {"Ps5003_020",  // Magatsu-Izanagi
        "A tall, lean warrior, cloaked in a long, high-collared greatcoat of mottled blood red, its skirts "
        "falling to his ankles, its front lined with black panels and fastened with rows of red buckles. His face "
        "is a dark red mask with narrow glowing yellow eyes and a dripping red cloth, under a black band and two "
        "short horn-like points. Black stripes run down his red sleeves, which end in red clawed hands, and his "
        "legs are red armour tapering to spikes. A long black scarf streams behind him, and he grips a huge, "
        "broad black sword with a blood-red edge. A sinister, corrupted mirror of a noble warrior, bloodied and "
        "hungry for chaos."},
  {"Ps5003_030",  // Kaguya
        "A slim, elegant moon princess of Japanese folklore in a skin-tight orange-red bodysuit and long red "
        "stockings, cut close to her womanly curves and banded with gold at the thighs. Her face is smooth and "
        "black, a deep green gem at her throat, under a gold headdress with two long, pale rabbit-ear plumes. "
        "Long strands of magenta hair stream behind her, and loops of cream ribbon curl around her and trail past "
        "her feet. From her back spread two vast, flat wings of glossy black panels framed in red, drawn with "
        "neon swirls of pink, yellow, green and cyan around red-and-white target discs, their edges fanned with "
        "layered rainbow bands. Ethereal and distant, she belongs to the night sky."},
};
const Use kPersonas[] = {
  {0, "Ps1001_010"}, {1, "Ps1001_020"}, {2, "Ps1002_020"}, {3, "Ps1001_030"}, {4, "Ps1002_030"}, {5, "Ps1001_040"},
  {6, "Ps1002_040"}, {7, "Ps1001_050"}, {8, "Ps1002_050"}, {9, "Ps1001_060"}, {10, "Ps1002_060"}, {11, "Ps1001_070"},
  {12, "Ps1002_070"}, {13, "Ps1001_080"}, {14, "Ps1002_080"}, {15, "Ps1001_100"}, {16, "Ps1001_090"},
  {17, "Ps1001_110"}, {35, "Ps0001_000"}, {36, "Ps0001_010"}, {37, "Ps0001_020"}, {38, "Ps0001_030"},
  {39, "Ps0001_040"}, {40, "Ps0001_050"}, {41, "Ps0001_060"}, {42, "Ps0001_070"}, {43, "Ps0001_080"},
  {44, "Ps0001_090"}, {45, "Ps0001_100"}, {46, "Ps0001_110"}, {47, "Ps0001_120"}, {48, "Ps0002_000"},
  {49, "Ps0002_010"}, {50, "Ps0003_000"}, {51, "Ps0003_010"}, {52, "Ps0003_020"}, {53, "Ps0003_030"},
  {54, "Ps0003_040"}, {55, "Ps0004_000"}, {56, "Ps0004_010"}, {57, "Ps0005_000"}, {58, "Ps0005_010"},
  {59, "Ps0005_020"}, {60, "Ps0005_030"}, {61, "Ps0005_040"}, {62, "Ps0005_050"}, {63, "Ps0005_060"},
  {64, "Ps1001_010"}, {65, "Ps1001_011"}, {66, "Ps0005_070"}, {67, "Ps0005_080"}, {68, "Ps0011_000"},
  {69, "Ps0011_010"}, {70, "Ps0011_020"}, {71, "Ps0011_030"}, {72, "Ps0011_040"}, {73, "Ps0011_050"},
  {74, "Ps0012_000"}, {75, "Ps0012_010"}, {76, "Ps0012_020"}, {77, "Ps0012_030"}, {78, "Ps0012_040"},
  {79, "Ps0012_050"}, {80, "Ps0013_000"}, {81, "Ps0013_010"}, {82, "Ps0013_020"}, {83, "Ps0013_030"},
  {84, "Ps0013_040"}, {85, "Ps0013_050"}, {86, "Ps0013_060"}, {87, "Ps0014_000"}, {88, "Ps0014_010"},
  {89, "Ps0015_000"}, {90, "Ps0015_010"}, {91, "Ps0021_000"}, {92, "Ps0021_010"}, {93, "Ps0021_020"},
  {94, "Ps0021_030"}, {95, "Ps0021_040"}, {96, "Ps0021_050"}, {97, "Ps0021_060"}, {98, "Ps0021_070"},
  {99, "Ps0021_080"}, {100, "Ps0021_090"}, {101, "Ps0022_000"}, {102, "Ps0022_010"}, {103, "Ps0022_020"},
  {104, "Ps0022_030"}, {105, "Ps0022_040"}, {106, "Ps0022_050"}, {107, "Ps0022_060"}, {108, "Ps0022_070"},
  {109, "Ps0022_080"}, {110, "Ps0022_090"}, {111, "Ps0022_100"}, {112, "Ps0023_000"}, {113, "Ps0023_010"},
  {114, "Ps0023_020"}, {115, "Ps0023_030"}, {116, "Ps0023_040"}, {117, "Ps0023_050"}, {118, "Ps0024_000"},
  {119, "Ps0024_010"}, {120, "Ps0024_020"}, {121, "Ps0024_030"}, {122, "Ps0025_000"}, {123, "Ps0025_010"},
  {124, "Ps0031_000"}, {125, "Ps0031_010"}, {126, "Ps0031_020"}, {127, "Ps0031_030"}, {128, "Ps1005_010"},
  {129, "Ps0031_040"}, {130, "Ps0032_000"}, {131, "Ps0034_000"}, {132, "Ps0034_010"}, {133, "Ps0034_020"},
  {134, "Ps0035_000"}, {135, "Ps0035_010"}, {136, "Ps0035_020"}, {137, "Ps0035_030"}, {138, "Ps0041_000"},
  {139, "Ps0041_010"}, {140, "Ps0041_020"}, {141, "Ps0042_000"}, {142, "Ps0042_010"}, {143, "Ps0044_000"},
  {144, "Ps0044_010"}, {145, "Ps0044_020"}, {146, "Ps0045_000"}, {147, "Ps0051_000"}, {148, "Ps0051_010"},
  {149, "Ps0051_020"}, {150, "Ps0051_030"}, {151, "Ps0051_040"}, {152, "Ps0051_050"}, {153, "Ps0051_060"},
  {154, "Ps0051_070"}, {155, "Ps0051_080"}, {156, "Ps0052_000"}, {157, "Ps0052_010"}, {158, "Ps0052_020"},
  {159, "Ps0052_030"}, {160, "Ps0053_000"}, {161, "Ps0053_010"}, {162, "Ps0053_020"}, {163, "Ps0053_030"},
  {164, "Ps0053_040"}, {165, "Ps0054_000"}, {166, "Ps0054_010"}, {167, "Ps0054_020"}, {168, "Ps0054_030"},
  {169, "Ps0054_040"}, {170, "Ps0054_050"}, {171, "Ps0055_000"}, {172, "Ps0055_010"}, {173, "Ps0055_020"},
  {174, "Ps0061_000"}, {175, "Ps0061_010"}, {176, "Ps0061_020"}, {177, "Ps0061_030"}, {178, "Ps0061_040"},
  {179, "Ps0062_000"}, {180, "Ps0062_010"}, {181, "Ps0062_020"}, {182, "Ps0062_030"}, {183, "Ps1002_010"},
  {184, "Ps0064_000"}, {185, "Ps0064_010"}, {186, "Ps0065_000"}, {187, "Ps0065_010"}, {188, "Ps0065_020"},
  {189, "Ps0071_000"}, {190, "Ps0071_010"}, {191, "Ps0071_020"}, {192, "Ps0072_000"}, {194, "Ps0072_010"},
  {195, "Ps0081_000"}, {196, "Ps0081_010"}, {197, "Ps0081_020"}, {198, "Ps0081_030"}, {199, "Ps0081_040"},
  {200, "Ps0081_050"}, {201, "Ps0082_000"}, {202, "Ps0082_010"}, {203, "Ps0082_020"}, {204, "Ps0083_000"},
  {205, "Ps0083_010"}, {206, "Ps0084_000"}, {207, "Ps0085_000"}, {208, "Ps0085_010"}, {221, "Ps2001_020"},
  {222, "Ps2001_030"}, {223, "Ps2001_010"}, {232, "Ps0023_050"}, {233, "Ps0022_070"}, {234, "Ps0035_010"},
  {235, "Ps0013_010"}, {236, "Ps0064_000"}, {237, "Ps0001_110"}, {238, "Ps0044_020"}, {239, "Ps0061_020"},
  {240, "Ps0052_000"}, {241, "Ps1002_020"}, {242, "Ps1002_030"}, {243, "Ps1002_040"}, {244, "Ps1002_050"},
  {245, "Ps1002_070"}, {246, "Ps1002_080"}, {247, "Ps1001_090"}, {248, "Ps0021_040"}, {249, "Ps0011_030"},
  {250, "Ps0005_010"}, {251, "Ps0023_030"}, {252, "Ps0031_010"}, {253, "Ps5001_010"}, {254, "Ps0061_010"},
  {255, "Ps5002_010"}, {256, "Ps0085_010"}, {300, "Ps5001_010"}, {301, "Ps5001_020"}, {302, "Ps5001_030"},
  {303, "Ps5001_040"}, {304, "Ps5001_050"}, {305, "Ps5001_060"}, {306, "Ps5001_070"}, {307, "Ps5001_080"},
  {308, "Ps5001_090"}, {309, "Ps5002_010"}, {310, "Ps5002_020"}, {311, "Ps5002_030"}, {312, "Ps5002_040"},
  {313, "Ps5002_050"}, {314, "Ps5002_060"}, {315, "Ps5002_070"}, {316, "Ps5002_080"}, {317, "Ps5002_090"},
  {318, "Ps5003_010"}, {319, "Ps5003_020"}, {320, "Ps5003_030"},
};
const Use kEnemies[] = {
  {1, "Em0011_000"}, {2, "Em0011_001"}, {3, "Em0011_002"}, {4, "Em0011_003"}, {5, "Em0012_000"}, {6, "Em0012_001"},
  {7, "Em0012_002"}, {8, "Em0012_003"}, {9, "Em0013_000"}, {10, "Em0013_001"}, {11, "Em0013_002"},
  {12, "Em0013_003"}, {13, "Em0001_000"}, {18, "Em0021_000"}, {19, "Em0021_001"}, {20, "Em0021_002"},
  {21, "Em0021_003"}, {22, "Em0022_000"}, {23, "Em0022_001"}, {24, "Em0022_002"}, {25, "Em0022_003"},
  {26, "Em0023_000"}, {27, "Em0023_001"}, {28, "Em0023_002"}, {29, "Em0023_003"}, {30, "Em0001_001"},
  {35, "Em0031_000"}, {36, "Em0031_001"}, {37, "Em0031_002"}, {38, "Em0031_003"}, {39, "Em0032_000"},
  {40, "Em0032_001"}, {41, "Em0032_002"}, {42, "Em0032_003"}, {43, "Em0033_000"}, {44, "Em0033_001"},
  {45, "Em0033_002"}, {46, "Em0033_003"}, {47, "Em0001_002"}, {52, "Em0041_000"}, {53, "Em0041_001"},
  {54, "Em0041_002"}, {55, "Em0041_003"}, {56, "Em0042_000"}, {57, "Em0042_001"}, {58, "Em0042_002"},
  {59, "Em0042_003"}, {60, "Em0043_000"}, {61, "Em0043_001"}, {62, "Em0043_002"}, {63, "Em0043_003"},
  {64, "Em0001_003"}, {69, "Em0051_000"}, {70, "Em0051_001"}, {71, "Em0051_002"}, {72, "Em0051_003"},
  {73, "Em0052_000"}, {74, "Em0052_001"}, {75, "Em0052_002"}, {76, "Em0052_003"}, {77, "Em0053_000"},
  {78, "Em0053_001"}, {79, "Em0053_002"}, {80, "Em0053_003"}, {81, "Em0001_004"}, {84, "Em0084_000"},
  {86, "Em0061_000"}, {87, "Em0061_001"}, {88, "Em0061_002"}, {89, "Em0061_003"}, {90, "Em0062_000"},
  {91, "Em0062_001"}, {92, "Em0062_002"}, {93, "Em0062_003"}, {94, "Em0063_000"}, {95, "Em0063_001"},
  {96, "Em0063_002"}, {97, "Em0063_003"}, {98, "Em0001_005"}, {103, "Em0071_000"}, {104, "Em0071_001"},
  {105, "Em0071_002"}, {106, "Em0071_003"}, {107, "Em0072_000"}, {108, "Em0072_001"}, {109, "Em0072_002"},
  {110, "Em0072_003"}, {111, "Em0073_000"}, {112, "Em0073_001"}, {113, "Em0073_002"}, {114, "Em0073_003"},
  {115, "Em0001_006"}, {120, "Em0111_000"}, {121, "Em0111_001"}, {122, "Em0111_002"}, {123, "Em0111_003"},
  {124, "Em0112_000"}, {125, "Em0112_001"}, {126, "Em0112_002"}, {127, "Em0112_003"}, {128, "Em0113_000"},
  {129, "Em0113_001"}, {130, "Em0113_002"}, {131, "Em0113_003"}, {132, "Em0001_010"}, {137, "Em0091_000"},
  {138, "Em0091_001"}, {139, "Em0091_002"}, {140, "Em0091_003"}, {141, "Em0092_000"}, {142, "Em0092_001"},
  {143, "Em0092_002"}, {144, "Em0092_003"}, {145, "Em0093_000"}, {146, "Em0093_001"}, {147, "Em0093_002"},
  {148, "Em0093_003"}, {149, "Em0001_008"}, {154, "Em0101_000"}, {155, "Em0101_001"}, {156, "Em0102_000"},
  {157, "Em0102_001"}, {158, "Em0103_000"}, {159, "Em0103_001"}, {160, "Em0104_000"}, {161, "Em0104_001"},
  {162, "Em0105_000"}, {163, "Em0105_001"}, {164, "Em0105_002"}, {165, "Em0105_003"}, {166, "Em0001_009"},
  {171, "Em0081_000"}, {172, "Em0081_001"}, {173, "Em0081_002"}, {174, "Em0081_003"}, {175, "Em0082_002"},
  {176, "Em0082_000"}, {177, "Em0082_001"}, {178, "Em0082_003"}, {179, "Em0083_000"}, {180, "Em0083_001"},
  {181, "Em0083_002"}, {182, "Em0083_003"}, {183, "Em0001_007"}, {188, "Em0121_000"}, {189, "Em0121_001"},
  {190, "Em0121_002"}, {191, "Em0121_003"}, {192, "Em0122_000"}, {193, "Em0122_001"}, {194, "Em0122_002"},
  {195, "Em0122_003"}, {196, "Em0123_000"}, {197, "Em0123_001"}, {198, "Em0123_002"}, {199, "Em0123_003"},
  {200, "Em0001_011"}, {205, "Em0011_004"}, {206, "Em0011_004"}, {207, "Em0011_004"}, {208, "Em0011_004"},
  {209, "Em0011_004"}, {210, "Em0011_004"}, {211, "Em0011_004"}, {212, "Em0011_004"}, {213, "Em0011_004"},
  {214, "Em0011_004"}, {215, "Em0011_004"}, {220, "Em0131_000"}, {221, "Em0001_000"}, {222, "Em0091_002"},
  {223, "Em0071_000"}, {224, "Em0011_000"}, {225, "Em0072_000"}, {226, "Em0082_000"}, {227, "Em0083_001"},
  {228, "Em0091_001"}, {229, "Em0031_000"}, {230, "Em0032_003"}, {231, "Em0052_001"}, {232, "Em0061_001"},
  {233, "Em0042_003"}, {234, "Em0062_000"}, {235, "Em0071_000"}, {236, "Em0022_000"}, {237, "Em0011_001"},
  {238, "Em0112_000"}, {239, "Em0012_000"}, {240, "Em0001_000"}, {241, "Em0021_000"}, {242, "Em0001_001"},
  {243, "Em0013_000"}, {244, "Em0012_001"}, {245, "Em0033_002"}, {246, "Em0082_001"}, {247, "Em0072_000"},
  {248, "Em0122_000"}, {249, "Em0101_001"}, {250, "Em0051_001"}, {251, "Em0043_003"}, {252, "Em0121_000"},
  {253, "Em0022_000"}, {254, "Em0093_002"}, {255, "Em0112_000"}, {256, "Em0112_001"}, {257, "Em0105_001"},
  {258, "Em0063_003"}, {259, "Em0063_000"}, {260, "Em0013_001"}, {261, "Em0011_001"}, {262, "Em0023_000"},
  {263, "Em0021_003"}, {264, "Em0052_003"}, {265, "Em0042_001"}, {266, "Em0033_000"}, {267, "Em0001_000"},
  {268, "Em0032_002"}, {269, "Em0105_002"}, {270, "Em0073_000"}, {271, "Em0033_001"}, {272, "Em0012_003"},
  {273, "Em0122_001"}, {274, "Em0011_002"}, {275, "Em0011_003"}, {276, "Em0043_001"}, {277, "Em0081_000"},
  {278, "Em0113_000"}, {279, "Em0052_002"}, {280, "Em0022_001"}, {281, "Em0071_003"}, {282, "Em0042_002"},
  {283, "Em0111_000"}, {284, "Em0062_001"}, {285, "Em0082_003"}, {286, "Em0073_001"}, {287, "Em0023_002"},
  {288, "Em0053_002"}, {289, "Em0113_001"}, {290, "Em0111_002"}, {291, "Em0073_003"}, {292, "Em0093_000"},
  {293, "Em0092_003"}, {294, "Em0103_001"}, {295, "Em0122_001"}, {296, "Em0001_000"}, {297, "Em0021_000"},
  {300, "Em0061_000"}, {301, "Em0001_000"}, {302, "Em0013_000"}, {303, "Em0073_000"}, {304, "Em0061_000"},
  {305, "Em0013_000"}, {306, "Em0021_003"}, {307, "Em0043_000"}, {308, "Em0043_003"}, {309, "Em0072_003"},
  {310, "Em0101_000"}, {311, "Em0021_000"}, {312, "Em0101_001"}, {313, "Em0022_002"}, {314, "Em0102_001"},
  {315, "Em0021_000"}, {316, "Em0022_002"}, {317, "Em0062_001"}, {318, "Em0052_001"}, {319, "Em0063_003"},
  {320, "Em0023_003"}, {321, "Em0121_002"}, {322, "Em0011_004"}, {323, "Em0011_003"}, {324, "Em0011_002"},
  {325, "Em0011_001"}, {326, "Em0011_000"}, {327, "Em0033_003"}, {328, "Em0083_002"}, {329, "Em0022_003"},
  {330, "Em0092_001"}, {331, "Em0042_003"}, {332, "Em0032_003"}, {333, "Em0062_003"}, {334, "Em0001_011"},
  {335, "Em0082_003"}, {336, "Em0112_002"}, {337, "Em0112_000"}, {338, "Em0112_001"}, {339, "Em0112_003"},
  {340, "Em0073_003"}, {341, "Em0081_003"}, {342, "Em0081_002"}, {343, "Em0081_001"}, {344, "Em0081_000"},
  {345, "Em0084_000"}, {348, "Em0001_005"}, {349, "Em0001_000"}, {350, "Human_Takaya"}, {351, "Human_Jin"},
  {352, "Human_Chidori"}, {353, "Human_Jin"}, {354, "Human_Takaya"}, {355, "Em0084_000"}, {356, "Human_Takaya"},
  {364, "Em0601_000"}, {369, "Em0021_000"}, {370, "Em0511_000"}, {371, "Em0021_000"}, {372, "Em0021_000"},
  {373, "Em0521_000"}, {376, "Em0522_000"}, {380, "Em0531_000"}, {381, "Em0532_000"}, {382, "Em0541_000"},
  {383, "Em0542_000"}, {384, "Em0543_000"}, {385, "Em0551_000"}, {386, "Em0561_000"}, {387, "Em0562_000"},
  {388, "Em0571_000"}, {389, "Em0572_000"}, {390, "Em0572_000"}, {391, "Em0572_000"}, {392, "Em0572_000"},
  {393, "Em0572_000"}, {394, "Em0572_000"}, {395, "Em0572_000"}, {396, "Em0581_000"}, {410, "Em0582_000"},
  {430, "Em0083_003"}, {431, "Em0061_003"}, {432, "Em0081_002"}, {433, "Em0081_001"}, {434, "Em0081_000"},
  {435, "Em0104_001"}, {436, "Em0121_003"}, {437, "Em0082_002"}, {438, "Em0122_002"}, {439, "Em0105_003"},
  {440, "Em0043_003"}, {441, "Em0021_002"}, {442, "Em0011_003"}, {443, "Em0112_002"}, {444, "Em0093_003"},
  {445, "Em0062_003"}, {446, "Em0113_003"}, {447, "Em0053_003"}, {448, "Em0123_003"}, {449, "Em0122_003"},
  {450, "Em0033_003"}, {451, "Em0081_003"}, {452, "Em0011_004"}, {453, "Em0011_004"}, {454, "Em0011_004"},
  {455, "Em0011_004"}, {456, "Em0011_004"}, {457, "Em0011_004"}, {458, "Em0011_004"}, {459, "Em0011_004"},
  {460, "Em0011_004"}, {461, "Em0011_004"}, {462, "Em0062_004"}, {463, "Em0082_004"}, {464, "Em0001_007"},
  {465, "Em0123_004"}, {466, "Em0041_004"}, {467, "Em0083_004"}, {468, "Em0063_004"}, {469, "Em0032_004"},
  {470, "Em0073_004"}, {471, "Em0023_004"}, {472, "Em0121_004"}, {473, "Em0092_004"}, {474, "Em0113_004"},
  {475, "Em0073_005"}, {476, "Em0052_004"}, {477, "Em0123_005"}, {478, "Em0051_001"}, {479, "Em0053_001"},
  {480, "Em0042_000"}, {481, "Em0113_002"}, {482, "Em0063_003"}, {483, "Em0104_001"}, {484, "Em0105_003"},
  {485, "Em0001_004"}, {500, "Human_Elizabeth"}, {520, "Em0023_000"}, {521, "Em0105_000"}, {522, "Em0103_000"},
  {523, "Em0033_000"}, {524, "Em0092_000"}, {525, "Em0053_001"}, {526, "Em0083_003"}, {527, "Em0031_003"},
  {528, "Em0123_003"}, {529, "Em0111_002"}, {530, "Em0121_001"}, {531, "Em0013_003"}, {532, "Em0051_003"},
  {533, "Em0041_003"}, {534, "Em0043_002"}, {535, "Em0112_002"}, {536, "Em0105_003"}, {537, "Em0113_003"},
  {538, "Em0072_003"}, {539, "Em0023_003"}, {540, "Em0092_003"}, {541, "Em0052_003"}, {542, "Em0104_001"},
  {543, "Em0042_003"},
};
