#!/usr/bin/env python3

import argparse
import re
import sys
from collections.abc import Callable
from typing import TextIO, cast


def convert_hex(content: str) -> str:
    return re.sub(
        r"\b0x([0-9a-fA-F]{1,7})U?\b",
        lambda m: str(int(m.group(1), 16)),
        content,
    )


def fix_bool(content: str) -> str:
    def replace(m: re.Match[str]) -> str:
        match (s := m.group(0)):
            case "0":
                return "false"
            case "1":
                return "true"
            case "0U" | "0u":
                return "NULL"
            case "int" | "s32":
                return "bool"
            case _:
                assert False, f'Unknown regex match "{s}"'

    return re.sub(
        r"(?<!\S)(?:0|1|0[Uu]|int|s32)(?=[;)\s])",
        replace,
        content,
    )


def fix_primitives(content: str) -> str:
    def replace(m: re.Match[str]) -> str:
        match (s := m.group(0)):
            case "s8":
                return "signed char"
            case "u8":
                return "char"
            case "s16":
                return "short"
            case "u16":
                return "unsigned short"
            case "s32":
                return "int"
            case "u32":
                return "uint"
            case "f32":
                return "float"
            case "f64":
                return "double"
            case _:
                assert False, f'Unknown regex match "{s}"'

    return re.sub(
            r"(?<![^\s(;])[fsu](?:16|32|64)(?![^\s);,])",
        replace,
        content,
    )


def remove_cast(content: str) -> str:
    return re.sub(
        r"\s*\([\w*]+\)\s*",
        "",
        content,
    )


def process_input(input: str, func: Callable[[str], str]) -> None:
    def write(in_fp: Callable[[], TextIO], out_fp: Callable[[], TextIO]):
        with in_fp() as fp:
            content = fp.read()
        content = func(content)
        with out_fp() as fp:
            _ = fp.write(content)

    if input == "-":
        write(lambda: sys.stdin, lambda: sys.stdout)
    else:
        write(lambda: open(input, "r"), lambda: open(input, "w"))


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Fix various issues with source code",
    )
    _ = parser.add_argument(
        "mode",
        type=str.lower,
        metavar="MODE",
        choices=[
            "bool",
            "cast",
            "hex",
            "prim",
        ],
        default="-",
        help="which action to take",
    )
    _ = parser.add_argument(
        "input",
        type=str,
        metavar="INPUT",
        nargs="?",
        default="-",
        help='input file to process (use "-" for stdin)',
    )
    args = parser.parse_args()

    # TODO subparser instead of mode switch (for help messages)
    def choose_action(mode: str) -> Callable[[str], str]:
        match mode:
            case "bool":
                return fix_bool
            case "cast":
                return remove_cast
            case "hex":
                return convert_hex
            case "prim":
                return fix_primitives
            case _:
                assert False, f'Unknown mode "{mode}"'

    process_input(
        cast(str, args.input),
        choose_action(cast(str, args.mode)),
    )


if __name__ == "__main__":
    main()
