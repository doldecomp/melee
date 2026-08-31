#ifndef MELEE_VI_0502_H
#define MELEE_VI_0502_H

#include "ft/forward.h"
#include "vi/forward.h"
#include <baselib/forward.h>

/* 31E110 */ void un_8031E110(int arg0, int arg1, int arg2);
/* 31E124 */ void vi0502_8031E124(CharacterKind, int, int);
/* 31E304 */ void vi0502_8031E304(HSD_GObj*);
/* 31E3BC */ void vi0502_GObj_OnProc(HSD_GObj*);
/* 31E444 */ void vi0502_Scene_OnEnter(void* arg);
/* 31E6CC */ void vi0502_Scene_OnFrame(void);
/* 4D6FA8 */ extern ViCharaDesc* un_804D6FA8[2];

#endif
