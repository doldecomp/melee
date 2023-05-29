#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_ItemThrow.h"

#include "ftCo_FallSpecial.h"
#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "pl/pl_0371.h"

#include <common_structs.h>
#include <math.h>
#include <placeholder.h>
#include <MSL/trigf.h>

#ifdef MWERKS_GEKKO
/* static */ float const ftCo_804D8590 = 0;
/* static */ double const ftCo_804D8598 = 4503599627370496;
/* static */ double const ftCo_804D85A0 = 4503601774854144;
/* static */ float const ftCo_804D85A8 = 1;
/* static */ float const ftCo_804D85AC = 0.01;
/* static */ float const ftCo_804D85B0 = deg_to_rad;
#endif

bool ftCo_80094E54(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_A &&
        (fp->input.held_inputs & HSD_PAD_LR || !it_8026B30C(fp->item_gobj)))
    {
        return true;
    }
    return false;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm bool ftCo_80094EA4(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80094EA4 00091A84  7C 08 02 A6 */	mflr r0
/* 80094EA8 00091A88  90 01 00 04 */	stw r0, 4(r1)
/* 80094EAC 00091A8C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 80094EB0 00091A90  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 80094EB4 00091A94  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 80094EB8 00091A98  DB A1 00 40 */	stfd f29, 0x40(r1)
/* 80094EBC 00091A9C  DB 81 00 38 */	stfd f28, 0x38(r1)
/* 80094EC0 00091AA0  93 E1 00 34 */	stw r31, 0x34(r1)
/* 80094EC4 00091AA4  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80094EC8 00091AA8  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 80094ECC 00091AAC  7C 7D 1B 78 */	mr r29, r3
/* 80094ED0 00091AB0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80094ED4 00091AB4  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 80094ED8 00091AB8  83 DF 00 10 */	lwz r30, 0x10(r31)
/* 80094EDC 00091ABC  28 00 00 00 */	cmplwi r0, 0
/* 80094EE0 00091AC0  41 82 00 78 */	beq lbl_80094F58
/* 80094EE4 00091AC4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 80094EE8 00091AC8  54 00 05 AF */	rlwinm. r0, r0, 0, 0x16, 0x17
/* 80094EEC 00091ACC  41 82 00 4C */	beq lbl_80094F38
/* 80094EF0 00091AD0  88 BF 06 73 */	lbz r5, 0x673(r31)
/* 80094EF4 00091AD4  3C 80 43 30 */	lis r4, 0x4330
/* 80094EF8 00091AD8  88 1F 06 74 */	lbz r0, 0x674(r31)
/* 80094EFC 00091ADC  7F E3 FB 78 */	mr r3, r31
/* 80094F00 00091AE0  90 A1 00 24 */	stw r5, 0x24(r1)
/* 80094F04 00091AE4  C8 42 8B B8 */	lfd f2, ftCo_804D8598
/* 80094F08 00091AE8  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80094F0C 00091AEC  C3 FF 06 20 */	lfs f31, 0x620(r31)
/* 80094F10 00091AF0  90 81 00 20 */	stw r4, 0x20(r1)
/* 80094F14 00091AF4  C3 DF 06 24 */	lfs f30, 0x624(r31)
/* 80094F18 00091AF8  90 81 00 18 */	stw r4, 0x18(r1)
/* 80094F1C 00091AFC  C8 21 00 20 */	lfd f1, 0x20(r1)
/* 80094F20 00091B00  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80094F24 00091B04  EF 81 10 28 */	fsubs f28, f1, f2
/* 80094F28 00091B08  EF A0 10 28 */	fsubs f29, f0, f2
/* 80094F2C 00091B0C  4B FE 8A 39 */	bl ftCo_GetLStickAngle
/* 80094F30 00091B10  38 A0 00 01 */	li r5, 1
/* 80094F34 00091B14  48 00 00 2C */	b lbl_80094F60
lbl_80094F38:
/* 80094F38 00091B18  C3 82 8B B0 */	lfs f28, ftCo_804D8590
/* 80094F3C 00091B1C  7F E3 FB 78 */	mr r3, r31
/* 80094F40 00091B20  C3 FF 06 38 */	lfs f31, 0x638(r31)
/* 80094F44 00091B24  FF A0 E0 90 */	fmr f29, f28
/* 80094F48 00091B28  C3 DF 06 3C */	lfs f30, 0x63c(r31)
/* 80094F4C 00091B2C  4B FE 8A 51 */	bl ftCo_GetCStickAngle
/* 80094F50 00091B30  38 A0 00 00 */	li r5, 0
/* 80094F54 00091B34  48 00 00 0C */	b lbl_80094F60
lbl_80094F58:
/* 80094F58 00091B38  38 60 00 00 */	li r3, 0
/* 80094F5C 00091B3C  48 00 01 D4 */	b lbl_80095130
lbl_80094F60:
/* 80094F60 00091B40  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80094F64 00091B44  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80094F68 00091B48  40 80 00 0C */	bge lbl_80094F74
/* 80094F6C 00091B4C  FC 40 F8 50 */	fneg f2, f31
/* 80094F70 00091B50  48 00 00 08 */	b lbl_80094F78
lbl_80094F74:
/* 80094F74 00091B54  FC 40 F8 90 */	fmr f2, f31
lbl_80094F78:
/* 80094F78 00091B58  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80094F7C 00091B5C  C0 04 00 3C */	lfs f0, 0x3c(r4)
/* 80094F80 00091B60  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80094F84 00091B64  4C 41 13 82 */	cror 2, 1, 2
/* 80094F88 00091B68  40 82 00 60 */	bne lbl_80094FE8
/* 80094F8C 00091B6C  80 64 00 40 */	lwz r3, 0x40(r4)
/* 80094F90 00091B70  3C 00 43 30 */	lis r0, 0x4330
/* 80094F94 00091B74  C8 62 8B C0 */	lfd f3, ftCo_804D85A0
/* 80094F98 00091B78  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80094F9C 00091B7C  C0 04 00 44 */	lfs f0, 0x44(r4)
/* 80094FA0 00091B80  90 61 00 1C */	stw r3, 0x1c(r1)
/* 80094FA4 00091B84  90 01 00 18 */	stw r0, 0x18(r1)
/* 80094FA8 00091B88  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 80094FAC 00091B8C  EC 42 18 28 */	fsubs f2, f2, f3
/* 80094FB0 00091B90  EC 02 00 2A */	fadds f0, f2, f0
/* 80094FB4 00091B94  FC 1C 00 40 */	fcmpo cr0, f28, f0
/* 80094FB8 00091B98  40 80 00 30 */	bge lbl_80094FE8
/* 80094FBC 00091B9C  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 80094FC0 00091BA0  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80094FC4 00091BA4  EC 3F 00 72 */	fmuls f1, f31, f1
/* 80094FC8 00091BA8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80094FCC 00091BAC  4C 41 13 82 */	cror 2, 1, 2
/* 80094FD0 00091BB0  40 82 00 0C */	bne lbl_80094FDC
/* 80094FD4 00091BB4  38 00 00 74 */	li r0, 0x74
/* 80094FD8 00091BB8  48 00 00 08 */	b lbl_80094FE0
lbl_80094FDC:
/* 80094FDC 00091BBC  38 00 00 75 */	li r0, 0x75
lbl_80094FE0:
/* 80094FE0 00091BC0  7C 1E 03 78 */	mr r30, r0
/* 80094FE4 00091BC4  48 00 01 28 */	b lbl_8009510C
lbl_80094FE8:
/* 80094FE8 00091BC8  C0 04 00 CC */	lfs f0, 0xcc(r4)
/* 80094FEC 00091BCC  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 80094FF0 00091BD0  4C 41 13 82 */	cror 2, 1, 2
/* 80094FF4 00091BD4  40 82 00 20 */	bne lbl_80095014
/* 80094FF8 00091BD8  C0 44 00 D0 */	lfs f2, 0xd0(r4)
/* 80094FFC 00091BDC  C0 1F 01 48 */	lfs f0, 0x148(r31)
/* 80095000 00091BE0  EC 02 00 2A */	fadds f0, f2, f0
/* 80095004 00091BE4  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 80095008 00091BE8  40 80 00 0C */	bge lbl_80095014
/* 8009500C 00091BEC  3B C0 00 76 */	li r30, 0x76
/* 80095010 00091BF0  48 00 00 FC */	b lbl_8009510C
lbl_80095014:
/* 80095014 00091BF4  C0 04 00 D4 */	lfs f0, 0xd4(r4)
/* 80095018 00091BF8  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8009501C 00091BFC  4C 40 13 82 */	cror 2, 0, 2
/* 80095020 00091C00  40 82 00 18 */	bne lbl_80095038
/* 80095024 00091C04  C0 04 00 D8 */	lfs f0, 0xd8(r4)
/* 80095028 00091C08  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 8009502C 00091C0C  40 80 00 0C */	bge lbl_80095038
/* 80095030 00091C10  3B C0 00 77 */	li r30, 0x77
/* 80095034 00091C14  48 00 00 D8 */	b lbl_8009510C
lbl_80095038:
/* 80095038 00091C18  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 8009503C 00091C1C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80095040 00091C20  40 80 00 0C */	bge lbl_8009504C
/* 80095044 00091C24  FC 40 F8 50 */	fneg f2, f31
/* 80095048 00091C28  48 00 00 08 */	b lbl_80095050
lbl_8009504C:
/* 8009504C 00091C2C  FC 40 F8 90 */	fmr f2, f31
lbl_80095050:
/* 80095050 00091C30  C0 04 00 98 */	lfs f0, 0x98(r4)
/* 80095054 00091C34  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80095058 00091C38  4C 41 13 82 */	cror 2, 1, 2
/* 8009505C 00091C3C  40 82 00 58 */	bne lbl_800950B4
/* 80095060 00091C40  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095064 00091C44  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095068 00091C48  40 80 00 0C */	bge lbl_80095074
/* 8009506C 00091C4C  FC 40 08 50 */	fneg f2, f1
/* 80095070 00091C50  48 00 00 08 */	b lbl_80095078
lbl_80095074:
/* 80095074 00091C54  FC 40 08 90 */	fmr f2, f1
lbl_80095078:
/* 80095078 00091C58  C0 04 00 20 */	lfs f0, 0x20(r4)
/* 8009507C 00091C5C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80095080 00091C60  4C 40 13 82 */	cror 2, 0, 2
/* 80095084 00091C64  40 82 00 30 */	bne lbl_800950B4
/* 80095088 00091C68  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8009508C 00091C6C  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095090 00091C70  EC 3F 00 72 */	fmuls f1, f31, f1
/* 80095094 00091C74  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095098 00091C78  4C 41 13 82 */	cror 2, 1, 2
/* 8009509C 00091C7C  40 82 00 0C */	bne lbl_800950A8
/* 800950A0 00091C80  38 00 00 68 */	li r0, 0x68
/* 800950A4 00091C84  48 00 00 08 */	b lbl_800950AC
lbl_800950A8:
/* 800950A8 00091C88  38 00 00 69 */	li r0, 0x69
lbl_800950AC:
/* 800950AC 00091C8C  7C 1E 03 78 */	mr r30, r0
/* 800950B0 00091C90  48 00 00 5C */	b lbl_8009510C
lbl_800950B4:
/* 800950B4 00091C94  C0 04 00 AC */	lfs f0, 0xac(r4)
/* 800950B8 00091C98  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 800950BC 00091C9C  4C 41 13 82 */	cror 2, 1, 2
/* 800950C0 00091CA0  40 82 00 18 */	bne lbl_800950D8
/* 800950C4 00091CA4  C0 04 00 20 */	lfs f0, 0x20(r4)
/* 800950C8 00091CA8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800950CC 00091CAC  40 81 00 0C */	ble lbl_800950D8
/* 800950D0 00091CB0  3B C0 00 6A */	li r30, 0x6a
/* 800950D4 00091CB4  48 00 00 38 */	b lbl_8009510C
lbl_800950D8:
/* 800950D8 00091CB8  C0 04 00 B0 */	lfs f0, 0xb0(r4)
/* 800950DC 00091CBC  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 800950E0 00091CC0  4C 40 13 82 */	cror 2, 0, 2
/* 800950E4 00091CC4  40 82 00 1C */	bne lbl_80095100
/* 800950E8 00091CC8  C0 04 00 20 */	lfs f0, 0x20(r4)
/* 800950EC 00091CCC  FC 00 00 50 */	fneg f0, f0
/* 800950F0 00091CD0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800950F4 00091CD4  40 80 00 0C */	bge lbl_80095100
/* 800950F8 00091CD8  3B C0 00 6B */	li r30, 0x6b
/* 800950FC 00091CDC  48 00 00 10 */	b lbl_8009510C
lbl_80095100:
/* 80095100 00091CE0  2C 05 00 00 */	cmpwi r5, 0
/* 80095104 00091CE4  41 82 00 08 */	beq lbl_8009510C
/* 80095108 00091CE8  3B C0 00 68 */	li r30, 0x68
lbl_8009510C:
/* 8009510C 00091CEC  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80095110 00091CF0  7C 1E 00 00 */	cmpw r30, r0
/* 80095114 00091CF4  41 82 00 18 */	beq lbl_8009512C
/* 80095118 00091CF8  38 7D 00 00 */	addi r3, r29, 0
/* 8009511C 00091CFC  38 9E 00 00 */	addi r4, r30, 0
/* 80095120 00091D00  48 00 07 DD */	bl ftCo_800958FC
/* 80095124 00091D04  38 60 00 01 */	li r3, 1
/* 80095128 00091D08  48 00 00 08 */	b lbl_80095130
lbl_8009512C:
/* 8009512C 00091D0C  38 60 00 00 */	li r3, 0
lbl_80095130:
/* 80095130 00091D10  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80095134 00091D14  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 80095138 00091D18  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 8009513C 00091D1C  CB A1 00 40 */	lfd f29, 0x40(r1)
/* 80095140 00091D20  CB 81 00 38 */	lfd f28, 0x38(r1)
/* 80095144 00091D24  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80095148 00091D28  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8009514C 00091D2C  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80095150 00091D30  38 21 00 58 */	addi r1, r1, 0x58
/* 80095154 00091D34  7C 08 03 A6 */	mtlr r0
/* 80095158 00091D38  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static FtMotionId getHeavyThrowMsid(ftCo_Fighter* fp, float arg1)
{
    if (arg1 * fp->facing_dir >= 0.0f) {
        return ftCo_MS_HeavyThrowF4;
    } else {
        return ftCo_MS_HeavyThrowB4;
    }
}

int ftCo_80094EA4(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    float stick_angle;
    float var_f28;
    float var_f29;
    float var_f30;
    float var_f31;
    FtMotionId msid;
    int ret;
    ftCo_Fighter* fp = gobj->user_data;
    msid = fp->motion_id;
    if (fp->item_gobj != NULL) {
        if (fp->input.x668 & (HSD_PAD_A | HSD_PAD_B)) {
            var_f31 = fp->input.lstick.x;
            var_f30 = fp->input.lstick.y;
            var_f28 = fp->x673;
            var_f29 = fp->x674;
            stick_angle = ftCo_GetLStickAngle(fp);
            ret = true;
        } else {
            var_f28 = 0.0f;
            var_f31 = fp->input.cstick.x;
            var_f29 = 0.0f;
            var_f30 = fp->input.cstick.y;
            stick_angle = ftCo_GetCStickAngle(fp);
            ret = false;
        }
        if (ABS(var_f31) >= p_ftCommonData->x3C &&
            var_f28 < p_ftCommonData->x40 + p_ftCommonData->x44)
        {
            msid = getHeavyThrowMsid(fp, var_f31);
        } else {
            if (var_f30 >= p_ftCommonData->xCC &&
                var_f29 < p_ftCommonData->xD0 + fp->co_attrs.jump_startup_time)
            {
                msid = ftCo_MS_HeavyThrowHi4;
            } else {
                if (var_f30 <= p_ftCommonData->xD4 &&
                    var_f29 < p_ftCommonData->xD8)
                {
                    msid = ftCo_MS_HeavyThrowLw4;
                } else {
                    if (ABS(var_f31) >= p_ftCommonData->x98) {
                        if (ABS(stick_angle) <= p_ftCommonData->x20) {
                            msid = var_f31 * fp->facing_dir >= 0
                                       ? ftCo_MS_HeavyThrowF
                                       : ftCo_MS_HeavyThrowB;
                        } else {
                            goto block_32;
                        }
                    } else {
                    block_32:
                        if (var_f30 >=
                                p_ftCommonData->attackhi3_stick_threshold_y &&
                            stick_angle > p_ftCommonData->x20)
                        {
                            msid = ftCo_MS_HeavyThrowHi;
                        } else {
                            if (var_f30 <= p_ftCommonData->xB0 &&
                                (stick_angle < -p_ftCommonData->x20))
                            {
                                msid = ftCo_MS_HeavyThrowLw;
                            } else if (ret != 0) {
                                msid = ftCo_MS_HeavyThrowF;
                            }
                        }
                    }
                }
            }
        }
        if (msid != fp->motion_id) {
            ftCo_800958FC(gobj, msid);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
#endif

int ftCo_8009515C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && fp->input.x668 & HSD_PAD_A) {
        if (fp->mv.co.itemthrow.x20 != 0) {
            ftCo_800957F4(gobj, ftCo_MS_LightThrowDash);
        } else {
            ftCo_80095A30(gobj);
        }
        return true;
    }
    if (fp->mv.co.itemthrow.x20 != 0) {
        --fp->mv.co.itemthrow.x20;
    }
    return false;
}

bool ftCo_800951D0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && ftCo_80094E54(fp)) {
        ftCo_80095A30(gobj);
        return true;
    }
    return false;
}

bool ftCo_80095254(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && ftCo_80094E54(fp)) {
        ftCo_800957F4(gobj, ftCo_MS_LightThrowDash);
        return true;
    }
    return false;
}

bool ftCo_800952DC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && fp->input.held_inputs & HSD_PAD_LR) {
        ftCo_800957F4(gobj, ftCo_MS_LightThrowDash);
        return true;
    }
    return false;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm bool ftCo_80095328(HSD_GObj*, bool*)
{ // clang-format off
    nofralloc
/* 80095328 00091F08  7C 08 02 A6 */	mflr r0
/* 8009532C 00091F0C  90 01 00 04 */	stw r0, 4(r1)
/* 80095330 00091F10  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 80095334 00091F14  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 80095338 00091F18  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 8009533C 00091F1C  DB A1 00 40 */	stfd f29, 0x40(r1)
/* 80095340 00091F20  DB 81 00 38 */	stfd f28, 0x38(r1)
/* 80095344 00091F24  93 E1 00 34 */	stw r31, 0x34(r1)
/* 80095348 00091F28  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8009534C 00091F2C  7C 9E 23 78 */	mr r30, r4
/* 80095350 00091F30  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 80095354 00091F34  7C 7D 1B 78 */	mr r29, r3
/* 80095358 00091F38  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8009535C 00091F3C  80 03 19 74 */	lwz r0, 0x1974(r3)
/* 80095360 00091F40  3B E3 00 00 */	addi r31, r3, 0
/* 80095364 00091F44  28 00 00 00 */	cmplwi r0, 0
/* 80095368 00091F48  41 82 00 30 */	beq lbl_80095398
/* 8009536C 00091F4C  7F E3 FB 78 */	mr r3, r31
/* 80095370 00091F50  48 04 A1 9D */	bl ftCo_800DF50C
/* 80095374 00091F54  2C 03 00 00 */	cmpwi r3, 0
/* 80095378 00091F58  41 82 00 20 */	beq lbl_80095398
/* 8009537C 00091F5C  C3 A2 8B B0 */	lfs f29, ftCo_804D8590
/* 80095380 00091F60  7F E3 FB 78 */	mr r3, r31
/* 80095384 00091F64  C3 FF 06 38 */	lfs f31, 0x638(r31)
/* 80095388 00091F68  FF C0 E8 90 */	fmr f30, f29
/* 8009538C 00091F6C  C3 9F 06 3C */	lfs f28, 0x63c(r31)
/* 80095390 00091F70  4B FE 86 0D */	bl ftCo_GetCStickAngle
/* 80095394 00091F74  48 00 00 94 */	b lbl_80095428
lbl_80095398:
/* 80095398 00091F78  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8009539C 00091F7C  28 03 00 00 */	cmplwi r3, 0
/* 800953A0 00091F80  41 82 00 80 */	beq lbl_80095420
/* 800953A4 00091F84  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 800953A8 00091F88  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 800953AC 00091F8C  41 82 00 24 */	beq lbl_800953D0
/* 800953B0 00091F90  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 800953B4 00091F94  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 800953B8 00091F98  40 82 00 10 */	bne lbl_800953C8
/* 800953BC 00091F9C  48 1D 5F 51 */	bl it_8026B30C
/* 800953C0 00091FA0  2C 03 00 00 */	cmpwi r3, 0
/* 800953C4 00091FA4  40 82 00 0C */	bne lbl_800953D0
lbl_800953C8:
/* 800953C8 00091FA8  38 00 00 01 */	li r0, 1
/* 800953CC 00091FAC  48 00 00 08 */	b lbl_800953D4
lbl_800953D0:
/* 800953D0 00091FB0  38 00 00 00 */	li r0, 0
lbl_800953D4:
/* 800953D4 00091FB4  2C 00 00 00 */	cmpwi r0, 0
/* 800953D8 00091FB8  41 82 00 48 */	beq lbl_80095420
/* 800953DC 00091FBC  88 BF 06 73 */	lbz r5, 0x673(r31)
/* 800953E0 00091FC0  3C 80 43 30 */	lis r4, 0x4330
/* 800953E4 00091FC4  88 1F 06 74 */	lbz r0, 0x674(r31)
/* 800953E8 00091FC8  7F E3 FB 78 */	mr r3, r31
/* 800953EC 00091FCC  90 A1 00 24 */	stw r5, 0x24(r1)
/* 800953F0 00091FD0  C8 42 8B B8 */	lfd f2, ftCo_804D8598
/* 800953F4 00091FD4  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800953F8 00091FD8  C3 FF 06 20 */	lfs f31, 0x620(r31)
/* 800953FC 00091FDC  90 81 00 20 */	stw r4, 0x20(r1)
/* 80095400 00091FE0  C3 9F 06 24 */	lfs f28, 0x624(r31)
/* 80095404 00091FE4  90 81 00 18 */	stw r4, 0x18(r1)
/* 80095408 00091FE8  C8 21 00 20 */	lfd f1, 0x20(r1)
/* 8009540C 00091FEC  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80095410 00091FF0  EF C1 10 28 */	fsubs f30, f1, f2
/* 80095414 00091FF4  EF A0 10 28 */	fsubs f29, f0, f2
/* 80095418 00091FF8  4B FE 85 4D */	bl ftCo_GetLStickAngle
/* 8009541C 00091FFC  48 00 00 0C */	b lbl_80095428
lbl_80095420:
/* 80095420 00092000  38 60 00 00 */	li r3, 0
/* 80095424 00092004  48 00 01 EC */	b lbl_80095610
lbl_80095428:
/* 80095428 00092008  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 8009542C 0009200C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80095430 00092010  40 80 00 0C */	bge lbl_8009543C
/* 80095434 00092014  FC 40 F8 50 */	fneg f2, f31
/* 80095438 00092018  48 00 00 08 */	b lbl_80095440
lbl_8009543C:
/* 8009543C 0009201C  FC 40 F8 90 */	fmr f2, f31
lbl_80095440:
/* 80095440 00092020  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095444 00092024  C0 03 00 DC */	lfs f0, 0xdc(r3)
/* 80095448 00092028  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8009544C 0009202C  40 80 00 8C */	bge lbl_800954D8
/* 80095450 00092030  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095454 00092034  FC 1C 00 40 */	fcmpo cr0, f28, f0
/* 80095458 00092038  40 80 00 0C */	bge lbl_80095464
/* 8009545C 0009203C  FC 40 E0 50 */	fneg f2, f28
/* 80095460 00092040  48 00 00 08 */	b lbl_80095468
lbl_80095464:
/* 80095464 00092044  FC 40 E0 90 */	fmr f2, f28
lbl_80095468:
/* 80095468 00092048  C0 03 00 E0 */	lfs f0, 0xe0(r3)
/* 8009546C 0009204C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80095470 00092050  40 80 00 68 */	bge lbl_800954D8
/* 80095474 00092054  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80095478 00092058  48 1D 5E 95 */	bl it_8026B30C
/* 8009547C 0009205C  2C 03 00 00 */	cmpwi r3, 0
/* 80095480 00092060  40 82 00 34 */	bne lbl_800954B4
/* 80095484 00092064  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 80095488 00092068  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8009548C 0009206C  40 82 00 28 */	bne lbl_800954B4
/* 80095490 00092070  38 7D 00 00 */	addi r3, r29, 0
/* 80095494 00092074  38 80 00 64 */	li r4, 0x64
/* 80095498 00092078  48 00 03 5D */	bl ftCo_800957F4
/* 8009549C 0009207C  28 1E 00 00 */	cmplwi r30, 0
/* 800954A0 00092080  41 82 00 0C */	beq lbl_800954AC
/* 800954A4 00092084  38 00 00 01 */	li r0, 1
/* 800954A8 00092088  90 1E 00 00 */	stw r0, 0(r30)
lbl_800954AC:
/* 800954AC 0009208C  38 60 00 01 */	li r3, 1
/* 800954B0 00092090  48 00 01 60 */	b lbl_80095610
lbl_800954B4:
/* 800954B4 00092094  38 7D 00 00 */	addi r3, r29, 0
/* 800954B8 00092098  38 9E 00 00 */	addi r4, r30, 0
/* 800954BC 0009209C  48 00 02 89 */	bl ftCo_80095744
/* 800954C0 000920A0  88 1F 22 24 */	lbz r0, 0x2224(r31)
/* 800954C4 000920A4  38 60 00 01 */	li r3, 1
/* 800954C8 000920A8  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 800954CC 000920AC  98 1F 22 24 */	stb r0, 0x2224(r31)
/* 800954D0 000920B0  38 60 00 01 */	li r3, 1
/* 800954D4 000920B4  48 00 01 3C */	b lbl_80095610
lbl_800954D8:
/* 800954D8 000920B8  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 800954DC 000920BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800954E0 000920C0  40 81 00 40 */	ble lbl_80095520
/* 800954E4 000920C4  80 63 03 FC */	lwz r3, 0x3fc(r3)
/* 800954E8 000920C8  3C 00 43 30 */	lis r0, 0x4330
/* 800954EC 000920CC  C8 22 8B C0 */	lfd f1, ftCo_804D85A0
/* 800954F0 000920D0  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800954F4 000920D4  90 61 00 1C */	stw r3, 0x1c(r1)
/* 800954F8 000920D8  90 01 00 18 */	stw r0, 0x18(r1)
/* 800954FC 000920DC  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80095500 000920E0  EC 00 08 28 */	fsubs f0, f0, f1
/* 80095504 000920E4  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 80095508 000920E8  40 80 00 0C */	bge lbl_80095514
/* 8009550C 000920EC  38 00 00 72 */	li r0, 0x72
/* 80095510 000920F0  48 00 00 08 */	b lbl_80095518
lbl_80095514:
/* 80095514 000920F4  38 00 00 66 */	li r0, 0x66
lbl_80095518:
/* 80095518 000920F8  7C 04 03 78 */	mr r4, r0
/* 8009551C 000920FC  48 00 00 D8 */	b lbl_800955F4
lbl_80095520:
/* 80095520 00092100  FC 00 00 50 */	fneg f0, f0
/* 80095524 00092104  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095528 00092108  40 80 00 40 */	bge lbl_80095568
/* 8009552C 0009210C  80 63 03 FC */	lwz r3, 0x3fc(r3)
/* 80095530 00092110  3C 00 43 30 */	lis r0, 0x4330
/* 80095534 00092114  C8 22 8B C0 */	lfd f1, ftCo_804D85A0
/* 80095538 00092118  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8009553C 0009211C  90 61 00 1C */	stw r3, 0x1c(r1)
/* 80095540 00092120  90 01 00 18 */	stw r0, 0x18(r1)
/* 80095544 00092124  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80095548 00092128  EC 00 08 28 */	fsubs f0, f0, f1
/* 8009554C 0009212C  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 80095550 00092130  40 80 00 0C */	bge lbl_8009555C
/* 80095554 00092134  38 00 00 73 */	li r0, 0x73
/* 80095558 00092138  48 00 00 08 */	b lbl_80095560
lbl_8009555C:
/* 8009555C 0009213C  38 00 00 67 */	li r0, 0x67
lbl_80095560:
/* 80095560 00092140  7C 04 03 78 */	mr r4, r0
/* 80095564 00092144  48 00 00 90 */	b lbl_800955F4
lbl_80095568:
/* 80095568 00092148  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8009556C 0009214C  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095570 00092150  EC 3F 00 72 */	fmuls f1, f31, f1
/* 80095574 00092154  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095578 00092158  4C 41 13 82 */	cror 2, 1, 2
/* 8009557C 0009215C  40 82 00 40 */	bne lbl_800955BC
/* 80095580 00092160  80 63 03 FC */	lwz r3, 0x3fc(r3)
/* 80095584 00092164  3C 00 43 30 */	lis r0, 0x4330
/* 80095588 00092168  C8 22 8B C0 */	lfd f1, ftCo_804D85A0
/* 8009558C 0009216C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80095590 00092170  90 61 00 1C */	stw r3, 0x1c(r1)
/* 80095594 00092174  90 01 00 18 */	stw r0, 0x18(r1)
/* 80095598 00092178  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8009559C 0009217C  EC 00 08 28 */	fsubs f0, f0, f1
/* 800955A0 00092180  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 800955A4 00092184  40 80 00 0C */	bge lbl_800955B0
/* 800955A8 00092188  38 00 00 70 */	li r0, 0x70
/* 800955AC 0009218C  48 00 00 08 */	b lbl_800955B4
lbl_800955B0:
/* 800955B0 00092190  38 00 00 64 */	li r0, 0x64
lbl_800955B4:
/* 800955B4 00092194  7C 04 03 78 */	mr r4, r0
/* 800955B8 00092198  48 00 00 3C */	b lbl_800955F4
lbl_800955BC:
/* 800955BC 0009219C  80 63 03 FC */	lwz r3, 0x3fc(r3)
/* 800955C0 000921A0  3C 00 43 30 */	lis r0, 0x4330
/* 800955C4 000921A4  C8 22 8B C0 */	lfd f1, ftCo_804D85A0
/* 800955C8 000921A8  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800955CC 000921AC  90 61 00 1C */	stw r3, 0x1c(r1)
/* 800955D0 000921B0  90 01 00 18 */	stw r0, 0x18(r1)
/* 800955D4 000921B4  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 800955D8 000921B8  EC 00 08 28 */	fsubs f0, f0, f1
/* 800955DC 000921BC  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 800955E0 000921C0  40 80 00 0C */	bge lbl_800955EC
/* 800955E4 000921C4  38 00 00 71 */	li r0, 0x71
/* 800955E8 000921C8  48 00 00 08 */	b lbl_800955F0
lbl_800955EC:
/* 800955EC 000921CC  38 00 00 65 */	li r0, 0x65
lbl_800955F0:
/* 800955F0 000921D0  7C 04 03 78 */	mr r4, r0
lbl_800955F4:
/* 800955F4 000921D4  7F A3 EB 78 */	mr r3, r29
/* 800955F8 000921D8  48 00 01 FD */	bl ftCo_800957F4
/* 800955FC 000921DC  28 1E 00 00 */	cmplwi r30, 0
/* 80095600 000921E0  41 82 00 0C */	beq lbl_8009560C
/* 80095604 000921E4  38 00 00 01 */	li r0, 1
/* 80095608 000921E8  90 1E 00 00 */	stw r0, 0(r30)
lbl_8009560C:
/* 8009560C 000921EC  38 60 00 01 */	li r3, 1
lbl_80095610:
/* 80095610 000921F0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80095614 000921F4  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 80095618 000921F8  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 8009561C 000921FC  CB A1 00 40 */	lfd f29, 0x40(r1)
/* 80095620 00092200  CB 81 00 38 */	lfd f28, 0x38(r1)
/* 80095624 00092204  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80095628 00092208  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8009562C 0009220C  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80095630 00092210  38 21 00 58 */	addi r1, r1, 0x58
/* 80095634 00092214  7C 08 03 A6 */	mtlr r0
/* 80095638 00092218  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo A lot of shared code with #ftCo_80094EA4.
bool ftCo_80095328(HSD_GObj* arg0, bool* arg1)
{
    HSD_GObj* temp_r3_2;
    float temp_f0;
    float var_f1;
    float var_f28;
    float var_f29;
    float var_f2;
    float var_f2_2;
    float var_f30;
    float var_f31;
    int var_r0;
    int var_r0_2;
    int var_r0_3;
    int var_r0_4;
    int var_r0_5;
    int var_r4;
    u8 temp_r5;
    void* temp_r3;

    temp_r3 = arg0->user_data;
    if (((HSD_GObj*) M2C_FIELD(temp_r3, HSD_GObj**, 0x1974) != NULL) &&
        (ftCo_800DF50C(temp_r3) != 0))
    {
        var_f29 = 0.0f;
        var_f31 = M2C_FIELD(temp_r3, float*, 0x638);
        var_f30 = 0.0f;
        var_f28 = M2C_FIELD(temp_r3, float*, 0x63C);
        var_f1 = ftCo_GetCStickAngle((Fighter*) temp_r3);
        goto block_12;
    }
    temp_r3_2 = M2C_FIELD(temp_r3, HSD_GObj**, 0x1974);
    if (temp_r3_2 != NULL) {
        if ((M2C_FIELD(temp_r3, int*, 0x668) & 0x100) &&
            ((M2C_FIELD(temp_r3, int*, 0x65C) & 0x80000000) ||
             (it_8026B30C(temp_r3_2) == 0)))
        {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            temp_r5 = M2C_FIELD(temp_r3, u8*, 0x673);
            var_f31 = M2C_FIELD(temp_r3, float*, 0x620);
            var_f28 = M2C_FIELD(temp_r3, float*, 0x624);
            var_f30 = (float) temp_r5;
            var_f29 = (float) M2C_FIELD(temp_r3, u8*, 0x674);
            var_f1 = ftCo_GetLStickAngle((Fighter*) temp_r3);
        block_12:
            if (var_f31 < 0.0f) {
                var_f2 = -var_f31;
            } else {
                var_f2 = var_f31;
            }
            if (var_f2 < p_ftCommonData->xDC) {
                if (var_f28 < 0.0f) {
                    var_f2_2 = -var_f28;
                } else {
                    var_f2_2 = var_f28;
                }
                if (var_f2_2 < p_ftCommonData->xE0) {
                    if ((it_8026B30C(M2C_FIELD(temp_r3, HSD_GObj**, 0x1974)) ==
                         0) &&
                        !(M2C_FIELD(temp_r3, int*, 0x65C) & 0x80000000))
                    {
                        ftCo_800957F4(arg0, 0x64);
                        if ((u32) arg1 != 0U) {
                            *arg1 = 1;
                        }
                        return 1;
                    }
                    ftCo_80095744(arg0, (int*) arg1);
                    M2C_FIELD(temp_r3, u8*, 0x2224) =
                        (u8) (M2C_FIELD(temp_r3, u8*, 0x2224) | 0x40);
                    return 1;
                }
                goto block_26;
            }
        block_26:
            temp_f0 = p_ftCommonData->x20;
            if (var_f1 > temp_f0) {
                if (var_f29 < (float) M2C_FIELD(p_ftCommonData, int*, 0x3FC)) {
                    var_r0_2 = 0x72;
                } else {
                    var_r0_2 = 0x66;
                }
                var_r4 = var_r0_2;
            } else if (var_f1 < -temp_f0) {
                if (var_f29 < (float) M2C_FIELD(p_ftCommonData, int*, 0x3FC)) {
                    var_r0_3 = 0x73;
                } else {
                    var_r0_3 = 0x67;
                }
                var_r4 = var_r0_3;
            } else {
                M2C_ERROR(unknown instruction : cror eq, gt, eq);
                if ((var_f31 * M2C_FIELD(temp_r3, float*, 0x2C)) == 0.0f) {
                    if (var_f30 <
                        (float) M2C_FIELD(p_ftCommonData, int*, 0x3FC))
                    {
                        var_r0_4 = 0x70;
                    } else {
                        var_r0_4 = 0x64;
                    }
                    var_r4 = var_r0_4;
                } else {
                    if (var_f30 <
                        (float) M2C_FIELD(p_ftCommonData, int*, 0x3FC))
                    {
                        var_r0_5 = 0x71;
                    } else {
                        var_r0_5 = 0x65;
                    }
                    var_r4 = var_r0_5;
                }
            }
            ftCo_800957F4(arg0, var_r4);
            if ((u32) arg1 != 0U) {
                *arg1 = 1;
            }
            return 1;
        }
        goto block_11;
    }
block_11:
    return 0;
}
#endif

bool ftCo_8009563C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && ftCo_80094E54(fp) &&
        fp->mv.co.itemthrow4.unk_timer != 0)
    {
        ftCo_800957F4(gobj, fp->motion_id == ftCo_MS_EscapeF
                                ? ftCo_MS_LightThrowF4
                                : ftCo_MS_LightThrowB4);
        return true;
    }
    if (fp->mv.co.itemthrow4.unk_timer != 0) {
        --fp->mv.co.itemthrow4.unk_timer;
    }
    return false;
}

#if defined(MWERKS_GEKKO)
#pragma push
#pragma force_active on
#endif
void ftCo_80095700(ftCo_GObj* gobj, enum_t arg1)
{
    ftCo_Fighter* fp = gobj->user_data;
    switch (arg1) {
    case 95:
    case 101:
    case 105:
    case 109:
    case 113:
    case 117:
        fp->mv.co.itemthrow.facing_dir = -fp->facing_dir;
        return;
    default:
        fp->mv.co.itemthrow.facing_dir = fp->facing_dir;
        return;
    }
}
#if defined(MWERKS_GEKKO)
#pragma pop
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80095744(ftCo_GObj* gobj, int*)
{ // clang-format off
    nofralloc
/* 80095744 00092324  7C 08 02 A6 */	mflr r0
/* 80095748 00092328  90 01 00 04 */	stw r0, 4(r1)
/* 8009574C 0009232C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80095750 00092330  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80095754 00092334  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80095758 00092338  7C 9E 23 78 */	mr r30, r4
/* 8009575C 0009233C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80095760 00092340  7C 7D 1B 78 */	mr r29, r3
/* 80095764 00092344  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095768 00092348  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009576C 0009234C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80095770 00092350  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80095774 00092354  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80095778 00092358  4B FE 92 1D */	bl ftCo_GetParasolStatus
/* 8009577C 0009235C  2C 03 FF FF */	cmpwi r3, -1
/* 80095780 00092360  41 82 00 38 */	beq lbl_800957B8
/* 80095784 00092364  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80095788 00092368  2C 00 00 92 */	cmpwi r0, 0x92
/* 8009578C 0009236C  40 82 00 10 */	bne lbl_8009579C
/* 80095790 00092370  7F A3 EB 78 */	mr r3, r29
/* 80095794 00092374  48 00 11 35 */	bl ftCo_800968C8
/* 80095798 00092378  48 00 00 0C */	b lbl_800957A4
lbl_8009579C:
/* 8009579C 0009237C  7F A3 EB 78 */	mr r3, r29
/* 800957A0 00092380  48 03 6F 91 */	bl ftCo_800CC730
lbl_800957A4:
/* 800957A4 00092384  28 1E 00 00 */	cmplwi r30, 0
/* 800957A8 00092388  41 82 00 20 */	beq lbl_800957C8
/* 800957AC 0009238C  38 00 00 01 */	li r0, 1
/* 800957B0 00092390  90 1E 00 00 */	stw r0, 0(r30)
/* 800957B4 00092394  48 00 00 14 */	b lbl_800957C8
lbl_800957B8:
/* 800957B8 00092398  28 1E 00 00 */	cmplwi r30, 0
/* 800957BC 0009239C  41 82 00 0C */	beq lbl_800957C8
/* 800957C0 000923A0  38 00 00 00 */	li r0, 0
/* 800957C4 000923A4  90 1E 00 00 */	stw r0, 0(r30)
lbl_800957C8:
/* 800957C8 000923A8  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800957CC 000923AC  38 81 00 14 */	addi r4, r1, 0x14
/* 800957D0 000923B0  C0 22 8B C8 */	lfs f1, ftCo_804D85A8
/* 800957D4 000923B4  48 1D 54 05 */	bl Item_8026ABD8
/* 800957D8 000923B8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800957DC 000923BC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800957E0 000923C0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800957E4 000923C4  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800957E8 000923C8  38 21 00 30 */	addi r1, r1, 0x30
/* 800957EC 000923CC  7C 08 03 A6 */	mtlr r0
/* 800957F0 000923D0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80095744(ftCo_GObj* gobj, int* arg1)
{
    Vec3 vec;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    vec.x = vec.y = vec.z = 0;
    if (ftCo_GetParasolStatus(gobj) != -1) {
        if (fp->motion_id == ftCo_MS_ItemParasolFallSpecial) {
            ftCo_800968C8(gobj);
        } else {
            ftCo_800CC730(gobj);
        }
        if (arg1 != NULL) {
            *arg1 = 1;
        }
    } else if (arg1 != NULL) {
        *arg1 = 0;
    }
    Item_8026ABD8(fp->item_gobj, &vec, 1);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
/* static */ void ftCo_8009588C(void);
/* static */ void ftCo_8009589C(void);
jtbl_t jtbl_803C561C = {
    ftCo_8009588C, ftCo_8009589C, ftCo_8009589C, ftCo_8009589C, ftCo_8009589C,
    ftCo_8009589C, ftCo_8009588C, ftCo_8009589C, ftCo_8009589C, ftCo_8009589C,
    ftCo_8009588C, ftCo_8009589C, ftCo_8009589C, ftCo_8009589C, ftCo_8009588C,
    ftCo_8009589C, ftCo_8009589C, ftCo_8009589C, ftCo_8009588C, ftCo_8009589C,
    ftCo_8009589C, ftCo_8009589C, ftCo_8009588C,
};
#pragma push
asm void ftCo_800957F4(ftCo_GObj* gobj, FtMotionId msid)
{ // clang-format off
    nofralloc
/* 800957F4 000923D4  7C 08 02 A6 */	mflr r0
/* 800957F8 000923D8  90 01 00 04 */	stw r0, 4(r1)
/* 800957FC 000923DC  38 00 00 00 */	li r0, 0
/* 80095800 000923E0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80095804 000923E4  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 80095808 000923E8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8009580C 000923EC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80095810 000923F0  3B C4 00 00 */	addi r30, r4, 0
/* 80095814 000923F4  2C 1E 00 6C */	cmpwi r30, 0x6c
/* 80095818 000923F8  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8009581C 000923FC  7C 7D 1B 78 */	mr r29, r3
/* 80095820 00092400  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80095824 00092404  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 80095828 00092408  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 8009582C 0009240C  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 80095830 00092410  C3 E2 8B C8 */	lfs f31, ftCo_804D85A8
/* 80095834 00092414  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80095838 00092418  41 80 00 10 */	blt lbl_80095848
/* 8009583C 0009241C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095840 00092420  C0 03 04 00 */	lfs f0, 0x400(r3)
/* 80095844 00092424  EF FF 00 32 */	fmuls f31, f31, f0
lbl_80095848:
/* 80095848 00092428  80 64 19 74 */	lwz r3, 0x1974(r4)
/* 8009584C 0009242C  48 1D 5A E9 */	bl it_8026B334
/* 80095850 00092430  C0 02 8B C8 */	lfs f0, ftCo_804D85A8
/* 80095854 00092434  38 1E FF A1 */	addi r0, r30, -95
/* 80095858 00092438  28 00 00 16 */	cmplwi r0, 0x16
/* 8009585C 0009243C  EC 00 08 24 */	fdivs f0, f0, f1
/* 80095860 00092440  EF FF 00 32 */	fmuls f31, f31, f0
/* 80095864 00092444  FC 40 F8 90 */	fmr f2, f31
/* 80095868 00092448  D0 5F 23 44 */	stfs f2, 0x2344(r31)
/* 8009586C 0009244C  80 9D 00 2C */	lwz r4, 0x2c(r29)
/* 80095870 00092450  41 81 00 2C */	bgt ftCo_8009589C
/* 80095874 00092454  3C 60 80 3C */	lis r3, jtbl_803C561C@ha
/* 80095878 00092458  38 63 56 1C */	addi r3, r3, jtbl_803C561C@l
/* 8009587C 0009245C  54 00 10 3A */	slwi r0, r0, 2
/* 80095880 00092460  7C 03 00 2E */	lwzx r0, r3, r0
/* 80095884 00092464  7C 09 03 A6 */	mtctr r0
/* 80095888 00092468  4E 80 04 20 */	bctr
entry ftCo_8009588C
/* 8009588C 0009246C  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 80095890 00092470  FC 00 00 50 */	fneg f0, f0
/* 80095894 00092474  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 80095898 00092478  48 00 00 0C */	b lbl_800958A4
entry ftCo_8009589C
/* 8009589C 0009247C  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 800958A0 00092480  D0 04 23 40 */	stfs f0, 0x2340(r4)
lbl_800958A4:
/* 800958A4 00092484  C0 22 8B B0 */	lfs f1, ftCo_804D8590
/* 800958A8 00092488  7F A3 EB 78 */	mr r3, r29
/* 800958AC 0009248C  38 9E 00 00 */	addi r4, r30, 0
/* 800958B0 00092490  FC 60 08 90 */	fmr f3, f1
/* 800958B4 00092494  38 A0 00 00 */	li r5, 0
/* 800958B8 00092498  38 C0 00 00 */	li r6, 0
/* 800958BC 0009249C  4B FD 3A F1 */	bl Fighter_ChangeMotionState
/* 800958C0 000924A0  7F A3 EB 78 */	mr r3, r29
/* 800958C4 000924A4  4B FD 92 E1 */	bl ftAnim_8006EBA4
/* 800958C8 000924A8  3C 60 80 09 */	lis r3, ftCo_80095EFC@ha
/* 800958CC 000924AC  38 03 5E FC */	addi r0, r3, ftCo_80095EFC@l
/* 800958D0 000924B0  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 800958D4 000924B4  7F A3 EB 78 */	mr r3, r29
/* 800958D8 000924B8  48 00 06 25 */	bl ftCo_80095EFC
/* 800958DC 000924BC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800958E0 000924C0  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800958E4 000924C4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800958E8 000924C8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800958EC 000924CC  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800958F0 000924D0  38 21 00 38 */	addi r1, r1, 0x38
/* 800958F4 000924D4  7C 08 03 A6 */	mtlr r0
/* 800958F8 000924D8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_800957F4(ftCo_GObj* gobj, int msid)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->throw_flags.flags = 0;
    {
        float numerator = 1;
        if (msid >= ftCo_MS_LightThrowF4) {
            numerator *= p_ftCommonData->x400;
        }
        {
            float anim_spd =
                numerator * (1 / it_8026B334(GET_FIGHTER(gobj)->item_gobj));
            fp->mv.co.itemthrow4.anim_spd = anim_spd;
            ftCo_80095700(gobj, msid);
            Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, NULL, 0,
                                      anim_spd, 0);
        }
    }
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftCo_80095EFC;
    ftCo_80095EFC(gobj);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
void ftCo_80095990(void);
void ftCo_800959A0(void);
jtbl_t jtbl_803C5678 = {
    ftCo_80095990, ftCo_800959A0, ftCo_800959A0, ftCo_800959A0, ftCo_800959A0,
    ftCo_800959A0, ftCo_80095990, ftCo_800959A0, ftCo_800959A0, ftCo_800959A0,
    ftCo_80095990, ftCo_800959A0, ftCo_800959A0, ftCo_800959A0, ftCo_80095990,
    ftCo_800959A0, ftCo_800959A0, ftCo_800959A0, ftCo_80095990, ftCo_800959A0,
    ftCo_800959A0, ftCo_800959A0, ftCo_80095990,
};
#pragma push
asm void ftCo_800958FC(ftCo_GObj* gobj, int)
{ // clang-format off
    nofralloc
/* 800958FC 000924DC  7C 08 02 A6 */	mflr r0
/* 80095900 000924E0  90 01 00 04 */	stw r0, 4(r1)
/* 80095904 000924E4  38 00 00 00 */	li r0, 0
/* 80095908 000924E8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8009590C 000924EC  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 80095910 000924F0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80095914 000924F4  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80095918 000924F8  7C 7E 1B 78 */	mr r30, r3
/* 8009591C 000924FC  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80095920 00092500  3B A4 00 00 */	addi r29, r4, 0
/* 80095924 00092504  2C 1D 00 6C */	cmpwi r29, 0x6c
/* 80095928 00092508  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009592C 0009250C  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 80095930 00092510  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 80095934 00092514  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 80095938 00092518  C3 E2 8B C8 */	lfs f31, ftCo_804D85A8
/* 8009593C 0009251C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80095940 00092520  41 80 00 10 */	blt lbl_80095950
/* 80095944 00092524  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095948 00092528  C0 03 04 00 */	lfs f0, 0x400(r3)
/* 8009594C 0009252C  EF FF 00 32 */	fmuls f31, f31, f0
lbl_80095950:
/* 80095950 00092530  80 64 19 74 */	lwz r3, 0x1974(r4)
/* 80095954 00092534  48 1D 59 E1 */	bl it_8026B334
/* 80095958 00092538  C0 02 8B C8 */	lfs f0, ftCo_804D85A8
/* 8009595C 0009253C  38 1D FF A1 */	addi r0, r29, -95
/* 80095960 00092540  28 00 00 16 */	cmplwi r0, 0x16
/* 80095964 00092544  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 80095968 00092548  EC 00 08 24 */	fdivs f0, f0, f1
/* 8009596C 0009254C  EF FF 00 32 */	fmuls f31, f31, f0
/* 80095970 00092550  FC 40 F8 90 */	fmr f2, f31
/* 80095974 00092554  41 81 00 2C */	bgt ftCo_800959A0
/* 80095978 00092558  3C 60 80 3C */	lis r3, jtbl_803C5678@ha
/* 8009597C 0009255C  38 63 56 78 */	addi r3, r3, jtbl_803C5678@l
/* 80095980 00092560  54 00 10 3A */	slwi r0, r0, 2
/* 80095984 00092564  7C 03 00 2E */	lwzx r0, r3, r0
/* 80095988 00092568  7C 09 03 A6 */	mtctr r0
/* 8009598C 0009256C  4E 80 04 20 */	bctr
entry ftCo_80095990
/* 80095990 00092570  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 80095994 00092574  FC 00 00 50 */	fneg f0, f0
/* 80095998 00092578  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 8009599C 0009257C  48 00 00 0C */	b lbl_800959A8
entry ftCo_800959A0
/* 800959A0 00092580  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 800959A4 00092584  D0 04 23 40 */	stfs f0, 0x2340(r4)
lbl_800959A8:
/* 800959A8 00092588  C0 22 8B B0 */	lfs f1, ftCo_804D8590
/* 800959AC 0009258C  7F C3 F3 78 */	mr r3, r30
/* 800959B0 00092590  38 9D 00 00 */	addi r4, r29, 0
/* 800959B4 00092594  FC 60 08 90 */	fmr f3, f1
/* 800959B8 00092598  38 A0 00 00 */	li r5, 0
/* 800959BC 0009259C  38 C0 00 00 */	li r6, 0
/* 800959C0 000925A0  4B FD 39 ED */	bl Fighter_ChangeMotionState
/* 800959C4 000925A4  7F C3 F3 78 */	mr r3, r30
/* 800959C8 000925A8  4B FD 91 DD */	bl ftAnim_8006EBA4
/* 800959CC 000925AC  3C 60 80 09 */	lis r3, ftCo_80095EFC@ha
/* 800959D0 000925B0  38 03 5E FC */	addi r0, r3, ftCo_80095EFC@l
/* 800959D4 000925B4  3C 60 80 09 */	lis r3, ftCo_800974C4@ha
/* 800959D8 000925B8  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 800959DC 000925BC  38 03 74 C4 */	addi r0, r3, ftCo_800974C4@l
/* 800959E0 000925C0  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 800959E4 000925C4  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 800959E8 000925C8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800959EC 000925CC  41 82 00 1C */	beq lbl_80095A08
/* 800959F0 000925D0  3C 60 80 09 */	lis r3, ftCo_800961D0@ha
/* 800959F4 000925D4  38 03 61 D0 */	addi r0, r3, ftCo_800961D0@l
/* 800959F8 000925D8  3C 60 80 09 */	lis r3, ftCo_80096498@ha
/* 800959FC 000925DC  90 1F 21 A4 */	stw r0, 0x21a4(r31)
/* 80095A00 000925E0  38 03 64 98 */	addi r0, r3, ftCo_80096498@l
/* 80095A04 000925E4  90 1F 21 A8 */	stw r0, 0x21a8(r31)
lbl_80095A08:
/* 80095A08 000925E8  7F C3 F3 78 */	mr r3, r30
/* 80095A0C 000925EC  48 00 04 F1 */	bl ftCo_80095EFC
/* 80095A10 000925F0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80095A14 000925F4  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 80095A18 000925F8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80095A1C 000925FC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80095A20 00092600  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80095A24 00092604  38 21 00 38 */	addi r1, r1, 0x38
/* 80095A28 00092608  7C 08 03 A6 */	mtlr r0
/* 80095A2C 0009260C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo Mostly just an inline of #ftCo_800957F4.
void ftCo_800958FC(HSD_GObj* gobj, FtMotionId msid)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    float temp_f2;
    float var_f31;
    void* temp_r31;
    void* temp_r4;
    temp_r31 = gobj->user_data;
    M2C_FIELD(temp_r31, int*, 0x2200) = 0;
    M2C_FIELD(temp_r31, int*, 0x2204) = 0;
    M2C_FIELD(temp_r31, int*, 0x2210) = 0;
    var_f31 = 1.0f;
    if (msid >= 0x6C) {
        var_f31 = 1.0f * p_ftCommonData->x400;
    }
    temp_r4 = gobj->user_data;
    temp_f2 =
        var_f31 *
        (1.0f / it_8026B334(M2C_FIELD(gobj->user_data, HSD_GObj**, 0x1974)));
    switch (msid) {
    case 0x5F:
    case 0x65:
    case 0x69:
    case 0x6D:
    case 0x71:
    case 0x75:
        M2C_FIELD(temp_r4, float*, 0x2340) =
            (float) -M2C_FIELD(temp_r4, float*, 0x2C);
        break;
    default:
        M2C_FIELD(temp_r4, float*, 0x2340) =
            (float) M2C_FIELD(temp_r4, float*, 0x2C);
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0U, NULL, 0.0f, temp_f2, 0.0f);
    ftAnim_8006EBA4(gobj);
    M2C_FIELD(temp_r31, void (**)(HSD_GObj*), 0x21BC) = ftCo_80095EFC;
    M2C_FIELD(temp_r31, void (**)(HSD_GObj*), 0x21DC) = ftCo_800974C4;
    if (((u8) M2C_FIELD(temp_r31, u8*, 0x2222) >> 7U) & 1) {
        M2C_FIELD(temp_r31, void (**)(HSD_GObj*), 0x21A4) = ftCo_800961D0;
        M2C_FIELD(temp_r31, void (**)(HSD_GObj*), 0x21A8) = ftCo_80096498;
    }
    ftCo_80095EFC(gobj);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm /* static */ void ftCo_80095A30(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80095A30 00092610  7C 08 02 A6 */	mflr r0
/* 80095A34 00092614  90 01 00 04 */	stw r0, 4(r1)
/* 80095A38 00092618  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80095A3C 0009261C  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 80095A40 00092620  93 E1 00 44 */	stw r31, 0x44(r1)
/* 80095A44 00092624  7C 7F 1B 78 */	mr r31, r3
/* 80095A48 00092628  93 C1 00 40 */	stw r30, 0x40(r1)
/* 80095A4C 0009262C  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 80095A50 00092630  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80095A54 00092634  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095A58 00092638  C0 23 06 20 */	lfs f1, 0x620(r3)
/* 80095A5C 0009263C  7C 7E 1B 78 */	mr r30, r3
/* 80095A60 00092640  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095A64 00092644  40 80 00 08 */	bge lbl_80095A6C
/* 80095A68 00092648  FC 20 08 50 */	fneg f1, f1
lbl_80095A6C:
/* 80095A6C 0009264C  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 80095A70 00092650  C0 05 00 3C */	lfs f0, 0x3c(r5)
/* 80095A74 00092654  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095A78 00092658  4C 41 13 82 */	cror 2, 1, 2
/* 80095A7C 0009265C  40 82 00 7C */	bne lbl_80095AF8
/* 80095A80 00092660  80 05 00 40 */	lwz r0, 0x40(r5)
/* 80095A84 00092664  3C 60 43 30 */	lis r3, 0x4330
/* 80095A88 00092668  88 9E 06 73 */	lbz r4, 0x673(r30)
/* 80095A8C 0009266C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80095A90 00092670  C8 42 8B C0 */	lfd f2, ftCo_804D85A0
/* 80095A94 00092674  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80095A98 00092678  C8 62 8B B8 */	lfd f3, ftCo_804D8598
/* 80095A9C 0009267C  90 61 00 28 */	stw r3, 0x28(r1)
/* 80095AA0 00092680  C0 05 00 44 */	lfs f0, 0x44(r5)
/* 80095AA4 00092684  90 81 00 34 */	stw r4, 0x34(r1)
/* 80095AA8 00092688  C8 21 00 28 */	lfd f1, 0x28(r1)
/* 80095AAC 0009268C  90 61 00 30 */	stw r3, 0x30(r1)
/* 80095AB0 00092690  EC 21 10 28 */	fsubs f1, f1, f2
/* 80095AB4 00092694  C8 41 00 30 */	lfd f2, 0x30(r1)
/* 80095AB8 00092698  EC 42 18 28 */	fsubs f2, f2, f3
/* 80095ABC 0009269C  EC 01 00 2A */	fadds f0, f1, f0
/* 80095AC0 000926A0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80095AC4 000926A4  40 80 00 34 */	bge lbl_80095AF8
/* 80095AC8 000926A8  C0 5E 06 20 */	lfs f2, 0x620(r30)
/* 80095ACC 000926AC  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 80095AD0 000926B0  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095AD4 000926B4  EC 22 00 72 */	fmuls f1, f2, f1
/* 80095AD8 000926B8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095ADC 000926BC  4C 41 13 82 */	cror 2, 1, 2
/* 80095AE0 000926C0  40 82 00 0C */	bne lbl_80095AEC
/* 80095AE4 000926C4  38 00 00 6C */	li r0, 0x6c
/* 80095AE8 000926C8  48 00 00 08 */	b lbl_80095AF0
lbl_80095AEC:
/* 80095AEC 000926CC  38 00 00 6D */	li r0, 0x6d
lbl_80095AF0:
/* 80095AF0 000926D0  7C 1D 03 78 */	mr r29, r0
/* 80095AF4 000926D4  48 00 01 B8 */	b lbl_80095CAC
lbl_80095AF8:
/* 80095AF8 000926D8  C0 9E 06 24 */	lfs f4, 0x624(r30)
/* 80095AFC 000926DC  C0 05 00 CC */	lfs f0, 0xcc(r5)
/* 80095B00 000926E0  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80095B04 000926E4  4C 41 13 82 */	cror 2, 1, 2
/* 80095B08 000926E8  40 82 00 3C */	bne lbl_80095B44
/* 80095B0C 000926EC  88 7E 06 74 */	lbz r3, 0x674(r30)
/* 80095B10 000926F0  3C 00 43 30 */	lis r0, 0x4330
/* 80095B14 000926F4  C8 62 8B B8 */	lfd f3, ftCo_804D8598
/* 80095B18 000926F8  90 61 00 2C */	stw r3, 0x2c(r1)
/* 80095B1C 000926FC  C0 25 00 D0 */	lfs f1, 0xd0(r5)
/* 80095B20 00092700  90 01 00 28 */	stw r0, 0x28(r1)
/* 80095B24 00092704  C0 1E 01 48 */	lfs f0, 0x148(r30)
/* 80095B28 00092708  C8 41 00 28 */	lfd f2, 0x28(r1)
/* 80095B2C 0009270C  EC 01 00 2A */	fadds f0, f1, f0
/* 80095B30 00092710  EC 22 18 28 */	fsubs f1, f2, f3
/* 80095B34 00092714  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095B38 00092718  40 80 00 0C */	bge lbl_80095B44
/* 80095B3C 0009271C  3B A0 00 6E */	li r29, 0x6e
/* 80095B40 00092720  48 00 01 6C */	b lbl_80095CAC
lbl_80095B44:
/* 80095B44 00092724  C0 05 00 D4 */	lfs f0, 0xd4(r5)
/* 80095B48 00092728  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80095B4C 0009272C  4C 40 13 82 */	cror 2, 0, 2
/* 80095B50 00092730  40 82 00 34 */	bne lbl_80095B84
/* 80095B54 00092734  88 7E 06 74 */	lbz r3, 0x674(r30)
/* 80095B58 00092738  3C 00 43 30 */	lis r0, 0x4330
/* 80095B5C 0009273C  C8 42 8B B8 */	lfd f2, ftCo_804D8598
/* 80095B60 00092740  90 61 00 2C */	stw r3, 0x2c(r1)
/* 80095B64 00092744  C0 05 00 D8 */	lfs f0, 0xd8(r5)
/* 80095B68 00092748  90 01 00 28 */	stw r0, 0x28(r1)
/* 80095B6C 0009274C  C8 21 00 28 */	lfd f1, 0x28(r1)
/* 80095B70 00092750  EC 21 10 28 */	fsubs f1, f1, f2
/* 80095B74 00092754  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095B78 00092758  40 80 00 0C */	bge lbl_80095B84
/* 80095B7C 0009275C  3B A0 00 6F */	li r29, 0x6f
/* 80095B80 00092760  48 00 01 2C */	b lbl_80095CAC
lbl_80095B84:
/* 80095B84 00092764  C0 3E 06 20 */	lfs f1, 0x620(r30)
/* 80095B88 00092768  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095B8C 0009276C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095B90 00092770  40 80 00 08 */	bge lbl_80095B98
/* 80095B94 00092774  FC 20 08 50 */	fneg f1, f1
lbl_80095B98:
/* 80095B98 00092778  C0 05 00 98 */	lfs f0, 0x98(r5)
/* 80095B9C 0009277C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095BA0 00092780  4C 41 13 82 */	cror 2, 1, 2
/* 80095BA4 00092784  40 82 00 74 */	bne lbl_80095C18
/* 80095BA8 00092788  7F C3 F3 78 */	mr r3, r30
/* 80095BAC 0009278C  4B FE 7D B9 */	bl ftCo_GetLStickAngle
/* 80095BB0 00092790  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095BB4 00092794  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095BB8 00092798  40 80 00 14 */	bge lbl_80095BCC
/* 80095BBC 0009279C  7F C3 F3 78 */	mr r3, r30
/* 80095BC0 000927A0  4B FE 7D A5 */	bl ftCo_GetLStickAngle
/* 80095BC4 000927A4  FC 20 08 50 */	fneg f1, f1
/* 80095BC8 000927A8  48 00 00 0C */	b lbl_80095BD4
lbl_80095BCC:
/* 80095BCC 000927AC  7F C3 F3 78 */	mr r3, r30
/* 80095BD0 000927B0  4B FE 7D 95 */	bl ftCo_GetLStickAngle
lbl_80095BD4:
/* 80095BD4 000927B4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095BD8 000927B8  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 80095BDC 000927BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095BE0 000927C0  4C 40 13 82 */	cror 2, 0, 2
/* 80095BE4 000927C4  40 82 00 34 */	bne lbl_80095C18
/* 80095BE8 000927C8  C0 5E 06 20 */	lfs f2, 0x620(r30)
/* 80095BEC 000927CC  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 80095BF0 000927D0  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095BF4 000927D4  EC 22 00 72 */	fmuls f1, f2, f1
/* 80095BF8 000927D8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095BFC 000927DC  4C 41 13 82 */	cror 2, 1, 2
/* 80095C00 000927E0  40 82 00 0C */	bne lbl_80095C0C
/* 80095C04 000927E4  38 00 00 5E */	li r0, 0x5e
/* 80095C08 000927E8  48 00 00 08 */	b lbl_80095C10
lbl_80095C0C:
/* 80095C0C 000927EC  38 00 00 5F */	li r0, 0x5f
lbl_80095C10:
/* 80095C10 000927F0  7C 1D 03 78 */	mr r29, r0
/* 80095C14 000927F4  48 00 00 98 */	b lbl_80095CAC
lbl_80095C18:
/* 80095C18 000927F8  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095C1C 000927FC  C0 3E 06 24 */	lfs f1, 0x624(r30)
/* 80095C20 00092800  C0 03 00 AC */	lfs f0, 0xac(r3)
/* 80095C24 00092804  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095C28 00092808  4C 41 13 82 */	cror 2, 1, 2
/* 80095C2C 0009280C  40 82 00 24 */	bne lbl_80095C50
/* 80095C30 00092810  7F C3 F3 78 */	mr r3, r30
/* 80095C34 00092814  4B FE 7D 31 */	bl ftCo_GetLStickAngle
/* 80095C38 00092818  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095C3C 0009281C  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 80095C40 00092820  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095C44 00092824  40 81 00 0C */	ble lbl_80095C50
/* 80095C48 00092828  3B A0 00 60 */	li r29, 0x60
/* 80095C4C 0009282C  48 00 00 60 */	b lbl_80095CAC
lbl_80095C50:
/* 80095C50 00092830  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095C54 00092834  C0 3E 06 24 */	lfs f1, 0x624(r30)
/* 80095C58 00092838  C0 03 00 B0 */	lfs f0, 0xb0(r3)
/* 80095C5C 0009283C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095C60 00092840  4C 40 13 82 */	cror 2, 0, 2
/* 80095C64 00092844  40 82 00 28 */	bne lbl_80095C8C
/* 80095C68 00092848  7F C3 F3 78 */	mr r3, r30
/* 80095C6C 0009284C  4B FE 7C F9 */	bl ftCo_GetLStickAngle
/* 80095C70 00092850  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095C74 00092854  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 80095C78 00092858  FC 00 00 50 */	fneg f0, f0
/* 80095C7C 0009285C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80095C80 00092860  40 80 00 0C */	bge lbl_80095C8C
/* 80095C84 00092864  3B A0 00 61 */	li r29, 0x61
/* 80095C88 00092868  48 00 00 24 */	b lbl_80095CAC
lbl_80095C8C:
/* 80095C8C 0009286C  80 7E 19 74 */	lwz r3, 0x1974(r30)
/* 80095C90 00092870  48 1D 56 7D */	bl it_8026B30C
/* 80095C94 00092874  2C 03 00 00 */	cmpwi r3, 0
/* 80095C98 00092878  40 82 00 0C */	bne lbl_80095CA4
/* 80095C9C 0009287C  38 00 00 5E */	li r0, 0x5e
/* 80095CA0 00092880  48 00 00 08 */	b lbl_80095CA8
lbl_80095CA4:
/* 80095CA4 00092884  38 00 00 63 */	li r0, 0x63
lbl_80095CA8:
/* 80095CA8 00092888  7C 1D 03 78 */	mr r29, r0
lbl_80095CAC:
/* 80095CAC 0009288C  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 80095CB0 00092890  38 00 00 00 */	li r0, 0
/* 80095CB4 00092894  2C 1D 00 6C */	cmpwi r29, 0x6c
/* 80095CB8 00092898  90 1E 22 00 */	stw r0, 0x2200(r30)
/* 80095CBC 0009289C  90 1E 22 04 */	stw r0, 0x2204(r30)
/* 80095CC0 000928A0  90 1E 22 10 */	stw r0, 0x2210(r30)
/* 80095CC4 000928A4  C3 E2 8B C8 */	lfs f31, ftCo_804D85A8
/* 80095CC8 000928A8  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 80095CCC 000928AC  41 80 00 10 */	blt lbl_80095CDC
/* 80095CD0 000928B0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80095CD4 000928B4  C0 03 04 00 */	lfs f0, 0x400(r3)
/* 80095CD8 000928B8  EF FF 00 32 */	fmuls f31, f31, f0
lbl_80095CDC:
/* 80095CDC 000928BC  80 64 19 74 */	lwz r3, 0x1974(r4)
/* 80095CE0 000928C0  48 1D 56 55 */	bl it_8026B334
/* 80095CE4 000928C4  C0 02 8B C8 */	lfs f0, ftCo_804D85A8
/* 80095CE8 000928C8  38 7F 00 00 */	addi r3, r31, 0
/* 80095CEC 000928CC  38 9D 00 00 */	addi r4, r29, 0
/* 80095CF0 000928D0  EC 00 08 24 */	fdivs f0, f0, f1
/* 80095CF4 000928D4  EF FF 00 32 */	fmuls f31, f31, f0
/* 80095CF8 000928D8  D3 FE 23 44 */	stfs f31, 0x2344(r30)
/* 80095CFC 000928DC  4B FF FA 05 */	bl ftCo_80095700
/* 80095D00 000928E0  C0 22 8B B0 */	lfs f1, ftCo_804D8590
/* 80095D04 000928E4  FC 40 F8 90 */	fmr f2, f31
/* 80095D08 000928E8  7F E3 FB 78 */	mr r3, r31
/* 80095D0C 000928EC  FC 60 08 90 */	fmr f3, f1
/* 80095D10 000928F0  38 9D 00 00 */	addi r4, r29, 0
/* 80095D14 000928F4  38 A0 00 00 */	li r5, 0
/* 80095D18 000928F8  38 C0 00 00 */	li r6, 0
/* 80095D1C 000928FC  4B FD 36 91 */	bl Fighter_ChangeMotionState
/* 80095D20 00092900  7F E3 FB 78 */	mr r3, r31
/* 80095D24 00092904  4B FD 8E 81 */	bl ftAnim_8006EBA4
/* 80095D28 00092908  3C 60 80 09 */	lis r3, ftCo_80095EFC@ha
/* 80095D2C 0009290C  38 03 5E FC */	addi r0, r3, ftCo_80095EFC@l
/* 80095D30 00092910  90 1E 21 BC */	stw r0, 0x21bc(r30)
/* 80095D34 00092914  7F E3 FB 78 */	mr r3, r31
/* 80095D38 00092918  48 00 01 C5 */	bl ftCo_80095EFC
/* 80095D3C 0009291C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80095D40 00092920  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 80095D44 00092924  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 80095D48 00092928  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80095D4C 0009292C  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 80095D50 00092930  38 21 00 50 */	addi r1, r1, 0x50
/* 80095D54 00092934  7C 08 03 A6 */	mtlr r0
/* 80095D58 00092938  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80095A30(HSD_GObj* gobj)
{
    int sp2C;
    int sp28;
    float temp_f4;
    float var_f1;
    float var_f1_2;
    float var_f1_3;
    int var_r0;
    int var_r0_2;
    int var_r0_3;
    int var_r29;
    u8 temp_r3_2;
    void* temp_r3;
    temp_r3 = gobj->user_data;
    var_f1 = M2C_FIELD(temp_r3, float*, 0x620);
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    M2C_ERROR(unknown instruction : cror eq, gt, eq);
    if ((var_f1 == p_ftCommonData->x3C) &&
        ((float) M2C_FIELD(temp_r3, u8*, 0x673) <
         ((float) p_ftCommonData->x40 + p_ftCommonData->x44)))
    {
        M2C_ERROR(unknown instruction : cror eq, gt, eq);
        if ((M2C_FIELD(temp_r3, float*, 0x620) *
             M2C_FIELD(temp_r3, float*, 0x2C)) == 0.0f)
        {
            var_r0 = 0x6C;
        } else {
            var_r0 = 0x6D;
        }
        var_r29 = var_r0;
    } else {
        temp_f4 = M2C_FIELD(temp_r3, float*, 0x624);
        M2C_ERROR(unknown instruction : cror eq, gt, eq);
        if ((temp_f4 == p_ftCommonData->xCC) &&
            (temp_r3_2 = M2C_FIELD(temp_r3, u8*, 0x674),
             sp2C = (int) temp_r3_2, sp28 = 0x43300000,
             (((float) temp_r3_2 < (p_ftCommonData->xD0 +
                                    M2C_FIELD(temp_r3, float*, 0x148))) != 0)))
        {
            var_r29 = 0x6E;
        } else {
            M2C_ERROR(unknown instruction : cror eq, lt, eq);
            if ((temp_f4 == p_ftCommonData->xD4) &&
                ((float) M2C_FIELD(temp_r3, u8*, 0x674) < p_ftCommonData->xD8))
            {
                var_r29 = 0x6F;
            } else {
                var_f1_2 = M2C_FIELD(temp_r3, float*, 0x620);
                if (var_f1_2 < 0.0f) {
                    var_f1_2 = -var_f1_2;
                }
                M2C_ERROR(unknown instruction : cror eq, gt, eq);
                if (var_f1_2 == p_ftCommonData->x98) {
                    if (ftCo_GetLStickAngle((Fighter*) temp_r3) < 0.0f) {
                        var_f1_3 = -ftCo_GetLStickAngle((Fighter*) temp_r3);
                    } else {
                        var_f1_3 = ftCo_GetLStickAngle((Fighter*) temp_r3);
                    }
                    M2C_ERROR(unknown instruction : cror eq, lt, eq);
                    if (var_f1_3 == p_ftCommonData->x20) {
                        M2C_ERROR(unknown instruction : cror eq, gt, eq);
                        if ((M2C_FIELD(temp_r3, float*, 0x620) *
                             M2C_FIELD(temp_r3, float*, 0x2C)) == 0.0f)
                        {
                            var_r0_2 = 0x5E;
                        } else {
                            var_r0_2 = 0x5F;
                        }
                        var_r29 = var_r0_2;
                    } else {
                        goto block_25;
                    }
                } else {
                block_25:
                    M2C_ERROR(unknown instruction : cror eq, gt, eq);
                    if ((M2C_FIELD(temp_r3, float*, 0x624) ==
                         p_ftCommonData->attackhi3_stick_threshold_y) &&
                        (ftCo_GetLStickAngle((Fighter*) temp_r3) >
                         p_ftCommonData->x20))
                    {
                        var_r29 = 0x60;
                    } else {
                        M2C_ERROR(unknown instruction : cror eq, lt, eq);
                        if ((M2C_FIELD(temp_r3, float*, 0x624) ==
                             p_ftCommonData->xB0) &&
                            (ftCo_GetLStickAngle((Fighter*) temp_r3) <
                             -p_ftCommonData->x20))
                        {
                            var_r29 = 0x61;
                        } else {
                            if (it_8026B30C(M2C_FIELD(temp_r3, HSD_GObj**,
                                                      0x1974)) == 0)
                            {
                                var_r0_3 = 0x5E;
                            } else {
                                var_r0_3 = 0x63;
                            }
                            var_r29 = var_r0_3;
                        }
                    }
                }
            }
        }
    }
    ftCo_800957F4(gobj, var_r29);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80095D5C(ftCo_Fighter* fp, Vec3* arg1)
{ // clang-format off
    nofralloc
/* 80095D5C 0009293C  7C 08 02 A6 */	mflr r0
/* 80095D60 00092940  90 01 00 04 */	stw r0, 4(r1)
/* 80095D64 00092944  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80095D68 00092948  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 80095D6C 0009294C  DB C1 00 28 */	stfd f30, 0x28(r1)
/* 80095D70 00092950  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80095D74 00092954  3B E4 00 00 */	addi r31, r4, 0
/* 80095D78 00092958  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80095D7C 0009295C  7C 7E 1B 78 */	mr r30, r3
/* 80095D80 00092960  80 A3 22 00 */	lwz r5, 0x2200(r3)
/* 80095D84 00092964  38 7E 01 10 */	addi r3, r30, 0x110
/* 80095D88 00092968  C3 E2 8B C8 */	lfs f31, ftCo_804D85A8
/* 80095D8C 0009296C  28 05 00 00 */	cmplwi r5, 0
/* 80095D90 00092970  41 82 00 28 */	beq lbl_80095DB8
/* 80095D94 00092974  54 A0 A5 BE */	rlwinm r0, r5, 0x14, 0x16, 0x1f
/* 80095D98 00092978  C8 22 8B B8 */	lfd f1, ftCo_804D8598
/* 80095D9C 0009297C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80095DA0 00092980  3C 00 43 30 */	lis r0, 0x4330
/* 80095DA4 00092984  C0 42 8B CC */	lfs f2, ftCo_804D85AC
/* 80095DA8 00092988  90 01 00 18 */	stw r0, 0x18(r1)
/* 80095DAC 0009298C  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80095DB0 00092990  EC 00 08 28 */	fsubs f0, f0, f1
/* 80095DB4 00092994  EF E2 00 32 */	fmuls f31, f2, f0
lbl_80095DB8:
/* 80095DB8 00092998  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 80095DBC 0009299C  28 05 00 00 */	cmplwi r5, 0
/* 80095DC0 000929A0  80 8D AE B0 */	lwz r4, Fighter_804D6550
/* 80095DC4 000929A4  1C 00 00 0C */	mulli r0, r0, 0xc
/* 80095DC8 000929A8  C0 23 00 B0 */	lfs f1, 0xb0(r3)
/* 80095DCC 000929AC  7C 64 02 14 */	add r3, r4, r0
/* 80095DD0 000929B0  C0 03 FB 98 */	lfs f0, -0x468(r3)
/* 80095DD4 000929B4  EC 01 00 32 */	fmuls f0, f1, f0
/* 80095DD8 000929B8  EF FF 00 32 */	fmuls f31, f31, f0
/* 80095DDC 000929BC  41 82 00 50 */	beq lbl_80095E2C
/* 80095DE0 000929C0  A8 1E 22 02 */	lha r0, 0x2202(r30)
/* 80095DE4 000929C4  54 00 A0 18 */	rlwinm r0, r0, 0x14, 0, 0xc
/* 80095DE8 000929C8  7C 00 A6 70 */	srawi r0, r0, 0x14
/* 80095DEC 000929CC  2C 00 01 69 */	cmpwi r0, 0x169
/* 80095DF0 000929D0  40 82 00 0C */	bne lbl_80095DFC
/* 80095DF4 000929D4  C3 C3 FB 9C */	lfs f30, -0x464(r3)
/* 80095DF8 000929D8  48 00 00 28 */	b lbl_80095E20
lbl_80095DFC:
/* 80095DFC 000929DC  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80095E00 000929E0  C8 22 8B C0 */	lfd f1, ftCo_804D85A0
/* 80095E04 000929E4  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80095E08 000929E8  3C 00 43 30 */	lis r0, 0x4330
/* 80095E0C 000929EC  C0 42 8B D0 */	lfs f2, ftCo_804D85B0
/* 80095E10 000929F0  90 01 00 18 */	stw r0, 0x18(r1)
/* 80095E14 000929F4  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80095E18 000929F8  EC 00 08 28 */	fsubs f0, f0, f1
/* 80095E1C 000929FC  EF C2 00 32 */	fmuls f30, f2, f0
lbl_80095E20:
/* 80095E20 00092A00  38 00 00 00 */	li r0, 0
/* 80095E24 00092A04  90 1E 22 00 */	stw r0, 0x2200(r30)
/* 80095E28 00092A08  48 00 00 08 */	b lbl_80095E30
lbl_80095E2C:
/* 80095E2C 00092A0C  C3 C3 FB 9C */	lfs f30, -0x464(r3)
lbl_80095E30:
/* 80095E30 00092A10  FC 20 F0 90 */	fmr f1, f30
/* 80095E34 00092A14  48 29 04 0D */	bl cosf
/* 80095E38 00092A18  EC 5F 00 72 */	fmuls f2, f31, f1
/* 80095E3C 00092A1C  C0 1E 23 40 */	lfs f0, 0x2340(r30)
/* 80095E40 00092A20  FC 20 F0 90 */	fmr f1, f30
/* 80095E44 00092A24  EC 00 00 B2 */	fmuls f0, f0, f2
/* 80095E48 00092A28  D0 1F 00 00 */	stfs f0, 0(r31)
/* 80095E4C 00092A2C  48 29 05 89 */	bl sinf
/* 80095E50 00092A30  EC 1F 00 72 */	fmuls f0, f31, f1
/* 80095E54 00092A34  D0 1F 00 04 */	stfs f0, 4(r31)
/* 80095E58 00092A38  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095E5C 00092A3C  D0 1F 00 08 */	stfs f0, 8(r31)
/* 80095E60 00092A40  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80095E64 00092A44  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 80095E68 00092A48  CB C1 00 28 */	lfd f30, 0x28(r1)
/* 80095E6C 00092A4C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80095E70 00092A50  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80095E74 00092A54  38 21 00 38 */	addi r1, r1, 0x38
/* 80095E78 00092A58  7C 08 03 A6 */	mtlr r0
/* 80095E7C 00092A5C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80095D5C(Fighter* fp, Vec3* arg1)
{
    float vel;
    float angle;
    void* array_element;
    u32 cmd_var0 = fp->cmd_vars[0];
    float vel_mul = 1;
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    if (cmd_var0 != 0) {
        vel_mul = 0.01f * ((cmd_var0 >> 12) & 0x3FF);
    }
    array_element = Fighter_804D6550 + (fp->motion_id * 3);
    vel = vel_mul * (co_attrs->item_throw_velocity_multiplier *
                     M2C_FIELD(array_element, float*, -0x468));
    if (cmd_var0 != 0) {
        u32 s16_var1 = ((s16*) &fp->cmd_vars)[1];
        int int_angle = ((int) (s16_var1 << 20)) >> 20;
        if (int_angle == 361) {
            angle = M2C_FIELD(array_element, float*, -0x464);
        } else {
            angle = deg_to_rad * int_angle;
        }
        fp->cmd_vars[0] = 0;
    } else {
        angle = M2C_FIELD(array_element, float*, -0x464);
    }
    arg1->x = fp->mv.co.itemthrow.facing_dir * (vel * cosf(angle));
    arg1->y = vel * sinf(angle);
    arg1->z = 0;
}
#endif

void ftCo_ItemThrow_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (ftCheckThrowB4(fp)) {
        fp->facing_dir = -fp->facing_dir;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80095EFC(ftCo_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 80095EFC 00092ADC  7C 08 02 A6 */	mflr r0
/* 80095F00 00092AE0  90 01 00 04 */	stw r0, 4(r1)
/* 80095F04 00092AE4  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 80095F08 00092AE8  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 80095F0C 00092AEC  93 E1 00 4C */	stw r31, 0x4c(r1)
/* 80095F10 00092AF0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80095F14 00092AF4  80 64 19 74 */	lwz r3, 0x1974(r4)
/* 80095F18 00092AF8  3B E4 00 00 */	addi r31, r4, 0
/* 80095F1C 00092AFC  28 03 00 00 */	cmplwi r3, 0
/* 80095F20 00092B00  41 82 01 E8 */	beq lbl_80096108
/* 80095F24 00092B04  48 1D CD 6D */	bl it_80272C90
/* 80095F28 00092B08  38 A1 00 30 */	addi r5, r1, 0x30
/* 80095F2C 00092B0C  38 80 00 00 */	li r4, 0
/* 80095F30 00092B10  4B F7 52 9D */	bl lb_8000B1CC
/* 80095F34 00092B14  88 7F 22 10 */	lbz r3, 0x2210(r31)
/* 80095F38 00092B18  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 80095F3C 00092B1C  41 82 00 18 */	beq lbl_80095F54
/* 80095F40 00092B20  38 00 00 00 */	li r0, 0
/* 80095F44 00092B24  50 03 26 F6 */	rlwimi r3, r0, 4, 0x1b, 0x1b
/* 80095F48 00092B28  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 80095F4C 00092B2C  38 00 00 01 */	li r0, 1
/* 80095F50 00092B30  48 00 00 08 */	b lbl_80095F58
lbl_80095F54:
/* 80095F54 00092B34  38 00 00 00 */	li r0, 0
lbl_80095F58:
/* 80095F58 00092B38  2C 00 00 00 */	cmpwi r0, 0
/* 80095F5C 00092B3C  41 82 01 94 */	beq lbl_800960F0
/* 80095F60 00092B40  38 7F 00 00 */	addi r3, r31, 0
/* 80095F64 00092B44  38 81 00 24 */	addi r4, r1, 0x24
/* 80095F68 00092B48  4B FF FD F5 */	bl ftCo_80095D5C
/* 80095F6C 00092B4C  80 1F 22 04 */	lwz r0, 0x2204(r31)
/* 80095F70 00092B50  38 9F 01 10 */	addi r4, r31, 0x110
/* 80095F74 00092B54  C0 82 8B C8 */	lfs f4, ftCo_804D85A8
/* 80095F78 00092B58  28 00 00 00 */	cmplwi r0, 0
/* 80095F7C 00092B5C  41 82 00 30 */	beq lbl_80095FAC
/* 80095F80 00092B60  54 00 02 BE */	clrlwi r0, r0, 0xa
/* 80095F84 00092B64  C8 22 8B B8 */	lfd f1, ftCo_804D8598
/* 80095F88 00092B68  90 01 00 44 */	stw r0, 0x44(r1)
/* 80095F8C 00092B6C  3C 60 43 30 */	lis r3, 0x4330
/* 80095F90 00092B70  C0 42 8B CC */	lfs f2, ftCo_804D85AC
/* 80095F94 00092B74  38 00 00 00 */	li r0, 0
/* 80095F98 00092B78  90 61 00 40 */	stw r3, 0x40(r1)
/* 80095F9C 00092B7C  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 80095FA0 00092B80  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 80095FA4 00092B84  EC 00 08 28 */	fsubs f0, f0, f1
/* 80095FA8 00092B88  EC 82 00 32 */	fmuls f4, f2, f0
lbl_80095FAC:
/* 80095FAC 00092B8C  C0 1F 22 14 */	lfs f0, 0x2214(r31)
/* 80095FB0 00092B90  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80095FB4 00092B94  FC 40 00 50 */	fneg f2, f0
/* 80095FB8 00092B98  C0 3F 08 9C */	lfs f1, 0x89c(r31)
/* 80095FBC 00092B9C  C0 A1 00 30 */	lfs f5, 0x30(r1)
/* 80095FC0 00092BA0  1C 00 00 0C */	mulli r0, r0, 0xc
/* 80095FC4 00092BA4  C0 1F 23 48 */	lfs f0, 0x2348(r31)
/* 80095FC8 00092BA8  EC E2 08 24 */	fdivs f7, f2, f1
/* 80095FCC 00092BAC  80 6D AE B0 */	lwz r3, Fighter_804D6550
/* 80095FD0 00092BB0  C0 64 00 B4 */	lfs f3, 0xb4(r4)
/* 80095FD4 00092BB4  7C 63 02 14 */	add r3, r3, r0
/* 80095FD8 00092BB8  C0 C1 00 34 */	lfs f6, 0x34(r1)
/* 80095FDC 00092BBC  EC 20 28 28 */	fsubs f1, f0, f5
/* 80095FE0 00092BC0  C0 43 FB A0 */	lfs f2, -0x460(r3)
/* 80095FE4 00092BC4  C0 02 8B B0 */	lfs f0, ftCo_804D8590
/* 80095FE8 00092BC8  EC 43 00 B2 */	fmuls f2, f3, f2
/* 80095FEC 00092BCC  EC 27 28 7A */	fmadds f1, f7, f1, f5
/* 80095FF0 00092BD0  EC 84 00 B2 */	fmuls f4, f4, f2
/* 80095FF4 00092BD4  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80095FF8 00092BD8  C0 3F 23 4C */	lfs f1, 0x234c(r31)
/* 80095FFC 00092BDC  FF E0 20 90 */	fmr f31, f4
/* 80096000 00092BE0  EC 21 30 28 */	fsubs f1, f1, f6
/* 80096004 00092BE4  EC 27 30 7A */	fmadds f1, f7, f1, f6
/* 80096008 00092BE8  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8009600C 00092BEC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80096010 00092BF0  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80096014 00092BF4  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80096018 00092BF8  80 BF 19 74 */	lwz r5, 0x1974(r31)
/* 8009601C 00092BFC  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80096020 00092C00  4B FA 89 59 */	bl pl_8003E978
/* 80096024 00092C04  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80096028 00092C08  2C 00 00 63 */	cmpwi r0, 0x63
/* 8009602C 00092C0C  40 82 00 1C */	bne lbl_80096048
/* 80096030 00092C10  FC 20 F8 90 */	fmr f1, f31
/* 80096034 00092C14  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80096038 00092C18  38 81 00 18 */	addi r4, r1, 0x18
/* 8009603C 00092C1C  38 A1 00 24 */	addi r5, r1, 0x24
/* 80096040 00092C20  48 1D 4C 35 */	bl Item_8026AC74
/* 80096044 00092C24  48 00 00 C4 */	b lbl_80096108
lbl_80096048:
/* 80096048 00092C28  2C 00 00 6C */	cmpwi r0, 0x6c
/* 8009604C 00092C2C  41 80 00 54 */	blt lbl_800960A0
/* 80096050 00092C30  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80096054 00092C34  48 1D 52 61 */	bl it_8026B2B4
/* 80096058 00092C38  2C 03 00 01 */	cmpwi r3, 1
/* 8009605C 00092C3C  40 82 00 18 */	bne lbl_80096074
/* 80096060 00092C40  38 7F 00 00 */	addi r3, r31, 0
/* 80096064 00092C44  38 80 00 1D */	li r4, 0x1d
/* 80096068 00092C48  38 A0 00 00 */	li r5, 0
/* 8009606C 00092C4C  4B FE 8B 41 */	bl ftCommon_8007EBAC
/* 80096070 00092C50  48 00 00 14 */	b lbl_80096084
lbl_80096074:
/* 80096074 00092C54  38 7F 00 00 */	addi r3, r31, 0
/* 80096078 00092C58  38 80 00 1B */	li r4, 0x1b
/* 8009607C 00092C5C  38 A0 00 00 */	li r5, 0
/* 80096080 00092C60  4B FE 8B 2D */	bl ftCommon_8007EBAC
lbl_80096084:
/* 80096084 00092C64  FC 20 F8 90 */	fmr f1, f31
/* 80096088 00092C68  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8009608C 00092C6C  38 81 00 18 */	addi r4, r1, 0x18
/* 80096090 00092C70  38 A1 00 24 */	addi r5, r1, 0x24
/* 80096094 00092C74  38 C0 00 01 */	li r6, 1
/* 80096098 00092C78  48 1D 4C 89 */	bl Item_8026AD20
/* 8009609C 00092C7C  48 00 00 6C */	b lbl_80096108
lbl_800960A0:
/* 800960A0 00092C80  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800960A4 00092C84  48 1D 52 11 */	bl it_8026B2B4
/* 800960A8 00092C88  2C 03 00 01 */	cmpwi r3, 1
/* 800960AC 00092C8C  40 82 00 18 */	bne lbl_800960C4
/* 800960B0 00092C90  38 7F 00 00 */	addi r3, r31, 0
/* 800960B4 00092C94  38 80 00 1C */	li r4, 0x1c
/* 800960B8 00092C98  38 A0 00 00 */	li r5, 0
/* 800960BC 00092C9C  4B FE 8A F1 */	bl ftCommon_8007EBAC
/* 800960C0 00092CA0  48 00 00 14 */	b lbl_800960D4
lbl_800960C4:
/* 800960C4 00092CA4  38 7F 00 00 */	addi r3, r31, 0
/* 800960C8 00092CA8  38 80 00 1A */	li r4, 0x1a
/* 800960CC 00092CAC  38 A0 00 00 */	li r5, 0
/* 800960D0 00092CB0  4B FE 8A DD */	bl ftCommon_8007EBAC
lbl_800960D4:
/* 800960D4 00092CB4  FC 20 F8 90 */	fmr f1, f31
/* 800960D8 00092CB8  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800960DC 00092CBC  38 81 00 18 */	addi r4, r1, 0x18
/* 800960E0 00092CC0  38 A1 00 24 */	addi r5, r1, 0x24
/* 800960E4 00092CC4  38 C0 00 00 */	li r6, 0
/* 800960E8 00092CC8  48 1D 4C 39 */	bl Item_8026AD20
/* 800960EC 00092CCC  48 00 00 1C */	b lbl_80096108
lbl_800960F0:
/* 800960F0 00092CD0  80 61 00 30 */	lwz r3, 0x30(r1)
/* 800960F4 00092CD4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800960F8 00092CD8  90 7F 23 48 */	stw r3, 0x2348(r31)
/* 800960FC 00092CDC  90 1F 23 4C */	stw r0, 0x234c(r31)
/* 80096100 00092CE0  80 01 00 38 */	lwz r0, 0x38(r1)
/* 80096104 00092CE4  90 1F 23 50 */	stw r0, 0x2350(r31)
lbl_80096108:
/* 80096108 00092CE8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8009610C 00092CEC  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 80096110 00092CF0  83 E1 00 4C */	lwz r31, 0x4c(r1)
/* 80096114 00092CF4  38 21 00 58 */	addi r1, r1, 0x58
/* 80096118 00092CF8  7C 08 03 A6 */	mtlr r0
/* 8009611C 00092CFC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80095EFC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Item_GObj* item_gobj = fp->item_gobj;
    if (item_gobj != NULL) {
        Vec3 vec0;
        lb_8000B1CC(it_80272C90(item_gobj), NULL, &vec0);
        if (ftCheckThrowB3(fp)) {
            Vec3 vec1;
            ftCo_80095D5C(fp, &vec1);
            {
                u32 cmd_var1 = fp->cmd_vars[1];
                float var_f4 = 1;
                if (cmd_var1 != 0) {
                    fp->cmd_vars[1] = 0;
                    var_f4 = 0.01f * (cmd_var1 & 0x3FFFFF);
                }
                {
                    float vec0_x = vec0.x;
                    float fsm = -fp->x2214 / fp->frame_spd_mul;
                    float cd_xB4 = M2C_FIELD(fp + 0x110, float*, 0xB4);
                    float temp_f2 =
                        cd_xB4 *
                        M2C_FIELD((Fighter_804D6550 + (fp->motion_id * 3)),
                                  float*, -0x460);
                    float temp_f4 = var_f4 * temp_f2;
                    {
                        Vec3 vec2;
                        vec2.x = fsm * (fp->mv.co.itemthrow4.x8.x - vec0_x) +
                                 vec0_x;
                        {
                            float vec1_y =
                                fsm * (fp->mv.co.itemthrow4.x8.y - vec0.y) +
                                vec0.y;
                            vec2.y = vec1_y;
                            vec2.z = 0;
                            pl_8003E978(fp->player_id, fp->x221F_flag.bits.b4,
                                        fp->item_gobj, vec1_y, temp_f2, cd_xB4,
                                        temp_f4, vec0_x, vec0.y, fsm);
                        }
                        {
                            FtMoveId msid = fp->motion_id;
                            if (msid == ftCo_MS_LightThrowDrop) {
                                Item_8026AC74(fp->item_gobj, &vec2, &vec1,
                                              temp_f4);
                            } else if (msid >= ftCo_MS_LightThrowF4) {
                                if (it_8026B2B4(fp->item_gobj) == 1) {
                                    ftCommon_8007EBAC(fp, 29, 0);
                                } else {
                                    ftCommon_8007EBAC(fp, 27, 0);
                                }
                                Item_8026AD20(fp->item_gobj, &vec2, &vec1,
                                              temp_f4);
                            } else {
                                if (it_8026B2B4(fp->item_gobj) == 1) {
                                    ftCommon_8007EBAC(fp, 28, 0);
                                } else {
                                    ftCommon_8007EBAC(fp, 26, 0);
                                }
                                Item_8026AD20(fp->item_gobj, &vec2, &vec1,
                                              temp_f4);
                            }
                        }
                    }
                }
            }
        } else {
            fp->mv.co.itemthrow4.x8.x = vec0.x;
            fp->mv.co.itemthrow4.x8.y = vec0.y;
            fp->mv.co.itemthrow4.x8.z = vec0.z;
        }
    }
}
#endif

void ftCo_ItemThrow_IASA(ftCo_GObj* gobj) {}

void ftCo_ItemThrow_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_LightThrowDash_Phys(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80096144 00092D24  7C 08 02 A6 */	mflr r0
/* 80096148 00092D28  90 01 00 04 */	stw r0, 4(r1)
/* 8009614C 00092D2C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80096150 00092D30  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 80096154 00092D34  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 80096158 00092D38  C0 06 04 08 */	lfs f0, 0x408(r6)
/* 8009615C 00092D3C  C0 25 08 94 */	lfs f1, 0x894(r5)
/* 80096160 00092D40  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80096164 00092D44  4C 40 13 82 */	cror 2, 0, 2
/* 80096168 00092D48  40 82 00 24 */	bne lbl_8009618C
/* 8009616C 00092D4C  C0 26 04 04 */	lfs f1, 0x404(r6)
/* 80096170 00092D50  C0 05 01 28 */	lfs f0, 0x128(r5)
/* 80096174 00092D54  C0 66 04 0C */	lfs f3, 0x40c(r6)
/* 80096178 00092D58  EC 01 00 32 */	fmuls f0, f1, f0
/* 8009617C 00092D5C  C0 45 00 2C */	lfs f2, 0x2c(r5)
/* 80096180 00092D60  EC 23 00 32 */	fmuls f1, f3, f0
/* 80096184 00092D64  4B FE EE AD */	bl ft_80085030
/* 80096188 00092D68  48 00 00 18 */	b lbl_800961A0
lbl_8009618C:
/* 8009618C 00092D6C  C0 26 04 04 */	lfs f1, 0x404(r6)
/* 80096190 00092D70  C0 05 01 28 */	lfs f0, 0x128(r5)
/* 80096194 00092D74  C0 45 00 2C */	lfs f2, 0x2c(r5)
/* 80096198 00092D78  EC 21 00 32 */	fmuls f1, f1, f0
/* 8009619C 00092D7C  4B FE EE 95 */	bl ft_80085030
lbl_800961A0:
/* 800961A0 00092D80  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800961A4 00092D84  38 21 00 08 */	addi r1, r1, 8
/* 800961A8 00092D88  7C 08 03 A6 */	mtlr r0
/* 800961AC 00092D8C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_LightThrowDash_Phys(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCommonData* cd = p_ftCommonData;
    if (fp->cur_anim_frame <= cd->x408) {
        ft_80085030(gobj, cd->x40C * (cd->x404 * fp->co_attrs.gr_friction),
                    fp->facing_dir);
    } else {
        ft_80085030(gobj, p_ftCommonData->x404 * fp->co_attrs.gr_friction,
                    fp->facing_dir);
    }
}
#endif

void ftCo_LightThrowAir_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_800961D0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ft_80084DB0(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftCo_LightThrowDashDrop_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCo_LightThrow_Coll(ftCo_GObj* gobj)
{
    ft_800841B8(gobj, ftCo_80096250);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80096250(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80096250 00092E30  7C 08 02 A6 */	mflr r0
/* 80096254 00092E34  90 01 00 04 */	stw r0, 4(r1)
/* 80096258 00092E38  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8009625C 00092E3C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 80096260 00092E40  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80096264 00092E44  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80096268 00092E48  7C 7E 1B 78 */	mr r30, r3
/* 8009626C 00092E4C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80096270 00092E50  7F E3 FB 78 */	mr r3, r31
/* 80096274 00092E54  4B FE 73 61 */	bl ftCommon_8007D5D4
/* 80096278 00092E58  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 8009627C 00092E5C  2C 03 00 6C */	cmpwi r3, 0x6c
/* 80096280 00092E60  41 80 00 5C */	blt lbl_800962DC
/* 80096284 00092E64  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80096288 00092E68  38 83 00 04 */	addi r4, r3, 4
/* 8009628C 00092E6C  C3 FF 00 2C */	lfs f31, 0x2c(r31)
/* 80096290 00092E70  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 80096294 00092E74  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 80096298 00092E78  41 82 00 08 */	beq lbl_800962A0
/* 8009629C 00092E7C  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_800962A0:
/* 800962A0 00092E80  3C A0 0C 4C */	lis r5, 0x0C4C5080@ha
/* 800962A4 00092E84  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800962A8 00092E88  C0 5F 23 44 */	lfs f2, 0x2344(r31)
/* 800962AC 00092E8C  7F C3 F3 78 */	mr r3, r30
/* 800962B0 00092E90  C0 62 8B B0 */	lfs f3, ftCo_804D8590
/* 800962B4 00092E94  38 A5 50 80 */	addi r5, r5, 0x0C4C5080@l
/* 800962B8 00092E98  38 C0 00 00 */	li r6, 0
/* 800962BC 00092E9C  4B FD 30 F1 */	bl Fighter_ChangeMotionState
/* 800962C0 00092EA0  3C 60 80 09 */	lis r3, ftCo_80095EFC@ha
/* 800962C4 00092EA4  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 800962C8 00092EA8  38 03 5E FC */	addi r0, r3, ftCo_80095EFC@l
/* 800962CC 00092EAC  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 800962D0 00092EB0  7F C3 F3 78 */	mr r3, r30
/* 800962D4 00092EB4  4B FF FC 29 */	bl ftCo_80095EFC
/* 800962D8 00092EB8  48 00 00 58 */	b lbl_80096330
lbl_800962DC:
/* 800962DC 00092EBC  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800962E0 00092EC0  38 83 00 06 */	addi r4, r3, 6
/* 800962E4 00092EC4  C3 FF 00 2C */	lfs f31, 0x2c(r31)
/* 800962E8 00092EC8  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 800962EC 00092ECC  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 800962F0 00092ED0  41 82 00 08 */	beq lbl_800962F8
/* 800962F4 00092ED4  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_800962F8:
/* 800962F8 00092ED8  3C A0 0C 4C */	lis r5, 0x0C4C5080@ha
/* 800962FC 00092EDC  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 80096300 00092EE0  C0 5F 23 44 */	lfs f2, 0x2344(r31)
/* 80096304 00092EE4  7F C3 F3 78 */	mr r3, r30
/* 80096308 00092EE8  C0 62 8B B0 */	lfs f3, ftCo_804D8590
/* 8009630C 00092EEC  38 A5 50 80 */	addi r5, r5, 0x0C4C5080@l
/* 80096310 00092EF0  38 C0 00 00 */	li r6, 0
/* 80096314 00092EF4  4B FD 30 99 */	bl Fighter_ChangeMotionState
/* 80096318 00092EF8  3C 60 80 09 */	lis r3, ftCo_80095EFC@ha
/* 8009631C 00092EFC  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 80096320 00092F00  38 03 5E FC */	addi r0, r3, ftCo_80095EFC@l
/* 80096324 00092F04  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 80096328 00092F08  7F C3 F3 78 */	mr r3, r30
/* 8009632C 00092F0C  4B FF FB D1 */	bl ftCo_80095EFC
lbl_80096330:
/* 80096330 00092F10  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80096334 00092F14  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 80096338 00092F18  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8009633C 00092F1C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80096340 00092F20  38 21 00 28 */	addi r1, r1, 0x28
/* 80096344 00092F24  7C 08 03 A6 */	mtlr r0
/* 80096348 00092F28  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline void inlineA1(ftCo_GObj* gobj, FtMotionId msid)
{
    ftCo_Fighter* fp = gobj->user_data;
    float facing_dir = fp->facing_dir;
    if (facing_dir != fp->facing_dir1) {
        fp->facing_dir = fp->facing_dir1;
    }
    Fighter_ChangeMotionState(
        gobj, msid,
        Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
            Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
            Ft_MF_SkipModelFlags | Ft_MF_Unk27,
        NULL, fp->cur_anim_frame, fp->mv.co.itemthrow4.anim_spd, 0);
    fp->facing_dir = facing_dir;
}

static inline void inlineA0(ftCo_GObj* gobj, FtMotionId msid)
{
    ftCo_Fighter* fp = gobj->user_data;
    inlineA1(gobj, msid);
    fp->cb.x21BC_callback_Accessory4 = ftCo_80095EFC;
    ftCo_80095EFC(gobj);
}

void ftCo_80096250(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    if (fp->motion_id >= ftCo_MS_LightThrowF4) {
        inlineA0(gobj, fp->motion_id + 4);
    } else {
        inlineA0(gobj, fp->motion_id + 6);
    }
}
#endif

void ftCo_LightThrowAir_Coll(ftCo_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_80096374);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80096374(ftCo_GObj* gobj, float lag)
{ // clang-format off
    nofralloc
/* 80096374 00092F54  7C 08 02 A6 */	mflr r0
/* 80096378 00092F58  90 01 00 04 */	stw r0, 4(r1)
/* 8009637C 00092F5C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80096380 00092F60  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 80096384 00092F64  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80096388 00092F68  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8009638C 00092F6C  7C 7E 1B 78 */	mr r30, r3
/* 80096390 00092F70  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80096394 00092F74  7F E3 FB 78 */	mr r3, r31
/* 80096398 00092F78  4B FE 74 65 */	bl ftCommon_8007D7FC
/* 8009639C 00092F7C  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 800963A0 00092F80  2C 03 00 6C */	cmpwi r3, 0x6c
/* 800963A4 00092F84  41 80 00 5C */	blt lbl_80096400
/* 800963A8 00092F88  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800963AC 00092F8C  38 83 FF FC */	addi r4, r3, -4
/* 800963B0 00092F90  C3 FF 00 2C */	lfs f31, 0x2c(r31)
/* 800963B4 00092F94  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 800963B8 00092F98  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 800963BC 00092F9C  41 82 00 08 */	beq lbl_800963C4
/* 800963C0 00092FA0  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_800963C4:
/* 800963C4 00092FA4  3C A0 0C 4C */	lis r5, 0x0C4C5080@ha
/* 800963C8 00092FA8  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800963CC 00092FAC  C0 5F 23 44 */	lfs f2, 0x2344(r31)
/* 800963D0 00092FB0  7F C3 F3 78 */	mr r3, r30
/* 800963D4 00092FB4  C0 62 8B B0 */	lfs f3, ftCo_804D8590
/* 800963D8 00092FB8  38 A5 50 80 */	addi r5, r5, 0x0C4C5080@l
/* 800963DC 00092FBC  38 C0 00 00 */	li r6, 0
/* 800963E0 00092FC0  4B FD 2F CD */	bl Fighter_ChangeMotionState
/* 800963E4 00092FC4  3C 60 80 09 */	lis r3, ftCo_80095EFC@ha
/* 800963E8 00092FC8  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 800963EC 00092FCC  38 03 5E FC */	addi r0, r3, ftCo_80095EFC@l
/* 800963F0 00092FD0  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 800963F4 00092FD4  7F C3 F3 78 */	mr r3, r30
/* 800963F8 00092FD8  4B FF FB 05 */	bl ftCo_80095EFC
/* 800963FC 00092FDC  48 00 00 58 */	b lbl_80096454
lbl_80096400:
/* 80096400 00092FE0  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80096404 00092FE4  38 83 FF FA */	addi r4, r3, -6
/* 80096408 00092FE8  C3 FF 00 2C */	lfs f31, 0x2c(r31)
/* 8009640C 00092FEC  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 80096410 00092FF0  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 80096414 00092FF4  41 82 00 08 */	beq lbl_8009641C
/* 80096418 00092FF8  D0 1F 00 2C */	stfs f0, 0x2c(r31)
lbl_8009641C:
/* 8009641C 00092FFC  3C A0 0C 4C */	lis r5, 0x0C4C5080@ha
/* 80096420 00093000  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 80096424 00093004  C0 5F 23 44 */	lfs f2, 0x2344(r31)
/* 80096428 00093008  7F C3 F3 78 */	mr r3, r30
/* 8009642C 0009300C  C0 62 8B B0 */	lfs f3, ftCo_804D8590
/* 80096430 00093010  38 A5 50 80 */	addi r5, r5, 0x0C4C5080@l
/* 80096434 00093014  38 C0 00 00 */	li r6, 0
/* 80096438 00093018  4B FD 2F 75 */	bl Fighter_ChangeMotionState
/* 8009643C 0009301C  3C 60 80 09 */	lis r3, ftCo_80095EFC@ha
/* 80096440 00093020  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 80096444 00093024  38 03 5E FC */	addi r0, r3, ftCo_80095EFC@l
/* 80096448 00093028  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8009644C 0009302C  7F C3 F3 78 */	mr r3, r30
/* 80096450 00093030  4B FF FA AD */	bl ftCo_80095EFC
lbl_80096454:
/* 80096454 00093034  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80096458 00093038  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8009645C 0009303C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80096460 00093040  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80096464 00093044  38 21 00 28 */	addi r1, r1, 0x28
/* 80096468 00093048  7C 08 03 A6 */	mtlr r0
/* 8009646C 0009304C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80096374(ftCo_GObj* gobj, float lag)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    {
        int msid = fp->motion_id;
        if (msid >= ftCo_MS_LightThrowF4) {
            inlineA0(gobj, msid - 4);
        } else {
            inlineA0(gobj, msid - 6);
        }
    }
}
#endif

void ftCo_HeavyThrow_Coll(ftCo_GObj* gobj)
{
    ft_800841B8(gobj, ftCo_80096E68);
}

void ftCo_80096498(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == GA_Ground) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
    }
}
