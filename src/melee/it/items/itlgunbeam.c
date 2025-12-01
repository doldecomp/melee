#include "itlgunbeam.h"

#include <placeholder.h>

#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/types.h"
#include "lb/lbvector.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>

/* 2993E0 */ static void it_802993E0(Item_GObj* gobj, s32 flags);
/* 299528 */ static void it_80299528(Item_GObj* gobj, s32 arg1);
/* 2998A0 */ static void it_802998A0(Item_GObj*, HSD_GObj*, s32);
/* 29999C */ static bool itLgunbeam_UnkMotion0_Anim(Item_GObj*);
/* 2999E4 */ static void itLgunbeam_UnkMotion0_Phys(Item_GObj*);
/* 299A68 */ static bool itLgunbeam_UnkMotion0_Coll(Item_GObj*);
/* 3F6630 */ ItemStateTable it_803F6630[] = {
    { 0, itLgunbeam_UnkMotion0_Anim, itLgunbeam_UnkMotion0_Phys,
      itLgunbeam_UnkMotion0_Coll },
};

void it_802993E0(Item_GObj* gobj, s32 flags)
{
    Item* item = GET_ITEM(gobj);
    Vec3 pos;
    pos.x = pos.y = pos.z = 0.0f;
    while (item->xDD4_itemVar.lgunbeam.angle0 < -M_PI) {
        item->xDD4_itemVar.lgunbeam.angle0 += 2 * M_PI;
    }
    while (item->xDD4_itemVar.lgunbeam.angle0 > +M_PI) {
        item->xDD4_itemVar.lgunbeam.angle0 -= 2 * M_PI;
    }
    if (flags & (1 << 0)) {
        pos.x += item->x378_itemColl.floor.normal.x;
        pos.y += item->x378_itemColl.floor.normal.y;
    }
    if (flags & (1 << 1)) {
        pos.x += item->x378_itemColl.ceiling.normal.x;
        pos.y += item->x378_itemColl.ceiling.normal.y;
    }
    if (flags & (1 << 2)) {
        pos.x += item->x378_itemColl.left_facing_wall.normal.x;
        pos.y += item->x378_itemColl.left_facing_wall.normal.y;
    }
    if (flags & (1 << 3)) {
        pos.x += item->x378_itemColl.right_facing_wall.normal.x;
        pos.y += item->x378_itemColl.right_facing_wall.normal.y;
    }
    lbVector_Normalize(&pos);
    item->xDD4_itemVar.lgunbeam.position1 = pos;
}

void it_80299528(Item_GObj* gobj, s32 arg1)
{
    Item* ip = GET_ITEM(gobj);

    if (arg1 != 0) {
        float angle1 = atan2f(ip->xDD4_itemVar.lgunbeam.position1.x,
                              ip->xDD4_itemVar.lgunbeam.position1.y);
        float angle2 = atan2f(ip->xDD4_itemVar.lgunbeam.velocity.x,
                              ip->xDD4_itemVar.lgunbeam.velocity.y) -
                       angle1;
        while (angle2 > M_PI) {
            angle2 -= 2 * M_PI;
        }
        while (angle2 < -M_PI) {
            angle2 += 2 * M_PI;
        }
        {
            float var_f1;
            if (angle2 == 0.0f) {
                var_f1 = 0.0f;
            } else {
                float temp_f1 =
                    lbVector_Angle(&ip->xDD4_itemVar.lgunbeam.position1,
                                   &ip->xDD4_itemVar.lgunbeam.velocity);
                {
                    float var_f2_2;
                    if (ABS(angle2) < M_PI_2) {
                        var_f2_2 = 0.02f * (ABS(angle2) / M_PI);
                    } else {
                        var_f2_2 = 0.5 * (ABS(angle2) / M_PI);
                    }
                    {
                        float var_f0;
                        if (angle2 < 0.0f) {
                            var_f0 = -var_f2_2;
                        } else {
                            var_f0 = var_f2_2;
                        }
                        var_f1 = temp_f1 * var_f0;
                    }
                }
            }
            ip->xDD4_itemVar.lgunbeam.angle0 -= var_f1;
        }
        while (ip->xDD4_itemVar.lgunbeam.angle0 < -M_PI) {
            ip->xDD4_itemVar.lgunbeam.angle0 += 2 * M_PI;
        }
        while (ip->xDD4_itemVar.lgunbeam.angle0 > +M_PI) {
            ip->xDD4_itemVar.lgunbeam.angle0 -= 2 * M_PI;
        }
    }
}

void it_802996D0(HSD_GObj* owner_gobj, Vec3* pos, u32 arg2, f32 facing_dir)
{
    SpawnItem spawn;
    PAD_STACK(4);

    spawn.kind = It_Kind_L_Gun_Beam;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(owner_gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = arg2;

    {
        Item_GObj* gobj = Item_80268B18(&spawn);
        if (gobj != NULL) {
            Item* item = GET_ITEM(gobj);
            ItLGunBeamAttr* item_spec_attr =
                item->xC4_article_data->x4_specialAttributes;
            item->xDAC_itcmd_var0 = item->xDB0_itcmd_var1 =
                item->xDB4_itcmd_var2 = item->xDB8_itcmd_var3 = 0;
            item->xDD4_itemVar.lgunbeam.lifetime = item_spec_attr->lifetime;
            it_80275158(gobj, item_spec_attr->lifetime);
            item->xDD4_itemVar.lgunbeam.position0 = *pos;
            {
                float temp = item_spec_attr->x4;
                item->xDD4_itemVar.lgunbeam.angle1 =
                    ((item_spec_attr->x8 - temp) * HSD_Randf()) + temp;
            }
            {
                float temp = item_spec_attr->xC;
                item->xDD4_itemVar.lgunbeam.angle0 =
                    (item_spec_attr->x10 - temp) * HSD_Randf() + temp;
            }
            {
                f32 angle;
                if (item->facing_dir == +1) {
                    angle = +item->xDD4_itemVar.lgunbeam.angle0;
                } else {
                    angle = -item->xDD4_itemVar.lgunbeam.angle0;
                }
                item->xDD4_itemVar.lgunbeam.angle0 = angle;
            }
            while (item->xDD4_itemVar.lgunbeam.angle0 < -M_PI) {
                item->xDD4_itemVar.lgunbeam.angle0 += 2 * M_PI;
            }
            while (item->xDD4_itemVar.lgunbeam.angle0 > M_PI) {
                item->xDD4_itemVar.lgunbeam.angle0 -= 2 * M_PI;
            }
            item->xDD4_itemVar.lgunbeam.xE04 = 0.0f;
            item->xDCC_flag.b3 = false;

            it_802998A0(gobj, owner_gobj, HSD_Randi(4));
        }
    }
}

void it_802998A0(Item_GObj* gobj, HSD_GObj* fighter_gobj, s32 arg2)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 sp2C = 1.0f;
    Vec3 pos;
    it_8026B3A8(gobj);
    // item->unkDCA = item->unkDCA & ~0x10;
    {
        PAD_STACK(8);
        ip->xDC8_word.flags.x3 = 0;
        it_80272940(gobj);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        pos = ip->pos;
        Item_802694CC(gobj);
        itLgunbeam_UnkMotion0_Phys(gobj);
        ip->pos.x -= ip->x40_vel.x;
        ip->pos.y -= ip->x40_vel.y;
        it_8026D9A0(gobj);
        ip->pos = pos;
        // item->pos.x = sp30;
        // item->pos.y = temp_r0;
        // item->pos.z = temp_r0_2;
        // efSync_Spawn(arg2 + 0x44E, gobj, item_jobj, item->0x2C, &sp2C,
        // temp_f1); efSync_Spawn(arg2 + 0x44E, gobj, item_jobj,
        // item->facing_dir, pos, &sp2C);
        efSync_Spawn(arg2 + 0x44E, gobj, jobj, ip->facing_dir, ip->pos, &sp2C);
        db_80225DD8(gobj, fighter_gobj);
    }
}

bool itLgunbeam_UnkMotion0_Anim(HSD_GObj* gobj)
{
    PAD_STACK(4 * 4);
    if (it_80273130(gobj) == 1) {
        efLib_DestroyAll(gobj);
        return true;
    }
    return false;
}

void itLgunbeam_UnkMotion0_Phys(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);

    ip->xDD4_itemVar.lgunbeam.position0 = ip->pos;

    ip->xDD4_itemVar.lgunbeam.velocity.x = ip->x40_vel.x =
        ip->xDD4_itemVar.lgunbeam.angle1 *
        sinf(ip->xDD4_itemVar.lgunbeam.angle0);

    ip->xDD4_itemVar.lgunbeam.velocity.y = ip->x40_vel.y =
        ip->xDD4_itemVar.lgunbeam.angle1 *
        cosf(ip->xDD4_itemVar.lgunbeam.angle0);

    ip->xDD4_itemVar.lgunbeam.velocity.z = ip->x40_vel.z = 0.0f;

    lbVector_Normalize(&ip->xDD4_itemVar.lgunbeam.velocity);
}

bool itLgunbeam_UnkMotion0_Coll(HSD_GObj* gobj)
{
    s32 flags = 0;
    Item* ip = GET_ITEM(gobj);
    while (ip->xDD4_itemVar.lgunbeam.angle0 < -M_PI) {
        ip->xDD4_itemVar.lgunbeam.angle0 += 2 * M_PI;
    }
    while (ip->xDD4_itemVar.lgunbeam.angle0 > +M_PI) {
        ip->xDD4_itemVar.lgunbeam.angle0 -= 2 * M_PI;
    }
    {
        ip->x378_itemColl.ecb_source.up = 3.0f;
        ip->x378_itemColl.ecb_source.down = 3.0f;
        ip->x378_itemColl.ecb_source.front = 3.0f;
        ip->x378_itemColl.ecb_source.back = 3.0f;
        it_8026D9A0(gobj);

        if (ip->x378_itemColl.env_flags & Collide_FloorMask) {
            flags |= 1;
        }
        if (ip->x378_itemColl.env_flags & Collide_CeilingMask) {
            flags |= 2;
        }
        if (ip->x378_itemColl.env_flags & Collide_LeftWallMask) {
            flags |= 4;
        }
        if (ip->x378_itemColl.env_flags & Collide_RightWallMask) {
            flags |= 8;
        }
        if (flags) {
            it_802993E0(gobj, flags);
            it_80299528(gobj, flags);
        }
    }
    return false;
}

bool it_3F14_Logic39_DmgDealt(Item_GObj* gobj)
{
    return false;
}

bool it_3F14_Logic39_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.lgunbeam.angle0 += M_PI;
    while (ip->xDD4_itemVar.lgunbeam.angle0 < -M_PI) {
        ip->xDD4_itemVar.lgunbeam.angle0 += 2 * M_PI;
    }
    while (ip->xDD4_itemVar.lgunbeam.angle0 > +M_PI) {
        ip->xDD4_itemVar.lgunbeam.angle0 -= 2 * M_PI;
    }
    ip->facing_dir = -ip->facing_dir;
    ip->x40_vel.x = -ip->x40_vel.x;
    ip->x40_vel.y = -ip->x40_vel.y;
    return false;
}

bool it_3F14_Logic39_Clanked(Item_GObj* gobj)
{
    return true;
}

bool it_3F14_Logic39_Absorbed(Item_GObj* gobj)
{
    return false;
}

bool it_3F14_Logic39_ShieldBounced(Item_GObj* gobj)
{
    return true;
}

bool it_3F14_Logic39_HitShield(Item_GObj* gobj)
{
    return true;
}

void it_3F14_Logic39_EvtUnk(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
