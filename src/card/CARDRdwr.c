#include <dolphin.h>
#include <dolphin/card.h>

#include "__card.h"

// functions
static void BlockReadCallback(long chan, long result);
static void BlockWriteCallback(long chan, long result);

static void BlockReadCallback(long chan, long result) {
    struct CARDControl * card;
    void (* callback)(long, long);

    card = &__CARDBlock[chan];

    if ((result >= 0)) {
        card->xferred += 0x200;
        card->addr += 0x200;
        ((u8*)card->buffer) += 0x200;

        if (--card->repeat > 0) {
            result = __CARDReadSegment(chan, BlockReadCallback);
            if (result >= 0) {
                return;
            }
        }
    }
    if (!card->apiCallback) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = NULL;
        callback(chan, result);
    }
}

long __CARDRead(long chan, unsigned long addr, long length, void * dst, void (* callback)(long, long)) {
    struct CARDControl * card;

    ASSERTLINE(0x58, 0 < length && length % CARD_SEG_SIZE == 0);
    ASSERTLINE(0x59, 0 <= chan && chan < 2);
    card = &__CARDBlock[chan];
    if (card->attached == 0) {
        return CARD_RESULT_NOCARD;
    }
    card->xferCallback = callback;
    card->repeat = (length / 512u);
    card->addr = addr;
    card->buffer = dst;
    return __CARDReadSegment(chan, BlockReadCallback);
}

static void BlockWriteCallback(long chan, long result) {
    struct CARDControl * card;
    void (* callback)(long, long);

    card = &__CARDBlock[chan];
    if (result >= 0) {
        card->xferred += 0x80;
        card->addr += 0x80;
        ((u8*)card->buffer) += 0x80;

        if (--card->repeat > 0) {
            result = __CARDWritePage(chan, BlockWriteCallback);
            if (result >= 0) {
                return;
            }
        }
    }
    if (!card->apiCallback) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = NULL;
        callback(chan, result);
    }
}

long __CARDWrite(long chan, unsigned long addr, long length, void * dst, void (* callback)(long, long)) {
    struct CARDControl * card;

    ASSERTLINE(0x95, 0 < length && length % CARD_PAGE_SIZE == 0);
    ASSERTLINE(0x96, 0 <= chan && chan < 2);
    card = &__CARDBlock[chan];
    if (card->attached == 0) {
        return CARD_RESULT_NOCARD;
    }
    card->xferCallback = callback;
    card->repeat = (length / 128u);
    card->addr = addr;
    card->buffer = dst;
    return __CARDWritePage(chan, BlockWriteCallback);
}

long CARDGetXferredBytes(long chan) {
    ASSERTLINE(0xB4, 0 <= chan && chan < 2);
    return __CARDBlock[chan].xferred;
}
