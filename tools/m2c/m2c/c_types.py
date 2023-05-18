"""This file handles variable types, function signatures and struct layouts
based on a C AST. Based on the pycparser library."""

import copy
import functools
import hashlib
import pickle
import re
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path
from typing import (
    ClassVar,
    Dict,
    List,
    Match,
    Optional,
    Set,
    Tuple,
    Union,
    cast,
)

from pycparser import c_ast as ca
from pycparser.c_ast import ArrayDecl, FuncDecl, IdentifierType, PtrDecl, TypeDecl
from pycparser.c_generator import CGenerator
from pycparser.c_parser import CParser
from pycparser.plyparser import ParseError

from .error import DecompFailure

CType = Union[PtrDecl, ArrayDecl, TypeDecl, FuncDecl]
StructUnion = Union[ca.Struct, ca.Union]
SimpleType = Union[PtrDecl, TypeDecl]
CParserScope = Dict[str, bool]


@dataclass
class StructField:
    type: CType
    size: int
    name: str


@dataclass
class Struct:
    type: CType
    fields: Dict[int, List[StructField]]
    # TODO: bitfields
    has_bitfields: bool
    size: int
    align: int


@dataclass
class Array:
    subtype: "DetailedStructMember"
    subctype: CType
    subsize: int
    dim: int


DetailedStructMember = Union[Array, Struct, None]


@dataclass
class Param:
    type: CType
    name: Optional[str]


@dataclass
class Function:
    type: CType
    ret_type: Optional[CType]
    params: Optional[List[Param]]
    is_variadic: bool


@dataclass(eq=False)
class Enum:
    tag: Optional[str]
    names: Dict[int, str]


@dataclass(eq=False)
class TypeMap:
    # Change VERSION if TypeMap changes to invalidate all preexisting caches
    VERSION: ClassVar[int] = 4

    cparser_scope: CParserScope = field(default_factory=dict)
    source_hash: Optional[str] = None

    typedefs: Dict[str, CType] = field(default_factory=dict)
    var_types: Dict[str, CType] = field(default_factory=dict)
    vars_with_initializers: Set[str] = field(default_factory=set)
    functions: Dict[str, Function] = field(default_factory=dict)
    structs: Dict[Union[str, StructUnion], Struct] = field(default_factory=dict)
    struct_typedefs: Dict[Union[str, StructUnion], TypeDecl] = field(
        default_factory=dict
    )
    enums: Dict[Union[str, ca.Enum], Enum] = field(default_factory=dict)
    enum_values: Dict[str, int] = field(default_factory=dict)


def to_c(node: ca.Node) -> str:
    return CGenerator().visit(node)


def basic_type(names: List[str]) -> TypeDecl:
    idtype = IdentifierType(names=names)
    return TypeDecl(declname=None, quals=[], type=idtype, align=[])


def pointer(type: CType) -> CType:
    return PtrDecl(quals=[], type=type)


def resolve_typedefs(type: CType, typemap: TypeMap) -> CType:
    while (
        isinstance(type, TypeDecl)
        and isinstance(type.type, IdentifierType)
        and len(type.type.names) == 1
        and type.type.names[0] in typemap.typedefs
    ):
        type = typemap.typedefs[type.type.names[0]]
    return type


def type_of_var_decl(decl: ca.Decl) -> CType:
    assert not isinstance(
        decl.type, (ca.Struct, ca.Union, ca.Enum)
    ), "decls that declare variables have CType types"
    return decl.type


def type_from_global_decl(decl: ca.Decl) -> CType:
    """Get the CType of a global Decl, stripping names of function parameters."""
    tp = type_of_var_decl(decl)
    if not isinstance(tp, ca.FuncDecl) or not tp.args:
        return tp

    def anonymize_param(param: ca.Decl) -> ca.Typename:
        param = copy.deepcopy(param)
        param.name = None
        set_decl_name(param)
        return ca.Typename(
            name=None, quals=param.quals, type=type_of_var_decl(param), align=[]
        )

    new_params: List[Union[ca.Decl, ca.ID, ca.Typename, ca.EllipsisParam]] = [
        anonymize_param(param) if isinstance(param, ca.Decl) else param
        for param in tp.args.params
    ]
    return ca.FuncDecl(args=ca.ParamList(new_params), type=tp.type)


def is_void(type: CType) -> bool:
    return (
        isinstance(type, ca.TypeDecl)
        and isinstance(type.type, ca.IdentifierType)
        and type.type.names == ["void"]
    )


def primitive_size(type: Union[ca.Enum, ca.IdentifierType]) -> int:
    if isinstance(type, ca.Enum):
        return 4
    names = type.names
    if "double" in names:
        return 8
    if "float" in names:
        return 4
    if "short" in names:
        return 2
    if "char" in names:
        return 1
    if "void" in names:
        return 0
    if names.count("long") == 2:
        return 8
    return 4


def primitive_range(type: Union[ca.Enum, ca.IdentifierType]) -> Optional[range]:
    bits = 8 * primitive_size(type)
    signed = True
    if not isinstance(type, ca.Enum):
        names = type.names
        if "double" in names or "float" in names or "void" in names:
            return None
        if "unsigned" in names:
            signed = False
    if signed:
        bits -= 1
        return range(-(2**bits), 2**bits)
    else:
        return range(0, 2**bits)


def function_arg_size_align(type: CType, typemap: TypeMap) -> Tuple[int, int]:
    type = resolve_typedefs(type, typemap)
    if isinstance(type, PtrDecl) or isinstance(type, ArrayDecl):
        return 4, 4
    assert not isinstance(type, FuncDecl), "Function argument can not be a function"
    inner_type = type.type
    if isinstance(inner_type, (ca.Struct, ca.Union)):
        struct = get_struct(inner_type, typemap)
        assert (
            struct is not None
        ), "Function argument can not be of an incomplete struct"
        return struct.size, struct.align
    size = primitive_size(inner_type)
    if size == 0:
        raise DecompFailure("Function parameter has void type")
    return size, size


def is_struct_type(type: CType, typemap: TypeMap) -> bool:
    type = resolve_typedefs(type, typemap)
    if not isinstance(type, TypeDecl):
        return False
    return isinstance(type.type, (ca.Struct, ca.Union))


def is_unk_type(type: CType, typemap: TypeMap) -> bool:
    """Return True if `type` represents an unknown type, or undetermined struct padding."""
    # Check for types matching "char unk_N[...];" or "char padN[...];"
    if (
        isinstance(type, ArrayDecl)
        and isinstance(type.type, TypeDecl)
        and isinstance(type.type.type, IdentifierType)
        and type.type.declname is not None
        and type.type.type.names == ["char"]
    ):
        declname = type.type.declname
        if declname.startswith("unk_") or declname.startswith("pad"):
            return True

    # Check for types which are typedefs starting with "UNK_" or "M2C_UNK",
    # or are arrays/pointers to one of these types.
    while True:
        if (
            isinstance(type, TypeDecl)
            and isinstance(type.type, IdentifierType)
            and len(type.type.names) == 1
            and type.type.names[0] in typemap.typedefs
        ):
            type_name = type.type.names[0]
            if type_name.startswith("UNK_") or type_name.startswith("M2C_UNK"):
                return True
            type = typemap.typedefs[type_name]
        elif isinstance(type, (PtrDecl, ArrayDecl)):
            type = type.type
        else:
            return False


def parse_function(fn: CType) -> Optional[Function]:
    if not isinstance(fn, FuncDecl):
        return None
    params: List[Param] = []
    is_variadic = False
    has_void = False
    if fn.args:
        for arg in fn.args.params:
            if isinstance(arg, ca.EllipsisParam):
                is_variadic = True
            elif isinstance(arg, ca.Decl):
                params.append(Param(type=type_of_var_decl(arg), name=arg.name))
            elif isinstance(arg, ca.ID):
                raise DecompFailure(
                    "K&R-style function header is not supported: " + to_c(fn)
                )
            else:
                assert isinstance(arg, ca.Typename)
                if is_void(arg.type):
                    has_void = True
                else:
                    params.append(Param(type=arg.type, name=None))
    maybe_params: Optional[List[Param]] = params
    if not params and not has_void and not is_variadic:
        # Function declaration without a parameter list
        maybe_params = None
    ret_type = None if is_void(fn.type) else fn.type
    return Function(
        type=fn, ret_type=ret_type, params=maybe_params, is_variadic=is_variadic
    )


def divmod_towards_zero(lhs: int, rhs: int, op: str) -> int:
    if rhs < 0:
        rhs = -rhs
        lhs = -lhs
    if lhs < 0:
        return -divmod_towards_zero(-lhs, rhs, op)
    if op == "/":
        return lhs // rhs
    else:
        return lhs % rhs


def parse_constant_int(expr: "ca.Expression", typemap: TypeMap) -> int:
    if isinstance(expr, ca.Constant):
        try:
            return int(expr.value.rstrip("lLuU"), 0)
        except ValueError:
            raise DecompFailure(f"Failed to parse {to_c(expr)} as an int literal")
    if isinstance(expr, ca.ID):
        if expr.name in typemap.enum_values:
            return typemap.enum_values[expr.name]
    if isinstance(expr, ca.BinaryOp):
        op = expr.op
        lhs = parse_constant_int(expr.left, typemap)
        if op == "&&" and lhs == 0:
            return 0
        if op == "||" and lhs != 0:
            return 1
        rhs = parse_constant_int(expr.right, typemap)
        if op == "+":
            return lhs + rhs
        if op == "-":
            return lhs - rhs
        if op == "*":
            return lhs * rhs
        if op == "<<":
            return lhs << rhs
        if op == ">>":
            return lhs >> rhs
        if op == "&":
            return lhs & rhs
        if op == "|":
            return lhs | rhs
        if op == "^":
            return lhs ^ rhs
        if op == ">=":
            return 1 if lhs >= rhs else 0
        if op == "<=":
            return 1 if lhs <= rhs else 0
        if op == ">":
            return 1 if lhs > rhs else 0
        if op == "<":
            return 1 if lhs < rhs else 0
        if op == "==":
            return 1 if lhs == rhs else 0
        if op == "!=":
            return 1 if lhs != rhs else 0
        if op in ["&&", "||"]:
            return 1 if rhs != 0 else 0
        if op in ["/", "%"]:
            if rhs == 0:
                raise DecompFailure(
                    f"Division by zero when evaluating expression {to_c(expr)}"
                )
            return divmod_towards_zero(lhs, rhs, op)
    if isinstance(expr, ca.TernaryOp):
        cond = parse_constant_int(expr.cond, typemap) != 0
        return parse_constant_int(expr.iftrue if cond else expr.iffalse, typemap)
    if isinstance(expr, ca.ExprList) and not isinstance(expr.exprs[-1], ca.Typename):
        return parse_constant_int(expr.exprs[-1], typemap)
    if isinstance(expr, ca.UnaryOp) and not isinstance(expr.expr, ca.Typename):
        sub = parse_constant_int(expr.expr, typemap)
        if expr.op == "-":
            return -sub
        if expr.op == "~":
            return ~sub
        if expr.op == "!":
            return 1 if sub == 0 else 1
    if isinstance(expr, ca.UnaryOp) and isinstance(expr.expr, ca.Typename):
        size, align, _ = parse_struct_member(
            expr.expr.type, f"referenced in {expr.op}", typemap, allow_unsized=False
        )
        if expr.op == "sizeof":
            return size
        if expr.op == "_Alignof":
            return align
    if isinstance(expr, ca.Cast):
        value = parse_constant_int(expr.expr, typemap)
        type = resolve_typedefs(expr.to_type.type, typemap)
        if isinstance(type, ca.TypeDecl) and isinstance(
            type.type, (ca.Enum, ca.IdentifierType)
        ):
            rng = primitive_range(type.type)
            if rng is not None:
                return rng.start + (value - rng.start) % (rng.stop - rng.start)
    raise DecompFailure(
        f"Failed to evaluate expression {to_c(expr)} at compile time; only simple arithmetic is supported for now"
    )


def parse_enum(enum: ca.Enum, typemap: TypeMap) -> None:
    """Parse an enum and compute the values of all its enumerators, for use in
    constant evaluation.

    We match IDO in treating all enums as having size 4, so no need to compute
    size or alignment here."""
    if enum.values is None:
        return

    typemap_enum = Enum(tag=enum.name, names={})
    typemap.enums[enum] = typemap_enum
    if enum.name is not None and enum.name not in typemap.enums:
        typemap.enums[enum.name] = typemap_enum

    next_value = 0
    for enumerator in enum.values.enumerators:
        if enumerator.value:
            value = parse_constant_int(enumerator.value, typemap)
        else:
            value = next_value
        next_value = value + 1
        typemap.enum_values[enumerator.name] = value
        # If there are multiple names mapping to a single value, take the last one
        typemap_enum.names[value] = enumerator.name


def get_struct(
    struct: Union[ca.Struct, ca.Union], typemap: TypeMap
) -> Optional[Struct]:
    if struct.name:
        return typemap.structs.get(struct.name)
    else:
        return typemap.structs.get(struct)


class UndefinedStructError(DecompFailure):
    pass


def parse_struct(struct: Union[ca.Struct, ca.Union], typemap: TypeMap) -> Struct:
    existing = get_struct(struct, typemap)
    if existing:
        return existing
    if struct.decls is None:
        raise UndefinedStructError(
            f"Tried to use struct {struct.name} before it is defined (does it have a definition?)."
        )
    ret = do_parse_struct(struct, typemap)
    if struct.name:
        typemap.structs[struct.name] = ret
    typemap.structs[struct] = ret
    return ret


def parse_struct_member(
    type: CType, field_name: str, typemap: TypeMap, *, allow_unsized: bool
) -> Tuple[int, int, DetailedStructMember]:
    type = resolve_typedefs(type, typemap)
    if isinstance(type, PtrDecl):
        return 4, 4, None
    if isinstance(type, ArrayDecl):
        if type.dim is None:
            raise DecompFailure(f"Array field {field_name} must have a size")
        dim = parse_constant_int(type.dim, typemap)
        size, align, substr = parse_struct_member(
            type.type, field_name, typemap, allow_unsized=False
        )
        return size * dim, align, Array(substr, type.type, size, dim)
    if isinstance(type, FuncDecl):
        assert allow_unsized, "Struct can not contain a function"
        return 0, 0, None
    inner_type = type.type
    if isinstance(inner_type, (ca.Struct, ca.Union)):
        substr = parse_struct(inner_type, typemap)
        return substr.size, substr.align, substr
    if isinstance(inner_type, ca.Enum):
        parse_enum(inner_type, typemap)
    # Otherwise it has to be of type Enum or IdentifierType
    size = primitive_size(inner_type)
    if size == 0 and not allow_unsized:
        raise DecompFailure(f"Field {field_name} cannot be void")
    return size, size, None


def do_parse_struct(struct: Union[ca.Struct, ca.Union], typemap: TypeMap) -> Struct:
    is_union = isinstance(struct, ca.Union)
    assert struct.decls is not None, "enforced by caller"
    assert struct.decls, "Empty structs are not valid C"

    fields: Dict[int, List[StructField]] = defaultdict(list)
    union_size = 0
    align = 1
    offset = 0
    bit_offset = 0
    has_bitfields = False

    def flush_bitfields() -> None:
        nonlocal offset, bit_offset
        if not is_union and bit_offset != 0:
            bit_offset = 0
            offset += 1

    for decl in struct.decls:
        if not isinstance(decl, ca.Decl):
            # Ignore pragmas
            continue

        type = decl.type
        if isinstance(type, (ca.Struct, ca.Union)):
            if type.decls is None:
                continue
            substruct = parse_struct(type, typemap)
            if type.name is not None:
                # Struct defined within another, which is silly but valid C.
                # parse_struct already makes sure it gets defined in the global
                # namespace, so no more to do here.
                pass
            else:
                # C extension: anonymous struct/union, whose members are flattened
                flush_bitfields()
                align = max(align, substruct.align)
                offset = (offset + substruct.align - 1) & -substruct.align
                for off, sfields in substruct.fields.items():
                    for field in sfields:
                        fields[offset + off].append(field)
                if is_union:
                    union_size = max(union_size, substruct.size)
                else:
                    offset += substruct.size
            continue

        if isinstance(type, ca.Enum):
            parse_enum(type, typemap)
            continue

        field_name = f"{struct.name}.{decl.name}"
        if decl.bitsize is not None:
            # A bitfield "type a : b;" has the following effects on struct layout:
            # - align the struct as if it contained a 'type' field.
            # - allocate the next 'b' bits of the struct, going from high bits to low
            #   within each byte.
            # - ensure that 'a' can be loaded using a single load of the size given by
            #   'type' (lw/lh/lb, unsigned counterparts). If it straddles a 'type'
            #   alignment boundary, skip all bits up to that boundary and then use the
            #   next 'b' bits from there instead.
            has_bitfields = True
            width = parse_constant_int(decl.bitsize, typemap)
            ssize, salign, substr = parse_struct_member(
                type, field_name, typemap, allow_unsized=False
            )
            align = max(align, salign)
            if width == 0:
                continue
            if ssize != salign or substr is not None:
                raise DecompFailure(f"Bitfield {field_name} is not of primitive type")
            if width > ssize * 8:
                raise DecompFailure(f"Width of bitfield {field_name} exceeds its type")
            if is_union:
                union_size = max(union_size, ssize)
            else:
                if offset // ssize != (offset + (bit_offset + width - 1) // 8) // ssize:
                    bit_offset = 0
                    offset = (offset + ssize) & -ssize
                bit_offset += width
                offset += bit_offset // 8
                bit_offset &= 7
            continue

        if decl.name is None:
            continue

        flush_bitfields()
        ssize, salign, substr = parse_struct_member(
            type, field_name, typemap, allow_unsized=False
        )
        align = max(align, salign)
        offset = (offset + salign - 1) & -salign
        fields[offset].append(
            StructField(
                type=type,
                size=ssize,
                name=decl.name,
            )
        )
        if is_union:
            union_size = max(union_size, ssize)
        else:
            offset += ssize

    flush_bitfields()

    # If there is a typedef for this struct, prefer using that name
    if struct in typemap.struct_typedefs:
        ctype = typemap.struct_typedefs[struct]
    elif struct.name and struct.name in typemap.struct_typedefs:
        ctype = typemap.struct_typedefs[struct.name]
    else:
        ctype = TypeDecl(declname=None, quals=[], type=struct, align=[])

    size = union_size if is_union else offset
    size = (size + align - 1) & -align
    return Struct(
        type=ctype, fields=fields, has_bitfields=has_bitfields, size=size, align=align
    )


def add_builtin_typedefs(source: str) -> str:
    """Add built-in typedefs to the source code (m2c emits those, so it makes
    sense to pre-define them to simplify hand-written C contexts)."""
    typedefs = {
        "u8": "unsigned char",
        "s8": "char",
        "u16": "unsigned short",
        "s16": "short",
        "u32": "unsigned int",
        "s32": "int",
        "u64": "unsigned long long",
        "s64": "long long",
        "f32": "float",
        "f64": "double",
    }
    line = " ".join(f"typedef {v} {k};" for k, v in typedefs.items())
    return line + "\n" + source


def strip_comments(text: str) -> str:
    # https://stackoverflow.com/a/241506
    def replacer(match: Match[str]) -> str:
        s = match.group(0)
        if s.startswith("/"):
            return " " + "\n" * s.count("\n")
        else:
            return s

    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE,
    )
    return re.sub(pattern, replacer, text)


def strip_macro_defs(text: str) -> str:
    """Strip macro definitions from C source. m2c does not run the preprocessor,
    for a bunch of reasons:

    - we don't know what include directories to use
    - it avoids a dependency on cpp, which is commonly unavailable on MacOS/Windows
    - web site security (#includes could read sensitive files)
    - performance

    Instead that responsibility is passed on to whoever generates the context file.

    But the context file may sometimes still contain macro definitions, if generated
    with the dual purpose of being used as a real include file that users expect to
    preserve macros.

    Under the optimistic assumption that the macros aren't necessary for parsing the
    context file itself, we strip all macro definitions before parsing."""
    pattern = re.compile(r"^[ \t]*#[ \t]*define[ \t](\\\n|.)*", flags=re.MULTILINE)
    return re.sub(pattern, lambda m: m.group(0).count("\n") * "\n", text)


def parse_c(
    source: str, initial_scope: CParserScope
) -> Tuple[ca.FileAST, CParserScope]:
    # This is a modified version of `CParser.parse()` which initializes `_scope_stack`,
    # which contains the only stateful part of the parser that needs to be preserved
    # when parsing multiple files.
    c_parser = CParser()
    c_parser.clex.filename = "<source>"
    c_parser.clex.reset_lineno()
    c_parser._scope_stack = [initial_scope.copy()]
    c_parser._last_yielded_token = None
    try:
        ast = c_parser.cparser.parse(input=source, lexer=c_parser.clex)
    except ParseError as e:
        msg = str(e)
        position, msg = msg.split(": ", 1)
        parts = position.split(":")
        if len(parts) >= 2:
            # Adjust the line number by 1 to correct for the added typedefs
            lineno = int(parts[1]) - 1
            posstr = f" at line {lineno}"
            if len(parts) >= 3:
                posstr += f", column {parts[2]}"
            try:
                line = source.split("\n")[lineno].rstrip()
                posstr += "\n\n" + line
            except IndexError:
                posstr += "(out of bounds?)"
        else:
            posstr = ""
        raise DecompFailure(f"Syntax error when parsing C context.\n{msg}{posstr}")
    return ast, c_parser._scope_stack[0].copy()


def build_typemap(source_paths: List[Path], use_cache: bool) -> TypeMap:
    # Wrapper to convert `source_paths` into a hashable type
    return _build_typemap(tuple(source_paths), use_cache)


@functools.lru_cache(maxsize=16)
def _build_typemap(source_paths: Tuple[Path, ...], use_cache: bool) -> TypeMap:
    typemap = TypeMap()

    for source_path in source_paths:
        source = source_path.read_text(encoding="utf-8-sig")

        # Compute a hash of the inputs to the TypeMap, which is used to check if the cached
        # version is still valid. The hashing process does not need to be cryptographically
        # secure, caching should only be enabled in trusted environments. (Unpickling files
        # can lead to arbitrary code execution.)
        hasher = hashlib.sha256()
        hasher.update(f"version={TypeMap.VERSION}\n".encode("utf-8"))
        hasher.update(f"parent={typemap.source_hash}\n".encode("utf-8"))
        hasher.update(source.encode("utf-8"))
        source_hash = hasher.hexdigest()

        cache_path = source_path.with_name(f"{source_path.name}.m2c")
        if use_cache and cache_path.exists():
            try:
                with cache_path.open("rb") as f:
                    cache = cast(TypeMap, pickle.load(f))
            except Exception as e:
                print(
                    f"Warning: Unable to read cache file {cache_path}, skipping ({e})"
                )
            else:
                if cache.source_hash == source_hash:
                    typemap = cache
                    continue

        source = add_builtin_typedefs(source)
        source = strip_comments(source)
        source = strip_macro_defs(source)

        ast, result_scope = parse_c(source, typemap.cparser_scope)
        typemap.cparser_scope = result_scope
        typemap.source_hash = source_hash

        for item in ast.ext:
            if isinstance(item, ca.Typedef):
                typemap.typedefs[item.name] = resolve_typedefs(item.type, typemap)
                if isinstance(item.type, TypeDecl) and isinstance(
                    item.type.type, (ca.Struct, ca.Union)
                ):
                    typedef = basic_type([item.name])
                    if item.type.type.name:
                        typemap.struct_typedefs[item.type.type.name] = typedef
                    typemap.struct_typedefs[item.type.type] = typedef
            if isinstance(item, ca.FuncDef):
                assert item.decl.name is not None, "cannot define anonymous function"
                fn = parse_function(type_of_var_decl(item.decl))
                assert fn is not None
                typemap.functions[item.decl.name] = fn
            if isinstance(item, ca.Decl) and isinstance(item.type, FuncDecl):
                assert item.name is not None, "cannot define anonymous function"
                fn = parse_function(item.type)
                assert fn is not None
                typemap.functions[item.name] = fn

        class Visitor(ca.NodeVisitor):
            def visit_Struct(self, struct: ca.Struct) -> None:
                if struct.decls is not None:
                    parse_struct(struct, typemap)

            def visit_Union(self, union: ca.Union) -> None:
                if union.decls is not None:
                    parse_struct(union, typemap)

            def visit_Decl(self, decl: ca.Decl) -> None:
                if decl.name is not None:
                    typemap.var_types[decl.name] = type_from_global_decl(decl)
                    if decl.init is not None:
                        typemap.vars_with_initializers.add(decl.name)
                if not isinstance(decl.type, FuncDecl):
                    self.visit(decl.type)

            def visit_Enum(self, enum: ca.Enum) -> None:
                parse_enum(enum, typemap)

            def visit_FuncDef(self, fn: ca.FuncDef) -> None:
                if fn.decl.name is not None:
                    typemap.var_types[fn.decl.name] = type_from_global_decl(fn.decl)

        Visitor().visit(ast)

        if use_cache:
            try:
                with cache_path.open("wb") as f2:
                    pickle.dump(typemap, f2)
            except Exception as e:
                print(
                    f"Warning: Unable to write cache file {cache_path}, skipping ({e})"
                )

    return typemap


def set_decl_name(decl: ca.Decl) -> None:
    name = decl.name
    type = type_of_var_decl(decl)
    while not isinstance(type, TypeDecl):
        type = type.type
    type.declname = name


def type_to_string(type: CType, name: str = "") -> str:
    if isinstance(type, TypeDecl) and isinstance(
        type.type, (ca.Struct, ca.Union, ca.Enum)
    ):
        if isinstance(type.type, ca.Struct):
            su = "struct"
        else:
            # (ternary to work around a mypy bug)
            su = "union" if isinstance(type.type, ca.Union) else "enum"
        if type.type.name:
            return f"{su} {type.type.name}"
        else:
            return f"anon {su}"
    decl = ca.Decl(name, [], [], [], [], copy.deepcopy(type), None, None)
    set_decl_name(decl)
    return to_c(decl)


def dump_typemap(typemap: TypeMap) -> None:
    print("Variables:")
    for var, type in typemap.var_types.items():
        print(f"{type_to_string(type, var)};")
    print()
    print("Functions:")
    for name, fn in typemap.functions.items():
        print(f"{type_to_string(fn.type, name)};")
    print()
    print("Structs:")
    for name_or_id, struct in typemap.structs.items():
        if not isinstance(name_or_id, str):
            continue
        print(f"{name_or_id}: size {hex(struct.size)}, align {struct.align}")
        for offset, fields in struct.fields.items():
            print(f"  {hex(offset)}:", end="")
            for field in fields:
                print(f" {field.name} ({type_to_string(field.type)})", end="")
            print()
    print()
    print("Enums:")
    for name, value in typemap.enum_values.items():
        print(f"{name}: {value}")
    print()
