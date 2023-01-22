#ifndef _ftfalco_h_
#define _ftfalco_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

extern ActionState as_table_falco[];
extern char lbl_803D1CA8[];
extern char lbl_803D1CB4[];

void ftFalco_OnDeath(HSD_GObj*);
void ftFalco_OnItemPickup(HSD_GObj*, bool);
void ftFalco_OnItemInvisible(HSD_GObj*);
void ftFalco_OnItemVisible(HSD_GObj*);
void ftFalco_OnItemDrop(HSD_GObj*, bool);
void ftFalco_OnLoad(HSD_GObj*);
void ftFalco_LoadSpecialAttrs(HSD_GObj*);
void ftFalco_OnKnockbackEnter(HSD_GObj*);
void ftFalco_OnKnockbackExit(HSD_GObj*);

#endif
