# ------------------------------------------------------------------------------
# pycparser: c_parser.py
#
# CParser class: Parser and AST builder for the C language
#
# Eli Bendersky [https://eli.thegreenplace.net/]
# License: BSD
# ------------------------------------------------------------------------------

from . import c_ast
from typing import Any, Dict, List, Optional

class CParser:
    clex: Any  # CLexer
    cparser: Any  # LRParser
    _scope_stack: List[Dict[str, bool]]
    _last_yielded_token: Optional[Any]

    def __init__(self) -> None: ...
    def parse(
        self, text: str, filename: str = "", debuglevel: int = 0
    ) -> c_ast.FileAST: ...
