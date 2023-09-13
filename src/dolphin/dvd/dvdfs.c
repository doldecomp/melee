#include <platform.h>

#include <dolphin/dvd/dvdfs.h>
#include <dolphin/os/os.h>
#include <dolphin/os/OSBootInfo.h>

extern OSBootInfo* BootInfo;
extern FSTEntry* FstStart;
extern char* FstStringStart;
extern s32 MaxEntryNum;

void __DVDFSInit()
{
    BootInfo = (OSBootInfo*) OSPhysicalToCached(0);
    FstStart = (FSTEntry*) BootInfo->FSTLocation;

    if (FstStart) {
        MaxEntryNum = FstStart[0].nextEntryOrLength;
        FstStringStart = (char*) &(FstStart[MaxEntryNum]);
    }
}
