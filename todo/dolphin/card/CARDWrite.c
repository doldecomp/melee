#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDDir.h>
#include <dolphin/card/CARDOpen.h>
#include <dolphin/card/CARDRdwr.h>
#include <dolphin/card/CARDRead.h>
#include <dolphin/card/CARDWrite.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSTime.h>

#define OFFSET(n, a) (((u32) (n)) & ((a) - 1))

static void EraseCallback(EXIChannel chan, s32 result);

static void WriteCallback(EXIChannel chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    u16* fat;
    CARDDir* dir;
    CARDDir* ent;
    CARDFileInfo* fileinfo;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    fileinfo = card->fileInfo;
    if (fileinfo->length < 0) {
        result = CARD_RESULT_CANCELED;
        goto error;
    }

    fileinfo->length -= card->sectorSize;
    if (fileinfo->length <= 0) {
        dir = __CARDGetDirBlock(card);
        ent = &dir[fileinfo->fileNo];
        ent->time = OSTicksToSeconds(OSGetTime());
        callback = card->apiCallback;
        card->apiCallback = 0;
        result = __CARDUpdateDir(chan, callback);
    } else {
        fat = __CARDGetFatBlock(card);
        fileinfo->offset += card->sectorSize;
        fileinfo->iBlock = fat[fileinfo->iBlock];
        if (!CARDIsValidBlockNo(card, fileinfo->iBlock)) {
            result = CARD_RESULT_BROKEN;
            goto error;
        }
        result = __CARDEraseSector(chan, card->sectorSize * fileinfo->iBlock,
                                   EraseCallback);
    }

    if (result < 0) {
        goto error;
    }
    return;

error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}

static void EraseCallback(EXIChannel chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    CARDFileInfo* fileInfo;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    fileInfo = card->fileInfo;
    result = __CARDWrite(chan, card->sectorSize * fileInfo->iBlock,
                         card->sectorSize, card->buffer, WriteCallback);
    if (result < 0) {
        goto error;
    }
    return;

error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}

s32 CARDWriteAsync(CARDFileInfo* fileInfo, const void* buf, u32 length,
                   s32 offset, CARDCallback callback)
{
    CARDControl* card;
    s32 result;
    CARDDir* dir;
    CARDDir* ent;

    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0) {
        return result;
    }

    if (OFFSET(offset, card->sectorSize) != 0 ||
        OFFSET(length, card->sectorSize) != 0)
    {
        return __CARDPutControlBlock(card, CARD_RESULT_FATAL_ERROR);
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(card, ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    DCStoreRange((void*) buf, length);

    /// @todo Eliminate cast to #CARDCallback.
    card->apiCallback =
        callback ? callback : (CARDCallback) __CARDDefaultApiCallback;

    card->buffer = (void*) buf;
    result = __CARDEraseSector(
        fileInfo->chan, card->sectorSize * fileInfo->iBlock, EraseCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}

int CARDWrite(CARDFileInfo* info, void* buf, s32 length, s32 offset)
{
    /// @todo Eliminate cast to #CARDCallback.
    int result = CARDWriteAsync(info, buf, length, offset,
                                (CARDCallback) __CARDSyncCallback);

    if (result < 0) {
        return result;
    }

    return __CARDSync(info->chan);
}
