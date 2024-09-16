#include "controller.h"

#include "placeholder.h"

#include "baselib/rumble.h"
#include "baselib/util.h"

#include <dolphin/os/OSInterrupt.h>
#include <dolphin/pad/pad.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

HSD_PadStatus default_status_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
PadLibData default_libinfo_data = { 0,    0,    0, 0,    0, 0,    0x2D, 8,
                                    0,    0x1E, 0, 0,    0, 0x7F, 0,    0,
                                    0xFF, 0,    0, 0xFF, 0, 0x7F, 0xFF, 0xFF };
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

static void HSD_PadClampCheck1(u8* val, u8 shift, u8 min, u8 max)
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

static void HSD_PadClampCheck3(s8* x, s8* y, u8 shift, s8 min, s8 max)
{
    f32 r;

    r = sqrtf(((f32) *x * (f32) *x) + ((f32) *y * (f32) *y));

    if (r < min) {
        *y = 0;
        *x = 0;
        return;
    }
    if (r > max) {
        *x = ((f32) *x * (f32) max) / r;
        *y = ((f32) *y * (f32) max) / r;
        r = sqrtf(((f32) *x * (f32) *x) + ((f32) *y * (f32) *y));
    }

    if (shift == 1 && r > 0.0F) {
        *x = (f32) *x - (((f32) *x * (f32) min) / r);
        *y = (f32) *y - (((f32) *y * (f32) min) / r);
    }
}

static void HSD_PadClamp(HSD_PadStatus* mp)
{
    PadLibData* p = &HSD_PadLibData;

    switch (p->clamp_stickType) {
    case 0:
        HSD_PadClampCheck3(&mp->stickX, &mp->stickY, p->clamp_stickShift,
                           p->clamp_stickMin, p->clamp_stickMax);
        HSD_PadClampCheck3(&mp->subStickX, &mp->subStickY, p->clamp_stickShift,
                           p->clamp_stickMin, p->clamp_stickMax);
        break;
    default:
        break;
    }
    HSD_PadClampCheck1(&mp->analogL, HSD_PadLibData.clamp_analogLRShift,
                       p->clamp_analogLRMin, p->clamp_analogLRMax);
    HSD_PadClampCheck1(&mp->analogR, p->clamp_analogLRShift,
                       p->clamp_analogLRMin, p->clamp_analogLRMax);
    HSD_PadClampCheck1(&mp->analogA, p->clamp_analogABShift,
                       p->clamp_analogABMin, p->clamp_analogABMax);
    HSD_PadClampCheck1(&mp->analogB, p->clamp_analogABShift,
                       p->clamp_analogABMin, p->clamp_analogABMax);
}

static void HSD_PadADConvertCheck1(HSD_PadStatus* mp, s8 x, s8 y, u32 up,
                                   u32 down, u32 left, u32 right)
{
    PadLibData* p = &HSD_PadLibData;
    f32 r, a, ha;
    PAD_STACK(8);

    r = sqrtf(((f32) x * (f32) x) + ((f32) y * (f32) y));
    a = atan2f_check(y, x);
    ha = 0.5F * p->adc_angle;
    if (!(r < p->adc_th)) {
        if (a < -2.356194490192345 + ha) {
            mp->button |= left;
        }
        if (a >= -2.356194490192345 - ha && a <= -0.7853981633974483 + ha) {
            mp->button |= down;
        }
        if (a > -0.7853981633974483 - ha && a < 0.7853981633974483 + ha) {
            mp->button |= right;
        }
        if (a >= 0.7853981633974483 - ha && a <= 2.356194490192345 + ha) {
            mp->button |= up;
        }
        if (a > 2.356194490192345 - ha) {
            mp->button |= left;
        }
    }
}

static void HSD_PadADConvert(HSD_PadStatus* mp)
{
    PadLibData* p = &HSD_PadLibData;

    switch (p->adc_type) {
    case 0:
        HSD_PadADConvertCheck1(mp, mp->stickX, mp->stickY, 0x10000, 0x20000,
                               0x40000, 0x80000);
        HSD_PadADConvertCheck1(mp, mp->subStickX, mp->subStickY, 0x100000,
                               0x200000, 0x400000, 0x800000);
        break;
    default:
        return;
    }
}

static void HSD_PadScale(HSD_PadStatus* mp)
{
    PadLibData* p = &HSD_PadLibData;

    mp->nml_stickX = (f32) mp->stickX / (f32) p->scale_stick;
    mp->nml_stickY = (f32) mp->stickY / (f32) p->scale_stick;
    mp->nml_subStickX = (f32) mp->subStickX / (f32) p->scale_stick;
    mp->nml_subStickY = (f32) mp->subStickY / (f32) p->scale_stick;
    mp->nml_analogL = (f32) mp->analogL / (f32) p->scale_analogLR;
    mp->nml_analogR = (f32) mp->analogR / (f32) p->scale_analogLR;
    mp->nml_analogA = (f32) mp->analogA / (f32) p->scale_analogAB;
    mp->nml_analogB = (f32) mp->analogB / (f32) p->scale_analogAB;
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
    int iVar1;
    PadLibData* p;
    HSD_PadStatus* mp;
    PADStatus* qread;
    int i;

    bool intr;

    p = &HSD_PadLibData;
    mp = &HSD_PadMasterStatus[0];
    intr = OSDisableInterrupts();
    if (p->qcount != 0) {
        qread = &p->queue->stat[p->qread * 4];
        HSD_PadRawQueueShift(p->qnum, &p->qread);
        p->qcount -= 1;

        for (i = 0; i < 4; i++, mp += 1, qread += 1) {
            mp->last_button = mp->button;
            mp->err = qread->err;
            if (mp->err == 0) {
                mp->button = qread->button;
                mp->stickX = qread->stickX;
                mp->stickY = qread->stickY;
                mp->subStickX = qread->substickX;
                mp->subStickY = qread->substickY;
                mp->analogL = qread->triggerLeft;
                mp->analogR = qread->triggerRight;
                mp->analogA = qread->analogA;
                mp->analogB = qread->analogB;
                HSD_PadClamp(mp);
                HSD_PadADConvert(mp);
                HSD_PadScale(mp);
                HSD_PadCrossDir(mp);
            } else if (mp->err == -3) {
                mp->err = 0;
            } else {
                mp->button = 0;
                mp->subStickY = 0;
                mp->subStickX = 0;
                mp->stickY = 0;
                mp->stickX = 0;
                mp->analogB = 0;
                mp->analogA = 0;
                mp->analogR = 0;
                mp->analogL = 0;
                mp->nml_subStickY = 0.0;
                mp->nml_subStickX = 0.0;
                mp->nml_stickY = 0.0;
                mp->nml_stickX = 0.0;
                mp->nml_analogB = 0.0;
                mp->nml_analogA = 0.0;
                mp->nml_analogR = 0.0;
                mp->nml_analogL = 0.0;
            }
            mp->trigger = mp->button & (mp->last_button ^ mp->button);
            mp->release = mp->last_button & (mp->last_button ^ mp->button);
            if (mp->last_button ^ mp->button) {
                mp->repeat = mp->trigger;
                mp->repeat_count = p->repeat_start;
            } else {
                iVar1 = mp->repeat_count - 1;
                mp->repeat_count = iVar1;
                if (iVar1 != 0) {
                    mp->repeat = 0;
                } else {
                    mp->repeat = mp->button;
                    mp->repeat_count = p->repeat_interval;
                }
            }
        }
    }
    OSRestoreInterrupts(intr);
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
    }
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

void HSD_PadInit(u8 qnum, HSD_PadData* queue, u16 nb_list,
                 HSD_PadRumbleListData* listdatap)
{
    int i;
    PadLibData* p = &HSD_PadLibData;

    *p = default_libinfo_data;
    p->qnum = qnum;
    p->queue = queue;
    HSD_PadRumbleInit(nb_list, listdatap);
    for (i = 0; i < 4; i++) {
        HSD_PadMasterStatus[i] = default_status_data;
        HSD_PadCopyStatus[i] = default_status_data;
        HSD_PadGameStatus[i] = default_status_data;
    }
    PADInit();
}
