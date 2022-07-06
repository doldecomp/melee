#ifndef _ftfalco_h_
#define _ftfalco_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

void ftFalco_OnDeath(HSD_GObj*);
void ftFalco_OnItemPickup(HSD_GObj*, BOOL);
void ftFalco_StoreHeldItem(HSD_GObj*);
void ftFalco_RestoreHeldItem(HSD_GObj*);
void ftFalco_OnItemDrop(HSD_GObj*, BOOL);
void ftFalco_OnLoad(HSD_GObj*);
void func_80149D3C(HSD_GObj*);
void ftFalco_OnKnockbackEnter(HSD_GObj*);
void ftFalco_OnKnockbackExit(HSD_GObj*);

#endif
