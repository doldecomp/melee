#ifndef DOLPHIN_AI_AI
#define DOLPHIN_AI_AI

#include <Runtime/platform.h>

typedef void (*AISCallback)(u32 count);
typedef void (*AIDCallback)(void);

extern vu32 __AIRegs[8] AT_ADDRESS(0xCC006C00);

AIDCallback AIRegisterDMACallback(AIDCallback);
void AIInitDMA(u32 addr, u32 length);
void AIStartDMA(void);
void AISetStreamPlayState(u32 state);
u32 AIGetStreamPlayState(void);
void AISetDSPSampleRate(u32 rate);
u32 AIGetDSPSampleRate(void);
void AISetStreamSampleRate(u32 rate);
u32 AIGetStreamSampleRate(void);
void AISetStreamVolLeft(u8 volume);
u8 AIGetStreamVolLeft(void);
void AISetStreamVolRight(u8 volume);
u8 AIGetStreamVolRight(void);
void AIInit(u8* stack);
void AIResetStreamSampleCount(void);
void AISetStreamTrigger(u32 trigger);

#endif // DOLPHIN_AI_AI
