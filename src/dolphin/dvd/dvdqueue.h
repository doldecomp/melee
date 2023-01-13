#ifndef DOLPHIN_DVD_DVDQUEUE_H
#define DOLPHIN_DVD_DVDQUEUE_H

#include <dolphin/dvd/dvd.h>

void __DVDClearWaitingQueue(void);
bool __DVDCheckWaitingQueue(void);
int __DVDPushWaitingQueue(int a, DVDCommandBlock* b);
bool __DVDDequeueWaitingQueue(DVDCommandBlock* a);

#endif
