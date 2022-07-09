#ifndef _ftganon_h_
#define _ftganon_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

void ftGanon_OnDeath(HSD_GObj*);
void ftGanon_OnItemPickup(HSD_GObj*, BOOL);
void ftGanon_OnItemInvisible(HSD_GObj*);
void ftGanon_OnItemVisible(HSD_GObj*);
void ftGanon_OnItemDrop(HSD_GObj*, BOOL);
void ftGanon_OnLoad(HSD_GObj*);
void func_8014EE40(HSD_GObj*);
void ftGanon_OnKnockbackEnter(HSD_GObj*);
void ftGanon_OnKnockbackExit(HSD_GObj*);

#endif
