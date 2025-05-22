#ifndef _METROTRK_MSGCMD_H
#define _METROTRK_MSGCMD_H

#include <platform.h>

#define DSFetch_s8(_p_) (*((s8*) _p_))
#define DSFetch_s16(_p_) (*((s16*) _p_))
#define DSFetch_s32(_p_) (*((s32*) _p_))
#define DSFetch_s64(_p_) (*((s64*) _p_))

#define DSFetch_u8(_p_) (*((u8*) _p_))
#define DSFetch_u16(_p_) (*((u16*) _p_))
#define DSFetch_u32(_p_) (*((u32*) _p_))
#define DSFetch_u64(_p_) (*((u64*) _p_))

#define DS_PROTOCOL_MAJOR_VERSION_1 1
#define DS_PROTOCOL_MINOR_VERSION_10 10
#define DS_PROTOCOL_MAJOR_VERSION DS_PROTOCOL_MAJOR_VERSION_1
#define DS_PROTOCOL_MINOR_VERSION DS_PROTOCOL_MINOR_VERSION_10
#define DS_KERNEL_MAJOR_VERSION 0
#define DS_KERNEL_MINOR_VERSION 4

typedef enum MessageCommandID {
    kDSPing = 0x00,
    kDSConnect = 0x01,
    kDSDisconnect = 0x02,
    kDSReset = 0x03,
    kDSVersions = 0x04,
    kDSSupportMask = 0x05,
    kDSOverride = 0x07,
    kDSReadMemory = 0x10,
    kDSWriteMemory = 0x11,
    kDSReadRegisters = 0x12,
    kDSWriteRegisters = 0x13,
    kDSSetOption = 0x17,
    kDSContinue = 0x18,
    kDSStep = 0x19,
    kDSStop = 0x1A,
    kDSReplyACK = 0x80,
    kDSReplyNAK = 0xFF,
    kDSNotifyStopped = 0x90,
    kDSNotifyException = 0x91,
    kDSWriteFile = 0xD0,
    kDSReadFile = 0xD1,
    kDSOpenFile = 0xD2,
    kDSCloseFile = 0xD3,
    kDSPositionFile = 0xD4
} MessageCommandID;

#define DS_MIN_MSG_LENGTH 1
#define DS_MIN_REPLY_LENGTH 2

#define DS_MIN_MSG_VERSIONS_LENGTH DS_MIN_MSG_LENGTH
#define DS_MIN_REPLY_VERSIONS_LENGTH (DS_MIN_REPLY_LENGTH + 4)

/*
** CPU Major types.
*/

#define DS_CPU_MAJOR_PPC 0x00
#define DS_CPU_MAJOR_MIPS 0x01
#define DS_CPU_MAJOR_NEC_V8XX 0x02
#define DS_CPU_MAJOR_MOT_DSP 0x03
#define DS_CPU_MAJOR_ARM 0x04
#define DS_CPU_MAJOR_X86 0x05
#define DS_CPU_MAJOR_MCORE 0x06
#define DS_CPU_MAJOR_M68K 0x07 /* includes ColdFire */
#define DS_CPU_MAJOR_SUPERH 0x08

/*
** MIPS CPU minor types.
*/

#define DS_CPU_MIPS_R3000 0x00
#define DS_CPU_MIPS_R3081E 0x01

#define DS_CPU_MIPS_VR4100 0x20
#define DS_CPU_MIPS_VR4300 0x21
#define DS_CPU_MIPS_VR4500 0x22
#define DS_CPU_MIPS_VR4111 0x23
#define DS_CPU_MIPS_TR4101 0x24

#define DS_CPU_MIPS_VR5000 0x40

/*
** PowerPC CPU minor types.
*/

#define DS_CPU_PPC_403 0x00

#define DS_CPU_PPC_5XX 0x20 /* used when not precisely known */
#define DS_CPU_PPC_505 0x21
#define DS_CPU_PPC_509 0x22
#define DS_CPU_PPC_50X 0x27 /* used when not precisely known */
#define DS_CPU_PPC_555 0x28

#define DS_CPU_PPC_603E 0x40

#define DS_CPU_PPC_7XX 0x50 /* used when not precisely known */
#define DS_CPU_PPC_740 0x51
#define DS_CPU_PPC_750 0x52
#define DS_CPU_PPC_7400 0x53
#define DS_CPU_PPC_7410 0x54

#define DS_CPU_PPC_8260 0x61

#define DS_CPU_PPC_8XX 0x80 /* used when not precisely known */
#define DS_CPU_PPC_821 0x81
#define DS_CPU_PPC_823 0x82
#define DS_CPU_PPC_860 0x83

/*
** NEC V8xx CPU minor types.
*/

#define DS_CPU_NEC_V8XX_V810 0x00
#define DS_CPU_NEC_V8XX_V821 0x01

#define DS_CPU_NEC_V8XX_V830 0x10
#define DS_CPU_NEC_V8XX_V831 0x11
#define DS_CPU_NEC_V8XX_V832 0x12

#define DS_CPU_NEC_V8XX_V850 0x20
#define DS_CPU_NEC_V8XX_V853 0x21
#define DS_CPU_NEC_V8XX_V850E 0x22
#define DS_CPU_NEC_V8XX_V850_SA1 0x23

/*
** M68K/Coldfire CPU minor types.
*/

#define DS_CPU_M68K_68000 0x00
#define DS_CPU_M68K_68020 0x02
#define DS_CPU_M68K_68030 0x04
#define DS_CPU_M68K_68040 0x06
#define DS_CPU_M68K_68060 0x08

#define DS_CPU_M68K_68302 0x20
#define DS_CPU_M68K_68306 0x22
#define DS_CPU_M68K_68307 0x24
#define DS_CPU_M68K_68328 0x26
#define DS_CPU_M68K_68EZ328 0x28
#define DS_CPU_M68K_68VZ328 0x29
#define DS_CPU_M68K_68340 0x2A
#define DS_CPU_M68K_68360 0x2C

#define DS_CPU_M68K_CF5102 0x80
#define DS_CPU_M68K_CF5202 0x82
#define DS_CPU_M68K_CF5204 0x84
#define DS_CPU_M68K_CF5206 0x86
#define DS_CPU_M68K_CF5206E 0x88
#define DS_CPU_M68K_CF5307 0x8A

/*
** MCore CPU minor types.
*/

#define DS_CPU_MCORE_200 0x00
#define DS_CPU_MCORE_340 0x20

typedef u8 DSSupportMask[32]; /* 256 bits total */

#define DS_MIN_MSG_SUPPORTMASK_LENGTH DS_MIN_MSG_LENGTH
#define DS_MIN_REPLY_SUPPORTMASK_LENGTH                                       \
    (DS_MIN_REPLY_LENGTH + sizeof(DSSupportMask) + 1)

#if DS_PROTOCOL == DS_PROTOCOL_RTOS
#define DS_MIN_MSG_READMEMORY_LENGTH (DS_MIN_MSG_LENGTH + 15)
#else
#define DS_MIN_MSG_READMEMORY_LENGTH (DS_MIN_MSG_LENGTH + 7)
#endif
#define DS_MIN_REPLY_READMEMORY_LENGTH (DS_MIN_REPLY_LENGTH + 2)

#if DS_PROTOCOL == DS_PROTOCOL_RTOS
#define DS_MIN_MSG_WRITEMEMORY_LENGTH (DS_MIN_MSG_LENGTH + 15)
#else
#define DS_MIN_MSG_WRITEMEMORY_LENGTH (DS_MIN_MSG_LENGTH + 7)
#endif
#define DS_MIN_REPLY_WRITEMEMORY_LENGTH (DS_MIN_REPLY_LENGTH + 2)

// Memory commands options
#define DS_MSG_MEMORY_SEGMENTED 0x01 /* non-flat addr space */
#define DS_MSG_MEMORY_EXTENDED 0x02  /* > 32-bit data addr */
#define DS_MSG_MEMORY_PROTECTED 0x04 /* non-user memory */
#define DS_MSG_MEMORY_USERVIEW 0x08  /* breakpoints are invisible */

#define DS_MSG_MEMORY_SPACE_PROGRAM 0x00
#define DS_MSG_MEMORY_SPACE_DATA 0x40
#define DS_MSG_MEMORY_SPACE_IO 0x80

#define TRK_MSG_HEADER_LENGTH DS_MSG_MEMORY_SPACE_DATA
#define TRK_MSG_REPLY_HEADER_LENGTH (TRK_MSG_HEADER_LENGTH + DS_MIN_MSG_LENGTH)

// Others

#define DS_MSG_MEMORY_SPACE_MASK 0xC0

#define DS_MAXREADWRITELENGTH 0x0800 /* 2K data portion */
#define DS_MAXMESSAGESIZE (DS_MAXREADWRITELENGTH + 0x80)
/* max size of all message including cmd hdr */
#define MAXMESSAGESIZE DS_MAXMESSAGESIZE

#define DS_MIN_MSG_FLUSHCACHE_LENGTH (DS_MIN_MSG_LENGTH + 9)
#define DS_MIN_REPLY_FLUSHCACHE_LENGTH (DS_MIN_REPLY_LENGTH)

#if DS_PROTOCOL == DS_PROTOCOL_RTOS
#define DS_MIN_MSG_READREGISTERS_LENGTH (DS_MIN_MSG_LENGTH + 13)
#else
#define DS_MIN_MSG_READREGISTERS_LENGTH (DS_MIN_MSG_LENGTH + 5)
#endif
#define DS_MIN_REPLY_READREGISTERS_LENGTH DS_MIN_REPLY_LENGTH

#if DS_PROTOCOL == DS_PROTOCOL_RTOS
#define DS_MIN_MSG_WRITEREGISTERS_LENGTH (DS_MIN_MSG_LENGTH + 13)
#else
#define DS_MIN_MSG_WRITEREGISTERS_LENGTH (DS_MIN_MSG_LENGTH + 5)
#endif
#define DS_MIN_REPLY_WRITEREGISTERS_LENGTH DS_MIN_REPLY_LENGTH

// Register commands options
typedef enum {
    kDSRegistersDefault = 0x0,   /* Default register block */
    kDSRegistersFP = 0x1,        /* floating point registers */
    kDSRegistersExtended1 = 0x2, /* Extended register set 1 */
    kDSRegistersExtended2 = 0x3  /* Extended register set 2 */
} DSMessageRegisterOptions;

#if DS_PROTOCOL == DS_PROTOCOL_RTOS
#define DS_MIN_MSG_STEP_COUNT_LENGTH (DS_MIN_MSG_LENGTH + 10)
#define DS_MIN_MSG_STEP_RANGE_LENGTH (DS_MIN_MSG_LENGTH + 17)
#else
#define DS_MIN_MSG_STEP_COUNT_LENGTH (DS_MIN_MSG_LENGTH + 2)
#define DS_MIN_MSG_STEP_RANGE_LENGTH (DS_MIN_MSG_LENGTH + 9)
#endif
#define DS_MIN_MSG_STEP_LENGTH (DS_MIN_MSG_STEP_COUNT_LENGTH)
#define DS_MIN_REPLY_STEP_LENGTH DS_MIN_REPLY_LENGTH

// Step command options
typedef enum {
    kDSStepIntoCount = 0x00, /* Exec count instructions & stop */
    kDSStepIntoRange = 0x01, /* Exec until PC is out of specified range */
    kDSStepOverCount = 0x10, /* Step over 1*count instructions & stop */
    kDSStepOverRange = 0x11  /* Step over until PC is out of specified range */
} DSMessageStepOptions;

/*
** These are the predefined file handles.  Additional files may
** be opened via the kDSOpenFile command.  New file handles
** returned by that command may be used in addition to the
** ones defined here.
*/

typedef enum DSFileHandle {
    kDSStdin = 0x00,
    kDSStdout = 0x01,
    kDSStderr = 0x02
} DSFileHandle;

/*
** The result of an I/O command can be any one of the following.
*/

typedef enum DSIOResult {
    kDSIONoError = 0x00,
    kDSIOError = 0x01,
    kDSIOEOF = 0x02
} DSIOResult;

// Reply errors
typedef enum DSReplyError {
    kDSReplyNoError = 0x00,
    kDSReplyError = 0x01,
    kDSReplyPacketSizeError = 0x02,
    kDSReplyCWDSError = 0x03,
    kDSReplyEscapeError = 0x04,
    kDSReplyBadFCS = 0x05,
    kDSReplyOverflow = 0x06,
    kDSReplySequenceMissing = 0x07,
    kDSReplyUnsupportedCommandError = 0x10,
    kDSReplyParameterError = 0x11,
    kDSReplyUnsupportedOptionError = 0x12,
    kDSReplyInvalidMemoryRange = 0x13,
    kDSReplyInvalidRegisterRange = 0x14,
    kDSReplyCWDSException = 0x15,
    kDSReplyNotStopped = 0x16,
    kDSReplyBreakpointsFull = 0x17,
    kDSReplyBreakpointConflict = 0x18,
    kDSReplyOsError = 0x20,
    kDSReplyInvalidProcessId = 0x21,
    kDSReplyInvalidThreadId = 0x22,
    kDSDebugSecurityError = 0x23
} DSReplyError;

#endif
