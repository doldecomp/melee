#ifndef DOLPHIN_DVD_DVDLOW_H
#define DOLPHIN_DVD_DVDLOW_H

#include <platform.h>

#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>

void __DVDInitWA(void);
void __DVDInterruptHandler(__OSInterrupt, OSContext*);
void DVDLowRead(void*, u32, u32, DVDLowCallback);
void DVDLowStopMotor(DVDLowCallback);
void DVDLowRequestError(DVDLowCallback);
void DVDLowSeek(u32, DVDLowCallback);
void DVDLowAudioBufferConfig(u32, u32, DVDLowCallback);
void DVDLowReadDiskID(DVDBuffer*, DVDLowCallback);
void DVDLowRequestAudioStatus(u32, DVDLowCallback);
void DVDLowAudioStream(u32, u32, u32, DVDLowCallback);
void DVDLowInquiry(void*, DVDLowCallback);
void DVDLowWaitCoverClose(DVDLowCallback);
void DVDLowReset(void);
void DVDLowBreak(void);

#endif
