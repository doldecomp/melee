#include "gr/granime.h"

#include <platform.h>

#include "baselib/debug.h"
#include "gr/grdatfiles.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbheap.h"

#include <stdarg.h>
#include <dolphin/os.h>
#include <baselib/aobj.h>
#include <baselib/dobj.h>
#include <baselib/mobj.h>
#include <baselib/robj.h>
#include <baselib/tobj.h>
#include <Runtime/Gecko_setjmp.h>

/* 1C6620 */ static void grAnime_801C6620(HSD_PObj* arg0, HSD_ShapeAnim* arg1);
/* 1C6710 */ static void grAnime_801C6710(HSD_TObj* tobj,
                                          HSD_TexAnim* texanim);
/* 1C67A8 */ static void grAnime_801C67A8(HSD_MObj*, HSD_MatAnim*);
/* 1C683C */ static void grAnime_801C683C(HSD_DObj* arg0, HSD_MatAnim* arg1,
                                          HSD_ShapeAnimDObj* arg2);
/* 1C68F4 */ static void grAnime_801C68F4(HSD_RObj* robj,
                                          HSD_RObjAnimJoint* robjanimjoint);
/* 1C6960 */ static void grAnime_801C6960(HSD_RObj* robj,
                                          HSD_RObjAnimJoint* arg1);
/* 1C69FC */ static HSD_AObj* grAnime_801C69FC(HSD_AObj* aobj);
/* 1C6A54 */ static void grAnime_801C6A54(HSD_JObj* jobj,
                                          HSD_AnimJoint* animjoint,
                                          HSD_MatAnimJoint* matanimjoint,
                                          HSD_ShapeAnimJoint* shapeanimjoint);
/* 1C6C0C */ void grAnime_801C6C0C(HSD_JObj* jobj, HSD_AnimJoint* animjoint,
                                   HSD_MatAnimJoint* matanimjoint,
                                   HSD_ShapeAnimJoint* shapeanimjoint);
/* 1C6EE4 */ static void fn_801C6EE4(HSD_AObj* aobj);
/* 1C6F2C */ static void fn_801C6F2C(HSD_AObj* aobj);
/* 1C6F50 */ static void grAnime_801C6F50(HSD_AObj* aobj, void* obj, u32 flags,
                                          void* func, u32 type, void* param);
/* 1C706C */ static void grAnime_801C706C(HSD_TObj* tobj, s32 flags,
                                          void* func, u32 type, void* param);
/* 1C70E0 */ static void grAnime_801C70E0(HSD_DObj* dobj, int flags,
                                          void* function, u32 arg3,
                                          void* arg4);
/* 1C7228 */ static void grAnime_801C7228(HSD_JObj* obj, int flags, void* func,
                                          u32 type, void* param, int arg5);
///* 1C7B24 */ static void grAnime_801C7B24(HSD_GObj* gobj, int arg1, u32 arg2,
///                                          f32 arg8);
/* 1C82E8 */ static void fn_801C82E8(int arg0, int* arg1);
/* 4D6958 */ static float grAnime_804D6958;
/* 4D695C */ static float grAnime_804D695C;

void grAnime_801C65B0(UnkArchiveStruct* arg0)
{
    if (arg0 == NULL) {
        return;
    }
    if ((uintptr_t) arg0->unk0 != -1U) {
        if (arg0->unk8 == 0) {
            lbArchive_80016EFC(arg0->unk0);
        } else if (arg0->unk8 == 1) {
            lbHeap_80015CA8(0, arg0->unk0);
        }
    }
    memzero(arg0, sizeof(*arg0));
}

void grAnime_801C6620(HSD_PObj* arg0, HSD_ShapeAnim* arg1)
{
    struct _unk_struct_pobj* unk;
    HSD_PObj* pobj;
    HSD_ShapeAnim* shape_anim;

    if (arg0 == NULL || arg1 == NULL) {
        return;
    }
    pobj = arg0;
    shape_anim = arg1;
    while (pobj != NULL) {
        if (pobj != NULL) {
            HSD_ASSERT(38, pobj_type(pobj) == POBJ_SHAPEANIM &&
                                pobj->u.shape_set);
            if (shape_anim != NULL) {
                unk = pobj->u.unk;
                if (shape_anim->aobjdesc != NULL) {
                    if (unk->aobj != NULL) {
                        HSD_AObjRemove(unk->aobj);
                    }
                    unk->aobj = HSD_AObjLoadDesc(shape_anim->aobjdesc);
                }
            }
        }
        pobj = pobj->next;
        shape_anim = shape_anim != NULL ? shape_anim->next : NULL;
    }
}

inline HSD_TexAnim* HSD_TexAnimFindById(HSD_TexAnim* cur, int id)
{
    while (cur != NULL) {
        if ((signed) cur->id == id) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void grAnime_801C6710(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    if (tobj == NULL) {
        return;
    }
    texanim = HSD_TexAnimFindById(texanim, tobj->id);
    if (texanim != NULL && texanim->aobjdesc != NULL) {
        if (tobj->aobj != NULL) {
            HSD_AObjRemove(tobj->aobj);
        }
        tobj->aobj = HSD_AObjLoadDesc(texanim->aobjdesc);
        tobj->imagetbl = texanim->imagetbl;
    }
}

inline void grAnime_801C6710_all(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    if (tobj != NULL) {
        while (tobj != NULL) {
            grAnime_801C6710(tobj, texanim);
            tobj = tobj->next;
        }
    }
}

void grAnime_801C67A8(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    if (mobj != NULL && matanim != NULL) {
        if (matanim->aobjdesc != NULL) {
            if (mobj->aobj != NULL) {
                HSD_AObjRemove(mobj->aobj);
            }
            mobj->aobj = HSD_AObjLoadDesc(matanim->aobjdesc);
        }
        grAnime_801C6710_all(mobj->tobj, matanim->texanim);
    }
}

static inline void grAnime_801C67A8_inner(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    grAnime_801C67A8(mobj, matanim);
}

static inline void grAnime_801C67A8_noinline(HSD_MObj* mobj,
                                             HSD_MatAnim* matanim)
{
    grAnime_801C67A8_inner(mobj, matanim);
}

void grAnime_801C683C(HSD_DObj* arg0, HSD_MatAnim* arg1,
                      HSD_ShapeAnimDObj* arg2)
{
    HSD_DObj* dobj;
    HSD_MatAnim* matanim;
    HSD_ShapeAnimDObj* sa_dobj;

    if (arg0 == NULL) {
        return;
    }
    dobj = arg0;
    matanim = arg1;
    sa_dobj = arg2;
    while (dobj != NULL) {
        if (dobj != NULL) {
            grAnime_801C6620(dobj->pobj,
                             sa_dobj != NULL ? sa_dobj->shapeanim : NULL);
            grAnime_801C67A8_noinline(dobj->mobj, matanim);
        }
        dobj = dobj->next;
        matanim = matanim != NULL ? matanim->next : NULL;
        sa_dobj = sa_dobj != NULL ? sa_dobj->next : NULL;
    }
}

static inline void grAnime_801C683C_inner(HSD_DObj* arg0, HSD_MatAnim* arg1,
                                          HSD_ShapeAnimDObj* arg2)
{
    grAnime_801C683C(arg0, arg1, arg2);
}

static inline void grAnime_801C683C_noinline(HSD_DObj* arg0, HSD_MatAnim* arg1,
                                             HSD_ShapeAnimDObj* arg2)
{
    grAnime_801C683C_inner(arg0, arg1, arg2);
}

void grAnime_801C68F4(HSD_RObj* robj, HSD_RObjAnimJoint* robjanimjoint)
{
    if (robj == NULL || robjanimjoint == NULL) {
        return;
    }
    if (robjanimjoint->aobjdesc != NULL) {
        if (robj->aobj != NULL) {
            HSD_AObjRemove(robj->aobj);
        }
        robj->aobj = HSD_AObjLoadDesc(robjanimjoint->aobjdesc);
    }
}

inline void grAnime_801C6960(HSD_RObj* robj, HSD_RObjAnimJoint* arg1)
{
    HSD_RObj* phi_r31;
    HSD_RObjAnimJoint* phi_r30;

    if (robj == NULL || arg1 == NULL) {
        return;
    }
    phi_r31 = robj;
    phi_r30 = arg1;
    while ((phi_r31 != NULL) && (phi_r30 != NULL)) {
        grAnime_801C68F4(phi_r31, phi_r30);
        phi_r31 = phi_r31->next;
        phi_r30 = phi_r30->next;
    }
}

static inline void grAnime_801C6960_inner(HSD_RObj* robj,
                                          HSD_RObjAnimJoint* arg1)
{
    grAnime_801C6960(robj, arg1);
}

static inline void grAnime_801C6960_noinline(HSD_RObj* robj,
                                             HSD_RObjAnimJoint* arg1)
{
    grAnime_801C6960_inner(robj, arg1);
}

HSD_AObj* grAnime_801C69FC(HSD_AObj* aobj)
{
    HSD_FObj** cur;

    if (aobj == NULL || aobj->fobj == NULL) {
        return aobj;
    }

    cur = &aobj->fobj;
    while ((*cur) != NULL) {
        if ((*cur)->obj_type == 0xC) {
            HSD_FObj* tmp = *cur;
            *cur = tmp->next;
            tmp->next = aobj->fobj;
            aobj->fobj = tmp;
            break;
        }
        cur = &(*cur)->next;
    }
    return aobj;
}

static inline HSD_AObj* grAnime_801C69FC_inner(HSD_AObj* aobj)
{
    return grAnime_801C69FC(aobj);
}

static inline HSD_AObj* grAnime_801C69FC_noinline(HSD_AObj* aobj)
{
    return grAnime_801C69FC_inner(aobj);
}

void grAnime_801C6A54(HSD_JObj* jobj, HSD_AnimJoint* animjoint,
                      HSD_MatAnimJoint* matanimjoint,
                      HSD_ShapeAnimJoint* shapeanimjoint)
{
    if (jobj == NULL) {
        return;
    }
    if (animjoint != NULL) {
        if (animjoint->aobjdesc != NULL) {
            if (jobj->aobj != NULL) {
                HSD_AObjRemove(jobj->aobj);
            }
            jobj->aobj = HSD_AObjLoadDesc(animjoint->aobjdesc);
            grAnime_801C69FC(jobj->aobj);
        }
        grAnime_801C6960(jobj->robj, animjoint->robj_anim);
    }
    if (union_type_dobj(jobj)) {
        grAnime_801C683C(
            jobj->u.dobj, matanimjoint != NULL ? matanimjoint->matanim : NULL,
            shapeanimjoint != NULL ? shapeanimjoint->shapeanimdobj : NULL);
    }
}

static inline void grAnime_801C6A54_inner(HSD_JObj* jobj,
                                          HSD_AnimJoint* animjoint,
                                          HSD_MatAnimJoint* matanimjoint,
                                          HSD_ShapeAnimJoint* shapeanimjoint)
{
    grAnime_801C6A54(jobj, animjoint, matanimjoint, shapeanimjoint);
}

static inline void grAnime_801C6A54_noinline(HSD_JObj* jobj,
                                             HSD_AnimJoint* animjoint,
                                             HSD_MatAnimJoint* matanimjoint,
                                             HSD_ShapeAnimJoint* shapeanimjoint)
{
    grAnime_801C6A54_inner(jobj, animjoint, matanimjoint, shapeanimjoint);
}

void grAnime_801C6C0C(HSD_JObj* jobj, HSD_AnimJoint* animjoint,
                      HSD_MatAnimJoint* matanimjoint,
                      HSD_ShapeAnimJoint* shapeanimjoint)
{
    HSD_JObj* jp;
    HSD_AnimJoint* aj;
    HSD_MatAnimJoint* mj;
    HSD_ShapeAnimJoint* sj;

    PAD_STACK(16);
    if (jobj != NULL) {
        grAnime_801C6A54(jobj, animjoint, matanimjoint, shapeanimjoint);
        if (!(jobj->flags & 0x1000)) {
            jp = jobj->child;
            aj = animjoint != NULL ? animjoint->child : NULL;
            mj = matanimjoint != NULL ? matanimjoint->child : NULL;
            sj = shapeanimjoint != NULL ? shapeanimjoint->child : NULL;
            while (jp != NULL) {
                grAnime_801C6C0C(jp, aj, mj, sj);
                jp = jp->next;
                aj = aj != NULL ? aj->next : NULL;
                mj = mj != NULL ? mj->next : NULL;
                sj = sj != NULL ? sj->next : NULL;
            }
        }
    }
}

static inline void grAnime_801C6C0C_inner(
    HSD_JObj* jobj, HSD_AnimJoint* animjoint,
    HSD_MatAnimJoint* matanimjoint, HSD_ShapeAnimJoint* shapeanimjoint)
{
    grAnime_801C6C0C(jobj, animjoint, matanimjoint, shapeanimjoint);
}

static inline void grAnime_801C6C0C_noinline(
    HSD_JObj* jobj, HSD_AnimJoint* animjoint,
    HSD_MatAnimJoint* matanimjoint, HSD_ShapeAnimJoint* shapeanimjoint)
{
    grAnime_801C6C0C_inner(jobj, animjoint, matanimjoint, shapeanimjoint);
}

void fn_801C6EE4(HSD_AObj* aobj)
{
    HSD_AObjSetFlags(aobj, AOBJ_LOOP);
    HSD_AObjSetRewindFrame(aobj, grAnime_804D6958);
    HSD_AObjSetEndFrame(aobj, grAnime_804D695C);
}

void fn_801C6F2C(HSD_AObj* aobj)
{
    HSD_AObjSetFlags(aobj, AOBJ_LOOP);
}

enum {
    ARG_TYPE_DOBJ = 3,
    ARG_TYPE_MOBJ = 8,
    ARG_TYPE_POBJ = 9,
    ARG_TYPE_TOBJ = 11,
};
enum {
    CALL_ON_DOBJ = 1 << (ARG_TYPE_DOBJ - 1),
    CALL_ON_MOBJ = 1 << (ARG_TYPE_MOBJ - 1),
    CALL_ON_POBJ = 1 << (ARG_TYPE_POBJ - 1),
    CALL_ON_TOBJ = 1 << (ARG_TYPE_TOBJ - 1),
};

typedef void (*Callback1)(HSD_AObj* aobj, HSD_TObj* obj, u32 flags,
                          float param);
typedef void (*Callback2)(HSD_AObj* aobj, int param);
typedef void (*Callback4)(HSD_AObj* aobj, HSD_TObj* obj, u32 flags, int param);
typedef void (*Callback3)(HSD_AObj* aobj, HSD_TObj* obj, int param);

void grAnime_801C6F50(HSD_AObj* aobj, void* obj, u32 flags, void* func,
                      u32 type, void* param)
{
    switch (type) {
    case 0:
        ((Event) func)();
        break;
    case 1:
        ((Callback1) func)(aobj, obj, flags, *(float*) param);
        break;
    case 2:
        ((Callback2) func)(aobj, *(int*) param);
        break;
    case 3:
        ((Callback2) func)(aobj, *(int*) param);
        break;
    case 4:
        ((Event) func)();
        break;
    case 8:
        ((Event) func)();
        break;
    case 5:
        ((Callback1) func)(aobj, obj, flags, *(float*) param);
        break;
    case 6:
        ((Callback3) func)(aobj, obj, *(int*) param);
        break;
    case 7:
        ((Callback3) func)(aobj, obj, *(int*) param);
        break;
    case 9:
        ((Callback1) func)(aobj, obj, flags, *(float*) param);
        break;
    case 10:
        ((Callback4) func)(aobj, obj, flags, *(int*) param);
        break;
    case 11:
        ((Callback4) func)(aobj, obj, flags, *(int*) param);
        break;
    }
}

void grAnime_801C706C(HSD_TObj* tobj, s32 flags, void* func, u32 type,
                      void* param)
{
    while (tobj != NULL) {
        if (flags & 0x400 && tobj->aobj != NULL) {
            grAnime_801C6F50(tobj->aobj, tobj, 0xBU, func, type, param);
        }
        tobj = tobj->next;
    }
}

static inline void grAnime_801C706C_inner(HSD_TObj* tobj, s32 flags, void* func,
                                          u32 type, void* param)
{
    grAnime_801C706C(tobj, flags, func, type, param);
}

static inline void grAnime_801C706C_noinline(HSD_TObj* tobj, s32 flags,
                                             void* func, u32 type, void* param)
{
    grAnime_801C706C_inner(tobj, flags, func, type, param);
}

void grAnime_801C70E0(HSD_DObj* dobj, int flags, void* function, u32 arg3,
                      void* arg4)
{
    HSD_MObj* mobj;
    HSD_PObj* pobj;

    while (dobj != NULL) {
        if (flags & CALL_ON_DOBJ && dobj->aobj != NULL) {
            grAnime_801C6F50(dobj->aobj, dobj, ARG_TYPE_DOBJ, function, arg3,
                             arg4);
        }
        if (dobj->mobj != NULL) {
            mobj = dobj->mobj;
            if (flags & CALL_ON_MOBJ && mobj->aobj != NULL) {
                HSD_MObj* mobj_tmp = dobj->mobj;
                grAnime_801C6F50(mobj_tmp->aobj, mobj_tmp, ARG_TYPE_MOBJ,
                                 function, arg3, arg4);
            }
            grAnime_801C706C(mobj->tobj, flags, function, arg3, arg4);
        }
        pobj = dobj->pobj;
        if (flags & CALL_ON_POBJ && pobj != NULL &&
            pobj_type(pobj) == POBJ_SHAPEANIM && pobj->u.unk != NULL &&
            pobj->u.unk->aobj != NULL)
        {
            grAnime_801C6F50(pobj->u.unk->aobj, pobj, ARG_TYPE_POBJ, function,
                             arg3, arg4);
        }
        dobj = dobj->next;
    }
}

/*
void grAnime_801C706C(HSD_TObj* tobj, int flags, void (*function)(), void*
arg3, void* arg4)
{
    while (tobj != NULL) {
        if (flags & CALL_ON_TOBJ && tobj->aobj != NULL) {
            grAnime_801C6F50(tobj->aobj, tobj, ARG_TYPE_TOBJ, function, arg3,
arg4);
        }
        tobj = tobj->next;
    }
}*/

inline bool grAnime_801C6F50_wrapped(HSD_JObj* obj, int flags, void* func,
                                     u32 type, void* param)
{
    HSD_ASSERT(0x33A, obj);
    if (flags & 0x20) {
        if (obj->aobj != NULL) {
            grAnime_801C6F50(obj->aobj, obj, 6, func, type, param);
        }
    }
    return ((obj->flags & 0x4020) ? false : true);
}

void grAnime_801C7228(HSD_JObj* obj, int flags, void* func, u32 type,
                      void* param, int arg5)
{
    HSD_MObj* temp_r20;
    HSD_PObj* temp_r4;
    int phi_r0;
    HSD_DObj* phi_r23;
    HSD_RObj* phi_r23_2;
    HSD_JObj* phi_r24;
    int phi_r0_2;
    HSD_RObj* phi_r22;
    HSD_JObj* phi_r20;

    if (grAnime_801C6F50_wrapped(obj, flags, func, type, param)) {
#if 0
        grAnime_801C70E0(obj->u.dobj, arg1, arg2, arg3, arg4);
#else
        phi_r23 = obj->u.dobj;
        while (phi_r23 != NULL) {
            if ((flags & 4) && phi_r23->aobj != NULL) {
                grAnime_801C6F50(phi_r23->aobj, phi_r23, 3, func, type, param);
            }
            temp_r20 = phi_r23->mobj;
            if (temp_r20 != NULL) {
                if ((flags & 0x80) && temp_r20->aobj != NULL) {
                    grAnime_801C6F50(temp_r20->aobj, temp_r20, 8, func, type,
                                     param);
                }
                grAnime_801C706C_noinline(temp_r20->tobj, flags, func, type,
                                          param);
            }
            temp_r4 = phi_r23->pobj;
            if (((int) (flags & 0x100) != 0) && (temp_r4 != NULL) &&
                ((temp_r4->flags & 0x3000) == 0x1000))
            {
                if (temp_r4->u.unk != NULL) {
                    if (temp_r4->u.unk->aobj != NULL) {
                        grAnime_801C6F50(temp_r4->u.unk->aobj, temp_r4, 9,
                                         func, type, param);
                    }
                }
            }
            phi_r23 = phi_r23->next;
        }
#endif
    }
    phi_r23_2 = obj->robj;
    while (phi_r23_2 != NULL) {
        if ((flags & 0x200) && phi_r23_2->aobj != NULL) {
            grAnime_801C6F50(phi_r23_2->aobj, phi_r23_2, 0xA, func, type,
                             param);
        }
        phi_r23_2 = phi_r23_2->next;
    }
    if (arg5 && !(obj->flags & 0x1000)) {
        phi_r24 = obj->child;
        while (phi_r24 != NULL) {
#if 0
            grAnime_801C7228(phi_r24, arg1, arg2, arg3, arg4, arg5);
#else

            if (grAnime_801C6F50_wrapped(phi_r24, flags, func, type, param)) {
                grAnime_801C70E0(phi_r24->u.dobj, flags, func, type, param);
            }
            phi_r22 = phi_r24->robj;
            while (phi_r22 != NULL) {
                if (flags & 0x200) {
                    if (phi_r22->aobj != NULL) {
                        grAnime_801C6F50(phi_r22->aobj, phi_r22, 0xA, func,
                                         type, param);
                    }
                }
                phi_r22 = phi_r22->next;
            }
            if (arg5 && !(phi_r24->flags & 0x1000)) {
                phi_r20 = phi_r24->child;
                while (phi_r20 != NULL) {
                    grAnime_801C7228(phi_r20, flags, func, type, param, arg5);
                    phi_r20 = phi_r20->next;
                }
            }
#endif
            phi_r24 = phi_r24->next;
        }
    }
}

void grAnime_801C752C(HSD_JObj* obj, s32 arg1, s32 flags, void* func,
                      u32 type, ...)
{
    HSD_JObj* obj_tmp;
    HSD_RObj* robj;
    int flags2;
    HSD_JObj* child;
    va_list ap;
    callbackArg arg;

    if (obj == NULL) {
        return;
    }
    va_start(ap, type);
    obj_tmp = obj;
    switch (type) {
    case AOBJ_ARG_A:
    case AOBJ_ARG_AO:
    case AOBJ_ARG_AOT:
        break;
    case AOBJ_ARG_AF:
    case AOBJ_ARG_AOF:
    case AOBJ_ARG_AOTF:
        arg.f = va_arg(ap, f64);
        break;
    case AOBJ_ARG_AV:
    case AOBJ_ARG_AOV:
    case AOBJ_ARG_AOTV:
        arg.v = va_arg(ap, void*);
        break;
    case AOBJ_ARG_AU:
    case AOBJ_ARG_AOU:
    case AOBJ_ARG_AOTU:
        arg.d = va_arg(ap, u32);
        break;
    default:
        HSD_ASSERTREPORT(0x36F, NULL, "not match arg_type\n");
        break;
    }
    if (grAnime_801C6F50_wrapped(obj_tmp, flags, func, type, &arg)) {
        grAnime_801C70E0(obj->u.dobj, flags, func, type, &arg);
    }
    flags2 = flags & 0x200;
    for (robj = obj->robj; robj != 0L; robj = robj->next) {
        if (flags2 && (robj->aobj != 0L)) {
            grAnime_801C6F50(robj->aobj, robj, 0xA, func, type, &arg);
        }
    }
    if (arg1 != 0 && !(obj->flags & 0x1000)) {
        for (child = obj->child; child != NULL; child = child->next) {
            grAnime_801C7228(child, flags, func, type, &arg, arg1);
        }
    }
    va_end(ap);
}

void grAnime_801C775C(HSD_GObj* gobj, int arg1, u32 arg2, f32 arg8, f32 arg9)
{
    u32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x220;
    }
    if (arg2 & 2) {
        var_r31 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r31 |= 0x100;
    }
    grAnime_804D6958 = arg8;
    grAnime_804D695C = arg9;
    grAnime_801C752C(jobj, 1, var_r31, fn_801C6EE4, 0);
}

void grAnime_801C77FC(HSD_GObj* gobj, int arg1, u32 arg2)
{
    s32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x220;
    }
    if (arg2 & 2) {
        var_r31 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r31 |= 0x100;
    }
    grAnime_801C752C(jobj, 1, var_r31, fn_801C6F2C, 0);
}

void grAnime_801C787C(HSD_GObj* gobj, int arg1, u32 arg2)
{
    s32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x220;
    }
    if (arg2 & 2) {
        var_r31 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r31 |= 0x100;
    }
    grAnime_801C752C(jobj, 0, var_r31, fn_801C6F2C, 0);
}

void grAnime_801C78FC(HSD_GObj* gobj, int arg1, u32 arg2)
{
    s32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x220;
    }
    if (arg2 & 2) {
        var_r31 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r31 |= 0x100;
    }
    grAnime_801C752C(jobj, 1, var_r31, HSD_AObjClearFlags, 3, AOBJ_LOOP);
}

void grAnime_801C7980(HSD_GObj* gobj, int arg1, u32 arg2)
{
    s32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x220;
    }
    if (arg2 & 2) {
        var_r31 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r31 |= 0x100;
    }
    grAnime_801C752C(jobj, 0, var_r31, HSD_AObjClearFlags, 3, AOBJ_LOOP);
}

void grAnime_801C7A04(HSD_GObj* gobj, int arg1, u32 arg2, f32 val)
{
    s32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x220;
    }
    if (arg2 & 2) {
        var_r31 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r31 |= 0x100;
    }
    grAnime_801C752C(jobj, 1, var_r31, HSD_AObjSetRate, 1, val);
}

void grAnime_801C7A94(HSD_GObj* gobj, int arg1, u32 arg2, f32 val)
{
    s32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x220;
    }
    if (arg2 & 2) {
        var_r31 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r31 |= 0x100;
    }
    grAnime_801C752C(jobj, 0, var_r31, HSD_AObjSetRate, 1, val);
}

void grAnime_801C7B24(HSD_GObj* gobj, int arg1, u32 arg2, f32 arg8)
{
    u32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x81;
    }
    if (arg2 & 2) {
        var_r31 |= 0x416;
    }
    if (arg2 & 4) {
        var_r31 |= 8;
    }
    HSD_JObjReqAnimAllByFlags(jobj, var_r31, arg8);
}

void grAnime_801C7BA0(HSD_GObj* gobj, int arg1, u32 arg2, f32 arg8)
{
    u32 var_r31 = 0;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return;
    }
    if (arg2 & 1) {
        var_r31 |= 0x81;
    }
    if (arg2 & 2) {
        var_r31 |= 0x416;
    }
    if (arg2 & 4) {
        var_r31 |= 8;
    }
    HSD_JObjReqAnimByFlags(jobj, var_r31, arg8);
}

void grAnime_801C7C1C(HSD_JObj* jobj, s32 map_id, s32 arg2, s32 arg3, s32 arg4,
                      int arg5, f32 farg0, f32 farg1)
{
    u32 var_r30 = 0;
    s32 var_r29 = 0;
    UnkArchiveStruct* archive;
    HSD_AnimJoint** ajp;
    HSD_MatAnimJoint** mjp;
    HSD_ShapeAnimJoint** sjp;
    HSD_AnimJoint* aj_t;
    HSD_MatAnimJoint* mj_t;
    HSD_ShapeAnimJoint* sj_t;
    HSD_AnimJoint* aj;
    HSD_MatAnimJoint* mj;
    HSD_ShapeAnimJoint* sj;
    HSD_JObj* child;
    HSD_AnimJoint* caj;
    HSD_MatAnimJoint* cmj;
    HSD_ShapeAnimJoint* csj;
    u8* eflags;
    s32 flag;

    if (jobj == NULL) {
        return;
    }
    archive = grDatFiles_801C6330(map_id);
    HSD_ASSERT(0x4DE, archive);
    if ((arg3 & 1) &&
        (ajp = archive->unk4->unk8[map_id].unk4, ajp != NULL) &&
        (aj_t = ajp[arg4], aj_t != NULL))
    {
        aj = &aj_t[arg2];
        var_r30 |= 0x81;
        var_r29 |= 0x220;
    } else {
        aj = NULL;
    }
    if ((arg3 & 2) &&
        (mjp = archive->unk4->unk8[map_id].unk8, mjp != NULL) &&
        (mj_t = mjp[arg4], mj_t != NULL))
    {
        mj = &mj_t[arg2];
        var_r30 |= 0x416;
        var_r29 |= 0x7484;
    } else {
        mj = NULL;
    }
    if ((arg3 & 4) &&
        (sjp = archive->unk4->unk8[map_id].unkC, sjp != NULL) &&
        (sj_t = sjp[arg4], sj_t != NULL))
    {
        sj = &sj_t[arg2];
        var_r30 |= 8;
        var_r29 |= 0x100;
    } else {
        sj = NULL;
    }
    if (arg5 != 0) {
        if (jobj != NULL) {
            grAnime_801C6A54_noinline(jobj, aj, mj, sj);
            if (!(jobj->flags & 0x1000)) {
                child = jobj->child;
                if (aj != NULL) {
                    if (aj != NULL) {
                        caj = aj->child;
                    } else {
                        caj = NULL;
                    }
                } else {
                    caj = NULL;
                }
                if (mj != NULL) {
                    if (mj != NULL) {
                        cmj = mj->child;
                    } else {
                        cmj = NULL;
                    }
                } else {
                    cmj = NULL;
                }
                if (sj != NULL) {
                    if (sj != NULL) {
                        csj = sj->child;
                    } else {
                        csj = NULL;
                    }
                } else {
                    csj = NULL;
                }
                while (child != NULL) {
                    grAnime_801C6C0C_noinline(child, caj, cmj, csj);
                    child = child->next;
                    if (caj != NULL) {
                        if (caj != NULL) {
                            caj = caj->next;
                        } else {
                            caj = NULL;
                        }
                    } else {
                        caj = NULL;
                    }
                    if (cmj != NULL) {
                        if (cmj != NULL) {
                            cmj = cmj->next;
                        } else {
                            cmj = NULL;
                        }
                    } else {
                        cmj = NULL;
                    }
                    if (csj != NULL) {
                        if (csj != NULL) {
                            csj = csj->next;
                        } else {
                            csj = NULL;
                        }
                    } else {
                        csj = NULL;
                    }
                }
            }
        }
        HSD_JObjReqAnimAllByFlags(jobj, var_r30, farg0);
    } else {
        if (jobj != NULL) {
            if (aj != NULL) {
                if (aj->aobjdesc != NULL) {
                    if (jobj->aobj != NULL) {
                        HSD_AObjRemove(jobj->aobj);
                    }
                    jobj->aobj = HSD_AObjLoadDesc(aj->aobjdesc);
                    grAnime_801C69FC_noinline(jobj->aobj);
                }
                grAnime_801C6960_noinline(jobj->robj, aj->robj_anim);
            }
            if ((jobj->flags & 0x4020) ? false : true) {
                HSD_ShapeAnimDObj* sdobj = sj != NULL ? sj->shapeanimdobj : NULL;
                HSD_MatAnim* manim = mj != NULL ? mj->matanim : NULL;
                grAnime_801C683C_noinline(jobj->u.dobj, manim, sdobj);
            }
        }
        HSD_JObjReqAnimByFlags(jobj, var_r30, farg0);
    }
    grAnime_801C752C(jobj, arg5, var_r29, HSD_AObjSetRate, 1, farg1);
    archive = grDatFiles_801C6330(map_id);
    HSD_ASSERT(0x148, archive);
    eflags = (u8*) archive->unk4->unk8[map_id].x28;
    if (eflags != NULL) {
        flag = eflags[arg4];
    } else {
        flag = 0;
    }
    if (flag != 0) {
        grAnime_801C752C(jobj, arg5, var_r29, HSD_AObjSetFlags, 3,
                         0x20000000);
    }
}

void grAnime_801C7FF8(Ground_GObj* gobj, int arg1, int arg2, int arg3,
                      float arg4, float arg5)
{
    Ground* gr = GET_GROUND(gobj);
    if (gr != NULL && arg3 >= 0) {
        HSD_JObj* temp_r3 = Ground_801C3FA4(gobj, arg1);
        if (temp_r3 != NULL) {
            HSD_JObj* jobj = grMaterial_801C8B28(temp_r3);
            grMaterial_801C8B68(jobj, 0);
            grAnime_801C7C1C(temp_r3, gr->map_id, arg1, arg2, arg3, 1, arg4,
                             arg5);
        }
    }
}

void grAnime_801C8098(Ground_GObj* gobj, int arg1, int arg2, int arg3,
                      float arg4, float arg5)
{
    Ground* gr = GET_GROUND(gobj);
    if (gr != NULL && arg3 >= 0) {
        HSD_JObj* temp_r3 = Ground_801C3FA4(gobj, arg1);
        if (temp_r3 != NULL) {
            HSD_JObj* jobj = grMaterial_801C8B28(temp_r3);
            grMaterial_801C8B68(jobj, 0);
            grAnime_801C7C1C(temp_r3, gr->map_id, arg1, arg2, arg3, 0, arg4,
                             arg5);
        }
    }
}

void grAnime_801C8138(HSD_GObj* gobj, enum_t arg1, bool arg2)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    UnkArchiveStruct* archive;
    HSD_Joint* joint;
    HSD_AnimJoint** ajp;
    HSD_MatAnimJoint** mjp;
    HSD_ShapeAnimJoint** sap;
    HSD_AnimJoint* aj;
    HSD_MatAnimJoint* ma;
    HSD_ShapeAnimJoint* sa;
    u8* flags;
    s32 flag;

    if (arg2 < 0) {
        return;
    }
    archive = grDatFiles_801C6330(arg1);
    HSD_ASSERT(0x556, archive);
    joint = archive->unk4->unk8[arg1].unk0;
    if (HSD_JObjGetChild(jobj) != NULL) {
        jobj = HSD_JObjGetChild(jobj);
    }
    if (joint != NULL) {
        lb_8000B804(jobj, joint);
    }
    grMaterial_801C8B68(jobj, 0);
    HSD_JObjRemoveAnimAll(jobj);
    sap = archive->unk4->unk8[arg1].unkC;
    ajp = archive->unk4->unk8[arg1].unk4;
    mjp = archive->unk4->unk8[arg1].unk8;
    if (sap != NULL) {
        sa = sap[arg2];
    } else {
        sa = NULL;
    }
    if (mjp != NULL) {
        ma = mjp[arg2];
    } else {
        ma = NULL;
    }
    if (ajp != NULL) {
        aj = ajp[arg2];
    } else {
        aj = NULL;
    }
    HSD_JObjAddAnimAll(jobj, aj, ma, sa);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    archive = grDatFiles_801C6330(arg1);
    HSD_ASSERT(0x148, archive);
    flags = (u8*) archive->unk4->unk8[arg1].x28;
    if (flags != NULL) {
        flag = flags[arg2];
    } else {
        flag = 0;
    }
    if ((s32) flag != 0) {
        grAnime_801C752C(jobj, 1, 0x77A4, HSD_AObjSetFlags, 3, 0x20000000);
    }
    HSD_JObjAnimAll(jobj);
}

extern __jmp_buf grAnime_8049EE40;

void fn_801C82E8(int arg0, int* arg1)
{
    *arg1 = arg0;
    longjmp(&grAnime_8049EE40, 1);
}

HSD_AObj* grAnime_801C8318(HSD_GObj* gobj, int arg1, u32 arg2)
{
    HSD_JObj* jobj;
    enum _HSD_TypeMask var_r30 = 0;
    HSD_AObj* sp14 = NULL;
    jobj = Ground_801C3FA4(gobj, arg1);
    if (jobj == NULL) {
        return 0;
    }
    if (arg2 & 1) {
        var_r30 |= 0x220;
    }
    if (arg2 & 2) {
        var_r30 |= 0x7484;
    }
    if (arg2 & 4) {
        var_r30 |= 0x100;
    }
    if (__setjmp(&grAnime_8049EE40) == 0) {
        HSD_ForeachAnim(jobj, JOBJ_TYPE, var_r30, fn_801C82E8, AOBJ_ARG_AV,
                        &sp14);
    }
    return sp14;
}

bool grAnime_801C83D0(HSD_GObj* gobj, bool arg1, enum_t arg2)
{
    HSD_AObj* aobj = grAnime_801C8318(gobj, arg1, arg2);
    PAD_STACK(8);
    if (HSD_AObjGetFlags(aobj) & 0x40000000) {
        return true;
    }
    return false;
}

bool grAnime_801C84A4(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    HSD_AObj* aobj = grAnime_801C8318(gobj, arg1, arg2);
    PAD_STACK(8);
    if (HSD_AObjGetFlags(aobj) & 0x04000000) {
        return true;
    }
    return false;
}

HSD_Joint* grAnime_801C8578(HSD_Joint* joint, s32* counter)
{
    if (*counter == 0) {
        return joint;
    }
    if (joint->child != NULL) {
        *counter -= 1;
        joint = grAnime_801C8578(joint->child, counter);
        if (*counter == 0) {
            return joint;
        }
    }
    if (joint->next != NULL) {
        *counter -= 1;
        joint = grAnime_801C8578(joint->next, counter);
        if (*counter == 0) {
            return joint;
        }
    }
    return joint;
}

static inline HSD_Joint* grAnime_801C8578_noinline(HSD_Joint* joint,
                                                   s32* counter)
{
    return grAnime_801C8578(joint, counter);
}

void grAnime_801C86D4(s32 arg0, HSD_GObj* arg1, s32 arg2)
{
    s32 sp2;
    s32 sp3;
    s32 sp;
    s32 sp4;
    HSD_Joint* joint;
    UnkArchiveStruct* archive;

    Ground_801C3FA4(arg1, arg2);
    archive = grDatFiles_801C6330(arg0);
    HSD_ASSERT(0x602, archive);
    {
        HSD_Joint* root = archive->unk4->unk8[arg0].unk0;
        sp = arg2;
        joint = grAnime_801C8578_noinline(root, &sp);
    }
    HSD_JObjResetRST(Ground_801C3FA4(arg1, arg2), joint);
}

void grAnime_801C8780(HSD_GObj* gobj, u32 arg1, u32 arg2, f32 arg3, f32 arg4)
{
    UnkArchiveStruct* archive;

    Ground_801C498C();
    archive = grDatFiles_801C6330(arg1);
    HSD_ASSERT(0x617, archive);
}
