#include <dolphin.h>
#include <dolphin/ax.h>
#include <dolphin/axfx.h>

void AXFXDelayCallback(struct AXFX_BUFFERUPDATE * bufferUpdate, struct AXFX_DELAY * delay) {
    long l;
    long r;
    long s;
    long * lBuf;
    long * rBuf;
    long * sBuf;
    u32 i;
    long * left;
    long * right;
    long * sur;

    left = bufferUpdate->left;
    right = bufferUpdate->right;
    sur = bufferUpdate->surround;
    lBuf = delay->left + (delay->currentPos[0] * 0xA0);
    rBuf = delay->right + (delay->currentPos[1] * 0xA0);
    sBuf = delay->sur + (delay->currentPos[2] * 0xA0);

    for(i = 0; i < 160; i++) {
        l = *lBuf;
        r = *rBuf;
        s = *sBuf;
        *lBuf++ = *left + ((s32)(l * delay->currentFeedback[0]) >> 7);
        *rBuf++ = *right + ((s32)(r * delay->currentFeedback[1]) >> 7);
        *sBuf++ = *sur + ((s32)(s * delay->currentFeedback[2]) >> 7);
        *left++ = (s32)(l * delay->currentOutput[0]) >> 7;
        *right++ = (s32)(r * delay->currentOutput[1]) >> 7;
        *sur++ = (s32)(s * delay->currentOutput[2]) >> 7;
    }
    delay->currentPos[0] = (s32) ((delay->currentPos[0] + 1) % delay->currentSize[0]);
    delay->currentPos[1] = (s32) ((delay->currentPos[1] + 1) % delay->currentSize[1]);
    delay->currentPos[2] = (s32) ((delay->currentPos[2] + 1) % delay->currentSize[2]);
}

int AXFXDelaySettings(struct AXFX_DELAY * delay) {
    unsigned long i;
    long * l;
    long * r;
    long * s;
    int old;

    AXFXDelayShutdown(delay);
    old = OSDisableInterrupts();

    for(i = 0; i < 3; i++) {
        delay->currentSize[i] = (((delay->delay[i] - 5) << 5) + 0x9F) / 160U;
        delay->currentPos[i] = 0;
        delay->currentFeedback[i] = (delay->feedback[i] << 7) / 100U;
        delay->currentOutput[i] = (delay->output[i] << 7) / 100U;
    }
    delay->left = OSAllocFromHeap(__OSCurrHeap, delay->currentSize[0] * 0xA0 * 4);
    delay->right = OSAllocFromHeap(__OSCurrHeap, delay->currentSize[1] * 0xA0 * 4);
    delay->sur = OSAllocFromHeap(__OSCurrHeap, delay->currentSize[2] * 0xA0 * 4);
    ASSERTLINE(0x47, delay->left!=NULL);
    ASSERTLINE(0x48, delay->right!=NULL);
    ASSERTLINE(0x49, delay->sur!=NULL);
    l = delay->left;
    r = delay->right;
    s = delay->sur;
    for(i = 0; i < delay->currentSize[0] * 0xA0; i++) {
        *l++ = 0;
    }
    for(i = 0; i < delay->currentSize[1] * 0xA0; i++) {
        *r++ = 0;
    }
    for(i = 0; i < delay->currentSize[2] * 0xA0; i++) {
        *s++ = 0;
    }
    OSRestoreInterrupts(old);
    return 1;
}

int AXFXDelayInit(struct AXFX_DELAY * delay) {
    int old;

    old = OSDisableInterrupts();
    delay->left = NULL;
    delay->right = NULL;
    delay->sur = NULL;
    OSRestoreInterrupts(old);
    AXFXDelaySettings(delay);
}

int AXFXDelayShutdown(struct AXFX_DELAY * delay) {
    int old;

    old = OSDisableInterrupts();
    if (delay->left) {
        OSFreeToHeap(__OSCurrHeap, delay->left);
    }
    if (delay->right) {
        OSFreeToHeap(__OSCurrHeap, delay->right);
    }
    if (delay->sur) {
        OSFreeToHeap(__OSCurrHeap, delay->sur);
    }
    OSRestoreInterrupts(old);
    return 1;
}
