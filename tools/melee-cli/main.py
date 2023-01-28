import argparse
import sys
from typing import Any


def build(args):
    print(args)


def parse_args(args: list[str]) -> Any:

    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers()

    parser_build = subparsers.add_parser(
        "build", aliases=["b"], help="Build the project"
    )

    parser_build.set_defaults(func=build)

    return parser.parse_args(args)


def main():
    args = parse_args(sys.argv[1:])
    args.func(args)


if __name__ == "__main__":
    main()
