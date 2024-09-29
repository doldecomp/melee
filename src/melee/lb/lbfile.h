#ifndef GALE01_01615C
#define GALE01_01615C

#include <platform.h>

#include <baselib/forward.h>

/* 01615C */ void lbFile_8001615C(void*, int, void*, bool);
/* 0161A0 */ bool lbFile_800161A0(void);
/* 0161C4 */ void lbFile_800161C4(int file, u32 src, u32 dest, u32 size,
                                  int type, int pri);
/* 016204 */ char* lbFile_80016204(const char* basename);
/* 01634C */ size_t lbFile_8001634C(s32 fileno);
/* 0163D8 */ s32 lbFile_800163D8(const char* basename);
/* 0164A4 */ void lbFile_800164A4(s32 file, u32 src, u32* dest, s32 size,
                                  HSD_DevComCallback callback, void* args);
/* 016580 */ void lbFile_80016580(const char* basename, u32 src, u32* dest,
                                  HSD_DevComCallback callback, void* args);
/* 01668C */ void lbFile_8001668C(const char* basename, u32* src, u32* dest);
/* 016760 */ void lbFile_80016760(const char* basename, u32* src, u32* dest);
/* 0168A0 */ bool lbFile_800168A0(s32 arg0, const char* basename, u32* src,
                                  u32* dest);

#endif
