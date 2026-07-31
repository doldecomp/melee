#ifndef SYSDOLPHIN_BASELIB_PSDISP_H
#define SYSDOLPHIN_BASELIB_PSDISP_H

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include <dolphin/gx.h>

void psDispParticles(u32 target_link, u32 sw);
HSD_Particle* particleSort(s32, u8, HSD_Particle**, HSD_Particle**);
void setVtxDesc(s32);

#endif
