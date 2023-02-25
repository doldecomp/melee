#include <sysdolphin/baselib/gobjproc.h>

#include <sysdolphin/baselib/gobj.h>

extern HSD_ObjAllocData gobjproc_alloc_data;

extern HSD_GObjProc* lbl_804D7830;
extern HSD_GObjProc* lbl_804D7838;
extern HSD_GObjProc** lbl_804D7840;
extern HSD_GObjProc** lbl_804D7844;

void func_8038FC18(HSD_GObjProc* gproc)
{
    s32 temp_r7 = gproc->gobj->p_link;
    s32 temp_r8 = gproc->s_link;
    if (lbl_804CE3E4.b0 && gproc == lbl_804D7830) {
        lbl_804D7830 = gproc->next;
    }
    if (gproc ==
        lbl_804D7844[temp_r7 + temp_r8 * (HSD_GObjLibInitData.p_link_max + 1)])
    {
        if (gproc->prev != NULL && gproc->prev->gobj->p_link == temp_r7) {
            lbl_804D7844[temp_r7 + temp_r8 * (HSD_GObjLibInitData.p_link_max +
                                              1)] = gproc->prev;
        } else {
            lbl_804D7844[temp_r7 +
                         temp_r8 * (HSD_GObjLibInitData.p_link_max + 1)] = NULL;
        }
    }
    if (gproc->prev != NULL) {
        gproc->prev->next = gproc->next;
    } else {
        lbl_804D7840[temp_r8] = gproc->next;
    }
    if (gproc->next != NULL) {
        gproc->next->prev = gproc->prev;
    }
}

void func_8038FCE4(HSD_GObjProc* gproc)
{
    HSD_GObj* gobj = gproc->gobj;
    func_8038FC18(gproc);
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

HSD_GObjProc* func_8038FD54(HSD_GObj* gobj, void (*func)(HSD_GObj*), u8 pri)
{
    HSD_GObjProc* gproc;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    gproc = HSD_ObjAlloc(&gobjproc_alloc_data);
    assertProc(gproc);
    HSD_ASSERT(216, pri <= HSD_GObjLibInitData.gproc_pri_max);
    gproc->s_link = pri;
    gproc->flags_1 = gproc->flags_2 = 0;
    gproc->flags_3 = 3;
    gproc->gobj = gobj;
    gproc->on_invoke = func;
    func_8038FAA8(gproc);
    return gproc;
}

void func_8038FE24(HSD_GObjProc* gproc)
{
    if (!lbl_804CE3E4.b0 && gproc == lbl_804D7838) {
        lbl_804CE3E4.b2 = true;
    } else {
        func_8038FCE4(gproc);
        HSD_ObjFree(&gobjproc_alloc_data, gproc);
    }
}

void func_8038FED4(HSD_GObj* gobj)
{
    HSD_GObjProc* cur = gobj->proc;
    while (cur != NULL) {
        HSD_GObjProc* next = cur->child;
        func_8038FE24(cur);
        cur = next;
    }
}
