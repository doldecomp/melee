#include <dolphin/os/OSRtc.h>

#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/os.h>

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
    BOOL enabled;
    BOOL locked;
    BOOL sync;
    void (*callback)(void);
} SramControlBlock;

static SramControlBlock Scb ATTRIBUTE_ALIGN(32);

BOOL WriteSram(void* buffer, u32 offset, u32 size);

void WriteSramCallback(void)
{
    s32 unused;
    Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, 0x40 - Scb.offset);
    if (Scb.sync) {
        Scb.offset = 0x40;
    }
}

static BOOL ReadSram(void* buffer)
{
    BOOL err;
    u32 cmd;

    DCInvalidateRange(buffer, RTC_SRAM_SIZE);

    if (!EXILock(RTC_CHAN, RTC_DEV, 0)) {
        return FALSE;
    }
    if (!EXISelect(RTC_CHAN, RTC_DEV, RTC_FREQ)) {
        EXIUnlock(RTC_CHAN);
        return FALSE;
    }

    cmd = RTC_CMD_READ | RTC_SRAM_ADDR;
    err = FALSE;
    err |= !EXIImm(RTC_CHAN, &cmd, 4, 1, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIDma(RTC_CHAN, buffer, RTC_SRAM_SIZE, 0, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIDeselect(RTC_CHAN);
    EXIUnlock(RTC_CHAN);

    return !err;
}

BOOL WriteSram(void* buffer, u32 offset, u32 size)
{
    BOOL err;
    u32 cmd;

    if (!EXILock(RTC_CHAN, RTC_DEV, WriteSramCallback)) {
        return FALSE;
    }
    if (!EXISelect(RTC_CHAN, RTC_DEV, RTC_FREQ)) {
        EXIUnlock(RTC_CHAN);
        return FALSE;
    }

    offset <<= 6;
    cmd = RTC_CMD_WRITE | RTC_SRAM_ADDR + offset;
    err = FALSE;
    err |= !EXIImm(RTC_CHAN, &cmd, 4, 1, NULL);
    err |= !EXISync(RTC_CHAN);
    err |= !EXIImmEx(RTC_CHAN, buffer, (s32) size, 1);
    err |= !EXIDeselect(RTC_CHAN);
    EXIUnlock(RTC_CHAN);

    return !err;
}

void __OSInitSram()
{
    Scb.locked = Scb.enabled = FALSE;
    Scb.sync = ReadSram(Scb.sram);
    Scb.offset = RTC_SRAM_SIZE;
}

static void* LockSram(u32 offset)
{
    BOOL enabled = OSDisableInterrupts();

    if (Scb.locked != FALSE) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }

    Scb.enabled = enabled;
    Scb.locked = TRUE;

    return Scb.sram + offset;
}

OSSram* __OSLockSram()
{
    return LockSram(0);
}

OSSramEx* __OSLockSramEx()
{
    return LockSram(sizeof(OSSram));
}

static BOOL UnlockSram(BOOL commit, u32 offset)
{
    u16* p;

    if (commit) {
        if (offset == 0) {
            OSSram* sram = (OSSram*) Scb.sram;

            if (2u < (sram->flags & 3)) {
                sram->flags &= ~3;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for (p = (u16*) &sram->counterBias; p < (u16*) (Scb.sram + sizeof(OSSram)); p++) {
                sram->checkSum += *p;
                sram->checkSumInv += ~*p;
            }
        }

        if (offset < Scb.offset) {
            Scb.offset = offset;
        }

        Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, RTC_SRAM_SIZE - Scb.offset);
        if (Scb.sync) {
            Scb.offset = RTC_SRAM_SIZE;
        }
    }
    Scb.locked = FALSE;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

void __OSUnlockSram(BOOL commit)
{
    UnlockSram(commit, 0);
}

void __OSUnlockSramEx(BOOL commit)
{
    UnlockSram(commit, 0x14);
}

BOOL __OSSyncSram()
{
    return Scb.sync;
}

inline OSSram* __OSLockSramHACK()
{
    return LockSram(0);
}

u32 OSGetSoundMode()
{
    OSSram* sram = __OSLockSramHACK();
    u32 mode = (sram->flags & 0x4) ? OS_SOUND_MODE_STEREO : OS_SOUND_MODE_MONO;
    __OSUnlockSram(FALSE);
    return mode;
}

void OSSetSoundMode(u32 mode)
{
    OSSram* sram;
    mode <<= 2;
    mode &= 4;

    sram = __OSLockSramHACK();
    if (mode == (sram->flags & 4)) {
        __OSUnlockSram(FALSE);
        return;
    }

    sram->flags &= ~4;
    sram->flags |= mode;
    __OSUnlockSram(TRUE);
}

u32 OSGetProgressiveMode()
{
    OSSram* sram = __OSLockSramHACK();
    u32 mode = (sram->flags & 0x80) >> 7;
    __OSUnlockSram(FALSE);
    return mode;
}

void OSSetProgressiveMode(u32 mode)
{
    OSSram* sram;
    mode <<= 7;
    mode &= 0x80;

    sram = __OSLockSramHACK();
    if (mode == (sram->flags & 0x80)) {
        __OSUnlockSram(FALSE);
        return;
    }

    sram->flags &= ~0x80;
    sram->flags |= mode;
    __OSUnlockSram(TRUE);
}

u32 OSGetWirelessID(u32 channel)
{
    OSSramEx* sram = __OSLockSramEx();
    u16 id = sram->wirelessPadID[channel];
    __OSUnlockSramEx(FALSE);
    return id;
}

void OSSetWirelessID(u32 channel, u16 id)
{
    OSSramEx* sram = __OSLockSramEx();
    if (sram->wirelessPadID[channel] != id) {
        sram->wirelessPadID[channel] = id;
        __OSUnlockSramEx(TRUE);
    } else {
        __OSUnlockSramEx(FALSE);
    }
}
