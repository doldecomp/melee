// https://github.com/kiwi515/open_rvl/blob/fe0742f3ed2090041d5a3c98b98da5ff3546338a/include/OS/OSThread.h

#ifndef _OSTHREAD_H_
#define _OSTHREAD_H_

#include <platform.h>

#include <dolphin/os/OSContext.h>

#define OS_PRIORITY_MIN 0
#define OS_PRIORITY_MAX 31

#define OS_THREAD_ATTR_DETACH 0x0001u

#define OS_THREAD_STACK_MAGIC 0xDEADBABE

#define OS_THREAD_SPECIFIC_MAX 2

typedef s32 OSPriority; //  0 highest, 31 lowest

typedef struct OSThread OSThread;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSThreadLink OSThreadLink;

typedef struct OSMutex OSMutex;
typedef struct OSMutexQueue OSMutexQueue;
typedef struct OSMutexLink OSMutexLink;
typedef struct OSCond OSCond;

typedef enum {
    OS_THREAD_STATE_EXITED = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_WAITING = 4,
    OS_THREAD_STATE_MORIBUND = 8
} OSThreadState;

typedef enum {
    OS_THREAD_DETACHED = (1 << 0)
} OSThreadFlag;

struct OSThreadQueue {
    OSThread* head; // at 0x0
    OSThread* tail; // at 0x4
};

struct OSThreadLink {
    OSThread* next;
    OSThread* prev;
};

struct OSMutexQueue {
    OSMutex* head; // at 0x0
    OSMutex* tail; // at 0x4
};

struct OSMutexLink {
    OSMutex* next; // at 0x0
    OSMutex* prev; // at 0x4
};

struct OSThread {
    OSContext context;
    u16 state;
    u16 attr;
    s32 suspend;
    OSPriority priority;
    OSPriority base;
    void* val;
    OSThreadQueue* queue;
    OSThreadLink link;
    OSThreadQueue queueJoin;
    OSMutex* mutex;
    OSMutexQueue queueMutex;
    OSThreadLink linkActive;
    u8* stackBase;
    u32* stackEnd;
    s32 error;
    void* specific[OS_THREAD_SPECIFIC_MAX];
};

typedef void (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

extern OSThreadQueue OS_THREAD_QUEUE AT_ADDRESS(0x800000DC);
extern OSThread* OS_CURRENT_THREAD AT_ADDRESS(0x800000E4);

OSSwitchThreadCallback OSSetSwitchThreadCallback(OSSwitchThreadCallback);
void __OSThreadInit(void);
void OSSetCurrentThread(OSThread*);
void OSInitMutexQueue(OSMutexQueue*);
void OSInitThreadQueue(OSThreadQueue*);
OSThread* OSGetCurrentThread(void);
bool OSIsThreadTerminated(OSThread*);
s32 OSDisableScheduler(void);
s32 OSEnableScheduler(void);
s32 __OSGetEffectivePriority(OSThread*);
void __OSPromoteThread(OSThread*, s32);
void __OSReschedule(void);
void OSYieldThread(void);
bool OSCreateThread(OSThread* thread, void* (*func)(void*), void* param,
                    void* stack, u32 stackSize, OSPriority priority, u16 attr);
void OSExitThread(OSThread*);
void OSCancelThread(OSThread*);
bool OSJoinThread(OSThread*, void*);
void OSDetachThread(OSThread*);
s32 OSResumeThread(OSThread*);
s32 OSSuspendThread(OSThread*);
void OSSleepThread(OSThreadQueue*);
void OSWakeupThread(OSThreadQueue*);
bool OSSetThreadPriority(OSThread*, s32);
void OSClearStack(u8);
void OSSleepTicks(s64);

void CheckThreadQueue(void);
void UnsetRun(OSThread* thread);
void OSCheckActiveThreads(void);
void SetEffectivePriority(void);

#endif
