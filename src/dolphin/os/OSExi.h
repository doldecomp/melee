#ifndef DOLPHIN_OS_OSEXI_H
#define DOLPHIN_OS_OSEXI_H

#include <dolphin/os/OSInterrupt.h>

typedef struct EXIControl {
    EXICallback exiCallback;
    EXICallback tcCallback;
    EXICallback extCallback;
    vu32 state;
    int immLen;
    u8* immBuf;
    u32 dev;
    u32 id;
    s32 idTime;
    int items;
    struct {
        u32 dev;
        EXICallback callback;
    } queue[3];
} EXIControl;

#define EXI_REG_MAX 5
extern vu32 __EXIRegs[EXI_MAX_CHAN][EXI_REG_MAX] AT_ADDRESS(0xCC006800);

void SetExiInterruptMask(EXIChannel, volatile EXIControl*);
bool EXIImm(EXIChannel, void* buf, s32 len, u32 type, EXICallback);
bool EXIImmEx(EXIChannel, void* buf, s32 len, u32 mode);
bool EXIDma(EXIChannel, void* buf, s32 len, u32 type, EXICallback);
bool EXISync(EXIChannel);
u32 EXIClearInterrupts(EXIChannel, bool exi, bool tc, bool ext);
EXICallback EXISetExiCallback(EXIChannel, EXICallback exiCallback);
bool EXIProbe(EXIChannel);
s32 EXIProbeEx(EXIChannel);
bool EXIAttach(EXIChannel, EXICallback);
bool EXIDetach(EXIChannel);
bool EXISelect(EXIChannel, u32 dev, u32 freq);
bool EXIDeselect(EXIChannel);
void EXIInit(void);
bool EXILock(EXIChannel, u32 dev, EXICallback unlockedCallback);
bool EXIUnlock(EXIChannel);
u32 EXIGetState(EXIChannel);
s32 EXIGetID(EXIChannel, u32 dev, u32* id);

#endif
