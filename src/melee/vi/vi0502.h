#ifndef MELEE_VI_0502_H
#define MELEE_VI_0502_H

#include <placeholder.h>

#include "ft/forward.h"
#include "sc/forward.h"
#include <baselib/forward.h>

#include <dolphin/gx/GXStruct.h>

/* 4D6F90 */ extern SceneDesc* un_804D6F90;
/* 4D6F98 */ extern HSD_Archive* un_804D6F98;
/* 4D6F9C */ extern HSD_Archive* un_804D6F9C;
/* 4DE09C */ extern GXColor erase_colors_vi0502;

/* 31E124 */ void vi0502_8031E124(CharacterKind, s8, s8);
/* 31E304 */ void vi0502_8031E304(HSD_GObj*);
/* 31E3BC */ void vi0502_RunFrame(HSD_GObj*);
/* 31E444 */ void un_8031E444_OnEnter(void* arg);

#endif
