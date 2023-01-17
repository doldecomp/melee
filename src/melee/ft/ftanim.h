#ifndef MELEE_FT_FTANIM_H
#define MELEE_FT_FTANIM_H

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

void func_8006E9B4(HSD_GObj*);
void func_8006EBA4(HSD_GObj*);
void func_8006EBE8(HSD_GObj* fighter_gobj, f32, f32, f32);
void func_8006F0FC(HSD_GObj* fighter_gobj, f32);
void ftAnim_SetAnimRate(HSD_GObj*, f32);
bool ftAnim_IsFramesRemaining(HSD_GObj*);
f32 func_8006F484(void*);
void func_8006FE48(HSD_GObj*);
void func_80070308(HSD_GObj*);
void func_800704F0(HSD_GObj*, s32, f32);
void func_80070654(HSD_GObj*);
void func_80070758(struct _HSD_JObj*);
void func_8007077C(HSD_GObj*);
void ftAnim_ApplyPartAnim(HSD_GObj*, s32, s32, f32);
void func_80070C48(HSD_GObj*, s32);
void func_80070CC4(HSD_GObj*, s32);
void func_80070E74(HSD_GObj*);
void func_80070F28(HSD_GObj*);
void func_80070FB4(HSD_GObj*, s32, s32);
bool func_80070FD0(struct _Fighter*);
void Fighter_GetNextJointInTree(HSD_Joint** pjoint, s32* pdepth);

#endif
