#ifndef SYSDOLPHIN_BASELIB_3B27_H
#define SYSDOLPHIN_BASELIB_3B27_H

#include <Runtime/platform.h>

#include <placeholder.h>

#include <sysdolphin/baselib/hsd_3A94.h>

/* 3B27F4 */ int hsd_803B27F4(CardState* state, const char* comment,
                              void* banner, void* icons,
                              CardCallback callback);
/* 3B286C */ int hsd_803B286C(CardState* state, const char* filename,
                              const char* comment, void* banner, void* icons,
                              CardCallback callback);
/* 3B2928 */ int hsd_803B2928(CardState* state, const char* comment,
                              void* banner, void* icons,
                              CardCallback callback);
/* 3B29D8 */ int hsd_803B29D8(CardState* state, int file_idx, u8* buf,
                              CardCallback callback);
/* 3B2A4C */ int hsd_803B2A4C(CardState* state, int file_idx, u8* buf,
                              CardCallback callback);
/* 3B2ADC */ int hsd_803B2ADC(CardState* state, UNK_T data);

#endif
