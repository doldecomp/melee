#ifndef MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER2_NANA_H
#define MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER2_NANA_H

#include <melee/ft/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

extern ActionState as_table_nana[];
extern char lbl_803CDB78[];
extern char lbl_803CDB84[];
extern Fighter_CostumeStrings lbl_803CDD2C[];
extern char lbl_803CDCA0[];
extern Fighter_DemoStrings lbl_803CDD1C;

void ftNana_OnDeath(HSD_GObj* fighter_gobj);
void ftNana_80122FAC(HSD_GObj* fighter_gobj);
void ftNana_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftNana_OnLoad(HSD_GObj* fighter_gobj);

#endif
