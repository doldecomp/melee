#include <melee/ft/chara/ftPurin/ftpurin.h>

#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_005.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftparts.h>
#include <melee/gm/code_801601C4.h>
#include <melee/gr/grstadium.h>
#include <melee/it/item2.h>

/* static */ extern char* lbl_803D05B4[5];

void func_8013C2F8(void)
{
    lbl_8045A1E0[0] = NULL;
    lbl_8045A1E0[1] = NULL;
    lbl_8045A1E0[2] = NULL;
    lbl_8045A1E0[3] = NULL;
    lbl_8045A1E0[4] = NULL;
}

void ftPurin_OnDeath(HSD_GObj* fighter_gobj)
{
    func_80074A4C(fighter_gobj, 0, 0);
}

void ftPurin_OnUserDataRemove(HSD_GObj* fighter_gobj)
{
    func_8013C494(fighter_gobj);
}

void func_8013C360(HSD_GObj* fighter_gobj)
{
    s32 unused;

    HSD_Joint** joint_list = lbl_8045A1E0;
    Fighter* fp = fighter_gobj->user_data;

    if (lbl_803D05B4[fp->x619_costume_id]) {
        void** item_list = fp->x10C_ftData->x48_items;
        void** item_list_shifted = item_list[1];
        if (!joint_list[fp->x619_costume_id]) {
            UnkCostumeStruct* costume_list =
                CostumeListsForeachCharacter[fp->x4_fighterKind].costume_list;
            joint_list[fp->x619_costume_id] = HSD_ArchiveGetPublicAddress(
                costume_list[fp->x619_costume_id].x14_archive,
                lbl_803D05B4[fp->x619_costume_id]);
        }

        fp->sa.purin.x2244 = HSD_ObjAlloc(&lbl_80459080);
        func_80074148();
        fp->sa.purin.x223C = HSD_JObjLoadJoint(joint_list[fp->x619_costume_id]);
        fp->x2225_flag.bits.b2 = 1;
        func_80074170();
        func_80075650(fighter_gobj, fp->sa.purin.x223C, &fp->sa.purin.x2240);

        func_8007487C(&item_list_shifted[1], &fp->sa.purin.x2248,
                      fp->x619_costume_id, &fp->sa.purin.x2240,
                      &fp->sa.purin.x2240);
        func_8009DC54(fp);
        return;
    }

    fp->sa.purin.x223C = 0;
}

void func_8013C494(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_JObj* jobj = fp->sa.purin.x223C;

    if (jobj) {
        HSD_JObjRemoveAll(fp->sa.purin.x223C);
        fp->sa.purin.x223C = NULL;
        HSD_ObjFree(&lbl_80459080, fp->sa.purin.x2244);
        fp->sa.purin.x2244 = NULL;
    }
}

void func_8013C4F0(HSD_GObj* fighter_gobj, s32 arg1, Mtx vmtx)
{
    s32 unused[2];

    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.purin.x223C && fp->x2225_flag.bits.b2) {
        Mtx* mtx;
        HSD_JObj* jobj;
        HSD_JObj* bone_jobj = fp->x5E8_fighterBones[6].x0_jobj;
        HSD_JObjGetMtx(fp->x5E8_fighterBones[6].x0_jobj);
        mtx = (0, &bone_jobj->mtx);
        jobj = fp->sa.purin.x223C;
        HSD_JObjCopyMtx(fp->sa.purin.x223C, *mtx);
        jobj->flags |= 0x03800000;
        HSD_JObjSetMtxDirty(jobj);

        HSD_JObjDispAll(fp->sa.purin.x223C, vmtx, func_80390EB8(arg1), 0);
    }
}

void func_8013C614(Fighter* fp, s32 arg1, s32 arg2)
{
    if (fp->sa.purin.x223C) {
        if (arg2) {
            func_80074CA0(&fp->sa.purin.x2248, arg1, &fp->sa.purin.x2240);
            return;
        }

        func_80074D7C(&fp->sa.purin.x2248, arg1, &fp->sa.purin.x2240);
    }
}

void* func_8013C664(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.purin.x223C)
        return fp->sa.purin.x223C;

    return fighter_gobj;
}

void ftPurin_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    PUSH_ATTRS(fp, ftPurinAttributes);
    fp->x2222_flag.bits.b1 = 1;
    fp->x2D0 = fp->x2D4_specialAttributes;
    func_8013C360(fighter_gobj);
}

void ftPurin_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        switch (func_8026B320(fp->x1974_heldItem)) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            func_80070FB4(fighter_gobj, 0, 0);
            break;
        case 4:
            func_80070FB4(fighter_gobj, 0, 1);
            break;
        }
        if (bool) {
            func_80070C48(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x1974_heldItem) {
        if (!func_8026B2B4(fp->x1974_heldItem)) {
            func_80070CC4(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x1974_heldItem) {
        if (!func_8026B2B4(fp->x1974_heldItem)) {
            func_80070C48(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1)
{
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftPurin_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftPurinAttributes);
}

void ftPurin_OnKnockbackEnter(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftPurin_OnKnockbackExit(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8013C94C(void)
{ // clang-format off
    nofralloc
/* 8013C94C 0013952C  7C 08 02 A6 */	mflr r0
/* 8013C950 00139530  90 01 00 04 */	stw r0, 4(r1)
/* 8013C954 00139534  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013C958 00139538  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013C95C 0013953C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013C960 00139540  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8013C964 00139544  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8013C968 00139548  40 82 00 2C */	bne lbl_8013C994
/* 8013C96C 0013954C  80 BF 05 E8 */	lwz r5, 0x5e8(r31)
/* 8013C970 00139550  38 83 00 00 */	addi r4, r3, 0
/* 8013C974 00139554  4C C6 31 82 */	crclr 6
/* 8013C978 00139558  38 60 04 D6 */	li r3, 0x4d6
/* 8013C97C 0013955C  80 A5 00 50 */	lwz r5, 0x50(r5)
/* 8013C980 00139560  4B F2 34 5D */	bl ef_Spawn
/* 8013C984 00139564  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8013C988 00139568  38 60 00 01 */	li r3, 1
/* 8013C98C 0013956C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8013C990 00139570  98 1F 22 19 */	stb r0, 0x2219(r31)
lbl_8013C994:
/* 8013C994 00139574  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 8013C998 00139578  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 8013C99C 0013957C  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 8013C9A0 00139580  90 1F 21 D4 */	stw r0, 0x21d4(r31)
/* 8013C9A4 00139584  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 8013C9A8 00139588  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 8013C9AC 0013958C  38 00 00 00 */	li r0, 0
/* 8013C9B0 00139590  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8013C9B4 00139594  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013C9B8 00139598  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013C9BC 0013959C  38 21 00 18 */	addi r1, r1, 0x18
/* 8013C9C0 001395A0  7C 08 03 A6 */	mtlr r0
/* 8013C9C4 001395A4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern f32 const lbl_804D9C10;
extern f32 const lbl_804D9C14;
extern f32 const lbl_804D9C18;

#ifdef MWERKS_GEKKO
#pragma push
asm void ftPurin_SpecialHi_StartAction(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8013C9C8 001395A8  7C 08 02 A6 */	mflr r0
/* 8013C9CC 001395AC  90 01 00 04 */	stw r0, 4(r1)
/* 8013C9D0 001395B0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013C9D4 001395B4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013C9D8 001395B8  7C 7F 1B 78 */	mr r31, r3
/* 8013C9DC 001395BC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013C9E0 001395C0  C0 22 A2 30 */	lfs f1, lbl_804D9C10(r2)
/* 8013C9E4 001395C4  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 8013C9E8 001395C8  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013C9EC 001395CC  40 82 00 28 */	bne lbl_8013CA14
/* 8013C9F0 001395D0  C0 22 A2 34 */	lfs f1, lbl_804D9C14(r2)
/* 8013C9F4 001395D4  7F E3 FB 78 */	mr r3, r31
/* 8013C9F8 001395D8  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013C9FC 001395DC  38 80 01 6D */	li r4, 0x16d
/* 8013CA00 001395E0  FC 60 08 90 */	fmr f3, f1
/* 8013CA04 001395E4  38 A0 00 00 */	li r5, 0
/* 8013CA08 001395E8  38 C0 00 00 */	li r6, 0
/* 8013CA0C 001395EC  4B F2 C9 A1 */	bl Fighter_ActionStateChange_800693AC
/* 8013CA10 001395F0  48 00 00 24 */	b lbl_8013CA34
lbl_8013CA14:
/* 8013CA14 001395F4  C0 22 A2 34 */	lfs f1, lbl_804D9C14(r2)
/* 8013CA18 001395F8  7F E3 FB 78 */	mr r3, r31
/* 8013CA1C 001395FC  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013CA20 00139600  38 80 01 6F */	li r4, 0x16f
/* 8013CA24 00139604  FC 60 08 90 */	fmr f3, f1
/* 8013CA28 00139608  38 A0 00 00 */	li r5, 0
/* 8013CA2C 0013960C  38 C0 00 00 */	li r6, 0
/* 8013CA30 00139610  4B F2 C9 7D */	bl Fighter_ActionStateChange_800693AC
lbl_8013CA34:
/* 8013CA34 00139614  7F E3 FB 78 */	mr r3, r31
/* 8013CA38 00139618  4B F3 21 6D */	bl func_8006EBA4
/* 8013CA3C 0013961C  83 FF 00 2C */	lwz r31, 0x2c(r31)
/* 8013CA40 00139620  38 00 00 00 */	li r0, 0
/* 8013CA44 00139624  3C 60 80 14 */	lis r3, lbl_8013C94C@ha
/* 8013CA48 00139628  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 8013CA4C 0013962C  38 03 C9 4C */	addi r0, r3, lbl_8013C94C@l
/* 8013CA50 00139630  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8013CA54 00139634  48 02 E7 85 */	bl func_8016B1D8
/* 8013CA58 00139638  2C 03 00 00 */	cmpwi r3, 0
/* 8013CA5C 0013963C  41 82 00 20 */	beq lbl_8013CA7C
/* 8013CA60 00139640  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8013CA64 00139644  48 09 85 95 */	bl func_801D4FF8
/* 8013CA68 00139648  2C 03 00 00 */	cmpwi r3, 0
/* 8013CA6C 0013964C  41 82 00 10 */	beq lbl_8013CA7C
/* 8013CA70 00139650  38 00 00 01 */	li r0, 1
/* 8013CA74 00139654  90 1F 23 40 */	stw r0, 0x2340(r31)
/* 8013CA78 00139658  48 00 00 0C */	b lbl_8013CA84
lbl_8013CA7C:
/* 8013CA7C 0013965C  38 00 00 00 */	li r0, 0
/* 8013CA80 00139660  90 1F 23 40 */	stw r0, 0x2340(r31)
lbl_8013CA84:
/* 8013CA84 00139664  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013CA88 00139668  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013CA8C 0013966C  38 21 00 20 */	addi r1, r1, 0x20
/* 8013CA90 00139670  7C 08 03 A6 */	mtlr r0
/* 8013CA94 00139674  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftPurin_SpecialAirHi_StartAction(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8013CA98 00139678  7C 08 02 A6 */	mflr r0
/* 8013CA9C 0013967C  90 01 00 04 */	stw r0, 4(r1)
/* 8013CAA0 00139680  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013CAA4 00139684  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013CAA8 00139688  7C 7F 1B 78 */	mr r31, r3
/* 8013CAAC 0013968C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013CAB0 00139690  C0 22 A2 30 */	lfs f1, lbl_804D9C10(r2)
/* 8013CAB4 00139694  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 8013CAB8 00139698  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013CABC 0013969C  40 82 00 28 */	bne lbl_8013CAE4
/* 8013CAC0 001396A0  C0 22 A2 34 */	lfs f1, lbl_804D9C14(r2)
/* 8013CAC4 001396A4  7F E3 FB 78 */	mr r3, r31
/* 8013CAC8 001396A8  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013CACC 001396AC  38 80 01 6E */	li r4, 0x16e
/* 8013CAD0 001396B0  FC 60 08 90 */	fmr f3, f1
/* 8013CAD4 001396B4  38 A0 00 00 */	li r5, 0
/* 8013CAD8 001396B8  38 C0 00 00 */	li r6, 0
/* 8013CADC 001396BC  4B F2 C8 D1 */	bl Fighter_ActionStateChange_800693AC
/* 8013CAE0 001396C0  48 00 00 24 */	b lbl_8013CB04
lbl_8013CAE4:
/* 8013CAE4 001396C4  C0 22 A2 34 */	lfs f1, lbl_804D9C14(r2)
/* 8013CAE8 001396C8  7F E3 FB 78 */	mr r3, r31
/* 8013CAEC 001396CC  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013CAF0 001396D0  38 80 01 70 */	li r4, 0x170
/* 8013CAF4 001396D4  FC 60 08 90 */	fmr f3, f1
/* 8013CAF8 001396D8  38 A0 00 00 */	li r5, 0
/* 8013CAFC 001396DC  38 C0 00 00 */	li r6, 0
/* 8013CB00 001396E0  4B F2 C8 AD */	bl Fighter_ActionStateChange_800693AC
lbl_8013CB04:
/* 8013CB04 001396E4  7F E3 FB 78 */	mr r3, r31
/* 8013CB08 001396E8  4B F3 20 9D */	bl func_8006EBA4
/* 8013CB0C 001396EC  83 FF 00 2C */	lwz r31, 0x2c(r31)
/* 8013CB10 001396F0  38 00 00 00 */	li r0, 0
/* 8013CB14 001396F4  3C 60 80 14 */	lis r3, lbl_8013C94C@ha
/* 8013CB18 001396F8  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 8013CB1C 001396FC  38 03 C9 4C */	addi r0, r3, lbl_8013C94C@l
/* 8013CB20 00139700  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8013CB24 00139704  48 02 E6 B5 */	bl func_8016B1D8
/* 8013CB28 00139708  2C 03 00 00 */	cmpwi r3, 0
/* 8013CB2C 0013970C  41 82 00 20 */	beq lbl_8013CB4C
/* 8013CB30 00139710  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8013CB34 00139714  48 09 84 C5 */	bl func_801D4FF8
/* 8013CB38 00139718  2C 03 00 00 */	cmpwi r3, 0
/* 8013CB3C 0013971C  41 82 00 10 */	beq lbl_8013CB4C
/* 8013CB40 00139720  38 00 00 01 */	li r0, 1
/* 8013CB44 00139724  90 1F 23 40 */	stw r0, 0x2340(r31)
/* 8013CB48 00139728  48 00 00 0C */	b lbl_8013CB54
lbl_8013CB4C:
/* 8013CB4C 0013972C  38 00 00 00 */	li r0, 0
/* 8013CB50 00139730  90 1F 23 40 */	stw r0, 0x2340(r31)
lbl_8013CB54:
/* 8013CB54 00139734  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013CB58 00139738  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013CB5C 0013973C  38 21 00 20 */	addi r1, r1, 0x20
/* 8013CB60 00139740  7C 08 03 A6 */	mtlr r0
/* 8013CB64 00139744  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8013CB68(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8013CB68 00139748  7C 08 02 A6 */	mflr r0
/* 8013CB6C 0013974C  90 01 00 04 */	stw r0, 4(r1)
/* 8013CB70 00139750  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013CB74 00139754  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013CB78 00139758  7C 7F 1B 78 */	mr r31, r3
/* 8013CB7C 0013975C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8013CB80 00139760  80 04 23 40 */	lwz r0, 0x2340(r4)
/* 8013CB84 00139764  2C 00 00 00 */	cmpwi r0, 0
/* 8013CB88 00139768  41 82 00 30 */	beq lbl_8013CBB8
/* 8013CB8C 0013976C  88 64 09 57 */	lbz r3, 0x957(r4)
/* 8013CB90 00139770  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8013CB94 00139774  40 82 00 24 */	bne lbl_8013CBB8
/* 8013CB98 00139778  80 04 09 14 */	lwz r0, 0x914(r4)
/* 8013CB9C 0013977C  2C 00 00 00 */	cmpwi r0, 0
/* 8013CBA0 00139780  41 82 00 18 */	beq lbl_8013CBB8
/* 8013CBA4 00139784  38 00 00 01 */	li r0, 1
/* 8013CBA8 00139788  50 03 2E B4 */	rlwimi r3, r0, 5, 0x1a, 0x1a
/* 8013CBAC 0013978C  98 64 09 57 */	stb r3, 0x957(r4)
/* 8013CBB0 00139790  38 00 00 07 */	li r0, 7
/* 8013CBB4 00139794  90 04 09 44 */	stw r0, 0x944(r4)
lbl_8013CBB8:
/* 8013CBB8 00139798  7F E3 FB 78 */	mr r3, r31
/* 8013CBBC 0013979C  4B F3 26 7D */	bl ftAnim_IsFramesRemaining
/* 8013CBC0 001397A0  2C 03 00 00 */	cmpwi r3, 0
/* 8013CBC4 001397A4  40 82 00 0C */	bne lbl_8013CBD0
/* 8013CBC8 001397A8  7F E3 FB 78 */	mr r3, r31
/* 8013CBCC 001397AC  4B F4 D6 F1 */	bl func_8008A2BC
lbl_8013CBD0:
/* 8013CBD0 001397B0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013CBD4 001397B4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013CBD8 001397B8  38 21 00 18 */	addi r1, r1, 0x18
/* 8013CBDC 001397BC  7C 08 03 A6 */	mtlr r0
/* 8013CBE0 001397C0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8013CBE4(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8013CBE4 001397C4  7C 08 02 A6 */	mflr r0
/* 8013CBE8 001397C8  90 01 00 04 */	stw r0, 4(r1)
/* 8013CBEC 001397CC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013CBF0 001397D0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013CBF4 001397D4  7C 7F 1B 78 */	mr r31, r3
/* 8013CBF8 001397D8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8013CBFC 001397DC  80 04 23 40 */	lwz r0, 0x2340(r4)
/* 8013CC00 001397E0  2C 00 00 00 */	cmpwi r0, 0
/* 8013CC04 001397E4  41 82 00 30 */	beq lbl_8013CC34
/* 8013CC08 001397E8  88 64 09 57 */	lbz r3, 0x957(r4)
/* 8013CC0C 001397EC  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8013CC10 001397F0  40 82 00 24 */	bne lbl_8013CC34
/* 8013CC14 001397F4  80 04 09 14 */	lwz r0, 0x914(r4)
/* 8013CC18 001397F8  2C 00 00 00 */	cmpwi r0, 0
/* 8013CC1C 001397FC  41 82 00 18 */	beq lbl_8013CC34
/* 8013CC20 00139800  38 00 00 01 */	li r0, 1
/* 8013CC24 00139804  50 03 2E B4 */	rlwimi r3, r0, 5, 0x1a, 0x1a
/* 8013CC28 00139808  98 64 09 57 */	stb r3, 0x957(r4)
/* 8013CC2C 0013980C  38 00 00 07 */	li r0, 7
/* 8013CC30 00139810  90 04 09 44 */	stw r0, 0x944(r4)
lbl_8013CC34:
/* 8013CC34 00139814  7F E3 FB 78 */	mr r3, r31
/* 8013CC38 00139818  4B F3 26 01 */	bl ftAnim_IsFramesRemaining
/* 8013CC3C 0013981C  2C 03 00 00 */	cmpwi r3, 0
/* 8013CC40 00139820  40 82 00 0C */	bne lbl_8013CC4C
/* 8013CC44 00139824  7F E3 FB 78 */	mr r3, r31
/* 8013CC48 00139828  4B F8 FA E9 */	bl func_800CC730
lbl_8013CC4C:
/* 8013CC4C 0013982C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013CC50 00139830  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013CC54 00139834  38 21 00 18 */	addi r1, r1, 0x18
/* 8013CC58 00139838  7C 08 03 A6 */	mtlr r0
/* 8013CC5C 0013983C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void lbl_8013CC60(HSD_GObj* arg0) {}

void lbl_8013CC64(HSD_GObj* arg0) {}

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8013CC68(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8013CC68 00139848  7C 08 02 A6 */	mflr r0
/* 8013CC6C 0013984C  90 01 00 04 */	stw r0, 4(r1)
/* 8013CC70 00139850  94 21 FF F8 */	stwu r1, -8(r1)
/* 8013CC74 00139854  4B F4 82 C9 */	bl func_80084F3C
/* 8013CC78 00139858  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8013CC7C 0013985C  38 21 00 08 */	addi r1, r1, 8
/* 8013CC80 00139860  7C 08 03 A6 */	mtlr r0
/* 8013CC84 00139864  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8013CC88(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8013CC88 00139868  7C 08 02 A6 */	mflr r0
/* 8013CC8C 0013986C  90 01 00 04 */	stw r0, 4(r1)
/* 8013CC90 00139870  94 21 FF F8 */	stwu r1, -8(r1)
/* 8013CC94 00139874  4B F4 82 59 */	bl func_80084EEC
/* 8013CC98 00139878  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8013CC9C 0013987C  38 21 00 08 */	addi r1, r1, 8
/* 8013CCA0 00139880  7C 08 03 A6 */	mtlr r0
/* 8013CCA4 00139884  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
