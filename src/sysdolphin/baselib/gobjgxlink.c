#include "sysdolphin/baselib/gobjgxlink.h"

extern HSD_GObj** lbl_804D7820;
extern HSD_GObj** lbl_804D7824;

void GObj_GXReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj)
{
    u32 link = gobj->gx_link;

    gobj->prev_gx = hiprio_gobj;
    if (hiprio_gobj != NULL) { //If there is a higher priority GObj, make gobj the next in GX order
        gobj->next_gx = hiprio_gobj->next_gx;
        hiprio_gobj->next_gx = gobj;
    } else { //If there's not a higher priority GObj of this type, this gobj becomes the highest priority
        gobj->next_gx = lbl_804D7824[link];
        lbl_804D7824[link] = gobj;
    }
    
    if (gobj->next_gx != NULL) {
        gobj->next_gx->prev_gx = gobj;
    } else {
        lbl_804D7820[gobj->gx_link] = gobj;
    }
}
