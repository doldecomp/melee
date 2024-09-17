#include <platform.h>

#include <dolphin/dvd/forward.h>

#include <dolphin/dvd/dvd.h>
#include <dolphin/dvd/dvdfs.h>
#include <dolphin/os.h>
#include <dolphin/os/OSBootInfo.h>
#include <dolphin/os/OSThread.h>
#include <MSL/ctype.h>

static OSBootInfo* BootInfo;
static FSTEntry* FstStart;
static char* FstStringStart;
static u32 MaxEntryNum;
static u32 currentDirectory = 0;
OSThreadQueue __DVDThreadQueue;
u32 __DVDLongFileNameFlag = 0;

static void cbForReadAsync(s32 result, DVDCommandBlock* block);

void __DVDFSInit(void)
{
    BootInfo = (OSBootInfo*) OSPhysicalToCached(0);
    FstStart = (FSTEntry*) BootInfo->FSTLocation;

    if (FstStart) {
        MaxEntryNum = FstStart[0].nextEntryOrLength;
        FstStringStart = (char*) &(FstStart[MaxEntryNum]);
    }
}

#define entryIsDir(i)                                                         \
    (((FstStart[i].isDirAndStringOff & 0xff000000) == 0) ? false : true)
#define stringOff(i) (FstStart[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FstStart[i].parentOrPosition)
#define nextDir(i) (FstStart[i].nextEntryOrLength)
#define filePosition(i) (FstStart[i].parentOrPosition)
#define fileLength(i) (FstStart[i].nextEntryOrLength)

static bool isSame(const char* path, const char* string)
{
    while (*string != '\0') {
        if (tolower(*path++) != tolower(*string++)) {
            return false;
        }
    }

    if ((*path == '/') || (*path == '\0')) {
        return true;
    }

    return false;
}

s32 DVDConvertPathToEntrynum(const char* pathPtr)
{
    const char* ptr;
    char* stringPtr;
    bool isDir;
    u32 length;
    u32 dirLookAt;
    u32 i;
    const char* origPathPtr = pathPtr;
    const char* extentionStart;
    bool illegal;
    bool extention;

    dirLookAt = currentDirectory;

    while (1) {
        if (*pathPtr == '\0') {
            return (s32) dirLookAt;
        } else if (*pathPtr == '/') {
            dirLookAt = 0;
            pathPtr++;
            continue;
        } else if (*pathPtr == '.') {
            if (*(pathPtr + 1) == '.') {
                if (*(pathPtr + 2) == '/') {
                    dirLookAt = parentDir(dirLookAt);
                    pathPtr += 3;
                    continue;
                } else if (*(pathPtr + 2) == '\0') {
                    return (s32) parentDir(dirLookAt);
                }
            } else if (*(pathPtr + 1) == '/') {
                pathPtr += 2;
                continue;
            } else if (*(pathPtr + 1) == '\0') {
                return (s32) dirLookAt;
            }
        }

        if (__DVDLongFileNameFlag == 0) {
            extention = false;
            illegal = false;

            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
                if (*ptr == '.') {
                    if ((ptr - pathPtr > 8) || (extention == true)) {
                        illegal = true;
                        break;
                    }
                    extention = true;
                    extentionStart = ptr + 1;

                } else if (*ptr == ' ') {
                    illegal = true;
                }
            }

            if ((extention == true) && (ptr - extentionStart > 3)) {
                illegal = true;
            }

            if (illegal) {
                OSPanic("dvdfs.c", 376,
                        "DVDConvertEntrynumToPath(possibly DVDOpen or "
                        "DVDChangeDir or DVDOpenDir): "
                        "specified directory or file (%s) doesn't match "
                        "standard 8.3 format. This is a "
                        "temporary restriction and will be removed soon\n",
                        origPathPtr);
            }
        } else {
            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
                ;
            }
        }

        isDir = (*ptr == '\0') ? false : true;
        length = (u32) (ptr - pathPtr);

        ptr = pathPtr;

        for (i = dirLookAt + 1; i < nextDir(dirLookAt);
             i = entryIsDir(i) ? nextDir(i) : (i + 1))
        {
            if ((entryIsDir(i) == false) && (isDir == true)) {
                continue;
            }

            stringPtr = FstStringStart + stringOff(i);

            if (isSame(ptr, stringPtr) == true) {
                goto next_hier;
            }
        }

        return -1;

    next_hier:
        if (!isDir) {
            return (s32) i;
        }

        dirLookAt = i;
        pathPtr += length + 1;
    }
}

bool DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo)
{
    if ((entrynum < 0) || ((unsigned) entrynum >= MaxEntryNum) ||
        entryIsDir(entrynum))
    {
        return false;
    }

    fileInfo->startAddr = filePosition(entrynum);
    fileInfo->length = fileLength(entrynum);
    fileInfo->callback = (DVDCallback) NULL;
    fileInfo->cb.state = DVD_STATE_END;

    return true;
}

bool DVDClose(DVDFileInfo* fileInfo)
{
    DVDCancel(&(fileInfo->cb));
    return true;
}

bool DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length,
                      s32 offset, DVDCallback callback, s32 prio)
{
    if (!((0 <= offset) && ((unsigned) offset < fileInfo->length))) {
        OSPanic("dvdfs.c", 739,
                "DVDReadAsync(): specified area is out of the file  ");
    }

    if (!((0 <= offset + length) &&
          ((unsigned) (offset + length) <
           fileInfo->length + DVD_MIN_TRANSFER_SIZE)))
    {
        OSPanic("dvdfs.c", 745,
                "DVDReadAsync(): specified area is out of the file  ");
    }

    fileInfo->callback = callback;
    DVDReadAbsAsyncPrio(&(fileInfo->cb), addr, length,
                        (s32) (fileInfo->startAddr + offset), cbForReadAsync,
                        prio);

    return true;
}

static void cbForReadAsync(s32 result, DVDCommandBlock* block)
{
    DVDFileInfo* fileInfo;

    fileInfo = (DVDFileInfo*) ((char*) block);
    if (fileInfo->callback) {
        (fileInfo->callback)(result, fileInfo);
    }
}
