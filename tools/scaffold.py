#!/usr/bin/env python3

import argparse
import json
from pathlib import Path
from typing import NoReturn, TextIO, cast

ROOT = Path(__file__).parents[1]
DTK_ROOT = ROOT / "build/GALE01"
REPORT_PATH = DTK_ROOT / "report.json"
SRC_ROOT = ROOT / "src"
MODULE = "main"


def wip(msg: str = "") -> NoReturn:
    raise NotImplementedError(msg)


def main() -> None:
    def sanitize_path(s: str) -> tuple[Path, str]:
        p = Path(s).resolve()
        s = f"{MODULE}/{(p.parent / p.stem)
                        .relative_to(SRC_ROOT)
                        .as_posix()
                        .replace("\\", "/")}"

        return p, s

    parser = argparse.ArgumentParser()
    _ = parser.add_argument(
        "paths",
        metavar="SRC_FILE",
        type=sanitize_path,
        nargs="+",
    )
    args = parser.parse_args()

    with REPORT_PATH.open("r") as fp:
        report = json.load(fp)

    units: dict[str, list[Path]] = {}

    for p, s in cast(list[tuple[Path, str]], args.paths):
        if not s in units:
            units[s] = [p]
        else:
            l = units[s]
            l.append(p)
            l.sort()

    for unit in report.get("units", []):
        unit_name: str = unit["name"]
        if unit_name not in units.keys():
            continue

        buffers: list[tuple[Path, TextIO]] = [
            (p, p.open("a")) for p in units[unit_name]
        ]

        for function in unit.get("functions", []):
            func_name: str = function["name"]
            address = int(function["metadata"]["virtual_address"])
            short_address = f"{address:X}"[-6:]

            for path, fp in buffers:
                match path.suffix:
                    case ".c":
                        format = "/// #{name}\n"
                    case ".h":
                        format = "/* {short_address} */ UNK_RET {name}(UNK_PARAMS);"
                    case _:
                        raise ValueError(f'Unknown filetype "{path.suffix}"')

                print(
                    format.format(
                        name=func_name,
                        short_address=short_address,
                    ),
                    file=fp,
                )

        for _, fp in buffers:
            fp.close()


if __name__ == "__main__":
    main()
