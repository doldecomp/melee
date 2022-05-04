#ifndef _ground_h_
#define _ground_h_

#include <melee/gr/stage.h>

#include <sysdolphin/baselib/gobj.h>

static void func_801BFFA8(void);
static void func_801BFFAC(s32);
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
static BOOL func_801C0A70(Vec3* pos);
static void func_801C0C2C();
static BOOL func_801C24F8(s32, u32, s32*);
void func_801C5544(Map*, s32);
static void func_801C55AC(Map*);
HSD_GObj* func_801C57A4(void);
static void func_801C5878(void);
static void func_801C466C(void);
static void func_801C1CD0(HSD_GObj*);
static void func_801C1D38(HSD_GObj*);
static void func_801C2BBC(HSD_GObj*, s32);
static void func_801C2BD4(void* arg0);
HSD_GObj* func_801C14D0(s32);
static void func_801C34AC(s32, struct _HSD_JObj*, struct _HSD_Joint*);
static void func_801C28CC(void*, s32);

#endif
