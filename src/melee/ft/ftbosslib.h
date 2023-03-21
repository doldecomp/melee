#ifndef MELEE_FT_FTBOSSLIB_H
#define MELEE_FT_FTBOSSLIB_H

#include "ft/forward.h"
#include "ftMasterHand/forward.h"

#include <baselib/gobj.h>

HSD_GObj* func_8015C3E8(FighterKind arg0);

/// Fighter_GetState(FighterKind)
/// @returns A fighter action state ID.
enum_t func_8015C44C(FighterKind kind);

void func_8015BD20(HSD_GObj*);
void func_8015BD24(s32, f32*, f32, s32, s32, s32);
void func_8015BDB4(HSD_GObj*);
void func_8015BE40(HSD_GObj* gobj, Vec3*, f32*, f32, f32);
void func_8015BF74(HSD_GObj* gobj, f32 x_diff_max);
void func_8015C010(HSD_GObj*, f32);
void func_8015C09C(HSD_GObj* gobj, f32 facing_dir);
void func_8015C190(HSD_GObj*);
void func_8015C208(HSD_GObj*, Vec3*);
HSD_GObj* func_8015C244(HSD_GObj*, Vec3*);
bool func_8015C31C(void);
bool func_8015C3A0(void);
s32 func_8015C4C4(void);
void func_8015C5F8(HSD_GObj*);

bool func_8015C270(void);
bool func_8015C2A8(void);
bool func_8015C2E0(void);
bool func_8015C358(void);
s32 func_8015C530(enum_t arg0);
ftMasterHand_SpecialAttrs* func_8015C6BC(void);
s32 func_8015C74C(void);
s32 func_8015C7EC(void);
s32 func_8015C88C(void);
s32 func_8015C92C(void);
s32 func_8015C9CC(void);
void func_8015CA6C_inline(s32 arg0);
void func_8015CA6C(s32 arg0);
void func_8015CB7C(void);
void func_8015CB9C_inline(Vec3 spC);
void func_8015CB9C(s32 arg0);
void func_8015CC14(void);

#endif
