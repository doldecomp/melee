# Link Map Visualizer
# Regex to match symbol found in file: "(\w)\] ([_a-zA-Z0-9\-.]+) \((\w+),(\w+)\) found in ([_a-zA-Z0-9\-.]+)"
# Regex to match symbol found as a linker generated symbol: "(\w)\] ([_a-zA-Z0-9\-.]+) found as linker generated symbol"
import re

# Assumptions
# GALE01.map exists within build
GALE01 = 'build/ssbm.us.1.2/GALE01.map'

# open file and start iterating
with open(GALE01) as file:
    while line := file.readline():
        tokens = line.split()

        # pass on empty line
        if (len(tokens) != 0):
            head, *tail = tokens
            if (']' in head):
                level = int(head[:-1])
                print('level: {level} | tokens: {tokens}'.format(level=level, tokens=tokens))