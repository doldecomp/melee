#ifndef MELEE_FT_FTDRAWCOMMON_H
#define MELEE_FT_FTDRAWCOMMON_H

#include <platform.h>
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>
#include <baselib/gobj.h>

void ftDrawCommon_80080E18(HSD_GObj*, int);
MtxPtr ftDrawCommon_8008051C(HSD_GObj*, MtxPtr);

void ftDrawCommon_800805C8(HSD_GObj* gobj, s32 arg1, s32 arg2);
void ftDrawCommon_80081118(void);
void ftDrawCommon_80081140(void);
void ftDrawCommon_80081168(void);
void ftDrawCommon_80081200(void);
void ftDrawCommon_80080C28(HSD_GObj* gobj, s32 arg1);

#endif
