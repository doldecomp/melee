#include "mnsnap.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

extern s32 mnSnap_804A0A10[84];

void fn_80253DB4(HSD_GObj* gobj, int arg1) {
    if (mnSnap_804A0A10[71] >= 4) {
        HSD_GObj_JObjCallback(gobj, arg1);
    }
}
void fn_80253DE8(HSD_GObj* gobj, int arg1) {
    if (mnSnap_804A0A10[71] == 2) {
        HSD_GObj_JObjCallback(gobj, arg1);
    }
}

void fn_80253E1C(HSD_GObj* gobj, int arg1) {
    s32 val = mnSnap_804A0A10[71];
    if (val == 6 || (u32)(val - 10) <= 1) {
        HSD_GObj_JObjCallback(gobj, arg1);
    }
}

void fn_80253E5C(HSD_GObj* gobj, int arg1) {
    if (mnSnap_804A0A10[83] == 1) {
        HSD_GObj_JObjCallback(gobj, arg1);
    }
}

/// #mnSnap_80253E90

/// #fn_80253F08

/// #mnSnap_80253F6C

extern f32 mnSnap_804DC2C0;

void mnSnap_80254014(void) {
    u8* base = (u8*)mnSnap_804A0A10;
    HSD_JObj** ptr;
    s32 i;

    ptr = (HSD_JObj**)(base + 0xAC);
    HSD_JObjReqAnimAll(*ptr, mnSnap_804DC2C0);
    HSD_JObjAnimAll(*ptr);
    i = 0;
    ptr = (HSD_JObj**)(base + i * 4);
    do {
        HSD_JObjClearFlagsAll(*(HSD_JObj**)(base + 0xB8 + i * 4), 0x10);
        i++;
        ptr++;
    } while (i < 5);
    HSD_JObjSetFlagsAll(*(HSD_JObj**)(base + 0x8C), 0x10);
}

/// #mnSnap_8025409C
