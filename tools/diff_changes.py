#!/usr/bin/env python3
import argparse
import json
import sys
from typing import Optional


def process_json(data):
    result = {}
    for unit in data.get("units", []):
        matching_functions = []
        for function in unit.get("functions", []):
            if function is None:
                continue

            def get_fuzzy(key) -> float:
                obj = function.get(key) or {}
                return obj.get("fuzzy_match_percent") or 0

            from_fuzzy = get_fuzzy("from")
            to_fuzzy = get_fuzzy("to")
            if from_fuzzy == 100 and to_fuzzy < from_fuzzy:
                func_name = function.get("name")
                matching_functions.append(f"{func_name} ({from_fuzzy}% -> {to_fuzzy})")

        if matching_functions:
            result[unit.get("name")] = matching_functions

    return result


def process_input(input_file: Optional[str]) -> None:
    content = ""
    if input_file == "-" or not input_file:
        content = json.load(sys.stdin)
    else:
        with open(input_file, "r") as f:
            content = json.load(f)

    result = process_json(content)
    if not result:
        print("No functions broken.")
        sys.exit(0)
    else:
        print("::warning One or more functions were broken!")
        sys.stdout.write(json.dumps(result, indent=2))
        sys.exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="List broken functions from the output of objdiff's `changes` command."
    )
    parser.add_argument(
        "input_file",
        metavar="INPUT_FILE",
        nargs="?",
        default="",
        help='input file to process (use "-" for stdin)',
    )
    args = parser.parse_args()

    if args.input_file != "":
        process_input(args.input_file)
    else:
        print("No argument provided to diff_changes.py.")
        sys.exit(1)
