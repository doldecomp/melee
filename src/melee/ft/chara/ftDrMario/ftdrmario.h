#ifndef _ftdrmario_h_
#define _ftdrmario_h_

#include <platform.h>

#include "ft/fighter.h"

#include <baselib/gobj.h>

typedef struct _ftDrMarioAttributes {
    u8 pad_x0[4];
    u32 x4;
    u8 pad_x8[4];
    u32 xC;
    u8 pad_x10[4];
    u32 x14;
} ftDrMarioAttributes;

extern MotionState ftDrMario_MotionStateTable[];
extern char lbl_803D15D8[];
extern char lbl_803D15E4[];
extern Fighter_CostumeStrings lbl_803D180C[];
extern char lbl_803D1770[];
extern Fighter_DemoStrings lbl_803D17FC;

void ftDrMario_OnDeath(HSD_GObj*);
void ftDrMario_OnLoad(HSD_GObj*);
void func_80149540(HSD_GObj*);
void ftDrMario_OnItemPickup(HSD_GObj*, bool);
void ftDrMario_OnItemInvisible(HSD_GObj*);
void ftDrMario_OnItemVisible(HSD_GObj*);
void ftDrMario_OnItemDrop(HSD_GObj*, bool);
void ftDrMario_LoadSpecialAttrs(HSD_GObj*);
void ftDrMario_OnKnockbackEnter(HSD_GObj*);
void ftDrMario_OnKnockbackExit(HSD_GObj*);
void ftDrMario_801497CC(HSD_GObj*);
bool ftDrMario_80149844(HSD_GObj*);
void ftDrMario_801498A0(HSD_GObj*);
u32 ftDrMario_801498EC(HSD_GObj*);
void ftDrMario_80149910(HSD_GObj*);

// ftdrmario_2.c
void ftDrMario_80149954(HSD_GObj*);
void ftDrMario_80149A6C(HSD_GObj*);
void ftDrMario_80149A8C(HSD_GObj*);
void ftDrMario_80149AAC(HSD_GObj*);

void ftDrMario_80149954(HSD_GObj*);
void ftDrMario_80149A6C(HSD_GObj*);
void ftDrMario_80149A8C(HSD_GObj*);
void ftDrMario_80149AAC(HSD_GObj*);
void ftDrMario_80149954(HSD_GObj*);
void ftDrMario_80149A6C(HSD_GObj*);
void ftDrMario_80149A8C(HSD_GObj*);
void ftDrMario_80149AAC(HSD_GObj*);
void ftMario_SpecialN_Anim(HSD_GObj*);
void ftMario_SpecialN_IASA(HSD_GObj*);
void ftMario_SpecialN_Phys(HSD_GObj*);
void ftMario_SpecialN_Coll(HSD_GObj*);
void ftMario_SpecialAirN_Anim(HSD_GObj*);
void ftMario_SpecialAirN_IASA(HSD_GObj*);
void ftMario_SpecialAirN_Phys(HSD_GObj*);
void ftMario_SpecialAirN_Coll(HSD_GObj*);
void ftMario_SpecialS_Anim(HSD_GObj*);
void ftMario_SpecialS_IASA(HSD_GObj*);
void ftMario_SpecialS_Phys(HSD_GObj*);
void ftMario_SpecialS_Coll(HSD_GObj*);
void ftMario_SpecialAirS_Anim(HSD_GObj*);
void ftMario_SpecialAirS_IASA(HSD_GObj*);
void ftMario_SpecialAirS_Phys(HSD_GObj*);
void ftMario_SpecialAirS_Coll(HSD_GObj*);
void ftMario_SpecialHi_Anim(HSD_GObj*);
void ftMario_SpecialHi_IASA(HSD_GObj*);
void ftMario_SpecialHi_Phys(HSD_GObj*);
void ftMario_SpecialHi_Coll(HSD_GObj*);
void ftMario_SpecialAirHi_Anim(HSD_GObj*);
void ftMario_SpecialAirHi_IASA(HSD_GObj*);
void ftMario_SpecialAirHi_Phys(HSD_GObj*);
void ftMario_SpecialAirHi_Coll(HSD_GObj*);
void ftMario_SpecialLw_Anim(HSD_GObj*);
void ftMario_SpecialLw_IASA(HSD_GObj*);
void ftMario_SpecialLw_Phys(HSD_GObj*);
void ftMario_SpecialLw_Coll(HSD_GObj*);
void ftMario_SpecialAirLw_Anim(HSD_GObj*);
void ftMario_SpecialAirLw_IASA(HSD_GObj*);
void ftMario_SpecialAirLw_Phys(HSD_GObj*);
void ftMario_SpecialAirLw_Coll(HSD_GObj*);

#endif
