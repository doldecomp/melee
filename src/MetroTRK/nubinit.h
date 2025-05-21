#ifndef GALE01_326AD8
#define GALE01_326AD8

#include <platform.h>

#include "MetroTRK/dserror.h"

DSError TRKInitializeNub(void);
DSError TRKTerminateNub(void);
void TRKNubWelcome(void);
bool TRKInitializeEndian(void);

extern bool gTRKBigEndian;

#endif
