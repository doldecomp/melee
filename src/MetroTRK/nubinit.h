#ifndef GALE01_326AD8
#define GALE01_326AD8

#include <MetroTRK/dserror.h>
#include <Runtime/platform.h>

DSError TRKInitializeNub(void);
DSError TRKTerminateNub(void);
void TRKNubWelcome(void);
bool TRKInitializeEndian(void);

extern bool gTRKBigEndian;

#endif
