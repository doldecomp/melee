#include <platform.h>
#include "ft/forward.h"

#include "ftPe_FloatAttack.h"

#include "ftPe_Float.h"
#include "ftPe_Init.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <baselib/gobj.h>

static void ftPe_8011BF34(HSD_GObj* gobj);

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm bool ftPe_8011BE80(HSD_GObj*)
{
    // clang-format off
    nofralloc
/* 8011BE80 00118A60  7C 08 02 A6 */	mflr r0
/* 8011BE84 00118A64  90 01 00 04 */	stw r0, 4(r1)
/* 8011BE88 00118A68  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8011BE8C 00118A6C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8011BE90 00118A70  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8011BE94 00118A74  7C 7E 1B 78 */	mr r30, r3
/* 8011BE98 00118A78  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8011BE9C 00118A7C  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8011BEA0 00118A80  3B E3 00 00 */	addi r31, r3, 0
/* 8011BEA4 00118A84  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8011BEA8 00118A88  40 82 00 14 */	bne lbl_8011BEBC
/* 8011BEAC 00118A8C  7F E3 FB 78 */	mr r3, r31
/* 8011BEB0 00118A90  4B FC 35 C9 */	bl ft_800DF478
/* 8011BEB4 00118A94  2C 03 00 00 */	cmpwi r3, 0
/* 8011BEB8 00118A98  41 82 00 60 */	beq lbl_8011BF18
lbl_8011BEBC:
/* 8011BEBC 00118A9C  C0 3F 22 30 */	lfs f1, 0x2230(r31)
/* 8011BEC0 00118AA0  C0 02 9D F0 */	lfs f0, 0.0f
/* 8011BEC4 00118AA4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8011BEC8 00118AA8  40 81 00 50 */	ble lbl_8011BF18
/* 8011BECC 00118AAC  7F E3 FB 78 */	mr r3, r31
/* 8011BED0 00118AB0  4B F7 0F 99 */	bl ft_8008CE68
/* 8011BED4 00118AB4  38 03 FF BF */	addi r0, r3, -65
/* 8011BED8 00118AB8  28 00 00 01 */	cmplwi r0, 1
/* 8011BEDC 00118ABC  41 81 00 2C */	bgt lbl_8011BF08
/* 8011BEE0 00118AC0  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8011BEE4 00118AC4  28 03 00 00 */	cmplwi r3, 0
/* 8011BEE8 00118AC8  41 82 00 20 */	beq lbl_8011BF08
/* 8011BEEC 00118ACC  48 14 F4 21 */	bl it_8026B30C
/* 8011BEF0 00118AD0  2C 03 00 03 */	cmpwi r3, 3
/* 8011BEF4 00118AD4  40 82 00 14 */	bne lbl_8011BF08
/* 8011BEF8 00118AD8  7F C3 F3 78 */	mr r3, r30
/* 8011BEFC 00118ADC  4B FB 1E A5 */	bl ft_800CDDA0
/* 8011BF00 00118AE0  38 60 00 01 */	li r3, 1
/* 8011BF04 00118AE4  48 00 00 18 */	b lbl_8011BF1C
lbl_8011BF08:
/* 8011BF08 00118AE8  7F C3 F3 78 */	mr r3, r30
/* 8011BF0C 00118AEC  48 00 00 29 */	bl ftPe_8011BF34
/* 8011BF10 00118AF0  38 60 00 01 */	li r3, 1
/* 8011BF14 00118AF4  48 00 00 08 */	b lbl_8011BF1C
lbl_8011BF18:
/* 8011BF18 00118AF8  38 60 00 00 */	li r3, 0
lbl_8011BF1C:
/* 8011BF1C 00118AFC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8011BF20 00118B00  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8011BF24 00118B04  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8011BF28 00118B08  38 21 00 20 */	addi r1, r1, 0x20
/* 8011BF2C 00118B0C  7C 08 03 A6 */	mtlr r0
/* 8011BF30 00118B10  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftPe_8011BE80(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A || ft_800DF478(fp)) {
        if (fp->fv.pe.x4 > 0) {
            if (ft_8008CE68(fp) - 65U <= 1) {
                HSD_GObj* igobj = fp->item_gobj;
                if (igobj != NULL && it_8026B30C(igobj) == 3) {
                    ft_800CDDA0(gobj);
                    return true;
                }
            }
            ftPe_8011BF34(gobj);
            return true;
        }
    }
    return false;
}
#endif

static void ftPe_8011BF34(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = ft_8008CE68(fp);
    fp->mv.pe.floatattack.x0 = 0;
    ft_8008CFAC(gobj, msid + ftCo_MS_CaptureDamageKoopa);
}

void ftPe_FloatAttackAir_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.x4 > 0) {
        fp->fv.pe.x4 -= 1;
    }
    if (ftCheckThrowB3(fp)) {
        fp->facing_dir = -fp->facing_dir;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.pe.floatattack.x0) {
            ft_800CC730(gobj);
        } else {
            ftPe_8011BB6C(gobj, false);
        }
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftPe_FloatAttackAir_IASA(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8011C044 00118C24  7C 08 02 A6 */	mflr r0
/* 8011C048 00118C28  90 01 00 04 */	stw r0, 4(r1)
/* 8011C04C 00118C2C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8011C050 00118C30  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8011C054 00118C34  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8011C058 00118C38  7C 7E 1B 78 */	mr r30, r3
/* 8011C05C 00118C3C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011C060 00118C40  7F E3 FB 78 */	mr r3, r31
/* 8011C064 00118C44  4B FF F9 BD */	bl ftPe_Float_CheckContinueInput
/* 8011C068 00118C48  2C 03 00 00 */	cmpwi r3, 0
/* 8011C06C 00118C4C  40 82 00 0C */	bne lbl_8011C078
/* 8011C070 00118C50  38 00 00 01 */	li r0, 1
/* 8011C074 00118C54  90 1F 23 40 */	stw r0, 0x2340(r31)
lbl_8011C078:
/* 8011C078 00118C58  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8011C07C 00118C5C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8011C080 00118C60  41 82 00 C8 */	beq lbl_8011C148
/* 8011C084 00118C64  38 7E 00 00 */	addi r3, r30, 0
/* 8011C088 00118C68  38 80 00 00 */	li r4, 0
/* 8011C08C 00118C6C  4B F7 92 9D */	bl ft_80095328
/* 8011C090 00118C70  2C 03 00 00 */	cmpwi r3, 0
/* 8011C094 00118C74  40 82 00 B4 */	bne lbl_8011C148
/* 8011C098 00118C78  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8011C09C 00118C7C  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8011C0A0 00118C80  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8011C0A4 00118C84  40 82 00 14 */	bne lbl_8011C0B8
/* 8011C0A8 00118C88  7F E3 FB 78 */	mr r3, r31
/* 8011C0AC 00118C8C  4B FC 33 CD */	bl ft_800DF478
/* 8011C0B0 00118C90  2C 03 00 00 */	cmpwi r3, 0
/* 8011C0B4 00118C94  41 82 00 7C */	beq lbl_8011C130
lbl_8011C0B8:
/* 8011C0B8 00118C98  C0 3F 22 30 */	lfs f1, 0x2230(r31)
/* 8011C0BC 00118C9C  C0 02 9D F0 */	lfs f0, 0.0f
/* 8011C0C0 00118CA0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8011C0C4 00118CA4  40 81 00 6C */	ble lbl_8011C130
/* 8011C0C8 00118CA8  7F E3 FB 78 */	mr r3, r31
/* 8011C0CC 00118CAC  4B F7 0D 9D */	bl ft_8008CE68
/* 8011C0D0 00118CB0  38 03 FF BF */	addi r0, r3, -65
/* 8011C0D4 00118CB4  28 00 00 01 */	cmplwi r0, 1
/* 8011C0D8 00118CB8  41 81 00 2C */	bgt lbl_8011C104
/* 8011C0DC 00118CBC  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8011C0E0 00118CC0  28 03 00 00 */	cmplwi r3, 0
/* 8011C0E4 00118CC4  41 82 00 20 */	beq lbl_8011C104
/* 8011C0E8 00118CC8  48 14 F2 25 */	bl it_8026B30C
/* 8011C0EC 00118CCC  2C 03 00 03 */	cmpwi r3, 3
/* 8011C0F0 00118CD0  40 82 00 14 */	bne lbl_8011C104
/* 8011C0F4 00118CD4  7F C3 F3 78 */	mr r3, r30
/* 8011C0F8 00118CD8  4B FB 1C A9 */	bl ft_800CDDA0
/* 8011C0FC 00118CDC  38 00 00 01 */	li r0, 1
/* 8011C100 00118CE0  48 00 00 34 */	b lbl_8011C134
lbl_8011C104:
/* 8011C104 00118CE4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8011C108 00118CE8  7F E3 FB 78 */	mr r3, r31
/* 8011C10C 00118CEC  4B F7 0D 5D */	bl ft_8008CE68
/* 8011C110 00118CF0  38 00 00 00 */	li r0, 0
/* 8011C114 00118CF4  38 83 00 00 */	addi r4, r3, 0
/* 8011C118 00118CF8  90 1F 23 40 */	stw r0, 0x2340(r31)
/* 8011C11C 00118CFC  38 7E 00 00 */	addi r3, r30, 0
/* 8011C120 00118D00  38 84 01 17 */	addi r4, r4, 0x117
/* 8011C124 00118D04  4B F7 0E 89 */	bl ft_8008CFAC
/* 8011C128 00118D08  38 00 00 01 */	li r0, 1
/* 8011C12C 00118D0C  48 00 00 08 */	b lbl_8011C134
lbl_8011C130:
/* 8011C130 00118D10  38 00 00 00 */	li r0, 0
lbl_8011C134:
/* 8011C134 00118D14  2C 00 00 00 */	cmpwi r0, 0
/* 8011C138 00118D18  40 82 00 10 */	bne lbl_8011C148
/* 8011C13C 00118D1C  7F C3 F3 78 */	mr r3, r30
/* 8011C140 00118D20  4B FA F7 31 */	bl ft_800CB870
/* 8011C144 00118D24  2C 03 00 00 */	cmpwi r3, 0
lbl_8011C148:
/* 8011C148 00118D28  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8011C14C 00118D2C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8011C150 00118D30  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8011C154 00118D34  38 21 00 20 */	addi r1, r1, 0x20
/* 8011C158 00118D38  7C 08 03 A6 */	mtlr r0
/* 8011C15C 00118D3C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftPe_FloatAttackAir_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftPe_Float_CheckContinueInput(fp)) {
        fp->mv.pe.floatattack.x0 = true;
    }
    if (fp->x2218_b0 && !ft_80095328(gobj, false)) {
        if (!ftPe_8011BE80(gobj)) {
            if (ft_800CB870(gobj)) {
                return;
            }
        }
    }
}
#endif

void ftPe_FloatAttackAir_Phys(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->mv.pe.floatattack.x0) {
        ft_80084DB0(gobj);
    } else {
        ftPe_Float_Phys(gobj);
    }
}

void ftPe_FloatAttackAir_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ft_8008D5FC);
}
