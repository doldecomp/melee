#ifndef SYSDOLPHIN_BASELIB_3B27_H
#define SYSDOLPHIN_BASELIB_3B27_H

#include <placeholder.h>
#include <platform.h>

/* 3B27F4 */ int hsd_803B27F4(const s32*, const char*, int, int,
                              void (*)(int, int));
/* 3B286C */ int hsd_803B286C(const s32*, UNK_T, const char*, int, int,
                              void (*)(int, int));
/* 3B2928 */ int hsd_803B2928(const s32*, const char*, int, int, void (*)(int, int));
/* 3B29D8 */ int hsd_803B29D8(const s32* ctx, int channel, const u8* data,
                              UNK_T callback);
/* 3B2A4C */ int hsd_803B2A4C(const s32*, int, const u8*, void (*)(int, int));
/* 3B2ADC */ int hsd_803B2ADC(s32* ctx, UNK_T data);

#endif
