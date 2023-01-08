#ifndef MELEE_MP_MPCOLL_H
#define MELEE_MP_MPCOLL_H

#include <dolphin/types.h>
#include <melee/ft/fighter.h>

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
void func_800436D8(CollData*, s32);
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

#endif
