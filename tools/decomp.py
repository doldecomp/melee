#!/usr/bin/env python3

import argparse
import subprocess
import sys
from pathlib import Path
from sys import stderr
from typing import Optional, cast

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

root = Path(__file__).parent.parent
dtk_root = root / "build/GALE01"
obj_root = dtk_root / "obj"
asm_root = dtk_root / "asm"
m2c_script = root / "tools/m2c/m2c.py"
ctx_file = root / "build/ctx.c"
m2ctx_script = root / "tools/m2ctx/m2ctx.py"


def has_function(obj_path: Path, function_name: str) -> bool:
    with open(obj_path, "rb") as f:
        elf_file = ELFFile(f)
        symbol_table = elf_file.get_section_by_name(".symtab")

        if isinstance(symbol_table, SymbolTableSection):
            for symbol in symbol_table.iter_symbols():
                if (
                    symbol["st_info"]["type"] == "STT_FUNC"
                    and symbol.name == function_name
                ):
                    return True
    return False


def find_obj(root: Path, function_name: str) -> Optional[Path]:
    for p in root.rglob("*.o"):
        if has_function(p, function_name):
            return p.relative_to(root)
    return None


def resolve_path(p: Path) -> str:
    return str(p.resolve())


def run_cmd(cmd: list[str]) -> str:
    if cmd[0] == "python":
        executable = sys.executable
    else:
        executable = None
    result = subprocess.run(cmd, capture_output=True, executable=executable)
    if result.returncode != 0:
        print(" ".join(cmd), file=sys.stderr)
        print(result.stdout.decode(), file=sys.stderr)
        print(result.stderr.decode(), file=sys.stderr)
        sys.exit(1)
    else:
        return result.stdout.decode()


def gen_ctx():
    run_cmd(
        [
            "python",
            resolve_path(m2ctx_script),
            "--quiet",
            "--preprocessor",
        ]
    )


def main():
    parser = argparse.ArgumentParser(description="Decomp a function using m2c")
    parser.add_argument(
        "function",
        type=str,
        help="a function to be processed",
    )
    parser.add_argument(
        dest="m2c_args",
        nargs=argparse.REMAINDER,
        help="additional arguments to be passed to m2c",
    )
    parser.add_argument(
        "--no-context",
        action="store_false",
        dest="ctx",
        help=f"do not generate {ctx_file.name}",
    )
    parser.add_argument(
        "--no-copy",
        action="store_false",
        dest="copy",
        help=f"do not copy the output to the clipboard",
    )
    parser.add_argument(
        "--no-print",
        action="store_false",
        dest="print",
        help=f"do not print the output",
    )
    parser.add_argument(
        "--colorize",
        action="store_true",
        dest="color",
        help=f"colorize the output (requires pygments)",
    )

    args = parser.parse_args()

    if (obj_file := find_obj(obj_root, args.function)) is not None:
        asm_file = asm_root / cast(Path, obj_file).with_suffix(".s")

        m2c_cmd: list[str] = [
            "python",
            resolve_path(m2c_script),
            *args.m2c_args,
            "--target",
            "ppc-mwcc-c",
            "--context",
            resolve_path(ctx_file),
            "--function",
            args.function,
            resolve_path(asm_file),
        ]

        if args.ctx:
            gen_ctx()

        output = run_cmd(m2c_cmd)
        if args.copy:
            import pyperclip

            pyperclip.copy(output)
        if args.print:
            if args.color:
                from pygments import highlight
                from pygments.formatters import TerminalFormatter
                from pygments.lexers import CLexer

                output = highlight(output, CLexer(), TerminalFormatter())
            print(output, file=sys.stdout)
    else:
        print(f"Could not find {args.function}", file=stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
