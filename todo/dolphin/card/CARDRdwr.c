#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDRdwr.h>

static void BlockReadCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    card->xferred += CARD_SEG_SIZE;

    card->addr += CARD_SEG_SIZE;
    card->buffer = (u8*) card->buffer + CARD_SEG_SIZE;
    if (--card->repeat <= 0) {
        goto error;
    }

    /// @todo Eliminate cast to #CARDCallback.
    result = __CARDReadSegment(chan, (CARDCallback) BlockReadCallback);

    if (result < 0) {
        goto error;
    }
    return;

error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = 0;
        callback(chan, result);
    }
}

s32 __CARDRead(s32 chan, u32 addr, u32 length, void* dst,
               CARDCallback callback)
{
    CARDControl* card = &__CARDBlock[chan];
    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    card->xferCallback = callback;
    card->repeat = (int) (length / CARD_SEG_SIZE);
    card->addr = addr;
    card->buffer = dst;

    /// @todo Eliminate cast to #CARDCallback.
    return __CARDReadSegment(chan, (CARDCallback) BlockReadCallback);
}

static void BlockWriteCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    card->xferred += CARD_PAGE_SIZE;

    card->addr += CARD_PAGE_SIZE;
    card->buffer = (u8*) card->buffer + CARD_PAGE_SIZE;
    if (--card->repeat <= 0) {
        goto error;
    }

    /// @todo Eliminate cast to #CARDCallback.
    result = __CARDWritePage(chan, (CARDCallback) BlockWriteCallback);

    if (result < 0) {
        goto error;
    }

    return;

error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = 0;
        callback(chan, result);
    }
}

s32 __CARDWrite(s32 chan, u32 addr, u32 length, void* dst,
                CARDCallback callback)
{
    CARDControl* card = &__CARDBlock[chan];
    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    card->xferCallback = callback;
    card->repeat = length / CARD_PAGE_SIZE;
    card->addr = addr;
    card->buffer = dst;

    return __CARDWritePage(chan, (CARDCallback) BlockWriteCallback);
}

/// @todo Used only by #hsd_803AAA48
#pragma push
#pragma force_active on
u32 CARDGetXferredBytes(s32 chan)
{
    return __CARDBlock[chan].xferred;
}
#pragma pop
