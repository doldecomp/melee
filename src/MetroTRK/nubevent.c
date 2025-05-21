#include "nubevent.h"

#include "MetroTRK/mem_TRK.h"


typedef struct EventQueue {
    u8 pad[4];
    int fCount;
    int fFirst;
    NubEvent fEventList[2];
    NubEventID fEventID;
} EventQueue;

EventQueue gTRKEventQueue;

DSError TRKInitializeEventQueue(void)
{
    TRKInitializeMutex(&gTRKEventQueue);
    TRKAcquireMutex(&gTRKEventQueue);
    gTRKEventQueue.fCount = 0;
    gTRKEventQueue.fFirst = 0;
    gTRKEventQueue.fEventID = 0x100;
    TRKReleaseMutex(&gTRKEventQueue);
    return kNoError;
}

void* TRKCopyEvent(void* src, void* dst)
{
    return TRK_memcpy(src, dst, sizeof(NubEvent));
}

bool TRKGetNextEvent(NubEvent* ev)
{
    bool ret = false;

    TRKAcquireMutex(&gTRKEventQueue);

    if (gTRKEventQueue.fCount > 0) {
        TRKCopyEvent(ev, &gTRKEventQueue.fEventList[gTRKEventQueue.fFirst]);
        gTRKEventQueue.fCount--;
        gTRKEventQueue.fFirst++;

        if (gTRKEventQueue.fFirst == 2) {
            gTRKEventQueue.fFirst = 0;
        }

        ret = true;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return ret;
}

DSError TRKPostEvent(NubEvent* ev)
{
    DSError ret = kNoError;
    int evID;

    TRKAcquireMutex(&gTRKEventQueue);

    if (gTRKEventQueue.fCount == 2) {
        ret = kEventQueueFull;
    } else {
        evID = (gTRKEventQueue.fFirst + gTRKEventQueue.fCount) % 2;
        TRKCopyEvent(&gTRKEventQueue.fEventList[evID], ev);
        gTRKEventQueue.fEventList[evID].fID = gTRKEventQueue.fEventID;
        gTRKEventQueue.fEventID++;

        if (gTRKEventQueue.fEventID < 256) {
            gTRKEventQueue.fEventID = 256;
        }

        gTRKEventQueue.fCount++;
    }

    TRKReleaseMutex(&gTRKEventQueue);
    return ret;
}

void TRKConstructEvent(NubEvent* event, int eventType)
{
    event->fType = eventType;
    event->fID = 0;
    event->fMessageBufferID = -1;
}

void TRKDestructEvent(NubEvent* event)
{
    TRKReleaseBuffer(event->fMessageBufferID);
}