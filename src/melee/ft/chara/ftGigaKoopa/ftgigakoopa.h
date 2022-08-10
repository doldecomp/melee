#ifndef _ftgigakoopa_h_
#define _ftgigakoopa_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

void ftGKoopa_OnDeath(HSD_GObj*);
void func_8014F698(HSD_GObj*);
void ftGKoopa_OnLoad(HSD_GObj*);
void ftGKoopa_OnItemPickup(HSD_GObj*, BOOL);
void ftGKoopa_OnItemInvisible(HSD_GObj*);
void ftGKoopa_OnItemVisible(HSD_GObj*);
void ftGKoopa_OnItemDrop(HSD_GObj*, BOOL);
void ftGKoopa_LoadSpecialAttrs(HSD_GObj*);
void ftGKoopa_OnKnockbackEnter(HSD_GObj*);
void ftGKoopa_OnKnockbackExit(HSD_GObj*);
void func_8014F98C(s32, s32*, s32*);
s32 func_8014F9A4(s32);

#endif
