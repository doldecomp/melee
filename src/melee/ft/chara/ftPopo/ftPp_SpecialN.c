#include <platform.h>
#include <dolphin/mtx/forward.h>

#include "ftPp_SpecialN.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftPopo/types.h"
#include "it/items/it_27CF.h"

#include <common_structs.h>
#include <baselib/gobj.h>

#ifdef MUST_MATCH
#include "melee/ft/chara/ftPopo/ftPp_Init.h"
#include "melee/ft/ft_0877.h"
#include "melee/ft/ft_0881.h"
#include "melee/lb/lb_00B0.h"
#endif

void ftPp_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(gobj);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.nn.x222C = 0;

    Fighter_ChangeMotionState(gobj, 341, 0, 0.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftPp_SpecialN_8011F500;
}

void ftPp_SpecialAirN_Enter(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = (Fighter*) HSD_GObjGetUserData(gobj);
    ftIceClimberAttributes* icattr = fp->dat_attrs;

    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.nn.x222C = 0;

    if ((s32) fp->fv.nn.x224C == false) {
        fp->self_vel.y = icattr->x4;
        fp->fv.nn.x224C = true;
        fp->fv.nn.x2250 = 0.0f;
    } else {
        fp->fv.nn.x2250 = -10.0;
    }

    Fighter_ChangeMotionState(gobj, 342, 0, 0.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftPp_SpecialN_8011F500;
}

void ftPp_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPp_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftPp_SpecialN_IASA(HSD_GObj* arg0) {}

void ftPp_SpecialAirN_IASA(HSD_GObj* arg0) {}

void ftPp_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPp_SpecialN_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        Fighter* fp1;
        fp1 = GET_FIGHTER(gobj);
        if (fp1->fv.nn.x222C != 0U) {
            Fighter* fp2;
            it_802C17DC(fp1->fv.nn.x222C);
            fp2 = GET_FIGHTER(gobj);
            if ((u32) fp1->fv.nn.x222C == (u32) fp2->fv.nn.x222C) {
                fp2->fv.nn.x222C = 0U;
                fp2->death2_cb = 0U;
                fp2->take_dmg_cb = 0U;
            }
        }
        ftCo_800CC730(gobj);
    }
}

void ftPp_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter *fp, *fp1, *fp2;
    ftIceClimberAttributes* da;
    u8 _[16];

    fp = gobj->user_data;
    da = fp->dat_attrs;
    if (ft_80081D0C(gobj) != GA_Ground) {
        fp1 = gobj->user_data;
        if (fp1->fv.pp.x222C != 0) {
            it_802C17DC(fp1->fv.pp.x222C);
            fp2 = gobj->user_data;
            if (fp1->fv.pp.x222C == fp2->fv.pp.x222C) {
                fp2->fv.pp.x222C = 0U;
                fp2->death2_cb = NULL;
                fp2->take_dmg_cb = NULL;
            }
        }
        fp->fv.pp.x224C = 0;
        fp->fv.pp.x2250 = 0.0f;
        ftCo_800D5CB0(gobj, 0, da->x8);
    }
}

#ifdef MUST_MATCH
#pragma push
asm void ftPp_SpecialN_8011F500(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8011F500 0011C0E0  7C 08 02 A6 */	mflr r0
/* 8011F504 0011C0E4  90 01 00 04 */	stw r0, 4(r1)
/* 8011F508 0011C0E8  94 21 FF C8 */	stwu r1, -56(r1)
/* 8011F50C 0011C0EC  93 E1 00 34 */	stw r31, 52(r1)
/* 8011F510 0011C0F0  93 C1 00 30 */	stw r30, 48(r1)
/* 8011F514 0011C0F4  93 A1 00 2C */	stw r29, 44(r1)
/* 8011F518 0011C0F8  7C 7D 1B 78 */	mr r29, r3
/* 8011F51C 0011C0FC  80 63 00 2C */	lwz r3, 44(r3)
/* 8011F520 0011C100  80 03 22 00 */	lwz r0, 8704(r3)
/* 8011F524 0011C104  3B E3 00 00 */	addi r31, r3, 0
/* 8011F528 0011C108  28 00 00 00 */	cmplwi r0, 0
/* 8011F52C 0011C10C  41 82 01 44 */	beq lbl_8011F670
/* 8011F530 0011C110  28 00 00 01 */	cmplwi r0, 1
/* 8011F534 0011C114  40 82 00 A0 */	bne lbl_8011F5D4
/* 8011F538 0011C118  80 7F 05 E8 */	lwz r3, 1512(r31)
/* 8011F53C 0011C11C  38 A1 00 1C */	addi r5, r1, 28
/* 8011F540 0011C120  83 DF 02 D4 */	lwz r30, 724(r31)
/* 8011F544 0011C124  38 80 00 00 */	li r4, 0
/* 8011F548 0011C128  80 63 00 00 */	lwz r3, 0(r3)
/* 8011F54C 0011C12C  4B EE BC 81 */	bl lb_8000B1CC
/* 8011F550 0011C130  C0 5E 00 0C */	lfs f2, 12(r30)
/* 8011F554 0011C134  7F A3 EB 78 */	mr r3, r29
/* 8011F558 0011C138  C0 3F 00 2C */	lfs f1, 44(r31)
/* 8011F55C 0011C13C  38 81 00 1C */	addi r4, r1, 28
/* 8011F560 0011C140  C0 01 00 1C */	lfs f0, 28(r1)
/* 8011F564 0011C144  38 A0 00 6A */	li r5, 106
/* 8011F568 0011C148  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8011F56C 0011C14C  D0 01 00 1C */	stfs f0, 28(r1)
/* 8011F570 0011C150  C0 3E 00 10 */	lfs f1, 16(r30)
/* 8011F574 0011C154  C0 1F 22 50 */	lfs f0, 8784(r31)
/* 8011F578 0011C158  C0 41 00 20 */	lfs f2, 32(r1)
/* 8011F57C 0011C15C  EC 01 00 2A */	fadds f0, f1, f0
/* 8011F580 0011C160  EC 02 00 2A */	fadds f0, f2, f0
/* 8011F584 0011C164  D0 01 00 20 */	stfs f0, 32(r1)
/* 8011F588 0011C168  C0 3F 00 2C */	lfs f1, 44(r31)
/* 8011F58C 0011C16C  48 1A 20 05 */	bl it_802C1590
/* 8011F590 0011C170  90 7F 22 2C */	stw r3, 8748(r31)
/* 8011F594 0011C174  3C 80 00 02 */	lis r4, 0x0001FBE5@ha
/* 8011F598 0011C178  38 7F 00 00 */	addi r3, r31, 0
/* 8011F59C 0011C17C  38 84 FB E5 */	addi r4, r4, 0x0001FBE5@l
/* 8011F5A0 0011C180  38 A0 00 7F */	li r5, 127
/* 8011F5A4 0011C184  38 C0 00 40 */	li r6, 64
/* 8011F5A8 0011C188  4B F6 8B A1 */	bl ft_80088148
/* 8011F5AC 0011C18C  80 1F 22 2C */	lwz r0, 8748(r31)
/* 8011F5B0 0011C190  28 00 00 00 */	cmplwi r0, 0
/* 8011F5B4 0011C194  41 82 00 14 */	beq lbl_8011F5C8
/* 8011F5B8 0011C198  3C 60 80 12 */	lis r3, ftPp_Init_8011F060@ha
/* 8011F5BC 0011C19C  38 03 F0 60 */	addi r0, r3, ftPp_Init_8011F060@l
/* 8011F5C0 0011C1A0  90 1F 21 E4 */	stw r0, 8676(r31)
/* 8011F5C4 0011C1A4  90 1F 21 DC */	stw r0, 8668(r31)
lbl_8011F5C8:
/* 8011F5C8 0011C1A8  38 00 00 00 */	li r0, 0
/* 8011F5CC 0011C1AC  90 1F 22 00 */	stw r0, 8704(r31)
/* 8011F5D0 0011C1B0  48 00 00 A0 */	b lbl_8011F670
lbl_8011F5D4:
/* 8011F5D4 0011C1B4  28 00 00 02 */	cmplwi r0, 2
/* 8011F5D8 0011C1B8  40 82 00 98 */	bne lbl_8011F670
/* 8011F5DC 0011C1BC  80 7F 22 2C */	lwz r3, 8748(r31)
/* 8011F5E0 0011C1C0  28 03 00 00 */	cmplwi r3, 0
/* 8011F5E4 0011C1C4  41 82 00 8C */	beq lbl_8011F670
/* 8011F5E8 0011C1C8  48 1A 21 11 */	bl it_802C16F8
/* 8011F5EC 0011C1CC  38 00 00 00 */	li r0, 0
/* 8011F5F0 0011C1D0  90 1F 22 00 */	stw r0, 8704(r31)
/* 8011F5F4 0011C1D4  80 1F 00 04 */	lwz r0, 4(r31)
/* 8011F5F8 0011C1D8  2C 00 00 0A */	cmpwi r0, 10
/* 8011F5FC 0011C1DC  40 82 00 20 */	bne lbl_8011F61C
/* 8011F600 0011C1E0  3C 80 00 02 */	lis r4, 0x0001FC5D@ha
/* 8011F604 0011C1E4  38 7F 00 00 */	addi r3, r31, 0
/* 8011F608 0011C1E8  38 84 FC 5D */	addi r4, r4, 0x0001FC5D@l
/* 8011F60C 0011C1EC  38 A0 00 7F */	li r5, 127
/* 8011F610 0011C1F0  38 C0 00 40 */	li r6, 64
/* 8011F614 0011C1F4  4B F6 8B C5 */	bl ft_800881D8
/* 8011F618 0011C1F8  48 00 00 1C */	b lbl_8011F634
lbl_8011F61C:
/* 8011F61C 0011C1FC  3C 80 00 02 */	lis r4, 0x0001FC2A@ha
/* 8011F620 0011C200  38 7F 00 00 */	addi r3, r31, 0
/* 8011F624 0011C204  38 84 FC 2A */	addi r4, r4, 0x0001FC2A@l
/* 8011F628 0011C208  38 A0 00 7F */	li r5, 127
/* 8011F62C 0011C20C  38 C0 00 40 */	li r6, 64
/* 8011F630 0011C210  4B F6 8B A9 */	bl ft_800881D8
lbl_8011F634:
/* 8011F634 0011C214  3C 80 00 02 */	lis r4, 0x0001FBE8@ha
/* 8011F638 0011C218  38 7F 00 00 */	addi r3, r31, 0
/* 8011F63C 0011C21C  38 84 FB E8 */	addi r4, r4, 0x0001FBE8@l
/* 8011F640 0011C220  38 A0 00 7F */	li r5, 127
/* 8011F644 0011C224  38 C0 00 40 */	li r6, 64
/* 8011F648 0011C228  4B F6 8B 01 */	bl ft_80088148
/* 8011F64C 0011C22C  80 9D 00 2C */	lwz r4, 44(r29)
/* 8011F650 0011C230  80 7F 22 2C */	lwz r3, 8748(r31)
/* 8011F654 0011C234  80 04 22 2C */	lwz r0, 8748(r4)
/* 8011F658 0011C238  7C 03 00 40 */	cmplw r3, r0
/* 8011F65C 0011C23C  40 82 00 14 */	bne lbl_8011F670
/* 8011F660 0011C240  38 00 00 00 */	li r0, 0
/* 8011F664 0011C244  90 04 22 2C */	stw r0, 8748(r4)
/* 8011F668 0011C248  90 04 21 E4 */	stw r0, 8676(r4)
/* 8011F66C 0011C24C  90 04 21 DC */	stw r0, 8668(r4)
lbl_8011F670:
/* 8011F670 0011C250  80 01 00 3C */	lwz r0, 60(r1)
/* 8011F674 0011C254  83 E1 00 34 */	lwz r31, 52(r1)
/* 8011F678 0011C258  83 C1 00 30 */	lwz r30, 48(r1)
/* 8011F67C 0011C25C  83 A1 00 2C */	lwz r29, 44(r1)
/* 8011F680 0011C260  38 21 00 38 */	addi r1, r1, 56
/* 8011F684 0011C264  7C 08 03 A6 */	mtlr r0
/* 8011F688 0011C268  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
