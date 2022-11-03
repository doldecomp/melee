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
