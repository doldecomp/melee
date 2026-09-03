#include "hash.h"

#include "debug.h"

HSD_HashEntry* HashSearchEntry(HSD_Hash* hash, int idx, void* key,
                               HSD_HashEntry** ptr)
{
    if (hash->table[idx] == NULL) {
        return NULL;
    }
    if (ptr != NULL) {
        HSD_HashEntry** entry;
        for (entry = &hash->table[idx]; *entry != NULL;
             entry = &((*entry)->next))
        {
            if (hash->parent.class_info->keycheck(hash, (*entry)->key, key) ==
                0)
            {
                *ptr = (HSD_HashEntry*) entry;
                return *entry;
            }
        }
    } else {
        HSD_HashEntry* entry;
        for (entry = hash->table[idx]; entry != NULL; entry = entry->next) {
            if (hash->parent.class_info->keycheck(hash, entry->key, key) == 0)
            {
                return entry;
            }
        }
    }
    return NULL;
}

HSD_HashClassInfo* HSD_HashSearch(HSD_Hash* hash, void* key, int* success)
{
    HSD_HashEntry* entry;
    u32 idx;

    idx = hash->parent.class_info->getidx(hash);
    HSD_ASSERT(113, idx < hash->table_size);
    entry = HashSearchEntry(hash, idx, key, NULL);
    if (success != NULL) {
        *success = !!entry;
    }
    if (entry != NULL) {
        return (HSD_HashClassInfo*) entry->value;
    }
    return NULL;
}
