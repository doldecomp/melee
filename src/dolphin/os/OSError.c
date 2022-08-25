#include <dolphin/os/OSError.h>
#include <stdio.h>

void OSReport(char* msg, ...)
{
    va_list args;

    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
}
