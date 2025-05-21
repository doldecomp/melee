#ifndef _METROTRK_MUTEX_TRK_H
#define _METROTRK_MUTEX_TRK_H

#include <platform.h>

#include "MetroTRK/dserror.h"

typedef unsigned int DSMutex;

DSError TRKReleaseMutex(void* p1);
DSError TRKAcquireMutex(void* p1);
DSError TRKInitializeMutex(void* p1);

#endif