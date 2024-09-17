#include <dolphin/os/OSMutex.h>

void __OSUnlockAllMutex(OSThread* thread)
{
    while (thread->queueMutex.head != NULL) {
        OSMutex* head = thread->queueMutex.head;
        OSMutex* next = head->link.next;

        if (next == NULL) {
            thread->queueMutex.tail = NULL;
        } else {
            next->link.prev = NULL;
        }
        thread->queueMutex.head = next;
        head->count = 0;
        head->thread = NULL;
        OSWakeupThread(&head->queue);
    }
}

bool __OSCheckMutex(OSMutex* mutex)
{
    OSThread* thread;
    OSThreadQueue* queue;
    OSPriority priority = 0;

    queue = &mutex->queue;
    if (!(queue->head == NULL || queue->head->link.prev == NULL)) {
        return false;
    }
    if (!(queue->tail == NULL || queue->tail->link.next == NULL)) {
        return false;
    }
    for (thread = queue->head; thread; thread = thread->link.next) {
        if (!(thread->link.next == NULL ||
              thread == thread->link.next->link.prev))
        {
            return false;
        }
        if (!(thread->link.prev == NULL ||
              thread == thread->link.prev->link.next))
        {
            return false;
        }

        if (thread->state != OS_THREAD_STATE_WAITING) {
            return false;
        }

        if (thread->priority < priority) {
            return false;
        }
        priority = thread->priority;
    }

    if (mutex->thread) {
        if (mutex->count <= 0) {
            return false;
        }
    } else {
        if (0 != mutex->count) {
            return false;
        }
    }

    return true;
}

bool __OSCheckDeadLock(OSThread* thread)
{
    OSMutex* mutex;

    mutex = thread->mutex;
    while (mutex && mutex->thread) {
        if (mutex->thread == thread) {
            return true;
        }
        mutex = mutex->thread->mutex;
    }
    return false;
}

bool __OSCheckMutexes(OSThread* thread)
{
    OSMutex* mutex;

    for (mutex = thread->queueMutex.head; mutex; mutex = mutex->link.next) {
        if (mutex->thread != thread) {
            return false;
        }
        if (!__OSCheckMutex(mutex)) {
            return false;
        }
    }
    return true;
}
