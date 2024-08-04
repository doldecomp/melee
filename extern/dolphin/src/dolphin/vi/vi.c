#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/hw_regs.h>
#include <macros.h>

#include "__gx.h"
#include "__os.h"
#include "__vi.h"

typedef struct {
    u8 equ;
    u16 acv;
    u16 prbOdd;
    u16 prbEven;
    u16 psbOdd;
    u16 psbEven;
    u8 bs1;
    u8 bs2;
    u8 bs3;
    u8 bs4;
    u16 be1;
    u16 be2;
    u16 be3;
    u16 be4;
    u16 nhlines;
    u16 hlw;
    u8 hsy;
    u8 hcs;
    u8 hce;
    u8 hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITiming;

typedef struct {
    u16 DispPosX;
    u16 DispPosY;
    u16 DispSizeX;
    u16 DispSizeY;
    u16 AdjustedDispPosX;
    u16 AdjustedDispPosY;
    u16 AdjustedDispSizeY;
    u16 AdjustedPanPosY;
    u16 AdjustedPanSizeY;
    u16 FBSizeX;
    u16 FBSizeY;
    u16 PanPosX;
    u16 PanPosY;
    u16 PanSizeX;
    u16 PanSizeY;
    VIXFBMode FBMode;
    u32 nonInter;
    u32 tv;
    u8 wordPerLine;
    u8 std;
    u8 wpl;
    u32 bufAddr;
    u32 tfbb;
    u32 bfbb;
    u8 xof;
    BOOL black;
    BOOL threeD;
    u32 rbufAddr;
    u32 rtfbb;
    u32 rbfbb;
    VITiming *timing;
} SomeVIStruct;

static volatile u32 retraceCount;
static u32 changeMode;
static volatile u32 flushFlag;
static struct OSThreadQueue retraceQueue;
static void (*PreCB)(u32);
static void (*PostCB)(u32);
static u32 encoderType;
static s16 displayOffsetH;
static s16 displayOffsetV;
static volatile u64 changed;
static u16 regs[59];
static volatile u64 shdwChanged;
static u16 shdwRegs[59];

#define MARK_CHANGED(index) (changed |= 1LL << (63 - (index)))

static VITiming timing[7] =
{
    { 6, 240, 24, 25, 3, 2, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 12, 12, 12, 12, 520, 520, 520, 520, 526, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 5, 287, 35, 36, 1, 0, 13, 12, 11, 10, 619, 618, 617, 620, 625, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 5, 287, 35, 35, 2, 2, 13, 11, 13, 11, 619, 621, 619, 621, 626, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 6, 240, 24, 25, 3, 2, 16, 15, 14, 13, 518, 517, 516, 519, 525, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 16, 14, 16, 14, 518, 520, 518, 520, 526, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 12, 480, 44, 44, 10, 10, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 162, 373, 122, 412 },
};
static u16 taps[25] = {
    0x01F0, 0x01DC,
    0x01AE, 0x0174,
    0x0129, 0x00DB,
    0x008E, 0x0046,
    0x000C, 0x00E2,
    0x00CB, 0x00C0,
    0x00C4, 0x00CF,
    0x00DE, 0x00EC,
    0x00FC, 0x0008,
    0x000F, 0x0013,
    0x0013, 0x000F,
    0x000C, 0x0008,
    0x0001
};

static SomeVIStruct HorVer;
static u32 FBSet;

static u32 getCurrentFieldEvenOdd(void);

static u32 getEncoderType(void)
{
    return 1;
}

static s32 cntlzd(u64 bit)
{
    u32 hi;
    u32 lo;
    s32 value;

    hi = bit >> 32;
    lo = bit & 0xFFFFFFFF;
    value = __cntlzw(hi);
    if (value < 32) {
        return value;
    }
    return __cntlzw(lo) + 32;
}

static int VISetRegs(void)
{
    s32 regIndex;

    if (changeMode != 1 || getCurrentFieldEvenOdd() != 0) {
        while (shdwChanged != 0) {
            regIndex = cntlzd(shdwChanged);
            __VIRegs[regIndex] = shdwRegs[regIndex];
            shdwChanged &= ~((u64)1 << (63 - regIndex));
        }
        changeMode = 0;
        return 1;
    }
    return 0;
}

static void __VIRetraceHandler(__OSInterrupt unused, OSContext *context)
{
    OSContext exceptionContext;
    u16 reg;
    u32 inter;
#if DEBUG
    static u32 dbgCount;
#endif

    inter = 0;
    reg = __VIRegs[0x18];
    if (reg & 0x8000) {
        __VIRegs[0x18] = reg & ~0x8000;
        inter |= 1;
    }
    reg = __VIRegs[0x1A];
    if (reg & 0x8000) {
        __VIRegs[0x1A] = reg & ~0x8000;
        inter |= 2;
    }
    reg = __VIRegs[0x1C];
    if (reg & 0x8000) {
        __VIRegs[0x1C] = reg & ~0x8000;
        inter |= 4;
    }
    reg = __VIRegs[0x1E];
    if (reg & 0x8000) {
        __VIRegs[0x1E] = reg & ~0x8000;
        inter |= 8;
    }
    reg = __VIRegs[0x1E];
    if ((inter & 4) || (inter & 8)) {
        OSSetCurrentContext(context);
        return;
    }
    if (inter == 0) {
        ASSERTLINE(0x2BA, FALSE);
    }
    retraceCount += 1;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (PreCB) {
        PreCB(retraceCount);
    }
    if (flushFlag != 0) {
#if DEBUG
        dbgCount = 0;
#endif
        if (VISetRegs() != 0) {
            flushFlag = 0;
        }
    }
#if DEBUG
    else if (changed != 0) {
        dbgCount++;
        if (dbgCount > 60) {
            OSReport("Warning: VIFlush() was not called for 60 frames although VI settings were changed\n");
            dbgCount = 0;
        }
    }
#endif
    if (PostCB) {
        OSClearContext(&exceptionContext);
        PostCB(retraceCount);
    }
    OSWakeupThread(&retraceQueue);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb)
{
    BOOL enabled;
    VIRetraceCallback oldcb;

    oldcb = PreCB;
    enabled = OSDisableInterrupts();
    PreCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb)
{
    BOOL enabled;
    VIRetraceCallback oldcb;

    oldcb = PostCB;
    enabled = OSDisableInterrupts();
    PostCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

#pragma dont_inline on
static VITiming *getTiming(VITVMode mode)
{
    switch (mode) {
    case VI_TVMODE_NTSC_INT:  return &timing[0];
    case VI_TVMODE_NTSC_DS:   return &timing[1];
    case VI_TVMODE_PAL_INT:   return &timing[2];
    case VI_TVMODE_PAL_DS:    return &timing[3];
    case VI_TVMODE_MPAL_INT:  return &timing[4];
    case VI_TVMODE_MPAL_DS:   return &timing[5];
    case VI_TVMODE_NTSC_PROG: return &timing[6];
    default: return NULL;
    }
}
#pragma dont_inline reset

void __VIInit(VITVMode mode)
{
    VITiming *tm;
    u32 nonInter;
    u32 tv;
    volatile u32 a;
    u16 hct;
    u16 vct;
    u32 encoderType;

    encoderType = getEncoderType();
    if (encoderType == 0) {
        __VIInitPhilips();
    }
    nonInter = mode & 2;
    tv = (u32)mode >> 2;
    *(u32 *)OSPhysicalToCached(0xCC) = tv;
    if (encoderType == 0) {
        tv = 3;
    }
    tm = getTiming(mode);
    __VIRegs[1] = 2;

    // why?
    for (a = 0; a < 1000; a++) {
    }

    __VIRegs[1] = 0;
    __VIRegs[3] = (u32)tm->hlw;
    __VIRegs[2] = tm->hce | (tm->hcs << 8);
    __VIRegs[5] = tm->hsy | ((tm->hbe640 & 0x1FF) << 7);
    __VIRegs[4] = (tm->hbe640 >> 9) | ((tm->hbs640 & 0xFFFF) << 1);
    if (encoderType == 0) {
        __VIRegs[0x39] = tm->hbeCCIR656 | 0x8000;
        __VIRegs[0x3A] = (u32)tm->hbsCCIR656;
    }
    __VIRegs[0] = (u32)tm->equ;
    __VIRegs[7] = (u32)(tm->prbOdd + (tm->acv * 2) - 2);
    __VIRegs[6] = (u32)(tm->psbOdd + 2);
    __VIRegs[9] = (u32)(tm->prbEven + (tm->acv * 2) - 2);
    __VIRegs[8] = (u32)(tm->psbEven + 2);
    __VIRegs[11] = tm->bs1 | (tm->be1 << 5);
    __VIRegs[10] = tm->bs3 | (tm->be3 << 5);
    __VIRegs[13] = tm->bs2 | (tm->be2 << 5);
    __VIRegs[12] = tm->bs4 | (tm->be4 << 5);
    __VIRegs[36] = 0x2828;
    __VIRegs[27] = 1;
    __VIRegs[26] = 0x1001;
    hct = tm->hlw + 1;
    vct = (tm->nhlines / 2) + 1;
    __VIRegs[25] = (u16)(u32)hct;
    __VIRegs[24] = vct | 0x1000;
    if (mode != VI_TVMODE_NTSC_PROG) {
        __VIRegs[1] = (nonInter << 2) | 1 | (tv << 8);
        __VIRegs[54] = 0;
        return;
    }
    __VIRegs[1] = (tv << 8) | 5;
    __VIRegs[54] = 1;
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(val, min, max) ((val) > (max) ? (max) : (val) < (min) ? (min) : (val))

static void AdjustPosition(u16 acv)
{
    s32 coeff;
    s32 frac;

    HorVer.AdjustedDispPosX = CLAMP((s16)HorVer.DispPosX + displayOffsetH, 0, 0x2D0 - HorVer.DispSizeX);
    coeff = (HorVer.FBMode == VI_XFBMODE_SF) ? 2 : 1;
    frac = HorVer.DispPosY & 1;
    HorVer.AdjustedDispPosY = MAX((s16)HorVer.DispPosY + displayOffsetV, frac);
    HorVer.AdjustedDispSizeY = HorVer.DispSizeY
                             + MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0)
                             - MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV - (((s16)acv * 2) - frac), 0);
    HorVer.AdjustedPanPosY = HorVer.PanPosY
                           - (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff);
    HorVer.AdjustedPanSizeY = HorVer.PanSizeY
                            + (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff)
                            - (MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV - (((s16)acv * 2) - frac), 0) / coeff);
}

static void ImportAdjustingValues(void)
{
    OSSram *sram = __OSLockSram();

    ASSERTLINE(0x3E2, sram);
    displayOffsetH = sram->displayOffsetH;
    displayOffsetV = 0;
    __OSUnlockSram(0);
}

void VIInit(void)
{
    u16 dspCfg;
    u32 value;
    u32 tv;

    encoderType = getEncoderType();
    if (!(__VIRegs[1] & 1)) {
        __VIInit(VI_TVMODE_NTSC_INT);
    }
    retraceCount = 0;
    changed = 0;
    shdwChanged = 0;
    changeMode = 0;
    flushFlag = 0;
    __VIRegs[39] = taps[0] | ((taps[1] & 0x3F) << 10);
    __VIRegs[38] = (taps[1] >> 6) | (taps[2] << 4);
    __VIRegs[41] = taps[3] | ((taps[4] & 0x3F) << 10);
    __VIRegs[40] = (taps[4] >> 6) | (taps[5] << 4);
    __VIRegs[43] = taps[6] | ((taps[7] & 0x3F) << 10);
    __VIRegs[42] = (taps[7] >> 6) | (taps[8] << 4);
    __VIRegs[45] = taps[9] | (taps[10] << 8);
    __VIRegs[44] = taps[11] | (taps[12] << 8);
    __VIRegs[47] = taps[13] | (taps[14] << 8);
    __VIRegs[46] = taps[15] | (taps[16] << 8);
    __VIRegs[49] = taps[17] | (taps[18] << 8);
    __VIRegs[48] = taps[19] | (taps[20] << 8);
    __VIRegs[51] = taps[21] | (taps[22] << 8);
    __VIRegs[50] = taps[23] | (taps[24] << 8);
    __VIRegs[56] = 0x280;
    ImportAdjustingValues();
    HorVer.DispSizeX = 0x280U;
    HorVer.DispSizeY = 0x1E0U;
    HorVer.DispPosX = (0x2D0 - HorVer.DispSizeX) / 2;
    HorVer.DispPosY = (0x1E0 - HorVer.DispSizeY) / 2;
    AdjustPosition(0xF0U);
    HorVer.FBSizeX = 0x280;
    HorVer.FBSizeY = 0x1E0;
    HorVer.PanPosX = 0;
    HorVer.PanPosY = 0;
    HorVer.PanSizeX = 0x280;
    HorVer.PanSizeY = 0x1E0;
    HorVer.FBMode = 0;
    dspCfg = __VIRegs[1];
    HorVer.nonInter = (s32) ((dspCfg >> 2U) & 1);
    HorVer.tv = (u32) ((dspCfg >> 8U) & 3);
    tv = (HorVer.tv == 3) ? 0 : HorVer.tv;
    HorVer.timing = getTiming((tv << 2) + HorVer.nonInter);
    regs[1] = dspCfg;
    HorVer.wordPerLine = 0x28;
    HorVer.std = 0x28;
    HorVer.wpl = 0x28;
    HorVer.xof = 0;
    HorVer.black = 1;
    HorVer.threeD = 0;
    OSInitThreadQueue(&retraceQueue);
    value = __VIRegs[24];
    value &= ~0x8000;
#if !DEBUG
    value = (u16)value;
#endif
    __VIRegs[24] = value;
    value = __VIRegs[26];
    value = value & ~0x8000;
#if !DEBUG
    value = (u16)value;
#endif
    __VIRegs[26] = value;
    PreCB = NULL;
    PostCB = NULL;
    __OSSetInterruptHandler(0x18, __VIRetraceHandler);
    __OSUnmaskInterrupts(0x80);
}

void VIWaitForRetrace(void)
{
    BOOL enabled;
    u32 count;

    enabled = OSDisableInterrupts();
    count = retraceCount;
    do {
        OSSleepThread(&retraceQueue);
    } while (count == retraceCount);
    OSRestoreInterrupts(enabled);
}

static void setInterruptRegs(VITiming *tm)
{
#if DEBUG
    u16 vct, hct;
#else
    u16 hct, vct;
#endif
    u16 borrow;

    vct = tm->nhlines / 2;
    borrow = tm->nhlines % 2;
    if (borrow != 0) {
        hct = tm->hlw;
    } else {
        hct = 0;
    }
    vct++;
    hct++;
    regs[25] = (u16)(u32)hct;
    MARK_CHANGED(25);
    regs[24] = vct | 0x1000;
    MARK_CHANGED(24);

    vct;
}

static void setPicConfig(u16 fbSizeX, VIXFBMode xfbMode, u16 panPosX, u16 panSizeX, u8 *wordPerLine, u8 *std, u8 *wpl, u8 *xof)
{
    *wordPerLine = (fbSizeX + 15) / 16;
    *std = (xfbMode == VI_XFBMODE_SF) ? *wordPerLine : (u8)(*wordPerLine * 2);
    *xof = panPosX % 16;
    *wpl = (*xof + panSizeX + 15) / 16;
    regs[0x24] = *std | (*wpl << 8);
    changed |= 0x8000000;
}

static void setBBIntervalRegs(VITiming *tm)
{
    u16 val;

    val = tm->bs1 | (tm->be1 << 5);
    regs[11] = val;
    changed |= 0x10000000000000;

    val = tm->bs3 | (tm->be3 << 5);
    regs[10] = val;
    changed |= 0x20000000000000;

    val = tm->bs2 | (tm->be2 << 5);
    regs[13] = val;
    changed |= 0x4000000000000;

    val = tm->bs4 | (tm->be4 << 5);
    regs[12] = val;
    changed |= (1LL << (63-12));
}

static void setScalingRegs(u16 panSizeX, u16 dispSizeX, BOOL threeD)
{
    u32 scale;

    panSizeX = threeD ? (panSizeX << 1) : panSizeX;
    if (panSizeX < dispSizeX) {
        scale = (u32)(dispSizeX + (panSizeX << 8) - 1) / dispSizeX;
        regs[37] = scale | 0x1000;
        changed |= 0x04000000;
        regs[56] = (u32)panSizeX;
        changed |= 0x80;
    } else {
        regs[37] = 0x100;
        changed |= 0x04000000;
    }
}

static void calcFbbs(u32 bufAddr, u16 panPosX, u16 panPosY, u8 wordPerLine, VIXFBMode xfbMode, u16 dispPosY, u32 *tfbb, u32 *bfbb)
{
    u32 bytesPerLine;
    u32 xoffInWords;
    u32 tmp;

    xoffInWords = (panPosX & ~0xF) >> 4;
    bytesPerLine = (wordPerLine & 0xFF) << 5;
    *tfbb = bufAddr + (xoffInWords << 5) + (bytesPerLine * panPosY);
    *bfbb = (xfbMode == VI_XFBMODE_SF) ? *tfbb : *tfbb + bytesPerLine;
    if (dispPosY % 2 == 1) {
        tmp = *tfbb;
        *tfbb = *bfbb;
        *bfbb = tmp;
    }
    *tfbb &= 0x3FFFFFFF;
    *bfbb &= 0x3FFFFFFF;
}

static void setFbbRegs(SomeVIStruct *HorVer, u32 *tfbb, u32 *bfbb, u32 *rtfbb, u32 *rbfbb)
{
    u32 shifted;

    calcFbbs(HorVer->bufAddr, HorVer->PanPosX, HorVer->AdjustedPanPosY, HorVer->wordPerLine, HorVer->FBMode, HorVer->AdjustedDispPosY, tfbb, bfbb);
    if (HorVer->threeD) {
        calcFbbs(HorVer->rbufAddr, HorVer->PanPosX, HorVer->AdjustedPanPosY, HorVer->wordPerLine, HorVer->FBMode, HorVer->AdjustedDispPosY, rtfbb, rbfbb);
    }
    if (*tfbb < 0x01000000U && *bfbb < 0x01000000U && *rtfbb < 0x01000000U && *rbfbb < 0x01000000U) {
        shifted = 0;
    } else {
        shifted = 1;
    }
    if (shifted) {
        *tfbb >>= 5;
        *bfbb >>= 5;
        *rtfbb >>= 5;
        *rbfbb >>= 5;
    }

    regs[15] = (u16)*tfbb & 0xFFFF;
    MARK_CHANGED(15);
    regs[14] = (shifted << 12) | ((*tfbb >> 16) | (HorVer->xof << 8));
    MARK_CHANGED(14);
    regs[19] = (u16)*bfbb & 0xFFFF;
    MARK_CHANGED(19);
    regs[18] = (*bfbb >> 16);
    MARK_CHANGED(18);
    if (HorVer->threeD) {
        regs[17] = (u16)*rtfbb & 0xFFFF;
        MARK_CHANGED(17);
        regs[16] = *rtfbb >> 16;
        MARK_CHANGED(16);
        regs[21] = (u16)*rbfbb & 0xFFFF;
        MARK_CHANGED(21);
        regs[20] = *rbfbb >> 16;
        MARK_CHANGED(20);
    }
}

static void setHorizontalRegs(VITiming *tm, u16 dispPosX, u16 dispSizeX)
{
    u32 hbe;
    u32 hbs;
    u32 hbeLo;
    u32 hbeHi;

    regs[3] = (u16)(u32)tm->hlw;
    MARK_CHANGED(3);
    regs[2] = tm->hce | (tm->hcs << 8);
    MARK_CHANGED(2);
    hbe = tm->hbe640 - 40 + dispPosX;
    hbs = tm->hbs640 + 40 + dispPosX - (720 - dispSizeX);
    hbeLo = hbe & 0x1FF;
    hbeHi = hbe >> 9;
    regs[5] = tm->hsy | (hbeLo << 7);
    MARK_CHANGED(5);
    regs[4] = hbeHi | (hbs * 2);
    MARK_CHANGED(4);
}

static void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven, u16 psbOdd, u16 psbEven, int black)
{
    u16 actualPrbOdd;
    u16 actualPrbEven;
    u16 actualPsbOdd;
    u16 actualPsbEven;
    u16 actualAcv;
    u16 c;
    u16 d;

    if (equ >= 10) {
        c = 1;
        d = 2;
    } else {
        c = 2;
        d = 1;
    }
    if ((dispPosY % 2) == 0) {
        actualPrbOdd = prbOdd + (d * dispPosY);
        actualPsbOdd = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
        actualPrbEven = prbEven + (d * dispPosY);
        actualPsbEven = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
    } else {
        actualPrbOdd = prbEven + (d * dispPosY);
        actualPsbOdd = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
        actualPrbEven = prbOdd + (d * dispPosY);
        actualPsbEven = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
    }
    actualAcv = dispSizeY / c;
    if (black) {
        actualPrbOdd += dispSizeY - 2;
        actualPsbOdd += 2;
        actualPrbEven += dispSizeY - 2;
        actualPsbEven += 2;
        actualAcv = 0;
    }
    regs[0] = equ | (actualAcv << 4);
    MARK_CHANGED(0);
    regs[7] = (u16)(u32)actualPrbOdd;
    MARK_CHANGED(7);
    regs[6] = (u16)(u32)actualPsbOdd;
    MARK_CHANGED(6);
    regs[9] = (u16)(u32)actualPrbEven;
    MARK_CHANGED(9);
    regs[8] = (u16)(u32)actualPsbEven;
    MARK_CHANGED(8);
}

void VIConfigure(GXRenderModeObj *rm)
{
    VITiming *tm;
    u32 reg;
    int enabled;
    u32 newNonInter;
    u32 tvInBootrom;
    u32 tvInGame;

    ASSERTMSGLINEV(0x601, (rm->viHeight & 1) == 0,
        "VIConfigure(): Odd number(%d) is specified to viHeight\n",
        rm->viHeight);

    if (rm->xFBmode == VI_XFBMODE_DF || rm->viTVmode == VI_TVMODE_NTSC_PROG) {
        ASSERTMSGLINEV(0x607, rm->xfbHeight == rm->viHeight,
            "VIConfigure(): xfbHeight(%d) is not equal to viHeight(%d) when DF XFB mode or progressive mode is specified\n",
            rm->xfbHeight, rm->viHeight);
    }
    if (rm->xFBmode == VI_XFBMODE_SF && rm->viTVmode != VI_TVMODE_NTSC_PROG) {
        ASSERTMSGLINEV(0x60E, rm->viHeight == rm->xfbHeight * 2,
            "VIConfigure(): xfbHeight(%d) is not as twice as viHeight(%d) when SF XFB mode is specified\n",
            rm->xfbHeight, rm->viHeight);
    }

    enabled = OSDisableInterrupts();
    if (rm->viTVmode == VI_TVMODE_NTSC_PROG) {
        HorVer.nonInter = 2;
    } else {
        newNonInter = rm->viTVmode & 1;
        if (HorVer.nonInter != newNonInter) {
            changeMode = 1;
        }
        HorVer.nonInter = newNonInter;
    }

    tvInBootrom = VIGetTvFormat();
    tvInGame = (u32)rm->viTVmode >> 2;
    ASSERTMSGLINEV(0x635, tvInBootrom == tvInGame || (tvInBootrom == 2 && tvInGame == 0) || (tvInBootrom == 0 && tvInGame == 2),
        "Doesn't match TV format: TV format in bootrom is %d but TV format specified in the game is %d (0:NTSC, 1:PAL, 2:MPAL)\n"
        /* BUG: forgot to pass in additional parameters! */);

    HorVer.tv        = tvInBootrom;
    HorVer.DispPosX  = rm->viXOrigin;
    HorVer.DispPosY  = (HorVer.nonInter == 1) ? (u16)(rm->viYOrigin * 2) : rm->viYOrigin;
    HorVer.DispSizeX = rm->viWidth;
    HorVer.FBSizeX   = rm->fbWidth;
    HorVer.FBSizeY   = rm->xfbHeight;
    HorVer.FBMode    = rm->xFBmode;
    HorVer.PanSizeX  = HorVer.FBSizeX;
    HorVer.PanSizeY  = HorVer.FBSizeY;
    HorVer.PanPosX   = 0;
    HorVer.PanPosY   = 0;
    HorVer.DispSizeY = (HorVer.nonInter == 2) ? HorVer.PanSizeY
                     : (HorVer.FBMode == VI_XFBMODE_SF) ? (u16)(HorVer.PanSizeY * 2)
                     : HorVer.PanSizeY;
    tm = getTiming(rm->viTVmode);
    HorVer.timing = tm;
    AdjustPosition(tm->acv);
    ASSERTMSGLINEV(0x654, rm->viXOrigin <= tm->hlw + 40 - tm->hbe640,
        "VIConfigure(): viXOrigin(%d) cannot be greater than %d in this TV mode\n",
        rm->viXOrigin, tm->hlw + 40 - tm->hbe640);
    ASSERTMSGLINEV(0x659,  rm->viXOrigin + rm->viWidth >= 0x2A8 - tm->hbs640,
        "VIConfigure(): viXOrigin + viWidth (%d) cannot be less than %d in this TV mode\n",
        rm->viXOrigin + rm->viWidth, 0x2A8 - tm->hbs640);

    if (encoderType == 0) {
        HorVer.tv = 3;
    }
    setInterruptRegs(tm);
    reg = regs[1];
    SET_REG_FIELD(0x66A, reg, 1, 2, (HorVer.nonInter & 1));
    SET_REG_FIELD(0x66B, reg, 2, 8, HorVer.tv);
    regs[1] = reg;
    MARK_CHANGED(1);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    setHorizontalRegs(tm, HorVer.AdjustedDispPosX, HorVer.DispSizeX);
    setBBIntervalRegs(tm);
    setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX, HorVer.PanSizeX, &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.AdjustedDispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height)
{
    BOOL enabled;
    VITiming *tm;

#if DEBUG
    ASSERTMSGLINEV(0x69C, (xOrg & 1) == 0,
        "VIConfigurePan(): Odd number(%d) is specified to xOrg\n",
        xOrg);
    if (HorVer.FBMode == VI_XFBMODE_DF) {
        ASSERTMSGLINEV(0x6A1, (height & 1) == 0,
            "VIConfigurePan(): Odd number(%d) is specified to height when DF XFB mode\n",
            height);
    }
#endif
    enabled = OSDisableInterrupts();
    HorVer.PanPosX   = xOrg;
    HorVer.PanPosY   = yOrg;
    HorVer.PanSizeX  = width;
    HorVer.PanSizeY  = height;
    HorVer.DispSizeY = (HorVer.nonInter == 2) ? HorVer.PanSizeY
                     : (HorVer.FBMode == VI_XFBMODE_SF) ? (u16)(HorVer.PanSizeY * 2)
                     : HorVer.PanSizeY;
    tm = HorVer.timing;
    AdjustPosition(tm->acv);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX, HorVer.PanSizeX, &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

void VIFlush(void)
{
    BOOL enabled;
    s32 regIndex;

    enabled = OSDisableInterrupts();
    shdwChanged |= changed;
    while (changed != 0) {
        regIndex = cntlzd(changed);
        shdwRegs[regIndex] = regs[regIndex];
        changed &= ~((u64)1 << (63 - regIndex));
    }
    flushFlag = 1;
    OSRestoreInterrupts(enabled);
}

void VISetNextFrameBuffer(void *fb)
{
    BOOL enabled;

    ASSERTMSGLINEV(0x6F7, ((u32)fb & 0x1F) == 0,
        "VISetNextFrameBuffer(): Frame buffer address(0x%08x) is not 32byte aligned\n",
        fb);
    enabled = OSDisableInterrupts();
    HorVer.bufAddr = (u32)fb;
    FBSet = 1;
    setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    OSRestoreInterrupts(enabled);
}

void VISetNextRightFrameBuffer(void *fb)
{
    BOOL enabled;

    ASSERTMSGLINEV(0x71F, ((u32)fb & 0x1F) == 0,
        "VISetNextFrameBuffer(): Frame buffer address(0x%08x) is not 32byte aligned\n",
        fb);
    enabled = OSDisableInterrupts();
    HorVer.rbufAddr = (u32)fb;
    FBSet = 1;
    setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    OSRestoreInterrupts(enabled);
}

void VISetBlack(BOOL black)
{
    BOOL enabled;
    VITiming *tm;

    enabled = OSDisableInterrupts();
    HorVer.black = black;
    tm = HorVer.timing;
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

void VISet3D(BOOL threeD)
{
    BOOL enabled;
    u32 reg;

    enabled = OSDisableInterrupts();
    HorVer.threeD = threeD;
    reg = regs[1];
    SET_REG_FIELD(0x766, reg, 1, 3, HorVer.threeD);
    regs[1] = reg;
    MARK_CHANGED(1);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    OSRestoreInterrupts(enabled);
}

u32 VIGetRetraceCount(void)
{
    return retraceCount;
}

static u32 getCurrentHalfLine(void)
{
    u32 hcount;
    u32 vcount0;
    u32 vcount;
    VITiming *tm;

    tm = HorVer.timing;
    vcount = __VIRegs[22] & 0x7FF;
    do {
        vcount0 = vcount;
        hcount = __VIRegs[23] & 0x7FF;
        vcount = __VIRegs[22] & 0x7FF;
    } while (vcount0 != vcount);
    return ((vcount - 1) * 2) + ((hcount - 1) / tm->hlw);
}

static u32 getCurrentFieldEvenOdd(void)
{
    u16 value;
    u32 nin;
    u32 fmt;
    VITVMode tvMode;
    u32 nhlines;
    VITiming *tm;

    if (__VIRegs[54] & 1) {
        tm = getTiming(VI_TVMODE_NTSC_PROG);
    } else {
        value = __VIRegs[1];
        nin = ((value >> 2U) & 1);
        fmt = ((value >> 8U) & 3);
        tvMode = (fmt << 2) + nin;
        tm = getTiming(tvMode);
    }
    nhlines = tm->nhlines;
    if (getCurrentHalfLine() < nhlines) {
        return 1U;
    }
    return 0U;
}

u32 VIGetNextField(void)
{
    s32 nextField;
    BOOL enabled;
#if !DEBUG
    u8 unused[4];
#endif

    enabled = OSDisableInterrupts();
    nextField = getCurrentFieldEvenOdd() ^ 1;
    OSRestoreInterrupts(enabled);
    return nextField ^ (HorVer.AdjustedDispPosY & 1);
}

u32 VIGetCurrentLine(void)
{
    u32 halfLine;
    VITiming *tm;
    BOOL enabled;

    tm = HorVer.timing;
    enabled = OSDisableInterrupts();
    halfLine = getCurrentHalfLine();
    OSRestoreInterrupts(enabled);
    if (halfLine >= tm->nhlines) {
        halfLine -= tm->nhlines;
    }
    return halfLine >> 1U;
}

u32 VIGetTvFormat(void)
{
    u32 format = *(u32 *)OSPhysicalToCached(0xCC);

    ASSERTMSGLINE(0x80D, format == 0 || format == 1 || format == 2,
        "VIGetTvFormat(): Wrong format is stored in lo mem. Maybe lo mem is trashed");
    return format;
}

void __VISetAdjustingValues(s16 x, s16 y)
{
    BOOL enabled;
    VITiming *tm;

    ASSERTMSGLINE(0x822, (y & 1) == 0, "__VISetAdjustValues(): y offset should be an even number");
    enabled = OSDisableInterrupts();
    displayOffsetH = x;
    displayOffsetV = y;
    tm = HorVer.timing;
    AdjustPosition(tm->acv);
    setHorizontalRegs(tm, HorVer.AdjustedDispPosX, HorVer.DispSizeX);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.AdjustedDispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

void __VIGetAdjustingValues(s16 *x, s16 *y)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    *x = displayOffsetH;
    *y = displayOffsetV;
    OSRestoreInterrupts(enabled);
}
