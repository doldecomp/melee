#!/usr/bin/env python3
"""
Auto-add missing includes for undeclared functions, similar to clangd quick fixes.

Usage:
  tools/fix_includes.py <path/to/file.c>

Approach:
- Read compile_commands.json to find the compile args for the file.
- Run clang with -fsyntax-only to capture diagnostics.
- Extract function names from implicit declaration errors.
- Search project headers for matching declarations.
- Insert missing #include lines into the C file.

This script makes a best-effort fix and focuses on function declarations.
Assumes compile_commands.json entry exists for the file.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import subprocess
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple


ROOT = Path(__file__).resolve().parents[1]
COMPILE_COMMANDS = ROOT / "compile_commands.json"


def load_compile_args(src: Path) -> Optional[List[str]]:
    """Return the compile arguments for `src` from compile_commands.json, if present."""
    if not COMPILE_COMMANDS.exists():
        return None

    abs_src = src.resolve()

    # Parse JSON lazily to avoid large memory if file is huge
    with COMPILE_COMMANDS.open("r") as f:
        entries = json.load(f)

    # Entries may use absolute file paths
    for entry in entries:
        entry_file = Path(entry.get("file", "")).resolve()
        if entry_file == abs_src:
            if "arguments" in entry and entry["arguments"]:
                return list(entry["arguments"])
            cmd = entry.get("command")
            if cmd:
                # Split the command string into args
                return shlex.split(cmd)
            break
    return None


def build_syntax_only_args(args: List[str], src: Path) -> List[str]:
    """Transform compile args into a -fsyntax-only invocation for clang."""
    out: List[str] = []
    skip_next = False
    for i, a in enumerate(args):
        if skip_next:
            skip_next = False
            continue
        if a == "-c":
            # Replace compile with syntax-only check
            out.append("-fsyntax-only")
            continue
        if a == "-o":
            skip_next = True
            continue
        # Some build systems add things like --serialize-diagnostics: ignore outputs
        if a.startswith("-o") and len(a) > 2:
            # handle short form -oFILE
            continue
        if a.startswith("--serialize-diagnostics"):
            if "=" not in a:
                skip_next = True
            continue
        out.append(a)

    # Ensure the source is present and last
    # Remove any absolute file path occurrences, then add the provided src
    out = [x for x in out if x != str(src.resolve())]
    out.append(str(src))
    return out


IMPLICIT_DECL_PATTERNS = [
    re.compile(r"implicit declaration of function '([A-Za-z_][A-Za-z0-9_]*)'"),
    re.compile(r"use of undeclared identifier '([A-Za-z_][A-Za-z0-9_]*)'"),
    re.compile(r"call to undeclared function '([A-Za-z_][A-Za-z0-9_]*)'"),
]


def run_clang_syntax_check(args: List[str], cwd: Path) -> Tuple[int, str, str]:
    """Run clang with given args, return (code, stdout, stderr)."""
    try:
        proc = subprocess.run(
            args, cwd=cwd, text=True, capture_output=True, check=False
        )
        return proc.returncode, proc.stdout, proc.stderr
    except FileNotFoundError:
        return 127, "", "clang not found"


def extract_undeclared_functions(diag: str) -> List[str]:
    names: Set[str] = set()
    for line in diag.splitlines():
        for pat in IMPLICIT_DECL_PATTERNS:
            m = pat.search(line)
            if m:
                names.add(m.group(1))
    return sorted(names)


def search_headers_for_function(name: str) -> Optional[Path]:
    """Search project headers for a prototype containing the function name.

    Pure-Python scan to avoid external tool flakiness.
    """
    pattern = re.compile(rf"\b{name}\s*\(")
    root = ROOT / "src"
    candidates: List[Path] = []
    for p in root.rglob("*.h"):
        try:
            with p.open("r", errors="ignore") as f:
                txt = f.read()
            if pattern.search(txt):
                candidates.append(p)
        except Exception:
            continue
    if not candidates:
        return None
    return min(candidates, key=lambda p: len(str(p)))


def parse_existing_includes(src_text: str) -> Tuple[List[str], Set[str], Set[str]]:
    includes: List[str] = []
    included_paths: Set[str] = set()
    included_basenames: Set[str] = set()
    for line in src_text.splitlines():
        m = re.match(r'\s*#\s*include\s*([<"])([^>"]+)[>"]', line)
        if m:
            includes.append(line)
            path = m.group(2)
            # Normalize to prefer 'it/...' over 'melee/it/...'
            if path.startswith('melee/'):
                path = path[len('melee/') :]
            included_paths.add(path)
            included_basenames.add(Path(path).name)
    return includes, included_paths, included_basenames


def insert_includes(src_text: str, new_includes: List[str]) -> str:
    lines = src_text.splitlines()
    # Find last include line index
    last_inc_idx = -1
    inc_re = re.compile(r"^\s*#\s*include\b")
    for i, line in enumerate(lines):
        if inc_re.match(line):
            last_inc_idx = i
    if last_inc_idx == -1:
        # No includes found; insert at top with a newline after
        result = "\n".join(new_includes + [""] + lines)
    else:
        # Insert after the last include
        new_lines = lines[: last_inc_idx + 1] + new_includes + lines[last_inc_idx + 1 :]
        result = "\n".join(new_lines)

    # Ensure the result always ends with a newline
    if not result.endswith("\n"):
        result += "\n"
    return result


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("source", type=Path, help="Path to C source file")
    args = ap.parse_args()

    src = args.source
    if not src.exists():
        print(f"error: source not found: {src}")
        return 2

    cc_args = load_compile_args(src)
    if not cc_args:
        print(f"error: compile_commands.json entry not found for {src}")
        return 1

    # Ensure we use clang explicitly (first arg is the compiler)
    cmd = [cc_args[0]] + build_syntax_only_args(cc_args[1:], src)
    code, out, err = run_clang_syntax_check(cmd, ROOT)
    undeclared = extract_undeclared_functions(err)

    if not undeclared:
        print("No undeclared functions detected by clang.")
        return 0

    # Read the source for include analysis
    with open(src, "r") as f:
        src_text = f.read()
    _, already, already_base = parse_existing_includes(src_text)

    to_include: List[str] = []
    proposals: Dict[str, Path] = {}

    print("Undeclared functions:")
    for name in undeclared:
        print(f"  - {name}")
        header = search_headers_for_function(name)
        if header is None:
            continue
        try:
            rel = header.relative_to(ROOT / "src")
        except ValueError:
            rel = header
        # Map 'melee/it/...' to 'it/...'
        rel_parts = rel.as_posix().split('/')
        if rel_parts and rel_parts[0] == 'melee':
            rel_parts = rel_parts[1:]
        inc_path = '/'.join(rel_parts)
        proposals[inc_path] = header

    if not proposals:
        print("No matching headers found for functions.")
        return 1

    # Skip including the source's own header if present
    own_header = src.with_suffix('.h')
    for inc_path, p in sorted(proposals.items()):
        if p.resolve() == own_header.resolve():
            continue
        if inc_path in already:
            continue
        if Path(inc_path).name in already_base:
            continue
        to_include.append(f"#include \"{inc_path}\"")

    if not to_include:
        print("All required headers already included.")
        return 0

    new_text = insert_includes(src_text, to_include)
    with open(src, "w") as f:
        f.write(new_text)

    print("Added includes:")
    for inc in to_include:
        print(f"  {inc}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
