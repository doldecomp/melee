#ifndef SYSDOLPHIN_BASELIB_GOBJPROC_H
#define SYSDOLPHIN_BASELIB_GOBJPROC_H

#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef void (*HSD_GObjEvent)(HSD_GObj* gobj);

struct _HSD_GObjProc* func_8038FD54(HSD_GObj*, HSD_GObjEvent, u8);

#endif
