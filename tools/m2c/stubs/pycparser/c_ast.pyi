# -----------------------------------------------------------------
# pycparser: c_ast.py
#
# AST Node classes.
#
# Eli Bendersky [https://eli.thegreenplace.net/]
# License: BSD
# -----------------------------------------------------------------

from typing import TextIO, Iterable, List, Any, Optional, Union as Union_
from .plyparser import Coord
import sys

class Node(object):
    coord: Optional[Coord]

    def __repr__(self) -> str: ...
    def __iter__(self) -> Iterable[Node]: ...
    def children(self) -> Iterable[Node]: ...
    def show(
        self,
        buf: TextIO = sys.stdout,
        offset: int = 0,
        attrnames: bool = False,
        nodenames: bool = False,
        showcoord: bool = False,
    ) -> None: ...

Expression = Union_[
    "ArrayRef",
    "Assignment",
    "BinaryOp",
    "Cast",
    "CompoundLiteral",
    "Constant",
    "ExprList",
    "FuncCall",
    "ID",
    "StructRef",
    "TernaryOp",
    "UnaryOp",
]
Statement = Union_[
    Expression,
    "Break",
    "Case",
    "Compound",
    "Continue",
    "Decl",
    "Default",
    "DoWhile",
    "EmptyStatement",
    "For",
    "Goto",
    "If",
    "Label",
    "Return",
    "Switch",
    "Typedef",
    "While",
    "Pragma",
]
Type = Union_["PtrDecl", "ArrayDecl", "FuncDecl", "TypeDecl"]
InnerType = Union_["IdentifierType", "Struct", "Union", "Enum"]
ExternalDeclaration = Union_["FuncDef", "Decl", "Typedef", "Pragma"]
AnyNode = Union_[
    Statement,
    Type,
    InnerType,
    "Alignas",
    "FuncDef",
    "EllipsisParam",
    "Enumerator",
    "EnumeratorList",
    "FileAST",
    "InitList",
    "NamedInitializer",
    "ParamList",
    "Typename",
]

class NodeVisitor:
    def visit(self, node: Node) -> None: ...
    def generic_visit(self, node: Node) -> None: ...
    def visit_Alignas(self, node: Alignas) -> None: ...
    def visit_ArrayDecl(self, node: ArrayDecl) -> None: ...
    def visit_ArrayRef(self, node: ArrayRef) -> None: ...
    def visit_Assignment(self, node: Assignment) -> None: ...
    def visit_BinaryOp(self, node: BinaryOp) -> None: ...
    def visit_Break(self, node: Break) -> None: ...
    def visit_Case(self, node: Case) -> None: ...
    def visit_Cast(self, node: Cast) -> None: ...
    def visit_Compound(self, node: Compound) -> None: ...
    def visit_CompoundLiteral(self, node: CompoundLiteral) -> None: ...
    def visit_Constant(self, node: Constant) -> None: ...
    def visit_Continue(self, node: Continue) -> None: ...
    def visit_Decl(self, node: Decl) -> None: ...
    def visit_DeclList(self, node: DeclList) -> None: ...
    def visit_Default(self, node: Default) -> None: ...
    def visit_DoWhile(self, node: DoWhile) -> None: ...
    def visit_EllipsisParam(self, node: EllipsisParam) -> None: ...
    def visit_EmptyStatement(self, node: EmptyStatement) -> None: ...
    def visit_Enum(self, node: Enum) -> None: ...
    def visit_Enumerator(self, node: Enumerator) -> None: ...
    def visit_EnumeratorList(self, node: EnumeratorList) -> None: ...
    def visit_ExprList(self, node: ExprList) -> None: ...
    def visit_FileAST(self, node: FileAST) -> None: ...
    def visit_For(self, node: For) -> None: ...
    def visit_FuncCall(self, node: FuncCall) -> None: ...
    def visit_FuncDecl(self, node: FuncDecl) -> None: ...
    def visit_FuncDef(self, node: FuncDef) -> None: ...
    def visit_Goto(self, node: Goto) -> None: ...
    def visit_ID(self, node: ID) -> None: ...
    def visit_IdentifierType(self, node: IdentifierType) -> None: ...
    def visit_If(self, node: If) -> None: ...
    def visit_InitList(self, node: InitList) -> None: ...
    def visit_Label(self, node: Label) -> None: ...
    def visit_NamedInitializer(self, node: NamedInitializer) -> None: ...
    def visit_ParamList(self, node: ParamList) -> None: ...
    def visit_PtrDecl(self, node: PtrDecl) -> None: ...
    def visit_Return(self, node: Return) -> None: ...
    def visit_Struct(self, node: Struct) -> None: ...
    def visit_StructRef(self, node: StructRef) -> None: ...
    def visit_Switch(self, node: Switch) -> None: ...
    def visit_TernaryOp(self, node: TernaryOp) -> None: ...
    def visit_TypeDecl(self, node: TypeDecl) -> None: ...
    def visit_Typedef(self, node: Typedef) -> None: ...
    def visit_Typename(self, node: Typename) -> None: ...
    def visit_UnaryOp(self, node: UnaryOp) -> None: ...
    def visit_Union(self, node: Union) -> None: ...
    def visit_While(self, node: While) -> None: ...
    def visit_Pragma(self, node: Pragma) -> None: ...

class Alignas(Node):
    alignment: Union_[Expression, Typename]
    coord: Optional[Coord]

    def __init__(
        self,
        alignment: Union_[Expression, Typename],
        coord: Optional[Coord] = None,
    ): ...

class ArrayDecl(Node):
    type: Type
    dim: Optional[Expression]
    dim_quals: List[str]

    def __init__(
        self,
        type: Type,
        dim: Optional[Node],
        dim_quals: List[str],
        coord: Optional[Coord] = None,
    ): ...

class ArrayRef(Node):
    name: Expression
    subscript: Expression

    def __init__(self, name: Node, subscript: Node, coord: Optional[Coord] = None): ...

class Assignment(Node):
    op: str
    lvalue: Expression
    rvalue: Expression

    def __init__(
        self,
        op: str,
        lvalue: Expression,
        rvalue: Expression,
        coord: Optional[Coord] = None,
    ): ...

class BinaryOp(Node):
    op: str
    left: Expression
    right: Expression

    def __init__(
        self, op: str, left: Node, right: Node, coord: Optional[Coord] = None
    ): ...

class Break(Node):
    def __init__(self, coord: Optional[Coord] = None): ...

class Case(Node):
    expr: Expression
    stmts: List[Statement]

    def __init__(
        self, expr: Expression, stmts: List[Statement], coord: Optional[Coord] = None
    ): ...

class Cast(Node):
    to_type: "Typename"
    expr: Expression

    def __init__(
        self, to_type: "Typename", expr: Expression, coord: Optional[Coord] = None
    ): ...

class Compound(Node):
    block_items: Optional[List[Statement]]

    def __init__(
        self, block_items: Optional[List[Statement]], coord: Optional[Coord] = None
    ): ...

class CompoundLiteral(Node):
    type: "Typename"
    init: "InitList"

    def __init__(
        self, type: "Typename", init: "InitList", coord: Optional[Coord] = None
    ): ...

class Constant(Node):
    type: str
    value: str

    def __init__(self, type: str, value: str, coord: Optional[Coord] = None): ...

class Continue(Node):
    def __init__(self, coord: Optional[Coord] = None): ...

class Decl(Node):
    name: Optional[str]
    quals: List[str]  # e.g. const
    align: List[Alignas]
    storage: List[str]  # e.g. register
    funcspec: List[str]  # e.g. inline
    type: Union_[Type, "Struct", "Enum", "Union"]
    init: Optional[Union_[Expression, "InitList"]]
    bitsize: Optional[Expression]

    def __init__(
        self,
        name: Optional[str],
        quals: List[str],
        align: List[Alignas],
        storage: List[str],
        funcspec: List[str],
        type: Union_[Type, "Struct", "Enum", "Union"],
        init: Optional[Union_[Expression, "InitList"]],
        bitsize: Optional[Expression],
        coord: Optional[Coord] = None,
    ): ...

class DeclList(Node):
    decls: List[Decl]

    def __init__(self, decls: List[Decl], coord: Optional[Coord] = None): ...

class Default(Node):
    stmts: List[Statement]

    def __init__(self, stmts: List[Statement], coord: Optional[Coord] = None): ...

class DoWhile(Node):
    cond: Expression
    stmt: Statement

    def __init__(
        self, cond: Expression, stmt: Statement, coord: Optional[Coord] = None
    ): ...

class EllipsisParam(Node):
    def __init__(self, coord: Optional[Coord] = None): ...

class EmptyStatement(Node):
    def __init__(self, coord: Optional[Coord] = None): ...

class Enum(Node):
    name: Optional[str]
    values: "Optional[EnumeratorList]"

    def __init__(
        self,
        name: Optional[str],
        values: "Optional[EnumeratorList]",
        coord: Optional[Coord] = None,
    ): ...

class Enumerator(Node):
    name: str
    value: Optional[Expression]

    def __init__(
        self, name: str, value: Optional[Expression], coord: Optional[Coord] = None
    ): ...

class EnumeratorList(Node):
    enumerators: List[Enumerator]

    def __init__(
        self, enumerators: List[Enumerator], coord: Optional[Coord] = None
    ): ...

class ExprList(Node):
    exprs: List[Union_[Expression, Typename]]  # typename only for offsetof

    def __init__(
        self, exprs: List[Union_[Expression, Typename]], coord: Optional[Coord] = None
    ): ...

class FileAST(Node):
    ext: List[ExternalDeclaration]

    def __init__(
        self, ext: List[ExternalDeclaration], coord: Optional[Coord] = None
    ): ...

class For(Node):
    init: Union_[None, Expression, DeclList]
    cond: Optional[Expression]
    next: Optional[Expression]
    stmt: Statement

    def __init__(
        self,
        init: Union_[None, Expression, DeclList],
        cond: Optional[Expression],
        next: Optional[Expression],
        stmt: Statement,
        coord: Optional[Coord] = None,
    ): ...

class FuncCall(Node):
    name: Expression
    args: Optional[ExprList]

    def __init__(
        self, name: Expression, args: Optional[ExprList], coord: Optional[Coord] = None
    ): ...

class FuncDecl(Node):
    args: Optional[ParamList]
    type: Type  # return type

    def __init__(
        self, args: Optional[ParamList], type: Type, coord: Optional[Coord] = None
    ): ...

class FuncDef(Node):
    decl: Decl
    param_decls: Optional[List[Decl]]
    body: Compound

    def __init__(
        self,
        decl: Decl,
        param_decls: Optional[List[Decl]],
        body: Compound,
        coord: Optional[Coord] = None,
    ): ...

class Goto(Node):
    name: str

    def __init__(self, name: str, coord: Optional[Coord] = None): ...

class ID(Node):
    name: str

    def __init__(self, name: str, coord: Optional[Coord] = None): ...

class IdentifierType(Node):
    names: List[str]  # e.g. ['long', 'int']

    def __init__(self, names: List[str], coord: Optional[Coord] = None): ...

class If(Node):
    cond: Expression
    iftrue: Statement
    iffalse: Optional[Statement]

    def __init__(
        self,
        cond: Expression,
        iftrue: Statement,
        iffalse: Optional[Statement],
        coord: Optional[Coord] = None,
    ): ...

class InitList(Node):
    exprs: List[Union_[Expression, "NamedInitializer"]]

    def __init__(
        self,
        exprs: List[Union_[Expression, "NamedInitializer"]],
        coord: Optional[Coord] = None,
    ): ...

class Label(Node):
    name: str
    stmt: Statement

    def __init__(self, name: str, stmt: Statement, coord: Optional[Coord] = None): ...

class NamedInitializer(Node):
    name: List[Expression]  # [ID(x), Constant(4)] for {.x[4] = ...}
    expr: Expression

    def __init__(
        self, name: List[Expression], expr: Expression, coord: Optional[Coord] = None
    ): ...

class ParamList(Node):
    params: List[Union_[Decl, ID, Typename, EllipsisParam]]

    def __init__(
        self,
        params: List[Union_[Decl, ID, Typename, EllipsisParam]],
        coord: Optional[Coord] = None,
    ): ...

class PtrDecl(Node):
    quals: List[str]
    type: Type

    def __init__(self, quals: List[str], type: Type, coord: Optional[Coord] = None): ...

class Return(Node):
    expr: Optional[Expression]

    def __init__(self, expr: Optional[Expression], coord: Optional[Coord] = None): ...

class Struct(Node):
    name: Optional[str]
    decls: Optional[List[Union_[Decl, Pragma]]]

    def __init__(
        self,
        name: Optional[str],
        decls: Optional[List[Union_[Decl, Pragma]]],
        coord: Optional[Coord] = None,
    ): ...

class StructRef(Node):
    name: Expression
    type: str
    field: ID

    def __init__(
        self, name: Expression, type: str, field: ID, coord: Optional[Coord] = None
    ): ...

class Switch(Node):
    cond: Expression
    stmt: Statement

    def __init__(
        self, cond: Expression, stmt: Statement, coord: Optional[Coord] = None
    ): ...

class TernaryOp(Node):
    cond: Expression
    iftrue: Expression
    iffalse: Expression

    def __init__(
        self,
        cond: Expression,
        iftrue: Expression,
        iffalse: Expression,
        coord: Optional[Coord] = None,
    ): ...

class TypeDecl(Node):
    declname: Optional[str]
    quals: List[str]
    type: InnerType
    align: List[Alignas]

    def __init__(
        self,
        declname: Optional[str],
        quals: List[str],
        align: List[Alignas],
        type: InnerType,
        coord: Optional[Coord] = None,
    ): ...

class Typedef(Node):
    name: str
    quals: List[str]
    storage: List[str]
    type: Type

    def __init__(
        self,
        name: str,
        quals: List[str],
        storage: List[str],
        type: Type,
        coord: Optional[Coord] = None,
    ): ...

class Typename(Node):
    name: None
    quals: List[str]
    align: List[Alignas]
    type: Type

    def __init__(
        self,
        name: None,
        quals: List[str],
        align: List[Alignas],
        type: Type,
        coord: Optional[Coord] = None,
    ): ...

class UnaryOp(Node):
    op: str
    expr: Union_[Expression, Typename]

    def __init__(
        self, op: str, expr: Union_[Expression, Typename], coord: Optional[Coord] = None
    ): ...

class Union(Node):
    name: Optional[str]
    decls: Optional[List[Union_[Decl, Pragma]]]

    def __init__(
        self,
        name: Optional[str],
        decls: Optional[List[Union_[Decl, Pragma]]],
        coord: Optional[Coord] = None,
    ): ...

class While(Node):
    cond: Expression
    stmt: Statement

    def __init__(
        self, cond: Expression, stmt: Statement, coord: Optional[Coord] = None
    ): ...

class Pragma(Node):
    string: str

    def __init__(self, string: str, coord: Optional[Coord] = None): ...
