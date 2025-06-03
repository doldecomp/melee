#ifndef SYSDOLPHIN_BASELIB_RUMBLE_H
#define SYSDOLPHIN_BASELIB_RUMBLE_H

#include <platform.h>

#include "baselib/forward.h"

#include <dolphin/pad.h>

struct HSD_RumbleData {
    u8 last_status;
    u8 status;
    u8 direct_status;
    u16 nb_list;
    HSD_PadRumbleListData* listdatap;
};

struct RumbleCommand {
    u16 op;
    u16 frame;
};

union HSD_Rumble {
    u16 def;
    RumbleCommand command;
};

struct RumbleInfo {
    u16 max_list;
    u8 unk2;
    HSD_PadRumbleListData* listdatap;
};

struct HSD_PadRumbleListData {
    /*0x00*/ HSD_PadRumbleListData* next;
    /*0x04*/ u32 id;
    /*0x08*/ u8 pause;
    /*0x09*/ u8 pri;
    /*0x0A*/ u8 status;
    /*0x0C*/ u16 loop_count;
    /*0x0E*/ u16 wait;
    /*0x10*/ s32 frame;
    /*0x14*/ /* HSD_Rumble* */ u16* stack;
    /*0x18*/ /* HSD_Rumble* */ u16* listp;
    /*0x1C*/ /* HSD_Rumble* */ u16* headp;
};

void HSD_PadRumbleRemoveId(u8, int);

void HSD_PadRumbleFree(HSD_RumbleData* a, HSD_PadRumbleListData* b);
void HSD_PadRumbleRemove(u8 no);
void HSD_PadRumbleRemoveAll(void);
void HSD_PadRumblePause(u8 no, int status);
void HSD_PadRumblePauseAll(void);
void HSD_PadRumbleUnpauseAll(void);
void func_80378430_inline(HSD_PadRumbleListData** r6,
                          HSD_PadRumbleListData* r7);
int HSD_PadRumbleAdd(u8 no, int id, int frame, int pri, void* listp);
void HSD_Rumble_80378524(int max);
int HSD_PadRumbleInterpret1(HSD_PadRumbleListData* a, u8* b);
void HSD_PadRumbleInterpret(void);
void HSD_PadRumbleInit(u16 a, void* b);
void HSD_PadRumbleOn(u8 no);
void HSD_PadRumbleOffN(u8 no);

#endif
