#ifndef DOLPHIN_DVD_DVDFS_H
#define DOLPHIN_DVD_DVDFS_H

#include <platform.h>

#include <dolphin/dvd/dvd.h>
#include <dolphin/os/os.h>

typedef struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
} FSTEntry;

void __DVDFSInit(void);
s32 DVDConvertPathToEntrynum(const char* pathPtr);
bool DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo);
bool DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length,
                      s32 offset, DVDCallback callback, s32 prio);

#endif
