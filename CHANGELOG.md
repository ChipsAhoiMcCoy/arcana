# Changelog

## Unreleased

### Menus
- Restaurants and other order lists (Hagakure, Wilduck and the like) say each dish's price and, with the list's heading, how much money you have ("Hagakure Ramen. What should I order...? You have 360 yen.", "Pork ramen, 900 yen, 1 of 1"). The screen showed both; neither was said.
- Spending all your money is said too ("Spent 110 yen" with 110 yen in your wallet): a purchase that left 0 yen was silent.
- Be Blue V's treatment (a teammate relearns a forgotten skill) works: the list of forgotten skills was silent and took no keys, so the 3000 yen paid left you stuck. Each skill is read with its cost and what it does, then the slots to choose the skill it replaces, and the swap is said ("Learned Garu, in place of Pulinpa").
- A member's Stats page: RT and LT now jump between its sections, as on every Persona page. They opened the game's Persona status (silently: the page already reads it) and Theurgy list (only once someone knew one). The page gains a Theurgy section with each Theurgy the member knows, its effect, and what fills their gauge. The keyboard's X (Persona status) now says "Persona status" as it opens and "Stats" as it closes.
- "What other players did today" (N / View in town) closes with Escape, C and B (Circle) as well as N / View: the cancel often did nothing before.
- Its activities are grouped under their kind: "Daily life, 74 percent" is said as you enter the group, and each activity under it is counted within it ("2 of 5"), as the Shadow analysis page is.

- At a low frame rate (a slow computer, or a busy one) the camp menu could ignore the arrow keys, and other menus could step their cursor twice: the mod ran several times in one of the game's frames and miscounted them. It now runs once a frame.
- Selling (and buying in the shops that ask how many outside Aohige Pharmacy): "How many?" now says the total as you change the count ("2, 360 yen"), as the screen shows it. Only the pharmacy's purchases said it before.
- The bulletin board in Fountain Square (Paulownia Mall) opens the Missing Persons list: it is now read as the camp's is (each case with its number, name, status and profile; F1 for the keys). It was silent, and until you found C to close it nothing else in the field answered.
- The police station's Sell Item: Q and E now say which category is up ("Sell Item, Armor, No items"), in the game's words; two empty categories in a row were silent before. A purchase or a sale no longer says "Shop" again before the next prompt.
- After a fusion accident (the Velvet Room's fusion goes wrong and makes another Persona), the new Persona's page is read ("Chi You, Tower, level 86", then its stats, skills and affinities, Space to go on): it was silent. When its Social Link then levels it up, "Level up!" and the new level are said from the top of the page.
- The calendar in your dorm room (check it on the wall) is read as the camp's Calendar is: each day with its weekday, plans, holidays and moon, moving by day, week and month, and the part-time jobs. It was silent before.

### Field
- A skill card is said as one when you get it ("Got Maragi skill card"), from a Tartarus chest, an item notice or a battle's results: it was said as its skill alone ("Got Maragi"), where the screen shows a card.
- The route sound when you select a point (straight, round, or unreachable) no longer calls Tartarus' stairs, teleporters and Gatekeepers unreachable from afar: their trigger floats above the floor, and the walk went there all along.
- A Tartarus floor lists its ways on (stairs, teleporter, doors) and its Gatekeeper wherever on the floor they are, past the points of interest range: after the 5F Gatekeeper the list said "No Exits" with the stairs 68 meters off.
- Walking to a breakable object in Tartarus stops as soon as your strike would break it, turned to face it: the strike-reach ring sounds, and Ctrl breaks it. The walk used to head for its middle, and where they stand in a ring the others blocked you and it said "Stuck, stopping".
- Strike assist also aims at breakable objects: with no Shadow in reach, a swing turns you to the nearest breakable object your strike would reach on any side, and the ring sounds for it from any side, as for a Shadow.
- Where am I (Slash) no longer says an objective the game has stopped showing: "Return to the dorm" from your first school day was still said days later.
- "Shift available" is said after a 1 More once the wheel shows Shift: the first 1 More of a battle used to say only "1 More!", as the Shift button was still sliding in.
- The party key (Shift+Apostrophe) ends with the navigator outside the party and her SP ("Fuuka, navigator, SP 248 of 299"), which pays for her support in Tartarus (Jamming, Sylphid Aura); the game shows it beside her menu.
- After the 1/31 scene with Jin, "Event: Jin" no longer stays in the list: the spot left there only turns you back ("There's no time to look back."). Only the spot that starts a story scene is listed as its event.
- The desk in your room is listed as "Desk, Computer": the online game (Innocent Sin Online) is played at it, and only checking it told you so.
- Walk and use (Shift+Period) turns you to the thing once you stand still, then presses: arriving on someone's prompt while still sliding (Elizabeth in the back alley), you could end up facing away, the prompt gone and the press lost.
- In the dorm (and wherever floors are stacked) a floor no longer lists the stairs from the floor below that arrive on it: on 3F the exits are "Hallway 2F" and "Hallway 4F", not also "Hallway 3F". During the Dark Hour outside Tartarus (the 4/9 dorm escape, the full-moon operations' buildings) the list keeps to your floor too: the dorm's lounge listed every floor's rooms ("Your Room, 5 meters").
- 4/9, the dorm escape: the 2F hallway no longer lists "Head Upstairs", a spot at the stairs down that does nothing when checked (the way up is "Hallway 3F"). The same goes for a monorail "Vending Machine" that does nothing.
- 5/9: the way from the overhead bridge onto the monorail is listed under Exits as "Into the monorail", at any distance (it is 200 meters up the bridge). The bridge's other spots, which only turn the party back, were listed instead as plain "Event".
- A reward of yen (one of Elizabeth's requests) is said once: "Got 30000 yen" came twice, from the notice and again as the money arrived.
- The July hotel's third floor: each room's mirror says whether it shows your reflection ("Large Mirror, shows no reflection"), as a sighted player sees on walking in; the defective mirror is the one with none. Before, the only way to find it was to break each one in turn.
- A missing person in Tartarus is listed under People wherever they are on the floor ("Missing Person, Ayako Yoshimoto, 120 meters, south-east"), as the floor's objective asks you to find them. Past the list's range they were not listed at all.
- In Tartarus the "close" line names a Shadow that is not an ordinary one, as the list does: "The Reaper close, facing you", "Rare Shadow close, back turned". The Reaper was "Shadow close", so the line that came right before it caught you did not say what it was.
- A Rare Shadow's chase is told: "Rare Shadow fleeing" as it notices you and runs, and "Rare Shadow got away" when it vanishes (after about 15 seconds, or sooner once it loses you). Both were silent, and its growl rose as if it were hunting you while it ran away.
- Where am I (Slash) after loading another save no longer says the last game's objective: it says the new one's once it shows (or that none is shown yet).
- Where am I (Slash) says the moon as the date in the corner shows it: "full moon" on a full moon night, else the days to the next one ("full moon in 29 days", the game's LIMIT countdown), with the quarters and the new moon as the calendar marks them.
- The August full moon's underground base: below about 25 meters the mod lost track of you (no points of interest, no auto-walk, no sonar) on the way down to the Shadow. It took you for one of the game's spare field characters, which it parks under the map; it now tells them apart by where they are parked, not by depth.
- In that base the number on the place banner is a depth, and is said as one: "Underground, 33 meters" (it was "floor 33"; the game shows 33M, and its exits are named "17m Underground").
- A full moon's boss can be found: the spot that starts the fight (Fuuka's "Are you ready?") is listed under Events as "Large Shadow". On 11/3 the Moonlight Bridge's was 13 meters up the bridge with nothing listed but the party; the same goes for the monorail, Fuuka's rescue in Tartarus, the July hotel and the August base. Where the way to the boss is a named door or exit (9/5's Club Escapade, 10/4's Iwatodai Station), it says "Large Shadow" after its name and is listed under Events as well.
- Walking to a point and using it (Shift+Period) presses Space once the prompt has finished appearing and you have stopped: at a low frame rate the press came too early and the game ignored it (the July hotel's mirror).
- Where the game marks the objective on the minimap with a "!" (the faculty office on your first school day), that place is said with "objective" after its name ("Faculty Office, objective, 28 meters, 9 o'clock") and is listed under Events too (key 6), so it can be found without stepping through every door.
- The July full moon's hotel: its staircases are listed under Exits by the floor they lead to ("Stairs to floor 3"), and the auto-walk takes them. Before, they were left out, so the way up to the Shadow on the third floor could not be found. The floor you are on is said with the place ("Hotel Hallway, floor 2"), as the game's banner shows it. Only the stairs on your floor are listed, and the things you check on its ground floor (the information panel, the waiting booths, the reception desk, the entrance) are Objects, not Exits.
- On a Sunday or a holiday the time of day is "Daytime", as the game's date shows it (Slash, the day and time changes): it was called "Afternoon".

### Battle
- An enemy's second action in a turn is named as theirs: Elizabeth's Slash Attack after her Inferno was said as "Makoto: Slash Attack", taken for a counter of the one she hit. Only a passive skill (a Counter) is now said under the name of the one it belongs to.
- The monorail battle's countdown says "Time's up" when it runs out. After "10 seconds left" nothing more was said until the game over.
- After escaping (Tactics, Escape) the results page is headed "Escaped", and "The enemies fled" when they ran; both were called "Victory".
- Analyze in battle: F1 (both triggers + Menu) also names Full Analysis (N, the pad's View) once the page shows it.
- "1 More!" is said when a weakness hit defeats its target too (the game shows its 1 MORE and you act again); it was only said after a Down.
- Giving a new skill up when all eight slots are full ("Forget Repel Wind?", yes) no longer says "Learned Repel Wind".
- Learning a skill after a battle with all eight slots full: F1 now says how to give the new skill up (up from the top row to the new skill, then Space or A, which asks "Forget ...?"). It said Escape goes back, and Escape does nothing there.
- A skill or attack that hits the same unit several times no longer reads every hit: once the action is over, each unit it hit gets one line with what it came to ("Makoto 147 damage in all"; a single hit as before, "Makoto 26 damage"). Strength's Mobius Rondo, six hits on each of four members, was 24 lines in a row; it is now four.

### Achievements
- New: an achievement is said as it unlocks, with its name and description ("Achievement unlocked: SEES the Day. Joined the Specialized Extracurricular Execution Squad."). Steam shows unlocks only in its overlay, which a screen reader does not read. One you had unlocked before is not said again.

### Dialogue
- A choice whose first answer is only "......" (Takaya's "Now... kill me." on 1/31) is said as "ellipsis, 1 of 2" as it opens, as moving to it already said: it opened as "...... 1 of 2", which a screen reader reads as nothing or as dots.
- Confirming a line before its voice or reading has ended no longer says "Next" (or plays the end sound) as the window closes: the cue is for a line that waits for you, and you have already gone on.

### Audio description
- Battle scenes are described too: a full moon boss's entrance and fall, and the turns of its fight the camera stops for (the monorail's Shadow speeding the train up, Fuuka finding her power in her first battle), the same way as story scenes (the same settings, the narrator or your screen reader, a box that holds the scene until you go on). After a line the battle shows with its scene, the description comes once the line is said, and one press goes on from both. So far the first night on the dorm roof (4/9), the monorail (5/9), Fuuka's rescue (6/12, its king and queen falling in either order), the July hotel's Hierophant and Lovers, the August base's tank (its entrance, the tank splitting in two, both falls) the September Hermit, October's Fortune and Strength at Iwatodai Station (their entrance, Strength hiding Fortune, each falling), November's Strega on the Moonlight Bridge (Takaya and Jin, each falling, in either order) and the Hanged Man (its entrance, its statues breaking and rising again, its fall), the last night's Jin and Takaya at the top of Tartarus (each entrance and fall, and Takaya's shot to his own temple), November's Chidori in Tartarus (her entrance), the Nyx Avatar's entrance, its sword sweep, its wings turning red, its flight and its fall, the last battle against Nyx (its entrance, your friends' strength reaching you, and the Great Seal), Elizabeth's battle in Tartarus (her entrance and fall), the August 14 night on the bridge (Shinjiro and Takaya against the Shadow), and the Ancient Castle in Tartarus where Yukari finds new strength (its entrance, her memories, the moment she loads the cartridge into her Evoker, and the end of the fight). A member's first summon in battle is described too (Akihiko's, Mitsuru's, Aigis's, Ken's, Koromaru's and Shinjiro's).
- A 3D scene's first description now waits for the scene to open: its music starts and its fade in from black ends before the description is said (and before its box pauses the scene). Before, most first descriptions came on the scene's first frame, so you heard them over the last scene's music, and the scene's own music only began once you pressed Enter.

### Social stats
- A stat that rises says by how much ("Academics up, 2 points"), and the Stats up screen says how far each stat is from its next rank ("Charm 1 Plain, 1 point to the next rank"), as its gauges show. A single point is no longer "1 points" (here and in "Bond deepened").

### Social Links
- The "Personality" card a dorm hangout ends on (cooking, reading, a film with a member) is read: the member, what fills their Theurgy gauge, and the characteristic they gained with its effect ("Characteristic: Buff Boost. Increases the effects of buffs on self."). It was silent and waited for Space.
- The shrine's fortune ("Who should I think of...?") names each link as the game labels it, then the person, the arcana and the rank, and whether the link is reversed (the fortune can mend it) or ready to rank up: "Track Team, Kazushi Miyamoto, Chariot, rank 5, ready to rank up". Before, only the label was said ("Track Team"), where the game shows the person's portrait.
- A Social Link reaching its maximum is announced as such: "Social Link at max rank, Justice Social Link, Chihiro Fushimi, rank MAX". The card was read before it turned to MAX, so it said "Social Link rank up ... rank 9".
- The people list (the scanner) says "ready to rank up" after a Social Link partner whose next hangout will rank the link up, and so does the prompt as you walk up to them (with "reversed" for a reversed link). In the game this shows only on the town map's cards.
- "Ready to rank up" now follows the game's own rule everywhere it is said (the town map, the Social Link menu and Shift+backslash): a romance uses its own point table, and a link the game holds back (a social stat or the story gating its next hangout) is not called ready.

## 0.6.0

### Languages
- New: the mod speaks the game's 13 languages: English, Japanese, French, Italian, German, Spanish, Brazilian Portuguese, Polish, Turkish, Russian, Korean, Simplified and Traditional Chinese. By default it follows the language Steam runs the game in; Language of the mod (F2, Language) picks another. Menus, hints, places, portraits, the looks of Personas and Shadows and the audio descriptions are all translated, with the game's own names for its people, places and terms. In any language but English the audio descriptions are read by your screen reader: the narrator's recorded voice speaks English only.
- With the game in another language than English: shops, doors and exits in town are told apart by the game's own rows (they were listed as things, and every exit was "Go to"), Tartarus's and the Abyss's blocks get their descriptions, yes-or-no questions in Japanese and Chinese get their keys, Japanese and Chinese text is not broken by spaces at its line breaks, and dates, positions ("2 of 5") and counts are said in each language's own order and plural forms.

### Menus
- New: the contract can be filled in on a controller. A on a name opens an on-screen keyboard of the mod's: the D-pad walks a QWERTY grid read key by key with its place, A types, B erases the last letter (and, with nothing typed, closes the keyboard), Y toggles capitals, X reads the name, and Start saves it. Opening it says the field, what is in it and the key under the cursor; its buttons are read by the hints key (both triggers + Menu), whose layer works on the keyboard too. First letters are capitals by themselves. It plays the game's own menu sounds: the cursor as you move (at an edge the key is said again, with no sound, as in any menu), the confirm sound as a key is typed, the cancel sound on an erase and the page-turn sound on capitals. With capitals on, keys are read as "capital Q", and a capital letter typed into a name (on the keyboard too) is read as "capital M"; a typed space is read as "space". In Big Picture mode and on a Steam Deck, the game would open Steam's controller keyboard instead, which a screen reader does not read: the mod turns that down, so its own keyboard is used everywhere. On the keyboard, the contract is as before.
- Coming back to a menu from something the game handles itself (a shop's quantity, a page, a prompt) on the same row now reads that row again. Going back from a shop's "Is this what you want?" to the quantity and confirming again brought the prompt back in silence; going back from a quantity to the list was silent too.

### Dialogue
- In story scenes, a speaker who goes on is no longer named again when the scene closes and reopens the message window between their lines (Junpei's ghost story named him on each window). A scene's description read between two of their lines does not name them again either (the Mysterious Boy was named again after the lobby's description).
- The log (B) holds the navigator's and the party's remarks while exploring again, such as Mitsuru's warning about a locked treasure chest in Tartarus, and the audio descriptions of scenes. The game's own log leaves them out, and since the log was read from it they were missing (in Tartarus it was empty). They are listed in the order they were said, between the game's lines. An empty log says "None".

### Online features
- The game's online statistics are read, as menus (they need the game's Network Functions on, and a press of N, or View on a controller, as in the game). In town, N opens what other players did today, with the date: each kind of activity (daily life, Social Links, Tartarus) with its share, then the activities the game notes for it; up and down read them, and Tab (RT) jumps to the next kind. On a class question's answers, N opens how other players answered: a row per answer with its percentage, opening on the answer you are on. The title is said as it opens and the first row once the figures arrive. N, C or Escape (View or B) closes either, and closing other players' answers reads the answer you are on again. F1 names the keys.
- A choice list (a class question's answers, any question in a scene) reads the focused answer again when you come back to it from a screen opened over it, such as the log (B).

### Field
- New: walking on the keyboard. The game's movement keys always run (only a controller's stick could walk). Hold Alt to walk, as you hold Shift to dash; Shift still dashes while you hold Alt. Alt never opens the window's hidden system menu, and the mod's keys work while you hold it. The mod's walk to a point of interest keeps its running pace.
- New: Always dash (F2, Exploring, on by default). Outside Tartarus you dash whenever you move, as if Shift (RT) were held; holding Shift (RT) then runs, and Alt still walks. The mod's walk to a point of interest dashes too. In Tartarus and Episode Aigis' dungeons it does nothing, since a dash there widens what the Shadows notice. The game's own rule against dashing in some places still holds.
- The walk to a point of interest got a stress test over the dorm, school, stations, malls, shrine and club, and these fixes:
  - It no longer says "Stuck" from a spot pressed up against furniture. Beside Naganaki Shrine's see-saw, every walk from there failed: the path started on a scrap of walkable ground on the see-saw itself and led back into it. Paths now start from the floor under your feet, also for the door check, the sonar and the points of interest list; standing in the gap round a piece of furniture, the walk first steps out on the open side, and wedged in a corner it can back out the way you came.
  - The Net Cafe at the Iwatodai Strip Mall is reached again: its stairs run over the diner's closed door, which was taken for a door on the way, so the walk said there was no path.
  - Room doors set into a wall are in the points of interest list again, and the walk takes you to them: on the school's ground floor the Printing Room, Science Room, Home Ec Prep Room and the Event Bulletin Board, upstairs the PA Room, Computer Room, Student Council Room and Classroom 2-E (seen from downstairs), and the Storage Room on the school rooftop. The walking path to each ended on the far side of the wall, through a closed classroom door, so they were taken for being behind it. A thing in a wall is now reached from whichever side has no closed door on the way.
  - A shop vendor behind a counter (the School Store) is arrived at as soon as their prompt is up, instead of pushing into the counter and then circling the store.
  - Officer Kurosawa is no longer in the points of interest list or the sonar in Paulownia Mall. He stands inside the police station, behind its wall, and you cannot talk to him there: his shop opens at the Police Station's door, which stays in the list. The walk to him used to circle the plaza for about fifteen seconds and could end up through the back alley's exit. The list now leaves out anyone the game gives no way to talk to. Two more walk fixes came with this. A walk round something it cannot reach only heads for sides it can get to, and says "Stuck" within a few seconds. A walk to a person that passes through an exit stops there, and the place's name tells you where you are.
  - Planning a way between furniture (classroom 2-F's desks, the dorm's lounge) no longer makes the game hitch for up to a fiftieth of a second: the plan is spread over a few frames while you stand.
- The map in Tartarus (M) is read. It is the game's shortcut list, "Where should I go?", and each shortcut appears once you find what it leads to: Go to the Next Floor (the stairs) takes you up from anywhere on the floor, Use the Teleporter opens the terminal's floor list, and Return to Entrance and Enter Monad use the return device and the Monad door. Before you have found any of them, the map says "No shortcuts found yet" with the floor you are on. The mod said nothing on it before.
- New: Relaxed Reaper rate (F2, Exploring, off by default). In Tartarus, you can stay on a floor twice as long before the Reaper comes: about six minutes on a normal floor instead of three, and its quicker returns take twice as long too. Fuuka still warns you shortly before it arrives. Turned on while you are on a floor, the time left there doubles; turned off, it halves back.
- The mod's field sounds (sonar, wall tones, Shadow cues and sight zones) now go quiet whenever the game takes the hero from you: opening a door, checking or picking something up, a camera the game moves by itself. They come back the moment you can move again, so silence means wait.
- The people list now says when the game shows a speech bubble over someone: "something to say" (the students the guides tell you to talk to, in an investigation as on any day), and "overhear" for the ear the game puts over people chatting, whom you listen in on. Once heard they read "already spoken to" and "already heard" (before: "talked to" and "heard", which a screen reader made hard to tell apart from "talk"). A name with nothing after it used to stand for the speech bubble, and the ear was not told apart from it. The game's handwritten word icons are read too: "overhear, a buzz of chatter" over a crowd and "overhear, whispering" over people gossiping.

### Social Links
- Mutatsu's order quiz at Club Escapade (Tower): the bartender asks what a customer ordered by where they stand ("that girl by the entrance"), while the field names the customers by their looks. Each question is now followed by who it means ("That's the Unemotional Woman."), and the people list says where each customer stands, in the bartender's words ("Unemotional Woman (by the entrance)").

### Stability
- Fixed a crash ("Illegal call to StaticFindObject() while collecting garbage!") that could happen while a 3D scene's description held the scene (Description wait), most likely around a scene's end or with Auto on. The game frees its unused memory about every two seconds and lets other work run in the middle of it, and the mod's own work ran there too. The mod now waits until that cleanup is done.

## 0.5.0

### Audio description
- New setting, Faster narrator in 3D scenes (F2, Audio description; off by default): the narrator reads the descriptions of 3D story scenes 25, 50 or 75 percent faster, at the same pitch. The animated movies keep the normal speed, since their descriptions are timed between the lines.
- The descriptions' settings have a category of their own in the mod settings, Audio description, after Dialogue: Movies, 3D scenes, 3D scenes read by, Faster narrator in 3D scenes and Descriptions wait for Enter. The rest of Dialogue and movies is now Dialogue: Voiced dialogue, When a line ends, Read subtitles. The narrator's volume stays under Volume. Saved settings are kept.
- Every 3D story scene's description was rewritten, now that a description pauses the scene until you go on: the main story from the arrival to graduation, every Social Link and the team's Linked Episodes, the group outings and study nights, Elizabeth's requests and outings, Takaya's night meetings, Tartarus's one-time moments and the short field scenes. They speak to you in the second person ("You walk into the lounge"), say where a scene is when its lines don't, and are as full as the moment needs, with fewer, longer descriptions in place of many short ones. Scenes the dialogue already carries are left quiet. The animated movies are unchanged.
- Every 3D scene's description (the main story, Social Links, outings and part-time jobs, requests and Tartarus and field scenes) was checked against the scene itself and corrected where it was wrong: where it takes place (a booth sofa at the bar, not the counter; outside the arcade, not the fountain), who sits or stands where, who arrives and who leaves, what is handed over, and the body language the dialogue only hints at (folded arms, a hand pressed to the chest, looking away).
- "3D scenes" (F2, Audio description) is now on, suppress repeated descriptions, or off. Suppress repeated descriptions reads each description once: one you have heard (gone on from with Enter or Auto, or heard to its end) is not read again when its scene comes back. Who reads them, the narrator's voice or your screen reader, is its own row, "3D scenes read by"; a saved screen-reader choice carries over.
- The scenes that repeat are described again, for a first look: the job shifts at Chagall Café, Be Blue V and the cinema, coffee, meals, karaoke, the arcade and films on your own, studying, school mornings and lessons, the fusion animation, the Velvet Room door and Elizabeth's calls, the dorm's deliveries, and Tartarus's golden hand, chests, clocks, Monad doors and the Reaper. With suppress repeated descriptions on, each is read the first time only.
- A 3D scene's description read by your screen reader now ends with "Next" (or the sound chosen in "When a line ends") once it waits for you, as a message window does; only the narrator's voice gave one before. As with message windows, none is given under Auto, which goes on by itself, and fast-forward skips the descriptions it passes as it skips the dialogue.
- With the game's Auto on, a 3D scene's description no longer starts over someone talking: Auto lets the scene run on through its lines, and a description whose moment came during a line was read over the voice. It now waits until the line ends.
- A 3D scene's description no longer plays a sound as it appears, as a dialogue window doesn't; going on from it still makes the page-turn sound.
- About 30 Social Link scenes never played their descriptions, because the game names the scene after another one: the evening hangouts in the dorm with the team, the films at the cinema with Yukari, Akihiko, Mitsuru, Yuko, Chihiro and others, and two of Koromaru's scenes (the angry dog, and the collar at the shrine). Descriptions are now found by the scene the game plays, whatever it is called.

### Battle
- The box the game slides in during a turn is read: a boss's warnings before a big attack ("is charging up...", "has set its sights!", "is targeting Mitsuru!", "'s glare sharpens!", "is almost done charging up...!"), stat changes and their end ("Attack up!", "Defense reverted!"), what an enemy does instead of attacking ("Supreme Hand is waiting...", "ran away..."), and why a command did nothing ("Insufficient SP!", "No effect!"). Ailments are left to the line that names who took them.
- An enemy that runs away is no longer called defeated.
- A and D change target in Analyze again, as in the game, beside Q and E: since Analyze became a page, the mod had taken them.

### Field
- New: the number keys 1 to 7 each pick one category of points of interest: 1 exits, 2 doors, 3 people, 4 shops, 5 objects, 6 events, 7 Shadows. The first press selects that category's nearest, each press after it the next one out, wrapping round; Shift goes back (as the first press, the farthest). The thing is said straight away, without its category ("No Shadows" when there are none near).
- Comma no longer says a point's category before it ("Objects, Vending Machine, ..."): you hear the thing itself at once.
- With Strike assist on, the strike-reach ring now sounds for a Shadow in reach on any side, not only in front of you: the assist turns you to it as you swing, so a Shadow coming at your back could already be struck, but the ring stayed silent until a swing had turned you round.
- In top-down exploration the wall behind you keeps sounding while you walk: walking away from a wall cut its tone at once, so you lost where it was.
- New: Shadow sight (F2, Exploring, on by default). In Tartarus, each nearby Shadow's sight is a zone on the ground that sizzles from its edge nearest you, heard from where that edge is, for as long as the edge is within the Shadow sight range (10 meters by default, 2 to 16): louder and higher by an even step for every metre nearer, loudest at the edge, so you hear it close in or fall away as you walk. Step over it and the Shadow notices you. The three nearest zones sound at once. It is the game's own test, read from each Shadow: how far and how wide it sees for its mood (an angry Shadow sees farther and only to its front), the wider sight when you dash, which way it faces, and walls, which block its view and cut its zone. While a wall hides you from a Shadow that would otherwise see you, a muffled hum plays. Shadows chasing you, and every Shadow while Fuuka's Jamming hides you, are left out. The sounds are Grim Dark's harmful-ground sounds. Both are in the sound test.
- Characters the game lets you talk to but who have no model of their own in their spot are listed again: the Weak Cat at the Station Outskirts was left off the list and the radar.
- A few named characters the game places without a name of their own are called by their name instead of "Person": Officer Kurosawa outside the Paulownia Mall police station, and Mitsuru, Junpei, Akihiko, the bartender and others on certain days.
- A Social Link partner you have not begun a link with is no longer given away by their arcana: the field and the town map's list of who is where say "Unknown Arcana" until the link is formed (the game's own prompt shows the arcana only then too).

### Menus
- The camp's member lists say who is in your active party: "Yukari, reserve, level 90, ...", "Akihiko, in party", "Fuuka, navigator". This covers Stats and its Tactics, Skill, Item and Equip, and a shop's "For whom?". A list that holds only your party, as early in the year, is read as before.
- New: the mod's keys can be changed. Mod keys, at the end of Controls in the mod settings (F2), now opens a list of every keyboard key the mod adds: Enter (A) on one, then press the key you want. Keys that go back with Shift move with their key and are not listed separately. A key another action already has swaps with it, the game's own keys (moving, Space, Enter, Escape, Backspace, Tab) are refused with the game's buzz, Delete (X) puts one back on its default and the last row resets them all. Your keys are saved in keys.ini beside settings.ini. Escape (B) goes back to the settings rather than closing them. The controller's keys stay as they are.
- The help that names the mod's keys (F1 in the field, the Shift+F1 and F2 reminder, the game's Config screens, the Sonar setting) says each key where you put it. Punctuation keys are named in words ("Period", "Apostrophe") in Shift+F1 and the Mod keys list, where they were the bare character, which screen readers can leave unsaid.
- The mod's settings (F2) now pause the game while you are exploring, as the camp menu does: Shadows, characters and the field's sounds stand still until you close them, so a Shadow in Tartarus can no longer reach you while you change a setting.
- A text in the mail list could be read with a line someone had said to you earlier in the place of its sender (and, opened, with another old line before its message): the game had loaded the text into the memory that conversation used. Only the text's own sender and message are read now.
- Escape now goes back on every step of a menu, including the ones where the game takes the keys itself: the calendar's part-time jobs, a shop's quantity, Theurgy's personality page, an open mail, the area map and others. C, the game's own key, works as before.
- F1 now also knows: the battle's Persona page (Space equips the one shown from a skill list; from Shift or Survey Q and E switch member), a member's Persona status opened from Stats, a level up's skill learning (no Persona switching), the Overstock's stats page, Rush running (Tab or C stops it), an open text (Space replies), a request's info (up and down switch request), the shop's second views and the antique shop's Fuse Equipment, a music row in Config (Space opens the playlist), the title menu (Z plays the credits), the boot notices (any key), the location list (Tab zooms the map), the town map's entrance list (Escape back to the map), a list you cannot cancel, and the fusion animation's controller button. Movies: Tab skips only while paused, so Tab twice from a playing movie. After a fusion's animation, F1 no longer offers its skip.
- A request's info (F on a request) keeps the requests screen up, so its keys are its own rather than the field's.
- F1 gives the right keys on more screens. Analyze names the arrows and Tab's sections besides its target keys. Fixed or completed: the camp menu, the Persona page (F reads a line again), Tactics (F joins or leaves the party), a member's stats, the shop's quantity (left and right change it by ten) and its buy list (back, not leave, when the shop has a top menu), the town map, the Velvet Room's compendium (Space opens the page) and Persona pages (Q and E switch Persona), the Overstock's controller wording and the results' controller wording. A yes or no question in a system window gives its yes and no keys, a dictionary term says Space continues, the system notice that takes any key says so, and learning a skill and the Game Over poem keep their keys when you come back to them.
- Semicolon (triggers + B) on a Social Link in the camp menu, or on its page, describes the picture the menu draws beside it, written from the game's own artwork: each partner, both halves of the old couple, and the team's collage of faces, which grows as members join.

### Mod settings
- Every mod setting now runs from off, or its least, at the left to on, or its most, at the right, so Left turns a setting off or down and Right turns it on or up, as in most menus. On/off rows are Off, On; Wall tones Off, while moving, continuous; Plays the selected point, the category, everything; Voiced dialogue not read, name only, read aloud; When a line ends, Movies and 3D scenes start from Off; Menu animation speed, Trigger delay and the narrator's speed grow from Off. The volumes and ranges already grew to the right. Before, Off was at the right end, as the game's own Config draws its ON and OFF; the game's Config itself is unchanged. Saved settings are kept.

## 0.4.0

### Audio description
- Descriptions in 3D story scenes can wait for you like a message window (Descriptions wait for Enter, on by default): each one pauses the scene, plays the game's message-window sound, is read by the narrator or your screen reader, and waits for Enter, Space or A, which plays the sound a message window makes when you press past a page and goes on. Pressing while the narrator speaks cuts the description short. With Auto on, the box goes on by itself once the description has been said, as the game's own lines do; fast-forward skips descriptions as before. They are also in the log (B). Turn the option off to have them fitted between the lines while the scene plays, as before. The animated movies never wait: their descriptions stay timed between the lines.
- More 3D story scenes are described: April's main story (the hero's arrival, the dorm, meeting the chairman, the boy in striped pyjamas, the first days at school, the first Dark Hour and the awakening on the roof), studying at your desk or in the library, Elizabeth's requests (her calls, the outings around the city and the school, her challenge) and the teachers' requests, the Velvet Room's fusion animations, short field moments (the claw machine, the Velvet Room door, the club, the dorm lounge, Aigis running ahead on the island) and Tartarus's own moments (the golden hand Shadow that runs, chests, the Reaper's arrival, the great clock, the party's first steps inside). Social Links have begun with Yukari's, from the rooftop to the last ranks, and Junpei's (the arcade, the watermelon, the flowers, the shrine, the manga nights and the rooftop garden).
- About 140 descriptions in 3D scenes ran into a moment where the scene stops for a line, and the narrator paused mid-word until you moved on. Every scene's stops are now known exactly, and those descriptions were shortened or moved so each one ends before the scene stops.
- Fast-forwarding a 3D scene is followed as part of the scene instead of as its end: a description is never finished over fast-forward (one in its last second used to play on), the descriptions you speed past are left out, and the rest play as the scene goes on.

### Shops
- Opening a shop says only its name ("Shop"); your money is no longer read with it. The status key still reads it.
- Slash (Where am I) works in a shop: it said "Not in the field". It names the place you walked in from (the shop's own room has no name in the game).
- After choosing Buy Weapon and a member, the list starts at the first weapon instead of repeating "Buy Weapon, for Colton". Any list whose heading is only the choices you just made skips it the same way.

### Mail
- Opening a mail from the list reads its text: the sender and subject, which the list just said, are no longer read again first. The review key still reads it whole.
- Going back from a mail to the list says the mail you were on again.
- Turning down a hangout or an outing in a mail's reply takes you back to the inbox, on that mail, instead of leaving you on the mail you already answered.

### Messages, log and travel
- The log (B) reads each line from the game's own log, so the line you hear is the one whose voice plays when you confirm it. Before, every line could be read one older than the game's, after a voiced page or fast-forwarding.
- "Where should I go?" is said once per trip: pressing M says it, but the list of entrances after you pick a place on the town map (Paulownia Mall's, for one) and M's list again after you back out of the town map do not repeat it.
- A line the game marks as voiced but has no voice for is read at once. After Junpei's arcade hangout, "The Strength of Junpei's Persona, Hermes, was raised by 3." stayed silent until the review key.
- Saving says "Saved" with the slot, and the slot is no longer read again over it, which cut "Saved" off.
- Little pictures in a message are left out unless they sit between words, where they still read as "a key". The Game Parade Newsletter's subject was read "a keya keya key GAMES a keya key".

### Punctuation and unknown entries
- A line that is only punctuation is now said: a page where someone answers "......" reads "Junpei: ellipsis" instead of just the name (screen readers skip a bare ellipsis), and an answer of "..." in a choice list reads "ellipsis, 2 of 3" instead of only its position. Question marks, exclamation marks and dashes on their own are named the same way. A speaker the game hides as "???" is read as "Unknown".
- The compendium names a Persona you have not registered "Unknown" ("Unknown, Magician, level 50"), as the game shows question marks there. Before, the row began with the arcana and nothing where the name goes.

### Persona and Shadow descriptions
- Semicolon (triggers + B) on a Persona or a Shadow describes how it looks: every Persona, the DLC ones included, every Shadow and each of its recoloured siblings, the full-moon bosses and the people you fight, written from the game's own 3D models in the style of the portrait descriptions. In battle it describes the enemy under the cursor (a party member: their Persona); it also works on any Persona status page (a fusion's result, a level up, the camp's Persona list, Shuffle Time), the fusion and search lists, the compendium's registered entries and the registry list, the battle's skill list (the Persona heading it, the one Q and E switched to) and a Persona learning a skill, also while a message covers its page.

### Wall tones
- The wall tones keep playing while a point you chose with Comma, the points of interest list or the right stick is heard alone. They used to fall silent until it ended.
- The Wall tones setting has a third choice, Continuous: the tones play all the time, standing still too. Only while moving (as before, and the default) and Off are the others.
- New setting, Wall tone range (Exploring): how far away a wall starts to sound, 1 to 10 meters, 5 by default. It applies in both camera modes. In top-down exploration the tones used to reach only 3 meters; they now reach the same 5 meters as with the game's camera.
- Wall tones follow your walking more closely: a change in a tone's volume now settles in about 5 ms instead of 15, and the tones are worked out from where you will be a frame later rather than where you were a frame ago: roughly 25 to 45 ms sooner in all.

### Sound timing
- The sonar's beats, the focused thing's beat and the strike ring now keep an even rhythm. Each beat used to start on the game's next frame and the mixer's next 10 ms block, so beats one period apart could land up to a frame and a half apart. Now each one starts at the exact moment it is due.
- Sounds from places (the sonar, a Shadow's snarl, the focused thing) are heard from where you and the camera will be a frame later, as the wall tones are, so they keep their place as you run past or turn the camera.

### Title screen
- The credits that Z (L1) opens from the title menu are announced: "Credits", then "Credits paused" when you pause them, with what to press. Before, they rolled in silence and the title menu took no keys until they ended, so the game seemed to have stopped responding. Enter (A) pauses them; while they are paused, Tab (the Menu button) skips them and Enter resumes them. Backslash reads the names on screen.

### Mod settings
- The Sonar rows and the Sound test's sonar sounds are named by their kind alone ("Exits", "Door") instead of starting each with "Sonar:".
- Every setting's values run in the order of the game's own Config menu: On is to the left of Off, and Off is always at the right end (Audio description, Menu animation speed, Trigger delay and When a line ends included), so Left turns a setting on and Right turns it off, as in the game. Voiced dialogue runs from read aloud to not read. Numbers still grow to the right.
- The settings are regrouped. A new Volume category holds every volume: Master, Sonar, Wall tones, Shadow sounds and Audio description (the wall tone volume was under Exploring, the sonar's under Sonar, the narrator's under Dialogue and movies). Sound keeps Placement and Lower pitch behind you. Rows no longer repeat their category's name: under Sonar, "Plays" and "Range"; under Volume, "Master" and "Sonar". "Controller trigger delay" is now "Trigger delay" and "Read cutscene subtitles" is "Read subtitles". Exploring lists Top-down exploration and the points of interest range first, then the wall tones, then the Shadow options. Saved settings are kept.
- New defaults: the Sonar, Wall tones and Shadow sounds volumes start at 50 percent (they were 80, 100 and 60). Volumes you have already set are kept.
- The Descriptions in menus setting is removed: a skill's, item's, gear's or setting's description is always read after its row, and the details keys read it again.

### Menus
- A menu opened by confirming a row no longer starts by repeating that row's name: Item in the camp lands straight on the first member instead of "Item, Makoto...". A menu opened any other way still says its name, and a title that asks something keeps its question. Likewise, the list a confirm opens does not start with the name just chosen, at any depth: confirming a member in Equip says "Weapon: ..." rather than "Colton, Weapon: ...", and confirming Armor goes straight to the first piece of armor. Backing out into a list you were already in does not repeat its heading either: back from the armor list you hear "Armor: Bulletproof Shirt", not "Colton, Armor: ...".
- New setting, Menu animation speed (Controls and help; off by default): while a menu is up, the game runs 4, 8 or 16 times faster, so its opening slides and transitions finish sooner and the menu takes your keys sooner. At 16 times the camp menu opens in about a twentieth of a second instead of a third, and the Velvet Room's menu in under a fifth of a second instead of two. The game's menu sounds still play. The phone (Mail) slides in and out at the faster speed too (its opening was left at normal speed). The speed is on only while a menu is busy (opening, closing, changing lists, carrying out a choice): a menu waiting for your key runs at normal speed, so the idle lines the game times while you browse (Igor's "Take all the time you need", the shopkeepers') come at their normal pace instead of sixteen times as often. Characters on screen keep their normal speed, so their looping animations and the sounds in them (the hero's cards at the fusion table, which played many times a second) are as in the game. Battles, story scenes and conversations keep their normal speed.

### Battle
- Analyze is a page you move through, like a Persona's status page. It opens on the enemy's name and health. Down goes through its arcana, level, maximum HP and maximum SP, then each affinity on a line of its own ("Fire: weak", "Slash: normal", "Dark: unknown"), then the "Skill and attack type" panel (each skill's description is in the detail lines), then what it drops. Tab and Shift+Tab (the triggers) jump between Affinities, Skill and attack type, and Drops. Changing target (A and D, LB and RB) goes back to the new target's name. What the game still hides is said as unknown, as the screen shows it ("Level unknown", "Unknown" under Skill and attack type). Before, Analyze said only the name, health and level, and the rest waited in the detail lines.
- Analyze no longer gives away a Shadow's level before the game shows it (the screen draws "Lv ??" until then).
- A foe's Light and Dark affinities are named right. A Shadow weak to Light was said to be weak to Dark, and one weak to Dark left that weakness out.
- A physical skill's HP cost is no longer read as damage to the one using it: the skill list already says the price.

### Personas
- A Persona's status page (the camp, fusion results, the Compendium, level ups, in battle) reads all nine affinities, one line each, normal ones too: "Slash: normal", "Fire: weak", as the page's icon row shows them. Before, only weaknesses and resistances were read.
- Persona affinities (the Persona page, fusion and Compendium) are read from the Personas' own table. The mod could read the enemies' table instead, which uses the same numbers for different monsters: Omoikane was said to null Strike and Fire, drain Elec and repel Dark, when it resists Elec and is weak to Dark. Episode Aigis keeps its own copies of the game's tables (skill names and costs, fusion, Persona affinities, names, the minimap, system text); the mod now reads the copy for the story you are playing, the same one the game reads, instead of whichever was loaded last.

### Config
- The Dungeon BGM and Boss Battle BGM playlists move with the arrows again: the mod moved the other playlist's cursor, so the list jumped around and Space could set a track you had not heard.
- Space or Enter on a BGM row opens its playlist. It used to save and leave the page.
- The track a playlist has set is said as "current", and setting one says it again with "current".
- A BGM playlist is named after its row ("Change Battle BGM") and split in two sections, each with its own positions: Modes (Default, Random, Favorited, each said with what it does) and Tracks. Tab and Shift+Tab (RT and LT) jump between them.
- In a playlist, F (X) says "playing" or "stopped", and E (RB), the game's favorite key, says "favorite" or "not a favorite". The track playing and your favorites are part of each row, and Favorited says "no favorites yet" while it cannot be set. F1 lists these keys.
- Change Voice Language says the new language as you switch it. It always read English and stayed silent on a change.

### Field
- In top-down exploration, the back alley behind Fountain Square (the way to the Velvet Room) is turned to match the way you walk in. The game moves you there by a jump: you walk north up the passage and arrive facing along the alley, which runs east. Inside the alley, up now keeps going toward the Velvet Room's door and down takes you back out, so the way you walked in continues instead of turning a corner. Compass directions in the alley follow the turn. Back in the plaza, north is the map's north again. The school rooftop is turned the same way: its stairs turn back on themselves, so on the roof up leads away from the stairwell door. A new setting, Keep your heading through passages (Exploring, on by default), turns this off.
- Top-down exploration keeps the camera facing north everywhere you walk. Some places hand the view to a scene camera of their own where you stand: by the Velvet Room's door in Paulownia Mall it turned about a quarter turn away from north, the station and the strip mall have them too, and your room had a fixed camera. While the mode holds, those scene cameras are off and the north camera shows the whole field; the mod also no longer has to turn the camera back every frame there. Walking and sound already went by north and are unchanged. Story scenes, conversations, menus and battles keep the game's own cameras.
- Opening the travel list (LB / M) no longer says the area's name before "Where should I go?", and closing it no longer says the area again.
- Auto-walk to a staircase takes the landing's own way to it. On the dorm's 2F landing it cut across the stairs down, so on the night of April 9 every walk to the 3F stairs ended in "It's not safe down below...".
- When the walk reaches someone's side but the game shows no prompt there, it goes round to another side instead of saying "Stuck". It gave up one step from the Suspicious Man in Club Escapade.
- Yukari is listed by name during the dorm escape. She was listed as "Person".
- People who sell you something are listed under Shops, not People: Octopia's takoyaki stand (the New Year's one too), the Flower Shop Lady, the School Store Vendor, the 6HARA Clerk, the Luxury Shopkeeper, the Suspicious Man and the Fortune-Teller.

### Notices
- "Next" on the Stats up panel waits until Space closes it. It was said as the panel rose, while the game still ignored the key; a press then did nothing. The same false start could give "Next" early on the victory pages.

### Requests
- A request's reward is read when you report it to Elizabeth ("Got ..."). The request list hid the notice. The Stats up notice is read over any menu too.

### Camp menu
- An arrow pressed while the camp menu closes says nothing. It read the next entry, which the game had already stopped listening to.

## 0.3.0

### New name
- The mod is now called Arcana. It says "Arcana loaded" when the game starts.
- The mod's folder in `Win64` is now `Arcana`, holding `arcana.dll`. When updating, delete the old `Win64\P3RAccess` folder.
- Settings and logs are now in `%LOCALAPPDATA%\Arcana`, and the log is `arcana.log`. The old `%LOCALAPPDATA%\P3RAccess` folder, with your settings, is moved there the first time the game starts.
- The download is now `arcana-<version>.zip`, from https://github.com/ChipsAhoiMcCoy/arcana.

### Auto-walk
- It moves the hero straight along its way at any angle, as a stick held exactly that way would, instead of the nearest of the eight directions the movement keys give: it keeps to narrow ways between furniture, takes the shortest line, and no camera angle can turn it off course. If the game does not take this, the walk goes back to the movement keys by itself.
- Things set into the wall, whose spot the hero can only reach the edge of (the radiator and the mirror in your room), are arrived at: the walk said "Stuck" a step away from them.
- Prompts for things passed on the way are no longer read, so they are not taken for arriving. The prompt up when the walk ends is read as before.
- Comma selects the nearest point of interest, whatever its category, and says it as the bracket keys do; pressed again it moves to the next nearest, and Shift+Comma goes back. It does not walk: press Apostrophe or Period to go there. It has no controller button: the right stick already finds things.
- Period walks to the selected point, as Apostrophe does, so Comma and Period sit together.
- Walking to the selected point and using it is now Shift+Period instead of Shift+Enter.
- The category is said once, first, as you enter it (the bracket keys, the controller's layer, Comma landing in another category): "Objects, Vending Machine, 3 meters, north, 1 of 4". Moving through the category says each point without it: "Desk, 2 meters, east, 2 of 4".

### Shadows in Tartarus
- The nearest Shadow within 30 m snarls steadily from where it is, instead of a growl repeated faster as it nears. It is louder the closer it is and higher while it hunts you. Its facing changes the sound, not its pitch: bright when it faces you, duller as it turns away, and muffled with a wobble once you are behind it, where a strike brings the advantage. Follow the wobble to sneak up on it.
- The mod's own alarm when a Shadow notices you is gone: the game sounds one itself.
- "Behind" now uses the game's own rule, more than 90 degrees off the Shadow's front (it was 110): the wobble, the spoken "Shadow close, back turned" and the behind ring agree with the advantage the game gives.
- The strike ring starts the moment any of the Shadow's body is within your strike, the game's own test (it counted a little short, 40 cm off the game's reach). It keeps ringing through your swing; it used to stop as you swung.
- Strike assist (a new setting, on): when you attack with a Shadow close enough that your strike would reach it if you faced it, from any side, you turn to face it as the swing starts. Your reach stays the same.
- The sound test has "Shadow, facing you", "Shadow, hunting you" and "Shadow, back turned".
- The log records each Shadow coming into your strike's reach, you stepping into its attack zone, each swing, and how each battle began.

### Focus ping
- Whenever something is focused (the list's keys, Comma, Shift+Semicolon or the right stick), Grim Dark's route ping plays once from where it is, as it does when Grim Dark's review cursor lands on something: one sound for in sight with a straight walk, one for a walk round something, one for no way there. It plays with the sonar off too; with it on, the thing's own sound follows.

### Wall tones
- The wall tones play only while you move (the stick, the keys or the auto-walk, even pushing into a wall), in either camera mode, and are quiet while you stand still.

### Audio description in story scenes (new)
- Story scenes played in the game's 3D engine, not only the animated movies, can now be described, in the same narrator voice, between the lines and never over them. The descriptions follow the scene's own clock, wait while a line is on screen, and stay quiet while you fast-forward. Described so far: the main story from the May full moon's monorail operation (Yukari climbing the ladder at the stopped monorail) through the New Year: the ghost story and the night at school, Fuuka, Koromaru, the hotel on the boulevard, Strega, Yakushima and Aigis, Chidori, Ken and Shinjiro, Takaya's ambush, the Personas changing, Ikutsuki's betrayal, the Kyoto trip, Chidori's sacrifice and Ryoji's truth, the New Year, the climb to the top of Tartarus and the ending; and side events (school days, exams, the nurse's office, the night walks with Koromaru, Takaya in the back alley, the new gear and Theurgy in Tartarus, time alone at the arcade, the cinema and the restaurants, and part-time jobs).
- Two settings choose how descriptions are given, one for the animated movies (Audio description in movies) and one for the 3D scenes (Audio description in 3D scenes): by the narrator's voice, as text read by your screen reader, or off. Your earlier on or off for the movies is kept.

### Descriptions read again
- Skills, items, gear, the camp menu's entries and Config's settings read their description after their name and position again, in the camp menu, in battle, on a Persona's status page and in fusion inheritance: "Maeiga, 16 SP, 2 of 7, Deals medium Dark damage to all foes." They had moved to the details keys, where players did not find them.
- A new setting, Descriptions in menus (Controls and help, on), turns this off for those who prefer the names alone; the details keys still read every description either way.
- In battle, whoever is in focus and a party member's details (HP, SP, ailments, affinities, Persona) stay on the details keys.

### Fixes
- At the fortune-teller in Club Escapade, and the other scripts that show your wallet before naming a price, no longer reads "Price 100000000 yen" before the choices. That number is the game's own "no price yet"; the real price is read once the game names it.
- Things on another floor you can walk to by stairs are listed again: from Paulownia Mall's fountain, Mandragora upstairs (and from upstairs, the shops below) were left out, so the karaoke bar could not be found or walked to.
- Tutorials name the keys the game draws: battle tutorials read from the Tutorial list said the field's keys ("Pressing H during battle will let you Rush", Shift for Theurgy, U for Tactics; the game draws Tab, T and W), Assist said E for F, Auto-Recover said E for Y, and Full Analysis, Oracle, the network tips and the sword strike said only "a key" (N, N, N and Ctrl).
- F1 in Tartarus says what N does: it opens the navigator's support skills (Escape Route, Jamming, Tartarus Search). It said only "N Navi".
- Pressing any button on a controller stops what is being said, as a key does with a screen reader: confirming an item no longer leaves its description reading on (the Beef Bowl CD). With SAPI or OneCore instead of a screen reader, any key but Shift, Ctrl and Alt does the same.
- Party chatter in the field whose voice is only a short reaction (a grunt or a laugh, not the words) is read again. On the monorail's Overhead Bridge, Junpei's "Alright, bring on the big one!" and Yukari's "Hey, don't get too excited and do something stupid" were silent. Chatter the game voices in full is still left to its voice.
- In the top-down mode the auto-walk no longer runs into the walls where the game's camera does not face north (your room in the dorm): it steered by the camera while the hero walks by the compass, and said "Stopped" or "Stuck" short of the desk, bed and closet.
- A mail is no longer read again after you answer its reply choice (the part-time job's mail was read a second time as the loading began). An item notice or a "Stats up!" panel with a message window over it is not read again either when the window closes.
- Back on that mail after its reply choice, when the game leaves you on it (turning down a hangout), its sender and title are said: it was silent.
- "Next", or the sound chosen in the Voice end sound setting, is said once A or Cross continues, not as the screen opens while its animation still plays: on the "Stats up!" panel, an item or money notice, a Social Link's rank card, and each victory page (the summary, the level-ups, the hero's page, a Persona's status page). The mod knows it from the game itself asking for the button, or the victory screen's own OK prompt, never from a timer.
- Two "Stats up!" panels in a row (Charm, then Courage) each read their stats: the second was silent.
- Voiced lines in field events (Mitsuru on the radio as you arrive at the Overhead Bridge, Junpei inside the monorail) end with "Next" again. The mod read the line's voice number wrong whenever it was above 255, so it never noticed the voice begin.
- "Auto on" and "Auto off" are said only when you switch Auto yourself (Shift, or X / Square on a controller). The game turns Auto off by itself where a scene's dialogue ends, and saying so talked over the scene's first description.
- "Next" waits for the narrator to finish a description before it is said, instead of talking over it.
- The morning walk at the school gate no longer says Junpei is with you: the friend who greets you there changes from day to day.

## 0.2.0

### Top-down exploration (new; to be tried)
- While you walk freely, the camera stays facing north and cannot be turned: up always walks north. The game's own sounds and the mod's are heard from where you stand with north ahead, as if from above, so a Shadow's growl comes from the Shadow. Conversations, story scenes, menus and battles keep the game's camera and sound. The Top-down exploration setting (Exploring) switches it off.
- Up walks north everywhere. Where the game shows a place from a fixed scene camera of its own (Fountain Square, the station, many rooms), up walked toward that camera's view instead, so sounds slid past sideways while you walked straight.
- North is the corner map's up in every place: where the game draws a map turned (Port Island Station, your room, the Command Room and others), north turns with it.
- The right stick scans a direction: push it toward one to hear the nearest point of interest that way, its distance and how far the wall is, and to hear that point's sound from where it is.
- RT while the right stick is on a point walks there and uses it (checks, talks, opens) once its prompt comes up. That RT never dashes.
- Directions in the points of interest list are given by the compass ("north-east") in this mode.
- The wall tones in this mode play only while you move, reach 3 m and leave out the direction behind your walk: fixed to the compass, they had found a wall in three or four directions all the time.
- In this mode the wall tones went quiet when you walked straight into a wall, just as it was nearest, because the hero had stopped moving. They now play while you push a direction, whether or not the hero gets anywhere.
- New sound placement, from Dark Vision: left and right by level and by the moment each ear hears a sound, sounds behind darker. The Sound placement setting (Sound) chooses it, Steam Audio's 3D (as before) or a plain pan. It replaces the 3D sound setting.

### Keys
- Shift+Enter walks to the selected point of interest and uses it once its prompt comes up, after Grim Dark's walk-there-and-use key.
- Shift+Semicolon says the selected point of interest again from where you stand, with its sound, as Grim Dark's semicolon does.

### Sonar
- A door or exit right beside you no longer swings from ear to ear as you walk past it. Its nearest edge sits on the floor, about a metre below where you are heard from, and that height counted toward how far to the side it sounded: an edge a hand's width to your right sounded almost fully right. Left and right now follow the distance across the floor alone, in the stereo sound placement.
- A thing is heard from its part nearest you, not from its middle, as in Dark Vision: a long counter or a wide exit sounds from beside you and quickens as you near its edge, so it is heard sooner. Standing inside a thing's area (Paulownia Mall's exits are strips you walk through), its sound comes from its middle at the quickest rhythm. People and Shadows still sound from where they stand.
- Sounds always play in full. Up close, where a thing repeats fastest, a shortened form of its sound played instead, so a door's knock and the exit's and event's sounds were cut off. Now the whole sound plays every time at its own pitch, as in Grim Dark, and a long one starts again over its own tail when its rhythm is faster than it is long.
- Grim Dark's sonar sounds: exits use its dungeon entrance sound, objects its interactable sound, events its ruined shrine, Twilight Fragments its loot, and a near Shadow its enemy ping. Doors, people and shops keep their own sounds, as Grim Dark has none like them.
- Each thing keeps its own rhythm again, as in Grim Dark: things of different kinds sound independently, and only two of one kind are kept a moment apart. In 0.1.0-alpha.3 only one sound played at a time, so in a crowd every thing waited its turn and the rhythms fell into a slow queue.
- The Sonar rhythm setting is gone with the sweep rhythm; pulse is the only one.
- Every thing repeats a quarter more slowly than before at each distance: almost seven times a second at 1 m, about once a second at 10 m.

### Sound
- Stairs no longer sound like a wall. The wall tones read the bottom of a staircase as a wall right there, in either mode: the stairs up out of a Tartarus floor, and low steps such as the ones your party stands on near the top of Tartarus. They now follow the steps up.
- If you muted the game in Windows' volume mixer, starting it un-muted it a few seconds in. Your mute now stays; only a mute the mod itself left behind is lifted.
- The mod's sounds (wall tones, sonar, cues, audio description) came back only after a restart when the output device went away, or when there was none at launch, such as a Bluetooth headset that connected late. They now come back on their own within a few seconds of the device returning.
- When a movie was skipped back or forward during a description, the description stopped with a click. It now fades out under the next one.
- In stereo sound placement, something close beside you now sounds from that side: a door 1 m to your right was placed less than halfway right, less than one 10 m away.
- Things behind you are easier to tell from things ahead. In the stereo placement the darkening behind now reaches the sonar's sounds; before, most of them sounded almost the same ahead and behind. In top-down mode, sounds to the south now play lower too, with "Lower pitch behind you" on, as in the camera mode.

### Points of interest
- On a controller, holding both triggers selected the nearest point every time, so choosing a point, letting go, then holding the triggers and pressing A walked to the nearest point instead of the one you chose. Opening the layer now says your selection and keeps it; with nothing selected it still picks the nearest.
- Moving to the Events category said a story event's name twice over ("Events: Event: Jin"). It is now "Events: Jin".
- Empty spots where the game can place a character were listed as "Person" when nobody stood there (three on the dorm's third floor, a step from the hallway), and walking to one stalled. They are no longer listed.
- People in your own room were left out of the list when the desks split the floor, as in Classroom 2-F: walking from the back door to Junpei's desk, the way around led out through one door and back in through the other, so he seemed to be behind a closed door. Anyone you could see over the furniture is listed now, and walking there finds its own way between the desks: from the back door to every desk, both bookshelves and the front door's students. Only where your body truly does not fit does it say "No path, though it is in this room". A student standing by the front door no longer hides the rest of the room.
- A missing person in Tartarus is listed with their name from the police notice once the notice shows it: "Missing Person, Ayako Yoshimoto".

### Battle
- The countdown in the battle against the Priestess on the monorail is spoken: "Time left: 29 minutes 59 seconds" when it starts, the minutes left with each of your turns ("29 minutes left"), every 5 minutes, then at 1 minute, 30 and 10 seconds, and the new time whenever the story cuts it short.

### Shops
- When a script asks you to pay with your money shown (the late-night TV shopping's "Buy / Don't buy"), the price and what you have are said before the answers: "Price 2980 yen, you have 4800 yen".

### Character descriptions
- The area key (Semicolon, or both triggers and B) now describes the character talking to you while their portrait is up beside the line: how they look, the outfit the portrait shows (summer or winter uniform, casual clothes, swimsuit, yukata, combat gear and the rest) and how they stand. It follows their outfit as it changes through the year. All 155 outfits of the 53 characters with a portrait are described. Outside a conversation the key describes the place, as before.

### Fusion
- A skill change offered after a fusion (Igor: "A skill seems to be on the verge of changing...") is followed by what each skill would become: "Bufu would become Spirit Drain. Agi would become Dodge Ice". Tried in the game, with the new Persona levelling up first and without.
- Choosing skills to inherit now says how many you may take ("Choose skills to inherit, up to 2.") and counts as you choose ("chosen, 1 of 2 picks"). Taking the last one brings Igor's question at once, as before.

### The end of the game
- A save made after the credits was read like any other ("March 5, level 96"). The list now says what its row shows: "Slot 9: Makoto Yuki, Clear data, start a new game, play time 46 hours 16 minutes".
- The credits: the review key now reads the names rolling past at that moment ("Credits. Chief Designer, Yuichiro Takada, Art Director, Tomohiro Kumagai, ..."). The roll is not read by itself.
- The last choice of the ending opened with no answer picked and Enter did nothing until Left or Right was pressed. The first answer is now picked as it opens, and Enter takes it.
- On that same choice, Left or Right changed the game's answer while the mod kept reading the first one, so Enter could take an answer you never heard. The mod now follows the game's answer.

### Lists
- A "LIST" choice longer than its window (the Velvet Room's Talk, 16 topics) listed only the rows on screen as it opened: the topics further down could not be reached. The whole list is read now.

### Town map
- F (town info) now reads a destination's shops and places from the game's own list instead of the text on screen, in the order the panel shows them, with the ones closed now marked "unavailable". It is said as soon as the panel comes up or the cursor moves, without waiting for the panel's animation.

### Shopping
- The TV shopping show (Sunday afternoons, the TV in your room) has now been played through with the mod: the show, the Buy / Don't buy choice and the purchase are all read.

### Mod settings
- Letter keys no longer jump to a setting by name in the mod settings menu; they do nothing there. The arrows, Home and End, Tab and the rest are unchanged.

### Calendar
- F on a day (the part-time jobs) read only the highlighted job's description, sometimes with the day's "Nothing in particular" still fading behind it. Each job is now read by name with its place in the list and "unavailable" when that day does not take it: "Chagall Café (unavailable), 1 of 2. Serve coffee that boosts a person's charm! Time: Night ...".
- When the story moved to another day with only the time-of-day screen (the epilogue's jump to March), just "After School" was said. The new date is now read with it.

### Less said twice, fewer keys read out
- Key names are no longer part of spoken lines; F1 reads them, as everywhere else. A turn's line ends "Theurgy ready" (it was "Theurgy ready, T"), a 1 More says "Shift available" (it was "B shifts the turn to another member"), a shop's quantity opens with "How many? 1" (it was "How many? W and S change, Space confirms. 1"), and the Stats up screen no longer ends with "Space continues."
- Beside a Shadow that kept turning, "Shadow close, facing you" and "Shadow close, back turned" were said every time it turned: over a hundred times in a minute next to one that circled. Each is now said once as you close in on a Shadow; the ring that tells you a strike will connect, and whether from behind, still follows its facing all the time.
- A Shadow that chased you out of earshot and came back was treated as if it had not noticed you. It is still growled as hunting.
- After a Persona with eight skills learns one at a battle's end and you choose the skill to forget, the victory screen no longer says "Victory" again, and the Persona's "Level up!" line is read once (it came twice).
- "Theurgy obtained" no longer cuts off the line being read, and the town map's information about a place no longer cuts off the place's name.
- The victory page, a saved-game line, an opened mail and a few other lines of a menu's own can no longer be read twice in a row when nothing was pressed in between.
- A thought or notice of two pages that followed another one (Club Escapade's closed door, the dorm fridge's notice) was read whole while its first page still showed, and its second page again, as a new line, once it came up. Each page is now read when the game shows it.
- Walking to the Velvet Room from Paulownia Mall stopped in the back alley, short of the door, and needed a second press. A walk now goes on to its target after crossing into another part of the map on the way.
- An item added to a "Got ..." notice that is already up is said alone ("Got 1 Up"), not with the whole list again.
- The point of interest list keys (the bracket keys) say "Not in the field" in a menu, a conversation or a battle, where the list is not about what is on screen.

### Battle
- Shuffle Time's Persona Overstock list (a Persona card with a full stock): the game's cursor is now put on the row you focus, also after Home, End or a jump, instead of being stepped there one press at a time.
- When the game greys out commands on the battle wheel, the turn's line now says so ("Attack, Items, Guard unavailable"). It happens in a tutorial's battle and on the very last turn of the final battle, where only the Persona's skills are left and a press of Space did nothing without a word.
- Analyze now gives everything its screen shows. Besides the name, level, health and affinities, the detail buffer (Ctrl+Up and Ctrl+Down, or the right stick) reads the enemy's maximum HP and SP, its arcana, its attack type, its skills and what it drops, each only once the game itself shows it (a Shadow not yet analyzed keeps its skills unknown).
- A battle now opens with who has the advantage, as the splash on screen shows it: "S.E.E.S. advantage" when you struck first, "Shadow advantage" when the Shadow caught you. Nothing is said for an even start.
- When a Persona with eight skills levelled up after a battle and had to forget one to learn the new skill, the list of skills was not presented: only "This Persona cannot learn any more skills" was read, and Enter forgot whichever skill the game's cursor was on. The list is now a menu, as it already was with a skill card: the new skill first, then the eight slots with their costs; Enter asks "Forget ...?", and the level-up page follows.
- A physical skill's cost in the battle skill list was read as a percentage ("Akasha Arts, 140% HP") when the number is the HP it takes from that member. It now reads "Akasha Arts, 140 HP". The Persona pages keep the percentage ("22% HP"), which is what they show.

### Points of interest: what the list was missing
- The icon the game floats over a person is now read after their name in the list: "Akihiko Sanada, talked to" once you have heard what they have to say today, "Social Link" when a link can move forward, "Social Link, reversed", "hangout", "Linked Episode", "request", "study group" and "walk". A person with nothing after the name has something new to say.
- The two Twilight Fragments in the underground base of the August full moon were listed as "Something Shining", as plain objects. They are now "Twilight Fragment", with the fragment's sound on the sonar, like the ones in town.
- A missing person waiting on a Tartarus floor was not in the list at all. They are now listed under People by the game's own name for them ("Missing Person", "Stray Cat", "Old Man in Pain"), sound on the sonar as a person, and leave the list once rescued. Not yet tested in the game.
- Tartarus' Monad door ("Enter Door") was listed under Objects with the object sound. It is a way onward: it is now under Exits with the exit sound, and so are the doors inside the passage ("Exit Door", "Proceed Onward", "Go Back").
- Every Tartarus chest read "Treasure Chest". The list now tells them apart: "Treasure Chest", "Rare Treasure Chest" (the silver case under purple sparks), "Gold Treasure Chest" (the gold case; the one opened held a Diamond) and "Locked Treasure Chest, 3 Twilight Fragments", with what it costs to open. The prompt beside a chest still reads as the game shows it, "Check: Treasure Chest".
- Every Shadow on a floor read "Shadow". The game's stronger kind is now "Strong Shadow"; the rare kind that runs from you is "Rare Shadow" and the Reaper is "The Reaper" (those two not yet met in the game).

### Points of interest: only the part of the map you are in
- Some places are two areas in one map with a closed door between them, like the school's Gym Hallway and the Corridor outside it. Everything past the door was listed and sounded on the sonar, and the auto-walk to it ran into the door and said "Stuck, stopping". Things past a closed door are now left out of the points of interest list and the sonar until you go through the door's exit; then that side's things are listed and the other side's are left out.
- The exit that takes you through the door stays in the list.
- A point you selected before going through a door is no longer selected once the door is between you and it.
- A Twilight Fragment's prompt is said with its verb, "Check: Something Shining", like any other thing's. It is said again when you walk away from the fragment and come back; it used to stay silent until some other prompt had shown.
- Fixed: after a prompt went away the mod looked its thing up in a fresh list of points of interest every frame, and never stopped once that thing had left the list. It now asks the thing itself.

### Objectives
- Fixed: with two objectives on screen at once (a story objective and a Tartarus floor's "Explore the floor"), both were said again and again without end. Each line of the objective panel is now said once, when it appears.
- A fourth line of the panel ("Find a valuable treasure chest") is read too; it was below where the mod looked.

### Auto-walk: round people in the way
- At the top of Tartarus the walk to "Event: Takaya" went straight at it, into the pillar in the middle of the landing, and said "Stuck, stopping". A story trigger that floats well above its floor is now walked to by the floor under it: the walk goes round the pillar and up the ramp.
- The auto-walk's path knows the walls but not who is standing on the floor. With a student walking toward you down a hallway, it pushed into them and said "Stuck, stopping". It now sees someone in the next step of its path and steps to one side of them, then goes on.
- When it is blocked by anything else its path does not know of, it tries a step to either side before giving up. It says "Stuck, stopping" after three such steps that brought it no nearer.
- Fixed: arriving at a Social Link partner sitting at a desk (Kenji in Classroom 2-F) turned you away from them, so the Talk prompt went away and they could not be talked to. You are now turned to face them.

### Mail
- Fixed: the phone's mail list read "Mail 1" in place of the sender and subject about every other time it was opened, and a mail opened from such a list read only the sender's name, without its subject or text.
- Fixed: opening a mail read nothing at all. The sender, the subject and the mail's text are read when it opens.
- With no mail, the list says "No messages"; it also read the keys to close it, which F1 reads now.

### Town map
- Each destination says who is there now, after its name and position: the Social Links you can spend time with ("Social Links here: Kenji Tomochika (Magician), rank 1, ready to rank up") and the other characters the map marks. A link you have not started yet is listed too, as the game marks it, under the game's own name for it ("Bookstore (Hierophant)"). The game shows them as card icons; nothing read them before.

### Shops
- A row you cannot buy says why, where it said "not now": "out of stock", "carrying the maximum" (99 of it) or "not enough yen" ("Nastea, 110 yen, 3 owned, out of stock").
- A vending machine holds a few of each drink and refills once a week. Its rows say how many are left ("Fountain Dew, 110 yen, 0 owned, 2 left"); the game shows only a sold-out mark.

### Sonar: nearness is heard
- A thing repeats much faster as you close in: about once a second at 10 m, twice at 5 m, three times at 3 m, five times at 2 m and eight times a second at 1 m. It was three times a second at best and once a second at the range's edge.
- The speed goes by distance alone. It used to stretch with the Sonar range setting, so the same door at the same distance ticked slower with a longer range.
- The sounds are shorter (0.11 to 0.16 seconds, from 0.16 to 0.28), so more of them fit in a second. They still never play over one another.
- Inside 2 to 3 m a thing plays a clipped form of its sound so that it can repeat that fast: one knock, one whistled note, the higher bell strike, a puff of air, the start of the pluck.
- With many things around, the near ones keep most of their speed and the far ones wait longer. The turns used to be shared so evenly that a thing beside you in a full room repeated less than once a second.

### Twilight Fragments
- The glowing blue fragments lying around town ("Something Shining" on screen) are listed among the objects as "Twilight Fragment" instead of under the game's name. A fragment leaves the list once it is picked up.
- In Tartarus the objects list "Twilight Fragment crystal": the breakable object that always gives a fragment when struck. It was missing from the points of interest and from the sonar altogether, and it had no strike-reach ring. It has all three now.
- Both have a sonar sound of their own, so a fragment stands out from the other objects by ear: three high chimes of glass, rising, a sparkle. There is a "Sonar: Twilight Fragments" setting and a "Sonar: Twilight Fragment" row in the Sound test.

### Events: Gatekeepers and scenes you walk into
- Points of interest have a new category, Events, between Objects and Shadows: spots that start a fight or a scene when you walk into them, with nothing to press. On a Tartarus Gatekeeper's floor it lists "Gatekeeper", where the fight starts, until the Gatekeeper is beaten.
- Events have a sonar sound of their own, a quick trill between two hollow notes. They used to share the objects' plucked note. There is a "Sonar: events" setting and a "Sonar: event" row in the Sound test.
- Fixed: the sonar could tick for an unnamed event spot that the points of interest list did not have. On a Tartarus floor it sounded like an object right beside you that could not be found in the list.
- An unnamed event spot that is already finished is no longer listed.

### Less to listen to
- A battle turn opens with a shorter line: "Junpei, HP 99, SP 17. Cowardly Maya, 35%, Down, weak to Slash, Fire". The HP and SP maxima, the word "Target" and the target's place are gone from it; moving the target still says its place.
- Affinities drop the word "Attack": "weak to Fire, Ice" instead of "weak to Fire Attack, Ice Attack". "Downed" is now "Down".
- The battle skill list reads name and cost only ("Agi, 3 SP, 2 of 3"). What the skill does is one flick away: Ctrl+Down or the right stick down reads it, then the acting member's details.
- The Stats list reads each member with their Persona's name only. Ctrl+Down or the right stick down walks the Persona's stats, skills with costs and affinities line by line. This is the same details list battles have, now outside battle too.
- More lists keep their descriptions for the same details keys instead of reading them after every row: the camp menu's entries, items in the camp menu and in battle, the camp menu's skills, Equip's gear, the skills on a Persona's status page (one just learned still says what it does), the fusion skill-inheritance list and the game's Config. Backslash reads a row with its description in one go, as before. Shops, requests, the calendar, Shuffle Time's cards and event choices still read theirs at once.
- F1 mentions the details keys wherever the focused row has details.
- Choosing who gets an item, casts or receives a skill, or changes gear no longer reads each member's level.
- A skill or item that hits a whole side asks one question and says the buttons: "Use Mazio Gem on all enemies? A to confirm, B to cancel." It no longer says "Choose target", every name on that side and "1 of 1"; each hit says who it landed on, as before. F1 there reads the same two buttons.
- The mod settings are in five categories instead of one list of 27: Exploring, Sonar, Sound, Dialogue and movies, Controls and help. Tab and Shift+Tab, Page Down and Page Up, or RB and LB change category.
- Mod settings: every setting says what it does, read with the row after its value and position. No extra key is needed.
- Mod settings: a new Sound test category. Space or A on a row plays one of the mod's sounds, and the row says what the sound means: the sonar's five sounds, a sound from behind you, the Shadow's growl, alarm and lost-you sound, the strike-reach rings, the four wall tones and the controller layer's tick.
- Mod settings: pressing on at the first or last row says the row again without the cursor sound, as the game's menus do.

### Removed
- The beacon (the chirp toward the selected point of interest), its setting and its key, Shift+Semicolon. The sonar already marks the selected point, and the auto-walk takes you there; the beacon was one more sound on top of them.
- The short tick that marked the selected point of interest among the sonar's sounds. The selected point still always has a place among them, and still plays its sound once when you land on it in the list.
- The nearby chimes and their setting. The sonar's sounds are what tell you something is near; with the sonar off, nothing plays in their place.
- "Beeps and chimes volume" is now "Shadow sounds volume": it sets the Shadow cues and the controller layer's tick, which is all that is left on it. Your saved value is kept.

### Fixes
- After Shuffle Time, enemies finished by an All-Out Attack are no longer read as healed, down and defeated a second time.
- On a controller, moving to the first or last target on the command wheel sent its line to the screen reader twice.

## 0.1.0-alpha.3

### Sonar (new)
- Every point of interest near you now repeats its own sound from where it is, faster and louder the closer it is: exits a rising breath of air, doors two knocks, people a two-note whistle, shops a small bell, objects a plucked note. On by default; F3 (both triggers and R3 on a controller) turns it on or off.
- It works with the points of interest list: the point you selected is marked by a short tick before its sound and always has a place among the sounds, and each point you land on in the list plays its sound once from where it is, however far.
- New mod settings: Sonar, Sonar plays (everything nearby, the list's category only, or the selected point only at any distance), Sonar range, a switch for each kind (changing one plays its sound), and Sonar volume.
- It reaches 10 m unless you change it (up to 40), and a thing sounds the moment it comes into range.
- Its sounds take turns: one at a time, each after the last has finished, the most overdue first, so they never play over one another however many things are near.
- The nearby chimes now play only while the sonar is off.

### Menus
- What a menu presses in the game for you (stepping the game's highlight, the confirm) now goes out on the device you pressed: a key for the keyboard, a button for the controller. It used to follow whichever device had stirred last, so a controller's stick resting near its edge could turn a keyboard confirm into a controller press.
- Returning to the title from System no longer reads "Menu, System, 9 of 9" again after you confirm.
- Rewind: you can now go back to any day in the list. The game's cursor did not follow the focus, so only the day the list opened on could be confirmed.
- Rewind: the list waits for its opening animation like the other menus, and nothing is read again behind the fade after you confirm a day.
- A prompt such as "Check: Dorm Register" is no longer said behind the black screen while a rewind or a load takes you away.

### Shadows in Tartarus
- The Shadow's growl is heard from 30 m instead of 15, is louder at a distance, and is pitched where headphones carry it. A Shadow above or below you is no longer left out, which could keep one silent until it was on you.
- The Shadow's growl is now a longer, rattling snarl and repeats faster: every 0.8 seconds at 30 m, running together into one unbroken snarl beside you.
- Strike reach: while a Shadow is inside the reach of your strike, a quick ting of steel repeats fast (about six a second, stopping the moment you leave the reach) in the middle of your head (it is about you, so it has no direction), so you know the attack will connect before you swing. It is read from the game's own hit area. Behind the Shadow, the ring is the two quick ticks that mean the strike brings the advantage; those used to rely on an estimate of the distance.
- A Shadow that notices you sounds a harsh two-note alarm from where it is, and its growl is higher, louder and faster while it hunts you. Two soft falling notes mean it has lost you.
- The strike-reach ring also plays for a breakable object while your strike would break it. A Shadow in reach takes the ring first. Like the other Shadow cues it needs the Shadow alerts setting on.

### Exploring
- Pushing the controller's left stick stops the auto-walk, as a movement key already did on the keyboard.
- The auto-walk finds the way in to a thing that stands inside something solid, such as a Tartarus teleporter between its pillars: it checks which sides the hero's body can come in from, walks round to the nearest and goes straight in. It used to circle the thing a sixth of a turn at a time, which could miss every gap and end in "Stuck".
- Exits are said by name alone: "Iwatodai Station", not "Iwatodai Station exit", which was taken for the way out of the place.
- Prompts say "Go to" only before a place an exit leads to. A prompt that already says what you do, like "Enter the Velvet Room", and a device you operate are said by name alone.
- The auto-walk ends when a dialogue or menu comes up, instead of walking on into a way the game has just turned you back from.

### Sounds
- A sound with a place in the world now stays at that place while it plays: the sonar's sounds, the beacon, the Shadow cues and the nearby chimes shift in your ears as you walk or turn the camera during them. Each used to stay where it was heard when it started.
- None of the mod's field sounds play in a battle, a story scene, a conversation, a menu or shop, behind a faded-out screen, or while the mod's settings are open. The wall tones and the nearby chimes used to go on through battles and scenes; the wall tones, the sonar, the chimes, the Shadow cues and the beacon now all follow one rule.
- The mod's plain beeps are replaced by sounds made to match the sonar's. The beacon is a short rising chirp, the Shadow pulse a low, rough growl, the "strike from behind" cue two quick high ticks, and the controller layer's tick is softer.
- A nearby chime is now its kind's sonar sound, played once, instead of a beep at one of five pitches.

### Battles
- The hero's level-up page on the victory screen no longer reads the equipped Persona and its level. Among your new level, HP and SP it sounded as if the Persona had levelled too. A Persona that does level up is still announced on its own line.
- The target no longer wraps around on the command wheel or in Analyze. At the first or last enemy, a further press says who you are still on, so you can tell the leftmost from the rightmost.
- A skill or item that hits a whole side is now one choice in the target list: "All enemies" or "All allies" with their names, instead of a single enemy's name.
- Damage or healing on the one target you chose yourself is said as the number alone: "14 damage", "healed 53". The name stays wherever you did not pick the target: enemies' and allies' own actions, anything that hits several, and an attack sent back at you.
- Enemies finished by an All-Out Attack are announced as defeated when the battle is won, not after Shuffle Time.
- Rush is announced: "Rush" when you turn it on, "Rush off" when you stop it or the game ends it, as a boss's mid-battle lines do. It was silent.
- The word the game shows beside a hit is said: "Weak", "Critical", "Resist", "Miss" or "Block", followed by "on" and the name unless it is the one target you chose. A miss or a blocked attack used to say nothing at all.

### Keys (F1)
- On a Tartarus floor, F1 now also names Auto-Recover (Y, or RB on a controller) and Navi (N, or View).
- F1 on a dialogue choice list names its keys. It said "No keys to tell here".
- The Auto-Recover tutorial names Y on the keyboard, not E.

### Game over
- The poem before the choices is read: "Game Over", then its four lines as the game brings them in. That stretch was silent, apart from your fallen allies' HP being read out, which is gone.
- Confirm during the poem skips the rest of it and goes on to the choices. The game itself only finishes one line per press.
- Each choice is followed by its own description. The wrong one was read first and then corrected, and a description could repeat or follow you to the next choice.
- The choices are announced once the game takes input on them. They were announced a moment early, so a confirm pressed at once was lost.

### Victory screen
- The screen no longer waits for the game's animation. The summary is read at once, your confirm brings the level-ups straight away, and a confirm with nothing left to hear takes you through the rest of the animation to the next page that is yours to read.

### Shuffle Time
- Each card now says what its face shows before its effect: "Fool", or a suit card's suit and number such as "Wands 1".

### Velvet Room
- A Persona's status page in registration and in the compendium is read again. It was silent: the list behind it kept the focus. The page now opens with what confirming does, "Register this Persona?" or "Summon this Persona?", before the Persona's name.

## 0.1.0-alpha.2

### Stability
- The mod now checks which version of the game it is running on. On anything but the current Steam version, such as the demo, it says so and turns its menus off, because reading them there caused crashes and frozen games. Messages and the field still work.
- Menu lines no longer repeat by themselves. A line is not said again until you press something or something else speaks, and holding a key at the end of a list stays quiet.
- Holding a confirm button now counts as one press.
- Quitting the game no longer makes the mod say false things, like "April 1" and every Social Link reversed, or fault on the way out.

### Battles
- New: anyone in focus says their ailments with their health, such as "Jin, 96%, Downed, Poisoned".
- New: a details list for whoever is in focus. Ctrl+Down or the right stick down moves through it line by line, and Ctrl+Up or the stick up goes back. It holds name and level, HP, SP, ailments and buffs with their turns, guarding, the affinities you have found, and for a party member their Persona, stats and Theurgy gauge.
- Your first target move on a battle's first turn is no longer lost.
- With one enemy left, pressing left or right says who it is.
- A skill, item or Guard you chose yourself is no longer read back. What enemies, and members acting on their own, do is still read.
- A false action after an enemy's Guard is gone, and a counter now names the character who countered.
- Several weaknesses are separated by commas, and affinity lines no longer end on a missing attack name.
- Party members' levels in battle are now correct.

### Victory screen
- "Victory" now waits for the last blow's news instead of cutting it off.
- The EXP, the money and each item are now their own lines, read in turn, and you can go back through them with the arrows.
- Level-ups that slide in no longer move you off the line you are on.
- A Persona's status page reads its level, the skill learned and the stats that rose.
- The hero's level-up page is read again after a notice cuts it off, and a press stops the reading without carrying into the next battle.
- A member's max HP and SP are no longer read at level-up, because the numbers were out of date.

### Menus
- Menus now wait for the game's opening animations. A menu speaks once it can take input, and presses made before then are dropped, as the game drops them.
- Titles such as "Skills" and "Choose target" are no longer cut off.
- Fusion Search and Special Fusion make one tick per move instead of two.
- Config reads a new list once, from the right row.
- Equip: the hints and the details view's scroll arrows now match the game.

### Exploring
- The party's voiced chatter is no longer read over the voices, so it stops cutting off lines like "Thebel, floor 4". This includes the Reaper's warning, which you still hear from the game. A line with no voice is still read.
- Camp menu tabs, such as Consumable Items, are no longer announced as objectives.

## 0.1.0-alpha.1

The first public release. This is an alpha: expect bugs, and please report them.

- Speech for dialogue, choices, notices, menus, battles, shops, Social Links, the Velvet Room, calendar, mail, saves and more, through NVDA, JAWS or Windows speech.
- Every menu is navigable with the arrow keys or D-pad, with positions, descriptions and type-ahead where it applies. The game's highlight follows.
- Getting around: points of interest, auto-walk, a guidance beacon, nearby chimes, wall tones and Shadow alerts, with optional 3D sound for headphones.
- Written descriptions of every area, following time of day and season.
- Audio description for all 42 animated story movies, by a separate narrator voice.
- Spoken descriptions of story cut-ins and full-screen pictures.
- Full controller support for the mod's keys: hold both triggers.
- A settings menu on F2, or both triggers and View.

See [KNOWN_ISSUES.md](KNOWN_ISSUES.md) for what is missing or untested.
