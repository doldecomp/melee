#ifndef SYSDOLPHIN_BASELIB_3B27_H
#define SYSDOLPHIN_BASELIB_3B27_H

#include <Runtime/platform.h>

#include <placeholder.h>

#include "sysdolphin/baselib/hsd_3A94.h"

/* 3B27F4 */ int hsd_803B27F4(const CardState*, const char*, int, int,
                              void (*)(int, int));
/* 3B286C */ int hsd_803B286C(CardState*, const char* filename,
                              const char* comment, int, int,
                              void (*)(int, int));
/* 3B2928 */ int hsd_803B2928(const CardState*, const char*, int, int,
                              void (*)(int, int));
/* 3B29D8 */ int hsd_803B29D8(const CardState* ctx, int channel,
                              const u8* data, UNK_T callback);
/* 3B2A4C */ int hsd_803B2A4C(const s32*, int, const u8*, void (*)(int, int));
/* 3B2ADC */ int hsd_SetCardIconInfo(CardState* ctx, CardIconInfo* icon_info);

#endif
