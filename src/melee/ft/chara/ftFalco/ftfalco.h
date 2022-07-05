#ifndef _ftfalco_h_
#define _ftfalco_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

void ftFalco_OnDeath(HSD_GObj*);
void ftFalco_OnItemPickup(HSD_GObj*, BOOL);
void ftFalco_OnItemInvisible(HSD_GObj*);
void ftFalco_OnItemVisible(HSD_GObj*);
void ftFalco_OnItemRelease(HSD_GObj*, s32);
void ftFalco_OnLoad(HSD_GObj*);
void func_80149D3C(HSD_GObj*);
void func_80149D5C(HSD_GObj*);
void func_80149DC8(HSD_GObj*);

#endif
