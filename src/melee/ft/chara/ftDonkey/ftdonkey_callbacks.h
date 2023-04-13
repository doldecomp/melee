#ifndef MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H
#define MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H

#include <platform.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

extern ActionState ftDonkey_MotionStateTable[];
extern char lbl_803CBDF8[];
extern char lbl_803CBE04[];
extern Fighter_CostumeStrings lbl_803CC020[];
extern char lbl_803CBF88[];
extern Fighter_DemoStrings lbl_803CC010;

void ftDonkey_OnDeath(HSD_GObj* fighter_gobj);
void ftDonkey_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftDonkey_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftDonkey_OnItemVisible(HSD_GObj* fighter_gobj);
void ftDonkey_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftDonkey_8010D96C(HSD_GObj* fighter_gobj);
void ftDonkey_OnLoad(HSD_GObj* fighter_gobj);
void ftDonkey_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftDonkey_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftDonkey_OnKnockbackExit(HSD_GObj* fighter_gobj);

#endif
