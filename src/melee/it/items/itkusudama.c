#include "itkusudama.h"

#include <placeholder.h>
#include <platform.h>

#include "dolphin/mtx.h"
#include "ef/efsync.h"
#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "sysdolphin/baselib/random.h"

HSD_GObj* it_802896CC(Vec3* arg0)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = It_Kind_Kusudama;
    spawn.prev_pos = *arg0;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0f;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B5C(&spawn);
    if (gobj != NULL) {
        it_8028A190(gobj);
    }
    return gobj;
}

void it_3F14_Logic4_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCE_flag.b7 = 0;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDB4_itcmd_var2 = 0;
    ip->xDD4_itemVar.kusudama.x0 = 0;
    it_8028A3CC(gobj);
}

void it_802897C8(Item_GObj* gobj, f32 angle)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 f;
    f32 rotx;

    if (angle > 3.1415927f) {
        angle -= 6.2831855f;
    }
    if (ip->facing_dir == -1.0f) {
        angle *= -1.0f;
    }
    rotx = HSD_JObjGetRotationX(jobj);
    f = rotx;
    f -= angle;
    if (f < 0.0f) {
        f = -f;
    }
    if (f > 0.17453292f) {
        f32 temp = 0.08726646f;
        if (rotx < angle) {
            angle = rotx + temp;
        } else {
            angle = rotx - temp;
        }
    }
    HSD_JObjSetRotationX(jobj, angle);
}

void it_80289910(Item_GObj* gobj, f32 angle)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    if (angle > 3.1415927f) {
        angle -= 6.2831855f;
    }
    if (ip->facing_dir == -1.0f) {
        angle *= -1.0f;
    }
    HSD_JObjSetRotationX(jobj, angle);
}

void it_80289A00(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);
    f32 roty;
    itKusudamaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    roty = HSD_JObjGetRotationY(jobj);
    if (ip->facing_dir == 1.0f) {
        if (roty > 1.5707964f + attrs->x28) {
            roty -= attrs->x28;
        } else {
            roty = 1.5707964f;
        }
    } else {
        if (roty < -1.5707964f - attrs->x28) {
            roty += attrs->x28;
        } else {
            roty = -1.5707964f;
        }
    }
    HSD_JObjSetRotationY(jobj, roty);
}

void it_80289B50(Item_GObj* gobj, s32 arg1)
{
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (it_8028A114(gobj, attr->x4, attr->x0, attr->x8, attr->xC)) {
        if (arg1 != 0) {
            Item_8026AE84(ip, 0x126, 0x7F, 0x40);
        }
        it_8028A544(gobj);
    } else {
        it_8028AC74(gobj);
    }
}

static inline void it_80289BE8_inline(Item_GObj* gobj, f32 vel_scale,
                                      Vec3* pos, Vec3* vel)
{
    Item* ip = GET_ITEM(gobj);
    *pos = ip->pos;
    pos->y -= 5.0f;
    vel->x = (vel_scale * HSD_Randf()) - (vel_scale * 0.5f);
    vel->y = ((vel_scale * 0.5f) * HSD_Randf()) - (vel_scale * 0.25f);
    vel->z = 0.0f;
}

static inline ItemKind it_80289BE8_spawn(Item_GObj* gobj, ItemKind kind,
                                         f32 vel_scale, Vec3* pos, Vec3* vel)
{
    Item_GObj* spawned_gobj;

    it_80289BE8_inline(gobj, vel_scale, pos, vel);

    spawned_gobj = it_8026F5C8(gobj, kind, pos);
    if (spawned_gobj) {
        it_8026F53C(spawned_gobj, vel, true);
        it_80274ED8();
        return kind;
    }
    return -1;
}

void it_80289BE8(Item_GObj* gobj, s32 arg1, s32 arg2, s32 arg3)
{
    ItemKind spawned[15];
    Vec3 pos;
    Vec3 vel;
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 count;
    int i;
    PAD_STACK(8);

    pos = ip->pos;
    pos.y -= 5.0f;
    vel.x = vel.y = vel.z = 0.0f;

    if (it_8026F8B4(gobj, &pos, &vel, false)) {
        return;
    }

    it_80289BE8_inline(gobj, 0.1f, &pos, &vel);
    pos.y -= 5.0f;

    if (it_8026F6BC(gobj, &pos, &vel, true) != NULL) {
        return;
    }

    if (!it_8026D324(It_Kind_Foods)) {
        arg2 = 0;
    }

    for (i = 0; i < 15; i++) {
        spawned[i] = -1;
    }

    i = HSD_Randi(arg1 + arg2 + arg3);
    if (i < arg1) {
        ItemKind prev_kind;
        ItemKind kind = attr->x10;
        count = attr->x14;
        if (kind == It_Kind_M_Ball && it_8026C704() == true) {
            i = HSD_Randi(arg2 + arg3);
            goto food_or_random;
        }
        if (!it_8026D324(kind)) {
            i = HSD_Randi(arg2 + arg3);
            goto food_or_random;
        }
        for (i = 0; i < count; i++) {
            if (kind == It_Kind_M_Ball && it_8026C704() == true) {
                break;
            }
            it_80289BE8_spawn(gobj, kind, 1.4f, &pos, &vel);
            spawned[i] = kind;
        }
        for (; i < count; i++) {
            ItemKind rand_kind = it_8026F3AC();
            Vec3 vel;
            Vec3 pos;
            PAD_STACK(8);
            if (rand_kind != -1) {
                prev_kind =
                    it_80289BE8_spawn(gobj, rand_kind, 1.2f, &pos, &vel);
            }
            spawned[i] = prev_kind;
        }
    } else {
        i -= arg1;
    food_or_random:
        if (i < arg2) {
            count = HSD_Randi(5) + 10;
            for (i = 0; i < count; i++) {
                it_80289BE8_spawn(gobj, It_Kind_Foods, 1.8f, &pos, &vel);
                spawned[i] = It_Kind_Foods;
            }
        } else {
            ItemKind prev_kind;
            Vec3 vel;
            Vec3 pos;
            count = HSD_Randi(2) + 3;
            for (i = 0; i < count; i++) {
                ItemKind rand_kind = it_8026F3AC();
                if (rand_kind != -1) {
                    prev_kind =
                        it_80289BE8_spawn(gobj, rand_kind, 1.2f, &pos, &vel);
                }
                spawned[i] = prev_kind;
            }
        }
    }
    if (ftLib_80086960(ip->owner)) {
        ftLib_800874CC(ip->owner, spawned, i);
    }
}

bool it_8028A114(Item_GObj* gobj, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 sum1 = arg1 + arg2;
    s32 sum2 = arg3 + sum1;
    s32 rand = HSD_Randi(arg4 + sum2);
    if (rand < arg1) {
        return true;
    }
    if (rand < sum1) {
        return true;
    }
    if (rand < sum2) {
        return true;
    }
    return false;
}

static inline void it_8028A190_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 rotx = 1.5707964f;
    HSD_JObj* jobj = gobj->hsd_obj;
    if (ip->facing_dir == -1.0f) {
        rotx *= -1.0f;
    }
    HSD_JObjSetRotationX(jobj, rotx);
}

void it_8028A190(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    itResetVelocity(ip);
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8028A190_inline(gobj);
}

bool itKusudama_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_802897C8(gobj, 1.5707964f);
    return false;
}

void itKusudama_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8028A3CC);
    return false;
}

bool itKusudama_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDB4_itcmd_var2 == 1) {
        ip->xDB4_itcmd_var2 = 2;
        if (HSD_Randi(2) != 0) {
            Item_8026AE84(ip, 0x127, 0x7F, 0x40);
        } else {
            Item_8026AE84(ip, 0x128, 0x7F, 0x40);
        }
    }
    if (ip->xDB0_itcmd_var1 != 0) {
        it_8028AD44(gobj);
    }
    it_802897C8(gobj, 0.0f);
    it_80289A00(gobj);
    return false;
}

void itKusudama_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

void it_8028A3CC(Item_GObj* gobj)
{
    Item* _ip = GET_ITEM(gobj); // NOTE: unused
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    it_8028A190_inline(gobj);
}

bool itKusudama_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_802897C8(gobj, 1.5707964f);
    return false;
}

void itKusudama_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itKusudama_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8028A190);
    return false;
}

static inline void it_8028A544_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 roty;
    if (ip->facing_dir == 1.0f) {
        roty = 4.694936f;
    } else {
        roty = -4.694936f;
    }
    HSD_JObjSetRotationY(jobj, roty);
}

void it_8028A544(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    ip->x40_vel.z = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = attr->x18;
    ip->xDD4_itemVar.kusudama.x4 = attr->x1C;
    ip->xDD4_itemVar.kusudama.x0 = true;
    it_802762BC(ip);
    it_80275444(gobj);
    it_8026BB20(gobj);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    it_8028A544_inline(gobj);
}

static inline void itKusudama_UnkMotion3_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 rot_y;

    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDD4_itemVar.kusudama.x4 = 0x5A;
    ip->xDD1_flag.b1 = 1;
    it_8026B3A8(gobj);
    rot_y = HSD_JObjGetRotationY(jobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    HSD_JObjSetRotationY(jobj, rot_y);
}

bool itKusudama_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(12);

    ip->xDD4_itemVar.kusudama.x4 -= 1;
    if (ip->xDD4_itemVar.kusudama.x4 <= 0) {
        itKusudama_UnkMotion3_inline(gobj);
    }
    it_802897C8(gobj, 0.0f);
    it_80289A00(gobj);
    return false;
}

void itKusudama_UnkMotion3_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    CollData* coll = &ip->x378_itemColl;
    PAD_STACK(8);

    it_8026DA08(gobj);
    if (coll->env_flags & 0x6000) {
        itKusudama_UnkMotion3_inline(gobj);
    }
    return false;
}

void it_3F14_Logic4_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itKusudama_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itKusudama_UnkMotion4_Phys(Item_GObj* gobj) {}

void it_3F14_Logic4_Thrown(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

bool itKusudama_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

void itKusudama_UnkMotion6_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

static inline void itKusudama_UnkMotion5_Coll_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (it_8028A114(gobj, attr->x4, attr->x0, attr->x8, attr->xC)) {
        Item_8026AE84(ip, 0x126, 0x7F, 0x40);
        it_8028A544(gobj);
    } else {
        it_8028AC74(gobj);
    }
}

bool itKusudama_UnkMotion5_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_8026DA08(gobj)) {
        itKusudama_UnkMotion5_Coll_inline(gobj);
    } else if (it_802763E0(gobj)) {
        if (ip->x40_vel.y > 0.0f) {
            ip->x40_vel.y = 0.0f;
        }
    } else if (it_80276308(gobj)) {
        itKusudama_UnkMotion5_Coll_inline(gobj);
    }
    return false;
}

void it_3F14_Logic4_Dropped(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

static inline void itKusudama_UnkMotion6_Coll_inline2(Item_GObj* gobj)
{
    it_80289910(gobj, 1.5707964f);
}

static inline void itKusudama_UnkMotion6_Coll_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    itKusudama_UnkMotion6_Coll_inline2(gobj);
}

bool itKusudama_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    if (it_8026DA08(gobj)) {
        f32 vel_y = ip->x40_vel.y;
        if (vel_y < 0.0f) {
            vel_y = -vel_y;
        }
        if (vel_y > attr->x2C) {
            itKusudama_UnkMotion5_Coll_inline(gobj);
        } else {
            it_802762B0(ip);
            itKusudama_UnkMotion6_Coll_inline(gobj);
        }
    }
    return false;
}

void it_8028AC74(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(4);
    it_80272A3C(jobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->xDCF_flag.b2 = true;
    ip->xDD4_itemVar.kusudama.x0 = true;
    ip->xDD4_itemVar.kusudama.x4 = 0x28;
    it_80275444(gobj);
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itKusudama_UnkMotion7_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itKusudama_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

void it_8028AD44(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);
    Item_8026AE84(ip, 0xF8, 0x7F, 0x40);
    it_802756D0(gobj);
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->xDCF_flag.b2 = true;
    ip->xDD4_itemVar.kusudama.x0 = true;
    ip->xDD4_itemVar.kusudama.x4 = 0x55;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}

static inline void itKusudama_UnkMotion8_Anim_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    efSync_Spawn(0x433, gobj, ip->xBBC_dynamicBoneTable->bones[3]);
    efSync_Spawn(0x433, gobj, ip->xBBC_dynamicBoneTable->bones[5]);
}

bool itKusudama_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDAC_itcmd_var0 != 0) {
        ip->xDAC_itcmd_var0 = 0;
        it_80289BE8(gobj, attrs->x4, attrs->x0, attrs->x8);
        itKusudama_UnkMotion8_Anim_inline(gobj);
    }
    ip->xDD4_itemVar.kusudama.x4 -= 1;
    if (ip->xDD4_itemVar.kusudama.x4 > 0) {
        return false;
    }
    return true;
}

void itKusudama_UnkMotion8_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion8_Coll(Item_GObj* gobj)
{
    return false;
}

static inline void it_3F14_Logic4_DmgDealt_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (it_8028A114(gobj, attr->x4, attr->x0, attr->x8, attr->xC)) {
        it_8028A544(gobj);
    } else {
        it_8028AC74(gobj);
    }
}

bool it_3F14_Logic4_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (!ip->xDD4_itemVar.kusudama.x0) {
        it_3F14_Logic4_DmgDealt_inline(gobj);
    }
    return false;
}

static inline void it_3F14_Logic4_Clanked_inline(Item_GObj* gobj)
{
    it_80289B50(gobj, 0);
}

bool it_3F14_Logic4_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (!ip->xDD4_itemVar.kusudama.x0) {
        it_3F14_Logic4_Clanked_inline(gobj);
    }
    return false;
}

bool it_3F14_Logic4_HitShield(Item_GObj* gobj)
{
    return it_3F14_Logic4_Clanked(gobj);
}

bool it_3F14_Logic4_Reflected(Item_GObj* gobj)
{
    return it_3F14_Logic4_Clanked(gobj);
}

bool it_3F14_Logic4_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKusudamaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (!ip->xDD4_itemVar.kusudama.x0) {
        if (ip->xC9C >= attr->x20) {
            it_3F14_Logic4_DmgDealt_inline(gobj);
        }
    }
    return false;
}

void it_3F14_Logic4_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
