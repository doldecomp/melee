#ifndef _ftsandbag_h_
#define _ftsandbag_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

void ftSandbag_OnDeath(void);
void ftSandbag_OnLoad(HSD_GObj* gobj);
void func_8014FA30(Fighter* fighter);
u32 func_8014FB78(HSD_GObj* gobj);

void ftSandbag_OnKnockbackEnter(void);
void ftSandbag_OnKnockbackExit(void);

void func_8014FBA4(HSD_GObj* gobj);

void func_8014FC20(void);
void func_8014FC24(void);

void func_8014FC28(HSD_GObj* gobj);
void func_8014FC48(HSD_GObj* gobj);

#endif
