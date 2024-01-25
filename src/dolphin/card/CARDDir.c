#include <platform.h>

#include <__mem.h>
#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDCheck.h>
#include <dolphin/card/CARDDir.h>
#include <dolphin/card/CARDRdwr.h>
#include <dolphin/os/OSCache.h>

CARDDir* __CARDGetDirBlock(CARDControl* card)
{
    return card->currentDir;
}

static usize_t const card_size = 0x2000;

static void WriteCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    if (0 <= result) {
        CARDDir* dir0 = (CARDDir*) ((uintptr_t) card->workArea + card_size);
        CARDDir* dir1 =
            (CARDDir*) ((uintptr_t) card->workArea + card_size * 2);

        if (card->currentDir == dir0) {
            card->currentDir = dir1;
            memcpy(dir1, dir0, card_size);
        } else {
            card->currentDir = dir0;
            memcpy(dir0, dir1, card_size);
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
    u8 _[8];

    CARDControl* card;
    CARDCallback callback;
    CARDDir* dir;
    uintptr_t addr;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    dir = __CARDGetDirBlock(card);
    addr = ((uintptr_t) dir - (uintptr_t) card->workArea) / card_size *
           card->sectorSize;

    /// @todo Eliminate cast to #CARDCallback.
    result =
        __CARDWrite(chan, addr, card_size, dir, (CARDCallback) WriteCallback);

    if (result < 0) {
        goto error;
    }

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
    u8 _[8];

    CARDControl* card;
    CARDDirCheck* check;
    uintptr_t addr;
    CARDDir* dir;

    card = &__CARDBlock[chan];
    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    dir = __CARDGetDirBlock(card);
    check = __CARDGetDirCheck(dir);
    ++check->checkCode;
    __CARDCheckSum(dir, card_size - sizeof(uintptr_t), &check->checkSum,
                   &check->checkSumInv);
    DCStoreRange(dir, card_size);

    card->eraseCallback = callback;
    addr = ((uintptr_t) dir - (uintptr_t) card->workArea) / card_size *
           card->sectorSize;

    /// @todo Eliminate cast to #CARDCallback.
    return __CARDEraseSector(chan, addr, (CARDCallback) EraseCallback);
}
