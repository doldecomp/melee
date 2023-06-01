#!/usr/bin/env python3
import ast
import struct
import sys


def convert_literal_to_dword(s):
    literal = ast.literal_eval(s)
    if isinstance(literal, float):
        dword = struct.unpack(">I", struct.pack(">f", literal))[0]
    else:
        dword = int(literal)
    return dword


if __name__ == "__main__":
    python_literals = list(map(convert_literal_to_dword, sys.argv[1:3]))
    qword = (python_literals[0] << 32) | python_literals[1]
    double = struct.unpack(">d", qword.to_bytes(8, "big"))[0]
    print(double)
