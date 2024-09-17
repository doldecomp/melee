#include "hio.h"

#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>

static s32 Chan = -1;
static unsigned long Dev;
static HIOCallback ExiCallback;
static HIOCallback TxCallback;
static HIOCallback RxCallback;

static void ExtHandler(s32 chan, OSContext* context)
{
    Chan = -1;
    Dev = 0;
    if ((chan < 2)) {
        EXISetExiCallback(chan, NULL);
        return;
    }
}

static void ExiHandler(s32 chan, OSContext* context)
{
    if (ExiCallback) {
        ExiCallback();
    }
}

static void DbgHandler(__OSInterrupt interrupt, OSContext* context)
{
    struct OSContext exceptionContext;

    __PIRegs[0] = 0x1000;
    if (ExiCallback) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        ExiCallback();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void TxHandler(s32 chan, OSContext* context)
{
    EXIDeselect(Chan);
    EXIUnlock(Chan);
    if (TxCallback) {
        TxCallback();
    }
}

static void RxHandler(s32 chan, OSContext* context)
{
    EXIDeselect(Chan);
    EXIUnlock(Chan);
    if (RxCallback) {
        RxCallback();
    }
}

bool HIOEnumDevices(HIOEnumCallback callback)
{
    s32 chan;
    u32 id;

    if (Chan != -1 || callback == NULL) {
        return 0;
    }
    Dev = 0;
    for (chan = 0; chan <= 2; chan++) {
        if (chan < 2) {
            do {
            } while (EXIProbeEx(chan) == 0);
        }
        if ((EXIGetID(chan, Dev, &id) != 0) &&
            ((u32) (id + 0xFEFF0000) == 0U) && (callback(chan) == 0))
        {
            return 1;
        }
    }
    return 1;
}

bool HIOInit(s32 chan, HIOCallback callback)
{
    int err;
    u32 cmd;
    u32 id;

    if (__OSGetDIConfig() == 0xFFU) {
        Chan = -1;
        Dev = 0U;
        return 0;
    }
    if (Chan != -1) {
        return 1;
    }
    Chan = chan;
    ExiCallback = callback;
    TxCallback = NULL;
    RxCallback = NULL;
    if (chan < 2 && Dev == 0) {
        do {
        } while (EXIProbeEx(Chan) == 0);
        if (EXIAttach(Chan, ExtHandler) == 0) {
            Chan = -1;
            Dev = 0;
            return 0;
        }
    }
    if (EXILock(Chan, Dev, 0) == 0) {
        EXIDetach(Chan);
        Chan = -1;
        Dev = 0;
        return 0;
    }
    if (EXISelect(Chan, Dev, 0) == 0) {
        EXIUnlock(Chan);
        EXIDetach(Chan);
        Chan = -1;
        Dev = 0;
        return 0;
    }
    cmd = 0;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 2, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIImm(Chan, &id, 4, 0, 0);
    err |= !EXISync(Chan);
    err |= !EXIDeselect(Chan);
    EXIUnlock(Chan);
    if (err != 0 || id != 0x1010000) {
        if (chan < 2 && Dev == 0) {
            EXIDetach(Chan);
        }
        EXIUnlock(Chan);
        Chan = -1;
        Dev = 0;
        return 0;
    }
    if (ExiCallback) {
        if (chan < 2) {
            if (Dev == 0) {
                EXISetExiCallback(Chan, ExiHandler);
            } else {
                EXISetExiCallback(2, ExiHandler);
            }
        } else {
            __OSSetInterruptHandler(0x19, DbgHandler);
            __OSUnmaskInterrupts(0x40);
        }
    }
    return 1;
}

bool HIOReadMailbox(u32* word)
{
    int err;
    u32 cmd;

    if (Chan == -1 || __OSGetDIConfig() == 0xFFU) {
        return 0;
    }
    if (EXILock(Chan, Dev, 0) == 0) {
        return 0;
    }
    if (EXISelect(Chan, Dev, 4) == 0) {
        EXIUnlock(Chan);
        return 0;
    }
    cmd = 0x60000000;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 2, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIImm(Chan, word, 4, 0, 0);
    err |= !EXISync(Chan);
    err |= !EXIDeselect(Chan);
    EXIUnlock(Chan);
    return !err;
}

bool HIOWriteMailbox(u32 word)
{
    int err;
    u32 cmd;

    if (Chan == -1 || __OSGetDIConfig() == 0xFFU) {
        return 0;
    }
    if (EXILock(Chan, Dev, 0) == 0) {
        return 0;
    }
    if (EXISelect(Chan, Dev, 4) == 0) {
        EXIUnlock(Chan);
        return 0;
    }
    cmd = (word & 0x1FFFFFFF) | 0xC0000000;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 4, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIDeselect(Chan);
    EXIUnlock(Chan);
    return !err;
}

bool HIORead(u32 addr, void* buffer, s32 size)
{
    int err;
    u32 cmd;

    if (Chan == -1 || __OSGetDIConfig() == 0xFFU) {
        return 0;
    }

    if (EXILock(Chan, Dev, 0) == 0) {
        return 0;
    }
    if (EXISelect(Chan, Dev, 4) == 0) {
        EXIUnlock(Chan);
        return 0;
    }
    cmd = ((addr << 8) & 0x01FFFC00) | 0x20000000;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 4, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIDma(Chan, buffer, size, 0, NULL);
    err |= !EXISync(Chan);
    err |= !EXIDeselect(Chan);
    EXIUnlock(Chan);
    return !err;
}

bool HIOWrite(u32 addr, void* buffer, s32 size)
{
    int err;
    u32 cmd;

    if (Chan == -1 || __OSGetDIConfig() == 0xFFU) {
        return 0;
    }

    if (EXILock(Chan, Dev, 0) == 0) {
        return 0;
    }
    if (EXISelect(Chan, Dev, 4) == 0) {
        EXIUnlock(Chan);
        return 0;
    }
    cmd = ((addr << 8) & 0x01FFFC00) | 0xA0000000;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 4, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIDma(Chan, buffer, size, 1, NULL);
    err |= !EXISync(Chan);
    err |= !EXIDeselect(Chan);
    EXIUnlock(Chan);
    return !err;
}

bool HIOReadAsync(u32 addr, void* buffer, s32 size, HIOCallback callback)
{
    int err;
    u32 cmd;

    if (Chan == -1 || __OSGetDIConfig() == 0xFFU) {
        return 0;
    }

    RxCallback = callback;
    if (EXILock(Chan, Dev, 0) == 0) {
        return 0;
    }
    if (EXISelect(Chan, Dev, 4) == 0) {
        EXIUnlock(Chan);
        return 0;
    }
    cmd = ((addr << 8) & 0x01FFFC00) | 0x20000000;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 4, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIDma(Chan, buffer, size, 0, RxHandler);
    return !err;
}

bool HIOWriteAsync(u32 addr, void* buffer, s32 size, HIOCallback callback)
{
    int err;
    u32 cmd;

    if (Chan == -1 || __OSGetDIConfig() == 0xFFU) {
        return 0;
    }

    TxCallback = callback;
    if (EXILock(Chan, Dev, 0) == 0) {
        return 0;
    }
    if (EXISelect(Chan, Dev, 4) == 0) {
        EXIUnlock(Chan);
        return 0;
    }
    cmd = ((addr << 8) & 0x01FFFC00) | 0xA0000000;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 4, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIDma(Chan, buffer, size, 1, TxHandler);
    return !err;
}

bool HIOReadStatus(u32* status)
{
    int err;
    u32 cmd;

    if (Chan == -1 || __OSGetDIConfig() == 0xFFU) {
        return 0;
    }
    if (EXILock(Chan, Dev, 0) == 0) {
        return 0;
    }
    if (EXISelect(Chan, Dev, 4) == 0) {
        EXIUnlock(Chan);
        return 0;
    }
    cmd = 0x40000000;
    err = 0;
    err |= !EXIImm(Chan, &cmd, 2, 1, 0);
    err |= !EXISync(Chan);
    err |= !EXIImm(Chan, status, 4, 0, 0);
    err |= !EXISync(Chan);
    err |= !EXIDeselect(Chan);
    EXIUnlock(Chan);
    return !err;
}
