#!/usr/bin/env python3

################################################################################
#                                 Description                                  #
################################################################################
# calcprogress: Used to calculate the progress of the Melee decompilation.     #
# Prints to stdout for now, but eventually will have some form of storage,     #
# i.e. CSV, so that it can be used for a webpage display.                      #
#                                                                              #
# Usage: No arguments needed                                                   #
################################################################################




###############################################
#                                             #
#                  Imports                    #
#                                             #
###############################################

import os
import sys
import struct
import re
import math

###############################################
#                                             #
#                 Constants                   #
#                                             #
###############################################

MEM1_HI = 0x81700000 
MEM1_LO = 0x80003100

MW_WII_SYMBOL_REGEX = r"^\s*"\
r"(?P<SectOfs>\w{8})\s+"\
r"(?P<Size>\w{6})\s+"\
r"(?P<VirtOfs>\w{8})\s+"\
r"(?P<FileOfs>\w{8})\s+"\
r"(\w{1,2})\s+"\
r"(?P<Symbol>[0-9A-Za-z_<>$@.*]*)\s*"\
r"(?P<Object>\S*)"

MW_GC_SYMBOL_REGEX = r"^\s*"\
r"(?P<SectOfs>\w{8})\s+"\
r"(?P<Size>\w{6})\s+"\
r"(?P<VirtOfs>\w{8})\s+"\
r"(\w{1,2})\s+"\
r"(?P<Symbol>[0-9A-Za-z_<>$@.*]*)\s*"\
r"(?P<Object>\S*)"

REGEX_TO_USE = MW_GC_SYMBOL_REGEX

TEXT_SECTIONS = ["init", "text"]
DATA_SECTIONS = [
"rodata", "data", "bss", "sdata", "sbss", "sdata2", "sbss2",
"ctors", "_ctors", "dtors", "ctors$99", "_ctors$99", "ctors$00", "dtors$99",
"extab_", "extabindex_", "_extab", "_exidx"
]

# DOL info
TEXT_SECTION_COUNT = 7
DATA_SECTION_COUNT = 11

SECTION_TEXT = 0
SECTION_DATA = 1

###############################################
#                                             #
#                Entrypoint                   #
#                                             #
###############################################

if __name__ == "__main__":
    # Sum up DOL section sizes
    dol_handle = open(sys.argv[1], "rb")

    # Seek to virtual addresses
    dol_handle.seek(0x48)
    
    # Read virtual addresses
    text_starts = list()
    for i in range(TEXT_SECTION_COUNT):
        text_starts.append(int.from_bytes(dol_handle.read(4), byteorder='big'))
    data_starts = list()
    for i in range(DATA_SECTION_COUNT):
        data_starts.append(int.from_bytes(dol_handle.read(4), byteorder='big'))

    # Read lengths
    text_sizes = list()
    for i in range(TEXT_SECTION_COUNT):
        text_sizes.append(int.from_bytes(dol_handle.read(4), byteorder='big'))
    data_sizes = list()
    for i in range(DATA_SECTION_COUNT):
        data_sizes.append(int.from_bytes(dol_handle.read(4), byteorder='big'))



    # BSS address + length
    bss_start = int.from_bytes(dol_handle.read(4), byteorder='big')
    bss_size = int.from_bytes(dol_handle.read(4), byteorder='big')
    bss_end = bss_start + bss_size


    dol_code_size = 0
    dol_data_size = 0
    for i in range(DATA_SECTION_COUNT):
        # Ignore sections inside BSS
        if (data_starts[i] >= bss_start) and (data_starts[i] + data_sizes[i] <= bss_end): continue
        dol_data_size += data_sizes[i]

    dol_data_size += bss_size

    for i in text_sizes:
        dol_code_size += i

    # Open map file
    mapfile = open(sys.argv[2], "r")
    symbols = mapfile.readlines()

    decomp_code_size = 0
    decomp_data_size = 0
    section_type = None

    # Find first section
    first_section = 0
    while (symbols[first_section].startswith(".") == False and "section layout" not in symbols[first_section]): first_section += 1
    assert(first_section < len(symbols)), "Map file contains no sections!!!"
    
    cur_object = None
    cur_size = 0
    j = 0
    for i in range(first_section, len(symbols)):
        # New section
        if (symbols[i].startswith(".") == True or "section layout" in symbols[i]):
            # Grab section name (i.e. ".init section layout" -> "init")
            sectionName = re.search(r"\.*(?P<Name>\w+)\s", symbols[i]).group("Name")
            # Determine type of section
            section_type = SECTION_DATA if (sectionName in DATA_SECTIONS) else SECTION_TEXT
        # Parse symbols until we hit the next section declaration
        else:
            if "UNUSED" in symbols[i]: continue
            if "entry of" in symbols[i]:
                if j == i - 1:
                    if section_type == SECTION_TEXT:
                        decomp_code_size -= cur_size
                    else:
                        decomp_data_size -= cur_size
                    cur_size = 0
                    #print(f"Line* {j}: {symbols[j]}")
                #print(f"Line {i}: {symbols[i]}")
                continue
            assert(section_type != None), f"Symbol found outside of a section!!!\n{symbols[i]}"
            words = symbols[i].split()
            if len(words) == 0: continue
            if words[-1].endswith('.s.o'): continue
            match_obj = re.search(REGEX_TO_USE, symbols[i])
            # Should be a symbol in ASM (so we discard it)
            if (match_obj == None):
                #print(f"Line {i}: {symbols[i]}")
                continue
            # Has the object file changed?
            last_object = cur_object
            cur_object = match_obj.group("Object").strip()
            if last_object != cur_object: continue
            # Is the symbol a file-wide section?
            symb = match_obj.group("Symbol")
            if (symb.startswith("*fill*")) or (symb.startswith(".") and symb[1:] in TEXT_SECTIONS or symb[1:] in DATA_SECTIONS): continue
            # For sections that don't start with "."
            if (symb in DATA_SECTIONS): continue
            # If not, we accumulate the file size
            cur_size = int(match_obj.group("Size"), 16)
            j = i
            if (section_type == SECTION_TEXT):
                decomp_code_size += cur_size
            else:
                decomp_data_size += cur_size

    # Calculate percentages
    codeCompletionPcnt = (decomp_code_size / dol_code_size)
    dataCompletionPcnt = (decomp_data_size / dol_data_size)
    bytesPerTrophy = dol_code_size / 290
    bytesPerEvent = dol_data_size / 51
    
    trophyCount = math.floor(decomp_code_size / bytesPerTrophy)
    eventCount = math.floor(decomp_data_size / bytesPerEvent)

    print("Progress:")
    print(f"\tCode sections: {decomp_code_size} / {dol_code_size} bytes in src ({codeCompletionPcnt:%})")
    print(f"\tData sections: {decomp_data_size} / {dol_data_size} bytes in src ({dataCompletionPcnt:%})")
    print("\nYou have {} of 290 Trophies and completed {} of 51 Event Matches.".format(trophyCount, eventCount))
