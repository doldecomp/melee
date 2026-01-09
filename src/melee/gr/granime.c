#include "gr/granime.h"

#include <platform.h>

#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbheap.h"

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
/* 1C6C0C */ static void grAnime_801C6C0C(HSD_JObj* jobj,
                                          HSD_AnimJoint* animjoint,
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
/* 1C775C */ static void grAnime_801C775C(HSD_GObj* gobj, int arg1, u32 arg2,
                                          f32 arg8, f32 arg9);
/* 1C7B24 */ static void grAnime_801C7B24(HSD_GObj* gobj, int arg1, u32 arg2,
                                          f32 arg8);
/* 1C7BA0 */ static void grAnime_801C7BA0(HSD_GObj* gobj, int arg1, u32 arg2,
                                          f32 arg8);
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
#pragma push
#pragma dont_inline on
            grAnime_801C67A8(dobj->mobj, matanim);
        }
        dobj = dobj->next;
        matanim = matanim != NULL ? matanim->next : NULL;
        sa_dobj = sa_dobj != NULL ? sa_dobj->next : NULL;
    }
}
#pragma pop

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

void grAnime_801C6960(HSD_RObj* robj, HSD_RObjAnimJoint* arg1)
{
    HSD_RObj* phi_r31;
    HSD_RObjAnimJoint* phi_r30;

    if (robj == NULL || arg1 == NULL) {
        return;
    }
    phi_r31 = robj;
    phi_r30 = arg1;
    while ((phi_r31 != NULL) && (phi_r30 != NULL)) {
        if ((phi_r31 != NULL) && (phi_r30 != NULL) &&
            (phi_r30->aobjdesc != NULL))
        {
            if (phi_r31->aobj != NULL) {
                HSD_AObjRemove(phi_r31->aobj);
            }
            phi_r31->aobj = HSD_AObjLoadDesc(phi_r30->aobjdesc);
        }
        phi_r31 = phi_r31->next;
        phi_r30 = phi_r30->next;
    }
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

void grAnime_801C6C0C(HSD_JObj* jobj, HSD_AnimJoint* animjoint,
                      HSD_MatAnimJoint* matanimjoint,
                      HSD_ShapeAnimJoint* shapeanimjoint)
{
    if (jobj == NULL) {
        return;
    }
    grAnime_801C6A54(jobj, animjoint, matanimjoint, shapeanimjoint);
    if (jobj->flags & 0x1000) {
        return;
    }
    jobj = jobj->child;
    animjoint = animjoint != NULL ? animjoint->child : NULL;
    matanimjoint = matanimjoint != NULL ? matanimjoint->child : NULL;
    shapeanimjoint = shapeanimjoint != NULL ? shapeanimjoint->child : NULL;

    while (jobj != NULL) {
        grAnime_801C6C0C(jobj, animjoint, matanimjoint, shapeanimjoint);
        jobj = jobj->next;
        animjoint = animjoint != NULL ? animjoint->next : NULL;
        matanimjoint = matanimjoint != NULL ? matanimjoint->next : NULL;
        shapeanimjoint = shapeanimjoint != NULL ? shapeanimjoint->next : NULL;
    }
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

    if (obj == NULL) {
        __assert("granime.c", 0x33AU, "obj");
    }
    if (flags & 0x20) {
        if (obj->aobj != NULL) {
            grAnime_801C6F50(obj->aobj, obj, 6, func, type, param);
        }
    }
    phi_r0 = ((obj->flags & 0x4020) ? false : true);
    if (phi_r0 != 0) {
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
                grAnime_801C706C(temp_r20->tobj, flags, func, type, param);
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
            if (phi_r24 == NULL) {
                __assert("granime.c", 0x33AU, "obj");
            }
            if ((flags & 0x20) && (phi_r24->aobj != NULL)) {
                grAnime_801C6F50(phi_r24->aobj, phi_r24, 6, func, type, param);
            }
            phi_r0_2 = phi_r24->flags & 0x4020 ? false : true;
            if (phi_r0_2 != 0) {
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

/// #grAnime_801C752C

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

/// #grAnime_801C7C1C

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

/// #grAnime_801C8138

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

/// #grAnime_801C83D0

/// #grAnime_801C84A4

/// #grAnime_801C8578

/// #grAnime_801C86D4

/// #grAnime_801C8780
