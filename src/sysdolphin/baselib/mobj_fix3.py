import re

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'r') as f:
    c_code = f.read()

func_docs_c = {
    "HSD_MObjLoadDesc": "/**\n * @brief Allocates and loads an MObj and its material properties from an MObjDesc.\n * @param mobjdesc Material object descriptor\n * @return Newly allocated MObj\n */",
    "MObjMakeTExp": "/**\n * @brief Generates the TEV texture expression (TExp) tree based on the MObj's textures and rendering mode.\n * @param mobj MObj pointer\n * @param tobj_top Head of the TObj linked list\n * @param list Pointer to store the resulting TExp list\n * @return The root expression node\n */",
    "HSD_MObjGetTObj": "/**\n * @brief Retrieves the linked list of texture objects (TObj) from the MObj.\n * @param mobj MObj pointer\n * @return Head of the TObj linked list\n */",
    "HSD_MObjAlloc": "/**\n * @brief Allocates a new, uninitialized MObj instance.\n * @return Newly allocated MObj\n */",
    "HSD_MaterialAlloc": "/**\n * @brief Allocates a new HSD_Material struct, initializing its alpha to 1.0.\n * @return Newly allocated Material\n */",
}

for func, doc in func_docs_c.items():
    # More permissive regex for return type
    pattern = r'^(.*?)([a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func + r'\s*\([^)]*\)\s*\{)'
    c_code = re.sub(pattern, r'\1' + doc + r'\n\2', c_code, flags=re.MULTILINE)

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'w') as f:
    f.write(c_code)
