#ifndef GALE01_1393AC
#define GALE01_1393AC

#include <platform.h>

#include "ftZelda/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 1392DC */ void ftZd_Init_OnDeath(HSD_GObj* gobj);
/* 139334 */ void ftZd_Init_OnLoad(HSD_GObj* gobj);
/* 1393AC */ void ftZd_Init_801393AC(HSD_GObj* gobj);
/* 1393CC */ void ftZd_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 1394AC */ void ftZd_Init_OnItemInvisible(HSD_GObj* gobj);
/* 1394F4 */ void ftZd_Init_OnItemVisible(HSD_GObj* gobj);
/* 13953C */ void ftZd_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 139590 */ void ftZd_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 1395C8 */ void ftZd_Init_801395C8(HSD_GObj* gobj);
/* 139624 */ void ftZd_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 139668 */ void ftZd_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3CFA58 */ extern MotionState ftZd_Init_MotionStateTable[ftZd_MS_SelfCount];
/* 3CFC98 */ extern char ftZd_Init_DatFilename[];
/* 3CFCA4 */ extern char ftZd_Init_DataName[];
/* 3CFE24 */ extern char ftZd_Init_AnimDatFilename[];
/* 3CFEA0 */ extern Fighter_DemoStrings ftZd_Init_DemoMotionFilenames;
/* 3CFEB0 */ extern Fighter_CostumeStrings ftZd_Init_CostumeStrings[];

#endif
