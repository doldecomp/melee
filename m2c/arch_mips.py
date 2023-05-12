from dataclasses import replace
from typing import (
    Callable,
    Dict,
    List,
    Optional,
    Set,
    Tuple,
    Union,
)

from .error import DecompFailure
from .options import Target
from .asm_file import Label
from .asm_instruction import (
    Argument,
    AsmAddressMode,
    AsmInstruction,
    AsmLiteral,
    JumpTarget,
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
    Pattern,
    Replacement,
    SimpleAsmPattern,
    make_pattern,
)
from .translate import (
    Abi,
    AbiArgSlot,
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
    UnaryOp,
    as_f32,
    as_f64,
    as_intish,
    as_s64,
    as_sintish,
    as_u32,
    as_u64,
    as_uintish,
)
from .evaluate import (
    condition_from_expr,
    error_stmt,
    fn_op,
    fold_divmod,
    fold_mul_chains,
    handle_add,
    handle_add_double,
    handle_add_float,
    handle_add_real,
    handle_addi,
    handle_bgez,
    handle_conditional_move,
    handle_convert,
    handle_la,
    handle_lw,
    handle_load,
    handle_lwl,
    handle_lwr,
    handle_or,
    handle_sltiu,
    handle_sltu,
    handle_sra,
    handle_swl,
    handle_swr,
    imm_add_32,
    load_upper,
    make_store,
    void_fn_op,
)
from .types import FunctionSignature, Type


LENGTH_TWO: Set[str] = {
    "neg",
    "negu",
    "not",
    "neg.s",
    "abs.s",
    "sqrt.s",
    "neg.d",
    "abs.d",
    "sqrt.d",
}

LENGTH_THREE: Set[str] = {
    "slt",
    "slti",
    "sltu",
    "sltiu",
    "add",
    "addi",
    "addiu",
    "addu",
    "sub",
    "subu",
    "daddi",
    "daddiu",
    "dsubu",
    "add.s",
    "sub.s",
    "div.s",
    "mul.s",
    "add.d",
    "sub.d",
    "div.d",
    "mul.d",
    "ori",
    "and",
    "or",
    "nor",
    "xor",
    "andi",
    "xori",
    "sll",
    "sllv",
    "srl",
    "srlv",
    "sra",
    "srav",
    "dsll",
    "dsll32",
    "dsllv",
    "dsrl",
    "dsrl32",
    "dsrlv",
    "dsra",
    "dsra32",
    "dsrav",
    "div",
    "divu",
    "ddiv",
    "ddivu",
}


class DivPattern(SimpleAsmPattern):
    pattern = make_pattern(
        "bnez $q, .A",
        "*",  # nop or div
        "break",
        ".A:",
        "li $at, -1",
        "bne $q, $at, .B",
        "li $at, 0x80000000",
        "bne $p, $at, .B",
        "nop",
        "break",
        ".B:",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        return Replacement([m.body[1]], len(m.body) - 1)


class DivuPattern(SimpleAsmPattern):
    pattern = make_pattern(
        "bnez $q, .A",
        "nop",
        "break",
        ".A:",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        return Replacement([], len(m.body) - 1)


class ModP2Pattern1(SimpleAsmPattern):
    """Modulo by power of two."""

    pattern = make_pattern(
        "bgez $i, .A",
        "andi $o, $i, N",
        "beqz $o, .A",
        "nop",
        "addiu $o, $o, (-1 - N)",
        ".A:",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        val = (m.literals["N"] & 0xFFFF) + 1
        if val & (val - 1):
            return None  # not a power of two
        mod = AsmInstruction("mod.fictive", [m.regs["o"], m.regs["i"], AsmLiteral(val)])
        return Replacement([mod], len(m.body) - 1)


class ModP2Pattern2(SimpleAsmPattern):
    """Modulo by power of two where the mask is too big to fit an andi."""

    pattern = make_pattern(
        "li $at, HI",
        "addiu $at, $at, LO?",
        "bgez $i, .A",
        "and $o, $i, $at",
        "beqz $o, .A",
        "addiu $at, $at, 1",
        "subu $o, $o, $at",
        ".A:",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        val = (m.literals["HI"] & 0xFFFFFFFF) + 1
        if "LO" in m.literals:
            val += ((m.literals["LO"] + 0x8000) & 0xFFFF) - 0x8000
        if not val or val & (val - 1):
            return None  # not a power of two
        mod = AsmInstruction(
            "mod.fictive",
            [m.regs["o"], m.regs["i"], AsmLiteral(val)],
        )
        return Replacement([mod], len(m.body) - 1)


class DivP2Pattern1(SimpleAsmPattern):
    """Division by power of two where input reg != output reg."""

    pattern = make_pattern(
        "bgez $i, .A",
        "sra $o, $i, N",
        "addiu $at, $i, ((1 << N) - 1)",
        "sra $o, $at, N",
        ".A:",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        shift = m.literals["N"] & 0x1F
        div = AsmInstruction(
            "div.fictive", [m.regs["o"], m.regs["i"], AsmLiteral(2**shift)]
        )
        return Replacement([div], len(m.body) - 1)


class DivP2Pattern2(SimpleAsmPattern):
    """Division by power of two where input reg = output reg."""

    pattern = make_pattern(
        "bgez $x, .A",
        "move $at, $x",
        "addiu $at, $x, M",
        ".A:",
        "sra $x, $at, N",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        shift = m.literals["N"] & 0x1F
        div = AsmInstruction(
            "div.fictive", [m.regs["x"], m.regs["x"], AsmLiteral(2**shift)]
        )
        return Replacement([div], len(m.body))


class Div2S16Pattern(SimpleAsmPattern):
    pattern = make_pattern(
        "sll $i, $i, N",
        "sra $o, $i, N",
        "srl $i, $i, 0x1f",
        "addu $o, $o, $i",
        "sra $o, $o, 1",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        # Keep 32->16 conversion from $i to $o, just add a division
        div = AsmInstruction("div.fictive", [m.regs["o"], m.regs["o"], AsmLiteral(2)])
        return Replacement([m.body[0], m.body[1], div], len(m.body))


class Div2S32Pattern1(SimpleAsmPattern):
    pattern = make_pattern(
        "srl $t, $i, 0x1f",
        "addu $t, $i, $t",
        "sra $o, $t, 1",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        if m.regs["t"] == m.regs["i"]:
            return None
        div = AsmInstruction("div.fictive", [m.regs["o"], m.regs["i"], AsmLiteral(2)])
        # While it would be more correct, we don't include m.body[:2] in the
        # result, because the srl incorrectly type inferences $i to u32.
        return Replacement([div], len(m.body))


class Div2S32Pattern2(SimpleAsmPattern):
    pattern = make_pattern(
        "srl $t, $i, 0x1f",
        "addu $i, $i, $t",
        "sra $o, $i, 1",
    )

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        if m.regs["t"] == m.regs["i"]:
            return None
        div = AsmInstruction("div.fictive", [m.regs["o"], m.regs["i"], AsmLiteral(2)])
        return Replacement([div], len(m.body))


class UtfPattern(SimpleAsmPattern):
    pattern = make_pattern(
        "bgez $x, .A",
        "cvt.s.w $o, $i",
        "li $at, 0x4f800000",
        "mtc1",
        "nop",
        "add.s",
        ".A:",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        new_instr = AsmInstruction("cvt.s.u.fictive", [m.regs["o"], m.regs["i"]])
        return Replacement([new_instr], len(m.body) - 1)


class FtuPattern(SimpleAsmPattern):
    pattern = make_pattern(
        "cfc1 $o, $31",  # use out register as scratch
        "nop",
        "andi",
        "andi?",  # (skippable)
        "*",  # bnez or bneql
        "*",
        "li?",
        "mtc1",
        "mtc1?",
        "li",
        "*",  # sub.fmt *, X, *
        "ctc1",
        "nop",
        "*",  # cvt.w.fmt *, *
        "cfc1",
        "nop",
        "andi",
        "andi?",
        "bnez",
        "nop",
        "mfc1",
        "li",
        "b",
        "or",
        ".A:",
        "b",
        "li",
        "*",  # label: (moved one step down if bneql)
        "*",  # mfc1
        "nop",
        "bltz",
        "nop",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        sub = next(
            x
            for x in m.body
            if isinstance(x, Instruction) and x.mnemonic.startswith("sub")
        )
        fmt = sub.mnemonic.split(".")[-1]
        args = [m.regs["o"], sub.args[1]]
        if fmt == "s":
            new_instr = AsmInstruction("cvt.u.s.fictive", args)
        else:
            new_instr = AsmInstruction("cvt.u.d.fictive", args)
        return Replacement([new_instr], len(m.body))


class Mips1DoubleLoadStorePattern(AsmPattern):
    lwc_pattern = make_pattern("lwc1", "lwc1")
    swc_pattern = make_pattern("swc1", "swc1")

    def match(self, matcher: AsmMatcher) -> Optional[Replacement]:
        # TODO: sometimes the instructions aren't consecutive.
        m = matcher.try_match(self.lwc_pattern) or matcher.try_match(self.swc_pattern)
        if not m:
            return None
        a, b = m.body
        assert isinstance(a, Instruction)
        assert isinstance(b, Instruction)
        ra, ma = a.args
        rb, mb = b.args
        # Ideally we'd verify that the memory locations are consecutive as well,
        # but that's a bit annoying with %lo macros vs raw offsets, and they
        # might also be misidentified as separate globals.
        if not (
            isinstance(ra, Register)
            and ra.is_float()
            and ra.other_f64_reg() == rb
            and isinstance(ma, AsmAddressMode)
            and isinstance(mb, AsmAddressMode)
            and ma.rhs == mb.rhs
        ):
            return None
        num = int(ra.register_name[1:])
        if num % 2 == 1:
            ra, rb = rb, ra
            ma, mb = mb, ma
        # Store the even-numbered register (ra) into the low address (mb).
        new_args = [ra, mb]
        new_mn = "ldc1" if a.mnemonic == "lwc1" else "sdc1"
        new_instr = AsmInstruction(new_mn, new_args)
        return Replacement([new_instr], len(m.body))


class GccSqrtPattern(SimpleAsmPattern):
    pattern = make_pattern(
        "sqrt.s $o, $i",
        "c.eq.s",
        "nop",
        "bc1t",
        "*",
        "jal sqrtf",
        "nop",
        "mov.s $o, $f0?",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        return Replacement([m.body[0], m.body[4]], len(m.body))


class TrapuvPattern(SimpleAsmPattern):
    pattern = make_pattern(
        "li $x, 0xfffa0000",
        "move $y, $sp",
        "addiu $sp, $sp, N",
        "ori $x, $x, 0x5a5a",
        ".loop:",
        "addiu $y, $y, -8",
        "sw $x, ($y)",
        "bne $y, $sp, .loop",
        "sw $x, 4($y)",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        new_instr = AsmInstruction("trapuv.fictive", [])
        return Replacement([m.body[2], new_instr], len(m.body))


class SetGpPattern(AsmPattern):
    """Strip PIC .cpload pattern at the top of functions."""

    pattern = make_pattern(
        "*",
        "addiu $gp, $gp, _",
        "addu $gp, $gp, $t9",
    )

    def match(self, matcher: AsmMatcher) -> Optional[Replacement]:
        if matcher.index != 0:
            return None
        m = matcher.try_match(self.pattern)
        if m is None:
            return None
        nop = AsmInstruction("nop", [])
        return Replacement([nop], len(m.body))


class MemcpyPatternBase(AsmPattern):
    """IDO unrolled memcpy, used e.g. for struct copies. Slightly different patterns
    are used for -mips1 vs -mips2, and for >=4 vs <4 byte alignment."""

    pattern_mips1: Pattern
    pattern_mips2: Pattern
    epilogue1: Pattern
    epilogue2: Pattern
    instruction_name: str

    def match(self, matcher: AsmMatcher) -> Optional[Replacement]:
        for pattern in (self.pattern_mips1, self.pattern_mips2):
            m = matcher.try_match(pattern)
            if m:
                break
        else:
            return None

        # Find length by searching backwards for an "addiu $e, $x, ..." where
        # $x = $i or there's a "move $i, $x".
        length: Optional[int] = None
        e_src: Optional[Instruction] = None
        i_src: Optional[Instruction] = None
        for i in range(matcher.index - 1, -1, -1):
            item = matcher.input[i]
            if isinstance(item, Label):
                break
            if not i_src and m.regs["i"] in item.outputs:
                i_src = item
            if not e_src and m.regs["e"] in item.outputs:
                e_src = item
        if e_src is None or e_src.mnemonic != "addiu":
            return None
        if e_src.args[1] != m.regs["i"] and (
            i_src is None or i_src.mnemonic != "move" or i_src.args[1] != e_src.args[1]
        ):
            return None
        assert isinstance(e_src.args[2], AsmLiteral)
        length = e_src.args[2].value

        # Extend the pattern to include additional bytes copied when the total size
        # isn't a multiple of three. (This doesn't really work well at the moment,
        # see the comment in AlignedMemcpyPattern...)
        added_length = length
        m2 = matcher.try_match(pattern + self.epilogue1)
        if m2:
            m = m2
            length += 4
            m3 = matcher.try_match(pattern + self.epilogue1 + self.epilogue2)
            if m3:
                m = m3
                length += 4

        from_reg = Register("from")
        to_reg = Register("to")
        from_offset = AsmLiteral(m.literals["N"])
        to_offset = AsmLiteral(m.literals["M"])
        added_len_arg = AsmLiteral(added_length)
        len_arg = AsmLiteral(length)
        return Replacement(
            [
                m.body[0],
                AsmInstruction("addiu", [from_reg, m.regs["i"], from_offset]),
                AsmInstruction("addiu", [to_reg, m.regs["o"], to_offset]),
                AsmInstruction(self.instruction_name, [to_reg, from_reg, len_arg]),
                AsmInstruction("addiu", [m.regs["o"], m.regs["o"], added_len_arg]),
                AsmInstruction("addiu", [m.regs["i"], m.regs["i"], added_len_arg]),
            ]
            + list(m.wildcard_items)
            + [AsmInstruction("nop", [])],
            len(m.body),
        )


class AlignedMemcpyPattern(MemcpyPatternBase):
    pattern_mips1 = make_pattern(
        ".loop:",
        "lw $a, N($i)",
        "addiu $i, $i, 12",
        "sw $a, M($o)",
        "lw $b, (N-8)($i)",
        "addiu $o, $o, 12",
        "sw $b, (M-8)($o)",
        "lw $c, (N-4)($i)",
        "bne $i, $e, .loop",
        "sw $c, (M-4)($o)",
    )
    pattern_mips2 = make_pattern(
        ".loop:",
        "lw $a, N($i)",
        "addiu $i, $i, 12",
        "addiu $o, $o, 12",
        "sw $a, MM($o)",
        ".eq M, MM+12",
        "lw $b, (N-8)($i)",
        "sw $b, (M-8)($o)",
        "lw $c, (N-4)($i)",
        "bne $i, $e, .loop",
        "sw $c, (M-4)($o)",
    )
    # TODO: the * should not be there on -mips2, and the very last instruction can be
    # reordered to be further down. (Luckily the effects of failing to capture this is
    # just an extra word copy after the memcpy.)
    epilogue1 = make_pattern(
        "lw $x, N($i)",
        "*",
        "sw $x, M($o)",
    )
    epilogue2 = make_pattern(
        "lw $y, (N+4)($i)",
        "*",
        "sw $y, (M+4)($o)",
    )
    instruction_name = "memcpy.aligned.fictive"


class UnalignedMemcpyPattern(MemcpyPatternBase):
    pattern_mips1 = make_pattern(
        ".loop:",
        "lwl $a, N($i)",
        "lwr $a, (N+3)($i)",
        "addiu $i, $i, 12",
        "swl $a, M($o)",
        "swr $a, (M+3)($o)",
        "lwl $b, (N-8)($i)",
        "lwr $b, (N-5)($i)",
        "addiu $o, $o, 12",
        "swl $b, (M-8)($o)",
        "swr $b, (M-5)($o)",
        "lwl $c, (N-4)($i)",
        "lwr $c, (N-1)($i)",
        "nop",
        "swl $c, (M-4)($o)",
        "bne $i, $e, .loop",
        "swr $c, (M-1)($o)",
    )
    pattern_mips2 = make_pattern(
        ".loop:",
        "lwl $a, N($i)",
        "lwr $a, (N+3)($i)",
        "addiu $i, $i, 12",
        "addiu $o, $o, 12",
        "swl $a, MM($o)",
        ".eq M, MM+12",
        "swr $a, (M-9)($o)",
        "lwl $b, (N-8)($i)",
        "lwr $b, (N-5)($i)",
        "swl $b, (M-8)($o)",
        "swr $b, (M-5)($o)",
        "lwl $c, (N-4)($i)",
        "lwr $c, (N-1)($i)",
        "swl $c, (M-4)($o)",
        "bne $i, $e, .loop",
        "swr $c, (M-1)($o)",
    )
    epilogue1 = make_pattern(
        "lwl $x, N($i)",
        "lwr $x, (N+3)($i)",
        "*",
        "swl $x, M($o)",
        "swr $x, (M+3)($o)",
    )
    epilogue2 = make_pattern(
        "lwl $y, (N+4)($i)",
        "lwr $y, (N+7)($i)",
        "*",
        "swl $y, (M+4)($o)",
        "swr $y, (M+7)($o)",
    )
    instruction_name = "memcpy.unaligned.fictive"


class GpJumpPattern(SimpleAsmPattern):
    """Remove additions of $gp used for position-independent jump tables. It's
    possible that this could be done for all additions of $gp, not just jumps,
    but we are conservative for now."""

    pattern = make_pattern(
        "addu $x, $x, $gp",
        "jr $x",
    )

    def replace(self, m: AsmMatch) -> Replacement:
        return Replacement([m.body[1]], len(m.body))


class OriSpPattern(SimpleAsmPattern):
    """Some versions of PS2 compilers emit ori for small stack additions instead
    of addiu. Normalize."""

    pattern = make_pattern("ori $x, $sp, N")

    def replace(self, m: AsmMatch) -> Optional[Replacement]:
        n = m.literals["N"]
        if 0 <= n < 16 and m.regs["x"] != Register("sp"):
            ins = AsmInstruction("addiu", [m.regs["x"], Register("sp"), AsmLiteral(n)])
            return Replacement([ins], len(m.body))
        return None


class MipsArch(Arch):
    arch = Target.ArchEnum.MIPS

    stack_pointer_reg = Register("sp")
    frame_pointer_reg = Register("fp")
    return_address_reg = Register("ra")

    base_return_regs = [Register(r) for r in ["v0", "f0"]]
    all_return_regs = [Register(r) for r in ["v0", "v1", "f0", "f1"]]
    argument_regs = [
        Register(r) for r in ["a0", "a1", "a2", "a3", "f12", "f13", "f14", "f15"]
    ]
    simple_temp_regs = [
        Register(r)
        for r in [
            "v0",
            "v1",
            "t0",
            "t1",
            "t2",
            "t3",
            "t4",
            "t5",
            "t6",
            "t7",
            "t8",
            "t9",
            "f0",
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
            "f16",
            "f17",
            "f18",
            "f19",
        ]
    ]
    temp_regs = (
        argument_regs
        + simple_temp_regs
        + [
            Register(r)
            for r in [
                "at",
                "hi",
                "lo",
                "condition_bit",
            ]
        ]
    )
    saved_regs = [
        Register(r)
        for r in [
            "s0",
            "s1",
            "s2",
            "s3",
            "s4",
            "s5",
            "s6",
            "s7",
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
            "ra",
            "31",
            "fp",
            "gp",
        ]
    ]
    all_regs = saved_regs + temp_regs + [stack_pointer_reg, Register("zero")]

    aliased_gp_regs = {
        "s8": Register("fp"),
        "r0": Register("zero"),
    }

    o32abi_float_regs = {
        "fv0": Register("f0"),
        "fv0f": Register("f1"),
        "fv1": Register("f2"),
        "fv1f": Register("f3"),
        "ft0": Register("f4"),
        "ft0f": Register("f5"),
        "ft1": Register("f6"),
        "ft1f": Register("f7"),
        "ft2": Register("f8"),
        "ft2f": Register("f9"),
        "ft3": Register("f10"),
        "ft3f": Register("f11"),
        "fa0": Register("f12"),
        "fa0f": Register("f13"),
        "fa1": Register("f14"),
        "fa1f": Register("f15"),
        "ft4": Register("f16"),
        "ft4f": Register("f17"),
        "ft5": Register("f18"),
        "ft5f": Register("f19"),
        "fs0": Register("f20"),
        "fs0f": Register("f21"),
        "fs1": Register("f22"),
        "fs1f": Register("f23"),
        "fs2": Register("f24"),
        "fs2f": Register("f25"),
        "fs3": Register("f26"),
        "fs3f": Register("f27"),
        "fs4": Register("f28"),
        "fs4f": Register("f29"),
        "fs5": Register("f30"),
        "fs5f": Register("f31"),
    }

    aliased_regs = {**o32abi_float_regs, **aliased_gp_regs}

    @classmethod
    def missing_return(cls) -> List[Instruction]:
        meta = InstructionMeta.missing()
        return [
            cls.parse("jr", [Register("ra")], meta),
            cls.parse("nop", [], meta),
        ]

    @classmethod
    def normalize_instruction(cls, instr: AsmInstruction) -> AsmInstruction:
        args = instr.args
        if len(args) == 3:
            if instr.mnemonic == "sll" and args[0] == args[1] == Register("zero"):
                return AsmInstruction("nop", [])
            if instr.mnemonic == "or" and args[2] == Register("zero"):
                return AsmInstruction("move", args[:2])
            if instr.mnemonic == "addu" and args[2] == Register("zero"):
                return AsmInstruction("move", args[:2])
            if instr.mnemonic == "daddu" and args[2] == Register("zero"):
                return AsmInstruction("move", args[:2])
            if instr.mnemonic == "nor" and args[1] == Register("zero"):
                return AsmInstruction("not", [args[0], args[2]])
            if instr.mnemonic == "nor" and args[2] == Register("zero"):
                return AsmInstruction("not", [args[0], args[1]])
            if instr.mnemonic == "addiu" and args[2] == AsmLiteral(0):
                return AsmInstruction("move", args[:2])
            if (
                instr.mnemonic == "ori"
                and args[1] == Register("zero")
                and isinstance(args[2], AsmLiteral)
            ):
                lit = AsmLiteral(args[2].value & 0xFFFF)
                return AsmInstruction("li", [args[0], lit])
            if (
                instr.mnemonic == "addiu"
                and args[1] == Register("zero")
                and isinstance(args[2], AsmLiteral)
            ):
                lit = AsmLiteral(((args[2].value + 0x8000) & 0xFFFF) - 0x8000)
                return AsmInstruction("li", [args[0], lit])
            if instr.mnemonic == "beq" and args[0] == args[1] == Register("zero"):
                return AsmInstruction("b", [args[2]])
            if instr.mnemonic in ["bne", "beq", "beql", "bnel"] and args[1] == Register(
                "zero"
            ):
                mn = instr.mnemonic[:3] + "z" + instr.mnemonic[3:]
                return AsmInstruction(mn, [args[0], args[2]])
        if len(args) == 2:
            if instr.mnemonic == "beqz" and args[0] == Register("zero"):
                return AsmInstruction("b", [args[1]])
            if instr.mnemonic == "lui" and isinstance(args[1], AsmLiteral):
                lit = AsmLiteral((args[1].value & 0xFFFF) << 16)
                return AsmInstruction("li", [args[0], lit])
            if instr.mnemonic == "jalr" and args[0] != Register("ra"):
                raise DecompFailure("Two-argument form of jalr is not supported.")
            if instr.mnemonic in ("mult", "multu", "dmult", "dmultu", "madd", "maddu"):
                return AsmInstruction(instr.mnemonic, [Register("zero"), *args])
            if instr.mnemonic in LENGTH_THREE:
                return cls.normalize_instruction(
                    AsmInstruction(instr.mnemonic, [args[0]] + args)
                )
        if len(args) == 1:
            if instr.mnemonic == "jalr":
                return AsmInstruction("jalr", [Register("ra"), args[0]])
            if instr.mnemonic in LENGTH_TWO:
                return cls.normalize_instruction(
                    AsmInstruction(instr.mnemonic, [args[0]] + args)
                )
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
        has_delay_slot = False
        is_branch_likely = False
        is_conditional = False
        is_return = False
        is_store = False
        eval_fn: Optional[Callable[[NodeState, InstrArgs], object]] = None

        instr_str = str(AsmInstruction(mnemonic, args))

        memory_sizes = {
            "b": 1,
            "h": 2,
            "w": 4,
            "d": 8,
        }
        size = memory_sizes.get(mnemonic[1:2])

        def make_memory_access(arg: Argument) -> List[Location]:
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

        if mnemonic == "jr" and args[0] == Register("ra"):
            # Return
            assert len(args) == 1
            inputs = [Register("ra")]
            is_return = True
            has_delay_slot = True
        elif mnemonic == "jr":
            # Jump table (switch)
            assert len(args) == 1 and isinstance(args[0], Register)
            inputs.append(args[0])
            jump_target = args[0]
            is_conditional = True
            has_delay_slot = True
            eval_fn = lambda s, a: s.set_switch_expr(a.reg(0))
        elif mnemonic == "jal" or mnemonic == "bal":
            # Function call to label
            assert len(args) == 1
            inputs = list(cls.argument_regs)
            outputs = list(cls.all_return_regs)
            clobbers = list(cls.temp_regs)
            function_target = args[0]
            has_delay_slot = True
            eval_fn = lambda s, a: s.make_function_call(a.sym_imm(0), outputs)
        elif mnemonic == "jalr":
            # Function call to pointer
            assert (
                len(args) == 2
                and args[0] == Register("ra")
                and isinstance(args[1], Register)
            )
            inputs = list(cls.argument_regs)
            inputs.append(args[1])
            outputs = list(cls.all_return_regs)
            clobbers = list(cls.temp_regs)
            function_target = args[1]
            has_delay_slot = True
            eval_fn = lambda s, a: s.make_function_call(a.reg(1), outputs)
        elif mnemonic in ("b", "j"):
            # Unconditional jump
            assert len(args) == 1
            jump_target = get_jump_target(args[0])
            has_delay_slot = True
        elif mnemonic in (
            "beql",
            "bnel",
            "beqzl",
            "bnezl",
            "bgezl",
            "bgtzl",
            "blezl",
            "bltzl",
            "bc1tl",
            "bc1fl",
        ):
            # Branch-likely
            if mnemonic in ("beql", "bnel"):
                assert (
                    len(args) == 3
                    and isinstance(args[0], Register)
                    and isinstance(args[1], Register)
                )
                inputs.append(args[0])
                inputs.append(args[1])
            elif mnemonic in ("bc1tl", "bc1fl"):
                assert len(args) == 1
                inputs.append(Register("condition_bit"))
            else:
                assert len(args) == 2 and isinstance(args[0], Register)
                inputs.append(args[0])
            jump_target = get_jump_target(args[-1])
            has_delay_slot = True
            is_branch_likely = True
            is_conditional = True
            # Branch-likely instructions should be rewritten by flow_graph.py
            eval_fn = unreachable_eval

        elif mnemonic in (
            "beq",
            "bne",
            "beqz",
            "bnez",
            "bgez",
            "bgtz",
            "blez",
            "bltz",
            "bc1t",
            "bc1f",
        ):
            # Normal branch
            if mnemonic in ("beq", "bne"):
                assert (
                    len(args) == 3
                    and isinstance(args[0], Register)
                    and isinstance(args[1], Register)
                )
                inputs = [args[0], args[1]]
            elif mnemonic in ("bc1t", "bc1f"):
                assert len(args) == 1
                inputs = [Register("condition_bit")]
            else:
                assert len(args) == 2 and isinstance(args[0], Register)
                inputs = [args[0]]
            jump_target = get_jump_target(args[-1])
            has_delay_slot = True
            is_conditional = True

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                if mnemonic in ("bc1t", "bc1f"):
                    cond = condition_from_expr(a.regs[Register("condition_bit")])
                    if mnemonic == "bc1f":
                        cond = cond.negated()
                else:
                    cond = cls.instrs_branches[mnemonic](a)
                s.set_branch_condition(cond)

        elif mnemonic == "mfc0":
            assert len(args) == 2 and isinstance(args[0], Register)
            outputs = [args[0]]
            eval_fn = lambda s, a: s.set_reg(
                a.reg_ref(0), ErrorExpr(f"mfc0 {a.raw_arg(1)}")
            )
        elif mnemonic == "mtc0":
            assert len(args) == 2 and isinstance(args[0], Register)
            inputs = [args[0]]
            eval_fn = lambda s, a: s.write_statement(error_stmt(instr_str))
        elif mnemonic in cls.instrs_no_dest:
            assert not any(isinstance(a, AsmAddressMode) for a in args)
            inputs = [r for r in args if isinstance(r, Register)]
            eval_fn = lambda s, a: s.write_statement(cls.instrs_no_dest[mnemonic](a))
        elif mnemonic in cls.instrs_store:
            assert isinstance(args[0], Register)
            inputs = [args[0]]
            outputs = make_memory_access(args[1])
            is_store = True
            if isinstance(args[1], AsmAddressMode):
                inputs.append(args[1].rhs)
            if mnemonic == "sdc1":
                inputs.append(args[0].other_f64_reg())

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                store = cls.instrs_store[mnemonic](a)
                if store is not None:
                    s.store_memory(store, a.reg_ref(0))

        elif mnemonic == "mtc1":
            # Floating point moving instruction, source first
            assert (
                len(args) == 2
                and isinstance(args[0], Register)
                and isinstance(args[1], Register)
            )
            inputs = [args[0]]
            outputs = [args[1]]
            eval_fn = lambda s, a: s.set_reg(a.reg_ref(1), a.reg(0))
        elif mnemonic in cls.instrs_destination_first:
            assert isinstance(args[0], Register)
            outputs = [args[0]]
            mn_parts = mnemonic.split(".")
            if mnemonic in (
                "add.d",
                "sub.d",
                "neg.d",
                "abs.d",
                "sqrt.d",
                "div.d",
                "mul.d",
                "mov.d",
            ):
                # f64 arithmetic operations; all registers are f64's
                assert 2 <= len(args) <= 3
                for reg in args[1:]:
                    assert isinstance(reg, Register)
                    inputs.extend([reg, reg.other_f64_reg()])
                outputs.append(args[0].other_f64_reg())
            elif mn_parts[0] in ("cvt", "trunc"):
                # f64 conversion; either the input or output will be an f64
                assert len(args) == 2 and isinstance(args[1], Register)
                if mn_parts[2] == "d":
                    inputs = [args[1], args[1].other_f64_reg()]
                else:
                    inputs = [args[1]]
                if mn_parts[1] == "d":
                    outputs.append(args[0].other_f64_reg())
            elif mnemonic.startswith("l") and size is not None:
                # Load instructions
                assert len(args) == 2
                inputs = make_memory_access(args[1])
                if isinstance(args[1], AsmAddressMode):
                    inputs.append(args[1].rhs)
                if mnemonic == "lwr":
                    # lwl, lwr sometimes read from their destination registers,
                    # though we treat lwl as not doing so -- see handle_lwl.
                    inputs.append(args[0])
                elif mnemonic == "ldc1":
                    outputs.append(args[0].other_f64_reg())
            elif mnemonic == "la" and isinstance(args[1], AsmAddressMode):
                inputs = [args[1].rhs]
            elif mnemonic == "mfhi":
                assert len(args) == 1
                inputs = [Register("hi")]
            elif mnemonic == "mflo":
                assert len(args) == 1
                inputs = [Register("lo")]
            elif mnemonic in ("movn", "movz"):
                assert (
                    len(args) == 3
                    and isinstance(args[1], Register)
                    and isinstance(args[2], Register)
                )
                inputs = [args[0], args[1], args[2]]
            else:
                assert not any(isinstance(a, AsmAddressMode) for a in args)
                inputs = [r for r in args[1:] if isinstance(r, Register)]

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                target = a.reg_ref(0)
                s.set_reg(target, cls.instrs_destination_first[mnemonic](a))
                if len(outputs) == 2:
                    s.set_reg(target.other_f64_reg(), SecondF64Half())

        elif mnemonic in cls.instrs_float_comp:
            assert (
                len(args) == 2
                and isinstance(args[0], Register)
                and isinstance(args[1], Register)
            )
            if mnemonic.endswith(".d"):
                inputs = [
                    args[0],
                    args[0].other_f64_reg(),
                    args[1],
                    args[1].other_f64_reg(),
                ]
            else:
                inputs = [args[0], args[1]]
            outputs = [Register("condition_bit")]
            eval_fn = lambda s, a: s.set_reg(
                Register("condition_bit"), cls.instrs_float_comp[mnemonic](a)
            )
        elif mnemonic in cls.instrs_hi_lo:
            assert (
                len(args) == 3
                and isinstance(args[0], Register)
                and isinstance(args[1], Register)
                and isinstance(args[2], Register)
            )
            inputs = [args[1], args[2]]
            if mnemonic in ("madd", "maddu"):
                inputs.append(Register("lo"))
            outputs = [Register("hi"), Register("lo")]
            if args[0] != Register("zero"):
                outputs.append(args[0])

            def eval_fn(s: NodeState, a: InstrArgs) -> None:
                hi, lo = cls.instrs_hi_lo[mnemonic](a)
                s.set_reg(Register("hi"), hi)
                s.set_reg(Register("lo"), lo)
                copy_lo_to = a.reg_ref(0)
                if copy_lo_to != Register("zero"):
                    s.set_reg(copy_lo_to, lo)

        elif mnemonic in ("mtlo", "mthi"):
            assert len(args) == 1 and isinstance(args[0], Register)
            inputs = [args[0]]
            output_reg = Register("hi") if mnemonic == "mthi" else Register("lo")
            outputs = [output_reg]
            eval_fn = lambda s, a: s.set_reg(output_reg, a.reg(0))
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
            has_delay_slot=has_delay_slot,
            is_branch_likely=is_branch_likely,
            is_conditional=is_conditional,
            is_return=is_return,
            is_store=is_store,
            eval_fn=eval_fn,
        )

    asm_patterns = [
        DivPattern(),
        DivuPattern(),
        DivP2Pattern1(),
        DivP2Pattern2(),
        Div2S16Pattern(),
        Div2S32Pattern1(),
        Div2S32Pattern2(),
        ModP2Pattern1(),
        ModP2Pattern2(),
        UtfPattern(),
        FtuPattern(),
        Mips1DoubleLoadStorePattern(),
        GccSqrtPattern(),
        TrapuvPattern(),
        SetGpPattern(),
        AlignedMemcpyPattern(),
        UnalignedMemcpyPattern(),
        GpJumpPattern(),
        OriSpPattern(),
    ]

    instrs_ignore: Set[str] = {
        # Ignore FCSR sets; they are leftovers from float->unsigned conversions.
        # FCSR gets are as well, but it's fine to read M2C_ERROR for those.
        "ctc1",
        "nop",
        "b",
        "j",
    }
    instrs_store: StoreInstrMap = {
        # Storage instructions
        "sb": lambda a: make_store(a, type=Type.int_of_size(8)),
        "sh": lambda a: make_store(a, type=Type.int_of_size(16)),
        "sw": lambda a: make_store(a, type=Type.reg32(likely_float=False)),
        "sd": lambda a: make_store(a, type=Type.reg64(likely_float=False)),
        # Unaligned stores
        "swl": lambda a: handle_swl(a),
        "swr": lambda a: handle_swr(a),
        # Floating point storage/conversion
        "swc1": lambda a: make_store(a, type=Type.reg32(likely_float=True)),
        "sdc1": lambda a: make_store(a, type=Type.reg64(likely_float=True)),
    }
    instrs_branches: CmpInstrMap = {
        # Branch instructions/pseudoinstructions
        "beq": lambda a: BinaryOp.icmp(a.reg(0), "==", a.reg(1)),
        "bne": lambda a: BinaryOp.icmp(a.reg(0), "!=", a.reg(1)),
        "beqz": lambda a: BinaryOp.icmp(a.reg(0), "==", Literal(0)),
        "bnez": lambda a: BinaryOp.icmp(a.reg(0), "!=", Literal(0)),
        "blez": lambda a: BinaryOp.scmp(a.reg(0), "<=", Literal(0)),
        "bgtz": lambda a: BinaryOp.scmp(a.reg(0), ">", Literal(0)),
        "bltz": lambda a: handle_bgez(a).negated(),
        "bgez": lambda a: handle_bgez(a),
    }
    instrs_no_dest: StmtInstrMap = {
        # Conditional traps (happen with Pascal code sometimes, might as well give a nicer
        # output than M2C_ERROR(...))
        "teq": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.icmp(a.reg(0), "==", a.reg(1))]
        ),
        "tne": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.icmp(a.reg(0), "!=", a.reg(1))]
        ),
        "tlt": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.scmp(a.reg(0), "<", a.reg(1))]
        ),
        "tltu": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.ucmp(a.reg(0), "<", a.reg(1))]
        ),
        "tge": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.scmp(a.reg(0), ">=", a.reg(1))]
        ),
        "tgeu": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.ucmp(a.reg(0), ">=", a.reg(1))]
        ),
        "teqi": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.icmp(a.reg(0), "==", a.imm(1))]
        ),
        "tnei": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.icmp(a.reg(0), "!=", a.imm(1))]
        ),
        "tlti": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.scmp(a.reg(0), "<", a.imm(1))]
        ),
        "tltiu": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.ucmp(a.reg(0), "<", a.imm(1))]
        ),
        "tgei": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.scmp(a.reg(0), ">=", a.imm(1))]
        ),
        "tgeiu": lambda a: void_fn_op(
            "M2C_TRAP_IF", [BinaryOp.ucmp(a.reg(0), ">=", a.imm(1))]
        ),
        "break": lambda a: void_fn_op(
            "M2C_BREAK", [a.imm(0)] if a.count() >= 1 else []
        ),
        "sync": lambda a: void_fn_op("M2C_SYNC", []),
        "trapuv.fictive": lambda a: CommentStmt("code compiled with -trapuv"),
        "memcpy.aligned.fictive": lambda a: void_fn_op(
            "M2C_MEMCPY_ALIGNED", [a.reg(0), a.reg(1), a.imm(2)]
        ),
        "memcpy.unaligned.fictive": lambda a: void_fn_op(
            "M2C_MEMCPY_UNALIGNED", [a.reg(0), a.reg(1), a.imm(2)]
        ),
    }
    instrs_float_comp: InstrMap = {
        # Float comparisons that don't raise exception on nan
        "c.eq.s": lambda a: BinaryOp.fcmp(a.reg(0), "==", a.reg(1)),
        "c.olt.s": lambda a: BinaryOp.fcmp(a.reg(0), "<", a.reg(1)),
        "c.oge.s": lambda a: BinaryOp.fcmp(a.reg(0), ">=", a.reg(1)),
        "c.ole.s": lambda a: BinaryOp.fcmp(a.reg(0), "<=", a.reg(1)),
        "c.ogt.s": lambda a: BinaryOp.fcmp(a.reg(0), ">", a.reg(1)),
        "c.neq.s": lambda a: BinaryOp.fcmp(a.reg(0), "==", a.reg(1)).negated(),
        "c.uge.s": lambda a: BinaryOp.fcmp(a.reg(0), "<", a.reg(1)).negated(),
        "c.ult.s": lambda a: BinaryOp.fcmp(a.reg(0), ">=", a.reg(1)).negated(),
        "c.ugt.s": lambda a: BinaryOp.fcmp(a.reg(0), "<=", a.reg(1)).negated(),
        "c.ule.s": lambda a: BinaryOp.fcmp(a.reg(0), ">", a.reg(1)).negated(),
        # Float comparisons that may raise exception on nan
        "c.seq.s": lambda a: BinaryOp.fcmp(a.reg(0), "==", a.reg(1)),
        "c.lt.s": lambda a: BinaryOp.fcmp(a.reg(0), "<", a.reg(1)),
        "c.ge.s": lambda a: BinaryOp.fcmp(a.reg(0), ">=", a.reg(1)),
        "c.le.s": lambda a: BinaryOp.fcmp(a.reg(0), "<=", a.reg(1)),
        "c.gt.s": lambda a: BinaryOp.fcmp(a.reg(0), ">", a.reg(1)),
        "c.sne.s": lambda a: BinaryOp.fcmp(a.reg(0), "==", a.reg(1)).negated(),
        "c.nle.s": lambda a: BinaryOp.fcmp(a.reg(0), "<=", a.reg(1)).negated(),
        "c.nlt.s": lambda a: BinaryOp.fcmp(a.reg(0), "<", a.reg(1)).negated(),
        "c.nge.s": lambda a: BinaryOp.fcmp(a.reg(0), ">=", a.reg(1)).negated(),
        "c.ngt.s": lambda a: BinaryOp.fcmp(a.reg(0), ">", a.reg(1)).negated(),
        # Double comparisons that don't raise exception on nan
        "c.eq.d": lambda a: BinaryOp.dcmp(a.dreg(0), "==", a.dreg(1)),
        "c.olt.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<", a.dreg(1)),
        "c.oge.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">=", a.dreg(1)),
        "c.ole.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<=", a.dreg(1)),
        "c.ogt.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">", a.dreg(1)),
        "c.neq.d": lambda a: BinaryOp.dcmp(a.dreg(0), "==", a.dreg(1)).negated(),
        "c.uge.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<", a.dreg(1)).negated(),
        "c.ult.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">=", a.dreg(1)).negated(),
        "c.ugt.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<=", a.dreg(1)).negated(),
        "c.ule.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">", a.dreg(1)).negated(),
        # Double comparisons that may raise exception on nan
        "c.seq.d": lambda a: BinaryOp.dcmp(a.dreg(0), "==", a.dreg(1)),
        "c.lt.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<", a.dreg(1)),
        "c.ge.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">=", a.dreg(1)),
        "c.le.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<=", a.dreg(1)),
        "c.gt.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">", a.dreg(1)),
        "c.sne.d": lambda a: BinaryOp.dcmp(a.dreg(0), "==", a.dreg(1)).negated(),
        "c.nle.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<=", a.dreg(1)).negated(),
        "c.nlt.d": lambda a: BinaryOp.dcmp(a.dreg(0), "<", a.dreg(1)).negated(),
        "c.nge.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">=", a.dreg(1)).negated(),
        "c.ngt.d": lambda a: BinaryOp.dcmp(a.dreg(0), ">", a.dreg(1)).negated(),
    }
    instrs_hi_lo: Dict[str, Callable[[InstrArgs], Tuple[Expression, Expression]]] = {
        # Div and mul output two results, to LO/HI registers. (Format: (hi, lo))
        # PS2's mult/multu/madd/maddu instructions additionally support an output
        # register to copy LO to, $zero meaning no copying, and GNU as extends
        # that as a pseudo-instruction to div instructions too.
        "div": lambda a: (
            BinaryOp.sint(a.reg(1), "%", a.reg(2)),
            BinaryOp.sint(a.reg(1), "/", a.reg(2)),
        ),
        "divu": lambda a: (
            BinaryOp.uint(a.reg(1), "%", a.reg(2)),
            BinaryOp.uint(a.reg(1), "/", a.reg(2)),
        ),
        "ddiv": lambda a: (
            BinaryOp.s64(a.reg(1), "%", a.reg(2)),
            BinaryOp.s64(a.reg(1), "/", a.reg(2)),
        ),
        "ddivu": lambda a: (
            BinaryOp.u64(a.reg(1), "%", a.reg(2)),
            BinaryOp.u64(a.reg(1), "/", a.reg(2)),
        ),
        "mult": lambda a: (
            fold_divmod(BinaryOp.int(a.reg(1), "MULT_HI", a.reg(2))),
            BinaryOp.int(a.reg(1), "*", a.reg(2)),
        ),
        "multu": lambda a: (
            fold_divmod(BinaryOp.int(a.reg(1), "MULTU_HI", a.reg(2))),
            BinaryOp.int(a.reg(1), "*", a.reg(2)),
        ),
        "dmult": lambda a: (
            BinaryOp.int64(a.reg(1), "DMULT_HI", a.reg(2)),
            BinaryOp.int64(a.reg(1), "*", a.reg(2)),
        ),
        "dmultu": lambda a: (
            BinaryOp.int64(a.reg(1), "DMULTU_HI", a.reg(2)),
            BinaryOp.int64(a.reg(1), "*", a.reg(2)),
        ),
        # madd/maddu are PS2 extensions, and act as u64(HI|LO) += x * y.
        # In practice, compiler-generated code only uses the lo part of the
        # output, which means we also only need the lo part of the input.
        "madd": lambda a: (
            ErrorExpr("madd top half"),
            handle_add_real(
                Register("lo"),
                a.regs[Register("lo")],
                BinaryOp.int(a.reg(1), "*", a.reg(2)),
                a,
            ),
        ),
        "maddu": lambda a: (
            ErrorExpr("maddu top half"),
            handle_add_real(
                Register("lo"),
                a.regs[Register("lo")],
                BinaryOp.int(a.reg(1), "*", a.reg(2)),
                a,
            ),
        ),
    }
    instrs_destination_first: InstrMap = {
        # Flag-setting instructions
        "slt": lambda a: BinaryOp.scmp(a.reg(1), "<", a.reg(2)),
        "slti": lambda a: BinaryOp.scmp(a.reg(1), "<", a.imm(2)),
        "sltu": lambda a: handle_sltu(a),
        "sltiu": lambda a: handle_sltiu(a),
        # Integer arithmetic
        "addi": lambda a: handle_addi(a),
        "addiu": lambda a: handle_addi(a),
        "add": lambda a: handle_add(a),
        "addu": lambda a: handle_add(a),
        "sub": lambda a: (
            fold_mul_chains(fold_divmod(BinaryOp.intptr(a.reg(1), "-", a.reg(2))))
        ),
        "subu": lambda a: (
            fold_mul_chains(fold_divmod(BinaryOp.intptr(a.reg(1), "-", a.reg(2))))
        ),
        "negu": lambda a: fold_mul_chains(
            UnaryOp.sint(op="-", expr=a.reg(1)),
        ),
        "neg": lambda a: fold_mul_chains(
            UnaryOp.sint(op="-", expr=a.reg(1)),
        ),
        "div.fictive": lambda a: BinaryOp.sint(a.reg(1), "/", a.full_imm(2)),
        "mod.fictive": lambda a: BinaryOp.sint(a.reg(1), "%", a.full_imm(2)),
        # 64-bit integer arithmetic, treated mostly the same as 32-bit for now
        "daddi": lambda a: handle_addi(a),
        "daddiu": lambda a: handle_addi(a),
        "daddu": lambda a: handle_add(a),
        "dsubu": lambda a: fold_mul_chains(BinaryOp.intptr(a.reg(1), "-", a.reg(2))),
        "dnegu": lambda a: fold_mul_chains(
            UnaryOp(op="-", expr=as_s64(a.reg(1)), type=Type.s64())
        ),
        "dneg": lambda a: fold_mul_chains(
            UnaryOp(op="-", expr=as_s64(a.reg(1)), type=Type.s64())
        ),
        # Hi/lo register uses (used after division/multiplication)
        "mfhi": lambda a: a.regs[Register("hi")],
        "mflo": lambda a: a.regs[Register("lo")],
        # Floating point arithmetic
        "add.s": lambda a: handle_add_float(a),
        "sub.s": lambda a: BinaryOp.f32(a.reg(1), "-", a.reg(2)),
        "neg.s": lambda a: UnaryOp("-", as_f32(a.reg(1)), type=Type.f32()),
        "abs.s": lambda a: fn_op("fabsf", [as_f32(a.reg(1))], Type.f32()),
        "sqrt.s": lambda a: fn_op("sqrtf", [as_f32(a.reg(1))], Type.f32()),
        "div.s": lambda a: BinaryOp.f32(a.reg(1), "/", a.reg(2)),
        "mul.s": lambda a: BinaryOp.f32(a.reg(1), "*", a.reg(2)),
        # Double-precision arithmetic
        "add.d": lambda a: handle_add_double(a),
        "sub.d": lambda a: BinaryOp.f64(a.dreg(1), "-", a.dreg(2)),
        "neg.d": lambda a: UnaryOp("-", as_f64(a.dreg(1)), type=Type.f64()),
        "abs.d": lambda a: fn_op("fabs", [as_f64(a.dreg(1))], Type.f64()),
        "sqrt.d": lambda a: fn_op("sqrt", [as_f64(a.dreg(1))], Type.f64()),
        "div.d": lambda a: BinaryOp.f64(a.dreg(1), "/", a.dreg(2)),
        "mul.d": lambda a: BinaryOp.f64(a.dreg(1), "*", a.dreg(2)),
        # Floating point conversions
        "cvt.d.s": lambda a: handle_convert(a.reg(1), Type.f64(), Type.f32()),
        "cvt.d.w": lambda a: handle_convert(a.reg(1), Type.f64(), Type.intish()),
        "cvt.s.d": lambda a: handle_convert(a.dreg(1), Type.f32(), Type.f64()),
        "cvt.s.w": lambda a: handle_convert(a.reg(1), Type.f32(), Type.intish()),
        "cvt.w.d": lambda a: handle_convert(a.dreg(1), Type.s32(), Type.f64()),
        "cvt.w.s": lambda a: handle_convert(a.reg(1), Type.s32(), Type.f32()),
        "cvt.s.u.fictive": lambda a: handle_convert(a.reg(1), Type.f32(), Type.u32()),
        "cvt.u.d.fictive": lambda a: handle_convert(a.dreg(1), Type.u32(), Type.f64()),
        "cvt.u.s.fictive": lambda a: handle_convert(a.reg(1), Type.u32(), Type.f32()),
        "trunc.w.s": lambda a: handle_convert(a.reg(1), Type.s32(), Type.f32()),
        "trunc.w.d": lambda a: handle_convert(a.dreg(1), Type.s32(), Type.f64()),
        # Bit arithmetic
        "ori": lambda a: handle_or(a.reg(1), a.unsigned_imm(2)),
        "and": lambda a: BinaryOp.int(left=a.reg(1), op="&", right=a.reg(2)),
        "or": lambda a: BinaryOp.int(left=a.reg(1), op="|", right=a.reg(2)),
        "not": lambda a: UnaryOp("~", a.reg(1), type=Type.intish()),
        "nor": lambda a: UnaryOp(
            "~", BinaryOp.int(left=a.reg(1), op="|", right=a.reg(2)), type=Type.intish()
        ),
        "xor": lambda a: BinaryOp.int(left=a.reg(1), op="^", right=a.reg(2)),
        "andi": lambda a: BinaryOp.int(left=a.reg(1), op="&", right=a.unsigned_imm(2)),
        "xori": lambda a: BinaryOp.int(left=a.reg(1), op="^", right=a.unsigned_imm(2)),
        # Shifts
        "sll": lambda a: fold_mul_chains(
            BinaryOp.int(left=a.reg(1), op="<<", right=as_intish(a.imm(2)))
        ),
        "sllv": lambda a: fold_mul_chains(
            BinaryOp.int(left=a.reg(1), op="<<", right=as_intish(a.reg(2)))
        ),
        "srl": lambda a: fold_divmod(
            BinaryOp(
                left=as_uintish(a.reg(1)),
                op=">>",
                right=as_intish(a.imm(2)),
                type=Type.u32(),
            )
        ),
        "srlv": lambda a: fold_divmod(
            BinaryOp(
                left=as_uintish(a.reg(1)),
                op=">>",
                right=as_intish(a.reg(2)),
                type=Type.u32(),
            )
        ),
        "sra": lambda a: handle_sra(a),
        "srav": lambda a: fold_divmod(
            BinaryOp(
                left=as_sintish(a.reg(1)),
                op=">>",
                right=as_intish(a.reg(2)),
                type=Type.s32(),
            )
        ),
        # 64-bit shifts
        "dsll": lambda a: fold_mul_chains(
            BinaryOp.int64(left=a.reg(1), op="<<", right=as_intish(a.imm(2)))
        ),
        "dsll32": lambda a: fold_mul_chains(
            BinaryOp.int64(left=a.reg(1), op="<<", right=imm_add_32(a.imm(2)))
        ),
        "dsllv": lambda a: BinaryOp.int64(
            left=a.reg(1), op="<<", right=as_intish(a.reg(2))
        ),
        "dsrl": lambda a: BinaryOp(
            left=as_u64(a.reg(1)), op=">>", right=as_intish(a.imm(2)), type=Type.u64()
        ),
        "dsrl32": lambda a: BinaryOp(
            left=as_u64(a.reg(1)), op=">>", right=imm_add_32(a.imm(2)), type=Type.u64()
        ),
        "dsrlv": lambda a: BinaryOp(
            left=as_u64(a.reg(1)), op=">>", right=as_intish(a.reg(2)), type=Type.u64()
        ),
        "dsra": lambda a: BinaryOp(
            left=as_s64(a.reg(1)), op=">>", right=as_intish(a.imm(2)), type=Type.s64()
        ),
        "dsra32": lambda a: BinaryOp(
            left=as_s64(a.reg(1)), op=">>", right=imm_add_32(a.imm(2)), type=Type.s64()
        ),
        "dsrav": lambda a: BinaryOp(
            left=as_s64(a.reg(1)), op=">>", right=as_intish(a.reg(2)), type=Type.s64()
        ),
        # Move pseudoinstruction
        "move": lambda a: a.reg(1),
        "move.fictive": lambda a: a.reg(1),
        # Floating point moving instructions
        "mfc1": lambda a: a.reg(1),
        "mov.s": lambda a: a.reg(1),
        "mov.d": lambda a: as_f64(a.dreg(1)),
        # Conditional moves
        "movn": lambda a: handle_conditional_move(a, True),
        "movz": lambda a: handle_conditional_move(a, False),
        # FCSR get
        "cfc1": lambda a: ErrorExpr("cfc1"),
        # Immediates
        "li": lambda a: a.full_imm(1),
        "lui": lambda a: load_upper(a),
        "la": lambda a: handle_la(a),
        # Loading instructions
        "lb": lambda a: handle_load(a, type=Type.s8()),
        "lbu": lambda a: handle_load(a, type=Type.u8()),
        "lh": lambda a: handle_load(a, type=Type.s16()),
        "lhu": lambda a: handle_load(a, type=Type.u16()),
        "lw": lambda a: handle_lw(a),
        "ld": lambda a: handle_load(a, type=Type.reg64(likely_float=False)),
        "lwu": lambda a: handle_load(a, type=Type.u32()),
        "lwc1": lambda a: handle_load(a, type=Type.reg32(likely_float=True)),
        "ldc1": lambda a: handle_load(a, type=Type.reg64(likely_float=True)),
        # Unaligned loads
        "lwl": lambda a: handle_lwl(a),
        "lwr": lambda a: handle_lwr(a),
    }

    @staticmethod
    def function_abi(
        fn_sig: FunctionSignature,
        likely_regs: Dict[Register, bool],
        *,
        for_call: bool,
    ) -> Abi:
        """Compute stack positions/registers used by a function according to the o32 ABI,
        based on C type information. Additionally computes a list of registers that might
        contain arguments, if the function is a varargs function. (Additional varargs
        arguments may be passed on the stack; we could compute the offset at which that
        would start but right now don't care -- we just slurp up everything.)"""

        known_slots: List[AbiArgSlot] = []
        candidate_slots: List[AbiArgSlot] = []
        if fn_sig.params_known:
            offset = 0
            only_floats = True
            if fn_sig.return_type.is_struct():
                # The ABI for struct returns is to pass a pointer to where it should be written
                # as the first argument.
                known_slots.append(
                    AbiArgSlot(
                        offset=0,
                        reg=Register("a0"),
                        name="__return__",
                        type=Type.ptr(fn_sig.return_type),
                        comment="return",
                    )
                )
                offset = 4
                only_floats = False

            for ind, param in enumerate(fn_sig.params):
                # Array parameters decay into pointers
                param_type = param.type.decay()
                size, align = param_type.get_parameter_size_align_bytes()
                size = (size + 3) & ~3
                only_floats = only_floats and param_type.is_float()
                offset = (offset + align - 1) & -align
                name = param.name
                reg2: Optional[Register]
                if ind < 2 and only_floats:
                    reg = Register("f12" if ind == 0 else "f14")
                    is_double = (
                        param_type.is_float() and param_type.get_size_bits() == 64
                    )
                    known_slots.append(
                        AbiArgSlot(offset=offset, reg=reg, name=name, type=param_type)
                    )
                    if is_double and not for_call:
                        name2 = f"{name}_lo" if name else None
                        reg2 = Register("f13" if ind == 0 else "f15")
                        known_slots.append(
                            AbiArgSlot(
                                offset=offset + 4,
                                reg=reg2,
                                name=name2,
                                type=Type.any_reg(),
                            )
                        )
                else:
                    for i in range(offset // 4, (offset + size) // 4):
                        unk_offset = 4 * i - offset
                        reg2 = Register(f"a{i}") if i < 4 else None
                        if size > 4:
                            name2 = f"{name}_unk{unk_offset:X}" if name else None
                            sub_type = Type.any()
                            comment: Optional[str] = f"{param_type}+{unk_offset:#x}"
                        else:
                            assert unk_offset == 0
                            name2 = name
                            sub_type = param_type
                            comment = None
                        known_slots.append(
                            AbiArgSlot(
                                offset=4 * i,
                                reg=reg2,
                                name=name2,
                                type=sub_type,
                                comment=comment,
                            )
                        )
                offset += size

            if fn_sig.is_variadic:
                for i in range(offset // 4, 4):
                    candidate_slots.append(
                        AbiArgSlot(i * 4, Register(f"a{i}"), Type.any_reg())
                    )

        else:
            candidate_slots = [
                AbiArgSlot(0, Register("f12"), Type.floatish()),
                AbiArgSlot(4, Register("f13"), Type.floatish()),
                AbiArgSlot(4, Register("f14"), Type.floatish()),
                AbiArgSlot(12, Register("f15"), Type.floatish()),
                AbiArgSlot(0, Register("a0"), Type.intptr()),
                AbiArgSlot(4, Register("a1"), Type.any_reg()),
                AbiArgSlot(8, Register("a2"), Type.any_reg()),
                AbiArgSlot(12, Register("a3"), Type.any_reg()),
            ]

        valid_extra_regs: Set[Register] = {
            slot.reg for slot in known_slots if slot.reg is not None
        }
        possible_slots: List[AbiArgSlot] = []
        for slot in candidate_slots:
            if slot.reg is None or slot.reg not in likely_regs:
                continue

            # Don't pass this register if lower numbered ones are undefined.
            # Following the o32 ABI, register order can be a prefix of either:
            # a0, a1, a2, a3
            # f12, a1, a2, a3
            # f12, f14, a2, a3
            # f12, f13, a2, a3
            # f12, f13, f14, f15
            require: Optional[List[str]] = None
            if slot == candidate_slots[0]:
                # For varargs, a subset of a0 .. a3 may be used. Don't check
                # earlier registers for the first member of that subset.
                pass
            elif slot.reg == Register("f13") or slot.reg == Register("f14"):
                require = ["f12"]
            elif slot.reg == Register("f15"):
                require = ["f14"]
            elif slot.reg == Register("a1"):
                require = ["a0", "f12"]
            elif slot.reg == Register("a2"):
                require = ["a1", "f13", "f14"]
            elif slot.reg == Register("a3"):
                require = ["a2"]
            if require and not any(Register(r) in valid_extra_regs for r in require):
                continue

            valid_extra_regs.add(slot.reg)

            if (
                slot.reg == Register("f13") or slot.reg == Register("f15")
            ) and for_call:
                # We don't pass in f13 or f15 because they will often only
                # contain SecondF64Half(), and otherwise would need to be
                # merged with f12/f14 which we don't have logic for right
                # now. However, f13 can still matter for whether a2 should
                # be passed, and so is kept in valid_extra_regs
                continue

            # Skip registers that are untouched from the initial parameter
            # list. This is sometimes wrong (can give both false positives
            # and negatives), but having a heuristic here is unavoidable
            # without access to function signatures, or when dealing with
            # varargs functions. Decompiling multiple functions at once
            # would help.
            # TODO: don't do this in the middle of the argument list,
            # except for f12 if a0 is passed and such.
            if not likely_regs[slot.reg]:
                continue

            possible_slots.append(slot)

        return Abi(
            arg_slots=known_slots,
            possible_slots=possible_slots,
        )

    @staticmethod
    def function_return(expr: Expression) -> Dict[Register, Expression]:
        # We may not know what this function's return registers are --
        # $f0, $v0 or ($v0,$v1) or $f0 -- but we don't really care,
        # it's fine to be liberal here and put the return value in all
        # of them. (It's not perfect for u64's, but that's rare anyway.)
        return {
            Register("f0"): Cast(
                expr, reinterpret=True, silent=True, type=Type.floatish()
            ),
            Register("v0"): Cast(
                expr, reinterpret=True, silent=True, type=Type.intptr()
            ),
            Register("v1"): as_u32(
                Cast(expr, reinterpret=True, silent=False, type=Type.u64())
            ),
            Register("f1"): SecondF64Half(),
        }
