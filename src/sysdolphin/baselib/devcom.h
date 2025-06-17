#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h"
#include "baselib/archive.h"

#include <dolphin/ar.h>

struct HSD_DevCom {
    HSD_DevCom* next;
    int dcReq;
    int file;
    u32 src;
    u32 dest;
    size_t size;
    u16 type;
    u16 cancelflag;
    HSD_DevComCallback callback;
    void* args;
};

bool HSD_DevComIsBusy(int idx);
void HSD_DevComUnlink(HSD_DevCom*);
void HSD_DevComStdCallback(ARQRequest*);
void HSD_DevComARAMCallback(ARQRequest*);
UNK_RET HSD_DevComARAMWakeUp(UNK_PARAMS);
UNK_RET HSD_DevComDVDStdCallback(UNK_PARAMS);
UNK_RET HSD_DevComDVDARAMEndCallback(UNK_PARAMS);
UNK_RET HSD_DevComDVDMemCallback(UNK_PARAMS);
UNK_RET HSD_DevComDVDCallback(UNK_PARAMS);
UNK_RET HSD_DevComDVDWakeUp(UNK_PARAMS);
int HSD_DevComRequest(int file, u32 src, u32 dest, size_t size, int type,
                      int pri, HSD_DevComCallback callback, void* args);
UNK_RET HSD_DevComCancelEx(UNK_PARAMS);

#endif
