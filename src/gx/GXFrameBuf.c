#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "__gx.h"

GXRenderModeObj GXNtsc240Ds = {
    1,
    640, 240, 240,
    40, 0,
    640, 480,
    0,
    0,
    0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240DsAa = {
    1, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240Int = {
    0, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc240IntAa = {
    0, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480IntDf = {
    0, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 }
};

GXRenderModeObj GXNtsc480Int = {
    0, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480IntAa = {
    0, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 }
};

GXRenderModeObj GXNtsc480Prog = {
    2, 640, 480, 480, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 }
};

GXRenderModeObj GXNtsc480ProgAa = {
    2, 640, 242, 480, 40, 0, 640, 480, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 }
};

GXRenderModeObj GXMpal240Ds = {9, 640, 240, 240, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240DsAa = {9, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240Int = {8, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240IntAa = {8, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal480IntDf = {8, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXMpal480Int = {8, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal480IntAa = {8, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXPal264Ds = {5, 640, 264, 264, 40, 23, 640, 528, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264DsAa = {5, 640, 264, 264, 40, 23, 640, 528, 0, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264Int = {4, 640, 264, 264, 40, 23, 640, 528, 0, 1, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264IntAa = {4, 640, 264, 264, 40, 23, 640, 528, 0, 1, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal528IntDf = {4, 640, 528, 528, 40, 23, 640, 528, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXPal528Int = {4, 640, 528, 528, 40, 23, 640, 528, 1, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal524IntAa = {4, 640, 264, 524, 40, 23, 640, 524, 1, 0, 1, { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXRmHW = {1, 320, 240, 240, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };

void GXAdjustForOverscan(GXRenderModeObj *rmin, GXRenderModeObj *rmout, u16 hor, u16 ver)
{
    unsigned short hor2 = hor * 2;
    unsigned short ver2 = ver * 2;
    unsigned long verf;

    if (rmin != rmout) {
        *rmout = *rmin;
    }

    rmout->fbWidth = rmin->fbWidth - hor2;
    verf = (ver2 * rmin->efbHeight) / (u32)rmin->xfbHeight;
    rmout->efbHeight = rmin->efbHeight - verf;
    if (rmin->xFBmode == VI_XFBMODE_SF && (rmin->viTVmode & 2) != 2) {
        rmout->xfbHeight = rmin->xfbHeight - ver;
    } else {
        rmout->xfbHeight = rmin->xfbHeight - ver2;
    }
    rmout->viWidth = rmin->viWidth - hor2;
    rmout->viHeight = rmin->viHeight - ver2;
    rmout->viXOrigin = rmin->viXOrigin + hor;
    rmout->viYOrigin = rmin->viYOrigin + ver;
}

void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    CHECK_GXBEGIN(0x3B9, "GXSetDispCopySrc");

    gx->cpDispSrc = 0;
    SET_REG_FIELD(0x3BC, gx->cpDispSrc, 10,  0, left);
    SET_REG_FIELD(0x3BD, gx->cpDispSrc, 10, 10, top);
    SET_REG_FIELD(0x3BE, gx->cpDispSrc,  8, 24, 0x49);

    gx->cpDispSize = 0;
    SET_REG_FIELD(0x3C1, gx->cpDispSize, 10,  0, wd - 1);
    SET_REG_FIELD(0x3C2, gx->cpDispSize, 10, 10, ht - 1);
    SET_REG_FIELD(0x3C3, gx->cpDispSize,  8, 24, 0x4A);
}


void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    CHECK_GXBEGIN(0x3D5, "GXSetTexCopySrc");

    gx->cpTexSrc = 0;
    SET_REG_FIELD(0x3D8, gx->cpTexSrc, 10,  0, left);
    SET_REG_FIELD(0x3D9, gx->cpTexSrc, 10, 10, top);
    SET_REG_FIELD(0x3DA, gx->cpTexSrc,  8, 24, 0x49);

    gx->cpTexSize = 0;
    SET_REG_FIELD(0x3DD, gx->cpTexSize, 10,  0, wd - 1);
    SET_REG_FIELD(0x3DE, gx->cpTexSize, 10, 10, ht - 1);
    SET_REG_FIELD(0x3DF, gx->cpTexSize,  8, 24, 0x4A);
}

void GXSetDispCopyDst(u16 wd, u16 ht)
{
    u16 stride;

    ASSERTMSGLINE(0x3F3, (wd & 0xF) == 0, "GXSetDispCopyDst: Width must be a multiple of 16");
    CHECK_GXBEGIN(0x3F4, "GXSetDispCopyDst");

    stride = (int)wd * 2;
    gx->cpDispStride = 0;
    SET_REG_FIELD(0x3FA, gx->cpDispStride, 10,  0, (stride >> 5) );
    SET_REG_FIELD(0x3FB, gx->cpDispStride,  8, 24, 0x4D);
}

void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap)
{
    u32 rowTiles;
    u32 colTiles;
    u32 cmpTiles;
    u32 peTexFmt;
    u32 peTexFmtH;

    CHECK_GXBEGIN(0x415, "GXSetTexCopyDst");

    gx->cpTexZ = 0;
    peTexFmt = fmt & 0xF;
    ASSERTMSGLINEV(0x434, peTexFmt < 13, "%s: invalid texture format", "GXSetTexCopyDst");

    if (fmt == GX_TF_Z16) {
        peTexFmt = 0xB;
    }
    switch (fmt) {
    case GX_TF_I4:
    case GX_TF_I8:
    case GX_TF_IA4:
    case GX_TF_IA8:
    case GX_CTF_YUVA8:
        SET_REG_FIELD(0, gx->cpTex, 2, 15, 3);
        break;
    default:
        SET_REG_FIELD(0, gx->cpTex, 2, 15, 2);
        break;
    }

    gx->cpTexZ = (fmt & _GX_TF_ZTF) == _GX_TF_ZTF;
    peTexFmtH = (peTexFmt >> 3) & 1;
    !peTexFmt;
    SET_REG_FIELD(0x44B, gx->cpTex, 1, 3, peTexFmtH);
    peTexFmt = peTexFmt & 7;
    __GetImageTileCount(fmt, wd, ht, &rowTiles, &colTiles, &cmpTiles);

    gx->cpTexStride = 0;
    SET_REG_FIELD(0x454, gx->cpTexStride, 10,  0, rowTiles * cmpTiles);
    SET_REG_FIELD(0x455, gx->cpTexStride,  8, 24, 0x4D);
    SET_REG_FIELD(0x456, gx->cpTex, 1, 9, mipmap);
    SET_REG_FIELD(0x457, gx->cpTex, 3, 4, peTexFmt);
}

void GXSetDispCopyFrame2Field(GXCopyMode mode)
{
    CHECK_GXBEGIN(0x468, "GXSetDispCopyFrame2Field");
    SET_REG_FIELD(0x469, gx->cpDisp, 2, 12, mode);
    SET_REG_FIELD(0x46A, gx->cpTex, 2, 12, 0);
}

void GXSetCopyClamp(GXFBClamp clamp)
{
    u8 clmpB;
    u8 clmpT;

    CHECK_GXBEGIN(0x47D, "GXSetCopyClamp");

    clmpT = (clamp & 1) == 1;
    clmpB = (clamp & 2) == 2;

    SET_REG_FIELD(0x481, gx->cpDisp, 1, 0, clmpT);
    SET_REG_FIELD(0x482, gx->cpDisp, 1, 1, clmpB);

    SET_REG_FIELD(0x484, gx->cpTex, 1, 0, clmpT);
    SET_REG_FIELD(0x485, gx->cpTex, 1, 1, clmpB);
}

u32 GXSetDispCopyYScale(f32 vscale)
{
    u8 enable;
    u32 iScale;
    f32 fScale;
    u32 ht;
    u32 reg;

    CHECK_GXBEGIN(0x49B, "GXSetDispCopyYScale");

    ASSERTMSGLINE(0x49D, vscale >= 1.0f, "GXSetDispCopyYScale: Vertical scale must be >= 1.0");

    iScale = (u32) (256.0f / vscale) & 0x1FF;
    fScale = 256.0f / (f32) iScale;
    enable = (iScale != 256);

    reg = 0;
    SET_REG_FIELD(0x4A6, reg, 9, 0, iScale);
    SET_REG_FIELD(0x4A7, reg, 8, 24, 0x4E);
    GX_WRITE_RAS_REG(reg);
    gx->bpSent = 1;
    SET_REG_FIELD(0x4AB, gx->cpDisp, 1, 10, enable);
    ht = GET_REG_FIELD(gx->cpDispSize, 10, 10) + 1;
    return ht * fScale;
}

void GXSetCopyClear(GXColor clear_clr, u32 clear_z)
{
    u32 reg;

    CHECK_GXBEGIN(0x4C4, "GXSetCopyClear");
    ASSERTMSGLINE(0x4C6, clear_z <= 0xFFFFFF, "GXSetCopyClear: Z clear value is out of range");

    reg = 0;
    SET_REG_FIELD(0x4C9, reg, 8, 0, clear_clr.r);
    SET_REG_FIELD(0x4CA, reg, 8, 8, clear_clr.a);
    SET_REG_FIELD(0x4CB, reg, 8, 24, 0x4F);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(0x4CF, reg, 8, 0, clear_clr.b);
    SET_REG_FIELD(0x4D0, reg, 8, 8, clear_clr.g);
    SET_REG_FIELD(0x4D1, reg, 8, 24, 0x50);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(0x4D5, reg, 24, 0, clear_z);
    SET_REG_FIELD(0x4D6, reg, 8, 24, 0x51);
    GX_WRITE_RAS_REG(reg);
    gx->bpSent = 1;
}

void GXSetCopyFilter(GXBool aa, const u8 sample_pattern[12][2], GXBool vf, const u8 vfilter[7]) {
    u32 msLoc[4];
    u32 coeff0;
    u32 coeff1;

    CHECK_GXBEGIN(0x4F1, "GXSetCopyFilter");

    if (aa != 0) {
        msLoc[0] = 0;
        SET_REG_FIELD(0x4F5, msLoc[0], 4,  0, sample_pattern[0][0]);
        SET_REG_FIELD(0x4F6, msLoc[0], 4,  4, sample_pattern[0][1]);
        SET_REG_FIELD(0x4F7, msLoc[0], 4,  8, sample_pattern[1][0]);
        SET_REG_FIELD(0x4F8, msLoc[0], 4, 12, sample_pattern[1][1]);
        SET_REG_FIELD(0x4F9, msLoc[0], 4, 16, sample_pattern[2][0]);
        SET_REG_FIELD(0x4FA, msLoc[0], 4, 20, sample_pattern[2][1]);
        SET_REG_FIELD(0x4FB, msLoc[0], 8, 24, 1);

        msLoc[1] = 0;
        SET_REG_FIELD(0x4FE, msLoc[1], 4,  0, sample_pattern[3][0]);
        SET_REG_FIELD(0x4FF, msLoc[1], 4,  4, sample_pattern[3][1]);
        SET_REG_FIELD(0x500, msLoc[1], 4,  8, sample_pattern[4][0]);
        SET_REG_FIELD(0x501, msLoc[1], 4, 12, sample_pattern[4][1]);
        SET_REG_FIELD(0x502, msLoc[1], 4, 16, sample_pattern[5][0]);
        SET_REG_FIELD(0x503, msLoc[1], 4, 20, sample_pattern[5][1]);
        SET_REG_FIELD(0x504, msLoc[1], 8, 24, 2);

        msLoc[2] = 0;
        SET_REG_FIELD(0x507, msLoc[2], 4,  0, sample_pattern[6][0]);
        SET_REG_FIELD(0x508, msLoc[2], 4,  4, sample_pattern[6][1]);
        SET_REG_FIELD(0x509, msLoc[2], 4,  8, sample_pattern[7][0]);
        SET_REG_FIELD(0x50A, msLoc[2], 4, 12, sample_pattern[7][1]);
        SET_REG_FIELD(0x50B, msLoc[2], 4, 16, sample_pattern[8][0]);
        SET_REG_FIELD(0x50C, msLoc[2], 4, 20, sample_pattern[8][1]);
        SET_REG_FIELD(0x50D, msLoc[2], 8, 24, 3);

        msLoc[3] = 0;
        SET_REG_FIELD(0x510, msLoc[3], 4,  0, sample_pattern[9][0]);
        SET_REG_FIELD(0x511, msLoc[3], 4,  4, sample_pattern[9][1]);
        SET_REG_FIELD(0x512, msLoc[3], 4,  8, sample_pattern[10][0]);
        SET_REG_FIELD(0x513, msLoc[3], 4, 12, sample_pattern[10][1]);
        SET_REG_FIELD(0x514, msLoc[3], 4, 16, sample_pattern[11][0]);
        SET_REG_FIELD(0x515, msLoc[3], 4, 20, sample_pattern[11][1]);
        SET_REG_FIELD(0x516, msLoc[3], 8, 24, 4);
    } else {
        msLoc[0] = 0x01666666;
        msLoc[1] = 0x02666666;
        msLoc[2] = 0x03666666;
        msLoc[3] = 0x04666666;
    }
    GX_WRITE_RAS_REG(msLoc[0]);
    GX_WRITE_RAS_REG(msLoc[1]);
    GX_WRITE_RAS_REG(msLoc[2]);
    GX_WRITE_RAS_REG(msLoc[3]);

    coeff0 = 0;
    SET_REG_FIELD(0, coeff0, 8, 24, 0x53);
    coeff1 = 0;
    SET_REG_FIELD(0, coeff1, 8, 24, 0x54);
    if (vf != 0) {
        SET_REG_FIELD(0x52E, coeff0, 6,  0, vfilter[0]);
        SET_REG_FIELD(0x52F, coeff0, 6,  6, vfilter[1]);
        SET_REG_FIELD(0x530, coeff0, 6, 12, vfilter[2]);
        SET_REG_FIELD(0x531, coeff0, 6, 18, vfilter[3]);
        SET_REG_FIELD(0x532, coeff1, 6,  0, vfilter[4]);
        SET_REG_FIELD(0x533, coeff1, 6,  6, vfilter[5]);
        SET_REG_FIELD(0x534, coeff1, 6, 12, vfilter[6]);
    } else {
        SET_REG_FIELD(0, coeff0, 6,  0, 0);
        SET_REG_FIELD(0, coeff0, 6,  6, 0);
        SET_REG_FIELD(0, coeff0, 6, 12, 21);
        SET_REG_FIELD(0, coeff0, 6, 18, 22);
        SET_REG_FIELD(0, coeff1, 6,  0, 21);
        SET_REG_FIELD(0, coeff1, 6,  6,  0);
        SET_REG_FIELD(0, coeff1, 6, 12,  0);
    }
    GX_WRITE_RAS_REG(coeff0);
    GX_WRITE_RAS_REG(coeff1);
    gx->bpSent = 1;
}

void GXSetDispCopyGamma(GXGamma gamma)
{
    CHECK_GXBEGIN(0x555, "GXSetDispCopyGamma");
    SET_REG_FIELD(0x556, gx->cpDisp, 2, 7, gamma);
}

#if DEBUG
static void __GXVerifCopy(void *dest, u8 clear)
{
    u8 clmpT;
    u8 clmpB;
    u32 x0;
    u32 y0;
    u32 dx;
    u32 dy;

    CHECK_GXBEGIN(0x56A, "GXCopyDisp");

    clmpT = GET_REG_FIELD(gx->cpDisp, 1, 0);
    clmpB = (u32)GET_REG_FIELD(gx->cpDisp, 1, 1);
    x0 = GET_REG_FIELD(gx->cpDispSrc, 10, 0);
    dx = GET_REG_FIELD(gx->cpDispSize, 10, 0) + 1;
    y0 = GET_REG_FIELD(gx->cpDispSrc, 10, 10);
    dy = GET_REG_FIELD(gx->cpDispSize, 10, 10) + 1;

    ASSERTMSGLINE(0x574, clmpT || y0 != 0, "GXCopy: Have to set GX_CLAMP_TOP if source top == 0");
    ASSERTMSGLINE(0x576, clmpB || y0 + dy <= 528, "GXCopy: Have to set GX_CLAMP_BOTTOM if source bottom > 528");
    ASSERTMSGLINE(0x57B, (gx->peCtrl & 7) != 3 || clear == 0, "GXCopy: Can not do clear while pixel type is Z");
    if ((u32) (gx->peCtrl & 7) == 5) {
        ASSERTMSGLINE(0x581, clear == 0, "GXCopy: Can not clear YUV framebuffer");
        ASSERTMSGLINE(0x583, (x0 & 3) == 0, "GXCopy: Source x is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(0x585, (y0 & 3) == 0, "GXCopy: Source y is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(0x587, (dx & 3) == 0, "GXCopy: Source width is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(0x589, (dy & 3) == 0, "GXCopy: Source height is not multiple of 4 for YUV copy");
    } else {
        ASSERTMSGLINE(0x58D, (x0 & 1) == 0, "GXCopy: Source x is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(0x58F, (y0 & 1) == 0, "GXCopy: Source y is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(0x591, (dx & 1) == 0, "GXCopy: Source width is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(0x593, (dy & 1) == 0, "GXCopy: Source height is not multiple of 2 for RGB copy");
    }
    ASSERTMSGLINE(0x597, ((u32)dest & 0x1F) == 0, "GXCopy: Display destination address not 32B aligned");
}
#endif

void GXCopyDisp(void *dest, GXBool clear)
{
    u32 reg;
    u32 tempPeCtrl;
    u32 phyAddr;
    u8 changePeCtrl;

    CHECK_GXBEGIN(0x5B1, "GXCopyDisp");

#if DEBUG
    __GXVerifCopy(dest, clear);
#endif
    if (clear) {
        reg = gx->zmode;
        SET_REG_FIELD(0, reg, 1, 0, 1);
        SET_REG_FIELD(0, reg, 3, 1, 7);
        GX_WRITE_RAS_REG(reg);

        reg = gx->cmode0;
        SET_REG_FIELD(0, reg, 1, 0, 0);
        SET_REG_FIELD(0, reg, 1, 1, 0);
        GX_WRITE_RAS_REG(reg);
    }
    changePeCtrl = FALSE;
    if ((clear || (u32)GET_REG_FIELD(gx->peCtrl, 3, 0) == 3)
     && (u32)GET_REG_FIELD(gx->peCtrl, 1, 6) == 1) {
        changePeCtrl = TRUE;
        tempPeCtrl = gx->peCtrl;
        SET_REG_FIELD(0, tempPeCtrl, 1, 6, 0);
        GX_WRITE_RAS_REG(tempPeCtrl);
    }
    GX_WRITE_RAS_REG(gx->cpDispSrc);
    GX_WRITE_RAS_REG(gx->cpDispSize);
    GX_WRITE_RAS_REG(gx->cpDispStride);

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    SET_REG_FIELD(0x5D8, reg, 21, 0, phyAddr >> 5);
    SET_REG_FIELD(0x5D9, reg, 8, 24, 0x4B);
    GX_WRITE_RAS_REG(reg);

    SET_REG_FIELD(0x5DC, gx->cpDisp, 1, 11, clear);
    SET_REG_FIELD(0x5DD, gx->cpDisp, 1, 14, 1);
    SET_REG_FIELD(0x5DE, gx->cpDisp, 8, 24, 0x52);
    GX_WRITE_RAS_REG(gx->cpDisp);

    if (clear) {
        GX_WRITE_RAS_REG(gx->zmode);
        GX_WRITE_RAS_REG(gx->cmode0);
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(gx->peCtrl);
    }
    gx->bpSent = 1;
}

void GXCopyTex(void *dest, GXBool clear)
{
    u32 reg;
    u32 tempPeCtrl;
    u32 phyAddr;
    u8 changePeCtrl;

    CHECK_GXBEGIN(0x604, "GXCopyTex");

#if DEBUG
    __GXVerifCopy(dest, clear);
#endif
    if (clear) {
        reg = gx->zmode;
        SET_REG_FIELD(0, reg, 1, 0, 1);
        SET_REG_FIELD(0, reg, 3, 1, 7);
        GX_WRITE_RAS_REG(reg);

        reg = gx->cmode0;
        SET_REG_FIELD(0, reg, 1, 0, 0);
        SET_REG_FIELD(0, reg, 1, 1, 0);
        GX_WRITE_RAS_REG(reg);
    }
    changePeCtrl = 0;
    tempPeCtrl = gx->peCtrl;
    if (((u8) gx->cpTexZ != 0) && ((u32) (tempPeCtrl & 7) != 3)) {
        changePeCtrl = 1;
        tempPeCtrl = (tempPeCtrl & 0xFFFFFFF8) | 3;
    }
    if (((clear != 0) || ((u32) (tempPeCtrl & 7) == 3)) && ((u32) ((tempPeCtrl >> 6U) & 1) == 1)) {
        changePeCtrl = 1;
        tempPeCtrl &= 0xFFFFFFBF;
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(tempPeCtrl);
    }
    GX_WRITE_RAS_REG(gx->cpTexSrc);
    GX_WRITE_RAS_REG(gx->cpTexSize);
    GX_WRITE_RAS_REG(gx->cpTexStride);

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    SET_REG_FIELD(0x635, reg, 21, 0, phyAddr >> 5);
    SET_REG_FIELD(0x636, reg, 8, 24, 0x4B);
    GX_WRITE_RAS_REG(reg);

    SET_REG_FIELD(0x639, gx->cpTex, 1, 11, clear);
    SET_REG_FIELD(0x63A, gx->cpTex, 1, 14, 0);
    SET_REG_FIELD(0x63B, gx->cpTex, 8, 24, 0x52);
    GX_WRITE_RAS_REG(gx->cpTex);

    if (clear != 0) {
        GX_WRITE_RAS_REG(gx->zmode);
        GX_WRITE_RAS_REG(gx->cmode0);
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(gx->peCtrl);
    }
    gx->bpSent = 1;
}

void GXClearBoundingBox(void)
{
    u32 reg;

    CHECK_GXBEGIN(0x65B, "GXClearBoundingBox");
    reg = 0x550003FF;
    GX_WRITE_RAS_REG(reg);
    reg = 0x560003FF;
    GX_WRITE_RAS_REG(reg);
    gx->bpSent = 1;
}

void GXReadBoundingBox(u16 *left, u16 *top, u16 *right, u16 *bottom)
{
    CHECK_GXBEGIN(0x671, "GXReadBoundingBox");
    *left = __peReg[8];
    *top = __peReg[10];
    *right = __peReg[9];
    *bottom = __peReg[11];
}
