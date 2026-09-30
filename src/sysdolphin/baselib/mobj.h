/**
 * @file mobj.h
 * @brief Material Object (MObj) system for rendering
 * @details Defines material properties for DObj meshes: textures, colors, alpha, blending, and TEV configurations.
 * Module prefix: HSD_MObj
 */
#ifndef _mobj_h_
#define _mobj_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dolphin/gx.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/texp.h>
#include <sysdolphin/baselib/tobj.h>

#define MOBJ_ANIM 0x4
#define TOBJ_ANIM 0x10
#define ALL_ANIM 0x7FF

#define HSD_A_M_AMBIENT_R 1
#define HSD_A_M_AMBIENT_G 2
#define HSD_A_M_AMBIENT_B 3
#define HSD_A_M_DIFFUSE_R 4
#define HSD_A_M_DIFFUSE_G 5
#define HSD_A_M_DIFFUSE_B 6
#define HSD_A_M_SPECULAR_R 7
#define HSD_A_M_SPECULAR_G 8
#define HSD_A_M_SPECULAR_B 9
#define HSD_A_M_ALPHA 10
#define HSD_A_M_PE_REF0 11
#define HSD_A_M_PE_REF1 12
#define HSD_A_M_PE_DSTALPHA 13

#define RENDER_DIFFUSE_SHIFT 0
#define RENDER_DIFFUSE_BITS (3 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_MAT0 (0 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_MAT (1 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_VTX (2 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_BOTH (3 << RENDER_DIFFUSE_SHIFT)

#define RENDER_CONSTANT (1 << 0)
#define RENDER_VERTEX (1 << 1)
#define RENDER_DIFFUSE (1 << 2)
#define RENDER_SPECULAR (1 << 3)
#define CHANNEL_FIELD                                                         \
    (RENDER_CONSTANT | RENDER_VERTEX | RENDER_DIFFUSE | RENDER_SPECULAR)
#define RENDER_TEX0 (1 << 4)
#define RENDER_TEX1 (1 << 5)
#define RENDER_TEX2 (1 << 6)
#define RENDER_TEX3 (1 << 7)
#define RENDER_TEX4 (1 << 8)
#define RENDER_TEX5 (1 << 9)
#define RENDER_TEX6 (1 << 10)
#define RENDER_TEX7 (1 << 11)
#define RENDER_TEXTURES                                                       \
    (RENDER_TEX0 | RENDER_TEX1 | RENDER_TEX2 | RENDER_TEX3 | RENDER_TEX4 |    \
     RENDER_TEX5 | RENDER_TEX6 | RENDER_TEX7)
#define RENDER_TOON (1 << 12)

#define RENDER_ALPHA_SHIFT 13
#define RENDER_ALPHA_BITS (3 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_COMPAT (0 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_MAT (1 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_VTX (2 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_BOTH (3 << RENDER_ALPHA_SHIFT)

#define RENDER_SHADOW (1 << 26)
#define RENDER_ZMODE_ALWAYS (1 << 27)
#define RENDER_NO_ZUPDATE (1 << 29)
#define RENDER_XLU (1 << 30)

#define RENDER_BLENDING (RENDER_XLU | RENDER_NO_ZUPDATE)

struct HSD_MObj {
    HSD_Class parent;
    u32 rendermode;
    HSD_TObj* tobj;
    HSD_Material* mat;
    HSD_PEDesc* pe;
    HSD_AObj* aobj;
    struct _HSD_TExpTevDesc* tevdesc;
    HSD_TExp* texp;
};

struct HSD_Material {
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    f32 alpha;
    f32 shininess;
};

struct HSD_PEDesc {
    u8 flags;
    u8 ref0;
    u8 ref1;
    u8 dst_alpha;
    u8 type;
    u8 src_factor;
    u8 dst_factor;
    u8 logic_op;
    u8 z_comp;
    u8 alpha_comp0;
    u8 alpha_op;
    u8 alpha_comp1;
};

typedef struct _HSD_MObjDesc {
    char* class_name;
    u32 rendermode;
    struct _HSD_TObjDesc* texdesc;
    HSD_Material* mat;
    void* renderdesc;
    HSD_PEDesc* pedesc;
} HSD_MObjDesc;

typedef struct _HSD_ChanAnim {
    struct _HSD_ChanAnim* next;
    HSD_AObjDesc* aobjdesc;
} HSD_ChanAnim;

typedef struct _HSD_TevRegAnim {
    struct _HSD_TevRegAnim* next;
    HSD_AObjDesc* aobjdesc;
} HSD_TevRegAnim;

typedef struct _HSD_RenderAnim {
    struct _HSD_ChanAnim* chananim;
    struct _HSD_TevRegAnim* reganim;
} HSD_RenderAnim;

typedef struct _HSD_MatAnim {
    struct _HSD_MatAnim* next;
    HSD_AObjDesc* aobjdesc;
    struct _HSD_TexAnim* texanim;
    struct _HSD_RenderAnim* renderanim;
} HSD_MatAnim;

struct HSD_MatAnimJoint {
    HSD_MatAnimJoint* child;
    HSD_MatAnimJoint* next;
    HSD_MatAnim* matanim;
};

struct HSD_MObjInfo {
    /*  +0 */ HSD_ClassInfo parent;
    /* +3C */ HSD_MObjSetupFunc setup;
    /* +40 */ int (*load)(HSD_MObj* mobj, HSD_MObjDesc* desc);
    /* +44 */ HSD_TExp* (*make_texp)(HSD_MObj* mobj, HSD_TObj* tobj_top,
                                     HSD_TExp** list);
    /* +48 */ void (*setup_tev)(HSD_MObj* mobj, HSD_TObj* tobj,
                                u32 rendermode);
    /* +4C */ void (*unset)(HSD_MObj* mobj, u32 rendermode);
};

#define HSD_MOBJ(o) ((HSD_MObj*) (o))
#define HSD_MOBJ_INFO(i) ((HSD_MObjInfo*) (i))
#define HSD_MOBJ_METHOD(o) HSD_MOBJ_INFO(HSD_CLASS_METHOD(o))

extern HSD_MObjInfo hsdMObj;

/**
 * @brief Sets the global active MObj instance.
 * @param mobj MObj pointer
 */
void HSD_MObjSetCurrent(HSD_MObj* mobj);
/**
 * @brief Appends render mode flags to the MObj.
 * @param mobj MObj pointer
 * @param flags Flags to set
 */
void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags);
/**
 * @brief Removes render mode flags from the MObj.
 * @param mobj MObj pointer
 * @param flags Flags to clear
 */
void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags);
/**
 * @brief Removes animation objects from the MObj based on anim flags (e.g. MOBJ_ANIM, TOBJ_ANIM).
 * @param mobj MObj pointer
 * @param flags Animation flags
 */
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags);
/**
 * @brief Adds a material animation description to the MObj, converting it to an AObj.
 * @param mobj MObj pointer
 * @param matanim Material animation descriptor
 */
void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim);
/**
 * @brief Requests the MObj's animation (including TObjs) to evaluate at the specified start frame, filtered by flags.
 * @param mobj MObj pointer
 * @param startframe Animation frame index
 * @param flags Animation flags
 */
void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags);
/**
 * @brief Requests the MObj's animation to evaluate at the specified frame (ALL_ANIM).
 * @param mobj MObj pointer
 * @param startframe Animation frame index
 */
void HSD_MObjReqAnim(HSD_MObj* mobj, f32 startframe);
/**
 * @brief Updates the animation state of the MObj and its associated TObjs.
 * @param mobj MObj pointer
 */
void HSD_MObjAnim(HSD_MObj* mobj);
/**
 * @brief Allocates and loads an MObj and its material properties from an MObjDesc.
 * @param mobjdesc Material object descriptor
 * @return Newly allocated MObj
 */
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc);
/**
 * @brief Retrieves the linked list of texture objects (TObj) from the MObj.
 * @param mobj MObj pointer
 * @return Head of the TObj linked list
 */
HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj);
/**
 * @brief Destroys and frees the MObj and its associated resources.
 * @param mobj MObj pointer
 */
void HSD_MObjRemove(HSD_MObj* mobj);
/**
 * @brief Allocates a new, uninitialized MObj instance.
 * @return Newly allocated MObj
 */
HSD_MObj* HSD_MObjAlloc(void);
/**
 * @brief Allocates a new HSD_Material struct, initializing its alpha to 1.0.
 * @return Newly allocated Material
 */
HSD_Material* HSD_MaterialAlloc(void);
/**
 * @brief Compiles TEV (Texture Environment) texture expressions for the MObj.
 * @param mobj MObj pointer
 */
void HSD_MObjCompileTev(HSD_MObj* mobj);
/**
 * @brief Removes a texture object from the global shadow texture list.
 * @param tobj Texture object
 */
void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj);
/**
 * @brief Generates the TEV texture expression (TExp) tree based on the MObj's textures and rendering mode.
 * @param mobj MObj pointer
 * @param tobj_top Head of the TObj linked list
 * @param list Pointer to store the resulting TExp list
 * @return The root expression node
 */
HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list);
/**
 * @brief Loads the compiled TEV configuration to GX hardware registers.
 * @param mobj MObj pointer
 * @param tobj Texture object
 * @param arg2 Additional volatile config flag
 */
void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 arg2);

/**
 * @brief Main material setup function before drawing a mesh. Configures GX colors, TEV, textures, and blending (PE).
 * @param mobj MObj pointer
 * @param rendermode Current rendering mode
 */
void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode);
/**
 * @brief Cleans up GX state after drawing a mesh with this MObj.
 * @param mobj MObj pointer
 * @param rendermode Current rendering mode
 */
void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode);
/**
 * @brief Sets the global texture image used for toon-shading rendering.
 * @param imagedesc Image descriptor for toon shading
 */
void HSD_MObjSetToonTextureImage(HSD_ImageDesc* imagedesc);
/**
 * @brief Overrides the diffuse color of the MObj's material.
 * @param mobj MObj pointer
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 */
void HSD_MObjSetDiffuseColor(HSD_MObj* mobj, u8 r, u8 g, u8 b);
/**
 * @brief Overrides the alpha blending value of the MObj's material.
 * @param mobj MObj pointer
 * @param alpha New alpha value (0.0 to 1.0)
 */
void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha);
/**
 * @brief Adds a texture object to the global shadow texture list.
 * @param tobj Texture object
 */
void HSD_MObjAddShadowTexture(HSD_TObj* tobj);

extern HSD_TObj* tobj_shadows;
extern HSD_TObj* tobj_toon;

#endif
