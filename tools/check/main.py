#!/usr/bin/env python3
"""Source style checks for the Melee decompilation tree.

Each check looks for a pattern that has been swept out of the tree and
should not return (for example a raw ``0x10`` where ``JOBJ_HIDDEN`` is
meant). Checks are enabled by default and can be disabled individually
with ``--no-<check>``, mirroring clang's ``-Wno-`` flags.

Output and exit codes mirror ``melee-issues`` (``tools/issues``):
``--msg-style std`` prints a ``severity > category > [option] > file``
hierarchy and a final ``Issues: OK`` / ``Issues: N`` summary; the process
exits 0 when clean, 65 (``EX_DATAERR``) when issues are found, and 74
(``EX_IOERR``) on an internal error. ``--msg-style actions`` emits GitHub
Actions warning annotations instead of the hierarchy.

Usage:
    python3 tools/check/main.py [--no-<check> ...] [--msg-style {std,actions}] [PATH ...]
"""
import argparse
import re
import sys
from collections.abc import Callable, Iterator
from dataclasses import dataclass
from itertools import groupby
from pathlib import Path

SOURCE_GLOB = "*.[ch]"

# Exit codes mirror the `exitcode` crate used by melee-issues.
EXIT_OK = 0
EXIT_ISSUES = 65  # EX_DATAERR
EXIT_ERROR = 74  # EX_IOERR

# All findings are warnings; melee-issues groups by severity first.
SEVERITY = "Warning"


@dataclass(frozen=True)
class Finding:
    path: str
    line: int
    column: int
    message: str
    snippet: str


# A check reads one file's (path, text) and yields any findings in it.
ScanFn = Callable[[Path, str], Iterator[Finding]]


@dataclass(frozen=True)
class Check:
    name: str  # kebab-case id; drives --no-<name> and the [option] label
    help: str
    scan: ScanFn
    category: str = "Style Issue"


# --- shared lexing helpers ------------------------------------------------


def strip_noise(text: str) -> str:
    """Blank comments and string/char literals, preserving offsets and newlines.

    The result is the same length as the input with the same newline
    positions, so offsets and line/column numbers map back to the original.
    """
    out: list[str] = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("".join(ch if ch == "\n" else " " for ch in text[i:j]))
            i = j
        elif c in "\"'":
            quote, j = c, i + 1
            while j < n:
                if text[j] == "\\":
                    j += 2
                    continue
                if text[j] == quote:
                    j += 1
                    break
                j += 1
            out.append("".join(ch if ch == "\n" else " " for ch in text[i:j]))
            i = j
        else:
            out.append(c)
            i += 1
    return "".join(out)


def find_close(text: str, open_idx: int) -> int:
    """Index of the ``)`` matching the ``(`` at ``open_idx``, or -1."""
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return i
    return -1


def top_level_commas(text: str, open_idx: int, close_idx: int) -> list[int]:
    """Indices of commas at paren depth 1 between ``open_idx`` and ``close_idx``."""
    depth = 0
    commas: list[int] = []
    for i in range(open_idx, close_idx):
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif c == "," and depth == 1:
            commas.append(i)
    return commas


def line_col(text: str, idx: int) -> tuple[int, int]:
    """1-based (line, column) of ``idx`` in ``text``."""
    bol = text.rfind("\n", 0, idx) + 1
    return text.count("\n", 0, idx) + 1, idx - bol + 1


def directive_lines(text: str) -> set[int]:
    """0-based line indices inside preprocessor directives (incl. continuations)."""
    covered: set[int] = set()
    lines = text.split("\n")
    i = 0
    while i < len(lines):
        if lines[i].lstrip().startswith("#"):
            covered.add(i)
            while i < len(lines) and lines[i].rstrip().endswith("\\"):
                i += 1
                covered.add(i)
        i += 1
    return covered


# --- check: jobj-flags ----------------------------------------------------

# HSD_JObj{Set,Clear}Flags[All] called with a raw hidden-flag literal where
# JOBJ_HIDDEN is meant. The literal pattern matches integer literals whose
# value is 16 (hex, decimal, or octal, with an optional unsigned/long
# suffix); composite masks such as ``0x10 | JOBJ_PTCL`` are not matched.
#
# TODO(future): generalize to resolving arbitrary raw literals against the
# JObj flag #defines instead of hard-coding the single hidden-flag pattern.
_JOBJ_CALL = re.compile(r"HSD_JObj(?:Set|Clear)Flags(?:All)?\s*\(")
_HIDDEN_LITERAL = re.compile(r"(?:16|0[xX]0*10|0+20)[uUlL]*")
_JOBJ_MESSAGE = (
    "Use JOBJ_HIDDEN instead of a raw 0x10 literal "
    "(see src/sysdolphin/baselib/jobj.h)"
)


def scan_jobj_flags(path: Path, text: str) -> Iterator[Finding]:
    code = strip_noise(text)
    pos = 0
    while True:
        m = _JOBJ_CALL.search(code, pos)
        if m is None:
            return
        open_idx = code.index("(", m.end() - 1)
        close_idx = find_close(code, open_idx)
        if close_idx < 0:
            pos = m.end()
            continue
        commas = top_level_commas(code, open_idx, close_idx)
        if len(commas) == 1:
            arg = code[commas[0] + 1 : close_idx].strip()
            if _HIDDEN_LITERAL.fullmatch(arg):
                line, column = line_col(code, m.start())
                snippet = " ".join(text[m.start() : close_idx + 1].split())
                yield Finding(str(path), line, column, _JOBJ_MESSAGE, snippet)
        pos = close_idx


# --- check: assert-macros -------------------------------------------------

# Direct __assert(...) calls whose file argument is __FILE__ or the file's
# own basename string; both are expressible with the HSD assert macros
# (debug.h). Calls passing a different filename cannot use the macros (they
# hard-code __FILE__) and are left alone. A site annotated with a Doxygen
# @todo within the preceding four lines is exempt: it records that no
# byte-matching macro form is known there yet.
_ASSERT_CALL = re.compile(r"__assert\s*\(")
_ASSERT_MESSAGE = (
    "Use HSD_ASSERT/HSD_ASSERTMSG/HSD_ASSERTREPORT instead of a direct "
    "__assert call (see src/sysdolphin/baselib/debug.h), or annotate with a "
    "@todo if no byte-matching form is known yet"
)
_ASSERT_EXEMPT_PATHS = frozenset({"src/sysdolphin/baselib/debug.h"})


def scan_assert_macros(path: Path, text: str) -> Iterator[Finding]:
    if str(path) in _ASSERT_EXEMPT_PATHS:
        return
    own = f'"{path.name}"'
    code = strip_noise(text)
    lines = text.split("\n")
    dlines = directive_lines(text)
    pos = 0
    while True:
        m = _ASSERT_CALL.search(code, pos)
        if m is None:
            return
        pos = m.end()
        line0 = code.count("\n", 0, m.start())
        if line0 in dlines:
            continue
        open_idx = code.index("(", m.start())
        close_idx = find_close(code, open_idx)
        if close_idx < 0:
            continue
        commas = top_level_commas(code, open_idx, close_idx)
        end_first = commas[0] if commas else close_idx
        # Read the first argument from the original text: in the comment- and
        # string-blanked view a "basename.c" literal would be erased.
        first = text[open_idx + 1 : end_first].strip()
        if first not in ("__FILE__", own):
            continue
        context = "\n".join(lines[max(0, line0 - 4) : line0 + 1])
        if "@todo" in context:
            continue
        _, column = line_col(code, m.start())
        snippet = " ".join(text[m.start() : close_idx + 1].split())
        yield Finding(str(path), line0 + 1, column, _ASSERT_MESSAGE, snippet)


# --- registry & driver ----------------------------------------------------

CHECKS: list[Check] = [
    Check(
        "jobj-flags",
        "raw 0x10 instead of JOBJ_HIDDEN in HSD_JObj flag calls",
        scan_jobj_flags,
    ),
    Check(
        "assert-macros",
        "direct __assert calls that could use the HSD assert macros",
        scan_assert_macros,
    ),
]


def _dest(name: str) -> str:
    return "no_" + name.replace("-", "_")


def collect(checks: list[Check], roots: list[str]) -> list[tuple[Check, Finding]]:
    found: list[tuple[Check, Finding]] = []
    for root in roots:
        root_path = Path(root)
        if not root_path.is_dir():
            raise FileNotFoundError(f"scan root does not exist: {root}")
        for path in sorted(root_path.rglob(SOURCE_GLOB)):
            text = path.read_text(errors="replace")
            for check in checks:
                for finding in check.scan(path, text):
                    found.append((check, finding))
    return found


def print_std(pairs: list[tuple[Check, Finding]]) -> None:
    """Print findings as melee-issues does: severity > category > [option] > file."""
    indent = "    "
    ordered = sorted(
        pairs,
        key=lambda cf: (SEVERITY, cf[0].category, cf[0].name, cf[1].path, cf[1].line, cf[1].column),
    )
    print(f"{SEVERITY} ({len(ordered)})")
    for category, cat_items in groupby(ordered, key=lambda cf: cf[0].category):
        cat_items = list(cat_items)
        print(f"{indent}{category} ({len(cat_items)})")
        for option, opt_items in groupby(cat_items, key=lambda cf: cf[0].name):
            opt_items = list(opt_items)
            print(f"{indent * 2}[{option}] ({len(opt_items)})")
            for filename, file_items in groupby(opt_items, key=lambda cf: cf[1].path):
                file_items = list(file_items)
                print(f"{indent * 3}{filename} ({len(file_items)})")
                for _check, f in file_items:
                    print(f"{indent * 4}{f.line}:{f.column}: {f.message}")


def print_actions(pairs: list[tuple[Check, Finding]]) -> None:
    for _check, f in pairs:
        print(
            f"::warning file={f.path},line={f.line},col={f.column}::"
            f"{f.message}: {f.snippet}"
        )


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument(
        "paths", nargs="*", default=["src"], help="source roots to scan (default: src)"
    )
    parser.add_argument(
        "--msg-style",
        choices=["std", "actions"],
        default="std",
        help="message style (default 'std'; 'actions' emits GitHub Actions annotations)",
    )
    for check in CHECKS:
        parser.add_argument(
            f"--no-{check.name}",
            dest=_dest(check.name),
            action="store_true",
            help=f"disable check: {check.help}",
        )
    args = parser.parse_args(argv)

    enabled = [c for c in CHECKS if not getattr(args, _dest(c.name))]
    pairs = collect(enabled, args.paths or ["src"])
    if not pairs:
        print("Issues: OK")
        return EXIT_OK
    if args.msg_style == "actions":
        print_actions(pairs)
    else:
        print_std(pairs)
    print(f"Issues: {len(pairs)}", file=sys.stderr)
    return EXIT_ISSUES


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as exc:  # noqa: BLE001 - mirror melee-issues' Error/IOERR path
        print(f"Error: {exc}", file=sys.stderr)
        sys.exit(EXIT_ERROR)
