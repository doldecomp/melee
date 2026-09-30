import re

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'r') as f:
    c_code = f.read()

# Fix static MObjUpdateFunc
c_code = re.sub(r'static /\*\*\n(.*?)\n \*/\nvoid MObjUpdateFunc', r'/**\n\1\n */\nstatic void MObjUpdateFunc', c_code, flags=re.DOTALL)
# Fix static MObjLoad
c_code = re.sub(r'static /\*\*\n(.*?)\n \*/\nint MObjLoad', r'/**\n\1\n */\nstatic int MObjLoad', c_code, flags=re.DOTALL)
# Fix static MObjRelease
c_code = re.sub(r'static /\*\*\n(.*?)\n \*/\nvoid MObjRelease', r'/**\n\1\n */\nstatic void MObjRelease', c_code, flags=re.DOTALL)
# Fix static MObjAmnesia
c_code = re.sub(r'static /\*\*\n(.*?)\n \*/\nvoid MObjAmnesia', r'/**\n\1\n */\nstatic void MObjAmnesia', c_code, flags=re.DOTALL)
# Fix static MObjInfoInit
c_code = re.sub(r'static /\*\*\n(.*?)\n \*/\nvoid MObjInfoInit', r'/**\n\1\n */\nstatic void MObjInfoInit', c_code, flags=re.DOTALL)

# Fix 'val' -> 'anim_data' in MObjUpdateFunc
# I previously did: c_code = replace_in_func('MObjUpdateFunc', 'val', 'anim_data', c_code)
# But looking at line 133: `void MObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)` -> it missed replacing the signature! Let's do a simple regex replace for val in the signature.
c_code = re.sub(r'void MObjUpdateFunc\(void\* obj, enum_t type, HSD_ObjData\* val\)', r'void MObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* anim_data)', c_code)

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'w') as f:
    f.write(c_code)
