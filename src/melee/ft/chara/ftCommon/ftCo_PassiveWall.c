#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_PassiveWall.h"

#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_DownAttack.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialAir.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lb_00CE.h"

/* literal */ extern float const ftCo_804D8C60;
/* literal */ extern float const ftCo_804D8C64;
/* literal */ extern double const ftCo_804D8C68;
/* literal */ extern float const ftCo_804D8C70;
/* literal */ extern double const ftCo_804D8C78;

#ifdef WIP
#pragma force_active on
#endif

bool ftCo_800C1D38(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if ((coll->env_flags & MPCOLL_FLAGS_B11 ||
         coll->env_flags & MPCOLL_FLAGS_B05) &&
        ftCo_800986B0(gobj))
    {
        ftCommon_MotionState msid =
            ftCo_800C1E0C(fp) ? ftCo_MS_PassiveWallJump : ftCo_MS_PassiveWall;
        if (coll->env_flags & MPCOLL_FLAGS_B11) {
            ftCo_800C1E64(gobj, msid, p_ftCommonData->x760, 0, ftCo_804D8C60);
        } else {
            ftCo_800C1E64(gobj, msid, p_ftCommonData->x760, 0, ftCo_804D8C64);
        }
        return true;
    }
    return false;
}

ASM bool ftCo_800C1E0C(Fighter* fp)
#if !defined(MUST_MATCH) || defined(WIP)
{
    if (fp->x67E < p_ftCommonData->x250 ||
        fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax)
    {
        return true;
    }
    return false;
}

#else /* clang-format off */
{ nofralloc
/* 800C1E0C 000BE9EC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C1E10 000BE9F0  3C 00 43 30 */	lis r0, 0x4330
/* 800C1E14 000BE9F4  88 83 06 7E */	lbz r4, 0x67e(r3)
/* 800C1E18 000BE9F8  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 800C1E1C 000BE9FC  90 81 00 14 */	stw r4, 0x14(r1)
/* 800C1E20 000BEA00  C8 42 92 88 */	lfd f2, ftCo_804D8C68
/* 800C1E24 000BEA04  90 01 00 10 */	stw r0, 0x10(r1)
/* 800C1E28 000BEA08  C0 05 02 50 */	lfs f0, 0x250(r5)
/* 800C1E2C 000BEA0C  C8 21 00 10 */	lfd f1, 0x10(r1)
/* 800C1E30 000BEA10  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C1E34 000BEA14  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C1E38 000BEA18  41 80 00 18 */	blt lbl_800C1E50
/* 800C1E3C 000BEA1C  C0 23 06 24 */	lfs f1, 0x624(r3)
/* 800C1E40 000BEA20  C0 05 00 70 */	lfs f0, 0x70(r5)
/* 800C1E44 000BEA24  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C1E48 000BEA28  4C 41 13 82 */	cror 2, 1, 2
/* 800C1E4C 000BEA2C  40 82 00 0C */	bne lbl_800C1E58
lbl_800C1E50:
/* 800C1E50 000BEA30  38 60 00 01 */	li r3, 1
/* 800C1E54 000BEA34  48 00 00 08 */	b lbl_800C1E5C
lbl_800C1E58:
/* 800C1E58 000BEA38  38 60 00 00 */	li r3, 0
lbl_800C1E5C:
/* 800C1E5C 000BEA3C  38 21 00 18 */	addi r1, r1, 0x18
/* 800C1E60 000BEA40  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C1E64(ftCo_GObj* gobj, int msid, int timer,
                       int vel_y_exponent, float facing_dir)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 ef_offset;
    fp->cmd_vars[0] = true;
    {
        CollData* coll = &fp->coll_data;
        fp->facing_dir = -facing_dir;
        ftCommon_8007E2FC(gobj);
        if (fp->coll_data.env_flags & MPCOLL_FLAGS_B11) {
            ef_offset.x = coll->xA4_ecbCurrCorrect.left.x;
            ef_offset.y = coll->xA4_ecbCurrCorrect.left.y;
            ef_offset.z = ftCo_804D8C70;
        } else {
            ef_offset.x = coll->xA4_ecbCurrCorrect.right.x;
            ef_offset.y = coll->xA4_ecbCurrCorrect.right.y;
            ef_offset.z = ftCo_804D8C70;
        }
    }
    ftKb_SpecialN_800F1F1C(gobj, &ef_offset);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, ftCo_804D8C70,
                              timer != 0 ? ftCo_804D8C70 : ftCo_804D8C64,
                              ftCo_804D8C70, NULL);
    fp->x670_timer_lstick_tilt_x = 0xFE;
    fp->x671_timer_lstick_tilt_y = 0xFE;
    fp->mv.co.passivewall.timer = timer;
    fp->mv.co.passivewall.x4 = 0;
    fp->mv.co.passivewall.x8 = false;
    fp->mv.co.passivewall.vel_y_exponent = vel_y_exponent;
    {
        Vec3 ef_pos;
        float pos_x_offset = fp->cur_pos.x + ef_offset.x;
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4] = { 0 };
#endif
        ef_pos.x = pos_x_offset;
        ef_pos.y = fp->cur_pos.y + ef_offset.y;
        ef_pos.z = fp->cur_pos.z;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2,
                      (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 10),
                      NULL, &ef_pos);
        fp->cur_pos.x =
            -(fp->x68C_transNPos.z * -fp->facing_dir - pos_x_offset);
    }
    ft_80081F2C(gobj);
    ft_800881D8(fp, fp->ft_data->x4C_collisionData->x24, 0x7F, 0x40);
    ftCommon_8007EBAC(fp, 12, 0);
    if (timer == 0) {
        ft_80088148(fp, 3, 0x7F, 0x40);
    }
    ftCo_800BFFD0(fp, 120, 0);
    ftColl_8007B760(gobj, p_ftCommonData->x764);
}

#else /* clang-format off */
{ nofralloc
/* 800C1E64 000BEA44  7C 08 02 A6 */	mflr r0
/* 800C1E68 000BEA48  FC 00 08 50 */	fneg f0, f1
/* 800C1E6C 000BEA4C  90 01 00 04 */	stw r0, 4(r1)
/* 800C1E70 000BEA50  38 00 00 01 */	li r0, 1
/* 800C1E74 000BEA54  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800C1E78 000BEA58  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 800C1E7C 000BEA5C  BF 41 00 40 */	stmw r26, 0x40(r1)
/* 800C1E80 000BEA60  7C 7A 1B 78 */	mr r26, r3
/* 800C1E84 000BEA64  3B 64 00 00 */	addi r27, r4, 0
/* 800C1E88 000BEA68  7C BC 2B 78 */	mr r28, r5
/* 800C1E8C 000BEA6C  3B A6 00 00 */	addi r29, r6, 0
/* 800C1E90 000BEA70  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C1E94 000BEA74  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 800C1E98 000BEA78  3B DF 06 F0 */	addi r30, r31, 0x6f0
/* 800C1E9C 000BEA7C  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800C1EA0 000BEA80  4B FB C4 5D */	bl ftCommon_8007E2FC
/* 800C1EA4 000BEA84  80 1F 08 24 */	lwz r0, 0x824(r31)
/* 800C1EA8 000BEA88  54 00 05 29 */	rlwinm. r0, r0, 0, 0x14, 0x14
/* 800C1EAC 000BEA8C  41 82 00 20 */	beq lbl_800C1ECC
/* 800C1EB0 000BEA90  C0 3E 00 BC */	lfs f1, 0xbc(r30)
/* 800C1EB4 000BEA94  C0 02 92 90 */	lfs f0, ftCo_804D8C70
/* 800C1EB8 000BEA98  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 800C1EBC 000BEA9C  C0 3E 00 C0 */	lfs f1, 0xc0(r30)
/* 800C1EC0 000BEAA0  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 800C1EC4 000BEAA4  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800C1EC8 000BEAA8  48 00 00 1C */	b lbl_800C1EE4
lbl_800C1ECC:
/* 800C1ECC 000BEAAC  C0 3E 00 B4 */	lfs f1, 0xb4(r30)
/* 800C1ED0 000BEAB0  C0 02 92 90 */	lfs f0, ftCo_804D8C70
/* 800C1ED4 000BEAB4  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 800C1ED8 000BEAB8  C0 3E 00 B8 */	lfs f1, 0xb8(r30)
/* 800C1EDC 000BEABC  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 800C1EE0 000BEAC0  D0 01 00 38 */	stfs f0, 0x38(r1)
lbl_800C1EE4:
/* 800C1EE4 000BEAC4  38 7A 00 00 */	addi r3, r26, 0
/* 800C1EE8 000BEAC8  38 81 00 30 */	addi r4, r1, 0x30
/* 800C1EEC 000BEACC  48 03 00 31 */	bl ftKb_SpecialN_800F1F1C
/* 800C1EF0 000BEAD0  2C 1C 00 00 */	cmpwi r28, 0
/* 800C1EF4 000BEAD4  41 82 00 0C */	beq lbl_800C1F00
/* 800C1EF8 000BEAD8  C0 42 92 90 */	lfs f2, ftCo_804D8C70
/* 800C1EFC 000BEADC  48 00 00 08 */	b lbl_800C1F04
lbl_800C1F00:
/* 800C1F00 000BEAE0  C0 42 92 84 */	lfs f2, ftCo_804D8C64
lbl_800C1F04:
/* 800C1F04 000BEAE4  C0 22 92 90 */	lfs f1, ftCo_804D8C70
/* 800C1F08 000BEAE8  7F 43 D3 78 */	mr r3, r26
/* 800C1F0C 000BEAEC  38 9B 00 00 */	addi r4, r27, 0
/* 800C1F10 000BEAF0  FC 60 08 90 */	fmr f3, f1
/* 800C1F14 000BEAF4  38 A0 00 00 */	li r5, 0
/* 800C1F18 000BEAF8  38 C0 00 00 */	li r6, 0
/* 800C1F1C 000BEAFC  4B FA 74 91 */	bl Fighter_ChangeMotionState
/* 800C1F20 000BEB00  38 80 00 FE */	li r4, 0xfe
/* 800C1F24 000BEB04  4C C6 31 82 */	crclr 6
/* 800C1F28 000BEB08  98 9F 06 70 */	stb r4, 0x670(r31)
/* 800C1F2C 000BEB0C  38 00 00 00 */	li r0, 0
/* 800C1F30 000BEB10  38 7A 00 00 */	addi r3, r26, 0
/* 800C1F34 000BEB14  98 9F 06 71 */	stb r4, 0x671(r31)
/* 800C1F38 000BEB18  39 01 00 24 */	addi r8, r1, 0x24
/* 800C1F3C 000BEB1C  38 A0 00 02 */	li r5, 2
/* 800C1F40 000BEB20  93 9F 23 40 */	stw r28, 0x2340(r31)
/* 800C1F44 000BEB24  38 C0 04 1D */	li r6, 0x41d
/* 800C1F48 000BEB28  38 E0 00 00 */	li r7, 0
/* 800C1F4C 000BEB2C  90 1F 23 44 */	stw r0, 0x2344(r31)
/* 800C1F50 000BEB30  90 1F 23 48 */	stw r0, 0x2348(r31)
/* 800C1F54 000BEB34  93 BF 23 4C */	stw r29, 0x234c(r31)
/* 800C1F58 000BEB38  C0 5F 00 B0 */	lfs f2, 0xb0(r31)
/* 800C1F5C 000BEB3C  C0 21 00 30 */	lfs f1, 0x30(r1)
/* 800C1F60 000BEB40  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 800C1F64 000BEB44  EF E2 08 2A */	fadds f31, f2, f1
/* 800C1F68 000BEB48  D3 E1 00 24 */	stfs f31, 0x24(r1)
/* 800C1F6C 000BEB4C  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 800C1F70 000BEB50  EC 01 00 2A */	fadds f0, f1, f0
/* 800C1F74 000BEB54  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800C1F78 000BEB58  C0 1F 00 B8 */	lfs f0, 0xb8(r31)
/* 800C1F7C 000BEB5C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800C1F80 000BEB60  80 9A 00 2C */	lwz r4, 0x2c(r26)
/* 800C1F84 000BEB64  38 84 06 0C */	addi r4, r4, 0x60c
/* 800C1F88 000BEB68  4B FA 57 69 */	bl efAsync_Spawn
/* 800C1F8C 000BEB6C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C1F90 000BEB70  7F 43 D3 78 */	mr r3, r26
/* 800C1F94 000BEB74  C0 3F 06 94 */	lfs f1, 0x694(r31)
/* 800C1F98 000BEB78  FC 00 00 50 */	fneg f0, f0
/* 800C1F9C 000BEB7C  EC 01 F8 3C */	fnmsubs f0, f1, f0, f31
/* 800C1FA0 000BEB80  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 800C1FA4 000BEB84  4B FB FF 89 */	bl ft_80081F2C
/* 800C1FA8 000BEB88  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 800C1FAC 000BEB8C  38 7F 00 00 */	addi r3, r31, 0
/* 800C1FB0 000BEB90  38 A0 00 7F */	li r5, 0x7f
/* 800C1FB4 000BEB94  80 84 00 4C */	lwz r4, 0x4c(r4)
/* 800C1FB8 000BEB98  38 C0 00 40 */	li r6, 0x40
/* 800C1FBC 000BEB9C  80 84 00 24 */	lwz r4, 0x24(r4)
/* 800C1FC0 000BEBA0  4B FC 62 19 */	bl ft_800881D8
/* 800C1FC4 000BEBA4  38 7F 00 00 */	addi r3, r31, 0
/* 800C1FC8 000BEBA8  38 80 00 0C */	li r4, 0xc
/* 800C1FCC 000BEBAC  38 A0 00 00 */	li r5, 0
/* 800C1FD0 000BEBB0  4B FB CB DD */	bl ftCommon_8007EBAC
/* 800C1FD4 000BEBB4  2C 1C 00 00 */	cmpwi r28, 0
/* 800C1FD8 000BEBB8  40 82 00 18 */	bne lbl_800C1FF0
/* 800C1FDC 000BEBBC  38 7F 00 00 */	addi r3, r31, 0
/* 800C1FE0 000BEBC0  38 80 00 03 */	li r4, 3
/* 800C1FE4 000BEBC4  38 A0 00 7F */	li r5, 0x7f
/* 800C1FE8 000BEBC8  38 C0 00 40 */	li r6, 0x40
/* 800C1FEC 000BEBCC  4B FC 61 5D */	bl ft_80088148
lbl_800C1FF0:
/* 800C1FF0 000BEBD0  38 7F 00 00 */	addi r3, r31, 0
/* 800C1FF4 000BEBD4  38 80 00 78 */	li r4, 0x78
/* 800C1FF8 000BEBD8  38 A0 00 00 */	li r5, 0
/* 800C1FFC 000BEBDC  4B FF DF D5 */	bl ftCo_800BFFD0
/* 800C2000 000BEBE0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C2004 000BEBE4  7F 43 D3 78 */	mr r3, r26
/* 800C2008 000BEBE8  80 84 07 64 */	lwz r4, 0x764(r4)
/* 800C200C 000BEBEC  4B FB 97 55 */	bl ftColl_8007B760
/* 800C2010 000BEBF0  BB 41 00 40 */	lmw r26, 0x40(r1)
/* 800C2014 000BEBF4  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800C2018 000BEBF8  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 800C201C 000BEBFC  38 21 00 60 */	addi r1, r1, 0x60
/* 800C2020 000BEC00  7C 08 03 A6 */	mtlr r0
/* 800C2024 000BEC04  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineA0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_PassiveWallJump, Ft_MF_None,
                              fp->cur_anim_frame, ftCo_804D8C64, ftCo_804D8C70,
                              NULL);
    fp->x671_timer_lstick_tilt_y = 0xFE;
    fp->mv.co.passivewall.timer = 0;
}

ASM void ftCo_PassiveWall_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.passivewall.timer != 0) {
        --fp->mv.co.passivewall.timer;
        if (fp->mv.co.passivewall.timer == 0) {
            ft_80088148(fp, 8, 0x7F, 0x40);
            if (fp->mv.co.passivewall.x8) {
                inlineA0(gobj);
            } else {
                ftAnim_SetAnimRate(gobj, ftCo_804D8C64);
            }
            if (fp->motion_id == ftCo_MS_PassiveWall) {
                fp->self_vel.x =
                    fp->facing_dir * fp->co_attrs.passivewall_vel_x;
            } else {
                fp->self_vel.x = fp->facing_dir *
                                 fp->co_attrs.wall_jump_horizontal_velocity;
                fp->self_vel.y = fp->co_attrs.wall_jump_vertical_velocity;
                if (fp->x1969_walljumpUsed != 0) {
                    fp->self_vel.y *=
                        powf(p_ftCommonData->passive_wall_vel_y_base,
                             fp->mv.co.passivewall.vel_y_exponent);
                }
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C2028 000BEC08  7C 08 02 A6 */	mflr r0
/* 800C202C 000BEC0C  90 01 00 04 */	stw r0, 4(r1)
/* 800C2030 000BEC10  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C2034 000BEC14  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800C2038 000BEC18  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800C203C 000BEC1C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800C2040 000BEC20  7C 7D 1B 78 */	mr r29, r3
/* 800C2044 000BEC24  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800C2048 000BEC28  80 64 23 40 */	lwz r3, 0x2340(r4)
/* 800C204C 000BEC2C  3B C4 00 00 */	addi r30, r4, 0
/* 800C2050 000BEC30  2C 03 00 00 */	cmpwi r3, 0
/* 800C2054 000BEC34  41 82 00 F8 */	beq lbl_800C214C
/* 800C2058 000BEC38  38 03 FF FF */	addi r0, r3, -1
/* 800C205C 000BEC3C  90 1E 23 40 */	stw r0, 0x2340(r30)
/* 800C2060 000BEC40  80 1E 23 40 */	lwz r0, 0x2340(r30)
/* 800C2064 000BEC44  2C 00 00 00 */	cmpwi r0, 0
/* 800C2068 000BEC48  40 82 00 E4 */	bne lbl_800C214C
/* 800C206C 000BEC4C  38 7E 00 00 */	addi r3, r30, 0
/* 800C2070 000BEC50  38 80 00 08 */	li r4, 8
/* 800C2074 000BEC54  38 A0 00 7F */	li r5, 0x7f
/* 800C2078 000BEC58  38 C0 00 40 */	li r6, 0x40
/* 800C207C 000BEC5C  4B FC 60 CD */	bl ft_80088148
/* 800C2080 000BEC60  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 800C2084 000BEC64  2C 00 00 00 */	cmpwi r0, 0
/* 800C2088 000BEC68  41 82 00 3C */	beq lbl_800C20C4
/* 800C208C 000BEC6C  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 800C2090 000BEC70  7F A3 EB 78 */	mr r3, r29
/* 800C2094 000BEC74  C0 42 92 84 */	lfs f2, ftCo_804D8C64
/* 800C2098 000BEC78  38 80 00 CB */	li r4, 0xcb
/* 800C209C 000BEC7C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800C20A0 000BEC80  C0 62 92 90 */	lfs f3, ftCo_804D8C70
/* 800C20A4 000BEC84  38 A0 00 00 */	li r5, 0
/* 800C20A8 000BEC88  38 C0 00 00 */	li r6, 0
/* 800C20AC 000BEC8C  4B FA 73 01 */	bl Fighter_ChangeMotionState
/* 800C20B0 000BEC90  38 00 00 FE */	li r0, 0xfe
/* 800C20B4 000BEC94  98 1F 06 71 */	stb r0, 0x671(r31)
/* 800C20B8 000BEC98  38 00 00 00 */	li r0, 0
/* 800C20BC 000BEC9C  90 1F 23 40 */	stw r0, 0x2340(r31)
/* 800C20C0 000BECA0  48 00 00 10 */	b lbl_800C20D0
lbl_800C20C4:
/* 800C20C4 000BECA4  7F A3 EB 78 */	mr r3, r29
/* 800C20C8 000BECA8  C0 22 92 84 */	lfs f1, ftCo_804D8C64
/* 800C20CC 000BECAC  4B FA D0 C5 */	bl ftAnim_SetAnimRate
lbl_800C20D0:
/* 800C20D0 000BECB0  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 800C20D4 000BECB4  2C 00 00 CA */	cmpwi r0, 0xca
/* 800C20D8 000BECB8  40 82 00 18 */	bne lbl_800C20F0
/* 800C20DC 000BECBC  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 800C20E0 000BECC0  C0 1E 02 10 */	lfs f0, 0x210(r30)
/* 800C20E4 000BECC4  EC 01 00 32 */	fmuls f0, f1, f0
/* 800C20E8 000BECC8  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 800C20EC 000BECCC  48 00 00 60 */	b lbl_800C214C
lbl_800C20F0:
/* 800C20F0 000BECD0  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 800C20F4 000BECD4  C0 1E 02 14 */	lfs f0, 0x214(r30)
/* 800C20F8 000BECD8  EC 01 00 32 */	fmuls f0, f1, f0
/* 800C20FC 000BECDC  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 800C2100 000BECE0  C0 1E 02 18 */	lfs f0, 0x218(r30)
/* 800C2104 000BECE4  D0 1E 00 84 */	stfs f0, 0x84(r30)
/* 800C2108 000BECE8  88 1E 19 69 */	lbz r0, 0x1969(r30)
/* 800C210C 000BECEC  28 00 00 00 */	cmplwi r0, 0
/* 800C2110 000BECF0  41 82 00 3C */	beq lbl_800C214C
/* 800C2114 000BECF4  80 7E 23 4C */	lwz r3, 0x234c(r30)
/* 800C2118 000BECF8  3C 00 43 30 */	lis r0, 0x4330
/* 800C211C 000BECFC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C2120 000BED00  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800C2124 000BED04  C8 42 92 98 */	lfd f2, ftCo_804D8C78
/* 800C2128 000BED08  90 61 00 2C */	stw r3, 0x2c(r1)
/* 800C212C 000BED0C  C0 24 07 78 */	lfs f1, 0x778(r4)
/* 800C2130 000BED10  90 01 00 28 */	stw r0, 0x28(r1)
/* 800C2134 000BED14  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 800C2138 000BED18  EC 40 10 28 */	fsubs f2, f0, f2
/* 800C213C 000BED1C  4B F4 AD A5 */	bl powf
/* 800C2140 000BED20  C0 1E 00 84 */	lfs f0, 0x84(r30)
/* 800C2144 000BED24  EC 00 00 72 */	fmuls f0, f0, f1
/* 800C2148 000BED28  D0 1E 00 84 */	stfs f0, 0x84(r30)
lbl_800C214C:
/* 800C214C 000BED2C  7F A3 EB 78 */	mr r3, r29
/* 800C2150 000BED30  4B FA D0 E9 */	bl ftAnim_IsFramesRemaining
/* 800C2154 000BED34  2C 03 00 00 */	cmpwi r3, 0
/* 800C2158 000BED38  40 82 00 0C */	bne lbl_800C2164
/* 800C215C 000BED3C  7F A3 EB 78 */	mr r3, r29
/* 800C2160 000BED40  48 00 A5 D1 */	bl ftCo_800CC730
lbl_800C2164:
/* 800C2164 000BED44  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C2168 000BED48  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800C216C 000BED4C  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800C2170 000BED50  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800C2174 000BED54  38 21 00 40 */	addi r1, r1, 0x40
/* 800C2178 000BED58  7C 08 03 A6 */	mtlr r0
/* 800C217C 000BED5C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_PassiveWall_IASA(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->mv.co.passivewall.timer) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj))
        RETURN_IF(ftCo_80095328(gobj, NULL))
        RETURN_IF(ftCo_800D7100(gobj))
        RETURN_IF(ftCo_800C3B10(gobj))
        RETURN_IF(ftCo_80099A58(gobj))
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj))
        RETURN_IF(ftCo_800D705C(gobj))
        RETURN_IF(ftCo_800CB870(gobj))
        RETURN_IF(fp->cmd_vars[0] == 0)
        RETURN_IF(ftCo_800CEE70(gobj))
    } else {
        RETURN_IF(!ftCo_800C1E0C(fp))
        fp->mv.co.passivewall.x8 = true;
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C2180 000BED60  7C 08 02 A6 */	mflr r0
/* 800C2184 000BED64  90 01 00 04 */	stw r0, 4(r1)
/* 800C2188 000BED68  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C218C 000BED6C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C2190 000BED70  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C2194 000BED74  7C 7E 1B 78 */	mr r30, r3
/* 800C2198 000BED78  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C219C 000BED7C  80 1F 23 40 */	lwz r0, 0x2340(r31)
/* 800C21A0 000BED80  2C 00 00 00 */	cmpwi r0, 0
/* 800C21A4 000BED84  40 82 00 A8 */	bne lbl_800C224C
/* 800C21A8 000BED88  7F C3 F3 78 */	mr r3, r30
/* 800C21AC 000BED8C  4B FD 44 B1 */	bl ftCo_SpecialAir_CheckInput
/* 800C21B0 000BED90  2C 03 00 00 */	cmpwi r3, 0
/* 800C21B4 000BED94  40 82 00 F4 */	bne lbl_800C22A8
/* 800C21B8 000BED98  38 7E 00 00 */	addi r3, r30, 0
/* 800C21BC 000BED9C  38 80 00 00 */	li r4, 0
/* 800C21C0 000BEDA0  4B FD 31 69 */	bl ftCo_80095328
/* 800C21C4 000BEDA4  2C 03 00 00 */	cmpwi r3, 0
/* 800C21C8 000BEDA8  40 82 00 E0 */	bne lbl_800C22A8
/* 800C21CC 000BEDAC  7F C3 F3 78 */	mr r3, r30
/* 800C21D0 000BEDB0  48 01 4F 31 */	bl ftCo_800D7100
/* 800C21D4 000BEDB4  2C 03 00 00 */	cmpwi r3, 0
/* 800C21D8 000BEDB8  40 82 00 D0 */	bne lbl_800C22A8
/* 800C21DC 000BEDBC  7F C3 F3 78 */	mr r3, r30
/* 800C21E0 000BEDC0  48 00 19 31 */	bl ftCo_800C3B10
/* 800C21E4 000BEDC4  2C 03 00 00 */	cmpwi r3, 0
/* 800C21E8 000BEDC8  40 82 00 C0 */	bne lbl_800C22A8
/* 800C21EC 000BEDCC  7F C3 F3 78 */	mr r3, r30
/* 800C21F0 000BEDD0  4B FD 78 69 */	bl ftCo_80099A58
/* 800C21F4 000BEDD4  2C 03 00 00 */	cmpwi r3, 0
/* 800C21F8 000BEDD8  40 82 00 B0 */	bne lbl_800C22A8
/* 800C21FC 000BEDDC  7F C3 F3 78 */	mr r3, r30
/* 800C2200 000BEDE0  4B FC AB 69 */	bl ftCo_AttackAir_CheckItemThrowInput
/* 800C2204 000BEDE4  2C 03 00 00 */	cmpwi r3, 0
/* 800C2208 000BEDE8  40 82 00 A0 */	bne lbl_800C22A8
/* 800C220C 000BEDEC  7F C3 F3 78 */	mr r3, r30
/* 800C2210 000BEDF0  48 01 4E 4D */	bl ftCo_800D705C
/* 800C2214 000BEDF4  2C 03 00 00 */	cmpwi r3, 0
/* 800C2218 000BEDF8  40 82 00 90 */	bne lbl_800C22A8
/* 800C221C 000BEDFC  7F C3 F3 78 */	mr r3, r30
/* 800C2220 000BEE00  48 00 96 51 */	bl ftCo_800CB870
/* 800C2224 000BEE04  2C 03 00 00 */	cmpwi r3, 0
/* 800C2228 000BEE08  40 82 00 80 */	bne lbl_800C22A8
/* 800C222C 000BEE0C  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 800C2230 000BEE10  28 00 00 00 */	cmplwi r0, 0
/* 800C2234 000BEE14  41 82 00 74 */	beq lbl_800C22A8
/* 800C2238 000BEE18  7F C3 F3 78 */	mr r3, r30
/* 800C223C 000BEE1C  48 00 CC 35 */	bl ftCo_800CEE70
/* 800C2240 000BEE20  2C 03 00 00 */	cmpwi r3, 0
/* 800C2244 000BEE24  41 82 00 64 */	beq lbl_800C22A8
/* 800C2248 000BEE28  48 00 00 60 */	b lbl_800C22A8
lbl_800C224C:
/* 800C224C 000BEE2C  88 7F 06 7E */	lbz r3, 0x67e(r31)
/* 800C2250 000BEE30  3C 00 43 30 */	lis r0, 0x4330
/* 800C2254 000BEE34  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C2258 000BEE38  90 61 00 14 */	stw r3, 0x14(r1)
/* 800C225C 000BEE3C  C8 42 92 88 */	lfd f2, ftCo_804D8C68
/* 800C2260 000BEE40  90 01 00 10 */	stw r0, 0x10(r1)
/* 800C2264 000BEE44  C0 04 02 50 */	lfs f0, 0x250(r4)
/* 800C2268 000BEE48  C8 21 00 10 */	lfd f1, 0x10(r1)
/* 800C226C 000BEE4C  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C2270 000BEE50  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C2274 000BEE54  41 80 00 18 */	blt lbl_800C228C
/* 800C2278 000BEE58  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 800C227C 000BEE5C  C0 04 00 70 */	lfs f0, 0x70(r4)
/* 800C2280 000BEE60  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C2284 000BEE64  4C 41 13 82 */	cror 2, 1, 2
/* 800C2288 000BEE68  40 82 00 0C */	bne lbl_800C2294
lbl_800C228C:
/* 800C228C 000BEE6C  38 00 00 01 */	li r0, 1
/* 800C2290 000BEE70  48 00 00 08 */	b lbl_800C2298
lbl_800C2294:
/* 800C2294 000BEE74  38 00 00 00 */	li r0, 0
lbl_800C2298:
/* 800C2298 000BEE78  2C 00 00 00 */	cmpwi r0, 0
/* 800C229C 000BEE7C  41 82 00 0C */	beq lbl_800C22A8
/* 800C22A0 000BEE80  38 00 00 01 */	li r0, 1
/* 800C22A4 000BEE84  90 1F 23 48 */	stw r0, 0x2348(r31)
lbl_800C22A8:
/* 800C22A8 000BEE88  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C22AC 000BEE8C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C22B0 000BEE90  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C22B4 000BEE94  38 21 00 20 */	addi r1, r1, 0x20
/* 800C22B8 000BEE98  7C 08 03 A6 */	mtlr r0
/* 800C22BC 000BEE9C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_PassiveWall_Phys(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->mv.co.passivewall.timer) {
        ftCo_DatAttrs* co = &fp->co_attrs;
        ftCommon_8007D528(fp);
        if (fp->x221A_b4) {
            ftCommon_8007D4E4(fp);
        } else {
            ftCommon_8007D494(fp, co->grav, co->terminal_vel);
        }
        ftCommon_8007D140(fp, ftCo_804D8C70, ftCo_804D8C70,
                          fp->co_attrs.aerial_friction);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C22C0 000BEEA0  7C 08 02 A6 */	mflr r0
/* 800C22C4 000BEEA4  90 01 00 04 */	stw r0, 4(r1)
/* 800C22C8 000BEEA8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C22CC 000BEEAC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C22D0 000BEEB0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C22D4 000BEEB4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800C22D8 000BEEB8  80 03 23 40 */	lwz r0, 0x2340(r3)
/* 800C22DC 000BEEBC  3B E3 00 00 */	addi r31, r3, 0
/* 800C22E0 000BEEC0  2C 00 00 00 */	cmpwi r0, 0
/* 800C22E4 000BEEC4  40 82 00 4C */	bne lbl_800C2330
/* 800C22E8 000BEEC8  3B DF 01 10 */	addi r30, r31, 0x110
/* 800C22EC 000BEECC  38 7F 00 00 */	addi r3, r31, 0
/* 800C22F0 000BEED0  4B FB B2 39 */	bl ftCommon_8007D528
/* 800C22F4 000BEED4  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800C22F8 000BEED8  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800C22FC 000BEEDC  41 82 00 10 */	beq lbl_800C230C
/* 800C2300 000BEEE0  7F E3 FB 78 */	mr r3, r31
/* 800C2304 000BEEE4  4B FB B1 E1 */	bl ftCommon_8007D4E4
/* 800C2308 000BEEE8  48 00 00 14 */	b lbl_800C231C
lbl_800C230C:
/* 800C230C 000BEEEC  C0 3E 00 5C */	lfs f1, 0x5c(r30)
/* 800C2310 000BEEF0  7F E3 FB 78 */	mr r3, r31
/* 800C2314 000BEEF4  C0 5E 00 60 */	lfs f2, 0x60(r30)
/* 800C2318 000BEEF8  4B FB B1 7D */	bl ftCommon_8007D494
lbl_800C231C:
/* 800C231C 000BEEFC  C0 22 92 90 */	lfs f1, ftCo_804D8C70
/* 800C2320 000BEF00  7F E3 FB 78 */	mr r3, r31
/* 800C2324 000BEF04  C0 7F 01 80 */	lfs f3, 0x180(r31)
/* 800C2328 000BEF08  FC 40 08 90 */	fmr f2, f1
/* 800C232C 000BEF0C  4B FB AE 15 */	bl ftCommon_8007D140
lbl_800C2330:
/* 800C2330 000BEF10  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C2334 000BEF14  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C2338 000BEF18  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C233C 000BEF1C  38 21 00 20 */	addi r1, r1, 0x20
/* 800C2340 000BEF20  7C 08 03 A6 */	mtlr r0
/* 800C2344 000BEF24  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_PassiveWall_Coll(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->mv.co.passivewall.timer) {
        ft_80083318(gobj, ftCo_80096CC8, ft_80082B1C);
    } else {
        ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
    }
}
