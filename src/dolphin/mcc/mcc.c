#include "mcc.h"

static bool gIsChannelinfoDirty = true;
static u8 gLastError;

/// #callbackEventStream

/// #MCCStreamOpen

/// #MCCStreamClose

/// #MCCStreamWrite

/// #LoadChannelInfo

/// #FlushChannelInfo

void SetChannelInfoDirty(bool dirty)
{
    gIsChannelinfoDirty = dirty;
}

/// #MakeMemoryMap

/// #SearchFreeBlocks

/// #NotifyCompulsorily

/// #WaitAMinute

/// #MailboxCheck

/// #MCCExiCallback

/// #MCCTxCallback

/// #MCCRxCallback

/// #mccInitializeCheck

/// #MCCInit

/// #MCCExit

/// #MCCEnumDevices

/// #MCCGetFreeBlocks

u8 MCCGetLastError(void)
{
    return gLastError;
}

/// #MCCGetChannelInfo

/// #MCCGetConnectionStatus

/// #MCCNotify

/// #MCCSetChannelEventMask

/// #MCCOpen

/// #MCCClose

/// #MCCRead

/// #MCCWrite

/// #MCCCheckAsyncDone
