#include <__mem.h>
#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDBlock.h>
#include <dolphin/card/CARDDelete.h>
#include <dolphin/card/CARDDir.h>
#include <dolphin/card/CARDOpen.h>

static void DeleteCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    callback = card->apiCallback;
    card->apiCallback = 0;

    if (result < 0) {
        goto error;
    }

    result = __CARDFreeBlock(chan, card->startBlock, callback);
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

s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;

    if (fileNo < 0 || CARD_MAX_FILE <= fileNo) {
        return CARD_RESULT_FATAL_ERROR;
    }
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDAccess(card, ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    if (__CARDIsOpened(card, fileNo)) {
        return __CARDPutControlBlock(card, CARD_RESULT_BUSY);
    }
    card->startBlock = ent->startBlock;
    memset(ent, 0xff, sizeof(CARDDir));

    /// @todo Eliminate casts to #CARDCallback.
    card->apiCallback =
        callback ? callback : (CARDCallback) __CARDDefaultApiCallback;
    result = __CARDUpdateDir(chan, (CARDCallback) DeleteCallback);

    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}

s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback)
{
    CARDControl* card;
    s32 fileNo;
    s32 result;
    CARDDir* dir;
    CARDDir* ent;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    if (__CARDIsOpened(card, fileNo)) {
        return __CARDPutControlBlock(card, CARD_RESULT_BUSY);
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    card->startBlock = ent->startBlock;
    memset(ent, 0xff, sizeof(CARDDir));

    /// @todo Eliminate casts to #CARDCallback.
    card->apiCallback =
        callback ? callback : (CARDCallback) __CARDDefaultApiCallback;
    result = __CARDUpdateDir(chan, (CARDCallback) DeleteCallback);

    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}
