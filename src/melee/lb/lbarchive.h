#ifndef _lbarchive_h_
#define _lbarchive_h_

#include <platform.h>

#include <baselib/forward.h>

#include <baselib/archive.h>

void lbArchive_InitializeDAT(HSD_Archive* archive, void* data, size_t length);
void lbArchive_LoadSections(HSD_Archive* archive, void** symbols, ...);
HSD_Archive* lbArchive_LoadArchive(const char* filename);
HSD_Archive* lbArchive_LoadSymbols(const char* filename, void* symbols, ...);
HSD_Archive* lbArchive_80016DBC(const char* filename, void* symbols, ...);
void lbArchive_80016EFC(HSD_Archive*);
bool lbArchive_80017040(HSD_Archive** dst, const char* filename, void* symbols,
                        ...);
bool lbArchive_800171CC(HSD_Archive** dst, const char* filename, void* symbols,
                        ...);
int lbArchive_80017340(HSD_Archive*, u8*, size_t file_size,
                       intptr_t base_addr);

#endif
