#include <dolphin/types.h>

u32 OSGetPhysicalMemSize(void)
{
    return *(u32*) 0x80000028;
}
