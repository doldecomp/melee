#include <dolphin/os.h>

static BOOL Prepared;

void Run(register RunCallback callback)
{
#ifdef MWERKS_GEKKO
    OSDisableInterrupts();
    ICFlashInvalidate();
    __sync();
    __isync();
    asm {
        mtlr callback
        blr
    }
#endif
}

static void Callback(void)
{
    Prepared = TRUE;
}

void __OSReboot(u32 resetCode, BOOL forceMenu) {}
