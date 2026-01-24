#!/usr/bin/env python3
"""
Helper script for LLM-driven decompiling. Fixes any missing imports, then
rebuilds and runs objdiff-cli on the specified function.

Usage:
  tools/checkdiff.py <function_name>
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
import time
from pathlib import Path
from typing import Optional

ROOT = Path(__file__).resolve().parents[1]
REPORT_PATH = ROOT / "build/GALE01/report.json"
SRC_ROOT = ROOT / "src"


def find_unit_for_function(func_name: str) -> Optional[str]:
    with REPORT_PATH.open("r") as f:
        for unit in json.load(f).get("units", []):
            for function in unit.get("functions", []):
                if function.get("name") == func_name:
                    return unit.get("name", "").removeprefix("main/")
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("function", help="Function name")
    args = ap.parse_args()

    func_name = args.function

    # locate object file by parsing report.json
    obj_path = find_unit_for_function(func_name)
    if obj_path is None:
        print(f"error: could not find function '{func_name}' in report.json", file=sys.stderr)
        return 1

    c_file = SRC_ROOT / f"{obj_path}.c"

    # fix includes
    fix_includes = ROOT / "tools" / "fix_includes.py"
    result = subprocess.run(
        [sys.executable, str(fix_includes), str(c_file)],
        cwd=ROOT,
        capture_output=True,
    )
    if result.returncode != 0:
        print(f"fix_includes.py failed:", file=sys.stderr)
        print(result.stderr.decode(), file=sys.stderr)
        return 1

    # build
    ref_obj = f"./build/GALE01/obj/{obj_path}.o"
    our_obj = f"./build/GALE01/src/{obj_path}.o"
    result = subprocess.run(["ninja", our_obj], cwd=ROOT, capture_output=True, text=True)
    if result.returncode != 0:
        print("ninja failed:", file=sys.stderr)
        print(result.stdout)
        print(result.stderr, file=sys.stderr)
        return 1

    # diff
    result = subprocess.run(
        [
            "objdiff-cli-custom", "diff",
            "--format", "diff",
            "-c", "functionRelocDiffs=none",
            "-1", ref_obj,
            "-2", our_obj,
            func_name,
            "-o", "-",
        ],
        cwd=ROOT,
    )

    # kill wine-preloader so we don't eat the user's battery life
    subprocess.run(["killall", "wine-preloader"], capture_output=True)

    return result.returncode


if __name__ == "__main__":
    raise SystemExit(main())
