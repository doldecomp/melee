#ifndef _METROTRK_MEMMAP_H
#define _METROTRK_MEMMAP_H

#include <platform.h>

#include "MetroTRK/trk.h"

typedef struct memRange {
    /* 0x00 */ u8* start;
    /* 0x04 */ u8* end;
    /* 0x08 */ bool readable;
    /* 0x0C */ bool writeable;
} memRange; // size = 0x10

const memRange gTRKMemMap[] = { { (u8*) 0x00000000, (u8*) 0xFFFFFFFF, true,
                                  true } };

#endif
