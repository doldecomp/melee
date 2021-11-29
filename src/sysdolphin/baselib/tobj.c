#include "tobj.h"

#include "aobj.h"

inline void HSD_TObjRemoveAnim(HSD_TObj* tobj)
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

static inline HSD_TexAnim* lookupTextureAnim(s32 id, HSD_TexAnim* texanim)
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

inline void HSD_TObjReqAnimByFlags(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    if (tobj != NULL) {
        if (flags & TOBJ_ANIM) {
            HSD_AObjReqAnim(tobj->aobj, startframe);
        }
    }
}

inline void HSD_TObjReqAnimAllByFlags_inline(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjReqAnimByFlags(tp, startframe, flags);
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
    HSD_TObjReqAnimAllByFlags_inline(tobj, startframe, TOBJ_ANIM);
}
