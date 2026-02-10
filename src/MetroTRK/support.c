#include "support.h"

#include "MetroTRK/msg.h"
#include "MetroTRK/msgcmd.h"
#include "MetroTRK/serpoll.h"

#include <dolphin/os.h>

DSError TRKSuppAccessFile(u32 file_handle, u8* data, size_t* count,
                          u8* io_result, bool need_reply, bool read)
{
    MessageBuffer* replyBuffer;
    int replyBufferId;
    u32 length;
    MessageBuffer* buffer;
    int bufferId;
    DSError error;
    u32 i;
    u16 replyLength;
    u8 replyIOResult;
    bool exit;

    if (data == NULL || *count == 0) {
        return kParameterError;
    }

    exit = false;
    *io_result = kDSIONoError;
    i = 0;
    error = kNoError;
    while (!exit && i < *count && error == kNoError && *io_result == 0) {
        if (*count - i > 0x800) {
            length = 0x800;
        } else {
            length = *count - i;
        }

        error = TRKGetFreeBuffer(&bufferId, &buffer);

        if (error == kNoError) {
            error = TRKAppendBuffer1_ui8(buffer,
                                         read ? kDSReadFile : kDSWriteFile);
        }

        if (error == kNoError) {
            error = TRKAppendBuffer1_ui32(buffer, file_handle);
        }

        if (error == kNoError) {
            error = TRKAppendBuffer1_ui16(buffer, length);
        }

        if (!read && error == kNoError) {
            error = TRKAppendBuffer_ui8(buffer, data + i, length);
        }

        if (error == kNoError) {
            if (need_reply) {
                replyLength = 0;
                replyIOResult = 0;

                /// @todo fake match
                error =
                    (0, TRKRequestSend(buffer, &replyBufferId, read ? 5 : 5, 3,
                                       !(read && file_handle == 0)));

                if (error == kNoError) {
                    replyBuffer = (MessageBuffer*) TRKGetBuffer(replyBufferId);
                    TRKSetBufferPosition(replyBuffer, 2);
                }

                if (error == kNoError) {
                    error = TRKReadBuffer1_ui8(replyBuffer, &replyIOResult);
                }

                if (error == kNoError) {
                    error = TRKReadBuffer1_ui16(replyBuffer, &replyLength);
                }

                if (read && error == kNoError) {
                    if (replyBuffer->fLength != replyLength + 5) {
                        replyLength = replyBuffer->fLength - 5;
                        if (replyIOResult == 0) {
                            replyIOResult = 1;
                        }
                    }

                    if (replyLength <= length) {
                        error = TRKReadBuffer_ui8(replyBuffer, data + i,
                                                  replyLength);
                    }
                }

                if (replyLength != length) {
                    if ((!read || replyLength >= length) && replyIOResult == 0)
                    {
                        replyIOResult = 1;
                    }
                    length = replyLength;
                    exit = true;
                }

                *io_result = (DSIOResult) replyIOResult;
                TRKReleaseBuffer(replyBufferId);
            } else {
                error = TRKMessageSend(buffer);
            }
        }

        TRKReleaseBuffer(bufferId);
        i += length;
    }

    *count = i;
    return error;
}

DSError TRKRequestSend(MessageBuffer* msgBuf, int* bufferId, u32 p1, u32 p2,
                       int p3)
{
    int error = kNoError;
    MessageBuffer* buffer;
    u32 timer;
    int tries;
    u8 msg_error;
    u8 msg_command;
    bool badReply = true;

    *bufferId = -1;

    for (tries = p2 + 1; tries != 0 && *bufferId == -1 && error == kNoError;
         tries--)
    {
        error = TRKMessageSend(msgBuf);
        if (error == kNoError) {
            if (p3) {
                timer = 0;
            }

            while (true) {
                do {
                    *bufferId = TRKTestForPacket();
                    if (*bufferId != -1) {
                        break;
                    }
                } while (!p3 || ++timer < 79999980);

                if (*bufferId == -1) {
                    break;
                }

                badReply = false;

                buffer = TRKGetBuffer(*bufferId);
                TRKSetBufferPosition(buffer, 0);

                if ((error = TRKReadBuffer1_ui8(buffer, &msg_command)) !=
                    kNoError)
                {
                    break;
                }

                if (msg_command >= kDSReplyACK) {
                    break;
                }

                TRKProcessInput(*bufferId);
                *bufferId = -1;
            }

            if (*bufferId != -1) {
                if (buffer->fLength < p1) {
                    badReply = true;
                }
                if (error == kNoError && !badReply) {
                    error = TRKReadBuffer1_ui8(buffer, &msg_error);
                }
                if (error == kNoError && !badReply) {
                    if (msg_command != kDSReplyACK ||
                        msg_error != kDSReplyNoError)
                    {
                        badReply = true;
                    }
                }
                if (error != kNoError || badReply) {
                    TRKReleaseBuffer(*bufferId);
                    *bufferId = -1;
                }
            }
        }
    }

    if (*bufferId == -1) {
        error = kWaitACKError;
    }

    return error;
}
