#ifndef _lbfile_h_
#define _lbfile_h_

#include <platform.h>
#include <baselib/forward.h>

#include <baselib/archive.h>

void lbFile_8001615C(int, int, int, bool cancelflag);
bool lbFile_800161A0(void);

size_t lbFile_8001634C(s32 fileno);
s32 lbFile_800163D8(const char* basename);
void lbFile_8001668C(const char* basename, u32* src, u32* dest);
void lbFile_80016760(const char* basename, u32* src, u32* dest);
bool lbFile_800168A0(s32 arg0, const char* basename, u32* src, u32* dest);
char* lbFile_80016204(const char* basename);
void lbFile_800164A4(s32 file, u32 src, u32* dest, s32 size,
                     HSD_DevComCallback callback, void* args);
void lbFile_80016580(const char* basename, u32 src, u32* dest,
                     HSD_DevComCallback callback, void* args);
void lbFile_800161C4(int file, u32 src, u32 dest, u32 size, int type,
                     int pri);

#endif
