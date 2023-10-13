#include "ft/forward.h"

#include "ft_0BEC.h"

#include "ft/ftparts.h"
#include "ftFox/types.h"
#include "ftMario/ftMr_SpecialN.h"
#include "it/it_26B1.h"
#include "it/items/itdrmariopill.h"
#include "it/items/itfoxblaster.h"
#include "it/items/itnessbat.h"

LITERAL float const ftCo_804D8C00 = 0;
LITERAL float const ftCo_804D8C04 = 1;
LITERAL float const ftCo_804D8C08 = 0.71428;
LITERAL float const ftCo_804D8C0C = 0.8;

#ifdef WIP
#pragma force_active on
#endif

ASM void ftCo_800BECB0(Fighter_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0, Ft_MF_None, 0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    fp->x2228_b1 = true;
    fp->item_gobj = NULL;
    fp->x1984_heldItemSpec = NULL;
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

#else /* clang-format off */
{ nofralloc
/* 800BECB0 000BB890  7C 08 02 A6 */	mflr r0
/* 800BECB4 000BB894  38 80 00 00 */	li r4, 0
/* 800BECB8 000BB898  90 01 00 04 */	stw r0, 4(r1)
/* 800BECBC 000BB89C  38 A0 00 00 */	li r5, 0
/* 800BECC0 000BB8A0  38 C0 00 00 */	li r6, 0
/* 800BECC4 000BB8A4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800BECC8 000BB8A8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800BECCC 000BB8AC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800BECD0 000BB8B0  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800BECD4 000BB8B4  7C 7D 1B 78 */	mr r29, r3
/* 800BECD8 000BB8B8  C0 22 92 20 */	lfs f1, ftCo_804D8C00
/* 800BECDC 000BB8BC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BECE0 000BB8C0  FC 60 08 90 */	fmr f3, f1
/* 800BECE4 000BB8C4  C0 42 92 24 */	lfs f2, ftCo_804D8C04
/* 800BECE8 000BB8C8  4B FA A6 C5 */	bl Fighter_ChangeMotionState
/* 800BECEC 000BB8CC  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800BECF0 000BB8D0  38 80 00 01 */	li r4, 1
/* 800BECF4 000BB8D4  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800BECF8 000BB8D8  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800BECFC 000BB8DC  38 00 00 00 */	li r0, 0
/* 800BED00 000BB8E0  88 7F 22 19 */	lbz r3, 0x2219(r31)
/* 800BED04 000BB8E4  50 83 36 72 */	rlwimi r3, r4, 6, 0x19, 0x19
/* 800BED08 000BB8E8  98 7F 22 19 */	stb r3, 0x2219(r31)
/* 800BED0C 000BB8EC  88 7F 22 28 */	lbz r3, 0x2228(r31)
/* 800BED10 000BB8F0  50 83 36 72 */	rlwimi r3, r4, 6, 0x19, 0x19
/* 800BED14 000BB8F4  98 7F 22 28 */	stb r3, 0x2228(r31)
/* 800BED18 000BB8F8  90 1F 19 74 */	stw r0, 0x1974(r31)
/* 800BED1C 000BB8FC  90 1F 19 84 */	stw r0, 0x1984(r31)
/* 800BED20 000BB900  80 1F 00 04 */	lwz r0, 4(r31)
/* 800BED24 000BB904  2C 00 00 01 */	cmpwi r0, 1
/* 800BED28 000BB908  41 82 00 08 */	beq lbl_800BED30
/* 800BED2C 000BB90C  48 00 00 3C */	b lbl_800BED68
lbl_800BED30:
/* 800BED30 000BB910  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 800BED34 000BB914  38 7F 00 00 */	addi r3, r31, 0
/* 800BED38 000BB918  38 80 00 31 */	li r4, 0x31
/* 800BED3C 000BB91C  4B FB 62 D1 */	bl ftParts_8007500C
/* 800BED40 000BB920  80 BE 00 20 */	lwz r5, 0x20(r30)
/* 800BED44 000BB924  7C 64 1B 78 */	mr r4, r3
/* 800BED48 000BB928  7F A3 EB 78 */	mr r3, r29
/* 800BED4C 000BB92C  48 1E FC 49 */	bl it_802AE994
/* 800BED50 000BB930  90 7F 19 74 */	stw r3, 0x1974(r31)
/* 800BED54 000BB934  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800BED58 000BB938  C0 1F 01 9C */	lfs f0, 0x19c(r31)
/* 800BED5C 000BB93C  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800BED60 000BB940  EC 21 00 32 */	fmuls f1, f1, f0
/* 800BED64 000BB944  48 1A CD 85 */	bl it_8026BAE8
lbl_800BED68:
/* 800BED68 000BB948  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BED6C 000BB94C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800BED70 000BB950  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800BED74 000BB954  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800BED78 000BB958  38 21 00 28 */	addi r1, r1, 0x28
/* 800BED7C 000BB95C  7C 08 03 A6 */	mtlr r0
/* 800BED80 000BB960  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_800BED84(Fighter_GObj* gobj) {}

ASM void ftCo_800BED88(Fighter_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 2, Ft_MF_None, 0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
    fp->x2228_b1 = true;
    fp->item_gobj = NULL;
    fp->x1984_heldItemSpec = NULL;
    switch (fp->kind) {
    case FTKIND_FOX: {
        ftFox_DatAttrs* da = fp->dat_attrs;
        fp->item_gobj =
            it_802AE994(gobj, ftParts_8007500C(fp, FtPart_RThumbNb),
                        da->x20_FOX_BLASTER_GUN_ITKIND);
        it_8026BAE8(fp->item_gobj,
                    fp->x34_scale.y * fp->co_attrs.model_scaling);
        return;
    }
    case FTKIND_DRMARIO: {
        fp->item_gobj =
            it_802C09C4(gobj, &fp->cur_pos, ftMr_SpecialN_VitaminRandom(gobj),
                        0x31, 1, 0, fp->facing_dir);
        it_8026BAE8(fp->item_gobj,
                    0.71428f * (fp->x34_scale.y * fp->co_attrs.model_scaling));
        fp->x1984_heldItemSpec =
            it_802C09C4(gobj, &fp->cur_pos, ftMr_SpecialN_VitaminRandom(gobj),
                        0x31, 0, 0, fp->facing_dir);
        it_8026BAE8(fp->x1984_heldItemSpec,
                    0.71428f * (fp->x34_scale.y * fp->co_attrs.model_scaling));
        return;
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
/* 800BEDB0 000BB990  C0 22 92 20 */	lfs f1, ftCo_804D8C00
/* 800BEDB4 000BB994  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800BEDB8 000BB998  FC 60 08 90 */	fmr f3, f1
/* 800BEDBC 000BB99C  C0 42 92 24 */	lfs f2, ftCo_804D8C04
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
/* 800BEE88 000BBA68  C0 42 92 28 */	lfs f2, ftCo_804D8C08
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
/* 800BEED0 000BBAB0  C0 42 92 28 */	lfs f2, ftCo_804D8C08
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

ASM void ftCo_800BEF04(Fighter_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
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

#else /* clang-format off */
{ nofralloc
/* 800BEF04 000BBAE4  7C 08 02 A6 */	mflr r0
/* 800BEF08 000BBAE8  38 80 00 05 */	li r4, 5
/* 800BEF0C 000BBAEC  90 01 00 04 */	stw r0, 4(r1)
/* 800BEF10 000BBAF0  38 A0 00 00 */	li r5, 0
/* 800BEF14 000BBAF4  38 C0 00 00 */	li r6, 0
/* 800BEF18 000BBAF8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800BEF1C 000BBAFC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800BEF20 000BBB00  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800BEF24 000BBB04  7C 7E 1B 78 */	mr r30, r3
/* 800BEF28 000BBB08  C0 22 92 20 */	lfs f1, ftCo_804D8C00
/* 800BEF2C 000BBB0C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BEF30 000BBB10  FC 60 08 90 */	fmr f3, f1
/* 800BEF34 000BBB14  C0 42 92 24 */	lfs f2, ftCo_804D8C04
/* 800BEF38 000BBB18  4B FA A4 75 */	bl Fighter_ChangeMotionState
/* 800BEF3C 000BBB1C  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800BEF40 000BBB20  38 80 00 01 */	li r4, 1
/* 800BEF44 000BBB24  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800BEF48 000BBB28  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800BEF4C 000BBB2C  38 00 00 00 */	li r0, 0
/* 800BEF50 000BBB30  88 7F 22 19 */	lbz r3, 0x2219(r31)
/* 800BEF54 000BBB34  50 83 36 72 */	rlwimi r3, r4, 6, 0x19, 0x19
/* 800BEF58 000BBB38  98 7F 22 19 */	stb r3, 0x2219(r31)
/* 800BEF5C 000BBB3C  88 7F 22 28 */	lbz r3, 0x2228(r31)
/* 800BEF60 000BBB40  50 83 36 72 */	rlwimi r3, r4, 6, 0x19, 0x19
/* 800BEF64 000BBB44  98 7F 22 28 */	stb r3, 0x2228(r31)
/* 800BEF68 000BBB48  90 1F 19 74 */	stw r0, 0x1974(r31)
/* 800BEF6C 000BBB4C  90 1F 19 84 */	stw r0, 0x1984(r31)
/* 800BEF70 000BBB50  80 1F 00 04 */	lwz r0, 4(r31)
/* 800BEF74 000BBB54  2C 00 00 08 */	cmpwi r0, 8
/* 800BEF78 000BBB58  41 82 00 08 */	beq lbl_800BEF80
/* 800BEF7C 000BBB5C  48 00 00 3C */	b lbl_800BEFB8
lbl_800BEF80:
/* 800BEF80 000BBB60  38 7F 00 00 */	addi r3, r31, 0
/* 800BEF84 000BBB64  38 80 00 31 */	li r4, 0x31
/* 800BEF88 000BBB68  4B FB 60 85 */	bl ftParts_8007500C
/* 800BEF8C 000BBB6C  38 83 00 00 */	addi r4, r3, 0
/* 800BEF90 000BBB70  38 7E 00 00 */	addi r3, r30, 0
/* 800BEF94 000BBB74  48 1E E5 FD */	bl it_802AD590
/* 800BEF98 000BBB78  90 7F 19 74 */	stw r3, 0x1974(r31)
/* 800BEF9C 000BBB7C  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800BEFA0 000BBB80  C0 1F 01 9C */	lfs f0, 0x19c(r31)
/* 800BEFA4 000BBB84  C0 42 92 2C */	lfs f2, ftCo_804D8C0C
/* 800BEFA8 000BBB88  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BEFAC 000BBB8C  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800BEFB0 000BBB90  EC 22 00 32 */	fmuls f1, f2, f0
/* 800BEFB4 000BBB94  48 1A CB 35 */	bl it_8026BAE8
lbl_800BEFB8:
/* 800BEFB8 000BBB98  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800BEFBC 000BBB9C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800BEFC0 000BBBA0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800BEFC4 000BBBA4  38 21 00 18 */	addi r1, r1, 0x18
/* 800BEFC8 000BBBA8  7C 08 03 A6 */	mtlr r0
/* 800BEFCC 000BBBAC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_800BEFD0(Fighter_GObj* gobj) {}
