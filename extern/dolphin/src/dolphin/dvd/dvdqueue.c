#include <dolphin.h>
#include <dolphin/dvd.h>

#include "__dvd.h"

static struct {
    /* 0x00 */ struct DVDCommandBlock * next;
    /* 0x04 */ struct DVDCommandBlock * prev;
} WaitingQueue[4];

static struct DVDCommandBlock * PopWaitingQueuePrio(long prio);

void __DVDClearWaitingQueue(void) {
    unsigned long i;
    struct DVDCommandBlock * q;

    for(i = 0; i < 4; i++) {
        q = (struct DVDCommandBlock *)&WaitingQueue[i].next;
        q->next = q;
        q->prev = q;
    }
}

int __DVDPushWaitingQueue(long prio, struct DVDCommandBlock * block) {
    int enabled = OSDisableInterrupts();
    struct DVDCommandBlock * q = (struct DVDCommandBlock *)&WaitingQueue[prio];

    q->prev->next = block;
    block->prev = q->prev;
    block->next = q;
    q->prev = block;
    OSRestoreInterrupts(enabled);
    return 1;
}

static struct DVDCommandBlock * PopWaitingQueuePrio(long prio) {
    struct DVDCommandBlock * tmp;
    int enabled;
    struct DVDCommandBlock * q;

    enabled = OSDisableInterrupts();
    q = (struct DVDCommandBlock *)&WaitingQueue[prio];
    ASSERTLINE(0x54, q->next != q);
    tmp = q->next;
    q->next = tmp->next;
    tmp->next->prev = q;
    OSRestoreInterrupts(enabled);
    tmp->next = 0;
    tmp->prev = 0;
    return tmp;
}

struct DVDCommandBlock * __DVDPopWaitingQueue(void) {
    unsigned long i;
    int enabled;
    struct DVDCommandBlock * q;

    enabled = OSDisableInterrupts();
    for(i = 0; i < 4; i++) {
        q = (struct DVDCommandBlock *)&WaitingQueue[i];
        if (q->next != q) {
            return PopWaitingQueuePrio(i);
        }
    }
    OSRestoreInterrupts(enabled);
    return NULL;
}

int __DVDCheckWaitingQueue(void) {
    unsigned long i;
    int enabled;
    struct DVDCommandBlock * q;

    enabled = OSDisableInterrupts();
    for(i = 0; i < 4; i++) {
        q = (struct DVDCommandBlock *)&WaitingQueue[i];
        if (q->next != q) {
            return 1;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

int __DVDDequeueWaitingQueue(struct DVDCommandBlock * block) {
    int enabled;
    struct DVDCommandBlock * prev;
    struct DVDCommandBlock * next;

    enabled = OSDisableInterrupts();
    prev = block->prev;
    next = block->next;
    if (prev == NULL || next == NULL) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    prev->next = next;
    next->prev = prev;
    OSRestoreInterrupts(enabled);
    return 1;
}

int __DVDIsBlockInWaitingQueue(struct DVDCommandBlock * block) {
    unsigned long i;
    struct DVDCommandBlock * start;
    struct DVDCommandBlock * q;

    for(i = 0; i < 4; i++) {
        start = (struct DVDCommandBlock *)&WaitingQueue[i];
        if (start->next == start) {
            continue;
        }
        for(q = start->next; q != start; q = q->next) {
            if (q == block) {
                return 1;
            }
        }
    }
    return 0;
}

static char * CommandNames[16] = {
    "",
    "READ",
    "SEEK",
    "CHANGE_DISK",
    "BSREAD",
    "READID",
    "INITSTREAM",
    "CANCELSTREAM",
    "STOP_STREAM_AT_END",
    "REQUEST_AUDIO_ERROR",
    "REQUEST_PLAY_ADDR",
    "REQUEST_START_ADDR",
    "REQUEST_LENGTH",
    "AUDIO_BUFFER_CONFIG",
    "INQUIRY",
    "BS_CHANGE_DISK",
};

void DVDDumpWaitingQueue(void) {
    unsigned long i;
    struct DVDCommandBlock * start;
    struct DVDCommandBlock * q;

    OSReport("==== DVD Waiting Queue Status ====\n");
    for(i = 0; i < 4; i++) {
        OSReport("< Queue #%d > ", i);
        start = (struct DVDCommandBlock *)&WaitingQueue[i];
        if (start->next == start) {
            OSReport("None\n");
        } else {
            OSReport("\n");
            for(q = start->next; q != start; q = q->next) {
                OSReport("0x%08x: Command: %s ", q, CommandNames[q->command]);
                if (q->command == 1) {
                    OSReport("Disk offset: %d, Length: %d, Addr: 0x%08x\n", q->offset, q->length, q->addr);
                } else {
                    OSReport("\n");
                }
            }
        }
    }
}
