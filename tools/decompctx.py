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
import fnmatch
import os
import re
from typing import List

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))
src_dir = os.path.join(root_dir, "src")
include_dirs: List[str] = []  # Set with -I flag
exclude_globs: List[str] = []  # Set with -x flag

include_pattern = re.compile(r'^#\s*include\s*[<"](.+?)[>"]')
guard_pattern = re.compile(r"^#\s*ifndef\s+(.*)$")
once_pattern = re.compile(r"^#\s*pragma\s+once$")

defines = set()
deps = []


def generate_prelude(defines) -> str:
    if len(defines) == 0:
        return ""

    out_text = "/* decompctx prelude */\n"
    for define in defines:
        parts = define.split("=", 1)
        if len(parts) == 2:
            macro_name, macro_val = parts
            out_text += f"#define {macro_name} {macro_val}\n"
        else:
            out_text += f"#define {parts[0]}\n"
    out_text += "/* end decompctx prelude */\n\n"

    return out_text


def import_h_file(in_file: str, r_path: str) -> str:
    rel_path = os.path.join(root_dir, r_path, in_file)
    if os.path.exists(rel_path):
        return import_c_file(rel_path)
    for include_dir in include_dirs:
        inc_path = os.path.join(include_dir, in_file)
        if os.path.exists(inc_path):
            return import_c_file(inc_path)
    else:
        print("Failed to locate", in_file)
        return ""


def import_c_file(in_file: str) -> str:
    in_file = os.path.relpath(in_file, root_dir)
    deps.append(in_file)
    out_text = ""

    try:
        with open(in_file, encoding="utf-8") as file:
            out_text += process_file(in_file, list(file))
    except Exception:
        with open(in_file) as file:
            out_text += process_file(in_file, list(file))
    return out_text


def process_file(in_file: str, lines: List[str]) -> str:
    out_text = ""
    for idx, line in enumerate(lines):
        if idx == 0:
            guard_match = guard_pattern.match(line.strip())
            if guard_match:
                if guard_match[1] in defines:
                    break
                defines.add(guard_match[1])
            else:
                once_match = once_pattern.match(line.strip())
                if once_match:
                    if in_file in defines:
                        break
                    defines.add(in_file)
            print("Processing file", in_file)
        include_match = include_pattern.match(line.strip())
        if include_match and not include_match[1].endswith(".s"):
            excluded = False
            for glob in exclude_globs:
                if fnmatch.fnmatch(include_match[1], glob):
                    excluded = True
                    break

            out_text += f'/* "{in_file}" line {idx} "{include_match[1]}" */\n'
            if excluded:
                out_text += "/* Skipped excluded file */\n"
            else:
                out_text += import_h_file(include_match[1], os.path.dirname(in_file))
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
    parser.add_argument(
        "-I",
        "--include",
        help="""Include directory""",
        action="append",
    )
    parser.add_argument(
        "-x",
        "--exclude",
        help="""Excluded file name glob""",
        action="append",
    )
    parser.add_argument(
        "-D",
        "--define",
        help="""Macro definition""",
        action="append",
    )
    args = parser.parse_args()

    if args.include is None:
        exit("No include directories specified")
    global include_dirs
    include_dirs = args.include
    global exclude_globs
    exclude_globs = args.exclude or []
    prelude_defines = args.define or []
    output = generate_prelude(prelude_defines)
    output += import_c_file(args.c_file)

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
