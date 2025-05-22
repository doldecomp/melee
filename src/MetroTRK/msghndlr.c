#include "msghndlr.h"

#include "MetroTRK/dolphin_trk_glue.h"
#include "MetroTRK/mem_TRK.h"
#include "MetroTRK/msg.h"
#include "MetroTRK/msgbuf.h"
#include "MetroTRK/nubevent.h"
#include "MetroTRK/target_options.h"
#include "MetroTRK/targimpl.h"

#include <dolphin/os.h>

extern void __TRK_copy_vectors(void);
extern void __TRK_reset(void);

void TRKMessageIntoReply(MessageBuffer* b, MessageCommandID commandId,
                         DSReplyError replyError)
{
    TRKResetBuffer(b, true);

    if (b->fPosition < kMessageBufferSize) {
        b->fData[b->fPosition++] = commandId;
        b->fLength++;
    }

    if (b->fPosition < kMessageBufferSize) {
        b->fData[b->fPosition++] = replyError;
        b->fLength++;
    }
}

static DSError TRKSendACK(MessageBuffer* b)
{
    DSError error;
    s32 i = 3;

    while (i > 0) {
        error = TRKMessageSend(b);
        i--;

        if (error == kNoError) {
            break;
        }
    }

    return error;
}

DSError TRKStandardACK(MessageBuffer* b, MessageCommandID commandId,
                       DSReplyError replyError)
{
    TRKMessageIntoReply(b, commandId, replyError);
    return TRKSendACK(b);
}

DSError TRKDoUnsupported(MessageBuffer* b)
{
    return TRKStandardACK(b, kDSReplyACK, kDSReplyUnsupportedCommandError);
}

DSError TRKDoConnect(MessageBuffer* b)
{
    return TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);
}

DSError TRKDoDisconnect(MessageBuffer* b)
{
    DSError error = TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);
    NubEvent event;

    if (error == kNoError) {
        TRKConstructEvent(&event, 1);
        TRKPostEvent(&event);
    }

    return error;
}

DSError TRKDoReset(MessageBuffer* b)
{
    TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);
    __TRK_reset();
    return kNoError;
}

DSError TRKDoOverride(MessageBuffer* b)
{
    TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);
    __TRK_copy_vectors();
    return kNoError;
}

DSError TRKDoVersions(MessageBuffer* buf)
{
    DSVersions version;
    DSError error;

    if (buf->fLength != 1) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKMessageIntoReply(buf, kDSReplyACK, kDSReplyNoError);
    error = TRKTargetVersions(&version);

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, version.kernelMajor);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, version.kernelMinor);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, version.protocolMajor);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, version.protocolMinor);
    }

    if (error != kNoError) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyCWDSError);
    }

    return TRKSendACK(buf);
}

DSError TRKDoSupportMask(MessageBuffer* buf)
{
    DSSupportMask mask;
    DSError error;

    if (buf->fLength != 1) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKMessageIntoReply(buf, kDSReplyACK, kDSReplyNoError);

    error = TRKTargetSupportMask(&mask);

    if (error == kNoError) {
        error = TRKAppendBuffer(buf, &mask, sizeof(DSSupportMask));
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, 2);
    }

    if (error != kNoError) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyCWDSError);
    }

    return TRKSendACK(buf);
}

DSError TRKDoCPUType(MessageBuffer* buf)
{
    DSError error;
    DSCPUType type;

    if (buf->fLength != 1) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKMessageIntoReply(buf, kDSReplyACK, kDSReplyNoError);
    error = TRKTargetCPUType(&type);

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, type.cpuMajor);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, type.cpuMinor);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, type.bigEndian);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, type.defaultTypeSize);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, type.fpTypeSize);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, type.extended1TypeSize);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui8(buf, type.extended2TypeSize);
    }

    if (error != kNoError) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyCWDSError);
    }

    return TRKSendACK(buf);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
DSError TRKDoReadMemory(MessageBuffer* buf)
{
    u8 buffer[0x800] ATTRIBUTE_ALIGN(32);
    size_t sp10;
    u32 spC;
    u16 spA;
    u8 sp9;
    u8 sp8;
    DSReplyError reply;
    DSError error;

    if (buf->fLength != 8) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKSetBufferPosition(buf, 0);

    error = TRKReadBuffer1_ui8(buf, &sp8);

    if (error == kNoError) {
        error = TRKReadBuffer1_ui8(buf, &sp9);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui16(buf, &spA);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui32(buf, &spC);
    }

    if (sp9 & 2) {
        return TRKStandardACK(buf, kDSReplyACK,
                              kDSReplyUnsupportedOptionError);
    }

    if (spA > sizeof(buffer)) {
        return TRKStandardACK(buf, kDSReplyACK, kDSReplyParameterError);
    }

    TRKMessageIntoReply(buf, kDSReplyACK, kDSReplyNoError);
    if (error == kNoError) {
        sp10 = spA;
        error = TRKTargetAccessMemory(
            buffer, spC, &sp10, sp9 & 8 ? kUserMemory : kDebuggerMemory, 1);
        spA = sp10;

        if (error == kNoError) {
            error = TRKAppendBuffer1_ui16(buf, spA);
        }

        if (error == kNoError) {
            error = TRKAppendBuffer(buf, buffer, sp10);
        }
    }

    if (error != kNoError) {
        switch (error) {
        case kCWDSException:
            reply = kDSReplyCWDSException;
            break;
        case kInvalidMemory:
            reply = kDSReplyInvalidMemoryRange;
            break;
        case kInvalidRegister:
        default:
            reply = kDSReplyCWDSError;
            break;
        }

        return TRKStandardACK(buf, kDSReplyACK, reply);
    }

    return TRKSendACK(buf);
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
DSError TRKDoWriteMemory(MessageBuffer* b)
{
    u8 buffer[0x800] ATTRIBUTE_ALIGN(32);
    size_t sp10;
    u32 spC;
    u16 spA;
    u8 sp9;
    u8 sp8;
    DSReplyError reply;
    DSError error;

    if (b->fLength <= 8) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKSetBufferPosition(b, 0);

    error = TRKReadBuffer1_ui8(b, &sp8);

    if (error == kNoError) {
        error = TRKReadBuffer1_ui8(b, &sp9);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui16(b, &spA);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui32(b, &spC);
    }

    if (sp9 & 2) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyUnsupportedOptionError);
    }

    if (b->fLength != spA + 8 || spA > sizeof(buffer)) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyParameterError);
    }

    if (error == kNoError) {
        sp10 = spA;
        error = TRKReadBuffer(b, buffer, sp10);

        if (error == kNoError) {
            error = TRKTargetAccessMemory(
                buffer, spC, &sp10, sp9 & 8 ? kUserMemory : kDebuggerMemory,
                0);
        }

        spA = sp10;
    }

    if (error == kNoError) {
        TRKMessageIntoReply(b, kDSReplyACK, kDSReplyNoError);
    }

    if (error == kNoError) {
        error = TRKAppendBuffer1_ui16(b, spA);
    }

    if (error != kNoError) {
        switch (error) {
        case kCWDSException:
            reply = kDSReplyCWDSException;
            break;
        case kInvalidMemory:
            reply = kDSReplyInvalidMemoryRange;
            break;
        case kInvalidRegister:
        default:
            reply = kDSReplyCWDSError;
            break;
        }

        return TRKStandardACK(b, kDSReplyACK, reply);
    }

    return TRKSendACK(b);
}
#pragma clang diagnostic pop

DSError TRKDoReadRegisters(MessageBuffer* b)
{
    size_t sp10;
    u16 spC;
    u16 spA;
    u8 sp9;
    u8 sp8;
    DSError error;
    DSReplyError reply;

    if (b->fLength != 6) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKSetBufferPosition(b, 0);

    error = TRKReadBuffer1_ui8(b, &sp8);

    if (error == kNoError) {
        error = TRKReadBuffer1_ui8(b, &sp9);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui16(b, &spA);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui16(b, &spC);
    }

    if (!TRKTargetStopped()) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyNotStopped);
    }

    if (spA > spC) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyInvalidRegisterRange);
    }

    if (error == kNoError) {
        TRKMessageIntoReply(b, kDSReplyACK, kDSReplyNoError);
    }

    switch (sp9 & 7) {
    case 0:
        error = TRKTargetAccessDefault((u32) spA, (u32) spC, b, &sp10, 1);
        break;
    case 1:
        error = TRKTargetAccessFP((u32) spA, (u32) spC, b, &sp10, 1);
        break;
    case 2:
        error = TRKTargetAccessExtended1((u32) spA, (u32) spC, b, &sp10, 1);
        break;
    case 3:
        error = TRKTargetAccessExtended2((u32) spA, (u32) spC, b, &sp10, 1);
        break;
    default:
        error = kUnsupportedError;
        break;
    }

    if (error != kNoError) {
        switch (error) {
        case kUnsupportedError: /* switch 1 */
            reply = kDSReplyUnsupportedOptionError;
            break;
        case kInvalidRegister:
            reply = kDSReplyInvalidRegisterRange;
            break;
        case kCWDSException:
            reply = kDSReplyCWDSException;
            break;
        default:
            reply = kDSReplyCWDSError;
            break;
        }

        return TRKStandardACK(b, kDSReplyACK, reply);
    }

    return TRKSendACK(b);
}

DSError TRKDoWriteRegisters(MessageBuffer* b)
{
    size_t sp10;
    u16 spC;
    u16 spA;
    u8 sp9;
    u8 sp8;
    DSError error;
    DSReplyError reply;

    if (b->fLength <= 6) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKSetBufferPosition(b, 0);

    error = TRKReadBuffer1_ui8(b, &sp8);

    if (error == kNoError) {
        error = TRKReadBuffer1_ui8(b, &sp9);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui16(b, &spA);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui16(b, &spC);
    }

    if (!TRKTargetStopped()) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyNotStopped);
    }

    if (spA > spC) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyInvalidRegisterRange);
    }

    switch (sp9) {
    case 0:
        error = TRKTargetAccessDefault((u32) spA, (u32) spC, b, &sp10, 0);
        break;
    case 1:
        error = TRKTargetAccessFP((u32) spA, (u32) spC, b, &sp10, 0);
        break;
    case 2:
        error = TRKTargetAccessExtended1((u32) spA, (u32) spC, b, &sp10, 0);
        break;
    case 3:
        error = TRKTargetAccessExtended2((u32) spA, (u32) spC, b, &sp10, 0);
        break;
    default:
        error = kUnsupportedError;
        break;
    }

    if (error == kNoError) {
        TRKMessageIntoReply(b, kDSReplyACK, kDSReplyNoError);
    }

    if (error != kNoError) {
        switch (error) {
        case kUnsupportedError:
            reply = kDSReplyUnsupportedOptionError;
            break;
        case kInvalidRegister:
            reply = kDSReplyInvalidRegisterRange;
            break;
        case kMessageBufferReadError:
            reply = kDSReplyPacketSizeError;
            break;
        case kCWDSException:
            reply = kDSReplyCWDSException;
            break;
        default:
            reply = kDSReplyCWDSError;
            break;
        }

        return TRKStandardACK(b, kDSReplyACK, reply);
    }

    return TRKSendACK(b);
}

DSError TRKDoFlushCache(MessageBuffer* b)
{
    u32 sp10;
    u32 spC;
    u8 sp9;
    u8 sp8;
    DSReplyError reply;
    DSError error;

    if (b->fLength != 0xA) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKSetBufferPosition(b, 0);
    error = TRKReadBuffer1_ui8(b, &sp8);

    if (error == kNoError) {
        error = TRKReadBuffer1_ui8(b, &sp9);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui32(b, &spC);
    }

    if (error == kNoError) {
        error = TRKReadBuffer1_ui32(b, &sp10);
    }

    if (!TRKTargetStopped()) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyNotStopped);
    }

    if (spC > sp10) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyInvalidMemoryRange);
    }

    if (error == kNoError) {
        error = TRKTargetFlushCache(sp9, spC, sp10);
    }

    if (error == kNoError) {
        TRKMessageIntoReply(b, kDSReplyACK, kDSReplyNoError);
    }

    if (error != kNoError) {
        switch (error) {
        case kUnsupportedError:
            reply = kDSReplyUnsupportedOptionError;
            break;
        default:
            reply = kDSReplyCWDSError;
            break;
        }

        return TRKStandardACK(b, kDSReplyACK, reply);
    }

    return TRKSendACK(b);
}

DSError TRKDoContinue(MessageBuffer* b)
{
    DSError result;

    if (!TRKTargetStopped()) {
        result = TRKStandardACK(b, kDSReplyACK, kDSReplyNotStopped);
    } else {
        result = TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);

        if (result == kNoError) {
            result = TRKTargetContinue();
        }
    }

    return result;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
DSError TRKDoStep(MessageBuffer* b)
{
    DSError error;
    size_t sp10;
    u32 spC;
    u8 spA;
    u8 sp9;
    u8 sp8;
    u32 pc;

    if (b->fLength < 3) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyPacketSizeError);
    }

    TRKSetBufferPosition(b, 0);

    error = TRKReadBuffer1_ui8(b, &sp8);

    if (error == kNoError) {
        error = TRKReadBuffer1_ui8(b, &sp9);
    }

    if (!TRKTargetStopped()) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyNotStopped);
    }

    switch (sp9) {
    case kDSStepIntoCount:
    case kDSStepOverCount:
        if (error == kNoError) {
            TRKReadBuffer1_ui8(b, &spA);
        }

        if (spA < 1) {
            return TRKStandardACK(b, kDSReplyACK, kDSReplyParameterError);
        }
        break;
    case kDSStepIntoRange:
    case kDSStepOverRange:
        if (b->fLength != 0xA) {
            return TRKStandardACK(b, kDSReplyACK, kDSReplyPacketSizeError);
        }

        if (error == kNoError) {
            error = TRKReadBuffer1_ui32(b, &spC);
        }

        if (error == kNoError) {
            TRKReadBuffer1_ui32(b, &sp10);
        }

        pc = TRKTargetGetPC();
        if (pc < spC || pc > sp10) {
            return TRKStandardACK(b, kDSReplyACK, kDSReplyParameterError);
        }
        break;
    default:
        return TRKStandardACK(b, kDSReplyACK, kDSReplyUnsupportedOptionError);
    }

    error = TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);

    if (error == kNoError) {
        switch (sp9) {
        case kDSStepIntoCount:
        case kDSStepOverCount:
            error = TRKTargetSingleStep(spA, sp9 == kDSStepOverCount);
            break;
        case kDSStepIntoRange:
        case kDSStepOverRange:
            error =
                TRKTargetStepOutOfRange(spC, sp10, sp9 == kDSStepOverRange);
            break;
        default:
            break;
        }
    }

    return error;
}
#pragma clang diagnostic pop

DSError TRKDoStop(MessageBuffer* b)
{
    if (TRKTargetStop() == kNoError) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);
    }

    return TRKStandardACK(b, kDSReplyACK, kDSReplyError);
}
