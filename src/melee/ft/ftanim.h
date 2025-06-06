#ifndef GALE01_06DBF4
#define GALE01_06DBF4

#include <placeholder.h>

#include "ft/forward.h"
#include "it/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

/* 06FE08 */ void ftAnim_8006FE08(Fighter* fp, bool);
/* 06DE00 */ void ftAnim_GetNextJointInTree(HSD_Joint** pjoint, s32* pdepth);
/* 06E9B4 */ void ftAnim_8006E9B4(Fighter_GObj*);
/* 06EBA4 */ void ftAnim_8006EBA4(Fighter_GObj*);
/* 06EBE8 */ void ftAnim_8006EBE8(HSD_GObj* gobj, float, float anim_rate,
                                  float anim_blend_frames);
/* 06EED4 */ void ftAnim_8006EED4(Fighter*, Fighter_Part, Fighter_Part, float,
                                  float);
/* 06F0FC */ void ftAnim_8006F0FC(Fighter_GObj* gobj, float);
/* 06F190 */ void ftAnim_SetAnimRate(Fighter_GObj*, float);
/* 06F238 */ bool ftAnim_IsFramesRemaining(Fighter_GObj*);
/* 06F484 */ float ftAnim_8006F484(void*);
/* 06F4C8 */ void ftAnim_8006F4C8(Fighter* fp, int, lbMthp_8001E8F8_t*);
/* 06FA58 */ void ftAnim_8006FA58(Fighter* fp, bool, HSD_Joint* joint);
/* 06FB88 */ void ftAnim_8006FB88(Fighter* fp, bool, HSD_Joint* joint);
/* 06FE48 */ void ftAnim_8006FE48(Fighter_GObj*);
/* 06FE9C */ void ftAnim_8006FE9C(Fighter* fp, int, float, float);
/* 06FF74 */ void ftAnim_8006FF74(Fighter* fp, int);
/* 070010 */ void ftAnim_80070010(Fighter* fp, int, HSD_Joint* joint, float,
                                  float);
/* 070108 */ void ftAnim_80070108(Fighter* fp, int, HSD_Joint* joint, float,
                                  float);
/* 070308 */ void ftAnim_80070308(Fighter_GObj*);
/* 0704F0 */ void ftAnim_800704F0(Fighter_GObj*, s32, float);
/* 070654 */ void ftAnim_80070654(Fighter_GObj*);
/* 070710 */ void ftAnim_80070710(HSD_JObj* joint, float);
/* 070734 */ void ftAnim_80070734(HSD_JObj* jobj, float);
/* 070758 */ void ftAnim_80070758(HSD_JObj*);
/* 07077C */ void ftAnim_8007077C(Fighter_GObj*);
/* 070B88 */ void ftAnim_ApplyPartAnim(Fighter_GObj*, s32, s32, float);
/* 070C48 */ void ftAnim_80070C48(Fighter_GObj*, s32);
/* 070CC4 */ void ftAnim_80070CC4(Fighter_GObj*, s32);
/* 070E74 */ void ftAnim_80070E74(Fighter_GObj*);
/* 070F28 */ void ftAnim_80070F28(Fighter_GObj*);
/* 070FB4 */ void ftAnim_80070FB4(Fighter_GObj*, s32, s32);
/* 070FD0 */ bool ftAnim_80070FD0(Fighter*);

#endif
