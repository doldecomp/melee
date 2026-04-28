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

/* 2993E0 */ static void it_802993E0(Item_GObj* gobj, int flags);
/* 299528 */ static void it_80299528(Item_GObj* gobj, int arg1);
/* 2998A0 */ static void it_802998A0(Item_GObj*, HSD_GObj*, s32);
/* 29999C */ static bool itLgunbeam_UnkMotion0_Anim(Item_GObj*);
/* 2999E4 */ static void itLgunbeam_UnkMotion0_Phys(Item_GObj*);
/* 299A68 */ static bool itLgunbeam_UnkMotion0_Coll(Item_GObj*);
/* 3F6630 */ ItemStateTable it_803F6630[] = {
    { 0, itLgunbeam_UnkMotion0_Anim, itLgunbeam_UnkMotion0_Phys,
      itLgunbeam_UnkMotion0_Coll },
};

static inline void clamp_angle(float* f)
{
    while (*f < -M_PI) {
        *f += M_TAU;
    }
    while (*f > M_PI) {
        *f -= M_TAU;
    }
}

void it_802993E0(Item_GObj* gobj, int flags)
{
    Item* item = GET_ITEM(gobj);
    Vec3 pos;
    pos.x = pos.y = pos.z = 0.0f;
    clamp_angle(&item->xDD4_itemVar.lgunbeam.angle0);
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

void it_80299528(Item_GObj* gobj, int arg1)
{
    Item* ip = GET_ITEM(gobj);

    if (arg1 != 0) {
        float angle1 = atan2f(ip->xDD4_itemVar.lgunbeam.position1.x,
                              ip->xDD4_itemVar.lgunbeam.position1.y);
        float angle2 = atan2f(ip->xDD4_itemVar.lgunbeam.velocity.x,
                              ip->xDD4_itemVar.lgunbeam.velocity.y) -
                       angle1;
        // note: opposite order as clamp_angle
        while (angle2 > M_PI) {
            angle2 -= M_TAU;
        }
        while (angle2 < -M_PI) {
            angle2 += M_TAU;
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
        clamp_angle(&ip->xDD4_itemVar.lgunbeam.angle0);
    }
}

Item_GObj* it_802996D0(HSD_GObj* owner_gobj, Vec3* pos, u32 arg2,
                       f32 facing_dir)
{
    f32 diff;
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
            it_80275158(gobj, item->xDD4_itemVar.lgunbeam.lifetime =
                                  item_spec_attr->lifetime);
            item->xDD4_itemVar.lgunbeam.position0 = *pos;
            {
                f32 r = HSD_Randf();
                f32 lo = item_spec_attr->x4;
                diff = item_spec_attr->x8 - lo;
                item->xDD4_itemVar.lgunbeam.angle1 = diff * r + lo;
            }
            {
                f32 r = HSD_Randf();
                f32 lo = item_spec_attr->xC;
                diff = item_spec_attr->x10 - lo;
                item->xDD4_itemVar.lgunbeam.angle0 = diff * r + lo;
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
                item->xDD4_itemVar.lgunbeam.angle0 += M_TAU;
            }
            while (item->xDD4_itemVar.lgunbeam.angle0 > M_PI) {
                item->xDD4_itemVar.lgunbeam.angle0 -= M_TAU;
            }
            item->xDD4_itemVar.lgunbeam.xE04 = 0.0f;
            item->xDCC_flag.b3 = false;

            it_802998A0(gobj, owner_gobj, HSD_Randi(4));
        }
        return gobj;
    }
}

void it_802998A0(Item_GObj* gobj, HSD_GObj* fighter_gobj, s32 arg2)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    {
        PAD_STACK(0x198);
    }
    {
        Vec3 pos;
        f32 sp2C = 1.0f;
        PAD_STACK(0x10);
        it_8026B3A8(gobj);
        ip->xDC8_word.flags.x13 = 0;
        it_80272940(gobj);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        pos = ip->pos;
        Item_802694CC(gobj);
        itLgunbeam_UnkMotion0_Phys(gobj);
        ip->pos.x -= ip->x40_vel.x;
        ip->pos.y -= ip->x40_vel.y;
        it_8026D9A0(gobj);
        ip->pos = pos;
        efSync_Spawn(arg2 + 0x44E, gobj, jobj, &ip->facing_dir, &sp2C);
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
    int flags;
    Item* ip = GET_ITEM(gobj);
    int flags2;
    PAD_STACK(0x1E0);
    clamp_angle(&ip->xDD4_itemVar.lgunbeam.angle0);
    flags = 0;
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
    if ((flags2 = flags) != 0) {
        it_802993E0(gobj, flags2);
        it_80299528(gobj, flags2);
    }
    return false;
}

bool itLGunBeam_Logic39_DmgDealt(Item_GObj* gobj)
{
    return false;
}

bool itLGunBeam_Logic39_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.lgunbeam.angle0 += M_PI;
    clamp_angle(&ip->xDD4_itemVar.lgunbeam.angle0);
    ip->facing_dir = -ip->facing_dir;
    ip->x40_vel.x = -ip->x40_vel.x;
    ip->x40_vel.y = -ip->x40_vel.y;
    return false;
}

bool itLGunBeam_Logic39_Clanked(Item_GObj* gobj)
{
    return true;
}

bool itLGunBeam_Logic39_Absorbed(Item_GObj* gobj)
{
    return false;
}

bool itLGunBeam_Logic39_ShieldBounced(Item_GObj* gobj)
{
    return true;
}

bool itLGunBeam_Logic39_HitShield(Item_GObj* gobj)
{
    return true;
}

void itLGunBeam_Logic39_EvtUnk(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
