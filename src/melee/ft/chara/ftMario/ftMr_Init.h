#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H

#include "ftMario/forward.h"
#include <baselib/forward.h>

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include <stddef.h>

static usize_t const states_count = ftMr_MS_Count - ftCo_MS_Count;
extern MotionState ftMr_Init_MotionStateTable[states_count];

static usize_t const aux_states_count = 2;
extern MotionState ftMr_Init_UnkMotionStates0[aux_states_count];

void ftMr_Init_OnDeath(HSD_GObj*);
void ftMr_Init_OnLoadForDrMario(Fighter*);
void ftMr_Init_OnLoad(HSD_GObj*);
void ftMr_Init_OnTakeDamage(HSD_GObj*);
void ftMr_Init_OnItemPickup(HSD_GObj*, bool);
void ftMr_Init_OnItemInvisible(HSD_GObj*);
void ftMr_Init_OnItemVisible(HSD_GObj*);
void ftMr_Init_OnItemDrop(HSD_GObj*, bool);
void ftMr_Init_LoadSpecialAttrs(HSD_GObj*);
void ftMr_Init_OnKnockbackEnter(HSD_GObj*);
void ftMr_Init_OnKnockbackExit(HSD_GObj*);
void ftMr_Init_UnkDemoCallbacks0(s32, s32*, s32*);
char* ftMr_Init_GetMotionFileString(enum_t);

#endif
