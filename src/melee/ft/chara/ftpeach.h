#ifndef _ftpeach_h_
#define _ftpeach_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

#define ITEM_PEACH_UNK 98
#define ITEM_PEACH_TURNIP 99
#define ITEM_PEACH_PARASOL 103
#define ITEM_PEACH_TOAD 104
#define ITEM_PEACH_TOAD_SPORE 111

void ftPeach_OnDeath(HSD_GObj* gobj);

#endif
