#include <platform.h>

#include <baselib/fobj.h>
#include <baselib/jobj.h>

/* 01E560 */ static HSD_FObj* getFObj(s32, s8);

typedef struct {
    u32 unk0;
    u32 unk4;
    f32 unk8;
} asdf;

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

void lbAnim_8001E6D8(HSD_JObj* jobj, asdf* arg1, s32 arg2, s8 arg3)
{
    HSD_AObj* aobj;
    u32 unused[2];

    if (jobj != NULL && arg3 != 0) {
        if (jobj->aobj != NULL) {
            HSD_AObjRemove(jobj->aobj);
        }
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, arg1->unk4);
        HSD_AObjSetRewindFrame(aobj, 0.0f);
        HSD_AObjSetEndFrame(aobj, arg1->unk8);
        HSD_AObjSetFObj(aobj, getFObj(arg2, arg3));
        jobj->aobj = aobj;
        foo(jobj);
        if (arg1->unk0 & 1) {
            HSD_JObjSetFlags(jobj, 8);
            return;
        }
        HSD_JObjClearFlags(jobj, 8);
    }
}
