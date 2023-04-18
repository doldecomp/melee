#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_INIT_H

#include "ftMario/forward.h"
#include <baselib/forward.h>

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include <stddef.h>

static usize_t const states_count = ftMr_MS_Count - ftCo_MS_Count;
static usize_t const aux_states_count = 2;

/* 0e08cc */ void ftMr_Init_OnDeath(HSD_GObj* gobj);
/* 0e0920 */ void ftMr_Init_OnLoadForDrMario(Fighter*);
/* 0e0960 */ void ftMr_Init_OnLoad(HSD_GObj* gobj);
/* 0e0a00 */ void ftMr_Init_OnTakeDamage(HSD_GObj* gobj);
/* 0e0a20 */ void ftMr_Init_OnItemPickup(HSD_GObj* gobj, bool);
/* 0e0b00 */ void ftMr_Init_OnItemInvisible(HSD_GObj* gobj);
/* 0e0b48 */ void ftMr_Init_OnItemVisible(HSD_GObj* gobj);
/* 0e0b90 */ void ftMr_Init_OnItemDrop(HSD_GObj* gobj, bool);
/* 0e0be4 */ void ftMr_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 0e0c24 */ void ftMr_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 0e0c68 */ void ftMr_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 0e0cac */ void ftMr_Init_UnkDemoCallbacks0(s32, s32*, s32*);
/* 0e0ce0 */ char* ftMr_Init_GetMotionFileString(enum_t);
/* 3c7120 */ extern MotionState ftMr_Init_MotionStateTable[states_count];
/* 3c7260 */ extern MotionState ftMr_Init_UnkMotionStates0[aux_states_count];

#endif
