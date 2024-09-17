#include <__mem.h>
#include <string.h>
#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDBlock.h>
#include <dolphin/card/CARDCreate.h>
#include <dolphin/card/CARDDir.h>
#include <dolphin/card/CARDOpen.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSTime.h>

#define CARDSetIconSpeed(stat, n, f)                                          \
    ((stat)->iconSpeed =                                                      \
         (((stat)->iconSpeed & ~(CARD_STAT_SPEED_MASK << (2 * (n)))) |        \
          ((f) << (2 * (n)))))

#ifndef BUGFIX
#pragma push
#pragma force_active on
#endif
void CreateCallbackFat(s32 chan, s32 result)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    callback = card->apiCallback;
    card->apiCallback = 0;
    if (result < 0) {
        goto error;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[card->freeNo];
    memcpy(ent->gameName, card->diskID->gameName, sizeof(ent->gameName));
    memcpy(ent->company, card->diskID->company, sizeof(ent->company));
    ent->permission = CARD_ATTR_PUBLIC;
    ent->copyTimes = 0;
    ent->startBlock = card->startBlock;

    ent->bannerFormat = 0;
    ent->iconAddr = 0xffffffff;
    ent->iconFormat = 0;
    ent->iconSpeed = 0;
    ent->commentAddr = 0xffffffff;

    CARDSetIconSpeed(ent, 0, CARD_STAT_SPEED_FAST);

    card->fileInfo->offset = 0;
    card->fileInfo->iBlock = ent->startBlock;

    ent->time = (u32) OSTicksToSeconds(OSGetTime());
    result = __CARDUpdateDir(chan, callback);
    if (result < 0) {
        goto error;
    }
    return;

error:
    __CARDPutControlBlock(card, result);
    if (callback) {
        callback(chan, result);
    }
}
#ifndef BUGFIX
#pragma pop
#endif

/// @todo Used only by #hsd_803AAA48.
#pragma push
#pragma force_active on
s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size,
                    CARDFileInfo* fileInfo, CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    u16 fileNo;
    u16 freeNo;
    u16* fat;

    if (strlen(fileName) > (u32) CARD_FILENAME_MAX) {
        return CARD_RESULT_NAMETOOLONG;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    if (size <= 0 || (size % card->sectorSize) != 0) {
        return CARD_RESULT_FATAL_ERROR;
    }

    freeNo = (u16) -1;
    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        ent = &dir[fileNo];
        if (ent->gameName[0] == 0xff) {
            if (freeNo == (u16) -1) {
                freeNo = fileNo;
            }
        } else if (memcmp(ent->gameName, card->diskID->gameName,
                          sizeof(ent->gameName)) == 0 &&
                   memcmp(ent->company, card->diskID->company,
                          sizeof(ent->company)) == 0 &&
                   __CARDCompareFileName(ent, fileName))
        {
            return __CARDPutControlBlock(card, CARD_RESULT_EXIST);
        }
    }
    if (freeNo == (u16) -1) {
        return __CARDPutControlBlock(card, CARD_RESULT_NOENT);
    }

    fat = __CARDGetFatBlock(card);

    /// @todo #CARDControl::sectorSize is probably #size_t.
    if ((unsigned) card->sectorSize * fat[CARD_FAT_FREEBLOCKS] < size) {
        return __CARDPutControlBlock(card, CARD_RESULT_INSSPACE);
    }

    /// @todo Eliminate cast to #CARDCallback.
    card->apiCallback =
        callback ? callback : (CARDCallback) __CARDDefaultApiCallback;

    card->freeNo = freeNo;
    ent = &dir[freeNo];
    ent->length = (u16) (size / card->sectorSize);
    strncpy((char*) ent->fileName, fileName, CARD_FILENAME_MAX);

    card->fileInfo = fileInfo;
    fileInfo->chan = chan;
    fileInfo->fileNo = freeNo;

    /// @todo Eliminate cast to #CARDCallback.
    result = __CARDAllocBlock(chan, size / card->sectorSize,
                              (CARDCallback) CreateCallbackFat);

    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    return result;
}
#pragma pop
