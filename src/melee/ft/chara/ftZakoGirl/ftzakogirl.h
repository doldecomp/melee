#ifndef _ftzakogirl_h_
#define _ftzakogirl_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

extern char lbl_803D3568[];
extern char lbl_803D3574[];
extern Fighter_CostumeStrings lbl_803D35D8[];
extern char lbl_803D35A0[];

void ftZakoGirl_OnDeath(HSD_GObj*);
void ftZakoGirl_OnLoad(HSD_GObj*);
void ftZakoGirl_OnItemPickup(HSD_GObj*, bool);
void ftZakoGirl_OnItemInvisible(HSD_GObj*);
void ftZakoGirl_OnItemVisible(HSD_GObj*);
void ftZakoGirl_OnItemDrop(HSD_GObj*, bool);
void ftZakoGirl_LoadSpecialAttrs(HSD_GObj*);

#endif
