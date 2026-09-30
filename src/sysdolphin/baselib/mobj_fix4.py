import re

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'r') as f:
    c_code = f.read()

# Fix the next_tobj mistake
c_code = c_code.replace("->next_tobj", "->next")

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'w') as f:
    f.write(c_code)
