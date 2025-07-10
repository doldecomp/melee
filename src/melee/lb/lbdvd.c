#include <placeholder.h>

#include "lbdvd.static.h"

#include "lb_0192.h"
#include "lbarchive.h"
#include "lbfile.h"
#include "lbheap.h"

#include "db/db.h"
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

#pragma push
#pragma dont_inline on
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
#pragma pop

bool lbDvd_80017598(int heap)
{
    PreloadEntry* entry;
    bool enabled;
    int i;
    bool no_change;

    no_change = false;
    enabled = OSDisableInterrupts();

    if (preloadCache.persistent_heap == heap) {
        no_change = true;
    } else {
        for (i = 0; i < 0x50; i++) {
            entry = &preloadCache.entries[i];
            if (entry->state != 0 && entry->heap == heap) {
                if (entry->state == 2) {
                    no_change = true;
                } else {
                    lbDvd_800174E8(i);
                }
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return no_change;
}

static bool lbDvd_80017644(int heap)
{
    PreloadEntry* entry;
    int enabled;
    int i;
    bool no_change;

    no_change = false;
    enabled = OSDisableInterrupts();
    if (preloadCache.persistent_heap == heap) {
        no_change = true;
    } else {
        for (i = 0; i < 0x50; i++) {
            entry = &preloadCache.entries[i];
            if ((entry->state == 3 || entry->state == 4) &&
                entry->heap == heap && entry->load_score < 0 &&
                entry->load_state == 2) {
                lbDvd_800174E8(i);
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return no_change;
}

void lbDvd_80017700(int arg0)
{
    while (lbDvd_80017644(arg0)) {
        lb_800195D0();
    }
}

inline int same(int a, int b) {
    int result = 0;
    if (a == b)
        result = 1;
    return result;
}

void* lbDvd_80017740(int type, int entry_num, s32 transient_heap, s32 heap, u32 size, s8 load_state, s16 load_score, s8 arg7, s32 effect_index)
{
    PreloadEntry* entry;
    s32 temp_ret;
    s32 var_ctr;
    s32 var_r0;
    s32 var_r22;
    s32 var_r4;

    var_ctr = 0x50;
    var_r22 = -1;
    var_r4 = 0;
loop_1:
    entry = &preloadCache.entries[var_r4];
    if (entry->state == 0) {
        if (var_r22 == -1) {
            var_r22 = var_r4;
        }
        goto block_13;
    }
    if (entry->entry_num == entry_num && same(entry->heap, transient_heap)) {
        if (entry->state == 1) {
            if (entry->load_score < 0) {
                entry->load_score *= -1;
                if (entry->load_score <= 0x2314) {
                    entry->load_score += 10;
                }
            }
        } else {
            entry->load_score = 0x270F;
        }
    } else {
block_13:
        var_r4 += 1;
        var_ctr -= 1;
        if (var_ctr == 0) {
            if (var_r22 == -1) {
                __assert("lbdvd.c", 0x1C1, "free_index != -1");
            }
            entry = &preloadCache.entries[var_r22];
            entry->state = 1;
            entry->type = type;
            entry->entry_num = entry_num;
            temp_ret = lbHeap_80015BB8(heap);
            if (temp_ret != 0) {
                OSReport("%d, %d\n", heap, entry_num);
                __assert("lbdvd.c", 0x1CB, "0");
            }
            entry->heap = heap;
            entry->size = size;
            entry->archive = NULL;
            entry->raw_data = NULL;
            entry->load_state = load_state;
            entry->load_score = load_score;
            entry->unknown004 = arg7;
            entry->effect_index = transient_heap;
        } else {
            goto loop_1;
        }
    }
    return entry;
}

void lbDvd_800178E8(int arg0, char* arg1, int arg2, int arg3, int arg4, u8 arg5, s16 arg6, u8 arg7, int arg8)
{
    u8 _[8];
    int temp_r3 = DVDConvertPathToEntrynum(lbFile_80016204(arg1));
    lbDvd_80017740(arg0, temp_r3, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

/// #lbDvd_80017960

void lbDvd_80017A80(void)
{
    preloadCache.persistent_heap = 6;
    lbDvd_80017CC4();
}

void lbDvd_CachePreloadedFile(s32 index)
{
    s32 heap;
    PreloadEntry* new_var5;
    PreloadEntry(*new_var2)[80];
    s32 size;
    PreloadCache* new_var;
    void* data;
    PreloadCache* preload_cache;
    PreloadEntry* entry;
    PreloadEntry* preloadEntry;
    s8 type;
    short new_var4;
    int i;

    preload_cache = &preloadCache;
    preloadEntry = &preloadCache.entries[index];
    new_var5 = &preloadCache.entries[0];
    heap = preloadCache.entries[index].heap;
    for (i = 0; i < 80; i++) {
        entry = &preloadCache.entries[i];
        new_var = preload_cache;
        if (entry->state == 3) {
            if (heap == entry->heap && entry->load_score < 0) {
                if (preloadCache.entries[i].archive != 0) {
                    lbHeap_80015CA8(entry->heap, entry->archive->addr);
                }
                if (new_var5->raw_data != 0) {
                    lbHeap_80015CA8(new_var5->heap, new_var5->raw_data->addr);
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
        if (preload_cache->entries[index].size == 0) {
            size = lbFile_8001634C(new_var->entries[0].entry_num);
            preloadEntry->size = size;
        }
        data = lbHeap_80015BD0(preloadEntry->heap,
                              (preloadEntry->size + 0x1F) & 0xFFFFFFE0);
        preloadEntry->raw_data = data;
        type = preloadEntry->type;
        if ((type == 2) || (((u8) (type - 3)) <= 1)) {
            data = (void*) lbHeap_80015BD0((s32) entry->heap, 0x44);
            preloadEntry->archive = data;
        }
        if (preloadEntry->raw_data == 0) {
            lbDvd_80017E64(0, index, 0, 1);
        } else if (preloadEntry->type == 0) {
            lbDvd_80017E64(0, index, 0, 0);
        } else {
            preloadEntry->state = 2;
            preloadEntry->load_score = 9999;
            lbFile_800164A4(new_var4 = preloadEntry->entry_num,
                            (u32) preloadEntry->raw_data->addr,
                            &preloadEntry->size, 2, lbDvd_80017E64,
                            (void*) index);
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

void* lbDvd_GetPreloadedArchive(s32 arg0)
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
    return (void*) entry->raw_data->addr;
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

void lbDvd_800189EC(int arg0)
{
    while (lbDvd_800187F4(arg0) == 1) {
        lb_800195D0();
    }
}

/// #lbDvd_80018A2C

void lbDvd_80018C2C(int arg0)
{
    while (lbDvd_80018A2C(arg0) == 1) {
        lb_800195D0();
    }
}

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
        break;

    case 2:
        preloadCache.scene.is_heap_persistent[0] = 1;
        preloadCache.scene.is_heap_persistent[1] = 1;
        break;

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
        break;
    case 0:
        break;
    }
}

static s32 lbDvd_804D37F4[2] = { 4, 5 };

void lbDvd_80018CF4(int arg0)
{
    int tmp;
    int i;

    if (preloadCache.persistent_heaps != arg0) {
        preloadCache.scene.major_scene_changes =
            preloadCache.new_scene.major_scene_changes + 1;
    }
    preloadCache.persistent_heaps = arg0;
    lbHeap_800158D0(2, 1);
    lbHeap_800158D0(3, 1);

    for (i = 0; i < 2U; i++) {
        lbHeap_800158D0(lbDvd_804D37F4[i], 1);
    }
    switch (preloadCache.persistent_heaps) {
    case 0:
        preloadCache.scene = lbDvd_803BA638.scene;
        break;
    case 1:
        lbHeap_800158D0(2, 0);
        preloadCache.scene = lbDvd_803BA638.scene;
        break;
    case 2:
        lbHeap_800158D0(2, 0);
        lbHeap_800158D0(3, 0);
        preloadCache.scene = lbDvd_803BA638.scene;
        break;
    case 3:
        lbHeap_800158D0(2, 0);
        lbHeap_800158D0(3, 0);
        for (i = 0; i < 2U; i++) {
            lbHeap_800158D0(lbDvd_804D37F4[i], 0);
        }
        break;
    }
    if (lbHeap_800158E8(2) == 1) {
        while (lbDvd_80017598(2) != 0) {
            lb_800195D0();
        }
    }
    if (lbHeap_800158E8(3) == 1) {
        while (lbDvd_80017598(3) != 0) {
            lb_800195D0();
        }
    }
    for (i = 0; i < 2U; i++) {
        if (lbHeap_800158E8(lbDvd_804D37F4[i]) == 1) {
            tmp = lbDvd_804D37F4[i];
            while (lbDvd_80017598(tmp) != 0) {
                lb_800195D0();
            }
        }
    }
    lbHeap_80015900();
}

void lbDvd_80018F58(bool value)
{
    preloadCache.preloaded = value;
}

/// #lbDvd_80018F68

/// #lbDvd_80019100
