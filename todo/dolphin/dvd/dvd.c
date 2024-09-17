#include <__mem.h>
#include <string.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/dvd/dvderror.h>
#include <dolphin/dvd/dvdfs.h>
#include <dolphin/dvd/dvdlow.h>
#include <dolphin/dvd/dvdqueue.h>
#include <dolphin/dvd/fstload.h>
#include <dolphin/os.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSTime.h>

// Callback / state-change function declarations
static void cbForCancelAllSync(s32, DVDCommandBlock*);
static void cbForCancelStreamSync(s32, DVDCommandBlock*);
static void cbForCancelSync(s32, DVDCommandBlock*);
static void cbForStateBusy(u32 intType);
static void cbForStateCheckID1(u32 intType);
static void cbForStateCheckID2(u32);
static void cbForStateCheckID3(u32);
static void cbForStateCoverClosed(u32 intType);
static void cbForStateError(u32 intType);
static void cbForStateGettingError(u32 intType);
static void cbForStateGoToRetry(u32 intType);
static void cbForStateMotorStopped(u32 intType);
static void cbForStateReadingFST(u32 intType);
static void cbForUnrecoveredError(u32 intType);
static void cbForUnrecoveredErrorRetry(u32 intType);
static void stateBusy(DVDCommandBlock*);
static void stateCheckID2(DVDCommandBlock*);
static void stateCheckID3(DVDCommandBlock*);
static void stateCoverClosed(void);
static void stateCoverClosed_CMD(DVDCommandBlock*);
static void stateGettingError(void);
static void stateGoToRetry(void);
static void stateMotorStopped(void);
static void stateReady(void);
static void stateTimeout(void);

typedef struct {
    u8 x0[32];
    u32 magic;
    u8 pad[20];
    void* fst_start;
} OSBootInfo;

extern volatile struct _IO {
    u32 unk0;
    u32 unk4;
    u32 x8[6];
    u32 error;
} IO AT_ADDRESS(0xCC006000);

static DVDBuffer tmpBuffer;

/// @todo Unused @c .bss.
#ifndef BUGFIX
static u8 _[0x60];
#endif

DVDCommandBlock DummyCommandBlock;
OSAlarm ResetAlarm;

static DVDCommandBlock* executing;
static DVDDiskID* currID;
static OSBootInfo* bootInfo;
static volatile bool PauseFlag;
static volatile bool PausingFlag;
static bool AutoFinishing;
static volatile bool FatalErrorFlag;
static vu32 CurrCommand;
static vu32 Canceling;
static DVDCBCallback CancelCallback;
static vu32 ResumeFromHere;
static vu32 CancelLastError;
static vu32 LastError;
static vs32 NumInternalRetry;
static volatile bool ResetRequired;
static volatile bool CancelAllSyncComplete;
static bool FirstTimeInBootrom;
static bool DVDInitialized;
static void (*LastState)(DVDCommandBlock*);

static bool autoInvalidation = true;

extern OSThreadQueue __DVDThreadQueue;
DVDCommandBlock* __DVDPopWaitingQueue(void);

void DVDInit(void)
{
    if (!DVDInitialized) {
        OSInitAlarm();
        DVDInitialized = true;
        __DVDFSInit();
        __DVDClearWaitingQueue();
        __DVDInitWA();
        bootInfo = (void*) 0x80000000;
        currID = (void*) 0x80000000;
        __OSSetInterruptHandler(0x15,
                                (__OSInterruptHandler) __DVDInterruptHandler);
        __OSUnmaskInterrupts(0x400);
        OSInitThreadQueue(&__DVDThreadQueue);
        IO.unk0 = 0x2A;
        IO.unk4 = 0;
        if (bootInfo->magic == 0xE5207C22) {
            OSReport("app booted via JTAG\n");
            OSReport("load fst\n");
            __fstLoad();
        } else if (bootInfo->magic == 0xD15EA5E) {
            OSReport("app booted from bootrom\n");
        } else {
            FirstTimeInBootrom = true;
            OSReport("bootrom\n");
        }
    }
}

static void stateReadingFST(DVDCommandBlock* _)
{
    LastState = stateReadingFST;
    DVDLowRead(bootInfo->fst_start, OSRoundUp32B(tmpBuffer.FSTLength),
               tmpBuffer.FSTPosition, &cbForStateReadingFST);
}

static void cbForStateReadingFST(u32 intType)
{
    DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = 0;
        if (finished->callback) {
            finished->callback(0, finished);
        }
        stateReady();
    } else {
        stateGettingError();
    }
}

inline void stateError(u32 error)
{
    __DVDStoreErrorCode(error);
    DVDLowStopMotor(cbForStateError);
}

static void cbForStateError(u32 intType)
{
    DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    FatalErrorFlag = true;
    finished = executing;
    executing = &DummyCommandBlock;
    if (finished->callback) {
        finished->callback(-1, finished);
    }

    if (Canceling) {
        Canceling = false;
        if (CancelCallback) {
            (CancelCallback)(0, finished);
        }
    }

    stateReady();
}

static void stateTimeout(void)
{
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
}

static void stateGettingError(void)
{
    DVDLowRequestError(cbForStateGettingError);
}

u32 CategorizeError(u32 error)
{
    if (error == 0x20400) {
        LastError = error;
        return 1;
    }

    error &= 0xFFFFFF;

    if (error == 0x62800 || error == 0x23A00 || error == 0xB5A01) {
        return 0;
    }

    ++NumInternalRetry;
    if (NumInternalRetry == 2) {
        if (error == LastError) {
            LastError = error;
            return 1;
        } else {
            LastError = error;
            return 2;
        }
    } else {
        LastError = error;
        if (error == 0x31100 || executing->command == 5) {
            return 2;
        } else {
            return 3;
        }
    }
}

inline bool CheckCancel(u32 resume)
{
    DVDCommandBlock* finished;

    if (Canceling) {
        ResumeFromHere = resume;
        Canceling = false;

        finished = executing;
        executing = &DummyCommandBlock;

        finished->state = 10;
        if (finished->callback) {
            finished->callback(-3, finished);
        }
        if (CancelCallback) {
            CancelCallback(0, finished);
        }
        stateReady();
        return true;
    }
    return false;
}

static void cbForStateGettingError(u32 intType)
{
    u32 error;
    u32 status;
    u32 errorCategory;
    u32 resume;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 2) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    error = IO.error;
    status = error & 0xff000000;

    errorCategory = CategorizeError(error);

    if (errorCategory == 1) {
        executing->state = -1;
        stateError(error);
        return;
    }

    if ((errorCategory == 2) || (errorCategory == 3)) {
        resume = 0;
    } else {
        if (status == 0x01000000) {
            resume = 4;
        } else if (status == 0x02000000) {
            resume = 6;
        } else if (status == 0x03000000) {
            resume = 3;
        } else {
            resume = 5;
        }
    }

    if (CheckCancel(resume)) {
        return;
    }

    if (errorCategory == 2) {
        __DVDStoreErrorCode(error);
        stateGoToRetry();
        return;
    }

    if (errorCategory == 3) {
        if ((error & 0x00FFFFFF) == 0x00031100) {
            DVDLowSeek(executing->offset, cbForUnrecoveredError);
        } else {
            LastState(executing);
        }
        return;
    }

    if (status == 0x01000000) {
        executing->state = 5;
        stateMotorStopped();
    } else if (status == 0x02000000) {
        executing->state = 3;
        stateCoverClosed();
    } else if (status == 0x03000000) {
        executing->state = 4;
        stateMotorStopped();
    } else {
        executing->state = -1;
        stateError(0x1234567);
    }
}

static void cbForUnrecoveredError(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1) {
        stateGoToRetry();
        return;
    }

    DVDLowRequestError(cbForUnrecoveredErrorRetry);
}

static void cbForUnrecoveredErrorRetry(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }
    executing->state = -1;

    if (intType & 2) {
        __DVDStoreErrorCode(0x1234567);
        DVDLowStopMotor(cbForStateError);
        return;
    }

    __DVDStoreErrorCode(IO.error);
    DVDLowStopMotor(cbForStateError);
}

static void stateGoToRetry(void)
{
    DVDLowStopMotor(cbForStateGoToRetry);
}

static void cbForStateGoToRetry(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 2) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    NumInternalRetry = 0;

    if (CurrCommand == 4 || CurrCommand == 5 || CurrCommand == 13 ||
        CurrCommand == 15)
    {
        ResetRequired = true;
    }

    if (!CheckCancel(2)) {
        executing->state = 11;
        stateMotorStopped();
    }
}

static void stateCheckID(void)
{
    switch (CurrCommand) {
    case 3:
        if (memcmp(&tmpBuffer, executing->id, 0x1C) != 0) {
            DVDLowStopMotor(&cbForStateCheckID1);
            return;
        } else {
            memcpy(currID, &tmpBuffer, sizeof(tmpBuffer));
            executing->state = 1;
            DCInvalidateRange(&tmpBuffer, sizeof(tmpBuffer));
            LastState = stateCheckID2;
            stateCheckID2(executing);
        }
        break;
    default:
        if (memcmp(&tmpBuffer, currID, sizeof(tmpBuffer)) != 0) {
            DVDLowStopMotor(&cbForStateCheckID1);
        } else {
            LastState = stateCheckID3;
            stateCheckID3(executing);
        }
        break;
    }
}

static void stateCheckID3(DVDCommandBlock* _)
{
    DVDLowAudioBufferConfig(currID->streaming, 10, cbForStateCheckID3);
}

static void stateCheckID2(DVDCommandBlock* _)
{
    DVDLowRead(&tmpBuffer, sizeof(tmpBuffer), 0x420, cbForStateCheckID2);
}

static void cbForStateCheckID1(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 2) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    NumInternalRetry = 0;

    if (!CheckCancel(1)) {
        executing->state = 6;
        stateMotorStopped();
    }
}

static void cbForStateCheckID2(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        stateReadingFST(executing);
    } else {
        stateGettingError();
    }
}

static void cbForStateCheckID3(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        if (!CheckCancel(0)) {
            executing->state = 1;
            stateBusy(executing);
        }
    } else {
        stateGettingError();
    }
}

static void AlarmHandler(OSAlarm* unused0, OSContext* unused1)
{
    DVDReset();
    DCInvalidateRange(&tmpBuffer, 0x20);
    LastState = stateCoverClosed_CMD;
    stateCoverClosed_CMD(executing);
}

static void stateCoverClosed(void)
{
    DVDCommandBlock* finished;
    switch (CurrCommand) {
    case 4:
    case 5:
    case 13:
    case 15:
        __DVDClearWaitingQueue();
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            finished->callback(-4, finished);
        }
        stateReady();
        break;
    default:
        DVDReset();
        OSCreateAlarm(&ResetAlarm);
        OSSetAlarm(&ResetAlarm, OSMillisecondsToTicks(1150), AlarmHandler);
        break;
    }
}

static void stateCoverClosed_CMD(DVDCommandBlock* block)
{
    /// @todo Incorrect cast.
    DVDLowReadDiskID((DVDDiskID*) &tmpBuffer, cbForStateCoverClosed);
}

static void cbForStateCoverClosed(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        stateCheckID();
    } else {
        stateGettingError();
    }
}

static void stateMotorStopped(void)
{
    DVDLowWaitCoverClose(cbForStateMotorStopped);
}

static void cbForStateMotorStopped(u32 intType)
{
    IO.unk4 = 0;
    executing->state = 3;
    stateCoverClosed();
}

static void stateReady(void)
{
    DVDCommandBlock* finished;

    if (!__DVDCheckWaitingQueue()) {
        executing = (DVDCommandBlock*) NULL;
        return;
    }

    if (PauseFlag) {
        PausingFlag = true;
        executing = (DVDCommandBlock*) NULL;
        return;
    }

    executing = __DVDPopWaitingQueue();

    if (FatalErrorFlag) {
        executing->state = -1;
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            finished->callback(-1, finished);
        }
        stateReady();
        return;
    }

    CurrCommand = executing->command;

    if (ResumeFromHere) {
        switch (ResumeFromHere) {
        case 1:
            executing->state = 6;
            stateMotorStopped();
            break;
        case 2:
            executing->state = 11;
            stateMotorStopped();
            break;
        case 3:
            executing->state = 4;
            stateMotorStopped();
            break;
        case 7:
            executing->state = 7;
            stateMotorStopped();
            break;
        case 4:
            executing->state = 5;
            stateMotorStopped();
            break;
        case 6:
            executing->state = 3;
            stateCoverClosed();
            break;
        case 5:
            executing->state = -1;
            stateError(CancelLastError);
        }
        ResumeFromHere = 0;
    } else {
        executing->state = 1;
        stateBusy(executing);
    }
}

static void stateBusy(DVDCommandBlock* block)
{
    LastState = stateBusy;
    switch (block->command) {
    case 5:
        IO.unk4 = IO.unk4;
        block->currTransferSize = sizeof(DVDDiskID);
        DVDLowReadDiskID(block->addr, cbForStateBusy);
        break;
    case 1:
    case 4:
        IO.unk4 = IO.unk4;
        block->currTransferSize =
            MIN(block->length - block->transferredSize, 0x80000);
        DVDLowRead((void*) ((u8*) block->addr + block->transferredSize),
                   block->currTransferSize,
                   block->offset + block->transferredSize, cbForStateBusy);
        break;
    case 2:
        IO.unk4 = IO.unk4;
        DVDLowSeek(block->offset, cbForStateBusy);
        break;
    case 3:
        DVDLowStopMotor(cbForStateBusy);
        break;
    case 15:
        DVDLowStopMotor(cbForStateBusy);
        break;
    case 6:
        IO.unk4 = IO.unk4;
        if (AutoFinishing) {
            executing->currTransferSize = 0;
            DVDLowRequestAudioStatus(0, cbForStateBusy);
        } else {
            executing->currTransferSize = 1;
            DVDLowAudioStream(0, block->length, block->offset, cbForStateBusy);
        }
        break;
    case 7:
        IO.unk4 = IO.unk4;
        DVDLowAudioStream(0x10000, 0, 0, cbForStateBusy);
        break;
    case 8:
        IO.unk4 = IO.unk4;
        AutoFinishing = true;
        DVDLowAudioStream(0, 0, 0, cbForStateBusy);
        break;
    case 9:
        IO.unk4 = IO.unk4;
        DVDLowRequestAudioStatus(0, cbForStateBusy);
        break;
    case 10:
        IO.unk4 = IO.unk4;
        DVDLowRequestAudioStatus(0x10000, cbForStateBusy);
        break;
    case 11:
        IO.unk4 = IO.unk4;
        DVDLowRequestAudioStatus(0x20000, cbForStateBusy);
        break;
    case 12:
        IO.unk4 = IO.unk4;
        DVDLowRequestAudioStatus(0x30000, cbForStateBusy);
        break;
    case 13:
        IO.unk4 = IO.unk4;
        DVDLowAudioBufferConfig(block->offset, block->length, cbForStateBusy);
        break;
    case 14:
        IO.unk4 = IO.unk4;
        block->currTransferSize = sizeof(DVDDriveInfo);
        DVDLowInquiry(block->addr, cbForStateBusy);
        break;
    }
}

static void cbForStateBusy(u32 intType)
{
    DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if ((CurrCommand == 3) || (CurrCommand == 15)) {
        if (intType & 2) {
            executing->state = -1;
            stateError(0x1234567);
            return;
        }

        NumInternalRetry = 0;

        if (CurrCommand == 15) {
            ResetRequired = true;
        }

        if (CheckCancel(7)) {
            return;
        }

        executing->state = 7;
        stateMotorStopped();
        return;
    }

    if (CurrCommand == 1 || CurrCommand == 4 || CurrCommand == 5 ||
        CurrCommand == 14)
    {
        executing->transferredSize += executing->currTransferSize - IO.x8[4];
    }

    if (intType & 8) {
        Canceling = false;
        finished = executing;
        executing = &DummyCommandBlock;

        finished->state = 10;
        if (finished->callback) {
            finished->callback(-3, finished);
        }
        if (CancelCallback) {
            CancelCallback(0, finished);
        }
        stateReady();
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;

        if (CheckCancel(0)) {
            return;
        }

        if (CurrCommand == 1 || CurrCommand == 4 || CurrCommand == 5 ||
            CurrCommand == 14)
        {
            if (executing->transferredSize != executing->length) {
                stateBusy(executing);
                return;
            }

            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                finished->callback(finished->transferredSize, finished);
            }
            stateReady();
        } else if (CurrCommand == 9 || CurrCommand == 10 ||
                   CurrCommand == 11 || CurrCommand == 12)
        {
            s32 result;

            if ((CurrCommand == 11) || (CurrCommand == 10)) {
                result = IO.error << 2;
            } else {
                result = IO.error;
            }
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                finished->callback(result, finished);
            }
            stateReady();
        } else if (CurrCommand == 6) {
            if (executing->currTransferSize == 0) {
                if (IO.error & 1) {
                    finished = executing;
                    executing = &DummyCommandBlock;

                    finished->state = 9;
                    if (finished->callback) {
                        finished->callback(-2, finished);
                    }
                    stateReady();
                } else {
                    AutoFinishing = false;
                    executing->currTransferSize = 1;
                    DVDLowAudioStream(0, executing->length, executing->offset,
                                      cbForStateBusy);
                }
            } else {
                finished = executing;
                executing = &DummyCommandBlock;

                finished->state = 0;
                if (finished->callback) {
                    finished->callback(0, finished);
                }
                stateReady();
            }
        } else {
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                finished->callback(0, finished);
            }
            stateReady();
        }
    } else {
        if (CurrCommand == 14) {
            executing->state = -1;
            stateError(0x01234567);
            return;
        }

        if ((CurrCommand == 1 || CurrCommand == 4 || CurrCommand == 5 ||
             CurrCommand == 14) &&
            (executing->transferredSize == executing->length))
        {
            if (CheckCancel(0)) {
                return;
            }
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback) {
                finished->callback(finished->transferredSize, finished);
            }
            stateReady();
        } else {
            stateGettingError();
        }
    }
}

static inline bool issueCommand(s32 prio, DVDCommandBlock* block)
{
    bool level;
    bool result;

    if (autoInvalidation && (block->command == 1 || block->command == 4 ||
                             block->command == 5 || block->command == 14))
    {
        DCInvalidateRange(block->addr, block->length);
    }

    level = OSDisableInterrupts();

    block->state = 2;
    result = __DVDPushWaitingQueue(prio, block);

    if ((executing == (DVDCommandBlock*) NULL) && (PauseFlag == false)) {
        stateReady();
    }

    OSRestoreInterrupts(level);

    return result;
}

bool DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length,
                         s32 offset, DVDCBCallback callback, s32 prio)
{
    bool idle;
    block->command = 1;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(prio, block);
    return idle;
}

bool DVDSeekAbsAsyncPrio(DVDCommandBlock* block, u32 offset,
                         DVDCBCallback callback, s32 prio)
{
    bool idle;
    block->command = 2;
    block->offset = offset;
    block->callback = callback;

    idle = issueCommand(prio, block);
    return idle;
}

bool DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length,
                          s32 offset, DVDCBCallback callback)
{
    bool idle;
    block->command = 4;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    return idle;
}

bool DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID,
                   DVDCBCallback callback)
{
    bool idle;
    block->command = 5;
    block->addr = diskID;
    block->length = sizeof(DVDDiskID);
    ;
    block->offset = 0;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    return idle;
}

bool DVDPrepareStreamAbsAsync(DVDCommandBlock* block, u32 length, u32 offset,
                              DVDCBCallback callback)
{
    bool idle;
    block->command = 6;
    block->length = length;
    block->offset = offset;
    block->callback = callback;

    idle = issueCommand(1, block);
    return idle;
}

bool DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    bool idle;
    block->command = 7;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

int DVDCancelStream(DVDCommandBlock* block)
{
    bool enabled;
    int xferred;
    bool result = DVDCancelStreamAsync(block, cbForCancelStreamSync);

    if (!result) {
        return -1;
    }
    enabled = OSDisableInterrupts();
    while (true) {
        s32 state = ((volatile DVDCommandBlock*) block)->state;

        if (state == 0 || state == -1 || state == 10) {
            xferred = block->transferredSize;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return xferred;
}

static void cbForCancelStreamSync(s32 result, DVDCommandBlock* block)
{
    block->transferredSize = (u32) result;
    OSWakeupThread(&__DVDThreadQueue);
}

bool DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    bool idle;
    block->command = 8;
    block->callback = callback;

    idle = issueCommand(1, block);
    return idle;
}

bool DVDInquiryAsync(DVDCommandBlock* block, void* addr,
                     DVDCBCallback callback)
{
    bool idle;
    block->command = 14;
    block->addr = addr;
    block->length = 0x20;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    return idle;
}

void DVDReset(void)
{
    DVDLowReset();
    IO.unk0 = 0x2A;
    IO.unk4 = IO.unk4;
    ResetRequired = false;
    ResumeFromHere = 0;
}

s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block)
{
    bool enabled;
    s32 retVal;

    enabled = OSDisableInterrupts();

    if (block->state == 3) {
        retVal = 1;
    } else {
        retVal = block->state;
    }

    OSRestoreInterrupts(enabled);

    return retVal;
}

s32 DVDGetDriveStatus(void)
{
    bool enabled;
    s32 retVal;

    enabled = OSDisableInterrupts();

    if (FatalErrorFlag) {
        retVal = -1;
    } else if (PausingFlag) {
        retVal = 8;
    } else {
        if (executing == (DVDCommandBlock*) NULL) {
            retVal = 0;
        } else if (executing == &DummyCommandBlock) {
            retVal = 0;
        } else {
            retVal = DVDGetCommandBlockStatus(executing);
        }
    }

    OSRestoreInterrupts(enabled);

    return retVal;
}

bool DVDSetAutoInvalidation(bool autoInval)
{
    bool prev = autoInvalidation;
    autoInvalidation = autoInval;
    return prev;
}

inline void DVDPause(void)
{
    bool enabled = OSDisableInterrupts();
    PauseFlag = true;
    if (executing == (DVDCommandBlock*) NULL) {
        PausingFlag = true;
    }
    OSRestoreInterrupts(enabled);
}

inline void DVDResume(void)
{
    bool enabled = OSDisableInterrupts();
    PauseFlag = false;
    if (PausingFlag) {
        PausingFlag = false;
        stateReady();
    }
    OSRestoreInterrupts(enabled);
}

bool DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    bool enabled;
    DVDLowCallback old;

    enabled = OSDisableInterrupts();

    switch (block->state) {
    case -1:
    case 0:
    case 10:
        if (callback) {
            callback(0, block);
        }
        break;

    case 1:
        if (Canceling) {
            OSRestoreInterrupts(enabled);
            return false;
        }

        Canceling = true;
        CancelCallback = callback;
        if (block->command == 4 || block->command == 1) {
            DVDLowBreak();
        }
        break;

    case 2:
        __DVDDequeueWaitingQueue(block);
        block->state = 10;
        if (block->callback) {
            block->callback(-3, block);
        }
        if (callback) {
            callback(0, block);
        }
        break;

    case 3:
        switch (block->command) {
        case 5:
        case 4:
        case 13:
        case 15:
            if (callback) {
                callback(0, block);
            }
            break;

        default:
            if (Canceling) {
                OSRestoreInterrupts(enabled);
                return false;
            }
            Canceling = true;
            CancelCallback = callback;
            break;
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
        old = DVDLowClearCallback();
        if (old != cbForStateMotorStopped) {
            OSRestoreInterrupts(enabled);
            return false;
        }

        if (block->state == 4) {
            ResumeFromHere = 3;
        }
        if (block->state == 5) {
            ResumeFromHere = 4;
        }
        if (block->state == 6) {
            ResumeFromHere = 1;
        }
        if (block->state == 11) {
            ResumeFromHere = 2;
        }
        if (block->state == 7) {
            ResumeFromHere = 7;
        }

        block->state = 10;
        if (block->callback) {
            block->callback(-3, block);
        }
        if (callback) {
            callback(0, block);
        }
        stateReady();
        break;
    }

    OSRestoreInterrupts(enabled);
    return true;
}

s32 DVDCancel(DVDCommandBlock* block)
{
    s32 state;
    u32 command;
    bool enabled;

    if (DVDCancelAsync(block, cbForCancelSync) == false) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    for (;;) {
        state = ((volatile DVDCommandBlock*) block)->state;

        if (state == 0 || state == -1 || state == 10) {
            break;
        }

        if (state == 3) {
            command = ((volatile DVDCommandBlock*) block)->command;

            if (command == 4 || command == 5 || command == 13 || command == 15)
            {
                break;
            }
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

static void cbForCancelSync(s32 result, DVDCommandBlock* block)
{
    OSWakeupThread(&__DVDThreadQueue);
}

inline bool DVDCancelAllAsync(DVDCBCallback callback)
{
    bool enabled;
    DVDCommandBlock* p;
    bool retVal;

    enabled = OSDisableInterrupts();
    DVDPause();

    while ((p = __DVDPopWaitingQueue()) != 0) {
        DVDCancelAsync(p, NULL);
    }

    if (executing) {
        retVal = DVDCancelAsync(executing, callback);
    } else {
        retVal = true;
        if (callback) {
            callback(0, NULL);
        }
    }

    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

int DVDCancelAll(void)
{
    bool result;
    bool enabled;

    enabled = OSDisableInterrupts();
    CancelAllSyncComplete = false;

    result = DVDCancelAllAsync(cbForCancelAllSync);

    if (result == false) {
        OSRestoreInterrupts(enabled);
        return -1;
    }

    for (;;) {
        if (CancelAllSyncComplete) {
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

static void cbForCancelAllSync(s32 result, DVDCommandBlock* block)
{
    CancelAllSyncComplete = true;
    OSWakeupThread(&__DVDThreadQueue);
}

DVDDiskID* DVDGetCurrentDiskID(void)
{
    return (DVDDiskID*) OSPhysicalToCached(0);
}

bool DVDCheckDisk(void)
{
    bool enabled;
    s32 retVal;
    s32 state;
    u32 coverReg;

    enabled = OSDisableInterrupts();

    if (FatalErrorFlag) {
        state = -1;
    } else if (PausingFlag) {
        state = 8;
    } else {
        if (executing == (DVDCommandBlock*) NULL) {
            state = 0;
        } else if (executing == &DummyCommandBlock) {
            state = 0;
        } else {
            state = executing->state;
        }
    }

    switch (state) {
    case 1:
    case 9:
    case 10:
    case 2:
        retVal = true;
        break;

    case -1:
    case 11:
    case 7:
    case 3:
    case 4:
    case 5:
    case 6:
        retVal = false;
        break;

    case 0:
    case 8:
        coverReg = IO.unk4;
        if (((coverReg >> 2) & 1) || (coverReg & 1)) {
            retVal = false;
        } else {
            retVal = true;
        }
    }

    OSRestoreInterrupts(enabled);

    return retVal;
}

void __DVDPrepareResetAsync(DVDCBCallback callback)
{
    bool enabled = OSDisableInterrupts();

    __DVDClearWaitingQueue();

    if (Canceling) {
        CancelCallback = callback;
    } else {
        if (executing) {
            executing->callback = NULL;
        }
        DVDCancelAllAsync(callback);
    }

    OSRestoreInterrupts(enabled);
}
