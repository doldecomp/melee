#include <dolphin/dvd/dvdqueue.h>

#include <dolphin/dvd/dvd.h>
#include <dolphin/dvd/forward.h>
#include <dolphin/os/OSInterrupt.h>

typedef struct DVDNode {
    /*0x00*/ DVDCommandBlock* next;
    /*0x04*/ DVDCommandBlock* prev;
} DVDNode;

static DVDNode WaitingQueue[4];

static inline DVDCommandBlock* getWaitingBlock(int i)
{
    return (DVDCommandBlock*) &WaitingQueue[i];
}

void __DVDClearWaitingQueue(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        DVDCommandBlock* ptr = (DVDCommandBlock*) &WaitingQueue[i];

        ptr->next = (DVDCommandBlock*) ptr;
        ptr->prev = (DVDCommandBlock*) ptr;
    }
}

int __DVDPushWaitingQueue(int a, DVDCommandBlock* b)
{
    bool intrEnabled = OSDisableInterrupts();
    DVDCommandBlock* r5 = (DVDCommandBlock*) &WaitingQueue[a];

    r5->prev->next = b;
    b->prev = r5->prev;
    b->next = r5;
    r5->prev = b;
    OSRestoreInterrupts(intrEnabled);
    return 1;
}

DVDCommandBlock* __DVDPopWaitingQueue(void)
{
    bool intrEnabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 4; i++) {
        if (WaitingQueue[i].next != (DVDCommandBlock*) &WaitingQueue[i]) {
            DVDCommandBlock* r5;
            DVDCommandBlock* r31;

            OSRestoreInterrupts(intrEnabled);
            intrEnabled = OSDisableInterrupts();
            r5 = (DVDCommandBlock*) &WaitingQueue[i];
            r31 = r5->next;
            r5->next = r31->next;
            r31->next->prev = r5;
            OSRestoreInterrupts(intrEnabled);
            r31->next = NULL;
            r31->prev = NULL;
            return r31;
        }
    }
    OSRestoreInterrupts(intrEnabled);
    return NULL;
}

bool __DVDCheckWaitingQueue(void)
{
    bool intrEnabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 4; i++) {
        if (WaitingQueue[i].next != (DVDCommandBlock*) &WaitingQueue[i]) {
            OSRestoreInterrupts(intrEnabled);
            return true;
        }
    }
    OSRestoreInterrupts(intrEnabled);
    return false;
}

bool __DVDDequeueWaitingQueue(DVDCommandBlock* a)
{
    bool intrEnabled = OSDisableInterrupts();
    DVDCommandBlock* r4 = a->prev;
    DVDCommandBlock* r5 = a->next;

    if (r4 == NULL || r5 == NULL) {
        OSRestoreInterrupts(intrEnabled);
        return false;
    }
    r4->next = r5;
    r5->prev = r4;
    OSRestoreInterrupts(intrEnabled);
    return true;
}
