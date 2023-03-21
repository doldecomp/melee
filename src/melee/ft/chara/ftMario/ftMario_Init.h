#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H

#include "ft/fighter.h"
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "ftMario/forward.h"

#include <stddef.h>
#include <baselib/forward.h>

static usize_t const states_count = ftMario_MS_Count - ftCo_MS_Count;
extern MotionState as_table_mario[states_count];

static usize_t const aux_states_count = 2;
extern MotionState lbl_803C7260[aux_states_count];

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
void ftMario_800E0CAC(s32, s32*, s32*);
char* ftMario_GetMotionFileString(enum_t);

#endif
