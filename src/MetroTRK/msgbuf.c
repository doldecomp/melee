#include "msgbuf.h"

void TRKSetBufferUsed(UNK_T arg0, int arg1)
{
    M2C_FIELD(arg0, int*, 4) = arg1;
}

/// #TRKInitializeMessageBuffers

/// #TRKGetFreeBuffer

/// #TRKGetBuffer

/// #TRKReleaseBuffer

/// #TRKResetBuffer

/// #TRKSetBufferPosition

/// #TRKAppendBuffer

/// #TRKReadBuffer

/// #TRKAppendBuffer1_ui16

/// #TRKAppendBuffer1_ui32

/// #TRKAppendBuffer1_ui64

/// #TRKAppendBuffer_ui8

/// #TRKAppendBuffer_ui32

/// #TRKReadBuffer1_ui8

/// #TRKReadBuffer1_ui16

/// #TRKReadBuffer1_ui32

/// #TRKReadBuffer1_ui64

/// #TRKReadBuffer_ui8

/// #TRKReadBuffer_ui32
