/** @file
Issues:
 * @todo Should be called @c OS.c.
 */
#include <platform.h>
#include <placeholder.h>

#include <__mem.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/db/db.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os.h>
#include <dolphin/os/init/__start.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSArena.h>
#include <dolphin/os/OSAudioSystem.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSLink.h>
#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSResetSW.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/os/OSSync.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/sipriv.h>
#include <MetroTRK/dolphin_trk.h>
#include <MetroTRK/intrinsics.h>

typedef struct OSBootInfo {
    DVDDiskID DVDDiskID;
    u32 magic;
    u32 version;
    u32 memorySize;
    u32 consoleType; // at 0x2C
    void* arenaLo;
    void* arenaHi;
    void* FSTLocation;
    u32 FSTMaxLength;
} OSBootInfo;

typedef enum OSConsoleType {
    OS_CONSOLE_RETAIL = 0x00000000,
    OS_CONSOLE_EMULATOR = 0x10000000,
    OS_CONSOLE_PC_EMULATOR,
    OS_CONSOLE_ARTHUR,
    OS_CONSOLE_MINNOW,
} OSConsoleType;

#ifdef MWERKS_GEKKO
void __OSEVStart(void);
void __OSEVEnd(void);
#define OS_DBJUMPPOINT_ADDR 0x60
void __OSDBINTSTART(void);
void __OSDBINTEND(void);
void __OSDBJUMPSTART(void);
void __OSDBJUMPEND(void);
static const u32 NOP = 0x60000000;
#define OS_EXCEPTIONTABLE_ADDR 0x3000
#endif

static OSBootInfo* BootInfo;
static u32* BI2DebugFlag;
static UNK_T BI2DebugFlagHolder;
static bool AreWeInitialized;
static __OSExceptionHandler* OSExceptionTable;
OSTime __OSStartTime;

extern u8 __ArenaHi[];
extern u8 __ArenaLo[];

#ifdef MWERKS_GEKKO
/// Peephole bug triggered by inline asm function __OSFPRInit (unused in melee)
#pragma peephole off
#endif

u32 OSGetConsoleType(void)
{
    if (BootInfo == NULL || BootInfo->consoleType == 0) {
        // default console type
        return OS_CONSOLE_ARTHUR;
    }

    return BootInfo->consoleType;
}

extern u32 OSGetResetCode(void);

extern u32 BOOT_REGION_START AT_ADDRESS(0x812FDFF0);
extern u32 BOOT_REGION_END AT_ADDRESS(0x812FDFEC);

void ClearArena(void)
{
    if (OSGetResetCode() != 0x80000000) {
        memset(OSGetArenaLo(), 0, (u32) OSGetArenaHi() - (u32) OSGetArenaLo());
    } else {
        u32 boot_region_start = BOOT_REGION_START;
        u32 boot_region_end = BOOT_REGION_END;
        if (boot_region_start == 0) {
            memset(OSGetArenaLo(), 0,
                   (u32) OSGetArenaHi() - (u32) OSGetArenaLo());
        } else if ((u32) OSGetArenaLo() < boot_region_start) {
            if ((u32) OSGetArenaHi() <= boot_region_start) {
                memset(OSGetArenaLo(), 0,
                       (u32) OSGetArenaHi() - (u32) OSGetArenaLo());
            } else {
                memset(OSGetArenaLo(), 0,
                       boot_region_start - (u32) OSGetArenaLo());
                if ((u32) OSGetArenaHi() > boot_region_end) {
                    memset((void*) boot_region_end, 0,
                           (u32) OSGetArenaHi() - boot_region_end);
                }
            }
        }
    }
}

extern bool __DVDLongFileNameFlag;
extern u32 __PADSpec;

typedef struct BI2Debug {
    s32 debugMonSize;  // 0x0
    s32 simMemSize;    // 0x4
    u32 argOffset;     // 0x8
    u32 debugFlag;     // 0xC
    int trackLocation; // 0x10
    int trackSize;     // 0x14
    u32 countryCode;   // 0x18
    u8 unk[8];         // 0x1C
    u32 padSpec;       // 0x24
} BI2Debug;

#define OS_BI2_DEBUG_ADDRESS 0x800000F4
#define OS_DEBUG_ADDRESS_2 0x800030E9

extern vu16 __OSDeviceCode AT_ADDRESS(OS_BASE_CACHED | 0x30E6);

extern volatile struct {
    u32 x0;
    u32 intr;
    u8 _[0x2C - 0x8];
    u32 x2C;
} OS_PI AT_ADDRESS(0xCC003000);

/**
 * Initializes the Dolphin operating system.
 *     - most of the main operations get farmed out to other functions
 *     - loading debug info and setting up heap bounds largely happen here
 *     - a lot of OS reporting also gets controlled here
 */
void OSInit(void)
{
    // pretty sure this is the min(/max) amount of pointers etc for the stack
    // to match
    BI2Debug* DebugInfo;
    void* debugArenaLo;
    u32 inputConsoleType;

    // check if we've already done all this or not
    if (!AreWeInitialized) {
        // flag to make sure we don't have to do this again
        AreWeInitialized = true;

        // SYSTEM

        __OSStartTime = __OSGetSystemTime();
        OSDisableInterrupts();

        // DEBUG

        // load some DVD stuff

        // debug flag from the DVD BI2 header
        BI2DebugFlag = 0;
        // set pointer to BootInfo
        BootInfo = (OSBootInfo*) OS_BASE_CACHED;

        // flag to tell us whether we make it through the debug loading
        __DVDLongFileNameFlag = false;

        // time to grab a bunch of debug info from the DVD
        // the address for where the BI2 debug info is, is stored at
        // OS_BI2_DEBUG_ADDRESS
        DebugInfo = (BI2Debug*) *((u32*) OS_BI2_DEBUG_ADDRESS);

        // if the debug info address exists, grab some debug info
        if (DebugInfo != NULL) {
            // debug flag from DVD BI2
            BI2DebugFlag = &DebugInfo->debugFlag;
            // some other info from DVD BI2
            __PADSpec = (u32) DebugInfo->padSpec;
            // store flag in mem
            *((u8*) DEBUGFLAG_ADDR) = (u8) *BI2DebugFlag;
            // store other info in mem
            *((u8*) OS_DEBUG_ADDRESS_2) = (u8) __PADSpec;
        } else if (BootInfo->arenaHi) {
            // if the top of the heap is already set

            // grab whatever's stored at 0x800030E8
            BI2DebugFlagHolder = (u32*) (uintptr_t) (*(u8*) DEBUGFLAG_ADDR);
            // flag is then address of flag holder
            BI2DebugFlag = (u32*) &BI2DebugFlagHolder;
            // pad spec is whatever's at 0x800030E9
            __PADSpec = (u32) * ((u8*) OS_DEBUG_ADDRESS_2);
        }

        // we made it through debug!
        __DVDLongFileNameFlag = true;

        // HEAP

        // set up bottom of heap (ArenaLo)
        // grab address from BootInfo if it exists, otherwise use default
        // __ArenaLo
        OSSetArenaLo(BootInfo->arenaLo == NULL ? __ArenaLo
                                               : BootInfo->arenaLo);

        // if the input arenaLo is null, and debug flag location exists (and
        // flag is < 2), set arenaLo to just past the end of the db stack
        if (BootInfo->arenaLo == NULL && BI2DebugFlag != NULL &&
            *BI2DebugFlag < 2)
        {
            debugArenaLo = (char*) (((u32) _stack_addr + 0x1f) & ~0x1f);
            OSSetArenaLo(debugArenaLo);
        }

        // set up top of heap (ArenaHi)
        // grab address from BootInfo if it exists, otherwise use default
        // __ArenaHi
        OSSetArenaHi(BootInfo->arenaHi == NULL ? __ArenaHi
                                               : BootInfo->arenaHi);

        // OS INIT AND REPORT

        // initialise a whole bunch of OS stuff
        OSExceptionInit();
        __OSInitSystemCall();
        OSInitAlarm();
        __OSModuleInit();
        __OSInterruptInit();
        __OSSetInterruptHandler(OS_INTR_PI_RSW,
                                (void*) __OSResetSWInterruptHandler);
        __OSContextInit();
        __OSCacheInit();
        EXIInit();
        SIInit();
        __OSInitSram();
        __OSThreadInit();
        __OSInitAudioSystem();
        PPCMthid2(PPCMfhid2() & 0xBFFFFFFF);

        if (BootInfo->consoleType & 0x10000000) {
            BootInfo->consoleType = 0x10000004;
        } else {
            BootInfo->consoleType = 1;
        }
        {
            BootInfo->consoleType += (OS_PI.x2C & 0xF0000000) >> 28;
        }

        __OSInitMemoryProtection();

        // begin OS reporting
        OSReport("\nDolphin OS $Revision: 47 $.\n");
        OSReport("Kernel built : %s %s\n", "Nov 12 2001", "01:46:17");
        OSReport("Console Type : ");

        if (BootInfo == NULL ||
            (inputConsoleType = BootInfo->consoleType) == 0)
        {
            // default console type
            inputConsoleType = OS_CONSOLE_ARTHUR;
        } else {
            inputConsoleType = BootInfo->consoleType;
        }

        // work out what console type this corresponds to and report it
        // consoleTypeSwitchHi = inputConsoleType & 0xF0000000;
        if (!(inputConsoleType & 0x10000000)) {
            // check first bit

            OSReport("Retail %d\n", inputConsoleType);
        } else {
            // if first bit is set, check "the rest"

            switch (inputConsoleType) {
            case OS_CONSOLE_EMULATOR:
                OSReport("Mac Emulator\n");
                break;
            case OS_CONSOLE_PC_EMULATOR:
                OSReport("PC Emulator\n");
                break;
            case OS_CONSOLE_ARTHUR:
                OSReport("EPPC Arthur\n");
                break;
            case OS_CONSOLE_MINNOW:
                OSReport("EPPC Minnow\n");
                break;
            default:
                OSReport("Development HW%d\n", inputConsoleType - 0x10000003);
                break;
            }
        }

        // report memory size
        OSReport("Memory %d MB\n", BootInfo->memorySize >> 20);
        // report heap bounds
        OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());

        // if location of debug flag exists, and flag is >= 2, enable
        // MetroTRKInterrupts
        if (BI2DebugFlag != NULL && *BI2DebugFlag >= 2) {
            EnableMetroTRKInterrupts();
        }

        // free up memory and re-enable things
        ClearArena();
        OSEnableInterrupts();
    }
}

static u32 __OSExceptionLocations[] = {
    0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800,
    0x0900, 0x0C00, 0x0D00, 0x0F00, 0x1300, 0x1400, 0x1700,
};

#ifdef MWERKS_GEKKO
void OSExceptionInit(void)
{
    u8 exception;
    void* destAddr;

    // These two vars help us change the exception number embedded
    // in the exception handler code.
    u32* opCodeAddr;
    u32 oldOpCode;

    // Address range of the actual code to be copied.
    u8* handlerStart;
    u32 handlerSize;

    // Install the first level exception vector.
    opCodeAddr = (u32*) __OSEVSetNumber;
    oldOpCode = *opCodeAddr;
    handlerStart = (u8*) __OSEVStart;
    handlerSize = (u32) ((u8*) __OSEVEnd - (u8*) __OSEVStart);

    // Install the DB integrator, only if we are the first OSInit to be run
    destAddr = (void*) OSPhysicalToCached(OS_DBJUMPPOINT_ADDR);
    if (*(u32*) destAddr == 0)
    { // Low mem should be zero cleared only once by BS2
        DBPrintf("Installing OSDBIntegrator\n");
        memcpy(destAddr, (void*) __OSDBINTSTART,
               (u32) __OSDBINTEND - (u32) __OSDBINTSTART);
        DCFlushRangeNoSync(destAddr,
                           (u32) __OSDBINTEND - (u32) __OSDBINTSTART);
        __sync();
        ICInvalidateRange(destAddr, (u32) __OSDBINTEND - (u32) __OSDBINTSTART);
    }

    // Copy the right vector into the table
    for (exception = 0; exception < OS_EXCEPTION_COUNT; exception++) {
        if (BI2DebugFlag && (*BI2DebugFlag >= 2) &&
            __DBIsExceptionMarked(exception))
        {
            // this DBPrintf is suspicious.
            DBPrintf(">>> OSINIT: exception %d commandeered by TRK\n",
                     exception);
            continue;
        }

        // Modify the copy of code in text before transferring
        // to the exception table.
        *opCodeAddr = oldOpCode | exception;

        // Modify opcodes at __DBVECTOR if necessary
        if (__DBIsExceptionMarked(exception)) {
            DBPrintf(">>> OSINIT: exception %d vectored to debugger\n",
                     exception);
            memcpy(__DBVECTOR, __OSDBJUMPSTART,
                   (u32) __OSDBJUMPEND - (u32) __OSDBJUMPSTART);
        } else {
            // make sure the opcodes are still nop
            u32* ops = (u32*) __DBVECTOR;
            uint cb;

            for (cb = 0;
                 cb < (uintptr_t) __OSDBJUMPEND - (uintptr_t) __OSDBJUMPSTART;
                 cb += sizeof(u32))
            {
                *ops++ = NOP;
            }
        }

        // Install the modified handler.
        destAddr = (void*) OSPhysicalToCached(
            __OSExceptionLocations[(u32) exception]);
        memcpy(destAddr, handlerStart, handlerSize);
        DCFlushRangeNoSync(destAddr, handlerSize);
        __sync();
        ICInvalidateRange(destAddr, handlerSize);
    }

    // initialize pointer to exception table
    OSExceptionTable = OSPhysicalToCached(OS_EXCEPTIONTABLE_ADDR);

    // install default exception handlers
    for (exception = 0; exception < OS_EXCEPTION_COUNT; exception++) {
        /// @todo: remove cast
        __OSSetExceptionHandler(exception, (void*) OSDefaultExceptionHandler);
    }

    // restore the old opcode, so that we can re-start an application without
    // downloading the text segments
    *opCodeAddr = oldOpCode;

    DBPrintf("Exceptions initialized...\n");
}
#else

void OSExceptionInit(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO

asm void __OSDBIntegrator(void)
{ // clang-format off
    nofralloc
entry __OSDBINTSTART
    li r5, 0x40
    mflr r3
    stw r3, 0xc(r5)
    lwz r3, 8(r5)
    oris r3, r3, 0x8000
    mtlr r3
    li r3, 0x30
    mtmsr r3
    blr
entry __OSDBINTEND
} // clang-format on

#else

void __OSDBIntegrator(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void __OSDBJump(void)
{ // clang-format off
    nofralloc
entry __OSDBJUMPSTART
    bla OS_DBJUMPPOINT_ADDR
entry __OSDBJUMPEND
} // clang-format on

#else

void __OSDBJump(void)
{
    NOT_IMPLEMENTED;
}

#endif

__OSExceptionHandler __OSSetExceptionHandler(u8 exception,
                                             __OSExceptionHandler handler)
{
    __OSExceptionHandler old_handler = OSExceptionTable[exception];
    OSExceptionTable[exception] = handler;
    return old_handler;
}

__OSExceptionHandler __OSGetExceptionHandler(u8 exception)
{
    return OSExceptionTable[exception];
}

#ifdef MWERKS_GEKKO

asm void OSExceptionVector(void)
{ // clang-format off
    nofralloc
entry __OSEVStart
    mtspr 0x110, r4
    lwz r4, 0xc0(r0)
    stw r3, 0xc(r4)
    mfspr r3, 0x110
    stw r3, 0x10(r4)
    stw r5, 0x14(r4)
    lhz r3, 0x1a2(r4)
    ori r3, r3, 2
    sth r3, 0x1a2(r4)
    mfcr r3
    stw r3, 0x80(r4)
    mflr r3
    stw r3, 0x84(r4)
    mfctr r3
    stw r3, 0x88(r4)
    mfxer r3
    stw r3, 0x8c(r4)
    mfspr r3, 0x1a
    stw r3, 0x198(r4)
    mfspr r3, 0x1b
    stw r3, 0x19c(r4)
    mr r5, r3
entry __DBVECTOR
    nop
    mfmsr r3
    ori r3, r3, 0x30
    mtspr 0x1b, r3
entry __OSEVSetNumber
    li r3, 0
    lwz r4, 0xd4(r0)
    rlwinm. r5, r5, 0, 0x1e, 0x1e
    bne recoverable
    lis r5, OSDefaultExceptionHandler@ha
    addi r5, r5, OSDefaultExceptionHandler@l
    mtspr 0x1a, r5
    rfi
recoverable:
    rlwinm r5, r3, 2, 0x16, 0x1d
    lwz r5, 0x3000(r5)
    mtspr 0x1a, r5
    rfi
entry __OSEVEnd
    nop
} // clang-format on

#else

void OSExceptionVector(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void OSDefaultExceptionHandler(void)
{ // clang-format off
    nofralloc
    stw r0, 0(r4)
    stw r1, 4(r4)
    stw r2, 8(r4)
    stmw r6, 0x18(r4)
    mfspr r0, 0x391
    stw r0, 0x1a8(r4)
    mfspr r0, 0x392
    stw r0, 0x1ac(r4)
    mfspr r0, 0x393
    stw r0, 0x1b0(r4)
    mfspr r0, 0x394
    stw r0, 0x1b4(r4)
    mfspr r0, 0x395
    stw r0, 0x1b8(r4)
    mfspr r0, 0x396
    stw r0, 0x1bc(r4)
    mfspr r0, 0x397
    stw r0, 0x1c0(r4)
    mfdsisr r5
    mfdar r6
    b __OSUnhandledException
} // clang-format on

#else

void OSDefaultExceptionHandler(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

void __OSPSInit(void)
{
    PPCMthid2(PPCMfhid2() | 0xA0000000);
    ICFlashInvalidate();
    __sync();
    asm { // clang-format off
        li      r3, 0
        mtspr   GQR0, r3
    } // clang-format on
}

#else

void __OSPSInit(void)
{
    NOT_IMPLEMENTED;
}

#endif

#define DI_CONFIG_IDX 0x9
#define DI_CONFIG_CONFIG_MASK 0xFF

u32 __OSGetDIConfig(void)
{
    return __DIRegs[DI_CONFIG_IDX] & DI_CONFIG_CONFIG_MASK;
}
