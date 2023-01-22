#ifndef MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER2_NANA_H
#define MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER2_NANA_H

#include <melee/ft/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

extern ActionState as_table_nana[];

void ftNana_OnDeath(HSD_GObj* fighter_gobj);
void ftNana_80122FAC(HSD_GObj* fighter_gobj);
void ftNana_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftNana_OnLoad(HSD_GObj* fighter_gobj);

#endif
