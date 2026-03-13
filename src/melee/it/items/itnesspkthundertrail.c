#include "itnesspkthundertrail.h"

#include <placeholder.h>
#include <platform.h>

#include "db/db.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itnesspkthunderball.h"
#include "MSL/trigf.h"

#include <math.h>
#include <baselib/jobj.h>

Item_GObj* it_802AC43C(Fighter_GObj* gobj, Item_GObj* ball, Vec3* pos,
                       s32 trail_idx, s32 arg4, f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* trail;
    PAD_STACK(8);

    if (trail_idx < 0 || trail_idx > 5) {
        return NULL;
    }

    spawn.kind = it_803F6C18[trail_idx];
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = ball;
    spawn.x44_flag.b0 = true;
    spawn.x40 = arg4;

    trail = Item_80268B18(&spawn);
    if (trail != NULL) {
        Item* ip = GET_ITEM(trail);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        ip->xDD4_itemVar.nesspkthundertrail.x0 = ball;
        ip->xDD4_itemVar.nesspkthundertrail.x4 = trail_idx;
        ip->xDD4_itemVar.nesspkthundertrail.x8 = 0;
        it_8026B3A8(trail);
        ip->xDC8_word.flags.x13 = 0;
        it_80272940(trail);
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->x40_vel.y = 0.0f;
        ip->xDCC_flag.b3 = false;
        if (gobj != NULL) {
            db_80225DD8(trail, gobj);
        }
        it_802AC604(trail);
    }
    return trail;
}

void it_802AC58C(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        it_802725D4(gobj);
        ip->xDD4_itemVar.nesspkthundertrail.x0 = NULL;
        ip->owner = NULL;
        ip->xDC8_word.flags.x13 = 0;
    }
}

void it_802AC5D8(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->owner = NULL;
            ip->xDC8_word.flags.x13 = 0;
        }
    }
}

void it_802AC604(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
}

bool itNesspkthundertrail_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);

    if (ip->xDD4_itemVar.nesspkthundertrail.x8 & 1) {
        HSD_JObjSetFlagsAll(child, 0x10);
    } else {
        HSD_JObjClearFlagsAll(child, 0x10);
    }
    ip->xDD4_itemVar.nesspkthundertrail.x8++;

    if (ip->xDD4_itemVar.nesspkthundertrail.x0 == NULL) {
        return true;
    }
    return false;
}

void itNesspkthundertrail_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (ip->xDD4_itemVar.nesspkthundertrail.x0 != NULL) {
        f32 radius;
        f32 angle;
        Vec3 next_pos;

        it_802AB3F0(ip->xDD4_itemVar.nesspkthundertrail.x0, &ip->pos,
                    ip->xDD4_itemVar.nesspkthundertrail.x4);
        it_802AB468(ip->xDD4_itemVar.nesspkthundertrail.x0, &radius,
                    ip->xDD4_itemVar.nesspkthundertrail.x4);
        HSD_JObjSetScaleZ(jobj, 2.0f * radius / 4);

        it_802AB3F0(ip->xDD4_itemVar.nesspkthundertrail.x0, &next_pos,
                    ip->xDD4_itemVar.nesspkthundertrail.x4 + 1);

        if (ip->facing_dir == 1.0f) {
            angle = atan2f(ip->pos.y - next_pos.y, ip->pos.x - next_pos.x);
        } else {
            angle =
                M_PI + atan2f(ip->pos.y - next_pos.y, ip->pos.x - next_pos.x);
        }

        HSD_JObjSetRotationX(jobj, angle * -ip->facing_dir);
    }
}

bool itNesspkthundertrail_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}
