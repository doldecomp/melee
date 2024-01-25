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

#ifdef MUST_MATCH
#pragma push
asm void GXSetTevColorS10(s32, GXColorS10)
{ // clang-format off
    nofralloc
/* 80340260 0033CE40  A8 04 00 06 */	lha r0, 6(r4)
/* 80340264 0033CE44  54 69 08 3C */	slwi r9, r3, 1
/* 80340268 0033CE48  A8 A4 00 00 */	lha r5, 0(r4)
/* 8034026C 0033CE4C  39 09 00 E0 */	addi r8, r9, 0xe0
/* 80340270 0033CE50  54 0A 62 66 */	rlwinm r10, r0, 0xc, 9, 0x13
/* 80340274 0033CE54  50 AA 05 7E */	rlwimi r10, r5, 0, 0x15, 0x1f
/* 80340278 0033CE58  A8 E4 00 04 */	lha r7, 4(r4)
/* 8034027C 0033CE5C  A8 C4 00 02 */	lha r6, 2(r4)
/* 80340280 0033CE60  55 08 C0 0E */	slwi r8, r8, 0x18
/* 80340284 0033CE64  38 A0 00 61 */	li r5, 0x61
/* 80340288 0033CE68  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8034028C 0033CE6C  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80340290 0033CE70  98 A4 80 00 */	stb r5, 0xCC008000@l(r4)
/* 80340294 0033CE74  51 48 02 7E */	rlwimi r8, r10, 0, 9, 0x1f
/* 80340298 0033CE78  38 09 00 E1 */	addi r0, r9, 0xe1
/* 8034029C 0033CE7C  91 04 80 00 */	stw r8, -0x8000(r4)
/* 803402A0 0033CE80  54 C8 62 66 */	rlwinm r8, r6, 0xc, 9, 0x13
/* 803402A4 0033CE84  54 06 C0 0E */	slwi r6, r0, 0x18
/* 803402A8 0033CE88  50 E8 05 7E */	rlwimi r8, r7, 0, 0x15, 0x1f
/* 803402AC 0033CE8C  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 803402B0 0033CE90  51 06 02 7E */	rlwimi r6, r8, 0, 9, 0x1f
/* 803402B4 0033CE94  90 C4 80 00 */	stw r6, -0x8000(r4)
/* 803402B8 0033CE98  38 00 00 00 */	li r0, 0
/* 803402BC 0033CE9C  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 803402C0 0033CEA0  90 C4 80 00 */	stw r6, -0x8000(r4)
/* 803402C4 0033CEA4  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 803402C8 0033CEA8  90 C4 80 00 */	stw r6, -0x8000(r4)
/* 803402CC 0033CEAC  B0 03 00 02 */	sth r0, 2(r3)
/* 803402D0 0033CEB0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
asm void GXSetTevKColor(GXTevKColorID id, GXColor color)
{ // clang-format off
    nofralloc
/* 803402D4 0033CEB4  88 04 00 03 */	lbz r0, 3(r4)
/* 803402D8 0033CEB8  54 65 08 3C */	slwi r5, r3, 1
/* 803402DC 0033CEBC  88 C4 00 00 */	lbz r6, 0(r4)
/* 803402E0 0033CEC0  38 E5 00 E0 */	addi r7, r5, 0xe0
/* 803402E4 0033CEC4  54 00 60 26 */	slwi r0, r0, 0xc
/* 803402E8 0033CEC8  50 C0 06 3E */	rlwimi r0, r6, 0, 0x18, 0x1f
/* 803402EC 0033CECC  88 C4 00 01 */	lbz r6, 1(r4)
/* 803402F0 0033CED0  89 24 00 02 */	lbz r9, 2(r4)
/* 803402F4 0033CED4  54 00 03 0E */	rlwinm r0, r0, 0, 0xc, 7
/* 803402F8 0033CED8  64 08 00 80 */	oris r8, r0, 0x80
/* 803402FC 0033CEDC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340300 0033CEE0  54 E7 C0 0E */	slwi r7, r7, 0x18
/* 80340304 0033CEE4  38 00 00 61 */	li r0, 0x61
/* 80340308 0033CEE8  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8034030C 0033CEEC  54 C6 60 26 */	slwi r6, r6, 0xc
/* 80340310 0033CEF0  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80340314 0033CEF4  51 07 02 3E */	rlwimi r7, r8, 0, 8, 0x1f
/* 80340318 0033CEF8  90 E4 80 00 */	stw r7, -0x8000(r4)
/* 8034031C 0033CEFC  51 26 06 3E */	rlwimi r6, r9, 0, 0x18, 0x1f
/* 80340320 0033CF00  38 A5 00 E1 */	addi r5, r5, 0xe1
/* 80340324 0033CF04  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80340328 0033CF08  54 C0 03 0E */	rlwinm r0, r6, 0, 0xc, 7
/* 8034032C 0033CF0C  64 06 00 80 */	oris r6, r0, 0x80
/* 80340330 0033CF10  54 A0 C0 0E */	slwi r0, r5, 0x18
/* 80340334 0033CF14  50 C0 02 3E */	rlwimi r0, r6, 0, 8, 0x1f
/* 80340338 0033CF18  90 04 80 00 */	stw r0, -0x8000(r4)
/* 8034033C 0033CF1C  38 00 00 00 */	li r0, 0
/* 80340340 0033CF20  B0 03 00 02 */	sth r0, 2(r3)
/* 80340344 0033CF24  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
asm void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel)
{ // clang-format off
    nofralloc
/* 80340348 0033CF28  7C 65 0E 70 */	srawi r5, r3, 1
/* 8034034C 0033CF2C  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 80340350 0033CF30  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 80340354 0033CF34  54 A3 10 3A */	slwi r3, r5, 2
/* 80340358 0033CF38  38 E3 01 B0 */	addi r7, r3, 0x1b0
/* 8034035C 0033CF3C  7C E6 3A 14 */	add r7, r6, r7
/* 80340360 0033CF40  41 82 00 1C */	beq lbl_8034037C
/* 80340364 0033CF44  80 67 00 00 */	lwz r3, 0(r7)
/* 80340368 0033CF48  54 80 70 22 */	slwi r0, r4, 0xe
/* 8034036C 0033CF4C  54 63 04 98 */	rlwinm r3, r3, 0, 0x12, 0xc
/* 80340370 0033CF50  7C 60 03 78 */	or r0, r3, r0
/* 80340374 0033CF54  90 07 00 00 */	stw r0, 0(r7)
/* 80340378 0033CF58  48 00 00 18 */	b lbl_80340390
lbl_8034037C:
/* 8034037C 0033CF5C  80 67 00 00 */	lwz r3, 0(r7)
/* 80340380 0033CF60  54 80 20 36 */	slwi r0, r4, 4
/* 80340384 0033CF64  54 63 07 2C */	rlwinm r3, r3, 0, 0x1c, 0x16
/* 80340388 0033CF68  7C 60 03 78 */	or r0, r3, r0
/* 8034038C 0033CF6C  90 07 00 00 */	stw r0, 0(r7)
lbl_80340390:
/* 80340390 0033CF70  38 00 00 61 */	li r0, 0x61
/* 80340394 0033CF74  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340398 0033CF78  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8034039C 0033CF7C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 803403A0 0033CF80  38 00 00 00 */	li r0, 0
/* 803403A4 0033CF84  80 87 00 00 */	lwz r4, 0(r7)
/* 803403A8 0033CF88  90 85 80 00 */	stw r4, -0x8000(r5)
/* 803403AC 0033CF8C  B0 03 00 02 */	sth r0, 2(r3)
/* 803403B0 0033CF90  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
asm void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel)
{ // clang-format off
    nofralloc
/* 803403B4 0033CF94  7C 65 0E 70 */	srawi r5, r3, 1
/* 803403B8 0033CF98  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 803403BC 0033CF9C  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 803403C0 0033CFA0  54 A3 10 3A */	slwi r3, r5, 2
/* 803403C4 0033CFA4  38 E3 01 B0 */	addi r7, r3, 0x1b0
/* 803403C8 0033CFA8  7C E6 3A 14 */	add r7, r6, r7
/* 803403CC 0033CFAC  41 82 00 1C */	beq lbl_803403E8
/* 803403D0 0033CFB0  80 67 00 00 */	lwz r3, 0(r7)
/* 803403D4 0033CFB4  54 80 98 18 */	slwi r0, r4, 0x13
/* 803403D8 0033CFB8  54 63 03 4E */	rlwinm r3, r3, 0, 0xd, 7
/* 803403DC 0033CFBC  7C 60 03 78 */	or r0, r3, r0
/* 803403E0 0033CFC0  90 07 00 00 */	stw r0, 0(r7)
/* 803403E4 0033CFC4  48 00 00 18 */	b lbl_803403FC
lbl_803403E8:
/* 803403E8 0033CFC8  80 67 00 00 */	lwz r3, 0(r7)
/* 803403EC 0033CFCC  54 80 48 2C */	slwi r0, r4, 9
/* 803403F0 0033CFD0  54 63 05 E2 */	rlwinm r3, r3, 0, 0x17, 0x11
/* 803403F4 0033CFD4  7C 60 03 78 */	or r0, r3, r0
/* 803403F8 0033CFD8  90 07 00 00 */	stw r0, 0(r7)
lbl_803403FC:
/* 803403FC 0033CFDC  38 00 00 61 */	li r0, 0x61
/* 80340400 0033CFE0  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340404 0033CFE4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340408 0033CFE8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8034040C 0033CFEC  38 00 00 00 */	li r0, 0
/* 80340410 0033CFF0  80 87 00 00 */	lwz r4, 0(r7)
/* 80340414 0033CFF4  90 85 80 00 */	stw r4, -0x8000(r5)
/* 80340418 0033CFF8  B0 03 00 02 */	sth r0, 2(r3)
/* 8034041C 0033CFFC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

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

#ifdef MUST_MATCH
#pragma push
asm void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias)
{ // clang-format off
    nofralloc
/* 8034056C 0033D14C  2C 04 00 13 */	cmpwi r4, 0x13
/* 80340570 0033D150  54 A0 02 3E */	clrlwi r0, r5, 8
/* 80340574 0033D154  64 07 F4 00 */	oris r7, r0, 0xf400
/* 80340578 0033D158  41 82 00 28 */	beq lbl_803405A0
/* 8034057C 0033D15C  40 80 00 10 */	bge lbl_8034058C
/* 80340580 0033D160  2C 04 00 11 */	cmpwi r4, 0x11
/* 80340584 0033D164  41 82 00 14 */	beq lbl_80340598
/* 80340588 0033D168  48 00 00 28 */	b lbl_803405B0
lbl_8034058C:
/* 8034058C 0033D16C  2C 04 00 16 */	cmpwi r4, 0x16
/* 80340590 0033D170  41 82 00 18 */	beq lbl_803405A8
/* 80340594 0033D174  48 00 00 1C */	b lbl_803405B0
lbl_80340598:
/* 80340598 0033D178  38 C0 00 00 */	li r6, 0
/* 8034059C 0033D17C  48 00 00 18 */	b lbl_803405B4
lbl_803405A0:
/* 803405A0 0033D180  38 C0 00 01 */	li r6, 1
/* 803405A4 0033D184  48 00 00 10 */	b lbl_803405B4
lbl_803405A8:
/* 803405A8 0033D188  38 C0 00 02 */	li r6, 2
/* 803405AC 0033D18C  48 00 00 08 */	b lbl_803405B4
lbl_803405B0:
/* 803405B0 0033D190  38 C0 00 02 */	li r6, 2
lbl_803405B4:
/* 803405B4 0033D194  38 00 00 61 */	li r0, 0x61
/* 803405B8 0033D198  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803405BC 0033D19C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 803405C0 0033D1A0  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 803405C4 0033D1A4  54 C6 07 B6 */	rlwinm r6, r6, 0, 0x1e, 0x1b
/* 803405C8 0033D1A8  54 63 10 3A */	slwi r3, r3, 2
/* 803405CC 0033D1AC  90 E5 80 00 */	stw r7, -0x8000(r5)
/* 803405D0 0033D1B0  7C C3 1B 78 */	or r3, r6, r3
/* 803405D4 0033D1B4  54 63 02 3E */	clrlwi r3, r3, 8
/* 803405D8 0033D1B8  98 05 80 00 */	stb r0, -0x8000(r5)
/* 803405DC 0033D1BC  64 63 F5 00 */	oris r3, r3, 0xf500
/* 803405E0 0033D1C0  38 00 00 00 */	li r0, 0
/* 803405E4 0033D1C4  90 65 80 00 */	stw r3, -0x8000(r5)
/* 803405E8 0033D1C8  B0 04 00 02 */	sth r0, 2(r4)
/* 803405EC 0033D1CC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MUST_MATCH
static u32 GXTev_804014E0[] = { 0, 1, 0, 1, 0, 1, 7, 5, 6, 0 };
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
