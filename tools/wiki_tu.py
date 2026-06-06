#!/usr/bin/env python3

import argparse
import json
import sys
from pathlib import Path
from typing import Dict, Optional, cast

import humanfriendly
import mistletoe
from mistletoe.block_token import BlockToken, Table, TableRow, re
from mistletoe.span_token import RawText
from mistletoe.token import Token


def read_wiki(lines) -> Dict[str, Dict[str, str]]:
    assignees = {}

    def read_text(token: Token) -> str:
        if isinstance(token, RawText):
            return re.sub(r"<!--.*?-->", "", cast(str, token.content)).strip()

        assert token.children is not None
        return read_text(next(c for c in token.children))

    def read_tr(token: TableRow):
        assert token.children is not None
        td = list(map(read_text, token.children))

        assignee = {}
        if len(td) > 5 and td[5]:
            assignee["discord"] = td[5]
        if len(td) > 6 and td[6]:
            assignee["github"] = td[6]

        if assignee:
            assignees[td[0]] = assignee

    def read_table(token: Table):
        assert token.children is not None
        for child in token.children:
            if isinstance(child, TableRow):
                read_tr(child)

    def read_block(token: BlockToken):
        assert token.children is not None
        for child in token.children:
            if isinstance(child, Table):
                read_table(child)
            elif isinstance(child, BlockToken):
                read_block(child)

    read_block(mistletoe.Document(lines))
    return assignees


def read(args):
    if args.wiki_path == "-":
        fp = sys.stdin
    else:
        fp = Path(args.wiki_path).open("r")

    assignees = read_wiki(fp)
    __import__("pprint").pprint(assignees)


def write(args):
    if args.report_path == "-":
        data = json.load(sys.stdin)
    else:
        path = Path(args.report_path)
        data = json.load(path.open("r"))

    assignees = {}
    if cast(Optional[Path], args.wiki_path):
        md = args.wiki_path.read_text()
        assignees = read_wiki(md)

    def friendly_size(value: int) -> str:
        # Non-breaking space so sizes like "1.18 KB" do not wrap in a cell.
        size = humanfriendly.format_size(value).replace("bytes", "B")
        return size.replace(" ", "&nbsp;")

    def percent_cell(matched: int, total: int, reported: Optional[float]) -> str:
        # A TU with no section of this kind has nothing to match.
        if total == 0:
            return "&mdash;"
        pct = reported if reported is not None else (100.0 * matched / total)
        return f"`{humanfriendly.round_number(float(pct))}%`"

    def file_of(unit) -> str:
        # Strip the leading module ("main/") by splitting and recombining.
        return "/".join((unit["name"] or "/").split("/")[1:])

    def assignee_cells(file: str):
        assignee = assignees.get(file, {})
        if "discord" in assignee:
            # Exactly one leading "@", whether or not the parsed value had one.
            discord = f"`@{assignee['discord'].lstrip('@')}`"
        else:
            discord = "<!-- Discord -->"
        if "github" in assignee:
            github = f"[{assignee['github']}](../commits?author={assignee['github']})"
        else:
            github = "<!-- GitHub -->"
        return discord, github

    def percent_cells(unit):
        measures = unit["measures"]
        text = percent_cell(
            int(measures.get("matched_code") or 0),
            int(measures.get("total_code") or 0),
            measures.get("matched_code_percent"),
        )
        data = percent_cell(
            int(measures.get("matched_data") or 0),
            int(measures.get("total_data") or 0),
            measures.get("matched_data_percent"),
        )
        return text, data

    def row_full(unit) -> str:
        file = file_of(unit)
        file_link = f"[`{file}`](../blob/master/src/{file}.c)"
        matched = friendly_size(int(unit["measures"].get("matched_code") or 0))
        total = friendly_size(int(unit["measures"].get("total_code") or 0))
        text, data = percent_cells(unit)
        discord, github = assignee_cells(file)
        return f"{file_link}|{matched}|{total}|{text}|{data}|{discord}|{github}"

    def row_slim(unit) -> str:
        file = file_of(unit)
        file_link = f"[`{file}`](../blob/master/src/{file}.c)"
        text, data = percent_cells(unit)
        return f"{file_link}|{text}|{data}"

    # Bucket each TU by how far it has progressed. "complete" (fully linked) is
    # the canonical done flag -- it drives the official completed-unit count --
    # so it wins; otherwise split on whether .text is fully matched.
    in_progress = []
    data_left = []
    linked = []
    for unit in data["units"] or []:
        if unit["metadata"].get("complete"):
            linked.append(unit)
        elif float(unit["measures"].get("matched_code_percent") or 0) >= 100:
            data_left.append(unit)
        else:
            in_progress.append(unit)

    full_header = (
        "File|Matched|Total|.text %|data %|Assignee<br>Discord|Assignee<br>GitHub\n"
        "-|-|-|-|-|-|-"
    )
    slim_header = "File|.text %|data %\n-|-|-"

    print(
        "# Translation Units\n\n"
        "Edit this page and fill in your own username to assign yourself to a file.\n\n"
        "Just write your username as plaintext and it will be formatted "
        "automatically later.\n\n"
        "Each TU has two matching signals: **.text %** (code) and **data %**. "
        "A TU moves into **Fully linked** once it is marked complete "
        "(`.text` and data matched and linked into the build)."
    )

    # The count goes on its own line below each header so the header text --
    # and therefore the section's anchor URL -- stays stable as counts change.
    print("\n## .text in progress\n")
    print(f"{len(in_progress)} translation units\n")
    print(full_header)
    for unit in in_progress:
        print(row_full(unit))

    print("\n## .text matched - data / linking left\n")
    print(f"{len(data_left)} translation units\n")
    print(full_header)
    for unit in data_left:
        print(row_full(unit))

    print("\n## Fully linked\n")
    print(f"{len(linked)} translation units\n")
    print(slim_header)
    for unit in linked:
        print(row_slim(unit))


def main():
    parser = argparse.ArgumentParser(
        description="Generates and parses the wiki's list of translation units."
    )
    subparsers = parser.add_subparsers(dest="subcommand")

    parser_write = subparsers.add_parser("write", help="Write JSON data to a file.")
    parser_write.add_argument(
        "report_path",
        metavar="REPORT",
        nargs="?",
        const="-",
        default=None,
        type=str,
        help="Path to the JSON report generated by objdiff-cli.",
    )
    parser_write.add_argument(
        "wiki_path",
        metavar="WIKI",
        nargs="?",
        default=None,
        type=Path,
        help="Path to the existing Translation Units wiki page.",
    )
    parser_write.set_defaults(func=write)

    parser_read = subparsers.add_parser("read", help="test reading markdown")
    parser_read.add_argument(
        "wiki_path",
        metavar="WIKI",
        nargs="?",
        const="-",
        default=None,
        type=str,
        help="Path to the wiki markdown.",
    )
    parser_read.set_defaults(func=read)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
