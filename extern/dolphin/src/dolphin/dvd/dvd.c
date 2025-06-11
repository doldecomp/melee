#include "__dvd.h"

#include "os/__os.h"

#include <dolphin.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>

extern OSThreadQueue __DVDThreadQueue;

static unsigned char* tmpBuffer[32] ATTRIBUTE_ALIGN(32);
static struct DVDCommandBlock DummyCommandBlock;
static OSAlarm alarm;

static int autoInvalidation = 1;

static struct DVDCommandBlock* executing;
static void* tmp;
static struct DVDDiskID* currID;
static struct OSBootInfo_s* bootInfo;
static volatile int PauseFlag;
static volatile int PausingFlag;
static int AutoFinishing;
static BOOL FatalErrorFlag;
static volatile unsigned long CurrCommand;
static volatile unsigned long Canceling;
static struct DVDCommandBlock* CancelingCommandBlock;
static void (*CancelCallback)(long, struct DVDCommandBlock*);
static volatile unsigned long ResumeFromHere;
static volatile unsigned long CancelLastError;
static unsigned long LastError;
static volatile long NumInternalRetry;
static int ResetRequired;
static int CancelAllSyncComplete;
static volatile unsigned long ResetCount;
static int FirstTimeInBootrom;
static long ResultForSyncCommand;
static int DVDInitialized;
void (*LastState)(struct DVDCommandBlock*);

static void stateReadingFST();
static void cbForStateReadingFST(unsigned long intType);
static void stateError();
static void stateGettingError();
static unsigned long CategorizeError(unsigned long error);
static int ResetWorkAround(unsigned long error);
static void cbForStateGettingError(unsigned long intType);
static void stateGoToRetry();
static void cbForStateGoToRetry(unsigned long intType);
static void stateCheckID();
static void stateCheckID3();
static void stateCheckID2();
static void cbForStateCheckID1(unsigned long intType);
static void cbForStateCheckID2(unsigned long intType);
static void cbForStateCheckID3(unsigned long intType);
static void stateCoverClosed();
static void stateCoverClosed_CMD();
static void cbForStateCoverClosed(unsigned long intType);
static void stateMotorStopped();
static void cbForStateMotorStopped(unsigned long intType);
static void stateReady();
static void stateBusy(struct DVDCommandBlock* block);
static void cbForStateBusy(unsigned long intType);
static int issueCommand(long prio, struct DVDCommandBlock* block);
static void cbForCancelStreamSync(long result, struct DVDCommandBlock* block);
static void cbForStopStreamAtEndSync(long result,
                                     struct DVDCommandBlock* block);
static void cbForGetStreamErrorStatusSync(long result,
                                          struct DVDCommandBlock* block);
static void cbForGetStreamPlayAddrSync(long result,
                                       struct DVDCommandBlock* block);
static void cbForGetStreamStartAddrSync(long result,
                                        struct DVDCommandBlock* block);
static void cbForGetStreamLengthSync(long result,
                                     struct DVDCommandBlock* block);
static void cbForChangeDiskSync();
static void cbForInquirySync(long result, struct DVDCommandBlock* block);
static void cbForCancelSync();
static void cbForCancelAllSync();

void DVDInit()
{
    if (DVDInitialized == 0) {
        OSInitAlarm();
        DVDInitialized = 1;
        __DVDFSInit();
        __DVDClearWaitingQueue();
        __DVDInitWA();
        bootInfo = (void*) OSPhysicalToCached(0);
        currID = &bootInfo->DVDDiskID;
        __OSSetInterruptHandler(0x15, __DVDInterruptHandler);
        __OSUnmaskInterrupts(0x400U);
        OSInitThreadQueue(&__DVDThreadQueue);
        __DIRegs[0] = 0x2A;
        __DIRegs[1] = 0;
        if (bootInfo->magic == 0xE5207C22) {
            OSReport("app booted via JTAG\n");
            OSReport("load fst\n");
            __fstLoad();
            return;
        }
        if (bootInfo->magic == 0x0D15EA5E) {
            OSReport("app booted from bootrom\n");
            return;
        }
        FirstTimeInBootrom = 1;
        OSReport("bootrom\n");
    }
}

static void stateReadingFST()
{
    LastState = stateReadingFST;
    ASSERTLINE(0x219, ((u32) (bootInfo->FSTLocation) & (32 - 1)) == 0);
    DVDLowRead(bootInfo->FSTLocation, (u32) (tmpBuffer[2] + 0x1F) & 0xFFFFFFE0,
               (u32) tmpBuffer[1], cbForStateReadingFST);
}

static void cbForStateReadingFST(unsigned long intType)
{
    struct DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }

    ASSERTLINE(0x229, (intType & DVD_INTTYPE_CVR) == 0);
    if (intType & 1) {
        ASSERTLINE(0x22E, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = DVD_STATE_END;
        if (finished->callback) {
            finished->callback(0, finished);
        }
        stateReady();
        return;
    }
    ASSERTLINE(0x246, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

static void stateError(int code)
{
    __DVDStoreErrorCode(code);
    DVDLowStopMotor(cbForStateError);
}

static void cbForStateError(unsigned long intType)
{
    DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }

    finished = executing;
    FatalErrorFlag = TRUE;
    executing = &DummyCommandBlock;

    if (finished->callback != NULL) {
        finished->callback(-1, finished);
    }

    if (Canceling) {
        Canceling = FALSE;
        if (CancelCallback != NULL) {
            CancelCallback(0, finished);
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

static void stateGettingError()
{
    DVDLowRequestError(cbForStateGettingError);
}

static unsigned long CategorizeError(unsigned long error)
{
    if (error == 0x20400) {
        LastError = error;
        return 1;
    }
    error &= 0x00FFFFFF;
    if ((error == 0x62800) || (error == 0x23A00) || (error == 0xB5A01)) {
        return 0;
    }
    NumInternalRetry += 1;
    if (NumInternalRetry == 2) {
        if (error == LastError) {
            LastError = error;
            return 1;
        }
        LastError = error;
        return 2;
    }

    LastError = error;

    if (error == 0x31100 || executing->command == 5) {
        return 2;
    }
    return 3;
}

static int ResetWorkAround(unsigned long error)
{
    if ((LastState == stateCoverClosed_CMD ||
         (CurrCommand == DVD_COMMAND_READID)))
    {
        u32 status = error & 0xFF000000;
        if (status == 0x03000000 && ResetCount != 1) {
            if (ResetCount != 0) {
                ASSERTLINE(0x2F1, FALSE);
            }
            ResetCount += 1;
            return 1;
        }
    }
    ResetCount = 0;
    return 0;
}

static inline BOOL cancel_inline(int resume)
{
    if (Canceling) {
        DVDCommandBlock* finished = executing;
        ResumeFromHere = resume;
        Canceling = 0;
        executing = &DummyCommandBlock;
        finished->state = DVD_STATE_CANCELED;
        if (finished->callback) {
            finished->callback(-3, finished);
        }
        if (CancelCallback) {
            CancelCallback(0, finished);
        }
        stateReady();
        return TRUE;
    }
    return FALSE;
}

static void cbForStateGettingError(unsigned long intType)
{
    unsigned long error;
    u32 error_hi;
    int resume_from;
    u32 errorCategory;

    if (intType == 0x10) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }

    if (intType & DVD_INTTYPE_DE) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateError(0x1234567);
        return;
    }

    ASSERTLINE(0x30F, intType == DVD_INTTYPE_TC);
    error = __DIRegs[8];
    error_hi = error & 0xFF000000;

    errorCategory = CategorizeError(error);

    if (errorCategory == 1) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateError(error);
        return;
    }

    if (errorCategory - 2 <= 1) {
        resume_from = 0;
    } else if (error_hi == 0x1000000) {
        resume_from = 4;
    } else if (error_hi == 0x2000000) {
        resume_from = 6;
    } else if (error_hi == 0x3000000) {
        resume_from = 3;
    } else {
        resume_from = 5;
    }

    if (cancel_inline(resume_from)) {
        return;
    }

    if (errorCategory == 2) {
        __DVDStoreErrorCode(error);
        stateGoToRetry();
        return;
    } else if (errorCategory == 3) {
        if ((error & 0xFFFFFF) == 0x31100) {
            DVDLowSeek(executing->offset, cbForUnrecoveredError);
        } else {
            LastState(executing);
        }
        return;
    } else {
        if (error_hi == 0x1000000) {
            executing->state = DVD_STATE_COVER_OPEN;
            stateMotorStopped();
            return;
        } else if (error_hi == 0x2000000) {
            executing->state = DVD_STATE_COVER_CLOSED;
            stateCoverClosed();
            return;
        } else if (error_hi == 0x3000000) {
            executing->state = DVD_STATE_NO_DISK;
            stateMotorStopped();
            return;
        }
        executing->state = DVD_STATE_FATAL_ERROR;
        stateError(0x1234567);
        return;
    }
}

static void cbForUnrecoveredError(unsigned long intType)
{
    if (intType == 0x10) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }
    if (intType & 1) {
        stateGoToRetry();
        return;
    }
    DVDLowRequestError(cbForUnrecoveredErrorRetry);
}

static void cbForUnrecoveredErrorRetry(unsigned long intType)
{
    if (intType == 0x10) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }
    executing->state = DVD_STATE_FATAL_ERROR;
    if (intType & 2) {
        stateError(0x1234567);
        return;
    }
    stateError(__DIRegs[8]);
}

static void stateGoToRetry()
{
    DVDLowStopMotor(cbForStateGoToRetry);
}

static void cbForStateGoToRetry(unsigned long intType)
{
    struct DVDCommandBlock* finished;

    if (intType == 0x10) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    } else if (intType & 2) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateError(0x1234567);
        return;
    }
    ASSERTLINE(0x3D9, intType == DVD_INTTYPE_TC);
    NumInternalRetry = 0;
    if ((CurrCommand == DVD_COMMAND_BSREAD) ||
        (CurrCommand == DVD_COMMAND_READID) ||
        (CurrCommand == DVD_COMMAND_AUDIO_BUFFER_CONFIG) ||
        (CurrCommand == DVD_COMMAND_BS_CHANGE_DISK))
    {
        ResetRequired = 1;
    }

    if (!cancel_inline(2)) {
        executing->state = DVD_STATE_RETRY;
        stateMotorStopped();
    }
}

static void stateCheckID()
{
    switch (CurrCommand) {
    case DVD_COMMAND_CHANGE_DISK:
        if (memcmp(&tmpBuffer, executing->id, 0x1C)) {
            DVDLowStopMotor(cbForStateCheckID1);
            return;
        }
        memcpy(currID, &tmpBuffer, 0x20);
        executing->state = DVD_STATE_BUSY;
        DCInvalidateRange(&tmpBuffer, 0x20);
        LastState = stateCheckID2;
        stateCheckID2(executing);
        break;
    default:
        if (memcmp(&tmpBuffer, currID, 0x20)) {
            DVDLowStopMotor(cbForStateCheckID1);
            return;
        }
        LastState = stateCheckID3;
        stateCheckID3(executing);
        return;
    }
}

static void stateCheckID3()
{
    DVDLowAudioBufferConfig(currID->streaming, 0xAU, cbForStateCheckID3);
}

static void stateCheckID2()
{
    DVDLowRead(&tmpBuffer, 0x20U, 0x420, cbForStateCheckID2);
}

static void cbForStateCheckID1(unsigned long intType)
{
    if (intType == 0x10) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }
    if (intType & DVD_INTTYPE_DE) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateError(0x1234567);
        return;
    }
    ASSERTLINE(0x478, intType == DVD_INTTYPE_TC);

    NumInternalRetry = 0;

    if (!cancel_inline(1)) {
        executing->state = DVD_STATE_WRONG_DISK;
        stateMotorStopped();
    }
}

static void cbForStateCheckID2(unsigned long intType)
{
    ASSERTLINE(0x494, (intType & DVD_INTTYPE_CVR) == 0);

    if (intType == 0x10) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }

    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(0x499, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        stateReadingFST();
        return;
    }
    ASSERTLINE(0x4AA, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

static void cbForStateCheckID3(unsigned long intType)
{
    ASSERTLINE(0x4B4, (intType & DVD_INTTYPE_CVR) == 0);

    if (intType == 0x10) {
        executing->state = DVD_STATE_FATAL_ERROR;
        stateTimeout();
        return;
    }

    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(0x4B9, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        if (!cancel_inline(0)) {
            executing->state = DVD_STATE_BUSY;
            stateBusy(executing);
        }
        return;
    }
    ASSERTLINE(0x4CD, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

static void AlarmHandler(OSAlarm*, OSContext*)
{
    DVDReset();
    DCInvalidateRange(tmpBuffer, 0x20);
    LastState = stateCoverClosed_CMD;
    stateCoverClosed_CMD(executing);
}

static void stateCoverClosed()
{
    struct DVDCommandBlock* finished;

    switch (CurrCommand) {
    case DVD_COMMAND_BSREAD:
    case DVD_COMMAND_READID:
    case DVD_COMMAND_AUDIO_BUFFER_CONFIG:
    case DVD_COMMAND_BS_CHANGE_DISK:
        __DVDClearWaitingQueue();
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            finished->callback(-4, finished);
        }
        stateReady();
        return;
    }
    DVDReset();
    OSCreateAlarm(&alarm);
    OSSetAlarm(&alarm, OS_MSEC_TO_TICKS(1150), AlarmHandler);
    return;
}

static void stateCoverClosed_CMD()
{
    DVDLowReadDiskID((void*) &tmpBuffer, cbForStateCoverClosed);
}

static void cbForStateCoverClosed(unsigned long intType)
{
    ASSERTLINE(0x510, (intType & DVD_INTTYPE_CVR) == 0);
    if (intType == 0x10) {
        executing->state = DVD_RESULT_FATAL_ERROR;
        stateTimeout();
        return;
    }
    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(0x515, (intType & DVD_INTTYPE_DE) == 0);
        ASSERTLINE(0x519, (CurrCommand == DVD_COMMAND_READ) ||
                              (CurrCommand == DVD_COMMAND_SEEK) ||
                              (CurrCommand == DVD_COMMAND_CHANGE_DISK));
        NumInternalRetry = 0;
        stateCheckID();
        return;
    }
    ASSERTLINE(0x523, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

static void stateMotorStopped()
{
    DVDLowWaitCoverClose(cbForStateMotorStopped);
}

static void cbForStateMotorStopped(unsigned long intType)
{
    ASSERTLINE(0x540, intType == DVD_INTTYPE_CVR);
    __DIRegs[1] = 0;
    executing->state = DVD_STATE_COVER_CLOSED;
    stateCoverClosed();
}

static void stateReady()
{
    if (__DVDCheckWaitingQueue() == 0) {
        executing = NULL;
        return;
    }
    if (PauseFlag != 0) {
        PausingFlag = 1;
        executing = NULL;
        return;
    }
    executing = __DVDPopWaitingQueue();
    if (FatalErrorFlag) {
        DVDCommandBlock* finished;
        executing->state = DVD_RESULT_FATAL_ERROR;
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback != NULL) {
            finished->callback(-1, finished);
        }
        stateReady();
        return;
    }

    CurrCommand = executing->command;
    if (ResumeFromHere != 0) {
        switch (ResumeFromHere) {
        case 1:
            executing->state = DVD_STATE_WRONG_DISK;
            stateMotorStopped();
            break;
        case 2:
            executing->state = DVD_STATE_RETRY;
            stateMotorStopped();
            break;
        case 3:
            executing->state = DVD_STATE_NO_DISK;
            stateMotorStopped();
            break;
        case 7:
            executing->state = DVD_STATE_MOTOR_STOPPED;
            stateMotorStopped();
            break;
        case 4:
            executing->state = DVD_STATE_COVER_OPEN;
            stateMotorStopped();
            break;
        case 6:
            executing->state = DVD_STATE_COVER_CLOSED;
            stateCoverClosed();
            break;
        case 5:
            executing->state = DVD_STATE_FATAL_ERROR;
            stateError(CancelLastError);
            break;
        }
        ResumeFromHere = 0;
        return;
    }
    executing->state = DVD_STATE_BUSY;
    stateBusy(executing);
}

static void stateBusy(struct DVDCommandBlock* block)
{
    LastState = stateBusy;
    switch (block->command) {
    case DVD_COMMAND_READID:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = 0x20;
        DVDLowReadDiskID(block->addr, cbForStateBusy);
        return;
    case DVD_COMMAND_READ:
    case DVD_COMMAND_BSREAD:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize =
            (block->length - block->transferredSize > 0x80000)
                ? 0x80000
                : (block->length - block->transferredSize);
        DVDLowRead((char*) block->addr + block->transferredSize,
                   block->currTransferSize,
                   block->offset + block->transferredSize, cbForStateBusy);
        return;
    case DVD_COMMAND_SEEK:
        __DIRegs[1] = __DIRegs[1];
        DVDLowSeek(block->offset, cbForStateBusy);
        return;
    case DVD_COMMAND_CHANGE_DISK:
        DVDLowStopMotor(cbForStateBusy);
        return;
    case DVD_COMMAND_BS_CHANGE_DISK:
        DVDLowStopMotor(cbForStateBusy);
        return;
    case DVD_COMMAND_INITSTREAM:
        __DIRegs[1] = __DIRegs[1];
        if (AutoFinishing != 0) {
            executing->currTransferSize = 0;
            DVDLowRequestAudioStatus(0, cbForStateBusy);
            return;
        }
        executing->currTransferSize = 1;
        DVDLowAudioStream(0, block->length, block->offset, cbForStateBusy);
        return;
    case DVD_COMMAND_CANCELSTREAM:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioStream(0x10000, 0U, 0U, cbForStateBusy);
        return;
    case DVD_COMMAND_STOP_STREAM_AT_END:
        __DIRegs[1] = __DIRegs[1];
        AutoFinishing = 1;
        DVDLowAudioStream(0, 0U, 0U, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_AUDIO_ERROR:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_PLAY_ADDR:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x10000, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_START_ADDR:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x20000, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_LENGTH:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x30000, cbForStateBusy);
        return;
    case DVD_COMMAND_AUDIO_BUFFER_CONFIG:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioBufferConfig(block->offset, block->length, cbForStateBusy);
        return;
    case DVD_COMMAND_INQUIRY:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = 0x20;
        DVDLowInquiry(block->addr, cbForStateBusy);
        return;
    }
}

static void cbForStateBusy(unsigned long intType)
{
    struct DVDCommandBlock* finished;
    long result;

    if (intType == 0x10) {
        executing->state = DVD_RESULT_FATAL_ERROR;
        stateTimeout();
        return;
    }

    if ((CurrCommand == DVD_COMMAND_CHANGE_DISK) ||
        (CurrCommand == DVD_COMMAND_BS_CHANGE_DISK))
    {
        if (intType & DVD_INTTYPE_DE) {
            executing->state = DVD_STATE_FATAL_ERROR;
            stateError(0x1234567);
            return;
        }
        ASSERTLINE(0x64B, intType == DVD_INTTYPE_TC);
        NumInternalRetry = 0;
        if (CurrCommand == DVD_COMMAND_BS_CHANGE_DISK) {
            ResetRequired = 1;
        }
        if (cancel_inline(7)) {
            return;
        }
        executing->state = DVD_STATE_MOTOR_STOPPED;
        stateMotorStopped();
        return;
    }
    ASSERTLINE(0x671, (intType & DVD_INTTYPE_CVR) == 0);
    if ((CurrCommand == DVD_COMMAND_READ) ||
        (CurrCommand == DVD_COMMAND_BSREAD) ||
        (CurrCommand == DVD_COMMAND_READID) ||
        (CurrCommand == DVD_COMMAND_INQUIRY))
    {
        executing->transferredSize +=
            executing->currTransferSize - __DIRegs[6];
    }
    if (intType & 8) {
        Canceling = 0;
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = DVD_STATE_CANCELED;
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
        ASSERTLINE(0x697, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        if (cancel_inline(0)) {
            return;
        }
        if (CurrCommand == DVD_COMMAND_READ ||
            CurrCommand == DVD_COMMAND_BSREAD ||
            CurrCommand == DVD_COMMAND_READID ||
            CurrCommand == DVD_COMMAND_INQUIRY)
        {
            if (executing->transferredSize != executing->length) {
                stateBusy(executing);
                return;
            }
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(finished->transferredSize, finished);
            }
            stateReady();
            return;
        } else if (CurrCommand == DVD_COMMAND_REQUEST_AUDIO_ERROR ||
                   CurrCommand == DVD_COMMAND_REQUEST_PLAY_ADDR ||
                   CurrCommand == DVD_COMMAND_REQUEST_START_ADDR ||
                   CurrCommand == DVD_COMMAND_REQUEST_LENGTH)
        {
            if (CurrCommand == DVD_COMMAND_REQUEST_START_ADDR ||
                CurrCommand == DVD_COMMAND_REQUEST_PLAY_ADDR)
            {
                result = __DIRegs[8] * 4;
            } else {
                result = __DIRegs[8];
            }

            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(result, finished);
            }
            stateReady();
            return;
        } else if (CurrCommand == DVD_COMMAND_INITSTREAM) {
            if (executing->currTransferSize == 0) {
                if (__DIRegs[8] & 1) {
                    finished = executing;
                    executing = &DummyCommandBlock;
                    finished->state = DVD_STATE_IGNORED;
                    if (finished->callback) {
                        finished->callback(-2, finished);
                    }
                    stateReady();
                    return;
                }
                AutoFinishing = 0;
                executing->currTransferSize = 1;
                DVDLowAudioStream(0, executing->length, executing->offset,
                                  cbForStateBusy);
                return;
            }
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(0, finished);
            }
            stateReady();
            return;
        } else {
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(0, finished);
            }
            stateReady();
            return;
        }
    } else if (CurrCommand == 0xE) {
        executing->state = DVD_RESULT_FATAL_ERROR;
        stateError(0x1234567);
        return;
    } else {
        ASSERTLINE(0x728, intType == DVD_INTTYPE_DE);

        if ((CurrCommand == DVD_COMMAND_READ ||
             CurrCommand == DVD_COMMAND_BSREAD ||
             CurrCommand == DVD_COMMAND_READID ||
             CurrCommand == DVD_COMMAND_INQUIRY) &&
            executing->transferredSize == executing->length) {
            if (!cancel_inline(0)) {
                DVDCommandBlock* finished = executing;
                executing = &DummyCommandBlock;
                finished->state = DVD_STATE_END;
                if (finished->callback != NULL) {
                    finished->callback(finished->transferredSize, finished);
                }
                stateReady();
            }
        } else {
            stateGettingError();
        }
    }
}

static int issueCommand(long prio, struct DVDCommandBlock* block)
{
    int level;
    int result;

    if (autoInvalidation != 0 && (block->command == DVD_COMMAND_READ ||
                                  block->command == DVD_COMMAND_BSREAD ||
                                  block->command == DVD_COMMAND_READID ||
                                  block->command == DVD_COMMAND_INQUIRY))
    {
        DCInvalidateRange(block->addr, block->length);
    }
    level = OSDisableInterrupts();
#if DEBUG
    if (executing == block ||
        block->state == DVD_STATE_WAITING && __DVDIsBlockInWaitingQueue(block))
    {
        ASSERTMSGLINE(0x758, FALSE,
                      "DVD library: Specified command block (or file info) is "
                      "already in use\n");
    }
#endif
    block->state = DVD_STATE_WAITING;
    result = __DVDPushWaitingQueue(prio, block);
    if (executing == NULL && !PauseFlag) {
        stateReady();
    }
    OSRestoreInterrupts(level);
    return result;
}

int DVDReadAbsAsyncPrio(struct DVDCommandBlock* block, void* addr, long length,
                        long offset,
                        void (*callback)(long, struct DVDCommandBlock*),
                        long prio)
{
    int idle;

    ASSERTMSGLINE(0x780, block,
                  "DVDReadAbsAsync(): null pointer is specified to command "
                  "block address.");
    ASSERTMSGLINE(0x781, addr,
                  "DVDReadAbsAsync(): null pointer is specified to addr.");
    ASSERTMSGLINE(
        0x783, !OFFSET(addr, 32),
        "DVDReadAbsAsync(): address must be aligned with 32 byte boundary.");
    ASSERTMSGLINE(0x785, !(length & (32 - 1)),
                  "DVDReadAbsAsync(): length must be a multiple of 32.");
    ASSERTMSGLINE(0x787, !(offset & (4 - 1)),
                  "DVDReadAbsAsync(): offset must be a multiple of 4.");
    ASSERTMSGLINE(
        0x789, length > 0,
        "DVD read: 0 or negative value was specified to length of the read\n");
    block->command = DVD_COMMAND_READ;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(prio, block);
    ASSERTMSGLINE(0x793, idle,
                  "DVDReadAbsAsync(): command block is used for processing "
                  "previous request.");
    return idle;
}

int DVDSeekAbsAsyncPrio(struct DVDCommandBlock* block, long offset,
                        void (*callback)(long, struct DVDCommandBlock*),
                        long prio)
{
    int idle;

    ASSERTMSGLINE(
        0x7AA, block,
        "DVDSeekAbs(): null pointer is specified to command block address.");
    ASSERTMSGLINE(0x7AC, !(offset & (4 - 1)),
                  "DVDSeekAbs(): offset must be a multiple of 4.");
    block->command = DVD_COMMAND_SEEK;
    block->offset = offset;
    block->callback = callback;
    idle = issueCommand(prio, block);
    ASSERTMSGLINE(0x7B3, idle,
                  "DVDSeekAbs(): command block is used for processing "
                  "previous request.");
    return idle;
}

int DVDReadAbsAsyncForBS(struct DVDCommandBlock* block, void* addr,
                         long length, long offset,
                         void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    ASSERTMSGLINE(0x7D1, block,
                  "DVDReadAbsAsyncForBS(): null pointer is specified to "
                  "command block address.");
    ASSERTMSGLINE(
        0x7D2, addr,
        "DVDReadAbsAsyncForBS(): null pointer is specified to addr.");
    ASSERTMSGLINE(0x7D4, !OFFSET(addr, 32),
                  "DVDReadAbsAsyncForBS(): address must be aligned with 32 "
                  "byte boundary.");
    ASSERTMSGLINE(0x7D6, !(length & (32 - 1)),
                  "DVDReadAbsAsyncForBS(): length must be a multiple of 32.");
    ASSERTMSGLINE(0x7D8, !(offset & (4 - 1)),
                  "DVDReadAbsAsyncForBS(): offset must be a multiple of 4.");
    block->command = DVD_COMMAND_BSREAD;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(2, block);
    ASSERTMSGLINE(0x7E2, idle,
                  "DVDReadAbsAsyncForBS(): command block is used for "
                  "processing previous request.");
    return idle;
}

int DVDReadDiskID(struct DVDCommandBlock* block, struct DVDDiskID* diskID,
                  void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    ASSERTMSGLINE(0x7F9, block,
                  "DVDReadDiskID(): null pointer is specified to command "
                  "block address.");
    ASSERTMSGLINE(0x7FA, diskID,
                  "DVDReadDiskID(): null pointer is specified to id address.");
    ASSERTMSGLINE(
        0x7FC, !OFFSET(diskID, 32),
        "DVDReadDiskID(): id must be aligned with 32 byte boundary.");

    block->command = DVD_COMMAND_READID;
    block->addr = diskID;
    block->length = 0x20;
    block->offset = 0;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(2, block);
    ASSERTMSGLINE(0x806, idle,
                  "DVDReadDiskID(): command block is used for processing "
                  "previous request.");
    return idle;
}

int DVDPrepareStreamAbsAsync(struct DVDCommandBlock* block,
                             unsigned long length, unsigned long offset,
                             void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_INITSTREAM;
    block->length = length;
    block->offset = offset;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

int DVDCancelStreamAsync(struct DVDCommandBlock* block,
                         void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_CANCELSTREAM;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

long DVDCancelStream(struct DVDCommandBlock* block)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result = DVDCancelStreamAsync(block, cbForCancelStreamSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state != DVD_STATE_BUSY && state != DVD_STATE_WAITING) {
            retVal = ResultForSyncCommand;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForCancelStreamSync(long result, struct DVDCommandBlock* block)
{
    ResultForSyncCommand = result;
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDStopStreamAtEndAsync(struct DVDCommandBlock* block,
                            void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_STOP_STREAM_AT_END;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

long DVDStopStreamAtEnd(struct DVDCommandBlock* block)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result = DVDStopStreamAtEndAsync(block, cbForStopStreamAtEndSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state != DVD_STATE_BUSY && state != DVD_STATE_WAITING) {
            retVal = ResultForSyncCommand;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForStopStreamAtEndSync(long result,
                                     struct DVDCommandBlock* block)
{
    ResultForSyncCommand = result;
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDGetStreamErrorStatusAsync(struct DVDCommandBlock* block,
                                 void (*callback)(long,
                                                  struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_REQUEST_AUDIO_ERROR;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

long DVDGetStreamErrorStatus(struct DVDCommandBlock* block)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result =
        DVDGetStreamErrorStatusAsync(block, cbForGetStreamErrorStatusSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state != DVD_STATE_BUSY && state != DVD_STATE_WAITING) {
            retVal = ResultForSyncCommand;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForGetStreamErrorStatusSync(long result,
                                          struct DVDCommandBlock* block)
{
    ResultForSyncCommand = result;
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDGetStreamPlayAddrAsync(struct DVDCommandBlock* block,
                              void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_REQUEST_PLAY_ADDR;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

long DVDGetStreamPlayAddr(struct DVDCommandBlock* block)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result = DVDGetStreamPlayAddrAsync(block, cbForGetStreamPlayAddrSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state != DVD_STATE_BUSY && state != DVD_STATE_WAITING) {
            retVal = ResultForSyncCommand;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForGetStreamPlayAddrSync(long result,
                                       struct DVDCommandBlock* block)
{
    ResultForSyncCommand = result;
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDGetStreamStartAddrAsync(struct DVDCommandBlock* block,
                               void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_REQUEST_START_ADDR;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

long DVDGetStreamStartAddr(struct DVDCommandBlock* block)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result = DVDGetStreamStartAddrAsync(block, cbForGetStreamStartAddrSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state != DVD_STATE_BUSY && state != DVD_STATE_WAITING) {
            retVal = ResultForSyncCommand;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForGetStreamStartAddrSync(long result,
                                        struct DVDCommandBlock* block)
{
    ResultForSyncCommand = result;
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDGetStreamLengthAsync(struct DVDCommandBlock* block,
                            void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_REQUEST_LENGTH;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

long DVDGetStreamLength(struct DVDCommandBlock* block)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result = DVDGetStreamLengthAsync(block, cbForGetStreamLengthSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state != DVD_STATE_BUSY && state != DVD_STATE_WAITING) {
            retVal = ResultForSyncCommand;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForGetStreamLengthSync(long result,
                                     struct DVDCommandBlock* block)
{
    ResultForSyncCommand = result;
    OSWakeupThread(&__DVDThreadQueue);
}

void __DVDAudioBufferConfig(struct DVDCommandBlock* block,
                            unsigned long enable, unsigned long size,
                            void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    block->command = DVD_COMMAND_AUDIO_BUFFER_CONFIG;
    block->offset = enable;
    block->length = size;
    block->callback = callback;
    idle = issueCommand(2, block);
}

int DVDChangeDiskAsyncForBS(struct DVDCommandBlock* block,
                            void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    ASSERTMSGLINE(0xA1F, block,
                  "DVDChangeDiskAsyncForBS(): null pointer is specified to "
                  "command block address.");
    block->command = DVD_COMMAND_BS_CHANGE_DISK;
    block->callback = callback;
    idle = issueCommand(2, block);
    ASSERTMSGLINE(0xA25, idle,
                  "DVDChangeDiskAsyncForBS(): command block is used for "
                  "processing previous request.");
    return idle;
}

int DVDChangeDiskAsync(struct DVDCommandBlock* block, struct DVDDiskID* id,
                       void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    ASSERTMSGLINE(0xA3A, block,
                  "DVDChangeDisk(): null pointer is specified to command "
                  "block address.");
    ASSERTMSGLINE(0xA3B, id,
                  "DVDChangeDisk(): null pointer is specified to id address.");
    block->command = DVD_COMMAND_CHANGE_DISK;
    block->id = id;
    block->callback = callback;
    DCInvalidateRange(bootInfo->FSTLocation, bootInfo->FSTMaxLength);
    idle = issueCommand(2, block);
    ASSERTMSGLINE(0xA44, idle,
                  "DVDChangeDisk(): command block is used for processing "
                  "previous request.");
    return idle;
}

long DVDChangeDisk(struct DVDCommandBlock* block, struct DVDDiskID* id)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result = DVDChangeDiskAsync(block, id, cbForChangeDiskSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == DVD_STATE_END) {
            retVal = 0;
            break;
        } else if (state == DVD_STATE_FATAL_ERROR) {
            retVal = -1;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForChangeDiskSync()
{
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDInquiryAsync(struct DVDCommandBlock* block, struct DVDDriveInfo* info,
                    void (*callback)(long, struct DVDCommandBlock*))
{
    int idle;

    ASSERTMSGLINE(0xA94, block,
                  "DVDInquiry(): Null address was specified for block");
    ASSERTMSGLINE(0xA95, info,
                  "DVDInquiry(): Null address was specified for info");
    ASSERTMSGLINE(0xA97, !OFFSET(info, 32),
                  "DVDInquiry(): Address for info is not 32 bytes aligned");

    block->command = DVD_COMMAND_INQUIRY;
    block->addr = info;
    block->length = 0x20;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(2, block);
    return idle;
}

long DVDInquiry(struct DVDCommandBlock* block, struct DVDDriveInfo* info)
{
    int result;
    long state;
    int enabled;
    long retVal;

    result = DVDInquiryAsync(block, info, cbForInquirySync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state != DVD_STATE_BUSY && state != DVD_STATE_WAITING) {
            retVal = ResultForSyncCommand;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForInquirySync(long result, struct DVDCommandBlock* block)
{
    ResultForSyncCommand = result;
    OSWakeupThread(&__DVDThreadQueue);
}

void DVDReset()
{
    DVDLowReset();
    __DIRegs[0] = 0x2A;
    __DIRegs[1] = __DIRegs[1];
    ResetRequired = 0;
    ResumeFromHere = 0;
}

int DVDResetRequired()
{
    return ResetRequired;
}

long DVDGetCommandBlockStatus(struct DVDCommandBlock* block)
{
    ASSERTMSGLINE(0xAF9, block,
                  "DVDGetCommandBlockStatus(): null pointer is specified to "
                  "command block address.");
    if (block->state == DVD_STATE_END ||
        block->state == DVD_STATE_FATAL_ERROR ||
        block->state == DVD_STATE_CANCELED)
    {
        return block->state;
    }
    return block->state;
}

long DVDGetDriveStatus()
{
    struct DVDCommandBlock* block;
    long result;
    u8 _[4];

    BOOL enabled = OSDisableInterrupts();

    if (FatalErrorFlag) {
        result = DVD_STATE_FATAL_ERROR;
    } else if (PausingFlag != 0) {
        result = DVD_STATE_PAUSING;
    } else {
        block = executing;
        if (block == NULL) {
            result = DVD_STATE_END;
        } else if (block == &DummyCommandBlock) {
            result = DVD_STATE_END;
        } else {
            BOOL enabled = OSDisableInterrupts();
            result = block->state;
            if (block->state == DVD_STATE_COVER_CLOSED) {
                result = DVD_STATE_BUSY;
            }
            OSRestoreInterrupts(enabled);
        }
    }

    OSRestoreInterrupts(enabled);
    return result;
}

int DVDSetAutoInvalidation(int autoInval)
{
    int prev;

    prev = autoInvalidation;
    autoInvalidation = autoInval;
    return prev;
}

void DVDPause()
{
    int level;

    level = OSDisableInterrupts();
    PauseFlag = 1;
    if (executing == NULL) {
        PausingFlag = 1;
    }
    OSRestoreInterrupts(level);
}

void DVDResume()
{
    int level;

    level = OSDisableInterrupts();
    PauseFlag = 0;
    if (PausingFlag != 0) {
        PausingFlag = 0;
        stateReady();
    }
    OSRestoreInterrupts(level);
}

int DVDCancelAsync(struct DVDCommandBlock* block,
                   void (*callback)(long, struct DVDCommandBlock*))
{
    int enabled;
    void (*old)(unsigned long);

    enabled = OSDisableInterrupts();

    switch (block->state) {
    case DVD_STATE_FATAL_ERROR:
    case DVD_STATE_END:
    case DVD_STATE_CANCELED:
        if (callback) {
            callback(0, block);
        }
        break;
    case DVD_STATE_BUSY:
        if (Canceling != 0) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        Canceling = 1;
        CancelCallback = callback;
        if (block->command == DVD_COMMAND_BSREAD ||
            block->command == DVD_COMMAND_READ)
        {
            DVDLowBreak();
        }
        break;
    case DVD_STATE_WAITING:
        __DVDDequeueWaitingQueue(block);
        block->state = DVD_STATE_CANCELED;
        if (block->callback) {
            block->callback(-3, block);
        }
        if (callback) {
            callback(0, block);
        }
        break;
    case DVD_STATE_COVER_CLOSED:
        switch (block->command) {
        case DVD_COMMAND_BSREAD:
        case DVD_COMMAND_READID:
        case DVD_COMMAND_AUDIO_BUFFER_CONFIG:
        case DVD_COMMAND_BS_CHANGE_DISK:
            if (callback) {
                callback(0, block);
            }
            break;
        default:
            if (Canceling != 0U) {
                OSRestoreInterrupts(enabled);
                return 0;
            }
            CancelCallback = callback;
            Canceling = 1;
            break;
        }
        break;
    case DVD_STATE_NO_DISK:
    case DVD_STATE_COVER_OPEN:
    case DVD_STATE_WRONG_DISK:
    case DVD_STATE_MOTOR_STOPPED:
    case DVD_STATE_RETRY:
        old = DVDLowClearCallback();
        ASSERTLINE(0xBDB, old == cbForStateMotorStopped);
        if (old != cbForStateMotorStopped) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        if (block->state == DVD_STATE_NO_DISK) {
            ResumeFromHere = 3;
        }
        if (block->state == DVD_STATE_COVER_OPEN) {
            ResumeFromHere = 4;
        }
        if (block->state == DVD_STATE_WRONG_DISK) {
            ResumeFromHere = 1;
        }
        if (block->state == DVD_STATE_RETRY) {
            ResumeFromHere = 2;
        }
        if (block->state == DVD_STATE_MOTOR_STOPPED) {
            ResumeFromHere = 7;
        }
        block->state = DVD_STATE_CANCELED;
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
    return 1;
}

long DVDCancel(volatile struct DVDCommandBlock* block)
{
    int result;
    long state;
    unsigned long command;
    int enabled;

    result = DVDCancelAsync((void*) block, cbForCancelSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR ||
            state == DVD_STATE_CANCELED)
        {
            break;
        }
        if (state == DVD_STATE_COVER_CLOSED) {
            command = block->command;
            if ((command == DVD_COMMAND_BSREAD) ||
                (command == DVD_COMMAND_READID) ||
                (command == DVD_COMMAND_AUDIO_BUFFER_CONFIG) ||
                (command == DVD_COMMAND_BS_CHANGE_DISK))
            {
                break;
            }
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

static void cbForCancelSync()
{
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDCancelAllAsync(DVDCBCallback callback)
{
    int enabled;
    struct DVDCommandBlock* p;
    int retVal;

    enabled = OSDisableInterrupts();
    DVDPause();
    while ((p = __DVDPopWaitingQueue())) {
        DVDCancelAsync(p, NULL);
    }
    if (executing) {
        retVal = DVDCancelAsync(executing, callback);
    } else {
        retVal = 1;
        if (callback) {
            callback(0, NULL);
        }
    }
    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

long DVDCancelAll(void)
{
    int result;
    int enabled;

    enabled = OSDisableInterrupts();
    CancelAllSyncComplete = 0;
    result = DVDCancelAllAsync(cbForCancelAllSync);
    if (result == 0) {
        OSRestoreInterrupts(enabled);
        return -1;
    }
    while (1) {
        if (CancelAllSyncComplete == 0) {
            OSSleepThread(&__DVDThreadQueue);
        } else {
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

static void cbForCancelAllSync()
{
    CancelAllSyncComplete = 1;
    OSWakeupThread(&__DVDThreadQueue);
}

struct DVDDiskID* DVDGetCurrentDiskID()
{
    return (void*) OSPhysicalToCached(0);
}

BOOL DVDCheckDisk(void)
{
    s32 enabled;
    s32 result;
    s32 state;

    enabled = OSDisableInterrupts();
    if (FatalErrorFlag) {
        state = DVD_RESULT_FATAL_ERROR;
    } else if (PausingFlag) {
        state = DVD_STATE_PAUSING;
    } else if (executing == NULL) {
        state = DVD_STATE_END;
    } else if (executing == &DummyCommandBlock) {
        state = DVD_STATE_END;
    } else {
        state = executing->state;
    }
    switch (state) {
    case 1:
    case 2:
    case 9:
    case 10:
        result = TRUE;
        break;
    case -1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
        result = FALSE;
        break;
    case 0:
    case 8:
        {
            u32 temp_r4 = __DIRegs[1];
            if (((temp_r4 >> 2) & 1) || (temp_r4 & 1)) {
                result = FALSE;
            } else {
                result = TRUE;
            }
        }
        break;
    }
    OSRestoreInterrupts(enabled);
    return result;
}

void __DVDPrepareResetAsync(DVDCBCallback callback)
{
    BOOL enabled = OSDisableInterrupts();
    __DVDClearWaitingQueue();
    if (Canceling) {
        CancelCallback = callback;
    } else {
        if (executing != NULL) {
            executing->callback = NULL;
        }

        DVDCancelAllAsync(callback);
    }
    OSRestoreInterrupts(enabled);
}
