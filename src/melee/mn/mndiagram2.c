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

extern s32 HSD_GObj_804D783C;

HSD_GObj* GObj_Create(u16, u8, u8);
void* HSD_GObjProc_8038FD54(HSD_GObj*, void*, s32);
void mnDiagram2_80245178(s32);
void fn_80243D40(HSD_GObj*);

void mnDiagram2_802453B0(void) {
    MenuFlow* data = &mn_804A04F0;
    HSD_GObj* gobj;

    data->x10 = 1;
    data->hovered_selection = 0;
    mnDiagram2_80245178(0);
    gobj = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_80243D40, 0);
    {
        u32 val = HSD_GObj_804D783C;
        u8* ptr = (u8*)gobj + 0xD;
        *ptr = (*ptr & ~0x30) | ((val & 3) << 4);
    }
}