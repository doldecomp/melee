#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>

void GObj_PReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj)
{
    u8 link = gobj->p_link;
    gobj->prev = hiprio_gobj;
    if (hiprio_gobj != NULL) {
        gobj->next = hiprio_gobj->next;
        hiprio_gobj->next = gobj;
    } else {
        gobj->next = ((HSD_GObj**) HSD_GObj_Entities)[link];
        ((HSD_GObj**) HSD_GObj_Entities)[link] = gobj;
    }
    if (gobj->next != NULL) {
        gobj->next->prev = gobj;
    } else {
        plinklow_gobjs[link] = gobj;
    }
}

extern HSD_ObjAllocData gobj_alloc_data;

inline HSD_GObj* gobj_allocate(void)
{
    return HSD_ObjAlloc(&gobj_alloc_data);
}

inline void gobj_first_lower_prio(HSD_GObj* gobj)
{
    HSD_GObj* var_r4 = plinklow_gobjs[gobj->p_link];
    while (var_r4 != NULL && var_r4->p_priority > gobj->p_priority) {
        var_r4 = var_r4->prev;
    }
    GObj_PReorder(gobj, var_r4);
}

inline void gobj_first_higher_prio(HSD_GObj* gobj)
{
    HSD_GObj* var_r4 = ((HSD_GObj**) HSD_GObj_Entities)[gobj->p_link];
    while (var_r4 != NULL && var_r4->p_priority < gobj->p_priority) {
        var_r4 = var_r4->next;
    }
    GObj_PReorder(gobj, var_r4 != NULL ? var_r4->prev
                                       : plinklow_gobjs[gobj->p_link]);
}

extern char lbl_804084B8[];
extern char lbl_804084C4[];
HSD_GObj* CreateGObj(s32 where, u16 classifier, u8 p_link, u8 priority,
                     HSD_GObj* position)
{
    HSD_GObj* gobj;

    HSD_ASSERT(0xA8, p_link <= HSD_GObjLibInitData.p_link_max);
    if ((gobj = gobj_allocate()) == NULL) {
        return NULL;
    }
    gobj->classifier = classifier;
    gobj->p_link = p_link;
    gobj->gx_link = HSD_GOBJ_GXLINK_NONE;
    gobj->p_priority = priority;
    gobj->render_priority = 0;
    gobj->obj_kind = HSD_GOBJ_OBJ_NONE;
    gobj->user_data_kind = 0xFF;
    gobj->prev_gx = NULL;
    gobj->next_gx = NULL;
    gobj->proc = NULL;
    gobj->render_cb = NULL;
    gobj->gxlink_prios = 0;
    gobj->hsd_obj = NULL;
    gobj->user_data = NULL;
    gobj->user_data_remove_func = NULL;
    switch (where) {
    case 0:
        gobj_first_lower_prio(gobj);
        break;
    case 1:
        gobj_first_higher_prio(gobj);
        break;
    case 2: // insert after position
        GObj_PReorder(gobj, position);
        break;
    case 3: // insert before position
        GObj_PReorder(gobj, position->prev);
        break;
    }
    return gobj;
}

HSD_GObj* GObj_Create(u16 classifier, u8 p_link, u8 priority)
{
    return CreateGObj(0, classifier, p_link, priority, NULL);
}

extern HSD_GObj* HSD_GObj_804D781C;

void HSD_GObjPLink_80390228(HSD_GObj* gobj)
{
    HSD_ASSERT(0x171, gobj);
    if (!HSD_GObj_804CE3E4.b0 && gobj == HSD_GObj_804D781C) {
        HSD_GObj_804CE3E4.b1 = 1;
        return;
    }
    GObj_RemoveUserData(gobj);
    HSD_GObjObjet_80390B0C(gobj);
    HSD_GObjProc_8038FED4(gobj);
    if (gobj->gx_link != HSD_GOBJ_GXLINK_NONE) {
        HSD_GObjGXLink_8039084C(gobj);
    }
    if (gobj->prev != NULL) {
        gobj->prev->next = gobj->next;
    } else {
        ((HSD_GObj**) HSD_GObj_Entities)[gobj->p_link] = gobj->next;
    }
    if (gobj->next != NULL) {
        gobj->next->prev = gobj->prev;
    } else {
        plinklow_gobjs[gobj->p_link] = gobj->prev;
    }
    HSD_ObjFree(&gobj_alloc_data, gobj);
}

extern s32 HSD_GObj_804D783C;

void HSD_GObjPLink_8039032C(u32 arg0, HSD_GObj* gobj, u8 p_link, u8 priority,
                            HSD_GObj* position)
{
    HSD_GObjProc* proc_cur;
    HSD_GObjProc* child;
    HSD_GObjProc* cur;
    s32 flags_cur;
    s32 flags_new;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    HSD_ASSERT(0x1A3, p_link <= HSD_GObjLibInitData.p_link_max);
    if (!HSD_GObj_804CE3E4.b0 && gobj == HSD_GObj_804D781C) {
        HSD_GObj_804CE3E4.b3 = 1;
        HSD_GObj_804CE3E4.type = arg0;
        HSD_GObj_804CE3E4.p_link = p_link;
        HSD_GObj_804CE3E4.p_prio = priority;
        HSD_GObj_804CE3E4.gobj = position;
        return;
    }
    cur = gobj->proc;
    proc_cur = NULL;
    while (cur != NULL) {
        HSD_GObjProc_8038FC18(cur);
        child = cur->child;
        cur->child = proc_cur;
        proc_cur = cur;
        cur = child;
    }
    gobj->proc = NULL;
    if (gobj->prev != NULL) {
        gobj->prev->next = gobj->next;
    } else {
        ((HSD_GObj**) HSD_GObj_Entities)[gobj->p_link] = gobj->next;
    }
    if (gobj->next != NULL) {
        gobj->next->prev = gobj->prev;
    } else {
        plinklow_gobjs[gobj->p_link] = gobj->prev;
    }
    gobj->p_link = p_link;
    gobj->p_priority = priority;
    switch (arg0) {
    case 0:
        gobj_first_lower_prio(gobj);
        break;
    case 1:
        gobj_first_higher_prio(gobj);
        break;
    case 2:
        GObj_PReorder(gobj, position);
        break;
    case 3:
        GObj_PReorder(gobj, position->prev);
        break;
    }
    flags_new = HSD_GObj_804D783C == 0 ? 2 : HSD_GObj_804D783C - 1;
    flags_cur = flags_new == 0 ? 2 : flags_new - 1;
    cur = proc_cur;
    while (cur != NULL) {
        child = cur->child;
        HSD_GObjProc_8038FAA8(cur);
        if (cur->flags_3 == flags_cur) {
            cur->flags_3 = flags_new;
        }
        cur = child;
    }
}
