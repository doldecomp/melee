#include "hash.h"

#include "debug.h"

HSD_ClassInfo* HSD_HashSearch(HSD_Hash* hashp, void* key, int* success)
{
    HSD_HashEntry* entry;
    u32 idx;

    idx = hashp->parent.class_info->getidx(hashp);
    HSD_ASSERT(113, idx < hashp->table_size);
    entry = HashSearchEntry(hashp, idx, key, NULL);
    if (success != NULL) {
        *success = !!entry;
    }
    if (entry != NULL) {
        return (HSD_ClassInfo*) entry->value;
    }
    return NULL;
}
