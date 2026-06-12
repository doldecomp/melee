#include "it/itdrop.h"

#include "inlines.h"

#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/it_3F14.h"
#include "it/item.h"
#include "it/items/it_2E5A.h"
#include "it/itspawn.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

ItemKind it_8026F3AC(void)
{
    return it_8026C75C(&it_804A0E50);
}

static inline bool it_8026F3D4_check_kind(Item* ip, ItemKind it_kind)
{
    bool ret = false;
    if (it_kind == -1) {
        if (ip == NULL) {
        }
    }
    if ((it_kind >= It_Kind_L_Gun_Ray)) {
        ret = true;
    }
    return ret;
}

bool it_8026F3D4(Item_GObj* item_gobj, struct it_8026F3D4_arg1_t* arg1,
                 s32 num, s32 arg3)
{
    u8 _padA[0x4C];
    volatile s32 cnt2;
    u8 _padB[0x30];
    ItemKind sp30[8];
    Vec3 sp24;
    u8 _padC[4];
    ItemKind it_kind;
    int new_var;
    Item* item;
    Item_GObj* spawned_item_gobj;
    s32 cnt;
    bool chk1;
    float zero;
    static const f32 zero_init = 0.0f;

    spawned_item_gobj = NULL;
    chk1 = false;
    it_kind = -1;
    new_var = arg3 & 1;
    item = GET_ITEM(item_gobj);
    cnt2 = 0;
    zero = *(volatile f32*) &zero_init;
    for (cnt = 0; cnt < num; cnt++) {
        if ((new_var == 0) || (it_kind == -1)) {
            it_kind = it_8026C75C(&it_804A0E50);
        }
        if ((it_kind == -1) || (it_kind >= It_Kind_L_Gun_Ray) ||
            ((it_kind == It_Kind_M_Ball) && it_8026C704()))
        {
            chk1 |= it_8026F3D4_check_kind(item, it_kind);
            break;
        }
        spawned_item_gobj = it_8026F5C8(item_gobj, it_kind, &item->pos);
        if (spawned_item_gobj != NULL) {
            sp24.x = sp24.y = sp24.z = zero;
            it_8026F53C(spawned_item_gobj, &sp24, 0);
            chk1 = false;
            it_80274ED8();
            sp30[cnt2] = it_kind;
            cnt2++;
        }
    }
    if (ftLib_80086960(item->owner)) {
        s32 n = cnt2;
        if (n != 0) {
            ftLib_800874CC(item->owner, &sp30, n);
        }
    }
    if (arg1 != NULL) {
        arg1->x0 = chk1;
        arg1->x4 = it_kind;
        arg1->x8 = spawned_item_gobj;
    }
    return chk1;
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
        spawn.x4_parent_gobj2 = item_gobj;
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
    PAD_STACK(88);

    if (Item_804A0C64.x2C >= Item_804A0C64.x30) {
        return NULL;
    }
    if (HSD_Randi(it_804D6D28->x124) != 0) {
        return NULL;
    }
    spawned_item_gobj =
        it_8026F5C8(item_gobj, it_8026C65C(&it_804A0E60), arg1);
    if (spawned_item_gobj != NULL) {
        spawned_item = GET_ITEM(spawned_item_gobj);
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
        spawned_item = GET_ITEM(spawned_item_gobj);
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
