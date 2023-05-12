import contextlib
from dataclasses import dataclass
import enum
from pathlib import Path
from typing import Dict, Iterator, List, Optional, Union


class ChoicesEnum(enum.Enum):
    """A helper class that is easier to use with argparse"""

    def __str__(self) -> str:
        return str(self.value)


@dataclass(frozen=True)
class CodingStyle:
    class CommentStyle(ChoicesEnum):
        MULTILINE = "multiline"
        ONELINE = "oneline"
        NONE = "none"

    newline_after_function: bool
    newline_after_if: bool
    newline_before_else: bool
    switch_indent_level: int
    pointer_style_left: bool
    unknown_underscore: bool
    hex_case: bool
    comment_style: CommentStyle
    comment_column: int


@dataclass
class Target:
    class ArchEnum(ChoicesEnum):
        MIPS = "mips"
        PPC = "ppc"

    class EndianEnum(ChoicesEnum):
        LITTLE = "little"
        BIG = "big"

    class CompilerEnum(ChoicesEnum):
        IDO = "ido"
        GCC = "gcc"
        MWCC = "mwcc"

    class LanguageEnum(ChoicesEnum):
        C = "c"
        CXX = "c++"

    arch: ArchEnum
    endian: EndianEnum
    compiler: CompilerEnum
    language: LanguageEnum

    def is_big_endian(self) -> bool:
        return self.endian == Target.EndianEnum.BIG

    @staticmethod
    def parse(name: str) -> "Target":
        """
        Parse an `arch-compiler-language` triple.
        If `-language` is missing, use the default for the compiler.
        If `-compiler` is missing, use the default for the arch.
        (This makes `mips` an alias for `mips-ido-c`, etc.)
        """
        endian = Target.EndianEnum.BIG
        terms = name.split("-")
        try:
            arch_name = terms[0]
            if arch_name.endswith("el"):
                arch_name = arch_name[:-2]
                endian = Target.EndianEnum.LITTLE
            arch = Target.ArchEnum(arch_name)
            if len(terms) >= 2:
                compiler = Target.CompilerEnum(terms[1])
            elif arch == Target.ArchEnum.PPC:
                compiler = Target.CompilerEnum.MWCC
            else:
                compiler = Target.CompilerEnum.IDO

            if len(terms) >= 3:
                language = Target.LanguageEnum(terms[2])
            elif compiler == Target.CompilerEnum.MWCC:
                language = Target.LanguageEnum.CXX
            else:
                language = Target.LanguageEnum.C
        except ValueError as e:
            raise ValueError(f"Unable to parse Target '{name}' ({e})")

        return Target(
            arch=arch,
            endian=endian,
            compiler=compiler,
            language=language,
        )


@dataclass
class Options:
    class GlobalDeclsEnum(ChoicesEnum):
        ALL = "all"
        USED = "used"
        NONE = "none"

    class VisualizeTypeEnum(ChoicesEnum):
        ASM = "asm"
        C = "c"

    filenames: List[str]
    function_indexes_or_names: List[Union[int, str]]
    debug: bool
    void: bool
    ifs: bool
    switch_detection: bool
    andor_detection: bool
    skip_casts: bool
    zfill_constants: bool
    force_decimal: bool
    heuristic_strings: bool
    reg_vars: List[str]
    goto_patterns: List[str]
    stop_on_error: bool
    print_assembly: bool
    visualize_flowgraph: Optional[VisualizeTypeEnum]
    c_contexts: List[Path]
    use_cache: bool
    dump_typemap: bool
    pdb_translate: bool
    preproc_defines: Dict[str, Optional[int]]  # None = explicitly unset
    coding_style: CodingStyle
    sanitize_tracebacks: bool
    valid_syntax: bool
    global_decls: GlobalDeclsEnum
    target: Target
    print_stack_structs: bool
    unk_inference: bool
    passes: int
    incbin_dirs: List[Path]
    deterministic_vars: bool
    disable_gc: bool

    def formatter(self) -> "Formatter":
        return Formatter(
            self.coding_style,
            skip_casts=self.skip_casts,
            zfill_constants=self.zfill_constants,
            force_decimal=self.force_decimal,
            valid_syntax=self.valid_syntax,
        )


DEFAULT_CODING_STYLE: CodingStyle = CodingStyle(
    newline_after_function=False,
    newline_after_if=False,
    newline_before_else=False,
    switch_indent_level=1,
    pointer_style_left=False,
    unknown_underscore=False,
    hex_case=False,
    comment_style=CodingStyle.CommentStyle.MULTILINE,
    comment_column=52,
)


@dataclass
class Formatter:
    coding_style: CodingStyle = DEFAULT_CODING_STYLE
    indent_step: str = " " * 4
    skip_casts: bool = False
    extra_indent: int = 0
    debug: bool = False
    valid_syntax: bool = False
    line_length: int = 80
    zfill_constants: bool = False
    force_decimal: bool = False

    def indent(self, line: str, indent: int = 0) -> str:
        return self.indent_step * max(indent + self.extra_indent, 0) + line

    @contextlib.contextmanager
    def indented(self, amt: int = 1) -> Iterator[None]:
        try:
            self.extra_indent += amt
            yield
        finally:
            self.extra_indent -= amt

    def format_array(self, elements: List[str]) -> str:
        # If there are no newlines & the output would be short, put it all on one line.
        # Here, "line length" is just used as a rough guideline: we aren't accounting
        # for the LHS of the assignment or any indentation.
        if not any("\n" in el or len(el) > self.line_length for el in elements):
            output = f"{{ {', '.join(elements)} }}"
            if len(output) < self.line_length:
                return output

        # Otherwise, put each element on its own line (and include a trailing comma)
        output = "{\n"
        for el in elements:
            # Add 1 indentation level to the string
            el = el.replace("\n", "\n" + self.indent_step)
            output += self.indent(f"{el},\n", 1)
        output += "}"

        return output

    def with_comments(self, line: str, comments: List[str], *, indent: int = 0) -> str:
        """Indent `line` and append a list of `comments` joined with ';'"""
        base = self.indent(line, indent=indent)
        # If `comments` is empty; fall back to `Formatter.indent()` behavior
        if (
            not comments
            or self.coding_style.comment_style == CodingStyle.CommentStyle.NONE
        ):
            return base

        # Add padding to the style's `comment_column`, only if `line` is non-empty
        padding = ""
        if line:
            padding = max(1, self.coding_style.comment_column - len(base)) * " "
        if self.coding_style.comment_style == CodingStyle.CommentStyle.ONELINE:
            comment = f"// {'; '.join(comments)}"
        else:
            comment = f"/* {'; '.join(comments)} */"
        return f"{base}{padding}{comment}"

    def format_hex(self, val: int) -> str:
        return format(val, "x").upper()

    def format_int(self, val: int, size_bits: Optional[int] = None) -> str:
        if abs(val) < 10 or self.force_decimal:
            return str(val)

        if self.zfill_constants and size_bits is not None:
            hex_digits = f"{abs(val):0{size_bits // 4}X}"
        else:
            hex_digits = f"{abs(val):X}"

        # Always pad 7-digit hex constants to 8 digits. (These are very common and easily confused.)
        if len(hex_digits) == 7:
            hex_digits = f"0{hex_digits}"

        if val < 0:
            return f"-0x{hex_digits}"
        else:
            return f"0x{hex_digits}"
