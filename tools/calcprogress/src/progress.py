from dataclasses import dataclass

from .asm_util import AsmUtil
from .dol import Dol


@dataclass
class Slice:
    start: int
    end: int

    def size(self) -> int:
        assert self.end > self.start
        return self.end - self.start

    def contains_section(self, sect: AsmUtil.Section) -> bool:
        return self.start <= sect.start and self.end > sect.start + sect.size


@dataclass
class SliceGroup:
    name: str
    slices: list[Slice]

    def total_size(self) -> int:
        size = 0
        for _slice in self.slices:
            size += _slice.size()
        return size

    def contains_section(self, sect: AsmUtil.Section) -> bool:
        for _slice in self.slices:
            if _slice.contains_section(sect):
                return True
        return False


def calc_exec_progress(dol: Dol, asm_list: list[AsmUtil.Section], callback: "function"):
    """Calculate decompilation progress of the specified DOL.
    User callback specified for any game-specific progress info.
    """
    asm_code = 0
    asm_data = 0

    # Sum up code/data in ASM
    for section in asm_list:
        if section.type == AsmUtil.SECTION_CODE:
            asm_code += section.size
        elif section.type == AsmUtil.SECTION_DATA:
            asm_data += section.size
        else:
            assert False, f"Invalid section type ({section.type})!"

    # Dol sizes
    total_code = dol.code_size()
    total_data = dol.data_size()
    # Decompiled sizes
    src_code = total_code - asm_code
    src_data = total_data - asm_data
    # Percentages
    code_pcnt = src_code / total_code
    data_pcnt = src_data / total_data
    print(
        f"Code sections: {src_code} / {total_code} bytes in src ({code_pcnt:%})")
    print(
        f"Data sections: {src_data} / {total_data} bytes in src ({data_pcnt:%})")

    # User callback
    callback(src_code, total_code, src_data, total_data)


def calc_slice_group_progress(group: SliceGroup, asm_list: list[AsmUtil.Section], callback: "function"):
    """Calculate decompilation progress of the specified slice group.
    User callback specified for any game-specific progress info.
    """
    asm_size = 0
    for section in asm_list:
        if group.contains_section(section):
            if section.type == AsmUtil.SECTION_CODE:
                asm_size += section.size
            elif section.type == AsmUtil.SECTION_DATA:
                asm_size += section.size
            else:
                assert False, f"Invalid section type ({section.type})!"

    # Dol sizes
    total_size = group.total_size()
    # Decompiled sizes
    src_size = total_size - asm_size
    # Percentages
    slice_percent = src_size / total_size
    print(
        f"\t{group.name}: {src_size} / {total_size} bytes in src ({slice_percent:%})")

    # User callback
    callback(group.name, src_size, total_size)
