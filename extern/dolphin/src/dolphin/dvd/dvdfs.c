#include <dolphin.h>
#include <dolphin/dvd.h>

#include "__dvd.h"

struct FSTEntry {
    /* 0x00 */ u32 isDirAndStringOff;
    /* 0x04 */ u32 parentOrPosition;
    /* 0x08 */ u32 nextEntryOrLength;
};

// .sbss
static struct OSBootInfo_s * BootInfo; // size: 0x4, address: 0x0
static struct FSTEntry * FstStart; // size: 0x4, address: 0x4
static char * FstStringStart; // size: 0x4, address: 0x8
static unsigned long MaxEntryNum; // size: 0x4, address: 0xC
static unsigned long currentDirectory; // size: 0x4, address: 0x10
struct OSThreadQueue __DVDThreadQueue; // size: 0x8, address: 0x18
unsigned long __DVDLongFileNameFlag; // size: 0x4, address: 0x14

// functions
static BOOL isSame(const char* path, const char* string);
static u32 myStrncpy(char* dest, char* src, u32 maxlen);
static u32 entryToPath(u32 entry, char* path, u32 maxlen);
static BOOL DVDConvertEntrynumToPath(s32 entrynum, char* path, u32 maxlen);
static void cbForReadAsync(s32 result, DVDCommandBlock* block);
static void cbForReadSync();
static void cbForSeekAsync(long result, struct DVDCommandBlock * block);
static void cbForSeekSync();
static void cbForPrepareStreamAsync(s32 result, DVDCommandBlock* block);
static void cbForPrepareStreamSync();

void __DVDFSInit() {
    BootInfo = (void*)OSPhysicalToCached(0);
    FstStart = BootInfo->FSTLocation;
    if (FstStart) {
        MaxEntryNum = FstStart->nextEntryOrLength;
        FstStringStart = (char*)FstStart + (MaxEntryNum * 0xC);
    }
}

/* For convenience */
#define entryIsDir(i) (((FstStart[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FstStart[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FstStart[i].parentOrPosition)
#define nextDir(i) (FstStart[i].nextEntryOrLength)
#define filePosition(i) (FstStart[i].parentOrPosition)
#define fileLength(i) (FstStart[i].nextEntryOrLength)

static BOOL isSame(const char* path, const char* string) {
    while (*string != '\0') {
        if (tolower(*path++) != tolower(*string++)) {
            return FALSE;
        }
    }
    
    if ((*path == '/') || (*path == '\0')) {
        return TRUE;
    }
    
    return FALSE;
}

s32 DVDConvertPathToEntrynum(char* pathPtr) {
    const char* ptr;
    char* stringPtr;
    BOOL isDir;
    u32 length;
    u32 dirLookAt;
    u32 i;
    const char* origPathPtr = pathPtr;
    const char* extentionStart;
    BOOL illegal;
    BOOL extention;
    
    ASSERTMSGLINE(0x126, pathPtr, "DVDConvertPathToEntrynum(): null pointer is specified  ");
    
    dirLookAt = currentDirectory;
    
    while (1) {
    
    if (*pathPtr == '\0') {
        return (s32)dirLookAt;
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
                return (s32)parentDir(dirLookAt);
            }
        } else if (*(pathPtr + 1) == '/') {
            pathPtr += 2;
            continue;
        } else if (*(pathPtr + 1) == '\0') {
            return (s32)dirLookAt;
        }
    }
    
    if (__DVDLongFileNameFlag == 0) {
        extention = FALSE;
        illegal = FALSE;
    
        for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
            if (*ptr == '.') {
                if ((ptr - pathPtr > 8) || (extention == TRUE)) {
                    illegal = TRUE;
                    break;
                }
                extention = TRUE;
                extentionStart = ptr + 1;
        
            } else if (*ptr == ' ')
                illegal = TRUE;
        }
    
        if ((extention == TRUE) && (ptr - extentionStart > 3))
            illegal = TRUE;
    
        if (illegal)
            OSPanic(__FILE__, 0x16B,
                "DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): "
                "specified directory or file (%s) doesn't match standard 8.3 format. This is a "
                "temporary restriction and will be removed soon\n",
                origPathPtr);
    } else {
        for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++)
            ;
    }
    
    isDir = (*ptr == '\0') ? FALSE : TRUE;
    length = (u32)(ptr - pathPtr);
    
    ptr = pathPtr;
    
    for (i = dirLookAt + 1; i < nextDir(dirLookAt); i = entryIsDir(i) ? nextDir(i) : (i + 1)) {
        if ((entryIsDir(i) == FALSE) && (isDir == TRUE)) {
            continue;
        }
    
        stringPtr = FstStringStart + stringOff(i);
    
        if (isSame(ptr, stringPtr) == TRUE) {
            goto next_hier;
        }
    }
    
    return -1;
    
next_hier:
        if (!isDir) {
            return (s32)i;
        }
        
        dirLookAt = i;
        pathPtr += length + 1;
    }
}

BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo) {
    ASSERTMSGLINE(0x1AF, fileInfo, "DVDFastOpen(): null pointer is specified to file info address  ");
    ASSERTMSG1LINE(0x1B2, (entrynum >= 0) && ((u32) entrynum < (u32) MaxEntryNum), "DVDFastOpen(): specified entry number '%d' is out of range  ", entrynum);
    ASSERTMSG1LINE(0x1B5, !entryIsDir(entrynum), "DVDFastOpen(): entry number '%d' is assigned to a directory  ", entrynum);
    
    if ((entrynum < 0) || (entrynum >= MaxEntryNum) || entryIsDir(entrynum)) {
        return FALSE;
    }
    
    fileInfo->startAddr = filePosition(entrynum);
    fileInfo->length = fileLength(entrynum);
    fileInfo->callback = (DVDCallback)NULL;
    fileInfo->cb.state = DVD_STATE_END;
    
    return TRUE;
}

BOOL DVDOpen(char* fileName, DVDFileInfo* fileInfo) {
    s32 entry;
    char currentDir[128];
    
    ASSERTMSGLINE(0x1D3, fileName, "DVDOpen(): null pointer is specified to file name  ");
    ASSERTMSGLINE(0x1D4, fileInfo, "DVDOpen(): null pointer is specified to file info address  ");
    
    entry = DVDConvertPathToEntrynum(fileName);
    
    if (0 > entry) {
        DVDGetCurrentDir(currentDir, 128);
        OSReport("Warning: DVDOpen(): file '%s' was not found under %s.\n", fileName, currentDir);
        return FALSE;
    }
    
    if (entryIsDir(entry)) {
        ASSERTMSG1LINE(0x1E2, !entryIsDir(entry), "DVDOpen(): directory '%s' is specified as a filename  ", fileName);
        return FALSE;
    }
    
    fileInfo->startAddr = filePosition(entry);
    fileInfo->length = fileLength(entry);
    fileInfo->callback = (DVDCallback)NULL;
    fileInfo->cb.state = DVD_STATE_END;
    
    return TRUE;
}

BOOL DVDClose(DVDFileInfo* fileInfo) {
    ASSERTMSGLINE(0x1FA, fileInfo, "DVDClose(): null pointer is specified to file info address  ");
    DVDCancel(&(fileInfo->cb));
    return TRUE;
}

static u32 myStrncpy(char* dest, char* src, u32 maxlen) {
    u32 i = maxlen;
    
    while ((i > 0) && (*src != 0)) {
        *dest++ = *src++;
        i--;
    }
    
    return (maxlen - i);
}

static u32 entryToPath(u32 entry, char* path, u32 maxlen) {
    char* name;
    u32 loc;
    
    if (entry == 0) {
        return 0;
    }
    
    name = FstStringStart + stringOff(entry);
    
    loc = entryToPath(parentDir(entry), path, maxlen);
    
    if (loc == maxlen) {
        return loc;
    }
    
    *(path + loc++) = '/';
    
    loc += myStrncpy(path + loc, name, maxlen - loc);
    
    return loc;
}

static BOOL DVDConvertEntrynumToPath(s32 entrynum, char* path, u32 maxlen) {
    u32 loc;
    
    ASSERTMSG1LINE(0x255, (entrynum >= 0) && (entrynum < MaxEntryNum), "DVDConvertEntrynumToPath: specified entrynum(%d) is out of range  ", entrynum);
    ASSERTMSG1LINE(0x257, maxlen > 1, "DVDConvertEntrynumToPath: maxlen should be more than 1 (%d is specified)", maxlen);
    ASSERTMSGLINE(0x25C, entryIsDir(entrynum), "DVDConvertEntrynumToPath: cannot convert an entry num for a file to path  ");
    
    loc = entryToPath((u32)entrynum, path, maxlen);
    
    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return FALSE;
    }
    
    if (entryIsDir(entrynum)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return FALSE;
        }
    
        path[loc++] = '/';
    }
    
    path[loc] = '\0';
    return TRUE;
}

BOOL DVDGetCurrentDir(char* path, u32 maxlen) {
    ASSERTMSG1LINE(0x286, (maxlen > 1), "DVDGetCurrentDir: maxlen should be more than 1 (%d is specified)", maxlen);
    return DVDConvertEntrynumToPath((s32)currentDirectory, path, maxlen);
}

BOOL DVDChangeDir(char* dirName) {
    s32 entry;
    char currentDir[128];
    
    ASSERTMSGLINE(0x29C, dirName, "DVDChangeDir(): null pointer is specified to directory name  ");  
    entry = DVDConvertPathToEntrynum(dirName);
    ASSERTMSG2LINE(0x2A4, entry >= 0, "DVDChangeDir(): directory '%s' is not found under %s  ", dirName, (DVDGetCurrentDir(currentDir, 128), currentDir));
    ASSERTMSG1LINE(0x2A8, entryIsDir(entry), "DVDChangeDir(): file '%s' is specified as a directory name  ", dirName);
    
    if ((entry < 0) || (entryIsDir(entry) == FALSE)) {
        return FALSE;
    }
    
    currentDirectory = (u32)entry;
    
    return TRUE;
}

BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset,
                      DVDCallback callback, s32 prio) {

        ASSERTMSGLINE(0x2C7, fileInfo, "DVDReadAsync(): null pointer is specified to file info address  ");
        ASSERTMSGLINE(0x2C8, addr, "DVDReadAsync(): null pointer is specified to addr  ");
        ASSERTMSGLINE(0x2CC, !OFFSET(addr, 32), "DVDReadAsync(): address must be aligned with 32 byte boundaries  ");
        ASSERTMSGLINE(0x2CE, !(length & 0x1F), "DVDReadAsync(): length must be  multiple of 32 byte  ");
        ASSERTMSGLINE(0x2D0, !(offset & 3), "DVDReadAsync(): offset must be multiple of 4 byte  ");
        
        if (!((0 <= offset) && (offset < fileInfo->length))) {
            OSPanic(__FILE__, 0x2D5, "DVDReadAsync(): specified area is out of the file  ");
        }
        
        if (!((0 <= offset + length) && (offset + length < fileInfo->length + DVD_MIN_TRANSFER_SIZE))) {
            OSPanic(__FILE__, 0x2DB, "DVDReadAsync(): specified area is out of the file  ");
        }
        
        fileInfo->callback = callback;
        DVDReadAbsAsyncPrio(&(fileInfo->cb), addr, length, (s32)(fileInfo->startAddr + offset),
                            cbForReadAsync, prio);
        
        return TRUE;
}
#ifndef offsetof
#define offsetof(type, memb) ((u32) & ((type*)0)->memb)
#endif

static void cbForReadAsync(s32 result, DVDCommandBlock* block) {
  DVDFileInfo* fileInfo;

  fileInfo = (DVDFileInfo*)((char*)block - offsetof(DVDFileInfo, cb)); 
  ASSERTLINE(0x2ED, (void*) &fileInfo->cb == (void*) block);
  if (fileInfo->callback) {
    (fileInfo->callback)(result, fileInfo);
  }
}

long DVDReadPrio(struct DVDFileInfo * fileInfo, void * addr, long length, long offset, long prio) {
    int result;
    struct DVDCommandBlock * block;
    long state;
    int enabled;
    long retVal;

    ASSERTMSGLINE(0x30D, fileInfo, "DVDRead(): null pointer is specified to file info address  ");
    ASSERTMSGLINE(0x30E, addr, "DVDRead(): null pointer is specified to addr  ");
    ASSERTMSGLINE(0x312, !OFFSET(addr, 32), "DVDRead(): address must be aligned with 32 byte boundaries  ");
    ASSERTMSGLINE(0x314, !(length & 0x1F), "DVDRead(): length must be  multiple of 32 byte  ");
    ASSERTMSGLINE(0x316, !(offset & 3), "DVDRead(): offset must be multiple of 4 byte  ");

    if (!((0 <= offset) && (offset < fileInfo->length))) {
        OSPanic(__FILE__, 0x31B, "DVDRead(): specified area is out of the file  ");
    }

    if (!((0 <= offset + length) && (offset + length < fileInfo->length + DVD_MIN_TRANSFER_SIZE))) {
        OSPanic(__FILE__, 0x321, "DVDRead(): specified area is out of the file  ");
    }

    block = &fileInfo->cb;
    result = DVDReadAbsAsyncPrio(block, addr, length, fileInfo->startAddr + offset, cbForReadSync, prio);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while(1) {
        state = ((volatile DVDCommandBlock*)block)->state;
        if (state == 0) {
            retVal = (s32)block->transferredSize;
            break;
        } else if (state == -1) {
            retVal = -1;
            break;
        } else if (state == 10) {
            retVal = -6;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForReadSync() {
    OSWakeupThread(&__DVDThreadQueue);
}

int DVDSeekAsyncPrio(struct DVDFileInfo * fileInfo, long offset, void (* callback)(long, struct DVDFileInfo *), long prio) {
    ASSERTMSGLINE(0x368, fileInfo, "DVDSeek(): null pointer is specified to file info address  ");
    ASSERTMSGLINE(0x36C, !(offset & 3), "DVDSeek(): offset must be multiple of 4 byte  ");

    if (!((0 <= offset) && (offset < fileInfo->length))) {
        OSPanic(__FILE__, 0x371, "DVDSeek(): offset is out of the file  ");
    }

    fileInfo->callback = callback;
    DVDSeekAbsAsyncPrio(&fileInfo->cb, (u32)(char*)fileInfo->startAddr + offset, cbForSeekAsync, prio);
    return 1;
}

static void cbForSeekAsync(long result, struct DVDCommandBlock * block) {
    struct DVDFileInfo * fileInfo;

    fileInfo = (struct DVDFileInfo *)&block->next;
    ASSERTLINE(0x383, (void*) &fileInfo->cb == (void*) block);
    if (fileInfo->callback) {
      (fileInfo->callback)(result, fileInfo);
    }
}

long DVDSeekPrio(struct DVDFileInfo * fileInfo, long offset, long prio) {
    int result;
    struct DVDCommandBlock * block;
    long state;
    int enabled;
    long retVal;

    ASSERTMSGLINE(0x3A1, fileInfo, "DVDSeek(): null pointer is specified to file info address  ");
    ASSERTMSGLINE(0x3A5, !(offset & 3), "DVDSeek(): offset must be multiple of 4 byte  ");
    ASSERTMSGLINE(0x3A9, (offset >= 0) && ((u32) offset < (u32) fileInfo->length), "DVDSeek(): offset is out of the file  ");

    block = &fileInfo->cb;
    result = DVDSeekAbsAsyncPrio(block, (u32)(char*)fileInfo->startAddr + offset, cbForSeekSync, prio);
    if (!result) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while(1) {
        state = ((volatile DVDCommandBlock*)block)->state;
        if (state == 0) {
            retVal = 0;
            break;
        } else if (state == -1) {
            retVal = -1;
            break;
        } else if (state == 10) {
            retVal = -6;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForSeekSync() {
    OSWakeupThread(&__DVDThreadQueue);
}

long DVDGetFileInfoStatus(struct DVDFileInfo * fileInfo) {
    return fileInfo->cb.state;
}

int DVDOpenDir(char * dirName, DVDDir * dir) {
    long entry;
#if DEBUG
    char currentDir[128];
#endif

    ASSERTMSGLINE(0x401, dirName, "DVDOpendir(): null pointer is specified to directory name  ");
    entry = DVDConvertPathToEntrynum(dirName);
    ASSERTMSG2LINE(0x409, entry >= 0, "DVDOpendir(): directory '%s' is not found under %s  ", dirName, (DVDGetCurrentDir(currentDir, 128), currentDir));
    ASSERTMSG1LINE(0x40E, entryIsDir(entry), "DVDOpendir(): file '%s' is specified as a directory name  ", dirName);
    if (entry < 0 || !entryIsDir(entry)) {
        return 0;
    }
    dir->entryNum = entry;
    dir->location = entry + 1;
    dir->next = nextDir(entry);    
    return 1;
}

int DVDReadDir(DVDDir * dir, DVDDirEntry* dirent) {
    unsigned long loc;

    loc = dir->location;
    if ((loc <= (u32) dir->entryNum) || ((u32) dir->next <= loc)) {
        return 0;
    }
    dirent->entryNum = loc;
    dirent->isDir = entryIsDir(loc);
    dirent->name = FstStringStart + stringOff(loc);
    dir->location = entryIsDir(loc) ? nextDir(loc) : loc + 1;
    return 1;
}

int DVDCloseDir(DVDDir* dir) {
    return 1;
}

void * DVDGetFSTLocation() {
    return BootInfo->FSTLocation;
}

#define RoundUp32KB(x) (((u32)(x) + 32 * 1024 - 1) & ~(32 * 1024 - 1))
#define Is32KBAligned(x) (((u32)(x) & (32 * 1024 - 1)) == 0)

BOOL DVDPrepareStreamAsync(DVDFileInfo* fileInfo, u32 length, u32 offset, DVDCallback callback) {
    u32 start;
    
    ASSERTMSGLINE(0x46C, fileInfo, "DVDPrepareStreamAsync(): NULL file info was specified");
    
    start = fileInfo->startAddr + offset;
    
    if (!Is32KBAligned(start)) {
    OSPanic(__FILE__, 0x472,
        "DVDPrepareStreamAsync(): Specified start address (filestart(0x%x) + offset(0x%x)) is "
        "not 32KB aligned",
        fileInfo->startAddr, offset);
    }
    
    if (length == 0)
        length = fileInfo->length - offset;
    
    if (!Is32KBAligned(length)) {
    OSPanic(__FILE__, 0x47C,
        "DVDPrepareStreamAsync(): Specified length (0x%x) is not a multiple of 32768(32*1024)",
        length);
    }
    
    if (!((offset < fileInfo->length) && (offset + length <= fileInfo->length))) {
    OSPanic(__FILE__, 0x484,
        "DVDPrepareStreamAsync(): The area specified (offset(0x%x), length(0x%x)) is out of "
        "the file",
        offset, length);
    }
    
    fileInfo->callback = callback;
    return DVDPrepareStreamAbsAsync(&(fileInfo->cb), length, fileInfo->startAddr + offset,
                                    cbForPrepareStreamAsync);
}

static void cbForPrepareStreamAsync(s32 result, DVDCommandBlock* block) {
    DVDFileInfo* fileInfo;
    
    fileInfo = (DVDFileInfo*)((char*)block - offsetof(DVDFileInfo, cb));
    
    ASSERTLINE(0x497, (void*) &fileInfo->cb == (void*) block);
    
    if (fileInfo->callback) {
        (fileInfo->callback)(result, fileInfo);
    }
}

/* This is based on the revolution SDK, these may not match in all cases */
s32 DVDPrepareStream(DVDFileInfo* fileInfo, u32 length, u32 offset) {
    BOOL result;
    DVDCommandBlock* block;
    s32 state;
    BOOL enabled;
    s32 retVal;
    u32 start;
    
    ASSERTMSGLINE(0x4B9, fileInfo, "DVDPrepareStream(): NULL file info was specified");
    
    start = fileInfo->startAddr + offset;
    
    if (!Is32KBAligned(start)) {
        OSPanic(__FILE__, 0x4BF,
            "DVDPrepareStream(): Specified start address (filestart(0x%x) + offset(0x%x)) is not "
            "32KB aligned",
            fileInfo->startAddr, offset);
    }
    
    if (length == 0)
        length = fileInfo->length - offset;
    
    if (!Is32KBAligned(length)) {
        OSPanic(__FILE__, 0x4C9,
            "DVDPrepareStream(): Specified length (0x%x) is not a multiple of 32768(32*1024)",
            length);
    }
    
    if (!((offset < fileInfo->length) && (offset + length <= fileInfo->length))) {
      OSPanic(
        __FILE__, 0x4D1,
        "DVDPrepareStream(): The area specified (offset(0x%x), length(0x%x)) is out of the file",
        offset, length);
    }
    
    block = &(fileInfo->cb);
    result = DVDPrepareStreamAbsAsync(block, length, start, cbForPrepareStreamSync);
    
    if (result == FALSE) {
        return -1;
    }
    
    enabled = OSDisableInterrupts();
    
    while(1) {
        state = ((volatile DVDCommandBlock*)block)->state;
        
        if (state == DVD_STATE_END) {
            retVal = 0;
            break;
        }
        if (state == DVD_STATE_FATAL_ERROR) {
            retVal = DVD_RESULT_FATAL_ERROR;
            break;
        }
        if (state == DVD_STATE_CANCELED) {
            retVal = DVD_RESULT_CANCELED;
            break;
        }
        
        OSSleepThread(&__DVDThreadQueue);
    }
    
    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForPrepareStreamSync(s32 result, DVDCommandBlock* block) {
    OSWakeupThread(&__DVDThreadQueue);
}

s32 DVDGetTransferredSize(DVDFileInfo* fileinfo) {
    s32 bytes;
    DVDCommandBlock* cb;

    cb = &(fileinfo->cb);

    switch (cb->state) {
        case DVD_STATE_COVER_CLOSED:
        case DVD_STATE_NO_DISK:
        case DVD_STATE_COVER_OPEN:
        case DVD_STATE_WRONG_DISK:
        case DVD_STATE_FATAL_ERROR:
        case DVD_STATE_MOTOR_STOPPED:
        case DVD_STATE_CANCELED:
        case DVD_STATE_END:
            bytes = (s32)cb->transferredSize;
            break;
        case DVD_STATE_WAITING:
            bytes = 0;
            break;
        case DVD_STATE_BUSY:
            bytes = (s32)(cb->transferredSize + (cb->currTransferSize - __DIRegs[6]));
            break;
        default:
            ASSERTLINE(0x524, FALSE);
            break;
  }
  return bytes;
}
