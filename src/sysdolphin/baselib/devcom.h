#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <baselib/forward.h>

#include <platform.h>
#include <baselib/archive.h>

void HSD_DevComRequest(int, int, HSD_Archive*, int, int, int,
                       HSD_DevComCallback, int);

#endif
