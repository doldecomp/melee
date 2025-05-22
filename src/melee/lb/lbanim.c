#include <platform.h>

#include <baselib/fobj.h>
#include <baselib/jobj.h>

typedef struct FigaTrack {
    u16 length;
    u16 startframe;
    u8 obj_type;
    u8 frac_value;
    u8 frac_slope;
    u8* ad_head;
} FigaTrack;

typedef struct FigaTree {
    int type;
    u32 flags;
    f32 frames;
    void* nodes;
    FigaTrack** tracks;
} FigaTree;

static HSD_FObj* lbAnim_8001E560(FigaTrack* track, s8 count)
{
    HSD_FObj* fobj;
    HSD_FObj* next = NULL;
    HSD_FObj* result;
    int i;

    for (i = 0; i < count; i++) {
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

void foo(HSD_JObj* jobj)
{
    HSD_AObj* temp_r4 = jobj->aobj;
    if (temp_r4 != NULL && temp_r4->fobj != NULL) {
        HSD_FObj** cur = &temp_r4->fobj;
        while (*cur != NULL) {
            if ((*cur)->obj_type == 12) {
                HSD_FObj* fobj = *cur;
                *cur = fobj->next;
                fobj->next = temp_r4->fobj;
                temp_r4->fobj = fobj;
                break;
            }
            cur = &(*cur)->next;
        }
    }
}

void lbAnim_8001E6D8(HSD_JObj* jobj, FigaTree* tree, FigaTrack* track, s8 arg3)
{
    HSD_AObj* aobj;
    u32 unused[2];

    if (jobj != NULL && arg3 != 0) {
        if (jobj->aobj != NULL) {
            HSD_AObjRemove(jobj->aobj);
        }
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, tree->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0f);
        HSD_AObjSetEndFrame(aobj, tree->frames);
        HSD_AObjSetFObj(aobj, lbAnim_8001E560(track, arg3));
        jobj->aobj = aobj;
        foo(jobj);
        if (tree->type & 1) {
            HSD_JObjSetFlags(jobj, 8);
            return;
        }
        HSD_JObjClearFlags(jobj, 8);
    }
}
