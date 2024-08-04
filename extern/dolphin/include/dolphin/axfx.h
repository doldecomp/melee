#ifndef _DOLPHIN_AXFX_H_
#define _DOLPHIN_AXFX_H_

struct AXFX_REVSTD_DELAYLINE {
    /* 0x00 */ long inPoint;
    /* 0x04 */ long outPoint;
    /* 0x08 */ long length;
    /* 0x0C */ float * inputs;
    /* 0x10 */ float lastOutput;
};

struct AXFX_REVSTD_WORK {
    /* 0x000 */ struct AXFX_REVSTD_DELAYLINE AP[6];
    /* 0x078 */ struct AXFX_REVSTD_DELAYLINE C[6];
    /* 0x0F0 */ float allPassCoeff;
    /* 0x0F4 */ float combCoef[6];
    /* 0x10C */ float lpLastout[3];
    /* 0x118 */ float level;
    /* 0x11C */ float damping;
    /* 0x120 */ long preDelayTime;
    /* 0x124 */ float * preDelayLine[3];
    /* 0x130 */ float * preDelayPtr[3];
};

struct AXFX_REVERBSTD {
    /* 0x000 */ struct AXFX_REVSTD_WORK rv;
    /* 0x13C */ u8 tempDisableFX;
    /* 0x140 */ float coloration;
    /* 0x144 */ float mix;
    /* 0x148 */ float time;
    /* 0x14C */ float damping;
    /* 0x150 */ float preDelay;
};

struct AXFX_BUFFERUPDATE {
    /* 0x00 */ long * left;
    /* 0x04 */ long * right;
    /* 0x08 */ long * surround;
};

// REVHI Structs

struct AXFX_REVHI_DELAYLINE {
    /* 0x00 */ long inPoint;
    /* 0x04 */ long outPoint;
    /* 0x08 */ long length;
    /* 0x0C */ float * inputs;
    /* 0x10 */ float lastOutput;
};

struct AXFX_REVHI_WORK {
    /* 0x000 */ struct AXFX_REVHI_DELAYLINE AP[9];
    /* 0x0B4 */ struct AXFX_REVHI_DELAYLINE C[9];
    /* 0x168 */ float allPassCoeff;
    /* 0x16C */ float combCoef[9];
    /* 0x190 */ float lpLastout[3];
    /* 0x19C */ float level;
    /* 0x1A0 */ float damping;
    /* 0x1A4 */ long preDelayTime;
    /* 0x1A8 */ float crosstalk;
    /* 0x1AC */ float * preDelayLine[3];
    /* 0x1B8 */ float * preDelayPtr[3];
};

struct AXFX_REVERBHI {
    /* 0x000 */ struct AXFX_REVHI_WORK rv;
    /* 0x1C4 */ u8 tempDisableFX;
    /* 0x1C8 */ float coloration;
    /* 0x1CC */ float mix;
    /* 0x1D0 */ float time;
    /* 0x1D4 */ float damping;
    /* 0x1D8 */ float preDelay;
    /* 0x1DC */ float crosstalk;
};

struct AXFX_DELAY {
    /* 0x00 */ u32 currentSize[3];
    /* 0x0C */ u32 currentPos[3];
    /* 0x18 */ u32 currentFeedback[3];
    /* 0x24 */ u32 currentOutput[3];
    /* 0x30 */ long * left;
    /* 0x34 */ long * right;
    /* 0x38 */ long * sur;
    /* 0x3C */ u32 delay[3];
    /* 0x48 */ u32 feedback[3];
    /* 0x54 */ u32 output[3];
};

struct AXFX_CHORUS_SRCINFO {
    /* 0x00 */ long * dest;
    /* 0x04 */ long * smpBase;
    /* 0x08 */ long * old;
    /* 0x0C */ u32 posLo;
    /* 0x10 */ u32 posHi;
    /* 0x14 */ u32 pitchLo;
    /* 0x18 */ u32 pitchHi;
    /* 0x1C */ u32 trigger;
    /* 0x20 */ u32 target;
};

struct AXFX_CHORUS_WORK {
    /* 0x00 */ long * lastLeft[3];
    /* 0x0C */ long * lastRight[3];
    /* 0x18 */ long * lastSur[3];
    /* 0x24 */ u8 currentLast;
    /* 0x28 */ long oldLeft[4];
    /* 0x38 */ long oldRight[4];
    /* 0x48 */ long oldSur[4];
    /* 0x58 */ u32 currentPosLo;
    /* 0x5C */ u32 currentPosHi;
    /* 0x60 */ long pitchOffset;
    /* 0x64 */ u32 pitchOffsetPeriodCount;
    /* 0x68 */ u32 pitchOffsetPeriod;
    /* 0x6C */ struct AXFX_CHORUS_SRCINFO src;
};

struct AXFX_CHORUS {
    /* 0x00 */ struct AXFX_CHORUS_WORK work;
    /* 0x90 */ u32 baseDelay;
    /* 0x94 */ u32 variation;
    /* 0x98 */ u32 period;
};

// chorus.c
int AXFXChorusInit(struct AXFX_CHORUS * c);
int AXFXChorusShutdown(struct AXFX_CHORUS * c);
int AXFXChorusSettings(struct AXFX_CHORUS * c);
void AXFXChorusCallback(struct AXFX_BUFFERUPDATE * bufferUpdate, struct AXFX_CHORUS * chorus);

// delay.c
void AXFXDelayCallback(struct AXFX_BUFFERUPDATE * bufferUpdate, struct AXFX_DELAY * delay);
int AXFXDelaySettings(struct AXFX_DELAY * delay);
int AXFXDelayInit(struct AXFX_DELAY * delay);
int AXFXDelayShutdown(struct AXFX_DELAY * delay); 

// reverb_hi.c
void DoCrossTalk(long * l, long * r, float cross, float invcross);
int AXFXReverbHiInit(struct AXFX_REVERBHI * rev);
int AXFXReverbHiShutdown(struct AXFX_REVERBHI * rev);
int AXFXReverbHiSettings(struct AXFX_REVERBHI * rev);
void AXFXReverbHiCallback(struct AXFX_BUFFERUPDATE * bufferUpdate, struct AXFX_REVERBHI * reverb);

// reverb_std.c
int AXFXReverbStdInit(struct AXFX_REVERBSTD * rev);
int AXFXReverbStdShutdown(struct AXFX_REVERBSTD * rev);
int AXFXReverbStdSettings(struct AXFX_REVERBSTD * rev);
void AXFXReverbStdCallback(struct AXFX_BUFFERUPDATE * bufferUpdate, struct AXFX_REVERBSTD * reverb);

#endif // _DOLPHIN_AXFX_H_
