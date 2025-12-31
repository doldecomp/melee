#include "mndiagram2.h"

#include "mnmain.h"
#include "types.h"

#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/sislib.h>

void HSD_Free(void*);

extern AnimLoopSettings mnDiagram2_803EEB60;

void fn_80244D20(HSD_GObj* gobj) {
    void* data;
    AnimLoopSettings* table;
    HSD_JObj* jobj;
    int dummy;

    data = *(void**)((u8*)gobj + 0x2C);
    table = &mnDiagram2_803EEB60;
    jobj = *(HSD_JObj**)((u8*)data + 0x0C);
    dummy = 0;
    if (mn_8022ED6C(jobj, table) >= table->end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}
/// #fn_80245028

void fn_80245028(void* arg0) {
    if (*(void**)((u8*)arg0 + 0xC4) != NULL) {
        HSD_SisLib_803A5CC4(*(void**)((u8*)arg0 + 0xC4));
    }
    HSD_Free(arg0);
}