#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H

#include "ft/fighter.h"
#include "ft/forward.h"
#include "ftMario/forward.h"

#include <stddef.h>
#include <baselib/forward.h>

static usize_t const states_count = ftMario_AS_Count - ASID_MAX;
extern ActionState as_table_mario[states_count];

static usize_t const aux_states_count = 2;
extern ActionState lbl_803C7260[aux_states_count];

void ftMario_OnDeath(HSD_GObj*);
void ftMario_OnLoadForDrMario(Fighter*);
void ftMario_OnLoad(HSD_GObj*);
void ftMario_OnTakeDamage(HSD_GObj*);
void ftMario_OnItemPickup(HSD_GObj*, bool);
void ftMario_OnItemInvisible(HSD_GObj*);
void ftMario_OnItemVisible(HSD_GObj*);
void ftMario_OnItemDrop(HSD_GObj*, bool);
void ftMario_LoadSpecialAttrs(HSD_GObj*);
void ftMario_OnKnockbackEnter(HSD_GObj*);
void ftMario_OnKnockbackExit(HSD_GObj*);
void ftMario_func_800E0CAC(s32, s32*, s32*);
char* ftMario_800E0CE0(enum_t);

// ftmario4
void ftMario_SpecialHi_StartAction(HSD_GObj*);
void ftMario_SpecialAirHi_StartAction(HSD_GObj*);
void ftMario_SpecialHi_Anim(HSD_GObj*);
void ftMario_SpecialAirHi_Anim(HSD_GObj*);
void ftMario_SpecialHi_IASA(HSD_GObj*);
void ftMario_SpecialAirHi_IASA(HSD_GObj*);
void ftMario_SpecialHi_Phys(HSD_GObj*);
void ftMario_SpecialAirHi_Phys(HSD_GObj*);
void ftMario_SpecialHi_CheckLanding(HSD_GObj*);
void ftMario_SpecialHi_Coll(HSD_GObj*);
void ftMario_SpecialAirHi_Coll(HSD_GObj*);

// ftmario5
void ftMario_SpecialLw_UpdateRot(HSD_GObj*);
void ftMario_SpecialLw_StartAction(HSD_GObj*);
void ftMario_SpecialAirLw_StartAction(HSD_GObj*);
void ftMario_SpecialLw_Anim(HSD_GObj*);
void ftMario_SpecialAirLw_Anim(HSD_GObj*);
void ftMario_SpecialLw_IASA(HSD_GObj*);
void ftMario_SpecialAirLw_IASA(HSD_GObj*);
void ftMario_SpecialLw_Phys(HSD_GObj*);
void ftMario_SpecialAirLw_Phys(HSD_GObj*);
void ftMario_SpecialLw_Coll(HSD_GObj*);
void ftMario_SpecialAirLw_Coll(HSD_GObj*);

#endif
