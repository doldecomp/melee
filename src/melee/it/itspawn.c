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

extern u64 __shr2u(u32, u32, s32);

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

s32 it_8026C530(s32 arg0, ItemPickTable* arg1, s32 arg2, s32 arg3)
{
    u16* temp_r10;
    s32 temp_r6;
    s32 temp_r7;
    s32 mid;
    u16* temp_r9;
    s32 var_r5;
    s32 last;

    var_r5 = arg2;
    last = arg3 - 1;
    if (var_r5 == last) {
        return var_r5;
    }
    temp_r10 = arg1->xC;
    mid = (var_r5 + arg3) / 2;
    if (temp_r10[mid] > arg0) {
        if (var_r5 == (mid - 1)) {
        } else {
            temp_r6 = (var_r5 + mid) / 2;
            if (temp_r10[temp_r6] > arg0) {
                var_r5 = it_8026C530(arg0, arg1, var_r5, temp_r6);
            } else if (temp_r10[temp_r6 + 1] > arg0) {
                var_r5 = temp_r6;
            } else {
                var_r5 = it_8026C530(arg0, arg1, temp_r6, mid);
            }
        }
        return var_r5;
    }
    temp_r9 = (u16*) ((u8*) temp_r10 + 2);
    if (temp_r9[mid] > arg0) {
        return mid;
    }
    if (mid == last) {
        return mid;
    }
    temp_r7 = (mid + arg3) / 2;
    if (temp_r10[temp_r7] > arg0) {
        return it_8026C530(arg0, arg1, mid, temp_r7);
    }
    if (temp_r9[temp_r7] > arg0) {
        return temp_r7;
    }
    return it_8026C530(arg0, arg1, temp_r7, arg3);
}

/// argument is definitely size 0x10
int it_8026C65C(ItemPickTable* arg_struct)
{
    s32 rand_int;
    s32 temp_r6;
    s32 var_r3;
    u16* temp_r5;
    s32 count;
    temp_r6 = (s32) arg_struct->x8;

    count = arg_struct->x0;
    rand_int = HSD_Randi(temp_r6);
    if ((count - 1) == 0) {
        var_r3 = 0;
    } else {
        temp_r5 = arg_struct->xC;
        temp_r6 = count / 2;
        if (temp_r5[temp_r6] > rand_int) {
            var_r3 = it_8026C530(rand_int, arg_struct, 0, temp_r6);
        } else if (temp_r5[temp_r6 + 1] > rand_int) {
            var_r3 = temp_r6;
        } else {
            var_r3 = it_8026C530(rand_int, arg_struct, temp_r6, count);
        }
    }
    return arg_struct->x4[var_r3];
}

bool it_8026C704(void)
{
    bool chk = false;
    if ((Item_804A0C64.x1C >= Item_804A0C64.x20) ||
        (it_8026D324(It_Kind_M_Ball) == false))
    {
        chk = true;
    }
    return chk;
}

/// Decides item kind for spawned items - not sure in which context (i.e from
/// pokeballs, from capsules, thin air, etc.)
ItemKind it_8026C75C(ItemPickTable* arg_struct)
{
    s32 temp_r0;
    s32 chk2;
    bool chk1;
    u16 var_r30;
    u8 temp_r4;
    ItemKind kind;
    PAD_STACK(16);

    chk1 = false;
    if ((Item_804A0C64.x1C >= Item_804A0C64.x20) ||
        (it_8026D324(It_Kind_M_Ball) == false))
    {
        chk1 = true;
    }
    chk2 = false;
    if (arg_struct->x8 == 0) {
        return -1;
    }
    if (chk1) {
        temp_r4 = arg_struct->x0;
        if (arg_struct->x4[temp_r4 - 1] == It_Kind_M_Ball) {
            temp_r0 = arg_struct->x0 - 1;
            if (temp_r0 < 1) {
                return -1;
            }
            var_r30 = arg_struct->x8;
            chk2 = true;
            arg_struct->x8 = arg_struct->xC[temp_r0];
            arg_struct->x0 -= 1;
        }
    }
    kind = arg_struct->x4[it_8026C530(HSD_Randi(arg_struct->x8), arg_struct, 0,
                                      arg_struct->x0)];
    if (chk1 && chk2) {
        arg_struct->x8 = var_r30;
        arg_struct->x0 += 1;
        if (kind == It_Kind_M_Ball) {
            kind = -1;
        }
    }
    return kind;
}

void fn_8026C88C(HSD_GObj* gobj)
{
    RandomItemSpawner* alloc = &it_804A0E30;
    s32* alloc_x0 = &alloc->x0;
    Item_GObj* spawn_gobj;
    SpawnItem spawn;
    bool chk;

    if (db_AreItemSpawnsEnabled() != 0U) {
        alloc->x0--;
        if ((s32) alloc->x0 == 0) {
            spawn.kind = it_8026C75C(&alloc->x4);
            if ((s32) spawn.kind != -1) {
                if (it_8026CB3C(&spawn.prev_pos)) {
                    spawn.pos = spawn.prev_pos;
                    spawn.facing_dir = it_8026B684(&spawn.prev_pos);
                    spawn.x3C_damage = 0;
                    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
                    spawn.x0_parent_gobj = NULL;
                    spawn.x4_parent_gobj2 = NULL;
                    spawn.x44_flag.b0 = 1;
                    spawn.x40 = 0;
                    chk = true;
                } else {
                    chk = false;
                }
                if (chk) {
                    spawn_gobj = Item_80268B18(&spawn);
                    if (spawn_gobj != NULL) {
                        efSync_Spawn(0x420, spawn_gobj, &spawn.prev_pos);
                        it_80274ED8();
                    }
                }
            } ///< @todo Make a FLT_RAND(min, max) define or inline
            {
                s32* temp_r29 =
                    ((s32*) it_804D6D28) + (gm_8016AE80() * 2) + 0x3F;
                f32 randf = HSD_Randf();
                *alloc_x0 = (temp_r29[1] - temp_r29[0]) * randf + temp_r29[0];
                *alloc_x0 *= Ground_801C2AE8(Stage_80225194());
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
            sum = (f32) sum + ((arg4 * (f32) *p) + 0.99f);
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
    spawner->x4.x0 = cnt;
    *(item_kinds = &spawner->x4.x4) = HSD_MemAlloc(cnt * 4);
    *(weights = &spawner->x4.xC) = HSD_MemAlloc(cnt * 4);

    cnt2 = 0;
    mask = backup;
    p2 = counts;
    it_kind2 = 0;
    cumulative = 0;
    while (it_kind2 < It_Kind_L_Gun_Ray) {
        if ((mask & 1) && *p2 != 0) {
            (*item_kinds)[cnt2] = it_kind2;
            (*weights)[cnt2] = cumulative;
            cnt2++;
            cumulative = (cumulative + ((weight * *p2) + 0.99f));
        }
        p2++;
        it_kind2++;
        mask >>= 1;
    }
}

void it_8026CD50(s32* arg0, u64 arg1, f32 arg2)
{
    typedef struct {
        RandomItemSpawner alloc;
        ItemPickTable common;
        ItemPickTable monster;
    } ItemSpawnTables;
    ItemSpawnTables* tables = (ItemSpawnTables*) &it_804A0E30;
    s32 struct_size;
    ItemKind it_kind;
    s32 cumulative;
    s32 idx;
    s32* p;
    s32 cnt;
    u32 mask_low;
    u64 temp_ret;
    u64 mask;

    mask_low = (u32) arg1;
    mask = arg1;
    p = arg0 + It_Kind_BombHei;
    cnt = 0;
    it_kind = It_Kind_BombHei;
    {
        s32 new_var = It_Kind_L_Gun_Ray;
        while (it_kind < new_var) {
            if (((mask & 1) != 0) && (*p != 0)) {
                cnt++;
            }
            p++;
            it_kind++;
            temp_ret = __shr2u(mask, mask_low, 1);
            mask = temp_ret;
        }
    }
    struct_size = cnt * 4;
    idx = struct_size;
    mask_low = (u32) temp_ret;
    tables->common.x0 = cnt;
    tables->common.x4 = HSD_MemAlloc(idx);
    tables->common.xC = HSD_MemAlloc(idx);
    cnt = 0;
    p = arg0 + It_Kind_BombHei;
    idx = 0;
    cumulative = 0;
    it_kind = It_Kind_BombHei;
    while (it_kind < It_Kind_L_Gun_Ray) {
        mask_low = (u32) arg1;
        struct_size = cumulative;
        if ((((mask & 1) ^ 0) != 0) && (*p != 0)) {
            tables->common.x4[cnt] = it_kind;
            cnt++;
            tables->common.xC[idx] = struct_size;
            idx++;
            cumulative = cumulative + ((arg2 * *p) + 0.99f);
        }
        p++;
        it_kind++;
        temp_ret = __shr2u(mask, mask_low, 1);
        mask_low = (u32) temp_ret;
        mask = temp_ret;
    }
}

/// Builds the monster-item weighted-pick table (it_804A0E60)
void it_8026CF04(void)
{
    typedef struct {
        RandomItemSpawner alloc;
        ItemPickTable common;
        ItemPickTable monster;
    } ItemSpawnTables;
    ItemSpawnTables* tables = (ItemSpawnTables*) &it_804A0E30;
    ItemCommonData* item_common;
    s32 sum;
    u8** x4_loc;
    u16** xC_loc;
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
        tables->monster.x8 = sum;
        tables->monster.x0 = 4;
        *(x4_loc = &tables->monster.x4) = HSD_MemAlloc(tables->monster.x0 * 4);
        tables->monster.xC = HSD_MemAlloc(tables->monster.x0 * 4);
        xC_loc = &tables->monster.xC;
        item_common = it_804D6D28;
        cumulative = idx = i = 0;
        for (; i < 4; i++, idx++) {
            (*x4_loc)[i] = It_Kind_Kuriboh + i;
            (*xC_loc)[idx] = cumulative;
            cumulative += item_common->x128[i];
        }
    }
}

void it_8026D018(void)
{
    typedef struct {
        RandomItemSpawner alloc;
        ItemPickTable common;
        ItemPickTable monster;
    } ItemSpawnTables;
    ItemSpawnTables* tables = (ItemSpawnTables*) &it_804A0E30;
    bool chk;
    u8 _padA[8];
    if (!gm_8016B238() && (gm_8016AE80() != -1)) {
        tables->alloc.x18 = gm_8016AEA4();
        {
            u64 stage_mask = tables->alloc.x18;
            s32* stage_info = Ground_801C2AD8();
            bool chk2 = gm_8016AE80();
            f32 weight = gm_8016AE94();
            if ((stage_mask == 0) || (stage_info == NULL) || (chk2 == -1)) {
                chk = false;
            } else {
                it_8026CA4C(&tables->alloc.x4, stage_info, stage_mask, 0,
                            weight);
                if (tables->alloc.x4.x8 != 0) {
                    it_8026CB9C(stage_info, stage_mask, weight);
                    chk = true;
                }
            }
        }
        if (chk) {
            {
                u64 stage_mask = tables->alloc.x18;
                s32* stage_info = Ground_801C2AD8();
                f32 weight = gm_8016AE94();
                if ((stage_mask != 0) && (stage_info != NULL)) {
                    u64 monster_mask = stage_mask >> 6;
                    it_8026CA4C(&tables->common, stage_info, stage_mask, 6,
                                weight);
                    if (tables->common.x8 != 0) {
                        it_8026CD50(stage_info, monster_mask, weight);
                    }
                }
            }
            it_8026CF04();
            HSD_GObj_SetupProc(GObj_Create(5U, 7U, 0U), fn_8026C88C, 0U);
            {
                s32* range = &it_804D6D28->xFC[gm_8016AE80() * 2];
                s32* alloc_x0 = (s32*) &it_804A0E30.x0;
                f32 randf = HSD_Randf();
                *alloc_x0 = (range[1] - range[0]) * randf + range[0];
                *alloc_x0 *= Ground_801C2AE8(Stage_80225194());
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
    u64 temp_r29;
    s32 temp_r3;
    s32* temp_r30;

    temp_r29 = it_804A0E30.x18;
    temp_r30 = Ground_801C2AD8();
    temp_r3 = gm_8016AE80();
    if ((((temp_r29 ^ 0)) == 0) || (temp_r30 == NULL) || (temp_r3 == -1)) {
        return false;
    }
    temp_r29 = temp_r29 >> kind;
    if (((temp_r29 & 1) ^ 0) == 0) {
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
