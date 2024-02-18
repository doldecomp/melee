#ifndef SYSDOLPHIN_BASELIB_PSDISP_H
#define SYSDOLPHIN_BASELIB_PSDISP_H

#include <platform.h>
#include <dolphin/gx/forward.h>

#include "baselib/psstructs.h"

void psDispParticles(s32, u32);
unk_t particleSort(s32, u8, unk_t*, unk_t*);
void setVtxDesc(s32);

#endif
