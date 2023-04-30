#include <platform.h>
#include "ft/forward.h"

#include "ftPe_FloatFall.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"

#include <baselib/gobj.h>

void ftPe_FloatFall_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CCDA8(gobj);
    }
}

void ftPe_FloatFall_IASA(HSD_GObj* gobj) {}

void ftPe_FloatFall_Phys(HSD_GObj* gobj)
{
    ft_800CC6C8();
}

void ftPe_FloatFall_Coll(HSD_GObj* gobj)
{
    ft_800831CC(gobj, ft_80096CC8, ft_80082B1C);
}

static void ftPe_8011BF34(HSD_GObj* gobj);

#if defined(MUST_MATCH) && !defined(WIP)
/* static */ float const lbl_804D97D0 = 0;
/* static */ float const lbl_804D97D4 = 1;
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
/* 8011BEC0 00118AA0  C0 02 9D F0 */	lfs f0, lbl_804D97D0
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
                HSD_GObj* igobj = fp->x1974_heldItem;
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
    fp->mv.pe.floatfall.x0 = 0;
    ft_8008CFAC(gobj, msid + ftCo_MS_CaptureDamageKoopa);
}
