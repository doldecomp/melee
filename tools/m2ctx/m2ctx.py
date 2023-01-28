#!/usr/bin/env python3

import os
import subprocess
import sys
from pathlib import Path
from typing import List

here = Path(__file__).parent
root = (here / '../../').resolve()
src = root / 'src'
build = root / 'build'
header_path = build / 'ctx.h'
source_path = build / 'ctx.c'
mwcc_command = root / "tools/mwcc_compiler/1.2.5e/mwcceppc.exe"

MWCC_FLAGS = [
    "-EP",
    "-Cpp_exceptions", "off",
    "-proc", "gekko",
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

PCPP_FLAGS = [
    "-I", "src",
    "-I", "src/MSL",
    "-D", "__MWERKS__",
    "-D" "M2CTX",
    "--passthru-defines",
    "--line-directive",
    "--compress",
]

def write_header(path: Path):
    files = sorted({f'#include <{file.relative_to(src)}>'
                    for file in src.rglob("*.h")})
    path.write_text('\n'.join(files))

def try_import(c_command: List[str]):
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

def pcpp_import(in_file: Path) -> str:
    c_command = ['pcpp', *PCPP_FLAGS, str(in_file)]
    return try_import(c_command)


def mwcc_import(in_file: Path) -> str:
    c_command = [str(mwcc_command), *MWCC_FLAGS, "-E", str(in_file)]

    if sys.platform != "win32":
        wine = os.environ.get("WINE", "wine")
        c_command = [wine] + c_command

    return try_import(c_command)


def main():
    import argparse

    parser = argparse.ArgumentParser(
        description="""Create a context file which can be used for mips_to_c""")

    parser.add_argument("-q", "--quiet", action="store_true",
                        help="do not print the output")
    parser.add_argument("-n", "--no-file", action="store_true",
                        help=f"do not write {source_path.relative_to(root)}")
    parser.add_argument("-x", "--clipboard", action="store_true",
                        help="copy the output to the clipboard (requires pyperclip)")
    parser.add_argument("-c", "--colorize", action="store_true",
                        help="colorize the output (requires pygments)")
    parser.add_argument("-f", "--format", action="store_true",
                        help="colorize the output (requires clang-format)")
    parser.add_argument("-p", "--preprocessor", action="store_true",
                        help="preserve preprocessor directives (requires pcpp)")
    args = parser.parse_args()


    write_header(header_path)

    if args.preprocessor:
        import pcpp
        output = pcpp_import(header_path)
    else:
        output = mwcc_import(header_path)

    if args.format:
        try:
            output = subprocess.check_output(['clang-format'], cwd=root,
                                             input=output, encoding="utf8")
        except subprocess.CalledProcessError as err:
            print(f'Failed to format the output:\n{err.output}',
                  file=sys.stderr)

    output = output.strip()

    if not args.no_file:
        source_path.write_text(output)

    if args.clipboard:
        import pyperclip
        pyperclip.copy(output)

    if not args.quiet:
        if args.colorize:
            from pygments import highlight
            from pygments.lexers import CLexer
            from pygments.formatters import TerminalFormatter
            output = highlight(output, CLexer(), TerminalFormatter())

        print(output)


if __name__ == "__main__":
    main()
