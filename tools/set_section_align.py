#!/usr/bin/env python3
"""Override a section's alignment in a CodeWarrior-produced ELF object.

MWCC always emits `.rodata` with 8-byte section alignment. When a translation
unit's section lands on a 4-mod-8 address in the original binary, mwld cannot
place the compiled object there. The alignment is recorded twice — in the ELF
section header and in CodeWarrior's per-section table inside `.comment` — and
mwld uses the `.comment` copy, so both must be rewritten.

usage: set_section_align.py <object> <section>=<align> [<section>=<align> ...]
"""

import struct
import sys

# Offset of the per-section alignment table inside a CodeWarrior `.comment`
# section: "CodeWarrior" (11) + version block (10) + reserved (34).
CW_TABLE_OFFSET = 0x37
CW_TABLE_STRIDE = 8


def sections(data: bytearray):
    (shoff,) = struct.unpack_from(">I", data, 0x20)
    entsize, count, strndx = struct.unpack_from(">HHH", data, 0x2E)
    (stroff,) = struct.unpack_from(">I", data, shoff + strndx * entsize + 0x10)
    out = []
    for i in range(count):
        off = shoff + i * entsize
        (name,) = struct.unpack_from(">I", data, off)
        end = data.index(b"\0", stroff + name)
        out.append((data[stroff + name : end].decode(), off))
    return out


def main() -> int:
    path = sys.argv[1]
    with open(path, "rb") as f:
        data = bytearray(f.read())
    if data[:4] != b"\x7fELF" or data[5] != 2:
        sys.exit(f"{path}: not a big-endian ELF32 object")

    table = sections(data)
    names = [name for name, _ in table]
    if ".comment" not in names:
        sys.exit(f"{path}: no .comment section; not a CodeWarrior object")
    (_, comment_hdr) = table[names.index(".comment")]
    (comment_off,) = struct.unpack_from(">I", data, comment_hdr + 0x10)
    if bytes(data[comment_off : comment_off + 11]) != b"CodeWarrior":
        sys.exit(f"{path}: unrecognised .comment layout")

    for arg in sys.argv[2:]:
        section, _, value = arg.partition("=")
        align = int(value, 0)
        if section not in names:
            sys.exit(f"{path}: no section named {section}")
        index = names.index(section)
        struct.pack_into(">I", data, table[index][1] + 0x20, align)
        data[comment_off + CW_TABLE_OFFSET + CW_TABLE_STRIDE * index] = align

    with open(path, "wb") as f:
        f.write(data)
    return 0


if __name__ == "__main__":
    sys.exit(main())
