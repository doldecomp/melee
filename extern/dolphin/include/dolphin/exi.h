#ifndef _DOLPHIN_EXI_H_
#define _DOLPHIN_EXI_H_

#include <dolphin/os/OSContext.h>

typedef void (*EXICallback)(s32 chan, OSContext *context);

EXICallback EXISetExiCallback(s32 channel, EXICallback callback);

void EXIInit(void);
BOOL EXILock(s32 channel, u32 device, EXICallback callback);
BOOL EXIUnlock(s32 channel);
BOOL EXISelect(s32 channel, u32 device, u32 frequency);
BOOL EXIDeselect(s32 channel);
BOOL EXIImm(s32 channel, void *buffer, s32 length, u32 type, EXICallback callback);
BOOL EXIImmEx(s32 channel, void *buffer, s32 length, u32 type);
BOOL EXIDma(s32 channel, void *buffer, s32 length, u32 type, EXICallback callback);
BOOL EXISync(s32 channel);
BOOL EXIProbe(s32 channel);
s32 EXIProbeEx(s32 channel);
BOOL EXIAttach(s32 channel, EXICallback callback);
BOOL EXIDetach(s32 channel);
u32 EXIGetState(s32 channel);
s32 EXIGetID(s32 channel, u32 device, u32* id);
void EXIProbeReset(void);

#endif
