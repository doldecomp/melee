.include "macros.inc"

.section .data
    .balign 8
.global lbl_80402420
lbl_80402420:
    .asciz "OSCheckActiveThreads: Failed RunQueue[prio].head != NULL && RunQueue[prio].tail != NULL in %d\n"
    .balign 4
    .asciz "OSThread.c"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed RunQueue[prio].head == NULL && RunQueue[prio].tail == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(&RunQueue[prio]) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSActiveThreadQueue.head == NULL || __OSActiveThreadQueue.head->linkActive.prev == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSActiveThreadQueue.tail == NULL || __OSActiveThreadQueue.tail->linkActive.next == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->linkActive.next == NULL || thread == thread->linkActive.next->linkActive.prev in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->linkActive.prev == NULL || thread == thread->linkActive.prev->linkActive.next in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed *(thread->stackEnd) == OS_THREAD_STACK_MAGIC in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed OS_PRIORITY_MIN <= thread->priority && thread->priority <= OS_PRIORITY_MAX+1 in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed 0 <= thread->suspend in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(&thread->queueJoin) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue == &RunQueue[thread->priority] in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed IsMember(&RunQueue[thread->priority], thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->priority == __OSGetEffectivePriority(thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed !IsSuspended(thread->suspend) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue != NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(thread->queue) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed IsMember(thread->queue, thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->priority == 32 in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed !__OSCheckDeadLock(thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queueMutex.head == NULL && thread->queueMutex.tail == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed. unkown thread state (%d) of thread %p\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSCheckMutexes(thread) in %d\n"
    .balign 4

.section .bss, "wa"
    .balign 8
.global lbl_804A7FB8
lbl_804A7FB8:
    .skip 0x9E8

.section .sdata
    .balign 8
.global lbl_804D5C28
lbl_804D5C28:
    .4byte 0x00000000
    .4byte 0x00000000

.section .sbss
    .balign 8
.global RunQueueBits
RunQueueBits:
    .skip 0x4
.global lbl_804D73DC
lbl_804D73DC:
    .skip 0x4
.global Reschedule
Reschedule:
    .skip 0x8
