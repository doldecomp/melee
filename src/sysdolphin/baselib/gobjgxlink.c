#include "gobjgxlink.h"

#include "debug.h"
#include "gobj.h"

#pragma push
#pragma dont_inline on
void GObj_GXReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj)
{
    u32 link = gobj->gx_link;

    gobj->prev_gx = hiprio_gobj;
    if (hiprio_gobj != NULL) {
        // If there is a higher priority GObj, make gobj the next in GX order
        gobj->next_gx = hiprio_gobj->next_gx;
        hiprio_gobj->next_gx = gobj;
    } else {
        // If there's not a higher priority GObj of this type, this gobj
        // becomes the highest priority
        gobj->next_gx = HSD_GObj_804D7824[link];
        HSD_GObj_804D7824[link] = gobj;
    }

    if (gobj->next_gx != NULL) {
        gobj->next_gx->prev_gx = gobj;
    } else {
        HSD_GObj_804D7820[gobj->gx_link] = gobj;
    }
}
#pragma pop

void GObj_SetupGXLink(HSD_GObj* gobj, GObj_RenderFunc render_cb, u8 gx_link,
                      u32 priority)
{
    HSD_GObj* i;
    HSD_GObj* prev;

    HSD_ASSERT(167, gx_link <= HSD_GObjLibInitData.gx_link_max);
    gobj->render_cb = render_cb;
    gobj->gx_link = gx_link;
    gobj->render_priority = priority;

    for (i = HSD_GObj_804D7820[gobj->gx_link];
         i != NULL && (i->render_priority > gobj->render_priority); i = prev)
    {
        prev = i->prev_gx;
    }
    GObj_GXReorder(gobj, i);
}

void GObj_SetupGXLinkMax(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                         u32 priority)
{
    HSD_GObj* i;
    u8 max_link = HSD_GObjLibInitData.gx_link_max;

    gobj->render_cb = render_cb;
    gobj->gx_link = max_link + 1;
    gobj->render_priority = priority;

    i = HSD_GObj_804D7820[gobj->gx_link];
    while (i != NULL && i->render_priority > gobj->render_priority) {
        i = i->prev_gx;
    }
    GObj_GXReorder(gobj, i);
}

inline HSD_GObj* GObj_GXFindPrioPosition(HSD_GObj* gobj)
{
    HSD_GObj* i;

    i = HSD_GObj_804D7824[gobj->gx_link];
    while (i != NULL && i->render_priority < gobj->render_priority) {
        i = i->next_gx;
    }

    return i;
}

void GObj_SetupGXLinkMaxSorted(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                               u32 priority)
{
    HSD_GObj* i;
    u8 max_link = HSD_GObjLibInitData.gx_link_max;

    gobj->render_cb = render_cb;
    gobj->gx_link = max_link + 1;
    gobj->render_priority = priority;

    i = GObj_GXFindPrioPosition(gobj);

    if (i != NULL) {
        i = i->prev_gx;
    } else {
        i = HSD_GObj_804D7820[gobj->gx_link];
    }
    GObj_GXReorder(gobj, i);
}

void HSD_GObjGXLink_8039084C(HSD_GObj* gobj)
{
    HSD_GObj* prev;
    HSD_GObj* next;

    HSD_ASSERT(415, gobj->gx_link != HSD_GOBJ_GXLINK_NONE);

    prev = gobj->prev_gx;
    if (prev != NULL) {
        prev->next_gx = gobj->next_gx;
    } else {
        HSD_GObj_804D7824[gobj->gx_link] = gobj->next_gx;
    }
    next = gobj->next_gx;
    if (next != NULL) {
        next->prev_gx = gobj->prev_gx;
    } else {
        HSD_GObj_804D7820[gobj->gx_link] = gobj->prev_gx;
    }
    gobj->gx_link = HSD_GOBJ_GXLINK_NONE;
    gobj->render_priority = 0;
    gobj->prev_gx = NULL;
    gobj->next_gx = NULL;
}

inline HSD_GObj* get_by_prio(HSD_GObj* gobj)
{
    HSD_GObj* cur = HSD_GObj_804D7824[gobj->gx_link];
    while (cur != NULL && cur->render_priority < gobj->render_priority) {
        cur = cur->next_gx;
    }
    return cur;
}

void HSD_GObjGXLink_80390908(HSD_GObj* gobj, u8 gx_link, u8 priority)
{
    HSD_GObj* cur;
    HSD_ASSERT(535, gx_link <= HSD_GObjLibInitData.gx_link_max);
    HSD_GObjGXLink_8039084C(gobj);
    gobj->gx_link = gx_link;
    gobj->render_priority = priority;
    cur = get_by_prio(gobj);
    GObj_GXReorder(gobj, cur != NULL ? cur->prev_gx
                                     : HSD_GObj_804D7820[gobj->gx_link]);
}

void HSD_GObjGXLink_803909D8(HSD_GObj* gobj, HSD_GObj* other)
{
    u8 _[12];

    u8 link;
    u8 prio;

    prio = other->render_priority;
    link = other->gx_link;
    HSD_GObjGXLink_8039084C(gobj);
    gobj->gx_link = link;
    gobj->render_priority = prio;
    GObj_GXReorder(gobj, other->prev_gx);
}
