"""Functions for evaluating assembly instructions and building Expression trees."""
from dataclasses import replace
import struct
from typing import (
    Callable,
    List,
    Optional,
    Tuple,
    Union,
)
from .asm_instruction import (
    AsmLiteral,
    Register,
)
from .error import DecompFailure
from .translate import (
    AddressMode,
    AddressOf,
    ArrayAccess,
    BinaryOp,
    CarryBit,
    Cast,
    Condition,
    ErrorExpr,
    ExprCondition,
    ExprStmt,
    Expression,
    FuncCall,
    GlobalSymbol,
    InstrArgs,
    Literal,
    Load3Bytes,
    LocalVar,
    Lwl,
    RawSymbolRef,
    RegInfo,
    StackInfo,
    StoreStmt,
    StructAccess,
    TernaryOp,
    UnalignedLoad,
    UnaryOp,
    as_intish,
    as_intptr,
    as_sintish,
    as_type,
    early_unwrap,
    early_unwrap_ints,
    var_for_expr,
)
from .types import (
    FunctionParam,
    FunctionSignature,
    StructDeclaration,
    Type,
)


def error_stmt(msg: str) -> ExprStmt:
    return ExprStmt(ErrorExpr(msg))


def deref(
    arg: Union[AddressMode, RawSymbolRef, Expression],
    regs: RegInfo,
    stack_info: StackInfo,
    *,
    size: int,
    store: bool = False,
) -> Expression:
    if isinstance(arg, Expression):
        offset = 0
        var = arg
    elif isinstance(arg, AddressMode):
        offset = arg.offset
        if stack_info.is_stack_reg(arg.rhs):
            return stack_info.get_stack_var(offset, store=store)
        var = regs[arg.rhs]
    else:
        offset = arg.offset
        var = stack_info.global_info.address_of_gsym(arg.sym.symbol_name)

    # Struct member is being dereferenced.

    # Cope slightly better with raw pointers.
    if isinstance(var, Literal) and var.value % (2**16) == 0:
        var = Literal(var.value + offset, type=var.type)
        offset = 0

    # Handle large struct offsets.
    uw_var = early_unwrap(var)
    if isinstance(uw_var, BinaryOp) and uw_var.op == "+":
        for base, addend in [(uw_var.left, uw_var.right), (uw_var.right, uw_var.left)]:
            if isinstance(addend, Literal) and addend.likely_partial_offset():
                offset += addend.value
                var = base
                uw_var = early_unwrap(var)
                break

    var.type.unify(Type.ptr())
    stack_info.record_struct_access(var, offset)
    type: Type = stack_info.unique_type_for("struct", (uw_var, offset), Type.any())

    # Struct access with type information.
    array_expr = array_access_from_add(
        var, offset, stack_info, target_size=size, ptr=False
    )
    if array_expr is not None:
        return array_expr
    field_path, field_type, _ = var.type.get_deref_field(offset, target_size=size)
    if field_path is not None:
        field_type.unify(type)
        type = field_type
    else:
        field_path = None

    return StructAccess(
        struct_var=var,
        offset=offset,
        target_size=size,
        field_path=field_path,
        stack_info=stack_info,
        type=type,
    )


def condition_from_expr(expr: Expression) -> Condition:
    uw_expr = early_unwrap(expr)
    if isinstance(uw_expr, Condition) and not (
        isinstance(uw_expr, BinaryOp) and not uw_expr.is_comparison()
    ):
        return uw_expr
    return ExprCondition(expr, type=expr.type)


def imm_add_32(expr: Expression) -> Expression:
    if isinstance(expr, Literal):
        return as_intish(Literal(expr.value + 32))
    else:
        return BinaryOp.int(expr, "+", Literal(32))


def fn_op(fn_name: str, args: List[Expression], type: Type) -> FuncCall:
    fn_sig = FunctionSignature(
        return_type=type,
        params=[FunctionParam(type=arg.type) for arg in args],
        params_known=True,
        is_variadic=False,
    )
    return FuncCall(
        function=GlobalSymbol(symbol_name=fn_name, type=Type.function(fn_sig)),
        args=args,
        type=type,
    )


def void_fn_op(fn_name: str, args: List[Expression]) -> ExprStmt:
    fn_call = fn_op(fn_name, args, Type.any_reg())
    fn_call.use()
    return ExprStmt(fn_call)


def load_upper(args: InstrArgs) -> Expression:
    assert not isinstance(
        args.raw_arg(1), Literal
    ), "normalize_instruction should convert lui/lis <literal> to li"

    ref = args.hi_imm(1)
    stack_info = args.stack_info
    source = stack_info.global_info.address_of_gsym(ref.sym.symbol_name)
    imm = Literal(ref.offset)
    return handle_addi_real(args.reg_ref(0), None, source, imm, args)


def handle_convert(expr: Expression, dest_type: Type, source_type: Type) -> Cast:
    # int <-> float casts should be explicit
    silent = dest_type.data().kind != source_type.data().kind
    expr.type.unify(source_type)
    return Cast(expr=expr, type=dest_type, silent=silent, reinterpret=False)


def handle_la(args: InstrArgs) -> Expression:
    output_reg = args.reg_ref(0)
    target = args.memory_ref(1)
    stack_info = args.stack_info
    if isinstance(target, AddressMode):
        return handle_addi(
            replace(
                args,
                raw_args=[output_reg, target.rhs, AsmLiteral(target.offset)],
            )
        )

    sym = stack_info.global_info.address_of_gsym(target.sym.symbol_name)
    return add_imm(output_reg, sym, Literal(target.offset), args)


def handle_lw(args: InstrArgs) -> Expression:
    ref = args.maybe_got_imm(1)
    if ref is not None:
        # Handle `lw $a, %got(x + offset)($gp)` as an address load rather than a load.
        sym = args.stack_info.global_info.address_of_gsym(ref.sym.symbol_name)
        return add_imm(args.reg_ref(0), sym, Literal(ref.offset), args)
    return handle_load(args, type=Type.reg32(likely_float=False))


def handle_or(left: Expression, right: Expression) -> Expression:
    if left == right:
        # `or $rD, $rS, $rS` can be used to move $rS into $rD
        return left

    if isinstance(left, Literal) and isinstance(right, Literal):
        if (((left.value & 0xFFFF) == 0 and (right.value & 0xFFFF0000) == 0)) or (
            (right.value & 0xFFFF) == 0 and (left.value & 0xFFFF0000) == 0
        ):
            return Literal(value=(left.value | right.value))
    # Regular bitwise OR.
    return BinaryOp.int(left=left, op="|", right=right)


def handle_sltu(args: InstrArgs) -> Expression:
    right = args.reg(2)
    if args.reg_ref(1) == Register("zero"):
        # (0U < x) is equivalent to (x != 0)
        uw_right = early_unwrap(right)
        if isinstance(uw_right, BinaryOp) and uw_right.op == "^":
            # ((a ^ b) != 0) is equivalent to (a != b)
            return BinaryOp.icmp(uw_right.left, "!=", uw_right.right)
        return BinaryOp.icmp(right, "!=", Literal(0))
    else:
        left = args.reg(1)
        return BinaryOp.ucmp(left, "<", right)


def handle_sltiu(args: InstrArgs) -> Expression:
    left = args.reg(1)
    right = args.imm(2)
    if isinstance(right, Literal):
        value = right.value & 0xFFFFFFFF
        if value == 1:
            # (x < 1U) is equivalent to (x == 0)
            uw_left = early_unwrap(left)
            if isinstance(uw_left, BinaryOp) and uw_left.op == "^":
                # ((a ^ b) == 0) is equivalent to (a == b)
                return BinaryOp.icmp(uw_left.left, "==", uw_left.right)
            return BinaryOp.icmp(left, "==", Literal(0))
        else:
            right = Literal(value)
    return BinaryOp.ucmp(left, "<", right)


def handle_addi(args: InstrArgs) -> Expression:
    output_reg = args.reg_ref(0)
    source_reg = args.reg_ref(1)

    ref = args.maybe_gprel_imm(2)
    if ref is not None and source_reg == Register("gp"):
        sym = args.stack_info.global_info.address_of_gsym(ref.sym.symbol_name)
        return add_imm(output_reg, sym, Literal(ref.offset), args)

    source = args.reg(1)
    imm = args.imm(2)

    # `(x + 0xEDCC)` is emitted as `((x + 0x10000) - 0x1234)`,
    # i.e. as an `addis` followed by an `addi`
    uw_source = early_unwrap(source)
    if (
        isinstance(uw_source, BinaryOp)
        and uw_source.op == "+"
        and isinstance(uw_source.right, Literal)
        and uw_source.right.value % 0x10000 == 0
        and isinstance(imm, Literal)
    ):
        return add_imm(
            output_reg, uw_source.left, Literal(imm.value + uw_source.right.value), args
        )
    return handle_addi_real(output_reg, source_reg, source, imm, args)


def handle_addis(args: InstrArgs) -> Expression:
    source_reg = args.reg_ref(1)
    source = args.reg(1)
    imm = args.shifted_imm(2)
    return handle_addi_real(args.reg_ref(0), source_reg, source, imm, args)


def handle_addi_real(
    output_reg: Register,
    source_reg: Optional[Register],
    source: Expression,
    imm: Expression,
    args: InstrArgs,
) -> Expression:
    stack_info = args.stack_info
    if source_reg is not None and stack_info.is_stack_reg(source_reg):
        # Adding to sp, i.e. passing an address.
        assert isinstance(imm, Literal)
        if stack_info.is_stack_reg(output_reg):
            # Changing sp. Just ignore that.
            return source
        # Keep track of all local variables that we take addresses of.
        var = stack_info.get_stack_var(imm.value, store=False)
        if isinstance(var, LocalVar):
            stack_info.add_local_var(var)
        return AddressOf(var, type=var.type.reference())
    else:
        return add_imm(output_reg, source, imm, args)


def add_imm(
    output_reg: Register, source: Expression, imm: Expression, args: InstrArgs
) -> Expression:
    stack_info = args.stack_info
    if imm == Literal(0):
        # addiu $reg1, $reg2, 0 is a move
        # (this happens when replacing %lo(...) by 0)
        return source
    elif source.type.is_pointer_or_array():
        # Pointer addition (this may miss some pointers that get detected later;
        # unfortunately that's hard to do anything about with m2c's single-pass
        # architecture). Don't do this in the case "var_x = var_x + imm": that
        # happens with loops over subarrays and it's better to expose the raw
        # immediate.
        dest_var = stack_info.get_planned_var(output_reg, args.instruction_ref)
        inplace = dest_var is not None and var_for_expr(source) == dest_var
        if isinstance(imm, Literal) and not imm.likely_partial_offset() and not inplace:
            array_access = array_access_from_add(
                source, imm.value, stack_info, target_size=None, ptr=True
            )
            if array_access is not None:
                return array_access

            field_path, field_type, _ = source.type.get_deref_field(
                imm.value, target_size=None
            )
            if field_path is not None:
                return AddressOf(
                    StructAccess(
                        struct_var=source,
                        offset=imm.value,
                        target_size=None,
                        field_path=field_path,
                        stack_info=stack_info,
                        type=field_type,
                    ),
                    type=field_type.reference(),
                )
        if isinstance(imm, Literal):
            target = source.type.get_pointer_target()
            if target:
                target_size = target.get_size_bytes()
                if target_size and imm.value % target_size == 0:
                    # Pointer addition.
                    return BinaryOp(
                        left=source, op="+", right=as_intish(imm), type=source.type
                    )
        return BinaryOp(left=source, op="+", right=as_intish(imm), type=Type.ptr())
    elif isinstance(source, Literal) and isinstance(imm, Literal):
        return Literal(source.value + imm.value)
    else:
        # Regular binary addition.
        return BinaryOp.intptr(left=source, op="+", right=imm)


def handle_load(args: InstrArgs, type: Type) -> Expression:
    # For now, make the cast silent so that output doesn't become cluttered.
    # Though really, it would be great to expose the load types somehow...
    size = type.get_size_bytes()
    assert size is not None
    expr = deref(args.memory_ref(1), args.regs, args.stack_info, size=size)

    # Detect rodata constants
    if isinstance(expr, StructAccess) and expr.offset == 0:
        target = early_unwrap(expr.struct_var)
        if (
            isinstance(target, AddressOf)
            and isinstance(target.expr, GlobalSymbol)
            and type.is_likely_float()
        ):
            sym_name = target.expr.symbol_name
            ent = args.stack_info.global_info.asm_data_value(sym_name)
            if (
                ent
                and ent.data
                and isinstance(ent.data[0], bytes)
                and len(ent.data[0]) >= size
                and ent.is_readonly
                and type.unify(target.expr.type)
            ):
                data = ent.data[0][:size]
                val: int
                if size == 4:
                    (val,) = struct.unpack(">I", data)
                else:
                    (val,) = struct.unpack(">Q", data)
                return Literal(value=val, type=type)

    return as_type(expr, type, silent=True)


def deref_unaligned(
    arg: Union[AddressMode, RawSymbolRef],
    regs: RegInfo,
    stack_info: StackInfo,
    *,
    store: bool = False,
) -> Expression:
    # We don't know the correct size pass to deref. Passing None would signal that we
    # are taking an address, cause us to prefer entire substructs as referenced fields,
    # which would be confusing. Instead, we lie and pass 1. Hopefully nothing bad will
    # happen...
    return deref(arg, regs, stack_info, size=1, store=store)


def handle_lwl(args: InstrArgs) -> Expression:
    # Unaligned load for the left part of a register (lwl can technically merge with
    # a pre-existing lwr, but doesn't in practice, so we treat this as a standard
    # destination-first operation)
    ref = args.memory_ref(1)
    expr = deref_unaligned(ref, args.regs, args.stack_info)
    key: Tuple[int, object]
    if isinstance(ref, AddressMode):
        key = (ref.offset, args.regs[ref.rhs])
    else:
        key = (ref.offset, ref.sym)
    return Lwl(expr, key)


def handle_lwr(args: InstrArgs) -> Expression:
    # Unaligned load for the right part of a register. This lwr may merge with an
    # existing lwl, if it loads from the same target but with an offset that's ±3.
    uw_old_value = early_unwrap(args.reg(0))
    ref = args.memory_ref(1)
    lwl_key: Tuple[int, object]
    delta = -3 if args.stack_info.global_info.target.is_big_endian() else 3
    if isinstance(ref, AddressMode):
        lwl_key = (ref.offset + delta, args.regs[ref.rhs])
    else:
        lwl_key = (ref.offset + delta, ref.sym)
    if isinstance(uw_old_value, Lwl) and uw_old_value.key[0] == lwl_key[0]:
        return UnalignedLoad(uw_old_value.load_expr)
    # IDO may copy 3 bytes between 4-byte-aligned addresses using lwr+swr, e.g. for
    # the purpose of array initializers. Little endian can use lwl+swl instead,
    # but other compilers don't seem to emit this pattern so we don't handle that
    # at the moment.
    if ref.offset % 4 == 2 and args.stack_info.global_info.target.is_big_endian():
        left_mem_ref = replace(ref, offset=ref.offset - 2)
        load_expr = deref_unaligned(left_mem_ref, args.regs, args.stack_info)
        return Load3Bytes(load_expr)
    return ErrorExpr("Unable to handle lwr; missing a corresponding lwl")


def make_store(args: InstrArgs, type: Type) -> Optional[StoreStmt]:
    size = type.get_size_bytes()
    assert size is not None
    stack_info = args.stack_info
    source_reg = args.reg_ref(0)
    source_raw = args.regs.get_raw(source_reg)
    if type.is_likely_float() and size == 8:
        source_val = args.dreg(0)
    else:
        source_val = args.reg(0)
    target = args.memory_ref(1)
    is_stack = isinstance(target, AddressMode) and stack_info.is_stack_reg(target.rhs)
    if (
        is_stack
        and source_raw is not None
        and stack_info.should_save(source_raw, target.offset)
    ):
        # Elide register preserval.
        return None
    dest = deref(target, args.regs, stack_info, size=size, store=True)
    dest.type.unify(type)
    return StoreStmt(source=as_type(source_val, type, silent=is_stack), dest=dest)


def make_storex(args: InstrArgs, type: Type) -> Optional[StoreStmt]:
    # "indexed stores" like `stwx rS, rA, rB` write `rS` into `(rA + rB)`
    size = type.get_size_bytes()
    assert size is not None

    source = args.reg(0)
    ptr = BinaryOp.intptr(left=args.reg(1), op="+", right=args.reg(2))

    # TODO: Can we assume storex's are never used to save registers to the stack?
    dest = deref(ptr, args.regs, args.stack_info, size=size, store=True)
    dest.type.unify(type)
    return StoreStmt(source=as_type(source, type, silent=False), dest=dest)


def handle_swl(args: InstrArgs) -> Optional[StoreStmt]:
    # swl in practice only occurs together with swr, so we can treat it as a regular
    # store, with the expression wrapped in UnalignedLoad if needed.
    source = args.reg(0)
    target = args.memory_ref(1)
    if not isinstance(early_unwrap(source), UnalignedLoad):
        source = UnalignedLoad(source)
    dest = deref_unaligned(target, args.regs, args.stack_info, store=True)
    return StoreStmt(source=source, dest=dest)


def handle_swr(args: InstrArgs) -> Optional[StoreStmt]:
    expr = early_unwrap(args.reg(0))
    target = args.memory_ref(1)
    if not isinstance(expr, Load3Bytes):
        # Elide swr's that don't come from 3-byte-loading lwr's; they probably
        # come with a corresponding swl which has already been emitted.
        return None
    real_target = replace(target, offset=target.offset - 2)
    dest = deref_unaligned(real_target, args.regs, args.stack_info, store=True)
    return StoreStmt(source=expr, dest=dest)


def handle_sra(args: InstrArgs) -> Expression:
    lhs = args.reg(1)
    shift = args.imm(2)
    if isinstance(shift, Literal) and shift.value in [16, 24]:
        expr = early_unwrap(lhs)
        pow2 = 1 << shift.value
        if isinstance(expr, BinaryOp) and isinstance(expr.right, Literal):
            tp = Type.s16() if shift.value == 16 else Type.s8()
            rhs = expr.right.value
            if expr.op == "<<" and rhs == shift.value:
                return as_type(expr.left, tp, silent=False)
            elif expr.op == "<<" and rhs > shift.value:
                new_shift = fold_mul_chains(
                    BinaryOp.int(expr.left, "<<", Literal(rhs - shift.value))
                )
                return as_type(new_shift, tp, silent=False)
            elif expr.op == "*" and rhs % pow2 == 0 and rhs != pow2:
                mul = BinaryOp.int(expr.left, "*", Literal(value=rhs // pow2))
                return as_type(mul, tp, silent=False)
    return fold_divmod(
        BinaryOp(as_sintish(lhs), ">>", as_intish(shift), type=Type.s32())
    )


def handle_conditional_move(args: InstrArgs, nonzero: bool) -> Expression:
    op = "!=" if nonzero else "=="
    type = Type.any_reg()
    return TernaryOp(
        BinaryOp.scmp(args.reg(2), op, Literal(0)),
        as_type(args.reg(1), type, silent=True),
        as_type(args.reg(0), type, silent=True),
        type,
    )


def fold_divmod(original_expr: BinaryOp) -> BinaryOp:
    """
    Return a new BinaryOp instance if this one can be simplified to a single / or % op.
    This involves simplifying expressions using MULT_HI, MULTU_HI, +, -, <<, >>, and /.

    In GCC 2.7.2, the code that generates these instructions is in expmed.c.

    See also https://ridiculousfish.com/blog/posts/labor-of-division-episode-i.html
    for a modern writeup of a similar algorithm.

    This optimization is also used by MWCC and modern compilers (but not IDO).
    """
    mult_high_ops = ("MULT_HI", "MULTU_HI")
    possible_match_ops = mult_high_ops + ("-", "+", ">>")

    # Only operate on integer expressions of certain operations
    if original_expr.is_floating() or original_expr.op not in possible_match_ops:
        return original_expr

    # Use `early_unwrap_ints` instead of `early_unwrap` to ignore Casts to integer types
    # Although this discards some extra type information, this function largely ignores
    # sign/size information to stay simpler. The result will be made with BinaryOp.int()
    # regardless of input types.
    expr = original_expr
    left_expr = early_unwrap_ints(expr.left)
    right_expr = early_unwrap_ints(expr.right)
    divisor_shift = 0

    # Normalize MULT_HI(N, x) to MULT_HI(x, N)
    if isinstance(left_expr, Literal) and not isinstance(right_expr, Literal):
        left_expr, right_expr = right_expr, left_expr

    # Detect signed power-of-two division: (x >> N) + M2C_CARRY --> x / (1 << N)
    if (
        isinstance(left_expr, BinaryOp)
        and left_expr.op == ">>"
        and isinstance(left_expr.right, Literal)
        and expr.op == "+"
        and isinstance(right_expr, CarryBit)
    ):
        new_denom = 1 << left_expr.right.value
        return BinaryOp.sint(
            left=left_expr.left,
            op="/",
            right=Literal(new_denom),
            silent=True,
        )

    # Fold `/` with `>>`: ((x / N) >> M) --> x / (N << M)
    # NB: If x is signed, this is only correct if there is a sign-correcting subtraction term
    if (
        isinstance(left_expr, BinaryOp)
        and left_expr.op == "/"
        and isinstance(left_expr.right, Literal)
        and expr.op == ">>"
        and isinstance(right_expr, Literal)
    ):
        new_denom = left_expr.right.value << right_expr.value
        if new_denom < (1 << 32):
            return BinaryOp.int(
                left=left_expr.left,
                op="/",
                right=Literal(new_denom),
            )

    # Detect `%`: (x - ((x / y) * y)) --> x % y
    if expr.op == "-" and isinstance(right_expr, BinaryOp) and right_expr.op == "*":
        div_expr = early_unwrap_ints(right_expr.left)
        mod_base = early_unwrap_ints(right_expr.right)
        if (
            isinstance(div_expr, BinaryOp)
            and early_unwrap_ints(div_expr.left) == left_expr
        ):
            # Accept either `(x / y) * y` or `(x >> N) * M` (where `1 << N == M`)
            divisor = early_unwrap_ints(div_expr.right)
            if (div_expr.op == "/" and divisor == mod_base) or (
                div_expr.op == ">>"
                and isinstance(divisor, Literal)
                and isinstance(mod_base, Literal)
                and (1 << divisor.value) == mod_base.value
            ):
                return BinaryOp.int(left=left_expr, op="%", right=right_expr.right)

    # Detect dividing by a negative: ((x >> 31) - (x / N)) --> x / -N
    if (
        expr.op == "-"
        and isinstance(left_expr, BinaryOp)
        and left_expr.op == ">>"
        and early_unwrap_ints(left_expr.right) == Literal(31)
        and isinstance(right_expr, BinaryOp)
        and right_expr.op == "/"
        and isinstance(right_expr.right, Literal)
    ):
        # Swap left_expr & right_expr, but replace the N in right_expr with -N
        left_expr, right_expr = (
            replace(right_expr, right=Literal(-right_expr.right.value)),
            left_expr,
        )

    # Remove outer error term: ((x / N) + ((x / N) >> 31)) --> x / N
    # As N gets close to (1 << 30), this is no longer a negligible error term
    if (
        expr.op == "+"
        and isinstance(left_expr, BinaryOp)
        and left_expr.op == "/"
        and isinstance(left_expr.right, Literal)
        and left_expr.right.value <= (1 << 29)
        and isinstance(right_expr, BinaryOp)
        and early_unwrap_ints(right_expr.left) == left_expr
        and right_expr.op == ">>"
        and early_unwrap_ints(right_expr.right) == Literal(31)
    ):
        return left_expr

    # Remove outer error term: ((x / N) - (x >> 31)) --> x / N
    if (
        expr.op == "-"
        and isinstance(left_expr, BinaryOp)
        and left_expr.op == "/"
        and isinstance(left_expr.right, Literal)
        and isinstance(right_expr, BinaryOp)
        and right_expr.op == ">>"
        and early_unwrap_ints(right_expr.right) == Literal(31)
    ):
        div_expr = left_expr
        shift_var_expr = early_unwrap_ints(right_expr.left)
        div_var_expr = early_unwrap_ints(div_expr.left)
        # Check if the LHS of the shift is the same var that we're dividing by
        if div_var_expr == shift_var_expr:
            if isinstance(div_expr.right, Literal) and div_expr.right.value >= (
                1 << 30
            ):
                return BinaryOp.int(
                    left=div_expr.left,
                    op=div_expr.op,
                    right=div_expr.right,
                )
            return div_expr
        # If the var is under 32 bits, the error term may look like `(x << K) >> 31` instead
        if (
            isinstance(shift_var_expr, BinaryOp)
            and early_unwrap_ints(div_expr.left)
            == early_unwrap_ints(shift_var_expr.left)
            and shift_var_expr.op == "<<"
            and isinstance(shift_var_expr.right, Literal)
        ):
            return div_expr

    # Shift on the result of the mul: MULT_HI(x, N) >> M, shift the divisor by M
    if (
        isinstance(left_expr, BinaryOp)
        and expr.op == ">>"
        and isinstance(right_expr, Literal)
    ):
        divisor_shift += right_expr.value
        expr = left_expr
        left_expr = early_unwrap_ints(expr.left)
        right_expr = early_unwrap_ints(expr.right)

        # Remove inner addition: (MULT_HI(x, N) + x) >> M --> MULT_HI(x, N) >> M
        # MULT_HI performs signed multiplication, so the `+ x` acts as setting the 32nd bit
        # while having a result with the same sign as x.
        # We can ignore it because `round_div` can work with arbitrarily large constants
        if (
            isinstance(left_expr, BinaryOp)
            and left_expr.op == "MULT_HI"
            and expr.op == "+"
            and (
                right_expr == early_unwrap_ints(left_expr.left)
                or right_expr == early_unwrap_ints(left_expr.right)
            )
        ):
            expr = left_expr
            left_expr = early_unwrap_ints(expr.left)
            right_expr = early_unwrap_ints(expr.right)

        # Normalize MULT_HI(N, x) to MULT_HI(x, N)
        if isinstance(left_expr, Literal) and not isinstance(right_expr, Literal):
            left_expr, right_expr = right_expr, left_expr

    # Shift on the LHS of the mul: MULT_HI(x >> M, N) --> MULT_HI(x, N) >> M
    if (
        expr.op in mult_high_ops
        and isinstance(left_expr, BinaryOp)
        and left_expr.op == ">>"
        and isinstance(left_expr.right, Literal)
    ):
        divisor_shift += left_expr.right.value
        left_expr = early_unwrap_ints(left_expr.left)

    # Instead of checking for the error term precisely, just check that
    # the quotient is "close enough" to the integer value
    def round_div(x: int, y: int) -> Optional[int]:
        if y <= 1:
            return None
        result = round(x / y)
        if x / (y + 1) <= result <= x / (y - 1):
            return result
        return None

    if expr.op in mult_high_ops and isinstance(right_expr, Literal):
        denom = round_div(1 << (32 + divisor_shift), right_expr.value)
        if denom is not None:
            return BinaryOp.int(
                left=left_expr,
                op="/",
                right=Literal(denom),
            )

    return original_expr


def replace_clz_shift(expr: BinaryOp) -> BinaryOp:
    """
    Simplify an expression matching `CLZ(x) >> 5` into `x == 0`,
    and further simplify `(a - b) == 0` into `a == b`.
    """
    # Check that the outer expression is `>>`
    if expr.is_floating() or expr.op != ">>":
        return expr

    # Match `CLZ(x) >> 5`, or return the original expr
    left_expr = early_unwrap_ints(expr.left)
    right_expr = early_unwrap_ints(expr.right)
    if not (
        isinstance(left_expr, UnaryOp)
        and left_expr.op == "CLZ"
        and isinstance(right_expr, Literal)
        and right_expr.value == 5
    ):
        return expr

    # If the inner `x` is `(a - b)`, return `a == b`
    sub_expr = early_unwrap(left_expr.expr)
    if (
        isinstance(sub_expr, BinaryOp)
        and not sub_expr.is_floating()
        and sub_expr.op == "-"
    ):
        return BinaryOp.icmp(sub_expr.left, "==", sub_expr.right)

    return BinaryOp.icmp(left_expr.expr, "==", Literal(0, type=left_expr.expr.type))


def replace_bitand(expr: BinaryOp) -> Expression:
    """Detect expressions using `&` for truncating integer casts"""
    if not expr.is_floating() and expr.op == "&":
        if expr.right == Literal(0xFF):
            return as_type(expr.left, Type.int_of_size(8), silent=False)
        if expr.right == Literal(0xFFFF):
            return as_type(expr.left, Type.int_of_size(16), silent=False)
    return expr


def fold_mul_chains(expr: Expression) -> Expression:
    """Simplify an expression involving +, -, * and << to a single multiplication,
    e.g. 4*x - x -> 3*x, or x<<2 -> x*4. This includes some logic for preventing
    folds of consecutive sll, and keeping multiplications by large powers of two
    as bitshifts at the top layer."""

    def fold(
        expr: Expression, toplevel: bool, allow_sll: bool
    ) -> Tuple[Expression, int]:
        if isinstance(expr, BinaryOp):
            lbase, lnum = fold(expr.left, False, (expr.op != "<<"))
            rbase, rnum = fold(expr.right, False, (expr.op != "<<"))
            if expr.op == "<<" and isinstance(expr.right, Literal) and allow_sll:
                # Left-shifts by small numbers are easier to understand if
                # written as multiplications (they compile to the same thing).
                if toplevel and lnum == 1 and not (1 <= expr.right.value <= 4):
                    return (expr, 1)
                return (lbase, lnum << expr.right.value)
            if (
                expr.op == "*"
                and isinstance(expr.right, Literal)
                and (allow_sll or expr.right.value % 2 != 0)
            ):
                return (lbase, lnum * expr.right.value)
            if early_unwrap(lbase) == early_unwrap(rbase):
                if expr.op == "+":
                    return (lbase, lnum + rnum)
                if expr.op == "-":
                    return (lbase, lnum - rnum)
        if isinstance(expr, UnaryOp) and expr.op == "-" and not toplevel:
            base, num = fold(expr.expr, False, True)
            return (base, -num)
        uw_expr = early_unwrap(expr)
        if uw_expr is not expr:
            base, num = fold(uw_expr, False, allow_sll)
            if num != 1:
                return (base, num)
        return (expr, 1)

    base, num = fold(expr, True, True)
    if num == 1:
        return expr
    return BinaryOp.int(left=base, op="*", right=Literal(num))


def array_access_from_add(
    expr: Expression,
    offset: int,
    stack_info: StackInfo,
    *,
    target_size: Optional[int],
    ptr: bool,
) -> Optional[Expression]:
    """Given `expr` of the form `a + (imm * b + Y)` and an `offset` X, try to
    create a corresponding expression of the form `a->unk(X + Y)[b]` if type
    information allows."""
    expr = early_unwrap(expr)
    if not isinstance(expr, BinaryOp) or expr.op != "+":
        return None
    base = expr.left
    addend = expr.right
    if addend.type.is_pointer_or_array() and not base.type.is_pointer_or_array():
        base, addend = addend, base

    uw_addend = early_unwrap(addend)
    if isinstance(uw_addend, BinaryOp) and uw_addend.op == "+":
        if isinstance(uw_addend.right, Literal):
            offset += uw_addend.right.value
            addend = uw_addend.left
        elif isinstance(uw_addend.left, Literal):
            offset += uw_addend.left.value
            addend = uw_addend.right

    index = addend
    scale = 1
    uw_addend = early_unwrap(addend)
    if (
        isinstance(uw_addend, BinaryOp)
        and uw_addend.op in ("*", "<<")
        and isinstance(uw_addend.right, Literal)
    ):
        index = uw_addend.left
        scale = uw_addend.right.value
        if uw_addend.op == "<<":
            scale = 1 << scale

    if scale < 0:
        scale = -scale
        index = UnaryOp.sint("-", index)

    target_type = base.type.get_pointer_target()
    if target_type is None:
        return None

    uw_base = early_unwrap(base)
    typepool = stack_info.global_info.typepool

    # In `&x + index * scale`, if the type of `x` is not known, try to mark it as an array.
    # Skip the `scale = 1` case because this often indicates a complex `index` expression,
    # and is not actually a 1-byte array lookup.
    if (
        scale > 1
        and offset == 0
        and isinstance(uw_base, AddressOf)
        and target_type.get_size_bytes() is None
    ):
        inner_type: Optional[Type] = None
        if (
            isinstance(uw_base.expr, GlobalSymbol)
            and uw_base.expr.potential_array_dim(scale)[1] != 0
        ):
            # For GlobalSymbols, use the size of the asm data to check the feasibility of being
            # an array with `scale`. This helps be more conservative around fake symbols.
            pass
        elif scale == 2:
            # This *could* be a struct, but is much more likely to be an int
            inner_type = Type.int_of_size(16)
        elif scale == 4:
            inner_type = Type.reg32(likely_float=False)
        elif typepool.unk_inference and isinstance(uw_base.expr, GlobalSymbol):
            # Make up a struct with a tag name based on the symbol & struct size.
            # Although `scale = 8` could indicate an array of longs/doubles, it seems more
            # common to be an array of structs.
            struct_name = f"_struct_{uw_base.expr.symbol_name}_0x{scale:X}"
            struct = typepool.get_struct_by_tag_name(
                struct_name, stack_info.global_info.typemap
            )
            if struct is None:
                struct = StructDeclaration.unknown(
                    typepool, size=scale, tag_name=struct_name
                )
            elif struct.size != scale:
                # This should only happen if there was already a struct with this name in the context
                raise DecompFailure(f"sizeof(struct {struct_name}) != {scale:#x}")
            inner_type = Type.struct(struct)

        if inner_type is not None:
            # This might fail, if `uw_base.expr.type` can't be changed to an array
            uw_base.expr.type.unify(Type.array(inner_type, dim=None))
            # This acts as a backup, and will usually succeed
            target_type.unify(inner_type)

    if target_type.get_size_bytes() == scale:
        # base[index]
        pass
    else:
        # base->subarray[index]
        sub_path, sub_type, remaining_offset = base.type.get_deref_field(
            offset, target_size=scale, exact=False
        )
        # Check if the last item in the path is `0`, which indicates the start of an array
        # If it is, remove it: it will be replaced by `[index]`
        if sub_path is None or len(sub_path) < 2 or sub_path[-1] != 0:
            return None
        sub_path.pop()
        base = StructAccess(
            struct_var=base,
            offset=offset - remaining_offset,
            target_size=None,
            field_path=sub_path,
            stack_info=stack_info,
            type=sub_type,
        )
        offset = remaining_offset
        target_type = sub_type

    ret: Expression = ArrayAccess(base, index, type=target_type)

    # Add .field if necessary by wrapping ret in StructAccess(AddressOf(...))
    ret_ref = AddressOf(ret, type=ret.type.reference())
    field_path, field_type, _ = ret_ref.type.get_deref_field(
        offset, target_size=target_size
    )

    if offset != 0 or (target_size is not None and target_size != scale):
        ret = StructAccess(
            struct_var=ret_ref,
            offset=offset,
            target_size=target_size,
            field_path=field_path,
            stack_info=stack_info,
            type=field_type,
        )

    if ptr:
        ret = AddressOf(ret, type=ret.type.reference())

    return ret


def handle_add(args: InstrArgs) -> Expression:
    output_reg = args.reg_ref(0)
    lhs = args.reg(1)
    rhs = args.reg(2)

    # addiu instructions can sometimes be emitted as addu instead, when the
    # offset is too large.
    if isinstance(rhs, Literal):
        return handle_addi_real(output_reg, args.reg_ref(1), lhs, rhs, args)
    if isinstance(lhs, Literal):
        return handle_addi_real(output_reg, args.reg_ref(2), rhs, lhs, args)

    return handle_add_real(output_reg, lhs, rhs, args)


def handle_add_real(
    output_reg: Register,
    lhs: Expression,
    rhs: Expression,
    args: InstrArgs,
) -> Expression:
    stack_info = args.stack_info

    type = Type.intptr()
    # Because lhs & rhs are in registers, it shouldn't be possible for them to be arrays.
    # If they are, treat them the same as pointers anyways.
    if lhs.type.is_pointer_or_array():
        type = Type.ptr()
    elif rhs.type.is_pointer_or_array():
        type = Type.ptr()

    expr = BinaryOp(left=as_intptr(lhs), op="+", right=as_intptr(rhs), type=type)
    folded_expr = fold_mul_chains(expr)
    if isinstance(folded_expr, BinaryOp):
        folded_expr = fold_divmod(folded_expr)
    if folded_expr is not expr:
        return folded_expr
    array_expr = array_access_from_add(expr, 0, stack_info, target_size=None, ptr=True)
    if array_expr is not None:
        return array_expr
    return expr


def handle_add_float(args: InstrArgs) -> Expression:
    if args.reg_ref(1) == args.reg_ref(2):
        two = Literal(1 << 30, type=Type.f32())
        return BinaryOp.f32(two, "*", args.reg(1))
    return BinaryOp.f32(args.reg(1), "+", args.reg(2))


def handle_add_double(args: InstrArgs) -> Expression:
    if args.reg_ref(1) == args.reg_ref(2):
        two = Literal(1 << 62, type=Type.f64())
        return BinaryOp.f64(two, "*", args.dreg(1))
    return BinaryOp.f64(args.dreg(1), "+", args.dreg(2))


def fold_shift_bgez(expr: Expression) -> Optional[Condition]:
    uw_expr = early_unwrap(expr)
    if not isinstance(uw_expr, BinaryOp) or not isinstance(uw_expr.right, Literal):
        return None
    value = uw_expr.right.value
    if uw_expr.op == "<<":
        shift = value
    elif uw_expr.op == "*" and value > 0 and (value & (value - 1)) == 0:
        shift = value.bit_length() - 1
    else:
        return None
    bitand = BinaryOp.int(uw_expr.left, "&", Literal(1 << (31 - shift)))
    return UnaryOp("!", bitand, type=Type.bool())


def handle_bgez(args: InstrArgs) -> Condition:
    expr = args.reg(0)
    return fold_shift_bgez(expr) or BinaryOp.scmp(expr, ">=", Literal(0))


def rlwi_mask(mask_begin: int, mask_end: int) -> int:
    # Compute the mask constant used by the rlwi* family of PPC instructions,
    # referred to as the `MASK(MB, ME)` function in the processor manual.
    # Bit 0 is the MSB, Bit 31 is the LSB
    bits_upto: Callable[[int], int] = lambda m: (1 << (32 - m)) - 1
    all_ones = 0xFFFFFFFF
    if mask_begin <= mask_end:
        # Set bits inside the range, fully inclusive
        mask = bits_upto(mask_begin) - bits_upto(mask_end + 1)
    else:
        # Set bits from [31, mask_end] and [mask_begin, 0]
        mask = (bits_upto(mask_end + 1) - bits_upto(mask_begin)) ^ all_ones
    return mask


def handle_rlwinm(
    source: Expression,
    shift: int,
    mask_begin: int,
    mask_end: int,
    simplify: bool = True,
) -> Expression:
    # TODO: Detect shift + truncate, like `(x << 2) & 0xFFF3` or `(x >> 2) & 0x3FFF`

    # The output of the rlwinm instruction is `ROTL(source, shift) & mask`. We write this as
    # ((source << shift) & mask) | ((source >> (32 - shift)) & mask)
    # and compute both OR operands (upper_bits and lower_bits respectively).
    all_ones = 0xFFFFFFFF
    mask = rlwi_mask(mask_begin, mask_end)
    left_shift = shift
    right_shift = 32 - shift
    left_mask = (all_ones << left_shift) & mask
    right_mask = (all_ones >> right_shift) & mask

    # We only simplify if the `simplify` argument is True, and there will be no `|` in the
    # resulting expression. If there is an `|`, the expression is best left as bitwise math
    simplify = simplify and not (left_mask and right_mask)

    if isinstance(source, Literal):
        upper_value = (source.value << left_shift) & mask
        lower_value = (source.value >> right_shift) & mask
        return Literal(upper_value | lower_value)

    upper_bits: Optional[Expression]
    if left_mask == 0:
        upper_bits = None
    else:
        upper_bits = source
        if left_shift != 0:
            upper_bits = BinaryOp.int(
                left=upper_bits, op="<<", right=Literal(left_shift)
            )

        if simplify:
            upper_bits = fold_mul_chains(upper_bits)

        if left_mask != (all_ones << left_shift) & all_ones:
            upper_bits = BinaryOp.int(left=upper_bits, op="&", right=Literal(left_mask))
            if simplify:
                upper_bits = replace_bitand(upper_bits)

    lower_bits: Optional[Expression]
    if right_mask == 0:
        lower_bits = None
    else:
        lower_bits = BinaryOp.uint(left=source, op=">>", right=Literal(right_shift))

        if simplify:
            lower_bits = replace_clz_shift(fold_divmod(lower_bits))

        if right_mask != (all_ones >> right_shift) & all_ones:
            lower_bits = BinaryOp.int(
                left=lower_bits, op="&", right=Literal(right_mask)
            )
            if simplify:
                lower_bits = replace_bitand(lower_bits)

    if upper_bits is None and lower_bits is None:
        return Literal(0)
    elif upper_bits is None:
        assert lower_bits is not None
        return lower_bits
    elif lower_bits is None:
        return upper_bits
    else:
        return BinaryOp.int(left=upper_bits, op="|", right=lower_bits)


def handle_rlwimi(
    base: Expression, source: Expression, shift: int, mask_begin: int, mask_end: int
) -> Expression:
    # This instruction reads from `base`, replaces some bits with values from `source`, then
    # writes the result back into the first register. This can be used to copy any contiguous
    # bitfield from `source` into `base`, and is commonly used when manipulating flags, such
    # as in `x |= 0x10` or `x &= ~0x10`.

    # It's generally more readable to write the mask with `~` (instead of computing the inverse here)
    mask_literal = Literal(rlwi_mask(mask_begin, mask_end))
    mask = UnaryOp("~", mask_literal, type=Type.u32())
    masked_base = BinaryOp.int(left=base, op="&", right=mask)
    if source == Literal(0):
        # If the source is 0, there are no bits inserted. (This may look like `x &= ~0x10`)
        return masked_base
    # Set `simplify=False` to keep the `inserted` expression as bitwise math instead of `*` or `/`
    inserted = handle_rlwinm(source, shift, mask_begin, mask_end, simplify=False)
    if inserted == mask_literal:
        # If this instruction will set all the bits in the mask, we can OR the values
        # together without masking the base. (`x |= 0xF0` instead of `x = (x & ~0xF0) | 0xF0`)
        return BinaryOp.int(left=base, op="|", right=inserted)
    return BinaryOp.int(left=masked_base, op="|", right=inserted)


def handle_loadx(args: InstrArgs, type: Type) -> Expression:
    # "indexed loads" like `lwzx rD, rA, rB` read `(rA + rB)` into `rD`
    size = type.get_size_bytes()
    assert size is not None

    ptr = BinaryOp.intptr(left=args.reg(1), op="+", right=args.reg(2))
    expr = deref(ptr, args.regs, args.stack_info, size=size)
    return as_type(expr, type, silent=True)


def carry_add_to(expr: Expression) -> BinaryOp:
    return fold_divmod(BinaryOp.intptr(expr, "+", CarryBit()))


def carry_sub_from(expr: Expression) -> BinaryOp:
    return BinaryOp.intptr(expr, "-", UnaryOp("!", CarryBit(), type=Type.intish()))
