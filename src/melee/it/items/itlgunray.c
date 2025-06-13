#include <placeholder.h>

#include "itlgunray.h"

#include "db/db.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/items/itfoxlaser.h"
#include "it/types.h"
#include "lb/lbvector.h"

#include <math.h>
#include <stdbool.h>
#include <baselib/gobj.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>

/* 298300 */ static bool it_80298300(Item_GObj*);
/* 2983AC */ static void it_802982AC(Item_GObj*, Item_GObj*, Article*);
/* 2985D8 */ static void it_802985D8(Item_GObj*);
/* 2985F8 */ static bool it_802985F8(Item_GObj*);

static float const scale = 1e-3f;

ItemStateTable it_803F64F8[] = {
    { 0, it_80298300, it_802985D8, it_802985F8 },
};

void it_80298168(HSD_GObj* owner_gobj, Vec3* pos, f32 facing_dir)
{
    SpawnItem spawn;
    spawn.kind = It_Kind_L_Gun_Ray;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(owner_gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    {
        Item_GObj* gobj = Item_80268B18(&spawn);
        if (gobj != NULL) {
            Item* ip = GET_ITEM(gobj);
            Article* article = ip->xC4_article_data;
            ItLGunRayAttr* item_spec_attr = article->x4_specialAttributes;
            it_802982AC(gobj, owner_gobj, article);
            ip->xDD4_itemVar.lgunray.scale = 0.0f;
            ip->xDD4_itemVar.lgunray.angle =
                ip->facing_dir == +1 ? 0 : (float) M_PI;
            ip->xDD4_itemVar.lgunray.speed = item_spec_attr->speed;
            ip->xDD4_itemVar.lgunray.pos = spawn.pos;
            ip->x40_vel.x = item_spec_attr->speed * ip->facing_dir;
            db_80225DD8(gobj, owner_gobj);
        }
    }
}

void it_802982AC(Item_GObj* gobj, Item_GObj* owner_gobj, Article* article)
{
    ItLGunRayAttr* da = GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    it_80275158(gobj, da->lifetime);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

int it_80298300(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItLGunRayAttr* item_spec_attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);

    ip->x40_vel.x =
        ip->xDD4_itemVar.lgunray.speed * cosf(ip->xDD4_itemVar.lgunray.angle);
    ip->x40_vel.y =
        ip->xDD4_itemVar.lgunray.speed * sinf(ip->xDD4_itemVar.lgunray.angle);
    ip->x40_vel.z = 0.0f;
    ip->facing_dir = ip->x40_vel.x > 0.0f ? +1.0F : -1.0F;

    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);

    HSD_JObjSetRotationX(jobj,
                         M_PI + atan2f(ip->x40_vel.y, ip->facing_dir == 1.0f
                                                          ? -ip->x40_vel.x
                                                          : +ip->x40_vel.x));

    ip->xDD4_itemVar.lgunray.scale +=
        ABS(ip->xDD4_itemVar.lgunray.speed) / 7.0f;
    if (ip->xDD4_itemVar.lgunray.scale > item_spec_attr->max_scale) {
        ip->xDD4_itemVar.lgunray.scale = item_spec_attr->max_scale;
    }
    if (ip->xDD4_itemVar.lgunray.scale < 1e-5f) {
        ip->xDD4_itemVar.lgunray.scale = scale;
    }
    HSD_JObjSetScaleZ(jobj, ip->xDD4_itemVar.lgunray.scale);

    return it_80273130(gobj);
}

void it_802985D8(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.lgunray.pos = ip->pos;
}

int it_802985F8(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_8029C4D4(gobj, &ip->x378_itemColl)) {
        return true;
    }
    return false;
}

bool it_80298634(Item_GObj* gobj)
{
    return true;
}

bool it_8029863C(Item_GObj* gobj)
{
    return true;
}

bool it_80298644(Item_GObj* gobj)
{
    return true;
}

bool it_8029864C(Item_GObj* gobj)
{
    return true;
}

bool it_80298654(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    ip->facing_dir = -ip->facing_dir;
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    ip->xDD4_itemVar.lgunray.speed *= ip->xC70;
    HSD_JObjSetScaleZ(jobj, ip->xDD4_itemVar.lgunray.scale = scale);
    ip->xDD4_itemVar.lgunray.angle += M_PI;

    while (ip->xDD4_itemVar.lgunray.angle < 0.0f) {
        ip->xDD4_itemVar.lgunray.angle += 2 * M_PI;
    }
    while (ip->xDD4_itemVar.lgunray.angle > 2 * M_PI) {
        ip->xDD4_itemVar.lgunray.angle -= 2 * M_PI;
    }

    return false;
}

bool it_80298828(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);
    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->xDD4_itemVar.lgunray.scale = scale;
    ip->xDD4_itemVar.lgunray.angle = atan2f(ip->x40_vel.y, ip->x40_vel.x);
    while (ip->xDD4_itemVar.lgunray.angle < 0.0f) {
        ip->xDD4_itemVar.lgunray.angle += 2 * M_PI;
    }
    while (ip->xDD4_itemVar.lgunray.angle > 2 * M_PI) {
        ip->xDD4_itemVar.lgunray.angle -= 2 * M_PI;
    }
    return false;
}

void it_802988C4(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
