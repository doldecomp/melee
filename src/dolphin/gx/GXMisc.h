// header for GXMisc public API

#ifndef DOLPHIN_GX_GXMISC_H
#define DOLPHIN_GX_GXMISC_H

#include <dolphin/os/OSThread.h>

/* 003398FC */ extern void GXPixModeSync();
/* 003398B0 */ extern void GXWaitDrawDone();
/* 00339818 */ extern void GXSetDrawDone();
/* 003397A0 */ extern void GXSetMisc(s32, s32);

#endif