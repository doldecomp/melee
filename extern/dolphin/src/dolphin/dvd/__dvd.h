#ifndef _DOLPHIN_DVD_INTERNAL_H_
#define _DOLPHIN_DVD_INTERNAL_H_

#include <dolphin/dvd.h>

// dvd.c
static void stateTimeout(void);
static void cbForStateError(unsigned long intType);
static void cbForUnrecoveredError(unsigned long);
static void cbForUnrecoveredErrorRetry(unsigned long);
void __DVDAudioBufferConfig(struct DVDCommandBlock* block,
                            unsigned long enable, unsigned long size,
                            void (*callback)(long, struct DVDCommandBlock*));

void __DVDFSInit();
void __DVDPrepareResetAsync(DVDCBCallback);

// dvdlow.c
void __DVDInitWA(void);
void __DVDInterruptHandler(short unused, struct OSContext* context);

// dvdqueue.c
void __DVDClearWaitingQueue();
int __DVDPushWaitingQueue(long prio, struct DVDCommandBlock* block);
struct DVDCommandBlock* __DVDPopWaitingQueue();
int __DVDCheckWaitingQueue();
int __DVDDequeueWaitingQueue(struct DVDCommandBlock* block);
int __DVDIsBlockInWaitingQueue(struct DVDCommandBlock* block);

// fstload.c
void __fstLoad();

#endif // _DOLPHIN_DVD_INTERNAL_H_
