# Link Map Visualizer
# Regex to match symbol found in file: "(\w)\] ([_a-zA-Z0-9\-.]+) \((\w+),(\w+)\) found in ([_a-zA-Z0-9\-.]+)"
# Regex to match symbol found as a linker generated symbol: "(\w)\] ([_a-zA-Z0-9\-.]+) found as linker generated symbol"
from lib2to3.pgen2 import token
import re

# Assumptions
# GALE01.map exists within build
GALE01 = 'build/ssbm.us.1.2/GALE01.map'

def tokens2obj(tokens):
    # structure of tokens:
    # [ raw level, identifier, '(<type>,<scope>)', drop, drop, file object ]
    assert(len(tokens) == 6)
    raw_level, iden, _ctype_scope, _, _, file_obj = tokens
    level = int(raw_level[:-1])
    _ctype_scope = _ctype_scope[1:-1]
    ctype, scope = _ctype_scope.split(',')

    return {'level': level, 'id': iden, 'ctype': ctype, 'scope': scope, 'objfile': file_obj}

def tokens2symbol(tokens):
    # structure of tokens:
    # [ raw level, identifier, drop, drop, drop, drop, drop]
    assert(len(tokens) == 7)
    raw_level, iden, _, _, _, _, _ = tokens
    level = int(raw_level[:-1])

    return {'level': level, 'id': iden, 'ctype': 'linkersymbol'}

parsed = []

# open file and start iterating
with open(GALE01) as file:
    while line := file.readline():
        tokens = line.split()

        # pass on empty line
        if (len(tokens) != 0):
            head, *tail = tokens
            if (']' in head):
                if (len(tokens) == 6):
                    # take tokens and create the storage object
                    obj = tokens2obj(tokens)
                    parsed.append(obj)
                elif (len(tokens) == 7):
                    # take tokens are create generated symbol object
                    obj = tokens2symbol(tokens)
                    parsed.append(obj)
                else:
                    pass

print(len(parsed))