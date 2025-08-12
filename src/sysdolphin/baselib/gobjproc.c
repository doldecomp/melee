#include "gobjproc.h"

#include "debug.h"
#include "gobj.h"
#include "objalloc.h"

#include <placeholder.h>

extern HSD_ObjAllocData gobjproc_alloc_data;

/**
 * Inserts a new GObjProc
 */
void HSD_GObjProc_8038FAA8(HSD_GObjProc* gproc)
{
    HSD_GObj* proc_gobj;
    HSD_GObjProc* dst_proc;
    u8 s_link;
    int p_link;

    proc_gobj = gproc->gobj;
    s_link = gproc->s_link;
    p_link = proc_gobj->p_link;

    // Scan through this GObjProc until we find a destination GObjProc
    // with the same s_link where we can insert it.
    //
    // Start at the current proc's GObj, and scan backwards through
    // all previous GObjs' procs.
    if (HSD_GObj_804D7844[p_link + s_link * (HSD_GObjLibInitData.p_link_max +
                                             1)] != NULL)
    {
        HSD_GObj* cur_gobj = proc_gobj;
        while (cur_gobj != NULL) {
            dst_proc = cur_gobj->proc;
            while (dst_proc != NULL) {
                if (dst_proc->s_link == s_link) {
                    if (HSD_GObj_804D7844[p_link +
                                          s_link *
                                              (HSD_GObjLibInitData.p_link_max +
                                               1)] == dst_proc)
                    {
                        HSD_GObj_804D7844[p_link +
                                          s_link *
                                              (HSD_GObjLibInitData.p_link_max +
                                               1)] = gproc;
                    }
                    goto insert_at_dst;
                }
                dst_proc = dst_proc->child;
            }
            cur_gobj = cur_gobj->prev;
        }
    } else {
        HSD_GObj_804D7844[p_link + s_link * (HSD_GObjLibInitData.p_link_max +
                                             1)] = gproc;
    }

    // If we got here, we still don't have a destination,
    // so scan through the global GObjProcs instead.
    while (p_link-- != 0) {
        dst_proc =
            HSD_GObj_804D7844[p_link +
                              s_link * (HSD_GObjLibInitData.p_link_max + 1)];
        if (dst_proc != NULL) {
            goto insert_at_dst;
        }
    }

    // If we're still continuing, we haven't found a valid
    // destination, so just put it at the front of the global list.
    if (true) {
        gproc->next = HSD_GObj_804D7840[s_link];
        HSD_GObj_804D7840[s_link] = gproc;
        gproc->prev = NULL;
    } else {
        // Alternatively, we jump here if we have a valid destination,
        // so we insert it in the linked list.
    insert_at_dst:
        gproc->next = dst_proc->next;
        dst_proc->next = gproc;
        gproc->prev = dst_proc;
    }

    // We've now inserted the GObjProc properly, so regardless of insertion
    // method, update any other struct fields / globals we need to.
    if (gproc->next != NULL) {
        gproc->next->prev = gproc;
    }
    gproc->child = proc_gobj->proc;
    proc_gobj->proc = gproc;
    if (HSD_GObj_804CE3E4.b0 && gproc->prev == HSD_GObj_804D7838 &&
        gproc->next == HSD_GObj_804D7830 && s_link == HSD_GObj_804D7834)
    {
        HSD_GObj_804D7830 = gproc;
    }
}

void HSD_GObjProc_8038FC18(HSD_GObjProc* gproc)
{
    int p_link = gproc->gobj->p_link;
    int s_link = gproc->s_link;
    if (HSD_GObj_804CE3E4.b0 && gproc == HSD_GObj_804D7830) {
        HSD_GObj_804D7830 = gproc->next;
    }
    if (gproc ==
        HSD_GObj_804D7844[p_link +
                          s_link * (HSD_GObjLibInitData.p_link_max + 1)])
    {
        if (gproc->prev != NULL && gproc->prev->gobj->p_link == p_link) {
            HSD_GObj_804D7844[p_link +
                              s_link * (HSD_GObjLibInitData.p_link_max + 1)] =
                gproc->prev;
        } else {
            HSD_GObj_804D7844[p_link +
                              s_link * (HSD_GObjLibInitData.p_link_max + 1)] =
                NULL;
        }
    }
    if (gproc->prev != NULL) {
        gproc->prev->next = gproc->next;
    } else {
        HSD_GObj_804D7840[s_link] = gproc->next;
    }
    if (gproc->next != NULL) {
        gproc->next->prev = gproc->prev;
    }
}

void HSD_GObjProc_8038FCE4(HSD_GObjProc* gproc)
{
    HSD_GObj* gobj = gproc->gobj;
    HSD_GObjProc_8038FC18(gproc);
    if (gobj->proc == gproc) {
        gobj->proc = gproc->child;
    } else {
        HSD_GObjProc* cur = gobj->proc;
        while (cur->child != gproc) {
            cur = cur->child;
        }
        cur->child = gproc->child;
    }
}

inline void assertProc(HSD_GObjProc* gproc)
{
    HSD_ASSERT(31, gproc);
}

HSD_GObjProc* HSD_GObjProc_8038FD54(HSD_GObj* gobj, void (*func)(HSD_GObj*),
                                    u8 pri)
{
    HSD_GObjProc* gproc;

    u8 _[8];

    gproc = HSD_ObjAlloc(&gobjproc_alloc_data);
    assertProc(gproc);
    HSD_ASSERT(216, pri <= HSD_GObjLibInitData.gproc_pri_max);
    gproc->s_link = pri;
    gproc->flags_1 = gproc->flags_2 = 0;
    gproc->flags_3 = 3;
    gproc->gobj = gobj;
    gproc->on_invoke = func;
    HSD_GObjProc_8038FAA8(gproc);
    return gproc;
}

void HSD_GObjProc_8038FE24(HSD_GObjProc* gproc)
{
    if (!HSD_GObj_804CE3E4.b0 && gproc == HSD_GObj_804D7838) {
        HSD_GObj_804CE3E4.b2 = true;
    } else {
        HSD_GObjProc_8038FCE4(gproc);
        HSD_ObjFree(&gobjproc_alloc_data, gproc);
    }
}

void HSD_GObjProc_8038FED4(HSD_GObj* gobj)
{
    HSD_GObjProc* cur = gobj->proc;
    while (cur != NULL) {
        HSD_GObjProc* next = cur->child;
        HSD_GObjProc_8038FE24(cur);
        cur = next;
    }
}
