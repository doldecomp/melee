#include "mnsnap.h"

#include <sysdolphin/baselib/gobj.h>

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

/// #fn_80253E1C

void fn_80253E5C(HSD_GObj* gobj, int arg1) {
    if (mnSnap_804A0A10[83] == 1) {
        HSD_GObj_JObjCallback(gobj, arg1);
    }
}

/// #mnSnap_80253E90

/// #fn_80253F08

/// #mnSnap_80253F6C

/// #mnSnap_80254014

/// #mnSnap_8025409C
