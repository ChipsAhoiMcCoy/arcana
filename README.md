# Arcana

Arcana is a screen-reader accessibility mod for Persona 3 Reload on Steam. It speaks the game through your screen reader and adds sound for getting around: wall tones, a sonar of the people, doors, exits and things around you, and an auto-walk to any place of interest.

This is an unofficial fan project, not affiliated with or endorsed by Atlus or SEGA. It includes no game files; you need your own copy of the game. Persona 3 Reload and related names and characters belong to their owners.

## Status

Alpha. Most of the game is covered and much of it tested, but nobody has finished the game with the mod yet. See [KNOWN_ISSUES.md](KNOWN_ISSUES.md), and please report what you find.

The mod is made for the current Steam version of the full game. On anything else (the demo, an older update) it says so when it loads and reads messages and the field but not menus, because their different layout froze the game.

## Requirements

- Persona 3 Reload, Steam version (app 2161700), on Windows 10 or 11.
- A screen reader such as NVDA or JAWS. Without one, the mod uses Windows speech.
- A keyboard or a controller.
- Headphones are recommended.

## Install and uninstall

1. Download the zip from the Releases page and extract it.
2. Copy `dsound.dll` and the `Arcana` folder into the game's `P3R\Binaries\Win64` folder, the one with `P3R.exe` (by default `C:\Program Files (x86)\Steam\steamapps\common\P3R\P3R\Binaries\Win64`).
3. Start your screen reader, then the game from Steam.

To uninstall, delete those two from `Win64`. Settings and logs are in `%LOCALAPPDATA%\Arcana`; delete it too if you want them gone. Saves are not touched. Details and troubleshooting are in [INSTALL.md](INSTALL.md).

## First run

The game takes a while to start; you will hear "Arcana loaded". The caution and photosensitivity notices each stay up until you press Space or A. Then comes the title menu: up and down arrows or the D-pad, Enter or A to choose.

Learn two keys first: F1 reads the controls of the screen you are on, and F2 opens the mod's settings. On a controller, hold both triggers and press Menu or View.

## Keys

The game's own controls work as usual. The mod adds:

- F1: The controls of the screen you are on (a menu, battle, conversation or the field)
- Shift+F1: The mod's own keys
- F2: Mod settings
- F3: Sonar on or off
- Hold Alt: Walk. The game only runs on the keyboard (a controller's stick walks when pushed gently); while you hold Alt the movement keys walk, as holding Shift dashes. Shift with Alt still dashes. With Always dash (F2, Exploring, on by default), you dash without Shift outside Tartarus, and holding Shift runs. The mod's keys work while you hold it, and the mod's walk to a point of interest dashes or runs with you
- Slash: Where am I: date (with the moon: "full moon", or the days to the next one, as the date in the corner counts them), area, yen and current objective
- Shift+Slash: Social stats with their ranks
- Shift+Backslash: Social Links: each arcana with its partner and rank
- Backslash: Repeat the current message, or describe the current screen
- Right / Left bracket: Next (farther) / previous (nearer) point of interest in the category
- Shift+Right / Shift+Left bracket: Next / previous category, read from its nearest
- Apostrophe: Walk to the selected point of interest (press again, or move, to stop)
- 1 to 7: One category each: 1 Exits, 2 Doors, 3 People, 4 Shops, 5 Objects, 6 Events, 7 Shadows. The first press selects that category's nearest, each press after it the next one out, wrapping round; the category is not said ("No Shadows" when there are none near). Shift+number goes back; as the first press, the farthest. The selection and the bracket keys' category follow it
- Comma: Select the nearest point of interest of any category, said as the bracket keys say it with its place among all of them, without its category ("Vending Machine, 3 meters, north, 1 of 9"). Press again for the next nearest, wrapping round. It does not walk: Apostrophe or Period then goes there
- Shift+Comma: Back through the same list, toward the nearest; as the first press, the farthest
- Period: Walk to the selected point of interest, as Apostrophe does (press again, or move, to stop)
- Shift+Period: Walk to the selected point and use it: Space is pressed for you once its prompt (check, talk, open) comes up. Nothing is pressed where no prompt comes, as at an exit
- Shift+Apostrophe: Party: each member's level, HP and SP, then the navigator's SP
- Semicolon: Describe the area, or while someone talks, describe them; on a Persona or a Shadow in focus (a battle target, a fusion, the compendium), describe it; on a Social Link in the camp menu, describe its picture
- Shift+Semicolon: The selected point of interest again, from where you stand, with its sound

### On a controller

Hold both triggers (LT and RT) for the mod's keys. You hear a tick and, in the field, the selected point of interest (or the nearest of the current category if none is selected). While you hold them the game ignores your buttons:

- D-pad left / right: Previous / next category
- D-pad up / down: Previous (nearer) / next (farther) point of interest
- A: Walk to the selected point (again, or push the left stick, to stop)
- B: Describe the area, the person talking, the Persona or Shadow in focus, or a Social Link's picture
- X: Repeat the message, or describe the screen
- Y: Where am I
- LB: Social stats
- RB: Social Links
- L3: Party
- R3: Sonar on or off
- Menu: The controls of the screen you are on (like F1)
- View: Mod settings (like F2)

A single trigger reaches the game 0.15 seconds late (adjustable in the settings), so pressing both does not also dash or turn; a quick tap still works.

In top-down mode (always on while you walk freely), the right stick no longer turns the camera while you walk. Push it toward a direction (up is north) to snap to the nearest point of interest that way: its name and distance are said ("Iwatodai Station, 8 meters"), or "nothing", and its sound repeats alone from where it is while you hold the stick, even with the sonar off. It speaks again when another point takes over. Press RT while on a point to walk there and use it, as Shift+Period does; that press does not dash.

### In menus

Every menu (title, camp, shops, the Velvet Room, battle lists and the rest) is the mod's own: it reads each entry from the game's data as you move and moves the game's highlight to match. Use the arrow keys; W, A, S and D do nothing in these menus.

- Up / Down (D-pad): Move through the list, with its position ("3 of 9"); at either end the item is read again
- Left / Right (D-pad): Move along a row, change a value, open or close a group; in a plain list they reach the game
- Home / End: First / last item
- Enter or Space (A): Choose
- Tab / Shift+Tab (RT / LT): On a page in sections (a Persona's status page, a member's Stats page), next / previous section with its title ("Stats, Strength 54, 1 of 5"). Page Down / Page Up do the same, also where Tab is the game's.
- Tab / Shift+Tab: Next / previous panel, on screens with more than one
- Backslash (triggers + X): The focused item in full, with its description
- Ctrl+Down / Ctrl+Up (right stick down / up): Next / previous line of the focused row's details (see below)

Everything else (C to go back, Q and E for pages) is the game's, and if the game moves its highlight (stick, mouse, page change) the mod follows.

**Details.** Every item, skill, piece of gear and setting reads its description right after its name, cost or count and position: "Mediarama, 16 SP, 2 of 2, Moderately restores party's HP." This covers the camp menu's entries and help lines; items and skills in the camp menu, in battle and in fusion inheritance; Equip's gear; skills on a Persona's status page; and Config's settings. The details keys read it again. The details keys also walk what is too long to say on every move: whoever is in focus in battle (HP, SP, ailments, affinities), a party member on the Stats list (Persona, stats, skills), and the acting member after a battle skill's description, starting from the top each time you land on a row. F1 mentions the details keys wherever a row has them.

### Key hints

Key hints are only spoken when you press F1 (or triggers + Menu): the keys of the current menu, battle, conversation (next, log, auto, skip), tutorial (Q and E, or LB and RB, turn pages; each page is read with its position) or field ("Space checks and talks, Tab menu, M map, ..."). Escape is Back / Cancel in menus and battle prompts, except in the contract, where it is the game's; C, the game's own key, works too (on the battle command wheel both are the game's Guard).

Hints follow what you play with: after a controller button they name Xbox buttons ("A reads, B closes"), after a game key they name keyboard keys again, and tutorial button icons switch the same way. The mod's own keys don't switch them. With a controller connected and nothing pressed yet, hints start on the controller.

In a conversation, Auto (Shift, or X) and Fast-forward (Tab, or Menu) are announced on and off. While Auto is on, the "When a line ends" cue is not played. During fast-forward, lines are not read but still go in the log (B); when it stops, the line on screen is read.

### More keys on particular screens

F1 always gives the current screen's keys. These are not described elsewhere here:

- Stats: F (controller: X, Square on PlayStation) adds or removes the focused member: "Junpei joins the party", "Junpei leaves the party". The game allows it only in some places (the dorm, Tartarus's entrance hall, and a few others); elsewhere, such as on Tartarus's floors, it says "The party can't be changed here", and a member who can't join or leave is said so ("Colton can't leave the party"). The change is saved when you close Stats.
- Camp Persona: H releases a Persona.
- Quest: X sorts.
- Compendium: Q and E sort, Tab shows registered Personas only, F locks.
- Registration: Tab marks, F registers.
- Fusion Search: Q and E sort.
- Shops: Q and E switch member or category.
- Area map: Tab zooms.
- Online features (with the game's Network Functions on): N (View on a controller) in town opens what other players did today as a menu, with the date: each kind of activity (daily life, Social Links, Tartarus) with its share, then the activities the game notes for it; up and down read them, Tab (RT) jumps to the next kind. On a class question's answers, N opens how other players answered: a row per answer with its percentage, opening on the answer you are on. The first row is read once the figures arrive. N, C or Escape (View or B) closes either.
- Battle: Q on the target list analyzes; A and D, or Q and E (LB and RB), switch target in Analyze. Analyze is a page like a Persona's status: up and down go through the enemy's name, arcana, level, maximum HP and SP, each affinity ("Fire: weak", "Dark: unknown"), its attack type and skills, and its drops; Tab jumps between those sections. Once Fuuka can, N (the pad's View) runs her Full Analysis, as the game shows it, and its end says the affinities it found.

## Mod settings

F2 (or triggers + View) opens the settings from anywhere; the game's Config screen lists them too. The game gets none of your keys while they are open, and while you are exploring it stands still, as under the camp menu: Shadows, characters and the field's sounds wait until you close the settings.

They work like any other menu: up and down choose (at either end a further press repeats the row), Home and End jump, left and right change the value (every row runs from off, or its least, at the left to on, or its most, at the right), Space or Enter (A) steps through values, F1 (Menu) reads these keys, and Escape, Backspace or F2 (B or View) closes (on the Mod keys page, Escape, Backspace and B go back to the settings). Tab and Shift+Tab (Page Down / Page Up, RB / LB) switch category, wrapping. Each row says what it does after its name, value and position. Changes are saved at once to `%LOCALAPPDATA%\Arcana\settings.ini`. The menu plays the game's own menu sounds.

**Exploring**

- Keep your heading through passages: off, on. In top-down exploration, rooms the game moves you into turned around are turned to match (see below)
- Always dash: off, on. Outside Tartarus you dash whenever you move, without holding Shift (RT). Holding Shift (RT) then runs, and Alt still walks, so all three paces stay. The mod's walk to a point of interest dashes too. In Tartarus and Episode Aigis' dungeons you run as before, since a dash there draws the Shadows' notice. On by default
- Points of interest range: 60 meters; 20, 40, 100 or 150
- Same floor only: off, on. In a place with several floors (the Strip Mall, Paulownia Mall, the dorm), the points of interest list and the sonar leave out everything on the other floors; the stairs between floors stay
- Wall tones: only while moving; off or continuous (standing still too)
- Wall tone range: 5 meters; 1 to 10 in steps of 1
- Shadow alerts: off, on. In Tartarus: the Shadow's steady snarl (muffled and wobbling when its back is to you), the note when one loses you, the strike-reach ring (for Shadows and breakable objects) and the back-turned / facing-you cues
- Shadow sight: off, on. In Tartarus: each nearby Shadow's sight sizzles from its edge nearest you, louder and higher as you near it, and a muffled hum plays while a wall hides you from one
- Shadow sight range: 10 meters; 2 to 16 in steps of 2. How far from the edge of a Shadow's sight you start to hear it
- Strike assist: off, on. In Tartarus, when you attack, you turn to the Shadow your strike can reach, whichever way it is (with no Shadow in reach, to a breakable object)
- Relaxed Reaper rate: off, on. In Tartarus, you can stay on a floor twice as long before the Reaper comes (about six minutes on a normal floor instead of three); Fuuka's warning still comes shortly before it. Turned on while on a floor, the time left there doubles (and halves when turned off)
- Always advantage: off, on. Every battle you start by touching a Shadow begins with your advantage, as if you had struck it from behind: also when you strike it face to face and when it reaches you first. Boss and story battles stay as the game has them.

**Sonar**

- Sonar: off, on (also F3)
- Plays: the selected point only (at any distance), the list's category only, or everything nearby
- Range: 10 meters; 5, 15, 20, 30 or 40
- Exits, Doors, People, Shops, Objects, Events, Twilight Fragments: off, on, each kind on its own. Changing one plays its sound

**Volume** (each 0 to 100 percent in steps of 10)

- Master: 100 percent. Every sound the mod plays, not the game's own
- Sonar: 50 percent. Changing it plays a sonar sound
- Wall tones: 50 percent
- Shadow sounds: 50 percent. The Shadow cues and the controller layer's tick
- Audio description: 100 percent. The narrator of movies and scenes

**Sound**

- Lower pitch behind you: off, on. The sonar and the Shadow pulse play lower from behind (in top-down mode, from the south)

**Dialogue**

- Voiced dialogue: not read (the voice plays alone), speaker's name only, read aloud. Unvoiced lines are always read. A voiced line is not read even if its voice is silent (voice volume at zero): choose read aloud then. A speaker is named only on the first of their lines in a row
- When a line ends: off, say Next, page turn sound, message chime sound, cursor tick sound. The cue when a line waits for you to continue: on a voiced line when the voice finishes, on an unvoiced one after the reading (a sound plays as the reading begins on screen readers that can't report its end, such as NVDA)
- Read subtitles: off, on. The screen reader reads the subtitles of movies and cutscenes. They are in the log (B) either way. Off by default

**Audio description**

- Movies: off, narrator's voice, screen reader. The animated story movies are described between lines of dialogue: by a narrator, dipping the movie's sound, or as text read by your screen reader. Theurgies follow this setting too: each Theurgy's scene in battle is described as it plays, between the shouts, like a movie
- 3D scenes: off, suppress repeated descriptions, on. The same for the story scenes played in the game's 3D engine. Suppress repeated descriptions reads each description only the first time: a description you have heard is not read again when its scene comes back (a job shift, a meal). What you have heard is kept in seen-descriptions.txt beside settings.ini; delete that file to hear them all again. On by default
- 3D scenes read by: narrator's voice, screen reader
- Faster narrator in 3D scenes: off, 25 percent, 50 percent, 75 percent. The narrator reads the descriptions of 3D scenes that much faster, at the same pitch. The animated movies keep the normal speed: their descriptions are timed between the lines. Off by default
- Each description in a 3D story scene pauses the scene like a message window, with its sounds, and once it is said you hear "Next" (or the sound chosen in "When a line ends"), whether the narrator or your screen reader reads it; Enter, Space or A goes on (pressed while the narrator speaks, it cuts the description short). With the game's Auto on, it goes on by itself once the description is said; fast-forward skips descriptions. These descriptions are in the log (B). A battle's posed moments wait the same way, with a full description: a boss's entrance (what it looks like), a big reveal (the Nyx Avatar's wings turning red, the Great Seal) and a member's first summon; while such a box is up, Tab and the pad's Menu button do nothing. What moves on its own is never paused: the animated movies and Theurgies are described between their lines, and a battle's quick moments (a boss falling, the monorail speeding up) are described as they play, the narrator pausing while a character speaks

**Controls and help**

- Trigger delay: 150 milliseconds; how long one controller trigger waits for the other; off, 100 or 250
- Menu key hints on entry: off, on. Menus say their keys after their first line, besides F1. Off by default
- Menu animation speed: off, 4 times, 8 times, 16 times. While a menu is up (the camp menu, the Velvet Room, shops, the save list and the other menus the mod reads), the game runs that many times faster while the menu is busy, so menus open, close and change sooner and take your keys sooner. A menu waiting for your key runs at normal speed, so idle lines (Igor's, the shopkeepers') keep their pace. The game's menu sounds still play, and the characters on screen (the hero at the fusion table, the camp's party) move at their normal speed. In battle only a menu's opening is sped, before it takes your keys: the command wheel as a turn starts (the game holds its keys for a third of a second) and the battle's lists as they open (the Theurgy list's opening took almost a second); every attack, skill and enemy action keeps its normal speed. Story scenes (the fusion's own scene included) and conversations keep their normal speed. Off by default
- Mod keys: Space or Enter (A) opens the list of the mod's keys, where you can change them (below)

**Language**

- Language of the mod: the game's language, English, 日本語, Français, Italiano, Deutsch, Español, Português, Polski, Türkçe, Русский, 한국어, 简体中文, 繁體中文. Everything the mod says itself (menus, hints, places and portraits, the looks of Personas and Shadows, audio descriptions) in that language; the game's own text is in the game's language either way. On "the game's language" by default: the mod follows the language Steam runs the game in. In any language but English, the descriptions of movies and scenes are read by your screen reader (the narrator's voice speaks English only), so "read by" shows the screen reader. Translations are in `Arcana/assets/lang`; a line with no translation is said in English

**Mod keys** lists every keyboard key of the mod as a row: what it does, then its key ("Walk to the selected point of interest, Apostrophe"). Keys that go back with Shift (Shift+Comma, Shift with a number key) are not listed: they move with their key, so if Comma becomes K, Shift+K goes back. Enter (A) on a row, then press the new key, with Shift if you like (not for a key that goes back with Shift): it is said and saved at once to `%LOCALAPPDATA%\Arcana\keys.ini`. A key another of the mod's actions already uses swaps with it (that action takes your old key, and you hear where it went). The keys the game needs (W A S D and the arrows, Space, Enter, Escape, Backspace, Tab) and Ctrl or Alt chords are refused with the game's buzz, and the row waits for another key. Escape (B) cancels. Delete (X) puts the focused key back on its default; the last row, Reset all keys to default, puts every one back. The first row, Read all keys, reads them all at once, as Shift+F1 does. Escape or Backspace (B) goes back to the settings, on Mod keys; F2 (View) closes the settings. This document names the default keys. The controller's keys (both triggers held) are fixed.

**Sound test** plays each of the mod's sounds with Space or Enter (A), whatever is switched off, and says what it means: each sonar sound (and one played from behind you), the Shadow's growl (plain and hunting), the Shadow alarm and losing you, the Shadow sight sizzle (far, and at the edge) and the hum while a wall hides you, the two strike-reach rings, the four wall tones, the controller tick and the stairs' knocks.

## What is covered

### Story, messages and movies

- Dialogue, inner thoughts ("Thinking: ..."), system notices and their pages, controller notices ("A device was disconnected"). Subtitles of movies and cutscenes only if turned on in the settings.
- Choices: the highlighted answer and its position, as the list appears and on every move ("Go with this, 1 of 2"). A script that asks you to pay (the late-night TV shopping) says the price and your money first ("Price 2980 yen, you have 4800 yen").
- The log (B, in the field or a conversation): each line as you scroll, opening on the newest; Space replays its voice. Lines from before this session are said to be earlier. It also holds what the game's own log leaves out, in the order it was said: the navigator's and the party's remarks while exploring, and audio descriptions. Closing it in a conversation reads the line on screen again.
- The party's voiced chatter while exploring, and the navigator's and party's remarks in battle, are not read over the voices; they stay in the log. Unvoiced lines are read.
- Movies: "Movie paused" (Enter or A pauses and resumes; Tab or the Menu button skips while paused, so twice from a playing movie). Every animated story movie (the anime scenes, both openings, both credit rolls) has audio description: a narrator describes what is on screen between lines, never over dialogue. During the credits, Backslash reads the names on screen. The credits Z (L1) opens from the title menu are announced too: Enter (A) pauses them, and Tab (the Menu button) skips them while they are paused.
- 3D story scenes (the main story, Social Links, outings, Elizabeth's requests, moments in the field and Tartarus) are described too, in the second person ("You walk into the lounge"): a description pauses the scene like a message window until you go on. Scenes whose dialogue already says everything are left quiet. Scenes that repeat (job shifts, meals, studying, the Velvet Room door, Tartarus's golden hand and chests) are described for a first look; set 3D scenes (under Audio description in the mod settings) to suppress repeated descriptions to hear each of them only once. A battle's own scenes (a full moon boss's entrance, the turns of its fight, its fall) are described the same way, with the same settings.
- Cut-ins: a close-up flashed to stress a line is described before it ("Close-up: Yukari, glaring.").
- Pictures shown full screen are described as they appear (a class question's chalkboard, a sketch in the story).
- Semicolon (triggers + B) while someone talks with their portrait up describes them as the portrait shows them now: their look, the outfit (uniform, winter coat, swimsuit, yukata, combat gear...) and how they stand. Every outfit of every character with a portrait is described.
- Semicolon (triggers + B) on a Persona or a Shadow describes how it looks, written from the game's own 3D models: every Persona (the DLC ones too) and every Shadow, recoloured siblings and bosses included, and the people you fight. It works on the enemy or party member under the cursor in battle (a party member: their Persona), any Persona status page (a fusion's result, a level up, the camp's Persona list, Shuffle Time), the fusion and search lists, the compendium (registered entries only) and the registry list.
- Semicolon (triggers + B) on a Social Link in the camp menu, or on its page (the link or one of its people), describes the picture the menu draws beside it: the person, or for the team the collage of faces, which grows as members join. On the old couple's page, each of them has their own.
- Messages (Ctrl, or the morning's "I've got a text message..."): each mail as sender and title, "new" when unread; Space reads it, Escape closes. The reply choice that follows is read like any choice.
- A new day: the date, weekday, time of day and moon as the day-change screen starts ("April 7, Tuesday, Morning. Waxing gibbous moon"), and a new time of day as its screen plays. A date reached any other way (a load, a story jump) is said once you can walk.
- Game over: "Game Over" and the poem are read whole; one press of Space or Enter (A) ends it and goes to the choices, each read with its description.

### Start of the game

- The caution and photosensitivity notices stay up until you press Space or A, instead of moving on after 7 seconds.
- Title screen, title menu and difficulty (with descriptions).
- The contract is a menu ("First name, blank, 1 of 3", "Last name", "Done"). Enter (A) on a name opens it for typing; each letter typed or deleted is said, the left and right arrows, Home and End read the character they land on, up and down read the whole name, and Enter saves. Enter (A) on Done signs. On a controller, A on a name opens the mod's on-screen keyboard (QWERTY: a row of digits, three rows of letters with dash, apostrophe and period, then Space, Capitals, Erase and Done): the D-pad moves across the keys ("w, 2 of 10"; up and down say the row; at an edge a further press says the key again), A types the key, B erases the last letter, Y turns capitals on or off (a name's first letter, and one after a space or dash, is a capital anyway), X reads the name so far, and Start saves the name. The mod's layer (both triggers) works while it is open: triggers + Menu reads these buttons. B with nothing typed closes the keyboard and leaves the name blank. A keyboard still works while it is open. Steam's own controller keyboard (Big Picture, Steam Deck), which a screen reader does not read, is never used here: the mod's keyboard takes its place.

### In the field

- The area when you arrive, with the part and floor the game's banner names ("Iwatodai Dorm, Hallway, floor 2"); the objective when it changes ("Objective: Head to the faculty office").
- Interaction prompts ("Check: Vending Machine", "Go to: Iwatodai Station"; prompts that already say what you do, and devices, by name alone). Over a Social Link partner, their arcana and rank ("Talk: Kenji Tomochika, Magician, rank MAX").
- Items and money gained or spent ("Got Bead times 3, 500 yen"), and party HP or SP changing outside battle.
- Achievements as they unlock, with their name and what they are for ("Achievement unlocked: SEES the Day. Joined the Specialized Extracurricular Execution Squad."), in your Steam language: Steam shows them only in its overlay.
- Describe the area (Semicolon, or triggers + B): a written description of where you stand: every area of the town, the school, the dorm, Yakushima, Kyoto, the full-moon operations, Tartarus and the Abyss of Time. Outdoors it follows the time of day, the season and story changes (the Dark Hour, Christmas, January).
- The town map ("Go Elsewhere") is a numbered list in map order ("Paulownia Mall, 2 of 3"), opening on where you are; the stick still moves around the map and the list follows. Each destination says who is there ("Social Links here: Kenji Tomochika (Magician), rank 1, ready to rank up"). Space picks it, then its entrances (a closed one says so). F lists its shops and places, saying which are unavailable.
- M in town, school and the dorm: "Where should I go?" with the area's destinations and "Town Map" first. Where the story allows no travel, M opens the area map instead (Escape or C closes it). Other town keys: H saves anywhere, Ctrl opens messages, B the log.
- SELECT lists (the shrine's fortune and the like): the activity and question, then each entry. The rooftop garden lists each seedling with how many you own and what it grows, in how many days.

### Points of interest

Points of interest come in categories, each listed nearest first, empty ones skipped:

- Exits: ways into another area, named for where they lead ("Gekkoukan High School" there is the way into the school). Stairs you walk to another floor of the same place are here too ("Stairs to floor 2"); walking onto the floor says "Floor 2". In the July full moon's hotel, its staircases by the floor they lead to ("Stairs to floor 3").
- Doors: rooms you check to go in (classrooms, offices, the dorm's bedrooms). A door between two rooms is listed once, by where it leads.
- People: by name. Social Link partners with their arcana ("Yukari Takeba (Lovers)"), or as the camp describes them before you meet ("Jersey-Wearing Student (Chariot)"). After the name, what the icon over their head says: "something to say" (the game's speech bubble: the students guides tell you to talk to), "overhear" (an ear over people chatting: listen in), "already spoken to" and "already heard" once you have, "Social Link", "Social Link, reversed", "hangout", "Linked Episode", "request", "study group", "walk". Nothing after the name means the game shows no icon over them.
- Shops: businesses, food, vendors and vending machines.
- Objects: everything else you can check, including the glowing Twilight Fragments ("Twilight Fragment") and in Tartarus the crystals that give one ("Twilight Fragment crystal"). Picked up or broken ones leave the list.
- Events: spots that start a fight or scene when you walk into them ("Gatekeeper" on a Gatekeeper's floor until it is beaten; "Large Shadow" where a full moon's operation reaches its boss, such as up the Moonlight Bridge; a door or exit that leads to it says so after its name and is listed here too: "Club Escapade, Large Shadow"), and the place the story sends you when the game marks it on the minimap with a "!": that place is also said with "objective" after its name in its own category ("Faculty Office, objective").
- Shadows, in Tartarus.

A point is read with its name, distance, clock direction (12 o'clock is where pushing forward walks; in top-down mode, the compass) and position: "Iwatodai Station, 6 meters, 2 o'clock, 1 of 3". The category is said first when you change it or open the controller layer. Only the part of the map you are in is listed: your floor, and other floors you can walk to up or down stairs (Mandragora above Paulownia Mall's fountain); past a closed door is listed once you go through. Tartarus lists its whole floor, and its ways on (stairs, teleporters, doors) and its Gatekeeper at any distance, past the range setting.

Auto-walk sets off without a word. On the way, prompts for things you pass are not read; the one up when the walk ends is, so arriving reads the target's as usual. Auto-walk turns you to face what you walked to, so its prompt appears; a breakable object in Tartarus is reached as soon as your strike would break it, faced (the strike-reach ring sounds); stairs and doors end it on the far side. A party member's remark on the way pauses it until you close the remark.

With the sonar on, landing on a point (or Shift+Semicolon) plays its sound alone, repeating at its distance's rhythm from where it is, however far, while the mod's other sounds from places go quiet (the wall tones keep playing). This lasts about 3 seconds (or while you hold the triggers) and ends once you walk.

### Tartarus

- The block and floor ("Thebel, floor 3"); stairs ("Head Up") and the Monad door ("Enter Door") under Exits.
- Shadows by kind ("Shadow", "Strong Shadow", "Rare Shadow", "The Reaper"), with the sound cues under Sounds.
- Chests by kind ("Treasure Chest", "Rare Treasure Chest", "Gold Treasure Chest", "Locked Treasure Chest, 2 Twilight Fragments"); items read as you pick them up; opened chests leave the list.
- Breakable objects; a missing person under People until rescued, named once the police notice shows it ("Missing Person, Ayako Yoshimoto"; walk into them to rescue them), at any distance on the floor.
- Terminals: each floor you can travel to, the furthest marked; Space travels.
- M opens the floor's shortcuts ("Where should I go?"), each once you have found what it leads to: Go to the Next Floor (the stairs; it takes you up from anywhere on the floor), Use the Teleporter (the terminal's floor list), Return to Entrance, Enter Monad. Space takes one; Escape or C closes. With none found yet you hear "No shortcuts found yet" and the floor.
- Auto-Recover (Y, or RB) and the entrance clock read the new HP and SP. N (View on a controller) is the game's Navi: the navigator's support skills, such as Jamming, Escape Route and Tartarus Search, as the story unlocks them. They and the other helpers speak through messages.

### Camp menu

Tab opens and closes it; Escape backs out of a submenu. Each entry reads with its position (the help line is on the details keys); one the story has not opened says "unavailable".

- Item and Skill: items with how many you own; choosing who casts or receives reads each member's HP and SP, then the new HP.
- Equip: in the gear lists F (X) reads the item again with its description.
- Persona: one Persona at a time as its status page, read as lines in sections that Tab and Shift+Tab (RT and LT) jump between: the Persona, arcana, level ("equipped"; Space on this line equips it) and EXP to next level; Stats ("Strength 54"); Skills with costs; Learns later, with levels; Affinities ("Weak to Light", "Repels Fire Wind"). Q and E (LB and RB) switch Persona. The same page is used in the Velvet Room.
- Stats: each member with level, HP, SP and Persona ("Yukari, level 3, HP 74 of 74, SP 61 of 61, 2 of 3, Io, Lovers, level 3"). Once you have more members than the party holds, each says whether they are in party, reserve or the navigator ("Yukari, reserve, level 90, ..."), here and in the member lists of Skill, Item, Equip and the shops. Space opens their page as lines in sections that Tab and Shift+Tab (RT and LT) jump between: the member, your social stats, their Persona, its stats, skills, affinities, and once they know one, their Theurgies (each with its effect) and what fills their gauge; Q and E switch member, or to Tactics ("Yukari: Direct Commands"; Space opens it).
- Theurgy: once someone knows one, Z on a member's page opens the list (on a pad, the page's Theurgy section reads the same) ("Makoto, Cadenza, 1 of 2" and its effect): left and right choose, Q and E (LB and RB) switch character, F (X) reads what fills their gauge. A Social Link event that grants one says so ("New Theurgy: Cyclone Arrow. ..."), and the Personality card a dorm hangout ends on is read: the member, their gauge condition and the characteristic gained ("Characteristic: Buff Boost. Increases the effects of buffs on self.").
- Social Links: the list says when a link is reversed or ready to rank up. Space opens its page on the link and its latest memo, then each person's profile; Q and E switch link.
- Quest: Elizabeth's requests (from May 10, also at her counter): title, then task; F reads the full request and reward; Space accepts. Missing Persons (E): each case with its number, name once known, deadline and status, and the profile of each person identified.
- Calendar: left and right move a day, up and down a week, each day read with its weekday and plans; Q and E change month; F opens the part-time jobs, each with its time, pay, place and whether that day takes it. The calendar on the wall of your dorm room opens the same calendar.
- System: Config (each page, then each setting with its value and position, "Vibration: on, 1 of 24"; left and right change it; Space saves, H restores defaults; Key Configuration reads each binding; BGM rows open a playlist with Space or the right arrow, in two sections that Tab and Shift+Tab jump between: Modes (Default, Random, Favorited, each said with what it does) and Tracks; Space sets one, said as "current"; F (X) plays or stops a track, said as "playing" and "stopped"; E (RB) marks or unmarks a favorite), Dictionary, Tutorial (tabs Q and E switch; button icons read as key names), Save and load, and Rewind (each day you can go back to).
- Save and load: each slot with name, date, time of day, level, location and play time; a clear save says so ("Slot 9: Makoto Yuki, Clear data, start a new game, play time 46 hours 16 minutes").
- Learning a skill (a skill card, or a level up): the skill, then the Persona with its stats and skills; Q and E switch Persona on a skill card's page (a level up keeps its Persona), Space learns. When the eight slots are full the arrows move over them (two columns of four), each read with its cost; Space forgets it, Escape goes back. If a skill is about to change, each change is said ("Bufu would become Spirit Drain").

### Social stats and Social Links

- "Stats up" screens: each stat that rises, and rank ups with the game's rank names.
- A new link in two parts: "New Social Link" as the poem appears, then the link and rank once the card turns ("Strength Social Link, Yuko Nishiwaki, rank 1"). A rank up with no poem says it in one line.
- Points earned in a conversation: "Bond deepened: Magician, 3 points", with "ready to rank up" when the next rank is reached.

### Battles

Each turn uses the game's own keys (F1 names those open this turn). A turn opens with whose turn it is with HP and SP, then the target with its health, buffs, debuffs and the affinities you have found ("Junpei, HP 99, SP 17. Cowardly Maya, 35%, Down, weak to Slash, Fire"); unavailable commands are named. Moving the target adds its place ("1 of 2"); targets do not wrap. Backslash repeats the summary.

- Keys: Space attack, E skills, R items, C guard (asks first), Q analyze, W tactics, Tab rush, A and D or left and right change target, S survey (up and down go through everyone), F assist, T Theurgy when "Theurgy ready" is announced.
- Skill lists read name and cost (a physical skill's cost in HP); Space confirms, Q and E change Persona, F shows its status page. A skill or item that hits a whole side asks once ("Use Mazio Gem on all enemies? Space to confirm, Escape to cancel.").
- What enemies and members acting on their own used, damage, healing and defeats ("2 Cowardly Maya defeated"); on a target you chose, the number alone ("14 damage"). An action that hits the same one several times (a skill that strikes six times, a weapon that hits twice) is said at its last hit, added up ("Makoto 147 damage in all"), not hit by hit. Every number is said as its hit lands. Your own choices are not read back.
- Details of whoever is in focus (Ctrl+Down, right stick): name and level, HP, SP, ailments and buffs with turns left, guarding, affinities found, and for a party member their Persona, stats and Theurgy gauge. In Analyze also its arcana, level, maximum HP and SP, affinities, attack type, skills and drops, as far as the game shows.
- "S.E.E.S. advantage" or "Shadow advantage" at the start; "1 More! Shift available", after which B (Shift) passes the turn; the All-Out Attack prompt once with its buttons.
- Tactics (W): "Give an order?", each member's order, and the orders. Rush (Tab) lets the party fight alone; Tab or C (the Menu button or B) stops it.
- A battle against the clock (the Priestess on the monorail) says the time left at the start, with each of your turns, every 5 minutes, at 1 minute, 30 and 10 seconds, and when the story cuts it short.

### After battles

- Shuffle Time reads every card's effect as they are dealt, with its position, and says when you may take more than one ("choose 1 more"). A skill card says how many you own; a Persona card's status page is read. Arcana Burst's row reads the same ("Arcana Burst. choose 2"; C cancels the last pick).
- Persona Overstock: the new Persona ("Gain: ...") and each one you hold; Space releases the one chosen, F shows its stats (there Q and E go through them and Space releases the one shown).
- The victory screen reads each thing as its own line you can go back over with the arrows: EXP, money, items, each level up, the hero's level-up page, and the status page of a Persona that learned a skill. Space or Enter goes on.

### Velvet Room

- Its menu (Fusion, Summon from the Compendium, Register to the Compendium) and the fusion method.
- Dyad Fusion: each Persona with arcana and level; on the second list each row also says what the pair makes ("Apsaras, Priestess, level 2, makes Nekomata, Magician, level 3") or "cannot fuse", and whether it is above your level or already in stock. Right and Left step through the result's details.
- The result page is the status page, with the Social Link bonus ("Social Link bonus: rank 8, 32793 EXP, up to level 28"); Q and E page to the materials.
- Inheritance: "Choose skills to inherit, up to 2.", each skill with its cost, and "chosen, 1 of 2 picks" as you choose; Igor's "Is this Persona acceptable?" adds what it inherits. "Fusing." marks the animation. Tab (the Menu button) pauses it and offers to skip it: "Paused. Tab skips, Escape resumes." Tab again skips to the new Persona. The bonus level up is a page too ("Agility 21, up 7", new skills marked "new").
- Fusion Search names each Persona your stock can make and from which two; Special Fusion lists recipes with materials and how many you have.
- The compendium reads registered Personas with their price and says which are in your stock (one not registered yet is "Unknown"); Registration lists your Personas, then their status page.

### Shops

- Weapon and item shops: items with price and stats, descriptions, how many you own, why a row can't be bought ("not enough yen", "out of stock"), "How many?" with the total as you change it (up and down by one, left and right by ten), and the buy and equip prompts.
- Mayoido Antiques (from July): Fuse Equipment, Trade Card, Trade Item, each entry with how many you own, its stats and what the trade needs ("needs Topaz 3, you have 1").
- Vending machines say how many are left. Be Blue V's job is read as choices. Its treatment (a teammate relearns a forgotten skill) reads the forgotten skills with their cost and what they do ("Isis: Relearn a skill. Garu, 3 SP, 1 of 6"); Enter on one moves to the slots to choose the skill it replaces, and the swap is said ("Learned Garu, in place of Pulinpa").

## Top-down exploration

The game's camera sits behind the hero and turns, so a sound "ahead" kept changing direction. Top-down mode (always on while you walk freely) presents the field the way Dark Vision does:

- While you walk freely the camera faces north and cannot turn. The scene cameras some places switch to (by the Velvet Room's door, the station, your room) are turned off, so the north camera shows everywhere. Up always walks north.
- The game's sounds and the mod's are heard from where you stand with north ahead, as if from above.
- North is the corner map's up, place by place: where the game draws a map turned (Port Island Station, your room, the Command Room), north turns with it.
- Where the game moves you into a room turned around, that room is turned so the way you walked in stays up (the Keep your heading through passages setting, on by default). The back alley to the Velvet Room: walk north up the passage from Fountain Square, and up keeps leading along the alley to the door while down leads back out. The school rooftop: its stairs turn back on themselves, so on the roof up leads away from the stairwell door and down leads back to it. Compass words in a turned room follow the turn. Only rooms with a single way in whose turn the game's own data gives exactly are turned.
- The wall tones are a compass: north, east, south and west, reaching as far as the Wall tone range setting (5 m by default). All four sound while you move, the wall behind you too; standing still, they sound with Wall tones on Continuous.
- Points of interest give compass directions ("north-east"), and the right stick scans (see On a controller).

Conversations, story scenes, menus and battles keep the game's own camera and sound.

## Sounds

- **Wall tones:** four looping tones for how close walls are: ahead and behind (centered, different pitches), right and left. Louder is closer; silence is open space. By default they play only while you move (the stick, the keys or the auto-walk, even pushing into a wall) and are quiet while you stand still; set Wall tones to Continuous to hear them all the time. Each measures how far you could actually go that way, so a wall you would slide along stays quiet.
- **Sonar:** every point of interest in range (10 m by default) repeats its own sound from where it is, faster and louder as you get closer: about once a second at 10 m, nearly twice at 5 m, nearly seven times at 1 m. A thing is heard from its part nearest you, so a long counter or wide exit sounds from beside you (the list's distance and direction are to that part too); inside its area, in the middle (from no side) at the quickest rhythm. Sounds play whole, overlapping when fast. Exits, objects, events and Twilight Fragments use Grim Dark's sounds (its dungeon entrance, interactable, ruined shrine and loot). Doors are a hollow knock, people a whistled "yoo-hoo", shops a till's ching. Directions follow the camera (or north, in top-down mode). To keep crowds readable, at most four things sound at once, two of a kind; the selected point always has a place, and anything within 2.5 m makes the rest quieter. Things on another floor or past a closed door are left out until you can reach them. Stairs to another floor of the same place (the Strip Mall, Paulownia Mall, Club Escapade) have their own sound: four wooden knocks climbing like rungs, from where you step onto the stairs (walk at it and you are on them; on the stairs it stays a couple of metres ahead, round their turns), at the same quickening rhythm as everything else. The sonar is silent in menus, conversations, story scenes and battles.
- **Focus ping:** whenever something is focused (chosen in the list with the bracket keys, Comma or a number key, said again with Shift+Semicolon, or found with the right stick), Grim Dark's route ping plays once from where it is: one sound when you can see it and walk straight there, another when the way goes round something, and a third when there is no way from here (another floor, or behind a closed door). With the sonar on, the thing's own sound then repeats as before. The ping plays with the sonar off too.
- **Shadow sound:** in Tartarus, the nearest Shadow within 30 m snarls steadily from where it is, louder as it gets closer and higher while it hunts you. Its facing changes the sound, not its pitch: bright when it faces you, duller as it turns away, and once you are behind it (more than 90 degrees off its front, where a strike brings the advantage) muffled and wobbling. Follow the wobble to sneak up on it. The game's own sound tells you when one notices you; a soft falling note means it lost you. Within 4 m you also hear whether it has its back turned or is facing you.
- **Strike reach:** while a Shadow is inside your strike's reach (the game's own hit area: the moment any of the Shadow's body touches it), a quick steel ring repeats in the middle of your head: attack now and it connects. With Strike assist on, this counts every side, since the assist turns you to the Shadow as you swing: a Shadow closing in from behind rings as soon as a strike would reach it. When you are also behind it, a glassy upward tick plays instead: the strike gives the advantage. A breakable object rings the same way. Part of Shadow alerts.
- **Shadow sight:** in Tartarus, each nearby Shadow's sight is a zone on the ground, and it sizzles from its edge nearest you, heard from where that edge is. While the edge is within the Shadow sight range (10 m by default) it plays all the time, louder and higher by an even step for every metre nearer, loudest at the edge, so you hear it close in or fall away as you walk; step over it and the Shadow notices you. The three nearest zones sound at once. The zone is the game's own: how far and how wide each Shadow sees for its mood (an angry one sees farther, but only to its front), the wider sight it has while you dash (holding Shift), so the edge audibly pulls back when you slow to a run, and the walls that block its view, which cut the zone. Turning moves it too: walk round a Shadow and you hear its sight swing with it. While you stand where a Shadow would see you but a wall blocks its view, a muffled hum plays: step out past the corner and it sees you. Only Shadows that are wandering, and so looking, are heard: one chasing you already knows where you are. Nothing sounds while Fuuka's Jamming hides you. The sounds are Grim Dark's harmful-ground sounds (its sizzle, and its "standing in it" bed, played muffled). Its own setting, on by default.
- **Strike assist:** in Tartarus, when you attack with a Shadow close enough that your strike would reach it if you faced it, from any side, you turn to face it as the swing starts. Your reach stays the same: it only aims. A Shadow hunting you comes first, then the nearest. With no Shadow in reach it turns you to the nearest breakable object your strike would reach, and the ring counts every side for those too. Its own setting, on by default.

Placed sounds stay where they are while they play, so they shift and grow louder or quieter as you move. They are placed the way Dark Vision places them: left and right by level and by the moment each ear hears a sound, sounds behind you darker, and louder the nearer they are (half as loud at 3 meters as beside you, a quarter at 9), so a few steps toward a Shadow or away from it are heard.

## Known limits

A game update can break the mod. The full list, including what has not been tried yet, is in [KNOWN_ISSUES.md](KNOWN_ISSUES.md).

## Reporting bugs

Please open an issue at https://github.com/ChipsAhoiMcCoy/arcana/issues with:

- What you did, what you heard, and what you expected.
- Your screen reader, and keyboard or controller.
- The log, `%LOCALAPPDATA%\Arcana\arcana.log` (after a restart, the previous session is `arcana.last-play.log`). It holds what the mod spoke, including story text, and may show your Windows user name, so look it over before sharing.

## Credits

Arcana builds on Grim Dark by Austin Hicks and Dark Vision by Bradley Renshaw. It uses Prism, Steam Audio, Microsoft Detours and miniaudio. The movie narrator is the Kokoro voice model's af_heart voice. Thanks to the Persona 3 Reload modding community. See [CREDITS.md](CREDITS.md) and [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).

## License

The mod's code is under the zlib license ([LICENSE](LICENSE)). Parts from other projects keep their own licenses, listed in [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md). The license covers the mod only, not the game.
