#ifndef DOLPHIN_DVD_DVDLOW_H
#define DOLPHIN_DVD_DVDLOW_H

#include <platform.h>

#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>

void __DVDInitWA(void);
void __DVDInterruptHandler(__OSInterrupt, OSContext*);
bool DVDLowRead(void*, u32, u32, DVDLowCallback);
bool DVDLowStopMotor(DVDLowCallback callback);
bool DVDLowRequestError(DVDLowCallback callback);
bool DVDLowSeek(u32 offset, DVDLowCallback callback);
bool DVDLowAudioBufferConfig(bool enable, u32 size, DVDLowCallback callback);
bool DVDLowReadDiskID(DVDDiskID* diskID, DVDLowCallback callback);
bool DVDLowRequestAudioStatus(u32 subcmd, DVDLowCallback callback);
bool DVDLowAudioStream(u32 subcmd, u32 length, u32 offset,
                       DVDLowCallback callback);
bool DVDLowInquiry(DVDDriveInfo* info, DVDLowCallback callback);
bool DVDLowWaitCoverClose(DVDLowCallback callback);
void DVDLowReset(void);
bool DVDLowBreak(void);

#endif
