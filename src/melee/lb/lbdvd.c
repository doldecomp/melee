#include "lb_0192.h"
#include "lbarchive.h"

#include "lbdvd.static.h"

#include "lbfile.h"
#include "lbheap.h"
#include "types.h"

#include <placeholder.h>

#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/gr/grdatfiles.h>
#include <melee/gr/stage.h>
#include <melee/pl/player.h>
#include <melee/gm/gm_unsplit.h>

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
void lbDvd_800174E8(int index)
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
        for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
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
        for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
            entry = &preloadCache.entries[i];
            if ((entry->state == 3 || entry->state == 4) &&
                entry->heap == heap && entry->load_score < 0 &&
                entry->load_state == 2)
            {
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

inline int same(int a, s32 b)
{
    int result = 0;
    if (a == b) {
        result = 1;
    }
    return result;
}

void* lbDvd_80017740(int type, int entry_num, int transient_heap, int heap,
                     u32 size, int load_state, int load_score, u8 arg7,
                     int effect_index)
{
    PreloadEntry* entry;
    int free_index = -1;
    int i;

    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        entry = &preloadCache.entries[i];
        if (entry->state == 0) {
            if (free_index == -1) {
                free_index = i;
            }
        } else if (entry->entry_num == entry_num && same(entry->heap, transient_heap)) {
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
            goto done;
        }
    }

    if (free_index == -1) {
        __assert("lbdvd.c", 0x1C1, "free_index != -1");
    }
    entry = &preloadCache.entries[free_index];
    entry->state = 1;
    entry->type = type;
    entry->entry_num = entry_num;
    if (lbHeap_80015BB8(heap)) {
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
    entry->effect_index = effect_index;

done:
    return entry;
}

void lbDvd_800178E8(int arg0, char* arg1, int arg2, int arg3, int arg4,
                    int arg5, int arg6, u8 arg7, int arg8)
{
    u8 _[8];
    int temp_r3 = DVDConvertPathToEntrynum(lbFile_80016204(arg1));
    lbDvd_80017740(arg0, temp_r3, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

void lbDvd_80017960(void)
{
    int j;
    struct GameCache* game_cache = &preloadCache.new_scene.game_cache;
    int i;
    u8 _[4];

    if (preloadCache.new_scene.game_cache.major_id != MJ_COUNT) {
        switch (preloadCache.new_scene.game_cache.major_id) {
        case MJ_CAMERA_MODE:
            gm_801B23F0();
            break;
        }
    }

    if (game_cache->stage_id != 0x148) {
        Stage_802251B4(game_cache->stage_id);
    }

    for (i = 0; i < 8; i++) {
        if (game_cache->entries[i].char_id != CHKIND_NONE) {
            Player_80031CB0(game_cache->entries[i].char_id, game_cache->entries[i].color);
        }
        if (game_cache->entries[i].char_id == CKIND_KIRBY) {
            if (game_cache->entries[i].x5 == 0) {
                CharacterKind kind;
                for (kind = 0; kind < CHKIND_MAX; kind++) {
                    Player_80031D2C(kind, game_cache->entries[i].color);
                }
            } else {
                for (j = 0; j < 8; j++) {
                    if (game_cache->entries[j].char_id != CHKIND_NONE) {
                        if (game_cache->entries[j].char_id == CKIND_KIRBY && game_cache->entries[j].x5 == 0) {
                            CharacterKind kind;
                            for (kind = 0; kind < CHKIND_MAX; kind++) {
                                Player_80031D2C(kind, game_cache->entries[i].color);
                            }
                        }
                        Player_80031D2C(game_cache->entries[j].char_id, game_cache->entries[i].color);
                    }
                }
            }
        }
    }
}

void lbDvd_80017A80(void)
{
    preloadCache.persistent_heap = 6;
    lbDvd_80017CC4();
}

void lbDvd_CachePreloadedFile(s32 index)
{
    int heap;
    s32 i;
    PreloadEntry* preloadEntry;
    PreloadEntry* entry;
    entry = &preloadCache.entries[index];
    preloadEntry = entry;
    heap = preloadEntry->heap;

    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        entry = &preloadCache.entries[i];
        if (entry->state == 3) {
            if (entry->heap == heap && entry->load_score < 0) {
                entry = &preloadCache.entries[i];
                if (entry->archive != 0) {
                    lbHeap_80015CA8(entry->heap, entry->archive->addr);
                }
                if (entry->raw_data != 0) {
                    lbHeap_80015CA8(entry->heap, entry->raw_data->addr);
                }
                *entry = lbDvd_803BA68C;
            }
        }
    }

    preloadCache.persistent_heap = heap;
    heap = lbHeap_80015D6C(heap, lbDvd_80017A80, heap);

    if (heap == 0) {
        preloadCache.persistent_heap = 6;
    }

    if (heap == 0) {
        if (preloadEntry->size == 0) {
            preloadEntry->size = lbFile_8001634C(preloadEntry->entry_num);
        }
        preloadEntry->raw_data = lbHeap_80015BD0(preloadEntry->heap, OSRoundUp32B(preloadEntry->size));
        if (preloadEntry->type == 2 || preloadEntry->type == 3 || preloadEntry->type == 4) {
            preloadEntry->archive = lbHeap_80015BD0(preloadEntry->heap, sizeof(HSD_Archive));
        }
        if (preloadEntry->raw_data == 0) {
            lbDvd_80017E64(0, index, 0, 1);
        } else if (preloadEntry->type == 0) {
            lbDvd_80017E64(0, index, 0, 0);
        } else {
            preloadEntry->state = 2;
            preloadEntry->load_score = 9999;
            lbFile_800164A4(preloadEntry->entry_num,
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
        for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
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

void lbDvd_80017E64(int key, int index, void* value, bool cancelflag)
{
    PreloadEntry* preloadEntry = &preloadCache.entries[index];
    if (cancelflag != 0) {
        __assert(__FILE__, 827, "0");
    } else {
        preloadEntry->state = 3;
    }
    lbDvd_80017CC4();
}

void* lbDvd_GetPreloadedArchive(ssize_t entry_num)
{
    s8 type;
    ssize_t i;
    s32 interrupt;
    PreloadEntry* entry;

    interrupt = OSDisableInterrupts();

    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        entry = &preloadCache.entries[i];
        if (entry->state != 0 && entry->load_score > 0 &&
            entry->entry_num == entry_num)
        {
            break;
        }
    }

    if (i == 80) {
        OSRestoreInterrupts(interrupt);
        return 0;
    }

    if (entry->state == 1) {
        entry->load_score = 8980;
    }

    OSRestoreInterrupts(interrupt);
    lbDvd_800189EC(entry_num);
    if (entry->load_state == 1) {
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

struct lbDvd_803B72C0_t {
    u8 x0;
    char* x4;
    int x8;
};

static void inline1(void)
{
    struct lbDvd_803B72C0_t spA0 = { 2, "LbRb.dat" };
    if (preloadCache.new_scene.is_heap_persistent[0]) {
        const char* x4 = spA0.x4;
        int x8 = spA0.x8;
        u8 tmp = spA0.x0;
        int temp_r3_2 = DVDConvertPathToEntrynum(lbFile_80016204(x4));
        lbDvd_80017740(tmp, temp_r3_2, 2, 2, 0, 1, 9, 0x80, x8);
    }
}

static void inline2(void)
{
    int i;
    int temp_r3_6;
    struct lbDvd_803B72C0_t sp28[4] = {
        { 3, "EfMnData.dat", 0x1F },
        { 3, "EfCoData.dat" },
        { 2, "ItCo." },
        { 2, "IfAll" },
    };
    if (preloadCache.new_scene.is_heap_persistent[1]) {
        for (i = 0; i < ARRAY_SIZE(sp28); i++) {
            int temp_r29_2 = sp28[i].x8;
            u8 temp_r27_2 = sp28[i].x0;
            const char* tmp = sp28[i].x4;
            temp_r3_6 = DVDConvertPathToEntrynum(lbFile_80016204(tmp));
            lbDvd_80017740(temp_r27_2, temp_r3_6, 3, 3, 0, 1, 8, 0x40, temp_r29_2);
        }
    }
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

void lbDvd_80018254(void)
{
    bool enabled;
    PreloadEntry* entry;
    struct lbDvd_803B72C0_t* var_r26;
    int i;

    u8 _[0x18];

    if (memcmp(&preloadCache.new_scene, &preloadCache.scene, sizeof(PreloadCacheScene)) == 0) {
        return;
    }

    preloadCache.new_scene = preloadCache.scene;
    enabled = OSDisableInterrupts();

    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        entry = &preloadCache.entries[i];
        if (entry->state != 0) {
            if (entry->load_score > 0) {
                entry->load_score *= -1;
            }
        }
    }

    switch (preloadCache.persistent_heaps) {
    case 0:
        break;
    case 1:
        inline1();
        break;
    case 2:
        inline1();
        inline2();
        break;
    case 3:
        inline1();
        inline2();
        lbDvd_80017960();
        break;
    }

    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        entry = &preloadCache.entries[i];
        if (entry->load_score < 0) {
            if (entry->state == 1) {
                if (preloadCache.entries[i].archive != NULL) {
                    lbHeap_80015CA8(entry->heap, entry->archive->addr);
                }
                if (entry->raw_data != NULL) {
                    lbHeap_80015CA8(entry->heap, entry->raw_data->addr);
                }
                *entry = lbDvd_803BA68C;
            } else if (entry->state == 4) {
                entry->state = 3;
            }
        }
    }

    lbDvd_80017CC4();
    OSRestoreInterrupts(enabled);
}

static inline void inline3(PreloadEntry* entry, bool* var_r9, bool* var_r10)
{
    int i;
    PreloadEntry* other;
    *var_r10 = false;
    *var_r9 = false;
    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        other = &preloadCache.entries[i];
        if (other->state == 1 && other->heap == entry->heap && other->load_score > 0) {
            *var_r9 = true;
        }
        if ((other->state == 2 || other->state == 3) && other->heap == entry->heap && other->load_score < 0) {
            *var_r10 = true;
        }
    }
}

static inline void inline3_alt(PreloadEntry* entry, bool* var_r9, bool* var_r10)
{
    PreloadEntry* other;
    int i;
    *var_r10 = false;
    *var_r9 = false;
    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        other = &preloadCache.entries[i];
        if (other->state == 1 && other->heap == entry->heap && other->load_score > 0) {
            *var_r9 = true;
        }
        if ((other->state == 2 || other->state == 3) && other->heap == entry->heap && other->load_score < 0) {
            *var_r10 = true;
        }
    }
}

int lbDvd_800187F4(int entry_num)
{
    int result = 0;
    PreloadEntry* entry;
    int i;

    bool enabled = OSDisableInterrupts();
    bool var_r9;
    bool var_r10;

    int persistent_heap = preloadCache.persistent_heap;

    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        entry = &preloadCache.entries[i];
        if (entry->state == 0) {
            continue;
        }

        if (entry->load_score <= 0) {
            continue;
        }

        if (entry->entry_num != entry_num) {
            continue;
        }

        if (entry->heap == persistent_heap) {
            result = 1;
            break;
        }

        switch (entry->state) {
        case 1:
        case 2:
            result = 1;
            break;
        case 3:
            inline3(entry, &var_r9, &var_r10);
            if (var_r9 && var_r10) {
                result = 1;
                break;
            }
            entry->state = 4;
            entry->load_score = 0x270F;
        case 4:
            result = 2;
            break;
        default:
            continue;
        }
        break;
    }

    OSRestoreInterrupts(enabled);
    return result;
}

void lbDvd_800189EC(int entry_num)
{
    while (lbDvd_800187F4(entry_num) == 1) {
        lb_800195D0();
    }
}

int lbDvd_80018A2C(u8 arg0)
{
    bool var_r31_2;
    bool var_r30;
    int result = 0;
    PreloadEntry* entry;
    bool enabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 0x50; i++) {
        entry = &preloadCache.entries[i];
        if (entry->state == 0) {
            continue;
        }
        if (entry->load_score <= 0) {
            continue;
        }
        if (!(entry->unknown004 & arg0)) {
            continue;
        }

        if (entry->heap == preloadCache.persistent_heap) {
            result = 1;
            break;
        }

        switch (entry->state) {
        case 1:
        case 2:
            result = 1;
            break;
        case 3:
            var_r30 = 0;
            var_r31_2 = 0;
            inline3_alt(entry, &var_r31_2, &var_r30);
            if (var_r31_2 && var_r30) {
                result = 1;
                break;
            }
            entry->state = 4;
            entry->load_score = 0x270F;
        case 4:
            result = 2;
            continue;
        default:
            continue;
        }
        break;
    }

    OSRestoreInterrupts(enabled);
    return result;
}

void lbDvd_80018C2C(u8 arg0)
{
    while (lbDvd_80018A2C(arg0) == 1) {
        lb_800195D0();
    }
}

void lbDvd_80018C6C(void)
{
    switch (preloadCache.persistent_heaps) {
    case 1:
        preloadCache.scene.is_heap_persistent[0] = true;
        break;
    case 2:
        preloadCache.scene.is_heap_persistent[0] = true;
        preloadCache.scene.is_heap_persistent[1] = true;
        break;
    case 3:
        preloadCache.scene.is_heap_persistent[0] = true;
        preloadCache.scene.is_heap_persistent[1] = true;
        preloadCache.scene.game_cache = lbDvd_803BA638.game_cache;
    case 0:
        break;
    }
}

static s32 lbDvd_804D37F4[2] = { 4, 5 };

static inline void inline0(void)
{
    int i;
    int tmp;
    for (i = 0; i < ARRAY_SIZE(lbDvd_804D37F4); i++) {
        if (lbHeap_800158E8(lbDvd_804D37F4[i]) == 1) {
            tmp = lbDvd_804D37F4[i];
            while (lbDvd_80017598(tmp) != 0) {
                lb_800195D0();
            }
        }
    }
}

void lbDvd_80018CF4(int arg0)
{
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
        preloadCache.scene.is_heap_persistent[0] = lbDvd_803BA638.is_heap_persistent[0];
        preloadCache.scene.is_heap_persistent[1] = lbDvd_803BA638.is_heap_persistent[1];
        preloadCache.scene.game_cache = lbDvd_803BA638.game_cache;
        break;
    case 1:
        lbHeap_800158D0(2, 0);
        preloadCache.scene.is_heap_persistent[1] = lbDvd_803BA638.is_heap_persistent[1];
        preloadCache.scene.game_cache = lbDvd_803BA638.game_cache;
        break;
    case 2:
        lbHeap_800158D0(2, 0);
        lbHeap_800158D0(3, 0);
        preloadCache.scene.game_cache = lbDvd_803BA638.game_cache;
        break;
    case 3:
        lbHeap_800158D0(2, 0);
        lbHeap_800158D0(3, 0);
        for (i = 0; i < ARRAY_SIZE(lbDvd_804D37F4); i++) {
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
    inline0();
    lbHeap_80015900();
}

void lbDvd_80018F58(bool value)
{
    preloadCache.preloaded = value;
}

void lbDvd_80018F68(void)
{
    int i;
    preloadCache.persistent_heaps = 0;
    preloadCache.scene = lbDvd_803BA638;
    preloadCache.new_scene = lbDvd_803BA638;
    for (i = 0; i < (signed) ARRAY_SIZE(preloadCache.entries); i++) {
        preloadCache.entries[i] = lbDvd_803BA68C;
    }
    preloadCache.persistent_heap = 6;
    preloadCache.preloaded = 0;
}
