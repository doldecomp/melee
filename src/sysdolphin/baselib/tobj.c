#include "sysdolphin/baselib/tobj.h"

#include "sysdolphin/baselib/aobj.h"

extern void TObjInfoInit(void);

HSD_TObjInfo hsdTObj = { TObjInfoInit };

extern char lbl_804055B8[];
extern char lbl_804D5C90[7];// = "tobj.c\0";

void HSD_TObjRemoveAnim(HSD_TObj* tobj)
{
    if (tobj == NULL){
        return;
    }

    HSD_AObjRemove(tobj->aobj);
    tobj->aobj = NULL;
}

void HSD_TObjRemoveAnimAll(HSD_TObj* tobj)
{
    HSD_TObj* tp;

    if (tobj != NULL){
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjRemoveAnim(tp);
        }
    }
}

static HSD_TexAnim* lookupTextureAnim(s32 id, HSD_TexAnim* texanim)
{
    HSD_TexAnim* ta;
    for (ta = texanim; ta; ta = ta->next) {
        if (ta->id == id)
            return ta;
    }
    return NULL;
}

void HSD_TObjAddAnim(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    s32 i;
    HSD_TexAnim* ta;

    if (tobj != NULL) {
        if ((ta = lookupTextureAnim(tobj->id, texanim)) != NULL) {
            if (tobj->aobj != NULL) {
                HSD_AObjRemove(tobj->aobj);
            }
            tobj->aobj = HSD_AObjLoadDesc(ta->aobjdesc);
            tobj->imagetbl = ta->imagetbl;

            if (tobj->tluttbl != NULL) {
                for (i = 0; tobj->tluttbl[i]; i++) {
                    HSD_TlutFree(tobj->tluttbl[i]);
                }
                HSD_Free(tobj->tluttbl);
            }

            if (ta->n_tluttbl) {
                tobj->tluttbl = (HSD_Tlut**)HSD_MemAlloc((s32)sizeof(HSD_Tlut*) * (ta->n_tluttbl + 1));
                for (i = 0; i < ta->n_tluttbl; i++) {
                    tobj->tluttbl[i] = HSD_TlutLoadDesc(ta->tluttbl[i]);
                }
                tobj->tluttbl[i] = NULL;
            } else {
                tobj->tluttbl = NULL;
            }
            tobj->tlut_no = -1;
        }
    }
}

void HSD_TObjAddAnimAll(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp; tp = tp->next) {
            HSD_TObjAddAnim(tp, texanim);
        }
    }
}

void HSD_TObjReqAnimByFlags(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    if (tobj != NULL) {
        if (flags & TOBJ_ANIM) {
            HSD_AObjReqAnim(tobj->aobj, startframe);
        }
    }
}

void HSD_TObjReqAnimAllByFlags(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjReqAnimByFlags(tp, startframe, flags);
        }
    }
}

void HSD_TObjReqAnim(HSD_TObj* tobj, f32 startframe)
{
    HSD_TObjReqAnimByFlags(tobj, startframe, TOBJ_ANIM);
}

void HSD_TObjReqAnimAll(HSD_TObj* tobj, f32 startframe)
{
    HSD_TObjReqAnimAllByFlags(tobj, startframe, TOBJ_ANIM);
}

// Non-matching due to jump table
#ifdef NON_MATCHING
static void TObjUpdateFunc(void* obj, u32 type, FObjData* val)
{
    HSD_TObj* tobj = obj;

    if (tobj == NULL)
        return;

    switch (type) {
    case HSD_A_T_TIMG: {
        int n;
        if (tobj->imagetbl == NULL){
            __assert(lbl_804D5C90, 276, lbl_804055B8);
        }
        n = (int)val->fv;
        if (tobj->imagetbl[n]) {
            tobj->imagedesc = tobj->imagetbl[n];
        }
    } break;
    case HSD_A_T_TCLT: {
        if (tobj->tluttbl) {
            tobj->tlut_no = (u8)val->fv;
        }
    } break;
    case HSD_A_T_BLEND:
        tobj->blending = val->fv;
        break;
    case HSD_A_T_ROTX:
        tobj->rotate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTY:
        tobj->rotate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTZ:
        tobj->rotate.z = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAU:
        tobj->translate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAV:
        tobj->translate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAU:
        tobj->scale.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAV:
        tobj->scale.y = val->fv;
        goto mtxdirty;
    mtxdirty:
        tobj->flags |= TEX_MTX_DIRTY;
        break;
    case HSD_A_T_LOD_BIAS:
        tobj->lod->LODBias = val->fv;
        break;
    case HSD_A_T_KONST_R:
        tobj->tev->konst.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_KONST_G:
        tobj->tev->konst.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_KONST_B:
        tobj->tev->konst.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_KONST_A:
        tobj->tev->konst.a = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_R:
        tobj->tev->tev0.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_G:
        tobj->tev->tev0.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_B:
        tobj->tev->tev0.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV0_A:
        tobj->tev->tev0.a = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_R:
        tobj->tev->tev1.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_G:
        tobj->tev->tev1.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_B:
        tobj->tev->tev1.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TEV1_A:
        tobj->tev->tev1.a = (u8)(255.0 * val->fv);
        break;
    case HSD_A_T_TS_BLEND:
        tobj->blending = val->fv;
        break;
    }
}
#endif
