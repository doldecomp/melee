#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSInterrupt.h>

static DVDNode WaitingQueue[4];

void __DVDClearWaitingQueue(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        DVDNode* ptr = &WaitingQueue[i];

        ptr->next = ptr;
        ptr->prev = ptr;
    }
}

int __DVDPushWaitingQueue(int a, DVDNode* b)
{
    bool intrEnabled = OSDisableInterrupts();
    DVDNode* r5 = &WaitingQueue[a];

    r5->prev->next = b;
    b->prev = r5->prev;
    b->next = r5;
    r5->prev = b;
    OSRestoreInterrupts(intrEnabled);
    return 1;
}

DVDNode* __DVDPopWaitingQueue(void)
{
    bool intrEnabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 4; i++) {
        if (WaitingQueue[i].next != &WaitingQueue[i]) {
            DVDNode* r5;
            DVDNode* r31;

            OSRestoreInterrupts(intrEnabled);
            intrEnabled = OSDisableInterrupts();
            r5 = &WaitingQueue[i];
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
        if (WaitingQueue[i].next != &WaitingQueue[i]) {
            OSRestoreInterrupts(intrEnabled);
            return true;
        }
    }
    OSRestoreInterrupts(intrEnabled);
    return false;
}

bool __DVDDequeueWaitingQueue(DVDNode* a)
{
    bool intrEnabled = OSDisableInterrupts();
    DVDNode* r4 = a->prev;
    DVDNode* r5 = a->next;

    if (r4 == NULL || r5 == NULL) {
        OSRestoreInterrupts(intrEnabled);
        return false;
    }
    r4->next = r5;
    r5->prev = r4;
    OSRestoreInterrupts(intrEnabled);
    return true;
}
