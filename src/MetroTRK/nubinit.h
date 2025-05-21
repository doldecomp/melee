#ifndef GALE01_326AD8
#define GALE01_326AD8

#include <platform.h>

#include "MetroTRK/dserror.h"

/* 326AD8 */ DSError TRKInitializeNub(void);
/* 326BAC */ DSError TRKTerminateNub(void);
/* 326BD0 */ void TRKNubWelcome(void);
/* 326BF8 */ bool TRKInitializeEndian(void);

extern bool gTRKBigEndian;

#endif
