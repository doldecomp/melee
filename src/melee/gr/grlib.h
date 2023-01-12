#ifndef _grtlib_h_
#define _grtlib_h_

#include <melee/gr/stage.h>
#include <melee/lb/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

struct _UnkGeneratorStruct* func_801C96F8(s32, s8, S32Vec3*);
void func_801C97DC(s32, s32, s32);
void func_801C9808(s32, s32, s32);
void func_801C9834(struct _UnkGeneratorStruct* arg0);
void func_801C9854(s32);
void func_801C9874(struct _UnkGeneratorStruct*);
void func_801C98A0(HSD_JObj*);
void func_801C9908(HSD_JObj*);
void func_801C99C0(s32, s32, s32, s32);
Vec3* func_801C9A10(void);
void func_801C9A70(enum_t, Vec3*);
void func_801C9B20(void* arg1, UnkAnimStruct* arg2, void* arg3);
void func_801C9B6C(void*);
void func_801C9B8C(void*);
static void func_801C9BC8(HSD_GObj*);
static void func_801C9C40(HSD_GObj*);
HSD_GObj* func_801C9CEC(s32);
s16 func_801C9E40(void);
void func_801C9E50(s16);
BOOL func_801C9E60(Vec3*);
BOOL func_801C9EE8(void);
Vec3* func_801C9A10(void);

/// @remarks Only called from yorster and inishie1
BOOL func_801C9EE8(void);

#endif
