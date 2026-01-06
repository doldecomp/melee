#ifndef MELEE_FTANIM_H
#define MELEE_FTANIM_H

#include "ft/types.h"

#include <melee/ft/forward.h>
#include <melee/it/forward.h>
#include <melee/lb/forward.h>

/* 06DBF4 */ void ftAnim_GetNextAnimJointInTree(HSD_AnimJoint**, int*);
/* 06DCF4 */ void ftAnim_GetNextMatAnimJointInTree(HSD_MatAnimJoint**, int*);
/* 06DE00 */ void ftAnim_GetNextJointInTree(HSD_Joint**, s32* pdepth);
/* 06DF0C */ void ftAnim_8006DF0C(Fighter*);
/* 06E054 */ void ftAnim_8006E054(Fighter*, HSD_JObj*, HSD_JObj*, HSD_JObj*);
/* 06E7B8 */ void ftAnim_8006E7B8(Fighter*, int);
/* 06E9B4 */ void ftAnim_8006E9B4(Fighter_GObj*);
/* 06EBA4 */ void ftAnim_8006EBA4(Fighter_GObj*);
/* 06EBE8 */ void ftAnim_8006EBE8(HSD_GObj*, float, float anim_rate,
                                  float anim_blend_frames);
/* 06EDD0 */ void ftAnim_8006EDD0(Fighter*, int, float, float);
/* 06EED4 */ void ftAnim_8006EED4(Fighter*, Fighter_Part, FigaTree*, float,
                                  float);
/* 06F0FC */ void ftAnim_8006F0FC(Fighter_GObj*, float anim_rate);
/* 06F190 */ void ftAnim_SetAnimRate(Fighter_GObj*, float);
/* 06F238 */ bool ftAnim_IsFramesRemaining(Fighter_GObj*);
/* 06F368 */ bool ftAnim_8006F368(Fighter*, Fighter_Part);
/* 06F3DC */ float ftAnim_8006F3DC(Fighter_GObj*);
/* 06F484 */ float ftAnim_8006F484(Fighter_GObj*);
/* 06F4C8 */ void ftAnim_8006F4C8(Fighter*, int, FigaTree*);
/* 06F628 */ void ftAnim_8006F628(Fighter*, Fighter_Part, bool);
/* 06F7C8 */ void ftAnim_8006F7C8(Fighter*, Fighter_Part, int, FigaTree*);
/* 06F954 */ void ftAnim_8006F954(Fighter*, Fighter_Part, bool,
                                  FigaTree* unused);
/* 06F994 */ HSD_Joint* ftAnim_8006F994(Fighter*, HSD_JObj*, HSD_Joint*);
/* 06FA58 */ void ftAnim_8006FA58(Fighter*, Fighter_Part, HSD_Joint*);
/* 06FB88 */ void ftAnim_8006FB88(Fighter*, bool, HSD_Joint*);
/* 06FCE4 */ void ftAnim_8006FCE4(Fighter*, bool);
/* 06FE08 */ void ftAnim_8006FE08(Fighter*, bool);
/* 06FE48 */ void ftAnim_8006FE48(Fighter_GObj*);
/* 06FE9C */ void ftAnim_8006FE9C(Fighter*, int start_idx, float, float);
/* 06FF74 */ void ftAnim_8006FF74(Fighter*, int start_idx);
/* 070010 */ void ftAnim_80070010(Fighter*, int, float, float, HSD_Joint*);
/* 070108 */ void ftAnim_80070108(Fighter*, int, float, float, HSD_Joint*);
/* 070200 */ void ftAnim_80070200(Fighter*, ftData_x8_x8*, CostumeTObjList*,
                                  DObjList*);
/* 070308 */ void ftAnim_80070308(Fighter_GObj*);
/* 070458 */ void ftAnim_80070458(Fighter*, CostumeTObjList*, u32 tobj_idx,
                                  float frame);
/* 0704F0 */ void ftAnim_800704F0(Fighter_GObj*, int tobj_idx, float frame);
/* 0705E0 */ void ftAnim_800705E0(CostumeTObjList* tobj_list);
/* 070654 */ void ftAnim_80070654(Fighter_GObj*);
/* 070710 */ void ftAnim_80070710(HSD_JObj*, float frame);
/* 070734 */ void ftAnim_80070734(HSD_JObj*, float frame);
/* 070758 */ void ftAnim_80070758(HSD_JObj*);
/* 07077C */ void ftAnim_8007077C(Fighter_GObj*);
/* 0707B0 */ void ftAnim_800707B0(Fighter_GObj*);
/* 070904 */ void ftAnim_80070904(Fighter*, int start_idx, HSD_AnimJoint*);
/* 070A10 */ void ftAnim_80070A10(Fighter*, Fighter_Part, FigaTree*);
/* 070B88 */ void ftAnim_ApplyPartAnim(Fighter_GObj*, s32, s32, float);
/* 070C48 */ void ftAnim_80070C48(Fighter_GObj*, s32);
/* 070CC4 */ void ftAnim_80070CC4(Fighter_GObj*, int);
/* 070E74 */ void ftAnim_80070E74(Fighter_GObj*);
/* 070F28 */ void ftAnim_80070F28(Fighter_GObj*);
/* 070FB4 */ void ftAnim_80070FB4(Fighter_GObj*, s32, s32);
/* 070FD0 */ bool ftAnim_80070FD0(Fighter*);

#endif
