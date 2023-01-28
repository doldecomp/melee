import struct
import sys
import capstone as cs
from typing import Any, BinaryIO, List, Optional, Set, TextIO, Tuple
from elf_file import ElfFile, ElfSection, ElfSymbol

# Based on `doldisasm.py` from camthesaxman:
# https://gist.github.com/camthesaxman/a36f610dbf4cc53a874322ef146c4123

CsMnemonic = int
CsRegister = int


MANUAL_MNEMONICS: Set[CsMnemonic] = {
    # Unsupported instructions
    cs.ppc.PPC_INS_VMSUMSHM,
    cs.ppc.PPC_INS_VMHADDSHS,
    cs.ppc.PPC_INS_XXSLDWI,
    cs.ppc.PPC_INS_VSEL,
    cs.ppc.PPC_INS_XVSUBSP,
    cs.ppc.PPC_INS_XXSEL,
    cs.ppc.PPC_INS_XVMULSP,
    cs.ppc.PPC_INS_XVDIVSP,
    cs.ppc.PPC_INS_VADDUHM,
    cs.ppc.PPC_INS_XXPERMDI,
    cs.ppc.PPC_INS_XVMADDASP,
    cs.ppc.PPC_INS_XVMADDMSP,
    cs.ppc.PPC_INS_XVCMPGTSP,
    cs.ppc.PPC_INS_XXMRGHD,
    cs.ppc.PPC_INS_XSMSUBMDP,
    cs.ppc.PPC_INS_XSTDIVDP,
    cs.ppc.PPC_INS_XVADDSP,
    cs.ppc.PPC_INS_XVCMPEQSP,
    cs.ppc.PPC_INS_XVMSUBASP,
    cs.ppc.PPC_INS_XVCMPGESP,
    # Instructions that Capstone gets wrong
    cs.ppc.PPC_INS_MFESR,
    cs.ppc.PPC_INS_MFDEAR,
    cs.ppc.PPC_INS_MTESR,
    cs.ppc.PPC_INS_MTDEAR,
    cs.ppc.PPC_INS_MFICCR,
    cs.ppc.PPC_INS_MFASR,
}

LOAD_STORE_MNEMONICS: Set[CsMnemonic] = {
    cs.ppc.PPC_INS_LWZ,
    cs.ppc.PPC_INS_LMW,
    cs.ppc.PPC_INS_LHA,
    cs.ppc.PPC_INS_LHAU,
    cs.ppc.PPC_INS_LHZ,
    cs.ppc.PPC_INS_LHZU,
    cs.ppc.PPC_INS_LBZ,
    cs.ppc.PPC_INS_LBZU,
    cs.ppc.PPC_INS_LFD,
    cs.ppc.PPC_INS_LFDU,
    cs.ppc.PPC_INS_LFS,
    cs.ppc.PPC_INS_LFSU,
    cs.ppc.PPC_INS_STW,
    cs.ppc.PPC_INS_STWU,
    cs.ppc.PPC_INS_STMW,
    cs.ppc.PPC_INS_STH,
    cs.ppc.PPC_INS_STHU,
    cs.ppc.PPC_INS_STB,
    cs.ppc.PPC_INS_STBU,
    cs.ppc.PPC_INS_STFS,
    cs.ppc.PPC_INS_STFSU,
    cs.ppc.PPC_INS_STFD,
    cs.ppc.PPC_INS_STDU,
}

# TODO: Is there an attribute exposed by capstone that we can use instead of this
# hardcoded list? (This list is known to be missing most branch mnemonics)
BRANCH_MNEMONICS: Set[CsMnemonic] = {
    cs.ppc.PPC_INS_B,
    cs.ppc.PPC_INS_BL,
    cs.ppc.PPC_INS_BDZ,
    cs.ppc.PPC_INS_BDNZ,
    cs.ppc.PPC_INS_BC,
}

# These name substitutions are performed by doldisasm.py so that all symbols
# and labels in the output asm only use alphanumerics and '$'
SUBSTITUTIONS: Tuple[Tuple[str, str], ...] = (
    ("<", "$$0"),
    (">", "$$1"),
    ("@", "$$2"),
    ("\\", "$$3"),
    (",", "$$4"),
    ("-", "$$5"),
)


def symbol_name(sym: ElfSymbol) -> str:
    name = sym.name
    for sub in SUBSTITUTIONS:
        name = name.replace(*sub)
    return name


def address_label(addr: int) -> str:
    return f".L{addr:08X}"


# Returns true if the instruction is a load or store with the given register as a base
def is_load_store_reg_offset(insn: cs.CsInsn, reg: Optional[CsRegister]) -> bool:
    return insn.id in LOAD_STORE_MNEMONICS and (
        reg == None or insn.operands[1].mem.base == reg
    )


# Converts the instruction to a string, fixing various issues with Capstone
def instruction_to_text(
    insn: cs.CsInsn, raw: int, section: ElfSection
) -> Optional[str]:
    # Look up the relocation for this address, which is either at offset+0 or offset+2
    # (It should be possible to determine which offset to use from either the relocation
    # type or the instruction mnemonic, but for now just check both since they should
    # be mutually exclusive.)
    offset = insn.address - section.address
    reloc = section.relocations.get(offset)
    if reloc is None:
        reloc = section.relocations.get(offset + 2)

    label: Optional[str] = None
    if reloc is not None:
        label = symbol_name(reloc.symbol)
    elif insn.operands:
        label_addr = insn.operands[0].imm
        symbol = section.symbols.get(label_addr)
        if symbol is not None:
            label = symbol_name(symbol)
        else:
            label = address_label(label_addr)

    # Probably data, not a real instruction
    if insn.id == cs.ppc.PPC_INS_BDNZ and (insn.bytes[0] & 1):
        return None
    if insn.id in BRANCH_MNEMONICS:
        if not label:
            return "%s %s" % (
                insn.mnemonic,
                f"unk label: {(raw, insn.address - section.address)}",
            )
            return None
        return "%s %s" % (insn.mnemonic, label)
    elif insn.id == cs.ppc.PPC_INS_BC:
        branchPred = "+" if (insn.bytes[1] & 0x20) else ""
        if not insn.operands:
            pass
        elif insn.operands[0].type == cs.ppc.PPC_OP_IMM:
            if not label:
                return None
            return "%s%s %s" % (
                insn.mnemonic,
                branchPred,
                label,
            )
        elif insn.operands[1].type == cs.ppc.PPC_OP_IMM:
            if not label:
                return None
            return "%s%s %s, %s" % (
                insn.mnemonic,
                branchPred,
                insn.reg_name(insn.operands[0].value.reg),
                label,
            )
    if reloc is not None:
        assert label is not None
        # r13 offset loads
        if (
            insn.id == cs.ppc.PPC_INS_ADDI
            and insn.operands[1].reg == cs.ppc.PPC_REG_R13
        ):
            return "%s %s, %s, %s@sda21" % (
                insn.mnemonic,
                insn.reg_name(insn.operands[0].reg),
                insn.reg_name(insn.operands[1].reg),
                label,
            )

        # r2 offset loads
        if insn.id == cs.ppc.PPC_INS_ADDI and insn.operands[1].reg == cs.ppc.PPC_REG_R2:
            return "%s %s, %s, %s@sda2" % (
                insn.mnemonic,
                insn.reg_name(insn.operands[0].reg),
                insn.reg_name(insn.operands[1].reg),
                label,
            )

        # Reloc R_PPC_EMB_SDA21, the linker sets the register to either
        # $r13 or $r2 based on the section name.
        if reloc.relocation_type == 109:
            if reloc.symbol.section is None:
                reg = "r0"
            elif reloc.symbol.section.name.endswith("2"):
                reg = "r13"
            else:
                reg = "r2"
            if insn.id == cs.ppc.PPC_INS_LI:
                return "addi %s, %s, %s@sda21" % (
                    insn.reg_name(insn.operands[0].value.reg),
                    reg,
                    label,
                )
            else:
                return "%s %s, %s@sda21(%s)" % (
                    insn.mnemonic,
                    insn.reg_name(insn.operands[0].value.reg),
                    label,
                    reg,
                )

        # Handle split loads (high part)
        if insn.id == cs.ppc.PPC_INS_LIS:
            suffix = "h" if reloc.relocation_type == 5 else "ha"
            return "%s %s, %s@%s" % (
                insn.mnemonic,
                insn.reg_name(insn.operands[0].reg),
                label,
                suffix,
            )
        # Handle split loads (low part)
        if insn.id in {cs.ppc.PPC_INS_ADDI, cs.ppc.PPC_INS_ORI}:
            return "%s %s, %s, %s@l" % (
                insn.mnemonic,
                insn.reg_name(insn.operands[0].reg),
                insn.reg_name(insn.operands[1].reg),
                label,
            )
        if is_load_store_reg_offset(insn, None):
            return "%s %s, %s@l(%s)" % (
                insn.mnemonic,
                insn.reg_name(insn.operands[0].reg),
                label,
                insn.reg_name(insn.operands[1].mem.base),
            )

    # Sign-extend immediate values (Capstone doesn't do that automatically)
    if insn.id in {
        cs.ppc.PPC_INS_ADDI,
        cs.ppc.PPC_INS_ADDIC,
        cs.ppc.PPC_INS_SUBFIC,
        cs.ppc.PPC_INS_MULLI,
    } and (insn.operands[2].imm & 0x8000):
        return "%s %s, %s, %i" % (
            insn.mnemonic,
            insn.reg_name(insn.operands[0].reg),
            insn.reg_name(insn.operands[1].value.reg),
            insn.operands[2].imm - 0x10000,
        )
    elif (insn.id == cs.ppc.PPC_INS_LI or insn.id == cs.ppc.PPC_INS_CMPWI) and (
        insn.operands[1].imm & 0x8000
    ):
        return "%s %s, %i" % (
            insn.mnemonic,
            insn.reg_name(insn.operands[0].reg),
            insn.operands[1].imm - 0x10000,
        )
    # cntlz -> cntlzw
    elif insn.id == cs.ppc.PPC_INS_CNTLZW:
        return "cntlzw %s" % insn.op_str
    elif insn.id == cs.ppc.PPC_INS_MTICCR:
        return "mtictc %s" % insn.op_str
    # Dunno why GNU assembler doesn't accept this
    elif insn.id == cs.ppc.PPC_INS_LMW and insn.operands[0].reg == cs.ppc.PPC_REG_R0:
        return ".4byte 0x%08X  /* illegal %s %s */" % (raw, insn.mnemonic, insn.op_str)
    return "%s %s" % (insn.mnemonic, insn.op_str)


def disasm_ps(inst: int) -> Optional[str]:
    RA = (inst >> 16) & 0x1F
    RB = (inst >> 11) & 0x1F
    FA = (inst >> 16) & 0x1F
    FB = (inst >> 11) & 0x1F
    FC = (inst >> 6) & 0x1F
    FD = (inst >> 21) & 0x1F
    FS = (inst >> 21) & 0x1F
    IX = (inst >> 7) & 0x7
    WX = (inst >> 10) & 0x1

    opcode = (inst >> 1) & 0x1F
    if opcode == 6:  # doesn't seem to be used
        mnemonic = "psq_lux" if inst & 0x40 else "psq_lx"
        return "%s f%i, (r%i + r%i), %i, qr%i" % (mnemonic, FD, RA, RB, WX, IX)
    if opcode == 7:
        mnemonic = "psq_stux" if inst & 0x40 else "psq_stx"
        return "%s f%i, r%i, r%i, %i, qr%i" % (mnemonic, FS, RA, RB, WX, IX)
    if opcode == 18:
        return "ps_div f%i, f%i, f%i" % (FD, FA, FB)
    if opcode == 20:
        return "ps_sub f%i, f%i, f%i" % (FD, FA, FB)
    if opcode == 21:
        return "ps_add f%i, f%i, f%i" % (FD, FA, FB)
    if opcode == 23:
        return "ps_sel f%i, f%i, f%i" % (FD, FA, FC)
    if opcode == 24:
        return "ps_res f%i, f%i" % (FD, FB)
    if opcode == 25:
        return "ps_mul f%i, f%i, f%i" % (FD, FA, FC)
    if opcode == 26:
        return "ps_rsqrte f%i, f%i" % (FD, FB)
    if opcode == 28:
        return "ps_msub f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)
    if opcode == 29:
        return "ps_madd f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)
    if opcode == 30:
        return "ps_nmsub f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)
    if opcode == 31:
        return "ps_nmadd f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)
    if opcode == 10:
        return "ps_sum0 f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)
    if opcode == 11:
        return "ps_sum1 f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)
    if opcode == 12:
        return "ps_muls0 f%i, f%i, f%i" % (FD, FA, FC)
    if opcode == 13:
        return "ps_muls1 f%i, f%i, f%i" % (FD, FA, FC)
    if opcode == 14:
        return "ps_madds0 f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)
    if opcode == 15:
        return "ps_madds1 f%i, f%i, f%i, f%i" % (FD, FA, FC, FB)

    opcode = (inst >> 1) & 0x3FF
    if opcode == 40:
        return "ps_neg f%i, f%i" % (FD, FB)
    if opcode == 72:
        return "ps_mr f%i, f%i" % (FD, FB)
    if opcode == 136:
        return "ps_nabs f%i, f%i" % (FD, FB)
    if opcode == 264:
        return "ps_abs f%i, f%i" % (FD, FB)
    if opcode in {0, 32, 64, 96}:
        mnemonics = ["ps_cmpu0", "ps_cmpo0", "ps_cmpu1", "ps_cmpo1"]
        mnemonic = mnemonics[(inst >> 6) & 3]
        i = (inst & 0x03800000) >> 23
        return "%s cr%i, f%i, f%i" % (mnemonic, i, FA, FB)
    if opcode == 528:
        return "ps_merge00 f%i, f%i, f%i" % (FD, FA, FB)
    if opcode == 560:
        return "ps_merge01 f%i, f%i, f%i" % (FD, FA, FB)
    if opcode == 592:
        return "ps_merge10 f%i, f%i, f%i" % (FD, FA, FB)
    if opcode == 624:
        return "ps_merge11 f%i, f%i, f%i" % (FD, FA, FB)
    if opcode == 1014:
        if not (inst & 0x03E00000):
            if (inst & 1) == 0:
                return "dcbz_l r%i, r%i" % (
                    (inst & 0x001F0000) >> 16,
                    (inst & 0x0000F800) >> 11,
                )
    return None


def sign_extend_12(value: int) -> int:
    if value > 0 and (value & 0x800):
        value -= 0x1000
    return value


def disasm_ps_mem(inst: int, idx: int) -> str:
    RA = (inst >> 16) & 0x1F
    RS = (inst >> 21) & 0x1F
    I = (inst >> 12) & 0x7
    W = (inst >> 15) & 0x1
    disp = sign_extend_12(inst & 0xFFF)
    if idx == 56:
        mnemonic = "psq_l"
    if idx == 57:
        mnemonic = "psq_lu"
    if idx == 60:
        mnemonic = "psq_st"
    if idx == 61:
        mnemonic = "psq_stu"
    return "%s f%i, %i(r%i), %i, qr%i" % (mnemonic, RS, disp, RA, W, I)


def disasm_fcmp(inst: int) -> str:
    crd = (inst & 0x03800000) >> 23
    a = (inst & 0x001F0000) >> 16
    b = (inst & 0x0000F800) >> 11
    return "fcmpo cr%i, f%i, f%i" % (crd, a, b)


def disasm_mspr(inst: int, mode: int) -> Optional[str]:
    if inst & 1:
        return None
    d = (inst & 0x03E00000) >> 21
    a = (inst & 0x001F0000) >> 16
    b = (inst & 0x0000F800) >> 11
    spr = (b << 5) + a
    if mode:
        return "mtspr 0x%X, r%i" % (spr, d)
    else:
        return "mfspr r%i, 0x%X" % (d, spr)


def disasm_mcrxr(inst: int) -> Optional[str]:
    if inst & 0x007FF801:
        return None
    crd = (inst & 0x03800000) >> 23
    return "mcrxr cr%i" % crd


# Disassemble code
def disassemble_instruction(
    address: int,
    insn: Optional[cs.CsInsn],
    raw_bytes: bytes,
    section: ElfSection,
    output: TextIO,
) -> None:
    # Output symbol label (if any)
    offset = address - section.address
    symbol = section.symbols.get(offset)
    if symbol is not None:
        if not symbol.name.startswith("lbl_"):
            output.write(f"\n.global {symbol_name(symbol)}\n")
        output.write(f"{symbol_name(symbol)}:\n")

    prefixComment = "/* %08X %08X  %02X %02X %02X %02X */" % (
        address,
        offset,
        raw_bytes[0],
        raw_bytes[1],
        raw_bytes[2],
        raw_bytes[3],
    )
    asm = None
    raw = struct.unpack(">I", raw_bytes)[0]
    if insn is not None:
        asm = instruction_to_text(insn, raw, section)
    else:  # Capstone couldn't disassemble it
        idx = (raw & 0xFC000000) >> 26
        idx2 = (raw & 0x000007FE) >> 1
        # mtspr
        if idx == 31 and idx2 == 467:
            asm = disasm_mspr(raw, 1)
        # mfspr
        elif idx == 31 and idx2 == 339:
            asm = disasm_mspr(raw, 0)
        # mcrxr
        elif idx == 31 and idx2 == 512:
            asm = disasm_mcrxr(raw)
        # fcmpo
        elif idx == 63 and idx2 == 32:
            asm = disasm_fcmp(raw)
        # Paired singles
        elif idx == 4:
            asm = disasm_ps(raw)
        elif idx in {56, 57, 60, 61}:
            asm = disasm_ps_mem(raw, idx)
    if asm == None:
        asm = f".4byte 0x{raw:08X}  /* unknown instruction */"
    output.write(f"{prefixComment}\t{asm}\n")


def disassemble_bytes(
    cap: cs.Cs, base_address: int, data: bytes
) -> List[Tuple[Optional[cs.CsInsn], int, bytes]]:
    output: List[Tuple[Optional[cs.CsInsn], int, bytes]] = []
    offset = 0
    end = len(data)
    while offset < end:
        code = data[offset:end]
        for insn in cap.disasm(code, base_address + offset):
            if insn.id in MANUAL_MNEMONICS:
                output.append((None, insn.address, insn.bytes))
            else:
                output.append((insn, insn.address, insn.bytes))
            offset += 4
        if offset < end:
            address = base_address + offset
            output.append((None, address, data[offset : offset + 4]))
            offset += 4
    return output


def disassemble_ppc_text_section(section: ElfSection, output: TextIO) -> None:
    cap = cs.Cs(cs.CS_ARCH_PPC, cs.CS_MODE_32 | cs.CS_MODE_BIG_ENDIAN)
    cap.detail = True
    cap.imm_unsigned = False

    disassembly = disassemble_bytes(cap, section.address, section.data)

    extra_labels: Set[int] = set()
    for insn, addr, _ in disassembly:
        offset = addr - section.address
        if (
            insn is not None
            and insn.id in BRANCH_MNEMONICS
            and insn.operands[0].imm not in section.symbols
            and offset not in section.relocations
            and offset + 2 not in section.relocations
        ):
            extra_labels.add(insn.operands[0].imm)

    for insn, addr, raw in disassembly:
        if addr in extra_labels:
            output.write(f"{address_label(addr)}:\n")
        disassemble_instruction(addr, insn, raw, section, output)


def disassemble_data_section(section: ElfSection, output: TextIO) -> None:
    def output_slice(start: int, end: int) -> None:
        i = start
        while i < end:
            reloc = section.relocations.get(i)

            if i & 3 != 0:
                next_i = min((i & ~3) + 4, end)
            else:
                next_i = min(i + 4, end)
            assert i < next_i <= end
            word = section.data[i:next_i]
            i = next_i

            if reloc is not None:
                assert len(word) == 4
                suffix = f"({reloc.symbol_offset})" if reloc.symbol_offset else ""
                output.write(f"\t.word {symbol_name(reloc.symbol)}{suffix}\n")
            elif len(word) == 4:
                output.write(
                    "\t.word 0x" + "".join(hex(x)[2:].zfill(2) for x in word) + "\n"
                )
            else:
                output.write("\t.bytes " + ", ".join(hex(x) for x in word) + "\n")

    offset = 0
    for symbol in sorted(section.symbols.values()):
        if not symbol.name:
            continue
        output_slice(offset, symbol.offset)
        offset = symbol.offset
        output.write(f"\n.global {symbol_name(symbol)}\n")
        output.write(f"{symbol_name(symbol)}:\n")
    output_slice(offset, len(section.data))


def disassemble_ppc_elf(elf_in: BinaryIO, asm_out: TextIO) -> None:
    elf = ElfFile.parse(elf_in.read())
    asm_out.write('.include "macros.inc"\n\n')

    for section in elf.sections.values():
        asm_out.write(
            f".section {section.name}  # {section.address:#x} - {section.address + len(section.data):#x}\n"
        )
        if section.name == ".text":
            disassemble_ppc_text_section(section, asm_out)
        else:
            disassemble_data_section(section, asm_out)
        asm_out.write("\n")


if __name__ == "__main__":
    disassemble_ppc_elf(sys.stdin.buffer, sys.stdout)
