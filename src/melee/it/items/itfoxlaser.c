#include "itfoxlaser.h"

#include <placeholder.h>

#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/types.h"

#include "lb/forward.h"

#include <common_structs.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/db/db.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/it/items/inlines.h>
#include <melee/lb/lbrefract.h>
#include <melee/lb/lbvector.h>
#include <MSL/math.h>

ItemStateTable it_803F67D0[] = {
    { 0, itFoxlaser_UnkMotion1_Anim, itFoxlaser_UnkMotion1_Phys,
      itFoxlaser_UnkMotion1_Coll },
    { 1, itFoxlaser_UnkMotion1_Anim, itFoxlaser_UnkMotion1_Phys,
      itFoxlaser_UnkMotion1_Coll },
};

inline void* getFoxLaser(Item* item)
{
    return &item->xDD4_itemVar;
}

bool it_8029C4D4(Item_GObj* item_gobj, CollData* arg1)
{
    Item* item = GET_ITEM(item_gobj);
    return it_8026E9A4(item_gobj, &item->xDD4_itemVar.foxlaser.pos, &item->pos,
                       0);
}

static inline void normalizeAngle(f32* angle)
{
    while (*angle < 0.0F) {
        *angle += M_TAU;
    }
    while (*angle > M_TAU) {
        *angle -= M_TAU;
    }
}

void it_8029C504(HSD_GObj* parent, Vec3* pos, enum_t msid, int kind, f32 angle,
                 f32 speed)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;
    bool right_facing;

    normalizeAngle(&angle);
    spawn.kind = kind;
    Item_InitRaySpawnPosition(&spawn, parent, pos);
    right_facing = true;
    if (!(angle < M_PI / 2) && !(angle > M_PI * 3 / 2)) {
        right_facing = false;
    }
    Item_InitRaySpawnFields(&spawn, parent, right_facing ? +1.0F : -1.0F);
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* item = GET_ITEM(item_gobj);
        FoxLaserAttr* attr = item->xC4_article_data->x4_specialAttributes;
        Item_80268E5C(item_gobj, msid, ITEM_ANIM_UPDATE);
        it_80275158(item_gobj, attr->lifetime);
        item->xDD4_itemVar.foxlaser.scale = 0.0F;
        item->xDD4_itemVar.foxlaser.angle = angle;
        item->xDD4_itemVar.foxlaser.speed = speed;
        item->xDD4_itemVar.foxlaser.pos = spawn.pos;
        db_80225DD8(item_gobj, parent);
    }
}

void it_8029C6A4(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec, int kind)
{
    it_8029C504(parent, vec, 0, kind, angle, vel);
}

void it_8029C6CC(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec, int kind)
{
    it_8029C504(parent, vec, 1, kind, angle, vel);
}

static inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return +x;
    }
}

bool itFoxlaser_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    Item* ip = GET_ITEM(item_gobj);
    FoxLaserAttr* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(item_gobj);

    return Item_UpdateRayAnimation(item_gobj, ip, jobj, &attr->scale, 11.25F);
}

void itFoxlaser_UnkMotion1_Phys(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->xDD4_itemVar.foxlaser.pos = item->pos;
}

bool itFoxlaser_UnkMotion1_Coll(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Vec3 pos = item->pos;
    PAD_STACK(4);
    if (it_8029C4D4(item_gobj, NULL)) {
        it_80275158(item_gobj, 1.0F);
        item->pos = pos;
    }
    return false;
}

bool itFoxLaser_Logic94_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itFoxLaser_Logic94_Reflected(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    if (item->facing_dir != item->xC68) {
        item->facing_dir = item->xC68;
        HSD_JObjSetRotationY(jobj, (M_PI / 2) * item->facing_dir);
    }
    Item_ResetRayAfterReflection(item, jobj);
    return false;
}

bool itFoxLaser_Logic94_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itFoxLaser_Logic94_ShieldBounced(Item_GObj* item_gobj)
{
    PAD_STACK(4);
    return Item_BounceRayOffShield(item_gobj);
}

bool itFoxLaser_Logic94_HitShield(Item_GObj* arg0)
{
    return true;
}

void itFoxLaser_Logic94_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref)
{
    it_8026B894(item_gobj, ref);
}
