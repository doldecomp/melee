#ifndef _grtlib_h_
#define _grtlib_h_

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/gr/stage.h>
#include <melee/lb/types.h>

struct UnkGeneratorStruct* grLib_801C96F8(s32, s8, S32Vec3*);
void grLib_801C97DC(s32, s32, HSD_JObj*);
void grLib_801C9808(s32, s32, HSD_JObj*);
void grLib_801C9834(struct UnkGeneratorStruct* arg0);
void grLib_801C9854(s32);
void grLib_801C9874(struct UnkGeneratorStruct*);
void grLib_801C98A0(HSD_JObj*);
void grLib_801C9908(HSD_JObj*);
void grLib_801C99C0(s32, s32, HSD_JObj*, s32);
Vec3* grLib_801C9A10(void);
void grLib_801C9A70(enum_t, Vec3*);
void grLib_801C9B20(void* arg1, UnkAnimStruct* arg2, void* arg3);
void grLib_801C9B6C(void*);
void grLib_801C9B8C(void*);
static void grLib_801C9BC8(HSD_GObj*);
static void grLib_801C9C40(HSD_GObj*);
HSD_GObj* grLib_801C9CEC(s32);
s16 grLib_801C9E40(void);
void grLib_801C9E50(s16);
bool grLib_801C9E60(Vec3*);
bool grLib_801C9EE8(void);
Vec3* grLib_801C9A10(void);

/// @remarks Only called from yorster and inishie1
bool grLib_801C9EE8(void);
bool grLib_801C96E8(HSD_GObj* arg0);

#endif
