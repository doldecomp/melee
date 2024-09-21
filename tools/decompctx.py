#!/usr/bin/env python3

###
# Generates a ctx.c file, usable for "Context" on https://decomp.me.
#
# Usage:
#   python3 tools/decompctx.py src/file.cpp
#
# If changes are made, please submit a PR to
# https://github.com/encounter/dtk-template
###

import argparse
import os
import re
from typing import List

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))
src_dir = os.path.join(root_dir, "src")
include_dirs = [
    os.path.join(root_dir, "include"),
    # Add additional include directories here
]

include_pattern = re.compile(r'^#\s*include\s*[<"](.+?)[>"]$')
guard_pattern = re.compile(r"^#\s*ifndef\s+(.*)$")

defines = set()


def import_h_file(in_file: str, r_path: str, deps: List[str]) -> str:
    rel_path = os.path.join(root_dir, r_path, in_file)
    if os.path.exists(rel_path):
        return import_c_file(rel_path, deps)
    for include_dir in include_dirs:
        inc_path = os.path.join(include_dir, in_file)
        if os.path.exists(inc_path):
            return import_c_file(inc_path, deps)
    else:
        print("Failed to locate", in_file)
        return ""


def import_c_file(in_file: str, deps: List[str]) -> str:
    in_file = os.path.relpath(in_file, root_dir)
    deps.append(in_file)
    out_text = ""

    try:
        with open(in_file, encoding="utf-8") as file:
            out_text += process_file(in_file, list(file), deps)
    except Exception:
        with open(in_file) as file:
            out_text += process_file(in_file, list(file), deps)
    return out_text


def process_file(in_file: str, lines: List[str], deps: List[str]) -> str:
    out_text = ""
    for idx, line in enumerate(lines):
        guard_match = guard_pattern.match(line.strip())
        if idx == 0:
            if guard_match:
                if guard_match[1] in defines:
                    break
                defines.add(guard_match[1])
            print("Processing file", in_file)
        include_match = include_pattern.match(line.strip())
        if include_match and not include_match[1].endswith(".s"):
            out_text += f'/* "{in_file}" line {idx} "{include_match[1]}" */\n'
            out_text += import_h_file(include_match[1], os.path.dirname(in_file), deps)
            out_text += f'/* end "{include_match[1]}" */\n'
        else:
            out_text += line

    return out_text


def sanitize_path(path: str) -> str:
    return path.replace("\\", "/").replace(" ", "\\ ")


def main():
    parser = argparse.ArgumentParser(
        description="""Create a context file which can be used for decomp.me"""
    )
    parser.add_argument(
        "c_file",
        help="""File from which to create context""",
    )
    parser.add_argument(
        "-o",
        "--output",
        help="""Output file""",
        default="ctx.c",
    )
    parser.add_argument(
        "-d",
        "--depfile",
        help="""Dependency file""",
    )
    args = parser.parse_args()

    deps = []
    output = import_c_file(args.c_file, deps)

    with open(os.path.join(root_dir, args.output), "w", encoding="utf-8") as f:
        f.write(output)

    if args.depfile:
        with open(os.path.join(root_dir, args.depfile), "w", encoding="utf-8") as f:
            f.write(sanitize_path(args.output) + ":")
            for dep in deps:
                path = sanitize_path(dep)
                f.write(f" \\\n\t{path}")


if __name__ == "__main__":
    main()
