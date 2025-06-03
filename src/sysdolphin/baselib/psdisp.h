#ifndef SYSDOLPHIN_BASELIB_PSDISP_H
#define SYSDOLPHIN_BASELIB_PSDISP_H

#include <platform.h>
#include <placeholder.h>

#include "baselib/psstructs.h"

#include <dolphin/gx.h>

void psDispParticles(s32, u32);
UNK_T particleSort(s32, u8, UNK_T*, UNK_T*);
void setVtxDesc(s32);

#endif
