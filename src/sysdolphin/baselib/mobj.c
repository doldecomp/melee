/**
 * @file mobj.c
 * @brief Material Object (MObj) system implementation
 * @details Handles the material properties for DObj meshes, including textures, colors, alpha, blending, and TEV configurations.
 * Module prefix: HSD_MObj
 */
#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

static HSD_ClassInfo* default_class;
static HSD_MObj* current_mobj;
HSD_TObj* tobj_shadows;
HSD_TObj* tobj_toon;

static void MObjInfoInit(void);
HSD_MObjInfo hsdMObj = { MObjInfoInit };

/**
 * @brief Sets the global active MObj instance.
 * @param mobj MObj pointer
 */
void HSD_MObjSetCurrent(HSD_MObj* mobj)
{
    current_mobj = mobj;
}

/**
 * @brief Appends render mode flags to the MObj.
 * @param mobj MObj pointer
 * @param flags Flags to set
 */
void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) {
        mobj->rendermode |= flags;
    }
}

/**
 * @brief Removes render mode flags from the MObj.
 * @param mobj MObj pointer
 * @param flags Flags to clear
 */
void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) {
        mobj->rendermode &= ~flags;
    }
}

/**
 * @brief Removes animation objects from the MObj based on anim flags (e.g. MOBJ_ANIM, TOBJ_ANIM).
 * @param mobj MObj pointer
 * @param flags Animation flags
 */
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj == NULL) {
        return;
    }

    if (flags & MOBJ_ANIM) {
        HSD_AObjRemove(mobj->aobj);
        mobj->aobj = NULL;
    }
    if (flags & TOBJ_ANIM) {
        HSD_TObjRemoveAnimAll(mobj->tobj);
    }
}

/**
 * @brief Adds a material animation description to the MObj, converting it to an AObj.
 * @param mobj MObj pointer
 * @param matanim Material animation descriptor
 */
void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    if (mobj == NULL) {
        return;
    }

    if (matanim != NULL) {
        if (mobj->aobj != NULL) {
            HSD_AObjRemove(mobj->aobj);
        }
        mobj->aobj = HSD_AObjLoadDesc(matanim->aobjdesc);
        HSD_TObjAddAnimAll(mobj->tobj, matanim->texanim);
    }
}

/**
 * @brief Requests the MObj's animation (including TObjs) to evaluate at the specified start frame, filtered by flags.
 * @param mobj MObj pointer
 * @param startframe Animation frame index
 * @param flags Animation flags
 */
void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags)
{
    if (mobj == NULL) {
        return;
    }
    if (flags & MOBJ_ANIM) {
        HSD_AObjReqAnim(mobj->aobj, startframe);
    }
    HSD_TObjReqAnimAllByFlags(mobj->tobj, startframe, flags);
}

/**
 * @brief Requests the MObj's animation to evaluate at the specified frame (ALL_ANIM).
 * @param mobj MObj pointer
 * @param startframe Animation frame index
 */
void HSD_MObjReqAnim(HSD_MObj* mobj, f32 startframe)
{
    HSD_MObjReqAnimByFlags(mobj, startframe, ALL_ANIM);
}

/**
 * @brief Callback applied during AObj interpretation to update material properties (ambient, diffuse, specular, alpha, PE).
 * @param obj Cast to MObj pointer
 * @param type ID of the material field being updated
 * @param anim_data The animation value to apply
 */
static void MObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* anim_data)
{
    HSD_MObj* mobj = obj;

    if (mobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_M_AMBIENT_R:
        mobj->mat->ambient.r = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_AMBIENT_G:
        mobj->mat->ambient.g = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_AMBIENT_B:
        mobj->mat->ambient.b = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_DIFFUSE_R:
        mobj->mat->diffuse.r = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_DIFFUSE_G:
        mobj->mat->diffuse.g = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_DIFFUSE_B:
        mobj->mat->diffuse.b = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_ALPHA:
        mobj->mat->alpha = 1.0F - anim_data->fv;
        break;
    case HSD_A_M_SPECULAR_R:
        mobj->mat->specular.r = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_SPECULAR_G:
        mobj->mat->specular.g = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_SPECULAR_B:
        mobj->mat->specular.b = (u8) (255.0 * anim_data->fv);
        break;
    case HSD_A_M_PE_REF0:
        if (mobj->pe) {
            mobj->pe->ref0 = (u8) (255.0 * anim_data->fv);
        }
        break;
    case HSD_A_M_PE_REF1:
        if (mobj->pe) {
            mobj->pe->ref1 = (u8) (255.0 * anim_data->fv);
        }
        break;
    case HSD_A_M_PE_DSTALPHA:
        if (mobj->pe) {
            mobj->pe->dst_alpha = (u8) (255.0 * anim_data->fv);
        }
        break;
    }
}

/**
 * @brief Updates the animation state of the MObj and its associated TObjs.
 * @param mobj MObj pointer
 */
void HSD_MObjAnim(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return;
    }
    HSD_AObjInterpretAnim(mobj->aobj, mobj, MObjUpdateFunc);
    HSD_TObjAnimAll(mobj->tobj);
}

/**
 * @brief Initializes an MObj from an MObjDesc.
 * @param mobj MObj pointer to initialize
 * @param desc Material object descriptor
 * @return 0 on success
 */
static int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
{
    mobj->rendermode = desc->rendermode;
    mobj->tobj = HSD_TObjLoadDesc(desc->texdesc);
    mobj->mat = HSD_MaterialAlloc();
    memcpy(mobj->mat, desc->mat, sizeof(HSD_Material));
    mobj->rendermode |= RENDER_TOON;
    if (desc->pedesc != NULL) {
        mobj->pe = hsdAllocMemPiece(sizeof(HSD_PEDesc));
        memcpy(mobj->pe, desc->pedesc, sizeof(HSD_PEDesc));
    }
    mobj->aobj = NULL;
    return 0;
}

/**
 * @brief Allocates and loads an MObj and its material properties from an MObjDesc.
 * @param mobjdesc Material object descriptor
 * @return Newly allocated MObj
 */
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    if (mobjdesc) {
        HSD_MObj* mobj;
        HSD_ClassInfo* info;

        if (!mobjdesc->class_name ||
            !(info = hsdSearchClassInfo(mobjdesc->class_name)))
        {
            mobj = HSD_MObjAlloc();
        } else {
            mobj = hsdNew(info);
            HSD_ASSERT(353, mobj);
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}

/**
 * @brief Generates the TEV texture expression (TExp) tree based on the MObj's textures and rendering mode.
 * @param mobj MObj pointer
 * @param tobj_top Head of the TObj linked list
 * @param list Pointer to store the resulting TExp list
 * @return The root expression node
 */
HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list)
{
    HSD_TExp *diff, *spec, *ext, *alpha;
    HSD_TExp *texp1, *texp2, *texp3;
    HSD_TObj *curr_tobj, *diff_tobj, *spec_tobj, *ext_tobj, *toon_tobj = NULL;
    u32 done = 0;

    u8 _[20];

    HSD_ASSERT(416, list);
    *list = NULL;
    for (curr_tobj = tobj_top; curr_tobj != NULL; curr_tobj = curr_tobj->next) {
        if (tobj_coord(curr_tobj) == TEX_COORD_TOON) {
            toon_tobj = curr_tobj;
        }
    }

    if (mobj->rendermode & RENDER_VERTEX) {
        texp1 = HSD_TExpTev(list);
        HSD_TExpOrder(texp1, NULL, GX_COLOR0A0);
        HSD_TExpColorOp(texp1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(texp1, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, HSD_TEXP_RAS);
        HSD_TExpAlphaOp(texp1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpAlphaIn(texp1, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS);
        diff = texp1;
        alpha = texp1;
    } else {
        HSD_TExp* diff_cnst =
            HSD_TExpCnst(&mobj->mat->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
        HSD_TExp* alpha_cnst =
            HSD_TExpCnst(&mobj->mat->alpha, HSD_TE_X, HSD_TE_F32, list);

        texp1 = HSD_TExpTev(list);
        HSD_TExpColorOp(texp1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(texp1, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff_cnst);
        HSD_TExpAlphaOp(texp1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpAlphaIn(texp1, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, alpha_cnst);
        diff = texp1;
        alpha = texp1;
    }

    for (diff_tobj = tobj_top; diff_tobj != NULL; diff_tobj = diff_tobj->next) {
        if ((diff_tobj->flags & (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT)) &&
            diff_tobj->id != GX_TEXMAP_NULL)
        {
            HSD_TOBJ_METHOD(diff_tobj)->make_texp(
                diff_tobj, (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT), done,
                &diff, &alpha, list);
        }
    }
    done |= (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT);

    if (mobj->rendermode & RENDER_DIFFUSE) {
        texp2 = HSD_TExpTev(list);
        if (toon_tobj != NULL) {
            HSD_TExpOrder(texp2, toon_tobj, GX_COLOR0A0);
            HSD_TExpColorOp(texp2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(texp2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_TEX, HSD_TE_0, HSD_TEXP_ZERO);
        } else {
            HSD_TExpOrder(texp2, NULL, GX_COLOR0A0);
            HSD_TExpColorOp(texp2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(texp2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        }
        diff = texp2;
        HSD_TExpAlphaOp(texp2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpAlphaIn(texp2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, alpha,
                        HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        alpha = texp2;
    }

    if (mobj->rendermode & RENDER_SPECULAR) {
        HSD_TExp* cnst =
            HSD_TExpCnst(&mobj->mat->specular, HSD_TE_RGB, HSD_TE_U8, list);
        texp3 = HSD_TExpTev(list);
        HSD_TExpColorOp(texp3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(texp3, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB,
                        cnst);
        spec = texp3;

        for (spec_tobj = tobj_top; spec_tobj != NULL; spec_tobj = spec_tobj->next) {
            if ((spec_tobj->flags & TEX_LIGHTMAP_SPECULAR) &&
                spec_tobj->id != GX_TEXMAP_NULL)
            {
                HSD_TOBJ_METHOD(spec_tobj)->make_texp(
                    spec_tobj, TEX_LIGHTMAP_SPECULAR, done, &spec, &alpha, list);
            }
        }
        done |= TEX_LIGHTMAP_SPECULAR;

        texp3 = HSD_TExpTev(list);
        HSD_TExpOrder(texp3, NULL, GX_COLOR1A1);
        HSD_TExpColorOp(texp3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(texp3, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, spec,
                        HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        spec = texp3;

        texp3 = HSD_TExpTev(list);
        HSD_TExpColorOp(texp3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(texp3, HSD_TE_RGB, spec, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff);
        diff = texp3;
    }

    ext = diff;

    for (ext_tobj = tobj_top; ext_tobj != NULL; ext_tobj = ext_tobj->next) {
        if ((ext_tobj->flags & TEX_LIGHTMAP_EXT) && ext_tobj->id != GX_TEXMAP_NULL)
        {
            HSD_TOBJ_METHOD(ext_tobj)->make_texp(ext_tobj, TEX_LIGHTMAP_EXT, done,
                                               &ext, &alpha, list);
        }
    }

    if (ext != alpha || HSD_TExpGetType(ext) != HSD_TE_TEV ||
        HSD_TExpGetType(alpha) != HSD_TE_TEV)
    {
        texp2 = HSD_TExpTev(list);
        HSD_TExpColorOp(texp2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(texp2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB,
                        ext);
        HSD_TExpAlphaOp(texp2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpAlphaIn(texp2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                        alpha);
        return texp2;
    }

    return ext;
}

/**
 * @brief Compiles TEV (Texture Environment) texture expressions for the MObj.
 * @param mobj MObj pointer
 */
void HSD_MObjCompileTev(HSD_MObj* mobj)
{
    HSD_TObj *tobj, **shadow_tail;
    HSD_TExp* texp;

    shadow_tail = NULL;
    if (mobj != NULL) {
        if (mobj->tevdesc != NULL) {
            HSD_TExpFreeTevDesc(mobj->tevdesc);
            mobj->tevdesc = NULL;
        }
        if (mobj->texp != NULL) {
            HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
            mobj->texp = NULL;
        }
        tobj = mobj->tobj;
        if (mobj->rendermode & RENDER_SHADOW) {
            if (tobj_shadows != NULL) {
                shadow_tail = &tobj;
                while (*shadow_tail != NULL) {
                    shadow_tail = &(*shadow_tail)->next;
                }
                *shadow_tail = tobj_shadows;
            }
        }
        if (mobj->rendermode & RENDER_TOON) {
            if (tobj_toon != NULL && tobj_toon->imagedesc != NULL) {
                tobj_toon->next = tobj;
                tobj = tobj_toon;
            }
        }
        HSD_TObjAssignResources(tobj);
        texp = HSD_MOBJ_METHOD(mobj)->make_texp(mobj, tobj, &mobj->texp);
        HSD_TExpCompile(texp, &mobj->tevdesc, &mobj->texp);
        if (shadow_tail != NULL) {
            *shadow_tail = NULL;
        }
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused1[] = "hsdIsDescendantOf(info, &hsdMObj)";
#endif

/**
 * @brief Loads the compiled TEV configuration to GX hardware registers.
 * @param mobj MObj pointer
 * @param tobj Texture object
 * @param arg2 Additional volatile config flag
 */
void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 arg2)
{
    HSD_ASSERT(624, mobj->tevdesc);
    HSD_TExpSetupTev(mobj->tevdesc, mobj->texp);
    HSD_TObjSetupVolatileTev(tobj, arg2);
}

/**
 * @brief Main material setup function before drawing a mesh. Configures GX colors, TEV, textures, and blending (PE).
 * @param mobj MObj pointer
 * @param rendermode Current rendering mode
 */
void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObj *tobj, **tail;

    HSD_StateInitTev();
    rendermode = mobj->rendermode;
    HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                         mobj->mat->specular, mobj->mat->alpha);
    if (rendermode & RENDER_SPECULAR) {
        HSD_SetMaterialShininess(mobj->mat->shininess);
    }

    tobj = mobj->tobj;
    tail = NULL;

    if ((rendermode & RENDER_SHADOW) && tobj_shadows != NULL) {
        tail = &tobj;
        while (*tail != NULL) {
            tail = &(*tail)->next;
        }
        *tail = tobj_shadows;
    }
    if ((rendermode & RENDER_TOON) && tobj_toon != NULL &&
        tobj_toon->imagedesc != NULL)
    {
        tobj_toon->next = tobj;
        tobj = tobj_toon;
    }
    HSD_TObjSetup(tobj);
    HSD_TObjSetupTextureCoordGen(tobj);
    HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj, rendermode);
    HSD_SetupRenderModeWithCustomPE(rendermode, mobj->pe);
    if (tail != NULL) {
        *tail = NULL;
    }
}

/**
 * @brief Cleans up GX state after drawing a mesh with this MObj.
 * @param mobj MObj pointer
 * @param rendermode Current rendering mode
 */
void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObjSetup(NULL);
}

static HSD_TObjDesc tobj_toon_desc = { NULL,
                                       NULL,
                                       GX_TEXMAP7,
                                       GX_TG_COLOR0,
                                       { 0.0F, 0.0F, 0.0F },
                                       { 0.0F, 0.0F, 0.0F },
                                       { 0.0F, 0.0F, 0.0F },
                                       GX_CLAMP,
                                       GX_CLAMP,
                                       0,
                                       0,
                                       TEX_COORD_TOON,
                                       1.0F,
                                       GX_LINEAR,
                                       0,
                                       NULL,
                                       NULL };

/**
 * @brief Sets the global texture image used for toon-shading rendering.
 * @param imagedesc Image descriptor for toon shading
 */
void HSD_MObjSetToonTextureImage(HSD_ImageDesc* imagedesc)
{
    if (tobj_toon == NULL) {
        tobj_toon_desc.imagedesc = imagedesc;
        tobj_toon = HSD_TObjLoadDesc(&tobj_toon_desc);
        HSD_ASSERTREPORT(0x2F8, tobj_toon, "cannot allocate tobj for toon.");
    }
    tobj_toon->imagedesc = imagedesc;
}

/**
 * @brief Overrides the diffuse color of the MObj's material.
 * @param mobj MObj pointer
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 */
void HSD_MObjSetDiffuseColor(HSD_MObj* mobj, u8 r, u8 g, u8 b)
{
    mobj->mat->diffuse.r = r;
    mobj->mat->diffuse.g = g;
    mobj->mat->diffuse.b = b;
}

/**
 * @brief Overrides the alpha blending value of the MObj's material.
 * @param mobj MObj pointer
 * @param alpha New alpha value (0.0 to 1.0)
 */
void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha)
{
    mobj->mat->alpha = alpha;
}

/**
 * @brief Retrieves the linked list of texture objects (TObj) from the MObj.
 * @param mobj MObj pointer
 * @return Head of the TObj linked list
 */
HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return NULL;
    }
    return mobj->tobj;
}

/**
 * @brief Destroys and frees the MObj and its associated resources.
 * @param mobj MObj pointer
 */
void HSD_MObjRemove(HSD_MObj* mobj)
{
    if (mobj != NULL) {
        HSD_CLASS_METHOD(mobj)->release((HSD_Class*) mobj);
        HSD_CLASS_METHOD(mobj)->destroy((HSD_Class*) mobj);
    }
}

/**
 * @brief Allocates a new, uninitialized MObj instance.
 * @return Newly allocated MObj
 */
HSD_MObj* HSD_MObjAlloc(void)
{
    HSD_MObj* mobj =
        hsdNew(default_class != NULL ? default_class : &hsdMObj.parent);
    HSD_ASSERT(915, mobj);
    return mobj;
}

/**
 * @brief Allocates a new HSD_Material struct, initializing its alpha to 1.0.
 * @return Newly allocated Material
 */
HSD_Material* HSD_MaterialAlloc(void)
{
    HSD_Material* mat = hsdAllocMemPiece(sizeof(HSD_Material));
    HSD_ASSERT(943, mat);
    memset(mat, 0, sizeof(HSD_Material));
    mat->alpha = 1.0F;
    return mat;
}

/**
 * @brief Adds a texture object to the global shadow texture list.
 * @param tobj Texture object
 */
void HSD_MObjAddShadowTexture(HSD_TObj* tobj)
{
    HSD_TObj* cur;
    HSD_ASSERT(990, tobj);
    for (cur = tobj_shadows; cur != NULL; cur = cur->next) {
        if (cur == tobj) {
            return;
        }
    }
    tobj->next = tobj_shadows;
    tobj_shadows = tobj;
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused2[] = "mobj->rendermode&RENDER_SPECULAR";
#pragma pop
#endif

/**
 * @brief Removes a texture object from the global shadow texture list.
 * @param tobj Texture object
 */
void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj)
{
    if (tobj != NULL) {
        HSD_TObj** curr_tobj = &tobj_shadows;
        while (*curr_tobj != NULL) {
            if (*curr_tobj == tobj) {
                *curr_tobj = tobj->next;
                tobj->next = NULL;
                return;
            }
            curr_tobj = &(*curr_tobj)->next;
        }
    } else {
        HSD_TObj* next_tobj;
        for (next_tobj = NULL; tobj_shadows != NULL; tobj_shadows = next_tobj) {
            next_tobj = tobj_shadows->next;
            tobj_shadows->next = NULL;
        }
    }
}

/**
 * @brief Internal release method for freeing MObj components.
 * @param o MObj as HSD_Class
 */
static void MObjRelease(HSD_Class* o)
{
    HSD_MObj* mobj = HSD_MOBJ(o);

    HSD_AObjRemove(mobj->aobj);
    hsdFreeMemPiece(mobj->mat, sizeof(HSD_Material));
    HSD_TObjRemoveAll(mobj->tobj);

    if (mobj->tevdesc != NULL) {
        HSD_TExpFreeTevDesc(mobj->tevdesc);
    }
    if (mobj->texp != NULL) {
        HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
    }
    if (mobj->pe != NULL) {
        hsdFreeMemPiece(mobj->pe, sizeof(HSD_PEDesc));
    }
    HSD_PARENT_INFO(&hsdMObj)->release(o);
}

/**
 * @brief Clears global references (e.g. toon/shadow tobjs) upon class teardown.
 * @param info Class info pointer
 */
static void MObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdMObj)) {
        tobj_toon = NULL;
        tobj_shadows = NULL;
    }
    HSD_PARENT_INFO(&hsdMObj)->amnesia(info);
}

/**
 * @brief Initializes the HSD_MObj class info and virtual methods.
 */
static void MObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdMObj), HSD_CLASS_INFO(&hsdClass),
                     "sysdolphin_base_library", "hsd_mobj",
                     sizeof(HSD_MObjInfo), sizeof(HSD_MObj));

    HSD_CLASS_INFO(&hsdMObj)->release = MObjRelease;
    HSD_CLASS_INFO(&hsdMObj)->amnesia = MObjAmnesia;
    HSD_MOBJ_INFO(&hsdMObj)->setup = HSD_MObjSetup;
    HSD_MOBJ_INFO(&hsdMObj)->unset = HSD_MObjUnset;
    HSD_MOBJ_INFO(&hsdMObj)->load = MObjLoad;
    HSD_MOBJ_INFO(&hsdMObj)->make_texp = MObjMakeTExp;
    HSD_MOBJ_INFO(&hsdMObj)->setup_tev = MObjSetupTev;
}
