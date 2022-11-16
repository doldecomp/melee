#include <dolphin/dvd/dvd.h>

#include <dolphin/os/os.h>
#include <dolphin/os/OSThread.h>

extern BOOL DVDInitialized;
extern BOOL FirstTimeInBootrom;
extern struct {
    u32 x0[8];
    u32 boot_magic;
}* bootInfo;
extern s32 IDShouldBe;
void __DVDInterruptHandler();
extern OSThreadQueue __DVDThreadQueue;

struct _IO {
    u32 unk0;
    u32 unk4;
} IO : 0xCC006000;

void DVDInit(void)
{
    if (!DVDInitialized) {
        OSInitAlarm();
        DVDInitialized = TRUE;
        __DVDFSInit();
        __DVDClearWaitingQueue();
        __DVDInitWA();
        bootInfo = (void*) 0x80000000;
        IDShouldBe = 0x80000000;
        __OSSetInterruptHandler(0x15, __DVDInterruptHandler);
        __OSUnmaskInterrupts(0x400);
        OSInitThreadQueue(&__DVDThreadQueue);
        IO.unk0 = 0x2A;
        IO.unk4 = 0;
        if (bootInfo->boot_magic == 0xE5207C22) {
            OSReport("app booted via JTAG\n");
            OSReport("load fst\n");
            __fstLoad();
        } else if (bootInfo->boot_magic == 0xD15EA5E) {
            OSReport("app booted from bootrom\n");
        } else {
            FirstTimeInBootrom = TRUE;
            OSReport("bootrom\n");
        }
    }
}
