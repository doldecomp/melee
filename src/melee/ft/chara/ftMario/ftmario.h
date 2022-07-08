#ifndef _ftmario_h_
#define _ftmario_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"
#include "melee/ft/ftcommon.h"

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
    /* 0x3C */f32 x3C;
    /* 0x40 */f32 x40;
    /* 0x44 */f32 x44;
    /* 0x48 */f32 x48;
    /* 0x4C */f32 x4C;
    /* 0x50 */s32 x50;
    /* 0x54 */f32 x54;
    /* 0x58 */f32 x58;
    /* 0x5C */s32 x5C;
    /* 0x60 */u8 x60_padding[0x84 - 0x60];
} ftMarioAttributes;

typedef struct ftMarioUnkStruct
{
    u8 x0_str_arr[3];
    u8 x3_balign;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
    u32 x14;
} ftMarioUnkStruct;

inline ftMarioAttributes* GetMarioAttr(Fighter* ft)
{
    ftMarioAttributes* mario_attr = ft->x2D4_specialAttributes;
    return mario_attr;
}

//ftmario1
void ftMario_OnDeath(HSD_GObj*);
void ftMario_OnLoadForDrMario(Fighter*);
void ftMario_OnLoad(HSD_GObj*);
void ftMario_func_800E0A00(HSD_GObj*);
void ftMario_OnItemPickup(HSD_GObj*, BOOL);
void ftMario_OnItemInvisible(HSD_GObj*);
void ftMario_OnItemVisible(HSD_GObj*);
void ftMario_OnItemDrop(HSD_GObj*, BOOL);
void ftMario_func_800E0BE4(HSD_GObj*);
void ftMario_OnKnockbackEnter(HSD_GObj*);
void ftMario_OnKnockbackExit(HSD_GObj*);
void ftMario_func_800E0CAC(s32, u32*, u32*);
s32 ftMario_func_800E0CE0(s32 arg0);

//ftmario2
int ftMario_func_800E0D1C(HSD_GObj*);
void ftMario_SpecialN_StartAction(HSD_GObj*);
void ftMario_func_800E0E18(HSD_GObj*);
void ftMario_func_800E0E54(HSD_GObj*);
void ftMario_func_800E0E84(HSD_GObj*);
void ftMario_func_800E0EA4(HSD_GObj*);
void ftMario_func_800E0EE0(HSD_GObj*);
void ftMario_SpecialNAir_StartAction(HSD_GObj*);
void ftMario_func_800E10B0(HSD_GObj*);
void ftMario_func_800E10EC(HSD_GObj*);
void ftMario_func_800E111C(void);
void ftMario_func_800E113C(HSD_GObj*);
void ftMario_func_800E1178(HSD_GObj*);
void ftMario_func_800E11E0(HSD_GObj*);

//ftmario3
void ftMario_func_800E1248(HSD_GObj*);
void ftMario_func_800E132C(HSD_GObj*);
void ftMario_func_800E1368(HSD_GObj*);
void ftMario_func_800E13C8(HSD_GObj*);
void ftMario_func_800E13F8(HSD_GObj*);
void ftMario_func_800E13F8(HSD_GObj*);
BOOL ftMario_func_800E1428(HSD_GObj*);
void ftMario_SpecialS_StartAction(HSD_GObj*);
void ftMario_SpecialSAir_StartAction(HSD_GObj*);
void ftMario_func_800E1550(HSD_GObj*);
void ftMario_func_800E158C(HSD_GObj*);
void ftMario_func_800E15C8(void);
void ftMario_func_800E15CC(void);
void ftMario_func_800E15D0(HSD_GObj*);
void ftMario_func_800E16E0(HSD_GObj*);
void ftMario_func_800E1840(HSD_GObj*);
void ftMario_func_800E187C(HSD_GObj*);
void ftMario_func_800E18B8(HSD_GObj*);
void ftMario_func_800E198C(HSD_GObj*);

//ftmario4
void ftMario_SpecialHi_StartAction(HSD_GObj*);
void ftMario_SpecialHiAir_StartAction(HSD_GObj*);
void ftMario_func_800E1B24(HSD_GObj*);
void ftMario_func_800E1B84(HSD_GObj*);
void ftMario_func_800E1BE4(HSD_GObj*);
void ftMario_func_800E1D2C(HSD_GObj*);
void ftMario_func_800E1E74(HSD_GObj*);
void ftMario_func_800E1EAC(HSD_GObj*);
void ftMario_func_800E1F40(HSD_GObj*);
void ftMario_func_800E1F70(HSD_GObj*);
void ftMario_func_800E1FE0(HSD_GObj*);

//ftmario5
void ftMario_func_800E2050(HSD_GObj*);
void ftMario_SpecialLw_StartAction(HSD_GObj*);
void ftMario_SpecialLwAir_StartAction(HSD_GObj*);
void ftMario_func_800E22BC(HSD_GObj*);
void ftMario_func_800E2308(HSD_GObj*);
void ftMario_func_800E23DC(void);
void ftMario_func_800E23E0(void);
void ftMario_func_800E23E4(HSD_GObj*);
void ftMario_func_800E2508(HSD_GObj*);
void ftMario_func_800E25C4(HSD_GObj*);
void ftMario_func_800E2778(HSD_GObj*);

#endif
