#!/usr/bin/env python3

import argparse
from pathlib import Path
import re


def search_string_in_files(search_string: str) -> None:
    # Define the src directory
    src_dir = Path(__file__).parents[1] / "src"

    # Walk through the src directory
    for file in src_dir.rglob("*.h"):
        with open(file, "r") as f:
            contents = f.read()
            # Search for the string as a whole word
            if re.search(r"\b" + re.escape(search_string) + r"\b", contents):
                # Print the include statement with the file path relative to src
                print(f'#include "{file.relative_to(src_dir)}"')
                return

    print(f"No .h file found in src directory containing the string '{search_string}'")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Search for a string in .h files in the src directory."
    )
    parser.add_argument("search_string", help="The string to search for.")
    args = parser.parse_args()

    search_string_in_files(args.search_string)


if __name__ == "__main__":
    main()
