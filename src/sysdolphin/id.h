#ifndef _id_h_
#define _id_h_

#include "global.h"

#include "objalloc.h"

typedef struct _IDEntry {
    struct _IDEntry* next;
    u32 id;
    void* data;
} IDEntry;

typedef struct _HSD_IDTable {
    struct _IDEntry table[101];
} HSD_IDTable;

HSD_ObjAllocData* HSD_IDGetAllocData(void);
void HSD_IDInitAllocData(void);
void HSD_IDSetup(void);

#endif
