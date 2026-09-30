/**
 * @file controller.h
 * @brief GameCube Controller Input Processing
 * @details Handles polling of raw PAD status, deadzone clamping, analog stick scaling, queue processing, and button event tracking (presses, releases, holds).
 */

#ifndef _controller_h_
#define _controller_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/pad.h>
#include <sysdolphin/baselib/rumble.h>

typedef u32 HSD_Pad;

#define HSD_PAD_DPADLEFT (1 << 0)
#define HSD_PAD_DPADRIGHT (1 << 1)
#define HSD_PAD_DPADDOWN (1 << 2)
#define HSD_PAD_DPADUP (1 << 3)
#define HSD_PAD_Z (1 << 4)
#define HSD_PAD_R (1 << 5)
#define HSD_PAD_L (1 << 6)
#define HSD_PAD_7 (1 << 7)

/// @remarks Also covers Z-Button macro in-game.
#define HSD_PAD_A (1 << 8)

#define HSD_PAD_B (1 << 9)
#define HSD_PAD_X (1 << 10)
#define HSD_PAD_Y (1 << 11)
#define HSD_PAD_START (1 << 12)

/// Digital input of either L or R
#define HSD_PAD_LR (1 << 31)

#define HSD_PAD_AB (HSD_PAD_A | HSD_PAD_B)
#define HSD_PAD_XY (HSD_PAD_X | HSD_PAD_Y)

#define PAD_ERR_NO_CONTROLLER -1

typedef enum _HSD_FlushType {
    HSD_PAD_FLUSH_QUEUE_MERGE,
    HSD_PAD_FLUSH_QUEUE_THROWAWAY,
    HSD_PAD_FLUSH_QUEUE_LEAVE1,
    HSD_PAD_FLUSH_QUEUE_TERMINATE,
} HSD_FlushType;

struct HSD_PadData {
    PADStatus stat[4];
};

struct HSD_PadStatus {
    u32 button;
    u32 last_button;
    u32 trigger;
    u32 repeat;
    u32 release;
    s32 repeat_count;
    s8 stickX;
    s8 stickY;
    s8 subStickX;
    s8 subStickY;
    u8 analogL;
    u8 analogR;
    u8 analogA;
    u8 analogB;
    f32 nml_stickX;
    f32 nml_stickY;
    f32 nml_subStickX;
    f32 nml_subStickY;
    f32 nml_analogL;
    f32 nml_analogR;
    f32 nml_analogA;
    f32 nml_analogB;
    u8 cross_dir;
    s8 err;
};

struct PadLibData {
    /*0x00*/ u8 qnum;
    /*0x01*/ u8 qread;
    /*0x02*/ u8 qwrite;
    /*0x03*/ u8 qcount;
    /*0x04*/ u8 qtype;
    /*0x08*/ HSD_PadData* queue;
    /*0x0C*/ s32 repeat_start;
    /*0x10*/ s32 repeat_interval;
    /*0x14*/ s8 adc_type;
    /*0x15*/ s8 adc_th;
    /*0x18*/ f32 adc_angle;
    /*0x1C*/ u8 clamp_stickType;
    /*0x1D*/ u8 clamp_stickShift;
    /*0x1E*/ s8 clamp_stickMax;
    /*0x1F*/ s8 clamp_stickMin;
    /*0x20*/ u8 clamp_analogLRShift;
    /*0x21*/ u8 clamp_analogLRMax;
    /*0x22*/ u8 clamp_analogLRMin;
    /*0x23*/ u8 clamp_analogABShift;
    /*0x24*/ u8 clamp_analogABMax;
    /*0x25*/ u8 clamp_analogABMin;
    /*0x26*/ s8 scale_stick;
    /*0x27*/ u8 scale_analogLR;
    /*0x28*/ u8 scale_analogAB;
    /*0x29*/ u8 cross_dir;
    /*0x2A*/ u8 reset_switch_status;
    /*0x2B*/ u8 reset_switch;
    /*0x2C*/ struct RumbleInfo rumble_info;
};

extern HSD_PadStatus HSD_PadMasterStatus[4];
extern HSD_PadStatus HSD_PadGameStatus[4];
extern HSD_PadStatus HSD_PadCopyStatus[4];

/**
 * @brief Retrieves the normalized Main Stick Y axis value for a given port
 * @param slot The controller port index (0-3)
 * @return Normalized Y value between -1.0 and 1.0
 */
static inline float HSD_PadGetNmlStickY(u8 slot)
{
    return HSD_PadCopyStatus[slot].nml_stickY;
}

/**
 * @brief Retrieves the normalized C-Stick Y axis value for a given port
 * @param slot The controller port index (0-3)
 * @return Normalized Y value between -1.0 and 1.0
 */
static inline float HSD_PadGetNmlSubStickY(u8 slot)
{
    return HSD_PadCopyStatus[slot].nml_subStickY;
}

/**
 * @brief Flushes the controller input queue according to the specified flush type
 * @param ftype The flush strategy to employ
 */
void HSD_PadFlushQueue(HSD_FlushType ftype);

/**
 * @brief Gets the number of unprocessed elements currently in the raw controller input queue
 * @return The number of items in the queue
 */
u8 HSD_PadGetRawQueueCount(void);

/**
 * @brief Checks if the hardware reset switch is currently engaged
 * @return Non-zero if pressed, zero otherwise
 */
s32 HSD_PadGetResetSwitch(void);

/**
 * @brief Polls physical GameCube controllers and pushes the status into the raw queue
 * @param err_check If true, requires at least one port to return successfully
 */
void HSD_PadRenewRawStatus(bool err_check);

/**
 * @brief Reads from the raw input queue, processes deadzones and repeats, and updates Master status
 */
void HSD_PadRenewMasterStatus(void);

/**
 * @brief Copies the processed inputs from Master status into the Copy status struct
 */
void HSD_PadRenewCopyStatus(void);

/**
 * @brief Copies the processed inputs from Master status into the Game status struct
 */
void HSD_PadRenewGameStatus(void);

/**
 * @brief Fully renews controller state by calling raw, master, copy, and game updates sequentially
 */
void HSD_PadRenewStatus(void);

/**
 * @brief Resets and recalibrates all physical controllers, clears queues, and halts rumble
 */
void HSD_PadReset(void);

/**
 * @brief Initializes the HSD pad library and underlying GameCube PAD subsystem
 * @param qnum Number of items the queue can hold
 * @param queue Pointer to the allocated queue buffer
 * @param nb_list Max number of rumble events
 * @param listdatap Pointer to allocated rumble event buffer
 */
void HSD_PadInit(u8 qnum, HSD_PadData* queue, u16 nb_list, HSD_PadRumbleListData* listdatap);

extern PadLibData HSD_PadLibData;

#endif
