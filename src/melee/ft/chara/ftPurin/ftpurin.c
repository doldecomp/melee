#include <melee/ft/chara/ftPurin/ftpurin.h>

#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_005.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftparts.h>
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
