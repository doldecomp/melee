#include "ftCo_0C35.h"

#include "ftCo_Damage.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "it/items/itlinkhookshot.h"
#include "mp/mpcoll.h"

#include <math.h>
#include <MSL/trigf.h>

#ifdef WIP
#pragma force_active on
#endif

/* literal */ double const ftCo_804D8CD0 = S32_TO_F32;
/* literal */ float const ftCo_804D8CD8 = 0;
/* literal */ double const ftCo_804D8CE0 = M_PI;
/* literal */ double const ftCo_804D8CE8 = M_PI_2;
/* literal */ SDATA char ftCo_804D3C38[] = "jobj.h";
/* literal */ SDATA char ftCo_804D3C40[] = "jobj";
/* literal */ char lbl_803C6CA8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

static inline void inlineA0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->dmg.x18F4 = p_ftCommonData->x648;
    fp->dmg.x18F4 = fp->dmg.x18F4;
    if (fp->dmg.x18F4 > fp->dmg.x1954) {
        fp->dmg.x1954 = fp->dmg.x18F4;
    }
    fp->x2220_flag.bits.b4 = true;
    Fighter_UnkRecursiveFunc_8006D044(gobj);
}

ASM void ftCo_800C3598(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    {
        float mag = fp->ground_or_air == GA_Air ? p_ftCommonData->x64C
                                                : p_ftCommonData->x650;
        float angle = ftCo_Damage_CalcAngle(fp, fp->dmg.kb_applied);
        float x = mag * cosf(angle);
        float y = mag * sinf(angle);
        if (fp->ground_or_air == GA_Air) {
            ftCo_Damage_CalcVel(fp, x * fp->dmg.x1844_direction, y);
            fp->xF0_ground_kb_vel = 0;
        } else {
            fp->xF0_ground_kb_vel = x * fp->dmg.x1844_direction;
            fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel;
            ftCo_Damage_CalcVel(
                fp, fp->coll_data.floor.normal.y * fp->xF0_ground_kb_vel,
                -fp->coll_data.floor.normal.x * fp->xF0_ground_kb_vel);
        }
        ftCommon_800804FC(fp);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C3598 000C0178  7C 08 02 A6 */	mflr r0
/* 800C359C 000C017C  90 01 00 04 */	stw r0, 4(r1)
/* 800C35A0 000C0180  3C 00 43 30 */	lis r0, 0x4330
/* 800C35A4 000C0184  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C35A8 000C0188  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 800C35AC 000C018C  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 800C35B0 000C0190  DB A1 00 28 */	stfd f29, 0x28(r1)
/* 800C35B4 000C0194  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C35B8 000C0198  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C35BC 000C019C  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 800C35C0 000C01A0  80 84 06 48 */	lwz r4, 0x648(r4)
/* 800C35C4 000C01A4  7C BF 2B 78 */	mr r31, r5
/* 800C35C8 000C01A8  90 85 18 F4 */	stw r4, 0x18f4(r5)
/* 800C35CC 000C01AC  80 85 18 F4 */	lwz r4, 0x18f4(r5)
/* 800C35D0 000C01B0  C8 42 92 F0 */	lfd f2, ftCo_804D8CD0
/* 800C35D4 000C01B4  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 800C35D8 000C01B8  C0 05 19 54 */	lfs f0, 0x1954(r5)
/* 800C35DC 000C01BC  90 81 00 1C */	stw r4, 0x1c(r1)
/* 800C35E0 000C01C0  90 01 00 18 */	stw r0, 0x18(r1)
/* 800C35E4 000C01C4  C8 21 00 18 */	lfd f1, 0x18(r1)
/* 800C35E8 000C01C8  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C35EC 000C01CC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C35F0 000C01D0  40 81 00 18 */	ble lbl_800C3608
/* 800C35F4 000C01D4  90 81 00 1C */	stw r4, 0x1c(r1)
/* 800C35F8 000C01D8  90 01 00 18 */	stw r0, 0x18(r1)
/* 800C35FC 000C01DC  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 800C3600 000C01E0  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C3604 000C01E4  D0 05 19 54 */	stfs f0, 0x1954(r5)
lbl_800C3608:
/* 800C3608 000C01E8  88 05 22 20 */	lbz r0, 0x2220(r5)
/* 800C360C 000C01EC  38 80 00 01 */	li r4, 1
/* 800C3610 000C01F0  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 800C3614 000C01F4  98 05 22 20 */	stb r0, 0x2220(r5)
/* 800C3618 000C01F8  4B FA 9A 2D */	bl Fighter_UnkRecursiveFunc_8006D044
/* 800C361C 000C01FC  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 800C3620 000C0200  2C 00 00 01 */	cmpwi r0, 1
/* 800C3624 000C0204  40 82 00 10 */	bne lbl_800C3634
/* 800C3628 000C0208  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C362C 000C020C  C3 E3 06 4C */	lfs f31, 0x64c(r3)
/* 800C3630 000C0210  48 00 00 0C */	b lbl_800C363C
lbl_800C3634:
/* 800C3634 000C0214  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C3638 000C0218  C3 E3 06 50 */	lfs f31, 0x650(r3)
lbl_800C363C:
/* 800C363C 000C021C  7F E3 FB 78 */	mr r3, r31
/* 800C3640 000C0220  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 800C3644 000C0224  4B FC A1 AD */	bl ftCo_Damage_CalcAngle
/* 800C3648 000C0228  FF C0 08 90 */	fmr f30, f1
/* 800C364C 000C022C  48 26 2B F5 */	bl cosf
/* 800C3650 000C0230  EF BF 00 72 */	fmuls f29, f31, f1
/* 800C3654 000C0234  FC 20 F0 90 */	fmr f1, f30
/* 800C3658 000C0238  48 26 2D 7D */	bl sinf
/* 800C365C 000C023C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 800C3660 000C0240  EC 5F 00 72 */	fmuls f2, f31, f1
/* 800C3664 000C0244  2C 00 00 01 */	cmpwi r0, 1
/* 800C3668 000C0248  40 82 00 20 */	bne lbl_800C3688
/* 800C366C 000C024C  C0 1F 18 44 */	lfs f0, 0x1844(r31)
/* 800C3670 000C0250  7F E3 FB 78 */	mr r3, r31
/* 800C3674 000C0254  EC 3D 00 32 */	fmuls f1, f29, f0
/* 800C3678 000C0258  4B FC A5 95 */	bl ftCo_Damage_CalcVel
/* 800C367C 000C025C  C0 02 92 F8 */	lfs f0, ftCo_804D8CD8
/* 800C3680 000C0260  D0 1F 00 F0 */	stfs f0, 0xf0(r31)
/* 800C3684 000C0264  48 00 00 30 */	b lbl_800C36B4
lbl_800C3688:
/* 800C3688 000C0268  C0 1F 18 44 */	lfs f0, 0x1844(r31)
/* 800C368C 000C026C  7F E3 FB 78 */	mr r3, r31
/* 800C3690 000C0270  EC 1D 00 32 */	fmuls f0, f29, f0
/* 800C3694 000C0274  D0 1F 00 F0 */	stfs f0, 0xf0(r31)
/* 800C3698 000C0278  C0 1F 08 44 */	lfs f0, 0x844(r31)
/* 800C369C 000C027C  C0 5F 00 F0 */	lfs f2, 0xf0(r31)
/* 800C36A0 000C0280  FC 00 00 50 */	fneg f0, f0
/* 800C36A4 000C0284  C0 3F 08 48 */	lfs f1, 0x848(r31)
/* 800C36A8 000C0288  EC 21 00 B2 */	fmuls f1, f1, f2
/* 800C36AC 000C028C  EC 40 00 B2 */	fmuls f2, f0, f2
/* 800C36B0 000C0290  4B FC A5 5D */	bl ftCo_Damage_CalcVel
lbl_800C36B4:
/* 800C36B4 000C0294  7F E3 FB 78 */	mr r3, r31
/* 800C36B8 000C0298  4B FB CE 45 */	bl ftCommon_800804FC
/* 800C36BC 000C029C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C36C0 000C02A0  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 800C36C4 000C02A4  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 800C36C8 000C02A8  CB A1 00 28 */	lfd f29, 0x28(r1)
/* 800C36CC 000C02AC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C36D0 000C02B0  38 21 00 40 */	addi r1, r1, 0x40
/* 800C36D4 000C02B4  7C 08 03 A6 */	mtlr r0
/* 800C36D8 000C02B8  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C36DC(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    fp->xF0_ground_kb_vel = p_ftCommonData->x654 * -fp->specialn_facing_dir;
    fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel;
    ftCo_Damage_CalcVel(fp,
                        fp->coll_data.floor.normal.y * fp->xF0_ground_kb_vel,
                        -fp->coll_data.floor.normal.x * fp->xF0_ground_kb_vel);
}

#else /* clang-format off */
{ nofralloc
/* 800C36DC 000C02BC  7C 08 02 A6 */	mflr r0
/* 800C36E0 000C02C0  90 01 00 04 */	stw r0, 4(r1)
/* 800C36E4 000C02C4  3C 00 43 30 */	lis r0, 0x4330
/* 800C36E8 000C02C8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800C36EC 000C02CC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C36F0 000C02D0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C36F4 000C02D4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 800C36F8 000C02D8  80 84 06 48 */	lwz r4, 0x648(r4)
/* 800C36FC 000C02DC  7C BF 2B 78 */	mr r31, r5
/* 800C3700 000C02E0  90 85 18 F4 */	stw r4, 0x18f4(r5)
/* 800C3704 000C02E4  80 85 18 F4 */	lwz r4, 0x18f4(r5)
/* 800C3708 000C02E8  C8 42 92 F0 */	lfd f2, ftCo_804D8CD0
/* 800C370C 000C02EC  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 800C3710 000C02F0  C0 05 19 54 */	lfs f0, 0x1954(r5)
/* 800C3714 000C02F4  90 81 00 1C */	stw r4, 0x1c(r1)
/* 800C3718 000C02F8  90 01 00 18 */	stw r0, 0x18(r1)
/* 800C371C 000C02FC  C8 21 00 18 */	lfd f1, 0x18(r1)
/* 800C3720 000C0300  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C3724 000C0304  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C3728 000C0308  40 81 00 18 */	ble lbl_800C3740
/* 800C372C 000C030C  90 81 00 1C */	stw r4, 0x1c(r1)
/* 800C3730 000C0310  90 01 00 18 */	stw r0, 0x18(r1)
/* 800C3734 000C0314  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 800C3738 000C0318  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C373C 000C031C  D0 05 19 54 */	stfs f0, 0x1954(r5)
lbl_800C3740:
/* 800C3740 000C0320  88 05 22 20 */	lbz r0, 0x2220(r5)
/* 800C3744 000C0324  38 80 00 01 */	li r4, 1
/* 800C3748 000C0328  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 800C374C 000C032C  98 05 22 20 */	stb r0, 0x2220(r5)
/* 800C3750 000C0330  4B FA 98 F5 */	bl Fighter_UnkRecursiveFunc_8006D044
/* 800C3754 000C0334  C0 1F 19 AC */	lfs f0, 0x19ac(r31)
/* 800C3758 000C0338  7F E3 FB 78 */	mr r3, r31
/* 800C375C 000C033C  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C3760 000C0340  FC 00 00 50 */	fneg f0, f0
/* 800C3764 000C0344  C0 24 06 54 */	lfs f1, 0x654(r4)
/* 800C3768 000C0348  EC 01 00 32 */	fmuls f0, f1, f0
/* 800C376C 000C034C  D0 1F 00 F0 */	stfs f0, 0xf0(r31)
/* 800C3770 000C0350  C0 1F 08 44 */	lfs f0, 0x844(r31)
/* 800C3774 000C0354  C0 5F 00 F0 */	lfs f2, 0xf0(r31)
/* 800C3778 000C0358  FC 00 00 50 */	fneg f0, f0
/* 800C377C 000C035C  C0 3F 08 48 */	lfs f1, 0x848(r31)
/* 800C3780 000C0360  EC 21 00 B2 */	fmuls f1, f1, f2
/* 800C3784 000C0364  EC 40 00 B2 */	fmuls f2, f0, f2
/* 800C3788 000C0368  4B FC A4 85 */	bl ftCo_Damage_CalcVel
/* 800C378C 000C036C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800C3790 000C0370  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C3794 000C0374  38 21 00 28 */	addi r1, r1, 0x28
/* 800C3798 000C0378  7C 08 03 A6 */	mtlr r0
/* 800C379C 000C037C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C37A0(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x18F4 != 0) {
        Fighter_Part part = ftParts_8007500C(fp, FtPart_TransN);
        HSD_JObj* jobj = fp->parts[part].x4_jobj2;
        --fp->dmg.x18F4;
        {
            float rot_y = M_PI *
                          (float) (p_ftCommonData->x648 - fp->dmg.x18F4) /
                          (float) p_ftCommonData->x648;
            ftParts_80075AF0(fp, part, rot_y);
            HSD_JObjSetRotationY(jobj, rot_y);
            if (fp->dmg.x18F4 == 0) {
                fp->x2220_flag.bits.b4 = false;
                fp->facing_dir = -fp->facing_dir;
                ftParts_80075AF0(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
                ftParts_80075AF0(fp, part, 0);
                HSD_JObjSetRotationY(jobj, 0);
                if (fp->x21F8 != NULL) {
                    fp->x21F8(gobj);
                }
            }
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C37A0 000C0380  7C 08 02 A6 */	mflr r0
/* 800C37A4 000C0384  90 01 00 04 */	stw r0, 4(r1)
/* 800C37A8 000C0388  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800C37AC 000C038C  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 800C37B0 000C0390  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800C37B4 000C0394  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800C37B8 000C0398  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800C37BC 000C039C  93 81 00 20 */	stw r28, 0x20(r1)
/* 800C37C0 000C03A0  7C 7C 1B 78 */	mr r28, r3
/* 800C37C4 000C03A4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800C37C8 000C03A8  80 03 18 F4 */	lwz r0, 0x18f4(r3)
/* 800C37CC 000C03AC  3B E3 00 00 */	addi r31, r3, 0
/* 800C37D0 000C03B0  2C 00 00 00 */	cmpwi r0, 0
/* 800C37D4 000C03B4  41 82 02 1C */	beq lbl_800C39F0
/* 800C37D8 000C03B8  38 7F 00 00 */	addi r3, r31, 0
/* 800C37DC 000C03BC  38 80 00 01 */	li r4, 1
/* 800C37E0 000C03C0  4B FB 18 2D */	bl ftParts_8007500C
/* 800C37E4 000C03C4  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C37E8 000C03C8  7C 7E 1B 78 */	mr r30, r3
/* 800C37EC 000C03CC  80 BF 18 F4 */	lwz r5, 0x18f4(r31)
/* 800C37F0 000C03D0  80 64 06 48 */	lwz r3, 0x648(r4)
/* 800C37F4 000C03D4  3C 80 43 30 */	lis r4, 0x4330
/* 800C37F8 000C03D8  C8 42 92 F0 */	lfd f2, ftCo_804D8CD0
/* 800C37FC 000C03DC  7C 05 18 50 */	subf r0, r5, r3
/* 800C3800 000C03E0  C8 62 93 00 */	lfd f3, ftCo_804D8CE0
/* 800C3804 000C03E4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C3808 000C03E8  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 800C380C 000C03EC  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800C3810 000C03F0  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800C3814 000C03F4  57 C0 20 36 */	slwi r0, r30, 4
/* 800C3818 000C03F8  90 81 00 18 */	stw r4, 0x18(r1)
/* 800C381C 000C03FC  7C C6 02 14 */	add r6, r6, r0
/* 800C3820 000C0400  83 A6 00 04 */	lwz r29, 4(r6)
/* 800C3824 000C0404  38 05 FF FF */	addi r0, r5, -1
/* 800C3828 000C0408  90 61 00 14 */	stw r3, 0x14(r1)
/* 800C382C 000C040C  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 800C3830 000C0410  7F E3 FB 78 */	mr r3, r31
/* 800C3834 000C0414  90 81 00 10 */	stw r4, 0x10(r1)
/* 800C3838 000C0418  7F C4 F3 78 */	mr r4, r30
/* 800C383C 000C041C  EC 20 10 28 */	fsubs f1, f0, f2
/* 800C3840 000C0420  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C3844 000C0424  90 1F 18 F4 */	stw r0, 0x18f4(r31)
/* 800C3848 000C0428  FC 23 00 72 */	fmul f1, f3, f1
/* 800C384C 000C042C  EC 00 10 28 */	fsubs f0, f0, f2
/* 800C3850 000C0430  FF E1 00 24 */	fdiv f31, f1, f0
/* 800C3854 000C0434  FF E0 F8 18 */	frsp f31, f31
/* 800C3858 000C0438  FC 20 F8 90 */	fmr f1, f31
/* 800C385C 000C043C  4B FB 22 95 */	bl ftParts_80075AF0
/* 800C3860 000C0440  28 1D 00 00 */	cmplwi r29, 0
/* 800C3864 000C0444  40 82 00 14 */	bne lbl_800C3878
/* 800C3868 000C0448  38 6D 85 98 */	addi r3, r13, ftCo_804D3C38
/* 800C386C 000C044C  38 80 02 94 */	li r4, 0x294
/* 800C3870 000C0450  38 AD 85 A0 */	addi r5, r13, ftCo_804D3C40
/* 800C3874 000C0454  48 2C 49 AD */	bl __assert
lbl_800C3878:
/* 800C3878 000C0458  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800C387C 000C045C  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 800C3880 000C0460  41 82 00 18 */	beq lbl_800C3898
/* 800C3884 000C0464  3C 60 80 3C */	lis r3, lbl_803C6CA8@ha
/* 800C3888 000C0468  38 A3 6C A8 */	addi r5, r3, lbl_803C6CA8@l
/* 800C388C 000C046C  38 6D 85 98 */	addi r3, r13, ftCo_804D3C38
/* 800C3890 000C0470  38 80 02 95 */	li r4, 0x295
/* 800C3894 000C0474  48 2C 49 8D */	bl __assert
lbl_800C3898:
/* 800C3898 000C0478  D3 FD 00 20 */	stfs f31, 0x20(r29)
/* 800C389C 000C047C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800C38A0 000C0480  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800C38A4 000C0484  40 82 00 4C */	bne lbl_800C38F0
/* 800C38A8 000C0488  28 1D 00 00 */	cmplwi r29, 0
/* 800C38AC 000C048C  41 82 00 44 */	beq lbl_800C38F0
/* 800C38B0 000C0490  40 82 00 14 */	bne lbl_800C38C4
/* 800C38B4 000C0494  38 6D 85 98 */	addi r3, r13, ftCo_804D3C38
/* 800C38B8 000C0498  38 80 02 34 */	li r4, 0x234
/* 800C38BC 000C049C  38 AD 85 A0 */	addi r5, r13, ftCo_804D3C40
/* 800C38C0 000C04A0  48 2C 49 61 */	bl __assert
lbl_800C38C4:
/* 800C38C4 000C04A4  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 800C38C8 000C04A8  38 60 00 00 */	li r3, 0
/* 800C38CC 000C04AC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800C38D0 000C04B0  40 82 00 10 */	bne lbl_800C38E0
/* 800C38D4 000C04B4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800C38D8 000C04B8  41 82 00 08 */	beq lbl_800C38E0
/* 800C38DC 000C04BC  38 60 00 01 */	li r3, 1
lbl_800C38E0:
/* 800C38E0 000C04C0  2C 03 00 00 */	cmpwi r3, 0
/* 800C38E4 000C04C4  40 82 00 0C */	bne lbl_800C38F0
/* 800C38E8 000C04C8  7F A3 EB 78 */	mr r3, r29
/* 800C38EC 000C04CC  48 2A F9 FD */	bl HSD_JObjSetMtxDirtySub
lbl_800C38F0:
/* 800C38F0 000C04D0  80 1F 18 F4 */	lwz r0, 0x18f4(r31)
/* 800C38F4 000C04D4  2C 00 00 00 */	cmpwi r0, 0
/* 800C38F8 000C04D8  40 82 00 F8 */	bne lbl_800C39F0
/* 800C38FC 000C04DC  88 1F 22 20 */	lbz r0, 0x2220(r31)
/* 800C3900 000C04E0  38 60 00 00 */	li r3, 0
/* 800C3904 000C04E4  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 800C3908 000C04E8  98 1F 22 20 */	stb r0, 0x2220(r31)
/* 800C390C 000C04EC  38 7F 00 00 */	addi r3, r31, 0
/* 800C3910 000C04F0  38 80 00 00 */	li r4, 0
/* 800C3914 000C04F4  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C3918 000C04F8  FC 00 00 50 */	fneg f0, f0
/* 800C391C 000C04FC  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800C3920 000C0500  C8 22 93 08 */	lfd f1, ftCo_804D8CE8
/* 800C3924 000C0504  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C3928 000C0508  FC 21 00 32 */	fmul f1, f1, f0
/* 800C392C 000C050C  FC 20 08 18 */	frsp f1, f1
/* 800C3930 000C0510  4B FB 21 C1 */	bl ftParts_80075AF0
/* 800C3934 000C0514  C0 22 92 F8 */	lfs f1, ftCo_804D8CD8
/* 800C3938 000C0518  38 7F 00 00 */	addi r3, r31, 0
/* 800C393C 000C051C  38 9E 00 00 */	addi r4, r30, 0
/* 800C3940 000C0520  4B FB 21 B1 */	bl ftParts_80075AF0
/* 800C3944 000C0524  28 1D 00 00 */	cmplwi r29, 0
/* 800C3948 000C0528  40 82 00 14 */	bne lbl_800C395C
/* 800C394C 000C052C  38 6D 85 98 */	addi r3, r13, ftCo_804D3C38
/* 800C3950 000C0530  38 80 02 94 */	li r4, 0x294
/* 800C3954 000C0534  38 AD 85 A0 */	addi r5, r13, ftCo_804D3C40
/* 800C3958 000C0538  48 2C 48 C9 */	bl __assert
lbl_800C395C:
/* 800C395C 000C053C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800C3960 000C0540  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 800C3964 000C0544  41 82 00 18 */	beq lbl_800C397C
/* 800C3968 000C0548  3C 60 80 3C */	lis r3, lbl_803C6CA8@ha
/* 800C396C 000C054C  38 A3 6C A8 */	addi r5, r3, lbl_803C6CA8@l
/* 800C3970 000C0550  38 6D 85 98 */	addi r3, r13, ftCo_804D3C38
/* 800C3974 000C0554  38 80 02 95 */	li r4, 0x295
/* 800C3978 000C0558  48 2C 48 A9 */	bl __assert
lbl_800C397C:
/* 800C397C 000C055C  C0 02 92 F8 */	lfs f0, ftCo_804D8CD8
/* 800C3980 000C0560  D0 1D 00 20 */	stfs f0, 0x20(r29)
/* 800C3984 000C0564  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800C3988 000C0568  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800C398C 000C056C  40 82 00 4C */	bne lbl_800C39D8
/* 800C3990 000C0570  28 1D 00 00 */	cmplwi r29, 0
/* 800C3994 000C0574  41 82 00 44 */	beq lbl_800C39D8
/* 800C3998 000C0578  40 82 00 14 */	bne lbl_800C39AC
/* 800C399C 000C057C  38 6D 85 98 */	addi r3, r13, ftCo_804D3C38
/* 800C39A0 000C0580  38 80 02 34 */	li r4, 0x234
/* 800C39A4 000C0584  38 AD 85 A0 */	addi r5, r13, ftCo_804D3C40
/* 800C39A8 000C0588  48 2C 48 79 */	bl __assert
lbl_800C39AC:
/* 800C39AC 000C058C  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 800C39B0 000C0590  38 60 00 00 */	li r3, 0
/* 800C39B4 000C0594  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800C39B8 000C0598  40 82 00 10 */	bne lbl_800C39C8
/* 800C39BC 000C059C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800C39C0 000C05A0  41 82 00 08 */	beq lbl_800C39C8
/* 800C39C4 000C05A4  38 60 00 01 */	li r3, 1
lbl_800C39C8:
/* 800C39C8 000C05A8  2C 03 00 00 */	cmpwi r3, 0
/* 800C39CC 000C05AC  40 82 00 0C */	bne lbl_800C39D8
/* 800C39D0 000C05B0  7F A3 EB 78 */	mr r3, r29
/* 800C39D4 000C05B4  48 2A F9 15 */	bl HSD_JObjSetMtxDirtySub
lbl_800C39D8:
/* 800C39D8 000C05B8  81 9F 21 F8 */	lwz r12, 0x21f8(r31)
/* 800C39DC 000C05BC  28 0C 00 00 */	cmplwi r12, 0
/* 800C39E0 000C05C0  41 82 00 10 */	beq lbl_800C39F0
/* 800C39E4 000C05C4  7D 88 03 A6 */	mtlr r12
/* 800C39E8 000C05C8  38 7C 00 00 */	addi r3, r28, 0
/* 800C39EC 000C05CC  4E 80 00 21 */	blrl
lbl_800C39F0:
/* 800C39F0 000C05D0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800C39F4 000C05D4  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800C39F8 000C05D8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800C39FC 000C05DC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800C3A00 000C05E0  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800C3A04 000C05E4  83 81 00 20 */	lwz r28, 0x20(r1)
/* 800C3A08 000C05E8  38 21 00 38 */	addi r1, r1, 0x38
/* 800C3A0C 000C05EC  7C 08 03 A6 */	mtlr r0
/* 800C3A10 000C05F0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
