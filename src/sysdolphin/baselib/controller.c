#include "controller.h"

#include "placeholder.h"

#include "baselib/rumble.h"

#include <dolphin/os/OSInterrupt.h>
#include <dolphin/pad/pad.h>

PadLibData HSD_PadLibData;
HSD_PadStatus HSD_PadMasterStatus[4];
HSD_PadStatus HSD_PadCopyStatus[4];
HSD_PadStatus HSD_PadGameStatus[4];

u8 HSD_PadGetRawQueueCount(void)
{
    u8 queue_count;
    u32 intr;
    PadLibData* p;

    p = &HSD_PadLibData;
    intr = OSDisableInterrupts();
    queue_count = p->qcount;
    OSRestoreInterrupts(intr);

    return queue_count;
}

s32 HSD_PadGetResetSwitch(void)
{
    PadLibData* p = &HSD_PadLibData;

    return (p->reset_switch != 0) ? true : false;
}

static void HSD_PadRawQueueShift(u8 qnum, u8* qptr)
{
    *qptr = (*qptr + 1) % qnum;
}

static void HSD_PadRawMerge(PADStatus* src1, PADStatus* src2, PADStatus* dst)
{
    int i;
    for (i = 0; i < 4; i++) {
        dst[i].button = src1[i].button | src2[i].button;
    }
}

void HSD_PadFlushQueue(HSD_FlushType ftype)
{
    PadLibData* p;
    PADStatus* qdst;
    PADStatus* qread;
    bool intr;

    p = &HSD_PadLibData;
    intr = OSDisableInterrupts();
    switch (ftype) {
    case HSD_PAD_FLUSH_QUEUE_MERGE:
        for (; p->qcount > 1; p->qcount -= 1) {
            qread = &p->queue->stat[p->qread * 4];
            HSD_PadRawQueueShift(p->qnum, &p->qread);
            qdst = &p->queue->stat[p->qread * 4];
            HSD_PadRawMerge(qread, qdst, qdst);
        }
        break;
    case HSD_PAD_FLUSH_QUEUE_THROWAWAY:
        p->qread = p->qwrite;
        p->qcount = 0;
        break;
    case HSD_PAD_FLUSH_QUEUE_LEAVE1:
        if (p->qcount > 1) {
            p->qread = p->qwrite != 0 ? p->qwrite - 1 : p->qnum - 1;
            p->qcount = 1;
        }
        break;
    }
    OSRestoreInterrupts(intr);
}

void HSD_PadClampCheck1(u8* val, u8 shift, u8 min, u8 max)
{
    if (*val < min) {
        *val = 0;
        return;
    }
    if (*val > max) {
        *val = max;
    }
    if (shift != 1) {
        return;
    }
    *val = *val - min;
}

static void HSD_PadCrossDir(HSD_PadStatus* mp)
{
    switch (HSD_PadLibData.cross_dir) {
    case 0:
        break;

    case 1:
        if ((mp->button & 0xC) == 0) {
            return;
        }
        mp->button = mp->button & 0xFFFFFFFC;
        return;

    case 2:
        if ((mp->button & 0x3) == 0) {
            return;
        }
        mp->button = mp->button & 0xFFFFFFF3;
        return;

    case 3:
        if ((mp->button & 0xC) != 0) {
            if ((mp->button & 3) != 0) {
                if (mp->cross_dir == 1) {
                    mp->button = mp->button & 0xFFFFFFFC;
                    return;
                }
                mp->button = mp->button & 0xFFFFFFF3;
                return;
            } else {
                mp->cross_dir = 1;
                return;
            }
        }
        if ((mp->button & 3) != 0) {
            mp->cross_dir = 2;
            return;
        }
    }
}

void HSD_PadRenewMasterStatus(void)
{
    NOT_IMPLEMENTED;
}

void HSD_PadRenewCopyStatus(void)
{
    int iVar1;
    HSD_PadStatus* mp;
    HSD_PadStatus* cp;
    PadLibData* p;

    int i;

    p = &HSD_PadLibData;
    for (i = 0; i < 4; i++) {
        mp = &HSD_PadMasterStatus[i];
        cp = &HSD_PadCopyStatus[i];

        cp->last_button = cp->button;
        cp->err = mp->err;
        if (cp->err == 0) {
            cp->button = mp->button;
            cp->stickX = mp->stickX;
            cp->stickY = mp->stickY;
            cp->subStickX = mp->subStickX;
            cp->subStickY = mp->subStickY;
            cp->analogL = mp->analogL;
            cp->analogR = mp->analogR;
            cp->analogA = mp->analogA;
            cp->analogB = mp->analogB;
            cp->nml_stickX = mp->nml_stickX;
            cp->nml_stickY = mp->nml_stickY;
            cp->nml_subStickX = mp->nml_subStickX;
            cp->nml_subStickY = mp->nml_subStickY;
            cp->nml_analogL = mp->nml_analogL;
            cp->nml_analogR = mp->nml_analogR;
            cp->nml_analogA = mp->nml_analogA;
            cp->nml_analogB = mp->nml_analogB;
        } else {
            cp->button = 0;
            cp->subStickY = 0;
            cp->subStickX = 0;
            cp->stickY = 0;
            cp->stickX = 0;
            cp->analogB = 0;
            cp->analogA = 0;
            cp->analogR = 0;
            cp->analogL = 0;
            cp->nml_subStickY = 0.0;
            cp->nml_subStickX = 0.0;
            cp->nml_stickY = 0.0;
            cp->nml_stickX = 0.0;
            cp->nml_analogB = 0.0;
            cp->nml_analogA = 0.0;
            cp->nml_analogR = 0.0;
            cp->nml_analogL = 0.0;
        }
        cp->trigger = cp->button & (cp->last_button ^ cp->button);
        cp->release = cp->last_button & (cp->last_button ^ cp->button);
        if (cp->last_button ^ cp->button) {
            cp->repeat = cp->trigger;
            cp->repeat_count = p->repeat_start;
        } else {
            iVar1 = cp->repeat_count - 1;
            cp->repeat_count = iVar1;
            if (iVar1 != 0) {
                cp->repeat = 0;
            } else {
                cp->repeat = cp->button;
                cp->repeat_count = p->repeat_interval;
            }
        }
    };
    return;
}

void HSD_PadRenewGameStatus(void)
{
    int iVar1;
    HSD_PadStatus* mp;
    HSD_PadStatus* gs;
    PadLibData* p;

    int i;

    p = &HSD_PadLibData;
    for (i = 0; i < 4; i++) {
        mp = &HSD_PadMasterStatus[i];
        gs = &HSD_PadGameStatus[i];

        gs->last_button = gs->button;
        gs->err = mp->err;
        if (gs->err == 0) {
            gs->button = mp->button;
            gs->stickX = mp->stickX;
            gs->stickY = mp->stickY;
            gs->subStickX = mp->subStickX;
            gs->subStickY = mp->subStickY;
            gs->analogL = mp->analogL;
            gs->analogR = mp->analogR;
            gs->analogA = mp->analogA;
            gs->analogB = mp->analogB;
            gs->nml_stickX = mp->nml_stickX;
            gs->nml_stickY = mp->nml_stickY;
            gs->nml_subStickX = mp->nml_subStickX;
            gs->nml_subStickY = mp->nml_subStickY;
            gs->nml_analogL = mp->nml_analogL;
            gs->nml_analogR = mp->nml_analogR;
            gs->nml_analogA = mp->nml_analogA;
            gs->nml_analogB = mp->nml_analogB;
        } else {
            gs->button = 0;
            gs->subStickY = 0;
            gs->subStickX = 0;
            gs->stickY = 0;
            gs->stickX = 0;
            gs->analogB = 0;
            gs->analogA = 0;
            gs->analogR = 0;
            gs->analogL = 0;
            gs->nml_subStickY = 0.0;
            gs->nml_subStickX = 0.0;
            gs->nml_stickY = 0.0;
            gs->nml_stickX = 0.0;
            gs->nml_analogB = 0.0;
            gs->nml_analogA = 0.0;
            gs->nml_analogR = 0.0;
            gs->nml_analogL = 0.0;
        }
        gs->trigger = gs->button & (gs->last_button ^ gs->button);
        gs->release = gs->last_button & (gs->last_button ^ gs->button);
        if (gs->last_button ^ gs->button) {
            gs->repeat = gs->trigger;
            gs->repeat_count = p->repeat_start;
        } else {
            iVar1 = gs->repeat_count - 1;
            gs->repeat_count = iVar1;
            if (iVar1 != 0) {
                gs->repeat = 0;
            } else {
                gs->repeat = gs->button;
                gs->repeat_count = p->repeat_interval;
            }
        }
    };
    return;
}

void HSD_PadRenewStatus(void)
{
    HSD_PadRenewRawStatus(0);
    HSD_PadRenewMasterStatus();
    HSD_PadRenewCopyStatus();
    HSD_PadRenewGameStatus();
}

void HSD_PadReset(void)
{
    PadLibData* p;
    bool intr;
    int i;

    p = &HSD_PadLibData;
    intr = OSDisableInterrupts();

    HSD_PadRumbleRemoveAll();

    for (i = 0; i < 4; ++i) {
        HSD_PadRumbleOffN(i);
    }

    HSD_PadFlushQueue(HSD_PAD_FLUSH_QUEUE_THROWAWAY);
    PADRecalibrate(0xF0000000);
    p->reset_switch = 0;

    OSRestoreInterrupts(intr);
}
