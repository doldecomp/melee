#include "serpoll.h"

#include "MetroTRK/dolphin_trk_glue.h"
#include "MetroTRK/msgbuf.h"
#include "MetroTRK/msghndlr.h"
#include "MetroTRK/nubevent.h"

void* gTRKInputPendingPtr;
static FramingState gTRKFramingState;

DSError TRKInitializeSerialHandler(void)
{
    gTRKFramingState.fBufferID = -1;
    gTRKFramingState.fReceiveState = 0;
    gTRKFramingState.fEscape = 0;
    return kNoError;
}

DSError TRKTerminateSerialHandler(void)
{
    return kNoError;
}

void TRKProcessInput(MessageBufferID bufID)
{
    NubEvent event;

    TRKConstructEvent(&event, 2);
    event.fMessageBufferID = bufID;
    gTRKFramingState.fBufferID = -1;
    TRKPostEvent(&event);
}

void TRKGetInput(void)
{
    MessageBuffer* msgbuffer;
    MessageBufferID bufID;
    u8 command;

    bufID = TRKTestForPacket();

    if (bufID != -1) {
        msgbuffer = TRKGetBuffer(bufID);
        TRKSetBufferPosition(msgbuffer, 0);
        TRKReadBuffer1_ui8(msgbuffer, &command);
        if (command < 0x80) {
            TRKProcessInput(bufID);
        } else {
            TRKReleaseBuffer(bufID);
        }
    }
}

MessageBufferID TRKTestForPacket(void)
{
    int bytes;
    int batch;
    DSError err;
    MessageBuffer* b;
    int id;

    bytes = TRKPollUART();

    if (bytes > 0) {
        TRKGetFreeBuffer(&id, &b);
        if (bytes > 0x880) {
            for (; bytes > 0; bytes -= batch) {
                batch = bytes > 0x880 ? 0x880 : bytes;
                TRK_ReadUARTN(b->fData, batch);
            }
            TRKStandardACK(b, kDSReplyNAK, 6);
        } else {
            err = TRK_ReadUARTN(b->fData, bytes);
            if (err == kNoError) {
                b->fLength = bytes;
                return id;
            }
        }
    }

    if (id != -1) {
        TRKReleaseBuffer(id);
    }
    return -1;
}