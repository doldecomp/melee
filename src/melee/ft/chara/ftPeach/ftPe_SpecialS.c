#include <platform.h>
#include "forward.h"
#include "ft/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftPe_SpecialS.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftPeach/types.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <baselib/gobj.h>

#ifdef MUST_MATCH
static double const lbl_804D97F0 = -0.0078125;
#endif

/* 11C2F4 */ static void reset(HSD_GObj* gobj);
/* 11C430 */ static void doAirEnd0(HSD_GObj* gobj);
/* 11C7B0 */ static void enterAirStart(HSD_GObj* gobj);
/* 11C818 */ static void enterStart(HSD_GObj* gobj);
/* 11C9E0 */ static void enterAirJump(HSD_GObj* gobj);
/* 11CBBC */ static void enterAirEnd(HSD_GObj* gobj);
/* 11CC18 */ static void enterEnd(HSD_GObj* gobj);
/* 11CC74 */ static void enterEndSmash(HSD_GObj* gobj);
/* 11CD30 */ static void enterAirEndSmash(HSD_GObj* gobj);

static MotionFlags const start_mf =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
    Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;
static MotionFlags const end_mf = Ft_MF_SkipColAnim | Ft_MF_UpdateCmd;

static void reset(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->self_vel.x = 0;
    fp->x6A4_transNOffset.x = 0;
    if (fp->x673 < da->x30) {
        fp->x2070.x2072_b4 = true;
        fp->mv.pe.specials.x0 = true;
    } else {
        fp->mv.pe.specials.x0 = false;
    }
}

static inline void enter(HSD_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->cb.x21EC_callback = reset;
    fp->self_vel.y = 0;
    fp->gr_vel = da->x34 * fp->facing_dir;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftPe_SpecialS_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->cb.x21EC_callback = reset;
    fp->self_vel.y = 0;
    fp->gr_vel = da->x34 * fp->facing_dir;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSStart, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftPe_SpecialAirS_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->cb.x21EC_callback = reset;
    fp->self_vel.y = da->x40;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSStart, Ft_MF_None, 0, 1,
                              0, NULL);
    ftAnim_8006EBA4(gobj);
}

static void doAirEnd0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221C_b5) {
        Fighter* other_fp = GET_FIGHTER(fp->unk_gobj);
        if (other_fp != NULL) {
            switch (other_fp->kind) {
            case FTKIND_MARS:
            case FTKIND_EMBLEM: {
                FtMotionId msid = other_fp->motion_id;
                if (msid != 369 && msid != 371) {
                    return;
                }
                break;
            }
            case FTKIND_PEACH: {
                FtMotionId msid = other_fp->motion_id;
                if (msid != 365 && msid != 367) {
                    return;
                }
                break;
            }
            default:
                return;
            }
        }
    }
    fp->self_vel.x = 0;
    if (fp->self_vel.y >= 0) {
        fp->self_vel.y = 0;
    }
    fp->cmd_vars[2] = 1;
    enterAirEndSmash(gobj);
}

void ftPe_SpecialSStart_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftAnim_IsFramesRemaining(gobj)) {
        return;
    }
    if (fp->cmd_vars[0]) {
        enterEndSmash(gobj);
    } else {
        ftCommon_8007D5D4(fp);
        fp->cur_pos.x += -4 * fp->facing_dir * fp->x34_scale.y;
        fp->cur_pos.y += 3.5f * fp->x34_scale.y;
        enterAirJump(gobj);
    }
}

void ftPe_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->cmd_vars[0]) {
            enterAirEndSmash(gobj);
        } else {
            enterAirJump(gobj);
        }
    }
}

void ftPe_SpecialSStart_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialAirSStart_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialSStart_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    ftCommon_8007CA80(fp, da->x38 * fp->facing_dir, da->x3C * fp->facing_dir,
                      0);
    ftCommon_8007CB74(gobj);
}

void ftPe_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftPe_SpecialSStart_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8011C664 00119244  7C 08 02 A6 */	mflr r0
/* 8011C668 00119248  90 01 00 04 */	stw r0, 4(r1)
/* 8011C66C 0011924C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8011C670 00119250  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8011C674 00119254  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8011C678 00119258  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8011C67C 0011925C  7C 7D 1B 78 */	mr r29, r3
/* 8011C680 00119260  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011C684 00119264  3B DF 06 F0 */	addi r30, r31, 0x6f0
/* 8011C688 00119268  4B F6 61 19 */	bl ft_800827A0
/* 8011C68C 0011926C  2C 03 00 00 */	cmpwi r3, 0
/* 8011C690 00119270  40 82 00 0C */	bne lbl_8011C69C
/* 8011C694 00119274  7F A3 EB 78 */	mr r3, r29
/* 8011C698 00119278  48 00 01 19 */	bl enterAirStart
lbl_8011C69C:
/* 8011C69C 0011927C  80 7E 01 34 */	lwz r3, 0x134(r30)
/* 8011C6A0 00119280  54 60 05 33 */	rlwinm. r0, r3, 0, 0x14, 0x19
/* 8011C6A4 00119284  41 82 00 14 */	beq lbl_8011C6B8
/* 8011C6A8 00119288  C0 22 9E 10 */	lfs f1, lbl_804D97F0
/* 8011C6AC 0011928C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8011C6B0 00119290  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8011C6B4 00119294  41 82 00 1C */	beq lbl_8011C6D0
lbl_8011C6B8:
/* 8011C6B8 00119298  54 60 06 BF */	clrlwi. r0, r3, 0x1a
/* 8011C6BC 0011929C  41 82 00 24 */	beq lbl_8011C6E0
/* 8011C6C0 001192A0  C0 22 9E 04 */	lfs f1, 1.0f
/* 8011C6C4 001192A4  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8011C6C8 001192A8  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8011C6CC 001192AC  40 82 00 14 */	bne lbl_8011C6E0
lbl_8011C6D0:
/* 8011C6D0 001192B0  C0 02 9E 00 */	lfs f0, 0.0f
/* 8011C6D4 001192B4  38 00 00 01 */	li r0, 1
/* 8011C6D8 001192B8  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8011C6DC 001192BC  90 1F 22 00 */	stw r0, 0x2200(r31)
lbl_8011C6E0:
/* 8011C6E0 001192C0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8011C6E4 001192C4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8011C6E8 001192C8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8011C6EC 001192CC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8011C6F0 001192D0  38 21 00 20 */	addi r1, r1, 0x20
/* 8011C6F4 001192D4  7C 08 03 A6 */	mtlr r0
/* 8011C6F8 001192D8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftPe_SpecialSStart_Coll(HSD_GObj* gobj)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    if (!ft_800827A0(gobj)) {
        enterAirStart(gobj);
    }
    {
        u32 env_flags = coll->env_flags;
        if ((env_flags & MPCOLL_LEFTWALL && fp->facing_dir == -1) ||
            (env_flags & MPCOLL_RIGHTWALL && fp->facing_dir == +1))
        {
            fp->gr_vel = 0;
            fp->cmd_vars[0] = 1;
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftPe_SpecialAirSStart_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8011C6FC 001192DC  7C 08 02 A6 */	mflr r0
/* 8011C700 001192E0  90 01 00 04 */	stw r0, 4(r1)
/* 8011C704 001192E4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8011C708 001192E8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8011C70C 001192EC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8011C710 001192F0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8011C714 001192F4  7C 7D 1B 78 */	mr r29, r3
/* 8011C718 001192F8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011C71C 001192FC  3B DF 06 F0 */	addi r30, r31, 0x6f0
/* 8011C720 00119300  4B F6 55 ED */	bl ft_80081D0C
/* 8011C724 00119304  2C 03 00 00 */	cmpwi r3, 0
/* 8011C728 00119308  41 82 00 0C */	beq lbl_8011C734
/* 8011C72C 0011930C  7F A3 EB 78 */	mr r3, r29
/* 8011C730 00119310  48 00 00 E9 */	bl enterStart
lbl_8011C734:
/* 8011C734 00119314  80 1E 01 34 */	lwz r0, 0x134(r30)
/* 8011C738 00119318  54 00 04 65 */	rlwinm. r0, r0, 0, 0x11, 0x12
/* 8011C73C 0011931C  41 82 00 14 */	beq lbl_8011C750
/* 8011C740 00119320  C0 02 9E 00 */	lfs f0, 0.0f
/* 8011C744 00119324  38 00 00 01 */	li r0, 1
/* 8011C748 00119328  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8011C74C 0011932C  90 1F 22 00 */	stw r0, 0x2200(r31)
lbl_8011C750:
/* 8011C750 00119330  80 7E 01 34 */	lwz r3, 0x134(r30)
/* 8011C754 00119334  54 60 05 33 */	rlwinm. r0, r3, 0, 0x14, 0x19
/* 8011C758 00119338  41 82 00 14 */	beq lbl_8011C76C
/* 8011C75C 0011933C  C0 22 9E 10 */	lfs f1, lbl_804D97F0
/* 8011C760 00119340  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8011C764 00119344  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8011C768 00119348  41 82 00 1C */	beq lbl_8011C784
lbl_8011C76C:
/* 8011C76C 0011934C  54 60 06 BF */	clrlwi. r0, r3, 0x1a
/* 8011C770 00119350  41 82 00 24 */	beq lbl_8011C794
/* 8011C774 00119354  C0 22 9E 04 */	lfs f1, 1.0f
/* 8011C778 00119358  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8011C77C 0011935C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8011C780 00119360  40 82 00 14 */	bne lbl_8011C794
lbl_8011C784:
/* 8011C784 00119364  C0 02 9E 00 */	lfs f0, 0.0f
/* 8011C788 00119368  38 00 00 01 */	li r0, 1
/* 8011C78C 0011936C  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8011C790 00119370  90 1F 22 00 */	stw r0, 0x2200(r31)
lbl_8011C794:
/* 8011C794 00119374  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8011C798 00119378  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8011C79C 0011937C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8011C7A0 00119380  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8011C7A4 00119384  38 21 00 20 */	addi r1, r1, 0x20
/* 8011C7A8 00119388  7C 08 03 A6 */	mtlr r0
/* 8011C7AC 0011938C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftPe_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (ft_80081D0C(gobj)) {
        enterStart(gobj);
    }
    if (coll->env_flags & MPCOLL_CEIL) {
        fp->self_vel.y = 0;
        fp->cmd_vars[0] = 1;
    }
    {
        u32 env_flags = coll->env_flags;
        if ((env_flags & MPCOLL_LEFTWALL && fp->facing_dir == -1) ||
            (env_flags & MPCOLL_RIGHTWALL && fp->facing_dir == +1))
        {
            fp->self_vel.x = 0;
            fp->cmd_vars[0] = 1;
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void enterAirStart(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8011C7B0 00119390  7C 08 02 A6 */	mflr r0
/* 8011C7B4 00119394  90 01 00 04 */	stw r0, 4(r1)
/* 8011C7B8 00119398  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011C7BC 0011939C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8011C7C0 001193A0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8011C7C4 001193A4  7C 7E 1B 78 */	mr r30, r3
/* 8011C7C8 001193A8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011C7CC 001193AC  C0 02 9E 00 */	lfs f0, 0.0f
/* 8011C7D0 001193B0  7F E3 FB 78 */	mr r3, r31
/* 8011C7D4 001193B4  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8011C7D8 001193B8  4B F6 0D FD */	bl ftCommon_8007D5D4
/* 8011C7DC 001193BC  3C 80 0C 4C */	lis r4, 0x0C4C5084@ha
/* 8011C7E0 001193C0  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8011C7E4 001193C4  C0 42 9E 04 */	lfs f2, 1.0f
/* 8011C7E8 001193C8  7F C3 F3 78 */	mr r3, r30
/* 8011C7EC 001193CC  C0 62 9E 00 */	lfs f3, 0.0f
/* 8011C7F0 001193D0  38 A4 50 84 */	addi r5, r4, 0x0C4C5084@l
/* 8011C7F4 001193D4  38 80 01 65 */	li r4, 0x165
/* 8011C7F8 001193D8  38 C0 00 00 */	li r6, 0
/* 8011C7FC 001193DC  4B F4 CB B1 */	bl Fighter_ChangeMotionState
/* 8011C800 001193E0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011C804 001193E4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8011C808 001193E8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8011C80C 001193EC  38 21 00 18 */	addi r1, r1, 0x18
/* 8011C810 001193F0  7C 08 03 A6 */	mtlr r0
/* 8011C814 001193F4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void enterAirStart(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = 0;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSStart, start_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void enterStart(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8011C818 001193F8  7C 08 02 A6 */	mflr r0
/* 8011C81C 001193FC  90 01 00 04 */	stw r0, 4(r1)
/* 8011C820 00119400  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011C824 00119404  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8011C828 00119408  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8011C82C 0011940C  7C 7E 1B 78 */	mr r30, r3
/* 8011C830 00119410  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011C834 00119414  7F E3 FB 78 */	mr r3, r31
/* 8011C838 00119418  4B F6 0F C5 */	bl ftCommon_8007D7FC
/* 8011C83C 0011941C  3C 80 0C 4C */	lis r4, 0x0C4C5084@ha
/* 8011C840 00119420  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8011C844 00119424  C0 42 9E 04 */	lfs f2, 1.0f
/* 8011C848 00119428  7F C3 F3 78 */	mr r3, r30
/* 8011C84C 0011942C  C0 62 9E 00 */	lfs f3, 0.0f
/* 8011C850 00119430  38 A4 50 84 */	addi r5, r4, 0x0C4C5084@l
/* 8011C854 00119434  38 80 01 62 */	li r4, 0x162
/* 8011C858 00119438  38 C0 00 00 */	li r6, 0
/* 8011C85C 0011943C  4B F4 CB 51 */	bl Fighter_ChangeMotionState
/* 8011C860 00119440  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011C864 00119444  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8011C868 00119448  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8011C86C 0011944C  38 21 00 18 */	addi r1, r1, 0x18
/* 8011C870 00119450  7C 08 03 A6 */	mtlr r0
/* 8011C874 00119454  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void enterStart(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSStart, start_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}
#endif

void ftPe_SpecialAirSJump_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    if (GET_FIGHTER(gobj)->cmd_vars[3] != 0 || !ftAnim_IsFramesRemaining(gobj))
    {
        enterAirEndSmash(gobj);
    }
}

void ftPe_SpecialAirSJump_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialAirSJump_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[1]) {
        ftCommon_8007CE94(fp, da->x54);
    }
    ftCommon_8007D494(fp, fp->cmd_vars[1] ? da->x58 : da->x50, da->x5C);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftPe_SpecialAirSJump_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8011C93C 0011951C  7C 08 02 A6 */	mflr r0
/* 8011C940 00119520  90 01 00 04 */	stw r0, 4(r1)
/* 8011C944 00119524  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8011C948 00119528  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8011C94C 0011952C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8011C950 00119530  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8011C954 00119534  7C 7D 1B 78 */	mr r29, r3
/* 8011C958 00119538  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8011C95C 0011953C  3B E4 00 00 */	addi r31, r4, 0
/* 8011C960 00119540  3B C4 06 F0 */	addi r30, r4, 0x6f0
/* 8011C964 00119544  4B F6 53 A9 */	bl ft_80081D0C
/* 8011C968 00119548  2C 03 00 00 */	cmpwi r3, 0
/* 8011C96C 0011954C  41 82 00 14 */	beq lbl_8011C980
/* 8011C970 00119550  7F E3 FB 78 */	mr r3, r31
/* 8011C974 00119554  4B F6 0E 89 */	bl ftCommon_8007D7FC
/* 8011C978 00119558  7F A3 EB 78 */	mr r3, r29
/* 8011C97C 0011955C  48 00 02 F9 */	bl enterEndSmash
lbl_8011C980:
/* 8011C980 00119560  80 7E 01 34 */	lwz r3, 0x134(r30)
/* 8011C984 00119564  54 60 05 33 */	rlwinm. r0, r3, 0, 0x14, 0x19
/* 8011C988 00119568  41 82 00 14 */	beq lbl_8011C99C
/* 8011C98C 0011956C  C0 22 9E 10 */	lfs f1, lbl_804D97F0
/* 8011C990 00119570  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8011C994 00119574  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8011C998 00119578  41 82 00 1C */	beq lbl_8011C9B4
lbl_8011C99C:
/* 8011C99C 0011957C  54 60 06 BF */	clrlwi. r0, r3, 0x1a
/* 8011C9A0 00119580  41 82 00 24 */	beq lbl_8011C9C4
/* 8011C9A4 00119584  C0 22 9E 04 */	lfs f1, 1.0f
/* 8011C9A8 00119588  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8011C9AC 0011958C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8011C9B0 00119590  40 82 00 14 */	bne lbl_8011C9C4
lbl_8011C9B4:
/* 8011C9B4 00119594  38 00 00 01 */	li r0, 1
/* 8011C9B8 00119598  90 1F 22 08 */	stw r0, 0x2208(r31)
/* 8011C9BC 0011959C  7F A3 EB 78 */	mr r3, r29
/* 8011C9C0 001195A0  48 00 03 71 */	bl enterAirEndSmash
lbl_8011C9C4:
/* 8011C9C4 001195A4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8011C9C8 001195A8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8011C9CC 001195AC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8011C9D0 001195B0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8011C9D4 001195B4  38 21 00 20 */	addi r1, r1, 0x20
/* 8011C9D8 001195B8  7C 08 03 A6 */	mtlr r0
/* 8011C9DC 001195BC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftPe_SpecialAirSJump_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        enterEndSmash(gobj);
    }
    {
        u32 env_flags = coll->env_flags;
        if ((env_flags & MPCOLL_LEFTWALL && fp->facing_dir == -1) ||
            (env_flags & MPCOLL_RIGHTWALL && fp->facing_dir == +1))
        {
            fp->cmd_vars[2] = 1;
            enterAirEndSmash(gobj);
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void enterAirJump(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8011C9E0 001195C0  7C 08 02 A6 */	mflr r0
/* 8011C9E4 001195C4  90 01 00 04 */	stw r0, 4(r1)
/* 8011C9E8 001195C8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8011C9EC 001195CC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8011C9F0 001195D0  7C 7F 1B 78 */	mr r31, r3
/* 8011C9F4 001195D4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8011C9F8 001195D8  80 05 23 40 */	lwz r0, 0x2340(r5)
/* 8011C9FC 001195DC  80 65 02 D4 */	lwz r3, 0x2d4(r5)
/* 8011CA00 001195E0  2C 00 00 00 */	cmpwi r0, 0
/* 8011CA04 001195E4  41 82 00 18 */	beq lbl_8011CA1C
/* 8011CA08 001195E8  C0 23 00 48 */	lfs f1, 0x48(r3)
/* 8011CA0C 001195EC  C0 05 00 2C */	lfs f0, 0x2c(r5)
/* 8011CA10 001195F0  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011CA14 001195F4  D0 05 00 80 */	stfs f0, 0x80(r5)
/* 8011CA18 001195F8  48 00 00 14 */	b lbl_8011CA2C
lbl_8011CA1C:
/* 8011CA1C 001195FC  C0 23 00 44 */	lfs f1, 0x44(r3)
/* 8011CA20 00119600  C0 05 00 2C */	lfs f0, 0x2c(r5)
/* 8011CA24 00119604  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011CA28 00119608  D0 05 00 80 */	stfs f0, 0x80(r5)
lbl_8011CA2C:
/* 8011CA2C 0011960C  C0 03 00 4C */	lfs f0, 0x4c(r3)
/* 8011CA30 00119610  38 7F 00 00 */	addi r3, r31, 0
/* 8011CA34 00119614  38 80 01 68 */	li r4, 0x168
/* 8011CA38 00119618  D0 05 00 84 */	stfs f0, 0x84(r5)
/* 8011CA3C 0011961C  38 A0 00 00 */	li r5, 0
/* 8011CA40 00119620  38 C0 00 00 */	li r6, 0
/* 8011CA44 00119624  C0 22 9E 00 */	lfs f1, 0.0f
/* 8011CA48 00119628  C0 42 9E 04 */	lfs f2, 1.0f
/* 8011CA4C 0011962C  FC 60 08 90 */	fmr f3, f1
/* 8011CA50 00119630  4B F4 C9 5D */	bl Fighter_ChangeMotionState
/* 8011CA54 00119634  3C 60 80 08 */	lis r3, ftCommon_8007F76C@ha
/* 8011CA58 00119638  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8011CA5C 0011963C  38 03 F7 6C */	addi r0, r3, ftCommon_8007F76C@l
/* 8011CA60 00119640  3C 60 80 12 */	lis r3, doAirEnd0@ha
/* 8011CA64 00119644  90 04 21 F8 */	stw r0, 0x21f8(r4)
/* 8011CA68 00119648  38 03 C4 30 */	addi r0, r3, doAirEnd0@l
/* 8011CA6C 0011964C  90 04 21 F4 */	stw r0, 0x21f4(r4)
/* 8011CA70 00119650  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8011CA74 00119654  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8011CA78 00119658  38 21 00 20 */	addi r1, r1, 0x20
/* 8011CA7C 0011965C  7C 08 03 A6 */	mtlr r0
/* 8011CA80 00119660  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else
static void setCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21F8_callback = ftCommon_8007F76C;
    fp->cb.x21F4_callback = doAirEnd0;
}

static void enterAirJump(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->mv.pe.specials.x0) {
        fp->self_vel.x = da->specials_smash_vel_x * fp->facing_dir;
    } else {
        fp->self_vel.x = da->specials_vel_x * fp->facing_dir;
    }
    fp->self_vel.y = da->specials_vel_y;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSJump, Ft_MF_None, 0, 1,
                              0, NULL);
    setCallbacks(gobj);
}
#endif

void ftPe_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPe_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftPe_SpecialSEnd_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialAirSEnd_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPe_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPe_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        enterAirEnd(gobj);
    }
}

void ftPe_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        enterEnd(gobj);
    }
}

void enterAirEnd(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSEnd_0, end_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void enterEnd(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSEnd, end_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

static void doPostEnd(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[38] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[2]) {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &vec);
        vec.z = 0;
        {
            float facing_dir = fp->facing_dir;
            it_802BD158(gobj, &vec, fp->mv.pe.specials.x0, facing_dir);
            fp->self_vel.x = da->specials_end_vel_x * fp->facing_dir;
            fp->self_vel.y = da->specials_end_vel_y;
        }
    }
    fp->cb.x21F8_callback = ftCommon_8007F7B4;
}

static void enterEndSmash(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSEnd, Ft_MF_None, 0, 1, 0,
                              NULL);
    doPostEnd(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void enterAirEndSmash(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8011CD30 00119910  7C 08 02 A6 */	mflr r0
/* 8011CD34 00119914  90 01 00 04 */	stw r0, 4(r1)
/* 8011CD38 00119918  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8011CD3C 0011991C  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8011CD40 00119920  93 C1 00 50 */	stw r30, 0x50(r1)
/* 8011CD44 00119924  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 8011CD48 00119928  7C 7D 1B 78 */	mr r29, r3
/* 8011CD4C 0011992C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8011CD50 00119930  80 83 02 D4 */	lwz r4, 0x2d4(r3)
/* 8011CD54 00119934  C0 23 00 80 */	lfs f1, 0x80(r3)
/* 8011CD58 00119938  C0 04 00 68 */	lfs f0, 0x68(r4)
/* 8011CD5C 0011993C  EC 01 00 24 */	fdivs f0, f1, f0
/* 8011CD60 00119940  D0 03 00 80 */	stfs f0, 0x80(r3)
/* 8011CD64 00119944  C0 23 00 84 */	lfs f1, 0x84(r3)
/* 8011CD68 00119948  C0 04 00 6C */	lfs f0, 0x6c(r4)
/* 8011CD6C 0011994C  EC 01 00 24 */	fdivs f0, f1, f0
/* 8011CD70 00119950  D0 03 00 84 */	stfs f0, 0x84(r3)
/* 8011CD74 00119954  80 03 22 08 */	lwz r0, 0x2208(r3)
/* 8011CD78 00119958  28 00 00 00 */	cmplwi r0, 0
/* 8011CD7C 0011995C  41 82 00 28 */	beq lbl_8011CDA4
/* 8011CD80 00119960  C0 22 9E 00 */	lfs f1, 0.0f
/* 8011CD84 00119964  7F A3 EB 78 */	mr r3, r29
/* 8011CD88 00119968  C0 42 9E 04 */	lfs f2, 1.0f
/* 8011CD8C 0011996C  38 80 01 67 */	li r4, 0x167
/* 8011CD90 00119970  FC 60 08 90 */	fmr f3, f1
/* 8011CD94 00119974  38 A0 00 00 */	li r5, 0
/* 8011CD98 00119978  38 C0 00 00 */	li r6, 0
/* 8011CD9C 0011997C  4B F4 C6 11 */	bl Fighter_ChangeMotionState
/* 8011CDA0 00119980  48 00 00 24 */	b lbl_8011CDC4
lbl_8011CDA4:
/* 8011CDA4 00119984  C0 22 9E 00 */	lfs f1, 0.0f
/* 8011CDA8 00119988  7F A3 EB 78 */	mr r3, r29
/* 8011CDAC 0011998C  C0 42 9E 04 */	lfs f2, 1.0f
/* 8011CDB0 00119990  38 80 01 66 */	li r4, 0x166
/* 8011CDB4 00119994  FC 60 08 90 */	fmr f3, f1
/* 8011CDB8 00119998  38 A0 00 00 */	li r5, 0
/* 8011CDBC 0011999C  38 C0 00 00 */	li r6, 0
/* 8011CDC0 001199A0  4B F4 C5 ED */	bl Fighter_ChangeMotionState
lbl_8011CDC4:
/* 8011CDC4 001199A4  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 8011CDC8 001199A8  80 1E 22 08 */	lwz r0, 0x2208(r30)
/* 8011CDCC 001199AC  83 FE 02 D4 */	lwz r31, 0x2d4(r30)
/* 8011CDD0 001199B0  28 00 00 00 */	cmplwi r0, 0
/* 8011CDD4 001199B4  41 82 00 4C */	beq lbl_8011CE20
/* 8011CDD8 001199B8  80 7E 05 E8 */	lwz r3, 0x5e8(r30)
/* 8011CDDC 001199BC  38 A1 00 38 */	addi r5, r1, 0x38
/* 8011CDE0 001199C0  38 80 00 00 */	li r4, 0
/* 8011CDE4 001199C4  80 63 00 40 */	lwz r3, 0x40(r3)
/* 8011CDE8 001199C8  4B EE E3 E5 */	bl lb_8000B1CC
/* 8011CDEC 001199CC  C0 02 9E 00 */	lfs f0, 0.0f
/* 8011CDF0 001199D0  38 7D 00 00 */	addi r3, r29, 0
/* 8011CDF4 001199D4  38 81 00 38 */	addi r4, r1, 0x38
/* 8011CDF8 001199D8  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 8011CDFC 001199DC  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 8011CE00 001199E0  80 BE 23 40 */	lwz r5, 0x2340(r30)
/* 8011CE04 001199E4  48 1A 03 55 */	bl it_802BD158
/* 8011CE08 001199E8  C0 3F 00 60 */	lfs f1, 0x60(r31)
/* 8011CE0C 001199EC  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 8011CE10 001199F0  EC 01 00 32 */	fmuls f0, f1, f0
/* 8011CE14 001199F4  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 8011CE18 001199F8  C0 1F 00 64 */	lfs f0, 0x64(r31)
/* 8011CE1C 001199FC  D0 1E 00 84 */	stfs f0, 0x84(r30)
lbl_8011CE20:
/* 8011CE20 00119A00  3C 60 80 08 */	lis r3, ftCommon_8007F7B4@ha
/* 8011CE24 00119A04  38 03 F7 B4 */	addi r0, r3, ftCommon_8007F7B4@l
/* 8011CE28 00119A08  90 1E 21 F8 */	stw r0, 0x21f8(r30)
/* 8011CE2C 00119A0C  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8011CE30 00119A10  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 8011CE34 00119A14  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 8011CE38 00119A18  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 8011CE3C 00119A1C  38 21 00 58 */	addi r1, r1, 0x58
/* 8011CE40 00119A20  7C 08 03 A6 */	mtlr r0
/* 8011CE44 00119A24  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void enterAirEndSmash(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->self_vel.x /= da->x68;
    fp->self_vel.y /= da->x6C;
    if (fp->cmd_vars[2] != 0U) {
        Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSEnd_1, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSEnd_0, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
    }
    doPostEnd(gobj);
}
#endif
