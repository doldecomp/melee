#include "sysdolphin/baselib/gobjgxlink.h"

extern HSD_GObj** lbl_804D7820;
extern HSD_GObj** lbl_804D7824;

extern HSD_GObjLibInitData lbl_804CE380;

extern char lbl_804084F0[13]; //"gobjgxlink.c"
extern char lbl_80408500[43]; //"gx_link <= HSD_GObjLibInitData.gx_link_max"

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

void GObj_SetupGXLink(HSD_GObj* gobj, void (*render_cb)(HSD_GObj*, s32), u8 gx_link, u32 priority)
{
    HSD_GObj* i;
    HSD_GObj* prev;

    if (gx_link > lbl_804CE380.gx_link_max) {
        __assert(lbl_804084F0, 167, lbl_80408500);
    }
    gobj->render_cb = render_cb;
    gobj->gx_link = gx_link;
    gobj->render_priority = priority;

    for (i = lbl_804D7820[gobj->gx_link]; i != NULL && (i->render_priority > gobj->render_priority); i = prev) 
    {
        prev = i->prev_gx;
    }
    GObj_GXReorder(gobj, i);
}
