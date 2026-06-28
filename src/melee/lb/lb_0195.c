#include "lb_0195.h"

#include "lb_0192.h"
#include "lbaudio_ax.h"
#include "lbcardgame.h"
#include "lbcardnew.h"
#include "lbsnap.h"

#include <dolphin/dvd.h>
#include <dolphin/vi.h>
#include <baselib/controller.h>
#include <baselib/initialize.h>
#include <baselib/sislib.h>
#include <baselib/video.h>

struct lb_804329F0_t {
    union {
        struct UnkArrElem {
            /* 0x00 */ s64 x0;
            /* 0x08 */ s64 x8;
            /* 0x10 */ int x10;
        } x0[2];
        /* 0x00 */ u32 x0_words[12];
    };
    u32 x4;
    u64 x38;
    OSTime x40;
    int x48;
    OSAlarm alarm;
};

/* 4329F0 */ static struct lb_804329F0_t lb_804329F0;

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

void lb_80019628(void)
{
    OSTime period;
    OSTime new_val = lb_804329F0.x38;

    if (new_val == lb_804329F0.x0[0].x0) {
        return;
    }

    lb_804329F0.x0[0].x0 = new_val;

    if (lb_804329F0.x0[0].x8 >= lb_804329F0.x0[0].x0) {
        lb_804329F0.x0_words[3] = 0;
        lb_804329F0.x0_words[2] = 0;
    }

    period = (OSTime) (f32) (u32) OS_TIMER_CLOCK;

    if (lb_804329F0.x0[0].x0 < period) {
        period = lb_804329F0.x0[0].x0;
    }

    if (lb_804329F0.x0[1].x0 < period) {
        period = lb_804329F0.x0[1].x0;
    }

    if (period >= (OSTime) (f64) (0.016666668f * (f32) (u32) OS_TIMER_CLOCK)) {
        period = (OSTime) (f64) (0.016666668f * (f32) (u32) OS_TIMER_CLOCK);
    }

    if (lb_804329F0.x40 == period) {
        return;
    }

    lb_804329F0.x40 = period;

    {
        u32 rate = (u32) (lb_804329F0.x40 / (OS_TIMER_CLOCK / 1000));
        if (rate > 11) {
            rate = 11;
        }
        if (lb_804329F0.x4 != rate) {
            PADSetSamplingRate(rate);
            lb_804329F0.x4 = rate;
        }
    }

    if (lb_804329F0.x48 != 0) {
        OSCancelAlarm(&lb_804329F0.alarm);
    }
    OSCreateAlarm(&lb_804329F0.alarm);
    OSSetPeriodicAlarm(&lb_804329F0.alarm, lb_804329F0.x40, lb_804329F0.x40,
                       (OSAlarmHandler) fn_800195FC);
    lb_804329F0.x48 = 1;
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
