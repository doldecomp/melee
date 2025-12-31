#include "mnvibration.h"

extern void* mnVibration_804D6C28;

void* mnVibration_802474C4(s32 arg0) {
    void* node = *(void**)((u8*)*(void**)((u8*)mnVibration_804D6C28 + 0x2C) + 0x50);
    if (node == NULL) {
        node = NULL;
    } else {
        node = *(void**)((u8*)node + 0x10);
    }
    for (; arg0 > 0; arg0--) {
        if (node == NULL) {
            node = NULL;
        } else {
            node = *(void**)((u8*)node + 0x8);
        }
    }
    return node;
}
