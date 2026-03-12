#!/usr/bin/env python3
"""Find undecompiled function stubs in a C source file.

Scans for `/// #function_name` markers where the next non-blank line
is NOT the function definition (meaning it's still a stub).

Outputs JSON array of {name, size, file, line} sorted by size ascending.
"""

import json
import re
import sys
from pathlib import Path

SYMBOLS_FILE = Path("config/GALE01/symbols.txt")


def get_symbol_sizes():
    """Parse symbols.txt to get function sizes."""
    sizes = {}
    for line in SYMBOLS_FILE.read_text().splitlines():
        m = re.match(
            r"(\w+)\s*=\s*\.text:0x[0-9A-Fa-f]+;\s*//\s*type:function\s+size:0x([0-9A-Fa-f]+)",
            line,
        )
        if m:
            sizes[m.group(1)] = int(m.group(2), 16)
    return sizes


def find_stubs(c_file):
    """Find stub markers where no implementation follows."""
    text = Path(c_file).read_text()
    lines = text.splitlines()
    stubs = []
    for i, line in enumerate(lines):
        m = re.match(r"^/// #(\w+)\s*$", line)
        if not m:
            continue
        func_name = m.group(1)
        # Check if function is defined (not just declared) anywhere in the file
        # A definition looks like: `type func_name(` at the start of a line
        defn_pattern = re.compile(
            rf"^\w[\w\s\*]*\b{re.escape(func_name)}\s*\(", re.MULTILINE
        )
        has_impl = False
        for m2 in defn_pattern.finditer(text):
            line_no = text[:m2.start()].count("\n")
            if line_no == i:
                continue
            # Verify it has { within next few lines (definition, not declaration)
            snippet = "\n".join(lines[line_no : line_no + 3])
            if "{" in snippet:
                has_impl = True
                break
        if not has_impl:
            stubs.append({"name": func_name, "line": i + 1, "file": str(c_file)})
    return stubs


def main():
    if len(sys.argv) < 2:
        print("Usage: find_stubs.py <file.c> [<file2.c> ...]", file=sys.stderr)
        sys.exit(1)

    sizes = get_symbol_sizes()
    all_stubs = []
    for f in sys.argv[1:]:
        for stub in find_stubs(f):
            stub["size"] = sizes.get(stub["name"], 0)
            all_stubs.append(stub)

    all_stubs.sort(key=lambda s: s["size"])
    print(json.dumps(all_stubs, indent=2))


if __name__ == "__main__":
    main()
