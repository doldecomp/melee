#!/usr/bin/env python3
import argparse
import json
import os
import sys
from pathlib import Path


def load_json(source: str):
    if source == "-":
        return json.load(sys.stdin)
    with Path(source).open("r", encoding="utf-8") as f:
        return json.load(f)


def main():
    parser = argparse.ArgumentParser(
        description="Filter JSON units like jq '.units[] | select(...) | .name'"
    )
    parser.add_argument("json", help="Path to JSON file, or '-' for stdin")
    args = parser.parse_args()

    data = load_json(args.json)

    unit_names = []

    for unit in data["units"]:
        if unit["measures"]["fuzzy_match_percent"] < 100:
            continue

        if unit["metadata"]["auto_generated"]:
            continue

        if unit["metadata"]["complete"]:
            continue

        unit_names.append(unit["name"].removeprefix("main/"))

    if unit_names:
        print("::warning::One or more units are complete but not linked!")
        print(*unit_names, sep=os.linesep)
        sys.exit(1)


if __name__ == "__main__":
    main()
