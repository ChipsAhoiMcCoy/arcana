// How the Personas and Shadows look (included by look_text.cpp), written from renders of the game's own 3D models
// and textures (research tools, 2026-11-17). Model keys: Ps<group>_<variant> a Persona's, Em<family>_<variant> a
// Shadow's (BP_Em<family>_<variant>; siblings of one family are recolours), Human_<name> a person fought.
const Model kModels[] = {
  {"Em0001_000",  // 検証用のマーヤ
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Pinned to the hump by little silver bolts is a teal-blue mask of "
        "a long, solemn face: round black eyeholes, a straight nose, a small downturned mouth and the numeral I "
        "on its brow. The lowest of the Shadows, barely more than a stain, it is all reaching, hands open and "
        "lifted as if trying to climb out of the floor."},
  {"Em0001_001",  // Merciless Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Across the hump, where eyes would be, sits a small magenta "
        "half-mask flaring out at the sides like butterfly wings, with narrow, heavy-lidded eye slits and the "
        "numeral II at one edge. Below it the ooze is blank. Coy behind its party mask, it reaches upward with "
        "both clawed hands open, half beckoning, half grasping."},
  {"Em0001_002",  // Frivolous Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. On the hump sits a cream-white mask shaped like a crown, three "
        "sharp points standing up along its top, edged in thin gold, the numeral III on its brow and its eyes "
        "closed in two calm, curved lines. Serene and pleased with itself, it lifts its hands as if the floor "
        "were a throne room."},
  {"Em0001_003",  // Haughty Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is lavender-purple and showy, marked IV: shadowed "
        "eyeholes under a fan of spiked prongs that rays out above like a crown of thorns, and two long curved "
        "prongs sweeping down past the chin like tusks. Puffed up behind that thorny headpiece, it looks down its "
        "nose from a body that is barely more than a spill."},
  {"Em0001_004",  // ?
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is a steel-blue oval, wide at the brow and narrowing to "
        "a point at the chin, marked V, with two small slanted diamond eyeholes and a larger diamond hole for a "
        "mouth, hanging open like a yawn. Dull and slack-jawed, it raises its claws as if out of habit rather "
        "than malice."},
  {"Em0001_005",  // ?
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is a rosy pink face marked VI, the brows tilted up in a "
        "pitiful slant over drooping, half-closed eyes and a small mouth turned down in a sorrowful pout. It "
        "looks forlorn and pleading, though the clawed hands raised on either side of that sad little face "
        "suggest the sorrow is only bait."},
  {"Em0001_006",  // Ill-Fated Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is a bright yellow plate shaped like a knight's shield, "
        "faceless but for two heavy black bars bent down at their inner ends like a scowling brow, with the "
        "numeral VII small at the top. Blank and grim behind that warning-yellow shield, it has the air of "
        "something that brings bad luck with it."},
  {"Em0001_007",  // ?
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is a deep royal-blue face, smooth and serene like a "
        "statue's, with almond eyeholes, a fine straight nose and full closed lips, a small white diamond "
        "outlined on the brow beside the numeral XI. Calm and almost beautiful above those grasping hands, it "
        "gazes out with a composure that feels hungry rather than kind."},
  {"Em0001_008",  // Desirous Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is burnt orange and round, marked IX, with a single "
        "dark hole at its centre ringed by a raised rim like one wide staring eye, and below it a jaw of long "
        "grooves like the teeth of a skull. Fixed on whatever is in front of it, that one empty eye stares with a "
        "flat, wanting hunger."},
  {"Em0001_009",  // Imprudent Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is a glossy emerald-green oval marked X, its two eyes "
        "black spirals stacked one above the other and joined by a looping line, over a huge black crescent grin "
        "that runs almost from edge to edge. Dizzy-eyed and grinning wide, it looks ready to throw itself at "
        "anything without a thought."},
  {"Em0001_010",  // Bigoted Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is a pale sage-green shield with a pointed chin and no "
        "face at all, only a bold black cross running down and across it, arrow-pointed at top and bottom, with "
        "the numeral VIII above. Blank and rigid behind that cross, it holds its claws up with the stiff, "
        "unbending air of a zealot."},
  {"Em0001_011",  // Devious Maya
        "A puddle of black ooze spread wide across the floor, a low hump rising at its centre and two long, thin "
        "arms reaching straight up out of it, knobbly as dead branches, each hand splayed with needle-tipped "
        "fingers and a hooked thorn for a thumb. Its mask is a soft slate-grey face, round and puffy like a "
        "sleeper's, with a creased brow, heavy eyelids shut, a broad flat nose and the numeral XII low on the "
        "cheeks where a mouth would be. Drowsy and unreadable, it lifts its clawed hands as if scheming in its "
        "sleep."},
  {"Em0011_000",  // White Hand
        "A giant gloved hand standing upside down on its four fingertips like legs, its thumb jutting out to one "
        "side, and rising from its wrist a short neck and a black egg-shaped head. The glove is crisp white, and "
        "down the back of the hand runs a cream tuxedo shirtfront, finely pleated, with three dark buttons, a "
        "little red bow tie at the collar. Bolted over the face with silver spikes is a long teal-blue mask "
        "marked I, round black eyeholes, a long straight nose and a small downturned mouth. Neat and solemn as a "
        "stage magician's prop, it is a conjuring trick walking about on its own."},
  {"Em0011_001",  // Pink Hand
        "A giant gloved hand standing upside down on its four fingertips like legs, its thumb jutting out to one "
        "side, a short neck and a black egg-shaped head rising from the wrist. This glove is fluffy pink knitwear "
        "patterned with white leafy flowers, with a frilled pink lace cuff standing up around the neck over a "
        "gaudy gold-filigree necklace crusted with pearls and studs, and on one finger a gold ring set with a "
        "huge faceted aqua gem. Bolted over the face with silver spikes is the long teal-blue mask marked I, "
        "round-eyed and glum. Frilly and heavy with jewels, it is dressed to be noticed."},
  {"Em0011_002",  // Black Hand
        "A giant gloved hand standing upside down on its four fingertips like legs, its thumb jutting out to one "
        "side, a short neck and a black egg-shaped head rising from the wrist. This glove is glossy black "
        "leather, a spiked metal collar ringing the neck, and down the back of the hand runs a grey leather panel "
        "edged with silver studs and fastened by three buttons shaped like tiny skulls. Bolted over the face with "
        "silver spikes is the long teal-blue mask marked I, round black eyeholes over a glum mouth. All leather, "
        "studs and skulls, it stands hard and menacing where its siblings are prim."},
  {"Em0011_003",  // Foot Soldier
        "A giant gloved hand standing upside down on its four fingertips like legs, its thumb jutting out to one "
        "side, a short neck and an egg-shaped head rising from the wrist, glove and head alike a pale silvery "
        "white. A tall, tightly pleated ivory ruff stands around the neck above a white lace jabot, and down the "
        "back of the hand runs a royal-blue panel embroidered with gold scrollwork and crossed by three gold "
        "braids, like a courtier's doublet. Bolted over the face with silver spikes is the long teal-blue mask "
        "marked I, round-eyed and glum. Stiff and correct, it carries itself like a footman of some old royal "
        "court."},
  {"Em0011_004",  // Final Checkmate
        "A giant gloved hand standing upside down on its four fingertips like legs, its thumb jutting out to one "
        "side, a short neck and an egg-shaped head rising from the wrist, all of it gleaming gold. Red piping "
        "traces a waistcoat front down the back of the hand, closed with three round red buttons, a small red bow "
        "tie sits at the neck, and every fingertip ends in a glossy red-painted nail. Bolted over the face with "
        "silver spikes is the long teal-blue mask marked I, round black eyeholes over a glum mouth. Polished and "
        "gaudy from head to fingertips, it looks like a treasure that has learned to walk."},
  {"Em0012_000",  // Laughing Table
        "A small conjuror's table come to life, with the four tools of the tarot magician floating in a tower "
        "above it. The table stands on thin dark legs that splay out into curling feet, draped in a dusty "
        "grey-brown cloth with a faint cobweb pattern and a frayed, striped hem, and bolted to its front is a "
        "long teal-blue mask marked I, round-eyed and glum. Above it hang a plain pewter goblet, a single-edged "
        "steel blade standing point-up out of it, a flat dark disc, and on top a gnarled wooden club with a lumpy "
        "knob. Shabby and cobwebbed, it has the air of a street conjuror's act gone sour."},
  {"Em0012_001",  // Grievous Table
        "A small conjuror's table come to life, with the four tools of the tarot magician floating in a tower "
        "above it. The table stands on thin dark legs that splay into curling feet, draped in a harlequin cloth "
        "of red and black diamonds hemmed in gold, a long teal-blue mask marked I bolted to its front. Above it "
        "hang a black goblet ringed with red flame-shaped points, a red-hilted sword with a blade of glowing "
        "amber crystal, a flat red disc, and on top a gnarled wooden crook curled like a question mark around a "
        "red orb. Gaudy as a carnival booth, it still wears the same long, mournful face."},
  {"Em0012_002",  // Angry Table
        "A small conjuror's table come to life, with the four tools of the tarot magician floating in a tower "
        "above it. The table stands on thin dark legs that splay into curling feet, draped in a cloth split down "
        "the middle, red and royal blue in front, yellow and black behind, with a heavy gold fringe, a long "
        "teal-blue mask marked I bolted to its front. Above it hang a tan goblet banded with dark triangles, a "
        "straight steel sword with a gold crossguard, a flat gold disc, and on top a gnarled wooden crook shod in "
        "silver. Loud in clashing colours, it still wears a glum face."},
  {"Em0012_003",  // Terminal Table
        "A small conjuror's table come to life, with the four tools of the tarot magician floating in a tower "
        "above it. The table stands on pale silver legs that splay into curling feet, draped in a white lace "
        "cloth, a long teal-blue mask marked I bolted to its front. Above it hang a dark blue-black goblet shaped "
        "like a wine glass, a slender silver rapier with an ornate swept hilt rising from it, a thin silver disc, "
        "and on top a slim navy rod banded in gold, crowned with a small gold cross and ending in a spike. All "
        "white, silver and navy, it looks laid out for a wake."},
  {"Em0013_000",  // Magical Magus
        "A tall robed sorcerer in a jester's hood, standing before a vast black shape that rises into two "
        "gigantic hands, their long fingers spread wide on either side like a curtain thrown open. Its long robe "
        "falls in bold black and white stripes, the flared sleeves trimmed in studded navy, small white hands "
        "held open at its sides. A studded navy collar meets at a round gold cross brooch, and a navy sash hangs "
        "to the hem. A white two-pointed hood curls down into horns, a gold ring at each tip, around the long "
        "teal-blue mask marked I. Grand and stagey, it presents itself like a ringmaster of dark tricks."},
  {"Em0013_001",  // Venomous Magus
        "A tall robed sorcerer in a jester's hood, standing before a vast black shape that rises into two "
        "gigantic hands, their long fingers spread wide on either side like a curtain thrown open. Its robe is "
        "candy-pink scattered with purple stars, the wide sleeves lined in orange-gold, pink hands open at its "
        "sides. A gold collar set with green gems meets at a round brooch of teal stones, and a pink sash hangs "
        "to the hem. A starry pink two-pointed hood curls down into horns, a gold ring at each tip, around the "
        "long teal-blue mask marked I. Sweet as a party conjuror, it stands before those vast black hands."},
  {"Em0013_002",  // Prime Magus
        "A tall robed sorcerer in a jester's hood, standing before a vast black shape that rises into two "
        "gigantic hands, their long fingers spread wide on either side like a curtain thrown open. Its robe is "
        "deep crimson striped in darker red, the wide sleeves cuffed in gold, cream hands open at its sides. A "
        "gold collar set with purple stones meets at a jewelled brooch, and a gold band of purple gems runs to "
        "the hem. A crimson two-pointed hood curls down into horns, a gold ring at each tip, around the long "
        "teal-blue mask marked I. Rich and solemn in blood red, it stands like a high priest."},
  {"Em0013_003",  // Grand Magus
        "A tall robed sorcerer in a jester's hood, standing before two gigantic hands that spread their long "
        "fingers wide on either side, but here they are pale and ghostly, mint fading to sky blue, and the mass "
        "beneath them blushes lavender and pink toward the floor. Its robe shimmers in stripes of buttery yellow "
        "and aqua, the wide sleeves trimmed in silver, aqua hands open at its sides, a silver collar studded with "
        "teal. A mint-and-yellow two-pointed hood curls down into horns, a silver ring at each tip, around the "
        "long teal-blue mask marked I. Iridescent and weightless, it seems more vision than conjuror."},
  {"Em0021_000",  // Loathsome Tiara
        "A floating head with no body, only a long curtain of wavy charcoal-black hair pouring down beneath it "
        "and splitting into ragged, tentacle-like points. The dark grey face is blank but for a rose-pink domino "
        "mask cut like butterfly wings, edged in silver, a small numeral II scratched beside one eye. Above it "
        "towers a headdress twice its height in dusky rose-pink: two huge open loops like the finger holes of a "
        "pair of scissors, flanking an almond-shaped panel of olive gold with nested ridges, all set on a spiked "
        "gold coronet studded with rivets. All crown and hair, it drifts like a queen reduced to her regalia."},
  {"Em0021_001",  // Grieving Tiara
        "A floating head with no body, only a long curtain of wavy charcoal-black hair pouring down beneath it "
        "and splitting into ragged, tentacle-like points. The dark grey face is blank but for a rose-pink domino "
        "mask cut like butterfly wings, edged in silver, a small numeral II scratched beside one eye. Above it "
        "towers a headdress twice its height in polished silver: two huge open loops like the finger holes of a "
        "pair of scissors, flanking an almond-shaped panel of deep glossy teal, on a silver coronet whose points "
        "are edged in bright teal. Cold and gleaming, it hovers like a mourner crowned in moonlight."},
  {"Em0021_002",  // Mage Soldier
        "A floating head with no body, only a long curtain of wavy charcoal-black hair pouring down beneath it "
        "and splitting into ragged, tentacle-like points. The dark grey face is blank but for a rose-pink domino "
        "mask cut like butterfly wings, edged in silver, a small numeral II scratched beside one eye. Above it "
        "towers a headdress twice its height in royal violet piped with fine gold lines: two huge open loops like "
        "the finger holes of a pair of scissors, flanking an almond-shaped panel of dull pewter grey, set on a "
        "spiked gold coronet. Regal in violet and gold, it hangs as still as a crown on display."},
  {"Em0021_003",  // Shouting Tiara
        "A floating head with no body, only a long curtain of wavy pale lilac-grey hair pouring down beneath it "
        "and splitting into ragged, tentacle-like points, the face itself a ghostly lavender grey. It is blank "
        "but for a rose-pink domino mask cut like butterfly wings, edged in silver, a small numeral II scratched "
        "beside one eye. Above it towers a headdress twice its height in creamy bone-beige: two huge open loops "
        "like the finger holes of a pair of scissors, flanking an almond-shaped panel of deep wine red, on a "
        "crimson coronet studded with silver. Pale as a spectre and trimmed in blood red, it drifts like a "
        "crowned ghost."},
  {"Em0022_000",  // Tome of Atrophy
        "A floating head with no body, a long mane of wavy indigo-violet hair hanging beneath it in ragged, "
        "tentacle-like locks. The dark grey face is blank but for a rose-pink butterfly-wing domino mask edged in "
        "silver. On its head sits a teal-green crown with gold leaf-shaped points, and rising from it a tall "
        "arching hoop of riveted bronze topped with a spearhead finial, framing a thick holy book standing "
        "upright: brown leather, an olive-green panel on its cover and a raised cross within. Head below and "
        "scripture above, it drifts like a grim relic carried in a procession."},
  {"Em0022_001",  // Tome of Persecution
        "A floating head with no body, a long mane of wavy candy-pink hair hanging beneath it in ragged, "
        "tentacle-like locks that deepen to magenta at the tips. The dark grey face is blank but for a rose-pink "
        "butterfly-wing domino mask edged in silver. On its head sits a pale blue crown with leafy green points, "
        "and rising from it a tall arching hoop of riveted moss-green metal topped with a silver finial, framing "
        "a thick holy book standing upright: a mauve-pink tome with a sky-blue panel and a bright gold cross on "
        "its cover. Sugary in colour, it still holds its scripture high and stiff above a blank, masked face."},
  {"Em0022_002",  // Silent Book
        "A floating head with no body, a long mane of wavy dark navy-blue hair hanging beneath it in ragged, "
        "tentacle-like locks. The dark grey face is blank but for a rose-pink butterfly-wing domino mask edged in "
        "silver. On its head sits a steel-blue crown set with small red stones, and rising from it a tall arching "
        "hoop of riveted steel-blue metal topped with a spearhead finial, framing a thick holy book standing "
        "upright: charcoal-black, a blood-red panel on its cover and a darker red cross within. Sombre and "
        "severe, it carries the look of a forbidden book that should stay shut."},
  {"Em0022_003",  // Morbid Book
        "A floating head with no body, a long mane of wavy pale cream-blonde hair hanging beneath it in ragged, "
        "tentacle-like locks, the face a light grey. It is blank but for a rose-pink butterfly-wing domino mask "
        "edged in silver. On its head sits a teal and navy crown with gold points, and rising from it a tall "
        "arching hoop of riveted brass topped with a spearhead finial, framing a thick holy book standing "
        "upright: silvery white, a gold panel on its cover and a raised gold cross within. Bright and gilded, it "
        "hangs in the air like a sacred relic carried by a pale, blank-faced keeper."},
  {"Em0023_000",  // Tranquil Idol
        "A slender, faceless woman of smooth dark slate grey, sitting cross-legged in meditation on a floating "
        "stepped pedestal of dark stone that narrows to a point beneath her like an upside-down pyramid. Her "
        "long, thin arms reach down to either side, hands resting on the pedestal's edge. She is bare and smooth "
        "as a statue, with a woman's breasts and narrow waist, a rose-pink butterfly-wing domino mask over her "
        "eyes. A crimson veil edged in gold falls from her head like a hood and spreads into wide wings across "
        "the stone, above a green band of bronze studs. She sits utterly still, a shrine's idol waiting for "
        "worship."},
  {"Em0023_001",  // Liberating Idol
        "A slender, faceless woman of smooth dusky grey, sitting cross-legged in meditation on a floating stepped "
        "pedestal of magenta stone that narrows to a point beneath her. Her long, thin arms reach down, hands "
        "resting on its edge. She is bare and smooth as a statue, with a woman's breasts and a rose-pink "
        "butterfly-wing domino mask, and a pale sea-green veil falls from her head and spreads wide across the "
        "stone. Behind her rises a tall magenta throne-back with an indigo panel, crowned by a great spoked wheel "
        "with a golden sunburst at its hub. Calm and unknowable, she sits beneath her great wheel like an oracle."},
  {"Em0023_002",  // Ruinous Idol
        "A slender, faceless woman of smooth charcoal grey, sitting cross-legged in meditation on a floating "
        "stepped pedestal of tarnished brass. Her long, thin arms reach down, hands resting on its edge. She is "
        "bare and smooth as a statue, with a woman's breasts and a rose-pink butterfly-wing domino mask, and a "
        "cream veil traced in gold spreads wide across the brass. Behind her rises a brass throne-back with a "
        "royal-blue panel, topped by two spoked wheels stacked in a blue oval, a crescent moon at the upper hub "
        "and a sunburst at the lower, a star on either side. Cold and cosmic, she sits enthroned beneath sun and "
        "moon."},
  {"Em0023_003",  // Vehement Idol
        "A slender, faceless woman of smooth icy pale blue, sitting cross-legged in meditation on a floating "
        "stepped pedestal of sea-green stone ringed with coloured jewels. Her long, thin arms reach down, hands "
        "resting on its edge. She is bare and smooth as a statue, with a woman's breasts and a rose-pink "
        "butterfly-wing domino mask, and a long peachy-blonde veil flows from her head like hair, blushing pink "
        "where it spreads across the stone. Behind her stands a pale blue throne-back with an olive-gold panel, "
        "crowned by a silvery full moon in navy rings, star-tipped rays bursting from it. Dreamy and moonlit, she "
        "sits like a goddess of the night sky."},
  {"Em0023_004",  // ?
        "A slender, faceless woman of smooth deep teal green, sitting cross-legged in meditation on a floating "
        "stepped pedestal of weathered bronze whose point breaks off into raw rock. Her long, thin arms reach "
        "down, hands resting on its edge. She is bare and smooth as a statue, with a woman's breasts and a "
        "rose-pink butterfly-wing domino mask, and a pale blue hood falls into a royal-blue veil edged in gold, "
        "spread wide across the stone. Behind her a bronze throne-back frames a silver tablet carved with script, "
        "ivy spilling over it, crowned by two stacked wheels of sun and moon. She looks like an idol forgotten in "
        "an overgrown temple."},
  {"Em0031_000",  // Lightning Eagle
        "A great raven-black bird of prey standing upright on long scaly legs with red-tipped talons, huge ragged "
        "wings spread wide and a long tail sweeping behind. Over its dark, beak-like face sits an ivory mask with "
        "serene closed eyes and a top cut into crown points, the numeral III on its brow and a small gold ring at "
        "one cheek. A white frilled ruff circles its throat, a tall scarlet heart-shaped collar rises behind its "
        "head, and its breast is wrapped in a smooth red bodice like a gown. Haughty and stately, it carries "
        "itself like a queen of hearts who hunts."},
  {"Em0031_001",  // Dark Eagle
        "A great raven-black bird of prey standing upright on long scaly legs with dark red talons, huge ragged "
        "wings spread wide and a long tail sweeping behind. Over its dark, beak-like face sits an ivory mask with "
        "serene closed eyes and a top cut into crown points, the numeral III on its brow and a small gold ring at "
        "one cheek. Behind its head rise two tall, slender violet blades like a hare's ears over a dark red ruff, "
        "and its breast is laced into a purple corset trimmed with red frills. Sleek and sinister, it holds "
        "itself like an empress of the night."},
  {"Em0031_002",  // Jupiter Eagle
        "A great black bird of prey with a faint green sheen, standing upright on long scaly legs with grey "
        "talons, huge ragged wings spread wide and a long tail sweeping behind. Over its dark, beak-like face "
        "sits an ivory mask with serene closed eyes and a top cut into crown points, the numeral III on its brow "
        "and a small gold ring at one cheek. Behind its head opens a huge round fan of grey-green metal ringed "
        "with rivet holes, over a pleated grey ruff, and its breast is armoured in a silver plated bodice. Steely "
        "and upright, it stands like a war queen in battle dress."},
  {"Em0031_003",  // Eternal Eagle
        "A great pale bird of prey standing upright on long legs, broad-winged, its feathers a soft greenish "
        "ivory that burn to rusty orange at the wingtips and along a long, sweeping tail, its talons turquoise. "
        "Behind its head rises a huge bubblegum-pink heart, like the standing collar of a court gown, and a pink "
        "bodice hugs its breast under a white pleated ruff. Its face is an ivory mask with serenely closed eyes, "
        "a tall crown-like point, the numeral III on its brow and a small gold ring at one cheek. Dressed for a "
        "royal wedding, it holds itself proud and dreamy, a bird in love with its own splendour."},
  {"Em0032_000",  // Creation Relic
        "A mother carved in warm, grain-streaked wood, seated upright on a tall throne of dark iron-grey stone, a "
        "small wooden child held against her chest in one arm while her other hand lifts a heavy iron ball before "
        "her. Her long hair falls over her shoulders from under a tall flat-topped hat, and her face is hidden by "
        "an ivory mask with closed eyes, a crown-like point and the numeral III on the brow. Beside the throne "
        "hang five long, slender iron spearheads in a row, all aimed ahead. A church Madonna at first glance, she "
        "sits calm and watchful, her blessing backed by blades."},
  {"Em0032_001",  // Constancy Relic
        "A mother carved as a weathered statue, seated upright on a tall throne of glossy black stone studded "
        "with small clear crystals down its back. Her robe and tall flat-topped hat are a mottled jade green like "
        "old bronze, her skin and flowing hair a cold blue-grey, and she cradles a small grey child against her "
        "chest while her other hand lifts a pale tan ball. An ivory mask with closed eyes, a crown-like point and "
        "the numeral III hides her face. Five long spearheads of glassy pale green hang in a row beside her, "
        "aimed ahead. Still and patient as a graveyard saint, she keeps her quiet, armed vigil."},
  {"Em0032_002",  // Heartless Relic
        "A mother carved as a statue, seated upright on a tall throne of glossy black stone set with small clear "
        "crystals down its back. Her robe and tall flat-topped hat are a deep navy blue, her skin and long, "
        "flowing hair a chalky pale grey, and a small grey child clings to her chest in one arm while her other "
        "hand lifts a dark grey ball. An ivory mask with closed eyes, a crown-like point and the numeral III "
        "hides her face. Five long, slender white-silver spearheads hang in a row beside her, aimed ahead. Cold "
        "and solemn in mourning blue, she sits like a saint keeping a deadly watch."},
  {"Em0032_003",  // Change Relic
        "A mother carved entirely from pale cream limestone, seated upright on a stone throne: her robe, her long "
        "hair, her tall flat-topped hat, the small child held to her chest and the throne all one weathered "
        "stone. Behind the throne bursts a great fan of flat stone rays, a sunburst crowned by one tall central "
        "spike that towers over her head. In her free hand she lifts a small golden ball, and her face is hidden "
        "by a pinkish ivory mask with closed eyes, a crown-like point and the numeral III. Five long stone "
        "spearheads hang beside her, aimed ahead. Radiant and austere, she sits like an enthroned sun goddess."},
  {"Em0032_004",  // ?
        "A mother carved as a statue, seated upright on a tall throne of dusky purple stone set with small clear "
        "crystals down its back. Her robe and tall flat-topped hat are a dull khaki gold trimmed with dusky "
        "purple, her skin and long, flowing hair pale grey. One arm holds a small grey child to her chest; the "
        "other hand lifts a bright red ball, round and glossy as an apple. An ivory mask with closed eyes, a "
        "crown-like point and the numeral III hides her face. Five long silver spearheads hang beside her, aimed "
        "ahead. Regal and still, she offers the red fruit calmly, like a blessing."},
  {"Em0033_000",  // Elegant Mother
        "A tall, slender woman with a sleek, featureless black body, lounging sideways on an ornate chaise "
        "longue, both long black legs stretched up along the seat and her arms draped lazily over its sides, "
        "clawed fingers dangling. The chaise is bottle-green upholstery framed in copper-brown wrought scrolls. A "
        "floor-length dark navy-violet coat with gold piping spills to the ground from a huge shaggy tawny fur "
        "collar, with pearls and gold chains at her throat. An ivory mask with closed eyes, a crown-like point "
        "and the numeral III sits under a tall black hat, straight magenta locks at her cheeks. Languid and rich, "
        "she sprawls as if the room were hers."},
  {"Em0033_001",  // Regal Mother
        "A tall, slender woman with a sleek, featureless black body, lounging sideways on a plum-purple chaise "
        "longue framed in silver-grey wrought iron, both long black legs stretched up along the seat and her "
        "clawed hands hanging over its sides. Behind it fans a great spread of black spikes webbed with sheer "
        "fins shading from lime green to sea blue, flecked orange at the edges. Her floor-length crimson coat has "
        "fluffy lilac fur at collar and cuffs, with pearls at her throat, a tall lilac hat over long honey-brown "
        "hair and an ivory mask with closed eyes, a crown-like point and the numeral III. Decadent and imperious, "
        "she reclines at ease."},
  {"Em0033_002",  // Lascivious Lady
        "A tall, slender woman with a sleek, featureless black body, lounging sideways on a tiger-striped chaise "
        "longue framed in gold scrollwork, both long black legs stretched up along the seat and her clawed hands "
        "hanging over its sides. Behind it fans a huge spread of dark purple spikes webbed with white fins "
        "spotted in black. Her floor-length coat and tall hat are leopard print, the collar and cuffs smoky grey "
        "fur, with pearls at her throat and long purple hair framing an ivory mask with closed eyes, a crown-like "
        "point and the numeral III. Wrapped in one animal print over another, she sprawls flamboyant and "
        "predatory."},
  {"Em0033_003",  // Divine Mother
        "A tall, slender woman with a smooth, featureless lilac-grey body, lounging sideways on a lavender chaise "
        "longue framed in pale silver scrollwork, both long legs stretched up along the seat and her clawed hands "
        "resting over its sides. Behind her rises a full peacock's tail, green feathers with blue and gold eye "
        "spots shading to violet at the roots. Her floor-length pale mint coat has feathery mint fur at collar "
        "and cuffs, with pearls at her throat, a tall mint hat over long blonde hair and an ivory mask with "
        "closed eyes, a crown-like point and the numeral III. Cool and vain, she lounges in pastel splendour."},
  {"Em0041_000",  // Grave Beetle
        "A huge rhinoceros beetle, longer than a car, standing high on four pairs of black, jagged legs, its "
        "domed shell cracked all over like old glaze in mottled purple and moss green and splashed with streaks "
        "of blood red. From its snout a long horn curves up and back like a swan's neck, balancing on its tip a "
        "lavender half mask with hollow eye slots, the numeral IV on its brow and five barbed spikes fanning up "
        "like a crown. Pale, bulging eyes sit low on its head, and thin smoky wings jut straight out sideways. "
        "Diseased and ancient, it looks like something that crawled out of a grave."},
  {"Em0041_001",  // Adamant Beetle
        "A huge rhinoceros beetle standing high on four pairs of dark, thorny legs, its smooth shell a deep "
        "crimson-maroon like polished lacquer. A band of gold key pattern runs around the edge of its wing case, "
        "and a jagged gold crown set with tiny blue stones sits on its back where a rider would sit. From its "
        "snout a long horn curves up and back, balancing on its tip a lavender half mask with hollow eye slots, "
        "the numeral IV on its brow and five barbed spikes. Its eyes are glossy pink domes, and pale tan wings "
        "jut straight out sideways. Polished and pompous, it carries itself like minor royalty."},
  {"Em0041_002",  // Golden Beetle
        "A huge rhinoceros beetle dressed as a king, standing high on four pairs of black, thorny legs. Its head "
        "and thorax are armoured in bright gold, and its wing case is a royal blanket embroidered in purple, teal "
        "and gold swirls on deep navy. On its back sits a full coronation crown: crimson velvet under gold arches "
        "studded with jewels, a white fur band at the base and a jewelled cross on top. A long gold horn curves "
        "up from its snout, holding high a lavender half mask with hollow eyes, the numeral IV and five barbed "
        "spikes. Gaudy and majestic, it parades its crown like a monarch."},
  {"Em0041_003",  // Emperor Beetle
        "A huge rhinoceros beetle in shimmering pastel blue, violet and mint, standing on four pairs of pale, "
        "almost white, spiky legs. Unlike its plainer kin it has two extra horns, long curved tusks rising from "
        "its thorax and arching forward to meet in a point above its head, draped with strings of teal, lilac and "
        "yellow beads like a festival archway. A row of round turquoise stones studs its wing case. Its snout "
        "horn curves up beneath the arch, holding a dark violet half mask with hollow eyes, the numeral IV and "
        "five barbed spikes. Jewel-draped and gleaming, it moves like a float in an emperor's parade."},
  {"Em0041_004",  // ?
        "A huge rhinoceros beetle in bold scarlet, standing high on four pairs of dark, thorny legs, its wing "
        "case covered in curling gold swirls and edged in gold. A jagged crown of bright green rimmed with gold "
        "sits on its back, and its eyes are round green gems. Its wings jut straight out sideways, fading from "
        "red through orange to green tips. From its snout a long red horn curves up and back, holding high a "
        "lavender half mask with hollow eye slots, the numeral IV and five barbed spikes. Loud and fiery, it "
        "struts in its finery like a festival lantern come to life."},
  {"Em0042_000",  // ?
        "A headless knight on a dragon steed, his armour hollow: gunmetal-grey plates with flared, pointed "
        "shoulder guards and a gold-patterned chest band hang in place with empty air between them, a dark blue "
        "scarf streaming behind. Where the head should be floats a lavender half mask with hollow eyes, the "
        "numeral IV and five barbed spikes. His mount has a long armoured dragon's head with one horn, a spiky "
        "mane and red eyes, its body hidden under a navy caparison trimmed in gold and hung with purple diamond "
        "jewels. He bears a long lance and a small round shield. Grim and empty, he rides like vengeance with no "
        "one inside."},
  {"Em0042_001",  // Champion Knight
        "A headless knight on a dragon steed, his armour hollow: dark violet-grey plates with flared, pointed "
        "shoulder guards and a gold-patterned chest band hang in place with empty air between them, a crimson "
        "scarf streaming behind. Where the head should be floats a lavender half mask with hollow eyes, the "
        "numeral IV and five barbed spikes. His mount has a long armoured dragon's head with one horn, a spiky "
        "mane and red eyes, its body draped in a deep crimson caparison trimmed in gold and hung with steel-grey "
        "diamond charms. He bears a dark lance and a small round shield. Proud in blood red, he rides like a "
        "champion."},
  {"Em0042_002",  // Demented Knight
        "A headless knight on a dragon steed, almost wholly black, his armour hollow: blue-black plates with "
        "flared, pointed shoulder guards and a pale-patterned chest band hang in place with empty air between "
        "them, a dark plum scarf streaming behind. Where the head should be floats a lavender half mask with "
        "hollow eyes, the numeral IV and five barbed spikes. His mount is black too, its studded dragon head "
        "horned and spiky-maned with red eyes, under a deep purple caparison edged in red and white braid and "
        "hung with purple diamond charms. He bears a black lance and a small round shield. He rides like a "
        "nightmare out of hell."},
  {"Em0042_003",  // Intrepid Knight
        "A headless knight on a dragon steed, pale and ghostly, his armour hollow: frosty mint-white plates with "
        "flared, pointed shoulder guards and a red-patterned chest band hang in place with empty air between "
        "them, a vivid violet scarf streaming behind. Where the head should be floats a dark violet half mask "
        "with hollow eyes, the numeral IV and five barbed spikes. His mount is bone white, its dragon head "
        "crested with one long horn and a spiky mane, under a pale lilac-grey caparison trimmed in red and hung "
        "with purple charms. He bears a red-banded grey lance and a small round shield. He rides swift and "
        "spectral."},
  {"Em0043_000",  // Haunted Castle
        "A walking crag with a castle on its summit: a towering column of grey rock wound with ledges like a "
        "twisted tooth, narrowing below into two thick stony legs with an arch between them. A narrow stair winds "
        "around it, little gatehouses cling to its sides and black cannon barrels poke out in every direction. On "
        "top stands a grey stone castle with battlements, an arched door and turrets under purple roofs and "
        "pennants. From the keep rises a black hooded head wearing a lavender mask with hollow eyes, the numeral "
        "IV and a sunburst of barbed spikes. Dour and heavy, it is a fortress on the march."},
  {"Em0043_001",  // Isolated Castle
        "A walking crag with a castle on its summit: a towering column of rock furred with bright green moss, "
        "wound with ledges and narrowing below into two thick legs with an arch between them. A narrow stair "
        "winds up it, little gatehouses cling to its sides and dark cannons poke out all around. On top stands a "
        "sandy, honey-coloured stone castle with battlements, an arched door and turrets under brick-red roofs "
        "and pennants. From the keep rises a black hooded head wearing a lavender mask with hollow eyes, the "
        "numeral IV and a sunburst of barbed spikes. Green and weathered, it is a lonely island fortress that "
        "grew legs."},
  {"Em0043_002",  // Death Castle
        "A walking crag with a castle on its summit, its rock a lurid blood crimson, wound with ledges and "
        "narrowing below into two thick legs with an arch between them. A red stair winds up it, and black "
        "cannons banded in red poke out from ports framed with red crosses. On top stands a cold grey stone "
        "castle with battlements, an arched door and turrets under dark red roofs and pennants. From the keep "
        "rises a black hooded head wearing a lavender mask with hollow eyes, the numeral IV and a sunburst of "
        "barbed spikes. Soaked in red from foot to battlements, it looks built for slaughter."},
  {"Em0043_003",  // Comeback Castle
        "A walking crag with a castle on its summit, all in pale, dreamy tones: a towering column of soft "
        "lilac-grey rock wound with ledges like a twisted tooth, narrowing below into two thick legs with an arch "
        "between them, a faint purple stair winding up it. Bronze cannons banded in gold poke out all around. On "
        "top stands a weathered white stone castle with battlements, an arched door and turrets under blue-violet "
        "roofs and tan pennants. From the keep rises a cream-white hooded head wearing an orchid-pink mask with "
        "hollow eyes, the numeral IV and a sunburst of barbed spikes. Stately and serene, it looks like a "
        "fairy-tale stronghold."},
  {"Em0051_000",  // Trance Twins
        "Two gaunt, identical figures standing side by side, skewered together like prisoners: three long iron "
        "rods, each with an arrowhead at one end and fletching-like crossbars at the other, run through the iron "
        "collars at their necks, the cuffs at their wrists and the shackles at their ankles. Each has charcoal "
        "skin, a close olive-brown skullcap, round disc-like ears and long bony hands hanging limp, in a drab "
        "olive-brown monk's robe with a cowl and a rope belt. Each face is a blue oval mask with the numeral V, "
        "slanted eye slits and a gaping triangular mouth, bolted on. Joyless and limp, they stand like penitents "
        "sentenced together."},
  {"Em0051_001",  // ?
        "Two gaunt, identical figures standing side by side, skewered together like prisoners by three long dark "
        "iron rods, each with an arrowhead and fletching-like crossbars, run through the blue-violet collars at "
        "their necks, the cuffs at their wrists and the shackles at their ankles. Each has dark charcoal skin, a "
        "bald head, round disc-like ears and bony hands hanging limp, in a black robe with a short purple "
        "shoulder cape trimmed in lilac and a purple sash. Each face is a blue oval mask with the numeral V, "
        "slanted eye slits and a gaping triangular mouth, bolted on. They look like executioners chained to each "
        "other."},
  {"Em0051_002",  // Death Twins
        "Two gaunt, identical figures standing side by side, skewered together like prisoners by three long brass "
        "rods, each with an arrowhead and fletching-like crossbars, run through the brass collars at their necks, "
        "the cuffs at their wrists and the shackles at their ankles. Each has dark charcoal skin, round disc-like "
        "ears and a small red skullcap banded in gold, in crimson robes piped in gold with a wide panel of black "
        "and gold filigree down the front, like a cardinal's finery. Each face is a blue oval mask with the "
        "numeral V, slanted eye slits and a gaping triangular mouth, bolted on. They stand grand and grim."},
  {"Em0051_003",  // Crazy Twins
        "Two gaunt, identical figures standing side by side, skewered together like prisoners by three long "
        "olive-brass rods, each with an arrowhead and fletching-like crossbars, run through the pale sea-green "
        "collars at their necks, the cuffs at their wrists and the shackles at their ankles. Unlike their kin "
        "they have pale ash-grey skin, with bald heads, round disc-like ears and bony hands hanging limp, in "
        "off-white cowled robes woven with a faint damask pattern and tied with an olive cord. Each face is a "
        "blue oval mask with the numeral V, slanted eye slits and a gaping triangular mouth, bolted on. "
        "Washed-out and ghostly, they look quietly unhinged."},
  {"Em0052_000",  // Corrupt Tower
        "A towering totem of three huge stone heads stacked one upon another, dark grey, eyes closed and serene, "
        "each smaller than the one below and seated inside the open mitre of the head beneath it. The mitres are "
        "crimson bishops' hats in gold frames, banded with gold studded with blue stones, a column of gems up the "
        "front, purple above green. The topmost face wears a blue oval mask with slanted eye slits, bolted to the "
        "head, beneath the tallest mitre, its gold front worked like a sunburst around a large purple gem over "
        "two green. Silent and pious, it rises like a church spire that worships itself."},
  {"Em0052_001",  // Dogmatic Tower
        "A towering totem of three huge stone heads stacked one upon another, dark grey, eyes closed and serene, "
        "each smaller than the one below and seated inside the open mitre of the head beneath it. The mitres are "
        "ivory-cream bishops' hats in gold frames, banded with gold squares studded with little red stones, a "
        "gold medallion set with rubies on each front. The topmost face wears a blue oval mask with slanted eye "
        "slits, bolted to the head, beneath the tallest mitre, its gold sunburst panel carrying a column of three "
        "red gems. Pale and stern, it stands with the cold sanctity of doctrine."},
  {"Em0052_002",  // Pagoda of Disaster
        "A towering totem of three huge stone heads stacked one upon another, dark grey, eyes closed and serene, "
        "each smaller than the one below and seated inside the open mitre of the head beneath it. The mitres are "
        "glossy black bishops' hats framed in silver, banded with silver squares set with violet stones, a silver "
        "medallion of red gems on each front. The topmost face wears a blue oval mask with slanted eye slits, "
        "bolted to the head, beneath the tallest mitre, its silver sunburst panel carrying a column of three red "
        "gems. All black and silver, it looks like a heretic's idol, a church turned against itself."},
  {"Em0052_003",  // Fanatic Tower
        "A towering totem of three huge heads stacked one upon another, chalky white like marble statues, eyes "
        "closed and serene, each smaller than the one below and seated inside the open mitre of the head beneath "
        "it. The mitres are royal blue laced with gold filigree hearts and curls, and on each front stands a "
        "large oval mirror in a gold frame with spiky flourishes and a green gem below. The topmost face wears a "
        "blue oval mask with slanted eye slits, bolted to the head, beneath the tallest mitre, a green bead at "
        "its tip. Gleaming and lofty, it rises like a cathedral spire admiring itself."},
  {"Em0052_004",  // ?
        "A towering totem of three huge heads stacked one upon another, eyes closed and serene, each smaller than "
        "the one below and seated inside the open mitre of the head beneath it. The heads are pale sea green, "
        "their white faces streaked by thin green lines running down from the eyes like dried tears. The mitres "
        "are deep green with gold flame-like swirls, gold zigzag bands and a cream spine studded with red gems. "
        "The topmost face wears a bolted blue oval mask with slanted eye slits, under a mitre ending in a gold "
        "spearpoint set with a red gem. Weeping and solemn, it stands like a shrine to sorrow."},
  {"Em0053_000",  // Blue Sigil
        "A priest walled inside a giant book: huge tan parchment pages, dense with black script under curled "
        "initials, enclose him on every side in two tiers, a narrow slit between them showing the figure within. "
        "He wears a teal-blue cassock with silver cross-shaped clasps, a white stole edged in gold and dotted "
        "with blue flowers, a dark navy cape, and a round brooch of a gold square stone ringed by blue gems and "
        "pearls. A tall white mitre with gold crosses tops a blue mask with the numeral V, slanted eyes and a "
        "gaping beak-like mouth. He peers out from his scripture like a keeper of forbidden texts."},
  {"Em0053_001",  // Red Sigil
        "A priest walled inside a giant book: huge ashen grey pages, dense with black script under curled "
        "initials, enclose him on every side in two tiers, a narrow slit between them showing him, and small "
        "black feathered wings on curling stems peek out at his sides. He wears a black cassock with bone-white "
        "cross-shaped clasps, a crimson cape, and a round brooch of a red square stone ringed by lilac pearls. "
        "His tall black mitre carries silver crosses and spikes above a blue mask with the numeral V, slanted "
        "eyes and a gaping beak-like mouth. In black and blood red, he looks like a zealot of a darker creed."},
  {"Em0053_002",  // Cultist of the Storm
        "A priest walled inside a giant book: huge pages of dark wine red, dense with black script under curled "
        "initials, enclose him on every side in two tiers, a narrow slit between them showing the figure within. "
        "He wears an emerald green cassock with gold cross-shaped clasps, a deep blue stole, a green cape, and a "
        "round brooch of a gold square stone ringed by green gems and pearls. His tall green mitre carries gold "
        "crosses above a blue mask with the numeral V, slanted eyes and a gaping beak-like mouth. In green and "
        "gold behind his blood-dark pages, he looks like the leader of a storm-worshipping sect."},
  {"Em0053_003",  // Cultist of Death
        "A priest walled inside a giant book: huge ghostly white pages, dense with black script under curled "
        "initials, enclose him on every side in two tiers, a narrow slit between them showing him, and small pink "
        "feathered wings on gold curls peek out at his sides. He wears a white cassock with lilac cross-shaped "
        "clasps, a hot pink stole, and a round brooch of a teal stone ringed in pearls. His tall mitre is "
        "bubblegum pink, banded and spiked in silver, above a blue mask with the numeral V, slanted eyes and a "
        "gaping beak-like mouth. Sweetly coloured, he stands stiff and solemn as a priest at a graveside."},
  {"Em0061_000",  // Jealous Cupid
        "A small, plump cherub of pure shadow, the size of a toddler, standing slack with its round belly pushed "
        "out, its stubby legs, long-fingered hands and feathered wings all a dull charcoal black. Its whole face "
        "is a hot pink mask stamped with a pale VI on the brow and bolted round the edge with steel clasps to a "
        "black hood; the eyes droop half-shut and the little mouth hangs open in a sleepy O. One hand dangles a "
        "pale silver bow with curled scroll ends and arrows tipped with hearts, pointing at the floor. The god of "
        "love gone sullen and dark, it looks bored, spoiled and quietly dangerous."},
  {"Em0061_001",  // Enslaved Cupid
        "A small, plump cherub of shadow, the size of a toddler, standing slack with its round belly pushed out, "
        "in a skin-tight black body striped down the sides and legs with royal blue. Its wings fade from dark "
        "teal at the root to bright sky blue at the tips. Its whole face is a hot pink mask stamped with a pale "
        "VI and bolted with steel clasps to a black hood; the eyes droop half-shut and the little mouth hangs "
        "open in a sleepy O. One hand dangles a violet bow with curled ends and blue-shafted arrows tipped with "
        "violet hearts. Cool-toned and sulky, it slumps like love gone cold."},
  {"Em0061_002",  // Devoted Cupid
        "A small, plump cherub of shadow, the size of a toddler, standing slack with its round belly pushed out, "
        "in a skin-tight black body striped down the sides and legs with deep magenta. Its wings fade from black "
        "at the root to hot pink at the tips. Its whole face is a hot pink mask stamped with a pale VI and bolted "
        "with steel clasps to a black hood; the eyes droop half-shut and the little mouth hangs open in a sleepy "
        "O. One hand dangles a candy-pink bow with curled ends and black-shafted arrows tipped with bright red "
        "hearts. All pink and black, it looks smothering, sulky and devoted."},
  {"Em0061_003",  // Luckless Cupid
        "A small, plump cherub, the size of a toddler, standing slack with its round belly pushed out, its body, "
        "stubby legs and long-fingered hands are a glassy mint aqua under a white hood. Its wings shimmer in "
        "pastels, lilac at the root through pale green and yellow to warm orange tips. Its whole face is a "
        "crimson-pink mask stamped with a pale VI and bolted with gold clasps; the eyes droop half-shut and the "
        "little mouth hangs open in a sleepy O. One hand dangles a gold bow with curled ends and arrows tipped "
        "with gold hearts. Pastel and sugary, it droops as bored as its darker kin."},
  {"Em0062_000",  // Lustful Snake
        "A long serpent held rigidly upright, taller than a person and straight as a spear, its pitch-black body "
        "finely ringed, tapering to a needle point below and a small blunt head above. A tiny crimson-pink mask "
        "with slit eyes sits on the back of its head. Hung on either side of it like charms on a cord are two "
        "flat ornaments: in front a magenta ring above a cross with arrowhead arms and a heart at its foot, the "
        "sign of woman, and behind a steel-blue ring above a downward arrow, the sign of man. It stands stiff and "
        "silent between them, desire reduced to a pair of symbols."},
  {"Em0062_001",  // Immoral Snake
        "A long serpent held rigidly upright, taller than a person and straight as a spear, black down its front, "
        "its back and sides striped in narrow bands of magenta and violet. Its small blunt head carries a tiny "
        "crimson-pink mask with slit eyes at the back. Hung on either side of it are two flat ornaments: in front "
        "a magenta ring above a cross with arrowhead arms and a heart at its foot, the sign of woman, and behind "
        "a dusky indigo ring above a downward arrow, the sign of man. Black in front and gaudy behind, it shows "
        "its stripes only to those who come around it."},
  {"Em0062_002",  // Carnal Snake
        "A long serpent held rigidly upright, taller than a person and straight as a spear, smooth black in "
        "front, its back sheathed in a mesh of blood-red scales like fishnet stretched over shadow. Its small "
        "blunt head carries a tiny crimson-pink mask with slit eyes at the back. Hung on either side of it are "
        "two flat ornaments: in front a polished silver ring above a cross with arrowhead arms and a heart at its "
        "foot, the sign of woman, and behind a black iron ring engraved with runes above a downward arrow, the "
        "sign of man. Black, red and silver, it has a cold, sinful elegance."},
  {"Em0062_003",  // Invasive Serpent
        "A long serpent held rigidly upright, taller than a person and straight as a spear, its whole body a pale "
        "cream like old ivory, finely ridged, tapering to a needle point below and a small blunt head above, with "
        "a tiny crimson-pink slit-eyed mask at the back. Hung on either side of it are two flat ornaments that "
        "shimmer like mother-of-pearl: in front a ring above a cross with arrowhead arms and a heart at its foot, "
        "the sign of woman, washed in pink and lilac, and behind a ring above a downward arrow, the sign of man, "
        "in mint, blue and cyan. Pale and pearly, it looks deceptively sweet."},
  {"Em0062_004",  // ?
        "A long serpent held rigidly upright, taller than a person and straight as a spear, deep teal down its "
        "front, its back covered in small overlapping scales of leaf green. Its small blunt head carries a tiny "
        "crimson-pink slit-eyed mask at the back. Hung on either side of it are two flat ornaments of engraved "
        "bronze: in front a ring above a cross with arrowhead arms and a heart at its foot, the sign of woman, "
        "and behind a ring above a downward arrow, the sign of man. Green and bronze like a jungle idol, it is "
        "the most natural-looking of its kind, and as still as one."},
  {"Em0063_000",  // Dependent Partner
        "A headless ballroom dancer of human height with a big black heart floating above a bare dark stump of "
        "neck. Pinned to the heart by a ring of nails is a crimson-pink mask stamped VI, its eyes shut and its "
        "mouth sagging open in grief. The body is dressed as both partners at once: a man's white tailcoat with "
        "cream lapels and a pink bow, open over a long coral-pink gown fading to peach at the hem, black ooze "
        "dripping from its waist. Black boots, long dark fingers and a slim fencing foil with a bell guard. It "
        "looks like a dance for two left to one."},
  {"Em0063_001",  // Ardent Dancer
        "A headless ballroom dancer of human height with a big black heart floating above its dark neck stump, a "
        "crimson-pink mask stamped VI nailed to the heart, eyes shut and mouth sagging open in grief. It wears "
        "both partners' clothes: a sky-blue tailcoat with cream lapels and a golden bow, open over a "
        "marigold-yellow gown printed with white flowers, its skirt falling in tiers of lace-edged ruffles, black "
        "ooze dripping from the waist. Black boots, long dark fingers and a gold fencing foil with a bell guard. "
        "Dressed in sunshine colours, it carries its sorrow onto the dance floor all the same."},
  {"Em0063_002",  // Royal Dancer
        "A headless ballroom dancer of human height with a big black heart floating above its dark neck stump, a "
        "crimson-pink mask stamped VI nailed to the heart, eyes shut and mouth sagging open in grief. It is "
        "dressed all in black for both partners: a black tailcoat with white lapels and a black bow, open over a "
        "long black gown, both sprinkled with tiny gold dots, with gold piping running down the coat-tails and "
        "around the hem. Black boots, long dark fingers and a silver fencing foil with a bell guard. Dressed for "
        "a midnight ball, it is the most formal and funereal of its kind."},
  {"Em0063_003",  // ?
        "A headless ballroom dancer of human height whose floating heart is pale icy mint fading to white, not "
        "black like its kin, with a crimson-pink mask stamped VI nailed to it, eyes shut and mouth sagging open "
        "in grief. Its body wears a cream tailcoat with a pink bow, open over a long pastel pink gown with a mint "
        "underlayer that shows at the waist like melting icing, and its boots, hands and neck stump are a pale "
        "frosty blue. A grey-blue fencing foil with a bell guard. All pastels and frost, it looks like the figure "
        "from a wedding cake, its heart broken."},
  {"Em0063_004",  // ?
        "A headless dancer of human height whose floating heart is a dark slate teal, a crimson-pink mask stamped "
        "VI nailed to it, eyes shut and mouth sagging open in grief. Unlike its kin it wears no long gown: a "
        "short crimson jacket with a frilled white cravat and ruffled white cuffs, cinched by a black belt over a "
        "short skirt of white tiered ruffles, splashed with red where the jacket's colour runs into it, and below "
        "that long dark legs in tall black boots. A gold fencing foil with a bell guard. Short-skirted and sharp, "
        "it looks dressed for a flamenco duel rather than a waltz."},
  {"Em0071_000",  // Bestial Wheel
        "A lion's head with no body, rolling on a single big black spoked wheel: a great spiky mane of shaggy "
        "brown blades flares around the head, and a short tawny back arcs over the wheel into a long tail "
        "streaming out behind to a tufted brown bulb. Clamped over its face with black studs is a yellow lion "
        "mask stamped VII, its eye slits narrow and closed, and below it a fanged red mouth gapes in a snarl. "
        "Long black spikes jut straight out from the hub on either side like a war chariot's scythes. All mane, "
        "teeth and iron, it is a chariot that has become its own beast."},
  {"Em0071_001",  // Mach Wheel
        "A lion's head with no body, rolling on a single big black spoked wheel, its spiky mane made of bright "
        "green blades like a crown of jungle leaves. A short tawny back arcs over the wheel into a long tail that "
        "streams out behind to a leafy green tuft. Clamped over its face with black studs is a yellow lion mask "
        "stamped VII, eye slits narrow and closed, a fanged red mouth snarling below it. Dark slate spikes jut "
        "out from a steel hub on either side like a war chariot's scythes. Leafy and wild, it looks like a "
        "chariot grown out of the undergrowth."},
  {"Em0071_002",  // Brave Wheel
        "A lion's head with no body, rolling on a single big black wheel whose spokes are painted red, its spiky "
        "mane of orange and red blades flaring around it like a bonfire. A short rust-red back arcs over the "
        "wheel into a long tail that streams out behind to a flame-orange tuft. Clamped over its face with black "
        "studs is a yellow lion mask stamped VII, eye slits narrow and closed, a fanged red mouth snarling below "
        "it. Black spikes jut out from a red-ringed hub on either side like a war chariot's scythes. Fiery from "
        "mane to tail, it looks built to charge straight through."},
  {"Em0071_003",  // Dancing Beast Wheel
        "A lion's head with no body, rolling on a single wheel with a pale ice-blue rim and polished gold spokes "
        "and hub, its spiky mane made of icy blue-white blades like shards of frost. A short lilac back arcs over "
        "the wheel into a long tail that fades to pale blue and ends in a frosty tuft. Clamped over its face with "
        "silver studs is a yellow lion mask stamped VII, eye slits narrow and closed, a fanged dark mouth "
        "snarling below it. Long gold spikes jut from the hub on either side like a war chariot's scythes. Ice "
        "and gold, it has the cold splendour of a royal carriage."},
  {"Em0072_000",  // Wild Drive
        "A hulking armoured knight fused with a horse, caught mid-gallop: a broad torso leaning forward on four "
        "crooked black horse legs, one pair flung out in front and the other kicked back. Its face is a yellow "
        "knight's mask with a T-shaped eye slit and a small VII, set in a black mesh hood that wraps the neck "
        "like a scarf. It wears grey-silver plate strapped down the chest with tan buckles, a bronze shield on "
        "its belly and round bronze and teal shields at its flanks, and through its shoulders runs a massive "
        "grey-green spiked cudgel. Heavy and grim, it charges like a jouster that tramples rather than rides."},
  {"Em0072_001",  // Killer Drive
        "A hulking armoured knight fused with a horse, caught mid-gallop: a broad torso leaning forward on four "
        "crooked black horse legs, one pair flung out in front and the other kicked back. Its face is a yellow "
        "knight's mask with a T-shaped eye slit and a small VII, set in a dark green mesh hood. Its armour is "
        "navy lined with bright blue seams, with a faceted steel disc on each shoulder, a gold belly shield and "
        "round gold shields with teal bosses at its flanks. Through its shoulders runs a long pale steel lance, "
        "pointed at both ends. Blue and gold, it rears like a jouster at full tilt."},
  {"Em0072_002",  // Slaughter Drive
        "A hulking armoured knight fused with a horse, caught mid-gallop on four crooked black horse legs, one "
        "pair flung out in front and the other kicked back. Its face is a yellow knight's mask with a T-shaped "
        "eye slit and a small VII, wrapped in a hood of cream-white cloth like a pilgrim's. Its armour is glossy "
        "crimson trimmed in cream, its belly plate purple engraved in gold, and its round shields purple with red "
        "rims and cream bosses. Through its shoulders runs a long golden sword blade with an ornate purple and "
        "gold crossguard. Red, gold and royal purple, it charges like a crusader under a banner."},
  {"Em0072_003",  // Rampage Drive
        "A hulking armoured knight fused with a horse, caught mid-gallop on four crooked horse legs, pale icy "
        "mint rather than black, one pair flung out in front and the other kicked back. Its face is a yellow "
        "knight's mask with a T-shaped eye slit and a small VII, in a pale aqua mesh hood. Its armour shades from "
        "blue to teal with cream trim, a vivid blue belly shield and round shields shimmering blue and teal in "
        "gold rims, and through its shoulders runs a long lance of pale lavender steel, pointed at both ends. It "
        "looks like a ghostly knight charging out of the snow."},
  {"Em0073_000",  // Wicked Turret
        "A battle tank bigger than a car, low and broad, its hull draped in armour like a heavy pleated skirt: "
        "scalloped charcoal plates, riveted and edged in gold zigzag trim, spreading out over six spoked road "
        "wheels on each side and fraying at the front into ragged fringes. A squat gold-trimmed turret sits on "
        "top with a long black gun, and its rounded roof is a smooth yellow dome with dark eye slits: the "
        "Shadow's mask, lying face up to the sky. Dark, gilded and heavy, it is a war chariot reborn as rolling "
        "artillery."},
  {"Em0073_001",  // Scarlet Turret
        "A battle tank bigger than a car, low and broad, its hull draped in armour like a heavy pleated skirt: "
        "scalloped plates of glossy crimson, riveted and edged in silver-white zigzag trim, spreading out over "
        "six dark spoked road wheels on each side and fraying at the front into ragged fringes. A ribbed crimson "
        "turret ringed in cream and silver sits on top with a long black gun, and its rounded roof is a smooth "
        "yellow dome with dark eye slits: the Shadow's mask, lying face up to the sky. Glossy red and silver, it "
        "looks like a parade tank that has gone to war."},
  {"Em0073_002",  // Wicked Turret
        "A battle tank bigger than a car, low and broad, its hull draped in armour like a heavy pleated skirt: "
        "scalloped plates of deep purple, strapped down with riveted steel bands and edged in silver zigzag trim, "
        "spreading out over six dark spoked road wheels on each side and fraying at the front into ragged "
        "fringes. A ribbed purple turret ringed in steel sits on top with a long black gun, and its rounded roof "
        "is a smooth yellow dome with dark eye slits: the Shadow's mask, lying face up to the sky. Bruise-purple "
        "and banded in steel, it has a cold, regal menace."},
  {"Em0073_003",  // Hallowed Turret
        "A battle tank bigger than a car, low and broad, its hull draped in armour like a heavy pleated skirt: "
        "scalloped plates of pale cream blushing to sand, riveted and edged in silver zigzag trim, spreading out "
        "over six pale grey spoked road wheels on each side and fraying at the front into ragged fringes. A cream "
        "turret ringed in silver sits on top with a long gun of polished brass, and its rounded roof is a smooth "
        "yellow dome with dark eye slits: the Shadow's mask, lying face up to the sky. Pale and burnished, it "
        "looks almost ceremonial, a war machine dressed for a procession."},
  {"Em0073_004",  // ?
        "A battle tank bigger than a car, low and broad, its hull draped in armour like a heavy pleated skirt: "
        "scalloped plates painted in woodland camouflage blotches of olive, tan, black and green, with strands of "
        "ivy trailing down over them, spreading out over six spoked road wheels on each side. A ribbed dark green "
        "turret sits on top with a green gun banded in bronze, and its rounded roof is a smooth yellow dome with "
        "dark eye slits: the Shadow's mask, lying face up to the sky, ivy creeping over it too. Overgrown and "
        "camouflaged, it looks as if it has lain hidden in a forest for years."},
  {"Em0073_005",  // ?
        "A battle tank bigger than a car, low and broad, its hull draped in armour like a heavy pleated skirt: "
        "scalloped plates of navy blue painted across the front and sides with hot-rod flames of yellow and red "
        "licking upward, edged in copper-orange zigzag trim and spreading out over six dark spoked road wheels on "
        "each side. A ribbed navy turret ringed in copper sits on top with a navy gun banded in orange, and its "
        "rounded roof is a smooth yellow dome with dark eye slits: the Shadow's mask, lying face up to the sky. "
        "Loud and flashy, it wears its painted flames like a hot rod."},
  {"Em0081_000",  // Voltaic Youngest Sibling
        "A tall samurai standing straight-backed in white lacquered armour laced with green cord over a black "
        "body, a gold crest of three swirling commas on its breastplate. Its face is a smooth cobalt-blue mask, "
        "calm and expressionless, with the numeral XI and a diamond on its brow, under a white helmet crowned "
        "with a gold blade flanked by two sweeping horns. A navy capelet sits on its shoulders and a long cloak "
        "falls behind, navy outside and blood red within. Arrows stick out of its shoulder guards, and it carries "
        "an enormously long, thin curved sword. Pale and proud, it stands like a warrior who fought on full of "
        "arrows."},
  {"Em0081_001",  // Blazing Middle Sibling
        "A tall samurai standing straight-backed in red lacquered armour edged with silver over a black body, a "
        "gold three-comma crest on its breastplate. Its face is a smooth cobalt-blue mask with the numeral XI and "
        "a diamond on its brow. In place of a horned crest it wears a towering ribbed red cone with a gold disc "
        "on each side, taller than its head and neck together, like a famous warlord's helmet. A black capelet "
        "and long black cloak edged in gold hang from its shoulders, arrows stick out of its shoulder guards, and "
        "it carries an enormously long, thin curved sword. Red and towering, it stands in imperious pride."},
  {"Em0081_002",  // Deadly Eldest Sibling
        "A tall samurai standing straight-backed in dark violet lacquered armour edged with lilac over a black "
        "body, a blood-red three-comma crest on its breastplate. Its face is a smooth cobalt-blue mask with the "
        "numeral XI on its brow and a black patch strapped over one eye, under a dark purple helmet crowned by a "
        "wide silver crescent moon, the badge of the famous one-eyed warlord. A plum capelet sits on its "
        "shoulders and a long cloak falls behind, purple outside and sea-teal within. Red-fletched arrows stick "
        "out of its shoulder guards, and it carries an enormously long, thin curved sword. One-eyed and dark, it "
        "has a battle-worn veteran's grim calm."},
  {"Em0081_003",  // Tenjin Musha
        "A tall samurai standing straight-backed in cream and pale gold lacquered armour bound with green cord, "
        "over a body of pale blue-grey, a deep blue three-comma crest on its breastplate. Its face is a smooth "
        "cobalt-blue mask with the numeral XI and a diamond on its brow, under a cream helmet crowned with a gold "
        "ring between two upswept feathered wings. A cream capelet and a long cream cloak drape from its "
        "shoulders, arrows stick out of its shoulder guards, and it carries an enormously long, thin curved sword "
        "with a pale gold blade and a blue-corded hilt. Pale and winged, it has the serene bearing of a heavenly "
        "general."},
  {"Em0082_000",  // Steel Gigas
        "A colossal giant built like a professional wrestler, its glossy black body swollen into slabs of muscle, "
        "the shoulders and chest so huge that its small head sits low between them. Round silver rivets stud its "
        "chest, shoulders and the fronts of its thighs. Its face is a smooth cobalt-blue mask with the numeral XI "
        "on the brow, fixed above a metal frame that cages its jaw, and long straight white hair hangs from the "
        "back of its head. It wears nothing but silver wrestling briefs with a swirling pattern, silver "
        "wristbands and tall silver boots. Silent and vast, it stands like a heavyweight waiting for the bell."},
  {"Em0082_001",  // Profligate Gigas
        "A colossal giant built like a professional wrestler, its glossy black body swollen into slabs of muscle, "
        "the shoulders and chest so huge that its small head sits low between them. Bronze rivets stud its chest, "
        "shoulders and the fronts of its thighs. Its face is a smooth cobalt-blue mask with the numeral XI on the "
        "brow, fixed above a metal frame that cages its jaw, and long golden-blond hair hangs from the back of "
        "its head. It wears only gold wrestling briefs with an orange centre and swirling trim, gold wristbands "
        "and tall gold boots. Black and gold, it looks like a champion expecting the whole arena to watch."},
  {"Em0082_002",  // Daring Gigas
        "A colossal giant built like a professional wrestler, its glossy black body swollen into slabs of muscle, "
        "its small head sunk between huge shoulders. Rose-pink rivets stud its chest, shoulders and thighs. Its "
        "face is a smooth cobalt-blue mask with the numeral XI on the brow, above a jaw cage with pink bars, and "
        "long straight hair falls from the back of its head in a rainbow, purple and red at the crown through "
        "orange and yellow to green at the tips. It wears pastel, rainbow-sheened briefs with a pink centre, pale "
        "teal wristbands and mint-green boots. Loud in every colour at once, it looks dressed to steal the show."},
  {"Em0082_003",  // Ultimate Gigas
        "A colossal giant built like a professional wrestler, its body swollen into slabs of muscle, its small "
        "head sunk between huge shoulders, its skin chalk white, painted with bold red flame markings like kabuki "
        "paint, curling over its chest, shoulders and back and down its legs. Grey rivets stud its muscles. Its "
        "face is a smooth cobalt-blue mask with the numeral XI on the brow, above a jaw cage with red bars, and "
        "long straight red hair hangs from the back of its head. It wears black briefs, black wristbands and tall "
        "black boots. Pale as marble and painted for war, it looks at the peak of its strength."},
  {"Em0082_004",  // ?
        "A colossal giant built like a professional wrestler, its body swollen into slabs of muscle, its small "
        "head sunk between huge shoulders, the skin a deep purple-black painted with vivid green flame markings "
        "over its chest, back, arms and calves and studded with green rivets. Its face is a smooth cobalt-blue "
        "mask with the numeral XI on the brow, above a jaw cage, and long straight bright green hair hangs from "
        "the back of its head. Unlike its kin it wears longer green trunks down to mid-thigh, edged with spiky "
        "white bands, with green-banded wristbands and tall green boots. Venom-green on bruise-dark skin, it "
        "looks poisonous as well as strong."},
  {"Em0083_000",  // Wild Beast
        "A big sandy-gold lion standing square on all fours, with a thick, shaggy brown mane, a long tail ending "
        "in a brown tuft, and pale, almost white eyes in a heavy, scowling face. A black iron collar engraved "
        "with patterns rings its neck under the mane, and chains hang from it, one running down to a huge black "
        "iron ball wider than the lion's head. Set into the back of that ball is the Shadow's face: a smooth "
        "cobalt-blue mask, calm and expressionless, with the numeral XI on its brow. The lion of the Strength "
        "card, it stands proud and sullen, shackled like a convict to its own mask."},
  {"Em0083_001",  // Enslaved Beast
        "A big lion standing square on all fours, its body the dark green of weathered bronze, as if cast for a "
        "temple gate, with a thick, shaggy mane of ashen grey, a long tail ending in a grey tuft, and pale, cold "
        "eyes. An engraved black iron collar rings its neck, and chains hang from it, one running down to a huge "
        "black iron ball wider than the lion's head. Set into the back of that ball is the Shadow's face: a "
        "smooth cobalt-blue mask, calm and expressionless, with the numeral XI on its brow. It looks like a "
        "guardian statue come to life to find itself in chains."},
  {"Em0083_002",  // Feral Beast
        "A big lion standing square on all fours, its body dusky purple, with a thick, shaggy mane of pure black, "
        "a long tail ending in a black tuft, and small eyes burning red in a dark face. A bronze-trimmed collar "
        "engraved with patterns rings its neck under the mane, and dark iron chains hang from it, one running "
        "down to a huge black iron ball wider than the lion's head. Set into the back of that ball is the "
        "Shadow's face: a smooth cobalt-blue mask, calm and expressionless, with the numeral XI on its brow. Dark "
        "as a moonless night, with ember eyes, it looks savage and only barely held."},
  {"Em0083_003",  // Nemean Beast
        "A big white lion standing square on all fours, its body pale grey-white as marble, with a thick, shaggy "
        "mane of olive-gold, a long tail ending in an olive tuft, and piercing yellow eyes. A silver collar "
        "engraved with patterns rings its neck, and bright steel chains hang from it, one running down to a huge "
        "cracked grey stone ball wider than the lion's head. Set into the back of that ball is the Shadow's face: "
        "a smooth cobalt-blue mask, calm and expressionless, with the numeral XI on its brow. Pale and gleaming, "
        "it looks like the lion of legend whose hide no blade could pierce, chained all the same."},
  {"Em0083_004",  // ?
        "A big lion standing square on all fours, its body a rich mustard gold, with a thick, wild mane streaked "
        "in black and bright yellow like a storm cloud shot with lightning, a long tail ending in a black and "
        "yellow tuft, and glowing yellow eyes. An engraved silver collar rings its neck, and steel chains hang "
        "from it, one running down to a huge cracked grey stone ball wider than the lion's head. Set into the "
        "back of that ball is the Shadow's face: a smooth cobalt-blue mask, calm and expressionless, with the "
        "numeral XI on its brow. Bold and electric, it looks the fiercest of its chained kind."},
  {"Em0084_000",  // Shadow of the Abyss
        "A monstrous heap of a creature, many times a person's size, squatting low like a giant toad: a black "
        "mound of lumpy, glistening flesh streaked with blood red. Almost its whole front is a gaping mouth, "
        "ringed with rows of blunt red teeth, its ribbed red gullet running back to a dangling red uvula and a "
        "fat red tongue lolling on its lower jaw. A cluster of glossy red bulbous eyes sits along its brow, and "
        "stubby clawed feet with red talons poke out at the sides. Dozens of swords stand thrust into its back. "
        "It sits wide open and waiting, a pit that has swallowed many before you."},
  {"Em0091_000",  // Black Raven
        "A large black raven, its ragged wings spread wide, gripping the iron handle of a hanging lantern in its "
        "talons: a brass-framed lantern with a single white candle inside, swinging beneath it as it flies. It "
        "has a heavy hooked beak held slightly open and dusky black feathers that fray at every edge. Strapped "
        "across its breast by thin metal bands is its mask, a rust-orange plate with one round black eyehole at "
        "the centre ringed by grooves, the numeral IX above it and a grille of slits below. The Hermit's lantern "
        "carried by a bird of ill omen, it looks like a guide you should not follow."},
  {"Em0091_001",  // Will O' Wisp Raven
        "A big black raven standing upright on the handle of a hanging lantern, its heavy hooked beak half open "
        "and its wings spread wide, the long feathers of its wings and trailing tail burning from black through "
        "crimson and orange to ragged tips of flame yellow, as if the bird were catching fire at the edges. Below "
        "its claws swings a bronze-framed lantern holding one white candle. Strapped across its breast with steel "
        "bands is its mask, a rust-orange plate with one round black hole ringed by grooves, the numeral IX above "
        "and slits below. An omen bird bearing a light for the dead, it looks hungry and spiteful."},
  {"Em0091_002",  // Ruthless Ice Raven
        "A big black raven standing upright on the handle of a hanging lantern, its heavy hooked beak half open "
        "and its wings spread wide, the long feathers of its wings and trailing tail shading from black through "
        "deep violet to jagged tips of icy sky blue, like feathers rimed with frost. Below its claws swings a "
        "cold grey steel lantern holding one white candle. Strapped across its breast with steel bands is its "
        "mask, a rust-orange plate with a single round black hole ringed by grooves, the numeral IX above it and "
        "slits below. The fire-tipped raven's cold twin, it looks just as cruel, its light chill and colourless."},
  {"Em0091_003",  // Amenti Raven
        "A raven drained entirely of colour, beak, legs and every feather a pale ghostly white, standing upright "
        "on the handle of a hanging lantern with its ragged wings spread wide and its long tail trailing behind. "
        "Below its claws swings a black iron lantern holding one white candle. The only colour on it is the mask "
        "strapped across its breast with steel bands, a rust-orange plate with a single round black hole ringed "
        "by grooves, the numeral IX above it and slits below. A white bird out of the land of the dead, it stands "
        "stiff and watchful, like a guide waiting for a soul to follow its light."},
  {"Em0092_000",  // Phantom Mage
        "A gaunt phantom floating upright inside a hooded cloak of shabby beige cloth, its hem cut into ragged "
        "points, the back sewn shut down its whole length with a line of big black cross-stitches, like a rag "
        "doll's seam. In the hood's shadow sits a rust-orange mask with a single round black hole, the numeral IX "
        "above and a grille of slits at the chin. A gold chain crosses its ribbed black chest, a brass lantern "
        "with one white candle hangs below, and two long, spindly black legs dangle beneath, tapering to points. "
        "Threadbare and patched like a cast-off rag, it hovers hunched and furtive."},
  {"Em0092_001",  // Phantom Master
        "A gaunt phantom floating upright inside a hooded black cloak lined in dark purple and edged in grey, the "
        "cloak spreading wide from its shoulders like folded bat wings, its hem split into long ragged points "
        "that end in arrowhead barbs. In the hood's shadow sits a rust-orange mask with a single round black "
        "hole, the numeral IX above and a grille of slits at the chin. A silver chain crosses its ribbed black "
        "chest, a dark iron lantern with one white candle hangs below, and two spindly black legs dangle beneath. "
        "Sleek and barbed where its kin is ragged, it looks like a sorcerer grown sure of its power."},
  {"Em0092_002",  // Phantom Lord
        "A gaunt phantom floating upright inside a rich hooded cloak of emerald green, lined in dark wine red and "
        "trimmed with gold braid, its pointed hem hung all round with gold-capped green teardrop gems. In the "
        "hood's shadow sits a rust-orange mask with a single round black hole, the numeral IX above and a grille "
        "of slits at the chin. A gold chain crosses its ribbed black chest, and below it hangs an ornate gold "
        "lantern with curling arms and dangling green gems around one white candle; two spindly black legs dangle "
        "beneath. Dressed like a court magician in jewels, it floats lordly and still."},
  {"Em0092_003",  // Phantom King
        "A gaunt phantom floating upright inside a full, bell-shaped hooded cloak of creamy ivory, edged all "
        "round in soft lavender, its unbroken hem flaring wide and only a little frayed and nicked. In the hood's "
        "shadow sits a rust-orange mask with a single round black hole, the numeral IX above and a grille of "
        "slits at the chin. Its ribbed body and its two long, spindly legs are pale silver-white, a gold chain "
        "crosses its chest, and below hangs a gold lantern with a small pair of feathered wings, one white candle "
        "inside. Pale and stately, it glides like a ghostly king on a solemn errand."},
  {"Em0092_004",  // ?
        "A gaunt phantom with a dark teal body and long, thin teal arms and legs, wrapped in a plum-purple hood "
        "and short capelet from which long purple stoles hang in strips almost to its feet, each embroidered with "
        "twisting gold glyphs. Gold-capped red teardrop gems dangle from the capelet's points. In the hood's "
        "shadow sits a rust-orange mask with a single round black hole, the numeral IX above and a grille of "
        "slits at the chin. A gold chain crosses its chest above an ornate gold lantern set with a red gem. "
        "Draped in written spells, it hangs like a priest of some forbidden rite."},
  {"Em0093_000",  // Resentful Surveillant
        "A colossal disembodied head resting on the ground, a stern charcoal face with a heavy brow and grim, "
        "downturned mouth, two rust-red stripes running from its crown down past its eyes. Its eyes are dark blue "
        "orbs ringed in pale yellow-green, and a long mane of blood-red hair pours from its scalp and spreads "
        "across the floor behind it like a cloak. Three more blue eyeballs float above its head, a black crow "
        "perched on each with wings flung wide. Pinned to the middle of its brow by silver spikes is a small "
        "copper-orange mask with one round hole, marked IX. Unblinking, it broods like an omen of death."},
  {"Em0093_001",  // Fate Seeker
        "A colossal disembodied head resting on the ground, a stern slate-grey face with a heavy brow and grim, "
        "downturned mouth, two pale grey stripes slanting from its crown past its eyes. Its eyes are glossy "
        "magenta orbs with violet rings, and a long mane of ash-grey hair pours from its scalp and spreads behind "
        "it like a dusty shroud. Three more magenta eyeballs float above its head, a black crow perched on each "
        "with wings flung wide. Pinned to its brow by silver spikes is a small copper-orange mask with one round "
        "hole, marked IX. All dull grey but for those vivid eyes, it watches with the patience of fate."},
  {"Em0093_002",  // Arcanist Decapitator
        "A colossal disembodied head resting on the ground, a stern charcoal face with a heavy brow and grim, "
        "downturned mouth, its skin plain and unstriped. Its eyes are bulging cream eyeballs with bright sky-blue "
        "irises, staring wide, and a long mane of straw-blond hair pours from its scalp and spreads across the "
        "floor behind it. Three more cream eyeballs with blue irises float above its head, a black crow perched "
        "on each with wings flung wide. Pinned to its brow by silver spikes is a small copper-orange mask with "
        "one round hole, marked IX. With its pale gold mane and wide stare, it looks haughty and startled at "
        "once."},
  {"Em0093_003",  // Appropriating Noble
        "A colossal disembodied head resting on the ground, its face and long, spreading mane both a pale lilac "
        "white, as if bled of all colour, the brow heavy and the mouth grim and downturned. From its eyes, black "
        "orbs with blood-red centres, two thick streaks of dark red run down its cheeks to the jaw like tears of "
        "blood. Three more black eyeballs with red centres float above its head, each with a white crow perched "
        "on top, wings flung wide. Pinned to its brow by silver spikes is a small copper-orange mask with one "
        "round hole, marked IX. Ghost-pale and weeping blood, it looks endlessly mournful."},
  {"Em0101_000",  // Bronze Dice
        "A single giant die, a heavy cube with thick, bevelled charcoal-black edges framing dark grey faces. On "
        "one face is bolted its mask, a glossy green oval held by six silver pins: two black spiral eyes stacked "
        "one above the other, a small X scratched beside them and a wide black crescent grin, a dizzy, lopsided "
        "leer. A side face shows two bright green pips joined by a green line, and the face behind the mask "
        "carries a gold skull and crossbones. Squat, dark and grinning, it has the sly, lopsided cheer of a "
        "loaded die."},
  {"Em0101_001",  // Iron Dice
        "A single giant die, a heavy cube with thick, bevelled blood-red edges framing dark grey faces, some of "
        "them sculpted into shallow four-sided pyramids. On one face is bolted its mask, a glossy green oval held "
        "by six silver pins: two black spiral eyes stacked one above the other, a small X beside them and a wide "
        "black crescent grin. A side face shows two hot-pink pips joined by a pink line, and the face behind the "
        "mask carries a pale aqua skull and crossbones. Red-rimmed and loud with pink, it looks meaner than the "
        "plain dark die, a loaded throw waiting to land."},
  {"Em0102_000",  // Silver Dice
        "A pair of giant dice hovering side by side with a gap between them, each a heavy cube with thick, "
        "bevelled brassy olive-gold edges framing dark grey faces. Each wears the same mask bolted to its front, "
        "a glossy green oval held by silver pins: two black spiral eyes stacked one above the other, a small X "
        "beside them and a wide black crescent grin. Their side faces show two deep blue pips joined by a blue "
        "line, and their backs each carry a silver skull and crossbones. Twin grins side by side, they look like "
        "a matched throw that can only come up badly."},
  {"Em0102_001",  // Platinum Dice
        "A pair of giant dice hovering side by side with a gap between them, each a heavy cube of pale icy "
        "blue-grey, edges and faces alike, polished like frosted glass. Each wears the same mask bolted to its "
        "front, a glossy green oval held by silver pins: two black spiral eyes stacked one above the other, a "
        "small X beside them and a wide black crescent grin. Their side faces show two deep blue pips joined by a "
        "blue line, and their backs each carry a glossy black skull and crossbones. Cold and gleaming, the twins "
        "look expensive, and just as sure to come up deadly."},
  {"Em0103_000",  // Terror Dice
        "A single giant die with bevelled charcoal-black edges and dark grey faces, run through its middle by a "
        "huge, razor-thin black disc that circles it like a planet's ring, several times wider than the die and "
        "sharp all round. On its front is bolted its mask, a glossy green oval held by silver pins, with two "
        "black spiral eyes, a small X and a wide black crescent grin, the blade cutting straight across it. A "
        "side face shows two green pips joined by a line, the back a gold skull and crossbones. It looks like a "
        "die spinning fast enough to slice anything near it."},
  {"Em0103_001",  // Curse Dice
        "A single giant die with bevelled blood-red edges and dark grey faces sculpted into shallow pyramids, run "
        "through its middle by a huge, razor-thin crimson disc that circles it like a planet's ring, several "
        "times wider than the die and sharp at every edge. On its front is bolted its mask, a glossy green oval "
        "held by silver pins, with two black spiral eyes, a small X and a wide black crescent grin, the blade "
        "slicing across it. A side face shows two hot-pink pips joined by a line, the back a pale aqua skull and "
        "crossbones. All red and pink, it looks like a curse spinning on its axis."},
  {"Em0104_000",  // Death Dice
        "Two giant dice hanging one above the other with a wide gap between them, each a cube with bevelled "
        "brassy olive-gold edges and dark grey faces. Through the gap runs a huge, razor-thin olive-gold disc, "
        "many times wider than the dice, like a planet's ring. Each die wears the same mask on its front, a "
        "glossy green oval held by silver pins, with two black spiral eyes, a small X and a wide black crescent "
        "grin. Their sides show two deep blue pips joined by a line, their backs silver skulls and crossbones. "
        "Two grins stacked round a blade, it hangs like a bad throw about to fall."},
  {"Em0104_001",  // Reckoning Dice
        "Two giant dice hanging one above the other with a wide gap between them, each a cube of pale icy "
        "blue-grey, polished like frosted glass. Through the gap runs a huge, razor-thin disc of the same frosty "
        "blue, many times wider than the dice, like a planet's ring. Each die wears the same mask on its front, a "
        "glossy green oval held by silver pins, with two black spiral eyes, a small X and a wide black crescent "
        "grin. Their sides show two deep blue pips joined by a line, their backs glossy black skulls and "
        "crossbones. Cold and gleaming, it hangs over you like a final reckoning."},
  {"Em0105_000",  // Flowing Sand
        "A tall, gangly hourglass that walks: its body is two swollen bulbs of pale lavender glass pinched to a "
        "narrow waist, bound by cream-white metal straps studded with plum rivets. Long, thin charcoal-black arms "
        "hang from the top bulb down to the lower bulb, and two spindly black legs carry the lower one, so it "
        "stands like a stooped, headless man. Its mask, a shallow green dome with black markings, sits pinned on "
        "its crown, face to the sky. Round its waist turns a wide, flat olive-gold ring engraved with strange "
        "lettering and fringed with feather-like blades. It looks patient and vacant, a clock with all the time "
        "it needs."},
  {"Em0105_001",  // Ochlocratic Sand
        "A tall, gangly hourglass that walks: its body is two swollen bulbs of rose-red glass pinched to a narrow "
        "waist, bound by cream metal straps studded with plum rivets. Long, thin charcoal-black arms hang from "
        "the top bulb down to the lower bulb, and two spindly black legs carry the lower one, so it stands like a "
        "stooped, headless man. Its mask, a shallow green dome with black markings, sits pinned on its crown, "
        "face to the sky. Round its waist turns a wide, flat magenta ring engraved with lettering and fringed "
        "with olive and pink feather-like blades. Flushed red, it looks hotter-tempered, a clock running out of "
        "patience."},
  {"Em0105_002",  // Rampaging Sand
        "A tall, gangly hourglass that walks: its body is two swollen bulbs of deep cobalt-blue glass pinched to "
        "a narrow waist, bound by slate-grey straps studded with gold rivets. Long, thin charcoal-black arms hang "
        "from the top bulb down to the lower bulb, and two spindly black legs carry the lower one, so it stands "
        "like a stooped, headless man. Its mask, a shallow green dome with black markings, sits pinned on its "
        "crown, face to the sky. Round its waist turns a wide, flat navy ring inscribed in gold and fringed with "
        "dark feather-like blades. Dark and glossy, it looks like a clock that never runs down."},
  {"Em0105_003",  // Eternal Sand
        "A tall, gangly hourglass that walks: its body is two swollen bulbs of pearly silver-white glass pinched "
        "to a narrow waist, bound by pale tan straps studded with grey rivets. Unlike its dark-limbed kin, its "
        "long, thin arms and spindly legs are ivory cream, the arms hanging from the top bulb down to the lower "
        "bulb, so it stands like a stooped, headless man of bone. Its mask, a shallow green dome with black "
        "markings, sits pinned on its crown. Round its waist turns a wide, flat cream ring engraved with "
        "lettering and fringed with pale feather-like blades. Ghostly pale all over, it looks as if it could wait "
        "forever."},
  {"Em0111_000",  // Cruel Greatsword
        "A giant arm of rough brown and tan masonry rising straight out of a dark earthen mound, its stone hand "
        "lifted high, fingers together and palm forward like a hand raised to swear an oath, a carved teal band "
        "around the wrist. Standing upright before it, hilt down and point to the sky, floats a huge sword: a "
        "broad steel blade, a carved bronze-brown crossguard and grip, a pale lavender gem in the pommel near the "
        "ground. On the guard sits its mask, a grey-green shield bearing a bold black cross and the numeral VIII. "
        "Stern and monumental, it stands like a crusader's grave marker sworn to judge."},
  {"Em0111_001",  // Conviction Sword
        "A giant arm of rough blue-grey masonry rising straight out of a black earthen mound, its stone hand "
        "lifted high, fingers together and palm forward like a hand raised to swear an oath, a carved gold band "
        "around the wrist. Standing upright before it, hilt down and point to the sky, floats a huge sword: a "
        "broad, icy pale-blue blade, a black crossguard and grip, a magenta gem in the pommel near the ground. On "
        "the guard sits its mask, a grey-green shield bearing a bold black cross and the numeral VIII. Cold and "
        "blue, it stands as unbending as a vow that will not be taken back."},
  {"Em0111_002",  // Judgment Sword
        "A giant arm of rough, mossy green masonry rising straight out of a dark green earthen mound, its stone "
        "hand lifted high, fingers together and palm forward like a hand raised to swear an oath, a carved bronze "
        "band around the wrist. Standing upright before it, hilt down and point to the sky, floats a huge sword: "
        "a broad, bright sky-blue blade, a carved olive-gold crossguard and grip, a magenta gem in the pommel "
        "near the ground. On the guard sits its mask, a grey-green shield bearing a bold black cross and the "
        "numeral VIII. Overgrown and ancient, it looks like an executioner's monument nobody tends any more."},
  {"Em0111_003",  // Doom Sword
        "A giant arm of pale grey, faintly lilac masonry rising straight out of a slate-grey mound, its stone "
        "hand lifted high, fingers together and palm forward like a hand raised to swear an oath, a carved teal "
        "band around the wrist. Standing upright before it, hilt down and point to the sky, floats a huge sword: "
        "a broad, gleaming silver-blue blade, a black crossguard and grip, a magenta gem in the pommel near the "
        "ground. On the guard sits its mask, a pale shield bearing a bold black cross and the numeral VIII. Pale "
        "as a tombstone, it stands over the ground like a sentence already passed."},
  {"Em0112_000",  // Heat Balance
        "A towering black iron cross, its foot sharpened to a stake, hung as a giant pair of scales: from each "
        "arm a chain carries a shallow pan, the left one fiery red, the right one sky blue, hanging level and "
        "evenly balanced. Behind the cross turns a spoked wheel split down the middle, its left half bright red "
        "and its right half blue, black thorns jutting from its rim. At the crossing sits its mask, a grey-green "
        "shield bearing a bold black cross and the numeral VIII, pinned by silver studs. Fire weighed against "
        "ice, it hangs rigid and impartial, a machine built only to judge."},
  {"Em0112_001",  // Sky Balance
        "A towering black iron cross, its foot sharpened to a stake, hung as scales whose pans do not match: on "
        "the left a violet chain carries a deep, pointed cone of purple and blue ribs, and on the right a green "
        "chain carries a stepped green bowl fading to yellow at its base. Behind the cross turns a spoked wheel "
        "split down the middle, violet on the left and green on the right, black thorns jutting from its rim. At "
        "the crossing sits its mask, a grey-green shield bearing a bold black cross and the numeral VIII. "
        "Lopsided, it looks like a judge weighing things that cannot be compared."},
  {"Em0112_002",  // World Balance
        "A towering black iron cross inlaid with thin gold lines, its foot sharpened to a stake, hung as a giant "
        "pair of golden scales, a shallow gold pan swinging on a gold chain from each arm. Behind it turns a "
        "grand double wheel of gold, an inner ring and a wider outer ring joined by spokes, its rim set all round "
        "with silver spearheads. At the crossing sits its mask, a grey-green shield bearing a bold black cross "
        "and the numeral VIII, pinned by silver studs. Richer and grander than its iron kin, it hangs in perfect "
        "balance like the last arbiter of everything that exists."},
  {"Em0112_003",  // Light Balance
        "A towering cross that shimmers in pastel iridescence, pale aqua, soft lilac and buttery yellow, warming "
        "to coral at the stake of its sharpened foot. From its arms hangs a pair of scales, a shallow "
        "silvery-blue pan on a silver chain at each side. Behind it turns a golden wheel with copper rivets, long "
        "golden spikes radiating from its rim like the rays of a sun. At the crossing sits its mask, a grey-green "
        "shield bearing a bold black cross and the numeral VIII. Bright and almost holy, it hangs like a sunburst "
        "over an altar, as pitiless as its darker kin."},
  {"Em0113_000",  // Order Giant
        "A towering giant built like a crumbling castle keep, its body and huge, blocky arms all stacked courses "
        "of weathered tan and brown stone, its shoulders rising as square turrets on either side of a small "
        "broken tower for a head. Sunk in that tower is a tiny pale green shield mask marked with a black cross, "
        "ringed by a half-wheel of iron spikes. Down its front hangs an enormous broadsword, point to the ground, "
        "its carved copper-brown hilt at its throat, and near the point dangles a small black cross carrying "
        "golden scales. It looms like a fortress come to pass sentence."},
  {"Em0113_001",  // Merciless Judge
        "A towering giant built like a castle keep of blue-violet bricks with teal mortar, its body and huge, "
        "blocky arms all masonry, its shoulders rising as square turrets on either side of a small broken tower "
        "for a head. Sunk in that tower is a tiny pale shield mask marked with a black cross, framed by a gold "
        "crescent collar bristling with blue spikes. Down its front hangs an enormous broadsword, point to the "
        "ground, blade and hilt in cold teal-blue with a magenta gem in the pommel, and near the point dangles a "
        "small cross carrying golden scales. It stands like a stern judge carved from a fortress wall."},
  {"Em0113_002",  // ?
        "A towering giant built like a castle keep overgrown with moss, its body and huge arms grey stone thick "
        "with bright green, its shoulders rising as square turrets on either side of a small broken tower for a "
        "head. Sunk in that tower is a tiny pale shield mask marked with a black cross, framed by a carved wheel "
        "of pale silver set with short spikes. Down its front hangs an enormous steel broadsword, point to the "
        "ground, with an olive-gold hilt and a purple gem in the pommel, and near the point dangles a small cross "
        "carrying golden scales. It stands like a ruin still keeping order."},
  {"Em0113_003",  // Void Giant
        "A towering giant built like a frost-pale castle keep of white and soft lavender bricks, its body and "
        "huge, blocky arms all masonry, its shoulders rising as square turrets on either side of a small broken "
        "tower for a head. Sunk in that tower is a tiny pale shield mask marked with a black cross, framed by "
        "gold spikes, one shooting straight up. Down its front hangs an enormous broadsword, point to the ground, "
        "with a pale teal hilt and a magenta gem in the pommel, and near the point dangles a small silvery cross "
        "carrying pale scales. It stands like a judge from a merciless heaven."},
  {"Em0113_004",  // ?
        "A towering giant built like a castle keep melting from within, its body and huge arms black bricks with "
        "molten orange seams glowing between them, its shoulders rising as square turrets on either side of a "
        "small broken tower for a head. Sunk in that tower is a tiny pale shield mask marked with a black cross "
        "in a gold crescent of spikes. Down its front hangs an enormous broadsword, point down, its blade glowing "
        "orange under a grey iron hilt with an amber gem, and near the point dangles a small dark cross carrying "
        "golden scales. It stands like a furnace that has learned to judge."},
  {"Em0121_000",  // Deviant Convict
        "A hulking bull-man of hard black muscle, standing hunched with its knees bent and its chin lifted, huge "
        "arms and swollen thighs tapering into backward-jointed legs and hooves. A long, shaggy mane of sandy "
        "blond hair pours over its shoulders and back, a bib of brown fur covers its chest and belly. Short cream "
        "horns curl up from its head, and its face is a smooth grey-blue mask of a sleeping face, eyes peacefully "
        "shut, the numeral XII over the mouth. A silver collar rings its neck, heavy chains running from it to "
        "cuffs on both wrists. A shackled brute, it waits with eerie calm."},
  {"Em0121_001",  // Minotaur III
        "A hulking bull-man of hard black muscle, standing hunched with its knees bent and its chin lifted, huge "
        "arms and swollen thighs tapering into backward-jointed legs and hooves. A long mane of vivid violet hair "
        "falls over its shoulders above a bib of shaggy purple fur, and two tall tawny-gold horns, studded with "
        "rivets, sweep high above its head. Its face is a smooth grey-blue mask of a sleeping face, eyes shut, "
        "the numeral XII over the mouth. A black iron collar rings its neck, heavy black chains running from it "
        "to cuffs on both wrists. It looks like a chained beast with a showman's vanity."},
  {"Em0121_002",  // Minotaur II
        "A hulking bull-man of hard black muscle standing hunched with its knees bent and its chin lifted, "
        "swollen thighs tapering into backward-jointed legs and hooves. Its long mane flares red, orange and "
        "yellow like a blaze, over a bib of crimson fur, and its horns, banded deep red and gold, are swagged "
        "with strings of gold beads. Its face is a smooth grey-blue mask of a sleeping face, eyes shut, the "
        "numeral XII over the mouth. A gold collar and gold chains bind its neck and wrists, and a red and gold "
        "beaded collar-piece hangs across its upper chest. A gilded gladiator, it stands proud even in chains."},
  {"Em0121_003",  // Minotaur Nulla
        "A hulking bull-man drained of all colour, ashen grey from his hunched back and massive arms down to "
        "backward-jointed legs ending in hooves. A long white mane spills over his shoulders and down his back, "
        "and shaggy white fur covers his chest and belly. Two tall pale horns curve up from his skull. His face "
        "is a smooth grey-blue mask of a sleeping face, eyes shut and brow creased, the numeral XII over the "
        "mouth. Silver chains run from a pale collar at his neck to cuffs at both wrists. The labyrinth's beast "
        "as a ghost of himself, he stands heavy and bowed, asleep inside his chains."},
  {"Em0121_004",  // ?
        "A hulking bull-man of hard navy-black muscle, hunched and massive in the arms, his backward-jointed legs "
        "ending in hooves. A long sky-blue mane falls over his shoulders and back above a bib of shaggy blue fur. "
        "Two great horns banded red and black curve up, with a third, smaller horn jutting from his brow. His "
        "face is a smooth grey-blue mask of a sleeping face, eyes shut, the numeral XII over the mouth. A red "
        "collar holds a breastplate of silver discs fringed with red beads, and blood-red chains run from it to "
        "his wrist cuffs. Horned three times over, he stands hunched, ready to charge."},
  {"Em0122_000",  // Jotun of Power
        "A grotesquely fat giant with dark charcoal skin, a vast round belly and four thick arms, perched astride "
        "a child's rocking horse far too small for him, built of weathered grey planks riveted together, with a "
        "jagged mane and long curved rockers. His small bald head wears a pale grey-blue mask of a sleeping face, "
        "brow furrowed, the numeral XII over the mouth. Purple-blue leather straps truss him at the throat, under "
        "the belly and at wrists, thighs and ankles, and two heavy rings pierce his chest, joined by a sagging "
        "silver chain. Bloated, bound and rocking, he sits like a punishment dressed as a nursery toy."},
  {"Em0122_001",  // Jotun of Blood
        "A grotesquely fat giant with dark charcoal skin, a vast round belly and four thick arms, perched astride "
        "a rocking horse far too small for him, its body of salmon-pink planks riveted together, with a jagged "
        "mane and long pink rockers. His small bald head wears a pale grey-blue mask of a sleeping face, brow "
        "furrowed, the numeral XII over the mouth. Olive-green straps studded with orange truss his neck, wrists, "
        "thighs and ankles, a maroon band circles under his belly, and two heavy rings pierce his chest, joined "
        "by a sagging blood-red chain. The sweet pink horse makes the bloated, shackled rider all the more "
        "unsettling."},
  {"Em0122_002",  // Jotun of Evil
        "A grotesquely fat giant with dark olive-drab skin, a vast round belly and four thick arms, perched "
        "astride a rocking horse far too small for him, built of dark gunmetal plates painted all over with "
        "staring gold and white eyes, with a mane of steel spikes. His small bald head wears a pale grey-blue "
        "mask of a sleeping face, brow furrowed, the numeral XII over the mouth. Gold bands truss his neck, "
        "wrists, thighs and ankles, collar and cuffs bristling with spikes, and two spiked rings pierce his "
        "chest, joined by a sagging gold chain. Gilded and spiked, he rides as if watched from every side."},
  {"Em0122_003",  // Genocidal Mercenary
        "A grotesquely fat giant with ghostly white skin, a vast round belly and four thick arms, perched astride "
        "a rocking horse far too small for him, built of pale mint-green, faintly pearly plates with a jagged "
        "mane and long curved rockers. His small bald head wears a darker grey mask of a sleeping face, brow "
        "furrowed, the numeral XII over the mouth. Dull teal straps truss his neck, belly, wrists, thighs and "
        "ankles, and two heavy rings pierce his chest, joined by a sagging blood-red chain, the only warm colour "
        "on him. Pale, swollen and bound, he sits on his toy horse like a corpse set out for show."},
  {"Em0123_000",  // Mighty Cyclops
        "A muscular man with dark grey skin hung upside down at the centre of a great steel wheel taller than a "
        "person. His booted ankles are clamped together and chained to the top of the rim, his arms bound behind "
        "his back, a silver harness of straps and rings across his chest. His head, at the bottom, is one huge "
        "blue eye, a small grey mask of a sleeping face set at its centre like a pupil. The wheel is a heavy ring "
        "of bolts and dark slots edged all round with spikes, eight barred spokes behind him. A one-eyed captive "
        "on a torture wheel, he hangs limp and watching."},
  {"Em0123_001",  // Mad Cyclops
        "A muscular man with charcoal skin and black boots hung upside down against a great round disc taller "
        "than a person. His ankles are clamped in a brass cuff and chained to the top, his arms bound behind his "
        "back, a brass harness across his chest. His head, at the bottom, is one huge yellow eye, a small grey "
        "sleeping mask at its centre like a pupil. The disc is deep violet painted with red flame-shaped petals "
        "around round black eyes, in a black rim of red panels and brass bolts ringed by violet studs, brass "
        "chains looping down. Gaudy and occult, he hangs like a carnival target."},
  {"Em0123_002",  // Fierce Cyclops
        "A muscular man with charcoal skin and black boots hung upside down against a great round disc taller "
        "than a person. His ankles are clamped in a steel cuff and chained to the top, his arms bound behind his "
        "back, a steel harness across his chest. His head, at the bottom, is one huge red eye, a small grey "
        "sleeping mask at its centre like a pupil. The disc is a shallow bowl of mustard gold etched with "
        "radiating lines, framed in a thick black rim pierced with slots and edged with silver spikes, silver "
        "chains looping down. The red eye glares out from the gold like an angry sun."},
  {"Em0123_003",  // Chaos Cyclops
        "A muscular man with chalk-white skin hung upside down against a great round disc taller than a person, "
        "bare but for black leather: a strapped harness across his chest and tight black briefs. His ankles are "
        "clamped in a black cuff and chained to the top, his arms bound behind his back. His head, at the bottom, "
        "is one huge red eye, a small grey sleeping mask at its centre like a pupil. The disc is deep crimson "
        "shaggy fur in a silver rim edged with golden spikes, pale gold chains looping down. White flesh on "
        "blood-red fur, he hangs like a sinner pinned up for display."},
  {"Em0123_004",  // ?
        "A muscular man with dark plum-purple skin hung upside down at the centre of a great wheel taller than a "
        "person. His booted ankles are clamped in a cobalt-blue cuff and chained to the top of the rim, his arms "
        "bound behind his back, a cobalt harness across his chest. His head, at the bottom, is one huge red eye, "
        "a small grey sleeping mask at its centre like a pupil. The wheel is a broad ring of icy, mottled "
        "sky-blue metal edged all round with blue spikes, eight barred spokes behind him, cobalt chains looping "
        "down its sides. Cold and stark, he hangs like a prisoner frozen mid-punishment."},
  {"Em0123_005",  // ?
        "A muscular man with dark purple skin hung upside down against a great round disc taller than a person. "
        "His booted ankles are clamped in a red cuff and chained to the top, his arms bound behind his back, a "
        "red harness across his chest. His head, at the bottom, is one huge teal-green eye, a small grey sleeping "
        "mask at its centre like a pupil. The disc is a bowl of glossy mint green warming to amber at its edge, "
        "in a bright green rim edged with red and green spikes, red chains looping down. Garish as a festive "
        "ornament, he hangs there a captive all the same."},
  {"Em0131_000",  // The Reaper
        "A tall, gaunt figure of death in a long double-breasted coat of black and crimson with brass buttons, "
        "its collar, sleeves and skirts torn into ragged tatters that trail around it in place of legs, all "
        "spattered with blood. Its head is a pale hood soaked red, one bulging, bloodshot eye staring out of one "
        "side, a rope cinched around its neck like a noose. Long chains cross its chest and loop over its "
        "shoulders. Its arms hang at its sides, each gloved hand gripping a revolver whose absurdly long silver "
        "barrel reaches nearly to the floor. Unhurried and silent, it has the stillness of something that always "
        "arrives."},
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
        "An absurd queen built around a huge riveted globe of dark slate-green metal, closed with gold latches "
        "and a gold medallion like a jewel box, framed by puffed teal silk sleeves and bloomers, spindly black "
        "legs ending in red high heels. From it rises an impossibly long black neck ringed with gold and hung "
        "with amethysts, a vast fan of cream, feather-like scallops dotted with gold stars spreading behind it "
        "like a peacock's tail. Her face is a cream crown-shaped mask, eyes closed, marked III. Thin black arms "
        "trail a sheer aqua veil, and she carries a gold-headed sceptre. Vain and grotesquely grand, she poses "
        "like a monarch on parade."},
  {"Em0522_000",  // Emperor
        "A stiff, towering king shaped like a walking shield: his body is one long rounded plate of teal-green "
        "studded with brass rosettes and emblazoned with a bold red cross, a small round red face with shut eyes "
        "at its foot. His head is a spiky purple crown-mask marked IV. His shoulders swell into ribbed teal puffs "
        "capped with brass and fringed with white tassels, a scarlet cape hangs behind, and long sleeves fall to "
        "white fur cuffs and black clawed hands, one gripping a long blue sword held low. Thin black legs end in "
        "curled, pointed shoes. Rigid as a tin soldier, he stands like authority with nothing inside it."},
  {"Em0531_000",  // Hierophant
        "A grotesque mock pontiff, two beings stacked into one. Below squats an enormously round white body, its "
        "face a small blue mask with a gaping mouth peering from a black hood, in a red brocade capelet, striped "
        "cyan breeches, black fishnets and red high heels, a gilded throne frame and a red banner of crossed keys "
        "at its hips. From its back rises a naked headless woman of white porcelain, arms spread, her breasts and "
        "buttocks huge and round, a golden tree studded with red jewels growing from her neck. Two white crosses "
        "stand beside it. Pompous and obscene, it holds that bare body aloft like a banner."},
  {"Em0532_000",  // Lovers
        "A giant heart of translucent red glass, caged in riveted brass bands like a corset of armour, spikes "
        "bristling along its top. Thick branching limbs spread from its sides like bare antlers or wings, shading "
        "from blood red to violet, and long drips run from heart and limbs as if it were melting. A column of "
        "small pink hearts runs down its front. On top, on a short black neck, sits a tiny pink mask with a sad, "
        "drooping face, VI on its brow. Inside it, dim through the glass, drift the signs of woman and man. "
        "Bleeding in its cage, it is love made heavy and sorrowful."},
  {"Em0541_000",  // Chariot
        "A battered old tank standing high on four walking legs, each one a full caterpillar track looped around "
        "toothed wheels, so the hull rides off the ground like a beast on stilts. It is painted in mottled desert "
        "camouflage of sand, brown and moss green. Its boxy turret has a wide square hatch in front where a gun "
        "should be, a staring red-rimmed eye painted on each side. Round headlamps flank the hull, and across its "
        "front runs a wide grinning mouth of red lips and white teeth. Lopsided and leering, it is a child's "
        "drawing of war brought to clanking, hungry life."},
  {"Em0542_000",  // Justice
        "A small, stubby knight hovering on wings, doll-like in plain steel armour, a red sash across its chest "
        "and a red belt at its waist. Its round great helm is cut by a black cross-shaped visor, two yellow eyes "
        "glinting behind it, VIII on the brow. Two big grey wings of riveted metal feathers fan from its back, "
        "and behind its head stands a gold disc of pleated rays embossed with scales and a cross, like a halo. A "
        "short sword hangs point-down beneath its feet. Apart from it floats a long camouflage-painted cannon "
        "barrel with a boxy breech. Earnest and stiff, it is a tin-toy crusader of judgement."},
  {"Em0543_000",  // Tank-Form Shadow
        "A tank and a knight joined into one machine: a camouflaged war machine of sand, brown and moss green "
        "standing high on four legs that are each a looping caterpillar track, a long cannon now jutting from its "
        "boxy turret. Staring red-rimmed eyes are painted on the turret's sides and a wide grin of red lips and "
        "white teeth across the hull. Slung underneath between the tracks hangs the little steel knight, "
        "cross-visored helm, red sash and short sword pointing down, grey wings of metal feathers spread wide and "
        "a gold sunburst disc behind its head. Loud and lumbering, it carries its own crusader into battle."},
  {"Em0551_000",  // Hermit
        "A hunched, towering beast of wire standing on four legs that are nothing but thick bundles of cables, "
        "red, blue, green, black and yellow, trailing loose across the ground. Brass collars gather each bundle, "
        "and above them the legs turn to dark scaly flesh arching into a black back traced with red circuit "
        "lines. Three black cylinders like old valves, printed with white lettering, jut from its shoulders. Its "
        "head hangs low in front, buried in a huge spiky mane of pale blue-grey spines, its face a small orange "
        "mask with one round black hole at its centre, like a single eye. It lurks, all static and eavesdropping."},
  {"Em0561_000",  // Fortune
        "A little brass mechanical beast crouched like a sphinx near the hub of an enormous flat bronze wheel, "
        "many times its size. Its scrolled golden body is riveted with gears and glass portholes, a grey dome "
        "rides on its back with a ribbed brass fan behind, and a long dark chain ending in a small spiked ball "
        "trails out like a tail. Its face is a green mask speckled with red, framed by a striped pharaoh's "
        "headdress. Across the disc beside it lies a long black block tapering to a needle-sharp silver point, "
        "the wheel's pointer. Small and watchful, it waits on a spin of chance."},
  {"Em0562_000",  // Strength
        "A tall, slender lady floating upright in a long cream gown that flares into a wide cone and ends in a "
        "point where her feet should be, with puffed white sleeves and a pink trim at the neckline. Her skin is "
        "jet black, long ash-blonde hair falls down her back, and her face is a smooth cobalt-blue mask with "
        "closed, sleepy eyes. One dark hand holds a single red rose. A great bouquet of roses, lilies and "
        "sunflowers tangled with vines swallows the lower gown. A pink ribbon swirls over her head like a halo, "
        "and spear-tipped iron railings run before her. Graceful and still, she is gentleness fenced in."},
  {"Em0571_000",  // Hanged Man
        "A massive grey-green brute strung beneath a steel girder like a carcass on a crane, his muscular body "
        "slung from hooks and straps, his arms spread wide, cuffed at wrists and ankles, with dark hands and "
        "heavy black boots. His head is a lavender-grey helmet marked with a numeral above a black, glassy face "
        "plate ringed in teal, like a diver's mask. Above, chains run up to two long brass beams stacked one over "
        "the other, each sprouting ragged sky-blue wings of jagged feathers. Strung between the ground and the "
        "sky, he hangs helpless and enormous."},
  {"Em0572_000",  // Statue
        "A life-size statue of a woman carved in pale grey stone, standing on a low plinth. A long veil covers "
        "her head and falls over her shoulders in heavy folds almost to her feet, over a plain, high-waisted "
        "gown. Her head bows slightly, her eyes are lowered and her face is serene, and her hands are pressed "
        "together in prayer before her chest. Smooth and unadorned, she is the quiet, sorrowful image of a holy "
        "mother, at peace in her prayer and eerie for standing where no statue should."},
  {"Em0581_000",  // Nyx Avatar
        "A dark, regal figure borne on two pairs of vast black feathered wings, wider than a house, their "
        "undersides veined with glowing electric-blue lines like cracks of lightning. At their centre is a "
        "slender, humanlike body: a pale, gaunt face with the faintest smile, framed by spiky black hair, under a "
        "tall flat-crowned black hat with a gold band. Its fitted coat of black and gunmetal armour glows with "
        "the same blue veins, long blade-like panels hanging to a point in place of legs. One clawed hand holds a "
        "long, slim silver sword with a gold hilt. Cold and terribly calm, it is death in a dress uniform."},
  {"Em0582_000",  // Nyx Core
        "A huge egg-shaped orb hanging at the heart of a vast black tangle, its shell a pearly swirl of pale sage "
        "green and bronze streaked like feathers or marbled silk, split down one side by a stepped zigzag seam. "
        "Long ribbons and torn sheets of jet-black matter spread from it like a burst flower or a ruined web, and "
        "from their ends reach dozens of thin, bony black arms ending in skeletal clawed hands, grasping in every "
        "direction. There is no face and no mask, only the cracked, shimmering core and its many withered hands. "
        "Silent and enormous, it feels less like a creature than the end of everything."},
  {"Em0601_000",  // ?
        "A gaunt, two-headed beast with a skull at each end of its body and no front or back. Each head is a long "
        "tan bone skull with a grin of jagged teeth and two glowing red bead eyes, crowned with long horns that "
        "sweep back like scythe blades. Between them stretches a hunched, heavily muscled body of sooty "
        "black-brown flesh, hung with dripping, shredded strands like wet rags, held up on four long, thin limbs "
        "that end in spindly clawed hands. It wears no mask. Bone and tar, it prowls whichever way it likes, "
        "every direction a face."},
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
        "glowing green eyes. He wears fine silver chainmail over gold-edged plate, a red leather strap across his "
        "chest, and a white tabard striped down the middle in red with a black star and glyph, cinched by a "
        "studded red belt. He carries a plain long sword. Heaven's foot soldier, he stands grim and unbending."},
  {"Ps0001_010",  // Asura
        "A towering demigod of Indian legend with blazing red skin, a powerful bare chest and six arms fanning "
        "from his shoulders, each ringed with gold bands. His head bears faces on three sides, the front one "
        "scowling with pale blue eyes under a tall spiked gold helmet. Broad gold shoulder plates join a gold "
        "collar, a thin gold chain loops across his chest and a white sash falls from one shoulder. A gold buckle "
        "shaped like a snarling beast's face holds a skirt of layered gold plates over patterned white cloth, "
        "gold rings stacked at his ankles. A warlike titan of old myth, he looks ready to strike."},
  {"Ps0001_020",  // Atavaka
        "A fearsome guardian deity of Buddhist lore with green skin, a lean, muscled bare torso and eight arms "
        "spreading around him like a wheel. His head is a cluster of scowling faces with blood-red eyes and a red "
        "mark on the brow, under spiky royal-blue hair and a gold diadem, a smaller head with a blue topknot "
        "rising on top. Silver hoops hang from his ears. White scarves stream over a blue sash, baggy white "
        "trousers and ornate gold knee guards. His hands carry a tall gold trident hung with a red tassel, a gold "
        "sword, a ritual sceptre and a long coiled rope. He is wrath turned to protection."},
  {"Ps0001_030",  // Attis
        "A slender, unsettling youth wrapped from neck to toe in worn tan bandages like a mummy, the wrappings "
        "outlining a lean, muscled body. A shaggy mop of blond hair spills from his head, and two short, dark "
        "curved horns rise through the bandage binding his brow. His teal-skinned face is crossed by pale bands, "
        "leaving narrow golden eyes showing, and his teal hands and feet carry the same stripes. Long ragged "
        "ribbons of bandage stream from his shoulders and heel, and one hand holds a small curved blade. The "
        "shepherd of the old myth who gave up his manhood for a goddess, he seems bound, sacrificed and quietly "
        "tragic."},
  {"Ps0001_040",  // Atropos
        "A tall, slim woman in a skin-tight black bodysuit finely pinstriped in grey, with black gloves and bare "
        "feet. Her head is swallowed by a tall grey cylinder of woven, interlocking lattice, like a basket or a "
        "cage, rising well above her crown and split down the front by a narrow gap. Through it you glimpse a "
        "pale face with glowing golden eyes and teal hair under a braided gold band. One hand holds a slender "
        "golden needle, and a long, thin black thread trails from her. The Fate who cuts the thread of life, she "
        "is cold, impersonal and hidden, a silent keeper of endings."},
  {"Ps0001_050",  // Ananta
        "An enormous serpent of Hindu myth whose seven cobra heads rise together from one trunk and fan out like "
        "the fingers of an opening hand. Each broad, flared hood is salmon-pink and ribbed in front, sea-blue "
        "scales behind marked with pale green rings, and each head stares down with small yellow eyes. Ornate "
        "gold bands clasp the necks together, and below them a gold collar with a hanging gold ornament holds a "
        "draped white cloth. Beneath, the body bends to the ground and becomes one long blue and pink tail "
        "stretching far away behind it. Upright and still, it feels ancient and vast, a being older than the "
        "world."},
  {"Ps0001_060",  // Anubis
        "A jackal-headed god of ancient Egypt, jet black from head to foot, sitting cross-legged in mid-air with "
        "his back straight. His long, narrow muzzle and two very tall, pointed ears give him a sharp, elegant "
        "silhouette, and his red-rimmed eyes have teal irises. A blue and white striped headcloth drapes behind "
        "his head in two flat lappets. A broad silver and gold collar with a red inner band circles his neck, "
        "silver bands ring his arms, and he wears a white pleated kilt tied with a teal sash. One hand holds up "
        "golden balance scales with two hanging pans. The weigher of hearts, he sits calm, aloof and utterly "
        "impartial."},
  {"Ps0001_070",  // Abaddon
        "A colossal mound of olive-green flesh, wider than it is tall, made almost entirely of a gaping mouth. "
        "Its lumpy hide is covered in small pointed warts, and the whole bulk slumps down behind like a melting "
        "hill. Near the top, two round yellow eyes and a flat nose sit above a vast open maw ringed with big, "
        "square white teeth, its throat a deep red cavern with a dangling uvula and a huge red tongue rolling at "
        "the bottom. Small clawed hands poke out at either side of its base. The abyss of the old scriptures "
        "given a face, it is a bottomless hunger ready to swallow anything whole."},
  {"Ps0001_080",  // Apsaras
        "A graceful celestial dancer with smooth pale blue skin and a slender, shapely figure, poised on bare "
        "toes. Her navy hair is pinned into two round buns under a silver circlet with a blue teardrop jewel, her "
        "heavy-lidded golden eyes calm, blue gems at her ears and throat. A skin-tight white leotard, wrapped "
        "across the chest and edged in silver, moulds her breasts and belly; below a belt of glossy blue "
        "teardrops, a short skirt of sheer mint-green silk shows the leotard cut high over her bare legs. A sheer "
        "green ribbon arcs over her head. She holds herself light and serene, plainly on show."},
  {"Ps0001_090",  // Arahabaki
        "A squat, chunky figure shaped like an ancient Japanese clay idol, cast all over in dark teal stone with "
        "a faint mottled sheen. Its big round head is dominated by two enormous goggle eyes, each shut to a thin "
        "glowing orange slit inside a spiky rim, above a small round open mouth, with a tall ornamental finial "
        "like a crown on top. The body is all bulging curves: wide rounded shoulders flaring into short ridged "
        "stumps of arms with small claws, two round swellings on the chest, a flared skirt-like waist and thick, "
        "bulbous legs. Heavy and unmoving, it keeps a strange, sleepy watch, an earthbound guardian older than "
        "memory."},
  {"Ps0001_100",  // Ara Mitama
        "A glossy, blood-red spirit shaped like a giant comma: a big round head that tapers down and curls into a "
        "long pointed tail, like the curved jewel of Japanese tradition. There is no body, only that smooth, "
        "plump teardrop of red, larger than a person's torso. Its face is pure rage: heavy, deeply furrowed "
        "brows, fierce white eyes outlined in black, a flared nose and a wide, grimacing mouth baring a solid row "
        "of clenched white teeth. The rough, wild half of the soul given shape, it is all hot temper with nowhere "
        "to hide."},
  {"Ps0001_110",  // Alice
        "A little girl with long, straight blonde hair, a fringe cut straight across her brow and a white "
        "headband, large amber eyes in a pale, doll-like face and small, unsmiling lips. She wears a royal purple "
        "dress with short puffed sleeves cuffed in white, a frilled white collar and a thin black ribbon at the "
        "throat. A broad white sash ties in a big bow at her back, a frilled white petticoat peeks below the full "
        "skirt, and she stands in black strapped shoes. Prim as a storybook child, her face is eerily blank and "
        "still, the calm of a doll that is not quite playing."},
  {"Ps0001_120",  // Alilat
        "A tall, double-pointed crystal of dusky rose stone standing on end, a six-sided column as tall as a "
        "person that narrows to a sharp point above and below. Deep red lines are cut into every face, each "
        "showing the same squat goddess idol: a domed head banded with stripes, two almond eyes, full round "
        "breasts, a narrow waist and wide hips over short, stubby legs. On each pointed end sits a ring within a "
        "ring crossed by a straight bar, like an unblinking eye. An ancient desert goddess worn down to a carved "
        "talisman, it stands mute and sacred, older than any temple."},
  {"Ps0002_000",  // Inugami
        "A black dog's head on an absurdly long, thin white body that hangs straight down like a strip of cloth, "
        "ending far below in a long, pale, feathery tail. The head is jet black with tall pointed ears, small "
        "glaring red eyes, a tangled red sigil on its brow and a grinning mouth crammed with sharp white teeth "
        "and red gums. Just under the neck two thin white forelegs dangle, tipped with black claws, and far down "
        "the body two small hind legs hang limp. The dog spirit of folk curses, it is a grin on a ribbon, hanging "
        "there waiting to be set loose on someone."},
  {"Ps0002_010",  // Incubus
        "A wiry little demon with dusty pink skin stretched over a scrawny, rib-showing body, his long spindly "
        "arms and shins darkening to black at the claws. His bald, egg-shaped head sprouts pointed ears and two "
        "long curling antennae, and his face is all leer: narrowed yellow eyes, a jutting chin and a wide, toothy "
        "grin. Tall bat wings rise high over him, pink bony struts with black membrane. He wears only skimpy "
        "black briefs, a curved red horn jutting from the front of them, and a whip-thin tail ends in an "
        "arrowhead. The night visitor who preys on sleepers, he grins with greasy, gleeful mischief."},
  {"Ps0003_000",  // Virtue
        "An angel that seems carved whole from dark green stone flecked like weathered bronze, a statue come "
        "loose from its plinth. She hangs in the air with her body in a gentle twist, hips turned, one knee drawn "
        "forward and her bare feet pointed down, her arms folded tight across her breasts and her head turned "
        "aside and lowered. She is nude, her curves smooth as polished sculpture, with short, softly waved hair. "
        "A pair of long, narrow feathered wings sweeps down from her shoulders almost to her feet, the same green "
        "stone as the rest of her. Modest, solemn and still, she holds herself inward as if in prayer."},
  {"Ps0003_010",  // Vasuki
        "A small, many-armed figure perched on top of an immensely long, thin snake's tail of purple scales that "
        "stretches far below him to a needle point, so he seems a head and shoulders. Around his chest a wheel of "
        "bare arms fans out on every side, each banded in grey and gold bracers. His pale face is painted purple "
        "around the eyes, long red hair falling behind. Above it rise a gold crown, a grey cobra's hood painted "
        "with two staring green eyes, a gold spire and two long gold feelers. The serpent king who served as the "
        "gods' churning rope, he looks strange, ceremonial and unblinking."},
  {"Ps0003_020",  // Valkyrie
        "A warrior maiden on a blood-red horse, her long cape streaming behind. She sits tall in a fitted brown "
        "leather bodysuit plated with silver scale armour down the chest and hips, a long silver sword in each "
        "hand. Her golden hair is swept up into a tall, curling crest, her red lips set off by a silver half-mask "
        "whose sides flare into little wings. The horse is crimson, with a flame-like red mane and tail tipped in "
        "gold, and a round red shield slung at its side. The chooser of the slain, she rides poised, proud and "
        "ready to charge."},
  {"Ps0003_030",  // Vishnu
        "A four-armed god with smooth golden-yellow skin and a lean build, standing tall and barefoot. His long "
        "black hair is drawn up into a topknot under a tall silver crown, framing a calm, handsome face with teal "
        "eyes and the hint of a smile. A braided silver cord loops around his body and curls up behind his "
        "shoulders into two great scrolls. A pale blue wrap skirt covers his hips. His four hands hold a heavy "
        "silver mace, a pink spiral conch, a silver ring-shaped discus and a pink lotus. The preserver of the "
        "world, he stands at ease, serene and quietly certain."},
  {"Ps0003_040",  // Uriel
        "An archangel with smooth pale blue skin, a straight, upright bearing and two great wings arching from "
        "his back, their tips sweeping down past his knees. His youthful face is stern under short, neat brown "
        "hair, his golden eyes cool and level. He wears fitted magenta armour under a long white tabard edged in "
        "gold and marked with gold crosses down its length, bound by a gold sash whose ends hang to his shins. In "
        "one hand he holds a long sword with a gold hilt, its blade shading from blue to violet. Upright and "
        "unbending, he looks like a judge who has already weighed you."},
  {"Ps0004_000",  // Eligor
        "A demon knight mounted on a dark navy horse, sealed head to foot in blood-red plate armour, every limb "
        "sheathed in stacked, ridged plates. His closed helm is crowned with two curving brown ram's horns, two "
        "small white eyes glinting through its visor slit, and a shaggy grey fur mantle bunches over his "
        "shoulders. A long dark purple cape hangs behind him, and he levels a long, thin spear. His horse is near "
        "black, with a wild, pale silvery-green mane and tail. A duke of hell at the head of his host, he sits "
        "rigid and faceless in his shell, a war machine waiting for the charge."},
  {"Ps0004_010",  // Angel
        "A winged woman, slim and long-legged, bound more than dressed. A dark band blindfolds her eyes, printed "
        "with a single open eye, and below it her red lips are just parted. A black collar rings her throat, and "
        "a heavy chain drops from it past her knees. Her outfit is little more than black straps: a narrow band "
        "pulled tight across her breasts, leaving their undersides bare, a wide belt at her waist and tiny black "
        "shorts. Wavy dark blonde hair falls loose, and two broad white-grey wings spread wide from her back. "
        "Heaven's lowest servant, she stands blind and chained, at once pure and provocative."},
  {"Ps0005_000",  // Okuninushi
        "A slim young man of ancient Japan with a fine-boned, gentle face, calm brown eyes and long straight "
        "black hair that hangs past his shoulders in front, the rest looped into two round coils on top of his "
        "head and held by a thin red headband. He wears armour of small grey metal plates laced in rows with red "
        "cords over a white robe and baggy white trousers. A necklace of curved orange jewels sits at his throat, "
        "and he holds a long, straight, double-edged sword. The god who built a land and healed its creatures, he "
        "looks mild, patient and quietly capable."},
  {"Ps0005_010",  // ?
        "A tall, lean god with dusky purple skin and a hard, muscled body, standing barefoot and nearly bare. His "
        "long black hair falls past his shoulders from under a gold helmet, two tall, slender gold horns rising "
        "straight up from it like blades. Beneath it his eyes glow a cold, pale white in a grim, set face. A "
        "white cloth is wrapped low on his hips, and a long white cloak falls from his shoulders to the ground "
        "behind him. He grips a long, slender dark spear. The all-father of the northern gods, he stands cold, "
        "remote and severe, his blank white eyes giving nothing away."},
  {"Ps0005_020",  // Ose
        "A tall leopard-man with tawny spotted fur over a lean, sharply muscled body, his chest and belly bare "
        "and a long spotted tail behind. His cat's face rises out of a tall green collar, teal eyes narrowed and "
        "a wide, toothy grin under his whiskers. A short green cape over his shoulders becomes a long cloak to "
        "the ground, green outside and dark wine-red within. A narrow silver plate covers only his groin, and a "
        "gold sheath hangs at his side. He holds a needle-thin rapier. A leopard duke of hell, he carries himself "
        "like a cocky duellist with time to toy with you."},
  {"Ps0005_030",  // Oni
        "A huge, burly ogre with brick-red skin, slab-like shoulders and thick, bulging arms and legs. Two short "
        "black horns jut from his head beside a single tall spike of blond hair, and his face is a scowling demon "
        "mask come alive: glowing blue eyes under a heavy brow, a hooked nose and a broad mouth crammed with "
        "jagged grey fangs. A short navy cape with a white collar covers his shoulders; baggy navy shorts sit "
        "under a dark sash. He swings a huge iron cleaver on a long pole. The ogre of folk tales, he looks surly, "
        "heavy and spoiling for a fight."},
  {"Ps0005_040",  // Oberon
        "A slender fairy king dressed like a toy soldier, framed by four huge butterfly wings, black veined with "
        "green and dotted with yellow spots, the lower pair trailing long swallowtails nearly to his ankles. His "
        "face is pale as porcelain, with ice-blue eyes and a faint, superior smile, straight black hair falling "
        "to his shoulders under a tall gold crown set with red jewels. He wears a red military jacket with puffed "
        "sleeves, short flared red trunks, white tights and tall black boots, and holds a slim rapier. The king "
        "of the fairies, he poses with the vain, theatrical pride of a stage monarch."},
  {"Ps0005_050",  // Omoikane
        "A human brain the size of a boulder, hanging in the air, pinkish-orange and deeply folded, with two "
        "round, glossy blue eyes set low on its front where a face would be. From its underside dangles a tangle "
        "of long, limp, fleshy tendrils like a jellyfish's, and one straight stalk drops far below to a pointed, "
        "leaf-shaped tip. Thin fleshy rods spear clean through it from side to side, sticking far out on both "
        "sides like pins through a specimen, some ending in more staring blue eyes, others in flat, frilled tips "
        "like fins. The god of wisdom pictured as bare thought, it hovers calm and unblinking, taking everything "
        "in."},
  {"Ps0005_060",  // Orthrus
        "A huge two-headed hound, bigger than a horse, its two wolfish heads side by side at the front of one "
        "lean, long-legged body of dull mustard-gold fur. Each head has tall pointed ears, piercing teal eyes and "
        "a snarling mouth full of sharp teeth, and both are buried in a shaggy dark teal-black mane bristling in "
        "spikes over the shoulders. Behind it a startlingly long, whip-thin tail of purple segmented scales juts "
        "straight out, several times the length of the body. The guard dog of the cattle herds of myth, it stands "
        "low and wary, both mouths ready to bite."},
  {"Ps0005_070",  // Orobas
        "A tall, wiry horse-man standing upright on a horse's hind legs, the knees bending backward to tan "
        "hooves. His man-shaped body is deep crimson, lean and ribbed, fading to pale cream on the chest, throat "
        "and lower legs. On his shoulders sits a full horse's head glinting green eyes and flat teeth bared in a "
        "stiff, toothy grin. A thick, wild mane of dark green hair tumbles over his head and shoulders, and a "
        "long green tail sweeps out behind him. A demon stallion risen onto two legs, he looks uncanny and a "
        "little too eager, as if about to tell you a secret."},
  {"Ps0005_080",  // Onmoraki
        "A scrawny little creature like a plucked chicken wearing an onion for a head. The head is a big, pale "
        "cream bulb topped by a twisting green shoot, with two sleepy, half-closed eyes and a wide black grin "
        "slashed right across it; it does not sit on the shoulders but hangs out in front, held by a thin, "
        "striped neck that curls from the back of the bulb. Below is a round, pot-bellied body, spindly arms and "
        "skinny, bony bird legs. The spirit of a body left unmourned, it looks gormless and eerie at once, a lost "
        "soul stuck in a ridiculous shape."},
  {"Ps0011_000",  // Kali
        "A six-armed goddess with blood-red skin, her arms fanned out around her like a wheel, four of them "
        "gripping long, sweeping curved blades. Her black hair is slicked back to her shoulders, a green jewel "
        "sits like a third eye in her forehead, and her green eyes glare above a mouth showing small fangs. Her "
        "torso is cased in a ribbed silver breastplate, a green eye set at her belly. A grey apron marked with a "
        "great spiral hangs over a navy fringed skirt, and a girdle of grinning skulls rings her hips. Barefoot "
        "and poised, she is wrath given a body, beautiful and terrible."},
  {"Ps0011_010",  // Ganesha
        "A big, pot-bellied elephant-headed god with dusky blue skin, standing square on sturdy legs and broad "
        "bare feet. Huge pink-lined ears fan out beneath a gold domed helmet topped by a stacked gold crown, and "
        "his yellow eyes look out shrewdly over the trunk. One white tusk curves out proudly; the other is "
        "snapped off short. A wide collar of green bands and gold plates covers his shoulders, a string of gold "
        "beads hangs over his round belly, and a white loincloth wraps his hips. He holds a long curved sword. "
        "The remover of obstacles, he looks genial and solid, and plainly ready to fight."},
  {"Ps0011_020",  // Hua Po
        "A small, slender fairy with red skin and four large, gauzy butterfly wings that shade from yellow-green "
        "through purple to deep blue at the tips. Her hair is black at the crown and falls in two straight, blunt "
        "curtains of bright orange-gold either side of her face, framing big green eyes and a sweet, small smile. "
        "She wears a short cream tunic dress in the Chinese style, with a high collar, its long sleeves printed "
        "with blossoms, and little orange slippers on her bare red legs. A flower spirit of an old tale, she "
        "looks bright, light on her feet and ready to flit away."},
  {"Ps0011_030",  // ?
        "A tall, graceful angel with sage-green skin, long wavy black hair swept back from her face, amber eyes "
        "and a faint, composed smile. Two great feathered wings rise from her back, pale grey-green in front and "
        "rich green behind. Her chest and belly are cased in a gold cuirass moulded to her breasts and stomach, "
        "above a long, flowing white gown banded in crimson and patterned with red diamonds at the hem. In one "
        "hand she holds a slim sword, in the other a long stem of orange lilies. The herald of heaven, she stands "
        "serene and upright, gentle in face and armoured all the same."},
  {"Ps0011_040",  // Garuda
        "A great bird-man with a lean, tan human body hunched forward, his eagle's head thrust out ahead of him "
        "and two broad brown feathered wings spread wide where his arms would be. His head has a hooked yellow "
        "beak and blue eyes under a tall, ornate gold headdress. A red cloth wraps his hips, long banners of red, "
        "white and blue swirls hang down his front, gold bands circle his ankles above bare feet, and a long, "
        "stiff, pointed tail juts out behind him like a spear. The king of birds who carries a god, he looks "
        "proud and poised to launch himself into the sky."},
  {"Ps0011_050",  // Ganga
        "A slender goddess of pale blue-white skin from the waist up, rising from an immensely long serpent's "
        "tail of silvery scales that runs straight down far below her to a needle point. Two great fins of "
        "coral-red membrane fan out from her arms and sides, like a fish's fins. Her head carries a tall stacked "
        "gold crown, a red jewel on her brow, and her pale green eyes look out calm and level. A small gold bra "
        "hung with red tassels covers her breasts above a bare, slim waist. The holy river given a body, she "
        "seems to flow rather than stand, cool and untouchable."},
  {"Ps0012_000",  // Kaiwan
        "A huge five-pointed star with a face at its heart, hanging upright. Its spikes are charcoal black "
        "slashed with wavy grey stripes in front and plain black behind. In the centre sits a long, pale grey "
        "face with pointed ears, a ridged, lilac-tinged forehead, deep lines down the cheeks, a heavy downturned "
        "mouth and small blood-red eyes under a scowling brow. Around it writhe thick, twisting purple tendrils, "
        "curling up like smoke above the head and trailing down in a long, ragged beard. A star god of ill omen, "
        "it hangs glowering under its heavy brow, gloomy and unforgiving."},
  {"Ps0012_010",  // Kikuri-Hime
        "A tall, slender goddess with dark charcoal skin, pale blue eyes and pale blue lips, barefoot and very "
        "straight. Very long, straight white hair falls from her crown to below her waist, and at each side of "
        "her head sits a big pink-red ornament shaped like a lotus seed pod. Her fitted top is banded in red, "
        "cream and black; at her hips two great round lotus buds, pink with green petals, sit like a belt, with "
        "long white tassels hanging below. A vast pleated red mantle falls from her arms to the ground. Still and "
        "solemn, she has the quiet of a shrine at dawn."},
  {"Ps0012_020",  // Chimera
        "A three-headed beast larger than a horse, a lion, a goat and a serpent sharing one sleek tawny body. At "
        "the front a snarling lion's head is buried in a thick, shaggy golden mane, red-eyed and baring its "
        "fangs. Rising from its back is a long-necked black goat's head with a flowing grey-black mane, glaring "
        "yellow-green eyes and long ridged horns curving up and back. Its tail is an enormous serpent in bright "
        "blue scales banded with purple, stretching far behind to a blue snake's head. The fire-breathing monster "
        "of Greek myth, it looks ill-matched and ferocious, each head ready to go its own way."},
  {"Ps0012_030",  // Cybele
        "A tall, curvy goddess with vivid blue skin and nothing on her but paint: swooping white stripes curl "
        "around her like ribbons, cupping her full breasts, crossing her belly and spiralling down her hips and "
        "long legs. Long ridged brown ram's horns sweep back from her head, and glossy black hair falls in a long "
        "ponytail almost to her knees. She has pointed ears, sultry amber eyes under painted lids and dark lips "
        "curled in a knowing smile. In each hand she holds a slim curved sword with a bronze hilt. The great "
        "mother of wild places, she stands naked and unashamed, untamed and openly alluring."},
  {"Ps0012_040",  // Girimekhala
        "A massive, pot-bellied elephant demon with teal-blue skin streaked with dark, tiger-like stripes, its "
        "huge head stooped low on its shoulders. A single great purple eye stares from the middle of its brow "
        "above a long trunk, broad ears and two big curving ivory tusks. Heavy gold shoulder guards with curling "
        "engravings cap its shoulders over a dark collar, a thick black sash wraps its swollen belly with a round "
        "gold medallion hanging below, and gold bands ring its arms and ankles. It holds a long curved sword. The "
        "one-eyed war elephant of a demon king, it looks lumbering, heavy and brutish, built to trample."},
  {"Ps0012_050",  // King Frost
        "A small snowman king perched on top of an enormous golden war machine. His head is a round white "
        "snowball with two oval black eyes and a wide black grin with two little fangs, framed by a powdered, "
        "curly blond wig. A tall, spiked gold crown with a white snowflake on its front rises above. Below him "
        "swells a huge dome of riveted gold metal, a big padlock on its front and arched wheel openings at the "
        "sides. A white mitten holds out an outsized gold key. He sits grinning on top of his golden machine, "
        "pompous, puffed up and delighted with himself."},
  {"Ps0013_000",  // Queen Medb
        "A tall, long-legged queen with a wild cloud of lilac-pink hair that tumbles to her waist and spills down "
        "over her chest, her face hidden behind a sharp green mask. A cropped bolero of cream scales covers her "
        "shoulders over a shiny silver bra that lifts her breasts, and below it a skin-tight bodysuit in chevrons "
        "clings to her hips and legs. Fluffy lilac fur cuffs swallow her forearms above clawed red gloves, and a "
        "long cape of cream scales falls behind her to the ground. The warrior queen of the old Irish tales, she "
        "stands masked and imperious, hungry, her body sheathed and openly on show."},
  {"Ps0013_010",  // Cu Chulainn
        "A tall, slim warrior standing straight and composed, long straight black hair falling past his shoulders "
        "under a white circlet set with a violet diamond above his brow. His face is handsome and serious, pale "
        "blue eyes level and unsmiling. He wears sleek white armour traced with violet lines, with a high collar, "
        "layered shoulder plates, over a short skirt of dark mail, with dark violet gloves and tall violet boots. "
        "A long pale grey cape falls behind him to the ground. He holds a very long, slender spear. The hound of "
        "the old Irish tales, he looks cool, noble and wholly sure of his duty."},
  {"Ps0013_020",  // Kumbhanda
        "A gaunt, skeletal ghoul standing hunched with its bony knees bent and splayed, its dark green-black "
        "flesh stretched over ribs, spine and long, knobbly limbs that end in clawed hands and feet. Its head is "
        "a long grey face like a horse's skull, fixed in a grin of flat teeth, with glowing yellow eyes and lank "
        "dark red hair hanging to its chest. On top sits a wide, flat red hat, its brim hung all round with long "
        "cords ending in barbed hooks. It holds a curved, rusty blade. A demon that feeds on sleepers, it stoops "
        "and leers as if waiting for you to close your eyes."},
  {"Ps0013_030",  // Kushi Mitama
        "A big, glossy, olive-green bead shaped like a comma, its round head sweeping off to one side into a "
        "long, pointed, curling tail, like an ancient curved jewel. Across the round part is a sly face: one eye "
        "screwed shut in a squinting wink under a furrowed brow, the other wide and white under a high, arched "
        "black brow, and a crooked smirk showing a sliver of white teeth. It has no limbs and nothing else on it. "
        "A fragment of the soul that brings luck and wonder, it looks cheeky and knowing, as if it has just let "
        "you in on a joke."},
  {"Ps0013_040",  // Kurama Tengu
        "A powerful mountain goblin dressed as a wandering ascetic, with vivid blue skin and a broad, muscular "
        "build. His long blue hair is swept back into a sharp crest, a small black box-cap on his forehead, green "
        "lightning-like marks run down his face, and his red eyes are hooded and grim. He wears white robes with "
        "a gold stole hung with big round tassels, black-and-white striped baggy trousers and straw sandals. "
        "Large wings, grey-white in front and deep blue behind, rise behind him, and he holds a conch. The goblin "
        "lord who trained a hero in the mountains, he looks stern, aloof and severe."},
  {"Ps0013_050",  // Gurulu
        "A tall, gaunt bird demon with a dark, inky purple-black body caged in a pale grey skeleton worn on the "
        "outside: ribs, spine, hips and leg bones clamped over it like armour. Its head juts forward on a stooped "
        "neck, a bird's skull with a long hooked beak, a sharp horn sweeping back from the crown and a red jewel "
        "on the brow. Two huge wings of ragged black-violet feathers span far to either side, and its feet are "
        "bony talons. It carries a long staff. A bird of death and ill omen, it looks stark, cold and patient, "
        "like something that waits beside the dying."},
  {"Ps0013_060",  // Clotho
        "A slender, poised woman with porcelain-pale skin and amber eyes, her face cool and unreadable. Her "
        "golden-blond hair is shaped into a full, rounded bob, two bright green spools of thread wound into it at "
        "either side of her face. A high-necked, close-fitting white suit covers her from throat to ankle, her "
        "feet bare. From her waist hangs a tall cylinder of a skirt woven in a dark grey lattice like a loom's "
        "work, open down the front. In one hand she holds a black and gold handle trailing a single long, fine "
        "thread. The fate who spins each life, she looks precise, detached and quietly ominous."},
  {"Ps0014_000",  // Quetzalcoatl
        "An immense winged serpent caught in level flight, its impossibly long, thin body of pale sea-green "
        "scales stretched out straight behind it to a fine, tapering tail. Just behind its head bursts a great "
        "upright fan of frosty, pale blue feathers like a ruff, and two vast, slender wings of white and "
        "lavender-grey feathers spread wide on either side, far broader than the body is thick. Its head is a "
        "snake's, with glowing red eyes and jaws wide open on a pink mouth and sharp fangs. The feathered serpent "
        "of the old Mexican gods, it glides calm and majestic, a creature of wind and open sky."},
  {"Ps0014_010",  // Genbu
        "A giant tortoise walking low on thick, tan, scaly legs with sharp claws, its broad domed shell made of "
        "deep teal-black plates outlined in bright magenta lines. Its long-necked tan head has green eyes, a "
        "curved beak open on small fangs, and a dark, bristly beard hanging beneath its chin. From its rear an "
        "enormously long serpent stretches straight out behind it, scaled in red-orange with a row of dark spikes "
        "along its back, ending far away in a fierce, maned red-orange snake's head that faces backwards. The "
        "black warrior who guards the north, it plods steady and unbreakable, a fortress with a sentry watching "
        "its back."},
  {"Ps0015_000",  // Koumokuten
        "A broad, thickset temple guardian with dark blue skin, standing square in armour with a writing brush in "
        "one hand and a green scroll in the other, ready to take down a record. His face is set in a deep scowl, "
        "heavy brows knotted over narrow white eyes, his black hair drawn into a high topknot clasped by a red "
        "and gold flame ornament. Maroon plates cover his chest over orange robes, snarling beasts' heads guard "
        "his shoulders, and a white sash is knotted above a long armoured skirt. A king who watches one quarter "
        "of heaven, he looks grim and unblinking, a witness who misses nothing."},
  {"Ps0015_010",  // Kohryu
        "An immense golden dragon, its serpent body stretched long and low behind it to a needle-fine tail, small "
        "spines running down its back. Its head bristles with a ruff of golden whiskers around wide red eyes and "
        "a snarling mouth of small teeth, and above it rises a towering crown of branching golden antlers fanned "
        "out around a tall V-shaped crest. Each of its four clawed feet grips a large glossy orb, one red, one "
        "blue, one smoky black and one pale lavender. The yellow dragon of the centre, lord of all the others, it "
        "holds its jewels like a ruler holding the world."},
  {"Ps0021_000",  // Saki Mitama
        "A floating drop of polished gold shaped like a comma or a curved jewel bead: a round, egg-smooth head "
        "whose top sweeps off sideways into a long, tapering tail that curls back on itself like a wisp in the "
        "wind. On the round end is moulded a calm, gentle face, thin arched brows, eyes closed in contented "
        "crescents, a small straight nose and a soft smile, the lips just parted. It has no body, limbs or "
        "clothes, only that single bright shape. A spirit of good fortune from Shinto belief, it drifts in quiet, "
        "sunny bliss, as if dreaming of something pleasant."},
  {"Ps0021_010",  // Succubus
        "A tall, long-legged demon woman built to tempt, mostly bare skin framed in black. Her high-necked black "
        "leotard clings to her breasts and is cut away at both sides and down the whole back, rising to her hip "
        "bones in front and narrowing to a thong behind, with long black opera gloves and thigh-high black "
        "stockings. Huge bat wings, dark crimson inside and navy outside, tower over her head, and a whip-thin "
        "black tail ends in a spade at her heels. Wavy dark blonde hair, pointed ears, blue eyes and dark lips; a "
        "red heart hangs from her black choker, and a cuff with a short chain rings one ankle. The night visitor "
        "of medieval legend, she looks cool and unhurried, sure of her effect."},
  {"Ps0021_020",  // Satan
        "A colossal winged serpent rearing up from a thick, dark navy tail that bends to the ground and runs far "
        "behind it. Its lean, ribbed blue torso holds a small horned demon's face with yellow eyes, a gold point "
        "in its brow and a fanged, gaping mouth, under a tall segmented crest arched like a scorpion's tail. Tier "
        "upon tier of great wings fan out around it, deep blue outside and blood red within, each ending in a "
        "clawed hand, steel blades jutting between them. Two immensely long, jointed bone-grey spines slant down "
        "from its sides. The great accuser at the end of days, it looks vast and inhuman."},
  {"Ps0021_030",  // Sati
        "A slender goddess veiled in black from head to foot, all but her eyes hidden. A black veil covers her "
        "face below deep pink-red eyes, fine gold chains looping from it, and a crown of scalloped gold "
        "medallions sits over her black bob. Her close black gown wraps across her chest under ribbed gold trim "
        "and is belted in scalloped gold, then splits high at the front to bare her pale thighs over a black "
        "high-cut brief, the skirts falling in banded tiers to bare feet. The goddess who gave herself to the "
        "fire, she looks composed and unreadable, her heat kept under the black."},
  {"Ps0021_040",  // ?
        "A tall, lean, muscular figure like an anatomy chart come to life, bright red muscle panels laid over "
        "pale bone-grey bands, each edged in a crisp white line. Its bald red head is tipped back so the face "
        "looks up at the sky, a pale grey mask with sharp blue eyes and an open red mouth, a tall curved crest "
        "sweeping from the crown. Its hands are smooth red mitts, its legs taper to pointed red tips, and in the "
        "hollow of its belly sits a perfectly round black orb like a hole into nothing. The old god of time and "
        "harvest, it seems rapt and strangely empty."},
  {"Ps0021_050",  // Samael
        "A huge, flat crimson serpent stretched out straight and level as a thrown spear, its long, blade-thin "
        "body of rough red hide slashed with diagonal black stripes and dark purple underneath, tapering to a "
        "needle point far behind. Its head is broad and blunt, craggy red with a short horn and a cluster of "
        "glossy blue eyes, one large in the middle and smaller ones around it, above a heavy purple jaw. From its "
        "shoulders run long, thin red struts like the bare bones of wings, hooked claws hanging from them. The "
        "angel of death as a serpent, it looks sleek, silent and venomous."},
  {"Ps0021_060",  // Sarasvati
        "A graceful goddess of music and learning with warm brown skin, long black hair, calm blue eyes and "
        "gold-painted lips, a long-necked wooden sitar floating upright at her side. A tall golden crown set with "
        "blue gems rises to a small golden urn, ringed behind by a gold halo. She wears a high-necked emerald top "
        "edged in gold and black stripes under a white short-sleeved jacket and overskirt, a sapphire-studded "
        "gold belt, and full green trousers gathered at her bare ankles, pale silk scarves drifting by her "
        "shoulders. She stands serene and refined, as if listening to a melody no one else hears."},
  {"Ps0021_070",  // Thunderbird
        "A great stylised bird carved as if from dark slate, smooth and upright like a totem pole rather than "
        "feathered. Its narrow, bulb-shaped head is capped by a rounded crest, with two round, fiery orange eyes "
        "and jagged lightning-bolt grooves cut down its face like war paint. Two massive wings arch up from its "
        "shoulders and sweep down to long curved points, ribbed underneath in grooved black bands. Two small "
        "taloned hands cradle a glowing red core at its chest, and below, its body flares into a wide, forked "
        "tail. The storm bird of the plains, it stands rigid and watchful, thunder held in its claws."},
  {"Ps0021_080",  // Sandalphon
        "A tall angel built like a gleaming golden statue, his polished gold body jointed like armour, his face a "
        "calm gold mask with bright blue eyes under a silver helmet cut in a sharp, straight-fringed bob. A long, "
        "sleeveless green tabard bearing a big red cross hangs to his ankles, bound by a red sash whose long "
        "tails slant away to the ground. Silver plates with round sun-wheel medallions sit at his shoulders, "
        "elbows and knees. A golden horseshoe arch rises over his back, and behind it spread vast wings of long, "
        "pale silver blades. A guardian of heaven's gate, he stands immaculate and utterly composed."},
  {"Ps0021_090",  // Sandman
        "A lanky little imp whose whole head is a polished black and silver crescent moon, its thick curve "
        "forming skull and jutting chin. Pointed grey elf ears stick out at the sides, narrow amber eyes look out "
        "half-lidded and sly, and below a black triangle of a nose curls a thin, smug grin. His skinny body is "
        "sheathed in a snug dark red bodysuit with silver rings at wrists and ankles, ending in curly-toed red "
        "slippers. In one hand he hauls a fat burlap sack, stitched shut and banded in black, full of the sand of "
        "sleep. He looks sly, unhurried and pleased with himself."},
  {"Ps0022_000",  // Siegfried
        "A tall, lean young warrior with orange-red skin and a hard, muscled build, standing easy with a long "
        "blue-steel broadsword in his hand and a second blade hanging at his hip. Long, shaggy greenish-blond "
        "hair spills from under a crimson spiked helmet over a calm face with blue eyes. His sleeveless tunic is "
        "covered in crimson diamond plates studded with silver, over a high collar of black mail, two black "
        "straps crossing his chest. A round shield with an embossed silver face rides on his back. The "
        "dragon-slayer of the old German songs, he looks quiet and sure, unafraid of anything."},
  {"Ps0022_010",  // Shiisaa
        "A stocky lion-dog the size of a pony, all bright yellow body and stout legs planted wide on big "
        "white-clawed paws. Its huge round head grins from ear to ear over rows of square white teeth, with round "
        "staring eyes ringed in red under bushy curled brows. A thick teal mane and beard carved into tight "
        "curls, darkening to red at the tips, frames the face and rises to a tall spike on its crown, and more "
        "teal curls sprout at its legs and in its big swirling tail. The guardian of Okinawan rooftops and gates, "
        "it looks fierce and comical at once, loyally baring its teeth."},
  {"Ps0022_020",  // Shiva
        "A lean, muscular god with deep blue skin and four arms, standing tall and loose beside a golden trident "
        "taller than he is. His long black hair is piled into a topknot with a gold finial and a silver crescent "
        "moon, and on his brow three pale stripes cross a vertical third eye above a faint, knowing smile. Dark "
        "prayer beads hang on his bare chest, a teal serpent winds around his shoulders and waist, and a "
        "fur-edged leopard-skin wrap hangs over a long crimson sash; he holds a conch and a small drum. The "
        "destroyer and renewer of the world, he looks serene and dangerous."},
  {"Ps0022_030",  // Shiki-Ouji
        "A tall, spindly warrior cut from flat, sharp-cornered planes, as if folded from stiff paper. Its front "
        "is split straight down the middle, one half white and the other black, and its back is blood red and "
        "black with a column of black script painted down it. A great crescent, half black and half white, sweeps "
        "up like horns over a small skull face with a fringe of paper strips for a jaw. Angular plates jut from "
        "its shoulders, a short skirt of layered paper strips flares at its hips, and its long fingers end in "
        "claws. A paper servant called up by sorcery, it looks weightless, stiff and eerie."},
  {"Ps0022_040",  // Jikokuten
        "A broad, square-shouldered general in heavy armour, standing solid with a long straight sword at his "
        "feet. His face is a golden mask locked in a ferocious scowl, heavy black brows drawn down over white "
        "eyes and a thick curled black moustache, under a dark green helmet banded in gold with a gold flower "
        "boss, a red plume and silver wings over the ears. His armour is dark green lamellar trimmed in gold, "
        "snarling lion heads on the shoulders, a red cloth falling from his helmet behind and a white sash "
        "knotted at the waist. A king who guards one quarter of heaven, he looks proud and immovable."},
  {"Ps0022_050",  // Black Frost
        "A small, round snow sprite turned jet black, a big ball of a head on a pudgy little body. A deep purple "
        "jester's hood with two pointed cat-ear peaks hugs his head, its long tail kinked into a zigzag behind "
        "him and a yellow horned crescent on the front. His face is all menace: slanted, angry red eyes and a "
        "huge red grin with two white fangs. A collar of jagged purple points sits at his neck, his arms are "
        "ragged black flaps like torn wings, and he stands in purple boots with gold cuffs and curling toes. The "
        "cheerful frost imp's dark twin, he looks gleeful and spiteful."},
  {"Ps0022_060",  // Jatayu
        "A great crimson vulture with huge wings spread wide, his long, bare red neck thrust straight out ahead "
        "of a hunched body as if leaning into the wind, a thick ruff of grey-white plumes at its base. His hooked "
        "tan beak and bright blue eye sit under a dark bronze helmet with a pointed dome and two curved horns, "
        "heavy gold pendants hanging from it, each ending in a ribbed crimson tassel. He stands on scaly tan legs "
        "with sharp talons, and an extremely long, thin, segmented tail trails far behind. The old vulture king "
        "of Indian epic, he looks battle-worn, noble and grimly determined."},
  {"Ps0022_070",  // Jack Frost
        "A small, round snow sprite about knee high, snowy white all over, with a big ball of a head on a pudgy "
        "little belly. A royal-blue jester's hood with two pointed cat-ear peaks hugs his head, its long tail "
        "kinked into a zigzag behind him and a yellow oval on the front. His face is pure cartoon delight: big "
        "black oval eyes and a huge open grin with two little white fangs. A collar of blue points rings his "
        "neck, his arms end in soft mitten hands, and he stands in chunky blue boots with yellow cuffs. A winter "
        "imp of folk tales, he looks bursting with cheer."},
  {"Ps0022_080",  // Jack-o'-Lantern
        "A pumpkin-headed spook with no body at all, just a round orange jack-o'-lantern floating above a "
        "billowing dark blue cloak that flaps open over empty air. Its carved face burns with two glowing "
        "red-white eyes over a small triangle nose and a wide, jagged grin. A floppy teal witch's hat with a "
        "white band and a long bent tip sits low on its head. The cloak is tied at the neck by a cord ending in "
        "two white pom-poms, and a single white-gloved hand holds up an old iron lantern with a glowing yellow "
        "glass. The trickster of the old wisp tales, it looks gleeful, out to lead someone astray."},
  {"Ps0022_090",  // Chi You
        "A towering war god with bright green skin and six muscular arms, bristling with a weapon in nearly every "
        "hand. His head is a bull's, with long curved black horns, a fanged snout and small blue eyes under a "
        "white helmet with a pink crest. A scalloped mantle of white and pink plates spreads over his shoulders "
        "above a long red quilted tabard marked with a black character on a yellow disc. He wields a spear, a "
        "halberd, a golden axe and a gold gong trailing ribbons, and a shield painted with a snarling face hangs "
        "on his back. An ancient Chinese god of war, he looks brutish and tireless."},
  {"Ps0022_100",  // Silky
        "A slender, quiet woman with pale mint-green skin and long green hair that drifts out behind her in "
        "loose, wavering strands like weed in a stream. A neat white kerchief covers her head and falls to her "
        "shoulders, framing amber eyes and a still, gentle face. She wears a long burnt-orange gown cut off the "
        "shoulder, its fitted bodice laced down the front with curling black scrollwork that is echoed at the "
        "cuffs, the full skirt sweeping to the floor in a wide bell edged in dark trim. The silk-rustling ghost "
        "of old Border houses who tends to the chores at night, she looks modest, patient and a little sad."},
  {"Ps0023_000",  // Scathach
        "A pale warrior woman crouching low with her knees spread wide, almost swallowed by an enormous black "
        "cloak that falls in a vast cone to the ground, open at the front just enough to show her. A tall black "
        "hat banded with silver crosses shades a ghost-white face with closed eyes, pink lips and a red rose "
        "painted on one cheek. Green and teal rings circle her throat over a ridged black bustier; a silver "
        "Celtic cross hangs on her bare belly, and a narrow, high-cut black brief is all that covers her between "
        "bare white thighs held wide apart. She waits silent and coiled in the cloak's dark."},
  {"Ps0023_010",  // Skadi
        "A tall, slender goddess, naked from head to foot, her whole body a smooth, featureless silhouette of jet "
        "black: small breasts, a narrow waist and long bare legs, framed by the open front of her cape. Only her "
        "glaring red eyes and red lips stand out on her face, and her silver-white hair sweeps up into two tall "
        "plumes like horns. Two carved gold collar pieces stand on her shoulders like crowns, and from them a "
        "vast cape spreads to the ground, forest green inside and woven outside in gold and black chevrons. Bare "
        "and unconcerned, she stands as cold and still as a snowbound peak."},
  {"Ps0023_020",  // Suzaku
        "A glorious crimson phoenix hanging in the air with its wings flung wide and up, its long neck held proud "
        "above a fluffy pink breast. A soft white crest and a spray of pink feathers top its head, with a small "
        "golden beak and blue eyes. Behind it a huge fan of red plumes rises like a peacock's, each tipped with a "
        "gold eye, among curling black spikes like thorns. Below, five long streamers hang almost to the ground, "
        "blue, white, black, red and gold, each ending in a feathered eye. The vermilion bird that guards the "
        "south, it looks blazing, proud and untouchable."},
  {"Ps0023_030",  // ?
        "A tall, wiry god with dusky purple skin sitting cross-legged in midair, his face lost behind a long, "
        "straight curtain of silver-white hair that falls to his chest. A towering silver crown of twisted, "
        "branching spikes rises from his head like dead branches or frozen lightning. A necklace of curved golden "
        "fangs with a turquoise pendant hangs on his bare, muscled chest, and a long, stiff cape falls behind "
        "him, charcoal speckled with blood red and swirled with faint storm patterns. One hand holds out a long "
        "black sword barbed along its edge like a thorn branch. The storm god cast out of heaven, he sits in "
        "brooding calm."},
  {"Ps0023_040",  // Slime
        "A lumpy mound of green sludge about waist high, slumped on the floor and running down its own sides in "
        "thick ridges and drips like melting wax. Sickly yellow blotches mottle its slick surface, pooling "
        "thickest over its rounded top, and it is pitted all over with little dark holes. Two round, glossy red "
        "eyes bulge from deep sockets near the top, and below them gapes a wide black mouth with a heavy, sagging "
        "lower lip, fixed in a look of dismay. It has no limbs at all, only quivering muck. The lowliest of "
        "things, it seems gloomy, helpless and faintly pitiable."},
  {"Ps0023_050",  // Surt
        "A towering, gaunt giant with charcoal-grey skin wound all over in ragged dark red bands, like stripes of "
        "embers smouldering across his body. His long, narrow head rises straight up into a flat-topped column "
        "like a tall fez, with narrow glowing yellow eyes under a heavy scowl, a hooked nose and a small stub of "
        "beard on his chin. His body is lean but hard with muscle, long-armed and barefoot, and in one hand he "
        "grips a very long, thin dark red sword with an orange and black patterned hilt. The fire giant who will "
        "burn the world at its end, he looks grim and patient, all banked heat."},
  {"Ps0024_000",  // Qitian Dasheng
        "A wiry old ape in the robes of a court sage, riding a puffy white swirl of cloud with a long red staff "
        "capped in gold nearby. His wrinkled brown face is split by a wide grin of clenched teeth, with sharp "
        "blue eyes, pointed ears and a great white mane and beard. A tall red official's hat banded in gold sits "
        "on his head, a tasselled rod laid across its crown. His crimson robe has enormous bell sleeves trimmed "
        "in orange-gold, wrapped over a blue under-robe and cinched with a gold-buckled belt. The monkey who "
        "declared himself heaven's equal, he looks ancient, cocky and still spoiling for a fight."},
  {"Ps0024_010",  // Seiryu
        "An enormous Eastern dragon, its body a tremendously long, thin serpent of dark navy scales stretched out "
        "far behind it, a row of yellow-green spines down its back and small clawed feet along its length. All "
        "the drama is in the head, which faces you: a shaggy mane of dark green fur flaring like a lion's ruff, "
        "two branching tan antlers, long green whiskers trailing from the snout, blazing yellow-orange eyes under "
        "a scowling brow and a gaping red mouth of fangs. Big hooked tan talons spread at either side of its "
        "face. The azure dragon of the east, it looks ancient and furious, ready to coil around the sky."},
  {"Ps0024_020",  // Setanta
        "A young warrior, a boy with a neat black bowl cut and steady grey-blue eyes looking out over a long "
        "sky-blue tartan scarf, crossed with green and pink lines, wound up over his nose and hanging down his "
        "chest. He wears quilted white padded armour with big puffed shoulders and a polished steel breastplate, "
        "a belt hung with two carved wooden medallions and fringed tassels, blue tartan sleeves and breeches, "
        "tall white quilted boots and a plain brown cape. He carries a long steel-tipped spear and a pair of "
        "slender wooden staves. The boy who would become a legendary hound of Ulster, he looks earnest, quiet and "
        "fearless."},
  {"Ps0024_030",  // Seth
        "A huge, sleek black dragon hunched forward with its long neck bent low, so its narrow head hangs down "
        "and glares up from beneath vast wings held high and wide like a canopy. Its whole body is dark charcoal "
        "with a faint purple sheen, the wings' leading edges studded with small hooked claws. The head bristles "
        "with a crown of backswept spikes, with small green eyes and a mouth lined in red. Its lean body crouches "
        "on clawed hind legs, and a long, whip-like tail trails far behind, ridged its whole length with jagged "
        "spines. The desert god of chaos and storms, it looks lithe, cruel and ready to pounce."},
  {"Ps0025_000",  // Zouchouten
        "A broad-shouldered temple guardian with green skin, standing square in steel-blue armour beside a tall "
        "golden trident that towers over him. His face is set in a hard scowl, heavy brows drawn down over pale "
        "glaring eyes and a thin moustache drooping at the corners, his black hair tied up in a topknot under a "
        "small blue crown. Rounded black plates cover his chest, his blue shoulder guards are moulded into "
        "snarling beast faces, and a thick white rope sash is knotted over layered black lamellar skirts, with "
        "white sleeves and blue leggings. One of the four kings who guard heaven's quarters, he looks immovable "
        "and grim."},
  {"Ps0025_010",  // Throne
        "A slender, silent figure standing inside a great stone wheel, as if it were bound to the spokes. Its "
        "deep navy hood frames a dark brown face, calm and mask-like, with faintly glowing red eyes, and its robe "
        "of glossy dark blue falls in a layered cape over the shoulders and in wide sleeves to bare feet. Around "
        "it rises the wheel, weathered grey stone taller than a person, six spokes meeting at a hub behind its "
        "back and six round amber lamps glowing around the rim like watching eyes. An angel of the high choirs "
        "pictured as the wheel of heaven's throne, it looks solemn, patient and judging."},
  {"Ps0031_000",  // Dakini
        "A slender, golden-skinned goddess with a curved silver sword in each hand, lithe and lightly dressed. "
        "Her crown is a row of tiny pale skull-faced heads under golden domed finials, flanked by fin-shaped "
        "golden plates, over black hair in a bun; her red-lidded eyes are painted with blue stripes beneath, with "
        "a red mark on her brow and great gold disc earrings. A cropped green top barely covers her breasts and "
        "leaves her belly bare, and a dusky pink wrap skirt hangs low on her hips, small skulls at her belt. Red "
        "beads loop her throat, arms and ankles. A sky-dancer of fierce lore, she looks lovely and lethal."},
  {"Ps0031_010",  // ?
        "A dead holy man sitting cross-legged on the ground in perfect meditation, nothing left of him but a "
        "grinning skull and bony hands inside his robes. A tall, pointed ochre hat bound with a green band and "
        "two silver discs towers over the skull, long green cloths hanging down beside the face. His voluminous "
        "gold-ochre robe spreads out at the sleeves into great flaring wings, over a green under-robe crossed "
        "with a dark lattice. In his hands he holds out a string of red prayer beads and a small golden ritual "
        "bell. The monk who starved himself into a living Buddha, he radiates an eerie, unshakeable serenity."},
  {"Ps0031_020",  // Take-Mikazuchi
        "A lean young god with reddish-brown skin, standing straight in plain white, a long black scabbard thrust "
        "through his belt and a golden sword lying at his feet. His black hair is looped into two bunches at the "
        "sides of his head in the ancient style, tied with a blue headband above narrowed amber eyes and a cool, "
        "tight-lipped frown. Teal curved jewels hang from his ears and on a necklace of dark beads. His white "
        "tunic fastens with small ties over full trousers bound below the knee, with blue shoes and a gold and "
        "blue apron panel. The thunder god of old Japan, he looks quietly dangerous."},
  {"Ps0031_030",  // Take-Minakata
        "A hulking captive with no arms, standing with his head hung forward, his chest bound tight in a "
        "crisscross harness of thick hemp rope. His green ogre's face is craggy and scowling, with small tusks "
        "and one glowing red eye, two pale horns curving forward from his temples, and black hair tied in loops "
        "at the sides. Dark round guards cap the stumps of his shoulders. He wears a white tunic and trousers, a "
        "navy striped sash, red cords below the knee and dark shin guards, his green feet bare. The war god who "
        "lost his contest and was bound in exile, he stands beaten but glowering."},
  {"Ps0031_040",  // Tam Lin
        "A tall, slim knight with an elfin face, long straight silver-white hair falling past his shoulders and "
        "cool blue eyes, a teal circlet set with a diamond-shaped gem on his brow and a small ring in one pointed "
        "ear. His sleek teal plate armour is edged in silver piping, with a high stand-up collar, flared shoulder "
        "guards and tall teal and black boots, over a skirt of black mail, his hands in black clawed gauntlets. A "
        "long white cloak hangs to his heels, and he holds a thin black spear. The young knight of the ballad, "
        "stolen away to the fairy court, he looks elegant, remote and faintly sorrowful."},
  {"Ps0032_000",  // Chernobog
        "A tall, gaunt figure that is a single column of glossy black robe flaring to the ground, a red sunburst "
        "glowing on its chest. Its face is a pale blue skull grinning under an enormous flat, round purple hat "
        "like a mushroom cap, its underside ribbed with gills. One hand holds a long, straight silver sword "
        "upright before it, the jewelled guard at its fist. Around the hem of its robe sprout slender teal stalks "
        "topped with little purple caps, a sinister garden of fungus rising from where it stands. The black god "
        "of night and ill fortune, it looks patient and funereal, waiting for everything to rot."},
  {"Ps0034_000",  // Dionysus
        "A lithe young god painted from head to toe in a psychedelic swirl of green, blue, yellow and orange "
        "waves that runs unbroken over his face, a blue band across his mouth and nose like a mask. A shock of "
        "spiky silver-white hair crowns long, wavy brown locks. Under the paint he wears only a thin white thong, "
        "white gloves and boots, and a crimson cloth thrown over one shoulder spills far past his feet. A twisted "
        "wooden staff topped with a silver pine cone, the wine god's wand, hangs across him on a cord. Bright, "
        "bare and dizzying, he carries himself like a revel with no intention of ending."},
  {"Ps0034_010",  // Titania
        "A tall, slender fairy queen standing barefoot and still, long wavy golden hair falling to her waist and "
        "a pink lily tucked behind one pointed ear. She has teal eyes, soft pink lips and a calm, faintly cool "
        "face above a green choker. Her forest-green gown has a low scoop neck, a pointed shoulder capelet and "
        "long sleeves, its wide bell skirt worked with golden zigzags like running flames, and a thin chain rings "
        "one ankle. Four tall, translucent wings of pale lilac and blue, veined like a dragonfly's, rise behind "
        "her. Graceful and remote, she holds herself like the queen of a midsummer forest."},
  {"Ps0034_020",  // Decarabia
        "A five-pointed star about the height of a person, almost flat, with a single great eye staring from its "
        "centre: a demon of the old grimoires that was said to appear as a star. Its front is a mottled rusty "
        "orange-red, smooth and gently domed, while its back is cold blue-grey stone, ridged in lines that run "
        "out along each point. The eye is violet with a white gleam, rimmed in black, and short black stalks "
        "tipped with dots sprout around its lower edge like lashes. Unblinking and utterly still, it watches with "
        "the patience of something that has never needed to move."},
  {"Ps0035_000",  // Thoth
        "A lean white baboon sitting on top of a huge closed book stood on its end, knees bent over its front "
        "edge and black feet hanging down its cover, a long thin tail held straight out behind. His black, "
        "long-muzzled face juts from a vast round ruff of white fur, chin raised, yellow eyes narrowed and teeth "
        "bared, and a golden disc rests in a golden crescent moon on his crown. A broad Egyptian collar of teal "
        "and black, dotted with gold diamonds, covers his chest, and the book bears hieroglyphs and a painted "
        "eye. The Egyptian god of writing perches above his book, lofty and unhurried."},
  {"Ps0035_010",  // Thor
        "A towering, heavily muscled thunder god of Norse myth, deep brown skin banded with black knotwork "
        "tattoos on his arms and thighs. His head is shut inside a gold helmet with a spiked crest and a closed "
        "faceplate, two glowing blue eye slits staring out, and long black hair falls from beneath it over his "
        "chest. A gold breastplate of overlapping scales covers his torso above white briefs, thick white cuffs "
        "wrap his forearms and shins, and a white cowl and black-lined cloak hang from his shoulders. One fist "
        "holds a heavy, blocky grey hammer. Faceless and enormous, he stands like a storm that has put on armour."},
  {"Ps0035_020",  // Dominion
        "A tall, slender angel standing very straight, pale and long-faced, with a wild mane of dark blue hair "
        "and level green eyes that give nothing away. A ring of white parchment marked in dotted script circles "
        "behind his head and streams out to one side, like a decree unrolling. Broad wings of grey-brown feathers "
        "rise from his back. He wears a long white robe, a brown cape and sash trimmed with gold key patterns, a "
        "silver belt set with red stones and a crimson cloak. One hand holds black balance scales, the other a "
        "blue book. Calm and impartial, he looks ready to weigh whoever stands before him."},
  {"Ps0035_030",  // Trumpeter
        "A skeletal angel floating upright in long, twisting pale grey robes that trail away to nothing where its "
        "feet should be, great grey wings drooping behind it. Its head is a grinning bone-white skull with stiff "
        "golden curls rolled at each side like a judge's wig, under a tall black and gold checkered cap. A black "
        "stole patterned with white clovers and pointed triangles runs down its chest, a long black bar across "
        "its shoulders like a yoke. It carries a golden trumpet topped with a small red bird bearing one blue "
        "eye. Solemn and patient, it hangs in the air waiting for the signal to sound the end."},
  {"Ps0041_000",  // Naga
        "A serpent spirit of Hindu myth, a slim man above the waist and a long snake below, his tail stretching "
        "far out behind him along the ground. His skin is smooth pale blue-grey, the tail streaked with magenta "
        "down its back and a small bell tied to its tip. Long black hair rises in a topknot and falls in two tied "
        "tails over his chest, under a silver tiara with a green gem, and a yellow sash crosses his bare chest. "
        "He carries a slim silver spear and a round steel shield marked with a coiled serpent. Calm and "
        "level-eyed, he keeps watch like a guardian of a river shrine."},
  {"Ps0041_010",  // Naga Raja
        "A serpent king of Hindu myth, a lean man's torso rising from an immensely long snake's body that runs on "
        "and on beneath him, its tan scales banded with dark red. His head is framed by a great fan of golden "
        "spines like a cobra's spread hood, shading a cold, narrow, expressionless face. A black spiked emblem "
        "marks his bare chest below a necklace of orange teeth, his arms are sheathed in gold scales ending in "
        "claws, and a sheer white stole loops over his shoulders and streams away. He holds a golden spear "
        "trailing a red tassel. Tall, still and unblinking, he looks coiled to strike."},
  {"Ps0041_020",  // Narcissus
        "A slender, pale young man standing barefoot in a tuft of bright green grass among nodding white "
        "daffodils, and more of the same flowers growing straight out of the crown of his head on green stems. "
        "Long, wavy golden hair spills to his waist and falls across one blue eye. He is naked except for a "
        "length of deep crimson silk wrapped low around his hips, its long end streaming out behind him. His face "
        "is soft and downcast, gazing at nothing. The beautiful youth of Greek myth who loved his own reflection "
        "and became a flower, he stands absorbed in himself, dreamy and untouchable."},
  {"Ps0042_000",  // Nidhoggr
        "An immensely long, low worm lying flat along the ground, a smooth tube of pale teal hide veined with "
        "jagged violet lines that tapers behind it to a needle-thin tail. It has no eyes: its blunt front end is "
        "a single round, gaping mouth ringed with big, square, horribly human teeth around a pink tongue. Near "
        "the head two thick, flipper-like arms with flat, fingered hands sprawl out to the sides, a row of pale "
        "knobs runs along each flank and its underside is dark ribbed red. The serpent of Norse myth that gnaws "
        "the roots of the world tree, it is nothing but a crawling, open mouth."},
  {"Ps0042_010",  // Nigi Mitama
        "A plump teardrop of smooth, glossy teal, about the size of a person's chest, with no limbs at all, its "
        "pointed tip curling up and over to one side like a curl of water or a comma-shaped jewel. On its round "
        "front sits a simple, gentle face: eyes closed in happy crescents under arched brows, a small rounded "
        "nose and a wide, contented smile showing a sliver of white teeth. The peaceful, harmonious side of the "
        "soul in Shinto belief, it floats in perfect contentment, as soothing to look at as a still pool."},
  {"Ps0044_000",  // Neko Shogun
        "A small, round black cat standing upright on short legs in full samurai armour, a cat general of "
        "Japanese legend. Big yellow-green eyes peer from under a black and gold helmet with gold crescents, "
        "pink-lined ears poking through and a flaming red plume on top. Two tall red war banners rise from his "
        "back, one printed with a black paw print and one with a black cat's face. His pale teal armour is edged "
        "in gold and frilly white trim, with a cat-face badge and a red apron in front, and he grips a long black "
        "staff. Small and puffed up with importance, he stands as if commanding an army."},
  {"Ps0044_010",  // Nekomata
        "A tall, lean cat woman with long legs and a narrow waist, sheathed from neck to feet in a skin-tight "
        "black bodysuit, ribbed across the chest, that shows every line of her figure. Over it she wears a "
        "cropped, shaggy jacket of white fur, and her fingers end in black claws. Long, sleek brown hair falls "
        "between pointed black cat ears; slitted golden eyes look out over a black mask striped with white "
        "whiskers and showing two small fangs. A long, thin grey tail hangs behind her. The demon cat of Japanese "
        "folklore in a woman's shape, she looks sleek, teasing and ready to scratch."},
  {"Ps0044_020",  // Nebiros
        "A gaunt, tall figure swallowed by a voluminous red hooded cloak that falls around him in a great "
        "diamond, a demon of the grimoires who commands the dead. Under the hood his face is painted as a skull, "
        "white with purple hollows, one eye rimmed in red, a gold chain hanging from a pointed ear. His thin "
        "purple body is painted with green bones like a costume skeleton, in red shorts and purple and white "
        "striped stockings. Beside him dangles his marionette, a small stick skeleton banded in pale green and "
        "yellow with a cat-eared mask for a head. Theatrical and morbid, a showman of the grave."},
  {"Ps0045_000",  // Norn
        "A great floating wreath of burnished gold, a thick ring of swirling, rippling metal like molten cloud "
        "around a perfectly round hole of pure black. Three women are sculpted into the ring as if grown from it, "
        "each with a single great golden wing, the three wings spaced around the rim like the spokes of a turning "
        "wheel. One sits on top, legs drawn up and long hair streaming, looking down with a cool, heavy-lidded "
        "face; her two sisters lie half sunk into the sides. Loose golden ribbons curl all around the rim. The "
        "three sisters of Norse fate, they keep their silent watch over the void at its centre."},
  {"Ps0051_000",  // Baal Zebul
        "A hulking, pot-bellied brute with smooth blue skin veined in purple, thick limbs and a huge round gut, "
        "his mouth gaping in a fanged roar under glaring red eyes and pointed ears. A wild black mane spills down "
        "his back from under a tiger-striped headband, and a necklace of small skulls and teeth rings his thick "
        "neck. A tiger pelt is slung over one shoulder and wrapped around his belly, the beast's own head, "
        "blue-eyed and snarling, riding on his shoulder beside his face. He carries a long black club headed with "
        "a spiked skull. Bloated and roaring, an old lord of heaven brought down to a devouring ogre."},
  {"Ps0051_010",  // Parvati
        "A tall, slender goddess standing barefoot and composed, with rose-pink hair coiled into two round buns "
        "like lotus buds and a long tail down her back. Magenta eyes and pink lips sit in a calm, gentle face "
        "under a gold tiara with a blue jewel, a lavender veil sprinkled with gold falling from a small white cap "
        "over her shoulders. A fitted pink top hugs her bust above a broad gold collar; below a pink and gold "
        "sash she wears loose saffron trousers under a long pink overskirt open down the front. A pink lotus "
        "hangs from one hand. The goddess of devotion is serene and quietly regal."},
  {"Ps0051_020",  // High Pixie
        "A slender, grown-up fairy standing tall and straight, a spiky crest of icy blue hair standing straight "
        "up above pointed ears, silver hoop earrings, pale blue eyes and plum lips set in a cool, unimpressed "
        "look. Her outfit is half armour: a riveted steel breastplate and collar over a purple leotard cut high "
        "at the hips, dark charcoal leggings, long purple gloves and chunky purple boots. Four tall, pointed "
        "wings rise from her bare back, translucent turquoise and sea green. Taller and sharper than the little "
        "fairies, she carries herself like a captain of a fairy court, pretty and not to be trifled with."},
  {"Ps0051_030",  // Pazuzu
        "A tall, lean demon with a man's tan, sinewy body and the head of a snarling lion, four great tawny wings "
        "spread from his back, two reaching high above his head and two sweeping low past his knees. His face is "
        "fierce and old, blue eyes narrowed and teeth bared inside a shaggy mane and beard of silvery white, and "
        "a crest of curved cream and gold plates rises over his skull like a helmet's comb. A jagged stripe of "
        "rust-red feathers runs down his bare chest to his loins, and his hands and bird-like feet end in claws. "
        "The Mesopotamian king of wind demons looks gaunt, ancient and pitiless."},
  {"Ps0051_040",  // Hanuman
        "A wiry monkey king of Hindu legend, standing tall and bare-chested with his mouth wide open in a fanged "
        "roar, fierce green eyes glaring above a long white beard. A tall golden helmet shaped like a temple "
        "spire sits on his head, a red jewel on its brow, and a broad golden collar of pointed wings set with "
        "teal gems spreads over his shoulders. Gold bands circle his arms and ankles. Below a red sash hangs a "
        "green apron worked with a golden swirl, flanked by long white streamers, and his long tail hangs to the "
        "ground. He holds a curved scimitar. Old, proud and spoiling for a fight."},
  {"Ps0051_050",  // Baphomet
        "A sooty black goat-headed idol sitting cross-legged in the air, shaggy goat legs crossed at the shins "
        "and hooves tucked under, two vast wings of dark brown-black feathers spread wide behind it. Its long "
        "goat's face glows with red eyes under two pairs of great ridged horns curling back and out around a "
        "pointed crest. A lank black mane falls over a woman's breasts capped in glossy black, a white cloth "
        "wraps its hips, and at its belly sits a golden staff wound with twin serpents around a green orb. Half "
        "beast and half woman, it sits like the idol of a black mass, silent and expectant."},
  {"Ps0051_060",  // Hariti
        "A tall, ghostly woman drifting upright in a long hooded robe of dusky rose-red, the hood rising to two "
        "small points like a cat's ears. Her face is porcelain pale, with blood-red eyes, red lips and a lock of "
        "dark hair across her brow. The robe clings to her slim figure and breasts before opening into enormous "
        "trailing sleeves and a ragged hem, slit at the front over a bare leg. Far beneath her bare feet, on a "
        "long purple cord, dangles a tightly swaddled bundle of gold brocade, a hooded baby. The child-eating "
        "demon who became a guardian of children, she looks tender and deeply unsettling at once."},
  {"Ps0051_070",  // Barong
        "A long, low lion-beast of Balinese temple dance, built like a huge shaggy dog under a curtain of coarse "
        "cream-white hair that falls to the ground on every side, sturdy blue legs and paws showing beneath. Its "
        "face is a carved blue mask with bulging orange eyes, square white teeth and pink ears, framed in an "
        "ornate silver headdress studded with blue gems, with a long beard of dark green and blue strands. A "
        "silver spike crowns its head between two thin feelers, and its tail rises straight up as a tall silver "
        "pole topped with a spray of navy ribbons. Gaudy and kindly, it stands like a festival guardian."},
  {"Ps0051_080",  // Power
        "An armoured angel of war standing rigid and square-shouldered, two huge wings of dark slate feathers "
        "rising behind him. His dusky violet face is shadowed, green eyes glaring from under a blood-red helmet "
        "that flares into two curling horns around a central spike. His red armour has a high ribbed collar, "
        "broad shoulder plates with gold rosettes and plated gauntlets and shins, belted in brown leather over a "
        "red and black checked skirt and a long grey-green tabard. He carries a long red spear and a red kite "
        "shield edged in gold, a black octopus sprawled across it. A grim soldier of heaven, he waits for orders."},
  {"Ps0052_000",  // Pixie
        "A tiny fairy, small enough to sit on a shoulder, with a bob of auburn hair curling at her cheeks, big "
        "rose-pink eyes, pointed ears and a sweet, cheeky little smile. She wears a simple high-necked royal blue "
        "leotard with long blue gloves and thigh-high blue boots, each topped with a black crisscross band that "
        "matches her choker. Two pairs of gauzy wings sprout from her back, sky-blue and teal marbled like water, "
        "their tips curling into pale green tendrils. The little fairy of English folklore, she looks bright, "
        "eager and ready to flit off on an errand."},
  {"Ps0052_010",  // Pisaca
        "A gaunt, starved figure with a thin woman's frame, standing on tiptoe on long, wasted legs, its skin "
        "leathery rust-brown and crossed with dark cracks like dried bark. Its head is a smooth, faceless bulb "
        "from which a long, thin stalk juts straight out to each side, each tipped with a single yellow eye. "
        "Where its face and chest should be, a huge mouth splits the body open from throat to belly, dark purple "
        "inside and lined down both edges with rows of curved ivory fangs. Long, spidery arms end in dark claws. "
        "The corpse-eating ghoul of Indian legend, it seems to be nothing but an open, waiting hunger."},
  {"Ps0052_020",  // Bishamonten
        "A broad, solid Buddhist guardian god planted squarely on both feet, deep red skin, gold eyes and a "
        "furious scowl under heavy brows, a thick black moustache curling at the tips. His black hair is pulled "
        "into a topknot capped with a small gold crest. He wears ornate olive-gold armour: a high flared collar, "
        "a studded breastplate, shoulder guards shaped like snarling lion heads, a scaled skirt and plated shins, "
        "with white sleeves and a thick white sash knotted at his waist. One red hand holds a small golden "
        "pagoda, the other a long golden rod. The guardian king of the north, he looks unbending and thunderous."},
  {"Ps0052_030",  // Byakko
        "A colossal white tiger caught mid-prowl, head carried low beneath high, hunched shoulders, its snowy "
        "coat striped in crisp black. Piercing ice-blue eyes glare from a broad scowling face, and its mouth "
        "hangs open in a snarl over long fangs. A great ruff of white fur sweeps back from its cheeks and chest "
        "in points like flames, and more flame-shaped tufts flare around its legs above heavy paws. Its tail is "
        "impossibly long and thin, stretching out straight behind it to a pointed tip like a spear's. The white "
        "tiger who guards the west in Chinese myth, it moves with cold, deliberate menace."},
  {"Ps0053_000",  // Fortuna
        "A tall, long-legged goddess of luck standing barefoot, her waist replaced by a silver spoked wheel like "
        "a chariot's. Long wavy hair of deep royal blue falls from under a small white hood, and her amber eyes "
        "and knowing half-smile give nothing away. A white high-necked halter clings to her full bust and bares "
        "her shoulders and arms, and a short wrapped brown skirt sits low on her hips above long bare legs. Two "
        "long scarves loop around her in great arcs, one twisted brown and one gauzy white, like a wheel forever "
        "turning. Alluring and capricious, she looks as likely to raise you up as to spin you down."},
  {"Ps0053_010",  // Forneus
        "A huge, flat fish-demon gliding low over the ground, part manta ray and part shark, its body spreading "
        "into vast thin fins that sweep far out to either side, a tall shark's dorsal fin rising behind and a "
        "whip-thin tail trailing away. Its hide is charcoal grey dappled with blue-black spots. From its back "
        "rises a squat stony head with narrow teal eyes, curved black horns and a silver crown set with green "
        "gems, while at the front edge of the body two small purple eyes sit above a wide mouth of jagged teeth. "
        "A brooding king of the deep, it lies flat and sly, waiting."},
  {"Ps0053_020",  // Futsunushi
        "A lean, sinewy sword god standing straight and bare-chested, grey-green skin, glaring magenta eyes and a "
        "deep, stern frown. Long straight violet hair falls past his shoulders from under a white headband marked "
        "with a black and white yin-yang, and a leather cord at his throat holds a curved purple jewel. Grey "
        "bandages bind his forearms, waist, loins and thighs, like a fighter who trains until he bleeds. Beside "
        "him stands a tall flat rack of swords, dozens of slim verdigris-green blades upright side by side like a "
        "fence. The Japanese god of the sword, he looks austere and unshakeable, a man who has given everything "
        "to the blade."},
  {"Ps0053_030",  // Flauros
        "A tall, lean leopard demon with no head above its shoulders: its scarlet leopard's face is set low in "
        "its chest, ice-blue eyes glaring over white jowls and bared fangs flanked by gold tusks. Its body is red "
        "fur spotted in black with a white belly. A high-shouldered black leather jacket studded with gold spikes "
        "covers its torso, its collar rising behind into two tall black columns, and between them stands a black "
        "and gold pillar topped by a tiny grinning blue demon face. Black gauntlets end in long gold claws. "
        "Flashy and feral, it looks dressed to swagger and ready to maul."},
  {"Ps0053_040",  // Principality
        "A tall angel in the look of a crusader prince, standing calm and upright, two great wings of olive and "
        "green feathers rising behind him. His pale face is still and faintly sad, golden eyes looking out from "
        "under a silver helmet crowned with long spikes that burst outward like rays of light. A chainmail hood "
        "falls to his shoulders under a short teal capelet; he wears a royal blue tunic and a green surcoat hung "
        "with gold medallions over a long pale robe, a sword at his hip. He holds a long staff tipped with a "
        "golden cross. Dignified and devout, he keeps a silent vigil."},
  {"Ps0054_000",  // Pale Rider
        "A hooded skeleton sitting upright on a pale horse, the fourth horseman of the apocalypse. The rider's "
        "face is a bare, yellowed skull deep inside a black hood, and his black robe falls into enormous ragged "
        "sleeves and a tattered hem that hangs over the horse's flanks, bony gauntleted hands poking out. He "
        "carries a scythe on a long wooden shaft, its thin black blade sweeping in a cruel curve. The horse is "
        "ghostly grey-white, darkening toward its hooves, with pale blue eyes, a long wispy mane falling over its "
        "face and a ragged, smoky tail, harnessed in black straps. Silent and unhurried, death itself comes "
        "riding."},
  {"Ps0054_010",  // Hecatoncheires
        "A hulking giant with smooth, mottled teal skin and the hard muscles of a statue, a fan of ten arms "
        "bursting from its shoulders and back, splayed in every direction, the topmost pair flung up high as if "
        "every hand were straining for something. Its head is a lumpy dome scattered with round, glassy blue "
        "eyes, and three gaping mouths full of big human teeth open on its face and sides. The main mouth is "
        "gagged: a gold chain runs through it and a heavy brass padlock is jammed between its teeth. The "
        "hundred-handed giant of Greek myth, chained by the gods, it seems to struggle without end."},
  {"Ps0054_020",  // Berith
        "An armoured knight on a blood-red warhorse, a duke of hell riding to war. The rider is sealed head to "
        "toe in dark slate-teal plate: a visored helmet topped with a spike and flared crests, golden eyes "
        "glinting through the slit, rounded shoulder plates, spiked elbow guards, flanged gauntlets and a layered "
        "plate skirt. He carries a long golden lance with a barbed point. His horse is muscular and deep red, "
        "with a thick black mane, a long black tail, gold hooves and a dark leather saddle with silver stirrups. "
        "Faceless and martial, the pair look like the head of a cavalry charge, grim and unstoppable."},
  {"Ps0054_030",  // Hell Biker
        "A grinning skull in black leather astride a long chrome chopper, a ghost rider of urban legend. Its head "
        "is a bare, bone-white skull with small fiery orange eyes, and a long red scarf at its throat streams out "
        "behind it like a flag. A black leather biker jacket with a wide collar and silver piping, black gloves, "
        "trousers and knee-high boots complete the look. The motorcycle is all stretched chrome: towering "
        "handlebars, a raked front fork, a round headlamp, an exposed engine and a pink fuel tank painted with a "
        "red heart struck by a yellow lightning bolt. Loud and reckless, it looks out for one last race."},
  {"Ps0054_040",  // Beelzebub
        "A monstrous giant fly squatting hunched on crooked, thorny legs, its bloated, ribbed abdomen curling "
        "down and under it, its body clad in blue-black chitin edged with ragged spines. Huge glossy red compound "
        "eyes bulge beneath a gold helm striped in black like a tiger's hide, its brim sweeping up into horns. A "
        "long rust-red proboscis hangs above a necklace of small grey skulls, and one hooked claw clutches a bone "
        "sceptre tipped with a skull. Two tall, narrow wings stand up from its back, shimmering white, green and "
        "violet, each marked with a skull and crossbones. The lord of the flies, it looks regal and filthy."},
  {"Ps0054_050",  // Belphegor
        "A squat, brawny demon standing hunched with his head thrust forward and long arms hanging, deep purple "
        "skin, tall ridged horns curving up from his brow, pointed ears and a hooked nose over a nasty grin of "
        "jagged teeth. Small red eyes glare from under a heavy scowl, and a scruffy grey beard spills over a "
        "black spiked collar. His hands and lower legs are tan like worn leather gloves and boots, ending in "
        "purple claws, and a thin tail tipped with an arrowhead trails behind him. Right behind him stands his "
        "throne, a gleaming toilet with its lid raised. The demon of sloth, he looks crude and gleefully vulgar."},
  {"Ps0055_000",  // Houou
        "A long-legged crimson bird with its broad wings flung wide, built like a pheasant. From its head rises a "
        "tall golden plume rolled into spirals, like a flame frozen in metal. A spiky red crest rings a small "
        "gold beak and a bright blue eye, and a shaggy ruff of jade-green feathers covers its neck and breast. "
        "Its wings are slate blue in front, edged in red, and solid red behind; one impossibly long, thin "
        "olive-gold tail trails far behind it, and gold legs end in hooked talons. The bird of good omen of East "
        "Asian legend, it holds itself tall and upright, its golden plume raised like a torch."},
  {"Ps0055_010",  // Horus
        "A great golden falcon caught in mid-swoop, wings raised high in a wide V and both feet thrust forward, "
        "talons open to seize its prey. Every feather is gold, from deep amber on its body to pale straw at the "
        "wing tips, and a long fanned tail hangs below it like a train. Its head is compact and fierce, a ruff of "
        "spiky feathers around a hooked pinkish beak and small, hard blue eyes under a frowning brow. Its legs "
        "are scaled in rust red, ending in curved black claws. The falcon of the Egyptian sky god, it strikes "
        "with the glare and blaze of the noon sun."},
  {"Ps0055_020",  // White Rider
        "A crowned skeleton in a hooded black robe, sitting tall on a pale horse. A bare white skull grins from "
        "deep in the hood under a spiked gold crown, and the robe's wide sleeves and hem hang in tattered strips "
        "over the horse's flanks. A quiver of white-fletched arrows rides on his back, and a long, slender bow "
        "rests across the saddle. His mount is chalk white with a wild, straw-pale mane and tail, its whole hide "
        "covered in dozens of open blue eyes staring every way at once. The horseman who rides out to conquer, he "
        "sits still and upright, a king who needs no face."},
  {"Ps0061_000",  // Mara
        "A huge green phallus leaning forward out of a brass war chariot, frankly and unmistakably a penis with a "
        "body. Its ribbed, veined shaft rises to a smooth, hooded dome of a head, and just under the rim gapes a "
        "wide, wet pink mouth with a tongue lolling out. Long tapering green spines fan up and back from it like "
        "quills, and small clawed limbs wave at its sides. The chariot is gleaming brass, a grinning skull on its "
        "front, coiled springs, big spoked wheels and curved silver blades jutting ahead. The demon who tempted "
        "the Buddha with lust, it thrusts itself forward, gaping and shameless."},
  {"Ps0061_010",  // ?
        "A pale, living woman with a bare white skull for a face, standing above a seven-headed red beast. The "
        "skull grins from under a blood-red veil that hangs like a cloak, a gold band across her brow. Her "
        "low-cut red bodice with puffed sleeves bares pale cleavage over billowing purple striped bloomers; long "
        "purple gloves reach her elbows, and one hand holds out a golden goblet. Beneath her crouches the beast, "
        "red and spotted with black diamonds, bat wings spread, seven snarling horned heads each in a small gold "
        "crown. The great harlot of Revelation, she offers her cup with a lover's grin and only bone behind it."},
  {"Ps0061_020",  // Masakado
        "A samurai lord standing stiff and square in heavy court robes, his face half lost in a storm of hair. A "
        "huge, wind-tossed mane of deep blue sweeps over one eye, and the face beneath is chalk white, painted "
        "kabuki-style with red streaks around glaring yellow eyes. His robes are burnished gold printed with thin "
        "rings, boxy at the shoulders over full white sleeves; a white panel at his waist bears a black crest of "
        "small circles around a larger one, and a long sword in a brown scabbard hangs at his side. The rebel "
        "warlord whose angry spirit was said to guard the capital, he glowers out, unbowed."},
  {"Ps0061_030",  // Mada
        "A burly four-armed demon standing before a great turquoise wheel, its head a tall, narrow purple dome "
        "like a mitre. Rows of orange flame strokes climb the dome, and near its base square teeth are bared in a "
        "grimace, framed by fat turquoise curls like tusks and whiskers. Its chest is purple, its thick arms and "
        "legs black, dotted white and banded with white stripes; turquoise discs ring its wrists above clawed "
        "hands, and a flared turquoise frill circles its waist like a skirt. The demon of drunkenness of Hindu "
        "myth, it looks swollen, garish and ready to swallow anything."},
  {"Ps0061_040",  // Matador
        "A skeleton bullfighter standing tall and narrow-hipped, a slim curved sword in one bony hand and a red "
        "cape hung from a rod in the other. A grinning white skull looks out from under a teal tricorn hat edged "
        "in gold braid. His suit of lights is a short teal jacket crusted with gold embroidery, big gold shoulder "
        "pads, rows of gold ornaments set with red jewels down the front, a white cravat pinned with a red stone, "
        "a red sash, tight white trousers striped in gold and tall teal boots. Dead and still dressed for the "
        "ring, he holds himself with the matador's proud, upright poise."},
  {"Ps0062_000",  // Michael
        "A tall, broad-shouldered warrior angel standing straight and barefoot, a long iron spear held level at "
        "his side. His skin is a fiery orange-red, his dark slate hair swept back from a hard, handsome face with "
        "narrowed yellow-green eyes. A gold breastplate moulded to every muscle of his chest sits under ornate "
        "gold shoulder guards, with gold bands at wrists and ankles, and a long white skirt bordered in gold "
        "diamonds falls to his shins, slit up one leg. Huge wings arch up over his head, tan feathers in front "
        "and blazing orange behind. The archangel who leads heaven's armies, he looks stern, steady and ready to "
        "strike."},
  {"Ps0062_010",  // Mishaguji
        "A thin, chalk-white figure with a human body and no face, its head tipped back as if sniffing the air. "
        "The head is a smooth, ridged dome like a grub's, a single thin slit of a mouth across its tip, with "
        "black hair hanging beneath it to the shoulders. A scaly mustard-yellow plate runs down its chest and "
        "belly, red stripes edge its arms and sides, and its forearms and shins turn pink, veined white, ending "
        "in clawed hands and feet. A long ridged tail tapers behind it, and it carries a rough, pinkish spear. "
        "The old snake god of rural Japan, it stands silent, blind and alien."},
  {"Ps0062_020",  // Mitra
        "A lean, crimson-skinned man with the head of a lion, bound from ankles to shoulders in the coils of a "
        "great snake. His lion's face is red, with cold blue eyes, a thick, curling dark brown mane and a full "
        "beard. The snake, banded orange and black, winds around him again and again, and its dark head rears "
        "straight up behind his own, a red tongue flicking above his crown. Two pairs of translucent rose-red "
        "feathered wings rise from his back, and a hooked dark sickle hangs in each hand. The lion-headed god of "
        "the old Persian mysteries, he stands rigid and solemn inside the serpent's grip."},
  {"Ps0062_030",  // Mithras
        "A slim young man rising bare-chested from a great black boulder, sunk in it to the waist as if the rock "
        "were still giving birth to him. His skin is pale lavender-grey, his face fine and cool with red eyes, "
        "and long golden hair tumbles past his chest in heavy corkscrew ringlets under a small crested gold "
        "helmet. The boulder is rough and pitted, carved all over with golden zodiac signs, and a smooth pink "
        "crystal wedge opens in its front where his body meets the stone. The god born from a rock, he looks calm "
        "and remote, half emerged and in no hurry."},
  {"Ps0064_000",  // Metatron
        "A towering archangel who seems carved from silver and marble, standing perfectly straight beneath two "
        "great wings. His skin is cold metallic grey, his golden hair swept back in waves, his stern face set "
        "with piercing green eyes and a gold mark on the brow. Silver plate scrolled with gold covers his arms "
        "and legs; a white robe drapes from one shoulder, and a long white tabard falls to his shins, a tall gold "
        "cross down its front and ribbons trailing from a knotted sash. His pale grey wings rise high, their tips "
        "ending in dark round knobs. The voice of God in Jewish legend, he looks impassive and absolute."},
  {"Ps0064_010",  // Melchizedek
        "A tall armoured angel with no face at all, standing square and stiff like a machine. His head is a "
        "smooth gold helmet, blank and rounded, a single ridge running down its front to a beak-like point where "
        "a face should be. His muscled body is clad in vivid purple with a white panel down the chest and belly; "
        "ribbed gold gauntlets sheathe his forearms, huge segmented gold greaves his shins, and a spiked gold "
        "collar holds a round turquoise jewel at his breast. Behind him spread stiff grey wings of straight "
        "slats, like shutters. The priest-king of scripture remade as a weapon, he looks cold and implacable."},
  {"Ps0065_000",  // Mokoi
        "A gangly green figure that looks whittled from a sapling, standing loose-limbed and slightly hunched. "
        "Its head is a tall block like a tree stump, sliced at a slant on top to show reddish growth rings, with "
        "two big round staring white eyes and a thin, flat red line of a mouth. Its body is dark green and "
        "cracked like wood grain, a small pot belly above a white cloth knotted loosely round its hips, its arms "
        "long and mitten-like, its legs straight as posts. One hand holds a red boomerang tipped in yellow. A "
        "night spirit of Aboriginal Australian legend, it stares blankly, comic at first, then quietly sinister."},
  {"Ps0065_010",  // Mothman
        "A tall, egg-shaped bundle of shaggy steel-blue fur balanced on two long, spindly dark legs with bird's "
        "feet, wings spread wide at its shoulders. Its round head has two glinting red eyes and a wide, flat "
        "black slot of a mouth, and two thin antennae curve up from it, each tipped with a little green and blue "
        "feathery fan. The wings are plain blue behind, but in front they blaze with big black-ringed eyespots on "
        "red and yellow, edged with dark green feathers. The winged figure said to haunt the night before a "
        "disaster, it stands stiff and gawky, comic and ominous at once."},
  {"Ps0065_020",  // Mot
        "An upright coffin of weathered gold stone that lives, two long, thin arms reaching out from holes in its "
        "sides. Its six-sided lid is carved like a temple relief: an eye shooting rays, a crescent moon and a "
        "sun, and below them a stiff, long-eared figure between spread wings above a coiling serpent, with lines "
        "of strange script at top and bottom. A single dark, curved horn juts up from the carved eye. The arms "
        "are scaled in purple netted with bright red veins, ending in clawed hands. The old Canaanite god of "
        "death, it stands sealed and still, only its arms groping out into the world."},
  {"Ps0071_000",  // Yakshini
        "A tall, slender demoness with violet skin, bare-breasted, a curved sabre held low in each hand. Long, "
        "straight black hair pours down her front, barely covering her breasts, and leaves her flat belly bare. "
        "Her face is sharp and cool, with pointed ears, bright blue eyes and two small fangs, under a spiky gold "
        "headdress set with red jewels from which two long gold horns sweep up. Gold bands ring her arms and "
        "ankles, and her only clothing is a short red and white wave-patterned skirt hung with gold discs. A "
        "blood-drinking tree spirit of Indian legend, she looks lithe, alluring and coldly ready to kill."},
  {"Ps0071_010",  // Yatagarasu
        "A big blue-black crow standing upright on three legs, wings spread wide. Its feathers are glossy and "
        "dark, sleek on its body and broad on its wings, with a long, tapering tail sweeping to the ground behind "
        "it. A heavy curved beak of dull grey horn juts from its face, and small red eyes glare out under a "
        "stern, frowning brow. Around its neck a black cord hangs a cluster of three fat red comma-shaped jewels "
        "against its breast, and its three scaly legs end in hooked claws. The sun's crow of Japanese myth, sent "
        "to guide the first emperor, it looks proud, grave and watchful."},
  {"Ps0071_020",  // Yamata-no-Orochi
        "An eight-headed serpent whose necks rise straight up from one low body like a grove of tall green "
        "columns, four on each side with a gap between. Each neck is scaled deep mossy green along the back and "
        "banded pale tan down the ribbed belly, thick at the base and tapering high above to a narrow snake's "
        "head with small icy blue eyes; several of the heads gape open to show their dark throats. A long, heavy "
        "green tail runs out behind along the ground. The great serpent of Japanese myth that devoured a maiden "
        "each year, it stands tall, still and many-mouthed, watching from every height at once."},
  {"Ps0072_000",  // Unicorn
        "A slender unicorn standing square on four long legs, head held high and its horn tilted forward like a "
        "lance. Its coat is a pale silvery lavender-white, smooth over a fine-boned, well-muscled body, and each "
        "hoof is capped in gold. The horn is long, spiralled and golden, rising from a shaggy, windswept mane of "
        "pale silver-green, and a tail of the same colour streams straight out behind as if caught in a wind. Its "
        "face is narrow, with pointed ears and small, sharp red eyes. The creature of legend that only the pure "
        "may approach, it looks graceful, proud and wary."},
  {"Ps0072_010",  // Yurlungur
        "An impossibly long, thin serpent, a smooth tube of a body many times longer than a person is tall and no "
        "thicker than an arm. Its colours run through the whole rainbow along its length, from magenta and violet "
        "through sky blue, green and yellow to deep red and back to pink, and all along it run bold black bars "
        "and squared spirals like painted designs. Its head is blunt and rounded, a deep purple, with two small "
        "round gold eyes set wide apart. The rainbow serpent of Aboriginal Australian legend, which carved the "
        "rivers as it moved, it looks calm, ancient and endless."},
  {"Ps0081_000",  // Rakshasa
        "A lean, sinewy demon warrior, his muscled body a deep reddish pink wrapped in spiralling pale pink "
        "bands, as if bound in ribbons from neck to ankles. His face is a hard, helmet-like mask: a ridged brow "
        "striped in pale pink, pointed ears and a sullen, downturned mouth, with two long, thin red horns "
        "sweeping up high above it like antennae. Long straight black hair falls past his shoulders. A broad "
        "black sash with a round gold boss cinches his waist, black panels hanging in front, and a thin straight "
        "sword rests in each hand. The man-eating demon of Indian myth, he stands quick-limbed and scowling."},
  {"Ps0081_010",  // Lakshmi
        "A slim, graceful goddess floating on pointed toes, a ribbon of sheer golden silk arching high over her "
        "head and trailing out to both sides. Her honey-blonde hair is sculpted into rolled curls under a small "
        "silver tiara with a blue jewel, and her calm face has pale turquoise eyes, teal lips and a gold mark on "
        "her brow. A wide silver collar and red beads circle her neck above a short pale blue top that bares her "
        "midriff, under an open black vest; loose pale blue trousers gather at her bare ankles beneath a panelled "
        "black overskirt. The Hindu goddess of fortune and plenty, she drifts poised and serene."},
  {"Ps0081_020",  // Lachesis
        "A slim woman standing straight and still inside a stiff grey mantle that flares from her shoulders to "
        "her hips like a box, woven of interlocking metal links and open down the front. Beneath it a ribbed "
        "crimson bodysuit covers her from throat to ankles. Her pale, mask-like face has golden eyes and an "
        "unreadable calm, framed by a big golden bob with a lilac puff at each side, and a braided gold band "
        "rings her head and loops up into a handle like a basket's. A long, thin measuring rod floats level at "
        "her waist. The Fate who measures each life's thread, she looks patient and exact."},
  {"Ps0081_030",  // Raphael
        "A tall, clean-cut archangel standing straight, a long sword with a gold hilt in one hand. His skin is "
        "pale lavender, his spiky golden hair swept high and back, his sharp face set with narrow green eyes and "
        "a cool, level stare. He wears close-fitting royal blue armour with a ribbed high collar, rounded "
        "shoulder plates and greaves, a white sash across his chest from a gold clasp at one shoulder, and a long "
        "white tabard marked with gold crosses. Big wings spread from his back, pale blue-grey in front and deep "
        "violet behind. The archangel of healing, he looks composed, righteous and quietly proud."},
  {"Ps0081_040",  // Lamia
        "A woman above the hips and a serpent below, her body rising from a red snake's tail many times her own "
        "height. From the waist up she is slender and bare-breasted, long, wavy blue-black hair falling over her "
        "shoulders and partly across her breasts, with pointed ears, blue eyes and a faint, knowing smile. A gold "
        "collar with a blue pendant circles her throat, and gold bands ring her arms. The tail is scaled in rich "
        "red with dark swirls along its back and a ridged brown belly, tapering to a fine point. The serpent "
        "queen of Greek legend, she looks cool, alluring and patient."},
  {"Ps0081_050",  // Rangda
        "A witch-queen buried in a vast, spiky black mane that bursts around her head and pours down behind her "
        "to the ground. Her face is red, with bulging blue eyes, curved white tusks and a bundle of green sticks "
        "clenched in her teeth. Her bare breasts are painted pink with black swirls under a gold collar, and her "
        "long red arms end in enormous, needle-thin claws. At her waist hangs a gold demon mask with red eyes, "
        "dropping a long striped panel like a tongue, flanked by strings of black and red lanterns ending in gold "
        "hooks. The witch of Balinese dance-drama, she looks savage, garish and terrifying."},
  {"Ps0082_000",  // Leanan Sidhe
        "A tall, gaunt, bloodless beauty in a long, clinging violet-black gown. Its stiff collar flares up behind "
        "her neck, its neckline plunges in a narrow V almost to her navel, baring the inner curves of her "
        "breasts, and a slit runs up one leg. Straight blonde hair, held back by a dark band, falls in one sheet "
        "down her back and past her heels. Her face is sharp and pale, with pointed ears, red eyes and dark red "
        "lips in a cool half-smile, and small silver trinkets glint in her hands. The fairy lover of Irish legend "
        "who drains her poets dry, she looks elegant, hungry and unhurried."},
  {"Ps0082_010",  // Lilith
        "A slender, chalk-white woman almost naked, a huge brown python draped around her neck and hanging down "
        "her body past her knees, its head resting at her belly with a red tongue flicking. Her only covering is "
        "grey and black snakeskin wound round her in strips: a band across her breasts, a scaled collar, a patch "
        "over her crotch, coils down her arms and legs, and a patch over one side of her face. Her black hair is "
        "swept up and back in a sleek crest, her eyes gold with slit pupils above dark lips. Adam's first wife of "
        "Hebrew legend, turned demon, she looks cold, bare and serenely seductive."},
  {"Ps0082_020",  // Lilim
        "A lithe, long-legged young demon woman standing easy, with smooth tan skin, sleek black hair to her "
        "shoulders, pointed ears, blue eyes and full pink lips in a small, sure smile. A tiny cropped white "
        "jacket with a high zipped collar hangs open over her bare chest, barely covering her breasts, above low "
        "white hot pants with a broad belt and a round silver buckle. White gloves, bare legs and feet, and a "
        "small dark tattoo on one thigh. Plum-red bat wings spread from her back, and a thin tail ends in an "
        "arrowhead. A daughter of the night demons of legend, she looks playful and flirtatious."},
  {"Ps0083_000",  // Lucifer
        "A towering fallen angel hanging in the air, legs together and feet pointed down, clawed hands splayed "
        "inside a great spread of six bat wings. His body is dark blue-green and ribbed with sinew, and long, "
        "ridged ivory horns curl up from his brow like a ram's. Wild golden hair falls about a grim, scowling "
        "face with red eyes. The wings fan out in three pairs, dark teal outside and blood red within, veined "
        "like flesh, their joints hooked into claws. Long ribbons of pale grey cloth wind loosely round his body "
        "and drift above his head. The rebel angel cast out of heaven, he looks vast, proud and terrible."},
  {"Ps0083_010",  // Helel
        "A slender, naked angel standing calm at the centre of six great white wings, three pairs fanning out on "
        "every side, softly tinged with lilac. His skin is pale and ashen, his face fine and androgynous with "
        "glowing gold eyes, and long golden hair falls straight past his waist. Two thick, ridged grey horns "
        "curve out and up from his head like a ram's, the only dark thing about him. A long ribbon of pale "
        "lavender-silver cloth spirals loosely round his body from chest to ankles and streams up above his head. "
        "The morning star before the fall, he looks radiant and serene, the horns already curling from his head."},
  {"Ps0084_000",  // Legion
        "A floating ball of fused crimson flesh about the size of a person, made of bald, bulging heads crushed "
        "together, every face screaming, mouths stretched wide over rows of square teeth, brows knotted and small "
        "yellow eyes glaring. Veins and folds ripple across the purplish-red skin. Thick, ringed tendrils like "
        "fat worms wriggle out all round it, ending in pointed, diamond-shaped tips, more of them crawl over its "
        "surface between the faces, and a few hang down beneath it like dangling legs. The many demons who "
        "answered to one name in the Gospel, it is a howling crowd packed into one body, every mouth open in the "
        "same scream."},
  {"Ps0085_000",  // Loa
        "A giant human skull hanging in the air with a snake wound through it. The skull is pale bone with a few "
        "dark cracks across the crown, its eye sockets black and its grin full of big square teeth. A long, "
        "slender snake, dark green above and golden yellow beneath, coils over the crown, slips through one eye "
        "socket and around the jaw, and trails its tail below; its head rears out beside the other eye, red eyes "
        "glinting and jaws open on a purplish lining. A voodoo spirit of death, grave and serpent in one, it is "
        "stark and silent, the snake the only living thing in it."},
  {"Ps0085_010",  // ?
        "A tall, slim trickster in a skin-tight dark purple suit, huge purple-black bat wings rising behind him "
        "and curling over at the tips. His face is split down the middle, one half pale sea-green and the other "
        "dark brown with a green slash across the cheek; his eyes are closed, his lips curved in a small, private "
        "smile. Long, straight blond hair falls in a curtain past his shoulders. Square silver clasps fasten the "
        "suit down his chest, silver rings stack up his neck, and his boots curl up at the toes like a jester's. "
        "The Norse god of mischief, he looks elegant, amused and not to be trusted."},
  {"Ps1001_010",  // Orpheus
        "A lean mechanical bard fused to a great lyre: its pale green arms curl up behind his shoulders to a "
        "shell-shaped crest above his head, and its blue strings run down his back, so he seems to be the "
        "instrument as much as its player. Ash-white hair falls over a dark grey face, one red eye glowing "
        "through it, with a pale blue band across his brow and a red scarf wound high at his throat. His body is "
        "teal plating with dotted speaker grilles on the chest and a round porthole in his belly; his limbs are "
        "puffy grey sleeves and stiff, pillar-like legs, like a marionette's. The singer who walked into the "
        "underworld, remade as a machine, he stands guarded and silent behind his hair."},
  {"Ps1001_011",  // Orpheus Telos
        "A lean mechanical bard fused to a great golden lyre: its arms curl up behind his shoulders to a "
        "shell-shaped crest above his head, and its gold strings run down his back, so he seems to be the "
        "instrument as much as its player. Golden hair falls over a pale grey face, one bright cyan eye shining "
        "through it, with a red band across his brow and a grey scarf at his throat. His body is glossy red "
        "plating piped in gold, a gold-rimmed porthole in his belly; his legs are stiff grey pillars, like a "
        "marionette's. The underworld singer reborn in red and gold, he stands bright and complete."},
  {"Ps1001_020",  // Io
        "A slender, slate-grey girl riding inside a huge bull's skull of polished ivory and black, sitting low in "
        "a padded orange seat set into its brow with her knees drawn up. Her eyes are closed, black tears "
        "streaking down from them, and her golden hair is braided up into a tall plume that curls above her head "
        "like a flame. She wears a loose salmon-pink blouse with fluttering sleeves and a gold choker. The skull "
        "is part machine, bolted and panelled in black, with two towering ridged horns and painted eyes ringed in "
        "black lashes. The maiden of Greek myth turned into a heifer, she rides quiet, sad and patient."},
  {"Ps1001_030",  // Hermes
        "A slim, dark figure hanging upright in the air, toes pointed down, between two great golden wings that "
        "are not feathered but cut from metal into sweeping, lacy openwork studded with rivets. Its face is "
        "hidden behind a gold helmet with a black grilled visor, swept back into a long winged blade of silver "
        "and gold. It wears a fitted, high-collared bronze-brown coat whose long skirt is cut into jagged panels, "
        "gold trim at the collar, bronze gauntlets and tall bronze boots over black tights. The swift messenger "
        "god of Greece, it looks sleek, sharp and built for speed."},
  {"Ps1001_040",  // Polydeuces
        "A hulking, top-heavy giant with vast shoulders and bulging arms, his tiny head sunk so deep into his "
        "collar that only a blank pale face with two round, empty eyes peers out under a heavy blond fringe. Long "
        "golden hair pours down his back to his thighs. His pale teal bodysuit is criss-crossed with stitched "
        "cream straps, a vest of square silver plates armours his chest, and plated belts ring his hips and legs. "
        "His hands are red, one forearm is a huge grey syringe ending in a needle, and his legs taper to thin red "
        "points. The boxer twin of Greek myth, he looks mute and massive."},
  {"Ps1001_050",  // Penthesilea
        "A tall, slim duellist queen, her face sealed inside a smooth teal-grey knight's helm with only a narrow "
        "eye slit, a tiny gold crown perched on top. A navy jacket with a high, flared collar hangs open over a "
        "teal steel corset pinched hard at the waist, riveted cups moulded over her breasts and a short flared "
        "plate for a skirt. Silver chains loop at her shoulders and a white lace cravat falls down her chest. "
        "Wide white cuffs flare at her wrists and atop black heeled boots over dark green stockings, and a "
        "slender gold-hilted sword lies at her feet. A faceless Amazon queen, she stands cold, shapely, "
        "untouchable."},
  {"Ps1001_060",  // Lucia
        "A woman rising from an enormous ball gown, its skirt a vast glossy dome of deep blue and teal, mottled "
        "like a night sky and netted in gold filigree spreading from a sunburst at its front. Rose-pink silk "
        "drapes the dome and pours out behind into a long train. Above it rise a slim pink corset, a black "
        "off-shoulder top and long pink sleeves with frilled cuffs. Bandages wrap her whole head, leaving only a "
        "smooth blood-red face with parted lips, and a wild mane of ash-blonde hair streams out to both sides. "
        "Blind and stately, she rests in her great skirt like a mother sheltering all beneath it."},
  {"Ps1001_070",  // Palladion
        "A tall goddess who seems carved from teal stone, gown, skin and face all one colour, her long skirt "
        "sweeping out in great rippling folds that swirl behind her as if she were gliding. Her face is blank and "
        "serene between two long braids. A teal helmet traced in gold rises to a tall red horsehair crest, a "
        "black spearhead jutting straight up through its middle. A golden mantle of fish-scale plates covers her "
        "shoulders, a round sun face at its centre, a gold sash binds her waist, and wide fluted sleeves hang "
        "from her arms. The guardian statue of a war goddess, she moves with calm, unhurried grace."},
  {"Ps1001_080",  // Nemesis
        "A tall, skeletal machine of dark slate-blue armour, angular and bony, its head a pointed spire and its "
        "legs tapering to two long stilt-like spikes. Two round orange eyes stare from its broad chest plate "
        "either side of a thin glowing blue seam running down its whole body. That seam is the edge of a huge "
        "dark wheel encircling it front to back like a gyroscope: a heavy gear ringed with blazing blue teeth, a "
        "zigzag of blue light and a thin gold ring inside, the body hung within it like a mechanism. Thin arms "
        "end in clawed fingers. Retribution made clockwork, it waits, unblinking, for the wheel to turn."},
  {"Ps1001_090",  // ?
        "A three-headed hound taller than a man, standing high on four long legs sheathed in engraved silver "
        "greaves that end not in paws but in trident points. Its heads are black with white muzzles and narrow "
        "yellow eyes, lips peeled back over red gums and teeth, each on a long blue neck guarded by an engraved "
        "silver collar plate, and heavy chains loop across its broad blue chest. Its lean body is black above and "
        "blue beneath, small ragged wings rise from its back, and a long, thin spiked tail juts straight out "
        "behind. The watchdog of the dead, it stands braced and snarling three ways at once."},
  {"Ps1001_100",  // Castor
        "A hulking dark rider fused with his warhorse. Out of his chest juts the horse's head in grey barding, a "
        "long golden horn on its brow and loose reins trailing, while its black hindquarters and a heavy hoof "
        "kick out behind him below ragged dark plates. He is massive in a black bodysuit seamed with silver "
        "stitching, a vest of riveted grey steel squares and red straps buckled round his arms, his hands and "
        "feet a bare deep blue. His head is a small pale skull-like face sunk between his shoulders under a blond "
        "fringe, golden hair pouring down his back. Grim and heavy, rider and steed are one beast."},
  {"Ps1001_110",  // ?
        "An empty ball gown standing on its own, no woman inside. Where her body should be, a slender gold "
        "lattice like a little tower rises from a ring of cream roses on a fluted white bodice, and below a "
        "second band of roses the wide white skirt falls in gathered swags. Atop the tower perches a narrow "
        "crimson head with small hollow eyes, spreading two vast butterfly wings of glowing red stained glass, "
        "veined dark crimson, curling into spirals above and dripping into long thin trails below. Two drifting "
        "grey ribbons stand in for arms. Lovely and hollow, it is a dress worn by a ghost."},
  {"Ps1002_010",  // Messiah
        "A lean, pale saviour before a towering slate-grey cross, its upright rising far above his head and its "
        "base spreading into great downswept wings of grey feathers, a white gloved hand lifted palm up at each "
        "wing's shoulder. His long limbs are bound in ribbed cream wrappings like grave bandages, a short teal "
        "top bares his ridged stomach, and a grey hood and scarf wrap his head and throat. Golden hair falls "
        "across a smooth white mask cracked down one side, one red eye showing. He holds a long black rod banded "
        "in grey. Solemn and still, he looks newly risen from the coffin."},
  {"Ps1002_020",  // ?
        "A winged goddess of ancient Egypt in gold, black and enamel, her body ending at the waist in a gold "
        "spindle point so that she hovers, all wings and headdress. Two tall black horns curve up from her brow "
        "to cradle a great glossy red sun disc. Her face is pale and calm under a white headdress, eyes ringed in "
        "violet, her slim black body laced with gold. Red and blue feathers cap her shoulders, a gold ring stands "
        "at each side, and her arms sweep out into long wings enamelled red and blue, edged in ivory. Serene and "
        "watchful, she spreads her wings like a mother shielding her own."},
  {"Ps1002_030",  // ?
        "A slim, upright figure in glossy red, framed by two huge golden wings of riveted openwork, pierced and "
        "lacy as filigree, curving up around it like a gilded frame. Its head is a white beaked helmet with a "
        "black lattice visor and a red ball on the crest, sweeping back into a long silver and gold blade. A "
        "high-collared red coat pinstriped in gold flares into a short skirt of jagged panels over tall red "
        "boots, with red gauntlets and silver shoulder plates, and from one shoulder a third, blade-like wing "
        "juts straight back. The thrice-great alchemist, it stands poised and brilliant, a herald of "
        "transformation."},
  {"Ps1002_040",  // ?
        "A towering emperor standing with his bare black feet on a small globe of the Earth, the world underfoot. "
        "A tall white hood crowned with a silver laurel wreath frames a black face with glowing red eyes; a white "
        "scarf is knotted at his throat over a red-lined white cape. His chest opens like a lit shrine: in a "
        "glowing red niche sits a small dark man on a throne, legs crossed and chin on hand, lost in thought. "
        "Dark, muscular arms banded in silver jut from stacked shoulder plates, white scales skirt his waist, and "
        "a plain sword lies ready. Proud and composed, he rules by thinking."},
  {"Ps1002_050",  // ?
        "A haughty warrior queen in navy and gold, all hard edges and bristling spikes. A bright red mask covers "
        "her eyes and hair, gold ram-like curls at each ear, above a pale face and closed lips. Her high-collared "
        "navy coat opens on a white cravat and a gold-ribbed navy corset that pinches her waist and moulds "
        "riveted cups over her breasts. Saw-toothed gold plates and steel spikes flare from her shoulders and "
        "hips, a stone lion's face glowers at her belt, and a full navy skirt puffs out above long green boots. A "
        "needle-thin rapier lies at her feet. Severe and alluring, she rules by fear."},
  {"Ps1002_060",  // Juno
        "A towering queen rising from an enormous dome of a skirt, glossy deep blue netted in gold scrollwork "
        "that blooms into petals around a red panel, crimson silk draped over it and sweeping behind into a long "
        "train. Above a slim red corset, a black off-shoulder top and long red sleeves, her face is a white mask "
        "set with a cluster of orange almond-shaped eyes, framed by a frilled red and white bonnet and pale blue "
        "hair. Behind her shoulders spreads a broad fan of charcoal wings edged in red and set with peacock eyes "
        "in teal, blue and orange. Regal and all-seeing, she watches from every eye at once."},
  {"Ps1002_070",  // ?
        "A war goddess almost hidden behind a huge round shield of royal blue and gold, ringed with gold waves "
        "and worked with a stern face of red eyes and a downturned mouth. The shield rides on a long "
        "blue-and-gold lance, a gold spearhead at its tip and a round mirror at its other end. Above the rim show "
        "her calm blue-grey face and long brown braids under a gold Greek helmet topped by a tiny sphinx and a "
        "tall red crest, a golden mantle of fish scales on her shoulders. Below, a white gown billows in deep "
        "folds where legs would be. Vigilant and fearless, she leads with her shield."},
  {"Ps1002_080",  // ?
        "A tall, spindly war machine in red-orange and black armour whose shoulders are two great black spheres, "
        "each held in a skeletal steel cage, studded with small orange-lit plates and marked on its outer face "
        "with bold orange zodiac signs: twins, lion, crab and more. Two broad silver bands cross in a great X "
        "over its chest, looping round both spheres like the paths of orbits. The body between is an angular "
        "orange block with no face; long thin arms hang from the spheres to clawed black hands, and its legs "
        "taper into orange spikes. Cold and celestial, it carries the heavens on its shoulders as judgement."},
  {"Ps1005_010",  // Thanatos
        "A tall, gaunt reaper whose wings are coffins: eight black caskets fan out from its back like great "
        "feathers, chained together, each lid inlaid in blue with a pale carved figure lying shrouded. Its face "
        "is a white skull-like mask drawn into a sharp beak, a jagged grin of dark teeth beneath. A long, "
        "high-collared navy greatcoat studded with silver rivets flares around stick-thin legs of bone-white "
        "plate tipped in gold, red straps cross its chest, a gold buckle shines at its belt and a long black "
        "sword hangs at its hip. Death in a soldier's coat, it stands silent, upright and inevitable."},
  {"Ps2001_010",  // Hypnos
        "A slender, bald, naked figure, smooth and sexless as a mannequin, its pale sea-green skin threaded all "
        "over with thin branching red veins, as if the body had been peeled back to its circulation. A dark grey "
        "sleep mask on a thin strap covers its eyes. From its back a cage of bright red ribs curves out and "
        "gathers into two long black arms, which end in huge ragged wings of torn charcoal feathers spreading far "
        "wider than the body is tall. The god of sleep, it stands blind, bare and calm, like a sleepwalker who "
        "has no intention of waking."},
  {"Ps2001_020",  // Moros
        "A tall, stilt-legged machine stacked from cones like a clock tower taken apart. Its head is a wide "
        "grey-steel cone turned point down, its rim engraved with numerals like a clock face and banded in teal, "
        "a thin white spire rising above a black strip of scrolling green digital lettering. Point meets point "
        "below it with a second funnel, hourglass fashion, narrowing to a spike between legs of ball joints and "
        "slim white shafts with flat feet. One arm is a single rod strung with white spheres, like a clock hand, "
        "ending in green prongs. Faceless and upright, it stands like a countdown on legs."},
  {"Ps2001_030",  // Medea
        "A tall, impossibly slender woman, long-limbed and narrow-waisted, her body sheathed in matte black that "
        "clings to her breasts and hips, her arms and long legs glossy blood red, licked with gold flames at "
        "shoulders and thighs. A thin gold line runs from her throat down between her breasts to a gold heart "
        "ornament at her belly. Her face is hidden by a pale bone mask with curled ram's horns and narrow, "
        "glaring red eyes, and ropy straw-gold dreadlocks fall to her thighs. A wavy black dagger and a small "
        "gold chalice lie at her pointed feet. The scorned sorceress of poison, she is elegant, sensual and "
        "vicious."},
  {"Ps5001_010",  // Arsène
        "A tall, lean gentleman devil standing between two enormous wings of glossy black feathers with a violet "
        "sheen, spread wider than he is tall. A towering black top hat crowns a black and red mask whose long, "
        "sharp points sweep forward and out like a blade, over a white frilled cravat bunched at his throat "
        "beneath a fine gold chain. His fitted blood-red tailcoat opens on a black laced waistcoat, and red "
        "sleeves end in long black claws. His legs run into high red boots with black spurred heels like talons. "
        "The gentleman thief turned demon, he stands sleek, theatrical and wicked, ready to steal with a "
        "flourish."},
  {"Ps5001_020",  // Captain Kidd
        "A skeleton pirate captain standing on the deck of a small black galleon that he rides like a raft, its "
        "hull broadside beneath his boots. A black tricorn hat edged in gold and marked with a skull and "
        "crossbones shades a grinning white skull with one glowing red eye. Two broad cutlasses cross in an X at "
        "his collar, framing his face, and grey belts cross his chest over a tight blue jacket with gold "
        "frogging, chains hanging from them to two anchors. His arms end in chunky black cannons with gold "
        "muzzles, and a tattered red and black coat streams behind. Swaggering and gleeful, he is all buccaneer "
        "bravado."},
  {"Ps5001_030",  // Zorro
        "A hulking masked swordsman built like a cartoon strongman: a huge barrel chest and great rounded arms "
        "and shoulders, perched on thin, spindly legs. His tight black outfit is embroidered with silver vines "
        "and studded with rivets, cinched by a red sash and an ornate silver buckle shaped like a bold Z. His "
        "small head hides under a black hood and mask with sharp yellow eyes, framed by a tall, pointed white "
        "collar, and a wide-brimmed black hat and a sweeping black cape flare out behind him. In one big hand he "
        "holds a slim silver rapier. Barrel-chested and gallant, he is the masked avenger at his most swaggering."},
  {"Ps5001_040",  // Carmen
        "A tall, curvaceous temptress in a flamenco gown of tiered ruffles striped red, black and coral, the "
        "skirt swirling out to one side as if caught mid-turn over red high heels. Her rose-heaped bodice plunges "
        "almost to the waist, baring the inner curves of her full pink breasts. Her pink face hides behind a dark "
        "speckled masquerade mask, a cigarette at her lips, black hair piled into two drill-curled buns. From her "
        "lacy black gloves run thorny green vines, leashes to two small men in black suits with big pink hearts "
        "for heads and dazed heart eyes. Sultry and dangerous, she keeps her admirers on a leash."},
  {"Ps5001_050",  // Goemon
        "A flamboyant kabuki outlaw posed on a tall black and gold wooden clog, his robe's enormous winged "
        "sleeves spread wide like a stage curtain. A huge rope of twisted navy and white rises in two loops over "
        "his shoulders, and a dark purple cap tops a white kabuki face streaked with red and teal. The black "
        "sleeves are trimmed in teal and lined with pink leopard print, over a red cross-wrapped front, a black "
        "and white diamond-patterned undergarment and a yellow chequered sash knotted with red cord. He holds out "
        "a long white pipe painted with gold flowers. Loud and proud, he plays the thief to the back row."},
  {"Ps5001_060",  // Johanna
        "A heavy armoured motorcycle with no rider, low, long and broad as a beast of chrome. Its body is "
        "polished pale silver-blue steel in sharp, curving plates with fin-like flares, bulging side panels "
        "sweeping back over deep chrome engine blocks, and two fat treaded tyres on turbine-spoked wheels. Over "
        "the front wheel rises a tall crest of deep royal blue, swept back like a helmet's plume or a head of "
        "hair, with long silver handlebars spreading from behind it above a low black seat. Gleaming and squat, "
        "it crouches like a war mount waiting for its rider, built to charge straight through anything in its "
        "way."},
  {"Ps5001_070",  // Milady
        "A noblewoman who is almost all ballgown and has no head. Above a slim black corset that pushes up her "
        "breasts, between puffed sleeves striped pink and red, rises only a stiff white fan-shaped collar with a "
        "teal ribbon at the throat and nothing inside it. The face is on the skirt instead: its vast hot-magenta "
        "bell is painted with shut, lashed eyes and smiling gold lips among gold lilies and vines, hemmed in pink "
        "ruffles and gold fringe and swagged with wine-red drapes. A small dagger hangs at her breast. Elegant "
        "and quietly deadly, she smiles with her eyes closed, her secrets beneath her skirts."},
  {"Ps5001_080",  // Robin Hood
        "A broad, heavily muscled hero in sculpted white and silver armour trimmed in gold, half outlaw archer "
        "and half comic-book superhero. A blue heart-shaped plate on his chest bears a bold gold and red emblem "
        "of two letters, R and H, above moulded abdominal plates, a red studded belt and a short fringed skirt. "
        "Gold epaulettes tipped with red spikes cap his shoulders, and his black helmet rises to a red crest "
        "between two swept gold wings. A long cape speckled blue and white streams behind him, and he carries a "
        "long golden arrow like a lance. Square-shouldered and earnest, he looks ready to pose for his own "
        "poster."},
  {"Ps5001_090",  // Cendrillon
        "A tall, delicate fairy-tale princess in armour of cut glass, her long, slender legs sheathed in faceted "
        "royal and sky-blue crystal tapering to sharp gold points for feet. Her bodice is ice-blue crystal around "
        "a violet gem, her arms black and traced with cyan swirls. A black face with glowing cyan eyes and pink "
        "lips peeks from a blue hood under a gold visored helmet, crowned with a big pale cyan bow whose tails "
        "flare like little wings. Gold filigree rises behind her neck and flares at her hips, and a sheer white "
        "cape hangs behind like a petticoat. A princess armed for battle, she stands light and glittering."},
  {"Ps5002_010",  // Satanael
        "A towering fallen god held in a storm of wings: six huge, ragged black bat wings, lined with dark "
        "feathers and barbed in gold, spread around him in tiers far wider than he is tall. His lean body is "
        "armoured in black and ash grey, fluted gold-trimmed plates over shoulders and hips, his gold-buttoned "
        "jacket crossed by a crimson sash to a gold star medal. His small head sits low between high shoulders, a "
        "gilded mask between two golden horns sweeping sideways. One clawed hand holds a long, needle-thin dark "
        "weapon with a gilded grip. Majestic and ominous, he hangs in the air, wings spread in open defiance."},
  {"Ps5002_020",  // Seiten Taisei
        "A stocky, muscular monkey king standing on a round black storm cloud curled with spiral puffs, a yellow "
        "and red eye at one end, a dark wisp trailing from the other. His skin is black, his opera-style armour "
        "bright red, teal and gold, wrapped in crossed silver chains, over baggy red trousers. A thick red scarf "
        "bunches under his white monkey face, which wears green goggles, and a huge sunburst of golden spikes "
        "bursts up and back from his head. Golden streamers fly from his shoulders, and he carries a long red and "
        "black staff capped in gold. Cocky and planted wide, he rides the cloud like a born trickster."},
  {"Ps5002_030",  // Mercurius
        "A slim, long-legged messenger in a skin-tight royal-blue jumpsuit quilted like scales, zipped down the "
        "front to a gold circle-and-cross symbol at the chest. A blue hood frames a black face mask crowned with "
        "two flaming red wing shapes that sweep up like horns. Big ribbed gold discs guard his shoulders, and his "
        "gauntlets and boots are scaled gold. Two great wings of layered blue, silver and sky-blue feathers sweep "
        "down from his shoulders to his heels like a long coat. Beside him floats a tall gold staff twined in "
        "spirals and topped with small wings. Sleek and quick, he is a god of speed and cunning."},
  {"Ps5002_040",  // Hecate
        "A gaunt, theatrical witch queen with no legs: her body narrows to a slim black stem that flares into a "
        "pedestal on the floor, like a candlestick. A tall cape of bat-like wings, red veined with black, hangs "
        "from her shoulders to a scalloped hem tipped with silver claws. Her small red face is crowned by huge "
        "black antler-like horns, and in their curve glare two enormous cat's eyes of blue and orange with slit "
        "pupils. Silver spikes guard her chest, and from a ring in each hand a long chain runs to a small fanged "
        "blue demon head. Spooky and stylish, she presides like a goddess of witchcraft."},
  {"Ps5002_050",  // Kamu Susano-o
        "A brawny storm god with bright blue skin covered in dark red tribal tattoos, a wild mane of white spikes "
        "bursting up around a gold mask with red eyes and two tall gold horns. A long red-and-gold patterned "
        "scarf wraps his throat and streams far out across both shoulders like a banner in the wind. A collar of "
        "jagged gilded plates rings his waist above a flared, studded skirt of black armour, loose black trousers "
        "and gold-cuffed boots. A huge, blocky black broadsword is slung diagonally across his hips, and he holds "
        "a slender black blade of linked segments. Fierce and untamed, he looks like a tempest given fists."},
  {"Ps5002_060",  // Anat
        "A war goddess built from a motorcycle, standing tall beside a second, riderless machine just like her. "
        "Her body is polished silver-blue steel panels, chrome pistons and black machinery, a wheel set at her "
        "back and her legs ending in gold claws. Her face is a stern blood-red woman's head between two great "
        "curving golden horns, a deep blue crest sweeping back like hair. A grinning red skull sits on her chest "
        "over a gold collar, and gold blades bristle from her shoulders and hands. Beside her the motorcycle "
        "raises the same blue crest. Fierce and upright, she is a war goddess who is her own steed."},
  {"Ps5002_070",  // Astarte
        "A slender, voluptuous goddess with deep black skin rising waist-up from the crown of a gigantic floating "
        "skull, her arms angled down at her sides. She wears only gold: coiled gold cups over her full breasts, a "
        "choker and stacked bangles, her long black hair streaming behind her under a huge golden crescent moon. "
        "The skull is enormous and bubble-round, printed all over with cheerful pink, purple and orange flowers, "
        "with big round green and yellow eyes under blue lashes, ringed at the jaw by sweeping gold bands and "
        "tapering to a black arrow-tipped spike. Seductive and serene, she rides death like a carnival float."},
  {"Ps5002_080",  // Loki
        "A tall, slender trickster god dazzling from head to toe in black and white stripes that swirl in "
        "clashing chevrons over a lean, armoured body, so busy the eye cannot rest. His head is a smooth black "
        "mask with a thin red mouth, crowned with two curling striped horns, and from it pour long, thick black "
        "braids tipped in red that hang to his knees. Thin gold chains loop across his chest, and he stands on "
        "gold high-heeled points. Beside him hangs a long greatsword, its blade blazing red-orange like a tongue "
        "of fire, its hilt black and jagged. Dazzling and unsettling, he is mischief that hurts to look at."},
  {"Ps5002_090",  // Vanadis
        "A tall, slender warrior goddess in deep scarlet, a great ring of dark brown and black feathers spreading "
        "from her hips and sweeping down like folded wings around long red-stockinged legs that end in sharp "
        "black points. A black hood hangs like a veil to her shoulders, and from it rise two tall, curved scarlet "
        "horns like a helmet's crest, framing a dark face with small golden eyes above a white ruff. Her fitted "
        "red bodice is laced with gold scrollwork and black heart-like patterns over her breasts, and a collar of "
        "red scales flares at her waist. Poised and proud, she carries love and battle in one bearing."},
  {"Ps5003_010",  // Izanagi
        "A tall, lean warrior standing straight and still in a long black greatcoat with a stand-up collar, its "
        "skirts falling to his shins, lined with blood red and fastened down a grey front with a silver zip and "
        "rows of buckles. His face is a smooth silver mask with narrow yellow eyes above a pale cloth, under a "
        "white headband with two short horn-like points, its long white tails streaming behind. Gold crests sit "
        "on his shoulders, black gloves end his sleeves, and grey-armoured legs taper to spikes. He grips a long, "
        "straight black sword with a white-bound hilt. Stoic and steady, he looks made to seek the truth."},
  {"Ps5003_020",  // Magatsu-Izanagi
        "A tall, lean warrior in a long greatcoat of mottled blood red, cut like a noble twin's but stained "
        "through, its skirts falling to his shins over a black front fastened with rows of red buckles. His face "
        "is a dark red mask with narrow glowing yellow eyes, a red cloth dripping beneath it like blood, under a "
        "black band with two short horn-like points, its long black tails streaming behind. Black stripes run "
        "down his red sleeves to clawed red hands, and red-armoured legs taper to spikes. He grips a long, "
        "straight black sword edged in blood red. Sinister and hungry, he is a hero's mirror turned to chaos."},
  {"Ps5003_030",  // Kaguya
        "A slim, elegant moon princess standing upright between two vast, flat wings spread level from her "
        "shoulders like the panels of a folding screen: glossy black framed in red, drawn with neon swirls of "
        "pink, yellow, green and cyan around red and white target discs, edged in rainbow bands. She wears a "
        "tight orange-red leotard cut high at the hips and thigh-high red stockings banded in gold, like a bunny "
        "girl's costume. Her face is smooth and black, a green gem at her throat, under a gold headdress with two "
        "pale rabbit-ear plumes, magenta strands streaming behind. Cream ribbons curl around her, and she gazes "
        "out distant and composed."},
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
