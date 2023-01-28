import abc
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Sequence, Tuple, TypeVar, Union

from .asm_file import Label
from .asm_instruction import (
    Argument,
    AsmAddressMode,
    AsmGlobalSymbol,
    AsmInstruction,
    AsmLiteral,
    BinOp,
    JumpTarget,
    NaiveParsingArch,
    Register,
    RegFormatter,
    parse_asm_instruction,
)
from .instruction import (
    ArchAsm,
    Instruction,
    InstructionMeta,
)


BodyPart = Union[Instruction, Label]
ReplacementPart = Union[AsmInstruction, Instruction, Label]
PatternPart = Union[AsmInstruction, Label, None]
Pattern = List[Tuple[PatternPart, bool]]


def make_pattern(*parts: str) -> Pattern:
    ret: Pattern = []
    for part in parts:
        optional = part.endswith("?")
        part = part.rstrip("?")
        if part == "*":
            ret.append((None, optional))
        elif part.endswith(":"):
            ret.append((Label(part.strip(".:")), optional))
        else:
            ins = parse_asm_instruction(part, NaiveParsingArch(), RegFormatter(), {})
            ret.append((ins, optional))
    return ret


@dataclass
class Replacement:
    new_body: Sequence[ReplacementPart]
    num_consumed: int


@dataclass
class AsmMatch:
    body: List[BodyPart]
    wildcard_items: List[BodyPart]
    regs: Dict[str, Register]
    literals: Dict[str, int]


class AsmPattern(abc.ABC):
    @abc.abstractmethod
    def match(self, matcher: "AsmMatcher") -> Optional[Replacement]:
        ...


class SimpleAsmPattern(AsmPattern):
    @property
    @abc.abstractmethod
    def pattern(self) -> Pattern:
        ...

    @abc.abstractmethod
    def replace(self, m: "AsmMatch") -> Optional[Replacement]:
        ...

    def match(self, matcher: "AsmMatcher") -> Optional[Replacement]:
        m = matcher.try_match(self.pattern)
        if not m:
            return None
        return self.replace(m)


@dataclass
class TryMatchState:
    symbolic_registers: Dict[str, Register] = field(default_factory=dict)
    symbolic_labels: Dict[str, str] = field(default_factory=dict)
    symbolic_literals: Dict[str, int] = field(default_factory=dict)
    wildcard_items: List[BodyPart] = field(default_factory=list)

    T = TypeVar("T")

    def match_var(self, var_map: Dict[str, T], key: str, value: T) -> bool:
        if key in var_map:
            if var_map[key] != value:
                return False
        else:
            var_map[key] = value
        return True

    def match_reg(self, actual: Register, exp: Register) -> bool:
        if len(exp.register_name) <= 1:
            return self.match_var(self.symbolic_registers, exp.register_name, actual)
        else:
            return exp.register_name == actual.register_name

    def eval_math(self, e: Argument) -> int:
        if isinstance(e, AsmLiteral):
            return e.value
        if isinstance(e, BinOp):
            if e.op == "+":
                return self.eval_math(e.lhs) + self.eval_math(e.rhs)
            if e.op == "-":
                return self.eval_math(e.lhs) - self.eval_math(e.rhs)
            if e.op == "<<":
                return self.eval_math(e.lhs) << self.eval_math(e.rhs)
            assert False, f"bad binop in math pattern: {e}"
        elif isinstance(e, AsmGlobalSymbol):
            assert (
                e.symbol_name in self.symbolic_literals
            ), f"undefined variable in math pattern: {e.symbol_name}"
            return self.symbolic_literals[e.symbol_name]
        else:
            assert False, f"bad pattern part in math pattern: {e}"

    def match_arg(self, a: Argument, e: Argument) -> bool:
        if isinstance(e, AsmLiteral):
            return isinstance(a, AsmLiteral) and a.value == e.value
        if isinstance(e, Register):
            return isinstance(a, Register) and self.match_reg(a, e)
        if isinstance(e, AsmGlobalSymbol):
            if e.symbol_name.isupper():
                return isinstance(a, AsmLiteral) and self.match_var(
                    self.symbolic_literals, e.symbol_name, a.value
                )
            elif e.symbol_name == "_":
                return True
            else:
                return isinstance(a, AsmGlobalSymbol) and a.symbol_name == e.symbol_name
        if isinstance(e, AsmAddressMode):
            return (
                isinstance(a, AsmAddressMode)
                and self.match_arg(a.lhs, e.lhs)
                and self.match_reg(a.rhs, e.rhs)
            )
        if isinstance(e, JumpTarget):
            return isinstance(a, JumpTarget) and self.match_var(
                self.symbolic_labels, e.target, a.target
            )
        if isinstance(e, BinOp):
            return isinstance(a, AsmLiteral) and a.value == self.eval_math(e)
        assert False, f"bad pattern part: {e}"

    def match_one(self, actual: BodyPart, exp: PatternPart) -> bool:
        if exp is None:
            self.wildcard_items.append(actual)
            return True
        if isinstance(exp, Label):
            return isinstance(actual, Label) and self.match_var(
                self.symbolic_labels, exp.name, actual.name
            )
        if not isinstance(actual, Instruction):
            return False
        ins = actual
        if ins.mnemonic != exp.mnemonic:
            return False
        if exp.args:
            if len(ins.args) != len(exp.args):
                return False
            for (a, e) in zip(ins.args, exp.args):
                if not self.match_arg(a, e):
                    return False
        return True

    def match_meta(self, ins: AsmInstruction) -> bool:
        assert ins.mnemonic == ".eq"
        res = self.eval_math(ins.args[1])
        return self.match_arg(AsmLiteral(res), ins.args[0])


@dataclass
class AsmMatcher:
    input: List[BodyPart]
    output: List[BodyPart] = field(default_factory=list)
    index: int = 0

    def try_match(self, pattern: Pattern) -> Optional[AsmMatch]:
        state = TryMatchState()

        start_index = index = self.index
        for (pat, optional) in pattern:
            if isinstance(pat, AsmInstruction) and pat.mnemonic[0] == ".":
                if not state.match_meta(pat) and not optional:
                    return None
            elif index < len(self.input) and state.match_one(self.input[index], pat):
                index += 1
            elif not optional:
                return None
        return AsmMatch(
            self.input[start_index:index],
            state.wildcard_items,
            state.symbolic_registers,
            state.symbolic_literals,
        )

    def derived_meta(self) -> InstructionMeta:
        for part in self.input[self.index :]:
            if isinstance(part, Instruction):
                return part.meta.derived()
        return InstructionMeta.missing()

    def apply(self, repl: Replacement, arch: ArchAsm) -> None:
        # Track which registers are overwritten/clobbered in the replacement asm
        repl_writes = []
        final_instr: Optional[Instruction] = None
        for part in repl.new_body:
            if isinstance(part, AsmInstruction):
                # Parse any AsmInstructions into Instructions before substituting
                part = arch.parse(part.mnemonic, part.args, self.derived_meta())
            if isinstance(part, Instruction):
                # Update list of written registers
                repl_writes.extend(part.outputs)
                repl_writes.extend(part.clobbers)
                final_instr = part
            self.output.append(part)

        # Calculate which regs are *not* written by the repl asm, but were in the input asm
        # Denote the replacement asm as "clobbering" these regs by marking the final instr
        for part in self.input[self.index : self.index + repl.num_consumed]:
            if isinstance(part, Instruction):
                for arg in part.outputs + part.clobbers:
                    assert final_instr is not None
                    if arg not in repl_writes and arg not in final_instr.clobbers:
                        final_instr.clobbers.append(arg)

        # Advance the input
        self.index += repl.num_consumed


def simplify_patterns(
    body: List[BodyPart],
    patterns: List[AsmPattern],
    arch: ArchAsm,
) -> List[BodyPart]:
    """Detect and simplify asm standard patterns emitted by known compilers. This is
    especially useful for patterns that involve branches, which are hard to deal with
    in the translate phase."""
    matcher = AsmMatcher(body)
    while matcher.index < len(matcher.input):
        for pattern in patterns:
            m = pattern.match(matcher)
            if m:
                matcher.apply(m, arch)
                break
        else:
            matcher.apply(Replacement([matcher.input[matcher.index]], 1), arch)

    return matcher.output
