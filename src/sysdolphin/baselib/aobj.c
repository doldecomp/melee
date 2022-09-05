#include <stdarg.h>
#include <string.h>

#include <sysdolphin/baselib/aobj.h>

#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/robj.h>
#include <sysdolphin/baselib/tobj.h>

HSD_ObjAllocData aobj_alloc_data;

static char lbl_804D5D08[7] = "aobj.c\0";
static char lbl_804D5D10[4] = "new\0";
static char lbl_804D5D14[4] = "obj\0";

char lbl_80405FB8[9] = "object.h\0";
char lbl_80405FC4[39] = "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF\0";
extern s32 lbl_8040601C;
extern s32 lbl_8040603C;
extern void* jtbl_80406058;
extern void* jtbl_8040608C;

static HSD_SList* endcallback_list;

static s32 lbl_804D762C;
static s32 lbl_804D7630;

void HSD_AObjInitAllocData(void)
{
    HSD_ObjAllocInit(&aobj_alloc_data, sizeof(HSD_AObj), 4);
}

HSD_ObjAllocData* HSD_AObjGetAllocData(void)
{
    return &aobj_alloc_data;
}

u32 HSD_AObjGetFlags(HSD_AObj* aobj)
{
    return (aobj) ? aobj->flags : 0;
}

void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags |= flags;
    }
}

void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags &= ~flags;
    }
}

void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj)
{
    if (!aobj)
        return;

    if (aobj->fobj)
        HSD_FObjRemoveAll(aobj->fobj);
    aobj->fobj = fobj;
}

void HSD_AObjInitEndCallBack(void)
{
    lbl_804D762C = 0;
    lbl_804D7630 = 0;
}

void HSD_AObjInvokeCallBacks(void)
{
    HSD_SList* list;

    if (lbl_804D762C != 0 && lbl_804D7630 == 0) {
        list = endcallback_list;
        while (list) {
            void (*func)(void) = list->data;
            (*func)();
            list = list->next;
        }
    }
}

void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame)
{
    u32 flags;

    if (!aobj)
        return;

    aobj->curr_frame = frame;

    flags = aobj->flags & 0xBFFFFFFF;
    aobj->flags = flags | AOBJ_FIRST_PLAY;

    HSD_FObjReqAnimAll(aobj->fobj, frame);
}

void HSD_AObjStopAnim(HSD_AObj* aobj, void* obj, void (*func)())
{
    if (!aobj)
        return;

    HSD_FObjStopAnimAll(aobj->fobj, obj, func, aobj->framerate);
    aobj->flags |= AOBJ_NO_ANIM;
}

void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj, void (*update_func)())
{
    f32 rate = 0;

    if (!aobj || aobj->flags & AOBJ_NO_ANIM)
        return;

    if (aobj->flags & AOBJ_FIRST_PLAY) {
        aobj->flags &= 0xF7FFFFFF;
        rate = 0.0F;
    } else {
        rate = aobj->framerate;
        aobj->curr_frame += aobj->framerate;
    }

    if ((aobj->flags & AOBJ_LOOP) && aobj->end_frame <= aobj->curr_frame) {
        if (aobj->rewind_frame < aobj->end_frame) {
            f32 x, y;

            HSD_FObjStopAnimAll(aobj->fobj, obj, update_func, rate);
            y = aobj->end_frame - aobj->rewind_frame;
            x = aobj->curr_frame - aobj->rewind_frame;
            aobj->curr_frame = fmod(x, y) + aobj->rewind_frame;
            HSD_FObjReqAnimAll(aobj->fobj, aobj->curr_frame);
        } else {
            aobj->curr_frame = aobj->end_frame;
        }
        rate = 0.0F;
        aobj->flags |= AOBJ_REWINDED;
    } else {
        aobj->flags &= 0xFBFFFFFF;
    }

    if (aobj->flags & AOBJ_NO_UPDATE) {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, NULL, rate);
    } else {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, update_func, rate);
    }

    if (!(aobj->flags & AOBJ_LOOP) && (aobj->end_frame <= aobj->curr_frame) && aobj) {
        HSD_FObjStopAnimAll(aobj->fobj, obj, update_func, aobj->framerate);
        aobj->flags |= AOBJ_NO_ANIM;
    }

    if (aobj->flags & AOBJ_NO_ANIM) {
        lbl_804D762C += 1;
    } else {
        lbl_804D7630 += 1;
    }
}

float fmod(float a, float b)
{
    long long quotient;
    if (__fabs(b) > __fabs(a))
        return a;
    quotient = a / b;
    return a - b * quotient;
}

HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc)
{
    HSD_FObjDesc* fobjdesc;
    HSD_AObj* aobj;
    HSD_JObj* jobj;
    HSD_FObj* fobj;
    u32 id;
    HSD_Obj* phi_r30;

    if (aobjdesc != NULL) {
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, aobjdesc->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0F);
        HSD_AObjSetEndFrame(aobj, aobjdesc->end_frame);
        fobjdesc = aobjdesc->fobjdesc;
        fobj = HSD_FObjLoadDesc(fobjdesc);
        HSD_AObjSetFObj(aobj, fobj);
        id = aobjdesc->obj_id;
        if (id != 0U) {
            HSD_Obj* hsd_obj = HSD_IDGetDataFromTable(0, id, 0);
            phi_r30 = hsd_obj;
            if (hsd_obj != NULL) {
                if (hsd_obj != NULL) {
                    u16* ref_count = &hsd_obj->ref_count;
                    *ref_count += 1;
                    if (*ref_count == (u16) -1) {
                        __assert("object.h", 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
                    }
                }
            } else {
                phi_r30 = (HSD_Obj*) HSD_JObjLoadJoint((void*) aobjdesc->obj_id);
            }
            if (aobj != NULL) {
                if (aobj->hsd_obj != NULL) {
                    HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
                }
                aobj->hsd_obj = phi_r30;
            }
        }
        return aobj;
    }
    return NULL;
}

void HSD_AObjRemove(HSD_AObj* aobj)
{
    if (!aobj)
        return;

    if (aobj) {
        if (aobj->fobj)
            HSD_FObjRemoveAll(aobj->fobj);
        aobj->fobj = NULL;
    }

    if (aobj) {
        if (aobj->hsd_obj != NULL)
            HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
        aobj->hsd_obj = NULL;
    }
    HSD_AObjFree(aobj);
}

HSD_AObj* HSD_AObjAlloc(void)
{
    HSD_AObj* aobj = (HSD_AObj*) HSD_ObjAlloc(&aobj_alloc_data);
    if (aobj == NULL) {
        __assert(lbl_804D5D08, 489, lbl_804D5D10);
    }
    memset(aobj, 0, sizeof(HSD_AObj));
    aobj->flags = AOBJ_NO_ANIM;
    aobj->framerate = 1.0F;
    return aobj;
}

void HSD_AObjFree(HSD_AObj* aobj)
{
    if (!aobj)
        return;

    HSD_ObjFree(&aobj_alloc_data, (HSD_ObjAllocLink*) aobj);
}

void callbackForeachFunc(struct _HSD_AObj* aobj, void* obj, HSD_Type type, void (*func)(), AObj_Arg_Type arg_type, callbackArg* arg)
{
    switch (arg_type) {
    case AOBJ_ARG_A:
        (*func)(aobj);
        return;
    case AOBJ_ARG_AF:
        (*func)(aobj, arg->f);
        return;
    case AOBJ_ARG_AV:
        (*func)(aobj, arg->v);
        return;
    case AOBJ_ARG_AU:
        (*func)(aobj, arg->d);
        return;
    case AOBJ_ARG_AO:
        (*func)(aobj, obj);
        return;
    case AOBJ_ARG_AOT:
        (*func)(aobj, obj, type);
        return;
    case AOBJ_ARG_AOF:
        (*func)(aobj, obj, arg->f);
        return;
    case AOBJ_ARG_AOV:
        (*func)(aobj, obj, arg->v);
        return;
    case AOBJ_ARG_AOU:
        (*func)(aobj, obj, arg->d);
        return;
    case AOBJ_ARG_AOTF:
        (*func)(aobj, obj, type, arg->f);
        return;
    case AOBJ_ARG_AOTV:
        (*func)(aobj, obj, type, arg->v);
        return;
    case AOBJ_ARG_AOTU:
        (*func)(aobj, obj, type, (u32) arg->d);
        return;
    }
}

void TObjForeachAnim(HSD_TObj* tobj, HSD_TypeMask mask, void (*func)(), AObj_Arg_Type arg_type, callbackArg* arg)
{
    while (tobj != NULL) {
        if (mask & TOBJ_MASK && tobj->aobj != NULL) {
            callbackForeachFunc(tobj->aobj, tobj, TOBJ_TYPE, func, arg_type, arg);
        }
        tobj = tobj->next;
    }
}

void RObjForeachAnim(HSD_RObj* robj, HSD_TypeMask mask, void (*func)(), AObj_Arg_Type arg_type, callbackArg* arg)
{
    while (robj != NULL) {
        if (mask & ROBJ_MASK && robj->aobj != NULL) {
            callbackForeachFunc(robj->aobj, robj, ROBJ_TYPE, func, arg_type, arg);
        }
        robj = robj->next;
    }
}

void PObjForeachAnim(HSD_PObj* pobj, HSD_TypeMask mask, void (*func)(), AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (pobj == NULL)
        return;

    if ((pobj->flags & 0x3000) == 0x1000
        && pobj->u.x14_unk != NULL && pobj->u.x14_unk->aobj != NULL) {
        callbackForeachFunc(pobj->u.x14_unk->aobj, pobj, POBJ_TYPE, func, arg_type, arg);
    }
}

void MObjForeachAnim(HSD_MObj* mobj, HSD_TypeMask mask, void (*func)(), AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mobj == NULL)
        return;

    if (mask & MOBJ_MASK && mobj->aobj != NULL) {
        callbackForeachFunc(mobj->aobj, mobj, MOBJ_TYPE, func, arg_type, arg);
    }
    TObjForeachAnim(mobj->tobj, mask, func, arg_type, arg);
}

void DObjForeachAnim(HSD_DObj* dobj, HSD_TypeMask mask, void (*func)(), AObj_Arg_Type arg_type, callbackArg* arg)
{
    HSD_PObj* pobj;

    while (dobj != NULL) {
        if (mask & DOBJ_MASK && dobj->aobj != NULL) {
            callbackForeachFunc(dobj->aobj, dobj, DOBJ_TYPE, func, arg_type, arg);
        }
        MObjForeachAnim(dobj->mobj, mask, func, arg_type, arg);
        pobj = dobj->pobj;
        if (mask & POBJ_MASK) {
            PObjForeachAnim(pobj, mask, func, arg_type, arg);
        }
        dobj = dobj->next;
    }
}

// https://decomp.me/scratch/AOTU9
#ifdef NON_MATCHING
void JObjForeachAnim(HSD_JObj* jobj, HSD_TypeMask mask, void (*func)(), AObj_Arg_Type arg_type, callbackArg* arg)
{
    HSD_JObj* child;
    HSD_JObj* new_var;

    (jobj != NULL) ? (void)0 : __assert("aobj.c", 0x2CB, "obj");

    if (mask & JOBJ_MASK && jobj->aobj != NULL) {
        callbackForeachFunc(jobj->aobj, jobj, JOBJ_TYPE, func, arg_type, arg);
    }
    if (union_type_dobj(jobj)) {
        DObjForeachAnim(jobj->u.dobj, mask, func, arg_type, arg);
    }
    RObjForeachAnim(jobj->robj, mask, func, arg_type, arg);
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        child = jobj->child;
        while (child != NULL) {
            new_var = child;
            JObjForeachAnim(new_var, mask, func, arg_type, arg);
            child = child->next;
        }
    }
}
#else
#pragma push
asm void JObjForeachAnim()
{ // clang-format off
    nofralloc
    /* 80364924 00361504  7C 08 02 A6 */	mflr r0
    /* 80364928 00361508  90 01 00 04 */	stw r0, 4(r1)
    /* 8036492C 0036150C  94 21 FF B0 */	stwu r1, -0x50(r1)
    /* 80364930 00361510  BE A1 00 24 */	stmw r21, 0x24(r1)
    /* 80364934 00361514  7C 79 1B 79 */	or. r25, r3, r3
    /* 80364938 00361518  3B 44 00 00 */	addi r26, r4, 0
    /* 8036493C 0036151C  3B 65 00 00 */	addi r27, r5, 0
    /* 80364940 00361520  3B 86 00 00 */	addi r28, r6, 0
    /* 80364944 00361524  3B A7 00 00 */	addi r29, r7, 0
    /* 80364948 00361528  40 82 00 14 */	bne lbl_8036495C
    /* 8036494C 0036152C  38 6D A6 68 */	addi r3, r13, lbl_804D5D08
    /* 80364950 00361530  38 80 02 CB */	li r4, 0x2cb
    /* 80364954 00361534  38 AD A6 74 */	addi r5, r13, lbl_804D5D14
    /* 80364958 00361538  48 02 38 C9 */	bl __assert
lbl_8036495C:
    /* 8036495C 0036153C  57 5F 06 B5 */	rlwinm. r31, r26, 0, 0x1a, 0x1a
    /* 80364960 00361540  41 82 00 28 */	beq lbl_80364988
    /* 80364964 00361544  80 79 00 7C */	lwz r3, 0x7c(r25)
    /* 80364968 00361548  28 03 00 00 */	cmplwi r3, 0
    /* 8036496C 0036154C  41 82 00 1C */	beq lbl_80364988
    /* 80364970 00361550  38 99 00 00 */	addi r4, r25, 0
    /* 80364974 00361554  38 DB 00 00 */	addi r6, r27, 0
    /* 80364978 00361558  38 FC 00 00 */	addi r7, r28, 0
    /* 8036497C 0036155C  39 1D 00 00 */	addi r8, r29, 0
    /* 80364980 00361560  38 A0 00 06 */	li r5, 6
    /* 80364984 00361564  4B FF FC 55 */	bl callbackForeachFunc
lbl_80364988:
    /* 80364988 00361568  80 19 00 14 */	lwz r0, 0x14(r25)
    /* 8036498C 0036156C  70 00 40 20 */	andi. r0, r0, 0x4020
    /* 80364990 00361570  41 82 00 0C */	beq lbl_8036499C
    /* 80364994 00361574  38 00 00 00 */	li r0, 0
    /* 80364998 00361578  48 00 00 08 */	b lbl_803649A0
lbl_8036499C:
    /* 8036499C 0036157C  38 00 00 01 */	li r0, 1
lbl_803649A0:
    /* 803649A0 00361580  2C 00 00 00 */	cmpwi r0, 0
    /* 803649A4 00361584  41 82 00 F0 */	beq lbl_80364A94
    /* 803649A8 00361588  83 D9 00 18 */	lwz r30, 0x18(r25)
    /* 803649AC 0036158C  57 58 07 7A */	rlwinm r24, r26, 0, 0x1d, 0x1d
    /* 803649B0 00361590  57 57 06 30 */	rlwinm r23, r26, 0, 0x18, 0x18
    /* 803649B4 00361594  57 56 05 EE */	rlwinm r22, r26, 0, 0x17, 0x17
    /* 803649B8 00361598  48 00 00 D4 */	b lbl_80364A8C
lbl_803649BC:
    /* 803649BC 0036159C  2C 18 00 00 */	cmpwi r24, 0
    /* 803649C0 003615A0  41 82 00 28 */	beq lbl_803649E8
    /* 803649C4 003615A4  80 7E 00 10 */	lwz r3, 0x10(r30)
    /* 803649C8 003615A8  28 03 00 00 */	cmplwi r3, 0
    /* 803649CC 003615AC  41 82 00 1C */	beq lbl_803649E8
    /* 803649D0 003615B0  38 9E 00 00 */	addi r4, r30, 0
    /* 803649D4 003615B4  38 DB 00 00 */	addi r6, r27, 0
    /* 803649D8 003615B8  38 FC 00 00 */	addi r7, r28, 0
    /* 803649DC 003615BC  39 1D 00 00 */	addi r8, r29, 0
    /* 803649E0 003615C0  38 A0 00 03 */	li r5, 3
    /* 803649E4 003615C4  4B FF FB F5 */	bl callbackForeachFunc
lbl_803649E8:
    /* 803649E8 003615C8  82 BE 00 08 */	lwz r21, 8(r30)
    /* 803649EC 003615CC  28 15 00 00 */	cmplwi r21, 0
    /* 803649F0 003615D0  41 82 00 48 */	beq lbl_80364A38
    /* 803649F4 003615D4  2C 17 00 00 */	cmpwi r23, 0
    /* 803649F8 003615D8  41 82 00 28 */	beq lbl_80364A20
    /* 803649FC 003615DC  80 75 00 14 */	lwz r3, 0x14(r21)
    /* 80364A00 003615E0  28 03 00 00 */	cmplwi r3, 0
    /* 80364A04 003615E4  41 82 00 1C */	beq lbl_80364A20
    /* 80364A08 003615E8  38 95 00 00 */	addi r4, r21, 0
    /* 80364A0C 003615EC  38 DB 00 00 */	addi r6, r27, 0
    /* 80364A10 003615F0  38 FC 00 00 */	addi r7, r28, 0
    /* 80364A14 003615F4  39 1D 00 00 */	addi r8, r29, 0
    /* 80364A18 003615F8  38 A0 00 08 */	li r5, 8
    /* 80364A1C 003615FC  4B FF FB BD */	bl callbackForeachFunc
lbl_80364A20:
    /* 80364A20 00361600  80 75 00 08 */	lwz r3, 8(r21)
    /* 80364A24 00361604  38 9A 00 00 */	addi r4, r26, 0
    /* 80364A28 00361608  38 BB 00 00 */	addi r5, r27, 0
    /* 80364A2C 0036160C  38 DC 00 00 */	addi r6, r28, 0
    /* 80364A30 00361610  38 FD 00 00 */	addi r7, r29, 0
    /* 80364A34 00361614  4B FF FC C1 */	bl TObjForeachAnim
lbl_80364A38:
    /* 80364A38 00361618  2C 16 00 00 */	cmpwi r22, 0
    /* 80364A3C 0036161C  80 9E 00 0C */	lwz r4, 0xc(r30)
    /* 80364A40 00361620  41 82 00 48 */	beq lbl_80364A88
    /* 80364A44 00361624  28 04 00 00 */	cmplwi r4, 0
    /* 80364A48 00361628  41 82 00 40 */	beq lbl_80364A88
    /* 80364A4C 0036162C  A0 04 00 0C */	lhz r0, 0xc(r4)
    /* 80364A50 00361630  54 00 04 A6 */	rlwinm r0, r0, 0, 0x12, 0x13
    /* 80364A54 00361634  2C 00 10 00 */	cmpwi r0, 0x1000
    /* 80364A58 00361638  40 82 00 30 */	bne lbl_80364A88
    /* 80364A5C 0036163C  80 64 00 14 */	lwz r3, 0x14(r4)
    /* 80364A60 00361640  28 03 00 00 */	cmplwi r3, 0
    /* 80364A64 00361644  41 82 00 24 */	beq lbl_80364A88
    /* 80364A68 00361648  80 63 00 20 */	lwz r3, 0x20(r3)
    /* 80364A6C 0036164C  28 03 00 00 */	cmplwi r3, 0
    /* 80364A70 00361650  41 82 00 18 */	beq lbl_80364A88
    /* 80364A74 00361654  38 DB 00 00 */	addi r6, r27, 0
    /* 80364A78 00361658  38 FC 00 00 */	addi r7, r28, 0
    /* 80364A7C 0036165C  39 1D 00 00 */	addi r8, r29, 0
    /* 80364A80 00361660  38 A0 00 09 */	li r5, 9
    /* 80364A84 00361664  4B FF FB 55 */	bl callbackForeachFunc
lbl_80364A88:
    /* 80364A88 00361668  83 DE 00 04 */	lwz r30, 4(r30)
lbl_80364A8C:
    /* 80364A8C 0036166C  28 1E 00 00 */	cmplwi r30, 0
    /* 80364A90 00361670  40 82 FF 2C */	bne lbl_803649BC
lbl_80364A94:
    /* 80364A94 00361674  83 19 00 80 */	lwz r24, 0x80(r25)
    /* 80364A98 00361678  57 5E 05 AC */	rlwinm r30, r26, 0, 0x16, 0x16
    /* 80364A9C 0036167C  48 00 00 34 */	b lbl_80364AD0
lbl_80364AA0:
    /* 80364AA0 00361680  2C 1E 00 00 */	cmpwi r30, 0
    /* 80364AA4 00361684  41 82 00 28 */	beq lbl_80364ACC
    /* 80364AA8 00361688  80 78 00 18 */	lwz r3, 0x18(r24)
    /* 80364AAC 0036168C  28 03 00 00 */	cmplwi r3, 0
    /* 80364AB0 00361690  41 82 00 1C */	beq lbl_80364ACC
    /* 80364AB4 00361694  38 98 00 00 */	addi r4, r24, 0
    /* 80364AB8 00361698  38 DB 00 00 */	addi r6, r27, 0
    /* 80364ABC 0036169C  38 FC 00 00 */	addi r7, r28, 0
    /* 80364AC0 003616A0  39 1D 00 00 */	addi r8, r29, 0
    /* 80364AC4 003616A4  38 A0 00 0A */	li r5, 0xa
    /* 80364AC8 003616A8  4B FF FB 11 */	bl callbackForeachFunc
lbl_80364ACC:
    /* 80364ACC 003616AC  83 18 00 00 */	lwz r24, 0(r24)
lbl_80364AD0:
    /* 80364AD0 003616B0  28 18 00 00 */	cmplwi r24, 0
    /* 80364AD4 003616B4  40 82 FF CC */	bne lbl_80364AA0
    /* 80364AD8 003616B8  80 19 00 14 */	lwz r0, 0x14(r25)
    /* 80364ADC 003616BC  54 00 04 E7 */	rlwinm. r0, r0, 0, 0x13, 0x13
    /* 80364AE0 003616C0  40 82 01 14 */	bne lbl_80364BF4
    /* 80364AE4 003616C4  83 39 00 10 */	lwz r25, 0x10(r25)
    /* 80364AE8 003616C8  48 00 01 04 */	b lbl_80364BEC
lbl_80364AEC:
    /* 80364AEC 003616CC  28 19 00 00 */	cmplwi r25, 0
    /* 80364AF0 003616D0  3B 19 00 00 */	addi r24, r25, 0
    /* 80364AF4 003616D4  40 82 00 14 */	bne lbl_80364B08
    /* 80364AF8 003616D8  38 6D A6 68 */	addi r3, r13, lbl_804D5D08
    /* 80364AFC 003616DC  38 80 02 CB */	li r4, 0x2cb
    /* 80364B00 003616E0  38 AD A6 74 */	addi r5, r13, lbl_804D5D14
    /* 80364B04 003616E4  48 02 37 1D */	bl __assert
lbl_80364B08:
    /* 80364B08 003616E8  2C 1F 00 00 */	cmpwi r31, 0
    /* 80364B0C 003616EC  41 82 00 2C */	beq lbl_80364B38
    /* 80364B10 003616F0  80 19 00 7C */	lwz r0, 0x7c(r25)
    /* 80364B14 003616F4  28 00 00 00 */	cmplwi r0, 0
    /* 80364B18 003616F8  41 82 00 20 */	beq lbl_80364B38
    /* 80364B1C 003616FC  80 78 00 7C */	lwz r3, 0x7c(r24)
    /* 80364B20 00361700  38 98 00 00 */	addi r4, r24, 0
    /* 80364B24 00361704  38 DB 00 00 */	addi r6, r27, 0
    /* 80364B28 00361708  38 FC 00 00 */	addi r7, r28, 0
    /* 80364B2C 0036170C  39 1D 00 00 */	addi r8, r29, 0
    /* 80364B30 00361710  38 A0 00 06 */	li r5, 6
    /* 80364B34 00361714  4B FF FA A5 */	bl callbackForeachFunc
lbl_80364B38:
    /* 80364B38 00361718  80 19 00 14 */	lwz r0, 0x14(r25)
    /* 80364B3C 0036171C  70 00 40 20 */	andi. r0, r0, 0x4020
    /* 80364B40 00361720  41 82 00 0C */	beq lbl_80364B4C
    /* 80364B44 00361724  38 00 00 00 */	li r0, 0
    /* 80364B48 00361728  48 00 00 08 */	b lbl_80364B50
lbl_80364B4C:
    /* 80364B4C 0036172C  38 00 00 01 */	li r0, 1
lbl_80364B50:
    /* 80364B50 00361730  2C 00 00 00 */	cmpwi r0, 0
    /* 80364B54 00361734  41 82 00 1C */	beq lbl_80364B70
    /* 80364B58 00361738  80 78 00 18 */	lwz r3, 0x18(r24)
    /* 80364B5C 0036173C  38 9A 00 00 */	addi r4, r26, 0
    /* 80364B60 00361740  38 BB 00 00 */	addi r5, r27, 0
    /* 80364B64 00361744  38 DC 00 00 */	addi r6, r28, 0
    /* 80364B68 00361748  38 FD 00 00 */	addi r7, r29, 0
    /* 80364B6C 0036174C  4B FF FC 71 */	bl DObjForeachAnim
lbl_80364B70:
    /* 80364B70 00361750  83 19 00 80 */	lwz r24, 0x80(r25)
    /* 80364B74 00361754  48 00 00 34 */	b lbl_80364BA8
lbl_80364B78:
    /* 80364B78 00361758  2C 1E 00 00 */	cmpwi r30, 0
    /* 80364B7C 0036175C  41 82 00 28 */	beq lbl_80364BA4
    /* 80364B80 00361760  80 78 00 18 */	lwz r3, 0x18(r24)
    /* 80364B84 00361764  28 03 00 00 */	cmplwi r3, 0
    /* 80364B88 00361768  41 82 00 1C */	beq lbl_80364BA4
    /* 80364B8C 0036176C  38 98 00 00 */	addi r4, r24, 0
    /* 80364B90 00361770  38 DB 00 00 */	addi r6, r27, 0
    /* 80364B94 00361774  38 FC 00 00 */	addi r7, r28, 0
    /* 80364B98 00361778  39 1D 00 00 */	addi r8, r29, 0
    /* 80364B9C 0036177C  38 A0 00 0A */	li r5, 0xa
    /* 80364BA0 00361780  4B FF FA 39 */	bl callbackForeachFunc
lbl_80364BA4:
    /* 80364BA4 00361784  83 18 00 00 */	lwz r24, 0(r24)
lbl_80364BA8:
    /* 80364BA8 00361788  28 18 00 00 */	cmplwi r24, 0
    /* 80364BAC 0036178C  40 82 FF CC */	bne lbl_80364B78
    /* 80364BB0 00361790  80 19 00 14 */	lwz r0, 0x14(r25)
    /* 80364BB4 00361794  54 00 04 E7 */	rlwinm. r0, r0, 0, 0x13, 0x13
    /* 80364BB8 00361798  40 82 00 30 */	bne lbl_80364BE8
    /* 80364BBC 0036179C  82 B9 00 10 */	lwz r21, 0x10(r25)
    /* 80364BC0 003617A0  48 00 00 20 */	b lbl_80364BE0
lbl_80364BC4:
    /* 80364BC4 003617A4  38 75 00 00 */	addi r3, r21, 0
    /* 80364BC8 003617A8  38 9A 00 00 */	addi r4, r26, 0
    /* 80364BCC 003617AC  38 BB 00 00 */	addi r5, r27, 0
    /* 80364BD0 003617B0  38 DC 00 00 */	addi r6, r28, 0
    /* 80364BD4 003617B4  38 FD 00 00 */	addi r7, r29, 0
    /* 80364BD8 003617B8  4B FF FD 4D */	bl JObjForeachAnim
    /* 80364BDC 003617BC  82 B5 00 08 */	lwz r21, 8(r21)
lbl_80364BE0:
    /* 80364BE0 003617C0  28 15 00 00 */	cmplwi r21, 0
    /* 80364BE4 003617C4  40 82 FF E0 */	bne lbl_80364BC4
lbl_80364BE8:
    /* 80364BE8 003617C8  83 39 00 08 */	lwz r25, 8(r25)
lbl_80364BEC:
    /* 80364BEC 003617CC  28 19 00 00 */	cmplwi r25, 0
    /* 80364BF0 003617D0  40 82 FE FC */	bne lbl_80364AEC
lbl_80364BF4:
    /* 80364BF4 003617D4  BA A1 00 24 */	lmw r21, 0x24(r1)
    /* 80364BF8 003617D8  80 01 00 54 */	lwz r0, 0x54(r1)
    /* 80364BFC 003617DC  38 21 00 50 */	addi r1, r1, 0x50
    /* 80364C00 003617E0  7C 08 03 A6 */	mtlr r0
    /* 80364C04 003617E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
#endif

#pragma push
asm void HSD_ForeachAnim(void*, ...)
{ // clang-format off
    nofralloc
    /* 80364C08 003617E8  7C 08 02 A6 */	mflr r0
    /* 80364C0C 003617EC  90 01 00 04 */	stw r0, 4(r1)
    /* 80364C10 003617F0  94 21 FF 50 */	stwu r1, -0xb0(r1)
    /* 80364C14 003617F4  BF 01 00 90 */	stmw r24, 0x90(r1)
    /* 80364C18 003617F8  40 86 00 24 */	bne cr1, lbl_80364C3C
    /* 80364C1C 003617FC  D8 21 00 28 */	stfd f1, 0x28(r1)
    /* 80364C20 00361800  D8 41 00 30 */	stfd f2, 0x30(r1)
    /* 80364C24 00361804  D8 61 00 38 */	stfd f3, 0x38(r1)
    /* 80364C28 00361808  D8 81 00 40 */	stfd f4, 0x40(r1)
    /* 80364C2C 0036180C  D8 A1 00 48 */	stfd f5, 0x48(r1)
    /* 80364C30 00361810  D8 C1 00 50 */	stfd f6, 0x50(r1)
    /* 80364C34 00361814  D8 E1 00 58 */	stfd f7, 0x58(r1)
    /* 80364C38 00361818  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_80364C3C:
    /* 80364C3C 0036181C  90 61 00 08 */	stw r3, 8(r1)
    /* 80364C40 00361820  7C 7B 1B 79 */	or. r27, r3, r3
    /* 80364C44 00361824  3B 84 00 00 */	addi r28, r4, 0
    /* 80364C48 00361828  90 81 00 0C */	stw r4, 0xc(r1)
    /* 80364C4C 0036182C  3B A5 00 00 */	addi r29, r5, 0
    /* 80364C50 00361830  3B C6 00 00 */	addi r30, r6, 0
    /* 80364C54 00361834  90 A1 00 10 */	stw r5, 0x10(r1)
    /* 80364C58 00361838  3B E7 00 00 */	addi r31, r7, 0
    /* 80364C5C 0036183C  90 C1 00 14 */	stw r6, 0x14(r1)
    /* 80364C60 00361840  90 E1 00 18 */	stw r7, 0x18(r1)
    /* 80364C64 00361844  91 01 00 1C */	stw r8, 0x1c(r1)
    /* 80364C68 00361848  91 21 00 20 */	stw r9, 0x20(r1)
    /* 80364C6C 0036184C  91 41 00 24 */	stw r10, 0x24(r1)
    /* 80364C70 00361850  41 82 06 88 */	beq lbl_803652F8
    /* 80364C74 00361854  3C 00 05 00 */	lis r0, 0x500
    /* 80364C78 00361858  90 01 00 80 */	stw r0, 0x80(r1)
    /* 80364C7C 0036185C  38 01 00 B8 */	addi r0, r1, 0xb8
    /* 80364C80 00361860  28 1F 00 0B */	cmplwi r31, 0xb
    /* 80364C84 00361864  90 01 00 84 */	stw r0, 0x84(r1)
    /* 80364C88 00361868  38 01 00 08 */	addi r0, r1, 8
    /* 80364C8C 0036186C  90 01 00 88 */	stw r0, 0x88(r1)
    /* 80364C90 00361870  41 81 00 68 */	bgt lbl_80364CF8
    /* 80364C94 00361874  3C 60 80 40 */	lis r3, jtbl_8040608C@ha
    /* 80364C98 00361878  38 63 60 8C */	addi r3, r3, jtbl_8040608C@l
    /* 80364C9C 0036187C  57 E0 10 3A */	slwi r0, r31, 2
    /* 80364CA0 00361880  7C 03 00 2E */	lwzx r0, r3, r0
    /* 80364CA4 00361884  7C 09 03 A6 */	mtctr r0
    /* 80364CA8 00361888  4E 80 04 20 */	bctr 
    /* 80364CAC 0036188C  38 61 00 80 */	addi r3, r1, 0x80
    /* 80364CB0 00361890  38 80 00 03 */	li r4, 3
    /* 80364CB4 00361894  4B FB D9 6D */	bl __va_arg
    /* 80364CB8 00361898  C8 03 00 00 */	lfd f0, 0(r3)
    /* 80364CBC 0036189C  FC 00 00 18 */	frsp f0, f0
    /* 80364CC0 003618A0  D0 01 00 7C */	stfs f0, 0x7c(r1)
    /* 80364CC4 003618A4  48 00 00 48 */	b lbl_80364D0C
    /* 80364CC8 003618A8  38 61 00 80 */	addi r3, r1, 0x80
    /* 80364CCC 003618AC  38 80 00 01 */	li r4, 1
    /* 80364CD0 003618B0  4B FB D9 51 */	bl __va_arg
    /* 80364CD4 003618B4  80 03 00 00 */	lwz r0, 0(r3)
    /* 80364CD8 003618B8  90 01 00 7C */	stw r0, 0x7c(r1)
    /* 80364CDC 003618BC  48 00 00 30 */	b lbl_80364D0C
    /* 80364CE0 003618C0  38 61 00 80 */	addi r3, r1, 0x80
    /* 80364CE4 003618C4  38 80 00 01 */	li r4, 1
    /* 80364CE8 003618C8  4B FB D9 39 */	bl __va_arg
    /* 80364CEC 003618CC  80 03 00 00 */	lwz r0, 0(r3)
    /* 80364CF0 003618D0  90 01 00 7C */	stw r0, 0x7c(r1)
    /* 80364CF4 003618D4  48 00 00 18 */	b lbl_80364D0C
lbl_80364CF8:
    /* 80364CF8 003618D8  3C 60 80 40 */	lis r3, lbl_8040601C@ha
    /* 80364CFC 003618DC  38 A3 60 1C */	addi r5, r3, lbl_8040601C@l
    /* 80364D00 003618E0  38 6D A6 68 */	addi r3, r13, lbl_804D5D08
    /* 80364D04 003618E4  38 80 03 3A */	li r4, 0x33a
    /* 80364D08 003618E8  48 02 35 71 */	bl HSD_Panic
lbl_80364D0C:
    /* 80364D0C 003618EC  28 1C 00 0C */	cmplwi r28, 0xc
    /* 80364D10 003618F0  41 81 05 D4 */	bgt lbl_803652E4
    /* 80364D14 003618F4  3C 60 80 40 */	lis r3, jtbl_80406058@ha
    /* 80364D18 003618F8  38 63 60 58 */	addi r3, r3, jtbl_80406058@l
    /* 80364D1C 003618FC  57 80 10 3A */	slwi r0, r28, 2
    /* 80364D20 00361900  7C 03 00 2E */	lwzx r0, r3, r0
    /* 80364D24 00361904  7C 09 03 A6 */	mtctr r0
    /* 80364D28 00361908  4E 80 04 20 */	bctr 
    /* 80364D2C 0036190C  28 1B 00 00 */	cmplwi r27, 0
    /* 80364D30 00361910  40 82 00 14 */	bne lbl_80364D44
    /* 80364D34 00361914  38 6D A6 68 */	addi r3, r13, lbl_804D5D08
    /* 80364D38 00361918  38 80 02 CB */	li r4, 0x2cb
    /* 80364D3C 0036191C  38 AD A6 74 */	addi r5, r13, lbl_804D5D14
    /* 80364D40 00361920  48 02 34 E1 */	bl __assert
lbl_80364D44:
    /* 80364D44 00361924  57 A0 06 B5 */	rlwinm. r0, r29, 0, 0x1a, 0x1a
    /* 80364D48 00361928  41 82 00 2C */	beq lbl_80364D74
    /* 80364D4C 0036192C  80 1B 00 7C */	lwz r0, 0x7c(r27)
    /* 80364D50 00361930  28 00 00 00 */	cmplwi r0, 0
    /* 80364D54 00361934  41 82 00 20 */	beq lbl_80364D74
    /* 80364D58 00361938  80 7B 00 7C */	lwz r3, 0x7c(r27)
    /* 80364D5C 0036193C  38 9B 00 00 */	addi r4, r27, 0
    /* 80364D60 00361940  38 DE 00 00 */	addi r6, r30, 0
    /* 80364D64 00361944  38 FF 00 00 */	addi r7, r31, 0
    /* 80364D68 00361948  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364D6C 0036194C  38 A0 00 06 */	li r5, 6
    /* 80364D70 00361950  4B FF F8 69 */	bl callbackForeachFunc
lbl_80364D74:
    /* 80364D74 00361954  80 1B 00 14 */	lwz r0, 0x14(r27)
    /* 80364D78 00361958  70 00 40 20 */	andi. r0, r0, 0x4020
    /* 80364D7C 0036195C  41 82 00 0C */	beq lbl_80364D88
    /* 80364D80 00361960  38 00 00 00 */	li r0, 0
    /* 80364D84 00361964  48 00 00 08 */	b lbl_80364D8C
lbl_80364D88:
    /* 80364D88 00361968  38 00 00 01 */	li r0, 1
lbl_80364D8C:
    /* 80364D8C 0036196C  2C 00 00 00 */	cmpwi r0, 0
    /* 80364D90 00361970  41 82 00 1C */	beq lbl_80364DAC
    /* 80364D94 00361974  80 7B 00 18 */	lwz r3, 0x18(r27)
    /* 80364D98 00361978  38 9D 00 00 */	addi r4, r29, 0
    /* 80364D9C 0036197C  38 BE 00 00 */	addi r5, r30, 0
    /* 80364DA0 00361980  38 DF 00 00 */	addi r6, r31, 0
    /* 80364DA4 00361984  38 E1 00 7C */	addi r7, r1, 0x7c
    /* 80364DA8 00361988  4B FF FA 35 */	bl DObjForeachAnim
lbl_80364DAC:
    /* 80364DAC 0036198C  83 9B 00 80 */	lwz r28, 0x80(r27)
    /* 80364DB0 00361990  57 BA 05 AC */	rlwinm r26, r29, 0, 0x16, 0x16
    /* 80364DB4 00361994  48 00 00 34 */	b lbl_80364DE8
lbl_80364DB8:
    /* 80364DB8 00361998  2C 1A 00 00 */	cmpwi r26, 0
    /* 80364DBC 0036199C  41 82 00 28 */	beq lbl_80364DE4
    /* 80364DC0 003619A0  80 7C 00 18 */	lwz r3, 0x18(r28)
    /* 80364DC4 003619A4  28 03 00 00 */	cmplwi r3, 0
    /* 80364DC8 003619A8  41 82 00 1C */	beq lbl_80364DE4
    /* 80364DCC 003619AC  38 9C 00 00 */	addi r4, r28, 0
    /* 80364DD0 003619B0  38 DE 00 00 */	addi r6, r30, 0
    /* 80364DD4 003619B4  38 FF 00 00 */	addi r7, r31, 0
    /* 80364DD8 003619B8  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364DDC 003619BC  38 A0 00 0A */	li r5, 0xa
    /* 80364DE0 003619C0  4B FF F7 F9 */	bl callbackForeachFunc
lbl_80364DE4:
    /* 80364DE4 003619C4  83 9C 00 00 */	lwz r28, 0(r28)
lbl_80364DE8:
    /* 80364DE8 003619C8  28 1C 00 00 */	cmplwi r28, 0
    /* 80364DEC 003619CC  40 82 FF CC */	bne lbl_80364DB8
    /* 80364DF0 003619D0  80 1B 00 14 */	lwz r0, 0x14(r27)
    /* 80364DF4 003619D4  54 00 04 E7 */	rlwinm. r0, r0, 0, 0x13, 0x13
    /* 80364DF8 003619D8  40 82 05 00 */	bne lbl_803652F8
    /* 80364DFC 003619DC  83 1B 00 10 */	lwz r24, 0x10(r27)
    /* 80364E00 003619E0  48 00 00 20 */	b lbl_80364E20
lbl_80364E04:
    /* 80364E04 003619E4  38 78 00 00 */	addi r3, r24, 0
    /* 80364E08 003619E8  38 9D 00 00 */	addi r4, r29, 0
    /* 80364E0C 003619EC  38 BE 00 00 */	addi r5, r30, 0
    /* 80364E10 003619F0  38 DF 00 00 */	addi r6, r31, 0
    /* 80364E14 003619F4  38 E1 00 7C */	addi r7, r1, 0x7c
    /* 80364E18 003619F8  4B FF FB 0D */	bl JObjForeachAnim
    /* 80364E1C 003619FC  83 18 00 08 */	lwz r24, 8(r24)
lbl_80364E20:
    /* 80364E20 00361A00  28 18 00 00 */	cmplwi r24, 0
    /* 80364E24 00361A04  40 82 FF E0 */	bne lbl_80364E04
    /* 80364E28 00361A08  48 00 04 D0 */	b lbl_803652F8
    /* 80364E2C 00361A0C  57 BA 07 7A */	rlwinm r26, r29, 0, 0x1d, 0x1d
    /* 80364E30 00361A10  57 BC 06 30 */	rlwinm r28, r29, 0, 0x18, 0x18
    /* 80364E34 00361A14  57 B9 05 EE */	rlwinm r25, r29, 0, 0x17, 0x17
    /* 80364E38 00361A18  48 00 00 D4 */	b lbl_80364F0C
lbl_80364E3C:
    /* 80364E3C 00361A1C  2C 1A 00 00 */	cmpwi r26, 0
    /* 80364E40 00361A20  41 82 00 28 */	beq lbl_80364E68
    /* 80364E44 00361A24  80 7B 00 10 */	lwz r3, 0x10(r27)
    /* 80364E48 00361A28  28 03 00 00 */	cmplwi r3, 0
    /* 80364E4C 00361A2C  41 82 00 1C */	beq lbl_80364E68
    /* 80364E50 00361A30  38 9B 00 00 */	addi r4, r27, 0
    /* 80364E54 00361A34  38 DE 00 00 */	addi r6, r30, 0
    /* 80364E58 00361A38  38 FF 00 00 */	addi r7, r31, 0
    /* 80364E5C 00361A3C  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364E60 00361A40  38 A0 00 03 */	li r5, 3
    /* 80364E64 00361A44  4B FF F7 75 */	bl callbackForeachFunc
lbl_80364E68:
    /* 80364E68 00361A48  83 1B 00 08 */	lwz r24, 8(r27)
    /* 80364E6C 00361A4C  28 18 00 00 */	cmplwi r24, 0
    /* 80364E70 00361A50  41 82 00 48 */	beq lbl_80364EB8
    /* 80364E74 00361A54  2C 1C 00 00 */	cmpwi r28, 0
    /* 80364E78 00361A58  41 82 00 28 */	beq lbl_80364EA0
    /* 80364E7C 00361A5C  80 78 00 14 */	lwz r3, 0x14(r24)
    /* 80364E80 00361A60  28 03 00 00 */	cmplwi r3, 0
    /* 80364E84 00361A64  41 82 00 1C */	beq lbl_80364EA0
    /* 80364E88 00361A68  38 98 00 00 */	addi r4, r24, 0
    /* 80364E8C 00361A6C  38 DE 00 00 */	addi r6, r30, 0
    /* 80364E90 00361A70  38 FF 00 00 */	addi r7, r31, 0
    /* 80364E94 00361A74  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364E98 00361A78  38 A0 00 08 */	li r5, 8
    /* 80364E9C 00361A7C  4B FF F7 3D */	bl callbackForeachFunc
lbl_80364EA0:
    /* 80364EA0 00361A80  80 78 00 08 */	lwz r3, 8(r24)
    /* 80364EA4 00361A84  38 9D 00 00 */	addi r4, r29, 0
    /* 80364EA8 00361A88  38 BE 00 00 */	addi r5, r30, 0
    /* 80364EAC 00361A8C  38 DF 00 00 */	addi r6, r31, 0
    /* 80364EB0 00361A90  38 E1 00 7C */	addi r7, r1, 0x7c
    /* 80364EB4 00361A94  4B FF F8 41 */	bl TObjForeachAnim
lbl_80364EB8:
    /* 80364EB8 00361A98  2C 19 00 00 */	cmpwi r25, 0
    /* 80364EBC 00361A9C  80 9B 00 0C */	lwz r4, 0xc(r27)
    /* 80364EC0 00361AA0  41 82 00 48 */	beq lbl_80364F08
    /* 80364EC4 00361AA4  28 04 00 00 */	cmplwi r4, 0
    /* 80364EC8 00361AA8  41 82 00 40 */	beq lbl_80364F08
    /* 80364ECC 00361AAC  A0 04 00 0C */	lhz r0, 0xc(r4)
    /* 80364ED0 00361AB0  54 00 04 A6 */	rlwinm r0, r0, 0, 0x12, 0x13
    /* 80364ED4 00361AB4  2C 00 10 00 */	cmpwi r0, 0x1000
    /* 80364ED8 00361AB8  40 82 00 30 */	bne lbl_80364F08
    /* 80364EDC 00361ABC  80 64 00 14 */	lwz r3, 0x14(r4)
    /* 80364EE0 00361AC0  28 03 00 00 */	cmplwi r3, 0
    /* 80364EE4 00361AC4  41 82 00 24 */	beq lbl_80364F08
    /* 80364EE8 00361AC8  80 63 00 20 */	lwz r3, 0x20(r3)
    /* 80364EEC 00361ACC  28 03 00 00 */	cmplwi r3, 0
    /* 80364EF0 00361AD0  41 82 00 18 */	beq lbl_80364F08
    /* 80364EF4 00361AD4  38 DE 00 00 */	addi r6, r30, 0
    /* 80364EF8 00361AD8  38 FF 00 00 */	addi r7, r31, 0
    /* 80364EFC 00361ADC  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364F00 00361AE0  38 A0 00 09 */	li r5, 9
    /* 80364F04 00361AE4  4B FF F6 D5 */	bl callbackForeachFunc
lbl_80364F08:
    /* 80364F08 00361AE8  83 7B 00 04 */	lwz r27, 4(r27)
lbl_80364F0C:
    /* 80364F0C 00361AEC  28 1B 00 00 */	cmplwi r27, 0
    /* 80364F10 00361AF0  40 82 FF 2C */	bne lbl_80364E3C
    /* 80364F14 00361AF4  48 00 03 E4 */	b lbl_803652F8
    /* 80364F18 00361AF8  28 1B 00 00 */	cmplwi r27, 0
    /* 80364F1C 00361AFC  41 82 03 DC */	beq lbl_803652F8
    /* 80364F20 00361B00  57 A0 06 31 */	rlwinm. r0, r29, 0, 0x18, 0x18
    /* 80364F24 00361B04  41 82 00 28 */	beq lbl_80364F4C
    /* 80364F28 00361B08  80 7B 00 14 */	lwz r3, 0x14(r27)
    /* 80364F2C 00361B0C  28 03 00 00 */	cmplwi r3, 0
    /* 80364F30 00361B10  41 82 00 1C */	beq lbl_80364F4C
    /* 80364F34 00361B14  38 9B 00 00 */	addi r4, r27, 0
    /* 80364F38 00361B18  38 DE 00 00 */	addi r6, r30, 0
    /* 80364F3C 00361B1C  38 FF 00 00 */	addi r7, r31, 0
    /* 80364F40 00361B20  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364F44 00361B24  38 A0 00 08 */	li r5, 8
    /* 80364F48 00361B28  4B FF F6 91 */	bl callbackForeachFunc
lbl_80364F4C:
    /* 80364F4C 00361B2C  83 7B 00 08 */	lwz r27, 8(r27)
    /* 80364F50 00361B30  57 B9 05 6A */	rlwinm r25, r29, 0, 0x15, 0x15
    /* 80364F54 00361B34  48 00 00 34 */	b lbl_80364F88
lbl_80364F58:
    /* 80364F58 00361B38  2C 19 00 00 */	cmpwi r25, 0
    /* 80364F5C 00361B3C  41 82 00 28 */	beq lbl_80364F84
    /* 80364F60 00361B40  80 7B 00 64 */	lwz r3, 0x64(r27)
    /* 80364F64 00361B44  28 03 00 00 */	cmplwi r3, 0
    /* 80364F68 00361B48  41 82 00 1C */	beq lbl_80364F84
    /* 80364F6C 00361B4C  38 9B 00 00 */	addi r4, r27, 0
    /* 80364F70 00361B50  38 DE 00 00 */	addi r6, r30, 0
    /* 80364F74 00361B54  38 FF 00 00 */	addi r7, r31, 0
    /* 80364F78 00361B58  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364F7C 00361B5C  38 A0 00 0B */	li r5, 0xb
    /* 80364F80 00361B60  4B FF F6 59 */	bl callbackForeachFunc
lbl_80364F84:
    /* 80364F84 00361B64  83 7B 00 08 */	lwz r27, 8(r27)
lbl_80364F88:
    /* 80364F88 00361B68  28 1B 00 00 */	cmplwi r27, 0
    /* 80364F8C 00361B6C  40 82 FF CC */	bne lbl_80364F58
    /* 80364F90 00361B70  48 00 03 68 */	b lbl_803652F8
    /* 80364F94 00361B74  57 A0 05 EF */	rlwinm. r0, r29, 0, 0x17, 0x17
    /* 80364F98 00361B78  41 82 03 60 */	beq lbl_803652F8
    /* 80364F9C 00361B7C  28 1B 00 00 */	cmplwi r27, 0
    /* 80364FA0 00361B80  41 82 03 58 */	beq lbl_803652F8
    /* 80364FA4 00361B84  A0 1B 00 0C */	lhz r0, 0xc(r27)
    /* 80364FA8 00361B88  54 00 04 A6 */	rlwinm r0, r0, 0, 0x12, 0x13
    /* 80364FAC 00361B8C  2C 00 10 00 */	cmpwi r0, 0x1000
    /* 80364FB0 00361B90  40 82 03 48 */	bne lbl_803652F8
    /* 80364FB4 00361B94  80 7B 00 14 */	lwz r3, 0x14(r27)
    /* 80364FB8 00361B98  28 03 00 00 */	cmplwi r3, 0
    /* 80364FBC 00361B9C  41 82 03 3C */	beq lbl_803652F8
    /* 80364FC0 00361BA0  80 63 00 20 */	lwz r3, 0x20(r3)
    /* 80364FC4 00361BA4  28 03 00 00 */	cmplwi r3, 0
    /* 80364FC8 00361BA8  41 82 03 30 */	beq lbl_803652F8
    /* 80364FCC 00361BAC  38 9B 00 00 */	addi r4, r27, 0
    /* 80364FD0 00361BB0  38 DE 00 00 */	addi r6, r30, 0
    /* 80364FD4 00361BB4  38 FF 00 00 */	addi r7, r31, 0
    /* 80364FD8 00361BB8  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80364FDC 00361BBC  38 A0 00 09 */	li r5, 9
    /* 80364FE0 00361BC0  4B FF F5 F9 */	bl callbackForeachFunc
    /* 80364FE4 00361BC4  48 00 03 14 */	b lbl_803652F8
    /* 80364FE8 00361BC8  57 B9 05 6A */	rlwinm r25, r29, 0, 0x15, 0x15
    /* 80364FEC 00361BCC  48 00 00 34 */	b lbl_80365020
lbl_80364FF0:
    /* 80364FF0 00361BD0  2C 19 00 00 */	cmpwi r25, 0
    /* 80364FF4 00361BD4  41 82 00 28 */	beq lbl_8036501C
    /* 80364FF8 00361BD8  80 7B 00 64 */	lwz r3, 0x64(r27)
    /* 80364FFC 00361BDC  28 03 00 00 */	cmplwi r3, 0
    /* 80365000 00361BE0  41 82 00 1C */	beq lbl_8036501C
    /* 80365004 00361BE4  38 9B 00 00 */	addi r4, r27, 0
    /* 80365008 00361BE8  38 DE 00 00 */	addi r6, r30, 0
    /* 8036500C 00361BEC  38 FF 00 00 */	addi r7, r31, 0
    /* 80365010 00361BF0  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80365014 00361BF4  38 A0 00 0B */	li r5, 0xb
    /* 80365018 00361BF8  4B FF F5 C1 */	bl callbackForeachFunc
lbl_8036501C:
    /* 8036501C 00361BFC  83 7B 00 08 */	lwz r27, 8(r27)
lbl_80365020:
    /* 80365020 00361C00  28 1B 00 00 */	cmplwi r27, 0
    /* 80365024 00361C04  40 82 FF CC */	bne lbl_80364FF0
    /* 80365028 00361C08  48 00 02 D0 */	b lbl_803652F8
    /* 8036502C 00361C0C  57 B9 06 72 */	rlwinm r25, r29, 0, 0x19, 0x19
    /* 80365030 00361C10  57 BA 05 28 */	rlwinm r26, r29, 0, 0x14, 0x14
    /* 80365034 00361C14  48 00 00 D4 */	b lbl_80365108
lbl_80365038:
    /* 80365038 00361C18  2C 19 00 00 */	cmpwi r25, 0
    /* 8036503C 00361C1C  41 82 00 28 */	beq lbl_80365064
    /* 80365040 00361C20  80 7B 00 48 */	lwz r3, 0x48(r27)
    /* 80365044 00361C24  28 03 00 00 */	cmplwi r3, 0
    /* 80365048 00361C28  41 82 00 1C */	beq lbl_80365064
    /* 8036504C 00361C2C  38 9B 00 00 */	addi r4, r27, 0
    /* 80365050 00361C30  38 DE 00 00 */	addi r6, r30, 0
    /* 80365054 00361C34  38 FF 00 00 */	addi r7, r31, 0
    /* 80365058 00361C38  39 01 00 7C */	addi r8, r1, 0x7c
    /* 8036505C 00361C3C  38 A0 00 07 */	li r5, 7
    /* 80365060 00361C40  4B FF F5 79 */	bl callbackForeachFunc
lbl_80365064:
    /* 80365064 00361C44  83 1B 00 18 */	lwz r24, 0x18(r27)
    /* 80365068 00361C48  28 18 00 00 */	cmplwi r24, 0
    /* 8036506C 00361C4C  41 82 00 48 */	beq lbl_803650B4
    /* 80365070 00361C50  2C 1A 00 00 */	cmpwi r26, 0
    /* 80365074 00361C54  41 82 00 28 */	beq lbl_8036509C
    /* 80365078 00361C58  80 78 00 18 */	lwz r3, 0x18(r24)
    /* 8036507C 00361C5C  28 03 00 00 */	cmplwi r3, 0
    /* 80365080 00361C60  41 82 00 1C */	beq lbl_8036509C
    /* 80365084 00361C64  38 98 00 00 */	addi r4, r24, 0
    /* 80365088 00361C68  38 DE 00 00 */	addi r6, r30, 0
    /* 8036508C 00361C6C  38 FF 00 00 */	addi r7, r31, 0
    /* 80365090 00361C70  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80365094 00361C74  38 A0 00 0C */	li r5, 0xc
    /* 80365098 00361C78  4B FF F5 41 */	bl callbackForeachFunc
lbl_8036509C:
    /* 8036509C 00361C7C  80 78 00 1C */	lwz r3, 0x1c(r24)
    /* 803650A0 00361C80  38 9D 00 00 */	addi r4, r29, 0
    /* 803650A4 00361C84  38 BE 00 00 */	addi r5, r30, 0
    /* 803650A8 00361C88  38 DF 00 00 */	addi r6, r31, 0
    /* 803650AC 00361C8C  38 E1 00 7C */	addi r7, r1, 0x7c
    /* 803650B0 00361C90  4B FF F6 B9 */	bl RObjForeachAnim
lbl_803650B4:
    /* 803650B4 00361C94  83 1B 00 1C */	lwz r24, 0x1c(r27)
    /* 803650B8 00361C98  28 18 00 00 */	cmplwi r24, 0
    /* 803650BC 00361C9C  41 82 00 48 */	beq lbl_80365104
    /* 803650C0 00361CA0  2C 1A 00 00 */	cmpwi r26, 0
    /* 803650C4 00361CA4  41 82 00 28 */	beq lbl_803650EC
    /* 803650C8 00361CA8  80 78 00 18 */	lwz r3, 0x18(r24)
    /* 803650CC 00361CAC  28 03 00 00 */	cmplwi r3, 0
    /* 803650D0 00361CB0  41 82 00 1C */	beq lbl_803650EC
    /* 803650D4 00361CB4  38 98 00 00 */	addi r4, r24, 0
    /* 803650D8 00361CB8  38 DE 00 00 */	addi r6, r30, 0
    /* 803650DC 00361CBC  38 FF 00 00 */	addi r7, r31, 0
    /* 803650E0 00361CC0  39 01 00 7C */	addi r8, r1, 0x7c
    /* 803650E4 00361CC4  38 A0 00 0C */	li r5, 0xc
    /* 803650E8 00361CC8  4B FF F4 F1 */	bl callbackForeachFunc
lbl_803650EC:
    /* 803650EC 00361CCC  80 78 00 1C */	lwz r3, 0x1c(r24)
    /* 803650F0 00361CD0  38 9D 00 00 */	addi r4, r29, 0
    /* 803650F4 00361CD4  38 BE 00 00 */	addi r5, r30, 0
    /* 803650F8 00361CD8  38 DF 00 00 */	addi r6, r31, 0
    /* 803650FC 00361CDC  38 E1 00 7C */	addi r7, r1, 0x7c
    /* 80365100 00361CE0  4B FF F6 69 */	bl RObjForeachAnim
lbl_80365104:
    /* 80365104 00361CE4  83 7B 00 0C */	lwz r27, 0xc(r27)
lbl_80365108:
    /* 80365108 00361CE8  28 1B 00 00 */	cmplwi r27, 0
    /* 8036510C 00361CEC  40 82 FF 2C */	bne lbl_80365038
    /* 80365110 00361CF0  48 00 01 E8 */	b lbl_803652F8
    /* 80365114 00361CF4  28 1B 00 00 */	cmplwi r27, 0
    /* 80365118 00361CF8  41 82 01 E0 */	beq lbl_803652F8
    /* 8036511C 00361CFC  57 A0 07 BD */	rlwinm. r0, r29, 0, 0x1e, 0x1e
    /* 80365120 00361D00  41 82 00 28 */	beq lbl_80365148
    /* 80365124 00361D04  80 7B 00 84 */	lwz r3, 0x84(r27)
    /* 80365128 00361D08  28 03 00 00 */	cmplwi r3, 0
    /* 8036512C 00361D0C  41 82 00 1C */	beq lbl_80365148
    /* 80365130 00361D10  38 9B 00 00 */	addi r4, r27, 0
    /* 80365134 00361D14  38 DE 00 00 */	addi r6, r30, 0
    /* 80365138 00361D18  38 FF 00 00 */	addi r7, r31, 0
    /* 8036513C 00361D1C  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80365140 00361D20  38 A0 00 02 */	li r5, 2
    /* 80365144 00361D24  4B FF F4 95 */	bl callbackForeachFunc
lbl_80365148:
    /* 80365148 00361D28  83 1B 00 24 */	lwz r24, 0x24(r27)
    /* 8036514C 00361D2C  28 18 00 00 */	cmplwi r24, 0
    /* 80365150 00361D30  41 82 00 48 */	beq lbl_80365198
    /* 80365154 00361D34  57 A0 05 29 */	rlwinm. r0, r29, 0, 0x14, 0x14
    /* 80365158 00361D38  41 82 00 28 */	beq lbl_80365180
    /* 8036515C 00361D3C  80 78 00 18 */	lwz r3, 0x18(r24)
    /* 80365160 00361D40  28 03 00 00 */	cmplwi r3, 0
    /* 80365164 00361D44  41 82 00 1C */	beq lbl_80365180
    /* 80365168 00361D48  38 98 00 00 */	addi r4, r24, 0
    /* 8036516C 00361D4C  38 DE 00 00 */	addi r6, r30, 0
    /* 80365170 00361D50  38 FF 00 00 */	addi r7, r31, 0
    /* 80365174 00361D54  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80365178 00361D58  38 A0 00 0C */	li r5, 0xc
    /* 8036517C 00361D5C  4B FF F4 5D */	bl callbackForeachFunc
lbl_80365180:
    /* 80365180 00361D60  80 78 00 1C */	lwz r3, 0x1c(r24)
    /* 80365184 00361D64  38 9D 00 00 */	addi r4, r29, 0
    /* 80365188 00361D68  38 BE 00 00 */	addi r5, r30, 0
    /* 8036518C 00361D6C  38 DF 00 00 */	addi r6, r31, 0
    /* 80365190 00361D70  38 E1 00 7C */	addi r7, r1, 0x7c
    /* 80365194 00361D74  4B FF F5 D5 */	bl RObjForeachAnim
lbl_80365198:
    /* 80365198 00361D78  83 1B 00 28 */	lwz r24, 0x28(r27)
    /* 8036519C 00361D7C  28 18 00 00 */	cmplwi r24, 0
    /* 803651A0 00361D80  41 82 01 58 */	beq lbl_803652F8
    /* 803651A4 00361D84  57 A0 05 29 */	rlwinm. r0, r29, 0, 0x14, 0x14
    /* 803651A8 00361D88  41 82 00 28 */	beq lbl_803651D0
    /* 803651AC 00361D8C  80 78 00 18 */	lwz r3, 0x18(r24)
    /* 803651B0 00361D90  28 03 00 00 */	cmplwi r3, 0
    /* 803651B4 00361D94  41 82 00 1C */	beq lbl_803651D0
    /* 803651B8 00361D98  38 98 00 00 */	addi r4, r24, 0
    /* 803651BC 00361D9C  38 DE 00 00 */	addi r6, r30, 0
    /* 803651C0 00361DA0  38 FF 00 00 */	addi r7, r31, 0
    /* 803651C4 00361DA4  39 01 00 7C */	addi r8, r1, 0x7c
    /* 803651C8 00361DA8  38 A0 00 0C */	li r5, 0xc
    /* 803651CC 00361DAC  4B FF F4 0D */	bl callbackForeachFunc
lbl_803651D0:
    /* 803651D0 00361DB0  80 78 00 1C */	lwz r3, 0x1c(r24)
    /* 803651D4 00361DB4  38 9D 00 00 */	addi r4, r29, 0
    /* 803651D8 00361DB8  38 BE 00 00 */	addi r5, r30, 0
    /* 803651DC 00361DBC  38 DF 00 00 */	addi r6, r31, 0
    /* 803651E0 00361DC0  38 E1 00 7C */	addi r7, r1, 0x7c
    /* 803651E4 00361DC4  4B FF F5 85 */	bl RObjForeachAnim
    /* 803651E8 00361DC8  48 00 01 10 */	b lbl_803652F8
    /* 803651EC 00361DCC  57 B9 05 AC */	rlwinm r25, r29, 0, 0x16, 0x16
    /* 803651F0 00361DD0  48 00 00 34 */	b lbl_80365224
lbl_803651F4:
    /* 803651F4 00361DD4  2C 19 00 00 */	cmpwi r25, 0
    /* 803651F8 00361DD8  41 82 00 28 */	beq lbl_80365220
    /* 803651FC 00361DDC  80 7B 00 18 */	lwz r3, 0x18(r27)
    /* 80365200 00361DE0  28 03 00 00 */	cmplwi r3, 0
    /* 80365204 00361DE4  41 82 00 1C */	beq lbl_80365220
    /* 80365208 00361DE8  38 9B 00 00 */	addi r4, r27, 0
    /* 8036520C 00361DEC  38 DE 00 00 */	addi r6, r30, 0
    /* 80365210 00361DF0  38 FF 00 00 */	addi r7, r31, 0
    /* 80365214 00361DF4  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80365218 00361DF8  38 A0 00 0A */	li r5, 0xa
    /* 8036521C 00361DFC  4B FF F3 BD */	bl callbackForeachFunc
lbl_80365220:
    /* 80365220 00361E00  83 7B 00 00 */	lwz r27, 0(r27)
lbl_80365224:
    /* 80365224 00361E04  28 1B 00 00 */	cmplwi r27, 0
    /* 80365228 00361E08  40 82 FF CC */	bne lbl_803651F4
    /* 8036522C 00361E0C  48 00 00 CC */	b lbl_803652F8
    /* 80365230 00361E10  28 1B 00 00 */	cmplwi r27, 0
    /* 80365234 00361E14  41 82 00 C4 */	beq lbl_803652F8
    /* 80365238 00361E18  57 A0 05 29 */	rlwinm. r0, r29, 0, 0x14, 0x14
    /* 8036523C 00361E1C  41 82 00 28 */	beq lbl_80365264
    /* 80365240 00361E20  80 7B 00 18 */	lwz r3, 0x18(r27)
    /* 80365244 00361E24  28 03 00 00 */	cmplwi r3, 0
    /* 80365248 00361E28  41 82 00 1C */	beq lbl_80365264
    /* 8036524C 00361E2C  38 9B 00 00 */	addi r4, r27, 0
    /* 80365250 00361E30  38 DE 00 00 */	addi r6, r30, 0
    /* 80365254 00361E34  38 FF 00 00 */	addi r7, r31, 0
    /* 80365258 00361E38  39 01 00 7C */	addi r8, r1, 0x7c
    /* 8036525C 00361E3C  38 A0 00 0C */	li r5, 0xc
    /* 80365260 00361E40  4B FF F3 79 */	bl callbackForeachFunc
lbl_80365264:
    /* 80365264 00361E44  83 7B 00 1C */	lwz r27, 0x1c(r27)
    /* 80365268 00361E48  57 B9 05 AC */	rlwinm r25, r29, 0, 0x16, 0x16
    /* 8036526C 00361E4C  48 00 00 34 */	b lbl_803652A0
lbl_80365270:
    /* 80365270 00361E50  2C 19 00 00 */	cmpwi r25, 0
    /* 80365274 00361E54  41 82 00 28 */	beq lbl_8036529C
    /* 80365278 00361E58  80 7B 00 18 */	lwz r3, 0x18(r27)
    /* 8036527C 00361E5C  28 03 00 00 */	cmplwi r3, 0
    /* 80365280 00361E60  41 82 00 1C */	beq lbl_8036529C
    /* 80365284 00361E64  38 9B 00 00 */	addi r4, r27, 0
    /* 80365288 00361E68  38 DE 00 00 */	addi r6, r30, 0
    /* 8036528C 00361E6C  38 FF 00 00 */	addi r7, r31, 0
    /* 80365290 00361E70  39 01 00 7C */	addi r8, r1, 0x7c
    /* 80365294 00361E74  38 A0 00 0A */	li r5, 0xa
    /* 80365298 00361E78  4B FF F3 41 */	bl callbackForeachFunc
lbl_8036529C:
    /* 8036529C 00361E7C  83 7B 00 00 */	lwz r27, 0(r27)
lbl_803652A0:
    /* 803652A0 00361E80  28 1B 00 00 */	cmplwi r27, 0
    /* 803652A4 00361E84  40 82 FF CC */	bne lbl_80365270
    /* 803652A8 00361E88  48 00 00 50 */	b lbl_803652F8
    /* 803652AC 00361E8C  57 A0 06 F7 */	rlwinm. r0, r29, 0, 0x1b, 0x1b
    /* 803652B0 00361E90  41 82 00 48 */	beq lbl_803652F8
    /* 803652B4 00361E94  28 1B 00 00 */	cmplwi r27, 0
    /* 803652B8 00361E98  41 82 00 40 */	beq lbl_803652F8
    /* 803652BC 00361E9C  80 7B 00 1C */	lwz r3, 0x1c(r27)
    /* 803652C0 00361EA0  28 03 00 00 */	cmplwi r3, 0
    /* 803652C4 00361EA4  41 82 00 34 */	beq lbl_803652F8
    /* 803652C8 00361EA8  38 9B 00 00 */	addi r4, r27, 0
    /* 803652CC 00361EAC  38 DE 00 00 */	addi r6, r30, 0
    /* 803652D0 00361EB0  38 FF 00 00 */	addi r7, r31, 0
    /* 803652D4 00361EB4  39 01 00 7C */	addi r8, r1, 0x7c
    /* 803652D8 00361EB8  38 A0 00 05 */	li r5, 5
    /* 803652DC 00361EBC  4B FF F2 FD */	bl callbackForeachFunc
    /* 803652E0 00361EC0  48 00 00 18 */	b lbl_803652F8
lbl_803652E4:
    /* 803652E4 00361EC4  3C 60 80 40 */	lis r3, lbl_8040603C@ha
    /* 803652E8 00361EC8  38 A3 60 3C */	addi r5, r3, lbl_8040603C@l
    /* 803652EC 00361ECC  38 6D A6 68 */	addi r3, r13, lbl_804D5D08
    /* 803652F0 00361ED0  38 80 03 5E */	li r4, 0x35e
    /* 803652F4 00361ED4  48 02 2F 85 */	bl HSD_Panic
lbl_803652F8:
    /* 803652F8 00361ED8  BB 01 00 90 */	lmw r24, 0x90(r1)
    /* 803652FC 00361EDC  80 01 00 B4 */	lwz r0, 0xb4(r1)
    /* 80365300 00361EE0  38 21 00 B0 */	addi r1, r1, 0xb0
    /* 80365304 00361EE4  7C 08 03 A6 */	mtlr r0
    /* 80365308 00361EE8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate)
{
    if (!aobj)
        return;
    aobj->framerate = rate;
}

void HSD_AObjSetRewindFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj)
        return;
    aobj->rewind_frame = frame;
}

void HSD_AObjSetEndFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj)
        return;
    aobj->end_frame = frame;
}

void HSD_AObjSetCurrentFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj)
        return;

    if (!(aobj->flags & AOBJ_NO_ANIM) && aobj) {
        aobj->curr_frame = frame;
        aobj->flags = (aobj->flags & 0xBFFFFFFF) | AOBJ_FIRST_PLAY;
        HSD_FObjReqAnimAll(aobj->fobj, frame);
    }
}

void _HSD_AObjForgetMemory(void)
{
    endcallback_list = NULL;
}
