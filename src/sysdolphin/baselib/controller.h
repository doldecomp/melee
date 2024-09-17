#ifndef _controller_h_
#define _controller_h_

#include <platform.h>

#include "baselib/forward.h"

#include <dolphin/pad.h>

/// @todo Circular dependency
#include "baselib/rumble.h"

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
    /*0x2C*/ RumbleInfo rumble_info;
};

extern HSD_PadStatus HSD_PadMasterStatus[4];
extern HSD_PadStatus HSD_PadGameStatus[4];
extern HSD_PadStatus HSD_PadCopyStatus[4];

void HSD_PadFlushQueue(HSD_FlushType);
u8 HSD_PadGetRawQueueCount(void);
s32 HSD_PadGetResetSwitch(void);
void HSD_PadRenewRawStatus(bool);
void HSD_PadRenewMasterStatus(void);
void HSD_PadRenewGameStatus(void);
void HSD_PadRenewStatus(void);
void HSD_PadReset(void);
void HSD_PadInit(u8, HSD_PadData*, u16, HSD_PadRumbleListData*);

#endif
