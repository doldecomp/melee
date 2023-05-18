#!/usr/bin/env python3

import argparse
import re
import sys
from typing import Optional


def convert_hex(content: str) -> str:
    return re.sub(
        r"\b0x([0-9a-fA-F]{1,7})U?\b",
        lambda x: str(int(x.group(1), 16)),
        content,
    )


def process_input(input_file: Optional[str]) -> None:
    if input_file == "-" or not input_file:
        content = sys.stdin.read()
        sys.stdout.write(convert_hex(content))
    else:
        with open(input_file, "r") as f:
            content = f.read()

        content = convert_hex(content)

        with open(input_file, "w") as f:
            f.write(content)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Convert hexadecimal numbers to decimal in a text file"
    )
    parser.add_argument(
        "input_file",
        metavar="INPUT_FILE",
        nargs="?",
        default="",
        help='input file to process (use "-" for stdin)',
    )
    args = parser.parse_args()

    process_input(args.input_file)
