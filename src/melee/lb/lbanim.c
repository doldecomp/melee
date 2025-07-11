#include "lbanim.h"

#include <baselib/fobj.h>
#include <baselib/jobj.h>
#include <baselib/aobj.h>

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

HSD_FObj* fn_8001E60C(FigaTrack* track, s8 frames)
{
    HSD_FObj* fobj;
    HSD_FObj* prev = NULL;
    HSD_FObj* first = NULL;
    int i;

    for (i = 0; i < frames; i++) {
        if (track->obj_type != 5 && (u8) (track->obj_type - 6) > 1) {
            fobj = HSD_FObjAlloc();
            if (first == NULL) {
                first = fobj;
            }
            if (prev != NULL) {
                prev->next = fobj;
            }
            prev = fobj;
            fobj->startframe = track->startframe;
            fobj->obj_type = track->obj_type;
            fobj->frac_value = track->frac_value;
            fobj->frac_slope = track->frac_slope;
            fobj->ad_head = track->ad_head;
            fobj->length = track->length;
            fobj->flags = 0;
            track++;
        }
    }
    fobj->next = NULL;
    return first;
}

// Duplicate of JObjSortAnim
static inline void lbAnim_JObjSortAnim(HSD_AObj* aobj)
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
    PAD_STACK(8);

    if (jobj != NULL && frames != 0) {
        if (jobj->aobj != NULL) {
            HSD_AObjRemove(jobj->aobj);
        }
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, tree->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0F);
        HSD_AObjSetEndFrame(aobj, tree->frames);
        HSD_AObjSetFObj(aobj, lbAnim_InitFrames(track, frames));
        jobj->aobj = aobj;
        lbAnim_JObjSortAnim(jobj->aobj);
        if (tree->type & 1) {
            HSD_JObjSetFlags(jobj, JOBJ_CLASSICAL_SCALE);
        } else {
            HSD_JObjClearFlags(jobj, JOBJ_CLASSICAL_SCALE);
        }
    }
}

void lbAnim_8001E7E8(HSD_JObj* jobj, FigaTree* tree, FigaTrack* track,
                     s8 frames)
{
    HSD_AObj* aobj;
    PAD_STACK(8);

    if (jobj != NULL && frames != 0) {
        if (jobj->aobj != NULL) {
            HSD_AObjRemove(jobj->aobj);
        }
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, tree->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0F);
        HSD_AObjSetEndFrame(aobj, tree->frames);
        HSD_AObjSetFObj(aobj, fn_8001E60C(track, frames));
        jobj->aobj = aobj;
        lbAnim_JObjSortAnim(jobj->aobj);
        if (tree->type & 1) {
            HSD_JObjSetFlags(jobj, JOBJ_CLASSICAL_SCALE);
        } else {
            HSD_JObjClearFlags(jobj, JOBJ_CLASSICAL_SCALE);
        }
    }
}

float lbAnim_8001E8F8(FigaTree* tree)
{
    if (tree != NULL) {
        return tree->frames;
    }
    return 0.0F;
}
