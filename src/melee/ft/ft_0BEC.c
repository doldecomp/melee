#include "ft/forward.h"

#include "ft_0BEC.h"

#include "ft/ftparts.h"
#include "ftFox/types.h"
#include "ftMario/ftMr_SpecialN.h"
#include "it/it_26B1.h"
#include "it/items/itdrmariopill.h"
#include "it/items/itfoxblaster.h"
#include "it/items/itnessbat.h"

static inline void setupInitialState(Fighter_GObj* gobj,
                                     FtMotionId initial_motion)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, initial_motion, Ft_MF_None, 0.f, 1.f, 0.f,
                              NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    fp->x2228_b1 = true;
    fp->item_gobj = NULL;
    fp->x1984_heldItemSpec = NULL;
}

void ftCo_800BECB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    setupInitialState(gobj, ftCo_MS_DeadDown);
    switch (fp->kind) {
    case FTKIND_FOX: {
        ftFox_DatAttrs* da = fp->dat_attrs;
        fp->item_gobj =
            it_802AE994(gobj, ftParts_8007500C(fp, FtPart_RThumbNb),
                        da->x20_FOX_BLASTER_GUN_ITKIND);
        it_8026BAE8(fp->item_gobj,
                    fp->x34_scale.y * fp->co_attrs.model_scaling);
    }
    }
}

void ftCo_800BED84(Fighter_GObj* gobj) {}

ASM void ftCo_800BED88(Fighter_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    setupInitialState(gobj, ftCo_MS_DeadRight);
    switch (fp->kind) {
    case FTKIND_FOX: {
        ftFox_DatAttrs* da = fp->dat_attrs;
        fp->item_gobj =
            it_802AE994(gobj, ftParts_8007500C(fp, FtPart_RThumbNb),
                        da->x20_FOX_BLASTER_GUN_ITKIND);
        it_8026BAE8(fp->item_gobj,
                    fp->x34_scale.y * fp->co_attrs.model_scaling);
        break;
    }
    case FTKIND_DRMARIO: {
        ftCo_DatAttrs* co;
        fp->item_gobj =
            it_802C09C4(gobj, &fp->cur_pos, ftMr_SpecialN_VitaminRandom(gobj),
                        0x31, 1, 0, fp->facing_dir);
        co = &fp->co_attrs;
        it_8026BAE8(fp->item_gobj,
                    0.71428f * (fp->x34_scale.y * co->model_scaling));
        fp->x1984_heldItemSpec =
            it_802C09C4(gobj, &fp->cur_pos, ftMr_SpecialN_VitaminRandom(gobj),
                        0x31, 0, 0, fp->facing_dir);
        it_8026BAE8(fp->x1984_heldItemSpec,
                    0.71428f * (fp->x34_scale.y * co->model_scaling));
        break;
    }
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BED88 000BB968  7C 08 02 A6 */	mflr r0
/* 800BED8C 000BB96C  38 80 00 02 */	li r4, 2
/* 800BED90 000BB970  90 01 00 04 */	stw r0, 4(r1)
/* 800BED94 000BB974  38 A0 00 00 */	li r5, 0
/* 800BED98 000BB978  38 C0 00 00 */	li r6, 0
/* 800BED9C 000BB97C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800BEDA0 000BB980  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800BEDA4 000BB984  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800BEDA8 000BB988  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800BEDAC 000BB98C  7C 7D 1B 78 */	mr r29, r3
/* 800BEDB0 000BB990  C0 22 92 20 */	lfs f1, 0.f
/* 800BEDB4 000BB994  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800BEDB8 000BB998  FC 60 08 90 */	fmr f3, f1
/* 800BEDBC 000BB99C  C0 42 92 24 */	lfs f2, 1.f
/* 800BEDC0 000BB9A0  4B FA A5 ED */	bl Fighter_ChangeMotionState
/* 800BEDC4 000BB9A4  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 800BEDC8 000BB9A8  38 80 00 01 */	li r4, 1
/* 800BEDCC 000BB9AC  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800BEDD0 000BB9B0  98 1E 22 19 */	stb r0, 0x2219(r30)
/* 800BEDD4 000BB9B4  38 00 00 00 */	li r0, 0
/* 800BEDD8 000BB9B8  88 7E 22 19 */	lbz r3, 0x2219(r30)
/* 800BEDDC 000BB9BC  50 83 36 72 */	rlwimi r3, r4, 6, 0x19, 0x19
/* 800BEDE0 000BB9C0  98 7E 22 19 */	stb r3, 0x2219(r30)
/* 800BEDE4 000BB9C4  88 7E 22 28 */	lbz r3, 0x2228(r30)
/* 800BEDE8 000BB9C8  50 83 36 72 */	rlwimi r3, r4, 6, 0x19, 0x19
/* 800BEDEC 000BB9CC  98 7E 22 28 */	stb r3, 0x2228(r30)
/* 800BEDF0 000BB9D0  90 1E 19 74 */	stw r0, 0x1974(r30)
/* 800BEDF4 000BB9D4  90 1E 19 84 */	stw r0, 0x1984(r30)
/* 800BEDF8 000BB9D8  80 1E 00 04 */	lwz r0, 4(r30)
/* 800BEDFC 000BB9DC  2C 00 00 15 */	cmpwi r0, 0x15
/* 800BEE00 000BB9E0  41 82 00 50 */	beq lbl_800BEE50
/* 800BEE04 000BB9E4  40 80 00 E0 */	bge lbl_800BEEE4
/* 800BEE08 000BB9E8  2C 00 00 01 */	cmpwi r0, 1
/* 800BEE0C 000BB9EC  41 82 00 08 */	beq lbl_800BEE14
/* 800BEE10 000BB9F0  48 00 00 D4 */	b lbl_800BEEE4
lbl_800BEE14:
/* 800BEE14 000BB9F4  83 FE 02 D4 */	lwz r31, 0x2d4(r30)
/* 800BEE18 000BB9F8  38 7E 00 00 */	addi r3, r30, 0
/* 800BEE1C 000BB9FC  38 80 00 31 */	li r4, 0x31
/* 800BEE20 000BBA00  4B FB 61 ED */	bl ftParts_8007500C
/* 800BEE24 000BBA04  80 BF 00 20 */	lwz r5, 0x20(r31)
/* 800BEE28 000BBA08  7C 64 1B 78 */	mr r4, r3
/* 800BEE2C 000BBA0C  7F A3 EB 78 */	mr r3, r29
/* 800BEE30 000BBA10  48 1E FB 65 */	bl it_802AE994
/* 800BEE34 000BBA14  90 7E 19 74 */	stw r3, 0x1974(r30)
/* 800BEE38 000BBA18  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 800BEE3C 000BBA1C  C0 1E 01 9C */	lfs f0, 0x19c(r30)
/* 800BEE40 000BBA20  80 7E 19 74 */	lwz r3, 0x1974(r30)
/* 800BEE44 000BBA24  EC 21 00 32 */	fmuls f1, f1, f0
/* 800BEE48 000BBA28  48 1A CC A1 */	bl it_8026BAE8
/* 800BEE4C 000BBA2C  48 00 00 98 */	b lbl_800BEEE4
lbl_800BEE50:
/* 800BEE50 000BBA30  7F A3 EB 78 */	mr r3, r29
/* 800BEE54 000BBA34  48 02 1E C9 */	bl ftMr_SpecialN_VitaminRandom
/* 800BEE58 000BBA38  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 800BEE5C 000BBA3C  7C 65 1B 78 */	mr r5, r3
/* 800BEE60 000BBA40  38 7D 00 00 */	addi r3, r29, 0
/* 800BEE64 000BBA44  38 9E 00 B0 */	addi r4, r30, 0xb0
/* 800BEE68 000BBA48  38 C0 00 31 */	li r6, 0x31
/* 800BEE6C 000BBA4C  38 E0 00 01 */	li r7, 1
/* 800BEE70 000BBA50  39 00 00 00 */	li r8, 0
/* 800BEE74 000BBA54  48 20 1B 51 */	bl it_802C09C4
/* 800BEE78 000BBA58  90 7E 19 74 */	stw r3, 0x1974(r30)
/* 800BEE7C 000BBA5C  3B FE 01 10 */	addi r31, r30, 0x110
/* 800BEE80 000BBA60  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 800BEE84 000BBA64  C0 1E 01 9C */	lfs f0, 0x19c(r30)
/* 800BEE88 000BBA68  C0 42 92 28 */	lfs f2, 0.71428f
/* 800BEE8C 000BBA6C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BEE90 000BBA70  80 7E 19 74 */	lwz r3, 0x1974(r30)
/* 800BEE94 000BBA74  EC 22 00 32 */	fmuls f1, f2, f0
/* 800BEE98 000BBA78  48 1A CC 51 */	bl it_8026BAE8
/* 800BEE9C 000BBA7C  7F A3 EB 78 */	mr r3, r29
/* 800BEEA0 000BBA80  48 02 1E 7D */	bl ftMr_SpecialN_VitaminRandom
/* 800BEEA4 000BBA84  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 800BEEA8 000BBA88  7C 65 1B 78 */	mr r5, r3
/* 800BEEAC 000BBA8C  38 7D 00 00 */	addi r3, r29, 0
/* 800BEEB0 000BBA90  38 9E 00 B0 */	addi r4, r30, 0xb0
/* 800BEEB4 000BBA94  38 C0 00 31 */	li r6, 0x31
/* 800BEEB8 000BBA98  38 E0 00 00 */	li r7, 0
/* 800BEEBC 000BBA9C  39 00 00 00 */	li r8, 0
/* 800BEEC0 000BBAA0  48 20 1B 05 */	bl it_802C09C4
/* 800BEEC4 000BBAA4  90 7E 19 84 */	stw r3, 0x1984(r30)
/* 800BEEC8 000BBAA8  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 800BEECC 000BBAAC  C0 1F 00 8C */	lfs f0, 0x8c(r31)
/* 800BEED0 000BBAB0  C0 42 92 28 */	lfs f2, 0.71428f
/* 800BEED4 000BBAB4  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BEED8 000BBAB8  80 7E 19 84 */	lwz r3, 0x1984(r30)
/* 800BEEDC 000BBABC  EC 22 00 32 */	fmuls f1, f2, f0
/* 800BEEE0 000BBAC0  48 1A CC 09 */	bl it_8026BAE8
lbl_800BEEE4:
/* 800BEEE4 000BBAC4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BEEE8 000BBAC8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800BEEEC 000BBACC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800BEEF0 000BBAD0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800BEEF4 000BBAD4  38 21 00 28 */	addi r1, r1, 0x28
/* 800BEEF8 000BBAD8  7C 08 03 A6 */	mtlr r0
/* 800BEEFC 000BBADC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_800BEF00(Fighter_GObj* gobj) {}

void ftCo_800BEF04(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStarIce, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    fp->x2228_b1 = true;
    fp->item_gobj = NULL;
    fp->x1984_heldItemSpec = NULL;
    switch (fp->kind) {
    case FTKIND_NESS: {
        fp->item_gobj =
            it_802AD590(gobj, ftParts_8007500C(fp, FtPart_RThumbNb));
        it_8026BAE8(fp->item_gobj,
                    0.8f * (fp->x34_scale.y * fp->co_attrs.model_scaling));
    }
    }
}

void ftCo_800BEFD0(Fighter_GObj* gobj) {}
