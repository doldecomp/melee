#!/usr/bin/env python
#
# CodeWarrior demangler, supporting operators, templates (including literals), and arrays.
#
# This can be included as a library, or used as a CLI application directly:
#
#   $ ./demangle_cw.py 'check__3FooCFUlR3Bar'
#   Foo::check (long unsigned, Bar &) const
#
# CodeWarrior's symbol mangling and C++ ABI seems to be based on the Macintosh spec
# defined in this document, section 3.4.1.2 (page 18):
#
#   https://mirror.informatimago.com/next/developer.apple.com/tools/mpw-tools/compilers/docs/abi_spec.pdf
#
# It deviates from this spec in a few key ways:
#   - The <count> in <qualified_name> is an unterminated <int> (no '_' separator)
#   - Parameterized types use '<', ',' and '>' characters instead of the "__PT" prefix
#
# This file, like the rest of this repository, is licensed under the GPL v3. It is based
# on `demangler.cs` by arookas, which was provided under the 3-clause BSD License below:
#
#   https://gist.github.com/arookas/0c0cd842c9ca836d7a9ed06a655b1a22
#
# Copyright (c) 2017, arookas
# All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#
#   1. Redistributions of source code must retain the above copyright notice, this
#      list of conditions and the following disclaimer.
#
#   2. Redistributions in binary form must reproduce the above copyright notice,
#      this list of conditions and the following disclaimer in the documentation
#      and/or other materials provided with the distribution.
#
#   3. Neither the name of the copyright holder nor the names of its
#      contributors may be used to endorse or promote products derived from
#      this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from contextlib import contextmanager
from dataclasses import dataclass, field
from enum import Enum
from io import StringIO, TextIOBase
from typing import ClassVar, Iterator, List, Optional, Set

__all__ = [
    "CxxName",
    "CxxSymbol",
    "CxxTerm",
    "CxxType",
    "demangle",
    "parse",
]


# These substitutions are performed by the doldisasm.py decomp tool, and not by
# the CodeWarrior compiler directly. Undo them for convience, even though they
# aren't technically part of CW's mangling scheme.
DOLDISASM_SUBSTITUTIONS = [
    ("<", "$$0"),
    (">", "$$1"),
    ("@", "$$2"),
    ("\\", "$$3"),
    (",", "$$4"),
    ("-", "$$5"),
]


def read_exact(src: TextIOBase, size: int) -> str:
    """Read exactly `n` bytes from `src`, or raise a ValueError"""
    value = src.read(size)
    if len(value) != size:
        raise ValueError(f"Unable to read {size} bytes; got {value!r}")
    return value


@contextmanager
def peeking(src: TextIOBase) -> Iterator[None]:
    """Store the current offset in `src`, and restore it at the end of the context"""
    ptr = src.tell()
    try:
        yield
    finally:
        src.seek(ptr)


def peek(src: TextIOBase, n: int = 1) -> str:
    """Read up to `n` bytes from `src` without advancing the offset"""
    with peeking(src):
        return src.read(n)


@contextmanager
def as_stringio(src: str) -> Iterator[StringIO]:
    """Wrap `src` in a `StringIO`, and assert it was fully consumed at the end of the context"""
    buf = StringIO(src)
    yield buf
    leftover = buf.read()
    if leftover:
        raise ValueError(f"Unable to parse full input, leftover chars: {leftover!r}")


@dataclass
class CxxName:
    """
    Represent the name of a C++ symbol, class, or namespace.
    This may be parameterized with `template_params`.
    """

    NUMBER_CHARS: ClassVar[Set[str]] = set("-0123456789")

    name: str
    template_params: Optional[List["CxxType"]] = None

    @staticmethod
    def parse(src: TextIOBase) -> "CxxName":
        # Numbers: either a template literal, or a length prefix
        number_str = ""
        while peek(src) in CxxName.NUMBER_CHARS:
            number_str += read_exact(src, 1)
        if number_str == "":
            raise ValueError(
                "Unable to parse CxxName, input did not start with a number"
            )
        number = int(number_str)

        # Check if the number represents a template literal
        if peek(src) in (",", ">"):
            return CxxName(number_str)

        # Otherwise, it is the length of the name
        if number <= 0:
            raise ValueError("length must be positive")
        name = read_exact(src, number)

        # Simple case: plain identifier
        if "<" not in name:
            return CxxName(name)

        # Otherwise, parse the template parameters between the `<...>` brackets
        if name[-1] != ">":
            raise ValueError("unpaired '<'")
        base_name, sep, param_strs = name.partition("<")

        with as_stringio(param_strs) as buf:
            template_params = []
            while True:
                template_params.append(CxxType.parse(buf))
                sep = read_exact(buf, 1)
                if sep == ">":
                    break
                if sep == ",":
                    continue
                raise ValueError(f"Unexpected character while parsing CxxName: {sep}")

        return CxxName(name=base_name, template_params=template_params)

    def __str__(self) -> str:
        if self.template_params is None:
            return self.name
        return f"{self.name}<{', '.join(str(p) for p in self.template_params)}>"


@dataclass
class CxxTerm:
    """
    Represent a part of a C++ type, like a token.

    This mostly corresponds to a single letter in a mangled type, like 'v' or 'U',
    but it also can represent multicharacter components of a mangled type:

    - ARRAY: with dimension `array_dim`
    - FUNCTION: with `function_params` and `function_return` types
    - QUALIFIED name: with a list of paths in `qualified_name`
    - SYMBOL_REFERENCE: to the `symbol_reference` symbol
    """

    class Kind(Enum):
        CONST = "C"
        POINTER = "P"
        REFERENCE = "R"
        SIGNED = "S"
        UNSIGNED = "U"
        ELLIPSIS = "e"
        VOID = "v"
        BOOL = "b"
        CHAR = "c"
        SHORT = "s"
        INT = "i"
        LONG = "l"
        LONG_LONG = "x"
        WIDE_CHAR = "w"
        FLOAT = "f"
        DOUBLE = "d"
        LONG_DOUBLE = "r"

        ARRAY = "A"
        QUALIFIED = "Q"
        FUNCTION = "F"
        SYMBOL_REFERENCE = "&"

    NONTERMINATING_KINDS = {
        Kind.CONST,
        Kind.POINTER,
        Kind.REFERENCE,
        Kind.SIGNED,
        Kind.UNSIGNED,
        Kind.ARRAY,
    }

    OPS = {
        "__nw": " new",
        "__nwa": " new[]",
        "__dl": " delete",
        "__dla": " delete[]",
        "__pl": "+",
        "__mi": "-",
        "__ml": "*",
        "__dv": "/",
        "__md": "%",
        "__er": "^",
        "__adv": "/=",
        "__ad": "&",
        "__or": "|",
        "__co": "~",
        "__nt": "!",
        "__as": "=",
        "__lt": "<",
        "__gt": ">",
        "__apl": "+=",
        "__ami": "-=",
        "__amu": "*=",
        "__amd": "%=",
        "__aer": "^=",
        "__aad": "&=",
        "__aor": "|=",
        "__ls": "<<",
        "__rs": ">>",
        "__ars": ">>=",
        "__als": "<<=",
        "__eq": "==",
        "__ne": "!=",
        "__le": "<=",
        "__ge": ">=",
        "__aa": "&&",
        "__oo": "||",
        "__pp": "++",
        "__mm": "--",
        "__cl": "()",
        "__vc": "[]",
        "__rf": "->",
        "__cm": ",",
        "__rm": "->*",
    }

    kind: Kind

    # The following fields are only populated for the corresponding `kind`s
    array_dim: Optional[int] = None
    function_params: Optional[List["CxxType"]] = None
    function_return: Optional["CxxType"] = None
    qualified_name: Optional[List["CxxName"]] = None
    symbol_reference: Optional["CxxSymbol"] = None

    @staticmethod
    def parse(src: TextIOBase) -> "CxxTerm":
        if peek(src) in CxxName.NUMBER_CHARS:
            return CxxTerm(
                kind=CxxTerm.Kind.QUALIFIED, qualified_name=[CxxName.parse(src)]
            )

        kind = CxxTerm.Kind(read_exact(src, 1))
        if kind == CxxTerm.Kind.QUALIFIED:
            count = int(read_exact(src, 1))
            qualified_name = []
            for _ in range(count):
                qualified_name.append(CxxName.parse(src))
            return CxxTerm(kind=kind, qualified_name=qualified_name)

        if kind == CxxTerm.Kind.FUNCTION:
            function_params = []
            function_return = None
            while peek(src) not in ("", "_", ",", ">"):
                function_params.append(CxxType.parse(src))
            if peek(src, 1) == "_":
                read_exact(src, 1)
                function_return = CxxType.parse(src)
            return CxxTerm(
                kind=kind,
                function_params=function_params,
                function_return=function_return,
            )

        if kind == CxxTerm.Kind.ARRAY:
            array_dim = 0
            while True:
                c = read_exact(src, 1)
                if c == "_":
                    break
                array_dim = (array_dim * 10) + int(c)
            return CxxTerm(kind=kind, array_dim=array_dim)

        if kind == CxxTerm.Kind.SYMBOL_REFERENCE:
            return CxxTerm(
                kind=kind,
                symbol_reference=CxxSymbol.parse(src),
            )

        return CxxTerm(kind=kind)

    def __str__(self) -> str:
        if self.kind == CxxTerm.Kind.ARRAY:
            assert self.array_dim is not None
            return f"[{self.array_dim}]"

        if self.kind == CxxTerm.Kind.QUALIFIED:
            assert self.qualified_name is not None
            names = [str(q) for q in self.qualified_name]
            if names[-1] in CxxTerm.OPS:
                names[-1] = "operator" + CxxTerm.OPS[names[-1]]
            elif names[-1] == "__ct":
                assert len(names) >= 2
                names[-1] = names[-2]
            elif names[-1] == "__dt":
                assert len(names) >= 2
                names[-1] = f"~{names[-2]}"
            return "::".join(names)

        if self.kind == CxxTerm.Kind.FUNCTION:
            assert self.function_params is not None
            prefix = ""
            if self.function_return is not None:
                prefix = f"{self.function_return} (*) "
            args = ", ".join(str(p) for p in self.function_params)
            return f"{prefix}({args})"

        if self.kind == CxxTerm.Kind.SYMBOL_REFERENCE:
            assert self.symbol_reference is not None
            return f"&{self.symbol_reference}"

        if self.kind == CxxTerm.Kind.POINTER:
            return "*"
        if self.kind == CxxTerm.Kind.REFERENCE:
            return "&"
        if self.kind == CxxTerm.Kind.LONG_LONG:
            return "long long"
        if self.kind == CxxTerm.Kind.LONG_DOUBLE:
            return "long double"
        if self.kind == CxxTerm.Kind.WIDE_CHAR:
            return "wchar_t"
        if self.kind == CxxTerm.Kind.ELLIPSIS:
            return "..."
        return str(self.kind.name).lower()


@dataclass
class CxxType:
    """
    Represents a complete C++ type.

    The final element in `terms` is the primitive type, such as CHAR or
    FUNCTION. Working from the end, each previous term modifies the type.
    (This order matches the order in the mangled type)

    Example:
        `[CONST, POINTER, CHAR]` => "char * const"
        `[POINTER, CONST, CHAR]` => "char const *"
    """

    terms: List[CxxTerm] = field(default_factory=list)

    @staticmethod
    def parse(src: TextIOBase) -> "CxxType":
        terms = []
        while True:
            if peek(src) in (",", ">"):
                break
            term = CxxTerm.parse(src)
            terms.append(term)
            if term.kind not in CxxTerm.NONTERMINATING_KINDS:
                break
        return CxxType(terms=terms)

    def __str__(self) -> str:
        return " ".join(str(a) for a in self.terms[::-1]).strip()


@dataclass
class CxxSymbol:
    """Represents a C++ symbol & its type."""

    STATIC_FUNCTIONS = {"__sinit", "__sterm"}

    name: CxxTerm
    type: CxxType

    @staticmethod
    def parse(src: TextIOBase) -> "CxxSymbol":
        # Find the `base_name`, which is the prefix of `src` which usually represents
        # original, unmangled name of the symbol. It's typically separated from the
        # type information by the rightmost "__", but there are many edge cases.

        # The number of underscores that separate the `base_name` from the rest of the type info
        strip_underscores = 0
        # The nesting depth of "<...>" clauses in `base_name`
        template_depth = 0

        # By default, the `base_name` is the *entire* src string (with no trailing underscores)
        with peeking(src):
            base_name = src.read()
        with peeking(src):
            # `chars` is a buffer of the chars we've read from `src`
            chars = ""
            while True:
                # Try to read 1 character; if it's empty, return the `base_name` we've found so far
                c = src.read(1)
                if not c:
                    break

                # If we hit either "," or ">" but we are not parsing a template, that means we have
                # been called to parse a SYMBOL_REFERENCE inside a template, and we have hit a delimiter.
                # Otherwise, track "<" and ">" counts in `template_depth`.
                if c in (",", ">") and template_depth == 0:
                    if strip_underscores == 0:
                        base_name = chars
                    break
                elif c == "<":
                    template_depth += 1
                elif c == ">":
                    template_depth -= 1

                chars += c
                if chars in CxxSymbol.STATIC_FUNCTIONS:
                    # STATIC_FUNCTIONS are special prefixes which match exactly and only have 1 separating "_"
                    base_name = chars
                    strip_underscores = 1
                    break
                elif c == "_" and peek(src) == "_":
                    # If we're in the middle of reading a "__", then this may be where `base_name` ends.
                    # However, we only split here if the character after the "__" could be the start of
                    # of the mangled type info, or a class name.
                    #
                    # - "C" or "F" are common starts to mangled type info for functions (CONST, FUNCTION).
                    # - "Q" or a number indicates the start of a qualified name or a class name.
                    #
                    # This is a heuristic, and will fail to parse non-function unqualified symbols (such
                    # as "foo__Ul") and some functions with internal "__" characters (such as "bar__5__FooFv")
                    lookahead = peek(src, 2)
                    if len(lookahead) < 2 or lookahead[1] in "CFQ0123456789":
                        base_name = chars[:-1]
                        strip_underscores = 2

        # `base_name` is found, so remove it (and any separator underscores) from the input buffer
        read_exact(src, len(base_name) + strip_underscores)

        if base_name in CxxSymbol.STATIC_FUNCTIONS:
            # This is a special case. A function like `__sinit_Foo_cpp` is the static
            # constructor (ctor) for "Foo.cpp".
            # "Demangle" this into `void Foo_cpp::__sinit(void)`
            with as_stringio("Fv_v") as buf:
                type = CxxType.parse(buf)
            return CxxSymbol(
                name=CxxTerm(
                    CxxTerm.Kind.QUALIFIED,
                    qualified_name=[CxxName(src.read()), CxxName(base_name)],
                ),
                type=type,
            )

        # After the "__", the `base_name` is followed by the (optional) qualified class name, then the symbol's type.
        class_name: Optional[CxxType] = CxxType.parse(src)
        if peek(src) not in ("", ",", ">"):
            type = CxxType.parse(src)
        else:
            assert class_name is not None
            type = class_name
            class_name = None

        # Combine the `base_name` with the qualified class name to build a fully qualified symbol name.
        qualified_name: List["CxxName"] = []
        if class_name is not None:
            assert len(class_name.terms) == 1
            assert class_name.terms[0].kind == CxxTerm.Kind.QUALIFIED
            assert class_name.terms[0].qualified_name is not None
            qualified_name.extend(class_name.terms[0].qualified_name)

        with as_stringio(str(len(base_name)) + base_name) as buf:
            qualified_name.append(CxxName.parse(buf))

        name = CxxTerm(CxxTerm.Kind.QUALIFIED, qualified_name=qualified_name)
        return CxxSymbol(name=name, type=type)

    def __str__(self) -> str:
        return f"{self.name} {self.type}"


def parse(mangled: str) -> CxxSymbol:
    for old, new in DOLDISASM_SUBSTITUTIONS:
        mangled = mangled.replace(new, old)
    with as_stringio(mangled) as buf:
        return CxxSymbol.parse(buf)


def demangle(mangled: str) -> str:
    try:
        return str(parse(mangled))
    except ValueError:
        return mangled


def test() -> bool:
    TEST_CASES = [
        # Unmangled, but with underscores
        ("__foo_bar", "__foo_bar"),
        # Namespacing
        ("get__6FoobarFi", "Foobar::get (int)"),
        # Constructor / Destructor
        (
            "__ct__10FooBarFoosFP7ArgPtrsUsPCc",
            "FooBarFoos::FooBarFoos (ArgPtrs *, short unsigned, char const *)",
        ),
        ("__dt__10FooBarFoosFv", "FooBarFoos::~FooBarFoos (void)"),
        # Overloaded operators
        ("__dl__FPv", "operator delete (void *)"),
        ("__nw__FUl", "operator new (long unsigned)"),
        ("__eq__3FooCFRC3Foo", "Foo::operator== (Foo const &) const"),
        # Namespacing & templated arguments
        (
            "do__Q214GrandFooSystem8MiniFoosFUlPC3VecP3VecfUlUlPP8LateBazzUlUc",
            "GrandFooSystem::MiniFoos::do (long unsigned, Vec const *, Vec *, float, long unsigned, long unsigned, LateBazz * *, long unsigned, char unsigned)",
        ),
        (
            "spin__11ThingieBaseFRCQ29MyLibrary8FVec3$$0f$$1RCQ29MyLibrary8FVec3$$0f$$1RCQ29MyLibrary8FVec3$$0f$$1",
            "ThingieBase::spin (MyLibrary::FVec3<float> const &, MyLibrary::FVec3<float> const &, MyLibrary::FVec3<float> const &)",
        ),
        # Templated function names
        (
            "function<&alpha,&beta,&GAMMA>__FR5Class_i",
            "function<&alpha, &beta, &GAMMA> int (*) (Class &)",
        ),
        (
            "function<&m0__5Class,&mf0__5ClassFi>__FR5Class_i",
            "function<&m0 Class, &Class::mf0 (int)> int (*) (Class &)",
        ),
        # Static functions
        ("__sinit_Foo_cpp", "Foo_cpp::__sinit void (*) (void)"),
        ("__sterm_Foo_cpp", "Foo_cpp::__sterm void (*) (void)"),
        # Confusing function names (check that we split on the last valid "__")
        ("foo__3BarFv", "Bar::foo (void)"),
        ("foo__3BarFv__3BarFv", "Bar::foo__3BarFv (void)"),
        ("foo__Q23Bar3BarFv__3BarFv", "Bar::foo__Q23Bar3BarFv (void)"),
        (
            "copy__Q23std14__copy$$0Pv$$41$$40$$1FPPvPPvPPv",
            "std::__copy<void *, 1, 0>::copy (void * *, void * *, void * *)",
        ),
        ("__init__bar__9Bar$$03Foo$$1", "__init__bar Bar<Foo>"),
        ("bar__5__BarFv", "__Bar::bar (void)"),
        # These examples we fail to demangle correctly
        ("bar__5__FooFv", "bar__5__FooFv"),  # should be "__Foo::bar (void)"
        (
            "foo__Ul",
            "foo__Ul",
        ),  # should be "foo long unsigned" (or "long unsigned foo")
    ]
    all_pass = True
    for mangled, demangled in TEST_CASES:
        output = demangle(mangled)
        if output != demangled:
            print(f"Failed: {(mangled, output)}")
            all_pass = False

    if all_pass:
        print(f"All {len(TEST_CASES)} test cases passed")

    return all_pass


def main() -> None:
    import sys

    if len(sys.argv) != 2:
        # Print help
        print(f"usage: {sys.argv[0]} <mangled_name>")
        sys.exit(1)

    if sys.argv[1] == "--test":
        # Run internal unit tests
        sys.exit(0 if test() else 1)

    if sys.argv[1] == "-":
        # Batch mode: demangle each line in the input
        for line in sys.stdin:
            print(demangle(line.strip()))
        sys.exit(0)

    # Default: demangle the command-line argument
    print(demangle(sys.argv[1]))


if __name__ == "__main__":
    main()
