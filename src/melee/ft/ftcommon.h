#ifndef MELEE_FT_FTCOMMON_H
#define MELEE_FT_FTCOMMON_H

#include <ctypes.h>

typedef struct _Fighter Fighter;
typedef struct _HSD_GObj HSD_GObj;
typedef struct _HSD_JObj HSD_JObj;
typedef struct _HSD_Joint HSD_Joint;
typedef struct _HSD_AnimJoint HSD_AnimJoint;
typedef struct _Vec Vec;

void func_8007C930(Fighter* fp, f32 result);
void func_8007C98C(Fighter* fp, f32, f32, f32);
void func_8007CA80(Fighter* fp, f32, f32);
void func_8007CADC(Fighter* fp, f32, f32, f32);
void func_8007CB74(HSD_GObj* fighter_gobj);
HSD_GObj* func_8007CC1C(HSD_GObj* fighter_gobj);
void func_8007CC78(Fighter* fp, f32 max);
void func_8007CCA0(Fighter* fp, f32);
void func_8007CCE8(Fighter* fp);
f32 func_8007CD6C(f32 value, f32 decrement);
f32 func_8007CDA4(Fighter* fp);
f32 func_8007CDF8(Fighter* fp);
void func_8007CE4C(Fighter* fp, f32 value);
void func_8007CE94(Fighter* fp, f32 value);
void func_8007CEF4(Fighter* fp);
BOOL func_8007CF58(Fighter* fp);
BOOL func_8007D050(Fighter* fp, f32);
void func_8007D140(Fighter* fp, f32, f32, f32);
void func_8007D174(Fighter* fp, f32, f32, f32, f32);
void func_8007D268(Fighter* fp);
void func_8007D28C(Fighter* fp, f32);
void func_8007D2E8(Fighter* fp, f32, f32);
void func_8007D344(Fighter* fp, f32, f32, f32);
void func_8007D3A8(Fighter* fp, f32, f32, f32);
void func_8007D440(Fighter* fp, f32);
void func_8007D468(Fighter* fp);
void func_8007D494(Fighter* fp, f32, f32);
void func_8007D4B8(Fighter* fp);
void func_8007D4E4(Fighter* fp);
void ftComm_ClampFallSpeed(Fighter* fp, f32);
void func_8007D508(Fighter* fp, f32, f32);
BOOL func_8007D528(Fighter* fp);
void func_8007D5BC(Fighter* fp);
void func_8007D5D4(Fighter* fp);
void func_8007D60C(Fighter* fp);
void func_8007D698(Fighter* fp);
void func_8007D6A4(Fighter* fp);
void func_8007D780(Fighter* fp);
void func_8007D7FC(Fighter* fp);
void func_8007D92C(HSD_GObj* fighter_gobj);
f32 func_8007D964(Fighter* fp);
f32 func_8007D99C(Fighter* fp);
f32 func_8007D9D4(Fighter* fp);
void func_8007D9FC(Fighter* fp);
void func_8007DA24(Fighter* fp);
f32 func_8007DA74(s32, u32, f32);
void func_8007DB24(HSD_GObj* fighter_gobj);
void func_8007DB58(HSD_GObj* fighter_gobj);

/* TODO
* void func_8007DBCC(Fighter* fp, BOOL, f32);
*/

s32 func_8007DC08(Fighter* fp, f32);
void func_8007DD7C(HSD_GObj* fighter_gobj, Vec*);
void func_8007DFD0();
void func_8007E0E4(HSD_GObj* fighter_gobj);
HSD_GObj* func_8007E2A4(HSD_GObj* fighter_gobj);
void ftCommon_SetOnGrabCallbacks(Fighter* fp, s16, void (*cb0)(HSD_GObj* fighter_gobj), void (*cb1)(HSD_GObj* fighter_gobj), void (*cb2)(HSD_GObj* fighter_gobj, HSD_GObj* unk_gobj));
void func_8007E2F4(Fighter* fp, s16 value);
void func_8007E2FC(HSD_GObj* fighter_gobj);
void func_8007E358(HSD_GObj* fighter_gobj);
void func_8007E3EC(HSD_GObj* fighter_gobj);
void func_8007E5AC(Fighter* fp);
void func_8007E620(Fighter* fp, HSD_Joint*);
void func_8007E690(Fighter* fp, HSD_AnimJoint*);
void func_8007E6DC(HSD_GObj* fighter_gobj, HSD_GObj* item_gobj, s32);
void func_8007E79C(HSD_GObj* fighter_gobj, s32);
void func_8007E7E4(HSD_GObj* fighter_gobj, s32);
void func_8007E82C(HSD_GObj* fighter_gobj);
void func_8007E83C(HSD_GObj* fighter_gobj, s32, f32 div);
s32 ftGetParasolStatus(HSD_GObj* fighter_gobj);
void func_8007EA90(Fighter* fp, s32);
void func_8007EBAC(Fighter* fp, u32, u32);
void func_8007EC30(u32, u32);
void func_8007ECD4(Fighter* fp, s32);
void func_8007ED2C(Fighter* fp);
void func_8007ED50(Fighter* fp, s32 percent_temp);
void func_8007EE0C(Fighter* fp, s32);
void func_8007EEC8(Fighter* fp, s32, s32);
void func_8007EF5C(Fighter* fp, s32);
void func_8007EFC0(Fighter* fp, u32 value);
void func_8007EFC8(HSD_GObj* fighter_gobj, void (*)(HSD_GObj* fighter_gobj));
void func_8007F578(HSD_GObj* fighter_gobj);
void func_8007F5CC(HSD_GObj* fighter_gobj, s32);
f32 Fighter_GetModelScale(Fighter* fp);
void func_8007F6A4(Fighter* fp, HSD_JObj*);
void func_8007F76C(HSD_GObj* fighter_gobj);
void func_8007F7B4(HSD_GObj* fighter_gobj);
void* func_8007F804(Fighter* fp);
void func_8007F824(HSD_GObj* fighter_gobj);
void func_8007F86C(HSD_GObj* fighter_gobj);
void func_8007F8B4(Fighter* fp, Vec* v);
void func_8007F8E8(HSD_GObj* fighter_gobj);
void func_8007F948(HSD_GObj* fighter_gobj, HSD_GObj* unk_gobj, s32);
void func_8007F9B4(HSD_GObj* fighter_gobj);
void func_8007FA00(HSD_GObj* fighter_gobj);
void func_8007FA58(HSD_GObj* fighter_gobj, HSD_GObj* unk_gobj);
void func_8007FC7C(HSD_GObj* fighter_gobj, f32);
void func_8007FDA0(HSD_GObj* fighter_gobj);
void func_8007FE84(HSD_GObj* fighter_gobj, HSD_GObj* item_gobj, s32, f32);
void func_8007FF74(HSD_GObj* fighter_gobj);
BOOL func_8007FFD8(Fighter* fp, f32);
BOOL func_80080144(Fighter* fp);
void func_80080174();
void func_8008021C(HSD_GObj* fighter_gobj);
void func_8008031C(HSD_GObj* fighter_gobj);
void func_80080460(Fighter* fp);
void func_80080474(Fighter* fp);
void func_80080484(Fighter* fp);
void func_800804A0(Fighter* fp, f32);
f32 func_800804EC(Fighter* fp);
void func_800804FC(Fighter* fp);

#endif
