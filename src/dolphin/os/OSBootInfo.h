#ifndef DOLPHIN_OS_OSBOOTINFO_H_

#include <platform.h>

#include <dolphin/dvd/dvd.h>

typedef struct OSBootInfo {
    DVDDiskID DVDDiskID; // _00
    u32 magic;           // _20
    u32 version;         // _24
    u32 memorySize;      // _28
    u32 consoleType;     // _2C
    void* arenaLo;       // _30, overrides __ArenaLo if non-null
    void* arenaHi;       // _34, overrides FSTLocation if non-null
    void* FSTLocation;   // _38, start addr of FST area
    u32 FSTMaxLength;    // _3C, length of FST area
} OSBootInfo;

#endif
