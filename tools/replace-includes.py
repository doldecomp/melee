#!/usr/bin/env python3

import logging
from pathlib import Path
import re

IN_ROOTS = [
    Path.cwd().joinpath(s).resolve(strict=True)
    for s in [
        "src",
        "src/Runtime",
        "src/MSL",
        "src/melee",
        "src/melee/ft/kinds",
        "extern/dolphin/include",
        "extern/dolphin/src",
        "build/GALE01/include",
    ]
]

IN_FILES = IN_ROOTS[0].rglob("*.[ch]")

OUT_ROOTS = [
    IN_ROOTS[2],  # src/MSL
    IN_ROOTS[0],  # src
    IN_ROOTS[5],  # extern/dolphin/include
    IN_ROOTS[7],  # build/GALE01/include
]

INCLUDE_RE = re.compile(r'^#include [<"](?P<path>.*?)[>"]$', re.MULTILINE)
DEFAULT_FMT = "#include <{}>"


def main():
    logging.basicConfig(level=logging.WARNING)
    paths = [p.resolve(strict=True) for p in IN_FILES]
    for src_path in paths:
        logging.debug("Opening `%s`", src_path)
        text = src_path.read_text(encoding="utf-8", errors="strict")
        local_root = src_path.joinpath(src_path.parent).resolve(strict=True)
        in_roots = [local_root, *IN_ROOTS]
        out_roots = [*OUT_ROOTS]

        def repl(m: re.Match[str]) -> str:
            mp = Path(m["path"])
            s = m[0]
            logging.debug("Evaluating `%s`", s)

            def put(p: Path) -> str:
                p = p.resolve()
                def decide_fmt() -> tuple[Path, str]:
                    if p.suffix not in {".c", ".h", ".inc"}:
                        logging.warning("Deleting suspicious include `%s`", m[0])
                        return p, ""

                    if src_path.suffix == ".c":
                        try:
                            return p.relative_to(src_path.parent), '#include "{}"'
                        except ValueError:
                            pass

                    for root in out_roots:
                        try:
                            return p.relative_to(root), "#include <{}>"
                        except ValueError:
                            continue
                    logging.error("Out root not found: %s", mp)
                    return p, m[0]

                p, fmt = decide_fmt()
                s = fmt.format(p.as_posix())
                logging.info("Replaced `%s`", s)
                return s

            def search_relative() -> str | None:
                if src_path.suffix == ".c" and mp.is_relative_to(src_path.parent):
                    logging.info(
                        "Relative include: `%s`", p := mp.relative_to(src_path.parent)
                    )
                    return put(p)
                return None

            def search_sus() -> str | None:
                if not mp.suffix in {".c", ".h", ".inc"}:
                    return put(mp)
                return None

            def search_roots() -> str | None:
                for root in in_roots:
                    logging.debug("Trying `%s` / `%s`", root, str(mp))
                    try:
                        resolved = root.joinpath(mp).resolve(strict=True)
                        logging.info("Found `%s`", resolved)

                        return put(resolved)
                    except FileNotFoundError:
                        logging.debug("Did not find `%s` in `%s`", mp, root)
                        continue
                return None

            s = next(
                filter(
                    lambda x: x is not None,
                    map(
                        lambda f: f(),
                        [
                            search_relative,
                            search_sus,
                            search_roots,
                        ],
                    ),
                ),
                None,
            )
            if s is None:
                logging.error("Didn't find `%s`", s := m[0])

            return s

        _ = src_path.write_text(
            INCLUDE_RE.sub(repl, text), encoding="utf-8", errors="strict"
        )


if __name__ == "__main__":
    main()
