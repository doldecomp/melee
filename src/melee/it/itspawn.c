#include "it/itspawn.h"

#include "db/db.h"
#include "ef/efsync.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/it_3F14.h"
#include "it/item.h"
#include "mp/mpcoll.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/memory.h>
#include <baselib/random.h>

ItemPickTable monster;
ItemPickTable it_804A0E50;
RandomItemSpawner it_804A0E30;

void it_8026C47C(struct it_8026C47C_arg0_t* arg_struct)
{
    u32 it_kind;
    u32 unused;
    s32 bit_idx;
    s32* word;
    PAD_STACK(8);

    it_kind = (unused = It_Kind_Capsule);
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
    while (it_kind < 238) {
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

/// bisection search in the item table for a given value
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

ItemKind it_8026C65C(ItemPickTable* table)
{
    int temp_r6 = table->x8;
    return table->x4[bisectValue(HSD_Randi(temp_r6), table, 0, table->size)];
}

bool it_8026C704(void)
{
    bool result = false;
    if (Item_804A0C64.x1C >= Item_804A0C64.x20 || !it_8026D324(It_Kind_M_Ball))
    {
        result = true;
    }
    return result;
}

/// Decides item kind for spawned items - not sure in which context (i.e from
/// pokeballs, from capsules, thin air, etc.)
/// @todo Two callee-saved registers are swapped.
ItemKind it_8026C75C(ItemPickTable* table)
{
    bool chk1;
    bool chk2;
    int saved;
    ItemKind ret;
    ItemKind kind;
    PAD_STACK(16);

    chk1 = false;
    if (Item_804A0C64.x1C >= Item_804A0C64.x20 || !it_8026D324(It_Kind_M_Ball))
    {
        chk1 = true;
    }
    chk2 = false;
    if (table->x8 == 0) {
        return -1;
    }
    if (chk1) {
        if (table->x4[table->size - 1] == It_Kind_M_Ball) {
            int i_last = table->size - 1;
            if (i_last < 1) {
                return -1;
            }
            saved = table->x8;
            chk2 = true;
            table->x8 = table->xC[i_last];
            table->size--;
        }
    }
    kind = it_8026C65C(table);

    ret = kind;
    if (chk1 && chk2) {
        table->x8 = saved;
        table->size++;
        if (kind == It_Kind_M_Ball) {
            ret = -1;
        }
    }
    return ret;
}

static inline bool initSpawnItem(SpawnItem* spawn)
{
    if (it_8026CB3C(&spawn->prev_pos)) {
        spawn->pos = spawn->prev_pos;
        spawn->facing_dir = it_8026B684(&spawn->prev_pos);
        spawn->x3C_damage = 0;
        spawn->vel.x = spawn->vel.y = spawn->vel.z = 0.0F;
        spawn->x0_parent_gobj = NULL;
        spawn->x4_parent_gobj2 = spawn->x0_parent_gobj;
        spawn->x44_flag.b0 = true;
        spawn->x40 = 0;
        return true;
    } else {
        return false;
    }
}

void fn_8026C88C(HSD_GObj* gobj)
{
    Item_GObj* spawn_gobj;
    u8 pad[4];
    SpawnItem spawn;

    if (db_AreItemSpawnsEnabled()) {
        it_804A0E30.x0--;
        if (it_804A0E30.x0 == 0) {
            spawn.kind = it_8026C75C(&it_804A0E30.x4);
            if (spawn.kind != -1) {
                if (initSpawnItem(&spawn)) {
                    spawn_gobj = Item_80268B18(&spawn);
                    if (spawn_gobj != NULL) {
                        efSync_Spawn(0x420, spawn_gobj, &spawn.prev_pos);
                        it_80274ED8();
                    }
                }
            } ///< @todo Make a FLT_RAND(min, max) define or inline
            {
                s32* range = &it_804D6D28->xFC[gm_8016AE80() * 2];
                f32 randf = HSD_Randf();
                it_804A0E30.x0 = range[0] + (range[1] - range[0]) * randf;
                it_804A0E30.x0 *= Ground_801C2AE8(Stage_80225194());
            }
        }
    }
}

#pragma push
#pragma dont_inline on
void it_8026CA4C(ItemPickTable* alloc, s32* arg1, u64 arg2, s32 arg3, f32 arg4)
{
    u64 mask = arg2;
    s32* p = arg1 + arg3;
    s32 i = arg3;
    s32 sum = 0;

    while (i < It_Kind_L_Gun_Ray) {
        if (mask & 1) {
            sum += arg4 * *p + 0.99f;
        }
        p++;
        i++;
        mask >>= 1;
    }
    alloc->x8 = sum;
}
#pragma pop

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

/// Builds some structs for items
void it_8026CB9C(s32* counts, u64 mask, f32 weight)
{
    s32* p;
    s32 cnt;
    ItemKind it_kind;
    s32 cnt2;
    ItemKind it_kind2;
    s32* p2;
    s32 cumulative;
    s32 idx;
    u64 backup;

    backup = mask;
    p = counts;
    it_kind = 0;
    cnt = 0;
    while (it_kind < It_Kind_L_Gun_Ray) {
        if ((mask & 1) && *p != 0) {
            cnt++;
        }
        p++;
        it_kind++;
        mask >>= 1;
    }
    it_804A0E30.x4.size = cnt;
    it_804A0E30.x4.x4 = HSD_MemAlloc(cnt * 4);
    it_804A0E30.x4.xC = HSD_MemAlloc(cnt * 4);

    cnt2 = 0;
    p2 = counts;
    mask = backup;
    idx = cnt2;
    it_kind2 = 0;
    cumulative = 0;
    while (it_kind2 < It_Kind_L_Gun_Ray) {
        if ((mask & 1) && *p2 != 0) {
            it_804A0E30.x4.x4[cnt2] = it_kind2;
            it_804A0E30.x4.xC[idx] = cumulative;
            cnt2++;
            idx++;
            cumulative += weight * *p2 + 0.99f;
        }
        p2++;
        it_kind2++;
        mask >>= 1;
    }
}

void it_8026CD50(s32* counts, u64 mask, f32 weight)
{
    s32 cnt;
    s32* p;
    ItemKind it_kind;
    ItemKind it_kind2;
    s32 cumulative;
    u64 backup;

    backup = mask;
    p = counts + It_Kind_BombHei;
    cnt = 0;
    it_kind = It_Kind_BombHei;
    while (it_kind < It_Kind_L_Gun_Ray) {
        if ((mask & 1) && *p != 0) {
            cnt++;
        }
        p++;
        it_kind++;
        mask >>= 1;
    }
    it_804A0E50.size = cnt;
    it_804A0E50.x4 = HSD_MemAlloc(cnt * 4);
    it_804A0E50.xC = HSD_MemAlloc(cnt * 4);

    mask = backup;
    p = &counts[It_Kind_BombHei];
    cumulative = 0;
    cnt = 0;
    it_kind2 = It_Kind_BombHei;
    while (it_kind2 < It_Kind_L_Gun_Ray) {
        if ((mask & 1) && *p != 0) {
            it_804A0E50.x4[cnt] = it_kind2;
            it_804A0E50.xC[cnt] = cumulative;
            cumulative += weight * *p + 0.99f;
            cnt++;
        }
        p++;
        it_kind2++;
        mask >>= 1;
    }
}

/// Builds the monster-item weighted-pick table (it_804A0E60)
void it_8026CF04(void)
{
    ItemCommonData* item_common;
    s32 sum;
    int i;
    u32 cumulative;
    u32 idx;
    s32* counts;

    counts = it_804D6D28->x128;
    sum = counts[0];
    sum += counts[1];
    sum += counts[2];
    sum += counts[3];
    if (sum != 0) {
        monster.x8 = sum;
        monster.size = 4;
        monster.x4 = HSD_MemAlloc(monster.size * 4);
        monster.xC = HSD_MemAlloc(monster.size * 4);
        idx = i = 0;
        counts = &it_804D6D28->x128[0];
        (void) counts;
        cumulative = 0;
        for (; i < 4; i++, idx++) {
            monster.x4[i] = It_Kind_Kuriboh + i;
            monster.xC[idx] = cumulative;
            cumulative += counts[i];
        }
    }
}

static inline bool it_8026D018_inline(f32 weight, int chk, s32* stage_info,
                                      u64 stage_mask)
{
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

void it_8026D018(void)
{
    if (!gm_8016B238() && (gm_8016AE80() != -1)) {
        it_804A0E30.x18 = gm_8016AEA4();
        if (it_8026D018_inline(gm_8016AE94(), gm_8016AE80(), Ground_801C2AD8(),
                               it_804A0E30.x18))
        {
            u64 stage_mask = it_804A0E30.x18;
            s32* stage_info = Ground_801C2AD8();
            f32 weight = gm_8016AE94();
            if ((stage_mask != 0) && (stage_info != NULL)) {
                u64 monster_mask = stage_mask >> 6;
                it_8026CA4C(&it_804A0E50, stage_info, monster_mask, 6, weight);
                if (it_804A0E50.x8 != 0) {
                    it_8026CD50(stage_info, monster_mask, weight);
                }
            }
            it_8026CF04();
            HSD_GObj_SetupProc(GObj_Create(5, 7, 0), fn_8026C88C, 0);
            {
                s32* range = &it_804D6D28->xFC[gm_8016AE80() * 2];
                f32 randf = HSD_Randf();
                f32 diff = range[1] - range[0];
                it_804A0E30.x0 = diff * randf + range[0];
                it_804A0E30.x0 *= Ground_801C2AE8(Stage_80225194());
            }
        }
    }
}

/// Spawn item of specified kind at specified position (but no z-offset)
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
        spawn.x44_flag.b0 = 1;
        spawn.x40 = 0;
        Item_80268B9C(&spawn);
        item_spawn_chk = true;
    }
    return item_spawn_chk;
}

bool it_8026D324(ItemKind kind)
{
    u64 temp_r29 = it_804A0E30.x18;
    s32* temp_r30 = Ground_801C2AD8();
    s32 temp_r3 = gm_8016AE80();
    if (temp_r29 == 0 || temp_r30 == NULL || temp_r3 == -1) {
        return false;
    }
    if (!(temp_r29 >> kind & 1)) {
        return false;
    }
    return true;
}

bool it_8026D3CC(void)
{
    bool result = it_8026D324(It_Kind_Heart);

    result |= it_8026D324(It_Kind_Tomato);
    result |= it_8026D324(It_Kind_Foods);
    return result;
}
