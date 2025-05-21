#include "notify.h"

#include "MetroTRK/msgbuf.h"
#include "MetroTRK/support.h"
#include "MetroTRK/targimpl.h"

DSError TRKDoNotifyStopped(u8 cmdId)
{
    DSError result;
    int sp8;
    MessageBuffer* buffer;
    int spC;

    result = TRKGetFreeBuffer(&spC, &buffer);

    if (result == kNoError) {
        result = TRKAppendBuffer1_ui8(buffer, cmdId);

        if (result == kNoError) {
            if (cmdId == kDSNotifyStopped) {
                TRKTargetAddStopInfo(buffer);
            } else {
                TRKTargetAddExceptionInfo(buffer);
            }
        }

        result = TRKRequestSend(buffer, &sp8, 2, 3, 1);

        if (result == kNoError) {
            TRKReleaseBuffer(sp8);
        }

        TRKReleaseBuffer(spC);
    }

    return result;
}
