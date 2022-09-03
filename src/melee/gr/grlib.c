#include <melee/gr/grlib.h>
#include <sysdolphin/baselib/psappsrt.h>

extern StageInfo stage_info;
extern u8 lbl_804D7849;
extern struct _UnkEffectStruct* lbl_804D78FC;

static Vec lbl_8049EF58[6];

BOOL func_801C96E8(HSD_GObj* arg0)
{
    Map* map = arg0->user_data;
    return map->x10_flags.b4;
}



UnkGeneratorStruct* func_8039F05C(s8, s8, s32);
UnkGeneratorMember* psAddGeneratorAppSRT_begin(UnkGeneratorStruct*, s32);

UnkGeneratorStruct* func_801C96F8(s32 arg0, s8 arg1, S32Vec* arg2)
{
    UnkGeneratorStruct* temp_r3;
    UnkGeneratorMember* phi_r30;
    f32 scale;

    temp_r3 = func_8039F05C(0, arg1, arg0);
    if (temp_r3 != NULL) {
        phi_r30 = temp_r3->x54;
        if (phi_r30 == NULL) {
            phi_r30 = psAddGeneratorAppSRT_begin(temp_r3, 1);
        } else {
            phi_r30->xA2 = 0;
        }
        if (phi_r30 == NULL) {
            func_8039D4DC(temp_r3);
            return NULL;
        }
        phi_r30->x8 = *arg2;
        scale = func_801C0498();
        phi_r30->x24 *= scale;
        phi_r30->x28 *= scale;
        phi_r30->x2C *= scale;
        temp_r3->x2C = 0.0f;
        temp_r3->x28 = 0.0f;
        temp_r3->x24 = 0.0f;
    }
    return temp_r3;
}

void func_801C97DC(s32 arg0, s32 arg1, s32 arg2)
{
    func_8039F6CC(0, arg1, arg0, arg2);
}

void func_801C9808(s32 arg0, s32 arg1, s32 arg2)
{
    func_8039EFAC(0, arg1, arg0, arg2);
}

void func_801C9834(s32 arg0)
{
    func_8039D4DC(arg0);
}

void func_801C9854(s32 arg0)
{
    func_8039D5DC(arg0);
}

typedef struct _UnkEffectStruct { // MexTK: ptclGen (particle generator)
    struct _UnkEffectStruct* next;
    u8 x4_fill[0xC];
    HSD_JObj* x10_jobj;
    u16 x14_fill;
    u16 x16_flags;
} UnkEffectStruct;

void func_801C9874(UnkEffectStruct* arg0)
{
    arg0->x16_flags |= 0x80;
    func_8039D4DC(arg0);
}

void func_801C98A0(HSD_JObj* jobj)
{
    UnkEffectStruct* cur, *next;

    if (jobj == NULL) {
        return;
    }

    for (cur = lbl_804D78FC; cur != NULL; cur = next) {
        next = cur->next;
        if (cur->x10_jobj == jobj) {
            cur->x16_flags |= 0x80;
            func_8039D4DC(cur);
        }
    }
}

inline HSD_JObj* jobj_child(HSD_JObj* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->child;
}

inline HSD_JObj* jobj_next(HSD_JObj* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}

void func_801C9908(HSD_JObj* jobj)
{
    UnkEffectStruct* cur;
    UnkEffectStruct* next;

    if (jobj == NULL) {
        return;
    }

    for (cur = lbl_804D78FC; cur != NULL; cur = next) {
        next = cur->next;
        if (cur->x10_jobj == jobj) {
            cur->x16_flags |= 0x80;
            func_8039D4DC(cur);
        }
    }

    if (jobj->flags & JOBJ_INSTANCE) {
        return;
    }

    for (jobj = jobj_child(jobj); jobj != NULL; jobj = jobj_next(jobj)) {
        func_801C9908(jobj);
    }
}

void func_801C99C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg3 != 0) {
        func_8039EFAC(0, arg0, arg1, arg2);
    } else {
        func_8039F6CC(0, arg0, arg1, arg2);
    }
}

Vec* func_801C9A10(void)
{
    func_801C2D24(0, &lbl_8049EF58[0]);
    func_801C2D24(1, &lbl_8049EF58[1]);
    func_801C2D24(2, &lbl_8049EF58[2]);
    func_801C2D24(3, &lbl_8049EF58[3]);
    return lbl_8049EF58;
}

void func_801C9A70(s32 arg0, Vec* v)
{
    s32 i;
    switch (arg0) {
    case 0:
        i = 0;
        break;
    case 1:
        i = 1;
        break;
    case 2:
        i = 2;
        break;
    case 3:
        i = 3;
        break;
    default:
        assert_line(290, 0);
    }
    *v = lbl_8049EF58[i];
}

typedef struct _UnkAnimStruct {
    void* x0_data;
    s32 x4_size;
} UnkAnimStruct;

void func_801C9B20(void* arg1, UnkAnimStruct* arg2, void* arg3)
{
    func_8000FD48(arg1, arg3, arg2->x4_size);
    func_80011710(arg2, arg3);
}

void func_801C9B6C(void* arg0)
{
    func_8000FD18(arg0);
}

void func_801C9B8C(void* arg0)
{
    func_8001044C(arg0, 0, 0, 0.0f, 0, 0, 0, 0);
}

static void func_801C9BC8(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObjAnimAll(jobj);
    func_8002A278(HSD_JObjGetTranslationX(jobj), HSD_JObjGetTranslationY(jobj));
}

static void func_801C9C40(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_AObj* aobj = jobj->aobj;

    HSD_JObjAnimAll(jobj);
    func_8002A278(HSD_JObjGetTranslationX(jobj), HSD_JObjGetTranslationY(jobj));

    if (aobj == NULL || aobj->flags & 0x40000000) {
        func_80390228(gobj);
    }
}

HSD_GObj* func_801C9CEC(s32 idx1)
{
    u8 tmp;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 idx0;

    if (idx1 == 1) {
        idx0 = 0;
    } else if (idx1 == 2) {
        idx0 = 1;
    } else if (idx1 == 3) {
        idx0 = 2;
    } else if (idx1 == 4) {
        idx0 = 3;
    } else {
        return NULL;
    }

    if (stage_info.x6CC == NULL) {
        return NULL;
    }
    tmp = idx1;
    gobj = func_803901F0(3, 18, tmp);
    jobj = HSD_JObjLoadJoint(stage_info.x6CC->joint);

    func_80390A70(gobj, lbl_804D7849, jobj);
    if (idx1 == 1) {
        func_8038FD54(gobj, func_801C9BC8, 1);
    } else {
        func_8038FD54(gobj, func_801C9C40, 1);
    }

    HSD_JObjAddAnimAll(jobj, stage_info.x6CC->anims[idx0], NULL, NULL);
    HSD_JObjReqAnimAll(jobj, 0);
    if (idx1 == 1) {
        HSD_ForeachAnim(jobj, 6, 0x20, HSD_AObjSetFlags, 3, 0x20000000);
    }
    return gobj;
}

s16 func_801C9E40(void)
{
    return stage_info.x708;
}

void func_801C9E50(s16 val)
{
    stage_info.x708 = val;
}

BOOL func_801C9E60(Vec* v)
{
    s32 id = stage_info.internal_stage_id;
    if (id == RCRUISE) {
        func_80201918(v);
        return TRUE;
    }
    if (id == BIGBLUE) {
        func_801EF7D8(v);
        return TRUE;
    }
    if (id == ICEMTN) {
        func_801FA728(v);
        return TRUE;
    }
    v->z = 0;
    v->y = 0;
    v->x = 0;
    return FALSE;
}

// Only called from yorster and inishie1
asm BOOL func_801C9EE8()
{
    nofralloc
/* 801C9EE8 001C6AC8  7C 08 02 A6 */	mflr r0
/* 801C9EEC 001C6ACC  90 01 00 04 */	stw r0, 4(r1)
/* 801C9EF0 001C6AD0  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 801C9EF4 001C6AD4  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 801C9EF8 001C6AD8  FF E0 08 90 */	fmr f31, f1
/* 801C9EFC 001C6ADC  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 801C9F00 001C6AE0  DB A1 00 40 */	stfd f29, 0x40(r1)
/* 801C9F04 001C6AE4  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 801C9F08 001C6AE8  93 C1 00 38 */	stw r30, 0x38(r1)
/* 801C9F0C 001C6AEC  7C 7E 1B 78 */	mr r30, r3
/* 801C9F10 001C6AF0  80 8D C1 8C */	lwz r4, lbl_804D782C
/* 801C9F14 001C6AF4  C0 A2 B3 AC */	lfs f5, 0.5f
/* 801C9F18 001C6AF8  80 A4 00 20 */	lwz r5, 0x20(r4)
/* 801C9F1C 001C6AFC  C0 02 B3 A8 */	lfs f0, 0.0f
/* 801C9F20 001C6B00  48 00 00 A0 */	b lbl_801C9FC0
lbl_801C9F24:
/* 801C9F24 001C6B04  80 65 00 2C */	lwz r3, 0x2c(r5)
/* 801C9F28 001C6B08  C0 3E 00 04 */	lfs f1, 4(r30)
/* 801C9F2C 001C6B0C  C0 C3 07 98 */	lfs f6, 0x798(r3)
/* 801C9F30 001C6B10  C0 83 07 A0 */	lfs f4, 0x7a0(r3)
/* 801C9F34 001C6B14  C0 43 06 F8 */	lfs f2, 0x6f8(r3)
/* 801C9F38 001C6B18  EC 66 20 2A */	fadds f3, f6, f4
/* 801C9F3C 001C6B1C  EC 86 20 28 */	fsubs f4, f6, f4
/* 801C9F40 001C6B20  EC 45 10 FA */	fmadds f2, f5, f3, f2
/* 801C9F44 001C6B24  EC 65 F9 3A */	fmadds f3, f5, f4, f31
/* 801C9F48 001C6B28  EC 22 08 28 */	fsubs f1, f2, f1
/* 801C9F4C 001C6B2C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801C9F50 001C6B30  40 80 00 08 */	bge lbl_801C9F58
/* 801C9F54 001C6B34  FC 20 08 50 */	fneg f1, f1
lbl_801C9F58:
/* 801C9F58 001C6B38  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 801C9F5C 001C6B3C  40 81 00 0C */	ble lbl_801C9F68
/* 801C9F60 001C6B40  38 00 00 00 */	li r0, 0
/* 801C9F64 001C6B44  48 00 00 48 */	b lbl_801C9FAC
lbl_801C9F68:
/* 801C9F68 001C6B48  C0 83 07 A4 */	lfs f4, 0x7a4(r3)
/* 801C9F6C 001C6B4C  C0 C3 07 AC */	lfs f6, 0x7ac(r3)
/* 801C9F70 001C6B50  C0 43 06 F4 */	lfs f2, 0x6f4(r3)
/* 801C9F74 001C6B54  EC 66 20 2A */	fadds f3, f6, f4
/* 801C9F78 001C6B58  C0 3E 00 00 */	lfs f1, 0(r30)
/* 801C9F7C 001C6B5C  EC 84 30 28 */	fsubs f4, f4, f6
/* 801C9F80 001C6B60  EC 45 10 FA */	fmadds f2, f5, f3, f2
/* 801C9F84 001C6B64  EC 65 F9 3A */	fmadds f3, f5, f4, f31
/* 801C9F88 001C6B68  EC 22 08 28 */	fsubs f1, f2, f1
/* 801C9F8C 001C6B6C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801C9F90 001C6B70  40 80 00 08 */	bge lbl_801C9F98
/* 801C9F94 001C6B74  FC 20 08 50 */	fneg f1, f1
lbl_801C9F98:
/* 801C9F98 001C6B78  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 801C9F9C 001C6B7C  40 81 00 0C */	ble lbl_801C9FA8
/* 801C9FA0 001C6B80  38 00 00 00 */	li r0, 0
/* 801C9FA4 001C6B84  48 00 00 08 */	b lbl_801C9FAC
lbl_801C9FA8:
/* 801C9FA8 001C6B88  38 00 00 01 */	li r0, 1
lbl_801C9FAC:
/* 801C9FAC 001C6B8C  2C 00 00 00 */	cmpwi r0, 0
/* 801C9FB0 001C6B90  41 82 00 0C */	beq lbl_801C9FBC
/* 801C9FB4 001C6B94  38 60 00 01 */	li r3, 1
/* 801C9FB8 001C6B98  48 00 00 D8 */	b lbl_801CA090
lbl_801C9FBC:
/* 801C9FBC 001C6B9C  80 A5 00 08 */	lwz r5, 8(r5)
lbl_801C9FC0:
/* 801C9FC0 001C6BA0  28 05 00 00 */	cmplwi r5, 0
/* 801C9FC4 001C6BA4  40 82 FF 60 */	bne lbl_801C9F24
/* 801C9FC8 001C6BA8  83 E4 00 24 */	lwz r31, 0x24(r4)
/* 801C9FCC 001C6BAC  C3 A2 B3 AC */	lfs f29, 0.5f
/* 801C9FD0 001C6BB0  C3 C2 B3 A8 */	lfs f30, 0.0f
/* 801C9FD4 001C6BB4  48 00 00 B0 */	b lbl_801CA084
lbl_801C9FD8:
/* 801C9FD8 001C6BB8  7F E3 FB 78 */	mr r3, r31
/* 801C9FDC 001C6BBC  48 0A 13 25 */	bl itGetKind
/* 801C9FE0 001C6BC0  2C 03 00 A0 */	cmpwi r3, 0xa0
/* 801C9FE4 001C6BC4  41 82 00 9C */	beq lbl_801CA080
/* 801C9FE8 001C6BC8  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 801C9FEC 001C6BCC  C0 1E 00 04 */	lfs f0, 4(r30)
/* 801C9FF0 001C6BD0  C0 83 04 20 */	lfs f4, 0x420(r3)
/* 801C9FF4 001C6BD4  C0 63 04 28 */	lfs f3, 0x428(r3)
/* 801C9FF8 001C6BD8  C0 23 03 80 */	lfs f1, 0x380(r3)
/* 801C9FFC 001C6BDC  EC 44 18 2A */	fadds f2, f4, f3
/* 801CA000 001C6BE0  EC 64 18 28 */	fsubs f3, f4, f3
/* 801CA004 001C6BE4  EC 3D 08 BA */	fmadds f1, f29, f2, f1
/* 801CA008 001C6BE8  EC 5D F8 FA */	fmadds f2, f29, f3, f31
/* 801CA00C 001C6BEC  EC 01 00 28 */	fsubs f0, f1, f0
/* 801CA010 001C6BF0  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 801CA014 001C6BF4  40 80 00 08 */	bge lbl_801CA01C
/* 801CA018 001C6BF8  FC 00 00 50 */	fneg f0, f0
lbl_801CA01C:
/* 801CA01C 001C6BFC  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 801CA020 001C6C00  40 81 00 0C */	ble lbl_801CA02C
/* 801CA024 001C6C04  38 00 00 00 */	li r0, 0
/* 801CA028 001C6C08  48 00 00 48 */	b lbl_801CA070
lbl_801CA02C:
/* 801CA02C 001C6C0C  C0 63 04 2C */	lfs f3, 0x42c(r3)
/* 801CA030 001C6C10  C0 83 04 34 */	lfs f4, 0x434(r3)
/* 801CA034 001C6C14  C0 23 03 7C */	lfs f1, 0x37c(r3)
/* 801CA038 001C6C18  EC 44 18 2A */	fadds f2, f4, f3
/* 801CA03C 001C6C1C  C0 1E 00 00 */	lfs f0, 0(r30)
/* 801CA040 001C6C20  EC 63 20 28 */	fsubs f3, f3, f4
/* 801CA044 001C6C24  EC 3D 08 BA */	fmadds f1, f29, f2, f1
/* 801CA048 001C6C28  EC 5D F8 FA */	fmadds f2, f29, f3, f31
/* 801CA04C 001C6C2C  EC 01 00 28 */	fsubs f0, f1, f0
/* 801CA050 001C6C30  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 801CA054 001C6C34  40 80 00 08 */	bge lbl_801CA05C
/* 801CA058 001C6C38  FC 00 00 50 */	fneg f0, f0
lbl_801CA05C:
/* 801CA05C 001C6C3C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 801CA060 001C6C40  40 81 00 0C */	ble lbl_801CA06C
/* 801CA064 001C6C44  38 00 00 00 */	li r0, 0
/* 801CA068 001C6C48  48 00 00 08 */	b lbl_801CA070
lbl_801CA06C:
/* 801CA06C 001C6C4C  38 00 00 01 */	li r0, 1
lbl_801CA070:
/* 801CA070 001C6C50  2C 00 00 00 */	cmpwi r0, 0
/* 801CA074 001C6C54  41 82 00 0C */	beq lbl_801CA080
/* 801CA078 001C6C58  38 60 00 01 */	li r3, 1
/* 801CA07C 001C6C5C  48 00 00 14 */	b lbl_801CA090
lbl_801CA080:
/* 801CA080 001C6C60  83 FF 00 08 */	lwz r31, 8(r31)
lbl_801CA084:
/* 801CA084 001C6C64  28 1F 00 00 */	cmplwi r31, 0
/* 801CA088 001C6C68  40 82 FF 50 */	bne lbl_801C9FD8
/* 801CA08C 001C6C6C  38 60 00 00 */	li r3, 0
lbl_801CA090:
/* 801CA090 001C6C70  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 801CA094 001C6C74  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 801CA098 001C6C78  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 801CA09C 001C6C7C  CB A1 00 40 */	lfd f29, 0x40(r1)
/* 801CA0A0 001C6C80  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 801CA0A4 001C6C84  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 801CA0A8 001C6C88  38 21 00 58 */	addi r1, r1, 0x58
/* 801CA0AC 001C6C8C  7C 08 03 A6 */	mtlr r0
/* 801CA0B0 001C6C90  4E 80 00 20 */	blr 
}
