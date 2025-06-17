#include <placeholder.h>

#include "gobjproc.h"

#include "debug.h"
#include "gobj.h"
#include "objalloc.h"

extern HSD_ObjAllocData gobjproc_alloc_data;

#pragma push
#pragma dont_inline on
void HSD_GObjProc_8038FAA8(HSD_GObjProc* gproc)
{
    NOT_IMPLEMENTED;
}
#pragma pop

void HSD_GObjProc_8038FC18(HSD_GObjProc* gproc)
{
    s32 temp_r7 = gproc->gobj->p_link;
    s32 temp_r8 = gproc->s_link;
    if (HSD_GObj_804CE3E4.b0 && gproc == HSD_GObj_804D7830) {
        HSD_GObj_804D7830 = gproc->next;
    }
    if (gproc ==
        HSD_GObj_804D7844[temp_r7 +
                          temp_r8 * (HSD_GObjLibInitData.p_link_max + 1)])
    {
        if (gproc->prev != NULL && gproc->prev->gobj->p_link == temp_r7) {
            HSD_GObj_804D7844[temp_r7 +
                              temp_r8 * (HSD_GObjLibInitData.p_link_max + 1)] =
                gproc->prev;
        } else {
            HSD_GObj_804D7844[temp_r7 +
                              temp_r8 * (HSD_GObjLibInitData.p_link_max + 1)] =
                NULL;
        }
    }
    if (gproc->prev != NULL) {
        gproc->prev->next = gproc->next;
    } else {
        HSD_GObj_804D7840[temp_r8] = gproc->next;
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
