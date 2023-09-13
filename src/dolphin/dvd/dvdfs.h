#ifndef DOLPHIN_DVD_DVDFS_H
#define DOLPHIN_DVD_DVDFS_H

void __DVDFSInit(void);

typedef struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
} FSTEntry;

#endif
