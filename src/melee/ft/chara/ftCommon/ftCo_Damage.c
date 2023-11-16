#include <platform.h>
#include "forward.h"
#include "ft/forward.h"

#include "ftCo_Damage.h"

#include "ftCo_Bury.h"
#include "ftCo_DamageFall.h"
#include "ftCo_DamageIce.h"
#include "ftCo_DownAttack.h"
#include "ftCo_DownBound.h"
#include "ftCo_DownDamage.h"
#include "ftCo_PassiveStand.h"
#include "ftCo_Wait.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C08.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftDonkey/ftDk_HeavyLanding.h"
#include "gm/gm_1601.h"
#include "lb/lbbgflash.h"
#include "lb/lbvector.h"
#include "pl/pl_0371.h"
#include "un/un_2FC9.h"

#include <common_structs.h>
#include <math.h>
#include <placeholder.h>
#include <dolphin/mtx/vec.h>
#include <MetroTRK/intrinsics.h>
#include <MSL/trigf.h>

int ftCo_803C5520[2][12] = {
    { 81, 78, 75, 82, 79, 76, 83, 80, 77, 89, 88, 87 },
    { 84, 84, 84, 85, 85, 85, 86, 86, 86, 89, 88, 87 },
};

#ifdef MWERKS_GEKKO
float const lbl_804D84D0 = deg_to_rad;
float const lbl_804D84D4 = 0;
float const lbl_804D84D8 = 1;
double const lbl_804D84E0 = 4503601774854144;
float const lbl_804D84E8 = M_PI_2;
float const lbl_804D84EC = 0.0001;
double const lbl_804D84F0 = M_PI_2;
float const lbl_804D84F8 = 0.00001;
double const lbl_804D8500 = 0.5;
double const lbl_804D8508 = 3;
#endif

/* 08DA4C */ static bool ftCo_8008DA4C(ftCo_GObj* gobj, enum_t, enum_t);
/* 08F938 */ static bool doIasa(ftCo_GObj* gobj);

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08D7F0 */ float ftCo_Damage_CalcAngle(ftCo_Fighter* fp, float)
{
    // clang-format off
    nofralloc
/* 8008D7F0 0008A3D0  7C 08 02 A6 */	mflr r0
/* 8008D7F4 0008A3D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008D7F8 0008A3D8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008D7FC 0008A3DC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008D800 0008A3E0  7C 7F 1B 78 */	mr r31, r3
/* 8008D804 0008A3E4  80 63 18 48 */	lwz r3, 0x1848(r3)
/* 8008D808 0008A3E8  2C 03 01 69 */	cmpwi r3, 0x169
/* 8008D80C 0008A3EC  41 82 00 50 */	beq lbl_8008D85C
/* 8008D810 0008A3F0  4B FE D4 59 */	bl ftColl_8007AC68
/* 8008D814 0008A3F4  2C 03 00 00 */	cmpwi r3, 0
/* 8008D818 0008A3F8  41 82 00 18 */	beq lbl_8008D830
/* 8008D81C 0008A3FC  38 00 00 01 */	li r0, 1
/* 8008D820 0008A400  98 1F 23 5A */	stb r0, 0x235a(r31)
/* 8008D824 0008A404  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008D828 0008A408  80 03 07 F0 */	lwz r0, 0x7f0(r3)
/* 8008D82C 0008A40C  98 1F 23 5B */	stb r0, 0x235b(r31)
lbl_8008D830:
/* 8008D830 0008A410  80 7F 18 48 */	lwz r3, 0x1848(r31)
/* 8008D834 0008A414  3C 00 43 30 */	lis r0, 0x4330
/* 8008D838 0008A418  C8 22 8B 00 */	lfd f1, lbl_804D84E0
/* 8008D83C 0008A41C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008D840 0008A420  C0 42 8A F0 */	lfs f2, lbl_804D84D0
/* 8008D844 0008A424  90 61 00 14 */	stw r3, 0x14(r1)
/* 8008D848 0008A428  90 01 00 10 */	stw r0, 0x10(r1)
/* 8008D84C 0008A42C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8008D850 0008A430  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008D854 0008A434  EC 22 00 32 */	fmuls f1, f2, f0
/* 8008D858 0008A438  48 00 00 6C */	b lbl_8008D8C4
lbl_8008D85C:
/* 8008D85C 0008A43C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008D860 0008A440  2C 00 00 01 */	cmpwi r0, 1
/* 8008D864 0008A444  40 82 00 10 */	bne lbl_8008D874
/* 8008D868 0008A448  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008D86C 0008A44C  C0 23 01 44 */	lfs f1, 0x144(r3)
/* 8008D870 0008A450  48 00 00 54 */	b lbl_8008D8C4
lbl_8008D874:
/* 8008D874 0008A454  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008D878 0008A458  C0 63 01 4C */	lfs f3, 0x14c(r3)
/* 8008D87C 0008A45C  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 8008D880 0008A460  40 80 00 0C */	bge lbl_8008D88C
/* 8008D884 0008A464  C0 22 8A F4 */	lfs f1, lbl_804D84D4
/* 8008D888 0008A468  48 00 00 3C */	b lbl_8008D8C4
lbl_8008D88C:
/* 8008D88C 0008A46C  C0 03 01 50 */	lfs f0, 0x150(r3)
/* 8008D890 0008A470  EC 41 18 28 */	fsubs f2, f1, f3
/* 8008D894 0008A474  C0 83 01 48 */	lfs f4, 0x148(r3)
/* 8008D898 0008A478  EC 20 18 28 */	fsubs f1, f0, f3
/* 8008D89C 0008A47C  C0 62 8A F0 */	lfs f3, lbl_804D84D0
/* 8008D8A0 0008A480  C0 02 8A F8 */	lfs f0, lbl_804D84D8
/* 8008D8A4 0008A484  EC A3 01 32 */	fmuls f5, f3, f4
/* 8008D8A8 0008A488  EC 22 08 24 */	fdivs f1, f2, f1
/* 8008D8AC 0008A48C  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8008D8B0 0008A490  EC 03 00 32 */	fmuls f0, f3, f0
/* 8008D8B4 0008A494  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 8008D8B8 0008A498  FC 20 00 90 */	fmr f1, f0
/* 8008D8BC 0008A49C  40 81 00 08 */	ble lbl_8008D8C4
/* 8008D8C0 0008A4A0  FC 20 28 90 */	fmr f1, f5
lbl_8008D8C4:
/* 8008D8C4 0008A4A4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D8C8 0008A4A8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D8CC 0008A4AC  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D8D0 0008A4B0  7C 08 03 A6 */	mtlr r0
/* 8008D8D4 0008A4B4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

float ftCo_Damage_CalcAngle(Fighter* fp, float f)
{
    if (fp->dmg.x1848_kb_angle != 361) {
        if (ftColl_8007AC68(fp->dmg.x1848_kb_angle)) {
            fp->mv.co.damage.x1A = 1;
            fp->mv.co.damage.x1B = p_ftCommonData->x7F0;
        }
        return deg_to_rad * fp->dmg.x1848_kb_angle;
    }
    if (fp->ground_or_air == GA_Air) {
        return p_ftCommonData->x144;
    } else if (f < p_ftCommonData->x14C) {
        return 0;
    } else {
        float result =
            deg_to_rad * (p_ftCommonData->x148 *
                              ((f - p_ftCommonData->x14C) /
                               (p_ftCommonData->x150 - p_ftCommonData->x14C)) +
                          1);
        if (result > deg_to_rad * p_ftCommonData->x148) {
            result = deg_to_rad * p_ftCommonData->x148;
        }
        return result;
    }
}
#endif

float ftCo_ScaleBy154(float mul)
{
    return mul * p_ftCommonData->x154;
}

bool ftCo_8008D8E8(float f)
{
    return f < p_ftCommonData->x158   ? 0
           : f < p_ftCommonData->x15C ? 1
           : f < p_ftCommonData->x160 ? 2
                                      : 3;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_Damage_CalcKnockback(ftCo_Fighter*)
{ // clang-format off
    nofralloc
/* 8008D930 0008A510  7C 08 02 A6 */	mflr r0
/* 8008D934 0008A514  90 01 00 04 */	stw r0, 4(r1)
/* 8008D938 0008A518  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008D93C 0008A51C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008D940 0008A520  7C 7F 1B 78 */	mr r31, r3
/* 8008D944 0008A524  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008D948 0008A528  C0 23 18 50 */	lfs f1, 0x1850(r3)
/* 8008D94C 0008A52C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008D950 0008A530  41 82 00 E8 */	beq lbl_8008DA38
/* 8008D954 0008A534  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008D958 0008A538  2C 00 00 27 */	cmpwi r0, 0x27
/* 8008D95C 0008A53C  41 82 00 0C */	beq lbl_8008D968
/* 8008D960 0008A540  2C 00 00 28 */	cmpwi r0, 0x28
/* 8008D964 0008A544  40 82 00 18 */	bne lbl_8008D97C
lbl_8008D968:
/* 8008D968 0008A548  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008D96C 0008A54C  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D970 0008A550  C0 03 01 24 */	lfs f0, 0x124(r3)
/* 8008D974 0008A554  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008D978 0008A558  D0 1F 18 50 */	stfs f0, 0x1850(r31)
lbl_8008D97C:
/* 8008D97C 0008A55C  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008D980 0008A560  2C 00 01 45 */	cmpwi r0, 0x145
/* 8008D984 0008A564  40 82 00 18 */	bne lbl_8008D99C
/* 8008D988 0008A568  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008D98C 0008A56C  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D990 0008A570  C0 03 07 18 */	lfs f0, 0x718(r3)
/* 8008D994 0008A574  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008D998 0008A578  D0 1F 18 50 */	stfs f0, 0x1850(r31)
lbl_8008D99C:
/* 8008D99C 0008A57C  80 1F 21 14 */	lwz r0, 0x2114(r31)
/* 8008D9A0 0008A580  2C 00 00 02 */	cmpwi r0, 2
/* 8008D9A4 0008A584  40 82 00 18 */	bne lbl_8008D9BC
/* 8008D9A8 0008A588  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008D9AC 0008A58C  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D9B0 0008A590  C0 03 07 C4 */	lfs f0, 0x7c4(r3)
/* 8008D9B4 0008A594  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008D9B8 0008A598  D0 1F 18 50 */	stfs f0, 0x1850(r31)
lbl_8008D9BC:
/* 8008D9BC 0008A59C  C0 02 8A F8 */	lfs f0, lbl_804D84D8
/* 8008D9C0 0008A5A0  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 8008D9C4 0008A5A4  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008D9C8 0008A5A8  41 82 00 18 */	beq lbl_8008D9E0
/* 8008D9CC 0008A5AC  80 6D AE 84 */	lwz r3, Fighter_804D6524
/* 8008D9D0 0008A5B0  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D9D4 0008A5B4  C0 63 00 00 */	lfs f3, 0(r3)
/* 8008D9D8 0008A5B8  48 04 1B BD */	bl ftCo_CalcYScaledKnockback
/* 8008D9DC 0008A5BC  D0 3F 18 50 */	stfs f1, 0x1850(r31)
lbl_8008D9E0:
/* 8008D9E0 0008A5C0  C0 1F 18 B0 */	lfs f0, 0x18b0(r31)
/* 8008D9E4 0008A5C4  C0 3F 18 B4 */	lfs f1, 0x18b4(r31)
/* 8008D9E8 0008A5C8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8008D9EC 0008A5CC  40 81 00 08 */	ble lbl_8008D9F4
/* 8008D9F0 0008A5D0  48 00 00 08 */	b lbl_8008D9F8
lbl_8008D9F4:
/* 8008D9F4 0008A5D4  FC 00 08 90 */	fmr f0, f1
lbl_8008D9F8:
/* 8008D9F8 0008A5D8  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 8008D9FC 0008A5DC  FC 20 00 90 */	fmr f1, f0
/* 8008DA00 0008A5E0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008DA04 0008A5E4  41 82 00 10 */	beq lbl_8008DA14
/* 8008DA08 0008A5E8  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DA0C 0008A5EC  C0 03 06 F0 */	lfs f0, 0x6f0(r3)
/* 8008DA10 0008A5F0  EC 21 00 2A */	fadds f1, f1, f0
lbl_8008DA14:
/* 8008DA14 0008A5F4  C0 1F 18 50 */	lfs f0, 0x1850(r31)
/* 8008DA18 0008A5F8  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008DA1C 0008A5FC  D0 1F 18 50 */	stfs f0, 0x1850(r31)
/* 8008DA20 0008A600  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DA24 0008A604  C0 1F 18 50 */	lfs f0, 0x1850(r31)
/* 8008DA28 0008A608  C0 23 01 04 */	lfs f1, 0x104(r3)
/* 8008DA2C 0008A60C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8008DA30 0008A610  40 80 00 08 */	bge lbl_8008DA38
/* 8008DA34 0008A614  D0 3F 18 50 */	stfs f1, 0x1850(r31)
lbl_8008DA38:
/* 8008DA38 0008A618  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008DA3C 0008A61C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008DA40 0008A620  38 21 00 18 */	addi r1, r1, 0x18
/* 8008DA44 0008A624  7C 08 03 A6 */	mtlr r0
/* 8008DA48 0008A628  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_Damage_CalcKnockback(Fighter* fp)
{
    if (!fp->dmg.kb_applied) {
        return;
    }
    /// @todo Probably a @c switch.
    if (fp->motion_id == ftCo_MS_Squat) {
        goto squat;
    }
    if (fp->motion_id != ftCo_MS_SquatWait) {
        goto not_squatwait;
    }
squat:
    fp->dmg.kb_applied *= p_ftCommonData->kb_squat_mul;
not_squatwait:
    if (fp->motion_id == ftCo_MS_DamageIce) {
        fp->dmg.kb_applied *= p_ftCommonData->kb_ice_mul;
    }
    if (fp->smash_attrs.state == SmashState_Charging) {
        fp->dmg.kb_applied *= p_ftCommonData->kb_smashcharge_mul;
    }
    if (fp->x34_scale.y != 1) {
        fp->dmg.kb_applied =
            ftCo_CalcYScaledKnockback(Fighter_804D6524, fp->dmg.kb_applied,
                                      fp->x34_scale.y, *Fighter_804D6524);
    }
    {
        float armor =
            fp->dmg.armor0 > fp->dmg.armor1 ? fp->dmg.armor0 : fp->dmg.armor1;
        if (fp->x2223_b7) {
            armor += p_ftCommonData->unk_armor;
        }
        fp->dmg.kb_applied -= armor;
        if (fp->dmg.kb_applied < p_ftCommonData->kb_min) {
            fp->dmg.kb_applied = p_ftCommonData->kb_min;
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08DA4C */ /* static */ bool ftCo_8008DA4C(ftCo_GObj* gobj, enum_t,
                                                 enum_t)
{
    // clang-format off
    nofralloc
/* 8008DA4C 0008A62C  7C 08 02 A6 */	mflr r0
/* 8008DA50 0008A630  90 01 00 04 */	stw r0, 4(r1)
/* 8008DA54 0008A634  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008DA58 0008A638  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008DA5C 0008A63C  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DA60 0008A640  C0 23 18 38 */	lfs f1, 0x1838(r3)
/* 8008DA64 0008A644  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008DA68 0008A648  41 82 00 94 */	beq lbl_8008DAFC
/* 8008DA6C 0008A64C  2C 04 00 05 */	cmpwi r4, 5
/* 8008DA70 0008A650  41 82 00 54 */	beq lbl_8008DAC4
/* 8008DA74 0008A654  40 80 00 1C */	bge lbl_8008DA90
/* 8008DA78 0008A658  2C 04 00 02 */	cmpwi r4, 2
/* 8008DA7C 0008A65C  41 82 00 34 */	beq lbl_8008DAB0
/* 8008DA80 0008A660  40 80 00 6C */	bge lbl_8008DAEC
/* 8008DA84 0008A664  2C 04 00 01 */	cmpwi r4, 1
/* 8008DA88 0008A668  40 80 00 14 */	bge lbl_8008DA9C
/* 8008DA8C 0008A66C  48 00 00 60 */	b lbl_8008DAEC
lbl_8008DA90:
/* 8008DA90 0008A670  2C 04 00 0D */	cmpwi r4, 0xd
/* 8008DA94 0008A674  41 82 00 44 */	beq lbl_8008DAD8
/* 8008DA98 0008A678  48 00 00 54 */	b lbl_8008DAEC
lbl_8008DA9C:
/* 8008DA9C 0008A67C  38 85 00 0B */	addi r4, r5, 0xb
/* 8008DAA0 0008A680  38 A0 00 00 */	li r5, 0
/* 8008DAA4 0008A684  48 03 25 2D */	bl ftCo_800BFFD0
/* 8008DAA8 0008A688  7C 60 1B 78 */	mr r0, r3
/* 8008DAAC 0008A68C  48 00 00 50 */	b lbl_8008DAFC
lbl_8008DAB0:
/* 8008DAB0 0008A690  38 85 00 0F */	addi r4, r5, 0xf
/* 8008DAB4 0008A694  38 A0 00 00 */	li r5, 0
/* 8008DAB8 0008A698  48 03 25 19 */	bl ftCo_800BFFD0
/* 8008DABC 0008A69C  7C 60 1B 78 */	mr r0, r3
/* 8008DAC0 0008A6A0  48 00 00 3C */	b lbl_8008DAFC
lbl_8008DAC4:
/* 8008DAC4 0008A6A4  38 85 00 1F */	addi r4, r5, 0x1f
/* 8008DAC8 0008A6A8  38 A0 00 00 */	li r5, 0
/* 8008DACC 0008A6AC  48 03 25 05 */	bl ftCo_800BFFD0
/* 8008DAD0 0008A6B0  7C 60 1B 78 */	mr r0, r3
/* 8008DAD4 0008A6B4  48 00 00 28 */	b lbl_8008DAFC
lbl_8008DAD8:
/* 8008DAD8 0008A6B8  38 85 00 23 */	addi r4, r5, 0x23
/* 8008DADC 0008A6BC  38 A0 00 00 */	li r5, 0
/* 8008DAE0 0008A6C0  48 03 24 F1 */	bl ftCo_800BFFD0
/* 8008DAE4 0008A6C4  7C 60 1B 78 */	mr r0, r3
/* 8008DAE8 0008A6C8  48 00 00 14 */	b lbl_8008DAFC
lbl_8008DAEC:
/* 8008DAEC 0008A6CC  38 80 00 04 */	li r4, 4
/* 8008DAF0 0008A6D0  38 A0 00 00 */	li r5, 0
/* 8008DAF4 0008A6D4  48 03 24 DD */	bl ftCo_800BFFD0
/* 8008DAF8 0008A6D8  7C 60 1B 78 */	mr r0, r3
lbl_8008DAFC:
/* 8008DAFC 0008A6DC  7C 03 03 78 */	mr r3, r0
/* 8008DB00 0008A6E0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008DB04 0008A6E4  38 21 00 08 */	addi r1, r1, 8
/* 8008DB08 0008A6E8  7C 08 03 A6 */	mtlr r0
/* 8008DB0C 0008A6EC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftCo_8008DA4C(ftCo_GObj* gobj, enum_t arg1, enum_t arg2)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->dmg.x1838_percentTemp) {
        switch (arg1) {
        case 1:
            return ftCo_800BFFD0(fp, arg2 + 11, 0);
            break;
        case 2:
            return ftCo_800BFFD0(fp, arg2 + 15, 0);
            break;
        case 5:
            return ftCo_800BFFD0(fp, arg2 + 31, 0);
            break;
        case 13:
            return ftCo_800BFFD0(fp, arg2 + 35, 0);
            break;
        }
    }
    return ftCo_800BFFD0(fp, 4, 0);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08DB10 */ /* static */ void ftCo_8008DB10(ftCo_GObj* gobj, int, float)
{ // clang-format off
    nofralloc
/* 8008DB10 0008A6F0  7C 08 02 A6 */	mflr r0
/* 8008DB14 0008A6F4  90 01 00 04 */	stw r0, 4(r1)
/* 8008DB18 0008A6F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008DB1C 0008A6FC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008DB20 0008A700  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DB24 0008A704  C0 43 18 38 */	lfs f2, 0x1838(r3)
/* 8008DB28 0008A708  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 8008DB2C 0008A70C  41 82 00 D0 */	beq lbl_8008DBFC
/* 8008DB30 0008A710  2C 04 00 05 */	cmpwi r4, 5
/* 8008DB34 0008A714  41 82 00 6C */	beq lbl_8008DBA0
/* 8008DB38 0008A718  40 80 00 1C */	bge lbl_8008DB54
/* 8008DB3C 0008A71C  2C 04 00 02 */	cmpwi r4, 2
/* 8008DB40 0008A720  41 82 00 40 */	beq lbl_8008DB80
/* 8008DB44 0008A724  40 80 00 9C */	bge lbl_8008DBE0
/* 8008DB48 0008A728  2C 04 00 01 */	cmpwi r4, 1
/* 8008DB4C 0008A72C  40 80 00 14 */	bge lbl_8008DB60
/* 8008DB50 0008A730  48 00 00 90 */	b lbl_8008DBE0
lbl_8008DB54:
/* 8008DB54 0008A734  2C 04 00 0D */	cmpwi r4, 0xd
/* 8008DB58 0008A738  41 82 00 68 */	beq lbl_8008DBC0
/* 8008DB5C 0008A73C  48 00 00 84 */	b lbl_8008DBE0
lbl_8008DB60:
/* 8008DB60 0008A740  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DB64 0008A744  C0 03 01 7C */	lfs f0, 0x17c(r3)
/* 8008DB68 0008A748  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DB6C 0008A74C  40 81 00 90 */	ble lbl_8008DBFC
/* 8008DB70 0008A750  38 60 00 03 */	li r3, 3
/* 8008DB74 0008A754  38 80 00 00 */	li r4, 0
/* 8008DB78 0008A758  4B F9 40 D1 */	bl lbBgFlash_80021C48
/* 8008DB7C 0008A75C  48 00 00 80 */	b lbl_8008DBFC
lbl_8008DB80:
/* 8008DB80 0008A760  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DB84 0008A764  C0 03 01 80 */	lfs f0, 0x180(r3)
/* 8008DB88 0008A768  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DB8C 0008A76C  40 81 00 70 */	ble lbl_8008DBFC
/* 8008DB90 0008A770  38 60 00 04 */	li r3, 4
/* 8008DB94 0008A774  38 80 00 00 */	li r4, 0
/* 8008DB98 0008A778  4B F9 40 B1 */	bl lbBgFlash_80021C48
/* 8008DB9C 0008A77C  48 00 00 60 */	b lbl_8008DBFC
lbl_8008DBA0:
/* 8008DBA0 0008A780  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DBA4 0008A784  C0 03 01 84 */	lfs f0, 0x184(r3)
/* 8008DBA8 0008A788  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DBAC 0008A78C  40 81 00 50 */	ble lbl_8008DBFC
/* 8008DBB0 0008A790  38 60 00 05 */	li r3, 5
/* 8008DBB4 0008A794  38 80 00 00 */	li r4, 0
/* 8008DBB8 0008A798  4B F9 40 91 */	bl lbBgFlash_80021C48
/* 8008DBBC 0008A79C  48 00 00 40 */	b lbl_8008DBFC
lbl_8008DBC0:
/* 8008DBC0 0008A7A0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DBC4 0008A7A4  C0 03 01 88 */	lfs f0, 0x188(r3)
/* 8008DBC8 0008A7A8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DBCC 0008A7AC  40 81 00 30 */	ble lbl_8008DBFC
/* 8008DBD0 0008A7B0  38 60 00 06 */	li r3, 6
/* 8008DBD4 0008A7B4  38 80 00 00 */	li r4, 0
/* 8008DBD8 0008A7B8  4B F9 40 71 */	bl lbBgFlash_80021C48
/* 8008DBDC 0008A7BC  48 00 00 20 */	b lbl_8008DBFC
lbl_8008DBE0:
/* 8008DBE0 0008A7C0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DBE4 0008A7C4  C0 03 01 78 */	lfs f0, 0x178(r3)
/* 8008DBE8 0008A7C8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DBEC 0008A7CC  40 81 00 10 */	ble lbl_8008DBFC
/* 8008DBF0 0008A7D0  38 60 00 02 */	li r3, 2
/* 8008DBF4 0008A7D4  38 80 00 00 */	li r4, 0
/* 8008DBF8 0008A7D8  4B F9 40 51 */	bl lbBgFlash_80021C48
lbl_8008DBFC:
/* 8008DBFC 0008A7DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008DC00 0008A7E0  38 21 00 08 */	addi r1, r1, 8
/* 8008DC04 0008A7E4  7C 08 03 A6 */	mtlr r0
/* 8008DC08 0008A7E8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_8008DB10(ftCo_GObj* gobj, enum_t arg1, float arg2)
{
    if (!GET_FIGHTER(gobj)->dmg.x1838_percentTemp) {
        return;
    }
    switch (arg1) {
    case 1:
        if (arg2 > p_ftCommonData->x17C) {
            lbBgFlash_80021C48(3, 0);
        }
        return;
    case 2:
        if (arg2 > p_ftCommonData->x180) {
            lbBgFlash_80021C48(4, 0);
        }
        return;
    case 5:
        if (arg2 > p_ftCommonData->x184) {
            lbBgFlash_80021C48(5, 0);
        }
        return;
    case 13:
        if (arg2 > p_ftCommonData->x188) {
            lbBgFlash_80021C48(6, 0);
        }
        return;
    default:
        if (arg2 > p_ftCommonData->x178) {
            lbBgFlash_80021C48(2, 0);
        }
        return;
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08DC0C */ /* static */ void ftCo_Damage_CalcVel(ftCo_Fighter* fp, float,
                                                       float)
{ // clang-format off
    nofralloc
/* 8008DC0C 0008A7EC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008DC10 0008A7F0  80 A3 18 AC */	lwz r5, 0x18ac(r3)
/* 8008DC14 0008A7F4  80 04 00 FC */	lwz r0, 0xfc(r4)
/* 8008DC18 0008A7F8  7C 05 00 00 */	cmpw r5, r0
/* 8008DC1C 0008A7FC  40 80 00 10 */	bge lbl_8008DC2C
/* 8008DC20 0008A800  D0 23 00 8C */	stfs f1, 0x8c(r3)
/* 8008DC24 0008A804  D0 43 00 90 */	stfs f2, 0x90(r3)
/* 8008DC28 0008A808  4E 80 00 20 */	blr
lbl_8008DC2C:
/* 8008DC2C 0008A80C  C0 83 00 8C */	lfs f4, 0x8c(r3)
/* 8008DC30 0008A810  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DC34 0008A814  EC 64 00 72 */	fmuls f3, f4, f1
/* 8008DC38 0008A818  C0 A3 00 90 */	lfs f5, 0x90(r3)
/* 8008DC3C 0008A81C  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8008DC40 0008A820  40 80 00 10 */	bge lbl_8008DC50
/* 8008DC44 0008A824  EC 04 08 2A */	fadds f0, f4, f1
/* 8008DC48 0008A828  D0 03 00 8C */	stfs f0, 0x8c(r3)
/* 8008DC4C 0008A82C  48 00 00 3C */	b lbl_8008DC88
lbl_8008DC50:
/* 8008DC50 0008A830  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008DC54 0008A834  40 80 00 0C */	bge lbl_8008DC60
/* 8008DC58 0008A838  FC 60 20 50 */	fneg f3, f4
/* 8008DC5C 0008A83C  48 00 00 08 */	b lbl_8008DC64
lbl_8008DC60:
/* 8008DC60 0008A840  FC 60 20 90 */	fmr f3, f4
lbl_8008DC64:
/* 8008DC64 0008A844  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DC68 0008A848  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DC6C 0008A84C  40 80 00 0C */	bge lbl_8008DC78
/* 8008DC70 0008A850  FC 00 08 50 */	fneg f0, f1
/* 8008DC74 0008A854  48 00 00 08 */	b lbl_8008DC7C
lbl_8008DC78:
/* 8008DC78 0008A858  FC 00 08 90 */	fmr f0, f1
lbl_8008DC7C:
/* 8008DC7C 0008A85C  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 8008DC80 0008A860  40 81 00 08 */	ble lbl_8008DC88
/* 8008DC84 0008A864  D0 23 00 8C */	stfs f1, 0x8c(r3)
lbl_8008DC88:
/* 8008DC88 0008A868  EC 25 00 B2 */	fmuls f1, f5, f2
/* 8008DC8C 0008A86C  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DC90 0008A870  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DC94 0008A874  40 80 00 10 */	bge lbl_8008DCA4
/* 8008DC98 0008A878  EC 05 10 2A */	fadds f0, f5, f2
/* 8008DC9C 0008A87C  D0 03 00 90 */	stfs f0, 0x90(r3)
/* 8008DCA0 0008A880  4E 80 00 20 */	blr
lbl_8008DCA4:
/* 8008DCA4 0008A884  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 8008DCA8 0008A888  40 80 00 0C */	bge lbl_8008DCB4
/* 8008DCAC 0008A88C  FC 20 28 50 */	fneg f1, f5
/* 8008DCB0 0008A890  48 00 00 08 */	b lbl_8008DCB8
lbl_8008DCB4:
/* 8008DCB4 0008A894  FC 20 28 90 */	fmr f1, f5
lbl_8008DCB8:
/* 8008DCB8 0008A898  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DCBC 0008A89C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008DCC0 0008A8A0  40 80 00 0C */	bge lbl_8008DCCC
/* 8008DCC4 0008A8A4  FC 00 10 50 */	fneg f0, f2
/* 8008DCC8 0008A8A8  48 00 00 08 */	b lbl_8008DCD0
lbl_8008DCCC:
/* 8008DCCC 0008A8AC  FC 00 10 90 */	fmr f0, f2
lbl_8008DCD0:
/* 8008DCD0 0008A8B0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8008DCD4 0008A8B4  4C 81 00 20 */	blelr
/* 8008DCD8 0008A8B8  D0 43 00 90 */	stfs f2, 0x90(r3)
/* 8008DCDC 0008A8BC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_Damage_CalcVel(Fighter* fp, float x, float y)
{
    if (fp->dmg.x18ac_time_since_hit < p_ftCommonData->xFC) {
        fp->x8c_kb_vel.x = x;
        fp->x8c_kb_vel.y = y;
    } else {
        float cur_x = fp->x8c_kb_vel.x;
        float cur_y = fp->x8c_kb_vel.y;
        if (cur_x * x < 0) {
            fp->x8c_kb_vel.x = cur_x + x;
        } else if (ABS(x) > ABS(cur_x)) {
            fp->x8c_kb_vel.x = x;
        }
        if (cur_y * y < 0) {
            fp->x8c_kb_vel.y = cur_y + y;
        } else if (ABS(y) > ABS(cur_y)) {
            fp->x8c_kb_vel.y = y;
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08DCE0 */ void ftCo_8008DCE0(ftCo_GObj* gobj, int, float)
{ // clang-format off
    nofralloc
/* 8008DCE0 0008A8C0  7C 08 02 A6 */	mflr r0
/* 8008DCE4 0008A8C4  3C A0 80 3C */	lis r5, ftCo_803C5520@ha
/* 8008DCE8 0008A8C8  90 01 00 04 */	stw r0, 4(r1)
/* 8008DCEC 0008A8CC  94 21 FF 38 */	stwu r1, -0xc8(r1)
/* 8008DCF0 0008A8D0  DB E1 00 C0 */	stfd f31, 0xc0(r1)
/* 8008DCF4 0008A8D4  DB C1 00 B8 */	stfd f30, 0xb8(r1)
/* 8008DCF8 0008A8D8  DB A1 00 B0 */	stfd f29, 0xb0(r1)
/* 8008DCFC 0008A8DC  DB 81 00 A8 */	stfd f28, 0xa8(r1)
/* 8008DD00 0008A8E0  DB 61 00 A0 */	stfd f27, 0xa0(r1)
/* 8008DD04 0008A8E4  FF 60 08 90 */	fmr f27, f1
/* 8008DD08 0008A8E8  DB 41 00 98 */	stfd f26, 0x98(r1)
/* 8008DD0C 0008A8EC  DB 21 00 90 */	stfd f25, 0x90(r1)
/* 8008DD10 0008A8F0  BF 01 00 70 */	stmw r24, 0x70(r1)
/* 8008DD14 0008A8F4  3B 24 00 00 */	addi r25, r4, 0
/* 8008DD18 0008A8F8  7C 78 1B 78 */	mr r24, r3
/* 8008DD1C 0008A8FC  3B E5 55 20 */	addi r31, r5, ftCo_803C5520@l
/* 8008DD20 0008A900  3B 60 00 01 */	li r27, 1
/* 8008DD24 0008A904  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8008DD28 0008A908  C0 1D 18 38 */	lfs f0, 0x1838(r29)
/* 8008DD2C 0008A90C  7F A3 EB 78 */	mr r3, r29
/* 8008DD30 0008A910  C3 9D 18 50 */	lfs f28, 0x1850(r29)
/* 8008DD34 0008A914  FC 00 00 1E */	fctiwz f0, f0
/* 8008DD38 0008A918  D8 01 00 68 */	stfd f0, 0x68(r1)
/* 8008DD3C 0008A91C  80 81 00 6C */	lwz r4, 0x6c(r1)
/* 8008DD40 0008A920  4B FD F0 65 */	bl Fighter_8006CDA4
/* 8008DD44 0008A924  D3 9D 18 E0 */	stfs f28, 0x18e0(r29)
/* 8008DD48 0008A928  FC 20 E0 90 */	fmr f1, f28
/* 8008DD4C 0008A92C  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 8008DD50 0008A930  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 8008DD54 0008A934  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008DD58 0008A938  4B FB 25 19 */	bl pl_80040270
/* 8008DD5C 0008A93C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DD60 0008A940  3C 00 43 30 */	lis r0, 0x4330
/* 8008DD64 0008A944  C8 22 8B 00 */	lfd f1, lbl_804D84E0
/* 8008DD68 0008A948  C0 03 01 54 */	lfs f0, 0x154(r3)
/* 8008DD6C 0008A94C  EF DC 00 32 */	fmuls f30, f28, f0
/* 8008DD70 0008A950  FC 00 F0 1E */	fctiwz f0, f30
/* 8008DD74 0008A954  D8 01 00 60 */	stfd f0, 0x60(r1)
/* 8008DD78 0008A958  80 61 00 64 */	lwz r3, 0x64(r1)
/* 8008DD7C 0008A95C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008DD80 0008A960  90 61 00 5C */	stw r3, 0x5c(r1)
/* 8008DD84 0008A964  90 01 00 58 */	stw r0, 0x58(r1)
/* 8008DD88 0008A968  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 8008DD8C 0008A96C  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008DD90 0008A970  D0 1D 23 40 */	stfs f0, 0x2340(r29)
/* 8008DD94 0008A974  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 8008DD98 0008A978  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DD9C 0008A97C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008DDA0 0008A980  40 82 00 0C */	bne lbl_8008DDAC
/* 8008DDA4 0008A984  C0 02 8A F8 */	lfs f0, lbl_804D84D8
/* 8008DDA8 0008A988  D0 1D 23 40 */	stfs f0, 0x2340(r29)
lbl_8008DDAC:
/* 8008DDAC 0008A98C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DDB0 0008A990  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008DDB4 0008A994  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008DDB8 0008A998  40 80 00 0C */	bge lbl_8008DDC4
/* 8008DDBC 0008A99C  3B C0 00 00 */	li r30, 0
/* 8008DDC0 0008A9A0  48 00 00 30 */	b lbl_8008DDF0
lbl_8008DDC4:
/* 8008DDC4 0008A9A4  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008DDC8 0008A9A8  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008DDCC 0008A9AC  40 80 00 0C */	bge lbl_8008DDD8
/* 8008DDD0 0008A9B0  3B C0 00 01 */	li r30, 1
/* 8008DDD4 0008A9B4  48 00 00 1C */	b lbl_8008DDF0
lbl_8008DDD8:
/* 8008DDD8 0008A9B8  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008DDDC 0008A9BC  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008DDE0 0008A9C0  40 80 00 0C */	bge lbl_8008DDEC
/* 8008DDE4 0008A9C4  3B C0 00 02 */	li r30, 2
/* 8008DDE8 0008A9C8  48 00 00 08 */	b lbl_8008DDF0
lbl_8008DDEC:
/* 8008DDEC 0008A9CC  3B C0 00 03 */	li r30, 3
lbl_8008DDF0:
/* 8008DDF0 0008A9D0  2C 19 FF FF */	cmpwi r25, -1
/* 8008DDF4 0008A9D4  3B 9E 00 00 */	addi r28, r30, 0
/* 8008DDF8 0008A9D8  41 82 00 08 */	beq lbl_8008DE00
/* 8008DDFC 0008A9DC  3B 80 00 03 */	li r28, 3
lbl_8008DE00:
/* 8008DE00 0008A9E0  C0 03 01 00 */	lfs f0, 0x100(r3)
/* 8008DE04 0008A9E4  38 00 00 00 */	li r0, 0
/* 8008DE08 0008A9E8  FC 20 E0 90 */	fmr f1, f28
/* 8008DE0C 0008A9EC  7F A3 EB 78 */	mr r3, r29
/* 8008DE10 0008A9F0  98 1D 23 5A */	stb r0, 0x235a(r29)
/* 8008DE14 0008A9F4  EF FC 00 32 */	fmuls f31, f28, f0
/* 8008DE18 0008A9F8  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DE1C 0008A9FC  D0 1D 23 54 */	stfs f0, 0x2354(r29)
/* 8008DE20 0008AA00  4B FF F9 D1 */	bl ftCo_Damage_CalcAngle
/* 8008DE24 0008AA04  2C 1E 00 02 */	cmpwi r30, 2
/* 8008DE28 0008AA08  FF A0 08 90 */	fmr f29, f1
/* 8008DE2C 0008AA0C  41 80 00 70 */	blt lbl_8008DE9C
/* 8008DE30 0008AA10  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008DE34 0008AA14  28 00 00 05 */	cmplwi r0, 5
/* 8008DE38 0008AA18  40 82 00 64 */	bne lbl_8008DE9C
/* 8008DE3C 0008AA1C  C0 22 8B 08 */	lfs f1, lbl_804D84E8
/* 8008DE40 0008AA20  48 29 84 01 */	bl cosf
/* 8008DE44 0008AA24  FF 40 08 90 */	fmr f26, f1
/* 8008DE48 0008AA28  FC 20 E8 90 */	fmr f1, f29
/* 8008DE4C 0008AA2C  48 29 83 F5 */	bl cosf
/* 8008DE50 0008AA30  C0 02 8B 08 */	lfs f0, lbl_804D84E8
/* 8008DE54 0008AA34  EF 21 D0 2A */	fadds f25, f1, f26
/* 8008DE58 0008AA38  FC 20 00 90 */	fmr f1, f0
/* 8008DE5C 0008AA3C  48 29 85 79 */	bl sinf
/* 8008DE60 0008AA40  FF 40 08 90 */	fmr f26, f1
/* 8008DE64 0008AA44  FC 20 E8 90 */	fmr f1, f29
/* 8008DE68 0008AA48  48 29 85 6D */	bl sinf
/* 8008DE6C 0008AA4C  EC 21 D0 2A */	fadds f1, f1, f26
/* 8008DE70 0008AA50  C0 02 8B 0C */	lfs f0, lbl_804D84EC
/* 8008DE74 0008AA54  EC 41 00 72 */	fmuls f2, f1, f1
/* 8008DE78 0008AA58  EC 59 16 7A */	fmadds f2, f25, f25, f2
/* 8008DE7C 0008AA5C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008DE80 0008AA60  4C 40 13 82 */	cror 2, 0, 2
/* 8008DE84 0008AA64  40 82 00 0C */	bne lbl_8008DE90
/* 8008DE88 0008AA68  C0 22 8A F4 */	lfs f1, lbl_804D84D4
/* 8008DE8C 0008AA6C  48 00 00 0C */	b lbl_8008DE98
lbl_8008DE90:
/* 8008DE90 0008AA70  FC 40 C8 90 */	fmr f2, f25
/* 8008DE94 0008AA74  4B F9 4D 9D */	bl atan2f
lbl_8008DE98:
/* 8008DE98 0008AA78  FF A0 08 90 */	fmr f29, f1
lbl_8008DE9C:
/* 8008DE9C 0008AA7C  FC 20 E8 90 */	fmr f1, f29
/* 8008DEA0 0008AA80  48 29 83 A1 */	bl cosf
/* 8008DEA4 0008AA84  EF 3F 00 72 */	fmuls f25, f31, f1
/* 8008DEA8 0008AA88  FC 20 E8 90 */	fmr f1, f29
/* 8008DEAC 0008AA8C  48 29 85 29 */	bl sinf
/* 8008DEB0 0008AA90  C0 1D 18 44 */	lfs f0, 0x1844(r29)
/* 8008DEB4 0008AA94  EF 5F 00 72 */	fmuls f26, f31, f1
/* 8008DEB8 0008AA98  D0 1D 00 2C */	stfs f0, 0x2c(r29)
/* 8008DEBC 0008AA9C  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 8008DEC0 0008AAA0  2C 00 00 01 */	cmpwi r0, 1
/* 8008DEC4 0008AAA4  40 82 00 74 */	bne lbl_8008DF38
/* 8008DEC8 0008AAA8  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008DECC 0008AAAC  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008DED0 0008AAB0  7C 7F 1A 14 */	add r3, r31, r3
/* 8008DED4 0008AAB4  54 00 10 3A */	slwi r0, r0, 2
/* 8008DED8 0008AAB8  7C 63 02 14 */	add r3, r3, r0
/* 8008DEDC 0008AABC  83 E3 00 30 */	lwz r31, 0x30(r3)
/* 8008DEE0 0008AAC0  7F A3 EB 78 */	mr r3, r29
/* 8008DEE4 0008AAC4  48 00 05 B5 */	bl ftCo_Damage_CheckAirMotion
/* 8008DEE8 0008AAC8  2C 03 00 00 */	cmpwi r3, 0
/* 8008DEEC 0008AACC  41 82 00 28 */	beq lbl_8008DF14
/* 8008DEF0 0008AAD0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008DEF4 0008AAD4  FC 20 E8 90 */	fmr f1, f29
/* 8008DEF8 0008AAD8  C0 03 01 90 */	lfs f0, 0x190(r3)
/* 8008DEFC 0008AADC  EF FF 00 32 */	fmuls f31, f31, f0
/* 8008DF00 0008AAE0  48 29 83 41 */	bl cosf
/* 8008DF04 0008AAE4  EF 3F 00 72 */	fmuls f25, f31, f1
/* 8008DF08 0008AAE8  FC 20 E8 90 */	fmr f1, f29
/* 8008DF0C 0008AAEC  48 29 84 C9 */	bl sinf
/* 8008DF10 0008AAF0  EF 5F 00 72 */	fmuls f26, f31, f1
lbl_8008DF14:
/* 8008DF14 0008AAF4  FC 20 C8 50 */	fneg f1, f25
/* 8008DF18 0008AAF8  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 8008DF1C 0008AAFC  FC 40 D0 90 */	fmr f2, f26
/* 8008DF20 0008AB00  7F A3 EB 78 */	mr r3, r29
/* 8008DF24 0008AB04  EC 21 00 32 */	fmuls f1, f1, f0
/* 8008DF28 0008AB08  4B FF FC E5 */	bl ftCo_Damage_CalcVel
/* 8008DF2C 0008AB0C  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DF30 0008AB10  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008DF34 0008AB14  48 00 01 74 */	b lbl_8008E0A8
lbl_8008DF38:
/* 8008DF38 0008AB18  FC 20 C8 50 */	fneg f1, f25
/* 8008DF3C 0008AB1C  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 8008DF40 0008AB20  3B 5D 08 44 */	addi r26, r29, 0x844
/* 8008DF44 0008AB24  38 7A 00 00 */	addi r3, r26, 0
/* 8008DF48 0008AB28  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008DF4C 0008AB2C  38 81 00 44 */	addi r4, r1, 0x44
/* 8008DF50 0008AB30  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8008DF54 0008AB34  D3 41 00 48 */	stfs f26, 0x48(r1)
/* 8008DF58 0008AB38  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DF5C 0008AB3C  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 8008DF60 0008AB40  4B F7 F6 C1 */	bl lbVector_Angle
/* 8008DF64 0008AB44  FF 40 08 90 */	fmr f26, f1
/* 8008DF68 0008AB48  C0 02 8B 08 */	lfs f0, lbl_804D84E8
/* 8008DF6C 0008AB4C  FC 1A 00 40 */	fcmpo cr0, f26, f0
/* 8008DF70 0008AB50  40 80 00 3C */	bge lbl_8008DFAC
/* 8008DF74 0008AB54  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008DF78 0008AB58  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008DF7C 0008AB5C  54 00 10 3A */	slwi r0, r0, 2
/* 8008DF80 0008AB60  7C 03 02 14 */	add r0, r3, r0
/* 8008DF84 0008AB64  7F FF 00 2E */	lwzx r31, r31, r0
/* 8008DF88 0008AB68  7F A3 EB 78 */	mr r3, r29
/* 8008DF8C 0008AB6C  4B FE F6 49 */	bl ftCommon_8007D5D4
/* 8008DF90 0008AB70  C0 21 00 44 */	lfs f1, 0x44(r1)
/* 8008DF94 0008AB74  7F A3 EB 78 */	mr r3, r29
/* 8008DF98 0008AB78  C0 41 00 48 */	lfs f2, 0x48(r1)
/* 8008DF9C 0008AB7C  4B FF FC 71 */	bl ftCo_Damage_CalcVel
/* 8008DFA0 0008AB80  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008DFA4 0008AB84  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008DFA8 0008AB88  48 00 01 00 */	b lbl_8008E0A8
lbl_8008DFAC:
/* 8008DFAC 0008AB8C  2C 1C 00 03 */	cmpwi r28, 3
/* 8008DFB0 0008AB90  40 82 00 BC */	bne lbl_8008E06C
/* 8008DFB4 0008AB94  7F A3 EB 78 */	mr r3, r29
/* 8008DFB8 0008AB98  4B FE F6 1D */	bl ftCommon_8007D5D4
/* 8008DFBC 0008AB9C  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008DFC0 0008ABA0  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008DFC4 0008ABA4  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008DFC8 0008ABA8  C8 22 8B 10 */	lfd f1, lbl_804D84F0
/* 8008DFCC 0008ABAC  C0 04 01 E8 */	lfs f0, 0x1e8(r4)
/* 8008DFD0 0008ABB0  54 00 10 3A */	slwi r0, r0, 2
/* 8008DFD4 0008ABB4  7C 03 02 14 */	add r0, r3, r0
/* 8008DFD8 0008ABB8  FC 01 00 2A */	fadd f0, f1, f0
/* 8008DFDC 0008ABBC  7F FF 00 2E */	lwzx r31, r31, r0
/* 8008DFE0 0008ABC0  FC 1A 00 40 */	fcmpo cr0, f26, f0
/* 8008DFE4 0008ABC4  40 81 00 6C */	ble lbl_8008E050
/* 8008DFE8 0008ABC8  C0 21 00 48 */	lfs f1, 0x48(r1)
/* 8008DFEC 0008ABCC  7F A3 EB 78 */	mr r3, r29
/* 8008DFF0 0008ABD0  C0 04 01 EC */	lfs f0, 0x1ec(r4)
/* 8008DFF4 0008ABD4  FC 40 08 50 */	fneg f2, f1
/* 8008DFF8 0008ABD8  C0 21 00 44 */	lfs f1, 0x44(r1)
/* 8008DFFC 0008ABDC  EC 42 00 32 */	fmuls f2, f2, f0
/* 8008E000 0008ABE0  4B FF FC 0D */	bl ftCo_Damage_CalcVel
/* 8008E004 0008ABE4  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E008 0008ABE8  3B 60 00 00 */	li r27, 0
/* 8008E00C 0008ABEC  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008E010 0008ABF0  C0 1A 00 00 */	lfs f0, 0(r26)
/* 8008E014 0008ABF4  C0 5A 00 04 */	lfs f2, 4(r26)
/* 8008E018 0008ABF8  FC 20 00 50 */	fneg f1, f0
/* 8008E01C 0008ABFC  4B F9 4C 15 */	bl atan2f
/* 8008E020 0008AC00  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 8008E024 0008AC04  38 78 00 00 */	addi r3, r24, 0
/* 8008E028 0008AC08  39 01 00 40 */	addi r8, r1, 0x40
/* 8008E02C 0008AC0C  4C C6 31 82 */	crclr 6
/* 8008E030 0008AC10  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 8008E034 0008AC14  81 38 00 2C */	lwz r9, 0x2c(r24)
/* 8008E038 0008AC18  38 A0 00 04 */	li r5, 4
/* 8008E03C 0008AC1C  80 E4 00 00 */	lwz r7, 0(r4)
/* 8008E040 0008AC20  38 C0 04 06 */	li r6, 0x406
/* 8008E044 0008AC24  38 89 06 0C */	addi r4, r9, 0x60c
/* 8008E048 0008AC28  4B FD 96 A9 */	bl efAsync_Spawn
/* 8008E04C 0008AC2C  48 00 00 5C */	b lbl_8008E0A8
lbl_8008E050:
/* 8008E050 0008AC30  C0 21 00 44 */	lfs f1, 0x44(r1)
/* 8008E054 0008AC34  7F A3 EB 78 */	mr r3, r29
/* 8008E058 0008AC38  C0 41 00 48 */	lfs f2, 0x48(r1)
/* 8008E05C 0008AC3C  4B FF FB B1 */	bl ftCo_Damage_CalcVel
/* 8008E060 0008AC40  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E064 0008AC44  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008E068 0008AC48  48 00 00 40 */	b lbl_8008E0A8
lbl_8008E06C:
/* 8008E06C 0008AC4C  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008E070 0008AC50  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008E074 0008AC54  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 8008E078 0008AC58  54 00 10 3A */	slwi r0, r0, 2
/* 8008E07C 0008AC5C  7C 03 02 14 */	add r0, r3, r0
/* 8008E080 0008AC60  7F FF 00 2E */	lwzx r31, r31, r0
/* 8008E084 0008AC64  7F A3 EB 78 */	mr r3, r29
/* 8008E088 0008AC68  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008E08C 0008AC6C  C0 1A 00 00 */	lfs f0, 0(r26)
/* 8008E090 0008AC70  C0 5D 00 F0 */	lfs f2, 0xf0(r29)
/* 8008E094 0008AC74  FC 00 00 50 */	fneg f0, f0
/* 8008E098 0008AC78  C0 3A 00 04 */	lfs f1, 4(r26)
/* 8008E09C 0008AC7C  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008E0A0 0008AC80  EC 40 00 B2 */	fmuls f2, f0, f2
/* 8008E0A4 0008AC84  4B FF FB 69 */	bl ftCo_Damage_CalcVel
lbl_8008E0A8:
/* 8008E0A8 0008AC88  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E0AC 0008AC8C  2C 1C 00 03 */	cmpwi r28, 3
/* 8008E0B0 0008AC90  D0 1D 00 88 */	stfs f0, 0x88(r29)
/* 8008E0B4 0008AC94  D0 1D 00 84 */	stfs f0, 0x84(r29)
/* 8008E0B8 0008AC98  D0 1D 00 80 */	stfs f0, 0x80(r29)
/* 8008E0BC 0008AC9C  D0 1D 00 EC */	stfs f0, 0xec(r29)
/* 8008E0C0 0008ACA0  40 82 00 7C */	bne lbl_8008E13C
/* 8008E0C4 0008ACA4  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 8008E0C8 0008ACA8  2C 00 00 01 */	cmpwi r0, 1
/* 8008E0CC 0008ACAC  40 82 00 70 */	bne lbl_8008E13C
/* 8008E0D0 0008ACB0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E0D4 0008ACB4  C0 03 02 34 */	lfs f0, 0x234(r3)
/* 8008E0D8 0008ACB8  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 8008E0DC 0008ACBC  40 81 00 18 */	ble lbl_8008E0F4
/* 8008E0E0 0008ACC0  C0 03 02 38 */	lfs f0, 0x238(r3)
/* 8008E0E4 0008ACC4  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 8008E0E8 0008ACC8  40 80 00 0C */	bge lbl_8008E0F4
/* 8008E0EC 0008ACCC  3B E0 00 5A */	li r31, 0x5a
/* 8008E0F0 0008ACD0  48 00 00 4C */	b lbl_8008E13C
lbl_8008E0F4:
/* 8008E0F4 0008ACD4  80 63 02 3C */	lwz r3, 0x23c(r3)
/* 8008E0F8 0008ACD8  3C 00 43 30 */	lis r0, 0x4330
/* 8008E0FC 0008ACDC  C8 22 8B 00 */	lfd f1, lbl_804D84E0
/* 8008E100 0008ACE0  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008E104 0008ACE4  C0 5D 18 30 */	lfs f2, 0x1830(r29)
/* 8008E108 0008ACE8  90 61 00 5C */	stw r3, 0x5c(r1)
/* 8008E10C 0008ACEC  90 01 00 58 */	stw r0, 0x58(r1)
/* 8008E110 0008ACF0  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 8008E114 0008ACF4  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008E118 0008ACF8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008E11C 0008ACFC  4C 41 13 82 */	cror 2, 1, 2
/* 8008E120 0008AD00  40 82 00 1C */	bne lbl_8008E13C
/* 8008E124 0008AD04  48 2F 24 05 */	bl HSD_Randf
/* 8008E128 0008AD08  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E12C 0008AD0C  C0 03 02 40 */	lfs f0, 0x240(r3)
/* 8008E130 0008AD10  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E134 0008AD14  40 80 00 08 */	bge lbl_8008E13C
/* 8008E138 0008AD18  3B E0 00 5B */	li r31, 0x5b
lbl_8008E13C:
/* 8008E13C 0008AD1C  2C 19 FF FF */	cmpwi r25, -1
/* 8008E140 0008AD20  41 82 00 08 */	beq lbl_8008E148
/* 8008E144 0008AD24  7F 3F CB 78 */	mr r31, r25
lbl_8008E148:
/* 8008E148 0008AD28  2C 1F 01 45 */	cmpwi r31, 0x145
/* 8008E14C 0008AD2C  41 82 00 1C */	beq lbl_8008E168
/* 8008E150 0008AD30  2C 1E 00 02 */	cmpwi r30, 2
/* 8008E154 0008AD34  41 80 00 14 */	blt lbl_8008E168
/* 8008E158 0008AD38  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008E15C 0008AD3C  28 00 00 05 */	cmplwi r0, 5
/* 8008E160 0008AD40  40 82 00 08 */	bne lbl_8008E168
/* 8008E164 0008AD44  3B E0 00 5A */	li r31, 0x5a
lbl_8008E168:
/* 8008E168 0008AD48  FC 20 E0 90 */	fmr f1, f28
/* 8008E16C 0008AD4C  FC 40 E8 90 */	fmr f2, f29
/* 8008E170 0008AD50  48 29 41 7D */	bl un_803222EC
/* 8008E174 0008AD54  D0 3D 18 A4 */	stfs f1, 0x18a4(r29)
/* 8008E178 0008AD58  80 7D 18 C0 */	lwz r3, 0x18c0(r29)
/* 8008E17C 0008AD5C  80 9D 00 08 */	lwz r4, 8(r29)
/* 8008E180 0008AD60  48 29 41 BD */	bl un_8032233C
/* 8008E184 0008AD64  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E188 0008AD68  FC 1B 00 00 */	fcmpu cr0, f27, f0
/* 8008E18C 0008AD6C  41 82 00 08 */	beq lbl_8008E194
/* 8008E190 0008AD70  D3 7D 00 2C */	stfs f27, 0x2c(r29)
lbl_8008E194:
/* 8008E194 0008AD74  80 78 00 2C */	lwz r3, 0x2c(r24)
/* 8008E198 0008AD78  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E19C 0008AD7C  C0 23 18 38 */	lfs f1, 0x1838(r3)
/* 8008E1A0 0008AD80  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008E1A4 0008AD84  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008E1A8 0008AD88  41 82 00 80 */	beq lbl_8008E228
/* 8008E1AC 0008AD8C  2C 00 00 05 */	cmpwi r0, 5
/* 8008E1B0 0008AD90  41 82 00 4C */	beq lbl_8008E1FC
/* 8008E1B4 0008AD94  40 80 00 1C */	bge lbl_8008E1D0
/* 8008E1B8 0008AD98  2C 00 00 02 */	cmpwi r0, 2
/* 8008E1BC 0008AD9C  41 82 00 30 */	beq lbl_8008E1EC
/* 8008E1C0 0008ADA0  40 80 00 5C */	bge lbl_8008E21C
/* 8008E1C4 0008ADA4  2C 00 00 01 */	cmpwi r0, 1
/* 8008E1C8 0008ADA8  40 80 00 14 */	bge lbl_8008E1DC
/* 8008E1CC 0008ADAC  48 00 00 50 */	b lbl_8008E21C
lbl_8008E1D0:
/* 8008E1D0 0008ADB0  2C 00 00 0D */	cmpwi r0, 0xd
/* 8008E1D4 0008ADB4  41 82 00 38 */	beq lbl_8008E20C
/* 8008E1D8 0008ADB8  48 00 00 44 */	b lbl_8008E21C
lbl_8008E1DC:
/* 8008E1DC 0008ADBC  38 9C 00 0B */	addi r4, r28, 0xb
/* 8008E1E0 0008ADC0  38 A0 00 00 */	li r5, 0
/* 8008E1E4 0008ADC4  48 03 1D ED */	bl ftCo_800BFFD0
/* 8008E1E8 0008ADC8  48 00 00 40 */	b lbl_8008E228
lbl_8008E1EC:
/* 8008E1EC 0008ADCC  38 9C 00 0F */	addi r4, r28, 0xf
/* 8008E1F0 0008ADD0  38 A0 00 00 */	li r5, 0
/* 8008E1F4 0008ADD4  48 03 1D DD */	bl ftCo_800BFFD0
/* 8008E1F8 0008ADD8  48 00 00 30 */	b lbl_8008E228
lbl_8008E1FC:
/* 8008E1FC 0008ADDC  38 9C 00 1F */	addi r4, r28, 0x1f
/* 8008E200 0008ADE0  38 A0 00 00 */	li r5, 0
/* 8008E204 0008ADE4  48 03 1D CD */	bl ftCo_800BFFD0
/* 8008E208 0008ADE8  48 00 00 20 */	b lbl_8008E228
lbl_8008E20C:
/* 8008E20C 0008ADEC  38 9C 00 23 */	addi r4, r28, 0x23
/* 8008E210 0008ADF0  38 A0 00 00 */	li r5, 0
/* 8008E214 0008ADF4  48 03 1D BD */	bl ftCo_800BFFD0
/* 8008E218 0008ADF8  48 00 00 10 */	b lbl_8008E228
lbl_8008E21C:
/* 8008E21C 0008ADFC  38 80 00 04 */	li r4, 4
/* 8008E220 0008AE00  38 A0 00 00 */	li r5, 0
/* 8008E224 0008AE04  48 03 1D AD */	bl ftCo_800BFFD0
lbl_8008E228:
/* 8008E228 0008AE08  FC 20 E0 90 */	fmr f1, f28
/* 8008E22C 0008AE0C  80 9D 18 60 */	lwz r4, 0x1860(r29)
/* 8008E230 0008AE10  7F 03 C3 78 */	mr r3, r24
/* 8008E234 0008AE14  4B FF F8 DD */	bl ftCo_8008DB10
/* 8008E238 0008AE18  C0 22 8A F4 */	lfs f1, lbl_804D84D4
/* 8008E23C 0008AE1C  7F 03 C3 78 */	mr r3, r24
/* 8008E240 0008AE20  C0 42 8A F8 */	lfs f2, lbl_804D84D8
/* 8008E244 0008AE24  7F E4 FB 78 */	mr r4, r31
/* 8008E248 0008AE28  FC 60 08 90 */	fmr f3, f1
/* 8008E24C 0008AE2C  38 A0 00 40 */	li r5, 0x40
/* 8008E250 0008AE30  38 C0 00 00 */	li r6, 0
/* 8008E254 0008AE34  4B FD B1 59 */	bl Fighter_ChangeMotionState
/* 8008E258 0008AE38  7F 03 C3 78 */	mr r3, r24
/* 8008E25C 0008AE3C  4B FE 09 49 */	bl ftAnim_8006EBA4
/* 8008E260 0008AE40  48 0D CD B5 */	bl gm_8016B014
/* 8008E264 0008AE44  2C 03 00 00 */	cmpwi r3, 0
/* 8008E268 0008AE48  41 82 00 1C */	beq lbl_8008E284
/* 8008E26C 0008AE4C  7F 03 C3 78 */	mr r3, r24
/* 8008E270 0008AE50  4B FE D4 31 */	bl ftColl_8007B6A0
/* 8008E274 0008AE54  88 1D 22 21 */	lbz r0, 0x2221(r29)
/* 8008E278 0008AE58  38 60 00 01 */	li r3, 1
/* 8008E27C 0008AE5C  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8008E280 0008AE60  98 1D 22 21 */	stb r0, 0x2221(r29)
lbl_8008E284:
/* 8008E284 0008AE64  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E288 0008AE68  C0 03 01 2C */	lfs f0, 0x12c(r3)
/* 8008E28C 0008AE6C  FC 1C 00 40 */	fcmpo cr0, f28, f0
/* 8008E290 0008AE70  40 81 00 0C */	ble lbl_8008E29C
/* 8008E294 0008AE74  38 00 00 01 */	li r0, 1
/* 8008E298 0008AE78  48 00 00 08 */	b lbl_8008E2A0
lbl_8008E29C:
/* 8008E29C 0008AE7C  38 00 00 00 */	li r0, 0
lbl_8008E2A0:
/* 8008E2A0 0008AE80  90 1D 23 44 */	stw r0, 0x2344(r29)
/* 8008E2A4 0008AE84  38 A0 00 00 */	li r5, 0
/* 8008E2A8 0008AE88  3C 60 80 09 */	lis r3, ftCo_Damage_OnEveryHitlag@ha
/* 8008E2AC 0008AE8C  98 BD 23 59 */	stb r5, 0x2359(r29)
/* 8008E2B0 0008AE90  38 03 E4 F0 */	addi r0, r3, ftCo_Damage_OnEveryHitlag@l
/* 8008E2B4 0008AE94  3C 60 80 09 */	lis r3, ftCo_Damage_OnExitHitlag@ha
/* 8008E2B8 0008AE98  90 1D 21 D0 */	stw r0, 0x21d0(r29)
/* 8008E2BC 0008AE9C  38 80 00 FE */	li r4, 0xfe
/* 8008E2C0 0008AEA0  38 03 E7 14 */	addi r0, r3, ftCo_Damage_OnExitHitlag@l
/* 8008E2C4 0008AEA4  98 9D 06 70 */	stb r4, 0x670(r29)
/* 8008E2C8 0008AEA8  38 60 00 01 */	li r3, 1
/* 8008E2CC 0008AEAC  2C 1F 00 5B */	cmpwi r31, 0x5b
/* 8008E2D0 0008AEB0  98 9D 06 71 */	stb r4, 0x671(r29)
/* 8008E2D4 0008AEB4  90 1D 21 D8 */	stw r0, 0x21d8(r29)
/* 8008E2D8 0008AEB8  C0 1D 18 50 */	lfs f0, 0x1850(r29)
/* 8008E2DC 0008AEBC  D0 1D 18 A8 */	stfs f0, 0x18a8(r29)
/* 8008E2E0 0008AEC0  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 8008E2E4 0008AEC4  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8008E2E8 0008AEC8  98 1D 22 1C */	stb r0, 0x221c(r29)
/* 8008E2EC 0008AECC  90 BD 18 AC */	stw r5, 0x18ac(r29)
/* 8008E2F0 0008AED0  40 82 00 48 */	bne lbl_8008E338
/* 8008E2F4 0008AED4  83 38 00 2C */	lwz r25, 0x2c(r24)
/* 8008E2F8 0008AED8  C0 79 00 80 */	lfs f3, 0x80(r25)
/* 8008E2FC 0008AEDC  C0 39 00 8C */	lfs f1, 0x8c(r25)
/* 8008E300 0008AEE0  C0 59 00 84 */	lfs f2, 0x84(r25)
/* 8008E304 0008AEE4  C0 19 00 90 */	lfs f0, 0x90(r25)
/* 8008E308 0008AEE8  EC 23 08 2A */	fadds f1, f3, f1
/* 8008E30C 0008AEEC  EC 42 00 2A */	fadds f2, f2, f0
/* 8008E310 0008AEF0  4B F9 49 21 */	bl atan2f
/* 8008E314 0008AEF4  C0 19 00 2C */	lfs f0, 0x2c(r25)
/* 8008E318 0008AEF8  38 79 00 00 */	addi r3, r25, 0
/* 8008E31C 0008AEFC  38 80 00 02 */	li r4, 2
/* 8008E320 0008AF00  EF 60 00 72 */	fmuls f27, f0, f1
/* 8008E324 0008AF04  4B FE 6C E9 */	bl ftParts_8007500C
/* 8008E328 0008AF08  FC 20 D8 90 */	fmr f1, f27
/* 8008E32C 0008AF0C  38 83 00 00 */	addi r4, r3, 0
/* 8008E330 0008AF10  38 79 00 00 */	addi r3, r25, 0
/* 8008E334 0008AF14  4B FE 75 F9 */	bl ftParts_8007592C
lbl_8008E338:
/* 8008E338 0008AF18  38 00 00 FF */	li r0, 0xff
/* 8008E33C 0008AF1C  98 1D 06 7F */	stb r0, 0x67f(r29)
/* 8008E340 0008AF20  7F A3 EB 78 */	mr r3, r29
/* 8008E344 0008AF24  48 00 19 75 */	bl ftCo_Damage_SetMv8FromKbThreshold
/* 8008E348 0008AF28  80 1D 23 48 */	lwz r0, 0x2348(r29)
/* 8008E34C 0008AF2C  2C 00 00 00 */	cmpwi r0, 0
/* 8008E350 0008AF30  41 82 00 0C */	beq lbl_8008E35C
/* 8008E354 0008AF34  38 00 00 01 */	li r0, 1
/* 8008E358 0008AF38  90 1D 23 48 */	stw r0, 0x2348(r29)
lbl_8008E35C:
/* 8008E35C 0008AF3C  2C 1C 00 03 */	cmpwi r28, 3
/* 8008E360 0008AF40  40 82 00 24 */	bne lbl_8008E384
/* 8008E364 0008AF44  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008E368 0008AF48  C0 04 05 E8 */	lfs f0, 0x5e8(r4)
/* 8008E36C 0008AF4C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008E370 0008AF50  4C 41 13 82 */	cror 2, 1, 2
/* 8008E374 0008AF54  40 82 00 10 */	bne lbl_8008E384
/* 8008E378 0008AF58  7F A3 EB 78 */	mr r3, r29
/* 8008E37C 0008AF5C  80 84 05 EC */	lwz r4, 0x5ec(r4)
/* 8008E380 0008AF60  4B FF 0C 41 */	bl ftCommon_8007EFC0
lbl_8008E384:
/* 8008E384 0008AF64  2C 1B 00 00 */	cmpwi r27, 0
/* 8008E388 0008AF68  41 82 00 5C */	beq lbl_8008E3E4
/* 8008E38C 0008AF6C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E390 0008AF70  C0 03 02 0C */	lfs f0, 0x20c(r3)
/* 8008E394 0008AF74  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E398 0008AF78  4C 41 13 82 */	cror 2, 1, 2
/* 8008E39C 0008AF7C  40 82 00 20 */	bne lbl_8008E3BC
/* 8008E3A0 0008AF80  38 00 00 4F */	li r0, 0x4f
/* 8008E3A4 0008AF84  90 1D 19 08 */	stw r0, 0x1908(r29)
/* 8008E3A8 0008AF88  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 8008E3AC 0008AF8C  80 63 00 4C */	lwz r3, 0x4c(r3)
/* 8008E3B0 0008AF90  80 03 00 20 */	lwz r0, 0x20(r3)
/* 8008E3B4 0008AF94  90 1D 19 0C */	stw r0, 0x190c(r29)
/* 8008E3B8 0008AF98  48 00 00 2C */	b lbl_8008E3E4
lbl_8008E3BC:
/* 8008E3BC 0008AF9C  C0 03 02 08 */	lfs f0, 0x208(r3)
/* 8008E3C0 0008AFA0  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E3C4 0008AFA4  4C 41 13 82 */	cror 2, 1, 2
/* 8008E3C8 0008AFA8  40 82 00 1C */	bne lbl_8008E3E4
/* 8008E3CC 0008AFAC  38 00 00 50 */	li r0, 0x50
/* 8008E3D0 0008AFB0  90 1D 19 08 */	stw r0, 0x1908(r29)
/* 8008E3D4 0008AFB4  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 8008E3D8 0008AFB8  80 63 00 4C */	lwz r3, 0x4c(r3)
/* 8008E3DC 0008AFBC  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 8008E3E0 0008AFC0  90 1D 19 0C */	stw r0, 0x190c(r29)
lbl_8008E3E4:
/* 8008E3E4 0008AFC4  2C 1C 00 03 */	cmpwi r28, 3
/* 8008E3E8 0008AFC8  40 82 00 50 */	bne lbl_8008E438
/* 8008E3EC 0008AFCC  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 8008E3F0 0008AFD0  2C 00 00 01 */	cmpwi r0, 1
/* 8008E3F4 0008AFD4  40 82 00 44 */	bne lbl_8008E438
/* 8008E3F8 0008AFD8  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E3FC 0008AFDC  C0 03 01 74 */	lfs f0, 0x174(r3)
/* 8008E400 0008AFE0  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E404 0008AFE4  4C 41 13 82 */	cror 2, 1, 2
/* 8008E408 0008AFE8  40 82 00 0C */	bne lbl_8008E414
/* 8008E40C 0008AFEC  38 60 00 04 */	li r3, 4
/* 8008E410 0008AFF0  48 00 00 20 */	b lbl_8008E430
lbl_8008E414:
/* 8008E414 0008AFF4  C0 03 01 70 */	lfs f0, 0x170(r3)
/* 8008E418 0008AFF8  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E41C 0008AFFC  4C 41 13 82 */	cror 2, 1, 2
/* 8008E420 0008B000  40 82 00 0C */	bne lbl_8008E42C
/* 8008E424 0008B004  38 60 00 03 */	li r3, 3
/* 8008E428 0008B008  48 00 00 08 */	b lbl_8008E430
lbl_8008E42C:
/* 8008E42C 0008B00C  38 60 00 02 */	li r3, 2
lbl_8008E430:
/* 8008E430 0008B010  38 9D 00 B0 */	addi r4, r29, 0xb0
/* 8008E434 0008B014  4B FA 2A 11 */	bl Camera_80030E44
lbl_8008E438:
/* 8008E438 0008B018  7F 03 C3 78 */	mr r3, r24
/* 8008E43C 0008B01C  4B FF 13 E9 */	bl ftCommon_8007F824
/* 8008E440 0008B020  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008E444 0008B024  2C 00 01 45 */	cmpwi r0, 0x145
/* 8008E448 0008B028  41 82 00 20 */	beq lbl_8008E468
/* 8008E44C 0008B02C  2C 1E 00 02 */	cmpwi r30, 2
/* 8008E450 0008B030  41 80 00 18 */	blt lbl_8008E468
/* 8008E454 0008B034  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008E458 0008B038  28 00 00 05 */	cmplwi r0, 5
/* 8008E45C 0008B03C  40 82 00 0C */	bne lbl_8008E468
/* 8008E460 0008B040  7F 03 C3 78 */	mr r3, r24
/* 8008E464 0008B044  48 00 26 FD */	bl ftCo_80090B60
lbl_8008E468:
/* 8008E468 0008B048  BB 01 00 70 */	lmw r24, 0x70(r1)
/* 8008E46C 0008B04C  80 01 00 CC */	lwz r0, 0xcc(r1)
/* 8008E470 0008B050  CB E1 00 C0 */	lfd f31, 0xc0(r1)
/* 8008E474 0008B054  CB C1 00 B8 */	lfd f30, 0xb8(r1)
/* 8008E478 0008B058  CB A1 00 B0 */	lfd f29, 0xb0(r1)
/* 8008E47C 0008B05C  CB 81 00 A8 */	lfd f28, 0xa8(r1)
/* 8008E480 0008B060  CB 61 00 A0 */	lfd f27, 0xa0(r1)
/* 8008E484 0008B064  CB 41 00 98 */	lfd f26, 0x98(r1)
/* 8008E488 0008B068  CB 21 00 90 */	lfd f25, 0x90(r1)
/* 8008E48C 0008B06C  38 21 00 C8 */	addi r1, r1, 0xc8
/* 8008E490 0008B070  7C 08 03 A6 */	mtlr r0
/* 8008E494 0008B074  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static float calcAngle(float angle)
{
    float x = cosf(angle) + cosf(M_PI_2);
    float y = sinf(angle) + sinf(M_PI_2);
    if (x * x + y * y <= 0.0001f) {
        return 0;
    }
    return atan2f(y, x);
}

static void inlineA0(ftCo_GObj* gobj, float f1, float f2)
{
    {
        ftCo_Fighter* fp = gobj->user_data;
        efAsync_Spawn(gobj, fp->x60C, 4U, 0x406U, fp->parts[FtPart_TopN].joint,
                      f1, fp, f2);
    }
}

static void inlineA1(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftParts_8007592C(fp, ftParts_8007500C(fp, FtPart_XRotN),
                     fp->facing_dir *
                         atan2f(fp->self_vel.x + fp->x8c_kb_vel.x,
                                fp->self_vel.y + fp->x8c_kb_vel.y));
}

void ftCo_8008DCE0(ftCo_GObj* gobj, int arg1, float facing_dir)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[0x38] = { 0 };
#endif
    float temp_f30;
    Vec3 pos;
    float sp40;
    Vec3* normal;
    float temp_f1_2;
    float temp_f1_3;
    float temp_f2;
    float var_f31;
    float kb_angle;
    s32 var_r0;
    bool var_r30;
    ftCo_Fighter* fp = gobj->user_data;
    enum_t var_r28;
    FtMotionId msid;
    float x;
    float y;
    int var_r27 = 1;
    float kb_applied = fp->dmg.kb_applied;
    Fighter_8006CDA4(fp, fp->dmg.x1838_percentTemp, ftCo_803C5520[0][0]);
    fp->dmg.kb_applied1 = kb_applied;
    pl_80040270(fp->player_id, fp->x221F_b4, kb_applied);
    temp_f30 = kb_applied * p_ftCommonData->x154;
    fp->mv.co.damage.x0 = (int) temp_f30;
    if (!fp->mv.co.damage.x0) {
        fp->mv.co.damage.x0 = 1;
    }
    {
        if (temp_f30 < p_ftCommonData->x158) {
            var_r30 = 0;
            goto block_9;
        } else {
            if (!(temp_f30 < p_ftCommonData->x15C)) {
                goto block_6;
            }
            var_r30 = 1;
            goto block_9;
        }
    block_6:
        if (!(temp_f30 < p_ftCommonData->x160)) {
            goto block_8;
        }
        var_r30 = 2;
        goto block_9;
    block_8:
        var_r30 = 3;
    block_9:
        var_r28 = var_r30;
        if (arg1 == -1) {
            goto block_11;
        }
        var_r28 = 3;
    block_11:
        fp->mv.co.damage.x1A = 0;
        var_f31 = kb_applied * p_ftCommonData->x100;
        fp->mv.co.damage.x14 = 0;
        kb_angle = ftCo_Damage_CalcAngle(fp, kb_applied);
        if (var_r30 < 2) {
            goto block_17;
        }
        if ((u32) M2C_FIELD(fp, u32*, 0x1860) != 5U) {
            goto block_17;
        }
        kb_angle = calcAngle(kb_angle);
    block_17:
        x = var_f31 * cosf(kb_angle);
        y = var_f31 * sinf(kb_angle);
        fp->facing_dir = fp->dmg.x1844_direction;
        if (fp->ground_or_air != GA_Air) {
            goto block_21;
        }
        msid = ftCo_803C5520[var_r28 * 12][fp->dmg.x184c_damaged_hurtbox + 12];
        if (!ftCo_Damage_CheckAirMotion(fp)) {
            goto block_20;
        }
        var_f31 *= p_ftCommonData->x190;
        x = var_f31 * cosf(kb_angle);
        y = var_f31 * sinf(kb_angle);
    block_20:
        ftCo_Damage_CalcVel(fp, -x * fp->facing_dir, y);
        fp->xF0_ground_kb_vel = 0;
        goto block_28;
    block_21:
        normal = &fp->coll_data.floor.normal;
        pos.x = -x * fp->facing_dir;
        pos.y = y;
        pos.z = 0;
        temp_f1_2 = lbVector_Angle(normal, &pos);
        if (!(temp_f1_2 < M_PI_2)) {
            goto block_23;
        }
        msid = (int) *(ftCo_803C5520 +
                       ((var_r28 * 0xC) + (M2C_FIELD(fp, s32*, 0x184C) * 4)));
        ftCommon_8007D5D4(fp);
        ftCo_Damage_CalcVel(fp, pos.x, pos.y);
        fp->xF0_ground_kb_vel = 0;
        goto block_28;
    block_23:
        if (var_r28 != 3) {
            goto block_27;
        }
        ftCommon_8007D5D4(fp);
        msid = (int) *(ftCo_803C5520 + ((var_r28 * 0xC) +
                                        (fp->dmg.x184c_damaged_hurtbox * 4)));
        if (!(temp_f1_2 >
              (float) (M_PI_2 +
                       (double) M2C_FIELD(p_ftCommonData, float*, 0x1E8))))
        {
            goto block_26;
        }
        ftCo_Damage_CalcVel(fp, pos.x, -pos.y * p_ftCommonData->x1EC);
        var_r27 = 0;
        fp->xF0_ground_kb_vel = 0;
        temp_f1_3 = atan2f(-normal->x, normal->y);
        sp40 = temp_f1_3;
        inlineA0(gobj, sp40, temp_f1_3);
        goto block_28;
    block_26:
        ftCo_Damage_CalcVel(fp, pos.x, pos.y);
        fp->xF0_ground_kb_vel = 0;
        goto block_28;
    block_27:
        msid = (int) *(ftCo_803C5520 +
                       ((var_r28 * 0xC) + (M2C_FIELD(fp, s32*, 0x184C) * 4)));
        fp->xF0_ground_kb_vel = pos.x;
        temp_f2 = fp->xF0_ground_kb_vel;
        ftCo_Damage_CalcVel(fp, normal->y * temp_f2, -normal->x * temp_f2);
    block_28:
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
        fp->gr_vel = 0;
        if (var_r28 != 3) {
            goto block_36;
        }
        if (fp->ground_or_air != GA_Air) {
            goto block_36;
        }
        if (!(kb_angle > M2C_FIELD(p_ftCommonData, float*, 0x234))) {
            goto block_33;
        }
        if (!(kb_angle < M2C_FIELD(p_ftCommonData, float*, 0x238))) {
            goto block_33;
        }
        msid = 0x5A;
        goto block_36;
    block_33:
        if (!(fp->dmg.x1830_percent >=
              (float) M2C_FIELD(p_ftCommonData, s32*, 0x23C)))
        {
            goto block_36;
        }
        if (!(HSD_Randf() < M2C_FIELD(p_ftCommonData, float*, 0x240))) {
            goto block_36;
        }
        msid = 0x5B;
    block_36:
        if (arg1 == -1) {
            goto block_38;
        }
        msid = arg1;
    block_38:
        if (msid == 0x145) {
            goto block_42;
        }
        if (var_r30 < 2) {
            goto block_42;
        }
        if ((u32) M2C_FIELD(fp, u32*, 0x1860) != 5U) {
            goto block_42;
        }
        msid = 0x5A;
    block_42:
        M2C_FIELD(fp, float*, 0x18A4) = un_803222EC(kb_applied, kb_angle);
        un_8032233C(M2C_FIELD(fp, s32*, 0x18C0), M2C_FIELD(fp, s32*, 8));
        if (!facing_dir) {
            goto block_44;
        }
        M2C_FIELD(fp, float*, 0x2C) = facing_dir;
    }
block_44:

    ftCo_8008DA4C(gobj, var_r28, 0);
    ftCo_8008DB10(gobj, (s32) M2C_FIELD(fp, u32*, 0x1860), kb_applied);
    Fighter_ChangeMotionState(gobj, msid, 0x40U, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    if (!gm_8016B014()) {
        goto block_60;
    }
    ftColl_8007B6A0(gobj);
    fp->x2221_b1 = true;
block_60:
    if (!(kb_applied > p_ftCommonData->x12C)) {
        goto block_62;
    }
    var_r0 = 1;
    goto block_63;
block_62:
    var_r0 = 0;
block_63:
    M2C_FIELD(fp, s32*, 0x2344) = var_r0;
    M2C_FIELD(fp, s8*, 0x2359) = 0;
    M2C_FIELD(fp, void (**)(ftCo_GObj*), 0x21D0) = ftCo_Damage_OnEveryHitlag;
    fp->x670_timer_lstick_tilt_x = 0xFE;
    fp->x671_timer_lstick_tilt_y = 0xFE;
    M2C_FIELD(fp, void (**)(ftCo_GObj*), 0x21D8) = ftCo_Damage_OnExitHitlag;
    M2C_FIELD(fp, float*, 0x18A8) = (float) M2C_FIELD(fp, float*, 0x1850);
    fp->x221C_b6 = true;
    M2C_FIELD(fp, s32*, 0x18AC) = (s32) 0;
    if (msid == 0x5B) {
        inlineA1(gobj);
    }
    fp->x67F = 0xFF;
    ftCo_Damage_SetMv8FromKbThreshold(fp);
    if (M2C_FIELD(fp, s32*, 0x2348) == 0) {
        goto block_67;
    }
    fp->mv.co.damage.x8 = 1;
block_67:
    if (var_r28 != 3) {
        goto block_70;
    }
    if (!(var_f31 >= M2C_FIELD(p_ftCommonData, float*, 0x5E8))) {
        goto block_70;
    }
    ftCommon_8007EFC0(fp, M2C_FIELD(p_ftCommonData, u32*, 0x5EC));
block_70:
    if (var_r27 == 0) {
        goto block_75;
    }
    if (!(temp_f30 >= M2C_FIELD(p_ftCommonData, float*, 0x20C))) {
        goto block_73;
    }
    M2C_FIELD(fp, s32*, 0x1908) = 0x4F;
    M2C_FIELD(fp, s32*, 0x190C) = (s32) M2C_FIELD(
        M2C_FIELD(M2C_FIELD(fp, void**, 0x10C), void**, 0x4C), s32*, 0x20);
    goto block_75;
block_73:
    if (!(temp_f30 >= M2C_FIELD(p_ftCommonData, float*, 0x208))) {
        goto block_75;
    }
    M2C_FIELD(fp, s32*, 0x1908) = 0x50;
    M2C_FIELD(fp, s32*, 0x190C) = (s32) M2C_FIELD(
        M2C_FIELD(M2C_FIELD(fp, void**, 0x10C), void**, 0x4C), s32*, 0x1C);
block_75:
    if (var_r28 != 3) {
        goto block_83;
    }
    if (fp->ground_or_air != GA_Air) {
        goto block_83;
    }
    if (!(temp_f30 >= M2C_FIELD(p_ftCommonData, float*, 0x174))) {
        goto block_79;
    }
    {
        enum_t cam_enum = 4;
        goto block_82;
    block_79:
        if (!(temp_f30 >= p_ftCommonData->x170)) {
            goto block_81;
        }
        cam_enum = 3;
        goto block_82;
    block_81:
        cam_enum = 2;
    block_82:
        Camera_80030E44(cam_enum, &fp->cur_pos);
    }
block_83:
    ftCommon_8007F824(gobj);
    if (fp->motion_id == 0x145) {
        return;
    }
    if (var_r30 < 2) {
        return;
    }
    if ((u32) fp->dmg.x1860 == 5U) {
        ftCo_80090B60(gobj);
    }
}
#endif

bool ftCo_Damage_CheckAirMotion(ftCo_Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_JumpF:
    case ftCo_MS_JumpB:
    case ftCo_MS_JumpAerialF:
    case ftCo_MS_JumpAerialB:
    case ftCo_MS_Fall:
    case ftCo_MS_FallF:
    case ftCo_MS_FallB:
    case ftCo_MS_FallAerial:
    case ftCo_MS_FallAerialF:
    case ftCo_MS_FallAerialB:
    case ftCo_MS_FallSpecial:
    case ftCo_MS_FallSpecialF:
    case ftCo_MS_FallSpecialB:
    case ftCo_MS_DamageFall:
    case ftCo_MS_EscapeAir:
        if (fp->x680 <= p_ftCommonData->x18C &&
            fp->x684 >= p_ftCommonData->x1C)
        {
            return true;
        }
    default:
        return false;
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08E4F0 */ /* static */ void ftCo_Damage_OnEveryHitlag(ftCo_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 8008E4F0 0008B0D0  7C 08 02 A6 */	mflr r0
/* 8008E4F4 0008B0D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008E4F8 0008B0D8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008E4FC 0008B0DC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008E500 0008B0E0  88 03 22 1A */	lbz r0, 0x221a(r3)
/* 8008E504 0008B0E4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008E508 0008B0E8  41 82 00 8C */	beq lbl_8008E594
/* 8008E50C 0008B0EC  C0 63 06 20 */	lfs f3, 0x620(r3)
/* 8008E510 0008B0F0  C0 43 06 24 */	lfs f2, 0x624(r3)
/* 8008E514 0008B0F4  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008E518 0008B0F8  EC 23 00 F2 */	fmuls f1, f3, f3
/* 8008E51C 0008B0FC  EC 02 00 B2 */	fmuls f0, f2, f2
/* 8008E520 0008B100  C0 84 04 B0 */	lfs f4, 0x4b0(r4)
/* 8008E524 0008B104  EC 21 00 2A */	fadds f1, f1, f0
/* 8008E528 0008B108  EC 04 01 32 */	fmuls f0, f4, f4
/* 8008E52C 0008B10C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E530 0008B110  4C 41 13 82 */	cror 2, 1, 2
/* 8008E534 0008B114  40 82 00 60 */	bne lbl_8008E594
/* 8008E538 0008B118  88 03 06 70 */	lbz r0, 0x670(r3)
/* 8008E53C 0008B11C  80 A4 04 B4 */	lwz r5, 0x4b4(r4)
/* 8008E540 0008B120  7C 00 28 00 */	cmpw r0, r5
/* 8008E544 0008B124  41 80 00 10 */	blt lbl_8008E554
/* 8008E548 0008B128  88 03 06 71 */	lbz r0, 0x671(r3)
/* 8008E54C 0008B12C  7C 00 28 00 */	cmpw r0, r5
/* 8008E550 0008B130  40 80 00 44 */	bge lbl_8008E594
lbl_8008E554:
/* 8008E554 0008B134  C0 84 04 B8 */	lfs f4, 0x4b8(r4)
/* 8008E558 0008B138  38 00 00 FE */	li r0, 0xfe
/* 8008E55C 0008B13C  C0 03 00 B0 */	lfs f0, 0xb0(r3)
/* 8008E560 0008B140  EC 23 01 32 */	fmuls f1, f3, f4
/* 8008E564 0008B144  EC 42 01 32 */	fmuls f2, f2, f4
/* 8008E568 0008B148  EC 00 08 2A */	fadds f0, f0, f1
/* 8008E56C 0008B14C  D0 03 00 B0 */	stfs f0, 0xb0(r3)
/* 8008E570 0008B150  C0 03 00 B4 */	lfs f0, 0xb4(r3)
/* 8008E574 0008B154  EC 00 10 2A */	fadds f0, f0, f2
/* 8008E578 0008B158  D0 03 00 B4 */	stfs f0, 0xb4(r3)
/* 8008E57C 0008B15C  98 03 06 70 */	stb r0, 0x670(r3)
/* 8008E580 0008B160  98 03 06 71 */	stb r0, 0x671(r3)
/* 8008E584 0008B164  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 8008E588 0008B168  88 63 00 0C */	lbz r3, 0xc(r3)
/* 8008E58C 0008B16C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008E590 0008B170  4B FB 1C 61 */	bl pl_800401F0
lbl_8008E594:
/* 8008E594 0008B174  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008E598 0008B178  38 21 00 08 */	addi r1, r1, 8
/* 8008E59C 0008B17C  7C 08 03 A6 */	mtlr r0
/* 8008E5A0 0008B180  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

#define SOLUTION 1
void ftCo_Damage_OnEveryHitlag(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221A_b2) {
        float lstick_x = fp->input.lstick.x;
        float lstick_y = fp->input.lstick.y;
        float cd_x4B0 = p_ftCommonData->x4B0;
        if (lstick_x * lstick_x + lstick_y * lstick_y == cd_x4B0 * cd_x4B0) {
            s32 cd_x4B4 = p_ftCommonData->x4B4;
#if SOLUTION == 0
            if (((M2C_FIELD(fp, u8*, 0x670) < cd_x4B4) ||
                 M2C_FIELD(fp, u8*, 0x671) < cd_x4B4))
#else
            if (((fp->x670_timer_lstick_tilt_x < cd_x4B4) ||
                 fp->x671_timer_lstick_tilt_y < cd_x4B4))
#endif
            {
                float cd_x4B8 = p_ftCommonData->x4B8;
                float scaled_lstick_x = lstick_x * cd_x4B8;
                float scaled_lstick_y = lstick_y * cd_x4B8;
                fp->cur_pos.x += scaled_lstick_x;
                fp->cur_pos.y += scaled_lstick_y;
#if SOLUTION == 0
                M2C_FIELD(fp, u8*, 0x670) = 0xFE;
                M2C_FIELD(fp, u8*, 0x671) = 0xFE;
#else
                fp->x670_timer_lstick_tilt_x = 0xFE;
                fp->x671_timer_lstick_tilt_y = 0xFE;
#endif
#if SOLUTION == 0
                pl_800401F0(fp->player_id,
                            (M2C_FIELD(fp, u8*, 0x221F) >> 3) & 1,
                            scaled_lstick_x, scaled_lstick_y);
#else
                pl_800401F0(fp->player_id, fp->x221F_b4, scaled_lstick_x,
                            scaled_lstick_y);
#endif
            }
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08E5A4 */ /* static */ void ftCo_8008E5A4(ftCo_Fighter* fp)
{ // clang-format off
    nofralloc
/* 8008E5A4 0008B184  7C 08 02 A6 */	mflr r0
/* 8008E5A8 0008B188  90 01 00 04 */	stw r0, 4(r1)
/* 8008E5AC 0008B18C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8008E5B0 0008B190  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 8008E5B4 0008B194  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 8008E5B8 0008B198  DB A1 00 40 */	stfd f29, 0x40(r1)
/* 8008E5BC 0008B19C  DB 81 00 38 */	stfd f28, 0x38(r1)
/* 8008E5C0 0008B1A0  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8008E5C4 0008B1A4  7C 7F 1B 78 */	mr r31, r3
/* 8008E5C8 0008B1A8  C0 22 8A F4 */	lfs f1, lbl_804D84D4
/* 8008E5CC 0008B1AC  C0 63 06 20 */	lfs f3, 0x620(r3)
/* 8008E5D0 0008B1B0  FC 03 08 00 */	fcmpu cr0, f3, f1
/* 8008E5D4 0008B1B4  40 82 00 10 */	bne lbl_8008E5E4
/* 8008E5D8 0008B1B8  C0 1F 06 24 */	lfs f0, 0x624(r31)
/* 8008E5DC 0008B1BC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8008E5E0 0008B1C0  41 82 01 10 */	beq lbl_8008E6F0
lbl_8008E5E4:
/* 8008E5E4 0008B1C4  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008E5E8 0008B1C8  C3 9F 00 90 */	lfs f28, 0x90(r31)
/* 8008E5EC 0008B1CC  FC 80 08 50 */	fneg f4, f1
/* 8008E5F0 0008B1D0  C0 02 8B 18 */	lfs f0, lbl_804D84F8
/* 8008E5F4 0008B1D4  EF FC 07 32 */	fmuls f31, f28, f28
/* 8008E5F8 0008B1D8  FF A0 08 90 */	fmr f29, f1
/* 8008E5FC 0008B1DC  EC 44 F9 3A */	fmadds f2, f4, f4, f31
/* 8008E600 0008B1E0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008E604 0008B1E4  41 80 00 EC */	blt lbl_8008E6F0
/* 8008E608 0008B1E8  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008E60C 0008B1EC  38 7F 00 8C */	addi r3, r31, 0x8c
/* 8008E610 0008B1F0  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E614 0008B1F4  38 81 00 20 */	addi r4, r1, 0x20
/* 8008E618 0008B1F8  EC 24 00 72 */	fmuls f1, f4, f1
/* 8008E61C 0008B1FC  D0 61 00 20 */	stfs f3, 0x20(r1)
/* 8008E620 0008B200  38 A1 00 14 */	addi r5, r1, 0x14
/* 8008E624 0008B204  EC 7C 08 FA */	fmadds f3, f28, f3, f1
/* 8008E628 0008B208  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008E62C 0008B20C  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 8008E630 0008B210  EC 23 00 F2 */	fmuls f1, f3, f3
/* 8008E634 0008B214  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8008E638 0008B218  EF C1 10 24 */	fdivs f30, f1, f2
/* 8008E63C 0008B21C  48 2B 48 1D */	bl PSVECCrossProduct
/* 8008E640 0008B220  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 8008E644 0008B224  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E648 0008B228  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E64C 0008B22C  40 80 00 08 */	bge lbl_8008E654
/* 8008E650 0008B230  FF C0 F0 50 */	fneg f30, f30
lbl_8008E654:
/* 8008E654 0008B234  FC 20 E0 90 */	fmr f1, f28
/* 8008E658 0008B238  FC 40 E8 90 */	fmr f2, f29
/* 8008E65C 0008B23C  4B F9 45 D5 */	bl atan2f
/* 8008E660 0008B240  EF FD FF 7A */	fmadds f31, f29, f29, f31
/* 8008E664 0008B244  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E668 0008B248  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008E66C 0008B24C  40 81 00 50 */	ble lbl_8008E6BC
/* 8008E670 0008B250  FC 40 F8 34 */	frsqrte f2, f31
/* 8008E674 0008B254  C8 82 8B 20 */	lfd f4, lbl_804D8500
/* 8008E678 0008B258  C8 62 8B 28 */	lfd f3, lbl_804D8508
/* 8008E67C 0008B25C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8008E680 0008B260  FC 44 00 B2 */	fmul f2, f4, f2
/* 8008E684 0008B264  FC 1F 18 3C */	fnmsub f0, f31, f0, f3
/* 8008E688 0008B268  FC 42 00 32 */	fmul f2, f2, f0
/* 8008E68C 0008B26C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8008E690 0008B270  FC 44 00 B2 */	fmul f2, f4, f2
/* 8008E694 0008B274  FC 1F 18 3C */	fnmsub f0, f31, f0, f3
/* 8008E698 0008B278  FC 42 00 32 */	fmul f2, f2, f0
/* 8008E69C 0008B27C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8008E6A0 0008B280  FC 44 00 B2 */	fmul f2, f4, f2
/* 8008E6A4 0008B284  FC 1F 18 3C */	fnmsub f0, f31, f0, f3
/* 8008E6A8 0008B288  FC 02 00 32 */	fmul f0, f2, f0
/* 8008E6AC 0008B28C  FC 1F 00 32 */	fmul f0, f31, f0
/* 8008E6B0 0008B290  FC 00 00 18 */	frsp f0, f0
/* 8008E6B4 0008B294  D0 01 00 0C */	stfs f0, 0xc(r1)
/* 8008E6B8 0008B298  C3 E1 00 0C */	lfs f31, 0xc(r1)
lbl_8008E6BC:
/* 8008E6BC 0008B29C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E6C0 0008B2A0  C0 42 8A F0 */	lfs f2, lbl_804D84D0
/* 8008E6C4 0008B2A4  C0 03 01 A8 */	lfs f0, 0x1a8(r3)
/* 8008E6C8 0008B2A8  EC 02 00 32 */	fmuls f0, f2, f0
/* 8008E6CC 0008B2AC  EF 80 0F BA */	fmadds f28, f0, f30, f1
/* 8008E6D0 0008B2B0  FC 20 E0 90 */	fmr f1, f28
/* 8008E6D4 0008B2B4  48 29 7B 6D */	bl cosf
/* 8008E6D8 0008B2B8  EC 1F 00 72 */	fmuls f0, f31, f1
/* 8008E6DC 0008B2BC  FC 20 E0 90 */	fmr f1, f28
/* 8008E6E0 0008B2C0  D0 1F 00 8C */	stfs f0, 0x8c(r31)
/* 8008E6E4 0008B2C4  48 29 7C F1 */	bl sinf
/* 8008E6E8 0008B2C8  EC 1F 00 72 */	fmuls f0, f31, f1
/* 8008E6EC 0008B2CC  D0 1F 00 90 */	stfs f0, 0x90(r31)
lbl_8008E6F0:
/* 8008E6F0 0008B2D0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8008E6F4 0008B2D4  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 8008E6F8 0008B2D8  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 8008E6FC 0008B2DC  CB A1 00 40 */	lfd f29, 0x40(r1)
/* 8008E700 0008B2E0  CB 81 00 38 */	lfd f28, 0x38(r1)
/* 8008E704 0008B2E4  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8008E708 0008B2E8  38 21 00 58 */	addi r1, r1, 0x58
/* 8008E70C 0008B2EC  7C 08 03 A6 */	mtlr r0
/* 8008E710 0008B2F0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_8008E5A4(Fighter* fp)
{
    if (fp->input.lstick.x || fp->input.lstick.y) {
        float lstick_x = fp->input.lstick.x;
        float kb_x = fp->x8c_kb_vel.x;
        float kb_y = fp->x8c_kb_vel.y;
        float kb_vel_x_neg = -kb_x;
        float kb_mag = kb_vel_x_neg * kb_vel_x_neg + kb_y * kb_y;
        if (!(kb_mag < 0.00001f)) {
            Vec3 lstick_vec3;
            lstick_vec3.x = lstick_x;
            {
                float lstick_y = fp->input.lstick.y;
                float f3 = kb_y * lstick_x + kb_vel_x_neg * lstick_y;
                lstick_vec3.y = lstick_y;
                lstick_vec3.z = 0;
                {
                    float f30 = f3 * f3 / kb_mag;
                    Vec3 kb_vel_cross_lstick;
                    PSVECCrossProduct(&fp->x8c_kb_vel, &lstick_vec3,
                                      &kb_vel_cross_lstick);
                    if (kb_vel_cross_lstick.z < 0) {
                        f30 = -f30;
                    }
                    {
                        float angle = atan2f(kb_y, kb_x);
                        float kb_mag = sqrtf(kb_x * kb_x + kb_y * kb_y);
                        angle += deg_to_rad * p_ftCommonData->x1A8 * f30;
                        fp->x8c_kb_vel.x = kb_mag * cosf(angle);
                        fp->x8c_kb_vel.y = kb_mag * sinf(angle);
                    }
                }
            }
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08E714 */ /* static */ void ftCo_Damage_OnExitHitlag(ftCo_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 8008E714 0008B2F4  7C 08 02 A6 */	mflr r0
/* 8008E718 0008B2F8  90 01 00 04 */	stw r0, 4(r1)
/* 8008E71C 0008B2FC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008E720 0008B300  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8008E724 0008B304  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 8008E728 0008B308  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008E72C 0008B30C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008E730 0008B310  7C 7E 1B 78 */	mr r30, r3
/* 8008E734 0008B314  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008E738 0008B318  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E73C 0008B31C  C0 5F 06 20 */	lfs f2, 0x620(r31)
/* 8008E740 0008B320  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008E744 0008B324  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8008E748 0008B328  C0 03 04 B0 */	lfs f0, 0x4b0(r3)
/* 8008E74C 0008B32C  EC 21 00 72 */	fmuls f1, f1, f1
/* 8008E750 0008B330  EC 00 00 32 */	fmuls f0, f0, f0
/* 8008E754 0008B334  EC 22 08 2A */	fadds f1, f2, f1
/* 8008E758 0008B338  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E75C 0008B33C  4C 41 13 82 */	cror 2, 1, 2
/* 8008E760 0008B340  40 82 00 0C */	bne lbl_8008E76C
/* 8008E764 0008B344  38 00 00 01 */	li r0, 1
/* 8008E768 0008B348  48 00 00 08 */	b lbl_8008E770
lbl_8008E76C:
/* 8008E76C 0008B34C  38 00 00 00 */	li r0, 0
lbl_8008E770:
/* 8008E770 0008B350  2C 00 00 00 */	cmpwi r0, 0
/* 8008E774 0008B354  40 82 00 14 */	bne lbl_8008E788
/* 8008E778 0008B358  7F E3 FB 78 */	mr r3, r31
/* 8008E77C 0008B35C  48 05 0E 8D */	bl ftCo_800DF608
/* 8008E780 0008B360  2C 03 00 00 */	cmpwi r3, 0
/* 8008E784 0008B364  41 82 00 70 */	beq lbl_8008E7F4
lbl_8008E788:
/* 8008E788 0008B368  7F E3 FB 78 */	mr r3, r31
/* 8008E78C 0008B36C  48 05 0E 7D */	bl ftCo_800DF608
/* 8008E790 0008B370  2C 03 00 00 */	cmpwi r3, 0
/* 8008E794 0008B374  41 82 00 20 */	beq lbl_8008E7B4
/* 8008E798 0008B378  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E79C 0008B37C  C0 3F 06 38 */	lfs f1, 0x638(r31)
/* 8008E7A0 0008B380  C0 43 04 BC */	lfs f2, 0x4bc(r3)
/* 8008E7A4 0008B384  C0 1F 06 3C */	lfs f0, 0x63c(r31)
/* 8008E7A8 0008B388  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008E7AC 0008B38C  EC 40 00 B2 */	fmuls f2, f0, f2
/* 8008E7B0 0008B390  48 00 00 1C */	b lbl_8008E7CC
lbl_8008E7B4:
/* 8008E7B4 0008B394  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E7B8 0008B398  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008E7BC 0008B39C  C0 43 04 BC */	lfs f2, 0x4bc(r3)
/* 8008E7C0 0008B3A0  C0 1F 06 24 */	lfs f0, 0x624(r31)
/* 8008E7C4 0008B3A4  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008E7C8 0008B3A8  EC 40 00 B2 */	fmuls f2, f0, f2
lbl_8008E7CC:
/* 8008E7CC 0008B3AC  C0 1F 00 B0 */	lfs f0, 0xb0(r31)
/* 8008E7D0 0008B3B0  EC 00 08 2A */	fadds f0, f0, f1
/* 8008E7D4 0008B3B4  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 8008E7D8 0008B3B8  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 8008E7DC 0008B3BC  EC 00 10 2A */	fadds f0, f0, f2
/* 8008E7E0 0008B3C0  D0 1F 00 B4 */	stfs f0, 0xb4(r31)
/* 8008E7E4 0008B3C4  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8008E7E8 0008B3C8  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8008E7EC 0008B3CC  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008E7F0 0008B3D0  4B FB 1A 01 */	bl pl_800401F0
lbl_8008E7F4:
/* 8008E7F4 0008B3D4  80 1F 23 44 */	lwz r0, 0x2344(r31)
/* 8008E7F8 0008B3D8  2C 00 00 00 */	cmpwi r0, 0
/* 8008E7FC 0008B3DC  41 82 00 1C */	beq lbl_8008E818
/* 8008E800 0008B3E0  38 00 00 00 */	li r0, 0
/* 8008E804 0008B3E4  90 1F 23 44 */	stw r0, 0x2344(r31)
/* 8008E808 0008B3E8  7F C3 F3 78 */	mr r3, r30
/* 8008E80C 0008B3EC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008E810 0008B3F0  80 84 01 30 */	lwz r4, 0x130(r4)
/* 8008E814 0008B3F4  4B FE CF 91 */	bl ftColl_8007B7A4
lbl_8008E818:
/* 8008E818 0008B3F8  7F E3 FB 78 */	mr r3, r31
/* 8008E81C 0008B3FC  4B FF FD 89 */	bl ftCo_8008E5A4
/* 8008E820 0008B400  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8008E824 0008B404  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8008E828 0008B408  41 82 00 C0 */	beq lbl_8008E8E8
/* 8008E82C 0008B40C  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008E830 0008B410  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E834 0008B414  FF E0 08 90 */	fmr f31, f1
/* 8008E838 0008B418  C3 DF 00 90 */	lfs f30, 0x90(r31)
/* 8008E83C 0008B41C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008E840 0008B420  40 82 00 0C */	bne lbl_8008E84C
/* 8008E844 0008B424  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 8008E848 0008B428  41 82 00 A0 */	beq lbl_8008E8E8
lbl_8008E84C:
/* 8008E84C 0008B42C  FC 20 F0 90 */	fmr f1, f30
/* 8008E850 0008B430  FC 40 F8 90 */	fmr f2, f31
/* 8008E854 0008B434  4B F9 43 DD */	bl atan2f
/* 8008E858 0008B438  EC 5E 07 B2 */	fmuls f2, f30, f30
/* 8008E85C 0008B43C  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E860 0008B440  EC 9F 17 FA */	fmadds f4, f31, f31, f2
/* 8008E864 0008B444  FF E0 08 90 */	fmr f31, f1
/* 8008E868 0008B448  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008E86C 0008B44C  40 81 00 50 */	ble lbl_8008E8BC
/* 8008E870 0008B450  FC 20 20 34 */	frsqrte f1, f4
/* 8008E874 0008B454  C8 62 8B 20 */	lfd f3, lbl_804D8500
/* 8008E878 0008B458  C8 42 8B 28 */	lfd f2, lbl_804D8508
/* 8008E87C 0008B45C  FC 01 00 72 */	fmul f0, f1, f1
/* 8008E880 0008B460  FC 23 00 72 */	fmul f1, f3, f1
/* 8008E884 0008B464  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008E888 0008B468  FC 21 00 32 */	fmul f1, f1, f0
/* 8008E88C 0008B46C  FC 01 00 72 */	fmul f0, f1, f1
/* 8008E890 0008B470  FC 23 00 72 */	fmul f1, f3, f1
/* 8008E894 0008B474  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008E898 0008B478  FC 21 00 32 */	fmul f1, f1, f0
/* 8008E89C 0008B47C  FC 01 00 72 */	fmul f0, f1, f1
/* 8008E8A0 0008B480  FC 23 00 72 */	fmul f1, f3, f1
/* 8008E8A4 0008B484  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008E8A8 0008B488  FC 01 00 32 */	fmul f0, f1, f0
/* 8008E8AC 0008B48C  FC 04 00 32 */	fmul f0, f4, f0
/* 8008E8B0 0008B490  FC 00 00 18 */	frsp f0, f0
/* 8008E8B4 0008B494  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8008E8B8 0008B498  C0 81 00 10 */	lfs f4, 0x10(r1)
lbl_8008E8BC:
/* 8008E8BC 0008B49C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008E8C0 0008B4A0  FC 20 F8 90 */	fmr f1, f31
/* 8008E8C4 0008B4A4  C0 03 01 AC */	lfs f0, 0x1ac(r3)
/* 8008E8C8 0008B4A8  EF C0 01 32 */	fmuls f30, f0, f4
/* 8008E8CC 0008B4AC  48 29 79 75 */	bl cosf
/* 8008E8D0 0008B4B0  EC 1E 00 72 */	fmuls f0, f30, f1
/* 8008E8D4 0008B4B4  FC 20 F8 90 */	fmr f1, f31
/* 8008E8D8 0008B4B8  D0 1F 00 8C */	stfs f0, 0x8c(r31)
/* 8008E8DC 0008B4BC  48 29 7A F9 */	bl sinf
/* 8008E8E0 0008B4C0  EC 1E 00 72 */	fmuls f0, f30, f1
/* 8008E8E4 0008B4C4  D0 1F 00 90 */	stfs f0, 0x90(r31)
lbl_8008E8E8:
/* 8008E8E8 0008B4C8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008E8EC 0008B4CC  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8008E8F0 0008B4D0  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 8008E8F4 0008B4D4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008E8F8 0008B4D8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008E8FC 0008B4DC  38 21 00 30 */	addi r1, r1, 0x30
/* 8008E900 0008B4E0  7C 08 03 A6 */	mtlr r0
/* 8008E904 0008B4E4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static bool isPointInCircle(float x, float y, float radius)
{
    if (x + y >= radius) {
        return true;
    } else {
        return false;
    }
}

void ftCo_Damage_OnExitHitlag(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (isPointInCircle(SQ(fp->input.lstick.x), SQ(fp->input.lstick.y),
                        SQ(p_ftCommonData->x4B0)) ||
        ftCo_800DF608(fp))
    {
        float x, y;
        if (ftCo_800DF608(fp)) {
            float cd_x4BC = p_ftCommonData->x4BC;
            x = fp->input.cstick.x * cd_x4BC;
            y = fp->input.cstick.y * cd_x4BC;
        } else {
            float cd_x4BC = p_ftCommonData->x4BC;
            x = fp->input.lstick.x * cd_x4BC;
            y = fp->input.lstick.y * cd_x4BC;
        }
        fp->cur_pos.x += x;
        fp->cur_pos.y += y;
        pl_800401F0(fp->player_id, fp->x221F_b4, x, y);
    }
    if (fp->mv.co.damage.x4) {
        fp->mv.co.damage.x4 = false;
        ftColl_8007B7A4(gobj, p_ftCommonData->x130);
    }
    ftCo_8008E5A4(fp);
    if (fp->input.held_inputs & HSD_PAD_LR) {
        float kb_x = fp->x8c_kb_vel.x;
        float kb_y = fp->x8c_kb_vel.y;
        if (kb_x || kb_y) {
            float kb_angle = atan2f(kb_y, kb_x);
            float scaled_kb_mag =
                sqrtf(kb_x * kb_x + kb_y * kb_y) * p_ftCommonData->x1AC;
            fp->x8c_kb_vel.x = scaled_kb_mag * cosf(kb_angle);
            fp->x8c_kb_vel.y = scaled_kb_mag * sinf(kb_angle);
        }
    }
}
#endif

void ftCo_8008E908(ftCo_GObj* gobj, float facing_dir)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221D_b7) {
        fp->x2064_ledgeCooldown = p_ftCommonData->ledge_cooldown;
    }
    {
        uint fp_x1860 = fp->dmg.x1860;
        if ((fp_x1860 == 6 || fp_x1860 == 7) && !fp->x2228_b2) {
            ftCo_800C318C(gobj, fp_x1860 == 6 ? 0 : 1);
        } else {
            ftCo_8008DCE0(gobj, -1, facing_dir);
        }
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08E984 */ bool ftCo_8008E984(ftCo_Fighter* fp)
{ // clang-format off
    nofralloc
/* 8008E984 0008B564  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008E988 0008B568  C0 43 18 50 */	lfs f2, 0x1850(r3)
/* 8008E98C 0008B56C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008E990 0008B570  41 82 00 30 */	beq lbl_8008E9C0
/* 8008E994 0008B574  88 83 22 1A */	lbz r4, 0x221a(r3)
/* 8008E998 0008B578  54 80 DF FF */	rlwinm. r0, r4, 0x1b, 0x1f, 0x1f
/* 8008E99C 0008B57C  41 82 00 2C */	beq lbl_8008E9C8
/* 8008E9A0 0008B580  54 80 E7 FF */	rlwinm. r0, r4, 0x1c, 0x1f, 0x1f
/* 8008E9A4 0008B584  41 82 00 24 */	beq lbl_8008E9C8
/* 8008E9A8 0008B588  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008E9AC 0008B58C  C0 23 18 A8 */	lfs f1, 0x18a8(r3)
/* 8008E9B0 0008B590  C0 04 01 40 */	lfs f0, 0x140(r4)
/* 8008E9B4 0008B594  EC 01 00 2A */	fadds f0, f1, f0
/* 8008E9B8 0008B598  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008E9BC 0008B59C  40 80 00 0C */	bge lbl_8008E9C8
lbl_8008E9C0:
/* 8008E9C0 0008B5A0  38 60 00 01 */	li r3, 1
/* 8008E9C4 0008B5A4  4E 80 00 20 */	blr
lbl_8008E9C8:
/* 8008E9C8 0008B5A8  38 60 00 00 */	li r3, 0
/* 8008E9CC 0008B5AC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftCo_8008E984(Fighter* fp)
{
    if (fp->dmg.kb_applied == 0 ||
        (fp->x221A_b2 && fp->x221A_b3 &&
         fp->dmg.kb_applied < fp->dmg.x18A8 + p_ftCommonData->x140))
    {
        return true;
    } else {
        return false;
    }
}
/* Warning: struct _HSD_VtxDescList is not defined (only forward-declared) */
/* Warning: struct HSD_Spline is not defined (only forward-declared) */
/* Warning: struct _HSD_RObjDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ExpDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ByteCodeExpDesc is not defined (only forward-declared)
 */
/* Warning: struct _HSD_IKHintDesc is not defined (only forward-declared) */
/* Warning: struct UnkFloat6_Camera is not defined (only forward-declared) */
/* Warning: struct _HSD_Rvalue is not defined (only forward-declared) */
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08E9D0 */ void ftCo_8008E9D0(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8008E9D0 0008B5B0  7C 08 02 A6 */	mflr r0
/* 8008E9D4 0008B5B4  90 01 00 04 */	stw r0, 4(r1)
/* 8008E9D8 0008B5B8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008E9DC 0008B5BC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008E9E0 0008B5C0  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008E9E4 0008B5C4  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8008E9E8 0008B5C8  7C 7D 1B 78 */	mr r29, r3
/* 8008E9EC 0008B5CC  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008E9F0 0008B5D0  48 03 A3 11 */	bl ftCo_800C8D00
/* 8008E9F4 0008B5D4  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8008E9F8 0008B5D8  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008E9FC 0008B5DC  41 82 00 0C */	beq lbl_8008EA08
/* 8008EA00 0008B5E0  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008EA04 0008B5E4  40 82 00 0C */	bne lbl_8008EA10
lbl_8008EA08:
/* 8008EA08 0008B5E8  7F A3 EB 78 */	mr r3, r29
/* 8008EA0C 0008B5EC  48 04 D8 79 */	bl ftCo_800DC284
lbl_8008EA10:
/* 8008EA10 0008B5F0  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8008EA14 0008B5F4  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008EA18 0008B5F8  41 82 00 0C */	beq lbl_8008EA24
/* 8008EA1C 0008B5FC  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008EA20 0008B600  40 82 00 0C */	bne lbl_8008EA2C
lbl_8008EA24:
/* 8008EA24 0008B604  7F A3 EB 78 */	mr r3, r29
/* 8008EA28 0008B608  48 04 D9 7D */	bl ftCo_800DC3A4
lbl_8008EA2C:
/* 8008EA2C 0008B60C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008EA30 0008B610  C0 5E 18 50 */	lfs f2, 0x1850(r30)
/* 8008EA34 0008B614  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008EA38 0008B618  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008EA3C 0008B61C  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008EA40 0008B620  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EA44 0008B624  40 80 00 0C */	bge lbl_8008EA50
/* 8008EA48 0008B628  38 80 00 00 */	li r4, 0
/* 8008EA4C 0008B62C  48 00 00 30 */	b lbl_8008EA7C
lbl_8008EA50:
/* 8008EA50 0008B630  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008EA54 0008B634  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EA58 0008B638  40 80 00 0C */	bge lbl_8008EA64
/* 8008EA5C 0008B63C  38 80 00 01 */	li r4, 1
/* 8008EA60 0008B640  48 00 00 1C */	b lbl_8008EA7C
lbl_8008EA64:
/* 8008EA64 0008B644  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008EA68 0008B648  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EA6C 0008B64C  40 80 00 0C */	bge lbl_8008EA78
/* 8008EA70 0008B650  38 80 00 02 */	li r4, 2
/* 8008EA74 0008B654  48 00 00 08 */	b lbl_8008EA7C
lbl_8008EA78:
/* 8008EA78 0008B658  38 80 00 03 */	li r4, 3
lbl_8008EA7C:
/* 8008EA7C 0008B65C  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8008EA80 0008B660  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008EA84 0008B664  C0 23 18 38 */	lfs f1, 0x1838(r3)
/* 8008EA88 0008B668  80 1E 18 60 */	lwz r0, 0x1860(r30)
/* 8008EA8C 0008B66C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008EA90 0008B670  41 82 00 94 */	beq lbl_8008EB24
/* 8008EA94 0008B674  2C 00 00 05 */	cmpwi r0, 5
/* 8008EA98 0008B678  41 82 00 54 */	beq lbl_8008EAEC
/* 8008EA9C 0008B67C  40 80 00 1C */	bge lbl_8008EAB8
/* 8008EAA0 0008B680  2C 00 00 02 */	cmpwi r0, 2
/* 8008EAA4 0008B684  41 82 00 34 */	beq lbl_8008EAD8
/* 8008EAA8 0008B688  40 80 00 6C */	bge lbl_8008EB14
/* 8008EAAC 0008B68C  2C 00 00 01 */	cmpwi r0, 1
/* 8008EAB0 0008B690  40 80 00 14 */	bge lbl_8008EAC4
/* 8008EAB4 0008B694  48 00 00 60 */	b lbl_8008EB14
lbl_8008EAB8:
/* 8008EAB8 0008B698  2C 00 00 0D */	cmpwi r0, 0xd
/* 8008EABC 0008B69C  41 82 00 44 */	beq lbl_8008EB00
/* 8008EAC0 0008B6A0  48 00 00 54 */	b lbl_8008EB14
lbl_8008EAC4:
/* 8008EAC4 0008B6A4  38 84 00 0B */	addi r4, r4, 0xb
/* 8008EAC8 0008B6A8  38 A0 00 00 */	li r5, 0
/* 8008EACC 0008B6AC  48 03 15 05 */	bl ftCo_800BFFD0
/* 8008EAD0 0008B6B0  7C 7F 1B 78 */	mr r31, r3
/* 8008EAD4 0008B6B4  48 00 00 50 */	b lbl_8008EB24
lbl_8008EAD8:
/* 8008EAD8 0008B6B8  38 84 00 0F */	addi r4, r4, 0xf
/* 8008EADC 0008B6BC  38 A0 00 00 */	li r5, 0
/* 8008EAE0 0008B6C0  48 03 14 F1 */	bl ftCo_800BFFD0
/* 8008EAE4 0008B6C4  7C 7F 1B 78 */	mr r31, r3
/* 8008EAE8 0008B6C8  48 00 00 3C */	b lbl_8008EB24
lbl_8008EAEC:
/* 8008EAEC 0008B6CC  38 84 00 1F */	addi r4, r4, 0x1f
/* 8008EAF0 0008B6D0  38 A0 00 00 */	li r5, 0
/* 8008EAF4 0008B6D4  48 03 14 DD */	bl ftCo_800BFFD0
/* 8008EAF8 0008B6D8  7C 7F 1B 78 */	mr r31, r3
/* 8008EAFC 0008B6DC  48 00 00 28 */	b lbl_8008EB24
lbl_8008EB00:
/* 8008EB00 0008B6E0  38 84 00 23 */	addi r4, r4, 0x23
/* 8008EB04 0008B6E4  38 A0 00 00 */	li r5, 0
/* 8008EB08 0008B6E8  48 03 14 C9 */	bl ftCo_800BFFD0
/* 8008EB0C 0008B6EC  7C 7F 1B 78 */	mr r31, r3
/* 8008EB10 0008B6F0  48 00 00 14 */	b lbl_8008EB24
lbl_8008EB14:
/* 8008EB14 0008B6F4  38 80 00 04 */	li r4, 4
/* 8008EB18 0008B6F8  38 A0 00 00 */	li r5, 0
/* 8008EB1C 0008B6FC  48 03 14 B5 */	bl ftCo_800BFFD0
/* 8008EB20 0008B700  7C 7F 1B 78 */	mr r31, r3
lbl_8008EB24:
/* 8008EB24 0008B704  2C 1F 00 00 */	cmpwi r31, 0
/* 8008EB28 0008B708  41 82 00 0C */	beq lbl_8008EB34
/* 8008EB2C 0008B70C  7F A3 EB 78 */	mr r3, r29
/* 8008EB30 0008B710  48 03 18 D9 */	bl ftCo_800C0408
lbl_8008EB34:
/* 8008EB34 0008B714  7F C3 F3 78 */	mr r3, r30
/* 8008EB38 0008B718  4B FF 19 C5 */	bl ftCommon_800804FC
/* 8008EB3C 0008B71C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008EB40 0008B720  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8008EB44 0008B724  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008EB48 0008B728  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8008EB4C 0008B72C  38 21 00 30 */	addi r1, r1, 0x30
/* 8008EB50 0008B730  7C 08 03 A6 */	mtlr r0
/* 8008EB54 0008B734  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline void inlineF0(ftCo_GObj* gobj)
{
    ftCo_800C8D00(gobj);
    {
        ftCo_Fighter* fp = gobj->user_data;
        if (fp->motion_id == 0xe0 || fp->motion_id == 0xe1) {
            ftCo_800DC284(gobj);
        }
        if (fp->motion_id == 0xe3 || fp->motion_id == 0xe4) {
            ftCo_800DC3A4(gobj);
        }
    }
}

void ftCo_8008E9D0(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif

    ftCo_Fighter* fp = gobj->user_data;
    inlineF0(gobj);
    if (ftCo_8008DA4C(gobj, ftCo_8008D8E8(fp->dmg.kb_applied), 0)) {
        ftCo_800C0408(gobj);
    }
    ftCommon_800804FC(fp);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08EB58 */ void ftCo_8008EB58(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8008EB58 0008B738  7C 08 02 A6 */	mflr r0
/* 8008EB5C 0008B73C  90 01 00 04 */	stw r0, 4(r1)
/* 8008EB60 0008B740  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008EB64 0008B744  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008EB68 0008B748  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008EB6C 0008B74C  7C 7E 1B 78 */	mr r30, r3
/* 8008EB70 0008B750  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008EB74 0008B754  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008EB78 0008B758  C0 5F 18 50 */	lfs f2, 0x1850(r31)
/* 8008EB7C 0008B75C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008EB80 0008B760  41 82 00 30 */	beq lbl_8008EBB0
/* 8008EB84 0008B764  88 7F 22 1A */	lbz r3, 0x221a(r31)
/* 8008EB88 0008B768  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008EB8C 0008B76C  41 82 00 2C */	beq lbl_8008EBB8
/* 8008EB90 0008B770  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008EB94 0008B774  41 82 00 24 */	beq lbl_8008EBB8
/* 8008EB98 0008B778  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008EB9C 0008B77C  C0 3F 18 A8 */	lfs f1, 0x18a8(r31)
/* 8008EBA0 0008B780  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008EBA4 0008B784  EC 01 00 2A */	fadds f0, f1, f0
/* 8008EBA8 0008B788  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008EBAC 0008B78C  40 80 00 0C */	bge lbl_8008EBB8
lbl_8008EBB0:
/* 8008EBB0 0008B790  38 00 00 01 */	li r0, 1
/* 8008EBB4 0008B794  48 00 00 08 */	b lbl_8008EBBC
lbl_8008EBB8:
/* 8008EBB8 0008B798  38 00 00 00 */	li r0, 0
lbl_8008EBBC:
/* 8008EBBC 0008B79C  2C 00 00 00 */	cmpwi r0, 0
/* 8008EBC0 0008B7A0  41 82 00 B8 */	beq lbl_8008EC78
/* 8008EBC4 0008B7A4  7F C3 F3 78 */	mr r3, r30
/* 8008EBC8 0008B7A8  48 03 A1 39 */	bl ftCo_800C8D00
/* 8008EBCC 0008B7AC  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008EBD0 0008B7B0  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008EBD4 0008B7B4  41 82 00 0C */	beq lbl_8008EBE0
/* 8008EBD8 0008B7B8  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008EBDC 0008B7BC  40 82 00 0C */	bne lbl_8008EBE8
lbl_8008EBE0:
/* 8008EBE0 0008B7C0  7F C3 F3 78 */	mr r3, r30
/* 8008EBE4 0008B7C4  48 04 D6 A1 */	bl ftCo_800DC284
lbl_8008EBE8:
/* 8008EBE8 0008B7C8  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008EBEC 0008B7CC  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008EBF0 0008B7D0  41 82 00 0C */	beq lbl_8008EBFC
/* 8008EBF4 0008B7D4  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008EBF8 0008B7D8  40 82 00 0C */	bne lbl_8008EC04
lbl_8008EBFC:
/* 8008EBFC 0008B7DC  7F C3 F3 78 */	mr r3, r30
/* 8008EC00 0008B7E0  48 04 D7 A5 */	bl ftCo_800DC3A4
lbl_8008EC04:
/* 8008EC04 0008B7E4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008EC08 0008B7E8  C0 5F 18 50 */	lfs f2, 0x1850(r31)
/* 8008EC0C 0008B7EC  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008EC10 0008B7F0  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008EC14 0008B7F4  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008EC18 0008B7F8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EC1C 0008B7FC  40 80 00 0C */	bge lbl_8008EC28
/* 8008EC20 0008B800  38 A0 00 00 */	li r5, 0
/* 8008EC24 0008B804  48 00 00 30 */	b lbl_8008EC54
lbl_8008EC28:
/* 8008EC28 0008B808  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008EC2C 0008B80C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EC30 0008B810  40 80 00 0C */	bge lbl_8008EC3C
/* 8008EC34 0008B814  38 A0 00 01 */	li r5, 1
/* 8008EC38 0008B818  48 00 00 1C */	b lbl_8008EC54
lbl_8008EC3C:
/* 8008EC3C 0008B81C  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008EC40 0008B820  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EC44 0008B824  40 80 00 0C */	bge lbl_8008EC50
/* 8008EC48 0008B828  38 A0 00 02 */	li r5, 2
/* 8008EC4C 0008B82C  48 00 00 08 */	b lbl_8008EC54
lbl_8008EC50:
/* 8008EC50 0008B830  38 A0 00 03 */	li r5, 3
lbl_8008EC54:
/* 8008EC54 0008B834  80 9F 18 60 */	lwz r4, 0x1860(r31)
/* 8008EC58 0008B838  7F C3 F3 78 */	mr r3, r30
/* 8008EC5C 0008B83C  4B FF ED F1 */	bl ftCo_8008DA4C
/* 8008EC60 0008B840  2C 03 00 00 */	cmpwi r3, 0
/* 8008EC64 0008B844  41 82 00 0C */	beq lbl_8008EC70
/* 8008EC68 0008B848  7F C3 F3 78 */	mr r3, r30
/* 8008EC6C 0008B84C  48 03 17 9D */	bl ftCo_800C0408
lbl_8008EC70:
/* 8008EC70 0008B850  7F E3 FB 78 */	mr r3, r31
/* 8008EC74 0008B854  4B FF 18 89 */	bl ftCommon_800804FC
lbl_8008EC78:
/* 8008EC78 0008B858  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008EC7C 0008B85C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8008EC80 0008B860  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008EC84 0008B864  38 21 00 30 */	addi r1, r1, 0x30
/* 8008EC88 0008B868  7C 08 03 A6 */	mtlr r0
/* 8008EC8C 0008B86C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static bool inlineB0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    float kb_applied = fp->dmg.kb_applied;
    // might not be correct?
    if (kb_applied != 0) {
        return true;
    }
    if (fp->x221A_b2 && fp->x221A_b3 &&
        fp->dmg.kb_applied < fp->dmg.x18A8 + p_ftCommonData->x140)
    {
        return true;
    }
    return false;
}

/// @todo Inline depth.
#ifdef MUST_MATCH
#pragma push
#pragma inline_depth(1)
#endif
void ftCo_8008EB58(ftCo_GObj* gobj)
{
    if (inlineB0(gobj)) {
        ftCo_800C8D00(gobj);
        inlineF0(gobj);
        {
            ftCo_Fighter* fp = gobj->user_data;
            if (ftCo_8008DA4C(gobj, fp->dmg.x1860,
                              ftCo_8008D8E8(fp->dmg.kb_applied)))
            {
                ftCo_800C0408(gobj);
            }
            ftCommon_800804FC(fp);
        }
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08EC90 */ void ftCo_8008EC90(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8008EC90 0008B870  7C 08 02 A6 */	mflr r0
/* 8008EC94 0008B874  90 01 00 04 */	stw r0, 4(r1)
/* 8008EC98 0008B878  94 21 FF 50 */	stwu r1, -0xb0(r1)
/* 8008EC9C 0008B87C  DB E1 00 A8 */	stfd f31, 0xa8(r1)
/* 8008ECA0 0008B880  BF 61 00 94 */	stmw r27, 0x94(r1)
/* 8008ECA4 0008B884  7C 7F 1B 78 */	mr r31, r3
/* 8008ECA8 0008B888  3B C0 00 00 */	li r30, 0
/* 8008ECAC 0008B88C  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8008ECB0 0008B890  C3 E2 8A F4 */	lfs f31, lbl_804D84D4
/* 8008ECB4 0008B894  88 7D 22 20 */	lbz r3, 0x2220(r29)
/* 8008ECB8 0008B898  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008ECBC 0008B89C  40 82 00 18 */	bne lbl_8008ECD4
/* 8008ECC0 0008B8A0  54 60 EF FF */	rlwinm. r0, r3, 0x1d, 0x1f, 0x1f
/* 8008ECC4 0008B8A4  40 82 00 10 */	bne lbl_8008ECD4
/* 8008ECC8 0008B8A8  C0 1D 18 50 */	lfs f0, 0x1850(r29)
/* 8008ECCC 0008B8AC  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 8008ECD0 0008B8B0  40 82 00 BC */	bne lbl_8008ED8C
lbl_8008ECD4:
/* 8008ECD4 0008B8B4  7F E3 FB 78 */	mr r3, r31
/* 8008ECD8 0008B8B8  48 03 A0 29 */	bl ftCo_800C8D00
/* 8008ECDC 0008B8BC  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008ECE0 0008B8C0  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008ECE4 0008B8C4  41 82 00 0C */	beq lbl_8008ECF0
/* 8008ECE8 0008B8C8  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008ECEC 0008B8CC  40 82 00 0C */	bne lbl_8008ECF8
lbl_8008ECF0:
/* 8008ECF0 0008B8D0  7F E3 FB 78 */	mr r3, r31
/* 8008ECF4 0008B8D4  48 04 D5 91 */	bl ftCo_800DC284
lbl_8008ECF8:
/* 8008ECF8 0008B8D8  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008ECFC 0008B8DC  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008ED00 0008B8E0  41 82 00 0C */	beq lbl_8008ED0C
/* 8008ED04 0008B8E4  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008ED08 0008B8E8  40 82 00 0C */	bne lbl_8008ED14
lbl_8008ED0C:
/* 8008ED0C 0008B8EC  7F E3 FB 78 */	mr r3, r31
/* 8008ED10 0008B8F0  48 04 D6 95 */	bl ftCo_800DC3A4
lbl_8008ED14:
/* 8008ED14 0008B8F4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008ED18 0008B8F8  C0 5D 18 50 */	lfs f2, 0x1850(r29)
/* 8008ED1C 0008B8FC  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008ED20 0008B900  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008ED24 0008B904  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008ED28 0008B908  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008ED2C 0008B90C  40 80 00 0C */	bge lbl_8008ED38
/* 8008ED30 0008B910  38 A0 00 00 */	li r5, 0
/* 8008ED34 0008B914  48 00 00 30 */	b lbl_8008ED64
lbl_8008ED38:
/* 8008ED38 0008B918  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008ED3C 0008B91C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008ED40 0008B920  40 80 00 0C */	bge lbl_8008ED4C
/* 8008ED44 0008B924  38 A0 00 01 */	li r5, 1
/* 8008ED48 0008B928  48 00 00 1C */	b lbl_8008ED64
lbl_8008ED4C:
/* 8008ED4C 0008B92C  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008ED50 0008B930  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008ED54 0008B934  40 80 00 0C */	bge lbl_8008ED60
/* 8008ED58 0008B938  38 A0 00 02 */	li r5, 2
/* 8008ED5C 0008B93C  48 00 00 08 */	b lbl_8008ED64
lbl_8008ED60:
/* 8008ED60 0008B940  38 A0 00 03 */	li r5, 3
lbl_8008ED64:
/* 8008ED64 0008B944  80 9D 18 60 */	lwz r4, 0x1860(r29)
/* 8008ED68 0008B948  7F E3 FB 78 */	mr r3, r31
/* 8008ED6C 0008B94C  4B FF EC E1 */	bl ftCo_8008DA4C
/* 8008ED70 0008B950  2C 03 00 00 */	cmpwi r3, 0
/* 8008ED74 0008B954  41 82 00 0C */	beq lbl_8008ED80
/* 8008ED78 0008B958  7F E3 FB 78 */	mr r3, r31
/* 8008ED7C 0008B95C  48 03 16 8D */	bl ftCo_800C0408
lbl_8008ED80:
/* 8008ED80 0008B960  7F A3 EB 78 */	mr r3, r29
/* 8008ED84 0008B964  4B FF 17 79 */	bl ftCommon_800804FC
/* 8008ED88 0008B968  48 00 09 94 */	b lbl_8008F71C
lbl_8008ED8C:
/* 8008ED8C 0008B96C  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008ED90 0008B970  28 00 00 0A */	cmplwi r0, 0xa
/* 8008ED94 0008B974  40 82 00 1C */	bne lbl_8008EDB0
/* 8008ED98 0008B978  7F E3 FB 78 */	mr r3, r31
/* 8008ED9C 0008B97C  48 03 47 9D */	bl ftCo_800C3538
/* 8008EDA0 0008B980  2C 03 00 00 */	cmpwi r3, 0
/* 8008EDA4 0008B984  40 82 09 78 */	bne lbl_8008F71C
/* 8008EDA8 0008B988  C3 FD 00 2C */	lfs f31, 0x2c(r29)
/* 8008EDAC 0008B98C  3B C0 00 01 */	li r30, 1
lbl_8008EDB0:
/* 8008EDB0 0008B990  7F E3 FB 78 */	mr r3, r31
/* 8008EDB4 0008B994  48 03 57 19 */	bl ftCo_800C44CC
/* 8008EDB8 0008B998  2C 03 00 00 */	cmpwi r3, 0
/* 8008EDBC 0008B99C  40 82 09 60 */	bne lbl_8008F71C
/* 8008EDC0 0008B9A0  7F E3 FB 78 */	mr r3, r31
/* 8008EDC4 0008B9A4  48 04 41 E1 */	bl ftCo_800D2FA4
/* 8008EDC8 0008B9A8  2C 03 00 00 */	cmpwi r3, 0
/* 8008EDCC 0008B9AC  40 82 09 50 */	bne lbl_8008F71C
/* 8008EDD0 0008B9B0  80 9D 1A 58 */	lwz r4, 0x1a58(r29)
/* 8008EDD4 0008B9B4  28 04 00 00 */	cmplwi r4, 0
/* 8008EDD8 0008B9B8  41 82 08 48 */	beq lbl_8008F620
/* 8008EDDC 0008B9BC  88 1D 22 1B */	lbz r0, 0x221b(r29)
/* 8008EDE0 0008B9C0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8008EDE4 0008B9C4  40 82 04 8C */	bne lbl_8008F270
/* 8008EDE8 0008B9C8  2C 1E 00 00 */	cmpwi r30, 0
/* 8008EDEC 0008B9CC  83 64 00 2C */	lwz r27, 0x2c(r4)
/* 8008EDF0 0008B9D0  7C 9C 23 78 */	mr r28, r4
/* 8008EDF4 0008B9D4  40 82 03 4C */	bne lbl_8008F140
/* 8008EDF8 0008B9D8  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 8008EDFC 0008B9DC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008EE00 0008B9E0  41 82 00 0C */	beq lbl_8008EE0C
/* 8008EE04 0008B9E4  38 00 00 01 */	li r0, 1
/* 8008EE08 0008B9E8  48 00 00 40 */	b lbl_8008EE48
lbl_8008EE0C:
/* 8008EE0C 0008B9EC  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008EE10 0008B9F0  3C 00 43 30 */	lis r0, 0x4330
/* 8008EE14 0008B9F4  C8 22 8B 00 */	lfd f1, lbl_804D84E0
/* 8008EE18 0008B9F8  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8008EE1C 0008B9FC  C0 5D 18 38 */	lfs f2, 0x1838(r29)
/* 8008EE20 0008BA00  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008EE24 0008BA04  90 61 00 8C */	stw r3, 0x8c(r1)
/* 8008EE28 0008BA08  90 01 00 88 */	stw r0, 0x88(r1)
/* 8008EE2C 0008BA0C  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 8008EE30 0008BA10  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008EE34 0008BA14  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008EE38 0008BA18  40 80 00 0C */	bge lbl_8008EE44
/* 8008EE3C 0008BA1C  38 00 00 01 */	li r0, 1
/* 8008EE40 0008BA20  48 00 00 08 */	b lbl_8008EE48
lbl_8008EE44:
/* 8008EE44 0008BA24  38 00 00 00 */	li r0, 0
lbl_8008EE48:
/* 8008EE48 0008BA28  2C 00 00 00 */	cmpwi r0, 0
/* 8008EE4C 0008BA2C  41 82 02 F4 */	beq lbl_8008F140
/* 8008EE50 0008BA30  C0 5B 18 50 */	lfs f2, 0x1850(r27)
/* 8008EE54 0008BA34  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008EE58 0008BA38  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 8008EE5C 0008BA3C  41 82 01 BC */	beq lbl_8008F018
/* 8008EE60 0008BA40  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008EE64 0008BA44  40 82 00 0C */	bne lbl_8008EE70
/* 8008EE68 0008BA48  38 00 00 01 */	li r0, 1
/* 8008EE6C 0008BA4C  48 00 00 3C */	b lbl_8008EEA8
lbl_8008EE70:
/* 8008EE70 0008BA50  88 7B 22 1A */	lbz r3, 0x221a(r27)
/* 8008EE74 0008BA54  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008EE78 0008BA58  41 82 00 2C */	beq lbl_8008EEA4
/* 8008EE7C 0008BA5C  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008EE80 0008BA60  41 82 00 24 */	beq lbl_8008EEA4
/* 8008EE84 0008BA64  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008EE88 0008BA68  C0 3B 18 A8 */	lfs f1, 0x18a8(r27)
/* 8008EE8C 0008BA6C  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008EE90 0008BA70  EC 01 00 2A */	fadds f0, f1, f0
/* 8008EE94 0008BA74  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008EE98 0008BA78  40 80 00 0C */	bge lbl_8008EEA4
/* 8008EE9C 0008BA7C  38 00 00 01 */	li r0, 1
/* 8008EEA0 0008BA80  48 00 00 08 */	b lbl_8008EEA8
lbl_8008EEA4:
/* 8008EEA4 0008BA84  38 00 00 00 */	li r0, 0
lbl_8008EEA8:
/* 8008EEA8 0008BA88  2C 00 00 00 */	cmpwi r0, 0
/* 8008EEAC 0008BA8C  41 82 00 D8 */	beq lbl_8008EF84
/* 8008EEB0 0008BA90  83 9F 00 2C */	lwz r28, 0x2c(r31)
/* 8008EEB4 0008BA94  7F E3 FB 78 */	mr r3, r31
/* 8008EEB8 0008BA98  48 03 9E 49 */	bl ftCo_800C8D00
/* 8008EEBC 0008BA9C  80 1C 00 10 */	lwz r0, 0x10(r28)
/* 8008EEC0 0008BAA0  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008EEC4 0008BAA4  41 82 00 0C */	beq lbl_8008EED0
/* 8008EEC8 0008BAA8  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008EECC 0008BAAC  40 82 00 0C */	bne lbl_8008EED8
lbl_8008EED0:
/* 8008EED0 0008BAB0  7F E3 FB 78 */	mr r3, r31
/* 8008EED4 0008BAB4  48 04 D3 B1 */	bl ftCo_800DC284
lbl_8008EED8:
/* 8008EED8 0008BAB8  80 1C 00 10 */	lwz r0, 0x10(r28)
/* 8008EEDC 0008BABC  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008EEE0 0008BAC0  41 82 00 0C */	beq lbl_8008EEEC
/* 8008EEE4 0008BAC4  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008EEE8 0008BAC8  40 82 00 0C */	bne lbl_8008EEF4
lbl_8008EEEC:
/* 8008EEEC 0008BACC  7F E3 FB 78 */	mr r3, r31
/* 8008EEF0 0008BAD0  48 04 D4 B5 */	bl ftCo_800DC3A4
lbl_8008EEF4:
/* 8008EEF4 0008BAD4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008EEF8 0008BAD8  C0 5C 18 50 */	lfs f2, 0x1850(r28)
/* 8008EEFC 0008BADC  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008EF00 0008BAE0  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008EF04 0008BAE4  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008EF08 0008BAE8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EF0C 0008BAEC  40 80 00 0C */	bge lbl_8008EF18
/* 8008EF10 0008BAF0  38 A0 00 00 */	li r5, 0
/* 8008EF14 0008BAF4  48 00 00 30 */	b lbl_8008EF44
lbl_8008EF18:
/* 8008EF18 0008BAF8  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008EF1C 0008BAFC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EF20 0008BB00  40 80 00 0C */	bge lbl_8008EF2C
/* 8008EF24 0008BB04  38 A0 00 01 */	li r5, 1
/* 8008EF28 0008BB08  48 00 00 1C */	b lbl_8008EF44
lbl_8008EF2C:
/* 8008EF2C 0008BB0C  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008EF30 0008BB10  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EF34 0008BB14  40 80 00 0C */	bge lbl_8008EF40
/* 8008EF38 0008BB18  38 A0 00 02 */	li r5, 2
/* 8008EF3C 0008BB1C  48 00 00 08 */	b lbl_8008EF44
lbl_8008EF40:
/* 8008EF40 0008BB20  38 A0 00 03 */	li r5, 3
lbl_8008EF44:
/* 8008EF44 0008BB24  80 9C 18 60 */	lwz r4, 0x1860(r28)
/* 8008EF48 0008BB28  7F E3 FB 78 */	mr r3, r31
/* 8008EF4C 0008BB2C  4B FF EB 01 */	bl ftCo_8008DA4C
/* 8008EF50 0008BB30  2C 03 00 00 */	cmpwi r3, 0
/* 8008EF54 0008BB34  41 82 00 0C */	beq lbl_8008EF60
/* 8008EF58 0008BB38  7F E3 FB 78 */	mr r3, r31
/* 8008EF5C 0008BB3C  48 03 14 AD */	bl ftCo_800C0408
lbl_8008EF60:
/* 8008EF60 0008BB40  7F 83 E3 78 */	mr r3, r28
/* 8008EF64 0008BB44  4B FF 15 99 */	bl ftCommon_800804FC
/* 8008EF68 0008BB48  80 7B 18 3C */	lwz r3, 0x183c(r27)
/* 8008EF6C 0008BB4C  38 00 00 03 */	li r0, 3
/* 8008EF70 0008BB50  90 7D 18 3C */	stw r3, 0x183c(r29)
/* 8008EF74 0008BB54  C0 1B 19 60 */	lfs f0, 0x1960(r27)
/* 8008EF78 0008BB58  D0 1D 19 60 */	stfs f0, 0x1960(r29)
/* 8008EF7C 0008BB5C  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008EF80 0008BB60  48 00 07 9C */	b lbl_8008F71C
lbl_8008EF84:
/* 8008EF84 0008BB64  7F E3 FB 78 */	mr r3, r31
/* 8008EF88 0008BB68  48 04 F8 CD */	bl ftCo_800DE854
/* 8008EF8C 0008BB6C  38 7C 00 00 */	addi r3, r28, 0
/* 8008EF90 0008BB70  38 9F 00 00 */	addi r4, r31, 0
/* 8008EF94 0008BB74  48 04 DE A1 */	bl ftCo_800DCE34
/* 8008EF98 0008BB78  7F E3 FB 78 */	mr r3, r31
/* 8008EF9C 0008BB7C  4B FE EB BD */	bl ftCommon_8007DB58
/* 8008EFA0 0008BB80  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008EFA4 0008BB84  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008EFA8 0008BB88  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008EFAC 0008BB8C  41 82 00 10 */	beq lbl_8008EFBC
/* 8008EFB0 0008BB90  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008EFB4 0008BB94  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008EFB8 0008BB98  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008EFBC:
/* 8008EFBC 0008BB9C  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008EFC0 0008BBA0  28 03 00 06 */	cmplwi r3, 6
/* 8008EFC4 0008BBA4  41 82 00 0C */	beq lbl_8008EFD0
/* 8008EFC8 0008BBA8  28 03 00 07 */	cmplwi r3, 7
/* 8008EFCC 0008BBAC  40 82 00 30 */	bne lbl_8008EFFC
lbl_8008EFD0:
/* 8008EFD0 0008BBB0  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008EFD4 0008BBB4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008EFD8 0008BBB8  40 82 00 24 */	bne lbl_8008EFFC
/* 8008EFDC 0008BBBC  28 03 00 06 */	cmplwi r3, 6
/* 8008EFE0 0008BBC0  40 82 00 0C */	bne lbl_8008EFEC
/* 8008EFE4 0008BBC4  38 80 00 00 */	li r4, 0
/* 8008EFE8 0008BBC8  48 00 00 08 */	b lbl_8008EFF0
lbl_8008EFEC:
/* 8008EFEC 0008BBCC  38 80 00 01 */	li r4, 1
lbl_8008EFF0:
/* 8008EFF0 0008BBD0  7F E3 FB 78 */	mr r3, r31
/* 8008EFF4 0008BBD4  48 03 41 99 */	bl ftCo_800C318C
/* 8008EFF8 0008BBD8  48 00 00 14 */	b lbl_8008F00C
lbl_8008EFFC:
/* 8008EFFC 0008BBDC  FC 20 F8 90 */	fmr f1, f31
/* 8008F000 0008BBE0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F004 0008BBE4  38 80 FF FF */	li r4, -1
/* 8008F008 0008BBE8  4B FF EC D9 */	bl ftCo_8008DCE0
lbl_8008F00C:
/* 8008F00C 0008BBEC  38 00 00 01 */	li r0, 1
/* 8008F010 0008BBF0  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F014 0008BBF4  48 00 07 08 */	b lbl_8008F71C
lbl_8008F018:
/* 8008F018 0008BBF8  80 7D 18 3C */	lwz r3, 0x183c(r29)
/* 8008F01C 0008BBFC  2C 03 00 00 */	cmpwi r3, 0
/* 8008F020 0008BC00  41 82 00 58 */	beq lbl_8008F078
/* 8008F024 0008BC04  80 9B 00 10 */	lwz r4, 0x10(r27)
/* 8008F028 0008BC08  C0 3B 19 60 */	lfs f1, 0x1960(r27)
/* 8008F02C 0008BC0C  4B FE EA 49 */	bl ftCommon_CalcHitlag
/* 8008F030 0008BC10  D0 3B 19 5C */	stfs f1, 0x195c(r27)
/* 8008F034 0008BC14  38 60 00 01 */	li r3, 1
/* 8008F038 0008BC18  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 8008F03C 0008BC1C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 8008F040 0008BC20  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 8008F044 0008BC24  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 8008F048 0008BC28  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8008F04C 0008BC2C  40 82 00 2C */	bne lbl_8008F078
/* 8008F050 0008BC30  81 9B 21 D4 */	lwz r12, 0x21d4(r27)
/* 8008F054 0008BC34  28 0C 00 00 */	cmplwi r12, 0
/* 8008F058 0008BC38  41 82 00 10 */	beq lbl_8008F068
/* 8008F05C 0008BC3C  7D 88 03 A6 */	mtlr r12
/* 8008F060 0008BC40  38 7F 00 00 */	addi r3, r31, 0
/* 8008F064 0008BC44  4E 80 00 21 */	blrl
lbl_8008F068:
/* 8008F068 0008BC48  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 8008F06C 0008BC4C  38 60 00 01 */	li r3, 1
/* 8008F070 0008BC50  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8008F074 0008BC54  98 1B 22 19 */	stb r0, 0x2219(r27)
lbl_8008F078:
/* 8008F078 0008BC58  38 00 00 00 */	li r0, 0
/* 8008F07C 0008BC5C  90 1D 06 6C */	stw r0, 0x66c(r29)
/* 8008F080 0008BC60  7F E3 FB 78 */	mr r3, r31
/* 8008F084 0008BC64  90 1D 06 68 */	stw r0, 0x668(r29)
/* 8008F088 0008BC68  83 7F 00 2C */	lwz r27, 0x2c(r31)
/* 8008F08C 0008BC6C  48 03 9C 75 */	bl ftCo_800C8D00
/* 8008F090 0008BC70  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 8008F094 0008BC74  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008F098 0008BC78  41 82 00 0C */	beq lbl_8008F0A4
/* 8008F09C 0008BC7C  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008F0A0 0008BC80  40 82 00 0C */	bne lbl_8008F0AC
lbl_8008F0A4:
/* 8008F0A4 0008BC84  7F E3 FB 78 */	mr r3, r31
/* 8008F0A8 0008BC88  48 04 D1 DD */	bl ftCo_800DC284
lbl_8008F0AC:
/* 8008F0AC 0008BC8C  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 8008F0B0 0008BC90  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008F0B4 0008BC94  41 82 00 0C */	beq lbl_8008F0C0
/* 8008F0B8 0008BC98  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008F0BC 0008BC9C  40 82 00 0C */	bne lbl_8008F0C8
lbl_8008F0C0:
/* 8008F0C0 0008BCA0  7F E3 FB 78 */	mr r3, r31
/* 8008F0C4 0008BCA4  48 04 D2 E1 */	bl ftCo_800DC3A4
lbl_8008F0C8:
/* 8008F0C8 0008BCA8  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F0CC 0008BCAC  C0 5B 18 50 */	lfs f2, 0x1850(r27)
/* 8008F0D0 0008BCB0  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008F0D4 0008BCB4  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008F0D8 0008BCB8  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008F0DC 0008BCBC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F0E0 0008BCC0  40 80 00 0C */	bge lbl_8008F0EC
/* 8008F0E4 0008BCC4  38 A0 00 00 */	li r5, 0
/* 8008F0E8 0008BCC8  48 00 00 30 */	b lbl_8008F118
lbl_8008F0EC:
/* 8008F0EC 0008BCCC  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008F0F0 0008BCD0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F0F4 0008BCD4  40 80 00 0C */	bge lbl_8008F100
/* 8008F0F8 0008BCD8  38 A0 00 01 */	li r5, 1
/* 8008F0FC 0008BCDC  48 00 00 1C */	b lbl_8008F118
lbl_8008F100:
/* 8008F100 0008BCE0  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008F104 0008BCE4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F108 0008BCE8  40 80 00 0C */	bge lbl_8008F114
/* 8008F10C 0008BCEC  38 A0 00 02 */	li r5, 2
/* 8008F110 0008BCF0  48 00 00 08 */	b lbl_8008F118
lbl_8008F114:
/* 8008F114 0008BCF4  38 A0 00 03 */	li r5, 3
lbl_8008F118:
/* 8008F118 0008BCF8  80 9B 18 60 */	lwz r4, 0x1860(r27)
/* 8008F11C 0008BCFC  7F E3 FB 78 */	mr r3, r31
/* 8008F120 0008BD00  4B FF E9 2D */	bl ftCo_8008DA4C
/* 8008F124 0008BD04  2C 03 00 00 */	cmpwi r3, 0
/* 8008F128 0008BD08  41 82 00 0C */	beq lbl_8008F134
/* 8008F12C 0008BD0C  7F E3 FB 78 */	mr r3, r31
/* 8008F130 0008BD10  48 03 12 D9 */	bl ftCo_800C0408
lbl_8008F134:
/* 8008F134 0008BD14  7F 63 DB 78 */	mr r3, r27
/* 8008F138 0008BD18  4B FF 13 C5 */	bl ftCommon_800804FC
/* 8008F13C 0008BD1C  48 00 05 E0 */	b lbl_8008F71C
lbl_8008F140:
/* 8008F140 0008BD20  C0 3B 18 50 */	lfs f1, 0x1850(r27)
/* 8008F144 0008BD24  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F148 0008BD28  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F14C 0008BD2C  41 82 00 90 */	beq lbl_8008F1DC
/* 8008F150 0008BD30  38 7C 00 00 */	addi r3, r28, 0
/* 8008F154 0008BD34  38 9F 00 00 */	addi r4, r31, 0
/* 8008F158 0008BD38  48 04 DC DD */	bl ftCo_800DCE34
/* 8008F15C 0008BD3C  7F E3 FB 78 */	mr r3, r31
/* 8008F160 0008BD40  4B FE E9 F9 */	bl ftCommon_8007DB58
/* 8008F164 0008BD44  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F168 0008BD48  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F16C 0008BD4C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F170 0008BD50  41 82 00 10 */	beq lbl_8008F180
/* 8008F174 0008BD54  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F178 0008BD58  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F17C 0008BD5C  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F180:
/* 8008F180 0008BD60  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F184 0008BD64  28 03 00 06 */	cmplwi r3, 6
/* 8008F188 0008BD68  41 82 00 0C */	beq lbl_8008F194
/* 8008F18C 0008BD6C  28 03 00 07 */	cmplwi r3, 7
/* 8008F190 0008BD70  40 82 00 30 */	bne lbl_8008F1C0
lbl_8008F194:
/* 8008F194 0008BD74  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F198 0008BD78  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F19C 0008BD7C  40 82 00 24 */	bne lbl_8008F1C0
/* 8008F1A0 0008BD80  28 03 00 06 */	cmplwi r3, 6
/* 8008F1A4 0008BD84  40 82 00 0C */	bne lbl_8008F1B0
/* 8008F1A8 0008BD88  38 80 00 00 */	li r4, 0
/* 8008F1AC 0008BD8C  48 00 00 08 */	b lbl_8008F1B4
lbl_8008F1B0:
/* 8008F1B0 0008BD90  38 80 00 01 */	li r4, 1
lbl_8008F1B4:
/* 8008F1B4 0008BD94  7F E3 FB 78 */	mr r3, r31
/* 8008F1B8 0008BD98  48 03 3F D5 */	bl ftCo_800C318C
/* 8008F1BC 0008BD9C  48 00 00 14 */	b lbl_8008F1D0
lbl_8008F1C0:
/* 8008F1C0 0008BDA0  FC 20 F8 90 */	fmr f1, f31
/* 8008F1C4 0008BDA4  38 7F 00 00 */	addi r3, r31, 0
/* 8008F1C8 0008BDA8  38 80 FF FF */	li r4, -1
/* 8008F1CC 0008BDAC  4B FF EB 15 */	bl ftCo_8008DCE0
lbl_8008F1D0:
/* 8008F1D0 0008BDB0  38 00 00 01 */	li r0, 1
/* 8008F1D4 0008BDB4  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F1D8 0008BDB8  48 00 05 44 */	b lbl_8008F71C
lbl_8008F1DC:
/* 8008F1DC 0008BDBC  38 7C 00 00 */	addi r3, r28, 0
/* 8008F1E0 0008BDC0  38 9F 00 00 */	addi r4, r31, 0
/* 8008F1E4 0008BDC4  48 04 DC 51 */	bl ftCo_800DCE34
/* 8008F1E8 0008BDC8  7F E3 FB 78 */	mr r3, r31
/* 8008F1EC 0008BDCC  4B FE E9 6D */	bl ftCommon_8007DB58
/* 8008F1F0 0008BDD0  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F1F4 0008BDD4  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F1F8 0008BDD8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F1FC 0008BDDC  41 82 00 10 */	beq lbl_8008F20C
/* 8008F200 0008BDE0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F204 0008BDE4  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F208 0008BDE8  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F20C:
/* 8008F20C 0008BDEC  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F210 0008BDF0  28 03 00 06 */	cmplwi r3, 6
/* 8008F214 0008BDF4  41 82 00 0C */	beq lbl_8008F220
/* 8008F218 0008BDF8  28 03 00 07 */	cmplwi r3, 7
/* 8008F21C 0008BDFC  40 82 00 30 */	bne lbl_8008F24C
lbl_8008F220:
/* 8008F220 0008BE00  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F224 0008BE04  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F228 0008BE08  40 82 00 24 */	bne lbl_8008F24C
/* 8008F22C 0008BE0C  28 03 00 06 */	cmplwi r3, 6
/* 8008F230 0008BE10  40 82 00 0C */	bne lbl_8008F23C
/* 8008F234 0008BE14  38 80 00 00 */	li r4, 0
/* 8008F238 0008BE18  48 00 00 08 */	b lbl_8008F240
lbl_8008F23C:
/* 8008F23C 0008BE1C  38 80 00 01 */	li r4, 1
lbl_8008F240:
/* 8008F240 0008BE20  7F E3 FB 78 */	mr r3, r31
/* 8008F244 0008BE24  48 03 3F 49 */	bl ftCo_800C318C
/* 8008F248 0008BE28  48 00 00 14 */	b lbl_8008F25C
lbl_8008F24C:
/* 8008F24C 0008BE2C  FC 20 F8 90 */	fmr f1, f31
/* 8008F250 0008BE30  38 7F 00 00 */	addi r3, r31, 0
/* 8008F254 0008BE34  38 80 FF FF */	li r4, -1
/* 8008F258 0008BE38  4B FF EA 89 */	bl ftCo_8008DCE0
lbl_8008F25C:
/* 8008F25C 0008BE3C  7F 83 E3 78 */	mr r3, r28
/* 8008F260 0008BE40  4B FE E8 F9 */	bl ftCommon_8007DB58
/* 8008F264 0008BE44  7F 83 E3 78 */	mr r3, r28
/* 8008F268 0008BE48  48 04 F0 89 */	bl ftCo_800DE2F0
/* 8008F26C 0008BE4C  48 00 04 B0 */	b lbl_8008F71C
lbl_8008F270:
/* 8008F270 0008BE50  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F274 0008BE54  C0 5D 18 50 */	lfs f2, 0x1850(r29)
/* 8008F278 0008BE58  83 64 00 2C */	lwz r27, 0x2c(r4)
/* 8008F27C 0008BE5C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008F280 0008BE60  40 82 00 0C */	bne lbl_8008F28C
/* 8008F284 0008BE64  38 00 00 01 */	li r0, 1
/* 8008F288 0008BE68  48 00 00 3C */	b lbl_8008F2C4
lbl_8008F28C:
/* 8008F28C 0008BE6C  88 7D 22 1A */	lbz r3, 0x221a(r29)
/* 8008F290 0008BE70  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008F294 0008BE74  41 82 00 2C */	beq lbl_8008F2C0
/* 8008F298 0008BE78  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008F29C 0008BE7C  41 82 00 24 */	beq lbl_8008F2C0
/* 8008F2A0 0008BE80  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F2A4 0008BE84  C0 3D 18 A8 */	lfs f1, 0x18a8(r29)
/* 8008F2A8 0008BE88  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008F2AC 0008BE8C  EC 01 00 2A */	fadds f0, f1, f0
/* 8008F2B0 0008BE90  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F2B4 0008BE94  40 80 00 0C */	bge lbl_8008F2C0
/* 8008F2B8 0008BE98  38 00 00 01 */	li r0, 1
/* 8008F2BC 0008BE9C  48 00 00 08 */	b lbl_8008F2C4
lbl_8008F2C0:
/* 8008F2C0 0008BEA0  38 00 00 00 */	li r0, 0
lbl_8008F2C4:
/* 8008F2C4 0008BEA4  2C 00 00 00 */	cmpwi r0, 0
/* 8008F2C8 0008BEA8  41 82 01 C8 */	beq lbl_8008F490
/* 8008F2CC 0008BEAC  C0 3B 18 50 */	lfs f1, 0x1850(r27)
/* 8008F2D0 0008BEB0  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F2D4 0008BEB4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F2D8 0008BEB8  41 82 01 5C */	beq lbl_8008F434
/* 8008F2DC 0008BEBC  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 8008F2E0 0008BEC0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008F2E4 0008BEC4  41 82 00 0C */	beq lbl_8008F2F0
/* 8008F2E8 0008BEC8  38 00 00 01 */	li r0, 1
/* 8008F2EC 0008BECC  48 00 00 40 */	b lbl_8008F32C
lbl_8008F2F0:
/* 8008F2F0 0008BED0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F2F4 0008BED4  3C 00 43 30 */	lis r0, 0x4330
/* 8008F2F8 0008BED8  C8 22 8B 00 */	lfd f1, lbl_804D84E0
/* 8008F2FC 0008BEDC  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8008F300 0008BEE0  C0 5B 18 38 */	lfs f2, 0x1838(r27)
/* 8008F304 0008BEE4  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008F308 0008BEE8  90 61 00 8C */	stw r3, 0x8c(r1)
/* 8008F30C 0008BEEC  90 01 00 88 */	stw r0, 0x88(r1)
/* 8008F310 0008BEF0  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 8008F314 0008BEF4  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008F318 0008BEF8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F31C 0008BEFC  40 80 00 0C */	bge lbl_8008F328
/* 8008F320 0008BF00  38 00 00 01 */	li r0, 1
/* 8008F324 0008BF04  48 00 00 08 */	b lbl_8008F32C
lbl_8008F328:
/* 8008F328 0008BF08  38 00 00 00 */	li r0, 0
lbl_8008F32C:
/* 8008F32C 0008BF0C  2C 00 00 00 */	cmpwi r0, 0
/* 8008F330 0008BF10  41 82 00 7C */	beq lbl_8008F3AC
/* 8008F334 0008BF14  80 1D 18 3C */	lwz r0, 0x183c(r29)
/* 8008F338 0008BF18  90 1B 18 3C */	stw r0, 0x183c(r27)
/* 8008F33C 0008BF1C  C0 1D 19 60 */	lfs f0, 0x1960(r29)
/* 8008F340 0008BF20  D0 1B 19 60 */	stfs f0, 0x1960(r27)
/* 8008F344 0008BF24  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F348 0008BF28  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F34C 0008BF2C  C0 44 18 50 */	lfs f2, 0x1850(r4)
/* 8008F350 0008BF30  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008F354 0008BF34  41 82 00 30 */	beq lbl_8008F384
/* 8008F358 0008BF38  88 64 22 1A */	lbz r3, 0x221a(r4)
/* 8008F35C 0008BF3C  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008F360 0008BF40  41 82 00 2C */	beq lbl_8008F38C
/* 8008F364 0008BF44  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008F368 0008BF48  41 82 00 24 */	beq lbl_8008F38C
/* 8008F36C 0008BF4C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F370 0008BF50  C0 24 18 A8 */	lfs f1, 0x18a8(r4)
/* 8008F374 0008BF54  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008F378 0008BF58  EC 01 00 2A */	fadds f0, f1, f0
/* 8008F37C 0008BF5C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F380 0008BF60  40 80 00 0C */	bge lbl_8008F38C
lbl_8008F384:
/* 8008F384 0008BF64  38 00 00 01 */	li r0, 1
/* 8008F388 0008BF68  48 00 00 08 */	b lbl_8008F390
lbl_8008F38C:
/* 8008F38C 0008BF6C  38 00 00 00 */	li r0, 0
lbl_8008F390:
/* 8008F390 0008BF70  2C 00 00 00 */	cmpwi r0, 0
/* 8008F394 0008BF74  41 82 00 0C */	beq lbl_8008F3A0
/* 8008F398 0008BF78  7F E3 FB 78 */	mr r3, r31
/* 8008F39C 0008BF7C  4B FF F6 35 */	bl ftCo_8008E9D0
lbl_8008F3A0:
/* 8008F3A0 0008BF80  38 00 00 02 */	li r0, 2
/* 8008F3A4 0008BF84  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F3A8 0008BF88  48 00 03 74 */	b lbl_8008F71C
lbl_8008F3AC:
/* 8008F3AC 0008BF8C  7F E3 FB 78 */	mr r3, r31
/* 8008F3B0 0008BF90  48 04 DA 85 */	bl ftCo_800DCE34
/* 8008F3B4 0008BF94  7F E3 FB 78 */	mr r3, r31
/* 8008F3B8 0008BF98  4B FE E7 A1 */	bl ftCommon_8007DB58
/* 8008F3BC 0008BF9C  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F3C0 0008BFA0  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F3C4 0008BFA4  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F3C8 0008BFA8  41 82 00 10 */	beq lbl_8008F3D8
/* 8008F3CC 0008BFAC  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F3D0 0008BFB0  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F3D4 0008BFB4  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F3D8:
/* 8008F3D8 0008BFB8  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F3DC 0008BFBC  28 03 00 06 */	cmplwi r3, 6
/* 8008F3E0 0008BFC0  41 82 00 0C */	beq lbl_8008F3EC
/* 8008F3E4 0008BFC4  28 03 00 07 */	cmplwi r3, 7
/* 8008F3E8 0008BFC8  40 82 00 30 */	bne lbl_8008F418
lbl_8008F3EC:
/* 8008F3EC 0008BFCC  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F3F0 0008BFD0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F3F4 0008BFD4  40 82 00 24 */	bne lbl_8008F418
/* 8008F3F8 0008BFD8  28 03 00 06 */	cmplwi r3, 6
/* 8008F3FC 0008BFDC  40 82 00 0C */	bne lbl_8008F408
/* 8008F400 0008BFE0  38 80 00 00 */	li r4, 0
/* 8008F404 0008BFE4  48 00 00 08 */	b lbl_8008F40C
lbl_8008F408:
/* 8008F408 0008BFE8  38 80 00 01 */	li r4, 1
lbl_8008F40C:
/* 8008F40C 0008BFEC  7F E3 FB 78 */	mr r3, r31
/* 8008F410 0008BFF0  48 03 3D 7D */	bl ftCo_800C318C
/* 8008F414 0008BFF4  48 00 00 14 */	b lbl_8008F428
lbl_8008F418:
/* 8008F418 0008BFF8  FC 20 F8 90 */	fmr f1, f31
/* 8008F41C 0008BFFC  38 7F 00 00 */	addi r3, r31, 0
/* 8008F420 0008C000  38 80 FF FF */	li r4, -1
/* 8008F424 0008C004  4B FF E8 BD */	bl ftCo_8008DCE0
lbl_8008F428:
/* 8008F428 0008C008  38 00 00 01 */	li r0, 1
/* 8008F42C 0008C00C  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F430 0008C010  48 00 02 EC */	b lbl_8008F71C
lbl_8008F434:
/* 8008F434 0008C014  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F438 0008C018  C0 44 18 50 */	lfs f2, 0x1850(r4)
/* 8008F43C 0008C01C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008F440 0008C020  41 82 00 30 */	beq lbl_8008F470
/* 8008F444 0008C024  88 64 22 1A */	lbz r3, 0x221a(r4)
/* 8008F448 0008C028  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008F44C 0008C02C  41 82 00 2C */	beq lbl_8008F478
/* 8008F450 0008C030  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008F454 0008C034  41 82 00 24 */	beq lbl_8008F478
/* 8008F458 0008C038  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F45C 0008C03C  C0 24 18 A8 */	lfs f1, 0x18a8(r4)
/* 8008F460 0008C040  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008F464 0008C044  EC 01 00 2A */	fadds f0, f1, f0
/* 8008F468 0008C048  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F46C 0008C04C  40 80 00 0C */	bge lbl_8008F478
lbl_8008F470:
/* 8008F470 0008C050  38 00 00 01 */	li r0, 1
/* 8008F474 0008C054  48 00 00 08 */	b lbl_8008F47C
lbl_8008F478:
/* 8008F478 0008C058  38 00 00 00 */	li r0, 0
lbl_8008F47C:
/* 8008F47C 0008C05C  2C 00 00 00 */	cmpwi r0, 0
/* 8008F480 0008C060  41 82 02 9C */	beq lbl_8008F71C
/* 8008F484 0008C064  7F E3 FB 78 */	mr r3, r31
/* 8008F488 0008C068  4B FF F5 49 */	bl ftCo_8008E9D0
/* 8008F48C 0008C06C  48 00 02 90 */	b lbl_8008F71C
lbl_8008F490:
/* 8008F490 0008C070  C0 3B 18 50 */	lfs f1, 0x1850(r27)
/* 8008F494 0008C074  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F498 0008C078  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F49C 0008C07C  41 82 00 F0 */	beq lbl_8008F58C
/* 8008F4A0 0008C080  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 8008F4A4 0008C084  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008F4A8 0008C088  41 82 00 0C */	beq lbl_8008F4B4
/* 8008F4AC 0008C08C  38 00 00 01 */	li r0, 1
/* 8008F4B0 0008C090  48 00 00 40 */	b lbl_8008F4F0
lbl_8008F4B4:
/* 8008F4B4 0008C094  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F4B8 0008C098  3C 00 43 30 */	lis r0, 0x4330
/* 8008F4BC 0008C09C  C8 22 8B 00 */	lfd f1, lbl_804D84E0
/* 8008F4C0 0008C0A0  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8008F4C4 0008C0A4  C0 5B 18 38 */	lfs f2, 0x1838(r27)
/* 8008F4C8 0008C0A8  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008F4CC 0008C0AC  90 61 00 8C */	stw r3, 0x8c(r1)
/* 8008F4D0 0008C0B0  90 01 00 88 */	stw r0, 0x88(r1)
/* 8008F4D4 0008C0B4  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 8008F4D8 0008C0B8  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008F4DC 0008C0BC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F4E0 0008C0C0  40 80 00 0C */	bge lbl_8008F4EC
/* 8008F4E4 0008C0C4  38 00 00 01 */	li r0, 1
/* 8008F4E8 0008C0C8  48 00 00 08 */	b lbl_8008F4F0
lbl_8008F4EC:
/* 8008F4EC 0008C0CC  38 00 00 00 */	li r0, 0
lbl_8008F4F0:
/* 8008F4F0 0008C0D0  2C 00 00 00 */	cmpwi r0, 0
/* 8008F4F4 0008C0D4  41 82 00 0C */	beq lbl_8008F500
/* 8008F4F8 0008C0D8  7C 83 23 78 */	mr r3, r4
/* 8008F4FC 0008C0DC  48 04 F3 59 */	bl ftCo_800DE854
lbl_8008F500:
/* 8008F500 0008C0E0  7F E3 FB 78 */	mr r3, r31
/* 8008F504 0008C0E4  80 9D 1A 58 */	lwz r4, 0x1a58(r29)
/* 8008F508 0008C0E8  48 04 D9 2D */	bl ftCo_800DCE34
/* 8008F50C 0008C0EC  7F E3 FB 78 */	mr r3, r31
/* 8008F510 0008C0F0  4B FE E6 49 */	bl ftCommon_8007DB58
/* 8008F514 0008C0F4  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F518 0008C0F8  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F51C 0008C0FC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F520 0008C100  41 82 00 10 */	beq lbl_8008F530
/* 8008F524 0008C104  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F528 0008C108  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F52C 0008C10C  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F530:
/* 8008F530 0008C110  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F534 0008C114  28 03 00 06 */	cmplwi r3, 6
/* 8008F538 0008C118  41 82 00 0C */	beq lbl_8008F544
/* 8008F53C 0008C11C  28 03 00 07 */	cmplwi r3, 7
/* 8008F540 0008C120  40 82 00 30 */	bne lbl_8008F570
lbl_8008F544:
/* 8008F544 0008C124  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F548 0008C128  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F54C 0008C12C  40 82 00 24 */	bne lbl_8008F570
/* 8008F550 0008C130  28 03 00 06 */	cmplwi r3, 6
/* 8008F554 0008C134  40 82 00 0C */	bne lbl_8008F560
/* 8008F558 0008C138  38 80 00 00 */	li r4, 0
/* 8008F55C 0008C13C  48 00 00 08 */	b lbl_8008F564
lbl_8008F560:
/* 8008F560 0008C140  38 80 00 01 */	li r4, 1
lbl_8008F564:
/* 8008F564 0008C144  7F E3 FB 78 */	mr r3, r31
/* 8008F568 0008C148  48 03 3C 25 */	bl ftCo_800C318C
/* 8008F56C 0008C14C  48 00 00 14 */	b lbl_8008F580
lbl_8008F570:
/* 8008F570 0008C150  FC 20 F8 90 */	fmr f1, f31
/* 8008F574 0008C154  38 7F 00 00 */	addi r3, r31, 0
/* 8008F578 0008C158  38 80 FF FF */	li r4, -1
/* 8008F57C 0008C15C  4B FF E7 65 */	bl ftCo_8008DCE0
lbl_8008F580:
/* 8008F580 0008C160  38 00 00 01 */	li r0, 1
/* 8008F584 0008C164  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F588 0008C168  48 00 01 94 */	b lbl_8008F71C
lbl_8008F58C:
/* 8008F58C 0008C16C  7C 83 23 78 */	mr r3, r4
/* 8008F590 0008C170  4B FE E5 C9 */	bl ftCommon_8007DB58
/* 8008F594 0008C174  80 7D 1A 58 */	lwz r3, 0x1a58(r29)
/* 8008F598 0008C178  48 04 DA 3D */	bl ftCo_800DCFD4
/* 8008F59C 0008C17C  7F E3 FB 78 */	mr r3, r31
/* 8008F5A0 0008C180  80 9D 1A 58 */	lwz r4, 0x1a58(r29)
/* 8008F5A4 0008C184  48 04 D8 91 */	bl ftCo_800DCE34
/* 8008F5A8 0008C188  7F E3 FB 78 */	mr r3, r31
/* 8008F5AC 0008C18C  4B FE E5 AD */	bl ftCommon_8007DB58
/* 8008F5B0 0008C190  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F5B4 0008C194  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F5B8 0008C198  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F5BC 0008C19C  41 82 00 10 */	beq lbl_8008F5CC
/* 8008F5C0 0008C1A0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F5C4 0008C1A4  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F5C8 0008C1A8  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F5CC:
/* 8008F5CC 0008C1AC  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F5D0 0008C1B0  28 03 00 06 */	cmplwi r3, 6
/* 8008F5D4 0008C1B4  41 82 00 0C */	beq lbl_8008F5E0
/* 8008F5D8 0008C1B8  28 03 00 07 */	cmplwi r3, 7
/* 8008F5DC 0008C1BC  40 82 00 30 */	bne lbl_8008F60C
lbl_8008F5E0:
/* 8008F5E0 0008C1C0  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F5E4 0008C1C4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F5E8 0008C1C8  40 82 00 24 */	bne lbl_8008F60C
/* 8008F5EC 0008C1CC  28 03 00 06 */	cmplwi r3, 6
/* 8008F5F0 0008C1D0  40 82 00 0C */	bne lbl_8008F5FC
/* 8008F5F4 0008C1D4  38 80 00 00 */	li r4, 0
/* 8008F5F8 0008C1D8  48 00 00 08 */	b lbl_8008F600
lbl_8008F5FC:
/* 8008F5FC 0008C1DC  38 80 00 01 */	li r4, 1
lbl_8008F600:
/* 8008F600 0008C1E0  7F E3 FB 78 */	mr r3, r31
/* 8008F604 0008C1E4  48 03 3B 89 */	bl ftCo_800C318C
/* 8008F608 0008C1E8  48 00 01 14 */	b lbl_8008F71C
lbl_8008F60C:
/* 8008F60C 0008C1EC  FC 20 F8 90 */	fmr f1, f31
/* 8008F610 0008C1F0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F614 0008C1F4  38 80 FF FF */	li r4, -1
/* 8008F618 0008C1F8  4B FF E6 C9 */	bl ftCo_8008DCE0
/* 8008F61C 0008C1FC  48 00 01 00 */	b lbl_8008F71C
lbl_8008F620:
/* 8008F620 0008C200  80 7D 19 74 */	lwz r3, 0x1974(r29)
/* 8008F624 0008C204  28 03 00 00 */	cmplwi r3, 0
/* 8008F628 0008C208  41 82 00 28 */	beq lbl_8008F650
/* 8008F62C 0008C20C  48 1D BC AD */	bl it_8026B2D8
/* 8008F630 0008C210  2C 03 00 00 */	cmpwi r3, 0
/* 8008F634 0008C214  41 82 00 1C */	beq lbl_8008F650
/* 8008F638 0008C218  88 1D 22 22 */	lbz r0, 0x2222(r29)
/* 8008F63C 0008C21C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008F640 0008C220  41 82 00 10 */	beq lbl_8008F650
/* 8008F644 0008C224  7F E3 FB 78 */	mr r3, r31
/* 8008F648 0008C228  48 05 10 91 */	bl ftDk_MS_349_800E06D8
/* 8008F64C 0008C22C  48 00 00 D0 */	b lbl_8008F71C
lbl_8008F650:
/* 8008F650 0008C230  7F E3 FB 78 */	mr r3, r31
/* 8008F654 0008C234  48 00 FA 9D */	bl ftCo_8009F0F0
/* 8008F658 0008C238  2C 03 00 00 */	cmpwi r3, 0
/* 8008F65C 0008C23C  40 82 00 C0 */	bne lbl_8008F71C
/* 8008F660 0008C240  7F E3 FB 78 */	mr r3, r31
/* 8008F664 0008C244  48 03 16 55 */	bl ftCo_800C0CB8
/* 8008F668 0008C248  2C 03 00 00 */	cmpwi r3, 0
/* 8008F66C 0008C24C  40 82 00 B0 */	bne lbl_8008F71C
/* 8008F670 0008C250  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008F674 0008C254  2C 00 01 45 */	cmpwi r0, 0x145
/* 8008F678 0008C258  40 82 00 20 */	bne lbl_8008F698
/* 8008F67C 0008C25C  C0 3D 00 2C */	lfs f1, 0x2c(r29)
/* 8008F680 0008C260  38 7F 00 00 */	addi r3, r31, 0
/* 8008F684 0008C264  38 80 01 45 */	li r4, 0x145
/* 8008F688 0008C268  4B FF E6 59 */	bl ftCo_8008DCE0
/* 8008F68C 0008C26C  7F E3 FB 78 */	mr r3, r31
/* 8008F690 0008C270  48 00 19 A1 */	bl ftCo_80091030
/* 8008F694 0008C274  48 00 00 88 */	b lbl_8008F71C
lbl_8008F698:
/* 8008F698 0008C278  7F E3 FB 78 */	mr r3, r31
/* 8008F69C 0008C27C  48 03 7E 59 */	bl ftCo_800C74F4
/* 8008F6A0 0008C280  2C 03 00 00 */	cmpwi r3, 0
/* 8008F6A4 0008C284  40 82 00 78 */	bne lbl_8008F71C
/* 8008F6A8 0008C288  7F E3 FB 78 */	mr r3, r31
/* 8008F6AC 0008C28C  4B FE E4 AD */	bl ftCommon_8007DB58
/* 8008F6B0 0008C290  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F6B4 0008C294  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F6B8 0008C298  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F6BC 0008C29C  41 82 00 10 */	beq lbl_8008F6CC
/* 8008F6C0 0008C2A0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F6C4 0008C2A4  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F6C8 0008C2A8  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F6CC:
/* 8008F6CC 0008C2AC  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F6D0 0008C2B0  28 03 00 06 */	cmplwi r3, 6
/* 8008F6D4 0008C2B4  41 82 00 0C */	beq lbl_8008F6E0
/* 8008F6D8 0008C2B8  28 03 00 07 */	cmplwi r3, 7
/* 8008F6DC 0008C2BC  40 82 00 30 */	bne lbl_8008F70C
lbl_8008F6E0:
/* 8008F6E0 0008C2C0  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F6E4 0008C2C4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F6E8 0008C2C8  40 82 00 24 */	bne lbl_8008F70C
/* 8008F6EC 0008C2CC  28 03 00 06 */	cmplwi r3, 6
/* 8008F6F0 0008C2D0  40 82 00 0C */	bne lbl_8008F6FC
/* 8008F6F4 0008C2D4  38 80 00 00 */	li r4, 0
/* 8008F6F8 0008C2D8  48 00 00 08 */	b lbl_8008F700
lbl_8008F6FC:
/* 8008F6FC 0008C2DC  38 80 00 01 */	li r4, 1
lbl_8008F700:
/* 8008F700 0008C2E0  7F E3 FB 78 */	mr r3, r31
/* 8008F704 0008C2E4  48 03 3A 89 */	bl ftCo_800C318C
/* 8008F708 0008C2E8  48 00 00 14 */	b lbl_8008F71C
lbl_8008F70C:
/* 8008F70C 0008C2EC  FC 20 F8 90 */	fmr f1, f31
/* 8008F710 0008C2F0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F714 0008C2F4  38 80 FF FF */	li r4, -1
/* 8008F718 0008C2F8  4B FF E5 C9 */	bl ftCo_8008DCE0
lbl_8008F71C:
/* 8008F71C 0008C2FC  2C 1E 00 00 */	cmpwi r30, 0
/* 8008F720 0008C300  41 82 00 0C */	beq lbl_8008F72C
/* 8008F724 0008C304  7F E3 FB 78 */	mr r3, r31
/* 8008F728 0008C308  48 03 3E 71 */	bl ftCo_800C3598
lbl_8008F72C:
/* 8008F72C 0008C30C  BB 61 00 94 */	lmw r27, 0x94(r1)
/* 8008F730 0008C310  80 01 00 B4 */	lwz r0, 0xb4(r1)
/* 8008F734 0008C314  CB E1 00 A8 */	lfd f31, 0xa8(r1)
/* 8008F738 0008C318  38 21 00 B0 */	addi r1, r1, 0xb0
/* 8008F73C 0008C31C  7C 08 03 A6 */	mtlr r0
/* 8008F740 0008C320  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static bool inlineB1(ftCo_Fighter* fp)
{
    if (fp->x221C_b0) {
        return true;
    }
    if (fp->dmg.x1838_percentTemp < p_ftCommonData->x3C0) {
        return true;
    }
    return false;
}

static inline void inlineB2(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
#ifdef MUST_MATCH
#pragma always_inline on
#endif
    inlineF0(gobj);
#ifdef MUST_MATCH
#pragma always_inline restore
#endif
    if (ftCo_8008DA4C(
            gobj, fp->dmg.x1860,
            ftCo_8008D8E8(fp->dmg.kb_applied * p_ftCommonData->x154)))
    {
        ftCo_800C0408(gobj);
    }
    ftCommon_800804FC(fp);
}

void ftCo_8008EC90(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    // u8 _[0x60] = { 0 };
#endif
    bool ret0 = false;
    ftCo_Fighter* fp = gobj->user_data;
    float facing_dir = 0;
    if (fp->x2220_flag.bits.b3 || fp->x2220_flag.bits.b4 ||
        !fp->dmg.kb_applied)
    {
        inlineB2(gobj);
        goto ret_A8C;
    } else if (fp->dmg.x1860 == 10U) {
        if (ftCo_800C3538(gobj)) {
            goto ret_A8C;
        }
        facing_dir = fp->facing_dir;
        ret0 = true;
    }
    if (!ftCo_800C44CC(gobj) && !ftCo_800D2FA4(gobj) &&
        fp->victim_gobj != NULL)
    {
        ftCo_GObj* other_gobj = fp->victim_gobj;
        ftCo_Fighter* other_fp = other_gobj->user_data;
        if (!fp->x221B_b5) {
            if (!ret0 && inlineB1(fp)) {
                if (other_fp->dmg.kb_applied) {
                    if (ftCo_8008E984(other_fp)) {
                        inlineB2(gobj);
                        fp->dmg.x183C_applied = other_fp->dmg.x183C_applied;
                        fp->x1960_vibrateMult = other_fp->x1960_vibrateMult;
                        other_fp->x1828 = 3;
                        goto ret_A8C;
                    }
                    ftCo_800DE854(gobj);
                    ftCo_800DCE34(other_gobj, gobj);
                    ftCommon_8007DB58(gobj);
                    ftCo_8008E908(gobj, facing_dir);
                    other_fp->x1828 = 1;
                    goto ret_A8C;
                }
                if (fp->dmg.x183C_applied != 0) {
                    other_fp->dmg.x195c_hitlag_frames = ftCommon_CalcHitlag(
                        fp->dmg.x183C_applied, other_fp->motion_id,
                        other_fp->x1960_vibrateMult);
                    other_fp->x221A_b2 = true;
                    if (!other_fp->x2219_b5) {
                        if (other_fp->pre_hitlag_cb != NULL) {
                            other_fp->pre_hitlag_cb(gobj);
                        }
                        other_fp->x2219_b5 = true;
                    }
                }
                other_fp->input.x668 = other_fp->input.x66C = 0;
                inlineB2(gobj);
                goto ret_A8C;
            }
            {
                if (other_fp->dmg.kb_applied) {
                    ftCo_800DCE34(other_gobj, gobj);
                    ftCommon_8007DB58(gobj);
                    ftCo_8008E908(gobj, facing_dir);
                    other_fp->x1828 = 1;
                    goto ret_A8C;
                }
                ftCo_800DCE34(other_gobj, gobj);
                ftCommon_8007DB58(gobj);
                ftCo_8008E908(gobj, facing_dir);
                ftCommon_8007DB58(other_gobj);
                ftCo_800DE2F0(other_gobj);
                goto ret_A8C;
            }
        }
        if (inlineB0(gobj)) {
            if (other_fp->dmg.kb_applied) {
                if (inlineB1(other_fp)) {
                    other_fp->dmg.x183C_applied = fp->dmg.x183C_applied;
                    other_fp->x1960_vibrateMult = fp->x1960_vibrateMult;
                    if (inlineB0(gobj)) {
                        ftCo_8008E9D0(gobj);
                    }
                    fp->x1828 = 2;
                    goto ret_A8C;
                }
                ftCo_800DCE34(gobj, other_gobj);
                ftCommon_8007DB58(gobj);
                ftCo_8008E908(gobj, facing_dir);
                fp->x1828 = 1;
                goto ret_A8C;
            }
            if (inlineB0(gobj)) {
                ftCo_8008E9D0(gobj);
            }
            goto ret_A8C;
        }
        if (other_fp->dmg.kb_applied) {
            if (inlineB1(other_fp)) {
                ftCo_800DE854(other_gobj);
            }
            ftCo_800DCE34(gobj, fp->victim_gobj);
            ftCommon_8007DB58(gobj);
            ftCo_8008E908(gobj, facing_dir);
            other_fp->x1828 = 1;
            goto ret_A8C;
        }
        ftCommon_8007DB58(other_gobj);
        ftCo_800DCFD4(fp->victim_gobj);
        ftCo_800DCE34(gobj, fp->victim_gobj);
        ftCommon_8007DB58(gobj);
        ftCo_8008E908(gobj, facing_dir);
    } else if (fp->item_gobj != NULL && it_8026B2D8(fp->item_gobj) &&
               fp->x2222_b0)
    {
        ftDk_MS_349_800E06D8(gobj);
    } else if (!ftCo_8009F0F0(gobj) && !ftCo_800C0CB8(gobj) &&
               fp->motion_id == ftCo_MS_DamageIce)
    {
        ftCo_8008DCE0(gobj, ftCo_MS_DamageIce, fp->facing_dir);
        ftCo_80091030(gobj);
    } else if (!ftCo_800C74F4(gobj)) {
        ftCommon_8007DB58(gobj);
        ftCo_8008E908(gobj, facing_dir);
    }
ret_A8C:
    if (ret0) {
        ftCo_800C3598(gobj);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08F744 */ void ftCo_8008F744(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8008F744 0008C324  7C 08 02 A6 */	mflr r0
/* 8008F748 0008C328  90 01 00 04 */	stw r0, 4(r1)
/* 8008F74C 0008C32C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008F750 0008C330  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008F754 0008C334  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008F758 0008C338  7C 7E 1B 78 */	mr r30, r3
/* 8008F75C 0008C33C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008F760 0008C340  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F764 0008C344  C0 23 23 40 */	lfs f1, 0x2340(r3)
/* 8008F768 0008C348  7C 7F 1B 78 */	mr r31, r3
/* 8008F76C 0008C34C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F770 0008C350  40 81 00 10 */	ble lbl_8008F780
/* 8008F774 0008C354  C0 02 8A F8 */	lfs f0, lbl_804D84D8
/* 8008F778 0008C358  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008F77C 0008C35C  D0 1F 23 40 */	stfs f0, 0x2340(r31)
lbl_8008F780:
/* 8008F780 0008C360  88 7F 22 1C */	lbz r3, 0x221c(r31)
/* 8008F784 0008C364  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8008F788 0008C368  41 82 00 50 */	beq lbl_8008F7D8
/* 8008F78C 0008C36C  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 8008F790 0008C370  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F794 0008C374  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F798 0008C378  4C 40 13 82 */	cror 2, 0, 2
/* 8008F79C 0008C37C  40 82 00 3C */	bne lbl_8008F7D8
/* 8008F7A0 0008C380  38 00 00 00 */	li r0, 0
/* 8008F7A4 0008C384  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 8008F7A8 0008C388  98 7F 22 1C */	stb r3, 0x221c(r31)
/* 8008F7AC 0008C38C  7F C3 F3 78 */	mr r3, r30
/* 8008F7B0 0008C390  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008F7B4 0008C394  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 8008F7B8 0008C398  B0 1F 20 98 */	sth r0, 0x2098(r31)
/* 8008F7BC 0008C39C  4B FF 00 B1 */	bl ftCommon_8007F86C
/* 8008F7C0 0008C3A0  7F C3 F3 78 */	mr r3, r30
/* 8008F7C4 0008C3A4  48 03 5A 7D */	bl ftCo_800C5240
/* 8008F7C8 0008C3A8  2C 03 00 00 */	cmpwi r3, 0
/* 8008F7CC 0008C3AC  41 82 00 0C */	beq lbl_8008F7D8
/* 8008F7D0 0008C3B0  7F E3 FB 78 */	mr r3, r31
/* 8008F7D4 0008C3B4  48 03 5D 79 */	bl ftCo_800C554C
lbl_8008F7D8:
/* 8008F7D8 0008C3B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008F7DC 0008C3BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008F7E0 0008C3C0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008F7E4 0008C3C4  38 21 00 18 */	addi r1, r1, 0x18
/* 8008F7E8 0008C3C8  7C 08 03 A6 */	mtlr r0
/* 8008F7EC 0008C3CC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_8008F744(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.damage.x0 > 0) {
        fp->mv.co.damage.x0 -= 1;
    }
    if (fp->x221C_b6) {
        if (fp->mv.co.damage.x0 <= 0) {
            fp->x221C_b6 = false;
            fp->x2098 = p_ftCommonData->x4CC;
            ftCommon_8007F86C(gobj);
            if (ftCo_800C5240(gobj)) {
                ftCo_800C554C((Fighter*) fp);
            }
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_Damage_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 8008F7F0 0008C3D0  7C 08 02 A6 */	mflr r0
/* 8008F7F4 0008C3D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008F7F8 0008C3D8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008F7FC 0008C3DC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008F800 0008C3E0  7C 7F 1B 78 */	mr r31, r3
/* 8008F804 0008C3E4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008F808 0008C3E8  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008F80C 0008C3EC  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F810 0008C3F0  C0 3E 23 40 */	lfs f1, 0x2340(r30)
/* 8008F814 0008C3F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F818 0008C3F8  40 81 00 10 */	ble lbl_8008F828
/* 8008F81C 0008C3FC  C0 02 8A F8 */	lfs f0, lbl_804D84D8
/* 8008F820 0008C400  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008F824 0008C404  D0 1E 23 40 */	stfs f0, 0x2340(r30)
lbl_8008F828:
/* 8008F828 0008C408  88 7E 22 1C */	lbz r3, 0x221c(r30)
/* 8008F82C 0008C40C  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8008F830 0008C410  41 82 00 50 */	beq lbl_8008F880
/* 8008F834 0008C414  C0 3E 23 40 */	lfs f1, 0x2340(r30)
/* 8008F838 0008C418  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F83C 0008C41C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F840 0008C420  4C 40 13 82 */	cror 2, 0, 2
/* 8008F844 0008C424  40 82 00 3C */	bne lbl_8008F880
/* 8008F848 0008C428  38 00 00 00 */	li r0, 0
/* 8008F84C 0008C42C  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 8008F850 0008C430  98 7E 22 1C */	stb r3, 0x221c(r30)
/* 8008F854 0008C434  7F E3 FB 78 */	mr r3, r31
/* 8008F858 0008C438  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008F85C 0008C43C  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 8008F860 0008C440  B0 1E 20 98 */	sth r0, 0x2098(r30)
/* 8008F864 0008C444  4B FF 00 09 */	bl ftCommon_8007F86C
/* 8008F868 0008C448  7F E3 FB 78 */	mr r3, r31
/* 8008F86C 0008C44C  48 03 59 D5 */	bl ftCo_800C5240
/* 8008F870 0008C450  2C 03 00 00 */	cmpwi r3, 0
/* 8008F874 0008C454  41 82 00 0C */	beq lbl_8008F880
/* 8008F878 0008C458  7F C3 F3 78 */	mr r3, r30
/* 8008F87C 0008C45C  48 03 5C D1 */	bl ftCo_800C554C
lbl_8008F880:
/* 8008F880 0008C460  7F E3 FB 78 */	mr r3, r31
/* 8008F884 0008C464  4B FD F9 B5 */	bl ftAnim_IsFramesRemaining
/* 8008F888 0008C468  2C 03 00 00 */	cmpwi r3, 0
/* 8008F88C 0008C46C  40 82 00 94 */	bne lbl_8008F920
/* 8008F890 0008C470  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8008F894 0008C474  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008F898 0008C478  40 82 00 88 */	bne lbl_8008F920
/* 8008F89C 0008C47C  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8008F8A0 0008C480  2C 00 00 01 */	cmpwi r0, 1
/* 8008F8A4 0008C484  40 82 00 74 */	bne lbl_8008F918
/* 8008F8A8 0008C488  88 1E 22 24 */	lbz r0, 0x2224(r30)
/* 8008F8AC 0008C48C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F8B0 0008C490  41 82 00 10 */	beq lbl_8008F8C0
/* 8008F8B4 0008C494  7F E3 FB 78 */	mr r3, r31
/* 8008F8B8 0008C498  48 00 0E C9 */	bl ftCo_80090780
/* 8008F8BC 0008C49C  48 00 00 64 */	b lbl_8008F920
lbl_8008F8C0:
/* 8008F8C0 0008C4A0  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F8C4 0008C4A4  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F8C8 0008C4A8  C0 24 23 54 */	lfs f1, 0x2354(r4)
/* 8008F8CC 0008C4AC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F8D0 0008C4B0  41 82 00 30 */	beq lbl_8008F900
/* 8008F8D4 0008C4B4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008F8D8 0008C4B8  C0 03 01 D0 */	lfs f0, 0x1d0(r3)
/* 8008F8DC 0008C4BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F8E0 0008C4C0  4C 40 13 82 */	cror 2, 0, 2
/* 8008F8E4 0008C4C4  40 82 00 1C */	bne lbl_8008F900
/* 8008F8E8 0008C4C8  80 04 06 68 */	lwz r0, 0x668(r4)
/* 8008F8EC 0008C4CC  38 7F 00 00 */	addi r3, r31, 0
/* 8008F8F0 0008C4D0  60 00 0C 00 */	ori r0, r0, 0xc00
/* 8008F8F4 0008C4D4  90 04 06 68 */	stw r0, 0x668(r4)
/* 8008F8F8 0008C4D8  48 03 BF 79 */	bl ftCo_800CB870
/* 8008F8FC 0008C4DC  48 00 00 08 */	b lbl_8008F904
lbl_8008F900:
/* 8008F900 0008C4E0  38 60 00 00 */	li r3, 0
lbl_8008F904:
/* 8008F904 0008C4E4  2C 03 00 00 */	cmpwi r3, 0
/* 8008F908 0008C4E8  40 82 00 18 */	bne lbl_8008F920
/* 8008F90C 0008C4EC  7F E3 FB 78 */	mr r3, r31
/* 8008F910 0008C4F0  48 03 CE 21 */	bl ftCo_800CC730
/* 8008F914 0008C4F4  48 00 00 0C */	b lbl_8008F920
lbl_8008F918:
/* 8008F918 0008C4F8  7F E3 FB 78 */	mr r3, r31
/* 8008F91C 0008C4FC  4B FF A9 A1 */	bl ft_8008A2BC
lbl_8008F920:
/* 8008F920 0008C500  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008F924 0008C504  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008F928 0008C508  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008F92C 0008C50C  38 21 00 20 */	addi r1, r1, 0x20
/* 8008F930 0008C510  7C 08 03 A6 */	mtlr r0
/* 8008F934 0008C514  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static bool inlineC0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.damage.x14 && fp->mv.co.damage.x14 <= p_ftCommonData->x1D0) {
        fp->input.x668 |= HSD_PAD_XY;
        return ftCo_800CB870(gobj);
    } else {
        return false;
    }
}

void ftCo_Damage_Anim(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_8008F744(gobj);
    if (!ftAnim_IsFramesRemaining(gobj) && !fp->x221C_b6) {
        if (fp->ground_or_air == GA_Air) {
            if (fp->x2224_b2) {
                ftCo_80090780(gobj);
            } else if (!inlineC0(gobj)) {
                ftCo_800CC730(gobj);
            }
        } else {
            ft_8008A2BC(gobj);
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm static bool doIasa(ftCo_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 8008F938 0008C518  7C 08 02 A6 */	mflr r0
/* 8008F93C 0008C51C  90 01 00 04 */	stw r0, 4(r1)
/* 8008F940 0008C520  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008F944 0008C524  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008F948 0008C528  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008F94C 0008C52C  7C 7E 1B 78 */	mr r30, r3
/* 8008F950 0008C530  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008F954 0008C534  88 03 23 5A */	lbz r0, 0x235a(r3)
/* 8008F958 0008C538  3B E3 00 00 */	addi r31, r3, 0
/* 8008F95C 0008C53C  28 00 00 00 */	cmplwi r0, 0
/* 8008F960 0008C540  41 82 00 A8 */	beq lbl_8008FA08
/* 8008F964 0008C544  88 7F 23 5B */	lbz r3, 0x235b(r31)
/* 8008F968 0008C548  28 03 00 00 */	cmplwi r3, 0
/* 8008F96C 0008C54C  41 82 00 0C */	beq lbl_8008F978
/* 8008F970 0008C550  38 03 FF FF */	addi r0, r3, -1
/* 8008F974 0008C554  98 1F 23 5B */	stb r0, 0x235b(r31)
lbl_8008F978:
/* 8008F978 0008C558  88 1F 23 5B */	lbz r0, 0x235b(r31)
/* 8008F97C 0008C55C  28 00 00 00 */	cmplwi r0, 0
/* 8008F980 0008C560  40 82 00 88 */	bne lbl_8008FA08
/* 8008F984 0008C564  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008F988 0008C568  2C 00 00 01 */	cmpwi r0, 1
/* 8008F98C 0008C56C  40 82 00 7C */	bne lbl_8008FA08
/* 8008F990 0008C570  C0 3F 00 90 */	lfs f1, 0x90(r31)
/* 8008F994 0008C574  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F998 0008C578  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F99C 0008C57C  40 80 00 6C */	bge lbl_8008FA08
/* 8008F9A0 0008C580  7F C3 F3 78 */	mr r3, r30
/* 8008F9A4 0008C584  48 04 70 21 */	bl ftCo_800D69C4
/* 8008F9A8 0008C588  2C 03 00 00 */	cmpwi r3, 0
/* 8008F9AC 0008C58C  40 82 00 14 */	bne lbl_8008F9C0
/* 8008F9B0 0008C590  7F C3 F3 78 */	mr r3, r30
/* 8008F9B4 0008C594  48 03 BF 2D */	bl ftCo_800CB8E0
/* 8008F9B8 0008C598  2C 03 00 00 */	cmpwi r3, 0
/* 8008F9BC 0008C59C  41 82 00 4C */	beq lbl_8008FA08
lbl_8008F9C0:
/* 8008F9C0 0008C5A0  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008F9C4 0008C5A4  38 7F 00 00 */	addi r3, r31, 0
/* 8008F9C8 0008C5A8  38 80 00 0C */	li r4, 0xc
/* 8008F9CC 0008C5AC  D0 1F 00 94 */	stfs f0, 0x94(r31)
/* 8008F9D0 0008C5B0  38 A0 00 00 */	li r5, 0
/* 8008F9D4 0008C5B4  D0 1F 00 90 */	stfs f0, 0x90(r31)
/* 8008F9D8 0008C5B8  D0 1F 00 8C */	stfs f0, 0x8c(r31)
/* 8008F9DC 0008C5BC  4B FE F1 D1 */	bl ftCommon_8007EBAC
/* 8008F9E0 0008C5C0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F9E4 0008C5C4  38 80 00 79 */	li r4, 0x79
/* 8008F9E8 0008C5C8  38 A0 00 00 */	li r5, 0
/* 8008F9EC 0008C5CC  48 03 05 E5 */	bl ftCo_800BFFD0
/* 8008F9F0 0008C5D0  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 8008F9F4 0008C5D4  38 60 00 01 */	li r3, 1
/* 8008F9F8 0008C5D8  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8008F9FC 0008C5DC  98 1F 22 27 */	stb r0, 0x2227(r31)
/* 8008FA00 0008C5E0  38 60 00 01 */	li r3, 1
/* 8008FA04 0008C5E4  48 00 00 28 */	b lbl_8008FA2C
lbl_8008FA08:
/* 8008FA08 0008C5E8  7F C3 F3 78 */	mr r3, r30
/* 8008FA0C 0008C5EC  48 03 B4 75 */	bl ftCo_800CAE80
/* 8008FA10 0008C5F0  2C 03 00 00 */	cmpwi r3, 0
/* 8008FA14 0008C5F4  41 82 00 14 */	beq lbl_8008FA28
/* 8008FA18 0008C5F8  C0 1F 23 40 */	lfs f0, 0x2340(r31)
/* 8008FA1C 0008C5FC  38 60 00 01 */	li r3, 1
/* 8008FA20 0008C600  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 8008FA24 0008C604  48 00 00 08 */	b lbl_8008FA2C
lbl_8008FA28:
/* 8008FA28 0008C608  38 60 00 00 */	li r3, 0
lbl_8008FA2C:
/* 8008FA2C 0008C60C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008FA30 0008C610  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008FA34 0008C614  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008FA38 0008C618  38 21 00 18 */	addi r1, r1, 0x18
/* 8008FA3C 0008C61C  7C 08 03 A6 */	mtlr r0
/* 8008FA40 0008C620  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo Some kind of missing @c bool inline
bool doIasa(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!(fp->mv.co.damage.x1A)) {
        goto ret_inline;
    }
    if (fp->mv.co.damage.x1B) {
        --fp->mv.co.damage.x1B;
    }
    if (!(!fp->mv.co.damage.x1B)) {
        goto ret_inline;
    }
    if (!(fp->ground_or_air == GA_Air)) {
        goto ret_inline;
    }
    if (!(fp->x8c_kb_vel.y < 0)) {
        goto ret_inline;
    }
    if (!(ftCo_800D69C4(gobj) || ftCo_800CB8E0(gobj))) {
        goto ret_inline;
    }
    fp->x8c_kb_vel.x = fp->x8c_kb_vel.y = fp->x8c_kb_vel.z = 0;
    ftCommon_8007EBAC(fp, 12, 0);
    ftCo_800BFFD0(fp, 121, 0);
    fp->x2227_b4 = true;
    return true;
ret_inline:
    if (ftCo_800CAE80(gobj)) {
        fp->mv.co.damage.x14 = fp->mv.co.damage.x0;
        return true;
    }
    return false;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_Damage_IASA(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 8008FA44 0008C624  7C 08 02 A6 */	mflr r0
/* 8008FA48 0008C628  90 01 00 04 */	stw r0, 4(r1)
/* 8008FA4C 0008C62C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008FA50 0008C630  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008FA54 0008C634  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008FA58 0008C638  7C 7E 1B 78 */	mr r30, r3
/* 8008FA5C 0008C63C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008FA60 0008C640  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8008FA64 0008C644  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FA68 0008C648  40 82 00 8C */	bne lbl_8008FAF4
/* 8008FA6C 0008C64C  7F C3 F3 78 */	mr r3, r30
/* 8008FA70 0008C650  48 03 57 D1 */	bl ftCo_800C5240
/* 8008FA74 0008C654  2C 03 00 00 */	cmpwi r3, 0
/* 8008FA78 0008C658  41 82 00 28 */	beq lbl_8008FAA0
/* 8008FA7C 0008C65C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008FA80 0008C660  2C 00 00 01 */	cmpwi r0, 1
/* 8008FA84 0008C664  40 82 00 10 */	bne lbl_8008FA94
/* 8008FA88 0008C668  7F C3 F3 78 */	mr r3, r30
/* 8008FA8C 0008C66C  48 03 64 09 */	bl ftCo_HammerFall_IASA
/* 8008FA90 0008C670  48 00 00 70 */	b lbl_8008FB00
lbl_8008FA94:
/* 8008FA94 0008C674  7F C3 F3 78 */	mr r3, r30
/* 8008FA98 0008C678  48 03 55 DD */	bl ftCo_HammerWait_IASA
/* 8008FA9C 0008C67C  48 00 00 64 */	b lbl_8008FB00
lbl_8008FAA0:
/* 8008FAA0 0008C680  C0 3F 23 54 */	lfs f1, 0x2354(r31)
/* 8008FAA4 0008C684  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008FAA8 0008C688  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008FAAC 0008C68C  41 82 00 24 */	beq lbl_8008FAD0
/* 8008FAB0 0008C690  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008FAB4 0008C694  C0 03 01 D0 */	lfs f0, 0x1d0(r3)
/* 8008FAB8 0008C698  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FABC 0008C69C  4C 40 13 82 */	cror 2, 0, 2
/* 8008FAC0 0008C6A0  40 82 00 10 */	bne lbl_8008FAD0
/* 8008FAC4 0008C6A4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008FAC8 0008C6A8  60 00 0C 00 */	ori r0, r0, 0xc00
/* 8008FACC 0008C6AC  90 1F 06 68 */	stw r0, 0x668(r31)
lbl_8008FAD0:
/* 8008FAD0 0008C6B0  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008FAD4 0008C6B4  2C 00 00 01 */	cmpwi r0, 1
/* 8008FAD8 0008C6B8  40 82 00 10 */	bne lbl_8008FAE8
/* 8008FADC 0008C6BC  7F C3 F3 78 */	mr r3, r30
/* 8008FAE0 0008C6C0  48 03 CF CD */	bl ftCo_800CCAAC
/* 8008FAE4 0008C6C4  48 00 00 1C */	b lbl_8008FB00
lbl_8008FAE8:
/* 8008FAE8 0008C6C8  7F C3 F3 78 */	mr r3, r30
/* 8008FAEC 0008C6CC  4B FF A9 E9 */	bl ftCo_Wait_IASA
/* 8008FAF0 0008C6D0  48 00 00 10 */	b lbl_8008FB00
lbl_8008FAF4:
/* 8008FAF4 0008C6D4  7F C3 F3 78 */	mr r3, r30
/* 8008FAF8 0008C6D8  4B FF FE 41 */	bl doIasa
/* 8008FAFC 0008C6DC  2C 03 00 00 */	cmpwi r3, 0
lbl_8008FB00:
/* 8008FB00 0008C6E0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008FB04 0008C6E4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008FB08 0008C6E8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008FB0C 0008C6EC  38 21 00 18 */	addi r1, r1, 0x18
/* 8008FB10 0008C6F0  7C 08 03 A6 */	mtlr r0
/* 8008FB14 0008C6F4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_Damage_IASA(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!fp->x221C_b6) {
        if (ftCo_800C5240(gobj)) {
            if (fp->ground_or_air == GA_Air) {
                ftCo_HammerFall_IASA(gobj);
            } else {
                ftCo_HammerWait_IASA(gobj);
            }
        } else {
            if (fp->mv.co.damage.x14 &&
                fp->mv.co.damage.x14 <= p_ftCommonData->x1D0)
            {
                fp->input.x668 |= HSD_PAD_XY;
            }
            if (fp->ground_or_air == GA_Air) {
                ftCo_800CCAAC(gobj);
            } else {
                ftCo_Wait_IASA(gobj);
            }
        }
    } else {
        RETURN_IF(doIasa(gobj))
    }
}
#endif

void ftCo_Damage_Phys(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (!fp->x221C_b6) {
            ft_80084DB0(gobj);
        } else {
            ft_80084EEC(gobj);
        }
    } else {
        ft_80084F3C(gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_Damage_Coll(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 8008FB64 0008C744  7C 08 02 A6 */	mflr r0
/* 8008FB68 0008C748  90 01 00 04 */	stw r0, 4(r1)
/* 8008FB6C 0008C74C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008FB70 0008C750  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008FB74 0008C754  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008FB78 0008C758  7C 7E 1B 78 */	mr r30, r3
/* 8008FB7C 0008C75C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008FB80 0008C760  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8008FB84 0008C764  3B E3 00 00 */	addi r31, r3, 0
/* 8008FB88 0008C768  2C 00 00 00 */	cmpwi r0, 0
/* 8008FB8C 0008C76C  40 82 00 18 */	bne lbl_8008FBA4
/* 8008FB90 0008C770  3C 60 80 09 */	lis r3, ftCo_8008FC94@ha
/* 8008FB94 0008C774  38 83 FC 94 */	addi r4, r3, ftCo_8008FC94@l
/* 8008FB98 0008C778  38 7E 00 00 */	addi r3, r30, 0
/* 8008FB9C 0008C77C  4B FF 4D 41 */	bl ft_800848DC
/* 8008FBA0 0008C780  48 00 00 DC */	b lbl_8008FC7C
lbl_8008FBA4:
/* 8008FBA4 0008C784  7F C3 F3 78 */	mr r3, r30
/* 8008FBA8 0008C788  4B FF 22 2D */	bl ft_80081DD4
/* 8008FBAC 0008C78C  2C 03 00 00 */	cmpwi r3, 0
/* 8008FBB0 0008C790  41 82 00 CC */	beq lbl_8008FC7C
/* 8008FBB4 0008C794  88 1F 22 24 */	lbz r0, 0x2224(r31)
/* 8008FBB8 0008C798  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008FBBC 0008C79C  41 82 00 10 */	beq lbl_8008FBCC
/* 8008FBC0 0008C7A0  7F C3 F3 78 */	mr r3, r30
/* 8008FBC4 0008C7A4  48 00 81 7D */	bl ftCo_80097D40
/* 8008FBC8 0008C7A8  48 00 00 B4 */	b lbl_8008FC7C
lbl_8008FBCC:
/* 8008FBCC 0008C7AC  C0 1F 00 8C */	lfs f0, 0x8c(r31)
/* 8008FBD0 0008C7B0  C0 3F 00 90 */	lfs f1, 0x90(r31)
/* 8008FBD4 0008C7B4  EC 40 00 32 */	fmuls f2, f0, f0
/* 8008FBD8 0008C7B8  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008FBDC 0008C7BC  EC 21 00 72 */	fmuls f1, f1, f1
/* 8008FBE0 0008C7C0  EC 82 08 2A */	fadds f4, f2, f1
/* 8008FBE4 0008C7C4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008FBE8 0008C7C8  40 81 00 50 */	ble lbl_8008FC38
/* 8008FBEC 0008C7CC  FC 20 20 34 */	frsqrte f1, f4
/* 8008FBF0 0008C7D0  C8 62 8B 20 */	lfd f3, lbl_804D8500
/* 8008FBF4 0008C7D4  C8 42 8B 28 */	lfd f2, lbl_804D8508
/* 8008FBF8 0008C7D8  FC 01 00 72 */	fmul f0, f1, f1
/* 8008FBFC 0008C7DC  FC 23 00 72 */	fmul f1, f3, f1
/* 8008FC00 0008C7E0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008FC04 0008C7E4  FC 21 00 32 */	fmul f1, f1, f0
/* 8008FC08 0008C7E8  FC 01 00 72 */	fmul f0, f1, f1
/* 8008FC0C 0008C7EC  FC 23 00 72 */	fmul f1, f3, f1
/* 8008FC10 0008C7F0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008FC14 0008C7F4  FC 21 00 32 */	fmul f1, f1, f0
/* 8008FC18 0008C7F8  FC 01 00 72 */	fmul f0, f1, f1
/* 8008FC1C 0008C7FC  FC 23 00 72 */	fmul f1, f3, f1
/* 8008FC20 0008C800  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008FC24 0008C804  FC 01 00 32 */	fmul f0, f1, f0
/* 8008FC28 0008C808  FC 04 00 32 */	fmul f0, f4, f0
/* 8008FC2C 0008C80C  FC 00 00 18 */	frsp f0, f0
/* 8008FC30 0008C810  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8008FC34 0008C814  C0 81 00 10 */	lfs f4, 0x10(r1)
lbl_8008FC38:
/* 8008FC38 0008C818  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008FC3C 0008C81C  C0 03 01 E0 */	lfs f0, 0x1e0(r3)
/* 8008FC40 0008C820  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008FC44 0008C824  4C 41 13 82 */	cror 2, 1, 2
/* 8008FC48 0008C828  40 82 00 10 */	bne lbl_8008FC58
/* 8008FC4C 0008C82C  7F C3 F3 78 */	mr r3, r30
/* 8008FC50 0008C830  48 00 80 F1 */	bl ftCo_80097D40
/* 8008FC54 0008C834  48 00 00 28 */	b lbl_8008FC7C
lbl_8008FC58:
/* 8008FC58 0008C838  C0 03 01 E4 */	lfs f0, 0x1e4(r3)
/* 8008FC5C 0008C83C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008FC60 0008C840  4C 41 13 82 */	cror 2, 1, 2
/* 8008FC64 0008C844  40 82 00 10 */	bne lbl_8008FC74
/* 8008FC68 0008C848  7F C3 F3 78 */	mr r3, r30
/* 8008FC6C 0008C84C  48 04 5F 8D */	bl ftCo_800D5BF8
/* 8008FC70 0008C850  48 00 00 0C */	b lbl_8008FC7C
lbl_8008FC74:
/* 8008FC74 0008C854  7F E3 FB 78 */	mr r3, r31
/* 8008FC78 0008C858  4B FE DB 85 */	bl ftCommon_8007D7FC
lbl_8008FC7C:
/* 8008FC7C 0008C85C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008FC80 0008C860  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008FC84 0008C864  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008FC88 0008C868  38 21 00 20 */	addi r1, r1, 0x20
/* 8008FC8C 0008C86C  7C 08 03 A6 */	mtlr r0
/* 8008FC90 0008C870  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_Damage_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        ft_800848DC(gobj, ftCo_8008FC94);
    } else if (ft_80081DD4(gobj)) {
        if (fp->x2224_b2) {
            ftCo_80097D40(gobj);
        } else {
            float mag = sqrtf(VEC2_SQ_LEN(fp->x8c_kb_vel));
            if (mag >= p_ftCommonData->x1E0) {
                ftCo_80097D40(gobj);
            } else if (mag >= p_ftCommonData->x1E4) {
                ftCo_800D5BF8(gobj);
            } else {
                ftCommon_8007D7FC(fp);
            }
        }
    }
}
#endif

void ftCo_8008FC94(ftCo_GObj* gobj)
{
    ftCommon_8007D5D4(gobj->user_data);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* 08FCB8 */ static void
ftCo_Damage_SetMv8FromKbThreshold(ftCo_Fighter* fp)
{ // clang-format off
    nofralloc
/* 8008FCB8 0008C898  7C 08 02 A6 */	mflr r0
/* 8008FCBC 0008C89C  90 01 00 04 */	stw r0, 4(r1)
/* 8008FCC0 0008C8A0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008FCC4 0008C8A4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008FCC8 0008C8A8  7C 7F 1B 78 */	mr r31, r3
/* 8008FCCC 0008C8AC  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8008FCD0 0008C8B0  2C 00 00 01 */	cmpwi r0, 1
/* 8008FCD4 0008C8B4  40 82 00 2C */	bne lbl_8008FD00
/* 8008FCD8 0008C8B8  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008FCDC 0008C8BC  C0 1F 00 90 */	lfs f0, 0x90(r31)
/* 8008FCE0 0008C8C0  EC 21 00 72 */	fmuls f1, f1, f1
/* 8008FCE4 0008C8C4  C0 5F 00 94 */	lfs f2, 0x94(r31)
/* 8008FCE8 0008C8C8  EC 00 00 32 */	fmuls f0, f0, f0
/* 8008FCEC 0008C8CC  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8008FCF0 0008C8D0  EC 01 00 2A */	fadds f0, f1, f0
/* 8008FCF4 0008C8D4  EC 22 00 2A */	fadds f1, f2, f0
/* 8008FCF8 0008C8D8  4B F7 D8 C5 */	bl sqrtf__Ff
/* 8008FCFC 0008C8DC  48 00 00 18 */	b lbl_8008FD14
lbl_8008FD00:
/* 8008FD00 0008C8E0  C0 3F 00 F0 */	lfs f1, 0xf0(r31)
/* 8008FD04 0008C8E4  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008FD08 0008C8E8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD0C 0008C8EC  40 80 00 08 */	bge lbl_8008FD14
/* 8008FD10 0008C8F0  FC 20 08 50 */	fneg f1, f1
lbl_8008FD14:
/* 8008FD14 0008C8F4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008FD18 0008C8F8  C0 03 05 68 */	lfs f0, 0x568(r3)
/* 8008FD1C 0008C8FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD20 0008C900  40 80 00 0C */	bge lbl_8008FD2C
/* 8008FD24 0008C904  38 00 00 00 */	li r0, 0
/* 8008FD28 0008C908  48 00 00 58 */	b lbl_8008FD80
lbl_8008FD2C:
/* 8008FD2C 0008C90C  C0 03 05 6C */	lfs f0, 0x56c(r3)
/* 8008FD30 0008C910  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD34 0008C914  40 80 00 0C */	bge lbl_8008FD40
/* 8008FD38 0008C918  80 03 05 7C */	lwz r0, 0x57c(r3)
/* 8008FD3C 0008C91C  48 00 00 44 */	b lbl_8008FD80
lbl_8008FD40:
/* 8008FD40 0008C920  C0 03 05 70 */	lfs f0, 0x570(r3)
/* 8008FD44 0008C924  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD48 0008C928  40 80 00 0C */	bge lbl_8008FD54
/* 8008FD4C 0008C92C  80 03 05 7C */	lwz r0, 0x57c(r3)
/* 8008FD50 0008C930  48 00 00 30 */	b lbl_8008FD80
lbl_8008FD54:
/* 8008FD54 0008C934  C0 03 05 74 */	lfs f0, 0x574(r3)
/* 8008FD58 0008C938  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD5C 0008C93C  40 80 00 0C */	bge lbl_8008FD68
/* 8008FD60 0008C940  80 03 05 80 */	lwz r0, 0x580(r3)
/* 8008FD64 0008C944  48 00 00 1C */	b lbl_8008FD80
lbl_8008FD68:
/* 8008FD68 0008C948  C0 03 05 78 */	lfs f0, 0x578(r3)
/* 8008FD6C 0008C94C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD70 0008C950  40 80 00 0C */	bge lbl_8008FD7C
/* 8008FD74 0008C954  80 03 05 84 */	lwz r0, 0x584(r3)
/* 8008FD78 0008C958  48 00 00 08 */	b lbl_8008FD80
lbl_8008FD7C:
/* 8008FD7C 0008C95C  80 03 05 88 */	lwz r0, 0x588(r3)
lbl_8008FD80:
/* 8008FD80 0008C960  90 1F 23 48 */	stw r0, 0x2348(r31)
/* 8008FD84 0008C964  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008FD88 0008C968  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008FD8C 0008C96C  38 21 00 18 */	addi r1, r1, 0x18
/* 8008FD90 0008C970  7C 08 03 A6 */	mtlr r0
/* 8008FD94 0008C974  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_Damage_SetMv8FromKbThreshold(Fighter* fp)
{
    float kb_vel = fp->ground_or_air == GA_Air
                       ? sqrtf__Ff(VEC3_SQ_LEN(fp->x8c_kb_vel))
                       : ABS(fp->xF0_ground_kb_vel);
    fp->mv.co.damage.x8 =
        kb_vel < p_ftCommonData->x568   ? 0
        : kb_vel < p_ftCommonData->x56C ? p_ftCommonData->x57C
        : kb_vel < p_ftCommonData->x570 ? p_ftCommonData->x57C
        : kb_vel < p_ftCommonData->x574 ? p_ftCommonData->x580
        : kb_vel < p_ftCommonData->x578 ? p_ftCommonData->x584
                                        : p_ftCommonData->x588;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_DamageFly_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 8008FD98 0008C978  7C 08 02 A6 */	mflr r0
/* 8008FD9C 0008C97C  90 01 00 04 */	stw r0, 4(r1)
/* 8008FDA0 0008C980  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8008FDA4 0008C984  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8008FDA8 0008C988  7C 7F 1B 78 */	mr r31, r3
/* 8008FDAC 0008C98C  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8008FDB0 0008C990  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8008FDB4 0008C994  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008FDB8 0008C998  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8008FDBC 0008C99C  2C 03 00 00 */	cmpwi r3, 0
/* 8008FDC0 0008C9A0  41 82 00 84 */	beq lbl_8008FE44
/* 8008FDC4 0008C9A4  38 03 FF FF */	addi r0, r3, -1
/* 8008FDC8 0008C9A8  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8008FDCC 0008C9AC  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8008FDD0 0008C9B0  2C 00 00 00 */	cmpwi r0, 0
/* 8008FDD4 0008C9B4  40 82 00 70 */	bne lbl_8008FE44
/* 8008FDD8 0008C9B8  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8008FDDC 0008C9BC  2C 00 00 01 */	cmpwi r0, 1
/* 8008FDE0 0008C9C0  40 82 00 10 */	bne lbl_8008FDF0
/* 8008FDE4 0008C9C4  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 8008FDE8 0008C9C8  C0 5E 00 90 */	lfs f2, 0x90(r30)
/* 8008FDEC 0008C9CC  48 00 00 1C */	b lbl_8008FE08
lbl_8008FDF0:
/* 8008FDF0 0008C9D0  C0 1E 08 44 */	lfs f0, 0x844(r30)
/* 8008FDF4 0008C9D4  C0 5E 00 F0 */	lfs f2, 0xf0(r30)
/* 8008FDF8 0008C9D8  FC 00 00 50 */	fneg f0, f0
/* 8008FDFC 0008C9DC  C0 3E 08 48 */	lfs f1, 0x848(r30)
/* 8008FE00 0008C9E0  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008FE04 0008C9E4  EC 40 00 B2 */	fmuls f2, f0, f2
lbl_8008FE08:
/* 8008FE08 0008C9E8  FC 20 08 50 */	fneg f1, f1
/* 8008FE0C 0008C9EC  4B F9 2E 25 */	bl atan2f
/* 8008FE10 0008C9F0  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 8008FE14 0008C9F4  38 7F 00 00 */	addi r3, r31, 0
/* 8008FE18 0008C9F8  39 01 00 28 */	addi r8, r1, 0x28
/* 8008FE1C 0008C9FC  4C C6 31 82 */	crclr 6
/* 8008FE20 0008CA00  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8008FE24 0008CA04  81 3F 00 2C */	lwz r9, 0x2c(r31)
/* 8008FE28 0008CA08  38 A0 00 04 */	li r5, 4
/* 8008FE2C 0008CA0C  80 E4 00 00 */	lwz r7, 0(r4)
/* 8008FE30 0008CA10  38 C0 04 08 */	li r6, 0x408
/* 8008FE34 0008CA14  38 89 06 0C */	addi r4, r9, 0x60c
/* 8008FE38 0008CA18  4B FD 78 B9 */	bl efAsync_Spawn
/* 8008FE3C 0008CA1C  7F C3 F3 78 */	mr r3, r30
/* 8008FE40 0008CA20  4B FF FE 79 */	bl ftCo_Damage_SetMv8FromKbThreshold
lbl_8008FE44:
/* 8008FE44 0008CA24  83 BF 00 2C */	lwz r29, 0x2c(r31)
/* 8008FE48 0008CA28  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008FE4C 0008CA2C  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 8008FE50 0008CA30  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FE54 0008CA34  40 81 00 10 */	ble lbl_8008FE64
/* 8008FE58 0008CA38  C0 02 8A F8 */	lfs f0, lbl_804D84D8
/* 8008FE5C 0008CA3C  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008FE60 0008CA40  D0 1D 23 40 */	stfs f0, 0x2340(r29)
lbl_8008FE64:
/* 8008FE64 0008CA44  88 7D 22 1C */	lbz r3, 0x221c(r29)
/* 8008FE68 0008CA48  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8008FE6C 0008CA4C  41 82 00 50 */	beq lbl_8008FEBC
/* 8008FE70 0008CA50  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 8008FE74 0008CA54  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008FE78 0008CA58  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FE7C 0008CA5C  4C 40 13 82 */	cror 2, 0, 2
/* 8008FE80 0008CA60  40 82 00 3C */	bne lbl_8008FEBC
/* 8008FE84 0008CA64  38 00 00 00 */	li r0, 0
/* 8008FE88 0008CA68  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 8008FE8C 0008CA6C  98 7D 22 1C */	stb r3, 0x221c(r29)
/* 8008FE90 0008CA70  7F E3 FB 78 */	mr r3, r31
/* 8008FE94 0008CA74  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8008FE98 0008CA78  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 8008FE9C 0008CA7C  B0 1D 20 98 */	sth r0, 0x2098(r29)
/* 8008FEA0 0008CA80  4B FE F9 CD */	bl ftCommon_8007F86C
/* 8008FEA4 0008CA84  7F E3 FB 78 */	mr r3, r31
/* 8008FEA8 0008CA88  48 03 53 99 */	bl ftCo_800C5240
/* 8008FEAC 0008CA8C  2C 03 00 00 */	cmpwi r3, 0
/* 8008FEB0 0008CA90  41 82 00 0C */	beq lbl_8008FEBC
/* 8008FEB4 0008CA94  7F A3 EB 78 */	mr r3, r29
/* 8008FEB8 0008CA98  48 03 56 95 */	bl ftCo_800C554C
lbl_8008FEBC:
/* 8008FEBC 0008CA9C  7F E3 FB 78 */	mr r3, r31
/* 8008FEC0 0008CAA0  4B FD F3 79 */	bl ftAnim_IsFramesRemaining
/* 8008FEC4 0008CAA4  2C 03 00 00 */	cmpwi r3, 0
/* 8008FEC8 0008CAA8  40 82 00 64 */	bne lbl_8008FF2C
/* 8008FECC 0008CAAC  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8008FED0 0008CAB0  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FED4 0008CAB4  40 82 00 58 */	bne lbl_8008FF2C
/* 8008FED8 0008CAB8  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008FEDC 0008CABC  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 8008FEE0 0008CAC0  C0 24 23 54 */	lfs f1, 0x2354(r4)
/* 8008FEE4 0008CAC4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008FEE8 0008CAC8  41 82 00 30 */	beq lbl_8008FF18
/* 8008FEEC 0008CACC  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8008FEF0 0008CAD0  C0 03 01 D0 */	lfs f0, 0x1d0(r3)
/* 8008FEF4 0008CAD4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FEF8 0008CAD8  4C 40 13 82 */	cror 2, 0, 2
/* 8008FEFC 0008CADC  40 82 00 1C */	bne lbl_8008FF18
/* 8008FF00 0008CAE0  80 04 06 68 */	lwz r0, 0x668(r4)
/* 8008FF04 0008CAE4  38 7F 00 00 */	addi r3, r31, 0
/* 8008FF08 0008CAE8  60 00 0C 00 */	ori r0, r0, 0xc00
/* 8008FF0C 0008CAEC  90 04 06 68 */	stw r0, 0x668(r4)
/* 8008FF10 0008CAF0  48 03 B9 61 */	bl ftCo_800CB870
/* 8008FF14 0008CAF4  48 00 00 08 */	b lbl_8008FF1C
lbl_8008FF18:
/* 8008FF18 0008CAF8  38 60 00 00 */	li r3, 0
lbl_8008FF1C:
/* 8008FF1C 0008CAFC  2C 03 00 00 */	cmpwi r3, 0
/* 8008FF20 0008CB00  40 82 00 0C */	bne lbl_8008FF2C
/* 8008FF24 0008CB04  7F E3 FB 78 */	mr r3, r31
/* 8008FF28 0008CB08  48 00 08 59 */	bl ftCo_80090780
lbl_8008FF2C:
/* 8008FF2C 0008CB0C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8008FF30 0008CB10  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8008FF34 0008CB14  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8008FF38 0008CB18  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8008FF3C 0008CB1C  38 21 00 40 */	addi r1, r1, 0x40
/* 8008FF40 0008CB20  7C 08 03 A6 */	mtlr r0
/* 8008FF44 0008CB24  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline void inlineD0(ftCo_GObj* gobj)
{
    float param;
    ftCo_Fighter* fp = gobj->user_data;
    --fp->mv.co.damage.x8;
    if (fp->mv.co.damage.x8 == 0) {
        float x, y;
        if (fp->ground_or_air == GA_Air) {
            y = fp->x8c_kb_vel.x;
            x = fp->x8c_kb_vel.y;
        } else {
            float kb_vel = fp->xF0_ground_kb_vel;
            y = fp->coll_data.floor.normal.y * kb_vel;
            x = -fp->coll_data.floor.normal.x * kb_vel;
        }
        {
            float trajectory = atan2f(-y, x);
            param = trajectory;
            efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 4, 1032,
                          fp->parts[FtPart_TopN].joint, &param);
        }
        ftCo_Damage_SetMv8FromKbThreshold(fp);
    }
}

void ftCo_DamageFly_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    inlineD0(gobj);
    ftCo_8008F744(gobj);
    if (!ftAnim_IsFramesRemaining(gobj) && !fp->x221C_b6) {
        if (!inlineC0(gobj)) {
            ftCo_80090780(gobj);
        }
    }
}
#endif

void ftCo_DamageFly_IASA(ftCo_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x221C_b6) {
        ftCo_DamageFall_IASA(gobj);
    } else {
        RETURN_IF(doIasa(gobj))
    }
}

static void doFlyRoll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    float trajectory =
        fp->facing_dir * atan2f(fp->self_vel.x + fp->x8c_kb_vel.x,
                                fp->self_vel.y + fp->x8c_kb_vel.y);
    ftParts_8007592C(fp, ftParts_8007500C(fp, FtPart_XRotN), trajectory);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_DamageFly_Phys(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 8008FF84 0008CB64  7C 08 02 A6 */	mflr r0
/* 8008FF88 0008CB68  90 01 00 04 */	stw r0, 4(r1)
/* 8008FF8C 0008CB6C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8008FF90 0008CB70  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8008FF94 0008CB74  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008FF98 0008CB78  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008FF9C 0008CB7C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8008FFA0 0008CB80  7C 7D 1B 78 */	mr r29, r3
/* 8008FFA4 0008CB84  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008FFA8 0008CB88  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8008FFAC 0008CB8C  2C 00 00 01 */	cmpwi r0, 1
/* 8008FFB0 0008CB90  40 82 00 28 */	bne lbl_8008FFD8
/* 8008FFB4 0008CB94  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8008FFB8 0008CB98  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FFBC 0008CB9C  40 82 00 10 */	bne lbl_8008FFCC
/* 8008FFC0 0008CBA0  7F A3 EB 78 */	mr r3, r29
/* 8008FFC4 0008CBA4  4B FF 4D ED */	bl ft_80084DB0
/* 8008FFC8 0008CBA8  48 00 00 18 */	b lbl_8008FFE0
lbl_8008FFCC:
/* 8008FFCC 0008CBAC  7F A3 EB 78 */	mr r3, r29
/* 8008FFD0 0008CBB0  4B FF 4F 1D */	bl ft_80084EEC
/* 8008FFD4 0008CBB4  48 00 00 0C */	b lbl_8008FFE0
lbl_8008FFD8:
/* 8008FFD8 0008CBB8  7F A3 EB 78 */	mr r3, r29
/* 8008FFDC 0008CBBC  4B FF 4F 61 */	bl ft_80084F3C
lbl_8008FFE0:
/* 8008FFE0 0008CBC0  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8008FFE4 0008CBC4  2C 00 00 5B */	cmpwi r0, 0x5b
/* 8008FFE8 0008CBC8  40 82 00 48 */	bne lbl_80090030
/* 8008FFEC 0008CBCC  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 8008FFF0 0008CBD0  C0 7F 00 80 */	lfs f3, 0x80(r31)
/* 8008FFF4 0008CBD4  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008FFF8 0008CBD8  C0 5F 00 84 */	lfs f2, 0x84(r31)
/* 8008FFFC 0008CBDC  C0 1F 00 90 */	lfs f0, 0x90(r31)
/* 80090000 0008CBE0  EC 23 08 2A */	fadds f1, f3, f1
/* 80090004 0008CBE4  EC 42 00 2A */	fadds f2, f2, f0
/* 80090008 0008CBE8  4B F9 2C 29 */	bl atan2f
/* 8009000C 0008CBEC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80090010 0008CBF0  38 7F 00 00 */	addi r3, r31, 0
/* 80090014 0008CBF4  38 80 00 02 */	li r4, 2
/* 80090018 0008CBF8  EF E0 00 72 */	fmuls f31, f0, f1
/* 8009001C 0008CBFC  4B FE 4F F1 */	bl ftParts_8007500C
/* 80090020 0008CC00  FC 20 F8 90 */	fmr f1, f31
/* 80090024 0008CC04  38 83 00 00 */	addi r4, r3, 0
/* 80090028 0008CC08  38 7F 00 00 */	addi r3, r31, 0
/* 8009002C 0008CC0C  4B FE 59 01 */	bl ftParts_8007592C
lbl_80090030:
/* 80090030 0008CC10  80 1E 11 98 */	lwz r0, 0x1198(r30)
/* 80090034 0008CC14  28 00 00 00 */	cmplwi r0, 0
/* 80090038 0008CC18  41 82 00 94 */	beq lbl_800900CC
/* 8009003C 0008CC1C  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 80090040 0008CC20  C0 1E 00 90 */	lfs f0, 0x90(r30)
/* 80090044 0008CC24  EC 41 00 72 */	fmuls f2, f1, f1
/* 80090048 0008CC28  C0 7E 00 94 */	lfs f3, 0x94(r30)
/* 8009004C 0008CC2C  EC 20 00 32 */	fmuls f1, f0, f0
/* 80090050 0008CC30  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 80090054 0008CC34  EC 63 00 F2 */	fmuls f3, f3, f3
/* 80090058 0008CC38  EC 22 08 2A */	fadds f1, f2, f1
/* 8009005C 0008CC3C  EC 83 08 2A */	fadds f4, f3, f1
/* 80090060 0008CC40  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80090064 0008CC44  40 81 00 50 */	ble lbl_800900B4
/* 80090068 0008CC48  FC 20 20 34 */	frsqrte f1, f4
/* 8009006C 0008CC4C  C8 62 8B 20 */	lfd f3, lbl_804D8500
/* 80090070 0008CC50  C8 42 8B 28 */	lfd f2, lbl_804D8508
/* 80090074 0008CC54  FC 01 00 72 */	fmul f0, f1, f1
/* 80090078 0008CC58  FC 23 00 72 */	fmul f1, f3, f1
/* 8009007C 0008CC5C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80090080 0008CC60  FC 21 00 32 */	fmul f1, f1, f0
/* 80090084 0008CC64  FC 01 00 72 */	fmul f0, f1, f1
/* 80090088 0008CC68  FC 23 00 72 */	fmul f1, f3, f1
/* 8009008C 0008CC6C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80090090 0008CC70  FC 21 00 32 */	fmul f1, f1, f0
/* 80090094 0008CC74  FC 01 00 72 */	fmul f0, f1, f1
/* 80090098 0008CC78  FC 23 00 72 */	fmul f1, f3, f1
/* 8009009C 0008CC7C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800900A0 0008CC80  FC 01 00 32 */	fmul f0, f1, f0
/* 800900A4 0008CC84  FC 04 00 32 */	fmul f0, f4, f0
/* 800900A8 0008CC88  FC 00 00 18 */	frsp f0, f0
/* 800900AC 0008CC8C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800900B0 0008CC90  C0 81 00 18 */	lfs f4, 0x18(r1)
lbl_800900B4:
/* 800900B4 0008CC94  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800900B8 0008CC98  C0 03 01 C8 */	lfs f0, 0x1c8(r3)
/* 800900BC 0008CC9C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800900C0 0008CCA0  40 80 00 0C */	bge lbl_800900CC
/* 800900C4 0008CCA4  7F A3 EB 78 */	mr r3, r29
/* 800900C8 0008CCA8  4B FE AF 31 */	bl ftColl_8007AFF8
lbl_800900CC:
/* 800900CC 0008CCAC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800900D0 0008CCB0  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800900D4 0008CCB4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800900D8 0008CCB8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800900DC 0008CCBC  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800900E0 0008CCC0  38 21 00 38 */	addi r1, r1, 0x38
/* 800900E4 0008CCC4  7C 08 03 A6 */	mtlr r0
/* 800900E8 0008CCC8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_DamageFly_Phys(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (!fp->x221C_b6) {
            ft_80084DB0(gobj);
        } else {
            ft_80084EEC(gobj);
        }
    } else {
        ft_80084F3C(gobj);
    }
    if (fp->motion_id == ftCo_MS_DamageFlyRoll) {
        doFlyRoll(gobj);
    }
    if (fp->x1064_thrownHitbox.owner != NULL &&
        sqrtf(VEC3_SQ_LEN(fp->x8c_kb_vel)) < p_ftCommonData->x1C8)
    {
        ftColl_8007AFF8(gobj);
    }
}
#endif

void ftCo_DamageFly_Coll(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    CollData* coll = &GET_FIGHTER(gobj)->coll_data;
    if (ft_80081DD4(gobj) != 0) {
        ftCo_80090184(gobj);
        return;
    } else {
        u32 env_flags = coll->env_flags;
        if (env_flags & MPCOLL_FLAGS_B11 || env_flags & MPCOLL_FLAGS_B05 ||
            env_flags & MPCOLL_FLAGS_B14)
        {
            RETURN_IF(ftCo_800C1D38(gobj))
            RETURN_IF(ftCo_800C23A0(gobj))
            RETURN_IF(ftCo_800C17CC(gobj))
        }
    }
}

void ftCo_80090184(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_80098928(gobj))
    RETURN_IF(ftCo_8009872C(gobj))
    ftCo_80097D40(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_DamageFlyRoll_Anim(ftCo_GObj*)
{
    // clang-format off
    nofralloc
/* 800901D0 0008CDB0  7C 08 02 A6 */	mflr r0
/* 800901D4 0008CDB4  90 01 00 04 */	stw r0, 4(r1)
/* 800901D8 0008CDB8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800901DC 0008CDBC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800901E0 0008CDC0  7C 7F 1B 78 */	mr r31, r3
/* 800901E4 0008CDC4  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800901E8 0008CDC8  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800901EC 0008CDCC  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800901F0 0008CDD0  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 800901F4 0008CDD4  2C 03 00 00 */	cmpwi r3, 0
/* 800901F8 0008CDD8  41 82 00 84 */	beq lbl_8009027C
/* 800901FC 0008CDDC  38 03 FF FF */	addi r0, r3, -1
/* 80090200 0008CDE0  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 80090204 0008CDE4  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 80090208 0008CDE8  2C 00 00 00 */	cmpwi r0, 0
/* 8009020C 0008CDEC  40 82 00 70 */	bne lbl_8009027C
/* 80090210 0008CDF0  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80090214 0008CDF4  2C 00 00 01 */	cmpwi r0, 1
/* 80090218 0008CDF8  40 82 00 10 */	bne lbl_80090228
/* 8009021C 0008CDFC  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 80090220 0008CE00  C0 5E 00 90 */	lfs f2, 0x90(r30)
/* 80090224 0008CE04  48 00 00 1C */	b lbl_80090240
lbl_80090228:
/* 80090228 0008CE08  C0 1E 08 44 */	lfs f0, 0x844(r30)
/* 8009022C 0008CE0C  C0 5E 00 F0 */	lfs f2, 0xf0(r30)
/* 80090230 0008CE10  FC 00 00 50 */	fneg f0, f0
/* 80090234 0008CE14  C0 3E 08 48 */	lfs f1, 0x848(r30)
/* 80090238 0008CE18  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8009023C 0008CE1C  EC 40 00 B2 */	fmuls f2, f0, f2
lbl_80090240:
/* 80090240 0008CE20  FC 20 08 50 */	fneg f1, f1
/* 80090244 0008CE24  4B F9 29 ED */	bl atan2f
/* 80090248 0008CE28  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 8009024C 0008CE2C  38 7F 00 00 */	addi r3, r31, 0
/* 80090250 0008CE30  39 01 00 24 */	addi r8, r1, 0x24
/* 80090254 0008CE34  4C C6 31 82 */	crclr 6
/* 80090258 0008CE38  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8009025C 0008CE3C  81 3F 00 2C */	lwz r9, 0x2c(r31)
/* 80090260 0008CE40  38 A0 00 04 */	li r5, 4
/* 80090264 0008CE44  80 E4 00 00 */	lwz r7, 0(r4)
/* 80090268 0008CE48  38 C0 04 08 */	li r6, 0x408
/* 8009026C 0008CE4C  38 89 06 0C */	addi r4, r9, 0x60c
/* 80090270 0008CE50  4B FD 74 81 */	bl efAsync_Spawn
/* 80090274 0008CE54  7F C3 F3 78 */	mr r3, r30
/* 80090278 0008CE58  4B FF FA 41 */	bl ftCo_Damage_SetMv8FromKbThreshold
lbl_8009027C:
/* 8009027C 0008CE5C  83 BF 00 2C */	lwz r29, 0x2c(r31)
/* 80090280 0008CE60  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 80090284 0008CE64  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 80090288 0008CE68  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009028C 0008CE6C  40 81 00 10 */	ble lbl_8009029C
/* 80090290 0008CE70  C0 02 8A F8 */	lfs f0, lbl_804D84D8
/* 80090294 0008CE74  EC 01 00 28 */	fsubs f0, f1, f0
/* 80090298 0008CE78  D0 1D 23 40 */	stfs f0, 0x2340(r29)
lbl_8009029C:
/* 8009029C 0008CE7C  88 7D 22 1C */	lbz r3, 0x221c(r29)
/* 800902A0 0008CE80  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 800902A4 0008CE84  41 82 00 50 */	beq lbl_800902F4
/* 800902A8 0008CE88  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 800902AC 0008CE8C  C0 02 8A F4 */	lfs f0, lbl_804D84D4
/* 800902B0 0008CE90  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800902B4 0008CE94  4C 40 13 82 */	cror 2, 0, 2
/* 800902B8 0008CE98  40 82 00 3C */	bne lbl_800902F4
/* 800902BC 0008CE9C  38 00 00 00 */	li r0, 0
/* 800902C0 0008CEA0  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 800902C4 0008CEA4  98 7D 22 1C */	stb r3, 0x221c(r29)
/* 800902C8 0008CEA8  7F E3 FB 78 */	mr r3, r31
/* 800902CC 0008CEAC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800902D0 0008CEB0  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 800902D4 0008CEB4  B0 1D 20 98 */	sth r0, 0x2098(r29)
/* 800902D8 0008CEB8  4B FE F5 95 */	bl ftCommon_8007F86C
/* 800902DC 0008CEBC  7F E3 FB 78 */	mr r3, r31
/* 800902E0 0008CEC0  48 03 4F 61 */	bl ftCo_800C5240
/* 800902E4 0008CEC4  2C 03 00 00 */	cmpwi r3, 0
/* 800902E8 0008CEC8  41 82 00 0C */	beq lbl_800902F4
/* 800902EC 0008CECC  7F A3 EB 78 */	mr r3, r29
/* 800902F0 0008CED0  48 03 52 5D */	bl ftCo_800C554C
lbl_800902F4:
/* 800902F4 0008CED4  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 800902F8 0008CED8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800902FC 0008CEDC  40 82 00 0C */	bne lbl_80090308
/* 80090300 0008CEE0  7F E3 FB 78 */	mr r3, r31
/* 80090304 0008CEE4  48 00 04 7D */	bl ftCo_80090780
lbl_80090308:
/* 80090308 0008CEE8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8009030C 0008CEEC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80090310 0008CEF0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80090314 0008CEF4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80090318 0008CEF8  38 21 00 40 */	addi r1, r1, 0x40
/* 8009031C 0008CEFC  7C 08 03 A6 */	mtlr r0
/* 80090320 0008CF00  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_DamageFlyRoll_Anim(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _0[8] = { 0 };
#endif
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _1[0x18] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.damage.x8 != 0) {
        inlineD0(gobj);
    }
    ftCo_8008F744(gobj);
    if (!fp->x221C_b6) {
        ftCo_80090780(gobj);
    }
}
#endif

void ftCo_DamageFlyRoll_IASA(ftCo_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x221C_b6) {
        ftCo_DamageFall_IASA(gobj);
    } else {
        doIasa(gobj);
    }
}

void ftCo_DamageFlyRoll_Phys(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (!fp->x221C_b6) {
            ft_80084DB0(gobj);
        } else {
            ft_80084EEC(gobj);
        }
    } else {
        ft_80084F3C(gobj);
    }
    if (fp->motion_id == ftCo_MS_DamageFlyRoll) {
        doFlyRoll(gobj);
    }
    if (fp->x1064_thrownHitbox.owner != NULL) {
        if (sqrtf__Ff(VEC3_SQ_LEN(fp->x8c_kb_vel)) < p_ftCommonData->x1C8) {
            ftColl_8007AFF8(gobj);
        }
    }
    if (fp->motion_id == ftCo_MS_DamageFlyRoll) {
        doFlyRoll(gobj);
    }
}

void ftCo_DamageFlyRoll_Coll(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    CollData* coll = &GET_FIGHTER(gobj)->coll_data;
    if (ft_80081DD4(gobj)) {
        RETURN_IF(ftCo_80098928(gobj))
        RETURN_IF(ftCo_8009872C(gobj))
        ftCo_80097D40(gobj);
    } else {
        u32 env_flags = coll->env_flags;
        if (env_flags & MPCOLL_FLAGS_B11 || env_flags & MPCOLL_FLAGS_B05 ||
            env_flags & MPCOLL_FLAGS_B14)
        {
            RETURN_IF(ftCo_800C1D38(gobj))
            RETURN_IF(ftCo_800C23A0(gobj))
            ftCo_800C17CC(gobj);
        }
    }
}
