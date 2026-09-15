#ifndef _DOLPHIN_OSRTC_H_
#define _DOLPHIN_OSRTC_H_

#ifdef __cplusplus
extern "C" {
#endif

// make the assert happy
#define OS_SOUND_MODE_MONO 0
#define OS_SOUND_MODE_STEREO 1

// make the asserts happy
#define OS_VIDEO_MODE_NTSC 0
#define OS_VIDEO_MODE_MPAL 2

struct SramControl {
    unsigned char sram[64];
    u32 offset;
    int enabled;
    int locked;
    int sync;
    void (*callback)();
};

typedef struct OSSram {
    unsigned short checkSum;
    unsigned short checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    signed char displayOffsetH;
    unsigned char ntd;
    unsigned char language;
    unsigned char flags;
} OSSram;

typedef struct OSSramEx {
    unsigned char flashID[2][12];
    u32 wirelessKeyboardID;
    unsigned short wirelessPadID[4];
    unsigned char dvdErrorCode;
    unsigned char _padding0;
    unsigned char flashIDCheckSum[2];
    unsigned char _padding1[4];
} OSSramEx;

u32 OSGetSoundMode();
void OSSetSoundMode(u32 mode);
u32 OSGetVideoMode();
void OSSetVideoMode(u32 mode);
unsigned char OSGetLanguage();
void OSSetLanguage(unsigned char language);
u32 OSGetProgressiveMode(void);
void OSSetProgressiveMode(u32 mode);
u16 OSGetWirelessID(s32);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSRTC_H_
