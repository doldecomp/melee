#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <Runtime/platform.h>
#include <sysdolphin/baselib/archive.h>

typedef void (*HSD_DevComCallback)(int, int, int, bool cancelflag);

void HSD_DevComRequest(int, int, HSD_Archive*, int, int, int,
                       HSD_DevComCallback, int);

#endif
