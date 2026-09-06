#include "main_TRK.h"

#include "mainloop.h"
#include "nubinit.h"

static int TRK_mainError;

u8 TRKTargetCPUMinorType(void)
{
    return 0x54;
}

int TRK_main(void)
{
    TRK_mainError = TRKInitializeNub();

    if (!TRK_mainError) {
        TRKNubWelcome();
        TRKNubMainLoop();
    }

    return TRK_mainError = TRKTerminateNub();
}
