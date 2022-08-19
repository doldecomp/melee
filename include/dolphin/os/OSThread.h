// https://github.com/kiwi515/open_rvl/blob/fe0742f3ed2090041d5a3c98b98da5ff3546338a/include/OS/OSThread.h

#ifndef _OSTHREAD_H_
#define _OSTHREAD_H_

#include <dolphin/types.h>
#include <dolphin/os/OSContext.h>

#define OS_PRIORITY_MIN 0
#define OS_PRIORITY_MAX 31

#define OS_THREAD_STACK_MAGIC 0xDEADBABE

typedef enum
{
    OS_THREAD_STATE_EXITED = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_SLEEPING = 4,
    OS_THREAD_STATE_MORIBUND = 8
} OSThreadState;

typedef enum
{
    OS_THREAD_DETACHED = (1 << 0)
} OSThreadFlag;

typedef struct OSThreadQueue
{
    struct OSThread *head; // at 0x0
    struct OSThread *tail; // at 0x4
} OSThreadQueue;

typedef struct OSMutexQueue
{
    struct OSMutex *head; // at 0x0
    struct OSMutex *tail; // at 0x4
} OSMutexQueue;

typedef struct OSThread
{
    OSContext context;
    u16 state;    // at 0x2C8
    u16 flags;    // at 0x2CA
    s32 suspend;  // at 0x2CC
    s32 priority; // at 0x2D0
    s32 WORD_0x2D4;
    u32 WORD_0x2D8;
    OSThreadQueue *queue;      // at 0x2DC
    struct OSThread *next;     // at 0x2E0
    struct OSThread *prev;     // at 0x2E4
    OSThreadQueue threadQueue; // at 0x2E8
    struct OSMutex *mutex;     // at 0x2F0
    OSMutexQueue mutexQueue;   // at 0x2F4
    struct OSThread *next2;    // at 0x2FC
    struct OSThread *prev2;    // at 0x300
    u32 *stackBegin;           // at 0x304
    u32 *stackEnd;             // at 0x308
    u32 WORD_0x30C;
    u32 ARR_0x310[2];
} OSThread;

typedef void (*OSSwitchThreadCallback)(OSThread *, OSThread *);

OSThreadQueue OS_THREAD_QUEUE
#ifndef M2C_CONTEXT
    : 0x800000DC
#endif
    ;
OSThread *OS_CURRENT_THREAD
#ifndef M2C_CONTEXT
    : 0x800000E4
#endif
    ;

STRUCT_PLACEHOLDER(OSThread, 1)
STRUCT_PLACEHOLDER(OSThread, 2)
STRUCT_PLACEHOLDER(OSThread, 3)
STRUCT_PLACEHOLDER(OSThread, 4)

typedef OSThread_Unk3 *(*OSThreadFunc)(OSThread_Unk4 *);
OSSwitchThreadCallback OSSetSwitchThreadCallback(OSSwitchThreadCallback);
void __OSThreadInit(void);
void OSSetCurrentThread(OSThread *);
void OSInitMutexQueue(OSMutexQueue *);
void OSInitThreadQueue(OSThreadQueue *);
OSThread *OSGetCurrentThread(void);
BOOL OSIsThreadTerminated(OSThread *);
s32 OSDisableScheduler(void);
s32 OSEnableScheduler(void);
s32 __OSGetEffectivePriority(OSThread *);
void __OSPromoteThread(OSThread *, s32);
void __OSReschedule(void);
void OSYieldThread(void);
BOOL OSCreateThread(OSThread *, OSThreadFunc, OSThread_Unk1 *, OSThread_Unk2 *, u32, s32, u16);
void OSExitThread(OSThread *);
void OSCancelThread(OSThread *);
BOOL OSJoinThread(OSThread *, void *);
void OSDetachThread(OSThread *);
s32 OSResumeThread(OSThread *);
s32 OSSuspendThread(OSThread *);
void OSSleepThread(OSThreadQueue *);
void OSWakeupThread(OSThreadQueue *);
BOOL OSSetThreadPriority(OSThread *, s32);
void OSClearStack(u8);
void OSSleepTicks(s64);

#endif