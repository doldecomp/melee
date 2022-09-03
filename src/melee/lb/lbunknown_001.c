#include <melee/lb/lbunknown_001.h>

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/robj.h>

static s32 lbl_803B9FC0[] = { 14, 14, 14, 14, 2, 4, 6, 0 };
static s32 lbl_803B9FE0[] = { 12, 13, 14, 15 };
static s32 lbl_803B9FF0[] = { 7, 4, 5, 6 };
static s32 lbl_803BA000[] = { 6, 6, 6, 6, 1, 2, 3, 0 };
static s32 lbl_803BA020[] = { 28, 29, 30, 31 };
static s32 lbl_803BA030[] = { 7, 4, 5, 6 };

BOOL func_8000B074(HSD_JObj* jobj)
{
    HSD_AObj* aobj = jobj->aobj;
    if (aobj != NULL && !(aobj->flags & AOBJ_NO_ANIM)) {
        return TRUE;
    }
    return FALSE;
}

BOOL func_8000B09C(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if (jobj->aobj != NULL && !(jobj->aobj->flags & AOBJ_NO_ANIM)) {
            return TRUE;
        }
        if (jobj->child == NULL && jobj->next == NULL || (jobj->flags & JOBJ_INSTANCE)) {
            while (TRUE) {
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
    return FALSE;
}

BOOL func_8000B134(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if (jobj->aobj != NULL && (jobj->aobj->flags & AOBJ_REWINDED)) {
            return TRUE;
        }
        if (jobj->child == NULL && jobj->next == NULL || (jobj->flags & JOBJ_INSTANCE)) {
            while (TRUE) {
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
    return FALSE;
}

inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}

void func_8000B1CC(HSD_JObj* arg0, Vec3* arg1, Vec3* arg2)
{
    Quaternion r;
    Vec3 s;

    if (arg0 == NULL) {
        *arg2 = *arg1;
        return;
    }
    if (jobj_parent(arg0) != NULL) {
        HSD_JObjSetupMatrix(arg0);
        if (arg1 == NULL || !arg1->x && !arg1->y && !arg1->z) {
            arg2->x = arg0->mtx[0][3];
            arg2->y = arg0->mtx[1][3];
            arg2->z = arg0->mtx[2][3];
        } else {
            PSMTXMUltiVec(arg0->mtx, arg1, arg2);
        }
        return;
    }
    if (arg1 == NULL || !arg1->x && !arg1->y && !arg1->z) {
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

void func_8000B4FC(HSD_JObj* jobj, HSD_Joint* joint)
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

void func_8000B5DC(HSD_JObj* jobj, HSD_Joint* joint)
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

void func_8000B6A4(HSD_JObj* jobj, HSD_Joint* joint)
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

void func_8000B760(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->translate = joint->position;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void func_8000B804(HSD_JObj* jobj, HSD_Joint* joint)
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

    func_8000B804(jobj->next, joint->next);
    func_8000B804(jobj->child, joint->child);
}

static void lbl_8000B9D8(HSD_JObj* jobj, f32** arg1, s32 arg2)
{
    f32* tmp = *arg1;
    if (arg2 != 0) {
        HSD_AObjSetRate(jobj->aobj, *tmp);
    }
}

void func_8000BA0C(HSD_JObj* jobj, f32 arg8)
{
    f32* sp10 = &arg8;
    HSD_JObjWalkTree(jobj, lbl_8000B9D8, &sp10);
}

// lbDObjSetRateAll
void func_8000BA44(HSD_DObj* dobj, f32 val)
{
    if (dobj == NULL) {
        return;
    }
    if (dobj->pobj != NULL) {
        HSD_PObj* cur;
        for (cur = dobj->pobj; cur != NULL; cur = cur->next) {
            if (pobj_type(cur) == POBJ_SHAPEANIM && cur->u.x14_unk->aobj != NULL) {
                HSD_AObjSetRate(cur->u.x14_unk->aobj, val);
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

// lbDObjReqAnimAll
// (exact copy of above, but with HSD_AObjReqAnim)
void func_8000BB24(HSD_DObj* dobj, f32 val)
{
    if (dobj == NULL) {
        return;
    }
    if (dobj->pobj != NULL) {
        HSD_PObj* cur;
        for (cur = dobj->pobj; cur != NULL; cur = cur->next) {
            if (pobj_type(cur) == POBJ_SHAPEANIM && cur->u.x14_unk->aobj != NULL) {
                HSD_AObjReqAnim(cur->u.x14_unk->aobj, val);
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

// lbGetJObjFramerate
f32 func_8000BD28(HSD_JObj* jobj)
{
    jobj = lbFindJObjWithAObj(jobj);
    if (jobj != NULL) {
        return jobj->aobj->framerate;
    }
    return 0;
}

// lbGetJObjCurrFrame
f32 func_8000BDB4(HSD_JObj* jobj)
{
    jobj = lbFindJObjWithAObj(jobj);
    if (jobj != NULL) {
        return jobj->aobj->curr_frame;
    }
    return 0;
}

// lbGetJObjEndFrame
f32 func_8000BE40(HSD_JObj* jobj)
{
    jobj = lbFindJObjWithAObj(jobj);
    if (jobj != NULL) {
        return jobj->aobj->end_frame;
    }
    return 0;
}

static HSD_AnimJoint* func_8000BECC(HSD_AnimJoint* animjoint)
{
    HSD_AnimJoint* tmp;
    if (animjoint == NULL) {
        return NULL;
    }
    if (animjoint->aobjdesc != NULL) {
        return animjoint;
    }
    tmp = func_8000BECC(animjoint->child);
    if (tmp != NULL) {
        return tmp;
    }
    tmp = func_8000BECC(animjoint->next);
    if (tmp != NULL) {
        return tmp;
    }
    return NULL;
}

f32 func_8000BFF0(HSD_AnimJoint* animjoint)
{
    animjoint = func_8000BECC(animjoint);
    if (animjoint != NULL) {
        return animjoint->aobjdesc->end_frame;
    }
    return 0;
}

void func_8000C07C(HSD_JObj* jobj, s32 i, HSD_AnimJoint** arg3,
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

typedef struct _UnkAnimContainer {
    u8 x0_pad[0x4];
    struct _HSD_AnimJoint** x4_anims;
    struct _HSD_MatAnimJoint** x8_matanims;
    struct _HSD_ShapeAnimJoint** xC_shapeanims;
} UnkAnimContainer;

void func_8000C0E8(HSD_JObj* jobj, s32 i, struct _UnkAnimContainer* arg2)
{
    func_8000C07C(jobj, i, arg2->x4_anims, arg2->x8_matanims, arg2->xC_shapeanims);
}

void func_8000C160(void* mem, int size)
{
    u8* bytes = mem;
    while (size--) {
       *bytes++ = 0;
    }
}

void func_8000C1C0(HSD_JObj* jobj, HSD_JObj* constraint)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, 0x90000001);
    HSD_RObjSetConstraintObj(robj, constraint);
    HSD_JObjPrependRObj(jobj, robj);
}

void func_8000C228(HSD_JObj* jobj, HSD_JObj* constraint)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, 0x90000002);
    HSD_RObjSetConstraintObj(robj, constraint);
    HSD_JObjPrependRObj(jobj, robj);
}

void func_8000C290(HSD_JObj* jobj, HSD_JObj* constraint)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, 0x90000004);
    HSD_RObjSetConstraintObj(robj, constraint);
    HSD_JObjPrependRObj(jobj, robj);
}

void func_8000C2F8(HSD_JObj* jobj, HSD_JObj* constraint)
{
    func_8000C1C0(jobj, constraint);
    func_8000C290(jobj, constraint);
}

inline HSD_RObj* robj_next(HSD_RObj* robj)
{
    if (robj != NULL) {
        return robj->next;
    }
    return NULL;
}

void func_8000C390(HSD_JObj* jobj)
{
    HSD_RObj* next;
    HSD_RObj* cur = HSD_JObjGetRObj(jobj);
    while (1) {
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

void func_8000C420(HSD_JObj* jobj, u32 flags, f32 limit)
{
    HSD_RObj* robj = HSD_RObjAlloc();
    HSD_RObjSetFlags(robj, flags | 0xA0000000);
    if (robj != NULL) {
        robj->u.limit = limit;
    }
    HSD_JObjPrependRObj(jobj, robj);
}

// https://decomp.me/scratch/atKIC
asm void func_8000C490(HSD_JObj*, HSD_JObj*, HSD_JObj*, f32, f32)
{
    nofralloc
/* 8000C490 00009070  7C 08 02 A6 */	mflr r0
/* 8000C494 00009074  90 01 00 04 */	stw r0, 4(r1)
/* 8000C498 00009078  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 8000C49C 0000907C  DB E1 00 88 */	stfd f31, 0x88(r1)
/* 8000C4A0 00009080  FF E0 10 90 */	fmr f31, f2
/* 8000C4A4 00009084  BF 61 00 74 */	stmw r27, 0x74(r1)
/* 8000C4A8 00009088  7C 7B 1B 78 */	mr r27, r3
/* 8000C4AC 0000908C  7C 9C 23 78 */	mr r28, r4
/* 8000C4B0 00009090  7C BD 2B 78 */	mr r29, r5
/* 8000C4B4 00009094  C0 04 00 38 */	lfs f0, 0x38(r4)
/* 8000C4B8 00009098  C0 43 00 38 */	lfs f2, 0x38(r3)
/* 8000C4BC 0000909C  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C4C0 000090A0  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C4C4 000090A4  D0 05 00 38 */	stfs f0, 0x38(r5)
/* 8000C4C8 000090A8  C0 04 00 3C */	lfs f0, 0x3c(r4)
/* 8000C4CC 000090AC  C0 5B 00 3C */	lfs f2, 0x3c(r27)
/* 8000C4D0 000090B0  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C4D4 000090B4  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C4D8 000090B8  D0 05 00 3C */	stfs f0, 0x3c(r5)
/* 8000C4DC 000090BC  C0 04 00 40 */	lfs f0, 0x40(r4)
/* 8000C4E0 000090C0  C0 5B 00 40 */	lfs f2, 0x40(r27)
/* 8000C4E4 000090C4  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C4E8 000090C8  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C4EC 000090CC  D0 05 00 40 */	stfs f0, 0x40(r5)
/* 8000C4F0 000090D0  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 8000C4F4 000090D4  C0 5B 00 2C */	lfs f2, 0x2c(r27)
/* 8000C4F8 000090D8  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C4FC 000090DC  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C500 000090E0  D0 05 00 2C */	stfs f0, 0x2c(r5)
/* 8000C504 000090E4  C0 04 00 30 */	lfs f0, 0x30(r4)
/* 8000C508 000090E8  C0 5B 00 30 */	lfs f2, 0x30(r27)
/* 8000C50C 000090EC  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C510 000090F0  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C514 000090F4  D0 05 00 30 */	stfs f0, 0x30(r5)
/* 8000C518 000090F8  C0 04 00 34 */	lfs f0, 0x34(r4)
/* 8000C51C 000090FC  C0 5B 00 34 */	lfs f2, 0x34(r27)
/* 8000C520 00009100  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C524 00009104  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C528 00009108  D0 05 00 34 */	stfs f0, 0x34(r5)
/* 8000C52C 0000910C  48 36 57 BD */	bl HSD_JObjGetFlags
/* 8000C530 00009110  54 7F 03 9C */	rlwinm r31, r3, 0, 0xe, 0xe
/* 8000C534 00009114  38 7C 00 00 */	addi r3, r28, 0
/* 8000C538 00009118  48 36 57 B1 */	bl HSD_JObjGetFlags
/* 8000C53C 0000911C  2C 1F 00 00 */	cmpwi r31, 0
/* 8000C540 00009120  54 7E 03 9C */	rlwinm r30, r3, 0, 0xe, 0xe
/* 8000C544 00009124  40 82 00 E8 */	bne lbl_8000C62C
/* 8000C548 00009128  2C 1E 00 00 */	cmpwi r30, 0
/* 8000C54C 0000912C  40 82 00 E0 */	bne lbl_8000C62C
/* 8000C550 00009130  C0 5B 00 1C */	lfs f2, 0x1c(r27)
/* 8000C554 00009134  C0 3C 00 1C */	lfs f1, 0x1c(r28)
/* 8000C558 00009138  C0 02 80 78 */	lfs f0, 0.0f
/* 8000C55C 0000913C  EC A2 08 28 */	fsubs f5, f2, f1
/* 8000C560 00009140  C0 9B 00 20 */	lfs f4, 0x20(r27)
/* 8000C564 00009144  C0 7C 00 20 */	lfs f3, 0x20(r28)
/* 8000C568 00009148  C0 5B 00 24 */	lfs f2, 0x24(r27)
/* 8000C56C 0000914C  C0 3C 00 24 */	lfs f1, 0x24(r28)
/* 8000C570 00009150  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 8000C574 00009154  FC 00 28 90 */	fmr f0, f5
/* 8000C578 00009158  EC 64 18 28 */	fsubs f3, f4, f3
/* 8000C57C 0000915C  EC 42 08 28 */	fsubs f2, f2, f1
/* 8000C580 00009160  40 80 00 0C */	bge lbl_8000C58C
/* 8000C584 00009164  FC 20 00 50 */	fneg f1, f0
/* 8000C588 00009168  48 00 00 08 */	b lbl_8000C590
lbl_8000C58C:
/* 8000C58C 0000916C  FC 20 00 90 */	fmr f1, f0
lbl_8000C590:
/* 8000C590 00009170  C0 02 80 80 */	lfs f0, 0.0001f
/* 8000C594 00009174  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000C598 00009178  4C 40 13 82 */	cror 2, 0, 2
/* 8000C59C 0000917C  40 82 00 90 */	bne lbl_8000C62C
/* 8000C5A0 00009180  C0 02 80 78 */	lfs f0, 0.0f
/* 8000C5A4 00009184  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8000C5A8 00009188  40 80 00 0C */	bge lbl_8000C5B4
/* 8000C5AC 0000918C  FC 20 18 50 */	fneg f1, f3
/* 8000C5B0 00009190  48 00 00 08 */	b lbl_8000C5B8
lbl_8000C5B4:
/* 8000C5B4 00009194  FC 20 18 90 */	fmr f1, f3
lbl_8000C5B8:
/* 8000C5B8 00009198  C0 02 80 80 */	lfs f0, 0.0001f
/* 8000C5BC 0000919C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000C5C0 000091A0  4C 40 13 82 */	cror 2, 0, 2
/* 8000C5C4 000091A4  40 82 00 68 */	bne lbl_8000C62C
/* 8000C5C8 000091A8  C0 02 80 78 */	lfs f0, 0.0f
/* 8000C5CC 000091AC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000C5D0 000091B0  40 80 00 0C */	bge lbl_8000C5DC
/* 8000C5D4 000091B4  FC 20 10 50 */	fneg f1, f2
/* 8000C5D8 000091B8  48 00 00 08 */	b lbl_8000C5E0
lbl_8000C5DC:
/* 8000C5DC 000091BC  FC 20 10 90 */	fmr f1, f2
lbl_8000C5E0:
/* 8000C5E0 000091C0  C0 02 80 80 */	lfs f0, 0.0001f
/* 8000C5E4 000091C4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000C5E8 000091C8  4C 40 13 82 */	cror 2, 0, 2
/* 8000C5EC 000091CC  40 82 00 40 */	bne lbl_8000C62C
/* 8000C5F0 000091D0  80 BB 00 1C */	lwz r5, 0x1c(r27)
/* 8000C5F4 000091D4  7F A3 EB 78 */	mr r3, r29
/* 8000C5F8 000091D8  80 1B 00 20 */	lwz r0, 0x20(r27)
/* 8000C5FC 000091DC  3C 80 00 02 */	lis r4, 2
/* 8000C600 000091E0  90 BD 00 1C */	stw r5, 0x1c(r29)
/* 8000C604 000091E4  90 1D 00 20 */	stw r0, 0x20(r29)
/* 8000C608 000091E8  80 BB 00 24 */	lwz r5, 0x24(r27)
/* 8000C60C 000091EC  80 1B 00 28 */	lwz r0, 0x28(r27)
/* 8000C610 000091F0  90 BD 00 24 */	stw r5, 0x24(r29)
/* 8000C614 000091F4  90 1D 00 28 */	stw r0, 0x28(r29)
/* 8000C618 000091F8  48 36 58 E9 */	bl HSD_JObjClearFlags
/* 8000C61C 000091FC  38 7D 00 00 */	addi r3, r29, 0
/* 8000C620 00009200  38 80 00 40 */	li r4, 0x40
/* 8000C624 00009204  48 36 56 DD */	bl HSD_JObjSetFlags
/* 8000C628 00009208  48 00 01 7C */	b lbl_8000C7A4
lbl_8000C62C:
/* 8000C62C 0000920C  2C 1F 00 00 */	cmpwi r31, 0
/* 8000C630 00009210  41 82 00 28 */	beq lbl_8000C658
/* 8000C634 00009214  80 7B 00 1C */	lwz r3, 0x1c(r27)
/* 8000C638 00009218  80 1B 00 20 */	lwz r0, 0x20(r27)
/* 8000C63C 0000921C  90 61 00 44 */	stw r3, 0x44(r1)
/* 8000C640 00009220  90 01 00 48 */	stw r0, 0x48(r1)
/* 8000C644 00009224  80 7B 00 24 */	lwz r3, 0x24(r27)
/* 8000C648 00009228  80 1B 00 28 */	lwz r0, 0x28(r27)
/* 8000C64C 0000922C  90 61 00 4C */	stw r3, 0x4c(r1)
/* 8000C650 00009230  90 01 00 50 */	stw r0, 0x50(r1)
/* 8000C654 00009234  48 00 00 28 */	b lbl_8000C67C
lbl_8000C658:
/* 8000C658 00009238  C0 1B 00 1C */	lfs f0, 0x1c(r27)
/* 8000C65C 0000923C  38 61 00 60 */	addi r3, r1, 0x60
/* 8000C660 00009240  38 81 00 44 */	addi r4, r1, 0x44
/* 8000C664 00009244  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 8000C668 00009248  C0 1B 00 20 */	lfs f0, 0x20(r27)
/* 8000C66C 0000924C  D0 01 00 64 */	stfs f0, 0x64(r1)
/* 8000C670 00009250  C0 1B 00 24 */	lfs f0, 0x24(r27)
/* 8000C674 00009254  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 8000C678 00009258  48 37 27 95 */	bl func_8037EE0C
lbl_8000C67C:
/* 8000C67C 0000925C  2C 1E 00 00 */	cmpwi r30, 0
/* 8000C680 00009260  41 82 00 28 */	beq lbl_8000C6A8
/* 8000C684 00009264  80 7C 00 1C */	lwz r3, 0x1c(r28)
/* 8000C688 00009268  80 1C 00 20 */	lwz r0, 0x20(r28)
/* 8000C68C 0000926C  90 61 00 34 */	stw r3, 0x34(r1)
/* 8000C690 00009270  90 01 00 38 */	stw r0, 0x38(r1)
/* 8000C694 00009274  80 7C 00 24 */	lwz r3, 0x24(r28)
/* 8000C698 00009278  80 1C 00 28 */	lwz r0, 0x28(r28)
/* 8000C69C 0000927C  90 61 00 3C */	stw r3, 0x3c(r1)
/* 8000C6A0 00009280  90 01 00 40 */	stw r0, 0x40(r1)
/* 8000C6A4 00009284  48 00 00 28 */	b lbl_8000C6CC
lbl_8000C6A8:
/* 8000C6A8 00009288  C0 1C 00 1C */	lfs f0, 0x1c(r28)
/* 8000C6AC 0000928C  38 61 00 54 */	addi r3, r1, 0x54
/* 8000C6B0 00009290  38 81 00 34 */	addi r4, r1, 0x34
/* 8000C6B4 00009294  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 8000C6B8 00009298  C0 1C 00 20 */	lfs f0, 0x20(r28)
/* 8000C6BC 0000929C  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 8000C6C0 000092A0  C0 1C 00 24 */	lfs f0, 0x24(r28)
/* 8000C6C4 000092A4  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 8000C6C8 000092A8  48 37 27 45 */	bl func_8037EE0C
lbl_8000C6CC:
/* 8000C6CC 000092AC  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 8000C6D0 000092B0  C0 21 00 48 */	lfs f1, 0x48(r1)
/* 8000C6D4 000092B4  C0 E1 00 34 */	lfs f7, 0x34(r1)
/* 8000C6D8 000092B8  EC 41 00 28 */	fsubs f2, f1, f0
/* 8000C6DC 000092BC  C0 61 00 44 */	lfs f3, 0x44(r1)
/* 8000C6E0 000092C0  EC 01 00 2A */	fadds f0, f1, f0
/* 8000C6E4 000092C4  C0 A1 00 3C */	lfs f5, 0x3c(r1)
/* 8000C6E8 000092C8  EC 23 38 2A */	fadds f1, f3, f7
/* 8000C6EC 000092CC  EC 83 38 28 */	fsubs f4, f3, f7
/* 8000C6F0 000092D0  C0 C1 00 4C */	lfs f6, 0x4c(r1)
/* 8000C6F4 000092D4  C0 61 00 40 */	lfs f3, 0x40(r1)
/* 8000C6F8 000092D8  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8000C6FC 000092DC  C1 21 00 50 */	lfs f9, 0x50(r1)
/* 8000C700 000092E0  ED 06 28 28 */	fsubs f8, f6, f5
/* 8000C704 000092E4  EC A6 28 2A */	fadds f5, f6, f5
/* 8000C708 000092E8  ED 49 18 28 */	fsubs f10, f9, f3
/* 8000C70C 000092EC  EC C9 18 2A */	fadds f6, f9, f3
/* 8000C710 000092F0  EC 64 01 32 */	fmuls f3, f4, f4
/* 8000C714 000092F4  EC 21 00 72 */	fmuls f1, f1, f1
/* 8000C718 000092F8  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000C71C 000092FC  EC 63 10 2A */	fadds f3, f3, f2
/* 8000C720 00009300  EC 88 02 32 */	fmuls f4, f8, f8
/* 8000C724 00009304  EC 45 01 72 */	fmuls f2, f5, f5
/* 8000C728 00009308  EC 01 00 2A */	fadds f0, f1, f0
/* 8000C72C 0000930C  EC AA 02 B2 */	fmuls f5, f10, f10
/* 8000C730 00009310  EC 64 18 2A */	fadds f3, f4, f3
/* 8000C734 00009314  EC 02 00 2A */	fadds f0, f2, f0
/* 8000C738 00009318  EC 26 01 B2 */	fmuls f1, f6, f6
/* 8000C73C 0000931C  EC 45 18 2A */	fadds f2, f5, f3
/* 8000C740 00009320  EC 01 00 2A */	fadds f0, f1, f0
/* 8000C744 00009324  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000C748 00009328  40 81 00 30 */	ble lbl_8000C778
/* 8000C74C 0000932C  FC 00 38 50 */	fneg f0, f7
/* 8000C750 00009330  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 8000C754 00009334  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 8000C758 00009338  FC 00 00 50 */	fneg f0, f0
/* 8000C75C 0000933C  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8000C760 00009340  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 8000C764 00009344  FC 00 00 50 */	fneg f0, f0
/* 8000C768 00009348  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 8000C76C 0000934C  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 8000C770 00009350  FC 00 00 50 */	fneg f0, f0
/* 8000C774 00009354  D0 01 00 40 */	stfs f0, 0x40(r1)
lbl_8000C778:
/* 8000C778 00009358  FC 20 F8 90 */	fmr f1, f31
/* 8000C77C 0000935C  38 61 00 44 */	addi r3, r1, 0x44
/* 8000C780 00009360  38 81 00 34 */	addi r4, r1, 0x34
/* 8000C784 00009364  38 BD 00 1C */	addi r5, r29, 0x1c
/* 8000C788 00009368  48 37 27 A1 */	bl func_8037EF28
/* 8000C78C 0000936C  38 7D 00 00 */	addi r3, r29, 0
/* 8000C790 00009370  3C 80 00 02 */	lis r4, 2
/* 8000C794 00009374  48 36 55 6D */	bl HSD_JObjSetFlags
/* 8000C798 00009378  38 7D 00 00 */	addi r3, r29, 0
/* 8000C79C 0000937C  38 80 00 40 */	li r4, 0x40
/* 8000C7A0 00009380  48 36 55 61 */	bl HSD_JObjSetFlags
lbl_8000C7A4:
/* 8000C7A4 00009384  BB 61 00 74 */	lmw r27, 0x74(r1)
/* 8000C7A8 00009388  80 01 00 94 */	lwz r0, 0x94(r1)
/* 8000C7AC 0000938C  CB E1 00 88 */	lfd f31, 0x88(r1)
/* 8000C7B0 00009390  38 21 00 90 */	addi r1, r1, 0x90
/* 8000C7B4 00009394  7C 08 03 A6 */	mtlr r0
/* 8000C7B8 00009398  4E 80 00 20 */	blr 
}
#pragma peephole on

void func_8000C7BC(HSD_JObj* src, HSD_JObj* dst)
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

// https://decomp.me/scratch/63ON3
asm void func_8000C868(HSD_Joint*, HSD_JObj*, HSD_JObj*, f32, f32)
{
    nofralloc
/* 8000C868 00009448  7C 08 02 A6 */	mflr r0
/* 8000C86C 0000944C  90 01 00 04 */	stw r0, 4(r1)
/* 8000C870 00009450  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 8000C874 00009454  DB E1 00 E0 */	stfd f31, 0xe0(r1)
/* 8000C878 00009458  FF E0 10 90 */	fmr f31, f2
/* 8000C87C 0000945C  93 E1 00 DC */	stw r31, 0xdc(r1)
/* 8000C880 00009460  93 C1 00 D8 */	stw r30, 0xd8(r1)
/* 8000C884 00009464  7C BE 2B 78 */	mr r30, r5
/* 8000C888 00009468  93 A1 00 D4 */	stw r29, 0xd4(r1)
/* 8000C88C 0000946C  7C 9D 23 78 */	mr r29, r4
/* 8000C890 00009470  93 81 00 D0 */	stw r28, 0xd0(r1)
/* 8000C894 00009474  7C 7C 1B 78 */	mr r28, r3
/* 8000C898 00009478  C0 04 00 38 */	lfs f0, 0x38(r4)
/* 8000C89C 0000947C  C0 43 00 2C */	lfs f2, 0x2c(r3)
/* 8000C8A0 00009480  7F A3 EB 78 */	mr r3, r29
/* 8000C8A4 00009484  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C8A8 00009488  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C8AC 0000948C  D0 05 00 38 */	stfs f0, 0x38(r5)
/* 8000C8B0 00009490  C0 04 00 3C */	lfs f0, 0x3c(r4)
/* 8000C8B4 00009494  C0 5C 00 30 */	lfs f2, 0x30(r28)
/* 8000C8B8 00009498  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C8BC 0000949C  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C8C0 000094A0  D0 05 00 3C */	stfs f0, 0x3c(r5)
/* 8000C8C4 000094A4  C0 04 00 40 */	lfs f0, 0x40(r4)
/* 8000C8C8 000094A8  C0 5C 00 34 */	lfs f2, 0x34(r28)
/* 8000C8CC 000094AC  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C8D0 000094B0  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C8D4 000094B4  D0 05 00 40 */	stfs f0, 0x40(r5)
/* 8000C8D8 000094B8  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 8000C8DC 000094BC  C0 5C 00 20 */	lfs f2, 0x20(r28)
/* 8000C8E0 000094C0  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C8E4 000094C4  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C8E8 000094C8  D0 05 00 2C */	stfs f0, 0x2c(r5)
/* 8000C8EC 000094CC  C0 04 00 30 */	lfs f0, 0x30(r4)
/* 8000C8F0 000094D0  C0 5C 00 24 */	lfs f2, 0x24(r28)
/* 8000C8F4 000094D4  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C8F8 000094D8  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C8FC 000094DC  D0 05 00 30 */	stfs f0, 0x30(r5)
/* 8000C900 000094E0  C0 04 00 34 */	lfs f0, 0x34(r4)
/* 8000C904 000094E4  C0 5C 00 28 */	lfs f2, 0x28(r28)
/* 8000C908 000094E8  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8000C90C 000094EC  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8000C910 000094F0  D0 05 00 34 */	stfs f0, 0x34(r5)
/* 8000C914 000094F4  48 36 53 D5 */	bl HSD_JObjGetFlags
/* 8000C918 000094F8  54 7F 03 9D */	rlwinm. r31, r3, 0, 0xe, 0xe
/* 8000C91C 000094FC  40 82 00 D4 */	bne lbl_8000C9F0
/* 8000C920 00009500  C0 DC 00 14 */	lfs f6, 0x14(r28)
/* 8000C924 00009504  C0 3D 00 1C */	lfs f1, 0x1c(r29)
/* 8000C928 00009508  C0 02 80 78 */	lfs f0, 0.0f
/* 8000C92C 0000950C  EC A6 08 28 */	fsubs f5, f6, f1
/* 8000C930 00009510  C0 9C 00 18 */	lfs f4, 0x18(r28)
/* 8000C934 00009514  C0 7D 00 20 */	lfs f3, 0x20(r29)
/* 8000C938 00009518  C0 5C 00 1C */	lfs f2, 0x1c(r28)
/* 8000C93C 0000951C  C0 3D 00 24 */	lfs f1, 0x24(r29)
/* 8000C940 00009520  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 8000C944 00009524  FC 00 28 90 */	fmr f0, f5
/* 8000C948 00009528  EC 64 18 28 */	fsubs f3, f4, f3
/* 8000C94C 0000952C  EC 42 08 28 */	fsubs f2, f2, f1
/* 8000C950 00009530  40 80 00 0C */	bge lbl_8000C95C
/* 8000C954 00009534  FC 20 00 50 */	fneg f1, f0
/* 8000C958 00009538  48 00 00 08 */	b lbl_8000C960
lbl_8000C95C:
/* 8000C95C 0000953C  FC 20 00 90 */	fmr f1, f0
lbl_8000C960:
/* 8000C960 00009540  C0 02 80 80 */	lfs f0, 0.0001f
/* 8000C964 00009544  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000C968 00009548  4C 40 13 82 */	cror 2, 0, 2
/* 8000C96C 0000954C  40 82 00 84 */	bne lbl_8000C9F0
/* 8000C970 00009550  C0 02 80 78 */	lfs f0, 0.0f
/* 8000C974 00009554  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8000C978 00009558  40 80 00 0C */	bge lbl_8000C984
/* 8000C97C 0000955C  FC 20 18 50 */	fneg f1, f3
/* 8000C980 00009560  48 00 00 08 */	b lbl_8000C988
lbl_8000C984:
/* 8000C984 00009564  FC 20 18 90 */	fmr f1, f3
lbl_8000C988:
/* 8000C988 00009568  C0 02 80 80 */	lfs f0, 0.0001f
/* 8000C98C 0000956C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000C990 00009570  4C 40 13 82 */	cror 2, 0, 2
/* 8000C994 00009574  40 82 00 5C */	bne lbl_8000C9F0
/* 8000C998 00009578  C0 02 80 78 */	lfs f0, 0.0f
/* 8000C99C 0000957C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000C9A0 00009580  40 80 00 0C */	bge lbl_8000C9AC
/* 8000C9A4 00009584  FC 20 10 50 */	fneg f1, f2
/* 8000C9A8 00009588  48 00 00 08 */	b lbl_8000C9B0
lbl_8000C9AC:
/* 8000C9AC 0000958C  FC 20 10 90 */	fmr f1, f2
lbl_8000C9B0:
/* 8000C9B0 00009590  C0 02 80 80 */	lfs f0, 0.0001f
/* 8000C9B4 00009594  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000C9B8 00009598  4C 40 13 82 */	cror 2, 0, 2
/* 8000C9BC 0000959C  40 82 00 34 */	bne lbl_8000C9F0
/* 8000C9C0 000095A0  D0 DE 00 1C */	stfs f6, 0x1c(r30)
/* 8000C9C4 000095A4  38 7E 00 00 */	addi r3, r30, 0
/* 8000C9C8 000095A8  3C 80 00 02 */	lis r4, 2
/* 8000C9CC 000095AC  C0 1C 00 18 */	lfs f0, 0x18(r28)
/* 8000C9D0 000095B0  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 8000C9D4 000095B4  C0 1C 00 1C */	lfs f0, 0x1c(r28)
/* 8000C9D8 000095B8  D0 1E 00 24 */	stfs f0, 0x24(r30)
/* 8000C9DC 000095BC  48 36 55 25 */	bl HSD_JObjClearFlags
/* 8000C9E0 000095C0  38 7E 00 00 */	addi r3, r30, 0
/* 8000C9E4 000095C4  38 80 00 40 */	li r4, 0x40
/* 8000C9E8 000095C8  48 36 53 19 */	bl HSD_JObjSetFlags
/* 8000C9EC 000095CC  48 00 01 50 */	b lbl_8000CB3C
lbl_8000C9F0:
/* 8000C9F0 000095D0  C0 1C 00 14 */	lfs f0, 0x14(r28)
/* 8000C9F4 000095D4  38 61 00 C0 */	addi r3, r1, 0xc0
/* 8000C9F8 000095D8  38 81 00 A4 */	addi r4, r1, 0xa4
/* 8000C9FC 000095DC  D0 01 00 C0 */	stfs f0, 0xc0(r1)
/* 8000CA00 000095E0  C0 1C 00 18 */	lfs f0, 0x18(r28)
/* 8000CA04 000095E4  D0 01 00 C4 */	stfs f0, 0xc4(r1)
/* 8000CA08 000095E8  C0 1C 00 1C */	lfs f0, 0x1c(r28)
/* 8000CA0C 000095EC  D0 01 00 C8 */	stfs f0, 0xc8(r1)
/* 8000CA10 000095F0  48 37 23 FD */	bl func_8037EE0C
/* 8000CA14 000095F4  2C 1F 00 00 */	cmpwi r31, 0
/* 8000CA18 000095F8  41 82 00 28 */	beq lbl_8000CA40
/* 8000CA1C 000095FC  80 7D 00 1C */	lwz r3, 0x1c(r29)
/* 8000CA20 00009600  80 1D 00 20 */	lwz r0, 0x20(r29)
/* 8000CA24 00009604  90 61 00 94 */	stw r3, 0x94(r1)
/* 8000CA28 00009608  90 01 00 98 */	stw r0, 0x98(r1)
/* 8000CA2C 0000960C  80 7D 00 24 */	lwz r3, 0x24(r29)
/* 8000CA30 00009610  80 1D 00 28 */	lwz r0, 0x28(r29)
/* 8000CA34 00009614  90 61 00 9C */	stw r3, 0x9c(r1)
/* 8000CA38 00009618  90 01 00 A0 */	stw r0, 0xa0(r1)
/* 8000CA3C 0000961C  48 00 00 28 */	b lbl_8000CA64
lbl_8000CA40:
/* 8000CA40 00009620  C0 1D 00 1C */	lfs f0, 0x1c(r29)
/* 8000CA44 00009624  38 61 00 B4 */	addi r3, r1, 0xb4
/* 8000CA48 00009628  38 81 00 94 */	addi r4, r1, 0x94
/* 8000CA4C 0000962C  D0 01 00 B4 */	stfs f0, 0xb4(r1)
/* 8000CA50 00009630  C0 1D 00 20 */	lfs f0, 0x20(r29)
/* 8000CA54 00009634  D0 01 00 B8 */	stfs f0, 0xb8(r1)
/* 8000CA58 00009638  C0 1D 00 24 */	lfs f0, 0x24(r29)
/* 8000CA5C 0000963C  D0 01 00 BC */	stfs f0, 0xbc(r1)
/* 8000CA60 00009640  48 37 23 AD */	bl func_8037EE0C
lbl_8000CA64:
/* 8000CA64 00009644  C0 01 00 98 */	lfs f0, 0x98(r1)
/* 8000CA68 00009648  C0 21 00 A8 */	lfs f1, 0xa8(r1)
/* 8000CA6C 0000964C  C0 E1 00 94 */	lfs f7, 0x94(r1)
/* 8000CA70 00009650  EC 41 00 28 */	fsubs f2, f1, f0
/* 8000CA74 00009654  C0 61 00 A4 */	lfs f3, 0xa4(r1)
/* 8000CA78 00009658  EC 01 00 2A */	fadds f0, f1, f0
/* 8000CA7C 0000965C  C0 A1 00 9C */	lfs f5, 0x9c(r1)
/* 8000CA80 00009660  EC 23 38 2A */	fadds f1, f3, f7
/* 8000CA84 00009664  EC 83 38 28 */	fsubs f4, f3, f7
/* 8000CA88 00009668  C0 C1 00 AC */	lfs f6, 0xac(r1)
/* 8000CA8C 0000966C  C0 61 00 A0 */	lfs f3, 0xa0(r1)
/* 8000CA90 00009670  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8000CA94 00009674  C1 21 00 B0 */	lfs f9, 0xb0(r1)
/* 8000CA98 00009678  ED 06 28 28 */	fsubs f8, f6, f5
/* 8000CA9C 0000967C  EC A6 28 2A */	fadds f5, f6, f5
/* 8000CAA0 00009680  ED 49 18 28 */	fsubs f10, f9, f3
/* 8000CAA4 00009684  EC C9 18 2A */	fadds f6, f9, f3
/* 8000CAA8 00009688  EC 64 01 32 */	fmuls f3, f4, f4
/* 8000CAAC 0000968C  EC 21 00 72 */	fmuls f1, f1, f1
/* 8000CAB0 00009690  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000CAB4 00009694  EC 63 10 2A */	fadds f3, f3, f2
/* 8000CAB8 00009698  EC 88 02 32 */	fmuls f4, f8, f8
/* 8000CABC 0000969C  EC 45 01 72 */	fmuls f2, f5, f5
/* 8000CAC0 000096A0  EC 01 00 2A */	fadds f0, f1, f0
/* 8000CAC4 000096A4  EC AA 02 B2 */	fmuls f5, f10, f10
/* 8000CAC8 000096A8  EC 64 18 2A */	fadds f3, f4, f3
/* 8000CACC 000096AC  EC 02 00 2A */	fadds f0, f2, f0
/* 8000CAD0 000096B0  EC 26 01 B2 */	fmuls f1, f6, f6
/* 8000CAD4 000096B4  EC 45 18 2A */	fadds f2, f5, f3
/* 8000CAD8 000096B8  EC 01 00 2A */	fadds f0, f1, f0
/* 8000CADC 000096BC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000CAE0 000096C0  40 81 00 30 */	ble lbl_8000CB10
/* 8000CAE4 000096C4  FC 00 38 50 */	fneg f0, f7
/* 8000CAE8 000096C8  D0 01 00 94 */	stfs f0, 0x94(r1)
/* 8000CAEC 000096CC  C0 01 00 98 */	lfs f0, 0x98(r1)
/* 8000CAF0 000096D0  FC 00 00 50 */	fneg f0, f0
/* 8000CAF4 000096D4  D0 01 00 98 */	stfs f0, 0x98(r1)
/* 8000CAF8 000096D8  C0 01 00 9C */	lfs f0, 0x9c(r1)
/* 8000CAFC 000096DC  FC 00 00 50 */	fneg f0, f0
/* 8000CB00 000096E0  D0 01 00 9C */	stfs f0, 0x9c(r1)
/* 8000CB04 000096E4  C0 01 00 A0 */	lfs f0, 0xa0(r1)
/* 8000CB08 000096E8  FC 00 00 50 */	fneg f0, f0
/* 8000CB0C 000096EC  D0 01 00 A0 */	stfs f0, 0xa0(r1)
lbl_8000CB10:
/* 8000CB10 000096F0  FC 20 F8 90 */	fmr f1, f31
/* 8000CB14 000096F4  38 61 00 A4 */	addi r3, r1, 0xa4
/* 8000CB18 000096F8  38 81 00 94 */	addi r4, r1, 0x94
/* 8000CB1C 000096FC  38 BE 00 1C */	addi r5, r30, 0x1c
/* 8000CB20 00009700  48 37 24 09 */	bl func_8037EF28
/* 8000CB24 00009704  38 7E 00 00 */	addi r3, r30, 0
/* 8000CB28 00009708  3C 80 00 02 */	lis r4, 2
/* 8000CB2C 0000970C  48 36 51 D5 */	bl HSD_JObjSetFlags
/* 8000CB30 00009710  38 7E 00 00 */	addi r3, r30, 0
/* 8000CB34 00009714  38 80 00 40 */	li r4, 0x40
/* 8000CB38 00009718  48 36 51 C9 */	bl HSD_JObjSetFlags
lbl_8000CB3C:
/* 8000CB3C 0000971C  80 01 00 EC */	lwz r0, 0xec(r1)
/* 8000CB40 00009720  CB E1 00 E0 */	lfd f31, 0xe0(r1)
/* 8000CB44 00009724  83 E1 00 DC */	lwz r31, 0xdc(r1)
/* 8000CB48 00009728  83 C1 00 D8 */	lwz r30, 0xd8(r1)
/* 8000CB4C 0000972C  83 A1 00 D4 */	lwz r29, 0xd4(r1)
/* 8000CB50 00009730  83 81 00 D0 */	lwz r28, 0xd0(r1)
/* 8000CB54 00009734  38 21 00 E8 */	addi r1, r1, 0xe8
/* 8000CB58 00009738  7C 08 03 A6 */	mtlr r0
/* 8000CB5C 0000973C  4E 80 00 20 */	blr 
}
#pragma peephole on

static s32 lbGetFreeColorRegImpl(s32 i0, HSD_TevDesc* tevdesc,
                                 HSD_TExp* texp1, HSD_TExp* texp2)
{
    BOOL register_used[8];
    int i;

    for (i = 0; i < 8; i++) {
        register_used[i] = FALSE;
    }
    while (texp1 != NULL) {
        if (texp1->cnst.reg < 8) {
            register_used[texp1->cnst.reg] = TRUE;
        }
        texp1 = texp1->cnst.next;
    }
    while (tevdesc != NULL) {
        s32 idx = lbl_803B9FF0[tevdesc->u.tevconf.clr_out_reg];
        register_used[idx] = TRUE;
        tevdesc = tevdesc->next;
    }
    while (texp2 != NULL) {
        if (texp2->cnst.reg < 8) {
            register_used[texp2->cnst.reg] = TRUE;
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

// lbGetFreeColorRegister
s32 func_8000CC5C(s32 i0, HSD_MObj* mobj, HSD_TExp* texp)
{
    return lbGetFreeColorRegImpl(i0, &mobj->tevdesc->desc, mobj->texp, texp);
}

s32 func_8000CC8C(s32 i)
{
    return lbl_803B9FC0[i];
}

s32 func_8000CCA4(s32 i)
{
    return lbl_803B9FE0[i];
}

static s32 lbGetFreeAlphaRegImpl(s32 i0, HSD_TevDesc* cur, HSD_TExp*, HSD_TExp*)
{
    BOOL register_used[8];
    int i;

    for (i = 0; i < 8; i++) {
        register_used[i] = FALSE;
    }
    while (cur != NULL) {
        s32 idx = lbl_803BA030[cur->u.tevconf.alpha_out_reg];
        register_used[idx] = TRUE;
        cur = cur->next;
    }
    for (i = i0; i < 7; i++) {
        if (!register_used[i]) {
            return i;
        }
    }
    return -1;
}

// lbGetFreeAlphaRegister
s32 func_8000CD60(s32 i0, HSD_MObj* mobj, HSD_TExp* texp)
{
    return lbGetFreeAlphaRegImpl(i0, &mobj->tevdesc->desc, mobj->texp, texp);
}

s32 func_8000CD90(s32 i)
{
    return lbl_803BA000[i];
}

s32 func_8000CDA8(s32 i)
{
    return lbl_803BA020[i];
}

inline HSD_LObj* lobj_next(HSD_LObj* lobj)
{
    if (lobj == NULL) {
        return NULL;
    }
    return lobj->next;
}

HSD_LObj* func_8000CDC0(HSD_LObj* cur)
{
    while (cur != NULL) {
        if (!(cur->flags & 3) && !(HSD_LObjGetFlags(cur) & 0x20)) {
            return cur;
        }
        cur = lobj_next(cur);
    }
}

void func_8000CE30(HSD_DObj* dobj, HSD_DObj* next)
{
    if (dobj != NULL) {
        dobj->next = next;
    }
}

void func_8000CE40(HSD_JObj* jobj, HSD_DObj* dobj)
{
    if (jobj != NULL) {
        jobj->u.dobj = dobj;
    }
}
