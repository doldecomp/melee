import abc
from collections import defaultdict
from dataclasses import dataclass, field, replace
from typing import ClassVar, Dict, List, Optional, TypeVar

from .error import static_assert_unreachable
from .flow_graph import (
    ArchFlowGraph,
    BaseNode,
    FlowGraph,
    InstrRef,
    LocationRefSetDict,
    RefSet,
    Reference,
    TerminalNode,
    build_flowgraph,
)
from .asm_file import AsmData, Function
from .asm_instruction import (
    Argument,
    AsmAddressMode,
    AsmGlobalSymbol,
    AsmInstruction,
    AsmLiteral,
    BinOp,
    JumpTarget,
    RegFormatter,
    Register,
)
from .instruction import (
    Instruction,
    InstructionMeta,
    Location,
    StackLocation,
    parse_instruction,
)


@dataclass(eq=False, frozen=True)
class IrPattern(abc.ABC):
    """
    Template for defining "IR" patterns that can match against input asm.
    The matching process uses the FlowGraph and register analysis to compute
    inter-instruction dependencies, so these patterns can match even when
    they have been interleaved/reordered by the compiler in the input asm.

    IrPattern subclasses *must* define `parts` and `replacement`, and can
    optionally implement `check()`.

    For now, the pattern cannot contain any branches, and the replacement
    must be a single instruction (though, it can be fictive).
    """

    parts: ClassVar[List[str]]
    replacement: ClassVar[str]

    def check(self, m: "IrMatch") -> bool:
        """Override to perform additional checks before replacement."""
        return True

    def compile(self, arch: ArchFlowGraph) -> "CompiledIrPattern":
        missing_meta = InstructionMeta.missing()
        regf = RegFormatter()
        replacement_instr = parse_instruction(
            self.replacement, missing_meta, arch, regf, {}
        )

        name = f"__pattern_{self.__class__.__name__}"
        func = Function(name=name)
        # Add a fictive nop instruction for each input to the replacement_instr.
        # This acts as a placeholder Reference to represent where the input was set,
        # and allows each input to be sourced from a different Reference.
        assert len(replacement_instr.inputs) == len(
            set(replacement_instr.inputs)
        ), "pattern inputs must be unique"
        for inp in replacement_instr.inputs:
            func.new_instruction(
                Instruction(
                    "in.fictive",
                    [],
                    meta=missing_meta,
                    inputs=[],
                    clobbers=[],
                    outputs=[inp],
                    eval_fn=None,
                )
            )
        for part in self.parts:
            func.new_instruction(parse_instruction(part, missing_meta, arch, regf, {}))

        asm_data = AsmData()
        flow_graph = build_flowgraph(func, asm_data, arch, fragment=True)
        return CompiledIrPattern(
            source=self,
            flow_graph=flow_graph,
            replacement_instr=replacement_instr,
        )


@dataclass(eq=False, frozen=True)
class CompiledIrPattern:
    source: IrPattern

    flow_graph: FlowGraph
    replacement_instr: Instruction


@dataclass
class IrMatch:
    """
    IrMatch represents the matched state of an IrPattern.
    This object is considered read-only; none of its methods modify its state.
    The `map_*` methods take a pattern part and return the matched part of the original asm.

    Single-letter registers and all-uppercase symbols in patterns are symbolic,
    whereas other registers and symbols are matched literally.
    """

    symbolic_registers: Dict[str, Register] = field(default_factory=dict)
    symbolic_labels: Dict[str, str] = field(default_factory=dict)
    symbolic_args: Dict[str, Argument] = field(default_factory=dict)
    ref_map: Dict[Reference, RefSet] = field(default_factory=dict)

    @staticmethod
    def _is_symbolic_reg(arg: Register) -> bool:
        # Single-letter registers are symbolic; everything else is literal
        return len(arg.register_name) <= 1

    @staticmethod
    def _is_symbolic_sym(arg: AsmGlobalSymbol) -> bool:
        # Uppercase symbols are symbolic; everything else is literal
        return arg.symbol_name.isupper()

    def eval_math(self, pat: Argument) -> Argument:
        # This function can only evaluate math in *patterns*, not candidate
        # instructions. It does not need to support arbitrary math, only
        # math used by IR patterns.
        if isinstance(pat, AsmLiteral):
            return pat
        if isinstance(pat, BinOp):
            lhs = self.eval_math(pat.lhs)
            rhs = self.eval_math(pat.rhs)
            if isinstance(lhs, AsmLiteral) and isinstance(rhs, AsmLiteral):
                if pat.op == "+":
                    return AsmLiteral(lhs.value + rhs.value)
                if pat.op == "-":
                    return AsmLiteral(lhs.value - rhs.value)
                if pat.op == "<<":
                    return AsmLiteral(lhs.value << rhs.value)
            return BinOp(pat.op, lhs, rhs)
        elif isinstance(pat, AsmGlobalSymbol):
            assert (
                pat.symbol_name in self.symbolic_args
            ), f"undefined variable in math pattern: {pat.symbol_name}"
            lit = self.symbolic_args[pat.symbol_name]
            return lit
        else:
            assert False, f"bad pattern expr: {pat}"

    def map_reg(self, key: Register) -> Register:
        if self._is_symbolic_reg(key):
            return self.symbolic_registers[key.register_name]
        return key

    def map_arg(self, key: Argument) -> Argument:
        if isinstance(key, AsmLiteral):
            return key
        if isinstance(key, Register):
            return self.map_reg(key)
        if isinstance(key, AsmGlobalSymbol):
            if self._is_symbolic_sym(key):
                return self.symbolic_args[key.symbol_name]
            return key
        if isinstance(key, AsmAddressMode):
            return AsmAddressMode(lhs=self.map_arg(key.lhs), rhs=self.map_reg(key.rhs))
        if isinstance(key, JumpTarget):
            return JumpTarget(self.symbolic_labels[key.target])
        if isinstance(key, BinOp):
            return self.eval_math(key)
        assert False, f"bad pattern part: {key}"

    def map_ref(self, key: Reference) -> InstrRef:
        refset = self.ref_map[key]
        value = refset.get_unique()
        assert isinstance(value, InstrRef)
        return value

    def try_map_ref(self, key: Reference) -> Optional[Reference]:
        refset = self.ref_map.get(key)
        if refset is None:
            return None
        return refset.get_unique()

    def map_location(self, key: Location) -> Location:
        if isinstance(key, Register):
            return self.map_reg(key)
        if isinstance(key, StackLocation):
            loc = StackLocation.from_offset(self.map_arg(key.offset_as_arg()))
            assert loc is not None
            return loc
        static_assert_unreachable(key)

    def map_asm(self, key: Instruction) -> AsmInstruction:
        return AsmInstruction(key.mnemonic, [self.map_arg(a) for a in key.args])


class TryIrMatch(IrMatch):
    """
    TryIrMatch represents the partial (in-progress) match state of an IrPattern.
    Unlike IrMatch, all of its `match_*` methods may modify its internal state.
    These all take a pair of arguments: pattern part, and candidate asm part.
    """

    K = TypeVar("K")
    V = TypeVar("V")

    def _match_var(self, var_map: Dict[K, V], key: K, value: V) -> bool:
        if key in var_map:
            if var_map[key] != value:
                return False
        else:
            var_map[key] = value
        return True

    def match_arg(self, pat: Argument, cand: Argument) -> bool:
        if isinstance(pat, AsmLiteral):
            return pat == cand
        if isinstance(pat, Register):
            if not self._is_symbolic_reg(pat):
                return pat == cand
            if not isinstance(cand, Register):
                return False
            return self._match_var(self.symbolic_registers, pat.register_name, cand)
        if isinstance(pat, AsmGlobalSymbol):
            if self._is_symbolic_sym(pat):
                return self._match_var(self.symbolic_args, pat.symbol_name, cand)
            return pat == cand
        if isinstance(pat, AsmAddressMode):
            return (
                isinstance(cand, AsmAddressMode)
                and self.match_arg(pat.lhs, cand.lhs)
                and self.match_arg(pat.rhs, cand.rhs)
            )
        if isinstance(pat, JumpTarget):
            return isinstance(cand, JumpTarget) and self._match_var(
                self.symbolic_labels, pat.target, cand.target
            )
        if isinstance(pat, BinOp):
            return self.eval_math(pat) == cand

        assert False, f"bad pattern arg: {pat}"

    def match_instr(self, pat: Instruction, cand: Instruction) -> bool:
        if pat.mnemonic != cand.mnemonic or len(pat.args) != len(cand.args):
            return False
        return all(self.match_arg(*args) for args in zip(pat.args, cand.args))

    def match_refset(self, pat: Reference, cand_set: RefSet) -> bool:
        return self._match_var(self.ref_map, pat, cand_set.copy())

    def match_inputrefs(
        self, pat: LocationRefSetDict, cand: LocationRefSetDict
    ) -> bool:
        for pat_loc, pat_refs in pat.items():
            cand_loc = self.map_location(pat_loc)
            cand_refs = cand.get(cand_loc)
            pat_ref = pat_refs.get_unique()
            assert pat_ref is not None, "patterns can not have phis"
            if not self.match_refset(pat_ref, cand_refs):
                return False
        return True

    def rename_reg(self, pat: Register, new_reg: Register) -> None:
        assert pat.register_name in self.symbolic_registers
        self.symbolic_registers[pat.register_name] = new_reg


def simplify_ir_patterns(
    arch: ArchFlowGraph, flow_graph: FlowGraph, patterns: List[IrPattern]
) -> None:
    # Precompute a RefSet for each mnemonic
    # NB: It's difficult to plainly iterate over all Instruction in the flow_graph
    # while it is being modified by the pattern replacement machinery.
    refs_by_mnemonic = defaultdict(list)
    for node in flow_graph.nodes:
        for ref in node.block.instruction_refs:
            refs_by_mnemonic[ref.instruction.mnemonic].append(ref)

    # Counter used to name temporary registers
    fictive_reg_index = 0

    for pattern_base in patterns:
        pattern = pattern_base.compile(arch)

        # For now, patterns can't have branches: they should only have 2 Nodes,
        # a BaseNode and an (empty) TerminalNode.
        assert (
            len(pattern.flow_graph.nodes) == 2
        ), "branching patterns not yet supported"
        assert isinstance(pattern.flow_graph.nodes[0], BaseNode)
        assert isinstance(pattern.flow_graph.nodes[1], TerminalNode)
        pattern_node = pattern.flow_graph.nodes[0]
        pattern_refs = pattern_node.block.instruction_refs

        # Split the pattern asm into 3 disjoint sets of instructions:
        # input_refs ("in.fictive"s), body_refs, and tail_ref (the last instruction)
        n_inputs = len(pattern.replacement_instr.inputs)
        input_refs, body_refs, tail_ref = (
            pattern_refs[:n_inputs],
            pattern_refs[n_inputs:-1],
            pattern_refs[-1],
        )
        assert all(r.instruction.mnemonic == "in.fictive" for r in input_refs)
        assert all(r.instruction.mnemonic != "in.fictive" for r in body_refs)

        # For now, pattern inputs must be Registers, not StackLocations. It's not always
        # trivial to create temporary StackLocations in the same way we create temporary
        # Registers during replacement. (Also, we do not have a way to elide temporary
        # stack variables during translation like we do with registers.)
        assert all(
            isinstance(inp, Register) for inp in pattern.replacement_instr.inputs
        )

        # For now, patterns can only have 1 output register (which must be set by the
        # final instruction in the pattern). This simplifies the replacement step because
        # we can replace the final instruction and know that all the pattern inputs have
        # been assigned by there, and the output has not yet been used.
        assert len(pattern.replacement_instr.outputs) == 1
        assert pattern.replacement_instr.outputs == tail_ref.instruction.outputs

        # Start matches with a mnemonic match for the last instruction in the pattern
        for cand_tail_ref in refs_by_mnemonic.get(tail_ref.instruction.mnemonic, []):
            state = TryIrMatch()
            if not state.match_refset(tail_ref, RefSet([cand_tail_ref])):
                continue

            # Continue matching by working backwards through the pattern
            is_match = True
            for pat_ref in [tail_ref] + body_refs[::-1]:
                # By pattern construction, pat_ref should be in the state's ref_map
                # (It would be missing for "disjoint" or irrelevant instructions in the
                # pattern, like random nops: these aren't allowed)
                cand = state.try_map_ref(pat_ref)
                pat_inputs = pattern.flow_graph.instr_inputs[pat_ref]
                if not (
                    isinstance(cand, InstrRef)
                    and state.match_instr(pat_ref.instruction, cand.instruction)
                    and state.match_inputrefs(pat_inputs, flow_graph.instr_inputs[cand])
                ):
                    is_match = False
                    break

            # Perform any additional pattern-specific validation
            if not is_match or not pattern.source.check(state):
                continue

            # Create temporary registers for the inputs to the replacement_instr.
            # These retain the input register contents even if an unrelated instruction
            # overwrites the register in the middle of the pattern.
            temp_reg_refs = {}
            for pat_ref in input_refs:
                assert len(pat_ref.instruction.outputs) == 1
                input_reg = pat_ref.instruction.outputs[0]
                assert isinstance(input_reg, Register)

                # It doesn't matter which instruction we pick; the new move instruction to save
                # the register can come before any of the instructions that use it.
                input_uses = pattern.flow_graph.instr_uses[pat_ref].get(input_reg)
                input_use_ref = state.map_ref(next(iter(input_uses)))

                # Create a unique fictive register to act as a temporary
                original_reg = state.map_reg(input_reg)
                temp_reg = Register(
                    f"{original_reg.register_name}_fictive_{fictive_reg_index}"
                )
                fictive_reg_index += 1
                state.rename_reg(input_reg, temp_reg)

                move_asm = AsmInstruction("move.fictive", [temp_reg, original_reg])
                move_ref = input_use_ref.add_instruction_before(move_asm, arch)
                temp_reg_refs[temp_reg] = move_ref

                # Update the instr_inputs/instr_uses graph
                for src_ref in flow_graph.instr_inputs[input_use_ref].get(original_reg):
                    flow_graph.add_instruction_use(
                        use=move_ref, loc=original_reg, src=src_ref
                    )

            # Rewrite the final instruction with the pattern's replacement instruction.
            repl_ref = state.map_ref(tail_ref)
            repl_asm = state.map_asm(pattern.replacement_instr)
            repl_ref.replace_instruction(repl_asm, arch)

            # Reset repl_ref's dependencies, then repopulate them from temp_reg_refs
            flow_graph.clear_instruction_inputs(repl_ref)
            for temp_reg, temp_ref in temp_reg_refs.items():
                flow_graph.add_instruction_use(use=repl_ref, loc=temp_reg, src=temp_ref)

            # For the rest of the instructions in the pattern body, take any instructions
            # whose outputs aren't used later and replace them with nops.
            for pat_ref in body_refs[::-1]:
                cand_ref = state.map_ref(pat_ref)

                if flow_graph.instr_uses[cand_ref].is_empty():
                    # Replace cand_ref with a nop, and clear its dependencies
                    nop_asm = AsmInstruction("nop", [])
                    cand_ref.replace_instruction(nop_asm, arch)
                    flow_graph.clear_instruction_inputs(cand_ref)
                elif not cand_ref.instruction.in_pattern:
                    # It needs to be kept; but ensure the meta.in_pattern flag is set
                    cand_ref.instruction = replace(
                        cand_ref.instruction, in_pattern=True
                    )

    # After all of the rewrites above, verify that the instruction dependency
    # data structures are still consistent
    flow_graph.validate_instruction_graph()
