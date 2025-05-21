#ifndef _METROTRK_MSGBUF_H
#define _METROTRK_MSGBUF_H

#include <platform.h>

#include "MetroTRK/dserror.h"
#include "MetroTRK/mutex_TRK.h"

typedef unsigned char u128[16];
typedef int MessageBufferID;

#define TRKMessageBufferGet(buf, type, offset) (*(type*) (buf->data + offset))
#define kMessageBufferSize 0x800 + 0x80
#define NUM_BUFFERS 3

typedef struct MessageBuffer {
    /* 0x00 */ DSMutex fMutex;
    /* 0x00 */ bool fInUse;
    /* 0x04 */ u32 fLength;
    /* 0x08 */ u32 fPosition;
    /* 0x0C */ u8 fData[kMessageBufferSize];
} MessageBuffer; // size = 0x88C

typedef struct TRKMsgBufs {
    /* 0x00 */ MessageBuffer buffers[NUM_BUFFERS];
} TRKMsgBufs; // size = 0x19A4

/* 326C9C */ DSError TRK_InitializeMessageBuffers(void);
/* 326D14 */ DSError TRKGetFreeBuffer(int*, MessageBuffer**);
/* 326DB0 */ MessageBuffer* TRKGetBuffer(int);
/* 326DDC */ void TRKReleaseBuffer(int);
/* 326E44 */ void TRKResetBuffer(MessageBuffer*, u8);
/* 326E84 */ DSError TRKSetBufferPosition(MessageBuffer*, u32);
/* 326EB4 */ DSError TRKAppendBuffer(MessageBuffer*, const void*, size_t);
/* 326F58 */ DSError TRKReadBuffer(MessageBuffer*, void*, size_t);
DSError TRKInitializeMessageBuffers(void);

/* 326FE4 */ DSError TRKAppendBuffer1_ui16(MessageBuffer* buffer,
                                           const u16 data);
/* 327038 */ DSError TRKAppendBuffer1_ui32(MessageBuffer* buffer,
                                           const u32 data);
/* 32709C */ DSError TRKAppendBuffer1_ui64(MessageBuffer* buffer,
                                           const u64 data);
/* 327124 */ DSError TRKAppendBuffer_ui8(MessageBuffer* buffer, const u8* data,
                                         int count);
/* 32718C */ DSError TRKAppendBuffer_ui32(MessageBuffer* buffer,
                                          const u32* data, int count);

/* 327208 */ DSError TRKReadBuffer1_ui8(MessageBuffer* buffer, u8* data);
/* 32722C */ DSError TRKReadBuffer1_ui16(MessageBuffer* buffer, u16* data);
/* 3272AC */ DSError TRKReadBuffer1_ui32(MessageBuffer* buffer, u32* data);
/* 32733C */ DSError TRKReadBuffer1_ui64(MessageBuffer* buffer, u64* data);

/* 3273EC */ DSError TRKReadBuffer_ui8(MessageBuffer* buffer, u8* data,
                                       int count);
/* 327460 */ DSError TRKReadBuffer_ui32(MessageBuffer* buffer, u32* data,
                                        int count);

static inline DSError TRKAppendBuffer1_ui8(MessageBuffer* buffer,
                                           const u8 data)
{
    if (buffer->fPosition >= kMessageBufferSize) {
        return kMessageBufferOverflow;
    }

    buffer->fData[buffer->fPosition++] = data;
    buffer->fLength++;
    return kNoError;
}

extern TRKMsgBufs gTRKMsgBufs;

#endif
