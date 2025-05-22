#include <platform.h>

#include <MSL/console_io.h>

s32 InitializeUART(u32);
s32 WriteUARTN(s32, s32);
s32 ReadUARTN(u8*, u32);

bool MSL_ConsoleIo_804D7080;

u8 __read_console(u32 arg0, u8* buf, u32* n)
{
    u8 _[8];

    s32 init_status = 0;
    s32 read_status;
    s32 return_status;
    u32 bytes_to_read;

    if (MSL_ConsoleIo_804D7080 == false) {
        init_status = InitializeUART(0xE100);
        if (init_status == 0) {
            MSL_ConsoleIo_804D7080 = true;
        }
    }
    if (init_status != 0) {
        return 1;
    }
    bytes_to_read = *n;
    read_status = 0;
    *n = 0;
    while (*n <= bytes_to_read && read_status == 0) {
        read_status = ReadUARTN(buf, 1);
        *n += 1;
        if (*buf == '\r') {
            break;
        }
        buf++;
    }
    if (read_status == 0) {
        return_status = 0;
    } else {
        return_status = 1;
    }
    return return_status;
}

s32 __write_console(s32 arg0, s32 arg1, s32* arg2)
{
    u8 _[8];
    s32 uart_status = 0;
    if (!MSL_ConsoleIo_804D7080) {
        uart_status = InitializeUART(0xE100);
        if (uart_status == 0) {
            MSL_ConsoleIo_804D7080 = true;
        }
    }
    if (uart_status != 0) {
        return 1;
    }
    if (WriteUARTN(arg1, *arg2)) {
        *arg2 = 0;
        return 1;
    }
    return 0;
}

s32 MSL_ConsoleIo_80325F18(void)
{
    return 0;
}
