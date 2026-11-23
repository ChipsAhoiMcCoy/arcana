# Translating Arcana

Arcana speaks the game's own text in the game's language. Everything it writes itself is written in English and
looked up, line by line, in a table for the player's language:

- menus, hints and announcements (`src/core/strings.h`),
- the area descriptions, the dialogue portraits, the looks of Personas and Shadows, the Social Link pictures,
- the audio description of the movies and story scenes (`assets/ad/*.txt`).

In any language but English the audio descriptions are read by the screen reader: the recorded narrator speaks
English only.

## The tables

`assets/lang/<code>/*.tsv`, one line per translated line:

```
English text<TAB>translated text
```

A tab, a line break and a backslash inside a text are written `\t`, `\n` and `\\`. The English side must be exactly
the catalogue's line (copy it, do not retype it); a line with no translation is said in English. The file names do not
matter: every `.tsv` in the folder is read.

Codes: `ja` Japanese, `fr` French, `it` Italian, `de` German, `es` Spanish, `pt` Brazilian Portuguese, `pl` Polish,
`tr` Turkish, `ru` Russian, `ko` Korean, `zh-Hans` Simplified Chinese, `zh-Hant` Traditional Chinese.

```
python tools/lang.py extract           the English catalogue (build/lang/catalogue.tsv)
python tools/lang.py status            how much each language has
python tools/lang.py todo es           the missing lines, in chunks (build/lang/todo/es/)
python tools/lang.py check es          placeholders kept, nothing stale
```

## How to write

Everything is heard through a screen reader, often at speed, by a player who cannot see the screen.

- **The game's own words.** Names of people, places, Personas, Shadows, arcana, items, skills and story terms
  (Dark Hour, Tartarus, SEES, Social Link, Velvet Room, Theurgy, Shuffle Time) as the game's translation in that
  language has them. Menu names as the game's menus call them.
- **Short and spoken.** Plain words, short sentences, no abbreviations a screen reader would spell out. Keep each
  line's meaning and nothing more: no added explanation, nothing left out.
- **Placeholders.** `{}`, `{sonar}` and every other `{...}` stay as they are, as many as the English has; their order
  may change only where the language needs it and the placeholder is named. Numbers come from the mod.
- **Fragments.** Some lines are pieces the mod joins with others ("of" in "2 of 5", "times" in "Got Bead times 3",
  a menu name before its position). `src/core/strings.h` shows each line's comment and name: read it to see how a
  piece is used, and translate it so the joined line reads well.
- **Contexts.** A line written `@context:text` is a word the English uses in two roles (`@target:on` in "Weak on
  Junpei", where plain `on` is a setting's value). Translate only the text after the colon; the context is never said.
- **Dates.** `{month} {day}{th}` is a date: `{th}` is English's ordinal ending (st, nd, rd); leave it out where the
  language has none, and put the day and the month in the language's order.
- **Keys.** Keyboard keys keep the names printed on them (Enter, Tab, Shift, Ctrl, Alt, Esc, F1); Space, the arrows,
  Page Up and Page Down as the language usually names them. Controller buttons keep their letters and Xbox names (A, B,
  X, Y, LB, RB, LT, RT, View, Menu); the D-pad and the sticks as the language usually names them.
- **Descriptions** (areas, portraits, looks, audio description): present tense; the player is "you", in the familiar
  form where the language has one. Keep the tone: vivid, concrete, a little warm; adult characters described as the
  English describes them, no more and no less.
- **Punctuation.** The language's own (Japanese and Chinese full-width, French spacing before `:` and `?` is fine).
  A line never ends with a comma or a stray space.
