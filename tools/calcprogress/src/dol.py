from dataclasses import dataclass
from enum import IntEnum

from .input_stream import InputStream


@dataclass
class Section:
    """DOL section
    """
    offset: int
    address: int
    size: int
    type: int
    data: bytes

    def __repr__(self) -> str:
        return f"local:{hex(self.address & 0xFFFFFFFF)}, vaddr:{hex(self.address & 0xFFFFFFFF)}, sz:{hex(self.size & 0xFFFFFFFF)}"

    def end(self) -> int:
        return self.address + self.size


@dataclass
class Dol():
    """Wii/GC executable
    """

    class SectionType(IntEnum):
        """Possible types of DOL sections
        """
        CODE = 0
        DATA = 1

    sections: list[Section]
    bss: Section
    _code_size: int
    _data_size: int

    # Maximum section count in DOL
    MAX_SECTIONS = 18
    # Maximum code section count in DOL
    MAX_CODE_SECTIONS = 7
    # Maximum data section count in DOL
    MAX_DATA_SECTIONS = 11

    def __init__(self, path: str) -> "Dol":
        """Read DOL file from path
        """

        # Open stream to file
        stream = InputStream.open_file(path, InputStream.ENDIAN_BIG)

        # DOL section offsets
        offsets = []
        for i in range(Dol.MAX_SECTIONS):
            offsets.append(stream.get_u32())
        # DOL section starting addresses
        addresses = []
        for i in range(Dol.MAX_SECTIONS):
            addresses.append(stream.get_u32())
        # DOL section sizes
        sizes = []
        for i in range(Dol.MAX_SECTIONS):
            sizes.append(stream.get_u32())

        # BSS section info
        bss_addr = stream.get_u32()
        bss_size = stream.get_u32()

        # Read section data
        data = []
        for i in range(Dol.MAX_SECTIONS):
            # Check for unused section
            if offsets[i] == 0 or addresses[i] == 0 or sizes[i] == 0:
                data.append(bytes())
            else:
                # Seek to data offset and read section
                stream.seek(offsets[i], InputStream.SEEK_BEGIN)
                data.append(stream.read(sizes[i]))

        self.sections = []
        # Construct code sections (0-7)
        self._code_size = 0
        for i in range(0, Dol.MAX_CODE_SECTIONS):
            self.sections.append(
                Section(offsets[i], addresses[i], sizes[i], Dol.SectionType.CODE, data[i]))
            self._code_size += sizes[i]
        # Construct data sections (11-18)
        self._data_size = 0
        for i in range(Dol.MAX_CODE_SECTIONS, Dol.MAX_SECTIONS):
            self.sections.append(
                Section(offsets[i], addresses[i], sizes[i], Dol.SectionType.DATA, data[i]))
            self._data_size += sizes[i]

        # Construct BSS section
        self.bss = Section(-1, bss_addr, bss_size,
                           Dol.SectionType.DATA, bytes(bss_size))
        self.sections.append(self.bss)

        # Sort sections by their virtual address
        self.sections.sort(key=lambda sect: sect.address)

    def start(self) -> int:
        """Start of DOL in virtual memory
        """
        return self.sections[0].address

    def end(self) -> int:
        """End of DOL in virtual memory
        """
        return self.sections[-1].address + self.sections[-1].size

    def in_bss(self, sect: Section) -> bool:
        """Check if section is in the DOL's BSS area
        """
        return sect.address >= self.bss.address and sect.end() <= self.bss.end()

    def code_size(self) -> int:
        """Total code size in DOL
        """
        return self._code_size

    def data_size(self) -> int:
        """Total data size in DOL
        """
        return self._data_size + self.bss.size
