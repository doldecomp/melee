#!/usr/bin/env python3
"""
Inventories the cleanup surface of the source tree: pointer casts, byte-offset
walks, m2c field-access macros, MUST_MATCH regions and compiler pragmas.

Each site is classified once by its outermost form, so `*(f32*) ((u8*) p + 0xE0)`
counts as one cast+offset rather than as three separate casts. The sites that move
a pointer by a literal constant are the ones worth chasing: each is a struct field
that has not been named yet.

Usage:
    python tools/cleanup_index.py                       # summary to stdout
    python tools/cleanup_index.py --tsv -               # TSV to stdout
    python tools/cleanup_index.py --out build/cleanup-index # index.html + cleanup_index.tsv
"""

import argparse
import bisect
import json
import re
import sys
from collections import Counter
from pathlib import Path
from typing import Iterator, NamedTuple, Optional

ROOT = Path(__file__).resolve().parent.parent
TEMPLATE = Path(__file__).resolve().parent / "cleanup-index-template.html"

# Types that never name a struct, used to split plain casts into two buckets.
PRIMITIVES = {
    "u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64",
    "char", "short", "int", "long", "void", "unsigned", "signed",
    "float", "double", "uintptr_t", "intptr_t", "size_t", "bool",
}

# A type name as it appears inside a cast, e.g. `const struct Foo`, `unsigned long`.
TYPE = (
    r"(?:const\s+|volatile\s+|struct\s+|union\s+|unsigned\s+|signed\s+)*"
    r"[A-Za-z_]\w*(?:\s+(?:int|char|long|short))?"
)

CAST = re.compile(r"\(\s*(" + TYPE + r")\s*(\*+)\s*\)\s*(?=[A-Za-z_&(*])")
OFFSET = re.compile(
    r"\(\s*(" + TYPE + r")\s*(\*+)\s*\)\s*"          # the cast
    r"\(?\s*&?[A-Za-z_][\w.\[\]]*(?:\s*->\s*\w+)*\s*\)?"  # the operand
    r"\s*([-+])\s*(0[xX][0-9a-fA-F]+|\d+)\b"         # the constant
)
DEREF = re.compile(r"(?<![\w\)\]])\*\s*\(\s*(" + TYPE + r")\s*(\*+)\s*\)")
INDEX = re.compile(r"\(\s*\(\s*(" + TYPE + r")\s*(\*+)\s*\)[^()]{1,40}\)\s*\[")
ABSOLUTE = re.compile(r"\(\s*(" + TYPE + r"\s*\*+)\s*\)\s*\(?\s*(0[xX][0-9a-fA-F]{6,8})\b")
# Narrow casts are excluded: a pointer is never truncated to u8 or s16.
TO_INT = re.compile(
    r"\(\s*(u32|s32|int|long|unsigned int|unsigned long|uintptr_t|size_t)\s*\)"
    r"\s*(&?)\s*([A-Za-z_]\w*)\s*(?![\w.\[]|->)"
)
BARE_OFFSET = re.compile(r"(?<![\w.>])([A-Za-z_]\w*)\s*([-+])\s*(0[xX][0-9a-fA-F]+)\b")
DECL = re.compile(r"\b[A-Za-z_]\w*\s*\*+\s*(?:const\s+)?([A-Za-z_]\w*)\s*(?=[,;)=\[])")
SIZEOF = re.compile(r"\bsizeof\s*$")
M2C_FIELD = re.compile(r"\bM2C_FIELD\s*\(")
MUST_MATCH_IF = re.compile(r"^[ \t]*#[ \t]*(if|ifdef|ifndef|elif)\b.*\bMUST_MATCH\b")
DIRECTIVE = re.compile(r"^[ \t]*#[ \t]*(\w+)")
PRAGMA = re.compile(r"^[ \t]*#[ \t]*pragma[ \t]+(.*?)[ \t]*$")
ORDER_FN = re.compile(r"\bstatic\s+\w+\s+(order_\w+|\w+_order\w*)\s*\(")
HELPER_FN = re.compile(r"\bstatic\s+(?:inline\s+)?[\w* ]+?\b(\w+)\s*\(")
STACK_PAD = re.compile(r"\bPAD_STACK\s*\(([^)]*)\)")
DEFINE = re.compile(r"^#\s*define\s+(\w+)", re.M)

# (name, shape, family). The family drives the colour on the page: `move` sites
# walk a pointer by a constant, `retype` sites only change its type, and `hack`
# regions are compiled only in the matching build.
CATEGORIES = [
    ("cast+offset", "(T*)p + 0xNN", "move"),
    ("cast+index", "((T*)p)[n]", "move"),
    ("raw-offset", "p + 0xNN, p typed", "move"),
    ("m2c-field", "M2C_FIELD(p, T*, off)", "move"),
    ("abs-address", "(T*)0xNNNNNNNN", "move"),
    ("struct-ptr-cast", "(Struct*)p", "retype"),
    ("prim-ptr-cast", "(u8*)p, (void*)p", "retype"),
    ("deref-cast", "*(T*)p", "retype"),
    ("ptr-to-int", "(u32)p", "retype"),
    ("must-match", "#ifdef MUST_MATCH", "hack"),
    ("pragma", "#pragma, not push/pop", "hack"),
]
FAMILY = {name: family for name, _, family in CATEGORIES}


class Site(NamedTuple):
    category: str
    file: str
    line: int
    type: str
    detail: str
    source: str


def blank_noise(text: str) -> str:
    """Replace comments and literals with spaces, keeping every offset intact."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            while i < n and text[i] != "\n":
                out[i] = " "
                i += 1
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            out[i] = out[i + 1] = " "
            i += 2
            while i < n and not (text[i] == "*" and i + 1 < n and text[i + 1] == "/"):
                if text[i] != "\n":
                    out[i] = " "
                i += 1
            if i < n:
                out[i] = out[i + 1] = " "
                i += 2
        elif c in "\"'":
            quote = c
            out[i] = " "
            i += 1
            while i < n and text[i] != quote:
                if text[i] == "\\":
                    out[i] = " "
                    i += 1
                    if i < n and text[i] != "\n":
                        out[i] = " "
                    i += 1
                    continue
                if text[i] != "\n":
                    out[i] = " "
                i += 1
            if i < n:
                out[i] = " "
                i += 1
        else:
            i += 1
    return "".join(out)


def pointer_names(text: str):
    """Map a position to the identifiers declared as pointers visible from it.

    Declarations are collected per top-level brace body (a function, plus the
    signature that precedes it) so that an `arg0` that is a pointer in one
    function is not assumed to be one in the next.
    """
    spans, depth, start = [], 0, None
    for i, ch in enumerate(text):
        if ch == "{":
            if depth == 0:
                start = i
            depth += 1
        elif ch == "}":
            depth = max(depth - 1, 0)
            if depth == 0 and start is not None:
                spans.append((start, i))
                start = None

    file_scope: set[str] = set()
    bodies: list[tuple[int, int, set[str]]] = []
    prev = 0
    for a, b in spans:
        head_start = max(prev, text.rfind(";", prev, a) + 1, text.rfind("}", prev, a) + 1)
        names = {m[1] for m in DECL.finditer(text[head_start:a])}
        names |= {m[1] for m in DECL.finditer(text[a:b])}
        bodies.append((a, b, names))
        file_scope |= {m[1] for m in DECL.finditer(text[prev:a])}
        prev = b
    file_scope |= {m[1] for m in DECL.finditer(text[prev:])}

    starts = [b[0] for b in bodies]

    def visible(pos: int) -> set[str]:
        k = bisect.bisect_right(starts, pos) - 1
        if k >= 0 and bodies[k][0] <= pos <= bodies[k][1]:
            return bodies[k][2] | file_scope
        return file_scope

    return visible


def classify(ty: str) -> str:
    bare = re.sub(r"\b(const|volatile|struct|union)\b", "", ty).strip()
    head = bare.split()[0] if bare.split() else bare
    return "prim-ptr-cast" if head in PRIMITIVES else "struct-ptr-cast"


def macro_args(text: str, open_paren: int) -> list[str]:
    """Split the arguments of the call whose `(` sits at open_paren."""
    args, depth, arg_start = [], 0, open_paren + 1
    for i in range(open_paren, len(text)):
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                args.append(text[arg_start:i].strip())
                return args
        elif c == "," and depth == 1:
            args.append(text[arg_start:i].strip())
            arg_start = i + 1
    return args


def must_match_regions(lines: list[str]) -> Iterator[tuple[int, str, list[str]]]:
    """Yield (directive index, directive, body lines) for each MUST_MATCH region.

    The body runs to the matching #else/#elif/#endif; nested conditionals are
    skipped over so they cannot end the region early.
    """
    for i, line in enumerate(lines):
        m = MUST_MATCH_IF.match(line)
        if not m:
            continue
        body, depth = [], 0
        for j in range(i + 1, len(lines)):
            d = DIRECTIVE.match(lines[j])
            name = d[1] if d else ""
            if name in ("if", "ifdef", "ifndef"):
                depth += 1
            elif name == "endif":
                if depth == 0:
                    break
                depth -= 1
            elif name in ("else", "elif") and depth == 0:
                break
            body.append(lines[j])
        yield i, m[1], body


def pragma_sites(lines: list[str]) -> Iterator[tuple[int, str, bool]]:
    """Yield (line index, pragma text, guarded) for each pragma that is not
    push/pop plumbing. `guarded` is true inside a MUST_MATCH branch, including
    the #else of an #ifndef MUST_MATCH.
    """
    # One entry per open conditional: "on" inside a MUST_MATCH branch,
    # "off" inside the branch that excludes it, None if unrelated.
    stack: list[Optional[str]] = []
    for i, line in enumerate(lines):
        d = DIRECTIVE.match(line)
        if not d:
            continue
        name = d[1]
        if name in ("if", "ifdef", "ifndef"):
            if MUST_MATCH_IF.match(line):
                stack.append("off" if name == "ifndef" else "on")
            else:
                stack.append(None)
        elif name == "elif" and stack:
            stack[-1] = "on" if MUST_MATCH_IF.match(line) else None
        elif name == "else" and stack:
            stack[-1] = {"on": "off", "off": "on"}.get(stack[-1])
        elif name == "endif" and stack:
            stack.pop()
        elif name == "pragma":
            text = PRAGMA.match(line)[1]
            if text not in ("push", "pop"):
                yield i, text, "on" in stack


def classify_hack(body: list[str]) -> Optional[tuple[str, str]]:
    """Return (kind, detail) for a MUST_MATCH body, or None if the region holds
    nothing but pragmas, which are indexed on their own by pragma_sites().
    """
    stripped = [l.strip() for l in body if l.strip()]
    code = [l for l in stripped if not l.startswith("#")]
    code_text = "\n".join(code)

    if not code:
        return None
    # Data-order functions are named order_* by convention, but any static
    # function whose body is only `(void) literal;` statements is one.
    if m := ORDER_FN.search(code_text):
        return "data order", m[1]
    if re.search(r"^\(void\)", code_text, re.M) and (m := HELPER_FN.search(code_text)):
        return "data order", m[1]
    if re.search(r"\basm\b", code_text):
        return "asm", ""
    if m := STACK_PAD.search(code_text):
        return "stack pad", f"PAD_STACK({m[1].strip()})"
    if m := DEFINE.search("\n".join(stripped)):
        return "macro", m[1]
    if m := HELPER_FN.search(code_text):
        return "helper", m[1]
    return "code", ""


def scan_file(path: Path, rel: str) -> Iterator[Site]:
    raw = path.read_text(encoding="utf-8", errors="replace")
    text = blank_noise(raw)
    lines = raw.split("\n")
    blank_lines = text.split("\n")

    offsets, acc = [], 0
    for line in blank_lines:
        offsets.append(acc)
        acc += len(line) + 1

    claimed: dict[int, int] = {}
    found: list[Site] = []

    def source_at(line: int) -> str:
        return lines[line - 1].strip()[:150] if line - 1 < len(lines) else ""

    def emit(category: str, start: int, ty: str, detail: str, rank: int) -> None:
        if claimed.get(start, -1) >= rank:
            return
        claimed[start] = rank
        line = bisect.bisect_right(offsets, start)
        found.append(Site(
            category, rel, line, re.sub(r"\s+", " ", ty).strip(),
            detail, source_at(line)))

    # An outer form claims its position and swallows the plain cast nested in it.
    offset_spans, wrapper_spans = [], []
    for m in OFFSET.finditer(text):
        offset_spans.append((m.start(), m.end()))
        emit("cast+offset", m.start(), m[1] + m[2], f"{m[3]} {m[4]}", 5)
    for m in INDEX.finditer(text):
        wrapper_spans.append((m.start(), m.end()))
        emit("cast+index", m.start(), m[1] + m[2], "", 4)
    for m in DEREF.finditer(text):
        wrapper_spans.append((m.start(), m.end()))
        emit("deref-cast", m.start(), m[1] + m[2], "", 3)
    for m in ABSOLUTE.finditer(text):
        wrapper_spans.append((m.start(), m.end()))
        emit("abs-address", m.start(), m[1], m[2], 6)
    for m in CAST.finditer(text):
        if SIZEOF.search(text[max(0, m.start() - 10):m.start()]):
            continue
        if any(a <= m.start() < b for a, b in wrapper_spans):
            continue
        emit(classify(m[1]), m.start(), m[1] + m[2], "", 1)

    # M2C_FIELD(expr, T*, offset) is a cast+offset that m2c left behind.
    for m in M2C_FIELD.finditer(text):
        prefix = text[text.rfind("\n", 0, m.start()) + 1:m.start()]
        if re.match(r"\s*#\s*define\s*$", prefix):
            continue
        args = macro_args(text, m.end() - 1)
        if len(args) == 3:
            sign = "-" if args[2].startswith("-") else "+"
            emit("m2c-field", m.start(), args[1], f"{sign} {args[2].lstrip('-')}", 7)

    # Both of these need to know which identifiers are pointers, so they are
    # heuristic where the syntactic categories above are exact.
    visible = pointer_names(text)
    for m in TO_INT.finditer(text):
        if m[2] == "&" or m[3] in visible(m.start()):
            emit("ptr-to-int", m.start(), m[1], m[2] + m[3], 2)
    for m in BARE_OFFSET.finditer(text):
        if any(a <= m.start() and m.end() <= b for a, b in offset_spans):
            continue
        if m[1] in visible(m.start()):
            emit("raw-offset", m.start(), "", f"{m[2]} {m[3]}", 0)

    for i, pragma, guarded in pragma_sites(blank_lines):
        detail = "MUST_MATCH" if guarded else "unguarded"
        found.append(Site("pragma", rel, i + 1, pragma, detail, source_at(i + 1)))

    # MUST_MATCH regions are reported at their directive but show the first
    # body line, so the listing says what the hack is rather than `#ifdef`.
    for i, directive, body in must_match_regions(blank_lines):
        hack = classify_hack(body)
        if hack is None:
            continue
        kind, detail = hack
        if directive == "ifndef":
            detail = f"#ifndef {detail}".strip()
        meaningful = (
            j for j, l in enumerate(body)
            if l.strip() and l.strip() != "#pragma push")
        first = next(meaningful, None)
        source = source_at(i + 2 + first) if first is not None else source_at(i + 1)
        found.append(Site("must-match", rel, i + 1, kind, detail, source))

    seen = set()
    for site in found:
        key = (site.line, site.category, site.type, site.detail)
        if key not in seen:
            seen.add(key)
            yield site


def scan_tree(src: Path) -> list[Site]:
    sites: list[Site] = []
    for path in sorted(src.rglob("*")):
        if path.suffix in (".c", ".h") and path.is_file():
            sites.extend(scan_file(path, path.relative_to(ROOT).as_posix()))
    sites.sort(key=lambda s: (s.file, s.line))
    return sites


def directory_of(rel: str) -> str:
    """The directory of a file, at most three levels deep (src/melee/gr)."""
    return "/".join(rel.split("/")[:-1][:3])


def write_tsv(sites: list[Site], out) -> None:
    out.write("category\tfile\tline\ttype\tdetail\tsource\n")
    for s in sites:
        out.write(f"{s.category}\t{s.file}\t{s.line}\t{s.type}\t{s.detail}\t{s.source}\n")


def write_html(
    sites: list[Site], path: Path, revision: str, generated: str, repo: str,
) -> None:
    payload = json.dumps([list(s) for s in sites], separators=(",", ":"))
    meta = json.dumps({
        "revision": revision,
        "generated": generated,
        "repo": repo.rstrip("/"),
        "files": len({s.file for s in sites}),
        "categories": CATEGORIES,
    }, separators=(",", ":"))
    html = TEMPLATE.read_text(encoding="utf-8")
    html = html.replace("__PAYLOAD__", payload.replace("</", "<\\/"))
    html = html.replace("__META__", meta.replace("</", "<\\/"))
    path.write_text(html, encoding="utf-8")


def summarize(sites: list[Site]) -> None:
    by_category = Counter(s.category for s in sites)
    by_family = Counter(FAMILY[s.category] for s in sites)
    print(
        f"{len(sites)} sites in {len({s.file for s in sites})} files: "
        f"{by_family['move']} move a pointer, {by_family['retype']} retype one, "
        f"{by_family['hack']} match hacks\n")
    for name, shape, family in CATEGORIES:
        if by_category[name]:
            print(f"  {by_category[name]:5d}  {name:<17} {family:<7} {shape}")
    print("\n  MUST_MATCH regions by kind")
    for kind, n in Counter(s.type for s in sites if s.category == "must-match").most_common():
        print(f"  {n:5d}  {kind}")
    print("\n  pragmas")
    for kind, n in Counter(s.type for s in sites if s.category == "pragma").most_common(8):
        print(f"  {n:5d}  {kind}")
    print("\n  top directories")
    for d, n in Counter(directory_of(s.file) for s in sites).most_common(8):
        print(f"  {n:5d}  {d}")
    print("\n  top files")
    for f, n in Counter(s.file for s in sites).most_common(8):
        print(f"  {n:5d}  {f}")


def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", type=Path, default=ROOT / "src",
                    help="tree to scan (default: src)")
    ap.add_argument("--out", type=Path,
                    help="directory to write index.html and cleanup_index.tsv into")
    ap.add_argument("--tsv", type=Path,
                    help="write the TSV here instead ('-' for stdout)")
    ap.add_argument("--revision", default="working tree",
                    help="revision label shown on the page")
    ap.add_argument("--generated", default="",
                    help="build date shown on the page")
    ap.add_argument("--repo", default="https://github.com/doldecomp/melee",
                    help="repository URL that line links on the page point into")
    args = ap.parse_args()

    sites = scan_tree(args.src)

    if args.tsv:
        if str(args.tsv) == "-":
            write_tsv(sites, sys.stdout)
        else:
            with args.tsv.open("w", encoding="utf-8") as fh:
                write_tsv(sites, fh)
    if args.out:
        args.out.mkdir(parents=True, exist_ok=True)
        write_html(
            sites, args.out / "index.html", args.revision, args.generated, args.repo)
        with (args.out / "cleanup_index.tsv").open("w", encoding="utf-8") as fh:
            write_tsv(sites, fh)
        print(
            f"wrote {args.out}/index.html and {args.out}/cleanup_index.tsv "
            f"({len(sites)} sites)")
    if not args.tsv and not args.out:
        summarize(sites)
    return 0


if __name__ == "__main__":
    sys.exit(main())
