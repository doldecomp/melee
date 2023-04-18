#ifndef MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER2_NANA_H
#define MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER2_NANA_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftNn_Init_MotionStateTable[];
extern char ftNn_Init_DatFilename[];
extern char ftNn_Init_DataName[];
extern Fighter_CostumeStrings ftNn_Init_CostumeStrings[];
extern char ftNn_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftNn_Init_DemoMotionFilenames;

void ftNn_Init_OnDeath(HSD_GObj* gobj);
void ftNn_Init_80122FAC(HSD_GObj* gobj);
void ftNn_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftNn_Init_OnLoad(HSD_GObj* gobj);

#endif
