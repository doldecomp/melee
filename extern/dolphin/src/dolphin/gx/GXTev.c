#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "__gx.h"

void GXSetTevOp(GXTevStageID id, GXTevMode mode)
{
    GXTevColorArg carg = GX_CC_RASC;
    GXTevAlphaArg aarg = GX_CA_RASA;

    CHECK_GXBEGIN(0x72, "GXSetTevOp");

    if (id != GX_TEVSTAGE0) {
        carg = GX_CC_CPREV;
        aarg = GX_CA_APREV;
    }

    switch (mode) {
    case GX_MODULATE:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_TEXC, carg, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_TEXA, aarg, GX_CA_ZERO);
        break;
    case GX_DECAL:
        GXSetTevColorIn(id, carg, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, aarg);
        break;
    case GX_BLEND:
        GXSetTevColorIn(id, carg, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_TEXA, aarg, GX_CA_ZERO);
        break;
    case GX_REPLACE:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        break;
    case GX_PASSCLR:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, carg);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, aarg);
        break;
    default:
        ASSERTMSGLINE(0x8F, 0, "GXSetTevOp: Invalid Tev Mode");
    }
    GXSetTevColorOp(id, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(id, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}


void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0xE5, "GXSetTevColorIn");
    ASSERTMSGLINE(0xE6, stage < 16, "GXSetTevColor: Invalid Tev Stage Index");
    ASSERTMSGLINE(0xE7, a <= 15, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0xE8, b <= 15, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0xE9, c <= 15, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0xEA, d <= 15, "GXSetTev*In: A/B/C/D argument out of range");

    pTevReg = &gx->tevc[stage];
    SET_REG_FIELD(0xED, *pTevReg, 4, 12, a);
    SET_REG_FIELD(0xEE, *pTevReg, 4,  8, b);
    SET_REG_FIELD(0xEF, *pTevReg, 4,  4, c);
    SET_REG_FIELD(0xF0, *pTevReg, 4,  0, d);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSent = 1;
}

void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x108, "GXSetTevAlphaIn");
    ASSERTMSGLINE(0x109, stage < 16, "GXSetTevAlpha: Invalid Tev Stage Index");
    ASSERTMSGLINE(0x10A, a <= 7, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0x10B, b <= 7, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0x10C, c <= 7, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0x10D, d <= 7, "GXSetTev*In: A/B/C/D argument out of range");

    pTevReg = &gx->teva[stage];
    SET_REG_FIELD(0x110, *pTevReg, 3, 13, a);
    SET_REG_FIELD(0x111, *pTevReg, 3, 10, b);
    SET_REG_FIELD(0x112, *pTevReg, 3,  7, c);
    SET_REG_FIELD(0x113, *pTevReg, 3,  4, d);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSent = 1;
}

void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x12E, "GXSetTevColorOp");
    ASSERTMSGLINE(0x12F, stage < 16, "GXSetTevColor: Invalid Tev Stage Index");

    pTevReg = &gx->tevc[stage];
    SET_REG_FIELD(0x137, *pTevReg, 1, 18, op & 1);
    if (op <= 1) {
        SET_REG_FIELD(0x139, *pTevReg, 2, 20, scale);
        SET_REG_FIELD(0x13A, *pTevReg, 2, 16, bias);
    } else {
        SET_REG_FIELD(0x13C, *pTevReg, 2, 20, (op >> 1) & 3);
        SET_REG_FIELD(0x13D, *pTevReg, 2, 16, 3);
    }
    SET_REG_FIELD(0x140, *pTevReg, 1, 19, clamp & 0xFF);
    SET_REG_FIELD(0x141, *pTevReg, 2, 22, out_reg);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSent = 1;
}

void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x15A, "GXSetTevAlphaOp");
    ASSERTMSGLINE(0x15B, stage < 16, "GXSetTevAlpha: Invalid Tev Stage Index");

    pTevReg = &gx->teva[stage];
    SET_REG_FIELD(0x163, *pTevReg, 1, 18, op & 1);
    if (op <= 1) {
        SET_REG_FIELD(0x165, *pTevReg, 2, 20, scale);
        SET_REG_FIELD(0x166, *pTevReg, 2, 16, bias);
    } else {
        SET_REG_FIELD(0x168, *pTevReg, 2, 20, (op >> 1) & 3);
        SET_REG_FIELD(0x169, *pTevReg, 2, 16, 3);
    }
    SET_REG_FIELD(0x16C, *pTevReg, 1, 19, clamp & 0xFF);
    SET_REG_FIELD(0x16D, *pTevReg, 2, 22, out_reg);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSent = 1;
}

void GXSetTevColor(GXTevRegID id, GXColor color)
{
    u32 regRA;
    u32 regBG;

    CHECK_GXBEGIN(0x182, "GXSetTevColor");

    regRA = 0;
    SET_REG_FIELD(0x185, regRA, 11,  0, color.r);
    SET_REG_FIELD(0x186, regRA, 11, 12, color.a);
    SET_REG_FIELD(0x187, regRA,  8, 24, 224 + id * 2);

    regBG = 0;
    SET_REG_FIELD(0x18A, regBG, 11,  0, color.b);
    SET_REG_FIELD(0x18B, regBG, 11, 12, color.g);
    SET_REG_FIELD(0x18C, regBG,  8, 24, 225 + id * 2);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    gx->bpSent = 1;
}

void GXSetTevColorS10(GXTevRegID id, GXColorS10 color)
{
    u32 regRA;
    u32 regBG;

    ASSERTMSGLINE(0x1A7, color.r >= -1024 && color.r < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");
    ASSERTMSGLINE(0x1A8, color.g >= -1024 && color.g < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");
    ASSERTMSGLINE(0x1A9, color.b >= -1024 && color.b < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");
    ASSERTMSGLINE(0x1AA, color.a >= -1024 && color.a < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");

    CHECK_GXBEGIN(0x1AC, "GXSetTevColorS10");

    regRA = 0;
    SET_REG_FIELD(0x1AF, regRA, 11,  0, color.r & 0x7FF);
    SET_REG_FIELD(0x1B0, regRA, 11, 12, color.a & 0x7FF);
    SET_REG_FIELD(0x1B1, regRA,  8, 24, 224 + id * 2);

    regBG = 0;
    SET_REG_FIELD(0x1B4, regBG, 11,  0, color.b & 0x7FF);
    SET_REG_FIELD(0x1B5, regBG, 11, 12, color.g & 0x7FF);
    SET_REG_FIELD(0x1B6, regBG,  8, 24, 225 + id * 2);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    gx->bpSent = 1;
}

void GXSetTevKColor(GXTevKColorID id, GXColor color)
{
    u32 regRA;
    u32 regBG;

    CHECK_GXBEGIN(0x1DD, "GXSetTevKColor");

    regRA = 0;
    SET_REG_FIELD(0x1E0, regRA, 8,  0, color.r);
    SET_REG_FIELD(0x1E1, regRA, 8, 12, color.a);
    SET_REG_FIELD(0x1E2, regRA, 4, 20, 8);
    SET_REG_FIELD(0x1E3, regRA, 8, 24, 224 + id * 2);

    regBG = 0;
    SET_REG_FIELD(0x1E6, regBG, 8,  0, color.b);
    SET_REG_FIELD(0x1E7, regBG, 8, 12, color.g);
    SET_REG_FIELD(0x1E8, regBG, 4, 20, 8);
    SET_REG_FIELD(0x1E9, regBG, 8, 24, 225 + id * 2);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);
    gx->bpSent = 1;
}

void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel)
{
    u32 *Kreg;

    CHECK_GXBEGIN(0x204, "GXSetTevKColorSel");
    ASSERTMSGLINE(0x205, stage < 16, "GXSetTevKColor*: Invalid Tev Stage Index");

    Kreg = &gx->tevKsel[stage >> 1];
    if (stage & 1) {
        SET_REG_FIELD(0x20A, *Kreg, 5, 14, sel);
    } else {
        SET_REG_FIELD(0x20C, *Kreg, 5, 4, sel);
    }

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSent = 1;
}

void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel)
{
    u32 *Kreg;

    CHECK_GXBEGIN(0x225, "GXSetTevKAlphaSel");
    ASSERTMSGLINE(0x226, stage < 16, "GXSetTevKColor*: Invalid Tev Stage Index");

    Kreg = &gx->tevKsel[stage >> 1];
    if (stage & 1) {
        SET_REG_FIELD(0x22B, *Kreg, 5, 19, sel);
    } else {
        SET_REG_FIELD(0x22D, *Kreg, 5, 9, sel);
    }

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSent = 1;
}

void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x24A, "GXSetTevSwapMode");
    ASSERTMSGLINE(0x24B, stage < 16, "GXSetTevSwapMode: Invalid Tev Stage Index");

    pTevReg = &gx->teva[stage];
    SET_REG_FIELD(0x24E, *pTevReg, 2, 0, ras_sel);
    SET_REG_FIELD(0x24F, *pTevReg, 2, 2, tex_sel);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSent = 1;
}

void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red, GXTevColorChan green, GXTevColorChan blue, GXTevColorChan alpha)
{
    u32 *Kreg;
#if !DEBUG
    // not a real variable, but needed to match release
    int index = table * 2;
#endif

    CHECK_GXBEGIN(0x26E, "GXSetTevSwapModeTable");
    ASSERTMSGLINE(0x26F, table < 4, "GXSetTevSwapModeTable: Invalid Swap Selection Index");

#if DEBUG
    Kreg = &gx->tevKsel[table * 2];
#else
    Kreg = &gx->tevKsel[index];
#endif
    SET_REG_FIELD(0x272, *Kreg, 2, 0, red);
    SET_REG_FIELD(0x273, *Kreg, 2, 2, green);

    GX_WRITE_RAS_REG(*Kreg);

    Kreg = &gx->tevKsel[table * 2 + 1];
    SET_REG_FIELD(0x277, *Kreg, 2, 0, blue);
    SET_REG_FIELD(0x278, *Kreg, 2, 2, alpha);

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSent = 1;
}

void GXSetTevClampMode(void)
{
    ASSERTMSGLINE(0x290, 0, "GXSetTevClampMode: not available on this hardware");
}

void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1)
{
    u32 reg = 0;

    CHECK_GXBEGIN(0x2B2, "GXSetAlphaCompare");

    SET_REG_FIELD(0x2B4, reg, 8, 0, ref0);
    SET_REG_FIELD(0x2B5, reg, 8, 8, ref1);
    SET_REG_FIELD(0x2B6, reg, 3, 16, comp0);
    SET_REG_FIELD(0x2B7, reg, 3, 19, comp1);
    SET_REG_FIELD(0x2B8, reg, 2, 22, op);
    SET_REG_FIELD(0x2B9, reg, 8, 24, 0xF3);

    GX_WRITE_RAS_REG(reg);
    gx->bpSent = 1;
}

void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias)
{
    u32 zenv0;
    u32 zenv1;
    u32 type;

    CHECK_GXBEGIN(0x2D1, "GXSetZTexture");

    zenv0 = 0;
    SET_REG_FIELD(0x2D4, zenv0, 24, 0, bias);
    SET_REG_FIELD(0x2D5, zenv0, 8, 24, 0xF4);

    zenv1 = 0;
    switch (fmt)
    {
    case GX_TF_Z8:
        type = 0;
        break;
    case GX_TF_Z16:
        type = 1;
        break;
    case GX_TF_Z24X8:
        type = 2;
        break;
    default:
        ASSERTMSGLINE(0x2DD, 0, "GXSetZTexture: Invalid z-texture format");
        type = 2;
        break;
    }
    SET_REG_FIELD(0x2E0, zenv1, 2, 0, type);
    SET_REG_FIELD(0x2E1, zenv1, 2, 2, op);
    SET_REG_FIELD(0x2E2, zenv1, 8, 24, 0xF5);

    GX_WRITE_RAS_REG(zenv0);
    GX_WRITE_RAS_REG(zenv1);
    gx->bpSent = 1;
}

void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color)
{
    u32 *ptref;
    u32 tmap;
    u32 tcoord;
    static int c2r[] = { 0, 1, 0, 1, 0, 1, 7, 5, 6 };

    CHECK_GXBEGIN(0x307, "GXSetTevOrder");
    ASSERTMSGLINE(0x308, stage < 16, "GXSetTevColor: Invalid Tev Stage Index");

    ptref = &gx->tref[stage / 2];
    gx->texmapId[stage] = map;

    tmap = map & ~0x100;
    tmap = (tmap >= GX_MAX_TEXMAP) ? GX_TEXMAP0 : tmap;
    tcoord = (coord >= GX_MAX_TEXCOORD) ? GX_TEXCOORD0 : coord;

    if (stage & 1) {
        SET_REG_FIELD(0x314, *ptref, 3, 12, tmap);
        SET_REG_FIELD(0x315, *ptref, 3, 15, tcoord);
        SET_REG_FIELD(0x317, *ptref, 3, 19, (color == GX_COLOR_NULL) ? 7 : c2r[color]);
        SET_REG_FIELD(0x319, *ptref, 1, 18, (map != GX_TEXMAP_NULL && !(map & 0x100)));
    } else {
        SET_REG_FIELD(0x31C, *ptref, 3, 0, tmap);
        SET_REG_FIELD(0x31D, *ptref, 3, 3, tcoord);
        SET_REG_FIELD(0x31F, *ptref, 3, 7, (color == GX_COLOR_NULL) ? 7 : c2r[color]);
        SET_REG_FIELD(0x321, *ptref, 1, 6, (map != GX_TEXMAP_NULL && !(map & 0x100)));
    }

    GX_WRITE_RAS_REG(*ptref);
    gx->bpSent = 1;
    gx->dirtyState |= 1;
}

void GXSetNumTevStages(u8 nStages)
{
    CHECK_GXBEGIN(0x331, "GXSetNumTevStages");

    ASSERTMSGLINE(0x333, nStages != 0 && nStages <= 16, "GXSetNumTevStages: Exceed max number of tex stages");
    SET_REG_FIELD(0x334, gx->genMode, 4, 10, nStages - 1);
    gx->dirtyState |= 4;
}
