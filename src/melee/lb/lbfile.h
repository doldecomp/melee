#ifndef _lbfile_h_
#define _lbfile_h_

#include <Runtime/platform.h>
#include <sysdolphin/baselib/archive.h>

void lbFile_8001615C(int, int, int, bool cancelflag);
bool lbFile_800161A0(void);

size_t func_8001634C(s32 fileno);
s32 func_800163D8(const char* basename);
void func_8001668C(const char* arg0, HSD_Archive* arg1, s32* arg2);
void func_80016760(const char* arg0, HSD_Archive** arg1, s32* arg2);
bool func_800168A0(s32 arg0, const char* arg1, HSD_Archive** arg2, s32* arg3);
char* func_80016204(const char* basename);

#endif
