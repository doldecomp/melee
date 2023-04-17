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

extern MotionState ftDr_Init_MotionStateTable[];
extern char ftDr_Init_DatFilename[];
extern char ftDr_Init_DataName[];
extern Fighter_CostumeStrings ftDr_Init_CostumeStrings[];
extern char ftDr_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftDr_Init_DemoMotionFilenames;

void ftDr_Init_OnDeath(HSD_GObj*);
void ftDr_Init_OnLoad(HSD_GObj*);
void ftDr_Init_80149540(HSD_GObj*);
void ftDr_Init_OnItemPickup(HSD_GObj*, bool);
void ftDr_Init_OnItemInvisible(HSD_GObj*);
void ftDr_Init_OnItemVisible(HSD_GObj*);
void ftDr_Init_OnItemDrop(HSD_GObj*, bool);
void ftDr_Init_LoadSpecialAttrs(HSD_GObj*);
void ftDr_Init_OnKnockbackEnter(HSD_GObj*);
void ftDr_Init_OnKnockbackExit(HSD_GObj*);
void ftDr_Init_801497CC(HSD_GObj*);
bool ftDr_Init_80149844(HSD_GObj*);
void ftDr_Init_801498A0(HSD_GObj*);
u32 ftDr_Init_801498EC(HSD_GObj*);
void ftDr_Init_80149910(HSD_GObj*);

// ftDr_Appeal.c
void ftDr_Appeal_Anim(HSD_GObj*);
void ftDr_Appeal_IASA(HSD_GObj*);
void ftDr_Appeal_Phys(HSD_GObj*);
void ftDr_Appeal_Coll(HSD_GObj*);

void ftDr_Appeal_Anim(HSD_GObj*);
void ftDr_Appeal_IASA(HSD_GObj*);
void ftDr_Appeal_Phys(HSD_GObj*);
void ftDr_Appeal_Coll(HSD_GObj*);
void ftDr_Appeal_Anim(HSD_GObj*);
void ftDr_Appeal_IASA(HSD_GObj*);
void ftDr_Appeal_Phys(HSD_GObj*);
void ftDr_Appeal_Coll(HSD_GObj*);
void ftMr_SpecialN_Anim(HSD_GObj*);
void ftMr_SpecialN_IASA(HSD_GObj*);
void ftMr_SpecialN_Phys(HSD_GObj*);
void ftMr_SpecialN_Coll(HSD_GObj*);
void ftMr_SpecialAirN_Anim(HSD_GObj*);
void ftMr_SpecialAirN_IASA(HSD_GObj*);
void ftMr_SpecialAirN_Phys(HSD_GObj*);
void ftMr_SpecialAirN_Coll(HSD_GObj*);
void ftMr_SpecialS_Anim(HSD_GObj*);
void ftMr_SpecialS_IASA(HSD_GObj*);
void ftMr_SpecialS_Phys(HSD_GObj*);
void ftMr_SpecialS_Coll(HSD_GObj*);
void ftMr_SpecialAirS_Anim(HSD_GObj*);
void ftMr_SpecialAirS_IASA(HSD_GObj*);
void ftMr_SpecialAirS_Phys(HSD_GObj*);
void ftMr_SpecialAirS_Coll(HSD_GObj*);
void ftMr_SpecialHi_Anim(HSD_GObj*);
void ftMr_SpecialHi_IASA(HSD_GObj*);
void ftMr_SpecialHi_Phys(HSD_GObj*);
void ftMr_SpecialHi_Coll(HSD_GObj*);
void ftMr_SpecialAirHi_Anim(HSD_GObj*);
void ftMr_SpecialAirHi_IASA(HSD_GObj*);
void ftMr_SpecialAirHi_Phys(HSD_GObj*);
void ftMr_SpecialAirHi_Coll(HSD_GObj*);
void ftMr_SpecialLw_Anim(HSD_GObj*);
void ftMr_SpecialLw_IASA(HSD_GObj*);
void ftMr_SpecialLw_Phys(HSD_GObj*);
void ftMr_SpecialLw_Coll(HSD_GObj*);
void ftMr_SpecialAirLw_Anim(HSD_GObj*);
void ftMr_SpecialAirLw_IASA(HSD_GObj*);
void ftMr_SpecialAirLw_Phys(HSD_GObj*);
void ftMr_SpecialAirLw_Coll(HSD_GObj*);

#endif
