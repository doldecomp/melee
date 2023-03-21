#ifndef _ftganon_h_
#define _ftganon_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState as_table_ganon[];
extern char lbl_803D2CD8[];
extern char lbl_803D2CE4[];
extern Fighter_CostumeStrings lbl_803D2E40[];
extern char lbl_803D2DB4[];
extern Fighter_DemoStrings lbl_803D2E30;

void ftGanon_OnDeath(HSD_GObj*);
void ftGanon_OnItemPickup(HSD_GObj*, bool);
void ftGanon_OnItemInvisible(HSD_GObj*);
void ftGanon_OnItemVisible(HSD_GObj*);
void ftGanon_OnItemDrop(HSD_GObj*, bool);
void ftGanon_OnLoad(HSD_GObj*);
void ftGanon_LoadSpecialAttrs(HSD_GObj*);
void ftGanon_OnKnockbackEnter(HSD_GObj*);
void ftGanon_OnKnockbackExit(HSD_GObj*);
void func_800E4B00(HSD_GObj*);
void func_800E4B60(HSD_GObj*);
void func_800E4BF8(HSD_GObj*);
void func_800E4E1C(HSD_GObj*);
void func_800E4EE8(HSD_GObj*);
void func_800E4F48(HSD_GObj*);
void func_800E4FDC(HSD_GObj*);
void func_800E50D8(HSD_GObj*);
void func_800E51F8(HSD_GObj*);
void func_800E5234(HSD_GObj*);
void func_800E5238(HSD_GObj*);
void func_800E523C(HSD_GObj*);
void func_800E5310(HSD_GObj*);
void func_800E5384(HSD_GObj*);
void func_800E5388(HSD_GObj*);
void func_800E54B8(HSD_GObj*);
void func_800E415C(HSD_GObj*);
void func_800E4408(HSD_GObj*);
void func_800E46B8(HSD_GObj*);
void func_800E4268(HSD_GObj*);
void func_800E449C(HSD_GObj*);
void func_800E47B0(HSD_GObj*);
void func_800E42E0(HSD_GObj*);
void func_800E45E4(HSD_GObj*);
void func_800E48BC(HSD_GObj*);
void func_800E4354(HSD_GObj*);
void func_800E4618(HSD_GObj*);
void func_800E493C(HSD_GObj*);
void func_800E4390(HSD_GObj*);
void func_800E4678(HSD_GObj*);
void func_800E495C(HSD_GObj*);
void func_800E42A4(HSD_GObj*);
void func_800E455C(HSD_GObj*);
void func_800E4838(HSD_GObj*);
void func_800E43CC(HSD_GObj*);
void func_800E4698(HSD_GObj*);
void func_800E49DC(HSD_GObj*);

#endif
