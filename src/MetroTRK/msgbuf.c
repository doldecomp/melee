#include "msgbuf.h"

#include "MetroTRK/mem_TRK.h"
#include "MetroTRK/nubinit.h"

TRKMsgBufs gTRKMsgBufs;

static void TRKSetBufferUsed(MessageBuffer* b, bool state)
{
    b->fInUse = state;
}

DSError TRKInitializeMessageBuffers(void)
{
    int i;

    for (i = 0; i < NUM_BUFFERS; i++) {
        TRKInitializeMutex(&gTRKMsgBufs.buffers[i].fMutex);
        TRKAcquireMutex(&gTRKMsgBufs.buffers[i].fMutex);
        TRKSetBufferUsed(&gTRKMsgBufs.buffers[i], false);
        TRKReleaseMutex(&gTRKMsgBufs.buffers[i].fMutex);
    }

    return kNoError;
}

DSError TRKGetFreeBuffer(int* bufferIndexPtr, MessageBuffer** destBufPtr)
{
    DSError error = kNoMessageBufferAvailable;
    int i;
    *destBufPtr = NULL;

    for (i = 0; i < NUM_BUFFERS; i++) {
        MessageBuffer* buf = TRKGetBuffer(i);

        TRKAcquireMutex(&buf->fMutex);

        if (!buf->fInUse) {
            TRKResetBuffer(buf, 1);
            TRKSetBufferUsed(buf, true);
            *destBufPtr = buf;
            *bufferIndexPtr = i;
            error = kNoError;
            i = NUM_BUFFERS; // why not break? weird choice
        }

        TRKReleaseMutex(&buf->fMutex);
    }

    return error;
}

MessageBuffer* TRKGetBuffer(int index)
{
    MessageBuffer* buf = NULL;

    if (index >= 0 && index < NUM_BUFFERS) {
        buf = &gTRKMsgBufs.buffers[index];
    }

    return buf;
}

void TRKReleaseBuffer(int index)
{
    MessageBuffer* b;

    if (index == -1) {
        return;
    }

    if (index >= 0 && index < 3) {
        b = &gTRKMsgBufs.buffers[index];
        TRKAcquireMutex(&b->fMutex);
        TRKSetBufferUsed(b, 0);
        TRKReleaseMutex(&b->fMutex);
    }
}

void TRKResetBuffer(MessageBuffer* buf, u8 keepData)
{
    buf->fLength = 0;
    buf->fPosition = 0;

    if (!keepData) {
        TRK_memset(buf->fData, 0, kMessageBufferSize);
    }
}

DSError TRKSetBufferPosition(MessageBuffer* buf, u32 pos)
{
    DSError error = kNoError;

    if (pos > kMessageBufferSize) {
        error = kMessageBufferOverflow;
    } else {
        buf->fPosition = pos;
        // If the new position is past the current length,
        // update the length
        if (pos > buf->fLength) {
            buf->fLength = pos;
        }
    }

    return error;
}

DSError TRKAppendBuffer(MessageBuffer* buf, const void* data, size_t length)
{
    DSError error = kNoError; // r31
    u32 bytesLeft;

    // Return if no bytes to append
    if (length == 0) {
        return kNoError;
    }

    bytesLeft = kMessageBufferSize - buf->fPosition;

    // If there isn't enough space left in the buffer, change the number
    // of bytes to append to the remaning number of bytes
    if (bytesLeft < length) {
        error = kMessageBufferOverflow;
        length = bytesLeft;
    }

    if (length == 1) {
        // If the length of bytes to append is 1, just copy the byte over
        buf->fData[buf->fPosition] = ((u8*) data)[0];
    } else {
        // Otherwise, use memcpy
        TRK_memcpy(buf->fData + buf->fPosition, data, length);
    }

    // Update the position and length
    buf->fPosition += length;
    buf->fLength = buf->fPosition;

    return error;
}

DSError TRKReadBuffer(MessageBuffer* buf, void* data, size_t length)
{
    DSError error = kNoError;
    unsigned int bytesLeft;

    // Return if no bytes to read
    if (length == 0) {
        return kNoError;
    }

    bytesLeft = buf->fLength - buf->fPosition;

    // If the number of bytes to read exceeds the buffer length, change
    // the length to the remaining number of bytes
    if (length > bytesLeft) {
        error = kMessageBufferReadError;
        length = bytesLeft;
    }

    TRK_memcpy(data, buf->fData + buf->fPosition, length);
    buf->fPosition += length;
    return error;
}

DSError TRKAppendBuffer1_ui16(MessageBuffer* buffer, const u16 data)
{
    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*) &data;
    } else {
        byteData = (u8*) &data;
        bigEndianData = swapBuffer;

        bigEndianData[0] = byteData[1];
        bigEndianData[1] = byteData[0];
    }

    return TRKAppendBuffer(buffer, (const void*) bigEndianData, sizeof(data));
}

DSError TRKAppendBuffer1_ui32(MessageBuffer* buffer, const u32 data)
{
    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*) &data;
    } else {
        byteData = (u8*) &data;
        bigEndianData = swapBuffer;

        bigEndianData[0] = byteData[3];
        bigEndianData[1] = byteData[2];
        bigEndianData[2] = byteData[1];
        bigEndianData[3] = byteData[0];
    }

    return TRKAppendBuffer(buffer, (const void*) bigEndianData, sizeof(data));
}

DSError TRKAppendBuffer1_ui64(MessageBuffer* buffer, const u64 data)
{
    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*) &data;
    } else {
        byteData = (u8*) &data;
        bigEndianData = swapBuffer;

        bigEndianData[0] = byteData[7];
        bigEndianData[1] = byteData[6];
        bigEndianData[2] = byteData[5];
        bigEndianData[3] = byteData[4];
        bigEndianData[4] = byteData[3];
        bigEndianData[5] = byteData[2];
        bigEndianData[6] = byteData[1];
        bigEndianData[7] = byteData[0];
    }

    return TRKAppendBuffer(buffer, (const void*) bigEndianData, sizeof(data));
}

DSError TRKAppendBuffer_ui8(MessageBuffer* buffer, const u8* data, int count)
{
    DSError err;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < count; i++) {
        err = TRKAppendBuffer1_ui8(buffer, data[i]);
    }

    return err;
}

DSError TRKAppendBuffer_ui32(MessageBuffer* buffer, const u32* data, int count)
{
    DSError err;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < count; i++) {
        err = TRKAppendBuffer1_ui32(buffer, data[i]);
    }

    return err;
}

DSError TRKReadBuffer1_ui8(MessageBuffer* buffer, u8* data)
{
    return TRKReadBuffer(buffer, (void*) data, 1);
}

DSError TRKReadBuffer1_ui16(MessageBuffer* buffer, u16* data)
{
    DSError err;

    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*) data;
    } else {
        bigEndianData = swapBuffer;
    }

    err = TRKReadBuffer(buffer, (void*) bigEndianData, sizeof(*data));

    if (!gTRKBigEndian && err == kNoError) {
        byteData = (u8*) data;

        byteData[0] = bigEndianData[1];
        byteData[1] = bigEndianData[0];
    }

    return err;
}

DSError TRKReadBuffer1_ui32(MessageBuffer* buffer, u32* data)
{
    DSError err;

    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*) data;
    } else {
        bigEndianData = swapBuffer;
    }

    err = TRKReadBuffer(buffer, (void*) bigEndianData, sizeof(*data));

    if (!gTRKBigEndian && err == kNoError) {
        byteData = (u8*) data;

        byteData[0] = bigEndianData[3];
        byteData[1] = bigEndianData[2];
        byteData[2] = bigEndianData[1];
        byteData[3] = bigEndianData[0];
    }

    return err;
}

DSError TRKReadBuffer1_ui64(MessageBuffer* buffer, u64* data)
{
    DSError err;

    u8* bigEndianData;
    u8* byteData;
    u8 swapBuffer[sizeof(data)];

    if (gTRKBigEndian) {
        bigEndianData = (u8*) data;
    } else {
        bigEndianData = swapBuffer;
    }

    err = TRKReadBuffer(buffer, (void*) bigEndianData, sizeof(*data));

    if (!gTRKBigEndian && err == 0) {
        byteData = (u8*) data;

        byteData[0] = bigEndianData[7];
        byteData[1] = bigEndianData[6];
        byteData[2] = bigEndianData[5];
        byteData[3] = bigEndianData[4];
        byteData[4] = bigEndianData[3];
        byteData[5] = bigEndianData[2];
        byteData[6] = bigEndianData[1];
        byteData[7] = bigEndianData[0];
    }

    return err;
}

DSError TRKReadBuffer_ui8(MessageBuffer* buffer, u8* data, int count)
{
    DSError err;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < count; i++) {
        err = TRKReadBuffer1_ui8(buffer, &(data[i]));
    }

    return err;
}

DSError TRKReadBuffer_ui32(MessageBuffer* buffer, u32* data, int count)
{
    DSError err;
    int i;

    for (i = 0, err = kNoError; err == kNoError && i < count; i++) {
        err = TRKReadBuffer1_ui32(buffer, &(data[i]));
    }

    return err;
}
