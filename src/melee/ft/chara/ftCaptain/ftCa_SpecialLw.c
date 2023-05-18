#include <platform.h>
#include "ft/forward.h"
#include "ftCaptain/forward.h"

#include "ftCaptain/ftCa_SpecialLw.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"

#include <common_structs.h>
#include <baselib/gobj.h>

/// @todo These are all literals.
float const ftCa_SpecialHi_804D9220 = 0;
float const ftCa_SpecialHi_804D9224 = 0.01745329238474369f;
float const ftCa_SpecialHi_804D9228 = 1;
float const ftCa_SpecialHi_804D922C = -1;

#ifdef MWERKS_GEKKO
#pragma push
static asm void ftCa_SpecialHi_800E3EAC(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E3EAC 00000000  7C 08 02 A6 */	mflr r0
/* 800E3EB0 00000004  90 01 00 04 */	stw r0, 0x4(r1)
/* 800E3EB4 00000008  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800E3EB8 0000000C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800E3EBC 00000010  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800E3EC0 00000014  7C 7E 1B 78 */	mr r30, r3
/* 800E3EC4 00000018  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800E3EC8 0000001C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E3ECC 00000020  88 7F 22 10 */	lbz r3, 0x2210(r31)
/* 800E3ED0 00000024  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 800E3ED4 00000028  54 60 D7 FF */	extrwi. r0, r3, 1, 25
/* 800E3ED8 0000002C  41 82 00 18 */	beq lbl_800E3EF0
/* 800E3EDC 00000030  38 00 00 00 */	li r0, 0x0
/* 800E3EE0 00000034  50 03 36 72 */	rlwimi r3, r0, 6, 25, 25
/* 800E3EE4 00000038  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 800E3EE8 0000003C  38 00 00 01 */	li r0, 0x1
/* 800E3EEC 00000040  48 00 00 08 */	b lbl_800E3EF4
lbl_800E3EF0:
/* 800E3EF0 00000044  38 00 00 00 */	li r0, 0x0
lbl_800E3EF4:
/* 800E3EF4 00000048  2C 00 00 00 */	cmpwi r0, 0x0
/* 800E3EF8 0000004C  41 82 00 F8 */	beq lbl_800E3FF0
/* 800E3EFC 00000050  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800E3F00 00000054  54 00 CF FF */	extrwi. r0, r0, 1, 24
/* 800E3F04 00000058  40 82 00 E4 */	bne lbl_800E3FE8
/* 800E3F08 0000005C  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800E3F0C 00000060  2C 00 01 65 */	cmpwi r0, 0x165
/* 800E3F10 00000064  40 82 00 20 */	bne lbl_800E3F30
/* 800E3F14 00000068  C0 02 98 40 */	lfs f0, ftCa_SpecialHi_804D9220
/* 800E3F18 0000006C  38 7F 00 00 */	addi r3, r31, 0x0
/* 800E3F1C 00000070  38 80 00 0E */	li r4, 0xe
/* 800E3F20 00000074  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800E3F24 00000078  4B F9 10 E9 */	bl ftParts_8007500C
/* 800E3F28 0000007C  7C 7D 1B 78 */	mr r29, r3
/* 800E3F2C 00000080  48 00 00 2C */	b lbl_800E3F58
lbl_800E3F30:
/* 800E3F30 00000084  2C 00 01 67 */	cmpwi r0, 0x167
/* 800E3F34 00000088  40 82 00 24 */	bne lbl_800E3F58
/* 800E3F38 0000008C  C0 22 98 44 */	lfs f1, ftCa_SpecialHi_804D9224
/* 800E3F3C 00000090  7F E3 FB 78 */	mr r3, r31
/* 800E3F40 00000094  C0 04 00 70 */	lfs f0, 0x70(r4)
/* 800E3F44 00000098  38 80 00 09 */	li r4, 0x9
/* 800E3F48 0000009C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800E3F4C 000000A0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800E3F50 000000A4  4B F9 10 BD */	bl ftParts_8007500C
/* 800E3F54 000000A8  7C 7D 1B 78 */	mr r29, r3
lbl_800E3F58:
/* 800E3F58 000000AC  7F C3 F3 78 */	mr r3, r30
/* 800E3F5C 000000B0  4B FA 33 49 */	bl ftLib_800872A4
/* 800E3F60 000000B4  2C 03 00 19 */	cmpwi r3, 0x19
/* 800E3F64 000000B8  41 82 00 44 */	beq lbl_800E3FA8
/* 800E3F68 000000BC  40 80 00 6C */	bge lbl_800E3FD4
/* 800E3F6C 000000C0  2C 03 00 02 */	cmpwi r3, 0x2
/* 800E3F70 000000C4  41 82 00 08 */	beq lbl_800E3F78
/* 800E3F74 000000C8  48 00 00 60 */	b lbl_800E3FD4
lbl_800E3F78:
/* 800E3F78 000000CC  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800E3F7C 000000D0  57 A0 20 36 */	slwi r0, r29, 4
/* 800E3F80 000000D4  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800E3F84 000000D8  7F C3 F3 78 */	mr r3, r30
/* 800E3F88 000000DC  7C E4 00 2E */	lwzx r7, r4, r0
/* 800E3F8C 000000E0  38 85 06 0C */	addi r4, r5, 0x60c
/* 800E3F90 000000E4  4C C6 31 82 */	crclr 4*cr1+eq
/* 800E3F94 000000E8  39 01 00 1C */	addi r8, r1, 0x1c
/* 800E3F98 000000EC  38 A0 00 03 */	li r5, 0x3
/* 800E3F9C 000000F0  38 C0 04 90 */	li r6, 0x490
/* 800E3FA0 000000F4  4B F8 37 51 */	bl efAsync_Spawn
/* 800E3FA4 000000F8  48 00 00 30 */	b lbl_800E3FD4
lbl_800E3FA8:
/* 800E3FA8 000000FC  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800E3FAC 00000100  57 A0 20 36 */	slwi r0, r29, 4
/* 800E3FB0 00000104  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800E3FB4 00000108  7F C3 F3 78 */	mr r3, r30
/* 800E3FB8 0000010C  7C E4 00 2E */	lwzx r7, r4, r0
/* 800E3FBC 00000110  38 85 06 0C */	addi r4, r5, 0x60c
/* 800E3FC0 00000114  4C C6 31 82 */	crclr 4*cr1+eq
/* 800E3FC4 00000118  39 01 00 1C */	addi r8, r1, 0x1c
/* 800E3FC8 0000011C  38 A0 00 03 */	li r5, 0x3
/* 800E3FCC 00000120  38 C0 05 0C */	li r6, 0x50c
/* 800E3FD0 00000124  4B F8 37 21 */	bl efAsync_Spawn
lbl_800E3FD4:
/* 800E3FD4 00000128  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800E3FD8 0000012C  38 60 00 01 */	li r3, 0x1
/* 800E3FDC 00000130  50 60 3E 30 */	rlwimi r0, r3, 7, 24, 24
/* 800E3FE0 00000134  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800E3FE4 00000138  48 00 00 0C */	b lbl_800E3FF0
lbl_800E3FE8:
/* 800E3FE8 0000013C  7F C3 F3 78 */	mr r3, r30
/* 800E3FEC 00000140  4B F9 9B 39 */	bl ftCommon_8007DB24
lbl_800E3FF0:
/* 800E3FF0 00000144  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800E3FF4 00000148  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800E3FF8 0000014C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800E3FFC 00000150  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800E4000 00000154  38 21 00 30 */	addi r1, r1, 0x30
/* 800E4004 00000158  7C 08 03 A6 */	mtlr r0
/* 800E4008 0000015C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void ftCa_SpecialHi_800E3EAC(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}
#endif

static void ftCa_SpecialHi_800E400C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = getFtSpecialAttrsD(fp);
    if (fp->mv.ca.speciallw.x0 <= da->speciallw_unk2) {
        ++fp->mv.ca.speciallw.x0;
        fp->mv.ca.speciallw.friction *= da->speciallw_on_hit_spd_modifier;
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialLw_Enter(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4040 000E0C20  7C 08 02 A6 */	mflr r0
/* 800E4044 000E0C24  38 80 01 65 */	li r4, 0x165
/* 800E4048 000E0C28  90 01 00 04 */	stw r0, 4(r1)
/* 800E404C 000E0C2C  38 00 00 00 */	li r0, 0
/* 800E4050 000E0C30  38 A0 00 00 */	li r5, 0
/* 800E4054 000E0C34  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E4058 000E0C38  38 C0 00 00 */	li r6, 0
/* 800E405C 000E0C3C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E4060 000E0C40  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800E4064 000E0C44  7C 7E 1B 78 */	mr r30, r3
/* 800E4068 000E0C48  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E406C 000E0C4C  90 1F 22 08 */	stw r0, 0x2208(r31)
/* 800E4070 000E0C50  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 800E4074 000E0C54  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 800E4078 000E0C58  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 800E407C 000E0C5C  B0 1F 23 40 */	sth r0, 0x2340(r31)
/* 800E4080 000E0C60  C0 42 98 48 */	lfs f2, ftCa_SpecialHi_804D9228/*1*/
/* 800E4084 000E0C64  D0 5F 23 44 */	stfs f2, 0x2344(r31)
/* 800E4088 000E0C68  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E408C 000E0C6C  FC 60 08 90 */	fmr f3, f1
/* 800E4090 000E0C70  4B F8 53 1D */	bl Fighter_ChangeMotionState
/* 800E4094 000E0C74  7F C3 F3 78 */	mr r3, r30
/* 800E4098 000E0C78  4B F8 AB 0D */	bl ftAnim_8006EBA4
/* 800E409C 000E0C7C  3C 60 80 0E */	lis r3, ftCa_SpecialHi_800E400C@ha
/* 800E40A0 000E0C80  38 03 40 0C */	addi r0, r3, ftCa_SpecialHi_800E400C@l
/* 800E40A4 000E0C84  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 800E40A8 000E0C88  90 1F 21 C0 */	stw r0, 0x21c0(r31)
/* 800E40AC 000E0C8C  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 800E40B0 000E0C90  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 800E40B4 000E0C94  90 1F 21 D4 */	stw r0, 0x21d4(r31)
/* 800E40B8 000E0C98  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 800E40BC 000E0C9C  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 800E40C0 000E0CA0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E40C4 000E0CA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E40C8 000E0CA8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800E40CC 000E0CAC  38 21 00 20 */	addi r1, r1, 0x20
/* 800E40D0 000E0CB0  7C 08 03 A6 */	mtlr r0
/* 800E40D4 000E0CB4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLw_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags.flags = 0;
    fp->mv.ca.speciallw.x0 = 0;
    fp->mv.ca.speciallw.friction = 1;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLw, Ft_MF_None, NULL, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21C0_callback_OnGiveDamage = ftCa_SpecialHi_800E400C;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirLw_Enter(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E40D8 000E0CB8  7C 08 02 A6 */	mflr r0
/* 800E40DC 000E0CBC  38 80 01 67 */	li r4, 0x167
/* 800E40E0 000E0CC0  90 01 00 04 */	stw r0, 4(r1)
/* 800E40E4 000E0CC4  38 00 00 00 */	li r0, 0
/* 800E40E8 000E0CC8  38 A0 00 00 */	li r5, 0
/* 800E40EC 000E0CCC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E40F0 000E0CD0  38 C0 00 00 */	li r6, 0
/* 800E40F4 000E0CD4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E40F8 000E0CD8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800E40FC 000E0CDC  7C 7E 1B 78 */	mr r30, r3
/* 800E4100 000E0CE0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E4104 000E0CE4  90 1F 22 08 */	stw r0, 0x2208(r31)
/* 800E4108 000E0CE8  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 800E410C 000E0CEC  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 800E4110 000E0CF0  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 800E4114 000E0CF4  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E4118 000E0CF8  C0 42 98 48 */	lfs f2, ftCa_SpecialHi_804D9228/*1*/
/* 800E411C 000E0CFC  FC 60 08 90 */	fmr f3, f1
/* 800E4120 000E0D00  4B F8 52 8D */	bl Fighter_ChangeMotionState
/* 800E4124 000E0D04  7F C3 F3 78 */	mr r3, r30
/* 800E4128 000E0D08  4B F8 AA 7D */	bl ftAnim_8006EBA4
/* 800E412C 000E0D0C  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 800E4130 000E0D10  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 800E4134 000E0D14  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 800E4138 000E0D18  90 1F 21 D4 */	stw r0, 0x21d4(r31)
/* 800E413C 000E0D1C  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 800E4140 000E0D20  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 800E4144 000E0D24  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E4148 000E0D28  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E414C 000E0D2C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800E4150 000E0D30  38 21 00 20 */	addi r1, r1, 0x20
/* 800E4154 000E0D34  7C 08 03 A6 */	mtlr r0
/* 800E4158 000E0D38  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLw, Ft_MF_None, NULL, 0,
                              1, 0);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialLw_Anim(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E415C 000E0D3C  7C 08 02 A6 */	mflr r0
/* 800E4160 000E0D40  90 01 00 04 */	stw r0, 4(r1)
/* 800E4164 000E0D44  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800E4168 000E0D48  93 E1 00 44 */	stw r31, 0x44(r1)
/* 800E416C 000E0D4C  93 C1 00 40 */	stw r30, 0x40(r1)
/* 800E4170 000E0D50  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 800E4174 000E0D54  7C 7D 1B 78 */	mr r29, r3
/* 800E4178 000E0D58  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800E417C 000E0D5C  4B F8 B0 BD */	bl ftAnim_IsFramesRemaining
/* 800E4180 000E0D60  2C 03 00 00 */	cmpwi r3, 0
/* 800E4184 000E0D64  40 82 00 C8 */	bne lbl_800E424C
/* 800E4188 000E0D68  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 800E418C 000E0D6C  2C 00 00 00 */	cmpwi r0, 0
/* 800E4190 000E0D70  40 82 00 64 */	bne lbl_800E41F4
/* 800E4194 000E0D74  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 800E4198 000E0D78  38 00 00 00 */	li r0, 0
/* 800E419C 000E0D7C  83 FE 02 D4 */	lwz r31, 0x2d4(r30)
/* 800E41A0 000E0D80  7F C3 F3 78 */	mr r3, r30
/* 800E41A4 000E0D84  90 1E 22 08 */	stw r0, 0x2208(r30)
/* 800E41A8 000E0D88  90 1E 22 04 */	stw r0, 0x2204(r30)
/* 800E41AC 000E0D8C  90 1E 22 00 */	stw r0, 0x2200(r30)
/* 800E41B0 000E0D90  90 1E 22 10 */	stw r0, 0x2210(r30)
/* 800E41B4 000E0D94  4B F9 96 49 */	bl ftCommon_8007D7FC
/* 800E41B8 000E0D98  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E41BC 000E0D9C  7F A3 EB 78 */	mr r3, r29
/* 800E41C0 000E0DA0  C0 5F 00 7C */	lfs f2, 0x7c(r31)
/* 800E41C4 000E0DA4  38 80 01 66 */	li r4, 0x166
/* 800E41C8 000E0DA8  FC 60 08 90 */	fmr f3, f1
/* 800E41CC 000E0DAC  38 A0 00 00 */	li r5, 0
/* 800E41D0 000E0DB0  38 C0 00 00 */	li r6, 0
/* 800E41D4 000E0DB4  4B F8 51 D9 */	bl Fighter_ChangeMotionState
/* 800E41D8 000E0DB8  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 800E41DC 000E0DBC  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 800E41E0 000E0DC0  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 800E41E4 000E0DC4  90 1E 21 D4 */	stw r0, 0x21d4(r30)
/* 800E41E8 000E0DC8  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 800E41EC 000E0DCC  90 1E 21 D8 */	stw r0, 0x21d8(r30)
/* 800E41F0 000E0DD0  48 00 00 5C */	b lbl_800E424C
lbl_800E41F4:
/* 800E41F4 000E0DD4  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 800E41F8 000E0DD8  38 00 00 00 */	li r0, 0
/* 800E41FC 000E0DDC  90 1E 22 08 */	stw r0, 0x2208(r30)
/* 800E4200 000E0DE0  7F C3 F3 78 */	mr r3, r30
/* 800E4204 000E0DE4  90 1E 22 04 */	stw r0, 0x2204(r30)
/* 800E4208 000E0DE8  90 1E 22 00 */	stw r0, 0x2200(r30)
/* 800E420C 000E0DEC  90 1E 22 10 */	stw r0, 0x2210(r30)
/* 800E4210 000E0DF0  4B F9 93 C5 */	bl ftCommon_8007D5D4
/* 800E4214 000E0DF4  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E4218 000E0DF8  7F A3 EB 78 */	mr r3, r29
/* 800E421C 000E0DFC  C0 42 98 48 */	lfs f2, ftCa_SpecialHi_804D9228/*1*/
/* 800E4220 000E0E00  38 80 01 6A */	li r4, 0x16a
/* 800E4224 000E0E04  FC 60 08 90 */	fmr f3, f1
/* 800E4228 000E0E08  38 A0 00 00 */	li r5, 0
/* 800E422C 000E0E0C  38 C0 00 00 */	li r6, 0
/* 800E4230 000E0E10  4B F8 51 7D */	bl Fighter_ChangeMotionState
/* 800E4234 000E0E14  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 800E4238 000E0E18  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 800E423C 000E0E1C  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 800E4240 000E0E20  90 1E 21 D4 */	stw r0, 0x21d4(r30)
/* 800E4244 000E0E24  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 800E4248 000E0E28  90 1E 21 D8 */	stw r0, 0x21d8(r30)
lbl_800E424C:
/* 800E424C 000E0E2C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800E4250 000E0E30  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 800E4254 000E0E34  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 800E4258 000E0E38  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 800E425C 000E0E3C  38 21 00 48 */	addi r1, r1, 0x48
/* 800E4260 000E0E40  7C 08 03 A6 */	mtlr r0
/* 800E4264 000E0E44  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            Fighter* fp = GET_FIGHTER(gobj);
            ftCaptain_DatAttrs* da = fp->dat_attrs;
            fp->cmd_vars[2] = 0;
            fp->cmd_vars[1] = 0;
            fp->cmd_vars[0] = 0;
            fp->throw_flags.flags = 0;
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEnd, Ft_MF_None,
                                      NULL, 0, da->speciallw_ground_lag_mul,
                                      0);
            fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
            fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        } else {
            Fighter* fp = GET_FIGHTER(gobj);
            fp->cmd_vars[2] = 0;
            fp->cmd_vars[1] = 0;
            fp->cmd_vars[0] = 0;
            fp->throw_flags.flags = 0;
            ftCommon_8007D5D4(fp);
            Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEndAir,
                                      Ft_MF_None, NULL, 0, 1, 0);
            fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
            fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        }
    }
}
#endif

void ftCa_SpecialLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCa_SpecialLwEndAir_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirLw_Anim(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E42E0 000E0EC0  7C 08 02 A6 */	mflr r0
/* 800E42E4 000E0EC4  90 01 00 04 */	stw r0, 4(r1)
/* 800E42E8 000E0EC8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E42EC 000E0ECC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E42F0 000E0ED0  7C 7F 1B 78 */	mr r31, r3
/* 800E42F4 000E0ED4  4B F8 AF 45 */	bl ftAnim_IsFramesRemaining
/* 800E42F8 000E0ED8  2C 03 00 00 */	cmpwi r3, 0
/* 800E42FC 000E0EDC  40 82 00 44 */	bne lbl_800E4340
/* 800E4300 000E0EE0  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800E4304 000E0EE4  38 00 00 00 */	li r0, 0
/* 800E4308 000E0EE8  90 04 22 08 */	stw r0, 0x2208(r4)
/* 800E430C 000E0EEC  7C 83 23 78 */	mr r3, r4
/* 800E4310 000E0EF0  90 04 22 04 */	stw r0, 0x2204(r4)
/* 800E4314 000E0EF4  90 04 22 00 */	stw r0, 0x2200(r4)
/* 800E4318 000E0EF8  90 04 22 10 */	stw r0, 0x2210(r4)
/* 800E431C 000E0EFC  4B F9 92 B9 */	bl ftCommon_8007D5D4
/* 800E4320 000E0F00  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E4324 000E0F04  7F E3 FB 78 */	mr r3, r31
/* 800E4328 000E0F08  C0 42 98 48 */	lfs f2, ftCa_SpecialHi_804D9228/*1*/
/* 800E432C 000E0F0C  38 80 01 69 */	li r4, 0x169
/* 800E4330 000E0F10  FC 60 08 90 */	fmr f3, f1
/* 800E4334 000E0F14  38 A0 00 00 */	li r5, 0
/* 800E4338 000E0F18  38 C0 00 00 */	li r6, 0
/* 800E433C 000E0F1C  4B F8 50 71 */	bl Fighter_ChangeMotionState
lbl_800E4340:
/* 800E4340 000E0F20  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E4344 000E0F24  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E4348 000E0F28  38 21 00 20 */	addi r1, r1, 0x20
/* 800E434C 000E0F2C  7C 08 03 A6 */	mtlr r0
/* 800E4350 000E0F30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[2] = 0;
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->throw_flags.flags = 0;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLwEndAir, Ft_MF_None,
                                  NULL, 0, 1, 0);
    }
}
#endif

void ftCa_SpecialAirLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCa_SpecialAirLwEndAir_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftCa_SpecialHiThrow1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialLw_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4408 000E0FE8  7C 08 02 A6 */	mflr r0
/* 800E440C 000E0FEC  90 01 00 04 */	stw r0, 4(r1)
/* 800E4410 000E0FF0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800E4414 000E0FF4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800E4418 000E0FF8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800E441C 000E0FFC  7C 7E 1B 78 */	mr r30, r3
/* 800E4420 000E1000  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800E4424 000E1004  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 800E4428 000E1008  3B E3 00 00 */	addi r31, r3, 0
/* 800E442C 000E100C  2C 00 00 00 */	cmpwi r0, 0
/* 800E4430 000E1010  40 82 00 18 */	bne lbl_800E4448
/* 800E4434 000E1014  7F E3 FB 78 */	mr r3, r31
/* 800E4438 000E1018  4B F9 A1 75 */	bl ftCommon_8007E5AC
/* 800E443C 000E101C  7F C3 F3 78 */	mr r3, r30
/* 800E4440 000E1020  4B FA 0C 49 */	bl ft_80085088
/* 800E4444 000E1024  48 00 00 1C */	b lbl_800E4460
lbl_800E4448:
/* 800E4448 000E1028  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E444C 000E102C  38 7F 00 00 */	addi r3, r31, 0
/* 800E4450 000E1030  38 80 00 00 */	li r4, 0
/* 800E4454 000E1034  4B F9 18 61 */	bl ftParts_80075CB4
/* 800E4458 000E1038  7F C3 F3 78 */	mr r3, r30
/* 800E445C 000E103C  4B FA 0C D9 */	bl ft_80085134
lbl_800E4460:
/* 800E4460 000E1040  C0 3F 23 44 */	lfs f1, 0x2344(r31)
/* 800E4464 000E1044  7F C3 F3 78 */	mr r3, r30
/* 800E4468 000E1048  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 800E446C 000E104C  EC 00 00 72 */	fmuls f0, f0, f1
/* 800E4470 000E1050  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800E4474 000E1054  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800E4478 000E1058  EC 00 00 72 */	fmuls f0, f0, f1
/* 800E447C 000E105C  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800E4480 000E1060  4B FF FA 2D */	bl ftCa_SpecialHi_800E3EAC
/* 800E4484 000E1064  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800E4488 000E1068  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800E448C 000E106C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800E4490 000E1070  38 21 00 18 */	addi r1, r1, 0x18
/* 800E4494 000E1074  7C 08 03 A6 */	mtlr r0
/* 800E4498 000E1078  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC((Fighter*) fp);
        ft_80085088(gobj);
    } else {
        ftParts_80075CB4((Fighter*) fp, 0, 0);
        ft_80085134(gobj);
    }
    {
        f32 friction = fp->mv.ca.speciallw.friction;
        fp->self_vel.x *= friction;
        fp->self_vel.y *= friction;
    }
    ftCa_SpecialHi_800E3EAC(gobj);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialLwEnd_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E449C 000E107C  7C 08 02 A6 */	mflr r0
/* 800E44A0 000E1080  90 01 00 04 */	stw r0, 4(r1)
/* 800E44A4 000E1084  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800E44A8 000E1088  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800E44AC 000E108C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800E44B0 000E1090  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800E44B4 000E1094  7C 7D 1B 78 */	mr r29, r3
/* 800E44B8 000E1098  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E44BC 000E109C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 800E44C0 000E10A0  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 800E44C4 000E10A4  2C 00 00 00 */	cmpwi r0, 0
/* 800E44C8 000E10A8  40 82 00 44 */	bne lbl_800E450C
/* 800E44CC 000E10AC  7F E3 FB 78 */	mr r3, r31
/* 800E44D0 000E10B0  4B F9 A0 DD */	bl ftCommon_8007E5AC
/* 800E44D4 000E10B4  80 1F 22 08 */	lwz r0, 0x2208(r31)
/* 800E44D8 000E10B8  28 00 00 00 */	cmplwi r0, 0
/* 800E44DC 000E10BC  41 82 00 24 */	beq lbl_800E4500
/* 800E44E0 000E10C0  C0 3E 00 84 */	lfs f1, 0x84(r30)
/* 800E44E4 000E10C4  7F E3 FB 78 */	mr r3, r31
/* 800E44E8 000E10C8  C0 1F 01 28 */	lfs f0, 0x128(r31)
/* 800E44EC 000E10CC  EC 21 00 32 */	fmuls f1, f1, f0
/* 800E44F0 000E10D0  4B F9 84 41 */	bl ftCommon_8007C930
/* 800E44F4 000E10D4  7F A3 EB 78 */	mr r3, r29
/* 800E44F8 000E10D8  4B F9 86 7D */	bl ftCommon_8007CB74
/* 800E44FC 000E10DC  48 00 00 28 */	b lbl_800E4524
lbl_800E4500:
/* 800E4500 000E10E0  7F A3 EB 78 */	mr r3, r29
/* 800E4504 000E10E4  4B FA 0A 39 */	bl ft_80084F3C
/* 800E4508 000E10E8  48 00 00 1C */	b lbl_800E4524
lbl_800E450C:
/* 800E450C 000E10EC  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E4510 000E10F0  38 7F 00 00 */	addi r3, r31, 0
/* 800E4514 000E10F4  38 80 00 00 */	li r4, 0
/* 800E4518 000E10F8  4B F9 17 9D */	bl ftParts_80075CB4
/* 800E451C 000E10FC  7F A3 EB 78 */	mr r3, r29
/* 800E4520 000E1100  4B FA 09 CD */	bl ft_80084EEC
lbl_800E4524:
/* 800E4524 000E1104  C0 3F 23 44 */	lfs f1, 0x2344(r31)
/* 800E4528 000E1108  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 800E452C 000E110C  EC 00 00 72 */	fmuls f0, f0, f1
/* 800E4530 000E1110  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800E4534 000E1114  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800E4538 000E1118  EC 00 00 72 */	fmuls f0, f0, f1
/* 800E453C 000E111C  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800E4540 000E1120  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800E4544 000E1124  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800E4548 000E1128  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800E454C 000E112C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800E4550 000E1130  38 21 00 28 */	addi r1, r1, 0x28
/* 800E4554 000E1134  7C 08 03 A6 */	mtlr r0
/* 800E4558 000E1138  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLwEnd_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = gobj->user_data;
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC(fp);
        if (fp->cmd_vars[2] != 0) {
            ftCommon_8007C930(fp, da->speciallw_ground_traction *
                                      fp->co_attrs.gr_friction);
            ftCommon_8007CB74(gobj);
        } else {
            ft_80084F3C(gobj);
        }
    } else {
        ftParts_80075CB4(fp, 0, 0);
        ft_80084EEC(gobj);
    }
    {
        f32 friction = fp->mv.ca.speciallw.friction;
        fp->self_vel.x *= friction;
        fp->self_vel.y *= friction;
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialLwEndAir_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E455C 000E113C  7C 08 02 A6 */	mflr r0
/* 800E4560 000E1140  90 01 00 04 */	stw r0, 4(r1)
/* 800E4564 000E1144  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800E4568 000E1148  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800E456C 000E114C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800E4570 000E1150  7C 7E 1B 78 */	mr r30, r3
/* 800E4574 000E1154  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800E4578 000E1158  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 800E457C 000E115C  3B E3 00 00 */	addi r31, r3, 0
/* 800E4580 000E1160  2C 00 00 00 */	cmpwi r0, 0
/* 800E4584 000E1164  40 82 00 18 */	bne lbl_800E459C
/* 800E4588 000E1168  7F E3 FB 78 */	mr r3, r31
/* 800E458C 000E116C  4B F9 A0 21 */	bl ftCommon_8007E5AC
/* 800E4590 000E1170  7F C3 F3 78 */	mr r3, r30
/* 800E4594 000E1174  4B FA 0A F5 */	bl ft_80085088
/* 800E4598 000E1178  48 00 00 34 */	b lbl_800E45CC
lbl_800E459C:
/* 800E459C 000E117C  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E45A0 000E1180  38 7F 00 00 */	addi r3, r31, 0
/* 800E45A4 000E1184  38 80 00 00 */	li r4, 0
/* 800E45A8 000E1188  4B F9 17 0D */	bl ftParts_80075CB4
/* 800E45AC 000E118C  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 800E45B0 000E1190  28 00 00 00 */	cmplwi r0, 0
/* 800E45B4 000E1194  41 82 00 10 */	beq lbl_800E45C4
/* 800E45B8 000E1198  7F C3 F3 78 */	mr r3, r30
/* 800E45BC 000E119C  4B FA 09 31 */	bl ft_80084EEC
/* 800E45C0 000E11A0  48 00 00 0C */	b lbl_800E45CC
lbl_800E45C4:
/* 800E45C4 000E11A4  7F C3 F3 78 */	mr r3, r30
/* 800E45C8 000E11A8  4B FA 0B 6D */	bl ft_80085134
lbl_800E45CC:
/* 800E45CC 000E11AC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800E45D0 000E11B0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800E45D4 000E11B4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800E45D8 000E11B8  38 21 00 18 */	addi r1, r1, 0x18
/* 800E45DC 000E11BC  7C 08 03 A6 */	mtlr r0
/* 800E45E0 000E11C0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLwEndAir_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC(fp);
        ft_80085088(gobj);
        return;
    }
    ftParts_80075CB4(fp, 0, 0);
    if (fp->cmd_vars[0] != 0) {
        ft_80084EEC(gobj);
    } else {
        ft_80085134(gobj);
    }
}
#endif

void ftCa_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
    ftCa_SpecialHi_800E3EAC(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirLwEnd_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4618 000E11F8  7C 08 02 A6 */	mflr r0
/* 800E461C 000E11FC  90 01 00 04 */	stw r0, 4(r1)
/* 800E4620 000E1200  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E4624 000E1204  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E4628 000E1208  7C 7F 1B 78 */	mr r31, r3
/* 800E462C 000E120C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800E4630 000E1210  80 03 22 08 */	lwz r0, 0x2208(r3)
/* 800E4634 000E1214  80 A3 02 D4 */	lwz r5, 0x2d4(r3)
/* 800E4638 000E1218  28 00 00 00 */	cmplwi r0, 0
/* 800E463C 000E121C  41 82 00 20 */	beq lbl_800E465C
/* 800E4640 000E1220  C0 25 00 88 */	lfs f1, 0x88(r5)
/* 800E4644 000E1224  C0 03 01 28 */	lfs f0, 0x128(r3)
/* 800E4648 000E1228  EC 21 00 32 */	fmuls f1, f1, f0
/* 800E464C 000E122C  4B F9 82 E5 */	bl ftCommon_8007C930
/* 800E4650 000E1230  7F E3 FB 78 */	mr r3, r31
/* 800E4654 000E1234  4B F9 85 21 */	bl ftCommon_8007CB74
/* 800E4658 000E1238  48 00 00 0C */	b lbl_800E4664
lbl_800E465C:
/* 800E465C 000E123C  7F E3 FB 78 */	mr r3, r31
/* 800E4660 000E1240  4B FA 08 DD */	bl ft_80084F3C
lbl_800E4664:
/* 800E4664 000E1244  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E4668 000E1248  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E466C 000E124C  38 21 00 20 */	addi r1, r1, 0x20
/* 800E4670 000E1250  7C 08 03 A6 */	mtlr r0
/* 800E4674 000E1254  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirLwEnd_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[2] != 0) {
        ftCommon_8007C930(fp, da->speciallw_air_landing_traction *
                                  fp->co_attrs.gr_friction);
        ftCommon_8007CB74(gobj);
        return;
    } else {
        ft_80084F3C(gobj);
    }
}
#endif

void ftCa_SpecialAirLwEndAir_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftCa_SpecialHiThrow1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialLw_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E46B8 000E1298  7C 08 02 A6 */	mflr r0
/* 800E46BC 000E129C  90 01 00 04 */	stw r0, 4(r1)
/* 800E46C0 000E12A0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800E46C4 000E12A4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800E46C8 000E12A8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800E46CC 000E12AC  7C 7E 1B 78 */	mr r30, r3
/* 800E46D0 000E12B0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800E46D4 000E12B4  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 800E46D8 000E12B8  3B E3 00 00 */	addi r31, r3, 0
/* 800E46DC 000E12BC  2C 00 00 00 */	cmpwi r0, 0
/* 800E46E0 000E12C0  40 82 00 20 */	bne lbl_800E4700
/* 800E46E4 000E12C4  7F C3 F3 78 */	mr r3, r30
/* 800E46E8 000E12C8  4B F9 E0 21 */	bl ft_80082708
/* 800E46EC 000E12CC  2C 03 00 00 */	cmpwi r3, 0
/* 800E46F0 000E12D0  40 82 00 28 */	bne lbl_800E4718
/* 800E46F4 000E12D4  7F E3 FB 78 */	mr r3, r31
/* 800E46F8 000E12D8  4B F9 8E DD */	bl ftCommon_8007D5D4
/* 800E46FC 000E12DC  48 00 00 1C */	b lbl_800E4718
lbl_800E4700:
/* 800E4700 000E12E0  7F C3 F3 78 */	mr r3, r30
/* 800E4704 000E12E4  4B F9 D6 09 */	bl ft_80081D0C
/* 800E4708 000E12E8  2C 03 00 00 */	cmpwi r3, 0
/* 800E470C 000E12EC  41 82 00 0C */	beq lbl_800E4718
/* 800E4710 000E12F0  7F E3 FB 78 */	mr r3, r31
/* 800E4714 000E12F4  4B F9 90 E9 */	bl ftCommon_8007D7FC
lbl_800E4718:
/* 800E4718 000E12F8  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 800E471C 000E12FC  28 00 00 00 */	cmplwi r0, 0
/* 800E4720 000E1300  41 82 00 78 */	beq lbl_800E4798
/* 800E4724 000E1304  C0 02 98 4C */	lfs f0, ftCa_SpecialHi_804D922C/*-1*/
/* 800E4728 000E1308  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800E472C 000E130C  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800E4730 000E1310  40 82 00 10 */	bne lbl_800E4740
/* 800E4734 000E1314  80 1F 08 24 */	lwz r0, 0x824(r31)
/* 800E4738 000E1318  54 00 05 29 */	rlwinm. r0, r0, 0, 0x14, 0x14
/* 800E473C 000E131C  40 82 00 1C */	bne lbl_800E4758
lbl_800E4740:
/* 800E4740 000E1320  C0 02 98 48 */	lfs f0, ftCa_SpecialHi_804D9228/*1*/
/* 800E4744 000E1324  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800E4748 000E1328  40 82 00 50 */	bne lbl_800E4798
/* 800E474C 000E132C  80 1F 08 24 */	lwz r0, 0x824(r31)
/* 800E4750 000E1330  54 00 06 B5 */	rlwinm. r0, r0, 0, 0x1a, 0x1a
/* 800E4754 000E1334  41 82 00 44 */	beq lbl_800E4798
lbl_800E4758:
/* 800E4758 000E1338  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800E475C 000E133C  38 00 00 00 */	li r0, 0
/* 800E4760 000E1340  90 04 22 08 */	stw r0, 0x2208(r4)
/* 800E4764 000E1344  7C 83 23 78 */	mr r3, r4
/* 800E4768 000E1348  90 04 22 04 */	stw r0, 0x2204(r4)
/* 800E476C 000E134C  90 04 22 00 */	stw r0, 0x2200(r4)
/* 800E4770 000E1350  90 04 22 10 */	stw r0, 0x2210(r4)
/* 800E4774 000E1354  4B F9 8E 61 */	bl ftCommon_8007D5D4
/* 800E4778 000E1358  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E477C 000E135C  7F C3 F3 78 */	mr r3, r30
/* 800E4780 000E1360  C0 42 98 48 */	lfs f2, ftCa_SpecialHi_804D9228/*1*/
/* 800E4784 000E1364  38 80 01 6B */	li r4, 0x16b
/* 800E4788 000E1368  FC 60 08 90 */	fmr f3, f1
/* 800E478C 000E136C  38 A0 00 00 */	li r5, 0
/* 800E4790 000E1370  38 C0 00 00 */	li r6, 0
/* 800E4794 000E1374  4B F8 4C 19 */	bl Fighter_ChangeMotionState
lbl_800E4798:
/* 800E4798 000E1378  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800E479C 000E137C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800E47A0 000E1380  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800E47A4 000E1384  38 21 00 28 */	addi r1, r1, 0x28
/* 800E47A8 000E1388  7C 08 03 A6 */	mtlr r0
/* 800E47AC 000E138C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLw_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if ((s32) fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == 0) {
            ftCommon_8007D5D4((Fighter*) fp);
        }
    } else if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC((Fighter*) fp);
    }
    {
        f32 facing_dir;
        if ((fp->cmd_vars[0] != 0) &&
            /// @todo Pull out these check functions
            (((facing_dir = fp->facing_dir, ((facing_dir == -1) != 0)) &&
              (fp->coll_data.env_flags & MPCOLL_FLAGS_B11)) ||
             (facing_dir == +1 &&
              (fp->coll_data.env_flags & MPCOLL_FLAGS_B5))))
        {
            Fighter* fp = GET_FIGHTER(gobj);
            fp->cmd_vars[2] = 0;
            fp->cmd_vars[1] = 0;
            fp->cmd_vars[0] = 0;
            fp->throw_flags.flags = 0;
            ftCommon_8007D5D4(fp);
            Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiThrow1,
                                      Ft_MF_None, NULL, 0, 1, 0);
        }
    }
}
#endif

void ftCa_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        if (fp->cmd_vars[1] != 0) {
            if (!ft_800827A0(gobj)) {
                ftCommon_8007D5D4(fp);
            }
        } else if (!ft_80082708(gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialLwEndAir_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4838 000E1418  7C 08 02 A6 */	mflr r0
/* 800E483C 000E141C  90 01 00 04 */	stw r0, 4(r1)
/* 800E4840 000E1420  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800E4844 000E1424  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800E4848 000E1428  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E484C 000E142C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 800E4850 000E1430  2C 00 00 00 */	cmpwi r0, 0
/* 800E4854 000E1434  40 82 00 40 */	bne lbl_800E4894
/* 800E4858 000E1438  80 1F 22 04 */	lwz r0, 0x2204(r31)
/* 800E485C 000E143C  28 00 00 00 */	cmplwi r0, 0
/* 800E4860 000E1440  41 82 00 1C */	beq lbl_800E487C
/* 800E4864 000E1444  4B F9 DF 3D */	bl ft_800827A0
/* 800E4868 000E1448  2C 03 00 00 */	cmpwi r3, 0
/* 800E486C 000E144C  40 82 00 3C */	bne lbl_800E48A8
/* 800E4870 000E1450  7F E3 FB 78 */	mr r3, r31
/* 800E4874 000E1454  4B F9 8D 61 */	bl ftCommon_8007D5D4
/* 800E4878 000E1458  48 00 00 30 */	b lbl_800E48A8
lbl_800E487C:
/* 800E487C 000E145C  4B F9 DE 8D */	bl ft_80082708
/* 800E4880 000E1460  2C 03 00 00 */	cmpwi r3, 0
/* 800E4884 000E1464  40 82 00 24 */	bne lbl_800E48A8
/* 800E4888 000E1468  7F E3 FB 78 */	mr r3, r31
/* 800E488C 000E146C  4B F9 8D 49 */	bl ftCommon_8007D5D4
/* 800E4890 000E1470  48 00 00 18 */	b lbl_800E48A8
lbl_800E4894:
/* 800E4894 000E1474  4B F9 D4 79 */	bl ft_80081D0C
/* 800E4898 000E1478  2C 03 00 00 */	cmpwi r3, 0
/* 800E489C 000E147C  41 82 00 0C */	beq lbl_800E48A8
/* 800E48A0 000E1480  7F E3 FB 78 */	mr r3, r31
/* 800E48A4 000E1484  4B F9 8F 59 */	bl ftCommon_8007D7FC
lbl_800E48A8:
/* 800E48A8 000E1488  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800E48AC 000E148C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800E48B0 000E1490  38 21 00 18 */	addi r1, r1, 0x18
/* 800E48B4 000E1494  7C 08 03 A6 */	mtlr r0
/* 800E48B8 000E1498  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLwEndAir_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        if (fp->cmd_vars[1] != 0) {
            if (!ft_800827A0(gobj)) {
                ftCommon_8007D5D4(fp);
            }
        } else if (!ft_80082708(gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirLw_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E48BC 000E149C  7C 08 02 A6 */	mflr r0
/* 800E48C0 000E14A0  90 01 00 04 */	stw r0, 4(r1)
/* 800E48C4 000E14A4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800E48C8 000E14A8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800E48CC 000E14AC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800E48D0 000E14B0  7C 7E 1B 78 */	mr r30, r3
/* 800E48D4 000E14B4  4B F9 D4 39 */	bl ft_80081D0C
/* 800E48D8 000E14B8  2C 03 00 00 */	cmpwi r3, 0
/* 800E48DC 000E14BC  41 82 00 48 */	beq lbl_800E4924
/* 800E48E0 000E14C0  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800E48E4 000E14C4  38 00 00 00 */	li r0, 0
/* 800E48E8 000E14C8  83 E4 02 D4 */	lwz r31, 0x2d4(r4)
/* 800E48EC 000E14CC  7C 83 23 78 */	mr r3, r4
/* 800E48F0 000E14D0  90 04 22 08 */	stw r0, 0x2208(r4)
/* 800E48F4 000E14D4  90 04 22 04 */	stw r0, 0x2204(r4)
/* 800E48F8 000E14D8  90 04 22 00 */	stw r0, 0x2200(r4)
/* 800E48FC 000E14DC  90 04 22 10 */	stw r0, 0x2210(r4)
/* 800E4900 000E14E0  4B F9 8E FD */	bl ftCommon_8007D7FC
/* 800E4904 000E14E4  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E4908 000E14E8  7F C3 F3 78 */	mr r3, r30
/* 800E490C 000E14EC  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 800E4910 000E14F0  38 80 01 68 */	li r4, 0x168
/* 800E4914 000E14F4  FC 60 08 90 */	fmr f3, f1
/* 800E4918 000E14F8  38 A0 00 00 */	li r5, 0
/* 800E491C 000E14FC  38 C0 00 00 */	li r6, 0
/* 800E4920 000E1500  4B F8 4A 8D */	bl Fighter_ChangeMotionState
lbl_800E4924:
/* 800E4924 000E1504  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800E4928 000E1508  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800E492C 000E150C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800E4930 000E1510  38 21 00 30 */	addi r1, r1, 0x30
/* 800E4934 000E1514  7C 08 03 A6 */	mtlr r0
/* 800E4938 000E1518  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        fp->cmd_vars[2] = 0;
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->throw_flags.flags = 0;
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLwEnd, Ft_MF_None,
                                  NULL, 0, da->speciallw_landing_lag_mul, 0);
    }
}
#endif

void ftCa_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirLwEndAir_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E495C 000E153C  7C 08 02 A6 */	mflr r0
/* 800E4960 000E1540  90 01 00 04 */	stw r0, 4(r1)
/* 800E4964 000E1544  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800E4968 000E1548  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800E496C 000E154C  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800E4970 000E1550  7C 7E 1B 78 */	mr r30, r3
/* 800E4974 000E1554  4B F9 D3 99 */	bl ft_80081D0C
/* 800E4978 000E1558  2C 03 00 00 */	cmpwi r3, 0
/* 800E497C 000E155C  41 82 00 48 */	beq lbl_800E49C4
/* 800E4980 000E1560  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800E4984 000E1564  38 00 00 00 */	li r0, 0
/* 800E4988 000E1568  83 E4 02 D4 */	lwz r31, 0x2d4(r4)
/* 800E498C 000E156C  7C 83 23 78 */	mr r3, r4
/* 800E4990 000E1570  90 04 22 08 */	stw r0, 0x2208(r4)
/* 800E4994 000E1574  90 04 22 04 */	stw r0, 0x2204(r4)
/* 800E4998 000E1578  90 04 22 00 */	stw r0, 0x2200(r4)
/* 800E499C 000E157C  90 04 22 10 */	stw r0, 0x2210(r4)
/* 800E49A0 000E1580  4B F9 8E 5D */	bl ftCommon_8007D7FC
/* 800E49A4 000E1584  C0 22 98 40 */	lfs f1, ftCa_SpecialHi_804D9220/*0*/
/* 800E49A8 000E1588  7F C3 F3 78 */	mr r3, r30
/* 800E49AC 000E158C  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 800E49B0 000E1590  38 80 01 68 */	li r4, 0x168
/* 800E49B4 000E1594  FC 60 08 90 */	fmr f3, f1
/* 800E49B8 000E1598  38 A0 00 00 */	li r5, 0
/* 800E49BC 000E159C  38 C0 00 00 */	li r6, 0
/* 800E49C0 000E15A0  4B F8 49 ED */	bl Fighter_ChangeMotionState
lbl_800E49C4:
/* 800E49C4 000E15A4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800E49C8 000E15A8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800E49CC 000E15AC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800E49D0 000E15B0  38 21 00 30 */	addi r1, r1, 0x30
/* 800E49D4 000E15B4  7C 08 03 A6 */	mtlr r0
/* 800E49D8 000E15B8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirLwEndAir_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        fp->cmd_vars[2] = 0;
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->throw_flags.flags = 0;
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLwEnd, Ft_MF_None,
                                  NULL, 0, da->speciallw_landing_lag_mul, 0);
    }
}
#endif
