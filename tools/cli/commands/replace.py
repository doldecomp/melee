import itertools
import re

import utils


def multiple_replace(text, find_dict, pattern, ignore_case: bool):
    matches = list(pattern.finditer(text))
    matches.reverse()
    for match in matches:
        key = match.group()

        if ignore_case:
            key = key.lower()

        text = text[: match.start()] + find_dict[key] + text[match.end() :]
    return text


def run(args):
    pairs = [pair.split("=") for pair in args.pairs]

    if args.reverse:
        pairs = [(b, a) for (a, b) in pairs]

    if args.ignore_case:
        re_flags = re.IGNORECASE
        get_case = lambda s: s.lower()
    else:
        re_flags = re.NOFLAG
        get_case = lambda s: s

    find_dict = {get_case(x[0]): x[1] for x in pairs}

    pattern_str = "|".join(map(re.escape, find_dict.keys()))

    if not args.no_boundaries:
        pattern_str = rf"\b(?:{pattern_str})\b"

    pattern = re.compile(pattern_str, flags=re_flags)

    paths = itertools.chain(utils.get_src_files(), utils.get_asm_files())

    for path in paths:
        text = path.read_text()
        text = multiple_replace(text, find_dict, pattern, args.ignore_case)
        path.write_text(text)


def attach_subparser(subparsers):
    parser = subparsers.add_parser(
        "replace", aliases=["r"], help="replace a symbol in source files"
    )

    parser.add_argument(
        "pairs",
        nargs="+",
        type=str,
        metavar="PATTERN=REPLACEMENT",
        help="replace PATTERN with REPLACEMENT in all files",
    )

    parser.add_argument(
        "-b",
        "--no-boundaries",
        action="store_true",
        help="do not respect word boundaries",
    )

    parser.add_argument(
        "-i",
        "--ignore-case",
        action="store_true",
        help="perform case-insensitive replacements",
    )

    parser.add_argument(
        "-r",
        "--reverse",
        action="store_true",
        help="perform the replacements in reverse",
    )

    parser.set_defaults(func=run)
