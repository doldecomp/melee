#ifndef MELEE_FT_CHARA_FTSAMUS_FTSAMUS1_H
#define MELEE_FT_CHARA_FTSAMUS_FTSAMUS1_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftSs_Init_MotionStateTable[];
extern char ftSs_Init_DatFilename[];
extern char ftSs_Init_DataName[];
extern Fighter_CostumeStrings ftSs_Init_CostumeStrings[];
extern char ftSs_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftSs_Init_DemoMotionFilenames;

void ftSs_Init_OnDeath(HSD_GObj* gobj);
void ftSs_Init_OnLoad(HSD_GObj* gobj);
void ftSs_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftSs_Init_OnItemInvisible(HSD_GObj* gobj);
void ftSs_Init_OnItemVisible(HSD_GObj* gobj);
void ftSs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftSs_Init_UnkMotionStates4(HSD_GObj* gobj);
void ftSs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftSs_Init_80128770(HSD_AObj* gobj, f32 rate);
void ftSs_Init_CreateThrowGrappleBeam(HSD_GObj* gobj, s32 motion_state,
                                      f32 anim_speed);

#endif
