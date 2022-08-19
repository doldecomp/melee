// https://github.com/kiwi515/open_rvl/blob/b73758d687ac2e0b79f096ed7475ddd4662e8566/include/OS/OSMutex.h

#ifndef _OS_MUTEX_H_
#define _OS_MUTEX_H_
#include <dolphin/os/OSThread.h>
#include <dolphin/types.h>

typedef struct OSMutex
{
    OSThreadQueue queue;  // at 0x0
    OSThread *thread;     // at 0x8
    s32 lock;             // at 0xC
    struct OSMutex *next; // at 0x10
    struct OSMutex *prev; // at 0x14
} OSMutex;

void OSInitMutex(OSMutex *);
void OSLockMutex(OSMutex *);
void OSUnlockMutex(OSMutex *);
void __OSUnlockAllMutex(OSThread *);
BOOL OSTryLockMutex(OSMutex *);

#endif