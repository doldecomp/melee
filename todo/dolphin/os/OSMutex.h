#ifndef DOLPHIN_OS_OSMUTEX_H
#define DOLPHIN_OS_OSMUTEX_H

#include <platform.h>

#include <dolphin/os/OSThread.h>

typedef struct OSMutex {
    OSThreadQueue queue; // at 0x00
    OSThread* thread;    // at 0x08
    s32 count;           // at 0x0C
    OSMutexLink link;    // at 0x10
} OSMutex;

void OSInitMutex(OSMutex*);
void OSLockMutex(OSMutex*);
void OSUnlockMutex(OSMutex*);
void __OSUnlockAllMutex(OSThread*);
bool OSTryLockMutex(OSMutex*);

bool __OSCheckDeadLock(OSThread* thread);
bool __OSCheckMutexes(OSThread* thread);
bool __OSCheckMutex(OSMutex* mutex);

#endif
