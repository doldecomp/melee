#include <dolphin.h>
#include <dolphin/card.h>

// internal includes
#include "__card.h"

// functions
static void WriteCallback(long chan, long result);
static void EraseCallback(long chan, long result);

static void WriteCallback(long chan, long result) {
    struct CARDControl * card;
    void (* callback)(long, long);
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

static void EraseCallback(long chan, long result) {
    struct CARDControl * card;
    void (* callback)(long, long);
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

long CARDWriteAsync(struct CARDFileInfo * fileInfo, void * buf, long length, long offset, void (* callback)(long, long)) {
    struct CARDControl * card;
    long result;
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
    result = __CARDAccess(ent);
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

long CARDWrite(struct CARDFileInfo * fileInfo, void * buf, long length, long offset) {
    long result = CARDWriteAsync(fileInfo, buf, length, offset, __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(fileInfo->chan);
}
