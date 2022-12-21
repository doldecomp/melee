#include <dolphin/card.h>

#define OFFSET(n, a) (((u32) (n)) & ((a) -1))
#define TRUNC(n, a) (((u32) (n)) & ~((a) -1))

s32 __CARDSeek(CARDFileInfo* fileInfo, s32 length, s32 offset, CARDControl** pcard)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    u16* fat;

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0) {
        return result;
    }

    if (!CARDIsValidBlockNo(card, fileInfo->iBlock) ||
        card->cBlock * card->sectorSize <= fileInfo->offset) {
        return __CARDPutControlBlock(card, CARD_RESULT_FATAL_ERROR);
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    if (ent->length * card->sectorSize <= offset ||
        ent->length * card->sectorSize < offset + length) {
        return __CARDPutControlBlock(card, CARD_RESULT_LIMIT);
    }

    card->fileInfo = fileInfo;
    fileInfo->length = length;
    if (offset < fileInfo->offset) {
        fileInfo->offset = 0;
        fileInfo->iBlock = ent->startBlock;
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
        }
    }
    fat = __CARDGetFatBlock(card);
    while (fileInfo->offset < TRUNC(offset, card->sectorSize)) {
        fileInfo->offset += card->sectorSize;
        fileInfo->iBlock = fat[fileInfo->iBlock];
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
        }
    }

    fileInfo->offset = offset;

    *pcard = card;
    return CARD_RESULT_READY;
}

static void ReadCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    u16* fat;
    CARDFileInfo* fileInfo;
    s32 length;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    fileInfo = card->fileInfo;
    if (fileInfo->length < 0) {
        result = CARD_RESULT_CANCELED;
        goto error;
    }

    length = (s32) TRUNC(fileInfo->offset + card->sectorSize, card->sectorSize) - fileInfo->offset;
    fileInfo->length -= length;
    if (fileInfo->length <= 0) {
        goto error;
    }

    fat = __CARDGetFatBlock(card);
    fileInfo->offset += length;
    fileInfo->iBlock = fat[fileInfo->iBlock];
    if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
        result = CARD_RESULT_BROKEN;
        goto error;
    }

    result = __CARDRead(chan, card->sectorSize * fileInfo->iBlock,
                        (fileInfo->length < card->sectorSize) ? fileInfo->length : card->sectorSize,
                        card->buffer, ReadCallback);
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

s32 CARDReadAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset,
                  CARDCallback callback)
{
    CARDControl* card;
    s32 result;
    CARDDir* dir;
    CARDDir* ent;

    if (OFFSET(offset, CARD_SEG_SIZE) != 0 || OFFSET(length, CARD_SEG_SIZE) != 0) {
        return CARD_RESULT_FATAL_ERROR;
    }
    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0) {
        return result;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(card, ent);
    if (result == CARD_RESULT_NOPERM) {
        result = __CARDIsPublic(ent);
    }

    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    DCInvalidateRange(buf, length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;

    offset = (s32) OFFSET(fileInfo->offset, card->sectorSize);
    length = (length < card->sectorSize - offset) ? length : card->sectorSize - offset;
    result = __CARDRead(fileInfo->chan, card->sectorSize * fileInfo->iBlock + offset, length,
                        buf, ReadCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}

int CARDRead(CARDFileInfo* fileinfo, void* buf, u32 length, u32 offset)
{
    int result = CARDReadAsync(fileinfo, buf, length, offset, __CARDSyncCallback);
    if (result < 0) {
        return result;
    }
    return __CARDSync(fileinfo->chan);
}
