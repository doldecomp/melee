# ------------------------------------------------------------------------------
# pycparser: c_generator.py
#
# C code generator from pycparser AST nodes.
#
# Eli Bendersky [https://eli.thegreenplace.net/]
# License: BSD
# ------------------------------------------------------------------------------
from . import c_ast

class CGenerator:
    def __init__(self) -> None: ...
    def visit(self, node: c_ast.Node) -> str: ...
