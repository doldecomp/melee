#ifndef MELEE_EF_EFSYNC_H
#define MELEE_EF_EFSYNC_H

#include <platform.h>

int efSync_Spawn(s32, ...);
// In fn_80114034 it seems to want a function definition like
// efSync_Spawn(0x4FC, gobj, fp->parts[FtPart_R2ndNb].joint);

#endif
