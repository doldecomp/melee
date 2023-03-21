#ifndef MELEE_GR_GRDYNAMICATTR_H
#define MELEE_GR_GRDYNAMICATTR_H

#include "gr/forward.h"

#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>

struct grDynamicAttr_UnkStruct {
    grDynamicAttr_UnkStruct* next;
    s32 unk4;
    Vec3 unk8;
    s32 unk14;
    f32 unk18;
    s32 unk1C;
    u8 x0_fill[0x24 - 0x20];
};

int func_801CA284(Vec3* v, int arg1);

int func_801CA284(Vec3* v, int arg1);
void func_801CA0B4(void);
grDynamicAttr_UnkStruct* func_801CA0F8(s32 arg0, Vec3* v, enum_t floor_id,
                                       f32 f, s32 arg3);
void func_801CA1C0(grDynamicAttr_UnkStruct* arg);
void func_801CA224(void);

#endif
