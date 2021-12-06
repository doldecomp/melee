#! /usr/bin/env python3

# Written by Ethan Roseman (ethteck)
# MIT License
# Copyright 2021

# Modified by EpochFlame

import argparse

# Byte sequence that marks code size
CODESIZE_MAGIC = b"\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x34"

# Byte sequences for conditional branches to link register
CBLR_BYTES = [
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

# Fix conditional branches
for seq in CBLR_BYTES:
    vanilla_idx = vanilla_bytes.count(seq)
    final_idx = final_bytes.count(seq)
    if vanilla_idx > final_idx:
        vanilla_findpos = 0
        for x in range(vanilla_idx):
            vanilla_findpos = vanilla_bytes.find(seq, vanilla_findpos)
            final_bytes = final_bytes[:vanilla_findpos] + vanilla_bytes[vanilla_findpos:vanilla_findpos+4] + final_bytes[vanilla_findpos+4:]
            vanilla_findpos+=1

# Fix remaining branches to link register
seq = b"\x4E\x80\x00\x20"
vanilla_idx = vanilla_bytes.count(seq)
final_idx = final_bytes.count(seq)
if vanilla_idx > final_idx:
    vanilla_findpos = 0
    for x in range(vanilla_idx):
        vanilla_findpos = vanilla_bytes.find(seq, vanilla_findpos)
        final_bytes = final_bytes[:vanilla_findpos] + vanilla_bytes[vanilla_findpos:vanilla_findpos+4] + final_bytes[vanilla_findpos+4:]
        vanilla_findpos+=1

with open(args.target, "wb") as f:
    f.write(final_bytes)
