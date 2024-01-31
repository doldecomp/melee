#include <dolphin/os.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSRtc.h>

#define RTC_CMD_READ 0x20000000
#define RTC_CMD_WRITE 0xA0000000

#define RTC_SRAM_ADDR 0x00000100
#define RTC_SRAM_SIZE 64

#define RTC_CHAN 0
#define RTC_DEV 1
#define RTC_FREQ 3 // EXI_FREQ_8M

typedef struct SramControlBlock {
    u8 sram[RTC_SRAM_SIZE];
    u32 offset;
    bool enabled;
    bool locked;
    bool sync;
    void (*callback)(void);
} SramControlBlock;

static SramControlBlock Scb ATTRIBUTE_ALIGN(32);

bool WriteSram(void* buffer, u32 offset, u32 size);

void WriteSramCallback(s32 unused0, OSContext* unused1)
{
    Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, 0x40 - Scb.offset);
    if (Scb.sync) {
        Scb.offset = 0x40;
    }
}

static bool ReadSram(void* buffer)
{
    bool err;
    u32 cmd;

    DCInvalidateRange(buffer, RTC_SRAM_SIZE);

    if (!EXILock(RTC_CHAN, RTC_DEV, 0)) {
        return false;
    }
    if (!EXISelect(RTC_CHAN, RTC_DEV, RTC_FREQ)) {
        EXIUnlock(RTC_CHAN);
        return false;
    }

    cmd = RTC_CMD_READ | RTC_SRAM_ADDR;
    err = false;
    err |= !EXIImm(RTC_CHAN, &cmd, 4, 1, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIDma(RTC_CHAN, buffer, RTC_SRAM_SIZE, 0, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIDeselect(RTC_CHAN);
    EXIUnlock(RTC_CHAN);

    return !err;
}

bool WriteSram(void* buffer, u32 offset, u32 size)
{
    bool err;
    u32 cmd;

    if (!EXILock(RTC_CHAN, RTC_DEV, WriteSramCallback)) {
        return false;
    }

    if (!EXISelect(RTC_CHAN, RTC_DEV, RTC_FREQ)) {
        EXIUnlock(RTC_CHAN);
        return false;
    }

    offset <<= 6;
    cmd = RTC_CMD_WRITE | RTC_SRAM_ADDR + offset;
    err = false;
    err |= !EXIImm(RTC_CHAN, &cmd, 4, 1, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIImmEx(RTC_CHAN, buffer, (s32) size, 1);
    err |= !EXIDeselect(RTC_CHAN);
    EXIUnlock(RTC_CHAN);

    return !err;
}

void __OSInitSram(void)
{
    Scb.locked = Scb.enabled = false;
    Scb.sync = ReadSram(Scb.sram);
    Scb.offset = RTC_SRAM_SIZE;
}

static void* LockSram(u32 offset)
{
    bool enabled = OSDisableInterrupts();

    if (Scb.locked != false) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }

    Scb.enabled = enabled;
    Scb.locked = true;

    return Scb.sram + offset;
}

OSSram* __OSLockSram(void)
{
    return LockSram(0);
}

OSSramEx* __OSLockSramEx(void)
{
    return LockSram(sizeof(OSSram));
}

static bool UnlockSram(bool commit, u32 offset)
{
    u16* p;

    if (commit) {
        if (offset == 0) {
            OSSram* sram = (OSSram*) Scb.sram;

            if (2u < (sram->flags & 3)) {
                sram->flags &= ~3;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for (p = (u16*) &sram->counterBias;
                 p < (u16*) (Scb.sram + sizeof(OSSram)); p++)
            {
                sram->checkSum += *p;
                sram->checkSumInv += ~*p;
            }
        }

        if (offset < Scb.offset) {
            Scb.offset = offset;
        }

        Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset,
                             RTC_SRAM_SIZE - Scb.offset);
        if (Scb.sync) {
            Scb.offset = RTC_SRAM_SIZE;
        }
    }
    Scb.locked = false;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

void __OSUnlockSram(bool commit)
{
    UnlockSram(commit, 0);
}

void __OSUnlockSramEx(bool commit)
{
    UnlockSram(commit, 0x14);
}

bool __OSSyncSram(void)
{
    return Scb.sync;
}

static inline OSSram* __OSLockSramHACK(void)
{
    return LockSram(0);
}

u32 OSGetSoundMode(void)
{
    OSSram* sram = __OSLockSramHACK();
    u32 mode = (sram->flags & 0x4) ? OS_SOUND_MODE_STEREO : OS_SOUND_MODE_MONO;
    __OSUnlockSram(false);
    return mode;
}

void OSSetSoundMode(u32 mode)
{
    OSSram* sram;
    mode <<= 2;
    mode &= 4;

    sram = __OSLockSramHACK();
    if (mode == (sram->flags & 4)) {
        __OSUnlockSram(false);
        return;
    }

    sram->flags &= ~4;
    sram->flags |= mode;
    __OSUnlockSram(true);
}

u32 OSGetProgressiveMode(void)
{
    OSSram* sram = __OSLockSramHACK();
    u32 mode = (sram->flags & 0x80) >> 7;
    __OSUnlockSram(false);
    return mode;
}

void OSSetProgressiveMode(u32 mode)
{
    OSSram* sram;
    mode <<= 7;
    mode &= 0x80;

    sram = __OSLockSramHACK();
    if (mode == (sram->flags & 0x80)) {
        __OSUnlockSram(false);
        return;
    }

    sram->flags &= ~0x80;
    sram->flags |= mode;
    __OSUnlockSram(true);
}

u32 OSGetWirelessID(u32 chan)
{
    OSSramEx* sram = __OSLockSramEx();
    u16 id = sram->wirelessPadID[chan];
    __OSUnlockSramEx(false);
    return id;
}

void OSSetWirelessID(u32 chan, u16 id)
{
    OSSramEx* sram = __OSLockSramEx();
    if (sram->wirelessPadID[chan] != id) {
        sram->wirelessPadID[chan] = id;
        __OSUnlockSramEx(true);
    } else {
        __OSUnlockSramEx(false);
    }
}
