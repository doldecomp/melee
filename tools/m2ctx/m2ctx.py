#!/usr/bin/env python3

import argparse
import subprocess
import sys
from pathlib import Path

here = Path(__file__).parent
root = here / '../../'
mwcc_command = root / "tools/mwcc_compiler/1.2.5e/mwcceppc.exe"

MWCC_FLAGS = [
    "-EP",
    "-Cpp_exceptions", "off",
    "-proc", "gekko",
    "-DGEKKO",
    "-fp", "hard",
    "-fp_contract", "on",
    "-O4,p",
    "-enum", "int",
    "-nodefaults",
    "-inline", "auto", "-I-",
    "-i", "src/MSL",
    "-i", "src",
    "-DM2CTX",
]


def normalize_path(p: str) -> str:
    p = Path(p)
    if not p.is_relative_to(root):
        p = root / p
    p = p.resolve().relative_to(root.resolve())
    return str(p)


def import_c_file(in_file: str) -> str:
    in_file = normalize_path(root / in_file)
    c_command = [normalize_path(mwcc_command), *MWCC_FLAGS, "-E", in_file]

    try:
        out_text = subprocess.check_output(c_command, cwd=root, encoding="utf8")
    except subprocess.CalledProcessError as err:
        print(
            "Failed to preprocess input file, when running command:\n"
            + ' '.join(c_command)
            + f'\n\n{err.output}',
            file=sys.stderr,
        )
        sys.exit(1)

    if not out_text:
        print("Output is empty - aborting")
        sys.exit(1)

    return out_text


def main():
    parser = argparse.ArgumentParser(
        description="""Create a context file which can be used for mips_to_c"""
    )
    parser.add_argument(
        "c_file",
        help="""File from which to create context""",
    )
    args = parser.parse_args()

    output = import_c_file(args.c_file)

    print(output)

if __name__ == "__main__":
    main()
