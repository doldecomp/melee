#! /usr/bin/env python3

# Written by Ethan Roseman (ethteck)
# MIT License
# Copyright 2021

# Modified by EpochFlame

import argparse

# Byte sequence that marks code size
CODESIZE_MAGIC = b"\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x34"
BLR_BYTE_SEQ = b"\x4E\x80\x00\x20"
MTLR_BYTE_SEQ = b"\x7C\x08\x03\xA6"

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
profile_bytes = args.profile.read()
args.profile.close()

# Remove byte sequence
stripped_bytes = profile_bytes.replace(b"\x48\x00\x00\x01\x60\x00\x00\x00", b"")

# Find end of code sections in vanilla and stripped bytes
code_size_offset = (vanilla_bytes.find(CODESIZE_MAGIC) + 12)
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

with open(args.target, "wb") as f:
    f.write(final_bytes)
