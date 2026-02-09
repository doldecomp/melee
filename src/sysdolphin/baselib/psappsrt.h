#ifndef SYSDOLPHIN_BASELIB_PSAPPSRT_H
#define SYSDOLPHIN_BASELIB_PSAPPSRT_H

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "baselib/objalloc.h"

#include <dolphin/mtx.h>

#define PSAPPSRT_UNK_B09 (1 << 9)
#define PSAPPSRT_UNK_B10 (1 << 10)
#define PSAPPSRT_UNK_B11 (1 << 11)

/* 003A0D18 */ bool psInitAppSRT(int, int);
/* 003A0D58 */ HSD_psAppSRT* psAddGeneratorAppSRT(s32, u16);
/* 003A0E3C */ void HSD_PSAppSrt_803A425C(HSD_Particle*, s32);
int psRemoveGeneratorSRT(HSD_Generator*);
int psRemoveParticleAppSRT(HSD_Particle*);
HSD_psAppSRT* psAddGeneratorAppSRT_begin(HSD_Generator*, s32);
int psAttachParticleAppSRT(HSD_Particle*, HSD_psAppSRT*);
int psAttachGeneratorAppSRT(HSD_Generator*, HSD_psAppSRT*);

extern HSD_ObjAllocData HSD_PSAppSrt_804D10B0;

#endif
