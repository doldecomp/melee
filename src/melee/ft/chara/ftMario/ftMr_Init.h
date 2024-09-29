#ifndef GALE01_0E08CC
#define GALE01_0E08CC

#include <platform.h>

#include "ftMario/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

static usize_t const aux_states_count = 2;

/* 0E08CC */ void ftMr_Init_OnDeath(HSD_GObj* gobj);
/* 0E0920 */ void ftMr_Init_OnLoadForDrMario(Fighter*);
/* 0E0960 */ void ftMr_Init_OnLoad(HSD_GObj* gobj);
/* 0E0A00 */ void ftMr_Init_OnTakeDamage(HSD_GObj* gobj);
/* 0E0A20 */ void ftMr_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 0E0B00 */ void ftMr_Init_OnItemInvisible(HSD_GObj* gobj);
/* 0E0B48 */ void ftMr_Init_OnItemVisible(HSD_GObj* gobj);
/* 0E0B90 */ void ftMr_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 0E0BE4 */ void ftMr_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 0E0C24 */ void ftMr_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 0E0C68 */ void ftMr_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 0E0CAC */ void ftMr_Init_UnkDemoCallbacks0(int, int*, int*);
/* 0E0CE0 */ char* ftMr_Init_GetMotionFileString(enum_t);
/* 3C7120 */ extern MotionState ftMr_Init_MotionStateTable[ftMr_MS_SelfCount];
/* 3C7260 */ extern MotionState ftMr_Init_UnkMotionStates0[aux_states_count];

#endif
