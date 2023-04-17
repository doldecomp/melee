#ifndef _ftsandbag_h_
#define _ftsandbag_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftSb_Init_MotionStateTable[];
extern char ftSb_Init_DatFilename[];
extern char ftSb_Init_DataName[];
extern Fighter_CostumeStrings ftSb_Init_CostumeStrings[];
extern char ftSb_Init_AnimDatFilename[];

void ftSb_Init_OnDeath(HSD_GObj*);
void ftSb_Init_OnLoad(HSD_GObj* gobj);
void ftSb_Init_8014FA30(Fighter* fp);
void ftSb_Init_LoadSpecialAttrs(HSD_GObj* gobj);

void ftSb_Init_OnKnockbackEnter(HSD_GObj*);
void ftSb_Init_OnKnockbackExit(HSD_GObj*);

void ftSb_Init_8014FBA4(HSD_GObj* gobj);

void ftSb_Init_8014FC20(HSD_GObj*);
void ftSb_Init_8014FC24(HSD_GObj*);

void ftSb_Init_8014FC28(HSD_GObj* gobj);
void ftSb_Init_8014FC48(HSD_GObj* gobj);

#endif
