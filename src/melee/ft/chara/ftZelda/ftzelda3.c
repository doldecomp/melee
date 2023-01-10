#include <melee/ft/chara/ftZelda/ftzelda.h>

#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/code_80081B38.h>

void ftZelda_8013A830(HSD_GObj* fighter_gobj)
{
    Fighter* fp; // r31

    fp = fighter_gobj->user_data;
    if (fp->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4F4, fighter_gobj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftZelda_8013A8AC(HSD_GObj* fighter_gobj)
{
    Fighter* fp; // r31

    fp = fighter_gobj->user_data;
    if (fp->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4F5, fighter_gobj, fp->x5E8_fighterBones[1].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

void ftZelda_SpecialN_StartAction(HSD_GObj* fighter_gobj)
{
    f32 temp_f1;
    Fighter* fp;       // r31
    Fighter* fighter2; // r5
    ftZeldaAttributes* attributes;
    f32 unused[5];

    temp_f1 = 0;
    fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x155, 0, NULL, temp_f1,
                                       1.0, temp_f1);
    func_8006EBA4(fighter_gobj);

    fighter2 = fighter_gobj->user_data;
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2200_ftcmd_var0 = 0;
    fighter2->x2340_stateVar1 = attributes->x4;
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

void ftZelda_SpecialAirN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp; // r31
    Fighter* fighter2;
    ftZeldaAttributes* attributes;
    f32 unused[5];

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = fp->x80_self_vel.x / attributes->x8;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0, NULL, 0, 1.0, 0);
    func_8006EBA4(fighter_gobj);

    fighter2 = getFighter(fighter_gobj);
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2200_ftcmd_var0 = 0;
    fighter2->x2340_stateVar1 = attributes->x4;
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

void ftZelda_8013AA38(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftZeldaAttributes* attributes;
    s32 unused[5];

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 2;
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }

    if (fp->x2200_ftcmd_var0 == 0)
        fp->x2218_flag.bits.b3 = 0;

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        func_8008A2BC(fighter_gobj);
}

// 8013AACC - 8013AB60 (0x94 bytes)
// https://decomp.me/scratch/ttWvN
void ftZelda_8013AACC(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftZeldaAttributes* attributes;
    s32 unused[5];

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1U) {
        fp->x2200_ftcmd_var0 = 2U;
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }

    if (fp->x2200_ftcmd_var0 == 0U) {
        fp->x2218_flag.bits.b3 = 0;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftZelda_8013AB60(HSD_GObj* fighter_gobj)
{
    return;
}
void ftZelda_8013AB64(HSD_GObj* fighter_gobj)
{
    return;
}

// 8013AB68 - 8013AB9C (0x34 bytes)
void ftZelda_8013AB68(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

// 8013AB9C - 8013AC10 (0x74 bytes)
// https://decomp.me/scratch/juoPH
void ftZelda_8013AB9C(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 stateVar1;
    attr* fighterAttr;
    ftZeldaAttributes* charAttr;
    f32 arg2, arg3;
    s32 unused[2];

    fp = fighter_gobj->user_data;
    stateVar1 = fp->x2340_stateVar1;
    fighterAttr = &fp->x110_attr;
    charAttr = fp->x2D4_specialAttributes;

    if (stateVar1 != 0) {
        fp->x2340_stateVar1 = stateVar1 - 1;
    } else {
        arg2 = charAttr->xC;
        arg3 = fighterAttr->x170_TerminalVelocity;
        func_8007D494(fp, arg2, arg3);
    }

    func_8007CF58(fp);
    func_8007AEF8(fighter_gobj);
}

// 8013AC10 - 8013AC4C (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC10(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == 0) {
        ftZelda_8013AC88(fighter_gobj);
    }
}

// 8013AC4C - 8013AC88 (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC4C(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != 0) {
        ftZelda_8013AD1C(fighter_gobj);
    }
}

#ifdef MUST_MATCH

#pragma push
asm void ftZelda_8013AC88(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8013AC88 00000000  7C 08 02 A6 */	mflr r0
/* 8013AC8C 00000004  90 01 00 04 */	stw r0, 0x4(r1)
/* 8013AC90 00000008  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8013AC94 0000000C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8013AC98 00000010  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8013AC9C 00000014  7C 7E 1B 78 */	mr r30, r3
/* 8013ACA0 00000018  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013ACA4 0000001C  7F E3 FB 78 */	mr r3, r31
/* 8013ACA8 00000020  4B F4 29 2D */	bl func_8007D5D4
/* 8013ACAC 00000024  3C 80 0C 4C */	lis r4, 0xc4c
/* 8013ACB0 00000028  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013ACB4 0000002C  C0 42 A2 04 */	lfs f2, 1.0F
/* 8013ACB8 00000030  7F C3 F3 78 */	mr r3, r30
/* 8013ACBC 00000034  C0 62 A2 00 */	lfs f3, 0.0F
/* 8013ACC0 00000038  38 A4 50 8E */	addi r5, r4, 0x508e
/* 8013ACC4 0000003C  38 80 01 56 */	li r4, 0x156
/* 8013ACC8 00000040  38 C0 00 00 */	li r6, 0x0
/* 8013ACCC 00000044  4B F2 E6 E1 */	bl Fighter_ActionStateChange_800693AC
/* 8013ACD0 00000048  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 8013ACD4 0000004C  80 03 22 00 */	lwz r0, 0x2200(r3)
/* 8013ACD8 00000050  80 83 02 D4 */	lwz r4, 0x2d4(r3)
/* 8013ACDC 00000054  28 00 00 02 */	cmplwi r0, 0x2
/* 8013ACE0 00000058  40 82 00 18 */	bne lbl_8013ACF8
/* 8013ACE4 0000005C  3C 60 80 14 */	lis r3, ftZelda_8013ADB0@ha
/* 8013ACE8 00000060  38 A3 AD B0 */	addi r5, r3, ftZelda_8013ADB0@l
/* 8013ACEC 00000064  38 7E 00 00 */	addi r3, r30, 0x0
/* 8013ACF0 00000068  38 84 00 84 */	addi r4, r4, 0x84
/* 8013ACF4 0000006C  4B F4 05 49 */	bl ftColl_CreateReflectHit
lbl_8013ACF8:
/* 8013ACF8 00000070  3C 60 80 14 */	lis r3, ftZelda_8013A8AC@ha
/* 8013ACFC 00000074  38 03 A8 AC */	addi r0, r3, ftZelda_8013A8AC@l
/* 8013AD00 00000078  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8013AD04 0000007C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013AD08 00000080  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8013AD0C 00000084  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8013AD10 00000088  38 21 00 28 */	addi r1, r1, 0x28
/* 8013AD14 0000008C  7C 08 03 A6 */	mtlr r0
/* 8013AD18 00000090  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void ftZelda_8013AC88(HSD_GObj* fighter_gobj)
{
    ftZeldaAttributes* attributes;
    Fighter* fp;
    Fighter* fighter2;
    s32 unused[5];

    fp = fighter_gobj->user_data;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x156, 0x0C4C508E, NULL,
                                       fp->x894_currentAnimFrame, 1.0, 0);

    fighter2 = fighter_gobj->user_data;
    attributes = fighter2->x2D4_specialAttributes;

    if (fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

#endif

#ifdef MUST_MATCH

#pragma push
asm void ftZelda_8013AD1C(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8013AD1C 00000000  7C 08 02 A6 */	mflr r0
/* 8013AD20 00000004  90 01 00 04 */	stw r0, 0x4(r1)
/* 8013AD24 00000008  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8013AD28 0000000C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8013AD2C 00000010  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8013AD30 00000014  7C 7E 1B 78 */	mr r30, r3
/* 8013AD34 00000018  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8013AD38 0000001C  7F E3 FB 78 */	mr r3, r31
/* 8013AD3C 00000020  4B F4 2A C1 */	bl func_8007D7FC
/* 8013AD40 00000024  3C 80 0C 4C */	lis r4, 0xc4c
/* 8013AD44 00000028  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8013AD48 0000002C  C0 42 A2 04 */	lfs f2, 1.0F
/* 8013AD4C 00000030  7F C3 F3 78 */	mr r3, r30
/* 8013AD50 00000034  C0 62 A2 00 */	lfs f3, 0.0F
/* 8013AD54 00000038  38 A4 50 8E */	addi r5, r4, 0x508e
/* 8013AD58 0000003C  38 80 01 55 */	li r4, 0x155
/* 8013AD5C 00000040  38 C0 00 00 */	li r6, 0x0
/* 8013AD60 00000044  4B F2 E6 4D */	bl Fighter_ActionStateChange_800693AC
/* 8013AD64 00000048  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 8013AD68 0000004C  80 03 22 00 */	lwz r0, 0x2200(r3)
/* 8013AD6C 00000050  80 83 02 D4 */	lwz r4, 0x2d4(r3)
/* 8013AD70 00000054  28 00 00 02 */	cmplwi r0, 0x2
/* 8013AD74 00000058  40 82 00 18 */	bne lbl_8013AD8C
/* 8013AD78 0000005C  3C 60 80 14 */	lis r3, ftZelda_8013ADB0@ha
/* 8013AD7C 00000060  38 A3 AD B0 */	addi r5, r3, ftZelda_8013ADB0@l
/* 8013AD80 00000064  38 7E 00 00 */	addi r3, r30, 0x0
/* 8013AD84 00000068  38 84 00 84 */	addi r4, r4, 0x84
/* 8013AD88 0000006C  4B F4 04 B5 */	bl ftColl_CreateReflectHit
lbl_8013AD8C:
/* 8013AD8C 00000070  3C 60 80 14 */	lis r3, ftZelda_8013A830@ha
/* 8013AD90 00000074  38 03 A8 30 */	addi r0, r3, ftZelda_8013A830@l
/* 8013AD94 00000078  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8013AD98 0000007C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8013AD9C 00000080  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8013ADA0 00000084  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8013ADA4 00000088  38 21 00 28 */	addi r1, r1, 0x28
/* 8013ADA8 0000008C  7C 08 03 A6 */	mtlr r0
/* 8013ADAC 00000090  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void ftZelda_8013AD1C(HSD_GObj* fighter_gobj)
{
    ftZeldaAttributes* attributes;
    Fighter* fp;
    Fighter* fighter2;
    s32 unused[5];

    fp = fighter_gobj->user_data;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x155, 0x0C4C508E, NULL,
                                       fp->x894_currentAnimFrame, 1.0, 0);

    fighter2 = fighter_gobj->user_data;
    attributes = fighter2->x2D4_specialAttributes;

    if (fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighter_gobj, &attributes->x84,
                                &ftZelda_8013ADB0);
    }
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

#endif

void ftZelda_8013ADB0(HSD_GObj* fighter_gobj)
{
    return;
}
