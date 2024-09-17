#ifndef DOLPHIN_DVD_DVDFS_H
#define DOLPHIN_DVD_DVDFS_H

#include <platform.h>

#include <dolphin/dvd/dvd.h>
#include <dolphin/os.h>

typedef struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
} FSTEntry;

void __DVDFSInit(void);

#endif
