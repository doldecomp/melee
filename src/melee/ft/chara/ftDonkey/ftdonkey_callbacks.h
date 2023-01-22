#ifndef MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H
#define MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H

#include <melee/ft/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

extern ActionState as_table_donkey[];

void ftDonkey_OnDeath(HSD_GObj* fighter_gobj);
void ftDonkey_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftDonkey_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftDonkey_OnItemVisible(HSD_GObj* fighter_gobj);
void ftDonkey_OnItemDrop(HSD_GObj* gobj, bool bool1);
void func_8010D96C(HSD_GObj* fighter_gobj);
void ftDonkey_OnLoad(HSD_GObj* fighter_gobj);
void ftDonkey_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftDonkey_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftDonkey_OnKnockbackExit(HSD_GObj* fighter_gobj);

#endif
