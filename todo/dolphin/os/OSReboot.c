#include <placeholder.h>

#include <dolphin/os/OSReboot.h>

static bool Prepared;

void Run(register Event callback)
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
#else
    NOT_IMPLEMENTED;
#endif
}

static void Callback(void)
{
    Prepared = true;
}

void __OSReboot(u32 resetCode, bool forceMenu)
{
    NOT_IMPLEMENTED;
}
