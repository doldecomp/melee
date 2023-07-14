#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <platform.h>
#include <baselib/forward.h>

#include <baselib/archive.h>

s32 HSD_DevComIsBusy(s32 idx);
void HSD_DevComRequest(int, int, HSD_Archive*, int, int, int,
                       HSD_DevComCallback, int);

#endif
