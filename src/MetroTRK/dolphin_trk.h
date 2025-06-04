#ifndef METROTRK_DOLPHIN_TRK_H
#define METROTRK_DOLPHIN_TRK_H

#include <platform.h>

#include <MetroTRK/dserror.h>

SECTION_INIT void __TRK_reset(void);
void InitMetroTRK(void);
void EnableMetroTRKInterrupts(void);
u32 TRKTargetTranslate(u32 addr);
DSError TRKInitializeTarget(void);

#endif
