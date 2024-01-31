#include <placeholder.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/types.h>

void GXSetTevOp(GXTevStageID id, GXTevMode mode)
{
    GXTevColorArg inputColor = GX_CC_RASC;
    GXTevAlphaArg inputAlpha = GX_CA_RASA;

    if (id != GX_TEVSTAGE0) {
        inputColor = GX_CC_CPREV;
        inputAlpha = GX_CA_APREV;
    }
    switch (mode) {
    case GX_MODULATE:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_TEXC, inputColor, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_TEXA, inputAlpha, GX_CA_ZERO);
        break;
    case GX_DECAL:
        GXSetTevColorIn(id, inputColor, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, inputAlpha);
        break;
    case GX_BLEND:
        GXSetTevColorIn(id, inputColor, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_TEXA, inputAlpha, GX_CA_ZERO);
        break;
    case GX_REPLACE:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        break;
    case GX_PASSCLR:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, inputColor);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, inputAlpha);
        break;
    }
    GXSetTevColorOp(id, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                    GX_TEVPREV);
    GXSetTevAlphaOp(id, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                    GX_TEVPREV);
}

void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b,
                     GXTevColorArg c, GXTevColorArg d)
{
    GXContext* gx = __GXContexts.main;
    u32* temp_r9 = &gx->x130_data[stage];

    INSERT_FIELD(*temp_r9, a, 4, 12);
    INSERT_FIELD(*temp_r9, b, 4, 8);
    INSERT_FIELD(*temp_r9, c, 4, 4);
    INSERT_FIELD(*temp_r9, d, 4, 0);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(*temp_r9);
    set_x2(GX_FALSE);
}

void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b,
                     GXTevAlphaArg c, GXTevAlphaArg d)
{
    u32* temp_r9 = &__GXContexts.main->x170_data[stage];

    INSERT_FIELD(*temp_r9, a, 3, 13);
    INSERT_FIELD(*temp_r9, b, 3, 10);
    INSERT_FIELD(*temp_r9, c, 3, 7);
    INSERT_FIELD(*temp_r9, d, 3, 4);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(*temp_r9);
    set_x2(GX_FALSE);
}

void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, GXBool clamp, GXTevRegID out_reg)
{
    u32* temp_r3 = &__GXContexts.main->x130_data[stage];

    INSERT_FIELD(*temp_r3, op & 1, 1, 18);
    if (op <= 1) {
        INSERT_FIELD(*temp_r3, scale, 2, 20);
        INSERT_FIELD(*temp_r3, bias, 2, 16);
    } else {
        INSERT_FIELD(*temp_r3, (op >> 1) & 3, 2, 20);
        INSERT_FIELD(*temp_r3, 3, 2, 16);
    }
    INSERT_FIELD(*temp_r3, clamp & 0xFF, 1, 19);
    INSERT_FIELD(*temp_r3, out_reg, 2, 22);

    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(*temp_r3);
    set_x2(GX_FALSE);
}

void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, GXBool clamp, GXTevRegID out_reg)
{
    u32* temp_r3 = &__GXContexts.main->x170_data[stage];

    INSERT_FIELD(*temp_r3, op & 1, 1, 18);
    if (op <= 1) {
        INSERT_FIELD(*temp_r3, scale, 2, 20);
        INSERT_FIELD(*temp_r3, bias, 2, 16);
    } else {
        INSERT_FIELD(*temp_r3, (op >> 1) & 3, 2, 20);
        INSERT_FIELD(*temp_r3, 3, 2, 16);
    }
    INSERT_FIELD(*temp_r3, clamp & 0xFF, 1, 19);
    INSERT_FIELD(*temp_r3, out_reg, 2, 22);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(*temp_r3);
    set_x2(GX_FALSE);
}

void GXSetTevColor(GXTevRegID id, GXColor color)
{
    u32 r30;
    u32 r31;
    r30 = 0;
    INSERT_FIELD(r30, color.r, 11, 0);
    INSERT_FIELD(r30, color.a, 8, 12);
    INSERT_FIELD(r30, 224 + id * 2, 8, 24);
    r31 = 0;
    INSERT_FIELD(r31, color.b, 11, 0);
    INSERT_FIELD(r31, color.g, 8, 12);
    INSERT_FIELD(r31, 225 + id * 2, 8, 24);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = r30;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = r31;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = r31;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = r31;
    __GXContexts.main->x0.u16[1] = 0;
}

void GXSetTevColorS10(s32 arg0, GXColorS10 arg1)
{
    NOT_IMPLEMENTED;
}

void GXSetTevKColor(GXTevKColorID id, GXColor color)
{
    NOT_IMPLEMENTED;
}

void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel)
{
    NOT_IMPLEMENTED;
}

void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel)
{
    NOT_IMPLEMENTED;
}

#ifdef MUST_MATCH
#pragma push
asm void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel,
                          GXTevSwapSel tex_sel)
{ // clang-format off
    nofralloc
/* 80340420 0033D000  54 63 10 3A */	slwi r3, r3, 2
/* 80340424 0033D004  80 0D A5 08 */	lwz r0, __GXContexts(r13)
/* 80340428 0033D008  38 E3 01 70 */	addi r7, r3, 0x170
/* 8034042C 0033D00C  7C E0 3A 14 */	add r7, r0, r7
/* 80340430 0033D010  80 07 00 00 */	lwz r0, 0(r7)
/* 80340434 0033D014  54 A6 10 3A */	slwi r6, r5, 2
/* 80340438 0033D018  38 60 00 61 */	li r3, 0x61
/* 8034043C 0033D01C  54 00 00 3A */	rlwinm r0, r0, 0, 0, 0x1d
/* 80340440 0033D020  7C 00 23 78 */	or r0, r0, r4
/* 80340444 0033D024  90 07 00 00 */	stw r0, 0(r7)
/* 80340448 0033D028  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8034044C 0033D02C  38 00 00 00 */	li r0, 0
/* 80340450 0033D030  80 87 00 00 */	lwz r4, 0(r7)
/* 80340454 0033D034  54 84 07 B6 */	rlwinm r4, r4, 0, 0x1e, 0x1b
/* 80340458 0033D038  7C 84 33 78 */	or r4, r4, r6
/* 8034045C 0033D03C  90 87 00 00 */	stw r4, 0(r7)
/* 80340460 0033D040  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80340464 0033D044  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340468 0033D048  80 87 00 00 */	lwz r4, 0(r7)
/* 8034046C 0033D04C  90 85 80 00 */	stw r4, -0x8000(r5)
/* 80340470 0033D050  B0 03 00 02 */	sth r0, 2(r3)
/* 80340474 0033D054  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
asm void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red,
                               GXTevColorChan green, GXTevColorChan blue,
                               GXTevColorChan alpha)
{ // clang-format off
    nofralloc
/* 80340478 0033D058  54 69 08 3C */	slwi r9, r3, 1
/* 8034047C 0033D05C  80 0D A5 08 */	lwz r0, __GXContexts(r13)
/* 80340480 0033D060  54 63 18 38 */	slwi r3, r3, 3
/* 80340484 0033D064  39 63 01 B0 */	addi r11, r3, 0x1b0
/* 80340488 0033D068  7D 60 5A 14 */	add r11, r0, r11
/* 8034048C 0033D06C  81 0B 00 00 */	lwz r8, 0(r11)
/* 80340490 0033D070  38 09 00 01 */	addi r0, r9, 1
/* 80340494 0033D074  54 03 10 3A */	slwi r3, r0, 2
/* 80340498 0033D078  55 00 00 3A */	rlwinm r0, r8, 0, 0, 0x1d
/* 8034049C 0033D07C  7C 00 23 78 */	or r0, r0, r4
/* 803404A0 0033D080  90 0B 00 00 */	stw r0, 0(r11)
/* 803404A4 0033D084  54 A0 10 3A */	slwi r0, r5, 2
/* 803404A8 0033D088  39 20 00 61 */	li r9, 0x61
/* 803404AC 0033D08C  80 8B 00 00 */	lwz r4, 0(r11)
/* 803404B0 0033D090  3D 00 CC 01 */	lis r8, 0xCC008000@ha
/* 803404B4 0033D094  39 43 01 B0 */	addi r10, r3, 0x1b0
/* 803404B8 0033D098  54 83 07 B6 */	rlwinm r3, r4, 0, 0x1e, 0x1b
/* 803404BC 0033D09C  7C 60 03 78 */	or r0, r3, r0
/* 803404C0 0033D0A0  90 0B 00 00 */	stw r0, 0(r11)
/* 803404C4 0033D0A4  54 E3 10 3A */	slwi r3, r7, 2
/* 803404C8 0033D0A8  38 00 00 00 */	li r0, 0
/* 803404CC 0033D0AC  99 28 80 00 */	stb r9, 0xCC008000@l(r8)
/* 803404D0 0033D0B0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803404D4 0033D0B4  80 AB 00 00 */	lwz r5, 0(r11)
/* 803404D8 0033D0B8  7D 44 52 14 */	add r10, r4, r10
/* 803404DC 0033D0BC  90 A8 80 00 */	stw r5, -0x8000(r8)
/* 803404E0 0033D0C0  80 8A 00 00 */	lwz r4, 0(r10)
/* 803404E4 0033D0C4  54 84 00 3A */	rlwinm r4, r4, 0, 0, 0x1d
/* 803404E8 0033D0C8  7C 84 33 78 */	or r4, r4, r6
/* 803404EC 0033D0CC  90 8A 00 00 */	stw r4, 0(r10)
/* 803404F0 0033D0D0  80 8A 00 00 */	lwz r4, 0(r10)
/* 803404F4 0033D0D4  54 84 07 B6 */	rlwinm r4, r4, 0, 0x1e, 0x1b
/* 803404F8 0033D0D8  7C 83 1B 78 */	or r3, r4, r3
/* 803404FC 0033D0DC  90 6A 00 00 */	stw r3, 0(r10)
/* 80340500 0033D0E0  99 28 80 00 */	stb r9, -0x8000(r8)
/* 80340504 0033D0E4  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340508 0033D0E8  80 8A 00 00 */	lwz r4, 0(r10)
/* 8034050C 0033D0EC  90 88 80 00 */	stw r4, -0x8000(r8)
/* 80340510 0033D0F0  B0 03 00 02 */	sth r0, 2(r3)
/* 80340514 0033D0F4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void GXSetTevClampMode(s32 arg0, s32 arg1) {}

void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1,
                       u8 ref1)
{
    u32 reg = 0;
    INSERT_FIELD(reg, ref0, 8, 0);
    INSERT_FIELD(reg, ref1, 8, 8);
    INSERT_FIELD(reg, comp0, 3, 16);
    INSERT_FIELD(reg, comp1, 3, 19);
    INSERT_FIELD(reg, op, 2, 22);
    INSERT_FIELD(reg, 0xF3, 8, 24);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = reg;
    set_x2(GX_FALSE);
}

void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias)
{
    NOT_IMPLEMENTED;
}

static u32 GXTev_804014E0[] = { 0, 1, 0, 1, 0, 1, 7, 5, 6, 0 };
#ifdef MUST_MATCH
#pragma push
asm void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map,
                       GXChannelID color)
{ // clang-format off
    nofralloc
/* 803405F0 0033D1D0  7C 67 0E 70 */	srawi r7, r3, 1
/* 803405F4 0033D1D4  81 2D A5 08 */	lwz r9, __GXContexts(r13)
/* 803405F8 0033D1D8  54 AA 06 2C */	rlwinm r10, r5, 0, 0x18, 0x16
/* 803405FC 0033D1DC  7C E7 01 94 */	addze r7, r7
/* 80340600 0033D1E0  54 60 10 3A */	slwi r0, r3, 2
/* 80340604 0033D1E4  7D 09 02 14 */	add r8, r9, r0
/* 80340608 0033D1E8  54 E7 10 3A */	slwi r7, r7, 2
/* 8034060C 0033D1EC  90 A8 04 9C */	stw r5, 0x49c(r8)
/* 80340610 0033D1F0  38 E7 01 00 */	addi r7, r7, 0x100
/* 80340614 0033D1F4  28 0A 00 08 */	cmplwi r10, 8
/* 80340618 0033D1F8  38 0A 00 00 */	addi r0, r10, 0
/* 8034061C 0033D1FC  7C E9 3A 14 */	add r7, r9, r7
/* 80340620 0033D200  41 80 00 0C */	blt lbl_8034062C
/* 80340624 0033D204  39 20 00 00 */	li r9, 0
/* 80340628 0033D208  48 00 00 08 */	b lbl_80340630
lbl_8034062C:
/* 8034062C 0033D20C  7C 09 03 78 */	mr r9, r0
lbl_80340630:
/* 80340630 0033D210  2C 04 00 08 */	cmpwi r4, 8
/* 80340634 0033D214  41 80 00 08 */	blt lbl_8034063C
/* 80340638 0033D218  38 80 00 00 */	li r4, 0
lbl_8034063C:
/* 8034063C 0033D21C  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 80340640 0033D220  41 82 00 94 */	beq lbl_803406D4
/* 80340644 0033D224  81 07 00 00 */	lwz r8, 0(r7)
/* 80340648 0033D228  55 23 60 26 */	slwi r3, r9, 0xc
/* 8034064C 0033D22C  54 80 78 20 */	slwi r0, r4, 0xf
/* 80340650 0033D230  55 04 05 20 */	rlwinm r4, r8, 0, 0x14, 0x10
/* 80340654 0033D234  7C 83 1B 78 */	or r3, r4, r3
/* 80340658 0033D238  90 67 00 00 */	stw r3, 0(r7)
/* 8034065C 0033D23C  2C 06 00 FF */	cmpwi r6, 0xff
/* 80340660 0033D240  80 67 00 00 */	lwz r3, 0(r7)
/* 80340664 0033D244  54 63 04 5A */	rlwinm r3, r3, 0, 0x11, 0xd
/* 80340668 0033D248  7C 60 03 78 */	or r0, r3, r0
/* 8034066C 0033D24C  90 07 00 00 */	stw r0, 0(r7)
/* 80340670 0033D250  40 82 00 0C */	bne lbl_8034067C
/* 80340674 0033D254  38 00 00 07 */	li r0, 7
/* 80340678 0033D258  48 00 00 18 */	b lbl_80340690
lbl_8034067C:
/* 8034067C 0033D25C  3C 60 80 40 */	lis r3, GXTev_804014E0@ha
/* 80340680 0033D260  54 C4 10 3A */	slwi r4, r6, 2
/* 80340684 0033D264  38 03 14 E0 */	addi r0, r3, GXTev_804014E0@l
/* 80340688 0033D268  7C 60 22 14 */	add r3, r0, r4
/* 8034068C 0033D26C  80 03 00 00 */	lwz r0, 0(r3)
lbl_80340690:
/* 80340690 0033D270  80 67 00 00 */	lwz r3, 0(r7)
/* 80340694 0033D274  54 00 98 18 */	slwi r0, r0, 0x13
/* 80340698 0033D278  2C 05 00 FF */	cmpwi r5, 0xff
/* 8034069C 0033D27C  54 63 03 52 */	rlwinm r3, r3, 0, 0xd, 9
/* 803406A0 0033D280  7C 60 03 78 */	or r0, r3, r0
/* 803406A4 0033D284  90 07 00 00 */	stw r0, 0(r7)
/* 803406A8 0033D288  38 80 00 00 */	li r4, 0
/* 803406AC 0033D28C  41 82 00 10 */	beq lbl_803406BC
/* 803406B0 0033D290  54 A0 05 EF */	rlwinm. r0, r5, 0, 0x17, 0x17
/* 803406B4 0033D294  40 82 00 08 */	bne lbl_803406BC
/* 803406B8 0033D298  38 80 00 01 */	li r4, 1
lbl_803406BC:
/* 803406BC 0033D29C  80 67 00 00 */	lwz r3, 0(r7)
/* 803406C0 0033D2A0  54 80 90 1A */	slwi r0, r4, 0x12
/* 803406C4 0033D2A4  54 63 03 98 */	rlwinm r3, r3, 0, 0xe, 0xc
/* 803406C8 0033D2A8  7C 60 03 78 */	or r0, r3, r0
/* 803406CC 0033D2AC  90 07 00 00 */	stw r0, 0(r7)
/* 803406D0 0033D2B0  48 00 00 8C */	b lbl_8034075C
lbl_803406D4:
/* 803406D4 0033D2B4  80 67 00 00 */	lwz r3, 0(r7)
/* 803406D8 0033D2B8  54 80 18 38 */	slwi r0, r4, 3
/* 803406DC 0033D2BC  2C 06 00 FF */	cmpwi r6, 0xff
/* 803406E0 0033D2C0  54 63 00 38 */	rlwinm r3, r3, 0, 0, 0x1c
/* 803406E4 0033D2C4  7C 63 4B 78 */	or r3, r3, r9
/* 803406E8 0033D2C8  90 67 00 00 */	stw r3, 0(r7)
/* 803406EC 0033D2CC  80 67 00 00 */	lwz r3, 0(r7)
/* 803406F0 0033D2D0  54 63 07 72 */	rlwinm r3, r3, 0, 0x1d, 0x19
/* 803406F4 0033D2D4  7C 60 03 78 */	or r0, r3, r0
/* 803406F8 0033D2D8  90 07 00 00 */	stw r0, 0(r7)
/* 803406FC 0033D2DC  40 82 00 0C */	bne lbl_80340708
/* 80340700 0033D2E0  38 00 00 07 */	li r0, 7
/* 80340704 0033D2E4  48 00 00 18 */	b lbl_8034071C
lbl_80340708:
/* 80340708 0033D2E8  3C 60 80 40 */	lis r3, GXTev_804014E0@ha
/* 8034070C 0033D2EC  54 C4 10 3A */	slwi r4, r6, 2
/* 80340710 0033D2F0  38 03 14 E0 */	addi r0, r3, GXTev_804014E0@l
/* 80340714 0033D2F4  7C 60 22 14 */	add r3, r0, r4
/* 80340718 0033D2F8  80 03 00 00 */	lwz r0, 0(r3)
lbl_8034071C:
/* 8034071C 0033D2FC  80 67 00 00 */	lwz r3, 0(r7)
/* 80340720 0033D300  54 00 38 30 */	slwi r0, r0, 7
/* 80340724 0033D304  2C 05 00 FF */	cmpwi r5, 0xff
/* 80340728 0033D308  54 63 06 6A */	rlwinm r3, r3, 0, 0x19, 0x15
/* 8034072C 0033D30C  7C 60 03 78 */	or r0, r3, r0
/* 80340730 0033D310  90 07 00 00 */	stw r0, 0(r7)
/* 80340734 0033D314  38 80 00 00 */	li r4, 0
/* 80340738 0033D318  41 82 00 10 */	beq lbl_80340748
/* 8034073C 0033D31C  54 A0 05 EF */	rlwinm. r0, r5, 0, 0x17, 0x17
/* 80340740 0033D320  40 82 00 08 */	bne lbl_80340748
/* 80340744 0033D324  38 80 00 01 */	li r4, 1
lbl_80340748:
/* 80340748 0033D328  80 67 00 00 */	lwz r3, 0(r7)
/* 8034074C 0033D32C  54 80 30 32 */	slwi r0, r4, 6
/* 80340750 0033D330  54 63 06 B0 */	rlwinm r3, r3, 0, 0x1a, 0x18
/* 80340754 0033D334  7C 60 03 78 */	or r0, r3, r0
/* 80340758 0033D338  90 07 00 00 */	stw r0, 0(r7)
lbl_8034075C:
/* 8034075C 0033D33C  38 00 00 61 */	li r0, 0x61
/* 80340760 0033D340  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340764 0033D344  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340768 0033D348  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8034076C 0033D34C  38 00 00 00 */	li r0, 0
/* 80340770 0033D350  80 87 00 00 */	lwz r4, 0(r7)
/* 80340774 0033D354  90 85 80 00 */	stw r4, -0x8000(r5)
/* 80340778 0033D358  B0 03 00 02 */	sth r0, 2(r3)
/* 8034077C 0033D35C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340780 0033D360  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80340784 0033D364  60 00 00 01 */	ori r0, r0, 1
/* 80340788 0033D368  90 03 04 F0 */	stw r0, 0x4f0(r3)
/* 8034078C 0033D36C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void GXSetNumTevStages(u8 arg0)
{
    u32 temp = (arg0 - 1) << 10;
    __GXContexts.main->x204 = (__GXContexts.main->x204 & ~0x3C00) | temp;
    __GXContexts.main->x4F0_flags |= (1 << 2);
}
