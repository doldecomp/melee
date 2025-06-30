#include "lbcardnew.h"

#include "lbcardnew.static.h"

#include <dolphin/card.h>
#include <melee/lb/lb_0192.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/hsd_3AA7.h>

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

    switch (CARDProbeEx(arg0, &sp10, &spC)) {
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
