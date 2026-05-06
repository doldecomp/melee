#include <dolphin.h>
#include <dolphin/gx.h>
#include <dolphin/demo.h>

#include "__demo.h"

unsigned char DemoStatEnable = 0;
static DemoStatData * DemoStat;
static unsigned long DemoStatIndx;
static unsigned long DemoStatMaxIndx;
static unsigned long DemoStatClocks;
static unsigned long DemoStatDisp;
static unsigned long DemoStatStrLen;
static unsigned long topPixIn;
static unsigned long topPixOut;
static unsigned long botPixIn;
static unsigned long botPixOut;
static unsigned long clrPixIn;
static unsigned long copyClks;
static unsigned long vcCheck;
static unsigned long vcMiss;
static unsigned long vcStall;
static unsigned long cpReq;
static unsigned long tcReq;
static unsigned long cpuRdReq;
static unsigned long cpuWrReq;
static unsigned long dspReq;
static unsigned long ioReq;
static unsigned long viReq;
static unsigned long peReq;
static unsigned long rfReq;
static unsigned long fiReq;

// functions
static void DEMOWriteStats(unsigned char update);
static void DEMOWriteStats(unsigned char update);

void DEMOSetStats(DemoStatData * stat, unsigned long nstats, DEMO_STAT_DISP disp) {
    if (!stat || nstats == 0) {
        DemoStatEnable = FALSE;
    } else {
        DemoStatEnable = TRUE;
        DemoStat = stat;
        DemoStatIndx = 0;
        DemoStatMaxIndx = nstats;
        DemoStatDisp = disp;
        DemoStatStrLen = strlen(DemoStat->text);
    }
}

static void DEMOWriteStats(unsigned char update) {
    unsigned long cnt0;
    unsigned long cnt1;
    unsigned long cnt2;
    unsigned long cnt3;
    unsigned long cnt4;
    unsigned long cnt5;
    unsigned long cnt6;
    unsigned long cnt7;
    unsigned long cnt8;
    unsigned long cnt9;

    switch (DemoStat[DemoStatIndx].stat_type) {
        case DEMO_STAT_GP0:
            cnt0 = GXReadGP0Metric();
            GXSetGPMetric(DemoStat[DemoStatIndx].stat, 0x16);
            GXClearGPMetric();
            if (update) {
                DemoStat[DemoStatIndx].count = cnt0;
            }
            break;
        case DEMO_STAT_GP1:
            cnt0 = GXReadGP1Metric();
            GXSetGPMetric(0x23, DemoStat[DemoStatIndx].stat);
            GXClearGPMetric();
            if (update) {
                DemoStat[DemoStatIndx].count = cnt0;
            }
            break;
        case DEMO_STAT_MEM:
            GXReadMemMetric(&cnt0, &cnt1, &cnt2, &cnt3, &cnt4, &cnt5, &cnt6, &cnt7, &cnt8, &cnt9);
            GXClearMemMetric();
            if (update) {
                cpReq = cnt0;
                tcReq = cnt1;
                cpuRdReq = cnt2;
                cpuWrReq = cnt3;
                dspReq = cnt4;
                ioReq = cnt5;
                viReq = cnt6;
                peReq = cnt7;
                rfReq = cnt8;
                fiReq = cnt9;
            }
            break;
        case DEMO_STAT_PIX:
            GXReadPixMetric(&cnt0, &cnt1, &cnt2, &cnt3, &cnt4, &cnt5);
            GXClearPixMetric();
            if (update) {
                topPixIn = cnt0;
                topPixOut = cnt1;
                botPixIn = cnt2;
                botPixOut = cnt3;
                clrPixIn = cnt4;
                copyClks = cnt5;
            }
            break;
        case DEMO_STAT_VC:
            GXReadVCacheMetric(&cnt0, &cnt1, &cnt2);
            GXSetVCacheMetric(0);
            GXClearVCacheMetric();
            if (update) {
                vcCheck = cnt0;
                vcMiss = cnt1;
                vcStall = cnt2;
            }
            break;
        case DEMO_STAT_FR:
            GXReadPixMetric(&cnt0, &cnt1, &cnt2, &cnt3, &cnt4, &cnt5);
            GXClearPixMetric();
            if (update) {
                topPixIn = cnt0;
                topPixOut = cnt1;
                botPixIn = cnt2;
                botPixOut = cnt3;
                clrPixIn = cnt4;
                copyClks = cnt5;
            }
            DemoStatClocks = GXReadGP0Metric();
            GXSetGPMetric(0x22, 0x16);
            GXClearGPMetric();
            break;
        case DEMO_STAT_TBW:
        case DEMO_STAT_TBP:
            GXReadPixMetric(&cnt0, &cnt1, &cnt2, &cnt3, &cnt4, &cnt5);
            GXClearPixMetric();
            if (update) {
                topPixIn = cnt0;
                topPixOut = cnt1;
                botPixIn = cnt2;
                botPixOut = cnt3;
                clrPixIn = cnt4;
                copyClks = cnt5;
            }
            DemoStatClocks = GXReadGP0Metric();
            GXSetGPMetric(0x22, 0x16);
            GXClearGPMetric();
            GXReadMemMetric(&cnt0, &cnt1, &cnt2, &cnt3, &cnt4, &cnt5, &cnt6, &cnt7, &cnt8, &cnt9);
            GXClearMemMetric();
            tcReq = cnt1;
            break;
        case DEMO_STAT_MYC:
        case DEMO_STAT_MYR:
            break;
        default:
            OSPanic("DEMOStats.c", 0x119, "DEMOSetStats: Unknown demo stat type\n");
    }
}

void DEMOUpdateStats(unsigned char inc) {
    DEMOWriteStats(inc);
    if (inc) {
        DemoStatIndx = DemoStatIndx + 1;
        if (DemoStatIndx == DemoStatMaxIndx) {
            DemoStatIndx = 0;
        }
    }
}

void DEMOPrintStats(void) {
    GXRenderModeObj * rmode;
    unsigned long i;
    signed short text_x;
    signed short text_y;
    signed short text_yinc;
    unsigned short wd;
    unsigned short ht;
    float rate;

    if (DemoStatDisp == DEMO_STAT_IO) {
        for (i = 0; i < DemoStatMaxIndx; i++) {
            switch (DemoStat[i].stat_type) {
                case DEMO_STAT_PIX:
                    switch (DemoStat[i].stat) {
                        case 0:
                            OSReport("%s: %8d\n", DemoStat[i].text, topPixIn);
                            break;
                        case 1:
                            OSReport("%s: %8d\n", DemoStat[i].text, topPixOut);
                            break;
                        case 2:
                            OSReport("%s: %8d\n", DemoStat[i].text, botPixIn);
                            break;
                        case 3:
                            OSReport("%s: %8d\n", DemoStat[i].text, botPixOut);
                            break;
                        case 4:
                            OSReport("%s: %8d\n", DemoStat[i].text, clrPixIn);
                            break;
                        case 5:
                            OSReport("%s: %8d\n", DemoStat[i].text, copyClks);
                            break;
                    }
                    break;
                case DEMO_STAT_FR:
                    rate = 40.0F * (topPixIn + botPixIn) / (float) (DemoStatClocks - copyClks);
                    OSReport("%s: %8.2f\n", DemoStat[i].text, rate);
                    break;
                case DEMO_STAT_TBW:
                    rate = 40.0F * (tcReq << 5) / (float) (DemoStatClocks - copyClks);
                    OSReport("%s: %8.2f\n", DemoStat[i].text, rate);
                    break;
                case DEMO_STAT_TBP:
                    rate = (tcReq << 5) / (float) (topPixIn + botPixIn);
                    OSReport("%s: %8.2f\n", DemoStat[i].text, rate);
                    break;
                case DEMO_STAT_VC:
                    switch (DemoStat[i].stat) {
                        case 0:
                            OSReport("%s: %8d\n", DemoStat[i].text, vcCheck);
                            break;
                        case 1:
                            OSReport("%s: %8d\n", DemoStat[i].text, vcMiss);
                            break;
                        case 2:
                            OSReport("%s: %8d\n", DemoStat[i].text, vcStall);
                            break;
                    }
                    break;
                case DEMO_STAT_MYR:
                    rate = DemoStat[i].stat / (float) DemoStat[i].count;
                    OSReport("%s: %8.2f\n", DemoStat[i].text, rate);
                    break;
                case DEMO_STAT_MEM:
                    switch (DemoStat[i].stat) {
                        case 0:
                            OSReport("%s: %8d\n", DemoStat[i].text, cpReq);
                            break;
                        case 1:
                            OSReport("%s: %8d\n", DemoStat[i].text, tcReq);
                            break;
                        case 2:
                            OSReport("%s: %8d\n", DemoStat[i].text, cpuRdReq);
                            break;
                        case 3:
                            OSReport("%s: %8d\n", DemoStat[i].text, cpuWrReq);
                            break;
                        case 4:
                            OSReport("%s: %8d\n", DemoStat[i].text, dspReq);
                            break;
                        case 5:
                            OSReport("%s: %8d\n", DemoStat[i].text, ioReq);
                            break;
                        case 6:
                            OSReport("%s: %8d\n", DemoStat[i].text, viReq);
                            break;
                        case 7:
                            OSReport("%s: %8d\n", DemoStat[i].text, peReq);
                            break;
                        case 8:
                            OSReport("%s: %8d\n", DemoStat[i].text, rfReq);
                            break;
                        case 9:
                            OSReport("%s: %8d\n", DemoStat[i].text, fiReq);
                            break;
                    }
                    break;
                default:
                    OSReport("%s: %8d\n", DemoStat[i].text, DemoStat[i].count);
                    break;
            }
        }
    } else {
        rmode = DEMOGetRenderModeObj();
        switch (DemoStatDisp) {
            case DEMO_STAT_TL:
                text_x = 0x10;
                text_y = 0x10;
                text_yinc = 0xA;
                wd = rmode->fbWidth;
                ht = rmode->xfbHeight;
                break;
            case DEMO_STAT_BL:
                text_x = 0x10;
                text_y = rmode->xfbHeight - 0x18;
                text_yinc = -0xA;
                wd = rmode->fbWidth;
                ht = rmode->xfbHeight;
                break;
            case DEMO_STAT_TLD:
                text_x = 8;
                text_y = 8;
                text_yinc = 9;
                wd = rmode->fbWidth / 2;
                ht = rmode->xfbHeight / 2;
                break;
            case DEMO_STAT_BLD:
                text_x = 8;
                text_y = (rmode->xfbHeight - 0x18) / 2;
                text_yinc = -9;
                wd = rmode->fbWidth / 2;
                ht = rmode->xfbHeight / 2;
                break;
        }
        DEMOInitCaption(0, wd, ht);
        for (i = 0; i < DemoStatMaxIndx; i++) {
            switch (DemoStat[i].stat_type) {
                case DEMO_STAT_PIX:
                    switch (DemoStat[i].stat) {
                        case 0:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, topPixIn);
                            break;
                        case 1:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, topPixOut);
                            break;
                        case 2:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, botPixIn);
                            break;
                        case 3:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, botPixOut);
                            break;
                        case 4:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, clrPixIn);
                            break;
                        case 5:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, copyClks);
                            break;
                    }
                    break;
                case DEMO_STAT_FR:
                    rate = 40.0F * (topPixIn + botPixIn) / (float) (DemoStatClocks - copyClks);
                    DEMOPrintf(text_x, text_y, 0, "%s: %8.2f\n", DemoStat[i].text, rate);
                    break;
                case DEMO_STAT_TBW:
                    rate = 40.0F * (tcReq << 5) / (float) (DemoStatClocks - copyClks);
                    DEMOPrintf(text_x, text_y, 0, "%s: %8.2f\n", DemoStat[i].text, rate);
                    break;
                case DEMO_STAT_TBP:
                    rate = (tcReq << 5) / (float) (topPixIn - botPixIn);
                    DEMOPrintf(text_x, text_y, 0, "%s: %8.3f\n", DemoStat[i].text, rate);
                    break;
                case DEMO_STAT_VC:
                    switch (DemoStat[i].stat) {
                        case 0:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, vcCheck);
                            break;
                        case 1:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, vcMiss);
                            break;
                        case 2:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, vcStall);
                            break;
                    }
                    break;
                case DEMO_STAT_MEM:
                    switch (DemoStat[i].stat) {
                        case 0:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, cpReq);
                            break;
                        case 1:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, tcReq);
                            break;
                        case 2:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, cpuRdReq);
                            break;
                        case 3:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, cpuWrReq);
                            break;
                        case 4:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, dspReq);
                            break;
                        case 5:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, ioReq);
                            break;
                        case 6:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, viReq);
                            break;
                        case 7:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, peReq);
                            break;
                        case 8:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, rfReq);
                            break;
                        case 9:
                            DEMOPrintf(text_x, text_y, 0, "%s: %8d\n", DemoStat[i].text, fiReq);
                            break;
                    }
                    break;
                case DEMO_STAT_GP0:
                case DEMO_STAT_GP1:
                case DEMO_STAT_MYC:
                    DEMOPrintf(text_x, text_y, 0, "%s: %8d", DemoStat[i].text, DemoStat[i].count);
                    break;
                case DEMO_STAT_MYR:
                    rate = DemoStat[i].stat / (float) DemoStat[i].count;
                    DEMOPrintf(text_x, text_y, 0, "%s: %8.3f", DemoStat[i].text, rate);
                    break;
                default:
                    OSReport("Undefined stat type %d in DEMOPrintStats()\n", DemoStat[i].stat_type);
                    break;
            }
            text_y += text_yinc;
        }
    }
}
