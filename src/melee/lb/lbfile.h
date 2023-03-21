#ifndef _lbfile_h_
#define _lbfile_h_

#include <baselib/archive.h>
#include <baselib/forward.h>
#include <Runtime/platform.h>

void lbFile_8001615C(int, int, int, bool cancelflag);
bool lbFile_800161A0(void);

size_t func_8001634C(s32 fileno);
s32 func_800163D8(const char* basename);
void func_8001668C(const char* arg0, HSD_Archive* arg1, s32* arg2);
void func_80016760(const char* arg0, HSD_Archive** arg1, s32* arg2);
bool func_800168A0(s32 arg0, const char* arg1, HSD_Archive** arg2, s32* arg3);
char* func_80016204(const char* basename);
void func_800164A4(s32 arg0, HSD_Archive* arg1, s32* arg2, s32 arg3,
                   HSD_DevComCallback arg4, s32 arg5);
void func_80016580(const char* basename, HSD_Archive* arg1, s32* arg2,
                   HSD_DevComCallback arg3, s32 arg4);
void func_800161C4(int arg0, int arg1, HSD_Archive* arg2, int arg3, int arg4,
                   int arg5);

#endif
