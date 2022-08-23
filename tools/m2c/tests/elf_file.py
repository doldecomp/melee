import struct
from dataclasses import dataclass, field
from typing import Any, Dict, List, Optional, Tuple


# Based on the ELF file parser in simonlindholm's asm-differ ("diff.py")
# https://github.com/simonlindholm/asm-differ/blob/4b38c884c1efdc3bfa8b14f13015a69368a8d3a2/diff.py#L1137-L1247


@dataclass(order=True)
class ElfSymbol:
    offset: int
    name: str
    section: Optional["ElfSection"]


@dataclass(order=True)
class ElfRelocation:
    section_offset: int
    symbol: ElfSymbol
    symbol_offset: int
    relocation_type: int


@dataclass
class ElfSection:
    address: int
    name: str
    data: bytes = field(repr=False)
    relocations: Dict[int, ElfRelocation] = field(default_factory=dict, repr=False)
    symbols: Dict[int, ElfSymbol] = field(default_factory=dict, repr=False)


@dataclass
class ElfFile:
    sections: Dict[str, ElfSection] = field(default_factory=dict)
    symbols: Dict[str, ElfSymbol] = field(default_factory=dict)

    @staticmethod
    def parse(data: bytes) -> "ElfFile":
        if not data:
            raise ValueError("Input data is empty")
        e_ident = data[:16]
        if e_ident[:4] != b"\x7FELF":
            raise ValueError(
                f"Input data is not an ELF file (magic number is {e_ident[:4]!r})"
            )

        SHT_PROGBITS = 1
        SHT_SYMTAB = 2
        SHT_STRTAB = 3
        SHT_NOBITS = 8
        SHT_REL = 9
        SHT_RELA = 4

        is_32bit = e_ident[4] == 1
        is_little_endian = e_ident[5] == 1
        str_end = "<" if is_little_endian else ">"
        str_off = "I" if is_32bit else "Q"

        def read(spec: str, offset: int) -> Tuple[int, ...]:
            spec = spec.replace("P", str_off)
            size = struct.calcsize(spec)
            return struct.unpack(str_end + spec, data[offset : offset + size])

        def read_string(base: int, offset: int) -> str:
            if base == 0 or offset == 0:
                return ""
            offset += base
            return data[offset : data.index(b"\0", offset)].decode("latin1")

        (
            e_type,
            e_machine,
            e_version,
            e_entry,
            e_phoff,
            e_shoff,
            e_flags,
            e_ehsize,
            e_phentsize,
            e_phnum,
            e_shentsize,
            e_shnum,
            e_shstrndx,
        ) = read("HHIPPPIHHHHHH", 16)
        if e_type != 1:  # relocatable
            raise ValueError(f"Input elf is not relocatable (e_type = {e_type})")
        assert e_shoff != 0
        assert e_shnum != 0  # don't support > 0xFF00 sections
        assert e_shstrndx != 0

        @dataclass
        class Section:
            sh_name: int
            sh_type: int
            sh_flags: int
            sh_addr: int
            sh_offset: int
            sh_size: int
            sh_link: int
            sh_info: int
            sh_addralign: int
            sh_entsize: int

        sections = [
            Section(*read("IIPPPPIIPP", e_shoff + i * e_shentsize))
            for i in range(e_shnum)
        ]
        shstrtab_offset = sections[e_shstrndx].sh_offset
        sec_names = [read_string(shstrtab_offset, s.sh_name) for s in sections]

        strtab_sections = [
            i
            for i in range(e_shnum)
            if sections[i].sh_type == SHT_STRTAB and i != e_shstrndx
        ]
        assert len(strtab_sections) == 1
        strtab_offset = sections[strtab_sections[0]].sh_offset

        symtab_sections = [
            i for i in range(e_shnum) if sections[i].sh_type == SHT_SYMTAB
        ]
        assert len(symtab_sections) == 1
        symtab = sections[symtab_sections[0]]

        elf = ElfFile()

        # Parse SHT_PROGBIT/SHT_NOBITS sections (.text, .data, .bss, etc.)
        for s, name in zip(sections, sec_names):
            if s.sh_type == SHT_PROGBITS:
                if name == ".comment" or name.startswith(".note"):
                    continue
                section_data = data[s.sh_offset : s.sh_offset + s.sh_size]
                elf.sections[name] = ElfSection(
                    address=s.sh_addr, name=name, data=section_data
                )
            elif s.sh_type == SHT_NOBITS and s.sh_size != 0:
                section_data = b"\0" * s.sh_size
                elf.sections[name] = ElfSection(
                    address=s.sh_addr, name=name, data=section_data
                )

        # Parse SHT_SYMTAB section (symbol table)
        symbols_by_index: List[ElfSymbol] = []
        for offset in range(0, symtab.sh_size, symtab.sh_entsize):
            if is_32bit:
                sym_offset = symtab.sh_offset + offset
                st_name, st_value, st_size, st_info, st_other, st_shndx = read(
                    "IIIBBH", sym_offset
                )
            else:
                sym_offset = symtab.sh_offset + offset
                st_name, st_info, st_other, st_shndx, st_value, st_size = read(
                    "IBBHQQ", sym_offset
                )
            sym_name = read_string(strtab_offset, st_name)
            if st_shndx == 0 or st_shndx >= 0xFF00:
                section = None
            else:
                section = elf.sections.get(sec_names[st_shndx])

            symbol = ElfSymbol(offset=st_value, name=sym_name, section=section)
            elf.symbols[sym_name] = symbol
            symbols_by_index.append(symbol)
            # Do not overwrite existing symbols at this address, and skip
            # empty names or names starting with "..." (such as `...bss@0`).
            if (
                section is not None
                and st_value not in section.symbols
                and sym_name
                and not sym_name.startswith("...")
            ):
                section.symbols[st_value] = symbol

        # Parse SHT_REL/SHT_RELA sections (relocations)
        for s, name in zip(sections, sec_names):
            if s.sh_type == SHT_REL or s.sh_type == SHT_RELA:
                sec_name = sec_names[s.sh_info]
                section = elf.sections.get(sec_name)
                if section is None:
                    continue

                sec_base = sections[s.sh_info].sh_offset
                for i in range(0, s.sh_size, s.sh_entsize):
                    if s.sh_type == SHT_REL:
                        r_offset, r_info = read("PP", s.sh_offset + i)
                    else:
                        r_offset, r_info, r_addend = read("PPP", s.sh_offset + i)

                    if is_32bit:
                        r_sym = r_info >> 8
                        r_type = r_info & 0xFF
                    else:
                        r_sym = r_info >> 32
                        r_type = r_info & 0xFFFFFFFF

                    symbol = symbols_by_index[r_sym]

                    # Caonicalize the symbol, in case there are multiple symbols at the same offset
                    if symbol.section is not None:
                        symbol = symbol.section.symbols[symbol.offset]

                    if s.sh_type == SHT_REL:
                        # NB: This isn't needed for PPC, but we may want to re-use this code later.
                        # We will also need to add support for R_MIPS_{LO16,HI16,26}.
                        # (PPC uses RELA relocations, which embed the addend in the relocation
                        # instead of in the relocated section.)
                        if e_machine == 8 and r_type == 2:  # R_MIPS_32
                            (r_addend,) = read("I", sec_base + r_offset)
                        else:
                            continue

                    reloc = ElfRelocation(
                        section_offset=r_offset,
                        symbol=symbol,
                        symbol_offset=r_addend,
                        relocation_type=r_type,
                    )
                    section.relocations[r_offset] = reloc

        return elf
