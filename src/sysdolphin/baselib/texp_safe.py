import re
import sys

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp.c', 'r') as f:
    c_code = f.read()

# 1. Add file header
file_header_c = """/**
 * @file texp.c
 * @brief Texture Expression (TExp) compilation system implementation
 * @details Implements the TEV color combiner expression tree compiler for GameCube GX hardware.
 * Module prefix: HSD_TExp
 */
"""
if not c_code.startswith("/**"):
    c_code = file_header_c + c_code

# 2. Add documentation to ALL functions
# We will use a safe regex that only inserts docs before the function signature
func_docs_c = {
    "HSD_TExpGetType": "/**\n * @brief Returns the expression node type (TEV, TEX, RAS, CNST, etc.).\n * @param texp Texture expression node\n * @return Node type enum\n */",
    "TevAlloc": "/**\n * @brief Allocates a new TEV node.\n * @return Pointer to new HSD_TExp\n */",
    "CnstAlloc": "/**\n * @brief Allocates a new constant node.\n * @return Pointer to new HSD_TExp\n */",
    "HSD_TExpFree": "/**\n * @brief Frees a single expression node.\n * @param texp Expression node\n */",
    "HSD_TExpRef": "/**\n * @brief Increments the reference count of an expression node.\n * @param texp Expression node\n * @param sel Color/Alpha selector flag\n */",
    "HSD_TExpUnref": "/**\n * @brief Decrements the reference count of an expression node and frees descendants if zero.\n * @param texp Expression node\n * @param sel Color/Alpha selector flag\n */",
    "HSD_TExpFreeList": "/**\n * @brief Frees an expression list, selectively keeping referenced nodes if free_all is 0.\n * @param texp_list Expression list head\n * @param type Node type to free (or HSD_TE_ALL)\n * @param free_all If non-zero, unconditionally frees nodes matching the type\n * @return Updated expression list head\n */",
    "HSD_TExpTev": "/**\n * @brief Allocates and initializes a TEV stage expression node, prepending it to the given list.\n * @param texp_list Pointer to the expression list head\n * @return The new TEV expression node\n */",
    "HSD_TExpCnst": "/**\n * @brief Finds or allocates a constant color/alpha expression node.\n * @param val Pointer to the constant value\n * @param comp Component type (RGB, A, X)\n * @param type Data type of val\n * @param texp_list Pointer to the expression list head\n * @return The constant expression node\n */",
    "HSD_TExpColorOp": "/**\n * @brief Sets the color operation, bias, scale, and clamp for a TEV expression.\n * @param texp TEV expression node\n * @param op TEV color operation\n * @param bias TEV bias\n * @param scale TEV scale\n * @param clamp Clamp enable flag\n */",
    "HSD_TExpAlphaOp": "/**\n * @brief Sets the alpha operation, bias, scale, and clamp for a TEV expression.\n * @param texp TEV expression node\n * @param op TEV alpha operation\n * @param bias TEV bias\n * @param scale TEV scale\n * @param clamp Clamp enable flag\n */",
    "HSD_TExpColorInSub": "/**\n * @brief Subroutine to map a single color input in the TEV stage.\n * @param tev TEV node\n * @param sel Input selector\n * @param exp Expression\n * @param idx Input index (0-3)\n */",
    "HSD_TExpColorIn": "/**\n * @brief Maps inputs (A, B, C, D) for the TEV color stage equation.\n * @param texp TEV expression node\n * @param sel_a Selector for input A\n * @param exp_a Expression for input A\n * @param sel_b Selector for input B\n * @param exp_b Expression for input B\n * @param sel_c Selector for input C\n * @param exp_c Expression for input C\n * @param sel_d Selector for input D\n * @param exp_d Expression for input D\n */",
    "HSD_TExpAlphaInSub": "/**\n * @brief Subroutine to map a single alpha input in the TEV stage.\n * @param tev TEV node\n * @param sel Input selector\n * @param exp Expression\n * @param idx Input index (0-3)\n */",
    "HSD_TExpAlphaIn": "/**\n * @brief Maps inputs (A, B, C, D) for the TEV alpha stage equation.\n * @param texp TEV expression node\n * @param sel_a Selector for input A\n * @param exp_a Expression for input A\n * @param sel_b Selector for input B\n * @param exp_b Expression for input B\n * @param sel_c Selector for input C\n * @param exp_c Expression for input C\n * @param sel_d Selector for input D\n * @param exp_d Expression for input D\n */",
    "HSD_TExpOrder": "/**\n * @brief Sets the texture object and color channel order for a TEV expression.\n * @param texp TEV expression node\n * @param tex Texture object (TObj)\n * @param chan Color channel ID\n */",
    "AssignColorReg": "/**\n * @brief Assigns a color register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "AssignAlphaReg": "/**\n * @brief Assigns an alpha register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "AssignColorKonst": "/**\n * @brief Assigns a KColor register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "AssignAlphaKonst": "/**\n * @brief Assigns a KAlpha register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "TExpAssignReg": "/**\n * @brief Allocates hardware registers to expression nodes during compilation.\n * @param texp Expression node\n * @param res Resources tracking\n * @return 0 on success\n */",
    "TExp2TevDesc": "/**\n * @brief Converts an expression node to a hardware-ready TEV descriptor.\n * @param texp Expression node\n * @param desc Output TEV descriptor\n * @param init_cprev Pointer to initialization flag for cprev\n * @param init_aprev Pointer to initialization flag for aprev\n */",
    "HSD_TExpSetReg": "/**\n * @brief Applies constant register values to the GX hardware.\n * @param texp Constant expression node\n */",
    "HSD_TExpCompile": "/**\n * @brief Compiles the expression tree into GX TEV descriptors.\n * @param texp Root of the expression tree\n * @param tevdesc_out Pointer to store the compiled TEV descriptors\n * @param texp_list Pointer to expression list to manage lifecycle\n * @return Status flag (0 on success)\n */",
    "HSD_TExpFreeTevDesc": "/**\n * @brief Frees a TEV descriptor list.\n * @param tdesc Pointer to TEV descriptor list\n */",
    "HSD_TExpSetupTev": "/**\n * @brief Loads compiled TEV descriptors into GX hardware registers.\n * @param desc TEV descriptor list\n * @param texp Associated expression tree\n */"
}

# We will just split the file by lines and insert the comments where the function definition starts
lines = c_code.split('\n')
new_lines = []
for i, line in enumerate(lines):
    # Find functions
    for func, doc in func_docs_c.items():
        # Match function definition
        if re.match(r'^(static\s+)?[a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func + r'\s*\(', line):
            # Check if previous lines already have a comment
            if i == 0 or not lines[i-1].strip() == "*/":
                new_lines.extend(doc.split('\n'))
            break
    new_lines.append(line)

c_code = '\n'.join(new_lines)

# 3. Variable renaming via word boundary regex for specific function bodies
def safe_replace(func_name, old_var, new_var, text):
    # Find function start and end
    start_idx = -1
    brace_level = 0
    in_func = False
    
    # We will iterate character by character or line by line
    # Regex is safer if we just find the function bounds
    match = re.search(r'^(static\s+)?[a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func_name + r'\s*\([^)]*\)\s*\{', text, re.MULTILINE)
    if not match:
        return text
    start_idx = match.end()
    
    # find the matching closing brace
    brace_level = 1
    end_idx = start_idx
    while end_idx < len(text) and brace_level > 0:
        if text[end_idx] == '{':
            brace_level += 1
        elif text[end_idx] == '}':
            brace_level -= 1
        end_idx += 1
    
    if brace_level != 0:
        return text
    
    pre = text[:start_idx]
    body = text[start_idx:end_idx]
    post = text[end_idx:]
    
    body = re.sub(r'\b' + old_var + r'\b', new_var, body)
    
    return pre + body + post

c_code = safe_replace('HSD_TExpFreeList', 'all', 'free_all', c_code)
c_code = safe_replace('HSD_TExpFreeList', 'ptr', 'curr_texp', c_code)
c_code = safe_replace('HSD_TExpFreeList', 'next', 'next_texp', c_code)

c_code = safe_replace('AssignColorReg', 'idx', 'in_idx', c_code)
c_code = safe_replace('AssignColorReg', 'res', 'texp_res', c_code)
c_code = re.sub(r'AssignColorReg\(HSD_TETev\* tev, int idx, HSD_TExpRes\* res\)', r'AssignColorReg(HSD_TETev* tev, int in_idx, HSD_TExpRes* texp_res)', c_code)

c_code = safe_replace('AssignAlphaReg', 'idx', 'in_idx', c_code)
c_code = safe_replace('AssignAlphaReg', 'res', 'texp_res', c_code)
c_code = re.sub(r'AssignAlphaReg\(HSD_TETev\* tev, int idx, HSD_TExpRes\* res\)', r'AssignAlphaReg(HSD_TETev* tev, int in_idx, HSD_TExpRes* texp_res)', c_code)

c_code = safe_replace('AssignColorKonst', 'idx', 'in_idx', c_code)
c_code = safe_replace('AssignColorKonst', 'res', 'texp_res', c_code)
c_code = re.sub(r'AssignColorKonst\(HSD_TETev\* tev, int idx, HSD_TExpRes\* res\)', r'AssignColorKonst(HSD_TETev* tev, int in_idx, HSD_TExpRes* texp_res)', c_code)

c_code = safe_replace('AssignAlphaKonst', 'idx', 'in_idx', c_code)
c_code = safe_replace('AssignAlphaKonst', 'res', 'texp_res', c_code)
c_code = re.sub(r'AssignAlphaKonst\(HSD_TETev\* tev, int idx, HSD_TExpRes\* res\)', r'AssignAlphaKonst(HSD_TETev* tev, int in_idx, HSD_TExpRes* texp_res)', c_code)

# HSD_TExpCompile signature change
c_code = re.sub(r'int HSD_TExpCompile\(HSD_TExp\* texp, HSD_TExpTevDesc\*\* tevdesc,\s*HSD_TExp\*\* texp_list\)', 
                'int HSD_TExpCompile(HSD_TExp* texp, HSD_TExpTevDesc** tevdesc_out,\n                    HSD_TExp** texp_list)', c_code, flags=re.MULTILINE)
c_code = safe_replace('HSD_TExpCompile', 'tevdesc', 'tevdesc_out', c_code)
c_code = safe_replace('HSD_TExpCompile', 'num', 'num_nodes', c_code)
c_code = safe_replace('HSD_TExpCompile', 'val', 'assign_res', c_code)
c_code = safe_replace('HSD_TExpCompile', 'tdesc', 'new_tevdesc', c_code)

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp_test.c', 'w') as f:
    f.write(c_code)
print(len(c_code.split('\n')))
