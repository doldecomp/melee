#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/forward.h>

bool HSD_DevComIsBusy(int idx);
void HSD_DevComARAMWakeUp(void);
void HSD_DevComDVDWakeUp(void);
int HSD_DevComRequest(int file, uintptr_t src, uintptr_t dest, size_t size, int type,
                      int pri, HSD_DevComCallback callback, void* args);
int HSD_DevComCancelEx(int dcReq, u32 flags, HSD_DevComCallback, void* args);

#endif
