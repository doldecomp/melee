#include <dolphin/mtx/mtxtypes.h>
#include <math.h>
#include <melee/mp/mplib.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/debug.h>

typedef struct _UnkStruct {
    struct _UnkStruct* next;
    s32 unk4;
    Vec3 unk8;
    s32 unk14;
    f32 unk18;
    s32 unk1C;
    u8 x0_fill[0x24 - 0x20];
} UnkStruct;

static const s32 GC_Id_None = -1;

static UnkStruct lbl_8049EFA0[4];
static UnkStruct* lbl_804D6960;
static UnkStruct* lbl_804D6964;

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

UnkStruct* func_801CA0F8(s32 arg0, Vec3* v, enum_t floor_id, f32 f, s32 arg3)
{
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    UnkStruct* tmp;

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

void func_801CA1C0(UnkStruct* arg)
{
    UnkStruct* cur;

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
    UnkStruct* cur;
    UnkStruct* next;
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

s32 func_801CA284(Vec3* v, s32 arg1)
{
    UnkStruct* cur;
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
