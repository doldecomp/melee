#ifndef MELEE_FT_FTANIM_H
#define MELEE_FT_FTANIM_H

#include "ft/forward.h"

#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

void ftAnim_8006E9B4(Fighter_GObj*);
void ftAnim_8006EBA4(Fighter_GObj*);
void ftAnim_8006EBE8(Fighter_GObj* gobj, f32, f32, f32);
void ftAnim_8006F0FC(Fighter_GObj* gobj, f32);
void ftAnim_SetAnimRate(Fighter_GObj*, f32);
bool ftAnim_IsFramesRemaining(Fighter_GObj*);
f32 ftAnim_8006F484(void*);
void ftAnim_8006FE48(Fighter_GObj*);
void ftAnim_80070308(Fighter_GObj*);
void ftAnim_800704F0(Fighter_GObj*, s32, f32);
void ftAnim_80070654(Fighter_GObj*);
void ftAnim_80070758(HSD_JObj*);
void ftAnim_8007077C(Fighter_GObj*);
void ftAnim_ApplyPartAnim(Fighter_GObj*, s32, s32, f32);
void ftAnim_80070C48(Fighter_GObj*, s32);
void ftAnim_80070CC4(Fighter_GObj*, s32);
void ftAnim_80070E74(Fighter_GObj*);
void ftAnim_80070F28(Fighter_GObj*);
void ftAnim_80070FB4(Fighter_GObj*, s32, s32);
bool ftAnim_80070FD0(Fighter*);
void ftAnim_GetNextJointInTree(HSD_Joint** pjoint, s32* pdepth);
void ftAnim_8006FA58(Fighter* fp, int, int item);
void ftAnim_80070010(Fighter* fp, int, int item, f32, f32);
void ftAnim_8006FF74(Fighter* fp, int);
void ftAnim_8006FE9C(Fighter* fp, int, f32, f32);
void ftAnim_80070108(Fighter* fp, int, int item, f32, f32);
void ftAnim_8006FB88(Fighter* fp, int, HSD_Joint* joint);
void ftAnim_80070710(HSD_JObj* joint, f32);
void ftAnim_8006F4C8(Fighter* fp, int, u32);
/* 06EED4 */ /* static */ UNK_RET ftAnim_8006EED4(UNK_PARAMS);

#endif
