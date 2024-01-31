#ifndef DOLPHIN_OS_OSEXI_H
#define DOLPHIN_OS_OSEXI_H

#include <platform.h>

#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>

typedef void (*EXICallback)(s32 chan, OSContext* context);

typedef enum {
    EXI_STATE_DMA_ACCESS = (1 << 0),
    EXI_STATE_IMM_ACCESS = (1 << 1),
    EXI_STATE_SELECTED = (1 << 2),
    EXI_STATE_ATTACHED = (1 << 3),
    EXI_STATE_LOCKED = (1 << 4),
    EXI_STATE_BUSY = EXI_STATE_DMA_ACCESS | EXI_STATE_IMM_ACCESS
} EXIState;

typedef enum {
    EXI_CHAN_0,
    EXI_CHAN_1,
    EXI_CHAN_2,
    EXI_MAX_CHAN
} EXIChannel;

typedef enum {
    EXI_READ,
    EXI_WRITE,
    EXI_TYPE_2,
    EXI_MAX_TYPE
} EXIType;

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
bool EXISelect(s32, u32 dev, u32 freq);
bool EXIDeselect(EXIChannel);
void EXIInit(void);
bool EXILock(s32, u32 dev, EXICallback unlockedCallback);
bool EXIUnlock(EXIChannel);
u32 EXIGetState(EXIChannel);
s32 EXIGetID(EXIChannel, u32 dev, u32* id);

#endif
