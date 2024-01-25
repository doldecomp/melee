#include <__mem.h>
#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDCheck.h>
#include <dolphin/card/CARDFormat.h>
#include <dolphin/card/CARDRdwr.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSFont.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/os/OSTime.h>

extern vu16 __VIRegs[59] AT_ADDRESS(0xCC002000);

void FormatCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    ++card->formatStep;
    if (card->formatStep < CARD_NUM_SYSTEM_BLOCK) {
        /// @todo Eliminate cast to #CARDCallback.
        result =
            __CARDEraseSector(chan, (u32) card->sectorSize * card->formatStep,
                              (CARDCallback) FormatCallback);

        if (0 <= result) {
            return;
        }
    } else if (card->formatStep < 2 * CARD_NUM_SYSTEM_BLOCK) {
        int step = card->formatStep - CARD_NUM_SYSTEM_BLOCK;

        /// @todo Eliminate cast to #CARDCallback.
        result = __CARDWrite(
            chan, (u32) card->sectorSize * step, CARD_SYSTEM_BLOCK_SIZE,
            (u8*) card->workArea + (CARD_SYSTEM_BLOCK_SIZE * step),
            (CARDCallback) FormatCallback);

        if (result >= 0) {
            return;
        }
    } else {
        card->currentDir = (CARDDir*) ((u8*) card->workArea +
                                       (1 + 0) * CARD_SYSTEM_BLOCK_SIZE);
        memcpy(card->currentDir,
               (u8*) card->workArea + (1 + 1) * CARD_SYSTEM_BLOCK_SIZE,
               CARD_SYSTEM_BLOCK_SIZE);
        card->currentFat =
            (u16*) ((u8*) card->workArea + (3 + 0) * CARD_SYSTEM_BLOCK_SIZE);
        memcpy(card->currentFat,
               (u8*) card->workArea + (3 + 1) * CARD_SYSTEM_BLOCK_SIZE,
               CARD_SYSTEM_BLOCK_SIZE);
    }

error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}

s32 __CARDFormatRegionAsync(s32 chan, u16 encode, CARDCallback callback)
{
    CARDControl* card;
    CARDID* id;
    CARDDir* dir;
    u16* fat;
    s16 i;
    s32 result;
    OSSram* sram;
    OSSramEx* sramEx;
    u16 viDTVStatus;
    OSTime time;
    OSTime rand;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    id = (CARDID*) card->workArea;
    memset(id, 0xff, CARD_SYSTEM_BLOCK_SIZE);
    viDTVStatus = __VIRegs[55];

    id->encode = encode;

    sram = __OSLockSram();
    *(u32*) &id->serial[20] = sram->counterBias;
    *(u32*) &id->serial[24] = sram->language;
    __OSUnlockSram(false);

    rand = time = OSGetTime();

    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++) {
        rand = (rand * 1103515245 + 12345) >> 16;
        id->serial[i] = (u8) (sramEx->flashID[chan][i] + rand);
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }
    __OSUnlockSramEx(false);

    *(u32*) &id->serial[28] = viDTVStatus;
    *(OSTime*) &id->serial[12] = time;

    id->deviceID = 0;
    id->size = card->size;
    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &id->checkSum,
                   &id->checkSumInv);

    for (i = 0; i < 2; i++) {
        CARDDirCheck* check;

        dir = (CARDDir*) ((u8*) card->workArea +
                          (1 + i) * CARD_SYSTEM_BLOCK_SIZE);
        memset(dir, 0xff, CARD_SYSTEM_BLOCK_SIZE);
        check = __CARDGetDirCheck(dir);
        check->checkCode = i;
        __CARDCheckSum(dir, CARD_SYSTEM_BLOCK_SIZE - sizeof(u32),
                       &check->checkSum, &check->checkSumInv);
    }
    for (i = 0; i < 2; i++) {
        fat = (u16*) ((u8*) card->workArea + (3 + i) * CARD_SYSTEM_BLOCK_SIZE);
        memset(fat, 0x00, CARD_SYSTEM_BLOCK_SIZE);
        fat[CARD_FAT_CHECKCODE] = (u16) i;
        fat[CARD_FAT_FREEBLOCKS] =
            (u16) (card->cBlock - CARD_NUM_SYSTEM_BLOCK);
        fat[CARD_FAT_LASTSLOT] = CARD_NUM_SYSTEM_BLOCK - 1;
        __CARDCheckSum(&fat[CARD_FAT_CHECKCODE],
                       CARD_SYSTEM_BLOCK_SIZE - sizeof(u32),
                       &fat[CARD_FAT_CHECKSUM], &fat[CARD_FAT_CHECKSUMINV]);
    }

    /// @todo Eliminate cast to #CARDCallback.
    card->apiCallback =
        callback ? callback : (CARDCallback) __CARDDefaultApiCallback;

    DCStoreRange(card->workArea, CARD_WORKAREA_SIZE);

    card->formatStep = 0;

    /// @todo Eliminate cast to #CARDCallback.
    result = __CARDEraseSector(chan, (u32) card->sectorSize * card->formatStep,
                               (CARDCallback) FormatCallback);

    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }

    return result;
}

s32 CARDFormatAsync(s32 chan, CARDCallback callback)
{
    return __CARDFormatRegionAsync(chan, OSGetFontEncode(), callback);
}
