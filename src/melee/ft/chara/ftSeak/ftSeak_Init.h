#ifndef MELEE_FT_CHARA_FTSEAK_FTSEAK_INIT_H
#define MELEE_FT_CHARA_FTSEAK_FTSEAK_INIT_H

#include <platform.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

extern ActionState ftSeak_MotionStateTable[];
extern char lbl_803CC360[];
extern char lbl_803CC36C[];
extern char lbl_803CC4CC[];
extern Fighter_DemoStrings lbl_803CC548;
extern Fighter_CostumeStrings lbl_803CC558[];

void ftSeak_OnDeath(HSD_GObj* fighter_gobj);
void ftSeak_OnLoad(HSD_GObj* fighter_gobj);
void ftSeak_80110198(HSD_GObj* fighter_gobj);
void ftSeak_801101CC(HSD_GObj* fighter_gobj);
void ftSeak_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftSeak_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftSeak_OnItemVisible(HSD_GObj* fighter_gobj);
void ftSeak_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1);
void ftSeak_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftSeak_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftSeak_OnKnockbackExit(HSD_GObj* fighter_gobj);

#endif
