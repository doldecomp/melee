#include "lb_0192.h"

#include <dolphin/dvd.h>
#include <dolphin/vi.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/initialize.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/video.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbsnap.h>

static struct strings {
    const char* x0;
    const char* x4;
    const char* x8;
} jp_msg[6] = {
    {
        "",
        "ディスクカバーを閉めてください。",
        "",
    },
    {
        "",
        "スマッシュブラザーズＤＸのディスクをセットしてください。",
        "",
    },
    {
        "このディスクは",
        "スマッシュブラザーズＤＸのディスクではありません。",
        "スマッシュブラザーズＤＸのディスクをセットしてください。",
    },
    {
        "ディスクを読めませんでした。",
        "詳しくは本体の取扱説明書をお読みください。",
        "",
    },
    {
        "エラーが発生しました。",
        "本体のパワーボタンを押して電源をＯＦＦにし、",
        "本体の取扱説明書の指示にしたがってください。",
    },
    {
        "",
        "ディスクを読み込んでいます。",
        "",
    },
};

static struct strings us_msg[6] = {
    {
        "",
        "Close the Disc Cover.",
        "",
    },
    {
        "",
        "Insert the Super Smash Bros. Melee Game Disc.",
        "",
    },
    {
        "The inserted Game Disc is not",
        "Super Smash Bros. Melee.",
        "Insert the Super Smash Bros. Melee Game Disc.",
    },
    {
        "The Game Disc could not be read.",
        "Read the NINTENDO GAMECUBE Instruction Booklet",
        "for more information.",
    },
    {
        "An error has occurred. Turn the power OFF and",
        "check the NINTENDO GAMECUBE Instruction Booklet",
        "for further instructions.",
    },
    {
        "",
        "Reading the Game Disc...",
        "",
    },
};

static HSD_Text* lb_804D63D0;

struct lb_804329F0_t {
    struct UnkArrElem {
        /* 0x00 */ s64 x0;
        /* 0x08 */ s64 x8;
        /* 0x10 */ int x10;
    } x0[2];
    u32 x4;
    u64 x38;
    u64 x40;
    int x48;
    OSAlarm alarm;
};

/* 4329F0 */ static struct lb_804329F0_t lb_804329F0;

#pragma push
#pragma dont_inline on
static enum_t lb_80019230(void)
{
    switch (DVDGetDriveStatus()) {
    case 5:
        return 0;
    case 4:
        return 1;
    case 6:
        return 2;
    case 11:
        return 3;
    case -1:
        return 4;
    case 1:
        return 5;
    default:
        return -1;
    }
}
#pragma pop

void lb_800192A8(void (*cb)(void))
{
    int prev_i = -1;
    int i = lb_80019230();

    PAD_STACK(8);

    if (i != -1 && i != 5) {
        lbAudioAx_80024F08();
        HSD_Rumble_80378524(1);
        lb_804D63D0 = HSD_SisLib_803A6754(0, -1);
        if (lbLang_IsSavedLanguageJP()) {
            HSD_Text* text = lb_804D63D0;
            text->x24.x = 0.67F;
            text->x24.y = 0.75F;
        } else {
            HSD_Text* text = lb_804D63D0;
            text->x24.x = 0.58F;
            text->x24.y = 0.70F;
        }
        lb_804D63D0->x4A = 1;
        lb_804D63D0->x49 = 1;
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, -68.0F, "%s", jp_msg[i].x0);
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, -34.0F, "%s", jp_msg[i].x4);
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, 0.0F, "%s", jp_msg[i].x8);
        } else {
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, -68.0F, "%s", us_msg[i].x0);
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, -34.0F, "%s", us_msg[i].x4);
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, 0.0F, "%s", us_msg[i].x8);
        }

        while (true) {
            if (i != prev_i) {
                prev_i = i;
                if (i != -1) {
                    if (lbLang_IsSavedLanguageJP()) {
                        HSD_SisLib_803A70A0(lb_804D63D0, 0, "%s",
                                            jp_msg[i].x0);
                        HSD_SisLib_803A70A0(lb_804D63D0, 1, "%s",
                                            jp_msg[i].x4);
                        HSD_SisLib_803A70A0(lb_804D63D0, 2, "%s",
                                            jp_msg[i].x8);
                    } else {
                        HSD_SisLib_803A70A0(lb_804D63D0, 0, "%s",
                                            us_msg[i].x0);
                        HSD_SisLib_803A70A0(lb_804D63D0, 1, "%s",
                                            us_msg[i].x4);
                        HSD_SisLib_803A70A0(lb_804D63D0, 2, "%s",
                                            us_msg[i].x8);
                    }
                }
            }
            GXInvalidateVtxCache();
            GXInvalidateTexAll();
            HSD_StartRender(HSD_RP_SCREEN);
            HSD_SisLib_803A84BC(NULL, (u32) lb_804D63D0);
            HSD_Init_803755A8();
            HSD_VICopyXFBAsync(HSD_RP_SCREEN);
            if (cb != NULL) {
                cb();
            }
            if (i == -1) {
                break;
            }
            i = lb_80019230();
        }

        lbAudioAx_80024F6C();
        HSD_Rumble_80378524(0);
        HSD_SisLib_803A5CC4(lb_804D63D0);
        gmMainLib_8046B0F0.xC = true;
    }
}

void lb_8001955C(void)
{
    if (HSD_PadGetResetSwitch()) {
        lbAudioAx_80027DBC();
        do {
        } while (lb_8001B6F8() == 0xB);
        VISetPostRetraceCallback(0);
        VISetPreRetraceCallback(0);
        VISetBlack(1);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        OSResetSystem(0, 0, 0);
    }
    lb_8001B6F8();
    lb_8001CC84();
}

void lb_800195D0(void)
{
    lb_800192A8(lb_8001955C);
    lb_8001CC84();
}

void fn_800195FC(void)
{
    HSD_PadRenewRawStatus(0);
    lb_8001C600();
    lbSnap_8001D2BC();
}

void lb_80019880(u64 arg0)
{
    lb_804329F0.x38 = arg0;
}

u8 lb_80019894(void)
{
    u8 count;
    int enabled = OSDisableInterrupts();
    count = HSD_PadGetRawQueueCount();
    lb_80019628();
    OSRestoreInterrupts(enabled);
    return count;
}

void lb_800198E0(void)
{
    HSD_PadRenewMasterStatus();
}

void lb_80019900(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        lb_804329F0.x0[i].x8 += lb_804329F0.x40;
        if (lb_804329F0.x0[i].x8 >= lb_804329F0.x0[i].x0) {
            lb_804329F0.x0[i].x8 -= lb_804329F0.x0[i].x0;
            lb_804329F0.x0[i].x10 = true;
        } else {
            lb_804329F0.x0[i].x10 = false;
        }
    }

    if (lb_80019A30(0)) {
        HSD_PadRenewGameStatus();
    }
    if (lb_80019A30(0)) {
        HSD_PadRenewCopyStatus();
    }
}

bool lb_80019A30(int index)
{
    return lb_804329F0.x0[index].x10;
}

void lb_80019A48(void)
{
    int enabled = OSDisableInterrupts();

    if (lb_804329F0.x48) {
        OSCancelAlarm(&lb_804329F0.alarm);
        lb_804329F0.x48 = 0;
    }
    OSRestoreInterrupts(enabled);
}

void lb_80019AAC(Event arg0)
{
    int i;

    arg0();

    for (i = 0; i < 2; i++) {
        struct UnkArrElem* cur = &lb_804329F0.x0[i];
        cur->x0 = 1.0F / 60 * OS_TIMER_CLOCK;
        cur->x8 = 0;
        cur->x10 = 0;
    }

    lb_804329F0.x4 = 0;
    lb_804329F0.x48 = 0;
    lb_804329F0.x0[0].x0 = 0; // huh? overwritten?
    lb_804329F0.x40 = 0;
    lb_804329F0.x38 = 1.0F / 60 * OS_TIMER_CLOCK;

    lb_80019628();
}
