#ifndef _lbarchive_h_
#define _lbarchive_h_

#include <platform.h>

#include <baselib/forward.h>

#include <baselib/archive.h>

void lbArchive_InitializeDAT(HSD_Archive* archive, u8* data, u32 length);
void lbArchive_80016EFC(HSD_Archive* archive);
HSD_Archive* lbArchive_LoadArchive(char* filename);

void* lbArchive_LoadSymbols(char*, void**, ...);
void* lbArchive_80016DBC(char*, void**, ...);
s32 lbArchive_800171CC(void*, ...);
void lbArchive_LoadSections(HSD_Archive* archive, void** file, ...);

#endif
