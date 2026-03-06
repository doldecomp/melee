#include "itevyoshiegg.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "ef/efsync.h"
#include "gm/gm_1BA8.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include "it/items/forward.h"

#include <string.h>

ItemStateTable it_803F6728[] = {
    { -1, itEvyoshiegg_UnkMotion0_Anim, itEvyoshiegg_UnkMotion0_Phys,
      itEvyoshiegg_UnkMotion0_Coll },
    { -1, itEvyoshiegg_UnkMotion3_Anim, itEvyoshiegg_UnkMotion1_Phys,
      itEvyoshiegg_UnkMotion1_Coll },
    { -1, itEvyoshiegg_UnkMotion2_Anim, itEvyoshiegg_UnkMotion2_Phys, NULL },
    { 0, itEvyoshiegg_UnkMotion3_Anim, itEvyoshiegg_UnkMotion3_Phys,
      itEvyoshiegg_UnkMotion3_Coll },
    { -1, itEvyoshiegg_UnkMotion4_Anim, itEvyoshiegg_UnkMotion4_Phys,
      itEvyoshiegg_UnkMotion4_Coll },
    { -1, itEvyoshiegg_UnkMotion5_Anim, itEvyoshiegg_UnkMotion5_Phys,
      itEvyoshiegg_UnkMotion5_Coll },
};

void itEvYoshiEgg_Spawn(Vec3* pos)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    Item* it;
    itEvYoshiEgg_ItemVars* attrs;

    spawn.kind = It_Kind_EvYoshiEgg;
    spawn.prev_pos = *pos;
    spawn.pos = *pos;
    spawn.facing_dir = 1.0f;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        it = GET_ITEM(gobj);
        it_8029B268(gobj);
        it->xDD4_itemVar.evyoshiegg.xDD4 = 0;
    }
}

void itEvYoshiEgg_Logic42_Destroyed(Item_GObj* gobj)
{
    gm_801BEB68(1);
}

void itEvYoshiEgg_Logic42_Spawned(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    it->xDD4_itemVar.evyoshiegg.xDD4 = 0;
    it_8029B268(gobj);
}

void it_8029B1D8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);
    it_8026B390(gobj);
    itResetVelocity(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itEvyoshiegg_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itEvyoshiegg_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8029B268);
    return false;
}

void it_8029B268(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itEvyoshiegg_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itEvyoshiegg_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E32C(gobj, it_8029B1D8);
    return false;
}

void itEvYoshiEgg_Logic42_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itEvyoshiegg_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion2_Phys(Item_GObj* gobj) {}

void itEvYoshiEgg_Logic42_Dropped(Item_GObj* gobj)
{
    itEvYoshiEgg_Logic42_Thrown(gobj);
}

void itEvYoshiEgg_Logic42_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void itEvyoshiegg_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itEvyoshiegg_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DA08(gobj)) {
        return it_3F14_Logic42_DmgDealt(gobj);
    }
    return false;
}

/// #itEvyoshiegg_UnkMotion5_Anim
bool itEvyoshiegg_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.evyoshiegg.xDD8 == 40) {
        gm_801BEB68(1);
    }
    ip->xDD4_itemVar.evyoshiegg.xDD8 -= 1;

    if (ip->xDD4_itemVar.evyoshiegg.xDD8 > 0) {
        return false;
    }

    return true;
}

void itEvyoshiegg_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itEvyoshiegg_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

static inline bool itEvyoshiegg_BounceOff(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 1.5f;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    return false;
}

bool it_3F14_Logic42_DmgDealt(Item_GObj* gobj)
{
    return itEvyoshiegg_BounceOff(gobj);
}

bool it_3F14_Logic42_Clanked(Item_GObj* gobj)
{
    return itEvyoshiegg_BounceOff(gobj);
}

bool it_3F14_Logic42_HitShield(Item_GObj* gobj)
{
    return itEvyoshiegg_BounceOff(gobj);
}

bool it_3F14_Logic42_Reflected(Item_GObj* gobj)
{
    return itEvyoshiegg_BounceOff(gobj);
}

static inline void dmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), JOBJ_HIDDEN);
    it_802756D0(gobj);
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->xDD4_itemVar.evyoshiegg.xDD4 = 1;
    ip->xDD4_itemVar.evyoshiegg.xDD8 = 60;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itEvYoshiEgg_Logic42_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itEvYoshiEgg_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 val;
    f32* unused;

    if (ip->xDD4_itemVar.evyoshiegg.xDD4 != 0) {
        return false;
    }

    if (ip->xC9C < attrs->x0) {
        return false;
    }

    val = 1.5f;
    efSync_Spawn(1231, gobj, &ip->pos, &val);
    efSync_Spawn(1231, gobj, &ip->pos, &val);
    Item_8026AE84(ip, 244, 0x7F, 0x40);
    dmgReceived(gobj);
    return false;
}

void itEvYoshiEgg_Logic42_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itEvyoshiegg_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itEvyoshiegg_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8029B1D8, it_8029B268);
    return false;
}

void itEvYoshiEgg_Logic42_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
