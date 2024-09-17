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

void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel,
                      GXTevSwapSel tex_sel)
{
    NOT_IMPLEMENTED;
}

void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red,
                           GXTevColorChan green, GXTevColorChan blue,
                           GXTevColorChan alpha)
{
    NOT_IMPLEMENTED;
}

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

void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map,
                   GXChannelID color)
{
    NOT_IMPLEMENTED;
}

void GXSetNumTevStages(u8 arg0)
{
    u32 temp = (arg0 - 1) << 10;
    __GXContexts.main->x204 = (__GXContexts.main->x204 & ~0x3C00) | temp;
    __GXContexts.main->x4F0_flags |= (1 << 2);
}
