#ifndef MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H
#define MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H

#include "ft/types.h"

#include <baselib/forward.h>
#include <Runtime/platform.h>

extern ActionState as_table_donkey[];
extern char lbl_803CBDF8[];
extern char lbl_803CBE04[];
extern Fighter_CostumeStrings lbl_803CC020[];
extern char lbl_803CBF88[];
extern Fighter_DemoStrings lbl_803CC010;

void ftDonkey_OnDeath(HSD_GObj* gobj);
void ftDonkey_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftDonkey_OnItemInvisible(HSD_GObj* gobj);
void ftDonkey_OnItemVisible(HSD_GObj* gobj);
void ftDonkey_OnItemDrop(HSD_GObj* gobj, bool bool1);
void func_8010D96C(HSD_GObj* gobj);
void ftDonkey_OnLoad(HSD_GObj* gobj);
void ftDonkey_LoadSpecialAttrs(HSD_GObj* gobj);
void ftDonkey_OnKnockbackEnter(HSD_GObj* gobj);
void ftDonkey_OnKnockbackExit(HSD_GObj* gobj);

#endif
