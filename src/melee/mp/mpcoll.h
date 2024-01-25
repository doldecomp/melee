#ifndef MELEE_MP_MPCOLL_H
#define MELEE_MP_MPCOLL_H

#include <platform.h>
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ft/fighter.h"
#include "ft/types.h"

void mpColl_80042374(CollData*, f32, f32, f32);
void mpColl_80042078(CollData* cd, HSD_GObj* gobj, HSD_JObj*, HSD_JObj*,
                     HSD_JObj*, HSD_JObj*, HSD_JObj*, HSD_JObj*, HSD_JObj*,
                     f32);

/// "Coll_InitECB"
void mpColl_80041EE4(CollData*);

void mpColl_800471F8(CollData*);
void mpColl_800473CC(CollData*);
void mpColl_800477E0(CollData*);
void mpColl_80048464(CollData*);
void mpColl_80048160(CollData*);
void mpColl_80048274(CollData*);
void mpColl_80048578(CollData*);
void mpColl_80048768(CollData*);
void mpColl_80048388(CollData*);
void mpColl_800436D8(CollData*, int facing_dir);
void mpColl_800475F4(CollData*);
void mpColl_8004730C(CollData*, f32 (*x)[6]);
void mpColl_80047A08(CollData*);
void mpColl_8004B108(CollData*);
void mpColl_8004B21C(CollData*);
void mpColl_8004B2DC(CollData*);
void mpColl_8004B3F0(CollData*);
void mpColl_80047E14(CollData*);
void mpColl_80047AC8(CollData*);
void mpColl_80047F40(CollData*);
void mpColl_80047BF4(CollData*);
void mpColl_8004806C(CollData*);
void mpColl_80047D20(CollData*);
void mpColl_80048654(CollData*);
void mpColl_800474E0(CollData*);
void mpColl_800476B4(CollData*);
void mpColl_800478F4(CollData*);
void mpColl_8004B5C4(CollData*);
void mpColl_8004CC00(CollData*);
void mpColl_8004CA6C(CollData*);
void mpColl_8004CBF4(struct _CollData*);

void mpColl_80041C78(void);
void mpColl_80042384(CollData* cd);
void mpColl_800424DC(CollData* cd, u32 flags);
void mpColl_80041C8C(CollData* cd);
void mpColl_8004293C(CollData* cd);
void mpColl_80042C58(CollData* arg0, ftECB* arg1);
void mpColl_80042D24(CollData* cd);
void mpColl_80042DB0(CollData* ecb, f32 time);
void mpColl_80043268(CollData* arg0, s32 arg1, s32 arg2, f32 arg8);
void func_80043324_inline2(CollData* arg0, s32 arg1, s32 arg2, f32 arg8);
void func_80043324_inline(CollData* arg0, s32 arg1, s32 arg2, f32 arg8);
void mpColl_80043324(CollData* arg0, s32 arg1, s32 arg2);
void mpColl_80043558(CollData* arg0, s32 arg1);
void mpColl_80043670(CollData* arg0);
void mpColl_80041DD0(CollData* cd, u32 flags);
void mpColl_80043680(CollData* arg0, Vec3* arg1);
void mpColl_800436E4(CollData* arg0, f32 arg1);
s32 mpColl_80043754(s32 (*arg0)(void*, u32), CollData* arg1, u32 arg2);
void mpColl_800439FC(CollData* arg0);
void mpColl_80043ADC(CollData* arg0);
bool mpColl_80043BBC(CollData* arg0, s32* arg1);
void mpColl_80043C6C(CollData* arg0, s32 arg1, s32 arg2);
void mpColl_8004220C(CollData* cd, HSD_GObj* gobj, f32 arg1, f32 arg2,
                     f32 arg3, f32 arg4);
/* 04CBC0 */ bool mpColl_8004CBC0(CollData*);
/* 04CBE8 */ void mpColl_8004CBE8(CollData*);
/* 0443C4 */ bool mpColl_800443C4(CollData* cd, int* p_ledge_id);
/* 044164 */ bool mpColl_80044164(CollData* cd, int* p_ledge_id);
/* 4D64A0 */ extern s32 mpColl_804D64A0;
/* 4D64A4 */ extern s32 mpColl_804D64A4;
/* 4D64A8 */ extern s32 mpColl_804D64A8;
/* 4D64AC */ extern u32 mpColl_804D64AC;

#endif
