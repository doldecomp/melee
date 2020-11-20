#include "fobj.h"

extern HSD_ObjAllocData lbl_804C08D8;

HSD_ObjAllocData* HSD_FObjGetAllocData(void)
{
    return &lbl_804C08D8;
}

void HSD_FObjInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C08D8, sizeof(HSD_FObj), 4);
}

void HSD_FObjRemove(HSD_FObj* fobj)
{
    if (!fobj)
        return;

    HSD_FObjFree(fobj);
}

inline HSD_FObj *HSD_FObjGetNext(struct _HSD_FObj *fobj) {
    return fobj->next;
}

inline void *HSD_FObjRemoveAll_Inlined(struct _HSD_FObj *fobj) {
    if (!fobj)
        return;
    HSD_FObjRemoveAll(fobj->next);
    HSD_FObjRemove(fobj);
}

void HSD_FObjRemoveAll(HSD_FObj* fobj)
{
    HSD_FObj* t1;
    HSD_FObj* t2;
    HSD_FObj* t3;

    if (fobj)
    {
        t3 = HSD_FObjGetNext(fobj);
        if (t3)
        {
            t2 = HSD_FObjGetNext(t3);
            if (t2)
            {
                HSD_FObjRemoveAll_Inlined(t2->next);
                if (t2) {
                    HSD_FObjFree(t2);
                }
            }
            if (t3) {
                HSD_FObjFree(t3);
            }
        }
        if (fobj) {
            HSD_FObjFree(fobj);
        }
    }
}

u8 HSD_FObjSetState(HSD_FObj* fobj, u8 state)
{
    if (fobj)
        fobj->flags = (state & 0xF) | (fobj->flags & 0xF0);
    return state;
}

u32 HSD_FObjGetState(HSD_FObj* fobj)
{
    if (!fobj)
        return 0;
    return fobj->flags & 0xF;
}
