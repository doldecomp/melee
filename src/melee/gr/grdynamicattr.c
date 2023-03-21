#include <math.h>
#include <dolphin/mtx/types.h>
#include <baselib/debug.h>
#include <melee/gr/grdynamicattr.h>
#include <melee/mp/mplib.h>
#include <Runtime/platform.h>

static const s32 GC_Id_None = -1;

static grDynamicAttr_UnkStruct lbl_8049EFA0[4];
static grDynamicAttr_UnkStruct* lbl_804D6960;
static grDynamicAttr_UnkStruct* lbl_804D6964;

void func_801CA0B4(void)
{
    s32 i;
    void* prev = NULL;
    lbl_804D6960 = NULL;
    lbl_804D6964 = NULL;

    for (i = 0; i < 4; i++) {
        lbl_8049EFA0[i].next = prev;
        prev = lbl_804D6964 = &lbl_8049EFA0[i];
    }
}

grDynamicAttr_UnkStruct* func_801CA0F8(s32 arg0, Vec3* v, enum_t floor_id,
                                       f32 f, s32 arg3)
{
#ifdef MUST_MATCH
    u8 _[8];
#endif

    grDynamicAttr_UnkStruct* tmp;

    HSD_ASSERT(55, floor_id!=GC_Id_None);

    if ((tmp = lbl_804D6964) != NULL) {
        lbl_804D6964 = tmp->next;
        tmp->next = lbl_804D6960;
        lbl_804D6960 = tmp;
        tmp->unk4 = arg0;
        tmp->unk8 = *v;
        tmp->unk14 = floor_id;
        tmp->unk18 = f;
        tmp->unk1C = arg3;
        return tmp;
    }
    return NULL;
}

void func_801CA1C0(grDynamicAttr_UnkStruct* arg)
{
    grDynamicAttr_UnkStruct* cur;

    if (arg == NULL) {
        return;
    }

    if (lbl_804D6960 == arg) {
        lbl_804D6960 = arg->next;
        goto insert;
    }
    for (cur = lbl_804D6960; cur != NULL; cur = cur->next) {
        if (cur->next == arg) {
            cur->next = arg->next;
            break;
        }
    }
    if (cur == NULL) {
    insert:
        arg->next = lbl_804D6964;
        lbl_804D6964 = arg;
    }
}

void func_801CA224(void)
{
    grDynamicAttr_UnkStruct* cur;
    grDynamicAttr_UnkStruct* next;
    for (cur = lbl_804D6960; cur != NULL; cur = next) {
        next = cur->next;
        if (cur->unk1C > 0) {
            cur->unk1C--;
            if (cur->unk1C <= 0) {
                func_801CA1C0(cur);
            }
        }
    }
}

inline f32 do_sqrtf(f32 x)
{
    return sqrtf(x);
}

int func_801CA284(Vec3* v, int arg1)
{
    grDynamicAttr_UnkStruct* cur;

    for (cur = lbl_804D6960; cur != NULL; cur = cur->next) {
        if (func_80054F68(arg1, cur->unk14)) {
            f32 dx = v->x - cur->unk8.x;
            f32 dy = v->y - cur->unk8.y;
            f32 dx2 = dx * dx;
            f32 dy2 = dy * dy;

            if (do_sqrtf(dx2 + dy2) < cur->unk18)
                return cur->unk4;
        }
    }

    return 0;
}
