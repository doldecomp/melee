#ifndef _lbfile_h_
#define _lbfile_h_

#include <Runtime/platform.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/forward.h>

void lbFile_8001615C(int, int, int, bool cancelflag);
bool lbFile_800161A0(void);

size_t lbFile_8001634C(s32 fileno);
s32 lbFile_800163D8(const char* basename);
void lbFile_8001668C(const char* arg0, HSD_Archive* arg1, s32* arg2);
void lbFile_80016760(const char* arg0, HSD_Archive** arg1, s32* arg2);
bool lbFile_800168A0(s32 arg0, const char* arg1, HSD_Archive** arg2, s32* arg3);
char* lbFile_80016204(const char* basename);
void lbFile_800164A4(s32 arg0, HSD_Archive* arg1, s32* arg2, s32 arg3,
                     HSD_DevComCallback arg4, s32 arg5);
void lbFile_80016580(const char* basename, HSD_Archive* arg1, s32* arg2,
                     HSD_DevComCallback arg3, s32 arg4);
void lbFile_800161C4(int arg0, int arg1, HSD_Archive* arg2, int arg3, int arg4,
                     int arg5);

#endif
