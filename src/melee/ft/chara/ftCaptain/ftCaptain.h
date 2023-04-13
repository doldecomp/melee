#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H

#include "forward.h"

#include "ft/fighter.h"

#include <baselib/gobj.h>
#include <platform.h>

extern ActionState ftCaptain_MotionStateTable[];
extern char lbl_803C7598[];
extern char lbl_803C75A4[];
extern Fighter_CostumeStrings lbl_803C773C[];
extern char lbl_803C76A0[];
extern Fighter_DemoStrings lbl_803C772C;

void ftCaptain_800E28C8(HSD_GObj* fighter_gobj);
void ftCaptain_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftCaptain_OnDeath(HSD_GObj* fighter_gobj);
void ftCaptain_OnItemDrop(HSD_GObj* fighter_gobj, bool unk1);
void ftCaptain_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftCaptain_OnItemPickup(HSD_GObj* fighter_gobj, bool unk_var);
void ftCaptain_OnItemVisible(HSD_GObj* fighter_gobj);
void ftCaptain_OnLoad(HSD_GObj* fighter_gobj);

#endif
