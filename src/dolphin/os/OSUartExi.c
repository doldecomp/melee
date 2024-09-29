#include <platform.h>
#include <placeholder.h>

#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSUartExi.h>

static u32 Enabled[2];

extern s32 OSGetConsoleType(void);

s32 InitializeUART(void)
{
    if (!(OSGetConsoleType() & 0x10000000)) {
        Enabled[0] = 0;
        return 2;
    }
    Enabled[0] = 0xA5FF005A;
    return 0;
}

s32 ReadUARTN(void)
{
    return 4;
}

void WriteUARTN(void)
{
    NOT_IMPLEMENTED;
}
