#!/usr/bin/env python3

with open("mwcc_compiler/1.1/mwldeppc.exe", "r+b") as fh:
    fh.seek(0x0001ff75)
    fh.write(bytes([0x51]))
