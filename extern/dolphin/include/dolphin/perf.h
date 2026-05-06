#ifndef _DOLPHIN_PERF_H_
#define _DOLPHIN_PERF_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 PERFId;

typedef enum 
{
    PERF_CPU_EVENT,
    PERF_CPU_GP_EVENT,
    PERF_GP_EVENT,
} PerfType;

struct Frame {
    // total size: 0x10
    struct PerfSample * samples; // offset 0x0, size 0x4
    long lastSample; // offset 0x4, size 0x4
    unsigned long end; // offset 0x8, size 0x4
    unsigned long cachemisscycles; // offset 0xC, size 0x4
};

struct PerfEvent {
    // total size: 0x10
    char * name; // offset 0x0, size 0x4
    PerfType type; // offset 0x4, size 0x4
    long currSample; // offset 0x8, size 0x4
    struct _GXColor color; // offset 0xC, size 0x4
};

typedef struct PerfSample {
    /* 0x00 */ u8 id;
    /* 0x04 */ u32 cpuTimeStampStart;
    /* 0x08 */ u32 cpuTimeStampEnd;
    /* 0x0C */ u32 gpTimeStampStart;
    /* 0x10 */ u32 gpTimeStampEnd;
    /* 0x14 */ int interrupted;
    /* 0x18 */ u32 origcpuStart;
    /* 0x1C */ u32 origgpStart;
    /* 0x20 */ u32 cacheMisses[4];
    /* 0x30 */ u32 instructions[4];
    /* 0x40 */ u32 cpReq[2];
    /* 0x48 */ u32 tcReq[2];
    /* 0x50 */ u32 cpuRdReq[2];
    /* 0x58 */ u32 cpuWrReq[2];
    /* 0x60 */ u32 dspReq[2];
    /* 0x68 */ u32 ioReq[2];
    /* 0x70 */ u32 viReq[2];
    /* 0x78 */ u32 peReq[2];
    /* 0x80 */ u32 rfReq[2];
    /* 0x88 */ u32 fiReq[2];
    /* 0x90 */ u32 xfWaitIn[2];
    /* 0x98 */ u32 xfWaitOut[2];
    /* 0xA0 */ u32 rasBusy[2];
    /* 0xA8 */ u32 rasClocks[2];
} PerfSample;

typedef void *(*PERFAllocator)(u32 size);
typedef void (*PERFDeallocator)(void *block);
typedef void (*PERFDrawCallback)(void);

extern void (* GameDrawInit)(); // size: 0x4, address: 0x14

u32 PERFInit(u32 numSamples, u32 numFramesHistory, u32 numTypes,
    PERFAllocator allocator, PERFDeallocator deallocator, PERFDrawCallback initDraw);
void PERFEventStart(PERFId id);
void PERFEventEnd(PERFId id);
void PERFSetEvent(PERFId id, char *name, PerfType type);
void PERFStartFrame(void);
void PERFEndFrame(void);
void PERFStartAutoSampling(f32 msInterval);
void PERFStopAutoSampling(void);

void PERFPreDraw();
void PERFDumpScreen();
void PERFPostDraw();
void PERFSetDrawBWBarKey(int tf);
void PERFSetDrawBWBar(int tf);
void PERFSetDrawCPUBar(int tf);
void PERFSetDrawXFBars(int tf);
void PERFSetDrawRASBar(int tf);
void PERFToggleDrawBWBarKey();
void PERFToggleDrawBWBar();
void PERFToggleDrawCPUBar();
void PERFToggleDrawXFBars();
void PERFToggleDrawRASBar();

extern struct Frame * PERFFrames; // size: 0x4, address: 0x0
extern unsigned long PERFCurrFrame; // size: 0x4, address: 0x0
extern struct PerfEvent * PERFEvents; // size: 0x4, address: 0x0

#ifdef __cplusplus
}
#endif

#endif
