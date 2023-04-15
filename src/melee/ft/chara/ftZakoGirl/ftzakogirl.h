#ifndef _ftzakogirl_h_
#define _ftzakogirl_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern char ftGl_Init_DatFilename[];
extern char ftGl_Init_DataName[];
extern Fighter_CostumeStrings ftGl_Init_CostumeStrings[];
extern char ftGl_Init_AnimDatFilename[];

void ftGl_Init_OnDeath(HSD_GObj*);
void ftGl_Init_OnLoad(HSD_GObj*);
void ftGl_Init_OnItemPickup(HSD_GObj*, bool);
void ftGl_Init_OnItemInvisible(HSD_GObj*);
void ftGl_Init_OnItemVisible(HSD_GObj*);
void ftGl_Init_OnItemDrop(HSD_GObj*, bool);
void ftGl_Init_LoadSpecialAttrs(HSD_GObj*);

#endif
