#!/usr/bin/env python3
import json
import subprocess
from pathlib import Path
from typing import List, Tuple

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
                        }
                    )

    return functions


def main(obj_path: str) -> None:
    expected_root = Path("./expected/build/ssbm.us.1.2/")
    expected_path = expected_root / obj_path
    obj_name = str(expected_path.relative_to(expected_root)).replace(".o", "")

    entries: List[Tuple[str, int, int, float]] = []

    functions_info = get_functions_info(expected_path)
    for function in functions_info:
        cmd = [
            "python3",
            "./tools/asm-differ/diff.py",
            "-os",
            "--format",
            "json",
            f"{function['name']}",
        ]
        result = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            universal_newlines=True,
        ).stdout.strip()
        result = json.loads(result)
        current_score = int(result["current_score"])
        max_score = int(result["max_score"])

        percent = 100 - round(100 * current_score / max_score, 2)
        entries.append((function["name"], current_score, max_score, percent))

    # sort by percentage (ascending)
    # then by max score (descending)
    # then by name (ascending)
    entries.sort(key=lambda x: (x[3], -x[2], x[0]))

    print(f"## Report of `{obj_name}`")
    print("Function|Score|Max|%")
    print("-|-|-|-")
    for entry in entries:
        print(f"`{entry[0]}`|`{entry[1]}`|`{entry[2]}`|`{entry[3]:.2f}%`")


if __name__ == "__main__":
    import sys

    obj_path = sys.argv[1]
    main(obj_path)
