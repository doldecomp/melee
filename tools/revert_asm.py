#!/usr/bin/env python3

import argparse
import os
import platform
import subprocess
from pathlib import Path


def run_command(path: Path) -> None:
    root = Path(__file__).parents[1]
    path = path.resolve().relative_to(root / "src")
    obj_path = root / "build/GALE01/obj" / path.with_suffix(".o")
    src_path = "src" / path
    asm_path = "asm" / path.with_suffix(".s")
    dtk_path = Path("build/tools/dtk")

    if platform.system() == "Windows":
        dtk_path = dtk_path.with_suffix(".exe")

    command = [
        str(root.joinpath(e).resolve()) if isinstance(e, Path) else e
        for e in [dtk_path, "elf", "disasm", obj_path, asm_path]
    ]

    subprocess.run(command, check=True)

    mk_path = root / "obj_files.mk"
    lines = mk_path.read_text().splitlines()
    src_str = str(src_path.as_posix())
    asm_str = str(asm_path.as_posix())
    lines = [line.replace(src_str, asm_str) for line in lines if asm_str not in line]
    lines.append('')
    text = os.linesep.join(lines)
    mk_path.write_text(text)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="revert a C file to asm for make")
    parser.add_argument(
        "path", metavar="C_FILE", type=Path, help="the source file to revert"
    )

    args = parser.parse_args()

    run_command(args.path)
