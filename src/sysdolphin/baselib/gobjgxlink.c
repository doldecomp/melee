#include "gobjgxlink.h"

#include "debug.h"
#include "gobj.h"

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
        gobj->next_gx = HSD_GObjGXLinkHead[link];
        HSD_GObjGXLinkHead[link] = gobj;
    }

    if (gobj->next_gx != NULL) {
        gobj->next_gx->prev_gx = gobj;
    } else {
        HSD_GObj_804D7820[gobj->gx_link] = gobj;
    }
}

static inline void GObj_GXInsertFromTail(HSD_GObj* gobj)
{
    HSD_GObj* i = HSD_GObj_804D7820[gobj->gx_link];
    while (i != NULL && i->render_priority > gobj->render_priority) {
        i = i->prev_gx;
    }
    GObj_GXReorder(gobj, i);
}

static inline void GObj_GXInsertFromHead(HSD_GObj* gobj)
{
    HSD_GObj* i = HSD_GObjGXLinkHead[gobj->gx_link];
    while (i != NULL && i->render_priority < gobj->render_priority) {
        i = i->next_gx;
    }
    GObj_GXReorder(gobj,
                   i != NULL ? i->prev_gx : HSD_GObj_804D7820[gobj->gx_link]);
}

static inline void GObj_GXInsert(HSD_GObj* gobj, s32 where, HSD_GObj* position)
{
    switch (where) {
    case 0:
        GObj_GXInsertFromTail(gobj);
        break;
    case 1:
        GObj_GXInsertFromHead(gobj);
        break;
    case 3:
        GObj_GXReorder(gobj, position->prev_gx);
        break;
    }
}

void GObj_SetupGXLink(HSD_GObj* gobj, GObj_RenderFunc render_cb, u8 gx_link,
                      u32 priority)
{
    HSD_ASSERT(167, gx_link <= HSD_GObjLibInitData.gx_link_max);
    gobj->render_cb = render_cb;
    gobj->gx_link = gx_link;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 0, NULL);
}

void GObj_SetupGXLinkMax(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                         u32 priority)
{
    u8 max_link = HSD_GObjLibInitData.gx_link_max;

    gobj->render_cb = render_cb;
    gobj->gx_link = max_link + 1;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 0, NULL);
}

void GObj_SetupGXLinkMaxSorted(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                               u32 priority)
{
    u8 max_link = HSD_GObjLibInitData.gx_link_max;

    gobj->render_cb = render_cb;
    gobj->gx_link = max_link + 1;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 1, NULL);
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
        HSD_GObjGXLinkHead[gobj->gx_link] = gobj->next_gx;
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

void HSD_GObjGXLink_80390908(HSD_GObj* gobj, u8 gx_link, u8 priority)
{
    HSD_ASSERT(535, gx_link <= HSD_GObjLibInitData.gx_link_max);
    HSD_GObjGXLink_8039084C(gobj);
    gobj->gx_link = gx_link;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 1, NULL);
}

void HSD_GObjGXLink_803909D8(HSD_GObj* gobj, HSD_GObj* other)
{
    u8 link;
    u8 prio;

    prio = other->render_priority;
    link = other->gx_link;

    HSD_GObjGXLink_8039084C(gobj);
    gobj->gx_link = link;
    gobj->render_priority = prio;
    GObj_GXInsert(gobj, 3, other);
}
