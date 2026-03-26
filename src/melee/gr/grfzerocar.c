#include "gr/grfzerocar.h"

#include "gr/granime.h"
#include "gr/grdatfiles.h"
#include "gr/ground.h"
#include "lb/lb_00F9.h"
#include "sc/types.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

typedef struct grFZeroCarEntry {
    s16 unk0;
    s16 unk2;
    s16 children[4];
} grFZeroCarEntry;

struct grFZeroCar_RST {
    Vec3 scale;
    Vec3 translate;
    Quaternion rotate;
};

const struct grFZeroCar_RST grFZeroCar_803B7E50 = {
    { 1.0f, 1.0f, 1.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
};

grFZeroCarEntry grFZeroCar_803E0BD8[30] = {
    { 0, 0, { 1, 3, -1, -1 } },   { 0, 1, { 1, 3, 2, 4 } },
    { 0, 2, { 1, 2, 3, -1 } },    { 0, 3, { 1, 2, -1, -1 } },
    { 0, 4, { 1, 3, 2, 4 } },     { 0, 5, { 1, -1, -1, -1 } },
    { 0, 6, { 1, 2, -1, -1 } },   { 0, 7, { 1, 2, -1, -1 } },
    { 0, 8, { 1, 3, 2, 4 } },     { 0, 9, { 1, 2, -1, -1 } },
    { 0, 10, { 1, 2, -1, -1 } },  { 0, 11, { 1, -1, -1, -1 } },
    { 0, 12, { 1, 2, -1, -1 } },  { 0, 13, { 1, -1, -1, -1 } },
    { 0, 14, { 1, 2, -1, -1 } },  { 0, 15, { 1, 2, 3, -1 } },
    { 0, 16, { 1, 2, -1, -1 } },  { 0, 17, { 1, 2, -1, -1 } },
    { 0, 18, { 2, 3, 1, -1 } },   { 0, 19, { 1, 2, -1, -1 } },
    { 0, 20, { 1, 3, 2, 4 } },    { 0, 21, { 1, 2, 3, -1 } },
    { 0, 22, { 1, -1, -1, -1 } }, { 0, 23, { 1, 2, 3, -1 } },
    { 0, 24, { 1, 3, 2, 4 } },    { 0, 25, { 1, 2, 3, -1 } },
    { 0, 26, { 1, 2, 3, -1 } },   { 0, 27, { 1, -1, -1, -1 } },
    { 0, 28, { 1, -1, -1, -1 } }, { 0, 29, { 1, 3, 2, 4 } },
};

static inline void setup_car_child(HSD_JObj* parent, s16 ext_count, s32 offset,
                                   f32 scale_factor)
{
    UnkArchiveStruct* archive;
    HSD_JObj* jobj;

    archive = grDatFiles_801C6330(ext_count);
    HSD_ASSERT(95, archive);

    jobj = Ground_801C13D0(ext_count, 0);
    if (jobj != NULL) {
        DynamicModelDesc* entry =
            (DynamicModelDesc*) ((u8*) offset +
                                 (uintptr_t) archive->unk4->unk8);
        if (entry->anims != NULL) {
            if (entry->matanims != NULL) {
                grAnime_801C6C0C(jobj, *entry->anims, *entry->matanims, NULL);
                HSD_JObjReqAnimAllByFlags(jobj, 0x497, 0.0f);
                HSD_ForeachAnim(jobj, JOBJ_TYPE, 0x76a4, HSD_AObjSetRate,
                                AOBJ_ARG_AF, 1.0);
            }
        }
        HSD_JObjAddChild(parent, jobj);
    }

    HSD_JObjSetScaleX(parent, scale_factor);
    HSD_JObjSetScaleY(parent, scale_factor);
}

static inline void multiplyScale(HSD_JObj* jobj, f32 scale)
{
    Vec3 scl;
    HSD_JObjGetScale(jobj, &scl);
    scl.x *= scale;
    scl.y *= scale;
    scl.z *= scale;
    HSD_JObjSetScale(jobj, &scl);
}

void grFZeroCar_801CAFBC(HSD_GObj* gobj, void* data, s32 count, s32 mode)
{
    HSD_JObj* root;
    HSD_JObj* child;
    HSD_JObj* tra_jobj;
    f32 ground_scale;
    Vec3 scl_local;
    int i;
    s16* data_ptr;
    Vec3 trans_local;
    Quaternion rot_local;
    u32 pad1;
    u32 pad2;
    u32 pad3;
    u32 pad4;
    u32 pad5;
    u32 pad6;

    root = gobj->hsd_obj;
    ground_scale = Ground_801C0498();

    scl_local = grFZeroCar_803B7E50.scale;
    HSD_JObjSetScale(root, &scl_local);

    child = HSD_JObjGetChild(root);

    if (mode != 0) {
        lb_8000F9F8(child);
    }

    tra_jobj = HSD_JObjAlloc();
    HSD_ASSERT(172, tra_jobj);
    PSMTXIdentity(tra_jobj->mtx);
    tra_jobj->scl = NULL;
    HSD_JObjAddNext(child, tra_jobj);

    data_ptr = (s16*) data;

    for (i = 0; i < 30; i++) {
        s32 idx;
        s32 active;
        f32 scale_factor;
        HSD_JObj* c0;
        HSD_JObj* c1;
        HSD_JObj* c2;
        HSD_JObj* c3;

        if (i != 0) {
            child = Ground_801C13D0(data_ptr[i], 0);
            if (child != NULL) {
                tra_jobj = HSD_JObjAlloc();
                HSD_ASSERT(186, tra_jobj);
                PSMTXIdentity(tra_jobj->mtx);
                tra_jobj->scl = NULL;
                HSD_JObjAddNext(child, tra_jobj);
                HSD_JObjAddChild(root, tra_jobj);
                if (mode != 0) {
                    lb_8000F9F8(child);
                }
            } else {
                HSD_ASSERT(195, 0);
            }
        }

        trans_local = grFZeroCar_803B7E50.translate;
        rot_local = grFZeroCar_803B7E50.rotate;
        HSD_JObjSetTranslate(child, &trans_local);
        HSD_JObjSetRotation(child, &rot_local);

        {
            Vec3 scl;
            HSD_JObjGetScale(tra_jobj, &scl);
            scl.x *= ground_scale;
            scl.y *= ground_scale;
            scl.z *= ground_scale;
            HSD_JObjSetScale(tra_jobj, &scl);
        }

        idx = grFZeroCar_803E0BD8[i].children[0];
        scale_factor = 1.0f;
        active = 0;
        c0 = NULL;
        c1 = NULL;
        c2 = NULL;
        c3 = NULL;

        if (idx != -1) {
            active = 1;
        }
        if (grFZeroCar_803E0BD8[i].children[1] != -1) {
            active++;
        }
        if (grFZeroCar_803E0BD8[i].children[2] != -1) {
            active++;
        }
        if (grFZeroCar_803E0BD8[i].children[3] != -1) {
            active++;
        }

        if (active == 1) {
            scale_factor = 1.1f;
        } else if (active == 2) {
            scale_factor = 1.0f;
        } else if (active == 3) {
            scale_factor = 1.0f;
        } else if (active == 4) {
            scale_factor = 0.9f;
        }

        if (idx != -1) {
            HSD_JObj* j = child;
            while (j != NULL && idx != 0) {
                idx--;
                j = Ground_801C4100(j);
            }
            c0 = j;
        }

        idx = grFZeroCar_803E0BD8[i].children[1];
        if (idx != -1) {
            HSD_JObj* j = child;
            while (j != NULL && idx != 0) {
                idx--;
                j = Ground_801C4100(j);
            }
            c1 = j;
        }

        idx = grFZeroCar_803E0BD8[i].children[2];
        if (idx != -1) {
            HSD_JObj* j = child;
            while (j != NULL && idx != 0) {
                idx--;
                j = Ground_801C4100(j);
            }
            c2 = j;
        }

        idx = grFZeroCar_803E0BD8[i].children[3];
        if (idx != -1) {
            HSD_JObj* j = child;
            while (j != NULL && idx != 0) {
                idx--;
                j = Ground_801C4100(j);
            }
            c3 = j;
        }

        if (c0 != NULL) {
            setup_car_child(c0, count, (s16) count * 0x34, scale_factor);
        }

        if (c1 != NULL) {
            setup_car_child(c1, count, (s16) count * 0x34, scale_factor);
        }

        if (c2 != NULL) {
            setup_car_child(c2, count, (s16) count * 0x34, scale_factor);
        }

        if (c3 != NULL) {
            setup_car_child(c3, count, (s16) count * 0x34, scale_factor);
        }
    }
}
