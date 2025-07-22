#ifndef SYSDOLPHIN_BASELIB_PSAPPSRT_H
#define SYSDOLPHIN_BASELIB_PSAPPSRT_H

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/objalloc.h"

#include <dolphin/mtx.h>

#define PSAPPSRT_UNK_B09 (1 << 9)
#define PSAPPSRT_UNK_B10 (1 << 10)
#define PSAPPSRT_UNK_B11 (1 << 11)

/* 003A0D18 */ bool psInitAppSRT(int, int);
/* 003A0D58 */ s32 psAddGeneratorAppSRT(s32, u16);
/* 003A0E3C */ void HSD_PSAppSrt_803A425C(UNK_T, s32);
u16 psRemoveGeneratorSRT(UNK_T);
u16 psRemoveParticleAppSRT(UNK_T);
HSD_psAppSRT* psAddGeneratorAppSRT_begin(HSD_Generator*, s32);
u16 psAttachParticleAppSRT(UNK_T, UNK_T);

extern HSD_ObjAllocData HSD_PSAppSrt_804D10B0;

#endif
