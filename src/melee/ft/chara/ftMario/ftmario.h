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
    /* 0x18 */f32 x18;
    /* 0x1C */f32 x1C;
    /* 0x20 */f32 x20;
    /* 0x24 */f32 x24;
    /* 0x28 */f32 x28;
    /* 0x2C */f32 x2C;
    /* 0x30 */f32 x30;
    /* 0x34 */f32 x34;
    /* 0x38 */f32 x38;
    /* 0x3C */u8 x3C_padding[0x40 - 0x3C];
    /* 0x40 */f32 x40;
    /* 0x44 */u8 x44_padding[0x50 - 0x44];
    /* 0x50 */s32 x50;
    /* 0x54 */f32 x54;
    /* 0x58 */u8 x58_padding[0x84 - 0x58];
} ftMarioAttributes;

void ftMario_OnDeath(HSD_GObj*);
void ftMario_OnLoadForDrMario(Fighter*);
void ftMario_OnLoad(HSD_GObj*);
void func_800E0A00(HSD_GObj*);
void func_800E0A20(HSD_GObj*, s32);
void func_800E0B00(HSD_GObj*);
void func_800E0B48(HSD_GObj*);
void func_800E0B90(HSD_GObj*, s32);
void func_800E0BE4(HSD_GObj*);
void func_800E0C24(HSD_GObj*);
void func_800E0C68(HSD_GObj*);
void func_800E0CAC(s32, u32*, u32*);
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
void func_800E18B8(HSD_GObj*);
void func_800E198C(HSD_GObj*);

#endif
