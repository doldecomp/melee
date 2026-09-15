#include <dolphin.h>
#include <dolphin/card.h>

// internal includes
#include "__card.h"

// functions
static void WriteCallback(s32 chan, s32 result);
static void EraseCallback(s32 chan, s32 result);

static void WriteCallback(s32 chan, s32 result) {
    struct CARDControl * card;
    CARDCallback callback;
    unsigned short * fat;
    struct CARDDir * dir;
    struct CARDDir * ent;
    struct CARDFileInfo * fileInfo;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        fileInfo = card->fileInfo;
        if (fileInfo->length < 0) {
            result = CARD_RESULT_CANCELED;
            goto after;
        }
        fileInfo->length -= card->sectorSize;
        if (fileInfo->length <= 0) {
            dir = __CARDGetDirBlock(card);
            ent = dir + fileInfo->fileNo;
            ent->time = OSGetTime()/(__OSBusClock/4);
            callback = card->apiCallback;
            card->apiCallback = NULL;
            result = __CARDUpdateDir(chan, callback);
            goto check;
        } else {
            fat = __CARDGetFatBlock(card);
            fileInfo->offset += card->sectorSize;
            fileInfo->iBlock = fat[fileInfo->iBlock];
            if ((fileInfo->iBlock < 5) || (fileInfo->iBlock >= card->cBlock)) {
                result = CARD_RESULT_BROKEN;
                goto after;
            }
            result = __CARDEraseSector(chan, card->sectorSize * fileInfo->iBlock, EraseCallback);
check:;
            if (result < 0) {
                goto after;
            }
        }
    } else {
after:;
        callback = card->apiCallback;
        card->apiCallback = NULL;
        __CARDPutControlBlock(card, result);
        ASSERTLINE(0x7D, callback);
        callback(chan, result);
    }
}

static void EraseCallback(s32 chan, s32 result) {
    struct CARDControl * card;
    CARDCallback callback;
    struct CARDFileInfo * fileInfo;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        fileInfo = card->fileInfo;
        ASSERTLINE(0x98, OFFSET(fileInfo->offset, card->sectorSize) == 0);
        result = __CARDWrite(chan, card->sectorSize * fileInfo->iBlock, card->sectorSize, card->buffer, WriteCallback);
        if (result < 0) {
            goto after;
        }
    } else {
after:;
        callback = card->apiCallback;
        card->apiCallback = NULL;
        __CARDPutControlBlock(card, result);
        ASSERTLINE(0xA6, callback);
        callback(chan, result);
    }
}

s32 CARDWriteAsync(struct CARDFileInfo * fileInfo, void * buf, s32 length, s32 offset, CARDCallback callback) {
    struct CARDControl * card;
    s32 result;
    struct CARDDir * dir;
    struct CARDDir * ent;

    ASSERTLINE(0xC9, buf && ((u32) buf % 32) == 0);
    ASSERTLINE(0xCA, 0 < length);
    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0) {
        return result;
    }
    ASSERTLINE(0xD0, OFFSET(offset, card->sectorSize) == 0);
    ASSERTLINE(0xD1, OFFSET(length, card->sectorSize) == 0);

    if (OFFSET(offset, card->sectorSize) != 0 || OFFSET(length, card->sectorSize) != 0)
        return __CARDPutControlBlock(card, CARD_RESULT_FATAL_ERROR);

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(card, ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    DCStoreRange((void *)buf, (u32)length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    card->buffer = (void *)buf;
    result = __CARDEraseSector(fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock, EraseCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}

s32 CARDWrite(struct CARDFileInfo * fileInfo, void * buf, s32 length, s32 offset) {
    s32 result = CARDWriteAsync(fileInfo, buf, length, offset, __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(fileInfo->chan);
}
