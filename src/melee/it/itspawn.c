/**
 * @file itspawn.c
 * @brief Item spawning system
 * @details Handles spawning item entities into the world, resolving spawn probabilities, stage drops, and container interactions.
 * Module prefix: it (Item)
 */

#include "itspawn.h"

#include <Runtime/platform.h>

#include <placeholder.h>

#include "it_26B1.h"
#include "it_2725.h"
#include "it_3F14.h"
#include "item.h"
#include <melee/db/db.h>
#include <melee/ef/efsync.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/mp/mpcoll.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>

ItemPickTable it_804A0E60;
ItemPickTable it_804A0E50;
RandomItemSpawner it_804A0E30;

/// @todo .sdata2 order hack
#ifdef MUST_MATCH
static void sdata2_order(void)
{
    (void) S32_TO_F32;
    (void) 0.0F;
    (void) 0.99F;
    (void) it_804A0E30;
    (void) it_804A0E50;
}
#endif

/**
 * @brief Constructs a bitfield of active item spawn kinds, used by snapshot functions.
 * @param arg_struct Pointer to the bitfield argument struct
 */
void it_8026C47C(struct it_8026C47C_arg0_t* arg_struct)
{
    ItemKind it_kind;
    u32 unused;
    s32 bit_idx;
    s32* word;
    PAD_STACK(8);

    it_kind = (unused = It_Kind_Start); // set to 0
    bit_idx = 0;
    word = &arg_struct->unk0;
    arg_struct->unk0 = 0;
    arg_struct->unk4 = 0;
    arg_struct->unk8 = 0;
    arg_struct->unkC = 0;
    arg_struct->unk10 = 0;
    arg_struct->unk14 = 0;
    arg_struct->unk18 = 0;
    arg_struct->unk1C = 0;

    while ((u32) it_kind < It_Kind_Max_Check) {
        if (it_80272828(it_kind)) {
            *word |= 1 << bit_idx;
        }
        it_kind++;
        bit_idx++;
        if (!(it_kind & It_Kind_RabbitC)) {
            bit_idx = 0;
            word++;
        }
    }
}

/**
 * @brief Bisection search in the item table for a given random weight value
 * @param val The generated random weight value
 * @param table The ItemPickTable to search
 * @param lo Lower bound index
 * @param hi Upper bound index
 * @return The index of the selected item
 */
static int bisectValue(int val, ItemPickTable* table, int lo, int hi)
{
    int mid;

    // base case, done bisecting
    if (lo == hi - 1) {
        return lo;
    }

    mid = (lo + hi) / 2;
    if (table->xC[mid] > val) {
        // recurse into lower half
        return bisectValue(val, table, lo, mid);
    } else {
        if (table->xC[mid + 1] > val) {
            return mid;
        }
        // recurse into upper half
        return bisectValue(val, table, mid, hi);
    }
}

/**
 * @brief Randomly selects an item kind from an ItemPickTable based on weighted values.
 * @param table Pointer to the ItemPickTable
 * @return The chosen ItemKind
 */
ItemKind it_8026C65C(ItemPickTable* table)
{
    int rand_max = table->x8;
    return table->x4[bisectValue(HSD_Randi(rand_max), table, 0, table->size)];
}

/**
 * @brief Evaluates if the global item spawn limit or Master Ball restriction is met.
 * @return true if restricted (cannot spawn), false otherwise
 */
bool it_8026C704(void)
{
    bool is_restricted = false;
    if (Item_804A0C64.x1C >= Item_804A0C64.x20 || !it_8026D324(It_Kind_M_Ball))
    {
        is_restricted = true;
    }
    return is_restricted;
}

/**
 * @brief Selects an item kind to spawn from a table, substituting Master Balls if restricted.
 * @param table Pointer to the ItemPickTable
 * @return The chosen ItemKind
 */
ItemKind it_8026C75C(ItemPickTable* table)
{
    bool is_m_ball_restricted;
    int saved_total_weight;
    bool is_m_ball_replaced;
    ItemKind ret;
    ItemKind kind;
    ItemPickTable* tbl = table;
    PAD_STACK(16);

    is_m_ball_restricted = false;
    if (Item_804A0C64.x1C >= Item_804A0C64.x20 || !it_8026D324(It_Kind_M_Ball))
    {
        is_m_ball_restricted = true;
    }
    is_m_ball_replaced = false;
    if (tbl->x8 == 0) {
        return -1;
    }
    if (is_m_ball_restricted) {
        if (tbl->x4[tbl->size - 1] == It_Kind_M_Ball) {
            int i_last = tbl->size - 1;
            if (i_last < 1) {
                return -1;
            }
            saved_total_weight = tbl->x8;
            is_m_ball_replaced = true;
            // Temporarily exclude the Master Ball by narrowing the table bounds
            tbl->x8 = tbl->xC[i_last];
            tbl->size--;
        }
    }
    kind = it_8026C65C(tbl);

    ret = kind;
    if (is_m_ball_restricted && is_m_ball_replaced) {
        // Restore original table size and total weight
        tbl->x8 = saved_total_weight;
        tbl->size++;
        if (kind == It_Kind_M_Ball) {
            ret = -1;
        }
    }
    return ret;
}

static inline void it_8026C88C_inline(RandomItemSpawner* spawner)
{
    Vec3* pos;
    s32 is_valid_pos;
    Item_GObj* item_gobj;
    SpawnItem spawn;
    if (db_AreItemSpawnsEnabled() != 0U) {
        spawner->x0--;
        if (spawner->x0 == 0) {
            spawn.kind = it_8026C75C(&spawner->x4);
            if ((s32) spawn.kind != -1) {
                pos = &spawn.prev_pos;
                if (it_8026CB3C(pos)) {
                    spawn.pos = *pos;
                    spawn.facing_dir = it_8026B684(pos);
                    is_valid_pos = 1;
                    spawn.x3C_damage = 0;
                    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
                    spawn.x0_parent_gobj = NULL;
                    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
                    spawn.x44_flag.x0.b0 = is_valid_pos;
                    spawn.x40 = 0;
                } else {
                    is_valid_pos = false;
                }
                if (is_valid_pos) {
                    item_gobj = Item_80268B18(&spawn);
                    if (item_gobj != NULL) {
                        efSync_Spawn(0x420, item_gobj, pos);
                        it_80274ED8();
                    }
                }
            } ///< @todo Make a FLT_RAND(min, max) define or inline
            {
                s32* range = &it_804D6D28->xFC[gm_8016AE80() * 2];
                f32 randf = HSD_Randf();
                f32 diff = range[1] - range[0];
                spawner->x0 = diff * randf + range[0];
                spawner->x0 *= Ground_801C2AE8(Stage_80225194());
            }
        }
    }
}

/**
 * @brief Process callback that handles continuous random item spawning during a match.
 * @param gobj The Random Item Spawner GObj
 */
void fn_8026C88C(HSD_GObj* gobj)
{
    RandomItemSpawner* spawner = &it_804A0E30;
    it_8026C88C_inline(spawner);
}

/**
 * @brief Sums up total item spawn weights from stage info for a specific item pool.
 * @param alloc Pointer to the ItemPickTable to store the sum
 * @param stage_info Pointer to stage item frequency array
 * @param allowed_mask Bitmask of allowed items
 * @param start_idx Index to start summing from
 * @param weight Base weight multiplier
 */
void it_8026CA4C(ItemPickTable* alloc, s32* stage_info, u64 allowed_mask, s32 start_idx, f32 weight)
{
    u64 mask = allowed_mask;
    s32* p = stage_info + start_idx;
    s32 i = start_idx;
    s32 sum = 0;

    while (i < It_Kind_Common_End) {
        if (mask & 1) {
            sum += weight * *p + 0.99f;
        }
        p++;
        i++;
        mask >>= 1;
    }
    alloc->x8 = sum;
}

/**
 * @brief Verifies if a given spawn position is valid (within stage bounds and not colliding).
 * @param vec Pointer to the 3D spawn position vector
 * @return true if the position is valid, false otherwise
 */
bool it_8026CB3C(Vec3* vec)
{
    if (!Stage_80224FDC(vec)) {
        return false;
    }
    vec->z = 0.0f;
    if (mpColl_8004D024(vec)) {
        return false;
    }
    return true;
}

/**
 * @brief Builds the common item spawn probability table for random stage drops.
 * @param stage_info Pointer to the stage item counts/frequencies
 * @param allowed_mask Bitmask of allowed items
 * @param weight Base weight multiplier
 */
void it_8026CB9C(s32* stage_info, u64 allowed_mask, f32 weight)
{
    RandomItemSpawner* spawner = &it_804A0E30;
    u8** item_kinds;
    u16** weights;
    s32* p;
    s32 cnt;
    ItemKind it_kind;
    s32 cnt2;
    ItemKind it_kind2;
    s32* p2;
    s32 cumulative;
    s32 idx;
    u64 backup_mask;

    backup_mask = allowed_mask;
    p = stage_info;
    it_kind = 0;
    cnt = 0;
    while (it_kind < It_Kind_Common_End) {
        if ((allowed_mask & 1) && *p != 0) {
            cnt++;
        }
        p++;
        it_kind++;
        allowed_mask >>= 1;
    }
    spawner->x4.size = cnt;
    *(item_kinds = &spawner->x4.x4) = HSD_MemAlloc(cnt * 4);
    *(weights = &spawner->x4.xC) = HSD_MemAlloc(cnt * 4);

    idx = (cnt2 = 0);
    allowed_mask = backup_mask;
    p2 = stage_info;
    it_kind2 = 0;
    cumulative = 0;
    while (it_kind2 < It_Kind_Common_End) {
        if ((allowed_mask & 1) && *p2 != 0) {
            (*item_kinds)[cnt2] = it_kind2;
            (*weights)[idx] = cumulative;
            cnt2++;
            idx++;
            cumulative = (cumulative + ((weight * *p2) + 0.99f));
        }
        p2++;
        it_kind2++;
        allowed_mask >>= 1;
    }
}

/**
 * @brief Builds the container item spawn probability table (e.g. for capsules/crates).
 * @param stage_info Pointer to the stage item counts/frequencies
 * @param allowed_mask Bitmask of allowed items
 * @param weight Base weight multiplier
 */
void it_8026CD50(s32* stage_info, u64 allowed_mask, f32 weight)
{
#ifdef MUST_MATCH
    /// @todo #it_804A0E50 immediately follows #it_804A0E30; the original
    ///       addressed it relative to the spawner.
    RandomItemSpawner* spawner = &it_804A0E30;
#endif
    s32* p;
    s32 cnt;
    ItemKind it_kind;
    ItemKind it_kind2;
    s32 cnt2;
    s32* p2;
    u8** item_kinds;
    s32 idx;
    u16** weights;
    s32 cumulative;
    u64 backup_mask;

    backup_mask = allowed_mask;
    p = stage_info + It_Kind_Container_End;
    cnt = 0;
    it_kind = It_Kind_Container_End;
    while (it_kind < It_Kind_Common_End) {
        if ((allowed_mask & 1) && *p != 0) {
            cnt++;
        }
        p++;
        it_kind++;
        allowed_mask >>= 1;
    }
#ifdef MUST_MATCH
    ((ItemPickTable*) (spawner + 1))->size = cnt;
    *(item_kinds = &((ItemPickTable*) (spawner + 1))->x4) =
        HSD_MemAlloc(cnt * 4);
    *(weights = &((ItemPickTable*) (spawner + 1))->xC) = HSD_MemAlloc(cnt * 4);
#else
    // Non-matching builds may lay these globals out in a different order.
    it_804A0E50.size = cnt;
    *(item_kinds = &it_804A0E50.x4) = HSD_MemAlloc(cnt * 4);
    *(weights = &it_804A0E50.xC) = HSD_MemAlloc(cnt * 4);
#endif

    idx = (cnt2 = 0);
    allowed_mask = backup_mask;
    p2 = stage_info + It_Kind_Container_End;
    cumulative = 0;
    it_kind2 = It_Kind_Container_End;
    while (it_kind2 < It_Kind_Common_End) {
        if ((allowed_mask & 1) && *p2 != 0) {
            (*item_kinds)[cnt2] = it_kind2;
            (*weights)[idx] = cumulative;
            cnt2++;
            idx++;
            cumulative = (cumulative + ((weight * *p2) + 0.99f));
        }
        p2++;
        it_kind2++;
        allowed_mask >>= 1;
    }
}

/**
 * @brief Builds the monster-item weighted-pick table (it_804A0E60)
 */
void it_8026CF04(void)
{
    ItemCommonData* item_common;
    s32 sum;
    int i;
    u32 cumulative;
    u32 idx;
    s32* counts;
    s32* p;

    counts = it_804D6D28->x128;
    sum = counts[0];
    sum += counts[1];
    sum += counts[2];
    sum += counts[3];
    if (sum != 0) {
        it_804A0E60.x8 = sum;
        it_804A0E60.size = 4;
        it_804A0E60.x4 = HSD_MemAlloc(it_804A0E60.size * 4);
        it_804A0E60.xC = HSD_MemAlloc(it_804A0E60.size * 4);
        idx = i = 0;
        item_common = it_804D6D28;
        cumulative = 0;
        for (; i < 4; i++, idx++) {
            it_804A0E60.x4[i] = It_Kind_Monster_Start + i;
            it_804A0E60.xC[idx] = cumulative;
            (void) it_804A0E60.xC[(u32) (p = &item_common->x128[idx])];
            cumulative += *p;
        }
    }
}

static inline bool it_8026D018_inline(void)
{
    s32* stage_info;
    u64 stage_mask;
    int chk;
    f32 weight;

    stage_mask = it_804A0E30.x18;
    stage_info = Ground_801C2AD8();
    chk = gm_8016AE80();
    weight = gm_8016AE94();

    if (stage_mask == 0 || stage_info == NULL || chk == -1) {
        return false;
    }
    it_8026CA4C(&it_804A0E30.x4, stage_info, stage_mask, 0, weight);
    if (it_804A0E30.x4.x8 == 0) {
        return false;
    }
    it_8026CB9C(stage_info, stage_mask, weight);
    return true;
}

static inline void it_8026D018_inline2(void)
{
    s32* stage_info;
    u64 stage_mask;
    f32 weight;

    stage_mask = it_804A0E30.x18;
    stage_info = Ground_801C2AD8();
    weight = gm_8016AE94();

    if ((stage_mask != 0) && (stage_info != NULL)) {
        stage_mask >>= 6;
        it_8026CA4C(&it_804A0E50, stage_info, stage_mask, 6, weight);
        if (it_804A0E50.x8 != 0) {
            it_8026CD50(stage_info, stage_mask, weight);
        }
    }
}

static inline void it_8026D018_inline3(f32 randf, const s32* range)
{
    s32 diff = range[1] - range[0];

    (void) diff;
    it_804A0E30.x0 = diff * randf + range[0];
    it_804A0E30.x0 *= Ground_801C2AE8(Stage_80225194());
}

/**
 * @brief Initializes the stage's random item spawner and its associated tables.
 */
void it_8026D018(void)
{
    if (!gm_8016B238() && (gm_8016AE80() != -1)) {
        it_804A0E30.x18 = gm_8016AEA4();
        if (it_8026D018_inline()) {
            it_8026D018_inline2();
            it_8026CF04();
            HSD_GObj_SetupProc(GObj_Create(5, 7, 0), fn_8026C88C, 0);
            it_8026D018_inline3(HSD_Randf(),
                                &it_804D6D28->xFC[gm_8016AE80() * 2]);
        }
    }
}

/**
 * @brief Directly spawns an item of a specified kind at a given position.
 * @param pos Pointer to the 3D position vector
 * @param kind The ItemKind to spawn
 * @return true if spawned successfully, false if limits were exceeded
 */
bool it_8026D258(Vec3* pos, ItemKind kind)
{
    SpawnItem spawn;
    bool item_spawn_chk;

    item_spawn_chk = false;
    if (Item_804A0C64.x60 < Item_804A0C64.x64) {
        spawn.kind = kind;
        spawn.prev_pos = *pos;
        spawn.prev_pos.z = 0.0f;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = it_8026B684(&spawn.prev_pos);
        spawn.x3C_damage = 0;
        spawn.vel.z = 0.0f;
        spawn.vel.y = 0.0f;
        spawn.vel.x = 0.0f;
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.x0.b0 = 1;
        spawn.x40 = 0;
        Item_80268B9C(&spawn);
        item_spawn_chk = true;
    }
    return item_spawn_chk;
}

/**
 * @brief Checks if a specific item kind is allowed to spawn on the current stage/settings.
 * @param kind The ItemKind to check
 * @return true if allowed, false otherwise
 */
bool it_8026D324(ItemKind kind)
{
    u64 stage_mask = it_804A0E30.x18;
    s32* stage_info = Ground_801C2AD8();
    s32 item_switch = gm_8016AE80();
    if (stage_mask == 0 || stage_info == NULL || item_switch == -1) {
        return false;
    }
    if (!(stage_mask >> kind & 1)) {
        return false;
    }
    return true;
}

/**
 * @brief Checks if any healing item (Heart Container, Maxim Tomato, Food) is allowed to spawn.
 * @return true if at least one healing item is allowed, false otherwise
 */
bool it_8026D3CC(void)
{
    bool result = it_8026D324(It_Kind_Heart);

    result |= it_8026D324(It_Kind_Tomato);
    result |= it_8026D324(It_Kind_Foods);
    return result;
}
