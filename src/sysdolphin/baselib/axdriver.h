#ifndef _AXDRIVER_H_
#define _AXDRIVER_H_

#include <platform.h>

#include "baselib/forward.h"

#define SMSTATE_MASK 0xC0000000

#define SMSTATE_ACTIVE 0x40000000
#define SMSTATE_SLEEP 0x80000000

typedef enum {
    AXDRIVER_AUX_OFF = 0,
    AXDRIVER_AUX_REVERB_HI = 1,
    AXDRIVER_AUX_REVERB_STD = 2,
    AXDRIVER_AUX_CHORUS = 3,
    AXDRIVER_AUX_DELAY = 4
} AXDriverAuxType;

struct HSD_SM {
    /* 00 */ HSD_SM* prev;
    /* 04 */ HSD_SM* next;
    /* 08 */ u32 flags;
    /* 0C */ int unk;
    /* 10 */ int vID;
    /* 14 */ u16 fid;
    /* 16 */ u16 x16;
    /* 18 */ u8 track;
    /* 19 */ u8 pri;
    /* 1A */ u8 x1A;
    /* 1B */ u8 volume;
    /* 1C */ u8 x1C;
    /* 1D */ u8 pan;
    /* 1E */ u8 x1E;
    /* 20 */ s16 x20;
    /* 22 */ s16 fadetime;
    /* 24 */ u8 x24;
    /* 25 */ u8 x25;
    /* 26 */ u8 x26;
    /* 27 */ u8 x27;
    /* 28 */ u8 dp12flag;
    /* 29 */ u8 itdflag;
    /* 2A */ u16 x2A;
    /* 2C */ u32* cmd_stream;
    /* 30 */ int x30;
};

void* AXDriverAlloc(size_t size);
void AXDriverFree(void* ptr);
void AXDriverUnlink(HSD_SM* v, HSD_SM** head);
bool AXDriverKeyOff(int vid);
void HSD_AudioSFXKeyOffAll(void);
void HSD_AudioSFXKeyOffTrack(int track);
void AXDriver_8038C6C0(HSD_SM* v);
s32 AXDriver_8038D4E4(int, s16);
int AXDriver_8038D9D8(int);
void fn_8038DA5C(int arg0);
int AXDriver_8038E5D4(void);
int AXDriver_8038E5DC(void);
bool AXDriver_8038E844(int);
bool AXDriver_8038E37C(AXDriverAuxType type, void* param);
bool AXDriver_8038E8EC(char* arg0, int arg1, int arg2);
bool AXDriver_8038E968(void);
bool AXDriver_8038E9A8(void);
bool AXDriver_8038E9E0(void);
bool AXDriver_8038EA18(void);
int AXDriverSetupAux(int channel, AXDriverAuxType type, void* param);

#endif
