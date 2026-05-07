#include "itfreeze.h"

#include "placeholder.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include "it/items/forward.h"

#include "it/items/itwhitebea.h"

#include <baselib/jobj.h>
#include <MSL/math.h>

ItemStateTable it_803F5D28[] = { {
                                     0,
                                     itFreeze_UnkMotion0_Anim,
                                     itFreeze_UnkMotion0_Phys,
                                     itFreeze_UnkMotion0_Coll,
                                 },
                                 {
                                     0,
                                     itFreeze_UnkMotion3_Anim,
                                     itFreeze_UnkMotion1_Phys,
                                     itFreeze_UnkMotion1_Coll,
                                 },
                                 {
                                     -1,
                                     itFreeze_UnkMotion2_Anim,
                                     NULL,
                                     NULL,
                                 },
                                 {
                                     1,
                                     itFreeze_UnkMotion3_Anim,
                                     itFreeze_UnkMotion3_Phys,
                                     itFreeze_UnkMotion3_Coll,
                                 },
                                 {
                                     0,
                                     itFreeze_UnkMotion4_Anim,
                                     itFreeze_UnkMotion4_Phys,
                                     itFreeze_UnkMotion4_Coll,
                                 },
                                 {
                                     0,
                                     itFreeze_UnkMotion5_Anim,
                                     itFreeze_UnkMotion5_Phys,
                                     itFreeze_UnkMotion5_Coll,
                                 } };

Item_GObj* it_8028EB88(Item_GObj* ref_gobj, Vec3* pos, f32 facing_dir,
                       f32 decel)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    Item* ip;

    if (ref_gobj != NULL) {
        ip = GET_ITEM(ref_gobj);
    }
    spawn.kind = It_Kind_Freeze;
    spawn.prev_pos = *pos;
    if (ip != NULL) {
        spawn.pos = ip->pos;
    } else {
        spawn.pos = spawn.prev_pos;
    }
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        it_3F14_Logic17_Spawned(gobj);
        it_8028F434(gobj, decel, ref_gobj);
        return gobj;
    }
    return NULL;
}

void it_8028EC98(Item_GObj* gobj, f32 vel)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.freeze.x10 = vel;
    it_80275158(gobj, (f32) it_804D6D28->x30_lifetime);
}

void it_8028ECE0(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.freeze.unk_1C = NULL;
}

Item* it_8028ECF0(Item_GObj* gobj, Vec3* v)
{
    Item* ip = GET_ITEM(gobj);
    v->x = ip->pos.x;
    v->y = ip->pos.y;
    v->z = ip->pos.z;
    return ip;
}

void itFreeze_Logic17_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.freeze.unk_1C != NULL) {
        it_802E37A4(ip->xDD4_itemVar.freeze.unk_1C);
        ip->xDD4_itemVar.freeze.unk_1C = NULL;
    }
}

void it_3F14_Logic17_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->pos.x > 0.0f) {
        ip->facing_dir = -1.0f;
    } else {
        ip->facing_dir = 1.0f;
    }
    ip->xD5C = 0;
    ip->xDD4_itemVar.freeze.x0 = 0.0f;
    ip->xDD4_itemVar.freeze.x4.x = 0.0f;
    ip->xDD4_itemVar.freeze.x4.y = 1.0f;
    ip->xDD4_itemVar.freeze.x4.z = 0.0f;
    ip->xDD4_itemVar.freeze.unk_1C = NULL;
    it_8028F1D8(gobj);
}

void it_8028EDBC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnkAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    if (ip->ground_or_air != GA_Air) {
        if (ABS(ip->xDD4_itemVar.freeze.x4.x) > 0.1f) {
            if (ip->xDD4_itemVar.freeze.x0 == 0.0f) {
                if (ip->xDD4_itemVar.freeze.x4.x > 0.0f) {
                    ip->facing_dir = 1.0f;
                } else {
                    ip->facing_dir = -1.0f;
                }
                ip->xDD4_itemVar.freeze.x0 = attrs->x4_float * ip->facing_dir;
            } else {
                ip->xDD4_itemVar.freeze.x0 =
                    (ip->xDD4_itemVar.freeze.x4.x * attrs->xC) +
                    ip->xDD4_itemVar.freeze.x0;
            }
        } else {
            if (ABS(ip->xDD4_itemVar.freeze.x0) < attrs->x4_float) {
                ip->xDD4_itemVar.freeze.x0 = attrs->x4_float * ip->facing_dir;
            } else if (ip->xDD4_itemVar.freeze.x0 > 0.0f) {
                ip->xDD4_itemVar.freeze.x0 -= attrs->x10;
            } else {
                ip->xDD4_itemVar.freeze.x0 += attrs->x10;
            }
        }
        if (ip->xDD4_itemVar.freeze.x0 > attrs->x8) {
            ip->xDD4_itemVar.freeze.x0 = attrs->x8;
        } else if (ip->xDD4_itemVar.freeze.x0 < -attrs->x8) {
            ip->xDD4_itemVar.freeze.x0 = -attrs->x8;
        }
        if ((ip->xDD4_itemVar.freeze.x0 > 0.0f && ip->facing_dir < 0.0f) ||
            (ip->xDD4_itemVar.freeze.x0 < 0.0f && ip->facing_dir > 0.0f))
        {
            ip->facing_dir *= -1.0f;
        }
        ip->x40_vel.x =
            ip->xDD4_itemVar.freeze.x0 * ip->xDD4_itemVar.freeze.x4.y;
    }
}

void it_8028EF34(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.x = ip->xDD4_itemVar.freeze.x0;
    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8028EDBC(gobj);
}

bool itFreeze_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    CollData* cd = &ip->x378_itemColl;

    it_8026D62C(gobj, it_8028F1D8);
    if (ip->ground_or_air != GA_Air) {
        if (cd->env_flags & 0x18000) {
            it_80276408(gobj, cd, &ip->xDD4_itemVar.freeze.x4);
        } else {
            ip->xDD4_itemVar.freeze.x4.x = 0.0f;
        }
        {
            s32 env = cd->env_flags;
            if ((env & 0x3F) || (env & 0xFC0)) {
                ip->facing_dir = -ip->facing_dir;
                ip->xDD4_itemVar.freeze.x0 = -ip->xDD4_itemVar.freeze.x0;
                ip->x40_vel.x =
                    ip->xDD4_itemVar.freeze.x0 * ip->xDD4_itemVar.freeze.x4.y;
            }
        }
        if (ip->facing_dir == -1.0f) {
            HSD_JObjSetRotationZ(jobj, it_8027649C(gobj));
        } else {
            HSD_JObjSetRotationZ(jobj, -1.0f * it_8027649C(gobj));
        }
    }
    return false;
}

void it_8028F1D8(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFreeze_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    CollData* cd = &it->x378_itemColl;

    it_8026E414(gobj, it_8028EF34);
    if (it->ground_or_air != GA_Air && (cd->env_flags & Collide_FloorMask)) {
        it_80276408(gobj, cd, &it->xDD4_itemVar.freeze.x4);
    }
    return false;
}

void itFreeze_Logic17_PickedUp(Item_GObj* gobj)
{
    Item* item = gobj->user_data;
    Item_GObj* linked;

    if ((linked = item->xDD4_itemVar.freeze.unk_1C) != NULL) {
        it_802E37A4(linked);
        item->xDD4_itemVar.freeze.unk_1C = NULL;
    }

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_Logic17_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
}

void itFreeze_Logic17_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void itFreeze_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip;
    ItemAttr* it_attr;

    ip = gobj->user_data;
    it_attr = ip->xCC_item_attr;
    it_80272860(gobj, it_attr->x10_fall_speed, it_attr->x14_fall_speed_max);
}

bool itFreeze_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) != 0) {
        return 1;
    }
    return 0;
}

bool itFreeze_Logic17_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itFreeze_Logic17_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itFreeze_Logic17_DmgReceived(Item_GObj* arg0)
{
    return true;
}

void it_8028F434(Item_GObj* gobj, f32 vel, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    if (vel < 0.0f) {
        vel = -vel;
    }
    ip->xDD4_itemVar.freeze.x14 = vel;
    ip->xDD4_itemVar.freeze.unk_1C = ref_gobj;
    it_8026B390(gobj);
    it_802762B0(ip);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 decel;
    f32 abs_decel;
    f32 vel;
    f32 abs_vel;

    {
        f32 x10 = ip->xDD4_itemVar.freeze.x10;
        if (x10) {
            ip->x40_vel.x = x10;
            ip->xDD4_itemVar.freeze.x10 = 0.0f * 0.0f;
        }
    }

    decel = ip->xDD4_itemVar.freeze.x14;
    abs_decel = ABS(decel);

    vel = ip->x40_vel.x;
    abs_vel = ABS(vel);

    if (abs_vel < abs_decel) {
        ip->x40_vel.x = 0.0f;
        return;
    }

    if (vel > 0.0f) {
        if (ip->xDD4_itemVar.freeze.x14 < 0.0f) {
            decel = -decel;
        }
        ip->x40_vel.x -= decel;
    } else {
        if (decel < 0.0f) {
            decel = -decel;
        }
        ip->x40_vel.x += decel;
    }
}

static inline void itFreeze_ClearLinkedItem(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_GObj* linked = ip->xDD4_itemVar.freeze.unk_1C;
    if (linked != NULL) {
        it_802E37A4(linked);
        ip->xDD4_itemVar.freeze.unk_1C = NULL;
    }
}

static inline void itFreeze_ResetToMotion0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.freeze.x0;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    CollData* cd = &ip->x378_itemColl;
    PAD_STACK(8);

    it_8026D62C(gobj, it_8028F1D8);
    if (ip->ground_or_air == GA_Air) {
        itFreeze_ClearLinkedItem(gobj);
    } else {
        s32 env = cd->env_flags;
        if ((env & 0x3F) || (env & 0xFC0)) {
            it_8028F7C8(gobj);
            itFreeze_ClearLinkedItem(gobj);
            return false;
        }
        if (ip->xDD4_itemVar.freeze.unk_1C == NULL) {
            itFreeze_ResetToMotion0(gobj);
            return false;
        }
        if (ip->facing_dir == -1.0f) {
            HSD_JObjSetRotationZ(jobj, it_8027649C(gobj));
        } else {
            HSD_JObjSetRotationZ(jobj, -1.0f * it_8027649C(gobj));
        }
    }
    return false;
}

void it_8028F7C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_8026B390(gobj);
    ip->xDD4_itemVar.freeze.x18 = 90;
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itFreeze_UnkMotion5_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    it_8026D62C(gobj, it_8028F1D8);
    if (ip->xDD4_itemVar.freeze.x18 <= 0) {
        Item* ip2 = GET_ITEM(gobj);
        ip2->x40_vel.x = ip2->xDD4_itemVar.freeze.x0;
        ip2->x40_vel.z = 0.0f;
        ip2->x40_vel.y = 0.0f;
        it_8026B390(gobj);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    } else {
        ip->xDD4_itemVar.freeze.x18--;
    }
    return false;
}

void itFreeze_Logic17_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_8028F8E4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;
    ip->xDCC_flag.b3 = true;
    it_8026B390(gobj);
    ip->x378_itemColl.cur_pos = ip->pos;
    pos = ip->pos;
    it_80276100(gobj, &pos);
}

void it_8028F968(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80273454(gobj);
    ip->xDCC_flag.b3 = 0;
    it_8026B3A8(gobj);
}

void it_8028F9B8(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}
