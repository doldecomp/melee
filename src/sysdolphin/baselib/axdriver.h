#ifndef _AXDRIVER_H_
#define _AXDRIVER_H_

#include <platform.h>
#include <placeholder.h>

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
    /* 24 */ u8 x24[2];
    /* 26 */ u8 x26;
    /* 27 */ u8 x27;
    /* 28 */ u8 dp12flag;
    /* 29 */ u8 itdflag;
    /* 2A */ u16 x2A;
    /* 2C */ u32* cmd_stream;
    /* 30 */ int x30;
};

/* 38BB34 */ void* AXDriverAlloc(size_t size);
/* 38BB98 */ void AXDriverFree(void* ptr);
/* 38BB9C */ void AXDriverUnlink(HSD_SM* v, HSD_SM** head);
/* 38BC20 */ bool AXDriverKeyOff(int vid);
/* 38BD6C */ void HSD_AudioSFXKeyOffAll(void);
/* 38BE64 */ void HSD_AudioSFXKeyOffTrack(int track);
/* 38BF6C */ void AXDriver_8038BF6C(HSD_SM* v);
/* 38C678 */ u32 AXDriver_8038C678(u32 param_type, u32 param_value);
/* 38C6C0 */ void AXDriver_8038C6C0(HSD_SM* v);
/* 38CFF4 */ int AXDriver_8038CFF4(int sound_id, u8 volume, u8 pan, int track,
                                   int channel, float pitch);
/* 38D2B4 */ bool AXDriver_8038D2B4(int arg0, u8 arg1);
/* 38D3B8 */ bool AXDriver_8038D3B8(s32 arg0, u8 arg1);
/* 38D4E4 */ bool AXDriver_8038D4E4(s32 arg0, s16 arg1);
/* 38D5B4 */ bool AXDriver_8038D5B4(s32 arg0, s32 arg1, u8 arg2);
/* 38D914 */ bool AXDriver_8038D914(s32 arg0, s32 arg1, s8 arg2);
/* 38D9D8 */ bool AXDriver_8038D9D8(int arg0);
/* 38DA70 */ UNK_RET AXDriver_8038DA70(UNK_PARAMS);
/* 38DCFC */ void AXDriver_8038DCFC(void);
/* 38DD30 */ int AXDriverSetupAux(int channel, AXDriverAuxType type,
                                  void* param);
/* 38E034 */ UNK_RET AXDriver_8038E034(UNK_PARAMS);
/* 38E30C */ bool AXDriver_8038E30C(s32 arg0, s32 arg1, void* arg2, u8* arg3,
                                    u32 arg4);
/* 38E37C */ bool AXDriver_8038E37C(AXDriverAuxType type, void* param);
/* 38E498 */ void AXDriver_8038E498(int arg0, int arg1, int arg2, int arg3);
/* 38E5D4 */ int AXDriver_8038E5D4(void);
/* 38E5DC */ int AXDriver_8038E5DC(void);
/* 38E6C0 */ bool AXDriver_8038E6C0(int arg0);
/* 38E844 */ bool AXDriver_8038E844(int arg0);
/* 38E8EC */ bool AXDriver_8038E8EC(const char* arg0, int arg1, int arg2);
/* 38E968 */ bool AXDriverStop(void);
/* 38E9A8 */ bool AXDriverPause(void);
/* 38E9E0 */ bool AXDriverResume(void);
/* 38EA18 */ bool AXDriver_8038EA18(void);

#endif
