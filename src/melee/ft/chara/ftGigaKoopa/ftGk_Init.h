#ifndef _ftgigakoopa_h_
#define _ftgigakoopa_h_

#include "ft/types.h"

#include <baselib/gobj.h>

extern MotionState ftGk_Init_MotionStateTable[];
extern MotionState ftGk_Init_UnkMotionStates0[];
extern char ftGk_Init_DatFilename[];
extern char ftGk_Init_DataName[];
extern Fighter_CostumeStrings ftGk_Init_CostumeStrings[];
extern char ftGk_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftGk_Init_DemoMotionFilenames;

void ftGk_Init_OnDeath(HSD_GObj*);
void ftGk_Init_UnkMotionStates3(HSD_GObj*);
void ftGk_Init_OnLoad(HSD_GObj*);
void ftGk_Init_OnItemPickup(HSD_GObj*, bool);
void ftGk_Init_OnItemInvisible(HSD_GObj*);
void ftGk_Init_OnItemVisible(HSD_GObj*);
void ftGk_Init_OnItemDrop(HSD_GObj*, bool);
void ftGk_Init_LoadSpecialAttrs(HSD_GObj*);
void ftGk_Init_OnKnockbackEnter(HSD_GObj*);
void ftGk_Init_OnKnockbackExit(HSD_GObj*);
void ftGk_Init_UnkDemoCallbacks0(s32, s32*, s32*);
char* ftGk_Init_GetMotionFileString(enum_t);

#endif
