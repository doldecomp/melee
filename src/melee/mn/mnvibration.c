#include "mnvibration.h"

#include "mnmain.h"

#include <sysdolphin/baselib/gobjplink.h>

/// GObj wrapper for data access at offset 0x2C
typedef struct VibGObj {
    char x0[0x2C];
    void* x2C;
} VibGObj;

/// Data with jobj at offset 0x10
typedef struct VibJObjData {
    char x0[0x10];
    void* x10;
} VibJObjData;

void* mnVibration_802474C4(s32 arg0)
{
    VibNode* node;
    if (mnVibration_804D6C28->x2C == NULL) {
        node = NULL;
    } else {
        node = mnVibration_804D6C28->x2C->x50;
    }
    if (node == NULL) {
        node = NULL;
    } else {
        node = node->x10;
    }
    for (; arg0 > 0; arg0--) {
        if (node == NULL) {
            node = NULL;
        } else {
            node = node->x8;
        }
    }
    return node;
}
/// #fn_80247510

void fn_80248084(void* gobj)
{
    if (mn_804A04F0.cur_menu != 0x13) {
        HSD_GObjPLink_80390228(gobj);
    }
}

/// #mnVibration_802480B4

/// #mnVibration_8024829C

/// #mnVibration_80248444

/// #mnVibration_80248644

void fn_80248748(HSD_GObj* gobj)
{
    f32* table = mnVibration_803EECEC;
    VibJObjData* data = ((VibGObj*) gobj)->x2C;
    void* jobj = data->x10;
    f32 result = mn_8022ED6C(jobj, (AnimLoopSettings*) table);
    if (result >= table[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}
/// #fn_802487A8

/// #fn_80248A78

/// #mnVibration_80248ED4

/// #mnVibration_80249174
