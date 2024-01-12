// https://github.com/kiwi515/open_rvl/blob/fe0742f3ed2090041d5a3c98b98da5ff3546338a/include/OS/OSThread.h

#ifndef _OSTHREAD_H_
#define _OSTHREAD_H_

#include <platform.h>

#include <dolphin/os/OSContext.h>

#define OS_PRIORITY_MIN 0
#define OS_PRIORITY_MAX 31

#define OS_THREAD_STACK_MAGIC 0xDEADBABE

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
    u16 state;            // at 0x2C8
    u16 flags;            // at 0x2CA
    s32 suspend;          // at 0x2CC
    s32 priority;         // at 0x2D0
    s32 WORD_0x2D4;       // at 0x2D4
    u32 WORD_0x2D8;       // at 0x2D8
    OSThreadQueue* queue; // at 0x2DC
    OSThreadLink link;
    OSThreadQueue threadQueue; // at 0x2E8
    OSMutex* mutex;            // at 0x2F0
    OSMutexQueue queueMutex;   // at 0x2F4
    OSThreadLink linkActive;   // at 0x2FC
    u32* stackBegin;           // at 0x304
    u32* stackEnd;             // at 0x308
    u32 WORD_0x30C;            // at 0x30C
    u32 ARR_0x310[2];          // at 0x310
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
void SelectThread(void);

#endif
