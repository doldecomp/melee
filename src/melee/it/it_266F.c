#include "it/it_266F.h"

#include "inlines.h"
#include "types.h"

#include <platform.h>

#include "cm/camera.h"
#include "db/db.h"
#include "ef/efsync.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/it_2E5A.h"
#include "lb/lb_00F9.h"
#include "lb/lbcollision.h"
#include "lb/lbgx.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <math.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/random.h>
#include <baselib/state.h>
#include <baselib/tev.h>

extern HSD_ObjAllocUnk Item_804A0C64;
extern HSD_ObjAllocUnk4 it_804A0E30;
extern HSD_ObjAllocUnk6 it_804A0E50;
extern HSD_ObjAllocUnk6 it_804A0E60;
extern ItemCommonData* it_804D6D28;

extern u64 __shr2u(u64, u32, s32);

static Quaternion it_803B8560 = { 0.0f, 0.0f, 1.0f, 0.0f };
static Vec3 it_803B8570 = { 0.0f, 0.0f, 0.0f };
static Vec3 it_803B857C = { 0.0f, 0.0f, 0.0f };
static Quaternion it_803B8588 = { 0.0f, 0.0f, 0.0f, 0.0f };
static Quaternion it_803B8598 = { 0.0f, 0.0f, 0.0f, 0.0f };
static const Vec3 it_803B85A8[6] = {
    { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
};
static s32 it_803B85F0[4];

static U8Vec4 it_804D5168 = { 0xFF, 0x40, 0x80, 0x80 };

// static f64 it_804DC698 = S32_TO_F32;
// static f32 it_804DC6A0 = 0.0f;
// static f32 it_804DC6A4 = 0.99f;
// static f32 it_804DC6A8 = 0.0f;
// static f32 it_804DC6AC = 0.00001f;
// static f64 it_804DC6B0 = 0.0f;
// static f32 it_804DC6B8 = 0.0f;
// static f32 it_804DC6BC = 2.0f;
// static Vec2 it_804DC6C0 = { 0.5f, 0.0f };

void it_8026C47C(struct it_8026C47C_arg0_t* arg_struct)
{
    u32 it_kind;
    s32 var_r29; // Hold Kind??
    s32* var_r28;
    PAD_STACK(8);

    it_kind = It_Kind_Capsule;
    var_r29 = 0;
    var_r28 = &arg_struct->unk0;
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
            *var_r28 |= 1 << var_r29;
        }
        it_kind++;
        var_r29++;
        if (!(it_kind & It_Kind_RabbitC)) {
            var_r29 = 0;
            var_r28++;
        }
    }
}

s32 it_8026C530(s32 arg0, HSD_ObjAllocUnk6* arg1, s32 arg2, s32 arg3)
{
    u16* temp_r10;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    // s32 temp_r7_2;
    s32 temp_r7_3;
    // s32 temp_r8;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_r5;

    var_r5 = arg2;
    // temp_r8 = arg3 - 1;
    if (var_r5 == (arg3 - 1)) {
        return var_r5;
    }
    temp_r10 = arg1->xC;
    temp_r9 = (var_r5 + arg3) / 2;
    // temp_r7_2 = temp_r9 * 2;
    // temp_r7_2 = temp_r9;
    // if ((s32) *(temp_r10 + temp_r7_2) > arg0) {
    // if (((s32) *temp_r10[temp_r7_2])->x0 > arg0) {
    if (temp_r10[temp_r9] > arg0) {
        if (var_r5 == (temp_r9 - 1)) {
        } else {
            temp_r6 = (var_r5 + temp_r9) / 2;
            temp_r7_3 = temp_r6 * 1;
            // if ((s32) *(temp_r10 + temp_r7_3) > arg0) {
            // if (temp_r10[temp_r7_3]->x0 > arg0) {
            if (temp_r10[temp_r7_3] > arg0) {
                var_r5 = it_8026C530(arg0, arg1, var_r5, temp_r6);
                // } else if ((s32) (temp_r10 + temp_r7_3)->unk2 > arg0) {
                // } else if (temp_r10[temp_r7_3]->x2 > arg0) {
            } else if (temp_r10[temp_r7_3] > arg0) {
                var_r5 = temp_r6;
            } else {
                var_r5 = it_8026C530(arg0, arg1, temp_r6, temp_r9);
            }
        }
        return var_r5;
    }
    temp_r9_2 = (s32) temp_r10 + 2;
    // temp_r9_2 = temp_r10->x2;
    // if ((s32) *(temp_r9_2 + temp_r7_2) > arg0) {
    if ((temp_r9_2 + temp_r9) > arg0) {
        return temp_r9;
    }
    if (temp_r9 == arg3 - 1) {
        return temp_r9;
    }
    temp_r7 = (s32) (temp_r9 + arg3) / 2;
    // temp_r5 = temp_r7 * 2;
    temp_r5 = temp_r7;
    // if ((s32) *(temp_r10 + temp_r5) > arg0) {
    if (temp_r10[temp_r5] > arg0) {
        return it_8026C530(arg0, arg1, temp_r9, temp_r7);
    }
    // if ((s32) *(temp_r9_2 + temp_r5) > arg0) {
    if ((temp_r9_2 + temp_r5) > arg0) {
        return temp_r7;
    }
    return it_8026C530(arg0, arg1, temp_r7, arg3);
}

// argument is definitely size 0x10
u8 it_8026C65C(HSD_ObjAllocUnk6* arg_struct)
{
    s32 rand_int;
    s32 temp_r6;
    s32 var_r3;
    u16* temp_r5;

    rand_int = HSD_Randi((s32) arg_struct->x8);
    if ((arg_struct->x0 - 1) == 0) {
        var_r3 = 0;
    } else {
        temp_r5 = arg_struct->xC;
        temp_r6 = arg_struct->x0 / 2;
        if (temp_r5[temp_r6] > rand_int) {
            var_r3 = it_8026C530(rand_int, arg_struct, 0, temp_r6);
            // } else if (temp_r5[temp_r6].unk2 > rand_int) {
            // } else if (temp_r5[temp_r6] > rand_int) {
            // } else if ((&temp_r5[temp_r6] + 2) > rand_int) {
        } else if ((arg_struct->x0 << 2) > rand_int) {
            var_r3 = temp_r6;
        } else {
            var_r3 =
                it_8026C530(rand_int, arg_struct, temp_r6, arg_struct->x0);
        }
    }
    return arg_struct->x4[var_r3];
}

bool it_8026C704(void)
{
    bool chk;

    chk = false;
    if ((Item_804A0C64.x1C >= Item_804A0C64.x20) ||
        (it_8026D324(It_Kind_M_Ball) == false))
    {
        chk = true;
    }
    return chk;
}

// Decides item kind for spawned items - not sure in which context (i.e from
// pokeballs, from capsules, thin air, etc.)
ItemKind it_8026C75C(HSD_ObjAllocUnk6* arg_struct)
{
    s32 temp_r0;
    s32 chk2;
    bool chk1;
    u16 var_r30;
    u8 temp_r4;
    ItemKind kind;
    PAD_STACK(4);

    chk1 = it_8026C704(); // Check if pokeball or Item_804A0C64.x1C >=
                          // Item_804A0C64.x20 (something related to hold kind)
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

// .L_8026C88C
void fn_8026C88C(HSD_GObj* gobj)
{
    HSD_ObjAllocUnk4* it_804A0E30_ = &it_804A0E30;
    s32* it_804A0E30_x0 = (s32*) &it_804A0E30_->x0;
    Item_GObj* spawn_gobj;
    SpawnItem spawn;
    bool chk;
    s32* temp_r29;

    if (db_AreItemSpawnsEnabled() != 0U) {
        it_804A0E30_->x0--;
        if ((s32) it_804A0E30_->x0 == 0) {
            spawn.kind = it_8026C75C(&it_804A0E30_->x4);
            if ((s32) spawn.kind != -1) {
                if (it_8026CB3C(&spawn.prev_pos)) {
                    spawn.pos = spawn.prev_pos;
                    spawn.facing_dir = it_8026B684(&spawn.prev_pos);
                    spawn.x3C_damage = 0;
                    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
                    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj = NULL;
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
            }
            // @todo: Make a FLT_RAND(min, max) define or inline
            temp_r29 = ((s32*) it_804D6D28) + (gm_8016AE80() * 2) + 0x3F;
            *it_804A0E30_x0 =
                (temp_r29[1] - temp_r29[0]) * HSD_Randf() + temp_r29[0];
            *it_804A0E30_x0 *= Ground_801C2AE8(Stage_80225194());
        }
    }
}

void it_8026CA4C(u16* arg0, s32* arg1, u64 arg2, s32 arg3, f32 arg4)
{
#if 1
    u64 var_r5;
    s32* var_r28;
    s32 var_r31;
    s32 var_r27;

    var_r5 = arg2;
    var_r31 = arg3;
    var_r28 = arg1 + arg3;
    var_r27 = 0;
    while (var_r31 < It_Kind_L_Gun_Ray) {
        if (((var_r5 & 1) ^ 0) != 0) {
            var_r27 = ((f32) var_r27 + ((arg4 * (f32) *var_r28) + 0.99f));
        }
        var_r28++;
        var_r31++;
        var_r5 = var_r5 >> 1;
    }
    arg0[4] = var_r27;
#else
    s16 var_r27;
    s32 var_r31;
    s32 var_r6;
    s32* var_r28;
    u64 temp_r3;
    u64 temp_ret;
    u64 var_r5;

    var_r5 = arg2;
    var_r6 = arg3;
    var_r31 = M2C_ERROR(/* Read from unset register $r7 */);
    var_r28 = arg1 + arg3;
    var_r27 = 0;
    while (var_r31 < It_Kind_L_Gun_Ray) {
        if ((((var_r6 & 1) ^ 0) | ((var_r5 & 0) ^ 0)) != 0) {
            var_r27 =
                (s16) ((f32) var_r27 + ((arg4 * (f32) *var_r28) + 0.99f));
        }
        var_r28 += 4;
        var_r31++;
        temp_ret = __shr2u(var_r5, (u32) var_r6, 1);
        temp_r3 = temp_ret;
        var_r6 = (s32) (u32) temp_ret;
        var_r5 = temp_r3;
    }
    arg0[4] = var_r27;
#endif
}

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

// Builds some structs for items
void it_8026CB9C(s32* arg0, u64 arg2, f32 arg8)
{
    s32 struct_size;
    {
        u64 var_r5;
        s32* var_r28;
        ItemKind it_kind;
        s32 cnt;

        var_r5 = arg2;
        it_kind = 0;
        var_r28 = arg0;
        cnt = 0;
        while (it_kind < It_Kind_L_Gun_Ray) {
            if (((var_r5 & 1) ^ 0) != 0 && *var_r28 != 0) {
                cnt++;
            }
            var_r28++;
            it_kind++;
            var_r5 = var_r5 >> 1;
        }
        struct_size = cnt * 4;
        it_804A0E30.x4.x0 = cnt;
        it_804A0E30.x4.x4 = (u8*) HSD_MemAlloc(struct_size);
        it_804A0E30.x4.xC = (u16*) HSD_MemAlloc(struct_size);
    }
    {
        u64 var_r5;
        s32* var_r28;
        s32 var_r31;
        ItemKind it_kind;
        s32 cnt;
        s32 var_r29;
        s32 var_r25;

        cnt = 0;
        var_r5 = arg2;
        var_r28 = arg0;

        var_r29 = 0;
        it_kind = It_Kind_Capsule; // 0
        var_r25 = 0;

        while (it_kind < It_Kind_L_Gun_Ray) {
            if (((var_r5 & 1) ^ 0) != 0 && *var_r28 != 0) {
                it_804A0E30.x4.x4[cnt] = it_kind;
                cnt++;
                it_804A0E30.x4.xC[var_r29] = var_r25;
                // it_804A0E30.x4.xC[2 * cnt] = var_r25;
                var_r29 += 2;
                var_r25 =
                    (s16) ((f32) var_r25 + ((arg8 * (f32) *var_r28) + 0.99f));
            }
            var_r28++;
            it_kind++;
            var_r5 = var_r5 >> 1;
        }
    }
}

// extern HSD_ObjAllocUnk4 it_804A0E30;
void it_8026CD50(s32* arg0, u64 arg1, f32 arg2)
{
    s16 var_r25;
    s32 struct_size;
    ItemKind it_kind; // r26
    s32 var_r29;
    s32* var_r28;
    s32* var_r28_2;
    s32 cnt; // r27
    u32 var_r6;
    u64 temp_ret;
    u64 var_r5;

    var_r6 = (u32) arg1;
    var_r5 = arg1;
    // r29 = it_804A0E30;
    var_r28 = arg0 + 0x18;
    cnt = 0;
    it_kind = It_Kind_BombHei; // 6
    // r30 = 1
    // r31 = 0
    while (it_kind < It_Kind_L_Gun_Ray) {
        if (((((var_r5 << 8 & 1) ^ 0) | ((var_r6 & 0) ^ 0))) &&
            ((s32) *var_r28 != 0))
        {
            cnt++;
        }
        var_r28 += 4;
        it_kind++;
        temp_ret = __shr2u(var_r5, var_r6, 1);
        var_r6 = (u32) temp_ret;
        // var_r5 = temp_ret;
        // var_r5 = var_r5 >> 1;
    }
    struct_size = cnt * 4;
    // it_804A0E30.unk20 = cnt;
    // it_804A0E30.unk24 = HSD_MemAlloc(struct_size);
    // it_804A0E30.unk2C = HSD_MemAlloc(struct_size);
    it_804A0E50.x0 = cnt;
    it_804A0E50.x4 = HSD_MemAlloc(struct_size);
    it_804A0E50.xC = HSD_MemAlloc(struct_size);
    cnt = 0;
    var_r6 = (u32) arg1;
    // var_r5 = arg1;
    var_r28_2 = arg0 + 0x18;
    var_r29 = 0;
    var_r25 = 0;
    it_kind = It_Kind_BombHei; // 6
    while (it_kind < It_Kind_L_Gun_Ray) {
        if (((((var_r5 & 1) ^ 0) | ((var_r6 & 0) ^ 0)) != 0) &&
            ((s32) *var_r28_2 != 0))
        {
            *(it_804A0E50.x4 + cnt) = it_kind;
            cnt++;
            *(it_804A0E50.xC + var_r29) = var_r25;
            var_r29 += 2;
            var_r25 = var_r25 + ((arg2 * *var_r28_2) + 0.99f);
        }
        var_r28_2 += 4;
        it_kind++;
        temp_ret = __shr2u(var_r5, var_r6, 1);
        var_r6 = (u32) temp_ret;
        var_r5 = temp_ret;
    }
}

// Builds structs for monster items
void it_8026CF04(void)
{
    s16 temp_r4;
    s16 temp_r8_2;
    s32 temp_r8;
    u8* temp_r30;

    // @todo: probably a double somewhere
    temp_r4 = it_804D6D28->x128 + it_804D6D28->x12C + it_804D6D28->x130 +
              it_804D6D28->x134;
    // @todo: Investigate why it_804A0E30 is used instead of it_804A0E60.
    if (temp_r4 != 0) {
        it_804A0E60.x8 = temp_r4;
        it_804A0E60.x0 = 4U;
        temp_r30 = it_804A0E60.x4;
        it_804A0E60.x4 = (u8*) HSD_MemAlloc(it_804A0E60.x0 * 4);
        it_804A0E60.xC = (u16*) HSD_MemAlloc(it_804A0E60.x0 * 4);
        temp_r30[0] = It_Kind_Kuriboh;
        it_804A0E60.xC[0] = 0;
        temp_r8 = it_804D6D28->x128;
        temp_r30[1] = It_Kind_Leadead;
        it_804A0E60.xC[1] = (s16) temp_r8;
        temp_r8_2 = temp_r8 + it_804D6D28->x12C;
        temp_r30[2] = It_Kind_Octarock;
        it_804A0E60.xC[2] = temp_r8_2;
        temp_r30[3] = It_Kind_Ottosea;
        it_804A0E60.xC[3] = temp_r8_2 + it_804D6D28->x130;
    }
}

void it_8026D018(void)
{
#if 1
    bool chk;
    if (!gm_8016B238() && (gm_8016AE80() != -1)) {
        it_804A0E30.x18 = gm_8016AEA4();
        chk = false;
        {
            u64 temp_r28 = it_804A0E30.x18;
            s32* temp_r26 = (s32*) Ground_801C2AD8(); // stage_info.xA0
            bool chk2 = gm_8016AE80();
            f32 temp_f31 = gm_8016AE94();
            // chk = false;
            if (((temp_r28 ^ 0) == 0) || (temp_r26 == NULL) || (chk2 == -1)) {
                chk = false;
            } else {
                it_8026CA4C((u16*) &it_804A0E30.x4.x0, temp_r26, temp_r28, 0,
                            temp_f31);
                if ((u16) it_804A0E30.x4.x8 == 0) {
                } else {
                    it_8026CB9C(temp_r26, temp_r28, temp_f31);
                    chk = true;
                }
            }
        }
        if (chk) {
            {
                u64 temp_r26_2 = it_804A0E30.x18;
                s32* temp_r28_2 = (s32*) Ground_801C2AD8();
                f32 temp_f31_2 = gm_8016AE94();
                if (((temp_r26_2 ^ 0) != 0) && (temp_r28_2 != NULL)) {
                    u64 temp_r3 = temp_r26_2 >> 6;
                    it_8026CA4C((u16*) &it_804A0E30.x4.x0, temp_r28_2,
                                temp_r26_2, 6, temp_f31_2);
                    // if (*(u16*) ((u8*) &it_804A0E30 + 0x28) != 0) {
                    if (it_804A0E30.x4.x8 != 0) {
                        // if (it_804A0E50.x8 != 0) {
                        it_8026CD50(temp_r28_2, temp_r3, temp_f31_2);
                    }
                }
            }
            it_8026CF04();
            HSD_GObjProc_8038FD54(GObj_Create(5U, 7U, 0U), fn_8026C88C, 0U);
            {
                // @todo: Make a FLT_RAND(min, max) define or inline
                f32* temp_r29 =
                    ((f32*) it_804D6D28) + (gm_8016AE80() * 8) + 0xFC;
                it_804A0E30.x0 =
                    (s32) (((temp_r29[4] - temp_r29[0]) * HSD_Randf()) +
                           (f32) temp_r29[0]);
                it_804A0E30.x0 = (s32) ((f32) it_804A0E30.x0 *
                                        Ground_801C2AE8(Stage_80225194()));
            }
        }
    }
#else
    u64 temp_r28;
    s32* temp_r26;
    u64 temp_r3;
    bool chk2;
    bool chk;
    f32 temp_f31;
    f32* temp_r29;

    if (!gm_8016B238() && (gm_8016AE80() != -1)) {
        it_804A0E30.x18 = gm_8016AEA4();
        // chk = false;
        temp_r28 = it_804A0E30.x18;
        temp_r26 = (s32*) Ground_801C2AD8(); // stage_info.xA0
        chk2 = gm_8016AE80();
        temp_f31 = gm_8016AE94();
        if (((temp_r28 ^ 0) == 0) || (temp_r26 == NULL) || (chk2 == -1)) {
            chk = false;
        } else {
            it_8026CA4C((u16*) &it_804A0E30.x4.x0, temp_r26, temp_r28, 0,
                        temp_f31);
            if ((u16) it_804A0E30.x4.x8 == 0) {
            } else {
                it_8026CB9C(temp_r26, temp_r28, temp_f31);
                chk = true;
            }
        }
        if (chk) {
            temp_r28 = it_804A0E30.x18;
            temp_r26 = (s32*) Ground_801C2AD8();
            temp_f31 = gm_8016AE94();
            if (((temp_r28 ^ 0) != 0) && (temp_r26 != NULL)) {
                temp_r3 = temp_r28 >> 6;
                it_8026CA4C((u16*) &it_804A0E30.x4.x0, temp_r26, temp_r28, 6,
                            temp_f31);
                // if (*(u16*) ((u8*) &it_804A0E30 + 0x28) != 0) {
                if (it_804A0E30.x4.x8 != 0) {
                    // if (it_804A0E50.x8 != 0) {
                    it_8026CD50(temp_r26, temp_r3, temp_f31);
                }
            }
            it_8026CF04();
            HSD_GObjProc_8038FD54(GObj_Create(5U, 7U, 0U), fn_8026C88C, 0U);

            // @todo: Make a FLT_RAND(min, max) define or inline
            temp_r29 = it_804D6D28 + ((gm_8016AE80() * 8) + 0xFC);
            it_804A0E30.x0 =
                ((temp_r29[4] - temp_r29[0]) * HSD_Randf()) + temp_r29[0];
            it_804A0E30.x0 =
                it_804A0E30.x0 * Ground_801C2AE8(Stage_80225194());
        }
    }
#endif
}

// Spawn item of specified kind at specified position (but no z-offset)
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
    u8* temp_r30;

    temp_r29 = it_804A0E30.x18;
    temp_r30 = Ground_801C2AD8(); // u8* [4]
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
    return it_8026D324(It_Kind_Tomato) | it_8026D324(It_Kind_Foods) |
           it_8026D324(It_Kind_Heart);
}

void it_8026D564(Item_GObj* item_gobj)
{
    bool test;
    Item* ip = GET_ITEM((HSD_GObj*) item_gobj);
    CollData* coll = &ip->x378_itemColl;
    PAD_STACK(4);

    it_80276214(item_gobj);
    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;
    if (test) {
        ip->xC30 = coll->floor.index;
    }
}

bool it_8026D5CC(Item_GObj* item_gobj)
{
    Item* ip = GET_ITEM((HSD_GObj*) item_gobj);
    CollData* coll = &ip->x378_itemColl;

    it_80276214(item_gobj);
    return mpColl_8004B108(coll);
}

bool it_8026D604(Item_GObj* item_gobj)
{
    Item* ip = GET_ITEM((HSD_GObj*) item_gobj);

    return mpLib_80054ED8(ip->xC30);
}

void it_8026D62C(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test != false) {
        ip->xC30 = (u32) coll->floor.index;
    }
    if (test == false) {
        it_802762BC(ip);
        arg1((HSD_GObj*) gobj);
        return;
    }
    if ((it_80277544(gobj) != 0) && !ip->xDCD_flag.b3) {
        Item_8026ADC0((HSD_GObj*) gobj);
    }
}

void it_8026D6F4(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test != false) {
        ip->xC30 = coll->floor.index;
    }
    if (test == false) {
        arg1((HSD_GObj*) gobj);
    }
}

void it_8026D78C(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test != false) {
        ip->xC30 = coll->floor.index;
    }
    if (test == false) {
        arg1((HSD_GObj*) gobj);
        it_802762BC(ip);
    }
}

void it_8026D82C(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test) {
        ip->xC30 = coll->floor.index;
    }
    if (!test) {
        it_802762BC(ip);
    }
}

bool it_8026D8A4(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    bool test;
    PAD_STACK(8 * 4);

    it_80276214(gobj);

    {
        CollData* coll;
        Item* ip = GET_ITEM(gobj);
        coll = &ip->x378_itemColl;

        it_80276214(gobj);

        test = mpColl_8004B2DC(coll);
        ip->pos = coll->cur_pos;

        if (test != false) {
            ip->xC30 = coll->floor.index;
        }
    }
    if (it_802762D8(gobj) != false) {
        arg1(gobj);
    }
    return test;
}

void it_8026D938(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    Item* ip = GET_ITEM((HSD_GObj*) gobj);
    if (mpLib_80054ED8(ip->xC30) == false) {
        ip->xC30 = -1;
        arg1((HSD_GObj*) gobj);
    }
}

bool it_8026D9A0(Item_GObj* gobj)
{
    Item* item = GET_ITEM((HSD_GObj*) gobj);
    CollData* coll_data = &item->x378_itemColl;
    it_80276214(gobj);
    {
        u8 _[4];
        bool temp = mpColl_800477E0(coll_data);
        item->pos = coll_data->cur_pos;
        if (temp) {
            item->xC30 = coll_data->floor.index;
        }
        return temp;
    }
}

bool it_8026DA08(Item_GObj* gobj)
{
    Item* ip;
    CollData* coll;
    bool test;
    PAD_STACK(3 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;

    if (test) {
        ip->xC30 = coll->floor.index;
    }
    return test;
}

bool it_8026DA70(Item_GObj* gobj)
{
    Item* item = GET_ITEM((HSD_GObj*) gobj);
    CollData* coll = &item->x378_itemColl;

    it_80276214(gobj);
    return mpColl_800471F8(coll);
}

s32 it_8026DAA8(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    s32 test;
    PAD_STACK(12);

    ip = GET_ITEM((HSD_GObj*) gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    test |= it_80276308(gobj);
    test |= it_802763E0(gobj);
    return test;
}

bool it_8026DB40(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(12);

    ip = GET_ITEM((HSD_GObj*) gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (test != false) {
        ip->xC30 = coll->floor.index;
    }
    return test |= it_80276308(gobj);
}

bool it_8026DBC8(Item_GObj* gobj)
{
    if (it_8026DDFC(gobj) && it_8026DC24(gobj)) {
        it_802725D4(gobj);
        return it_8026DD5C(gobj);
    }
    return false;
}

bool it_8026DC24(Item_GObj* gobj)
{
    Item* ip = GET_ITEM((HSD_GObj*) gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    if (ip->xD50_landNum <= 1) {
        it_80274658(gobj, it_804D6D28->x74_float);
        it_80275DFC(gobj);
    }
    if (ABS(ip->x40_vel.x) <= 0.00001f) {
        ip->x40_vel.x = 0.0f;
    }
    if (ABS(ip->x40_vel.y) <= 0.00001f) {
        ip->x40_vel.y = 0.0f;
    }
    if (ABS(ip->x40_vel.x) <= attr->x5c) {
        if ((ABS(ip->x40_vel.y) <= attr->x5c)) {
            goto block_18a8;
        }
    }
    if (ip->xDCD_flag.b4 || !attr->x58) {
    block_18a8:
        itResetVelocity(ip);
        return true;
    }
    return false;
}

bool it_8026DD5C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM((HSD_GObj*) gobj);

    ip->xD50_landNum = 0;
    it_802762B0(ip);
    if (!it_80277040(gobj) || ip->xDCD_flag.b3) {
        it_80274740(gobj);
        it_80276CEC(gobj);
    } else {
        if (ip->xB8_itemLogicTable->entered_air != NULL) {
            Item_8026ADC0((HSD_GObj*) gobj);
            return false;
        }
        it_802734B4(gobj);
    }
    return true;
}

bool it_8026DDFC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xD50_landNum += 1;
    if (ip->xD50_landNum == 1) {
        if (ip->xD54_throwNum != 0) {
            u8* tmp = &it_804D6D28->x48_byte;
            if ((ip->xD54_throwNum == ((*tmp >> 4) & 0xF)) ||
                (HSD_Randi(*tmp & 0xF) == 0))
            {
                ip->destroy_type = 1;
                Item_8026A8EC(gobj);
                return false;
            }
        }
    }
    return true;
}

bool it_8026DE98(Item_GObj* gobj)
{
    return it_8026DDFC(gobj);
}

bool it_8026DF34(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(12);

    ip = GET_ITEM((HSD_GObj*) gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    if (cond) {
        return true;
    }
    return false;
}

bool it_8026DFB0(Item_GObj* gobj)
{
#if 1
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(26);

    ip = GET_ITEM((HSD_GObj*) gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    cond |= it_80276308(gobj);
    cond |= it_802763E0(gobj);
    if (cond & 0xF) {
        return true;
    }
    return false;
#else
    if (it_8026E_inline(gobj)) {
        return true;
    }
    return false;
#endif
}

bool it_8026E058(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(26);

    ip = GET_ITEM((HSD_GObj*) gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    cond |= it_80276308(gobj);
    if (cond & 0xD) {
        return true;
    }
    return false;
}

void it_8026E0F4(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(16);

    ip = GET_ITEM((HSD_GObj*) gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800477E0(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
}

inline bool it_8026E_inline(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(26);

    ip = GET_ITEM((HSD_GObj*) gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    cond |= it_80276308(gobj);
    cond |= it_802763E0(gobj);
    return cond & 0xF;
}

void it_8026E15C(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    bool res2;
    bool res = it_8026E_inline(gobj);
    u8 _[22];

    if (res) {
        it_80276FC4(gobj, res);
        if (res & 1) {
            if (it_8026DDFC(gobj) && it_8026DC24(gobj)) {
                it_802725D4(gobj);
                res2 = it_8026DD5C(gobj);
            } else {
                res2 = false;
            }
            if (res2 != false) {
                arg1((HSD_GObj*) gobj);
            }
        }
    }
}

void it_8026E248(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    bool res2;
    bool res = it_8026E_inline(gobj);
    PAD_STACK(26);

    if (res) {
        it_80276FC4(gobj, res);
        if (res & 1) {
            if (it_8026DE98(gobj) && it_8026DC24(gobj)) {
                res2 = it_8026DD5C(gobj);
            } else {
                res2 = false;
            }
            if (res2 != false) {
                arg1((HSD_GObj*) gobj);
            }
        }
    }
}
#if 0
bool it_8026E32C(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool chk2;
    PAD_STACK(42);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    if (chk & 0xF) {
        it_80276FC4(item_gobj, chk);
        if (chk & 1) {
            item = item_gobj->user_data;
            item->xD50_landNum += 1;
            if (it_8026DC24(item_gobj)) {
                chk2 = it_8026DD5C(item_gobj);
            } else {
                chk2 = false;
            }
            if (chk2) {
                arg1((HSD_GObj*) item_gobj);
            }
        }
    }
    return chk;
}

void it_8026E414(Item_GObj* item_gobj, HSD_GObjEvent arg1) {
    bool chk = it_8026DF34(item_gobj);

    chk |= it_80276308(item_gobj);
    chk |= it_802763E0(item_gobj);
    if (chk & 0xE) {
        it_80276FC4(item_gobj, chk);
    }
    if (chk & 1) {
        it_80275DFC(item_gobj);
        it_802762B0(item_gobj->user_data);
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E4D0(Item_GObj* item_gobj, HSD_GObjEvent arg1) {
    bool chk = it_8026DF34(item_gobj);

    chk |= it_80276308(item_gobj);
    chk |= it_802763E0(item_gobj);
    if (chk & 0xE) {
        it_80276FC4(item_gobj, chk);
    }
    if (chk & 1) {
        it_80275DFC(item_gobj);
        it_802762B0(item_gobj->user_data);
        arg1((HSD_GObj*) item_gobj);
        it_80272F7C(item_gobj->hsd_obj, item_gobj->user_data->xCC_item_attr->x60_scale);
    }
}

void it_8026E5A0(Item_GObj* item_gobj, HSD_GObjEvent arg1) {
    bool chk = it_8026DFB0(item_gobj);

    if (chk) {
        it_80276FC4(item_gobj, chk);
        if (chk & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item_gobj->user_data);
        }
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E664(Item_GObj* item_gobj, HSD_GObjEvent arg1) {
    bool chk = it_8026E058(item_gobj);

    if (chk) {
        if (chk & 0xC) {
            it_80276FC4(item_gobj, chk);
        }
        if (chk & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item_gobj->user_data);
        }
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E71C(Item_GObj* item_gobj, HSD_GObjEvent arg1) {
    bool chk = it_8026DFB0(item_gobj);

    if (chk) {
        if (chk & 0xC) {
            it_80276D9C(item_gobj, chk);
        }
        if (chk & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item_gobj->user_data);
        }
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E7E0(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool chk2;
    u8 pad[40];

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    {
        s32 chk_copy = chk;
        if (chk & 0xC) {
            it_80276D9C(item_gobj, chk_copy);
        }
    }
    if (chk & 1) {
        if (it_8026DE98(item_gobj) && it_8026DC24(item_gobj)) {
            chk2 = it_8026DD5C(item_gobj);
        } else {
            chk2 = false;
        }
        if (chk2) {
            arg1((HSD_GObj*) item_gobj);
        }
    }
}

void it_8026E8C4(Item_GObj* item_gobj, HSD_GObjEvent arg1, HSD_GObjEvent arg2) {
    Item* item;
    bool chk = it_8026DF34(item_gobj);

    item = item_gobj->user_data;
    if (chk == false) {
        it_802762BC(item);
        arg2((HSD_GObj*) item_gobj);
        return;
    }
    it_80277040(item_gobj);
    if (it_80276308(item_gobj)) {
        item->xD5C = 0;
    }
    if (!(item->xDC8_word.flags.x17 & 1) || ((u32) item->xD5C == 0U)) {
        it_80276CEC(item_gobj);
        arg1((HSD_GObj*) item_gobj);
    }
}
#else
bool it_8026E32C(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool chk2;
    PAD_STACK(38);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    if (chk & 0xF) {
        it_80276FC4(item_gobj, chk);
        if (chk & 1) {
            item = item_gobj->user_data;
            item->xD50_landNum += 1;
            if (it_8026DC24(item_gobj)) {
                chk2 = it_8026DD5C(item_gobj);
            } else {
                chk2 = false;
            }
            if (chk2) {
                arg1((HSD_GObj*) item_gobj);
            }
        }
    }
    return chk;
}

void it_8026E414(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    if (chk & 0xE) {
        it_80276FC4(item_gobj, chk);
    }
    if (chk & 1) {
        it_80275DFC(item_gobj);
        it_802762B0(item);
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E4D0(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    HSD_JObj* item_jobj;
    Item* item;
    bool chk;
    PAD_STACK(34);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    if (chk & 0xE) {
        it_80276FC4(item_gobj, chk);
    }
    if (chk & 1) {
        item_jobj = item_gobj->hsd_obj;
        it_80275DFC(item_gobj);
        it_802762B0(item);
        arg1((HSD_GObj*) item_gobj);
        it_80272F7C(item_jobj, item->xCC_item_attr->x60_scale);
    }
}

void it_8026E5A0(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    if (chk & 0xF) {
        if (chk & 0xE) {
            it_80276FC4(item_gobj, chk);
        }
        if (chk & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item);
        }
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E664(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    if (chk & 0xD) {
        if (chk & 0xC) {
            it_80276FC4(item_gobj, chk);
        }
        if (chk & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item);
        }
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E71C(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    if (chk & 0xF) {
        if (chk & 0xC) {
            it_80276D9C(item_gobj, chk);
        }
        if (chk & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item);
        }
        arg1((HSD_GObj*) item_gobj);
    }
}

void it_8026E7E0(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool chk2;
    PAD_STACK(30);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    // chk &= 0xC;
    if (chk & 0xC) {
        it_80276D9C(item_gobj, chk);
    }
    if (chk & 1) {
        if (it_8026DE98(item_gobj) && it_8026DC24(item_gobj)) {
            chk2 = it_8026DD5C(item_gobj);
        } else {
            chk2 = false;
        }
        if (chk2) {
            arg1((HSD_GObj*) item_gobj);
        }
    }
}

void it_8026E8C4(Item_GObj* item_gobj, HSD_GObjEvent arg1, HSD_GObjEvent arg2)
{
    CollData* coll;
    Item* item;
    bool chk;
    PAD_STACK(14);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_8004B108(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    if (chk == false) {
        it_802762BC(item);
        arg2((HSD_GObj*) item_gobj);
        return;
    }
    it_80277040(item_gobj);
    if (it_80276308(item_gobj)) {
        item->xD5C = 0;
    }
    if (!(item->xDC8_word.flags.x1F & 1) || (item->xD5C == 0U)) {
        it_80276CEC(item_gobj);
        arg1((HSD_GObj*) item_gobj);
    }
}
#endif

bool it_8026E9A4(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, Vec3* arg3)
{
    u8 _[4];
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, NULL, NULL, arg3, -1, -1, arg1->x, arg1->y,
                        arg2->x, arg2->y) == true)
    {
        *arg2 = p;
        return true;
    }
    return false;
}

bool it_8026EA20(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, Vec3* arg3,
                 UNK_T* arg4, u32* flags_out)
{
    Vec3 p;
    // PAD_STACK(4);
    PAD_STACK(8);

    if (mpCheckAllRemap(&p, *arg4, flags_out, arg3, -1, -1, arg1->x, arg1->y,
                        arg2->x, arg2->y) == true)
    {
        *arg2 = p;
        return true;
    }
    return false;
}

bool it_8026EA9C(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, Vec3* arg3, int* arg4,
                 u32* flags_out, s32 arg6)
{
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, arg4, flags_out, arg3, -1, arg6, arg1->x, arg1->y,
                        arg2->x, arg2->y) == true)
    {
        *arg2 = p;
        return true;
    }
    return false;
}

void it_8026EB18(HSD_GObj* gobj, s32 arg1, Vec3* arg2)
{
    Mtx m2;
    MtxPtr var_r30;
    if (arg2 != NULL) {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        MtxPtr temp_r30 = (MtxPtr) &cobj->view_mtx;
        {
            // @todo: This appears in several places in the codebase,
            // it's probably an inline
            Mtx m;
            PAD_STACK(1 * 4);
            PSMTXIdentity((MtxPtr) &m);
            m[0][3] = arg2->x;
            m[1][3] = arg2->y;
            m[2][3] = arg2->z;
            PSMTXConcat(temp_r30, (MtxPtr) &m, (MtxPtr) &m2);
            var_r30 = (MtxPtr) &m2;
        }
    } else {
        var_r30 = NULL;
    }
    HSD_JObjDispAll(GET_JOBJ(gobj), var_r30, HSD_GObj_80390EB8(arg1), 0U);
}

void it_8026EBC8(HSD_GObj* gobj, u16 arg1, u8* arg2)
{
    Item* ip = GET_ITEM(gobj);
    u16 cnt = 0;
    HSD_JObj* jobj;
    HSD_JObj* jobj_parent;
    u8* index = arg2;
    while (cnt < arg1) {
        jobj = ip->xBBC_dynamicBoneTable->bones[*index];
        jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A18(jobj);
        }
        cnt++;
        index++;
    }
}

void it_8026EC54(HSD_GObj* gobj, u16 arg1, u8* arg2)
{
    Item* ip = GET_ITEM(gobj);
    u16 cnt = 0;
    HSD_JObj* jobj;
    HSD_JObj* jobj_parent;
    u8* index = arg2;
    while (cnt < arg1) {
        jobj = ip->xBBC_dynamicBoneTable->bones[*index];
        jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A3C(jobj);
        }
        cnt++;
        index++;
    }
}

// arg1 is some kind of enum type? It gets passed to functions that check if
// it's 0 or 2 to run
bool it_8026ECE0(Item_GObj* gobj, u32 arg1)
{
    Item* ip;
    bool chk;
    u32 idx;

    chk = false;
    ip = GET_ITEM((HSD_GObj*) gobj);
    if (ip->kind == It_Kind_Unk4) {
        if (ip->xDAA_flag.b0 &&
            (ip->xDD4_itemVar.it_266F.x18.b0 ||
             ip->xDD4_itemVar.it_266F.x18.b1) &&
            lbColl_8000A10C(&ip->xDD4_itemVar.it_266F.x1C, arg1, ip->scl))
        {
            chk = true;
        }
    } else {
        if (ip->xDAA_flag.b6) {
            if (ip->xDAA_flag.b2) {
                idx = 0U;
                while (idx < 4U) {
                    if (lbColl_80009F54(&ip->x5D4_hitboxes[idx].hit, arg1,
                                        ip->scl) != false)
                    {
                        chk = true;
                    }
                    idx++;
                }
            }
            if (!ip->xDC8_word.flags.x13 && ip->xDAA_flag.b1) {
                if (ip->xD0C == 0) {
                    idx = 0U;
                    while (idx < ip->xAC8_hurtboxNum) {
                        if (lbColl_8000A244(&ip->xACC_itemHurtbox[idx], arg1,
                                            NULL, 0.0f) != false)
                        {
                            chk = true;
                        }
                        idx++;
                    }
                } else {
                    idx = 0U;
                    while (idx < ip->xAC8_hurtboxNum) {
                        if (lbColl_8000A584(&ip->xACC_itemHurtbox[idx],
                                            ip->xD0C, arg1, NULL,
                                            0.0f) != false)
                        {
                            chk = true;
                        }
                        idx++;
                    }
                }
            }
        }
        if (ip->xDAA_flag.b4 && ip->xDC8_word.flags.x15 &&
            (lbGx_8001E2F8((Vec4*) &ip->xBCC_unk, &ip->pos, &it_804D5168, arg1,
                           ip->facing_dir) != false))
        {
            chk = true;
        }
        if (ip->xDAA_flag.b3 && ip->xDD0_flag.b0 &&
            (lb_800149E0((MtxPtr) &ip->xB54, arg1) != false))
        {
            chk = true;
        }
    }
    return chk;
}

#if 0
static inline void it_8026EECC_inline_1(HSD_GObj* gobj, s32 arg1, Vec3* pos) {
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;
    it_266F_ItemVars* it_266F;

    ip->xDCF_flag.b4 = 1;
    ip->xDCF_flag.b5 = 0;
    it_266F = &ip->xDD4_itemVar.it_266F;
    it_8026EC54(gobj, it_266F->x0, it_266F->x4);
    it_8026EBC8(gobj, it_266F->x8, it_266F->xC);
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8(gobj, it_266F->x0, it_266F->x4);
    it_8026EC54(gobj, it_266F->x8, it_266F->xC);
}

static inline void it_8026EECC_inline_2(HSD_GObj* gobj, s32 arg1, Vec3* pos) {
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;

    ip->xDCF_flag.b4 = 0;
    ip->xDCF_flag.b5 = 0;
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
}

static inline void it_8026EECC_inline_3(HSD_GObj* gobj, s32 arg1, Vec3* pos) {
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;
    it_266F_ItemVars* it_266F;

    ip->xDCF_flag.b4 = 1;
    ip->xDCF_flag.b5 = 1;
    it_266F = &ip->xDD4_itemVar.it_266F;
    it_8026EC54(gobj, it_266F->x0, it_266F->x4);
    it_8026EBC8(gobj, it_266F->x8, it_266F->xC);
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    } else {
        new_pos = NULL;
    }

    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8(gobj, it_266F->x0, it_266F->x4);
    it_8026EC54(gobj, it_266F->x8, it_266F->xC);
}
#else
static inline void it_8026EECC_inline_1(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;

    ip->xDCF_flag.b4 = 1;
    ip->xDCF_flag.b5 = 0;
    it_8026EC54(gobj, ip->xDD4_itemVar.it_266F.x0,
                ip->xDD4_itemVar.it_266F.x4);
    it_8026EBC8(gobj, ip->xDD4_itemVar.it_266F.x8,
                ip->xDD4_itemVar.it_266F.xC);
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8(gobj, ip->xDD4_itemVar.it_266F.x0,
                ip->xDD4_itemVar.it_266F.x4);
    it_8026EC54(gobj, ip->xDD4_itemVar.it_266F.x8,
                ip->xDD4_itemVar.it_266F.xC);
}

static inline void it_8026EECC_inline_2(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;

    ip->xDCF_flag.b4 = 0;
    ip->xDCF_flag.b5 = 0;
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
}

static inline void it_8026EECC_inline_3(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;

    ip->xDCF_flag.b4 = 1;
    ip->xDCF_flag.b5 = 1;
    it_8026EC54(gobj, ip->xDD4_itemVar.it_266F.x0,
                ip->xDD4_itemVar.it_266F.x4);
    it_8026EBC8(gobj, ip->xDD4_itemVar.it_266F.x8,
                ip->xDD4_itemVar.it_266F.xC);
    if (ip->xDCF_flag.b7) {
        new_pos = pos;
    } else {
        new_pos = NULL;
    }

    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8(gobj, ip->xDD4_itemVar.it_266F.x0,
                ip->xDD4_itemVar.it_266F.x4);
    it_8026EC54(gobj, ip->xDD4_itemVar.it_266F.x8,
                ip->xDD4_itemVar.it_266F.xC);
}
#endif

void it_8026EECC(HSD_GObj* gobj, int arg1)
{
    Item* ip = gobj->user_data;
    Vec3 pos;
    PAD_STACK(48);

    if (ip->xDAA_flag.b7) {
        pos.x = pos.y = pos.z = 0.0F;
        if (ip->xDC8_word.flags.x13) {
            if ((ip->owner == NULL) || !ftLib_80086960(ip->owner) ||
                ftLib_800868D4(ip->owner, gobj))
            {
                ip = gobj->user_data;
                ip->xDCF_flag.b7 = 0;
                if ((ip->owner != NULL) && ftLib_80086960(ip->owner)) {
                    if (ftLib_80087074(ip->owner, &pos)) {
                        ip->xDCF_flag.b7 = 1;
                    }
                } else {
                    pos.x = pos.y = pos.z = 0.0F;
                }

                // @todo This could just be one big function call.
                ip = gobj->user_data;
                switch (Camera_80031060()) {
                case 1:
                    if (ip->xDCF_flag.b3) {
                        it_8026EECC_inline_1(gobj, arg1, &pos);
                        it_8026EECC_inline_2(gobj, arg1, &pos);
                        it_8026EECC_inline_3(gobj, arg1, &pos);
                    }
                    break;
                case 0:
                    if (!ip->xDCF_flag.b3) {
                        it_8026EECC_inline_2(gobj, arg1, &pos);
                    }
                    break;
                }
            }
        } else {
            ip = gobj->user_data;
            switch (Camera_80031060()) {
            case 1:
                if (ip->xDCF_flag.b3) {
                    it_8026EECC_inline_1(gobj, arg1, &pos);
                    it_8026EECC_inline_2(gobj, arg1, &pos);
                    it_8026EECC_inline_3(gobj, arg1, &pos);
                }
                break;
            case 0:
                if (!ip->xDCF_flag.b3) {
                    it_8026EECC_inline_2(gobj, arg1, &pos);
                }
                break;
            }
        }
    }
    // if (it_8026ECE0((Item_GObj*) gobj, arg1)) {
    // if (it_8026ECE0((Item_GObj*) gobj, arg1) != false) {
    if (it_8026ECE0((Item_GObj*) gobj, arg1) != 0U) {
        HSD_StateInvalidate(-1);
        HSD_StateInitTev();
        HSD_ClearVtxDesc();
    }
}

ItemKind it_8026F3AC(void)
{
    return it_8026C75C(&it_804A0E50);
}

void it_8026F3D4(Item_GObj* item_gobj, struct it_8026F3D4_arg1_t* arg1,
                 s32 num, s32 arg3)
{
    // HSD_ObjAllocUnk6 sp30;
    struct it_8026F3D4_body_t sp30;
    s32 cnt2;
    Vec3 sp24;
    Item* item;
    Item_GObj* spawned_item_gobj;
    bool chk2;
    s32 cnt;
    bool chk1;
    ItemKind it_kind;
    PAD_STACK(120);

    spawned_item_gobj = NULL;
    chk1 = false;
    it_kind = -1;
    cnt = 0;
    item = item_gobj->user_data;
    cnt2 = 0;
    while (cnt < num) {
        if (((arg3 & 1) == 0) || ((s32) it_kind == -1)) {
            it_kind = it_8026C75C(&it_804A0E50);
        }
        if (((s32) it_kind == -1) || (it_kind >= It_Kind_L_Gun_Ray) ||
            ((it_kind == It_Kind_M_Ball) && it_8026C704()))
        {
            if ((s32) it_kind == -1) {
                chk2 = false;
            }
            if (it_kind >= It_Kind_L_Gun_Ray) {
                chk2 = true;
            }
            chk1 |= chk2;
            break;
            // goto block_3068;
        } else {
            spawned_item_gobj = it_8026F5C8(item_gobj, it_kind, &item->pos);
            if (spawned_item_gobj != NULL) {
                sp24.z = 0.0f;
                sp24.y = 0.0f;
                sp24.x = 0.0f;
                it_8026F53C(spawned_item_gobj, &sp24, 0);
                chk1 = false;
                it_80274ED8();
                // (&sp30[0])[cnt2] = (s32) it_kind;
                sp30.x0[(s8) cnt2 << 2] = it_kind;

                // sp30.x0[0] = it_kind;
                cnt2++;
            }
            cnt++;
        }
    }
    // block_3068:
    if (ftLib_80086960(item->owner) && (cnt2 != 0)) {
        ftLib_800874CC(item->owner, &sp30, cnt2);
    }
    if (arg1 != NULL) {
        arg1->x0 = chk1;
        arg1->x4 = it_kind;
        arg1->x8 = spawned_item_gobj;
    }
}

void it_8026F53C(Item_GObj* item_gobj, Vec3* vel, bool chk)
{
    Item* item;

    item = item_gobj->user_data;
    if (chk == false) {
        vel->x = it_804D6D28->x54_float * (2.0f * (HSD_Randf() - 0.5f));
        vel->y = item->xCC_item_attr->x18;
        vel->z = 0.0f;
    }
    item->x40_vel = *vel;
}

Item_GObj* it_8026F5C8(Item_GObj* item_gobj, ItemKind kind, Vec3* pos)
{
    SpawnItem spawn;
    Item_GObj* spawn_gobj;
    PAD_STACK(12);

    spawn.kind = kind;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x3C_damage = 0;
    spawn.x44_flag.b0 = 1;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    spawn.x40 = 0;
    spawn.facing_dir = it_8026B684(&spawn.prev_pos);
    if (item_gobj != NULL) {
        it_8026BB88(item_gobj, &spawn.pos);
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = (HSD_GObj*) item_gobj;
    } else {
        spawn.pos = spawn.prev_pos;
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    }
    spawn_gobj = Item_80268B18(&spawn);
    if (spawn_gobj != NULL) {
        it_80274658(spawn_gobj, it_804D6D28->x70_float);
    }
    return spawn_gobj;
}

Item_GObj* it_8026F6BC(Item_GObj* item_gobj, Vec3* arg1, Vec3* vel, bool chk)
{
    Item* spawned_item;
    Item_GObj* spawned_item_gobj;
    PAD_STACK(96);

    if (Item_804A0C64.x2C >= Item_804A0C64.x30) {
        return NULL;
    }
    if (HSD_Randi(it_804D6D28->x124) != 0) {
        return NULL;
    }
    spawned_item_gobj =
        it_8026F5C8(item_gobj, it_8026C65C(&it_804A0E60), arg1);
    if (spawned_item_gobj != NULL) {
        spawned_item = spawned_item_gobj->user_data;
        if (chk == false) {
            vel->x = it_804D6D28->x54_float * (2.0f * (HSD_Randf() - 0.5f));
            vel->y = spawned_item->xCC_item_attr->x18;
            vel->z = 0.0f;
        }
        spawned_item->x40_vel = *vel;
    }
    return spawned_item_gobj;
}

Item_GObj* it_8026F7C8(Vec3* arg0, Vec3* vel, bool chk)
{
    Item* spawned_item;
    Item_GObj* spawned_item_gobj;
    ItemKind it_kind;
    PAD_STACK(80);

    if (gm_8016B238()) {
        return NULL;
    }
    it_kind = it_8026C75C(&it_804A0E50);
    if ((s32) it_kind == -1) {
        return NULL;
    }
    spawned_item_gobj = it_8026F5C8(NULL, it_kind, arg0);
    if (spawned_item_gobj != NULL) {
        spawned_item = spawned_item_gobj->user_data;
        if (chk == false) {
            vel->x = it_804D6D28->x54_float * (2.0f * (HSD_Randf() - 0.5f));
            vel->y = spawned_item->xCC_item_attr->x18;
            vel->z = 0.0f;
        }
        spawned_item->x40_vel = *vel;
        it_80274ED8();
    }
    return spawned_item_gobj;
}

bool it_8026F8B4(Item_GObj* item_gobj, Vec3* arg1, Vec3* arg2, bool chk)
{
    s32 rand_int;
    PAD_STACK(20);

    if (gm_8016B0B4() == false) {
        return false;
    }
    if (HSD_Randi(it_804D6D28->x138) != 0) {
        return false;
    }
    rand_int = HSD_Randi(it_804D6D28->x13C);
    rand_int += it_804D6D28->x140;
    if (chk == false) {
        arg2->x = it_804D6D28->x54_float * (2.0f * (HSD_Randf() - 0.5f));
        arg2->y = it_804D6D28->x144;
        arg2->z = 0.0f;
    }
    it_802E5F00(item_gobj, arg1, arg2, rand_int);
    return true;
}

void it_8026F9A0(void)
{
    it_804D6D18 = 0;
}
