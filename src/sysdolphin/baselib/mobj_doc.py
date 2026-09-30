import re

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'r') as f:
    c_code = f.read()

# Add file header
file_header = """/**
 * @file mobj.c
 * @brief Material Object (MObj) system implementation
 * @details Handles the material properties for DObj meshes, including textures, colors, alpha, blending, and TEV configurations.
 * Module prefix: HSD_MObj
 */
"""
if not c_code.startswith("/**"):
    c_code = file_header + c_code

def replace_in_func(func_name, old_var, new_var, text):
    pattern = r'(' + func_name + r'\s*\([^)]*\)\s*\{)(.*?)(^\})'
    
    def repl(m):
        body = m.group(2)
        body = re.sub(r'\b' + old_var + r'\b', new_var, body)
        return m.group(1) + body + m.group(3)
        
    return re.sub(pattern, repl, text, flags=re.DOTALL | re.MULTILINE)

# Variable renames
c_code = replace_in_func('MObjMakeTExp', 'exp', 'texp1', c_code)
c_code = replace_in_func('MObjMakeTExp', 'exp_2', 'texp2', c_code)
c_code = replace_in_func('MObjMakeTExp', 'exp_3', 'texp3', c_code)
c_code = replace_in_func('MObjMakeTExp', 'tobj', 'curr_tobj', c_code)
c_code = replace_in_func('MObjMakeTExp', 'tobj_2', 'diff_tobj', c_code)
c_code = replace_in_func('MObjMakeTExp', 'tobj_3', 'spec_tobj', c_code)
c_code = replace_in_func('MObjMakeTExp', 'tobj_4', 'ext_tobj', c_code)
c_code = replace_in_func('MObjMakeTExp', 'toon', 'toon_tobj', c_code)

c_code = replace_in_func('MObjUpdateFunc', 'val', 'anim_data', c_code)

c_code = replace_in_func('HSD_MObjDeleteShadowTexture', 'cur', 'curr_tobj', c_code)
c_code = replace_in_func('HSD_MObjDeleteShadowTexture', 'next', 'next_tobj', c_code)

c_code = replace_in_func('HSD_MObjCompileTev', 'tail', 'shadow_tail', c_code)

func_docs_c = {
    "HSD_MObjSetCurrent": "/**\n * @brief Sets the global active MObj instance.\n * @param mobj MObj pointer\n */",
    "HSD_MObjSetFlags": "/**\n * @brief Appends render mode flags to the MObj.\n * @param mobj MObj pointer\n * @param flags Flags to set\n */",
    "HSD_MObjClearFlags": "/**\n * @brief Removes render mode flags from the MObj.\n * @param mobj MObj pointer\n * @param flags Flags to clear\n */",
    "HSD_MObjRemoveAnimByFlags": "/**\n * @brief Removes animation objects from the MObj based on anim flags (e.g. MOBJ_ANIM, TOBJ_ANIM).\n * @param mobj MObj pointer\n * @param flags Animation flags\n */",
    "HSD_MObjAddAnim": "/**\n * @brief Adds a material animation description to the MObj, converting it to an AObj.\n * @param mobj MObj pointer\n * @param matanim Material animation descriptor\n */",
    "HSD_MObjReqAnimByFlags": "/**\n * @brief Requests the MObj's animation (including TObjs) to evaluate at the specified start frame, filtered by flags.\n * @param mobj MObj pointer\n * @param startframe Animation frame index\n * @param flags Animation flags\n */",
    "HSD_MObjReqAnim": "/**\n * @brief Requests the MObj's animation to evaluate at the specified frame (ALL_ANIM).\n * @param mobj MObj pointer\n * @param startframe Animation frame index\n */",
    "MObjUpdateFunc": "/**\n * @brief Callback applied during AObj interpretation to update material properties (ambient, diffuse, specular, alpha, PE).\n * @param obj Cast to MObj pointer\n * @param type ID of the material field being updated\n * @param anim_data The animation value to apply\n */",
    "HSD_MObjAnim": "/**\n * @brief Updates the animation state of the MObj and its associated TObjs.\n * @param mobj MObj pointer\n */",
    "MObjLoad": "/**\n * @brief Initializes an MObj from an MObjDesc.\n * @param mobj MObj pointer to initialize\n * @param desc Material object descriptor\n * @return 0 on success\n */",
    "HSD_MObjLoadDesc": "/**\n * @brief Allocates and loads an MObj and its material properties from an MObjDesc.\n * @param mobjdesc Material object descriptor\n * @return Newly allocated MObj\n */",
    "MObjMakeTExp": "/**\n * @brief Generates the TEV texture expression (TExp) tree based on the MObj's textures and rendering mode.\n * @param mobj MObj pointer\n * @param tobj_top Head of the TObj linked list\n * @param list Pointer to store the resulting TExp list\n * @return The root expression node\n */",
    "HSD_MObjCompileTev": "/**\n * @brief Compiles TEV (Texture Environment) texture expressions for the MObj.\n * @param mobj MObj pointer\n */",
    "MObjSetupTev": "/**\n * @brief Loads the compiled TEV configuration to GX hardware registers.\n * @param mobj MObj pointer\n * @param tobj Texture object\n * @param arg2 Additional volatile config flag\n */",
    "HSD_MObjSetup": "/**\n * @brief Main material setup function before drawing a mesh. Configures GX colors, TEV, textures, and blending (PE).\n * @param mobj MObj pointer\n * @param rendermode Current rendering mode\n */",
    "HSD_MObjUnset": "/**\n * @brief Cleans up GX state after drawing a mesh with this MObj.\n * @param mobj MObj pointer\n * @param rendermode Current rendering mode\n */",
    "HSD_MObjSetToonTextureImage": "/**\n * @brief Sets the global texture image used for toon-shading rendering.\n * @param imagedesc Image descriptor for toon shading\n */",
    "HSD_MObjSetDiffuseColor": "/**\n * @brief Overrides the diffuse color of the MObj's material.\n * @param mobj MObj pointer\n * @param r Red channel\n * @param g Green channel\n * @param b Blue channel\n */",
    "HSD_MObjSetAlpha": "/**\n * @brief Overrides the alpha blending value of the MObj's material.\n * @param mobj MObj pointer\n * @param alpha New alpha value (0.0 to 1.0)\n */",
    "HSD_MObjGetTObj": "/**\n * @brief Retrieves the linked list of texture objects (TObj) from the MObj.\n * @param mobj MObj pointer\n * @return Head of the TObj linked list\n */",
    "HSD_MObjRemove": "/**\n * @brief Destroys and frees the MObj and its associated resources.\n * @param mobj MObj pointer\n */",
    "HSD_MObjAlloc": "/**\n * @brief Allocates a new, uninitialized MObj instance.\n * @return Newly allocated MObj\n */",
    "HSD_MaterialAlloc": "/**\n * @brief Allocates a new HSD_Material struct, initializing its alpha to 1.0.\n * @return Newly allocated Material\n */",
    "HSD_MObjAddShadowTexture": "/**\n * @brief Adds a texture object to the global shadow texture list.\n * @param tobj Texture object\n */",
    "HSD_MObjDeleteShadowTexture": "/**\n * @brief Removes a texture object from the global shadow texture list.\n * @param tobj Texture object\n */",
    "MObjRelease": "/**\n * @brief Internal release method for freeing MObj components.\n * @param o MObj as HSD_Class\n */",
    "MObjAmnesia": "/**\n * @brief Clears global references (e.g. toon/shadow tobjs) upon class teardown.\n * @param info Class info pointer\n */",
    "MObjInfoInit": "/**\n * @brief Initializes the HSD_MObj class info and virtual methods.\n */",
}

for func, doc in func_docs_c.items():
    pattern = r'^(.*?)([a-zA-Z_][a-zA-Z0-9_]*\s+\*?\s*' + func + r'\s*\([^)]*\)\s*\{)'
    c_code = re.sub(pattern, r'\1' + doc + r'\n\2', c_code, flags=re.MULTILINE)

with open('/Users/kg/.gemini/antigravity/scratch/melee/src/sysdolphin/baselib/mobj.c', 'w') as f:
    f.write(c_code)

print("Done python script")
