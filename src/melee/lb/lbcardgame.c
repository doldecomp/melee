#include "lbcardgame.h"

#include "lbcardgame.static.h"

#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "lb/lbarchive.h"
#include "lb/lbcardnew.h"
#include "lb/lblanguage.h"

#include <dolphin/card.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/hsd_3AA7.h>
#include <sysdolphin/baselib/jobj.h>

static struct {
    u32 x0, x4, x8;
    u32 pad[2];
} lb_803BAB60 = {
    0x2000100,
    0,
    0x300,
};

static struct {
    u32 pad[5];
    struct gmm_x1868* x14;
    struct {
        UNK_T x0;
        UNK_T x4;
        UNK_T x8;
    } unk_arr[8];
} lb_803BAB74 = {
    0, // TODO
};

void lb_8001C600(void)
{
    int prev = lb_80433318.x0;
    lb_80433318.x0 = CARDProbe(0);
    if (lb_80433318.x0 != prev) {
        lb_80433318.x4 = 1;
    }
}

const char* lb_8001C658(void)
{
    OSCalendarTime time;
    const char* gamedata_str;
    int i;

    s64 temp_r6 = OSGetTime();
    temp_r6 /= OS_TIMER_CLOCK;
    OSTicksToCalendarTime(OSSecondsToTicks(temp_r6), &time);
    for (i = 0; i < 0x40; i++) {
        lb_80433318._1C[i] = 0;
    }
    if (lbLang_IsSettingJP()) {
        gamedata_str = "大乱闘スマッシュブラザーズＤＸ  セーブデータ";
    } else {
        gamedata_str = "Super Smash Bros. Melee         Game Data";
    }
    sprintf(lb_80433318._1C, "%s %4d/%02d/%02d", gamedata_str, time.year,
            time.mon + 1, time.mday);
    return lb_80433318._1C;
}

int lb_8001C820(void)
{
    int var_r0;

    if (un_80304470() != 0) {
        var_r0 = 2;
    } else if (gm_80164ABC() != 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    return lb_80433318.x5C[var_r0];
}

u32 lb_8001C87C(void)
{
    return lb_8001B7E0(0, "SuperSmashBros0110290334", &lb_803BAB74,
                       &lb_803BAB60, &lb_80433318.x4);
}

/// #lb_8001C87C

int lb_8001C8BC(void)
{
    if (!lb_80433318.enable) {
        __assert("lbcardgame.c", 0x140, "_p(enable)");
    }

    return lb_8001BC18(0, "SuperSmashBros0110290334", (void**) &lb_803BAB74,
                       &lb_803BAB60, lb_8001C658(), lb_8001C820(),
                       lb_80433318.x5C[3], &lb_80433318.x4);
}

#pragma push
#pragma dont_inline on
int lb_8001CAF4(void)
{
    int temp_r5 = lb_80433318.x4;
    lb_80433318.x4 = 0;
    switch (lb_80433318.x8) {
    case 0:
        if (temp_r5 != 0) {
            lb_80433318.x8 = 1;
        }
        break;
    case 3:
        if (lb_8001C404(0) != 0) {
            lb_80433318.x8 = 4;
        }
        break;
    case 4:
        if (temp_r5 != 0 && lb_8001C404(0) == 0) {
            lb_80433318.x8 = 3;
        }
        break;
    }
    return lb_80433318.x8;
}
#pragma pop

void lb_8001CBAC(s32 arg0)
{
    lb_80433318.x8 = arg0;
}

enum_t lb_8001CBBC(void)
{
    enum_t temp_r3;

    if (lb_8001CAF4() != 0) {
        return 0xD;
    }
    temp_r3 = lb_8001BD34(0, "SuperSmashBros0110290334", &lb_803BAB74,
                          &lb_80433318.x4);
    if (temp_r3 != 0 && temp_r3 != 2) {
        lb_80433318.x8 = 2;
    }
    return temp_r3;
}

void fn_8001CC30(int arg0)
{
    if (arg0 != 0) {
        lb_80433318.x8 = 2;
    }
}

bool lb_8001CC4C(void)
{
    return lb_8001BA44(0, "SuperSmashBros0110290334", &lb_80433318.x4);
}

static int dont_inline_helper(void)
{
    int temp_r24;

    if (lb_8001CAF4() != 0) {
        return 0xD;
    }

    temp_r24 = lb_8001C820();
    return lb_8001BE30(0, "SuperSmashBros0110290334", &lb_803BAB74,
                       lb_8001C658(), temp_r24, lb_80433318.x5C[3],
                       &lb_80433318.x4, fn_8001CC30);
}

void lb_8001CC84(void)
{
    int temp_r24;
    int temp_r3;
    int var_r3;

    do {
        switch (lb_80433318.x10) {
        case 0:
            if (lb_80433318.xC == 0) {
                break;
            }

            lb_80433318.xC = 0;
            if (lb_80433318.x8 != 0) {
                break;
            }

            if (dont_inline_helper() != 0xB) {
                lb_80433318.x14 = 1;
            } else {
                lb_80433318.x10 = 1;
            }
            break;
        case 1:
            temp_r3 = lb_8001B6F8();
            if (temp_r3 != 0xB) {
                if (temp_r3 != 0) {
                    lb_80433318.x14 = 1;
                }
                lb_80433318.x10 = 0;
            }
            break;
        }
    } while (lb_80433318.x10 != 1 && lb_80433318.xC != 0);
}

void lb_8001CDB4(void)
{
    while (lb_80433318.xC || lb_80433318.x10) {
        lb_8001CC84();
    }
}

void lb_8001CE00(void)
{
    if (!lb_80433318.enable) {
        __assert("lbcardgame.c", 0x2A3, "_p(enable)");
    }
    *gmMainLib_8015CD98() += gmMainLib_8015FC74();
    lb_80433318.xC = true;
}

u8 lb_8001CE78(void)
{
    lb_8001CAF4();
    if (lb_80433318.x8 != 0 && lb_80433318.x8 != 4) {
        return 0x29;
    }
    return 0x2D;
}

void fn_8001CEC0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

void fn_8001CEE4(HSD_GObj* gobj, int arg1)
{
    if (lb_80433318.x10 == 1) {
        HSD_GObj_803910D8(gobj, arg1);
    }
}

static float lb_804D3808[][2] = { { 21.5F, 16.5F } };

void lb_8001CF18(void)
{
    if (lb_80433318.x64 != NULL) {
        HSD_JObj* jobj;
        HSD_GObj* gobj = GObj_Create(0x18, 0x3D, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(lb_80433318.x64->cameras[0].desc);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_8001CEE4, 0xE);
        gobj->gxlink_prios = 0x80000;

        gobj = GObj_Create(0x18, 0x3D, 0);
        jobj = HSD_JObjLoadJoint(lb_80433318.x64->models[0]->joint);

        HSD_JObjSetTranslateX(jobj, lb_804D3808[lb_80433318.x60][0]);
        HSD_JObjSetTranslateY(jobj, lb_804D3808[lb_80433318.x60][1]);

        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x13, 0);
        HSD_GObjProc_8038FD54(gobj, fn_8001CEC0, 0);
        gm_8016895C(jobj, lb_80433318.x64->models[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
    }
}

void lb_8001D164(int arg0)
{
    if (lb_80433318.x5C == 0) {
        lbArchive_80016DBC("LbMcGame.", &lb_80433318.x5C, "MemCardIconData",
                           0);
        lbArchive_80016DBC("NtMemAc", &lb_80433318.x64,
                           "ScNtcCommon_scene_data", 0);
        lb_80433318.x60 = arg0;
        lb_80433318.enable = 1;
    }
}

void lb_8001D1F4(void)
{
    lb_80433318.x5C = NULL;
    lb_80433318.x64 = NULL;
    lb_80433318.enable = 0;
    lb_80433318.xC = 0;
    lb_80433318.x10 = 0;
    lb_80433318.x14 = 0;
}

struct unk {
    u8 pad[0x1F2C];
};

void lb_8001D21C(void)
{
    int i;

    lb_80433318.x0 = CARDProbe(0);
    lb_80433318.x4 = 0;
    lb_80433318.x8 = 0;
    lb_80433318.x5C = NULL;
    lb_80433318.x64 = NULL;
    lb_80433318.enable = 0;
    lb_80433318.xC = 0;
    lb_80433318.x10 = 0;
    lb_80433318.x14 = 0;
    lb_803BAB74.x14 = gmMainLib_8015CC40();

    for (i = 0; i < 7; i++) {
        struct unk* tmp = gmMainLib_8015CC4C();
        lb_803BAB74.unk_arr[i].x8 = &tmp[i];
    }
}
