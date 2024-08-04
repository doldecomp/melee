#include <dolphin.h>
#include <dolphin/mtx.h>
#include "fake_tgmath.h"

// TODO: A bunch of pointless void casts because of Mtx type-ness.
// Dunno how to resolve this at the moment.

void MTXInitStack(MTXStack *sPtr, u32 numMtx) {
    ASSERTMSGLINE(0x47, sPtr, "MTXInitStack():  NULL MtxStackPtr 'sPtr' ");
    ASSERTMSGLINE(0x48, sPtr->stackBase, "MTXInitStack():  'sPtr' contains a NULL ptr to stack memory ");
    ASSERTMSGLINE(0x49, numMtx, "MTXInitStack():  'numMtx' is 0 ");
    sPtr->numMtx = numMtx;
    sPtr->stackPtr = 0;
}

Mtx *MTXPush(MTXStack *sPtr, Mtx m) {
    ASSERTMSGLINE(0x65, sPtr, "MTXPush():  NULL MtxStackPtr 'sPtr' ");
    ASSERTMSGLINE(0x66, sPtr->stackBase, "MTXPush():  'sPtr' contains a NULL ptr to stack memory ");
    ASSERTMSGLINE(0x67, m, "MTXPush():  NULL MtxPtr 'm' ");
    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy((void*)m, (void*)sPtr->stackPtr);
    } else {
        ASSERTMSGLINE(0x76, ((((s32)sPtr->stackPtr - (s32)sPtr->stackBase) / 16) / 3) < (sPtr->numMtx - 1), "MTXPush():  stack overflow ");
        MTXCopy((void*)m, (void*)(sPtr->stackPtr + 1));
        sPtr->stackPtr++;
    }
    return sPtr->stackPtr;
}

Mtx *MTXPushFwd(MTXStack *sPtr, Mtx m) {
    ASSERTMSGLINE(0x9A, sPtr, "MTXPushFwd():  NULL MtxStackPtr 'sPtr' ");
    ASSERTMSGLINE(0x9B, sPtr->stackBase, "MTXPushFwd():  'sPtr' contains a NULL ptr to stack memory ");
    ASSERTMSGLINE(0x9C, m, "MTXPushFwd():  NULL MtxPtr 'm' ");

    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy((void*)m, (void*)sPtr->stackPtr);
    } else {
        ASSERTMSGLINE(0xAB, ((((s32)sPtr->stackPtr - (s32)sPtr->stackBase) / 16) / 3) < (sPtr->numMtx - 1), "MTXPushFwd():  stack overflow");
        MTXConcat((void*)sPtr->stackPtr, (void*)m, (void*)(sPtr->stackPtr + 1));
        sPtr->stackPtr++;
    }
    return sPtr->stackPtr;
}

Mtx *MTXPushInv(MTXStack *sPtr, Mtx m) {
    Mtx mInv;

    ASSERTMSGLINE(0xD5, sPtr, "MTXPushInv():  NULL MtxStackPtr 'sPtr' ");
    ASSERTMSGLINE(0xD6, sPtr->stackBase, "MTXPushInv():  'sPtr' contains a NULL ptr to stack memory ");
    ASSERTMSGLINE(0xD7, m, "MTXPushInv():  NULL MtxPtr 'm' ");
    MTXInverse((void*)m, (void*)&mInv);
    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy((void*)&mInv, (void*)sPtr->stackPtr);
    } else {
        ASSERTMSGLINE(0xE9, ((((s32)sPtr->stackPtr - (s32)sPtr->stackBase) / 16) / 3) < (sPtr->numMtx - 1), "MTXPushInv():  stack overflow");
        MTXConcat((void*)&mInv, (void*)sPtr->stackPtr, (void*)(sPtr->stackPtr + 1));
        sPtr->stackPtr++;
    }
    return sPtr->stackPtr;
}

Mtx *MTXPushInvXpose(MTXStack *sPtr, Mtx m) {
    Mtx mIT;

    ASSERTMSGLINE(0x114, sPtr, "MTXPushInvXpose():  NULL MtxStackPtr 'sPtr' ");
    ASSERTMSGLINE(0x115, sPtr->stackBase, "MTXPushInvXpose():  'sPtr' contains a NULL ptr to stack memory ");
    ASSERTMSGLINE(0x116, m, "MTXPushInvXpose():  NULL MtxPtr 'm' ");
    MTXInverse((void*)m, (void*)&mIT);
    MTXTranspose((void*)&mIT, (void*)&mIT);
    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy((void*)&mIT, (void*)sPtr->stackPtr);
    } else {
        ASSERTMSGLINE(0x129, ((((s32)sPtr->stackPtr - (s32)sPtr->stackBase) / 16) / 3) < (sPtr->numMtx - 1), "MTXPushInvXpose():  stack overflow ");
        MTXConcat((void*)sPtr->stackPtr, (void*)&mIT, (void*)(sPtr->stackPtr + 1));
        sPtr->stackPtr++;
    }
    return sPtr->stackPtr;
}

Mtx *MTXPop(MTXStack *sPtr) {
    ASSERTMSGLINE(0x145, sPtr, "MTXPop():  NULL MtxStackPtr 'sPtr' ");
    ASSERTMSGLINE(0x146, sPtr->stackBase, "MTXPop():  'sPtr' contains a NULL ptr to stack memory ");
    if (sPtr->stackPtr == NULL) {
        return NULL;
    }
    if (sPtr->stackBase == sPtr->stackPtr) {
        sPtr->stackPtr = NULL;
        return NULL;
    }
    sPtr->stackPtr--;
    return sPtr->stackPtr;
}

Mtx *MTXGetStackPtr(MTXStack *sPtr) {
    ASSERTMSGLINE(0x16B, sPtr, "MTXGetStackPtr():  NULL MtxStackPtr 'sPtr' ");
    ASSERTMSGLINE(0x16C, sPtr->stackBase, "MTXGetStackPtr():  'sPtr' contains a NULL ptr to stack memory ");
    return sPtr->stackPtr;
}
