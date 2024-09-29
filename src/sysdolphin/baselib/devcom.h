#ifndef SYSDOLPHIN_BASELIB_DEVCOM_H
#define SYSDOLPHIN_BASELIB_DEVCOM_H

#include <platform.h>

#include "baselib/forward.h"

#include "baselib/archive.h"

typedef struct HSD_DevCom HSD_DevCom;

struct HSD_DevCom {
    HSD_DevCom* next;
    int dcReq;
    int file;
    u32 src;
    u32 dest;
    u32 size;
    u16 type;
    u16 cancelflag;
    HSD_DevComCallback callback;
    void* args;
};

s32 HSD_DevComIsBusy(s32 idx);
void HSD_DevComUnlink(HSD_DevCom* dc, int link, HSD_DevCom* adc);
void HSD_DevComRequest(int file, unsigned long src, unsigned long dest,
                       unsigned long size, int type, int pri,
                       HSD_DevComCallback callback, void* args);

#endif
