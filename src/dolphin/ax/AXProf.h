#ifndef DOLPHIN_AX_AXPROF_H
#define DOLPHIN_AX_AXPROF_H

#include <platform.h>

#include <dolphin/ax.h>

AXPROFILE* __AXGetCurrentProfile(void);
void AXInitProfile(AXPROFILE* profile, u32 maxProfiles);
u32 AXGetProfile(void);

#endif
