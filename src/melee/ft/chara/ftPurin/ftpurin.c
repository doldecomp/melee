#include <melee/ft/chara/ftPurin/ftpurin.h>

#include <MSL/trigf.h>
#include <melee/ef/ef.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/gm/code_801601C4.h>
#include <melee/gr/grstadium.h>

extern char* lbl_803D05B4[1000]; /// not correct length
extern HSD_ObjAllocData lbl_80459080;
extern HSD_Joint* lbl_8045A1E0[1000]; /// not correct length

void func_8013C2F8()
{
    lbl_8045A1E0[0] = 0;
    lbl_8045A1E0[1] = 0;
    lbl_8045A1E0[2] = 0;
    lbl_8045A1E0[3] = 0;
    lbl_8045A1E0[4] = 0;
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
            UnkCostumeStruct* costume_list = CostumeListsForeachCharacter[fp->x4_fighterKind].costume_list;
            joint_list[fp->x619_costume_id] = HSD_ArchiveGetPublicAddress(costume_list[fp->x619_costume_id].x14_archive, lbl_803D05B4[fp->x619_costume_id]);
        }

        fp->sa.purin.x2244 = HSD_ObjAlloc(&lbl_80459080);
        func_80074148();
        fp->sa.purin.x223C = HSD_JObjLoadJoint(joint_list[fp->x619_costume_id]);
        fp->x2225_flag.bits.b2 = 1;
        func_80074170();
        func_80075650(fighter_gobj, fp->sa.purin.x223C, &fp->sa.purin.x2240);

        func_8007487C(&item_list_shifted[1], &fp->sa.purin.x2248, fp->x619_costume_id, &fp->sa.purin.x2240, &fp->sa.purin.x2240);
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

void func_8013C4F0(HSD_GObj* fighter_gobj, s32 arg1, s32 arg2)
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

        HSD_JObjDispAll(fp->sa.purin.x223C, arg2, func_80390EB8(arg1), 0);
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
    if (fp->sa.purin.x223C) {
        return fp->sa.purin.x223C;
    }
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

void ftPurin_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool)
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

void ftPurin_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1)
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

#pragma push
asm unk_t lbl_8013C94C()
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

extern f32 const lbl_804D9C10;
extern f32 const lbl_804D9C14;
extern f32 const lbl_804D9C18;

#pragma push
asm unk_t ftPurin_SpecialHi_StartAction()
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

#pragma push
asm unk_t ftPurin_SpecialAirHi_StartAction()
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

#pragma push
asm unk_t lbl_8013CB68()
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

#pragma push
asm unk_t lbl_8013CBE4()
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

void lbl_8013CC60(void)
{
    return;
}

void lbl_8013CC64(void)
{
    return;
}

#pragma push
asm unk_t lbl_8013CC68()
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

#pragma push
asm unk_t lbl_8013CC88(){ // clang-format off
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

unk_t func_8013CD34();

#pragma push
asm unk_t lbl_8013CCA8(){ // clang-format off
    nofralloc
/* 8013CCA8 00139888  7C 08 02 A6 */	mflr r0
/* 8013CCAC 0013988C  90 01 00 04 */	stw r0, 4(r1)
/* 8013CCB0 00139890  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013CCB4 00139894  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013CCB8 00139898  7C 7F 1B 78 */	mr r31, r3
/* 8013CCBC 0013989C  4B F4 5A E5 */	bl func_800827A0
/* 8013CCC0 001398A0  2C 03 00 00 */	cmpwi r3, 0
/* 8013CCC4 001398A4  40 82 00 0C */	bne lbl_8013CCD0
/* 8013CCC8 001398A8  7F E3 FB 78 */	mr r3, r31
/* 8013CCCC 001398AC  48 00 00 69 */	bl func_8013CD34
lbl_8013CCD0:
/* 8013CCD0 001398B0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013CCD4 001398B4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013CCD8 001398B8  38 21 00 18 */	addi r1, r1, 0x18
/* 8013CCDC 001398BC  7C 08 03 A6 */	mtlr r0
/* 8013CCE0 001398C0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

unk_t func_8013CDD8();

#pragma push
asm unk_t lbl_8013CCE4()
{ // clang-format off
    nofralloc
/* 8013CCE4 001398C4  7C 08 02 A6 */	mflr r0
/* 8013CCE8 001398C8  38 80 00 00 */	li r4, 0
/* 8013CCEC 001398CC  90 01 00 04 */	stw r0, 4(r1)
/* 8013CCF0 001398D0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013CCF4 001398D4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013CCF8 001398D8  3B E3 00 00 */	addi r31, r3, 0
/* 8013CCFC 001398DC  4B F4 55 A9 */	bl EnvColl_CheckGroundAndLedge
/* 8013CD00 001398E0  2C 03 00 00 */	cmpwi r3, 0
/* 8013CD04 001398E4  41 82 00 10 */	beq lbl_8013CD14
/* 8013CD08 001398E8  7F E3 FB 78 */	mr r3, r31
/* 8013CD0C 001398EC  48 00 00 CD */	bl func_8013CDD8
/* 8013CD10 001398F0  48 00 00 10 */	b lbl_8013CD20
lbl_8013CD14:
/* 8013CD14 001398F4  7F E3 FB 78 */	mr r3, r31
/* 8013CD18 001398F8  4B F4 45 81 */	bl func_80081298
/* 8013CD1C 001398FC  2C 03 00 00 */	cmpwi r3, 0
lbl_8013CD20:
/* 8013CD20 00139900  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013CD24 00139904  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013CD28 00139908  38 21 00 18 */	addi r1, r1, 0x18
/* 8013CD2C 0013990C  7C 08 03 A6 */	mtlr r0
/* 8013CD30 00139910  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013CD34()
{ // clang-format off
    nofralloc
/* 8013CD34 00139914  7C 08 02 A6 */	mflr r0
/* 8013CD38 00139918  90 01 00 04 */	stw r0, 4(r1)
/* 8013CD3C 0013991C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013CD40 00139920  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013CD44 00139924  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013CD48 00139928  7C 7E 1B 78 */	mr r30, r3
/* 8013CD4C 0013992C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013CD50 00139930  7F E3 FB 78 */	mr r3, r31
/* 8013CD54 00139934  4B F4 08 81 */	bl func_8007D5D4
/* 8013CD58 00139938  C0 22 A2 30 */	lfs f1, lbl_804D9C10(r2)
/* 8013CD5C 0013993C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013CD60 00139940  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013CD64 00139944  40 82 00 2C */	bne lbl_8013CD90
/* 8013CD68 00139948  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 8013CD6C 0013994C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013CD70 00139950  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013CD74 00139954  7F C3 F3 78 */	mr r3, r30
/* 8013CD78 00139958  C0 62 A2 34 */	lfs f3, lbl_804D9C14(r2)
/* 8013CD7C 0013995C  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 8013CD80 00139960  38 80 01 6E */	li r4, 0x16e
/* 8013CD84 00139964  38 C0 00 00 */	li r6, 0
/* 8013CD88 00139968  4B F2 C6 25 */	bl Fighter_ActionStateChange_800693AC
/* 8013CD8C 0013996C  48 00 00 28 */	b lbl_8013CDB4
lbl_8013CD90:
/* 8013CD90 00139970  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 8013CD94 00139974  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013CD98 00139978  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013CD9C 0013997C  7F C3 F3 78 */	mr r3, r30
/* 8013CDA0 00139980  C0 62 A2 34 */	lfs f3, lbl_804D9C14(r2)
/* 8013CDA4 00139984  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 8013CDA8 00139988  38 80 01 70 */	li r4, 0x170
/* 8013CDAC 0013998C  38 C0 00 00 */	li r6, 0
/* 8013CDB0 00139990  4B F2 C5 FD */	bl Fighter_ActionStateChange_800693AC
lbl_8013CDB4:
/* 8013CDB4 00139994  3C 60 80 14 */	lis r3, lbl_8013C94C@ha
/* 8013CDB8 00139998  38 03 C9 4C */	addi r0, r3, lbl_8013C94C@l
/* 8013CDBC 0013999C  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8013CDC0 001399A0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013CDC4 001399A4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013CDC8 001399A8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013CDCC 001399AC  38 21 00 18 */	addi r1, r1, 0x18
/* 8013CDD0 001399B0  7C 08 03 A6 */	mtlr r0
/* 8013CDD4 001399B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013CDD8()
{ // clang-format off
    nofralloc
/* 8013CDD8 001399B8  7C 08 02 A6 */	mflr r0
/* 8013CDDC 001399BC  90 01 00 04 */	stw r0, 4(r1)
/* 8013CDE0 001399C0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013CDE4 001399C4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013CDE8 001399C8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013CDEC 001399CC  7C 7E 1B 78 */	mr r30, r3
/* 8013CDF0 001399D0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013CDF4 001399D4  7F E3 FB 78 */	mr r3, r31
/* 8013CDF8 001399D8  4B F4 0A 05 */	bl func_8007D7FC
/* 8013CDFC 001399DC  C0 22 A2 30 */	lfs f1, lbl_804D9C10(r2)
/* 8013CE00 001399E0  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013CE04 001399E4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013CE08 001399E8  40 82 00 2C */	bne lbl_8013CE34
/* 8013CE0C 001399EC  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 8013CE10 001399F0  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013CE14 001399F4  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013CE18 001399F8  7F C3 F3 78 */	mr r3, r30
/* 8013CE1C 001399FC  C0 62 A2 34 */	lfs f3, lbl_804D9C14(r2)
/* 8013CE20 00139A00  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 8013CE24 00139A04  38 80 01 6D */	li r4, 0x16d
/* 8013CE28 00139A08  38 C0 00 00 */	li r6, 0
/* 8013CE2C 00139A0C  4B F2 C5 81 */	bl Fighter_ActionStateChange_800693AC
/* 8013CE30 00139A10  48 00 00 28 */	b lbl_8013CE58
lbl_8013CE34:
/* 8013CE34 00139A14  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 8013CE38 00139A18  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013CE3C 00139A1C  C0 42 A2 38 */	lfs f2, lbl_804D9C18(r2)
/* 8013CE40 00139A20  7F C3 F3 78 */	mr r3, r30
/* 8013CE44 00139A24  C0 62 A2 34 */	lfs f3, lbl_804D9C14(r2)
/* 8013CE48 00139A28  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 8013CE4C 00139A2C  38 80 01 6F */	li r4, 0x16f
/* 8013CE50 00139A30  38 C0 00 00 */	li r6, 0
/* 8013CE54 00139A34  4B F2 C5 59 */	bl Fighter_ActionStateChange_800693AC
lbl_8013CE58:
/* 8013CE58 00139A38  3C 60 80 14 */	lis r3, lbl_8013C94C@ha
/* 8013CE5C 00139A3C  38 03 C9 4C */	addi r0, r3, lbl_8013C94C@l
/* 8013CE60 00139A40  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8013CE64 00139A44  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013CE68 00139A48  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013CE6C 00139A4C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013CE70 00139A50  38 21 00 18 */	addi r1, r1, 0x18
/* 8013CE74 00139A54  7C 08 03 A6 */	mtlr r0
/* 8013CE78 00139A58  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013CE7C()
{ // clang-format off
    nofralloc
/* 8013CE7C 00139A5C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013CE80 00139A60  38 00 00 00 */	li r0, 0
/* 8013CE84 00139A64  90 03 21 BC */	stw r0, 0x21bc(r3)
/* 8013CE88 00139A68  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D9C20;
extern f32 const lbl_804D9C24;
extern f32 const lbl_804D9C28;

#pragma push
asm unk_t ftPurin_SpecialLw_StartAction()
{ // clang-format off
    nofralloc
/* 8013CE8C 00139A6C  7C 08 02 A6 */	mflr r0
/* 8013CE90 00139A70  90 01 00 04 */	stw r0, 4(r1)
/* 8013CE94 00139A74  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013CE98 00139A78  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013CE9C 00139A7C  7C 7F 1B 78 */	mr r31, r3
/* 8013CEA0 00139A80  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013CEA4 00139A84  C0 22 A2 40 */	lfs f1, lbl_804D9C20(r2)
/* 8013CEA8 00139A88  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 8013CEAC 00139A8C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013CEB0 00139A90  40 82 00 28 */	bne lbl_8013CED8
/* 8013CEB4 00139A94  C0 22 A2 44 */	lfs f1, lbl_804D9C24(r2)
/* 8013CEB8 00139A98  7F E3 FB 78 */	mr r3, r31
/* 8013CEBC 00139A9C  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013CEC0 00139AA0  38 80 01 71 */	li r4, 0x171
/* 8013CEC4 00139AA4  FC 60 08 90 */	fmr f3, f1
/* 8013CEC8 00139AA8  38 A0 00 00 */	li r5, 0
/* 8013CECC 00139AAC  38 C0 00 00 */	li r6, 0
/* 8013CED0 00139AB0  4B F2 C4 DD */	bl Fighter_ActionStateChange_800693AC
/* 8013CED4 00139AB4  48 00 00 24 */	b lbl_8013CEF8
lbl_8013CED8:
/* 8013CED8 00139AB8  C0 22 A2 44 */	lfs f1, lbl_804D9C24(r2)
/* 8013CEDC 00139ABC  7F E3 FB 78 */	mr r3, r31
/* 8013CEE0 00139AC0  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013CEE4 00139AC4  38 80 01 73 */	li r4, 0x173
/* 8013CEE8 00139AC8  FC 60 08 90 */	fmr f3, f1
/* 8013CEEC 00139ACC  38 A0 00 00 */	li r5, 0
/* 8013CEF0 00139AD0  38 C0 00 00 */	li r6, 0
/* 8013CEF4 00139AD4  4B F2 C4 B9 */	bl Fighter_ActionStateChange_800693AC
lbl_8013CEF8:
/* 8013CEF8 00139AD8  7F E3 FB 78 */	mr r3, r31
/* 8013CEFC 00139ADC  4B F3 1C A9 */	bl func_8006EBA4
/* 8013CF00 00139AE0  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8013CF04 00139AE4  38 00 00 00 */	li r0, 0
/* 8013CF08 00139AE8  3C 60 80 14 */	lis r3, lbl_8013CE7C@ha
/* 8013CF0C 00139AEC  90 04 22 00 */	stw r0, 0x2200(r4)
/* 8013CF10 00139AF0  38 03 CE 7C */	addi r0, r3, lbl_8013CE7C@l
/* 8013CF14 00139AF4  90 04 21 BC */	stw r0, 0x21bc(r4)
/* 8013CF18 00139AF8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013CF1C 00139AFC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013CF20 00139B00  38 21 00 20 */	addi r1, r1, 0x20
/* 8013CF24 00139B04  7C 08 03 A6 */	mtlr r0
/* 8013CF28 00139B08  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ftPurin_SpecialAirLw_StartAction()
{ // clang-format off
    nofralloc
/* 8013CF2C 00139B0C  7C 08 02 A6 */	mflr r0
/* 8013CF30 00139B10  90 01 00 04 */	stw r0, 4(r1)
/* 8013CF34 00139B14  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013CF38 00139B18  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013CF3C 00139B1C  7C 7F 1B 78 */	mr r31, r3
/* 8013CF40 00139B20  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013CF44 00139B24  C0 22 A2 40 */	lfs f1, lbl_804D9C20(r2)
/* 8013CF48 00139B28  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 8013CF4C 00139B2C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013CF50 00139B30  40 82 00 28 */	bne lbl_8013CF78
/* 8013CF54 00139B34  C0 22 A2 44 */	lfs f1, lbl_804D9C24(r2)
/* 8013CF58 00139B38  7F E3 FB 78 */	mr r3, r31
/* 8013CF5C 00139B3C  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013CF60 00139B40  38 80 01 72 */	li r4, 0x172
/* 8013CF64 00139B44  FC 60 08 90 */	fmr f3, f1
/* 8013CF68 00139B48  38 A0 00 00 */	li r5, 0
/* 8013CF6C 00139B4C  38 C0 00 00 */	li r6, 0
/* 8013CF70 00139B50  4B F2 C4 3D */	bl Fighter_ActionStateChange_800693AC
/* 8013CF74 00139B54  48 00 00 24 */	b lbl_8013CF98
lbl_8013CF78:
/* 8013CF78 00139B58  C0 22 A2 44 */	lfs f1, lbl_804D9C24(r2)
/* 8013CF7C 00139B5C  7F E3 FB 78 */	mr r3, r31
/* 8013CF80 00139B60  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013CF84 00139B64  38 80 01 74 */	li r4, 0x174
/* 8013CF88 00139B68  FC 60 08 90 */	fmr f3, f1
/* 8013CF8C 00139B6C  38 A0 00 00 */	li r5, 0
/* 8013CF90 00139B70  38 C0 00 00 */	li r6, 0
/* 8013CF94 00139B74  4B F2 C4 19 */	bl Fighter_ActionStateChange_800693AC
lbl_8013CF98:
/* 8013CF98 00139B78  7F E3 FB 78 */	mr r3, r31
/* 8013CF9C 00139B7C  4B F3 1C 09 */	bl func_8006EBA4
/* 8013CFA0 00139B80  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8013CFA4 00139B84  38 00 00 00 */	li r0, 0
/* 8013CFA8 00139B88  3C 60 80 14 */	lis r3, lbl_8013CE7C@ha
/* 8013CFAC 00139B8C  90 04 22 00 */	stw r0, 0x2200(r4)
/* 8013CFB0 00139B90  38 03 CE 7C */	addi r0, r3, lbl_8013CE7C@l
/* 8013CFB4 00139B94  90 04 21 BC */	stw r0, 0x21bc(r4)
/* 8013CFB8 00139B98  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013CFBC 00139B9C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013CFC0 00139BA0  38 21 00 20 */	addi r1, r1, 0x20
/* 8013CFC4 00139BA4  7C 08 03 A6 */	mtlr r0
/* 8013CFC8 00139BA8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013CFCC()
{ // clang-format off
    nofralloc
/* 8013CFCC 00139BAC  7C 08 02 A6 */	mflr r0
/* 8013CFD0 00139BB0  90 01 00 04 */	stw r0, 4(r1)
/* 8013CFD4 00139BB4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013CFD8 00139BB8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013CFDC 00139BBC  7C 7F 1B 78 */	mr r31, r3
/* 8013CFE0 00139BC0  4B F3 22 59 */	bl ftAnim_IsFramesRemaining
/* 8013CFE4 00139BC4  2C 03 00 00 */	cmpwi r3, 0
/* 8013CFE8 00139BC8  40 82 00 0C */	bne lbl_8013CFF4
/* 8013CFEC 00139BCC  7F E3 FB 78 */	mr r3, r31
/* 8013CFF0 00139BD0  4B F4 D2 CD */	bl func_8008A2BC
lbl_8013CFF4:
/* 8013CFF4 00139BD4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013CFF8 00139BD8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013CFFC 00139BDC  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D000 00139BE0  7C 08 03 A6 */	mtlr r0
/* 8013D004 00139BE4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013D008()
{ // clang-format off
    nofralloc
/* 8013D008 00139BE8  7C 08 02 A6 */	mflr r0
/* 8013D00C 00139BEC  90 01 00 04 */	stw r0, 4(r1)
/* 8013D010 00139BF0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D014 00139BF4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D018 00139BF8  7C 7F 1B 78 */	mr r31, r3
/* 8013D01C 00139BFC  4B F3 22 1D */	bl ftAnim_IsFramesRemaining
/* 8013D020 00139C00  2C 03 00 00 */	cmpwi r3, 0
/* 8013D024 00139C04  40 82 00 0C */	bne lbl_8013D030
/* 8013D028 00139C08  7F E3 FB 78 */	mr r3, r31
/* 8013D02C 00139C0C  4B F8 F7 05 */	bl func_800CC730
lbl_8013D030:
/* 8013D030 00139C10  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D034 00139C14  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D038 00139C18  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D03C 00139C1C  7C 08 03 A6 */	mtlr r0
/* 8013D040 00139C20  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void lbl_8013D044(void)
{
    return;
}

void lbl_8013D048(void)
{
    return;
}

#pragma push
asm unk_t lbl_8013D04C()
{ // clang-format off
    nofralloc
/* 8013D04C 00139C2C  7C 08 02 A6 */	mflr r0
/* 8013D050 00139C30  90 01 00 04 */	stw r0, 4(r1)
/* 8013D054 00139C34  94 21 FF F8 */	stwu r1, -8(r1)
/* 8013D058 00139C38  4B F4 7E E5 */	bl func_80084F3C
/* 8013D05C 00139C3C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8013D060 00139C40  38 21 00 08 */	addi r1, r1, 8
/* 8013D064 00139C44  7C 08 03 A6 */	mtlr r0
/* 8013D068 00139C48  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013D06C(){ // clang-format off
    nofralloc
/* 8013D06C 00139C4C  7C 08 02 A6 */	mflr r0
/* 8013D070 00139C50  90 01 00 04 */	stw r0, 4(r1)
/* 8013D074 00139C54  94 21 FF F8 */	stwu r1, -8(r1)
/* 8013D078 00139C58  4B F4 7E 75 */	bl func_80084EEC
/* 8013D07C 00139C5C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8013D080 00139C60  38 21 00 08 */	addi r1, r1, 8
/* 8013D084 00139C64  7C 08 03 A6 */	mtlr r0
/* 8013D088 00139C68  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

unk_t func_8013D104();

#pragma push
asm unk_t lbl_8013D08C(){ // clang-format off
    nofralloc
/* 8013D08C 00139C6C  7C 08 02 A6 */	mflr r0
/* 8013D090 00139C70  90 01 00 04 */	stw r0, 4(r1)
/* 8013D094 00139C74  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D098 00139C78  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D09C 00139C7C  7C 7F 1B 78 */	mr r31, r3
/* 8013D0A0 00139C80  4B F4 57 01 */	bl func_800827A0
/* 8013D0A4 00139C84  2C 03 00 00 */	cmpwi r3, 0
/* 8013D0A8 00139C88  40 82 00 0C */	bne lbl_8013D0B4
/* 8013D0AC 00139C8C  7F E3 FB 78 */	mr r3, r31
/* 8013D0B0 00139C90  48 00 00 55 */	bl func_8013D104
lbl_8013D0B4:
/* 8013D0B4 00139C94  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D0B8 00139C98  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D0BC 00139C9C  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D0C0 00139CA0  7C 08 03 A6 */	mtlr r0
/* 8013D0C4 00139CA4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

unk_t func_8013D19C();

#pragma push
asm unk_t lbl_8013D0C8()
{ // clang-format off
    nofralloc
/* 8013D0C8 00139CA8  7C 08 02 A6 */	mflr r0
/* 8013D0CC 00139CAC  90 01 00 04 */	stw r0, 4(r1)
/* 8013D0D0 00139CB0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D0D4 00139CB4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D0D8 00139CB8  7C 7F 1B 78 */	mr r31, r3
/* 8013D0DC 00139CBC  4B F4 4C 31 */	bl func_80081D0C
/* 8013D0E0 00139CC0  2C 03 00 00 */	cmpwi r3, 0
/* 8013D0E4 00139CC4  41 82 00 0C */	beq lbl_8013D0F0
/* 8013D0E8 00139CC8  7F E3 FB 78 */	mr r3, r31
/* 8013D0EC 00139CCC  48 00 00 B1 */	bl func_8013D19C
lbl_8013D0F0:
/* 8013D0F0 00139CD0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D0F4 00139CD4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D0F8 00139CD8  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D0FC 00139CDC  7C 08 03 A6 */	mtlr r0
/* 8013D100 00139CE0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013D104()
{ // clang-format off
    nofralloc
/* 8013D104 00139CE4  7C 08 02 A6 */	mflr r0
/* 8013D108 00139CE8  90 01 00 04 */	stw r0, 4(r1)
/* 8013D10C 00139CEC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D110 00139CF0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D114 00139CF4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013D118 00139CF8  7C 7E 1B 78 */	mr r30, r3
/* 8013D11C 00139CFC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D120 00139D00  7F E3 FB 78 */	mr r3, r31
/* 8013D124 00139D04  4B F4 04 B1 */	bl func_8007D5D4
/* 8013D128 00139D08  C0 22 A2 40 */	lfs f1, lbl_804D9C20(r2)
/* 8013D12C 00139D0C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013D130 00139D10  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013D134 00139D14  40 82 00 2C */	bne lbl_8013D160
/* 8013D138 00139D18  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 8013D13C 00139D1C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013D140 00139D20  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013D144 00139D24  7F C3 F3 78 */	mr r3, r30
/* 8013D148 00139D28  C0 62 A2 44 */	lfs f3, lbl_804D9C24(r2)
/* 8013D14C 00139D2C  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 8013D150 00139D30  38 80 01 72 */	li r4, 0x172
/* 8013D154 00139D34  38 C0 00 00 */	li r6, 0
/* 8013D158 00139D38  4B F2 C2 55 */	bl Fighter_ActionStateChange_800693AC
/* 8013D15C 00139D3C  48 00 00 28 */	b lbl_8013D184
lbl_8013D160:
/* 8013D160 00139D40  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 8013D164 00139D44  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013D168 00139D48  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013D16C 00139D4C  7F C3 F3 78 */	mr r3, r30
/* 8013D170 00139D50  C0 62 A2 44 */	lfs f3, lbl_804D9C24(r2)
/* 8013D174 00139D54  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 8013D178 00139D58  38 80 01 74 */	li r4, 0x174
/* 8013D17C 00139D5C  38 C0 00 00 */	li r6, 0
/* 8013D180 00139D60  4B F2 C2 2D */	bl Fighter_ActionStateChange_800693AC
lbl_8013D184:
/* 8013D184 00139D64  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D188 00139D68  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D18C 00139D6C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013D190 00139D70  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D194 00139D74  7C 08 03 A6 */	mtlr r0
/* 8013D198 00139D78  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013D19C()
{ // clang-format off
    nofralloc
/* 8013D19C 00139D7C  7C 08 02 A6 */	mflr r0
/* 8013D1A0 00139D80  90 01 00 04 */	stw r0, 4(r1)
/* 8013D1A4 00139D84  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D1A8 00139D88  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D1AC 00139D8C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013D1B0 00139D90  7C 7E 1B 78 */	mr r30, r3
/* 8013D1B4 00139D94  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D1B8 00139D98  7F E3 FB 78 */	mr r3, r31
/* 8013D1BC 00139D9C  4B F4 06 41 */	bl func_8007D7FC
/* 8013D1C0 00139DA0  C0 22 A2 40 */	lfs f1, lbl_804D9C20(r2)
/* 8013D1C4 00139DA4  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013D1C8 00139DA8  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013D1CC 00139DAC  40 82 00 2C */	bne lbl_8013D1F8
/* 8013D1D0 00139DB0  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 8013D1D4 00139DB4  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013D1D8 00139DB8  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013D1DC 00139DBC  7F C3 F3 78 */	mr r3, r30
/* 8013D1E0 00139DC0  C0 62 A2 44 */	lfs f3, lbl_804D9C24(r2)
/* 8013D1E4 00139DC4  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 8013D1E8 00139DC8  38 80 01 71 */	li r4, 0x171
/* 8013D1EC 00139DCC  38 C0 00 00 */	li r6, 0
/* 8013D1F0 00139DD0  4B F2 C1 BD */	bl Fighter_ActionStateChange_800693AC
/* 8013D1F4 00139DD4  48 00 00 28 */	b lbl_8013D21C
lbl_8013D1F8:
/* 8013D1F8 00139DD8  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 8013D1FC 00139DDC  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013D200 00139DE0  C0 42 A2 48 */	lfs f2, lbl_804D9C28(r2)
/* 8013D204 00139DE4  7F C3 F3 78 */	mr r3, r30
/* 8013D208 00139DE8  C0 62 A2 44 */	lfs f3, lbl_804D9C24(r2)
/* 8013D20C 00139DEC  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 8013D210 00139DF0  38 80 01 73 */	li r4, 0x173
/* 8013D214 00139DF4  38 C0 00 00 */	li r6, 0
/* 8013D218 00139DF8  4B F2 C1 95 */	bl Fighter_ActionStateChange_800693AC
lbl_8013D21C:
/* 8013D21C 00139DFC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D220 00139E00  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D224 00139E04  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013D228 00139E08  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D22C 00139E0C  7C 08 03 A6 */	mtlr r0
/* 8013D230 00139E10  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D9C30;
extern f32 const lbl_804D9C38;

#pragma push
asm unk_t ftPurin_SpecialS_StartAction()
{ // clang-format off
    nofralloc
/* 8013D234 00139E14  7C 08 02 A6 */	mflr r0
/* 8013D238 00139E18  38 80 01 6B */	li r4, 0x16b
/* 8013D23C 00139E1C  90 01 00 04 */	stw r0, 4(r1)
/* 8013D240 00139E20  38 A0 00 00 */	li r5, 0
/* 8013D244 00139E24  38 C0 00 00 */	li r6, 0
/* 8013D248 00139E28  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D24C 00139E2C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D250 00139E30  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013D254 00139E34  7C 7E 1B 78 */	mr r30, r3
/* 8013D258 00139E38  C0 22 A2 50 */	lfs f1, lbl_804D9C30(r2)
/* 8013D25C 00139E3C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D260 00139E40  FC 60 08 90 */	fmr f3, f1
/* 8013D264 00139E44  C0 42 A2 58 */	lfs f2, lbl_804D9C38(r2)
/* 8013D268 00139E48  4B F2 C1 45 */	bl Fighter_ActionStateChange_800693AC
/* 8013D26C 00139E4C  7F C3 F3 78 */	mr r3, r30
/* 8013D270 00139E50  4B F3 19 35 */	bl func_8006EBA4
/* 8013D274 00139E54  38 00 00 00 */	li r0, 0
/* 8013D278 00139E58  90 1F 22 0C */	stw r0, 0x220c(r31)
/* 8013D27C 00139E5C  90 1F 22 08 */	stw r0, 0x2208(r31)
/* 8013D280 00139E60  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 8013D284 00139E64  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 8013D288 00139E68  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D28C 00139E6C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D290 00139E70  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013D294 00139E74  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D298 00139E78  7C 08 03 A6 */	mtlr r0
/* 8013D29C 00139E7C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ftPurin_SpecialAirS_StartAction()
{ // clang-format off
    nofralloc
/* 8013D2A0 00139E80  7C 08 02 A6 */	mflr r0
/* 8013D2A4 00139E84  38 80 01 6C */	li r4, 0x16c
/* 8013D2A8 00139E88  90 01 00 04 */	stw r0, 4(r1)
/* 8013D2AC 00139E8C  38 A0 00 00 */	li r5, 0
/* 8013D2B0 00139E90  38 C0 00 00 */	li r6, 0
/* 8013D2B4 00139E94  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D2B8 00139E98  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D2BC 00139E9C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013D2C0 00139EA0  7C 7E 1B 78 */	mr r30, r3
/* 8013D2C4 00139EA4  C0 22 A2 50 */	lfs f1, lbl_804D9C30(r2)
/* 8013D2C8 00139EA8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D2CC 00139EAC  FC 60 08 90 */	fmr f3, f1
/* 8013D2D0 00139EB0  C0 42 A2 58 */	lfs f2, lbl_804D9C38(r2)
/* 8013D2D4 00139EB4  4B F2 C0 D9 */	bl Fighter_ActionStateChange_800693AC
/* 8013D2D8 00139EB8  7F C3 F3 78 */	mr r3, r30
/* 8013D2DC 00139EBC  4B F3 18 C9 */	bl func_8006EBA4
/* 8013D2E0 00139EC0  38 00 00 00 */	li r0, 0
/* 8013D2E4 00139EC4  90 1F 22 0C */	stw r0, 0x220c(r31)
/* 8013D2E8 00139EC8  90 1F 22 08 */	stw r0, 0x2208(r31)
/* 8013D2EC 00139ECC  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 8013D2F0 00139ED0  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 8013D2F4 00139ED4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D2F8 00139ED8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D2FC 00139EDC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013D300 00139EE0  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D304 00139EE4  7C 08 03 A6 */	mtlr r0
/* 8013D308 00139EE8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013D30C()
{ // clang-format off
    nofralloc
/* 8013D30C 00139EEC  7C 08 02 A6 */	mflr r0
/* 8013D310 00139EF0  90 01 00 04 */	stw r0, 4(r1)
/* 8013D314 00139EF4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D318 00139EF8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D31C 00139EFC  7C 7F 1B 78 */	mr r31, r3
/* 8013D320 00139F00  4B F3 1F 19 */	bl ftAnim_IsFramesRemaining
/* 8013D324 00139F04  2C 03 00 00 */	cmpwi r3, 0
/* 8013D328 00139F08  40 82 00 0C */	bne lbl_8013D334
/* 8013D32C 00139F0C  7F E3 FB 78 */	mr r3, r31
/* 8013D330 00139F10  4B F4 CF 8D */	bl func_8008A2BC
lbl_8013D334:
/* 8013D334 00139F14  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D338 00139F18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D33C 00139F1C  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D340 00139F20  7C 08 03 A6 */	mtlr r0
/* 8013D344 00139F24  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013D348()
{ // clang-format off
    nofralloc
/* 8013D348 00139F28  7C 08 02 A6 */	mflr r0
/* 8013D34C 00139F2C  90 01 00 04 */	stw r0, 4(r1)
/* 8013D350 00139F30  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D354 00139F34  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D358 00139F38  7C 7F 1B 78 */	mr r31, r3
/* 8013D35C 00139F3C  4B F3 1E DD */	bl ftAnim_IsFramesRemaining
/* 8013D360 00139F40  2C 03 00 00 */	cmpwi r3, 0
/* 8013D364 00139F44  40 82 00 0C */	bne lbl_8013D370
/* 8013D368 00139F48  7F E3 FB 78 */	mr r3, r31
/* 8013D36C 00139F4C  4B F8 F3 C5 */	bl func_800CC730
lbl_8013D370:
/* 8013D370 00139F50  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D374 00139F54  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D378 00139F58  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D37C 00139F5C  7C 08 03 A6 */	mtlr r0
/* 8013D380 00139F60  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void lbl_8013D384(void)
{
    return;
}

void lbl_8013D388(void)
{
    return;
}

#pragma push
asm unk_t lbl_8013D38C()
{ // clang-format off
    nofralloc
/* 8013D38C 00139F6C  7C 08 02 A6 */	mflr r0
/* 8013D390 00139F70  90 01 00 04 */	stw r0, 4(r1)
/* 8013D394 00139F74  94 21 FF F8 */	stwu r1, -8(r1)
/* 8013D398 00139F78  4B F4 7C 11 */	bl func_80084FA8
/* 8013D39C 00139F7C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8013D3A0 00139F80  38 21 00 08 */	addi r1, r1, 8
/* 8013D3A4 00139F84  7C 08 03 A6 */	mtlr r0
/* 8013D3A8 00139F88  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D9C34;

#pragma push
asm unk_t lbl_8013D3AC(){ // clang-format off
    nofralloc
/* 8013D3AC 00139F8C  7C 08 02 A6 */	mflr r0
/* 8013D3B0 00139F90  90 01 00 04 */	stw r0, 4(r1)
/* 8013D3B4 00139F94  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8013D3B8 00139F98  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 8013D3BC 00139F9C  93 E1 00 44 */	stw r31, 0x44(r1)
/* 8013D3C0 00139FA0  93 C1 00 40 */	stw r30, 0x40(r1)
/* 8013D3C4 00139FA4  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 8013D3C8 00139FA8  7C 7D 1B 78 */	mr r29, r3
/* 8013D3CC 00139FAC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D3D0 00139FB0  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 8013D3D4 00139FB4  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013D3D8 00139FB8  28 00 00 00 */	cmplwi r0, 0
/* 8013D3DC 00139FBC  41 82 00 BC */	beq lbl_8013D498
/* 8013D3E0 00139FC0  38 00 00 00 */	li r0, 0
/* 8013D3E4 00139FC4  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 8013D3E8 00139FC8  80 7F 22 2C */	lwz r3, 0x222c(r31)
/* 8013D3EC 00139FCC  38 03 00 01 */	addi r0, r3, 1
/* 8013D3F0 00139FD0  90 1F 22 2C */	stw r0, 0x222c(r31)
/* 8013D3F4 00139FD4  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8013D3F8 00139FD8  C0 02 A2 50 */	lfs f0, lbl_804D9C30(r2)
/* 8013D3FC 00139FDC  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8013D400 00139FE0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013D404 00139FE4  80 63 02 D4 */	lwz r3, 0x2d4(r3)
/* 8013D408 00139FE8  40 80 00 0C */	bge lbl_8013D414
/* 8013D40C 00139FEC  FC 60 08 50 */	fneg f3, f1
/* 8013D410 00139FF0  48 00 00 08 */	b lbl_8013D418
lbl_8013D414:
/* 8013D414 00139FF4  FC 60 08 90 */	fmr f3, f1
lbl_8013D418:
/* 8013D418 00139FF8  C0 43 00 E0 */	lfs f2, 0xe0(r3)
/* 8013D41C 00139FFC  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 8013D420 0013A000  40 81 00 08 */	ble lbl_8013D428
/* 8013D424 0013A004  FC 60 10 90 */	fmr f3, f2
lbl_8013D428:
/* 8013D428 0013A008  C0 83 00 DC */	lfs f4, 0xdc(r3)
/* 8013D42C 0013A00C  C0 02 A2 50 */	lfs f0, lbl_804D9C30(r2)
/* 8013D430 0013A010  EC 63 20 28 */	fsubs f3, f3, f4
/* 8013D434 0013A014  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8013D438 0013A018  40 80 00 08 */	bge lbl_8013D440
/* 8013D43C 0013A01C  FC 60 00 90 */	fmr f3, f0
lbl_8013D440:
/* 8013D440 0013A020  C0 02 A2 50 */	lfs f0, lbl_804D9C30(r2)
/* 8013D444 0013A024  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013D448 0013A028  40 80 00 08 */	bge lbl_8013D450
/* 8013D44C 0013A02C  FC 60 18 50 */	fneg f3, f3
lbl_8013D450:
/* 8013D450 0013A030  C0 23 00 E4 */	lfs f1, 0xe4(r3)
/* 8013D454 0013A034  EC 02 20 28 */	fsubs f0, f2, f4
/* 8013D458 0013A038  C0 42 A2 54 */	lfs f2, lbl_804D9C34(r2)
/* 8013D45C 0013A03C  EC 23 00 72 */	fmuls f1, f3, f1
/* 8013D460 0013A040  EC 01 00 24 */	fdivs f0, f1, f0
/* 8013D464 0013A044  EF E2 00 32 */	fmuls f31, f2, f0
/* 8013D468 0013A048  FC 20 F8 90 */	fmr f1, f31
/* 8013D46C 0013A04C  48 1E 8F 69 */	bl sinf
/* 8013D470 0013A050  C0 1E 00 F0 */	lfs f0, 0xf0(r30)
/* 8013D474 0013A054  EC 00 00 72 */	fmuls f0, f0, f1
/* 8013D478 0013A058  FC 20 F8 90 */	fmr f1, f31
/* 8013D47C 0013A05C  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8013D480 0013A060  48 1E 8D C1 */	bl cosf
/* 8013D484 0013A064  C0 5F 00 2C */	lfs f2, 0x2c(r31)
/* 8013D488 0013A068  C0 1E 00 F0 */	lfs f0, 0xf0(r30)
/* 8013D48C 0013A06C  EC 22 00 72 */	fmuls f1, f2, f1
/* 8013D490 0013A070  EC 00 00 72 */	fmuls f0, f0, f1
/* 8013D494 0013A074  D0 1F 00 80 */	stfs f0, 0x80(r31)
lbl_8013D498:
/* 8013D498 0013A078  80 1F 22 04 */	lwz r0, 0x2204(r31)
/* 8013D49C 0013A07C  2C 00 00 01 */	cmpwi r0, 1
/* 8013D4A0 0013A080  41 82 00 2C */	beq lbl_8013D4CC
/* 8013D4A4 0013A084  40 80 00 10 */	bge lbl_8013D4B4
/* 8013D4A8 0013A088  2C 00 00 00 */	cmpwi r0, 0
/* 8013D4AC 0013A08C  40 80 00 14 */	bge lbl_8013D4C0
/* 8013D4B0 0013A090  48 00 00 48 */	b lbl_8013D4F8
lbl_8013D4B4:
/* 8013D4B4 0013A094  2C 00 00 03 */	cmpwi r0, 3
/* 8013D4B8 0013A098  40 80 00 40 */	bge lbl_8013D4F8
/* 8013D4BC 0013A09C  48 00 00 34 */	b lbl_8013D4F0
lbl_8013D4C0:
/* 8013D4C0 0013A0A0  7F A3 EB 78 */	mr r3, r29
/* 8013D4C4 0013A0A4  4B F4 7A 29 */	bl func_80084EEC
/* 8013D4C8 0013A0A8  48 00 00 30 */	b lbl_8013D4F8
lbl_8013D4CC:
/* 8013D4CC 0013A0AC  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 8013D4D0 0013A0B0  C0 1E 00 F4 */	lfs f0, 0xf4(r30)
/* 8013D4D4 0013A0B4  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013D4D8 0013A0B8  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8013D4DC 0013A0BC  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 8013D4E0 0013A0C0  C0 1E 00 F4 */	lfs f0, 0xf4(r30)
/* 8013D4E4 0013A0C4  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013D4E8 0013A0C8  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8013D4EC 0013A0CC  48 00 00 0C */	b lbl_8013D4F8
lbl_8013D4F0:
/* 8013D4F0 0013A0D0  7F A3 EB 78 */	mr r3, r29
/* 8013D4F4 0013A0D4  4B F4 78 BD */	bl func_80084DB0
lbl_8013D4F8:
/* 8013D4F8 0013A0D8  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8013D4FC 0013A0DC  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 8013D500 0013A0E0  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 8013D504 0013A0E4  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 8013D508 0013A0E8  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 8013D50C 0013A0EC  38 21 00 50 */	addi r1, r1, 0x50
/* 8013D510 0013A0F0  7C 08 03 A6 */	mtlr r0
/* 8013D514 0013A0F4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

unk_t func_8013D590();

#pragma push
asm unk_t lbl_8013D518(){ // clang-format off
    nofralloc
/* 8013D518 0013A0F8  7C 08 02 A6 */	mflr r0
/* 8013D51C 0013A0FC  90 01 00 04 */	stw r0, 4(r1)
/* 8013D520 0013A100  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D524 0013A104  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D528 0013A108  7C 7F 1B 78 */	mr r31, r3
/* 8013D52C 0013A10C  4B F4 52 75 */	bl func_800827A0
/* 8013D530 0013A110  2C 03 00 00 */	cmpwi r3, 0
/* 8013D534 0013A114  40 82 00 0C */	bne lbl_8013D540
/* 8013D538 0013A118  7F E3 FB 78 */	mr r3, r31
/* 8013D53C 0013A11C  48 00 00 55 */	bl func_8013D590
lbl_8013D540:
/* 8013D540 0013A120  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D544 0013A124  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D548 0013A128  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D54C 0013A12C  7C 08 03 A6 */	mtlr r0
/* 8013D550 0013A130  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

unk_t func_8013D5F0();

#pragma push
asm unk_t lbl_8013D554()
{ // clang-format off
    nofralloc
/* 8013D554 0013A134  7C 08 02 A6 */	mflr r0
/* 8013D558 0013A138  90 01 00 04 */	stw r0, 4(r1)
/* 8013D55C 0013A13C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D560 0013A140  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D564 0013A144  7C 7F 1B 78 */	mr r31, r3
/* 8013D568 0013A148  4B F4 47 A5 */	bl func_80081D0C
/* 8013D56C 0013A14C  2C 03 00 00 */	cmpwi r3, 0
/* 8013D570 0013A150  41 82 00 0C */	beq lbl_8013D57C
/* 8013D574 0013A154  7F E3 FB 78 */	mr r3, r31
/* 8013D578 0013A158  48 00 00 79 */	bl func_8013D5F0
lbl_8013D57C:
/* 8013D57C 0013A15C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D580 0013A160  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D584 0013A164  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D588 0013A168  7C 08 03 A6 */	mtlr r0
/* 8013D58C 0013A16C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013D590()
{ // clang-format off
    nofralloc
/* 8013D590 0013A170  7C 08 02 A6 */	mflr r0
/* 8013D594 0013A174  90 01 00 04 */	stw r0, 4(r1)
/* 8013D598 0013A178  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D59C 0013A17C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D5A0 0013A180  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013D5A4 0013A184  7C 7E 1B 78 */	mr r30, r3
/* 8013D5A8 0013A188  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D5AC 0013A18C  7F E3 FB 78 */	mr r3, r31
/* 8013D5B0 0013A190  4B F4 00 25 */	bl func_8007D5D4
/* 8013D5B4 0013A194  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 8013D5B8 0013A198  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013D5BC 0013A19C  C0 42 A2 58 */	lfs f2, lbl_804D9C38(r2)
/* 8013D5C0 0013A1A0  7F C3 F3 78 */	mr r3, r30
/* 8013D5C4 0013A1A4  C0 62 A2 50 */	lfs f3, lbl_804D9C30(r2)
/* 8013D5C8 0013A1A8  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 8013D5CC 0013A1AC  38 80 01 6C */	li r4, 0x16c
/* 8013D5D0 0013A1B0  38 C0 00 00 */	li r6, 0
/* 8013D5D4 0013A1B4  4B F2 BD D9 */	bl Fighter_ActionStateChange_800693AC
/* 8013D5D8 0013A1B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D5DC 0013A1BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D5E0 0013A1C0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013D5E4 0013A1C4  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D5E8 0013A1C8  7C 08 03 A6 */	mtlr r0
/* 8013D5EC 0013A1CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013D5F0()
{ // clang-format off
    nofralloc
/* 8013D5F0 0013A1D0  7C 08 02 A6 */	mflr r0
/* 8013D5F4 0013A1D4  90 01 00 04 */	stw r0, 4(r1)
/* 8013D5F8 0013A1D8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D5FC 0013A1DC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D600 0013A1E0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8013D604 0013A1E4  7C 7E 1B 78 */	mr r30, r3
/* 8013D608 0013A1E8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D60C 0013A1EC  7F E3 FB 78 */	mr r3, r31
/* 8013D610 0013A1F0  4B F4 01 ED */	bl func_8007D7FC
/* 8013D614 0013A1F4  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 8013D618 0013A1F8  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013D61C 0013A1FC  C0 42 A2 58 */	lfs f2, lbl_804D9C38(r2)
/* 8013D620 0013A200  7F C3 F3 78 */	mr r3, r30
/* 8013D624 0013A204  C0 62 A2 50 */	lfs f3, lbl_804D9C30(r2)
/* 8013D628 0013A208  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 8013D62C 0013A20C  38 80 01 6B */	li r4, 0x16b
/* 8013D630 0013A210  38 C0 00 00 */	li r6, 0
/* 8013D634 0013A214  4B F2 BD 79 */	bl Fighter_ActionStateChange_800693AC
/* 8013D638 0013A218  7F E3 FB 78 */	mr r3, r31
/* 8013D63C 0013A21C  4B F3 FE 2D */	bl func_8007D468
/* 8013D640 0013A220  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D644 0013A224  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D648 0013A228  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8013D64C 0013A22C  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D650 0013A230  7C 08 03 A6 */	mtlr r0
/* 8013D654 0013A234  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern char* lbl_804D3E98;
extern char* lbl_804D3EA0;
extern char* lbl_804D3EA8;
extern f64 const lbl_804D9C40;
extern f32 const lbl_804D9C48;

#pragma push
asm unk_t lbl_8013D658()
{ // clang-format off
    nofralloc
/* 8013D658 0013A238  7C 08 02 A6 */	mflr r0
/* 8013D65C 0013A23C  90 01 00 04 */	stw r0, 4(r1)
/* 8013D660 0013A240  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8013D664 0013A244  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8013D668 0013A248  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8013D66C 0013A24C  80 03 00 28 */	lwz r0, 0x28(r3)
/* 8013D670 0013A250  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D674 0013A254  28 00 00 00 */	cmplwi r0, 0
/* 8013D678 0013A258  7C 1E 03 78 */	mr r30, r0
/* 8013D67C 0013A25C  40 82 00 14 */	bne lbl_8013D690
/* 8013D680 0013A260  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013D684 0013A264  38 80 02 F8 */	li r4, 0x2f8
/* 8013D688 0013A268  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013D68C 0013A26C  48 24 AB 95 */	bl __assert
lbl_8013D690:
/* 8013D690 0013A270  34 1F 22 30 */	addic. r0, r31, 0x2230
/* 8013D694 0013A274  40 82 00 14 */	bne lbl_8013D6A8
/* 8013D698 0013A278  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013D69C 0013A27C  38 80 02 F9 */	li r4, 0x2f9
/* 8013D6A0 0013A280  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013D6A4 0013A284  48 24 AB 7D */	bl __assert
lbl_8013D6A8:
/* 8013D6A8 0013A288  80 7F 22 30 */	lwz r3, 0x2230(r31)
/* 8013D6AC 0013A28C  80 1F 22 34 */	lwz r0, 0x2234(r31)
/* 8013D6B0 0013A290  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 8013D6B4 0013A294  90 1E 00 30 */	stw r0, 0x30(r30)
/* 8013D6B8 0013A298  80 1F 22 38 */	lwz r0, 0x2238(r31)
/* 8013D6BC 0013A29C  90 1E 00 34 */	stw r0, 0x34(r30)
/* 8013D6C0 0013A2A0  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8013D6C4 0013A2A4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013D6C8 0013A2A8  40 82 00 4C */	bne lbl_8013D714
/* 8013D6CC 0013A2AC  28 1E 00 00 */	cmplwi r30, 0
/* 8013D6D0 0013A2B0  41 82 00 44 */	beq lbl_8013D714
/* 8013D6D4 0013A2B4  40 82 00 14 */	bne lbl_8013D6E8
/* 8013D6D8 0013A2B8  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013D6DC 0013A2BC  38 80 02 34 */	li r4, 0x234
/* 8013D6E0 0013A2C0  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013D6E4 0013A2C4  48 24 AB 3D */	bl __assert
lbl_8013D6E8:
/* 8013D6E8 0013A2C8  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8013D6EC 0013A2CC  38 60 00 00 */	li r3, 0
/* 8013D6F0 0013A2D0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013D6F4 0013A2D4  40 82 00 10 */	bne lbl_8013D704
/* 8013D6F8 0013A2D8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013D6FC 0013A2DC  41 82 00 08 */	beq lbl_8013D704
/* 8013D700 0013A2E0  38 60 00 01 */	li r3, 1
lbl_8013D704:
/* 8013D704 0013A2E4  2C 03 00 00 */	cmpwi r3, 0
/* 8013D708 0013A2E8  40 82 00 0C */	bne lbl_8013D714
/* 8013D70C 0013A2EC  7F C3 F3 78 */	mr r3, r30
/* 8013D710 0013A2F0  48 23 5B D9 */	bl HSD_JObjSetMtxDirtySub
lbl_8013D714:
/* 8013D714 0013A2F4  C8 22 A2 60 */	lfd f1, lbl_804D9C40(r2)
/* 8013D718 0013A2F8  7F E3 FB 78 */	mr r3, r31
/* 8013D71C 0013A2FC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013D720 0013A300  38 80 00 00 */	li r4, 0
/* 8013D724 0013A304  FC 21 00 32 */	fmul f1, f1, f0
/* 8013D728 0013A308  FC 20 08 18 */	frsp f1, f1
/* 8013D72C 0013A30C  4B F3 83 C5 */	bl func_80075AF0
/* 8013D730 0013A310  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013D734 0013A314  C0 3F 23 60 */	lfs f1, 0x2360(r31)
/* 8013D738 0013A318  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8013D73C 0013A31C  41 82 00 08 */	beq lbl_8013D744
/* 8013D740 0013A320  D0 3F 00 2C */	stfs f1, 0x2c(r31)
lbl_8013D744:
/* 8013D744 0013A324  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013D748 0013A328  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013D74C 0013A32C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013D750 0013A330  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8013D754 0013A334  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8013D758 0013A338  38 21 00 20 */	addi r1, r1, 0x20
/* 8013D75C 0013A33C  7C 08 03 A6 */	mtlr r0
/* 8013D760 0013A340  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D9C4C;

#pragma push
asm unk_t lbl_8013D764()
{ // clang-format off
    nofralloc
/* 8013D764 0013A344  7C 08 02 A6 */	mflr r0
/* 8013D768 0013A348  90 01 00 04 */	stw r0, 4(r1)
/* 8013D76C 0013A34C  38 00 00 00 */	li r0, 0
/* 8013D770 0013A350  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8013D774 0013A354  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8013D778 0013A358  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8013D77C 0013A35C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8013D780 0013A360  7C 7D 1B 78 */	mr r29, r3
/* 8013D784 0013A364  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D788 0013A368  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013D78C 0013A36C  90 1F 23 4C */	stw r0, 0x234c(r31)
/* 8013D790 0013A370  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8013D794 0013A374  2C 00 01 66 */	cmpwi r0, 0x166
/* 8013D798 0013A378  40 80 00 18 */	bge lbl_8013D7B0
/* 8013D79C 0013A37C  2C 00 01 60 */	cmpwi r0, 0x160
/* 8013D7A0 0013A380  40 80 00 F4 */	bge lbl_8013D894
/* 8013D7A4 0013A384  2C 00 01 5E */	cmpwi r0, 0x15e
/* 8013D7A8 0013A388  40 80 00 10 */	bge lbl_8013D7B8
/* 8013D7AC 0013A38C  48 00 00 E8 */	b lbl_8013D894
lbl_8013D7B0:
/* 8013D7B0 0013A390  2C 00 01 68 */	cmpwi r0, 0x168
/* 8013D7B4 0013A394  40 80 00 E0 */	bge lbl_8013D894
lbl_8013D7B8:
/* 8013D7B8 0013A398  80 9E 00 38 */	lwz r4, 0x38(r30)
/* 8013D7BC 0013A39C  7F A3 EB 78 */	mr r3, r29
/* 8013D7C0 0013A3A0  80 1F 23 40 */	lwz r0, 0x2340(r31)
/* 8013D7C4 0013A3A4  7C 04 00 50 */	subf r0, r4, r0
/* 8013D7C8 0013A3A8  90 1F 23 40 */	stw r0, 0x2340(r31)
/* 8013D7CC 0013A3AC  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 8013D7D0 0013A3B0  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 8013D7D4 0013A3B4  4B F3 D8 25 */	bl func_8007AFF8
/* 8013D7D8 0013A3B8  C0 42 A2 68 */	lfs f2, lbl_804D9C48(r2)
/* 8013D7DC 0013A3BC  3C 80 0C 4C */	lis r4, 0x0C4C0292@ha
/* 8013D7E0 0013A3C0  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013D7E4 0013A3C4  7F A3 EB 78 */	mr r3, r29
/* 8013D7E8 0013A3C8  FC 60 10 90 */	fmr f3, f2
/* 8013D7EC 0013A3CC  38 A4 02 92 */	addi r5, r4, 0x0C4C0292@l
/* 8013D7F0 0013A3D0  38 80 01 6A */	li r4, 0x16a
/* 8013D7F4 0013A3D4  38 C0 00 00 */	li r6, 0
/* 8013D7F8 0013A3D8  4B F2 BB B5 */	bl Fighter_ActionStateChange_800693AC
/* 8013D7FC 0013A3DC  3C 60 80 14 */	lis r3, lbl_8013D658@ha
/* 8013D800 0013A3E0  38 63 D6 58 */	addi r3, r3, lbl_8013D658@l
/* 8013D804 0013A3E4  90 7F 21 E4 */	stw r3, 0x21e4(r31)
/* 8013D808 0013A3E8  38 00 00 00 */	li r0, 0
/* 8013D80C 0013A3EC  90 7F 21 DC */	stw r3, 0x21dc(r31)
/* 8013D810 0013A3F0  90 1F 21 C0 */	stw r0, 0x21c0(r31)
/* 8013D814 0013A3F4  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8013D818 0013A3F8  2C 00 00 00 */	cmpwi r0, 0
/* 8013D81C 0013A3FC  40 82 00 20 */	bne lbl_8013D83C
/* 8013D820 0013A400  C0 3F 00 EC */	lfs f1, 0xec(r31)
/* 8013D824 0013A404  7F E3 FB 78 */	mr r3, r31
/* 8013D828 0013A408  C0 1E 00 88 */	lfs f0, 0x88(r30)
/* 8013D82C 0013A40C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013D830 0013A410  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8013D834 0013A414  4B F3 FD A1 */	bl func_8007D5D4
/* 8013D838 0013A418  48 00 00 14 */	b lbl_8013D84C
lbl_8013D83C:
/* 8013D83C 0013A41C  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 8013D840 0013A420  C0 1E 00 88 */	lfs f0, 0x88(r30)
/* 8013D844 0013A424  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013D848 0013A428  D0 1F 00 80 */	stfs f0, 0x80(r31)
lbl_8013D84C:
/* 8013D84C 0013A42C  C0 1E 00 8C */	lfs f0, 0x8c(r30)
/* 8013D850 0013A430  38 7F 00 00 */	addi r3, r31, 0
/* 8013D854 0013A434  38 80 00 00 */	li r4, 0
/* 8013D858 0013A438  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8013D85C 0013A43C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013D860 0013A440  D0 1F 00 78 */	stfs f0, 0x78(r31)
/* 8013D864 0013A444  D0 1F 00 74 */	stfs f0, 0x74(r31)
/* 8013D868 0013A448  D0 1F 00 E4 */	stfs f0, 0xe4(r31)
/* 8013D86C 0013A44C  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8013D870 0013A450  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013D874 0013A454  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013D878 0013A458  4B F3 82 79 */	bl func_80075AF0
/* 8013D87C 0013A45C  3C 80 00 04 */	lis r4, 0x0003D0D6@ha
/* 8013D880 0013A460  38 7F 00 00 */	addi r3, r31, 0
/* 8013D884 0013A464  38 84 D0 D6 */	addi r4, r4, 0x0003D0D6@l
/* 8013D888 0013A468  38 A0 00 7F */	li r5, 0x7f
/* 8013D88C 0013A46C  38 C0 00 40 */	li r6, 0x40
/* 8013D890 0013A470  4B F4 A8 B9 */	bl func_80088148
lbl_8013D894:
/* 8013D894 0013A474  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013D898 0013A478  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8013D89C 0013A47C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8013D8A0 0013A480  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8013D8A4 0013A484  38 21 00 28 */	addi r1, r1, 0x28
/* 8013D8A8 0013A488  7C 08 03 A6 */	mtlr r0
/* 8013D8AC 0013A48C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013D8B0()
{ // clang-format off
    nofralloc
/* 8013D8B0 0013A490  7C 08 02 A6 */	mflr r0
/* 8013D8B4 0013A494  90 01 00 04 */	stw r0, 4(r1)
/* 8013D8B8 0013A498  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8013D8BC 0013A49C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8013D8C0 0013A4A0  7C 7F 1B 78 */	mr r31, r3
/* 8013D8C4 0013A4A4  4B F4 BF 61 */	bl func_80089824
/* 8013D8C8 0013A4A8  7F E3 FB 78 */	mr r3, r31
/* 8013D8CC 0013A4AC  4B F4 B9 D5 */	bl func_800892A0
/* 8013D8D0 0013A4B0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013D8D4 0013A4B4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8013D8D8 0013A4B8  38 21 00 18 */	addi r1, r1, 0x18
/* 8013D8DC 0013A4BC  7C 08 03 A6 */	mtlr r0
/* 8013D8E0 0013A4C0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013D8E4(){ // clang-format off
    nofralloc
/* 8013D8E4 0013A4C4  7C 08 02 A6 */	mflr r0
/* 8013D8E8 0013A4C8  90 01 00 04 */	stw r0, 4(r1)
/* 8013D8EC 0013A4CC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8013D8F0 0013A4D0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8013D8F4 0013A4D4  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8013D8F8 0013A4D8  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8013D8FC 0013A4DC  7C 7D 1B 78 */	mr r29, r3
/* 8013D900 0013A4E0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013D904 0013A4E4  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8013D908 0013A4E8  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013D90C 0013A4EC  2C 00 00 01 */	cmpwi r0, 1
/* 8013D910 0013A4F0  80 1F 09 14 */	lwz r0, 0x914(r31)
/* 8013D914 0013A4F4  40 82 00 1C */	bne lbl_8013D930
/* 8013D918 0013A4F8  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 8013D91C 0013A4FC  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013D920 0013A500  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013D924 0013A504  40 80 00 20 */	bge lbl_8013D944
/* 8013D928 0013A508  FC 20 08 50 */	fneg f1, f1
/* 8013D92C 0013A50C  48 00 00 18 */	b lbl_8013D944
lbl_8013D930:
/* 8013D930 0013A510  C0 3F 00 EC */	lfs f1, 0xec(r31)
/* 8013D934 0013A514  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013D938 0013A518  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013D93C 0013A51C  40 80 00 08 */	bge lbl_8013D944
/* 8013D940 0013A520  FC 20 08 50 */	fneg f1, f1
lbl_8013D944:
/* 8013D944 0013A524  C0 1E 00 CC */	lfs f0, 0xcc(r30)
/* 8013D948 0013A528  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013D94C 0013A52C  40 80 00 18 */	bge lbl_8013D964
/* 8013D950 0013A530  38 00 00 00 */	li r0, 0
/* 8013D954 0013A534  90 1F 09 14 */	stw r0, 0x914(r31)
/* 8013D958 0013A538  7F E3 FB 78 */	mr r3, r31
/* 8013D95C 0013A53C  4B F8 26 51 */	bl func_800BFFAC
/* 8013D960 0013A540  48 00 00 14 */	b lbl_8013D974
lbl_8013D964:
/* 8013D964 0013A544  2C 00 00 00 */	cmpwi r0, 0
/* 8013D968 0013A548  40 82 00 0C */	bne lbl_8013D974
/* 8013D96C 0013A54C  38 00 00 01 */	li r0, 1
/* 8013D970 0013A550  90 1F 09 14 */	stw r0, 0x914(r31)
lbl_8013D974:
/* 8013D974 0013A554  80 1F 09 14 */	lwz r0, 0x914(r31)
/* 8013D978 0013A558  2C 00 00 00 */	cmpwi r0, 0
/* 8013D97C 0013A55C  41 82 00 8C */	beq lbl_8013DA08
/* 8013D980 0013A560  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8013D984 0013A564  2C 00 00 01 */	cmpwi r0, 1
/* 8013D988 0013A568  40 82 00 38 */	bne lbl_8013D9C0
/* 8013D98C 0013A56C  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 8013D990 0013A570  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013D994 0013A574  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013D998 0013A578  40 80 00 08 */	bge lbl_8013D9A0
/* 8013D99C 0013A57C  FC 40 10 50 */	fneg f2, f2
lbl_8013D9A0:
/* 8013D9A0 0013A580  C0 1E 00 80 */	lfs f0, 0x80(r30)
/* 8013D9A4 0013A584  C0 3E 00 84 */	lfs f1, 0x84(r30)
/* 8013D9A8 0013A588  EC 00 10 2A */	fadds f0, f0, f2
/* 8013D9AC 0013A58C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013D9B0 0013A590  FC 00 00 1E */	fctiwz f0, f0
/* 8013D9B4 0013A594  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8013D9B8 0013A598  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 8013D9BC 0013A59C  48 00 00 34 */	b lbl_8013D9F0
lbl_8013D9C0:
/* 8013D9C0 0013A5A0  C0 5F 00 EC */	lfs f2, 0xec(r31)
/* 8013D9C4 0013A5A4  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013D9C8 0013A5A8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013D9CC 0013A5AC  40 80 00 08 */	bge lbl_8013D9D4
/* 8013D9D0 0013A5B0  FC 40 10 50 */	fneg f2, f2
lbl_8013D9D4:
/* 8013D9D4 0013A5B4  C0 1E 00 80 */	lfs f0, 0x80(r30)
/* 8013D9D8 0013A5B8  C0 3E 00 84 */	lfs f1, 0x84(r30)
/* 8013D9DC 0013A5BC  EC 00 10 2A */	fadds f0, f0, f2
/* 8013D9E0 0013A5C0  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013D9E4 0013A5C4  FC 00 00 1E */	fctiwz f0, f0
/* 8013D9E8 0013A5C8  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8013D9EC 0013A5CC  80 81 00 1C */	lwz r4, 0x1c(r1)
lbl_8013D9F0:
/* 8013D9F0 0013A5D0  2C 04 00 01 */	cmpwi r4, 1
/* 8013D9F4 0013A5D4  40 80 00 08 */	bge lbl_8013D9FC
/* 8013D9F8 0013A5D8  38 80 00 01 */	li r4, 1
lbl_8013D9FC:
/* 8013D9FC 0013A5DC  38 BD 00 00 */	addi r5, r29, 0
/* 8013DA00 0013A5E0  38 7F 09 14 */	addi r3, r31, 0x914
/* 8013DA04 0013A5E4  4B F3 D1 CD */	bl func_8007ABD0
lbl_8013DA08:
/* 8013DA08 0013A5E8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8013DA0C 0013A5EC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8013DA10 0013A5F0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8013DA14 0013A5F4  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8013DA18 0013A5F8  38 21 00 30 */	addi r1, r1, 0x30
/* 8013DA1C 0013A5FC  7C 08 03 A6 */	mtlr r0
/* 8013DA20 0013A600  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

unk_t lbl_8014222C();
extern f32 const lbl_804D9C50;

#pragma push
asm unk_t func_8013DA24()
{ // clang-format off
    nofralloc
/* 8013DA24 0013A604  7C 08 02 A6 */	mflr r0
/* 8013DA28 0013A608  90 01 00 04 */	stw r0, 4(r1)
/* 8013DA2C 0013A60C  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8013DA30 0013A610  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 8013DA34 0013A614  FF E0 08 90 */	fmr f31, f1
/* 8013DA38 0013A618  BF 61 00 34 */	stmw r27, 0x34(r1)
/* 8013DA3C 0013A61C  7C 7B 1B 78 */	mr r27, r3
/* 8013DA40 0013A620  3B C4 00 00 */	addi r30, r4, 0
/* 8013DA44 0013A624  3B A5 00 00 */	addi r29, r5, 0
/* 8013DA48 0013A628  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013DA4C 0013A62C  83 9F 02 D4 */	lwz r28, 0x2d4(r31)
/* 8013DA50 0013A630  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 8013DA54 0013A634  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 8013DA58 0013A638  4B F3 D5 A1 */	bl func_8007AFF8
/* 8013DA5C 0013A63C  2C 1E 00 00 */	cmpwi r30, 0
/* 8013DA60 0013A640  40 82 00 5C */	bne lbl_8013DABC
/* 8013DA64 0013A644  C0 22 A2 70 */	lfs f1, lbl_804D9C50(r2)
/* 8013DA68 0013A648  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013DA6C 0013A64C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013DA70 0013A650  40 82 00 0C */	bne lbl_8013DA7C
/* 8013DA74 0013A654  38 80 01 60 */	li r4, 0x160
/* 8013DA78 0013A658  48 00 00 08 */	b lbl_8013DA80
lbl_8013DA7C:
/* 8013DA7C 0013A65C  38 80 01 61 */	li r4, 0x161
lbl_8013DA80:
/* 8013DA80 0013A660  FC 20 F8 90 */	fmr f1, f31
/* 8013DA84 0013A664  C0 42 A2 70 */	lfs f2, lbl_804D9C50(r2)
/* 8013DA88 0013A668  C0 62 A2 68 */	lfs f3, lbl_804D9C48(r2)
/* 8013DA8C 0013A66C  38 7B 00 00 */	addi r3, r27, 0
/* 8013DA90 0013A670  38 BD 00 00 */	addi r5, r29, 0
/* 8013DA94 0013A674  38 C0 00 00 */	li r6, 0
/* 8013DA98 0013A678  4B F2 B9 15 */	bl Fighter_ActionStateChange_800693AC
/* 8013DA9C 0013A67C  C0 3F 00 EC */	lfs f1, 0xec(r31)
/* 8013DAA0 0013A680  C0 1C 00 90 */	lfs f0, 0x90(r28)
/* 8013DAA4 0013A684  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013DAA8 0013A688  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8013DAAC 0013A68C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DAB0 0013A690  D0 1F 00 78 */	stfs f0, 0x78(r31)
/* 8013DAB4 0013A694  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8013DAB8 0013A698  48 00 00 68 */	b lbl_8013DB20
lbl_8013DABC:
/* 8013DABC 0013A69C  C0 22 A2 70 */	lfs f1, lbl_804D9C50(r2)
/* 8013DAC0 0013A6A0  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013DAC4 0013A6A4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013DAC8 0013A6A8  40 82 00 0C */	bne lbl_8013DAD4
/* 8013DACC 0013A6AC  38 80 01 68 */	li r4, 0x168
/* 8013DAD0 0013A6B0  48 00 00 08 */	b lbl_8013DAD8
lbl_8013DAD4:
/* 8013DAD4 0013A6B4  38 80 01 69 */	li r4, 0x169
lbl_8013DAD8:
/* 8013DAD8 0013A6B8  FC 20 F8 90 */	fmr f1, f31
/* 8013DADC 0013A6BC  C0 42 A2 70 */	lfs f2, lbl_804D9C50(r2)
/* 8013DAE0 0013A6C0  C0 62 A2 68 */	lfs f3, lbl_804D9C48(r2)
/* 8013DAE4 0013A6C4  38 7B 00 00 */	addi r3, r27, 0
/* 8013DAE8 0013A6C8  38 BD 00 00 */	addi r5, r29, 0
/* 8013DAEC 0013A6CC  38 C0 00 00 */	li r6, 0
/* 8013DAF0 0013A6D0  4B F2 B8 BD */	bl Fighter_ActionStateChange_800693AC
/* 8013DAF4 0013A6D4  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 8013DAF8 0013A6D8  C0 1C 00 90 */	lfs f0, 0x90(r28)
/* 8013DAFC 0013A6DC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013DB00 0013A6E0  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8013DB04 0013A6E4  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 8013DB08 0013A6E8  C0 1C 00 94 */	lfs f0, 0x94(r28)
/* 8013DB0C 0013A6EC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013DB10 0013A6F0  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8013DB14 0013A6F4  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DB18 0013A6F8  D0 1F 00 E4 */	stfs f0, 0xe4(r31)
/* 8013DB1C 0013A6FC  D0 1F 00 EC */	stfs f0, 0xec(r31)
lbl_8013DB20:
/* 8013DB20 0013A700  3C 60 80 14 */	lis r3, lbl_8013D658@ha
/* 8013DB24 0013A704  80 BB 00 2C */	lwz r5, 0x2c(r27)
/* 8013DB28 0013A708  38 03 D6 58 */	addi r0, r3, lbl_8013D658@l
/* 8013DB2C 0013A70C  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 8013DB30 0013A710  3C 80 80 14 */	lis r4, lbl_8013D764@ha
/* 8013DB34 0013A714  38 84 D7 64 */	addi r4, r4, lbl_8013D764@l
/* 8013DB38 0013A718  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 8013DB3C 0013A71C  3C 60 80 14 */	lis r3, lbl_8014222C@ha
/* 8013DB40 0013A720  38 03 22 2C */	addi r0, r3, lbl_8014222C@l
/* 8013DB44 0013A724  90 85 21 C0 */	stw r4, 0x21c0(r5)
/* 8013DB48 0013A728  90 05 21 F8 */	stw r0, 0x21f8(r5)
/* 8013DB4C 0013A72C  83 DB 00 28 */	lwz r30, 0x28(r27)
/* 8013DB50 0013A730  83 9B 00 2C */	lwz r28, 0x2c(r27)
/* 8013DB54 0013A734  28 1E 00 00 */	cmplwi r30, 0
/* 8013DB58 0013A738  3B BC 22 30 */	addi r29, r28, 0x2230
/* 8013DB5C 0013A73C  40 82 00 14 */	bne lbl_8013DB70
/* 8013DB60 0013A740  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013DB64 0013A744  38 80 02 F8 */	li r4, 0x2f8
/* 8013DB68 0013A748  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013DB6C 0013A74C  48 24 A6 B5 */	bl __assert
lbl_8013DB70:
/* 8013DB70 0013A750  28 1D 00 00 */	cmplwi r29, 0
/* 8013DB74 0013A754  40 82 00 14 */	bne lbl_8013DB88
/* 8013DB78 0013A758  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013DB7C 0013A75C  38 80 02 F9 */	li r4, 0x2f9
/* 8013DB80 0013A760  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013DB84 0013A764  48 24 A6 9D */	bl __assert
lbl_8013DB88:
/* 8013DB88 0013A768  80 7D 00 00 */	lwz r3, 0(r29)
/* 8013DB8C 0013A76C  80 1D 00 04 */	lwz r0, 4(r29)
/* 8013DB90 0013A770  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 8013DB94 0013A774  90 1E 00 30 */	stw r0, 0x30(r30)
/* 8013DB98 0013A778  80 1D 00 08 */	lwz r0, 8(r29)
/* 8013DB9C 0013A77C  90 1E 00 34 */	stw r0, 0x34(r30)
/* 8013DBA0 0013A780  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8013DBA4 0013A784  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013DBA8 0013A788  40 82 00 4C */	bne lbl_8013DBF4
/* 8013DBAC 0013A78C  28 1E 00 00 */	cmplwi r30, 0
/* 8013DBB0 0013A790  41 82 00 44 */	beq lbl_8013DBF4
/* 8013DBB4 0013A794  40 82 00 14 */	bne lbl_8013DBC8
/* 8013DBB8 0013A798  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013DBBC 0013A79C  38 80 02 34 */	li r4, 0x234
/* 8013DBC0 0013A7A0  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013DBC4 0013A7A4  48 24 A6 5D */	bl __assert
lbl_8013DBC8:
/* 8013DBC8 0013A7A8  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8013DBCC 0013A7AC  38 60 00 00 */	li r3, 0
/* 8013DBD0 0013A7B0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013DBD4 0013A7B4  40 82 00 10 */	bne lbl_8013DBE4
/* 8013DBD8 0013A7B8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013DBDC 0013A7BC  41 82 00 08 */	beq lbl_8013DBE4
/* 8013DBE0 0013A7C0  38 60 00 01 */	li r3, 1
lbl_8013DBE4:
/* 8013DBE4 0013A7C4  2C 03 00 00 */	cmpwi r3, 0
/* 8013DBE8 0013A7C8  40 82 00 0C */	bne lbl_8013DBF4
/* 8013DBEC 0013A7CC  7F C3 F3 78 */	mr r3, r30
/* 8013DBF0 0013A7D0  48 23 56 F9 */	bl HSD_JObjSetMtxDirtySub
lbl_8013DBF4:
/* 8013DBF4 0013A7D4  C8 22 A2 60 */	lfd f1, lbl_804D9C40(r2)
/* 8013DBF8 0013A7D8  7F 83 E3 78 */	mr r3, r28
/* 8013DBFC 0013A7DC  C0 1C 00 2C */	lfs f0, 0x2c(r28)
/* 8013DC00 0013A7E0  38 80 00 00 */	li r4, 0
/* 8013DC04 0013A7E4  FC 21 00 32 */	fmul f1, f1, f0
/* 8013DC08 0013A7E8  FC 20 08 18 */	frsp f1, f1
/* 8013DC0C 0013A7EC  4B F3 7E E5 */	bl func_80075AF0
/* 8013DC10 0013A7F0  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DC14 0013A7F4  C0 3C 23 60 */	lfs f1, 0x2360(r28)
/* 8013DC18 0013A7F8  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8013DC1C 0013A7FC  41 82 00 08 */	beq lbl_8013DC24
/* 8013DC20 0013A800  D0 3C 00 2C */	stfs f1, 0x2c(r28)
lbl_8013DC24:
/* 8013DC24 0013A804  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DC28 0013A808  38 7F 00 00 */	addi r3, r31, 0
/* 8013DC2C 0013A80C  38 80 00 00 */	li r4, 0
/* 8013DC30 0013A810  D0 1C 23 60 */	stfs f0, 0x2360(r28)
/* 8013DC34 0013A814  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013DC38 0013A818  C8 22 A2 60 */	lfd f1, lbl_804D9C40(r2)
/* 8013DC3C 0013A81C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013DC40 0013A820  FC 21 00 32 */	fmul f1, f1, f0
/* 8013DC44 0013A824  FC 20 08 18 */	frsp f1, f1
/* 8013DC48 0013A828  4B F3 7E A9 */	bl func_80075AF0
/* 8013DC4C 0013A82C  BB 61 00 34 */	lmw r27, 0x34(r1)
/* 8013DC50 0013A830  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8013DC54 0013A834  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 8013DC58 0013A838  38 21 00 50 */	addi r1, r1, 0x50
/* 8013DC5C 0013A83C  7C 08 03 A6 */	mtlr r0
/* 8013DC60 0013A840  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8013DC64()
{ // clang-format off
    nofralloc
/* 8013DC64 0013A844  7C 08 02 A6 */	mflr r0
/* 8013DC68 0013A848  90 01 00 04 */	stw r0, 4(r1)
/* 8013DC6C 0013A84C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8013DC70 0013A850  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8013DC74 0013A854  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8013DC78 0013A858  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8013DC7C 0013A85C  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 8013DC80 0013A860  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013DC84 0013A864  28 1E 00 00 */	cmplwi r30, 0
/* 8013DC88 0013A868  83 BF 02 D4 */	lwz r29, 0x2d4(r31)
/* 8013DC8C 0013A86C  40 82 00 14 */	bne lbl_8013DCA0
/* 8013DC90 0013A870  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013DC94 0013A874  38 80 03 37 */	li r4, 0x337
/* 8013DC98 0013A878  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013DC9C 0013A87C  48 24 A5 85 */	bl __assert
lbl_8013DCA0:
/* 8013DCA0 0013A880  34 1F 22 30 */	addic. r0, r31, 0x2230
/* 8013DCA4 0013A884  40 82 00 14 */	bne lbl_8013DCB8
/* 8013DCA8 0013A888  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013DCAC 0013A88C  38 80 03 38 */	li r4, 0x338
/* 8013DCB0 0013A890  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013DCB4 0013A894  48 24 A5 6D */	bl __assert
lbl_8013DCB8:
/* 8013DCB8 0013A898  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8013DCBC 0013A89C  3C 80 80 14 */	lis r4, lbl_8013D764@ha
/* 8013DCC0 0013A8A0  80 1E 00 30 */	lwz r0, 0x30(r30)
/* 8013DCC4 0013A8A4  3C 60 80 14 */	lis r3, lbl_8014222C@ha
/* 8013DCC8 0013A8A8  38 C0 FF FF */	li r6, -1
/* 8013DCCC 0013A8AC  90 BF 22 30 */	stw r5, 0x2230(r31)
/* 8013DCD0 0013A8B0  38 A0 00 00 */	li r5, 0
/* 8013DCD4 0013A8B4  38 84 D7 64 */	addi r4, r4, lbl_8013D764@l
/* 8013DCD8 0013A8B8  90 1F 22 34 */	stw r0, 0x2234(r31)
/* 8013DCDC 0013A8BC  38 03 22 2C */	addi r0, r3, lbl_8014222C@l
/* 8013DCE0 0013A8C0  80 7E 00 34 */	lwz r3, 0x34(r30)
/* 8013DCE4 0013A8C4  90 7F 22 38 */	stw r3, 0x2238(r31)
/* 8013DCE8 0013A8C8  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DCEC 0013A8CC  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8013DCF0 0013A8D0  80 7D 00 34 */	lwz r3, 0x34(r29)
/* 8013DCF4 0013A8D4  90 7F 23 40 */	stw r3, 0x2340(r31)
/* 8013DCF8 0013A8D8  90 DF 23 44 */	stw r6, 0x2344(r31)
/* 8013DCFC 0013A8DC  90 DF 23 48 */	stw r6, 0x2348(r31)
/* 8013DD00 0013A8E0  90 BF 23 4C */	stw r5, 0x234c(r31)
/* 8013DD04 0013A8E4  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 8013DD08 0013A8E8  D0 1F 23 78 */	stfs f0, 0x2378(r31)
/* 8013DD0C 0013A8EC  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013DD10 0013A8F0  90 BF 23 64 */	stw r5, 0x2364(r31)
/* 8013DD14 0013A8F4  90 BF 23 68 */	stw r5, 0x2368(r31)
/* 8013DD18 0013A8F8  C0 1D 00 A0 */	lfs f0, 0xa0(r29)
/* 8013DD1C 0013A8FC  FC 00 00 1E */	fctiwz f0, f0
/* 8013DD20 0013A900  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8013DD24 0013A904  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8013DD28 0013A908  90 7F 23 6C */	stw r3, 0x236c(r31)
/* 8013DD2C 0013A90C  90 BF 23 70 */	stw r5, 0x2370(r31)
/* 8013DD30 0013A910  90 9F 21 C0 */	stw r4, 0x21c0(r31)
/* 8013DD34 0013A914  90 1F 21 F8 */	stw r0, 0x21f8(r31)
/* 8013DD38 0013A918  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8013DD3C 0013A91C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8013DD40 0013A920  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8013DD44 0013A924  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8013DD48 0013A928  38 21 00 30 */	addi r1, r1, 0x30
/* 8013DD4C 0013A92C  7C 08 03 A6 */	mtlr r0
/* 8013DD50 0013A930  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f64 const lbl_804D9C58;
extern f32 const lbl_804D9C60;

#pragma push
asm unk_t func_8013DD54()
{ // clang-format off
    nofralloc
/* 8013DD54 0013A934  7C 08 02 A6 */	mflr r0
/* 8013DD58 0013A938  90 01 00 04 */	stw r0, 4(r1)
/* 8013DD5C 0013A93C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8013DD60 0013A940  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8013DD64 0013A944  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013DD68 0013A948  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013DD6C 0013A94C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DD70 0013A950  48 00 00 14 */	b lbl_8013DD84
lbl_8013DD74:
/* 8013DD74 0013A954  C0 3F 23 54 */	lfs f1, 0x2354(r31)
/* 8013DD78 0013A958  FC 21 10 2A */	fadd f1, f1, f2
/* 8013DD7C 0013A95C  FC 20 08 18 */	frsp f1, f1
/* 8013DD80 0013A960  D0 3F 23 54 */	stfs f1, 0x2354(r31)
lbl_8013DD84:
/* 8013DD84 0013A964  C0 3F 23 54 */	lfs f1, 0x2354(r31)
/* 8013DD88 0013A968  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013DD8C 0013A96C  41 80 FF E8 */	blt lbl_8013DD74
/* 8013DD90 0013A970  C8 22 A2 78 */	lfd f1, lbl_804D9C58(r2)
/* 8013DD94 0013A974  48 00 00 14 */	b lbl_8013DDA8
lbl_8013DD98:
/* 8013DD98 0013A978  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 8013DD9C 0013A97C  FC 00 08 28 */	fsub f0, f0, f1
/* 8013DDA0 0013A980  FC 00 00 18 */	frsp f0, f0
/* 8013DDA4 0013A984  D0 1F 23 54 */	stfs f0, 0x2354(r31)
lbl_8013DDA8:
/* 8013DDA8 0013A988  C0 7F 23 54 */	lfs f3, 0x2354(r31)
/* 8013DDAC 0013A98C  FC 03 08 40 */	fcmpo cr0, f3, f1
/* 8013DDB0 0013A990  41 81 FF E8 */	bgt lbl_8013DD98
/* 8013DDB4 0013A994  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DDB8 0013A998  C0 5F 23 78 */	lfs f2, 0x2378(r31)
/* 8013DDBC 0013A99C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8013DDC0 0013A9A0  40 82 00 38 */	bne lbl_8013DDF8
/* 8013DDC4 0013A9A4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013DDC8 0013A9A8  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8013DDCC 0013A9AC  2C 00 00 01 */	cmpwi r0, 1
/* 8013DDD0 0013A9B0  40 82 00 10 */	bne lbl_8013DDE0
/* 8013DDD4 0013A9B4  3C 80 00 04 */	lis r4, 0x0003D0D3@ha
/* 8013DDD8 0013A9B8  38 84 D0 D3 */	addi r4, r4, 0x0003D0D3@l
/* 8013DDDC 0013A9BC  48 00 00 0C */	b lbl_8013DDE8
lbl_8013DDE0:
/* 8013DDE0 0013A9C0  3C 80 00 04 */	lis r4, 0x0003D0D0@ha
/* 8013DDE4 0013A9C4  38 84 D0 D0 */	addi r4, r4, 0x0003D0D0@l
lbl_8013DDE8:
/* 8013DDE8 0013A9C8  38 A0 00 7F */	li r5, 0x7f
/* 8013DDEC 0013A9CC  38 C0 00 40 */	li r6, 0x40
/* 8013DDF0 0013A9D0  4B F4 A7 21 */	bl func_80088510
/* 8013DDF4 0013A9D4  48 00 00 98 */	b lbl_8013DE8C
lbl_8013DDF8:
/* 8013DDF8 0013A9D8  2C 04 00 00 */	cmpwi r4, 0
/* 8013DDFC 0013A9DC  41 82 00 0C */	beq lbl_8013DE08
/* 8013DE00 0013A9E0  C0 22 A2 80 */	lfs f1, lbl_804D9C60(r2)
/* 8013DE04 0013A9E4  48 00 00 08 */	b lbl_8013DE0C
lbl_8013DE08:
/* 8013DE08 0013A9E8  C0 22 A2 70 */	lfs f1, lbl_804D9C50(r2)
lbl_8013DE0C:
/* 8013DE0C 0013A9EC  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 8013DE10 0013A9F0  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8013DE14 0013A9F4  40 82 00 40 */	bne lbl_8013DE54
/* 8013DE18 0013A9F8  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 8013DE1C 0013A9FC  40 80 00 70 */	bge lbl_8013DE8C
/* 8013DE20 0013AA00  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013DE24 0013AA04  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8013DE28 0013AA08  2C 00 00 01 */	cmpwi r0, 1
/* 8013DE2C 0013AA0C  40 82 00 10 */	bne lbl_8013DE3C
/* 8013DE30 0013AA10  3C 80 00 04 */	lis r4, 0x0003D0D3@ha
/* 8013DE34 0013AA14  38 84 D0 D3 */	addi r4, r4, 0x0003D0D3@l
/* 8013DE38 0013AA18  48 00 00 0C */	b lbl_8013DE44
lbl_8013DE3C:
/* 8013DE3C 0013AA1C  3C 80 00 04 */	lis r4, 0x0003D0D0@ha
/* 8013DE40 0013AA20  38 84 D0 D0 */	addi r4, r4, 0x0003D0D0@l
lbl_8013DE44:
/* 8013DE44 0013AA24  38 A0 00 7F */	li r5, 0x7f
/* 8013DE48 0013AA28  38 C0 00 40 */	li r6, 0x40
/* 8013DE4C 0013AA2C  4B F4 A6 C5 */	bl func_80088510
/* 8013DE50 0013AA30  48 00 00 3C */	b lbl_8013DE8C
lbl_8013DE54:
/* 8013DE54 0013AA34  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 8013DE58 0013AA38  40 81 00 34 */	ble lbl_8013DE8C
/* 8013DE5C 0013AA3C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013DE60 0013AA40  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8013DE64 0013AA44  2C 00 00 01 */	cmpwi r0, 1
/* 8013DE68 0013AA48  40 82 00 10 */	bne lbl_8013DE78
/* 8013DE6C 0013AA4C  3C 80 00 04 */	lis r4, 0x0003D0D3@ha
/* 8013DE70 0013AA50  38 84 D0 D3 */	addi r4, r4, 0x0003D0D3@l
/* 8013DE74 0013AA54  48 00 00 0C */	b lbl_8013DE80
lbl_8013DE78:
/* 8013DE78 0013AA58  3C 80 00 04 */	lis r4, 0x0003D0D0@ha
/* 8013DE7C 0013AA5C  38 84 D0 D0 */	addi r4, r4, 0x0003D0D0@l
lbl_8013DE80:
/* 8013DE80 0013AA60  38 A0 00 7F */	li r5, 0x7f
/* 8013DE84 0013AA64  38 C0 00 40 */	li r6, 0x40
/* 8013DE88 0013AA68  4B F4 A6 89 */	bl func_80088510
lbl_8013DE8C:
/* 8013DE8C 0013AA6C  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 8013DE90 0013AA70  D0 1F 23 78 */	stfs f0, 0x2378(r31)
/* 8013DE94 0013AA74  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013DE98 0013AA78  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8013DE9C 0013AA7C  38 21 00 28 */	addi r1, r1, 0x28
/* 8013DEA0 0013AA80  7C 08 03 A6 */	mtlr r0
/* 8013DEA4 0013AA84  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ftPurin_SpecialN_StartAction()
{ // clang-format off
    nofralloc
/* 8013DEA8 0013AA88  7C 08 02 A6 */	mflr r0
/* 8013DEAC 0013AA8C  90 01 00 04 */	stw r0, 4(r1)
/* 8013DEB0 0013AA90  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8013DEB4 0013AA94  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8013DEB8 0013AA98  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8013DEBC 0013AA9C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8013DEC0 0013AAA0  7C 7D 1B 78 */	mr r29, r3
/* 8013DEC4 0013AAA4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013DEC8 0013AAA8  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013DECC 0013AAAC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013DED0 0013AAB0  D0 1F 23 74 */	stfs f0, 0x2374(r31)
/* 8013DED4 0013AAB4  C0 22 A2 70 */	lfs f1, lbl_804D9C50(r2)
/* 8013DED8 0013AAB8  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 8013DEDC 0013AABC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013DEE0 0013AAC0  40 82 00 0C */	bne lbl_8013DEEC
/* 8013DEE4 0013AAC4  38 80 01 5A */	li r4, 0x15a
/* 8013DEE8 0013AAC8  48 00 00 08 */	b lbl_8013DEF0
lbl_8013DEEC:
/* 8013DEEC 0013AACC  38 80 01 5B */	li r4, 0x15b
lbl_8013DEF0:
/* 8013DEF0 0013AAD0  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013DEF4 0013AAD4  7F A3 EB 78 */	mr r3, r29
/* 8013DEF8 0013AAD8  C0 42 A2 70 */	lfs f2, lbl_804D9C50(r2)
/* 8013DEFC 0013AADC  38 A0 00 00 */	li r5, 0
/* 8013DF00 0013AAE0  FC 60 08 90 */	fmr f3, f1
/* 8013DF04 0013AAE4  38 C0 00 00 */	li r6, 0
/* 8013DF08 0013AAE8  4B F2 B4 A5 */	bl Fighter_ActionStateChange_800693AC
/* 8013DF0C 0013AAEC  38 00 00 00 */	li r0, 0
/* 8013DF10 0013AAF0  90 1F 22 0C */	stw r0, 0x220c(r31)
/* 8013DF14 0013AAF4  7F A3 EB 78 */	mr r3, r29
/* 8013DF18 0013AAF8  90 1F 22 08 */	stw r0, 0x2208(r31)
/* 8013DF1C 0013AAFC  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 8013DF20 0013AB00  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 8013DF24 0013AB04  4B F3 0C 81 */	bl func_8006EBA4
/* 8013DF28 0013AB08  7F A3 EB 78 */	mr r3, r29
/* 8013DF2C 0013AB0C  4B FF FD 39 */	bl func_8013DC64
/* 8013DF30 0013AB10  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013DF34 0013AB14  D0 1F 00 78 */	stfs f0, 0x78(r31)
/* 8013DF38 0013AB18  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8013DF3C 0013AB1C  C0 1E 00 44 */	lfs f0, 0x44(r30)
/* 8013DF40 0013AB20  D0 1F 23 5C */	stfs f0, 0x235c(r31)
/* 8013DF44 0013AB24  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8013DF48 0013AB28  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8013DF4C 0013AB2C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8013DF50 0013AB30  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8013DF54 0013AB34  38 21 00 30 */	addi r1, r1, 0x30
/* 8013DF58 0013AB38  7C 08 03 A6 */	mtlr r0
/* 8013DF5C 0013AB3C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ftPurin_SpecialAirN_StartAction()
{ // clang-format off
    nofralloc
/* 8013DF60 0013AB40  7C 08 02 A6 */	mflr r0
/* 8013DF64 0013AB44  90 01 00 04 */	stw r0, 4(r1)
/* 8013DF68 0013AB48  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8013DF6C 0013AB4C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8013DF70 0013AB50  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8013DF74 0013AB54  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8013DF78 0013AB58  7C 7D 1B 78 */	mr r29, r3
/* 8013DF7C 0013AB5C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013DF80 0013AB60  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013DF84 0013AB64  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013DF88 0013AB68  D0 1F 23 74 */	stfs f0, 0x2374(r31)
/* 8013DF8C 0013AB6C  C0 22 A2 70 */	lfs f1, lbl_804D9C50(r2)
/* 8013DF90 0013AB70  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 8013DF94 0013AB74  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8013DF98 0013AB78  40 82 00 0C */	bne lbl_8013DFA4
/* 8013DF9C 0013AB7C  38 80 01 62 */	li r4, 0x162
/* 8013DFA0 0013AB80  48 00 00 08 */	b lbl_8013DFA8
lbl_8013DFA4:
/* 8013DFA4 0013AB84  38 80 01 63 */	li r4, 0x163
lbl_8013DFA8:
/* 8013DFA8 0013AB88  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013DFAC 0013AB8C  7F A3 EB 78 */	mr r3, r29
/* 8013DFB0 0013AB90  C0 42 A2 70 */	lfs f2, lbl_804D9C50(r2)
/* 8013DFB4 0013AB94  38 A0 00 00 */	li r5, 0
/* 8013DFB8 0013AB98  FC 60 08 90 */	fmr f3, f1
/* 8013DFBC 0013AB9C  38 C0 00 00 */	li r6, 0
/* 8013DFC0 0013ABA0  4B F2 B3 ED */	bl Fighter_ActionStateChange_800693AC
/* 8013DFC4 0013ABA4  38 00 00 00 */	li r0, 0
/* 8013DFC8 0013ABA8  90 1F 22 0C */	stw r0, 0x220c(r31)
/* 8013DFCC 0013ABAC  7F A3 EB 78 */	mr r3, r29
/* 8013DFD0 0013ABB0  90 1F 22 08 */	stw r0, 0x2208(r31)
/* 8013DFD4 0013ABB4  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 8013DFD8 0013ABB8  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 8013DFDC 0013ABBC  4B F3 0B C9 */	bl func_8006EBA4
/* 8013DFE0 0013ABC0  7F A3 EB 78 */	mr r3, r29
/* 8013DFE4 0013ABC4  4B FF FC 81 */	bl func_8013DC64
/* 8013DFE8 0013ABC8  C0 1E 00 3C */	lfs f0, 0x3c(r30)
/* 8013DFEC 0013ABCC  D0 1F 00 78 */	stfs f0, 0x78(r31)
/* 8013DFF0 0013ABD0  C0 1E 00 54 */	lfs f0, 0x54(r30)
/* 8013DFF4 0013ABD4  D0 1F 23 5C */	stfs f0, 0x235c(r31)
/* 8013DFF8 0013ABD8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8013DFFC 0013ABDC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8013E000 0013ABE0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8013E004 0013ABE4  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8013E008 0013ABE8  38 21 00 30 */	addi r1, r1, 0x30
/* 8013E00C 0013ABEC  7C 08 03 A6 */	mtlr r0
/* 8013E010 0013ABF0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D9C64;

#pragma push
asm unk_t lbl_8013E014()
{ // clang-format off
    nofralloc
/* 8013E014 0013ABF4  7C 08 02 A6 */	mflr r0
/* 8013E018 0013ABF8  90 01 00 04 */	stw r0, 4(r1)
/* 8013E01C 0013ABFC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8013E020 0013AC00  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8013E024 0013AC04  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8013E028 0013AC08  7C 7E 1B 78 */	mr r30, r3
/* 8013E02C 0013AC0C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8013E030 0013AC10  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E034 0013AC14  7C 9F 23 78 */	mr r31, r4
/* 8013E038 0013AC18  D0 04 23 60 */	stfs f0, 0x2360(r4)
/* 8013E03C 0013AC1C  4B F3 11 FD */	bl ftAnim_IsFramesRemaining
/* 8013E040 0013AC20  2C 03 00 00 */	cmpwi r3, 0
/* 8013E044 0013AC24  40 82 00 94 */	bne lbl_8013E0D8
/* 8013E048 0013AC28  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013E04C 0013AC2C  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013E050 0013AC30  38 7E 00 00 */	addi r3, r30, 0
/* 8013E054 0013AC34  FC 40 08 90 */	fmr f2, f1
/* 8013E058 0013AC38  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013E05C 0013AC3C  FC 60 08 90 */	fmr f3, f1
/* 8013E060 0013AC40  38 80 01 5C */	li r4, 0x15c
/* 8013E064 0013AC44  38 C0 00 00 */	li r6, 0
/* 8013E068 0013AC48  4B F2 B3 45 */	bl Fighter_ActionStateChange_800693AC
/* 8013E06C 0013AC4C  3C 60 80 14 */	lis r3, lbl_8013D658@ha
/* 8013E070 0013AC50  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8013E074 0013AC54  38 03 D6 58 */	addi r0, r3, lbl_8013D658@l
/* 8013E078 0013AC58  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 8013E07C 0013AC5C  3C 80 80 14 */	lis r4, lbl_8013D764@ha
/* 8013E080 0013AC60  38 84 D7 64 */	addi r4, r4, lbl_8013D764@l
/* 8013E084 0013AC64  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 8013E088 0013AC68  3C 60 80 14 */	lis r3, lbl_8014222C@ha
/* 8013E08C 0013AC6C  38 03 22 2C */	addi r0, r3, lbl_8014222C@l
/* 8013E090 0013AC70  90 85 21 C0 */	stw r4, 0x21c0(r5)
/* 8013E094 0013AC74  7F C3 F3 78 */	mr r3, r30
/* 8013E098 0013AC78  90 05 21 F8 */	stw r0, 0x21f8(r5)
/* 8013E09C 0013AC7C  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013E0A0 0013AC80  D0 3F 08 94 */	stfs f1, 0x894(r31)
/* 8013E0A4 0013AC84  4B F3 10 ED */	bl ftAnim_SetAnimRate
/* 8013E0A8 0013AC88  C0 22 A2 84 */	lfs f1, lbl_804D9C64(r2)
/* 8013E0AC 0013AC8C  7F E3 FB 78 */	mr r3, r31
/* 8013E0B0 0013AC90  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013E0B4 0013AC94  38 80 00 00 */	li r4, 0
/* 8013E0B8 0013AC98  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013E0BC 0013AC9C  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8013E0C0 0013ACA0  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8013E0C4 0013ACA4  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E0C8 0013ACA8  D0 1F 00 74 */	stfs f0, 0x74(r31)
/* 8013E0CC 0013ACAC  D0 1F 00 E4 */	stfs f0, 0xe4(r31)
/* 8013E0D0 0013ACB0  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013E0D4 0013ACB4  4B F3 7A 1D */	bl func_80075AF0
lbl_8013E0D8:
/* 8013E0D8 0013ACB8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013E0DC 0013ACBC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8013E0E0 0013ACC0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8013E0E4 0013ACC4  38 21 00 28 */	addi r1, r1, 0x28
/* 8013E0E8 0013ACC8  7C 08 03 A6 */	mtlr r0
/* 8013E0EC 0013ACCC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D9C68;
extern f64 const lbl_804D9C70;

#pragma push
asm unk_t lbl_8013E0F0()
{ // clang-format off
    nofralloc
/* 8013E0F0 0013ACD0  7C 08 02 A6 */	mflr r0
/* 8013E0F4 0013ACD4  38 80 00 00 */	li r4, 0
/* 8013E0F8 0013ACD8  90 01 00 04 */	stw r0, 4(r1)
/* 8013E0FC 0013ACDC  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8013E100 0013ACE0  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8013E104 0013ACE4  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8013E108 0013ACE8  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8013E10C 0013ACEC  7C 7D 1B 78 */	mr r29, r3
/* 8013E110 0013ACF0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013E114 0013ACF4  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013E118 0013ACF8  4B FF FC 3D */	bl func_8013DD54
/* 8013E11C 0013ACFC  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E120 0013AD00  3C 60 43 30 */	lis r3, 0x4330
/* 8013E124 0013AD04  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013E128 0013AD08  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013E12C 0013AD0C  C8 42 A2 90 */	lfd f2, lbl_804D9C70(r2)
/* 8013E130 0013AD10  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013E134 0013AD14  C0 1E 00 A8 */	lfs f0, 0xa8(r30)
/* 8013E138 0013AD18  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8013E13C 0013AD1C  90 61 00 28 */	stw r3, 0x28(r1)
/* 8013E140 0013AD20  C8 21 00 28 */	lfd f1, 0x28(r1)
/* 8013E144 0013AD24  EC 21 10 28 */	fsubs f1, f1, f2
/* 8013E148 0013AD28  EC 01 00 2A */	fadds f0, f1, f0
/* 8013E14C 0013AD2C  FC 00 00 1E */	fctiwz f0, f0
/* 8013E150 0013AD30  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 8013E154 0013AD34  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013E158 0013AD38  90 1F 23 6C */	stw r0, 0x236c(r31)
/* 8013E15C 0013AD3C  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013E160 0013AD40  C0 3E 00 A4 */	lfs f1, 0xa4(r30)
/* 8013E164 0013AD44  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013E168 0013AD48  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8013E16C 0013AD4C  90 61 00 18 */	stw r3, 0x18(r1)
/* 8013E170 0013AD50  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8013E174 0013AD54  EC 00 10 28 */	fsubs f0, f0, f2
/* 8013E178 0013AD58  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8013E17C 0013AD5C  4C 41 13 82 */	cror 2, 1, 2
/* 8013E180 0013AD60  40 82 00 5C */	bne lbl_8013E1DC
/* 8013E184 0013AD64  FC 00 08 1E */	fctiwz f0, f1
/* 8013E188 0013AD68  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8013E18C 0013AD6C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013E190 0013AD70  90 1F 23 6C */	stw r0, 0x236c(r31)
/* 8013E194 0013AD74  80 1F 23 70 */	lwz r0, 0x2370(r31)
/* 8013E198 0013AD78  2C 00 00 00 */	cmpwi r0, 0
/* 8013E19C 0013AD7C  40 82 00 14 */	bne lbl_8013E1B0
/* 8013E1A0 0013AD80  38 7F 00 00 */	addi r3, r31, 0
/* 8013E1A4 0013AD84  38 80 00 05 */	li r4, 5
/* 8013E1A8 0013AD88  38 A0 00 00 */	li r5, 0
/* 8013E1AC 0013AD8C  4B F8 1E 25 */	bl func_800BFFD0
lbl_8013E1B0:
/* 8013E1B0 0013AD90  38 00 00 01 */	li r0, 1
/* 8013E1B4 0013AD94  90 1F 23 70 */	stw r0, 0x2370(r31)
/* 8013E1B8 0013AD98  3C 80 0C 4C */	lis r4, 0x0C4C0292@ha
/* 8013E1BC 0013AD9C  38 7D 00 00 */	addi r3, r29, 0
/* 8013E1C0 0013ADA0  C0 42 A2 68 */	lfs f2, lbl_804D9C48(r2)
/* 8013E1C4 0013ADA4  38 A4 02 92 */	addi r5, r4, 0x0C4C0292@l
/* 8013E1C8 0013ADA8  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013E1CC 0013ADAC  38 80 01 5D */	li r4, 0x15d
/* 8013E1D0 0013ADB0  FC 60 10 90 */	fmr f3, f2
/* 8013E1D4 0013ADB4  38 C0 00 00 */	li r6, 0
/* 8013E1D8 0013ADB8  4B F2 B1 D5 */	bl Fighter_ActionStateChange_800693AC
lbl_8013E1DC:
/* 8013E1DC 0013ADBC  80 7F 23 6C */	lwz r3, 0x236c(r31)
/* 8013E1E0 0013ADC0  3C 00 43 30 */	lis r0, 0x4330
/* 8013E1E4 0013ADC4  C8 62 A2 90 */	lfd f3, lbl_804D9C70(r2)
/* 8013E1E8 0013ADC8  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8013E1EC 0013ADCC  C0 22 A2 88 */	lfs f1, lbl_804D9C68(r2)
/* 8013E1F0 0013ADD0  90 61 00 1C */	stw r3, 0x1c(r1)
/* 8013E1F4 0013ADD4  C0 1E 00 AC */	lfs f0, 0xac(r30)
/* 8013E1F8 0013ADD8  90 01 00 18 */	stw r0, 0x18(r1)
/* 8013E1FC 0013ADDC  EC 21 00 32 */	fmuls f1, f1, f0
/* 8013E200 0013ADE0  C0 9F 23 74 */	lfs f4, 0x2374(r31)
/* 8013E204 0013ADE4  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 8013E208 0013ADE8  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 8013E20C 0013ADEC  EC 42 18 28 */	fsubs f2, f2, f3
/* 8013E210 0013ADF0  EC 22 00 72 */	fmuls f1, f2, f1
/* 8013E214 0013ADF4  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8013E218 0013ADF8  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 8013E21C 0013ADFC  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8013E220 0013AE00  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E224 0013AE04  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E228 0013AE08  48 00 00 14 */	b lbl_8013E23C
lbl_8013E22C:
/* 8013E22C 0013AE0C  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E230 0013AE10  FC 21 10 2A */	fadd f1, f1, f2
/* 8013E234 0013AE14  FC 20 08 18 */	frsp f1, f1
/* 8013E238 0013AE18  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013E23C:
/* 8013E23C 0013AE1C  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E240 0013AE20  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013E244 0013AE24  41 80 FF E8 */	blt lbl_8013E22C
/* 8013E248 0013AE28  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E24C 0013AE2C  48 00 00 14 */	b lbl_8013E260
lbl_8013E250:
/* 8013E250 0013AE30  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013E254 0013AE34  FC 00 10 28 */	fsub f0, f0, f2
/* 8013E258 0013AE38  FC 00 00 18 */	frsp f0, f0
/* 8013E25C 0013AE3C  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013E260:
/* 8013E260 0013AE40  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E264 0013AE44  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013E268 0013AE48  41 81 FF E8 */	bgt lbl_8013E250
/* 8013E26C 0013AE4C  38 80 00 03 */	li r4, 3
/* 8013E270 0013AE50  4B F3 76 BD */	bl func_8007592C
/* 8013E274 0013AE54  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013E278 0013AE58  38 7F 00 00 */	addi r3, r31, 0
/* 8013E27C 0013AE5C  38 80 00 00 */	li r4, 0
/* 8013E280 0013AE60  4B F3 78 71 */	bl func_80075AF0
/* 8013E284 0013AE64  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8013E288 0013AE68  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8013E28C 0013AE6C  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8013E290 0013AE70  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8013E294 0013AE74  38 21 00 40 */	addi r1, r1, 0x40
/* 8013E298 0013AE78  7C 08 03 A6 */	mtlr r0
/* 8013E29C 0013AE7C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013E2A0()
{ // clang-format off
    nofralloc
/* 8013E2A0 0013AE80  7C 08 02 A6 */	mflr r0
/* 8013E2A4 0013AE84  38 80 00 00 */	li r4, 0
/* 8013E2A8 0013AE88  90 01 00 04 */	stw r0, 4(r1)
/* 8013E2AC 0013AE8C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8013E2B0 0013AE90  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8013E2B4 0013AE94  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8013E2B8 0013AE98  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8013E2BC 0013AE9C  7C 7D 1B 78 */	mr r29, r3
/* 8013E2C0 0013AEA0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013E2C4 0013AEA4  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013E2C8 0013AEA8  4B FF FA 8D */	bl func_8013DD54
/* 8013E2CC 0013AEAC  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E2D0 0013AEB0  3C 60 43 30 */	lis r3, 0x4330
/* 8013E2D4 0013AEB4  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013E2D8 0013AEB8  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013E2DC 0013AEBC  C8 42 A2 90 */	lfd f2, lbl_804D9C70(r2)
/* 8013E2E0 0013AEC0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013E2E4 0013AEC4  C0 1E 00 A8 */	lfs f0, 0xa8(r30)
/* 8013E2E8 0013AEC8  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8013E2EC 0013AECC  90 61 00 28 */	stw r3, 0x28(r1)
/* 8013E2F0 0013AED0  C8 21 00 28 */	lfd f1, 0x28(r1)
/* 8013E2F4 0013AED4  EC 21 10 28 */	fsubs f1, f1, f2
/* 8013E2F8 0013AED8  EC 01 00 2A */	fadds f0, f1, f0
/* 8013E2FC 0013AEDC  FC 00 00 1E */	fctiwz f0, f0
/* 8013E300 0013AEE0  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 8013E304 0013AEE4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013E308 0013AEE8  90 1F 23 6C */	stw r0, 0x236c(r31)
/* 8013E30C 0013AEEC  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013E310 0013AEF0  C0 3E 00 A4 */	lfs f1, 0xa4(r30)
/* 8013E314 0013AEF4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013E318 0013AEF8  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8013E31C 0013AEFC  90 61 00 18 */	stw r3, 0x18(r1)
/* 8013E320 0013AF00  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8013E324 0013AF04  EC 00 10 28 */	fsubs f0, f0, f2
/* 8013E328 0013AF08  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8013E32C 0013AF0C  4C 41 13 82 */	cror 2, 1, 2
/* 8013E330 0013AF10  40 82 00 1C */	bne lbl_8013E34C
/* 8013E334 0013AF14  FC 00 08 1E */	fctiwz f0, f1
/* 8013E338 0013AF18  38 00 00 01 */	li r0, 1
/* 8013E33C 0013AF1C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8013E340 0013AF20  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8013E344 0013AF24  90 7F 23 6C */	stw r3, 0x236c(r31)
/* 8013E348 0013AF28  90 1F 23 70 */	stw r0, 0x2370(r31)
lbl_8013E34C:
/* 8013E34C 0013AF2C  80 7F 23 6C */	lwz r3, 0x236c(r31)
/* 8013E350 0013AF30  3C 00 43 30 */	lis r0, 0x4330
/* 8013E354 0013AF34  C8 62 A2 90 */	lfd f3, lbl_804D9C70(r2)
/* 8013E358 0013AF38  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8013E35C 0013AF3C  C0 22 A2 88 */	lfs f1, lbl_804D9C68(r2)
/* 8013E360 0013AF40  90 61 00 1C */	stw r3, 0x1c(r1)
/* 8013E364 0013AF44  C0 1E 00 AC */	lfs f0, 0xac(r30)
/* 8013E368 0013AF48  90 01 00 18 */	stw r0, 0x18(r1)
/* 8013E36C 0013AF4C  EC 21 00 32 */	fmuls f1, f1, f0
/* 8013E370 0013AF50  C0 9F 23 74 */	lfs f4, 0x2374(r31)
/* 8013E374 0013AF54  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 8013E378 0013AF58  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 8013E37C 0013AF5C  EC 42 18 28 */	fsubs f2, f2, f3
/* 8013E380 0013AF60  EC 22 00 72 */	fmuls f1, f2, f1
/* 8013E384 0013AF64  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8013E388 0013AF68  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 8013E38C 0013AF6C  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8013E390 0013AF70  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E394 0013AF74  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E398 0013AF78  48 00 00 14 */	b lbl_8013E3AC
lbl_8013E39C:
/* 8013E39C 0013AF7C  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E3A0 0013AF80  FC 21 10 2A */	fadd f1, f1, f2
/* 8013E3A4 0013AF84  FC 20 08 18 */	frsp f1, f1
/* 8013E3A8 0013AF88  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013E3AC:
/* 8013E3AC 0013AF8C  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E3B0 0013AF90  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013E3B4 0013AF94  41 80 FF E8 */	blt lbl_8013E39C
/* 8013E3B8 0013AF98  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E3BC 0013AF9C  48 00 00 14 */	b lbl_8013E3D0
lbl_8013E3C0:
/* 8013E3C0 0013AFA0  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013E3C4 0013AFA4  FC 00 10 28 */	fsub f0, f0, f2
/* 8013E3C8 0013AFA8  FC 00 00 18 */	frsp f0, f0
/* 8013E3CC 0013AFAC  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013E3D0:
/* 8013E3D0 0013AFB0  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E3D4 0013AFB4  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013E3D8 0013AFB8  41 81 FF E8 */	bgt lbl_8013E3C0
/* 8013E3DC 0013AFBC  38 80 00 03 */	li r4, 3
/* 8013E3E0 0013AFC0  4B F3 75 4D */	bl func_8007592C
/* 8013E3E4 0013AFC4  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013E3E8 0013AFC8  38 7F 00 00 */	addi r3, r31, 0
/* 8013E3EC 0013AFCC  38 80 00 00 */	li r4, 0
/* 8013E3F0 0013AFD0  4B F3 77 01 */	bl func_80075AF0
/* 8013E3F4 0013AFD4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8013E3F8 0013AFD8  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8013E3FC 0013AFDC  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8013E400 0013AFE0  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8013E404 0013AFE4  38 21 00 40 */	addi r1, r1, 0x40
/* 8013E408 0013AFE8  7C 08 03 A6 */	mtlr r0
/* 8013E40C 0013AFEC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t lbl_803D05C8;
extern unk_t lbl_803D05D8;
extern f64 const lbl_804D9C78;
extern f64 const lbl_804D9C80;
extern f64 const lbl_804D9C88;

#pragma push
asm unk_t lbl_8013E410()
{ // clang-format off
    nofralloc
/* 8013E410 0013AFF0  7C 08 02 A6 */	mflr r0
/* 8013E414 0013AFF4  38 80 00 00 */	li r4, 0
/* 8013E418 0013AFF8  90 01 00 04 */	stw r0, 4(r1)
/* 8013E41C 0013AFFC  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 8013E420 0013B000  DB E1 00 68 */	stfd f31, 0x68(r1)
/* 8013E424 0013B004  DB C1 00 60 */	stfd f30, 0x60(r1)
/* 8013E428 0013B008  BF 61 00 4C */	stmw r27, 0x4c(r1)
/* 8013E42C 0013B00C  7C 7B 1B 78 */	mr r27, r3
/* 8013E430 0013B010  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8013E434 0013B014  83 9D 02 D4 */	lwz r28, 0x2d4(r29)
/* 8013E438 0013B018  4B FF F9 1D */	bl func_8013DD54
/* 8013E43C 0013B01C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E440 0013B020  D0 1D 23 60 */	stfs f0, 0x2360(r29)
/* 8013E444 0013B024  83 DB 00 2C */	lwz r30, 0x2c(r27)
/* 8013E448 0013B028  83 FB 00 28 */	lwz r31, 0x28(r27)
/* 8013E44C 0013B02C  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8013E450 0013B030  2C 00 00 00 */	cmpwi r0, 0
/* 8013E454 0013B034  41 80 00 E4 */	blt lbl_8013E538
/* 8013E458 0013B038  2C 00 00 04 */	cmpwi r0, 4
/* 8013E45C 0013B03C  40 80 00 DC */	bge lbl_8013E538
/* 8013E460 0013B040  C0 1E 22 30 */	lfs f0, 0x2230(r30)
/* 8013E464 0013B044  3C 80 80 3D */	lis r4, lbl_803D05C8@ha
/* 8013E468 0013B048  54 05 10 3A */	slwi r5, r0, 2
/* 8013E46C 0013B04C  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8013E470 0013B050  38 04 05 C8 */	addi r0, r4, lbl_803D05C8@l
/* 8013E474 0013B054  7C 80 2A 14 */	add r4, r0, r5
/* 8013E478 0013B058  C0 3E 22 34 */	lfs f1, 0x2234(r30)
/* 8013E47C 0013B05C  3C 60 80 3D */	lis r3, lbl_803D05D8@ha
/* 8013E480 0013B060  C0 04 00 00 */	lfs f0, 0(r4)
/* 8013E484 0013B064  38 03 05 D8 */	addi r0, r3, lbl_803D05D8@l
/* 8013E488 0013B068  7C 60 2A 14 */	add r3, r0, r5
/* 8013E48C 0013B06C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013E490 0013B070  28 1F 00 00 */	cmplwi r31, 0
/* 8013E494 0013B074  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 8013E498 0013B078  C0 3E 22 38 */	lfs f1, 0x2238(r30)
/* 8013E49C 0013B07C  C0 03 00 00 */	lfs f0, 0(r3)
/* 8013E4A0 0013B080  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013E4A4 0013B084  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8013E4A8 0013B088  40 82 00 14 */	bne lbl_8013E4BC
/* 8013E4AC 0013B08C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E4B0 0013B090  38 80 02 F8 */	li r4, 0x2f8
/* 8013E4B4 0013B094  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E4B8 0013B098  48 24 9D 69 */	bl __assert
lbl_8013E4BC:
/* 8013E4BC 0013B09C  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8013E4C0 0013B0A0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8013E4C4 0013B0A4  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013E4C8 0013B0A8  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013E4CC 0013B0AC  80 01 00 38 */	lwz r0, 0x38(r1)
/* 8013E4D0 0013B0B0  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013E4D4 0013B0B4  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013E4D8 0013B0B8  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013E4DC 0013B0BC  40 82 00 4C */	bne lbl_8013E528
/* 8013E4E0 0013B0C0  28 1F 00 00 */	cmplwi r31, 0
/* 8013E4E4 0013B0C4  41 82 00 44 */	beq lbl_8013E528
/* 8013E4E8 0013B0C8  40 82 00 14 */	bne lbl_8013E4FC
/* 8013E4EC 0013B0CC  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E4F0 0013B0D0  38 80 02 34 */	li r4, 0x234
/* 8013E4F4 0013B0D4  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E4F8 0013B0D8  48 24 9D 29 */	bl __assert
lbl_8013E4FC:
/* 8013E4FC 0013B0DC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013E500 0013B0E0  38 60 00 00 */	li r3, 0
/* 8013E504 0013B0E4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013E508 0013B0E8  40 82 00 10 */	bne lbl_8013E518
/* 8013E50C 0013B0EC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013E510 0013B0F0  41 82 00 08 */	beq lbl_8013E518
/* 8013E514 0013B0F4  38 60 00 01 */	li r3, 1
lbl_8013E518:
/* 8013E518 0013B0F8  2C 03 00 00 */	cmpwi r3, 0
/* 8013E51C 0013B0FC  40 82 00 0C */	bne lbl_8013E528
/* 8013E520 0013B100  7F E3 FB 78 */	mr r3, r31
/* 8013E524 0013B104  48 23 4D C5 */	bl HSD_JObjSetMtxDirtySub
lbl_8013E528:
/* 8013E528 0013B108  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8013E52C 0013B10C  38 03 00 01 */	addi r0, r3, 1
/* 8013E530 0013B110  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8013E534 0013B114  48 00 00 A4 */	b lbl_8013E5D8
lbl_8013E538:
/* 8013E538 0013B118  28 1F 00 00 */	cmplwi r31, 0
/* 8013E53C 0013B11C  3B DE 22 30 */	addi r30, r30, 0x2230
/* 8013E540 0013B120  40 82 00 14 */	bne lbl_8013E554
/* 8013E544 0013B124  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E548 0013B128  38 80 02 F8 */	li r4, 0x2f8
/* 8013E54C 0013B12C  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E550 0013B130  48 24 9C D1 */	bl __assert
lbl_8013E554:
/* 8013E554 0013B134  28 1E 00 00 */	cmplwi r30, 0
/* 8013E558 0013B138  40 82 00 14 */	bne lbl_8013E56C
/* 8013E55C 0013B13C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E560 0013B140  38 80 02 F9 */	li r4, 0x2f9
/* 8013E564 0013B144  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013E568 0013B148  48 24 9C B9 */	bl __assert
lbl_8013E56C:
/* 8013E56C 0013B14C  80 7E 00 00 */	lwz r3, 0(r30)
/* 8013E570 0013B150  80 1E 00 04 */	lwz r0, 4(r30)
/* 8013E574 0013B154  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013E578 0013B158  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013E57C 0013B15C  80 1E 00 08 */	lwz r0, 8(r30)
/* 8013E580 0013B160  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013E584 0013B164  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013E588 0013B168  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013E58C 0013B16C  40 82 00 4C */	bne lbl_8013E5D8
/* 8013E590 0013B170  28 1F 00 00 */	cmplwi r31, 0
/* 8013E594 0013B174  41 82 00 44 */	beq lbl_8013E5D8
/* 8013E598 0013B178  40 82 00 14 */	bne lbl_8013E5AC
/* 8013E59C 0013B17C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E5A0 0013B180  38 80 02 34 */	li r4, 0x234
/* 8013E5A4 0013B184  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E5A8 0013B188  48 24 9C 79 */	bl __assert
lbl_8013E5AC:
/* 8013E5AC 0013B18C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013E5B0 0013B190  38 60 00 00 */	li r3, 0
/* 8013E5B4 0013B194  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013E5B8 0013B198  40 82 00 10 */	bne lbl_8013E5C8
/* 8013E5BC 0013B19C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013E5C0 0013B1A0  41 82 00 08 */	beq lbl_8013E5C8
/* 8013E5C4 0013B1A4  38 60 00 01 */	li r3, 1
lbl_8013E5C8:
/* 8013E5C8 0013B1A8  2C 03 00 00 */	cmpwi r3, 0
/* 8013E5CC 0013B1AC  40 82 00 0C */	bne lbl_8013E5D8
/* 8013E5D0 0013B1B0  7F E3 FB 78 */	mr r3, r31
/* 8013E5D4 0013B1B4  48 23 4D 15 */	bl HSD_JObjSetMtxDirtySub
lbl_8013E5D8:
/* 8013E5D8 0013B1B8  80 9B 00 2C */	lwz r4, 0x2c(r27)
/* 8013E5DC 0013B1BC  80 64 23 4C */	lwz r3, 0x234c(r4)
/* 8013E5E0 0013B1C0  80 A4 02 D4 */	lwz r5, 0x2d4(r4)
/* 8013E5E4 0013B1C4  38 03 00 01 */	addi r0, r3, 1
/* 8013E5E8 0013B1C8  90 04 23 4C */	stw r0, 0x234c(r4)
/* 8013E5EC 0013B1CC  80 64 23 4C */	lwz r3, 0x234c(r4)
/* 8013E5F0 0013B1D0  80 05 00 9C */	lwz r0, 0x9c(r5)
/* 8013E5F4 0013B1D4  7C 03 00 00 */	cmpw r3, r0
/* 8013E5F8 0013B1D8  41 80 00 28 */	blt lbl_8013E620
/* 8013E5FC 0013B1DC  80 04 09 14 */	lwz r0, 0x914(r4)
/* 8013E600 0013B1E0  2C 00 00 00 */	cmpwi r0, 0
/* 8013E604 0013B1E4  41 82 00 1C */	beq lbl_8013E620
/* 8013E608 0013B1E8  80 64 09 18 */	lwz r3, 0x918(r4)
/* 8013E60C 0013B1EC  38 00 00 00 */	li r0, 0
/* 8013E610 0013B1F0  38 63 00 01 */	addi r3, r3, 1
/* 8013E614 0013B1F4  54 63 07 FE */	clrlwi r3, r3, 0x1f
/* 8013E618 0013B1F8  90 64 09 18 */	stw r3, 0x918(r4)
/* 8013E61C 0013B1FC  90 04 23 4C */	stw r0, 0x234c(r4)
lbl_8013E620:
/* 8013E620 0013B200  7F 63 DB 78 */	mr r3, r27
/* 8013E624 0013B204  4B FF F2 C1 */	bl func_8013D8E4
/* 8013E628 0013B208  80 7D 23 6C */	lwz r3, 0x236c(r29)
/* 8013E62C 0013B20C  3C 00 43 30 */	lis r0, 0x4330
/* 8013E630 0013B210  C8 22 A2 98 */	lfd f1, lbl_804D9C78(r2)
/* 8013E634 0013B214  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8013E638 0013B218  C0 1C 00 98 */	lfs f0, 0x98(r28)
/* 8013E63C 0013B21C  90 61 00 44 */	stw r3, 0x44(r1)
/* 8013E640 0013B220  FC 21 00 32 */	fmul f1, f1, f0
/* 8013E644 0013B224  C0 1D 23 74 */	lfs f0, 0x2374(r29)
/* 8013E648 0013B228  90 01 00 40 */	stw r0, 0x40(r1)
/* 8013E64C 0013B22C  C8 62 A2 90 */	lfd f3, lbl_804D9C70(r2)
/* 8013E650 0013B230  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 8013E654 0013B234  FC 01 00 32 */	fmul f0, f1, f0
/* 8013E658 0013B238  C0 82 A2 88 */	lfs f4, lbl_804D9C68(r2)
/* 8013E65C 0013B23C  C3 FD 23 54 */	lfs f31, 0x2354(r29)
/* 8013E660 0013B240  EC 22 18 28 */	fsubs f1, f2, f3
/* 8013E664 0013B244  FC 00 00 18 */	frsp f0, f0
/* 8013E668 0013B248  EC 24 00 72 */	fmuls f1, f4, f1
/* 8013E66C 0013B24C  EF C1 00 32 */	fmuls f30, f1, f0
/* 8013E670 0013B250  EC 1F F0 2A */	fadds f0, f31, f30
/* 8013E674 0013B254  D0 1D 23 54 */	stfs f0, 0x2354(r29)
/* 8013E678 0013B258  80 7B 00 2C */	lwz r3, 0x2c(r27)
/* 8013E67C 0013B25C  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E680 0013B260  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E684 0013B264  48 00 00 14 */	b lbl_8013E698
lbl_8013E688:
/* 8013E688 0013B268  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E68C 0013B26C  FC 21 10 2A */	fadd f1, f1, f2
/* 8013E690 0013B270  FC 20 08 18 */	frsp f1, f1
/* 8013E694 0013B274  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013E698:
/* 8013E698 0013B278  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E69C 0013B27C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013E6A0 0013B280  41 80 FF E8 */	blt lbl_8013E688
/* 8013E6A4 0013B284  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E6A8 0013B288  48 00 00 14 */	b lbl_8013E6BC
lbl_8013E6AC:
/* 8013E6AC 0013B28C  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013E6B0 0013B290  FC 00 10 28 */	fsub f0, f0, f2
/* 8013E6B4 0013B294  FC 00 00 18 */	frsp f0, f0
/* 8013E6B8 0013B298  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013E6BC:
/* 8013E6BC 0013B29C  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E6C0 0013B2A0  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013E6C4 0013B2A4  41 81 FF E8 */	bgt lbl_8013E6AC
/* 8013E6C8 0013B2A8  38 80 00 03 */	li r4, 3
/* 8013E6CC 0013B2AC  4B F3 72 61 */	bl func_8007592C
/* 8013E6D0 0013B2B0  80 7D 23 40 */	lwz r3, 0x2340(r29)
/* 8013E6D4 0013B2B4  38 03 FF FF */	addi r0, r3, -1
/* 8013E6D8 0013B2B8  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 8013E6DC 0013B2BC  80 1D 23 40 */	lwz r0, 0x2340(r29)
/* 8013E6E0 0013B2C0  2C 00 00 00 */	cmpwi r0, 0
/* 8013E6E4 0013B2C4  41 81 00 D0 */	bgt lbl_8013E7B4
/* 8013E6E8 0013B2C8  C8 02 A2 60 */	lfd f0, lbl_804D9C40(r2)
/* 8013E6EC 0013B2CC  C0 5D 23 54 */	lfs f2, 0x2354(r29)
/* 8013E6F0 0013B2D0  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8013E6F4 0013B2D4  40 80 00 AC */	bge lbl_8013E7A0
/* 8013E6F8 0013B2D8  C8 02 A2 A0 */	lfd f0, lbl_804D9C80(r2)
/* 8013E6FC 0013B2DC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013E700 0013B2E0  40 80 00 A0 */	bge lbl_8013E7A0
/* 8013E704 0013B2E4  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013E708 0013B2E8  FC 1E 08 40 */	fcmpo cr0, f30, f1
/* 8013E70C 0013B2EC  40 81 00 4C */	ble lbl_8013E758
/* 8013E710 0013B2F0  C8 02 A2 A8 */	lfd f0, lbl_804D9C88(r2)
/* 8013E714 0013B2F4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013E718 0013B2F8  40 81 00 2C */	ble lbl_8013E744
/* 8013E71C 0013B2FC  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8013E720 0013B300  40 80 00 24 */	bge lbl_8013E744
/* 8013E724 0013B304  38 00 00 00 */	li r0, 0
/* 8013E728 0013B308  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013E72C 0013B30C  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 8013E730 0013B310  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013E734 0013B314  38 7B 00 00 */	addi r3, r27, 0
/* 8013E738 0013B318  38 80 00 00 */	li r4, 0
/* 8013E73C 0013B31C  4B FF F2 E9 */	bl func_8013DA24
/* 8013E740 0013B320  48 00 00 84 */	b lbl_8013E7C4
lbl_8013E744:
/* 8013E744 0013B324  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013E748 0013B328  38 7D 00 00 */	addi r3, r29, 0
/* 8013E74C 0013B32C  38 80 00 00 */	li r4, 0
/* 8013E750 0013B330  4B F3 73 A1 */	bl func_80075AF0
/* 8013E754 0013B334  48 00 00 70 */	b lbl_8013E7C4
lbl_8013E758:
/* 8013E758 0013B338  C8 02 A2 A8 */	lfd f0, lbl_804D9C88(r2)
/* 8013E75C 0013B33C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013E760 0013B340  40 80 00 2C */	bge lbl_8013E78C
/* 8013E764 0013B344  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8013E768 0013B348  40 81 00 24 */	ble lbl_8013E78C
/* 8013E76C 0013B34C  38 00 00 00 */	li r0, 0
/* 8013E770 0013B350  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013E774 0013B354  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 8013E778 0013B358  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013E77C 0013B35C  38 7B 00 00 */	addi r3, r27, 0
/* 8013E780 0013B360  38 80 00 00 */	li r4, 0
/* 8013E784 0013B364  4B FF F2 A1 */	bl func_8013DA24
/* 8013E788 0013B368  48 00 00 3C */	b lbl_8013E7C4
lbl_8013E78C:
/* 8013E78C 0013B36C  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013E790 0013B370  38 7D 00 00 */	addi r3, r29, 0
/* 8013E794 0013B374  38 80 00 00 */	li r4, 0
/* 8013E798 0013B378  4B F3 73 59 */	bl func_80075AF0
/* 8013E79C 0013B37C  48 00 00 28 */	b lbl_8013E7C4
lbl_8013E7A0:
/* 8013E7A0 0013B380  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013E7A4 0013B384  38 7D 00 00 */	addi r3, r29, 0
/* 8013E7A8 0013B388  38 80 00 00 */	li r4, 0
/* 8013E7AC 0013B38C  4B F3 73 45 */	bl func_80075AF0
/* 8013E7B0 0013B390  48 00 00 14 */	b lbl_8013E7C4
lbl_8013E7B4:
/* 8013E7B4 0013B394  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013E7B8 0013B398  38 7D 00 00 */	addi r3, r29, 0
/* 8013E7BC 0013B39C  38 80 00 00 */	li r4, 0
/* 8013E7C0 0013B3A0  4B F3 73 31 */	bl func_80075AF0
lbl_8013E7C4:
/* 8013E7C4 0013B3A4  BB 61 00 4C */	lmw r27, 0x4c(r1)
/* 8013E7C8 0013B3A8  80 01 00 74 */	lwz r0, 0x74(r1)
/* 8013E7CC 0013B3AC  CB E1 00 68 */	lfd f31, 0x68(r1)
/* 8013E7D0 0013B3B0  CB C1 00 60 */	lfd f30, 0x60(r1)
/* 8013E7D4 0013B3B4  38 21 00 70 */	addi r1, r1, 0x70
/* 8013E7D8 0013B3B8  7C 08 03 A6 */	mtlr r0
/* 8013E7DC 0013B3BC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013E7E0()
{ // clang-format off
    nofralloc
/* 8013E7E0 0013B3C0  7C 08 02 A6 */	mflr r0
/* 8013E7E4 0013B3C4  38 80 00 01 */	li r4, 1
/* 8013E7E8 0013B3C8  90 01 00 04 */	stw r0, 4(r1)
/* 8013E7EC 0013B3CC  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8013E7F0 0013B3D0  BF 61 00 3C */	stmw r27, 0x3c(r1)
/* 8013E7F4 0013B3D4  7C 7B 1B 78 */	mr r27, r3
/* 8013E7F8 0013B3D8  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8013E7FC 0013B3DC  83 85 02 D4 */	lwz r28, 0x2d4(r5)
/* 8013E800 0013B3E0  7C BD 2B 78 */	mr r29, r5
/* 8013E804 0013B3E4  4B FF F5 51 */	bl func_8013DD54
/* 8013E808 0013B3E8  83 DB 00 2C */	lwz r30, 0x2c(r27)
/* 8013E80C 0013B3EC  83 FB 00 28 */	lwz r31, 0x28(r27)
/* 8013E810 0013B3F0  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8013E814 0013B3F4  2C 00 00 00 */	cmpwi r0, 0
/* 8013E818 0013B3F8  41 80 00 E4 */	blt lbl_8013E8FC
/* 8013E81C 0013B3FC  2C 00 00 04 */	cmpwi r0, 4
/* 8013E820 0013B400  40 80 00 DC */	bge lbl_8013E8FC
/* 8013E824 0013B404  C0 1E 22 30 */	lfs f0, 0x2230(r30)
/* 8013E828 0013B408  3C 80 80 3D */	lis r4, lbl_803D05C8@ha
/* 8013E82C 0013B40C  54 05 10 3A */	slwi r5, r0, 2
/* 8013E830 0013B410  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8013E834 0013B414  38 04 05 C8 */	addi r0, r4, lbl_803D05C8@l
/* 8013E838 0013B418  7C 80 2A 14 */	add r4, r0, r5
/* 8013E83C 0013B41C  C0 3E 22 34 */	lfs f1, 0x2234(r30)
/* 8013E840 0013B420  3C 60 80 3D */	lis r3, lbl_803D05D8@ha
/* 8013E844 0013B424  C0 04 00 00 */	lfs f0, 0(r4)
/* 8013E848 0013B428  38 03 05 D8 */	addi r0, r3, lbl_803D05D8@l
/* 8013E84C 0013B42C  7C 60 2A 14 */	add r3, r0, r5
/* 8013E850 0013B430  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013E854 0013B434  28 1F 00 00 */	cmplwi r31, 0
/* 8013E858 0013B438  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8013E85C 0013B43C  C0 3E 22 38 */	lfs f1, 0x2238(r30)
/* 8013E860 0013B440  C0 03 00 00 */	lfs f0, 0(r3)
/* 8013E864 0013B444  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013E868 0013B448  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 8013E86C 0013B44C  40 82 00 14 */	bne lbl_8013E880
/* 8013E870 0013B450  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E874 0013B454  38 80 02 F8 */	li r4, 0x2f8
/* 8013E878 0013B458  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E87C 0013B45C  48 24 99 A5 */	bl __assert
lbl_8013E880:
/* 8013E880 0013B460  80 61 00 24 */	lwz r3, 0x24(r1)
/* 8013E884 0013B464  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8013E888 0013B468  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013E88C 0013B46C  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013E890 0013B470  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013E894 0013B474  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013E898 0013B478  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013E89C 0013B47C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013E8A0 0013B480  40 82 00 4C */	bne lbl_8013E8EC
/* 8013E8A4 0013B484  28 1F 00 00 */	cmplwi r31, 0
/* 8013E8A8 0013B488  41 82 00 44 */	beq lbl_8013E8EC
/* 8013E8AC 0013B48C  40 82 00 14 */	bne lbl_8013E8C0
/* 8013E8B0 0013B490  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E8B4 0013B494  38 80 02 34 */	li r4, 0x234
/* 8013E8B8 0013B498  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E8BC 0013B49C  48 24 99 65 */	bl __assert
lbl_8013E8C0:
/* 8013E8C0 0013B4A0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013E8C4 0013B4A4  38 60 00 00 */	li r3, 0
/* 8013E8C8 0013B4A8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013E8CC 0013B4AC  40 82 00 10 */	bne lbl_8013E8DC
/* 8013E8D0 0013B4B0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013E8D4 0013B4B4  41 82 00 08 */	beq lbl_8013E8DC
/* 8013E8D8 0013B4B8  38 60 00 01 */	li r3, 1
lbl_8013E8DC:
/* 8013E8DC 0013B4BC  2C 03 00 00 */	cmpwi r3, 0
/* 8013E8E0 0013B4C0  40 82 00 0C */	bne lbl_8013E8EC
/* 8013E8E4 0013B4C4  7F E3 FB 78 */	mr r3, r31
/* 8013E8E8 0013B4C8  48 23 4A 01 */	bl HSD_JObjSetMtxDirtySub
lbl_8013E8EC:
/* 8013E8EC 0013B4CC  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8013E8F0 0013B4D0  38 03 00 01 */	addi r0, r3, 1
/* 8013E8F4 0013B4D4  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8013E8F8 0013B4D8  48 00 00 A4 */	b lbl_8013E99C
lbl_8013E8FC:
/* 8013E8FC 0013B4DC  28 1F 00 00 */	cmplwi r31, 0
/* 8013E900 0013B4E0  3B DE 22 30 */	addi r30, r30, 0x2230
/* 8013E904 0013B4E4  40 82 00 14 */	bne lbl_8013E918
/* 8013E908 0013B4E8  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E90C 0013B4EC  38 80 02 F8 */	li r4, 0x2f8
/* 8013E910 0013B4F0  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E914 0013B4F4  48 24 99 0D */	bl __assert
lbl_8013E918:
/* 8013E918 0013B4F8  28 1E 00 00 */	cmplwi r30, 0
/* 8013E91C 0013B4FC  40 82 00 14 */	bne lbl_8013E930
/* 8013E920 0013B500  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E924 0013B504  38 80 02 F9 */	li r4, 0x2f9
/* 8013E928 0013B508  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013E92C 0013B50C  48 24 98 F5 */	bl __assert
lbl_8013E930:
/* 8013E930 0013B510  80 7E 00 00 */	lwz r3, 0(r30)
/* 8013E934 0013B514  80 1E 00 04 */	lwz r0, 4(r30)
/* 8013E938 0013B518  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013E93C 0013B51C  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013E940 0013B520  80 1E 00 08 */	lwz r0, 8(r30)
/* 8013E944 0013B524  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013E948 0013B528  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013E94C 0013B52C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013E950 0013B530  40 82 00 4C */	bne lbl_8013E99C
/* 8013E954 0013B534  28 1F 00 00 */	cmplwi r31, 0
/* 8013E958 0013B538  41 82 00 44 */	beq lbl_8013E99C
/* 8013E95C 0013B53C  40 82 00 14 */	bne lbl_8013E970
/* 8013E960 0013B540  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013E964 0013B544  38 80 02 34 */	li r4, 0x234
/* 8013E968 0013B548  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013E96C 0013B54C  48 24 98 B5 */	bl __assert
lbl_8013E970:
/* 8013E970 0013B550  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013E974 0013B554  38 60 00 00 */	li r3, 0
/* 8013E978 0013B558  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013E97C 0013B55C  40 82 00 10 */	bne lbl_8013E98C
/* 8013E980 0013B560  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013E984 0013B564  41 82 00 08 */	beq lbl_8013E98C
/* 8013E988 0013B568  38 60 00 01 */	li r3, 1
lbl_8013E98C:
/* 8013E98C 0013B56C  2C 03 00 00 */	cmpwi r3, 0
/* 8013E990 0013B570  40 82 00 0C */	bne lbl_8013E99C
/* 8013E994 0013B574  7F E3 FB 78 */	mr r3, r31
/* 8013E998 0013B578  48 23 49 51 */	bl HSD_JObjSetMtxDirtySub
lbl_8013E99C:
/* 8013E99C 0013B57C  C8 42 A2 98 */	lfd f2, lbl_804D9C78(r2)
/* 8013E9A0 0013B580  C0 1C 00 6C */	lfs f0, 0x6c(r28)
/* 8013E9A4 0013B584  C0 3D 23 74 */	lfs f1, 0x2374(r29)
/* 8013E9A8 0013B588  FC 42 00 32 */	fmul f2, f2, f0
/* 8013E9AC 0013B58C  C0 1D 23 54 */	lfs f0, 0x2354(r29)
/* 8013E9B0 0013B590  FC 20 08 50 */	fneg f1, f1
/* 8013E9B4 0013B594  FC 02 00 7A */	fmadd f0, f2, f1, f0
/* 8013E9B8 0013B598  FC 00 00 18 */	frsp f0, f0
/* 8013E9BC 0013B59C  D0 1D 23 54 */	stfs f0, 0x2354(r29)
/* 8013E9C0 0013B5A0  80 7B 00 2C */	lwz r3, 0x2c(r27)
/* 8013E9C4 0013B5A4  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E9C8 0013B5A8  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013E9CC 0013B5AC  48 00 00 14 */	b lbl_8013E9E0
lbl_8013E9D0:
/* 8013E9D0 0013B5B0  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E9D4 0013B5B4  FC 21 10 2A */	fadd f1, f1, f2
/* 8013E9D8 0013B5B8  FC 20 08 18 */	frsp f1, f1
/* 8013E9DC 0013B5BC  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013E9E0:
/* 8013E9E0 0013B5C0  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013E9E4 0013B5C4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013E9E8 0013B5C8  41 80 FF E8 */	blt lbl_8013E9D0
/* 8013E9EC 0013B5CC  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013E9F0 0013B5D0  48 00 00 14 */	b lbl_8013EA04
lbl_8013E9F4:
/* 8013E9F4 0013B5D4  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013E9F8 0013B5D8  FC 00 10 28 */	fsub f0, f0, f2
/* 8013E9FC 0013B5DC  FC 00 00 18 */	frsp f0, f0
/* 8013EA00 0013B5E0  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013EA04:
/* 8013EA04 0013B5E4  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013EA08 0013B5E8  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013EA0C 0013B5EC  41 81 FF E8 */	bgt lbl_8013E9F4
/* 8013EA10 0013B5F0  38 80 00 03 */	li r4, 3
/* 8013EA14 0013B5F4  4B F3 6F 19 */	bl func_8007592C
/* 8013EA18 0013B5F8  80 7D 23 40 */	lwz r3, 0x2340(r29)
/* 8013EA1C 0013B5FC  38 03 FF FF */	addi r0, r3, -1
/* 8013EA20 0013B600  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 8013EA24 0013B604  80 1D 23 40 */	lwz r0, 0x2340(r29)
/* 8013EA28 0013B608  2C 00 00 00 */	cmpwi r0, 0
/* 8013EA2C 0013B60C  41 81 00 34 */	bgt lbl_8013EA60
/* 8013EA30 0013B610  38 00 00 00 */	li r0, 0
/* 8013EA34 0013B614  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 8013EA38 0013B618  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013EA3C 0013B61C  38 7B 00 00 */	addi r3, r27, 0
/* 8013EA40 0013B620  C0 1D 23 74 */	lfs f0, 0x2374(r29)
/* 8013EA44 0013B624  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013EA48 0013B628  38 80 00 00 */	li r4, 0
/* 8013EA4C 0013B62C  FC 00 00 50 */	fneg f0, f0
/* 8013EA50 0013B630  D0 1D 23 74 */	stfs f0, 0x2374(r29)
/* 8013EA54 0013B634  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013EA58 0013B638  4B FF EF CD */	bl func_8013DA24
/* 8013EA5C 0013B63C  48 00 00 68 */	b lbl_8013EAC4
lbl_8013EA60:
/* 8013EA60 0013B640  80 9D 23 64 */	lwz r4, 0x2364(r29)
/* 8013EA64 0013B644  80 7C 00 70 */	lwz r3, 0x70(r28)
/* 8013EA68 0013B648  7C 04 1B D6 */	divw r0, r4, r3
/* 8013EA6C 0013B64C  7C 00 19 D6 */	mullw r0, r0, r3
/* 8013EA70 0013B650  7C 00 20 51 */	subf. r0, r0, r4
/* 8013EA74 0013B654  40 82 00 34 */	bne lbl_8013EAA8
/* 8013EA78 0013B658  C0 1D 08 44 */	lfs f0, 0x844(r29)
/* 8013EA7C 0013B65C  C0 5D 08 48 */	lfs f2, 0x848(r29)
/* 8013EA80 0013B660  FC 20 00 50 */	fneg f1, f0
/* 8013EA84 0013B664  4B EE 41 AD */	bl atan2f
/* 8013EA88 0013B668  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 8013EA8C 0013B66C  38 9B 00 00 */	addi r4, r27, 0
/* 8013EA90 0013B670  38 BD 00 B0 */	addi r5, r29, 0xb0
/* 8013EA94 0013B674  4C C6 31 82 */	crclr 6
/* 8013EA98 0013B678  38 DD 00 2C */	addi r6, r29, 0x2c
/* 8013EA9C 0013B67C  38 E1 00 30 */	addi r7, r1, 0x30
/* 8013EAA0 0013B680  38 60 03 FF */	li r3, 0x3ff
/* 8013EAA4 0013B684  4B F2 13 39 */	bl ef_Spawn
lbl_8013EAA8:
/* 8013EAA8 0013B688  80 BD 23 64 */	lwz r5, 0x2364(r29)
/* 8013EAAC 0013B68C  38 7D 00 00 */	addi r3, r29, 0
/* 8013EAB0 0013B690  38 80 00 00 */	li r4, 0
/* 8013EAB4 0013B694  38 05 00 01 */	addi r0, r5, 1
/* 8013EAB8 0013B698  90 1D 23 64 */	stw r0, 0x2364(r29)
/* 8013EABC 0013B69C  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013EAC0 0013B6A0  4B F3 70 31 */	bl func_80075AF0
lbl_8013EAC4:
/* 8013EAC4 0013B6A4  BB 61 00 3C */	lmw r27, 0x3c(r1)
/* 8013EAC8 0013B6A8  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8013EACC 0013B6AC  38 21 00 50 */	addi r1, r1, 0x50
/* 8013EAD0 0013B6B0  7C 08 03 A6 */	mtlr r0
/* 8013EAD4 0013B6B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013EAD8()
{ // clang-format off
    nofralloc
/* 8013EAD8 0013B6B8  7C 08 02 A6 */	mflr r0
/* 8013EADC 0013B6BC  90 01 00 04 */	stw r0, 4(r1)
/* 8013EAE0 0013B6C0  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8013EAE4 0013B6C4  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8013EAE8 0013B6C8  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8013EAEC 0013B6CC  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8013EAF0 0013B6D0  7C 7D 1B 78 */	mr r29, r3
/* 8013EAF4 0013B6D4  93 81 00 30 */	stw r28, 0x30(r1)
/* 8013EAF8 0013B6D8  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013EAFC 0013B6DC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013EB00 0013B6E0  D0 03 23 60 */	stfs f0, 0x2360(r3)
/* 8013EB04 0013B6E4  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 8013EB08 0013B6E8  83 FD 00 28 */	lwz r31, 0x28(r29)
/* 8013EB0C 0013B6EC  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8013EB10 0013B6F0  2C 00 00 00 */	cmpwi r0, 0
/* 8013EB14 0013B6F4  41 80 00 E4 */	blt lbl_8013EBF8
/* 8013EB18 0013B6F8  2C 00 00 04 */	cmpwi r0, 4
/* 8013EB1C 0013B6FC  40 80 00 DC */	bge lbl_8013EBF8
/* 8013EB20 0013B700  C0 1E 22 30 */	lfs f0, 0x2230(r30)
/* 8013EB24 0013B704  3C 80 80 3D */	lis r4, lbl_803D05C8@ha
/* 8013EB28 0013B708  54 05 10 3A */	slwi r5, r0, 2
/* 8013EB2C 0013B70C  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8013EB30 0013B710  38 04 05 C8 */	addi r0, r4, lbl_803D05C8@l
/* 8013EB34 0013B714  7C 80 2A 14 */	add r4, r0, r5
/* 8013EB38 0013B718  C0 3E 22 34 */	lfs f1, 0x2234(r30)
/* 8013EB3C 0013B71C  3C 60 80 3D */	lis r3, lbl_803D05D8@ha
/* 8013EB40 0013B720  C0 04 00 00 */	lfs f0, 0(r4)
/* 8013EB44 0013B724  38 03 05 D8 */	addi r0, r3, lbl_803D05D8@l
/* 8013EB48 0013B728  7C 60 2A 14 */	add r3, r0, r5
/* 8013EB4C 0013B72C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013EB50 0013B730  28 1F 00 00 */	cmplwi r31, 0
/* 8013EB54 0013B734  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8013EB58 0013B738  C0 3E 22 38 */	lfs f1, 0x2238(r30)
/* 8013EB5C 0013B73C  C0 03 00 00 */	lfs f0, 0(r3)
/* 8013EB60 0013B740  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013EB64 0013B744  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8013EB68 0013B748  40 82 00 14 */	bne lbl_8013EB7C
/* 8013EB6C 0013B74C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013EB70 0013B750  38 80 02 F8 */	li r4, 0x2f8
/* 8013EB74 0013B754  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013EB78 0013B758  48 24 96 A9 */	bl __assert
lbl_8013EB7C:
/* 8013EB7C 0013B75C  80 61 00 20 */	lwz r3, 0x20(r1)
/* 8013EB80 0013B760  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013EB84 0013B764  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013EB88 0013B768  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013EB8C 0013B76C  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8013EB90 0013B770  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013EB94 0013B774  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013EB98 0013B778  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013EB9C 0013B77C  40 82 00 4C */	bne lbl_8013EBE8
/* 8013EBA0 0013B780  28 1F 00 00 */	cmplwi r31, 0
/* 8013EBA4 0013B784  41 82 00 44 */	beq lbl_8013EBE8
/* 8013EBA8 0013B788  40 82 00 14 */	bne lbl_8013EBBC
/* 8013EBAC 0013B78C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013EBB0 0013B790  38 80 02 34 */	li r4, 0x234
/* 8013EBB4 0013B794  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013EBB8 0013B798  48 24 96 69 */	bl __assert
lbl_8013EBBC:
/* 8013EBBC 0013B79C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013EBC0 0013B7A0  38 60 00 00 */	li r3, 0
/* 8013EBC4 0013B7A4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013EBC8 0013B7A8  40 82 00 10 */	bne lbl_8013EBD8
/* 8013EBCC 0013B7AC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013EBD0 0013B7B0  41 82 00 08 */	beq lbl_8013EBD8
/* 8013EBD4 0013B7B4  38 60 00 01 */	li r3, 1
lbl_8013EBD8:
/* 8013EBD8 0013B7B8  2C 03 00 00 */	cmpwi r3, 0
/* 8013EBDC 0013B7BC  40 82 00 0C */	bne lbl_8013EBE8
/* 8013EBE0 0013B7C0  7F E3 FB 78 */	mr r3, r31
/* 8013EBE4 0013B7C4  48 23 47 05 */	bl HSD_JObjSetMtxDirtySub
lbl_8013EBE8:
/* 8013EBE8 0013B7C8  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8013EBEC 0013B7CC  38 03 00 01 */	addi r0, r3, 1
/* 8013EBF0 0013B7D0  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8013EBF4 0013B7D4  48 00 00 A4 */	b lbl_8013EC98
lbl_8013EBF8:
/* 8013EBF8 0013B7D8  28 1F 00 00 */	cmplwi r31, 0
/* 8013EBFC 0013B7DC  3B DE 22 30 */	addi r30, r30, 0x2230
/* 8013EC00 0013B7E0  40 82 00 14 */	bne lbl_8013EC14
/* 8013EC04 0013B7E4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013EC08 0013B7E8  38 80 02 F8 */	li r4, 0x2f8
/* 8013EC0C 0013B7EC  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013EC10 0013B7F0  48 24 96 11 */	bl __assert
lbl_8013EC14:
/* 8013EC14 0013B7F4  28 1E 00 00 */	cmplwi r30, 0
/* 8013EC18 0013B7F8  40 82 00 14 */	bne lbl_8013EC2C
/* 8013EC1C 0013B7FC  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013EC20 0013B800  38 80 02 F9 */	li r4, 0x2f9
/* 8013EC24 0013B804  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013EC28 0013B808  48 24 95 F9 */	bl __assert
lbl_8013EC2C:
/* 8013EC2C 0013B80C  80 7E 00 00 */	lwz r3, 0(r30)
/* 8013EC30 0013B810  80 1E 00 04 */	lwz r0, 4(r30)
/* 8013EC34 0013B814  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013EC38 0013B818  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013EC3C 0013B81C  80 1E 00 08 */	lwz r0, 8(r30)
/* 8013EC40 0013B820  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013EC44 0013B824  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013EC48 0013B828  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013EC4C 0013B82C  40 82 00 4C */	bne lbl_8013EC98
/* 8013EC50 0013B830  28 1F 00 00 */	cmplwi r31, 0
/* 8013EC54 0013B834  41 82 00 44 */	beq lbl_8013EC98
/* 8013EC58 0013B838  40 82 00 14 */	bne lbl_8013EC6C
/* 8013EC5C 0013B83C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013EC60 0013B840  38 80 02 34 */	li r4, 0x234
/* 8013EC64 0013B844  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013EC68 0013B848  48 24 95 B9 */	bl __assert
lbl_8013EC6C:
/* 8013EC6C 0013B84C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013EC70 0013B850  38 60 00 00 */	li r3, 0
/* 8013EC74 0013B854  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013EC78 0013B858  40 82 00 10 */	bne lbl_8013EC88
/* 8013EC7C 0013B85C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013EC80 0013B860  41 82 00 08 */	beq lbl_8013EC88
/* 8013EC84 0013B864  38 60 00 01 */	li r3, 1
lbl_8013EC88:
/* 8013EC88 0013B868  2C 03 00 00 */	cmpwi r3, 0
/* 8013EC8C 0013B86C  40 82 00 0C */	bne lbl_8013EC98
/* 8013EC90 0013B870  7F E3 FB 78 */	mr r3, r31
/* 8013EC94 0013B874  48 23 46 55 */	bl HSD_JObjSetMtxDirtySub
lbl_8013EC98:
/* 8013EC98 0013B878  7F A3 EB 78 */	mr r3, r29
/* 8013EC9C 0013B87C  4B F3 05 9D */	bl ftAnim_IsFramesRemaining
/* 8013ECA0 0013B880  2C 03 00 00 */	cmpwi r3, 0
/* 8013ECA4 0013B884  40 82 00 EC */	bne lbl_8013ED90
/* 8013ECA8 0013B888  83 DD 00 28 */	lwz r30, 0x28(r29)
/* 8013ECAC 0013B88C  83 9D 00 2C */	lwz r28, 0x2c(r29)
/* 8013ECB0 0013B890  28 1E 00 00 */	cmplwi r30, 0
/* 8013ECB4 0013B894  3B FC 22 30 */	addi r31, r28, 0x2230
/* 8013ECB8 0013B898  40 82 00 14 */	bne lbl_8013ECCC
/* 8013ECBC 0013B89C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013ECC0 0013B8A0  38 80 02 F8 */	li r4, 0x2f8
/* 8013ECC4 0013B8A4  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013ECC8 0013B8A8  48 24 95 59 */	bl __assert
lbl_8013ECCC:
/* 8013ECCC 0013B8AC  28 1F 00 00 */	cmplwi r31, 0
/* 8013ECD0 0013B8B0  40 82 00 14 */	bne lbl_8013ECE4
/* 8013ECD4 0013B8B4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013ECD8 0013B8B8  38 80 02 F9 */	li r4, 0x2f9
/* 8013ECDC 0013B8BC  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013ECE0 0013B8C0  48 24 95 41 */	bl __assert
lbl_8013ECE4:
/* 8013ECE4 0013B8C4  80 7F 00 00 */	lwz r3, 0(r31)
/* 8013ECE8 0013B8C8  80 1F 00 04 */	lwz r0, 4(r31)
/* 8013ECEC 0013B8CC  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 8013ECF0 0013B8D0  90 1E 00 30 */	stw r0, 0x30(r30)
/* 8013ECF4 0013B8D4  80 1F 00 08 */	lwz r0, 8(r31)
/* 8013ECF8 0013B8D8  90 1E 00 34 */	stw r0, 0x34(r30)
/* 8013ECFC 0013B8DC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8013ED00 0013B8E0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013ED04 0013B8E4  40 82 00 4C */	bne lbl_8013ED50
/* 8013ED08 0013B8E8  28 1E 00 00 */	cmplwi r30, 0
/* 8013ED0C 0013B8EC  41 82 00 44 */	beq lbl_8013ED50
/* 8013ED10 0013B8F0  40 82 00 14 */	bne lbl_8013ED24
/* 8013ED14 0013B8F4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013ED18 0013B8F8  38 80 02 34 */	li r4, 0x234
/* 8013ED1C 0013B8FC  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013ED20 0013B900  48 24 95 01 */	bl __assert
lbl_8013ED24:
/* 8013ED24 0013B904  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8013ED28 0013B908  38 60 00 00 */	li r3, 0
/* 8013ED2C 0013B90C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013ED30 0013B910  40 82 00 10 */	bne lbl_8013ED40
/* 8013ED34 0013B914  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013ED38 0013B918  41 82 00 08 */	beq lbl_8013ED40
/* 8013ED3C 0013B91C  38 60 00 01 */	li r3, 1
lbl_8013ED40:
/* 8013ED40 0013B920  2C 03 00 00 */	cmpwi r3, 0
/* 8013ED44 0013B924  40 82 00 0C */	bne lbl_8013ED50
/* 8013ED48 0013B928  7F C3 F3 78 */	mr r3, r30
/* 8013ED4C 0013B92C  48 23 45 9D */	bl HSD_JObjSetMtxDirtySub
lbl_8013ED50:
/* 8013ED50 0013B930  C8 22 A2 60 */	lfd f1, lbl_804D9C40(r2)
/* 8013ED54 0013B934  7F 83 E3 78 */	mr r3, r28
/* 8013ED58 0013B938  C0 1C 00 2C */	lfs f0, 0x2c(r28)
/* 8013ED5C 0013B93C  38 80 00 00 */	li r4, 0
/* 8013ED60 0013B940  FC 21 00 32 */	fmul f1, f1, f0
/* 8013ED64 0013B944  FC 20 08 18 */	frsp f1, f1
/* 8013ED68 0013B948  4B F3 6D 89 */	bl func_80075AF0
/* 8013ED6C 0013B94C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013ED70 0013B950  C0 3C 23 60 */	lfs f1, 0x2360(r28)
/* 8013ED74 0013B954  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8013ED78 0013B958  41 82 00 08 */	beq lbl_8013ED80
/* 8013ED7C 0013B95C  D0 3C 00 2C */	stfs f1, 0x2c(r28)
lbl_8013ED80:
/* 8013ED80 0013B960  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013ED84 0013B964  7F A3 EB 78 */	mr r3, r29
/* 8013ED88 0013B968  D0 1C 23 60 */	stfs f0, 0x2360(r28)
/* 8013ED8C 0013B96C  4B F4 B5 31 */	bl func_8008A2BC
lbl_8013ED90:
/* 8013ED90 0013B970  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8013ED94 0013B974  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8013ED98 0013B978  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8013ED9C 0013B97C  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8013EDA0 0013B980  83 81 00 30 */	lwz r28, 0x30(r1)
/* 8013EDA4 0013B984  38 21 00 40 */	addi r1, r1, 0x40
/* 8013EDA8 0013B988  7C 08 03 A6 */	mtlr r0
/* 8013EDAC 0013B98C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013EDB0()
{ // clang-format off
    nofralloc
/* 8013EDB0 0013B990  7C 08 02 A6 */	mflr r0
/* 8013EDB4 0013B994  90 01 00 04 */	stw r0, 4(r1)
/* 8013EDB8 0013B998  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8013EDBC 0013B99C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8013EDC0 0013B9A0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8013EDC4 0013B9A4  7C 7E 1B 78 */	mr r30, r3
/* 8013EDC8 0013B9A8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8013EDCC 0013B9AC  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013EDD0 0013B9B0  7C 9F 23 78 */	mr r31, r4
/* 8013EDD4 0013B9B4  D0 04 23 60 */	stfs f0, 0x2360(r4)
/* 8013EDD8 0013B9B8  4B F3 04 61 */	bl ftAnim_IsFramesRemaining
/* 8013EDDC 0013B9BC  2C 03 00 00 */	cmpwi r3, 0
/* 8013EDE0 0013B9C0  40 82 00 8C */	bne lbl_8013EE6C
/* 8013EDE4 0013B9C4  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013EDE8 0013B9C8  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013EDEC 0013B9CC  38 7E 00 00 */	addi r3, r30, 0
/* 8013EDF0 0013B9D0  FC 40 08 90 */	fmr f2, f1
/* 8013EDF4 0013B9D4  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013EDF8 0013B9D8  FC 60 08 90 */	fmr f3, f1
/* 8013EDFC 0013B9DC  38 80 01 64 */	li r4, 0x164
/* 8013EE00 0013B9E0  38 C0 00 00 */	li r6, 0
/* 8013EE04 0013B9E4  4B F2 A5 A9 */	bl Fighter_ActionStateChange_800693AC
/* 8013EE08 0013B9E8  3C 60 80 14 */	lis r3, lbl_8013D658@ha
/* 8013EE0C 0013B9EC  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8013EE10 0013B9F0  38 03 D6 58 */	addi r0, r3, lbl_8013D658@l
/* 8013EE14 0013B9F4  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 8013EE18 0013B9F8  3C 80 80 14 */	lis r4, lbl_8013D764@ha
/* 8013EE1C 0013B9FC  38 84 D7 64 */	addi r4, r4, lbl_8013D764@l
/* 8013EE20 0013BA00  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 8013EE24 0013BA04  3C 60 80 14 */	lis r3, lbl_8014222C@ha
/* 8013EE28 0013BA08  38 03 22 2C */	addi r0, r3, lbl_8014222C@l
/* 8013EE2C 0013BA0C  90 85 21 C0 */	stw r4, 0x21c0(r5)
/* 8013EE30 0013BA10  7F C3 F3 78 */	mr r3, r30
/* 8013EE34 0013BA14  90 05 21 F8 */	stw r0, 0x21f8(r5)
/* 8013EE38 0013BA18  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013EE3C 0013BA1C  D0 3F 08 94 */	stfs f1, 0x894(r31)
/* 8013EE40 0013BA20  4B F3 03 51 */	bl ftAnim_SetAnimRate
/* 8013EE44 0013BA24  C0 22 A2 84 */	lfs f1, lbl_804D9C64(r2)
/* 8013EE48 0013BA28  7F E3 FB 78 */	mr r3, r31
/* 8013EE4C 0013BA2C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8013EE50 0013BA30  38 80 00 00 */	li r4, 0
/* 8013EE54 0013BA34  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013EE58 0013BA38  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8013EE5C 0013BA3C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013EE60 0013BA40  D0 1F 00 74 */	stfs f0, 0x74(r31)
/* 8013EE64 0013BA44  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013EE68 0013BA48  4B F3 6C 89 */	bl func_80075AF0
lbl_8013EE6C:
/* 8013EE6C 0013BA4C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013EE70 0013BA50  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8013EE74 0013BA54  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8013EE78 0013BA58  38 21 00 28 */	addi r1, r1, 0x28
/* 8013EE7C 0013BA5C  7C 08 03 A6 */	mtlr r0
/* 8013EE80 0013BA60  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013EE84()
{ // clang-format off
    nofralloc
/* 8013EE84 0013BA64  7C 08 02 A6 */	mflr r0
/* 8013EE88 0013BA68  38 80 00 00 */	li r4, 0
/* 8013EE8C 0013BA6C  90 01 00 04 */	stw r0, 4(r1)
/* 8013EE90 0013BA70  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8013EE94 0013BA74  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8013EE98 0013BA78  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8013EE9C 0013BA7C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8013EEA0 0013BA80  7C 7D 1B 78 */	mr r29, r3
/* 8013EEA4 0013BA84  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013EEA8 0013BA88  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013EEAC 0013BA8C  4B FF EE A9 */	bl func_8013DD54
/* 8013EEB0 0013BA90  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013EEB4 0013BA94  3C 60 43 30 */	lis r3, 0x4330
/* 8013EEB8 0013BA98  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013EEBC 0013BA9C  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013EEC0 0013BAA0  C8 42 A2 90 */	lfd f2, lbl_804D9C70(r2)
/* 8013EEC4 0013BAA4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013EEC8 0013BAA8  C0 1E 00 A8 */	lfs f0, 0xa8(r30)
/* 8013EECC 0013BAAC  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8013EED0 0013BAB0  90 61 00 28 */	stw r3, 0x28(r1)
/* 8013EED4 0013BAB4  C8 21 00 28 */	lfd f1, 0x28(r1)
/* 8013EED8 0013BAB8  EC 21 10 28 */	fsubs f1, f1, f2
/* 8013EEDC 0013BABC  EC 01 00 2A */	fadds f0, f1, f0
/* 8013EEE0 0013BAC0  FC 00 00 1E */	fctiwz f0, f0
/* 8013EEE4 0013BAC4  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 8013EEE8 0013BAC8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013EEEC 0013BACC  90 1F 23 6C */	stw r0, 0x236c(r31)
/* 8013EEF0 0013BAD0  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013EEF4 0013BAD4  C0 3E 00 A4 */	lfs f1, 0xa4(r30)
/* 8013EEF8 0013BAD8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013EEFC 0013BADC  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8013EF00 0013BAE0  90 61 00 18 */	stw r3, 0x18(r1)
/* 8013EF04 0013BAE4  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8013EF08 0013BAE8  EC 00 10 28 */	fsubs f0, f0, f2
/* 8013EF0C 0013BAEC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8013EF10 0013BAF0  4C 41 13 82 */	cror 2, 1, 2
/* 8013EF14 0013BAF4  40 82 00 5C */	bne lbl_8013EF70
/* 8013EF18 0013BAF8  FC 00 08 1E */	fctiwz f0, f1
/* 8013EF1C 0013BAFC  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8013EF20 0013BB00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8013EF24 0013BB04  90 1F 23 6C */	stw r0, 0x236c(r31)
/* 8013EF28 0013BB08  80 1F 23 70 */	lwz r0, 0x2370(r31)
/* 8013EF2C 0013BB0C  2C 00 00 00 */	cmpwi r0, 0
/* 8013EF30 0013BB10  40 82 00 14 */	bne lbl_8013EF44
/* 8013EF34 0013BB14  38 7F 00 00 */	addi r3, r31, 0
/* 8013EF38 0013BB18  38 80 00 05 */	li r4, 5
/* 8013EF3C 0013BB1C  38 A0 00 00 */	li r5, 0
/* 8013EF40 0013BB20  4B F8 10 91 */	bl func_800BFFD0
lbl_8013EF44:
/* 8013EF44 0013BB24  38 00 00 01 */	li r0, 1
/* 8013EF48 0013BB28  90 1F 23 70 */	stw r0, 0x2370(r31)
/* 8013EF4C 0013BB2C  3C 80 0C 4C */	lis r4, 0x0C4C0292@ha
/* 8013EF50 0013BB30  38 7D 00 00 */	addi r3, r29, 0
/* 8013EF54 0013BB34  C0 42 A2 68 */	lfs f2, lbl_804D9C48(r2)
/* 8013EF58 0013BB38  38 A4 02 92 */	addi r5, r4, 0x0C4C0292@l
/* 8013EF5C 0013BB3C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013EF60 0013BB40  38 80 01 65 */	li r4, 0x165
/* 8013EF64 0013BB44  FC 60 10 90 */	fmr f3, f2
/* 8013EF68 0013BB48  38 C0 00 00 */	li r6, 0
/* 8013EF6C 0013BB4C  4B F2 A4 41 */	bl Fighter_ActionStateChange_800693AC
lbl_8013EF70:
/* 8013EF70 0013BB50  80 7F 23 6C */	lwz r3, 0x236c(r31)
/* 8013EF74 0013BB54  3C 00 43 30 */	lis r0, 0x4330
/* 8013EF78 0013BB58  C8 62 A2 90 */	lfd f3, lbl_804D9C70(r2)
/* 8013EF7C 0013BB5C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8013EF80 0013BB60  C0 22 A2 88 */	lfs f1, lbl_804D9C68(r2)
/* 8013EF84 0013BB64  90 61 00 1C */	stw r3, 0x1c(r1)
/* 8013EF88 0013BB68  C0 1E 00 AC */	lfs f0, 0xac(r30)
/* 8013EF8C 0013BB6C  90 01 00 18 */	stw r0, 0x18(r1)
/* 8013EF90 0013BB70  EC 21 00 32 */	fmuls f1, f1, f0
/* 8013EF94 0013BB74  C0 9F 23 74 */	lfs f4, 0x2374(r31)
/* 8013EF98 0013BB78  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 8013EF9C 0013BB7C  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 8013EFA0 0013BB80  EC 42 18 28 */	fsubs f2, f2, f3
/* 8013EFA4 0013BB84  EC 22 00 72 */	fmuls f1, f2, f1
/* 8013EFA8 0013BB88  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8013EFAC 0013BB8C  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 8013EFB0 0013BB90  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8013EFB4 0013BB94  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013EFB8 0013BB98  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013EFBC 0013BB9C  48 00 00 14 */	b lbl_8013EFD0
lbl_8013EFC0:
/* 8013EFC0 0013BBA0  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013EFC4 0013BBA4  FC 21 10 2A */	fadd f1, f1, f2
/* 8013EFC8 0013BBA8  FC 20 08 18 */	frsp f1, f1
/* 8013EFCC 0013BBAC  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013EFD0:
/* 8013EFD0 0013BBB0  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013EFD4 0013BBB4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013EFD8 0013BBB8  41 80 FF E8 */	blt lbl_8013EFC0
/* 8013EFDC 0013BBBC  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013EFE0 0013BBC0  48 00 00 14 */	b lbl_8013EFF4
lbl_8013EFE4:
/* 8013EFE4 0013BBC4  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013EFE8 0013BBC8  FC 00 10 28 */	fsub f0, f0, f2
/* 8013EFEC 0013BBCC  FC 00 00 18 */	frsp f0, f0
/* 8013EFF0 0013BBD0  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013EFF4:
/* 8013EFF4 0013BBD4  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013EFF8 0013BBD8  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013EFFC 0013BBDC  41 81 FF E8 */	bgt lbl_8013EFE4
/* 8013F000 0013BBE0  38 80 00 03 */	li r4, 3
/* 8013F004 0013BBE4  4B F3 69 29 */	bl func_8007592C
/* 8013F008 0013BBE8  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013F00C 0013BBEC  38 7F 00 00 */	addi r3, r31, 0
/* 8013F010 0013BBF0  38 80 00 00 */	li r4, 0
/* 8013F014 0013BBF4  4B F3 6A DD */	bl func_80075AF0
/* 8013F018 0013BBF8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8013F01C 0013BBFC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8013F020 0013BC00  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8013F024 0013BC04  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8013F028 0013BC08  38 21 00 40 */	addi r1, r1, 0x40
/* 8013F02C 0013BC0C  7C 08 03 A6 */	mtlr r0
/* 8013F030 0013BC10  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013F034()
{ // clang-format off
    nofralloc
/* 8013F034 0013BC14  7C 08 02 A6 */	mflr r0
/* 8013F038 0013BC18  38 80 00 00 */	li r4, 0
/* 8013F03C 0013BC1C  90 01 00 04 */	stw r0, 4(r1)
/* 8013F040 0013BC20  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8013F044 0013BC24  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8013F048 0013BC28  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8013F04C 0013BC2C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8013F050 0013BC30  7C 7D 1B 78 */	mr r29, r3
/* 8013F054 0013BC34  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013F058 0013BC38  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013F05C 0013BC3C  4B FF EC F9 */	bl func_8013DD54
/* 8013F060 0013BC40  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013F064 0013BC44  3C 60 43 30 */	lis r3, 0x4330
/* 8013F068 0013BC48  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 8013F06C 0013BC4C  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013F070 0013BC50  C8 42 A2 90 */	lfd f2, lbl_804D9C70(r2)
/* 8013F074 0013BC54  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013F078 0013BC58  C0 1E 00 A8 */	lfs f0, 0xa8(r30)
/* 8013F07C 0013BC5C  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8013F080 0013BC60  90 61 00 28 */	stw r3, 0x28(r1)
/* 8013F084 0013BC64  C8 21 00 28 */	lfd f1, 0x28(r1)
/* 8013F088 0013BC68  EC 21 10 28 */	fsubs f1, f1, f2
/* 8013F08C 0013BC6C  EC 01 00 2A */	fadds f0, f1, f0
/* 8013F090 0013BC70  FC 00 00 1E */	fctiwz f0, f0
/* 8013F094 0013BC74  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 8013F098 0013BC78  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013F09C 0013BC7C  90 1F 23 6C */	stw r0, 0x236c(r31)
/* 8013F0A0 0013BC80  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 8013F0A4 0013BC84  C0 3E 00 A4 */	lfs f1, 0xa4(r30)
/* 8013F0A8 0013BC88  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8013F0AC 0013BC8C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8013F0B0 0013BC90  90 61 00 18 */	stw r3, 0x18(r1)
/* 8013F0B4 0013BC94  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8013F0B8 0013BC98  EC 00 10 28 */	fsubs f0, f0, f2
/* 8013F0BC 0013BC9C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8013F0C0 0013BCA0  4C 41 13 82 */	cror 2, 1, 2
/* 8013F0C4 0013BCA4  40 82 00 1C */	bne lbl_8013F0E0
/* 8013F0C8 0013BCA8  FC 00 08 1E */	fctiwz f0, f1
/* 8013F0CC 0013BCAC  38 00 00 01 */	li r0, 1
/* 8013F0D0 0013BCB0  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8013F0D4 0013BCB4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8013F0D8 0013BCB8  90 7F 23 6C */	stw r3, 0x236c(r31)
/* 8013F0DC 0013BCBC  90 1F 23 70 */	stw r0, 0x2370(r31)
lbl_8013F0E0:
/* 8013F0E0 0013BCC0  80 7F 23 6C */	lwz r3, 0x236c(r31)
/* 8013F0E4 0013BCC4  3C 00 43 30 */	lis r0, 0x4330
/* 8013F0E8 0013BCC8  C8 62 A2 90 */	lfd f3, lbl_804D9C70(r2)
/* 8013F0EC 0013BCCC  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8013F0F0 0013BCD0  C0 22 A2 88 */	lfs f1, lbl_804D9C68(r2)
/* 8013F0F4 0013BCD4  90 61 00 1C */	stw r3, 0x1c(r1)
/* 8013F0F8 0013BCD8  C0 1E 00 AC */	lfs f0, 0xac(r30)
/* 8013F0FC 0013BCDC  90 01 00 18 */	stw r0, 0x18(r1)
/* 8013F100 0013BCE0  EC 21 00 32 */	fmuls f1, f1, f0
/* 8013F104 0013BCE4  C0 9F 23 74 */	lfs f4, 0x2374(r31)
/* 8013F108 0013BCE8  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 8013F10C 0013BCEC  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 8013F110 0013BCF0  EC 42 18 28 */	fsubs f2, f2, f3
/* 8013F114 0013BCF4  EC 22 00 72 */	fmuls f1, f2, f1
/* 8013F118 0013BCF8  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8013F11C 0013BCFC  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 8013F120 0013BD00  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8013F124 0013BD04  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013F128 0013BD08  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013F12C 0013BD0C  48 00 00 14 */	b lbl_8013F140
lbl_8013F130:
/* 8013F130 0013BD10  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F134 0013BD14  FC 21 10 2A */	fadd f1, f1, f2
/* 8013F138 0013BD18  FC 20 08 18 */	frsp f1, f1
/* 8013F13C 0013BD1C  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013F140:
/* 8013F140 0013BD20  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F144 0013BD24  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013F148 0013BD28  41 80 FF E8 */	blt lbl_8013F130
/* 8013F14C 0013BD2C  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013F150 0013BD30  48 00 00 14 */	b lbl_8013F164
lbl_8013F154:
/* 8013F154 0013BD34  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013F158 0013BD38  FC 00 10 28 */	fsub f0, f0, f2
/* 8013F15C 0013BD3C  FC 00 00 18 */	frsp f0, f0
/* 8013F160 0013BD40  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013F164:
/* 8013F164 0013BD44  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F168 0013BD48  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013F16C 0013BD4C  41 81 FF E8 */	bgt lbl_8013F154
/* 8013F170 0013BD50  38 80 00 03 */	li r4, 3
/* 8013F174 0013BD54  4B F3 67 B9 */	bl func_8007592C
/* 8013F178 0013BD58  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013F17C 0013BD5C  38 7F 00 00 */	addi r3, r31, 0
/* 8013F180 0013BD60  38 80 00 00 */	li r4, 0
/* 8013F184 0013BD64  4B F3 69 6D */	bl func_80075AF0
/* 8013F188 0013BD68  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8013F18C 0013BD6C  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8013F190 0013BD70  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8013F194 0013BD74  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8013F198 0013BD78  38 21 00 40 */	addi r1, r1, 0x40
/* 8013F19C 0013BD7C  7C 08 03 A6 */	mtlr r0
/* 8013F1A0 0013BD80  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013F1A4()
{ // clang-format off
    nofralloc
/* 8013F1A4 0013BD84  7C 08 02 A6 */	mflr r0
/* 8013F1A8 0013BD88  3C 80 80 3D */	lis r4, lbl_803D05C8@ha
/* 8013F1AC 0013BD8C  90 01 00 04 */	stw r0, 4(r1)
/* 8013F1B0 0013BD90  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 8013F1B4 0013BD94  DB E1 00 68 */	stfd f31, 0x68(r1)
/* 8013F1B8 0013BD98  DB C1 00 60 */	stfd f30, 0x60(r1)
/* 8013F1BC 0013BD9C  BF 41 00 48 */	stmw r26, 0x48(r1)
/* 8013F1C0 0013BDA0  3B E4 05 C8 */	addi r31, r4, lbl_803D05C8@l
/* 8013F1C4 0013BDA4  7C 7A 1B 78 */	mr r26, r3
/* 8013F1C8 0013BDA8  38 80 00 00 */	li r4, 0
/* 8013F1CC 0013BDAC  83 83 00 2C */	lwz r28, 0x2c(r3)
/* 8013F1D0 0013BDB0  83 7C 02 D4 */	lwz r27, 0x2d4(r28)
/* 8013F1D4 0013BDB4  4B FF EB 81 */	bl func_8013DD54
/* 8013F1D8 0013BDB8  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013F1DC 0013BDBC  D0 1C 23 60 */	stfs f0, 0x2360(r28)
/* 8013F1E0 0013BDC0  83 BA 00 2C */	lwz r29, 0x2c(r26)
/* 8013F1E4 0013BDC4  83 DA 00 28 */	lwz r30, 0x28(r26)
/* 8013F1E8 0013BDC8  80 1D 23 48 */	lwz r0, 0x2348(r29)
/* 8013F1EC 0013BDCC  2C 00 00 00 */	cmpwi r0, 0
/* 8013F1F0 0013BDD0  41 80 00 D0 */	blt lbl_8013F2C0
/* 8013F1F4 0013BDD4  2C 00 00 04 */	cmpwi r0, 4
/* 8013F1F8 0013BDD8  40 80 00 C8 */	bge lbl_8013F2C0
/* 8013F1FC 0013BDDC  C0 1D 22 30 */	lfs f0, 0x2230(r29)
/* 8013F200 0013BDE0  54 00 10 3A */	slwi r0, r0, 2
/* 8013F204 0013BDE4  7C 7F 02 14 */	add r3, r31, r0
/* 8013F208 0013BDE8  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8013F20C 0013BDEC  28 1E 00 00 */	cmplwi r30, 0
/* 8013F210 0013BDF0  C0 3D 22 34 */	lfs f1, 0x2234(r29)
/* 8013F214 0013BDF4  7C 1F 04 2E */	lfsx f0, r31, r0
/* 8013F218 0013BDF8  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013F21C 0013BDFC  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 8013F220 0013BE00  C0 3D 22 38 */	lfs f1, 0x2238(r29)
/* 8013F224 0013BE04  C0 03 00 10 */	lfs f0, 0x10(r3)
/* 8013F228 0013BE08  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013F22C 0013BE0C  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8013F230 0013BE10  40 82 00 14 */	bne lbl_8013F244
/* 8013F234 0013BE14  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F238 0013BE18  38 80 02 F8 */	li r4, 0x2f8
/* 8013F23C 0013BE1C  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F240 0013BE20  48 24 8F E1 */	bl __assert
lbl_8013F244:
/* 8013F244 0013BE24  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8013F248 0013BE28  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8013F24C 0013BE2C  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 8013F250 0013BE30  90 1E 00 30 */	stw r0, 0x30(r30)
/* 8013F254 0013BE34  80 01 00 38 */	lwz r0, 0x38(r1)
/* 8013F258 0013BE38  90 1E 00 34 */	stw r0, 0x34(r30)
/* 8013F25C 0013BE3C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8013F260 0013BE40  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013F264 0013BE44  40 82 00 4C */	bne lbl_8013F2B0
/* 8013F268 0013BE48  28 1E 00 00 */	cmplwi r30, 0
/* 8013F26C 0013BE4C  41 82 00 44 */	beq lbl_8013F2B0
/* 8013F270 0013BE50  40 82 00 14 */	bne lbl_8013F284
/* 8013F274 0013BE54  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F278 0013BE58  38 80 02 34 */	li r4, 0x234
/* 8013F27C 0013BE5C  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F280 0013BE60  48 24 8F A1 */	bl __assert
lbl_8013F284:
/* 8013F284 0013BE64  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8013F288 0013BE68  38 60 00 00 */	li r3, 0
/* 8013F28C 0013BE6C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013F290 0013BE70  40 82 00 10 */	bne lbl_8013F2A0
/* 8013F294 0013BE74  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013F298 0013BE78  41 82 00 08 */	beq lbl_8013F2A0
/* 8013F29C 0013BE7C  38 60 00 01 */	li r3, 1
lbl_8013F2A0:
/* 8013F2A0 0013BE80  2C 03 00 00 */	cmpwi r3, 0
/* 8013F2A4 0013BE84  40 82 00 0C */	bne lbl_8013F2B0
/* 8013F2A8 0013BE88  7F C3 F3 78 */	mr r3, r30
/* 8013F2AC 0013BE8C  48 23 40 3D */	bl HSD_JObjSetMtxDirtySub
lbl_8013F2B0:
/* 8013F2B0 0013BE90  80 7D 23 48 */	lwz r3, 0x2348(r29)
/* 8013F2B4 0013BE94  38 03 00 01 */	addi r0, r3, 1
/* 8013F2B8 0013BE98  90 1D 23 48 */	stw r0, 0x2348(r29)
/* 8013F2BC 0013BE9C  48 00 00 A4 */	b lbl_8013F360
lbl_8013F2C0:
/* 8013F2C0 0013BEA0  28 1E 00 00 */	cmplwi r30, 0
/* 8013F2C4 0013BEA4  3B BD 22 30 */	addi r29, r29, 0x2230
/* 8013F2C8 0013BEA8  40 82 00 14 */	bne lbl_8013F2DC
/* 8013F2CC 0013BEAC  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F2D0 0013BEB0  38 80 02 F8 */	li r4, 0x2f8
/* 8013F2D4 0013BEB4  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F2D8 0013BEB8  48 24 8F 49 */	bl __assert
lbl_8013F2DC:
/* 8013F2DC 0013BEBC  28 1D 00 00 */	cmplwi r29, 0
/* 8013F2E0 0013BEC0  40 82 00 14 */	bne lbl_8013F2F4
/* 8013F2E4 0013BEC4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F2E8 0013BEC8  38 80 02 F9 */	li r4, 0x2f9
/* 8013F2EC 0013BECC  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013F2F0 0013BED0  48 24 8F 31 */	bl __assert
lbl_8013F2F4:
/* 8013F2F4 0013BED4  80 7D 00 00 */	lwz r3, 0(r29)
/* 8013F2F8 0013BED8  80 1D 00 04 */	lwz r0, 4(r29)
/* 8013F2FC 0013BEDC  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 8013F300 0013BEE0  90 1E 00 30 */	stw r0, 0x30(r30)
/* 8013F304 0013BEE4  80 1D 00 08 */	lwz r0, 8(r29)
/* 8013F308 0013BEE8  90 1E 00 34 */	stw r0, 0x34(r30)
/* 8013F30C 0013BEEC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8013F310 0013BEF0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013F314 0013BEF4  40 82 00 4C */	bne lbl_8013F360
/* 8013F318 0013BEF8  28 1E 00 00 */	cmplwi r30, 0
/* 8013F31C 0013BEFC  41 82 00 44 */	beq lbl_8013F360
/* 8013F320 0013BF00  40 82 00 14 */	bne lbl_8013F334
/* 8013F324 0013BF04  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F328 0013BF08  38 80 02 34 */	li r4, 0x234
/* 8013F32C 0013BF0C  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F330 0013BF10  48 24 8E F1 */	bl __assert
lbl_8013F334:
/* 8013F334 0013BF14  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8013F338 0013BF18  38 60 00 00 */	li r3, 0
/* 8013F33C 0013BF1C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013F340 0013BF20  40 82 00 10 */	bne lbl_8013F350
/* 8013F344 0013BF24  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013F348 0013BF28  41 82 00 08 */	beq lbl_8013F350
/* 8013F34C 0013BF2C  38 60 00 01 */	li r3, 1
lbl_8013F350:
/* 8013F350 0013BF30  2C 03 00 00 */	cmpwi r3, 0
/* 8013F354 0013BF34  40 82 00 0C */	bne lbl_8013F360
/* 8013F358 0013BF38  7F C3 F3 78 */	mr r3, r30
/* 8013F35C 0013BF3C  48 23 3F 8D */	bl HSD_JObjSetMtxDirtySub
lbl_8013F360:
/* 8013F360 0013BF40  80 9A 00 2C */	lwz r4, 0x2c(r26)
/* 8013F364 0013BF44  80 64 23 4C */	lwz r3, 0x234c(r4)
/* 8013F368 0013BF48  80 A4 02 D4 */	lwz r5, 0x2d4(r4)
/* 8013F36C 0013BF4C  38 03 00 01 */	addi r0, r3, 1
/* 8013F370 0013BF50  90 04 23 4C */	stw r0, 0x234c(r4)
/* 8013F374 0013BF54  80 64 23 4C */	lwz r3, 0x234c(r4)
/* 8013F378 0013BF58  80 05 00 9C */	lwz r0, 0x9c(r5)
/* 8013F37C 0013BF5C  7C 03 00 00 */	cmpw r3, r0
/* 8013F380 0013BF60  41 80 00 28 */	blt lbl_8013F3A8
/* 8013F384 0013BF64  80 04 09 14 */	lwz r0, 0x914(r4)
/* 8013F388 0013BF68  2C 00 00 00 */	cmpwi r0, 0
/* 8013F38C 0013BF6C  41 82 00 1C */	beq lbl_8013F3A8
/* 8013F390 0013BF70  80 64 09 18 */	lwz r3, 0x918(r4)
/* 8013F394 0013BF74  38 00 00 00 */	li r0, 0
/* 8013F398 0013BF78  38 63 00 01 */	addi r3, r3, 1
/* 8013F39C 0013BF7C  54 63 07 FE */	clrlwi r3, r3, 0x1f
/* 8013F3A0 0013BF80  90 64 09 18 */	stw r3, 0x918(r4)
/* 8013F3A4 0013BF84  90 04 23 4C */	stw r0, 0x234c(r4)
lbl_8013F3A8:
/* 8013F3A8 0013BF88  7F 43 D3 78 */	mr r3, r26
/* 8013F3AC 0013BF8C  4B FF E5 39 */	bl func_8013D8E4
/* 8013F3B0 0013BF90  80 7C 23 6C */	lwz r3, 0x236c(r28)
/* 8013F3B4 0013BF94  3C 00 43 30 */	lis r0, 0x4330
/* 8013F3B8 0013BF98  C8 22 A2 98 */	lfd f1, lbl_804D9C78(r2)
/* 8013F3BC 0013BF9C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8013F3C0 0013BFA0  C0 1B 00 98 */	lfs f0, 0x98(r27)
/* 8013F3C4 0013BFA4  90 61 00 44 */	stw r3, 0x44(r1)
/* 8013F3C8 0013BFA8  FC 81 00 32 */	fmul f4, f1, f0
/* 8013F3CC 0013BFAC  C0 7C 23 74 */	lfs f3, 0x2374(r28)
/* 8013F3D0 0013BFB0  90 01 00 40 */	stw r0, 0x40(r1)
/* 8013F3D4 0013BFB4  C8 22 A2 90 */	lfd f1, lbl_804D9C70(r2)
/* 8013F3D8 0013BFB8  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 8013F3DC 0013BFBC  EC 20 08 28 */	fsubs f1, f0, f1
/* 8013F3E0 0013BFC0  C0 42 A2 88 */	lfs f2, lbl_804D9C68(r2)
/* 8013F3E4 0013BFC4  FC 64 00 F2 */	fmul f3, f4, f3
/* 8013F3E8 0013BFC8  C0 1B 00 BC */	lfs f0, 0xbc(r27)
/* 8013F3EC 0013BFCC  C3 FC 23 54 */	lfs f31, 0x2354(r28)
/* 8013F3F0 0013BFD0  EC 22 00 72 */	fmuls f1, f2, f1
/* 8013F3F4 0013BFD4  FC 40 18 18 */	frsp f2, f3
/* 8013F3F8 0013BFD8  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013F3FC 0013BFDC  EF C2 00 32 */	fmuls f30, f2, f0
/* 8013F400 0013BFE0  EC 1F F0 2A */	fadds f0, f31, f30
/* 8013F404 0013BFE4  D0 1C 23 54 */	stfs f0, 0x2354(r28)
/* 8013F408 0013BFE8  80 7A 00 2C */	lwz r3, 0x2c(r26)
/* 8013F40C 0013BFEC  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013F410 0013BFF0  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013F414 0013BFF4  48 00 00 14 */	b lbl_8013F428
lbl_8013F418:
/* 8013F418 0013BFF8  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F41C 0013BFFC  FC 21 10 2A */	fadd f1, f1, f2
/* 8013F420 0013C000  FC 20 08 18 */	frsp f1, f1
/* 8013F424 0013C004  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013F428:
/* 8013F428 0013C008  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F42C 0013C00C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013F430 0013C010  41 80 FF E8 */	blt lbl_8013F418
/* 8013F434 0013C014  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013F438 0013C018  48 00 00 14 */	b lbl_8013F44C
lbl_8013F43C:
/* 8013F43C 0013C01C  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013F440 0013C020  FC 00 10 28 */	fsub f0, f0, f2
/* 8013F444 0013C024  FC 00 00 18 */	frsp f0, f0
/* 8013F448 0013C028  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013F44C:
/* 8013F44C 0013C02C  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F450 0013C030  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013F454 0013C034  41 81 FF E8 */	bgt lbl_8013F43C
/* 8013F458 0013C038  38 80 00 03 */	li r4, 3
/* 8013F45C 0013C03C  4B F3 64 D1 */	bl func_8007592C
/* 8013F460 0013C040  80 7C 23 40 */	lwz r3, 0x2340(r28)
/* 8013F464 0013C044  38 03 FF FF */	addi r0, r3, -1
/* 8013F468 0013C048  90 1C 23 40 */	stw r0, 0x2340(r28)
/* 8013F46C 0013C04C  80 1C 23 40 */	lwz r0, 0x2340(r28)
/* 8013F470 0013C050  2C 00 00 00 */	cmpwi r0, 0
/* 8013F474 0013C054  41 81 02 68 */	bgt lbl_8013F6DC
/* 8013F478 0013C058  C8 02 A2 60 */	lfd f0, lbl_804D9C40(r2)
/* 8013F47C 0013C05C  C0 5C 23 54 */	lfs f2, 0x2354(r28)
/* 8013F480 0013C060  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8013F484 0013C064  40 80 01 BC */	bge lbl_8013F640
/* 8013F488 0013C068  C8 02 A2 A0 */	lfd f0, lbl_804D9C80(r2)
/* 8013F48C 0013C06C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013F490 0013C070  40 80 01 B0 */	bge lbl_8013F640
/* 8013F494 0013C074  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013F498 0013C078  FC 1E 08 40 */	fcmpo cr0, f30, f1
/* 8013F49C 0013C07C  40 81 00 D4 */	ble lbl_8013F570
/* 8013F4A0 0013C080  C8 02 A2 A8 */	lfd f0, lbl_804D9C88(r2)
/* 8013F4A4 0013C084  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013F4A8 0013C088  40 81 00 2C */	ble lbl_8013F4D4
/* 8013F4AC 0013C08C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8013F4B0 0013C090  40 80 00 24 */	bge lbl_8013F4D4
/* 8013F4B4 0013C094  38 00 00 00 */	li r0, 0
/* 8013F4B8 0013C098  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013F4BC 0013C09C  90 1C 23 40 */	stw r0, 0x2340(r28)
/* 8013F4C0 0013C0A0  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013F4C4 0013C0A4  38 7A 00 00 */	addi r3, r26, 0
/* 8013F4C8 0013C0A8  38 80 00 01 */	li r4, 1
/* 8013F4CC 0013C0AC  4B FF E5 59 */	bl func_8013DA24
/* 8013F4D0 0013C0B0  48 00 02 1C */	b lbl_8013F6EC
lbl_8013F4D4:
/* 8013F4D4 0013C0B4  80 7C 05 E8 */	lwz r3, 0x5e8(r28)
/* 8013F4D8 0013C0B8  83 43 00 00 */	lwz r26, 0(r3)
/* 8013F4DC 0013C0BC  28 1A 00 00 */	cmplwi r26, 0
/* 8013F4E0 0013C0C0  40 82 00 14 */	bne lbl_8013F4F4
/* 8013F4E4 0013C0C4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F4E8 0013C0C8  38 80 02 94 */	li r4, 0x294
/* 8013F4EC 0013C0CC  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F4F0 0013C0D0  48 24 8D 31 */	bl __assert
lbl_8013F4F4:
/* 8013F4F4 0013C0D4  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 8013F4F8 0013C0D8  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8013F4FC 0013C0DC  41 82 00 14 */	beq lbl_8013F510
/* 8013F500 0013C0E0  38 BF 00 20 */	addi r5, r31, 0x20
/* 8013F504 0013C0E4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F508 0013C0E8  38 80 02 95 */	li r4, 0x295
/* 8013F50C 0013C0EC  48 24 8D 15 */	bl __assert
lbl_8013F510:
/* 8013F510 0013C0F0  C0 02 A2 6C */	lfs f0, lbl_804D9C4C(r2)
/* 8013F514 0013C0F4  D0 1A 00 20 */	stfs f0, 0x20(r26)
/* 8013F518 0013C0F8  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 8013F51C 0013C0FC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013F520 0013C100  40 82 01 CC */	bne lbl_8013F6EC
/* 8013F524 0013C104  28 1A 00 00 */	cmplwi r26, 0
/* 8013F528 0013C108  41 82 01 C4 */	beq lbl_8013F6EC
/* 8013F52C 0013C10C  40 82 00 14 */	bne lbl_8013F540
/* 8013F530 0013C110  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F534 0013C114  38 80 02 34 */	li r4, 0x234
/* 8013F538 0013C118  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F53C 0013C11C  48 24 8C E5 */	bl __assert
lbl_8013F540:
/* 8013F540 0013C120  80 9A 00 14 */	lwz r4, 0x14(r26)
/* 8013F544 0013C124  38 60 00 00 */	li r3, 0
/* 8013F548 0013C128  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013F54C 0013C12C  40 82 00 10 */	bne lbl_8013F55C
/* 8013F550 0013C130  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013F554 0013C134  41 82 00 08 */	beq lbl_8013F55C
/* 8013F558 0013C138  38 60 00 01 */	li r3, 1
lbl_8013F55C:
/* 8013F55C 0013C13C  2C 03 00 00 */	cmpwi r3, 0
/* 8013F560 0013C140  40 82 01 8C */	bne lbl_8013F6EC
/* 8013F564 0013C144  7F 43 D3 78 */	mr r3, r26
/* 8013F568 0013C148  48 23 3D 81 */	bl HSD_JObjSetMtxDirtySub
/* 8013F56C 0013C14C  48 00 01 80 */	b lbl_8013F6EC
lbl_8013F570:
/* 8013F570 0013C150  C8 02 A2 A8 */	lfd f0, lbl_804D9C88(r2)
/* 8013F574 0013C154  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8013F578 0013C158  40 80 00 2C */	bge lbl_8013F5A4
/* 8013F57C 0013C15C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8013F580 0013C160  40 81 00 24 */	ble lbl_8013F5A4
/* 8013F584 0013C164  38 00 00 00 */	li r0, 0
/* 8013F588 0013C168  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013F58C 0013C16C  90 1C 23 40 */	stw r0, 0x2340(r28)
/* 8013F590 0013C170  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013F594 0013C174  38 7A 00 00 */	addi r3, r26, 0
/* 8013F598 0013C178  38 80 00 01 */	li r4, 1
/* 8013F59C 0013C17C  4B FF E4 89 */	bl func_8013DA24
/* 8013F5A0 0013C180  48 00 01 4C */	b lbl_8013F6EC
lbl_8013F5A4:
/* 8013F5A4 0013C184  80 7C 05 E8 */	lwz r3, 0x5e8(r28)
/* 8013F5A8 0013C188  83 43 00 00 */	lwz r26, 0(r3)
/* 8013F5AC 0013C18C  28 1A 00 00 */	cmplwi r26, 0
/* 8013F5B0 0013C190  40 82 00 14 */	bne lbl_8013F5C4
/* 8013F5B4 0013C194  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F5B8 0013C198  38 80 02 94 */	li r4, 0x294
/* 8013F5BC 0013C19C  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F5C0 0013C1A0  48 24 8C 61 */	bl __assert
lbl_8013F5C4:
/* 8013F5C4 0013C1A4  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 8013F5C8 0013C1A8  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8013F5CC 0013C1AC  41 82 00 14 */	beq lbl_8013F5E0
/* 8013F5D0 0013C1B0  38 BF 00 20 */	addi r5, r31, 0x20
/* 8013F5D4 0013C1B4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F5D8 0013C1B8  38 80 02 95 */	li r4, 0x295
/* 8013F5DC 0013C1BC  48 24 8C 45 */	bl __assert
lbl_8013F5E0:
/* 8013F5E0 0013C1C0  C0 02 A2 6C */	lfs f0, lbl_804D9C4C(r2)
/* 8013F5E4 0013C1C4  D0 1A 00 20 */	stfs f0, 0x20(r26)
/* 8013F5E8 0013C1C8  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 8013F5EC 0013C1CC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013F5F0 0013C1D0  40 82 00 FC */	bne lbl_8013F6EC
/* 8013F5F4 0013C1D4  28 1A 00 00 */	cmplwi r26, 0
/* 8013F5F8 0013C1D8  41 82 00 F4 */	beq lbl_8013F6EC
/* 8013F5FC 0013C1DC  40 82 00 14 */	bne lbl_8013F610
/* 8013F600 0013C1E0  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F604 0013C1E4  38 80 02 34 */	li r4, 0x234
/* 8013F608 0013C1E8  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F60C 0013C1EC  48 24 8C 15 */	bl __assert
lbl_8013F610:
/* 8013F610 0013C1F0  80 9A 00 14 */	lwz r4, 0x14(r26)
/* 8013F614 0013C1F4  38 60 00 00 */	li r3, 0
/* 8013F618 0013C1F8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013F61C 0013C1FC  40 82 00 10 */	bne lbl_8013F62C
/* 8013F620 0013C200  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013F624 0013C204  41 82 00 08 */	beq lbl_8013F62C
/* 8013F628 0013C208  38 60 00 01 */	li r3, 1
lbl_8013F62C:
/* 8013F62C 0013C20C  2C 03 00 00 */	cmpwi r3, 0
/* 8013F630 0013C210  40 82 00 BC */	bne lbl_8013F6EC
/* 8013F634 0013C214  7F 43 D3 78 */	mr r3, r26
/* 8013F638 0013C218  48 23 3C B1 */	bl HSD_JObjSetMtxDirtySub
/* 8013F63C 0013C21C  48 00 00 B0 */	b lbl_8013F6EC
lbl_8013F640:
/* 8013F640 0013C220  80 7C 05 E8 */	lwz r3, 0x5e8(r28)
/* 8013F644 0013C224  83 43 00 00 */	lwz r26, 0(r3)
/* 8013F648 0013C228  28 1A 00 00 */	cmplwi r26, 0
/* 8013F64C 0013C22C  40 82 00 14 */	bne lbl_8013F660
/* 8013F650 0013C230  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F654 0013C234  38 80 02 94 */	li r4, 0x294
/* 8013F658 0013C238  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F65C 0013C23C  48 24 8B C5 */	bl __assert
lbl_8013F660:
/* 8013F660 0013C240  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 8013F664 0013C244  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8013F668 0013C248  41 82 00 14 */	beq lbl_8013F67C
/* 8013F66C 0013C24C  38 BF 00 20 */	addi r5, r31, 0x20
/* 8013F670 0013C250  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F674 0013C254  38 80 02 95 */	li r4, 0x295
/* 8013F678 0013C258  48 24 8B A9 */	bl __assert
lbl_8013F67C:
/* 8013F67C 0013C25C  C0 02 A2 6C */	lfs f0, lbl_804D9C4C(r2)
/* 8013F680 0013C260  D0 1A 00 20 */	stfs f0, 0x20(r26)
/* 8013F684 0013C264  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 8013F688 0013C268  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013F68C 0013C26C  40 82 00 60 */	bne lbl_8013F6EC
/* 8013F690 0013C270  28 1A 00 00 */	cmplwi r26, 0
/* 8013F694 0013C274  41 82 00 58 */	beq lbl_8013F6EC
/* 8013F698 0013C278  40 82 00 14 */	bne lbl_8013F6AC
/* 8013F69C 0013C27C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F6A0 0013C280  38 80 02 34 */	li r4, 0x234
/* 8013F6A4 0013C284  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F6A8 0013C288  48 24 8B 79 */	bl __assert
lbl_8013F6AC:
/* 8013F6AC 0013C28C  80 9A 00 14 */	lwz r4, 0x14(r26)
/* 8013F6B0 0013C290  38 60 00 00 */	li r3, 0
/* 8013F6B4 0013C294  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013F6B8 0013C298  40 82 00 10 */	bne lbl_8013F6C8
/* 8013F6BC 0013C29C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013F6C0 0013C2A0  41 82 00 08 */	beq lbl_8013F6C8
/* 8013F6C4 0013C2A4  38 60 00 01 */	li r3, 1
lbl_8013F6C8:
/* 8013F6C8 0013C2A8  2C 03 00 00 */	cmpwi r3, 0
/* 8013F6CC 0013C2AC  40 82 00 20 */	bne lbl_8013F6EC
/* 8013F6D0 0013C2B0  7F 43 D3 78 */	mr r3, r26
/* 8013F6D4 0013C2B4  48 23 3C 15 */	bl HSD_JObjSetMtxDirtySub
/* 8013F6D8 0013C2B8  48 00 00 14 */	b lbl_8013F6EC
lbl_8013F6DC:
/* 8013F6DC 0013C2BC  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013F6E0 0013C2C0  38 7C 00 00 */	addi r3, r28, 0
/* 8013F6E4 0013C2C4  38 80 00 00 */	li r4, 0
/* 8013F6E8 0013C2C8  4B F3 64 09 */	bl func_80075AF0
lbl_8013F6EC:
/* 8013F6EC 0013C2CC  BB 41 00 48 */	lmw r26, 0x48(r1)
/* 8013F6F0 0013C2D0  80 01 00 74 */	lwz r0, 0x74(r1)
/* 8013F6F4 0013C2D4  CB E1 00 68 */	lfd f31, 0x68(r1)
/* 8013F6F8 0013C2D8  CB C1 00 60 */	lfd f30, 0x60(r1)
/* 8013F6FC 0013C2DC  38 21 00 70 */	addi r1, r1, 0x70
/* 8013F700 0013C2E0  7C 08 03 A6 */	mtlr r0
/* 8013F704 0013C2E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013F708()
{ // clang-format off
    nofralloc
/* 8013F708 0013C2E8  7C 08 02 A6 */	mflr r0
/* 8013F70C 0013C2EC  38 80 00 01 */	li r4, 1
/* 8013F710 0013C2F0  90 01 00 04 */	stw r0, 4(r1)
/* 8013F714 0013C2F4  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8013F718 0013C2F8  BF 61 00 34 */	stmw r27, 0x34(r1)
/* 8013F71C 0013C2FC  7C 7B 1B 78 */	mr r27, r3
/* 8013F720 0013C300  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8013F724 0013C304  83 85 02 D4 */	lwz r28, 0x2d4(r5)
/* 8013F728 0013C308  7C BD 2B 78 */	mr r29, r5
/* 8013F72C 0013C30C  4B FF E6 29 */	bl func_8013DD54
/* 8013F730 0013C310  83 DB 00 2C */	lwz r30, 0x2c(r27)
/* 8013F734 0013C314  83 FB 00 28 */	lwz r31, 0x28(r27)
/* 8013F738 0013C318  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8013F73C 0013C31C  2C 00 00 00 */	cmpwi r0, 0
/* 8013F740 0013C320  41 80 00 E4 */	blt lbl_8013F824
/* 8013F744 0013C324  2C 00 00 04 */	cmpwi r0, 4
/* 8013F748 0013C328  40 80 00 DC */	bge lbl_8013F824
/* 8013F74C 0013C32C  C0 1E 22 30 */	lfs f0, 0x2230(r30)
/* 8013F750 0013C330  3C 80 80 3D */	lis r4, lbl_803D05C8@ha
/* 8013F754 0013C334  54 05 10 3A */	slwi r5, r0, 2
/* 8013F758 0013C338  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8013F75C 0013C33C  38 04 05 C8 */	addi r0, r4, lbl_803D05C8@l
/* 8013F760 0013C340  7C 80 2A 14 */	add r4, r0, r5
/* 8013F764 0013C344  C0 3E 22 34 */	lfs f1, 0x2234(r30)
/* 8013F768 0013C348  3C 60 80 3D */	lis r3, lbl_803D05D8@ha
/* 8013F76C 0013C34C  C0 04 00 00 */	lfs f0, 0(r4)
/* 8013F770 0013C350  38 03 05 D8 */	addi r0, r3, lbl_803D05D8@l
/* 8013F774 0013C354  7C 60 2A 14 */	add r3, r0, r5
/* 8013F778 0013C358  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013F77C 0013C35C  28 1F 00 00 */	cmplwi r31, 0
/* 8013F780 0013C360  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8013F784 0013C364  C0 3E 22 38 */	lfs f1, 0x2238(r30)
/* 8013F788 0013C368  C0 03 00 00 */	lfs f0, 0(r3)
/* 8013F78C 0013C36C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013F790 0013C370  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8013F794 0013C374  40 82 00 14 */	bne lbl_8013F7A8
/* 8013F798 0013C378  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F79C 0013C37C  38 80 02 F8 */	li r4, 0x2f8
/* 8013F7A0 0013C380  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F7A4 0013C384  48 24 8A 7D */	bl __assert
lbl_8013F7A8:
/* 8013F7A8 0013C388  80 61 00 20 */	lwz r3, 0x20(r1)
/* 8013F7AC 0013C38C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013F7B0 0013C390  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013F7B4 0013C394  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013F7B8 0013C398  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8013F7BC 0013C39C  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013F7C0 0013C3A0  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013F7C4 0013C3A4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013F7C8 0013C3A8  40 82 00 4C */	bne lbl_8013F814
/* 8013F7CC 0013C3AC  28 1F 00 00 */	cmplwi r31, 0
/* 8013F7D0 0013C3B0  41 82 00 44 */	beq lbl_8013F814
/* 8013F7D4 0013C3B4  40 82 00 14 */	bne lbl_8013F7E8
/* 8013F7D8 0013C3B8  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F7DC 0013C3BC  38 80 02 34 */	li r4, 0x234
/* 8013F7E0 0013C3C0  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F7E4 0013C3C4  48 24 8A 3D */	bl __assert
lbl_8013F7E8:
/* 8013F7E8 0013C3C8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013F7EC 0013C3CC  38 60 00 00 */	li r3, 0
/* 8013F7F0 0013C3D0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013F7F4 0013C3D4  40 82 00 10 */	bne lbl_8013F804
/* 8013F7F8 0013C3D8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013F7FC 0013C3DC  41 82 00 08 */	beq lbl_8013F804
/* 8013F800 0013C3E0  38 60 00 01 */	li r3, 1
lbl_8013F804:
/* 8013F804 0013C3E4  2C 03 00 00 */	cmpwi r3, 0
/* 8013F808 0013C3E8  40 82 00 0C */	bne lbl_8013F814
/* 8013F80C 0013C3EC  7F E3 FB 78 */	mr r3, r31
/* 8013F810 0013C3F0  48 23 3A D9 */	bl HSD_JObjSetMtxDirtySub
lbl_8013F814:
/* 8013F814 0013C3F4  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8013F818 0013C3F8  38 03 00 01 */	addi r0, r3, 1
/* 8013F81C 0013C3FC  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8013F820 0013C400  48 00 00 A4 */	b lbl_8013F8C4
lbl_8013F824:
/* 8013F824 0013C404  28 1F 00 00 */	cmplwi r31, 0
/* 8013F828 0013C408  3B DE 22 30 */	addi r30, r30, 0x2230
/* 8013F82C 0013C40C  40 82 00 14 */	bne lbl_8013F840
/* 8013F830 0013C410  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F834 0013C414  38 80 02 F8 */	li r4, 0x2f8
/* 8013F838 0013C418  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F83C 0013C41C  48 24 89 E5 */	bl __assert
lbl_8013F840:
/* 8013F840 0013C420  28 1E 00 00 */	cmplwi r30, 0
/* 8013F844 0013C424  40 82 00 14 */	bne lbl_8013F858
/* 8013F848 0013C428  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F84C 0013C42C  38 80 02 F9 */	li r4, 0x2f9
/* 8013F850 0013C430  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013F854 0013C434  48 24 89 CD */	bl __assert
lbl_8013F858:
/* 8013F858 0013C438  80 7E 00 00 */	lwz r3, 0(r30)
/* 8013F85C 0013C43C  80 1E 00 04 */	lwz r0, 4(r30)
/* 8013F860 0013C440  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013F864 0013C444  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013F868 0013C448  80 1E 00 08 */	lwz r0, 8(r30)
/* 8013F86C 0013C44C  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013F870 0013C450  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013F874 0013C454  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013F878 0013C458  40 82 00 4C */	bne lbl_8013F8C4
/* 8013F87C 0013C45C  28 1F 00 00 */	cmplwi r31, 0
/* 8013F880 0013C460  41 82 00 44 */	beq lbl_8013F8C4
/* 8013F884 0013C464  40 82 00 14 */	bne lbl_8013F898
/* 8013F888 0013C468  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013F88C 0013C46C  38 80 02 34 */	li r4, 0x234
/* 8013F890 0013C470  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013F894 0013C474  48 24 89 8D */	bl __assert
lbl_8013F898:
/* 8013F898 0013C478  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013F89C 0013C47C  38 60 00 00 */	li r3, 0
/* 8013F8A0 0013C480  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013F8A4 0013C484  40 82 00 10 */	bne lbl_8013F8B4
/* 8013F8A8 0013C488  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013F8AC 0013C48C  41 82 00 08 */	beq lbl_8013F8B4
/* 8013F8B0 0013C490  38 60 00 01 */	li r3, 1
lbl_8013F8B4:
/* 8013F8B4 0013C494  2C 03 00 00 */	cmpwi r3, 0
/* 8013F8B8 0013C498  40 82 00 0C */	bne lbl_8013F8C4
/* 8013F8BC 0013C49C  7F E3 FB 78 */	mr r3, r31
/* 8013F8C0 0013C4A0  48 23 3A 29 */	bl HSD_JObjSetMtxDirtySub
lbl_8013F8C4:
/* 8013F8C4 0013C4A4  C8 42 A2 98 */	lfd f2, lbl_804D9C78(r2)
/* 8013F8C8 0013C4A8  C0 1C 00 6C */	lfs f0, 0x6c(r28)
/* 8013F8CC 0013C4AC  C0 3D 23 74 */	lfs f1, 0x2374(r29)
/* 8013F8D0 0013C4B0  FC 42 00 32 */	fmul f2, f2, f0
/* 8013F8D4 0013C4B4  C0 7C 00 BC */	lfs f3, 0xbc(r28)
/* 8013F8D8 0013C4B8  C0 1D 23 54 */	lfs f0, 0x2354(r29)
/* 8013F8DC 0013C4BC  FC 20 08 50 */	fneg f1, f1
/* 8013F8E0 0013C4C0  FC 22 00 72 */	fmul f1, f2, f1
/* 8013F8E4 0013C4C4  FC 20 08 18 */	frsp f1, f1
/* 8013F8E8 0013C4C8  EC 03 00 7A */	fmadds f0, f3, f1, f0
/* 8013F8EC 0013C4CC  D0 1D 23 54 */	stfs f0, 0x2354(r29)
/* 8013F8F0 0013C4D0  80 7B 00 2C */	lwz r3, 0x2c(r27)
/* 8013F8F4 0013C4D4  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013F8F8 0013C4D8  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013F8FC 0013C4DC  48 00 00 14 */	b lbl_8013F910
lbl_8013F900:
/* 8013F900 0013C4E0  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F904 0013C4E4  FC 21 10 2A */	fadd f1, f1, f2
/* 8013F908 0013C4E8  FC 20 08 18 */	frsp f1, f1
/* 8013F90C 0013C4EC  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013F910:
/* 8013F910 0013C4F0  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F914 0013C4F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013F918 0013C4F8  41 80 FF E8 */	blt lbl_8013F900
/* 8013F91C 0013C4FC  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013F920 0013C500  48 00 00 14 */	b lbl_8013F934
lbl_8013F924:
/* 8013F924 0013C504  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013F928 0013C508  FC 00 10 28 */	fsub f0, f0, f2
/* 8013F92C 0013C50C  FC 00 00 18 */	frsp f0, f0
/* 8013F930 0013C510  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013F934:
/* 8013F934 0013C514  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013F938 0013C518  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013F93C 0013C51C  41 81 FF E8 */	bgt lbl_8013F924
/* 8013F940 0013C520  38 80 00 03 */	li r4, 3
/* 8013F944 0013C524  4B F3 5F E9 */	bl func_8007592C
/* 8013F948 0013C528  80 7D 23 40 */	lwz r3, 0x2340(r29)
/* 8013F94C 0013C52C  38 03 FF FF */	addi r0, r3, -1
/* 8013F950 0013C530  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 8013F954 0013C534  80 1D 23 40 */	lwz r0, 0x2340(r29)
/* 8013F958 0013C538  2C 00 00 00 */	cmpwi r0, 0
/* 8013F95C 0013C53C  41 81 00 34 */	bgt lbl_8013F990
/* 8013F960 0013C540  38 00 00 00 */	li r0, 0
/* 8013F964 0013C544  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 8013F968 0013C548  3C 80 00 04 */	lis r4, 0x00040012@ha
/* 8013F96C 0013C54C  38 7B 00 00 */	addi r3, r27, 0
/* 8013F970 0013C550  C0 1D 23 74 */	lfs f0, 0x2374(r29)
/* 8013F974 0013C554  38 A4 00 12 */	addi r5, r4, 0x00040012@l
/* 8013F978 0013C558  38 80 00 00 */	li r4, 0
/* 8013F97C 0013C55C  FC 00 00 50 */	fneg f0, f0
/* 8013F980 0013C560  D0 1D 23 74 */	stfs f0, 0x2374(r29)
/* 8013F984 0013C564  C0 22 A2 68 */	lfs f1, lbl_804D9C48(r2)
/* 8013F988 0013C568  4B FF E0 9D */	bl func_8013DA24
/* 8013F98C 0013C56C  48 00 00 20 */	b lbl_8013F9AC
lbl_8013F990:
/* 8013F990 0013C570  80 BD 23 64 */	lwz r5, 0x2364(r29)
/* 8013F994 0013C574  38 7D 00 00 */	addi r3, r29, 0
/* 8013F998 0013C578  38 80 00 00 */	li r4, 0
/* 8013F99C 0013C57C  38 05 00 01 */	addi r0, r5, 1
/* 8013F9A0 0013C580  90 1D 23 64 */	stw r0, 0x2364(r29)
/* 8013F9A4 0013C584  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013F9A8 0013C588  4B F3 61 49 */	bl func_80075AF0
lbl_8013F9AC:
/* 8013F9AC 0013C58C  BB 61 00 34 */	lmw r27, 0x34(r1)
/* 8013F9B0 0013C590  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8013F9B4 0013C594  38 21 00 48 */	addi r1, r1, 0x48
/* 8013F9B8 0013C598  7C 08 03 A6 */	mtlr r0
/* 8013F9BC 0013C59C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013F9C0()
{ // clang-format off
    nofralloc
/* 8013F9C0 0013C5A0  7C 08 02 A6 */	mflr r0
/* 8013F9C4 0013C5A4  90 01 00 04 */	stw r0, 4(r1)
/* 8013F9C8 0013C5A8  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8013F9CC 0013C5AC  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 8013F9D0 0013C5B0  7C 7C 1B 78 */	mr r28, r3
/* 8013F9D4 0013C5B4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8013F9D8 0013C5B8  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013F9DC 0013C5BC  83 A3 02 D4 */	lwz r29, 0x2d4(r3)
/* 8013F9E0 0013C5C0  D0 03 23 60 */	stfs f0, 0x2360(r3)
/* 8013F9E4 0013C5C4  83 DC 00 2C */	lwz r30, 0x2c(r28)
/* 8013F9E8 0013C5C8  83 FC 00 28 */	lwz r31, 0x28(r28)
/* 8013F9EC 0013C5CC  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8013F9F0 0013C5D0  2C 00 00 00 */	cmpwi r0, 0
/* 8013F9F4 0013C5D4  41 80 00 E4 */	blt lbl_8013FAD8
/* 8013F9F8 0013C5D8  2C 00 00 04 */	cmpwi r0, 4
/* 8013F9FC 0013C5DC  40 80 00 DC */	bge lbl_8013FAD8
/* 8013FA00 0013C5E0  C0 1E 22 30 */	lfs f0, 0x2230(r30)
/* 8013FA04 0013C5E4  3C 80 80 3D */	lis r4, lbl_803D05C8@ha
/* 8013FA08 0013C5E8  54 05 10 3A */	slwi r5, r0, 2
/* 8013FA0C 0013C5EC  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8013FA10 0013C5F0  38 04 05 C8 */	addi r0, r4, lbl_803D05C8@l
/* 8013FA14 0013C5F4  7C 80 2A 14 */	add r4, r0, r5
/* 8013FA18 0013C5F8  C0 3E 22 34 */	lfs f1, 0x2234(r30)
/* 8013FA1C 0013C5FC  3C 60 80 3D */	lis r3, lbl_803D05D8@ha
/* 8013FA20 0013C600  C0 04 00 00 */	lfs f0, 0(r4)
/* 8013FA24 0013C604  38 03 05 D8 */	addi r0, r3, lbl_803D05D8@l
/* 8013FA28 0013C608  7C 60 2A 14 */	add r3, r0, r5
/* 8013FA2C 0013C60C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013FA30 0013C610  28 1F 00 00 */	cmplwi r31, 0
/* 8013FA34 0013C614  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8013FA38 0013C618  C0 3E 22 38 */	lfs f1, 0x2238(r30)
/* 8013FA3C 0013C61C  C0 03 00 00 */	lfs f0, 0(r3)
/* 8013FA40 0013C620  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013FA44 0013C624  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 8013FA48 0013C628  40 82 00 14 */	bne lbl_8013FA5C
/* 8013FA4C 0013C62C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FA50 0013C630  38 80 02 F8 */	li r4, 0x2f8
/* 8013FA54 0013C634  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FA58 0013C638  48 24 87 C9 */	bl __assert
lbl_8013FA5C:
/* 8013FA5C 0013C63C  80 61 00 24 */	lwz r3, 0x24(r1)
/* 8013FA60 0013C640  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8013FA64 0013C644  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013FA68 0013C648  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013FA6C 0013C64C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013FA70 0013C650  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013FA74 0013C654  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013FA78 0013C658  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013FA7C 0013C65C  40 82 00 4C */	bne lbl_8013FAC8
/* 8013FA80 0013C660  28 1F 00 00 */	cmplwi r31, 0
/* 8013FA84 0013C664  41 82 00 44 */	beq lbl_8013FAC8
/* 8013FA88 0013C668  40 82 00 14 */	bne lbl_8013FA9C
/* 8013FA8C 0013C66C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FA90 0013C670  38 80 02 34 */	li r4, 0x234
/* 8013FA94 0013C674  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FA98 0013C678  48 24 87 89 */	bl __assert
lbl_8013FA9C:
/* 8013FA9C 0013C67C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013FAA0 0013C680  38 60 00 00 */	li r3, 0
/* 8013FAA4 0013C684  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013FAA8 0013C688  40 82 00 10 */	bne lbl_8013FAB8
/* 8013FAAC 0013C68C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013FAB0 0013C690  41 82 00 08 */	beq lbl_8013FAB8
/* 8013FAB4 0013C694  38 60 00 01 */	li r3, 1
lbl_8013FAB8:
/* 8013FAB8 0013C698  2C 03 00 00 */	cmpwi r3, 0
/* 8013FABC 0013C69C  40 82 00 0C */	bne lbl_8013FAC8
/* 8013FAC0 0013C6A0  7F E3 FB 78 */	mr r3, r31
/* 8013FAC4 0013C6A4  48 23 38 25 */	bl HSD_JObjSetMtxDirtySub
lbl_8013FAC8:
/* 8013FAC8 0013C6A8  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8013FACC 0013C6AC  38 03 00 01 */	addi r0, r3, 1
/* 8013FAD0 0013C6B0  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8013FAD4 0013C6B4  48 00 00 A4 */	b lbl_8013FB78
lbl_8013FAD8:
/* 8013FAD8 0013C6B8  28 1F 00 00 */	cmplwi r31, 0
/* 8013FADC 0013C6BC  3B DE 22 30 */	addi r30, r30, 0x2230
/* 8013FAE0 0013C6C0  40 82 00 14 */	bne lbl_8013FAF4
/* 8013FAE4 0013C6C4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FAE8 0013C6C8  38 80 02 F8 */	li r4, 0x2f8
/* 8013FAEC 0013C6CC  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FAF0 0013C6D0  48 24 87 31 */	bl __assert
lbl_8013FAF4:
/* 8013FAF4 0013C6D4  28 1E 00 00 */	cmplwi r30, 0
/* 8013FAF8 0013C6D8  40 82 00 14 */	bne lbl_8013FB0C
/* 8013FAFC 0013C6DC  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FB00 0013C6E0  38 80 02 F9 */	li r4, 0x2f9
/* 8013FB04 0013C6E4  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013FB08 0013C6E8  48 24 87 19 */	bl __assert
lbl_8013FB0C:
/* 8013FB0C 0013C6EC  80 7E 00 00 */	lwz r3, 0(r30)
/* 8013FB10 0013C6F0  80 1E 00 04 */	lwz r0, 4(r30)
/* 8013FB14 0013C6F4  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013FB18 0013C6F8  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013FB1C 0013C6FC  80 1E 00 08 */	lwz r0, 8(r30)
/* 8013FB20 0013C700  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013FB24 0013C704  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013FB28 0013C708  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013FB2C 0013C70C  40 82 00 4C */	bne lbl_8013FB78
/* 8013FB30 0013C710  28 1F 00 00 */	cmplwi r31, 0
/* 8013FB34 0013C714  41 82 00 44 */	beq lbl_8013FB78
/* 8013FB38 0013C718  40 82 00 14 */	bne lbl_8013FB4C
/* 8013FB3C 0013C71C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FB40 0013C720  38 80 02 34 */	li r4, 0x234
/* 8013FB44 0013C724  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FB48 0013C728  48 24 86 D9 */	bl __assert
lbl_8013FB4C:
/* 8013FB4C 0013C72C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013FB50 0013C730  38 60 00 00 */	li r3, 0
/* 8013FB54 0013C734  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013FB58 0013C738  40 82 00 10 */	bne lbl_8013FB68
/* 8013FB5C 0013C73C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013FB60 0013C740  41 82 00 08 */	beq lbl_8013FB68
/* 8013FB64 0013C744  38 60 00 01 */	li r3, 1
lbl_8013FB68:
/* 8013FB68 0013C748  2C 03 00 00 */	cmpwi r3, 0
/* 8013FB6C 0013C74C  40 82 00 0C */	bne lbl_8013FB78
/* 8013FB70 0013C750  7F E3 FB 78 */	mr r3, r31
/* 8013FB74 0013C754  48 23 37 75 */	bl HSD_JObjSetMtxDirtySub
lbl_8013FB78:
/* 8013FB78 0013C758  7F 83 E3 78 */	mr r3, r28
/* 8013FB7C 0013C75C  4B F2 F6 BD */	bl ftAnim_IsFramesRemaining
/* 8013FB80 0013C760  2C 03 00 00 */	cmpwi r3, 0
/* 8013FB84 0013C764  40 82 01 14 */	bne lbl_8013FC98
/* 8013FB88 0013C768  83 DC 00 28 */	lwz r30, 0x28(r28)
/* 8013FB8C 0013C76C  83 7C 00 2C */	lwz r27, 0x2c(r28)
/* 8013FB90 0013C770  28 1E 00 00 */	cmplwi r30, 0
/* 8013FB94 0013C774  3B FB 22 30 */	addi r31, r27, 0x2230
/* 8013FB98 0013C778  40 82 00 14 */	bne lbl_8013FBAC
/* 8013FB9C 0013C77C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FBA0 0013C780  38 80 02 F8 */	li r4, 0x2f8
/* 8013FBA4 0013C784  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FBA8 0013C788  48 24 86 79 */	bl __assert
lbl_8013FBAC:
/* 8013FBAC 0013C78C  28 1F 00 00 */	cmplwi r31, 0
/* 8013FBB0 0013C790  40 82 00 14 */	bne lbl_8013FBC4
/* 8013FBB4 0013C794  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FBB8 0013C798  38 80 02 F9 */	li r4, 0x2f9
/* 8013FBBC 0013C79C  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013FBC0 0013C7A0  48 24 86 61 */	bl __assert
lbl_8013FBC4:
/* 8013FBC4 0013C7A4  80 7F 00 00 */	lwz r3, 0(r31)
/* 8013FBC8 0013C7A8  80 1F 00 04 */	lwz r0, 4(r31)
/* 8013FBCC 0013C7AC  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 8013FBD0 0013C7B0  90 1E 00 30 */	stw r0, 0x30(r30)
/* 8013FBD4 0013C7B4  80 1F 00 08 */	lwz r0, 8(r31)
/* 8013FBD8 0013C7B8  90 1E 00 34 */	stw r0, 0x34(r30)
/* 8013FBDC 0013C7BC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8013FBE0 0013C7C0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013FBE4 0013C7C4  40 82 00 4C */	bne lbl_8013FC30
/* 8013FBE8 0013C7C8  28 1E 00 00 */	cmplwi r30, 0
/* 8013FBEC 0013C7CC  41 82 00 44 */	beq lbl_8013FC30
/* 8013FBF0 0013C7D0  40 82 00 14 */	bne lbl_8013FC04
/* 8013FBF4 0013C7D4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FBF8 0013C7D8  38 80 02 34 */	li r4, 0x234
/* 8013FBFC 0013C7DC  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FC00 0013C7E0  48 24 86 21 */	bl __assert
lbl_8013FC04:
/* 8013FC04 0013C7E4  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8013FC08 0013C7E8  38 60 00 00 */	li r3, 0
/* 8013FC0C 0013C7EC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013FC10 0013C7F0  40 82 00 10 */	bne lbl_8013FC20
/* 8013FC14 0013C7F4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013FC18 0013C7F8  41 82 00 08 */	beq lbl_8013FC20
/* 8013FC1C 0013C7FC  38 60 00 01 */	li r3, 1
lbl_8013FC20:
/* 8013FC20 0013C800  2C 03 00 00 */	cmpwi r3, 0
/* 8013FC24 0013C804  40 82 00 0C */	bne lbl_8013FC30
/* 8013FC28 0013C808  7F C3 F3 78 */	mr r3, r30
/* 8013FC2C 0013C80C  48 23 36 BD */	bl HSD_JObjSetMtxDirtySub
lbl_8013FC30:
/* 8013FC30 0013C810  C8 22 A2 60 */	lfd f1, lbl_804D9C40(r2)
/* 8013FC34 0013C814  7F 63 DB 78 */	mr r3, r27
/* 8013FC38 0013C818  C0 1B 00 2C */	lfs f0, 0x2c(r27)
/* 8013FC3C 0013C81C  38 80 00 00 */	li r4, 0
/* 8013FC40 0013C820  FC 21 00 32 */	fmul f1, f1, f0
/* 8013FC44 0013C824  FC 20 08 18 */	frsp f1, f1
/* 8013FC48 0013C828  4B F3 5E A9 */	bl func_80075AF0
/* 8013FC4C 0013C82C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013FC50 0013C830  C0 3B 23 60 */	lfs f1, 0x2360(r27)
/* 8013FC54 0013C834  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8013FC58 0013C838  41 82 00 08 */	beq lbl_8013FC60
/* 8013FC5C 0013C83C  D0 3B 00 2C */	stfs f1, 0x2c(r27)
lbl_8013FC60:
/* 8013FC60 0013C840  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013FC64 0013C844  D0 1B 23 60 */	stfs f0, 0x2360(r27)
/* 8013FC68 0013C848  C0 5D 00 D8 */	lfs f2, 0xd8(r29)
/* 8013FC6C 0013C84C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8013FC70 0013C850  40 82 00 10 */	bne lbl_8013FC80
/* 8013FC74 0013C854  7F 83 E3 78 */	mr r3, r28
/* 8013FC78 0013C858  4B F8 CA B9 */	bl func_800CC730
/* 8013FC7C 0013C85C  48 00 00 1C */	b lbl_8013FC98
lbl_8013FC80:
/* 8013FC80 0013C860  C0 22 A2 70 */	lfs f1, lbl_804D9C50(r2)
/* 8013FC84 0013C864  38 7C 00 00 */	addi r3, r28, 0
/* 8013FC88 0013C868  38 80 00 01 */	li r4, 1
/* 8013FC8C 0013C86C  38 A0 00 00 */	li r5, 0
/* 8013FC90 0013C870  38 C0 00 01 */	li r6, 1
/* 8013FC94 0013C874  4B F5 6C 6D */	bl func_80096900
lbl_8013FC98:
/* 8013FC98 0013C878  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 8013FC9C 0013C87C  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8013FCA0 0013C880  38 21 00 58 */	addi r1, r1, 0x58
/* 8013FCA4 0013C884  7C 08 03 A6 */	mtlr r0
/* 8013FCA8 0013C888  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8013FCAC()
{ // clang-format off
    nofralloc
/* 8013FCAC 0013C88C  7C 08 02 A6 */	mflr r0
/* 8013FCB0 0013C890  90 01 00 04 */	stw r0, 4(r1)
/* 8013FCB4 0013C894  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8013FCB8 0013C898  BF 61 00 3C */	stmw r27, 0x3c(r1)
/* 8013FCBC 0013C89C  7C 7C 1B 78 */	mr r28, r3
/* 8013FCC0 0013C8A0  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8013FCC4 0013C8A4  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 8013FCC8 0013C8A8  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8013FCCC 0013C8AC  83 BE 02 D4 */	lwz r29, 0x2d4(r30)
/* 8013FCD0 0013C8B0  2C 00 00 00 */	cmpwi r0, 0
/* 8013FCD4 0013C8B4  41 80 00 E4 */	blt lbl_8013FDB8
/* 8013FCD8 0013C8B8  2C 00 00 04 */	cmpwi r0, 4
/* 8013FCDC 0013C8BC  40 80 00 DC */	bge lbl_8013FDB8
/* 8013FCE0 0013C8C0  C0 1E 22 30 */	lfs f0, 0x2230(r30)
/* 8013FCE4 0013C8C4  3C 80 80 3D */	lis r4, lbl_803D05C8@ha
/* 8013FCE8 0013C8C8  54 05 10 3A */	slwi r5, r0, 2
/* 8013FCEC 0013C8CC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8013FCF0 0013C8D0  38 04 05 C8 */	addi r0, r4, lbl_803D05C8@l
/* 8013FCF4 0013C8D4  7C 80 2A 14 */	add r4, r0, r5
/* 8013FCF8 0013C8D8  C0 3E 22 34 */	lfs f1, 0x2234(r30)
/* 8013FCFC 0013C8DC  3C 60 80 3D */	lis r3, lbl_803D05D8@ha
/* 8013FD00 0013C8E0  C0 04 00 00 */	lfs f0, 0(r4)
/* 8013FD04 0013C8E4  38 03 05 D8 */	addi r0, r3, lbl_803D05D8@l
/* 8013FD08 0013C8E8  7C 60 2A 14 */	add r3, r0, r5
/* 8013FD0C 0013C8EC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013FD10 0013C8F0  28 1F 00 00 */	cmplwi r31, 0
/* 8013FD14 0013C8F4  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8013FD18 0013C8F8  C0 3E 22 38 */	lfs f1, 0x2238(r30)
/* 8013FD1C 0013C8FC  C0 03 00 00 */	lfs f0, 0(r3)
/* 8013FD20 0013C900  EC 01 00 32 */	fmuls f0, f1, f0
/* 8013FD24 0013C904  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8013FD28 0013C908  40 82 00 14 */	bne lbl_8013FD3C
/* 8013FD2C 0013C90C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FD30 0013C910  38 80 02 F8 */	li r4, 0x2f8
/* 8013FD34 0013C914  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FD38 0013C918  48 24 84 E9 */	bl __assert
lbl_8013FD3C:
/* 8013FD3C 0013C91C  80 61 00 20 */	lwz r3, 0x20(r1)
/* 8013FD40 0013C920  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8013FD44 0013C924  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013FD48 0013C928  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013FD4C 0013C92C  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8013FD50 0013C930  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013FD54 0013C934  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013FD58 0013C938  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013FD5C 0013C93C  40 82 00 4C */	bne lbl_8013FDA8
/* 8013FD60 0013C940  28 1F 00 00 */	cmplwi r31, 0
/* 8013FD64 0013C944  41 82 00 44 */	beq lbl_8013FDA8
/* 8013FD68 0013C948  40 82 00 14 */	bne lbl_8013FD7C
/* 8013FD6C 0013C94C  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FD70 0013C950  38 80 02 34 */	li r4, 0x234
/* 8013FD74 0013C954  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FD78 0013C958  48 24 84 A9 */	bl __assert
lbl_8013FD7C:
/* 8013FD7C 0013C95C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013FD80 0013C960  38 60 00 00 */	li r3, 0
/* 8013FD84 0013C964  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013FD88 0013C968  40 82 00 10 */	bne lbl_8013FD98
/* 8013FD8C 0013C96C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013FD90 0013C970  41 82 00 08 */	beq lbl_8013FD98
/* 8013FD94 0013C974  38 60 00 01 */	li r3, 1
lbl_8013FD98:
/* 8013FD98 0013C978  2C 03 00 00 */	cmpwi r3, 0
/* 8013FD9C 0013C97C  40 82 00 0C */	bne lbl_8013FDA8
/* 8013FDA0 0013C980  7F E3 FB 78 */	mr r3, r31
/* 8013FDA4 0013C984  48 23 35 45 */	bl HSD_JObjSetMtxDirtySub
lbl_8013FDA8:
/* 8013FDA8 0013C988  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8013FDAC 0013C98C  38 03 00 01 */	addi r0, r3, 1
/* 8013FDB0 0013C990  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8013FDB4 0013C994  48 00 00 A4 */	b lbl_8013FE58
lbl_8013FDB8:
/* 8013FDB8 0013C998  28 1F 00 00 */	cmplwi r31, 0
/* 8013FDBC 0013C99C  3B 7E 22 30 */	addi r27, r30, 0x2230
/* 8013FDC0 0013C9A0  40 82 00 14 */	bne lbl_8013FDD4
/* 8013FDC4 0013C9A4  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FDC8 0013C9A8  38 80 02 F8 */	li r4, 0x2f8
/* 8013FDCC 0013C9AC  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FDD0 0013C9B0  48 24 84 51 */	bl __assert
lbl_8013FDD4:
/* 8013FDD4 0013C9B4  28 1B 00 00 */	cmplwi r27, 0
/* 8013FDD8 0013C9B8  40 82 00 14 */	bne lbl_8013FDEC
/* 8013FDDC 0013C9BC  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FDE0 0013C9C0  38 80 02 F9 */	li r4, 0x2f9
/* 8013FDE4 0013C9C4  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8
/* 8013FDE8 0013C9C8  48 24 84 39 */	bl __assert
lbl_8013FDEC:
/* 8013FDEC 0013C9CC  80 7B 00 00 */	lwz r3, 0(r27)
/* 8013FDF0 0013C9D0  80 1B 00 04 */	lwz r0, 4(r27)
/* 8013FDF4 0013C9D4  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8013FDF8 0013C9D8  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8013FDFC 0013C9DC  80 1B 00 08 */	lwz r0, 8(r27)
/* 8013FE00 0013C9E0  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8013FE04 0013C9E4  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8013FE08 0013C9E8  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8013FE0C 0013C9EC  40 82 00 4C */	bne lbl_8013FE58
/* 8013FE10 0013C9F0  28 1F 00 00 */	cmplwi r31, 0
/* 8013FE14 0013C9F4  41 82 00 44 */	beq lbl_8013FE58
/* 8013FE18 0013C9F8  40 82 00 14 */	bne lbl_8013FE2C
/* 8013FE1C 0013C9FC  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98
/* 8013FE20 0013CA00  38 80 02 34 */	li r4, 0x234
/* 8013FE24 0013CA04  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0
/* 8013FE28 0013CA08  48 24 83 F9 */	bl __assert
lbl_8013FE2C:
/* 8013FE2C 0013CA0C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8013FE30 0013CA10  38 60 00 00 */	li r3, 0
/* 8013FE34 0013CA14  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8013FE38 0013CA18  40 82 00 10 */	bne lbl_8013FE48
/* 8013FE3C 0013CA1C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8013FE40 0013CA20  41 82 00 08 */	beq lbl_8013FE48
/* 8013FE44 0013CA24  38 60 00 01 */	li r3, 1
lbl_8013FE48:
/* 8013FE48 0013CA28  2C 03 00 00 */	cmpwi r3, 0
/* 8013FE4C 0013CA2C  40 82 00 0C */	bne lbl_8013FE58
/* 8013FE50 0013CA30  7F E3 FB 78 */	mr r3, r31
/* 8013FE54 0013CA34  48 23 34 95 */	bl HSD_JObjSetMtxDirtySub
lbl_8013FE58:
/* 8013FE58 0013CA38  C8 42 A2 98 */	lfd f2, lbl_804D9C78(r2)
/* 8013FE5C 0013CA3C  C0 1D 00 6C */	lfs f0, 0x6c(r29)
/* 8013FE60 0013CA40  C0 3E 23 74 */	lfs f1, 0x2374(r30)
/* 8013FE64 0013CA44  FC 42 00 32 */	fmul f2, f2, f0
/* 8013FE68 0013CA48  C0 7D 00 BC */	lfs f3, 0xbc(r29)
/* 8013FE6C 0013CA4C  C0 1E 23 54 */	lfs f0, 0x2354(r30)
/* 8013FE70 0013CA50  FC 20 08 50 */	fneg f1, f1
/* 8013FE74 0013CA54  FC 22 00 72 */	fmul f1, f2, f1
/* 8013FE78 0013CA58  FC 20 08 18 */	frsp f1, f1
/* 8013FE7C 0013CA5C  EC 03 00 7A */	fmadds f0, f3, f1, f0
/* 8013FE80 0013CA60  D0 1E 23 54 */	stfs f0, 0x2354(r30)
/* 8013FE84 0013CA64  80 7C 00 2C */	lwz r3, 0x2c(r28)
/* 8013FE88 0013CA68  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013FE8C 0013CA6C  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013FE90 0013CA70  48 00 00 14 */	b lbl_8013FEA4
lbl_8013FE94:
/* 8013FE94 0013CA74  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013FE98 0013CA78  FC 21 10 2A */	fadd f1, f1, f2
/* 8013FE9C 0013CA7C  FC 20 08 18 */	frsp f1, f1
/* 8013FEA0 0013CA80  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013FEA4:
/* 8013FEA4 0013CA84  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013FEA8 0013CA88  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8013FEAC 0013CA8C  41 80 FF E8 */	blt lbl_8013FE94
/* 8013FEB0 0013CA90  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013FEB4 0013CA94  48 00 00 14 */	b lbl_8013FEC8
lbl_8013FEB8:
/* 8013FEB8 0013CA98  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 8013FEBC 0013CA9C  FC 00 10 28 */	fsub f0, f0, f2
/* 8013FEC0 0013CAA0  FC 00 00 18 */	frsp f0, f0
/* 8013FEC4 0013CAA4  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8013FEC8:
/* 8013FEC8 0013CAA8  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013FECC 0013CAAC  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 8013FED0 0013CAB0  41 81 FF E8 */	bgt lbl_8013FEB8
/* 8013FED4 0013CAB4  38 80 00 03 */	li r4, 3
/* 8013FED8 0013CAB8  4B F3 5A 55 */	bl func_8007592C
/* 8013FEDC 0013CABC  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013FEE0 0013CAC0  38 7E 00 00 */	addi r3, r30, 0
/* 8013FEE4 0013CAC4  38 80 00 00 */	li r4, 0
/* 8013FEE8 0013CAC8  4B F3 5C 09 */	bl func_80075AF0
/* 8013FEEC 0013CACC  BB 61 00 3C */	lmw r27, 0x3c(r1)
/* 8013FEF0 0013CAD0  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8013FEF4 0013CAD4  38 21 00 50 */	addi r1, r1, 0x50
/* 8013FEF8 0013CAD8  7C 08 03 A6 */	mtlr r0
/* 8013FEFC 0013CADC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void lbl_8013FF00(void)
{
    return;
}

#pragma push
asm unk_t lbl_8013FF04()
{ // clang-format off
    nofralloc
/* 8013FF04 0013CAE4  7C 08 02 A6 */	mflr r0
/* 8013FF08 0013CAE8  90 01 00 04 */	stw r0, 4(r1)
/* 8013FF0C 0013CAEC  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8013FF10 0013CAF0  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8013FF14 0013CAF4  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8013FF18 0013CAF8  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8013FF1C 0013CAFC  7C 7D 1B 78 */	mr r29, r3
/* 8013FF20 0013CB00  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013FF24 0013CB04  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8013FF28 0013CB08  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8013FF2C 0013CB0C  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 8013FF30 0013CB10  40 82 01 18 */	bne lbl_80140048
/* 8013FF34 0013CB14  C0 42 A2 68 */	lfs f2, lbl_804D9C48(r2)
/* 8013FF38 0013CB18  3C 80 00 04 */	lis r4, 0x00041092@ha
/* 8013FF3C 0013CB1C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013FF40 0013CB20  7F A3 EB 78 */	mr r3, r29
/* 8013FF44 0013CB24  FC 60 10 90 */	fmr f3, f2
/* 8013FF48 0013CB28  38 A4 10 92 */	addi r5, r4, 0x00041092@l
/* 8013FF4C 0013CB2C  38 80 01 5E */	li r4, 0x15e
/* 8013FF50 0013CB30  38 C0 00 00 */	li r6, 0
/* 8013FF54 0013CB34  4B F2 94 59 */	bl Fighter_ActionStateChange_800693AC
/* 8013FF58 0013CB38  3C 60 80 14 */	lis r3, lbl_8013D658@ha
/* 8013FF5C 0013CB3C  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 8013FF60 0013CB40  38 03 D6 58 */	addi r0, r3, lbl_8013D658@l
/* 8013FF64 0013CB44  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 8013FF68 0013CB48  3C 80 80 14 */	lis r4, lbl_8013D764@ha
/* 8013FF6C 0013CB4C  3C 60 80 14 */	lis r3, lbl_8014222C@ha
/* 8013FF70 0013CB50  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 8013FF74 0013CB54  38 84 D7 64 */	addi r4, r4, lbl_8013D764@l
/* 8013FF78 0013CB58  38 03 22 2C */	addi r0, r3, lbl_8014222C@l
/* 8013FF7C 0013CB5C  90 85 21 C0 */	stw r4, 0x21c0(r5)
/* 8013FF80 0013CB60  7F A3 EB 78 */	mr r3, r29
/* 8013FF84 0013CB64  90 05 21 F8 */	stw r0, 0x21f8(r5)
/* 8013FF88 0013CB68  4B F2 EC 1D */	bl func_8006EBA4
/* 8013FF8C 0013CB6C  80 9F 23 6C */	lwz r4, 0x236c(r31)
/* 8013FF90 0013CB70  3C 00 43 30 */	lis r0, 0x4330
/* 8013FF94 0013CB74  C8 42 A2 90 */	lfd f2, lbl_804D9C70(r2)
/* 8013FF98 0013CB78  38 7F 00 00 */	addi r3, r31, 0
/* 8013FF9C 0013CB7C  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 8013FFA0 0013CB80  90 81 00 24 */	stw r4, 0x24(r1)
/* 8013FFA4 0013CB84  38 80 00 00 */	li r4, 0
/* 8013FFA8 0013CB88  C0 1E 00 A0 */	lfs f0, 0xa0(r30)
/* 8013FFAC 0013CB8C  90 01 00 20 */	stw r0, 0x20(r1)
/* 8013FFB0 0013CB90  C0 7E 00 C0 */	lfs f3, 0xc0(r30)
/* 8013FFB4 0013CB94  C8 21 00 20 */	lfd f1, 0x20(r1)
/* 8013FFB8 0013CB98  C0 9F 23 74 */	lfs f4, 0x2374(r31)
/* 8013FFBC 0013CB9C  EC 21 10 28 */	fsubs f1, f1, f2
/* 8013FFC0 0013CBA0  EC 01 00 28 */	fsubs f0, f1, f0
/* 8013FFC4 0013CBA4  EC 03 00 32 */	fmuls f0, f3, f0
/* 8013FFC8 0013CBA8  EC 04 00 32 */	fmuls f0, f4, f0
/* 8013FFCC 0013CBAC  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8013FFD0 0013CBB0  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 8013FFD4 0013CBB4  4B F3 5B 1D */	bl func_80075AF0
/* 8013FFD8 0013CBB8  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8013FFDC 0013CBBC  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 8013FFE0 0013CBC0  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 8013FFE4 0013CBC4  48 00 00 14 */	b lbl_8013FFF8
lbl_8013FFE8:
/* 8013FFE8 0013CBC8  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013FFEC 0013CBCC  FC 21 10 2A */	fadd f1, f1, f2
/* 8013FFF0 0013CBD0  FC 20 08 18 */	frsp f1, f1
/* 8013FFF4 0013CBD4  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_8013FFF8:
/* 8013FFF8 0013CBD8  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8013FFFC 0013CBDC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80140000 0013CBE0  41 80 FF E8 */	blt lbl_8013FFE8
/* 80140004 0013CBE4  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 80140008 0013CBE8  48 00 00 14 */	b lbl_8014001C
lbl_8014000C:
/* 8014000C 0013CBEC  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 80140010 0013CBF0  FC 00 10 28 */	fsub f0, f0, f2
/* 80140014 0013CBF4  FC 00 00 18 */	frsp f0, f0
/* 80140018 0013CBF8  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8014001C:
/* 8014001C 0013CBFC  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 80140020 0013CC00  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 80140024 0013CC04  41 81 FF E8 */	bgt lbl_8014000C
/* 80140028 0013CC08  38 80 00 03 */	li r4, 3
/* 8014002C 0013CC0C  4B F3 59 01 */	bl func_8007592C
/* 80140030 0013CC10  3C 80 00 04 */	lis r4, 0x0003D0D9@ha
/* 80140034 0013CC14  38 7F 00 00 */	addi r3, r31, 0
/* 80140038 0013CC18  38 84 D0 D9 */	addi r4, r4, 0x0003D0D9@l
/* 8014003C 0013CC1C  38 A0 00 7F */	li r5, 0x7f
/* 80140040 0013CC20  38 C0 00 40 */	li r6, 0x40
/* 80140044 0013CC24  4B F4 81 05 */	bl func_80088148
lbl_80140048:
/* 80140048 0013CC28  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8014004C 0013CC2C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80140050 0013CC30  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80140054 0013CC34  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80140058 0013CC38  38 21 00 38 */	addi r1, r1, 0x38
/* 8014005C 0013CC3C  7C 08 03 A6 */	mtlr r0
/* 80140060 0013CC40  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_80140064()
{ // clang-format off
    nofralloc
/* 80140064 0013CC44  7C 08 02 A6 */	mflr r0
/* 80140068 0013CC48  90 01 00 04 */	stw r0, 4(r1)
/* 8014006C 0013CC4C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80140070 0013CC50  93 E1 00 34 */	stw r31, 0x34(r1)
/* 80140074 0013CC54  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80140078 0013CC58  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8014007C 0013CC5C  7C 7D 1B 78 */	mr r29, r3
/* 80140080 0013CC60  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80140084 0013CC64  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 80140088 0013CC68  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8014008C 0013CC6C  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 80140090 0013CC70  40 82 01 18 */	bne lbl_801401A8
/* 80140094 0013CC74  C0 42 A2 68 */	lfs f2, lbl_804D9C48(r2)
/* 80140098 0013CC78  3C 80 00 04 */	lis r4, 0x00041092@ha
/* 8014009C 0013CC7C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 801400A0 0013CC80  7F A3 EB 78 */	mr r3, r29
/* 801400A4 0013CC84  FC 60 10 90 */	fmr f3, f2
/* 801400A8 0013CC88  38 A4 10 92 */	addi r5, r4, 0x00041092@l
/* 801400AC 0013CC8C  38 80 01 5E */	li r4, 0x15e
/* 801400B0 0013CC90  38 C0 00 00 */	li r6, 0
/* 801400B4 0013CC94  4B F2 92 F9 */	bl Fighter_ActionStateChange_800693AC
/* 801400B8 0013CC98  3C 60 80 14 */	lis r3, lbl_8013D658@ha
/* 801400BC 0013CC9C  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 801400C0 0013CCA0  38 03 D6 58 */	addi r0, r3, lbl_8013D658@l
/* 801400C4 0013CCA4  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 801400C8 0013CCA8  3C 80 80 14 */	lis r4, lbl_8013D764@ha
/* 801400CC 0013CCAC  3C 60 80 14 */	lis r3, lbl_8014222C@ha
/* 801400D0 0013CCB0  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 801400D4 0013CCB4  38 84 D7 64 */	addi r4, r4, lbl_8013D764@l
/* 801400D8 0013CCB8  38 03 22 2C */	addi r0, r3, lbl_8014222C@l
/* 801400DC 0013CCBC  90 85 21 C0 */	stw r4, 0x21c0(r5)
/* 801400E0 0013CCC0  7F A3 EB 78 */	mr r3, r29
/* 801400E4 0013CCC4  90 05 21 F8 */	stw r0, 0x21f8(r5)
/* 801400E8 0013CCC8  4B F2 EA BD */	bl func_8006EBA4
/* 801400EC 0013CCCC  80 9F 23 6C */	lwz r4, 0x236c(r31)
/* 801400F0 0013CCD0  3C 00 43 30 */	lis r0, 0x4330
/* 801400F4 0013CCD4  C8 42 A2 90 */	lfd f2, lbl_804D9C70(r2)
/* 801400F8 0013CCD8  38 7F 00 00 */	addi r3, r31, 0
/* 801400FC 0013CCDC  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 80140100 0013CCE0  90 81 00 24 */	stw r4, 0x24(r1)
/* 80140104 0013CCE4  38 80 00 00 */	li r4, 0
/* 80140108 0013CCE8  C0 1E 00 A0 */	lfs f0, 0xa0(r30)
/* 8014010C 0013CCEC  90 01 00 20 */	stw r0, 0x20(r1)
/* 80140110 0013CCF0  C0 7E 00 C0 */	lfs f3, 0xc0(r30)
/* 80140114 0013CCF4  C8 21 00 20 */	lfd f1, 0x20(r1)
/* 80140118 0013CCF8  C0 9F 23 74 */	lfs f4, 0x2374(r31)
/* 8014011C 0013CCFC  EC 21 10 28 */	fsubs f1, f1, f2
/* 80140120 0013CD00  EC 01 00 28 */	fsubs f0, f1, f0
/* 80140124 0013CD04  EC 03 00 32 */	fmuls f0, f3, f0
/* 80140128 0013CD08  EC 04 00 32 */	fmuls f0, f4, f0
/* 8014012C 0013CD0C  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 80140130 0013CD10  C0 22 A2 6C */	lfs f1, lbl_804D9C4C(r2)
/* 80140134 0013CD14  4B F3 59 BD */	bl func_80075AF0
/* 80140138 0013CD18  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8014013C 0013CD1C  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 80140140 0013CD20  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 80140144 0013CD24  48 00 00 14 */	b lbl_80140158
lbl_80140148:
/* 80140148 0013CD28  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8014014C 0013CD2C  FC 21 10 2A */	fadd f1, f1, f2
/* 80140150 0013CD30  FC 20 08 18 */	frsp f1, f1
/* 80140154 0013CD34  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_80140158:
/* 80140158 0013CD38  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 8014015C 0013CD3C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80140160 0013CD40  41 80 FF E8 */	blt lbl_80140148
/* 80140164 0013CD44  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 80140168 0013CD48  48 00 00 14 */	b lbl_8014017C
lbl_8014016C:
/* 8014016C 0013CD4C  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 80140170 0013CD50  FC 00 10 28 */	fsub f0, f0, f2
/* 80140174 0013CD54  FC 00 00 18 */	frsp f0, f0
/* 80140178 0013CD58  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_8014017C:
/* 8014017C 0013CD5C  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 80140180 0013CD60  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 80140184 0013CD64  41 81 FF E8 */	bgt lbl_8014016C
/* 80140188 0013CD68  38 80 00 03 */	li r4, 3
/* 8014018C 0013CD6C  4B F3 57 A1 */	bl func_8007592C
/* 80140190 0013CD70  3C 80 00 04 */	lis r4, 0x0003D0D9@ha
/* 80140194 0013CD74  38 7F 00 00 */	addi r3, r31, 0
/* 80140198 0013CD78  38 84 D0 D9 */	addi r4, r4, 0x0003D0D9@l
/* 8014019C 0013CD7C  38 A0 00 7F */	li r5, 0x7f
/* 801401A0 0013CD80  38 C0 00 40 */	li r6, 0x40
/* 801401A4 0013CD84  4B F4 7F A5 */	bl func_80088148
lbl_801401A8:
/* 801401A8 0013CD88  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801401AC 0013CD8C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 801401B0 0013CD90  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 801401B4 0013CD94  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 801401B8 0013CD98  38 21 00 38 */	addi r1, r1, 0x38
/* 801401BC 0013CD9C  7C 08 03 A6 */	mtlr r0
/* 801401C0 0013CDA0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D9C90;

#pragma push
asm unk_t lbl_801401C4()
{ // clang-format off
    nofralloc
/* 801401C4 0013CDA4  7C 08 02 A6 */	mflr r0
/* 801401C8 0013CDA8  90 01 00 04 */	stw r0, 4(r1)
/* 801401CC 0013CDAC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801401D0 0013CDB0  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 801401D4 0013CDB4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 801401D8 0013CDB8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 801401DC 0013CDBC  7C 7E 1B 78 */	mr r30, r3
/* 801401E0 0013CDC0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801401E4 0013CDC4  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 801401E8 0013CDC8  C0 5F 06 20 */	lfs f2, 0x620(r31)
/* 801401EC 0013CDCC  80 7F 02 D4 */	lwz r3, 0x2d4(r31)
/* 801401F0 0013CDD0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 801401F4 0013CDD4  40 80 00 0C */	bge lbl_80140200
/* 801401F8 0013CDD8  FC 20 10 50 */	fneg f1, f2
/* 801401FC 0013CDDC  48 00 00 08 */	b lbl_80140204
lbl_80140200:
/* 80140200 0013CDE0  FC 20 10 90 */	fmr f1, f2
lbl_80140204:
/* 80140204 0013CDE4  C0 03 00 68 */	lfs f0, 0x68(r3)
/* 80140208 0013CDE8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8014020C 0013CDEC  40 81 01 1C */	ble lbl_80140328
/* 80140210 0013CDF0  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 80140214 0013CDF4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80140218 0013CDF8  40 81 00 0C */	ble lbl_80140224
/* 8014021C 0013CDFC  C3 E2 A2 70 */	lfs f31, lbl_804D9C50(r2)
/* 80140220 0013CE00  48 00 00 08 */	b lbl_80140228
lbl_80140224:
/* 80140224 0013CE04  C3 E2 A2 80 */	lfs f31, lbl_804D9C60(r2)
lbl_80140228:
/* 80140228 0013CE08  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 8014022C 0013CE0C  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 80140230 0013CE10  41 82 00 F8 */	beq lbl_80140328
/* 80140234 0013CE14  7F C3 F3 78 */	mr r3, r30
/* 80140238 0013CE18  4B F3 AD C1 */	bl func_8007AFF8
/* 8014023C 0013CE1C  FC 00 F8 50 */	fneg f0, f31
/* 80140240 0013CE20  D3 FF 23 60 */	stfs f31, 0x2360(r31)
/* 80140244 0013CE24  3C 80 0C 4C */	lis r4, 0x0C4C0292@ha
/* 80140248 0013CE28  38 7E 00 00 */	addi r3, r30, 0
/* 8014024C 0013CE2C  D0 1F 23 74 */	stfs f0, 0x2374(r31)
/* 80140250 0013CE30  38 A4 02 92 */	addi r5, r4, 0x0C4C0292@l
/* 80140254 0013CE34  C0 42 A2 68 */	lfs f2, lbl_804D9C48(r2)
/* 80140258 0013CE38  38 80 01 5F */	li r4, 0x15f
/* 8014025C 0013CE3C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 80140260 0013CE40  38 C0 00 00 */	li r6, 0
/* 80140264 0013CE44  FC 60 10 90 */	fmr f3, f2
/* 80140268 0013CE48  4B F2 91 45 */	bl Fighter_ActionStateChange_800693AC
/* 8014026C 0013CE4C  3C 60 80 14 */	lis r3, lbl_8013D658@ha
/* 80140270 0013CE50  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 80140274 0013CE54  38 03 D6 58 */	addi r0, r3, lbl_8013D658@l
/* 80140278 0013CE58  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 8014027C 0013CE5C  3C 80 80 14 */	lis r4, lbl_8013D764@ha
/* 80140280 0013CE60  3C 60 80 14 */	lis r3, lbl_8014222C@ha
/* 80140284 0013CE64  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 80140288 0013CE68  38 04 D7 64 */	addi r0, r4, lbl_8013D764@l
/* 8014028C 0013CE6C  38 63 22 2C */	addi r3, r3, lbl_8014222C@l
/* 80140290 0013CE70  90 05 21 C0 */	stw r0, 0x21c0(r5)
/* 80140294 0013CE74  38 00 00 00 */	li r0, 0
/* 80140298 0013CE78  90 65 21 F8 */	stw r3, 0x21f8(r5)
/* 8014029C 0013CE7C  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 801402A0 0013CE80  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 801402A4 0013CE84  C0 22 A2 B0 */	lfs f1, lbl_804D9C90(r2)
/* 801402A8 0013CE88  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 801402AC 0013CE8C  EC 01 00 32 */	fmuls f0, f1, f0
/* 801402B0 0013CE90  D0 1F 23 5C */	stfs f0, 0x235c(r31)
/* 801402B4 0013CE94  90 1F 23 64 */	stw r0, 0x2364(r31)
/* 801402B8 0013CE98  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 801402BC 0013CE9C  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 801402C0 0013CEA0  C0 02 A2 68 */	lfs f0, lbl_804D9C48(r2)
/* 801402C4 0013CEA4  48 00 00 14 */	b lbl_801402D8
lbl_801402C8:
/* 801402C8 0013CEA8  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 801402CC 0013CEAC  FC 21 10 2A */	fadd f1, f1, f2
/* 801402D0 0013CEB0  FC 20 08 18 */	frsp f1, f1
/* 801402D4 0013CEB4  D0 23 23 54 */	stfs f1, 0x2354(r3)
lbl_801402D8:
/* 801402D8 0013CEB8  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 801402DC 0013CEBC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801402E0 0013CEC0  41 80 FF E8 */	blt lbl_801402C8
/* 801402E4 0013CEC4  C8 42 A2 78 */	lfd f2, lbl_804D9C58(r2)
/* 801402E8 0013CEC8  48 00 00 14 */	b lbl_801402FC
lbl_801402EC:
/* 801402EC 0013CECC  C0 03 23 54 */	lfs f0, 0x2354(r3)
/* 801402F0 0013CED0  FC 00 10 28 */	fsub f0, f0, f2
/* 801402F4 0013CED4  FC 00 00 18 */	frsp f0, f0
/* 801402F8 0013CED8  D0 03 23 54 */	stfs f0, 0x2354(r3)
lbl_801402FC:
/* 801402FC 0013CEDC  C0 23 23 54 */	lfs f1, 0x2354(r3)
/* 80140300 0013CEE0  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 80140304 0013CEE4  41 81 FF E8 */	bgt lbl_801402EC
/* 80140308 0013CEE8  38 80 00 03 */	li r4, 3
/* 8014030C 0013CEEC  4B F3 56 21 */	bl func_8007592C
/* 80140310 0013CEF0  3C 80 00 04 */	lis r4, 0x0003D0D9@ha
/* 80140314 0013CEF4  38 7F 00 00 */	addi r3, r31, 0
/* 80140318 0013CEF8  38 84 D0 D9 */	addi r4, r4, 0x0003D0D9@l
/* 8014031C 0013CEFC  38 A0 00 7F */	li r5, 0x7f
/* 80140320 0013CF00  38 C0 00 40 */	li r6, 0x40
/* 80140324 0013CF04  4B F4 7E 25 */	bl func_80088148
lbl_80140328:
/* 80140328 0013CF08  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8014032C 0013CF0C  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80140330 0013CF10  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80140334 0013CF14  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80140338 0013CF18  38 21 00 30 */	addi r1, r1, 0x30
/* 8014033C 0013CF1C  7C 08 03 A6 */	mtlr r0
/* 80140340 0013CF20  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void lbl_80140344(void)
{
    return;
}

void lbl_80140348(void)
{
    return;
}
