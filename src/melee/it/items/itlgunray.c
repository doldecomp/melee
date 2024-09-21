#include "itlgunray.h"

#include "db/db_2253.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/items/itfoxlaser.h"
#include "it/types.h"
#include "lb/lbvector.h"

#include <math.h>
#include <stdbool.h>
#include <baselib/gobj.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>

// void it_802982AC(HSD_GObj); /* static */
void it_802982AC(Item_GObj*, Item_GObj*, Article*); /* static */
int it_80298300(HSD_GObj*);                         /* static */
void it_802985D8(HSD_GObj*);                        /* static */
int it_802985F8(HSD_GObj*);                         /* static */
static s8 it_803F6508[0x25] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static s8 it_804D5300[7] = "jobj.h";
static s8 it_804D5308[5] = "jobj";

static f32 it_804DCBD0 = 0.0f;
static f32 it_804DCBD4 = 1.0f;
static f32 it_804DCBD8 = 3.14159f;
static f32 it_804DCBDC = -1.0f;
static f32 it_804DCBE0[2] = { 0x3FF921FB, 0x54442D18 }; // some form of pi?
static f32 it_804DCBE8[2] = { 0x400921FB, 0x54442D18 }; // some form of pi?
static f32 it_804DCBF0 = 7.0f;
static f32 it_804DCBF4 = 0.00001f;
static f32 it_804DCBF8 = 0.001f;
static f32 it_804DCC00[2] = { 0x401921FB, 0x54442D18 }; // 2pi?

ItemStateTable it_803F64F8[1] = {
    { 0, it_80298300, it_802985D8, it_802985F8 },
};

// void it_80298168(HSD_GObj* owner_gobj, Vec3* arg1, f32 facing_dir) {
void it_80298168(HSD_GObj* owner_gobj, Vec3* pos, f32 dir)
{
    Article* article;
    Item* item;
    Item_GObj* item_gobj;
    SpawnItem spawn;
    s32 unused;

    f32 var_f2;
    ItLGunRayAttr* item_spec_attr;

    spawn.kind = 0x23; // type: LGunRay
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68((Item_GObj*) owner_gobj, &spawn.pos);
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = owner_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = 1; // Not sure if this is the right bit
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        article = item->xC4_article_data;
        item_spec_attr = article->x4_specialAttributes;
        it_802982AC(item_gobj, (Item_GObj*) owner_gobj, article);
        var_f2 = 0.0f;
        item->xDD4_itemVar.lgunray.x0 = 0.0f;
        if (item->facing_dir == 1.0f) {
            // item->xDD4_itemVar.lgunray.x4 = 0.0f;
        } else {
            var_f2 = 3.1415927f; // Pi
        }
        item->xDD4_itemVar.lgunray.x4 = var_f2;
        item->xDD4_itemVar.lgunray.x8 = item_spec_attr->x0;
        item->xDD4_itemVar.lgunray.xC = spawn.pos;
        item->x40_vel.x = item_spec_attr->x0 * item->facing_dir;
        db_80225DD8(item_gobj, (Fighter_GObj*) owner_gobj);
    }
}

// void it_802982AC(HSD_GObj* item_gobj) {
void it_802982AC(Item_GObj* item_gobj, Item_GObj* owner_gobj, Article* article)
{
    it_80275158((HSD_GObj*) item_gobj,
                ((ItLGunRayAttr*) ((Item*) item_gobj->user_data)
                     ->xC4_article_data->x4_specialAttributes)
                    ->x4);
    it_8026B3A8((Item_GObj*) item_gobj);
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
}

int it_80298300(HSD_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    // f32 rot_y;
    // f32 rot_x;
    // f32 scale_z;
    f32 dir;
    f32 var_f2;
    ItLGunRayAttr* item_spec_attr;

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    item_spec_attr = item->xC4_article_data->x4_specialAttributes;
    item->x40_vel.x =
        item->xDD4_itemVar.lgunray.x8 * cosf(item->xDD4_itemVar.lgunray.x4);
    item->x40_vel.y =
        item->xDD4_itemVar.lgunray.x8 * sinf(item->xDD4_itemVar.lgunray.x4);
    item->x40_vel.z = 0.0f;
    if (item->x40_vel.x > 0.0f) {
        dir = 1.0f;
    } else {
        dir = -1.0f;
    }
    item->facing_dir = dir;
    // rot_y = 1.5707963267948966 * item->facing_dir; // half-pi
    if (item_jobj == NULL) {
        HSD_JObjSetRotationY(item_jobj,
                             (1.5707963267948966 * item->facing_dir));
        // }

        if (item->facing_dir == 1.0f) {
            // var_f2 = -1 * item->x40_vel.x;
            var_f2 = -item->x40_vel.x;
        } else {
            var_f2 = item->x40_vel.x;
        }
        // rot_x = 3.141592653589793 + atan2f(item->x40_vel.y, var_f2);
        // if (item_jobj == NULL) {
        HSD_JObjSetRotationX(
            item_jobj, (3.141592653589793 + atan2f(item->x40_vel.y, var_f2)));
        // }
        var_f2 = item->xDD4_itemVar.lgunray.x8;
        if (item->xDD4_itemVar.lgunray.x8 < 0.0f) { // Get abs. value
            // var_f2 *= -1;
            var_f2 = -var_f2;
        }
        item->xDD4_itemVar.lgunray.x0 += var_f2 / 7.0f;
        if (item->xDD4_itemVar.lgunray.x0 > item_spec_attr->x8) {
            item->xDD4_itemVar.lgunray.x0 = item_spec_attr->x8;
        }
        if (item->xDD4_itemVar.lgunray.x0 < 0.00001f) {
            item->xDD4_itemVar.lgunray.x0 = 0.001f;
        }
        // scale_z = item->xDD4_itemVar.lgunray.x0;
        // if (item_jobj == NULL) {
        HSD_JObjSetScaleZ(item_jobj, item->xDD4_itemVar.lgunray.x0);

        it_80273130((Item_GObj*) item_gobj);
    }

    // return 0;
}

void it_802985D8(HSD_GObj* item_gobj)
{
    Item* item;
    item = item_gobj->user_data;
    item->xDD4_itemVar.lgunray.xC = item->pos;
}

int it_802985F8(HSD_GObj* item_gobj)
{
    CollData item_coll = ((Item*) item_gobj->user_data)
                             ->x378_itemColl; // Not sure how this is used
    if (it_8029C4D4((Item_GObj*) item_gobj) != 0) { // Fox laser function
        return 1;
    }
    return 0;
}

int it_80298634(Item_GObj* item_gobj)
{
    return 1;
}

int it_8029863C(Item_GObj* item_gobj)
{
    return 1;
}

int it_80298644(Item_GObj* item_gobj)
{
    return 1;
}

int it_8029864C(Item_GObj* item_gobj)
{
    return 1;
}

int it_80298654(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    // item->facing_dir *= -1;
    item->facing_dir = -item->facing_dir;
    if (item_jobj == NULL) {
        HSD_JObjSetRotationY(item_jobj,
                             (1.5707963267948966 * item->facing_dir));
        // }
        item->xDD4_itemVar.lgunray.x8 *= item->xC70;
        item->xDD4_itemVar.lgunray.x0 = 0.001f;
        // if (item_jobj == NULL) {
        HSD_JObjSetScaleZ(item_jobj, 0.001f);
        // }
        item->xDD4_itemVar.lgunray.x4 += 3.141592653589793;
    }
loop_26:
    if (item->xDD4_itemVar.lgunray.x4 < 0.0f) {
        item->xDD4_itemVar.lgunray.x4 += 6.283185307179586;
        goto loop_26;
    }
loop_29:
    if (item->xDD4_itemVar.lgunray.x4 > 6.283185307179586) {
        item->xDD4_itemVar.lgunray.x4 -= 6.283185307179586;
        goto loop_29;
    }

    return 0;
}

int it_80298828(Item_GObj* item_gobj)
{
    Item* item;
    f32 unused1;
    f32 unused2;

    item = item_gobj->user_data;
    lbVector_Mirror(&item->x40_vel, &item->xC58);
    item->xDD4_itemVar.lgunray.x0 = 0.001f;
    item->xDD4_itemVar.lgunray.x4 = atan2f(item->x40_vel.y, item->x40_vel.x);
loop_2:
    if (item->xDD4_itemVar.lgunray.x4 < 0.0f) {
        item->xDD4_itemVar.lgunray.x4 += 6.283185307179586;
        goto loop_2;
    }
loop_5:
    if (item->xDD4_itemVar.lgunray.x4 > 6.283185307179586) {
        item->xDD4_itemVar.lgunray.x4 -= 6.283185307179586;
        goto loop_5;
    }
    return 0;
}

void it_802988C4(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
