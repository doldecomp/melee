#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDCheck.h>
#include <dolphin/card/CARDMount.h>
#include <dolphin/card/CARDRdwr.h>
#include <dolphin/card/CARDUnlock.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSRtc.h>

u8 GameChoice AT_ADDRESS(0x800030E3);

u16 __CARDVendorID = 0xFFFF;

u32 SectorSizeTable[8] = {
    8 * 1024, 16 * 1024, 32 * 1024, 64 * 1024, 128 * 1024, 256 * 1024, 0, 0,
};

u32 LatencyTable[8] = {
    4, 8, 16, 32, 64, 128, 256, 512,
};

s32 CARDProbe(EXIChannel chan)
{
    if (GameChoice & 0x80) {
        return 0;
    }
    return EXIProbe(chan);
}

s32 CARDProbeEx(EXIChannel chan, s32* memSize, s32* sectorSize)
{
    u32 id;
    CARDControl* card;
    bool enabled;
    s32 result;
    int probe;

    if (chan < 0 || 2 <= chan) {
        return CARD_RESULT_FATAL_ERROR;
    }

    if (GameChoice & 0x80) {
        return CARD_RESULT_NOCARD;
    }

    card = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();

    probe = EXIProbeEx(chan);
    if (probe == -1) {
        result = CARD_RESULT_NOCARD;
    } else if (probe == 0) {
        result = CARD_RESULT_BUSY;
    } else if (card->attached) {
        if (card->mountStep < 1) {
            result = CARD_RESULT_BUSY;
        } else {
            if (memSize) {
                *memSize = card->size;
            }
            if (sectorSize) {
                *sectorSize = card->sectorSize;
            }
            result = CARD_RESULT_READY;
        }
    } else if ((EXIGetState(chan) & 8)) {
        result = CARD_RESULT_WRONGDEVICE;
    } else if (!EXIGetID(chan, 0, &id)) {
        result = CARD_RESULT_BUSY;
    } else if ((id == 0x80000004 && __CARDVendorID != 0xFFFF) ||
               (!(id & 0xFFFF0000) && !(id & 3)))
    {
        if (memSize) {
            *memSize = (s32) (id & 0xfc);
        }
        if (sectorSize) {
            *sectorSize = SectorSizeTable[(id & 0x00003800) >> 11];
        }
        result = CARD_RESULT_READY;
    } else {
        result = CARD_RESULT_WRONGDEVICE;
    }

    OSRestoreInterrupts(enabled);
    return result;
}

static void DoUnmount(s32 chan, s32 result);

s32 DoMount(EXIChannel chan)
{
    CARDControl* card;
    u32 id;
    u8 status;
    s32 result;
    OSSramEx* sram;
    int i;
    u8 checkSum;
    int step;

    card = &__CARDBlock[chan];

    if (card->mountStep == 0) {
        if (EXIGetID(chan, 0, &id) == 0) {
            result = CARD_RESULT_NOCARD;
        } else if ((id == 0x80000004 && __CARDVendorID != 0xFFFF) ||
                   (!(id & 0xFFFF0000) && !(id & 3)))
        {
            result = CARD_RESULT_READY;
        } else {
            result = CARD_RESULT_WRONGDEVICE;
        }
        if (result < 0) {
            goto error;
        }

        card->cid = id;

        card->size = (id & 0xFC);
        card->sectorSize = SectorSizeTable[(id & 0x00003800) >> 11];
        card->cBlock = ((card->size * 1024 * 1024 / 8) / card->sectorSize);
        card->latency = LatencyTable[(id & 0x00000700) >> 8];
        if (card->sectorSize == 0 || card->cBlock < 8) {
            result = -2;
            goto error;
        }

        result = __CARDClearStatus(chan);
        if (result < 0) {
            goto error;
        }
        result = __CARDReadStatus(chan, &status);
        if (result < 0) {
            goto error;
        }

        if (!EXIProbe(chan)) {
            result = CARD_RESULT_NOCARD;
            goto error;
        }
        if (!(status & 0x40)) {
            result = __CARDUnlock(chan, card->id);
            if (result < 0) {
                goto error;
            }

            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++) {
                sram->flashID[chan][i] = card->id[i];
                checkSum += card->id[i];
            }
            sram->flashIDCheckSum[chan] = (u8) ~checkSum;
            __OSUnlockSramEx(true);

            return result;
        } else {
            card->mountStep = 1;

            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++) {
                checkSum += sram->flashID[chan][i];
            }
            __OSUnlockSramEx(false);
            if (sram->flashIDCheckSum[chan] != (u8) ~checkSum) {
                result = CARD_RESULT_IOERROR;
                goto error;
            }
        }
    }

    if (card->mountStep == 1) {
        if (card->cid == 0x80000004) {
            u16 vendorID;

            sram = __OSLockSramEx();
            vendorID = *(u16*) sram->flashID[chan];
            __OSUnlockSramEx(false);

            if (__CARDVendorID == 0xFFFF || vendorID != __CARDVendorID) {
                result = CARD_RESULT_WRONGDEVICE;
                goto error;
            }
        }
        card->mountStep = 2;

        result = __CARDEnableInterrupt(chan, true);
        if (result < 0) {
            goto error;
        }

        EXISetExiCallback(chan, __CARDExiHandler);
        EXIUnlock(chan);
        DCInvalidateRange(card->workArea, CARD_WORKAREA_SIZE);
    }

    step = card->mountStep - 2;

    /// @todo Eliminate cast to #CARDCallback.
    result =
        __CARDRead(chan, (u32) card->sectorSize * step, CARD_SYSTEM_BLOCK_SIZE,
                   (u8*) card->workArea + (CARD_SYSTEM_BLOCK_SIZE * step),
                   (CARDCallback) __CARDMountCallback);

    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;

error:
    EXIUnlock(chan);
    DoUnmount(chan, result);
    return result;
}

void __CARDMountCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];

    switch (result) {
    case CARD_RESULT_READY:
        if (++card->mountStep < CARD_MAX_MOUNT_STEP) {
            result = DoMount(chan);
            if (0 <= result) {
                return;
            }
        } else {
            result = __CARDVerify(card);
        }
        break;
    case CARD_RESULT_UNLOCKED:
        result = DoMount(chan);
        if (0 <= result) {
            return;
        }
        break;
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_NOCARD:
        DoUnmount(chan, result);
        break;
    }

    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}

s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detachCallback,
                   CARDCallback attachCallback)
{
    CARDControl* card;
    bool enabled;

    if (chan < 0 || 2 <= chan) {
        return CARD_RESULT_FATAL_ERROR;
    }
    if (GameChoice & 0x80) {
        return CARD_RESULT_NOCARD;
    }
    card = &__CARDBlock[chan];

    enabled = OSDisableInterrupts();
    if (card->result == CARD_RESULT_BUSY) {
        OSRestoreInterrupts(enabled);
        return CARD_RESULT_BUSY;
    }

    if (!card->attached && (EXIGetState(chan) & 0x08)) {
        OSRestoreInterrupts(enabled);
        return CARD_RESULT_WRONGDEVICE;
    }

    card->result = CARD_RESULT_BUSY;
    card->workArea = workArea;
    card->extCallback = detachCallback;

    /// @todo Eliminate cast to #CARDCallback.
    card->apiCallback = attachCallback
                            ? attachCallback
                            : (CARDCallback) __CARDDefaultApiCallback;

    card->exiCallback = NULL;

    /// @todo eliminate cast to #EXICallback
    if (!card->attached && !EXIAttach(chan, (EXICallback) __CARDExtHandler)) {
        card->result = CARD_RESULT_NOCARD;
        OSRestoreInterrupts(enabled);
        return CARD_RESULT_NOCARD;
    }

    card->mountStep = 0;
    card->attached = true;
    EXISetExiCallback(chan, 0);
    OSCancelAlarm(&card->alarm);

    card->currentDir = 0;
    card->currentFat = 0;

    OSRestoreInterrupts(enabled);

    /// @todo Eliminate cast to #CARDCallback.
    card->unlockCallback = (CARDCallback) __CARDMountCallback;

    /// @todo eliminate cast to #EXICallback
    if (!EXILock(chan, 0, (EXICallback) __CARDUnlockedHandler)) {
        return CARD_RESULT_READY;
    }
    card->unlockCallback = 0;

    return DoMount(chan);
}

static void DoUnmount(s32 chan, s32 result)
{
    CARDControl* card;
    bool enabled;

    card = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();
    if (card->attached) {
        EXISetExiCallback(chan, 0);
        EXIDetach(chan);
        OSCancelAlarm(&card->alarm);
        card->attached = false;
        card->result = result;
        card->mountStep = 0;
    }
    OSRestoreInterrupts(enabled);
}

s32 CARDUnmount(s32 chan)
{
    CARDControl* card;
    s32 result;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    DoUnmount(chan, CARD_RESULT_NOCARD);
    return CARD_RESULT_READY;
}
