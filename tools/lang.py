"""The mod's own text in other languages (src/core/lang.cpp reads the tables).

Every line the mod writes itself is looked up by its English text in assets/lang/<code>/*.tsv
(one "English<TAB>translation" a line; \\t, \\n and \\\\ escaped). A line with no translation is said in English.

  python tools/lang.py extract            the English catalogue -> build/lang/catalogue.tsv (source, English)
  python tools/lang.py status             how much of the catalogue each language has
  python tools/lang.py todo <code> [--size N] [--source S]
                                          the missing lines in chunks of about N bytes -> build/lang/todo/<code>/NNN.tsv
  python tools/lang.py check [<code>]     every table: placeholders kept, no stray tabs, no line the catalogue lacks
"""
import argparse
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LANGS = ["ja", "fr", "it", "de", "es", "pt", "pl", "tr", "ru", "ko", "zh-Hans", "zh-Hant"]
NAMES = {"ja": "Japanese", "fr": "French", "it": "Italian", "de": "German", "es": "Spanish", "pt": "Brazilian Portuguese",
         "pl": "Polish", "tr": "Turkish", "ru": "Russian", "ko": "Korean", "zh-Hans": "Simplified Chinese",
         "zh-Hant": "Traditional Chinese"}


def esc(s):
    return s.replace("\\", "\\\\").replace("\t", "\\t").replace("\n", "\\n").replace("\r", "")


def unesc(s):
    out, i = [], 0
    while i < len(s):
        c = s[i]
        if c == "\\" and i + 1 < len(s):
            n = s[i + 1]
            out.append({"t": "\t", "n": "\n", "\\": "\\"}.get(n, "\\" + n))
            i += 2
        else:
            out.append(c)
            i += 1
    return "".join(out)


def c_literals(path):
    """Every string literal of a C++ file, adjacent ones joined, decoded to text (UTF-8 bytes)."""
    src = open(path, encoding="utf-8", newline="").read()
    i, n = 0, len(src)
    out = []
    cur = None          # bytes of the literal being joined
    pending_gap = False
    while i < n:
        c = src[i]
        if src.startswith("//", i):
            j = src.find("\n", i)
            i = n if j < 0 else j
            continue
        if src.startswith("/*", i):
            j = src.find("*/", i + 2)
            i = n if j < 0 else j + 2
            continue
        if c == "'":
            j = i + 1
            while j < n and src[j] != "'":
                j += 2 if src[j] == "\\" else 1
            i = j + 1
            if cur is not None: out.append(cur); cur = None
            continue
        if c == '"':
            # a raw prefix (u8, L, R) is not used for spoken text here
            j = i + 1
            buf = bytearray()
            while j < n and src[j] != '"':
                ch = src[j]
                if ch == "\\":
                    e = src[j + 1]
                    if e == "x":
                        m = re.match(r"[0-9A-Fa-f]{1,2}", src[j + 2:])
                        buf.append(int(m.group(0), 16)); j += 2 + len(m.group(0)); continue
                    if e in "01234567":
                        m = re.match(r"[0-7]{1,3}", src[j + 1:])
                        buf.append(int(m.group(0), 8)); j += 1 + len(m.group(0)); continue
                    buf += {"n": b"\n", "t": b"\t", "\\": b"\\", '"': b'"', "'": b"'", "r": b"\r", "0": b"\0"}.get(e, e.encode())
                    j += 2
                    continue
                buf += ch.encode("utf-8")
                j += 1
            cur = (cur or b"") + bytes(buf)
            i = j + 1
            continue
        if c.isspace():
            i += 1
            continue
        if cur is not None:
            out.append(cur)
            cur = None
        i += 1
    if cur is not None:
        out.append(cur)
    res = []
    for b in out:
        try:
            res.append(b.decode("utf-8"))
        except UnicodeDecodeError:
            pass
    return res


IDENT = re.compile(r"^[A-Za-z0-9_./\\:%-]*$")


def spoken(s, min_words=1):
    if not s.strip() or len(s) < 2:
        return False
    if "_" in s and " " not in s:
        return False          # an asset or object name
    if s.startswith(("/", "%", "#")) or s.endswith((".wav", ".mp3", ".txt", ".ini", ".dll", ".h")):
        return False
    if not re.search(r"[A-Za-z]", s):
        return False
    return len(s.split()) >= min_words


def catalogue():
    seen, rows = set(), []

    def add(source, s):
        if s not in seen:
            seen.add(s)
            rows.append((source, s))

    for s in c_literals(os.path.join(ROOT, "src", "core", "strings.h")):
        if spoken(s):
            add("strings", s)
    for name in ("area", "look", "portrait"):
        for s in c_literals(os.path.join(ROOT, "src", "core", f"{name}_entries.inc")):
            if spoken(s, 3):
                add(name + "s", s)
    for s in c_literals(os.path.join(ROOT, "src", "core", "social_art.cpp")):
        if spoken(s, 3):
            add("social-art", s)
    for p in sorted(glob.glob(os.path.join(ROOT, "assets", "ad", "*.txt"))):
        key = os.path.basename(p)[:-4]
        group = "ad-" + ("movies" if key.startswith("MS_") else key.split("_")[2].lower())
        for line in open(p, encoding="utf-8"):
            parts = line.rstrip("\r\n").split("\t", 3)
            if len(parts) == 4 and parts[3].strip():
                add(group, parts[3])
    return rows


def tables(code):
    t = {}
    for p in sorted(glob.glob(os.path.join(ROOT, "assets", "lang", code, "*.tsv"))):
        for k, line in enumerate(open(p, encoding="utf-8", newline=""), 1):
            line = line.rstrip("\r\n")
            if not line or "\t" not in line:
                continue
            en, tr = line.split("\t", 1)
            t[unesc(en)] = (unesc(tr), os.path.basename(p), k)
    return t


def cmd_extract(_):
    rows = catalogue()
    os.makedirs(os.path.join(ROOT, "build", "lang"), exist_ok=True)
    with open(os.path.join(ROOT, "build", "lang", "catalogue.tsv"), "w", encoding="utf-8", newline="\n") as f:
        for src, s in rows:
            f.write(f"{src}\t{esc(s)}\n")
    by = {}
    for src, s in rows:
        n, b = by.get(src, (0, 0))
        by[src] = (n + 1, b + len(s.encode()))
    for src, (n, b) in by.items():
        print(f"{src:14} {n:6} lines {b / 1024:8.1f} KB")
    print(f"{'total':14} {len(rows):6} lines {sum(len(s.encode()) for _, s in rows) / 1024:8.1f} KB")


def cmd_status(_):
    rows = catalogue()
    total = sum(len(s.encode()) for _, s in rows)
    for code in LANGS:
        t = tables(code)
        have = sum(len(s.encode()) for _, s in rows if s in t)
        print(f"{code:8} {NAMES[code]:22} {sum(1 for _, s in rows if s in t):6}/{len(rows)} lines {100 * have / total:5.1f}% of text")


def cmd_todo(a):
    t = tables(a.code)
    rows = [(src, s) for src, s in catalogue() if s not in t and (not a.source or src.startswith(a.source))]
    out = os.path.join(ROOT, "build", "lang", "todo", a.code)
    os.makedirs(out, exist_ok=True)
    for p in glob.glob(os.path.join(out, "*.tsv")):
        os.remove(p)
    chunk, size, k = [], 0, 0

    def flush():
        nonlocal chunk, size, k
        if chunk:
            k += 1
            with open(os.path.join(out, f"{k:03}.tsv"), "w", encoding="utf-8", newline="\n") as f:
                for src, s in chunk:
                    f.write(f"{src}\t{esc(s)}\n")
        chunk, size = [], 0

    last = None
    for src, s in rows:
        if size >= a.size or (last and src != last and size > a.size // 2):
            flush()
        chunk.append((src, s))
        size += len(s.encode())
        last = src
    flush()
    print(f"{a.code}: {len(rows)} lines missing, {k} chunks in {out}")


PH = re.compile(r"\{[a-z_0-9]*\}")


def cmd_check(a):
    cat = {s for _, s in catalogue()}
    bad = 0
    for code in [a.code] if a.code else LANGS:
        t = tables(code)
        stale = 0
        for en, (tr, f, k) in t.items():
            if en.startswith(("@place:", "@word:")):
                continue   # the game's own words (places.tsv, words.tsv), for matching its text
            if en not in cat:
                stale += 1
                continue
            if sorted(PH.findall(en)) != sorted(PH.findall(tr)) and not (en == "{month} {day}{th}" and set(PH.findall(tr)) <= {"{month}", "{day}", "{th}"} and "{day}" in tr and "{month}" in tr):
                print(f"{code} {f}:{k}: placeholders differ: {en!r} -> {tr!r}"); bad += 1
            if not tr.strip():
                print(f"{code} {f}:{k}: empty"); bad += 1
        if stale:
            print(f"{code}: {stale} lines no longer in the catalogue (English changed)")
    sys.exit(1 if bad else 0)


CJK = {"ja", "ko", "zh-Hans", "zh-Hant"}
NAMES_KEPT = ("Yukari", "Junpei", "Akihiko", "Mitsuru", "Fuuka", "Aigis", "Koromaru", "Shinjiro", "Elizabeth",
              "Metis", "Kazushi", "Kenji", "Bebe", "Chihiro", "Hidetoshi", "Ryoji", "Pharos")


def cmd_align(a):
    """Lines whose translation does not look like their English: a length far off, or a number missing. A run of them
    in one file means its lines slipped out of step."""
    for code in [a.code] if a.code else LANGS:
        by_file = {}
        for en, (tr, f, k) in tables(code).items():
            if len(en) < 40 or en.startswith("@"):
                continue
            r = len(tr) / len(en)
            lo, hi = (0.12, 0.9) if code in CJK else (0.55, 2.0)
            nums = set(re.findall(r"\d+", en))
            bad = bool(r < lo or r > hi or (nums and not nums <= set(re.findall(r"\d+", tr))))
            # the cast's names stay in Latin-script languages: a line naming someone the translation does not
            # (outside Russian and the CJK languages, which write them in their own script)
            if code not in CJK and code != "ru":
                for name in NAMES_KEPT:
                    if re.search(r"\b" + name + r"\b", en) and name not in tr:
                        bad = True
            by_file.setdefault(f, []).append((k, bad, en, tr))
        for f, rows in sorted(by_file.items()):
            rows.sort()
            n = sum(b for _, b, _, _ in rows)
            run, worst = 0, 0
            for _, b, _, _ in rows:
                run = run + 1 if b else 0
                worst = max(worst, run)
            if n:
                print(f"{code}/{f}: {n} of {len(rows)} odd, longest run {worst}")
                if a.show:
                    for k, b, en, tr in rows:
                        if b:
                            print(f"   {k}: {en[:70]!r} -> {tr[:70]!r}")


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("extract")
    sub.add_parser("status")
    p = sub.add_parser("todo"); p.add_argument("code"); p.add_argument("--size", type=int, default=40000); p.add_argument("--source")
    p = sub.add_parser("check"); p.add_argument("code", nargs="?")
    p = sub.add_parser("align"); p.add_argument("code", nargs="?"); p.add_argument("--show", action="store_true")
    a = ap.parse_args()
    {"extract": cmd_extract, "status": cmd_status, "todo": cmd_todo, "check": cmd_check, "align": cmd_align}[a.cmd](a)


if __name__ == "__main__":
    main()
