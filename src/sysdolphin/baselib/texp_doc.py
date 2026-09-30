import re

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp.h', 'r') as f:
    h_code = f.read()

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp.c', 'r') as f:
    c_code = f.read()

file_header_h = """/**
 * @file texp.h
 * @brief Texture Expression (TExp) compilation system
 * @details Implements the TEV color combiner expression tree compiler for GameCube GX hardware.
 * Module prefix: HSD_TExp
 */
"""

file_header_c = """/**
 * @file texp.c
 * @brief Texture Expression (TExp) compilation system implementation
 * @details Implements the TEV color combiner expression tree compiler for GameCube GX hardware.
 * Module prefix: HSD_TExp
 */
"""

if not h_code.startswith("/**"):
    h_code = file_header_h + h_code

if not c_code.startswith("/**"):
    c_code = file_header_c + c_code

def replace_in_func(func_name, old_var, new_var, text):
    pattern = r'(' + func_name + r'\s*\([^)]*\)\s*\{)(.*?)(^\})'
    
    def repl(m):
        body = m.group(2)
        body = re.sub(r'\b' + old_var + r'\b', new_var, body)
        return m.group(1) + body + m.group(3)
        
    return re.sub(pattern, repl, text, flags=re.DOTALL | re.MULTILINE)

c_code = replace_in_func('HSD_TExpFreeList', 'all', 'free_all', c_code)
c_code = replace_in_func('HSD_TExpFreeList', 'ptr', 'curr_texp', c_code)
c_code = replace_in_func('HSD_TExpFreeList', 'next', 'next_texp', c_code)

func_docs_h = {
    "HSD_TExpGetType": "/**\n * @brief Returns the expression node type (TEV, TEX, RAS, CNST, etc.).\n * @param texp Texture expression node\n * @return Node type enum\n */",
    "HSD_TExpTev": "/**\n * @brief Allocates and initializes a TEV stage expression node, prepending it to the given list.\n * @param list Pointer to the expression list head\n * @return The new TEV expression node\n */",
    "HSD_TExpCnst": "/**\n * @brief Finds or allocates a constant color/alpha expression node.\n * @param val Pointer to the constant value\n * @param comp Component type (RGB, A, X)\n * @param type Data type of val\n * @param list Pointer to the expression list head\n * @return The constant expression node\n */",
    "HSD_TExpOrder": "/**\n * @brief Sets the texture object and color channel order for a TEV expression.\n * @param texp TEV expression node\n * @param tex Texture object (TObj)\n * @param chan Color channel ID\n */",
    "HSD_TExpColorOp": "/**\n * @brief Sets the color operation, bias, scale, and clamp for a TEV expression.\n * @param texp TEV expression node\n * @param op TEV color operation\n * @param bias TEV bias\n * @param scale TEV scale\n * @param clamp Clamp enable flag\n */",
    "HSD_TExpColorIn": "/**\n * @brief Maps inputs (A, B, C, D) for the TEV color stage equation.\n * @param texp TEV expression node\n * @param sel_a Selector for input A\n * @param exp_a Expression for input A\n * @param sel_b Selector for input B\n * @param exp_b Expression for input B\n * @param sel_c Selector for input C\n * @param exp_c Expression for input C\n * @param sel_d Selector for input D\n * @param exp_d Expression for input D\n */",
    "HSD_TExpAlphaOp": "/**\n * @brief Sets the alpha operation, bias, scale, and clamp for a TEV expression.\n * @param texp TEV expression node\n * @param op TEV alpha operation\n * @param bias TEV bias\n * @param scale TEV scale\n * @param clamp Clamp enable flag\n */",
    "HSD_TExpAlphaIn": "/**\n * @brief Maps inputs (A, B, C, D) for the TEV alpha stage equation.\n * @param texp TEV expression node\n * @param sel_a Selector for input A\n * @param exp_a Expression for input A\n * @param sel_b Selector for input B\n * @param exp_b Expression for input B\n * @param sel_c Selector for input C\n * @param exp_c Expression for input C\n * @param sel_d Selector for input D\n * @param exp_d Expression for input D\n */",
    "HSD_TExpFreeTevDesc": "/**\n * @brief Frees a TEV descriptor list.\n * @param desc Pointer to TEV descriptor list\n */",
    "HSD_TExpFreeList": "/**\n * @brief Frees an expression list, selectively keeping referenced nodes if free_all is 0.\n * @param texp_list Expression list head\n * @param type Node type to free (or HSD_TE_ALL)\n * @param free_all If non-zero, unconditionally frees nodes matching the type\n * @return Updated expression list head\n */",
    "HSD_TExpCompile": "/**\n * @brief Compiles the expression tree into GX TEV descriptors.\n * @param texp Root of the expression tree\n * @param desc Pointer to store the compiled TEV descriptors\n * @param list Pointer to expression list to manage lifecycle\n * @return Status flag (0 on success)\n */",
    "HSD_TExpSetupTev": "/**\n * @brief Loads compiled TEV descriptors into GX hardware registers.\n * @param desc TEV descriptor list\n * @param texp Associated expression tree\n */",
    "HSD_TExpFree": "/**\n * @brief Frees a single expression node.\n * @param texp Expression node\n */",
    "HSD_TExpRef": "/**\n * @brief Increments the reference count of an expression node.\n * @param texp Expression node\n * @param sel Color/Alpha selector flag\n */",
    "HSD_TExpUnref": "/**\n * @brief Decrements the reference count of an expression node and frees descendants if zero.\n * @param texp Expression node\n * @param sel Color/Alpha selector flag\n */",
    "HSD_TExpSetReg": "/**\n * @brief Applies constant register values to the GX hardware.\n * @param texp Constant expression node\n */",
    "IsThroughColor": "/**\n * @brief Checks if the color operation is a pass-through (A+B where A=0, B=0).\n * @param texp TEV expression node\n * @return true if pass-through\n */",
    "IsThroughAlpha": "/**\n * @brief Checks if the alpha operation is a pass-through.\n * @param texp TEV expression node\n * @return true if pass-through\n */",
}

for func, doc in func_docs_h.items():
    # Update .h
    pattern_h = r'^(.*?)([a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func + r'\s*\([^)]*\)\s*;)'
    h_code = re.sub(pattern_h, r'\1' + doc + r'\n\2', h_code, flags=re.MULTILINE)
    if 'IsThrough' in func: # inline funcs in .h
        pattern_h2 = r'^(.*?)(static inline\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func + r'\s*\([^)]*\)\s*\{)'
        h_code = re.sub(pattern_h2, r'\1' + doc + r'\n\2', h_code, flags=re.MULTILINE)
    
    # Update .c
    pattern_c = r'^(.*?)([a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func + r'\s*\([^)]*\)\s*\{)'
    c_code = re.sub(pattern_c, r'\1' + doc + r'\n\2', c_code, flags=re.MULTILINE)

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp.h', 'w') as f:
    f.write(h_code)

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp.c', 'w') as f:
    f.write(c_code)

print("Done python script")
