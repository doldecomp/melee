#include "lbcardgame.h"

#include "lbcardgame.static.h"

#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "lb/lbarchive.h"
#include "lb/lbcardnew.h"
#include "lb/lblanguage.h"

#include <dolphin/card.h> // IWYU pragma: keep
#include <dolphin/os.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>

#define _p(x) (lb_80433318.x)

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
        u32 x0;
        u32 x4;
        UNK_T x8;
    } unk_arr[8];
} lb_803BAB74 = { { 0, 3, 0, 0x1790, 0 },
                  NULL,
                  {
                      { 0x1F2C, 1, NULL },
                      { 0x1F2C, 1, NULL },
                      { 0x1F2C, 1, NULL },
                      { 0x1F2C, 1, NULL },
                      { 0x1F2C, 1, NULL },
                      { 0x1F2C, 1, NULL },
                      { 0x1F2C, 1, NULL },
                      { -1, 0, NULL },
                  } };

void lb_8001C600(void)
{
    int prev = _p(x0);
    _p(x0) = CARDProbe(0);
    if (_p(x0) != prev) {
        _p(x4) = 1;
    }
}

const char* lb_8001C658(void)
{
    OSCalendarTime time;
    const char* gamedata_str;
    int i;

    s64 temp_r6 = OSGetTime();
    u32 seconds = OSTicksToSeconds(temp_r6);
    OSTicksToCalendarTime(OSSecondsToTicks((u64) seconds), &time);
    for (i = 0; i < 0x40; i++) {
        _p(_1C)[i] = 0;
    }
    if (lbLang_IsSettingJP()) {
        gamedata_str = "大乱闘スマッシュブラザーズＤＸ  セーブデータ";
    } else {
        gamedata_str = "Super Smash Bros. Melee         Game Data";
    }
    sprintf(_p(_1C), "%s %4d/%02d/%02d", gamedata_str, time.year, time.mon + 1,
            time.mday);
    return _p(_1C);
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
    return _p(x5C)[var_r0];
}

u32 lb_8001C87C(void)
{
    return lb_8001B7E0(0, "SuperSmashBros0110290334", &lb_803BAB74,
                       &lb_803BAB60, &_p(x4));
}

/// #lb_8001C87C

int lb_8001C8BC(void)
{
    HSD_ASSERT(0x140, _p(enable));

    return lb_8001BC18(0, "SuperSmashBros0110290334", (void**) &lb_803BAB74,
                       &lb_803BAB60, lb_8001C658(), lb_8001C820(), _p(x5C)[3],
                       &_p(x4));
}

#pragma push
#pragma dont_inline on
int lb_8001CAF4(void)
{
    int temp_r5 = _p(x4);
    _p(x4) = 0;
    switch (_p(x8)) {
    case 0:
        if (temp_r5 != 0) {
            _p(x8) = 1;
        }
        break;
    case 3:
        if (lb_8001C404(0) != 0) {
            _p(x8) = 4;
        }
        break;
    case 4:
        if (temp_r5 != 0 && lb_8001C404(0) == 0) {
            _p(x8) = 3;
        }
        break;
    }
    return _p(x8);
}
#pragma pop

void lb_8001CBAC(s32 arg0)
{
    _p(x8) = arg0;
}

enum_t lb_8001CBBC(void)
{
    enum_t temp_r3;

    if (lb_8001CAF4() != 0) {
        return 0xD;
    }
    temp_r3 =
        lb_8001BD34(0, "SuperSmashBros0110290334", &lb_803BAB74, &_p(x4));
    if (temp_r3 != 0 && temp_r3 != 2) {
        _p(x8) = 2;
    }
    return temp_r3;
}

void fn_8001CC30(int arg0)
{
    if (arg0 != 0) {
        _p(x8) = 2;
    }
}

bool lb_8001CC4C(void)
{
    return lb_8001BA44(0, "SuperSmashBros0110290334", &_p(x4));
}

static int dont_inline_helper(void)
{
    int temp_r24;

    if (lb_8001CAF4() != 0) {
        return 0xD;
    }

    temp_r24 = lb_8001C820();
    return lb_8001BE30(0, "SuperSmashBros0110290334", &lb_803BAB74,
                       lb_8001C658(), temp_r24, _p(x5C)[3], &_p(x4),
                       fn_8001CC30);
}

void lb_8001CC84(void)
{
    int temp_r24;
    int temp_r3;

    do {
        switch (_p(x10)) {
        case 0:
            if (_p(xC) == 0) {
                break;
            }

            _p(xC) = 0;
            if (_p(x8) != 0) {
                break;
            }

            if (dont_inline_helper() != 0xB) {
                _p(x14) = 1;
            } else {
                _p(x10) = 1;
            }
            break;
        case 1:
            temp_r3 = lb_8001B6F8();
            if (temp_r3 != 0xB) {
                if (temp_r3 != 0) {
                    _p(x14) = 1;
                }
                _p(x10) = temp_r3 = 0;
            }
            break;
        }
    } while (_p(x10) != 1 && _p(xC) != 0);
}

void lb_8001CDB4(void)
{
    while (_p(xC) || _p(x10)) {
        lb_8001CC84();
    }
}

void lb_8001CE00(void)
{
    HSD_ASSERT(0x2A3, _p(enable));
    *gm_GetPowerTime() += gmMainLib_8015FC74();
    _p(xC) = true;
}

u8 lb_8001CE78(void)
{
    lb_8001CAF4();
    if (_p(x8) != 0 && _p(x8) != 4) {
        return GM_MEMCARD;
    }
    return GM_COUNT;
}

void fn_8001CEC0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

void fn_8001CEE4(HSD_GObj* gobj, int arg1)
{
    if (_p(x10) == 1) {
        HSD_GObj_803910D8(gobj, arg1);
    }
}

static float lb_804D3808[][2] = { { 21.5F, 16.5F } };

void lb_8001CF18(void)
{
    if (_p(x64) != NULL) {
        HSD_JObj* jobj;
        HSD_GObj* gobj = GObj_Create(0x18, 0x3D, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(_p(x64)->cameras[0].desc);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_8001CEE4, 0xE);
        gobj->gxlink_prios = 0x80000;

        gobj = GObj_Create(0x18, 0x3D, 0);
        jobj = HSD_JObjLoadJoint(_p(x64)->models[0]->joint);

        HSD_JObjSetTranslateX(jobj, lb_804D3808[_p(x60)][0]);
        HSD_JObjSetTranslateY(jobj, lb_804D3808[_p(x60)][1]);

        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x13, 0);
        HSD_GObj_SetupProc(gobj, fn_8001CEC0, 0);
        gm_8016895C(jobj, _p(x64)->models[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
    }
}

void lb_8001D164(int arg0)
{
    if (_p(x5C) == 0) {
        lbArchive_80016DBC("LbMcGame.", &_p(x5C), "MemCardIconData", 0);
        lbArchive_80016DBC("NtMemAc", &_p(x64), "ScNtcCommon_scene_data", 0);
        _p(x60) = arg0;
        _p(enable) = 1;
    }
}

void lb_8001D1F4(void)
{
    _p(x5C) = NULL;
    _p(x64) = NULL;
    _p(enable) = 0;
    _p(xC) = 0;
    _p(x10) = 0;
    _p(x14) = 0;
}

struct unk {
    u8 pad[0x1F2C];
};

void lb_8001D21C(void)
{
    int i;

    _p(x0) = CARDProbe(0);
    _p(x4) = 0;
    _p(x8) = 0;
    _p(x5C) = NULL;
    _p(x64) = NULL;
    _p(enable) = 0;
    _p(xC) = 0;
    _p(x10) = 0;
    _p(x14) = 0;
    lb_803BAB74.x14 = gmMainLib_GetSaveData();

    for (i = 0; i < 7; i++) {
        struct unk* tmp = gmMainLib_8015CC4C();
        lb_803BAB74.unk_arr[i].x8 = &tmp[i];
    }
}
