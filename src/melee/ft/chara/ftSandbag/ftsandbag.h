#ifndef _ftsandbag_h_
#define _ftsandbag_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

extern ActionState as_table_sandbag[];
extern char lbl_803D39B8[];
extern char lbl_803D39C4[];

void ftSandbag_OnDeath(HSD_GObj*);
void ftSandbag_OnLoad(HSD_GObj* gobj);
void func_8014FA30(Fighter* fp);
void ftSandbag_LoadSpecialAttrs(HSD_GObj* gobj);

void ftSandbag_OnKnockbackEnter(HSD_GObj*);
void ftSandbag_OnKnockbackExit(HSD_GObj*);

void func_8014FBA4(HSD_GObj* gobj);

void func_8014FC20(HSD_GObj*);
void func_8014FC24(HSD_GObj*);

void func_8014FC28(HSD_GObj* gobj);
void func_8014FC48(HSD_GObj* gobj);

#endif
