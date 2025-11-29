#include "gr/grdynamicattr.h"

#include <platform.h>

#include "gr/types.h"
#include "mp/mplib.h"

#include <math.h>
#include <math_ppc.h>
#include <baselib/debug.h>

static const s32 GC_Id_None = -1;

static grDynamicAttr_UnkStruct grDynamicAttr_8049EFA0[4];
static grDynamicAttr_UnkStruct* grDynamicAttr_804D6960;
static grDynamicAttr_UnkStruct* grDynamicAttr_804D6964;

void grDynamicAttr_801CA0B4(void)
{
    s32 i;
    void* prev = NULL;
    grDynamicAttr_804D6960 = NULL;
    grDynamicAttr_804D6964 = NULL;

    for (i = 0; i < 4; i++) {
        grDynamicAttr_8049EFA0[i].next = prev;
        prev = grDynamicAttr_804D6964 = &grDynamicAttr_8049EFA0[i];
    }
}

grDynamicAttr_UnkStruct*
grDynamicAttr_801CA0F8(s32 arg0, Vec3* v, enum_t floor_id, f32 f, s32 arg3)
{
    u8 _[8];

    grDynamicAttr_UnkStruct* tmp;

    HSD_ASSERT(55, floor_id!=GC_Id_None);

    if ((tmp = grDynamicAttr_804D6964) != NULL) {
        grDynamicAttr_804D6964 = tmp->next;
        tmp->next = grDynamicAttr_804D6960;
        grDynamicAttr_804D6960 = tmp;
        tmp->unk4 = arg0;
        tmp->unk8 = *v;
        tmp->unk14 = floor_id;
        tmp->unk18 = f;
        tmp->unk1C = arg3;
        return tmp;
    }
    return NULL;
}

void grDynamicAttr_801CA1C0(grDynamicAttr_UnkStruct* arg)
{
    grDynamicAttr_UnkStruct* cur;

    if (arg == NULL) {
        return;
    }

    if (grDynamicAttr_804D6960 == arg) {
        grDynamicAttr_804D6960 = arg->next;
        goto insert;
    }
    for (cur = grDynamicAttr_804D6960; cur != NULL; cur = cur->next) {
        if (cur->next == arg) {
            cur->next = arg->next;
            break;
        }
    }
    if (cur == NULL) {
    insert:
        arg->next = grDynamicAttr_804D6964;
        grDynamicAttr_804D6964 = arg;
    }
}

void grDynamicAttr_801CA224(void)
{
    grDynamicAttr_UnkStruct* cur;
    grDynamicAttr_UnkStruct* next;
    for (cur = grDynamicAttr_804D6960; cur != NULL; cur = next) {
        next = cur->next;
        if (cur->unk1C > 0) {
            cur->unk1C--;
            if (cur->unk1C <= 0) {
                grDynamicAttr_801CA1C0(cur);
            }
        }
    }
}

inline f32 do_sqrtf(f32 x)
{
    return sqrtf(x);
}

int grDynamicAttr_801CA284(Vec3* v, int arg1)
{
    grDynamicAttr_UnkStruct* cur;

    for (cur = grDynamicAttr_804D6960; cur != NULL; cur = cur->next) {
        if (mpLinesConnected(arg1, cur->unk14)) {
            f32 dx = v->x - cur->unk8.x;
            f32 dy = v->y - cur->unk8.y;
            f32 dx2 = dx * dx;
            f32 dy2 = dy * dy;

            if (do_sqrtf(dx2 + dy2) < cur->unk18) {
                return cur->unk4;
            }
        }
    }

    return 0;
}
