#include "nubinit.h"

#include "MetroTRK/dispatch.h"
#include "MetroTRK/dolphin_trk_glue.h"
#include "MetroTRK/msgbuf.h"
#include "MetroTRK/serpoll.h"
#include "MetroTRK/targimpl.h"
#include "MetroTRK/usr_put.h"

bool gTRKBigEndian;

DSError TRKInitializeNub(void)
{
    DSError result;
    DSError resultTemp;

    result = TRKInitializeEndian();

    if (result == kNoError) {
        usr_put_initialize();
    }

    if (result == kNoError) {
        result = TRKInitializeEventQueue();
    }

    if (result == kNoError) {
        result = TRKInitializeMessageBuffers();
    }

    // v0.1 only
    if (result == kNoError) {
        result = TRKInitializeDispatcher();
    }

    if (result == kNoError) {
        // 0xE100 only on v0.1
        resultTemp =
            TRKInitializeIntDrivenUART(0xE100, 1, 0, &gTRKInputPendingPtr);
        TRKTargetSetInputPendingPtr(gTRKInputPendingPtr);
        if (resultTemp != kNoError) {
            result = resultTemp;
        }
    }

    if (result == kNoError) {
        result = TRKInitializeSerialHandler();
    }

    if (result == kNoError) {
        result = TRKInitializeTarget();
    }

    return result;
}

DSError TRKTerminateNub(void)
{
    TRKTerminateSerialHandler();
    return kNoError;
}

void TRKNubWelcome(void)
{
    TRK_board_display("MetroTRK for Dolphin v0.5");
}

bool TRKInitializeEndian(void)
{
    u8 bendian[4];
    bool result = false;

    gTRKBigEndian = true;

    bendian[0] = 0x12;
    bendian[1] = 0x34;
    bendian[2] = 0x56;
    bendian[3] = 0x78;

    if (*(u32*) bendian == 0x12345678) {
        gTRKBigEndian = true;
    } else if (*(u32*) bendian == 0x78563412) {
        gTRKBigEndian = false;
    } else {
        result = true;
    }

    return result;
}