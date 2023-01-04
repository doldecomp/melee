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

#endif
