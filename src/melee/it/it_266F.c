

#include <platform.h>

#include "it/it_266F.h"

#include "inlines.h"
#include "types.h"

#include "cm/camera.h"
#include "db/db_2253.h"
#include "ef/efsync.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
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

extern ItemCommonData* it_804D6D28;
extern HSD_ObjAllocUnk Item_804A0C64;

s32 lb_800149E0(f32*, u32); /* extern */
static U8Vec4 it_804D5168 = { 0xFF, 0x40, 0x80, 0x80 };

void it_8026C47C(struct it_8026C47C_arg0_t* arg0)
{
    s32* var_r28;
    s32 var_r29;
    u32 var_r30;
    f32 pad[2];

    var_r30 = 0;
    var_r29 = 0;
    var_r28 = (s32*) arg0;
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk18 = 0;
    arg0->unk1C = 0;
    while (var_r30 < 238) {
        if (it_80272828(var_r30) != 0U) {
            *var_r28 |= 1 << var_r29;
        }
        var_r30 += 1;
        var_r29 += 1;
        if (!(var_r30 & 0x1F)) {
            var_r29 = 0;
            var_r28 += 1;
        }
    }
}

#if 0
s32 it_8026C530(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 temp_r10;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 temp_r7_3;
    s32 temp_r8;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_r5;

    var_r5 = arg2;
    temp_r8 = arg3 - 1;
    if (var_r5 == temp_r8) {
        return var_r5;
    }
    temp_r10 = arg1->unkC;
    temp_r9 = (s32) (var_r5 + arg3) / 2;
    temp_r7_2 = temp_r9 * 2;
    if ((s32) *(temp_r10 + temp_r7_2) > arg0) {
        if (var_r5 == (s32) (temp_r9 - 1)) {

        } else {
            temp_r6 = (s32) (var_r5 + temp_r9) / 2;
            temp_r7_3 = temp_r6 * 2;
            if ((s32) *(temp_r10 + temp_r7_3) > arg0) {
                var_r5 = it_8026C530();
            } else if ((s32) (temp_r10 + temp_r7_3)->unk2 > arg0) {
                var_r5 = temp_r6;
            } else {
                var_r5 = it_8026C530(temp_r6, temp_r9);
            }
        }
        return var_r5;
    }
    temp_r9_2 = temp_r10 + 2;
    if ((s32) *(temp_r9_2 + temp_r7_2) > arg0) {
        return temp_r9;
    }
    if (temp_r9 == temp_r8) {
        return temp_r9;
    }
    temp_r7 = (s32) (temp_r9 + arg3) / 2;
    temp_r5 = temp_r7 * 2;
    if ((s32) *(temp_r10 + temp_r5) > arg0) {
        return it_8026C530(temp_r9, temp_r7);
    }
    if ((s32) *(temp_r9_2 + temp_r5) > arg0) {
        return temp_r7;
    }
    return it_8026C530(temp_r7);
}
#endif

// argument is definitely size 0x10
u8 it_8026C65C(HSD_ObjAllocUnk6* arg0)
{
    s32 temp_r3;
    s32 temp_r4;
    s32* temp_r5;
    s32 temp_r6;
    s32 var_r3;
    u8 temp_r31;
    s32 val;

    temp_r3 = HSD_Randi(arg0->x8);
    if ((arg0->x0 - 1) == 0) {
        var_r3 = 0;
    } else {
        temp_r6 = (s32) arg0->x0 / 2;
        temp_r4 = temp_r6 * 2;
        val = arg0->xC[temp_r6];
        if (val > temp_r3) {
            var_r3 = it_8026C530(0, arg0, 0, temp_r6);
        } else if (arg0->xC[temp_r6 + 1] > temp_r3) {
            var_r3 = temp_r6;
        } else {
            var_r3 = it_8026C530(0, arg0, temp_r6, (s32) arg0->x0);
        }
    }
    return arg0->x4[var_r3];
}

s32 it_8026C704(void)
{
    s32 var_r31;

    var_r31 = 0;
    if ((Item_804A0C64.x1C >= Item_804A0C64.x20) || (it_8026D324(34) == 0)) {
        var_r31 = 1;
    }
    return var_r31;
}

s8 it_8026C75C(HSD_ObjAllocUnk6* arg0)
{
    s32 temp_r0;
    s32 var_r29;
    s32 var_r31;
    u16 temp_r5;
    u16 var_r30;
    u8 temp_r0_2;
    u8 temp_r4;
    u8 var_r3;

    var_r31 = it_8026C704();
    var_r29 = 0;
    if (arg0->x8 == 0) {
        return -1;
    }
    if (var_r31 != 0) {
        temp_r4 = arg0->x0;
        if (arg0->x4[temp_r4 - 1] == 34) {
            temp_r0 = arg0->x0 - 1;
            if (temp_r0 < 1) {
                return -1;
            }
            var_r30 = arg0->x8;
            var_r29 = 1;
            arg0->x8 = arg0->xC[temp_r0];
            arg0->x0 -= 1;
        }
    }
    var_r3 = arg0->x4[it_8026C530(HSD_Randi((s32) arg0->x8), arg0, 0,
                                  (s32) arg0->x0)];
    if ((var_r31 != 0) && (var_r29 != 0)) {
        arg0->x8 = var_r30;
        arg0->x0 += 1;
        if ((s32) var_r3 == 34) {
            var_r3 = -1;
        }
    }
    return var_r3;
}

void fn_8026C88C(HSD_GObj* gobj)
{
    Item_GObj* temp_r3;
    Item_GObj* temp_ret;
    s32 var_r4;

    Item_GObj* spawn_gobj;
    SpawnItem spawn;
    s32 temp_r4;

    if (db_80225D54(&it_804A0E30) != 0U) {
        it_804A0E30.x0 -= 1;
        if ((s32) it_804A0E30.x0 == 0) {
            spawn.kind = it_8026C75C(&it_804A0E30.x4);
            if ((s32) spawn.kind != -1) {
                if (it_8026CB3C(&spawn.prev_pos) != 0) {
                    spawn.pos = spawn.prev_pos;
                    spawn.facing_dir = it_8026B684(&spawn.prev_pos);
                    spawn.x3C_damage = 0;
                    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
                    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj = NULL;
                    spawn.x44_flag.b0 = 1;
                    spawn.x40 = 0;
                    var_r4 = 1;
                } else {
                    var_r4 = 0;
                }
                if (var_r4 != 0) {
                    spawn_gobj = Item_80268B18(&spawn);
                    if (spawn_gobj != NULL) {
                        efSync_Spawn(0x420, spawn_gobj, &spawn.prev_pos);
                        it_80274ED8();
                    }
                }
            }
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
}

void it_8026CA4C(u16* arg0, s32* arg1, u64 arg2, s32 arg4, f32 arg8)
{
    u64 var_r5;
    s32* var_r28;
    s32 var_r31;
    s32 var_r27;

    var_r5 = arg2;
    var_r31 = arg4;
    var_r28 = arg1 + arg4;
    var_r27 = 0;
    while (var_r31 < 0x23) {
        if (((var_r5 & 1) ^ 0) != 0) {
            var_r27 = ((f32) var_r27 + ((arg8 * (f32) *var_r28) + 0.99f));
        }
        var_r28 += 1;
        var_r31 += 1;
        var_r5 = var_r5 >> 1;
    }
    arg0[4] = var_r27;
}

s32 it_8026CB3C(Vec3* arg0)
{
    if (Stage_80224FDC(arg0) == 0) {
        return 0;
    }
    arg0->z = 0.0f;
    if (mpColl_8004D024(arg0) != 0) {
        return 0;
    }
    return 1;
}

void it_8026CB9C(s32* arg0, u64 arg2, u32 arg3, f32 arg8)
{
    s32 temp_r26;
    {
        u64 var_r5;
        s32* var_r28;
        s32 var_r31;
        s32 var_r27;

        var_r5 = arg2;
        var_r31 = 0;
        var_r28 = arg0;
        var_r27 = 0;
        while (var_r31 < 35) {
            if (((var_r5 & 1) ^ 0) != 0 && *var_r28 != 0) {
                var_r27 += 1;
            }
            var_r28 += 1;
            var_r31 += 1;
            var_r5 = var_r5 >> 1;
        }
        temp_r26 = var_r27 * 4;
        it_804A0E30.x4.x0 = var_r27;
        it_804A0E30.x4.x4 = (u8*) HSD_MemAlloc(temp_r26);
        it_804A0E30.x4.xC = (u16*) HSD_MemAlloc(temp_r26);
    }
    {
        u64 var_r5;
        s32* var_r28;
        s32 var_r31;
        s32 var_r27;
        s32 var_r26_2;
        s32 var_r29;
        s32 var_r25;

        var_r26_2 = 0;
        var_r5 = arg2;
        var_r28 = arg0;

        var_r29 = 0;
        var_r27 = 0;
        var_r25 = 0;

        while (var_r27 < 35) {
            if (((var_r5 & 1) ^ 0) != 0 && *var_r28 != 0) {
                it_804A0E30.x4.x4[var_r26_2] = var_r27;
                var_r26_2 += 1;
                it_804A0E30.x4.xC[var_r29] = var_r25;
                var_r29 += 2;
                var_r25 =
                    (s16) ((f32) var_r25 + ((arg8 * (f32) *var_r28) + 0.99f));
            }
            var_r28 += 1;
            var_r27 += 1;
            var_r5 = var_r5 >> 1;
        }
    }
}

/// #it_8026CD50

void it_8026CF04(void)
{
    s16 temp_r4;
    s16 temp_r8_2;
    s32 temp_r8;
    u8* temp_r30;

    // @todo: probably a double somewhere
    temp_r4 = it_804D6D28->x128 + it_804D6D28->x12C + it_804D6D28->x130 +
              it_804D6D28->x134;
    // @todo: Investigate why it_804A0E30 is used instead of it_804A0E50.
    if (temp_r4 != 0) {
        it_804A0E50.x8 = temp_r4;
        it_804A0E50.x0 = 4U;
        temp_r30 = it_804A0E50.x4;
        it_804A0E50.x4 = (u8*) HSD_MemAlloc(it_804A0E50.x0 * 4);
        it_804A0E50.xC = (u16*) HSD_MemAlloc(it_804A0E50.x0 * 4);
        temp_r30[0] = 0x2B;
        it_804A0E50.xC[0] = 0;
        temp_r8 = it_804D6D28->x128;
        temp_r30[1] = 0x2C;
        it_804A0E50.xC[1] = (s16) temp_r8;
        temp_r8_2 = temp_r8 + it_804D6D28->x12C;
        temp_r30[2] = 0x2D;
        it_804A0E50.xC[2] = temp_r8_2;
        temp_r30[3] = 0x2E;
        it_804A0E50.xC[3] = temp_r8_2 + it_804D6D28->x130;
    }
}

void it_8026D018(void)
{
    s32 var_r29;
    if ((gm_8016B238() == 0) && (gm_8016AE80() != -1)) {
        it_804A0E30.x18 = gm_8016AEA4();
        var_r29 = 0;
        {
            u64 temp_r28 = it_804A0E30.x18;
            s32* temp_r26 = (s32*) Ground_801C2AD8();
            s32 temp_r30 = gm_8016AE80();
            f32 temp_f31 = gm_8016AE94();
            if (((temp_r28 ^ 0) == 0) || (temp_r26 == NULL) ||
                (temp_r30 == -1))
            {
                var_r29 = 0;
            } else {
                it_8026CA4C((u16*) &it_804A0E30.x4.x0, temp_r26, temp_r28, 0,
                            temp_f31);
                if ((u16) it_804A0E30.x4.x8 == 0) {
                } else {
                    it_8026CB9C(temp_r26, temp_r28, 0, temp_f31);
                    var_r29 = 1;
                }
            }
        }
        if (var_r29 != 0) {
            {
                u64 temp_r26_2 = it_804A0E30.x18;
                s32* temp_r28_2 = (s32*) Ground_801C2AD8();
                f32 temp_f31_2 = gm_8016AE94();
                if (((temp_r26_2 ^ 0) != 0) && (temp_r28_2 != NULL)) {
                    u64 temp_r3 = temp_r26_2 >> 6;
                    it_8026CA4C((u16*) &it_804A0E30.x4.x0, temp_r28_2,
                                temp_r26_2, 6, temp_f31_2);
                    if (*(u16*) ((u8*) &it_804A0E30 + 0x28) != 0) {
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
}

#if 0
s32 it_8026D258(void *arg0, s32 arg1) {
    u8 sp54;
    s32 sp50;
    s16 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp34;
    s32 sp30;
    f32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 temp_r0;
    s32 temp_r4;
    s32 var_r7;

    var_r7 = 0;
    if ((s32) Item_804A0C64.x60 < (s32) Item_804A0C64.x64) {
        sp18 = arg1;
        temp_r4 = arg0->unk0;
        temp_r0 = arg0->unk4;
        sp30 = temp_r4;
        sp34 = temp_r0;
        sp38 = arg0->unk8;
        sp38 = 0.0f;
        sp24 = temp_r4;
        sp28 = temp_r0;
        sp2C = sp38;
        sp48 = it_8026B684((Vec3 *) &sp30);
        sp4C = 0;
        sp44 = 0.0f;
        sp40 = 0.0f;
        sp3C = 0.0f;
        sp10 = 0;
        sp14 = sp10;
        sp54 |= 0x80;
        sp50 = 0;
        Item_80268B9C((SpawnItem *) &sp10);
        var_r7 = 1;
    }
    return var_r7;
}
#endif

bool it_8026D324(s32 arg0)
{
    u64 temp_r29;
    s32 temp_r3;
    u32 temp_r28;
    u64 temp_ret;
    u8* temp_r30;

    temp_r29 = it_804A0E30.x18;
    temp_r30 = Ground_801C2AD8();
    temp_r3 = gm_8016AE80();
    if ((((temp_r29 ^ 0)) == 0) || (temp_r30 == NULL) || (temp_r3 == -1)) {
        return 0;
    }
    temp_ret = temp_r29 >> arg0;
    if (((temp_ret & 1) ^ 0) == 0) {
        return 0;
    }
    return 1;
}

s32 it_8026D3CC(void)
{
    return it_8026D324(9) | it_8026D324(18) | it_8026D324(8);
}

void it_8026D564(Item_GObj* gobj)
{
    bool test;
    Item* ip = GET_ITEM(gobj);
    CollData* coll = &ip->x378_itemColl;
    it_80276214(gobj);
    PAD_STACK(4);
    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_topn;
    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
}

void it_8026D5CC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    CollData* coll = &ip->x378_itemColl;
    it_80276214(gobj);
    mpColl_8004B108(coll);
}

s32 it_8026D604(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
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
    ip->pos = coll->cur_topn;

    if (test != 0) {
        ip->xC30 = (u32) coll->floor.index;
    }
    if (test == 0) {
        it_802762BC(ip);
        arg1(gobj);
        return;
    }
    if ((it_80277544(gobj) != 0) && !ip->xDCD_flag.b3) {
        Item_8026ADC0(gobj);
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
    ip->pos = coll->cur_topn;

    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    if (test == 0) {
        arg1(gobj);
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
    ip->pos = coll->cur_topn;

    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    if (test == 0) {
        arg1(gobj);
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
    ip->pos = coll->cur_topn;

    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    if (test == 0) {
        it_802762BC(ip);
    }
}

s32 it_8026D8A4(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    Item* ip;
    CollData* coll;
    bool test;
    PAD_STACK(9 * 4);

    it_80276214(gobj);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B2DC(coll);
    ip->pos = coll->cur_topn;

    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    if (it_802762D8(gobj) != 0) {
        arg1(gobj);
    }
    return test;
}

void it_8026D938(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    Item* ip = gobj->user_data;
    if (mpLib_80054ED8(ip->xC30) == 0) {
        ip->xC30 = -1;
        arg1(gobj);
    }
}

bool it_8026D9A0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    CollData* coll_data = &item->x378_itemColl;
    it_80276214(gobj);
    {
        u8 _[4];
        bool temp = mpColl_800477E0(coll_data);
        item->pos = coll_data->cur_topn;
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
    ip->pos = coll->cur_topn;

    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    return test;
}

bool it_8026DA70(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    CollData* coll = &item->x378_itemColl;
    it_80276214(gobj);
    return mpColl_800471F8(coll);
}

s32 it_8026DAA8(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool test;
    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    PAD_STACK(12);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_topn;
    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    test |= it_80276308(gobj);
    return test | it_802763E0(gobj);
}

s32 it_8026DB40(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool test;
    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    PAD_STACK(12);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_topn;
    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    return test |= it_80276308(gobj);
}

s32 it_8026DBC8(HSD_GObj* gobj)
{
    if ((it_8026DDFC(gobj) != 0) && (it_8026DC24(gobj) != 0)) {
        it_802725D4(gobj);
        return it_8026DD5C(gobj);
    }
    return 0;
}

s32 it_8026DC24(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    if (ip->xD50_landNum <= 1) {
        it_80274658(gobj, it_804D6D28->x74_float);
        it_80275DFC(gobj);
    }
    if (fabs_inline(ip->x40_vel.x) <= 0.00001f) {
        ip->x40_vel.x = 0.0f;
    }
    if (fabs_inline(ip->x40_vel.y) <= 0.00001f) {
        ip->x40_vel.y = 0.0f;
    }
    if (fabs_inline(ip->x40_vel.x) <= attr->x5c) {
        if (!(fabs_inline(ip->x40_vel.y) <= attr->x5c)) {
            return 0;
        }
    }
    if (ip->xDCD_flag.b3 || (attr->x58 == 0.0f)) {
        ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0F;
        return 1;
    }
    return 0;
}

s32 it_8026DD5C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD50_landNum = 0;
    it_802762B0(ip);
    if ((it_80277040(gobj) == 0) || ip->xDCD_flag.b3) {
        it_80274740(gobj);
        it_80276CEC(gobj);
        return 1;
    }
    if (ip->xB8_itemLogicTable->entered_air != NULL) {
        Item_8026ADC0(gobj);
        return 0;
    }
    it_802734B4(gobj);
    return 1;
}

s32 it_8026DDFC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD50_landNum += 1;
    if ((u32) ip->xD50_landNum == 1U) {
        if (ip->xD54_throwNum != 0U) {
            if ((((ip->xD54_throwNum ==
                   ((u32) (it_804D6D28->x48_float >> 4U) & 0xF)) != 0)) ||
                (HSD_Randi(it_804D6D28->x48_float & 0xF) == 0))
            {
                ip->destroy_type = 1;
                Item_8026A8EC(gobj);
            }
            return 0;
        }
    }
    return 1;
}

s32 it_8026DE98(Item_GObj* arg0)
{
    return it_8026DDFC(arg0);
}

s32 it_8026DF34(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    PAD_STACK(12);
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_topn;
    if (cond) {
        ip->xC30 = (u32) coll->floor.index;
    }
    if (cond) {
        return 1;
    }
    return 0;
}

s32 it_8026DFB0(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    PAD_STACK(26);
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_topn;
    if (cond) {
        ip->xC30 = (u32) coll->floor.index;
    }
    cond |= it_80276308(gobj);
    if ((cond | it_802763E0(gobj)) & 0xF) {
        return 1;
    }
    return 0;
}

s32 it_8026E058(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    PAD_STACK(26);
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_topn;
    if (cond) {
        ip->xC30 = (u32) coll->floor.index;
    }
    cond |= it_80276308(gobj);
    if (cond & 0xD) {
        return 1;
    }
    return 0;
}

void it_8026E0F4(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    PAD_STACK(16);
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_topn;
    if (cond) {
        ip->xC30 = (u32) coll->floor.index;
    }
}

void it_8026E15C(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    s32 var_r3;
    bool res = it_8026DFB0(gobj);
    if (res) {
        it_80276FC4(gobj);
        if (res & 1) {
            if ((it_8026DDFC(gobj) != 0) && (it_8026DC24(gobj) != 0)) {
                it_802725D4(gobj);
                var_r3 = it_8026DD5C(gobj);
            } else {
                var_r3 = 0;
            }
            if (var_r3 != 0) {
                arg1(gobj);
            }
        }
    }
}

void it_8026E248(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    s32 var_r3;
    bool res = it_8026DFB0(gobj);
    if (res) {
        it_80276FC4(gobj);
        if (res & 1) {
            if ((it_8026DE98(gobj) != 0) && (it_8026DC24(gobj) != 0)) {
                var_r3 = it_8026DD5C(gobj);
            } else {
                var_r3 = 0;
            }
            if (var_r3 != 0) {
                arg1(gobj);
            }
        }
    }
}

/// #it_8026E32C

/// #it_8026E414

/// #it_8026E4D0

/// #it_8026E5A0

/// #it_8026E664

/// #it_8026E71C

/// #it_8026E7E0

/// #it_8026E8C4

s32 it_8026E9A4(Item_GObj* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3)
{
    Vec3 p;
    if (mpLib_800524DC(&p, 0, NULL, arg3, -1, -1, arg1->x, arg1->y, arg2->x,
                       arg2->y) == 1)
    {
        *arg2 = p;
        return 1;
    }
    return 0;
}

s32 it_8026EA20(Item_GObj* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, s32* arg4,
                Vec3* arg5)
{
    Vec3 p;
    if (mpLib_800524DC(&p, *arg4, arg5, arg3, -1, -1, arg1->x, arg1->y,
                       arg2->x, arg2->y) == 1)
    {
        *arg2 = p;
        return 1;
    }
    return 0;
}

s32 it_8026EA9C(Item_GObj* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, s32 arg4,
                Vec3* arg5, s32 arg6)
{
    Vec3 p;
    if (mpLib_800524DC(&p, arg4, arg5, arg3, -1, arg6, arg1->x, arg1->y,
                       arg2->x, arg2->y) == 1)
    {
        *arg2 = p;
        return 1;
    }
    return 0;
}

void it_8026EB18(HSD_GObj* arg0, s32 arg1, Vec3* arg2)
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
    HSD_JObjDispAll(GET_JOBJ(arg0), var_r30, HSD_GObj_80390EB8(arg1), 0U);
}

void it_8026EBC8(HSD_GObj* gobj, u16 arg1, u8* arg2)
{
    Item* ip = GET_ITEM(gobj);
    u16 var_r29 = 0;
    u8* var_r27 = arg2;
    while (var_r29 < arg1) {
        HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[*var_r27];
        HSD_JObj* jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A18(jobj);
        }
        var_r29 += 1;
        var_r27 += 1;
    }
}

void it_8026EC54(HSD_GObj* gobj, u16 arg1, u8* arg2)
{
    Item* ip = GET_ITEM(gobj);
    u16 var_r29 = 0;
    u8* var_r27 = arg2;
    while (var_r29 < arg1) {
        HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[*var_r27];
        HSD_JObj* jobj_parent = HSD_JObjGetParent(jobj);
        if (!(HSD_JObjGetFlags(jobj_parent) & 0x10)) {
            it_80272A3C(jobj);
        }
        var_r29 += 1;
        var_r27 += 1;
    }
}

u32 it_8026ECE0(Item_GObj* gobj, u32 arg1)
{
    Item* ip;
    u32 var_r27_2;
    u32 var_r27_3;
    u32 var_r30;
    u8 temp_r3;
    u8 temp_r3_2;
    Item* var_r28_2;
    Item* var_r28_3;

    var_r30 = 0;
    ip = GET_ITEM(gobj);
    if ((enum ItemKind) ip->kind == It_Kind_Unk4) {
        if (((ip->xDAA_flag.b7) && (ip->xDD4_itemVar.it_266F.x18.b7 == 0)) ||
            (ip->xDD4_itemVar.it_266F.x18.b6 &&
             (lbColl_8000A10C(&ip->xDD4_itemVar.it_266F.x1C, arg1, ip->scl) !=
              0)))
        {
            var_r30 = 1;
        }
    } else {
        temp_r3_2 = ip->xDAA_flag.u8;
        if (ip->xDAA_flag.b6) {
            if (ip->xDAA_flag.b2) {
                u32 idx = 0;
                do {
                    if (lbColl_80009F54(&ip->x5D4_hitboxes[idx].hit, arg1,
                                        ip->scl) != 0)
                    {
                        var_r30 = 1;
                    }
                    idx += 1;
                } while (idx < 4U);
            }
            if (!ip->xDCC_flag.b2 && ip->xDAA_flag.b2) {
                if ((s32) ip->xD0C == 0) {
                    u32 idx = 0;
                    while (idx < ip->xAC8_hurtboxNum) {
                        if (lbColl_8000A244(&ip->xACC_itemHurtbox[idx], arg1,
                                            NULL, 0.0f) != 0)
                        {
                            var_r30 = 1;
                        }
                        idx += 1;
                    }
                } else {
                    u32 idx = 0;
                    while (idx < ip->xAC8_hurtboxNum) {
                        if (lbColl_8000A584(&ip->xACC_itemHurtbox[idx],
                                            (u32) ip->xD0C, arg1, NULL,
                                            0.0f) != 0)
                        {
                            var_r30 = 1;
                        }
                        idx += 1;
                    }
                }
            }
        }
        if (ip->xDAA_flag.b7 && ip->xDC8_word.flags.x8 &&
            (lbGx_8001E2F8((Vec4*) &ip->xBCC_unk, &ip->pos, &it_804D5168, arg1,
                           ip->facing_dir) != 0))
        {
            var_r30 = 1;
        }
        if (ip->xDAA_flag.b4 && ip->xDD0_flag.b1 &&
            (lb_800149E0(&ip->xACC_itemHurtbox[1].b_pos.z, arg1) != 0))
        {
            var_r30 = 1;
        }
    }
    return var_r30;
}

static inline void it_8026EC54_inline(HSD_GObj* gobj, Item* ip)
{
    it_8026EC54(gobj, ip->xDD4_itemVar.it_266F.x0,
                ip->xDD4_itemVar.it_266F.x4);
}

static inline void it_8026EBC8_inline(HSD_GObj* gobj, Item* ip)
{
    it_8026EBC8(gobj, ip->xDD4_itemVar.it_266F.x8,
                ip->xDD4_itemVar.it_266F.xC);
}

static inline void it_8026EECC_inline_1(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;
    ip->xDCF_flag.b2 = 1;
    ip->xDCF_flag.b3 = 0;
    it_8026EC54_inline(gobj, ip);
    it_8026EBC8_inline(gobj, ip);
    if (ip->xDCF_flag.b0) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8_inline(gobj, ip);
    it_8026EC54_inline(gobj, ip);
}

static inline void it_8026EECC_inline_2(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;
    ip->xDCF_flag.b2 = 0;
    ip->xDCF_flag.b3 = 0;
    if (ip->xDCF_flag.b0) {
        new_pos = pos;
    }
    it_8026EB18(gobj, arg1, new_pos);
}

static inline void it_8026EECC_inline_3(HSD_GObj* gobj, s32 arg1, Vec3* pos)
{
    Item* ip = gobj->user_data;
    Vec3* new_pos = NULL;
    ip->xDCF_flag.b2 = 1;
    ip->xDCF_flag.b3 = 1;
    it_8026EC54_inline(gobj, ip);
    it_8026EBC8_inline(gobj, ip);
    if (ip->xDCF_flag.b0) {
        new_pos = pos;
    } else {
        new_pos = NULL;
    }
    it_8026EB18(gobj, arg1, new_pos);
    it_8026EBC8_inline(gobj, ip);
    it_8026EC54_inline(gobj, ip);
}

void it_8026EECC(HSD_GObj* gobj, int arg1)
{
    Item* ip = gobj->user_data;
    Vec3 pos;
    if (ip->xDAA_flag.b0) {
        pos.x = pos.y = pos.z = 0.0F;
        if (ip->xDCC_flag.b0) {
            if ((ip->owner == NULL) || (ftLib_80086960(ip->owner) == 0) ||
                (ftLib_800868D4(ip->owner, gobj) != 0))
            {
                {
                    Item* ip = gobj->user_data;
                    ip->xDCF_flag.b0 = 0;
                    if ((ip->owner != NULL) &&
                        (ftLib_80086960(ip->owner) != 0))
                    {
                        if (ftLib_80087074(ip->owner, &pos) != 0) {
                            ip->xDCF_flag.b0 = 1;
                        }
                    } else {
                        pos.x = pos.y = pos.z = 0.0F;
                    }
                }
                // @todo This could just be one big function call.
                {
                    Item* ip = gobj->user_data;
                    switch (Camera_80031060()) {
                    case 1:
                        if (ip->xDCF_flag.b2) {
                            it_8026EECC_inline_1(gobj, arg1, &pos);
                            it_8026EECC_inline_2(gobj, arg1, &pos);
                            it_8026EECC_inline_3(gobj, arg1, &pos);
                        }
                        break;
                    case 0:
                        if (!ip->xDCF_flag.b2) {
                            it_8026EECC_inline_2(gobj, arg1, &pos);
                        }
                        break;
                    }
                }
            }
        } else {
            {
                Item* ip = gobj->user_data;
                switch (Camera_80031060()) {
                case 1:
                    if (ip->xDCF_flag.b2) {
                        it_8026EECC_inline_1(gobj, arg1, &pos);
                        it_8026EECC_inline_2(gobj, arg1, &pos);
                        it_8026EECC_inline_3(gobj, arg1, &pos);
                    }
                    break;
                case 0:
                    if (!ip->xDCF_flag.b2) {
                        it_8026EECC_inline_2(gobj, arg1, &pos);
                    }
                    break;
                }
            }
        }
    }
    if (it_8026ECE0(gobj, (u32) arg1) != 0U) {
        HSD_StateInvalidate(-1);
        HSD_StateInitTev();
        HSD_ClearVtxDesc();
    }
}

void it_8026F3AC(void)
{
    it_8026C75C(&it_804A0E50);
}

/// #it_8026F3D4

/// #it_8026F53C

/// #it_8026F5C8

/// #it_8026F6BC

/// #it_8026F7C8

/// #it_8026F8B4

void it_8026F9A0(void)
{
    it_804D6D18 = 0;
}
