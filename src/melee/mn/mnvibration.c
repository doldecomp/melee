#include "mnvibration.h"

#include "mnmain.h"

#include <sysdolphin/baselib/gobjplink.h>

extern void* mnVibration_804D6C28;
extern f32 mnVibration_803EECEC[2];

f32 mn_8022ED6C(void*, f32*);

void* mnVibration_802474C4(s32 arg0) {
    void* node = *(void**)((u8*)*(void**)((u8*)mnVibration_804D6C28 + 0x2C) + 0x50);
    if (node == NULL) {
        node = NULL;
    } else {
        node = *(void**)((u8*)node + 0x10);
    }
    for (; arg0 > 0; arg0--) {
        if (node == NULL) {
            node = NULL;
        } else {
            node = *(void**)((u8*)node + 0x8);
        }
    }
    return node;
}
/// #fn_80247510

void fn_80248084(void* gobj) {
    if (mn_804A04F0.x0 != 0x13) {
        HSD_GObjPLink_80390228(gobj);
    }
}

/// #mnVibration_802480B4

/// #mnVibration_8024829C

/// #mnVibration_80248444

/// #mnVibration_80248644

void fn_80248748(HSD_GObj* gobj) {
    f32* table = mnVibration_803EECEC;
    void* data = *(void**)((u8*)gobj + 0x2C);
    void* jobj = *(void**)((u8*)data + 0x10);
    f32 result = mn_8022ED6C(jobj, table);
    if (result >= table[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}
/// #fn_802487A8

/// #fn_80248A78

/// #mnVibration_80248ED4

/// #mnVibration_80249174
