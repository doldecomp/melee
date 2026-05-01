#!/usr/bin/env python3

import argparse
import shutil
import subprocess
import sys
from pathlib import Path
from typing import List, Optional


def git_root() -> Path:
    result = subprocess.run(
        ["git", "rev-parse", "--show-toplevel"],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    if result.returncode != 0:
        print("error: not inside a git worktree", file=sys.stderr)
        sys.exit(result.returncode)
    return Path(result.stdout.strip())


def run_git_clang_format(
    root: Path, clang_format: str, base: Optional[str], check: bool
) -> int:
    cmd: List[str] = ["git", "clang-format", "--binary", clang_format]
    if check:
        cmd.append("--diff")
    if base is not None:
        cmd.append(base)

    result = subprocess.run(
        cmd,
        cwd=root,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    if result.stdout:
        print(result.stdout, end="")
    if result.stderr:
        print(result.stderr, end="", file=sys.stderr)
    if result.returncode != 0:
        return result.returncode

    if check and "diff --git" in result.stdout:
        return 1
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Format changed C/C++ lines using git clang-format."
    )
    parser.add_argument(
        "base",
        nargs="?",
        help="optional base revision to compare against",
    )
    parser.add_argument(
        "--check",
        action="store_true",
        help="check formatting without modifying files",
    )
    parser.add_argument(
        "--clang-format",
        default="clang-format",
        help="clang-format executable to use",
    )
    args = parser.parse_args()

    if shutil.which(args.clang_format) is None:
        print(f"error: {args.clang_format} not found", file=sys.stderr)
        return 1
    if shutil.which("git-clang-format") is None:
        print("error: git-clang-format not found", file=sys.stderr)
        return 1

    return run_git_clang_format(
        git_root(), args.clang_format, args.base, args.check
    )


if __name__ == "__main__":
    sys.exit(main())
