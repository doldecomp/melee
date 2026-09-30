import re

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp.c', 'r') as f:
    c_code = f.read()

def replace_in_func(func_name, old_var, new_var, text):
    pattern = r'(?m)^.*?([a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func_name + r'\s*\([^)]*\)\s*\{)(.*?)(^\})'
    
    def repl(m):
        body = m.group(2)
        body = re.sub(r'\b' + old_var + r'\b', new_var, body)
        return m.group(1) + body + m.group(3)
        
    return re.sub(pattern, repl, text, flags=re.DOTALL)

# Variable renames
c_code = replace_in_func('AssignColorReg', 'idx', 'in_idx', c_code)
c_code = replace_in_func('AssignColorReg', 'res', 'texp_res', c_code)

c_code = replace_in_func('AssignAlphaReg', 'idx', 'in_idx', c_code)
c_code = replace_in_func('AssignAlphaReg', 'res', 'texp_res', c_code)

c_code = replace_in_func('AssignColorKonst', 'idx', 'in_idx', c_code)
c_code = replace_in_func('AssignColorKonst', 'res', 'texp_res', c_code)

c_code = replace_in_func('AssignAlphaKonst', 'idx', 'in_idx', c_code)
c_code = replace_in_func('AssignAlphaKonst', 'res', 'texp_res', c_code)

# HSD_TExpCompile
# Because it's "HSD_TExpTevDesc** tevdesc", we must be careful. Let's just do it directly on the function body to be safe, or rename `tevdesc` safely.
# Wait, replacing `tevdesc` in `HSD_TExpCompile` might rename the argument too if I just rename the argument in the signature.
c_code = re.sub(r'int HSD_TExpCompile\(HSD_TExp\* texp, HSD_TExpTevDesc\*\* tevdesc,', 'int HSD_TExpCompile(HSD_TExp* texp, HSD_TExpTevDesc** tevdesc_out,', c_code)
c_code = replace_in_func('HSD_TExpCompile', 'tevdesc', 'tevdesc_out', c_code)
c_code = replace_in_func('HSD_TExpCompile', 'num', 'num_nodes', c_code)
c_code = replace_in_func('HSD_TExpCompile', 'val', 'assign_res', c_code)
c_code = replace_in_func('HSD_TExpCompile', 'tdesc', 'new_tevdesc', c_code)

# Some missing comments for internal functions?
# We only need to document the functions we care about, but the prompt says "add Doxygen comments to ALL functions"
# Let's add them to the remaining ones.

internal_func_docs = {
    "TevAlloc": "/**\n * @brief Allocates a new TEV node.\n * @return Pointer to new HSD_TExp\n */",
    "CnstAlloc": "/**\n * @brief Allocates a new constant node.\n * @return Pointer to new HSD_TExp\n */",
    "HSD_TExpColorInSub": "/**\n * @brief Subroutine to map a single color input in the TEV stage.\n * @param tev TEV node\n * @param sel Input selector\n * @param exp Expression\n * @param idx Input index (0-3)\n */",
    "HSD_TExpAlphaInSub": "/**\n * @brief Subroutine to map a single alpha input in the TEV stage.\n * @param tev TEV node\n * @param sel Input selector\n * @param exp Expression\n * @param idx Input index (0-3)\n */",
    "AssignColorReg": "/**\n * @brief Assigns a color register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "AssignAlphaReg": "/**\n * @brief Assigns an alpha register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "AssignColorKonst": "/**\n * @brief Assigns a KColor register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "AssignAlphaKonst": "/**\n * @brief Assigns a KAlpha register for the given TEV input.\n * @param tev TEV node\n * @param in_idx Input index\n * @param texp_res Resources state tracking\n * @return 0 on success, -1 on failure\n */",
    "HSD_TExpSimplify": "/**\n * @brief Simplifies the expression tree by combining or pruning nodes.\n * @param texp Expression tree\n */",
    "HSD_TExpSimplify2": "/**\n * @brief Secondary simplification pass for TEV expressions.\n * @param texp Expression tree\n */",
    "HSD_TExpMakeDag": "/**\n * @brief Converts the expression tree into a Directed Acyclic Graph (DAG) array.\n * @param texp Root expression node\n * @param list DAG array output\n * @return Number of nodes in the DAG\n */",
    "HSD_TExpSchedule": "/**\n * @brief Schedules the DAG nodes into a linear sequence for hardware configuration.\n * @param num_nodes Number of nodes\n * @param list DAG array\n * @param order Output array representing scheduling order\n * @param res Resources tracking\n */",
    "TExpAssignReg": "/**\n * @brief Allocates hardware registers to expression nodes during compilation.\n * @param texp Expression node\n * @param res Resources tracking\n * @return 0 on success\n */",
    "TExp2TevDesc": "/**\n * @brief Converts an expression node to a hardware-ready TEV descriptor.\n * @param texp Expression node\n * @param desc Output TEV descriptor\n * @param init_cprev Pointer to initialization flag for cprev\n * @param init_aprev Pointer to initialization flag for aprev\n */",
    "HSD_Index2TevStage": "/**\n * @brief Translates an integer index into a GX TEV stage enum.\n * @param idx Stage index\n * @return TEV stage enum\n */",
}

for func, doc in internal_func_docs.items():
    pattern = r'^(.*?)([a-zA-Z_][a-zA-Z0-9_]*\s*\**\s*' + func + r'\s*\([^)]*\)\s*\{)'
    c_code = re.sub(pattern, r'\1' + doc + r'\n\2', c_code, flags=re.MULTILINE)

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/texp.c', 'w') as f:
    f.write(c_code)

print("Done python script")
