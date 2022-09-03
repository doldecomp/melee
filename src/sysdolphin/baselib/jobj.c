#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/robj.h>

void JObjInfoInit(void);
HSD_JObjInfo hsdJObj = { JObjInfoInit };

static HSD_JObjInfo* default_class;
static HSD_SList* ufc_callbacks;
static void (*dptcl_callback)();
static void (*jsound_callback)(s32);
static void (*ptcltgt_callback)(HSD_JObj*, s32);
static HSD_JObj* current_jobj;

void HSD_JObjCheckDepend(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return;
    }

    switch (HSD_JObjMtxIsDirty(jobj)) {
        case FALSE:
            if ((jobj->flags & JOBJ_USER_DEF_MTX)){
                if (!(jobj->flags & JOBJ_MTX_INDEP_PARENT) && jobj->parent != NULL && HSD_JObjMtxIsDirty(jobj->parent)){
                    jobj->flags |= JOBJ_MTX_DIRTY;
                }
            }
            else if (jobj->parent != NULL && (jobj->parent->flags & JOBJ_MTX_DIRTY)
                || (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT1
                || (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2
                || (jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR
                || jobj->robj != NULL) {
                    jobj->flags |= JOBJ_MTX_DIRTY;
            }
        break;
    }
}

void JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void HSD_JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    JObjResetRST(jobj, joint);
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child_jobj = jobj->child;
        HSD_Joint* child_joint = joint->child;
        while (child_jobj != NULL) {
            HSD_JObjResetRST(child_jobj, child_joint);
            child_jobj = child_jobj->next;
            child_joint = child_joint != NULL ? child_joint->next : NULL;
        }
    }
}

void HSD_JObjWalkTree0(HSD_JObj* jobj, void (*cb)(HSD_JObj*, void*, u32), void* args)
{
    u32 type;

    if (jobj == NULL) {
        return;
    }
    assert_line(0xAE, jobj->parent);
    type = jobj->parent->child == jobj ? 1 : 2;
    if (cb != NULL) {
        cb(jobj, args, type);
    }
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            HSD_JObjWalkTree0(child, cb, args);
            child = child->next;
        }
    }
}

void HSD_JObjWalkTree(HSD_JObj* jobj, void (*cb)(HSD_JObj*, void*, u32), void* args)
{
    if (jobj == NULL) {
        return;
    }
    if (cb != NULL) {
        cb(jobj, args, 0);
    }
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            HSD_JObjWalkTree0(child, cb, args);
            child = child->next;
        }
    }
}

inline BOOL has_scl(HSD_JObj* jobj)
{
    BOOL result = FALSE;
    if (jobj != NULL && jobj->scl != NULL)
        result = TRUE;
    return result;
}

void HSD_JObjMakeMatrix(HSD_JObj* jobj)
{
    Vec* scl;

    HSD_JObjSetupMatrix(jobj->parent);
    if (jobj->flags & 8) {
        if (jobj->parent != NULL && jobj->parent->scl != NULL) {
            if (jobj->scl == NULL) {
                jobj->scl = HSD_VecAlloc();
            }
            *jobj->scl = *jobj->parent->scl;
        } else {
            if (jobj->scl != NULL) {
                HSD_VecFree(jobj->scl);
                jobj->scl = NULL;
            }
        }
    } else {
        if (jobj->scl == NULL) {
            jobj->scl = HSD_VecAlloc();
        }
        if (jobj->parent != NULL && jobj->parent->scl != NULL) {
            jobj->scl->x = jobj->scale.x * jobj->parent->scl->x;
            jobj->scl->y = jobj->scale.y * jobj->parent->scl->y;
            jobj->scl->z = jobj->scale.z * jobj->parent->scl->z;
        } else {
            *jobj->scl = jobj->scale;
        }
    }
    if (jobj->flags & 0x20000) {
        if (has_scl(jobj->parent)) {
            scl = jobj->parent->scl;
        } else {
            scl = NULL;
        }
        HSD_MtxSRTQuat(jobj->mtx, &jobj->scale, &jobj->rotate, &jobj->translate, scl);
    } else {
        if (has_scl(jobj->parent)) {
            scl = jobj->parent->scl;
        } else {
            scl = NULL;
        }
        HSD_MtxSRT(jobj->mtx, &jobj->scale, (Vec*) &jobj->rotate, &jobj->translate, scl);
    }
    if (jobj->parent != NULL) {
        PSMTXConcat(jobj->parent->mtx, jobj->mtx, jobj->mtx);
    }
    if (jobj->aobj != NULL && jobj->aobj->hsd_obj != NULL) {
        Vec vec;
        HSD_JObj* aobj_jobj = (HSD_JObj*) jobj->aobj->hsd_obj;
        HSD_JObjSetupMatrix((HSD_JObj*) jobj->aobj->hsd_obj);
        PSMTXMUltiVec(aobj_jobj->mtx, &jobj->translate, &vec);
        jobj->mtx[0][3] = vec.x;
        jobj->mtx[1][3] = vec.y;
        jobj->mtx[2][3] = vec.z;
    }
}

void HSD_JObjRemoveAnimByFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjRemove(jobj->aobj);
            jobj->aobj = NULL;
        }
        if (union_type_dobj(jobj)) {
            HSD_DObjRemoveAnimAllByFlags(jobj->u.dobj, flags);
        }
        HSD_RObjRemoveAnimAllByFlags(jobj->robj, flags);
    }
}

void HSD_JObjRemoveAnimAllByFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjRemoveAnimByFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjRemoveAnimAllByFlags(child, flags);
                child = child->next;
            }
        }
    }
}

void HSD_JObjRemoveAnim(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimByFlags(jobj, 0x7FF);
}

void HSD_JObjRemoveAnimAll(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimAllByFlags(jobj, 0x7FF);
}

void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    BOOL has_dobj;
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjReqAnim(jobj->aobj, frame);
        }
        if (jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
            has_dobj = FALSE;
        } else {
            has_dobj = TRUE;
        }
        if (has_dobj) {
            HSD_DObjReqAnimAllByFlags(jobj->u.dobj, frame, flags);
        }
        HSD_RObjReqAnimAllByFlags(jobj->robj, frame, flags);
    }
}

void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    if (jobj != NULL) {
        HSD_JObjReqAnimByFlags(jobj, flags, frame);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjReqAnimAllByFlags(child, flags, frame);
                child = child->next;
            }
        }
    }
}

void HSD_JObjReqAnimAll(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimAllByFlags(jobj, 0x7FF, frame);
}

void HSD_JObjReqAnim(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimByFlags(jobj, 0x7FF, frame);
}

void JObjSortAnim(HSD_AObj* aobj)
{
    HSD_FObj* fobj;
    HSD_FObj** fobj_ptr;

    if (aobj == NULL || aobj->fobj == NULL) {
        return;
    }
    fobj_ptr = &aobj->fobj;
    while ((fobj = *fobj_ptr) != NULL) {
        if (fobj->obj_type == TYPE_JOBJ) {
            *fobj_ptr = fobj->next;
            fobj->next = aobj->fobj;
            aobj->fobj = fobj;
            break;
        }
        fobj_ptr = &fobj->next;
    }
}

// https://decomp.me/scratch/uPtWK
#ifdef NON_MATCHING
void HSD_JObjAddAnim(HSD_JObj* jobj, HSD_AnimJoint* an_joint,
                     HSD_MatAnimJoint* mat_joint, HSD_ShapeAnimJoint* sh_joint)
{
    u32 unused;
    BOOL has_dobj;

    if (jobj != NULL) {
        if (an_joint != NULL) {
            if (jobj->aobj != NULL) {
                HSD_AObjRemove(jobj->aobj);
            }
            jobj->aobj = HSD_AObjLoadDesc(an_joint->aobjdesc);
            JObjSortAnim(jobj->aobj);
            HSD_RObjAddAnimAll(jobj->robj, an_joint->robj_anim);
            if (an_joint->flags & 1) {
                HSD_JObjSetFlags(jobj, JOBJ_CLASSICAL_SCALE);
            } else {
                HSD_JObjClearFlags(jobj, JOBJ_CLASSICAL_SCALE);
            }
        }
        if (jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
            has_dobj = FALSE;
        } else {
            has_dobj = TRUE;
        }
        if (has_dobj) {
            HSD_DObjAddAnimAll(jobj->u.dobj,
                               mat_joint != NULL ? mat_joint->matanim : NULL,
                               sh_joint != NULL ? sh_joint->shapeanimdobj : NULL);
        }
    }
}
#else
#pragma push
asm void HSD_JObjAddAnim(HSD_JObj*, HSD_AnimJoint* an_joint,
                         HSD_MatAnimJoint* mat_joint, HSD_ShapeAnimJoint* sh_joint)
{ // clang-format off
    nofralloc
/* 8036FA10 0036C5F0  7C 08 02 A6 */	mflr r0
/* 8036FA14 0036C5F4  90 01 00 04 */	stw r0, 4(r1)
/* 8036FA18 0036C5F8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8036FA1C 0036C5FC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8036FA20 0036C600  7C 7F 1B 79 */	or. r31, r3, r3
/* 8036FA24 0036C604  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8036FA28 0036C608  3B C6 00 00 */	addi r30, r6, 0
/* 8036FA2C 0036C60C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8036FA30 0036C610  3B A5 00 00 */	addi r29, r5, 0
/* 8036FA34 0036C614  93 81 00 20 */	stw r28, 0x20(r1)
/* 8036FA38 0036C618  3B 84 00 00 */	addi r28, r4, 0
/* 8036FA3C 0036C61C  41 82 01 00 */	beq lbl_8036FB3C
/* 8036FA40 0036C620  28 1C 00 00 */	cmplwi r28, 0
/* 8036FA44 0036C624  41 82 00 A8 */	beq lbl_8036FAEC
/* 8036FA48 0036C628  80 7F 00 7C */	lwz r3, 0x7c(r31)
/* 8036FA4C 0036C62C  28 03 00 00 */	cmplwi r3, 0
/* 8036FA50 0036C630  41 82 00 08 */	beq lbl_8036FA58
/* 8036FA54 0036C634  4B FF 4A 79 */	bl HSD_AObjRemove
lbl_8036FA58:
/* 8036FA58 0036C638  80 7C 00 08 */	lwz r3, 8(r28)
/* 8036FA5C 0036C63C  4B FF 49 41 */	bl HSD_AObjLoadDesc
/* 8036FA60 0036C640  90 7F 00 7C */	stw r3, 0x7c(r31)
/* 8036FA64 0036C644  80 9F 00 7C */	lwz r4, 0x7c(r31)
/* 8036FA68 0036C648  28 04 00 00 */	cmplwi r4, 0
/* 8036FA6C 0036C64C  41 82 00 4C */	beq lbl_8036FAB8
/* 8036FA70 0036C650  80 04 00 14 */	lwz r0, 0x14(r4)
/* 8036FA74 0036C654  28 00 00 00 */	cmplwi r0, 0
/* 8036FA78 0036C658  41 82 00 40 */	beq lbl_8036FAB8
/* 8036FA7C 0036C65C  38 64 00 14 */	addi r3, r4, 0x14
/* 8036FA80 0036C660  48 00 00 2C */	b lbl_8036FAAC
lbl_8036FA84:
/* 8036FA84 0036C664  88 05 00 13 */	lbz r0, 0x13(r5)
/* 8036FA88 0036C668  28 00 00 0C */	cmplwi r0, 0xc
/* 8036FA8C 0036C66C  40 82 00 1C */	bne lbl_8036FAA8
/* 8036FA90 0036C670  80 05 00 00 */	lwz r0, 0(r5)
/* 8036FA94 0036C674  90 03 00 00 */	stw r0, 0(r3)
/* 8036FA98 0036C678  80 04 00 14 */	lwz r0, 0x14(r4)
/* 8036FA9C 0036C67C  90 05 00 00 */	stw r0, 0(r5)
/* 8036FAA0 0036C680  90 A4 00 14 */	stw r5, 0x14(r4)
/* 8036FAA4 0036C684  48 00 00 14 */	b lbl_8036FAB8
lbl_8036FAA8:
/* 8036FAA8 0036C688  7C A3 2B 78 */	mr r3, r5
lbl_8036FAAC:
/* 8036FAAC 0036C68C  80 A3 00 00 */	lwz r5, 0(r3)
/* 8036FAB0 0036C690  28 05 00 00 */	cmplwi r5, 0
/* 8036FAB4 0036C694  40 82 FF D0 */	bne lbl_8036FA84
lbl_8036FAB8:
/* 8036FAB8 0036C698  80 7F 00 80 */	lwz r3, 0x80(r31)
/* 8036FABC 0036C69C  80 9C 00 0C */	lwz r4, 0xc(r28)
/* 8036FAC0 0036C6A0  48 00 B6 E1 */	bl HSD_RObjAddAnimAll
/* 8036FAC4 0036C6A4  80 1C 00 10 */	lwz r0, 0x10(r28)
/* 8036FAC8 0036C6A8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8036FACC 0036C6AC  41 82 00 14 */	beq lbl_8036FAE0
/* 8036FAD0 0036C6B0  38 7F 00 00 */	addi r3, r31, 0
/* 8036FAD4 0036C6B4  38 80 00 08 */	li r4, 8
/* 8036FAD8 0036C6B8  48 00 22 29 */	bl HSD_JObjSetFlags
/* 8036FADC 0036C6BC  48 00 00 10 */	b lbl_8036FAEC
lbl_8036FAE0:
/* 8036FAE0 0036C6C0  38 7F 00 00 */	addi r3, r31, 0
/* 8036FAE4 0036C6C4  38 80 00 08 */	li r4, 8
/* 8036FAE8 0036C6C8  48 00 24 19 */	bl HSD_JObjClearFlags
lbl_8036FAEC:
/* 8036FAEC 0036C6CC  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8036FAF0 0036C6D0  70 00 40 20 */	andi. r0, r0, 0x4020
/* 8036FAF4 0036C6D4  41 82 00 0C */	beq lbl_8036FB00
/* 8036FAF8 0036C6D8  38 00 00 00 */	li r0, 0
/* 8036FAFC 0036C6DC  48 00 00 08 */	b lbl_8036FB04
lbl_8036FB00:
/* 8036FB00 0036C6E0  38 00 00 01 */	li r0, 1
lbl_8036FB04:
/* 8036FB04 0036C6E4  2C 00 00 00 */	cmpwi r0, 0
/* 8036FB08 0036C6E8  41 82 00 34 */	beq lbl_8036FB3C
/* 8036FB0C 0036C6EC  28 1E 00 00 */	cmplwi r30, 0
/* 8036FB10 0036C6F0  41 82 00 0C */	beq lbl_8036FB1C
/* 8036FB14 0036C6F4  80 BE 00 08 */	lwz r5, 8(r30)
/* 8036FB18 0036C6F8  48 00 00 08 */	b lbl_8036FB20
lbl_8036FB1C:
/* 8036FB1C 0036C6FC  38 A0 00 00 */	li r5, 0
lbl_8036FB20:
/* 8036FB20 0036C700  28 1D 00 00 */	cmplwi r29, 0
/* 8036FB24 0036C704  41 82 00 0C */	beq lbl_8036FB30
/* 8036FB28 0036C708  80 9D 00 08 */	lwz r4, 8(r29)
/* 8036FB2C 0036C70C  48 00 00 08 */	b lbl_8036FB34
lbl_8036FB30:
/* 8036FB30 0036C710  38 80 00 00 */	li r4, 0
lbl_8036FB34:
/* 8036FB34 0036C714  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 8036FB38 0036C718  4B FE E3 69 */	bl HSD_DObjAddAnimAll
lbl_8036FB3C:
/* 8036FB3C 0036C71C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8036FB40 0036C720  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8036FB44 0036C724  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8036FB48 0036C728  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8036FB4C 0036C72C  83 81 00 20 */	lwz r28, 0x20(r1)
/* 8036FB50 0036C730  38 21 00 30 */	addi r1, r1, 0x30
/* 8036FB54 0036C734  7C 08 03 A6 */	mtlr r0
/* 8036FB58 0036C738  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
#endif

// This should match once HSD_JObjAddAnim matches.
// https://decomp.me/scratch/MYXYk
#ifdef NON_MATCHING
void HSD_JObjAddAnimAll(HSD_JObj* jobj, HSD_AnimJoint* arg1,
                        HSD_MatAnimJoint* arg2, HSD_ShapeAnimJoint* arg3)
{

    HSD_JObj* var_r31;
    HSD_AnimJoint* var_r26;
    HSD_MatAnimJoint* var_r25;
    HSD_ShapeAnimJoint* var_r24;

    if (jobj != NULL) {
        HSD_JObjAddAnim(jobj, arg1, arg2, arg3);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            var_r31 = jobj->child;
            var_r26 = arg1 != NULL ? arg1->child : NULL;
            var_r25 = arg2 != NULL ? arg2->child : NULL;
            var_r24 = arg3 != NULL ? arg3->child : NULL;
            while (var_r31 != NULL) {
                HSD_JObjAddAnimAll(var_r31, var_r26, var_r25, var_r24);
                var_r31 = var_r31->next;
                var_r26 = var_r26 != NULL ? var_r26->next : NULL;
                var_r25 = var_r25 != NULL ? var_r25->next : NULL;
                var_r24 = var_r24 != NULL ? var_r24->next : NULL;
            }
        }
    }
}
#else
#pragma push
asm void HSD_JObjAddAnimAll(HSD_JObj*, HSD_AnimJoint*,
                            HSD_MatAnimJoint*, HSD_ShapeAnimJoint*)
{ // clang-format off
    nofralloc
/* 8036FB5C 0036C73C  7C 08 02 A6 */	mflr r0
/* 8036FB60 0036C740  90 01 00 04 */	stw r0, 4(r1)
/* 8036FB64 0036C744  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8036FB68 0036C748  BF 01 00 18 */	stmw r24, 0x18(r1)
/* 8036FB6C 0036C74C  7C 7B 1B 79 */	or. r27, r3, r3
/* 8036FB70 0036C750  3B 44 00 00 */	addi r26, r4, 0
/* 8036FB74 0036C754  3B 25 00 00 */	addi r25, r5, 0
/* 8036FB78 0036C758  3B 06 00 00 */	addi r24, r6, 0
/* 8036FB7C 0036C75C  41 82 02 30 */	beq lbl_8036FDAC
/* 8036FB80 0036C760  41 82 00 B4 */	beq lbl_8036FC34
/* 8036FB84 0036C764  28 1A 00 00 */	cmplwi r26, 0
/* 8036FB88 0036C768  41 82 00 5C */	beq lbl_8036FBE4
/* 8036FB8C 0036C76C  80 7B 00 7C */	lwz r3, 0x7c(r27)
/* 8036FB90 0036C770  28 03 00 00 */	cmplwi r3, 0
/* 8036FB94 0036C774  41 82 00 08 */	beq lbl_8036FB9C
/* 8036FB98 0036C778  4B FF 49 35 */	bl HSD_AObjRemove
lbl_8036FB9C:
/* 8036FB9C 0036C77C  80 7A 00 08 */	lwz r3, 8(r26)
/* 8036FBA0 0036C780  4B FF 47 FD */	bl HSD_AObjLoadDesc
/* 8036FBA4 0036C784  90 7B 00 7C */	stw r3, 0x7c(r27)
/* 8036FBA8 0036C788  80 7B 00 7C */	lwz r3, 0x7c(r27)
/* 8036FBAC 0036C78C  4B FF FE 0D */	bl JObjSortAnim
/* 8036FBB0 0036C790  80 7B 00 80 */	lwz r3, 0x80(r27)
/* 8036FBB4 0036C794  80 9A 00 0C */	lwz r4, 0xc(r26)
/* 8036FBB8 0036C798  48 00 B5 E9 */	bl HSD_RObjAddAnimAll
/* 8036FBBC 0036C79C  80 1A 00 10 */	lwz r0, 0x10(r26)
/* 8036FBC0 0036C7A0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8036FBC4 0036C7A4  41 82 00 14 */	beq lbl_8036FBD8
/* 8036FBC8 0036C7A8  38 7B 00 00 */	addi r3, r27, 0
/* 8036FBCC 0036C7AC  38 80 00 08 */	li r4, 8
/* 8036FBD0 0036C7B0  48 00 21 31 */	bl HSD_JObjSetFlags
/* 8036FBD4 0036C7B4  48 00 00 10 */	b lbl_8036FBE4
lbl_8036FBD8:
/* 8036FBD8 0036C7B8  38 7B 00 00 */	addi r3, r27, 0
/* 8036FBDC 0036C7BC  38 80 00 08 */	li r4, 8
/* 8036FBE0 0036C7C0  48 00 23 21 */	bl HSD_JObjClearFlags
lbl_8036FBE4:
/* 8036FBE4 0036C7C4  80 1B 00 14 */	lwz r0, 0x14(r27)
/* 8036FBE8 0036C7C8  70 00 40 20 */	andi. r0, r0, 0x4020
/* 8036FBEC 0036C7CC  41 82 00 0C */	beq lbl_8036FBF8
/* 8036FBF0 0036C7D0  38 00 00 00 */	li r0, 0
/* 8036FBF4 0036C7D4  48 00 00 08 */	b lbl_8036FBFC
lbl_8036FBF8:
/* 8036FBF8 0036C7D8  38 00 00 01 */	li r0, 1
lbl_8036FBFC:
/* 8036FBFC 0036C7DC  2C 00 00 00 */	cmpwi r0, 0
/* 8036FC00 0036C7E0  41 82 00 34 */	beq lbl_8036FC34
/* 8036FC04 0036C7E4  28 18 00 00 */	cmplwi r24, 0
/* 8036FC08 0036C7E8  41 82 00 0C */	beq lbl_8036FC14
/* 8036FC0C 0036C7EC  80 B8 00 08 */	lwz r5, 8(r24)
/* 8036FC10 0036C7F0  48 00 00 08 */	b lbl_8036FC18
lbl_8036FC14:
/* 8036FC14 0036C7F4  38 A0 00 00 */	li r5, 0
lbl_8036FC18:
/* 8036FC18 0036C7F8  28 19 00 00 */	cmplwi r25, 0
/* 8036FC1C 0036C7FC  41 82 00 0C */	beq lbl_8036FC28
/* 8036FC20 0036C800  80 99 00 08 */	lwz r4, 8(r25)
/* 8036FC24 0036C804  48 00 00 08 */	b lbl_8036FC2C
lbl_8036FC28:
/* 8036FC28 0036C808  38 80 00 00 */	li r4, 0
lbl_8036FC2C:
/* 8036FC2C 0036C80C  80 7B 00 18 */	lwz r3, 0x18(r27)
/* 8036FC30 0036C810  4B FE E2 71 */	bl HSD_DObjAddAnimAll
lbl_8036FC34:
/* 8036FC34 0036C814  80 1B 00 14 */	lwz r0, 0x14(r27)
/* 8036FC38 0036C818  54 00 04 E7 */	rlwinm. r0, r0, 0, 0x13, 0x13
/* 8036FC3C 0036C81C  40 82 01 70 */	bne lbl_8036FDAC
/* 8036FC40 0036C820  28 1A 00 00 */	cmplwi r26, 0
/* 8036FC44 0036C824  83 FB 00 10 */	lwz r31, 0x10(r27)
/* 8036FC48 0036C828  41 82 00 0C */	beq lbl_8036FC54
/* 8036FC4C 0036C82C  80 1A 00 00 */	lwz r0, 0(r26)
/* 8036FC50 0036C830  48 00 00 08 */	b lbl_8036FC58
lbl_8036FC54:
/* 8036FC54 0036C834  38 00 00 00 */	li r0, 0
lbl_8036FC58:
/* 8036FC58 0036C838  28 19 00 00 */	cmplwi r25, 0
/* 8036FC5C 0036C83C  7C 1A 03 78 */	mr r26, r0
/* 8036FC60 0036C840  41 82 00 0C */	beq lbl_8036FC6C
/* 8036FC64 0036C844  80 19 00 00 */	lwz r0, 0(r25)
/* 8036FC68 0036C848  48 00 00 08 */	b lbl_8036FC70
lbl_8036FC6C:
/* 8036FC6C 0036C84C  38 00 00 00 */	li r0, 0
lbl_8036FC70:
/* 8036FC70 0036C850  28 18 00 00 */	cmplwi r24, 0
/* 8036FC74 0036C854  7C 19 03 78 */	mr r25, r0
/* 8036FC78 0036C858  41 82 00 0C */	beq lbl_8036FC84
/* 8036FC7C 0036C85C  80 18 00 00 */	lwz r0, 0(r24)
/* 8036FC80 0036C860  48 00 00 08 */	b lbl_8036FC88
lbl_8036FC84:
/* 8036FC84 0036C864  38 00 00 00 */	li r0, 0
lbl_8036FC88:
/* 8036FC88 0036C868  7C 18 03 78 */	mr r24, r0
/* 8036FC8C 0036C86C  48 00 01 18 */	b lbl_8036FDA4
lbl_8036FC90:
/* 8036FC90 0036C870  28 1F 00 00 */	cmplwi r31, 0
/* 8036FC94 0036C874  41 82 00 C4 */	beq lbl_8036FD58
/* 8036FC98 0036C878  38 7F 00 00 */	addi r3, r31, 0
/* 8036FC9C 0036C87C  38 9A 00 00 */	addi r4, r26, 0
/* 8036FCA0 0036C880  38 B9 00 00 */	addi r5, r25, 0
/* 8036FCA4 0036C884  38 D8 00 00 */	addi r6, r24, 0
/* 8036FCA8 0036C888  4B FF FD 69 */	bl HSD_JObjAddAnim
/* 8036FCAC 0036C88C  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8036FCB0 0036C890  54 00 04 E7 */	rlwinm. r0, r0, 0, 0x13, 0x13
/* 8036FCB4 0036C894  40 82 00 A4 */	bne lbl_8036FD58
/* 8036FCB8 0036C898  28 1A 00 00 */	cmplwi r26, 0
/* 8036FCBC 0036C89C  83 DF 00 10 */	lwz r30, 0x10(r31)
/* 8036FCC0 0036C8A0  41 82 00 0C */	beq lbl_8036FCCC
/* 8036FCC4 0036C8A4  83 BA 00 00 */	lwz r29, 0(r26)
/* 8036FCC8 0036C8A8  48 00 00 08 */	b lbl_8036FCD0
lbl_8036FCCC:
/* 8036FCCC 0036C8AC  3B A0 00 00 */	li r29, 0
lbl_8036FCD0:
/* 8036FCD0 0036C8B0  28 19 00 00 */	cmplwi r25, 0
/* 8036FCD4 0036C8B4  41 82 00 0C */	beq lbl_8036FCE0
/* 8036FCD8 0036C8B8  83 99 00 00 */	lwz r28, 0(r25)
/* 8036FCDC 0036C8BC  48 00 00 08 */	b lbl_8036FCE4
lbl_8036FCE0:
/* 8036FCE0 0036C8C0  3B 80 00 00 */	li r28, 0
lbl_8036FCE4:
/* 8036FCE4 0036C8C4  28 18 00 00 */	cmplwi r24, 0
/* 8036FCE8 0036C8C8  41 82 00 0C */	beq lbl_8036FCF4
/* 8036FCEC 0036C8CC  83 78 00 00 */	lwz r27, 0(r24)
/* 8036FCF0 0036C8D0  48 00 00 60 */	b lbl_8036FD50
lbl_8036FCF4:
/* 8036FCF4 0036C8D4  3B 60 00 00 */	li r27, 0
/* 8036FCF8 0036C8D8  48 00 00 58 */	b lbl_8036FD50
lbl_8036FCFC:
/* 8036FCFC 0036C8DC  38 7E 00 00 */	addi r3, r30, 0
/* 8036FD00 0036C8E0  38 9D 00 00 */	addi r4, r29, 0
/* 8036FD04 0036C8E4  38 BC 00 00 */	addi r5, r28, 0
/* 8036FD08 0036C8E8  38 DB 00 00 */	addi r6, r27, 0
/* 8036FD0C 0036C8EC  4B FF FE 51 */	bl HSD_JObjAddAnimAll
/* 8036FD10 0036C8F0  28 1D 00 00 */	cmplwi r29, 0
/* 8036FD14 0036C8F4  83 DE 00 08 */	lwz r30, 8(r30)
/* 8036FD18 0036C8F8  41 82 00 0C */	beq lbl_8036FD24
/* 8036FD1C 0036C8FC  83 BD 00 04 */	lwz r29, 4(r29)
/* 8036FD20 0036C900  48 00 00 08 */	b lbl_8036FD28
lbl_8036FD24:
/* 8036FD24 0036C904  3B A0 00 00 */	li r29, 0
lbl_8036FD28:
/* 8036FD28 0036C908  28 1C 00 00 */	cmplwi r28, 0
/* 8036FD2C 0036C90C  41 82 00 0C */	beq lbl_8036FD38
/* 8036FD30 0036C910  83 9C 00 04 */	lwz r28, 4(r28)
/* 8036FD34 0036C914  48 00 00 08 */	b lbl_8036FD3C
lbl_8036FD38:
/* 8036FD38 0036C918  3B 80 00 00 */	li r28, 0
lbl_8036FD3C:
/* 8036FD3C 0036C91C  28 1B 00 00 */	cmplwi r27, 0
/* 8036FD40 0036C920  41 82 00 0C */	beq lbl_8036FD4C
/* 8036FD44 0036C924  83 7B 00 04 */	lwz r27, 4(r27)
/* 8036FD48 0036C928  48 00 00 08 */	b lbl_8036FD50
lbl_8036FD4C:
/* 8036FD4C 0036C92C  3B 60 00 00 */	li r27, 0
lbl_8036FD50:
/* 8036FD50 0036C930  28 1E 00 00 */	cmplwi r30, 0
/* 8036FD54 0036C934  40 82 FF A8 */	bne lbl_8036FCFC
lbl_8036FD58:
/* 8036FD58 0036C938  28 1A 00 00 */	cmplwi r26, 0
/* 8036FD5C 0036C93C  83 FF 00 08 */	lwz r31, 8(r31)
/* 8036FD60 0036C940  41 82 00 0C */	beq lbl_8036FD6C
/* 8036FD64 0036C944  80 1A 00 04 */	lwz r0, 4(r26)
/* 8036FD68 0036C948  48 00 00 08 */	b lbl_8036FD70
lbl_8036FD6C:
/* 8036FD6C 0036C94C  38 00 00 00 */	li r0, 0
lbl_8036FD70:
/* 8036FD70 0036C950  28 19 00 00 */	cmplwi r25, 0
/* 8036FD74 0036C954  7C 1A 03 78 */	mr r26, r0
/* 8036FD78 0036C958  41 82 00 0C */	beq lbl_8036FD84
/* 8036FD7C 0036C95C  80 19 00 04 */	lwz r0, 4(r25)
/* 8036FD80 0036C960  48 00 00 08 */	b lbl_8036FD88
lbl_8036FD84:
/* 8036FD84 0036C964  38 00 00 00 */	li r0, 0
lbl_8036FD88:
/* 8036FD88 0036C968  28 18 00 00 */	cmplwi r24, 0
/* 8036FD8C 0036C96C  7C 19 03 78 */	mr r25, r0
/* 8036FD90 0036C970  41 82 00 0C */	beq lbl_8036FD9C
/* 8036FD94 0036C974  80 18 00 04 */	lwz r0, 4(r24)
/* 8036FD98 0036C978  48 00 00 08 */	b lbl_8036FDA0
lbl_8036FD9C:
/* 8036FD9C 0036C97C  38 00 00 00 */	li r0, 0
lbl_8036FDA0:
/* 8036FDA0 0036C980  7C 18 03 78 */	mr r24, r0
lbl_8036FDA4:
/* 8036FDA4 0036C984  28 1F 00 00 */	cmplwi r31, 0
/* 8036FDA8 0036C988  40 82 FE E8 */	bne lbl_8036FC90
lbl_8036FDAC:
/* 8036FDAC 0036C98C  BB 01 00 18 */	lmw r24, 0x18(r1)
/* 8036FDB0 0036C990  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8036FDB4 0036C994  38 21 00 38 */	addi r1, r1, 0x38
/* 8036FDB8 0036C998  7C 08 03 A6 */	mtlr r0
/* 8036FDBC 0036C99C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
#endif

typedef void (*ufc_callback)(HSD_JObj*, u32, f32);

void JObjUpdateFunc(void* obj, u32 type, FObjData* val)
{
    HSD_JObj* jobj = obj;
    ufc_callback cb;
    Vec p;
    HSD_JObj* jp;
    struct _HSD_RObj* robj;
    Mtx mtx;

    if (jobj != NULL) {
        switch (type) {
        case HSD_A_J_PATH:
            if (val->fv < 0.0L) {
                val->fv = 0.0F;
            }
            if (1.0L < val->fv) {
                val->fv = 1.0F;
            }
            assert_line(0x24B, jobj->aobj);
            jp = (HSD_JObj*) jobj->aobj->hsd_obj;
            assert_line(0x24D, jp);
            assert_line(0x24E, jp->u.spline);
            splArcLengthPoint(&p, jp->u.spline, val->fv);
            HSD_JObjSetTranslateX(jobj, p.x);
            HSD_JObjSetTranslateY(jobj, p.y);
            HSD_JObjSetTranslateZ(jobj, p.z);
            break;
        case HSD_A_J_ROTX:
            if (jobj->flags & JOBJ_JOINT1) {
                robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    robj->u.ik_hint.rotate_x = val->fv;
                }
            }
            HSD_JObjSetRotationX(jobj, val->fv);
            break;
        case HSD_A_J_ROTY:
            HSD_JObjSetRotationY(jobj, val->fv);
            break;
        case HSD_A_J_ROTZ:
            HSD_JObjSetRotationZ(jobj, val->fv);
            break;
        case HSD_A_J_TRAX:
            HSD_JObjSetTranslateX(jobj, val->fv);
            break;
        case HSD_A_J_TRAY:
            HSD_JObjSetTranslateY(jobj, val->fv);
            break;
        case HSD_A_J_TRAZ:
            HSD_JObjSetTranslateZ(jobj, val->fv);
            break;
        case HSD_A_J_SCAX:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleX(jobj, val->fv);
            break;
        case HSD_A_J_SCAY:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleY(jobj, val->fv);
            break;
        case HSD_A_J_SCAZ:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleZ(jobj, val->fv);
            break;
        case HSD_A_J_BRANCH:
            if (val->fv > 0.5) {
                HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_NODE:
            if (val->fv > 0.5) {
                HSD_JObjClearFlags(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_SETBYTE0:
        case HSD_A_J_SETBYTE1:
        case HSD_A_J_SETBYTE2:
        case HSD_A_J_SETBYTE3:
        case HSD_A_J_SETBYTE4:
        case HSD_A_J_SETBYTE5:
        case HSD_A_J_SETBYTE6:
        case HSD_A_J_SETBYTE7:
        case HSD_A_J_SETBYTE8:
        case HSD_A_J_SETBYTE9: {
            HSD_SList* callback_node = ufc_callbacks;
            while (callback_node != NULL) {
                cb = callback_node->data;
                cb(jobj, type, val->iv);
                callback_node = callback_node->next;
            }
            break;
        }
        case HSD_A_J_SETFLOAT0:
        case HSD_A_J_SETFLOAT1:
        case HSD_A_J_SETFLOAT2:
        case HSD_A_J_SETFLOAT3:
        case HSD_A_J_SETFLOAT4:
        case HSD_A_J_SETFLOAT5:
        case HSD_A_J_SETFLOAT6:
        case HSD_A_J_SETFLOAT7:
        case HSD_A_J_SETFLOAT8:
        case HSD_A_J_SETFLOAT9: {
            HSD_SList* callback_node = ufc_callbacks;
            while (callback_node != NULL) {
                cb = callback_node->data;
                cb(jobj, type, val->fv);
                callback_node = callback_node->next;
            }
            break;
        }
        case 0x28: {
            s32 iv = val->iv;
            s32 lo = iv & 0x3F;
            s32 hi = iv >> 6 & 0xFFFFFF;
            if (dptcl_callback != NULL) {
                dptcl_callback(0, lo, hi, jobj);
            }
        } break;
        case 0x29:
            if (jsound_callback != NULL) {
                jsound_callback(val->iv);
            }
            break;
        case 0x2A:
            if (ptcltgt_callback != NULL) {
                ptcltgt_callback(jobj, val->iv);
            }
            break;
        case 0x32:
            jobj->mtx[0][0] = val->p.x;
            jobj->mtx[1][0] = val->p.y;
            jobj->mtx[2][0] = val->p.z;
            break;
        case 0x33:
            jobj->mtx[0][1] = val->p.x;
            jobj->mtx[1][1] = val->p.y;
            jobj->mtx[2][1] = val->p.z;
            break;
        case 0x34:
            jobj->mtx[0][2] = val->p.x;
            jobj->mtx[1][2] = val->p.y;
            jobj->mtx[2][2] = val->p.z;
            break;
        case 0x35:
            jobj->mtx[0][3] = val->p.x;
            jobj->mtx[1][3] = val->p.y;
            jobj->mtx[2][3] = val->p.z;
            break;
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
            if (jobj->parent != NULL) {
                HSD_MtxInverseConcat(jobj->parent->mtx, jobj->mtx, mtx);
            } else {
                PSMTXCopy(jobj->mtx, mtx);
            }
            if (type == 0x36 || type == 0x38) {
                HSD_MtxGetTranslate(mtx, &jobj->translate);
            }
            if (type == 0x36 || type == 0x37) {
                HSD_MtxGetRotation(mtx, (Vec*) &jobj->rotate);
            }
            if (type == 0x36 || type == 0x39) {
                HSD_MtxGetScale(mtx, &jobj->scale);
            }
            break;
        }
    }
}

void HSD_JObjAnim(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_JObjCheckDepend(jobj);
        HSD_AObjInterpretAnim(jobj->aobj, jobj, JObjUpdateFunc);
        HSD_RObjAnimAll(jobj->robj);
        if (union_type_dobj(jobj)) {
            HSD_DObjAnimAll(jobj->u.dobj);
        }
    }
}

void JObjAnimAll(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if (jobj != NULL) {
        HSD_JObjAnim(jobj);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            child = jobj->child;
            while (child != NULL) {
                JObjAnimAll(child);
                child = child->next;
            }
        }
    }
}

void HSD_JObjAnimAll(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_AObjInitEndCallBack();
        JObjAnimAll(jobj);
        HSD_AObjInvokeCallBacks();
    }
}

inline MtxPtr HSD_CObjGetViewMtx(HSD_CObj* cobj)
{
    return cobj->view_mtx;
}

void HSD_JObjDispAll(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    MtxPtr new_var = vmtx;
    if (jobj != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            if (!(jobj->flags & JOBJ_HIDDEN)) {
                Mtx mtx;
                MtxPtr tmp;
                u32 unused;
                HSD_CObj* cobj;
                HSD_JObjSetupMatrix(jobj);
                HSD_JObjSetupMatrix(jobj->child);
                PSMTXInverse(jobj->child->mtx, mtx);
                PSMTXConcat(jobj->mtx, mtx, mtx);
                cobj = HSD_CObjGetCurrent();
                assert_line(0x355, cobj);
                PSMTXConcat(HSD_CObjGetViewMtx(cobj), mtx, mtx);
                HSD_JObjDispAll(jobj->child, mtx, flags, rendermode);
            }
        } else {
            if (jobj->flags & (flags << 0x12)) {
                HSD_JObjDisp(jobj, new_var, flags, rendermode);
            }
            if (jobj->flags & (flags << 0x1C)) {
                HSD_JObj* child = jobj->child;
                while (child != NULL) {
                    HSD_JObjDispAll(child, new_var, flags, rendermode);
                    child = child->next;
                }
            }
        }
    }
}

void HSD_JObjSetDefaultClass(HSD_JObjInfo* info)
{
    if (info != NULL) {
        assert_line(0x3A5, hsdIsDescendantOf(info, &hsdJObj));
    }
    default_class = info;
}

inline HSD_JObj* JObjLoadJointSub(HSD_Joint* joint, HSD_JObj* parent)
{
    HSD_JObj* jobj;
    HSD_ClassInfo* info;
    if (joint == NULL) {
        return NULL;
    }
    if (joint->class_name == NULL || !(info = hsdSearchClassInfo(joint->class_name))) {
        jobj = HSD_JObjAlloc();
    } else {
        jobj = hsdNew(info);
        assert_line(0x3CC, jobj);
    }
    HSD_JOBJ_METHOD(jobj)->load(jobj, joint, parent);
    return jobj;
}

s32 JObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{
    if (!(joint->flags & JOBJ_INSTANCE)) {
        jobj->child = JObjLoadJointSub(joint->child, jobj);
    }
    jobj->next = JObjLoadJointSub(joint->next, parent);
    jobj->parent = parent;
    jobj->flags |= joint->flags;
    if (union_type_spline(jobj)) {
        jobj->u.spline = joint->u.spline;
    } else if (union_type_ptcl(jobj)) {
        HSD_SList* slist;
        jobj->u.ptcl = joint->u.ptcl;
        slist = joint->u.ptcl;
        while (slist != NULL) {
            *(u32*) &slist->data |= 0x80000000;
            slist = slist->next;
        }
    } else {
        jobj->u.dobj = HSD_DObjLoadDesc(joint->u.dobjdesc);
    }
    jobj->robj = HSD_RObjLoadDesc(joint->robjdesc);
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    PSMTXIdentity(jobj->mtx);
    jobj->scl = NULL;
    if (joint->mtx != NULL) {
        jobj->envelopemtx = HSD_MtxAlloc();
        memcpy(jobj->envelopemtx, joint->mtx, sizeof(Mtx));
    }
    HSD_IDInsertToTable(NULL, (u32) joint, jobj);
    jobj->id = (u32) joint;
    return 0;
}

HSD_JObj* HSD_JObjLoadJoint(HSD_Joint* arg0)
{
    HSD_JObj* jobj = JObjLoadJointSub(arg0, 0);
    HSD_JObjResolveRefsAll(jobj, arg0);
    return jobj;
}

#pragma push
#pragma force_active on
static char unused1[] = "jobj_root";
static char unused2[] = "jobj_root == NULL";
#pragma pop

static char jobj_child[] = "jobj->child";
char lbl_804068E4[] = "object.h";
inline void ref_INC(void* o)
{
    if (o != NULL) {
        HSD_OBJ(o)->ref_count++;
        if (!(HSD_OBJ(o)->ref_count != (u16) -1)) {
            __assert(lbl_804068E4, 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
        }
    }
}

void HSD_JObjResolveRefs(HSD_JObj* jobj, HSD_Joint* joint)
{
    u32 unused;
    if (jobj == NULL || joint == NULL) {
        return;
    }
    HSD_RObjResolveRefsAll(jobj->robj, joint->robjdesc);
    if (!!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObjUnref(jobj->child);
        jobj->child = HSD_IDGetDataFromTable(NULL, (u32) joint->child, NULL);
        if (jobj->child == NULL) {
            __assert(__FILE__, 0x454, jobj_child);
        }
        ref_INC(jobj->child);
    }
    if (union_type_dobj(jobj)) {
        HSD_DObjResolveRefsAll(jobj->u.dobj, joint->u.dobjdesc);
    }
}

void HSD_JObjResolveRefsAll(HSD_JObj* jobj, HSD_Joint* joint)
{
    u32 unused;
    while (jobj != NULL && joint != NULL) {
        HSD_JObjResolveRefs(jobj, joint);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObjResolveRefsAll(jobj->child, joint->child);
        }
        jobj = jobj->next;
        joint = joint->next;
    }
}

inline int iref_CNT(void* o)
{
    return HSD_OBJ(o)->ref_count_individual;
}

char lbl_80406918[] = "HSD_OBJ(o)->ref_count_individual != 0";
inline int iref_INC(void* o)
{
    HSD_OBJ(o)->ref_count_individual += 1;
    if (HSD_OBJ(o)->ref_count_individual == 0) {
        __assert(lbl_804068E4, 0x9E, lbl_80406918);
    }
}

inline int ref_CNT(void* o)
{
    if (HSD_OBJ(o)->ref_count == (u16) -1) {
        return -1;
    } else {
        return HSD_OBJ(o)->ref_count;
    }
}

inline BOOL ref_DEC(void* o)
{
    BOOL ret = (u64) (HSD_OBJ(o)->ref_count == (u16) -1);
    if (ret)
        return ret;
    return HSD_OBJ(o)->ref_count-- == 0;
}

inline BOOL iref_DEC(void* o)
{
    BOOL ret = (u64) (HSD_OBJ(o)->ref_count_individual == 0);
    if (ret)
        return ret;
    HSD_OBJ(o)->ref_count_individual -= 1;
    return HSD_OBJ(o)->ref_count_individual == 0;
}

inline BOOL iref_none(void* o)
{
    return HSD_OBJ(o)->ref_count_individual == 0;
}

// Alternate form to match HSD_JObjUnrefThis
// (Original version causes regswap)
// TODO merge with iref_DEC
inline BOOL iref_DEC_alt(void* o)
{
    BOOL ret = iref_none(o);
    if (ret)
        return ret;
    HSD_OBJ(o)->ref_count_individual -= 1;
    return HSD_OBJ(o)->ref_count_individual == 0;
}

void HSD_JObjUnref(HSD_JObj* jobj)
{
    if (jobj != NULL && ref_DEC(jobj)) {
        if (iref_CNT(jobj) - 1 < 0) {
            if (jobj != NULL) {
                jobj->object.parent.class_info->release((HSD_Class*) jobj);
                jobj->object.parent.class_info->destroy((HSD_Class*) jobj);
            }
        } else {
            iref_INC(jobj);
            HSD_JOBJ_METHOD(jobj)->release_child(jobj);
            if (iref_DEC(jobj)) {
                if (jobj != NULL) {
                    jobj->object.parent.class_info->release((HSD_Class*) jobj);
                    jobj->object.parent.class_info->destroy((HSD_Class*) jobj);
                }
            }
        }
    }
}

void HSD_JObjUnrefThis(HSD_JObj* jobj)
{
    if (jobj != NULL && iref_DEC_alt(jobj) && ref_CNT(jobj) < 0) {
        if (jobj != NULL) {
            jobj->object.parent.class_info->release((HSD_Class*) jobj);
            jobj->object.parent.class_info->destroy((HSD_Class*) jobj);
        }
    }
}

HSD_JObj* HSD_JObjGetPrev(HSD_JObj*);

HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj)
{
    HSD_JObj* child;
    HSD_JObj* next;
    HSD_JObj* prev;

    if (jobj == NULL) {
        return 0;
    }
    child = jobj->child;
    if (child != NULL) {
        assert_line(0x4C0, child->next == NULL);
    }

    next = child != NULL ? child : jobj->next;

    prev = HSD_JObjGetPrev(jobj);
    if (prev != NULL) {
        prev->next = next;
    } else if (jobj->parent != NULL) {
        jobj->parent->child = next;
    }
    if (next != NULL && next == child) {
        next->next = jobj->next;
        next->parent = jobj->parent;
    }
    jobj->parent = NULL;
    jobj->child = NULL;
    jobj->next = NULL;
    HSD_JObjUnref(jobj);
    return child;
}

// Regswaps
// https://decomp.me/scratch/D9q7a
#ifdef NON_MATCHING
void HSD_JObjRemoveAll(HSD_JObj* jobj)
{
    HSD_JObj* next;
    if (jobj == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        HSD_JObj* prev = HSD_JObjGetPrev(jobj);
        if (prev != NULL) {
            prev->next = NULL;
        } else {
            jobj->parent->child = NULL;
        }
    }
    while (jobj != NULL) {
        next = jobj->next;
        jobj->parent = NULL;
        jobj->next = NULL;
        HSD_JObjUnref(jobj);
        jobj = next;
    }
}
#else
#pragma push
asm void HSD_JObjRemoveAll()
{ // clang-format off
    nofralloc
/* 80371590 0036E170  7C 08 02 A6 */	mflr r0
/* 80371594 0036E174  90 01 00 04 */	stw r0, 4(r1)
/* 80371598 0036E178  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8037159C 0036E17C  BF 41 00 10 */	stmw r26, 0x10(r1)
/* 803715A0 0036E180  7C 7D 1B 79 */	or. r29, r3, r3
/* 803715A4 0036E184  41 82 01 98 */	beq lbl_8037173C
/* 803715A8 0036E188  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 803715AC 0036E18C  28 00 00 00 */	cmplwi r0, 0
/* 803715B0 0036E190  41 82 00 2C */	beq lbl_803715DC
/* 803715B4 0036E194  7F A3 EB 78 */	mr r3, r29
/* 803715B8 0036E198  48 00 05 A9 */	bl HSD_JObjGetPrev
/* 803715BC 0036E19C  28 03 00 00 */	cmplwi r3, 0
/* 803715C0 0036E1A0  41 82 00 10 */	beq lbl_803715D0
/* 803715C4 0036E1A4  38 00 00 00 */	li r0, 0
/* 803715C8 0036E1A8  90 03 00 08 */	stw r0, 8(r3)
/* 803715CC 0036E1AC  48 00 00 10 */	b lbl_803715DC
lbl_803715D0:
/* 803715D0 0036E1B0  80 7D 00 0C */	lwz r3, 0xc(r29)
/* 803715D4 0036E1B4  38 00 00 00 */	li r0, 0
/* 803715D8 0036E1B8  90 03 00 10 */	stw r0, 0x10(r3)
lbl_803715DC:
/* 803715DC 0036E1BC  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 803715E0 0036E1C0  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 803715E4 0036E1C4  3C 80 80 40 */	lis r4, lbl_804068E4@ha
/* 803715E8 0036E1C8  3C 60 80 40 */	lis r3, lbl_80406918@ha
/* 803715EC 0036E1CC  3B 64 68 E4 */	addi r27, r4, lbl_804068E4@l
/* 803715F0 0036E1D0  3B 83 69 18 */	addi r28, r3, lbl_80406918@l
/* 803715F4 0036E1D4  54 1F 04 3E */	clrlwi r31, r0, 0x10
/* 803715F8 0036E1D8  48 00 01 3C */	b lbl_80371734
lbl_803715FC:
/* 803715FC 0036E1DC  83 DD 00 08 */	lwz r30, 8(r29)
/* 80371600 0036E1E0  38 00 00 00 */	li r0, 0
/* 80371604 0036E1E4  28 1D 00 00 */	cmplwi r29, 0
/* 80371608 0036E1E8  90 1D 00 0C */	stw r0, 0xc(r29)
/* 8037160C 0036E1EC  90 1D 00 08 */	stw r0, 8(r29)
/* 80371610 0036E1F0  41 82 01 20 */	beq lbl_80371730
/* 80371614 0036E1F4  A0 9D 00 04 */	lhz r4, 4(r29)
/* 80371618 0036E1F8  38 BD 00 04 */	addi r5, r29, 4
/* 8037161C 0036E1FC  7C 04 F8 50 */	subf r0, r4, r31
/* 80371620 0036E200  7C 00 00 34 */	cntlzw r0, r0
/* 80371624 0036E204  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 80371628 0036E208  41 82 00 08 */	beq lbl_80371630
/* 8037162C 0036E20C  48 00 00 18 */	b lbl_80371644
lbl_80371630:
/* 80371630 0036E210  38 64 FF FF */	addi r3, r4, -1
/* 80371634 0036E214  7C 04 00 D0 */	neg r0, r4
/* 80371638 0036E218  B0 65 00 00 */	sth r3, 0(r5)
/* 8037163C 0036E21C  7C 00 00 34 */	cntlzw r0, r0
/* 80371640 0036E220  54 00 D9 7E */	srwi r0, r0, 5
lbl_80371644:
/* 80371644 0036E224  2C 00 00 00 */	cmpwi r0, 0
/* 80371648 0036E228  41 82 00 E8 */	beq lbl_80371730
/* 8037164C 0036E22C  3B 5D 00 06 */	addi r26, r29, 6
/* 80371650 0036E230  A0 7D 00 06 */	lhz r3, 6(r29)
/* 80371654 0036E234  34 03 FF FF */	addic. r0, r3, -1
/* 80371658 0036E238  40 80 00 38 */	bge lbl_80371690
/* 8037165C 0036E23C  28 1D 00 00 */	cmplwi r29, 0
/* 80371660 0036E240  41 82 00 D0 */	beq lbl_80371730
/* 80371664 0036E244  80 9D 00 00 */	lwz r4, 0(r29)
/* 80371668 0036E248  7F A3 EB 78 */	mr r3, r29
/* 8037166C 0036E24C  81 84 00 30 */	lwz r12, 0x30(r4)
/* 80371670 0036E250  7D 88 03 A6 */	mtlr r12
/* 80371674 0036E254  4E 80 00 21 */	blrl 
/* 80371678 0036E258  80 9D 00 00 */	lwz r4, 0(r29)
/* 8037167C 0036E25C  7F A3 EB 78 */	mr r3, r29
/* 80371680 0036E260  81 84 00 34 */	lwz r12, 0x34(r4)
/* 80371684 0036E264  7D 88 03 A6 */	mtlr r12
/* 80371688 0036E268  4E 80 00 21 */	blrl 
/* 8037168C 0036E26C  48 00 00 A4 */	b lbl_80371730
lbl_80371690:
/* 80371690 0036E270  38 03 00 01 */	addi r0, r3, 1
/* 80371694 0036E274  B0 1A 00 00 */	sth r0, 0(r26)
/* 80371698 0036E278  A0 1A 00 00 */	lhz r0, 0(r26)
/* 8037169C 0036E27C  28 00 00 00 */	cmplwi r0, 0
/* 803716A0 0036E280  40 82 00 14 */	bne lbl_803716B4
/* 803716A4 0036E284  38 7B 00 00 */	addi r3, r27, 0
/* 803716A8 0036E288  38 BC 00 00 */	addi r5, r28, 0
/* 803716AC 0036E28C  38 80 00 9E */	li r4, 0x9e
/* 803716B0 0036E290  48 01 6B 71 */	bl __assert
lbl_803716B4:
/* 803716B4 0036E294  80 9D 00 00 */	lwz r4, 0(r29)
/* 803716B8 0036E298  7F A3 EB 78 */	mr r3, r29
/* 803716BC 0036E29C  81 84 00 4C */	lwz r12, 0x4c(r4)
/* 803716C0 0036E2A0  7D 88 03 A6 */	mtlr r12
/* 803716C4 0036E2A4  4E 80 00 21 */	blrl 
/* 803716C8 0036E2A8  A0 7A 00 00 */	lhz r3, 0(r26)
/* 803716CC 0036E2AC  7C 03 00 D0 */	neg r0, r3
/* 803716D0 0036E2B0  7C 00 00 34 */	cntlzw r0, r0
/* 803716D4 0036E2B4  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 803716D8 0036E2B8  41 82 00 08 */	beq lbl_803716E0
/* 803716DC 0036E2BC  48 00 00 1C */	b lbl_803716F8
lbl_803716E0:
/* 803716E0 0036E2C0  38 03 FF FF */	addi r0, r3, -1
/* 803716E4 0036E2C4  B0 1A 00 00 */	sth r0, 0(r26)
/* 803716E8 0036E2C8  A0 1A 00 00 */	lhz r0, 0(r26)
/* 803716EC 0036E2CC  7C 00 00 D0 */	neg r0, r0
/* 803716F0 0036E2D0  7C 00 00 34 */	cntlzw r0, r0
/* 803716F4 0036E2D4  54 00 D9 7E */	srwi r0, r0, 5
lbl_803716F8:
/* 803716F8 0036E2D8  2C 00 00 00 */	cmpwi r0, 0
/* 803716FC 0036E2DC  41 82 00 34 */	beq lbl_80371730
/* 80371700 0036E2E0  28 1D 00 00 */	cmplwi r29, 0
/* 80371704 0036E2E4  41 82 00 2C */	beq lbl_80371730
/* 80371708 0036E2E8  80 9D 00 00 */	lwz r4, 0(r29)
/* 8037170C 0036E2EC  7F A3 EB 78 */	mr r3, r29
/* 80371710 0036E2F0  81 84 00 30 */	lwz r12, 0x30(r4)
/* 80371714 0036E2F4  7D 88 03 A6 */	mtlr r12
/* 80371718 0036E2F8  4E 80 00 21 */	blrl 
/* 8037171C 0036E2FC  80 9D 00 00 */	lwz r4, 0(r29)
/* 80371720 0036E300  7F A3 EB 78 */	mr r3, r29
/* 80371724 0036E304  81 84 00 34 */	lwz r12, 0x34(r4)
/* 80371728 0036E308  7D 88 03 A6 */	mtlr r12
/* 8037172C 0036E30C  4E 80 00 21 */	blrl 
lbl_80371730:
/* 80371730 0036E310  7F DD F3 78 */	mr r29, r30
lbl_80371734:
/* 80371734 0036E314  28 1D 00 00 */	cmplwi r29, 0
/* 80371738 0036E318  40 82 FE C4 */	bne lbl_803715FC
lbl_8037173C:
/* 8037173C 0036E31C  BB 41 00 10 */	lmw r26, 0x10(r1)
/* 80371740 0036E320  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80371744 0036E324  38 21 00 28 */	addi r1, r1, 0x28
/* 80371748 0036E328  7C 08 03 A6 */	mtlr r0
/* 8037174C 0036E32C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
#endif

void RecalcParentTrspBits(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        HSD_JObj* child = jobj->child;
        u32 flags = ~JOBJ_ROOT_MASK;
        while (child != NULL) {
            flags |= (child->flags | child->flags << 10) & JOBJ_ROOT_MASK;
            child = child->next;
        }
        if (!(jobj->flags & ~flags)) {
            break;
        }
        jobj->flags &= flags;
        jobj = jobj->next;
    }
}

static void UpdateParentTrspBits(HSD_JObj* jobj, HSD_JObj* child)
{
    u32 flags = (child->flags | (child->flags << 10)) & JOBJ_ROOT_MASK;
    while (jobj != NULL) {
        if (!(flags & ~jobj->flags))
            break;
        jobj->flags |= flags;
        jobj = jobj->parent;
    }
}

void HSD_JObjAddChild(HSD_JObj* jobj, HSD_JObj* child)
{
    HSD_JObj* last;

    if (jobj == NULL || child == NULL) {
        return;
    }
    if (child->parent != NULL) {
        OSReport("child should be a orphan.\n");
        __assert(__FILE__, 0x546, "child->parent == NULL");
    }
    if (child->next != NULL) {
        OSReport("child should not have siblings");
        __assert(__FILE__, 0x547, "child->next == NULL");
    }
    if (jobj->child == NULL) {
        jobj->child = child;
    } else {
        assert_line(0x54D, !(jobj->flags & JOBJ_INSTANCE));
        last = jobj->child;
        while (last->next != NULL) {
            assert_line(0x550, last != child);
            last = last->next;
        }
        last->next = child;
    }
    child->parent = jobj;
    UpdateParentTrspBits(jobj, child);
}

HSD_JObj* HSD_JObjReparent(HSD_JObj* jobj, HSD_JObj* parent)
{
    HSD_JObj* next;

    if (jobj == NULL) {
        return NULL;
    }
    next = jobj->next;
    if (jobj->parent != NULL) {
        if (jobj->parent->child == jobj) {
            jobj->parent->child = next;
        } else {
            HSD_JObj* prev = HSD_JObjGetPrev(jobj);
            assert_line(0x56F, prev);
            prev->next = next;
        }
        RecalcParentTrspBits(jobj->parent);
        jobj->parent = NULL;
    }
    jobj->next = NULL;
    HSD_JObjAddChild(parent, jobj);
    return next;
}

void HSD_JObjAddNext(HSD_JObj* jobj, HSD_JObj* next)
{
    HSD_JObj* cur;

    if (jobj == NULL || next == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        cur = jobj->parent->child;
        jobj->parent->child = NULL;
        jobj->flags &= ~JOBJ_ROOT_MASK;
    } else {
        cur = jobj;
    }
    HSD_JObjReparent(next, jobj->parent);
    if (next->child != NULL) {
        HSD_JObj* child = next->child;
        while (child->next != NULL) {
            child = child->next;
        }
        child->next = cur;
    } else {
        next->child = cur;
    }
    while (cur != NULL) {
        cur->parent = next;
        UpdateParentTrspBits(next, cur);
        cur = cur->next;
    }
}

HSD_JObj* HSD_JObjGetPrev(HSD_JObj* jobj)
{
    HSD_JObj* cur;

    if (jobj == NULL || jobj->parent == NULL) {
        return NULL;
    }
    if (jobj == jobj->parent->child) {
        return NULL;
    }
    cur = jobj->parent->child;
    while (cur != NULL) {
        if (cur->next == jobj) {
            return cur;
        }
        cur = cur->next;
    }
    HSD_Panic(__FILE__, 0x5EC, "can not find specified jobj. maybe jobj tree is broken.\n");
    return NULL;
}

HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj)
{
    if (jobj == NULL || !union_type_dobj(jobj)) {
        return NULL;
    }
    return jobj->u.dobj;
}

void HSD_JObjAddDObj(HSD_JObj* jobj, HSD_DObj* dobj)
{
    if (jobj == NULL || dobj == NULL || !union_type_dobj(jobj)) {
        return;
    }
    dobj->next = jobj->u.dobj;
    jobj->u.dobj = dobj;
}

inline HSD_RObj* robj_set_next(HSD_RObj* robj, HSD_RObj* next)
{
    if (robj == NULL) {
        return next;
    }
    robj->next = next;
    return robj;
}

void HSD_JObjPrependRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    jobj->robj = robj_set_next(robj, jobj->robj);
}

void HSD_JObjDeleteRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    if (robj != NULL) {
        HSD_RObj** cur_ptr = &jobj->robj;
        HSD_RObj* cur;
        while (*cur_ptr != NULL) {
            cur = *cur_ptr;
            if (cur == robj) {
                *cur_ptr = cur->next;
                robj->next = NULL;
                return;
            }
            cur_ptr = &cur->next;
        }
    }
}

u32 HSD_JObjGetFlags(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        return jobj->flags;
    }
    return 0;
}

void HSD_JObjSetFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ flags) & JOBJ_CLASSICAL_SCALE) {
            // manually inlined HSD_JObjSetMtxDirty
            if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
        jobj->flags |= flags;
    }
}

void HSD_JObjSetFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjSetFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjSetFlagsAll(i, flags);
            }
        }
    }
}

void HSD_JObjClearFlags(HSD_JObj* jobj, u32 arg1)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ arg1) & JOBJ_CLASSICAL_SCALE) {
            // manually inlined HSD_JObjSetMtxDirty
            if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
        jobj->flags &= ~arg1;
    }
}

void HSD_JObjClearFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjClearFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjClearFlagsAll(i, flags);
            }
        }
    }
}

HSD_JObj* HSD_JObjAlloc(void)
{
    HSD_JObj* jobj = hsdNew((HSD_ClassInfo*) (default_class != NULL ? default_class : &hsdJObj));
    assert_line(0x7D3, jobj);
    return jobj;
}

void HSD_JObjSetCurrent(HSD_JObj* jobj)
{
    ref_INC(jobj);
    HSD_JObjUnref(current_jobj);
    current_jobj = jobj;
}

HSD_JObj* HSD_JObjGetCurrent(void)
{
    return current_jobj;
}

inline HSD_JObj* jobj_get_joint2(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

inline HSD_JObj* jobj_get_effector(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

// Note: this must not be declared inline, so that
// the "eff" assertion string data is placed before "robj".
HSD_JObj* jobj_get_effector_checked(HSD_JObj* eff)
{
    eff = jobj_get_effector(eff);
    assert_line(0x824, eff);
    if (HSD_RObjGetByType(eff->robj, REFTYPE_JOBJ, 1) != NULL) {
        return eff;
    } else {
        return NULL;
    }
}

extern const Vec lbl_803B94C4;

void resolveIKJoint1(HSD_JObj* jobj)
{
    HSD_JObj* robj_4;
    HSD_JObj* var_r28;
    HSD_JObj* var_r31;
    Vec* temp_r4;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f5;
    f32 temp_f5_2;
    Vec spBC = { 1.0F, 1.0F, 1.0F };
    f32 var_f1;
    f32 var_f29;
    f32 var_f29_2;
    f32 var_f28;
    f32 var_f27;
    f32 temp_f26;
    f32 var_f4;
    f32 var_f4_2;
    Vec spB0;
    f32 tmp;
    f32 var_f4_3;
    f32 var_f4_4;
    f32 var_f5;
    s32 var_r30;
    HSD_RObj* robj;
    Vec sp98;
    Vec sp8C;
    Vec sp80;
    struct _HSD_IKHint* new_var;
    Vec sp74;
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Mtx sp20;

    var_r30 = 0;
    var_f29 = 0.0F;
    var_r31 = jobj_get_joint2(jobj->child);
    spB0 = lbl_803B94C4;
    temp_r4 = jobj->scl;
    var_f5 = 1e-8F;
    if (temp_r4 != NULL) {
        spBC = *temp_r4;
    }
    robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
    assert_line(0x853, robj);
    new_var = &robj->u.ik_hint;
    temp_f26 = new_var->rotate_x;
    temp_f30 = new_var->bone_length * spBC.x;
    if (var_r31 != NULL) {
        robj = HSD_RObjGetByType(var_r31->robj, REFTYPE_IKHINT, 0);
        assert_line(0x85E, robj);
        var_f29 = robj->u.ik_hint.bone_length * var_r31->scale.x * spBC.x;
        var_r30 = robj->flags & 4 ? 1 : 0;
        var_r28 = jobj_get_effector_checked(var_r31->child);
    } else {
        var_r28 = jobj_get_effector_checked(jobj->child);
    }
    if (var_r28 != NULL) {
        if ((HSD_RObjGetByType(jobj->robj, REFTYPE_JOBJ, 3) == NULL) && (jobj != NULL)) {
            if (jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, JObjUpdateFunc);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= 0xFFFFFFBF;
                }
            }
        }
        robj_4 = jobj->parent;
        if (robj_4 != NULL) {
            HSD_MtxGetTranslate(robj_4->mtx, &spB0);
        }
        HSD_RObjGetGlobalPosition(var_r28->robj, 1, &var_r28->translate);
        PSVECSubtract(&var_r28->translate, &spB0, &sp8C);
        temp_f31 = PSVECDotProduct(&sp8C, &sp8C);
        if (temp_f31 > var_f5) {
            sp68 = sp8C;
            if (HSD_RObjGetGlobalPosition(jobj->robj, 3, &sp5C) != 0) {
                PSVECSubtract(&sp5C, &spB0, &sp5C);
                if (temp_f26 != 0.0F) {
                    PSMTXRotAxisRad(sp20, &sp68, temp_f26);
                    PSMTXMUltiVec(sp20, &sp5C, &sp5C);
                }
                PSVECCrossProduct(&sp68, &sp5C, &sp50);
                PSVECCrossProduct(&sp50, &sp68, &sp5C);
            } else {
                sp50.x = jobj->mtx[0][2];
                sp50.y = jobj->mtx[1][2];
                sp50.z = jobj->mtx[2][2];
                PSVECCrossProduct(&sp50, &sp68, &sp5C);
                PSVECCrossProduct(&sp68, &sp5C, &sp50);
            }
            var_f4 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp50, &sp50)));
            PSVECScale(&sp50, &sp80, var_f4);
            var_f4_2 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp5C, &sp5C)));
            PSVECScale(&sp5C, &sp74, var_f4_2);
            temp_f5 = temp_f30 * temp_f30;
            var_f28 = var_f29 * var_f29;
            temp_f1_7 = temp_f5 - var_f28;
            temp_f1_8 = 0.25F * (((2.0F * (temp_f5 + var_f28)) - temp_f31) - ((temp_f1_7 * temp_f1_7) / temp_f31));
            var_f27 = temp_f1_8;
            if (temp_f1_8 < 0.0F) {
                var_f27 = 0.0F;
            }
            temp_f5_2 = (temp_f5 - var_f27) / temp_f31;
            var_f4_3 = sqrtf(1.0F / (1e-10F + temp_f5_2));
            var_f1 = temp_f5_2 * var_f4_3;
            var_f5 = sqrtf(1.0F / (1e-10F + var_f27));
            var_f29_2 = var_f27 * var_f5;
        } else {
            var_f1 = 0.0F;
            var_f29_2 = temp_f30;
        }
        if (var_r30 != 0) {
            var_f29_2 = -var_f29_2;
        }
        if ((var_f28 - var_f27) < temp_f31) {
            PSVECScale(&sp8C, &sp98, var_f1);
        } else {
            PSVECScale(&sp8C, &sp98, -var_f1);
        }
        PSVECScale(&sp74, &sp5C, var_f29_2);
        PSVECAdd(&sp98, &sp5C, &sp98);
        var_f4_4 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp98, &sp98)));
        PSVECScale(&sp98, &sp98, var_f4_4);
        jobj->mtx[0][0] = sp98.x * spBC.x;
        jobj->mtx[1][0] = sp98.y * spBC.x;
        jobj->mtx[2][0] = sp98.z * spBC.x;
        PSVECCrossProduct(&sp80, &sp98, &sp5C);
        jobj->mtx[0][1] = sp5C.x * spBC.y;
        jobj->mtx[1][1] = sp5C.y * spBC.y;
        jobj->mtx[2][1] = sp5C.z * spBC.y;
        jobj->mtx[0][2] = sp80.x * spBC.z;
        jobj->mtx[1][2] = sp80.y * spBC.z;
        jobj->mtx[2][2] = sp80.z * spBC.z;
        jobj->mtx[0][3] = spB0.x;
        jobj->mtx[1][3] = spB0.y;
        jobj->mtx[2][3] = spB0.z;
    }
}

const Vec lbl_803B94C4 = { 0.0F, 0.0F, 0.0F };
const Vec lbl_803B94D0 = { 1.0F, 1.0F, 1.0F };

void resolveIKJoint2(HSD_JObj* jobj)
{
    Vec spA0;
    Vec sp94;
    Vec sp88;
    Vec sp7C;
    Vec sp70;
    Vec sp64;
    Mtx sp34;
    Vec sp28;
    Vec sp1C;
    HSD_JObj* temp_r5;
    HSD_JObj* var_r29;
    f32 temp_f1_4;
    f32 var_f1_2;
    f32 var_f31;
    f32 var_f4;
    f32 var_f4_2;
    s32 var_r27;
    s32 var_r30;
    HSD_RObj* temp_r28;
    HSD_RObj* temp_r29;
    HSD_RObj* robj;

    var_f31 = 1.0F;
    spA0 = lbl_803B94D0;
    var_r29 = jobj_get_effector_checked(jobj->child);
    if (var_r29 == NULL || jobj->parent == NULL) {
        return;
    }
    if (jobj->scl != NULL) {
        spA0 = *jobj->scl;
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        sp88.x = mtx[0][3];
        sp88.y = mtx[1][3];
        sp88.z = mtx[2][3];
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        sp7C.x = mtx[0][0];
        sp7C.y = mtx[1][0];
        sp7C.z = mtx[2][0];
    }
    var_f4 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp7C, &sp7C)));
    PSVECScale(&sp7C, &sp7C, var_f4);
    if (jobj->parent->scl != NULL) {
        var_f31 = jobj->parent->scl->x;
    }
    robj = HSD_RObjGetByType(jobj->parent->robj, REFTYPE_IKHINT, 0);
    assert_line(0x8FC, robj);
    PSVECScale(&sp7C, &sp7C, robj->u.ik_hint.bone_length * var_f31);
    PSVECAdd(&sp88, &sp7C, &sp94);
    PSVECSubtract(&var_r29->translate, &sp94, &sp7C);
    PSVECScale(&sp7C, &sp7C, sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp7C, &sp7C))));
    temp_r28 = HSD_RObjGetByType(jobj->robj, 0x20000000, 5);
    temp_r29 = HSD_RObjGetByType(jobj->robj, 0x20000000, 6);
    if ((temp_r28 != NULL) || (temp_r29 != NULL)) {
        var_r27 = 0;
        robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
        assert_line(0x91E, robj);
        var_r30 = robj->flags & 4 ? 1 : 0;
        {
            MtxPtr mtx = jobj->parent->mtx;
            sp28.x = mtx[0][0];
            sp28.y = mtx[1][0];
            sp28.z = mtx[2][0];
        }
        PSVECNormalize(&sp28, &sp28);
        temp_f1_4 = PSVECDotProduct(&sp28, &sp7C);
        if (temp_f1_4 >= 1.0F) {
            var_f1_2 = 0.0F;
        } else if (temp_f1_4 <= -1.0F) {
            var_f1_2 = M_PI;
        } else {
            var_f1_2 = acosf(temp_f1_4);
        }
        if (var_r30 == 0) {
            var_f1_2 = -var_f1_2;
        }
        if (temp_r28 != NULL && var_f1_2 < temp_r28->u.limit) {
            var_f1_2 = temp_r28->u.limit;
            var_r27 = 1;
        } else if (temp_r29 != NULL) {
            if (temp_r29->u.limit < var_f1_2) {
                var_f1_2 = temp_r29->u.limit;
                var_r27 = 1;
            }
        }
        if (var_r27 != 0) {
            {
                MtxPtr mtx = jobj->parent->mtx;
                sp1C.x = mtx[0][2];
                sp1C.y = mtx[1][2];
                sp1C.z = mtx[2][2];
            }
            PSMTXRotAxisRad(sp34, &sp1C, var_f1_2);
            PSMTXMUltiVec(sp34, &sp28, &sp7C);
        }
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        sp64.x = mtx[0][2];
        sp64.y = mtx[1][2];
        sp64.z = mtx[2][2];
    }
    PSVECCrossProduct(&sp64, &sp7C, &sp70);
    var_f4_2 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp70, &sp70)));
    PSVECScale(&sp70, &sp70, var_f4_2);
    PSVECCrossProduct(&sp7C, &sp70, &sp64);
    jobj->mtx[0][0] = sp7C.x * spA0.x;
    jobj->mtx[1][0] = sp7C.y * spA0.x;
    jobj->mtx[2][0] = sp7C.z * spA0.x;
    jobj->mtx[0][1] = sp70.x * spA0.y;
    jobj->mtx[1][1] = sp70.y * spA0.y;
    jobj->mtx[2][1] = sp70.z * spA0.y;
    jobj->mtx[0][2] = sp64.x * spA0.z;
    jobj->mtx[1][2] = sp64.y * spA0.z;
    jobj->mtx[2][2] = sp64.z * spA0.z;
    jobj->mtx[0][3] = sp94.x;
    jobj->mtx[1][3] = sp94.y;
    jobj->mtx[2][3] = sp94.z;
}

void HSD_JObjSetupMatrixSub(HSD_JObj* jobj)
{
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    HSD_JObj* parent;
    HSD_RObj* robj;
    f32 x_scale;

    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
    jobj->flags &= 0xFFFFFFBF;
    if (!(jobj->flags & 0x800000)) {
        switch (jobj->flags & 0x600000) {
        case 0x200000:
            resolveIKJoint1(jobj);
            break;
        case 0x400000:
            resolveIKJoint2(jobj);
            break;
        case 0x600000:
            parent = jobj->parent;
            x_scale = 1.0F;
            if (parent != NULL) {
                robj = HSD_RObjGetByType(parent->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    sp1C.x = parent->mtx[0][3];
                    sp1C.y = parent->mtx[1][3];
                    sp1C.z = parent->mtx[2][3];
                    sp10.x = parent->mtx[0][0];
                    sp10.y = parent->mtx[1][0];
                    sp10.z = parent->mtx[2][0];
                    PSVECScale(&sp10, &sp10, sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp10, &sp10))));
                    if (parent->scl != NULL) {
                        x_scale = parent->scl->x;
                    }
                    PSVECScale(&sp10, &sp10, robj->u.ik_hint.bone_length * x_scale);
                    PSVECAdd(&sp1C, &sp10, &sp28);
                    jobj->mtx[0][3] = sp28.x;
                    jobj->mtx[1][3] = sp28.y;
                    jobj->mtx[2][3] = sp28.z;
                }
            }
            break;
        default:
            if (jobj->robj != NULL && jobj != NULL && jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, JObjUpdateFunc);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= 0xFFFFFFBF;
                }
            }
            break;
        }
        jobj->flags &= 0xFFFFFFBF;
    }
}

void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj)
{
    jobj->flags |= 0x40;
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            if (!(child->flags & JOBJ_MTX_INDEP_PARENT)) {
                if (!HSD_JObjMtxIsDirty(child)) {
                    HSD_JObjSetMtxDirtySub(child);
                }
            }
            child = child->next;
        }
    }
}

void HSD_JObjSetDPtclCallback(void (*cb)(s32, s32, s32, HSD_JObj*))
{
    dptcl_callback = cb;
}

int JObjInit(HSD_Class* o)
{
    int status = HSD_OBJECT_PARENT_INFO(&hsdJObj)->init(o);
    if (status >= 0) {
        HSD_JObj* jobj = (HSD_JObj*) o;
        status = 0;
        jobj->flags = JOBJ_MTX_DIRTY;
        jobj->scale.x = 1.0F;
        jobj->scale.y = 1.0F;
        jobj->scale.z = 1.0F;
    }
    return status;
}

void JObjReleaseChild(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if ((child = jobj->child) != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            HSD_JObjUnref(child);
        } else {
            child->parent = NULL;
            HSD_JObjRemoveAll(jobj->child);
        }
        jobj->child = NULL;
    }
    if (jobj->parent != NULL) {
        HSD_JObjReparent(jobj, NULL);
    }
    if (union_type_dobj(jobj)) {
        if (jobj->u.dobj != NULL) {
            HSD_DObjRemoveAll(jobj->u.dobj);
            jobj->u.dobj = NULL;
        }
    }
    if (jobj->robj != NULL) {
        HSD_RObjRemoveAll(jobj->robj);
        jobj->robj = NULL;
    }
    if (jobj->aobj != NULL) {
        HSD_AObjRemove(jobj->aobj);
        jobj->aobj = NULL;
    }
}

void JObjRelease(HSD_Class* o)
{
    HSD_JObj* jobj = (HSD_JObj*) o;
    HSD_JOBJ_METHOD(jobj)->release_child(jobj);

    if (HSD_IDGetDataFromTable(NULL, jobj->id, NULL) == jobj) {
        u32 id = jobj->id;
        HSD_IDRemoveByIDFromTable(NULL, id);
    }
    if (jobj->scl != NULL) {
        HSD_VecFree(jobj->scl);
    }
    if (jobj->envelopemtx != NULL) {
        HSD_MtxFree(jobj->envelopemtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdJObj)->release(o);
}

void JObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdJObj)) {
        ufc_callbacks = NULL;
        current_jobj = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdJObj)->amnesia(info);
}

#pragma push
#pragma force_active on
static char unused3[] = "jobj[%d,%d]";
static char unused4[] = "SKELETON_ROOT ";
static char unused5[] = "SKELETON ";
static char unused6[] = "ENVELOPE_MODEL ";
static char unused7[] = "EFFECTOR ";
static char unused8[] = "  rot(L): ";
static char unused9[] = "  sca(L): ";
static char unused10[] = "  tra(L): ";
static char unused11[] = "  rot(G): ";
static char unused12[] = "  sca(G): ";
static char unused13[] = "  tra(G): ";
#pragma pop

void HSD_JObjDispSub(HSD_JObj* jobj, MtxPtr vmtx, MtxPtr pmtx, u32 trsp_mask, u32 rendermode);
void HSD_JObjMakeMatrix(HSD_JObj* jobj);
void HSD_JObjMakePositionMtx(HSD_JObj* jobj, MtxPtr mtx, MtxPtr rmtx);

void JObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdJObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_jobj", sizeof(HSD_JObjInfo),
                     sizeof(HSD_JObj));
    HSD_CLASS_INFO(&hsdJObj)->init = JObjInit;
    HSD_CLASS_INFO(&hsdJObj)->release = JObjRelease;
    HSD_CLASS_INFO(&hsdJObj)->amnesia = JObjAmnesia;
    HSD_JOBJ_INFO(&hsdJObj)->make_mtx = HSD_JObjMakeMatrix;
    HSD_JOBJ_INFO(&hsdJObj)->make_pmtx = HSD_JObjMakePositionMtx;
    HSD_JOBJ_INFO(&hsdJObj)->disp = HSD_JObjDispSub;
    HSD_JOBJ_INFO(&hsdJObj)->load = JObjLoad;
    HSD_JOBJ_INFO(&hsdJObj)->release_child = JObjReleaseChild;
}

#pragma push
#pragma force_active on
static u32 unused14[6] = { 0 };
#pragma pop
