#ifndef _METROTRK_DISPATCH_H
#define _METROTRK_DISPATCH_H

#include <platform.h>

#include "MetroTRK/dserror.h"
#include "MetroTRK/msgbuf.h"

/* 3276A8 */ DSError TRKInitializeDispatcher(void);
/* 3276BC */ DSError TRKDispatchMessage(MessageBuffer* buf);

#endif
