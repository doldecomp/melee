#include "hash.h"

#include "debug.h"

HSD_ClassInfo* HSD_HashSearch(HSD_Hash* hash, void* key, int* success)
{
    HSD_HashEntry* entry;
    int idx;

    idx = hash->parent.class_info->getidx(hash);
    HSD_ASSERT(113, idx < hash->table_size);
    entry = HashSearchEntry(hash, idx, key, NULL);
    if (success != NULL) {
        *success = !!entry;
    }
    if (entry != NULL) {
        return (HSD_ClassInfo*) entry->value;
    }
    return NULL;
}
