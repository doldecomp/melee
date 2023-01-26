#!/usr/bin/env python3
import os
import subprocess
from typing import List, Tuple
import json

def main(obj_path: str) -> None:
    build_path = "./build/ssbm.us.1.2/"
    obj_name = os.path.relpath(obj_path, start=build_path).replace(".o", "")

    entries: List[Tuple[str, int, int, float]] = []

    for symbol in subprocess.run(["nm", obj_path], stdout=subprocess.PIPE,
                 universal_newlines=True).stdout.strip().split("\n"):
        if symbol.split()[1] != "T":
            continue
        symbol = symbol.split()[2]
        result = subprocess.run(["python3", "./tools/asm-differ/diff.py", "-o",
                                 symbol, "--format", "json"], stdout=subprocess.PIPE,
                                 universal_newlines=True).stdout.strip()
        result = json.loads(result)
        current_score = int(result["current_score"])
        max_score = int(result["max_score"])

        if current_score == 0:
            continue

        percent = 100 - round(100 * current_score / max_score, 2)
        entries.append((symbol, current_score, max_score, percent))

    entries.sort(key=lambda x: x[3], reverse=True)

    print(f"## Report of `{obj_name}`")
    print("Function|Score|Max|%")
    print("-|-|-|-")
    for entry in entries:
        print(f"`{entry[0]}`|`{entry[1]}`|`{entry[2]}`|`{entry[3]}%`")

if __name__ == "__main__":
    import sys
    obj_path = sys.argv[1]
    main(obj_path)

