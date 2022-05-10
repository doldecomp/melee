#ifndef _ftmario_h_
#define _ftmario_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftMarioAttributes {
    /* 0x00 */u8 x0_padding[0x04 - 0x0];
	/* 0x04 */f32 x04;
	/* 0x08 */f32 x08;
	/* 0x0C */f32 x0C;
	/* 0x10 */f32 x10;
	/* 0x14 */u32 x14;
    /* 0x18 */u8 x14_padding[0x84 - 0x18];
} ftMarioAttributes;

void ftMario_OnDeath(HSD_GObj* gobj);
void func_800E0920(Fighter* ft);
void ftMario_OnLoad(HSD_GObj* gobj);
void func_800E0A00(HSD_GObj* gobj);
void func_800E0A20(HSD_GObj* gobj, s32 arg1);
void func_800E0B00(HSD_GObj* gobj);
void func_800E0B48(HSD_GObj* gobj);
void func_800E0B90(HSD_GObj* gobj, s32 arg1);
void func_800E0BE4(HSD_GObj* gobj);
void func_800E0C24(HSD_GObj* gobj);
void func_800E0C68(HSD_GObj* gobj);
void func_800E0CAC(s32 arg1, u32* arg2, u32* arg3);
s32 func_800E0CE0(s32 arg0);
int func_800E0D1C(HSD_GObj*);
void func_800E0DA8(HSD_GObj*);
void func_800E0E18(HSD_GObj*);
void func_800E0E54(HSD_GObj*);
void func_800E0E84(HSD_GObj*);
void func_800E0EA4(HSD_GObj*);
void func_800E0EE0(HSD_GObj*);
void func_800E1040(HSD_GObj*);
void func_800E10B0(HSD_GObj*);
void func_800E10EC(HSD_GObj*);
void func_800E111C(void);
void func_800E113C(HSD_GObj*);
void func_800E1178(HSD_GObj*);
void func_800E11E0(HSD_GObj*);
void func_800E1248(HSD_GObj*);
void func_800E132C(HSD_GObj*);
void func_800E1368(HSD_GObj*);
void func_800E13C8(HSD_GObj*);
void func_800E13F8(HSD_GObj*);
void func_800E13F8(HSD_GObj*);
BOOL func_800E1428(HSD_GObj*);
void func_800E1450(HSD_GObj*);
void func_800E14C8(HSD_GObj*);
void func_800E1550(HSD_GObj*);
void func_800E158C(HSD_GObj*);
void func_800E15C8(void);
void func_800E15CC(void);
void func_800E15D0(HSD_GObj*);
void func_800E16E0(HSD_GObj*);
void func_800E1840(HSD_GObj*);
void func_800E187C(HSD_GObj*);

#endif
