#ifndef _lbarchive_h_
#define _lbarchive_h_

#include <platform.h>

#include <sysdolphin/baselib/archive.h>

void lbArchive_InitializeDAT(HSD_Archive* archive, u8* data, u32 length);
void lbArchive_80016EFC(void);
void lbArchive_80016BE0(void);

void lbArchive_80016C64(char*, int**, char*, int, ...);
void* lbArchive_80016DBC(void*, ...);
s32 lbArchive_800171CC(void*, ...);
void lbArchive_80016AF0(void);

#endif
