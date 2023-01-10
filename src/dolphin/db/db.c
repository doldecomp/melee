#include <dolphin/base/PPCArch.h>
#include <dolphin/db/db.h>
#include <dolphin/os/os.h>
#include <placeholder.h>

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

BOOL DBIsDebuggerPresent(void)
{
    if (__DBInterface == NULL) {
        return 0;
    }

    return (BOOL) __DBInterface->bPresent;
}

static void __DBExceptionDestinationAux(void)
{
    u8 dummy[8];
    OSContext* ctx = (void*) (0x80000000 + *(u32*) 0xC0); // WTF??
    OSReport("DBExceptionDestination\n");
    OSDumpContext(ctx);
    PPCHalt();
}

#ifdef MWERKS_GEKKO

static asm void __DBExceptionDestination(void)
{ // clang-format off
    nofralloc
    mfmsr r3
    ori r3, r3, 0x30
    mtmsr r3
    b __DBExceptionDestinationAux
} // clang-format on

#elif defined(__GNUC__) && defined(GEKKO)

static void __DBExceptionDestination(void)
{
    asm("mfmsr %r3\n"
        "ori %r3, %r3, 0x30\n"
        "mtmsr %r3\n"
        "b __DBExceptionDestinationAux\n");
}

#else

static void __DBExceptionDestination(void)
{
    NOT_IMPLEMENTED;
}

#endif

int __DBIsExceptionMarked(u8 a)
{
    return __DBInterface->exceptionMask & (1 << a);
}

void DBPrintf(char* str, ...) {}
