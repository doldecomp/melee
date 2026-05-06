#ifndef _DOLPHIN_MIX_H_
#define _DOLPHIN_MIX_H_

#include <dolphin/ax.h>

struct MIXChannel {
    /* 0x00 */ AXVPB * axvpb;
    /* 0x04 */ u32 mode;
    /* 0x08 */ int input;
    /* 0x0C */ int auxA;
    /* 0x10 */ int auxB;
    /* 0x14 */ int pan;
    /* 0x18 */ int span;
    /* 0x1C */ int fader;
    /* 0x20 */ int l;
    /* 0x24 */ int r;
    /* 0x28 */ int f;
    /* 0x2C */ int b;
    /* 0x30 */ u16 v;
    /* 0x32 */ u16 v1;
    /* 0x34 */ u16 vL;
    /* 0x36 */ u16 vL1;
    /* 0x38 */ u16 vR;
    /* 0x3A */ u16 vR1;
    /* 0x3C */ u16 vS;
    /* 0x3E */ u16 vS1;
    /* 0x40 */ u16 vAL;
    /* 0x42 */ u16 vAL1;
    /* 0x44 */ u16 vAR;
    /* 0x46 */ u16 vAR1;
    /* 0x48 */ u16 vAS;
    /* 0x4A */ u16 vAS1;
    /* 0x4C */ u16 vBL;
    /* 0x4E */ u16 vBL1;
    /* 0x50 */ u16 vBR;
    /* 0x52 */ u16 vBR1;
    /* 0x54 */ u16 vBS;
    /* 0x56 */ u16 vBS1;
};

// mix.c
void MIXInit(void);
void MIXQuit(void);
void MIXInitChannel(AXVPB * axvpb, u32 mode, int input, int auxA, int auxB, int pan, int span, int fader);
void MIXReleaseChannel(AXVPB * axvpb);
void MIXResetControls(AXVPB * p);
void MIXSetInput(AXVPB * p, int dB);
void MIXAdjustInput(AXVPB * p, int dB);
int MIXGetInput(AXVPB * p);
void MIXAuxAPostFader(AXVPB * p);
void MIXAuxAPreFader(AXVPB * p);
int MIXAuxAIsPostFader(AXVPB * p);
void MIXSetAuxA(AXVPB * p, int dB);
void MIXAdjustAuxA(AXVPB * p, int dB);
int MIXGetAuxA(AXVPB * p);
void MIXAuxBPostFader(AXVPB * p);
void MIXAuxBPreFader(AXVPB * p);
int MIXAuxBIsPostFader(AXVPB * p);
void MIXSetAuxB(AXVPB * p, int dB);
void MIXAdjustAuxB(AXVPB * p, int dB);
int MIXGetAuxB(AXVPB * p);
void MIXSetPan(AXVPB * p, int pan);
void MIXAdjustPan(AXVPB * p, int pan);
int MIXGetPan(AXVPB * p);
void MIXSetSPan(AXVPB * p, int span);
void MIXAdjustSPan(AXVPB * p, int span);
int MIXGetSPan(AXVPB * p);
void MIXMute(AXVPB * p);
void MIXUnMute(AXVPB * p);
int MIXIsMute(AXVPB * p);
void MIXSetFader(AXVPB * p, int dB);
void MIXAdjustFader(AXVPB * p, int dB);
int MIXGetFader(AXVPB * p);
void MIXSetDvdStreamFader(int dB);
int MIXGetDvdStreamFader(void);
void MIXUpdateSettings(void);

#endif // _DOLPHIN_MIX_H_
