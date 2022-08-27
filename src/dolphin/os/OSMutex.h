#ifndef DOLPHIN_OS_OSMUTEX_H
#define DOLPHIN_OS_OSMUTEX_H

#include <dolphin/os/OSThread.h>

typedef struct OSMutex {
    OSThreadQueue queue; // at 0x00
    OSThread* thread;    // at 0x08
    s32 count;           // at 0x0C
    OSMutexLink link;    // at 0x10
} OSMutex;

#endif
