#ifndef MELEE_FT_CHARA_FTPIKACHU_FTPIKACHU1_H
#define MELEE_FT_CHARA_FTPIKACHU_FTPIKACHU1_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftPk_Init_MotionStateTable[];
extern char ftPk_Init_DatFilename[];
extern char ftPk_Init_DataName[];
extern Fighter_CostumeStrings ftPk_Init_CostumeStrings[];
extern char ftPk_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftPk_Init_DemoMotionFilenames;

void ftPk_Init_LoadSpecialAttrs(HSD_GObj*);

#endif
