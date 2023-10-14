#include "ftCommon/forward.h"

#include "ftCo_CaptureWaitKirby.h"

#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ftKirby/ftKb_Init.h"

LITERAL float const ftCo_804D8BB8 = 0;
LITERAL float const ftCo_804D8BBC = 1;
LITERAL double const ftCo_804D8BC0 = U32_TO_F32;
LITERAL double const ftCo_804D8BC8 = S32_TO_F32;

ASM void ftCo_800BD620(Fighter_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    ftCo_Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);
    fp->x2226_b2 = false;
    ftCo_800DB368(victim_fp, fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitKirby,
                              Ft_MF_SkipModel | Ft_MF_SkipMatAnim, 0, 1, 0,
                              NULL);
    Fighter_UpdateModelScale(gobj);
    fp->accessory1_cb = ftCo_800DB464;
    fp->x221E_b0 = true;
    ftColl_8007B62C(gobj, 2);
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 800BD620 000BA200  7C 08 02 A6 */	mflr r0
/* 800BD624 000BA204  90 01 00 04 */	stw r0, 4(r1)
/* 800BD628 000BA208  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800BD62C 000BA20C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800BD630 000BA210  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800BD634 000BA214  7C 7E 1B 78 */	mr r30, r3
/* 800BD638 000BA218  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BD63C 000BA21C  38 60 00 00 */	li r3, 0
/* 800BD640 000BA220  80 BF 1A 58 */	lwz r5, 0x1a58(r31)
/* 800BD644 000BA224  7F E4 FB 78 */	mr r4, r31
/* 800BD648 000BA228  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 800BD64C 000BA22C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 800BD650 000BA230  80 65 00 2C */	lwz r3, 0x2c(r5)
/* 800BD654 000BA234  98 1F 22 26 */	stb r0, 0x2226(r31)
/* 800BD658 000BA238  48 01 DD 11 */	bl ftCo_800DB368
/* 800BD65C 000BA23C  C0 22 91 D8 */	lfs f1, ftCo_804D8BB8
/* 800BD660 000BA240  7F C3 F3 78 */	mr r3, r30
/* 800BD664 000BA244  C0 42 91 DC */	lfs f2, ftCo_804D8BBC
/* 800BD668 000BA248  38 80 01 21 */	li r4, 0x121
/* 800BD66C 000BA24C  FC 60 08 90 */	fmr f3, f1
/* 800BD670 000BA250  38 A0 00 90 */	li r5, 0x90
/* 800BD674 000BA254  38 C0 00 00 */	li r6, 0
/* 800BD678 000BA258  4B FA BD 35 */	bl Fighter_ChangeMotionState
/* 800BD67C 000BA25C  7F C3 F3 78 */	mr r3, r30
/* 800BD680 000BA260  4B FA A5 35 */	bl Fighter_UpdateModelScale
/* 800BD684 000BA264  3C 60 80 0E */	lis r3, ftCo_800DB464@ha
/* 800BD688 000BA268  38 03 B4 64 */	addi r0, r3, ftCo_800DB464@l
/* 800BD68C 000BA26C  90 1F 21 B0 */	stw r0, 0x21b0(r31)
/* 800BD690 000BA270  38 80 00 01 */	li r4, 1
/* 800BD694 000BA274  38 7E 00 00 */	addi r3, r30, 0
/* 800BD698 000BA278  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 800BD69C 000BA27C  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 800BD6A0 000BA280  38 80 00 02 */	li r4, 2
/* 800BD6A4 000BA284  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 800BD6A8 000BA288  4B FB DF 85 */	bl ftColl_8007B62C
/* 800BD6AC 000BA28C  7F E3 FB 78 */	mr r3, r31
/* 800BD6B0 000BA290  4B FB FF 25 */	bl ftCommon_8007D5D4
/* 800BD6B4 000BA294  38 7F 00 00 */	addi r3, r31, 0
/* 800BD6B8 000BA298  38 80 01 FF */	li r4, 0x1ff
/* 800BD6BC 000BA29C  4B FC 0C 39 */	bl ftCommon_8007E2F4
/* 800BD6C0 000BA2A0  7F C3 F3 78 */	mr r3, r30
/* 800BD6C4 000BA2A4  4B FB 14 E1 */	bl ftAnim_8006EBA4
/* 800BD6C8 000BA2A8  7F C3 F3 78 */	mr r3, r30
/* 800BD6CC 000BA2AC  4B FC 0C 31 */	bl ftCommon_8007E2FC
/* 800BD6D0 000BA2B0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BD6D4 000BA2B4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800BD6D8 000BA2B8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800BD6DC 000BA2BC  38 21 00 28 */	addi r1, r1, 0x28
/* 800BD6E0 000BA2C0  7C 08 03 A6 */	mtlr r0
/* 800BD6E4 000BA2C4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineA0(ftCo_Fighter* fp, int arg1)
{
    fp->x671_timer_lstick_tilt_y = 254;
    ftKb_SpecialN_800F598C(fp->victim_gobj, arg1);
}

void ftCo_CaptureWaitKirby_Anim(ftCo_GObj* gobj) {}
#ifdef MWERKS_GEKKO
#pragma push
#pragma force_active on
#endif
ASM void ftCo_800BD6EC(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74)
    {
        inlineA0(fp, +1);
        return;
    }
    if (fp->input.lstick.y <= p_ftCommonData->x464 &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->x468 &&
        ftKb_SpecialN_800F597C(fp->victim_gobj))
    {
        inlineA0(fp, -1);
        ftKb_SpecialN_800F5954(fp->victim_gobj);
    }
}
#ifdef MWERKS_GEKKO
#pragma pop
#endif

#else /* clang-format off */
{ nofralloc
/* 800BD6EC 000BA2CC  7C 08 02 A6 */	mflr r0
/* 800BD6F0 000BA2D0  90 01 00 04 */	stw r0, 4(r1)
/* 800BD6F4 000BA2D4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800BD6F8 000BA2D8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800BD6FC 000BA2DC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BD700 000BA2E0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800BD704 000BA2E4  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 800BD708 000BA2E8  C0 04 00 70 */	lfs f0, 0x70(r4)
/* 800BD70C 000BA2EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD710 000BA2F0  4C 41 13 82 */	cror 2, 1, 2
/* 800BD714 000BA2F4  40 82 00 2C */	bne lbl_800BD740
/* 800BD718 000BA2F8  88 7F 06 71 */	lbz r3, 0x671(r31)
/* 800BD71C 000BA2FC  80 04 00 74 */	lwz r0, 0x74(r4)
/* 800BD720 000BA300  7C 03 00 00 */	cmpw r3, r0
/* 800BD724 000BA304  40 80 00 1C */	bge lbl_800BD740
/* 800BD728 000BA308  38 00 00 FE */	li r0, 0xfe
/* 800BD72C 000BA30C  98 1F 06 71 */	stb r0, 0x671(r31)
/* 800BD730 000BA310  38 80 00 01 */	li r4, 1
/* 800BD734 000BA314  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 800BD738 000BA318  48 03 82 55 */	bl ftKb_SpecialN_800F598C
/* 800BD73C 000BA31C  48 00 00 6C */	b lbl_800BD7A8
lbl_800BD740:
/* 800BD740 000BA320  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 800BD744 000BA324  C0 04 04 64 */	lfs f0, 0x464(r4)
/* 800BD748 000BA328  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD74C 000BA32C  4C 40 13 82 */	cror 2, 0, 2
/* 800BD750 000BA330  40 82 00 58 */	bne lbl_800BD7A8
/* 800BD754 000BA334  88 7F 06 71 */	lbz r3, 0x671(r31)
/* 800BD758 000BA338  3C 00 43 30 */	lis r0, 0x4330
/* 800BD75C 000BA33C  C8 42 91 E0 */	lfd f2, ftCo_804D8BC0
/* 800BD760 000BA340  90 61 00 14 */	stw r3, 0x14(r1)
/* 800BD764 000BA344  C0 04 04 68 */	lfs f0, 0x468(r4)
/* 800BD768 000BA348  90 01 00 10 */	stw r0, 0x10(r1)
/* 800BD76C 000BA34C  C8 21 00 10 */	lfd f1, 0x10(r1)
/* 800BD770 000BA350  EC 21 10 28 */	fsubs f1, f1, f2
/* 800BD774 000BA354  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD778 000BA358  40 80 00 30 */	bge lbl_800BD7A8
/* 800BD77C 000BA35C  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 800BD780 000BA360  48 03 81 FD */	bl ftKb_SpecialN_800F597C
/* 800BD784 000BA364  2C 03 00 00 */	cmpwi r3, 0
/* 800BD788 000BA368  41 82 00 20 */	beq lbl_800BD7A8
/* 800BD78C 000BA36C  38 00 00 FE */	li r0, 0xfe
/* 800BD790 000BA370  98 1F 06 71 */	stb r0, 0x671(r31)
/* 800BD794 000BA374  38 80 FF FF */	li r4, -1
/* 800BD798 000BA378  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 800BD79C 000BA37C  48 03 81 F1 */	bl ftKb_SpecialN_800F598C
/* 800BD7A0 000BA380  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 800BD7A4 000BA384  48 03 81 B1 */	bl ftKb_SpecialN_800F5954
lbl_800BD7A8:
/* 800BD7A8 000BA388  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800BD7AC 000BA38C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800BD7B0 000BA390  38 21 00 20 */	addi r1, r1, 0x20
/* 800BD7B4 000BA394  7C 08 03 A6 */	mtlr r0
/* 800BD7B8 000BA398  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineB0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    float lstick_x = fp->input.lstick.x;
    if (lstick_x < 0) {
        lstick_x = -lstick_x;
    }
    if (lstick_x >= p_ftCommonData->x3C &&
        fp->x670_timer_lstick_tilt_x <
            p_ftCommonData->x40 + p_ftCommonData->x44)
    {
        fp->x670_timer_lstick_tilt_x = 254;
        if (fp->input.lstick.x < 0) {
            ftKb_SpecialN_800F5A04(fp->victim_gobj);
        }
    }
}

ASM void ftCo_CaptureWaitKirby_IASA(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (ftKb_SpecialN_800F5A38(fp->victim_gobj, fp)) {
        inlineB0(gobj);
        ftCo_800BD6EC(gobj);
    }
    fp->x1A4C -= ftKb_SpecialN_800F5B00(fp->victim_gobj);
    fp->mv.co.capturekirby.x18 =
        ftCommon_8007DC08(fp, ftKb_SpecialN_800F5B10(fp->victim_gobj));
    if (fp->x1A4C <= 0) {
        Fighter_GObj* victim_gobj = fp->victim_gobj;
        fp->facing_dir = ftKb_SpecialN_800F5A60(victim_gobj);
        HSD_JObjSetScale(jobj, &jobj->scale);
        ftCo_800DC750(gobj);
        ftCo_800DA698(victim_gobj, 0);
    }
}
#else /* clang-format off */
{ nofralloc
/* 800BD7BC 000BA39C  7C 08 02 A6 */	mflr r0
/* 800BD7C0 000BA3A0  90 01 00 04 */	stw r0, 4(r1)
/* 800BD7C4 000BA3A4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800BD7C8 000BA3A8  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800BD7CC 000BA3AC  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800BD7D0 000BA3B0  7C 7E 1B 78 */	mr r30, r3
/* 800BD7D4 000BA3B4  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800BD7D8 000BA3B8  93 81 00 30 */	stw r28, 0x30(r1)
/* 800BD7DC 000BA3BC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800BD7E0 000BA3C0  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 800BD7E4 000BA3C4  80 64 1A 58 */	lwz r3, 0x1a58(r4)
/* 800BD7E8 000BA3C8  7C 9D 23 78 */	mr r29, r4
/* 800BD7EC 000BA3CC  48 03 82 4D */	bl ftKb_SpecialN_800F5A38
/* 800BD7F0 000BA3D0  2C 03 00 00 */	cmpwi r3, 0
/* 800BD7F4 000BA3D4  41 82 00 C8 */	beq lbl_800BD8BC
/* 800BD7F8 000BA3D8  7F C3 F3 78 */	mr r3, r30
/* 800BD7FC 000BA3DC  4B FF FE F1 */	bl ftCo_800BD6EC
/* 800BD800 000BA3E0  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800BD804 000BA3E4  C0 02 91 D8 */	lfs f0, ftCo_804D8BB8
/* 800BD808 000BA3E8  C0 25 06 20 */	lfs f1, 0x620(r5)
/* 800BD80C 000BA3EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD810 000BA3F0  40 80 00 08 */	bge lbl_800BD818
/* 800BD814 000BA3F4  FC 20 08 50 */	fneg f1, f1
lbl_800BD818:
/* 800BD818 000BA3F8  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 800BD81C 000BA3FC  C0 06 00 3C */	lfs f0, 0x3c(r6)
/* 800BD820 000BA400  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD824 000BA404  4C 41 13 82 */	cror 2, 1, 2
/* 800BD828 000BA408  40 82 00 94 */	bne lbl_800BD8BC
/* 800BD82C 000BA40C  80 06 00 40 */	lwz r0, 0x40(r6)
/* 800BD830 000BA410  3C 60 43 30 */	lis r3, 0x4330
/* 800BD834 000BA414  88 85 06 70 */	lbz r4, 0x670(r5)
/* 800BD838 000BA418  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800BD83C 000BA41C  C8 42 91 E8 */	lfd f2, ftCo_804D8BC8
/* 800BD840 000BA420  90 01 00 24 */	stw r0, 0x24(r1)
/* 800BD844 000BA424  C8 62 91 E0 */	lfd f3, ftCo_804D8BC0
/* 800BD848 000BA428  90 61 00 20 */	stw r3, 0x20(r1)
/* 800BD84C 000BA42C  C0 06 00 44 */	lfs f0, 0x44(r6)
/* 800BD850 000BA430  90 81 00 2C */	stw r4, 0x2c(r1)
/* 800BD854 000BA434  C8 21 00 20 */	lfd f1, 0x20(r1)
/* 800BD858 000BA438  90 61 00 28 */	stw r3, 0x28(r1)
/* 800BD85C 000BA43C  EC 21 10 28 */	fsubs f1, f1, f2
/* 800BD860 000BA440  C8 41 00 28 */	lfd f2, 0x28(r1)
/* 800BD864 000BA444  EC 42 18 28 */	fsubs f2, f2, f3
/* 800BD868 000BA448  EC 01 00 2A */	fadds f0, f1, f0
/* 800BD86C 000BA44C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800BD870 000BA450  40 80 00 4C */	bge lbl_800BD8BC
/* 800BD874 000BA454  38 00 00 FE */	li r0, 0xfe
/* 800BD878 000BA458  98 05 06 70 */	stb r0, 0x670(r5)
/* 800BD87C 000BA45C  C0 25 06 20 */	lfs f1, 0x620(r5)
/* 800BD880 000BA460  C0 02 91 D8 */	lfs f0, ftCo_804D8BB8
/* 800BD884 000BA464  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD888 000BA468  40 80 00 0C */	bge lbl_800BD894
/* 800BD88C 000BA46C  38 00 FF FF */	li r0, -1
/* 800BD890 000BA470  48 00 00 08 */	b lbl_800BD898
lbl_800BD894:
/* 800BD894 000BA474  38 00 00 01 */	li r0, 1
lbl_800BD898:
/* 800BD898 000BA478  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800BD89C 000BA47C  C8 22 91 E8 */	lfd f1, ftCo_804D8BC8
/* 800BD8A0 000BA480  90 01 00 24 */	stw r0, 0x24(r1)
/* 800BD8A4 000BA484  3C 00 43 30 */	lis r0, 0x4330
/* 800BD8A8 000BA488  80 65 1A 58 */	lwz r3, 0x1a58(r5)
/* 800BD8AC 000BA48C  90 01 00 20 */	stw r0, 0x20(r1)
/* 800BD8B0 000BA490  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 800BD8B4 000BA494  EC 20 08 28 */	fsubs f1, f0, f1
/* 800BD8B8 000BA498  48 03 81 4D */	bl ftKb_SpecialN_800F5A04
lbl_800BD8BC:
/* 800BD8BC 000BA49C  80 7D 1A 58 */	lwz r3, 0x1a58(r29)
/* 800BD8C0 000BA4A0  48 03 82 41 */	bl ftKb_SpecialN_800F5B00
/* 800BD8C4 000BA4A4  C0 1D 1A 4C */	lfs f0, 0x1a4c(r29)
/* 800BD8C8 000BA4A8  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BD8CC 000BA4AC  D0 1D 1A 4C */	stfs f0, 0x1a4c(r29)
/* 800BD8D0 000BA4B0  80 7D 1A 58 */	lwz r3, 0x1a58(r29)
/* 800BD8D4 000BA4B4  48 03 82 3D */	bl ftKb_SpecialN_800F5B10
/* 800BD8D8 000BA4B8  7F A3 EB 78 */	mr r3, r29
/* 800BD8DC 000BA4BC  4B FC 03 2D */	bl ftCommon_8007DC08
/* 800BD8E0 000BA4C0  90 7D 23 58 */	stw r3, 0x2358(r29)
/* 800BD8E4 000BA4C4  C0 3D 1A 4C */	lfs f1, 0x1a4c(r29)
/* 800BD8E8 000BA4C8  C0 02 91 D8 */	lfs f0, ftCo_804D8BB8
/* 800BD8EC 000BA4CC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD8F0 000BA4D0  4C 40 13 82 */	cror 2, 0, 2
/* 800BD8F4 000BA4D4  40 82 00 C4 */	bne lbl_800BD9B8
/* 800BD8F8 000BA4D8  83 9D 1A 58 */	lwz r28, 0x1a58(r29)
/* 800BD8FC 000BA4DC  7F 83 E3 78 */	mr r3, r28
/* 800BD900 000BA4E0  48 03 81 61 */	bl ftKb_SpecialN_800F5A60
/* 800BD904 000BA4E4  28 1F 00 00 */	cmplwi r31, 0
/* 800BD908 000BA4E8  D0 3D 00 2C */	stfs f1, 0x2c(r29)
/* 800BD90C 000BA4EC  40 82 00 14 */	bne lbl_800BD920
/* 800BD910 000BA4F0  38 6D 85 28 */	addi r3, r13, ftCo_804D3BC8
/* 800BD914 000BA4F4  38 80 02 F8 */	li r4, 0x2f8
/* 800BD918 000BA4F8  38 AD 85 30 */	addi r5, r13, ftCo_804D3BD0
/* 800BD91C 000BA4FC  48 2C A9 05 */	bl __assert
lbl_800BD920:
/* 800BD920 000BA500  34 1D 23 6C */	addic. r0, r29, 0x236c
/* 800BD924 000BA504  40 82 00 14 */	bne lbl_800BD938
/* 800BD928 000BA508  38 6D 85 28 */	addi r3, r13, ftCo_804D3BC8
/* 800BD92C 000BA50C  38 80 02 F9 */	li r4, 0x2f9
/* 800BD930 000BA510  38 AD 85 38 */	addi r5, r13, ftCo_804D3BD8
/* 800BD934 000BA514  48 2C A8 ED */	bl __assert
lbl_800BD938:
/* 800BD938 000BA518  80 7D 23 6C */	lwz r3, 0x236c(r29)
/* 800BD93C 000BA51C  80 1D 23 70 */	lwz r0, 0x2370(r29)
/* 800BD940 000BA520  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 800BD944 000BA524  90 1F 00 30 */	stw r0, 0x30(r31)
/* 800BD948 000BA528  80 1D 23 74 */	lwz r0, 0x2374(r29)
/* 800BD94C 000BA52C  90 1F 00 34 */	stw r0, 0x34(r31)
/* 800BD950 000BA530  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 800BD954 000BA534  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BD958 000BA538  40 82 00 4C */	bne lbl_800BD9A4
/* 800BD95C 000BA53C  28 1F 00 00 */	cmplwi r31, 0
/* 800BD960 000BA540  41 82 00 44 */	beq lbl_800BD9A4
/* 800BD964 000BA544  40 82 00 14 */	bne lbl_800BD978
/* 800BD968 000BA548  38 6D 85 28 */	addi r3, r13, ftCo_804D3BC8
/* 800BD96C 000BA54C  38 80 02 34 */	li r4, 0x234
/* 800BD970 000BA550  38 AD 85 30 */	addi r5, r13, ftCo_804D3BD0
/* 800BD974 000BA554  48 2C A8 AD */	bl __assert
lbl_800BD978:
/* 800BD978 000BA558  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 800BD97C 000BA55C  38 60 00 00 */	li r3, 0
/* 800BD980 000BA560  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BD984 000BA564  40 82 00 10 */	bne lbl_800BD994
/* 800BD988 000BA568  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BD98C 000BA56C  41 82 00 08 */	beq lbl_800BD994
/* 800BD990 000BA570  38 60 00 01 */	li r3, 1
lbl_800BD994:
/* 800BD994 000BA574  2C 03 00 00 */	cmpwi r3, 0
/* 800BD998 000BA578  40 82 00 0C */	bne lbl_800BD9A4
/* 800BD99C 000BA57C  7F E3 FB 78 */	mr r3, r31
/* 800BD9A0 000BA580  48 2B 59 49 */	bl HSD_JObjSetMtxDirtySub
lbl_800BD9A4:
/* 800BD9A4 000BA584  7F C3 F3 78 */	mr r3, r30
/* 800BD9A8 000BA588  48 01 ED A9 */	bl ftCo_800DC750
/* 800BD9AC 000BA58C  38 7C 00 00 */	addi r3, r28, 0
/* 800BD9B0 000BA590  38 80 00 00 */	li r4, 0
/* 800BD9B4 000BA594  48 01 CC E5 */	bl ftCo_800DA698
lbl_800BD9B8:
/* 800BD9B8 000BA598  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800BD9BC 000BA59C  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800BD9C0 000BA5A0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800BD9C4 000BA5A4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800BD9C8 000BA5A8  83 81 00 30 */	lwz r28, 0x30(r1)
/* 800BD9CC 000BA5AC  38 21 00 40 */	addi r1, r1, 0x40
/* 800BD9D0 000BA5B0  7C 08 03 A6 */	mtlr r0
/* 800BD9D4 000BA5B4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_CaptureWaitKirby_Phys(ftCo_GObj* gobj) {}

void ftCo_CaptureWaitKirby_Coll(ftCo_GObj* gobj) {}
