#ifndef _ftemblem_h_
#define _ftemblem_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern ActionState ftRoy_MotionStateTable[];
extern char lbl_803D3280[];
extern char lbl_803D328C[];
extern Fighter_CostumeStrings lbl_803D34A8[];
extern char lbl_803D3410[];
extern Fighter_DemoStrings lbl_803D3498;

void ftRoy_OnDeath(HSD_GObj*);
void ftRoy_OnItemPickup(HSD_GObj*, bool);
void ftRoy_OnItemInvisible(HSD_GObj*);
void ftRoy_OnItemVisible(HSD_GObj*);
void ftRoy_OnItemDrop(HSD_GObj*, bool);
void ftRoy_OnLoad(HSD_GObj*);
void ftRoy_LoadSpecialAttrs(HSD_GObj*);
void ftRoy_OnKnockbackEnter(HSD_GObj*);
void ftRoy_OnKnockbackExit(HSD_GObj*);

#endif
