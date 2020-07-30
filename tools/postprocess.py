#!/usr/bin/env python3

BANNER = """
# This script is the culmination of three patches supporting decompilation
# with the CodeWarrior compiler.
# - riidefi, 2020
#
# postprocess.py [args] file
#
# 1) Certain versions have a bug where the ctor alignment is ignored and set incorrectly.
#    This option is enabled with -fctor-realign, and disabled by default with -fno-ctor-realign
#
# 2) Certain C++ symbols cannot be assembled normally.
#    To support the buildsystem, a simple substitution system has been devised
#
#    ?<ID> -> CHAR
#
#    IDs (all irregular symbols in mangled names):
#       0: <
#       1: >
#       2: @
#       3: \\
#       4: ,
#       5: -
#
#    This option is enabled with -fsymbol-fixup, and disabled by default with -fno-symbol-fixup
#
# 3) CodeWarrior versions below 2.3 used a different scheduler model.
#    The script can currently adjust function epilogues with the old_stack option.
#    -fprologue-fixup=[default=none, none, old_stack]
"""

import struct

# Substitutions
substitutions = (
    ('<',  '?0'),
    ('>',  '?1'),
    ('@',  '?2'),
    ('\\', '?3'),
    (',',  '?4'),
    ('-',  '?5')
)

def format(symbol):
    for sub in substitutions:
        symbol = symbol.replace(sub[0], sub[1])

    return symbol

def decodeformat(symbol):
    for sub in substitutions:
        symbol = symbol.replace(sub[1], sub[0])

    return symbol

# Stream utilities

def read_u8(f):
    return struct.unpack("B", f.read(1))[0]

def read_u32(f):
    return struct.unpack(">I", f.read(4))[0]

def read_u16(f):
    return struct.unpack(">H", f.read(2))[0]

def write_u32(f, val):
    f.write(struct.pack(">I", val))

class ToReplace:
    def __init__(self, position, dest, src_size):
        self.position = position # Where in file
        self.dest = dest # String to patch
        self.src_size = src_size # Pad rest with zeroes

        # print("To replace: %s %s %s" % (self.position, self.dest, self.src_size))

def read_string(f):
    tmp = ""
    c = 0xff
    while c != 0x00:
        c = read_u8(f)
        if c != 0:
            tmp += chr(c)
    return tmp

def ctor_realign(f, ofsSecHeader, nSecHeader, idxSegNameSeg):
    patch_align_ofs = []

    for i in range(nSecHeader):
        f.seek(ofsSecHeader + i * 0x28)
        ofsname = read_u32(f)
        if not ofsname: continue

        back = f.tell()
        
        f.seek(ofsSecHeader + (idxSegNameSeg * 0x28) + 0x10)
        ofsShST = read_u32(f)
        f.seek(ofsShST + ofsname)
        name = read_string(f)
        if name == ".ctors" or name == ".dtors":
            patch_align_ofs.append(ofsSecHeader + i * 0x28 + 0x20)
            
        f.seek(back)
    
    return patch_align_ofs

SHT_PROGBITS = 1
SHT_STRTAB = 3

def impl_postprocess_elf(f, do_ctor_realign, do_old_stack, do_symbol_fixup):
    result = []

    f.seek(0x20)
    ofsSecHeader = read_u32(f)
    f.seek(0x30)
    nSecHeader = read_u16(f)
    idxSegNameSeg = read_u16(f)
    secF = False # First instance the section names

    # Header: 0x32:
    patch_align_ofs = []

    if do_ctor_realign:
       patch_align_ofs = ctor_realign(f, ofsSecHeader, nSecHeader, idxSegNameSeg)

    for i in range(nSecHeader):
        f.seek(ofsSecHeader + i * 0x28)
        sh_name = read_u32(f)
        sh_type = read_u32(f)

        if sh_type == SHT_STRTAB and do_symbol_fixup:
            if not secF:
                secF = True
                continue
            f.seek(ofsSecHeader + i * 0x28 + 0x10)
            ofs = read_u32(f)
            size = read_u32(f)

            f.seek(ofs)
            string = ""
            str_spos = ofs
            for i in range(ofs, ofs+size):
                c = read_u8(f)
                if c == 0:
                    if len(string):
                        fixed = decodeformat(string)
                        if fixed != string:
                            result.append(ToReplace(str_spos, fixed, len(string)))
                    string = ""
                    str_spos = i+1
                else:
                    string += chr(c)
        else:
            f.seek(ofsSecHeader + (idxSegNameSeg * 0x28) + 0x10)
            ofsShST = read_u32(f)
            f.seek(ofsShST + sh_name)
            name = read_string(f)

            if name == ".text" and do_old_stack:
                f.seek(ofsSecHeader + i * 0x28 + 0x10)
                ofs = read_u32(f)
                size = read_u32(f)

                # We assume
                # 1) Only instructions are in the .text section
                # 2) These instructions are 4-byte aligned
                assert ofs != 0
                assert ofs % 4 == 0
                assert size % 4 == 0 
                
                f.seek(ofs)

                mtlr_pos = 0
                
                # (mtlr position, blr position)
                epilogues = []

                for _ in range(ofs, ofs+size, 4):
                    it = f.tell()
                    instr = read_u32(f)

                    # Skip padding
                    if instr == 0: continue

                    # Call analysis is not actually required
                    # No mtlr will exist without a blr; mtctr/bctr* is used for dynamic dispatch
                    
                    # FUN_A:
                    #   li r3, 0
                    #   blr       <---- No mtlr, move onto the next function
                    # FUN_B:
                    #   ; complex function, stack manip
                    #   mtlr r0   <---- Expect a blr
                    #   addi r1, r1, 24
                    #   blr       <---- Confirm patch above

                    # mtlr alias for mtspr
                    if instr == 0x7C0803A6:
                        assert mtlr_pos == 0
                        mtlr_pos = it
                    # blr
                    elif instr == 0x4E800020:
                        if mtlr_pos:
                            epilogues.append((mtlr_pos, it))
                        mtlr_pos = 0
                        

                # Check for a lone mtlr
                assert mtlr_pos == 0

                # Reunify mtlr/blr instructions, shifting intermediary instructions up
                for mtlr_pos, blr_pos in epilogues:    
                    # Check if we need to do anything
                    if mtlr_pos + 4 == blr_pos: continue
                    
                    # As the processor can only hold 6 instructions at once in the pipeline,
                    # it's unlikely for the mtlr be shifted up more instructions than that--usually,
                    # only one:
                    #   mtlr r0
                    #   addi r1, r1, 24
                    #   blr
                    assert blr_pos - 4 > mtlr_pos
                    assert blr_pos - mtlr_pos <= 6 * 4

                    print("Patching old epilogue: %s %s" % (mtlr_pos, blr_pos))

                    f.seek(mtlr_pos)
                    mtlr = read_u32(f)
                    
                    for it in range(mtlr_pos, blr_pos - 4, 4):
                        f.seek(it + 4)
                        next_instr = read_u32(f)
                        f.seek(it)
                        write_u32(f, next_instr)
                    
                    f.seek(blr_pos - 4)
                    write_u32(f, mtlr)

    return (result, patch_align_ofs)

def postprocess_elf(f, do_ctor_realign, do_old_stack, do_symbol_fixup):
    patches = impl_postprocess_elf(f, do_ctor_realign, do_old_stack, do_symbol_fixup)

    f.seek(0)
    source_bytes = list(f.read())
    for patch in patches[0]:
        assert len(patch.dest) <= patch.src_size
        for j in range(patch.src_size):
            if j >= len(patch.dest):
                c = 0
            else:
                c = ord(patch.dest[j])
            source_bytes[patch.position + j] = c

    # Patch ctor align
    nP = 0
    for p in patches[1]:
        print("Patching ctors")
        source_bytes[p + 0] = 0
        source_bytes[p + 1] = 0
        source_bytes[p + 2] = 0
        source_bytes[p + 3] = 4
        nP += 1
        if nP > 1:
            print("Patched ctors + dtors")

    f.seek(0)
    f.write(bytes(source_bytes))

def frontend(args):
    inplace = ""
    do_ctor_realign = False
    do_old_stack = False
    do_symbol_fixup = False

    for arg in args:
        if arg.startswith('-f'):
            negated = False
            if arg.startswith('-fno-'):
                negated = True
                arg = arg[len('-fno-'):]
            else:
                arg = arg[len('-f'):]

            if arg == 'ctor_realign':
                do_ctor_realign = not negated
            elif arg == 'symbol-fixup':
                do_symbol_fixup = not negated
            elif arg.startswith('prologue-fixup='):
                do_old_stack = arg[len('prologue-fixup='):] == 'old_stack'
            else:
                print("Unknown argument: %s" % arg)
        elif arg.startswith('-'):
            print("Unknown argument: %s. Perhaps you meant -f%s?" % (arg, arg))
        else:
            if inplace:
                print("Cannot process %s. Only one source file may be specified." % arg)
            else:
                inplace = arg

    if not inplace:
        print("A file must be specified!")
        return

    try:
        postprocess_elf(open(inplace, 'rb+'), do_ctor_realign, do_old_stack, do_symbol_fixup)
    except FileNotFoundError:
        print("Cannot open file %s" % inplace)

if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        print(BANNER)
    else:
        frontend(sys.argv[1:])
