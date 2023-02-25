#ifndef DOLPHIN_DVD_DVDQUEUE_H
#define DOLPHIN_DVD_DVDQUEUE_H

#include <dolphin/dvd/forward.h>
#include <stdbool.h>

void __DVDClearWaitingQueue(void);
bool __DVDCheckWaitingQueue(void);
int __DVDPushWaitingQueue(int a, DVDCommandBlock* b);
bool __DVDDequeueWaitingQueue(DVDCommandBlock* a);
DVDCommandBlock* __DVDPopWaitingQueue(void);

#endif
