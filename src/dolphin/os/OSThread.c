#include <placeholder.h>

#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSMutex.h>
#include <dolphin/os/OSThread.h>

static vu32 RunQueueBits;
static volatile bool RunQueueHint;
static vs32 Reschedule;

void __OSThreadInit(void)
{
    NOT_IMPLEMENTED;
}

void OSInitThreadQueue(OSThreadQueue* queue)
{
    queue->tail = NULL;
    queue->head = NULL;
}

OSThread* OSGetCurrentThread(void)
{
    return OS_CURRENT_THREAD;
}

s32 OSDisableScheduler(void)
{
    bool enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = Reschedule++;
    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSEnableScheduler(void)
{
    bool enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = Reschedule--;
    OSRestoreInterrupts(enabled);
    return count;
}

void UnsetRun(OSThread* thread)
{
    OSThreadQueue* queue;
    OSThread* next;
    OSThread* prev;

    next = thread->link.next;
    queue = thread->queue;
    prev = thread->link.prev;

    if (next == NULL) {
        queue->tail = prev;
    } else {
        next->link.prev = prev;
    }

    if (prev == NULL) {
        queue->head = next;
    } else {
        prev->link.next = next;
    }

    if (queue->head == NULL) {
        RunQueueBits &= ~(1 << (31 - thread->priority));
    }

    thread->queue = NULL;
}

s32 __OSGetEffectivePriority(OSThread* thread)
{
    s32 prio = thread->base;

    OSMutex* mutex;
    for (mutex = thread->queueMutex.head; mutex != NULL;
         mutex = mutex->link.next)
    {
        OSThread* mutexThread = mutex->queue.head;
        if (mutexThread != NULL && mutexThread->priority < prio) {
            prio = mutexThread->priority;
        }
    }

    return prio;
}

void SetEffectivePriority(void)
{
    NOT_IMPLEMENTED;
}

static void SelectThread(bool yield)
{
    NOT_IMPLEMENTED;
}

void __OSReschedule(void)
{
    if (!RunQueueHint) {
        return;
    }

    SelectThread(false);
}

bool OSCreateThread(OSThread* thread, void* (*func)(void*), void* param,
                    void* stack, u32 stackSize, OSPriority priority, u16 attr)
{
    NOT_IMPLEMENTED;
}

void OSExitThread(OSThread* arg0)
{
    NOT_IMPLEMENTED;
}

void OSCancelThread(OSThread* arg0)
{
    NOT_IMPLEMENTED;
}

s32 OSResumeThread(OSThread* arg0)
{
    NOT_IMPLEMENTED;
}

s32 OSSuspendThread(OSThread* arg0)
{
    NOT_IMPLEMENTED;
}

void OSSleepThread(OSThreadQueue* arg0)
{
    NOT_IMPLEMENTED;
}

void OSWakeupThread(OSThreadQueue* arg0)
{
    NOT_IMPLEMENTED;
}

void CheckThreadQueue(void)
{
    NOT_IMPLEMENTED;
}

void OSCheckActiveThreads(void)
{
    NOT_IMPLEMENTED;
}
