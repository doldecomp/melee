#ifndef DOLPHIN_GX_GXMISC_H
#define DOLPHIN_GX_GXMISC_H

#include <dolphin/os/OSThread.h>

void GXPixModeSync(void);
void GXWaitDrawDone(void);
void GXSetDrawDone(void);
void GXSetMisc(s32, u32);

#endif
