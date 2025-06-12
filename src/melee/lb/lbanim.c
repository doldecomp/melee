#include "lbanim.h"

#include <baselib/fobj.h>
#include <baselib/jobj.h>

static HSD_FObj* lbAnim_InitFrames(FigaTrack* track, s8 frames)
{
    HSD_FObj* fobj;
    HSD_FObj* next = NULL;
    HSD_FObj* result;
    int i;

    for (i = 0; i < frames; i++) {
        fobj = HSD_FObjAlloc();
        if (i == 0) {
            result = fobj;
        }
        if (next != 0) {
            next->next = fobj;
        }
        next = fobj;
        fobj->startframe = track->startframe;
        fobj->obj_type = track->obj_type;
        fobj->frac_value = track->frac_value;
        fobj->frac_slope = track->frac_slope;
        fobj->ad_head = track->ad_head;
        fobj->length = track->length;
        fobj->flags = 0;
        track++;
    }
    fobj->next = NULL;
    return result;
}

// Duplicate of JObjSortAnim
static void lbAnim_JObjSortAnim(HSD_AObj* aobj)
{
    HSD_FObj* fobj;
    HSD_FObj** fobj_ptr;

    if (aobj == NULL || aobj->fobj == NULL) {
        return;
    }
    for (fobj_ptr = &aobj->fobj; *fobj_ptr != NULL; fobj_ptr = &fobj->next) {
        fobj = *fobj_ptr;
        if (fobj->obj_type == TYPE_JOBJ) {
            *fobj_ptr = fobj->next;
            fobj->next = aobj->fobj;
            aobj->fobj = fobj;
            break;
        }
    }
}

void lbAnim_8001E6D8(HSD_JObj* jobj, FigaTree* tree, FigaTrack* track,
                     s8 frames)
{
    HSD_AObj* aobj;
    u32 unused[2];

    if (jobj != NULL && frames != 0) {
        if (jobj->aobj != NULL) {
            HSD_AObjRemove(jobj->aobj);
        }
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, tree->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0f);
        HSD_AObjSetEndFrame(aobj, tree->frames);
        HSD_AObjSetFObj(aobj, lbAnim_InitFrames(track, frames));
        jobj->aobj = aobj;
        lbAnim_JObjSortAnim(jobj->aobj);
        if (tree->type & 1) {
            HSD_JObjSetFlags(jobj, 8);
            return;
        }
        HSD_JObjClearFlags(jobj, 8);
    }
}
