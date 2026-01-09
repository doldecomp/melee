#ifndef MELEE_IF_STATUS_H
#define MELEE_IF_STATUS_H

#include <placeholder.h>
#include <platform.h>

#include "if/forward.h"

#include "if/types.h"

#include <baselib/forward.h>

/* 2F4910 */ HudIndex* ifStatus_802F4910(void);
/* 2F4B84 */ void ifStatus_802F4B84(void);
/* 2F4EDC */ void ifStatus_802F4EDC(void);
/* 2F5B48 */ void ifStatus_802F5B48(void);
/* 2F5DE0 */ void ifStatus_802F5DE0(HSD_GObj* player, s32 arg1);
/* 2F5E50 */ void ifStatus_802F5E50(HSD_GObj* gobj, s32 arg1);
/* 2F5EC0 */ void ifStatus_802F5EC0(void);
/* 2F6194 */ HSD_GObj* ifStatus_802F6194(HSD_GObj*, s32);
/* 2F61FC */ void ifStatus_802F61FC(void);
/* 2F6508 */ void ifStatus_802F6508(s32);
/* 2F665C */ void ifStatus_802F665C(int);
/* 2F66A4 */ void ifStatus_802F66A4(void);
/* 2F6788 */ void ifStatus_802F6788(u8);
/* 2F6804 */ void ifStatus_802F6804(void);
/* 2F6898 */ void ifStatus_802F6898(void);
/* 2F68F0 */ void ifStatus_802F68F0(void);
/* 2F6948 */ void ifStatus_802F6948(s32);
/* 2F69C0 */ void ifStatus_802F69C0(s32, s32);
/* 2F6AF8 */ void ifStatus_802F6AF8(s32);
/* 2F6C04 */ void ifStatus_802F6C04(s32);
/* 2F6D10 */ void ifStatus_802F6D10(s32);
/* 2F6E1C */ void ifStatus_802F6E1C(int slot);
/* 2F6E3C */ void ifStatus_802F6E3C(s32);
/* 2F6EA4 */ void ifStatus_802F6EA4(int, int, int, int, Event, Event);
/* 2F7034 */ void ifStatus_802F7034(UNK_T);
/* 2F7134 */ void ifStatus_802F7134(void);
/* 2F7220 */ void ifStatus_802F7220(void);
/* 3F9628 */ extern Element_803F9628 ifStatus_803F9628[8];
/* 4A10C8 */ extern HudIndex ifStatus_HudInfo;

#endif
