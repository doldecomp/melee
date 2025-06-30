#include "lbcardgame.h"

#include "lbcardgame.static.h"

#include <dolphin/os.h>
#include <melee/lb/lb_0192.h>
#include <melee/lb/lbarchive.h>
#include <melee/gm/gmmain_lib.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/jobj.h>

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
        cur->x0 = 1.0F/60 * OS_TIMER_CLOCK;
        cur->x8 = 0;
        cur->x10 = 0;
    }

    lb_804329F0.x4 = 0;
    lb_804329F0.x48 = 0;
    lb_804329F0.x0[0].x0 = 0; // huh? overwritten?
    lb_804329F0.x40 = 0;
    lb_804329F0.x38 = 1.0F/60 * OS_TIMER_CLOCK;

    lb_80019628();
}

/// #lb_80019BB8

/// #lb_80019C38

/// #lb_80019CB0

/// #lb_80019EF0

/// #fn_8001A008

/// #fn_8001A0B0

/// #lb_8001A184

/// #lb_8001A3A4

/// #lb_8001A4CC

/// #lb_8001A594

/// #lb_8001A860

/// #lb_8001A8A4

/// #lb_8001A9CC

/// #lb_8001AAE4

/// #lb_8001AC04

/// #lb_8001ACEC

/// #lb_8001AE38

/// #lb_8001AF84

/// #lb_8001B068

/// #lb_8001B14C

/// #lb_8001B614

s32 lb_8001B6E0(s32 arg0)
{
    return lb_80432A68.unk_38[arg0].unk_0;
}

/// #lb_8001B6F8

/// #lb_8001B760

/// #lb_8001B7E0

/// #lb_8001B8C8

/// #lb_8001B99C

/// #lb_8001BA44

/// #lb_8001BB48

/// #lb_8001BC18

/// #lb_8001BD34

/// #lb_8001BE30

/// #lb_8001BF04

/// #lb_8001BFD8

/// #lb_8001C0F4

/// #lb_8001C2D8

int lb_8001C404(int arg0)
{
    s32 sp10;
    s32 spC;
    int probe_result = CARDProbeEx(arg0, &sp10, &spC);

    switch (probe_result) {
    case -1:
    case -2:
    case -3:
        return 0xF;
    case -4:
        return 4;
    case 0:
        return 0;
    case -5:
    case -128:
        return 0xE;
    case -6:
    case -13:
        return 9;
    case -14:
        return 0xD;
    }
}

/// #lb_8001C4A8

/// #lb_8001C550

void lb_8001C5A4(void)
{
    lb_80432A68.unk_0 = lb_80432A68.unk_4 = 0;
}

void lb_8001C5BC(void)
{
    hsd_803B2374();
    lb_80019EF0(0, 0, 0, 0);
    lb_80432A68.x8AC = 0;
}

void lb_8001C600(void)
{
    int prev = lb_80433318.x0;
    lb_80433318.x0 = CARDProbe(0);
    if (lb_80433318.x0 != prev) {
        lb_80433318.x4 = 1;
    }
}

/// #lb_8001C658

#pragma push
#pragma dont_inline on
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
#pragma pop

/// #lb_8001C87C

/// #lb_8001C8BC

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

// TODO file boundary somewhere around here?

void lb_8001CBAC(s32 arg0)
{
    lb_80433318.x8 = arg0;
}

extern UNK_T lb_803BAB74[];

enum_t lb_8001CBBC(void)
{
    enum_t temp_r3;

    if (lb_8001CAF4()) {
        return 0xD;
    }
    temp_r3 = lb_8001BD34(0, "SuperSmashBros0110290334", lb_803BAB74,
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

void lb_8001CC84(void)
{
    s32 temp_r24;
    s32 temp_r3;
    s32 var_r3;

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

            if (lb_8001CAF4() != 0) {
                var_r3 = 0xD;
            } else {
                temp_r24 = lb_8001C820();
                var_r3 = lb_8001BE30(0, "SuperSmashBros0110290334",
                    &lb_803BAB74, lb_8001C658(), temp_r24,
                    lb_80433318.x5C[3], &lb_80433318.x4, fn_8001CC30);
            }

            if (var_r3 != 0xB) {
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

u8 lb_8001CE78(void)
{
    lb_8001CAF4();
    if (lb_80433318.x8 != 0 && lb_80433318.x8 != 4) {
        return 0x29;
    }
    return 0x2D;
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
        __assert("lbcardgame.c", 0x2A3U, "_p(enable)");
    }
    *gmMainLib_8015CD98() += gmMainLib_8015FC74();
    lb_80433318.xC = true;
}

/// #lb_8001CE78

void fn_8001CEC0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

void fn_8001CEE4(HSD_GObj* gobj, u32 arg1)
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
        HSD_CObj* cobj = HSD_CObjLoadDesc(lb_80433318.x64->cameras[0]);
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

// TODO there is a data file boundary at lb_803BAB60
// (lb_803BAB60 is the start of a file's data section)
// lb_80433318 also seems to be its .bss start

void lb_8001D164(int arg0)
{
    if (lb_80433318.x5C == 0) {
        lbArchive_80016DBC("LbMcGame.", (void** ) &lb_80433318.x5C,
                "MemCardIconData", 0);
        lbArchive_80016DBC("NtMemAc", (void** ) &lb_80433318.x64,
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

/// #lb_8001D1F4

/// #lb_8001D21C
