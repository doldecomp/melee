#!/usr/bin/env python3
import argparse
import json
import subprocess
from pathlib import Path
from typing import List, Tuple, cast

import humanfriendly
from elftools.common.py3compat import sys
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection


def get_functions_info(file_path):
    with open(file_path, "rb") as f:
        elf_file = ELFFile(f)
        symbol_table = elf_file.get_section_by_name(".symtab")

        functions = []
        if isinstance(symbol_table, SymbolTableSection):
            for symbol in symbol_table.iter_symbols():
                if symbol["st_info"]["type"] == "STT_FUNC":
                    functions.append(
                        {
                            "name": symbol.name,
                            "size": symbol["st_size"],
                        }
                    )

    return functions


def calc_percent(current_score, max_score):
    return max(0, 100 - round(100 * current_score / max_score, 2))


def main(args) -> None:
    src_path = cast(Path, args.src_path)
    obj_path = src_path.with_suffix(".o")
    expected_root = Path("build/GALE01/obj")
    wip_root = Path("build/GALE01/src")
    expected_path = expected_root / obj_path
    wip_path = wip_root / obj_path

    entries: List[Tuple[str, int, int, int, float]] = []

    functions_info = get_functions_info(expected_path)
    file_size = 0
    file_current_score = 0
    file_max_score = 0
    for function in functions_info:
        cmd = [
            "python3",
            "./tools/asm-differ/diff.py",
            "-mos",
            "-f",
            str(wip_path),
            "--format",
            "json",
            f"{function['name']}",
        ]
        result = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
        ).stdout.strip()
        try:
            result = json.loads(result)
            current_score = int(result["current_score"])
            max_score = int(result["max_score"])

            percent = calc_percent(current_score, max_score)
            entries.append(
                (function["name"], function["size"], current_score, max_score, percent)
            )
            file_size += function["size"]
            file_current_score += current_score
            file_max_score += max_score
        except Exception as e:
            json.dump(function, sys.stderr)
            print(f"\n{repr(result)}", file=sys.stderr)
            print(e, file=sys.stderr)

    # sort by percentage (ascending)
    # then by size (descending)
    # then by max score (descending)
    # then by name (ascending)
    entries.sort(key=lambda x: (x[4], -x[1], -x[3], x[0]))
    file_percent = calc_percent(file_current_score, file_max_score)
    friendly_file_size = humanfriendly.format_size(file_size)

    if args.title:
        friendly_obj_name = src_path.stem
        msg = (
            f"Match {file_percent:.2f}% of `{friendly_obj_name}` ({friendly_file_size})"
            if file_percent < 100
            else f"Match `{friendly_obj_name}` ({friendly_file_size})"
        )
        print(msg)
    else:
        print(f"## Report of `{src_path}`")
        print("Function|Size|Score|Max|%\n-|-|-|-|-")
        print(
            f"**File**|"
            f"`{friendly_file_size}`|"
            f"`{humanfriendly.format_number(file_current_score)}`|"
            f"`{humanfriendly.format_number(file_max_score)}`|"
            f"`{file_percent:.2f}%`"
        )
        for entry in entries:
            print(
                f"`{entry[0]}`|"
                f"`{humanfriendly.format_size(entry[1])}`|"
                f"`{humanfriendly.format_number(entry[2])}`|"
                f"`{humanfriendly.format_number(entry[3])}`|"
                f"`{entry[4]:.2f}%`"
            )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Report progress of a translation unit"
    )
    parser.add_argument("src_path", type=Path, help="Path to the source file")
    parser.add_argument("--title", action="store_true", help="Output only a title")
    args = parser.parse_args()
    main(args)
