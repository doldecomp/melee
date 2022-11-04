#ifndef MELEE_GR_GROUND_H
#define MELEE_GR_GROUND_H

#include <ctypes.h>

typedef struct _Map Map;
typedef struct _HSD_GObj HSD_GObj;
typedef struct _HSD_JObj HSD_JObj;
typedef struct _HSD_LObj HSD_LObj;
typedef struct _HSD_Joint HSD_Joint;
typedef struct _Vec Vec;
typedef struct _StageInfo StageInfo;

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
static BOOL func_801C0A70(Vec* pos);
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
static void func_801C2BD4(void*);
HSD_GObj* func_801C14D0(s32);
static void func_801C34AC(s32, HSD_JObj*, HSD_Joint*);
static void func_801C28CC(void*, s32);
extern StageInfo stage_info;
BOOL func_801C4E20(void);
BOOL func_801C4DD0(void);
BOOL func_801C4DA0(Vec*, f32*);
void func_801C2374(HSD_LObj* lobj);
unk_t func_801C49B4(void);
void func_801C4368(f32*, f32*);
s32 func_801C5794(void);
BOOL func_801C5700(s32 i);
unk_t func_801C49F8(void); // get stage's "yakumono" ("about"?) param
HSD_JObj* func_801C3FA4(HSD_GObj* gobj, s32 depth);
HSD_JObj* func_801C2CF4(s32 i);
HSD_GObj* func_801C2BA4(s32 i);
void func_801C95C4(HSD_GObj* map_gobj);
void func_801C5AA4(BOOL);
void func_801C42AC(void);
s32 func_801C4210(void);
void func_801C3BB4(void);
void func_801C39C0(void);
BOOL func_801C2ED0(HSD_JObj* jobj, s32 map_id);
BOOL func_801C2D24(s32, Vec*);

#endif
