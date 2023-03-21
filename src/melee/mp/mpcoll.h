#ifndef MELEE_MP_MPCOLL_H
#define MELEE_MP_MPCOLL_H

#include "ft/fighter.h"

#include <Runtime/platform.h>

void func_80042374(CollData*, f32, f32, f32);
void func_80042078(CollData* cd, HSD_GObj* gobj, HSD_JObj*, HSD_JObj*,
                   HSD_JObj*, HSD_JObj*, HSD_JObj*, HSD_JObj*, HSD_JObj*, f32);

/// "Coll_InitECB"
void func_80041EE4(CollData*);

void func_800471F8(CollData*);
void func_800473CC(CollData*);
void func_800477E0(CollData*);
void func_80048464(CollData*);
void func_80048160(CollData*);
void func_80048274(CollData*);
void func_80048578(CollData*);
void func_80048768(CollData*);
void func_80048388(CollData*);
void func_800436D8(CollData*, int facing_dir);
void func_800475F4(CollData*);
void func_8004730C(CollData*, f32 (*x)[6]);
void func_80047A08(CollData*);
void func_8004B108(CollData*);
void func_8004B21C(CollData*);
void func_8004B2DC(CollData*);
void func_8004B3F0(CollData*);
void func_80047E14(CollData*);
void func_80047AC8(CollData*);
void func_80047F40(CollData*);
void func_80047BF4(CollData*);
void func_8004806C(CollData*);
void func_80047D20(CollData*);
void func_80048654(CollData*);
void func_800474E0(CollData*);
void func_800476B4(CollData*);
void func_800478F4(CollData*);
void func_8004B5C4(CollData*);
void func_8004CC00(CollData*);
void func_8004CA6C(CollData*);
void func_8004CBF4(struct _CollData*);

void func_80041C78(void);
void func_80042384(CollData* cd);
void func_800424DC(CollData* cd, u32 flags);
void func_80041C8C(CollData* cd);
void func_8004293C(CollData* cd);
void func_80042C58(CollData* arg0, ftECB* arg1);
void func_80042D24(CollData* cd);
void func_80042DB0(CollData* ecb, f32 time);
void func_80043268(CollData* arg0, s32 arg1, s32 arg2, f32 arg8);
void func_80043324_inline2(CollData* arg0, s32 arg1, s32 arg2, f32 arg8);
void func_80043324_inline(CollData* arg0, s32 arg1, s32 arg2, f32 arg8);
void func_80043324(CollData* arg0, s32 arg1, s32 arg2);
void func_80043558(CollData* arg0, s32 arg1);
void func_80043670(CollData* arg0);
void func_80041DD0(CollData* cd, u32 flags);
void func_80043680(CollData* arg0, Vec3* arg1);
void func_800436E4(CollData* arg0, f32 arg1);
s32 func_80043754(s32 (*arg0)(void*, u32), CollData* arg1, u32 arg2);
void func_800439FC(CollData* arg0);
void func_80043ADC(CollData* arg0);
bool func_80043BBC(CollData* arg0, s32* arg1);
void func_80043C6C(CollData* arg0, s32 arg1, s32 arg2);
void func_8004220C(CollData* cd, HSD_GObj* gobj, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4);

#endif
