#ifndef MELEE_FT_FTDRAWCOMMON_H
#define MELEE_FT_FTDRAWCOMMON_H

#include <platform.h>

#include <dolphin/mtx/types.h>
#include <sysdolphin/baselib/gobj.h>

void ftDrawCommmon_80080E18(HSD_GObj*, long);
MtxPtr ftDrawCommmon_8008051C(HSD_GObj*, MtxPtr);

void ftDrawCommmon_800805C8(HSD_GObj* gobj, s32 arg1, s32 arg2);
void ftDrawCommmon_80081118(void);
void ftDrawCommmon_80081140(void);
void ftDrawCommmon_80081168(void);
void ftDrawCommmon_80081200(void);
void ftDrawCommmon_80080C28(HSD_GObj* gobj, s32 arg1);

#endif
