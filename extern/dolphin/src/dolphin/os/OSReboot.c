#include <dolphin/os.h>
#include "__dvd.h"
#include "__os.h"

static void* SaveStart = NULL;
static void* SaveEnd   = NULL;
static volatile BOOL Prepared;

extern u32 OS_RESET_CODE : 0x800030F0;
// unknown function, set to true by __OSReboot
extern u8 OS_REBOOT_BOOL : 0x800030E2;
extern u32 UNK_817FFFF8 : 0x817FFFF8;
extern u32 UNK_817FFFFC : 0x817FFFFC;

extern void* BOOT_REGION_START : (0x812FDFF0);
extern void* BOOT_REGION_END   : (0x812FDFEC);

#define OS_BOOTROM_ADDR ((void*)0x81300000)

typedef struct _ApploaderHeader {
    /* 0x00 */ char date[16];
    /* 0x10 */ u32 entry;
    /* 0x14 */ u32 size;
    /* 0x18 */ u32 rebootSize;
    /* 0x1C */ u32 reserved2;
} ApploaderHeader; // Size: 0x20

static ApploaderHeader Header __attribute__((aligned(32)));

static asm void Run(register void (*addr)())
{
    fralloc
    bl OSDisableInterrupts
    bl ICFlashInvalidate
    sync
    isync
    mtlr addr
    blr
    frfree
    blr
}

inline void ReadApploader(DVDCommandBlock* dvdCmd, void* addr, u32 offset,
                          u32 numBytes)
{
    /* Not sure if this inline is correct - might need to call other inlines */
    while (Prepared == FALSE) { }
    DVDReadAbsAsyncForBS(dvdCmd, addr, numBytes, offset + 0x2440, NULL);

    while (TRUE) {
        switch (dvdCmd->state) {
        case 0:
            break;
        case 1:
        default:
            continue;
        case -1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            __OSDoHotReset(UNK_817FFFFC);
            continue;
        }
        break;
    }
}

static void Callback(s32 result, struct DVDCommandBlock* block)
{
    Prepared = TRUE;
}

void __OSReboot(u32 resetCode, u32 bootDol)
{
    OSContext exceptionContext;
    DVDCommandBlock dvdCmd;
    DVDCommandBlock dvdCmd2;
    u32 numBytes;
    u32 offset;

    OSDisableInterrupts();

    UNK_817FFFFC = resetCode;
    UNK_817FFFF8 = 0;
    OS_REBOOT_BOOL = TRUE;
    BOOT_REGION_START = SaveStart;
    BOOT_REGION_END = SaveEnd;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    DVDInit();
    DVDSetAutoInvalidation(TRUE);

    __DVDPrepareResetAsync(Callback);

    if (!DVDCheckDisk()) {
        __OSDoHotReset(UNK_817FFFFC);
    }

    __OSMaskInterrupts(0xFFFFFFE0);
    __OSUnmaskInterrupts(0x400);

    OSEnableInterrupts();

    offset   = 0;
    numBytes = 32;
    ReadApploader(&dvdCmd, (void*)&Header, offset, numBytes);

    offset   = Header.size + 0x20;
    numBytes = OSRoundUp32B(Header.rebootSize);
    ReadApploader(&dvdCmd2, OS_BOOTROM_ADDR, offset, numBytes);

    ICInvalidateRange(OS_BOOTROM_ADDR, numBytes);
    Run(OS_BOOTROM_ADDR);
}

