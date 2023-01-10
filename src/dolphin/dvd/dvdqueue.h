#ifndef DOLPHIN_DVD_DVDQUEUE_H
#define DOLPHIN_DVD_DVDQUEUE_H

#include <dolphin/dvd/dvd.h>

void __DVDClearWaitingQueue(void);
BOOL __DVDCheckWaitingQueue(void);
int __DVDPushWaitingQueue(int a, DVDCommandBlock* b);
BOOL __DVDDequeueWaitingQueue(DVDCommandBlock* a);

#endif
