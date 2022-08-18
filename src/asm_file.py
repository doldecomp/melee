import csv
from dataclasses import dataclass, field
import re
import struct
import typing
from pathlib import Path
from typing import Callable, Dict, List, Match, Optional, Set, Tuple, TypeVar, Union

from .error import DecompFailure
from .options import Options
from .asm_instruction import RegFormatter
from .instruction import (
    ArchAsm,
    Instruction,
    InstructionMeta,
    parse_instruction,
)


@dataclass(frozen=True)
class Label:
    name: str

    def __str__(self) -> str:
        return f"  .{self.name}:"


@dataclass
class Function:
    name: str
    body: List[Union[Instruction, Label]] = field(default_factory=list)
    reg_formatter: RegFormatter = field(default_factory=RegFormatter)

    def new_label(self, name: str) -> None:
        label = Label(name)
        if self.body and self.body[-1] == label:
            # Skip repeated labels
            return
        self.body.append(label)

    def new_instruction(self, instruction: Instruction) -> None:
        self.body.append(instruction)

    def bodyless_copy(self) -> "Function":
        return Function(
            name=self.name,
            reg_formatter=self.reg_formatter,
        )

    def __str__(self) -> str:
        body = "\n".join(str(item) for item in self.body)
        return f"glabel {self.name}\n{body}"


@dataclass
class AsmDataEntry:
    data: List[Union[str, bytes]] = field(default_factory=list)
    is_string: bool = False
    is_readonly: bool = False
    is_bss: bool = False
    is_jtbl: bool = False

    def size_range_bytes(self) -> Tuple[int, int]:
        """Return the range of possible sizes, if padding were stripped."""
        # TODO: The data address could be used to only strip padding
        # that ends on 16-byte boundaries and is at the end of a section
        max_size = 0
        for x in self.data:
            if isinstance(x, str):
                max_size += 4
            else:
                max_size += len(x)

        padding_size = 0
        if self.data and isinstance(self.data[-1], bytes):
            assert len(self.data) == 1 or isinstance(self.data[-2], str)
            for b in self.data[-1][::-1]:
                if b != 0:
                    break
                padding_size += 1
        padding_size = min(padding_size, 15)
        assert padding_size <= max_size

        # Assume the size is at least 1 byte, unless `max_size == 0`
        if max_size == padding_size and max_size != 0:
            return 1, max_size
        return max_size - padding_size, max_size


@dataclass
class AsmData:
    values: Dict[str, AsmDataEntry] = field(default_factory=dict)
    mentioned_labels: Set[str] = field(default_factory=set)

    def merge_into(self, other: "AsmData") -> None:
        for (sym, value) in self.values.items():
            other.values[sym] = value
        for label in self.mentioned_labels:
            other.mentioned_labels.add(label)


@dataclass
class AsmFile:
    filename: str
    functions: List[Function] = field(default_factory=list)
    asm_data: AsmData = field(default_factory=AsmData)
    current_function: Optional[Function] = field(default=None, repr=False)
    current_data: AsmDataEntry = field(default_factory=AsmDataEntry)

    def new_function(self, name: str) -> None:
        self.current_function = Function(name=name)
        self.functions.append(self.current_function)

    def new_instruction(self, instruction: Instruction) -> None:
        if self.current_function is None:
            # Allow (and ignore) nop instructions in the .text
            # section before any function labels
            if instruction.mnemonic == "nop":
                return
            else:
                raise DecompFailure(
                    f"unsupported non-nop instruction outside of function ({instruction})"
                )
        self.current_function.new_instruction(instruction)

    def new_label(self, label_name: str) -> None:
        assert self.current_function is not None
        self.current_function.new_label(label_name)

    def new_data_label(self, symbol_name: str, is_readonly: bool, is_bss: bool) -> None:
        self.current_data = AsmDataEntry(is_readonly=is_readonly, is_bss=is_bss)
        self.asm_data.values[symbol_name] = self.current_data

    def new_data_sym(self, sym: str) -> None:
        self.current_data.data.append(sym)
        self.asm_data.mentioned_labels.add(sym.lstrip("."))

    def new_data_bytes(self, data: bytes, *, is_string: bool = False) -> None:
        if not self.current_data.data and is_string:
            self.current_data.is_string = True
        if self.current_data.data and isinstance(self.current_data.data[-1], bytes):
            self.current_data.data[-1] += data
        else:
            self.current_data.data.append(data)

    def __str__(self) -> str:
        functions_str = "\n\n".join(str(function) for function in self.functions)
        return f"# {self.filename}\n{functions_str}"


def split_arg_list(args: str) -> List[str]:
    """Split a string of comma-separated arguments, handling quotes"""
    reader = csv.reader(
        [args],
        delimiter=",",
        doublequote=False,
        escapechar="\\",
        quotechar='"',
        skipinitialspace=True,
    )
    return [a.strip() for a in next(reader)]


def parse_ascii_directive(line: str, z: bool) -> bytes:
    # This is wrong wrt encodings; the assembler really operates on bytes and
    # not chars. But for our purposes it should be good enough.
    in_quote = False
    num_parts = 0
    ret: List[bytes] = []
    i = 0
    digits = "0123456789"
    while i < len(line):
        c = line[i]
        i += 1
        if not in_quote:
            if c == '"':
                in_quote = True
                num_parts += 1
        else:
            if c == '"':
                in_quote = False
                if z:
                    ret.append(b"\0")
                continue
            if c != "\\":
                ret.append(c.encode("utf-8"))
                continue
            if i == len(line):
                raise DecompFailure(
                    "backslash at end of .ascii line not supported: " + line
                )
            c = line[i]
            i += 1
            char_escapes = {
                "b": b"\b",
                "f": b"\f",
                "n": b"\n",
                "r": b"\r",
                "t": b"\t",
                "v": b"\v",
            }
            if c in char_escapes:
                ret.append(char_escapes[c])
            elif c == "x":
                # hex literal, consume any number of hex chars, possibly none
                value = 0
                while i < len(line) and line[i] in digits + "abcdefABCDEF":
                    value = value * 16 + int(line[i], 16)
                    i += 1
                ret.append(bytes([value & 0xFF]))
            elif c in digits:
                # Octal literal, consume up to two more digits.
                # Using just the digits 0-7 would be more sane, but this matches GNU as.
                it = 0
                value = int(c)
                while i < len(line) and line[i] in digits and it < 2:
                    value = value * 8 + int(line[i])
                    i += 1
                    it += 1
                ret.append(bytes([value & 0xFF]))
            else:
                ret.append(c.encode("utf-8"))

    if in_quote:
        raise DecompFailure("unterminated string literal: " + line)
    if num_parts == 0:
        raise DecompFailure(".ascii with no string: " + line)
    return b"".join(ret)


def add_warning(warnings: List[str], new: str) -> None:
    if new not in warnings:
        warnings.append(new)


def parse_incbin(
    args: List[str], options: Options, warnings: List[str]
) -> Optional[bytes]:
    try:
        filename = args[0]
        offset = int(args[1], 0)
        size = int(args[2], 0)
    except ValueError:
        raise DecompFailure(f"Could not parse asm_data .incbin directive: {args}")

    if not options.incbin_dirs:
        add_warning(
            warnings,
            f"Skipping .incbin directive for {filename}, pass --incbin-dir to set a search directory",
        )
        return None

    for incbin_dir in options.incbin_dirs:
        full_path = incbin_dir / filename
        try:
            with full_path.open("rb") as f:
                f.seek(offset)
                data = f.read(size)
        except OSError:
            continue
        except MemoryError:
            data = b""

        if len(data) != size:
            add_warning(
                warnings,
                f"Unable to read {size} bytes from {full_path} at {offset:#x} (got {len(data)} bytes)",
            )
            return None
        return data

    add_warning(
        warnings,
        f"Unable to find {filename} in any of {len(options.incbin_dirs)} search paths",
    )
    return None


def parse_file(f: typing.TextIO, arch: ArchAsm, options: Options) -> AsmFile:
    filename = Path(f.name).name
    asm_file: AsmFile = AsmFile(filename)
    ifdef_level: int = 0
    ifdef_levels: List[int] = []
    curr_section = ".text"
    warnings: List[str] = []
    defines: Dict[str, Optional[int]] = {
        # NULL is a non-standard but common asm macro that expands to 0
        "NULL": 0,
        **options.preproc_defines,
    }

    # https://stackoverflow.com/a/241506
    def re_comment_replacer(match: Match[str]) -> str:
        s = match.group(0)
        if s[0] in "/#; \t":
            return " "
        else:
            return s

    re_comment_or_string = re.compile(r'[#;].*|/\*.*?\*/|"(?:\\.|[^\\"])*"')
    re_whitespace_or_string = re.compile(r'\s+|"(?:\\.|[^\\"])*"')
    re_local_glabel = re.compile("L(_U_)?[0-9A-F]{8}")
    re_local_label = re.compile("loc_|locret_|def_|lbl_")
    re_label = re.compile(r'(?:([a-zA-Z0-9_.$]+)|"([a-zA-Z0-9_.$<>@,-]+)"):')

    T = TypeVar("T")

    def try_parse(parser: Callable[[], T]) -> T:
        try:
            return parser()
        except ValueError:
            raise DecompFailure(
                f"Could not parse asm_data {directive} in {curr_section}: {line}"
            )

    def parse_int(w: str) -> int:
        var_value = defines.get(w)
        if var_value is not None:
            return var_value
        return int(w, 0)

    for lineno, line in enumerate(f, 1):
        # Check for goto markers before stripping comments
        emit_goto = any(pattern in line for pattern in options.goto_patterns)

        # Strip comments and whitespace (but not within strings)
        line = re.sub(re_comment_or_string, re_comment_replacer, line)
        line = re.sub(re_whitespace_or_string, re_comment_replacer, line)
        line = line.strip()

        def process_label(label: str, *, glabel: bool) -> None:
            if curr_section == ".rodata":
                asm_file.new_data_label(label, is_readonly=True, is_bss=False)
            elif curr_section == ".data":
                asm_file.new_data_label(label, is_readonly=False, is_bss=False)
            elif curr_section == ".bss":
                asm_file.new_data_label(label, is_readonly=False, is_bss=True)
            elif curr_section == ".text":
                re_local = re_local_glabel if glabel else re_local_label
                if label.startswith("."):
                    if asm_file.current_function is None:
                        raise DecompFailure(f"Label {label} is not within a function!")
                    asm_file.new_label(label.lstrip("."))
                elif re_local.match(label) and asm_file.current_function is not None:
                    # Don't treat labels as new functions if they follow a
                    # specific naming pattern. This is used for jump table
                    # targets in both IDA and old n64split output.
                    # We skip this behavior for the very first label in the
                    # file though, to avoid crashes due to unidentified
                    # functions. (Should possibly be generalized to cover any
                    # glabel that has a branch that goes across?)
                    asm_file.new_label(label)
                else:
                    asm_file.new_function(label)

        # Check for labels
        while True:
            g = re_label.match(line)
            if not g:
                break

            label = g.group(1) or g.group(2)
            if ifdef_level == 0:
                process_label(label, glabel=False)

            line = line[len(g.group(0)) :].strip()

        if not line:
            continue

        if "=" in line:
            key, value = line.split("=", 1)
            key = key.strip()
            if " " not in key:
                line = f".set {key}, {value}"

        directive = line.split()[0]
        if directive.startswith("."):
            # Assembler directive.
            if directive == ".ifdef" or directive == ".ifndef":
                macro_name = line.split()[1]
                if macro_name not in defines:
                    defines[macro_name] = None
                    add_warning(
                        warnings,
                        f"Note: assuming {macro_name} is unset for .ifdef, "
                        f"pass -D{macro_name}/-U{macro_name} to set/unset explicitly.",
                    )
                level = 1 if defines[macro_name] is not None else 0
                if directive == ".ifdef":
                    level = 1 - level
                ifdef_level += level
                ifdef_levels.append(level)
            elif directive.startswith(".if"):
                macro_name = line.split()[1]
                if macro_name == "0":
                    level = 1
                elif macro_name == "1":
                    level = 0
                else:
                    level = 0
                    add_warning(warnings, f"Note: ignoring .if {macro_name} directive")
                ifdef_level += level
                ifdef_levels.append(level)
            elif directive == ".else":
                level = ifdef_levels.pop()
                ifdef_level -= level
                level = 1 - level
                ifdef_level += level
                ifdef_levels.append(level)
            elif directive == ".endif":
                ifdef_level -= ifdef_levels.pop()
            elif directive == ".macro":
                ifdef_level += 1
            elif directive == ".endm":
                ifdef_level -= 1
            elif ifdef_level == 0:
                if directive == ".section":
                    curr_section = line.split()[1].split(",")[0]
                    if curr_section in (".rdata", ".late_rodata", ".sdata2"):
                        curr_section = ".rodata"
                    elif curr_section == ".sdata":
                        curr_section = ".data"
                    elif curr_section.startswith(".text"):
                        curr_section = ".text"
                elif (
                    directive == ".rdata"
                    or directive == ".rodata"
                    or directive == ".late_rodata"
                ):
                    curr_section = ".rodata"
                elif directive == ".data":
                    curr_section = ".data"
                elif directive == ".bss":
                    curr_section = ".bss"
                elif directive == ".text":
                    curr_section = ".text"
                elif directive == ".set":
                    _, _, args_str = line.partition(" ")
                    args = split_arg_list(args_str)
                    if len(args) == 1:
                        # ".set noreorder" or similar, just ignore
                        pass
                    elif len(args) == 2:
                        defines[args[0]] = try_parse(lambda: parse_int(args[1]))
                    else:
                        raise DecompFailure(f"Could not parse {directive}: {line}")
                elif curr_section in (".rodata", ".data", ".bss"):
                    _, _, args_str = line.partition(" ")
                    args = split_arg_list(args_str)
                    if directive in (".word", ".4byte"):
                        for w in args:
                            if not w or w[0].isdigit() or w[0] == "-" or w in defines:
                                ival = try_parse(lambda: parse_int(w)) & 0xFFFFFFFF
                                asm_file.new_data_bytes(struct.pack(">I", ival))
                            else:
                                asm_file.new_data_sym(w)
                    elif directive in (".short", ".half", ".2byte"):
                        for w in args:
                            ival = try_parse(lambda: parse_int(w)) & 0xFFFF
                            asm_file.new_data_bytes(struct.pack(">H", ival))
                    elif directive == ".byte":
                        for w in args:
                            ival = try_parse(lambda: parse_int(w)) & 0xFF
                            asm_file.new_data_bytes(bytes([ival]))
                    elif directive == ".float":
                        for w in args:
                            fval = try_parse(lambda: float(w))
                            asm_file.new_data_bytes(struct.pack(">f", fval))
                    elif directive == ".double":
                        for w in args:
                            fval = try_parse(lambda: float(w))
                            asm_file.new_data_bytes(struct.pack(">d", fval))
                    elif directive in (".asci", ".asciz", ".ascii", ".asciiz"):
                        z = directive.endswith("z")
                        asm_file.new_data_bytes(
                            parse_ascii_directive(line, z), is_string=True
                        )
                    elif directive in (".space", ".skip"):
                        if len(args) == 2:
                            fill = try_parse(lambda: parse_int(args[1])) & 0xFF
                        elif len(args) == 1:
                            fill = 0
                        else:
                            raise DecompFailure(
                                f"Could not parse asm_data {directive} in {curr_section}: {line}"
                            )
                        size = try_parse(lambda: parse_int(args[0]))
                        asm_file.new_data_bytes(bytes([fill] * size))
                    elif line.startswith(".incbin"):
                        data = parse_incbin(args, options, warnings)
                        if data is not None:
                            asm_file.new_data_bytes(data)

        elif ifdef_level == 0:
            if directive in ("glabel", "dlabel"):
                parts = line.split()
                if len(parts) >= 2:
                    process_label(parts[1], glabel=True)

            elif curr_section == ".text":
                meta = InstructionMeta(
                    emit_goto=emit_goto,
                    filename=filename,
                    lineno=lineno,
                    synthetic=False,
                )
                if asm_file.current_function is not None:
                    reg_formatter = asm_file.current_function.reg_formatter
                else:
                    reg_formatter = RegFormatter()
                defined_vars = {k: v for k, v in defines.items() if v is not None}
                instr = parse_instruction(line, meta, arch, reg_formatter, defined_vars)
                asm_file.new_instruction(instr)

    if warnings:
        print("/*")
        print("\n".join(warnings))
        print("*/")

    return asm_file
