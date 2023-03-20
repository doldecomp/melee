#ifndef MELEE_FT_CHARA_FTMASTERHAND_FTMASTERHAND_01_H
#define MELEE_FT_CHARA_FTMASTERHAND_FTMASTERHAND_01_H

#include "ft/types.h"

#include <baselib/forward.h>

extern ActionState as_table_masterhand[];
extern char lbl_803D4070[];
extern char lbl_803D407C[];
extern Fighter_CostumeStrings lbl_803D40C4[];
extern char lbl_803D40B8[];

void ftMasterhand_OnDeath(HSD_GObj* gobj);
void ftMasterhand_OnLoad(HSD_GObj* gobj);

#endif
