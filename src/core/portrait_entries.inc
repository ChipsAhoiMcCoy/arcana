// The dialogue portraits (included by portrait_text.cpp): every outfit of every character the game has a
// bust-up for (T_BU_<PC|SC|NC><char>_Pose<x>_C<outfit>, 156 outfits in 267 poses), each rendered from the game's own
// textures and looked at (tools/bustup/outfits.py, 2026-11-12). An outfit's text is the character's look in it; a
// pose's text is said after it. Character ids: 1 protagonist, 2 Yukari, 3 Junpei, 4 Akihiko, 5 Mitsuru, 6 Fuuka,
// 7 Aigis, 8 Ken, 9 Koromaru, 10 Shinjiro, 11 Metis, 12 Aigis (Episode Aigis); 1xx Social Links, 2xx story, 1xxx others.
const Outfit kOutfits[] = {
  {1, 0, "A slim, pale teenage boy with soft slate-blue hair cut in a heavy rounded bob, a stray tuft at the crown "
         "and a long fringe falling across his right eye, so his grey-blue left eye does most of the looking. His "
         "face is calm and unreadable, lips barely parted as if he could not be bothered to finish a word. He wears "
         "a plain charcoal-grey top with a small upright collar split into a narrow V at the throat, nothing on it "
         "at all. Quiet and self-contained, he seems to watch the world from behind his hair without much caring "
         "what it does."},
  {2, 1, "A slim teenage girl with chin-length light brown hair that swings out at the ends, a side-swept fringe, "
         "big brown eyes and small silver studs in her ears. Her lips rest closed and soft, her look direct. Her "
         "pale grey stitched choker with its heart-shaped buckle sits snug at her throat above a crisp white school "
         "blouse, its pointed collar open at the neck and a breast pocket on the chest, nothing else added. Fresh "
         "and neat, the heart choker her one flourish, she looks bright, composed and quietly sure of herself."},
  {2, 2, "A slim teenage girl with chin-length light brown hair that swings out at the ends, a side-swept fringe, "
         "big brown eyes and small silver studs in her ears. Her lips rest in a small closed line, neither smiling "
         "nor cold. Her pale grey choker with its heart-shaped buckle sits snug at her throat, and below it the "
         "wide, sharply pointed white collar of her school shirt spreads out over a soft pink ribbed cardigan, a "
         "big red bow tied at the neck with its tails hanging down. Pink, red and neatly pressed, she looks "
         "self-assured and a little guarded."},
  {2, 5, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, big "
         "brown eyes and small silver studs in her ears, her closed lips soft and unsmiling. Her pale grey choker "
         "with its heart-shaped buckle stays snug at her throat. She wears a light pink camisole on thin red-edged "
         "straps, a little cluster of red dots on its front, her shoulders and arms bare. Light and simple, an easy "
         "summer look with her one signature touch kept, she seems relaxed and at ease in her own company."},
  {2, 6, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, big "
         "brown eyes and small silver studs in her ears, her closed lips soft and composed. Her pale grey choker "
         "with its heart-shaped buckle sits snug at her throat. She wears an off-the-shoulder pink ribbed knit top "
         "with a thick ruff of fluffy white fur around the neckline, thin dark straps showing over her bare "
         "shoulders. Soft pink and snowy fur, chosen with care, it is a fashionable look she wears with easy "
         "confidence."},
  {2, 51, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, big "
          "brown eyes and small silver studs in her ears. Her pale grey heart-buckled choker sits snug at her "
          "throat above the wide, pointed white collar of her school shirt, a big red bow tied beneath it over a "
          "soft pink ribbed cardigan. Around her upper arm is a red armband printed in black with S.E.E.S. and "
          "Special Extracurricular Execution Squad. Neat and pressed, the armband worn as plainly as the bow, she "
          "looks composed and ready for duty."},
  {2, 52, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, big "
          "brown eyes and small silver studs in her ears. A quiver of black-shafted, white-fletched arrows rides "
          "over her right shoulder. Over her school shirt, its pointed collar spread and a big red bow at the "
          "throat, she wears a pink top and a zip-up combat jacket, dark grey with a broad layered collar on one "
          "side and bright red on the other, a round black and white badge on the red sleeve. Her heart-buckled "
          "choker stays on. Armed and buttoned up, she looks alert and ready to shoot."},
  {2, 102, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, "
           "big brown eyes and small silver studs in her ears. Chunky dark-framed sunglasses with smoky lenses are "
           "pushed up on top of her head like a hairband. She wears a pale pink triangle bikini top edged in teal, "
           "its thin teal halter strings tied behind her neck; the top sits low, at the bottom of the picture, and "
           "for once there is no choker at her throat. With the shades parked in her hair and her lips resting "
           "closed, she looks unhurried and at ease, a day at the beach ahead of her."},
  {2, 106, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, "
           "big brown eyes and small silver studs in her ears. A black headband holds a tall white frill of "
           "scalloped, eyelet-punched lace upright on her head. Her maid's dress is charcoal black with puffed "
           "shoulders, a rounded white bib down the front fastened by four round black buttons, and a tall, sharply "
           "pointed white collar standing up under her chin; no choker today. Prim and spotless, she wears the "
           "costume with a cool, straight face that gives nothing away."},
  {2, 154, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, "
           "big brown eyes and small silver studs in her ears. She is wrapped in a dusty pink bath towel tucked "
           "straight across her chest, her shoulders, arms and collarbones bare, as at a hot spring. No choker or "
           "other trimmings today, only the studs. Her closed lips and level gaze stay as composed as ever, and "
           "without her usual accessories she looks simpler and a little more unguarded."},
  {2, 155, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, "
           "big brown eyes and small silver studs in her ears. She wears an inn's robes: a white cotton yukata "
           "crossed snugly at the neck, printed with a chain of grey rings linked by dark dots, and over it a loose "
           "slate-blue jacket with wide sleeves, worn open. No choker tonight. Bundled up in the plain borrowed "
           "robes, she looks warm, settled and quietly at ease."},
  {2, 156, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, "
           "big brown eyes and small silver studs in her ears. Her summer festival yukata is a bold pink and white "
           "checkerboard, crossed neatly at the neck and scattered with little five-petalled flowers in yellow, "
           "pink and orange-red on slender green stems, a glimpse of tan sash at her back. No choker tonight. "
           "Bright and cheerful in its pattern yet worn with her usual calm, closed-lipped poise, she looks ready "
           "for an evening of fireworks and stalls."},
  {2, 157, "A slim teenage girl with chin-length light brown hair, a side-swept fringe and big brown eyes. Above "
           "her left ear sits a cluster of pink and white silk blossoms, strands of little pink and silver petals "
           "dangling from it beside her cheek. Her formal kimono is deep rose pink printed with large "
           "white-outlined cherry blossoms, its collar edged in green, a teal patterned sash at the bottom of the "
           "picture and a gold and dark zigzag bow at her back. Dressed in her finest, she holds herself "
           "gracefully, composed and quietly pleased."},
  {2, 159, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, "
           "big brown eyes and small silver studs in her ears, her heart-buckled grey choker snug at her throat. "
           "She wears a coral-red long-sleeved crew-neck top under a work apron striped in pink and cream, its dark "
           "red shoulder straps and top edge picked out in white stitching, a pocket stitched on the front. Tidy, "
           "practical and still wearing her choker on the job, she looks capable and self-assured behind the "
           "counter."},
  {2, 201, "A slim teenage girl with chin-length light brown hair flicking out at the ends, a side-swept fringe, "
           "big brown eyes and small silver studs in her ears, her heart-buckled grey choker snug at her throat. "
           "Over her school shirt, its pointed white collar spread and a big red bow tied at the neck, she wears a "
           "pink top and a zip-up combat jacket, dark grey with a broad layered collar on one side and bright red "
           "on the other, a round black and white badge on the red sleeve. Dressed for a fight with nothing in her "
           "hands or on her back, she looks alert and steady."},
  {3, 1, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee on "
         "his chin. A slate-blue baseball cap with a white knotwork emblem sits forward on his head, never off. His "
         "white school shirt hangs open with its wide collar flipped up, over a plain navy T-shirt, and a silver "
         "chain hangs at his throat with a small square tag set with red and green studs. Cap, popped collar and "
         "chain all worn with care, he looks easygoing and a little showy."},
  {3, 2, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee, his "
         "slate-blue baseball cap with its white knotwork emblem pulled on forward. His school uniform is worn his "
         "own way: a charcoal-black blazer hanging open over a blue-grey shirt unbuttoned at the neck, its long "
         "collar turned up, a small green and yellow pin on the lapel. A silver chain hangs at his throat with a "
         "small square tag set with red and green studs. Sloppy on purpose and comfortable in it, he looks loose, "
         "friendly and a little restless."},
  {3, 5, "A lanky teenage boy with a long face and a long, thin neck, close-cropped dark hair, grey eyes and a "
         "scruffy little goatee, his slate-blue baseball cap with its white knotwork emblem pulled on forward. He "
         "wears a plain dark grey tank top that leaves his thin shoulders and arms bare, and a silver chain hanging "
         "low on his chest with a small square tag set with red and green studs. Gangly and unbothered, dressed for "
         "nothing more than a day of hanging around, he looks loose-limbed and carefree."},
  {3, 6, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee, his "
         "slate-blue baseball cap with its white knotwork emblem pulled on forward. A navy zip-up parka hangs open "
         "over a plain white T-shirt, its huge shaggy brown fur collar ruffed up around his skinny neck and "
         "spreading past his shoulders. His silver chain with its small red and green studded tag hangs at his "
         "chest. Bundled up and a little swallowed by all that fur, he looks warm, scruffy and pleased with the "
         "look."},
  {3, 51, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee, "
          "his slate-blue baseball cap with its white knotwork emblem pulled on forward. He wears his school "
          "uniform loose: a charcoal-black blazer open over a blue-grey shirt unbuttoned at the neck, its long "
          "collar turned up, a small green and yellow pin on the lapel, and the edge of a red armband printed in "
          "black just showing on his upper arm. His silver chain with its studded tag hangs at his throat. Slouchy "
          "as ever, the armband his one official touch, he looks easygoing and game."},
  {3, 52, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee, "
          "his slate-blue baseball cap with its white knotwork emblem pulled on forward. A big two-handed sword "
          "rides on his back, its long dark-gripped hilt and steel cross-guard rising high over his shoulder, held "
          "by a wide white leather strap with a steel buckle slung across his chest. Under it is only a blue-grey "
          "shirt open at the neck, collar up, a red armband on his sleeve and his studded silver chain at his "
          "throat. Armed and strapped up for a fight, he looks keen and a little cocky."},
  {3, 102, "A lanky, bare-chested teenage boy with a long face and long, thin neck, close-cropped dark hair, grey "
           "eyes and a scruffy little goatee. His slate-blue baseball cap is turned backwards, the brim jutting out "
           "behind and the adjustable strap with its metal buckle across his forehead. His only other accessory is "
           "the silver chain lying on his bare chest with its small square tag set with red and green studs. "
           "Skinny, sun-ready and wearing the cap even here, he looks relaxed and happily unselfconscious."},
  {3, 154, "A lanky, bare-chested teenage boy with a long face, a long thin neck and narrow shoulders, "
           "close-cropped dark hair, grey eyes and a scruffy little goatee. His slate-blue baseball cap stays on, "
           "turned backwards, the brim jutting out behind and the strap with its metal buckle across his forehead. "
           "The silver chain with its small square tag set with red and green studs lies on his bare chest, his "
           "only other accessory. Stripped down to cap and chain, he looks loose and completely at ease."},
  {3, 155, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee, "
           "his slate-blue baseball cap with its white knotwork emblem still pulled on forward. He wears an inn's "
           "robes: a white cotton yukata printed with a chain of grey rings, crossed loosely and low so a long V of "
           "bare chest shows, under a slate-indigo jacket worn open. No chain shows tonight. Rumpled in the "
           "borrowed robes but keeping his cap, he looks loose, unbothered and comfortably at home."},
  {3, 202, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee, "
           "his slate-blue baseball cap with its white knotwork emblem pulled on forward. No blazer today, only a "
           "blue-grey collared shirt, rumpled and open at the neck with its long collar standing up, a red armband "
           "around his upper arm. His silver chain with its small square tag set with red and green studs hangs at "
           "his throat. In shirtsleeves and ready to go, he looks scrappy, eager and ready to throw himself in."},
  {3, 901, "A lanky teenage boy with a long face, close-cropped dark hair, grey eyes and a scruffy little goatee, "
           "drawn in harsh, cold bluish light that leaves his cap and shoulders in heavy shadow. Dark rings sit "
           "under his eyes and the light catches his throat and the bridge of his nose. He wears his baseball cap "
           "with its knotwork emblem, a white shirt hanging open with its collar up over a navy T-shirt, and his "
           "silver chain with its studded square tag. The same clothes as ever, but he looks drained, sleepless and "
           "worn thin."},
  {4, 1, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
         "jaw and a white sticking plaster slapped at an angle above one eyebrow. His school uniform is a white "
         "shirt with a stiff collar and a thin black ribbon tie knotted loosely at the throat, under a red knitted "
         "sweater vest with a small gold letter pin on the chest. Neat, clean-cut and plainly fit, with the plaster "
         "the only thing out of place, he looks focused, disciplined and quietly sure of himself."},
  {4, 2, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
         "jaw and a white plaster stuck at an angle above one eyebrow. He wears his school uniform, a white shirt "
         "with a thin black ribbon tie under a red knitted sweater vest with a small gold letter pin, and the end "
         "of a tan leather holster strap shows buckled around his upper arm. Clean-cut on the surface with that "
         "hint of something strapped underneath, he looks composed, alert and ready to move."},
  {4, 5, "A lean, athletic teenage boy with short, spiky silver-grey hair swept up in ragged tufts, grey eyes under "
         "straight brows, a strong jaw and a white plaster stuck at an angle above one eyebrow. He wears a plain "
         "deep red V-neck shirt in a soft knit with thin pale pinstripes, a darker red band along the top of the "
         "shoulder, the V open low at his throat. No jewellery, nothing extra. Simple, sporty and unfussed, the "
         "shirt sits easily on his lean frame, and he wears it with calm, unshowy assurance."},
  {4, 6, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
         "jaw and a white plaster stuck at an angle above one eyebrow. A long red ribbed scarf is wound high around "
         "his neck, its ends hanging down his chest, over a dark charcoal shirt buttoned to the collar and a pale "
         "grey coat with tan-edged lapels. The deep red against the pale coat and silver hair makes a sharp winter "
         "picture, and he wears it with cool, easy composure."},
  {4, 51, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
          "jaw and a white plaster stuck at an angle above one eyebrow. He wears his school uniform, a white shirt "
          "with a thin black ribbon tie under a red knitted sweater vest with its small gold letter pin, and on his "
          "upper arm the end of a tan holster strap shows above the edge of a red armband. Neat, strapped and "
          "badged, he looks disciplined, composed and steady."},
  {4, 52, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
          "jaw and a white plaster stuck at an angle above one eyebrow. Over his white shirt, thin black ribbon tie "
          "and red knitted vest with its gold letter pin, he wears an open combat jacket with dark grey front "
          "panels set with large round brass snaps and one bright red sleeve bearing a round black and white "
          "quartered patch. Layered, bold and buttoned for action, he looks keyed up and confident, ready to step "
          "into a fight."},
  {4, 102, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
           "jaw and a white plaster stuck at an angle above one eyebrow. He wears a plain white crew-neck T-shirt "
           "with a ribbed neckband, printed on the chest in grey with small lettering reading SCUBA DIVING above a "
           "large bold SOS. No jewellery. Plain, loose and casual, the tee suits his lean frame, and he looks "
           "relaxed in it, easy and unguarded."},
  {4, 154, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
           "jaw and a white plaster stuck at an angle above one eyebrow. He is shirtless, as at a bath or hot "
           "spring, his neck, shoulders and upper chest bare, with nothing else worn, no towel and no jewellery "
           "showing. Even here the plaster stays on his brow, and he holds himself as straight and self-possessed "
           "as he does in uniform."},
  {4, 155, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
           "jaw and a white plaster stuck at an angle above one eyebrow. He wears an inn's robes: a white cotton "
           "yukata printed with a chain of grey rings, crossed loosely so a V of bare chest shows, under a "
           "slate-blue jacket with wide sleeves, worn open. The plaster still on his brow, settled into the soft "
           "borrowed robes, he looks unusually at ease, calm and off duty for a night."},
  {4, 159, "A lean, athletic teenage boy with short, spiky silver-grey hair, grey eyes under straight brows, a firm "
           "jaw and a white plaster stuck at an angle above one eyebrow. He wears a white collarless shirt with a "
           "narrow band neck, a short slit open at the throat and faint vertical pinstripes, and over it a dark red "
           "bib apron with shoulder straps, its edges outlined in dashed stitching. Neat and workmanlike, the apron "
           "tied on over a crisp shirt, he looks earnest, steady and attentive."},
  {5, 1, "A tall, poised teenage girl with long, heavy crimson hair falling past her shoulders in deep waves, one "
         "curl flicking outward, and a long fringe sweeping down over her left eye so only her right one, red and "
         "heavy-lidded, looks out. Her lips are soft coral, her expression cool and unhurried. Her school blouse is "
         "white with a high, close collar, full puffed sleeves and fine pleats, a large red ribbon bow tied at the "
         "throat, its wide tails spilling down her chest. Composed and faintly aloof, she holds herself very "
         "straight, with an air of quiet authority."},
  {5, 2, "A tall, poised teenage girl with long, heavy crimson hair falling past her shoulders in deep waves, one "
         "curl flicking outward, and a long fringe sweeping down over her left eye, her visible right eye red and "
         "heavy-lidded. Soft coral lips, a cool, contained expression. She wears a white school blouse with a high, "
         "close collar, full puffed sleeves and fine pleats, a large red ribbon bow at the throat with its wide "
         "tails falling down her chest. Immaculate and self-assured, every pleat and fold in place, she looks calm, "
         "commanding and a little remote."},
  {5, 5, "A tall, poised teenage girl with long, heavy crimson hair falling past her shoulders in deep waves, one "
         "curl flicking outward, and a long fringe sweeping down over her left eye, her visible right eye red and "
         "heavy-lidded, her lips soft coral. She wears a sleeveless white turtleneck in a fine vertical rib knit, "
         "its tall neck folded over, cut in deep at the armholes so her shoulders and arms are bare. No print, no "
         "trim, no jewellery: the red hair against the white does all the work. Understated and sure of her taste, "
         "she looks elegant and quietly reserved."},
  {5, 6, "A tall young woman with long, heavy crimson hair falling in loose waves past her shoulders, one curl "
         "flicking out at the side, and a long fringe that sweeps down over her left eye and hides it. Her one "
         "visible eye is red under a level brow, her lips coral and composed. She wears a black leather "
         "double-breasted coat with wide lapels and silver snap studs, its collar turned up, over a cream shirt "
         "whose tall, stiff collar stands folded around her throat like a scarf. Dark, sharp and expensively plain, "
         "she carries herself with cool, contained authority."},
  {5, 51, "A tall young woman with long, heavy crimson hair falling in loose waves past her shoulders, one curl "
          "flicking out at the side, and a long fringe sweeping over her left eye. Her visible eye is red and "
          "level, her coral lips closed and unsmiling. Her school uniform is a white blouse with a high collar and "
          "full, puffed sleeves, a large red bow tied at the throat with its wide loops and tails spilling down her "
          "chest, and a red armband with lettering on her upper arm, the mark of an office. Crisp and immaculate, "
          "she has the poise of someone used to being obeyed."},
  {5, 52, "A tall young woman with long, heavy crimson hair falling in loose waves past her shoulders, one curl "
          "flicking out at the side, and a long fringe over her left eye. Her visible eye is red and narrowed a "
          "little, her coral lips just parted. Over her white puffed-sleeve blouse and its big red bow she wears a "
          "hard black vest with a tall stand-up collar and a thick strap over one shoulder fastened by a brass "
          "stud, gear meant for fighting. The soft red bow against the black armour gives her the bearing of a "
          "noblewoman ready to lead a charge."},
  {5, 102, "A tall young woman with long, heavy crimson hair tumbling in loose waves over her bare shoulders, one "
           "curl flicking out at the side, and a long fringe over her left eye. Her visible eye is red and calm, "
           "her coral lips softly closed. At the beach she wears a plain white halter bikini top, its soft cups "
           "gathered into a small knot at the centre and sitting low, and a large red hibiscus with a long golden "
           "stamen is pinned at one strap, the only bright note on her. Even here she looks composed and a little "
           "apart, at ease without letting her guard down."},
  {5, 154, "A tall young woman with her crimson hair pinned up high at the back of her head, falling from there in "
           "big loose curls, the long fringe still sweeping over her left eye and a few strands loose at her cheeks "
           "and nape. Her visible eye is red and half-lidded, her coral lips slightly parted. At the hot spring she "
           "is wrapped in a dusty pink bath towel tucked straight across her chest, her neck, shoulders and arms "
           "bare above it. With her hair up and nothing formal about her, she looks unusually relaxed, though still "
           "self-possessed."},
  {5, 155, "A tall young woman with her crimson hair pinned up high at the back of her head and falling in big "
           "loose curls, the long fringe still over her left eye and a few strands loose at her cheeks. Her visible "
           "eye is red and half-lidded, her coral lips slightly parted. She wears an inn's white cotton yukata "
           "crossed neatly at the neck, printed with a chain of grey rings joined by dark dots, under a loose, "
           "wide-sleeved slate-blue jacket worn open. Off duty and plainly dressed, she still holds herself upright "
           "with quiet dignity."},
  {5, 156, "A tall young woman with her crimson hair pinned up high at the back of her head and falling in big "
           "loose curls, the long fringe over her left eye and stray strands at her cheeks. Her visible eye is red "
           "and half-lidded, her coral lips just parted. Her festival yukata is white cotton with fine paired pink "
           "stripes, printed with sprays of slender green leaves and hanging strands of purple and pink bell "
           "flowers, pink petals drifting among them, crossed neatly at the neck, with a green sash showing at her "
           "back. Light and summery, she wears it with graceful, unhurried poise."},
  {5, 157, "A tall young woman with her crimson hair swept up and pinned high, crowned with a large white silk "
           "flower ringed by looped gold cords, two red camellias beneath it and a gold tassel hanging behind her "
           "ear, her long fringe still over her left eye. Her visible eye is red and half-lidded, her coral lips "
           "slightly parted. Her New Year kimono is deep green silk with a large red camellia blooming across one "
           "shoulder and scattered orange dots, its collar layered in red over a gold-patterned band, with a gold "
           "brocade sash at her back. Lavish and formal, she wears it with the ease of long habit."},
  {5, 159, "A tall young woman with her crimson hair pinned up high at the back of her head and falling in big "
           "loose curls, the long fringe still over her left eye and strands loose at her cheeks. Her visible eye "
           "is red and half-lidded, her coral lips slightly parted. She wears a long-sleeved white turtleneck "
           "sweater in a fine vertical rib, and over it a plain dark brown bib apron on olive straps edged with "
           "dashed stitching, ready for the kitchen. Plainly dressed for work, she keeps the same composed, upright "
           "bearing she brings to everything."},
  {6, 1, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead and "
         "its jagged ends curling in at her jaw. Her large grey eyes are soft and a little wary, her small mouth "
         "closed in a faint, uncertain line. She wears a white long-sleeved blouse with a wide round neckline edged "
         "in scalloped lace and tied with a thin white ribbon, over a fitted bright teal turtleneck that rises high "
         "up her neck. Neat and slightly too buttoned-up, she seems shy and quietly watchful."},
  {6, 2, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead and "
         "its jagged ends curling in at her jaw. Her large grey eyes are gentle and a little wary, her small mouth "
         "closed. Her school uniform is a dark charcoal blazer with silver piping, a strap across the chest held by "
         "two round silver buttons and a red crest at the edge, over a high teal turtleneck patterned with faint "
         "lace. A thin white ribbon tied at the back of her neck trails over one shoulder. Small inside the dark "
         "blazer, she looks timid but attentive."},
  {6, 5, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead and "
         "its jagged ends curling in at her jaw. Her large grey eyes are soft and a little shy, her small mouth "
         "closed. She wears a light sleeveless mint-teal dress with wide ruffled straps over her shoulders and a "
         "square neckline edged in a ruffle and traced with a thin gold line, her arms and collarbones bare. Light "
         "and frilly, the dress suits her gentle, unassuming manner."},
  {6, 6, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead and "
         "its jagged ends curling in at her jaw. Her large grey eyes are soft and a little shy, her small mouth "
         "closed. She is bundled in a soft green poncho embroidered with white flowers, its wide cream collar "
         "trimmed in fur and tied at the front with a white ribbon ending in fluffy pompoms, over a charcoal ribbed "
         "turtleneck that rises high up her neck. Snug and storybook-sweet, she looks tucked away from the cold and "
         "content there."},
  {6, 52, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead, "
          "and large grey eyes, her small mouth closed. A chunky silver headset sits over her hair, its padded ear "
          "cups clamped on and a thin microphone arm curving to her chin. She is buried in a heavy charcoal "
          "greatcoat with a tall stand-up collar closed by a buttoned tab, brass buttons stamped with a cross, a "
          "short shoulder cape and gold cords hanging at one shoulder, a sliver of teal showing at her throat, and "
          "dark fingerless gloves. Small inside the heavy gear, she looks serious and ready to listen."},
  {6, 102, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead "
           "and its jagged ends curling in at her jaw. Her large grey eyes are soft and a little shy, her small "
           "mouth closed. At the beach she wears a plain mint-teal swimsuit top whose front is cut straight across, "
           "a fairly high, flat edge without print or trim, held up by thin white halter strings that tie in a "
           "loose bow behind her neck, her shoulders and arms bare. Simple and modest, it suits her quiet, slightly "
           "self-conscious way of holding herself."},
  {6, 154, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead "
           "and its jagged ends curling in at her jaw. Her large grey eyes are soft and a little shy, her small "
           "mouth closed. At the hot spring she is wrapped in a dusty pink terry-cloth towel tucked straight across "
           "her chest, her shoulders and arms bare above it. Even here she keeps her quiet, slightly reserved air."},
  {6, 155, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead "
           "and its jagged ends curling in at her jaw. Her large grey eyes are soft and a little shy, her small "
           "mouth closed. She wears an inn's white cotton yukata crossed at the neck, printed with a chain of grey "
           "rings joined by dark dots, under a loose, wide-sleeved slate-blue jacket worn open, its shoulders a "
           "little too big for her. Wrapped in the borrowed robes, she looks small, warm and at ease."},
  {6, 156, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead "
           "and its jagged ends curling in at her jaw. Her large grey eyes are soft and a little shy, her small "
           "mouth closed. Her festival yukata is mid-blue cotton crossed at the neck, printed with big golden "
           "sunflowers with brown, seed-dotted centres over faint pale green rings, and an orange obi bow peeks out "
           "at her back. The bright, sunny print lends her a gentle cheerfulness she wears a little bashfully."},
  {6, 157, "A slight teenage girl with a short teal bob, its choppy fringe cut straight and high on her forehead, "
           "and large grey eyes, her small mouth closed. Above one ear sits a hair ornament of an orange and a "
           "yellow fabric flower, green cords looping from them and ending in small silver beads. Her New Year "
           "kimono is bright teal printed with white, yellow and red chrysanthemums, its collar layered in cream, "
           "coral and olive, with a pink obi in a red diamond pattern and a yellow bow at the back. Dressed up and "
           "bright, she looks pleased but a little shy about it."},
  {6, 901, "A girl shown only as a flat dark grey silhouette, her face lost in deeper shadow so that only the faint "
           "outlines of her eyes and mouth show through, an unknown figure kept hidden. The outline gives her "
           "short, feathered bob, the tall stand-up collar of a school uniform closed at the throat, the shoulders "
           "of a blazer with the faint shapes of a button or two, and a thin ribbon tied at the back of her neck, "
           "its loops trailing behind one shoulder. No colour or pattern can be made out; she stands quiet and "
           "withheld."},
  {7, 2, "A girl-shaped android with short, feathery pale blonde hair and clear, bright blue eyes under a straight "
         "fringe, her face smooth and still, her lips closed. A gold headband cut with triangular openings crosses "
         "her hair, white mechanical units with red three-lobed centres sit where her ears would be, and fine seam "
         "lines mark her white throat. She wears the school uniform: a black blazer with silver piping, a large "
         "ruffled red bow at the throat and a round red badge with a black-and-white quartered emblem. The "
         "schoolgirl clothes over the machine give her an earnest, faintly uncanny calm."},
  {7, 6, "A girl-shaped android with short, feathery pale blonde hair and clear, bright blue eyes, her face smooth "
         "and still, her lips closed. A gold headband cut with triangular openings crosses her hair, and white "
         "mechanical units with red centres sit where her ears would be. Her clothes are prim and old-fashioned: a "
         "white blouse with a ruffled high collar and a frilled front, a loose white cravat tied in a soft bow, and "
         "an open teal-blue jacket over it. Dressed like a porcelain doll for an afternoon visit, she looks proper, "
         "earnest and quietly composed."},
  {7, 52, "A girl-shaped android in her battle body, short feathery pale blonde hair over clear, bright blue eyes, "
          "her face smooth and still. A gold headband cut with triangular openings crosses her hair and white "
          "mechanical units with red centres sit where her ears would be. Below the neck she is plainly a machine: "
          "smooth white plating, seamed at the throat, and heavy gold openwork shoulder joints with dark round "
          "hinges. A large ruffled red bow is tied at her throat, and a red armband with a black-and-white emblem "
          "and the letters S.E.E.S. circles one upper arm. Soft ribbon over hard metal, she looks gentle and ready "
          "to fight at once."},
  {7, 155, "A girl-shaped android with short, feathery pale blonde hair and clear, bright blue eyes, her face "
           "smooth and still, her lips closed. A gold headband cut with triangular openings crosses her hair, white "
           "mechanical units with red centres sit where her ears would be, and the seams of her white throat show "
           "plainly above the collar. She wears an inn's white cotton yukata printed with a chain of grey rings, "
           "under a loose, wide-sleeved slate-blue jacket worn open. The soft robes over her jointed neck make her "
           "look earnest and a touch out of place, as if relaxing were something she is still learning."},
  {7, 156, "A girl-shaped android with short, feathery pale blonde hair and clear, bright blue eyes, her face "
           "smooth and still, her lips closed. A gold headband cut with triangular openings crosses her hair, white "
           "mechanical units with red centres sit where her ears would be, and seams line her white throat. Her "
           "festival yukata is deep blue printed with large white blossoms with orange centres on slender stems, "
           "leaves and buds climbing between them, and a red obi bow shows behind her back. Fresh and pretty in it, "
           "she keeps her calm, doll-like poise."},
  {7, 157, "A girl-shaped android with short, feathery pale blonde hair and clear, bright blue eyes, her face "
           "smooth and still, her lips closed. A gold headband cut with triangular openings crosses her hair, and "
           "beside her white, red-centred ear unit is pinned a cluster of pink cherry blossoms with thin gold "
           "strips dangling below. Her New Year kimono is pale pink printed with large cherry blossoms, its collar "
           "edged in red and light blue over a gold patterned underlayer, with a green obi and a gold patterned bow "
           "at the back. Soft and springlike, she wears the finery with quiet, serious grace."},
  {7, 201, "A girl-shaped android with nothing over her battle body, short feathery pale blonde hair framing clear, "
           "bright blue eyes and a smooth, still face. A gold headband cut with triangular openings crosses her "
           "hair and white mechanical units with red centres sit where her ears would be. Her neck and chest are "
           "smooth white plating marked with fine seam lines, and heavy gold openwork joints with dark round hinges "
           "and ribbed black cylinders form her shoulders. With no bow or armband to soften it, the machinery "
           "stands bare, and she looks clinical, quiet and plainly built."},
  {7, 202, "A girl-shaped android in her battle body, short feathery pale blonde hair over clear, bright blue eyes, "
           "her face smooth and still. A gold headband cut with triangular openings crosses her hair and white "
           "mechanical units with red centres sit where her ears would be. Below the neck she is smooth white "
           "plating, seamed at the throat, with heavy gold openwork shoulder joints, dark round hinges and ribbed "
           "black cylinders. A large ruffled red bow tied at her throat is the only soft thing on her; there is no "
           "armband. Machine through and through but for that one ribbon, she looks calm and resolute."},
  {7, 203, "A girl-shaped android in her battle body after heavy damage, short pale blonde hair over a face smudged "
           "with soot and grime. A gold headband cut with triangular openings crosses her hair and white mechanical "
           "units with red centres sit where her ears would be, scuffed and dirtied like the rest of her. Her white "
           "plating and gold openwork shoulder joints are streaked with dark scorch marks and scratches, and the "
           "white trim beneath the ruffled red bow at her throat is torn into ragged edges. Battered and worn down, "
           "she still holds herself upright, like someone who has fought to the very end."},
  {7, 204, "A girl-shaped android with short, feathery pale blonde hair and clear, bright blue eyes, her face "
           "smooth and still, her lips closed. A gold headband cut with triangular openings crosses her hair, white "
           "mechanical units with red centres sit where her ears would be, and the seam lines of her white neck "
           "show plainly above a wide round collar. She wears a loose pale blue top like a nightdress, its round "
           "neckline edged in a white ruffle and a buttoned white placket, frilled at both sides, running down the "
           "front. Soft and homely on her, it makes her look gentle and a little fragile."},
  {8, 1, "A small boy of about ten with a soft, tousled light-brown bob, its fringe swept to one side and its ends "
         "flicking out over his ears, and large brown eyes in a round face. His small mouth is set in a flat, "
         "serious line. He wears a sleeveless orange hooded vest hanging open, its silver zip edge showing and the "
         "hood bunched at his neck, over a white collared shirt with small buttons and a thin black string tie in a "
         "loose bow, its long ends down his chest. He holds himself carefully straight, a child set on being taken "
         "seriously."},
  {8, 2, "A small boy of about ten with a soft, tousled light-brown bob, its ends flicking out over his ears, and "
         "large brown eyes in a round face, his small mouth set in a flat, serious line. His school uniform is an "
         "open dark grey zip jacket with a diagonal zip pocket, a small brass snap and a round badge, a red ring of "
         "gold lettering around a black-and-white quartered emblem. Under it an orange hoodie spreads its hood at "
         "his neck over a white collared shirt and a thin black string tie. Neat and buttoned-down, he looks "
         "determined to seem older than he is."},
  {8, 5, "A small boy of about ten with a soft, tousled light-brown bob, its ends flicking out over his ears, and "
         "large brown eyes in a round face, his small mouth set in a flat, serious line. He wears a zip-up track "
         "jacket, its front and lower sleeves burnt orange and its shoulders and upper sleeves mustard yellow, "
         "every seam piped in white, with a silver zip open at the collar over a dark grey crew-neck T-shirt. "
         "Sporty and practical, he still wears it with the same careful, solemn reserve."},
  {8, 6, "A small boy of about ten with a soft, tousled light-brown bob, its ends flicking out over his ears, and "
         "large brown eyes in a round face, his small mouth set in a flat, serious line. He is bundled in a thick, "
         "chunky cream knit sweater whose tall rolled turtleneck swallows him up to the chin, its front worked in "
         "vertical ribs, with tan shoulders and deeper caramel sleeves sewn on in raglan panels. Half buried in the "
         "big collar, he looks small and warm, though his face stays solemn."},
  {8, 52, "A small boy of about ten with a soft, tousled light-brown bob, its ends flicking out over his ears, and "
          "large brown eyes in a round face, his small mouth set in a flat, serious line. He wears his school "
          "clothes, an open dark grey zip jacket over an orange hoodie and a white collared shirt with a thin black "
          "string tie, with a black strap running over one shoulder and a big red armband around his upper arm "
          "bearing a black-and-white emblem. Kitted out for a fight, he looks small but grimly determined."},
  {8, 159, "A small boy of about ten with a soft, tousled light-brown bob, its ends flicking out over his ears, and "
           "large brown eyes in a round face, his small mouth set in a flat, serious line. He wears a plain "
           "lemon-yellow T-shirt with a dark grey ribbed crew neck, and over it a rust-brown apron on narrow "
           "straps, its edges and straps lined with dashed stitching and a stitched pocket across the bib. Ready "
           "for the kitchen, he looks earnest and attentive, a helper who means to do the job properly."},
  {9, 6, "A white Shiba Inu sitting upright, turned three-quarters to one side and shown from the chest up, with "
         "pricked pointed ears, two grey brow spots above striking red eyes, a black nose and soft grey shading "
         "over his neck, back and thick curled tail. He wears a sleeveless cream canvas vest with dashed stitching, "
         "and around his neck a thick grey metal collar with a round housing capped by a glowing blue glass dome, a "
         "small white angel wing fixed behind it on a white disc. Alert and sturdy, he sits like a loyal dog on "
         "watch, ready for whatever comes."},
  {9, 52, "A white Shiba Inu sitting upright, turned three-quarters to one side and shown from the chest up, with "
          "pricked pointed ears, two grey brow spots above red eyes and a thick curled grey tail, geared up for "
          "battle. Over his cream vest and thick grey metal collar, with its glowing blue glass dome and small "
          "white wing, he wears a black harness with brass-buckled straps, a round brass tag hanging at his chest, "
          "a white canister with red stripes strapped at his back and a red armband around his foreleg. Strapped "
          "and buckled in like a soldier, he looks keen, steady and ready to go."},
  {9, 201, "A white Shiba Inu sitting upright, broad and fluffy, with tall pointed ears, two grey dots for brows "
           "above bright red eyes, a black nose and a mouth hanging open in a pant, his pink tongue lolling out "
           "over his teeth. Soft grey shading runs over his neck, shoulders and back, his chest swells into a thick "
           "pale ruff, and a heavy plumed tail curls up behind him. No vest and no collar, only fur. Bright-eyed "
           "and eager, he sits like a dog who has been waiting for you and is very glad you came."},
  {10, 6, "A tall young man with a long jaw, shoulder-length brown hair hanging in ragged strands over grey eyes "
          "and spilling out behind his neck, his lips parted just enough to show his teeth. A dark grey knit beanie "
          "is pulled low to his brows, a small riveted metal plate on its ribbed brim. His long maroon-red pea coat "
          "is buttoned up double-breasted, its wide charcoal lapels and tall turned-up collar studded all over with "
          "little silver rivets. Bundled in and shut off, he looks hard, wary and in no mood to be approached."},
  {10, 52, "A tall young man with a long jaw, shoulder-length brown hair hanging in ragged strands over grey eyes "
           "and out behind his neck, lips parted over his teeth. His dark grey knit beanie, a small riveted metal "
           "plate on its brim, is pulled low. The long maroon-red coat hangs open here, its wide charcoal lapels "
           "and raised collar studded with silver rivets, over a black high-necked ribbed sweater bunched up to his "
           "chin, and a metal belt buckle shows at the bottom of the picture. Dressed to fight, he looks rough, "
           "tense and ready to wade in."},
  {10, 159, "A tall young man with a long jaw, shoulder-length brown hair hanging in ragged strands over grey eyes "
            "and out behind his neck, his lips parted over his teeth in a hard, sidelong look. His dark grey knit "
            "beanie is pulled low, a riveted metal plate with a slanted line on its brim. Under it he wears a plain "
            "charcoal mock-neck top and, over that, a tan canvas cooking apron on narrow straps, its bib edged in "
            "dashed stitching. The scowl and the apron sit together easily: he looks gruff, and quietly at home in "
            "a kitchen."},
  {11, 52, "A slender android girl with a short, sleek blue-black bob, its bangs falling between red eyes, and a "
           "faint, closed smile on her lips. Over her hair arches a gold band crowned with a red butterfly wing in "
           "a gold lattice, a round red disc at each ear pierced by a long gold spike: a headpiece that folds down "
           "into a butterfly visor over her face. Below the neck she is a seamless dark grey body with white "
           "jointed shoulder parts, and a red armband with a round emblem and white lettering is fixed to her upper "
           "arm. She looks calm and composed, quietly sure of herself."},
  {11, 201, "A slender android girl with a short, sleek blue-black bob, its bangs falling between red eyes, and a "
            "faint, closed smile on her lips. Over her hair arches a gold band crowned with a red butterfly wing in "
            "a gold lattice, a round red disc at each ear pierced by a long gold spike: a headpiece that folds down "
            "into a butterfly visor over her face. Below the neck she is a seamless dark grey body with white "
            "jointed shoulder parts, sleek and bare of any armband or insignia. She looks calm and composed, "
            "quietly sure of herself."},
  {12, 2, "A girl-shaped android with smooth fair skin, a choppy blond bob with long bangs falling between wide, "
          "bright blue eyes, and a small closed mouth that gives nothing away. A gold headband of open triangles "
          "sits in her hair, round white mechanical units with red three-lobed centres cover her ears, and her "
          "slender white neck is visibly jointed. She wears the school uniform: a black blazer with grey piping and "
          "a silver zip pull, a white collar, a big red ruffled bow at the throat and the round red-ringed school "
          "badge. Neat and very still, she has the attentive calm of a doll that is listening."},
  {12, 6, "A girl-shaped android with smooth fair skin, a choppy blond bob with long bangs falling between wide, "
          "bright blue eyes, and a small closed mouth. A gold headband of open triangles sits in her hair, round "
          "white mechanical units with red three-lobed centres cover her ears, and her neck is white and jointed. "
          "Her own clothes are old-fashioned and formal: a white blouse with a high frilled collar and a pleated "
          "front, a broad white cravat tied in a bow with long tails, and an open teal jacket. Prim and quietly "
          "elegant, she looks like a young lady from another century."},
  {12, 52, "A girl-shaped android with a choppy blond bob, long bangs falling between wide, bright blue eyes, and a "
           "small closed mouth. A gold headband of open triangles sits in her hair, round white ear units with red "
           "three-lobed centres cover her ears, and her white neck is jointed like a doll's. Here her machine body "
           "shows: a smooth white chest with a big red ruffled bow at the throat, and bulky gold shoulder joints of "
           "black ribbed cylinders, round black caps and open lattice plates, a red armband with a round emblem and "
           "lettering on her upper arm. Half schoolgirl, half war machine, she looks earnest and ready for orders."},
  {12, 53, "A girl-shaped android with a choppy blond bob, long bangs falling between wide, bright blue eyes, and a "
           "small closed mouth. A gold headband of open triangles sits in her hair, round white ear units with red "
           "three-lobed centres cover her ears, and her white neck is jointed like a doll's. Her machine body is on "
           "show: a smooth white chest with a big red ruffled bow at the throat, and bulky gold shoulder joints on "
           "both sides, black ribbed cylinders, round black caps and open lattice plates, with no armband. Half "
           "schoolgirl, half war machine, she looks earnest and quietly watchful."},
  {12, 54, "A girl-shaped android with a choppy blond bob and wide, bright blue eyes, armoured for a siege. A "
           "riveted steel visor band edged in gold crosses her brow over the lattice headband, white ear units with "
           "red centres at either side, and her white neck is jointed. A steel gorget hangs on chains over the red "
           "ruffled bow at her throat, a dark harness across her chest bristles with rows of brass bullet "
           "cartridges, and ribbed gold armour plates stack up over her shoulders, a red armband with a round "
           "emblem on her upper arm. Small, calm face above a body loaded for war, she looks steady and resolved."},
  {12, 201, "A girl-shaped android with a choppy blond bob and wide, bright blue eyes, armoured for a siege. A "
            "riveted steel visor band edged in gold crosses her brow over the lattice headband, white ear units "
            "with red centres at either side, and her white neck is jointed. A steel gorget hangs on chains over "
            "the red ruffled bow at her throat, a dark harness across her chest bristles with rows of brass bullet "
            "cartridges, and ribbed gold armour with open lattice plates caps both shoulders, with no armband. "
            "Small, calm face above a body loaded for war, she looks steady and resolved."},
  {101, 1, "A slim teenage boy with a long, ordinary face, short messy light-brown hair sticking up in tufts and "
           "falling in uneven bangs, and brown eyes glancing off to one side. His mouth is pressed into a small, "
           "wavering line, as if he is weighing something he would rather not say. He wears the summer school "
           "uniform: a white shirt with a pointed collar, small buttons and a breast pocket, a thin black ribbon "
           "tie knotted loosely, its ends hanging crooked. Plain and a little rumpled, he looks unsure of himself "
           "and trying not to show it."},
  {101, 2, "A slim teenage boy with a long, ordinary face, short messy light-brown hair sticking up in tufts and "
           "falling in uneven bangs, and brown eyes glancing off to one side, his mouth pressed into a small, "
           "wavering line. He wears the winter school uniform without much care: a black blazer with notched lapels "
           "and a silver strip slanting across the chest, a small green and yellow pin on the lapel and the round "
           "red-ringed school badge, over a white shirt with a thin black ribbon tie hanging loose. He looks "
           "rumpled and doubtful, never quite at ease."},
  {101, 6, "A slim teenage boy with a long, ordinary face, short messy light-brown hair sticking up in tufts and "
           "falling in uneven bangs, and brown eyes glancing off to one side, his mouth pressed into a small, "
           "wavering line. His own clothes are loud and cheerful: an open bright mustard-yellow zip jacket with a "
           "high stand-up collar lined in white and a row of snaps, over a dark grey V-neck T-shirt layered on a "
           "white one whose collar shows at his throat. The bright jacket and the hesitant face make him look like "
           "someone trying hard to seem relaxed."},
  {101, 158, "A slim teenage boy with a long, ordinary face, short light-brown hair poking up over a visor band, "
             "and brown eyes glancing off to one side, his mouth pressed into a small, wavering line. He is in a "
             "fast-food work uniform: an orange visor with a long pale yellow brim and a big looping W on its "
             "front, and an orange short-sleeved shirt with a pale yellow pointed collar, button strip, pocket edge "
             "and sleeve bands. Dressed for the counter, he looks a little embarrassed to be seen in it."},
  {102, 1, "A lean teenage boy with a long, angular face, dark grey hair slicked back from a high forehead, one "
           "stray lock curling forward and the ends flicking out at his nape. His narrow grey eyes slide sideways "
           "under one sharply raised brow, and his mouth is open in a thin, knowing half-smile. He wears the summer "
           "school uniform: a white shirt with a pointed collar and breast pocket, a thin black ribbon tie, and a "
           "mustard-yellow armband with large black characters on his upper arm. Stiff and self-satisfied, he looks "
           "like someone sure he has caught you out."},
  {102, 2, "A lean teenage boy with a long, angular face, dark grey hair slicked back from a high forehead, one "
           "stray lock curling forward and the ends flicking out at his nape. His narrow grey eyes slide sideways "
           "under one sharply raised brow, his mouth open in a thin, knowing half-smile. He wears the winter "
           "uniform correctly: a black blazer with a silver strip across its front, a small green and yellow lapel "
           "pin and the red school crest, a white shirt and thin black ribbon tie, and a mustard-yellow armband "
           "with black characters over the sleeve. Officious and pleased with himself, he looks ready to hand out a "
           "warning."},
  {103, 6, "An elderly man with wild, thinning white hair standing out in tufts around a bald crown, a dark spot on "
           "his forehead, bushy white brows and a white moustache. Black rectangular glasses sit low on his nose "
           "over heavy-lidded, watery eyes, and his lined face has a tired, wistful softness, lips slightly parted. "
           "He wears a cream knitted sweater with a dark grey ribbed turtleneck and red and blue zigzag bands "
           "across the chest and arms, and holds a dark wooden tobacco pipe. Stooped and gentle, he looks like a "
           "kind old man carrying a quiet sorrow."},
  {104, 6, "A small, very old woman with a round, deeply wrinkled face, sagging cheeks and heavy pouches under "
           "tired grey eyes, her thinning grey hair parted in the middle and cut to her chin. Her mouth is set in a "
           "small, downturned line, and her brows lift faintly, as if she is a little sad or worn. She wears a "
           "lilac blouse with a round collar and small buttons, printed with grey-blue leafy sprigs and tiny cream "
           "flowers, under a dark olive work apron whose broad straps fasten with round brass buttons. Soft and "
           "frail, she has the patient, weary look of someone used to long days alone."},
  {105, 101, "An athletic teenage boy with lightly tanned skin, a long jaw and short, spiky dark grey hair standing "
             "up on top and cut close at the sides. His dark eyes cut sideways and his lips are parted over his "
             "teeth in a half-grin, a confident, slightly cocky look. He wears a grey track jacket zipped right up "
             "to a tall stand-up collar, the zip pull at his throat, twin white stripes running down beside the zip "
             "and over his shoulders and red panels low on the chest. Loose-limbed and sure of himself, he looks "
             "like he is never far from a running track."},
  {105, 151, "An athletic teenage boy with lightly tanned skin, a long jaw and short, spiky dark grey hair standing "
             "up on top and cut close at the sides. His dark eyes cut sideways and his lips are parted over his "
             "teeth in a half-grin. He wears a dark grey sleeveless sports vest with a deep scooped neck, its "
             "neckline and armholes edged in red and a black and red patch at one shoulder, leaving his lean "
             "shoulders, arms and collarbones bare. Stripped down for practice, he looks loose, keen and full of "
             "himself."},
  {106, 1, "A teenage girl with tanned skin, short blue-black hair swept over to one side, a small tuft of ponytail "
           "sticking up at the back of her head and a slim pink hairpin above her temple. Her big brown eyes are "
           "open wide and her lips just parted, as if she has stopped mid-sentence. She wears the summer school "
           "uniform: a white blouse with a stand-up collar, small buttons and a breast pocket, and a large red bow "
           "with ruffled tails at the throat. Sun-browned and boyish, she looks open, eager and ready to be off."},
  {106, 2, "A teenage girl with tanned skin, short blue-black hair swept over to one side, a small tuft of ponytail "
           "sticking up at the back of her head and a slim pink hairpin above her temple. Her big brown eyes are "
           "open wide and her lips just parted, as if she has stopped mid-sentence. She wears the winter school "
           "uniform neatly: a black jacket with grey piping and a front flap fastened with silver buttons and a zip "
           "pull, a white collared blouse with a large red bow, and the round red-ringed school badge. Bright-eyed "
           "and direct, she looks keen and full of energy."},
  {106, 6, "A teenage girl with tanned skin, short blue-black hair swept over to one side, a small tuft of ponytail "
           "sticking up at the back of her head and a slim pink hairpin above her temple. Her big brown eyes are "
           "open wide and her lips just parted, as if she has stopped mid-sentence. Off duty she dresses easy and "
           "sporty: an open black zip-up hoodie, its white-lined hood folded around her neck and a white stripe "
           "down each sleeve, over a coral-red top with a wide scooped neck that bares her collarbones. Relaxed and "
           "boyish, she looks friendly and quick to laugh."},
  {106, 101, "A teenage girl with tanned skin, short blue-black hair swept over to one side, a small tuft of "
             "ponytail sticking up at the back of her head and a slim pink hairpin above her temple. Her big brown "
             "eyes are open wide and her lips just parted, as if she has stopped mid-sentence. She wears the "
             "athletics team's grey track jacket zipped up to a tall stand-up collar, the zip pull under her chin, "
             "twin white stripes down beside the zip and over her shoulders and red panels low on the chest. Zipped "
             "up for the track, she looks brisk, capable and eager to get going."},
  {107, 6, "An online game avatar drawn as a translucent green hologram of flat, low-polygon facets, crossed all "
           "over by horizontal scan lines and fringed with pink and cyan where its edges flicker. It has a short "
           "bob of hair that flicks out in points at the sides, a single half-lidded eye looking out from under a "
           "heavy fringe, and a bulky coat whose high collar rises over its mouth, marked with stripes and little "
           "diamond shapes. Blocky and faceless but for that one eye, it has a cool, sly, slightly mysterious air, "
           "like someone met only on a screen."},
  {108, 1, "A slim teenage boy with thick, soft, wavy light-brown hair falling in loose curls over his forehead, "
           "ears and neck, and grey eyes behind thin black rectangular glasses. His mouth curves in a small, gentle "
           "closed smile and his eyes look out at an angle, mild and friendly. He wears the summer school uniform: "
           "a crisp white collared shirt with small buttons and a breast pocket and a thin dark ribbon tied loosely "
           "at the collar. Tidy and soft-spoken in look, he seems quietly kind and easy to talk to."},
  {108, 2, "A slim teenage boy with thick, soft, wavy light-brown hair falling in loose curls over his forehead, "
           "ears and neck, and grey eyes behind thin black rectangular glasses. His mouth curves in a small, gentle "
           "closed smile and his eyes look out at an angle, mild and friendly. He wears the winter school uniform "
           "tidily: a charcoal blazer with notched lapels and a thin silver strip, a small green and cream bar pin "
           "on the lapel and the red-ringed school crest, over a white shirt and a thin dark ribbon tie. Neat and "
           "unassuming, he seems quietly kind and easy to talk to."},
  {108, 6, "A slim teenage boy with thick, soft, wavy light-brown hair falling in loose curls over his forehead, "
           "ears and neck, and grey eyes behind thin black rectangular glasses. His mouth curves in a small, gentle "
           "closed smile and his eyes look out at an angle, mild and friendly. Off duty he wears a collared "
           "button-up shirt in a bold plaid of red, sky blue, white and grey, open at the neck over a dark green "
           "T-shirt whose round collar just shows. Comfortable and unshowy, he looks relaxed and quietly content."},
  {109, 1, "A slender teenage girl with very long, straight brown hair parted in the middle and swept back off a "
           "high forehead, falling past her shoulders with long strands framing her face. Brown eyes look out from "
           "behind black rectangular glasses, lids half lowered, and her lips curve in a small, shy smile. She "
           "wears the summer school uniform: a white collared blouse with small buttons and a large, full red bow "
           "spreading across her chest. Proper and soft-spoken in look, she seems shy, careful and quietly pleased."},
  {109, 2, "A slender teenage girl with very long, straight brown hair parted in the middle and swept back off a "
           "high forehead, falling past her shoulders with long strands framing her face. Brown eyes look out from "
           "behind black rectangular glasses, lids half lowered, and her lips curve in a small, shy smile. She "
           "wears the winter school uniform very properly: a charcoal jacket with thin silver piping and the red "
           "school crest just showing, over a white collared blouse with white cuffs and a large, full red bow at "
           "the collar. Neat and reserved, she seems shy, careful and quietly pleased."},
  {109, 6, "A slender teenage girl with very long, straight brown hair parted in the middle and swept back off a "
           "high forehead, falling past her shoulders with long strands framing her face. Brown eyes look out from "
           "behind black rectangular glasses, lids half lowered, and her lips curve in a small, shy smile. Out of "
           "uniform she dresses softly and a little old-fashioned: a warm tan-orange cardigan with a frilled ruffle "
           "down its button front, over a cream top with a high, close collar cut in a zigzag at its edge. Gentle "
           "and modest, she seems shy, careful and quietly pleased."},
  {110, 6, "A little girl of about eight with a round face, big brown eyes and a small, closed smile. Her brown "
           "hair is pulled smoothly back into a braided bun wrapped in a ruffled pink scrunchie. She wears an open, "
           "slightly big denim-blue shirt with a pointed collar, silver snaps and rolled sleeves over a plain pink "
           "T-shirt, and on her back a glossy red leather school satchel, the stiff box kind, with red straps and "
           "silver fittings, a white cord dangling from a clip. Bright and sweet, she looks cheerful and brave in a "
           "small, determined way."},
  {111, 6, "A small, slight, pale boy who looks about ten, with messy, tousled dark blue-grey hair cut short with "
           "ragged bangs, and large, bright cyan-blue eyes, a small dark mole under his left eye. His face is calm, "
           "with the faintest closed smile, and his wide eyes look straight out without blinking. He wears a "
           "long-sleeved shirt in broad stripes of dark grey and off-white, much like old-fashioned pyjamas, with a "
           "round neck and three small grey buttons. Gentle and very still, he has a quietly eerie air, as if not "
           "entirely there."},
  {112, 1, "A slim, pale teenage boy with a neat, rounded blond bowl cut, thick straight bangs down to his brows, "
           "and pale turquoise eyes, his lips curved in a small, pleased smile. He carries an open folding fan of "
           "black paper on black ribs, painted with two gold butterflies above sweeping gold arcs and scattered "
           "gold dots. He wears the summer school uniform: a white shirt with a breast pocket and a thin black "
           "ribbon tie. The fan held up like a prop, he looks delighted with himself and charmingly earnest about "
           "it."},
  {112, 2, "A slim, pale teenage boy with a neat, rounded blond bowl cut, thick straight bangs down to his brows, "
           "and pale turquoise eyes, his lips curved in a small, pleased smile. He carries an open folding fan of "
           "black paper on black ribs, painted with two gold butterflies above sweeping gold arcs and gold dots. He "
           "wears the winter school uniform: a charcoal blazer with a thin silver strip, a green and cream lapel "
           "pin and the red-ringed school crest, over a white shirt and a thin black ribbon tie. Fan raised and "
           "smiling, he looks delighted with himself and charmingly earnest about it."},
  {112, 6, "A slim, pale teenage boy with a neat, rounded blond bowl cut, thick straight bangs down to his brows, "
           "and pale turquoise eyes, his lips curved in a small, pleased smile. Off duty he wears a plain dark "
           "charcoal long-sleeved crew-neck T-shirt, printed on the chest with a faint grey Eastern dragon, its "
           "scaly body coiled and its horned head turned aside, the print almost lost against the dark cloth. "
           "Low-key and comfortable, he looks contented and quietly amused."},
  {113, 6, "A middle-aged man with a long, tanned face, lines under his eyes and around his mouth, and thick, wavy "
           "dark grey hair swept back and falling loose over his ears and collar. His narrow grey eyes slide "
           "sideways under heavy lids, one brow cocked, and his mouth sits in a flat, slightly crooked line, as if "
           "weighing what you might be worth. He wears a grey-green suit jacket with notched lapels over a crisp "
           "white shirt with a pointed collar and a plain dark red tie in a neat knot. He has the easy, slippery "
           "assurance of a man who always has an angle."},
  {114, 6, "An elderly, heavyset man, completely bald, his tanned skin deeply creased across the brow, around the "
           "eyes and down the jowls, with large ears and loose folds at his throat. His grey eyes glare up and away "
           "under a hard frown, his lips pulled back to show clenched teeth. He wears dark charcoal monk's robes "
           "crossed over white under-layers, a broad pale band running over one shoulder and knotted low on his "
           "chest. In one thick hand, heavy with gold rings, he holds up a fat brown cigar with an ashy, "
           "smouldering tip. Gruff and unrepentant, he looks more like a hard-living brawler than a holy man."},
  {114, 901, "An elderly, heavyset man, completely bald, his tanned skin deeply creased across the brow, around the "
             "eyes and down the jowls, with large ears and loose folds at his throat. His grey eyes look up and "
             "away under a heavy frown, his mouth set in a grimace that shows his teeth. He wears dark charcoal "
             "monk's robes crossed over white under-layers, a broad pale band running over one shoulder and knotted "
             "low on his chest. No cigar or ringed hand is in view here, and without them he looks plainer and "
             "graver, a weathered old monk with something weighing on him."},
  {115, 6, "An athletic teenage boy with lightly tanned skin, short spiky dark grey hair cropped close at the "
           "sides, thick dark brows and grey eyes. His eyes glance off to one side and a small, lopsided half-smile "
           "tugs at his mouth, friendly and a little sheepish. He wears a light teal zip-up hoodie with the hood "
           "down around his neck, a silver zipper, grey drawstrings knotted at the ends and a small dark triangle "
           "logo on the chest, each sleeve striped in black edged with white and printed with grey triangles. "
           "Loose-limbed and easygoing, he carries himself like someone at home in his own body."},
  {116, 1, "A heavyset teenage boy with fair skin, a big round face with full cheeks and a soft double chin, short "
           "neat black hair with one curl springing up on top and another dipping onto his forehead, large ears and "
           "droopy grey eyes. His brows slope up in the middle and his lips pout open, a look of glum, put-upon "
           "weariness. He wears the summer school uniform: a white shirt pulled taut over his broad frame, with "
           "small white buttons, a breast pocket and a thin dark green ribbon tie hanging loose in a bow at the "
           "collar. Soft and slumped, he looks sulky yet oddly endearing."},
  {116, 2, "A heavyset teenage boy with fair skin, a big round face with full cheeks and a soft double chin, short "
           "neat black hair with one curl springing up on top and another dipping onto his forehead, large ears and "
           "droopy grey eyes. His brows slope up in the middle and his lips pout open, a look of glum, put-upon "
           "weariness. He wears the winter school uniform: a charcoal-black blazer with thin pale piping, a small "
           "green and cream pin and the red-ringed school crest, over a white shirt with a thin dark green ribbon "
           "tie hanging loose at the collar. Soft and slumped, he looks sulky yet oddly endearing."},
  {117, 6, "A thin, pale young man with a narrow face, straight chin-length silver-grey hair falling in a "
           "side-swept fringe across his brow, and grey eyes. His brows lift and knit, his lips part over his "
           "teeth, and he gazes upward with a look of faint pain and longing. He wears a loose long-sleeved shirt "
           "in bold vertical stripes of slate blue and pale grey, its pointed collar standing up and its top "
           "buttons undone so it falls open over his bony collarbones. Frail and far away, he looks like someone "
           "listening for something only he can hear."},
  {201, 6, "A short, hunched, wizened old man drawn like a goblin from a fairy tale. His nose comes first: "
           "impossibly long, straight and pointed, jutting out like a spike. His bald tan dome is fringed by wild, "
           "wispy white hair, with long pointed ears and thick, dark, curling brows drawn down in a scowl. Huge "
           "bulging eyes, bloodshot around tiny pupils, stare out above a wide grin full of teeth. He wears a black "
           "suit with a white shirt and dark tie, and thin white gloves on his long, bony fingers. Gleefully "
           "sinister, he looks delighted by something he has not yet told you."},
  {202, 6, "A slender young woman with pale skin, a short silver bob with blunt bangs curving in at her jaw, bright "
           "yellow eyes and a small, knowing smile, her lips parted as if about to say something delightful. Her "
           "royal-blue attendant's uniform fits close: a small brimmed cap with a side button tilted on her head, a "
           "sleeveless dress with a tall stand-up collar that bares her shoulders and arms, a dark seam down its "
           "front, and long blue gloves past her elbows. On her chest sits a large round emblem, navy and sky-blue "
           "rings around a dark centre with a gold dot. Her head tilts toward you with the poised, faintly uncanny "
           "courtesy of a hostess enjoying a private joke."},
  {202, 901, "A slender young woman with pale skin, a short silver bob with blunt bangs curving in at her jaw and "
             "bright yellow eyes, peering through chunky black glasses with thick, rounded-square frames, her lips "
             "parted in a small, pleased smile. The rest is her royal-blue attendant's uniform: a small brimmed cap "
             "tilted on her head, a sleeveless dress with a tall stand-up collar that bares her shoulders, a large "
             "round emblem of navy and sky-blue rings around a dark centre with a gold dot, and long blue gloves. "
             "She wears the glasses with the earnest relish of someone playing the scholar."},
  {202, 902, "A slender young woman with pale skin, a short silver bob with blunt bangs and bright yellow eyes, "
             "dressed up as a cat with total deadpan commitment. Fluffy white cat ears with pink insides stand up "
             "on either side of her head, and a white furry cat-muzzle mask with a pink nose and black whiskers "
             "covers her nose and upper lip. Her tilted cap stays on, over her royal-blue attendant's uniform: a "
             "sleeveless dress with a tall stand-up collar that bares her shoulders, a large round emblem of navy "
             "and sky-blue rings, and long blue gloves. Her eyes stay calm above the whiskers, utterly serious "
             "about the game."},
  {202, 903, "A slender young woman with pale skin and a short silver bob with blunt bangs, gleefully disguised in "
             "novelty joke glasses: round black frames with white lenses painted in swirling rings that hide her "
             "eyes, a big pinkish-red plastic nose and a bushy black moustache curled up at both ends, her lips "
             "parted beneath it in a small smile. Her tilted royal-blue cap stays on, over her attendant's uniform: "
             "a sleeveless dress with a tall stand-up collar that bares her shoulders, a large round emblem of navy "
             "and sky-blue rings, and long blue gloves. A ridiculous gag, she wears it with perfect poise."},
  {202, 904, "A slender young woman with pale skin, a short silver bob with blunt bangs and bright yellow eyes, "
             "merrily playing Santa. A red Santa hat with a thick white fur brim sits in place of her cap, its tip "
             "flopping to one side into a fluffy pom-pom, and a full white false beard and curled moustache hide "
             "her mouth and chin. Below is her royal-blue attendant's uniform: a sleeveless dress with a tall "
             "stand-up collar that bares her shoulders, a large round emblem of navy and sky-blue rings, and long "
             "blue gloves. Her calm yellow eyes above the beard make it festive, absurd and oddly dignified."},
  {211, 6, "A gaunt, bare-chested man with long, wavy silver-grey hair parted in the middle and falling past his "
           "shoulders and down his chest, held by a thin dark metal circlet across his brow. He has sunken cheeks, "
           "stubble along his jaw and pale yellow eyes under heavy lids and troubled, lifted brows, his lips just "
           "parted over his teeth. Purple tattoos cover his shoulders: on his right, a crowned serpent coiled "
           "around a spiky sun with a pink spiral at its heart; on his left, a tangle of figures half hidden by his "
           "hair. His lean chest is bare to below the collarbones, the hair spilling over it. He has the look of a "
           "wandering prophet, weary, unguarded and strangely calm."},
  {212, 6, "A lean young man with pale skin and straight, glossy dark blue hair cut in a jaw-length bob, its long "
           "fringe falling across one side of his face. Glasses with black rectangular frames and orange-tinted "
           "lenses sit over dark eyes that slide sideways, wary and unblinking, above a flat, tight-lipped mouth. "
           "His bright green jacket is zipped all the way up into a tall stand collar that covers his chin, two "
           "light grey stripes running down beside the zip, with black buckled harness straps over both shoulders "
           "and a black band around one upper arm. Guarded and watchful, he gives nothing away."},
  {213, 6, "A pale teenage girl with the still, fragile look of a gothic porcelain doll. Long, straight red hair "
           "with blunt bangs falls down her back and over her shoulders, white ribbons laced through it. Her grey "
           "eyes sit under heavy lids rimmed with spiky lashes and soft purple shadow, her lips closed in a small, "
           "blank pout. A frilly white headdress with a black band studded in silver diamonds crowns her head, "
           "pierced through by a long silver pin shaped like a sword. Her white frilled dress has a ruffled "
           "neckline and a high ruffled collar tied with a bow. Distant and expressionless, she seems to look "
           "straight through you."},
  {213, 201, "A pale, slender teenage girl stripped of all her gothic finery, which leaves her looking quieter and "
             "more fragile. Very long, straight red hair with blunt bangs cut across her brows falls loose over her "
             "shoulders and down past the edge of the picture. Her grey eyes sit under heavy lids rimmed with spiky "
             "dark lashes and a trace of purple shadow, her pale pink lips closed in a small pout. She wears only a "
             "plain pale aqua hospital gown, its wrap-over front crossing at her chest, loose and without trim. No "
             "headdress, ribbons or jewellery remain. Bare of her armour of frills, she seems smaller, drifting and "
             "far away."},
  {221, 2, "A slender teenage boy with fair skin and dark grey-black hair swept back from his forehead, a few "
           "strands springing up on top and the ends flicking out at his nape. He has bright blue eyes, a small "
           "black beauty mark under one eye, and his lips are parted in an easy, confident smile. He wears a white "
           "button-front shirt with small dark square buttons under his open dark school jacket, and his signature "
           "long, soft pale-yellow scarf, edged in a dark outline, wrapped high around his neck and hanging down "
           "the front. Breezy and self-possessed, he looks like someone sure the room is already his."},
  {221, 154, "A slender teenage boy with fair skin and dark grey-black hair swept back from his forehead, a few "
             "strands springing up on top and the ends flicking out at his nape. He has bright blue eyes, a small "
             "black beauty mark under one eye, and his lips are parted in an easy smile. He is bare-chested and "
             "bare-shouldered, as at a bath or hot spring, with no scarf or jewellery, the picture ending at his "
             "upper chest. Even with nothing to hide behind, he keeps the same relaxed, unbothered charm."},
  {221, 155, "A slender teenage boy with fair skin and dark grey-black hair swept back from his forehead, a few "
             "strands springing up on top and the ends flicking out at his nape. He has bright blue eyes, a small "
             "black beauty mark under one eye, and his lips are parted in an easy smile. He wears an inn-style "
             "yukata: a plain slate blue outer robe with wide sleeves, wrapped over a white inner robe patterned in "
             "grey chains of linked circles, its collar crossing in a V at his throat. No scarf or jewellery. He "
             "looks pleasantly unwound and right at home."},
  {222, 6, "A lanky middle-aged man with pale skin and long, wavy brown hair combed back from a high, receding "
           "hairline and falling loose behind his shoulders. Grey eyes look out from behind thin wire-rimmed "
           "glasses with narrow rectangular lenses, his brows gently raised, and a small pointed goatee sits under "
           "a mild, closed mouth. He wears a light tan double-breasted coat with wide notched lapels and pale "
           "buttons over a dark grey ribbed turtleneck, its high collar folded up under his chin. Rumpled and "
           "soft-spoken, he has the harmless, faintly absent air of an academic."},
  {223, 1, "A teenage girl with tanned skin and long, wavy ginger-brown hair with straight, blunt bangs, part of it "
           "caught up in a short, spiky ponytail high at the back of her head and the rest falling past her "
           "shoulders. Her brown eyes are framed by thick lashes, and her glossy lips are parted as if "
           "mid-sentence. She wears the summer school uniform: a white blouse with a wide, pointed collar, a dark "
           "grey knitted V-neck sweater vest with ribbed edges, and a large red bow tied at the collar. Trendy and "
           "quick, she carries herself with sharp, confident attitude."},
  {223, 2, "A teenage girl with tanned skin and long, wavy ginger-brown hair with straight, blunt bangs, part of it "
           "caught up in a short, spiky ponytail high at the back of her head and the rest falling past her "
           "shoulders. Her brown eyes are framed by thick lashes, and her glossy lips are parted as if "
           "mid-sentence. She wears the winter school uniform: a long-sleeved dark grey knitted cardigan with "
           "ribbed edges over a white blouse with a wide, pointed collar, and a large red bow tied at the collar. "
           "Trendy and quick, she carries herself with sharp, confident attitude."},
  {223, 6, "A teenage girl with tanned skin and ginger-brown hair with straight, blunt bangs, a short, spiky "
           "ponytail tied high at the back and the rest hanging to her shoulders. Her brown eyes are framed by "
           "thick lashes, and her glossy lips are parted as if mid-sentence. She is dressed down in an oversized "
           "cream hooded jacket hanging open, its hood bunched behind her neck, a grey-blue lining showing and a "
           "round snap on each front edge, over a pink scoop-neck top, with a small silver heart pendant on a thin "
           "chain at her collarbone. Cosy and casual, the look softens her usual sharp edge without dulling it."},
  {224, 6, "A stern middle-aged man with pale skin and short dark grey hair swept across his forehead to one side. "
           "A black eyepatch covers his right eye, its thin strap cutting diagonally up across his brow and into "
           "his hair; his other eye, grey and hard, glances sideways under a frowning brow, and his mouth is set in "
           "a thin, unyielding line. He wears an impeccable grey three-piece suit: notched lapels with a small "
           "round gold pin, a darker charcoal waistcoat, a white shirt with a pointed collar and a dark red tie. "
           "Cold and commanding, he has the hard, almost military bearing of a man used to being obeyed."},
  {252, 1, "A young boy with fair skin, short, tousled silver-white hair and grey eyes, a beige sticking plaster "
           "across the bridge of his nose. His brows are level and his lips slightly parted, his look steady and a "
           "little defiant for his age. He wears a white collared button-up shirt, open at the neck, with a breast "
           "pocket on the left, over a plain red T-shirt whose round neck shows at his throat. Scrappy and "
           "self-reliant, he already wears the marks of fights he means to win."},
  {253, 1, "A younger teenage girl with fair skin and wavy red hair falling in loose curls past her shoulders, a "
           "long side-swept fringe and a thin purple hairband. Her red eyes look out calmly and her soft pink lips "
           "rest just parted, composed and faintly reserved. She wears a school uniform: a white long-sleeved "
           "blouse with a small pointed collar, a dark grey knitted sweater vest with ribbed edges, and a large red "
           "bow at the collar with long, layered ruffled tails. Neat and ladylike, she already carries herself like "
           "a young heiress, polite and a little aloof."},
  {254, 5, "A little girl with fair skin, red eyes and red hair with a side-swept fringe, the rest worn in long, "
           "springy ringlets hanging on both sides of her head. Her small mouth rests in a faint, contented smile, "
           "her gaze calm and direct. She wears a white long-sleeved blouse with fine vertical pleats down the "
           "front, small round white buttons and a high stand collar, and a large red bow tied at her throat, "
           "fastened at its centre by a gold-framed oval brooch set with a dark green stone. Prim and perfectly "
           "turned out, she looks dressed for a formal portrait and quite at ease in it."},
  {1081, 6, "A lanky man with pale skin, messy, spiky dark hair, thick black rectangular glasses and heavy stubble "
            "on his chin and jaw, a red pencil tucked behind his left ear. His brows lift in a worried slant and "
            "his mouth hangs slightly open, a look of bleary, harried bewilderment. He wears a rumpled white lab "
            "coat hanging open over a mustard-yellow T-shirt with a dark brown round collar and a white outline "
            "print of a hand with two fingers raised. Scruffy and a little frayed, he looks as if he forgot to go "
            "home from the lab last night."},
  {1082, 6, "A middle-aged man with fair skin, lined cheeks and bags under his eyes, and neat, straight grey-brown "
            "hair cut in a mop that falls to his brows and over his ears. His grey eyes look out under level brows "
            "and his closed mouth sits in a mild, patient line. He wears a plain grey suit jacket with notched "
            "lapels, a white shirt with a pointed collar, and a tie striped diagonally in purple and dark grey. "
            "Tired and unassuming, he has the worn calm of a man who has sat through a great many meetings."},
  {1083, 6, "A middle-aged man with tanned, lined skin, brown eyes and a short goatee, wearing a full samurai "
            "helmet as if it were perfectly normal. The dark iron helmet is a domed bowl with a tall, curved gold "
            "crescent rising from its front, gold-tipped side flaps folded back at his temples and a flared neck "
            "guard of riveted plates, tied under his chin with a dark cord. Below it he wears a brown plaid suit "
            "jacket, a white shirt with a pointed collar and a red tie. His half-smile is pleased and perfectly "
            "earnest, the look of a history lover in his element."},
  {1084, 6, "A man in his thirties with tanned skin, grey eyes and tousled dark grey hair parted in the middle and "
            "falling over his ears, light stubble along his jaw and chin. His brows sit easy and his lips are just "
            "parted in a relaxed, half-amused look. He wears a plain dark grey suit jacket with notched lapels, a "
            "white shirt with a pointed collar and a red tie with a pattern of dark diamond checks. A little "
            "rumpled and never quite clean-shaven, he looks laid-back and good-humoured."},
  {1085, 6, "A slight man with pale skin and a huge, round dark grey afro that dwarfs the rest of him. Small round "
            "copper wire-rimmed glasses sit low on his nose over grey eyes, and he smiles widely with one large "
            "front tooth poking out like a cheerful rabbit's. He wears a mustard-yellow V-neck sweater over a green "
            "shirt with fine darker pinstripes and a tall, upturned collar, and holds a large brown wooden set "
            "square, its edges marked with measuring lines, propped over his shoulder. He looks delighted with "
            "himself, holding the big ruler as proudly as a prize."},
  {1086, 6, "A hard-faced police officer with tanned skin and short dark hair, his navy peaked cap pulled low so "
            "its glossy black peak throws one eye into shadow. Its front bears a gold badge: a star in a wreath of "
            "laurel leaves on a dark circle. His visible eye narrows sidelong, his jaw set and his mouth tight. He "
            "wears a navy uniform jacket with silver shoulder buttons, a white shirt and dark navy tie, a gold "
            "badge on his chest and a grey radio microphone clipped at his left shoulder, its coiled cord hanging "
            "down. Tough and wary, he watches from under the peak with a beat cop's grim gravity."},
  {1087, 6, "An old man with tanned, deeply wrinkled skin and grey eyes, his long blue-grey hair combed back from a "
            "receding hairline and tied in a bushy ponytail at the back of his head. Thick blue-grey brows and a "
            "full, shaggy beard and moustache frame a mouth set in a firm, unsmiling line. He wears a white jacket "
            "with a stand collar and round brass buttons, cut like a cook's coat. Weathered and gruff, he has the "
            "stubborn dignity of a man who has run the same kitchen for decades."},
  {1181, 6, "A heavyset older man with fair skin, grey hair combed back from his forehead and over his ears, a "
            "round face with a soft double chin and a bushy grey moustache, and small round wire-rimmed glasses "
            "with red tips on the earpieces. His eyes are closed in contentment and his mouth is open in a pleased, "
            "self-satisfied smile. He wears a dark grey suit jacket over a beige knitted V-neck sweater vest with "
            "ribbed edges, a white shirt with a pointed collar and a red tie. Round and grandfatherly, he looks "
            "thoroughly pleased with himself."},
  {1581, 6, "A young woman with fair skin and a chin-length, wavy light-brown bob with side-swept bangs, its ends "
            "flicking out. Her brown eyes look out level and steady, and her soft pink lips rest in a faint, "
            "composed smile. A small pearl stud glints in one ear. She wears a dusty rose suit jacket with notched "
            "lapels and a flap pocket, over a white blouse with a high stand collar and small round buttons down "
            "the front. Crisp and capable, she looks like a professional who keeps things neat and gets on with it."},
  {1582, 6, "A poised young woman with brown hair swept to one side in a long fringe and pinned up into a bun at "
            "the back, brown eyes glancing out from behind bold red oval glasses, her pink lips parted in a small, "
            "knowing smile. Pale pearls lie at the base of her throat. Her white jacket stands open, and under it a "
            "lilac top with a low, straight neckline leaves her collarbones and the top of her chest bare, the "
            "start of her cleavage showing above its edge. Polished and a little daring, she wears the low neckline "
            "under the sharp jacket with cool ease."},
  {1583, 6, "A woman with a bright, sunny, retro charm, her shoulder-length brown hair flipped out at the ends and "
            "held back by a yellow hairband, with side-swept bangs. Her brown eyes glance sideways and her pink "
            "lips curve in a warm, easy smile. She wears an orange suit jacket with notched lapels and round "
            "buttons over a white top, with a pale yellow silk scarf tied loosely at her throat, its ends "
            "fluttering to one side. Cheerful and outgoing, she looks like a woman stepped out of a sixties "
            "magazine."},
  {1586, 6, "A woman with fair skin and long, wavy black hair swept back from her forehead and gathered loosely "
            "behind her, a few strands curling down by her face. Thin metal-framed glasses sit low on her nose, and "
            "her green eyes peer at you over them under lowered lids, her peach lips curved in a sly, knowing "
            "smile. Her figure-hugging white top is cut in a Chinese style, with a high mandarin collar and a "
            "diagonal opening piped in green, and it clings to her full bust. A thin rigid gold hoop rests loosely "
            "around her neck. Quietly sultry, she looks as if she already knows your secrets."},
};
const Pose kPoses[] = {
  {1, 0, 'A', "His head tilts to one side and turns slightly away, his visible eye looking out at you from under "
    "the fringe, cool and detached."},
  {2, 1, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a cool, level look."},
  {2, 1, 'B', "She faces you more squarely, eyes wide and lips just parted, as if caught off guard."},
  {2, 2, 'A', "Her head tips to one side, chin lowered, her eyes turned up to you with a cool, measuring look."},
  {2, 2, 'B', "She faces you straight on, eyes wide and lips just parted, as if caught off guard."},
  {2, 5, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a calm, appraising look."},
  {2, 5, 'B', "She faces you more squarely, eyes wide and lips just parted, as if surprised by something you said."},
  {2, 6, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a cool, measuring look."},
  {2, 6, 'B', "She faces you more squarely, eyes wide and lips just parted, as if caught off guard."},
  {2, 51, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a cool, steady look."},
  {2, 51, 'B', "She faces you more squarely, eyes wide and lips just parted, as if startled."},
  {2, 52, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a cool, steady look."},
  {2, 52, 'B', "She faces you more squarely, eyes wide and lips just parted, as if startled mid-thought."},
  {2, 102, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a calm, appraising look."},
  {2, 102, 'B', "She faces you more squarely, eyes wide and lips just parted, as if caught by surprise."},
  {2, 106, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a composed, faintly sceptical "
    "look."},
  {2, 154, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a calm, appraising look."},
  {2, 154, 'B', "She faces you more squarely, eyes wide and lips just parted, as if caught off guard."},
  {2, 155, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a calm, appraising look."},
  {2, 155, 'B', "She faces you more squarely, eyes wide and lips just parted, as if startled."},
  {2, 156, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a calm, faintly amused look."},
  {2, 156, 'B', "She faces you more squarely, eyes wide and lips just parted, as if caught off guard."},
  {2, 157, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a soft, self-possessed look."},
  {2, 159, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a calm, attentive look."},
  {2, 159, 'B', "She faces you more squarely, eyes wide and lips just parted, as if caught off guard."},
  {2, 201, 'A', "Her head tips to one side, chin lowered, eyes turned up to you with a cool, steady look."},
  {2, 201, 'B', "She faces you more squarely, eyes wide and lips just parted, as if startled."},
  {3, 1, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 1, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 1, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 1, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 2, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 2, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 2, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 2, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 5, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 5, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 5, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 5, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 6, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 6, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 6, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 6, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 51, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 51, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 51, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 51, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 52, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 52, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 52, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 52, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm, the sword hilt "
    "upright behind him."},
  {3, 102, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 102, 'B', "He ducks his head and tilts it, one eye squeezed shut and brow knotted, teeth bared in a wince."},
  {3, 102, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 102, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 154, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 154, 'B', "He ducks his head and tilts it, one eye squeezed shut and brow knotted, teeth bared in a wince."},
  {3, 154, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 154, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 155, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 155, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 155, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 155, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 202, 'A', "His head tilts a little to one side, eyes sliding off sideways and lips parted as if about to chip "
    "in."},
  {3, 202, 'B', "He ducks his head under the cap's brim, one eye squeezed shut and teeth bared in a wince."},
  {3, 202, 'C', "He tips his head back, chin up, with a broad toothy grin, plainly pleased with himself."},
  {3, 202, 'D', "He leans in sideways and jerks his head back, eyes wide and teeth clenched in alarm."},
  {3, 901, 'A', "His head tilts to one side, tired eyes sliding off sideways, lips parted as if he has run out of "
    "things to say."},
  {3, 901, 'C', "He tips his head back with a broad toothy grin that the hollows under his eyes make look forced."},
  {4, 1, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 1, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 2, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 2, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 5, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 5, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 6, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 6, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 51, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 51, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 52, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 52, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 102, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 102, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 154, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 154, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 155, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 155, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {4, 159, 'A', "His body turns three-quarters away and his head tilts, eyes cutting sideways at you with a faint, "
    "confident half-smile."},
  {4, 159, 'B', "He faces you more squarely, head upright, eyes wide and lips just parted, listening closely."},
  {5, 1, 'A', "Her body turns three-quarters away and her head dips, her one visible eye glancing back at you over "
    "her shoulder, lips just parted."},
  {5, 1, 'B', "She faces you squarely, head upright, her gaze level and steady, lips closed in a cool, unsmiling "
    "line."},
  {5, 2, 'A', "Her body turns three-quarters away and her head dips, her one visible eye glancing back at you over "
    "her shoulder, lips just parted."},
  {5, 2, 'B', "She faces you squarely, head upright, her gaze level and steady, lips closed in a cool, unsmiling "
    "line."},
  {5, 5, 'A', "Her body turns three-quarters away and her head dips, her one visible eye glancing back at you over "
    "her shoulder, lips just parted."},
  {5, 5, 'B', "She faces you squarely, head upright, her gaze level and steady, lips closed in a cool, unsmiling "
    "line."},
  {5, 6, 'A', "She turns three-quarters away, head tipped down, her eye sliding sideways past you with a reserved, "
    "faintly wary look."},
  {5, 6, 'B', "She faces you squarely, chin level, her gaze steady and direct, lips set in calm command."},
  {5, 51, 'A', "She turns three-quarters away, head tipped down, glancing sideways past you, reserved and "
    "unreadable."},
  {5, 51, 'B', "She faces you squarely, chin level, regarding you with a steady, evaluating gaze."},
  {5, 52, 'A', "She turns three-quarters away, head tipped down, eyeing you sideways with a cool, guarded look."},
  {5, 52, 'B', "She faces you squarely, brows drawn slightly together, her gaze firm and resolute."},
  {5, 102, 'A', "She turns three-quarters away, head tipped down, glancing sideways past you with quiet reserve."},
  {5, 102, 'B', "She faces you squarely, chin level, meeting your eyes with a calm, steady look."},
  {5, 154, 'A', "She turns three-quarters away, head tipped down, glancing sideways with a mild, unhurried look."},
  {5, 155, 'A', "She turns three-quarters away, head tipped down, glancing sideways with a calm, reserved look."},
  {5, 156, 'A', "She turns three-quarters away, head tipped down, glancing sideways with a quiet, composed look."},
  {5, 157, 'A', "She turns three-quarters away, head tipped down, glancing sideways with a poised, faintly distant "
    "look."},
  {5, 159, 'A', "She turns three-quarters away, head tipped down, glancing sideways with a calm, attentive look."},
  {6, 1, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, hesitant curiosity."},
  {6, 1, 'B', "She faces you with wide, startled eyes and lips parted, one hand closed in a loose fist at her "
    "chest."},
  {6, 2, 'A', "Her head tilts a little to one side, arms down, looking at you with quiet, hesitant interest."},
  {6, 2, 'B', "She faces you with wide, startled eyes and lips parted, one hand closed in a loose fist at her "
    "chest."},
  {6, 5, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, tentative curiosity."},
  {6, 5, 'B', "She faces you with wide, startled eyes and lips parted, one hand closed in a loose fist at her "
    "chest."},
  {6, 6, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, hesitant curiosity."},
  {6, 6, 'B', "She faces you with wide, startled eyes and lips parted, one hand raised to her chest beside the "
    "collar's ribbon."},
  {6, 52, 'A', "Her head tilts a little to one side, arms down, looking at you with quiet, measured attention."},
  {6, 52, 'B', "She faces you with wide, startled eyes and lips parted, one gloved hand closed in a loose fist at "
    "her chest."},
  {6, 102, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, hesitant curiosity."},
  {6, 102, 'B', "She faces you with wide, startled eyes and lips parted, one hand closed in a loose fist at her "
    "chest."},
  {6, 154, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, hesitant curiosity."},
  {6, 154, 'B', "She faces you with wide, startled eyes and lips parted, one hand closed in a loose fist at her "
    "chest, holding the towel."},
  {6, 155, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, hesitant curiosity."},
  {6, 155, 'B', "She faces you with wide, startled eyes and lips parted, one hand closed in a loose fist at her "
    "chest."},
  {6, 156, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, hesitant curiosity."},
  {6, 156, 'B', "She faces you with wide, startled eyes and lips parted, one hand closed in a loose fist at her "
    "chest."},
  {6, 157, 'A', "Her head tilts a little to one side, arms down, looking at you with mild, hesitant curiosity."},
  {6, 901, 'A', "Her head tilts a little to one side, arms down at her sides."},
  {7, 2, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 2, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {7, 6, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 6, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {7, 52, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 52, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {7, 155, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 155, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {7, 156, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 156, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {7, 157, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 201, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 201, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {7, 202, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 202, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {7, 203, 'B', "She faces you straight on, one eye squeezed shut and the other open and steady, enduring the pain "
    "without complaint."},
  {7, 204, 'A', "She turns a little to one side, head slightly tilted, regarding you with a level, unblinking gaze."},
  {7, 204, 'B', "She faces you straight on, eyes wide and steady, her expression blank and attentive."},
  {8, 1, 'A', "His head tilts to one side as he faces you, looking up with a guarded, unsmiling calm."},
  {8, 1, 'B', "His head is bowed and turned aside, brows knit, eyeing you warily from under his fringe."},
  {8, 2, 'A', "His head tilts to one side as he faces you, looking up with a guarded, unsmiling calm."},
  {8, 2, 'B', "His head is bowed and turned aside, brows knit, eyeing you warily from under his fringe."},
  {8, 5, 'A', "His head tilts to one side as he faces you, looking up with a guarded, unsmiling calm."},
  {8, 5, 'B', "His head is bowed and turned aside, brows knit, eyeing you warily from under his fringe."},
  {8, 6, 'A', "His head tilts to one side as he faces you, looking up with a guarded, unsmiling calm."},
  {8, 6, 'B', "His head is bowed and turned aside, chin sunk into the collar, brows knit, eyeing you warily."},
  {8, 52, 'A', "His head tilts to one side as he faces you, looking up with a guarded, unsmiling calm."},
  {8, 52, 'B', "His head is bowed and turned aside, brows knit, eyeing you warily from under his fringe."},
  {8, 159, 'A', "His head tilts to one side as he faces you, looking up with a guarded, unsmiling calm."},
  {8, 159, 'B', "His head is bowed and turned aside, brows knit, eyeing you warily from under his fringe."},
  {9, 6, 'A', "He sits tall with his head raised and turned aside, ears pricked, mouth open and tongue lolling in a "
    "cheerful pant."},
  {9, 6, 'B', "His head is lowered and his ears fold back, brows lifted and mouth just open in an uneasy, worried "
    "look."},
  {9, 6, 'C', "He hunches forward with his head low and ears up, brows drawn down and teeth bared in a snarl."},
  {9, 6, 'D', "He throws his head back, nose pointed skyward and eyes shut, mouth wide open as if in a howl."},
  {9, 52, 'A', "He sits tall with his head raised and turned aside, ears pricked, mouth open and tongue lolling in "
    "a cheerful pant."},
  {9, 52, 'B', "His head is lowered and his ears fold back, brows lifted and mouth just open in an uneasy, worried "
    "look."},
  {9, 52, 'C', "He hunches forward with his head low and ears up, brows drawn down and teeth bared in a snarl."},
  {9, 52, 'D', "He throws his head back, nose pointed skyward and eyes shut, mouth wide open as if in a howl."},
  {9, 201, 'A', "He sits tall with his head turned to the side, ears pricked, mouth open and tongue out in a happy "
    "pant."},
  {9, 201, 'B', "He lowers his head with his ears folded back and his brows knitted, mouth just open, looking sorry "
    "and downcast."},
  {9, 201, 'C', "He hunches forward with his ears up and his brows drawn down, lips curled back from bared teeth in "
    "a growl."},
  {9, 201, 'D', "He throws his head back, nose to the sky and eyes squeezed shut, mouth open wide as if barking for "
    "joy."},
  {10, 6, 'A', "He leans forward with his shoulders hunched, eyes sliding sideways from under the beanie in a "
    "guarded glare."},
  {10, 6, 'B', "He straightens and turns his head a little aside, eyes wide and mouth closed, caught off guard for "
    "once."},
  {10, 52, 'A', "He leans forward with his shoulders hunched, eyes sliding sideways from under the beanie in a "
    "guarded glare."},
  {10, 52, 'B', "He straightens and turns his head a little aside, eyes wide and mouth closed, caught off guard for "
    "once."},
  {10, 159, 'A', "He leans forward with his shoulders hunched, eyes sliding sideways from under the beanie in a "
    "guarded glare."},
  {11, 52, 'A', "Her visor is folded up into a crown and her face shows, head tilted a little, a soft, steady gaze."},
  {11, 52, 'B', "The butterfly visor is folded down over her face, red wings in gold lattice hiding everything "
    "above her chin."},
  {11, 52, 'C', "The lowered visor stays shut over her face, only her jaw and smooth dark neck showing, blank and "
    "unreadable."},
  {11, 201, 'A', "Her visor is folded up into a crown and her face shows, head tilted a little, a soft, steady "
    "gaze."},
  {11, 201, 'B', "The butterfly visor is folded down over her face, red wings in gold lattice hiding everything "
    "above her chin."},
  {11, 201, 'C', "The lowered visor stays shut over her face, only her jaw and smooth dark neck showing, blank and "
    "unreadable."},
  {12, 2, 'A', "Her head turns and tilts a little to one side, her eyes steady on you."},
  {12, 2, 'B', "She faces you straight on with her head level, eyes wide and earnest."},
  {12, 6, 'A', "Her head turns and tilts a little to one side, her eyes steady on you."},
  {12, 6, 'B', "She faces you straight on with her head level, eyes wide and earnest."},
  {12, 52, 'A', "Her head turns and tilts a little to one side, her eyes steady on you."},
  {12, 52, 'B', "She faces you straight on with her head level, eyes wide and earnest."},
  {12, 53, 'A', "Her head turns and tilts a little to one side, her eyes steady on you."},
  {12, 53, 'B', "She faces you straight on with her head level, eyes wide and earnest."},
  {12, 54, 'A', "Her head turns and tilts a little to one side, her eyes steady on you under the steel visor."},
  {12, 54, 'B', "She faces you straight on with her head level, eyes wide and earnest beneath the visor."},
  {12, 201, 'A', "Her head turns and tilts a little to one side, her eyes steady on you under the steel visor."},
  {12, 201, 'B', "She faces you straight on with her head level, eyes wide and earnest beneath the visor."},
  {101, 1, 'A', "His head tilts to one side, eyes sliding away from you with a doubtful, sheepish look."},
  {101, 2, 'A', "His head tilts to one side, eyes sliding away from you with a doubtful, sheepish look."},
  {101, 6, 'A', "His head tilts to one side, eyes sliding away from you with a doubtful, sheepish look."},
  {101, 158, 'A', "His head tilts to one side under the visor, eyes sliding away from you with a doubtful, sheepish "
    "look."},
  {102, 1, 'A', "His body angles away and his head tips slightly, eyes cutting back to you with a smug, sidelong "
    "look."},
  {102, 2, 'A', "His body angles away and his head tips slightly, eyes cutting back to you with a smug, sidelong "
    "look."},
  {103, 6, 'A', "He leans forward, stooped toward you, holding the pipe out by its bowl in his right hand."},
  {104, 6, 'A', "She stands slightly hunched, facing you, her head drawn down a little into her shoulders."},
  {105, 101, 'A', "His body turns away while his head comes round toward you, eyes cutting sideways with a cocky "
    "half-grin."},
  {105, 151, 'A', "His body turns away while his head comes round toward you, eyes cutting sideways with a cocky "
    "half-grin."},
  {106, 1, 'A', "She faces you with her head tilted a little to one side, eyes wide, about to speak."},
  {106, 2, 'A', "She faces you with her head tilted a little to one side, eyes wide, about to speak."},
  {106, 6, 'A', "She faces you with her head tilted a little to one side, eyes wide, about to speak."},
  {106, 101, 'A', "She faces you with her head tilted a little to one side, eyes wide, about to speak."},
  {107, 6, 'A', "The avatar raises one open hand beside its shoulder, palm up, in an easy, offhand gesture."},
  {108, 1, 'A', "He faces you with his head tilted slightly to one side and a small, gentle smile."},
  {108, 2, 'A', "He faces you with his head tilted slightly to one side and a small, gentle smile."},
  {108, 6, 'A', "He faces you with his head tilted slightly to one side and a small, gentle smile."},
  {109, 1, 'A', "She holds her left hand loosely curled at her chest beside the bow, her head tipped slightly."},
  {109, 2, 'A', "She holds her left hand loosely curled at her chest beside the bow, her head tipped slightly."},
  {109, 6, 'A', "She holds her left hand loosely curled at her chest, her head tipped slightly."},
  {110, 6, 'A', "She grips both satchel straps in her fists in front of her chest, smiling up at you."},
  {111, 6, 'A', "He faces you straight on with his arms at his sides, gazing at you calmly."},
  {112, 1, 'A', "He holds the open fan up in his right hand beside his chin, head tipped, his other arm folded low."},
  {112, 2, 'A', "He holds the open fan up in his right hand beside his chin, head tipped, his other arm folded low."},
  {112, 6, 'A', "He stands with his arms folded low in front of him, head tilted, smiling to himself."},
  {113, 6, 'A', "His shoulders turn away to his right while his head tilts toward you, eyeing you sidelong with a "
    "sceptical, appraising look."},
  {114, 6, 'A', "He holds the cigar near his chin in his ringed right hand, head lifted, scowling up and past you."},
  {114, 901, 'A', "His head turns up and off to his right, gazing into the distance with a stern, troubled frown."},
  {115, 6, 'A', "He faces you with his shoulders square and his head turned slightly, smiling sidelong as if about "
    "to joke."},
  {115, 6, 'P', "His face fills a tilted blue phone screen, the same sidelong half-smile, with 'Mamoru Hayase' "
    "across the top as on an incoming call."},
  {116, 1, 'A', "His body turns to his right and his head droops forward, eyes sliding sideways in a mournful, "
    "sulky look."},
  {116, 2, 'A', "His body turns to his right and his head droops forward, eyes sliding sideways in a mournful, "
    "sulky look."},
  {117, 6, 'A', "His head turns and lifts, his gaze raised up and off to his left, wistful and pained."},
  {201, 6, 'A', "He hunches forward over his crossed, gloved hands, resting his chin on them and leaning toward you "
    "with his staring grin."},
  {202, 6, 'A', "She lifts her gloved left hand beside her shoulder, palm open and up, as if presenting something "
    "to you."},
  {202, 6, 'P', "Her face appears on a blue phone screen in dark silhouette, the caller name reading 'Unknown', as on "
                "an incoming call."},
  {202, 901, 'A', "She lifts her gloved left hand beside her shoulder, palm open and up, as if presenting something "
    "to you."},
  {202, 902, 'A', "She lifts her gloved left hand beside her shoulder, palm open and up, as if presenting something "
    "to you."},
  {202, 903, 'A', "She lifts her gloved left hand beside her shoulder, palm open and up, as if presenting something "
    "to you."},
  {202, 904, 'A', "She lifts her gloved left hand beside her shoulder, palm open and up, as if presenting something "
    "to you."},
  {211, 6, 'A', "He faces straight ahead, head level, with a tired, almost pitying look."},
  {211, 6, 'B', "He draws his head back with his shoulders raised and his hair flaring out, eyes wide and teeth "
    "bared in a grimace of strain."},
  {212, 6, 'A', "His body turns to his left while his head turns back toward you, eyeing you sidelong through the "
    "tinted lenses."},
  {213, 6, 'A', "She stands turned slightly, her head tilted to one side, regarding you with a cool, empty stare."},
  {213, 201, 'A', "She stands turned slightly, head tilted to one side, gazing past you with tired, half-closed "
    "eyes."},
  {221, 2, 'A', "He stands turned slightly, head tilted to one side, smiling at you with relaxed, knowing charm."},
  {221, 154, 'A', "He stands turned slightly, head tilted to one side, smiling at you with relaxed, knowing charm."},
  {221, 155, 'A', "He stands turned slightly, head tilted to one side, smiling at you with relaxed, knowing charm."},
  {222, 6, 'A', "He faces you with his head tilted slightly to his left, eyes glancing aside with a mild, patient "
    "look."},
  {222, 6, 'B', "He tips his head back with his eyes shut and chin raised, brows drawn up as if savouring his own "
    "words."},
  {222, 6, 'P', "His face fills a tilted phone screen in sepia tones, looking straight out, with 'Shuji Ikutsuki' "
    "across the top as on an incoming call."},
  {223, 1, 'A', "Her body turns away to her right and she looks back at you over her shoulder, lips parted to "
    "speak."},
  {223, 2, 'A', "Her body turns away to her right and she looks back at you over her shoulder, lips parted to "
    "speak."},
  {223, 6, 'A', "Her body turns away to her right and she looks back at you over her shoulder, lips parted to "
    "speak."},
  {224, 6, 'A', "He faces you with his head turned slightly to his right, his single eye fixing you with a cold, "
    "sidelong glare."},
  {252, 1, 'A', "He stands turned slightly, his head tilted to one side, watching you with a guarded, level gaze."},
  {253, 1, 'A', "She faces you with her head tilted slightly to her left, meeting your eyes with quiet poise."},
  {254, 5, 'A', "She faces you with her shoulders square and her head level, holding still and composed as if for a "
    "photograph."},
  {1081, 6, 'A', "He rubs the side of his neck with his right hand, head tilted, looking uneasy and unsure."},
  {1082, 6, 'A', "His body turns to his left while his head tilts toward you, regarding you with a weary, resigned "
    "look."},
  {1083, 6, 'A', "His body turns to his left while his head turns back toward you, smiling with quiet, satisfied "
    "enthusiasm."},
  {1084, 6, 'A', "His body turns to his left while his head turns back toward you, glancing over with easy "
    "interest."},
  {1085, 6, 'A', "He rests the set square on his shoulder, gripping it in his right hand, and grins off to the "
    "side."},
  {1086, 6, 'A', "His body turns to his left, the cap's peak shading one eye as he eyes you suspiciously from under "
    "it."},
  {1087, 6, 'A', "His body turns to his left while he lifts his head and looks off to the right with a sceptical, "
    "sidelong squint."},
  {1181, 6, 'A', "His body turns to his left and his head lifts, chin raised, as if savouring his own remarks."},
  {1581, 6, 'A', "She faces you with her head tilted slightly to her right, giving you a calm, attentive look."},
  {1582, 6, 'A', "She faces you with her head tilted slightly to her right, eyeing you with cool, amused interest."},
  {1583, 6, 'A', "Her arms are folded at her waist and her head tilts to her right, smiling at you with friendly "
    "confidence."},
  {1586, 6, 'A', "She faces you with her head tilted to her right, looking over the top of her glasses with a "
    "teasing smile."},
};
