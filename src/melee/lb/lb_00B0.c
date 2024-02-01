#include "lb/lb_00B0.h"

#include "sc/types.h" // IWYU pragma: keep

#include <placeholder.h>
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/types.h>
#include <baselib/aobj.h>
#include <baselib/dobj.h> // IWYU pragma: keep
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/pobj.h>
#include <baselib/robj.h>

static s32 lb_803B9FC0[] = { 14, 14, 14, 14, 2, 4, 6, 0 };
static s32 lb_803B9FE0[] = { 12, 13, 14, 15 };
static s32 lb_803B9FF0[] = { 7, 4, 5, 6 };
static s32 lb_803BA000[] = { 6, 6, 6, 6, 1, 2, 3, 0 };
static s32 lb_803BA020[] = { 28, 29, 30, 31 };
static s32 lb_803BA030[] = { 7, 4, 5, 6 };

bool lb_8000B074(HSD_JObj* jobj)
{
    HSD_AObj* aobj = jobj->aobj;

    if (aobj != NULL && !(aobj->flags & AOBJ_NO_ANIM)) {
        return true;
    }

    return false;
}

bool lb_8000B09C(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if (jobj->aobj != NULL && !(jobj->aobj->flags & AOBJ_NO_ANIM)) {
            return true;
        }
        if ((jobj->child == NULL && jobj->next == NULL) ||
            (jobj->flags & JOBJ_INSTANCE))
        {
            while (true) {
                if (jobj->parent == NULL) {
                    jobj = NULL;
                    break;
                }
                if (jobj->parent->next != NULL) {
                    jobj = jobj->parent->next;
                    break;
                }
                jobj = jobj->parent;
            }
        } else if (jobj->child != NULL) {
            jobj = jobj->child;
        } else {
            jobj = jobj->next;
        }
    }
    return false;
}

bool lb_8000B134(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if (jobj->aobj != NULL && (jobj->aobj->flags & AOBJ_REWINDED)) {
            return true;
        }
        if ((jobj->child == NULL && jobj->next == NULL) ||
            (jobj->flags & JOBJ_INSTANCE))
        {
            while (true) {
                if (jobj->parent == NULL) {
                    jobj = NULL;
                    break;
                }
                if (jobj->parent->next != NULL) {
                    jobj = jobj->parent->next;
                    break;
                }
                jobj = jobj->parent;
            }
        } else if (jobj->child != NULL) {
            jobj = jobj->child;
        } else {
            jobj = jobj->next;
        }
    }
    return false;
}

inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}

void lb_8000B1CC(HSD_JObj* arg0, Vec3* arg1, Vec3* arg2)
{
    Quaternion r;
    Vec3 s;

    if (arg0 == NULL) {
        *arg2 = *arg1;
        return;
    }
    if (jobj_parent(arg0) != NULL) {
        HSD_JObjSetupMatrix(arg0);
        if (arg1 == NULL || (!arg1->x && !arg1->y && !arg1->z)) {
            arg2->x = arg0->mtx[0][3];
            arg2->y = arg0->mtx[1][3];
            arg2->z = arg0->mtx[2][3];
        } else {
            PSMTXMUltiVec(arg0->mtx, arg1, arg2);
        }
        return;
    }
    if (arg1 == NULL || (!arg1->x && !arg1->y && !arg1->z)) {
        HSD_JObjGetTranslation(arg0, arg2);
        return;
    }
    HSD_JObjGetRotation(arg0, &r);
    HSD_JObjGetScale(arg0, &s);
    if (!r.x && !r.y && !r.z && s.x == 1 && s.y == 1 && s.z == 1) {
        HSD_JObjGetTranslation(arg0, arg2);
        arg2->x += arg1->x;
        arg2->y += arg1->y;
        arg2->z += arg1->z;
        return;
    }
    HSD_JObjSetupMatrix(arg0);
    PSMTXMUltiVec(arg0->mtx, arg1, arg2);
}

void lb_8000B4FC(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    HSD_JObjClearFlags(jobj, JOBJ_USE_QUATERNION);
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void lb_8000B5DC(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->translate = joint->position;
    HSD_JObjClearFlags(jobj, JOBJ_USE_QUATERNION);
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void lb_8000B6A4(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void lb_8000B760(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->translate = joint->position;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void lb_8000B804(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    HSD_JObjClearFlags(jobj, JOBJ_USE_QUATERNION);
    HSD_JObjSetFlags(jobj, JOBJ_MTX_DIRTY);

    lb_8000B804(jobj->next, joint->next);
    lb_8000B804(jobj->child, joint->child);
}

static void lb_8000B9D8(HSD_JObj* jobj, float** arg1, s32 arg2)
{
    float* tmp = *arg1;
    if (arg2 != 0) {
        HSD_AObjSetRate(jobj->aobj, *tmp);
    }
}

void lb_8000BA0C(HSD_JObj* jobj, float arg8)
{
    float* sp10 = &arg8;
    HSD_JObjWalkTree(jobj, lb_8000B9D8, &sp10);
}

void lbDObjSetRateAll(HSD_DObj* dobj, float val)
{
    if (dobj == NULL) {
        return;
    }
    if (dobj->pobj != NULL) {
        HSD_PObj* cur;
        for (cur = dobj->pobj; cur != NULL; cur = cur->next) {
            if (pobj_type(cur) == POBJ_SHAPEANIM &&
                cur->u.shape_set->aobj != NULL)
            {
                HSD_AObjSetRate(cur->u.shape_set->aobj, val);
            }
        }
    }
    if (dobj->mobj != NULL) {
        if (dobj->mobj->aobj != NULL) {
            HSD_AObjSetRate(dobj->mobj->aobj, val);
        }
        if (dobj->mobj->tobj != NULL) {
            HSD_TObj* cur;
            for (cur = dobj->mobj->tobj; cur != NULL; cur = cur->next) {
                if (cur->aobj != NULL) {
                    HSD_AObjSetRate(cur->aobj, val);
                }
            }
        }
    }
}

// (exact copy of above, but with HSD_AObjReqAnim)
void lbDObjReqAnimAll(HSD_DObj* dobj, float val)
{
    if (dobj == NULL) {
        return;
    }
    if (dobj->pobj != NULL) {
        HSD_PObj* cur;
        for (cur = dobj->pobj; cur != NULL; cur = cur->next) {
            if (pobj_type(cur) == POBJ_SHAPEANIM &&
                cur->u.shape_set->aobj != NULL)
            {
                HSD_AObjReqAnim(cur->u.shape_set->aobj, val);
            }
        }
    }
    if (dobj->mobj != NULL) {
        if (dobj->mobj->aobj != NULL) {
            HSD_AObjReqAnim(dobj->mobj->aobj, val);
        }
        if (dobj->mobj->tobj != NULL) {
            HSD_TObj* cur;
            for (cur = dobj->mobj->tobj; cur != NULL; cur = cur->next) {
                if (cur->aobj != NULL) {
                    HSD_AObjReqAnim(cur->aobj, val);
                }
            }
        }
    }
}

static HSD_JObj* lbFindJObjWithAObj(HSD_JObj* jobj)
{
    HSD_JObj* tmp;
    if (jobj == NULL) {
        return NULL;
    }
    if (jobj->aobj != NULL) {
        return jobj;
    }
    tmp = lbFindJObjWithAObj(jobj->child);
    if (tmp != NULL) {
        return tmp;
    }
    tmp = lbFindJObjWithAObj(jobj->next);
    if (tmp != NULL) {
        return tmp;
    }
    return NULL;
}

float lbGetJObjFramerate(HSD_JObj* jobj)
{
    jobj = lbFindJObjWithAObj(jobj);
    if (jobj != NULL) {
        return jobj->aobj->framerate;
    }
    return 0;
}

float lbGetJObjCurrFrame(HSD_JObj* jobj)
{
    jobj = lbFindJObjWithAObj(jobj);
    if (jobj != NULL) {
        return jobj->aobj->curr_frame;
    }
    return 0;
}

float lbGetJObjEndFrame(HSD_JObj* jobj)
{
    jobj = lbFindJObjWithAObj(jobj);
    if (jobj != NULL) {
        return jobj->aobj->end_frame;
    }
    return 0;
}

static HSD_AnimJoint* lb_8000BECC(HSD_AnimJoint* animjoint)
{
    HSD_AnimJoint* tmp;
    if (animjoint == NULL) {
        return NULL;
    }
    if (animjoint->aobjdesc != NULL) {
        return animjoint;
    }
    tmp = lb_8000BECC(animjoint->child);
    if (tmp != NULL) {
        return tmp;
    }
    tmp = lb_8000BECC(animjoint->next);
    if (tmp != NULL) {
        return tmp;
    }
    return NULL;
}

float lb_8000BFF0(HSD_AnimJoint* animjoint)
{
    animjoint = lb_8000BECC(animjoint);
    if (animjoint != NULL) {
        return animjoint->aobjdesc->end_frame;
    }
    return 0;
}

void lb_8000C07C(HSD_JObj* jobj, s32 i, HSD_AnimJoint** arg3,
                 HSD_MatAnimJoint** arg4, HSD_ShapeAnimJoint** arg5)
{
    HSD_AnimJoint* phi_r4;
    HSD_MatAnimJoint* phi_r5;
    HSD_ShapeAnimJoint* phi_r6;

    if (arg3 != NULL) {
        phi_r4 = arg3[i];
    } else {
        phi_r4 = NULL;
    }
    if (arg4 != NULL) {
        phi_r5 = arg4[i];
    } else {
        phi_r5 = NULL;
    }
    if (arg5 != NULL) {
        phi_r6 = arg5[i];
    } else {
        phi_r6 = NULL;
    }
    HSD_JObjAddAnimAll(jobj, phi_r4, phi_r5, phi_r6);
}

void lb_8000C0E8(HSD_JObj* jobj, s32 i, DynamicModelDesc* arg2)
{
    lb_8000C07C(jobj, i, arg2->anims, arg2->matanims, arg2->shapeanims);
}

void lb_8000C160(void* mem, int size)
{
    u8* bytes = mem;
    while (size--) {
        *bytes++ = 0;
    }
}

void lb_8000C1C0(HSD_JObj* jobj, HSD_JObj* constraint)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, 0x90000001);
    HSD_RObjSetConstraintObj(robj, constraint);
    HSD_JObjPrependRObj(jobj, robj);
}

void lb_8000C228(HSD_JObj* jobj, HSD_JObj* constraint)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, 0x90000002);
    HSD_RObjSetConstraintObj(robj, constraint);
    HSD_JObjPrependRObj(jobj, robj);
}

void lb_8000C290(HSD_JObj* jobj, HSD_JObj* constraint)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, 0x90000004);
    HSD_RObjSetConstraintObj(robj, constraint);
    HSD_JObjPrependRObj(jobj, robj);
}

void lb_8000C2F8(HSD_JObj* jobj, HSD_JObj* constraint)
{
    lb_8000C1C0(jobj, constraint);
    lb_8000C290(jobj, constraint);
}

inline HSD_RObj* robj_next(HSD_RObj* robj)
{
    if (robj != NULL) {
        return robj->next;
    }
    return NULL;
}

void lb_8000C390(HSD_JObj* jobj)
{
    HSD_RObj* next;
    HSD_RObj* cur = HSD_JObjGetRObj(jobj);

    while (true) {
        cur = HSD_RObjGetByType(cur, REFTYPE_JOBJ, 0);

        if (cur == NULL) {
            break;
        }

        next = robj_next(cur);
        HSD_JObjDeleteRObj(jobj, cur);
        HSD_RObjRemove(cur);
        cur = next;
    }
}

void lb_8000C420(HSD_JObj* jobj, u32 flags, float limit)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, flags | 0xA0000000);
    if (robj != NULL) {
        robj->u.limit = limit;
    }
    HSD_JObjPrependRObj(jobj, robj);
}

// https://decomp.me/scratch/atKIC
void lb_8000C490(HSD_JObj* arg0, HSD_JObj* arg1, HSD_JObj* arg2, float arg3,
                 float arg4)
{
    NOT_IMPLEMENTED;
}

void lb_8000C7BC(HSD_JObj* src, HSD_JObj* dst)
{
    dst->rotate = src->rotate;
    dst->scale = src->scale;
    dst->translate = src->translate;
    if (HSD_JObjGetFlags(src) & JOBJ_USE_QUATERNION) {
        HSD_JObjSetFlags(dst, JOBJ_USE_QUATERNION);
    } else {
        HSD_JObjClearFlags(dst, JOBJ_USE_QUATERNION);
    }
    HSD_JObjSetFlags(dst, JOBJ_MTX_DIRTY);
}

void lb_8000C868(HSD_Joint* arg0, HSD_JObj* arg1, HSD_JObj* arg2, float arg3,
                 float arg4)
{
    NOT_IMPLEMENTED;
}

static s32 lbGetFreeColorRegImpl(s32 i0, HSD_TevDesc* tevdesc, HSD_TExp* texp1,
                                 HSD_TExp* texp2)
{
    bool register_used[8];
    int i;

    for (i = 0; i < 8; i++) {
        register_used[i] = false;
    }
    while (texp1 != NULL) {
        if (texp1->cnst.reg < 8) {
            register_used[texp1->cnst.reg] = true;
        }
        texp1 = texp1->cnst.next;
    }
    while (tevdesc != NULL) {
        s32 idx = lb_803B9FF0[tevdesc->u.tevconf.clr_out_reg];
        register_used[idx] = true;
        tevdesc = tevdesc->next;
    }
    while (texp2 != NULL) {
        if (texp2->cnst.reg < 8) {
            register_used[texp2->cnst.reg] = true;
        }
        texp2 = texp2->cnst.next;
    }
    for (i = i0; i < 7; i++) {
        if (!register_used[i]) {
            return i;
        }
    }
    return -1;
}

s32 lbGetFreeColorRegister(s32 i0, HSD_MObj* mobj, HSD_TExp* texp)
{
    return lbGetFreeColorRegImpl(i0, &mobj->tevdesc->desc, mobj->texp, texp);
}

s32 lb_8000CC8C(s32 i)
{
    return lb_803B9FC0[i];
}

s32 lb_8000CCA4(s32 i)
{
    return lb_803B9FE0[i];
}

static s32 lbGetFreeAlphaRegImpl(s32 i0, HSD_TevDesc* cur, HSD_TExp* arg2,
                                 HSD_TExp* arg3)
{
    bool register_used[8];
    int i;

    for (i = 0; i < 8; i++) {
        register_used[i] = false;
    }
    while (cur != NULL) {
        s32 idx = lb_803BA030[cur->u.tevconf.alpha_out_reg];
        register_used[idx] = true;
        cur = cur->next;
    }
    for (i = i0; i < 7; i++) {
        if (!register_used[i]) {
            return i;
        }
    }
    return -1;
}

s32 lbGetFreeAlphaRegister(s32 i0, HSD_MObj* mobj, HSD_TExp* texp)
{
    return lbGetFreeAlphaRegImpl(i0, &mobj->tevdesc->desc, mobj->texp, texp);
}

s32 lb_8000CD90(s32 i)
{
    return lb_803BA000[i];
}

s32 lb_8000CDA8(s32 i)
{
    return lb_803BA020[i];
}

inline HSD_LObj* lobj_next(HSD_LObj* lobj)
{
    if (lobj == NULL) {
        return NULL;
    }
    return lobj->next;
}

HSD_LObj* lb_8000CDC0(HSD_LObj* cur)
{
    while (cur != NULL) {
        if (!(cur->flags & ((1 << 0) | (1 << 1))) &&
            !(HSD_LObjGetFlags(cur) & (1 << 5)))
        {
            return cur;
        }
        cur = lobj_next(cur);
    }
#ifdef BUGFIX
    return NULL;
#endif
}

void lb_8000CE30(HSD_DObj* dobj, HSD_DObj* next)
{
    if (dobj != NULL) {
        dobj->next = next;
    }
}

void lb_8000CE40(HSD_JObj* jobj, HSD_DObj* dobj)
{
    if (jobj != NULL) {
        jobj->u.dobj = dobj;
    }
}
