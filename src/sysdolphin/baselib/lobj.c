#include "sysdolphin/baselib/lobj.h"

#include <dolphin/mtx.h>

void LObjInfoInit(void);

HSD_LObjInfo hsdLObj = { LObjInfoInit };

extern s32 lightmask_diffuse;
extern s32 lightmask_attnfunc;
extern s32 lightmask_alpha;
extern s32 lightmask_specular;

extern s32 nb_active_lights;

HSD_LObj* active_lights[MAX_GXLIGHT];

u32 HSD_LObjGetFlags(HSD_LObj* lobj)
{
    return (lobj) ? lobj->flags : 0;
}

void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL)
        return;
    lobj->flags |= flags;
}

void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL)
        return;
    lobj->flags &= ~flags;
}

s32 HSD_LObjGetLightMaskDiffuse(void)
{
    return lightmask_diffuse;
}

s32 HSD_LObjGetLightMaskAttnFunc(void)
{
    return lightmask_attnfunc;
}

s32 HSD_LObjGetLightMaskAlpha(void)
{
    return lightmask_alpha;
}

s32 HSD_LObjGetLightMaskSpecular(void)
{
    return lightmask_specular;
}

s32 HSD_LObjGetNbActive(void)
{
    return nb_active_lights;
}

HSD_LObj* HSD_LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < MAX_GXLIGHT) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < MAX_GXLIGHT - 1) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

/*static*/ void LObjUpdateFunc(void* obj, u32 type, FObjData* val)
{
    HSD_LObj* lobj = obj;

    if (lobj == NULL)
        return;

    switch (type) {
    case HSD_A_L_VIS:
        if (val->fv < 0.5) {
            lobj->flags &= ~LOBJ_HIDDEN;
        } else {
            lobj->flags |= LOBJ_HIDDEN;
        }
        break;
    case HSD_A_L_A0:
    case HSD_A_L_CUTOFF:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a0 = val->fv;
        } else {
            lobj->u.spot.cutoff = val->fv;
        }
        break;
    case HSD_A_L_A1:
    case HSD_A_L_REFDIST:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a1 = val->fv;
        } else {
            lobj->u.spot.ref_dist = val->fv;
        }
        break;
    case HSD_A_L_A2:
    case HSD_A_L_REFBRIGHT:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a2 = val->fv;
        } else {
            lobj->u.spot.ref_br = val->fv;
        }
        break;
    case HSD_A_L_K0:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k0 = val->fv;
        }
        break;
    case HSD_A_L_K1:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k1 = val->fv;
        }
        break;
    case HSD_A_L_K2:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k2 = val->fv;
        }
        break;
    case HSD_A_L_LITC_R:
        lobj->color.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_L_LITC_G:
        lobj->color.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_L_LITC_B:
        lobj->color.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_L_LITC_A:
        lobj->color.a = (u8)(255.0 * val->fv);
        break;
    }
}

void HSD_LObjAnim(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_AObjInterpretAnim(lobj->aobj, lobj, &LObjUpdateFunc);
        HSD_WObjInterpretAnim(HSD_LObjGetPositionWObj(lobj));
        HSD_WObjInterpretAnim(HSD_LObjGetInterestWObj(lobj));
    }
}

void HSD_LObjAnimAll(HSD_LObj *lobj)
{
    HSD_LObj *lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjAnim(lp);
    }
}

void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe)
{
    if (lobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(lobj->aobj, startframe);
    HSD_WObjReqAnim(HSD_LObjGetPositionWObj(lobj), startframe);
    HSD_WObjReqAnim(HSD_LObjGetInterestWObj(lobj), startframe);
}

void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjReqAnim(lp, startframe);
    }
}

void HSD_LObjGetLightVector(HSD_LObj *lobj, VecPtr dir)
{
    Vec position = {0.0F, 0.0F, 0.0F};
    Vec interest = {0.0F, 0.0F, 0.0F};

    if (lobj == NULL)
        return;

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    PSVECNormalize(dir, dir);
}

void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess, u32 unused)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        return;
    }

    if ((lobj->flags & LOBJ_DIFFUSE) != 0) {
        if (lobj->hw_color.r != color.r
            || lobj->hw_color.g != color.g
            || lobj->hw_color.b != color.b
            || lobj->hw_color.a != color.a) {
            
            GXInitLightColor(&lobj->lightobj, color);
            lobj->hw_color = color;
            lobj->flags |= LOBJ_DIFF_DIRTY;
        }

        if (lobj->flags & LOBJ_DIFF_DIRTY) {
            GXLoadLightObjImm(&lobj->lightobj, lobj->id);
            lobj->flags &= ~LOBJ_DIFF_DIRTY;
        }
    }

    if (lobj->spec_id != GX_LIGHT_NULL) {
        if (lobj->shininess != shininess) {
            lobj->shininess = shininess;
            k0 *= 0.5F;
            GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, k0, 0.0F, 1.0F - k0);
            lobj->flags |= LOBJ_SPEC_DIRTY;
        }

        if (lobj->flags & LOBJ_SPEC_DIRTY) {
            GXLoadLightObjImm(&lobj->spec_lightobj, lobj->spec_id);
            lobj->flags &= ~LOBJ_SPEC_DIRTY;
        }
    }
}
