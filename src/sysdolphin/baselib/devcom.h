#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <platform.h>
#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/archive.h>

void HSD_DevComRequest(int, int, HSD_Archive*, int, int, int,
                       HSD_DevComCallback, int);

#endif
