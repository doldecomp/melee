#ifndef _ftgigakoopa_h_
#define _ftgigakoopa_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

extern ActionState as_table_gkoopa[];
extern ActionState lbl_803D38C8[];
extern char lbl_803D38E8[];
extern char lbl_803D38F4[];
extern Fighter_CostumeStrings lbl_803D3988[];
extern char lbl_803D3948[];
extern Fighter_DemoStrings lbl_803D3954;

void ftGKoopa_OnDeath(HSD_GObj*);
void func_8014F698(HSD_GObj*);
void ftGKoopa_OnLoad(HSD_GObj*);
void ftGKoopa_OnItemPickup(HSD_GObj*, bool);
void ftGKoopa_OnItemInvisible(HSD_GObj*);
void ftGKoopa_OnItemVisible(HSD_GObj*);
void ftGKoopa_OnItemDrop(HSD_GObj*, bool);
void ftGKoopa_LoadSpecialAttrs(HSD_GObj*);
void ftGKoopa_OnKnockbackEnter(HSD_GObj*);
void ftGKoopa_OnKnockbackExit(HSD_GObj*);
void func_8014F98C(s32, s32*, s32*);
char* ftGigaKoopa_GetMotionFileString(enum_t);

#endif
