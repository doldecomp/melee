from dataclasses import replace
import typing
from typing import (
    Callable,
    ClassVar,
    Dict,
    List,
    Optional,
    Set,
    Tuple,
    Union,
)

from .error import DecompFailure
from .flow_graph import FlowGraph
from .ir_pattern import IrMatch, IrPattern
from .options import Target
from .asm_instruction import (
    Argument,
    AsmAddressMode,
    AsmGlobalSymbol,
    AsmInstruction,
    AsmLiteral,
    BinOp,
    JumpTarget,
    Macro,
    Register,
    get_jump_target,
)
from .instruction import (
    Instruction,
    InstructionMeta,
    Location,
    StackLocation,
)
from .asm_pattern import (
    AsmMatch,
    AsmMatcher,
    AsmPattern,
    Replacement,
    SimpleAsmPattern,
    make_pattern,
)
from .translate import (
    Abi,
    AbiArgSlot,
    AddressMode,
    Arch,
    BinaryOp,
    Cast,
    CmpInstrMap,
    CommentStmt,
    ErrorExpr,
    ExprStmt,
    Expression,
    InstrArgs,
    InstrMap,
    Literal,
    NodeState,
    SecondF64Half,
    StmtInstrMap,
    StoreInstrMap,
    TernaryOp,
    UnaryOp,
    as_f32,
    as_f64,
    as_int64,
    as_intish,
    as_intptr,
    as_ptr,
    as_sintish,
    as_type,
    as_u32,
    as_uintish,
)
from .evaluate import (
    add_imm,
    carry_add_to,
    carry_sub_from,
    error_stmt,
    fn_op,
    fold_divmod,
    fold_mul_chains,
    handle_add,
    handle_add_double,
    handle_add_float,
    handle_addi,
    handle_addis,
    handle_convert,
    handle_load,
    handle_loadx,
    handle_or,
    handle_rlwimi,
    handle_rlwinm,
    handle_sra,
    load_upper,
    make_store,
    make_storex,
    void_fn_op,
)
from .types import FunctionSignature, Type


class FcmpoCrorPattern(SimpleAsmPattern):
    """
    For floating point, `x <= y` and `x >= y` use `cror` to OR together the `cr0_eq`
    bit with either `cr0_lt` or `cr0_gt`. Instead of implementing `cror`, we detect
    this pattern and and directly compute the two registers.
    """

    pattern = make_pattern(
        "fcmpo $cr0, $x, $y",
        "cror 2, N, 2",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        fcmpo = m.body[0]
        assert isinstance(fcmpo, Instruction)
        if m.literals["N"] == 0:
            return Replacement(
                [AsmInstruction("fcmpo.lte.fictive", fcmpo.args)], len(m.body)
            )
        elif m.literals["N"] == 1:
            return Replacement(
                [AsmInstruction("fcmpo.gte.fictive", fcmpo.args)], len(m.body)
            )
        return None


class MfcrPattern(SimpleAsmPattern):
    """Comparison results extracted as ints."""

    pattern = make_pattern(
        "mfcr $x",
        "rlwinm $x, $x, N, 31, 31",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        x = m.regs["x"]
        if m.literals["N"] == 1:
            reg = Register("cr0_lt")
        elif m.literals["N"] == 2:
            reg = Register("cr0_gt")
        elif m.literals["N"] == 3:
            reg = Register("cr0_eq")
        elif m.literals["N"] == 4:
            reg = Register("cr0_so")
        else:
            return None
        return Replacement([AsmInstruction("move.fictive", [x, reg])], len(m.body))


class TailCallPattern(AsmPattern):
    """
    If a function ends in `return fn(...);` then the compiler may perform tail-call
    optimization. This is emitted as `b fn` instead of using `bl fn; blr`.
    """

    def match(self, matcher: AsmMatcher) -> Optional[Replacement]:
        if matcher.index != len(matcher.input) - 1:
            return None
        instr = matcher.input[matcher.index]
        if (
            isinstance(instr, Instruction)
            and instr.mnemonic == "b"
            and isinstance(instr.args[0], AsmGlobalSymbol)
        ):
            return Replacement(
                [
                    AsmInstruction("bl", instr.args),
                    AsmInstruction("blr", []),
                ],
                1,
            )
        return None


class SaveRestoreRegsFnPattern(SimpleAsmPattern):
    """Expand calls to MWCC's built-in `_{save,rest}{gpr,fpr}_` functions into
    register saves/restores."""

    pattern = make_pattern(
        "addi $r11, $r1, N",
        "bl",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        addend = m.literals["N"]
        bl = m.body[1]
        assert isinstance(bl, Instruction)
        assert isinstance(bl.args[0], AsmGlobalSymbol)
        parts = bl.args[0].symbol_name.split("_")
        if len(parts) != 3 or parts[0]:
            return None
        if parts[1] in ("savegpr", "restgpr"):
            mnemonic = "stw" if parts[1] == "savegpr" else "lwz"
            size = 4
            reg_prefix = "r"
        elif parts[1] in ("savefpr", "restfpr"):
            mnemonic = "stfd" if parts[1] == "savefpr" else "lfd"
            size = 8
            reg_prefix = "f"
        else:
            return None
        regnum = int(parts[2])
        new_instrs = []
        for i in range(regnum, 32):
            reg = Register(reg_prefix + str(i))
            stack_pos = AsmAddressMode(
                AsmLiteral(size * (i - 32) + addend), Register("r1")
            )
            new_instrs.append(AsmInstruction(mnemonic, [reg, stack_pos]))
        return Replacement(new_instrs, len(m.body))


class BoolCastPattern(SimpleAsmPattern):
    """Cast to bool (a 1 bit type in MWCC), which also can be emitted from `!!x`."""

    pattern = make_pattern(
        "neg $a, $x",
        "addic $r0, $a, -1",
        "subfe $r0, $r0, $a",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        boolcast = AsmInstruction("boolcast.fictive", [Register("r0"), m.regs["x"]])
        if m.regs["a"] == Register("r0"):
            return None
        elif m.regs["x"] == m.regs["a"]:
            return Replacement([boolcast, m.body[0]], len(m.body))
        else:
            return Replacement([m.body[0], boolcast], len(m.body))


class BranchCtrPattern(AsmPattern):
    """Split decrement-$ctr-and-branch instructions into a pair of instructions."""

    def match(self, matcher: AsmMatcher) -> Optional[Replacement]:
        instr = matcher.input[matcher.index]
        if isinstance(instr, Instruction) and instr.mnemonic in ("bdz", "bdnz"):
            ctr = Register("ctr")
            return Replacement(
                [
                    AsmInstruction("addi", [ctr, ctr, AsmLiteral(-1)]),
                    AsmInstruction(instr.mnemonic + ".fictive", instr.args),
                ],
                1,
            )
        return None


class FloatishToUintPattern(SimpleAsmPattern):
    pattern = make_pattern("bl __cvt_fp2unsigned")

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        return Replacement(
            [AsmInstruction("cvt.u.d.fictive", [Register("r3"), Register("f1")])],
            len(m.body),
        )


class FloatishToSintIrPattern(IrPattern):
    # This pattern handles converting either f32 or f64 into a signed int
    # The `fctiwz` instruction does all the work; this pattern is just to
    # elide the stack store/load pair.
    replacement = "fctiwz.fictive $i, $f"
    parts = [
        "fctiwz $t, $f",
        "stfd $t, (N-4)($r1)",
        "lwz $i, N($r1)",
    ]


class CheckConstantMixin:
    def check(self, m: IrMatch) -> bool:
        # TODO: Also validate that `K($k)` is the expected constant in rodata
        return m.symbolic_registers["k"] in (Register("r2"), Register("r13"))


class SintToDoubleIrPattern(IrPattern, CheckConstantMixin):
    # The replacement asm for these patterns reference the float constant `K($k)`
    # as an input, even though the value is ignored. This is needed to mark `$k`
    # as an input to the pattern for matching.
    replacement = "cvt.d.i.fictive $f, $i, K($k)"
    parts = [
        "lis $a, 0x4330",
        "stw $a, N($r1)",
        "xoris $b, $i, 0x8000",
        "stw $b, (N+4)($r1)",
        "lfd $d, N($r1)",
        "lfd $c, K($k)",
        "fsub $f, $d, $c",
    ]


class UintToDoubleIrPattern(IrPattern, CheckConstantMixin):
    replacement = "cvt.d.u.fictive $f, $i, K($k)"
    parts = [
        "lis $a, 0x4330",
        "stw $a, N($r1)",
        "stw $i, (N+4)($r1)",
        "lfd $d, N($r1)",
        "lfd $c, K($k)",
        "fsub $f, $d, $c",
    ]


class SintToFloatIrPattern(IrPattern, CheckConstantMixin):
    replacement = "cvt.s.i.fictive $f, $i, K($k)"
    parts = [
        "lis $a, 0x4330",
        "stw $a, N($r1)",
        "xoris $b, $i, 0x8000",
        "stw $b, (N+4)($r1)",
        "lfd $d, N($r1)",
        "lfd $c, K($k)",
        "fsubs $f, $d, $c",
    ]


class UintToFloatIrPattern(IrPattern, CheckConstantMixin):
    replacement = "cvt.s.u.fictive $f, $i, K($k)"
    parts = [
        "lis $a, 0x4330",
        "stw $a, N($r1)",
        "stw $i, (N+4)($r1)",
        "lfd $d, N($r1)",
        "lfd $c, K($k)",
        "fsubs $f, $d, $c",
    ]


class PpcArch(Arch):
    arch = Target.ArchEnum.PPC

    stack_pointer_reg = Register("r1")
    frame_pointer_reg = Register("r30")
    return_address_reg = Register("lr")

    base_return_regs = [Register(r) for r in ["r3", "f1"]]
    all_return_regs = [Register(r) for r in ["f1", "r3", "r4"]]
    argument_regs = [
        Register(r)
        for r in [
            "r3",
            "r4",
            "r5",
            "r6",
            "r7",
            "r8",
            "r9",
            "r10",
            "f1",
            "f2",
            "f3",
            "f4",
            "f5",
            "f6",
            "f7",
            "f8",
            "f9",
            "f10",
            "f11",
            "f12",
            "f13",
        ]
    ]
    simple_temp_regs = [Register(r) for r in ["r11", "r12"]]
    temp_regs = (
        argument_regs
        + simple_temp_regs
        + [
            Register(r)
            for r in [
                "r0",
                "f0",
                "cr0_gt",
                "cr0_lt",
                "cr0_eq",
                "cr0_so",
                "ctr",
            ]
        ]
    )
    saved_regs = [
        Register(r)
        for r in [
            # TODO: Some of the bits in CR are required to be saved (like cr2_gt)
            # When those bits are implemented, they should be added here
            "lr",
            # $r2 & $r13 are used for the small-data region, and are like $gp in MIPS
            "r2",
            "r13",
            "r14",
            "r15",
            "r16",
            "r17",
            "r18",
            "r19",
            "r20",
            "r21",
            "r22",
            "r23",
            "r24",
            "r25",
            "r26",
            "r27",
            "r28",
            "r29",
            "r30",
            "r31",
            "f14",
            "f15",
            "f16",
            "f17",
            "f18",
            "f19",
            "f20",
            "f21",
            "f22",
            "f23",
            "f24",
            "f25",
            "f26",
            "f27",
            "f28",
            "f29",
            "f30",
            "f31",
        ]
    ]
    all_regs = (
        saved_regs
        + temp_regs
        + [stack_pointer_reg]
        + [
            Register(r)
            for r in [
                # `zero` isn't a "real" PPC register; it's a normalized form of `r0`
                "zero",
                # TODO: These `crX` registers are only used to parse instructions, but
                # the instructions that use these registers aren't implemented yet.
                "cr0",
                "cr1",
                "cr2",
                "cr3",
                "cr4",
                "cr5",
                "cr6",
                "cr7",
            ]
        ]
    )

    aliased_regs: Dict[str, Register] = {}

    @classmethod
    def missing_return(cls) -> List[Instruction]:
        return [cls.parse("blr", [], InstructionMeta.missing())]

    # List of all instructions where `$r0` as certian args is interpreted as `0`
    # instead of the contents of `$r0`. The dict value represents the argument
    # index that is affected.
    INSTRS_R0_AS_ZERO: ClassVar[Dict[str, int]] = {
        "addi": 1,
        "addis": 1,
        "dcbf": 0,
        "dcbi": 0,
        "dcbst": 0,
        "dcbt": 0,
        "dcbtst": 0,
        "dcbz": 0,
        "dcbz_l": 0,
        "eciwx": 1,
        "ecowx": 1,
        "icbi": 0,
        "lbz": 1,
        "lbzx": 1,
        "lfd": 1,
        "lfdx": 1,
        "lfs": 1,
        "lfsx": 1,
        "lha": 1,
        "lhax": 1,
        "lhbrx": 1,
        "lhz": 1,
        "lhzx": 1,
        "lmw": 1,
        "lswi": 1,
        "lswx": 1,
        "lwarx": 1,
        "lwbrx": 1,
        "lwz": 1,
        "lwzx": 1,
        "psq_lx": 1,
        "psq_stx": 1,
        "stb": 1,
        "stbx": 1,
        "stfd": 1,
        "stfdx": 1,
        "stfiwx": 1,
        "stfs": 1,
        "stfsx": 1,
        "sth": 1,
        "sthbrx": 1,
        "sthx": 1,
        "stmw": 1,
        "stswi": 1,
        "stswx": 1,
        "stw": 1,
        "stwbrx": 1,
        "stwcx.": 1,
        "stwx": 1,
    }

    @classmethod
    def normalize_instruction(cls, instr: AsmInstruction) -> AsmInstruction:
        # Remove +/- suffix, which indicates branch-(un)likely and can be ignored
        if instr.mnemonic.startswith("b") and (
            instr.mnemonic.endswith("+") or instr.mnemonic.endswith("-")
        ):
            return PpcArch.normalize_instruction(
                AsmInstruction(instr.mnemonic[:-1], instr.args)
            )

        args = instr.args
        base_mnemonic = instr.mnemonic.rstrip(".")
        dot = instr.mnemonic[len(base_mnemonic) :]

        def sub(a: Argument, b: Argument) -> Argument:
            if isinstance(a, AsmLiteral) and isinstance(b, AsmLiteral):
                return AsmLiteral(a.value - b.value)
            else:
                return BinOp("-", a, b)

        def add(a: Argument, b: Argument) -> Argument:
            if isinstance(a, AsmLiteral) and isinstance(b, AsmLiteral):
                return AsmLiteral(a.value + b.value)
            else:
                return BinOp("+", a, b)

        def make_dotted(mn: str, args: List[Argument]) -> AsmInstruction:
            return AsmInstruction(mn + dot, args)

        lit = AsmLiteral

        r0_index = cls.INSTRS_R0_AS_ZERO.get(instr.mnemonic)
        if r0_index is not None and len(args) > r0_index:
            # If the argument at the given index is $r0, replace it with $zero
            r0_arg = args[r0_index]
            if r0_arg == Register("r0"):
                r0_arg = Register("zero")
            elif isinstance(r0_arg, AsmAddressMode) and r0_arg.rhs == Register("r0"):
                r0_arg = AsmAddressMode(lhs=r0_arg.lhs, rhs=Register("zero"))

            if r0_arg is not args[r0_index]:
                new_args = args[:]
                new_args[r0_index] = r0_arg
                return PpcArch.normalize_instruction(
                    AsmInstruction(instr.mnemonic, new_args)
                )
        if len(args) == 4:
            if base_mnemonic == "extlwi":
                return make_dotted(
                    "rlwinm", args[:2] + [args[3], lit(0), sub(args[2], lit(1))]
                )
            if base_mnemonic == "extrwi":
                return make_dotted(
                    "rlwinm",
                    args[:2] + [add(args[2], args[3]), sub(lit(32), args[2]), lit(31)],
                )
            if base_mnemonic == "rotlwi":
                return make_dotted("rlwinm", args[:2] + [args[2], lit(0), lit(31)])
            if base_mnemonic == "rotrwi":
                return make_dotted(
                    "rlwinm", args[:2] + [sub(lit(32), args[2]), lit(0), lit(31)]
                )
            if base_mnemonic == "clrlslwi":
                b = args[2]
                n = args[3]
                return make_dotted("rlwinm", args[:2] + [n, sub(b, n), sub(lit(31), n)])
        if len(args) == 3:
            if (
                instr.mnemonic == "addi"
                and isinstance(args[2], Macro)
                and args[1] in (Register("r2"), Register("r13"))
                and args[2].macro_name in ("sda2", "sda21")
            ):
                return AsmInstruction("li", [args[0], args[2].argument])
            if base_mnemonic == "slwi":
                return make_dotted(
                    "rlwinm", args[:2] + [args[2], lit(0), sub(lit(31), args[2])]
                )
            if base_mnemonic == "srwi":
                return make_dotted(
                    "rlwinm", args[:2] + [sub(lit(32), args[2]), args[2], lit(31)]
                )
            if base_mnemonic == "clrlwi":
                return make_dotted("rlwinm", args[:2] + [lit(0), args[2], lit(31)])
            if base_mnemonic == "clrrwi":
                return make_dotted(
                    "rlwinm", args[:2] + [lit(0), lit(0), sub(lit(31), args[2])]
                )
        if len(args) == 2:
            if instr.mnemonic == "lis" and isinstance(args[1], AsmLiteral):
                val = lit((args[1].value & 0xFFFF) << 16)
                return AsmInstruction("li", [args[0], val])
            if (
                instr.mnemonic == "lis"
                and isinstance(args[1], Macro)
                and args[1].macro_name == "ha"
                and isinstance(args[1].argument, AsmLiteral)
            ):
                # The @ha macro compensates for the sign bit of the corresponding @l
                value = args[1].argument.value
                if value & 0x8000:
                    value += 0x10000
                val = lit(value & 0xFFFF0000)
                return AsmInstruction("li", [args[0], val])
            if instr.mnemonic.startswith("cmp"):
                # For the two-argument form of cmpw, the insert an implicit CR0 as the first arg
                cr0: Argument = Register("cr0")
                return AsmInstruction(instr.mnemonic, [cr0] + instr.args)
        return instr

    @classmethod
    def parse(
        cls, mnemonic: str, args: List[Argument], meta: InstructionMeta
    ) -> Instruction:
        inputs: List[Location] = []
        clobbers: List[Location] = []
        outputs: List[Location] = []
        jump_target: Optional[Union[JumpTarget, Register]] = None
        function_target: Optional[Argument] = None
        is_conditional = False
        is_return = False
        is_store = False
        eval_fn: Optional[Callable[[NodeState, InstrArgs], object]] = None

        instr_str = str(AsmInstruction(mnemonic, args))

        cr0_bits: List[Location] = [
            Register("cr0_lt"),
            Register("cr0_gt"),
            Register("cr0_eq"),
            Register("cr0_so"),
        ]

        memory_sizes = {
            "b": 1,
            "h": 2,
            "w": 4,
            "fs": 4,
            "fd": 8,
        }
        psq_imms = 0
        size = memory_sizes.get(mnemonic.lstrip("stl").rstrip("azux"))
        if mnemonic.startswith("psq_l") or mnemonic.startswith("psq_st"):
            psq_imms = 2
            size = 8

        def make_memory_access(arg: Argument, size: int) -> List[Location]:
            assert size is not None
            if isinstance(arg, AsmAddressMode) and arg.rhs == cls.stack_pointer_reg:
                loc = StackLocation.from_offset(arg.lhs)
                if loc is None:
                    return []
                elif size == 8:
                    return [loc, replace(loc, offset=loc.offset + 4)]
                else:
                    assert size <= 4
                    return [loc]
            return []

        def unreachable_eval(s: NodeState, a: InstrArgs) -> None:
            raise DecompFailure(
                f"Instruction {instr_str} should be replaced before eval"
            )

        if mnemonic == "blr":
            # Return
            assert len(args) == 0
            inputs = [Register("lr")]
            is_return = True
        elif mnemonic in (
            "beqlr",
            "bgelr",
            "bgtlr",
            "blelr",
            "bltlr",
            "bnelr",
            "bnglr",
            "bnllr",
            "bnslr",
            "bsolr",
        ):
            # Conditional return
            # TODO: Support crN argument
            assert len(args) <= 1
            inputs = cr0_bits + [Register("lr")]
            is_return = True
            is_conditional = True
            # NB: These are rewritten to mnemonic[:-2] by build_blocks in flow_graph.py
            eval_fn = unreachable_eval
        elif mnemonic == "bctr":
            # Jump table (switch)
            assert len(args) == 0
            inputs = [Register("ctr")]
            jump_target = Register("ctr")
            is_conditional = True
            eval_fn = lambda s, a: s.set_switch_expr(a.regs[Register("ctr")])
        elif mnemonic == "bl":
            # Function call to label
            assert len(args) == 1
            inputs = list(cls.argument_regs)
            outputs = list(cls.all_return_regs)
            clobbers = list(cls.temp_regs)
            function_target = args[0]
            eval_fn = lambda s, a: s.make_function_call(a.sym_imm(0), outputs)
        elif mnemonic in ("bctrl", "blrl"):
            # Function call to pointer in special reg ($ctr or $lr)
            assert len(args) == 0
            reg = Register(mnemonic[1:-1])
            inputs = list(cls.argument_regs)
            inputs.append(reg)
            outputs = list(cls.all_return_regs)
            clobbers = list(cls.temp_regs)
            function_target = reg
            eval_fn = lambda s, a: s.make_function_call(a.regs[reg], outputs)
        elif mnemonic == "b":
            # Unconditional jump
            assert len(args) == 1
            jump_target = get_jump_target(args[0])
        elif mnemonic in cls.instrs_branches:
            # Normal branch
            # TODO: Support crN argument
            assert 1 <= len(args) <= 2
            # If the name starts with "!", negate the condition
            raw_name = cls.instrs_branches[mnemonic]
            negated = raw_name.startswith("!")
            reg_name = raw_name.lstrip("!")

            inputs = [Register(reg_name)]
            jump_target = get_jump_target(args[-1])
            is_conditional = True

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                cond = a.cmp_reg(reg_name)
                if negated:
                    cond = cond.negated()
                s.set_branch_condition(cond)

        elif mnemonic in cls.instrs_store:
            assert isinstance(args[0], Register) and size is not None
            is_store = True
            if mnemonic.endswith("x"):
                assert (
                    len(args) == 3 + psq_imms
                    and isinstance(args[1], Register)
                    and isinstance(args[2], Register)
                )
                inputs = [args[0], args[1], args[2]]
            else:
                assert len(args) == 2 + psq_imms and isinstance(args[1], AsmAddressMode)
                inputs = [args[0], args[1].rhs]
                outputs = make_memory_access(args[1], size)

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                store = cls.instrs_store[mnemonic](a)
                if store is not None:
                    s.store_memory(store, a.reg_ref(0))

        elif mnemonic in cls.instrs_store_update:
            assert isinstance(args[0], Register) and size is not None
            is_store = True
            if mnemonic.endswith("x"):
                assert (
                    len(args) == 3 + psq_imms
                    and isinstance(args[1], Register)
                    and isinstance(args[2], Register)
                )
                inputs = [args[0], args[1], args[2]]
                outputs = [args[1]]
            else:
                assert len(args) == 2 + psq_imms and isinstance(args[1], AsmAddressMode)
                inputs = [args[0], args[1].rhs]
                outputs = make_memory_access(args[1], size) + [args[1].rhs]

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                store = cls.instrs_store_update[mnemonic](a)

                # Update the register in the second argument
                update = a.memory_ref(1)
                if not isinstance(update, AddressMode):
                    raise DecompFailure(
                        f"Unhandled store-and-update arg in {instr_str}: {update!r}"
                    )
                s.set_reg(
                    update.rhs,
                    add_imm(update.rhs, a.regs[update.rhs], Literal(update.offset), a),
                )

                if store is not None:
                    s.store_memory(store, a.reg_ref(0))

        elif mnemonic in cls.instrs_load:
            assert isinstance(args[0], Register) and size is not None
            if mnemonic.endswith("x"):
                assert (
                    len(args) == 3 + psq_imms
                    and isinstance(args[1], Register)
                    and isinstance(args[2], Register)
                )
                inputs = [args[1], args[2]]
            else:
                assert len(args) == 2 + psq_imms
                if isinstance(args[1], AsmAddressMode):
                    inputs = make_memory_access(args[1], size) + [args[1].rhs]
            outputs = [args[0]]
            eval_fn = lambda s, a: s.set_reg(a.reg_ref(0), cls.instrs_load[mnemonic](a))
        elif mnemonic in cls.instrs_load_update:
            assert isinstance(args[0], Register) and size is not None
            if mnemonic.endswith("x"):
                assert (
                    len(args) == 3 + psq_imms
                    and isinstance(args[1], Register)
                    and isinstance(args[2], Register)
                )
                inputs = [args[1], args[2]]
                outputs = [args[0], args[1]]

                def eval_fn(s: NodeState, a: InstrArgs) -> None:
                    target = a.reg_ref(0)
                    val = cls.instrs_load_update[mnemonic](a)
                    s.set_reg(target, val)
                    # In `rD, rA, rB`, update `rA = rA + rB`
                    update_reg = a.reg_ref(1)
                    offset = a.reg(2)
                    if update_reg == target:
                        raise DecompFailure(
                            f"Invalid instruction, rA and rD must be different in {instr_str}"
                        )
                    s.set_reg(
                        update_reg, add_imm(update_reg, a.regs[update_reg], offset, a)
                    )

            else:
                assert len(args) == 2 + psq_imms and isinstance(args[1], AsmAddressMode)
                inputs = make_memory_access(args[1], size) + [args[1].rhs]
                outputs = [args[0], args[1].rhs]

                def eval_fn(s: NodeState, a: InstrArgs) -> None:
                    target = a.reg_ref(0)
                    val = cls.instrs_load_update[mnemonic](a)
                    s.set_reg(target, val)
                    # In `rD, rA(N)`, update `rA = rA + N`
                    update = a.memory_ref(1)
                    if not isinstance(update, AddressMode):
                        raise DecompFailure(
                            f"Unhandled load-and-update arg in {instr_str}: {update!r}"
                        )
                    update_reg = update.rhs
                    offset = Literal(update.offset)
                    if update_reg == target:
                        raise DecompFailure(
                            f"Invalid instruction, rA and rD must be different in {instr_str}"
                        )
                    s.set_reg(
                        update_reg, add_imm(update_reg, a.regs[update_reg], offset, a)
                    )

        elif mnemonic in ("stmw", "lmw"):
            assert (
                len(args) == 2
                and isinstance(args[0], Register)
                and isinstance(args[1], AsmAddressMode)
                and args[0].register_name[0] == "r"
            )
            is_store = mnemonic == "stmw"
            index = int(args[0].register_name[1:])
            offset = args[1].lhs_as_literal()
            while index <= 31:
                reg = Register(f"r{index}")
                mem = make_memory_access(
                    AsmAddressMode(rhs=args[1].rhs, lhs=AsmLiteral(offset)), 4
                )
                if mnemonic == "stmw":
                    inputs.append(reg)
                    outputs.extend(mem)
                else:
                    outputs.append(reg)
                    inputs.extend(mem)
                index += 1
                offset += 4
            inputs.append(args[1].rhs)
            # TODO: These are only supported in function prologues/epilogues
            eval_fn = None
        elif mnemonic in cls.instrs_no_dest:
            assert not any(isinstance(a, (Register, AsmAddressMode)) for a in args)
            eval_fn = lambda s, a: s.write_statement(cls.instrs_no_dest[mnemonic](a))
        elif mnemonic.rstrip(".") in cls.instrs_destination_first:
            assert isinstance(args[0], Register)
            outputs = [args[0]]
            if mnemonic == "mflr":
                assert len(args) == 1
                inputs = [Register("lr")]
            elif mnemonic == "mfctr":
                assert len(args) == 1
                inputs = [Register("ctr")]
            elif mnemonic.rstrip(".") == "rlwimi":
                assert (
                    len(args) == 5
                    and isinstance(args[1], Register)
                    and not isinstance(args[2], (Register, AsmAddressMode))
                    and not isinstance(args[3], (Register, AsmAddressMode))
                    and not isinstance(args[4], (Register, AsmAddressMode))
                )
                inputs = [args[0], args[1]]
            elif mnemonic.startswith("cvt."):
                assert isinstance(args[1], Register)
                if len(args) == 2:
                    inputs = [args[1]]
                else:
                    assert isinstance(args[2], AsmAddressMode)
                    size = 8
                    inputs = make_memory_access(args[2], size) + [args[1], args[2].rhs]
            else:
                assert not any(isinstance(a, AsmAddressMode) for a in args)
                inputs = [r for r in args[1:] if isinstance(r, Register)]
            if mnemonic.endswith("."):
                # Instructions ending in `.` update the condition reg
                outputs.extend(cr0_bits)

                def eval_fn(s: NodeState, a: InstrArgs) -> None:
                    target = a.reg_ref(0)
                    val = cls.instrs_destination_first[mnemonic.rstrip(".")](a)
                    target_val = s.set_reg(target, val)
                    if target_val is None:
                        target_val = val
                    s.set_reg(
                        Register("cr0_eq"),
                        BinaryOp.icmp(
                            target_val, "==", Literal(0, type=target_val.type)
                        ),
                    )
                    # Use manual casts for cr0_gt/cr0_lt so that the type of target_val is not modified
                    # until the resulting bit is .use()'d.
                    target_s32 = Cast(
                        target_val, reinterpret=True, silent=True, type=Type.s32()
                    )
                    s.set_reg(
                        Register("cr0_gt"),
                        BinaryOp(target_s32, ">", Literal(0), type=Type.s32()),
                    )
                    s.set_reg(
                        Register("cr0_lt"),
                        BinaryOp(target_s32, "<", Literal(0), type=Type.s32()),
                    )
                    s.set_reg(
                        Register("cr0_so"),
                        fn_op("MIPS2C_OVERFLOW", [target_val], type=Type.s32()),
                    )

            else:
                eval_fn = lambda s, a: s.set_reg(
                    a.reg_ref(0), cls.instrs_destination_first[mnemonic](a)
                )
        elif mnemonic in ("mtctr", "mtlr"):
            assert len(args) == 1 and isinstance(args[0], Register)
            dest_reg = Register(mnemonic[2:])
            inputs = [args[0]]
            outputs = [dest_reg]
            eval_fn = lambda s, a: s.set_reg(dest_reg, a.reg(0))
        elif mnemonic in cls.instrs_ppc_compare:
            assert len(args) == 3 and isinstance(args[1], Register)
            inputs = [r for r in args[1:] if isinstance(r, Register)]
            outputs = list(cr0_bits)

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                base_reg = a.reg_ref(0)
                if base_reg != Register("cr0"):
                    error = f'"{instr_str}" is not supported, the first arg is not $cr0'
                    s.write_statement(error_stmt(error))
                    return

                s.set_reg(Register("cr0_eq"), cls.instrs_ppc_compare[mnemonic](a, "=="))
                s.set_reg(Register("cr0_gt"), cls.instrs_ppc_compare[mnemonic](a, ">"))
                s.set_reg(Register("cr0_lt"), cls.instrs_ppc_compare[mnemonic](a, "<"))
                s.set_reg(Register("cr0_so"), Literal(0))

        elif mnemonic in cls.instrs_ignore:
            pass
        else:
            # If the mnemonic is unsupported, guess if it is destination-first
            if args and isinstance(args[0], Register):
                inputs = [r for r in args[1:] if isinstance(r, Register)]
                outputs = [args[0]]
                maybe_dest_first = True
            else:
                maybe_dest_first = False

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                error = ErrorExpr(f"unknown instruction: {instr_str}")
                if mnemonic.endswith("."):
                    # Unimplemented instructions that modify CR0
                    s.set_reg(Register("cr0_eq"), error)
                    s.set_reg(Register("cr0_gt"), error)
                    s.set_reg(Register("cr0_lt"), error)
                    s.set_reg(Register("cr0_so"), error)
                if maybe_dest_first:
                    s.set_reg_real(a.reg_ref(0), error, emit_exactly_once=True)
                else:
                    s.write_statement(ExprStmt(error))

        return Instruction(
            mnemonic=mnemonic,
            args=args,
            meta=meta,
            inputs=inputs,
            clobbers=clobbers,
            outputs=outputs,
            jump_target=jump_target,
            function_target=function_target,
            is_conditional=is_conditional,
            is_return=is_return,
            is_store=is_store,
            eval_fn=eval_fn,
        )

    ir_patterns = [
        FloatishToSintIrPattern(),
        SintToDoubleIrPattern(),
        UintToDoubleIrPattern(),
        SintToFloatIrPattern(),
        UintToFloatIrPattern(),
    ]

    asm_patterns = [
        FcmpoCrorPattern(),
        MfcrPattern(),
        TailCallPattern(),
        SaveRestoreRegsFnPattern(),
        BoolCastPattern(),
        BranchCtrPattern(),
        FloatishToUintPattern(),
    ]

    instrs_ignore: Set[str] = {
        "nop",
        "b",
        # Assume stmw/lmw are only used for saving/restoring saved regs
        "stmw",
        "lmw",
        # `{crclr,crset} 6` are used as part of the ABI for floats & varargs
        # For now, we can ignore them (and later use them to help in function_abi)
        "crclr",
        "crset",
    }

    instrs_store: StoreInstrMap = {
        "stb": lambda a: make_store(a, type=Type.int_of_size(8)),
        "sth": lambda a: make_store(a, type=Type.int_of_size(16)),
        "stw": lambda a: make_store(a, type=Type.reg32(likely_float=False)),
        "stbx": lambda a: make_storex(a, type=Type.int_of_size(8)),
        "sthx": lambda a: make_storex(a, type=Type.int_of_size(16)),
        "stwx": lambda a: make_storex(a, type=Type.reg32(likely_float=False)),
        # TODO: Do we need to model the truncation from f64 to f32 here?
        "stfs": lambda a: make_store(a, type=Type.f32()),
        "stfd": lambda a: make_store(a, type=Type.f64()),
        "stfsx": lambda a: make_storex(a, type=Type.f32()),
        "stfdx": lambda a: make_storex(a, type=Type.f64()),
        "psq_st": lambda a: None,
    }
    instrs_store_update: StoreInstrMap = {
        "stbu": lambda a: make_store(a, type=Type.int_of_size(8)),
        "sthu": lambda a: make_store(a, type=Type.int_of_size(16)),
        "stwu": lambda a: make_store(a, type=Type.reg32(likely_float=False)),
        "stbux": lambda a: make_storex(a, type=Type.int_of_size(8)),
        "sthux": lambda a: make_storex(a, type=Type.int_of_size(16)),
        "stwux": lambda a: make_storex(a, type=Type.reg32(likely_float=False)),
        "stfsu": lambda a: make_store(a, type=Type.f32()),
        "stfdu": lambda a: make_store(a, type=Type.f64()),
        "stfsux": lambda a: make_storex(a, type=Type.f32()),
        "stfdux": lambda a: make_storex(a, type=Type.f64()),
    }
    instrs_load: InstrMap = {
        "lba": lambda a: handle_load(a, type=Type.s8()),
        "lbz": lambda a: handle_load(a, type=Type.u8()),
        "lha": lambda a: handle_load(a, type=Type.s16()),
        "lhz": lambda a: handle_load(a, type=Type.u16()),
        "lwz": lambda a: handle_load(a, type=Type.reg32(likely_float=False)),
        "lbax": lambda a: handle_loadx(a, type=Type.s8()),
        "lbzx": lambda a: handle_loadx(a, type=Type.u8()),
        "lhax": lambda a: handle_loadx(a, type=Type.s16()),
        "lhzx": lambda a: handle_loadx(a, type=Type.u16()),
        "lwzx": lambda a: handle_loadx(a, type=Type.reg32(likely_float=False)),
        # TODO: Do we need to model the promotion from f32 to f64 here?
        "lfs": lambda a: handle_load(a, type=Type.f32()),
        "lfd": lambda a: handle_load(a, type=Type.f64()),
        "lfsx": lambda a: handle_loadx(a, type=Type.f32()),
        "lfdx": lambda a: handle_loadx(a, type=Type.f64()),
        "psq_l": lambda a: ErrorExpr("psq_l unimplemented"),
    }
    instrs_load_update: InstrMap = {
        "lbau": lambda a: handle_load(a, type=Type.s8()),
        "lbzu": lambda a: handle_load(a, type=Type.u8()),
        "lhau": lambda a: handle_load(a, type=Type.s16()),
        "lhzu": lambda a: handle_load(a, type=Type.u16()),
        "lwzu": lambda a: handle_load(a, type=Type.reg32(likely_float=False)),
        "lbaux": lambda a: handle_loadx(a, type=Type.s8()),
        "lbzux": lambda a: handle_loadx(a, type=Type.u8()),
        "lhaux": lambda a: handle_loadx(a, type=Type.s16()),
        "lhzux": lambda a: handle_loadx(a, type=Type.u16()),
        "lwzux": lambda a: handle_loadx(a, type=Type.reg32(likely_float=False)),
        "lfsu": lambda a: handle_load(a, type=Type.f32()),
        "lfdu": lambda a: handle_load(a, type=Type.f64()),
        "lfsux": lambda a: handle_loadx(a, type=Type.f32()),
        "lfdux": lambda a: handle_loadx(a, type=Type.f64()),
    }

    instrs_branches: Dict[str, str] = {
        # Branch instructions/pseudoinstructions
        # Technically `bge` is defined as `cr0_gt || cr0_eq`; not as `!cr0_lt`
        # This assumption may not hold if the bits are modified with instructions like
        # `crand` which modify individual bits in CR.
        # The `!` indicates that the condition in the register is negated
        "beq": "cr0_eq",
        "bge": "!cr0_lt",
        "bgt": "cr0_gt",
        "ble": "!cr0_gt",
        "blt": "cr0_lt",
        "bne": "!cr0_eq",
        "bns": "!cr0_so",
        "bso": "cr0_so",
        "bdnz": "ctr",
        "bdz": "!ctr",
        "bdnz.fictive": "ctr",
        "bdz.fictive": "!ctr",
    }
    instrs_no_dest: StmtInstrMap = {
        "sync": lambda a: void_fn_op("M2C_SYNC", []),
        "isync": lambda a: void_fn_op("M2C_SYNC", []),
    }

    instrs_dest_first_non_load: InstrMap = {
        # Integer arithmetic
        # TODO: Read XER_CA in extended instrs, instead of using CarryBit
        "add": lambda a: handle_add(a),
        "addc": lambda a: handle_add(a),
        "adde": lambda a: carry_add_to(handle_add(a)),
        "addze": lambda a: carry_add_to(a.reg(1)),
        "addi": lambda a: handle_addi(a),
        "addic": lambda a: handle_addi(a),
        "addis": lambda a: handle_addis(a),
        "subf": lambda a: fold_divmod(
            BinaryOp.intptr(left=a.reg(2), op="-", right=a.reg(1))
        ),
        "subfc": lambda a: fold_divmod(
            BinaryOp.intptr(left=a.reg(2), op="-", right=a.reg(1))
        ),
        "subfe": lambda a: carry_sub_from(
            fold_divmod(BinaryOp.intptr(left=a.reg(2), op="-", right=a.reg(1)))
        ),
        "subfic": lambda a: fold_divmod(
            BinaryOp.intptr(left=a.imm(2), op="-", right=a.reg(1))
        ),
        "subfze": lambda a: carry_sub_from(
            fold_mul_chains(UnaryOp.sint("-", a.reg(1))),
        ),
        "neg": lambda a: fold_mul_chains(UnaryOp.sint("-", a.reg(1))),
        "divw": lambda a: BinaryOp.sint(a.reg(1), "/", a.reg(2)),
        "divwu": lambda a: BinaryOp.uint(a.reg(1), "/", a.reg(2)),
        "mulli": lambda a: BinaryOp.int(a.reg(1), "*", a.imm(2)),
        "mullw": lambda a: BinaryOp.int(a.reg(1), "*", a.reg(2)),
        "mulhw": lambda a: fold_divmod(BinaryOp.int(a.reg(1), "MULT_HI", a.reg(2))),
        "mulhwu": lambda a: fold_divmod(BinaryOp.int(a.reg(1), "MULTU_HI", a.reg(2))),
        # Bit arithmetic
        "or": lambda a: handle_or(a.reg(1), a.reg(2)),
        "ori": lambda a: handle_or(a.reg(1), a.unsigned_imm(2)),
        "oris": lambda a: handle_or(a.reg(1), a.shifted_imm(2)),
        "and": lambda a: BinaryOp.int(left=a.reg(1), op="&", right=a.reg(2)),
        "andc": lambda a: BinaryOp.int(
            left=a.reg(1), op="&", right=UnaryOp("~", a.reg(2), type=Type.intish())
        ),
        "not": lambda a: UnaryOp("~", a.reg(1), type=Type.intish()),
        "nor": lambda a: UnaryOp(
            "~", BinaryOp.int(left=a.reg(1), op="|", right=a.reg(2)), type=Type.intish()
        ),
        "xor": lambda a: BinaryOp.int(left=a.reg(1), op="^", right=a.reg(2)),
        "eqv": lambda a: UnaryOp(
            "~", BinaryOp.int(left=a.reg(1), op="^", right=a.reg(2)), type=Type.intish()
        ),
        "andi": lambda a: BinaryOp.int(left=a.reg(1), op="&", right=a.unsigned_imm(2)),
        "andis": lambda a: BinaryOp.int(left=a.reg(1), op="&", right=a.shifted_imm(2)),
        "xori": lambda a: BinaryOp.int(left=a.reg(1), op="^", right=a.unsigned_imm(2)),
        "xoris": lambda a: BinaryOp.int(left=a.reg(1), op="^", right=a.shifted_imm(2)),
        "boolcast.fictive": lambda a: UnaryOp(
            op="!!", expr=a.reg(1), type=Type.intish()
        ),
        "rlwimi": lambda a: handle_rlwimi(
            a.reg(0), a.reg(1), a.imm_value(2), a.imm_value(3), a.imm_value(4)
        ),
        "rlwinm": lambda a: handle_rlwinm(
            a.reg(1), a.imm_value(2), a.imm_value(3), a.imm_value(4)
        ),
        "slw": lambda a: fold_mul_chains(
            BinaryOp.int(left=a.reg(1), op="<<", right=as_intish(a.reg(2)))
        ),
        "srw": lambda a: fold_divmod(
            BinaryOp(
                left=as_uintish(a.reg(1)),
                op=">>",
                right=as_intish(a.reg(2)),
                type=Type.u32(),
            )
        ),
        "sraw": lambda a: fold_divmod(
            BinaryOp(
                left=as_sintish(a.reg(1)),
                op=">>",
                right=as_intish(a.reg(2)),
                type=Type.s32(),
            )
        ),
        "srawi": lambda a: handle_sra(a),
        "extsb": lambda a: handle_convert(a.reg(1), Type.s8(), Type.intish()),
        "extsh": lambda a: handle_convert(a.reg(1), Type.s16(), Type.intish()),
        "cntlzw": lambda a: UnaryOp(op="CLZ", expr=a.reg(1), type=Type.intish()),
        # Load Immediate
        "li": lambda a: a.full_imm(1),
        "lis": lambda a: load_upper(a),
        # Move from Special Register
        "mflr": lambda a: a.regs[Register("lr")],
        "mfctr": lambda a: a.regs[Register("ctr")],
        # Move pseudoinstructions
        "mr": lambda a: a.reg(1),
        "move.fictive": lambda a: a.reg(1),
        # Floating Point Arithmetic
        "fadd": lambda a: handle_add_double(a),
        "fadds": lambda a: handle_add_float(a),
        "fdiv": lambda a: BinaryOp.f64(a.reg(1), "/", a.reg(2)),
        "fdivs": lambda a: BinaryOp.f32(a.reg(1), "/", a.reg(2)),
        "fmul": lambda a: BinaryOp.f64(a.reg(1), "*", a.reg(2)),
        "fmuls": lambda a: BinaryOp.f32(a.reg(1), "*", a.reg(2)),
        "fsub": lambda a: BinaryOp.f64(a.reg(1), "-", a.reg(2)),
        "fsubs": lambda a: BinaryOp.f32(a.reg(1), "-", a.reg(2)),
        "fneg": lambda a: UnaryOp(op="-", expr=a.reg(1), type=Type.floatish()),
        "fmr": lambda a: a.reg(1),
        "frsp": lambda a: handle_convert(a.reg(1), Type.f32(), Type.f64()),
        "fctiwz": lambda a: handle_convert(a.reg(1), Type.sintish(), Type.floatish()),
        "fctiwz.fictive": lambda a: handle_convert(
            a.reg(1), Type.sintish(), Type.floatish()
        ),
        "cvt.u.d.fictive": lambda a: handle_convert(
            a.reg(1), Type.uintish(), Type.floatish()
        ),
        "cvt.d.i.fictive": lambda a: handle_convert(
            a.reg(1), Type.f64(), Type.sintish()
        ),
        "cvt.d.u.fictive": lambda a: handle_convert(
            a.reg(1), Type.f64(), Type.uintish()
        ),
        "cvt.s.i.fictive": lambda a: handle_convert(
            a.reg(1), Type.f32(), Type.sintish()
        ),
        "cvt.s.u.fictive": lambda a: handle_convert(
            a.reg(1), Type.f32(), Type.uintish()
        ),
        # Floating Poing Fused Multiply-{Add,Sub}
        "fmadd": lambda a: BinaryOp.f64(
            BinaryOp.f64(a.reg(1), "*", a.reg(2)), "+", a.reg(3)
        ),
        "fmadds": lambda a: BinaryOp.f32(
            BinaryOp.f32(a.reg(1), "*", a.reg(2)), "+", a.reg(3)
        ),
        "fnmadd": lambda a: UnaryOp(
            op="-",
            expr=BinaryOp.f64(BinaryOp.f64(a.reg(1), "*", a.reg(2)), "+", a.reg(3)),
            type=Type.f64(),
        ),
        "fnmadds": lambda a: UnaryOp(
            op="-",
            expr=BinaryOp.f32(BinaryOp.f32(a.reg(1), "*", a.reg(2)), "+", a.reg(3)),
            type=Type.f32(),
        ),
        "fmsub": lambda a: BinaryOp.f64(
            BinaryOp.f64(a.reg(1), "*", a.reg(2)), "-", a.reg(3)
        ),
        "fmsubs": lambda a: BinaryOp.f32(
            BinaryOp.f32(a.reg(1), "*", a.reg(2)), "-", a.reg(3)
        ),
        "fnmsub": lambda a: UnaryOp(
            op="-",
            expr=BinaryOp.f64(BinaryOp.f64(a.reg(1), "*", a.reg(2)), "-", a.reg(3)),
            type=Type.f64(),
        ),
        "fnmsubs": lambda a: UnaryOp(
            op="-",
            expr=BinaryOp.f32(BinaryOp.f32(a.reg(1), "*", a.reg(2)), "-", a.reg(3)),
            type=Type.f32(),
        ),
        # TODO: Detect if we should use fabs or fabsf
        "fabs": lambda a: fn_op("fabs", [a.reg(1)], Type.floatish()),
        "fres": lambda a: fn_op("__fres", [a.reg(1)], Type.floatish()),
        "frsqrte": lambda a: fn_op("__frsqrte", [a.reg(1)], Type.floatish()),
        "fsel": lambda a: TernaryOp(
            cond=BinaryOp.fcmp(a.reg(1), ">=", Literal(0)),
            left=a.reg(2),
            right=a.reg(3),
            type=Type.floatish(),
        ),
    }
    instrs_destination_first: InstrMap = {
        **instrs_dest_first_non_load,
        **instrs_load,
    }

    instrs_ppc_compare: Dict[str, Callable[[InstrArgs, str], Expression]] = {
        # Integer (signed/unsigned)
        "cmpw": lambda a, op: BinaryOp.sintptr_cmp(a.reg(1), op, a.reg(2)),
        "cmpwi": lambda a, op: BinaryOp.sintptr_cmp(a.reg(1), op, a.imm(2)),
        "cmplw": lambda a, op: BinaryOp.uintptr_cmp(a.reg(1), op, a.reg(2)),
        "cmplwi": lambda a, op: BinaryOp.uintptr_cmp(a.reg(1), op, a.imm(2)),
        # Floating point
        # TODO: There is a difference in how these two instructions handle NaN
        "fcmpo": lambda a, op: BinaryOp.fcmp(a.reg(1), op, a.reg(2)),
        "fcmpu": lambda a, op: BinaryOp.fcmp(a.reg(1), op, a.reg(2)),
        "fcmpo.lte.fictive": lambda a, op: BinaryOp.fcmp(
            a.reg(1), op if op != "==" else "<=", a.reg(2)
        ),
        "fcmpo.gte.fictive": lambda a, op: BinaryOp.fcmp(
            a.reg(1), op if op != "==" else ">=", a.reg(2)
        ),
    }

    @staticmethod
    def function_abi(
        fn_sig: FunctionSignature,
        likely_regs: Dict[Register, bool],
        *,
        for_call: bool,
    ) -> Abi:
        known_slots: List[AbiArgSlot] = []
        candidate_slots: List[AbiArgSlot] = []

        # $rX & $fX regs can be interspersed in function args, unlike in the MIPS O32 ABI
        intptr_regs = [r for r in PpcArch.argument_regs if r.register_name[0] != "f"]
        float_regs = [r for r in PpcArch.argument_regs if r.register_name[0] == "f"]

        if fn_sig.params_known:
            for ind, param in enumerate(fn_sig.params):
                # TODO: Support passing parameters on the stack
                param_type = param.type.decay()
                reg: Optional[Register]
                try:
                    if param_type.is_float():
                        reg = float_regs.pop(0)
                    else:
                        reg = intptr_regs.pop(0)
                except IndexError:
                    # Stack variable
                    reg = None
                known_slots.append(
                    AbiArgSlot(
                        offset=4 * ind, reg=reg, name=param.name, type=param_type
                    )
                )
            if fn_sig.is_variadic:
                # TODO: Find a better value to use for `offset`?
                for reg in intptr_regs:
                    candidate_slots.append(
                        AbiArgSlot(
                            offset=4 * len(known_slots), reg=reg, type=Type.intptr()
                        )
                    )
                for reg in float_regs:
                    candidate_slots.append(
                        AbiArgSlot(
                            offset=4 * len(known_slots), reg=reg, type=Type.floatish()
                        )
                    )
        else:
            for ind, reg in enumerate(PpcArch.argument_regs):
                if reg.register_name[0] != "f":
                    candidate_slots.append(
                        AbiArgSlot(offset=4 * ind, reg=reg, type=Type.intptr())
                    )
                else:
                    candidate_slots.append(
                        AbiArgSlot(offset=4 * ind, reg=reg, type=Type.floatish())
                    )

        valid_extra_regs: Set[Register] = {
            slot.reg for slot in known_slots if slot.reg is not None
        }
        possible_slots: List[AbiArgSlot] = []
        for slot in candidate_slots:
            if slot.reg is None or slot.reg not in likely_regs:
                continue

            # Don't pass this register if lower numbered ones are undefined.
            if slot == candidate_slots[0]:
                # For varargs, a subset of regs may be used. Don't check
                # earlier registers for the first member of that subset.
                pass
            else:
                # Only r3-r10/f1-f13 can be used for arguments
                regname = slot.reg.register_name
                prev_reg = Register(f"{regname[0]}{int(regname[1:])-1}")
                if (
                    prev_reg in PpcArch.argument_regs
                    and prev_reg not in valid_extra_regs
                ):
                    continue

            valid_extra_regs.add(slot.reg)

            # Skip registers that are untouched from the initial parameter
            # list. This is sometimes wrong (can give both false positives
            # and negatives), but having a heuristic here is unavoidable
            # without access to function signatures, or when dealing with
            # varargs functions. Decompiling multiple functions at once
            # would help.
            # TODO: don't do this in the middle of the argument list
            if not likely_regs[slot.reg]:
                continue

            possible_slots.append(slot)

        return Abi(
            arg_slots=known_slots,
            possible_slots=possible_slots,
        )

    @staticmethod
    def function_return(expr: Expression) -> Dict[Register, Expression]:
        return {
            Register("f1"): Cast(
                expr, reinterpret=True, silent=True, type=Type.floatish()
            ),
            Register("r3"): Cast(
                expr, reinterpret=True, silent=True, type=Type.intptr()
            ),
            Register("r4"): as_u32(
                Cast(expr, reinterpret=True, silent=False, type=Type.u64())
            ),
        }
