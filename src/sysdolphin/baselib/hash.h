#ifndef _hash_h_
#define _hash_h_

#include <platform.h>
#include "baselib/forward.h"

#include "baselib/class.h"

#define hash(s) (s % 0x65)

struct HSD_HashEntry {
    HSD_HashEntry* next;
    void* key;
    void* value;
};

typedef struct _HSD_HashClass {
    struct _HSD_HashInfo* class_info;
} HSD_HashClass;

typedef struct _HSD_HashInfo {
    HSD_ClassInfo parent;
    int (*getidx)(HSD_Hash* hash);
} HSD_HashClassInfo;

struct HSD_Hash {
    HSD_HashClass parent;
    HSD_HashEntry** table;
    u32 table_size;
};

HSD_HashEntry* HashSearchEntry(HSD_Hash*, int, void*, HSD_HashEntry**);
HSD_ClassInfo* HSD_HashSearch(HSD_Hash*, void*, int*);

#endif
