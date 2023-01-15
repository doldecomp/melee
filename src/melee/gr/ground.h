#ifndef _ground_h_
#define _ground_h_

#include <melee/gr/types.h>
#include <sysdolphin/baselib/gobj.h>

static void func_801BFFA8(void);
static void func_801BFFAC(bool);
static void func_801C1E94(void);
void func_801C3880(f32);
void func_801C3890(f32);
void func_801C38A0(f32);
void func_801C38AC(f32);
void func_801C38BC(f32 x, f32 y);
void func_801C38D0(f32 tilt, f32 pan, f32, f32);
void func_801C38EC(f32 depth, f32 zoom);
void func_801C3900(f32, f32, f32, f32, f32 up, f32 down, f32 left, f32 right);
void func_801C392C(f32 x, f32 y, f32 z, f32 fov, f32 vert, f32 horz);
void func_801C3950(f32 zoom);
void func_801C3960(f32 ratio);
void func_801C3970(f32 smooth);
void func_801C3980(f32 top);
void func_801C3990(f32 bottom);
void func_801C39A0(f32 left);
void func_801C39B0(f32 right);
static void func_801C1E2C(HSD_GObj*);
static bool func_801C0A70(Vec3* pos);
static void func_801C0C2C(HSD_GObj*);
static bool func_801C24F8(s32, u32, s32*);
void func_801C5544(Map*, s32);
static void func_801C55AC(Map*);
HSD_GObj* func_801C57A4(void);
static void func_801C5878(void);
static void func_801C466C(void);
static void func_801C1CD0(HSD_GObj*);
static void func_801C1D38(HSD_GObj*);
static void func_801C2BBC(HSD_GObj*, s32);
static void func_801C2BD4(void* arg0);
HSD_GObj* func_801C14D0(int);
static void func_801C34AC(s32, struct _HSD_JObj*, struct _HSD_Joint*);
static void func_801C28CC(void*, s32);

f32 func_801C0498(void);
bool func_801C28AC(s32, u32, s32*);
struct _HSD_GObj* func_801C2BA4(s32);
struct _HSD_JObj* func_801C2CF4(s32);
bool func_801C2D24(enum_t, Vec3*);
bool func_801C2ED0(struct _HSD_JObj*, s32);
void func_801C39C0(void);
void func_801C3BB4(void);
struct _HSD_JObj* func_801C3FA4(struct _HSD_GObj*, s32);
s32 func_801C4210(void);
void func_801C42AC(void);

/// Get stage's "yakumono" ("about"?) param
void* func_801C49F8(void);

void func_801C5A84(s32 arg0);
void func_801C5AA4(bool arg0);
bool func_801C3214(int arg0);

/// @param[in] arg0
/// @param[in] arg1
/// @param[out] result
/// @param[in] arg3
void func_801C4B50(s32 arg0, s32 arg1, Vec3* result, f32 arg3);

void func_801C0754(StructPairWithStageID* pair);
void func_801C0800(StructPairWithStageID* pair);
void func_801C0F78(StructPairWithStageID* pair);
void func_801C0FB8(StructPairWithStageID* pair);
void func_801C1074(StructPairWithStageID* pair, s32 arg1);
void func_801C06B8(InternalStageId arg0);
void func_801C2FE0(HSD_GObj* arg0);
void func_801C4A08(HSD_GObj* gobj);
void func_801C10B8(HSD_GObj* arg0, HSD_GObjEvent arg1);

#endif
