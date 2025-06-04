#include <placeholder.h>

#include "lbdvd.static.h"

#include "lbarchive.h"
#include "lbfile.h"
#include "lbheap.h"

#include "db/db_2253.h"
#include "ef/efasync.h"
#include "gr/grdatfiles.h"
#include "lb/types.h"

#include <dolphin/dvd.h>
#include <dolphin/os/OSInterrupt.h>
#include <baselib/debug.h>

void lbDvd_800174BC(void)
{
    lbDvd_80018C6C();
    lbDvd_80018254();
    lbDvd_80017700(4);
}

void lbDvd_800174E8(s32 index)
{
    PreloadEntry* entry = &preloadCache.entries[index];
    if (entry->archive != NULL) {
        lbHeap_80015CA8(entry->heap, entry->archive->addr);
    }
    if (entry->raw_data != NULL) {
        lbHeap_80015CA8(entry->heap, entry->raw_data->addr);
    }
    *entry = lbDvd_803BA68C;
}

bool lbDvd_80017598(bool cached)
{
    PreloadCache* var_r31;
    bool intr;
    int var_r29;
    bool var_r28;

    var_r28 = 0;
    intr = OSDisableInterrupts();
    var_r31 = &preloadCache;
    if (preloadCache.preloaded == cached) {
        var_r28 = 1;
    } else {
        var_r29 = 0;
        do {
            if (var_r31->entries[0].state != 0 &&
                var_r31->entries[0].heap == cached)
            {
                if (var_r31->entries[0].state == 2) {
                    var_r28 = 1;
                } else {
                    lbDvd_800174E8(var_r29);
                }
            }
            var_r29 += 1;
            var_r31 += 1;
        } while (var_r29 < 0x50);
    }
    OSRestoreInterrupts(intr);
    return var_r28;
}

/// #lbDvd_80017644

/// #lbDvd_80017700

void* lbDvd_80017740(int type, s16 entry_num, s32 transient_heap, s32 heap,
                     u32 size, s8 load_state, s16 load_score, s8 arg7,
                     s32 effect_index)
{
    s32 var_ctr;
    PreloadEntry* entry;
    s32 free_index;
    s32 curr_index;
    PreloadCache* preload_cache;
    free_index = -1;
    var_ctr = effect_index;
    preload_cache = &preloadCache;
    curr_index = 0;
    entry = &(&preloadCache)->entries[curr_index];
    curr_index = (s8) preload_cache->entries[curr_index].state;
    while (1) {
        if (curr_index == 0) {
            if (free_index != (-1)) {
                break;
            }
            free_index = curr_index;
        } else if (entry->entry_num == entry_num) {
            if (entry->heap == transient_heap) {
                if ((entry->state) == 1) {
                    if (entry->load_score < 0) {
                        entry->load_score *= -1;
                        if (entry->load_score <= 0x2314) {
                            entry->load_score += 0xA;
                        }
                    }
                } else {
                    entry->load_score = 0x270F;
                }
            }
        }
        break;
    }

    curr_index = (var_ctr = 1);
    if (var_ctr == ((free_index != (-1)) * 0)) {
        if (free_index == (-1)) {
            __assert(lbDvd_804D37D0, 0x1C1, lbDvd_803BA6A8);
            entry = &(&preloadCache)->entries[free_index];
        }
        entry = &(&preloadCache)->entries[free_index];
        entry->state = 1;
        entry->type = (((s8) type) & 0xFF);
        entry->entry_num = ((s16) entry_num) & 0xFFFFu;
        if (lbHeap_80015BB8(heap) != 0) {
            OSReport(lbDvd_804D37D8, heap, entry_num);
            __assert(__FILE__, 0x1CB, lbDvd_804D37E0);
        }
        entry->heap = heap;
        entry->size = size;
        entry->raw_data = (entry->archive = 0);
        entry->load_state = (s8) (curr_index = load_state);
        entry->load_score = (s16) (load_score & 0xFFFFFFFF);
        entry->unknown004 = arg7;
        entry->effect_index = effect_index;
    }
    return entry;
}

/// #lbDvd_800178E8

/// #lbDvd_80017960

/// #lbDvd_80017A80

void lbDvd_CachePreloadedFile(s32 index)
{
    s32 heap;
    s32 new_var3;
    PreloadEntry* new_var5;
    PreloadEntry(*new_var2)[80];
    s32 size;
    PreloadCache* new_var;
    HSD_AllocEntry* data;
    PreloadCache* preload_cache;
    PreloadEntry* entry;
    PreloadEntry* preloadEntry;
    PreloadEntry* unk_preloadEntry;
    s8 type;
    short new_var4;
    s32 i = 0;
    preload_cache = &preloadCache;
    new_var3 = index;
    preloadEntry = &preload_cache->entries[new_var3];
    new_var5 = &preloadCache.entries[0];
    heap = preload_cache->entries[new_var3].heap;
    unk_preloadEntry = &lbDvd_803BA68C;
    for (i = 0; i < 80; i++) {
        entry = &preloadCache.entries[0];
        new_var = preload_cache;
        if (new_var->entries[0].state == 3) {
            if ((heap == entry->heap) && (entry->load_score < 0)) {
                if ((&preloadCache)->entries[0].archive != 0) {
                    lbHeap_80015CA8((s8) entry->heap, entry->archive->addr);
                }
                if (new_var5->raw_data != 0) {
                    lbHeap_80015CA8((s8) new_var5->heap,
                                    new_var5->raw_data->addr);
                }
                *new_var5 = lbDvd_803BA68C;
            }
        }
    }

    preload_cache->persistent_heap = heap;
    new_var2 = &new_var->entries;
    heap = lbHeap_80015D6C(heap, lbDvd_80017A80, heap);
    if (heap == 0) {
        preload_cache->persistent_heap = 6;
        if (preload_cache->entries[new_var3].size == 0) {
            size = lbDvd_8001634C((*new_var2)[0].entry_num);
            new_var->entries[new_var3].size = size;
        }
        data = lbDvd_80015BD0((s32) preload_cache->entries[index].heap,
                              (preloadEntry->size + 0x1F) & 0xFFFFFFE0);
        preload_cache->entries[index].raw_data = data;
        type = preloadEntry->type;
        if ((type == 2) || (((u8) (type - 3)) <= 1)) {
            data = lbDvd_80015BD0((s32) entry->heap, 0x44);
            new_var->entries[0].archive = data;
        }
        if (preloadEntry->raw_data == 0) {
            lbDvd_80017E64(0, new_var3, 0, 1);
        } else if (preloadEntry->type == 0) {
            lbDvd_80017E64(0, new_var3, 0, 0);
        } else {
            preloadEntry->state = 2;
            preloadEntry->load_score = 9999;
            lbFile_800164A4(new_var4 = preloadEntry->entry_num,
                            *(u32*) preloadEntry->raw_data->addr,
                            &preloadEntry->size, 2, lbDvd_80017E64,
                            (void*) new_var3);
        }
    }
}

void lbDvd_80017CC4(void)
{
    PreloadEntry* entry;
    s32 file_to_cache;
    s32 file_already_cached;
    int max_load_score;
    int i;

    file_already_cached = -1;
    max_load_score = 0;
    file_to_cache = -1;

    if (preloadCache.persistent_heap == 6) {
        for (i = 0; i < 80; i++) {
            entry = &preloadCache.entries[i];
            switch (preloadCache.entries[i].state) {
            case 0:
            case 3:
                break;
            case 2:
                file_already_cached = i;
                break;
            case 1:
                if (entry->load_score > max_load_score) {
                    max_load_score = entry->load_score;
                    file_to_cache = i;
                }
                break;
            }
        }

        if (file_already_cached == -1 && file_to_cache != -1) {
            lbDvd_CachePreloadedFile(file_to_cache);
        }
    }
}

void lbDvd_80017E64(void* key, int index, void* value, bool cancelflag)
{
    PreloadEntry* preloadEntry = &preloadCache.entries[index];
    if (cancelflag != 0) {
        __assert(__FILE__, 827, "0");
    } else {
        preloadEntry->state = 3;
    }
    lbDvd_80017CC4();
}

HSD_Archive* lbDvd_GetPreloadedArchive(s32 arg0)
{
    s8 type;
    ssize_t i;
    s32 interrupt;
    PreloadEntry* entry;

    interrupt = OSDisableInterrupts();

    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        entry = &preloadCache.entries[i];
        if ((s8) entry->state != 0 && entry->load_score > 0 &&
            (s16) entry->entry_num == arg0)
        {
            break;
        }
    }

    if (i == 80) {
        OSRestoreInterrupts(interrupt);
        return 0;
    }

    if (((s32) entry->state) == 1) {
        entry->load_score = 8980;
    }

    OSRestoreInterrupts(interrupt);
    lbDvd_800189EC(arg0);
    if (((s32) entry->load_state) == 1) {
        PreloadEntry* entry = &preloadCache.entries[i];
        type = entry->type;

        switch (type) {
        case 2:
            lbArchive_InitializeDAT((HSD_Archive*) entry->archive->addr,
                                    (u8*) entry->raw_data->addr, entry->size);
            break;

        case 3:
            efAsync_8006730C((HSD_Archive*) entry->archive->addr,
                             (u8*) entry->raw_data->addr, entry->size,
                             entry->effect_index);
            break;

        case 4:
            grDatFiles_801C5FC0((HSD_Archive*) entry->archive->addr,
                                entry->raw_data->addr, entry->size);
            break;

        default:
            __assert(__FILE__, 864, "0");
            break;
        }

        entry->load_state = 2;
    }
    if (entry->archive) {
        return (HSD_Archive*) entry->archive->addr;
    }
    return (HSD_Archive*) entry->raw_data->addr;
}

HSD_Archive* lbDvd_8001819C(const char* basename)
{
    HSD_Archive* archive;
    char* filename = lbFile_80016204(basename);
    archive = lbDvd_GetPreloadedArchive(DVDConvertPathToEntrynum(filename));
    if (g_debugLevel != 0 && preloadCache.preloaded && archive == NULL) {
        OSReport("[LbDvd] %s is not PRELOADed.\n", filename);
        __assert(__FILE__, 948, "0");
    }
    return archive;
}

PreloadCacheScene* lbDvd_8001822C(void)
{
    return &preloadCache.scene;
}

void lbDvd_8001823C(void)
{
    preloadCache.scene.major_scene_changes =
        preloadCache.new_scene.major_scene_changes + 1;
}

/// #lbDvd_80018254

/// #lbDvd_800187F4

/// #lbDvd_800189EC

/// #lbDvd_80018A2C

/// #lbDvd_80018C2C

void lbDvd_80018C6C(void)
{
    PreloadCache* new_var;
    PreloadCache* var_r5;
    int new_var2;
    PreloadCacheScene temp_r3;
    s32 i;
    PreloadCache* var_r4 = &preloadCache;
    switch (preloadCache.persistent_heaps) {
    case 1:
        preloadCache.scene.is_heap_persistent[0] = 1;
        return;

    case 2:
        preloadCache.scene.is_heap_persistent[0] = 1;
        preloadCache.scene.is_heap_persistent[1] = 1;
        return;

    case 3:
        new_var = &preloadCache;
        preloadCache.scene.is_heap_persistent[0] = 1;
        i = 9;
        preloadCache.scene.is_heap_persistent[1] = 1;
        var_r5 = &lbDvd_803BA638;
        temp_r3 = var_r5->new_scene;
        var_r5 += 1;
        var_r4 += 1;
        var_r4->new_scene = temp_r3;
        return;
    case 0:
        return;
    }
}

/// #lbDvd_80018CF4

void lbDvd_80018F58(bool value)
{
    preloadCache.preloaded = value;
}

/// #lbDvd_80018F68

/// #lbDvd_80019100
