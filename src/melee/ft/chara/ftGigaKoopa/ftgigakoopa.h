#ifndef _ftgigakoopa_h_
#define _ftgigakoopa_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

extern ActionState ftGigaKoopa_MotionStateTable[];
extern ActionState lbl_803D38C8[];
extern char lbl_803D38E8[];
extern char lbl_803D38F4[];
extern Fighter_CostumeStrings lbl_803D3988[];
extern char lbl_803D3948[];
extern Fighter_DemoStrings lbl_803D3954;

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
unk_t ftGigaKoopa_GetMotionFileString(enum_t);

#endif
