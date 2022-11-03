#include <melee/ft/chara/ftPurin/ftpurin.h>

#include <melee/ef/ef.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
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
