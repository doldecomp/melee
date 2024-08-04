#include <string.h>

#include <dolphin/base/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <macros.h>

#include "__gx.h"

static struct __GXData_struct gxData;
struct __GXData_struct *gx = &gxData;
// DWARF info lists all of these as "void *", but these types make more sense.
u16 *__memReg;
u16 *__peReg;
u16 *__cpReg;
u32 *__piReg;
#if DEBUG
GXBool __GXinBegin;
#endif

asm BOOL IsWriteGatherBufferEmpty(void)
{
    sync
    mfspr r3, WPAR
    andi. r3, r3, 1
}

static void EnableWriteGatherPipe(void)
{
    u32 hid2 = PPCMfhid2();

    PPCMtwpar(OSUncachedToPhysical((void *)GXFIFO_ADDR));
    hid2 |= 0x40000000;
    PPCMthid2(hid2);
}

static void DisableWriteGatherPipe(void)
{
    u32 hid2 = PPCMfhid2();

    hid2 &= ~0x40000000;
    PPCMthid2(hid2);
}

static GXTexRegion *__GXDefaultTexRegionCallback(GXTexObj *t_obj, GXTexMapID unused)
{
    GXTexFmt fmt = GXGetTexObjFmt(t_obj);

    if (fmt != GX_TF_C4 && fmt != GX_TF_C8 && fmt != GX_TF_C14X2) {
        return &gx->TexRegions[gx->nextTexRgn++ & 7];
    } else {
        return &gx->TexRegionsCI[gx->nextTexRgnCI++ & 3];
    }
}

static GXTlutRegion *__GXDefaultTlutRegionCallback(u32 idx)
{
    if (idx >= 0x14U) {
        return NULL;
    }
    return &gx->TlutRegions[idx];
}

#if DEBUG
static void __GXDefaultVerifyCallback(GXWarningLevel level, u32 id, char *msg)
{
    OSReport("Level %1d, Warning %3d: %s\n", level, id, msg);
}
#endif

GXFifoObj FifoObj;

GXFifoObj *GXInit(void *base, u32 size)
{
    GXRenderModeObj *rmode;
    f32 identity_mtx[3][4];
    GXColor clear = {64, 64, 64, 255};
    GXColor black = {0, 0, 0, 0};
    GXColor white = {255, 255, 255, 255};
    u32 i;
    u32 reg;
    u32 freqBase;

    gx->inDispList = FALSE;
    gx->dlSaveContext = TRUE;
#if DEBUG
    __GXinBegin = FALSE;
#endif
    gx->tcsManEnab = FALSE;
    gx->vNum = 0;
    __piReg = OSPhysicalToUncached(0xC003000);
    __cpReg = OSPhysicalToUncached(0xC000000);
    __peReg = OSPhysicalToUncached(0xC001000);
    __memReg = OSPhysicalToUncached(0xC004000);
    __GXFifoInit();
    GXInitFifoBase(&FifoObj, base, size);
    GXSetCPUFifo(&FifoObj);
    GXSetGPFifo(&FifoObj);
    __GXPEInit();
    EnableWriteGatherPipe();

    gx->genMode = 0;
    SET_REG_FIELD(0, gx->genMode, 8, 24, 0);
    gx->bpMask = 255;
    SET_REG_FIELD(0, gx->bpMask, 8, 24, 0x0F);
    gx->lpSize = 0;
    SET_REG_FIELD(0, gx->lpSize, 8, 24, 0x22);
    for (i = 0; i < 16; ++i) {
        gx->tevc[i] = 0;
        gx->teva[i] = 0;
        gx->tref[i / 2] = 0;
        gx->texmapId[i] = GX_TEXMAP_NULL;
        SET_REG_FIELD(0x2F2, gx->tevc[i], 8, 24, 0xC0 + i * 2);
        SET_REG_FIELD(0x2F3, gx->teva[i], 8, 24, 0xC1 + i * 2);
        SET_REG_FIELD(0x2F5, gx->tevKsel[i / 2], 8, 24, 0xF6 + i / 2);
        SET_REG_FIELD(0x2F7, gx->tref[i / 2], 8, 24, 0x28 + i / 2);
    }
    gx->iref = 0;
    SET_REG_FIELD(0, gx->iref, 8, 24, 0x27);
    for (i = 0; i < 8; ++i) {
        gx->suTs0[i] = 0;
        gx->suTs1[i] = 0;
        SET_REG_FIELD(0x300, gx->suTs0[i], 8, 24, 0x30 + i * 2);
        SET_REG_FIELD(0x301, gx->suTs1[i], 8, 24, 0x31 + i * 2);
    }
    SET_REG_FIELD(0, gx->suScis0, 8, 24, 0x20);
    SET_REG_FIELD(0, gx->suScis1, 8, 24, 0x21);
    SET_REG_FIELD(0, gx->cmode0, 8, 24, 0x41);
    SET_REG_FIELD(0, gx->cmode1, 8, 24, 0x42);
    SET_REG_FIELD(0, gx->zmode, 8, 24, 0x40);
    SET_REG_FIELD(0, gx->peCtrl, 8, 24, 0x43);
    SET_REG_FIELD(0, gx->cpTex, 2, 7, 0);
    gx->dirtyState = 0;
    gx->dirtyVAT = FALSE;
#if DEBUG
    __gxVerif->verifyLevel = GX_WARN_ALL;
    GXSetVerifyCallback(__GXDefaultVerifyCallback);
    for (i = 0; i < 256; i++) {
        SET_REG_FIELD(0, __gxVerif->rasRegs[i], 8, 24, 0xFF);
    }
    memset(__gxVerif->xfRegsDirty, 0, 0x50);
    memset(__gxVerif->xfMtxDirty, 0, 0x100);
    memset(__gxVerif->xfNrmDirty, 0, 0x60);
    memset(__gxVerif->xfLightDirty, 0, 0x80);
#endif
    freqBase = __OSBusClock / 0x1F4;
    __GXFlushTextureState();
    reg = (freqBase >> 11) | 0x400 | 0x69000000;
    GX_WRITE_RAS_REG(reg);

    __GXFlushTextureState();
    reg = (freqBase / 0x1080) | 0x200 | 0x46000000;
    GX_WRITE_RAS_REG(reg);

    for (i = GX_VTXFMT0; i < GX_MAX_VTXFMT; i++)
    {
        SET_REG_FIELD(0, gx->vatA[i], 1, 30, 1);
        SET_REG_FIELD(0, gx->vatB[i], 1, 31, 1);
        {
            s32 regAddr;
            GX_WRITE_U8(8);
            GX_WRITE_U8(i | 0x80);
            GX_WRITE_U32(gx->vatB[i]);
            regAddr = i - 12;
        }
    }
    {
        u32 reg1 = 0;
        u32 reg2 = 0;
        SET_REG_FIELD(0, reg1, 1, 0, 1);
        SET_REG_FIELD(0, reg1, 1, 1, 1);
        SET_REG_FIELD(0, reg1, 1, 2, 1);
        SET_REG_FIELD(0, reg1, 1, 3, 1);
        SET_REG_FIELD(0, reg1, 1, 4, 1);
        SET_REG_FIELD(0, reg1, 1, 5, 1);
        GX_WRITE_XF_REG(0, reg1);
        SET_REG_FIELD(0, reg2, 1, 0, 1);
        GX_WRITE_XF_REG(0x12, reg2);
    #if DEBUG
        __gxVerif->xfRegsDirty[0] = 0;
    #endif
    }
    {
        u32 reg = 0;
        SET_REG_FIELD(0, reg, 1, 0, 1);
        SET_REG_FIELD(0, reg, 1, 1, 1);
        SET_REG_FIELD(0, reg, 1, 2, 1);
        SET_REG_FIELD(0, reg, 1, 3, 1);
        SET_REG_FIELD(0, reg, 8, 24, 0x58);
        GX_WRITE_RAS_REG(reg);
    }
    switch (VIGetTvFormat()) {
    case VI_NTSC: rmode = &GXNtsc480IntDf; break;
    case VI_PAL:  rmode = &GXPal528IntDf;  break;
    case VI_MPAL: rmode = &GXMpal480IntDf; break;
    default:
        ASSERTMSGLINE(0x38B, 0, "GXInit: invalid TV format");
        rmode = &GXNtsc480IntDf;
        break;
    }
    GXSetCopyClear(clear, 0xFFFFFF);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3CU);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x3CU);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, 0x3CU);
    GXSetTexCoordGen(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, 0x3CU);
    GXSetTexCoordGen(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, 0x3CU);
    GXSetTexCoordGen(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, 0x3CU);
    GXSetTexCoordGen(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, 0x3CU);
    GXSetTexCoordGen(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, 0x3CU);
    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6, 0);
    GXSetPointSize(6, 0);
    GXEnableTexOffsets(0, 0, 0);
    GXEnableTexOffsets(1, 0, 0);
    GXEnableTexOffsets(2, 0, 0);
    GXEnableTexOffsets(3, 0, 0);
    GXEnableTexOffsets(4, 0, 0);
    GXEnableTexOffsets(5, 0, 0);
    GXEnableTexOffsets(6, 0, 0);
    GXEnableTexOffsets(7, 0, 0);
    identity_mtx[0][0] = 1.0f;
    identity_mtx[0][1] = 0.0f;
    identity_mtx[0][2] = 0.0f;
    identity_mtx[0][3] = 0.0f;
    identity_mtx[1][0] = 0.0f;
    identity_mtx[1][1] = 1.0f;
    identity_mtx[1][2] = 0.0f;
    identity_mtx[1][3] = 0.0f;
    identity_mtx[2][0] = 0.0f;
    identity_mtx[2][1] = 0.0f;
    identity_mtx[2][2] = 1.0f;
    identity_mtx[2][3] = 0.0f;
    GXLoadPosMtxImm(identity_mtx, GX_PNMTX0);
    GXLoadNrmMtxImm(identity_mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);
    GXLoadTexMtxImm(identity_mtx, GX_PTIDENTITY, GX_MTX3x4);
    GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->xfbHeight, 0.0f, 1.0f);
    GXSetCoPlanar(GX_DISABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetScissor(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetScissorBoxOffset(0, 0);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, black);
    GXSetChanMatColor(GX_COLOR0A0, white);
    GXSetChanCtrl(GX_COLOR1A1, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, black);
    GXSetChanMatColor(GX_COLOR1A1, white);
    GXInvalidateTexAll();
    gx->nextTexRgn = 0;
    for (i = 0; i < 8; i++)
        GXInitTexCacheRegion(&gx->TexRegions[i], 0, i * 0x8000, 0, 0x80000 + i * 0x8000, 0);
    gx->nextTexRgnCI = 0;
    for (i = 0; i < 4; i++)
        GXInitTexCacheRegion(&gx->TexRegionsCI[i], 0, (i * 2 + 8) * 0x8000, 0, (i * 2 + 9) * 0x8000, 0);
    for (i = 0; i < 16; i++)
        GXInitTlutRegion(&gx->TlutRegions[i], 0xC0000 + i * 0x2000, 16);
    for (i = 0; i < 4; i++)
        GXInitTlutRegion(&gx->TlutRegions[i + 16], 0xE0000 + i * 0x8000, 64);
    GXSetTexRegionCallback(__GXDefaultTexRegionCallback);
    GXSetTlutRegionCallback(__GXDefaultTlutRegionCallback);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
    for (i = GX_TEVSTAGE0; i < GX_MAX_TEVSTAGE; i++)
    {
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = GX_TEVSTAGE0; i < GX_MAX_TEVSTAGE; i++)
        GXSetTevDirect((GXTevStageID)i);
    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, black);
    GXSetFogRangeAdj(GX_DISABLE, 0, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_ENABLE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
    GXSetDither(GX_ENABLE);
    GXSetDstAlpha(GX_DISABLE, 0);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetFieldMask(GX_ENABLE, GX_ENABLE);
    GXSetFieldMode(rmode->field_rendering,
                   ((rmode->viHeight == 2 * rmode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

    GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyDst(rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyYScale((f32)(rmode->xfbHeight) / (f32)(rmode->efbHeight));
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXClearBoundingBox();

    GXPokeColorUpdate(GX_TRUE);
    GXPokeAlphaUpdate(GX_TRUE);
    GXPokeDither(GX_FALSE);
    GXPokeBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, GX_LO_SET);
    GXPokeAlphaMode(GX_ALWAYS, 0);
    GXPokeAlphaRead(GX_READ_FF);
    GXPokeDstAlpha(GX_DISABLE, 0);
    GXPokeZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);

    return &FifoObj;
}
