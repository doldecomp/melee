#include "lb_0192.h"

#include "lbaudio_ax.h"
#include "lblanguage.h"

#include "gm/gmmain_lib.h"
#include "gm/types.h"

#include <dolphin/dvd.h>
#include <dolphin/vi.h>
#include <baselib/controller.h>
#include <baselib/initialize.h>
#include <baselib/sislib.h>
#include <baselib/video.h>

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

/* 4D63D0 */ static HSD_Text* lb_804D63D0;

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
            text->font_size.x = 0.67F;
            text->font_size.y = 0.75F;
        } else {
            HSD_Text* text = lb_804D63D0;
            text->font_size.x = 0.58F;
            text->font_size.y = 0.70F;
        }
        lb_804D63D0->default_alignment = 1;
        lb_804D63D0->default_kerning = 1;
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, -68.0F, "%s", jp_msg[i].x0);
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, -34.0F, "%s", jp_msg[i].x4);
            HSD_SisLib_803A6B98(lb_804D63D0, 0.0F, 0.0F, "%s", jp_msg[i].x8);
        } else {
            if ((!lb_804D63D0) && (!lb_804D63D0)) {
            }
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
