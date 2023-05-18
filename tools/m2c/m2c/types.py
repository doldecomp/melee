from dataclasses import dataclass, field
from typing import Dict, List, Optional, Set, Tuple, Union

import pycparser.c_ast as ca

from .c_types import (
    CType,
    Enum,
    StructUnion as CStructUnion,
    TypeMap,
    UndefinedStructError,
    is_unk_type,
    parse_constant_int,
    parse_function,
    parse_struct,
    primitive_size,
    resolve_typedefs,
    set_decl_name,
    to_c,
)
from .demangle_codewarrior import CxxName, CxxSymbol, CxxTerm, CxxType
from .error import DecompFailure, static_assert_unreachable
from .options import Formatter

# AccessPath represents a struct/array path, with ints for array access, and
# strs for struct fields. Ex: `["foo", 3, "bar"]` represents `.foo[3].bar`
AccessPath = List[Union[str, int]]


@dataclass
class TypePool:
    """
    Mutable shared state for Types, maintaining the set of available struct types.
    """

    unknown_field_prefix: str
    unk_inference: bool
    structs: Set["StructDeclaration"] = field(default_factory=set)
    structs_by_tag_name: Dict[str, "StructDeclaration"] = field(default_factory=dict)
    structs_by_ctype: Dict[CStructUnion, "StructDeclaration"] = field(
        default_factory=dict
    )
    unknown_decls: Dict[str, "Type"] = field(default_factory=dict)
    warnings: List[str] = field(default_factory=list)

    def get_struct_for_ctype(
        self,
        ctype: CStructUnion,
    ) -> Optional["StructDeclaration"]:
        """Return the StructDeclaration for a given ctype struct, if known"""
        struct = self.structs_by_ctype.get(ctype)
        if struct is not None:
            return struct
        if ctype.name is not None:
            return self.structs_by_tag_name.get(ctype.name)
        return None

    def get_or_create_struct_by_tag_name(
        self,
        tag_name: str,
        typemap: Optional[TypeMap],
        *,
        size: Optional[int] = None,
        with_typedef: bool = False,
    ) -> "StructDeclaration":
        struct = self.get_struct_by_tag_name(tag_name, typemap)
        if struct is not None:
            return struct
        struct = StructDeclaration.unknown(self, size, tag_name, align=4)
        if with_typedef:
            struct.typedef_name = tag_name
        return struct

    def get_struct_by_tag_name(
        self,
        tag_name: str,
        typemap: Optional[TypeMap],
    ) -> Optional["StructDeclaration"]:
        """
        Return the StructDeclaration with the given tag name, if available.
        If the struct is not already known and typemap is provided, try to find it there.
        """
        struct = self.structs_by_tag_name.get(tag_name)
        if struct is not None:
            return struct
        if typemap is not None:
            cstruct = typemap.structs.get(tag_name)
            if cstruct is not None:
                type = Type.ctype(cstruct.type, typemap, self)
                return type.get_struct_declaration()
        return None

    def add_struct(
        self,
        struct: "StructDeclaration",
        ctype_or_tag_name: Union[CStructUnion, str],
    ) -> None:
        """Add the struct declaration to the set of known structs for later access"""
        self.structs.add(struct)

        tag_name: Optional[str]
        if isinstance(ctype_or_tag_name, str):
            tag_name = ctype_or_tag_name
        else:
            ctype = ctype_or_tag_name
            tag_name = ctype.name
            self.structs_by_ctype[ctype] = struct

        if tag_name is not None:
            assert (
                tag_name not in self.structs_by_tag_name
            ), f"Duplicate tag: {tag_name}"
            self.structs_by_tag_name[tag_name] = struct

    def format_type_declarations(self, fmt: Formatter, stack_structs: bool) -> str:
        decls = []
        for struct in sorted(
            self.structs, key=lambda s: s.tag_name or s.typedef_name or ""
        ):
            # Only output stack structs if `stack_structs` is enabled
            if not stack_structs and struct.is_stack:
                continue
            # Include any struct with added fields, plus any stack structs
            if any(not f.known for f in struct.fields) or struct.is_stack:
                decls.append(struct.format(fmt) + "\n")
        return "\n".join(decls)

    def prune_structs(self) -> None:
        """Remove overlapping fields from all known structs"""
        for struct in self.structs:
            struct.prune_overlapping_fields()
            struct.rename_inferred_vtables()


@dataclass(eq=False)
class TypeData:
    K_INT = 1 << 0
    K_PTR = 1 << 1
    K_FLOAT = 1 << 2
    K_FN = 1 << 3
    K_VOID = 1 << 4
    K_ARRAY = 1 << 5
    K_STRUCT = 1 << 6
    K_INTPTR = K_INT | K_PTR
    K_ANYREG = K_INT | K_PTR | K_FLOAT
    K_ANY = K_INT | K_PTR | K_FLOAT | K_FN | K_VOID | K_ARRAY | K_STRUCT

    SIGNED = 1
    UNSIGNED = 2
    ANY_SIGN = 3

    kind: int = K_ANY
    likely_kind: int = K_ANY  # subset of kind
    size_bits: Optional[int] = None
    uf_parent: Optional["TypeData"] = None

    sign: int = ANY_SIGN  # K_INT
    ptr_to: Optional["Type"] = None  # K_PTR | K_ARRAY
    fn_sig: Optional["FunctionSignature"] = None  # K_FN
    array_dim: Optional[int] = None  # K_ARRAY
    struct: Optional["StructDeclaration"] = None  # K_STRUCT
    enum: Optional[Enum] = None  # K_INT
    new_field_within: Set["StructDeclaration"] = field(default_factory=set)

    def __post_init__(self) -> None:
        assert self.kind
        self.likely_kind &= self.kind

    def get_representative(self) -> "TypeData":
        # Follow `uf_parent` links until we hit the "root" TypeData
        equivalent_typedatas = set()
        root = self
        while root.uf_parent is not None:
            assert root not in equivalent_typedatas, "TypeData cycle detected"
            equivalent_typedatas.add(root)
            root = root.uf_parent

        # Set the `uf_parent` pointer on all visited TypeDatas
        for td in equivalent_typedatas:
            td.uf_parent = root

        return root


@dataclass(eq=False, repr=False)
class Type:
    """
    Type information for an expression, which may improve over time. The least
    specific type is any (initially the case for e.g. arguments); this might
    get refined into intish if the value gets used for e.g. an integer add
    operation, or into u32 if it participates in a logical right shift.
    Types cannot change except for improvements of this kind -- thus concrete
    types like u32 can never change into anything else, and e.g. ints can't
    become floats.
    """

    _data: TypeData

    def unify(self, other: "Type", *, seen: Optional[Set["TypeData"]] = None) -> bool:
        """
        Try to set this type equal to another. Returns true on success.
        Once set equal, the types will always be equal (we use a union-find
        structure to ensure this).
        The seen argument is used during recursion, to track which TypeData
        objects have been encountered so far.
        """

        x = self.data()
        y = other.data()
        if x is y:
            return True

        # If we hit a type that we have already seen, fail.
        # TODO: Is there a looser check that would allow more types to unify?
        if seen is None:
            seen = {x, y}
        elif x in seen or y in seen:
            return False
        else:
            seen = seen | {x, y}

        if (
            x.size_bits is not None
            and y.size_bits is not None
            and x.size_bits != y.size_bits
        ):
            return False

        kind = x.kind & y.kind
        likely_kind = x.likely_kind & y.likely_kind
        size_bits = x.size_bits if x.size_bits is not None else y.size_bits
        ptr_to = x.ptr_to if x.ptr_to is not None else y.ptr_to
        fn_sig = x.fn_sig if x.fn_sig is not None else y.fn_sig
        array_dim = x.array_dim if x.array_dim is not None else y.array_dim
        struct = x.struct if x.struct is not None else y.struct
        enum = x.enum if x.enum is not None else y.enum
        sign = x.sign & y.sign
        if size_bits not in (None, 32, 64):
            kind &= ~TypeData.K_FLOAT
        if size_bits not in (None, 32):
            kind &= ~TypeData.K_PTR
        if size_bits not in (None,):
            kind &= ~TypeData.K_FN
        if size_bits not in (None, 0):
            kind &= ~TypeData.K_VOID
        likely_kind &= kind
        if kind == 0 or sign == 0:
            return False
        if kind == TypeData.K_PTR:
            size_bits = 32
        if sign != TypeData.ANY_SIGN:
            assert kind & TypeData.K_INTPTR
        if enum is not None:
            assert kind == TypeData.K_INT
        if x.ptr_to is not None and y.ptr_to is not None:
            if not x.ptr_to.unify(y.ptr_to, seen=seen):
                return False
        if x.fn_sig is not None and y.fn_sig is not None:
            if not x.fn_sig.unify(y.fn_sig, seen=seen):
                return False
        if x.array_dim is not None and y.array_dim is not None:
            if x.array_dim != y.array_dim:
                return False
        if x.struct is not None and y.struct is not None:
            if not x.struct.unify(y.struct, seen=seen):
                return False
        if x.enum is not None and y.enum is not None:
            if x.enum != y.enum:
                return False
        if y.struct in x.new_field_within or x.struct in y.new_field_within:
            # Disallow recursive structs: if y is a struct that has a newly added
            # field of (yet unknown) type x, don't allow unifying x and y.
            return False
        x.kind = kind
        x.likely_kind = likely_kind
        x.size_bits = size_bits
        x.sign = sign
        x.ptr_to = ptr_to
        x.fn_sig = fn_sig
        x.array_dim = array_dim
        x.struct = struct
        x.enum = enum
        x.new_field_within |= y.new_field_within
        y.uf_parent = x
        return True

    def data(self) -> "TypeData":
        if self._data.uf_parent is None:
            return self._data
        self._data = self._data.get_representative()
        return self._data

    def is_float(self) -> bool:
        return self.data().kind == TypeData.K_FLOAT

    def is_likely_float(self) -> bool:
        data = self.data()
        return data.kind == TypeData.K_FLOAT or data.likely_kind == TypeData.K_FLOAT

    def is_pointer(self) -> bool:
        return self.data().kind == TypeData.K_PTR

    def is_pointer_or_array(self) -> bool:
        return self.data().kind in (TypeData.K_PTR, TypeData.K_ARRAY)

    def is_int(self) -> bool:
        return self.data().kind == TypeData.K_INT

    def is_reg(self) -> bool:
        return (self.data().kind & ~TypeData.K_ANYREG) == 0

    def is_function(self) -> bool:
        return self.data().kind == TypeData.K_FN

    def is_void(self) -> bool:
        return self.data().kind == TypeData.K_VOID

    def is_array(self) -> bool:
        return self.data().kind == TypeData.K_ARRAY

    def is_struct(self) -> bool:
        return self.data().kind == TypeData.K_STRUCT

    def is_signed(self) -> bool:
        return self.data().sign == TypeData.SIGNED

    def is_unsigned(self) -> bool:
        return self.data().sign == TypeData.UNSIGNED

    def get_enum_name(self, value: int) -> Optional[str]:
        data = self.data()
        if data.enum is None:
            return None
        return data.enum.names.get(value)

    def get_size_bits(self) -> Optional[int]:
        return self.data().size_bits

    def get_size_bytes(self) -> Optional[int]:
        size_bits = self.get_size_bits()
        return None if size_bits is None else size_bits // 8

    def get_parameter_size_align_bytes(self) -> Tuple[int, int]:
        """Return the size & alignment of self when used as a function argument"""
        data = self.data()
        if self.is_struct():
            assert data.struct is not None
            if data.struct.size is None:
                raise DecompFailure(f"Cannot use incomplete type {self} as parameter")
            return data.struct.size, data.struct.align
        size = (self.get_size_bits() or 32) // 8
        return size, size

    def get_pointer_target(self) -> Optional["Type"]:
        """If self is a pointer-to-a-Type, return the Type"""
        data = self.data()
        if self.is_pointer() and data.ptr_to is not None:
            return data.ptr_to
        return None

    def reference(self) -> "Type":
        """Return a pointer to self. If self is an array, decay the type to a pointer"""
        if self.is_array():
            data = self.data()
            assert data.ptr_to is not None
            return Type.ptr(data.ptr_to)
        return Type.ptr(self)

    def decay(self) -> "Type":
        """If self is an array, return a pointer to the element type. Otherwise, return self."""
        if self.is_array():
            data = self.data()
            assert data.ptr_to is not None
            return Type.ptr(data.ptr_to)
        return self

    def weaken_void_ptr(self) -> "Type":
        """If self is an explicit `void *`, return `Type.ptr()` without an target type."""
        target = self.get_pointer_target()
        if target is not None and target.is_void():
            return Type.ptr()
        return self

    def get_array(self) -> Tuple[Optional["Type"], Optional[int]]:
        """If self is an array, return a tuple of the inner Type & the array dimension"""
        if not self.is_array():
            return None, None
        data = self.data()
        assert data.ptr_to is not None
        return (data.ptr_to, data.array_dim)

    def get_function_pointer_signature(self) -> Optional["FunctionSignature"]:
        """If self is a function pointer, return the FunctionSignature"""
        data = self.data()
        if self.is_pointer() and data.ptr_to is not None:
            ptr_to = data.ptr_to.data()
            if ptr_to.kind == TypeData.K_FN:
                return ptr_to.fn_sig
        return None

    def get_struct_declaration(self) -> Optional["StructDeclaration"]:
        """If self is a struct, return the StructDeclaration"""
        if self.is_struct():
            data = self.data()
            assert data.struct is not None
            return data.struct
        return None

    GetFieldResult = Tuple[Optional[AccessPath], "Type", int]

    def get_field(
        self, offset: int, *, target_size: Optional[int], exact: bool = True
    ) -> GetFieldResult:
        """
        Locate the field in self at the appropriate offset, and optionally
        with an exact target size (both values in bytes).
        The target size can be used to disambiguate different fields in a union, or
        different levels inside nested structs.

        The return value is a tuple of `(field_path, field_type, remaining_offset)`.

        If `exact` is True, then `remaining_offset` is always 0. If no field is
        found, the result is `(None, Type.any(), 0)`.

        If `exact` is False, then `remaining_offset` may be nonzero. This means there
        was *not* a field at the exact offset provided; the returned field is at
        `(offset - remaining_offset)`.
        """
        NO_MATCHING_FIELD: Type.GetFieldResult = (None, Type.any(), 0)

        if offset < 0:
            return NO_MATCHING_FIELD

        if self.is_array():
            # Array types always have elements with known size
            data = self.data()
            assert data.ptr_to is not None
            size = data.ptr_to.get_size_bytes()
            assert size is not None

            index, remaining_offset = divmod(offset, size)
            if data.array_dim is not None and index >= data.array_dim:
                return NO_MATCHING_FIELD
            assert index >= 0 and remaining_offset >= 0

            # Assume this is an array access at the computed `index`.
            # Check if there is a field at the `remaining_offset` offset
            subpath, subtype, sub_remaining_offset = data.ptr_to.get_field(
                remaining_offset,
                target_size=target_size,
                exact=exact,
            )
            if subpath is not None:
                # Success: prepend `index` and return
                subpath.insert(0, index)
                return subpath, subtype, sub_remaining_offset
            return NO_MATCHING_FIELD

        if self.is_struct():
            data = self.data()
            assert data.struct is not None
            if data.struct.size is not None and offset >= data.struct.size:
                return NO_MATCHING_FIELD

            # Get a list of fields which contain the byte at offset. There may be more
            # than one if the StructDeclaration is for a union.
            possible_fields = data.struct.fields_containing_offset(offset)

            # We don't support bitfield access. If there isn't a field at the given offset,
            # it's better to bail early. We're likely recursively resolving a field, and
            # it's better for the caller to check for other fields (like in a union) than
            # to get a reference to a struct with bitfields.
            if not possible_fields and data.struct.has_bitfields:
                return NO_MATCHING_FIELD

            # One option is to return the whole struct itself. Do not do this if the struct
            # is marked as a stack struct, or if `target_size` is specified and does not match.
            possible_results: List[Type.GetFieldResult] = []
            if not data.struct.is_stack and (
                target_size is None or target_size == self.get_size_bytes()
            ):
                possible_results.append(([], self, offset))

            # Recursively check each of the `possible_fields` to find the best matches
            # for fields at the given offset.
            for field in possible_fields:
                inner_offset_bits = offset - field.offset
                subpath, subtype, sub_remaining_offset = field.type.get_field(
                    inner_offset_bits,
                    target_size=target_size,
                    exact=exact,
                )
                if subpath is None:
                    continue
                subpath.insert(0, field.name)
                possible_results.append((subpath, subtype, sub_remaining_offset))

                # Check if this subfield is an exact match. If it is, return it.
                if (
                    target_size is not None
                    and target_size == subtype.get_size_bytes()
                    and sub_remaining_offset == 0
                ):
                    return possible_results[-1]

            zero_offset_results = [r for r in possible_results if r[2] == 0]
            if zero_offset_results:
                # Try returning the first field which was at the correct offset,
                # but has the wrong size
                return zero_offset_results[0]
            elif exact:
                # Try to insert a new field into the struct at the given offset
                field_type = Type.any_field(new_within=data.struct)
                field_name = f"{data.struct.new_field_prefix}{offset:X}"
                new_field = data.struct.try_add_field(
                    field_type, offset, field_name, size=target_size
                )
                if new_field is not None:
                    return [field_name], field_type, 0
            elif possible_results:
                return possible_results[0]

        if (target_size is None or target_size == self.get_size_bytes()) and (
            offset == 0
        ):
            # The whole type itself is a match
            return [], self, offset

        return NO_MATCHING_FIELD

    def get_deref_field(
        self,
        offset: int,
        *,
        target_size: Optional[int],
        exact: bool = True,
    ) -> GetFieldResult:
        """
        Similar to `.get_field()`, but treat self as a pointer and find the field in the
        pointer's target.  The return value has the same semantics as `.get_field()`.

        If successful, the first item in the resulting `field_path` will be `0`.
        This mirrors how `foo[0].bar` and `foo->bar` are equivalent in C.
        """
        NO_MATCHING_FIELD: Type.GetFieldResult = (None, Type.any(), 0)

        target = self.get_pointer_target()
        if target is None:
            return NO_MATCHING_FIELD

        # Assume the pointer is to a single object, and not an array.
        field_path, field_type, remaining_offset = target.get_field(
            offset, target_size=target_size, exact=exact
        )
        if field_path is not None:
            field_path.insert(0, 0)
        return field_path, field_type, remaining_offset

    def get_initializer_fields(
        self,
    ) -> Optional[List[Union[int, "Type"]]]:
        """
        If self is a struct or array (i.e. initialized with `{...}` syntax), then
        return a list of fields suitable for creating an initializer.
        Return None if an initializer cannot be made (e.g. a struct with bitfields)

        Padding is represented by an int in the list, otherwise the list fields
        denote the field's Type.
        """
        data = self.data()
        if self.is_array():
            assert data.ptr_to is not None
            if data.array_dim is None:
                return None

            return [data.ptr_to] * data.array_dim

        if self.is_struct():
            assert data.struct is not None
            if data.struct.has_bitfields:
                # TODO: Support bitfields
                return None

            output: List[Union[int, Type]] = []
            position = 0

            def add_padding(upto: int) -> None:
                nonlocal position
                nonlocal output
                assert upto >= position
                if upto > position:
                    output.append(upto - position)

            for field in data.struct.fields:
                # Overlapping fields aren't supported
                if field.offset < position:
                    return None

                add_padding(field.offset)
                field_size = field.type.get_size_bytes()
                # If any field has unknown size, we can't make an initializer
                if field_size is None:
                    return None

                output.append(field.type)
                position = field.offset + field_size

                # Unions only have an initializer for the first field
                if data.struct.is_union:
                    break

            if data.struct.size is not None and position > data.struct.size:
                # This struct has a field that goes outside of the bounds of the struct
                return None

            add_padding(data.struct.min_size())
            return output

        return None

    def to_decl(self, name: str, fmt: Formatter) -> str:
        decl = ca.Decl(
            name=name,
            type=self._to_ctype(set(), fmt),
            quals=[],
            align=[],
            storage=[],
            funcspec=[],
            init=None,
            bitsize=None,
        )
        set_decl_name(decl)
        ret = to_c(decl)

        if fmt.coding_style.pointer_style_left:
            # Keep going until the result is unmodified
            while True:
                replaced = (
                    ret.replace(" *", "* ").replace("* )", "*)").replace("* ,", "*,")
                )
                if replaced == ret:
                    break
                ret = replaced

        return ret

    def _to_ctype(self, seen: Set["TypeData"], fmt: Formatter) -> CType:
        def simple_ctype(typename: str) -> ca.TypeDecl:
            return ca.TypeDecl(
                type=ca.IdentifierType(names=[typename]),
                declname=None,
                quals=[],
                align=[],
            )

        unk_symbol = "M2C_UNK" if fmt.valid_syntax else "?"

        data = self.data()
        if data in seen:
            return simple_ctype(unk_symbol)
        seen.add(data)
        size_bits = data.size_bits or 32
        sign = "s" if data.sign & TypeData.SIGNED else "u"

        if data.enum is not None and data.enum.tag is not None:
            assert data.kind == TypeData.K_INT
            return ca.TypeDecl(
                type=ca.Enum(name=data.enum.tag, values=None),
                declname=None,
                quals=[],
                align=[],
            )

        if (data.kind & TypeData.K_ANYREG) == TypeData.K_ANYREG and (
            data.likely_kind & (TypeData.K_INT | TypeData.K_FLOAT)
        ) not in (TypeData.K_INT, TypeData.K_FLOAT):
            if data.size_bits is not None:
                return simple_ctype(f"{unk_symbol}{size_bits}")
            return simple_ctype(unk_symbol)

        if (
            data.kind == TypeData.K_FLOAT
            or (data.likely_kind & (TypeData.K_FLOAT | TypeData.K_INT))
            == TypeData.K_FLOAT
        ):
            return simple_ctype(f"f{size_bits}")

        if data.kind == TypeData.K_PTR:
            target_ctype: CType
            if data.ptr_to is None:
                target_ctype = simple_ctype("void")
            else:
                target_ctype = data.ptr_to._to_ctype(seen.copy(), fmt)

            # Strip parameter names from function pointers
            if isinstance(target_ctype, ca.FuncDecl) and target_ctype.args:
                for arg in target_ctype.args.params:
                    if isinstance(arg, ca.Decl):
                        arg.name = None
                        set_decl_name(arg)

            return ca.PtrDecl(type=target_ctype, quals=[])

        if data.kind == TypeData.K_FN:
            assert data.fn_sig is not None
            return_ctype = data.fn_sig.return_type._to_ctype(seen.copy(), fmt)

            params: List[Union[ca.Decl, ca.ID, ca.Typename, ca.EllipsisParam]] = []
            for param in data.fn_sig.params:
                decl = ca.Decl(
                    name=param.name,
                    type=param.type._to_ctype(seen.copy(), fmt),
                    quals=[],
                    align=[],
                    storage=[],
                    funcspec=[],
                    init=None,
                    bitsize=None,
                )
                set_decl_name(decl)
                params.append(decl)

            if data.fn_sig.is_variadic:
                params.append(ca.EllipsisParam())

            return ca.FuncDecl(
                type=return_ctype,
                args=ca.ParamList(params),
            )

        if data.kind == TypeData.K_VOID:
            return simple_ctype("void")

        if data.kind == TypeData.K_ARRAY:
            assert data.ptr_to is not None
            dim: Optional[ca.Constant] = None
            if data.array_dim is not None:
                dim = ca.Constant(value=fmt.format_int(data.array_dim), type="")
            return ca.ArrayDecl(
                type=data.ptr_to._to_ctype(seen.copy(), fmt),
                dim=dim,
                dim_quals=[],
            )

        if data.kind == TypeData.K_STRUCT:
            assert data.struct is not None
            if data.struct.typedef_name:
                return simple_ctype(data.struct.typedef_name)
            # If there's no typedef or tag name, then label it as `_anonymous`
            name = data.struct.tag_name or "_anonymous"
            type: Union[ca.Union, ca.Struct] = (
                ca.Union(name=name, decls=None)
                if data.struct.is_union
                else ca.Struct(name=name, decls=None)
            )
            return ca.TypeDecl(
                declname=name,
                type=type,
                quals=[],
                align=[],
            )

        return simple_ctype(f"{sign}{size_bits}")

    def format(self, fmt: Formatter) -> str:
        return self.to_decl("", fmt)

    def __str__(self) -> str:
        return self.format(Formatter(debug=True))

    def __repr__(self) -> str:
        data = self.data()
        signstr = ("+" if data.sign & TypeData.SIGNED else "") + (
            "-" if data.sign & TypeData.UNSIGNED else ""
        )
        kindstr = (
            ("I" if data.kind & TypeData.K_INT else "")
            + ("P" if data.kind & TypeData.K_PTR else "")
            + ("F" if data.kind & TypeData.K_FLOAT else "")
            + ("N" if data.kind & TypeData.K_FN else "")
            + ("V" if data.kind & TypeData.K_VOID else "")
            + ("A" if data.kind & TypeData.K_ARRAY else "")
            + ("S" if data.kind & TypeData.K_STRUCT else "")
        )
        sizestr = str(data.size_bits) if data.size_bits is not None else "?"
        return f"Type({signstr + kindstr + sizestr})"

    @staticmethod
    def any() -> "Type":
        return Type(TypeData())

    @staticmethod
    def any_reg() -> "Type":
        return Type(TypeData(kind=TypeData.K_ANYREG))

    @staticmethod
    def any_field(*, new_within: "Optional[StructDeclaration]" = None) -> "Type":
        return Type(
            TypeData(
                kind=TypeData.K_ANY & ~TypeData.K_VOID,
                new_field_within={new_within} if new_within else set(),
            )
        )

    @staticmethod
    def intish() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT))

    @staticmethod
    def uintish() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, sign=TypeData.UNSIGNED))

    @staticmethod
    def sintish() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, sign=TypeData.SIGNED))

    @staticmethod
    def intptr() -> "Type":
        return Type(TypeData(kind=TypeData.K_INTPTR))

    @staticmethod
    def uintptr() -> "Type":
        return Type(TypeData(kind=TypeData.K_INTPTR, sign=TypeData.UNSIGNED))

    @staticmethod
    def sintptr() -> "Type":
        return Type(TypeData(kind=TypeData.K_INTPTR, sign=TypeData.SIGNED))

    @staticmethod
    def ptr(type: Optional["Type"] = None) -> "Type":
        return Type(TypeData(kind=TypeData.K_PTR, size_bits=32, ptr_to=type))

    @staticmethod
    def function(fn_sig: Optional["FunctionSignature"] = None) -> "Type":
        if fn_sig is None:
            fn_sig = FunctionSignature()
        return Type(TypeData(kind=TypeData.K_FN, fn_sig=fn_sig))

    @staticmethod
    def f32() -> "Type":
        return Type(TypeData(kind=TypeData.K_FLOAT, size_bits=32))

    @staticmethod
    def floatish() -> "Type":
        return Type(TypeData(kind=TypeData.K_FLOAT))

    @staticmethod
    def f64() -> "Type":
        return Type(TypeData(kind=TypeData.K_FLOAT, size_bits=64))

    @staticmethod
    def f128() -> "Type":
        return Type(TypeData(kind=TypeData.K_FLOAT, size_bits=128))

    @staticmethod
    def s8() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=8, sign=TypeData.SIGNED))

    @staticmethod
    def u8() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=8, sign=TypeData.UNSIGNED))

    @staticmethod
    def s16() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=16, sign=TypeData.SIGNED))

    @staticmethod
    def u16() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=16, sign=TypeData.UNSIGNED))

    @staticmethod
    def s32() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=32, sign=TypeData.SIGNED))

    @staticmethod
    def u32() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=32, sign=TypeData.UNSIGNED))

    @staticmethod
    def s64() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=64, sign=TypeData.SIGNED))

    @staticmethod
    def u64() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=64, sign=TypeData.UNSIGNED))

    @staticmethod
    def int64() -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=64))

    @staticmethod
    def int_of_size(size_bits: int) -> "Type":
        return Type(TypeData(kind=TypeData.K_INT, size_bits=size_bits))

    @staticmethod
    def reg32(*, likely_float: bool) -> "Type":
        likely = TypeData.K_FLOAT if likely_float else TypeData.K_INTPTR
        return Type(TypeData(kind=TypeData.K_ANYREG, likely_kind=likely, size_bits=32))

    @staticmethod
    def reg64(*, likely_float: bool) -> "Type":
        kind = TypeData.K_FLOAT | TypeData.K_INT
        likely = TypeData.K_FLOAT if likely_float else TypeData.K_INT
        return Type(TypeData(kind=kind, likely_kind=likely, size_bits=64))

    @staticmethod
    def bool() -> "Type":
        return Type.intish()

    @staticmethod
    def void() -> "Type":
        return Type(TypeData(kind=TypeData.K_VOID, size_bits=0))

    @staticmethod
    def array(type: "Type", dim: Optional[int]) -> "Type":
        # Array elements must have a known size
        el_size = type.get_size_bits()
        assert el_size is not None

        size_bits = None if dim is None else (el_size * dim)
        return Type(
            TypeData(
                kind=TypeData.K_ARRAY, size_bits=size_bits, ptr_to=type, array_dim=dim
            )
        )

    @staticmethod
    def struct(st: "StructDeclaration") -> "Type":
        size_bits = st.size * 8 if st.size is not None else None
        return Type(TypeData(kind=TypeData.K_STRUCT, size_bits=size_bits, struct=st))

    @staticmethod
    def ctype(ctype: CType, typemap: TypeMap, typepool: TypePool) -> "Type":
        real_ctype = resolve_typedefs(ctype, typemap)
        if typepool.unk_inference and is_unk_type(ctype, typemap):
            type = Type.any()

            if isinstance(real_ctype, ca.TypeDecl) and isinstance(
                real_ctype.type, ca.IdentifierType
            ):
                size_bits = primitive_size(real_ctype.type) * 8
                if size_bits < 32:
                    # This preserves the size of UNK_TYPE1, UNK_TYPE2
                    type = Type.int_of_size(size_bits)

            if isinstance(ctype, ca.TypeDecl) and ctype.declname:
                if ctype.declname in typepool.unknown_decls:
                    return typepool.unknown_decls[ctype.declname]
                typepool.unknown_decls[ctype.declname] = type

            return type

        if isinstance(real_ctype, ca.ArrayDecl):
            dim = None
            try:
                if real_ctype.dim is not None:
                    dim = parse_constant_int(real_ctype.dim, typemap)
            except DecompFailure:
                pass
            inner_type = Type.ctype(real_ctype.type, typemap, typepool)
            return Type.array(inner_type, dim)
        if isinstance(real_ctype, ca.PtrDecl):
            return Type.ptr(Type.ctype(real_ctype.type, typemap, typepool))
        if isinstance(real_ctype, ca.FuncDecl):
            fn = parse_function(real_ctype)
            assert fn is not None
            fn_sig = FunctionSignature(
                return_type=Type.void(),
                is_variadic=fn.is_variadic,
            )
            if fn.ret_type is not None:
                fn_sig.return_type = Type.ctype(fn.ret_type, typemap, typepool)
            if fn.params is not None:
                fn_sig.params = [
                    FunctionParam(
                        name=param.name or "",
                        type=Type.ctype(param.type, typemap, typepool),
                    )
                    for param in fn.params
                ]
                fn_sig.params_known = True
            return Type.function(fn_sig)
        if isinstance(real_ctype, ca.TypeDecl):
            if isinstance(real_ctype.type, (ca.Struct, ca.Union)):
                return Type.struct(
                    StructDeclaration.from_ctype(real_ctype.type, typemap, typepool)
                )
            if isinstance(real_ctype.type, ca.Enum):
                enum = None
                if real_ctype.type.name is not None:
                    enum = typemap.enums.get(real_ctype.type.name)
                if enum is None:
                    enum = typemap.enums.get(real_ctype.type)
                return Type(
                    TypeData(
                        kind=TypeData.K_INT,
                        size_bits=32,
                        sign=TypeData.SIGNED,
                        enum=enum,
                    )
                )

            names = real_ctype.type.names
            if "double" in names:
                return Type.f64()
            if "float" in names:
                return Type.f32()
            if "void" in names:
                return Type.void()
            size_bits = 8 * primitive_size(real_ctype.type)
            assert size_bits > 0
            sign = TypeData.UNSIGNED if "unsigned" in names else TypeData.SIGNED
            return Type(TypeData(kind=TypeData.K_INT, size_bits=size_bits, sign=sign))
        static_assert_unreachable(real_ctype)

    @staticmethod
    def demangled_symbol(
        typemap: TypeMap, typepool: TypePool, sym: CxxSymbol
    ) -> "Type":
        return Type.demangled_type(
            typemap, typepool, sym_type=sym.type, sym_name=sym.name
        )

    @staticmethod
    def demangled_type(
        typemap: TypeMap,
        typepool: TypePool,
        sym_type: CxxType,
        sym_name: Optional[CxxTerm] = None,
    ) -> "Type":
        def type_for_class(qualified_name: List[CxxName]) -> Type:
            # TODO: Using "::" here matches the C++ qualified identifiers, but is not valid C
            # Maybe this seperator should depend on the --valid-syntax option?
            class_name = "::".join(str(n) for n in qualified_name)
            class_struct = typepool.get_or_create_struct_by_tag_name(
                class_name, typemap, size=None, with_typedef=True
            )
            return Type.struct(class_struct)

        # TODO: This function may need to depend on the ABI or compiler to generate the types
        # of class member functions. It may need to be moved out of types.py, or some of this
        # logic could be moved into FunctionSignature?
        final_name = None
        if sym_name is not None:
            assert sym_name.kind == CxxTerm.Kind.QUALIFIED
            assert sym_name.qualified_name is not None
            assert len(sym_name.qualified_name) >= 1
            final_name = str(sym_name.qualified_name[-1]).split("@")[-1]

        # vtable types are created in translate.py by parsing the labels in the asm
        if final_name == "__vt":
            return Type.any()

        # RTTI data from MWCC is an 8-byte struct
        if final_name == "__RTTI":
            return Type.struct(
                typepool.get_or_create_struct_by_tag_name("RTTI", typemap, size=8)
            )

        type = Type.any()
        for term in sym_type.terms[::-1]:
            if term.kind == CxxTerm.Kind.CONST:
                pass
            elif term.kind in (CxxTerm.Kind.POINTER, CxxTerm.Kind.REFERENCE):
                type = Type.ptr(type)
            elif term.kind == CxxTerm.Kind.BOOL:
                type = Type.bool()
            elif term.kind == CxxTerm.Kind.CHAR:
                type = Type.int_of_size(8)
            elif term.kind in (CxxTerm.Kind.SHORT, CxxTerm.Kind.WIDE_CHAR):
                type = Type.int_of_size(16)
            elif term.kind in (CxxTerm.Kind.INT, CxxTerm.Kind.LONG):
                type = Type.int_of_size(32)
            elif term.kind == CxxTerm.Kind.LONG_LONG:
                type = Type.int_of_size(64)
            elif term.kind == CxxTerm.Kind.FLOAT:
                type = Type.f32()
            elif term.kind == CxxTerm.Kind.DOUBLE:
                type = Type.f64()
            elif term.kind == CxxTerm.Kind.LONG_DOUBLE:
                type = Type.f128()
            elif term.kind == CxxTerm.Kind.SIGNED:
                type.unify(Type(TypeData(kind=TypeData.K_INT, sign=TypeData.SIGNED)))
            elif term.kind == CxxTerm.Kind.UNSIGNED:
                type.unify(Type(TypeData(kind=TypeData.K_INT, sign=TypeData.UNSIGNED)))
            elif term.kind == CxxTerm.Kind.ARRAY:
                assert term.array_dim is not None, "array CxxTerms must have array_dim"
                type = Type.array(type, term.array_dim)
            elif term.kind == CxxTerm.Kind.FUNCTION:
                assert term.function_params is not None
                params = []
                if (
                    sym_name is not None
                    and sym_name.qualified_name is not None
                    and len(sym_name.qualified_name) > 1
                    and final_name not in CxxSymbol.STATIC_FUNCTIONS
                ):
                    class_type = type_for_class(sym_name.qualified_name[:-1])
                    # NB: This assumes `this` is passed as the first arg, which is true
                    # for most thiscall methods on PPC. However, this is incorrect for
                    # static member functions, functions returning structs, and other ABIs.
                    params.append(FunctionParam(type=Type.ptr(class_type), name="this"))
                if final_name == "__dt":
                    params.append(FunctionParam(type=Type.s16(), name="destroyFlag"))
                # TODO: Classes with virtual bases may also have an implicit `int vbasearg` arg
                is_variadic = False
                for i, param_type in enumerate(term.function_params):
                    name = f"arg{i}"
                    if param_type.terms[0].kind == CxxTerm.Kind.VOID:
                        assert len(term.function_params) == 1
                    elif param_type.terms[0].kind == CxxTerm.Kind.ELLIPSIS:
                        assert i == len(term.function_params) - 1
                        is_variadic = True
                    else:
                        params.append(
                            FunctionParam(
                                type=Type.demangled_type(typemap, typepool, param_type),
                                name=name,
                            )
                        )
                return_type = Type.any()
                if term.function_return is not None:
                    return_type = Type.demangled_type(
                        typemap, typepool, term.function_return
                    )
                elif final_name in ("__ct", "__dt"):
                    return_type = Type.ptr()
                type = Type.function(
                    FunctionSignature(
                        params=params,
                        params_known=True,
                        is_variadic=is_variadic,
                        return_type=return_type,
                    )
                )
            elif term.kind == CxxTerm.Kind.QUALIFIED:
                assert term.qualified_name is not None
                type = type_for_class(term.qualified_name)
            elif term.kind == CxxTerm.Kind.VOID:
                type = Type.void()
            elif term.kind == CxxTerm.Kind.ELLIPSIS:
                # This should be handled by the FUNCTION iterator above
                assert False, term.kind
            else:
                assert False, term.kind
        return type


@dataclass(eq=False)
class FunctionParam:
    type: Type = field(default_factory=Type.any)
    name: str = ""


@dataclass(eq=False)
class FunctionSignature:
    return_type: Type = field(default_factory=Type.any)
    params: List[FunctionParam] = field(default_factory=list)
    params_known: bool = False
    is_variadic: bool = False

    def unify(self, other: "FunctionSignature", *, seen: Set[TypeData]) -> bool:
        if self.params_known and other.params_known:
            if self.is_variadic != other.is_variadic:
                return False
            if len(self.params) != len(other.params):
                return False

        # Try to unify *all* ret/param types, without returning early
        # TODO: If not all the types unify, roll back any changes made
        can_unify = self.return_type.unify(other.return_type, seen=seen)
        for x, y in zip(self.params, other.params):
            can_unify &= x.type.unify(y.type, seen=seen)
        if not can_unify:
            return False

        # If one side has fewer params (and params_known is not True), then
        # extend its param list to match the other side
        if not self.params_known:
            self.is_variadic |= other.is_variadic
            self.params_known |= other.params_known
            while len(other.params) > len(self.params):
                self.params.append(other.params[len(self.params)])
        if not other.params_known:
            other.is_variadic |= self.is_variadic
            other.params_known |= self.params_known
            while len(self.params) > len(other.params):
                other.params.append(self.params[len(other.params)])

        # If any parameter names are missing, try to fill them in
        for x, y in zip(self.params, other.params):
            if not x.name and y.name:
                x.name = y.name
            elif not y.name and x.name:
                y.name = x.name

        return True

    def unify_with_args(self, concrete: "FunctionSignature") -> bool:
        """
        Unify a function's signature with a list of argument types.
        This is more flexible than unify() and is intended to check
        the function's type at a specific callsite.

        This function is not symmetric; `self` represents the prototype
        (e.g. with variadic args), whereas `concrete` represents the
        set of arguments at the callsite.
        """
        if len(self.params) > len(concrete.params):
            return False
        if not self.is_variadic and len(self.params) != len(concrete.params):
            return False
        can_unify = True
        for x, y in zip(self.params, concrete.params):
            can_unify &= x.type.unify(y.type)
        return can_unify


@dataclass(eq=False)
class StructDeclaration:
    """Representation of a C struct or union"""

    @dataclass(eq=False)
    class StructField:
        type: Type
        offset: int
        name: str
        known: bool

    size: Optional[int]
    align: int
    new_field_prefix: str
    tag_name: Optional[str] = None
    typedef_name: Optional[str] = None
    fields: List[StructField] = field(default_factory=list)  # sorted by `.offset`
    has_bitfields: bool = False
    is_union: bool = False
    is_stack: bool = False

    def min_size(self) -> int:
        if self.size is not None:
            return self.size
        return max(
            (
                field.offset + (field.type.get_size_bytes() or 1)
                for field in self.fields
            ),
            default=0,
        )

    def unify(
        self,
        other: "StructDeclaration",
        *,
        seen: Optional[Set["TypeData"]] = None,
    ) -> bool:
        # NB: Currently, the only structs that exist are defined from ctypes in the typemap,
        # so for now we can use reference equality to check if two structs are compatible.
        return self is other

    def fields_containing_offset(self, offset: int) -> List[StructField]:
        """Return the list of StructFields which contain the given offset (in bytes)"""
        fields = []
        for field in self.fields:
            # We assume fields are sorted by `offset`, ascending
            if field.offset > offset:
                break
            # If the field size is None, treat it as 1-byte wide so that it will only
            # be included if it is an exact match.
            field_size = field.type.get_size_bytes() or 1
            if field.offset + field_size <= offset:
                continue
            fields.append(field)
        return fields

    def try_add_field(
        self, type: Type, offset: int, name: str, size: Optional[int]
    ) -> Optional[StructField]:
        """
        Try to add a field into the struct, and return it if successful.
        Return None if the offset is outside of the bounds of the struct, or if the
        added field would overlap with a field marked as "known".
        """
        # TODO: Support unions
        if self.is_union:
            return None

        # Check that the offset is within the struct bounds
        if self.size is not None and not (0 <= offset < self.size):
            return None

        # Do not allow the new field to overlap with any other field
        # If there is a size we don't know, assume it is only 1 byte wide
        size = size or 1
        for field in self.fields:
            field_size = field.type.get_size_bytes() or 1

            # Two intervals overlap if one contains the start of the other
            if offset <= field.offset < offset + size:
                return None
            if field.offset <= offset < field.offset + field_size:
                return None

        field = self.StructField(type=type, offset=offset, name=name, known=False)
        self.fields.append(field)
        self.fields.sort(key=lambda f: f.offset)
        return field

    def prune_overlapping_fields(self) -> None:
        """Remove overlapping fields with `known=False` from the struct"""

        # TODO: Support unions
        if self.is_union:
            return None

        # Sort by offset, with bigger fields at the same offset first
        self.fields.sort(key=lambda f: (f.offset, -(f.type.get_size_bytes() or 0)))

        # Use a fake field to mark the end of the struct if it has a known size
        if self.size is not None:
            end_pseudofield = [
                StructDeclaration.StructField(
                    offset=self.size,
                    type=Type.void(),
                    known=True,
                    name="",
                )
            ]
        else:
            end_pseudofield = []

        fields_to_remove: Set[StructDeclaration.StructField] = set()
        for i, field in enumerate(self.fields):
            # Skip fields provided by the context or marked for removal
            if field.known or field in fields_to_remove:
                continue

            # If the size of a field (still) isn't known, assume it is 1 byte
            field_size = field.type.get_size_bytes() or 1

            conflicting_fields: List[StructDeclaration.StructField] = []
            for f2 in self.fields[i + 1 :] + end_pseudofield:
                assert f2.offset >= field.offset
                # If `f2` is after the end of `field`, we're done
                if f2.offset >= field.offset + field_size:
                    break
                if f2 in fields_to_remove:
                    continue

                # Now, we know `field` and `f2` overlap. Check if `f2` is a subfield of `field`.
                offset = f2.offset - field.offset
                sub_path, sub_type, _ = field.type.get_field(
                    offset, target_size=f2.type.get_size_bytes()
                )
                if sub_path is not None and sub_type.unify(f2.type):
                    # Remove `f2` so that accesses to `f2.offset` go through `field` instead.
                    # Defer adding `f2` to `fields_to_remove` until we're done processing `field`.
                    conflicting_fields.append(f2)
                elif not f2.known and f2.type.is_int() and field.type.is_int():
                    # Ignore overlapping inferred ints. This can happen when a load & cast is
                    # implemented with a load of a smaller size. It would be better to detect
                    # those cases directly; until then, the code is easier to manually fix
                    # if we leave the overlapping fields.
                    pass
                else:
                    # `field` is too big: this usually means that we incorrectly inferred
                    # it to be a (large) struct. Reset its type to something smaller.
                    # Although this is unlikely to produce the correct type for this field,
                    # it helps minimize the damage done to the rest of the struct.
                    if conflicting_fields:
                        offset = conflicting_fields[0].offset - field.offset
                        conflicting_fields = []

                    if offset == 0:
                        # `field` directly overlaps with another, smaller, field, so remove it
                        conflicting_fields = [field]
                    if offset >= 4:
                        field.type = Type.any_reg()
                    else:
                        field.type = Type.int_of_size(offset * 8)

                    break
            fields_to_remove |= set(conflicting_fields)
        self.fields = [f for f in self.fields if f not in fields_to_remove]

    def rename_inferred_vtables(self) -> None:
        """Rename inferred fields that are pointers to vtables"""
        sep = "_" if self.new_field_prefix.endswith("_") else ""
        for field in self.fields:
            if field.known or not field.name.startswith(self.new_field_prefix):
                continue
            type_ptr = field.type.get_pointer_target()
            if type_ptr is None:
                continue
            struct = type_ptr.get_struct_declaration()
            if struct is None or struct.tag_name is None:
                continue
            if struct.tag_name.startswith("__vt__"):
                name = field.name.replace(self.new_field_prefix, f"vtable{sep}", 1)
                if not any(f.name == name for f in self.fields):
                    field.name = name

    def format(self, fmt: Formatter) -> str:
        """
        Return the C representation of the struct/union.
        NB: We don't use ca.Struct here so that we can add comments for each field.

        TODO: This does not correctly handle nested anonymous structs/unions, though it
        is possible for the user to reconstruct these by hand from the "offset" comments.
        """
        keyword = "union" if self.is_union else "struct"
        decl = f"{keyword} {self.tag_name}" if self.tag_name else f"{keyword}"
        head = f"typedef {decl} {{" if self.typedef_name else f"{decl} {{"
        tail = f"}} {self.typedef_name};" if self.typedef_name else "};"

        # If there are no fields or padding, return everything on one line
        if self.size == 0 and not self.fields:
            return fmt.with_comments(head + tail, ["size 0x0"])

        lines = []
        lines.append(fmt.indent(head))
        with fmt.indented():
            offset_str_digits = len(fmt.format_hex(self.min_size()))

            def offset_comment(offset: int) -> str:
                # Indicate the offset of the field (in hex), written to the *left* of the field
                nonlocal offset_str_digits
                return f"/* 0x{fmt.format_hex(offset).zfill(offset_str_digits)} */"

            position = 0
            prev_field: Optional[StructDeclaration.StructField] = None

            def pad_to(offset: int, is_final: bool) -> None:
                nonlocal position
                if position < offset:
                    # Fill the gap with a char array, e.g. `char pad12[0x34];`
                    underscore = "_" if fmt.coding_style.unknown_underscore else ""
                    name = f"pad{underscore}{fmt.format_hex(position)}"
                    padding_size = offset - position

                    comments = []
                    # Hint if the previous field may be an array, unless this is the final field in a stack struct
                    if prev_field is not None and not (is_final and self.is_stack):
                        last_size = prev_field.type.get_size_bytes()
                        if last_size and padding_size > last_size:
                            array_dim_str = fmt.format_int(
                                padding_size // last_size + 1
                            )
                            comments.append(
                                f"maybe part of {prev_field.name}[{array_dim_str}]?"
                            )

                    lines.append(
                        fmt.with_comments(
                            f"{offset_comment(position)} char {name}[{fmt.format_int(padding_size)}];",
                            comments,
                        )
                    )
                    position = offset

            for field in self.fields:
                pad_to(field.offset, is_final=False)
                field_decl = f"{offset_comment(field.offset)} {field.type.to_decl(field.name, fmt)};"

                comments = []
                # Detect if adjacent fields incorrectly overlap (the C decl will not be accurate)
                if not self.is_union and position > field.offset:
                    comments.append("overlap")
                # Detect if a union field doesn't start at 0 (the C decl will not be accurate)
                if self.is_union and field.offset != 0:
                    comments.append("offset")
                # Mark fields that weren't in the input TypeMap (i.e. weren't in the context)
                if not field.known:
                    comments.append("inferred")
                lines.append(fmt.with_comments(field_decl, comments))
                # Hack to recompute field.type's size
                s = field.type.get_struct_declaration()
                if s is not None:
                    field.type.unify(Type.struct(s))
                position = max(
                    position, field.offset + (field.type.get_size_bytes() or 0)
                )
                prev_field = field
            pad_to(self.min_size(), is_final=True)
        compare = ">=" if self.size is None else "="
        lines.append(
            fmt.with_comments(tail, [f"size {compare} 0x{fmt.format_hex(position)}"])
        )
        return "\n".join(lines)

    @staticmethod
    def unknown(
        typepool: TypePool, size: Optional[int], tag_name: str, align: int = 1
    ) -> "StructDeclaration":
        """Return an StructDeclaration without any known fields"""
        decl = StructDeclaration(
            size=size,
            align=align,
            tag_name=tag_name,
            new_field_prefix=typepool.unknown_field_prefix,
        )
        typepool.add_struct(decl, tag_name)
        return decl

    @staticmethod
    def from_ctype(
        ctype: CStructUnion, typemap: TypeMap, typepool: TypePool
    ) -> "StructDeclaration":
        """
        Return StructDeclaration for a given ctype struct or union, constructing it
        and registering it in the typepool if it does not already exist.
        """
        existing_struct = typepool.get_struct_for_ctype(ctype)
        if existing_struct:
            return existing_struct

        typedef_name: Optional[str] = None
        if ctype in typemap.struct_typedefs:
            typedef = typemap.struct_typedefs[ctype]
            assert isinstance(typedef.type, ca.IdentifierType)
            typedef_name = typedef.type.names[0]
        elif ctype.name and ctype.name in typemap.struct_typedefs:
            typedef = typemap.struct_typedefs[ctype.name]
            assert isinstance(typedef.type, ca.IdentifierType)
            typedef_name = typedef.type.names[0]

        try:
            struct = parse_struct(ctype, typemap)
            struct_fields = struct.fields
            struct_has_bitfields = struct.has_bitfields
            struct_size = struct.size
            struct_align = struct.align
        except UndefinedStructError:
            struct_fields = {}
            struct_has_bitfields = False
            struct_size = 0
            struct_align = 1
            typepool.warnings.append(
                f"Warning: struct {typedef_name or ctype.name} is not defined (only forward-declared)"
            )

        assert (
            struct_size % struct_align == 0
        ), "struct size must be a multiple of its alignment"

        decl = StructDeclaration(
            size=struct_size,
            align=struct_align,
            tag_name=ctype.name,
            typedef_name=typedef_name,
            fields=[],
            has_bitfields=struct_has_bitfields,
            is_union=isinstance(ctype, ca.Union),
            new_field_prefix=typepool.unknown_field_prefix,
        )
        # Register the struct in the typepool now, before parsing the fields,
        # in case there are any self-referential fields in this struct.
        typepool.add_struct(decl, ctype)

        for offset, fields in sorted(struct_fields.items()):
            for field in fields:
                if typepool.unk_inference and is_unk_type(field.type, typemap):
                    continue
                field_type = Type.ctype(field.type, typemap, typepool)
                assert field.size == field_type.get_size_bytes(), (
                    field.size,
                    field_type.get_size_bytes(),
                    field.name,
                    field_type,
                )
                decl.fields.append(
                    StructDeclaration.StructField(
                        type=field_type,
                        offset=offset,
                        name=field.name,
                        known=True,
                    )
                )
        assert decl.fields == sorted(decl.fields, key=lambda f: f.offset)

        return decl
