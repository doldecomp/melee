#include <platform.h>
#include "ftCommon/forward.h"

#include "ftCo_DamageFall.h"

#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_DamageIce.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_HammerFall.h"
#include "ftCo_HammerWait.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialAir.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

void ftCo_80090574(ftCo_GObj* gobj)
{
    ft_80081DD4(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80090594(ftCo_Fighter*, enum_t, int, FtMotionId, enum_t, float)
{ // clang-format off
    nofralloc
/* 80090594 0008D174  7C 08 02 A6 */	mflr r0
/* 80090598 0008D178  90 01 00 04 */	stw r0, 4(r1)
/* 8009059C 0008D17C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800905A0 0008D180  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800905A4 0008D184  3B E3 00 00 */	addi r31, r3, 0
/* 800905A8 0008D188  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800905AC 0008D18C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800905B0 0008D190  3B A7 00 00 */	addi r29, r7, 0
/* 800905B4 0008D194  93 81 00 30 */	stw r28, 0x30(r1)
/* 800905B8 0008D198  3B 84 00 00 */	addi r28, r4, 0
/* 800905BC 0008D19C  2C 1C 00 0A */	cmpwi r28, 0xa
/* 800905C0 0008D1A0  41 82 00 B0 */	beq lbl_80090670
/* 800905C4 0008D1A4  2C 1C 00 0C */	cmpwi r28, 0xc
/* 800905C8 0008D1A8  41 82 00 A8 */	beq lbl_80090670
/* 800905CC 0008D1AC  38 1C FF FA */	addi r0, r28, -6
/* 800905D0 0008D1B0  28 00 00 01 */	cmplwi r0, 1
/* 800905D4 0008D1B4  41 81 00 08 */	bgt lbl_800905DC
/* 800905D8 0008D1B8  48 00 00 98 */	b lbl_80090670
lbl_800905DC:
/* 800905DC 0008D1BC  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800905E0 0008D1C0  2C 00 01 45 */	cmpwi r0, 0x145
/* 800905E4 0008D1C4  41 82 00 8C */	beq lbl_80090670
/* 800905E8 0008D1C8  83 CD AE B4 */	lwz r30, p_ftCommonData
/* 800905EC 0008D1CC  38 65 00 00 */	addi r3, r5, 0
/* 800905F0 0008D1D0  38 86 00 00 */	addi r4, r6, 0
/* 800905F4 0008D1D4  4B FE D4 81 */	bl ftCommon_CalcHitlag
/* 800905F8 0008D1D8  C0 5E 01 68 */	lfs f2, 0x168(r30)
/* 800905FC 0008D1DC  2C 1C 00 02 */	cmpwi r28, 2
/* 80090600 0008D1E0  C0 1E 01 6C */	lfs f0, 0x16c(r30)
/* 80090604 0008D1E4  38 00 00 00 */	li r0, 0
/* 80090608 0008D1E8  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8009060C 0008D1EC  FC 00 00 1E */	fctiwz f0, f0
/* 80090610 0008D1F0  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 80090614 0008D1F4  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80090618 0008D1F8  B0 7F 18 FA */	sth r3, 0x18fa(r31)
/* 8009061C 0008D1FC  98 1F 18 FC */	stb r0, 0x18fc(r31)
/* 80090620 0008D200  40 82 00 10 */	bne lbl_80090630
/* 80090624 0008D204  38 00 00 02 */	li r0, 2
/* 80090628 0008D208  98 1F 18 F8 */	stb r0, 0x18f8(r31)
/* 8009062C 0008D20C  48 00 00 2C */	b lbl_80090658
lbl_80090630:
/* 80090630 0008D210  2C 1D 00 01 */	cmpwi r29, 1
/* 80090634 0008D214  40 82 00 0C */	bne lbl_80090640
/* 80090638 0008D218  98 1F 18 F8 */	stb r0, 0x18f8(r31)
/* 8009063C 0008D21C  48 00 00 1C */	b lbl_80090658
lbl_80090640:
/* 80090640 0008D220  38 00 00 01 */	li r0, 1
/* 80090644 0008D224  98 1F 18 F8 */	stb r0, 0x18f8(r31)
/* 80090648 0008D228  C0 1F 08 44 */	lfs f0, 0x844(r31)
/* 8009064C 0008D22C  D0 1F 19 00 */	stfs f0, 0x1900(r31)
/* 80090650 0008D230  C0 1F 08 48 */	lfs f0, 0x848(r31)
/* 80090654 0008D234  D0 1F 19 04 */	stfs f0, 0x1904(r31)
lbl_80090658:
/* 80090658 0008D238  88 1F 18 F8 */	lbz r0, 0x18f8(r31)
/* 8009065C 0008D23C  80 6D AE 90 */	lwz r3, Fighter_804D6530
/* 80090660 0008D240  54 00 18 38 */	slwi r0, r0, 3
/* 80090664 0008D244  7C 63 02 14 */	add r3, r3, r0
/* 80090668 0008D248  80 03 00 04 */	lwz r0, 4(r3)
/* 8009066C 0008D24C  98 1F 18 FD */	stb r0, 0x18fd(r31)
lbl_80090670:
/* 80090670 0008D250  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80090674 0008D254  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80090678 0008D258  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8009067C 0008D25C  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80090680 0008D260  83 81 00 30 */	lwz r28, 0x30(r1)
/* 80090684 0008D264  38 21 00 40 */	addi r1, r1, 0x40
/* 80090688 0008D268  7C 08 03 A6 */	mtlr r0
/* 8009068C 0008D26C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80090594(ftCo_Fighter* fp, enum_t arg1, int dmg, FtMotionId msid,
                   enum_t arg4, float hitlag_mul)
{
    if (arg1 != ftCo_MS_DeadUpFallHitCameraIce && arg1 != ftCo_MS_Rebirth &&
        !((unsigned) (arg1 - 6) > 1) && fp->motion_id != ftCo_MS_DamageIce)
    {
        fp->dmg.x18fa_model_shift_frames =
            (u16) (p_ftCommonData->x168 *
                       ftCommon_CalcHitlag(dmg, msid, hitlag_mul) +
                   p_ftCommonData->x16C);
        fp->dmg.x18FC = 0;
        if (arg1 == 2) {
            fp->dmg.x18F8 = 2;
        } else if (arg4 == 1) {
            fp->dmg.x18F8 = 0;
        } else {
            fp->dmg.x18F8 = 1;
            fp->dmg.x1900 = fp->coll_data.floor.normal.x;
            fp->dmg.x1904 = fp->coll_data.floor.normal.y;
        }
        // fp->dmg.x18FD = (u8) &Fighter_804D6530[fp->dmg.x18F8 * 2][1];
    }
}
#endif

Vec2* ftCo_80090690(Fighter* fp, Vec2* shift)
{
    if (fp->dmg.x18fa_model_shift_frames != 0) {
        u8 fp_x18F8 = fp->dmg.x18F8;
        Vec2* vec = &Fighter_804D6530[fp_x18F8 * 2][fp->dmg.x18FC];
        if (fp_x18F8 == 1) {
            float x = vec->x * fp->facing_dir;
            shift->x = fp->dmg.x1904 * x;
            shift->y = -fp->dmg.x1900 * x + vec->y;
        } else {
            shift->x = vec->x * fp->facing_dir;
            shift->y = vec->y;
        }
        return shift;
    }
    return NULL;
}

void ftCo_80090718(Fighter* fp)
{
    if (fp->dmg.x1908 != -1) {
        ft_80088148(fp, fp->dmg.x1908, 127, 64);
        fp->dmg.x1908 = -1;
    }
    if (fp->dmg.x190C != NULL) {
        ft_800889F4(fp, fp->dmg.x190C);
        fp->dmg.x190C = NULL;
    }
}

void ftCo_80090780(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if ((s32) M2C_FIELD(fp, s32*, 0xE0) == 0) {
        ftCommon_8007D5D4((Fighter*) fp);
    }
    if (ftCo_GetParasolStatus(gobj) != -1) {
        ftCo_800CF4DC(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x26, 0x18001U, 0.0f, 1.0f, 0.0f,
                                  NULL);
        ftCommon_8007D468((Fighter*) fp);
        ftCommon_8007EBAC((Fighter*) fp, 8U, 0U);
    }
}

void ftCo_DamageFall_Anim(ftCo_GObj* gobj) {}

void ftCo_DamageFall_IASA(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!ftCo_800C5240(gobj)) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
        RETURN_IF(ftCo_80095328(gobj, 0));
        RETURN_IF(ftCo_800D7100(gobj));
        RETURN_IF(ftCo_800C3B10(gobj));
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
        RETURN_IF(ftCo_800D705C(gobj));
        RETURN_IF(ftCo_800CB870(gobj));
        if (ABS(fp->input.lstick.x) >= p_ftCommonData->x210 &&
            fp->x670_timer_lstick_tilt_x < p_ftCommonData->x214)
        {
            ftCo_800CC730(gobj);
            return;
        }
    }
    RETURN_IF(ftCo_800C5DDC(gobj));
    RETURN_IF(ftCo_800C5CD4(gobj));
}

void ftCo_DamageFall_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_DamageFall_Coll(ftCo_GObj* gobj)
{
    ft_8008370C(gobj, ftCo_80090984);
}
