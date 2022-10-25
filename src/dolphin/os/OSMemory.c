#include <dolphin/types.h>

u32 OSGetPhysicalMemSize(void)
{
    return *(u32*) 0x80000028;
}



#pragma push
asm unk_t OSGetConsoleSimulatedMemSize()
{ // clang-format off
    nofralloc
/* 80347BF0 003447D0  3C 60 80 00 */	lis r3, 0x800000F0@ha
/* 80347BF4 003447D4  80 63 00 F0 */	lwz r3, 0x800000F0@l(r3)
/* 80347BF8 003447D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop


