import abc
from collections import defaultdict
from dataclasses import dataclass, field, replace
from typing import (
    Any,
    Callable,
    Counter,
    DefaultDict,
    Dict,
    ItemsView,
    Iterator,
    List,
    Optional,
    Set,
    Tuple,
    Union,
)

from .error import DecompFailure
from .options import Formatter, Options, Target
from .asm_file import AsmData, Function, Label
from .asm_instruction import (
    AsmAddressMode,
    AsmGlobalSymbol,
    AsmInstruction,
    JumpTarget,
    Macro,
    Register,
)
from .instruction import (
    ArchAsm,
    Instruction,
    Location,
)
from .asm_pattern import simplify_patterns, AsmPattern


class ArchFlowGraph(ArchAsm):
    asm_patterns: List[AsmPattern] = []

    def simplify_ir(self, flow_graph: "FlowGraph") -> None:
        ...


class Reference(abc.ABC):
    """
    Reference acts as a pointer to either a specific Instruction, or one of the function's
    bounds (either before the function is called, or after the function returns)
    """


@dataclass(frozen=True)
class PrologueRef(Reference):
    """Reference to a Location's value before the start of a function (e.g. constants, args)"""

    location: Location


@dataclass(frozen=True)
class EpilogueRef(Reference):
    """Reference to return values of a function"""

    location: Location


@dataclass(eq=False)
class InstrRef(Reference):
    """
    Pointer to an Instruction as part of a Block. Allows other datastructures
    to hold references to a spot in the assembly that remains valid even as
    the Instruction is replaced or other Instructions are added to the Block.
    """

    instruction: Instruction
    block: "Block" = field(repr=False)

    def add_instruction_before(
        self, asm: AsmInstruction, arch: ArchFlowGraph
    ) -> "InstrRef":
        """Add `asm` into the parent assembly before this instruction."""
        instr = arch.parse(asm.mnemonic, asm.args, self.instruction.meta.derived())
        ref = InstrRef(instr, self.block)
        index = self.block.instruction_refs.index(self)
        self.block.instruction_refs.insert(index, ref)
        return ref

    def replace_instruction(self, new_asm: AsmInstruction, arch: ArchFlowGraph) -> None:
        """Replace the existing instruciton with `new_asm`.
        Previous ouputs & clobbers are added to the new Instruction's clobbers list."""
        old_instr = self.instruction
        new_instr = arch.parse(new_asm.mnemonic, new_asm.args, old_instr.meta.derived())

        # Copy over old outputs/clobbers into new_instr.clobbers
        for loc in old_instr.outputs + old_instr.clobbers:
            if loc not in new_instr.clobbers:
                new_instr.clobbers.append(loc)
        self.instruction = new_instr


@dataclass(eq=False)
class Block:
    index: int
    label: Optional[Label]
    approx_label_name: str
    instruction_refs: List[InstrRef] = field(default_factory=list)
    is_safeguard: bool = False

    # block_info is actually an Optional[BlockInfo], set by translate.py for
    # non-TerminalNode's, but due to circular dependencies we cannot type it
    # correctly. To access it, use the get_block_info method from translate.py.
    block_info: object = None

    @property
    def instructions(self) -> Iterator[Instruction]:
        return (r.instruction for r in self.instruction_refs)

    def add_block_info(self, block_info: object) -> None:
        assert self.block_info is None
        self.block_info = block_info

    def clone(self) -> "Block":
        ret = replace(self, instruction_refs=[])
        ret.instruction_refs = [
            InstrRef(ref.instruction.clone(), ret) for ref in self.instruction_refs
        ]
        return ret

    def __str__(self) -> str:
        name = f"{self.index} ({self.approx_label_name})"
        inst_str = "\n".join("    " + str(instr) for instr in self.instructions)
        return f"# {name}\n{inst_str}\n"


@dataclass(eq=False)
class BlockBuilder:
    _curr_index: int = 0
    _curr_label: Optional[Label] = None
    _last_label_name: str = "initial"
    _label_counter: int = 0
    _curr_instructions: List[Instruction] = field(default_factory=list)
    _blocks: List[Block] = field(default_factory=list)

    def new_block(self) -> Optional[Block]:
        if len(self._curr_instructions) == 0:
            return None

        label_name = self._last_label_name
        if self._label_counter > 0:
            label_name += f".{self._label_counter}"
        block = Block(self._curr_index, self._curr_label, label_name)
        block.instruction_refs.extend(
            InstrRef(i, block) for i in self._curr_instructions
        )
        self._blocks.append(block)

        self._curr_index += 1
        self._curr_label = None
        self._label_counter += 1
        self._curr_instructions = []

        return block

    def add_instruction(self, instruction: Instruction) -> None:
        self._curr_instructions.append(instruction)

    def set_label(self, label: Label) -> None:
        if label == self._curr_label:
            # It's okay to repeat a label (e.g. once with glabel, once as a
            # standard label -- this often occurs for switches).
            return
        # We could support multiple labels at the same position, and output
        # empty blocks. For now we don't, however.
        if self._curr_label:
            raise DecompFailure(
                "A block is currently not allowed to have more than one label,\n"
                f"but {self._curr_label.name}/{label.name} is given two."
            )
        self._curr_label = label
        self._last_label_name = label.name
        self._label_counter = 0

    def is_empty(self) -> bool:
        return not self._blocks and not self._curr_instructions

    def get_blocks(self) -> List[Block]:
        return self._blocks


def verify_no_trailing_delay_slot(function: Function) -> None:
    last_ins: Optional[Instruction] = None
    for item in function.body:
        if isinstance(item, Instruction):
            last_ins = item
    if last_ins and last_ins.has_delay_slot:
        raise DecompFailure(f"Last instruction is missing a delay slot:\n{last_ins}")


def invert_branch_mnemonic(mnemonic: str) -> str:
    inverses = {
        "beq": "bne",
        "bne": "beq",
        "beqz": "bnez",
        "bnez": "beqz",
        "bgez": "bltz",
        "bgtz": "blez",
        "blez": "bgtz",
        "bltz": "bgez",
        "bc1t": "bc1f",
        "bc1f": "bc1t",
    }
    return inverses[mnemonic]


def normalize_gcc_likely_branches(function: Function, arch: ArchFlowGraph) -> Function:
    """GCC sometimes emits branch-likely instructions that cross just a single
    instruction:
    ```
    beqzl $a0, .label
     instr
    .label:
    ```
    This acts as a one-instruction if statement, that runs the instruction only if
    the branch is taken. Normalize this kind of branch-likely into
    ```
    bnez $a0, .label
     nop
    instr
    .label:
    ```
    to reduce the amount of branch likelies we have to deal with: they make control
    flow and block splitting more complex."""
    new_function = function.bodyless_copy()
    new_body = new_function.body
    for i, item in enumerate(function.body):
        if (
            isinstance(item, Instruction)
            and item.is_branch_likely
            and isinstance(item.jump_target, JumpTarget)
            and i + 2 < len(function.body)
            and isinstance(function.body[i + 1], Instruction)
            and function.body[i + 2] == Label(item.jump_target.target)
        ):
            mn_inverted = invert_branch_mnemonic(item.mnemonic[:-1])
            new_body.append(arch.parse(mn_inverted, item.args, item.meta.derived()))
            new_body.append(arch.parse("nop", [], item.meta.derived()))
        else:
            new_body.append(item)
    return new_function


def normalize_ido_likely_branches(function: Function, arch: ArchFlowGraph) -> Function:
    """Branch-likely instructions only evaluate their delay slots when they are
    taken, making control flow more complex. However, on the IDO compiler they
    only occur in a very specific pattern:

    ...
    <branch likely instr> .label
     X
    ...
    X
    .label:
    ...

    which this function transforms back into a regular branch pattern by moving
    the label one step back and replacing the delay slot by a nop.

    Branch-likely instructions that do not appear in this pattern are kept.

    We also do this for b instructions, which sometimes occur in the same pattern."""
    seen_instrs: Set[Instruction] = set()
    label_prev_instr: Dict[str, Optional[Instruction]] = {}
    label_before_instr: Dict[Instruction, str] = {}
    instr_before_instr: Dict[Instruction, Instruction] = {}
    prev_instr: Optional[Instruction] = None
    prev_label: Optional[Label] = None
    prev_item: Union[Instruction, Label, None] = None
    for item in function.body:
        if isinstance(item, Instruction):
            assert item not in seen_instrs
            seen_instrs.add(item)
            if prev_label is not None:
                label_before_instr[item] = prev_label.name
                prev_label = None
            if isinstance(prev_item, Instruction):
                instr_before_instr[item] = prev_item
            prev_instr = item
        elif isinstance(item, Label):
            label_prev_instr[item.name] = prev_instr
            prev_label = item
            prev_instr = None
        prev_item = item

    insert_label_before: Dict[Instruction, str] = {}
    new_body: List[Tuple[Union[Instruction, Label], Union[Instruction, Label]]] = []

    body_iter: Iterator[Union[Instruction, Label]] = iter(function.body)
    for item in body_iter:
        orig_item = item
        if isinstance(item, Instruction) and (
            item.is_branch_likely or item.mnemonic == "b"
        ):
            assert isinstance(item.jump_target, JumpTarget)
            old_label = item.jump_target.target
            if old_label not in label_prev_instr:
                raise DecompFailure(
                    f"Unable to parse branch: label {old_label} does not exist in function {function.name}"
                )
            before_target = label_prev_instr[old_label]
            before_before_target = (
                instr_before_instr.get(before_target)
                if before_target is not None
                else None
            )
            next_item = next(body_iter)
            orig_next_item = next_item
            if (
                item.mnemonic == "b"
                and before_before_target is not None
                and before_before_target.has_delay_slot
            ):
                # Don't treat 'b' instructions as branch likelies if doing so would
                # introduce a label in a delay slot.
                new_body.append((item, item))
                new_body.append((next_item, next_item))
            elif (
                isinstance(next_item, Instruction)
                and before_target is not None
                and before_target is not next_item
                and str(before_target) == str(next_item)
                and (item.mnemonic != "b" or next_item.mnemonic != "nop")
            ):
                # Handle the IDO pattern.
                if before_target not in label_before_instr:
                    new_label = f"_m2c_{old_label}_before"
                    label_before_instr[before_target] = new_label
                    insert_label_before[before_target] = new_label
                new_target = JumpTarget(label_before_instr[before_target])
                mn_unlikely = item.mnemonic[:-1] or "b"
                item = arch.parse(
                    mn_unlikely, item.args[:-1] + [new_target], item.meta.derived()
                )
                next_item = arch.parse("nop", [], item.meta.derived())
                new_body.append((orig_item, item))
                new_body.append((orig_next_item, next_item))
            else:
                # Fall back to not transforming the branch likely at all.
                new_body.append((item, item))
                new_body.append((next_item, next_item))
        else:
            new_body.append((orig_item, item))

    new_function = function.bodyless_copy()
    for (orig_item, new_item) in new_body:
        if isinstance(orig_item, Instruction) and orig_item in insert_label_before:
            new_function.new_label(insert_label_before[orig_item])
        new_function.body.append(new_item)

    return new_function


def prune_unreferenced_labels(function: Function, asm_data: AsmData) -> Function:
    labels_used: Set[str] = {
        label.name
        for label in function.body
        if isinstance(label, Label) and label.name in asm_data.mentioned_labels
    }
    for item in function.body:
        if isinstance(item, Instruction) and isinstance(item.jump_target, JumpTarget):
            labels_used.add(item.jump_target.target)

    new_function = function.bodyless_copy()
    for item in function.body:
        if not (isinstance(item, Label) and item.name not in labels_used):
            new_function.body.append(item)

    return new_function


def simplify_standard_patterns(function: Function, arch: ArchFlowGraph) -> Function:
    new_body = simplify_patterns(function.body, arch.asm_patterns, arch)
    new_function = function.bodyless_copy()
    new_function.body.extend(new_body)
    return new_function


def build_blocks(
    function: Function, asm_data: AsmData, arch: ArchFlowGraph, *, fragment: bool
) -> List[Block]:
    if arch.arch == Target.ArchEnum.MIPS:
        verify_no_trailing_delay_slot(function)
        function = prune_unreferenced_labels(function, asm_data)
        function = normalize_gcc_likely_branches(function, arch)
        function = normalize_ido_likely_branches(function, arch)

    function = prune_unreferenced_labels(function, asm_data)
    function = simplify_standard_patterns(function, arch)
    function = prune_unreferenced_labels(function, asm_data)

    block_builder = BlockBuilder()

    body_iter: Iterator[Union[Instruction, Label]] = iter(function.body)
    branch_likely_counts: Counter[str] = Counter()
    cond_return_target: Optional[JumpTarget] = None

    def process_mips(item: Union[Instruction, Label]) -> None:
        if isinstance(item, Label):
            # Split blocks at labels.
            block_builder.new_block()
            block_builder.set_label(item)
            return

        if not item.has_delay_slot:
            block_builder.add_instruction(item)
            assert not item.is_jump(), "all MIPS jumps have a delay slot"
            return

        process_after: List[Union[Instruction, Label]] = []
        next_item = next(body_iter)

        if isinstance(next_item, Label):
            # Delay slot is a jump target, so we need the delay slot
            # instruction to be in two blocks at once... In most cases,
            # we can just duplicate it. (This happens from time to time
            # in -O2-compiled code.)
            label = next_item
            next_item = next(body_iter)

            assert isinstance(next_item, Instruction), "Cannot have two labels in a row"

            if item.is_branch_likely or item.function_target is not None:
                # (we could handle these cases too with some care, they're just very
                # rare so we don't bother)
                msg = [
                    f"Label {label.name} refers to a delay slot; this is currently not supported.",
                    "Please modify the assembly to work around it (e.g. copy the instruction",
                    "to all jump sources and move the label, or add a nop to the delay slot).",
                ]
                if "_before" in label.name:
                    msg += [
                        "",
                        "This label was auto-generated as the target for a branch-likely",
                        "instruction (e.g. beql); you can also try to turn that into a non-likely",
                        "branch if that's equivalent in this context, i.e., if it's okay to",
                        "execute its delay slot unconditionally.",
                    ]
                raise DecompFailure("\n".join(msg))
            elif (
                all(x not in next_item.inputs for x in next_item.outputs)
                and not next_item.is_store
            ):
                # It should be okay to execute this instruction twice. This check isn't
                # technically required, but it avoids creating new blocks which could
                # throw if_statements off guard.
                process_after.append(label)
                process_after.append(next_item.clone())
            else:
                target = item.jump_target
                assert isinstance(target, JumpTarget), "has delay slot and isn't a call"
                temp_label = JumpTarget(f"_m2c_{label.name}_skip")
                meta = item.meta.derived()
                nop = arch.parse("nop", [], meta)
                block_builder.add_instruction(
                    arch.parse(item.mnemonic, item.args[:-1] + [temp_label], item.meta)
                )
                block_builder.add_instruction(nop)
                block_builder.new_block()
                block_builder.add_instruction(
                    arch.parse("b", [JumpTarget(label.name)], item.meta.derived())
                )
                block_builder.add_instruction(nop.clone())
                block_builder.new_block()
                block_builder.set_label(Label(temp_label.target))
                block_builder.add_instruction(
                    arch.parse("b", [target], item.meta.derived())
                )
                block_builder.add_instruction(next_item.clone())
                block_builder.new_block()
                block_builder.set_label(label)
                block_builder.add_instruction(next_item)
                return

        if next_item.has_delay_slot:
            raise DecompFailure(
                f"Two delay slot instructions in a row is not supported:\n{item}\n{next_item}"
            )

        if item.is_branch_likely:
            assert isinstance(item.jump_target, JumpTarget)
            target = item.jump_target
            branch_likely_counts[target.target] += 1
            index = branch_likely_counts[target.target]
            mn_inverted = invert_branch_mnemonic(item.mnemonic[:-1])
            temp_label = JumpTarget(f"_m2c_{target.target}_branchlikelyskip_{index}")
            branch_not = arch.parse(
                mn_inverted, item.args[:-1] + [temp_label], item.meta.derived()
            )
            nop = arch.parse("nop", [], item.meta.derived())
            block_builder.add_instruction(branch_not)
            block_builder.add_instruction(nop)
            block_builder.new_block()
            block_builder.add_instruction(next_item)
            block_builder.add_instruction(
                arch.parse("b", [target], item.meta.derived())
            )
            block_builder.add_instruction(nop.clone())
            block_builder.new_block()
            block_builder.set_label(Label(temp_label.target))
            block_builder.add_instruction(nop.clone())
        elif item.function_target is not None:
            # Move the delay slot instruction to before the call so it
            # passes correct arguments.
            if len(item.args) >= 2 and item.args[1] in next_item.outputs:
                raise DecompFailure(
                    f"Instruction after {item.mnemonic} clobbers its source\n"
                    "register, which is currently not supported.\n\n"
                    "Try rewriting the assembly to avoid that."
                )
            block_builder.add_instruction(next_item)
            block_builder.add_instruction(item)
        else:
            block_builder.add_instruction(item)
            block_builder.add_instruction(next_item)

        if item.is_jump():
            # Split blocks at jumps, after the next instruction.
            block_builder.new_block()

        for item in process_after:
            process_mips(item)

    def process_no_delay_slots(item: Union[Instruction, Label]) -> None:
        nonlocal cond_return_target

        if isinstance(item, Label):
            # Split blocks at labels.
            block_builder.new_block()
            block_builder.set_label(item)
            return

        if item.is_conditional and item.is_return:
            if cond_return_target is None:
                cond_return_target = JumpTarget("_m2c_conditionalreturn_")
            # Strip the "lr" off of the instruction
            assert item.mnemonic[-2:] == "lr"
            branch_instr = arch.parse(
                item.mnemonic[:-2], [cond_return_target], item.meta.derived()
            )
            block_builder.add_instruction(branch_instr)
            block_builder.new_block()
            return

        block_builder.add_instruction(item)

        # Split blocks at jumps, at the next instruction.
        if item.is_jump():
            block_builder.new_block()

    for item in body_iter:
        if arch.arch == Target.ArchEnum.MIPS:
            process_mips(item)
        else:
            process_no_delay_slots(item)

    if block_builder.is_empty():
        raise DecompFailure(
            f"Function {function.name} contains no instructions. Maybe it is rodata?"
        )

    if fragment:
        # If we're parsing an asm fragment instead of a full function,
        # then it does not need to end in a return or jump
        block_builder.new_block()
        return block_builder.get_blocks()

    # Add an extra return statement as a safeguard. We emit a warning later on if
    # this is reachable.
    for instr in arch.missing_return():
        block_builder.add_instruction(instr)
    emitted_block = block_builder.new_block()
    assert emitted_block is not None
    emitted_block.is_safeguard = True

    if cond_return_target is not None:
        # Add an empty return block at the end of the function
        block_builder.set_label(Label(cond_return_target.target))
        for instr in arch.missing_return():
            block_builder.add_instruction(instr)
        block_builder.new_block()

    return block_builder.get_blocks()


def verify_no_duplicate_instructions(blocks: List[Block]) -> None:
    # (The invariant that this checks isn't super important, but it seems like
    # a good footgun to avoid.)
    seen = set()
    for block in blocks:
        for instr in block.instructions:
            assert instr not in seen, "Instructions must be clone()ed if emitted twice"
            seen.add(instr)


# Split out dataclass from abc due to a mypy limitation:
# https://github.com/python/mypy/issues/5374
@dataclass(eq=False)
class _BaseNode:
    block: Block
    emit_goto: bool
    parents: List["Node"] = field(init=False, default_factory=list)
    dominators: Set["Node"] = field(init=False, default_factory=set)
    immediate_dominator: Optional["Node"] = field(init=False, default=None)
    immediately_dominates: List["Node"] = field(init=False, default_factory=list)
    postdominators: Set["Node"] = field(init=False, default_factory=set)
    immediate_postdominator: Optional["Node"] = field(init=False, default=None)
    immediately_postdominates: List["Node"] = field(init=False, default_factory=list)
    # This is only populated on the head node of the loop,
    # i.e. there is an invariant `(node.loop is None) or (node.loop.head is node)`
    loop: Optional["NaturalLoop"] = field(init=False, default=None)


class BaseNode(_BaseNode, abc.ABC):
    def name(self) -> str:
        return str(self.block.index)

    @abc.abstractmethod
    def children(self) -> List["Node"]:
        ...

    def __repr__(self) -> str:
        return f"<{self.__class__.__name__}: {self.name()}>"


@dataclass(eq=False, repr=False)
class BasicNode(BaseNode):
    successor: "Node"
    # Optional link to the TerminalNode, used to make infinite loops reducible.
    # Used by `compute_relations()`, but ignored when emitting code.
    fake_successor: Optional["TerminalNode"] = None

    def children(self) -> List["Node"]:
        # TODO: Should we also include the fallthrough node if `emit_goto` is True?
        if self.fake_successor is not None:
            return [self.successor, self.fake_successor]
        return [self.successor]

    def __str__(self) -> str:
        return "".join(
            [
                f"{self.block}\n",
                f"# {self.name()} -> {self.successor.name()}",
                " (loop)" if self.loop else "",
                " (goto)" if self.emit_goto else "",
            ]
        )


@dataclass(eq=False, repr=False)
class ConditionalNode(BaseNode):
    conditional_edge: "Node"
    fallthrough_edge: "Node"

    def children(self) -> List["Node"]:
        if self.conditional_edge == self.fallthrough_edge:
            return [self.conditional_edge]
        return [self.conditional_edge, self.fallthrough_edge]

    def __str__(self) -> str:
        return "".join(
            [
                f"{self.block}\n",
                f"# {self.name()} -> ",
                f"cond: {self.conditional_edge.name()}",
                " (loop)" if self.loop else "",
                ", ",
                f"def: {self.fallthrough_edge.name()}",
                " (goto)" if self.emit_goto else "",
            ]
        )


@dataclass(eq=False, repr=False)
class ReturnNode(BaseNode):
    index: int
    terminal: "TerminalNode"

    def children(self) -> List["Node"]:
        return [self.terminal]

    def name(self) -> str:
        name = super().name()
        return name if self.is_real() else f"{name}.{self.index}"

    def is_real(self) -> bool:
        return self.index == 0

    def __str__(self) -> str:
        return "".join(
            [
                f"{self.block}\n",
                f"# {self.name()} -> ret",
                " (goto)" if self.emit_goto else "",
            ]
        )


@dataclass(eq=False, repr=False)
class SwitchNode(BaseNode):
    cases: List["Node"]

    def children(self) -> List["Node"]:
        # Deduplicate nodes in `self.cases`
        seen = set()
        children = []
        for node in self.cases:
            if node not in seen:
                seen.add(node)
                children.append(node)
        return children

    def __str__(self) -> str:
        targets = ", ".join(c.name() for c in self.cases)
        return f"{self.block}\n# {self.name()} -> {targets}"


@dataclass(eq=False, repr=False)
class TerminalNode(BaseNode):
    """
    This is a fictive node that acts as a common postdominator for every node
    in the flowgraph. There should be exactly one TerminalNode per flowgraph.
    This is sometimes referred to as the "exit node", and having it makes it
    easier to perform interval/structural analysis on the flowgraph.
    This node has no `block_info` or contents: it has no corresponding assembly
    and emits no C code.
    """

    @staticmethod
    def terminal() -> "TerminalNode":
        return TerminalNode(Block(-1, None, "", []), False)

    def children(self) -> List["Node"]:
        return []

    def __str__(self) -> str:
        return "return"


Node = Union[BasicNode, ConditionalNode, ReturnNode, SwitchNode, TerminalNode]


@dataclass(eq=False)
class NaturalLoop:
    """
    Loops are defined by "backedges" `tail->head` where `head`
    dominates `tail` in the control flow graph.

    The loop body is the set of nodes dominated by `head` where there
    is a path from the node to `tail` that does not contain `head`.

    A loop can contain multiple backedges that all point to `head`
    Each backedge is represented by the source node.
    """

    head: Node
    nodes: Set[Node] = field(default_factory=set)
    backedges: Set[Node] = field(default_factory=set)


def build_graph_from_block(
    block: Block,
    blocks: List[Block],
    nodes: List[Node],
    asm_data: AsmData,
    arch: ArchFlowGraph,
) -> Node:
    # Don't reanalyze blocks.
    for node in nodes:
        if node.block == block:
            return node

    new_node: Node
    dummy_node: Any = None
    terminal_node = nodes[0]
    assert isinstance(
        terminal_node, TerminalNode
    ), "expected first node to be TerminalNode"

    def find_block_by_label(label: str) -> Optional[Block]:
        for block in blocks:
            if block.label and block.label.name == label:
                return block
        return None

    # Extract branching instructions from this block.
    jumps: List[Instruction] = [inst for inst in block.instructions if inst.is_jump()]
    assert len(jumps) in [0, 1], "too many jump instructions in one block"

    if len(jumps) == 0:
        # No jumps, i.e. the next block is this node's successor block.
        new_node = BasicNode(block, False, dummy_node)
        nodes.append(new_node)

        # Recursively analyze.
        next_block = blocks[block.index + 1]
        new_node.successor = build_graph_from_block(
            next_block, blocks, nodes, asm_data, arch
        )
    elif len(jumps) == 1:
        # There is a jump. This is either:
        # - a ReturnNode, if it's a return instruction ("jr $ra" in MIPS)
        # - a SwitchNode, if it's a jumptable instruction ("jr $something_else" in MIPS)
        # - a BasicNode, if it's an unconditional branch, or
        # - a ConditionalNode.
        jump = jumps[0]

        if jump.is_return:
            new_node = ReturnNode(block, False, index=0, terminal=terminal_node)
            nodes.append(new_node)
            return new_node

        if isinstance(jump.jump_target, Register):
            new_node = SwitchNode(block, False, [])
            nodes.append(new_node)

            jtbl_names = []
            for ins in block.instructions:
                for arg in ins.args:
                    if isinstance(arg, AsmAddressMode):
                        arg = arg.lhs
                    if (
                        isinstance(arg, Macro)
                        and arg.macro_name in ("lo", "l")
                        and isinstance(arg.argument, AsmGlobalSymbol)
                        and any(
                            arg.argument.symbol_name.startswith(prefix)
                            for prefix in ("jtbl", "jpt_", "lbl_")
                        )
                    ):
                        jtbl_names.append(arg.argument.symbol_name)
            if len(jtbl_names) != 1:
                raise DecompFailure(
                    f"Unable to determine jump table for {jump.mnemonic} instruction {jump.meta.loc_str()}.\n\n"
                    "There must be a read of a variable in the same block as\n"
                    'the instruction, which has a name starting with "jtbl"/"jpt_"/"lbl_".'
                )

            jtbl_name = jtbl_names[0]
            if jtbl_name not in asm_data.values:
                raise DecompFailure(
                    f"Found {jump.mnemonic} instruction {jump.meta.loc_str()}, but the "
                    "corresponding jump table is not provided.\n"
                    "\n"
                    "Please include it in the input .s file(s), or in an additional file.\n"
                    'It needs to be within a data section (e.g. ".section .rodata", or\n'
                    ".late_rodata/.data/.sdata/.sdata2).\n"
                )

            jtbl_value = asm_data.values[jtbl_name]
            jtbl_value.is_jtbl = True
            for entry in jtbl_value.data:
                if isinstance(entry, bytes):
                    # We have entered padding, stop reading.
                    break
                entry = entry.lstrip(".")
                case_block = find_block_by_label(entry)
                if case_block is None:
                    raise DecompFailure(f"Cannot find jtbl target {entry}")
                case_node = build_graph_from_block(
                    case_block, blocks, nodes, asm_data, arch
                )
                new_node.cases.append(case_node)
            return new_node

        # Get the block associated with the jump target.
        branch_label = jump.jump_target
        assert isinstance(branch_label, JumpTarget)

        branch_block = find_block_by_label(branch_label.target)
        if branch_block is None:
            target = branch_label.target
            raise DecompFailure(f"Cannot find branch target {target}")

        emit_goto = jump.meta.emit_goto
        if not jump.is_conditional:
            # A constant branch becomes a basic edge to our branch target.
            new_node = BasicNode(block, emit_goto, dummy_node)
            nodes.append(new_node)
            # Recursively analyze.
            new_node.successor = build_graph_from_block(
                branch_block, blocks, nodes, asm_data, arch
            )
        else:
            # A conditional branch means the fallthrough block is the next
            # block if the branch isn't.
            new_node = ConditionalNode(block, emit_goto, dummy_node, dummy_node)
            nodes.append(new_node)
            # Recursively analyze this too.
            next_block = blocks[block.index + 1]
            new_node.conditional_edge = build_graph_from_block(
                branch_block, blocks, nodes, asm_data, arch
            )
            new_node.fallthrough_edge = build_graph_from_block(
                next_block, blocks, nodes, asm_data, arch
            )
    return new_node


def is_trivial_return_block(block: Block, arch: ArchFlowGraph) -> bool:
    # A heuristic for when a block is a simple "early-return" block.
    # This could be improved.
    for instr in block.instructions:
        if instr.is_store or instr.function_target is not None:
            return False
        if any(reg in arch.all_return_regs for reg in instr.inputs + instr.outputs):
            return False
    return True


def reachable_without(start: Node, end: Node, without: Node) -> bool:
    """Return whether `end` is reachable from `start` with `without` removed."""
    reachable: Set[Node] = set()
    stack: List[Node] = [start]

    while stack:
        node = stack.pop()
        if node == without or node in reachable:
            continue
        reachable.add(node)
        stack.extend(node.children())

    return end in reachable


def build_nodes(
    function: Function,
    blocks: List[Block],
    asm_data: AsmData,
    arch: ArchFlowGraph,
    *,
    fragment: bool,
) -> List[Node]:
    terminal_node = TerminalNode.terminal()
    graph: List[Node] = [terminal_node]

    # Fragments do not need a ReturnNode, they can directly fall through to the TerminalNode
    if fragment:
        blocks.append(terminal_node.block)

    # Traverse through the block tree.
    entry_block = blocks[0]
    build_graph_from_block(entry_block, blocks, graph, asm_data, arch)

    # Give the TerminalNode a new index so that it sorts to the end of the list
    assert [n for n in graph if isinstance(n, TerminalNode)] == [terminal_node]
    terminal_node.block.index = max(n.block.index for n in graph) + 1

    # Sort the nodes by index.
    graph.sort(key=lambda node: node.block.index)
    return graph


def warn_on_safeguard_use(nodes: List[Node], arch: ArchFlowGraph) -> None:
    node = next((node for node in nodes if node.block.is_safeguard), None)
    if node:
        label = node.block.approx_label_name
        return_instrs = arch.missing_return()
        print(f'Warning: missing "{return_instrs[0]}" in last block (.{label}).\n')


def is_premature_return(
    node: Node, edge: Node, nodes: List[Node], arch: ArchFlowGraph
) -> bool:
    """Check whether a given edge in the flow graph is an early return."""
    if len(nodes) < 3:
        return False
    antepenultimate_node, final_return_node, terminal_node = nodes[-3:]
    assert isinstance(terminal_node, TerminalNode)
    if not isinstance(edge, ReturnNode) or edge != final_return_node:
        return False
    if not is_trivial_return_block(edge.block, arch):
        # Only trivial return blocks can be used for premature returns,
        # hopefully.
        return False
    if not isinstance(node, BasicNode):
        # We only treat BasicNode's as being able to return early right now.
        # (Handling ConditionalNode's seems to cause assertion failures --
        # might need changes to build_flowgraph_between.)
        return False
    # The only node that is allowed to point to the return node is the node
    # before it in the flow graph list. (You'd think it would be the node
    # with index = return_node.index - 1, but that's not necessarily the
    # case -- some functions have a dead antepenultimate block with a
    # superfluous unreachable return.)
    return node != antepenultimate_node


def duplicate_premature_returns(nodes: List[Node], arch: ArchFlowGraph) -> List[Node]:
    """For each jump to an early return node, create a duplicate return node
    for it to jump to. This ensures nice nesting for the if_statements code,
    and avoids a phi node for the return value."""
    extra_nodes: List[Node] = []
    index = 0
    for node in nodes:
        if (
            isinstance(node, BasicNode)
            and not node.emit_goto
            and is_premature_return(node, node.successor, nodes, arch)
        ):
            assert isinstance(node.successor, ReturnNode)
            index += 1
            n = ReturnNode(
                node.successor.block.clone(),
                False,
                index=index,
                terminal=node.successor.terminal,
            )
            node.successor = n
            extra_nodes.append(n)

    nodes += extra_nodes
    nodes.sort(key=lambda node: node.block.index)

    # Filter nodes to only include ones reachable from the entry node
    queue = {nodes[0]}
    # Always include the TerminalNode (even if it isn't reachable right now)
    reachable_nodes: Set[Node] = {n for n in nodes if isinstance(n, TerminalNode)}
    while queue:
        node = queue.pop()
        reachable_nodes.add(node)
        queue.update(set(node.children()) - reachable_nodes)
    return [n for n in nodes if n in reachable_nodes]


def compute_relations(nodes: List[Node]) -> None:
    """
    Compute dominators, postdominators, and backedges for the set of nodes.
    These are properties of control-flow graphs, for example see:
    https://en.wikipedia.org/wiki/Control-flow_graph
    https://www.cs.princeton.edu/courses/archive/spr04/cos598C/lectures/02-ControlFlow.pdf
    """
    # Calculate parents
    for node in nodes:
        node.parents = []
    for node in nodes:
        for child in node.children():
            child.parents.append(node)

    def compute_dominators(
        entry: Node,
        parents: Callable[[Node], List[Node]],
        dominators: Callable[[Node], Set[Node]],
        immediately_dominates: Callable[[Node], List[Node]],
        set_immediate_dominator: Callable[[Node, Optional[Node]], None],
    ) -> None:
        # See https://en.wikipedia.org/wiki/Dominator_(graph_theory)#Algorithms
        # Note: if `n` is unreachable from `entry`, then *every* node will
        # vacuously belong to `n`'s dominator set.
        for n in nodes:
            dominators(n).clear()
            if n == entry:
                dominators(n).add(n)
            else:
                dominators(n).update(nodes)

        changes = True
        while changes:
            changes = False
            for node in nodes:
                if node == entry:
                    continue
                nset = dominators(node)
                for parent in parents(node):
                    nset = nset.intersection(dominators(parent))
                nset.add(node)
                if len(nset) < len(dominators(node)):
                    assert nset.issubset(dominators(node))
                    dominators(node).intersection_update(nset)
                    changes = True

        # Compute immediate dominator, and the inverse relation
        for node in nodes:
            immediately_dominates(node).clear()
        for node in nodes:
            doms = dominators(node).difference({node})
            # If `node == entry` or the flow graph is not reducible, `doms` may be empty.
            # TODO: Infinite loops could be made reducible by introducing
            # branches like `if (false) { return; }` without breaking semantics
            if doms:
                # There should be a unique max `len(dominators(d))` if the flowgraph
                # is reducible. Fall back to largest index for irreducible graphs.
                imdom = max(doms, key=lambda d: (len(dominators(d)), d.block.index))
                immediately_dominates(imdom).append(node)
                set_immediate_dominator(node, imdom)
            else:
                set_immediate_dominator(node, None)
        for node in nodes:
            immediately_dominates(node).sort(key=lambda x: x.block.index)

    def _set_immediate_dominator(node: Node, imdom: Optional[Node]) -> None:
        node.immediate_dominator = imdom

    def _set_immediate_postdominator(node: Node, impdom: Optional[Node]) -> None:
        node.immediate_postdominator = impdom

    entry = nodes[0]
    terminal = nodes[-1]
    assert isinstance(terminal, TerminalNode)

    # Compute dominators & immediate dominators
    compute_dominators(
        entry=entry,
        parents=lambda n: n.parents,
        dominators=lambda n: n.dominators,
        immediately_dominates=lambda n: n.immediately_dominates,
        set_immediate_dominator=_set_immediate_dominator,
    )

    # Compute postdominators & immediate postdominators
    # This uses the same algorithm as above, but with edges reversed
    compute_dominators(
        entry=terminal,
        parents=lambda n: n.children(),
        dominators=lambda n: n.postdominators,
        immediately_dominates=lambda n: n.immediately_postdominates,
        set_immediate_dominator=_set_immediate_postdominator,
    )

    # Iterate over all edges n -> c and check for backedges, which define natural loops
    for node in nodes:
        for child in node.children():
            if child not in node.dominators:
                continue
            # Found a backedge node -> child where child dominates node; child is the "head" of the loop
            if child.loop is None:
                child.loop = NaturalLoop(child)
            child.loop.nodes |= {child, node}
            child.loop.backedges.add(node)
            for parent in nodes:
                if reachable_without(parent, node, child):
                    child.loop.nodes.add(parent)


def terminate_infinite_loops(nodes: List[Node]) -> None:
    terminal_node = nodes[-1]
    assert isinstance(terminal_node, TerminalNode)

    # Fixed-point iteration
    while True:
        # Find the set of nodes which are rechable from the TerminalNode, backwards
        seen = set()
        queue: Set[Node] = {terminal_node}
        while queue:
            n = queue.pop()
            seen.add(n)
            queue.update(set(n.parents) - seen)

        # Find the BasicNodes which cannot reach the TerminalNode
        # Although it's possible to design asm which has an infinite loop without
        # BasicNodes, it doesn't seem to happen in practice. Keeping these fixups
        # contained keeps the `build_flowgraph_between(...)` logic simpler.
        unterminated_nodes = [
            node for node in nodes if node not in seen and isinstance(node, BasicNode)
        ]
        if not unterminated_nodes:
            # Nothing left to do!
            return

        # Add a "fake" edge from the final BasicNode to the TerminalNode,
        # which is used by `compute_relations()` but is ignored in codegen.
        unterminated_nodes[-1].fake_successor = terminal_node
        compute_relations(nodes)


@dataclass
class RefSet:
    """A set of References, backed by a list to avoid non-determinism"""

    refs: List[Reference] = field(default_factory=list)

    @staticmethod
    def empty() -> "RefSet":
        """Represent a missing reference, such as an unset register"""
        return RefSet(refs=[])

    def is_empty(self) -> bool:
        return not self

    def get_unique(self) -> Optional[Reference]:
        if len(self.refs) == 1:
            return self.refs[0]
        return None

    def add(self, ref: Reference) -> None:
        if ref not in self.refs:
            self.refs.append(ref)

    def update(self, other: "RefSet") -> None:
        for ref in other.refs:
            self.add(ref)

    def remove(self, ref: Reference) -> None:
        self.refs.remove(ref)

    def copy(self) -> "RefSet":
        return RefSet(refs=self.refs.copy())

    def __contains__(self, ref: Reference) -> bool:
        return ref in self.refs

    def __iter__(self) -> Iterator[Reference]:
        return iter(self.refs)

    def __len__(self) -> int:
        return len(self.refs)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, RefSet):
            return NotImplemented
        return len(self) == len(other) and all(x in other for x in self)


@dataclass
class LocationRefSetDict:
    """
    A map from Locations to RefSets.
    If a key is missing, it is equivalent to mapping to an empty RefSet.
    """

    refs: Dict[Location, RefSet] = field(default_factory=dict)

    def get(self, loc: Location) -> RefSet:
        # Missing keys map to an empty RefSet
        return self.refs.get(loc, RefSet.empty())

    def add(self, loc: Location, ref: Reference) -> None:
        if loc not in self:
            self.refs[loc] = RefSet([ref])
        else:
            self.refs[loc].add(ref)

    def remove(self, loc: Location) -> None:
        self.refs.pop(loc, None)

    def copy(self) -> "LocationRefSetDict":
        return LocationRefSetDict(refs=self.refs.copy())

    def items(self) -> ItemsView[Location, RefSet]:
        return self.refs.items()

    def is_empty(self) -> bool:
        return all(not v for v in self.refs.values())

    def __contains__(self, key: Location) -> bool:
        return bool(self.get(key))

    def __setitem__(self, key: Location, value: RefSet) -> None:
        self.refs[key] = value


@dataclass(frozen=True)
class FlowGraph:
    nodes: List[Node]

    # For each Reference (typically an instruction), track the source References for
    # each of its input Locations (typically registers)
    instr_inputs: DefaultDict[Reference, LocationRefSetDict] = field(
        default_factory=lambda: defaultdict(LocationRefSetDict)
    )
    # The set of all downstream References whose inputs depend on outputs from other
    # References. This is the same information as `instr_inputs`, but reversed.
    instr_uses: DefaultDict[Reference, LocationRefSetDict] = field(
        default_factory=lambda: defaultdict(LocationRefSetDict)
    )

    def entry_node(self) -> Node:
        return self.nodes[0]

    def terminal_node(self) -> TerminalNode:
        node = self.nodes[-1]
        assert isinstance(node, TerminalNode)
        return node

    def is_reducible(self) -> bool:
        """
        A control flow graph is considered reducible or "well-structured" if:
        1. The edges can be partitioned into two disjoint sets: forward edges
          and back edges
        2. The forward edges form a DAG, with all nodes reachable from the entry
        3. For all back edges A -> B, B dominates A

        We already calculated back edges in `compute_relations`, so we need to
        check that the non-back edges satisfy #2.

        Most C code produces reducible graphs: to produce non-reducible graphs,
        the code either needs a `goto` or an infinite loop, which is rare in
        practice.

        Having a reducible control flow graphs allows us to perform interval analysis:
        we can examine a section of the graph bounded by entry & exit nodes, where
        the exit node postdominates the entry node. In a reducible graph, the backedges
        in loops are unambiguous.

        https://en.wikipedia.org/wiki/Control-flow_graph#Reducibility
        https://www.cs.princeton.edu/courses/archive/spr04/cos598C/lectures/02-ControlFlow.pdf
        https://www.cs.columbia.edu/~suman/secure_sw_devel/Basic_Program_Analysis_CF.pdf
        """

        # Kahn's Algorithm, with backedges excluded
        # https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm
        seen = set()
        queue = {self.entry_node()}
        incoming_edges: Dict[Node, Set[Node]] = {
            n: set(n.parents) - (n.loop.backedges if n.loop else set())
            for n in self.nodes
        }

        while queue:
            n = queue.pop()
            seen.add(n)
            for s in n.children():
                if s.loop is not None and n in s.loop.backedges:
                    continue
                incoming_edges[s].remove(n)
                if not incoming_edges[s]:
                    queue.add(s)

        if any(v for v in incoming_edges.values()):
            # There are remaining edges: the graph has at least one cycle
            return False
        if len(seen) != len(self.nodes):
            # Not all nodes are reachable from the entry node
            return False

        # Traverse the graph again, but starting at the terminal and following
        # all edges backwards, to ensure that it is possible to reach the exit
        # from every node. We don't need to look for loops this time.
        seen = set()
        queue = {self.terminal_node()}
        while queue:
            n = queue.pop()
            seen.add(n)
            queue.update(set(n.parents) - seen)

        if len(seen) != len(self.nodes):
            # Not all nodes can reach the terminal node
            return False
        return True

    def reset_block_info(self) -> None:
        for node in self.nodes:
            node.block.block_info = None

    def add_instruction_use(
        self, *, use: Reference, loc: Location, src: Reference
    ) -> None:
        """Update instr_inputs/instr_uses that `use` depends on `loc` from `src`"""
        self.instr_inputs[use].add(loc, src)
        self.instr_uses[src].add(loc, use)

    def clear_instruction_inputs(self, ref: Reference) -> None:
        """Remove all inputs for `ref` from instr_inputs/instr_uses"""
        for loc, uses in self.instr_inputs[ref].items():
            for use in uses:
                self.instr_uses[use].get(loc).remove(ref)
        self.instr_inputs.pop(ref)

    def validate_instruction_graph(self) -> None:
        """Verify that the instr_inputs & instr_uses dicts are consistent"""
        # Recompute instr_uses from instr_inputs as new_uses
        new_uses: DefaultDict[Reference, LocationRefSetDict] = defaultdict(
            LocationRefSetDict
        )
        for ref, inputs in self.instr_inputs.items():
            for reg, deps in inputs.items():
                for dep in deps:
                    new_uses[dep].add(reg, ref)

        # Assert that new_uses is equivalent to instr_uses
        for ref, uses in new_uses.items():
            for reg, deps in uses.items():
                assert deps == self.instr_uses[ref].get(reg)


def phi_loc_sources(node: Node, loc: Location, imdom_srcs: RefSet) -> RefSet:
    """
    Return the RefSet of all of the places `loc` is assigned to, if it is a valid phi.

    Otherwise, return an empty set. This analysis is accurate when `loc` is a Register,
    but is only best-effort for local variables: it will miss local array accesses and
    stack pointers passed to functions.
    """
    assert node.immediate_dominator is not None

    seen = set()
    stack = node.parents[:]
    sources = RefSet()

    while stack:
        n = stack.pop()
        if n in seen:
            continue
        seen.add(n)

        # As an optimization, we only need to iterate up until the immediate dominator,
        # because its phi sources have already been computed (`imdom_srcs`).
        if n == node.immediate_dominator:
            # If `loc` was unset on the path to `node` via its imdom, it's not a valid phi
            if not imdom_srcs:
                return RefSet.empty()

            sources.update(imdom_srcs)
            continue

        # Find the last instruction in the node that either writes or clobbers to `loc`
        for ref in n.block.instruction_refs[::-1]:
            if loc in ref.instruction.outputs:
                sources.add(ref)
                break
            if loc in ref.instruction.clobbers:
                return RefSet.empty()
        else:
            # This node didn't touch `loc`, so iterate by checking its parents.
            stack.extend(n.parents)

    return sources


def locs_clobbered_until_dominator(node: Node) -> Set[Location]:
    assert node.immediate_dominator is not None

    seen = {node.immediate_dominator}
    stack = node.parents[:]
    clobbered = set()
    while stack:
        n = stack.pop()
        if n in seen:
            continue
        seen.add(n)
        for instr in n.block.instructions:
            clobbered.update(instr.outputs)
            clobbered.update(instr.clobbers)
        stack.extend(n.parents)
    return clobbered


def nodes_to_flowgraph(
    nodes: List[Node],
    function: Function,
    arch: ArchFlowGraph,
    *,
    print_warnings: bool = False,
) -> FlowGraph:
    flow_graph = FlowGraph(nodes)
    missing_regs = []

    def process_node(node: Node, loc_srcs: LocationRefSetDict) -> None:
        def add_use_sources(*, use: Reference, input_loc: Location) -> RefSet:
            sources = loc_srcs.get(input_loc)
            for src in sources:
                flow_graph.add_instruction_use(use=use, loc=input_loc, src=src)
            return sources

        # Calculate register usage for each instruction in this node
        for ref in node.block.instruction_refs:
            ir = ref.instruction

            # Calculate the source of each location
            for inp in ir.inputs:
                sources = add_use_sources(use=ref, input_loc=inp)
                # Registers must be written to before being read.
                # Function calls are known to list all possible argument registers,
                # so they're a common false positive here.
                # Otherwise, this may indicate that the instruction's inputs were
                # incorrectly specified (or the instruction isn't fully implemented).
                if (
                    isinstance(inp, Register)
                    and sources.is_empty()
                    and (ir.function_target is None or inp not in arch.argument_regs)
                ):
                    missing_regs.append((inp, ref))

            # Remove any clobbered locations
            for clob in ir.clobbers + ir.outputs:
                if clob in loc_srcs:
                    loc_srcs.remove(clob)

            # Mark outputs as coming from this instruction
            for out in ir.outputs:
                loc_srcs.add(out, ref)

        # If this is a TerminalNode, it has no instructions; instead add dependencies
        # for the (potential) return registers of the function
        if isinstance(node, TerminalNode):
            assert not node.block.instruction_refs
            for reg in arch.all_return_regs:
                add_use_sources(use=EpilogueRef(reg), input_loc=reg)

        # Process everything dominated by this node, now that we know our own
        # register sources. This will eventually reach every node.
        for child in node.immediately_dominates:
            child_loc_srcs = loc_srcs.copy()

            for loc in locs_clobbered_until_dominator(child):
                phi_reg_srcs = phi_loc_sources(child, loc, loc_srcs.get(loc))
                if phi_reg_srcs:
                    # If phi_reg_srcs is non-empty, then loc is set in every control flow path
                    # to the child node (but it may have a phi value)
                    child_loc_srcs[loc] = phi_reg_srcs
                elif loc in child_loc_srcs:
                    # Otherwise, it's not always set, and cannot be used by the child node
                    child_loc_srcs.remove(loc)

            process_node(child, child_loc_srcs)

    # Set all the registers that are valid to access at the start of a function
    entry_reg_srcs = LocationRefSetDict()
    for r in arch.all_regs:
        entry_reg_srcs.refs[r] = RefSet(refs=[PrologueRef(r)])

    # Recursively traverse every node, starting with the entry node, populating instr_inputs
    entry_node = flow_graph.entry_node()
    process_node(entry_node, entry_reg_srcs)

    if print_warnings and missing_regs:
        print("/*")
        print(f"Warning: in {function.name}, regs were read before being written to:")
        for reg, ref in missing_regs:
            print(f"   {reg} at {ref}: {ref.instruction}")
        print("*/")

    return flow_graph


def build_flowgraph(
    function: Function,
    asm_data: AsmData,
    arch: ArchFlowGraph,
    *,
    fragment: bool,
    print_warnings: bool = False,
) -> FlowGraph:
    """
    Build the FlowGraph for the given Function.
    If `fragment` is True, do not treat the asm as a full function: this is used
    for analyzing IR patterns which do not need to be normalized in the same way.
    """
    blocks = build_blocks(function, asm_data, arch, fragment=fragment)
    verify_no_duplicate_instructions(blocks)

    nodes = build_nodes(function, blocks, asm_data, arch, fragment=fragment)
    warn_on_safeguard_use(nodes, arch)
    if not fragment:
        nodes = duplicate_premature_returns(nodes, arch)

    compute_relations(nodes)
    if not fragment:
        terminate_infinite_loops(nodes)

    flow_graph = nodes_to_flowgraph(
        nodes, function, arch, print_warnings=print_warnings or fragment
    )
    if not fragment:
        arch.simplify_ir(flow_graph)

    return flow_graph


def visualize_flowgraph(
    flow_graph: FlowGraph, viz_type: Options.VisualizeTypeEnum
) -> str:
    import graphviz as g

    fmt = Formatter(debug=True)
    dot = g.Digraph(
        node_attr={
            "shape": "rect",
            "fontname": "Monospace",
        },
        edge_attr={
            "fontname": "Monospace",
        },
    )

    for node in flow_graph.nodes:
        block_info: Optional[Any] = node.block.block_info
        asm_label = ""
        c_label = ""

        # In Graphviz, "\l" makes the preceeding text left-aligned, and inserts a newline
        if block_info:
            asm_label = "".join(
                f"{'*' if i.meta.synthetic else '&nbsp;'} {i}\l"
                for i in node.block.instructions
            )
            c_label = "".join(
                w.format(fmt) + "\l" for w in block_info.to_write if w.should_write()
            )

        dot.node(node.name())
        if isinstance(node, BasicNode):
            dot.edge(node.name(), node.successor.name(), color="black")
        elif isinstance(node, ConditionalNode):
            if block_info:
                c_label += f"if ({block_info.branch_condition.format(fmt)})\l"
            dot.edge(node.name(), node.fallthrough_edge.name(), label="F", color="blue")
            dot.edge(node.name(), node.conditional_edge.name(), label="T", color="red")
        elif isinstance(node, ReturnNode):
            if block_info and block_info.return_value:
                c_label += f"return ({block_info.return_value.format(fmt)});\l"
            else:
                c_label += "return;\l"
            dot.edge(node.name(), node.terminal.name())
        elif isinstance(node, SwitchNode):
            assert block_info is not None
            switch_control = block_info.switch_control
            c_label += f"switch ({switch_control.control_expr.format(fmt)})\l"
            for i, case in enumerate(node.cases):
                dot.edge(
                    node.name(),
                    case.name(),
                    label=str(i + switch_control.offset),
                    color="green",
                )
        else:
            assert isinstance(node, TerminalNode)
            asm_label += "// exit\l"
            c_label += "// exit\l"

        line_label = ""
        first_instr = next(node.block.instructions, None)
        if first_instr is not None and first_instr.meta.lineno > 0:
            line_label = f" (line {first_instr.meta.lineno})"

        label = f"// Node {node.name()}{line_label}\l"
        if viz_type == Options.VisualizeTypeEnum.ASM:
            label += asm_label
        elif viz_type == Options.VisualizeTypeEnum.C:
            label += c_label
        else:
            raise ValueError("Invalid viz_type: {viz_type!r}")

        dot.node(node.name(), label=label)
    svg_bytes: bytes = dot.pipe("svg")
    return svg_bytes.decode("utf-8", "replace")
