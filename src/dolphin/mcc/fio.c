#include "fio.h"

/* 4D70DC */ static s32 gProcBusy;

/// #fioMccChannelEvent

/// #FIOInit

/// #FIOExit

/// #FIOQuery

/// #FIOFopen

/// #FIOFclose

/// #FIOFwrite

/// #fioPacketMakeHeader

/// #fioPacketSendPacket

/// #fioPacketReceiveResult

void fioPacketReceiveDone(void)
{
    gProcBusy = 0;
}

/// #fioPacketWrite

/// #fioPacketResultWrite
