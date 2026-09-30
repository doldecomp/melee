/**
 * @file controller.c
 * @brief GameCube Controller Input Processing
 * @details Handles polling of raw PAD status, deadzone clamping, analog stick scaling, queue processing, and button event tracking (presses, releases, holds).
 */

#include "controller.h"

#include <math.h>

#include "rumble.h"
#include <dolphin/os.h>
#include <dolphin/pad.h>

HSD_PadStatus default_status_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
PadLibData default_libinfo_data = { 0,    0,    0, 0,    0, 0,    0x2D, 8,
                                    0,    0x1E, 0, 0,    0, 0x7F, 0,    0,
                                    0xFF, 0,    0, 0xFF, 0, 0x7F, 0xFF, 0xFF };
PadLibData HSD_PadLibData;
HSD_PadStatus HSD_PadMasterStatus[4];
HSD_PadStatus HSD_PadCopyStatus[4];
HSD_PadStatus HSD_PadGameStatus[4];
const u32 pad_bit[4] = { PAD_CHAN0_BIT, PAD_CHAN1_BIT, PAD_CHAN2_BIT,
                         PAD_CHAN3_BIT };

/**
 * @brief Gets the number of unprocessed elements currently in the raw controller input queue
 * @return The number of items in the queue
 */
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

/**
 * @brief Checks if the hardware reset switch is currently engaged
 * @return Non-zero if pressed, zero otherwise
 */
s32 HSD_PadGetResetSwitch(void)
{
    PadLibData* p = &HSD_PadLibData;

    return (p->reset_switch != 0) ? true : false;
}

/**
 * @brief Helper function to wrap a queue index counter
 * @param qnum Total capacity of the queue
 * @param qptr Pointer to the current index
 */
static void HSD_PadRawQueueShift(u8 qnum, u8* qptr)
{
    *qptr = (*qptr + 1) % qnum;
}

/**
 * @brief Merges button presses from two raw pad status arrays using a bitwise OR
 * @param src1 First source array of PADStatus (4 ports)
 * @param src2 Second source array of PADStatus (4 ports)
 * @param dst Destination array to write the merged bitmasks
 */
static void HSD_PadRawMerge(PADStatus* src1, PADStatus* src2, PADStatus* dst)
{
    int i;
    for (i = 0; i < 4; i++) {
        dst[i].button = src1[i].button | src2[i].button;
    }
}

/**
 * @brief Polls physical GameCube controllers and pushes the status into the raw queue
 * @param err_check If true, requires at least one port to return successfully
 */
void HSD_PadRenewRawStatus(bool err_check)
{
    int i;
    u32 mask;
    PadLibData* p = &HSD_PadLibData;
    HSD_PadData* qwrite;
    PADStatus* qread;
    HSD_PadData current_pad_data;

    HSD_PadRumbleInterpret();
    PADRead(current_pad_data.stat);
    if (err_check) {
        for (i = 0; i < 4; i++) {
            if (!current_pad_data.stat[i].err) {
                break;
            }
        }
        if (i == 4) {
            return;
        }
    }

    qwrite = &p->queue[p->qwrite];
    if (p->qcount == p->qnum) {
        switch (p->qtype) {
        case 0:
            HSD_PadRawQueueShift(p->qnum, &p->qread);
            qread = p->queue[p->qread].stat;
            if (p->qnum != 1) {
                HSD_PadRawMerge(qwrite->stat, qread, qread);
            } else {
                HSD_PadRawMerge(current_pad_data.stat, qread, current_pad_data.stat);
            }
            break;
        case 1:
            HSD_PadRawQueueShift(p->qnum, &p->qread);
            break;
        case 2:
            goto skip;
        }
    } else {
        p->qcount += 1;
    }

    *qwrite = current_pad_data;
    HSD_PadRawQueueShift(p->qnum, &p->qwrite);

skip:
    mask = 0;
    for (i = 0; i < 4; i++) {
        if (current_pad_data.stat[i].err == -1) {
            mask |= pad_bit[i];
        }
    }
    if (mask != 0) {
        PADReset(mask);
    }
    if (OSGetResetSwitchState()) {
        p->reset_switch_status = 1;
    } else {
        if (p->reset_switch_status != 0) {
            p->reset_switch = 1;
            p->reset_switch_status = 0;
        }
    }
}

/**
 * @brief Flushes the controller input queue according to the specified flush type
 * @param ftype The flush strategy to employ
 */
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
    default:
        break;
    }
    OSRestoreInterrupts(intr);
}

/**
 * @brief Checks if an analog single-axis 1D value falls within the deadzone or exceeds max clamping
 * @param val Pointer to the analog value
 * @param shift Boolean flag to shift value closer to zero by the deadzone amount
 * @param min Deadzone threshold below which value is zeroes
 * @param max Max magnitude cap
 */
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

/**
 * @brief Checks if a 2D analog stick vector falls within the deadzone or exceeds max clamping radius
 * @param x Pointer to X-axis value
 * @param y Pointer to Y-axis value
 * @param shift Boolean flag to subtract deadzone minimum from radius magnitude
 * @param min Deadzone radius threshold
 * @param max Max radius limit
 */
static void HSD_PadClampCheck3(s8* x, s8* y, u8 shift, s8 min, s8 max)
{
    f32 radius;

    radius = sqrtf(((f32) *x * (f32) *x) + ((f32) *y * (f32) *y));

    if (radius < min) {
        *y = 0;
        *x = 0;
        return;
    }
    if (radius > max) {
        *x = ((f32) *x * (f32) max) / radius;
        *y = ((f32) *y * (f32) max) / radius;
        radius = sqrtf(((f32) *x * (f32) *x) + ((f32) *y * (f32) *y));
    }

    if (shift == 1 && radius > 1.000000013351432e-10f) {
        *x = (f32) *x - (((f32) *x * (f32) min) / radius);
        *y = (f32) *y - (((f32) *y * (f32) min) / radius);
    }
}

/**
 * @brief Applies all deadzone and magnitude checks on sticks and triggers
 * @param mp Pointer to the HSD_PadStatus to process
 */
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

/**
 * @brief Squares a float
 */
static inline f32 sq(f32 x)
{
    return x * x;
}

/**
 * @brief Returns the squared distance from the origin for a 2D float vector
 */
static inline f32 vec2DSqDist(f32 x, f32 y)
{
    f32 ret;
    ret = (x * x) + (y * y);
    return ret;
}

/**
 * @brief Returns the length/magnitude of a 2D byte vector
 */
static inline f32 vec2Dlen(s8 x, s8 y)
{
    return sqrtf(vec2DSqDist(x, y));
}

/**
 * @brief Emulates digital direction inputs depending on the angle of the analog stick
 * @param mp HSD_PadStatus pointer to mutate buttons on
 * @param x Stick X
 * @param y Stick Y
 * @param up Up bitflag to assign
 * @param down Down bitflag to assign
 * @param left Left bitflag to assign
 * @param right Right bitflag to assign
 */
static void HSD_PadADConvertCheck1(HSD_PadStatus* mp, s8 x, s8 y, u32 up,
                                   u32 down, u32 left, u32 right)
{
    PadLibData* p = &HSD_PadLibData;
    f32 radius;
    f32 angle;
    f32 half_angle;

    radius = sq(x);
    radius = vec2Dlen(x, y);

    if (fabs(x) == 0.0f) {
        angle = y >= 0 ? 1.5707963267948966 : -1.5707963267948966;
    } else {
        angle = (f32) atan2f(y, x);
    }

    half_angle = 0.5F * p->adc_angle;
    if (radius < p->adc_th) {
        return;
    }

    if (angle < -2.356194490192345 + half_angle) {
        mp->button |= left;
    }
    if (angle >= -2.356194490192345 - half_angle && angle <= -0.7853981633974483 + half_angle) {
        mp->button |= down;
    }
    if (angle > -0.7853981633974483 - half_angle && angle < 0.7853981633974483 + half_angle) {
        mp->button |= right;
    }
    if (angle >= 0.7853981633974483 - half_angle && angle <= 2.356194490192345 + half_angle) {
        mp->button |= up;
    }
    if (angle > 2.356194490192345 - half_angle) {
        mp->button |= left;
    }
}

/**
 * @brief Processes sticks to apply analog-to-digital button conversions
 * @param mp Pointer to the HSD_PadStatus to process
 */
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

/**
 * @brief Normalizes the raw byte stick coordinates into floats by dividing them against scaling factors
 * @param mp Pointer to the HSD_PadStatus to process
 */
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

/**
 * @brief Resolves and filters mutually exclusive D-Pad directions
 * @param pad_status Pointer to the HSD_PadStatus to process
 */
static void HSD_PadCrossDir(HSD_PadStatus* pad_status)
{
    switch (HSD_PadLibData.cross_dir) {
    case 0:
        break;

    case 1:
        if ((pad_status->button & (PAD_BUTTON_DOWN | PAD_BUTTON_UP)) == 0) {
            return;
        }
        pad_status->button = pad_status->button & ~(PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT);
        return;

    case 2:
        if ((pad_status->button & (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)) == 0) {
            return;
        }
        pad_status->button = pad_status->button & ~(PAD_BUTTON_DOWN | PAD_BUTTON_UP);
        return;

    case 3:
        if ((pad_status->button & (PAD_BUTTON_DOWN | PAD_BUTTON_UP)) != 0) {
            if ((pad_status->button & (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)) != 0) {
                if (pad_status->cross_dir == 1) {
                    pad_status->button =
                        pad_status->button & ~(PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT);
                    return;
                }
                pad_status->button = pad_status->button & ~(PAD_BUTTON_DOWN | PAD_BUTTON_UP);
                return;
            } else {
                pad_status->cross_dir = 1;
                return;
            }
        }
        if ((pad_status->button & (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)) != 0) {
            pad_status->cross_dir = 2;
            return;
        }
    }
}

/**
 * @brief Reads from the raw input queue, processes deadzones and repeats, and updates Master status
 */
void HSD_PadRenewMasterStatus(void)
{
    int remaining_repeat_count;
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
                remaining_repeat_count = mp->repeat_count - 1;
                mp->repeat_count = remaining_repeat_count;
                if (remaining_repeat_count != 0) {
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

/**
 * @brief Helper function to copy processed inputs natively
 * @param dst Destination HSD_PadStatus
 * @param src Source HSD_PadStatus
 */
static inline void HSD_PadCopyStatusFields(HSD_PadStatus* dst,
                                           HSD_PadStatus* src)
{
    dst->button = src->button;
    dst->stickX = src->stickX;
    dst->stickY = src->stickY;
    dst->subStickX = src->subStickX;
    dst->subStickY = src->subStickY;
    dst->analogL = src->analogL;
    dst->analogR = src->analogR;
    dst->analogA = src->analogA;
    dst->analogB = src->analogB;
    dst->nml_stickX = src->nml_stickX;
    dst->nml_stickY = src->nml_stickY;
    dst->nml_subStickX = src->nml_subStickX;
    dst->nml_subStickY = src->nml_subStickY;
    dst->nml_analogL = src->nml_analogL;
    dst->nml_analogR = src->nml_analogR;
    dst->nml_analogA = src->nml_analogA;
    dst->nml_analogB = src->nml_analogB;
}

/**
 * @brief Helper function to clear processed inputs
 * @param dst Destination HSD_PadStatus
 */
static inline void HSD_PadClearStatusFields(HSD_PadStatus* dst)
{
    dst->button = 0;
    dst->subStickY = 0;
    dst->subStickX = 0;
    dst->stickY = 0;
    dst->stickX = 0;
    dst->analogB = 0;
    dst->analogA = 0;
    dst->analogR = 0;
    dst->analogL = 0;
    dst->nml_subStickY = 0.0;
    dst->nml_subStickX = 0.0;
    dst->nml_stickY = 0.0;
    dst->nml_stickX = 0.0;
    dst->nml_analogB = 0.0;
    dst->nml_analogA = 0.0;
    dst->nml_analogR = 0.0;
    dst->nml_analogL = 0.0;
}

/**
 * @brief Copies the processed inputs from Master status into the Copy status struct
 */
void HSD_PadRenewCopyStatus(void)
{
    int remaining_repeat_count;
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
            HSD_PadCopyStatusFields(cp, mp);
        } else {
            HSD_PadClearStatusFields(cp);
        }
        cp->trigger = cp->button & (cp->last_button ^ cp->button);
        cp->release = cp->last_button & (cp->last_button ^ cp->button);
        if (cp->last_button ^ cp->button) {
            cp->repeat = cp->trigger;
            cp->repeat_count = p->repeat_start;
        } else {
            remaining_repeat_count = cp->repeat_count - 1;
            cp->repeat_count = remaining_repeat_count;
            if (remaining_repeat_count != 0) {
                cp->repeat = 0;
            } else {
                cp->repeat = cp->button;
                cp->repeat_count = p->repeat_interval;
            }
        }
    }
}

/**
 * @brief Copies the processed inputs from Master status into the Game status struct
 */
void HSD_PadRenewGameStatus(void)
{
    int remaining_repeat_count;
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
            HSD_PadCopyStatusFields(gs, mp);
        } else {
            HSD_PadClearStatusFields(gs);
        }
        gs->trigger = gs->button & (gs->last_button ^ gs->button);
        gs->release = gs->last_button & (gs->last_button ^ gs->button);
        if (gs->last_button ^ gs->button) {
            gs->repeat = gs->trigger;
            gs->repeat_count = p->repeat_start;
        } else {
            remaining_repeat_count = gs->repeat_count - 1;
            gs->repeat_count = remaining_repeat_count;
            if (remaining_repeat_count != 0) {
                gs->repeat = 0;
            } else {
                gs->repeat = gs->button;
                gs->repeat_count = p->repeat_interval;
            }
        }
    };
    return;
}

/**
 * @brief Fully renews controller state by calling raw, master, copy, and game updates sequentially
 */
void HSD_PadRenewStatus(void)
{
    HSD_PadRenewRawStatus(0);
    HSD_PadRenewMasterStatus();
    HSD_PadRenewCopyStatus();
    HSD_PadRenewGameStatus();
}

/**
 * @brief Resets and recalibrates all physical controllers, clears queues, and halts rumble
 */
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

/**
 * @brief Initializes the HSD pad library and underlying GameCube PAD subsystem
 * @param qnum Number of items the queue can hold
 * @param queue Pointer to the allocated queue buffer
 * @param nb_list Max number of rumble events
 * @param listdatap Pointer to allocated rumble event buffer
 */
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
