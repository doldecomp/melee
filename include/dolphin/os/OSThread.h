#ifndef _DOLPHIN_OSTHREAD_H_
#define _DOLPHIN_OSTHREAD_H_

#include <dolphin/os/OSContext.h>

typedef s32 OSPriority;

struct OSThread;
struct OSMutex;
struct OSMutexQueue;

typedef struct OSThread OSThread;

typedef struct OSThreadQueue
{
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct OSThreadLink
{
    struct OSThread *next;
    struct OSThread *prev;
} OSThreadLink;

typedef struct OSMutexQueue
{
    struct OSMutex *head;
    struct OSMutex *tail;
} OSMutexQueue;

typedef struct OSMutexLink
{
    struct OSMutex *next;
    struct OSMutex *prev;
} OSMutexLink;

typedef struct OSThread
{
    /*0x000*/ struct OSContext context;   
    /*0x2C8*/ u16 state;     
    /*0x2CA*/ u16 attr;      
    /*0x2CC*/ s32 suspend;   
    /*0x2D0*/ OSPriority priority;  
    /*0x2D4*/ OSPriority base;
    /*0x2D8*/ void *val;                          
    /*0x2DC*/ struct OSThreadQueue *queue;     
    /*0x2E0*/ struct OSThreadLink link;                    
    /*0x2E8*/ struct OSThreadQueue queueJoin;              
    /*0x2F0*/ struct OSMutex *mutex;     
    /*0x2F4*/ struct OSMutexQueue queueMutex;              
    /*0x2FC*/ struct OSThreadLink linkActive;             
    /*0x304*/ u8 *stackBase; 
    /*0x308*/ u32 *stackEnd;  
} OSThread;

enum OS_THREAD_STATE
{
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_WAITING = 4,
    OS_THREAD_STATE_MORIBUND = 8,
};

#define OS_PRIORITY_MIN 0  // highest
#define OS_PRIORITY_MAX 31 // lowest
#define OS_PRIORITY_IDLE OS_PRIORITY_MAX

#define OS_THREAD_ATTR_DETACH 0x0001u

#define OS_THREAD_STACK_MAGIC 0xDEADBABE

void OSInitThreadQueue(OSThreadQueue *queue);
void OSSleepThread(OSThreadQueue *queue);
void OSWakeupThread(OSThreadQueue *queue);
s32 OSSuspendThread(OSThread *thread);
s32 OSResumeThread(OSThread* thread);
OSThread* OSGetCurrentThread(void);
s32 OSEnableScheduler(void);
s32 OSDisableScheduler(void);

#define IsSuspended(suspend) (suspend > 0)

#endif
