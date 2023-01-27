#include <dolphin/card/CARDDir.h>

#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDCheck.h>
#include <dolphin/card/CARDRdwr.h>
#include <dolphin/os/OSCache.h>
#include <Runtime/__mem.h>

CARDDir* __CARDGetDirBlock(CARDControl* card)
{
    return card->currentDir;
}

static void WriteCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    if (0 <= result) {
        CARDDir* dir0 = (CARDDir*) ((uintptr_t) card->workArea + 0x2000);
        CARDDir* dir1 = (CARDDir*) ((uintptr_t) card->workArea + 0x4000);

        if (card->currentDir == dir0) {
            card->currentDir = dir1;
            memcpy(dir1, dir0, 0x2000);
        } else {
            card->currentDir = dir0;
            memcpy(dir0, dir1, 0x2000);
        }
    }

    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}

static void EraseCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    CARDDir* dir;
    u32 tmp[2];
    u32 addr;

    card = &__CARDBlock[chan];
    if (result < 0)
        goto error;

    dir = __CARDGetDirBlock(card);
    addr = ((uintptr_t) dir - (uintptr_t) card->workArea) / 0x2000 *
           card->sectorSize;

    /// @todo Eliminate cast to #CARDCallback.
    result = __CARDWrite(chan, addr, 0x2000, dir, (CARDCallback) WriteCallback);

    if (result < 0)
        goto error;

    return;

error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}

s32 __CARDUpdateDir(s32 chan, CARDCallback callback)
{
    CARDControl* card;
    CARDDirCheck* check;
    u32 tmp[2];
    u32 addr;
    CARDDir* dir;

    card = &__CARDBlock[chan];
    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    dir = __CARDGetDirBlock(card);
    check = __CARDGetDirCheck(dir);
    ++check->checkCode;
    __CARDCheckSum(dir, 0x2000 - sizeof(u32), &check->checkSum,
                   &check->checkSumInv);
    DCStoreRange(dir, 0x2000);

    card->eraseCallback = callback;
    addr = ((uintptr_t) dir - (uintptr_t) card->workArea) / 0x2000 *
           card->sectorSize;

    /// @todo Eliminate cast to #CARDCallback.
    return __CARDEraseSector(chan, addr, (CARDCallback) EraseCallback);
}
