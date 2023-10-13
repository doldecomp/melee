#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"

#include "ftCo_ItemGet.h"

#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftDonkey/ftDk_HeavyWait0.h"
#include "it/item.h"
#include "pl/pl_0371.h"

#include <common_structs.h>
#include <placeholder.h>

#ifdef MWERKS_GEKKO
/* static */ float const ftCo_804D8580 = 30000;
/* static */ float const ftCo_804D8584 = 1;
/* static */ float const ftCo_804D8588 = 0;

static char ftItemPickup_803C5580[] = "ftGetImmItem item_gobj is NULL!!\n";
#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif
static char assert_msg1[] = "ftpickupitem.c";
static char assert_msg2[] = "item_gobj";
#ifdef MUST_MATCH
#pragma pop
#endif
#endif

/* 094B6C */ static void ftCo_80094B6C(ftCo_GObj* gobj, Item_GObj* item_gobj);

bool ftCo_80094150(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    itPickup* pickup;
    Vec2* offset0;
    ftCo_Fighter* fp = gobj->user_data;
    if (Item_IsGrabbable(item_gobj) &&
        (!fp->x2222_b4 || !it_8026B47C(item_gobj)) &&
        (fp->item_gobj == NULL || it_8026B4F0(item_gobj)))
    {
        pickup = &fp->x294_itPickup;
        if (fp->ground_or_air == GA_Ground) {
            offset0 = &pickup->gr_light_offset[0];
        } else {
            offset0 = &pickup->air_light_offset[0];
        }
        {
            bool b = it_8026B2B4(item_gobj);
            Vec3 it_pos;
            it_8026B344(item_gobj, &it_pos);
            {
                float x_range = it_8026B378(item_gobj);
                float y_range = it_8026B384(item_gobj);
                Vec2* offset1 = !b ? offset0 : &pickup->gr_heavy_offset[0];
                float x1 = offset1[1].x;
                float x0 = (fp->facing_dir * offset1[0].x) + fp->cur_pos.x;
                float y0 = fp->cur_pos.y + offset1[0].y;
                float y1 = offset1[1].y;
                if (x0 - x1 - x_range < it_pos.x &&
                    x_range + (x0 + x1) > it_pos.x &&
                    y0 - y1 - y_range < it_pos.y &&
                    y_range + (y0 + y1) > it_pos.y)
                {
                    return true;
                }
            }
        }
        goto ret_false;
    }
ret_false:
    return false;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm ftCo_GObj* ftCo_800942A0(ftCo_GObj* gobj, u32 flags){
    // clang-format off
    nofralloc
/* 800942A0 00090E80  7C 08 02 A6 */	mflr r0
/* 800942A4 00090E84  90 01 00 04 */	stw r0, 4(r1)
/* 800942A8 00090E88  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800942AC 00090E8C  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 800942B0 00090E90  DB C1 00 50 */	stfd f30, 0x50(r1)
/* 800942B4 00090E94  BF 01 00 30 */	stmw r24, 0x30(r1)
/* 800942B8 00090E98  7C 98 23 78 */	mr r24, r4
/* 800942BC 00090E9C  83 43 00 2C */	lwz r26, 0x2c(r3)
/* 800942C0 00090EA0  80 1A 00 E0 */	lwz r0, 0xe0(r26)
/* 800942C4 00090EA4  3B DA 02 94 */	addi r30, r26, 0x294
/* 800942C8 00090EA8  2C 00 00 00 */	cmpwi r0, 0
/* 800942CC 00090EAC  40 82 00 0C */	bne lbl_800942D8
/* 800942D0 00090EB0  7F DD F3 78 */	mr r29, r30
/* 800942D4 00090EB4  48 00 00 08 */	b lbl_800942DC
lbl_800942D8:
/* 800942D8 00090EB8  3B BE 00 20 */	addi r29, r30, 0x20
lbl_800942DC:
/* 800942DC 00090EBC  7F 43 D3 78 */	mr r3, r26
/* 800942E0 00090EC0  48 00 DD 61 */	bl ftCo_800A2040
/* 800942E4 00090EC4  2C 03 00 00 */	cmpwi r3, 0
/* 800942E8 00090EC8  41 82 00 18 */	beq lbl_80094300
/* 800942EC 00090ECC  80 1A 1A 94 */	lwz r0, 0x1a94(r26)
/* 800942F0 00090ED0  2C 00 00 1C */	cmpwi r0, 0x1c
/* 800942F4 00090ED4  40 82 00 0C */	bne lbl_80094300
/* 800942F8 00090ED8  38 60 00 00 */	li r3, 0
/* 800942FC 00090EDC  48 00 01 64 */	b lbl_80094460
lbl_80094300:
/* 80094300 00090EE0  80 6D C1 8C */	lwz r3, HSD_GObj_Entities
/* 80094304 00090EE4  57 1C 07 FE */	clrlwi r28, r24, 0x1f
/* 80094308 00090EE8  C3 E2 8B A0 */	lfs f31, ftCo_804D8580
/* 8009430C 00090EEC  57 1B 07 BC */	rlwinm r27, r24, 0, 0x1e, 0x1e
/* 80094310 00090EF0  83 23 00 24 */	lwz r25, 0x24(r3)
/* 80094314 00090EF4  3B 00 00 00 */	li r24, 0
/* 80094318 00090EF8  48 00 01 3C */	b lbl_80094454
lbl_8009431C:
/* 8009431C 00090EFC  7F 23 CB 78 */	mr r3, r25
/* 80094320 00090F00  48 1D 6E 85 */	bl Item_IsGrabbable
/* 80094324 00090F04  2C 03 00 00 */	cmpwi r3, 0
/* 80094328 00090F08  41 82 01 28 */	beq lbl_80094450
/* 8009432C 00090F0C  7F 23 CB 78 */	mr r3, r25
/* 80094330 00090F10  48 1D 6F 85 */	bl it_8026B2B4
/* 80094334 00090F14  88 1A 22 22 */	lbz r0, 0x2222(r26)
/* 80094338 00090F18  3B E3 00 00 */	addi r31, r3, 0
/* 8009433C 00090F1C  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80094340 00090F20  41 82 00 14 */	beq lbl_80094354
/* 80094344 00090F24  7F 23 CB 78 */	mr r3, r25
/* 80094348 00090F28  48 1D 71 35 */	bl it_8026B47C
/* 8009434C 00090F2C  2C 03 00 00 */	cmpwi r3, 0
/* 80094350 00090F30  40 82 01 00 */	bne lbl_80094450
lbl_80094354:
/* 80094354 00090F34  80 1A 19 74 */	lwz r0, 0x1974(r26)
/* 80094358 00090F38  28 00 00 00 */	cmplwi r0, 0
/* 8009435C 00090F3C  41 82 00 14 */	beq lbl_80094370
/* 80094360 00090F40  7F 23 CB 78 */	mr r3, r25
/* 80094364 00090F44  48 1D 71 8D */	bl it_8026B4F0
/* 80094368 00090F48  2C 03 00 00 */	cmpwi r3, 0
/* 8009436C 00090F4C  41 82 00 E4 */	beq lbl_80094450
lbl_80094370:
/* 80094370 00090F50  2C 1F 00 00 */	cmpwi r31, 0
/* 80094374 00090F54  40 82 00 0C */	bne lbl_80094380
/* 80094378 00090F58  28 1C 00 00 */	cmplwi r28, 0
/* 8009437C 00090F5C  40 82 00 14 */	bne lbl_80094390
lbl_80094380:
/* 80094380 00090F60  2C 1F 00 01 */	cmpwi r31, 1
/* 80094384 00090F64  40 82 00 CC */	bne lbl_80094450
/* 80094388 00090F68  28 1B 00 00 */	cmplwi r27, 0
/* 8009438C 00090F6C  41 82 00 C4 */	beq lbl_80094450
lbl_80094390:
/* 80094390 00090F70  38 79 00 00 */	addi r3, r25, 0
/* 80094394 00090F74  38 81 00 1C */	addi r4, r1, 0x1c
/* 80094398 00090F78  48 1D 6F AD */	bl it_8026B344
/* 8009439C 00090F7C  7F 23 CB 78 */	mr r3, r25
/* 800943A0 00090F80  48 1D 6F D9 */	bl it_8026B378
/* 800943A4 00090F84  FF C0 08 90 */	fmr f30, f1
/* 800943A8 00090F88  7F 23 CB 78 */	mr r3, r25
/* 800943AC 00090F8C  48 1D 6F D9 */	bl it_8026B384
/* 800943B0 00090F90  2C 1F 00 00 */	cmpwi r31, 0
/* 800943B4 00090F94  40 82 00 0C */	bne lbl_800943C0
/* 800943B8 00090F98  7F A3 EB 78 */	mr r3, r29
/* 800943BC 00090F9C  48 00 00 08 */	b lbl_800943C4
lbl_800943C0:
/* 800943C0 00090FA0  38 7E 00 10 */	addi r3, r30, 0x10
lbl_800943C4:
/* 800943C4 00090FA4  C0 7A 00 2C */	lfs f3, 0x2c(r26)
/* 800943C8 00090FA8  C0 43 00 00 */	lfs f2, 0(r3)
/* 800943CC 00090FAC  C0 1A 00 B0 */	lfs f0, 0xb0(r26)
/* 800943D0 00090FB0  C0 83 00 08 */	lfs f4, 8(r3)
/* 800943D4 00090FB4  EC A3 00 BA */	fmadds f5, f3, f2, f0
/* 800943D8 00090FB8  C0 C1 00 1C */	lfs f6, 0x1c(r1)
/* 800943DC 00090FBC  C0 7A 00 B4 */	lfs f3, 0xb4(r26)
/* 800943E0 00090FC0  C0 43 00 04 */	lfs f2, 4(r3)
/* 800943E4 00090FC4  EC 05 20 28 */	fsubs f0, f5, f4
/* 800943E8 00090FC8  EC 63 10 2A */	fadds f3, f3, f2
/* 800943EC 00090FCC  C0 E3 00 0C */	lfs f7, 0xc(r3)
/* 800943F0 00090FD0  EC 00 F0 28 */	fsubs f0, f0, f30
/* 800943F4 00090FD4  FC 00 30 40 */	fcmpo cr0, f0, f6
/* 800943F8 00090FD8  40 80 00 58 */	bge lbl_80094450
/* 800943FC 00090FDC  EC 05 20 2A */	fadds f0, f5, f4
/* 80094400 00090FE0  EC 1E 00 2A */	fadds f0, f30, f0
/* 80094404 00090FE4  FC 00 30 40 */	fcmpo cr0, f0, f6
/* 80094408 00090FE8  40 81 00 48 */	ble lbl_80094450
/* 8009440C 00090FEC  EC 03 38 28 */	fsubs f0, f3, f7
/* 80094410 00090FF0  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 80094414 00090FF4  EC 00 08 28 */	fsubs f0, f0, f1
/* 80094418 00090FF8  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8009441C 00090FFC  40 80 00 34 */	bge lbl_80094450
/* 80094420 00091000  EC 03 38 2A */	fadds f0, f3, f7
/* 80094424 00091004  EC 01 00 2A */	fadds f0, f1, f0
/* 80094428 00091008  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8009442C 0009100C  40 81 00 24 */	ble lbl_80094450
/* 80094430 00091010  EC 02 18 28 */	fsubs f0, f2, f3
/* 80094434 00091014  EC 26 28 28 */	fsubs f1, f6, f5
/* 80094438 00091018  EC 00 00 32 */	fmuls f0, f0, f0
/* 8009443C 0009101C  EC 01 00 7A */	fmadds f0, f1, f1, f0
/* 80094440 00091020  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 80094444 00091024  40 80 00 0C */	bge lbl_80094450
/* 80094448 00091028  7F 38 CB 78 */	mr r24, r25
/* 8009444C 0009102C  FF E0 00 90 */	fmr f31, f0
lbl_80094450:
/* 80094450 00091030  83 39 00 08 */	lwz r25, 8(r25)
lbl_80094454:
/* 80094454 00091034  28 19 00 00 */	cmplwi r25, 0
/* 80094458 00091038  40 82 FE C4 */	bne lbl_8009431C
/* 8009445C 0009103C  7F 03 C3 78 */	mr r3, r24
lbl_80094460:
/* 80094460 00091040  BB 01 00 30 */	lmw r24, 0x30(r1)
/* 80094464 00091044  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80094468 00091048  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 8009446C 0009104C  CB C1 00 50 */	lfd f30, 0x50(r1)
/* 80094470 00091050  38 21 00 60 */	addi r1, r1, 0x60
/* 80094474 00091054  7C 08 03 A6 */	mtlr r0
/* 80094478 00091058  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

HSD_GObj* ftCo_800942A0(HSD_GObj* gobj, u32 flags)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    itPickup* pickup = &fp->x294_itPickup;
    Vec2* offset0;
    if (fp->ground_or_air == GA_Ground) {
        offset0 = &pickup->gr_light_offset[0];
    } else {
        offset0 = &pickup->air_light_offset[0];
    }
    if (ftCo_800A2040(fp) && (signed) fp->x1A94 == 28) {
        return NULL;
    }
    {
        float min_dist_sq = 30000;
        HSD_GObj* cur = HSD_GObj_Entities->items;
        HSD_GObj* result = NULL;
        while (cur != NULL) {
            if (Item_IsGrabbable(cur)) {
                enum_t unk_enum = it_8026B2B4(cur);
                if ((!fp->x2222_b4 || !it_8026B47C(cur)) &&
                    (fp->item_gobj == NULL || it_8026B4F0(cur)))
                {
                    if ((unk_enum == 0 && flags & (1 << 0)) ||
                        (unk_enum == 1 && flags & (1 << 1)))
                    {
                        Vec2* vec;
                        Vec3 it_pos;
                        it_8026B344(cur, &it_pos);
                        {
                            float x_range = it_8026B378(cur);
                            float y_range = it_8026B384(cur);
                            if (unk_enum == 0) {
                                vec = offset0;
                            } else {
                                vec = &pickup->gr_heavy_offset[0];
                            }
                            {
                                float x1 = vec[1].x;
                                float x0 =
                                    fp->facing_dir * vec[0].x + fp->cur_pos.x;
                                float y0 = fp->cur_pos.y + vec[0].y;
                                float y1 = vec[1].y;
                                if (x0 - x1 - x_range < it_pos.x &&
                                    x_range + (x0 + x1) > it_pos.x &&
                                    y0 - y1 - y_range < it_pos.y &&
                                    y_range + (y0 + y1) > it_pos.y)
                                {
                                    float y_diff = it_pos.y - y0;
                                    float x_diff = it_pos.x - x0;
                                    float dist_sq = SQ(x_diff) + SQ(y_diff);
                                    if (dist_sq < min_dist_sq) {
                                        result = cur;
                                        min_dist_sq = dist_sq;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            cur = cur->next;
        }
        return result;
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm bool ftCo_8009447C(ftCo_GObj* gobj, HSD_GObj* arg1)
{ // clang-format off
    nofralloc
/* 8009447C 0009105C  7C 08 02 A6 */	mflr r0
/* 80094480 00091060  90 01 00 04 */	stw r0, 4(r1)
/* 80094484 00091064  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80094488 00091068  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8009448C 0009106C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80094490 00091070  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80094494 00091074  7C 9D 23 79 */	or. r29, r4, r4
/* 80094498 00091078  93 81 00 18 */	stw r28, 0x18(r1)
/* 8009449C 0009107C  3B 83 00 00 */	addi r28, r3, 0
/* 800944A0 00091080  3C 60 80 3C */	lis r3, ftItemPickup_803C5580@ha
/* 800944A4 00091084  83 DC 00 2C */	lwz r30, 0x2c(r28)
/* 800944A8 00091088  3B E3 55 80 */	addi r31, r3, ftItemPickup_803C5580@l
/* 800944AC 0009108C  40 82 00 20 */	bne lbl_800944CC
/* 800944B0 00091090  38 7F 00 00 */	addi r3, r31, 0
/* 800944B4 00091094  4C C6 31 82 */	crclr 6
/* 800944B8 00091098  48 2B 11 F1 */	bl OSReport
/* 800944BC 0009109C  38 7F 00 24 */	addi r3, r31, 0x24
/* 800944C0 000910A0  38 BF 00 34 */	addi r5, r31, 0x34
/* 800944C4 000910A4  38 80 00 AE */	li r4, 0xae
/* 800944C8 000910A8  48 2F 3D 59 */	bl __assert
lbl_800944CC:
/* 800944CC 000910AC  7F A3 EB 78 */	mr r3, r29
/* 800944D0 000910B0  48 1D 6E 3D */	bl it_8026B30C
/* 800944D4 000910B4  2C 03 00 05 */	cmpwi r3, 5
/* 800944D8 000910B8  40 82 01 98 */	bne lbl_80094670
/* 800944DC 000910BC  7F A3 EB 78 */	mr r3, r29
/* 800944E0 000910C0  48 1D 6E 21 */	bl itGetKind
/* 800944E4 000910C4  2C 03 00 1F */	cmpwi r3, 0x1f
/* 800944E8 000910C8  41 82 01 38 */	beq lbl_80094620
/* 800944EC 000910CC  40 80 00 40 */	bge lbl_8009452C
/* 800944F0 000910D0  2C 03 00 12 */	cmpwi r3, 0x12
/* 800944F4 000910D4  41 82 00 AC */	beq lbl_800945A0
/* 800944F8 000910D8  40 80 00 1C */	bge lbl_80094514
/* 800944FC 000910DC  2C 03 00 09 */	cmpwi r3, 9
/* 80094500 000910E0  41 82 00 80 */	beq lbl_80094580
/* 80094504 000910E4  40 80 01 6C */	bge lbl_80094670
/* 80094508 000910E8  2C 03 00 08 */	cmpwi r3, 8
/* 8009450C 000910EC  40 80 00 54 */	bge lbl_80094560
/* 80094510 000910F0  48 00 01 60 */	b lbl_80094670
lbl_80094514:
/* 80094514 000910F4  2C 03 00 1D */	cmpwi r3, 0x1d
/* 80094518 000910F8  41 82 00 E8 */	beq lbl_80094600
/* 8009451C 000910FC  40 80 01 54 */	bge lbl_80094670
/* 80094520 00091100  2C 03 00 1C */	cmpwi r3, 0x1c
/* 80094524 00091104  40 80 00 EC */	bge lbl_80094610
/* 80094528 00091108  48 00 01 48 */	b lbl_80094670
lbl_8009452C:
/* 8009452C 0009110C  2C 03 00 CD */	cmpwi r3, 0xcd
/* 80094530 00091110  41 82 00 90 */	beq lbl_800945C0
/* 80094534 00091114  40 80 00 20 */	bge lbl_80094554
/* 80094538 00091118  2C 03 00 9F */	cmpwi r3, 0x9f
/* 8009453C 0009111C  41 82 01 2C */	beq lbl_80094668
/* 80094540 00091120  40 80 01 30 */	bge lbl_80094670
/* 80094544 00091124  2C 03 00 21 */	cmpwi r3, 0x21
/* 80094548 00091128  41 82 01 00 */	beq lbl_80094648
/* 8009454C 0009112C  40 80 01 24 */	bge lbl_80094670
/* 80094550 00091130  48 00 00 E0 */	b lbl_80094630
lbl_80094554:
/* 80094554 00091134  2C 03 00 E2 */	cmpwi r3, 0xe2
/* 80094558 00091138  41 82 00 88 */	beq lbl_800945E0
/* 8009455C 0009113C  48 00 01 14 */	b lbl_80094670
lbl_80094560:
/* 80094560 00091140  7F A3 EB 78 */	mr r3, r29
/* 80094564 00091144  48 1D 6F 19 */	bl it_8026B47C
/* 80094568 00091148  38 83 00 00 */	addi r4, r3, 0
/* 8009456C 0009114C  38 7E 00 00 */	addi r3, r30, 0
/* 80094570 00091150  4B FD 89 ED */	bl Fighter_8006CF5C
/* 80094574 00091154  7F A3 EB 78 */	mr r3, r29
/* 80094578 00091158  48 1D 63 75 */	bl Item_8026A8EC
/* 8009457C 0009115C  48 00 00 F4 */	b lbl_80094670
lbl_80094580:
/* 80094580 00091160  7F A3 EB 78 */	mr r3, r29
/* 80094584 00091164  48 1D 6E F9 */	bl it_8026B47C
/* 80094588 00091168  38 83 00 00 */	addi r4, r3, 0
/* 8009458C 0009116C  38 7E 00 00 */	addi r3, r30, 0
/* 80094590 00091170  4B FD 89 CD */	bl Fighter_8006CF5C
/* 80094594 00091174  7F A3 EB 78 */	mr r3, r29
/* 80094598 00091178  48 1D 63 55 */	bl Item_8026A8EC
/* 8009459C 0009117C  48 00 00 D4 */	b lbl_80094670
lbl_800945A0:
/* 800945A0 00091180  7F A3 EB 78 */	mr r3, r29
/* 800945A4 00091184  48 1D 6E D9 */	bl it_8026B47C
/* 800945A8 00091188  38 83 00 00 */	addi r4, r3, 0
/* 800945AC 0009118C  38 7E 00 00 */	addi r3, r30, 0
/* 800945B0 00091190  4B FD 89 AD */	bl Fighter_8006CF5C
/* 800945B4 00091194  7F A3 EB 78 */	mr r3, r29
/* 800945B8 00091198  48 1D 63 35 */	bl Item_8026A8EC
/* 800945BC 0009119C  48 00 00 B4 */	b lbl_80094670
lbl_800945C0:
/* 800945C0 000911A0  7F A3 EB 78 */	mr r3, r29
/* 800945C4 000911A4  48 1D 6E B9 */	bl it_8026B47C
/* 800945C8 000911A8  38 83 00 00 */	addi r4, r3, 0
/* 800945CC 000911AC  38 7E 00 00 */	addi r3, r30, 0
/* 800945D0 000911B0  4B FD 89 8D */	bl Fighter_8006CF5C
/* 800945D4 000911B4  7F A3 EB 78 */	mr r3, r29
/* 800945D8 000911B8  48 1D 63 15 */	bl Item_8026A8EC
/* 800945DC 000911BC  48 00 00 94 */	b lbl_80094670
lbl_800945E0:
/* 800945E0 000911C0  7F A3 EB 78 */	mr r3, r29
/* 800945E4 000911C4  48 1D 6E 99 */	bl it_8026B47C
/* 800945E8 000911C8  38 83 00 00 */	addi r4, r3, 0
/* 800945EC 000911CC  38 7E 00 00 */	addi r3, r30, 0
/* 800945F0 000911D0  4B FD 89 6D */	bl Fighter_8006CF5C
/* 800945F4 000911D4  7F A3 EB 78 */	mr r3, r29
/* 800945F8 000911D8  48 1D 62 F5 */	bl Item_8026A8EC
/* 800945FC 000911DC  48 00 00 74 */	b lbl_80094670
lbl_80094600:
/* 80094600 000911E0  7F 83 E3 78 */	mr r3, r28
/* 80094604 000911E4  48 03 01 21 */	bl ftCo_800C4724
/* 80094608 000911E8  38 60 00 01 */	li r3, 1
/* 8009460C 000911EC  48 00 00 68 */	b lbl_80094674
lbl_80094610:
/* 80094610 000911F0  7F 83 E3 78 */	mr r3, r28
/* 80094614 000911F4  48 03 0C E1 */	bl ftCo_800C52F4
/* 80094618 000911F8  38 60 00 01 */	li r3, 1
/* 8009461C 000911FC  48 00 00 58 */	b lbl_80094674
lbl_80094620:
/* 80094620 00091200  38 7C 00 00 */	addi r3, r28, 0
/* 80094624 00091204  38 9D 00 00 */	addi r4, r29, 0
/* 80094628 00091208  4B FE B4 31 */	bl ftCommon_8007FA58
/* 8009462C 0009120C  48 00 00 44 */	b lbl_80094670
lbl_80094630:
/* 80094630 00091210  38 7C 00 00 */	addi r3, r28, 0
/* 80094634 00091214  38 9D 00 00 */	addi r4, r29, 0
/* 80094638 00091218  4B FF 2B 71 */	bl ftLib_800871A8
/* 8009463C 0009121C  7F A3 EB 78 */	mr r3, r29
/* 80094640 00091220  48 1D 62 AD */	bl Item_8026A8EC
/* 80094644 00091224  48 00 00 2C */	b lbl_80094670
lbl_80094648:
/* 80094648 00091228  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8009464C 0009122C  38 7C 00 00 */	addi r3, r28, 0
/* 80094650 00091230  38 A0 00 01 */	li r5, 1
/* 80094654 00091234  80 84 07 CC */	lwz r4, 0x7cc(r4)
/* 80094658 00091238  48 03 42 7D */	bl ftCo_800C88D4
/* 8009465C 0009123C  7F A3 EB 78 */	mr r3, r29
/* 80094660 00091240  48 1D 62 8D */	bl Item_8026A8EC
/* 80094664 00091244  48 00 00 0C */	b lbl_80094670
lbl_80094668:
/* 80094668 00091248  7F A3 EB 78 */	mr r3, r29
/* 8009466C 0009124C  48 1D 62 81 */	bl Item_8026A8EC
lbl_80094670:
/* 80094670 00091250  38 60 00 00 */	li r3, 0
lbl_80094674:
/* 80094674 00091254  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80094678 00091258  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8009467C 0009125C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80094680 00091260  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80094684 00091264  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80094688 00091268  38 21 00 28 */	addi r1, r1, 0x28
/* 8009468C 0009126C  7C 08 03 A6 */	mtlr r0
/* 80094690 00091270  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftCo_8009447C(HSD_GObj* gobj, HSD_GObj* item_gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (item_gobj == NULL) {
        OSReport("ftGetImmItem item_gobj is NULL!!\n");
        __assert("ftpickupitem.c", 399, "item_gobj");
    }
    if (it_8026B30C(item_gobj) == 5) {
        switch (itGetKind(item_gobj)) {
        case It_Kind_Heart:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Tomato:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Foods:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case Pokemon_Lucky_Egg:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_WhispyHealApple:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_WStar:
            ftCo_800C4724(gobj);
            return 1;
        case It_Kind_Hammer:
            ftCo_800C52F4(gobj);
            return 1;
        case It_Kind_RabbitC:
            ftCommon_8007FA58(gobj, item_gobj);
            goto block_35;
        case It_Kind_MetalB:
            ftLib_800871A8(gobj, item_gobj);
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Spycloak:
            ftCo_800C88D4(gobj, p_ftCommonData->x7CC, 1);
            Item_8026A8EC(item_gobj);
            goto block_35;
        case It_Kind_Coin:
            Item_8026A8EC(item_gobj);
            goto block_35;
        }
    }
block_35:
    return false;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80094694(ftCo_GObj* gobj, enum_t, bool)
{ // clang-format off
    nofralloc
/* 80094694 00091274  7C 08 02 A6 */	mflr r0
/* 80094698 00091278  90 01 00 04 */	stw r0, 4(r1)
/* 8009469C 0009127C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800946A0 00091280  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 800946A4 00091284  3B 84 00 00 */	addi r28, r4, 0
/* 800946A8 00091288  2C 1C 00 5D */	cmpwi r28, 0x5d
/* 800946AC 0009128C  3B 63 00 00 */	addi r27, r3, 0
/* 800946B0 00091290  7C BD 2B 78 */	mr r29, r5
/* 800946B4 00091294  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800946B8 00091298  40 82 00 1C */	bne lbl_800946D4
/* 800946BC 0009129C  80 6D AE 84 */	lwz r3, Fighter_804D6524
/* 800946C0 000912A0  C0 22 8B A4 */	lfs f1, ftCo_804D8584
/* 800946C4 000912A4  C0 5E 00 38 */	lfs f2, 0x38(r30)
/* 800946C8 000912A8  C0 63 00 08 */	lfs f3, 8(r3)
/* 800946CC 000912AC  48 03 AE C9 */	bl ftCo_CalcYScaledKnockback
/* 800946D0 000912B0  48 00 00 08 */	b lbl_800946D8
lbl_800946D4:
/* 800946D4 000912B4  C0 22 8B A4 */	lfs f1, ftCo_804D8584
lbl_800946D8:
/* 800946D8 000912B8  3B E0 00 00 */	li r31, 0
/* 800946DC 000912BC  FC 40 08 90 */	fmr f2, f1
/* 800946E0 000912C0  93 FE 22 10 */	stw r31, 0x2210(r30)
/* 800946E4 000912C4  38 7B 00 00 */	addi r3, r27, 0
/* 800946E8 000912C8  38 9C 00 00 */	addi r4, r28, 0
/* 800946EC 000912CC  C0 22 8B A8 */	lfs f1, ftCo_804D8588
/* 800946F0 000912D0  38 A0 00 00 */	li r5, 0
/* 800946F4 000912D4  FC 60 08 90 */	fmr f3, f1
/* 800946F8 000912D8  38 C0 00 00 */	li r6, 0
/* 800946FC 000912DC  4B FD 4C B1 */	bl Fighter_ChangeMotionState
/* 80094700 000912E0  2C 1D 00 00 */	cmpwi r29, 0
/* 80094704 000912E4  41 82 00 3C */	beq lbl_80094740
/* 80094708 000912E8  48 00 00 0C */	b lbl_80094714
lbl_8009470C:
/* 8009470C 000912EC  7F 63 DB 78 */	mr r3, r27
/* 80094710 000912F0  4B FD A4 95 */	bl ftAnim_8006EBA4
lbl_80094714:
/* 80094714 000912F4  88 7E 22 10 */	lbz r3, 0x2210(r30)
/* 80094718 000912F8  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8009471C 000912FC  41 82 00 14 */	beq lbl_80094730
/* 80094720 00091300  53 E3 26 F6 */	rlwimi r3, r31, 4, 0x1b, 0x1b
/* 80094724 00091304  98 7E 22 10 */	stb r3, 0x2210(r30)
/* 80094728 00091308  38 00 00 01 */	li r0, 1
/* 8009472C 0009130C  48 00 00 08 */	b lbl_80094734
lbl_80094730:
/* 80094730 00091310  38 00 00 00 */	li r0, 0
lbl_80094734:
/* 80094734 00091314  2C 00 00 00 */	cmpwi r0, 0
/* 80094738 00091318  41 82 FF D4 */	beq lbl_8009470C
/* 8009473C 0009131C  48 00 00 0C */	b lbl_80094748
lbl_80094740:
/* 80094740 00091320  7F 63 DB 78 */	mr r3, r27
/* 80094744 00091324  4B FD A4 61 */	bl ftAnim_8006EBA4
lbl_80094748:
/* 80094748 00091328  2C 1C 00 5D */	cmpwi r28, 0x5d
/* 8009474C 0009132C  40 82 00 1C */	bne lbl_80094768
/* 80094750 00091330  38 00 00 01 */	li r0, 1
/* 80094754 00091334  3C 60 80 09 */	lis r3, ftCo_800974C4@ha
/* 80094758 00091338  90 1E 23 40 */	stw r0, 0x2340(r30)
/* 8009475C 0009133C  38 03 74 C4 */	addi r0, r3, ftCo_800974C4@l
/* 80094760 00091340  90 1E 21 DC */	stw r0, 0x21dc(r30)
/* 80094764 00091344  48 00 00 18 */	b lbl_8009477C
lbl_80094768:
/* 80094768 00091348  38 00 00 00 */	li r0, 0
/* 8009476C 0009134C  3C 60 80 09 */	lis r3, ftCo_80094DF8@ha
/* 80094770 00091350  90 1E 23 40 */	stw r0, 0x2340(r30)
/* 80094774 00091354  38 03 4D F8 */	addi r0, r3, ftCo_80094DF8@l
/* 80094778 00091358  90 1E 21 DC */	stw r0, 0x21dc(r30)
lbl_8009477C:
/* 8009477C 0009135C  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 80094780 00091360  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80094784 00091364  38 21 00 30 */	addi r1, r1, 0x30
/* 80094788 00091368  7C 08 03 A6 */	mtlr r0
/* 8009478C 0009136C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80094694(HSD_GObj* gobj, FtMotionId msid, bool loop)
{
    ftCo_Fighter* fp = gobj->user_data;
    {
        float anim_spd;
        if (msid == ftCo_MS_HeavyGet) {
            anim_spd = ftCo_CalcYScaledKnockback(
                Fighter_804D6524, 1, fp->x34_scale.y,
                M2C_FIELD(Fighter_804D6524, float*, 8));
        } else {
            anim_spd = 1;
        }
        fp->throw_flags = 0;
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, anim_spd, 0,
                                  NULL);
    }
    if (loop) {
        while (!ftCheckThrowB3(fp)) {
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftAnim_8006EBA4(gobj);
    }
    if (msid == ftCo_MS_HeavyGet) {
        fp->mv.co.itemget.x0 = true;
        fp->take_dmg_cb = ftCo_800974C4;
    } else {
        fp->mv.co.itemget.x0 = false;
        fp->take_dmg_cb = ftCo_80094DF8;
    }
}
#endif

bool ftCo_80094790(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (GET_FIGHTER(gobj)->x1978 == NULL) {
        HSD_GObj* unk_gobj = ftCo_800942A0(gobj, 3);
        if (unk_gobj != NULL) {
            if (!it_8026B2B4(unk_gobj)) {
                ftCo_80094694(gobj, 92, 0);
            } else {
                ftCo_80094694(gobj, 93, 0);
            }
            return true;
        }
    }
    return false;
}

void ftCo_80094818(HSD_GObj* gobj, int arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x1978 != NULL) {
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->x1978);
    } else if (fp->item_gobj != NULL) {
        if (ftData_OnItemPickupExt[fp->kind] != NULL) {
            ftData_OnItemPickupExt[fp->kind](gobj, arg1);
        }
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->item_gobj);
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_800948A8(ftCo_GObj* gobj, Item_GObj* item_gobj)
{ // clang-format off
    nofralloc
/* 800948A8 00091488  7C 08 02 A6 */	mflr r0
/* 800948AC 0009148C  90 01 00 04 */	stw r0, 4(r1)
/* 800948B0 00091490  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800948B4 00091494  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800948B8 00091498  7C 9F 23 78 */	mr r31, r4
/* 800948BC 0009149C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800948C0 000914A0  7C 7E 1B 78 */	mr r30, r3
/* 800948C4 000914A4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800948C8 000914A8  93 81 00 18 */	stw r28, 0x18(r1)
/* 800948CC 000914AC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800948D0 000914B0  80 03 19 74 */	lwz r0, 0x1974(r3)
/* 800948D4 000914B4  3B 83 00 00 */	addi r28, r3, 0
/* 800948D8 000914B8  28 00 00 00 */	cmplwi r0, 0
/* 800948DC 000914BC  41 82 00 0C */	beq lbl_800948E8
/* 800948E0 000914C0  93 FC 19 78 */	stw r31, 0x1978(r28)
/* 800948E4 000914C4  48 00 00 08 */	b lbl_800948EC
lbl_800948E8:
/* 800948E8 000914C8  93 FC 19 74 */	stw r31, 0x1974(r28)
lbl_800948EC:
/* 800948EC 000914CC  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 800948F0 000914D0  80 BD 19 78 */	lwz r5, 0x1978(r29)
/* 800948F4 000914D4  28 05 00 00 */	cmplwi r5, 0
/* 800948F8 000914D8  41 82 00 18 */	beq lbl_80094910
/* 800948FC 000914DC  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80094900 000914E0  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 80094904 000914E4  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80094908 000914E8  4B FA 98 75 */	bl pl_8003E17C
/* 8009490C 000914EC  48 00 00 54 */	b lbl_80094960
lbl_80094910:
/* 80094910 000914F0  80 1D 19 74 */	lwz r0, 0x1974(r29)
/* 80094914 000914F4  28 00 00 00 */	cmplwi r0, 0
/* 80094918 000914F8  41 82 00 48 */	beq lbl_80094960
/* 8009491C 000914FC  80 9D 00 04 */	lwz r4, 4(r29)
/* 80094920 00091500  3C 60 80 3C */	lis r3, ftData_OnItemPickupExt@ha
/* 80094924 00091504  38 03 18 8C */	addi r0, r3, ftData_OnItemPickupExt@l
/* 80094928 00091508  54 83 10 3A */	slwi r3, r4, 2
/* 8009492C 0009150C  7C 60 1A 14 */	add r3, r0, r3
/* 80094930 00091510  81 83 00 00 */	lwz r12, 0(r3)
/* 80094934 00091514  28 0C 00 00 */	cmplwi r12, 0
/* 80094938 00091518  41 82 00 14 */	beq lbl_8009494C
/* 8009493C 0009151C  7D 88 03 A6 */	mtlr r12
/* 80094940 00091520  38 7E 00 00 */	addi r3, r30, 0
/* 80094944 00091524  38 80 00 01 */	li r4, 1
/* 80094948 00091528  4E 80 00 21 */	blrl
lbl_8009494C:
/* 8009494C 0009152C  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80094950 00091530  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 80094954 00091534  80 BD 19 74 */	lwz r5, 0x1974(r29)
/* 80094958 00091538  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8009495C 0009153C  4B FA 98 21 */	bl pl_8003E17C
lbl_80094960:
/* 80094960 00091540  7F E3 FB 78 */	mr r3, r31
/* 80094964 00091544  48 1D 69 51 */	bl it_8026B2B4
/* 80094968 00091548  2C 03 00 00 */	cmpwi r3, 0
/* 8009496C 0009154C  40 82 00 2C */	bne lbl_80094998
/* 80094970 00091550  7F E3 FB 78 */	mr r3, r31
/* 80094974 00091554  48 1D 69 8D */	bl itGetKind
/* 80094978 00091558  2C 03 00 1D */	cmpwi r3, 0x1d
/* 8009497C 0009155C  40 82 00 0C */	bne lbl_80094988
/* 80094980 00091560  3B A0 00 00 */	li r29, 0
/* 80094984 00091564  48 00 00 20 */	b lbl_800949A4
lbl_80094988:
/* 80094988 00091568  80 7C 01 0C */	lwz r3, 0x10c(r28)
/* 8009498C 0009156C  80 63 00 08 */	lwz r3, 8(r3)
/* 80094990 00091570  8B A3 00 10 */	lbz r29, 0x10(r3)
/* 80094994 00091574  48 00 00 10 */	b lbl_800949A4
lbl_80094998:
/* 80094998 00091578  80 7C 01 0C */	lwz r3, 0x10c(r28)
/* 8009499C 0009157C  80 63 00 08 */	lwz r3, 8(r3)
/* 800949A0 00091580  8B A3 00 11 */	lbz r29, 0x11(r3)
lbl_800949A4:
/* 800949A4 00091584  88 9C 22 1F */	lbz r4, 0x221f(r28)
/* 800949A8 00091588  7F E5 FB 78 */	mr r5, r31
/* 800949AC 0009158C  88 7C 00 0C */	lbz r3, 0xc(r28)
/* 800949B0 00091590  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800949B4 00091594  4B FA 9E A1 */	bl pl_8003E854
/* 800949B8 00091598  38 7F 00 00 */	addi r3, r31, 0
/* 800949BC 0009159C  38 9E 00 00 */	addi r4, r30, 0
/* 800949C0 000915A0  38 BD 00 00 */	addi r5, r29, 0
/* 800949C4 000915A4  48 1D 61 91 */	bl Item_8026AB54
/* 800949C8 000915A8  7F E3 FB 78 */	mr r3, r31
/* 800949CC 000915AC  48 1D 68 E9 */	bl it_8026B2B4
/* 800949D0 000915B0  2C 03 00 01 */	cmpwi r3, 1
/* 800949D4 000915B4  40 82 00 20 */	bne lbl_800949F4
/* 800949D8 000915B8  80 9C 01 0C */	lwz r4, 0x10c(r28)
/* 800949DC 000915BC  38 7C 00 00 */	addi r3, r28, 0
/* 800949E0 000915C0  38 A0 00 7F */	li r5, 0x7f
/* 800949E4 000915C4  80 84 00 4C */	lwz r4, 0x4c(r4)
/* 800949E8 000915C8  38 C0 00 40 */	li r6, 0x40
/* 800949EC 000915CC  80 84 00 2C */	lwz r4, 0x2c(r4)
/* 800949F0 000915D0  4B FF 37 E9 */	bl ft_800881D8
lbl_800949F4:
/* 800949F4 000915D4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800949F8 000915D8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800949FC 000915DC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80094A00 000915E0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80094A04 000915E4  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80094A08 000915E8  38 21 00 28 */	addi r1, r1, 0x28
/* 80094A0C 000915EC  7C 08 03 A6 */	mtlr r0
/* 80094A10 000915F0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline void inlineB0(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u64 _ = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x1978 != NULL) {
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->x1978);
    } else if (fp->item_gobj != NULL) {
        if (ftData_OnItemPickupExt[fp->kind] != NULL) {
            ftData_OnItemPickupExt[fp->kind](gobj, true);
        }
        pl_8003E17C(fp->player_id, fp->x221F_b4, fp->item_gobj);
    }
}

void ftCo_800948A8(ftCo_GObj* gobj, Item_GObj* item_gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        fp->x1978 = item_gobj;
    } else {
        fp->item_gobj = item_gobj;
    }
    inlineB0(gobj);
    {
        u8 ret_part;
        if (it_8026B2B4(item_gobj) == 0) {
            if (itGetKind(item_gobj) == It_Kind_WStar) {
                ret_part = 0;
            } else {
                ret_part = fp->ft_data->x8->unk10;
            }
        } else {
            ret_part = fp->ft_data->x8->unk11;
        }
        pl_8003E854(fp->player_id, fp->x221F_b4, item_gobj);
        Item_8026AB54(item_gobj, gobj, ret_part);
        if (it_8026B2B4(item_gobj) == 1) {
            ft_800881D8(fp, fp->ft_data->x4C_collisionData->x2C, 127, 64);
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_ItemGet_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80094A14 000915F4  7C 08 02 A6 */	mflr r0
/* 80094A18 000915F8  90 01 00 04 */	stw r0, 4(r1)
/* 80094A1C 000915FC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80094A20 00091600  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80094A24 00091604  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80094A28 00091608  7C 7E 1B 78 */	mr r30, r3
/* 80094A2C 0009160C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80094A30 00091610  88 7F 22 10 */	lbz r3, 0x2210(r31)
/* 80094A34 00091614  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 80094A38 00091618  41 82 00 18 */	beq lbl_80094A50
/* 80094A3C 0009161C  38 00 00 00 */	li r0, 0
/* 80094A40 00091620  50 03 26 F6 */	rlwimi r3, r0, 4, 0x1b, 0x1b
/* 80094A44 00091624  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 80094A48 00091628  38 00 00 01 */	li r0, 1
/* 80094A4C 0009162C  48 00 00 08 */	b lbl_80094A54
lbl_80094A50:
/* 80094A50 00091630  38 00 00 00 */	li r0, 0
lbl_80094A54:
/* 80094A54 00091634  2C 00 00 00 */	cmpwi r0, 0
/* 80094A58 00091638  41 82 00 34 */	beq lbl_80094A8C
/* 80094A5C 0009163C  80 1F 23 40 */	lwz r0, 0x2340(r31)
/* 80094A60 00091640  2C 00 00 00 */	cmpwi r0, 0
/* 80094A64 00091644  41 82 00 0C */	beq lbl_80094A70
/* 80094A68 00091648  38 80 00 02 */	li r4, 2
/* 80094A6C 0009164C  48 00 00 08 */	b lbl_80094A74
lbl_80094A70:
/* 80094A70 00091650  38 80 00 01 */	li r4, 1
lbl_80094A74:
/* 80094A74 00091654  7F C3 F3 78 */	mr r3, r30
/* 80094A78 00091658  4B FF F8 29 */	bl ftCo_800942A0
/* 80094A7C 0009165C  7C 64 1B 79 */	or. r4, r3, r3
/* 80094A80 00091660  41 82 00 0C */	beq lbl_80094A8C
/* 80094A84 00091664  7F C3 F3 78 */	mr r3, r30
/* 80094A88 00091668  4B FF FE 21 */	bl ftCo_800948A8
lbl_80094A8C:
/* 80094A8C 0009166C  7F C3 F3 78 */	mr r3, r30
/* 80094A90 00091670  4B FD A7 A9 */	bl ftAnim_IsFramesRemaining
/* 80094A94 00091674  2C 03 00 00 */	cmpwi r3, 0
/* 80094A98 00091678  40 82 00 70 */	bne lbl_80094B08
/* 80094A9C 0009167C  80 1F 19 78 */	lwz r0, 0x1978(r31)
/* 80094AA0 00091680  28 00 00 00 */	cmplwi r0, 0
/* 80094AA4 00091684  41 82 00 08 */	beq lbl_80094AAC
/* 80094AA8 00091688  48 00 00 08 */	b lbl_80094AB0
lbl_80094AAC:
/* 80094AAC 0009168C  80 1F 19 74 */	lwz r0, 0x1974(r31)
lbl_80094AB0:
/* 80094AB0 00091690  28 00 00 00 */	cmplwi r0, 0
/* 80094AB4 00091694  7C 04 03 78 */	mr r4, r0
/* 80094AB8 00091698  41 82 00 48 */	beq lbl_80094B00
/* 80094ABC 0009169C  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80094AC0 000916A0  2C 00 00 5C */	cmpwi r0, 0x5c
/* 80094AC4 000916A4  40 82 00 18 */	bne lbl_80094ADC
/* 80094AC8 000916A8  7F C3 F3 78 */	mr r3, r30
/* 80094ACC 000916AC  4B FF F9 B1 */	bl ftCo_8009447C
/* 80094AD0 000916B0  2C 03 00 00 */	cmpwi r3, 0
/* 80094AD4 000916B4  41 82 00 2C */	beq lbl_80094B00
/* 80094AD8 000916B8  48 00 00 30 */	b lbl_80094B08
lbl_80094ADC:
/* 80094ADC 000916BC  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 80094AE0 000916C0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80094AE4 000916C4  41 82 00 10 */	beq lbl_80094AF4
/* 80094AE8 000916C8  7F C3 F3 78 */	mr r3, r30
/* 80094AEC 000916CC  48 04 AE 95 */	bl ftDk_MS_341_800DF980
/* 80094AF0 000916D0  48 00 00 18 */	b lbl_80094B08
lbl_80094AF4:
/* 80094AF4 000916D4  7F C3 F3 78 */	mr r3, r30
/* 80094AF8 000916D8  48 00 22 A5 */	bl ftCo_80096D9C
/* 80094AFC 000916DC  48 00 00 0C */	b lbl_80094B08
lbl_80094B00:
/* 80094B00 000916E0  7F C3 F3 78 */	mr r3, r30
/* 80094B04 000916E4  4B FF 57 B9 */	bl ft_8008A2BC
lbl_80094B08:
/* 80094B08 000916E8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80094B0C 000916EC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80094B10 000916F0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80094B14 000916F4  38 21 00 18 */	addi r1, r1, 0x18
/* 80094B18 000916F8  7C 08 03 A6 */	mtlr r0
/* 80094B1C 000916FC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline enum_t inlineA0(ftCo_Fighter* fp)
{
    enum_t unk_enum;
    if (fp->mv.co.itemget.x0) {
        unk_enum = 2;
    } else {
        unk_enum = 1;
    }
    return unk_enum;
}

void ftCo_ItemGet_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (ftCheckThrowB3(fp)) {
        Item_GObj* item_gobj = ftCo_800942A0(gobj, inlineA0(fp));
        if (item_gobj != NULL) {
            ftCo_800948A8(gobj, item_gobj);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Item_GObj* item_gobj = fp->x1978;
        if (item_gobj == NULL) {
            item_gobj = fp->item_gobj;
        }
        if (item_gobj != NULL) {
            if (fp->motion_id == ftCo_MS_LightGet) {
                if (ftCo_8009447C(gobj, item_gobj)) {
                    return;
                }
            } else {
                if (fp->x2222_b0) {
                    ftDk_MS_341_800DF980(gobj);
                } else {
                    ftCo_80096D9C(gobj);
                }
                return;
            }
        }
        ft_8008A2BC(gobj);
    }
}
#endif

void ftCo_ItemGet_IASA(HSD_GObj* gobj) {}

void ftCo_ItemGet_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_ItemGet_Coll(HSD_GObj* gobj)
{
    ft_800841B8(gobj, ftCo_80094D90);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm static void ftCo_80094B6C(ftCo_GObj* gobj, Item_GObj* item_gobj)
{ // clang-format off
    nofralloc
/* 80094B6C 0009174C  7C 08 02 A6 */	mflr r0
/* 80094B70 00091750  90 01 00 04 */	stw r0, 4(r1)
/* 80094B74 00091754  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80094B78 00091758  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80094B7C 0009175C  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80094B80 00091760  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80094B84 00091764  7C 9D 23 79 */	or. r29, r4, r4
/* 80094B88 00091768  93 81 00 20 */	stw r28, 0x20(r1)
/* 80094B8C 0009176C  3B 83 00 00 */	addi r28, r3, 0
/* 80094B90 00091770  3C 60 80 3C */	lis r3, ftItemPickup_803C5580@ha
/* 80094B94 00091774  83 DC 00 2C */	lwz r30, 0x2c(r28)
/* 80094B98 00091778  3B E3 55 80 */	addi r31, r3, ftItemPickup_803C5580@l
/* 80094B9C 0009177C  40 82 00 20 */	bne lbl_80094BBC
/* 80094BA0 00091780  38 7F 00 00 */	addi r3, r31, 0
/* 80094BA4 00091784  4C C6 31 82 */	crclr 6
/* 80094BA8 00091788  48 2B 0B 01 */	bl OSReport
/* 80094BAC 0009178C  38 7F 00 24 */	addi r3, r31, 0x24
/* 80094BB0 00091790  38 BF 00 34 */	addi r5, r31, 0x34
/* 80094BB4 00091794  38 80 01 8F */	li r4, 0x18f
/* 80094BB8 00091798  48 2F 36 69 */	bl __assert
lbl_80094BBC:
/* 80094BBC 0009179C  7F A3 EB 78 */	mr r3, r29
/* 80094BC0 000917A0  48 1D 67 4D */	bl it_8026B30C
/* 80094BC4 000917A4  2C 03 00 05 */	cmpwi r3, 5
/* 80094BC8 000917A8  40 82 01 A8 */	bne lbl_80094D70
/* 80094BCC 000917AC  7F A3 EB 78 */	mr r3, r29
/* 80094BD0 000917B0  48 1D 67 31 */	bl itGetKind
/* 80094BD4 000917B4  2C 03 00 1F */	cmpwi r3, 0x1f
/* 80094BD8 000917B8  41 82 01 48 */	beq lbl_80094D20
/* 80094BDC 000917BC  40 80 00 40 */	bge lbl_80094C1C
/* 80094BE0 000917C0  2C 03 00 12 */	cmpwi r3, 0x12
/* 80094BE4 000917C4  41 82 00 AC */	beq lbl_80094C90
/* 80094BE8 000917C8  40 80 00 1C */	bge lbl_80094C04
/* 80094BEC 000917CC  2C 03 00 09 */	cmpwi r3, 9
/* 80094BF0 000917D0  41 82 00 80 */	beq lbl_80094C70
/* 80094BF4 000917D4  40 80 01 7C */	bge lbl_80094D70
/* 80094BF8 000917D8  2C 03 00 08 */	cmpwi r3, 8
/* 80094BFC 000917DC  40 80 00 54 */	bge lbl_80094C50
/* 80094C00 000917E0  48 00 01 70 */	b lbl_80094D70
lbl_80094C04:
/* 80094C04 000917E4  2C 03 00 1D */	cmpwi r3, 0x1d
/* 80094C08 000917E8  41 82 00 E8 */	beq lbl_80094CF0
/* 80094C0C 000917EC  40 80 01 64 */	bge lbl_80094D70
/* 80094C10 000917F0  2C 03 00 1C */	cmpwi r3, 0x1c
/* 80094C14 000917F4  40 80 01 00 */	bge lbl_80094D14
/* 80094C18 000917F8  48 00 01 58 */	b lbl_80094D70
lbl_80094C1C:
/* 80094C1C 000917FC  2C 03 00 CD */	cmpwi r3, 0xcd
/* 80094C20 00091800  41 82 00 90 */	beq lbl_80094CB0
/* 80094C24 00091804  40 80 00 20 */	bge lbl_80094C44
/* 80094C28 00091808  2C 03 00 9F */	cmpwi r3, 0x9f
/* 80094C2C 0009180C  41 82 01 3C */	beq lbl_80094D68
/* 80094C30 00091810  40 80 01 40 */	bge lbl_80094D70
/* 80094C34 00091814  2C 03 00 21 */	cmpwi r3, 0x21
/* 80094C38 00091818  41 82 01 10 */	beq lbl_80094D48
/* 80094C3C 0009181C  40 80 01 34 */	bge lbl_80094D70
/* 80094C40 00091820  48 00 00 F0 */	b lbl_80094D30
lbl_80094C44:
/* 80094C44 00091824  2C 03 00 E2 */	cmpwi r3, 0xe2
/* 80094C48 00091828  41 82 00 88 */	beq lbl_80094CD0
/* 80094C4C 0009182C  48 00 01 24 */	b lbl_80094D70
lbl_80094C50:
/* 80094C50 00091830  7F A3 EB 78 */	mr r3, r29
/* 80094C54 00091834  48 1D 68 29 */	bl it_8026B47C
/* 80094C58 00091838  38 83 00 00 */	addi r4, r3, 0
/* 80094C5C 0009183C  38 7E 00 00 */	addi r3, r30, 0
/* 80094C60 00091840  4B FD 82 FD */	bl Fighter_8006CF5C
/* 80094C64 00091844  7F A3 EB 78 */	mr r3, r29
/* 80094C68 00091848  48 1D 5C 85 */	bl Item_8026A8EC
/* 80094C6C 0009184C  48 00 01 04 */	b lbl_80094D70
lbl_80094C70:
/* 80094C70 00091850  7F A3 EB 78 */	mr r3, r29
/* 80094C74 00091854  48 1D 68 09 */	bl it_8026B47C
/* 80094C78 00091858  38 83 00 00 */	addi r4, r3, 0
/* 80094C7C 0009185C  38 7E 00 00 */	addi r3, r30, 0
/* 80094C80 00091860  4B FD 82 DD */	bl Fighter_8006CF5C
/* 80094C84 00091864  7F A3 EB 78 */	mr r3, r29
/* 80094C88 00091868  48 1D 5C 65 */	bl Item_8026A8EC
/* 80094C8C 0009186C  48 00 00 E4 */	b lbl_80094D70
lbl_80094C90:
/* 80094C90 00091870  7F A3 EB 78 */	mr r3, r29
/* 80094C94 00091874  48 1D 67 E9 */	bl it_8026B47C
/* 80094C98 00091878  38 83 00 00 */	addi r4, r3, 0
/* 80094C9C 0009187C  38 7E 00 00 */	addi r3, r30, 0
/* 80094CA0 00091880  4B FD 82 BD */	bl Fighter_8006CF5C
/* 80094CA4 00091884  7F A3 EB 78 */	mr r3, r29
/* 80094CA8 00091888  48 1D 5C 45 */	bl Item_8026A8EC
/* 80094CAC 0009188C  48 00 00 C4 */	b lbl_80094D70
lbl_80094CB0:
/* 80094CB0 00091890  7F A3 EB 78 */	mr r3, r29
/* 80094CB4 00091894  48 1D 67 C9 */	bl it_8026B47C
/* 80094CB8 00091898  38 83 00 00 */	addi r4, r3, 0
/* 80094CBC 0009189C  38 7E 00 00 */	addi r3, r30, 0
/* 80094CC0 000918A0  4B FD 82 9D */	bl Fighter_8006CF5C
/* 80094CC4 000918A4  7F A3 EB 78 */	mr r3, r29
/* 80094CC8 000918A8  48 1D 5C 25 */	bl Item_8026A8EC
/* 80094CCC 000918AC  48 00 00 A4 */	b lbl_80094D70
lbl_80094CD0:
/* 80094CD0 000918B0  7F A3 EB 78 */	mr r3, r29
/* 80094CD4 000918B4  48 1D 67 A9 */	bl it_8026B47C
/* 80094CD8 000918B8  38 83 00 00 */	addi r4, r3, 0
/* 80094CDC 000918BC  38 7E 00 00 */	addi r3, r30, 0
/* 80094CE0 000918C0  4B FD 82 7D */	bl Fighter_8006CF5C
/* 80094CE4 000918C4  7F A3 EB 78 */	mr r3, r29
/* 80094CE8 000918C8  48 1D 5C 05 */	bl Item_8026A8EC
/* 80094CEC 000918CC  48 00 00 84 */	b lbl_80094D70
lbl_80094CF0:
/* 80094CF0 000918D0  C0 02 8B A8 */	lfs f0, ftCo_804D8588
/* 80094CF4 000918D4  7F A3 EB 78 */	mr r3, r29
/* 80094CF8 000918D8  C0 22 8B A4 */	lfs f1, ftCo_804D8584
/* 80094CFC 000918DC  38 81 00 14 */	addi r4, r1, 0x14
/* 80094D00 000918E0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80094D04 000918E4  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80094D08 000918E8  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80094D0C 000918EC  48 1D 5E CD */	bl Item_8026ABD8
/* 80094D10 000918F0  48 00 00 60 */	b lbl_80094D70
lbl_80094D14:
/* 80094D14 000918F4  7F 83 E3 78 */	mr r3, r28
/* 80094D18 000918F8  48 03 05 6D */	bl ftCo_800C5284
/* 80094D1C 000918FC  48 00 00 54 */	b lbl_80094D70
lbl_80094D20:
/* 80094D20 00091900  38 7C 00 00 */	addi r3, r28, 0
/* 80094D24 00091904  38 9D 00 00 */	addi r4, r29, 0
/* 80094D28 00091908  4B FE AD 31 */	bl ftCommon_8007FA58
/* 80094D2C 0009190C  48 00 00 44 */	b lbl_80094D70
lbl_80094D30:
/* 80094D30 00091910  38 7C 00 00 */	addi r3, r28, 0
/* 80094D34 00091914  38 9D 00 00 */	addi r4, r29, 0
/* 80094D38 00091918  4B FF 24 71 */	bl ftLib_800871A8
/* 80094D3C 0009191C  7F A3 EB 78 */	mr r3, r29
/* 80094D40 00091920  48 1D 5B AD */	bl Item_8026A8EC
/* 80094D44 00091924  48 00 00 2C */	b lbl_80094D70
lbl_80094D48:
/* 80094D48 00091928  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80094D4C 0009192C  38 7C 00 00 */	addi r3, r28, 0
/* 80094D50 00091930  38 A0 00 01 */	li r5, 1
/* 80094D54 00091934  80 84 07 CC */	lwz r4, 0x7cc(r4)
/* 80094D58 00091938  48 03 3B 7D */	bl ftCo_800C88D4
/* 80094D5C 0009193C  7F A3 EB 78 */	mr r3, r29
/* 80094D60 00091940  48 1D 5B 8D */	bl Item_8026A8EC
/* 80094D64 00091944  48 00 00 0C */	b lbl_80094D70
lbl_80094D68:
/* 80094D68 00091948  7F A3 EB 78 */	mr r3, r29
/* 80094D6C 0009194C  48 1D 5B 81 */	bl Item_8026A8EC
lbl_80094D70:
/* 80094D70 00091950  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80094D74 00091954  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80094D78 00091958  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80094D7C 0009195C  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80094D80 00091960  83 81 00 20 */	lwz r28, 0x20(r1)
/* 80094D84 00091964  38 21 00 30 */	addi r1, r1, 0x30
/* 80094D88 00091968  7C 08 03 A6 */	mtlr r0
/* 80094D8C 0009196C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80094B6C(HSD_GObj* gobj, HSD_GObj* item_gobj)
{
    Vec3 vec;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (item_gobj == NULL) {
        OSReport("ftGetImmItem item_gobj is NULL!!\n");
        __assert("ftpickupitem.c", 399, "item_gobj");
    }
    if (it_8026B30C(item_gobj) == 5) {
        switch (itGetKind(item_gobj)) {
        case It_Kind_Heart:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Tomato:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Foods:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case Pokemon_Lucky_Egg:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_WhispyHealApple:
            Fighter_8006CF5C(fp, it_8026B47C(item_gobj));
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_WStar:
            vec.x = vec.y = vec.z = 0;
            Item_8026ABD8(item_gobj, &vec, 1);
            return;
        case It_Kind_Hammer:
            ftCo_800C5284(gobj);
            return;
        case It_Kind_RabbitC:
            ftCommon_8007FA58(gobj, item_gobj);
            return;
        case It_Kind_MetalB:
            ftLib_800871A8(gobj, item_gobj);
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Spycloak:
            ftCo_800C88D4(gobj, p_ftCommonData->x7CC, 1);
            Item_8026A8EC(item_gobj);
            return;
        case It_Kind_Coin:
            Item_8026A8EC(item_gobj);
            return;
        }
    }
}
#endif

void ftCo_80094D90(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_8009750C(gobj);
    /// @todo #ftCo_80094DF8
    if (fp->item_gobj != NULL) {
        ftCo_80094B6C(gobj, fp->item_gobj);
    }
    if (fp->x1978 != NULL) {
        ftCo_80094B6C(gobj, fp->x1978);
    }
    ftCo_800CC730(gobj);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80094DF8(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80094DF8 000919D8  7C 08 02 A6 */	mflr r0
/* 80094DFC 000919DC  90 01 00 04 */	stw r0, 4(r1)
/* 80094E00 000919E0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80094E04 000919E4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80094E08 000919E8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80094E0C 000919EC  7C 7E 1B 78 */	mr r30, r3
/* 80094E10 000919F0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80094E14 000919F4  80 9F 19 74 */	lwz r4, 0x1974(r31)
/* 80094E18 000919F8  28 04 00 00 */	cmplwi r4, 0
/* 80094E1C 000919FC  41 82 00 0C */	beq lbl_80094E28
/* 80094E20 00091A00  7F C3 F3 78 */	mr r3, r30
/* 80094E24 00091A04  4B FF FD 49 */	bl ftCo_80094B6C
lbl_80094E28:
/* 80094E28 00091A08  80 9F 19 78 */	lwz r4, 0x1978(r31)
/* 80094E2C 00091A0C  28 04 00 00 */	cmplwi r4, 0
/* 80094E30 00091A10  41 82 00 0C */	beq lbl_80094E3C
/* 80094E34 00091A14  7F C3 F3 78 */	mr r3, r30
/* 80094E38 00091A18  4B FF FD 35 */	bl ftCo_80094B6C
lbl_80094E3C:
/* 80094E3C 00091A1C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80094E40 00091A20  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80094E44 00091A24  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80094E48 00091A28  38 21 00 18 */	addi r1, r1, 0x18
/* 80094E4C 00091A2C  7C 08 03 A6 */	mtlr r0
/* 80094E50 00091A30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80094DF8(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        ftCo_80094B6C(gobj, fp->item_gobj);
    }
    if (fp->x1978 != NULL) {
        ftCo_80094B6C(gobj, fp->x1978);
    }
}
#endif
