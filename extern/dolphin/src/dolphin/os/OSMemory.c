#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/dvd.h>

u32 OSGetPhysicalMemSize(void) {
#if DEBUG
    OSBootInfo * BootInfo = (OSBootInfo *)OSPhysicalToCached(0);

    return BootInfo->memorySize;
#else
    return __OSPhysicalMemSize;
#endif
}

u32 OSGetConsoleSimulatedMemSize(void) {
#if DEBUG
    unsigned long * memSize = (unsigned long *)OSPhysicalToCached(0xF0);

    return *memSize;
#else
    return __OSSimulatedMemSize;
#endif
}
