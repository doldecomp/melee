#include "itgreatfoxlaser.h"

#include "math.h"
#include "placeholder.h"

#include "baselib/debug.h"

#include "baselib/forward.h"

#include "ft/ftlib.h"
#include "gr/ground.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

#include <baselib/jobj.h>

s32 it_802EAF28(Item_GObj* item_gobj)
{
    // can't use xDD4_itemVar.greatfoxlaser.x38, which is an s16
    return GET_ITEM(item_gobj)->xDD4_itemVar.likelike.x38;
}

void it_802EAF34(HSD_GObj* owner, Vec3* offset, int type)
{
    Item_GObj* item_gobj;
    Vec3 pos;
    HSD_JObj* jobj = owner->hsd_obj;
    u8 _pad[4];
    SpawnItem spawn;
    PAD_STACK(12);

    lb_8000B1CC(jobj, offset, &pos);
    spawn.kind = 0xEB;
    spawn.prev_pos = pos;
    spawn.facing_dir = -1.0f;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = NULL;
    spawn.x44_flag.b0 = false;
    spawn.x40 = 0;
    HSD_ASSERT(0x2BBU, jobj);
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        itGreatFoxLaser_Attrs* attr =
            ip->xC4_article_data->x4_specialAttributes;
        f32 scale = Ground_801C0498();
        ip->scl = scale;
        HSD_JObjSetScaleX(item_gobj->hsd_obj, scale);
        HSD_JObjSetScaleY(item_gobj->hsd_obj, ip->scl);
        HSD_JObjSetScaleZ(item_gobj->hsd_obj, ip->scl);
        ip->xDD4_itemVar.greatfoxlaser.x20 = owner;
        ip->xDD4_itemVar.greatfoxlaser.x28 = *offset;
        ip->xDD4_itemVar.greatfoxlaser.x38 = type;
        if (ip->xDD4_itemVar.greatfoxlaser.x38 == 0) {
            it_80272460(&ip->x5D4_hitboxes[0].hit, attr->x0, item_gobj);
        } else {
            it_80272460(&ip->x5D4_hitboxes[0].hit, attr->x8, item_gobj);
        }
        it_802EB268(item_gobj);
    }
}

void it_802EB1EC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    it_8027B730(gobj);
    it_8027C56C(gobj, ip->facing_dir);
    ip->xDCC_flag.b3 = 0;
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    ip->xDD4_itemVar.greatfoxlaser.x36 = 1;
    it_802EB268(gobj);
}

void it_802EB268(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    ip->xDD4_itemVar.greatfoxlaser.x36 = 60;
    ip->xDD4_itemVar.greatfoxlaser.x34 = 0;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itGreatfoxlaser_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGreatFoxLaser_Attrs* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj;
    Vec3 offset;
    PAD_STACK(12);

    if (!it_80272C6C(gobj)) {
        if (ip->xDD4_itemVar.greatfoxlaser.x38 == 0) {
            ip->x40_vel.x = attr->x4 * ip->facing_dir;
            it_80272460(&ip->x5D4_hitboxes[0].hit, attr->x0, gobj);
        } else {
            ip->x40_vel.x = attr->xC * ip->facing_dir;
            it_80272460(&ip->x5D4_hitboxes[0].hit, attr->x8, gobj);
        }
    } else {
        jobj = ip->xDD4_itemVar.greatfoxlaser.x20->hsd_obj;
        offset = ip->xDD4_itemVar.greatfoxlaser.x28;
        lb_8000B1CC(jobj, &offset, &ip->pos);
    }
    if (ip->xDD4_itemVar.greatfoxlaser.x36 == 0) {
        return true;
    }
    ip->xDD4_itemVar.greatfoxlaser.x36--;
    return false;
}

void itGreatfoxlaser_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.greatfoxlaser.x34 != 0) {
        ip->facing_dir = -ip->facing_dir;
        it_8027C56C(gobj, ip->facing_dir);
        ip = GET_ITEM(gobj);
        it_8026B3A8(gobj);
        ip->xDD4_itemVar.greatfoxlaser.x36 = 60;
        ip->xDD4_itemVar.greatfoxlaser.x34 = 0;
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
}

bool itGreatFoxLaser_Logic27_DmgDealt(Item_GObj* item_gobj)
{
    return false;
}

bool itGreatFoxLaser_Logic27_Clanked(Item_GObj* item_gobj)
{
    return false;
}

bool itGreatFoxLaser_Logic27_Absorbed(Item_GObj* item_gobj)
{
    return false;
}

bool it_2725_Logic27_Reflected(Item_GObj* gobj)
{
    u8 _pad[4];
    Item* ip = GET_ITEM(gobj);
    Vec3 reflect_pos;
    Vec3 laser_pos;
    HSD_JObj* jobj;
    PAD_STACK(16);

    if (ip->msid == 0) {
        ftLib_80086644(ip->xC64_reflectGObj, &reflect_pos);
        jobj = ip->xDD4_itemVar.greatfoxlaser.x20->hsd_obj;
        lb_8000B1CC(jobj, &ip->xDD4_itemVar.greatfoxlaser.x28, &laser_pos);
        ip->xDD4_itemVar.greatfoxlaser.x28.x -=
            ABS(laser_pos.x - reflect_pos.x);
        lb_8000B1CC(jobj, &ip->xDD4_itemVar.greatfoxlaser.x28, &ip->pos);
        HSD_JObjSetTranslate(ip->xBBC_dynamicBoneTable->bones[2], &ip->pos);
        ip->xDD4_itemVar.greatfoxlaser.x34 = 1;
    }
    return false;
}

void it_802EB5A8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
