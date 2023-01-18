#ifndef MELEE_FT_CHARA_FTPEACH_FTPEACH_H
#define MELEE_FT_CHARA_FTPEACH_FTPEACH_H

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct _ftPeachAttributes {
    f32 unk0;
    f32 unk4;
    u8 padding[0xB8];
} ftPeachAttributes;

void ftPeach_OnDeath(HSD_GObj* gobj);

s32 ftPeach_8011BA20(Fighter* fp);

void ftPeach_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftPeach_OnKnockbackExit(HSD_GObj* fighter_gobj);
void ftPeach_OnLoad(HSD_GObj* gobj);
void ftPeach_8011B704(HSD_GObj* fighter_gobj);
void ftPeach_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftPeach_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftPeach_OnItemVisible(HSD_GObj* fighter_gobj);
void ftPeach_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1);
void ftPeach_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftPeach_8011B93C(HSD_GObj* fighter_gobj);

#endif
