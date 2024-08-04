#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/card.h>

#include "__card.h"

#define TRUNC(n, a) (((u32)(n)) & ~((a)-1))

// functions
static void ReadCallback(s32 chan, s32 result);

s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    u16 *fat;

    ASSERTLINE(0x57, 0 <= fileInfo->chan && fileInfo->chan < 2);
    ASSERTLINE(0x58, 0 <= fileInfo->fileNo && fileInfo->fileNo < CARD_MAX_FILE);

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0)
        return result;

    ASSERTLINE(0x5F, CARDIsValidBlockNo(card, fileInfo->iBlock));
    ASSERTLINE(0x60, fileInfo->offset < card->cBlock * card->sectorSize);

    if (!CARDIsValidBlockNo(card, fileInfo->iBlock) || card->cBlock * card->sectorSize <= fileInfo->offset)
        return __CARDPutControlBlock(card, CARD_RESULT_FATAL_ERROR);

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];

    ASSERTLINE(0x6A, ent->gameName[0] != 0xff);

    if (ent->length * card->sectorSize <= offset || ent->length * card->sectorSize < offset + length)
        return __CARDPutControlBlock(card, CARD_RESULT_LIMIT);

    card->fileInfo = fileInfo;
    fileInfo->length = length;
    if (offset < fileInfo->offset)
    {
        fileInfo->offset = 0;
        fileInfo->iBlock = ent->startBlock;
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock))
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
    }
    fat = __CARDGetFatBlock(card);
    while (fileInfo->offset < TRUNC(offset, card->sectorSize))
    {
        fileInfo->offset += card->sectorSize;
        fileInfo->iBlock = fat[fileInfo->iBlock];
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock))
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
    }

    fileInfo->offset = offset;

    *pcard = card;
    return CARD_RESULT_READY;
}

static void ReadCallback(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    u16 *fat;
    CARDFileInfo *fileInfo;
    s32 length;

    card = &__CARDBlock[chan];
    if (result < 0)
        goto error;

    fileInfo = card->fileInfo;
    if (fileInfo->length < 0)
    {
        result = CARD_RESULT_CANCELED;
        goto error;
    }

    // something funky is going on here; these conflicting casts are needed to match both debug
    // and retail regalloc and codegen. Perhaps the macro is different, but for the life of me
    // i cant figure this one out. Fake for now. Maybe? Unless the macro is just weird.
    length = TRUNC((int)fileInfo->offset + (long)card->sectorSize + card->sectorSize - 1, card->sectorSize) - fileInfo->offset;
    fileInfo->length -= length;
    if (fileInfo->length <= 0)
        goto error;

    fat = __CARDGetFatBlock(card);
    fileInfo->offset += length;
    fileInfo->iBlock = fat[fileInfo->iBlock];
    if (!CARDIsValidBlockNo(card, fileInfo->iBlock))
    {
        result = CARD_RESULT_BROKEN;
        goto error;
    }

    ASSERTLINE(0xBC, OFFSET(fileInfo->length, CARD_SEG_SIZE) == 0);
    ASSERTLINE(0xBD, OFFSET(fileInfo->offset, card->sectorSize) == 0);

    result = __CARDRead(chan, card->sectorSize * (u32)fileInfo->iBlock,
                        (fileInfo->length < card->sectorSize) ? fileInfo->length : card->sectorSize, card->buffer,
                        ReadCallback);
    if (result < 0)
        goto error;

    return;

error:
    callback = card->apiCallback;
    card->apiCallback = NULL;
    __CARDPutControlBlock(card, result);
    ASSERTLINE(0xCE, callback);
    callback(chan, result);
}

s32 CARDReadAsync(CARDFileInfo *fileInfo, void *buf, s32 length, s32 offset, CARDCallback callback) {
    CARDControl *card;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;

    ASSERTLINE(0xF0, buf && OFFSET(buf, 32) == 0);
    ASSERTLINE(0xF1, OFFSET(offset, CARD_SEG_SIZE) == 0);
    ASSERTLINE(0xF2, 0 < length && OFFSET(length, CARD_SEG_SIZE) == 0);

    if (OFFSET(offset, CARD_SEG_SIZE) != 0 || OFFSET(length, CARD_SEG_SIZE) != 0)
        return CARD_RESULT_FATAL_ERROR;
    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(ent);
    if (result == CARD_RESULT_NOPERM)
        result = __CARDIsPublic(ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    DCInvalidateRange(buf, (u32)length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;

    offset = (s32)OFFSET(fileInfo->offset, card->sectorSize);
    length = (length < card->sectorSize - offset) ? length : card->sectorSize - offset;
    result = __CARDRead(fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock + offset, length, buf, ReadCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}

long CARDRead(struct CARDFileInfo * fileInfo, void * buf, long length, long offset) {
    long result = CARDReadAsync(fileInfo, buf, length, offset, __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(fileInfo->chan);
}

s32 CARDCancel(CARDFileInfo *fileInfo) {
    BOOL intrEnabled;
    s32 result;
    CARDControl *card;

    ASSERTLINE(0x14D, 0 <= fileInfo->chan && fileInfo->chan < 2);
    ASSERTLINE(0x14E, 0 <= fileInfo->fileNo && fileInfo->fileNo < CARD_MAX_FILE);

    intrEnabled = OSDisableInterrupts();
    
    card = &__CARDBlock[fileInfo->chan];
    result = CARD_RESULT_READY;
    if (!card->attached)
        result = CARD_RESULT_NOCARD;
    else if (card->result == CARD_RESULT_BUSY && card->fileInfo == fileInfo)
    {
        fileInfo->length = -1;
        result = CARD_RESULT_CANCELED;
    }
    OSRestoreInterrupts(intrEnabled);
    return result;
}
