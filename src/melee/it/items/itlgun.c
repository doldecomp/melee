#include "itlgun.h"

#include "itlgunray.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/types.h"

#include <stdbool.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

/* 28E7D8 */ static void it_8028E7D8(Item_GObj*);
/* 28E828 */ static bool itLgun_UnkMotion0_Anim(Item_GObj*);
/* 28E830 */ static void itLgun_UnkMotion0_Phys(Item_GObj*);
/* 28E834 */ static bool itLgun_UnkMotion0_Coll(Item_GObj*);
/* 28E860 */ static void it_8028E860(Item_GObj*);
/* 28E888 */ static bool itLgun_UnkMotion4_Anim(Item_GObj*);
/* 28E890 */ static void itLgun_UnkMotion1_Phys(Item_GObj*);
/* 28E8C0 */ static bool itLgun_UnkMotion4_Coll(Item_GObj*);
/* 28E92C */ static bool itLgun_UnkMotion2_Anim(Item_GObj*);
/* 28E934 */ static void itLgun_UnkMotion2_Phys(Item_GObj*);
/* 28E96C */ static bool itLgun_UnkMotion3_Anim(Item_GObj*);
/* 28E9B4 */ static void itLgun_UnkMotion3_Phys(Item_GObj*);
/* 28EA08 */ static void itLgun_UnkMotion4_Phys(Item_GObj*);
/* 28EB28 */ static bool itLgun_UnkMotion5_Anim(Item_GObj*);
/* 28EB30 */ static void itLgun_UnkMotion5_Phys(Item_GObj*);
/* 28EB34 */ static bool itLgun_UnkMotion5_Coll(Item_GObj*);

ItemStateTable it_803F5CC8[] = {
    { -1, itLgun_UnkMotion0_Anim, itLgun_UnkMotion0_Phys,
      itLgun_UnkMotion0_Coll },
    { -1, itLgun_UnkMotion4_Anim, itLgun_UnkMotion1_Phys,
      itLgun_UnkMotion4_Coll },
    { -1, itLgun_UnkMotion2_Anim, itLgun_UnkMotion2_Phys, NULL },
    { 0, itLgun_UnkMotion3_Anim, itLgun_UnkMotion3_Phys, NULL },
    { +1, itLgun_UnkMotion4_Anim, itLgun_UnkMotion4_Phys,
      itLgun_UnkMotion4_Coll },
    { -1, itLgun_UnkMotion5_Anim, itLgun_UnkMotion5_Phys,
      itLgun_UnkMotion5_Coll },
};

void itLGun_Logic16_Spawned(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItLGunAttr* item_spec_attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xD4C = item_spec_attr->max_ammo;
    ip->xDD4_itemVar.lgun.timer = 0;
    it_8028E860(gobj);
}

void it_8028E774(Item_GObj* gobj, Vec3* arg1)
{
    ItLGunAttr* da = GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    arg1->x = da->pos.x;
    arg1->y = da->pos.y;
    arg1->z = da->pos.z;
}

/// Decrease ammo and fire/spawn lgunray
void it_8028E79C(Item_GObj* gobj, Vec3* pos, f32 facing_dir)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD4C > 0) {
        --ip->xD4C;
    }
    it_80298168(ip->owner, pos, facing_dir);
}

void it_8028E7D8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itLgun_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itLgun_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itLgun_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8028E860);
    return false;
}

void it_8028E860(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itLgun_UnkMotion4_Anim(HSD_GObj* gobj)
{
    return false;
}

void itLgun_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* item_comm_attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, item_comm_attr->x10_fall_speed,
                item_comm_attr->x14_fall_speed_max);
}

bool itLgun_UnkMotion4_Coll(HSD_GObj* gobj)
{
    if (GET_ITEM(gobj)->xD4C != 0) {
        it_8026E15C(gobj, it_8028E7D8);
        return false;
    }
    return it_8026DF34(gobj);
}

void itLGun_Logic16_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itLgun_UnkMotion2_Anim(HSD_GObj* gobj)
{
    return false;
}

void itLgun_UnkMotion2_Phys(HSD_GObj* gobj) {}

void it_8028E938(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.lgun.timer = 40;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool itLgun_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    --ip->xDD4_itemVar.lgun.timer;
    if (ip->xDD4_itemVar.lgun.timer <= 0) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLgun_UnkMotion3_Phys(Item_GObj* gobj) {}

void itLGun_Logic16_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void itLGun_Logic16_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void itLgun_UnkMotion4_Phys(Item_GObj* gobj)
{
    ItemAttr* item_comm_attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, item_comm_attr->x10_fall_speed,
                item_comm_attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itLGun_Logic16_DmgDealt(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool itLGun_Logic16_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim((Item_GObj*) gobj);
    return false;
}

bool itLGun_Logic16_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool itLGun_Logic16_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itLGun_Logic16_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void itLGun_Logic16_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itLgun_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itLgun_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itLgun_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8028E7D8, it_8028E860);
    return false;
}

void itLGun_Logic16_EvtUnk(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
