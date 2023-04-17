#ifndef _ftpichu_h_
#define _ftpichu_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

typedef struct _ftPichuAttributes {
    /* 0x00 */ u32 x0_padding[(0x14 - 0x0) / 4];
    /* 0x14 */ u32 x14;
    /* 0x14 */ u32 x18;
    /* 0x18 */ u32 x18_padding[(0xDC - 0x1C) / 4];
    /* 0xDC */ u32 xDC;
} ftPichuAttributes;

extern MotionState ftPc_Init_MotionStateTable[];
extern char ftPc_Init_DatFilename[];
extern char ftPc_Init_DataName[];
extern Fighter_CostumeStrings ftPc_Init_CostumeStrings[];
extern char ftPc_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftPc_Init_DemoMotionFilenames;

void ftPc_Init_OnLoad(HSD_GObj*);
void ftPc_Init_OnDeath(HSD_GObj*);
void ftPc_Init_OnItemPickup(HSD_GObj*, bool);
void ftPc_Init_OnItemInvisible(HSD_GObj*);
void ftPc_Init_OnItemVisible(HSD_GObj*);
void ftPc_Init_OnItemDrop(HSD_GObj*, bool);
void ftPc_Init_LoadSpecialAttrs(HSD_GObj*);
void ftPc_Init_OnKnockbackEnter(HSD_GObj*);
void ftPc_Init_OnKnockbackExit(HSD_GObj*);

#endif
