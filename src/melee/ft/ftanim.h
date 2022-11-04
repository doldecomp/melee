#ifndef MELEE_FT_FTANIM_H
#define MELEE_FT_FTANIM_H

#include <ctypes.h>

typedef struct _HSD_GObj HSD_GObj;

unk_t func_8006EED4();
unk_t func_80070734();
unk_t func_8006DE00();
void func_8006E9B4(HSD_GObj* fighter_gobj);
void func_8006EBA4(HSD_GObj* fighter_gobj);
void func_8006EBE8(HSD_GObj* fighter_gobj, f32, f32, f32);
void func_8006F0FC(HSD_GObj* fighter_gobj, f32);
void ftAnim_SetAnimRate(HSD_GObj* fighter_gobj, f32);
BOOL ftAnim_IsFramesRemaining(HSD_GObj* fighter_gobj);
f32 func_8006F484(HSD_GObj* fighter_gobj);

#endif
