// The area descriptions (included by area_text.cpp): one Entry per area, or per storey of a multi-storey area, then
// the lines every place shares.
// What each place holds comes from the game's own data: its named objects (DT_FldDailyHitName rows placed in the
// area's Hit level, with their heights per storey), its prop and variant sublevels (LV_F<major>_<minor>_BG_*), the
// light colours of Tartarus's block parts, and screenshots of the places (2026-11-02: the dorm, the school, the town
// by day and night, Adamah). Field ids: LV_F<major>_<minor>. Episode Aigis' copies (122 dorm, 123 mall, 401
// Tartarus) share these.
const Entry kEntries[] = {
// ---- Gekkoukan High School (F101) ----
{.major = 101, .minor = 101, .outdoor = true,
 .base = "School Entranceway. You come in through the front gate, between white marble gateposts and ornate "
         "wrought-iron gates, onto a broad, straight approach of paving stone that runs ahead to Gekkoukan High. "
         "Cherry trees and lamp posts line both sides above low hedged beds. At the far end, wide stone steps climb "
         "to the main entrance: a row of massive round pillars before a tall front of glass and dark steel, the "
         "entrance hall and its shoe lockers just visible through it. The whole approach is built to impress, wide, "
         "symmetrical and orderly, and students stream up and down the steps every morning and after class.",
 .day = "Sunlight glints off the great glass facade.",
 .evening = "Dusk washes the approach in deep blue; the lamps are lit, and the pillars stand dark against the "
            "glass.",
 .night = "The school stands dark and locked, its glass facade black.",
 .spring = "The cherry trees along the approach are in full bloom, and pink petals drift down over the steps.",
 .summer = "The trees are thick with green leaves, throwing patches of shade over the hot stone.",
 .autumn = "The trees have turned red and gold, and fallen leaves skitter across the steps.",
 .winter = "The trees are bare, and the stone approach looks grey and wind-swept under the cold sky."},
{.major = 101, .minor = 102, .floor = 1,
 .base = "School Building, first floor: the main lobby. A grand, high-ceilinged hall like an old bank, held up by "
         "massive fluted stone columns around a statue of a figure holding a sword and a staff, with a wide "
         "staircase rising under an arch at the back and tall latticed windows along one side. A counter sells "
         "school goods, and bulletin boards carry event notices and, at exam time, the posted results. Tiled "
         "corridors lead off past sliding doors to the faculty office, the nurse's office, the library, the "
         "laboratory, the science, art, music and home economics rooms with their prep rooms, the printing room, "
         "the janitor's room and the restrooms. One ends at heavy double doors under a green exit sign, beside a "
         "row of sinks where students loiter."},
{.major = 101, .minor = 102, .floor = 2,
 .base = "School Building, second floor: the classroom hallway. The stairs come up into a landing of pale stone "
         "tiles, with a pair of drinking fountains and a row of sinks. Across it a long stone bench runs under "
         "latticed windows, where students sit and chat. A long corridor of sliding classroom doors runs on past "
         "square pillars and bulletin boards crowded with flyers. Classroom 2-E is here, and your own classroom "
         "2-F, with the computer room, the PA room and the student council room further along, and restrooms by the "
         "stairs. Stairs lead down to the lobby and up toward the third floor and the roof."},
{.major = 101, .minor = 103, .outdoor = true,
 .base = "The gym hallway behind the school building, reached from the main building by an outdoor corridor of "
         "stone-brick arches, past small gardens and a locked gate. Indoors it is a long, plain passage of pale "
         "green walls and pale tiles, running straight to tall glass doors full of light, the gym's red double "
         "doors at their centre, taped with club posters. Lockers, stacked folding chairs, a whiteboard of club "
         "notices and racks of gear line the walls. The gym, the indoor swimming pool and the practice field are "
         "all reached from here.",
 .evening = "Pale evening light pours through the glass doors at the end of the hall, and shouts and whistles drift "
            "in from the practice field.",
 .spring = "", .autumn = "Fallen leaves gather in the corners of the arcade."},
{.major = 101, .minor = 121,
 .base = "Classroom 2-F, your homeroom. You come in through sliding doors at the back, beside a tall locker and "
         "cubby shelves for bags. Rows of white desks and dark red chairs face the blackboard and the teacher's "
         "lectern. A wall of tall windows hung with yellow curtains looks out over the trees of the school grounds. "
         "After class, students linger in knots between the desks.",
 .day = "Sunlight pours through the windows across the desks.",
 .evening = "The room is emptying, and orange evening light floods in through the windows, laying the window frames' "
            "shadows across the desks.",
 .night = "The room is dark and empty, the desks in silent rows.",
 .spring = "Outside the windows the cherry trees are in bloom.",
 .summer = "Outside the windows the trees are deep summer green.",
 .autumn = "Outside the windows the trees have turned red and gold.",
 .winter = "Outside the windows the trees stand bare."},
{.major = 101, .minor = 141, .outdoor = true,
 .base = "The school rooftop. You step out through the stairwell housing's glass double doors onto a broad deck of "
         "pale concrete tiles ringed by a metal railing. A steel ladder climbs the housing to a water tank and "
         "antennas, and there is a small storage room. Curved stone benches and brick flower planters stand along "
         "the edges, beside a railed-off strip of solar panels and a tall wind turbine turning. Beyond the railing "
         "lie the sea and the rooftops of Port Island. Students come here to eat lunch or talk away from the "
         "crowds.",
 .day = "The wind is fresh up here, and the sky is wide and open.",
 .evening = "The sun sets over the sea under pink and violet clouds, and the whole roof turns gold.",
 .night = "The city lights glitter below, and the sky above is dark and wide.",
 .spring = "A mild spring breeze carries the scent of the flower planters.",
 .summer = "The summer sun beats down on the concrete, and heat shimmers over the rooftops below.",
 .autumn = "A cool autumn wind blows across the roof, and the sky looks high and clear.",
 .winter = "A cold winter wind cuts across the roof, and the sea below looks grey."},
// ---- Iwatodai Dorm (F102) ----
{.major = 102, .minor = 101, .outdoor = true, .town = true,
 .base = "Dorm Entrance: a quiet street in Iwatodai. The dormitory is a handsome old building of dark red brick, "
         "its tall windows patterned in art deco ironwork. A short, wide flight of stone steps rises between stone "
         "posts to double front doors of dark wood with tall arched windows, lit by a single round lamp. A low iron "
         "fence over a hedge runs along the front. Plain concrete office buildings stand on either side, a car and "
         "a covered motorbike parked beneath one. Among the modern blocks the old dorm looks grand and out of its "
         "time.",
 .day = "The street is calm and sunlit.",
 .evening = "The streetlights flicker on as the sunset fades behind the dorm.",
 .night = "The dorm's tall windows glow warm yellow against the dark, quiet street.",
 .spring = "Fresh green leaves fill the trees along the street.",
 .summer = "The trees are in deep summer green, and the air is heavy and hot.",
 .autumn = "The roadside trees have turned, and fallen leaves gather along the curb and the steps.",
 .winter = "The trees are bare, and dry leaves collect in drifts by the steps and along the curb."},
{.major = 102, .minor = 102, .floor = 1,
 .base = "The dorm lounge, on the first floor. The dorm feels like an old Western hotel turned home. Just inside "
         "the front doors, on your left, is a curved wooden reception counter with the dorm register you sign to "
         "save, a pen and a little bell. Ahead the room opens out over a green and cream checked carpet. To the "
         "right, red velvet sofas and armchairs with carved wooden frames gather around a low table on a patterned "
         "rug, with an old-fashioned TV in a wooden cabinet beside them. Straight ahead, behind glass partitions on "
         "brass posts, is the dining room under a chandelier, with the kitchen and its fridge beyond. On the left a "
         "red carpet runner leads past wooden doors, a bulletin board and brass wall lamps to a red-carpeted "
         "staircase with a wooden banister climbing to the rooms. Bookshelves, a computer desk and a post box stand "
         "about, and a storeroom and the rear entrance are off to the side. Your dormmates often relax here in the "
         "evenings.",
 .dark = "It is the Dark Hour. The lamps are dead and the lounge is washed in a sickly green glow; the clock has "
         "stopped, and the room feels hollow and still.",
 .christmas = "A tall Christmas tree stands in the lounge, hung with ornaments and twinkling lights."},
{.major = 102, .minor = 102, .floor = 2,
 .base = "The dorm's second floor, the boys' floor. The stairs come up beside a turned wooden banister onto a red "
         "carpet runner. A sitting area opens here: low red upholstered benches around a wooden table, a "
         "glass-fronted bookcase, potted plants, a floor lamp and tall windows with roll-down blinds. A vending "
         "machine stands in the corner. Along the hallway, lit by brass wall lamps, are your room, Sanada's room "
         "and vacant rooms waiting for new residents. Stairs lead down to the lounge and up to the third floor. It "
         "feels more like an old hotel than a student dorm.",
 .dark = "It is the Dark Hour. The hallway is dead quiet under the green light, and the vending machine's glow has gone out."},
{.major = 102, .minor = 102, .floor = 3,
 .base = "The dorm's third floor, the girls' floor. The stairs arrive by a turned wooden banister onto a red carpet "
         "runner, in a stairwell open from floor to floor: over the rail you can see the flights winding down past "
         "the landings below. The open area here is a dining nook: two wooden tables with spindle-backed chairs, a "
         "pair of drink vending machines, a floor lamp and tall windows with roll-down blinds. Mitsuru's and "
         "Yukari's rooms and vacant rooms line the hallway. Stairs lead down to the second floor and up to the "
         "fourth.",
 .dark = "It is the Dark Hour. The hallway is silent and bathed in green light."},
{.major = 102, .minor = 102, .floor = 4,
 .base = "The dorm's fourth floor. The stairs climb to a quiet landing: a long red bench under a window and a "
         "potted plant. The hallway leads to a large, heavy door: the command room, where SEES meets. There are "
         "restrooms here, and stairs lead down to the rooms and up to the rooftop landing. The floor feels hushed "
         "and set apart.",
 .dark = "It is the Dark Hour. The hallway is bathed in green light; behind the large door, the command room is "
         "where the team gathers on nights like this."},
{.major = 102, .minor = 102, .floor = 5,
 .base = "The rooftop landing atop the dorm stairs: a cramped stairwell used for storage, its walls bare plaster. "
         "Taped cardboard boxes are stacked along one wall, stools sit upside down on an old table, and spare floor "
         "lamps lean in the corner. The door out to the roof is under a green emergency exit sign, a notice taped "
         "to it."},
{.major = 102, .minor = 121,
 .base = "Your Room, on the dorm's second floor. A small single room with wooden floorboards and cream striped "
         "wallpaper. Just inside the door are a small fridge and a sink with a mirror and shelves of towels, and "
         "beside them a wide built-in closet. Next to it two bare wall shelves hold a single moving box still not "
         "unpacked, and a calendar hangs on the wall. A rug covers the middle of the floor. Further in are your bed "
         "by the window, a desk with a computer and a TV. A shelf holds the things you have collected. It is plain "
         "and barely lived in yet, but it is yours.",
 .day = "Daylight comes in through the window over the bed.",
 .evening = "The setting sun throws orange light across the room through the window.",
 .night = "Outside the window it is night; the room is lit by its lamp.",
 .dark = "It is the Dark Hour. The lamp is dead, and the window spills a sickly green light across the bed and the "
         "floor under a huge, pale moon. Everything is utterly silent."},
{.major = 102, .minor = 125,
 .base = "Aragaki's Room. Shinjiro's room on the dorm's second floor: an iron-framed bed, a desk and swivel chair "
         "with an open cardboard box, empty wall shelves and a coat rack. Sparse and quiet, it is kept the way he "
         "left it."},
{.major = 102, .minor = 141,
 .base = "The command room on the dorm's fourth floor, the meeting room of SEES. You enter through tall double "
         "doors of dark wood. Green-striped wallpaper runs above wood panelling, and fluted grey columns rise "
         "between tall arched windows with iron grilles. One wall is taken up by a big console deck: a wide screen "
         "of glowing graphs and waveforms flanked by huge loudspeakers, with a desk of smaller monitors and a chair "
         "before it. Across the room a red sofa heaped with cushions, an armchair and stools sit around a long "
         "wooden table, beside tall bookshelves, a display shelf and a storage room.",
 .dark = "It is the Dark Hour. The whole room is drowned in green; the arched windows blaze with sickly yellow-green "
         "moonlight and throw the pattern of their iron grilles across the floor."},
{.major = 102, .minor = 151, .outdoor = true,
 .base = "The dorm rooftop. You come out through a plain steel door in the brick stairwell housing. Ahead lies a "
         "wide, flat roof of dark slate tiles behind a low concrete parapet. Pipes and machinery units sit on one "
         "side; on the other, by a second door, is a rooftop garden of planter boxes with gardening tools and a "
         "small storage shed. Taller apartment blocks crowd in close, and between them you can see across the "
         "rooftops of Iwatodai.",
 .day = "The garden beds bask in the open sun.",
 .evening = "The sunset paints the sky and the garden in orange.",
 .night = "The neighbourhood's lights spread out below a wide night sky.",
 .dark = "It is the Dark Hour. The sky is a sickly green, and an enormous yellow moon hangs low and close over the "
         "silent town; not a single light burns anywhere below.",
 .spring = "Mild spring air; the beds are ready for planting.",
 .summer = "The summer air is warm even up here.",
 .autumn = "A cool autumn wind blows across the roof.",
 .winter = "The winter wind is cold and sharp up here."},
// ---- Paulownia Mall (F103) ----
{.major = 103, .minor = 101, .outdoor = true, .town = true,
 .base = "Paulownia Mall, Fountain Square: a round plaza under a high glass dome, ringed by a two-storey wall of "
         "European-style shopfronts. Just inside the entrance you pass a wide, shallow pool with wrought-iron "
         "benches beside it. Ahead the paving spreads in wide rings around a tiered fountain at the centre, ringed "
         "by benches and potted trees. Behind the fountain, under a great brick archway, stairs climb to the "
         "karaoke bar Mandragora and its neon sign. Around the ring are Chagall Cafe, the accessory shop Be Blue V, "
         "Mayoido Antiques, Aohige Pharmacy, the CD and DVD shop Kenneth Arnold, the police station, and the arcade "
         "Game Parade with crane games outside, besides a bulletin board and the neon-lit entrance of Club "
         "Escapade. Tucked away in a corner is a strange blue door that only you seem to notice: the way into the "
         "Velvet Room. Shoppers mill about under the dome.",
 .day = "Daylight falls through the glass dome, the plaza bustles with shoppers, and the fountain sparkles.",
 .evening = "Shop signs light up as the dome turns orange overhead, and students crowd the plaza after school.",
 .night = "The dome shows a starry night sky. The fountain glows blue, neon signs blaze over Escapade, Mandragora and "
          "Game Parade, and Be Blue V and the antique shop have pulled down their shutters; the crowd is older now.",
 .dark = "It is the Dark Hour. The neon is dead, the fountain hangs silent, and coffins stand where shoppers were; "
         "dark puddles like blood stain the paving under the green dome.",
 .spring = "", .summer = "The summer heat hangs over the plaza, and people linger near the cool spray of the fountain.",
 .autumn = "", .winter = "Shoppers hurry through the plaza bundled in winter coats.",
 .christmas = "For Christmas the plaza is decorated with Christmas trees strung with glowing lights, and a large "
              "illuminated tree stands at its heart."},
{.major = 103, .minor = 111,
 .base = "Club Escapade, a nightclub in Paulownia Mall. A dark room pulsing with music, its walls a deep electric "
         "blue. At its heart a dance floor is ringed by a band of glowing blue light panels, where a few people "
         "dance, and laser beams sweep overhead. At one end is a black stage with a drum kit, microphone stands and "
         "towering speaker stacks; around the floor are lounge tables lit by small blue lamps, tall bar stools, and "
         "a bar where bottles glitter.",
 .day = "", .evening = "", .night = "",
 .dark = "It is the Dark Hour. The music has stopped dead; the coloured lights are frozen and dark, and the room is "
         "filled with silent coffins."},
// ---- Port Island Station (F104) ----
{.major = 104, .minor = 101, .outdoor = true, .town = true,
 .base = "Port Island Station: a wide plaza of grey flagstones crossed by bands of blue tile, dotted with tall "
         "columns and lampposts. Raised brick flowerbeds have red wooden benches set into them. Broad stone steps, "
         "with an escalator beside them, climb a brick terrace to the station entrance, with the ticket booth and "
         "the restrooms up top; a little flower shop sits in an arch under the steps. The cinema Screen Shot faces "
         "the plaza under big movie posters, beside a cafe's terrace under green umbrellas and a vending machine, "
         "and a department store, Tatsumi Mall, hangs its sale banners on one side.",
 .day = "Commuters and students stream across the bright plaza.",
 .evening = "The evening sun slants across the plaza, the columns throw long shadows, and the cinema's sign lights up.",
 .night = "The plaza is lit by the lampposts, the cinema's glow and the station lights; late commuters hurry past.",
 .spring = "The flowerbeds are in bloom.", .summer = "The flowerbeds are lush under the summer sun.",
 .autumn = "", .winter = "The flowerbeds are bare and the plaza is cold."},
{.major = 104, .minor = 102, .outdoor = true, .town = true,
 .base = "Station Outskirts: the back alley behind Port Island Station. A grimy yard of cracked paving hemmed in by "
         "brick walls studded with air conditioner units and scrawled with graffiti. A chain-link fence topped with "
         "barbed wire closes off one side, and a narrow passage runs past a lone drink vending machine. Garbage "
         "bags spill around a dumpster by a stairway. The Mahjong Parlor Red Hawk and the bar Que Sera Sera have "
         "their doors here. It is a hangout for delinquents, and most students know to stay away. A "
         "familiar-looking black cat sometimes prowls about.",
 .day = "Even in daylight the alley feels shadowed and stale.",
 .evening = "The alley falls into shadow early as the sun sets.",
 .night = "The alley is dark, lit only by a few buzzing lights and the signs over the bar and the mahjong parlor.",
 .spring = "", .summer = "The summer heat makes the alley stink of garbage.", .autumn = "", .winter = ""},
// ---- Iwatodai Station and Strip Mall (F105) ----
{.major = 105, .minor = 101, .outdoor = true, .town = true,
 .base = "Iwatodai Station, the station closest to the dorm. From the street you cross a tiled forecourt to a broad "
         "flight of low stone steps, where people sit and chat. At the top is a concrete concourse under "
         "fluorescent lights: posters and a station map on the walls, recycling bins and a long bench. Overhead a "
         "departure board lists the trains, and a wide staircase flanked by escalators climbs to the platforms. "
         "There is also an elevator, a telephone box with two booths, a vending machine, bicycle racks out front, "
         "and a construction site fenced off behind white hoardings. The strip mall is right next door.",
 .day = "Commuters come and go from the escalators in the daylight.",
 .evening = "The station grows busy with people coming home as the sky turns orange.",
 .night = "The station's fluorescent lights shine bright against the night; only a few travellers are about.",
 .dark = "It is the Dark Hour. The escalators have stopped, the lights are dead, and coffins stand on the concourse "
         "under a green sky.",
 .spring = "", .summer = "", .autumn = "", .winter = "It is winter, and the air at the station is cold."},
{.major = 105, .minor = 102, .floor = 1, .outdoor = true, .town = true,
 .base = "Iwatodai Strip Mall, ground floor. A three-storey brick building whose shops open onto stacked walkways, "
         "joined by stairs and an iron spiral staircase. At ground level the takoyaki stand Octopia serves from a "
         "little window under a yellow sign, with benches out front. Nearby, Wilduck Burger shines under its big "
         "orange sign, beside the used bookstore Bookworms. Bicycles are parked along the front.",
 .night = "The burger shop's sign and the shop lights glow warmly in the dark.",
 .spring = "", .summer = "", .autumn = "", .winter = ""},
{.major = 105, .minor = 102, .floor = 2, .outdoor = true, .town = true,
 .base = "Iwatodai Strip Mall, second floor. An open walkway behind a metal railing, beside the iron spiral "
         "staircase. The Chinese diner Wakatsu Kitchen hangs a green cloth curtain over its door, with a display "
         "case of plastic food samples beside it. Hagakure Ramen hangs deep blue curtains over a sliding glass "
         "door, and people queue outside. The sweets shop Azuki Arai has its mascot Azuki-chan, a beaming red-faced "
         "statue, standing at the door.",
 .night = "The restaurants' lit signs and warm windows glow along the walkway.",
 .spring = "", .summer = "", .autumn = "", .winter = ""},
{.major = 105, .minor = 102, .floor = 3, .outdoor = true, .town = true,
 .base = "Iwatodai Strip Mall, third floor. The top walkway, reached by the iron spiral staircase. The MangaStar "
         "net cafe has a purple sign scattered with stars, glass doors taped with posters for new games, and "
         "windows plastered with a cartoon mascot girl. Umiushi Beef Bowls is up here too, under a long orange-red "
         "sign, with an \"open 24 hours\" sign and people waiting outside. A drink vending machine stands nearby. "
         "Over the railing you can look down on the floor below.",
 .night = "The net café's sign glows; it stays open late.",
 .spring = "", .summer = "", .autumn = "", .winter = ""},
// ---- Naganaki Shrine (F106) ----
{.major = 106, .minor = 101, .outdoor = true, .town = true,
 .base = "Naganaki Shrine: a small Shinto shrine among old trees in Iwatodai. From the entrance steps a worn, mossy "
         "stone path leads straight to the wooden main hall, where a thick braided straw rope with white paper "
         "streamers hangs over the entrance above the offertory box. Stone guardian lion-dogs crouch on either side "
         "of the steps. To the left a tunnel of small red torii gates leads to the Inari fox statues; a roofed "
         "stone basin is there for cleansing your hands, a huge sacred tree spreads its branches overhead, and "
         "fortune slips are tied in white rows on a rack. Beside the grounds is a small playground: a slide, a "
         "jungle gym, a see-saw, a horizontal bar and a sandbox. Old and quiet, it feels sheltered from the town.",
 .day = "It is peaceful here; birdsong and the rustle of leaves replace the noise of the town.",
 .evening = "The low sun filters through the trees in long beams, and the playground stands empty and quiet.",
 .night = "The shrine is dark and hushed, the trees black against the sky.",
 .spring = "The trees around the grounds are fresh with new green.",
 .summer = "The trees are dense and green, and the shade is welcome in the heat.",
 .autumn = "The trees have turned red and gold, and fallen leaves cover the paving and the playground.",
 .winter = "The trees are bare, and the shrine grounds look stark and cold."},
// ---- Yakushima (F107) ----
{.major = 107, .minor = 101, .outdoor = true,
 .base = "The Kirijo family's private beach on Yakushima. A path comes down out of the trees onto soft white sand "
         "that slopes gently into clear, shallow turquoise water, a steep green bank of palms behind. Parasols "
         "shade yellow loungers, and big grey boulders sit half in the water. A boat is tied up at a wooden pier, "
         "and a rocky headland closes off the end of the beach. Behind it, the Kirijo Yakushima Mansion stands at "
         "the edge of an ancient cedar forest.",
 .day = "The summer sun blazes on the sand, and the sea glitters.",
 .evening = "The sun sinks into the sea, turning the water and the sand orange.",
 .night = "The beach is dark; waves wash softly on the sand under the stars.",
 .spring = "", .summer = "", .autumn = "", .winter = ""},
// ---- Kyoto, the school trip (F108) ----
{.major = 108, .minor = 101, .floor = 1,
 .base = "Godaigo Inn, a traditional Japanese inn in Kyoto, on its ground floor. The lobby is carpeted in dusty "
         "rose under a wooden ceiling, its curved walls cream. Along one side runs the long wooden front desk, with "
         "a wall of key boxes, a framed piece of calligraphy and a beckoning cat statue behind it. Guests in cotton "
         "robes sit on red-draped benches at low tables among paper lanterns, beside a display shelf of tea things "
         "and a gold folding screen. A carpeted staircase climbs at the back between two lanterns. Paper-paned "
         "windows look onto a lit inner garden with a stone lantern, and there is a pamphlet rack and a souvenir "
         "corner piled with Kyoto sweets, crafts and wooden swords. A passage leads to the hot spring."},
{.major = 108, .minor = 101, .floor = 2,
 .base = "Godaigo Inn, second floor. The stairs arrive at a quiet corridor running past guest rooms behind sliding "
         "doors, among them the Fuji Room, with a vending machine, a telephone and the emergency exit."},
{.major = 108, .minor = 101, .floor = 3,
 .base = "Godaigo Inn, third floor. Another corridor of guest rooms behind carved wooden doors, with a vending "
         "machine, a telephone, a travel guide and the emergency exit."},
{.major = 108, .minor = 102, .name = "Hot Spring", .outdoor = true,
 .base = "The inn's open-air hot spring. You come out of the dressing room through frosted sliding doors under a "
         "wooden porch hung with lanterns. Along both walls runs a row of washing taps with mirrors, stools and "
         "buckets. A wide pool of steaming water is edged with smooth boulders, screened in by a bamboo fence and "
         "maple trees; the air is warm and damp.",
 .night = "Steam rises into a sky full of stars, and small lamps glow along the bathhouse wall.",
 .spring = "", .summer = "", .autumn = "The maples around the pool are red.", .winter = ""},
{.major = 108, .minor = 104, .base = "The Nanten Room, a guest room at Godaigo Inn named for the nandina shrub. "
                                     "Tatami mats, the far wall a row of paper-paned sliding doors. Futons are laid "
                                     "out for the night. A low red-lacquered table holds a tea set, with floor "
                                     "cushions around it. A raised alcove holds a paper lantern under a hanging "
                                     "scroll, travel bags beside it. There are painted sliding closet doors, a "
                                     "small old TV, a round window and a latticed window."},
{.major = 108, .minor = 105, .base = "The Botan Room, a guest room at Godaigo Inn named for the peony. Green tatami "
                                     "under a square paper lamp. Ahead is a wall of paper-paned sliding doors, and "
                                     "a latticed window over cupboard doors. Futons are laid out along one side. A "
                                     "low red-lacquered table holds a tea set, with floor cushions. A porcelain jar "
                                     "stands in the alcove under a scroll. There are painted closet doors, a small "
                                     "old TV and a round window."},
{.major = 108, .minor = 106, .base = "The Tsubaki Room, a guest room at Godaigo Inn named for the camellia. Pale "
                                     "tatami, futons laid out for the night, a square paper lamp overhead. Painted "
                                     "closet doors fill the back wall; to the left are a paper-paned sliding door, "
                                     "a round window and a small old TV. To the right stand a low red-lacquered "
                                     "table with a tea set and floor cushions, and a hanging scroll in the alcove. "
                                     "It feels settled into."},
{.major = 108, .minor = 107, .base = "The Shoubu Room, a guest room at Godaigo Inn named for the iris. Pale tatami, "
                                     "futons laid out, a square paper lamp overhead. Painted closet doors fill the "
                                     "back wall; to the left are a paper-paned sliding door, a bamboo-barred round "
                                     "window, and a small old TV. To the right stand a low red-lacquered table with "
                                     "a tea set and floor cushions, and an ink painting of a pine. Hushed and tidy, "
                                     "it waits for guests."},
{.major = 108, .minor = 108, .base = "The Kikyo Room, a guest room at Godaigo Inn named for the bellflower. A "
                                     "square paper lamp hangs over pale tatami, futons down the left, paper-paned "
                                     "sliding doors across the far wall. To the right, a low red-lacquered table "
                                     "holds a tea set, with floor cushions and a paper lantern in the corner; "
                                     "painted closet doors, a small old TV and a round window complete it. Snug, it "
                                     "is ready for a late night of talk."},
{.major = 108, .minor = 109, .base = "The Ajisai Room, a guest room at Godaigo Inn named for the hydrangea. A "
                                     "square paper lamp hangs over pale tatami, futons in a neat row down the left, "
                                     "paper-paned sliding doors across the far wall. To the right, a low "
                                     "red-lacquered table holds a tea set, with floor cushions and a telephone on a "
                                     "shelf; painted closet doors, a small old TV and a round window complete it. "
                                     "Bright and roomy, set for several guests."},
{.major = 108, .minor = 110, .base = "The Suisen Room, a guest room at Godaigo Inn named for the daffodil. A square "
                                     "paper lamp hangs over pale tatami, futons along the left, paper-paned sliding "
                                     "doors across the far wall. On the right, a long, low red-lacquered table "
                                     "holds a tea set, with floor cushions and travel bags by a telephone; painted "
                                     "closet doors, a small old TV and a round window complete it. It has the calm "
                                     "of a day that is over."},
{.major = 108, .minor = 111, .base = "The Sazanka Room, a guest room at Godaigo Inn named for the sasanqua "
                                     "camellia, dimmer than its neighbours: pale tatami, futons laid out, a square "
                                     "paper lamp overhead. To the left are a paper-paned sliding door and a round "
                                     "window. Ahead are painted closet doors; to the right, a recess holds a small "
                                     "old TV, a telephone and a safe, beside a low table with a tea set and floor "
                                     "cushions. It feels tucked away."},
{.major = 108, .minor = 112, .base = "The Suzuran Room, a guest room at Godaigo Inn named for the lily of the "
                                     "valley: pale tatami, futons laid out, a square paper lamp overhead. To the "
                                     "left are a paper-paned sliding door and a round window. Ahead are painted "
                                     "closet doors; to the right, under a painting of autumn trees, a recess holds "
                                     "a small old TV and a telephone, beside a low table with a tea set and floor "
                                     "cushions. It looks lived in."},
// ---- The full-moon operations and the first night (Dark Hour only) ----
{.major = 302, .minor = 102, .name = "Inside Monorail",
 .base = "Inside the monorail, stalled on its elevated track in the Dark Hour. A narrow, cramped car drowned in "
         "murky green light, as if under deep water. Bench seats run along both walls beneath hand straps hanging "
         "dead still, and advertisements dangle from the ceiling. Ahead, a connecting door with a small window "
         "leads car after car toward the front of the train. Upright coffins stand where the passengers were. "
         "Through the windows lie the sea and the silent city under a huge moon. It is close, airless and utterly "
         "still.", .dark_only = true},
{.major = 302, .minor = 101, .name = "Overhead Bridge",
 .base = "The Overhead Bridge: the monorail's elevated concrete track, above the city in the Dark Hour. The "
         "guideway sweeps away in a long curve between low railed walls, red splashes dripping down the concrete "
         "like blood. Far ahead around the bend, the stalled train waits, and above the rooftops an enormous green "
         "moon hangs low. Exposed and silent, it is very far from the ground.", .dark_only = true},
{.major = 304, .minor = 101, .name = "Hotel Hallway",
 .base = "Champs de Fleurs, a love hotel on Shirakawa Boulevard, transformed by the Dark Hour. The hallways are "
         "carpeted in a dull check, the walls papered with faded flowers, lined with potted palms and floor lamps. "
         "On the ground floor are the entrance, a reception window, an information panel of room photos, curtained "
         "waiting booths, vending machines and elevators; at the end of the hall narrow stairs climb into darkness. "
         "Above, corridors of numbered doors run across three floors, with a strange vending machine on each "
         "landing. Coffins stand where guests were caught. Everything is sunk in a sickly green, cheap glamour gone "
         "stale.", .dark_only = true},
{.major = 304, .minor = 104, .name = "Hierophant's Chamber",
 .base = "A love hotel suite where the Shadow lies in wait, drenched in magenta and red light: red velvet curtains, "
         "mirrors covering the walls, a low sofa and a bed. Lurid and overheated.", .dark_only = true},
{.major = 304, .minor = -1, .name = "Hotel Room",
 .base = "A love hotel room on Shirakawa Boulevard, built around a big round red bed on a low platform in the "
         "middle. Behind it hangs a large mirror framed in hearts. A sofa and a glass coffee table sit to one side, "
         "and there are a heart-shaped chair, a glass-walled bathroom, a TV, a floor lamp and a small fridge. The "
         "Dark Hour washes it a sickly green, its romance gone hollow.",
 .dark_only = true},
{.major = 305, .minor = 101, .name = "Underground",
 .base = "An abandoned military base deep underground, entered through heavy riveted steel doors streaked with "
         "rust. Cracked concrete floors are strewn with rubble, and timber posts and beams shore up the walls "
         "against heaps of rock. Passages descend level by level, with signs marking 13 and then 17 meters "
         "underground. Rusting military equipment, cannon and artillery parts lie about, and side rooms hold beds, "
         "boxes, canned food, desks with diaries left behind, and a messy work area. Dim and stale, it has the "
         "weight of earth pressing close overhead.", .dark_only = true},
{.major = 308, .minor = 101, .name = "Moonlight Bridge",
 .base = "The Moonlight Bridge, the suspension bridge linking Port Island to the mainland, in the Dark Hour. A "
         "broad roadway runs ahead between hanging cables to a great arched tower, an enormous moon hanging right "
         "over the road. A trailer and a few cars sit abandoned, coffins stand where people were, and pools like "
         "blood smear the asphalt. Vast and dead still, it is a road out with no one on it.", .dark_only = true},
{.major = 150, .minor = 211,
 .base = "A vast floor of blue marble high in a tower, a round dais at its heart, walled in by great gears and "
         "glowing green windows, like the inside of a giant clock.", .dark_only = true},
{.major = 150, .minor = 109, .name = "Dark Hour Cityscape",
 .base = "The city in the Dark Hour, swallowed by a thick, featureless green haze: no street or building can be made "
         "out through it, and not a sound carries.", .dark_only = true},
{.name = "Iwatodai Station",
 .base = "Iwatodai Station in the Dark Hour, its lights dead. Out front a tiled plaza lies under a green haze: "
         "bicycles against a railing, two phone booths by the taxi stand, and steps climbing to the station and its "
         "frozen escalators. Red splashes stain the paving, and coffins stand where people were.", .dark_only = true},
{.name = "School Dorm",
 .base = "The dormitory in the Dark Hour, its windows dark. Stone steps climb to its front doors behind an iron "
         "fence, blood-red splashes on the pavement, in a sour green light.", .dark_only = true},
// ---- Tartarus (its blocks' special floors are fields 202-207) ----
{.major = 201, .minor = 101, .name = "Tartarus: Gates",
 .base = "Tartarus: Gates. This is Gekkoukan High's front approach, but in the Dark Hour the school has twisted and "
         "risen into Tartarus: a colossal tower of contorted, mismatched shapes stacked impossibly high, spiralling up "
         "into the green sky toward the enormous moon. The trees along the old approach still stand at its foot.",
 .spring = "Strangely, the cherry trees by the gate are still in bloom.",
 .autumn = "The trees by the gate still wear their autumn colours, eerie in the green light.", .dark_only = true},
{.major = 201, .minor = 102, .name = "Tartarus: Entrance",
 .base = "Tartarus: Entrance. A palatial hall. A bright blue carpet runs straight ahead from where you enter, down "
         "the middle of a polished marble floor circled by broad rings of gold, between tall white columns; the "
         "walls behind glow green. Ahead, a steep blue staircase climbs to a gigantic gilded clock face, its gears "
         "turning in green light: the way up into the tower. To the left stands a grandfather clock, the blue door "
         "of the Velvet Room nearby; at the foot of the stairs on the right Mitsuru's motorcycle is parked, and "
         "beyond it a small arch of coiled metal around a screen that carries you to floors you have reached. Grand "
         "and cold, it feels like the lobby of a palace built for no one.", .dark_only = true},
{.name = "Monad Passage",
 .base = "The Monad Passage, a hidden way beneath Tartarus's entrance hall: dark corridors that feel even heavier "
         "and more hostile than the tower above.", .dark_only = true},
{.name = "Monad Chambers",
 .base = "The Monad Chambers, a hidden area beyond a secret gate in the Abyss of Time, floating high above the floor you came from. It is built like the labyrinth below, but harsher: the same halls are lit by glowing red lamps and thin red strips of light, in a hot, dusty haze, and the strongest Shadows wait here. The exit stands near where you arrive.", .dark_only = true},
{.name = "Monad",
 .base = "Monad, a hidden area beyond a Monad door, floating high above the floor you came from. It is built like the block below, but drenched in harsh red and orange light, with dark puddles like blood smeared across the floors and red glowing arches in a pale haze. The exit door stands near where you arrive.", .dark_only = true},
{.major = 202, .minor = -1, .name = "Thebel",
 .base = "Tartarus, Thebel block, the first block of the tower: a maze that reshapes itself every night. Corridors "
         "of dark blue stone blocks stepping back in tiers like a ziggurat run over black and white checkered "
         "floors edged with glowing green. Where you arrive, a ring of green lights glows around a dark star-shaped "
         "seal. On special floors a stained-glass window burns at a long corridor's end. Cold and bare, it is a "
         "tomb laid out as a puzzle.", .dark_only = true},
{.major = 203, .minor = -1, .name = "Arqa",
 .base = "Tartarus, Arqa block, the second block: a maze that feels alive. Its walls are twisting, ribbed forms "
         "like coiled arms, knotted together overhead and glowing magenta and violet. The floor is dark and rippled "
         "like wet sand, with gnarled black spires rising from it. It feels like the inside of something breathing.", .dark_only = true},
{.major = 204, .minor = -1, .name = "Yabbashah",
 .base = "Tartarus, Yabbashah block, the third block: an industrial maze of steel girders. Broad halls run between "
         "steel pillars ringed with yellow light, over dark metal floors lined like a circuit board, to a girder "
         "arch crowned with a stained-glass window. Cold and mechanical, it feels like the engine room of the "
         "tower.", .dark_only = true},
{.major = 205, .minor = -1, .name = "Tziah",
 .base = "Tartarus, Tziah block, the fourth block: a dark gothic palace. A wide red carpet runs down a long hall "
         "between spiked iron railings and massive carved columns, toward a tall stained-glass window glowing "
         "green, a violet flame burning before it. Solemn and oppressive, it is like a cathedral to something that "
         "should not be worshipped.",
 .dark_only = true},
{.major = 206, .minor = -1, .name = "Harabah",
 .base = "Tartarus, Harabah block, the fifth block: a psychedelic maze like a nightclub gone mad. The floors are "
         "glowing checkerboards of magenta, cyan, red and blue, spiralling in to a dark hole so the ground seems to "
         "swirl away underfoot. The walls are forests of dark pillars topped with neon blocks, and tall cones of "
         "yellow light rise from glowing pools. Dizzying, it seems built to make you lose your footing.", .dark_only = true},
{.major = 207, .minor = 104,
 .base = "A floor of Tartarus built like its first block, drowned in green. Where you arrive, a circle of green "
         "lights rings a star-shaped seal. Ahead, a corridor of dark stone climbs a few steps to a stained-glass "
         "window, side passages opening to either hand. Still and hushed, it feels like a gathering place before a "
         "climb.", .dark_only = true},
{.major = 207, .minor = -1, .name = "Adamah",
 .base = "Tartarus, Adamah block, the sixth and last block, near the tower's top. The floors are dizzying black and "
         "white stripes sweeping in curves along winding paths over a glossy black ground. Ahead, a smooth white "
         "dome rises with three white spheres floating above it. All around tower pale monoliths carved with "
         "zigzags, like a city of white towers, under a dark green sky. Hypnotic, it feels less built than dreamed.", .dark_only = true},
{.name = "Tartarus",
 .base = "Tartarus, the tower of the Dark Hour. A maze of corridors that reshapes itself every night: dark blue "
         "stone walls over checkered floors edged with green, where Shadows roam.", .dark_only = true},
{.major = 201, .minor = 103,
 .base = "A room in velvet blue. One wall is tufted blue upholstery, the far wall wrought-iron grillwork. A row of "
         "panelled doors, one with a window glowing yellow; a sofa and a round table. Hushed, like a waiting room.", .dark_only = true},
{.major = 401, .minor = 103,
 .base = "A room all in deep velvet blue: walls of ornate patterned panels, a tufted blue wall, a tufted blue sofa "
         "and a round table draped in blue cloth, in a dim blue light.", .dark_only = true},
// ---- Episode Aigis: the Abyss of Time ----
{.major = 401, .minor = 102, .name = "Desert of Doors",
 .base = "The Desert of Doors, at the bottom of the Abyss of Time. An endless expanse of pale golden sand, rippled in "
         "wide rings, under a hazy white sky. Tall cream-coloured doors trimmed with gold ornament stand alone in the "
         "sand around you, each one leading into a labyrinth born of someone's past, with the blue door of the Velvet "
         "Room among them and a glowing point of light that carries you onward. Time does not move here.",
 .dark_only = true},
{.major = 402, .minor = -1,
 .base = "The landing at the gate of a labyrinth in the Abyss of Time: a raised platform of polished black and gold "
         "tiles inlaid with swirling gold patterns, floating in a bright golden haze over the sand. At its head stands "
         "a tall arched double door of gold, richly carved, between two burning torches on iron stands.",
 .dark_only = true},
{.major = 403, .minor = -1,
 .base = "The landing at the gate of a labyrinth in the Abyss of Time: a raised platform of polished black and gold "
         "tiles inlaid with swirling gold patterns, floating in a bright golden haze over the sand. At its head stands "
         "a tall arched double door of gold, richly carved, between two burning torches on iron stands.",
 .dark_only = true},
{.major = 404, .minor = -1,
 .base = "The landing at the gate of a labyrinth in the Abyss of Time: a raised platform of polished black and gold "
         "tiles inlaid with swirling gold patterns, floating in a bright golden haze over the sand. At its head stands "
         "a tall arched double door of gold, richly carved, between two burning torches on iron stands.",
 .dark_only = true},
{.major = 405, .minor = -1,
 .base = "The landing at the gate of a labyrinth in the Abyss of Time: a raised platform of polished black and gold "
         "tiles inlaid with swirling gold patterns, floating in a bright golden haze over the sand. At its head stands "
         "a tall arched double door of gold, richly carved, between two burning torches on iron stands.",
 .dark_only = true},
{.major = 406, .minor = -1,
 .base = "The landing at the gate of a labyrinth in the Abyss of Time: a raised platform of polished black and gold "
         "tiles inlaid with swirling gold patterns, floating in a bright golden haze over the sand. At its head stands "
         "a tall arched double door of gold, richly carved, between two burning torches on iron stands.",
 .dark_only = true},
{.major = 407, .minor = -1,
 .base = "The landing at the gate of a labyrinth in the Abyss of Time: a raised platform of polished black and gold "
         "tiles inlaid with swirling gold patterns, floating in a bright golden haze over the sand. At its head stands "
         "a tall arched double door of gold, richly carved, between two burning torches on iron stands.",
 .dark_only = true},
{.major = 408, .minor = -1,
 .base = "The landing at the gate of a labyrinth in the Abyss of Time: a raised platform of polished black and gold "
         "tiles inlaid with swirling gold patterns, floating in a bright golden haze over the sand. At its head stands "
         "a tall arched double door of gold, richly carved, between two burning torches on iron stands.",
 .dark_only = true},
{.major = 409, .minor = -1,
 .base = "The approach to Colosseo Purgatorio, an arena deep in the Abyss of Time: a round terrace of polished marble "
         "with a red carpet edged in gold running across it, wrought-iron candelabras with lit candles, the massive "
         "bronze bases of great columns, and a freestanding ornate door. Beyond the rim, a field of golden flowers "
         "stretches into a glowing haze.", .dark_only = true},
{.major = 170, .minor = 211, .name = "Colosseo Purgatorio",
 .base = "Colosseo Purgatorio, the arena of the Abyss of Time: a wide floor of raked sand ringed by towering walls "
         "with balconies high above, all washed in a hazy golden light.", .dark_only = true},
{.name = "Malebolge",
 .base = "Malebolge, the first labyrinth behind the doors of the Abyss of Time: a stately old hall like the corridor of a grand public building: thick round columns banded in bronze, globe lamps on the walls, high windows of red glass, and a long green runner over a worn tile floor, all in a dim, dusty amber light.", .dark_only = true},
{.name = "Cocytus",
 .base = "Cocytus, a labyrinth behind the doors of the Abyss of Time: a nightmarish violet dungeon. Webs and glistening purple slime cover the floor and stone walls, gothic iron fences and a great barred gate close off the way, clusters of round lights glow overhead, and a huge grinning face leers down from behind the bars.", .dark_only = true},
{.name = "Caina",
 .base = "Caina, a labyrinth behind the doors of the Abyss of Time: a cold high-tech maze: steel walkways lined with thick pipes run between walls of glowing blue hexagonal grids, with security cameras in round frames watching from the walls and glowing blue rings and hanging screens of symbols overhead.", .dark_only = true},
{.name = "Antenora",
 .base = "Antenora, a labyrinth behind the doors of the Abyss of Time: an ancient temple of carved sandstone. Square pillars with round glowing lamps line a paved processional way, screens of geometric lattice stand between them, and pale green light spills from a doorway far ahead.", .dark_only = true},
{.name = "Ptolomea",
 .base = "Ptolomea, a labyrinth behind the doors of the Abyss of Time. Its first floors are a stately old hall like the corridor of a grand public building: thick round columns banded in bronze, globe lamps on the walls, high windows of red glass, and a long green runner over a worn tile floor, all in a dim, dusty amber light.", .dark_only = true},
{.name = "Judecca",
 .base = "Judecca, a labyrinth behind the doors of the Abyss of Time: a cold high-tech maze: steel walkways lined with thick pipes run between walls of glowing blue hexagonal grids, with security cameras in round frames watching from the walls and glowing blue rings and hanging screens of symbols overhead.", .dark_only = true},
{.name = "Empyrean",
 .base = "Empyrean, the last labyrinth behind the doors of the Abyss of Time: a golden cathedral. Huge twisted marble columns rise from a polished checkerboard floor of gold and black inlaid with circular medallions, red marble walls and hanging banners lead the eye to a tall stained-glass window glowing at the end of the nave, and warm golden light pours over everything.", .dark_only = true},
};

// The lines every place shares, said after its own description where the entry has no line of its own: the light
// (indoors and outdoors, by day, at sunset, at night; the Dark Hour), the season outdoors, January's decline, and
// what January adds to a street.
constexpr const char* kOutdoorDay = "It is daytime under an open sky.";
constexpr const char* kOutdoorEvening = "The sun is setting; the sky glows orange and violet and long shadows stretch across the ground.";
constexpr const char* kOutdoorNight = "It is night. Streetlights and lit windows glow against the dark sky.";
constexpr const char* kIndoorDay = "Daylight comes in through the windows.";
constexpr const char* kIndoorEvening = "Warm sunset light slants in through the windows.";
constexpr const char* kIndoorNight = "It is dark outside the windows; the place runs on its ceiling lights.";
constexpr const char* kDarkHour =
    "It is the Dark Hour. Everything is washed in a sickly green light under a huge, swollen moon; the electric lights "
    "are dead, dark puddles like blood stain the ground, and anyone caught in it stands sealed in an upright coffin.";
constexpr const char* kSpring = "Spring: the trees are fresh and green, and the air is mild.";
constexpr const char* kSummer = "It is summer: the air is hot and humid, the sunlight harsh, the trees thick and deep green.";
constexpr const char* kAutumn = "It is autumn: the trees have turned orange and red, and dry leaves gather on the ground.";
constexpr const char* kWinter = "It is winter: the trees stand bare and the air is cold enough to see your breath.";
constexpr const char* kJanuary1 =
    "This January the colour seems to be draining out of the world; everything looks faded and grey.";
constexpr const char* kJanuary2 = "It is late January, and the world has gone almost grey, as if its colour were dying out.";
constexpr const char* kTown1 =
    "Litter lies uncollected, black garbage bags pile up in the corners, and white posters stamped with a red symbol, "
    "put up by the cult that welcomes the coming Fall, are pasted over the walls, pillars and signs.";
constexpr const char* kTown2 =
    "The cult's white posters with their red symbol are everywhere now, plastered over every wall, pillar, sign and "
    "shutter and scattered on the ground among the garbage bags and litter.";
