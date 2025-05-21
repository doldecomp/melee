#ifndef _METROTRK_SERPOLL_H
#define _METROTRK_SERPOLL_H

#include <platform.h>

#include "MetroTRK/msgbuf.h"
#include "MetroTRK/trk.h"

typedef unsigned char FCSType;

typedef enum ReceiverState {
    kWaitFlag = 0,
    kFoundFlag = 1,
    kInFrame = 2,
    kFrameOverflow = 3
} ReceiverState;

typedef struct FramingState {
    /* 0x00 */ MessageBufferID fBufferID;
    /* 0x04 */ MessageBuffer* fBuffer;
    /* 0x08 */ u8 fReceiveState;
    /* 0x0C */ int fEscape;
    /* 0x10 */ FCSType fFCS;
} FramingState; // size = 0x11

void TRKGetInput(void);
void TRKProcessInput(int);
DSError TRKInitializeSerialHandler(void);
DSError TRKTerminateSerialHandler(void);
MessageBufferID TRKTestForPacket(void);

extern void* gTRKInputPendingPtr;

#endif
