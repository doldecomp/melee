#include "mndiagram3.h"

#include "baselib/memory.h"
#include <sysdolphin/baselib/gobjplink.h>

extern f32 mnDiagram3_803EEC10[2];
f32 mn_8022ED6C(void*, f32*);

void fn_80246E04(void* gobj) {
    void* data;
    void* jobj;
    f32* table;

    data = *(void**)((u8*)gobj + 0x2C);
    table = mnDiagram3_803EEC10;
    jobj = *(void**)((u8*)data + 0x0C);
    if (mn_8022ED6C(jobj, table) >= table[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_80246F0C(void* arg0)
{
    HSD_Free(arg0);
}
