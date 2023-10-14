#include <platform.h>
#include "ft/forward.h"

#include "ftCo_Shouldered.h"

#include "ftCo_Damage.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "lb/lb_00B0.h"
#include "pl/pl_0371.h"

#include <common_structs.h>
#include <placeholder.h>

#ifdef MWERKS_GEKKO
#ifdef WIP
#pragma force_active on
#endif
float const ftCo_804D8750 = 0;
float const ftCo_804D8754 = 1;
double const ftCo_804D8758 = S32_TO_F32;
#endif

/* 09C744 */ static void ftCo_8009C744(ftCo_GObj* gobj);

ASM void ftCo_8009C5A4(ftCo_GObj* gobj, FtMotionId msid)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->motion_id != msid || msid != ftCo_MS_ShoulderedWait) {
        Fighter_ChangeMotionState(
            gobj, msid, fp->x2222_b6 ? Ft_MF_FreezeState : Ft_MF_None, 0, 1, 0,
            fp->victim_gobj);
        ftCommon_8007E2FC(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        fp->accessory1_cb = ftCo_800DB464;
    }
}
#else /* clang-format off */
{ nofralloc
/* 8009C5A4 00099184  7C 08 02 A6 */	mflr r0
/* 8009C5A8 00099188  90 01 00 04 */	stw r0, 4(r1)
/* 8009C5AC 0009918C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8009C5B0 00099190  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8009C5B4 00099194  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8009C5B8 00099198  7C 7E 1B 78 */	mr r30, r3
/* 8009C5BC 0009919C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8009C5C0 000991A0  80 03 00 10 */	lwz r0, 0x10(r3)
/* 8009C5C4 000991A4  3B E3 00 00 */	addi r31, r3, 0
/* 8009C5C8 000991A8  7C 00 20 00 */	cmpw r0, r4
/* 8009C5CC 000991AC  40 82 00 0C */	bne lbl_8009C5D8
/* 8009C5D0 000991B0  2C 04 01 0A */	cmpwi r4, 0x10a
/* 8009C5D4 000991B4  41 82 00 54 */	beq lbl_8009C628
lbl_8009C5D8:
/* 8009C5D8 000991B8  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 8009C5DC 000991BC  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8009C5E0 000991C0  41 82 00 0C */	beq lbl_8009C5EC
/* 8009C5E4 000991C4  3C A0 00 20 */	lis r5, 0x20
/* 8009C5E8 000991C8  48 00 00 08 */	b lbl_8009C5F0
lbl_8009C5EC:
/* 8009C5EC 000991CC  38 A0 00 00 */	li r5, 0
lbl_8009C5F0:
/* 8009C5F0 000991D0  C0 22 8D 70 */	lfs f1, ftCo_804D8750
/* 8009C5F4 000991D4  7F C3 F3 78 */	mr r3, r30
/* 8009C5F8 000991D8  C0 42 8D 74 */	lfs f2, ftCo_804D8754
/* 8009C5FC 000991DC  FC 60 08 90 */	fmr f3, f1
/* 8009C600 000991E0  80 DF 1A 58 */	lwz r6, 0x1a58(r31)
/* 8009C604 000991E4  4B FC CD A9 */	bl Fighter_ChangeMotionState
/* 8009C608 000991E8  7F C3 F3 78 */	mr r3, r30
/* 8009C60C 000991EC  4B FE 1C F1 */	bl ftCommon_8007E2FC
/* 8009C610 000991F0  38 7F 00 00 */	addi r3, r31, 0
/* 8009C614 000991F4  38 80 01 FF */	li r4, 0x1ff
/* 8009C618 000991F8  4B FE 1C DD */	bl ftCommon_8007E2F4
/* 8009C61C 000991FC  3C 60 80 0E */	lis r3, ftCo_800DB464@ha
/* 8009C620 00099200  38 03 B4 64 */	addi r0, r3, ftCo_800DB464@l
/* 8009C624 00099204  90 1F 21 B0 */	stw r0, 0x21b0(r31)
lbl_8009C628:
/* 8009C628 00099208  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8009C62C 0009920C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8009C630 00099210  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8009C634 00099214  38 21 00 20 */	addi r1, r1, 0x20
/* 8009C638 00099218  7C 08 03 A6 */	mtlr r0
/* 8009C63C 0009921C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_8009C640(ftCo_GObj* gobj, FtMotionId msid)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007DBCC(fp, 0,
                      (int) (fp->dmg.x1830_percent * p_ftCommonData->x4A0 +
                             p_ftCommonData->x4A4));
    fp->mv.co.shouldered.x0 = 0;
    fp->mv.co.shouldered.x4 = 0;
    ftCo_8009C5A4(gobj, msid);
}
#else /* clang-format off */
{ nofralloc
/* 8009C640 00099220  7C 08 02 A6 */	mflr r0
/* 8009C644 00099224  90 01 00 04 */	stw r0, 4(r1)
/* 8009C648 00099228  3C 00 43 30 */	lis r0, 0x4330
/* 8009C64C 0009922C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8009C650 00099230  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8009C654 00099234  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8009C658 00099238  7C 9E 23 78 */	mr r30, r4
/* 8009C65C 0009923C  38 80 00 00 */	li r4, 0
/* 8009C660 00099240  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8009C664 00099244  7C 7D 1B 78 */	mr r29, r3
/* 8009C668 00099248  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009C66C 0009924C  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 8009C670 00099250  C0 43 04 A0 */	lfs f2, 0x4a0(r3)
/* 8009C674 00099254  C0 03 04 A4 */	lfs f0, 0x4a4(r3)
/* 8009C678 00099258  7F E3 FB 78 */	mr r3, r31
/* 8009C67C 0009925C  C0 7F 18 30 */	lfs f3, 0x1830(r31)
/* 8009C680 00099260  C8 22 8D 78 */	lfd f1, ftCo_804D8758
/* 8009C684 00099264  EC 03 00 BA */	fmadds f0, f3, f2, f0
/* 8009C688 00099268  FC 00 00 1E */	fctiwz f0, f0
/* 8009C68C 0009926C  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 8009C690 00099270  80 A1 00 24 */	lwz r5, 0x24(r1)
/* 8009C694 00099274  6C A5 80 00 */	xoris r5, r5, 0x8000
/* 8009C698 00099278  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 8009C69C 0009927C  90 01 00 18 */	stw r0, 0x18(r1)
/* 8009C6A0 00099280  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8009C6A4 00099284  EC 20 08 28 */	fsubs f1, f0, f1
/* 8009C6A8 00099288  4B FE 15 25 */	bl ftCommon_8007DBCC
/* 8009C6AC 0009928C  C0 02 8D 70 */	lfs f0, ftCo_804D8750
/* 8009C6B0 00099290  38 00 00 00 */	li r0, 0
/* 8009C6B4 00099294  D0 1F 23 40 */	stfs f0, 0x2340(r31)
/* 8009C6B8 00099298  90 1F 23 44 */	stw r0, 0x2344(r31)
/* 8009C6BC 0009929C  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 8009C6C0 000992A0  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8009C6C4 000992A4  7C 00 F0 00 */	cmpw r0, r30
/* 8009C6C8 000992A8  40 82 00 0C */	bne lbl_8009C6D4
/* 8009C6CC 000992AC  2C 1E 01 0A */	cmpwi r30, 0x10a
/* 8009C6D0 000992B0  41 82 00 58 */	beq lbl_8009C728
lbl_8009C6D4:
/* 8009C6D4 000992B4  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 8009C6D8 000992B8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8009C6DC 000992BC  41 82 00 0C */	beq lbl_8009C6E8
/* 8009C6E0 000992C0  3C A0 00 20 */	lis r5, 0x20
/* 8009C6E4 000992C4  48 00 00 08 */	b lbl_8009C6EC
lbl_8009C6E8:
/* 8009C6E8 000992C8  38 A0 00 00 */	li r5, 0
lbl_8009C6EC:
/* 8009C6EC 000992CC  C0 22 8D 70 */	lfs f1, ftCo_804D8750
/* 8009C6F0 000992D0  7F A3 EB 78 */	mr r3, r29
/* 8009C6F4 000992D4  C0 42 8D 74 */	lfs f2, ftCo_804D8754
/* 8009C6F8 000992D8  7F C4 F3 78 */	mr r4, r30
/* 8009C6FC 000992DC  FC 60 08 90 */	fmr f3, f1
/* 8009C700 000992E0  80 DF 1A 58 */	lwz r6, 0x1a58(r31)
/* 8009C704 000992E4  4B FC CC A9 */	bl Fighter_ChangeMotionState
/* 8009C708 000992E8  7F A3 EB 78 */	mr r3, r29
/* 8009C70C 000992EC  4B FE 1B F1 */	bl ftCommon_8007E2FC
/* 8009C710 000992F0  38 7F 00 00 */	addi r3, r31, 0
/* 8009C714 000992F4  38 80 01 FF */	li r4, 0x1ff
/* 8009C718 000992F8  4B FE 1B DD */	bl ftCommon_8007E2F4
/* 8009C71C 000992FC  3C 60 80 0E */	lis r3, ftCo_800DB464@ha
/* 8009C720 00099300  38 03 B4 64 */	addi r0, r3, ftCo_800DB464@l
/* 8009C724 00099304  90 1F 21 B0 */	stw r0, 0x21b0(r31)
lbl_8009C728:
/* 8009C728 00099308  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8009C72C 0009930C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8009C730 00099310  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8009C734 00099314  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8009C738 00099318  38 21 00 38 */	addi r1, r1, 0x38
/* 8009C73C 0009931C  7C 08 03 A6 */	mtlr r0
/* 8009C740 00099320  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static ASM void ftCo_8009C744(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_GObj* vic_gobj = fp->victim_gobj;
    ftCo_Fighter* vic_fp = vic_gobj->user_data;
    Vec3 pos;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12] = { 0 };
#endif
    HitCapsule* hit = &vic_fp->xDF4[1];
    ftCo_800DC920(vic_gobj, gobj);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint, NULL,
                &pos);
    fp->dmg.kb_applied = ftColl_80079C70(fp, vic_fp, hit, hit->x8);
    fp->dmg.x1848_kb_angle = hit->kb_angle;
    fp->dmg.x1844_direction = -vic_fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 1;
    fp->dmg.x1854_collpos = pos;
    fp->dmg.x1860 = hit->element;
    ftColl_80078710(gobj);
    Fighter_UnkTakeDamage_8006CC30(fp, hit->damage);
    ftCo_Damage_CalcKnockback(fp);
    ftCo_8008E908(gobj, 0);
}
#else /* clang-format off */
{ nofralloc
/* 8009C744 00099324  7C 08 02 A6 */	mflr r0
/* 8009C748 00099328  90 01 00 04 */	stw r0, 4(r1)
/* 8009C74C 0009932C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8009C750 00099330  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 8009C754 00099334  7C 7B 1B 78 */	mr r27, r3
/* 8009C758 00099338  7F 64 DB 78 */	mr r4, r27
/* 8009C75C 0009933C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009C760 00099340  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 8009C764 00099344  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8009C768 00099348  7C 7E 1B 78 */	mr r30, r3
/* 8009C76C 0009934C  3B 9D 0F 2C */	addi r28, r29, 0xf2c
/* 8009C770 00099350  48 04 01 B1 */	bl ftCo_800DC920
/* 8009C774 00099354  38 7F 00 00 */	addi r3, r31, 0
/* 8009C778 00099358  38 80 00 02 */	li r4, 2
/* 8009C77C 0009935C  4B FD 88 91 */	bl ftParts_8007500C
/* 8009C780 00099360  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8009C784 00099364  54 60 20 36 */	slwi r0, r3, 4
/* 8009C788 00099368  38 A1 00 14 */	addi r5, r1, 0x14
/* 8009C78C 0009936C  7C 64 00 2E */	lwzx r3, r4, r0
/* 8009C790 00099370  38 80 00 00 */	li r4, 0
/* 8009C794 00099374  4B F6 EA 39 */	bl lb_8000B1CC
/* 8009C798 00099378  80 DC 00 08 */	lwz r6, 8(r28)
/* 8009C79C 0009937C  38 7F 00 00 */	addi r3, r31, 0
/* 8009C7A0 00099380  38 9D 00 00 */	addi r4, r29, 0
/* 8009C7A4 00099384  38 BC 00 00 */	addi r5, r28, 0
/* 8009C7A8 00099388  4B FD D4 C9 */	bl ftColl_80079C70
/* 8009C7AC 0009938C  D0 3F 18 50 */	stfs f1, 0x1850(r31)
/* 8009C7B0 00099390  38 00 00 01 */	li r0, 1
/* 8009C7B4 00099394  38 7E 00 00 */	addi r3, r30, 0
/* 8009C7B8 00099398  80 DC 00 20 */	lwz r6, 0x20(r28)
/* 8009C7BC 0009939C  38 9B 00 00 */	addi r4, r27, 0
/* 8009C7C0 000993A0  38 BF 18 44 */	addi r5, r31, 0x1844
/* 8009C7C4 000993A4  90 DF 18 48 */	stw r6, 0x1848(r31)
/* 8009C7C8 000993A8  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 8009C7CC 000993AC  FC 00 00 50 */	fneg f0, f0
/* 8009C7D0 000993B0  D0 1F 18 44 */	stfs f0, 0x1844(r31)
/* 8009C7D4 000993B4  90 1F 18 4C */	stw r0, 0x184c(r31)
/* 8009C7D8 000993B8  80 C1 00 14 */	lwz r6, 0x14(r1)
/* 8009C7DC 000993BC  80 01 00 18 */	lwz r0, 0x18(r1)
/* 8009C7E0 000993C0  90 DF 18 54 */	stw r6, 0x1854(r31)
/* 8009C7E4 000993C4  90 1F 18 58 */	stw r0, 0x1858(r31)
/* 8009C7E8 000993C8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009C7EC 000993CC  90 1F 18 5C */	stw r0, 0x185c(r31)
/* 8009C7F0 000993D0  80 1C 00 30 */	lwz r0, 0x30(r28)
/* 8009C7F4 000993D4  90 1F 18 60 */	stw r0, 0x1860(r31)
/* 8009C7F8 000993D8  4B FD BF 19 */	bl ftColl_80078710
/* 8009C7FC 000993DC  7F E3 FB 78 */	mr r3, r31
/* 8009C800 000993E0  C0 3C 00 0C */	lfs f1, 0xc(r28)
/* 8009C804 000993E4  4B FD 04 2D */	bl Fighter_UnkTakeDamage_8006CC30
/* 8009C808 000993E8  7F E3 FB 78 */	mr r3, r31
/* 8009C80C 000993EC  4B FF 11 25 */	bl ftCo_Damage_CalcKnockback
/* 8009C810 000993F0  7F 63 DB 78 */	mr r3, r27
/* 8009C814 000993F4  C0 22 8D 70 */	lfs f1, ftCo_804D8750
/* 8009C818 000993F8  4B FF 20 F1 */	bl ftCo_8008E908
/* 8009C81C 000993FC  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 8009C820 00099400  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8009C824 00099404  38 21 00 38 */	addi r1, r1, 0x38
/* 8009C828 00099408  7C 08 03 A6 */	mtlr r0
/* 8009C82C 0009940C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline float inlineA0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    return fp->ground_or_air == GA_Ground
               ? p_ftCommonData->x4A8
               : p_ftCommonData->x4A8 * p_ftCommonData->x4AC;
}

ASM void ftCo_Shouldered_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.shouldered.x4 = ftCommon_8007DC08(fp, inlineA0(fp->victim_gobj));
    if (fp->x1A4C <= 0) {
        HitCapsule* hit;
        ftCo_GObj* gobj1 = fp->victim_gobj;
        ftCo_Fighter* fp1 = gobj1->user_data;
        ftCo_GObj* gobj2 = fp1->victim_gobj;
        {
            ftCo_Fighter* fp1 = gobj1->user_data;
            ftCo_Fighter* fp2 = gobj2->user_data;
            Vec3 pos;
            hit = &fp2->xDF4[1];
            lb_8000B1CC(
                fp1->parts[(ftParts_8007500C(fp1, FtPart_TransN2))].joint,
                NULL, &pos);
            fp1->dmg.kb_applied = ftColl_80079C70(fp1, fp2, hit, hit->x8);
            fp1->dmg.x1848_kb_angle = hit->kb_angle;
            fp1->dmg.x1844_direction = fp1->facing_dir;
            fp1->dmg.x184c_damaged_hurtbox = 1;
            fp2->dmg.x1854_collpos = pos;
            fp1->dmg.x1860 = hit->element;
            ftColl_80078710(gobj);
            Fighter_UnkTakeDamage_8006CC30(fp1, hit->damage);
            ftCo_Damage_CalcKnockback(fp1);
            ftCo_8008E908(gobj1, 0);
        }
        ftCo_8009C744(gobj);
        return;
    }
    if (fp->mv.ca.specials.grav) {
        fp->mv.ca.specials.grav -= 1;
    }
    if (fp->mv.co.shouldered.x0 <= 0 && !fp->mv.co.shouldered.x4) {
        ftAnim_SetAnimRate(gobj, 1);
        fp->mv.co.shouldered.x0 = 0;
    }
    if (fp->mv.co.shouldered.x0 <= 0 && fp->mv.co.shouldered.x4 &&
        fp->motion_id == ftCo_MS_ShoulderedWait)
    {
        fp->mv.co.shouldered.x0 = p_ftCommonData->x3B0;
        ftAnim_SetAnimRate(gobj, p_ftCommonData->shouldered_anim_rate);
    }
}
#else /* clang-format off */
{ nofralloc
/* 8009C830 00099410  7C 08 02 A6 */	mflr r0
/* 8009C834 00099414  90 01 00 04 */	stw r0, 4(r1)
/* 8009C838 00099418  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8009C83C 0009941C  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 8009C840 00099420  7C 7F 1B 78 */	mr r31, r3
/* 8009C844 00099424  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8009C848 00099428  80 64 1A 58 */	lwz r3, 0x1a58(r4)
/* 8009C84C 0009942C  7C 9B 23 78 */	mr r27, r4
/* 8009C850 00099430  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8009C854 00099434  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8009C858 00099438  2C 00 00 00 */	cmpwi r0, 0
/* 8009C85C 0009943C  40 82 00 10 */	bne lbl_8009C86C
/* 8009C860 00099440  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009C864 00099444  C0 23 04 A8 */	lfs f1, 0x4a8(r3)
/* 8009C868 00099448  48 00 00 14 */	b lbl_8009C87C
lbl_8009C86C:
/* 8009C86C 0009944C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009C870 00099450  C0 23 04 A8 */	lfs f1, 0x4a8(r3)
/* 8009C874 00099454  C0 03 04 AC */	lfs f0, 0x4ac(r3)
/* 8009C878 00099458  EC 21 00 32 */	fmuls f1, f1, f0
lbl_8009C87C:
/* 8009C87C 0009945C  7F 63 DB 78 */	mr r3, r27
/* 8009C880 00099460  4B FE 13 89 */	bl ftCommon_8007DC08
/* 8009C884 00099464  90 7B 23 44 */	stw r3, 0x2344(r27)
/* 8009C888 00099468  C0 1B 1A 4C */	lfs f0, 0x1a4c(r27)
/* 8009C88C 0009946C  C0 42 8D 70 */	lfs f2, ftCo_804D8750
/* 8009C890 00099470  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8009C894 00099474  4C 40 13 82 */	cror 2, 0, 2
/* 8009C898 00099478  40 82 00 C8 */	bne lbl_8009C960
/* 8009C89C 0009947C  83 7B 1A 58 */	lwz r27, 0x1a58(r27)
/* 8009C8A0 00099480  38 80 00 34 */	li r4, 0x34
/* 8009C8A4 00099484  83 9B 00 2C */	lwz r28, 0x2c(r27)
/* 8009C8A8 00099488  80 BC 1A 58 */	lwz r5, 0x1a58(r28)
/* 8009C8AC 0009948C  7F 83 E3 78 */	mr r3, r28
/* 8009C8B0 00099490  83 A5 00 2C */	lwz r29, 0x2c(r5)
/* 8009C8B4 00099494  3B DD 0F 2C */	addi r30, r29, 0xf2c
/* 8009C8B8 00099498  4B FD 87 55 */	bl ftParts_8007500C
/* 8009C8BC 0009949C  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 8009C8C0 000994A0  54 60 20 36 */	slwi r0, r3, 4
/* 8009C8C4 000994A4  38 A1 00 28 */	addi r5, r1, 0x28
/* 8009C8C8 000994A8  7C 64 00 2E */	lwzx r3, r4, r0
/* 8009C8CC 000994AC  38 80 00 00 */	li r4, 0
/* 8009C8D0 000994B0  4B F6 E8 FD */	bl lb_8000B1CC
/* 8009C8D4 000994B4  80 DE 00 08 */	lwz r6, 8(r30)
/* 8009C8D8 000994B8  38 7C 00 00 */	addi r3, r28, 0
/* 8009C8DC 000994BC  38 9D 00 00 */	addi r4, r29, 0
/* 8009C8E0 000994C0  38 BE 00 00 */	addi r5, r30, 0
/* 8009C8E4 000994C4  4B FD D3 8D */	bl ftColl_80079C70
/* 8009C8E8 000994C8  D0 3C 18 50 */	stfs f1, 0x1850(r28)
/* 8009C8EC 000994CC  38 00 00 01 */	li r0, 1
/* 8009C8F0 000994D0  38 7B 00 00 */	addi r3, r27, 0
/* 8009C8F4 000994D4  80 9E 00 20 */	lwz r4, 0x20(r30)
/* 8009C8F8 000994D8  38 BC 18 44 */	addi r5, r28, 0x1844
/* 8009C8FC 000994DC  90 9C 18 48 */	stw r4, 0x1848(r28)
/* 8009C900 000994E0  C0 1C 00 2C */	lfs f0, 0x2c(r28)
/* 8009C904 000994E4  D0 1C 18 44 */	stfs f0, 0x1844(r28)
/* 8009C908 000994E8  90 1C 18 4C */	stw r0, 0x184c(r28)
/* 8009C90C 000994EC  80 81 00 28 */	lwz r4, 0x28(r1)
/* 8009C910 000994F0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8009C914 000994F4  90 9C 18 54 */	stw r4, 0x1854(r28)
/* 8009C918 000994F8  90 1C 18 58 */	stw r0, 0x1858(r28)
/* 8009C91C 000994FC  80 01 00 30 */	lwz r0, 0x30(r1)
/* 8009C920 00099500  90 1C 18 5C */	stw r0, 0x185c(r28)
/* 8009C924 00099504  80 1E 00 30 */	lwz r0, 0x30(r30)
/* 8009C928 00099508  90 1C 18 60 */	stw r0, 0x1860(r28)
/* 8009C92C 0009950C  80 9C 1A 58 */	lwz r4, 0x1a58(r28)
/* 8009C930 00099510  4B FD BD E1 */	bl ftColl_80078710
/* 8009C934 00099514  7F 83 E3 78 */	mr r3, r28
/* 8009C938 00099518  C0 3E 00 0C */	lfs f1, 0xc(r30)
/* 8009C93C 0009951C  4B FD 02 F5 */	bl Fighter_UnkTakeDamage_8006CC30
/* 8009C940 00099520  7F 83 E3 78 */	mr r3, r28
/* 8009C944 00099524  4B FF 0F ED */	bl ftCo_Damage_CalcKnockback
/* 8009C948 00099528  7F 63 DB 78 */	mr r3, r27
/* 8009C94C 0009952C  C0 22 8D 70 */	lfs f1, ftCo_804D8750
/* 8009C950 00099530  4B FF 1F B9 */	bl ftCo_8008E908
/* 8009C954 00099534  7F E3 FB 78 */	mr r3, r31
/* 8009C958 00099538  4B FF FD ED */	bl ftCo_8009C744
/* 8009C95C 0009953C  48 00 00 90 */	b lbl_8009C9EC
lbl_8009C960:
/* 8009C960 00099540  C0 1B 23 40 */	lfs f0, 0x2340(r27)
/* 8009C964 00099544  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8009C968 00099548  41 82 00 3C */	beq lbl_8009C9A4
/* 8009C96C 0009954C  C0 22 8D 74 */	lfs f1, ftCo_804D8754
/* 8009C970 00099550  EC 00 08 28 */	fsubs f0, f0, f1
/* 8009C974 00099554  D0 1B 23 40 */	stfs f0, 0x2340(r27)
/* 8009C978 00099558  C0 1B 23 40 */	lfs f0, 0x2340(r27)
/* 8009C97C 0009955C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8009C980 00099560  4C 40 13 82 */	cror 2, 0, 2
/* 8009C984 00099564  40 82 00 20 */	bne lbl_8009C9A4
/* 8009C988 00099568  80 1B 23 44 */	lwz r0, 0x2344(r27)
/* 8009C98C 0009956C  2C 00 00 00 */	cmpwi r0, 0
/* 8009C990 00099570  40 82 00 14 */	bne lbl_8009C9A4
/* 8009C994 00099574  7F E3 FB 78 */	mr r3, r31
/* 8009C998 00099578  4B FD 27 F9 */	bl ftAnim_SetAnimRate
/* 8009C99C 0009957C  C0 02 8D 70 */	lfs f0, ftCo_804D8750
/* 8009C9A0 00099580  D0 1B 23 40 */	stfs f0, 0x2340(r27)
lbl_8009C9A4:
/* 8009C9A4 00099584  C0 3B 23 40 */	lfs f1, 0x2340(r27)
/* 8009C9A8 00099588  C0 02 8D 70 */	lfs f0, ftCo_804D8750
/* 8009C9AC 0009958C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009C9B0 00099590  4C 40 13 82 */	cror 2, 0, 2
/* 8009C9B4 00099594  40 82 00 38 */	bne lbl_8009C9EC
/* 8009C9B8 00099598  80 1B 23 44 */	lwz r0, 0x2344(r27)
/* 8009C9BC 0009959C  2C 00 00 00 */	cmpwi r0, 0
/* 8009C9C0 000995A0  41 82 00 2C */	beq lbl_8009C9EC
/* 8009C9C4 000995A4  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 8009C9C8 000995A8  2C 00 01 0A */	cmpwi r0, 0x10a
/* 8009C9CC 000995AC  40 82 00 20 */	bne lbl_8009C9EC
/* 8009C9D0 000995B0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8009C9D4 000995B4  7F E3 FB 78 */	mr r3, r31
/* 8009C9D8 000995B8  C0 04 03 B0 */	lfs f0, 0x3b0(r4)
/* 8009C9DC 000995BC  D0 1B 23 40 */	stfs f0, 0x2340(r27)
/* 8009C9E0 000995C0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8009C9E4 000995C4  C0 24 03 B4 */	lfs f1, 0x3b4(r4)
/* 8009C9E8 000995C8  4B FD 27 A9 */	bl ftAnim_SetAnimRate
lbl_8009C9EC:
/* 8009C9EC 000995CC  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 8009C9F0 000995D0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8009C9F4 000995D4  38 21 00 58 */	addi r1, r1, 0x58
/* 8009C9F8 000995D8  7C 08 03 A6 */	mtlr r0
/* 8009C9FC 000995DC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_Shouldered_IASA(ftCo_GObj* gobj) {}

void ftCo_Shouldered_Phys(ftCo_GObj* gobj) {}

void ftCo_Shouldered_Coll(ftCo_GObj* gobj) {}
