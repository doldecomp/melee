#include "lb_0192.h"

#include "lbcardgame.h"
#include "lbcardnew.h"

#include <dolphin/dvd.h>
#include <sysdolphin/baselib/controller.h>

/* 019230 */ static enum_t lb_80019230(void);

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

enum_t lb_80019230(void)
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

void lb_800195D0(void)
{
    lb_800192A8(lb_8001955C);
    lb_8001CC84();
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
