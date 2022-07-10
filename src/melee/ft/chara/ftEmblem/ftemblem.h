#ifndef _ftemblem_h_
#define _ftemblem_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

void ftRoy_OnDeath(HSD_GObj*);
void ftRoy_OnItemPickup(HSD_GObj*, BOOL);
void ftRoy_OnItemInvisible(HSD_GObj*);
void ftRoy_OnItemVisible(HSD_GObj*);
void ftRoy_OnItemDrop(HSD_GObj*, BOOL);
void ftRoy_OnLoad(HSD_GObj*);
void ftRoy_LoadSpecialAttrs(HSD_GObj*);
void ftRoy_OnKnockbackEnter(HSD_GObj*);
void ftRoy_OnKnockbackExit(HSD_GObj*);

#endif
