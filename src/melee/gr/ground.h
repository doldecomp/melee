#ifndef _ground_h_
#define _ground_h_

#include "gr/granime.h"
#include "gr/types.h"

#include <baselib/gobj.h>

extern StageInfo stage_info;

static void Ground_801BFFA8(void);
static void Ground_801BFFAC(bool);
static void Ground_801C1E94(void);
void Ground_801C3880(f32);
void Ground_801C3890(f32);
void Ground_801C38A0(f32);
void Ground_801C38AC(f32);
void Ground_801C38BC(f32 x, f32 y);
void Ground_801C38D0(f32 tilt, f32 pan, f32, f32);
void Ground_801C38EC(f32 depth, f32 zoom);
void Ground_801C3900(f32, f32, f32, f32, f32 up, f32 down, f32 left,
                     f32 right);
void Ground_801C392C(f32 x, f32 y, f32 z, f32 fov, f32 vert, f32 horz);
void Ground_801C3950(f32 zoom);
void Ground_801C3960(f32 ratio);
void Ground_801C3970(f32 smooth);
void Ground_801C3980(f32 top);
void Ground_801C3990(f32 bottom);
void Ground_801C39A0(f32 left);
void Ground_801C39B0(f32 right);
static void Ground_801C1E2C(HSD_GObj*);
static bool Ground_801C0A70(Vec3* pos);
static void Ground_801C0C2C(HSD_GObj*);
static bool Ground_801C24F8(s32, u32, s32*);
void Ground_801C5544(Ground*, s32);
static void Ground_801C55AC(Ground*);
HSD_GObj* Ground_801C57A4(void);
static void Ground_801C5878(void);
static void Ground_801C466C(void);
static void Ground_801C1CD0(HSD_GObj*);
static void Ground_801C1D38(HSD_GObj*);
static void Ground_801C2BBC(HSD_GObj*, s32);
static void Ground_801C2BD4(void* arg0);
HSD_GObj* Ground_801C14D0(int);
static void Ground_801C34AC(s32, HSD_JObj*, struct HSD_Joint*);
static void Ground_801C28CC(void*, s32);

f32 Ground_801C0498(void);
bool Ground_801C28AC(s32, u32, s32*);
HSD_GObj* Ground_801C2BA4(s32);
HSD_JObj* Ground_801C2CF4(s32);
bool Ground_801C2D24(enum_t, Vec3*);
bool Ground_801C2ED0(HSD_JObj*, s32);
void Ground_801C39C0(void);
void Ground_801C3BB4(void);
HSD_JObj* Ground_801C3FA4(HSD_GObj*, s32);
s32 Ground_801C4210(void);
void Ground_801C42AC(void);

/// Get stage's "yakumono" ("about"?) param
void* Ground_801C49F8(void);

void Ground_801C5A84(s32 arg0);
void Ground_801C5AA4(bool arg0);
bool Ground_801C3214(int arg0);

/// @param[in] arg0
/// @param[in] arg1
/// @param[out] result
/// @param[in] arg3
void Ground_801C4B50(s32 arg0, s32 arg1, Vec3* result, f32 arg3);

void Ground_801C0754(StructPairWithStageID* pair);
void Ground_801C0800(StructPairWithStageID* pair);
void Ground_801C0F78(StructPairWithStageID* pair);
void Ground_801C0FB8(StructPairWithStageID* pair);
void Ground_801C1074(StructPairWithStageID* pair, s32 arg1);
void Ground_801C06B8(InternalStageId arg0);
void Ground_801C2FE0(HSD_GObj* arg0);
void Ground_801C4A08(HSD_GObj* gobj);
void Ground_801C10B8(HSD_GObj* arg0, HSD_GObjEvent arg1);

HSD_GObj* Ground_801C1A20(HSD_Joint* arg0, s32 arg1);
void Ground_801BFFB0(void);
void Ground_801C1D6C(u32 arg0);
u32 Ground_801C1D84(void);
u32 Ground_801C1D98(void);
u32 Ground_801C1DAC(void);
u32 Ground_801C1DC0(void);
s16 Ground_801C1DD4(void);
void Ground_801C1DE4(s32* arg0, s32* arg1);
void Ground_801C1E00(s32 arg0);
s32 Ground_801C1E18(void);
void* Ground_801C1E84(void);
void Ground_801C1FFC(void);
void Ground_801C205C(GXColor* color);
bool Ground_801C2090(GXColor* color);
f32 Ground_801C20D0(void);
void Ground_801C2374(HSD_LObj* lobj);
s32 Ground_801C247C(s32 arg0, s32 arg1);
void Ground_801C0378(void);
u8* Ground_801C2AD8(void);
f32 Ground_801C2AE8(s32 arg0);
void Ground_801C0478(void* ptr);
bool Ground_801C2C8C(void* arg0);
void Ground_801C2D0C(s32 i, HSD_JObj* jobj);
void Ground_801C04BC(f32 arg8);
bool Ground_801C3128(s32 arg0, void (*arg1)(s16));
s32 Ground_801C0508(void);
bool Ground_801C3260(s32 arg0);
void Ground_801C32AC(s32 arg0);
void Ground_801C052C(s32* arg0);
s32 Ground_801C32D4(s32 arg0, s32 arg1);
s32 Ground_801C33C0(s32 arg0, s32 arg1);
void Ground_801C0544(s32* arg0);
void Ground_801C055C(s32* arg0);
void Ground_801C0574(s32* arg0);
void Ground_801C058C(s32* arg0);
void Ground_801C05A4(s32* arg0);
void Ground_801C36F4(s32 map_id, HSD_JObj* jobj, void* unk);
void Ground_801C05BC(s32* arg0);
void Ground_801C05D4(s32* arg0);
void Ground_801C05EC(s32* arg0);
s32* Ground_801C0604(void);
s32* Ground_801C0618(void);
s32* Ground_801C062C(void);
s32* Ground_801C0640(void);
s32 Ground_801C3D44(s32 arg0, f32 arg8, f32 arg9);
s32 Ground_801C3DB4(s32 arg0, f32 arg8, f32 arg9);
s32* Ground_801C0654(void);
f32 Ground_801C3F20(HSD_JObj* arg0);
s32* Ground_801C0668(void);
s32* Ground_801C067C(void);
s32* Ground_801C0690(void);
HSD_JObj* Ground_801C4100(HSD_JObj* jobj);
s32* Ground_801C06A4(void);
void Ground_801C4338(void);
void Ground_801C4368(f32* arg0, f32* arg1);
void Ground_801C438C(f32 val);
void Ground_801C43A4(unk_t arg0);
bool Ground_801C43C4(void* arg0);
void Ground_801C445C(HSD_LObj* lobj);
HSD_GObj* Ground_801C498C(void);
unk_t Ground_801C49B4(void);
bool Ground_801C4D70(s32 arg0, Vec3* arg1, f32 arg8);
bool Ground_801C4DA0(Vec3* arg0, f32* arg1);
bool Ground_801C4DD0(void);
bool Ground_801C4E20(void);
void Ground_801C4FAC(void);
void Ground_801C53EC(u32 arg0);
void Ground_801C5414(unk_t arg0, s32 arg1);
void Ground_801C5440(Ground* gp, s32 i, u32 arg2);
bool Ground_801C54DC(Ground* gp, s32 i);
void Ground_801C5630(Ground* gp, s32 i, f32 val);
void Ground_801C5694(Ground* gp, s32 i, f32 val);
bool Ground_801C5700(int i);
void Ground_801C5740(s32 arg0);
void Ground_801C5750(void);
s32 Ground_801C5764(void);
s16 Ground_801C5774(void);
void Ground_801C5784(s32 arg0);
s32 Ground_801C5794(void);
HSD_GObj* Ground_801C57C8(void);
f32 Ground_801C57F0(void);
void Ground_801C5800(void);
s32 Ground_801C5840(void);
s32 Ground_801C58E0(s32 arg0, s32 arg1);
int Ground_801C5940(void);
void Ground_801C5A28(void);
void Ground_801C5A60(void);
s32 Ground_801C5A94(void);
bool Ground_801C5ABC(void);
u32 Ground_801C5AD0(s32 i);
void Ground_801C5AEC(Vec3* v, Vec3* arg1, Vec3* arg2, Vec3* arg3);
void Ground_801C1154(void);
void Ground_801C1158(void);
void Ground_801C11AC(HSD_GObj* gobj);
HSD_JObj* Ground_801C13D0(s32 arg0, s32 depth);
void Ground_801C4E70(HSD_JObj* arg0, HSD_JObj* arg1, HSD_JObj* arg2,
                     HSD_JObj* arg3, HSD_JObj* arg4, HSD_JObj* arg5);

#define GET_GROUND(gobj) ((Ground*) HSD_GObjGetUserData(gobj))

static inline void Ground_JObjInline1(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
}

#endif
