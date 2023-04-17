#ifndef _ftzakoboy_h_
#define _ftzakoboy_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

typedef struct _ftZakoboyAttributes {
    s32 x0;
} ftZakoboyAttributes;

extern char ftBo_Init_DatFilename[];
extern char ftBo_Init_DataName[];
extern Fighter_CostumeStrings ftBo_Init_CostumeStrings[];
extern char ftBo_Init_AnimDatFilename[];

void ftBo_Init_OnDeath(HSD_GObj*);
void ftBo_Init_OnItemPickup(HSD_GObj*, bool);
void ftBo_Init_OnItemInvisible(HSD_GObj*);
void ftBo_Init_OnItemVisible(HSD_GObj*);
void ftBo_Init_OnItemDrop(HSD_GObj*, bool);
void ftBo_Init_OnLoad(HSD_GObj*);
void ftBo_Init_LoadSpecialAttrs(HSD_GObj*);

#endif
