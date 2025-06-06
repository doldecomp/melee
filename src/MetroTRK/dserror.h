#ifndef _METROTRK_DSERROR_H
#define _METROTRK_DSERROR_H

typedef enum DSError {
    kUARTError = -0x0001,
    kNoError = 0x0000,
    kStepError = 0x0001,
    kParameterError = 0x0002,
    kEventQueueFull = 0x0100,
    kNoMessageBufferAvailable = 0x0300,
    kMessageBufferOverflow = 0x0301,
    kMessageBufferReadError = 0x0302,
    kDispatchError = 0x0500,
    kInvalidMemory = 0x0700,
    kInvalidRegister = 0x0701,
    kCWDSException = 0x0702,
    kUnsupportedError = 0x0703,
    kInvalidProcessId = 0x0704,
    kInvalidThreadId = 0x0705,
    kOsError = 0x0706,
    kWaitACKError = 0x0800
} DSError;

#endif
