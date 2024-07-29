import argparse
from typing import Optional
import json
import sys

def process_json(data):
    result = {}
    for unit in data.get('units', []):
        matching_functions = []
        for function in unit.get('functions', []):
            from_fuzzy = function.get('from', {}).get('fuzzy_match_percent')
            to_fuzzy = function.get('to', {}).get('fuzzy_match_percent')
            if from_fuzzy == 100 and to_fuzzy < from_fuzzy:
                func_name = function.get('name')
                matching_functions.append(f"{func_name} ({from_fuzzy}% -> {to_fuzzy})")

        if matching_functions:
            result[unit.get('name')] = matching_functions

    return result

def process_input(input_file: Optional[str]) -> None:
    content = "";
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
        print("::error::One or more functions were broken!")
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
