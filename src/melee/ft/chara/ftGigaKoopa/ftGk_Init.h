#ifndef GALE01_14F640
#define GALE01_14F640

#include <platform.h>

#include "ftKoopa/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 14F640 */ void ftGk_Init_OnDeath(HSD_GObj*);
/* 14F698 */ void ftGk_Init_UnkMotionStates3(HSD_GObj*);
/* 14F6B8 */ void ftGk_Init_OnLoad(HSD_GObj*);
/* 14F720 */ void ftGk_Init_OnItemPickup(HSD_GObj*, bool);
/* 14F800 */ void ftGk_Init_OnItemInvisible(HSD_GObj*);
/* 14F848 */ void ftGk_Init_OnItemVisible(HSD_GObj*);
/* 14F890 */ void ftGk_Init_OnItemDrop(HSD_GObj*, bool);
/* 14F8E4 */ void ftGk_Init_LoadSpecialAttrs(HSD_GObj*);
/* 14F904 */ void ftGk_Init_OnKnockbackEnter(HSD_GObj*);
/* 14F948 */ void ftGk_Init_OnKnockbackExit(HSD_GObj*);
/* 14F98C */ void ftGk_Init_UnkDemoCallbacks0(int, int*, int*);
/* 14F9A4 */ char* ftGk_Init_GetMotionFileString(enum_t);
/* 3D35E8 */ extern MotionState ftGk_Init_MotionStateTable[ftKp_MS_SelfCount];
/* 3D38C8 */ extern MotionState ftGk_Init_UnkMotionStates0[];
/* 3D38E8 */ extern char ftGk_Init_DatFilename[];
/* 3D38F4 */ extern char ftGk_Init_DataName[];
/* 3D3948 */ extern char ftGk_Init_AnimDatFilename[];
/* 3D3954 */ extern Fighter_DemoStrings ftGk_Init_DemoMotionFilenames;
/* 3D3988 */ extern Fighter_CostumeStrings ftGk_Init_CostumeStrings[];

#endif
