#include "mnsnap.h"

#include <sysdolphin/baselib/gobj.h>

extern s32 mnSnap_804A0A10[72];

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
