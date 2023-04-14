#ifndef _ftgigakoopa_h_
#define _ftgigakoopa_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftGigaKoopa_MotionStateTable[];
extern MotionState ftGigaKoopa_803D38C8[];
extern char ftGigaKoopa_803D38E8[];
extern char ftGigaKoopa_803D38F4[];
extern Fighter_CostumeStrings ftGigaKoopa_803D3988[];
extern char ftGigaKoopa_803D3948[];
extern Fighter_DemoStrings ftGigaKoopa_803D3954;

void ftGigaKoopa_OnDeath(HSD_GObj*);
void ftGigaKoopa_8014F698(HSD_GObj*);
void ftGigaKoopa_OnLoad(HSD_GObj*);
void ftGigaKoopa_OnItemPickup(HSD_GObj*, bool);
void ftGigaKoopa_OnItemInvisible(HSD_GObj*);
void ftGigaKoopa_OnItemVisible(HSD_GObj*);
void ftGigaKoopa_OnItemDrop(HSD_GObj*, bool);
void ftGigaKoopa_LoadSpecialAttrs(HSD_GObj*);
void ftGigaKoopa_OnKnockbackEnter(HSD_GObj*);
void ftGigaKoopa_OnKnockbackExit(HSD_GObj*);
void ftGigaKoopa_8014F98C(s32, s32*, s32*);
char* ftGigaKoopa_GetMotionFileString(enum_t);

#endif
