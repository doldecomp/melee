#!/usr/bin/env python3
import argparse
import sys
from typing import Any

from commands import build, replace


def parse_args(args: list[str]) -> Any:
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers()
    build.attach_subparser(subparsers)
    replace.attach_subparser(subparsers)

    return parser.parse_args(args)


def main():
    args = parse_args(sys.argv[1:])
    args.func(args)


if __name__ == "__main__":
    main()
