#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "__gx.h"

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color)
{
    u32 fogclr;
    u32 fog0;
    u32 fog1;
    u32 fog2;
    u32 fog3;
    f32 A;
    f32 B;
    f32 B_mant;
    f32 C;
    f32 a;
    f32 c;
    u32 B_expn;
    u32 b_m;
    u32 b_s;
    u32 a_hex;
    u32 c_hex;

    CHECK_GXBEGIN(0x6E, "GXSetFog");

    ASSERTMSGLINE(0x70, farz >= 0.0f, "GXSetFog: The farz should be positive value");
    ASSERTMSGLINE(0x71, farz >= nearz, "GXSetFog: The farz should be larger than nearz");

    if (farz == nearz || endz == startz) {
        A = 0.0f;
        B = 0.5f;
        C = 0.0f;
    } else {
        A = (farz * nearz) / ((farz - nearz) * (endz - startz));
        B = farz / (farz - nearz);
        C = startz / (endz - startz);
    }

    B_mant = B;
    B_expn = 0;
    while (B_mant > 1.0) {
        B_mant *= 0.5f;
        B_expn++;
    }
    while (B_mant > 0.0f && B_mant < 0.5) {
        B_mant *= 2.0f;
        B_expn--;
    }

    a = A / (f32) (1 << (B_expn + 1));
    b_m = 8.388638e6f * B_mant;
    b_s = B_expn + 1;
    c = C;

    fog1 = 0;
    SET_REG_FIELD(0x94, fog1, 24, 0, b_m);
    SET_REG_FIELD(0x95, fog1, 8, 24, 0xEF);

    fog2 = 0;
    SET_REG_FIELD(0x98, fog2, 5, 0, b_s);
    SET_REG_FIELD(0x99, fog2, 8, 24, 0xF0);

    a_hex = *(u32 *)&a;
    c_hex = *(u32 *)&c;

    fog0 = 0;
    SET_REG_FIELD(0xA0, fog0, 11, 0, (a_hex >> 12) & 0x7FF);
    SET_REG_FIELD(0xA1, fog0, 8, 11, (a_hex >> 23) & 0xFF);
    SET_REG_FIELD(0xA2, fog0, 1, 19, (a_hex >> 31));
    SET_REG_FIELD(0xA3, fog0, 8, 24, 0xEE);

    fog3 = 0;
    SET_REG_FIELD(0xA6, fog3, 11, 0, (c_hex >> 12) & 0x7FF);
    SET_REG_FIELD(0xA7, fog3, 8, 11, (c_hex >> 23) & 0xFF);
    SET_REG_FIELD(0xA8, fog3, 1, 19, (c_hex >> 31));
    SET_REG_FIELD(0xA9, fog3, 1, 20, 0);
    SET_REG_FIELD(0xAA, fog3, 3, 21, type);
    SET_REG_FIELD(0xAB, fog3, 8, 24, 0xF1);

    fogclr = 0;
    SET_REG_FIELD(0xAE, fogclr, 8, 0, color.b);
    SET_REG_FIELD(0xAF, fogclr, 8, 8, color.g);
    SET_REG_FIELD(0xB0, fogclr, 8, 16, color.r);
    SET_REG_FIELD(0xB1, fogclr, 8, 24, 0xF2);

    GX_WRITE_RAS_REG(fog0);
    GX_WRITE_RAS_REG(fog1);
    GX_WRITE_RAS_REG(fog2);
    GX_WRITE_RAS_REG(fog3);
    GX_WRITE_RAS_REG(fogclr);
    gx->bpSent = 1;
}

void GXInitFogAdjTable(GXFogAdjTable *table, u16 width, f32 projmtx[4][4])
{
    f32 xi;
    f32 iw;
    f32 rangeVal;
    f32 nearZ;
    f32 sideX;
    u32 i;

    CHECK_GXBEGIN(0xCE, "GXInitFogAdjTable");
    ASSERTMSGLINE(0xCF, table != NULL, "GXInitFogAdjTable: table pointer is null");
    ASSERTMSGLINE(0xD0, width <= 640, "GXInitFogAdjTable: invalid width value");

    if (0.0 == projmtx[3][3]) {
        nearZ = projmtx[2][3] / (projmtx[2][2] - 1.0f);
        sideX = (nearZ * (1.0f + projmtx[0][2])) / projmtx[0][0];
    } else {
        nearZ = (1.0f + projmtx[2][3]) / projmtx[2][2];
        sideX = -(projmtx[0][3] - 1.0f) / projmtx[0][0];
    }

    iw = 2.0f / width;
    for (i = 0; i < 10; i++) {
        xi = (i + 1) << 5;
        xi *= iw;
        xi *= sideX;
        rangeVal = sqrtf(1.0f + ((xi * xi) / (nearZ * nearZ)));
        table->r[i] = (u32)(256.0f * rangeVal) & 0xFFF;
    }
}

void GXSetFogRangeAdj(GXBool enable, u16 center, GXFogAdjTable *table)
{
    u32 i;
    u32 range_adj;
    u32 range_c;

    CHECK_GXBEGIN(0x106, "GXSetFogRangeAdj");

    if (enable) {
        ASSERTMSGLINE(0x109, table != NULL, "GXSetFogRangeAdj: table pointer is null");
        for (i = 0; i < 10; i += 2) {
            range_adj = 0;
            SET_REG_FIELD(0x10D, range_adj, 12, 0, table->r[i]);
            SET_REG_FIELD(0x10E, range_adj, 12, 12, table->r[i + 1]);
            SET_REG_FIELD(0x10F, range_adj, 8, 24, (i >> 1) + 0xE9);
            GX_WRITE_RAS_REG(range_adj);
        }
    }
    range_c = 0;
    SET_REG_FIELD(0x115, range_c, 10, 0, center + 340);
    SET_REG_FIELD(0x116, range_c, 1, 10, enable);
    SET_REG_FIELD(0x117, range_c, 8, 24, 0xE8);
    GX_WRITE_RAS_REG(range_c);
    gx->bpSent = 1;
}

void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op)
{
    CHECK_GXBEGIN(0x12F, "GXSetBlendMode");

    SET_REG_FIELD(0x135, gx->cmode0, 1, 0, (type == GX_BM_BLEND || type == GX_BM_SUBTRACT));
    SET_REG_FIELD(0x136, gx->cmode0, 1, 11, (type == GX_BM_SUBTRACT));
    SET_REG_FIELD(0x138, gx->cmode0, 1, 1, (type == GX_BM_LOGIC));
    SET_REG_FIELD(0x139, gx->cmode0, 4, 12, op);
    SET_REG_FIELD(0x13A, gx->cmode0, 3, 8, src_factor);
    SET_REG_FIELD(0x13B, gx->cmode0, 3, 5, dst_factor);
    SET_REG_FIELD(0x13C, gx->cmode0, 8, 24, 0x41);
    GX_WRITE_RAS_REG(gx->cmode0);
    gx->bpSent = 1;
}

void GXSetColorUpdate(GXBool update_enable)
{
    CHECK_GXBEGIN(0x14F, "GXSetColorUpdate");
    SET_REG_FIELD(0x150, gx->cmode0, 1, 3, update_enable);
    GX_WRITE_RAS_REG(gx->cmode0);
    gx->bpSent = 1;
}

void GXSetAlphaUpdate(GXBool update_enable)
{
    CHECK_GXBEGIN(0x158, "GXSetAlphaUpdate");
    SET_REG_FIELD(0x159, gx->cmode0, 1, 4, update_enable);
    GX_WRITE_RAS_REG(gx->cmode0);
    gx->bpSent = 1;
}

void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable)
{
    CHECK_GXBEGIN(0x170, "GXSetZMode");
    SET_REG_FIELD(0x171, gx->zmode, 1, 0, compare_enable);
    SET_REG_FIELD(0x172, gx->zmode, 3, 1, func);
    SET_REG_FIELD(0x173, gx->zmode, 1, 4, update_enable);
    GX_WRITE_RAS_REG(gx->zmode);
    gx->bpSent = 1;
}

void GXSetZCompLoc(GXBool before_tex)
{
    CHECK_GXBEGIN(0x17C, "GXSetZCompLoc");
    SET_REG_FIELD(0x17D, gx->peCtrl, 1, 6, before_tex);
    GX_WRITE_RAS_REG(gx->peCtrl);
    gx->bpSent = 1;
}

void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt)
{
    u32 oldPeCtrl;
    u8 aa;
    static u32 p2f[8] = { 0, 1, 2, 3, 4, 4, 4, 5 };

    CHECK_GXBEGIN(0x1A1, "GXSetPixelFmt");
    oldPeCtrl = gx->peCtrl;
    ASSERTMSGLINE(0x1A5, pix_fmt >= 0 && pix_fmt <= 7, "Invalid Pixel format");
    SET_REG_FIELD(0x1A7, gx->peCtrl, 3, 0, p2f[pix_fmt]);
    SET_REG_FIELD(0x1A8, gx->peCtrl, 3, 3, z_fmt);
    if (oldPeCtrl != gx->peCtrl) {
        GX_WRITE_RAS_REG(gx->peCtrl);
        if (pix_fmt == GX_PF_RGB565_Z16)
            aa = 1;
        else
            aa = 0;
        SET_REG_FIELD(0x1B1, gx->genMode, 1, 9, aa);
        gx->dirtyState |= 4;
    }
    if (p2f[pix_fmt] == 4) {
        SET_REG_FIELD(0x1B8, gx->cmode1, 2, 9, (pix_fmt - 4) & 0x3);
        SET_REG_FIELD(0x1B9, gx->cmode1, 8, 24, 0x42);
        GX_WRITE_RAS_REG(gx->cmode1);
    }
    gx->bpSent = 1;
}

void GXSetDither(GXBool dither)
{
    CHECK_GXBEGIN(0x1CD, "GXSetDither");
    SET_REG_FIELD(0x1CE, gx->cmode0, 1, 2, dither);
    GX_WRITE_RAS_REG(gx->cmode0);
    gx->bpSent = 1;
}

void GXSetDstAlpha(GXBool enable, u8 alpha)
{
    CHECK_GXBEGIN(0x1E1, "GXSetDstAlpha");
    SET_REG_FIELD(0x1E2, gx->cmode1, 8, 0, alpha);
    SET_REG_FIELD(0x1E3, gx->cmode1, 1, 8, enable);
    GX_WRITE_RAS_REG(gx->cmode1);
    gx->bpSent = 1;
}

void GXSetFieldMask(GXBool odd_mask, GXBool even_mask)
{
    u32 reg;

    CHECK_GXBEGIN(0x1F9, "GXSetFieldMask");
    reg = 0;
    SET_REG_FIELD(0x1FB, reg, 1, 0, even_mask);
    SET_REG_FIELD(0x1FC, reg, 1, 1, odd_mask);
    SET_REG_FIELD(0x1FD, reg, 8, 24, 0x44);
    GX_WRITE_RAS_REG(reg);
    gx->bpSent = 1;
}

void GXSetFieldMode(GXBool field_mode, GXBool half_aspect_ratio)
{
    u32 reg;

    CHECK_GXBEGIN(0x216, "GXSetFieldMode");
    SET_REG_FIELD(0x21A, gx->lpSize, 1, 22, half_aspect_ratio);
    GX_WRITE_RAS_REG(gx->lpSize);
    __GXFlushTextureState();
    reg = field_mode | 0x68000000;
    GX_WRITE_RAS_REG(reg);
    __GXFlushTextureState();
}
