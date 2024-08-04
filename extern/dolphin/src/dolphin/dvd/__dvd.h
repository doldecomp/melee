#ifndef _DOLPHIN_DVD_INTERNAL_H_
#define _DOLPHIN_DVD_INTERNAL_H_

#include <dolphin/dvd.h>

// dvd.c
void __DVDAudioBufferConfig(struct DVDCommandBlock * block, unsigned long enable, unsigned long size, void (* callback)(long, struct DVDCommandBlock *));

// dvdfs.c
extern struct OSThreadQueue __DVDThreadQueue;
extern unsigned long __DVDLongFileNameFlag;

void __DVDFSInit();

// dvdlow.c
void __DVDInterruptHandler(short unused, struct OSContext * context);

// dvdqueue.c
void __DVDClearWaitingQueue();
int __DVDPushWaitingQueue(long prio, struct DVDCommandBlock * block);
struct DVDCommandBlock * __DVDPopWaitingQueue();
int __DVDCheckWaitingQueue();
int __DVDDequeueWaitingQueue(struct DVDCommandBlock * block);
int __DVDIsBlockInWaitingQueue(struct DVDCommandBlock * block);

// fstload.c
void __fstLoad();

#endif // _DOLPHIN_DVD_INTERNAL_H_
