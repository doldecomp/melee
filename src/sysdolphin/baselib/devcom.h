#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <platform.h>
#include "baselib/forward.h"

#include "baselib/archive.h"

s32 HSD_DevComIsBusy(s32 idx);
void HSD_DevComRequest(int file, unsigned long src, unsigned long dest,
                       unsigned long size, int type, int pri,
                       HSD_DevComCallback callback, void* args);

#endif
