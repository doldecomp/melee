#ifndef MELEE_FT_CHARA_FTMASTERHAND_FTMASTERHAND_01_H
#define MELEE_FT_CHARA_FTMASTERHAND_FTMASTERHAND_01_H

#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftMh_Init_MotionStateTable[];
extern char ftMh_Init_DatFilename[];
extern char ftMh_Init_DataName[];
extern Fighter_CostumeStrings ftMh_Init_CostumeStrings[];
extern char ftMh_Init_AnimDatFilename[];

void ftMh_Init_OnDeath(HSD_GObj* gobj);
void ftMh_Init_OnLoad(HSD_GObj* gobj);

#endif
