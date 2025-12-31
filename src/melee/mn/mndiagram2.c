#include "mndiagram2.h"

#include <sysdolphin/baselib/sislib.h>

void HSD_Free(void*);

void fn_80245028(void* arg0) {
    if (*(void**)((u8*)arg0 + 0xC4) != NULL) {
        HSD_SisLib_803A5CC4(*(void**)((u8*)arg0 + 0xC4));
    }
    HSD_Free(arg0);
}