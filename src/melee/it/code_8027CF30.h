#ifndef MELEE_IT_CODE_8027CF30_H
#define MELEE_IT_CODE_8027CF30_H

#include <sysdolphin/baselib/gobj.h>

void func_80294E78(struct _HSD_GObj*, f32);
struct _HSD_GObj* func_8029A748(struct _HSD_GObj*, Vec*, u8, f32);
void func_8029A89C(struct _HSD_GObj*, f32);
void func_8029A8F4(struct _HSD_GObj*, Vec*, f32);
s32 func_802B1DEC(u32);
u32 func_802B1DF8(HSD_GObj*, Vec*, Vec*, s32, s32, s32);
s32 func_802B1FC8(u32);
void func_802B1FE8(u32, Vec*);
void func_802B56E4(u32, Vec*, f32, f32, f32);
void* func_802C8B28(struct _HSD_GObj*, Vec*, u32, f32);
void func_802D8618(s32, Vec*, s32, s32);
u32 func_802F0340(struct _HSD_GObj*, Vec*, Vec*, u32, u32, f32);
void func_802F046C(s32);
void func_802F0AE0(struct _HSD_GObj*, Vec*, Vec*, s32, s32, f32, f32, f32);

/// @todo @c arg0 is likely a @c HSD_GObj*.
void func_802C0DBC(u32 arg0);
u32 func_802C0850(HSD_GObj*, Vec3*, u32, s32, f32 facing_direction);

#endif
