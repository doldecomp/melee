#include <placeholder.h>

#include <dolphin/base/PPCArch.h>
#include <dolphin/db/db.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>

static DBInterface* __DBInterface;
static int DBVerbose;

static void __DBExceptionDestination(void);

void DBInit(void)
{
    __DBInterface = (void*) 0x80000040;
    *(u32*) 0x80000048 = (u32) __DBExceptionDestination - 0x80000000;
    DBVerbose = 1;
    return;
}

bool DBIsDebuggerPresent(void)
{
    if (__DBInterface == NULL) {
        return false;
    }

    return (bool) __DBInterface->bPresent;
}

static void __DBExceptionDestinationAux(void)
{
    u8 _[8];

    OSContext* ctx = (void*) (0x80000000 + *(u32*) 0xC0); // WTF??
    OSReport("DBExceptionDestination\n");
    OSDumpContext(ctx);
    PPCHalt();
}

#ifdef MWERKS_GEKKO
asm void __DBExceptionDestination(void)
{ // clang-format off
    nofralloc
    mfmsr r3
    ori r3, r3, 0x30
    mtmsr r3
    b __DBExceptionDestinationAux
} // clang-format on

#elif defined(__GNUC__) && defined(__PPCGEKKO__)
void __DBExceptionDestination(void)
{
    asm("mfmsr %r3\n"
        "ori %r3, %r3, 0x30\n"
        "mtmsr %r3\n"
        "b __DBExceptionDestinationAux\n");
}

#else
void __DBExceptionDestination(void)
{
    NOT_IMPLEMENTED;
}
#endif

bool __DBIsExceptionMarked(u8 exception)
{
    return __DBInterface->exceptionMask & (1 << exception);
}

void DBPrintf(const char* str, ...) {}
