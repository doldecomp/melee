# -----------------------------------------------------------------
# plyparser.py
#
# PLYParser class and other utilites for simplifying programming
# parsers with PLY
#
# Eli Bendersky [https://eli.thegreenplace.net/]
# License: BSD
# -----------------------------------------------------------------

from typing import Optional


class Coord:
    file: str
    line: int
    column: Optional[int]

    def __init__(self, file: str, line: int, column: Optional[int] = None):
        ...

    def __str__(self) -> str:
        ...


class ParseError(Exception):
    pass
