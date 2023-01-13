#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSInterrupt.h>

typedef struct _DVDQueue_sub {
    struct _DVDQueue_sub* unk0;
    struct _DVDQueue_sub* unk4;
} DVDQueue_sub;

static DVDQueue_sub WaitingQueue[4];

void __DVDClearWaitingQueue(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        DVDQueue_sub* ptr = &WaitingQueue[i];

        ptr->unk0 = ptr;
        ptr->unk4 = ptr;
    }
}

int __DVDPushWaitingQueue(int a, DVDQueue_sub* b)
{
    bool intrEnabled = OSDisableInterrupts();
    DVDQueue_sub* r5 = &WaitingQueue[a];

    r5->unk4->unk0 = b;
    b->unk4 = r5->unk4;
    b->unk0 = r5;
    r5->unk4 = b;
    OSRestoreInterrupts(intrEnabled);
    return 1;
}

DVDQueue_sub* __DVDPopWaitingQueue(void)
{
    bool intrEnabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 4; i++) {
        if (WaitingQueue[i].unk0 != &WaitingQueue[i]) {
            DVDQueue_sub* r5;
            DVDQueue_sub* r31;

            OSRestoreInterrupts(intrEnabled);
            intrEnabled = OSDisableInterrupts();
            r5 = &WaitingQueue[i];
            r31 = r5->unk0;
            r5->unk0 = r31->unk0;
            r31->unk0->unk4 = r5;
            OSRestoreInterrupts(intrEnabled);
            r31->unk0 = NULL;
            r31->unk4 = NULL;
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
        if (WaitingQueue[i].unk0 != &WaitingQueue[i]) {
            OSRestoreInterrupts(intrEnabled);
            return true;
        }
    }
    OSRestoreInterrupts(intrEnabled);
    return false;
}

bool __DVDDequeueWaitingQueue(DVDQueue_sub* a)
{
    bool intrEnabled = OSDisableInterrupts();
    DVDQueue_sub* r4 = a->unk4;
    DVDQueue_sub* r5 = a->unk0;

    if (r4 == NULL || r5 == NULL) {
        OSRestoreInterrupts(intrEnabled);
        return false;
    }
    r4->unk0 = r5;
    r5->unk4 = r4;
    OSRestoreInterrupts(intrEnabled);
    return true;
}
