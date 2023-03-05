#ifndef SYSDOLPHIN_BASELIB_RUMBLE_H
#define SYSDOLPHIN_BASELIB_RUMBLE_H

#include <dolphin/pad/Pad.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

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

struct Struct804C22E0 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u16 unk4;
    HSD_PadRumbleListData* unk8;
};

void func_80378280(u8, int);

void func_80378128(struct Struct804C22E0* a, HSD_PadRumbleListData* b);
void func_80378170(u8 a);
void func_80378208(void);
void func_80378330_inline(u8 a, int b);
void func_80378330(void);
void func_803783B0(void);
void func_80378430_inline(HSD_PadRumbleListData** r6,
                          HSD_PadRumbleListData* r7);
int func_80378430(u8 a, int b, int c, int d, void* e);
void func_80378524(int a);
int func_80378560(HSD_PadRumbleListData* a, u8* b);
void HSD_PadRumbleInterpret(void);
void HSD_PadRumbleInit(u16 a, void* b);
void HSD_PadRumbleOn(u8 a);
void func_803780DC(u8 a);
void HSD_PadRumbleInterpret_inline(HSD_PadRumbleListData** r6,
                                   HSD_PadRumbleListData* r29);

#endif
