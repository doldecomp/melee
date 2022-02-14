#ifndef _ftsandbag_h_
#define _ftsandbag_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

void ftSandbag_OnDeath();
void ftSandbag_OnLoad(HSD_GObj* gobj);
void func_8014FA30(Fighter* fighter);
u32 func_8014FB78(HSD_GObj* gobj);

void ftSandbag_OnKnockbackEnter();
void func_8014FBA0();

void func_8014FBA4(HSD_GObj* gobj);

void lbl_8014FC20();
void lbl_8014FC24();

void lbl_8014FC28();
void lbl_8014FC48();

#endif
