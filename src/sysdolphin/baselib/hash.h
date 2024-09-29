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
    struct _HSD_HashClassInfo* class_info;
} HSD_HashClass;

typedef struct _HSD_HashClassInfo {
    HSD_ClassInfo parent;
    int (*getidx)(HSD_Hash* hash);
    bool (*keycheck)(HSD_Hash* hash, void* table_key, void* key);
} HSD_HashClassInfo;

struct HSD_Hash {
    HSD_HashClass parent;
    HSD_HashEntry** table;
    u32 table_size;
};

HSD_HashEntry* HashSearchEntry(HSD_Hash*, int, void*, HSD_HashEntry**);
HSD_HashClassInfo* HSD_HashSearch(HSD_Hash*, void*, int*);

#endif
