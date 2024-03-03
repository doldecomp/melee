#!/usr/bin/env python3

import argparse
import os
import re
from collections.abc import Callable
from pathlib import Path
from typing import Optional, cast


def link(path: Path):
    root = Path(__file__).parents[1]
    path = path.resolve().relative_to(root / "src")
    mk_path = root / "obj_files.mk"
    cfg_path = root / "configure.py"
    path_str = str(path.as_posix())
    asm_path = ("asm" / path).with_suffix(".s")
    src_str = str(("src" / path).with_suffix(".c"))
    asm_str = str(asm_path)

    def edit_file(path: Path, op: Callable[[str], Optional[str]]) -> None:
        lines = path.read_text().splitlines()
        lines = map(op, lines)
        lines = filter(lambda s: s is not None, lines)
        lines = map(lambda s: cast(str, s), lines)
        lines = list(lines)
        lines.append("")
        text = os.linesep.join(lines)
        path.write_text(text)

    def edit_mk(s: str) -> Optional[str]:
        if src_str in s:
            return None
        return s.replace(asm_str, src_str)

    def edit_cfg(s: str) -> str:
        if path_str in s:
            return re.sub(r"\bNonMatching\b", "Matching", s)
        return s

    edit_file(mk_path, edit_mk)
    edit_file(cfg_path, edit_cfg)
    asm_path.unlink()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="replaces an asm file with a C file in the build"
    )
    parser.add_argument(
        "path",
        metavar="C_FILE",
        type=Path,
        help="the source file to link (src/.../foo.c)",
    )

    args = parser.parse_args()

    link(args.path)
