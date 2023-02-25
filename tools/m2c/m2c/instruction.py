import abc
from contextlib import contextmanager
from dataclasses import dataclass, replace
from typing import Callable, Dict, Iterator, List, Optional, Union

from .error import DecompFailure
from .options import Target
from .asm_instruction import (
    ArchAsmParsing,
    Argument,
    AsmGlobalSymbol,
    AsmLiteral,
    BinOp,
    JumpTarget,
    RegFormatter,
    Register,
    parse_asm_instruction,
)


@dataclass(frozen=True)
class StackLocation:
    """
    Represents a word on the stack. Currently only used for pattern matching.
    `symbolic_offset` represents a label offset that is only used in patterns,
    to represent the "N" in arguments such as `(N+4)($sp)`.
    """

    offset: int
    symbolic_offset: Optional[str]

    def __str__(self) -> str:
        prefix = "" if self.symbolic_offset is None else f"{self.symbolic_offset}+"
        return f"{prefix}{self.offset}($sp)"

    def offset_as_arg(self) -> Argument:
        if self.symbolic_offset is None:
            return AsmLiteral(self.offset)
        if self.offset == 0:
            return AsmGlobalSymbol(self.symbolic_offset)
        return BinOp(
            lhs=AsmGlobalSymbol(self.symbolic_offset),
            op="+",
            rhs=AsmLiteral(self.offset),
        )

    @staticmethod
    def from_offset(offset: Argument) -> Optional["StackLocation"]:
        def align(x: int) -> int:
            return x & ~3

        if isinstance(offset, AsmLiteral):
            return StackLocation(
                offset=align(offset.value),
                symbolic_offset=None,
            )
        if isinstance(offset, AsmGlobalSymbol):
            return StackLocation(
                offset=0,
                symbolic_offset=offset.symbol_name,
            )
        if (
            isinstance(offset, BinOp)
            and offset.op in ("+", "-")
            and isinstance(offset.lhs, AsmGlobalSymbol)
            and isinstance(offset.rhs, AsmLiteral)
        ):
            base = offset.rhs.value
            if offset.op == "-":
                base = -base
            return StackLocation(
                offset=align(base),
                symbolic_offset=offset.lhs.symbol_name,
            )
        return None


Location = Union[Register, StackLocation]


@dataclass(frozen=True)
class InstructionMeta:
    # True if the original asm line was marked with a goto pattern
    emit_goto: bool
    # Asm source filename & line number
    filename: str
    lineno: int
    # True if the Instruction is not directly from the source asm
    synthetic: bool

    @staticmethod
    def missing() -> "InstructionMeta":
        return InstructionMeta(
            emit_goto=False, filename="<unknown>", lineno=0, synthetic=True
        )

    def derived(self) -> "InstructionMeta":
        return replace(self, synthetic=True)

    def loc_str(self) -> str:
        adj = "near" if self.synthetic else "at"
        return f"{adj} {self.filename} line {self.lineno}"


@dataclass(frozen=True, eq=False)
class Instruction:
    mnemonic: str
    args: List[Argument]
    meta: InstructionMeta

    # Track register and stack dependencies
    # An Instruction evaluates by reading from `inputs`, invalidating `clobbers`,
    # then writing to `outputs` (in that order)
    inputs: List[Location]
    clobbers: List[Location]
    outputs: List[Location]

    # This should be typed as `eval_fn: Optional[Callable[[NodeState, InstrArgs], object]]`
    # but this use classes that are defined in translate.py. We're unable to use correct
    # types here without creating circular dependencies.
    # The return value is ignored, but is typed as `object` so lambdas are more ergonomic.
    # This member should only be accessed by `evaluate_instruction`.
    eval_fn: Optional[Callable[..., object]]

    jump_target: Optional[Union[JumpTarget, Register]] = None
    function_target: Optional[Argument] = None
    is_conditional: bool = False
    is_return: bool = False
    is_store: bool = False

    # These are for MIPS. `is_branch_likely` refers to branch instructions which
    # execute their delay slot only if the branch *is* taken. (Maybe these two
    # bools should be merged into a 3-valued enum?)
    has_delay_slot: bool = False
    is_branch_likely: bool = False

    # True if the Instruction was part of a matched IR pattern, but not elided
    in_pattern: bool = False

    def is_jump(self) -> bool:
        return self.jump_target is not None or self.is_return

    def __str__(self) -> str:
        if not self.args:
            return self.mnemonic
        args = ", ".join(str(arg) for arg in self.args)
        return f"{self.mnemonic} {args}"

    def arch_mnemonic(self, arch: "ArchAsm") -> str:
        """Combine architecture name with mnemonic for pattern matching"""
        return f"{arch.arch}:{self.mnemonic}"

    def clone(self) -> "Instruction":
        return replace(self, meta=self.meta.derived())


class ArchAsm(ArchAsmParsing):
    """Arch-specific information that relates to the asm level. Extends ArchAsmParsing."""

    arch: Target.ArchEnum

    stack_pointer_reg: Register
    frame_pointer_reg: Optional[Register]
    return_address_reg: Register

    base_return_regs: List[Register]
    all_return_regs: List[Register]
    argument_regs: List[Register]
    simple_temp_regs: List[Register]
    temp_regs: List[Register]
    saved_regs: List[Register]
    all_regs: List[Register]

    @abc.abstractmethod
    def missing_return(self) -> List[Instruction]:
        ...

    @abc.abstractmethod
    def parse(
        self, mnemonic: str, args: List[Argument], meta: InstructionMeta
    ) -> Instruction:
        ...


def parse_instruction(
    line: str,
    meta: InstructionMeta,
    arch: ArchAsm,
    reg_formatter: RegFormatter,
    defines: Dict[str, int],
) -> Instruction:
    try:
        base = parse_asm_instruction(line, arch, reg_formatter, defines)
        return arch.parse(base.mnemonic, base.args, meta)
    except Exception as e:
        msg = f"Failed to parse instruction {meta.loc_str()}: {line}"
        if isinstance(e, DecompFailure):
            msg += "\n\n" + e.message
        raise DecompFailure(msg)


@dataclass
class InstrProcessingFailure(Exception):
    instr: Instruction

    def __str__(self) -> str:
        return f"Error while processing instruction:\n{self.instr}"


@contextmanager
def set_current_instr(instr: Instruction) -> Iterator[None]:
    """Mark an instruction as being the one currently processed, for the
    purposes of error messages. Use like |with set_current_instr(instr): ...|"""
    try:
        yield
    except Exception as e:
        raise InstrProcessingFailure(instr) from e
