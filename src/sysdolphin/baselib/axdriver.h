#ifndef _AXDRIVER_H_
#define _AXDRIVER_H_

#include <platform.h>

#include "baselib/forward.h"

#define SMSTATE_MASK 0xC0000000

#define SMSTATE_ACTIVE 0x40000000
#define SMSTATE_SLEEP 0x80000000

struct HSD_SM {
    HSD_SM* prev;
    HSD_SM* next;
    u32 flags;
    int vid;
    int pid;
    int fid;
    u8 track;
    u8 pri;
    u8 pri0[2];
    u8 volumeType[2];
    s16 volume[2];
    u16 fadetime;
    u8 pan[2];
    s16 round;
    u8 dp12flag;
    u8 itdflag;
    u8 span[2];
    u8 maxfid;
    s16 pitch[2];
    u8 mix[2];
    u8 mixscale[2];
    u8 filter;
    u8 group;
    u16 loopcount;
    u32* curScore;
    long clock;
};

u8* AXDriverAlloc(s32 size);
void AXDriverFree(void* ptr);
void AXDriverUnlink(HSD_SM* v, HSD_SM** head);
void AXDriverKeyOff(int v);
void HSD_AudioSFXKeyOffAll(void);
void HSD_AudioSFXKeyOffTrack(int track);
s32 AXDriver_8038D4E4(int, s16);

#endif
