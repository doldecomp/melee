#ifndef MELEE_FT_FTANIM_H
#define MELEE_FT_FTANIM_H

#include <dolphin/types.h>

void func_8006E9B4();
void func_8006EBA4(struct _HSD_GObj*);
void func_8006EBE8(struct _HSD_GObj* fighter_gobj, f32, f32, f32);
void func_8006F0FC(struct _HSD_GObj* fighter_gobj, f32);
void ftAnim_SetAnimRate(struct _HSD_GObj*, f32);
BOOL ftAnim_IsFramesRemaining(struct _HSD_GObj*);
f32 func_8006F484(void*);
void func_8006FE48();
void func_80070308();
void func_800704F0(struct _HSD_GObj*, s32, f32);
void func_80070654();
void func_80070758();
void func_8007077C();
void ftAnim_ApplyPartAnim(struct _HSD_GObj*, s32, s32, f32);
void func_80070C48(struct _HSD_GObj*, s32);
void func_80070CC4(struct _HSD_GObj*, s32);
void func_80070E74();
void func_80070F28();
void func_80070FB4(struct _HSD_GObj*, s32, s32);
s32 func_80070FD0(struct _Fighter*);

#endif
