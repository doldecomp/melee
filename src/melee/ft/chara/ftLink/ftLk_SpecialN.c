#include <platform.h>
#include "ft/forward.h"
#include "ftLink/forward.h"
#include "it/forward.h"

#include "ftLk_SpecialN.h"

#include "ftLk_Init.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_ItemGet.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>

#if defined(MWERKS_GEKKO) || defined(M2CTX)
/* static */ float const ftLk_Init_804D9340 = 0.0;
/* static */ float const ftLk_Init_804D9344 = 5 * deg_to_rad;
/* static */ double const ftLk_Init_804D9348 = 0.0078125;
#endif

typedef enum cmd_var_idx {
    cmd_unk0_bool,
    cmd_unk1_bool,
    cmd_unk2,
    cmd_unk3,
} cmd_var_idx;

ftLk_SpecialNIndex ftLk_SpecialN_GetIndex(ftLk_GObj* gobj)
{
    ftLk_SpecialNIndex result = ftLk_SpecialNIndex_None;
    if (gobj != NULL) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.x14 != NULL) {
            FtMotionId msid = fp->motion_id;
            switch (msid) {
            case ftLk_MS_SpecialNStart:
            case ftLk_MS_SpecialNLoop:
            case ftLk_MS_SpecialNEnd:
            case ftLk_MS_SpecialAirNStart:
            case ftLk_MS_SpecialAirNLoop:
            case ftLk_MS_SpecialAirNEnd:
                result = msid - ftLk_MS_SpecialNStart;
            }
        }
    }
    return result;
}

void ftLk_SpecialN_UnsetArrow(ftLk_GObj* gobj)
{
    if (gobj != NULL) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.arrow_gobj != NULL) {
            fp->fv.lk.arrow_gobj = NULL;
            if (fp->fv.lk.boomerang_gobj == NULL && fp->fv.lk.x14 == NULL) {
                /// @todo Does this actually do anything? Doesn't seem to
                /// return @c bool.
                ftLk_Init_BoomerangExists(gobj);
            }
        }
    }
}

void ftLk_SpecialN_UnsetFv14(ftLk_GObj* gobj)
{
    if (gobj != NULL) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.x14 != NULL) {
            fp->fv.lk.x14 = NULL;
            if (fp->fv.lk.boomerang_gobj == NULL &&
                fp->fv.lk.arrow_gobj == NULL)
            {
                /// @todo Does this actually do anything? Doesn't seem to
                /// return @c bool.
                ftLk_Init_BoomerangExists(gobj);
            }
        }
    }
}

bool ftLk_SpecialN_IsActiveAnd2071b6(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->motion_id) {
    case ftLk_MS_SpecialNStart:
    case ftLk_MS_SpecialNLoop:
    case ftLk_MS_SpecialNEnd:
    case ftLk_MS_SpecialAirNStart:
    case ftLk_MS_SpecialAirNLoop:
    case ftLk_MS_SpecialAirNEnd:
        if (!fp->x2070.x2071_b6) {
            return false;
        }
        /// @attention Fall-through.
    default:
        return true;
    }
}

void ftLk_SpecialN_ProcessFv10(ftLk_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8A7C(fp->fv.lk.arrow_gobj);
        fp->fv.lk.arrow_gobj = NULL;
        ftLk_Init_BoomerangExists(gobj);
    }
}

void ftLk_SpecialN_ProcessFv14(ftLk_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.x14 != NULL) {
        it_802AF304(fp->fv.lk.x14);
        fp->fv.lk.x14 = NULL;
        ftLk_Init_BoomerangExists(gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialN_Enter(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800ECDAC 000E998C  7C 08 02 A6 */	mflr r0
/* 800ECDB0 000E9990  90 01 00 04 */	stw r0, 4(r1)
/* 800ECDB4 000E9994  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 800ECDB8 000E9998  BF 61 00 54 */	stmw r27, 0x54(r1)
/* 800ECDBC 000E999C  3B A0 00 00 */	li r29, 0
/* 800ECDC0 000E99A0  7C 7F 1B 78 */	mr r31, r3
/* 800ECDC4 000E99A4  83 63 00 2C */	lwz r27, 0x2c(r3)
/* 800ECDC8 000E99A8  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800ECDCC 000E99AC  83 9B 02 D4 */	lwz r28, 0x2d4(r27)
/* 800ECDD0 000E99B0  7F 63 DB 78 */	mr r3, r27
/* 800ECDD4 000E99B4  D0 1B 23 44 */	stfs f0, 0x2344(r27)
/* 800ECDD8 000E99B8  D0 1B 23 40 */	stfs f0, 0x2340(r27)
/* 800ECDDC 000E99BC  93 BB 23 58 */	stw r29, 0x2358(r27)
/* 800ECDE0 000E99C0  93 BB 22 0C */	stw r29, 0x220c(r27)
/* 800ECDE4 000E99C4  93 BB 22 08 */	stw r29, 0x2208(r27)
/* 800ECDE8 000E99C8  93 BB 22 04 */	stw r29, 0x2204(r27)
/* 800ECDEC 000E99CC  93 BB 22 00 */	stw r29, 0x2200(r27)
/* 800ECDF0 000E99D0  4B F9 0A 0D */	bl ftCommon_8007D7FC
/* 800ECDF4 000E99D4  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800ECDF8 000E99D8  38 7F 00 00 */	addi r3, r31, 0
/* 800ECDFC 000E99DC  38 80 01 58 */	li r4, 0x158
/* 800ECE00 000E99E0  D0 3B 00 84 */	stfs f1, 0x84(r27)
/* 800ECE04 000E99E4  FC 60 08 90 */	fmr f3, f1
/* 800ECE08 000E99E8  38 A0 00 00 */	li r5, 0
/* 800ECE0C 000E99EC  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800ECE10 000E99F0  38 C0 00 00 */	li r6, 0
/* 800ECE14 000E99F4  4B F7 C5 99 */	bl Fighter_ChangeMotionState
/* 800ECE18 000E99F8  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800ECE1C 000E99FC  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800ECE20 000E9A00  3B C3 AF 58 */	addi r30, r3, ftLk_800EAF58@l
/* 800ECE24 000E9A04  93 C4 21 DC */	stw r30, 0x21dc(r4)
/* 800ECE28 000E9A08  7F E3 FB 78 */	mr r3, r31
/* 800ECE2C 000E9A0C  93 C4 21 E4 */	stw r30, 0x21e4(r4)
/* 800ECE30 000E9A10  C0 3C 00 04 */	lfs f1, 4(r28)
/* 800ECE34 000E9A14  4B F8 23 5D */	bl ftAnim_SetAnimRate
/* 800ECE38 000E9A18  7F E3 FB 78 */	mr r3, r31
/* 800ECE3C 000E9A1C  4B F8 1D 69 */	bl ftAnim_8006EBA4
/* 800ECE40 000E9A20  83 7F 00 2C */	lwz r27, 0x2c(r31)
/* 800ECE44 000E9A24  80 1B 22 40 */	lwz r0, 0x2240(r27)
/* 800ECE48 000E9A28  83 9B 02 D4 */	lwz r28, 0x2d4(r27)
/* 800ECE4C 000E9A2C  28 00 00 00 */	cmplwi r0, 0
/* 800ECE50 000E9A30  40 82 00 70 */	bne lbl_800ECEC0
/* 800ECE54 000E9A34  38 7B 00 00 */	addi r3, r27, 0
/* 800ECE58 000E9A38  38 80 00 31 */	li r4, 0x31
/* 800ECE5C 000E9A3C  4B F8 81 B1 */	bl ftParts_8007500C
/* 800ECE60 000E9A40  80 9B 05 E8 */	lwz r4, 0x5e8(r27)
/* 800ECE64 000E9A44  54 60 20 36 */	slwi r0, r3, 4
/* 800ECE68 000E9A48  38 A1 00 44 */	addi r5, r1, 0x44
/* 800ECE6C 000E9A4C  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ECE70 000E9A50  38 80 00 00 */	li r4, 0
/* 800ECE74 000E9A54  4B F1 E3 59 */	bl lb_8000B1CC
/* 800ECE78 000E9A58  38 7B 00 00 */	addi r3, r27, 0
/* 800ECE7C 000E9A5C  38 80 00 31 */	li r4, 0x31
/* 800ECE80 000E9A60  4B F8 81 8D */	bl ftParts_8007500C
/* 800ECE84 000E9A64  C0 3B 00 2C */	lfs f1, 0x2c(r27)
/* 800ECE88 000E9A68  7C 65 1B 78 */	mr r5, r3
/* 800ECE8C 000E9A6C  80 DC 00 10 */	lwz r6, 0x10(r28)
/* 800ECE90 000E9A70  38 7F 00 00 */	addi r3, r31, 0
/* 800ECE94 000E9A74  38 81 00 44 */	addi r4, r1, 0x44
/* 800ECE98 000E9A78  48 1C 23 0D */	bl it_802AF1A4
/* 800ECE9C 000E9A7C  28 03 00 00 */	cmplwi r3, 0
/* 800ECEA0 000E9A80  90 7B 22 40 */	stw r3, 0x2240(r27)
/* 800ECEA4 000E9A84  41 82 00 14 */	beq lbl_800ECEB8
/* 800ECEA8 000E9A88  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 800ECEAC 000E9A8C  93 C3 21 DC */	stw r30, 0x21dc(r3)
/* 800ECEB0 000E9A90  93 C3 21 E4 */	stw r30, 0x21e4(r3)
/* 800ECEB4 000E9A94  48 00 00 10 */	b lbl_800ECEC4
lbl_800ECEB8:
/* 800ECEB8 000E9A98  3B A0 00 01 */	li r29, 1
/* 800ECEBC 000E9A9C  48 00 00 08 */	b lbl_800ECEC4
lbl_800ECEC0:
/* 800ECEC0 000E9AA0  3B A0 00 01 */	li r29, 1
lbl_800ECEC4:
/* 800ECEC4 000E9AA4  2C 1D 00 01 */	cmpwi r29, 1
/* 800ECEC8 000E9AA8  40 82 00 9C */	bne lbl_800ECF64
/* 800ECECC 000E9AAC  28 1F 00 00 */	cmplwi r31, 0
/* 800ECED0 000E9AB0  41 82 00 44 */	beq lbl_800ECF14
/* 800ECED4 000E9AB4  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 800ECED8 000E9AB8  28 03 00 00 */	cmplwi r3, 0
/* 800ECEDC 000E9ABC  41 82 00 38 */	beq lbl_800ECF14
/* 800ECEE0 000E9AC0  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800ECEE4 000E9AC4  28 00 00 00 */	cmplwi r0, 0
/* 800ECEE8 000E9AC8  41 82 00 2C */	beq lbl_800ECF14
/* 800ECEEC 000E9ACC  38 00 00 00 */	li r0, 0
/* 800ECEF0 000E9AD0  90 03 22 3C */	stw r0, 0x223c(r3)
/* 800ECEF4 000E9AD4  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ECEF8 000E9AD8  28 00 00 00 */	cmplwi r0, 0
/* 800ECEFC 000E9ADC  40 82 00 18 */	bne lbl_800ECF14
/* 800ECF00 000E9AE0  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ECF04 000E9AE4  28 00 00 00 */	cmplwi r0, 0
/* 800ECF08 000E9AE8  40 82 00 0C */	bne lbl_800ECF14
/* 800ECF0C 000E9AEC  7F E3 FB 78 */	mr r3, r31
/* 800ECF10 000E9AF0  4B FF DE 55 */	bl ftLk_Init_BoomerangExists
lbl_800ECF14:
/* 800ECF14 000E9AF4  28 1F 00 00 */	cmplwi r31, 0
/* 800ECF18 000E9AF8  41 82 00 44 */	beq lbl_800ECF5C
/* 800ECF1C 000E9AFC  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 800ECF20 000E9B00  28 03 00 00 */	cmplwi r3, 0
/* 800ECF24 000E9B04  41 82 00 38 */	beq lbl_800ECF5C
/* 800ECF28 000E9B08  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ECF2C 000E9B0C  28 00 00 00 */	cmplwi r0, 0
/* 800ECF30 000E9B10  41 82 00 2C */	beq lbl_800ECF5C
/* 800ECF34 000E9B14  38 00 00 00 */	li r0, 0
/* 800ECF38 000E9B18  90 03 22 40 */	stw r0, 0x2240(r3)
/* 800ECF3C 000E9B1C  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ECF40 000E9B20  28 00 00 00 */	cmplwi r0, 0
/* 800ECF44 000E9B24  40 82 00 18 */	bne lbl_800ECF5C
/* 800ECF48 000E9B28  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800ECF4C 000E9B2C  28 00 00 00 */	cmplwi r0, 0
/* 800ECF50 000E9B30  40 82 00 0C */	bne lbl_800ECF5C
/* 800ECF54 000E9B34  7F E3 FB 78 */	mr r3, r31
/* 800ECF58 000E9B38  4B FF DE 0D */	bl ftLk_Init_BoomerangExists
lbl_800ECF5C:
/* 800ECF5C 000E9B3C  7F E3 FB 78 */	mr r3, r31
/* 800ECF60 000E9B40  4B F9 D3 5D */	bl ft_8008A2BC
lbl_800ECF64:
/* 800ECF64 000E9B44  BB 61 00 54 */	lmw r27, 0x54(r1)
/* 800ECF68 000E9B48  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 800ECF6C 000E9B4C  38 21 00 68 */	addi r1, r1, 0x68
/* 800ECF70 000E9B50  7C 08 03 A6 */	mtlr r0
/* 800ECF74 000E9B54  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline void setCallbacks(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = ftLk_800EAF58;
    fp->cb.x21E4_callback_OnDeath2 = ftLk_800EAF58;
}

static inline bool unkCondition(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.lk.x14 == NULL) {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[36] = { 0 };
#endif
        Vec3 pos;
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                    NULL, &pos);
        {
            Item_GObj* fv_x14 =
                it_802AF1A4(fp->facing_dir, gobj, &pos,
                            ftParts_8007500C(fp, FtPart_RThumbNb), da->x10);
            fp->fv.lk.x14 = fv_x14;
            if (fv_x14 != NULL) {
                setCallbacks(gobj);
            } else {
                return true;
            }
        }
    } else {
        return true;
    }
    return false;
}

void ftLk_SpecialN_Enter(ftLk_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    ftLk_Fighter* fp = gobj->user_data;
    ftLk_DatAttrs* da = fp->dat_attrs;
    fp->mv.lk.specialn.x0.x = fp->mv.lk.specialn.x0.y = 0;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNStart, Ft_MF_None, NULL, 0,
                              1, 0);
    setCallbacks(gobj);
    ftAnim_SetAnimRate(gobj, da->specialn_anim_rate);
    ftAnim_8006EBA4(gobj);
    if (unkCondition(gobj) == true) {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        ft_8008A2BC(gobj);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirN_Enter(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800ECF78 000E9B58  7C 08 02 A6 */	mflr r0
/* 800ECF7C 000E9B5C  38 80 01 5B */	li r4, 0x15b
/* 800ECF80 000E9B60  90 01 00 04 */	stw r0, 4(r1)
/* 800ECF84 000E9B64  38 A0 00 00 */	li r5, 0
/* 800ECF88 000E9B68  38 C0 00 00 */	li r6, 0
/* 800ECF8C 000E9B6C  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 800ECF90 000E9B70  BF 41 00 50 */	stmw r26, 0x50(r1)
/* 800ECF94 000E9B74  3B 80 00 00 */	li r28, 0
/* 800ECF98 000E9B78  7C 7E 1B 78 */	mr r30, r3
/* 800ECF9C 000E9B7C  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 800ECFA0 000E9B80  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800ECFA4 000E9B84  83 E7 02 D4 */	lwz r31, 0x2d4(r7)
/* 800ECFA8 000E9B88  FC 60 08 90 */	fmr f3, f1
/* 800ECFAC 000E9B8C  D0 27 23 44 */	stfs f1, 0x2344(r7)
/* 800ECFB0 000E9B90  D0 27 23 40 */	stfs f1, 0x2340(r7)
/* 800ECFB4 000E9B94  93 87 23 58 */	stw r28, 0x2358(r7)
/* 800ECFB8 000E9B98  93 87 22 0C */	stw r28, 0x220c(r7)
/* 800ECFBC 000E9B9C  93 87 22 08 */	stw r28, 0x2208(r7)
/* 800ECFC0 000E9BA0  93 87 22 04 */	stw r28, 0x2204(r7)
/* 800ECFC4 000E9BA4  93 87 22 00 */	stw r28, 0x2200(r7)
/* 800ECFC8 000E9BA8  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800ECFCC 000E9BAC  4B F7 C3 E1 */	bl Fighter_ChangeMotionState
/* 800ECFD0 000E9BB0  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800ECFD4 000E9BB4  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800ECFD8 000E9BB8  3B A3 AF 58 */	addi r29, r3, ftLk_800EAF58@l
/* 800ECFDC 000E9BBC  93 A4 21 DC */	stw r29, 0x21dc(r4)
/* 800ECFE0 000E9BC0  7F C3 F3 78 */	mr r3, r30
/* 800ECFE4 000E9BC4  93 A4 21 E4 */	stw r29, 0x21e4(r4)
/* 800ECFE8 000E9BC8  C0 3F 00 04 */	lfs f1, 4(r31)
/* 800ECFEC 000E9BCC  4B F8 21 A5 */	bl ftAnim_SetAnimRate
/* 800ECFF0 000E9BD0  7F C3 F3 78 */	mr r3, r30
/* 800ECFF4 000E9BD4  4B F8 1B B1 */	bl ftAnim_8006EBA4
/* 800ECFF8 000E9BD8  83 5E 00 2C */	lwz r26, 0x2c(r30)
/* 800ECFFC 000E9BDC  80 1A 22 40 */	lwz r0, 0x2240(r26)
/* 800ED000 000E9BE0  83 7A 02 D4 */	lwz r27, 0x2d4(r26)
/* 800ED004 000E9BE4  28 00 00 00 */	cmplwi r0, 0
/* 800ED008 000E9BE8  40 82 00 70 */	bne lbl_800ED078
/* 800ED00C 000E9BEC  38 7A 00 00 */	addi r3, r26, 0
/* 800ED010 000E9BF0  38 80 00 31 */	li r4, 0x31
/* 800ED014 000E9BF4  4B F8 7F F9 */	bl ftParts_8007500C
/* 800ED018 000E9BF8  80 9A 05 E8 */	lwz r4, 0x5e8(r26)
/* 800ED01C 000E9BFC  54 60 20 36 */	slwi r0, r3, 4
/* 800ED020 000E9C00  38 A1 00 44 */	addi r5, r1, 0x44
/* 800ED024 000E9C04  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED028 000E9C08  38 80 00 00 */	li r4, 0
/* 800ED02C 000E9C0C  4B F1 E1 A1 */	bl lb_8000B1CC
/* 800ED030 000E9C10  38 7A 00 00 */	addi r3, r26, 0
/* 800ED034 000E9C14  38 80 00 31 */	li r4, 0x31
/* 800ED038 000E9C18  4B F8 7F D5 */	bl ftParts_8007500C
/* 800ED03C 000E9C1C  C0 3A 00 2C */	lfs f1, 0x2c(r26)
/* 800ED040 000E9C20  7C 65 1B 78 */	mr r5, r3
/* 800ED044 000E9C24  80 DB 00 10 */	lwz r6, 0x10(r27)
/* 800ED048 000E9C28  38 7E 00 00 */	addi r3, r30, 0
/* 800ED04C 000E9C2C  38 81 00 44 */	addi r4, r1, 0x44
/* 800ED050 000E9C30  48 1C 21 55 */	bl it_802AF1A4
/* 800ED054 000E9C34  28 03 00 00 */	cmplwi r3, 0
/* 800ED058 000E9C38  90 7A 22 40 */	stw r3, 0x2240(r26)
/* 800ED05C 000E9C3C  41 82 00 14 */	beq lbl_800ED070
/* 800ED060 000E9C40  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 800ED064 000E9C44  93 A3 21 DC */	stw r29, 0x21dc(r3)
/* 800ED068 000E9C48  93 A3 21 E4 */	stw r29, 0x21e4(r3)
/* 800ED06C 000E9C4C  48 00 00 10 */	b lbl_800ED07C
lbl_800ED070:
/* 800ED070 000E9C50  3B 80 00 01 */	li r28, 1
/* 800ED074 000E9C54  48 00 00 08 */	b lbl_800ED07C
lbl_800ED078:
/* 800ED078 000E9C58  3B 80 00 01 */	li r28, 1
lbl_800ED07C:
/* 800ED07C 000E9C5C  2C 1C 00 01 */	cmpwi r28, 1
/* 800ED080 000E9C60  40 82 00 C8 */	bne lbl_800ED148
/* 800ED084 000E9C64  28 1E 00 00 */	cmplwi r30, 0
/* 800ED088 000E9C68  41 82 00 44 */	beq lbl_800ED0CC
/* 800ED08C 000E9C6C  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 800ED090 000E9C70  28 03 00 00 */	cmplwi r3, 0
/* 800ED094 000E9C74  41 82 00 38 */	beq lbl_800ED0CC
/* 800ED098 000E9C78  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800ED09C 000E9C7C  28 00 00 00 */	cmplwi r0, 0
/* 800ED0A0 000E9C80  41 82 00 2C */	beq lbl_800ED0CC
/* 800ED0A4 000E9C84  38 00 00 00 */	li r0, 0
/* 800ED0A8 000E9C88  90 03 22 3C */	stw r0, 0x223c(r3)
/* 800ED0AC 000E9C8C  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ED0B0 000E9C90  28 00 00 00 */	cmplwi r0, 0
/* 800ED0B4 000E9C94  40 82 00 18 */	bne lbl_800ED0CC
/* 800ED0B8 000E9C98  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ED0BC 000E9C9C  28 00 00 00 */	cmplwi r0, 0
/* 800ED0C0 000E9CA0  40 82 00 0C */	bne lbl_800ED0CC
/* 800ED0C4 000E9CA4  7F C3 F3 78 */	mr r3, r30
/* 800ED0C8 000E9CA8  4B FF DC 9D */	bl ftLk_Init_BoomerangExists
lbl_800ED0CC:
/* 800ED0CC 000E9CAC  28 1E 00 00 */	cmplwi r30, 0
/* 800ED0D0 000E9CB0  41 82 00 44 */	beq lbl_800ED114
/* 800ED0D4 000E9CB4  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 800ED0D8 000E9CB8  28 03 00 00 */	cmplwi r3, 0
/* 800ED0DC 000E9CBC  41 82 00 38 */	beq lbl_800ED114
/* 800ED0E0 000E9CC0  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ED0E4 000E9CC4  28 00 00 00 */	cmplwi r0, 0
/* 800ED0E8 000E9CC8  41 82 00 2C */	beq lbl_800ED114
/* 800ED0EC 000E9CCC  38 00 00 00 */	li r0, 0
/* 800ED0F0 000E9CD0  90 03 22 40 */	stw r0, 0x2240(r3)
/* 800ED0F4 000E9CD4  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ED0F8 000E9CD8  28 00 00 00 */	cmplwi r0, 0
/* 800ED0FC 000E9CDC  40 82 00 18 */	bne lbl_800ED114
/* 800ED100 000E9CE0  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800ED104 000E9CE4  28 00 00 00 */	cmplwi r0, 0
/* 800ED108 000E9CE8  40 82 00 0C */	bne lbl_800ED114
/* 800ED10C 000E9CEC  7F C3 F3 78 */	mr r3, r30
/* 800ED110 000E9CF0  4B FF DC 55 */	bl ftLk_Init_BoomerangExists
lbl_800ED114:
/* 800ED114 000E9CF4  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800ED118 000E9CF8  C0 5F 00 08 */	lfs f2, 8(r31)
/* 800ED11C 000E9CFC  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 800ED120 000E9D00  40 82 00 10 */	bne lbl_800ED130
/* 800ED124 000E9D04  7F C3 F3 78 */	mr r3, r30
/* 800ED128 000E9D08  4B FD F6 09 */	bl ftCo_800CC730
/* 800ED12C 000E9D0C  48 00 00 1C */	b lbl_800ED148
lbl_800ED130:
/* 800ED130 000E9D10  C0 22 99 68 */	lfs f1, ftLk_Init_804D9348
/* 800ED134 000E9D14  38 7E 00 00 */	addi r3, r30, 0
/* 800ED138 000E9D18  38 80 00 01 */	li r4, 1
/* 800ED13C 000E9D1C  38 A0 00 00 */	li r5, 0
/* 800ED140 000E9D20  38 C0 00 01 */	li r6, 1
/* 800ED144 000E9D24  4B FA 97 BD */	bl ftCo_80096900
lbl_800ED148:
/* 800ED148 000E9D28  BB 41 00 50 */	lmw r26, 0x50(r1)
/* 800ED14C 000E9D2C  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 800ED150 000E9D30  38 21 00 68 */	addi r1, r1, 0x68
/* 800ED154 000E9D34  7C 08 03 A6 */	mtlr r0
/* 800ED158 000E9D38  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo Share more code with #ftLk_SpecialN_Enter.
void ftLk_SpecialAirN_Enter(ftLk_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    ftLk_Fighter* fp = gobj->user_data;
    ftLk_DatAttrs* da = fp->dat_attrs;
    fp->mv.lk.specialn.x0.x = fp->mv.lk.specialn.x0.y = 0;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNStart, Ft_MF_None, NULL,
                              0, 1, 0);
    setCallbacks(gobj);
    ftAnim_SetAnimRate(gobj, da->specialn_anim_rate);
    ftAnim_8006EBA4(gobj);
    if (unkCondition(gobj) == true) {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        if (da->x8 == 0) {
            ftCo_800CC730(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x8);
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialNStart_Anim(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800ED15C 000E9D3C  7C 08 02 A6 */	mflr r0
/* 800ED160 000E9D40  90 01 00 04 */	stw r0, 4(r1)
/* 800ED164 000E9D44  94 21 FF 78 */	stwu r1, -0x88(r1)
/* 800ED168 000E9D48  93 E1 00 84 */	stw r31, 0x84(r1)
/* 800ED16C 000E9D4C  93 C1 00 80 */	stw r30, 0x80(r1)
/* 800ED170 000E9D50  7C 7E 1B 78 */	mr r30, r3
/* 800ED174 000E9D54  93 A1 00 7C */	stw r29, 0x7c(r1)
/* 800ED178 000E9D58  93 81 00 78 */	stw r28, 0x78(r1)
/* 800ED17C 000E9D5C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800ED180 000E9D60  3C 60 80 3B */	lis r3, ftLk_Init_Vec3Group@ha
/* 800ED184 000E9D64  3B E3 75 20 */	addi r31, r3, ftLk_Init_Vec3Group@l
/* 800ED188 000E9D68  80 04 22 08 */	lwz r0, 0x2208(r4)
/* 800ED18C 000E9D6C  80 A4 02 D4 */	lwz r5, 0x2d4(r4)
/* 800ED190 000E9D70  28 00 00 00 */	cmplwi r0, 0
/* 800ED194 000E9D74  41 82 00 24 */	beq lbl_800ED1B8
/* 800ED198 000E9D78  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800ED19C 000E9D7C  C0 04 23 40 */	lfs f0, 0x2340(r4)
/* 800ED1A0 000E9D80  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800ED1A4 000E9D84  40 82 00 14 */	bne lbl_800ED1B8
/* 800ED1A8 000E9D88  C0 02 99 68 */	lfs f0, ftLk_Init_804D9348
/* 800ED1AC 000E9D8C  38 00 00 00 */	li r0, 0
/* 800ED1B0 000E9D90  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 800ED1B4 000E9D94  90 04 22 08 */	stw r0, 0x2208(r4)
lbl_800ED1B8:
/* 800ED1B8 000E9D98  7F C3 F3 78 */	mr r3, r30
/* 800ED1BC 000E9D9C  C0 25 00 04 */	lfs f1, 4(r5)
/* 800ED1C0 000E9DA0  4B F8 1F D1 */	bl ftAnim_SetAnimRate
/* 800ED1C4 000E9DA4  83 9E 00 2C */	lwz r28, 0x2c(r30)
/* 800ED1C8 000E9DA8  80 1C 22 00 */	lwz r0, 0x2200(r28)
/* 800ED1CC 000E9DAC  83 BC 02 D4 */	lwz r29, 0x2d4(r28)
/* 800ED1D0 000E9DB0  28 00 00 01 */	cmplwi r0, 1
/* 800ED1D4 000E9DB4  40 82 00 8C */	bne lbl_800ED260
/* 800ED1D8 000E9DB8  80 1C 22 3C */	lwz r0, 0x223c(r28)
/* 800ED1DC 000E9DBC  28 00 00 00 */	cmplwi r0, 0
/* 800ED1E0 000E9DC0  40 82 00 80 */	bne lbl_800ED260
/* 800ED1E4 000E9DC4  38 00 00 00 */	li r0, 0
/* 800ED1E8 000E9DC8  90 1C 22 00 */	stw r0, 0x2200(r28)
/* 800ED1EC 000E9DCC  38 7C 00 00 */	addi r3, r28, 0
/* 800ED1F0 000E9DD0  38 80 00 1F */	li r4, 0x1f
/* 800ED1F4 000E9DD4  4B F8 7E 19 */	bl ftParts_8007500C
/* 800ED1F8 000E9DD8  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 800ED1FC 000E9DDC  54 60 20 36 */	slwi r0, r3, 4
/* 800ED200 000E9DE0  38 A1 00 6C */	addi r5, r1, 0x6c
/* 800ED204 000E9DE4  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED208 000E9DE8  38 80 00 00 */	li r4, 0
/* 800ED20C 000E9DEC  4B F1 DF C1 */	bl lb_8000B1CC
/* 800ED210 000E9DF0  38 7C 00 00 */	addi r3, r28, 0
/* 800ED214 000E9DF4  38 80 00 1F */	li r4, 0x1f
/* 800ED218 000E9DF8  4B F8 7D F5 */	bl ftParts_8007500C
/* 800ED21C 000E9DFC  C0 3C 00 2C */	lfs f1, 0x2c(r28)
/* 800ED220 000E9E00  7C 65 1B 78 */	mr r5, r3
/* 800ED224 000E9E04  80 DD 00 0C */	lwz r6, 0xc(r29)
/* 800ED228 000E9E08  38 7E 00 00 */	addi r3, r30, 0
/* 800ED22C 000E9E0C  38 81 00 6C */	addi r4, r1, 0x6c
/* 800ED230 000E9E10  48 1B B1 B1 */	bl it_802A83E0
/* 800ED234 000E9E14  28 03 00 00 */	cmplwi r3, 0
/* 800ED238 000E9E18  90 7C 22 3C */	stw r3, 0x223c(r28)
/* 800ED23C 000E9E1C  41 82 00 1C */	beq lbl_800ED258
/* 800ED240 000E9E20  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800ED244 000E9E24  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800ED248 000E9E28  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800ED24C 000E9E2C  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800ED250 000E9E30  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800ED254 000E9E34  48 00 00 0C */	b lbl_800ED260
lbl_800ED258:
/* 800ED258 000E9E38  38 00 00 01 */	li r0, 1
/* 800ED25C 000E9E3C  48 00 00 08 */	b lbl_800ED264
lbl_800ED260:
/* 800ED260 000E9E40  38 00 00 00 */	li r0, 0
lbl_800ED264:
/* 800ED264 000E9E44  2C 00 00 00 */	cmpwi r0, 0
/* 800ED268 000E9E48  40 82 01 60 */	bne lbl_800ED3C8
/* 800ED26C 000E9E4C  83 9E 00 2C */	lwz r28, 0x2c(r30)
/* 800ED270 000E9E50  38 80 00 1F */	li r4, 0x1f
/* 800ED274 000E9E54  80 BF 00 00 */	lwz r5, 0(r31)
/* 800ED278 000E9E58  80 1F 00 04 */	lwz r0, 4(r31)
/* 800ED27C 000E9E5C  7F 83 E3 78 */	mr r3, r28
/* 800ED280 000E9E60  90 A1 00 48 */	stw r5, 0x48(r1)
/* 800ED284 000E9E64  90 01 00 4C */	stw r0, 0x4c(r1)
/* 800ED288 000E9E68  80 1F 00 08 */	lwz r0, 8(r31)
/* 800ED28C 000E9E6C  90 01 00 50 */	stw r0, 0x50(r1)
/* 800ED290 000E9E70  80 BF 00 0C */	lwz r5, 0xc(r31)
/* 800ED294 000E9E74  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800ED298 000E9E78  90 A1 00 54 */	stw r5, 0x54(r1)
/* 800ED29C 000E9E7C  90 01 00 58 */	stw r0, 0x58(r1)
/* 800ED2A0 000E9E80  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 800ED2A4 000E9E84  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800ED2A8 000E9E88  80 BF 00 18 */	lwz r5, 0x18(r31)
/* 800ED2AC 000E9E8C  80 1F 00 1C */	lwz r0, 0x1c(r31)
/* 800ED2B0 000E9E90  90 A1 00 60 */	stw r5, 0x60(r1)
/* 800ED2B4 000E9E94  90 01 00 64 */	stw r0, 0x64(r1)
/* 800ED2B8 000E9E98  80 1F 00 20 */	lwz r0, 0x20(r31)
/* 800ED2BC 000E9E9C  90 01 00 68 */	stw r0, 0x68(r1)
/* 800ED2C0 000E9EA0  4B F8 7D 4D */	bl ftParts_8007500C
/* 800ED2C4 000E9EA4  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 800ED2C8 000E9EA8  54 60 20 36 */	slwi r0, r3, 4
/* 800ED2CC 000E9EAC  38 A1 00 48 */	addi r5, r1, 0x48
/* 800ED2D0 000E9EB0  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED2D4 000E9EB4  38 80 00 00 */	li r4, 0
/* 800ED2D8 000E9EB8  4B F1 DE F5 */	bl lb_8000B1CC
/* 800ED2DC 000E9EBC  38 7C 00 00 */	addi r3, r28, 0
/* 800ED2E0 000E9EC0  38 80 00 31 */	li r4, 0x31
/* 800ED2E4 000E9EC4  4B F8 7D 29 */	bl ftParts_8007500C
/* 800ED2E8 000E9EC8  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 800ED2EC 000E9ECC  54 60 20 36 */	slwi r0, r3, 4
/* 800ED2F0 000E9ED0  38 A1 00 54 */	addi r5, r1, 0x54
/* 800ED2F4 000E9ED4  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED2F8 000E9ED8  38 80 00 00 */	li r4, 0
/* 800ED2FC 000E9EDC  4B F1 DE D1 */	bl lb_8000B1CC
/* 800ED300 000E9EE0  80 7C 05 E8 */	lwz r3, 0x5e8(r28)
/* 800ED304 000E9EE4  38 A1 00 60 */	addi r5, r1, 0x60
/* 800ED308 000E9EE8  38 80 00 00 */	li r4, 0
/* 800ED30C 000E9EEC  80 63 00 00 */	lwz r3, 0(r3)
/* 800ED310 000E9EF0  4B F1 DE BD */	bl lb_8000B1CC
/* 800ED314 000E9EF4  C0 21 00 54 */	lfs f1, 0x54(r1)
/* 800ED318 000E9EF8  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 800ED31C 000E9EFC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800ED320 000E9F00  D0 1C 23 4C */	stfs f0, 0x234c(r28)
/* 800ED324 000E9F04  C0 21 00 58 */	lfs f1, 0x58(r1)
/* 800ED328 000E9F08  C0 01 00 64 */	lfs f0, 0x64(r1)
/* 800ED32C 000E9F0C  EC 01 00 28 */	fsubs f0, f1, f0
/* 800ED330 000E9F10  D0 1C 23 50 */	stfs f0, 0x2350(r28)
/* 800ED334 000E9F14  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800ED338 000E9F18  D0 1C 23 54 */	stfs f0, 0x2354(r28)
/* 800ED33C 000E9F1C  C0 61 00 58 */	lfs f3, 0x58(r1)
/* 800ED340 000E9F20  C0 21 00 4C */	lfs f1, 0x4c(r1)
/* 800ED344 000E9F24  C0 41 00 54 */	lfs f2, 0x54(r1)
/* 800ED348 000E9F28  C0 01 00 48 */	lfs f0, 0x48(r1)
/* 800ED34C 000E9F2C  EC 23 08 28 */	fsubs f1, f3, f1
/* 800ED350 000E9F30  EC 42 00 28 */	fsubs f2, f2, f0
/* 800ED354 000E9F34  4B F3 58 DD */	bl atan2f
/* 800ED358 000E9F38  D0 3C 23 48 */	stfs f1, 0x2348(r28)
/* 800ED35C 000E9F3C  80 7C 22 3C */	lwz r3, 0x223c(r28)
/* 800ED360 000E9F40  28 03 00 00 */	cmplwi r3, 0
/* 800ED364 000E9F44  41 82 00 10 */	beq lbl_800ED374
/* 800ED368 000E9F48  38 81 00 54 */	addi r4, r1, 0x54
/* 800ED36C 000E9F4C  38 A1 00 48 */	addi r5, r1, 0x48
/* 800ED370 000E9F50  48 1B B0 29 */	bl it_802A8398
lbl_800ED374:
/* 800ED374 000E9F54  7F C3 F3 78 */	mr r3, r30
/* 800ED378 000E9F58  4B F8 1E C1 */	bl ftAnim_IsFramesRemaining
/* 800ED37C 000E9F5C  2C 03 00 00 */	cmpwi r3, 0
/* 800ED380 000E9F60  40 82 00 E0 */	bne lbl_800ED460
/* 800ED384 000E9F64  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800ED388 000E9F68  3C 80 00 04 */	lis r4, 0x00040010@ha
/* 800ED38C 000E9F6C  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800ED390 000E9F70  7F C3 F3 78 */	mr r3, r30
/* 800ED394 000E9F74  FC 60 08 90 */	fmr f3, f1
/* 800ED398 000E9F78  38 A4 00 10 */	addi r5, r4, 0x00040010@l
/* 800ED39C 000E9F7C  38 80 01 59 */	li r4, 0x159
/* 800ED3A0 000E9F80  38 C0 00 00 */	li r6, 0
/* 800ED3A4 000E9F84  4B F7 C0 09 */	bl Fighter_ChangeMotionState
/* 800ED3A8 000E9F88  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800ED3AC 000E9F8C  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800ED3B0 000E9F90  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800ED3B4 000E9F94  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800ED3B8 000E9F98  7F C3 F3 78 */	mr r3, r30
/* 800ED3BC 000E9F9C  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800ED3C0 000E9FA0  4B F8 17 E5 */	bl ftAnim_8006EBA4
/* 800ED3C4 000E9FA4  48 00 00 9C */	b lbl_800ED460
lbl_800ED3C8:
/* 800ED3C8 000E9FA8  28 1E 00 00 */	cmplwi r30, 0
/* 800ED3CC 000E9FAC  41 82 00 44 */	beq lbl_800ED410
/* 800ED3D0 000E9FB0  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 800ED3D4 000E9FB4  28 03 00 00 */	cmplwi r3, 0
/* 800ED3D8 000E9FB8  41 82 00 38 */	beq lbl_800ED410
/* 800ED3DC 000E9FBC  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800ED3E0 000E9FC0  28 00 00 00 */	cmplwi r0, 0
/* 800ED3E4 000E9FC4  41 82 00 2C */	beq lbl_800ED410
/* 800ED3E8 000E9FC8  38 00 00 00 */	li r0, 0
/* 800ED3EC 000E9FCC  90 03 22 3C */	stw r0, 0x223c(r3)
/* 800ED3F0 000E9FD0  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ED3F4 000E9FD4  28 00 00 00 */	cmplwi r0, 0
/* 800ED3F8 000E9FD8  40 82 00 18 */	bne lbl_800ED410
/* 800ED3FC 000E9FDC  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ED400 000E9FE0  28 00 00 00 */	cmplwi r0, 0
/* 800ED404 000E9FE4  40 82 00 0C */	bne lbl_800ED410
/* 800ED408 000E9FE8  7F C3 F3 78 */	mr r3, r30
/* 800ED40C 000E9FEC  4B FF D9 59 */	bl ftLk_Init_BoomerangExists
lbl_800ED410:
/* 800ED410 000E9FF0  28 1E 00 00 */	cmplwi r30, 0
/* 800ED414 000E9FF4  41 82 00 44 */	beq lbl_800ED458
/* 800ED418 000E9FF8  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 800ED41C 000E9FFC  28 03 00 00 */	cmplwi r3, 0
/* 800ED420 000EA000  41 82 00 38 */	beq lbl_800ED458
/* 800ED424 000EA004  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ED428 000EA008  28 00 00 00 */	cmplwi r0, 0
/* 800ED42C 000EA00C  41 82 00 2C */	beq lbl_800ED458
/* 800ED430 000EA010  38 00 00 00 */	li r0, 0
/* 800ED434 000EA014  90 03 22 40 */	stw r0, 0x2240(r3)
/* 800ED438 000EA018  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ED43C 000EA01C  28 00 00 00 */	cmplwi r0, 0
/* 800ED440 000EA020  40 82 00 18 */	bne lbl_800ED458
/* 800ED444 000EA024  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800ED448 000EA028  28 00 00 00 */	cmplwi r0, 0
/* 800ED44C 000EA02C  40 82 00 0C */	bne lbl_800ED458
/* 800ED450 000EA030  7F C3 F3 78 */	mr r3, r30
/* 800ED454 000EA034  4B FF D9 11 */	bl ftLk_Init_BoomerangExists
lbl_800ED458:
/* 800ED458 000EA038  7F C3 F3 78 */	mr r3, r30
/* 800ED45C 000EA03C  4B F9 CE 61 */	bl ft_8008A2BC
lbl_800ED460:
/* 800ED460 000EA040  80 01 00 8C */	lwz r0, 0x8c(r1)
/* 800ED464 000EA044  83 E1 00 84 */	lwz r31, 0x84(r1)
/* 800ED468 000EA048  83 C1 00 80 */	lwz r30, 0x80(r1)
/* 800ED46C 000EA04C  83 A1 00 7C */	lwz r29, 0x7c(r1)
/* 800ED470 000EA050  83 81 00 78 */	lwz r28, 0x78(r1)
/* 800ED474 000EA054  38 21 00 88 */	addi r1, r1, 0x88
/* 800ED478 000EA058  7C 08 03 A6 */	mtlr r0
/* 800ED47C 000EA05C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline bool foo(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_unk0_bool] == 1 && fp->fv.lk.arrow_gobj == NULL) {
        fp->cmd_vars[cmd_unk0_bool] = 0;
        {
            Vec3 vec3;
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                        NULL, &vec3);
            {
                Item_GObj* arrow_gobj =
                    it_802A83E0(fp->facing_dir, gobj, &vec3,
                                ftParts_8007500C(fp, FtPart_LThumbNb), da->xC);
                fp->fv.lk.arrow_gobj = arrow_gobj;
                if (arrow_gobj != NULL) {
                    setCallbacks(gobj);
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

MotionFlags const mf = Ft_MF_SkipModel | Ft_MF_SkipItemVis;

static inline void bar(ftLk_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[0x20] = { 0 };
#endif
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint, NULL,
                &vecs.a);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint, NULL,
                &vecs.b);
    lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
    fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
    fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
    fp->mv.lk.specialn.x8.z = 0;
    fp->mv.lk.specialn.x8.x = atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b);
    }
    if (ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNLoop, mf, NULL, 0, 1,
                                  0);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

static inline void baz(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_unk2] && fp->mv.lk.specialn.x0.x == 0) {
        fp->mv.lk.specialn.x0.x = 1;
        fp->cmd_vars[cmd_unk2] = 0;
    }
    ftAnim_SetAnimRate(gobj, da->specialn_anim_rate);
}

void ftLk_SpecialNStart_Anim(ftLk_GObj* gobj)
{
    baz(gobj);
    if (!foo(gobj)) {
        bar(gobj);
    } else {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        ft_8008A2BC(gobj);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialNLoop_Anim(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800ED480 000EA060  7C 08 02 A6 */	mflr r0
/* 800ED484 000EA064  3C 80 80 3B */	lis r4, ftLk_Init_Vec3Group@ha
/* 800ED488 000EA068  90 01 00 04 */	stw r0, 4(r1)
/* 800ED48C 000EA06C  38 C4 75 20 */	addi r6, r4, ftLk_Init_Vec3Group@l
/* 800ED490 000EA070  38 80 00 1F */	li r4, 0x1f
/* 800ED494 000EA074  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800ED498 000EA078  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800ED49C 000EA07C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800ED4A0 000EA080  80 A6 00 00 */	lwz r5, 0(r6)
/* 800ED4A4 000EA084  80 06 00 04 */	lwz r0, 4(r6)
/* 800ED4A8 000EA088  7F E3 FB 78 */	mr r3, r31
/* 800ED4AC 000EA08C  90 A1 00 10 */	stw r5, 0x10(r1)
/* 800ED4B0 000EA090  90 01 00 14 */	stw r0, 0x14(r1)
/* 800ED4B4 000EA094  80 06 00 08 */	lwz r0, 8(r6)
/* 800ED4B8 000EA098  90 01 00 18 */	stw r0, 0x18(r1)
/* 800ED4BC 000EA09C  80 A6 00 0C */	lwz r5, 0xc(r6)
/* 800ED4C0 000EA0A0  80 06 00 10 */	lwz r0, 0x10(r6)
/* 800ED4C4 000EA0A4  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 800ED4C8 000EA0A8  90 01 00 20 */	stw r0, 0x20(r1)
/* 800ED4CC 000EA0AC  80 06 00 14 */	lwz r0, 0x14(r6)
/* 800ED4D0 000EA0B0  90 01 00 24 */	stw r0, 0x24(r1)
/* 800ED4D4 000EA0B4  80 A6 00 18 */	lwz r5, 0x18(r6)
/* 800ED4D8 000EA0B8  80 06 00 1C */	lwz r0, 0x1c(r6)
/* 800ED4DC 000EA0BC  90 A1 00 28 */	stw r5, 0x28(r1)
/* 800ED4E0 000EA0C0  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800ED4E4 000EA0C4  80 06 00 20 */	lwz r0, 0x20(r6)
/* 800ED4E8 000EA0C8  90 01 00 30 */	stw r0, 0x30(r1)
/* 800ED4EC 000EA0CC  4B F8 7B 21 */	bl ftParts_8007500C
/* 800ED4F0 000EA0D0  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800ED4F4 000EA0D4  54 60 20 36 */	slwi r0, r3, 4
/* 800ED4F8 000EA0D8  38 A1 00 10 */	addi r5, r1, 0x10
/* 800ED4FC 000EA0DC  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED500 000EA0E0  38 80 00 00 */	li r4, 0
/* 800ED504 000EA0E4  4B F1 DC C9 */	bl lb_8000B1CC
/* 800ED508 000EA0E8  38 7F 00 00 */	addi r3, r31, 0
/* 800ED50C 000EA0EC  38 80 00 31 */	li r4, 0x31
/* 800ED510 000EA0F0  4B F8 7A FD */	bl ftParts_8007500C
/* 800ED514 000EA0F4  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800ED518 000EA0F8  54 60 20 36 */	slwi r0, r3, 4
/* 800ED51C 000EA0FC  38 A1 00 1C */	addi r5, r1, 0x1c
/* 800ED520 000EA100  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED524 000EA104  38 80 00 00 */	li r4, 0
/* 800ED528 000EA108  4B F1 DC A5 */	bl lb_8000B1CC
/* 800ED52C 000EA10C  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 800ED530 000EA110  38 A1 00 28 */	addi r5, r1, 0x28
/* 800ED534 000EA114  38 80 00 00 */	li r4, 0
/* 800ED538 000EA118  80 63 00 00 */	lwz r3, 0(r3)
/* 800ED53C 000EA11C  4B F1 DC 91 */	bl lb_8000B1CC
/* 800ED540 000EA120  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 800ED544 000EA124  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 800ED548 000EA128  EC 01 00 28 */	fsubs f0, f1, f0
/* 800ED54C 000EA12C  D0 1F 23 4C */	stfs f0, 0x234c(r31)
/* 800ED550 000EA130  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 800ED554 000EA134  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 800ED558 000EA138  EC 01 00 28 */	fsubs f0, f1, f0
/* 800ED55C 000EA13C  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 800ED560 000EA140  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800ED564 000EA144  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 800ED568 000EA148  C0 61 00 20 */	lfs f3, 0x20(r1)
/* 800ED56C 000EA14C  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 800ED570 000EA150  C0 41 00 1C */	lfs f2, 0x1c(r1)
/* 800ED574 000EA154  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 800ED578 000EA158  EC 23 08 28 */	fsubs f1, f3, f1
/* 800ED57C 000EA15C  EC 42 00 28 */	fsubs f2, f2, f0
/* 800ED580 000EA160  4B F3 56 B1 */	bl atan2f
/* 800ED584 000EA164  D0 3F 23 48 */	stfs f1, 0x2348(r31)
/* 800ED588 000EA168  80 7F 22 3C */	lwz r3, 0x223c(r31)
/* 800ED58C 000EA16C  28 03 00 00 */	cmplwi r3, 0
/* 800ED590 000EA170  41 82 00 10 */	beq lbl_800ED5A0
/* 800ED594 000EA174  38 81 00 1C */	addi r4, r1, 0x1c
/* 800ED598 000EA178  38 A1 00 10 */	addi r5, r1, 0x10
/* 800ED59C 000EA17C  48 1B AD FD */	bl it_802A8398
lbl_800ED5A0:
/* 800ED5A0 000EA180  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800ED5A4 000EA184  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800ED5A8 000EA188  38 21 00 40 */	addi r1, r1, 0x40
/* 800ED5AC 000EA18C  7C 08 03 A6 */	mtlr r0
/* 800ED5B0 000EA190  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialNLoop_Anim(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint, NULL,
                &vecs.a);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint, NULL,
                &vecs.b);
    lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
    fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
    fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
    fp->mv.lk.specialn.x8.z = 0;
    fp->mv.lk.specialn.x8.x = atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b);
    }
}
#endif

static void setupParts(ftLk_GObj* gobj, bool arg1)
{
    ftParts_80074A4C(gobj, 2, arg1);
    ftParts_80074B0C(gobj, 2, arg1);
}

static void updateParts(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221E_b3 == true && fp->mv.lk.specialn.unk_timer == 0) {
        ++fp->mv.lk.specialn.unk_timer;
        if (fp->item_gobj != NULL) {
            setupParts(gobj, true);
        } else {
            setupParts(gobj, false);
        }
    }
}

void ftLk_SpecialNEnd_Anim(ftLk_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLk_SpecialN_UnsetFv14(gobj);
        updateParts(gobj);
        ft_8008A2BC(gobj);
    } else {
        updateParts(gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNStart_Anim(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800ED72C 000EA30C  7C 08 02 A6 */	mflr r0
/* 800ED730 000EA310  90 01 00 04 */	stw r0, 4(r1)
/* 800ED734 000EA314  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 800ED738 000EA318  BF 61 00 7C */	stmw r27, 0x7c(r1)
/* 800ED73C 000EA31C  7C 7D 1B 78 */	mr r29, r3
/* 800ED740 000EA320  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800ED744 000EA324  3C 60 80 3B */	lis r3, ftLk_Init_Vec3Group@ha
/* 800ED748 000EA328  3B E3 75 20 */	addi r31, r3, ftLk_Init_Vec3Group@l
/* 800ED74C 000EA32C  80 04 22 08 */	lwz r0, 0x2208(r4)
/* 800ED750 000EA330  83 C4 02 D4 */	lwz r30, 0x2d4(r4)
/* 800ED754 000EA334  28 00 00 00 */	cmplwi r0, 0
/* 800ED758 000EA338  41 82 00 24 */	beq lbl_800ED77C
/* 800ED75C 000EA33C  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800ED760 000EA340  C0 04 23 40 */	lfs f0, 0x2340(r4)
/* 800ED764 000EA344  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800ED768 000EA348  40 82 00 14 */	bne lbl_800ED77C
/* 800ED76C 000EA34C  C0 02 99 68 */	lfs f0, ftLk_Init_804D9348
/* 800ED770 000EA350  38 00 00 00 */	li r0, 0
/* 800ED774 000EA354  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 800ED778 000EA358  90 04 22 08 */	stw r0, 0x2208(r4)
lbl_800ED77C:
/* 800ED77C 000EA35C  83 7D 00 2C */	lwz r27, 0x2c(r29)
/* 800ED780 000EA360  80 1B 22 00 */	lwz r0, 0x2200(r27)
/* 800ED784 000EA364  83 9B 02 D4 */	lwz r28, 0x2d4(r27)
/* 800ED788 000EA368  28 00 00 01 */	cmplwi r0, 1
/* 800ED78C 000EA36C  40 82 00 8C */	bne lbl_800ED818
/* 800ED790 000EA370  80 1B 22 3C */	lwz r0, 0x223c(r27)
/* 800ED794 000EA374  28 00 00 00 */	cmplwi r0, 0
/* 800ED798 000EA378  40 82 00 80 */	bne lbl_800ED818
/* 800ED79C 000EA37C  38 00 00 00 */	li r0, 0
/* 800ED7A0 000EA380  90 1B 22 00 */	stw r0, 0x2200(r27)
/* 800ED7A4 000EA384  38 7B 00 00 */	addi r3, r27, 0
/* 800ED7A8 000EA388  38 80 00 1F */	li r4, 0x1f
/* 800ED7AC 000EA38C  4B F8 78 61 */	bl ftParts_8007500C
/* 800ED7B0 000EA390  80 9B 05 E8 */	lwz r4, 0x5e8(r27)
/* 800ED7B4 000EA394  54 60 20 36 */	slwi r0, r3, 4
/* 800ED7B8 000EA398  38 A1 00 6C */	addi r5, r1, 0x6c
/* 800ED7BC 000EA39C  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED7C0 000EA3A0  38 80 00 00 */	li r4, 0
/* 800ED7C4 000EA3A4  4B F1 DA 09 */	bl lb_8000B1CC
/* 800ED7C8 000EA3A8  38 7B 00 00 */	addi r3, r27, 0
/* 800ED7CC 000EA3AC  38 80 00 1F */	li r4, 0x1f
/* 800ED7D0 000EA3B0  4B F8 78 3D */	bl ftParts_8007500C
/* 800ED7D4 000EA3B4  C0 3B 00 2C */	lfs f1, 0x2c(r27)
/* 800ED7D8 000EA3B8  7C 65 1B 78 */	mr r5, r3
/* 800ED7DC 000EA3BC  80 DC 00 0C */	lwz r6, 0xc(r28)
/* 800ED7E0 000EA3C0  38 7D 00 00 */	addi r3, r29, 0
/* 800ED7E4 000EA3C4  38 81 00 6C */	addi r4, r1, 0x6c
/* 800ED7E8 000EA3C8  48 1B AB F9 */	bl it_802A83E0
/* 800ED7EC 000EA3CC  28 03 00 00 */	cmplwi r3, 0
/* 800ED7F0 000EA3D0  90 7B 22 3C */	stw r3, 0x223c(r27)
/* 800ED7F4 000EA3D4  41 82 00 1C */	beq lbl_800ED810
/* 800ED7F8 000EA3D8  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800ED7FC 000EA3DC  80 9D 00 2C */	lwz r4, 0x2c(r29)
/* 800ED800 000EA3E0  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800ED804 000EA3E4  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800ED808 000EA3E8  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800ED80C 000EA3EC  48 00 00 0C */	b lbl_800ED818
lbl_800ED810:
/* 800ED810 000EA3F0  38 00 00 01 */	li r0, 1
/* 800ED814 000EA3F4  48 00 00 08 */	b lbl_800ED81C
lbl_800ED818:
/* 800ED818 000EA3F8  38 00 00 00 */	li r0, 0
lbl_800ED81C:
/* 800ED81C 000EA3FC  2C 00 00 00 */	cmpwi r0, 0
/* 800ED820 000EA400  40 82 01 60 */	bne lbl_800ED980
/* 800ED824 000EA404  83 7D 00 2C */	lwz r27, 0x2c(r29)
/* 800ED828 000EA408  38 80 00 1F */	li r4, 0x1f
/* 800ED82C 000EA40C  80 BF 00 00 */	lwz r5, 0(r31)
/* 800ED830 000EA410  80 1F 00 04 */	lwz r0, 4(r31)
/* 800ED834 000EA414  7F 63 DB 78 */	mr r3, r27
/* 800ED838 000EA418  90 A1 00 48 */	stw r5, 0x48(r1)
/* 800ED83C 000EA41C  90 01 00 4C */	stw r0, 0x4c(r1)
/* 800ED840 000EA420  80 1F 00 08 */	lwz r0, 8(r31)
/* 800ED844 000EA424  90 01 00 50 */	stw r0, 0x50(r1)
/* 800ED848 000EA428  80 BF 00 0C */	lwz r5, 0xc(r31)
/* 800ED84C 000EA42C  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800ED850 000EA430  90 A1 00 54 */	stw r5, 0x54(r1)
/* 800ED854 000EA434  90 01 00 58 */	stw r0, 0x58(r1)
/* 800ED858 000EA438  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 800ED85C 000EA43C  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800ED860 000EA440  80 BF 00 18 */	lwz r5, 0x18(r31)
/* 800ED864 000EA444  80 1F 00 1C */	lwz r0, 0x1c(r31)
/* 800ED868 000EA448  90 A1 00 60 */	stw r5, 0x60(r1)
/* 800ED86C 000EA44C  90 01 00 64 */	stw r0, 0x64(r1)
/* 800ED870 000EA450  80 1F 00 20 */	lwz r0, 0x20(r31)
/* 800ED874 000EA454  90 01 00 68 */	stw r0, 0x68(r1)
/* 800ED878 000EA458  4B F8 77 95 */	bl ftParts_8007500C
/* 800ED87C 000EA45C  80 9B 05 E8 */	lwz r4, 0x5e8(r27)
/* 800ED880 000EA460  54 60 20 36 */	slwi r0, r3, 4
/* 800ED884 000EA464  38 A1 00 48 */	addi r5, r1, 0x48
/* 800ED888 000EA468  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED88C 000EA46C  38 80 00 00 */	li r4, 0
/* 800ED890 000EA470  4B F1 D9 3D */	bl lb_8000B1CC
/* 800ED894 000EA474  38 7B 00 00 */	addi r3, r27, 0
/* 800ED898 000EA478  38 80 00 31 */	li r4, 0x31
/* 800ED89C 000EA47C  4B F8 77 71 */	bl ftParts_8007500C
/* 800ED8A0 000EA480  80 9B 05 E8 */	lwz r4, 0x5e8(r27)
/* 800ED8A4 000EA484  54 60 20 36 */	slwi r0, r3, 4
/* 800ED8A8 000EA488  38 A1 00 54 */	addi r5, r1, 0x54
/* 800ED8AC 000EA48C  7C 64 00 2E */	lwzx r3, r4, r0
/* 800ED8B0 000EA490  38 80 00 00 */	li r4, 0
/* 800ED8B4 000EA494  4B F1 D9 19 */	bl lb_8000B1CC
/* 800ED8B8 000EA498  80 7B 05 E8 */	lwz r3, 0x5e8(r27)
/* 800ED8BC 000EA49C  38 A1 00 60 */	addi r5, r1, 0x60
/* 800ED8C0 000EA4A0  38 80 00 00 */	li r4, 0
/* 800ED8C4 000EA4A4  80 63 00 00 */	lwz r3, 0(r3)
/* 800ED8C8 000EA4A8  4B F1 D9 05 */	bl lb_8000B1CC
/* 800ED8CC 000EA4AC  C0 21 00 54 */	lfs f1, 0x54(r1)
/* 800ED8D0 000EA4B0  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 800ED8D4 000EA4B4  EC 01 00 28 */	fsubs f0, f1, f0
/* 800ED8D8 000EA4B8  D0 1B 23 4C */	stfs f0, 0x234c(r27)
/* 800ED8DC 000EA4BC  C0 21 00 58 */	lfs f1, 0x58(r1)
/* 800ED8E0 000EA4C0  C0 01 00 64 */	lfs f0, 0x64(r1)
/* 800ED8E4 000EA4C4  EC 01 00 28 */	fsubs f0, f1, f0
/* 800ED8E8 000EA4C8  D0 1B 23 50 */	stfs f0, 0x2350(r27)
/* 800ED8EC 000EA4CC  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800ED8F0 000EA4D0  D0 1B 23 54 */	stfs f0, 0x2354(r27)
/* 800ED8F4 000EA4D4  C0 61 00 58 */	lfs f3, 0x58(r1)
/* 800ED8F8 000EA4D8  C0 21 00 4C */	lfs f1, 0x4c(r1)
/* 800ED8FC 000EA4DC  C0 41 00 54 */	lfs f2, 0x54(r1)
/* 800ED900 000EA4E0  C0 01 00 48 */	lfs f0, 0x48(r1)
/* 800ED904 000EA4E4  EC 23 08 28 */	fsubs f1, f3, f1
/* 800ED908 000EA4E8  EC 42 00 28 */	fsubs f2, f2, f0
/* 800ED90C 000EA4EC  4B F3 53 25 */	bl atan2f
/* 800ED910 000EA4F0  D0 3B 23 48 */	stfs f1, 0x2348(r27)
/* 800ED914 000EA4F4  80 7B 22 3C */	lwz r3, 0x223c(r27)
/* 800ED918 000EA4F8  28 03 00 00 */	cmplwi r3, 0
/* 800ED91C 000EA4FC  41 82 00 10 */	beq lbl_800ED92C
/* 800ED920 000EA500  38 81 00 54 */	addi r4, r1, 0x54
/* 800ED924 000EA504  38 A1 00 48 */	addi r5, r1, 0x48
/* 800ED928 000EA508  48 1B AA 71 */	bl it_802A8398
lbl_800ED92C:
/* 800ED92C 000EA50C  7F A3 EB 78 */	mr r3, r29
/* 800ED930 000EA510  4B F8 19 09 */	bl ftAnim_IsFramesRemaining
/* 800ED934 000EA514  2C 03 00 00 */	cmpwi r3, 0
/* 800ED938 000EA518  40 82 01 0C */	bne lbl_800EDA44
/* 800ED93C 000EA51C  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800ED940 000EA520  3C 80 00 04 */	lis r4, 0x00040010@ha
/* 800ED944 000EA524  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800ED948 000EA528  7F A3 EB 78 */	mr r3, r29
/* 800ED94C 000EA52C  FC 60 08 90 */	fmr f3, f1
/* 800ED950 000EA530  38 A4 00 10 */	addi r5, r4, 0x00040010@l
/* 800ED954 000EA534  38 80 01 5C */	li r4, 0x15c
/* 800ED958 000EA538  38 C0 00 00 */	li r6, 0
/* 800ED95C 000EA53C  4B F7 BA 51 */	bl Fighter_ChangeMotionState
/* 800ED960 000EA540  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800ED964 000EA544  80 9D 00 2C */	lwz r4, 0x2c(r29)
/* 800ED968 000EA548  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800ED96C 000EA54C  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800ED970 000EA550  7F A3 EB 78 */	mr r3, r29
/* 800ED974 000EA554  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800ED978 000EA558  4B F8 12 2D */	bl ftAnim_8006EBA4
/* 800ED97C 000EA55C  48 00 00 C8 */	b lbl_800EDA44
lbl_800ED980:
/* 800ED980 000EA560  28 1D 00 00 */	cmplwi r29, 0
/* 800ED984 000EA564  41 82 00 44 */	beq lbl_800ED9C8
/* 800ED988 000EA568  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 800ED98C 000EA56C  28 03 00 00 */	cmplwi r3, 0
/* 800ED990 000EA570  41 82 00 38 */	beq lbl_800ED9C8
/* 800ED994 000EA574  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800ED998 000EA578  28 00 00 00 */	cmplwi r0, 0
/* 800ED99C 000EA57C  41 82 00 2C */	beq lbl_800ED9C8
/* 800ED9A0 000EA580  38 00 00 00 */	li r0, 0
/* 800ED9A4 000EA584  90 03 22 3C */	stw r0, 0x223c(r3)
/* 800ED9A8 000EA588  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ED9AC 000EA58C  28 00 00 00 */	cmplwi r0, 0
/* 800ED9B0 000EA590  40 82 00 18 */	bne lbl_800ED9C8
/* 800ED9B4 000EA594  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ED9B8 000EA598  28 00 00 00 */	cmplwi r0, 0
/* 800ED9BC 000EA59C  40 82 00 0C */	bne lbl_800ED9C8
/* 800ED9C0 000EA5A0  7F A3 EB 78 */	mr r3, r29
/* 800ED9C4 000EA5A4  4B FF D3 A1 */	bl ftLk_Init_BoomerangExists
lbl_800ED9C8:
/* 800ED9C8 000EA5A8  28 1D 00 00 */	cmplwi r29, 0
/* 800ED9CC 000EA5AC  41 82 00 44 */	beq lbl_800EDA10
/* 800ED9D0 000EA5B0  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 800ED9D4 000EA5B4  28 03 00 00 */	cmplwi r3, 0
/* 800ED9D8 000EA5B8  41 82 00 38 */	beq lbl_800EDA10
/* 800ED9DC 000EA5BC  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800ED9E0 000EA5C0  28 00 00 00 */	cmplwi r0, 0
/* 800ED9E4 000EA5C4  41 82 00 2C */	beq lbl_800EDA10
/* 800ED9E8 000EA5C8  38 00 00 00 */	li r0, 0
/* 800ED9EC 000EA5CC  90 03 22 40 */	stw r0, 0x2240(r3)
/* 800ED9F0 000EA5D0  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800ED9F4 000EA5D4  28 00 00 00 */	cmplwi r0, 0
/* 800ED9F8 000EA5D8  40 82 00 18 */	bne lbl_800EDA10
/* 800ED9FC 000EA5DC  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800EDA00 000EA5E0  28 00 00 00 */	cmplwi r0, 0
/* 800EDA04 000EA5E4  40 82 00 0C */	bne lbl_800EDA10
/* 800EDA08 000EA5E8  7F A3 EB 78 */	mr r3, r29
/* 800EDA0C 000EA5EC  4B FF D3 59 */	bl ftLk_Init_BoomerangExists
lbl_800EDA10:
/* 800EDA10 000EA5F0  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800EDA14 000EA5F4  C0 5E 00 08 */	lfs f2, 8(r30)
/* 800EDA18 000EA5F8  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 800EDA1C 000EA5FC  40 82 00 10 */	bne lbl_800EDA2C
/* 800EDA20 000EA600  7F A3 EB 78 */	mr r3, r29
/* 800EDA24 000EA604  4B FD ED 0D */	bl ftCo_800CC730
/* 800EDA28 000EA608  48 00 00 1C */	b lbl_800EDA44
lbl_800EDA2C:
/* 800EDA2C 000EA60C  C0 22 99 68 */	lfs f1, ftLk_Init_804D9348
/* 800EDA30 000EA610  38 7D 00 00 */	addi r3, r29, 0
/* 800EDA34 000EA614  38 80 00 01 */	li r4, 1
/* 800EDA38 000EA618  38 A0 00 00 */	li r5, 0
/* 800EDA3C 000EA61C  38 C0 00 01 */	li r6, 1
/* 800EDA40 000EA620  4B FA 8E C1 */	bl ftCo_80096900
lbl_800EDA44:
/* 800EDA44 000EA624  BB 61 00 7C */	lmw r27, 0x7c(r1)
/* 800EDA48 000EA628  80 01 00 94 */	lwz r0, 0x94(r1)
/* 800EDA4C 000EA62C  38 21 00 90 */	addi r1, r1, 0x90
/* 800EDA50 000EA630  7C 08 03 A6 */	mtlr r0
/* 800EDA54 000EA634  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialAirNStart_Anim(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_unk1_bool] && fp->mv.lk.specialn.x0.x == 0) {
        fp->mv.lk.specialn.x0.x = 0;
        fp->cmd_vars[cmd_unk1_bool] = false;
    }
    if (!unkCondition(gobj)) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                    NULL, &vecs.a);
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                    NULL, &vecs.b);
        lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
        fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
        fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
        fp->mv.lk.specialn.x8.x =
            atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
        if (fp->fv.lk.arrow_gobj != NULL) {
            it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNLoop, mf, NULL,
                                      0, 1, 0);
            setCallbacks(gobj);
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        if (da->x8 == 0) {
            ftCo_800CC730(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x8);
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNLoop_Anim(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EDA58 000EA638  7C 08 02 A6 */	mflr r0
/* 800EDA5C 000EA63C  3C 80 80 3B */	lis r4, ftLk_Init_Vec3Group@ha
/* 800EDA60 000EA640  90 01 00 04 */	stw r0, 4(r1)
/* 800EDA64 000EA644  38 C4 75 20 */	addi r6, r4, ftLk_Init_Vec3Group@l
/* 800EDA68 000EA648  38 80 00 1F */	li r4, 0x1f
/* 800EDA6C 000EA64C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800EDA70 000EA650  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800EDA74 000EA654  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EDA78 000EA658  80 A6 00 00 */	lwz r5, 0(r6)
/* 800EDA7C 000EA65C  80 06 00 04 */	lwz r0, 4(r6)
/* 800EDA80 000EA660  7F E3 FB 78 */	mr r3, r31
/* 800EDA84 000EA664  90 A1 00 10 */	stw r5, 0x10(r1)
/* 800EDA88 000EA668  90 01 00 14 */	stw r0, 0x14(r1)
/* 800EDA8C 000EA66C  80 06 00 08 */	lwz r0, 8(r6)
/* 800EDA90 000EA670  90 01 00 18 */	stw r0, 0x18(r1)
/* 800EDA94 000EA674  80 A6 00 0C */	lwz r5, 0xc(r6)
/* 800EDA98 000EA678  80 06 00 10 */	lwz r0, 0x10(r6)
/* 800EDA9C 000EA67C  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 800EDAA0 000EA680  90 01 00 20 */	stw r0, 0x20(r1)
/* 800EDAA4 000EA684  80 06 00 14 */	lwz r0, 0x14(r6)
/* 800EDAA8 000EA688  90 01 00 24 */	stw r0, 0x24(r1)
/* 800EDAAC 000EA68C  80 A6 00 18 */	lwz r5, 0x18(r6)
/* 800EDAB0 000EA690  80 06 00 1C */	lwz r0, 0x1c(r6)
/* 800EDAB4 000EA694  90 A1 00 28 */	stw r5, 0x28(r1)
/* 800EDAB8 000EA698  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800EDABC 000EA69C  80 06 00 20 */	lwz r0, 0x20(r6)
/* 800EDAC0 000EA6A0  90 01 00 30 */	stw r0, 0x30(r1)
/* 800EDAC4 000EA6A4  4B F8 75 49 */	bl ftParts_8007500C
/* 800EDAC8 000EA6A8  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800EDACC 000EA6AC  54 60 20 36 */	slwi r0, r3, 4
/* 800EDAD0 000EA6B0  38 A1 00 10 */	addi r5, r1, 0x10
/* 800EDAD4 000EA6B4  7C 64 00 2E */	lwzx r3, r4, r0
/* 800EDAD8 000EA6B8  38 80 00 00 */	li r4, 0
/* 800EDADC 000EA6BC  4B F1 D6 F1 */	bl lb_8000B1CC
/* 800EDAE0 000EA6C0  38 7F 00 00 */	addi r3, r31, 0
/* 800EDAE4 000EA6C4  38 80 00 31 */	li r4, 0x31
/* 800EDAE8 000EA6C8  4B F8 75 25 */	bl ftParts_8007500C
/* 800EDAEC 000EA6CC  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800EDAF0 000EA6D0  54 60 20 36 */	slwi r0, r3, 4
/* 800EDAF4 000EA6D4  38 A1 00 1C */	addi r5, r1, 0x1c
/* 800EDAF8 000EA6D8  7C 64 00 2E */	lwzx r3, r4, r0
/* 800EDAFC 000EA6DC  38 80 00 00 */	li r4, 0
/* 800EDB00 000EA6E0  4B F1 D6 CD */	bl lb_8000B1CC
/* 800EDB04 000EA6E4  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 800EDB08 000EA6E8  38 A1 00 28 */	addi r5, r1, 0x28
/* 800EDB0C 000EA6EC  38 80 00 00 */	li r4, 0
/* 800EDB10 000EA6F0  80 63 00 00 */	lwz r3, 0(r3)
/* 800EDB14 000EA6F4  4B F1 D6 B9 */	bl lb_8000B1CC
/* 800EDB18 000EA6F8  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 800EDB1C 000EA6FC  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 800EDB20 000EA700  EC 01 00 28 */	fsubs f0, f1, f0
/* 800EDB24 000EA704  D0 1F 23 4C */	stfs f0, 0x234c(r31)
/* 800EDB28 000EA708  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 800EDB2C 000EA70C  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 800EDB30 000EA710  EC 01 00 28 */	fsubs f0, f1, f0
/* 800EDB34 000EA714  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 800EDB38 000EA718  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800EDB3C 000EA71C  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 800EDB40 000EA720  C0 61 00 20 */	lfs f3, 0x20(r1)
/* 800EDB44 000EA724  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 800EDB48 000EA728  C0 41 00 1C */	lfs f2, 0x1c(r1)
/* 800EDB4C 000EA72C  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 800EDB50 000EA730  EC 23 08 28 */	fsubs f1, f3, f1
/* 800EDB54 000EA734  EC 42 00 28 */	fsubs f2, f2, f0
/* 800EDB58 000EA738  4B F3 50 D9 */	bl atan2f
/* 800EDB5C 000EA73C  D0 3F 23 48 */	stfs f1, 0x2348(r31)
/* 800EDB60 000EA740  80 7F 22 3C */	lwz r3, 0x223c(r31)
/* 800EDB64 000EA744  28 03 00 00 */	cmplwi r3, 0
/* 800EDB68 000EA748  41 82 00 10 */	beq lbl_800EDB78
/* 800EDB6C 000EA74C  38 81 00 1C */	addi r4, r1, 0x1c
/* 800EDB70 000EA750  38 A1 00 10 */	addi r5, r1, 0x10
/* 800EDB74 000EA754  48 1B A8 25 */	bl it_802A8398
lbl_800EDB78:
/* 800EDB78 000EA758  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800EDB7C 000EA75C  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800EDB80 000EA760  38 21 00 40 */	addi r1, r1, 0x40
/* 800EDB84 000EA764  7C 08 03 A6 */	mtlr r0
/* 800EDB88 000EA768  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialAirNLoop_Anim(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint, NULL,
                &vecs.a);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint, NULL,
                &vecs.b);
    lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
    fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
    fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
    fp->mv.lk.specialn.x8.x = atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNEnd_Anim(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EDB8C 000EA76C  7C 08 02 A6 */	mflr r0
/* 800EDB90 000EA770  90 01 00 04 */	stw r0, 4(r1)
/* 800EDB94 000EA774  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800EDB98 000EA778  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800EDB9C 000EA77C  7C 7F 1B 78 */	mr r31, r3
/* 800EDBA0 000EA780  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800EDBA4 000EA784  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800EDBA8 000EA788  83 C4 02 D4 */	lwz r30, 0x2d4(r4)
/* 800EDBAC 000EA78C  4B F8 16 8D */	bl ftAnim_IsFramesRemaining
/* 800EDBB0 000EA790  2C 03 00 00 */	cmpwi r3, 0
/* 800EDBB4 000EA794  40 82 01 44 */	bne lbl_800EDCF8
/* 800EDBB8 000EA798  28 1F 00 00 */	cmplwi r31, 0
/* 800EDBBC 000EA79C  41 82 00 44 */	beq lbl_800EDC00
/* 800EDBC0 000EA7A0  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 800EDBC4 000EA7A4  28 03 00 00 */	cmplwi r3, 0
/* 800EDBC8 000EA7A8  41 82 00 38 */	beq lbl_800EDC00
/* 800EDBCC 000EA7AC  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800EDBD0 000EA7B0  28 00 00 00 */	cmplwi r0, 0
/* 800EDBD4 000EA7B4  41 82 00 2C */	beq lbl_800EDC00
/* 800EDBD8 000EA7B8  38 00 00 00 */	li r0, 0
/* 800EDBDC 000EA7BC  90 03 22 3C */	stw r0, 0x223c(r3)
/* 800EDBE0 000EA7C0  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800EDBE4 000EA7C4  28 00 00 00 */	cmplwi r0, 0
/* 800EDBE8 000EA7C8  40 82 00 18 */	bne lbl_800EDC00
/* 800EDBEC 000EA7CC  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800EDBF0 000EA7D0  28 00 00 00 */	cmplwi r0, 0
/* 800EDBF4 000EA7D4  40 82 00 0C */	bne lbl_800EDC00
/* 800EDBF8 000EA7D8  7F E3 FB 78 */	mr r3, r31
/* 800EDBFC 000EA7DC  4B FF D1 69 */	bl ftLk_Init_BoomerangExists
lbl_800EDC00:
/* 800EDC00 000EA7E0  28 1F 00 00 */	cmplwi r31, 0
/* 800EDC04 000EA7E4  41 82 00 44 */	beq lbl_800EDC48
/* 800EDC08 000EA7E8  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 800EDC0C 000EA7EC  28 03 00 00 */	cmplwi r3, 0
/* 800EDC10 000EA7F0  41 82 00 38 */	beq lbl_800EDC48
/* 800EDC14 000EA7F4  80 03 22 40 */	lwz r0, 0x2240(r3)
/* 800EDC18 000EA7F8  28 00 00 00 */	cmplwi r0, 0
/* 800EDC1C 000EA7FC  41 82 00 2C */	beq lbl_800EDC48
/* 800EDC20 000EA800  38 00 00 00 */	li r0, 0
/* 800EDC24 000EA804  90 03 22 40 */	stw r0, 0x2240(r3)
/* 800EDC28 000EA808  80 03 22 34 */	lwz r0, 0x2234(r3)
/* 800EDC2C 000EA80C  28 00 00 00 */	cmplwi r0, 0
/* 800EDC30 000EA810  40 82 00 18 */	bne lbl_800EDC48
/* 800EDC34 000EA814  80 03 22 3C */	lwz r0, 0x223c(r3)
/* 800EDC38 000EA818  28 00 00 00 */	cmplwi r0, 0
/* 800EDC3C 000EA81C  40 82 00 0C */	bne lbl_800EDC48
/* 800EDC40 000EA820  7F E3 FB 78 */	mr r3, r31
/* 800EDC44 000EA824  4B FF D1 21 */	bl ftLk_Init_BoomerangExists
lbl_800EDC48:
/* 800EDC48 000EA828  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800EDC4C 000EA82C  88 04 22 1E */	lbz r0, 0x221e(r4)
/* 800EDC50 000EA830  54 00 E7 FE */	rlwinm r0, r0, 0x1c, 0x1f, 0x1f
/* 800EDC54 000EA834  28 00 00 01 */	cmplwi r0, 1
/* 800EDC58 000EA838  40 82 00 68 */	bne lbl_800EDCC0
/* 800EDC5C 000EA83C  80 64 23 58 */	lwz r3, 0x2358(r4)
/* 800EDC60 000EA840  2C 03 00 00 */	cmpwi r3, 0
/* 800EDC64 000EA844  40 82 00 5C */	bne lbl_800EDCC0
/* 800EDC68 000EA848  38 03 00 01 */	addi r0, r3, 1
/* 800EDC6C 000EA84C  90 04 23 58 */	stw r0, 0x2358(r4)
/* 800EDC70 000EA850  80 04 19 74 */	lwz r0, 0x1974(r4)
/* 800EDC74 000EA854  28 00 00 00 */	cmplwi r0, 0
/* 800EDC78 000EA858  41 82 00 28 */	beq lbl_800EDCA0
/* 800EDC7C 000EA85C  38 7F 00 00 */	addi r3, r31, 0
/* 800EDC80 000EA860  38 80 00 02 */	li r4, 2
/* 800EDC84 000EA864  38 A0 00 01 */	li r5, 1
/* 800EDC88 000EA868  4B F8 6D C5 */	bl ftParts_80074A4C
/* 800EDC8C 000EA86C  38 7F 00 00 */	addi r3, r31, 0
/* 800EDC90 000EA870  38 80 00 02 */	li r4, 2
/* 800EDC94 000EA874  38 A0 00 01 */	li r5, 1
/* 800EDC98 000EA878  4B F8 6E 75 */	bl ftParts_80074B0C
/* 800EDC9C 000EA87C  48 00 00 24 */	b lbl_800EDCC0
lbl_800EDCA0:
/* 800EDCA0 000EA880  38 7F 00 00 */	addi r3, r31, 0
/* 800EDCA4 000EA884  38 80 00 02 */	li r4, 2
/* 800EDCA8 000EA888  38 A0 00 00 */	li r5, 0
/* 800EDCAC 000EA88C  4B F8 6D A1 */	bl ftParts_80074A4C
/* 800EDCB0 000EA890  38 7F 00 00 */	addi r3, r31, 0
/* 800EDCB4 000EA894  38 80 00 02 */	li r4, 2
/* 800EDCB8 000EA898  38 A0 00 00 */	li r5, 0
/* 800EDCBC 000EA89C  4B F8 6E 51 */	bl ftParts_80074B0C
lbl_800EDCC0:
/* 800EDCC0 000EA8A0  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800EDCC4 000EA8A4  C0 5E 00 08 */	lfs f2, 8(r30)
/* 800EDCC8 000EA8A8  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 800EDCCC 000EA8AC  40 82 00 10 */	bne lbl_800EDCDC
/* 800EDCD0 000EA8B0  7F E3 FB 78 */	mr r3, r31
/* 800EDCD4 000EA8B4  4B FD EA 5D */	bl ftCo_800CC730
/* 800EDCD8 000EA8B8  48 00 00 98 */	b lbl_800EDD70
lbl_800EDCDC:
/* 800EDCDC 000EA8BC  C0 22 99 68 */	lfs f1, ftLk_Init_804D9348
/* 800EDCE0 000EA8C0  38 7F 00 00 */	addi r3, r31, 0
/* 800EDCE4 000EA8C4  38 80 00 01 */	li r4, 1
/* 800EDCE8 000EA8C8  38 A0 00 00 */	li r5, 0
/* 800EDCEC 000EA8CC  38 C0 00 01 */	li r6, 1
/* 800EDCF0 000EA8D0  4B FA 8C 11 */	bl ftCo_80096900
/* 800EDCF4 000EA8D4  48 00 00 7C */	b lbl_800EDD70
lbl_800EDCF8:
/* 800EDCF8 000EA8D8  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800EDCFC 000EA8DC  88 04 22 1E */	lbz r0, 0x221e(r4)
/* 800EDD00 000EA8E0  54 00 E7 FE */	rlwinm r0, r0, 0x1c, 0x1f, 0x1f
/* 800EDD04 000EA8E4  28 00 00 01 */	cmplwi r0, 1
/* 800EDD08 000EA8E8  40 82 00 68 */	bne lbl_800EDD70
/* 800EDD0C 000EA8EC  80 64 23 58 */	lwz r3, 0x2358(r4)
/* 800EDD10 000EA8F0  2C 03 00 00 */	cmpwi r3, 0
/* 800EDD14 000EA8F4  40 82 00 5C */	bne lbl_800EDD70
/* 800EDD18 000EA8F8  38 03 00 01 */	addi r0, r3, 1
/* 800EDD1C 000EA8FC  90 04 23 58 */	stw r0, 0x2358(r4)
/* 800EDD20 000EA900  80 04 19 74 */	lwz r0, 0x1974(r4)
/* 800EDD24 000EA904  28 00 00 00 */	cmplwi r0, 0
/* 800EDD28 000EA908  41 82 00 28 */	beq lbl_800EDD50
/* 800EDD2C 000EA90C  38 7F 00 00 */	addi r3, r31, 0
/* 800EDD30 000EA910  38 80 00 02 */	li r4, 2
/* 800EDD34 000EA914  38 A0 00 01 */	li r5, 1
/* 800EDD38 000EA918  4B F8 6D 15 */	bl ftParts_80074A4C
/* 800EDD3C 000EA91C  38 7F 00 00 */	addi r3, r31, 0
/* 800EDD40 000EA920  38 80 00 02 */	li r4, 2
/* 800EDD44 000EA924  38 A0 00 01 */	li r5, 1
/* 800EDD48 000EA928  4B F8 6D C5 */	bl ftParts_80074B0C
/* 800EDD4C 000EA92C  48 00 00 24 */	b lbl_800EDD70
lbl_800EDD50:
/* 800EDD50 000EA930  38 7F 00 00 */	addi r3, r31, 0
/* 800EDD54 000EA934  38 80 00 02 */	li r4, 2
/* 800EDD58 000EA938  38 A0 00 00 */	li r5, 0
/* 800EDD5C 000EA93C  4B F8 6C F1 */	bl ftParts_80074A4C
/* 800EDD60 000EA940  38 7F 00 00 */	addi r3, r31, 0
/* 800EDD64 000EA944  38 80 00 02 */	li r4, 2
/* 800EDD68 000EA948  38 A0 00 00 */	li r5, 0
/* 800EDD6C 000EA94C  4B F8 6D A1 */	bl ftParts_80074B0C
lbl_800EDD70:
/* 800EDD70 000EA950  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800EDD74 000EA954  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800EDD78 000EA958  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800EDD7C 000EA95C  38 21 00 40 */	addi r1, r1, 0x40
/* 800EDD80 000EA960  7C 08 03 A6 */	mtlr r0
/* 800EDD84 000EA964  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialAirNEnd_Anim(ftLk_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        updateParts(gobj);
        if (da->x8 == 0) {
            ftCo_800CC730(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x8);
        }
    } else {
        updateParts(gobj);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialNStart_IASA(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EDD88 000EA968  7C 08 02 A6 */	mflr r0
/* 800EDD8C 000EA96C  90 01 00 04 */	stw r0, 4(r1)
/* 800EDD90 000EA970  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EDD94 000EA974  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EDD98 000EA978  7C 7F 1B 78 */	mr r31, r3
/* 800EDD9C 000EA97C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800EDDA0 000EA980  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800EDDA4 000EA984  C0 03 23 40 */	lfs f0, 0x2340(r3)
/* 800EDDA8 000EA988  80 83 02 D4 */	lwz r4, 0x2d4(r3)
/* 800EDDAC 000EA98C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800EDDB0 000EA990  41 82 00 6C */	beq lbl_800EDE1C
/* 800EDDB4 000EA994  C0 23 23 44 */	lfs f1, 0x2344(r3)
/* 800EDDB8 000EA998  C0 02 99 68 */	lfs f0, ftLk_Init_804D9348
/* 800EDDBC 000EA99C  EC 01 00 2A */	fadds f0, f1, f0
/* 800EDDC0 000EA9A0  D0 03 23 44 */	stfs f0, 0x2344(r3)
/* 800EDDC4 000EA9A4  C0 03 23 44 */	lfs f0, 0x2344(r3)
/* 800EDDC8 000EA9A8  C0 24 00 00 */	lfs f1, 0(r4)
/* 800EDDCC 000EA9AC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800EDDD0 000EA9B0  40 81 00 08 */	ble lbl_800EDDD8
/* 800EDDD4 000EA9B4  D0 23 23 44 */	stfs f1, 0x2344(r3)
lbl_800EDDD8:
/* 800EDDD8 000EA9B8  80 03 06 5C */	lwz r0, 0x65c(r3)
/* 800EDDDC 000EA9BC  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 800EDDE0 000EA9C0  40 82 00 3C */	bne lbl_800EDE1C
/* 800EDDE4 000EA9C4  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800EDDE8 000EA9C8  3C 80 00 04 */	lis r4, 0x00040010@ha
/* 800EDDEC 000EA9CC  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EDDF0 000EA9D0  7F E3 FB 78 */	mr r3, r31
/* 800EDDF4 000EA9D4  FC 60 08 90 */	fmr f3, f1
/* 800EDDF8 000EA9D8  38 A4 00 10 */	addi r5, r4, 0x00040010@l
/* 800EDDFC 000EA9DC  38 80 01 5A */	li r4, 0x15a
/* 800EDE00 000EA9E0  38 C0 00 00 */	li r6, 0
/* 800EDE04 000EA9E4  4B F7 B5 A9 */	bl Fighter_ChangeMotionState
/* 800EDE08 000EA9E8  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EDE0C 000EA9EC  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800EDE10 000EA9F0  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EDE14 000EA9F4  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EDE18 000EA9F8  90 04 21 E4 */	stw r0, 0x21e4(r4)
lbl_800EDE1C:
/* 800EDE1C 000EA9FC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EDE20 000EAA00  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EDE24 000EAA04  38 21 00 20 */	addi r1, r1, 0x20
/* 800EDE28 000EAA08  7C 08 03 A6 */	mtlr r0
/* 800EDE2C 000EAA0C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialNStart_IASA(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->mv.lk.specialn.x0.x != 0) {
        fp->mv.lk.specialn.x0.y += 1;
        if (fp->mv.lk.specialn.x0.y > da->x0) {
            fp->mv.lk.specialn.x0.y = da->x0;
        }
        /// @todo Shared with #ftLk_SpecialNLoop_IASA
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNEnd, mf, NULL, 0,
                                      1, 0);
            setCallbacks(gobj);
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialNLoop_IASA(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EDE30 000EAA10  7C 08 02 A6 */	mflr r0
/* 800EDE34 000EAA14  90 01 00 04 */	stw r0, 4(r1)
/* 800EDE38 000EAA18  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800EDE3C 000EAA1C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800EDE40 000EAA20  7C 7F 1B 78 */	mr r31, r3
/* 800EDE44 000EAA24  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800EDE48 000EAA28  80 64 02 D4 */	lwz r3, 0x2d4(r4)
/* 800EDE4C 000EAA2C  C0 03 00 00 */	lfs f0, 0(r3)
/* 800EDE50 000EAA30  D0 04 23 44 */	stfs f0, 0x2344(r4)
/* 800EDE54 000EAA34  80 04 06 5C */	lwz r0, 0x65c(r4)
/* 800EDE58 000EAA38  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 800EDE5C 000EAA3C  40 82 00 3C */	bne lbl_800EDE98
/* 800EDE60 000EAA40  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800EDE64 000EAA44  3C 80 00 04 */	lis r4, 0x00040010@ha
/* 800EDE68 000EAA48  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EDE6C 000EAA4C  7F E3 FB 78 */	mr r3, r31
/* 800EDE70 000EAA50  FC 60 08 90 */	fmr f3, f1
/* 800EDE74 000EAA54  38 A4 00 10 */	addi r5, r4, 0x00040010@l
/* 800EDE78 000EAA58  38 80 01 5A */	li r4, 0x15a
/* 800EDE7C 000EAA5C  38 C0 00 00 */	li r6, 0
/* 800EDE80 000EAA60  4B F7 B5 2D */	bl Fighter_ChangeMotionState
/* 800EDE84 000EAA64  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EDE88 000EAA68  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800EDE8C 000EAA6C  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EDE90 000EAA70  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EDE94 000EAA74  90 04 21 E4 */	stw r0, 0x21e4(r4)
lbl_800EDE98:
/* 800EDE98 000EAA78  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800EDE9C 000EAA7C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800EDEA0 000EAA80  38 21 00 28 */	addi r1, r1, 0x28
/* 800EDEA4 000EAA84  7C 08 03 A6 */	mtlr r0
/* 800EDEA8 000EAA88  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void doLoopIASA(ftLk_GObj* gobj, FtMotionId msid)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    fp->mv.lk.specialn.x0.y = da->x0;
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        Fighter_ChangeMotionState(gobj, msid, mf, NULL, 0, 1, 0);
        setCallbacks(gobj);
    }
}

void ftLk_SpecialNLoop_IASA(ftLk_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    doLoopIASA(gobj, ftLk_MS_SpecialNEnd);
}
#endif

void ftLk_SpecialNEnd_IASA(ftLk_GObj* gobj) {}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNStart_IASA(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EDEB0 000EAA90  7C 08 02 A6 */	mflr r0
/* 800EDEB4 000EAA94  90 01 00 04 */	stw r0, 4(r1)
/* 800EDEB8 000EAA98  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EDEBC 000EAA9C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EDEC0 000EAAA0  7C 7F 1B 78 */	mr r31, r3
/* 800EDEC4 000EAAA4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800EDEC8 000EAAA8  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800EDECC 000EAAAC  C0 03 23 40 */	lfs f0, 0x2340(r3)
/* 800EDED0 000EAAB0  80 83 02 D4 */	lwz r4, 0x2d4(r3)
/* 800EDED4 000EAAB4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800EDED8 000EAAB8  41 82 00 6C */	beq lbl_800EDF44
/* 800EDEDC 000EAABC  C0 23 23 44 */	lfs f1, 0x2344(r3)
/* 800EDEE0 000EAAC0  C0 02 99 68 */	lfs f0, ftLk_Init_804D9348
/* 800EDEE4 000EAAC4  EC 01 00 2A */	fadds f0, f1, f0
/* 800EDEE8 000EAAC8  D0 03 23 44 */	stfs f0, 0x2344(r3)
/* 800EDEEC 000EAACC  C0 03 23 44 */	lfs f0, 0x2344(r3)
/* 800EDEF0 000EAAD0  C0 24 00 00 */	lfs f1, 0(r4)
/* 800EDEF4 000EAAD4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800EDEF8 000EAAD8  40 81 00 08 */	ble lbl_800EDF00
/* 800EDEFC 000EAADC  D0 23 23 44 */	stfs f1, 0x2344(r3)
lbl_800EDF00:
/* 800EDF00 000EAAE0  80 03 06 5C */	lwz r0, 0x65c(r3)
/* 800EDF04 000EAAE4  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 800EDF08 000EAAE8  40 82 00 3C */	bne lbl_800EDF44
/* 800EDF0C 000EAAEC  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800EDF10 000EAAF0  3C 80 00 04 */	lis r4, 0x00040010@ha
/* 800EDF14 000EAAF4  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EDF18 000EAAF8  7F E3 FB 78 */	mr r3, r31
/* 800EDF1C 000EAAFC  FC 60 08 90 */	fmr f3, f1
/* 800EDF20 000EAB00  38 A4 00 10 */	addi r5, r4, 0x00040010@l
/* 800EDF24 000EAB04  38 80 01 5D */	li r4, 0x15d
/* 800EDF28 000EAB08  38 C0 00 00 */	li r6, 0
/* 800EDF2C 000EAB0C  4B F7 B4 81 */	bl Fighter_ChangeMotionState
/* 800EDF30 000EAB10  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EDF34 000EAB14  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800EDF38 000EAB18  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EDF3C 000EAB1C  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EDF40 000EAB20  90 04 21 E4 */	stw r0, 0x21e4(r4)
lbl_800EDF44:
/* 800EDF44 000EAB24  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EDF48 000EAB28  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EDF4C 000EAB2C  38 21 00 20 */	addi r1, r1, 0x20
/* 800EDF50 000EAB30  7C 08 03 A6 */	mtlr r0
/* 800EDF54 000EAB34  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialAirNStart_IASA(ftLk_GObj* gobj)
{
    /// @todo Same as #ftLk_SpecialNStart_IASA with different MSID
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->mv.lk.specialn.x0.x != 0) {
        fp->mv.lk.specialn.x0.y += 1;
        if (fp->mv.lk.specialn.x0.y > da->x0) {
            fp->mv.lk.specialn.x0.y = da->x0;
        }
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNEnd, mf, NULL,
                                      0, 1, 0);
            setCallbacks(gobj);
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNLoop_IASA(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EDF58 000EAB38  7C 08 02 A6 */	mflr r0
/* 800EDF5C 000EAB3C  90 01 00 04 */	stw r0, 4(r1)
/* 800EDF60 000EAB40  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800EDF64 000EAB44  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800EDF68 000EAB48  7C 7F 1B 78 */	mr r31, r3
/* 800EDF6C 000EAB4C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800EDF70 000EAB50  80 64 02 D4 */	lwz r3, 0x2d4(r4)
/* 800EDF74 000EAB54  C0 03 00 00 */	lfs f0, 0(r3)
/* 800EDF78 000EAB58  D0 04 23 44 */	stfs f0, 0x2344(r4)
/* 800EDF7C 000EAB5C  80 04 06 5C */	lwz r0, 0x65c(r4)
/* 800EDF80 000EAB60  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 800EDF84 000EAB64  40 82 00 3C */	bne lbl_800EDFC0
/* 800EDF88 000EAB68  C0 22 99 60 */	lfs f1, ftLk_Init_804D9340
/* 800EDF8C 000EAB6C  3C 80 00 04 */	lis r4, 0x00040010@ha
/* 800EDF90 000EAB70  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EDF94 000EAB74  7F E3 FB 78 */	mr r3, r31
/* 800EDF98 000EAB78  FC 60 08 90 */	fmr f3, f1
/* 800EDF9C 000EAB7C  38 A4 00 10 */	addi r5, r4, 0x00040010@l
/* 800EDFA0 000EAB80  38 80 01 5D */	li r4, 0x15d
/* 800EDFA4 000EAB84  38 C0 00 00 */	li r6, 0
/* 800EDFA8 000EAB88  4B F7 B4 05 */	bl Fighter_ChangeMotionState
/* 800EDFAC 000EAB8C  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EDFB0 000EAB90  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800EDFB4 000EAB94  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EDFB8 000EAB98  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EDFBC 000EAB9C  90 04 21 E4 */	stw r0, 0x21e4(r4)
lbl_800EDFC0:
/* 800EDFC0 000EABA0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800EDFC4 000EABA4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800EDFC8 000EABA8  38 21 00 28 */	addi r1, r1, 0x28
/* 800EDFCC 000EABAC  7C 08 03 A6 */	mtlr r0
/* 800EDFD0 000EABB0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialAirNLoop_IASA(ftLk_GObj* gobj)
{
    doLoopIASA(gobj, ftLk_MS_SpecialAirNLoop);
}
#endif

void ftLk_SpecialAirNEnd_IASA(ftLk_GObj* gobj) {}

void ftLk_SpecialNStart_Phys(ftLk_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialNLoop_Phys(ftLk_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialNEnd_Phys(ftLk_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialAirNStart_Phys(ftLk_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftLk_SpecialAirNLoop_Phys(ftLk_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftLk_SpecialAirNEnd_Phys(ftLk_GObj* gobj)
{
    ft_80084EEC(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialNStart_Coll(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EE098 000EAC78  7C 08 02 A6 */	mflr r0
/* 800EE09C 000EAC7C  90 01 00 04 */	stw r0, 4(r1)
/* 800EE0A0 000EAC80  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EE0A4 000EAC84  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EE0A8 000EAC88  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800EE0AC 000EAC8C  7C 7E 1B 78 */	mr r30, r3
/* 800EE0B0 000EAC90  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EE0B4 000EAC94  4B F9 46 55 */	bl ft_80082708
/* 800EE0B8 000EAC98  2C 03 00 00 */	cmpwi r3, 0
/* 800EE0BC 000EAC9C  40 82 00 4C */	bne lbl_800EE108
/* 800EE0C0 000EACA0  7F E3 FB 78 */	mr r3, r31
/* 800EE0C4 000EACA4  4B F8 F5 11 */	bl ftCommon_8007D5D4
/* 800EE0C8 000EACA8  3C 80 0C 4C */	lis r4, 0x0C4C5090@ha
/* 800EE0CC 000EACAC  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800EE0D0 000EACB0  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EE0D4 000EACB4  7F C3 F3 78 */	mr r3, r30
/* 800EE0D8 000EACB8  C0 62 99 60 */	lfs f3, ftLk_Init_804D9340
/* 800EE0DC 000EACBC  38 A4 50 90 */	addi r5, r4, 0x0C4C5090@l
/* 800EE0E0 000EACC0  38 80 01 5B */	li r4, 0x15b
/* 800EE0E4 000EACC4  38 C0 00 00 */	li r6, 0
/* 800EE0E8 000EACC8  4B F7 B2 C5 */	bl Fighter_ChangeMotionState
/* 800EE0EC 000EACCC  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EE0F0 000EACD0  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800EE0F4 000EACD4  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EE0F8 000EACD8  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EE0FC 000EACDC  7F C3 F3 78 */	mr r3, r30
/* 800EE100 000EACE0  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800EE104 000EACE4  4B F8 0A A1 */	bl ftAnim_8006EBA4
lbl_800EE108:
/* 800EE108 000EACE8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EE10C 000EACEC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EE110 000EACF0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800EE114 000EACF4  38 21 00 20 */	addi r1, r1, 0x20
/* 800EE118 000EACF8  7C 08 03 A6 */	mtlr r0
/* 800EE11C 000EACFC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static MotionFlags const coll_mf =
    Ft_MF_SkipModel | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static void doColl(ftLk_GObj* gobj, FtMotionId msid)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, msid, coll_mf, NULL,
                                  fp->cur_anim_frame, 1, 0);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftLk_SpecialNStart_Coll(ftLk_GObj* gobj)
{
    doColl(gobj, ftLk_MS_SpecialAirNStart);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialNLoop_Coll(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EE120 000EAD00  7C 08 02 A6 */	mflr r0
/* 800EE124 000EAD04  90 01 00 04 */	stw r0, 4(r1)
/* 800EE128 000EAD08  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EE12C 000EAD0C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EE130 000EAD10  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800EE134 000EAD14  7C 7E 1B 78 */	mr r30, r3
/* 800EE138 000EAD18  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EE13C 000EAD1C  4B F9 45 CD */	bl ft_80082708
/* 800EE140 000EAD20  2C 03 00 00 */	cmpwi r3, 0
/* 800EE144 000EAD24  40 82 00 4C */	bne lbl_800EE190
/* 800EE148 000EAD28  7F E3 FB 78 */	mr r3, r31
/* 800EE14C 000EAD2C  4B F8 F4 89 */	bl ftCommon_8007D5D4
/* 800EE150 000EAD30  3C 80 0C 4C */	lis r4, 0x0C4C5090@ha
/* 800EE154 000EAD34  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800EE158 000EAD38  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EE15C 000EAD3C  7F C3 F3 78 */	mr r3, r30
/* 800EE160 000EAD40  C0 62 99 60 */	lfs f3, ftLk_Init_804D9340
/* 800EE164 000EAD44  38 A4 50 90 */	addi r5, r4, 0x0C4C5090@l
/* 800EE168 000EAD48  38 80 01 5C */	li r4, 0x15c
/* 800EE16C 000EAD4C  38 C0 00 00 */	li r6, 0
/* 800EE170 000EAD50  4B F7 B2 3D */	bl Fighter_ChangeMotionState
/* 800EE174 000EAD54  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EE178 000EAD58  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800EE17C 000EAD5C  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EE180 000EAD60  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EE184 000EAD64  7F C3 F3 78 */	mr r3, r30
/* 800EE188 000EAD68  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800EE18C 000EAD6C  4B F8 0A 19 */	bl ftAnim_8006EBA4
lbl_800EE190:
/* 800EE190 000EAD70  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EE194 000EAD74  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EE198 000EAD78  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800EE19C 000EAD7C  38 21 00 20 */	addi r1, r1, 0x20
/* 800EE1A0 000EAD80  7C 08 03 A6 */	mtlr r0
/* 800EE1A4 000EAD84  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialNLoop_Coll(ftLk_GObj* gobj)
{
    doColl(gobj, ftLk_MS_SpecialAirNLoop);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialNEnd_Coll(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EE1A8 000EAD88  7C 08 02 A6 */	mflr r0
/* 800EE1AC 000EAD8C  90 01 00 04 */	stw r0, 4(r1)
/* 800EE1B0 000EAD90  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800EE1B4 000EAD94  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 800EE1B8 000EAD98  7C 7B 1B 78 */	mr r27, r3
/* 800EE1BC 000EAD9C  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 800EE1C0 000EADA0  80 1D 22 04 */	lwz r0, 0x2204(r29)
/* 800EE1C4 000EADA4  7F BC EB 78 */	mr r28, r29
/* 800EE1C8 000EADA8  83 DD 02 D4 */	lwz r30, 0x2d4(r29)
/* 800EE1CC 000EADAC  28 00 00 01 */	cmplwi r0, 1
/* 800EE1D0 000EADB0  40 82 00 A4 */	bne lbl_800EE274
/* 800EE1D4 000EADB4  80 1D 22 3C */	lwz r0, 0x223c(r29)
/* 800EE1D8 000EADB8  28 00 00 00 */	cmplwi r0, 0
/* 800EE1DC 000EADBC  41 82 00 98 */	beq lbl_800EE274
/* 800EE1E0 000EADC0  38 00 00 00 */	li r0, 0
/* 800EE1E4 000EADC4  90 1D 22 04 */	stw r0, 0x2204(r29)
/* 800EE1E8 000EADC8  38 7D 00 00 */	addi r3, r29, 0
/* 800EE1EC 000EADCC  38 80 00 31 */	li r4, 0x31
/* 800EE1F0 000EADD0  4B F8 6E 1D */	bl ftParts_8007500C
/* 800EE1F4 000EADD4  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 800EE1F8 000EADD8  54 60 20 36 */	slwi r0, r3, 4
/* 800EE1FC 000EADDC  38 A1 00 24 */	addi r5, r1, 0x24
/* 800EE200 000EADE0  7C 64 00 2E */	lwzx r3, r4, r0
/* 800EE204 000EADE4  38 80 00 00 */	li r4, 0
/* 800EE208 000EADE8  4B F1 CF C5 */	bl lb_8000B1CC
/* 800EE20C 000EADEC  38 7D 00 00 */	addi r3, r29, 0
/* 800EE210 000EADF0  38 80 00 1F */	li r4, 0x1f
/* 800EE214 000EADF4  4B F8 6D F9 */	bl ftParts_8007500C
/* 800EE218 000EADF8  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 800EE21C 000EADFC  54 60 20 36 */	slwi r0, r3, 4
/* 800EE220 000EAE00  38 A1 00 30 */	addi r5, r1, 0x30
/* 800EE224 000EAE04  7C 64 00 2E */	lwzx r3, r4, r0
/* 800EE228 000EAE08  38 80 00 00 */	li r4, 0
/* 800EE22C 000EAE0C  4B F1 CF A1 */	bl lb_8000B1CC
/* 800EE230 000EAE10  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800EE234 000EAE14  38 81 00 24 */	addi r4, r1, 0x24
/* 800EE238 000EAE18  C0 22 99 64 */	lfs f1, ftLk_Init_804D9344
/* 800EE23C 000EAE1C  38 A1 00 30 */	addi r5, r1, 0x30
/* 800EE240 000EAE20  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800EE244 000EAE24  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800EE248 000EAE28  83 FD 19 74 */	lwz r31, 0x1974(r29)
/* 800EE24C 000EAE2C  80 7D 22 3C */	lwz r3, 0x223c(r29)
/* 800EE250 000EAE30  C0 5D 23 44 */	lfs f2, 0x2344(r29)
/* 800EE254 000EAE34  C0 7E 00 00 */	lfs f3, 0(r30)
/* 800EE258 000EAE38  48 1B A2 B5 */	bl it_802A850C
/* 800EE25C 000EAE3C  7F 63 DB 78 */	mr r3, r27
/* 800EE260 000EAE40  4B FF E9 AD */	bl ftLk_SpecialN_UnsetArrow
/* 800EE264 000EAE44  93 FD 19 74 */	stw r31, 0x1974(r29)
/* 800EE268 000EAE48  38 7B 00 00 */	addi r3, r27, 0
/* 800EE26C 000EAE4C  38 80 00 00 */	li r4, 0
/* 800EE270 000EAE50  4B FA 65 A9 */	bl ftCo_80094818
lbl_800EE274:
/* 800EE274 000EAE54  7F 63 DB 78 */	mr r3, r27
/* 800EE278 000EAE58  4B F9 44 91 */	bl ft_80082708
/* 800EE27C 000EAE5C  2C 03 00 00 */	cmpwi r3, 0
/* 800EE280 000EAE60  40 82 00 4C */	bne lbl_800EE2CC
/* 800EE284 000EAE64  7F 83 E3 78 */	mr r3, r28
/* 800EE288 000EAE68  4B F8 F3 4D */	bl ftCommon_8007D5D4
/* 800EE28C 000EAE6C  3C 80 0C 4C */	lis r4, 0x0C4C5090@ha
/* 800EE290 000EAE70  C0 3C 08 94 */	lfs f1, 0x894(r28)
/* 800EE294 000EAE74  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EE298 000EAE78  7F 63 DB 78 */	mr r3, r27
/* 800EE29C 000EAE7C  C0 62 99 60 */	lfs f3, ftLk_Init_804D9340
/* 800EE2A0 000EAE80  38 A4 50 90 */	addi r5, r4, 0x0C4C5090@l
/* 800EE2A4 000EAE84  38 80 01 5D */	li r4, 0x15d
/* 800EE2A8 000EAE88  38 C0 00 00 */	li r6, 0
/* 800EE2AC 000EAE8C  4B F7 B1 01 */	bl Fighter_ChangeMotionState
/* 800EE2B0 000EAE90  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EE2B4 000EAE94  80 9B 00 2C */	lwz r4, 0x2c(r27)
/* 800EE2B8 000EAE98  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EE2BC 000EAE9C  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EE2C0 000EAEA0  7F 63 DB 78 */	mr r3, r27
/* 800EE2C4 000EAEA4  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800EE2C8 000EAEA8  4B F8 08 DD */	bl ftAnim_8006EBA4
lbl_800EE2CC:
/* 800EE2CC 000EAEAC  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 800EE2D0 000EAEB0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800EE2D4 000EAEB4  38 21 00 58 */	addi r1, r1, 0x58
/* 800EE2D8 000EAEB8  7C 08 03 A6 */	mtlr r0
/* 800EE2DC 000EAEBC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline void doEndColl(ftLk_GObj* gobj)
{
/// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12] = { 0 };
#endif
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    Item_GObj* item_gobj;
    if (fp->cmd_vars[cmd_unk1_bool] == true && fp->fv.lk.arrow_gobj != NULL) {
        fp->cmd_vars[cmd_unk1_bool] = false;
        {
            Vec3 rpos, lpos;
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                        NULL, &rpos);
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                        NULL, &lpos);
            rpos.z = lpos.z = 0;
            item_gobj = fp->item_gobj;
            it_802A850C(fp->fv.lk.arrow_gobj, &rpos, &lpos, 5 * deg_to_rad,
                        fp->mv.lk.specialn.x0.y, da->x0);
            ftLk_SpecialN_UnsetArrow(gobj);
            fp->item_gobj = item_gobj;
        }
        ftCo_80094818(gobj, false);
    }
}

void ftLk_SpecialNEnd_Coll(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    doEndColl(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNEnd, coll_mf, NULL,
                                  fp->cur_anim_frame, 1, 0);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNStart_Coll(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EE2E0 000EAEC0  7C 08 02 A6 */	mflr r0
/* 800EE2E4 000EAEC4  90 01 00 04 */	stw r0, 4(r1)
/* 800EE2E8 000EAEC8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EE2EC 000EAECC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EE2F0 000EAED0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800EE2F4 000EAED4  7C 7E 1B 78 */	mr r30, r3
/* 800EE2F8 000EAED8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EE2FC 000EAEDC  4B F9 3A 11 */	bl ft_80081D0C
/* 800EE300 000EAEE0  2C 03 00 01 */	cmpwi r3, 1
/* 800EE304 000EAEE4  40 82 00 4C */	bne lbl_800EE350
/* 800EE308 000EAEE8  7F E3 FB 78 */	mr r3, r31
/* 800EE30C 000EAEEC  4B F8 F4 F1 */	bl ftCommon_8007D7FC
/* 800EE310 000EAEF0  3C 80 0C 4C */	lis r4, 0x0C4C5090@ha
/* 800EE314 000EAEF4  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800EE318 000EAEF8  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EE31C 000EAEFC  7F C3 F3 78 */	mr r3, r30
/* 800EE320 000EAF00  C0 62 99 60 */	lfs f3, ftLk_Init_804D9340
/* 800EE324 000EAF04  38 A4 50 90 */	addi r5, r4, 0x0C4C5090@l
/* 800EE328 000EAF08  38 80 01 58 */	li r4, 0x158
/* 800EE32C 000EAF0C  38 C0 00 00 */	li r6, 0
/* 800EE330 000EAF10  4B F7 B0 7D */	bl Fighter_ChangeMotionState
/* 800EE334 000EAF14  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EE338 000EAF18  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800EE33C 000EAF1C  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EE340 000EAF20  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EE344 000EAF24  7F C3 F3 78 */	mr r3, r30
/* 800EE348 000EAF28  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800EE34C 000EAF2C  4B F8 08 59 */	bl ftAnim_8006EBA4
lbl_800EE350:
/* 800EE350 000EAF30  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EE354 000EAF34  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EE358 000EAF38  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800EE35C 000EAF3C  38 21 00 20 */	addi r1, r1, 0x20
/* 800EE360 000EAF40  7C 08 03 A6 */	mtlr r0
/* 800EE364 000EAF44  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static void doAirColl(ftLk_GObj* gobj, FtMotionId msid)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, msid, coll_mf, NULL,
                                  fp->cur_anim_frame, 1, 0);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftLk_SpecialAirNStart_Coll(ftLk_GObj* gobj)
{
    doAirColl(gobj, ftLk_MS_SpecialNStart);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNLoop_Coll(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EE368 000EAF48  7C 08 02 A6 */	mflr r0
/* 800EE36C 000EAF4C  90 01 00 04 */	stw r0, 4(r1)
/* 800EE370 000EAF50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EE374 000EAF54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EE378 000EAF58  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800EE37C 000EAF5C  7C 7E 1B 78 */	mr r30, r3
/* 800EE380 000EAF60  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EE384 000EAF64  4B F9 39 89 */	bl ft_80081D0C
/* 800EE388 000EAF68  2C 03 00 01 */	cmpwi r3, 1
/* 800EE38C 000EAF6C  40 82 00 4C */	bne lbl_800EE3D8
/* 800EE390 000EAF70  7F E3 FB 78 */	mr r3, r31
/* 800EE394 000EAF74  4B F8 F4 69 */	bl ftCommon_8007D7FC
/* 800EE398 000EAF78  3C 80 0C 4C */	lis r4, 0x0C4C5090@ha
/* 800EE39C 000EAF7C  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800EE3A0 000EAF80  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EE3A4 000EAF84  7F C3 F3 78 */	mr r3, r30
/* 800EE3A8 000EAF88  C0 62 99 60 */	lfs f3, ftLk_Init_804D9340
/* 800EE3AC 000EAF8C  38 A4 50 90 */	addi r5, r4, 0x0C4C5090@l
/* 800EE3B0 000EAF90  38 80 01 59 */	li r4, 0x159
/* 800EE3B4 000EAF94  38 C0 00 00 */	li r6, 0
/* 800EE3B8 000EAF98  4B F7 AF F5 */	bl Fighter_ChangeMotionState
/* 800EE3BC 000EAF9C  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EE3C0 000EAFA0  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 800EE3C4 000EAFA4  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EE3C8 000EAFA8  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EE3CC 000EAFAC  7F C3 F3 78 */	mr r3, r30
/* 800EE3D0 000EAFB0  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800EE3D4 000EAFB4  4B F8 07 D1 */	bl ftAnim_8006EBA4
lbl_800EE3D8:
/* 800EE3D8 000EAFB8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EE3DC 000EAFBC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EE3E0 000EAFC0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800EE3E4 000EAFC4  38 21 00 20 */	addi r1, r1, 0x20
/* 800EE3E8 000EAFC8  7C 08 03 A6 */	mtlr r0
/* 800EE3EC 000EAFCC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftLk_SpecialAirNLoop_Coll(ftLk_GObj* gobj)
{
    doAirColl(gobj, ftLk_MS_SpecialNLoop);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftLk_SpecialAirNEnd_Coll(ftLk_GObj*)
{ // clang-format off
    nofralloc
/* 800EE3F0 000EAFD0  7C 08 02 A6 */	mflr r0
/* 800EE3F4 000EAFD4  90 01 00 04 */	stw r0, 4(r1)
/* 800EE3F8 000EAFD8  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800EE3FC 000EAFDC  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 800EE400 000EAFE0  7C 7B 1B 78 */	mr r27, r3
/* 800EE404 000EAFE4  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 800EE408 000EAFE8  80 1D 22 04 */	lwz r0, 0x2204(r29)
/* 800EE40C 000EAFEC  7F BC EB 78 */	mr r28, r29
/* 800EE410 000EAFF0  83 DD 02 D4 */	lwz r30, 0x2d4(r29)
/* 800EE414 000EAFF4  28 00 00 01 */	cmplwi r0, 1
/* 800EE418 000EAFF8  40 82 00 A4 */	bne lbl_800EE4BC
/* 800EE41C 000EAFFC  80 1D 22 3C */	lwz r0, 0x223c(r29)
/* 800EE420 000EB000  28 00 00 00 */	cmplwi r0, 0
/* 800EE424 000EB004  41 82 00 98 */	beq lbl_800EE4BC
/* 800EE428 000EB008  38 00 00 00 */	li r0, 0
/* 800EE42C 000EB00C  90 1D 22 04 */	stw r0, 0x2204(r29)
/* 800EE430 000EB010  38 7D 00 00 */	addi r3, r29, 0
/* 800EE434 000EB014  38 80 00 31 */	li r4, 0x31
/* 800EE438 000EB018  4B F8 6B D5 */	bl ftParts_8007500C
/* 800EE43C 000EB01C  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 800EE440 000EB020  54 60 20 36 */	slwi r0, r3, 4
/* 800EE444 000EB024  38 A1 00 24 */	addi r5, r1, 0x24
/* 800EE448 000EB028  7C 64 00 2E */	lwzx r3, r4, r0
/* 800EE44C 000EB02C  38 80 00 00 */	li r4, 0
/* 800EE450 000EB030  4B F1 CD 7D */	bl lb_8000B1CC
/* 800EE454 000EB034  38 7D 00 00 */	addi r3, r29, 0
/* 800EE458 000EB038  38 80 00 1F */	li r4, 0x1f
/* 800EE45C 000EB03C  4B F8 6B B1 */	bl ftParts_8007500C
/* 800EE460 000EB040  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 800EE464 000EB044  54 60 20 36 */	slwi r0, r3, 4
/* 800EE468 000EB048  38 A1 00 30 */	addi r5, r1, 0x30
/* 800EE46C 000EB04C  7C 64 00 2E */	lwzx r3, r4, r0
/* 800EE470 000EB050  38 80 00 00 */	li r4, 0
/* 800EE474 000EB054  4B F1 CD 59 */	bl lb_8000B1CC
/* 800EE478 000EB058  C0 02 99 60 */	lfs f0, ftLk_Init_804D9340
/* 800EE47C 000EB05C  38 81 00 24 */	addi r4, r1, 0x24
/* 800EE480 000EB060  C0 22 99 64 */	lfs f1, ftLk_Init_804D9344
/* 800EE484 000EB064  38 A1 00 30 */	addi r5, r1, 0x30
/* 800EE488 000EB068  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800EE48C 000EB06C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800EE490 000EB070  83 FD 19 74 */	lwz r31, 0x1974(r29)
/* 800EE494 000EB074  80 7D 22 3C */	lwz r3, 0x223c(r29)
/* 800EE498 000EB078  C0 5D 23 44 */	lfs f2, 0x2344(r29)
/* 800EE49C 000EB07C  C0 7E 00 00 */	lfs f3, 0(r30)
/* 800EE4A0 000EB080  48 1B A0 6D */	bl it_802A850C
/* 800EE4A4 000EB084  7F 63 DB 78 */	mr r3, r27
/* 800EE4A8 000EB088  4B FF E7 65 */	bl ftLk_SpecialN_UnsetArrow
/* 800EE4AC 000EB08C  93 FD 19 74 */	stw r31, 0x1974(r29)
/* 800EE4B0 000EB090  38 7B 00 00 */	addi r3, r27, 0
/* 800EE4B4 000EB094  38 80 00 00 */	li r4, 0
/* 800EE4B8 000EB098  4B FA 63 61 */	bl ftCo_80094818
lbl_800EE4BC:
/* 800EE4BC 000EB09C  7F 63 DB 78 */	mr r3, r27
/* 800EE4C0 000EB0A0  4B F9 38 4D */	bl ft_80081D0C
/* 800EE4C4 000EB0A4  2C 03 00 01 */	cmpwi r3, 1
/* 800EE4C8 000EB0A8  40 82 00 4C */	bne lbl_800EE514
/* 800EE4CC 000EB0AC  7F 83 E3 78 */	mr r3, r28
/* 800EE4D0 000EB0B0  4B F8 F3 2D */	bl ftCommon_8007D7FC
/* 800EE4D4 000EB0B4  3C 80 0C 4C */	lis r4, 0x0C4C5090@ha
/* 800EE4D8 000EB0B8  C0 3C 08 94 */	lfs f1, 0x894(r28)
/* 800EE4DC 000EB0BC  C0 42 99 68 */	lfs f2, ftLk_Init_804D9348
/* 800EE4E0 000EB0C0  7F 63 DB 78 */	mr r3, r27
/* 800EE4E4 000EB0C4  C0 62 99 60 */	lfs f3, ftLk_Init_804D9340
/* 800EE4E8 000EB0C8  38 A4 50 90 */	addi r5, r4, 0x0C4C5090@l
/* 800EE4EC 000EB0CC  38 80 01 5A */	li r4, 0x15a
/* 800EE4F0 000EB0D0  38 C0 00 00 */	li r6, 0
/* 800EE4F4 000EB0D4  4B F7 AE B9 */	bl Fighter_ChangeMotionState
/* 800EE4F8 000EB0D8  3C 60 80 0F */	lis r3, ftLk_800EAF58@ha
/* 800EE4FC 000EB0DC  80 9B 00 2C */	lwz r4, 0x2c(r27)
/* 800EE500 000EB0E0  38 03 AF 58 */	addi r0, r3, ftLk_800EAF58@l
/* 800EE504 000EB0E4  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 800EE508 000EB0E8  7F 63 DB 78 */	mr r3, r27
/* 800EE50C 000EB0EC  90 04 21 E4 */	stw r0, 0x21e4(r4)
/* 800EE510 000EB0F0  4B F8 06 95 */	bl ftAnim_8006EBA4
lbl_800EE514:
/* 800EE514 000EB0F4  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 800EE518 000EB0F8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800EE51C 000EB0FC  38 21 00 58 */	addi r1, r1, 0x58
/* 800EE520 000EB100  7C 08 03 A6 */	mtlr r0
/* 800EE524 000EB104  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo Combine with #ftLk_SpecialNEnd_Coll.
void ftLk_SpecialAirNEnd_Coll(ftLk_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    doEndColl(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNEnd, coll_mf, NULL,
                                  fp->cur_anim_frame, 1, 0);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}
#endif
