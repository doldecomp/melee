#include <platform.h>
#include "ft/forward.h"
#include "ftCaptain/forward.h"

#include "ftCa_SpecialHi.h"

#include "math.h"
#include "runtime.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include <common_structs.h>
#include <baselib/gobj.h>

float const ftCa_SpecialLw_804D9230 = 0;
float const ftCa_SpecialLw_804D9234 = 1;
double const ftCa_SpecialLw_804D9238 = M_PI_2;

void ftCa_SpecialHiThrow1_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void ftCa_SpecialLw_800E49FC(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E49FC 000E15DC  7C 08 02 A6 */	mflr r0
/* 800E4A00 000E15E0  90 01 00 04 */	stw r0, 4(r1)
/* 800E4A04 000E15E4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800E4A08 000E15E8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800E4A0C 000E15EC  3B E0 00 00 */	li r31, 0
/* 800E4A10 000E15F0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800E4A14 000E15F4  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800E4A18 000E15F8  80 1E 01 68 */	lwz r0, 0x168(r30)
/* 800E4A1C 000E15FC  80 7E 02 D4 */	lwz r3, 0x2d4(r30)
/* 800E4A20 000E1600  98 1E 19 68 */	stb r0, 0x1968(r30)
/* 800E4A24 000E1604  80 03 00 64 */	lwz r0, 0x64(r3)
/* 800E4A28 000E1608  B0 1E 23 40 */	sth r0, 0x2340(r30)
/* 800E4A2C 000E160C  93 FE 22 00 */	stw r31, 0x2200(r30)
/* 800E4A30 000E1610  C0 23 00 5C */	lfs f1, 0x5c(r3)
/* 800E4A34 000E1614  48 23 DE 8D */	bl __cvt_fp2unsigned
/* 800E4A38 000E1618  90 7E 22 04 */	stw r3, 0x2204(r30)
/* 800E4A3C 000E161C  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E4A40 000E1620  D0 1E 23 44 */	stfs f0, 0x2344(r30)
/* 800E4A44 000E1624  D0 1E 23 48 */	stfs f0, 0x2348(r30)
/* 800E4A48 000E1628  88 1E 23 42 */	lbz r0, 0x2342(r30)
/* 800E4A4C 000E162C  53 E0 3E 30 */	rlwimi r0, r31, 7, 0x18, 0x18
/* 800E4A50 000E1630  98 1E 23 42 */	stb r0, 0x2342(r30)
/* 800E4A54 000E1634  88 1E 23 42 */	lbz r0, 0x2342(r30)
/* 800E4A58 000E1638  53 E0 36 72 */	rlwimi r0, r31, 6, 0x19, 0x19
/* 800E4A5C 000E163C  98 1E 23 42 */	stb r0, 0x2342(r30)
/* 800E4A60 000E1640  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800E4A64 000E1644  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800E4A68 000E1648  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800E4A6C 000E164C  38 21 00 28 */	addi r1, r1, 0x28
/* 800E4A70 000E1650  7C 08 03 A6 */	mtlr r0
/* 800E4A74 000E1654  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void ftCa_SpecialLw_800E49FC(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    fp->mv.ca.specialhi.x0 = da->specialhi_air_var;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = da->specialhi_unk2;
    fp->mv.ca.specialhi.vel.x = 0;
    fp->mv.ca.specialhi.vel.y = 0;
    fp->mv.ca.specialhi.x2_b0 = false;
    fp->mv.ca.specialhi.x2_b1 = false;
}
#endif

static void ftCa_SpecialLw_800E5128(HSD_GObj*);

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialHi_Enter(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4A78 000E1658  7C 08 02 A6 */	mflr r0
/* 800E4A7C 000E165C  38 80 01 61 */	li r4, 0x161
/* 800E4A80 000E1660  90 01 00 04 */	stw r0, 4(r1)
/* 800E4A84 000E1664  38 A0 00 00 */	li r5, 0
/* 800E4A88 000E1668  38 C0 00 00 */	li r6, 0
/* 800E4A8C 000E166C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800E4A90 000E1670  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800E4A94 000E1674  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800E4A98 000E1678  3B C3 00 00 */	addi r30, r3, 0
/* 800E4A9C 000E167C  3C 60 80 0E */	lis r3, ftCa_SpecialLw_800E49FC@ha
/* 800E4AA0 000E1680  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800E4AA4 000E1684  38 03 49 FC */	addi r0, r3, ftCa_SpecialLw_800E49FC@l
/* 800E4AA8 000E1688  38 7E 00 00 */	addi r3, r30, 0
/* 800E4AAC 000E168C  90 1F 21 EC */	stw r0, 0x21ec(r31)
/* 800E4AB0 000E1690  C0 22 98 50 */	lfs f1, ftCa_SpecialLw_804D9230/*0*/
/* 800E4AB4 000E1694  C0 42 98 54 */	lfs f2, ftCa_SpecialLw_804D9234/*1*/
/* 800E4AB8 000E1698  FC 60 08 90 */	fmr f3, f1
/* 800E4ABC 000E169C  4B F8 48 F1 */	bl Fighter_ChangeMotionState
/* 800E4AC0 000E16A0  3C 80 80 0E */	lis r4, ftCa_SpecialLw_800E5128@ha
/* 800E4AC4 000E16A4  3C 60 80 0A */	lis r3, ft_8009CA0C@ha
/* 800E4AC8 000E16A8  38 A4 51 28 */	addi r5, r4, ftCa_SpecialLw_800E5128@l
/* 800E4ACC 000E16AC  38 E3 CA 0C */	addi r7, r3, ft_8009CA0C@l
/* 800E4AD0 000E16B0  38 7F 00 00 */	addi r3, r31, 0
/* 800E4AD4 000E16B4  38 80 00 02 */	li r4, 2
/* 800E4AD8 000E16B8  38 C0 00 00 */	li r6, 0
/* 800E4ADC 000E16BC  4B F9 97 F5 */	bl ftCommon_8007E2D0
/* 800E4AE0 000E16C0  7F C3 F3 78 */	mr r3, r30
/* 800E4AE4 000E16C4  4B F8 A0 C1 */	bl ftAnim_8006EBA4
/* 800E4AE8 000E16C8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800E4AEC 000E16CC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800E4AF0 000E16D0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800E4AF4 000E16D4  38 21 00 18 */	addi r1, r1, 0x18
/* 800E4AF8 000E16D8  7C 08 03 A6 */	mtlr r0
/* 800E4AFC 000E16DC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21EC_callback = ftCa_SpecialLw_800E49FC;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHi, Ft_MF_None, NULL, 0, 1,
                              0);
    ftCommon_8007E2D0(fp, 2, ftCa_SpecialLw_800E5128, NULL, ft_8009CA0C);
    ftAnim_8006EBA4(gobj);
}
#endif

void ftCa_SpecialHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* temp_r31 = fp->x2D4_specialAttributes;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_80096900(gobj, 1, 1, false,
                    temp_r31->specialhi_freefall_air_spd_mul,
                    temp_r31->specialhi_landing_lag);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialHi_IASA(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4B60 000E1740  7C 08 02 A6 */	mflr r0
/* 800E4B64 000E1744  90 01 00 04 */	stw r0, 4(r1)
/* 800E4B68 000E1748  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E4B6C 000E174C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E4B70 000E1750  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800E4B74 000E1754  80 03 22 00 */	lwz r0, 0x2200(r3)
/* 800E4B78 000E1758  3B E3 00 00 */	addi r31, r3, 0
/* 800E4B7C 000E175C  28 00 00 00 */	cmplwi r0, 0
/* 800E4B80 000E1760  41 82 00 64 */	beq lbl_800E4BE4
/* 800E4B84 000E1764  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 800E4B88 000E1768  38 00 00 00 */	li r0, 0
/* 800E4B8C 000E176C  38 60 00 01 */	li r3, 1
/* 800E4B90 000E1770  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 800E4B94 000E1774  88 1F 23 42 */	lbz r0, 0x2342(r31)
/* 800E4B98 000E1778  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 800E4B9C 000E177C  98 1F 23 42 */	stb r0, 0x2342(r31)
/* 800E4BA0 000E1780  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 800E4BA4 000E1784  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E4BA8 000E1788  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E4BAC 000E178C  40 80 00 08 */	bge lbl_800E4BB4
/* 800E4BB0 000E1790  FC 20 08 50 */	fneg f1, f1
lbl_800E4BB4:
/* 800E4BB4 000E1794  C0 04 00 58 */	lfs f0, 0x58(r4)
/* 800E4BB8 000E1798  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E4BBC 000E179C  40 81 00 28 */	ble lbl_800E4BE4
/* 800E4BC0 000E17A0  7F E3 FB 78 */	mr r3, r31
/* 800E4BC4 000E17A4  4B F9 8E 39 */	bl ftCommon_8007D9FC
/* 800E4BC8 000E17A8  C8 22 98 58 */	lfd f1, ftCa_SpecialLw_804D9238/*1.5707963267948966*/
/* 800E4BCC 000E17AC  7F E3 FB 78 */	mr r3, r31
/* 800E4BD0 000E17B0  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800E4BD4 000E17B4  38 80 00 00 */	li r4, 0
/* 800E4BD8 000E17B8  FC 21 00 32 */	fmul f1, f1, f0
/* 800E4BDC 000E17BC  FC 20 08 18 */	frsp f1, f1
/* 800E4BE0 000E17C0  4B F9 0F 11 */	bl ftParts_80075AF0
lbl_800E4BE4:
/* 800E4BE4 000E17C4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E4BE8 000E17C8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E4BEC 000E17CC  38 21 00 20 */	addi r1, r1, 0x20
/* 800E4BF0 000E17D0  7C 08 03 A6 */	mtlr r0
/* 800E4BF4 000E17D4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialHi_IASA(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0 != 0) {
        ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.ca.specialhi.x2_b1 = true;
        {
            f32 lstick_x = fp->input.x620_lstick_x;
            if (lstick_x < 0) {
                lstick_x = -lstick_x;
            }
            if (lstick_x > da->specialhi_input_var) {
                ftCommon_8007D9FC(fp);
                ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialHi_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4BF8 000E17D8  7C 08 02 A6 */	mflr r0
/* 800E4BFC 000E17DC  90 01 00 04 */	stw r0, 4(r1)
/* 800E4C00 000E17E0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800E4C04 000E17E4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800E4C08 000E17E8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800E4C0C 000E17EC  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800E4C10 000E17F0  93 81 00 18 */	stw r28, 0x18(r1)
/* 800E4C14 000E17F4  7C 7C 1B 78 */	mr r28, r3
/* 800E4C18 000E17F8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E4C1C 000E17FC  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 800E4C20 000E1800  3B BF 01 10 */	addi r29, r31, 0x110
/* 800E4C24 000E1804  C0 1F 23 44 */	lfs f0, 0x2344(r31)
/* 800E4C28 000E1808  7F E3 FB 78 */	mr r3, r31
/* 800E4C2C 000E180C  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800E4C30 000E1810  C0 1F 23 48 */	lfs f0, 0x2348(r31)
/* 800E4C34 000E1814  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800E4C38 000E1818  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E4C3C 000E181C  D0 1F 00 88 */	stfs f0, 0x88(r31)
/* 800E4C40 000E1820  C0 3E 00 44 */	lfs f1, 0x44(r30)
/* 800E4C44 000E1824  C0 1F 01 7C */	lfs f0, 0x17c(r31)
/* 800E4C48 000E1828  EC 21 00 32 */	fmuls f1, f1, f0
/* 800E4C4C 000E182C  4B F9 84 05 */	bl ftCommon_8007D050
/* 800E4C50 000E1830  2C 03 00 00 */	cmpwi r3, 0
/* 800E4C54 000E1834  40 82 00 2C */	bne lbl_800E4C80
/* 800E4C58 000E1838  C0 3D 00 64 */	lfs f1, 0x64(r29)
/* 800E4C5C 000E183C  7F E3 FB 78 */	mr r3, r31
/* 800E4C60 000E1840  C0 1E 00 40 */	lfs f0, 0x40(r30)
/* 800E4C64 000E1844  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800E4C68 000E1848  C0 7D 00 6C */	lfs f3, 0x6c(r29)
/* 800E4C6C 000E184C  EC 41 00 32 */	fmuls f2, f1, f0
/* 800E4C70 000E1850  C0 1E 00 44 */	lfs f0, 0x44(r30)
/* 800E4C74 000E1854  C0 24 02 58 */	lfs f1, 0x258(r4)
/* 800E4C78 000E1858  EC 63 00 32 */	fmuls f3, f3, f0
/* 800E4C7C 000E185C  4B F9 87 2D */	bl ftCommon_8007D3A8
lbl_800E4C80:
/* 800E4C80 000E1860  C0 3F 00 74 */	lfs f1, 0x74(r31)
/* 800E4C84 000E1864  7F 83 E3 78 */	mr r3, r28
/* 800E4C88 000E1868  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 800E4C8C 000E186C  EC 01 00 2A */	fadds f0, f1, f0
/* 800E4C90 000E1870  D0 1F 23 44 */	stfs f0, 0x2344(r31)
/* 800E4C94 000E1874  C0 3F 00 78 */	lfs f1, 0x78(r31)
/* 800E4C98 000E1878  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800E4C9C 000E187C  EC 01 00 2A */	fadds f0, f1, f0
/* 800E4CA0 000E1880  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 800E4CA4 000E1884  4B FA 04 91 */	bl ft_80085134
/* 800E4CA8 000E1888  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E4CAC 000E188C  D0 1F 00 78 */	stfs f0, 0x78(r31)
/* 800E4CB0 000E1890  D0 1F 00 74 */	stfs f0, 0x74(r31)
/* 800E4CB4 000E1894  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 800E4CB8 000E1898  C0 1F 23 44 */	lfs f0, 0x2344(r31)
/* 800E4CBC 000E189C  EC 01 00 2A */	fadds f0, f1, f0
/* 800E4CC0 000E18A0  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800E4CC4 000E18A4  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800E4CC8 000E18A8  C0 1F 23 48 */	lfs f0, 0x2348(r31)
/* 800E4CCC 000E18AC  EC 01 00 2A */	fadds f0, f1, f0
/* 800E4CD0 000E18B0  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800E4CD4 000E18B4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800E4CD8 000E18B8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800E4CDC 000E18BC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800E4CE0 000E18C0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800E4CE4 000E18C4  83 81 00 18 */	lwz r28, 0x18(r1)
/* 800E4CE8 000E18C8  38 21 00 28 */	addi r1, r1, 0x28
/* 800E4CEC 000E18CC  7C 08 03 A6 */	mtlr r0
/* 800E4CF0 000E18D0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialHi_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    attr* attr = &fp->x110_attr;
    fp->x80_self_vel.x = fp->mv.ca.specialhi.vel.x;
    fp->x80_self_vel.y = fp->mv.ca.specialhi.vel.y;
    fp->x80_self_vel.z = 0;
    if (!ftCommon_8007D050(fp, da->specialhi_horz_vel *
                                   fp->x110_attr.x17C_AerialDriftMax))
    {
        ftCommon_8007D3A8(fp, p_ftCommonData->x258,
                          attr->x174_AerialDriftStickMult *
                              da->specialhi_air_friction_mul,
                          attr->x17C_AerialDriftMax * da->specialhi_horz_vel);
    }
    fp->mv.ca.specialhi.vel.x = fp->x74_anim_vel.x + fp->x80_self_vel.x;
    fp->mv.ca.specialhi.vel.y = fp->x74_anim_vel.y + fp->x80_self_vel.y;
    ft_80085134(gobj);
    fp->x74_anim_vel.x = fp->x74_anim_vel.y = 0;
    fp->x80_self_vel.x = fp->x80_self_vel.x + fp->mv.ca.specialhi.vel.x;
    fp->x80_self_vel.y = fp->x80_self_vel.y + fp->mv.ca.specialhi.vel.y;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirHi_Enter(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4CF4 000E18D4  7C 08 02 A6 */	mflr r0
/* 800E4CF8 000E18D8  38 80 01 62 */	li r4, 0x162
/* 800E4CFC 000E18DC  90 01 00 04 */	stw r0, 4(r1)
/* 800E4D00 000E18E0  38 A0 00 00 */	li r5, 0
/* 800E4D04 000E18E4  38 C0 00 00 */	li r6, 0
/* 800E4D08 000E18E8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800E4D0C 000E18EC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800E4D10 000E18F0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800E4D14 000E18F4  3B C3 00 00 */	addi r30, r3, 0
/* 800E4D18 000E18F8  3C 60 80 0E */	lis r3, ftCa_SpecialLw_800E49FC@ha
/* 800E4D1C 000E18FC  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800E4D20 000E1900  38 03 49 FC */	addi r0, r3, ftCa_SpecialLw_800E49FC@l
/* 800E4D24 000E1904  38 7E 00 00 */	addi r3, r30, 0
/* 800E4D28 000E1908  90 1F 21 EC */	stw r0, 0x21ec(r31)
/* 800E4D2C 000E190C  C0 22 98 50 */	lfs f1, ftCa_SpecialLw_804D9230/*0*/
/* 800E4D30 000E1910  C0 42 98 54 */	lfs f2, ftCa_SpecialLw_804D9234/*1*/
/* 800E4D34 000E1914  FC 60 08 90 */	fmr f3, f1
/* 800E4D38 000E1918  4B F8 46 75 */	bl Fighter_ChangeMotionState
/* 800E4D3C 000E191C  3C 80 80 0E */	lis r4, ftCa_SpecialLw_800E5128@ha
/* 800E4D40 000E1920  3C 60 80 0A */	lis r3, ft_8009CA0C@ha
/* 800E4D44 000E1924  38 A4 51 28 */	addi r5, r4, ftCa_SpecialLw_800E5128@l
/* 800E4D48 000E1928  38 E3 CA 0C */	addi r7, r3, ft_8009CA0C@l
/* 800E4D4C 000E192C  38 7F 00 00 */	addi r3, r31, 0
/* 800E4D50 000E1930  38 80 00 02 */	li r4, 2
/* 800E4D54 000E1934  38 C0 00 00 */	li r6, 0
/* 800E4D58 000E1938  4B F9 95 79 */	bl ftCommon_8007E2D0
/* 800E4D5C 000E193C  7F C3 F3 78 */	mr r3, r30
/* 800E4D60 000E1940  4B F8 9E 45 */	bl ftAnim_8006EBA4
/* 800E4D64 000E1944  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800E4D68 000E1948  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800E4D6C 000E194C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800E4D70 000E1950  38 21 00 18 */	addi r1, r1, 0x18
/* 800E4D74 000E1954  7C 08 03 A6 */	mtlr r0
/* 800E4D78 000E1958  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21EC_callback = ftCa_SpecialLw_800E49FC;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirHi, Ft_MF_None, NULL, 0,
                              1, 0);
    ftCommon_8007E2D0(fp, 2, ftCa_SpecialLw_800E5128, NULL, ft_8009CA0C);
    ftAnim_8006EBA4(gobj);
}
#endif

static void doAirColl(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    if (ft_CheckGroundAndLedge(gobj, 0)) {
        if (fp->mv.ca.specialhi.x2_b1) {
            ft_800D5CB0(gobj, 0, da->specialhi_landing_lag);
        } else {
            ft_80083B68(gobj);
        }
    } else if (fp->mv.ca.specialhi.x2_b1 && ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

static void doCollAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    if (ft_CheckGroundAndLedge(gobj, 0)) {
        if (fp->mv.ca.specialhi.x2_b1) {
            ft_800D5CB0(gobj, 0, da->specialhi_landing_lag);
        } else {
            ft_80083B68(gobj);
        }
    } else if (fp->mv.ca.specialhi.x2_b1 && ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftCa_SpecialHi_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        doCollAir(gobj);
    } else if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
    }
}

void ftCa_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif
    ftCaptain_DatAttrs* da = GET_FIGHTER(gobj)->x2D4_specialAttributes;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_80096900(gobj, 1, 1, false, da->specialhi_freefall_air_spd_mul,
                    da->specialhi_landing_lag);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirHi_IASA(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4F48 000E1B28  7C 08 02 A6 */	mflr r0
/* 800E4F4C 000E1B2C  90 01 00 04 */	stw r0, 4(r1)
/* 800E4F50 000E1B30  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800E4F54 000E1B34  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800E4F58 000E1B38  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E4F5C 000E1B3C  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 800E4F60 000E1B40  28 00 00 00 */	cmplwi r0, 0
/* 800E4F64 000E1B44  41 82 00 64 */	beq lbl_800E4FC8
/* 800E4F68 000E1B48  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 800E4F6C 000E1B4C  38 00 00 00 */	li r0, 0
/* 800E4F70 000E1B50  38 60 00 01 */	li r3, 1
/* 800E4F74 000E1B54  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 800E4F78 000E1B58  88 1F 23 42 */	lbz r0, 0x2342(r31)
/* 800E4F7C 000E1B5C  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 800E4F80 000E1B60  98 1F 23 42 */	stb r0, 0x2342(r31)
/* 800E4F84 000E1B64  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 800E4F88 000E1B68  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E4F8C 000E1B6C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E4F90 000E1B70  40 80 00 08 */	bge lbl_800E4F98
/* 800E4F94 000E1B74  FC 20 08 50 */	fneg f1, f1
lbl_800E4F98:
/* 800E4F98 000E1B78  C0 04 00 58 */	lfs f0, 0x58(r4)
/* 800E4F9C 000E1B7C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E4FA0 000E1B80  40 81 00 28 */	ble lbl_800E4FC8
/* 800E4FA4 000E1B84  7F E3 FB 78 */	mr r3, r31
/* 800E4FA8 000E1B88  4B F9 8A 55 */	bl ftCommon_8007D9FC
/* 800E4FAC 000E1B8C  C8 22 98 58 */	lfd f1, ftCa_SpecialLw_804D9238/*1.5707963267948966*/
/* 800E4FB0 000E1B90  7F E3 FB 78 */	mr r3, r31
/* 800E4FB4 000E1B94  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800E4FB8 000E1B98  38 80 00 00 */	li r4, 0
/* 800E4FBC 000E1B9C  FC 21 00 32 */	fmul f1, f1, f0
/* 800E4FC0 000E1BA0  FC 20 08 18 */	frsp f1, f1
/* 800E4FC4 000E1BA4  4B F9 0B 2D */	bl ftParts_80075AF0
lbl_800E4FC8:
/* 800E4FC8 000E1BA8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800E4FCC 000E1BAC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800E4FD0 000E1BB0  38 21 00 28 */	addi r1, r1, 0x28
/* 800E4FD4 000E1BB4  7C 08 03 A6 */	mtlr r0
/* 800E4FD8 000E1BB8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void doAirIASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.ca.specialhi.x2_b1 = true;
    {
        float lstick_x = fp->input.x620_lstick_x;
        if (lstick_x < 0) {
            lstick_x = -lstick_x;
        }
        if (lstick_x > da->specialhi_input_var) {
            ftCommon_8007D9FC(fp);
            ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
        }
    }
}
void ftCa_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    if (temp_r31->x2200_ftcmd_var0) {
        doAirIASA(gobj);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirHi_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E4FDC 000E1BBC  7C 08 02 A6 */	mflr r0
/* 800E4FE0 000E1BC0  90 01 00 04 */	stw r0, 4(r1)
/* 800E4FE4 000E1BC4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800E4FE8 000E1BC8  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800E4FEC 000E1BCC  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800E4FF0 000E1BD0  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800E4FF4 000E1BD4  93 81 00 30 */	stw r28, 0x30(r1)
/* 800E4FF8 000E1BD8  7C 7C 1B 78 */	mr r28, r3
/* 800E4FFC 000E1BDC  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 800E5000 000E1BE0  83 DD 02 D4 */	lwz r30, 0x2d4(r29)
/* 800E5004 000E1BE4  3B FD 01 10 */	addi r31, r29, 0x110
/* 800E5008 000E1BE8  C0 1D 23 44 */	lfs f0, 0x2344(r29)
/* 800E500C 000E1BEC  7F A3 EB 78 */	mr r3, r29
/* 800E5010 000E1BF0  D0 1D 00 80 */	stfs f0, 0x80(r29)
/* 800E5014 000E1BF4  C0 1D 23 48 */	lfs f0, 0x2348(r29)
/* 800E5018 000E1BF8  D0 1D 00 84 */	stfs f0, 0x84(r29)
/* 800E501C 000E1BFC  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E5020 000E1C00  D0 1D 00 88 */	stfs f0, 0x88(r29)
/* 800E5024 000E1C04  C0 3E 00 44 */	lfs f1, 0x44(r30)
/* 800E5028 000E1C08  C0 1D 01 7C */	lfs f0, 0x17c(r29)
/* 800E502C 000E1C0C  EC 21 00 32 */	fmuls f1, f1, f0
/* 800E5030 000E1C10  4B F9 80 21 */	bl ftCommon_8007D050
/* 800E5034 000E1C14  2C 03 00 00 */	cmpwi r3, 0
/* 800E5038 000E1C18  40 82 00 2C */	bne lbl_800E5064
/* 800E503C 000E1C1C  C0 3F 00 64 */	lfs f1, 0x64(r31)
/* 800E5040 000E1C20  7F A3 EB 78 */	mr r3, r29
/* 800E5044 000E1C24  C0 1E 00 40 */	lfs f0, 0x40(r30)
/* 800E5048 000E1C28  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800E504C 000E1C2C  C0 7F 00 6C */	lfs f3, 0x6c(r31)
/* 800E5050 000E1C30  EC 41 00 32 */	fmuls f2, f1, f0
/* 800E5054 000E1C34  C0 1E 00 44 */	lfs f0, 0x44(r30)
/* 800E5058 000E1C38  C0 24 02 58 */	lfs f1, 0x258(r4)
/* 800E505C 000E1C3C  EC 63 00 32 */	fmuls f3, f3, f0
/* 800E5060 000E1C40  4B F9 83 49 */	bl ftCommon_8007D3A8
lbl_800E5064:
/* 800E5064 000E1C44  C0 3D 00 74 */	lfs f1, 0x74(r29)
/* 800E5068 000E1C48  7F 83 E3 78 */	mr r3, r28
/* 800E506C 000E1C4C  C0 1D 00 80 */	lfs f0, 0x80(r29)
/* 800E5070 000E1C50  EC 01 00 2A */	fadds f0, f1, f0
/* 800E5074 000E1C54  D0 1D 23 44 */	stfs f0, 0x2344(r29)
/* 800E5078 000E1C58  C0 3D 00 78 */	lfs f1, 0x78(r29)
/* 800E507C 000E1C5C  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 800E5080 000E1C60  EC 01 00 2A */	fadds f0, f1, f0
/* 800E5084 000E1C64  D0 1D 23 48 */	stfs f0, 0x2348(r29)
/* 800E5088 000E1C68  4B FA 00 AD */	bl ft_80085134
/* 800E508C 000E1C6C  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E5090 000E1C70  D0 1D 00 78 */	stfs f0, 0x78(r29)
/* 800E5094 000E1C74  D0 1D 00 74 */	stfs f0, 0x74(r29)
/* 800E5098 000E1C78  C0 3D 00 80 */	lfs f1, 0x80(r29)
/* 800E509C 000E1C7C  C0 1D 23 44 */	lfs f0, 0x2344(r29)
/* 800E50A0 000E1C80  EC 01 00 2A */	fadds f0, f1, f0
/* 800E50A4 000E1C84  D0 1D 00 80 */	stfs f0, 0x80(r29)
/* 800E50A8 000E1C88  C0 3D 00 84 */	lfs f1, 0x84(r29)
/* 800E50AC 000E1C8C  C0 1D 23 48 */	lfs f0, 0x2348(r29)
/* 800E50B0 000E1C90  EC 01 00 2A */	fadds f0, f1, f0
/* 800E50B4 000E1C94  D0 1D 00 84 */	stfs f0, 0x84(r29)
/* 800E50B8 000E1C98  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800E50BC 000E1C9C  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800E50C0 000E1CA0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800E50C4 000E1CA4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800E50C8 000E1CA8  83 81 00 30 */	lwz r28, 0x30(r1)
/* 800E50CC 000E1CAC  38 21 00 40 */	addi r1, r1, 0x40
/* 800E50D0 000E1CB0  7C 08 03 A6 */	mtlr r0
/* 800E50D4 000E1CB4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    attr* attr = &fp->x110_attr;
    fp->x80_self_vel.x = fp->mv.ca.specialhi.vel.x;
    fp->x80_self_vel.y = fp->mv.ca.specialhi.vel.y;
    fp->x80_self_vel.z = 0;
    if (!ftCommon_8007D050(fp,
                           da->specialhi_horz_vel * attr->x17C_AerialDriftMax))
    {
        ftCommon_8007D3A8(fp, p_ftCommonData->x258,
                          attr->x174_AerialDriftStickMult *
                              da->specialhi_air_friction_mul,
                          attr->x17C_AerialDriftMax * da->specialhi_horz_vel);
    }
    fp->mv.ca.specialhi.vel.x = fp->x74_anim_vel.x + fp->x80_self_vel.x;
    fp->mv.ca.specialhi.vel.y = fp->x74_anim_vel.y + fp->x80_self_vel.y;
    ft_80085134(gobj);
    fp->x74_anim_vel.x = fp->x74_anim_vel.y = 0;
    fp->x80_self_vel.x = fp->x80_self_vel.x + fp->mv.ca.specialhi.vel.x;
    fp->x80_self_vel.y = fp->x80_self_vel.y + fp->mv.ca.specialhi.vel.y;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialAirHi_Coll(HSD_GObj*)
{
    // clang-format off
    nofralloc
/* 800E50D8 000E1CB8  7C 08 02 A6 */	mflr r0
/* 800E50DC 000E1CBC  90 01 00 04 */	stw r0, 4(r1)
/* 800E50E0 000E1CC0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800E50E4 000E1CC4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800E50E8 000E1CC8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E50EC 000E1CCC  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 800E50F0 000E1CD0  2C 00 00 01 */	cmpwi r0, 1
/* 800E50F4 000E1CD4  40 82 00 0C */	bne lbl_800E5100
/* 800E50F8 000E1CD8  4B FF FC 85 */	bl doAirColl
/* 800E50FC 000E1CDC  48 00 00 18 */	b lbl_800E5114
lbl_800E5100:
/* 800E5100 000E1CE0  4B F9 D6 09 */	bl ft_80082708
/* 800E5104 000E1CE4  2C 03 00 00 */	cmpwi r3, 0
/* 800E5108 000E1CE8  40 82 00 0C */	bne lbl_800E5114
/* 800E510C 000E1CEC  7F E3 FB 78 */	mr r3, r31
/* 800E5110 000E1CF0  4B F9 84 C5 */	bl ftCommon_8007D5D4
lbl_800E5114:
/* 800E5114 000E1CF4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800E5118 000E1CF8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800E511C 000E1CFC  38 21 00 18 */	addi r1, r1, 0x18
/* 800E5120 000E1D00  7C 08 03 A6 */	mtlr r0
/* 800E5124 000E1D04  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        doAirColl(gobj);
    } else if (ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
    }
}
#endif

static void ftCa_SpecialLw_800E550C(HSD_GObj*);

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void ftCa_SpecialLw_800E5128(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E5128 000E1D08  7C 08 02 A6 */	mflr r0
/* 800E512C 000E1D0C  38 80 01 63 */	li r4, 0x163
/* 800E5130 000E1D10  90 01 00 04 */	stw r0, 4(r1)
/* 800E5134 000E1D14  38 C0 00 00 */	li r6, 0
/* 800E5138 000E1D18  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800E513C 000E1D1C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800E5140 000E1D20  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800E5144 000E1D24  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800E5148 000E1D28  93 81 00 18 */	stw r28, 0x18(r1)
/* 800E514C 000E1D2C  7C 7C 1B 78 */	mr r28, r3
/* 800E5150 000E1D30  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 800E5154 000E1D34  C0 22 98 50 */	lfs f1, ftCa_SpecialLw_804D9230/*0*/
/* 800E5158 000E1D38  80 BD 1A 58 */	lwz r5, 0x1a58(r29)
/* 800E515C 000E1D3C  FC 60 08 90 */	fmr f3, f1
/* 800E5160 000E1D40  C0 42 98 54 */	lfs f2, ftCa_SpecialLw_804D9234/*1*/
/* 800E5164 000E1D44  83 C5 00 2C */	lwz r30, 0x2c(r5)
/* 800E5168 000E1D48  38 A0 00 02 */	li r5, 2
/* 800E516C 000E1D4C  4B F8 42 41 */	bl Fighter_ChangeMotionState
/* 800E5170 000E1D50  88 1D 22 22 */	lbz r0, 0x2222(r29)
/* 800E5174 000E1D54  3B E0 00 01 */	li r31, 1
/* 800E5178 000E1D58  53 E0 2E B4 */	rlwimi r0, r31, 5, 0x1a, 0x1a
/* 800E517C 000E1D5C  98 1D 22 22 */	stb r0, 0x2222(r29)
/* 800E5180 000E1D60  38 7D 00 00 */	addi r3, r29, 0
/* 800E5184 000E1D64  38 80 01 FF */	li r4, 0x1ff
/* 800E5188 000E1D68  4B F9 91 6D */	bl ftCommon_8007E2F4
/* 800E518C 000E1D6C  7F 83 E3 78 */	mr r3, r28
/* 800E5190 000E1D70  4B F9 91 6D */	bl ftCommon_8007E2FC
/* 800E5194 000E1D74  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 800E5198 000E1D78  2C 00 00 01 */	cmpwi r0, 1
/* 800E519C 000E1D7C  40 82 00 18 */	bne lbl_800E51B4
/* 800E51A0 000E1D80  88 1D 22 1B */	lbz r0, 0x221b(r29)
/* 800E51A4 000E1D84  38 60 00 00 */	li r3, 0
/* 800E51A8 000E1D88  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 800E51AC 000E1D8C  98 1D 22 1B */	stb r0, 0x221b(r29)
/* 800E51B0 000E1D90  48 00 00 28 */	b lbl_800E51D8
lbl_800E51B4:
/* 800E51B4 000E1D94  38 7E 00 00 */	addi r3, r30, 0
/* 800E51B8 000E1D98  38 9D 00 00 */	addi r4, r29, 0
/* 800E51BC 000E1D9C  4B FF 61 AD */	bl ft_800DB368
/* 800E51C0 000E1DA0  88 1D 22 1B */	lbz r0, 0x221b(r29)
/* 800E51C4 000E1DA4  53 E0 07 FE */	rlwimi r0, r31, 0, 0x1f, 0x1f
/* 800E51C8 000E1DA8  3C 60 80 0E */	lis r3, ftCa_SpecialLw_800E550C@ha
/* 800E51CC 000E1DAC  98 1D 22 1B */	stb r0, 0x221b(r29)
/* 800E51D0 000E1DB0  38 03 55 0C */	addi r0, r3, ftCa_SpecialLw_800E550C@l
/* 800E51D4 000E1DB4  90 1D 21 BC */	stw r0, 0x21bc(r29)
lbl_800E51D8:
/* 800E51D8 000E1DB8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800E51DC 000E1DBC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800E51E0 000E1DC0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800E51E4 000E1DC4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800E51E8 000E1DC8  83 81 00 18 */	lwz r28, 0x18(r1)
/* 800E51EC 000E1DCC  38 21 00 28 */	addi r1, r1, 0x28
/* 800E51F0 000E1DD0  7C 08 03 A6 */	mtlr r0
/* 800E51F4 000E1DD4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialLw_800E5128(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* vic_fp = GET_FIGHTER(fp->x1A58_interactedFighter);
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiCatch, 2, NULL, 0, 1, 0);
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    if (vic_fp->ground_or_air == GA_Air) {
        fp->x221B_b7 = false;
    } else {
        ft_800DB368(vic_fp, fp);
        fp->x221B_b7 = true;
        fp->cb.x21BC_callback_Accessory4 = ftCa_SpecialLw_800E550C;
    }
}
#endif

static void doCatchAnim(HSD_GObj* gobj);

void ftCa_SpecialHiCatch_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        doCatchAnim(gobj);
    }
}

void ftCa_SpecialHiCatch_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialHiCatch_Phys(HSD_GObj* gobj) {}

void ftCa_SpecialHiCatch_Coll(HSD_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x221B_b7) {
        ft_80083B68(gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void doCatchAnim(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E526C 000E1E4C  7C 08 02 A6 */	mflr r0
/* 800E5270 000E1E50  3C 80 00 08 */	lis r4, 0x00080002@ha
/* 800E5274 000E1E54  90 01 00 04 */	stw r0, 4(r1)
/* 800E5278 000E1E58  38 A4 00 02 */	addi r5, r4, 0x00080002@l
/* 800E527C 000E1E5C  38 E0 00 00 */	li r7, 0
/* 800E5280 000E1E60  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E5284 000E1E64  38 80 01 64 */	li r4, 0x164
/* 800E5288 000E1E68  38 C0 00 00 */	li r6, 0
/* 800E528C 000E1E6C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E5290 000E1E70  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800E5294 000E1E74  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800E5298 000E1E78  7C 7D 1B 78 */	mr r29, r3
/* 800E529C 000E1E7C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E52A0 000E1E80  83 DF 1A 58 */	lwz r30, 0x1a58(r31)
/* 800E52A4 000E1E84  90 FF 22 00 */	stw r7, 0x2200(r31)
/* 800E52A8 000E1E88  88 1F 23 42 */	lbz r0, 0x2342(r31)
/* 800E52AC 000E1E8C  50 E0 3E 30 */	rlwimi r0, r7, 7, 0x18, 0x18
/* 800E52B0 000E1E90  98 1F 23 42 */	stb r0, 0x2342(r31)
/* 800E52B4 000E1E94  C0 22 98 50 */	lfs f1, ftCa_SpecialLw_804D9230/*0*/
/* 800E52B8 000E1E98  D0 3F 23 44 */	stfs f1, 0x2344(r31)
/* 800E52BC 000E1E9C  FC 60 08 90 */	fmr f3, f1
/* 800E52C0 000E1EA0  D0 3F 23 48 */	stfs f1, 0x2348(r31)
/* 800E52C4 000E1EA4  C0 42 98 54 */	lfs f2, ftCa_SpecialLw_804D9234/*1*/
/* 800E52C8 000E1EA8  4B F8 40 E5 */	bl Fighter_ChangeMotionState
/* 800E52CC 000E1EAC  38 7F 00 00 */	addi r3, r31, 0
/* 800E52D0 000E1EB0  38 80 00 00 */	li r4, 0
/* 800E52D4 000E1EB4  4B F9 90 21 */	bl ftCommon_8007E2F4
/* 800E52D8 000E1EB8  38 7D 00 00 */	addi r3, r29, 0
/* 800E52DC 000E1EBC  38 9E 00 00 */	addi r4, r30, 0
/* 800E52E0 000E1EC0  4B FF 8F C9 */	bl ft_800DE2A8
/* 800E52E4 000E1EC4  38 7E 00 00 */	addi r3, r30, 0
/* 800E52E8 000E1EC8  38 80 00 00 */	li r4, 0
/* 800E52EC 000E1ECC  38 A0 00 00 */	li r5, 0
/* 800E52F0 000E1ED0  4B FF 94 D1 */	bl ft_800DE7C0
/* 800E52F4 000E1ED4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E52F8 000E1ED8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E52FC 000E1EDC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800E5300 000E1EE0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800E5304 000E1EE4  38 21 00 20 */	addi r1, r1, 0x20
/* 800E5308 000E1EE8  7C 08 03 A6 */	mtlr r0
/* 800E530C 000E1EEC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void doCatchAnim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* vic_gobj = fp->x1A58_interactedFighter;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.ca.specialhi.x2_b0 = false;
    fp->mv.ca.specialhi.vel.x = 0;
    fp->mv.ca.specialhi.vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiThrow,
                              Ft_MF_Unk19 | Ft_MF_KeepGfx, NULL, 0, 1, 0);
    ftCommon_8007E2F4(fp, 0);
    ft_800DE2A8(gobj, vic_gobj);
    ft_800DE7C0(vic_gobj, 0, 0);
}
#endif

void ftCa_SpecialHiThrow0_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
    ftCommon_8007D60C(fp);
    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.ca.specialhi.x2_b0 = true;
    }
}

void ftCa_SpecialHiThrow0_IASA(HSD_GObj* gobj) {}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCa_SpecialHiThrow0_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800E5388 000E1F68  7C 08 02 A6 */	mflr r0
/* 800E538C 000E1F6C  90 01 00 04 */	stw r0, 4(r1)
/* 800E5390 000E1F70  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800E5394 000E1F74  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 800E5398 000E1F78  BF 61 00 3C */	stmw r27, 0x3c(r1)
/* 800E539C 000E1F7C  7C 7B 1B 78 */	mr r27, r3
/* 800E53A0 000E1F80  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800E53A4 000E1F84  88 1E 23 42 */	lbz r0, 0x2342(r30)
/* 800E53A8 000E1F88  7F DD F3 78 */	mr r29, r30
/* 800E53AC 000E1F8C  83 9E 02 D4 */	lwz r28, 0x2d4(r30)
/* 800E53B0 000E1F90  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800E53B4 000E1F94  41 82 00 E4 */	beq lbl_800E5498
/* 800E53B8 000E1F98  C0 1E 23 44 */	lfs f0, 0x2344(r30)
/* 800E53BC 000E1F9C  3B FE 01 10 */	addi r31, r30, 0x110
/* 800E53C0 000E1FA0  38 7E 00 00 */	addi r3, r30, 0
/* 800E53C4 000E1FA4  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 800E53C8 000E1FA8  C0 1E 23 48 */	lfs f0, 0x2348(r30)
/* 800E53CC 000E1FAC  D0 1E 00 84 */	stfs f0, 0x84(r30)
/* 800E53D0 000E1FB0  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E53D4 000E1FB4  D0 1E 00 88 */	stfs f0, 0x88(r30)
/* 800E53D8 000E1FB8  C0 3C 00 44 */	lfs f1, 0x44(r28)
/* 800E53DC 000E1FBC  C0 1E 01 7C */	lfs f0, 0x17c(r30)
/* 800E53E0 000E1FC0  EC 21 00 32 */	fmuls f1, f1, f0
/* 800E53E4 000E1FC4  4B F9 7C 6D */	bl ftCommon_8007D050
/* 800E53E8 000E1FC8  2C 03 00 00 */	cmpwi r3, 0
/* 800E53EC 000E1FCC  40 82 00 2C */	bne lbl_800E5418
/* 800E53F0 000E1FD0  C0 3F 00 64 */	lfs f1, 0x64(r31)
/* 800E53F4 000E1FD4  7F C3 F3 78 */	mr r3, r30
/* 800E53F8 000E1FD8  C0 1C 00 40 */	lfs f0, 0x40(r28)
/* 800E53FC 000E1FDC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800E5400 000E1FE0  C0 7F 00 6C */	lfs f3, 0x6c(r31)
/* 800E5404 000E1FE4  EC 41 00 32 */	fmuls f2, f1, f0
/* 800E5408 000E1FE8  C0 1C 00 44 */	lfs f0, 0x44(r28)
/* 800E540C 000E1FEC  C0 24 02 58 */	lfs f1, 0x258(r4)
/* 800E5410 000E1FF0  EC 63 00 32 */	fmuls f3, f3, f0
/* 800E5414 000E1FF4  4B F9 7F 95 */	bl ftCommon_8007D3A8
lbl_800E5418:
/* 800E5418 000E1FF8  C0 3E 00 74 */	lfs f1, 0x74(r30)
/* 800E541C 000E1FFC  7F 63 DB 78 */	mr r3, r27
/* 800E5420 000E2000  C0 1E 00 80 */	lfs f0, 0x80(r30)
/* 800E5424 000E2004  EC 01 00 2A */	fadds f0, f1, f0
/* 800E5428 000E2008  D0 1E 23 44 */	stfs f0, 0x2344(r30)
/* 800E542C 000E200C  C0 3E 00 78 */	lfs f1, 0x78(r30)
/* 800E5430 000E2010  C0 1E 00 84 */	lfs f0, 0x84(r30)
/* 800E5434 000E2014  EC 01 00 2A */	fadds f0, f1, f0
/* 800E5438 000E2018  D0 1E 23 48 */	stfs f0, 0x2348(r30)
/* 800E543C 000E201C  4B F9 FC F9 */	bl ft_80085134
/* 800E5440 000E2020  C0 02 98 50 */	lfs f0, ftCa_SpecialLw_804D9230/*0*/
/* 800E5444 000E2024  7F A3 EB 78 */	mr r3, r29
/* 800E5448 000E2028  D0 1E 00 78 */	stfs f0, 0x78(r30)
/* 800E544C 000E202C  D0 1E 00 74 */	stfs f0, 0x74(r30)
/* 800E5450 000E2030  C0 3E 00 80 */	lfs f1, 0x80(r30)
/* 800E5454 000E2034  C0 1E 23 44 */	lfs f0, 0x2344(r30)
/* 800E5458 000E2038  EC 01 00 2A */	fadds f0, f1, f0
/* 800E545C 000E203C  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 800E5460 000E2040  C0 3E 00 84 */	lfs f1, 0x84(r30)
/* 800E5464 000E2044  C0 1E 23 48 */	lfs f0, 0x2348(r30)
/* 800E5468 000E2048  EC 01 00 2A */	fadds f0, f1, f0
/* 800E546C 000E204C  D0 1E 00 84 */	stfs f0, 0x84(r30)
/* 800E5470 000E2050  C0 5D 00 84 */	lfs f2, 0x84(r29)
/* 800E5474 000E2054  C0 1D 23 48 */	lfs f0, 0x2348(r29)
/* 800E5478 000E2058  C0 3C 00 60 */	lfs f1, 0x60(r28)
/* 800E547C 000E205C  EF E2 00 28 */	fsubs f31, f2, f0
/* 800E5480 000E2060  C0 5D 01 70 */	lfs f2, 0x170(r29)
/* 800E5484 000E2064  4B F9 80 11 */	bl ftCommon_8007D494
/* 800E5488 000E2068  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 800E548C 000E206C  EC 00 F8 28 */	fsubs f0, f0, f31
/* 800E5490 000E2070  D0 1D 23 48 */	stfs f0, 0x2348(r29)
/* 800E5494 000E2074  48 00 00 0C */	b lbl_800E54A0
lbl_800E5498:
/* 800E5498 000E2078  7F 63 DB 78 */	mr r3, r27
/* 800E549C 000E207C  4B F9 FC 99 */	bl ft_80085134
lbl_800E54A0:
/* 800E54A0 000E2080  BB 61 00 3C */	lmw r27, 0x3c(r1)
/* 800E54A4 000E2084  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800E54A8 000E2088  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 800E54AC 000E208C  38 21 00 58 */	addi r1, r1, 0x58
/* 800E54B0 000E2090  7C 08 03 A6 */	mtlr r0
/* 800E54B4 000E2094  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCa_SpecialHiThrow0_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    if (fp->mv.ca.specialhi.x2_b2) {
        attr* attr = &fp->x110_attr;
        fp->x80_self_vel.x = fp->mv.ca.specialhi.vel.x;
        fp->x80_self_vel.y = fp->mv.ca.specialhi.vel.y;
        fp->x80_self_vel.z = 0;
        if (!ftCommon_8007D050(fp, da->specialhi_horz_vel *
                                       attr->x17C_AerialDriftMax))
        {
            ftCommon_8007D3A8(fp, p_ftCommonData->x258,
                              attr->x174_AerialDriftStickMult *
                                  da->specialhi_air_friction_mul,
                              attr->x17C_AerialDriftMax *
                                  da->specialhi_horz_vel);
        }
        fp->mv.ca.specialhi.vel.x = fp->x74_anim_vel.x + fp->x80_self_vel.x;
        fp->mv.ca.specialhi.vel.y = fp->x74_anim_vel.y + fp->x80_self_vel.y;
        ft_80085134(gobj);
        fp->x74_anim_vel.x = fp->x74_anim_vel.y = 0;
        fp->x80_self_vel.x = fp->x80_self_vel.x + fp->mv.ca.specialhi.vel.x;
        fp->x80_self_vel.y = fp->x80_self_vel.y + fp->mv.ca.specialhi.vel.y;
        {
            float vel_y = fp->x80_self_vel.y - fp->mv.ca.specialhi.vel.y;
            ftCommon_8007D494(fp, da->specialhi_catch_grav,
                              attr->x170_TerminalVelocity);
            fp->mv.ca.specialhi.vel.y = fp->x80_self_vel.y - vel_y;
        }
    } else {
        ft_80085134(gobj);
    }
}
#endif

void ftCa_SpecialHiThrow0_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->x2D4_specialAttributes;
    if (ft_80081D0C(gobj)) {
        ft_800D5CB0(gobj, 0, da->specialhi_landing_lag);
    }
}

static void ftCa_SpecialLw_800E550C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* vic_fp = GET_FIGHTER(fp->x1A58_interactedFighter);
    fp->cur_pos = vic_fp->cur_pos;
}
