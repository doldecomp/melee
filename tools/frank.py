#! /usr/bin/env python3

# Written by Ethan Roseman (ethteck)
# MIT License
# Copyright 2021

# Modified by EpochFlame

import argparse
import sys

# Byte sequence that marks code size
CODESIZE_MAGIC = b"\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x34"
BLR_BYTE_SEQ = b"\x4E\x80\x00\x20"
MTLR_BYTE_SEQ = b"\x7C\x08\x03\xA6"
PROFILE_EXTRA_BYTES = b"\x48\x00\x00\x01\x60\x00\x00\x00"

LWZ_BYTE = b"\x80"

# Byte sequence array for branches to link register
BLR_BYTE_SEQ_ARRAY = [BLR_BYTE_SEQ,
b"\x4D\x80\x00\x20", b"\x4D\x80\x00\x21", b"\x4C\x81\x00\x20", b"\x4C\x81\x00\x21",
b"\x4D\x82\x00\x20", b"\x4D\x82\x00\x21", b"\x4C\x80\x00\x20", b"\x4C\x80\x00\x21",
b"\x4D\x81\x00\x20", b"\x4D\x81\x00\x21", b"\x4C\x80\x00\x20", b"\x4C\x80\x00\x21",
b"\x4C\x82\x00\x20", b"\x4C\x82\x00\x21", b"\x4C\x81\x00\x20", b"\x4C\x81\x00\x21",
b"\x4D\x83\x00\x20", b"\x4D\x83\x00\x21", b"\x4C\x83\x00\x20", b"\x4C\x83\x00\x21",
b"\x4D\x83\x00\x20", b"\x4D\x83\x00\x21", b"\x4C\x83\x00\x20", b"\x4C\x83\x00\x21"]

# Example invocation: ./frank.py vanilla.o profile.o output.o
parser = argparse.ArgumentParser()
parser.add_argument("vanilla", help="Path to the vanilla object", type=argparse.FileType('rb'))
parser.add_argument("profile", help="Path to the profile object", type=argparse.FileType('rb'))
parser.add_argument("target", help="Path to the target object (to write)")

args = parser.parse_args()

# Read contents into bytearrays and close files
vanilla_bytes = args.vanilla.read()
args.vanilla.close()

# If the file contains no code, the codesize magic will not be found.
# The vanilla object requires no modification.
code_size_magic_idx = vanilla_bytes.find(CODESIZE_MAGIC)
if code_size_magic_idx == -1:
    with open(args.target, "wb") as f:
        f.write(vanilla_bytes)
    sys.exit(0)

profile_bytes = args.profile.read()
args.profile.close()

# Peephole rescheduling
#
# This is the pattern we will detect:
#  (A) lwz <--.   .-->  (A) li
#  (B) li  <---\-'          bl
#               \           nop
#                '--->  (B) lwz
#
# If the profiled schedule swaps the
# instructions around the bl/nop, we
# instead use the vanilla schedule.
#
idx = 8
shift = 0 # difference between vanilla and profile code, due to bl/nops
while idx < len(profile_bytes) - 16:
    # Find next epilogue
    epi_pos = profile_bytes.find(PROFILE_EXTRA_BYTES, idx)
    if epi_pos == -1:
        break # break while loop when no targets remain
    if epi_pos % 4 != 0: # check 4-byte alignment
        idx += 4
        continue

    v_pos = epi_pos - shift
    shift += 8

    vanilla_inst_a = vanilla_bytes[v_pos-4:v_pos]
    vanilla_inst_b = vanilla_bytes[v_pos:v_pos+4]
    vanilla_inst_c = vanilla_bytes[v_pos+4:v_pos+8]
    profile_inst_a = profile_bytes[epi_pos-4:epi_pos]
    profile_inst_b = profile_bytes[epi_pos+8:epi_pos+12]
    profile_inst_c = profile_bytes[epi_pos+12:epi_pos+16]

    opcode_a = vanilla_inst_a[0] >> 2
    opcode_b = vanilla_inst_b[0] >> 2
    opcode_c = vanilla_inst_c[0] >> 2

    LWZ = 0x80 >> 2
    LFS = 0xC0 >> 2
    ADDI = 0x38 >> 2
    LI = ADDI # an LI instruction is just an ADDI with RA=0
    LMW = 0xB8 >> 2

    if opcode_a == LWZ and \
       opcode_b in [LI, LFS] and \
       vanilla_inst_a == profile_inst_b and \
       vanilla_inst_b == profile_inst_a and \
       vanilla_inst_c == profile_inst_c and \
       opcode_c != ADDI: # <- don't reorder if at the very end of the epilogue

        # Swap instructions (A) and (B)
        profile_bytes = profile_bytes[:epi_pos-4] \
                + vanilla_inst_a \
                + PROFILE_EXTRA_BYTES \
                + vanilla_inst_b \
                + profile_bytes[epi_pos+12:]

    # Similar reordering for lwz/lmw, except both insns follow the bl/nop
    elif opcode_b == LWZ and \
         opcode_c == LMW and \
         vanilla_inst_b == profile_inst_c and \
         vanilla_inst_c == profile_inst_b:

        profile_bytes = profile_bytes[:epi_pos+8] \
                + vanilla_inst_b \
                + vanilla_inst_c \
                + profile_bytes[epi_pos+16:]

    idx = epi_pos + 8

# Remove byte sequence
stripped_bytes = profile_bytes.replace(PROFILE_EXTRA_BYTES, b"")

# Find end of code sections in vanilla and stripped bytes
code_size_offset = code_size_magic_idx + len(CODESIZE_MAGIC)
code_size_bytes = vanilla_bytes[code_size_offset:code_size_offset+4]
code_size = int.from_bytes(code_size_bytes, byteorder='big')

eoc_offset = 0x34 + code_size

# Break if the eoc is not found
assert(eoc_offset != len(vanilla_bytes))

# Replace 0x34 - eoc in vanilla with bytes from stripped
final_bytes = vanilla_bytes[:0x34] + stripped_bytes[0x34:eoc_offset] + vanilla_bytes[eoc_offset:]

# Fix branches to link register
for seq in BLR_BYTE_SEQ_ARRAY:
    idx = 0

    while idx < len(vanilla_bytes):
        found_pos = vanilla_bytes.find(seq, idx)
        if found_pos == -1:
            break # break while loop when no targets remain
        if found_pos % 4 != 0: # check 4-byte alignment
            idx += 4
            continue
        final_bytes = final_bytes[:found_pos] + vanilla_bytes[found_pos:found_pos+4] + final_bytes[found_pos+4:]
        idx = found_pos + len(seq)

# Reunify mtlr/blr instructions, shifting intermediary instructions up
idx = 0

while idx < len(final_bytes):
    # Find mtlr position
    mtlr_found_pos = final_bytes.find(MTLR_BYTE_SEQ, idx)
    if mtlr_found_pos == -1:
        break # break while loop when no targets remain
    if mtlr_found_pos % 4 != 0: # check 4-byte alignment
        idx += 4
        continue
    # Find paired blr position
    blr_found_pos = final_bytes.find(BLR_BYTE_SEQ, mtlr_found_pos)
    if blr_found_pos == -1:
        break # break while loop when no targets remain
    if blr_found_pos % 4 != 0: # check 4-byte alignment
        idx += 4
        continue
    if mtlr_found_pos + 4 == blr_found_pos:
        idx += 4
        continue # continue if mtlr is followed directly by blr
    
    final_bytes = final_bytes[:mtlr_found_pos] + final_bytes[mtlr_found_pos+4:blr_found_pos] + final_bytes[mtlr_found_pos:mtlr_found_pos+4] + final_bytes[blr_found_pos:]
    idx = mtlr_found_pos + len(MTLR_BYTE_SEQ)

# Reorder lmw/lwz/lfd instructions, if needed (@Altafen)
# Specifically, if this sequence shows up in the stripped profiler code: "LMW, LWZ, LFD*"
# And this sequence shows up in the vanilla code: "LWZ, LFD*, LMW"
# (LFD* = any number of LFDs, including zero)
# If all bytes match between the two (except for the reordering), then use the vanilla ordering.
# This could be written to anchor around the "BL, NOP" instructions in unstripped profiler code,
# or to check for the presence of "ADDI, MTLR, BLR" soon after.
# This also could be written to decode the operands of each instruction to make sure the reorder is harmless.
# Neither of these safeguards are necessary at the moment.
LWZ = 32
LMW = 46
LFD = 50
idx = 0
while idx+4 < len(final_bytes):
    if final_bytes[idx] >> 2 == LMW and final_bytes[idx+4] >> 2 == LWZ and vanilla_bytes[idx] >> 2 == LWZ:
        start_idx = idx
        lmw_bytes = final_bytes[idx:idx+4]
        lwz_bytes = final_bytes[idx+4:idx+8]
        if vanilla_bytes[idx:idx+4] != lwz_bytes:
            idx += 4
            continue
        lfd_bytes = b""
        idx += 4
        while vanilla_bytes[idx] >> 2 == LFD:
            lfd_bytes += vanilla_bytes[idx:idx+4]
            idx += 4
        if vanilla_bytes[idx:idx+4] != lmw_bytes:
            continue
        if final_bytes[start_idx+8:start_idx+8+len(lfd_bytes)] != lfd_bytes:
            continue
        idx += 4
        final_bytes = final_bytes[:start_idx] + lwz_bytes + lfd_bytes + lmw_bytes + final_bytes[idx:]
        continue
    idx += 4

with open(args.target, "wb") as f:
    f.write(final_bytes)
