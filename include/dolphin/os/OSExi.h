#ifndef DOLPHIN_OS_OSEXI_H
#define DOLPHIN_OS_OSEXI_H

#include <dolphin/os/OSInterrupt.h>

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

typedef void (*EXICallback)(EXIChannel, OSContext*);

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

void SetExiInterruptMask(EXIChannel, volatile EXIControl*);
BOOL EXIImm(EXIChannel, void* buf, s32 len, u32 type, EXICallback);
BOOL EXIImmEx(EXIChannel, void* buf, s32 len, u32 mode);
BOOL EXIDma(EXIChannel, void* buf, s32 len, u32 type, EXICallback);
BOOL EXISync(EXIChannel);
u32 EXIClearInterrupts(EXIChannel, BOOL exi, BOOL tc, BOOL ext);
EXICallback EXISetExiCallback(EXIChannel, EXICallback exiCallback);
BOOL EXIProbe(EXIChannel);
s32 EXIProbeEx(EXIChannel);
BOOL EXIAttach(EXIChannel, EXICallback);
BOOL EXIDetach(EXIChannel);
BOOL EXISelect(EXIChannel, u32 dev, u32 freq);
BOOL EXIDeselect(EXIChannel);
void EXIInit(void);
BOOL EXILock(EXIChannel, u32 dev, EXICallback unlockedCallback);
BOOL EXIUnlock(EXIChannel);
u32 EXIGetState(EXIChannel);
s32 EXIGetID(EXIChannel, u32 dev, u32* id);

#endif
