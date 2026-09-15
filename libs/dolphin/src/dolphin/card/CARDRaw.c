#include <dolphin.h>
#include <dolphin/card.h>

#include "__card.h"

long __CARDRawReadAsync(long chan, void * buf, long length, long offset, void (* callback)(long, long)) {
    struct CARDControl * card;
    long result;

    ASSERTLINE(0x36, buf && ((u32) buf % 32) == 0);

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    ASSERTLINE(0x3E, 0 < length && (length % CARD_SEG_SIZE) == 0 && length < CARD_MAX_SIZE);
    ASSERTLINE(0x3F, (offset % card->sectorSize) == 0);
    DCInvalidateRange(buf, length);
    result = __CARDRead(chan, offset, length, buf, callback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}

long __CARDRawRead(long chan, void * buf, long length, long offset) {
    long result = __CARDRawReadAsync(chan, buf, length, offset, &__CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(chan);
}
