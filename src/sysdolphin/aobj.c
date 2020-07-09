#include "aobj.h"

extern HSD_ObjAllocData lbl_804C0880; //aobj_alloc_data

extern s32 lbl_804D7630;
extern s32 lbl_804D762C;

extern HSD_SList* lbl_804D7628;

void HSD_AObjInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C0880, sizeof(HSD_AObj), 4);
}

#pragma push
#pragma force_active on // Unused function until it's loaded into a GetAllocData function table, so force_active required to match for now
HSD_ObjAllocData* HSD_AObjGetAllocData(void)
{
    return &lbl_804C0880;
}
#pragma pop

u32 HSD_AObjGetFlags(HSD_AObj* aobj)
{
    return (aobj) ? aobj->flags : 0;
}

void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags |= flags;
    }
}

void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags &= ~flags;
    }
}

// HACK: Pragmas affect epilogue addi/mtlr ordering. Check when we have 1.0
#pragma push
#pragma altivec_codegen on
#pragma altivec_model on
void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj)
{
    if (aobj == NULL)
        return;
    if (aobj->fobj) {
            HSD_FObjRemoveAll(aobj->fobj);
    }
    aobj->fobj = fobj;
}
#pragma pop

void HSD_AObjInitEndCallBack(void)
{
    lbl_804D762C = 0;
    lbl_804D7630 = 0;
}

#pragma optimization_level 2
void HSD_AObjInvokeCallBacks(void)
{
    u32 junk1;
    u32 junk2;
    HSD_SList* list;

    if (lbl_804D762C != 0 && lbl_804D7630 == 0) {
        list = lbl_804D7628;
        while (list) {
            void (*func)(void) = list->data;
            (*func)();
            list = list->next;
        }
    }
}

void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame)
{
    u32 flags;

    if (aobj == NULL)
        return;

    aobj->curr_frame = frame;

    flags = aobj->flags & 0xBFFFFFFF;
    aobj->flags = flags | AOBJ_FIRST_PLAY;

    HSD_FObjReqAnimAll(aobj->fobj, frame);
}
