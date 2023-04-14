#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H

#include <platform.h>
#include "ftCaptain/forward.h"

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftCaptain_MotionStateTable[];
extern char lbl_803C7598[];
extern char lbl_803C75A4[];
extern Fighter_CostumeStrings lbl_803C773C[];
extern char lbl_803C76A0[];
extern Fighter_DemoStrings lbl_803C772C;

void ftCaptain_800E28C8(HSD_GObj* gobj);
void ftCaptain_LoadSpecialAttrs(HSD_GObj* gobj);
void ftCaptain_OnDeath(HSD_GObj* gobj);
void ftCaptain_OnItemDrop(HSD_GObj* gobj, bool);
void ftCaptain_OnItemInvisible(HSD_GObj* gobj);
void ftCaptain_OnItemPickup(HSD_GObj* gobj, bool);
void ftCaptain_OnItemVisible(HSD_GObj* gobj);
void ftCaptain_OnLoad(HSD_GObj* gobj);

#endif
